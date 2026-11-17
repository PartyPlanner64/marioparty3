#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} MgStoryStatParam; // Size 0xC

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} MgStoryStatPos; // Size 0x4

typedef struct {
    /* 0x00 */ MgStoryStatPos pos;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
} MgStoryStatElem; // Size 0xC

typedef struct {
    /* 0x00 */ s32 file;
    /* 0x04 */ MgStoryStatPos pos;
} MgStoryStatSprDef; // Size 0x8

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} MgStoryStatWinDef; // Size 0x8

typedef struct {
    /* 0x000 */ MgStoryStatParam *data;
    /* 0x004 */ MgStoryStatElem elems[23];
    /* 0x118 */ s16 unk118;
    /* 0x11A */ s16 windows[6];
    /* 0x126 */ s16 winFlags[6];
    /* 0x132 */ s16 group;
    /* 0x134 */ s16 graphics[4];
    /* 0x13C */ s16 unk13C;
    /* 0x13E */ s16 unk13E;
    /* 0x140 */ s16 unk140;
    /* 0x142 */ char unk142[0x2];
} MgStoryStatWork; // Size 0x144

MgStoryStatSprDef mgStoryStatSprTbl[15] = {
    { 0x00150000, { 0, -75 } },
    { 0x00150002, { 0, 8 } },
    { 0x00150011, { -86, -22 } },
    { 0x00150012, { 0, -22 } },
    { 0x00150013, { 86, -22 } },
    { 0x00150014, { -86, 24 } },
    { 0x00150015, { 0, 24 } },
    { 0x00150016, { 86, 24 } },
    { 0x00150017, { -86, -22 } },
    { 0x00150018, { 0, -22 } },
    { 0x00150019, { 86, -22 } },
    { 0x0015001A, { -86, 24 } },
    { 0x0015001B, { 0, 24 } },
    { 0x0015001C, { 86, 24 } },
    { 0x0015001E, { 0, 1 } },
};

s32 mgStoryResultSprTbl[] = {
    0x0015000D, 0x0015000C, 0x0015000B, 0x0015000A, 0x0015000A, 0x0015000A, 0x0015000A,
};

s32 mgStoryCharSprTbl[] = {
    0x00150004, 0x00150005, 0x00150006, 0x00150007, 0x00150008, 0x00150009,
};

u32 mgStoryCharMesTbl[] = {
    0x1C00, 0x1C01, 0x1C02, 0x1C03, 0x1C04, 0x1C05,
};

u32 mgStoryLevelMesTbl[] = {
    0x6102, 0x6103, 0x6104, 0x6105,
};

u32 mgStoryRankMesTbl[] = {
    0x6112, 0x6113, 0x6116, 0x6117, 0x6118, 0x6118, 0x6118,
};

u8 mgStoryRankBlinkTbl[] = {
    0xFF, 0x50, 0x50, 0x50, 0xFF, 0x50, 0xFF, 0xFF, 0x50,
};

u8 mgStoryRankBlinkAltTbl[] = {
    0xFF, 0x50, 0x50, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
};

u8 mgStoryRankColorTbl[][3] = {
    { 0x8C, 0x87, 0x87 }, { 0x7B, 0x2A, 0xBF }, { 0xF0, 0xD9, 0x12 }, { 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF },
};

MgStoryStatWinDef mgStoryStatWinTbl[6] = {
    { -72, -98, 80, 48 },  { 6, -98, 112, 20 },  { 6, -84, 112, 20 },
    { 6, -70, 112, 20 },   { -120, -50, 240, 20 }, { -104, -18, 112, 105 },
};

MgStoryStatPos mgStoryResultPosTbl[] = {
    { -86, -3 }, { 0, -3 }, { 86, -3 }, { -86, 43 }, { 0, 43 }, { 86, 43 }, { 0, 20 },
};

u32 mgStoryPageMesTbl[] = {
    0x6106, 0x6107, 0x6108, 0x6109,
};

u8 mgStoryResultOrderTbl[] = { 0, 2, 4, 6, 8, 11 };
u8 mgStoryResultOrderAltTbl[] = { 1, 3, 5, 7, 9, 10 };
u8 mgStoryResultScoreTbl[] = { 0, 0, 1, 2, 3 };
u8 mgStoryBossScoreTbl[] = { 0, 0, 1, 2, 3 };
u8 mgStoryRankBorderTbl[] = { 13, 26, 30, 34 };
s16 mgStoryStatPortNo = 0;
u8 mgStoryPageTbl[] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 2 };

extern s16 winPrio;

s16 MgStoryStatRankMarkDisp(MgStoryStatWork *work);

void MgStoryStatSprSet(s16 group, s16 member, s16 graphic, s16 prio, s16 x, s16 y) {
    HuSprTPLvlSet(group, member, 256);
    HuSprAttrReset(group, member, 0xFFFF);
    HuSprAttrSet(group, member, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
    HuSprScaleSet(group, member, 1.0f, 1.0f);
    HuSprAnimModeSet(group, member, HUSPR_ANIM_MODE_STOP);
    HuSprGrpMemberSet(group, member, graphic, 0);
    HuSprPriSet(group, member, prio);
    HuSprPosSet(group, member, x, y);
}

s16 MgStoryStatResultDisp(u8 *values, s16 alt, s16 start, s16 end, MgStoryStatElem *elemsA, MgStoryStatElem *elemsB,
                           MgStoryStatWork *work) {
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

    order = (alt != 0) ? mgStoryResultOrderAltTbl : mgStoryResultOrderTbl;
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
        elemsB->pos = mgStoryResultPosTbl[i];
        x = baseX + elemsB->pos.x;
        y = baseY + elemsB->pos.y;
        MgStoryStatSprSet(group, i + 16, graphic, 1200, x, y);
        elemsB->unk08 = 1;
        elemsB->unk0A = 1;
    }
    return result;
}

s16 MgStoryStatRankMarkDisp(MgStoryStatWork *work) {
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
    work->winFlags[5] = 1;
    work->unk140 = 1;
    return 0;
}

s16 MgStoryStatPageSet(s16 page, MgStoryStatWork *work) {
    u8 *values;
    MgStoryStatElem *elems;
    MgStoryStatElem *elemsB;
    s16 alt;

    HuWinHomeClear(work->windows[4]);
    HuWinMesSet(work->windows[4], mgStoryPageMesTbl[page], -2, -1);
    work->winFlags[4] = 1;
    if (page < 2) {
        alt = 0;
        elems = &work->elems[2];
        if (page == 1) {
            alt = 1;
            elems = &work->elems[8];
        }
        if (work->unk118 < 0) {
            values = GwStory.progress.fields.unk3;
        } else {
            values = GwStory.unk10[work->unk118];
        }
        elemsB = &work->elems[16];
        return MgStoryStatResultDisp(values, alt, 0, 6, elems, elemsB, work);
    } else if (page == 2) {
        if (work->unk118 < 0) {
            values = &GwStory.progress.fields.unkF;
        } else {
            values = &GwStory.unk58[work->unk118];
        }
        elems = &work->elems[14];
        elemsB = &work->elems[22];
        return MgStoryStatResultDisp(values, 0, 6, 7, elems, elemsB, work);
    } else {
        return MgStoryStatRankMarkDisp(work);
    }
}

void MgStoryStatExec(void) {
    s16 color[3];
    s16 step[3];
    u32 msgs[4];
    MgStoryStatParam *data;
    s16 *rankWin;
    MgStoryStatWork *work;
    MgStoryStatElem *elem;
    MgStoryStatSprDef *def;
    s16 *win;
    s16 *flag;
    s16 *gfx;
    u8 *colorStart;
    u8 *colorPtr;
    u16 group;
    s16 state;
    s16 shown;
    s16 fadeInWait;
    s16 sprFadeSpeed;
    s16 sprAlpha;
    s16 winFadeSpeed;
    s16 winAlpha;
    s16 hasRank;
    s16 colorFrames;
    s16 colorTimer;
    s16 colorCycle;
    s16 page;
    s16 prevPage;
    s16 pageChanging;
    s16 rank;
    s16 graphic;
    s16 x;
    s16 y;
    s16 member;
    s32 prio;
    s16 markX;
    s32 done;
    s32 i;

    data = HuPrcCurrentGet()->user_data;
    work = HuMemAllocTag(sizeof(MgStoryStatWork), 0x7918);
    memset(work, 0, sizeof(MgStoryStatWork));
    work->data = data;
    page = 0;
    prevPage = 0;
    for (elem = work->elems, i = 0; i < 23; i++, elem++) {
        elem->unk04 = -1;
        elem->unk06 = 256;
        elem->unk08 = 0;
        elem->unk0A = 0;
    }
    work->unk13E = -1;
    work->unk13C = -1;
    hasRank = 0;
    rank = -1;
    switch (data->unk00) {
        case 0:
        default:
            hasRank = 1;
            rank = MgStoryRankGet(data->unk02);
            msgs[0] = 0x6101;
            msgs[2] = mgStoryLevelMesTbl[GwStory.unk5E[data->unk02]];
            msgs[3] = mgStoryRankMesTbl[rank];
            work->unk118 = data->unk02;
            break;
        case 1:
            data->unk02 = GwStory.unk1;
            hasRank = 1;
            rank = MgStoryRankGet(-1);
            msgs[0] = 0x6101;
            msgs[2] = mgStoryLevelMesTbl[GwStory.unk2];
            msgs[3] = mgStoryRankMesTbl[rank];
            work->unk118 = -1;
            break;
        case 2:
            data->unk02 = GwStory.unk1;
            msgs[0] = 0x6100;
            msgs[2] = mgStoryLevelMesTbl[GwStory.unk2];
            work->unk118 = -1;
            if (GwStory.unk0 == 12) {
                hasRank = 1;
                rank = MgStoryRankGet(-1);
                page = 2;
                prevPage = 2;
                msgs[3] = mgStoryRankMesTbl[rank];
            } else {
                prevPage = page = mgStoryPageTbl[GwStory.unk0];
            }
            break;
    }
    msgs[1] = mgStoryCharMesTbl[data->unk02];

    group = HuSprGrpCreate(23, 0);
    member = 0;
    def = mgStoryStatSprTbl;
    for (elem = work->elems, i = 0; i < ARRAY_COUNTU(mgStoryStatSprTbl);
         i++, member++, def++, elem++) {
        prio = 1200;
        graphic = HuSprAnimDataRead(def->file);
        elem->unk04 = graphic;
        elem->pos = def->pos;
        x = elem->pos.x + data->x;
        y = elem->pos.y + data->y;
        if (i >= 2) {
            prio = 1199;
        }
        MgStoryStatSprSet(group, member, graphic, prio, x, y);
    }
    HuSprScaleSet(group, 1, 1.0f, 1.02f);
    HuSprColorSet(group, 1, 0, 0, 0);
    HuSprTPLvlSet(group, 1, 255);
    work->elems[1].unk06 = 255;
    work->group = group;

    graphic = HuSprAnimDataRead(mgStoryCharSprTbl[data->unk02]);
    work->elems[15].unk04 = graphic;
    work->elems[15].pos.x = -96;
    work->elems[15].pos.y = -74;
    x = work->elems[15].pos.x + data->x;
    y = work->elems[15].pos.y + data->y;
    MgStoryStatSprSet(group, 15, graphic, 1200, x, y);
    for (gfx = work->graphics, i = 0; i < 4; i++, gfx++) {
        *gfx = HuSprAnimDataRead(mgStoryResultSprTbl[i]);
    }
    work->unk13C = HuSprGrpCreate(13, 0);
    work->unk13E = HuSprAnimDataRead(0x15001D);
    y = data->y - 28;
    for (i = 0; i < 13; i++) {
        markX = data->x + (s16)(i * 12 - 24);
        MgStoryStatSprSet(work->unk13C, i, work->unk13E, 1200, markX, y);
    }

    winPrio = 400;
    win = work->windows;
    flag = work->winFlags;
    x = data->x;
    y = data->y;
    for (i = 0; i < ARRAY_COUNTU(work->windows); i++, win++, flag++) {
        *win = HuWinCreate(x + mgStoryStatWinTbl[i].x, y + mgStoryStatWinTbl[i].y, mgStoryStatWinTbl[i].w,
                           mgStoryStatWinTbl[i].h, 0, 12);
        HuWinMesSpeedSet(*win, 0);
        HuWinBGTPLvlSet(*win, 0);
        HuWinMesPalSet(*win, 2, 255, 0, 0);
        HuWinMesPalSet(*win, 4, 0, 144, 0);
        HuWinMesPalSet(*win, 5, 0, 176, 192);
        HuWinMesPalSet(*win, 6, 255, 173, 0);
        HuWinMesDefColSet(*win, 64, 64, 64);
        HuWinBGColSet(*win, 0, 0, 0);
        HuWinMesColSet(*win, 7);
        HuWinTPLvlSet(*win, 0);
        *flag = 0;
    }
    win = work->windows;
    HuWinMesSet(win[0], msgs[0], -1, -1);
    HuWinMesSet(win[1], msgs[1], -1, -1);
    HuWinMesSet(win[2], msgs[2], -1, -1);
    work->winFlags[0] = work->winFlags[1] = work->winFlags[2] = 1;
    if (hasRank) {
        HuWinMesSet(win[3], msgs[3], -1, -1);
        work->winFlags[3] = 1;
        HuWinMesPalSet(win[3], 7, mgStoryRankColorTbl[rank][0], mgStoryRankColorTbl[rank][1],
                       mgStoryRankColorTbl[rank][2]);
    }
    HuWinMesSet(win[5], 0x6111, -1, -1);
    MgStoryStatPageSet(page, work);

    state = 0;
    work->unk140 = 0;
    shown = 0;
    fadeInWait = 0;
    pageChanging = 0;
    sprFadeSpeed = 0;
    sprAlpha = 0;
    winFadeSpeed = 0;
    winAlpha = 0;
    colorCycle = 0;
    colorTimer = 0;
    colorFrames = 0;
    rankWin = &work->windows[3];
    do {
        if ((state == 1 || state == 2) && work->winFlags[0] == 0) {
            data->unk04 = 0;
        }
        if (fadeInWait) {
            if (sprFadeSpeed == 0 && winFadeSpeed == 0) {
                fadeInWait = 0;
                data->unk04 = 0;
            }
        }
        if (pageChanging) {
            if (sprFadeSpeed == 0 && winFadeSpeed == 0) {
                pageChanging = 0;
                MgStoryStatPageSet(page, work);
                sprAlpha = 0;
                sprFadeSpeed = 51;
                winAlpha = 0;
                winFadeSpeed = 51;
                fadeInWait = 1;
            }
        } else if (prevPage != page) {
            sprAlpha = 255;
            sprFadeSpeed = -51;
            winAlpha = 255;
            winFadeSpeed = -51;
            work->winFlags[4] = 1;
            if (prevPage == 3) {
                work->winFlags[5] = 1;
                work->unk140 = 1;
            }
            for (elem = work->elems, i = 0; i < 23; i++, elem++) {
                if (elem->unk0A > 0) {
                    elem->unk0A = 0;
                    elem->unk08 = 1;
                }
            }
            prevPage = page;
            pageChanging = 1;
        }
        if (state != data->unk04) {
            elem = work->elems;
            switch (data->unk04) {
                case 0:
                    break;
                case 1:
                    if (!shown) {
                        shown = 1;
                        sprAlpha = 0;
                        sprFadeSpeed = 36;
                        winAlpha = 0;
                        winFadeSpeed = 36;
                        elem[0].unk08 = 1;
                        elem[1].unk08 = 1;
                        elem[15].unk08 = 1;
                        if (rank == 4) {
                            colorCycle = 1;
                            colorPtr = colorStart = mgStoryRankBlinkTbl;
                            colorFrames = 6;
                        } else if (rank == 3) {
                            colorCycle = 1;
                            colorPtr = colorStart = mgStoryRankBlinkAltTbl;
                            colorFrames = 8;
                        }
                    }
                    break;
                case 2:
                    if (shown) {
                        shown = 0;
                        sprAlpha = 255;
                        sprFadeSpeed = -36;
                        winAlpha = 255;
                        winFadeSpeed = -36;
                        elem[0].unk08 = 1;
                        elem[1].unk08 = 1;
                        elem[15].unk08 = 1;
                        for (flag = work->winFlags, i = 0; i < 5; i++, flag++) {
                            *flag = 1;
                        }
                        if (prevPage == 3) {
                            work->winFlags[5] = 1;
                            work->unk140 = 1;
                        }
                        for (elem = work->elems, i = 0; i < 23; i++, elem++) {
                            if (elem->unk0A > 0) {
                                elem->unk0A = 0;
                                elem->unk08 = 1;
                            }
                        }
                    }
                    break;
                case 3:
                    page++;
                    if (page >= 4) {
                        page = 0;
                    }
                    break;
                case 4:
                    page--;
                    if (page < 0) {
                        page = 3;
                    }
                    break;
                case 255:
                    break;
            }
            state = data->unk04;
        }
        if (colorCycle) {
            if (colorTimer != 0) {
                colorTimer--;
                color[0] -= step[0];
                color[1] -= step[1];
                color[2] -= step[2];
                HuWinMesPalSet(*rankWin, 7, color[0], color[1], color[2]);
            } else {
                color[0] = colorPtr[0];
                color[1] = colorPtr[1];
                color[2] = colorPtr[2];
                HuWinMesPalSet(*rankWin, 7, color[0], color[1], color[2]);
                colorPtr += 3;
                if (colorPtr[0] == 0 && colorPtr[1] == 0 && colorPtr[2] == 0) {
                    colorPtr = colorStart;
                }
                step[0] = (color[0] - colorPtr[0]) / colorFrames;
                step[1] = (color[1] - colorPtr[1]) / colorFrames;
                step[2] = (color[2] - colorPtr[2]) / colorFrames;
                colorTimer = colorFrames - 1;
            }
        }
        if (sprFadeSpeed != 0) {
            done = 0;
            sprAlpha += sprFadeSpeed;
            if (sprAlpha >= 255) {
                sprFadeSpeed = 0;
                sprAlpha = 255;
                done = 1;
            } else if (sprAlpha <= 0) {
                sprFadeSpeed = 0;
                sprAlpha = 0;
                done = 1;
            }
            for (elem = work->elems, i = 0; i < 23; i++, elem++) {
                if (elem->unk08 > 0) {
                    if (elem->unk08 == 1) {
                        elem->unk08 = 2;
                        HuSprDispOn(group, i);
                    }
                    if ((s16)done) {
                        elem->unk08 = 0;
                    }
                    if (sprAlpha == 0) {
                        HuSprDispOff(group, i);
                    }
                    if (sprAlpha >= elem->unk06) {
                        HuSprTPLvlSet(group, i, elem->unk06);
                    } else {
                        HuSprTPLvlSet(group, i, sprAlpha);
                    }
                }
            }
            if (work->unk140) {
                if (done) {
                    work->unk140 = 0;
                }
                x = work->unk13C;
                for (i = 0; i < 13; i++) {
                    if (sprAlpha == 0) {
                        HuSprDispOff(x, i);
                    }
                    HuSprTPLvlSet(x, i, sprAlpha);
                }
            }
        }
        if (winFadeSpeed != 0) {
            done = 0;
            winAlpha += winFadeSpeed;
            if (winAlpha >= 255) {
                winFadeSpeed = 0;
                winAlpha = 255;
                done = 1;
            } else if (winAlpha <= 0) {
                winFadeSpeed = 0;
                winAlpha = 0;
                done = 1;
            }
            for (win = work->windows, flag = work->winFlags, i = 0; i < 6; i++, win++, flag++) {
                if (*flag > 0) {
                    if ((s16)done) {
                        *flag = 0;
                    }
                    HuWinTPLvlSet(*win, winAlpha);
                }
            }
        }
        HuPrcVSleep();
    } while (state != 255);

    HuSprGrpKill(group);
    for (elem = work->elems, i = 0; i < ARRAY_COUNTU(work->elems); i++, elem++) {
        if (elem->unk04 >= 0) {
            HuSprAnimKill(elem->unk04);
        }
    }
    HuSprGrpKill(work->unk13C);
    HuSprAnimKill(work->unk13E);
    for (gfx = work->graphics, i = 0; i < 4; i++, gfx++) {
        if (*gfx >= 0) {
            HuSprAnimKill(*gfx);
        }
    }
    for (win = work->windows, i = 0; i < ARRAY_COUNTU(work->windows); i++, win++) {
        HuWinKill(*win);
    }
    HuMemFree(work);
    data->unk04 = 0;
    while (TRUE) {
        HuPrcVSleep();
    }
}

Process *MgStoryStatCreate(u16 arg0, s16 arg1) {
    MgStoryStatParam *data;
    Process *prc;

    if (arg0 == 0 || arg0 == 1) {
        if (MgStoryRankGet(arg1) < 0) {
            return NULL;
        }
    }
    data = HuMemAllocTag(sizeof(MgStoryStatParam), 0x7918);
    memset(data, 0, sizeof(MgStoryStatParam));
    data->x = 160;
    data->y = 120;
    data->unk00 = arg0;
    data->unk02 = arg1;
    prc = omAddPrcObj(MgStoryStatExec, 0x4000, 0x800, 0);
    prc->user_data = data;
    return prc;
}

s32 MgStoryStatKill(Process *prc) {
    MgStoryStatParam *data;
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

s16 MgStoryStatModeSet(Process *prc, s16 value) {
    MgStoryStatParam *data = prc->user_data;

    data->unk04 = value;
    return value;
}

s16 MgStoryStatModeGet(Process *prc) {
    MgStoryStatParam *data = prc->user_data;

    return data->unk04;
}

void MgStoryStatModeWait(Process *prc, s16 value) {
    MgStoryStatParam *data = prc->user_data;

    if (data->unk04 != value) {
        do {
            HuPrcVSleep();
        } while (data->unk04 != value);
    }
}

s16 MgStoryRankGet(s16 arg0) {
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
    total = mgStoryBossScoreTbl[*last];
    for (i = 0; i < 12; i++, entries++) {
        if (*entries == 0) {
            return -1;
        }
        if (*entries >= 5) {
            *entries = 4;
        }
        total += mgStoryResultScoreTbl[*entries];
    }
    for (rank = 0; rank < 4; rank++) {
        if (total < mgStoryRankBorderTbl[rank]) {
            break;
        }
    }
    return rank;
}

void MgStoryStatViewProc(void) {
    s16 sprites[2];
    MgStoryStatPos pos[2];
    s16 *result;
    s16 cursorAnim;
    s16 arrowAnim;
    s16 window;
    s16 frameAnim;
    s16 frame;
    s16 cursor;
    Process *prc;
    s16 i;
    s16 selection;
    s16 speed;
    s16 angle;
    s16 story;
    f32 offset;

    result = HuPrcCurrentGet()->user_data;

    frameAnim = HuSprAnimDataRead(0x140064);
    frame = espEntry(frameAnim, 0, 1);
    espPriSet(frame, 0x4BA);
    espScaleSet(frame, 10.0f, 8.0f);
    espPosSet(frame, 160, 120);
    espColorSet(frame, 0, 0, 0);
    espTPLvlSet(frame, 0);
    espDispOff(frame);

    cursorAnim = HuSprAnimDataRead(0x150001);
    cursor = espEntry(cursorAnim, 0, 1);
    espPriSet(cursor, 600);
    espPosSet(cursor, 160, 204);
    espTPLvlSet(cursor, 0);
    espDispOff(cursor);

    window = HuWinCreate(48, 187, 224, 42, 0, 12);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 0);
    HuWinPriSet(window, 1);
    HuWinMesPalSet(window, 2, 255, 0, 0);
    HuWinMesPalSet(window, 4, 0, 144, 0);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 6, 255, 173, 0);
    HuWinMesDefColSet(window, 64, 64, 64);
    HuWinBGColSet(window, 0, 0, 0);
    HuWinMesColSet(window, 7);
    HuWinTPLvlSet(window, 255);

    pos[0].x = 25;
    pos[1].x = 295;
    pos[0].y = pos[1].y = 130;
    arrowAnim = HuSprAnimDataRead(0x150003);
    for (i = 0; i < 2; i++) {
        sprites[i] = espEntry(arrowAnim, 0, 1);
        espPriSet(sprites[i], 100);
        espPosSet(sprites[i], pos[i].x, pos[i].y);
        espTPLvlSet(sprites[i], 0);
        espDispOff(sprites[i]);
    }
    espAttrSet(sprites[1], HUSPR_ATTR_FLIPX);

    if (*result < 0) {
        story = GwStory.unk1;
    } else {
        story = *result;
    }
    prc = MgStoryStatCreate(0, story);
    HuPrcVSleep();
    MgStoryStatModeSet(prc, 1);
    espDispOn(cursor);
    espDispOn(sprites[0]);
    espDispOn(sprites[1]);
    espDispOn(frame);
    for (i = 0; i <= 256; i += 36) {
        espTPLvlSet(cursor, i);
        espTPLvlSet(sprites[0], i);
        espTPLvlSet(sprites[1], i);
        if (i <= 128) {
            espTPLvlSet(frame, i);
        }
        HuPrcVSleep();
    }

    HuWinMesSet(window, 0x6125, -1, -1);
    HuPrcVSleep();
    selection = 0;
    angle = 0;
    speed = 0;
    while (TRUE) {
        if (HuPadBtnDown[mgStoryStatPortNo] & B_BUTTON) {
            HuAudFXPlay(4);
            *result = -2;
            break;
        }
        if (HuPadBtnDown[mgStoryStatPortNo] & START_BUTTON) {
            HuAudFXPlay(2);
            *result = -1;
            break;
        }
        if (MgStoryStatModeGet(prc) == 0) {
            if ((HuPadBtnDown[mgStoryStatPortNo] & R_JPAD) || HuPadStkX[mgStoryStatPortNo] >= 31) {
                HuAudFXPlay(1);
                MgStoryStatModeSet(prc, 3);
                angle = 180;
                speed = -22;
                selection = 1;
            } else if ((HuPadBtnDown[mgStoryStatPortNo] & L_JPAD) || HuPadStkX[mgStoryStatPortNo] < -30) {
                HuAudFXPlay(1);
                MgStoryStatModeSet(prc, 4);
                angle = 180;
                speed = 22;
                selection = 0;
            }
        }
        if (speed != 0) {
            if ((u16)(angle += speed) > 360) {
                espPosSet(sprites[0], pos[0].x, pos[0].y);
                speed = 0;
                espPosSet(sprites[1], pos[1].x, pos[1].y);
            } else {
                offset = sindf(angle) * 8.0f;
                espPosSet(sprites[selection], pos[selection].x + offset, pos[selection].y);
            }
        }
        HuPrcVSleep();
    }

    MgStoryStatModeSet(prc, 2);
    HuWinHomeClear(window);
    for (i = 256; i >= 0; i -= 36) {
        espTPLvlSet(cursor, i);
        espTPLvlSet(sprites[0], i);
        espTPLvlSet(sprites[1], i);
        if (i <= 128) {
            espTPLvlSet(frame, i);
        }
        HuPrcVSleep();
    }
    espDispOff(cursor);
    espDispOff(sprites[0]);
    espDispOff(sprites[1]);
    espDispOff(frame);
    MgStoryStatModeWait(prc, 0);
    MgStoryStatKill(prc);
    espKill(frame);
    espKill(cursor);
    espKill(sprites[0]);
    espKill(sprites[1]);
    HuSprAnimKill(frameAnim);
    HuSprAnimKill(cursorAnim);
    HuSprAnimKill(arrowAnim);
    HuWinKill(window);
    omDelPrcObj(NULL);
    *result = -3;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void MgStoryStageGoto(void) {
    GW_PLAYER *temp;
    GW_PLAYER *player;
    GW_PLAYER *player0;
    s32 overlay;
    s16 event;
    u16 stat;
    s16 count;
    s8 star;
    s16 first;
    s32 i;

    switch (mgStoryPageTbl[GwStory.unk0]) {
        case 0:
            _ClearFlag(0x28);
            _ClearFlag(0);
            _SetFlag(0x1B);
            stat = 0x92;
            overlay = 0x47;
            event = 0;
            count = 4;
            star = 0;
            break;
        case 1:
            _ClearFlag(0x28);
            _ClearFlag(0);
            stat = 0x4090;
            overlay = 0x5A;
            event = 0;
            count = 2;
            star = 5;
            break;
        case 2:
        default:
            stat = 0x92;
            overlay = 0x70;
            event = 0;
            omOvlHisChg(-1, overlay, event, stat);
            GwSystem.minigame_index = 0x42;
            GwSystem.show_minigame_explanations = 0;
            GwPlayer[0].group = 0;
            GwPlayer[0].chr = GwStory.unk1;
            GwPlayer[0].cpu_difficulty = GwStory.unk2;
            for (i = 1; i < 4; i++) {
                GwPlayer[i].group = 1;
                GwPlayer[i].cpu_difficulty = GwStory.unk2;
                GwPlayer[i].chr = 6;
            }
            count = 2;
            star = 0;
            break;
    }
    first = TRUE;
    for (i = 0; i < count; i++) {
        GwPlayer[i].star = star;
        GwPlayer[i].coin = 0;
        if (GwPlayer[i].chr == GwStory.unk1) {
            GwPlayer[i].stat = 0;
            if (first) {
                first = FALSE;
                if (i != 0) {
                    player = &GwPlayer[i];
                    player0 = &GwPlayer[0];
                    temp = HuMemAllocTag(sizeof(GW_PLAYER), TAG_OVERLAY);
                    *temp = *player0;
                    *player0 = *player;
                    *player = *temp;
                    HuMemFree(temp);
                }
            }
        } else {
            GwPlayer[i].stat = PLAYER_IS_CPU;
        }
    }
    omOvlHisChg(0, 0x7D, 0, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
    omovlhisidx++;
    omOvlGotoEx(overlay, event, stat);
}
