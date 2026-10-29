#include "common.h"
#include "initialize.h"
#include "PR/R4300.h"

#define MSCP_COMPARE 0x4B4D4300
#define MSCP_COMPARE_ADDR (*(vu32 *)0xBFF00000)
#define MSCP_STATUS_ADDR (*(vu32 *)0xBFF00010)

extern u32 D_8007FB20_main[];

extern u32 __kmc_pt_mode;
extern u32 D_800A3FC0_main; // stat
extern u32 D_800A3FC4_main; // wport
extern u32 D_800A3FCC_main; // column

static inline void kmc_putchar(char c) {
    u32 data;

    while (TRUE) {
        osPiReadIo(D_800A3FC0_main, &data);
        if (data & 4) {
            osPiWriteIo(D_800A3FC4_main, c);
            break;
        }
    }
}

char *kmc_proutSyncPrintf(char *str, const char *buf, int n) {
    int i;
    char c;
    char *p;
    char *q;
    char xbuf[128];

    p = xbuf;

    for (i = 0; i < n; i++) {
        c = *buf++;

        switch (c) {
            case '\n':
                *p++ = '\n';
                D_800A3FCC_main = 0;
                break;
            case '\t':
                do {
                    *p++ = ' ';
                } while (++D_800A3FCC_main & 7);
                break;
            default:
                D_800A3FCC_main++;
                *p++ = c;
                break;
        }

        if (c == '\n' || (p - xbuf) > 100) {
            kmc_putchar(p - xbuf - 1);
            q = xbuf;
            while (q != p) {
                kmc_putchar(*q++);
            }
            p = xbuf;
        }
    }

    if (p != xbuf) {
        kmc_putchar(p - xbuf - 1);
        q = xbuf;
        while (q != p) {
            kmc_putchar(*q++);
        }
    }

    return (char *)1;
}

void __osInitialize_kmc(void) {
    int (*fnc)();
    u32 *dst;
    u32 *src;
    u32 monadr;
    vu32 *mon;
    vu32 *stat;
    u32 *vecSrc;
    u32 *vecDst;
    int j;

    if (!__kmc_pt_mode) {
        stat = (vu32 *)0xBFF08004;
        mon = (vu32 *)0xBFF00000;
        if (*mon != MSCP_COMPARE) {
            return;
        }

        vecSrc = D_8007FB20_main;
        vecDst = (u32 *)E_VEC;
        *vecDst++ = *vecSrc++;
        *vecDst++ = *vecSrc++;
        *vecDst++ = *vecSrc++;
        vecDst += 2, vecSrc += 2;
        *vecDst++ = *vecSrc++;
        *vecDst++ = *vecSrc++;
        *vecDst++ = *vecSrc++;

        osWritebackDCache((void *)E_VEC, 0x24);
        osInvalICache((void *)E_VEC, 0x24);
        __kmc_pt_mode = TRUE;
        if (!(*stat & 0x10)) {
            monadr = *(mon + 1);
            if (monadr != (u32)mon) {
                dst = (u32 *)(monadr | 0x20000000);
                for (j = 0x800, src = (u32 *)mon; j != 0; j--) {
                    *dst++ = *src++;
                }
            }
            fnc = (int (*)())(monadr + 8);
            fnc(MSCP_COMPARE, 0);
        }
        __printfunc = (void *)kmc_proutSyncPrintf;
    }
}

u32 __checkHardware_kmc(void) {
    if (MSCP_COMPARE_ADDR != MSCP_COMPARE) {
        return 0;
    }
    return MSCP_STATUS_ADDR == 0xB0FFB000;
}
