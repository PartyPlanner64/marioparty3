#include "common_board.h"
#include "sprgrp.h"
#include "game/malloc.h"
#include "game/mallocblock.h"

extern UnkBoard8 *mbSprGrpListHead;
extern u16 mbSprGrpNum;

void MBSprGrpInit(void) {
    mbSprGrpListHead = NULL;
    mbSprGrpNum = 0;
}

void MBSprGrpClose(void) {
    while (mbSprGrpListHead != NULL) {
        MBSprGrpKill(mbSprGrpListHead);
    }
}

static UnkBoard8 *MBSprGrpAlloc(s16 amount) {
    UnkBoard8 *temp_v0;
    s32 i;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkBoard8));
    if (temp_v0 != NULL) {
        mbSprGrpNum++;
        temp_v0->unk_00 = mbSprGrpListHead;
        temp_v0->unk_04 = 0;

        if (mbSprGrpListHead != NULL) {
            mbSprGrpListHead->unk_04 = temp_v0;
        }

        mbSprGrpListHead = temp_v0;
        temp_v0->amount = amount;

        temp_v0->model = HuMemMemoryAllocTemp(amount * (sizeof *temp_v0->model));
        for (i = 0; i < amount; i++) {
            temp_v0->model[i] = -1;
        }

        temp_v0->unk_10 = HuMemMemoryAllocTemp(amount * (sizeof *temp_v0->unk_10));
        for (i = 0; i < amount; i++) {
            temp_v0->unk_10[i] = 1.0f;
        }

        temp_v0->unk_14 = HuMemMemoryAllocTemp(amount * (sizeof *temp_v0->unk_14));
        for (i = 0; i < amount; i++) {
            temp_v0->unk_14[i] = 1.0f;
        }

        temp_v0->xPositions = HuMemMemoryAllocTemp(amount * (sizeof *temp_v0->xPositions));
        for (i = 0; i < amount; i++) {
            temp_v0->xPositions[i] = 0;
        }

        temp_v0->yPositions = HuMemMemoryAllocTemp(amount * (sizeof *temp_v0->yPositions));
        for (i = 0; i < amount; i++) {
            temp_v0->yPositions[i] = 0;
        }
    }
    return temp_v0;
}

UnkBoard8 *MBSprGrpCreate(s16 arg0, s16 arg1) {
    UnkBoard8 *temp_v0;

    temp_v0 = MBSprGrpAlloc(arg0);
    if (temp_v0 != NULL) {
        temp_v0->spriteGroup = HuSprGrpCreate(arg0, arg1);
    }
    return temp_v0;
}

void MBSprGrpKill(UnkBoard8* arg0) {
    s16 model;
    s32 i;

    if (arg0->unk_00 != NULL) {
        arg0->unk_00->unk_04 = arg0->unk_04;
    }

    if (arg0->unk_04 != NULL) {
        arg0->unk_04->unk_00 = arg0->unk_00;
    } else {
        mbSprGrpListHead = arg0->unk_00;
    }

    for (i = 0; i < arg0->amount; i++) {
        model = arg0->model[i];
        if (model >= 0) {
            HuSprAnimKill(model);
        }
    }

    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreeTemp(arg0->xPositions);
    HuMemMemoryFreeTemp(arg0->yPositions);
    HuMemMemoryFreeTemp(arg0->unk_10);
    HuMemMemoryFreeTemp(arg0->unk_14);
    HuMemMemoryFreeTemp(arg0->model);
    HuMemMemoryFreeTemp(arg0);
    mbSprGrpNum--;
}

//unused
void MBSprGrpPosSet(UnkBoard8* arg0, s16 member, s16 x, s16 y) {
    arg0->xPositions[member] = x;
    arg0->yPositions[member] = y;
    HuSprPosSet(arg0->spriteGroup, member, x, y);
}

//unused
void MBSprGrpScaleSet(UnkBoard8 *arg0, s16 member, f32 arg2, f32 arg3) {
    arg0->unk_10[member] = arg2; //rot?
    arg0->unk_14[member] = arg3; //scale?
    HuSprScaleSet(arg0->spriteGroup, member, arg2, arg3);
}
