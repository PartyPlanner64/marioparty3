#include "common.h"
#include "game_guys_roulette.h"

typedef struct GameGuysRouletteSpotLayer { // 0x14 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
} GameGuysRouletteSpotLayer;

typedef struct GameGuysRouletteSpot { // 0x18 bytes
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 radius;
    /* 0x0C */ f32 angle;
    /* 0x10 */ f32 speed;
    /* 0x14 */ s16 freqX;
    /* 0x16 */ s16 freqY;
} GameGuysRouletteSpot;

typedef struct GameGuysRouletteSpotHistory { // 0x20 bytes
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 radius[4];
} GameGuysRouletteSpotHistory;

typedef struct GameGuysRouletteSpotFreq {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} GameGuysRouletteSpotFreq;

s16 m266_spotIntroTimer = 0;   // intro timer
s16 m266_spotStartY = 120; // intro start y
s16 m266_spotBeamTimer = 0;   // outro timer

GameGuysRouletteSpot m266_spotTbl[3] BSS;
s16 m266_spotCenterX BSS;                            // center x
s16 m266_spotCenterY BSS;                            // center y
s16 m266_spotRadius BSS;                            // radius
s16 m266_spotTargetX BSS;                            // target x
s16 m266_spotTargetY BSS;                            // target y
u8 m266_spotTargetYPad[4] BSS;                          /* Unreferenced. */
GameGuysRouletteSpotHistory m266_spotHistoryTbl[3] BSS; // per-buffer ring state
u8 m266_spotHistoryTblPad[8] BSS;                          /* Unreferenced. */
GameGuysRouletteSpotLayer m266_spotMaskLayer BSS;
s16 m266_spotBufNo BSS; // current buffer index
GameGuysRouletteSpotLayer m266_spotColorLayer BSS;

void m266_SpotLayerInit(void);
void m266_SpotLayerClear(void);
void m266_SpotErase(s16 active, s16 x, s16 y, s16 radius);
void m266_SpotDraw(s16 active, s16 x, s16 y, s16 color);
void m266_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color);
void m266_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1);

void m266_SpotIntroInit(s16 x, s16 y) {
    s16 i;
    u8 pattern;
    GameGuysRouletteSpotFreq freqs[3] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };

    m266_spotCenterX = 160;
    m266_spotCenterY = 120;
    m266_spotRadius = 95;
    m266_spotTargetX = x;
    m266_spotTargetY = y;
    pattern = rand8() % 3;
    for (i = 0; i < 3; i++) {
        m266_spotTbl[i].active = 0;
        m266_spotTbl[i].freqX = freqs[pattern].x;
        m266_spotTbl[i].freqY = freqs[pattern].y;
        m266_spotTbl[i].speed = 1.5f;
        if (pattern == 0) {
            m266_spotTbl[i].speed = 1.75f;
        }
        m266_spotTbl[i].angle = i * 120;
        m266_spotTbl[i].x =
            m266_spotCenterX + cosdf(m266_spotTbl[i].freqX * m266_spotTbl[i].angle) * m266_spotRadius;
        m266_spotTbl[i].y =
            m266_spotCenterY + sindf(m266_spotTbl[i].freqY * m266_spotTbl[i].angle) * m266_spotRadius;
        m266_spotTbl[i].radius = 0;
    }
    m266_spotTbl[0].color = 1;
    m266_spotTbl[1].color = 2;
    m266_spotTbl[2].color = 4;
    m266_spotColorLayer.timer = 128;
    m266_spotMaskLayer.timer = 256;
    m266_SpotLayerInit();
    m266_SpotLayerClear();
    m266_spotBufNo = 0;
}

void m266_SpotBeamInit(void) {
    m266_SpotLayerClear();
    m266_spotBufNo = 0;
    m266_spotColorLayer.timer = 0;
    HuSprTPLvlSet(m266_spotColorLayer.group, 0, 0);
    HuSprAttrReset(m266_spotColorLayer.group, 0, 0xFFFF);
    HuSprAttrSet(m266_spotColorLayer.group, 0, 0x1000);
    m266_spotColorLayer.sprite->data->pat->data =
        m266_spotColorLayer.unk_04[m266_spotBufNo];
}

s16 m266_SpotIntroUpdate(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (m266_spotIntroTimer >= 5) {
        if (m266_spotIntroTimer < 15) {
            for (i = 0; i < 3; i++) {
                m266_spotTbl[i].active = 1;
                m266_spotTbl[i].radius = sindf((m266_spotIntroTimer - 5) * 9.0f) * 45.0f;
            }
        } else if (m266_spotIntroTimer < 20) {
            for (i = 0; i < 3; i++) {
                m266_spotTbl[i].radius = 45;
            }
        } else if (m266_spotIntroTimer < 47) {
            for (i = 0; i < 3; i++) {
                m266_spotTbl[i].angle += m266_spotTbl[i].speed;
                if (m266_spotTbl[i].angle >= 360.0f) {
                    m266_spotTbl[i].angle -= 360.0f;
                }
                if (m266_spotTbl[i].angle < 0.0f) {
                    m266_spotTbl[i].angle += 360.0f;
                }
                m266_spotTbl[i].x = m266_spotCenterX +
                                                     cosdf(m266_spotTbl[i].freqX * m266_spotTbl[i].angle) * m266_spotRadius;
                m266_spotTbl[i].y = m266_spotCenterY +
                                                     sindf(m266_spotTbl[i].freqY * m266_spotTbl[i].angle) * m266_spotRadius;
            }
        } else if (m266_spotIntroTimer < 80) {
            if (m266_spotRadius > 0) {
                if ((m266_spotRadius -= 3) <= 0) {
                    m266_spotRadius = 0;
                }
            }
            m266_spotCenterY =
                m266_spotStartY - sindf((m266_spotIntroTimer - 47) * 2.7272727f) *
                                                    (m266_spotStartY - m266_spotTargetY);
            if (m266_spotIntroTimer == 79) {
                m266_spotCenterY = m266_spotTargetY;
            }
            for (i = 0; i < 3; i++) {
                m266_spotTbl[i].angle += m266_spotTbl[i].speed;
                if (m266_spotTbl[i].angle >= 360.0f) {
                    m266_spotTbl[i].angle -= 360.0f;
                }
                if (m266_spotTbl[i].angle < 0.0f) {
                    m266_spotTbl[i].angle += 360.0f;
                }
                m266_spotTbl[i].x = m266_spotCenterX +
                                                     cosdf(m266_spotTbl[i].freqX * m266_spotTbl[i].angle) * m266_spotRadius;
                m266_spotTbl[i].y = m266_spotCenterY +
                                                     sindf(m266_spotTbl[i].freqY * m266_spotTbl[i].angle) * m266_spotRadius;
            }
        } else if (m266_spotIntroTimer < 90) {
            for (i = 1; i < 3; i++) {
                m266_spotTbl[i].active = 0;
            }
            m266_spotTbl[0].color = 7;
        } else if (m266_spotIntroTimer >= 120) {
            m266_SpotDispOff();
            return 1;
        } else {
            m266_spotTbl[0].radius = sindf((m266_spotIntroTimer - 90) * 3.0f) * 50.0f + 45.0f;
            m266_spotColorLayer.timer = 128.0f - sindf((m266_spotIntroTimer - 90) * 3.0f) * 128.0f;
            m266_spotMaskLayer.timer = 256.0f - sindf((m266_spotIntroTimer - 90) * 3.0f) * 256.0f;
        }
    }
    if (m266_spotIntroTimer == 15) {
        HuAudFXPlay(0x514);
    }
    if (m266_spotIntroTimer == 90) {
        HuAudFXAllFadeOut(30);
        HuAudSeqPlay(0x43);
    }
    if (m266_spotIntroTimer == 115) {
        HuAudFXPlay(0x2A1);
    }
    if (m266_spotColorLayer.timer <= 0) {
        m266_spotColorLayer.timer = 0;
    }
    HuSprTPLvlSet(m266_spotColorLayer.group, 0, m266_spotColorLayer.timer);
    if (m266_spotMaskLayer.timer <= 0) {
        m266_spotMaskLayer.timer = 0;
    }
    HuSprTPLvlSet(m266_spotMaskLayer.group, 0, m266_spotMaskLayer.timer);
    if (m266_spotIntroTimer < 90) {
        for (i = 0; i < 3; i++) {
            m266_SpotErase(m266_spotHistoryTbl[m266_spotBufNo].active[i], m266_spotHistoryTbl[m266_spotBufNo].x[i],
                                             m266_spotHistoryTbl[m266_spotBufNo].y[i], m266_spotHistoryTbl[m266_spotBufNo].radius[i]);
            m266_spotHistoryTbl[m266_spotBufNo].active[i] = m266_spotTbl[i].active;
            m266_spotHistoryTbl[m266_spotBufNo].x[i] = m266_spotTbl[i].x;
            m266_spotHistoryTbl[m266_spotBufNo].y[i] = m266_spotTbl[i].y;
            m266_spotHistoryTbl[m266_spotBufNo].radius[i] = m266_spotTbl[i].radius;
        }
    }
    if (m266_spotIntroTimer < 20) {
        for (i = 0; i < 3; i++) {
            m266_SpotDrawEx(m266_spotTbl[i].active, m266_spotTbl[i].x, m266_spotTbl[i].y, m266_spotTbl[i].radius, m266_spotTbl[i].color);
        }
    } else if (m266_spotIntroTimer < 81) {
        for (i = 0; i < 3; i++) {
            m266_SpotDraw(m266_spotTbl[i].active, m266_spotTbl[i].x, m266_spotTbl[i].y, m266_spotTbl[i].color);
        }
    } else {
        m266_SpotDrawEx(m266_spotTbl[0].active, m266_spotTbl[0].x, m266_spotTbl[0].y, m266_spotTbl[0].radius, m266_spotTbl[0].color);
    }
    m266_spotColorLayer.sprite->data->pat->data = m266_spotColorLayer.unk_04[m266_spotBufNo];
    m266_spotMaskLayer.sprite->data->pat->data = m266_spotMaskLayer.unk_04[m266_spotBufNo];
    m266_spotBufNo = (s16)(m266_spotBufNo + 1) % 3;
    m266_spotIntroTimer++;
    return 0;
}

s32 m266_SpotBeamUpdate(s32 x) {
    s16 i;

    m266_spotColorLayer.sprite->data->pat->data = m266_spotColorLayer.unk_04[0];
    if (m266_spotBeamTimer++ < 10) {
        m266_spotColorLayer.timer = 0;
    } else if (m266_spotBeamTimer < 30) {
        m266_spotColorLayer.timer = sindf((m266_spotBeamTimer - 10) * 4.5f) * 128.0f;
        HuSprTPLvlSet(m266_spotColorLayer.group, 0, m266_spotColorLayer.timer);
    } else if (m266_spotBeamTimer >= 40) {
        if (m266_spotBeamTimer < 90) {
            for (i = 0; i < 5; i++) {
                m266_SpotLineDraw(x, -100, x + (m266_spotBeamTimer - 40) + i, 240);
                m266_SpotLineDraw(x, -100, x - (m266_spotBeamTimer - 40) - i, 240);
            }
            m266_spotBeamTimer += 4;
        } else {
            return 1;
        }
    }
    return 0;
}

void m266_SpotDispOff(void) {
    HuSprDispOff(m266_spotColorLayer.group, 0);
    HuSprDispOff(m266_spotMaskLayer.group, 0);
    m266_spotColorLayer.sprite->data->pat->data =
        m266_spotColorLayer.unk_04[0];
    m266_spotMaskLayer.sprite->data->pat->data =
        m266_spotMaskLayer.unk_04[0];
}

s16 m266_SpotSprCreate(s32 dataNum, s32 attr, s32 priority, s32 tpLvl) {
    s16 sprite;
    s16 group;

    sprite = HuSprAnimDataRead(dataNum);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, attr | 0x1000);
    HuSprPriSet(group, 0, priority);
    HuSprPosSet(group, 0, 160, 120);
    HuSprTPLvlSet(group, 0, tpLvl);
    return group;
}

void m266_SpotLayerInit(void) {
    s16 *pal;

    m266_spotColorLayer.group = m266_SpotSprCreate(0x63000A, 0, 10, 128);
    m266_spotColorLayer.sprite = HuSprGet(m266_spotColorLayer.group, 0);
    m266_spotColorLayer.unk_04[0] = m266_spotColorLayer.sprite->data->pat->data;
    pal = m266_spotColorLayer.sprite->data->pal;
    m266_spotColorLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m266_spotColorLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;

    m266_spotMaskLayer.group = m266_SpotSprCreate(0x63000A, 0, 10, 256);
    m266_spotMaskLayer.sprite = HuSprGet(m266_spotMaskLayer.group, 0);
    m266_spotMaskLayer.unk_04[0] = m266_spotMaskLayer.sprite->data->pat->data;
    pal = m266_spotMaskLayer.sprite->data->pal;
    m266_spotMaskLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m266_spotMaskLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x0000;
}

void m266_SpotLayerClear(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = m266_spotColorLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = m266_spotMaskLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

void m266_SpotErase(s16 active, s16 x, s16 y, s16 radius) {
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    if ((active == 0) | (radius < 1)) {
        return;
    }
    pixels = (u8 *)m266_spotColorLayer.unk_04[m266_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    mask = (u8 *)m266_spotMaskLayer.unk_04[m266_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    for (py = y - radius; py < y + radius; py++) {
        pixels += 159 - radius;
        mask += 159 - radius;
        for (px = x - radius; px < x + (radius + 1); px += 2) {
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                *pixels = 0;
                *mask = 0;
            }
            pixels++;
            mask++;
        }
    }
}

void m266_SpotDraw(s16 active, s16 x, s16 y, s16 color) {
    m266_SpotDrawEx(active, x, y, 45, color);
}

void m266_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color) {
    s32 radiusSq;
    s32 distXSq;
    s32 distYSq;
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    radiusSq = radius * radius;
    if ((active == 0) | (radius < 1)) {
        return;
    }
    for (py = y - radius; py < y + radius; py++) {
        pixels = (u8 *)m266_spotColorLayer.unk_04[m266_spotBufNo] + (x - radius) / 2 + py * 160;
        mask = (u8 *)m266_spotMaskLayer.unk_04[m266_spotBufNo] + (x - radius) / 2 + py * 160;
        distYSq = (py - y) * (py - y);
        for (px = x - radius; px < x + radius; px++) {
            distXSq = (px - x) * (px - x);
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                if (distXSq + distYSq < radiusSq) {
                    if (px & 1) {
                        *pixels |= color;
                        *mask |= 1;
                    } else {
                        *pixels |= color << 4;
                        *mask |= 0x10;
                    }
                }
            }
            if (px & 1) {
                pixels++;
                mask++;
            }
        }
    }
}

void m266_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1) {
    s16 dx;
    s16 dy;
    s16 err;
    u8 *pixels;

    dx = (x0 > x1) ? x0 - x1 : x1 - x0;
    dy = (y0 > y1) ? y0 - y1 : y1 - y0;
    err = dy / 2;
    if (x0 <= x1) {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err < 0) {
                err += dy;
                x0++;
            }
            if (x0 >= 0 && x0 < 320 && y0 >= 0 && y0 < 240) {
                pixels = (u8 *)m266_spotColorLayer.unk_04[m266_spotBufNo] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    } else {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err < 0) {
                err += dy;
                x0--;
            }
            if (x0 >= 0 && x0 < 320 && y0 >= 0 && y0 < 240) {
                pixels = (u8 *)m266_spotColorLayer.unk_04[m266_spotBufNo] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    }
}
