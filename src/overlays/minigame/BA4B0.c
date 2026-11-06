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

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} BA4B0_Pos; // Size 0x4

typedef struct {
    /* 0x00 */ BA4B0_Pos pos;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
} BA4B0_Elem; // Size 0xC

typedef struct {
    /* 0x000 */ BA4B0_ProcessData *data;
    /* 0x004 */ BA4B0_Elem elems[23];
    /* 0x118 */ s16 unk118;
    /* 0x11A */ char unk11A[0x8];
    /* 0x122 */ s16 window;
    /* 0x124 */ char unk124[0xA];
    /* 0x12E */ s16 unk12E;
    /* 0x130 */ s16 unk130;
    /* 0x132 */ s16 group;
    /* 0x134 */ s16 graphics[4];
    /* 0x13C */ s16 unk13C;
    /* 0x13E */ s16 unk13E;
    /* 0x140 */ s16 unk140;
    /* 0x142 */ char unk142[0x2];
} BA4B0_Work; // Size 0x144

extern BA4B0_Pos D_800EBAA0_minigame[];
extern u8 D_800EBACC_minigame[];
extern u8 D_800EBAD4_minigame[];
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

s16 func_800E7A2C_minigame(u8 *values, s16 alt, s16 start, s16 end, BA4B0_Elem *elemsA, BA4B0_Elem *elemsB,
                           BA4B0_Work *work) {
    u8 *order;
    s16 group;
    s16 *graphics;
    s16 baseX;
    s16 baseY;
    s16 result;
    s16 value;
    s16 graphic;
    s16 x;
    s16 y;
    s32 i;

    order = (alt != 0) ? D_800EBAD4_minigame : D_800EBACC_minigame;
    group = work->group;
    graphics = work->graphics;
    baseX = work->data->x;
    baseY = work->data->y;
    result = -1;
    for (i = start; i < end; i++, order++, elemsB++, elemsA++) {
        value = values[*order] - 1;
        if (value < 0) {
            result = i;
            break;
        }
        elemsA->unk08 = 1;
        elemsA->unk0A = 1;
        graphic = graphics[value];
        elemsB->pos = D_800EBAA0_minigame[i];
        x = baseX + elemsB->pos.x;
        y = baseY + elemsB->pos.y;
        func_800E7930_minigame(group, i + 16, graphic, 1200, x, y);
        elemsB->unk08 = 1;
        elemsB->unk0A = 1;
    }
    return result;
}

#ifdef NON_MATCHING
// Regalloc: the per-rank count is zero-extended with andi instead of a plain move.
s16 func_800E7BCC_minigame(BA4B0_Work *work) {
    u8 counts[4];
    u8 *entries;
    u8 last;
    s16 group;
    s16 x;
    s16 y;
    s16 curX;
    s16 member;
    s16 rank;
    u8 count;
    s32 i;

    for (i = 0; i < 4; i++) {
        counts[i] = 0;
    }
    if (work->unk118 < 0) {
        last = GwStory.progress.fields.unkF;
        entries = GwStory.progress.fields.unk3;
    } else {
        last = GwStory.unk58[work->unk118];
        entries = GwStory.unk10[work->unk118];
    }
    if (last != 0) {
        counts[last - 1]++;
    }
    for (i = 0; i < 12; i++, entries++) {
        if (*entries != 0) {
            counts[*entries - 1]++;
        }
    }
    y = work->data->y - 8;
    x = work->data->x - 54;
    member = 0;
    group = work->unk13C;
    for (rank = 3; rank >= 0; rank--, y += 14) {
        curX = x;
        count = counts[rank];
        for (i = 0; i < count; i++, curX += 12) {
            HuSprPosSet(group, member, curX, y);
            HuSprTPLvlSet(group, member, 0);
            HuSprDispOn(group, member);
            member++;
        }
    }
    for (rank = member; rank < 13; rank++) {
        HuSprDispOff(group, rank);
    }
    work->unk130 = 1;
    work->unk140 = 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7BCC_minigame);
#endif

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
