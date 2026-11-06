#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} BA4B0_ProcessData; // Size 0xC

extern u8 D_800EBADC_minigame[];
extern u8 D_800EBAE4_minigame[];
extern u8 D_800EBAEC_minigame[];

void func_800E7F60_minigame(void);
s16 func_800E905C_minigame(s16 arg0);

void func_800E7930_minigame(s16 group, s16 member, s16 graphic, u16 prio, s16 x, s16 y) {
    HuSprTPLvlSet(group, member, 256);
    HuSprAttrReset(group, member, 0xFFFF);
    HuSprAttrSet(group, member, 0x9000);
    HuSprScaleSet(group, member, 1.0f, 1.0f);
    func_800550F4_main(group, member, 0);
    HuSprGrpMemberSet(group, member, graphic, 0);
    HuSprPriSet(group, member, prio);
    HuSprPosSet(group, member, x, y);
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7A2C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7BCC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7E08_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7F60_minigame);

Process *func_800E8EC4_minigame(u16 arg0, s16 arg1) {
    BA4B0_ProcessData *data;
    Process *prc;

    if (arg0 == 0 || arg0 == 1) {
        if (func_800E905C_minigame(arg1) < 0) {
            return NULL;
        }
    }
    data = HuMemAllocTag(sizeof(BA4B0_ProcessData), 0x7918);
    memset(data, 0, sizeof(BA4B0_ProcessData));
    data->x = 160;
    data->y = 120;
    data->unk00 = arg0;
    data->unk02 = arg1;
    prc = omAddPrcObj(func_800E7F60_minigame, 0x4000, 0x800, 0);
    prc->user_data = data;
    return prc;
}

s32 func_800E8F78_minigame(Process *prc) {
    BA4B0_ProcessData *data;
    s32 result;

    if (prc == NULL) {
        return 0;
    }
    data = prc->user_data;
    data->unk04 = 0xFF;
    do {
        HuPrcVSleep();
    } while (data->unk04 != 0);
    result = omDelPrcObj(prc);
    HuMemFree(data);
    return result;
}

s16 func_800E8FE4_minigame(Process *prc, s16 value) {
    BA4B0_ProcessData *data = prc->user_data;

    data->unk04 = value;
    return value;
}

s16 func_800E8FF8_minigame(Process *prc) {
    BA4B0_ProcessData *data = prc->user_data;

    return data->unk04;
}

void func_800E9004_minigame(Process *prc, s16 value) {
    BA4B0_ProcessData *data = prc->user_data;

    if (data->unk04 != value) {
        do {
            HuPrcVSleep();
        } while (data->unk04 != value);
    }
}

s16 func_800E905C_minigame(s16 arg0) {
    u8 *last;
    u8 *entries;
    s16 total;
    s16 rank;
    s32 i;

    if (arg0 >= 6) {
        return -1;
    }
    if (arg0 < 0) {
        last = &GwStory.progress.fields.unkF;
        entries = GwStory.progress.fields.unk3;
    } else {
        last = &GwStory.unk58[arg0];
        entries = GwStory.unk10[arg0];
    }
    if (*last == 0) {
        return -1;
    }
    if (*last >= 5) {
        *last = 4;
    }
    total = D_800EBAE4_minigame[*last];
    for (i = 0; i < 12; i++, entries++) {
        if (*entries == 0) {
            return -1;
        }
        if (*entries >= 5) {
            *entries = 4;
        }
        total += D_800EBADC_minigame[*entries];
    }
    for (rank = 0; rank < 4; rank++) {
        if (total < D_800EBAEC_minigame[rank]) {
            break;
        }
    }
    return rank;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E9170_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E989C_minigame);
