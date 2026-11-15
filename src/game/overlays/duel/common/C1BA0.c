#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkInputWaitWork {
    /* 0x00 */ Process *prc;
    /* 0x04 */ u16 *inputSeq;
    /* 0x08 */ s16 index;
} UnkInputWaitWork; // sizeof 0xC

void func_800D9E50_name_81(void);

void func_800D9DD0_name_81(u16 arg0, u16 arg1, char *arg2, u8 arg3, u8 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_800D9E50_name_81(void) {
    UnkInputWaitWork *work;

    work = HuPrcCurrentGet()->user_data;

    for (;; HuPrcVSleep()) {
        if (*D_800D5558_main == 0) {
            continue;
        } else if (*D_800D5558_main != work->inputSeq[work->index]) {
            work->index = 0;
            continue;
        } else if (work->inputSeq[++work->index] == 0) {
            work->index = -1;
            break;
        }
    }

    while (1) {
        HuPrcVSleep();
    }
}

void func_800D9EFC_name_81(u16 *arg0) {
    Process *process;
    UnkInputWaitWork *work;

    process = omAddPrcObj(func_800D9E50_name_81, 0xEFFF, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(UnkInputWaitWork));
    process->user_data = work;
    work->inputSeq = arg0;
    work->index = 0;
    work->prc = process;
}

void func_800D9F5C_name_81(UnkInputWaitWork *work) {
    omDelPrcObj(work->prc);
}

s32 func_800D9F78_name_81(UnkInputWaitWork *work) {
    if (~work->index) {
        return 0;
    } else {
        return 1;
    }
}
