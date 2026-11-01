#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/main.h"
#include "PR/os.h"
#include "game/nnsched.h"

extern OSThread gInitThread;
extern u8 gThread1Stack[];
extern OSThread gMainThread;
extern u64 *gThread3Stack;

void ultraMain(void);
void thread1_idle(void *arg);

void __osInitialize_autodetect(void);

void ultraMain() {
    __osInitialize_common();
    __osInitialize_autodetect();
    InitSchedulerEvent();
    func_800357AC_main(3);
    osCreateThread(&gInitThread, 1, &thread1_idle, NULL, &gThread1Stack[2048], 10);
    osStartThread(&gInitThread);
}

void thread1_idle(void *arg) {
    osCreateThread(&gMainThread, 3, &main, arg, &gThread3Stack, 2);
    osStartThread(&gMainThread);
    osSetIntMask(0x3FFF01);
    osSetThreadPri(NULL, 0);

    // idle forever
    while (1) {}
}
