#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/saveload.h"
#include "overlays/minigame.h"
#include "../ovl_81_name/ovl_81.h"
#include "game/esprite.h"
#include "game/pad.h"
#include "storyresult.h"

// 0xC byte data allocated by func_8010A4A4_storyresult and stored in the
// `user_data` pointer of the process it spawns.
typedef struct StoryResultWork {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 state;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} StoryResultWork; // sizeof 0xC

typedef struct StoryResultPos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} StoryResultPos; // sizeof 0x4

typedef struct StoryResultElem {
    /* 0x00 */ StoryResultPos pos;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
} StoryResultElem; // sizeof 0xC

// Panel state allocated by func_80108F0C_storyresult.
typedef struct StoryResultPanel {
    /* 0x000 */ StoryResultWork *data;
    /* 0x004 */ StoryResultElem elems[24];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ s16 windows[6];
    /* 0x132 */ s16 winFlags[6];
    /* 0x13E */ s16 group;
    /* 0x140 */ s16 graphics[4];
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ char unk14E[0x2];
} StoryResultPanel; // sizeof 0x150

void func_80107920_storyresult(void);
Process *func_8010832C_storyresult(s16 *arg0, s16 arg1);
void func_80108F0C_storyresult(void);
s16 func_8010A370_storyresult(s16 arg0);
s16 func_8010A5C4_storyresult(s16 playerIdx);
s16 func_8010A738_storyresult(s16 playerIdx);
s16 func_8010A7B0_storyresult(s16 playerIdx);
extern StoryResultPos D_8010AB34_storyresult[];
extern u32 D_8010AB50_storyresult[];
extern u8 D_8010AB6C_storyresult[];
extern u8 D_8010AB74_storyresult[];
extern u8 D_8010AB7C_storyresult[];
extern u8 D_8010AB84_storyresult[];
extern u8 D_8010AB8C_storyresult[];
extern u8 D_8010AB90_storyresult[];
extern MsetupCameraPreset D_8010AB9C_storyresult;
extern s16 D_800EBAF0_minigame;

s16 func_80106FF0_storyresult(void) {
    s16 count = GwStory.unk73 != 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(GwStory.unk67); i++) {
        if (GwStory.unk67[i] != 0) {
            count++;
        }
    }
    return count;
}

void func_80107030_storyresult(void) {
    s32 i;

    GwStory.unk64 = GwStory.unk0;
    GwStory.unk65 = GwStory.unk1;
    GwStory.unk66 = GwStory.unk2;
    GwStory.unk73 = GwStory.progress.fields.unkF;
    for (i = 0; i < ARRAY_COUNT(GwStory.unk67); i++) {
        GwStory.unk67[i] = GwStory.progress.fields.unk3[i];
    }
    _ClearFlag(0x28);
    _SetFlag(0x18);
    if (_CheckFlag(0x20)) {
        _SetFlag(0x29);
    } else {
        _ClearFlag(0x29);
    }
    func_80050614_main(1);
}

s16 func_801070D8_storyresult(void) {
    s16 idx = GwStory.unk1;
    s16 count = GwStory.unk58[idx] != 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(GwStory.unk10[0]); i++) {
        if (GwStory.unk10[idx][i] != 0) {
            count++;
        }
    }
    return count;
}

void func_80107140_storyresult(void) {
    s16 idx = GwStory.unk1;
    s32 i;

    GwStory.unk58[idx] = GwStory.progress.fields.unkF;
    for (i = 0; i < ARRAY_COUNT(GwStory.unk10[0]); i++) {
        GwStory.unk10[idx][i] = GwStory.progress.fields.unk3[i];
    }
    GwStory.unk5E[idx] = GwStory.unk2;
    _ClearFlag(0x28);
    if (_CheckFlag(0x20)) {
        _SetFlag(0x29);
    } else {
        _ClearFlag(0x29);
    }
    func_80050614_main(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107204_storyresult);

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80107920_storyresult);

Process *func_8010818C_storyresult(s16 *arg0, s16 arg1) {
    Process *prc;
    s32 rank = func_8010A370_storyresult(arg1);

    if (rank < 0) {
        *arg0 = -1;
        return NULL;
    }
    if (rank >= 4) {
        _SetFlag(0x1D);
    }
    _SetFlag(0x1E);
    *arg0 = arg1;
    D_800EBAF0_minigame = D_8010ABE0_storyresult;
    prc = omAddPrcObj(func_80107920_storyresult, 0x4000, 0x800, 0);
    prc->user_data = arg0;
    return prc;
}

void func_8010822C_storyresult(void) {
    s16 sp10;

    D_800CD280_main = 0;
    func_801060D0_storyresult(&D_8010AB9C_storyresult);
    D_8010A912_storyresult = 1;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_8010AC2A_storyresult = 0xB;
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8010818C_storyresult(&sp10, -1);
    while (sp10 >= -1) {
        HuPrcVSleep();
    }
    D_8010AC2A_storyresult = 0xB;
    D_8010AC28_storyresult = 0x36;
    D_8010A914_storyresult = 2;
    D_8010A910_storyresult = 1;

    while (1) {
        HuPrcVSleep();
    }
}

Process *func_8010832C_storyresult(s16 *arg0, s16 arg1) {
    Process *prc;

    if (func_800E905C_minigame(arg1) < 0) {
        *arg0 = -1;
        return NULL;
    }
    *arg0 = arg1;
    D_800EBAF0_minigame = 0;
    prc = omAddPrcObj(func_800E9170_minigame, 0x4000, 0x800, 0);
    prc->user_data = arg0;
    return prc;
}

#ifdef NON_MATCHING
// Regalloc: loop counters and the cycling value are assigned different registers.
void func_801083A4_storyresult(void) {
    s16 status;
    u16 sprite;
    s16 value;
    s16 buttons;
    s32 i;
    s32 j;

    D_800CD280_main = 0;
    func_801060D0_storyresult(&D_8010AB9C_storyresult);
    sprite = espEntry(func_8000B838_main(0x140067), 0, 0);
    espAttrSet(sprite, 0x4000);
    espPosSet(sprite, 160, 120);
    WipeCreateIn(D_8010AC2A_storyresult, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    for (i = 0, value = 4; i < ARRAY_COUNT(GwStory.progress.fields.unk3); i++) {
        GwStory.progress.fields.unk3[i] = 4;
        value++;
        if (value >= 5) {
            value = 1;
        }
    }
    GwStory.progress.fields.unkF = 4;
    GwStory.unk2 = 3;
    GwStory.unk66 = 1;
    GwStory.unk73 = 0;
    GwStory.unk65 = 4;
    GwStory.unk64 = 4;
    for (i = 0, value = 4; i < ARRAY_COUNT(GwStory.unk67); i++) {
        if (i >= GwStory.unk64) {
            value = 0;
        }
        GwStory.unk67[i] = value;
        value++;
        if (value >= 5) {
            value = 1;
        }
    }
    for (i = 0; i < ARRAY_COUNT(GwStory.unk58); i++) {
        GwStory.unk5E[i] = i & 3;
        GwStory.unk58[i] = 4;
        for (j = 0; j < ARRAY_COUNT(GwStory.unk10[i]); j++) {
            GwStory.unk10[i][j] = 4;
        }
    }
    buttons = (D_800CDA7C_main[0] & 4) != 0;
    if (D_800CDA7C_main[0] & 1) {
        buttons |= 2;
    }
    if (D_800CDA7C_main[0] & 8) {
        buttons |= 4;
    }
    func_8010832C_storyresult(&status, buttons);
    while (status >= 0) {
        HuPrcVSleep();
    }
    D_8010A910_storyresult = 1;
    while (1) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_801083A4_storyresult);
#endif

void func_801085E8_storyresult(s16 group, s16 member, s16 graphic, s16 prio, s16 x, s16 y) {
    HuSprTPLvlSet(group, member, 256);
    HuSprAttrReset(group, member, 0xFFFF);
    HuSprAttrSet(group, member, 0x9000);
    HuSprScaleSet(group, member, 1.0f, 1.0f);
    func_800550F4_main(group, member, 0);
    HuSprGrpMemberSet(group, member, graphic, 0);
    HuSprPriSet(group, member, prio);
    HuSprPosSet(group, member, x, y);
}

s16 func_801086E4_storyresult(u8 *values, s16 alt, s16 start, s16 end, StoryResultElem *elemsA,
                              StoryResultElem *elemsB, StoryResultPanel *work) {
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

    order = (alt != 0) ? D_8010AB74_storyresult : D_8010AB6C_storyresult;
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
        elemsB->pos = D_8010AB34_storyresult[i];
        x = baseX + elemsB->pos.x;
        y = baseY + elemsB->pos.y;
        func_801085E8_storyresult(group, i + 16, graphic, 1200, x, y);
        elemsB->unk08 = 1;
        elemsB->unk0A = 1;
    }
    return result;
}

s16 func_80108884_storyresult(StoryResultPanel *work) {
    u8 counts[4];
    u8 *entries;
    u8 last;
    s16 group;
    s16 x;
    s16 y;
    s16 curX;
    s16 member;
    s16 rank;
    s16 count;
    s32 i;

    for (i = 0; i < 4; i++) {
        counts[i] = 0;
    }
    if (work->unk124 < 0) {
        last = GwStory.progress.fields.unkF;
        entries = GwStory.progress.fields.unk3;
    } else {
        last = GwStory.unk58[work->unk124];
        entries = GwStory.unk10[work->unk124];
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
    group = work->unk148;
    for (rank = 3; rank >= 0; rank--, y += 14) {
        curX = x;
        count = counts[rank];
        for (i = 0; i < count; i++, curX += 12) {
            HuSprPosSet(group, member, curX, y);
            HuSprTPLvlSet(group, member, 0);
            HuSprAttrReset(group, member, 0x8000);
            member++;
        }
    }
    for (rank = member; rank < 13; rank++) {
        HuSprAttrSet(group, rank, 0x8000);
    }
    work->winFlags[5] = 1;
    work->unk14C = 1;
    return 0;
}

s16 func_80108AC0_storyresult(StoryResultPanel *work, u8 last, u8 *entries) {
    u8 counts[4];
    s16 group;
    s16 x;
    s16 y;
    s16 curX;
    s16 member;
    s16 rank;
    s16 count;
    s32 i;

    for (i = 0; i < 4; i++) {
        counts[i] = 0;
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
    group = work->unk148;
    for (rank = 3; rank >= 0; rank--, y += 14) {
        curX = x;
        count = counts[rank];
        for (i = 0; i < count; i++, curX += 12) {
            HuSprPosSet(group, member, curX, y);
            HuSprTPLvlSet(group, member, 0);
            HuSprAttrReset(group, member, 0x8000);
            member++;
        }
    }
    for (rank = member; rank < 13; rank++) {
        HuSprAttrSet(group, rank, 0x8000);
    }
    work->winFlags[5] = 1;
    work->unk14C = 1;
    return 0;
}

s16 func_80108CB8_storyresult(StoryResultPanel *work) {
    return func_80108AC0_storyresult(work, GwStory.unk58[GwStory.unk1], GwStory.unk10[GwStory.unk1]);
}

s16 func_80108D04_storyresult(StoryResultPanel *work) {
    return func_80108AC0_storyresult(work, GwStory.unk73, GwStory.unk67);
}

s16 func_80108D34_storyresult(s16 page, StoryResultPanel *work) {
    u8 *values;
    StoryResultElem *elems;
    StoryResultElem *elemsB;
    s16 alt;
    s16 result = -1;

    HuWinHomeClear(work->windows[4]);
    HuWinMesSet(work->windows[4], D_8010AB50_storyresult[page], -2, -1);
    work->winFlags[4] = 1;
    if (page < 2) {
        alt = 0;
        elems = &work->elems[2];
        if (page == 1) {
            alt = 1;
            elems = &work->elems[8];
        }
        if (work->unk124 < 0) {
            values = GwStory.progress.fields.unk3;
        } else {
            values = GwStory.unk10[work->unk124];
        }
        elemsB = &work->elems[16];
        result = func_801086E4_storyresult(values, alt, 0, 6, elems, elemsB, work);
    } else if (page == 2) {
        if (work->unk124 < 0) {
            values = &GwStory.progress.fields.unkF;
        } else {
            values = &GwStory.unk58[work->unk124];
        }
        elems = &work->elems[14];
        elemsB = &work->elems[22];
        result = func_801086E4_storyresult(values, 0, 6, 7, elems, elemsB, work);
    } else if (page == 3) {
        result = func_80108884_storyresult(work);
    } else if (page == 4) {
        result = func_80108CB8_storyresult(work);
    } else if (page == 5) {
        result = func_80108884_storyresult(work);
    } else if (page == 6) {
        result = func_80108D04_storyresult(work);
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_80108F0C_storyresult);

s16 func_8010A370_storyresult(s16 arg0) {
    u8 *last;
    u8 *entries;
    s16 total;
    s16 rank;
    s32 i;

    if (arg0 >= 6) {
        return -1;
    }
    if (arg0 < 0) {
        if (arg0 == -2) {
            last = &GwStory.unk73;
            entries = GwStory.unk67;
        } else {
            last = &GwStory.progress.fields.unkF;
            entries = GwStory.progress.fields.unk3;
        }
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
    total = D_8010AB84_storyresult[*last];
    for (i = 0; i < 12; i++, entries++) {
        if (*entries == 0) {
            return -1;
        }
        if (*entries >= 5) {
            *entries = 4;
        }
        total += D_8010AB7C_storyresult[*entries];
    }
    for (rank = 0; rank < 4; rank++) {
        if (total < D_8010AB8C_storyresult[rank]) {
            break;
        }
    }
    return rank;
}

Process *func_8010A4A4_storyresult(u16 arg0, s16 arg1) {
    StoryResultWork *data;
    Process *prc;

    if (arg0 == 0 || arg0 == 1) {
        if (func_8010A370_storyresult(arg1) < 0) {
            return NULL;
        }
    }
    data = HuMemAllocTag(sizeof(StoryResultWork), 0x7918);
    memset(data, 0, sizeof(StoryResultWork));
    data->x = 160;
    data->y = 120;
    data->unk_00 = arg0;
    data->unk_02 = arg1;
    prc = omAddPrcObj(func_80108F0C_storyresult, 0x4000, 0x1000, 0);
    prc->user_data = data;
    return prc;
}

s32 func_8010A558_storyresult(Process *prc) {
    StoryResultWork *work;
    s32 result;

    if (prc == NULL) {
        return 0;
    }
    work = prc->user_data;
    work->state = 0xFF;
    do {
        HuPrcVSleep();
    } while (work->state != 0);
    result = omDelPrcObj(prc);
    HuMemFree(work);
    return result;
}

#ifdef NON_MATCHING
// Regalloc: the star difference is allocated to v1 instead of a0.
s16 func_8010A5C4_storyresult(s16 playerIdx) {
    s16 stars = GwPlayer[playerIdx].star;
    s16 maxStars = 0;
    s16 coins;
    s16 maxCoins;
    s32 diff;
    s16 result;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == playerIdx) {
            continue;
        }
        if (maxStars < GwPlayer[i].star) {
            maxStars = GwPlayer[i].star;
        }
    }
    diff = stars - maxStars;
    if (diff >= 2) {
        result = 4;
    } else if (diff == 1) {
        result = 3;
    } else {
        coins = GwPlayer[playerIdx].coin;
        maxCoins = 0;
        for (i = 0; i < 4; i++) {
            if (i == playerIdx) {
                continue;
            }
            if (GwPlayer[i].star < stars) {
                continue;
            }
            if (maxCoins < GwPlayer[i].coin) {
                maxCoins = GwPlayer[i].coin;
            }
        }
        if (coins > maxCoins) {
            result = 2;
        } else {
            result = 1;
        }
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A5C4_storyresult);
#endif

#ifdef NON_MATCHING
// Scheduling: target computes both GwPlayer offsets before the first load.
s16 func_8010A738_storyresult(s16 playerIdx) {
    s32 other = playerIdx == 0;
    s32 diff = GwPlayer[playerIdx].star - GwPlayer[other].star;
    s16 result;

    if (diff >= 3) {
        result = 4;
    } else if (diff == 2) {
        result = 3;
    } else if (diff == 1) {
        result = 2;
    } else {
        result = 1;
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/storyresult/54F360", func_8010A738_storyresult);
#endif

s16 func_8010A7B0_storyresult(s16 playerIdx) {
    s16 bonusCoin = GwPlayer[playerIdx].bonusCoin;
    s16 value = 0;

    if (bonusCoin >= 0) {
        value = D_8010AB90_storyresult[bonusCoin];
    }
    return value;
}

s16 func_8010A7EC_storyresult(void) {
    s16 mode = D_8010A924_storyresult[GwStory.unk0];
    s16 count = (mode != 0) ? 2 : 4;
    s16 chr = GwStory.unk1;
    s16 result;
    s16 i;

    for (i = 0; i < count; i++) {
        if (GwPlayer[i].chr == chr) {
            break;
        }
    }
    if (i >= count) {
        return 0;
    }
    result = 0;
    switch (mode) {
        case 0:
            result = func_8010A5C4_storyresult(i);
            break;
        case 1:
            result = func_8010A738_storyresult(i);
            break;
        case 2:
            result = func_8010A7B0_storyresult(i);
            break;
    }
    return result;
}
