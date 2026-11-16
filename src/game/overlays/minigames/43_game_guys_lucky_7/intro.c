#include "common.h"
#include "game_guys_lucky_7.h"

typedef struct GameGuysLucky7SpotLayer { // 0x14 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
} GameGuysLucky7SpotLayer;

typedef struct GameGuysLucky7Spot { // 0x18 bytes
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 radius;
    /* 0x0A */ s16 freqX;
    /* 0x0C */ s16 freqY;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 speed;
} GameGuysLucky7Spot;

typedef struct GameGuysLucky7SpotHistory { // 0x20 bytes
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 radius[4];
} GameGuysLucky7SpotHistory;

typedef struct GameGuysLucky7SpotFreq {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} GameGuysLucky7SpotFreq;

s16 m267_spotIntroTimer = 0;   // intro timer
s16 m267_spotStartY = 120; // intro start y
s16 m267_spotBeamTimer = 0;   // outro timer

GameGuysLucky7Spot m267_spotTbl[3] BSS;
s16 m267_spotCenterX BSS;                          // center x
s16 m267_spotCenterY BSS;                          // center y
s16 m267_spotRadius BSS;                          // radius
s16 m267_spotTargetX BSS;                          // target x
s16 m267_spotTargetY BSS;                          // target y
u8 m267_spotTargetYPad[4] BSS;                        /* Unreferenced. */
GameGuysLucky7SpotHistory m267_spotHistoryTbl[3] BSS; // per-buffer ring state
u8 m267_spotHistoryTblPad[8] BSS;                        /* Unreferenced. */
GameGuysLucky7SpotLayer m267_spotMaskLayer BSS;
s16 m267_spotBufNo BSS; // current buffer index
GameGuysLucky7SpotLayer m267_spotColorLayer BSS;

void m267_SpotLayerInit(void);
void m267_SpotLayerClear(void);
void m267_SpotErase(s16 active, s16 x, s16 y, s16 radius);
void m267_SpotDraw(s16 active, s16 x, s16 y, s16 color);
void m267_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color);
void m267_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1);

void m267_SpotIntroInit(s16 x, s16 y) {
    s16 i;
    u8 pattern;
    GameGuysLucky7SpotFreq freqs[3] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };

    m267_spotCenterX = 160;
    m267_spotCenterY = 120;
    m267_spotRadius = 95;
    m267_spotTargetX = x;
    m267_spotTargetY = y;
    pattern = rand8() % 3;
    for (i = 0; i < 3; i++) {
        m267_spotTbl[i].active = 0;
        m267_spotTbl[i].freqX = freqs[pattern].x;
        m267_spotTbl[i].freqY = freqs[pattern].y;
        m267_spotTbl[i].speed = 1.5f;
        if (pattern == 0) {
            m267_spotTbl[i].speed = 1.75f;
        }
        m267_spotTbl[i].angle = i * 120;
        m267_spotTbl[i].x =
            m267_spotCenterX + cosdf(m267_spotTbl[i].freqX * m267_spotTbl[i].angle) * m267_spotRadius;
        m267_spotTbl[i].y =
            m267_spotCenterY + sindf(m267_spotTbl[i].freqY * m267_spotTbl[i].angle) * m267_spotRadius;
        m267_spotTbl[i].radius = 0;
    }
    m267_spotTbl[0].color = 1;
    m267_spotTbl[1].color = 2;
    m267_spotTbl[2].color = 4;
    m267_spotColorLayer.timer = 128;
    m267_spotMaskLayer.timer = 256;
    m267_SpotLayerInit();
    m267_SpotLayerClear();
    m267_spotBufNo = 0;
}

void m267_SpotBeamInit(void) {
    m267_SpotLayerClear();
    m267_spotBufNo = 0;
    m267_spotColorLayer.timer = 0;
    HuSprTPLvlSet(m267_spotColorLayer.group, 0, 0);
    HuSprAttrReset(m267_spotColorLayer.group, 0, 0xFFFF);
    HuSprAttrSet(m267_spotColorLayer.group, 0, 0x1000);
    m267_spotColorLayer.sprite->data->pat->data =
        m267_spotColorLayer.unk_04[m267_spotBufNo];
}

s16 m267_SpotIntroUpdate(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (m267_spotIntroTimer >= 5) {
        if (m267_spotIntroTimer < 15) {
            for (i = 0; i < 3; i++) {
                m267_spotTbl[i].active = 1;
                m267_spotTbl[i].radius = sindf((m267_spotIntroTimer - 5) * 9.0f) * 45.0f;
            }
        } else if (m267_spotIntroTimer < 20) {
            for (i = 0; i < 3; i++) {
                m267_spotTbl[i].radius = 45;
            }
        } else if (m267_spotIntroTimer < 47) {
            for (i = 0; i < 3; i++) {
                m267_spotTbl[i].angle += m267_spotTbl[i].speed;
                if (m267_spotTbl[i].angle >= 360.0f) {
                    m267_spotTbl[i].angle -= 360.0f;
                }
                if (m267_spotTbl[i].angle < 0.0f) {
                    m267_spotTbl[i].angle += 360.0f;
                }
                m267_spotTbl[i].x = m267_spotCenterX +
                                                    cosdf(m267_spotTbl[i].freqX * m267_spotTbl[i].angle) * m267_spotRadius;
                m267_spotTbl[i].y = m267_spotCenterY +
                                                    sindf(m267_spotTbl[i].freqY * m267_spotTbl[i].angle) * m267_spotRadius;
            }
        } else if (m267_spotIntroTimer < 80) {
            if (m267_spotRadius > 0) {
                if ((m267_spotRadius -= 3) <= 0) {
                    m267_spotRadius = 0;
                }
            }
            m267_spotCenterY =
                m267_spotStartY - sindf((m267_spotIntroTimer - 47) * 2.7272727f) *
                                                   (m267_spotStartY - m267_spotTargetY);
            if (m267_spotIntroTimer == 79) {
                m267_spotCenterY = m267_spotTargetY;
            }
            for (i = 0; i < 3; i++) {
                m267_spotTbl[i].angle += m267_spotTbl[i].speed;
                if (m267_spotTbl[i].angle >= 360.0f) {
                    m267_spotTbl[i].angle -= 360.0f;
                }
                if (m267_spotTbl[i].angle < 0.0f) {
                    m267_spotTbl[i].angle += 360.0f;
                }
                m267_spotTbl[i].x = m267_spotCenterX +
                                                    cosdf(m267_spotTbl[i].freqX * m267_spotTbl[i].angle) * m267_spotRadius;
                m267_spotTbl[i].y = m267_spotCenterY +
                                                    sindf(m267_spotTbl[i].freqY * m267_spotTbl[i].angle) * m267_spotRadius;
            }
        } else if (m267_spotIntroTimer < 90) {
            for (i = 1; i < 3; i++) {
                m267_spotTbl[i].active = 0;
            }
            m267_spotTbl[0].color = 7;
        } else if (m267_spotIntroTimer >= 120) {
            m267_SpotDispOff();
            return 1;
        } else {
            m267_spotTbl[0].radius = sindf((m267_spotIntroTimer - 90) * 3.0f) * 50.0f + 45.0f;
            m267_spotColorLayer.timer = 128.0f - sindf((m267_spotIntroTimer - 90) * 3.0f) * 128.0f;
            m267_spotMaskLayer.timer = 256.0f - sindf((m267_spotIntroTimer - 90) * 3.0f) * 256.0f;
        }
    }
    if (m267_spotIntroTimer == 15) {
        HuAudFXPlay(0x51F);
    }
    if (m267_spotIntroTimer == 90) {
        HuAudFXAllFadeOut(30);
        HuAudSeqPlay(0x43);
    }
    if (m267_spotIntroTimer == 100) {
        HuAudFXPlay(0x2A1);
    }
    if (m267_spotColorLayer.timer <= 0) {
        m267_spotColorLayer.timer = 0;
    }
    HuSprTPLvlSet(m267_spotColorLayer.group, 0, m267_spotColorLayer.timer);
    if (m267_spotMaskLayer.timer <= 0) {
        m267_spotMaskLayer.timer = 0;
    }
    HuSprTPLvlSet(m267_spotMaskLayer.group, 0, m267_spotMaskLayer.timer);
    if (m267_spotIntroTimer < 90) {
        for (i = 0; i < 3; i++) {
            m267_SpotErase(m267_spotHistoryTbl[m267_spotBufNo].active[i], m267_spotHistoryTbl[m267_spotBufNo].x[i],
                                            m267_spotHistoryTbl[m267_spotBufNo].y[i], m267_spotHistoryTbl[m267_spotBufNo].radius[i]);
            m267_spotHistoryTbl[m267_spotBufNo].active[i] = m267_spotTbl[i].active;
            m267_spotHistoryTbl[m267_spotBufNo].x[i] = m267_spotTbl[i].x;
            m267_spotHistoryTbl[m267_spotBufNo].y[i] = m267_spotTbl[i].y;
            m267_spotHistoryTbl[m267_spotBufNo].radius[i] = m267_spotTbl[i].radius;
        }
    }
    if (m267_spotIntroTimer < 20) {
        for (i = 0; i < 3; i++) {
            m267_SpotDrawEx(m267_spotTbl[i].active, m267_spotTbl[i].x, m267_spotTbl[i].y, m267_spotTbl[i].radius, m267_spotTbl[i].color);
        }
    } else if (m267_spotIntroTimer < 81) {
        for (i = 0; i < 3; i++) {
            m267_SpotDraw(m267_spotTbl[i].active, m267_spotTbl[i].x, m267_spotTbl[i].y, m267_spotTbl[i].color);
        }
    } else {
        m267_SpotDrawEx(m267_spotTbl[0].active, m267_spotTbl[0].x, m267_spotTbl[0].y, m267_spotTbl[0].radius, m267_spotTbl[0].color);
    }
    m267_spotColorLayer.sprite->data->pat->data = m267_spotColorLayer.unk_04[m267_spotBufNo];
    m267_spotMaskLayer.sprite->data->pat->data = m267_spotMaskLayer.unk_04[m267_spotBufNo];
    m267_spotBufNo = (s16)(m267_spotBufNo + 1) % 3;
    m267_spotIntroTimer++;
    return 0;
}

s32 m267_SpotBeamUpdate(s32 x) {
    s16 i;

    m267_spotColorLayer.sprite->data->pat->data = m267_spotColorLayer.unk_04[0];
    if (m267_spotBeamTimer++ < 10) {
        m267_spotColorLayer.timer = 0;
    } else if (m267_spotBeamTimer < 30) {
        m267_spotColorLayer.timer = sindf((m267_spotBeamTimer - 10) * 4.5f) * 128.0f;
        HuSprTPLvlSet(m267_spotColorLayer.group, 0, m267_spotColorLayer.timer);
    } else if (m267_spotBeamTimer >= 40) {
        if (m267_spotBeamTimer < 90) {
            for (i = 0; i < 5; i++) {
                m267_SpotLineDraw(x, -100, x + (m267_spotBeamTimer - 40) + i, 240);
                m267_SpotLineDraw(x, -100, x - (m267_spotBeamTimer - 40) - i, 240);
            }
            m267_spotBeamTimer += 4;
        } else {
            return 1;
        }
    }
    return 0;
}

void m267_SpotDispOff(void) {
    HuSprDispOff(m267_spotColorLayer.group, 0);
    HuSprDispOff(m267_spotMaskLayer.group, 0);
    m267_spotColorLayer.sprite->data->pat->data =
        m267_spotColorLayer.unk_04[0];
    m267_spotMaskLayer.sprite->data->pat->data =
        m267_spotMaskLayer.unk_04[0];
}

s16 m267_SpotSprCreate(s32 dataNum, s32 attr, s32 priority, s32 tpLvl) {
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

void m267_SpotLayerInit(void) {
    s16 *pal;

    m267_spotColorLayer.group = m267_SpotSprCreate(0x64000A, 0, 10, 128);
    m267_spotColorLayer.sprite = HuSprGet(m267_spotColorLayer.group, 0);
    m267_spotColorLayer.unk_04[0] = m267_spotColorLayer.sprite->data->pat->data;
    pal = m267_spotColorLayer.sprite->data->pal;
    m267_spotColorLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m267_spotColorLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;

    m267_spotMaskLayer.group = m267_SpotSprCreate(0x64000A, 0, 10, 256);
    m267_spotMaskLayer.sprite = HuSprGet(m267_spotMaskLayer.group, 0);
    m267_spotMaskLayer.unk_04[0] = m267_spotMaskLayer.sprite->data->pat->data;
    pal = m267_spotMaskLayer.sprite->data->pal;
    m267_spotMaskLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m267_spotMaskLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x0000;
}

void m267_SpotLayerClear(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = m267_spotColorLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = m267_spotMaskLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

void m267_SpotErase(s16 active, s16 x, s16 y, s16 radius) {
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    if ((active == 0) | (radius < 1)) {
        return;
    }
    pixels = (u8 *)m267_spotColorLayer.unk_04[m267_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    mask = (u8 *)m267_spotMaskLayer.unk_04[m267_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
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

void m267_SpotDraw(s16 active, s16 x, s16 y, s16 color) {
    m267_SpotDrawEx(active, x, y, 45, color);
}

void m267_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color) {
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
        pixels = (u8 *)m267_spotColorLayer.unk_04[m267_spotBufNo] + (x - radius) / 2 + py * 160;
        mask = (u8 *)m267_spotMaskLayer.unk_04[m267_spotBufNo] + (x - radius) / 2 + py * 160;
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

void m267_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1) {
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
                pixels = (u8 *)m267_spotColorLayer.unk_04[m267_spotBufNo] + x0 / 2 + y0 * 160;
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
                pixels = (u8 *)m267_spotColorLayer.unk_04[m267_spotBufNo] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    }
}
