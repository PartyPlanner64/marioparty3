#include "common.h"
#include "ovl_81.h"

void func_800D7D70_name_81(void) {
    s32 i;
    for (i = 0; i < 128; i++) {
        D_801029C8_name_81[i] = 0;
    }
}

s16 func_800D7DA0_name_81(s16 arg0) {
    D_801029C8_name_81[arg0]++;
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D7DC8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D7E14_name_81);

s16 func_800D7E68_name_81(s16 arg0) {
    if (D_801029C8_name_81[arg0] != 0) {
        D_801029C8_name_81[arg0]++;
        return arg0;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D7EB8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D7F0C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D7F4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8010_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8314_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D85A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D85B4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D87DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D87E8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8944_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D898C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8B18_name_81);

void func_800D8E34_name_81(Object* arg0) {
    Object* temp_s0 = arg0;

    func_8001C258_main(temp_s0->omObj1->model[0], 4, 0);
    if (temp_s0->omObj2 != NULL) {
        func_8001C258_main(temp_s0->omObj2->model[0], 4, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8E88_name_81);

void func_800D8EB8_name_81(Object* arg0) {
    Object* temp_s0 = arg0;

    func_8001C258_main(temp_s0->omObj1->model[0], 4, 4);
    if (temp_s0->omObj2 != NULL) {
        func_8001C258_main(temp_s0->omObj2->model[0], 4, 4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8F0C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8F3C_name_81);

s32 func_800D9098_name_81(NameEntry *arg0) {
    NameEntry *node;

    for (node = D_801029C0_name_81; node != NULL; node = node->next) {
        if (node == arg0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D90D0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D918C_name_81);

u16 func_800D9234_name_81(Object *arg0) {
    u16 ret;

    ret = 0;
    if (HmfModelData[arg0->omObj1->model[0]].motTime == D_800CCF58_main[HmfModelData[arg0->omObj1->model[0]].motId].unk02) {
        ret = 1;
    }
    return ret;
}

u16 func_800D92A8_name_81(Object *arg0) {
    u16 ret;

    ret = 0;
    if (HmfModelData[arg0->omObj1->model[0]].motTime == 0.0f) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D92F8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D9384_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D94C4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D9668_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D96F4_name_81);

void func_800D974C_name_81(Object* arg0) {
    Process* proc;
    Object** work;

    proc = omAddPrcObj(func_800D96F4_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    *work = arg0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C48_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C4C_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C50_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C54_name_81);
