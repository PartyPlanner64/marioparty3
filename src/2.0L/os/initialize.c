#include "common.h"
#include "initialize.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"

#define DEVICE_TYPE_INIT 7

extern __osExceptionVector __osExceptionPreamble[];

extern u64 D_800A3FA0_main;        // osClockRate
extern s32 D_800A3FA8_main;        // osViClock
extern OSPiHandle D_800D09C0_main; // __Dom1SpeedParam
extern OSPiHandle D_800CCEB0_main; // __Dom2SpeedParam
extern s32 D_8000030C;             // osResetType
extern s32 D_8000031C[];           // osAppNMIBuffer

extern void __osSetWatchLo(u32);
extern u32 __checkHardware_msp(void);
extern u32 __checkHardware_kmc(void);
extern u32 __checkHardware_isv(void);
extern void __osInitialize_msp(void);
extern void __osInitialize_kmc(void);
extern void __osInitialize_isv(void);
extern void __osInitialize_emu(void);

inline void __createSpeedParam(void) {
    D_800D09C0_main.type = DEVICE_TYPE_INIT;
    D_800D09C0_main.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    D_800D09C0_main.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    D_800D09C0_main.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    D_800D09C0_main.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    D_800CCEB0_main.type = DEVICE_TYPE_INIT;
    D_800CCEB0_main.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    D_800CCEB0_main.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    D_800CCEB0_main.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    D_800CCEB0_main.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}

void __osInitialize_common(void) {
    u32 pifdata;

    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);
    __osSetWatchLo(0x4900000);

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) {
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
    }

    *(__osExceptionVector *)UT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)XUT_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)ECC_VEC = *__osExceptionPreamble;
    *(__osExceptionVector *)E_VEC = *__osExceptionPreamble;

    osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    __createSpeedParam();
    osUnmapTLBAll();
    osMapTLBRdb();
    D_800A3FA0_main = D_800A3FA0_main * 3 / 4;

    if (D_8000030C == 0) {
        bzero(D_8000031C, OS_APP_NMI_BUFSIZE);
    }

    if (osTvType == OS_TV_PAL) {
        D_800A3FA8_main = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        D_800A3FA8_main = VI_MPAL_CLOCK;
    } else {
        D_800A3FA8_main = VI_NTSC_CLOCK;
    }

    if (__osGetCause() & CAUSE_IP5) {
        while (TRUE) {
        }
    }

    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
    IO_WRITE(AI_DACRATE_REG, AI_MAX_DAC_RATE - 1);
    IO_WRITE(AI_BITRATE_REG, AI_MAX_BIT_RATE - 1);
}

void __osInitialize_autodetect(void) {
    if (__checkHardware_msp()) {
        __osInitialize_msp();
    } else if (__checkHardware_kmc()) {
        __osInitialize_kmc();
    } else if (__checkHardware_isv()) {
        __osInitialize_isv();
    } else {
        __osInitialize_emu();
    }
}
