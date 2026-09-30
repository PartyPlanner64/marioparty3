#include "common.h"
#include "ovl_81.h"

typedef struct UnkInputWaitWork {
    /* 0x00 */ Process *prc;
    /* 0x04 */ u16 *inputSeq;
    /* 0x08 */ s16 index;
} UnkInputWaitWork; // sizeof 0xC

void func_800D9E50_name_81(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1BA0", func_800D9DD0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1BA0", func_800D9E50_name_81);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1BA0", func_800D9F5C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1BA0", func_800D9F78_name_81);
