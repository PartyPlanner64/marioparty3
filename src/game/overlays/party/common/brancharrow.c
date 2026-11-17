#include "common_board.h"
#include "game/board.h"
#include "model.h"
#include "game/malloc.h"

//this file matches brancharrow.c in duel/common

UnkBoard2 *MBBranchArrowCreate(s32 arg0) {
    s32 sp10[3] = { 0x00000016, 0x00000016, 0x00000016 };
    UnkBoard2 *temp_v0;
    Object *temp_v0_2;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkBoard2));
    temp_v0->unk_00 = 0;
    temp_v0->obj = MBModelCreate(sp10[arg0], NULL);
    Hu3DModelAttrSet(temp_v0->obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(temp_v0->obj->omObj1->model[0], 0x1400);
    Hu3DModelRemakeStatic(temp_v0->obj->omObj1->model[0]);
    MBModelTempAllocFree(temp_v0->obj);
    return temp_v0;
}

static void MBBranchArrowKill(UnkBoard2* arg0) {
    MBModelKill(arg0->obj);
    HuMemMemoryFreeTemp(arg0);
}

UnkEA790Struct* MBBranchArrowGrpCreate(void) {
    UnkEA790Struct* temp_v0;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkEA790Struct));
    temp_v0->unk_00 = 0;
    temp_v0->unk_02 = 0;
    temp_v0->unk_04 = 0;
    temp_v0->proc = NULL;
    temp_v0->unk_0C = 0;
    temp_v0->player = NULL;
    return temp_v0;
}

void MBBranchArrowGrpKill(UnkEA790Struct* arg0) {
    UnkBoard2** var_s1;
    s32 i;

    if (arg0->unk_02 != 0) {
        var_s1 = arg0->unk_04;
        for (i = 0; i < arg0->unk_02; i++) {
            MBBranchArrowKill(*var_s1++);
        }
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    
    if (arg0->proc != NULL) {
        omDelPrcObj(arg0->proc);
    }
    
    HuMemMemoryFreeTemp(arg0);
}

void MBBranchArrowGrpAdd(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2) {
    UnkBoard2 **newList;
    UnkBoard2 **dst;
    UnkBoard2 **src;
    s32 i;

    newList = HuMemMemoryAllocTemp(++arg0->unk_02 * sizeof(UnkBoard2 *));
    dst = newList;
    if (arg0->unk_04 != NULL) {
        src = arg0->unk_04;
        for (i = 0; i < arg0->unk_02 - 1; i++) {
            *dst++ = *src++;
        }
    }

    if (1) {
        *dst = arg1;
    } else {
        *dst = arg1;
    }

    if (arg0->unk_04 != NULL) {
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    
    arg0->unk_04 = newList;

    arg1->unk_00 = arg2;
    if (arg2 & 1) {
        arg0->unk_0C = arg0->unk_02 - 1;
    }
}

//unused
void MBBranchArrowGrpRemove(UnkEA790Struct *arg0, UnkBoard2* arg1) {
    UnkBoard2 **newList;
    UnkBoard2 **dst;
    UnkBoard2 **src;
    s16 count;
    s32 i;

    count = arg0->unk_02;
    newList = NULL;
    if (count >= 2) {
        count--;
        arg0->unk_02 = count;
        newList = HuMemMemoryAllocTemp(count * sizeof(s32));
        dst = newList;
        src = arg0->unk_04;
        for (i = 0; i <= arg0->unk_02; i++) {
            if (*src == arg1) {
                src++;
            } else {
                *dst = *src;
                src++;
                dst++;
            }
        }
    } else {
        arg0->unk_02 = 0;
    }

    if (arg0->unk_04 != NULL) {
        HuMemMemoryFreeTemp(arg0->unk_04);
    }
    arg0->unk_04 = newList;
}

UnkBoard2* MBBranchArrowGrpArrowGet(UnkEA790Struct* arg0, s16 arg1) {
    return arg0->unk_04[arg1];
}
