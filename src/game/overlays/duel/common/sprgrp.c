#include "common_duel.h"
#include "ovl_81.h"

void MBDSprGrpInit(void) {
    mbdSprGrpListHead = 0;
    mbdSprGrpNum = 0;
}

void MBDSprGrpClose(void) {
    while (mbdSprGrpListHead != 0) {
        MBDSprGrpKill(mbdSprGrpListHead);
    }
}

UnkBoard4 *MBDSprGrpAlloc(s16 arg0) {
    UnkBoard4 *temp_v0;
    s32 i;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(UnkBoard4));
    if (temp_v0 != NULL) {
        mbdSprGrpNum++;

        temp_v0->unk_00 = (void *)mbdSprGrpListHead;
        temp_v0->unk_04 = NULL;

        if (mbdSprGrpListHead != NULL) {
            mbdSprGrpListHead->unk_04 = temp_v0;
        }

        mbdSprGrpListHead = temp_v0;
        temp_v0->unk_08 = arg0;

        temp_v0->unk_0C = HuMemMemoryAllocTemp(arg0 * sizeof(*temp_v0->unk_0C));
        for (i = 0; i < arg0; i++) {
            temp_v0->unk_0C[i] = -1;
        }

        temp_v0->unk_10 = HuMemMemoryAllocTemp(arg0 * sizeof(*temp_v0->unk_10));
        for (i = 0; i < arg0; i++) {
            temp_v0->unk_10[i] = 1.0f;
        }

        temp_v0->unk_14 = HuMemMemoryAllocTemp(arg0 * sizeof(*temp_v0->unk_14));
        for (i = 0; i < arg0; i++) {
            temp_v0->unk_14[i] = 1.0f;
        }

        temp_v0->unk_18 = HuMemMemoryAllocTemp(arg0 * sizeof(*temp_v0->unk_18));
        for (i = 0; i < arg0; i++) {
            temp_v0->unk_18[i] = 0;
        }

        temp_v0->unk_1C = HuMemMemoryAllocTemp(arg0 * sizeof(*temp_v0->unk_1C));
        for (i = 0; i < arg0; i++) {
            temp_v0->unk_1C[i] = 0;
        }
    }
    return temp_v0;
}

UnkBoard4 *MBDSprGrpCreate(s16 arg0, s16 arg1) {
    UnkBoard4 *temp_v0;

    temp_v0 = MBDSprGrpAlloc(arg0);
    if (temp_v0 != NULL) {
        temp_v0->unk_0A = HuSprGrpCreate(arg0, arg1);
    }
    return temp_v0;
}

void MBDSprGrpKill(UnkBoard4 *arg0) {
    s32 i;

    if (arg0->unk_00 != NULL) {
        arg0->unk_00->unk_04 = arg0->unk_04;
    }

    if (arg0->unk_04 != NULL) {
        arg0->unk_04->unk_00 = arg0->unk_00;
    } else {
        mbdSprGrpListHead = arg0->unk_00;
    }

    for (i = 0; i < arg0->unk_08; i++) {
        if (arg0->unk_0C[i] >= 0) {
            HuSprAnimKill(arg0->unk_0C[i]);
        }
    }

    HuSprGrpKill(arg0->unk_0A);
    HuMemMemoryFreeTemp(arg0->unk_18);
    HuMemMemoryFreeTemp(arg0->unk_1C);
    HuMemMemoryFreeTemp(arg0->unk_10);
    HuMemMemoryFreeTemp(arg0->unk_14);
    HuMemMemoryFreeTemp(arg0->unk_0C);
    HuMemMemoryFreeTemp(arg0);
    mbdSprGrpNum -= 1;
}

void MBDSprGrpPosSet(UnkBoard4 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_18[arg1] = arg2;
    arg0->unk_1C[arg1] = arg3;
    HuSprPosSet(arg0->unk_0A, arg1, arg2, arg3);
}

void MBDSprGrpScaleSet(UnkBoard4 *arg0, s16 arg1, f32 arg2, f32 arg3) {
    arg0->unk_10[arg1] = arg2;
    arg0->unk_14[arg1] = arg3;
    HuSprScaleSet(arg0->unk_0A, arg1, arg2, arg3);
}
