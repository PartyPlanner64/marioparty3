#include "common.h"
#include "game_guys_magic_boxes.h"

typedef struct GameGuysMagicBoxesSpotLayer { // 0x14 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
} GameGuysMagicBoxesSpotLayer;

typedef struct GameGuysMagicBoxesSpot { // 0x18 bytes
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 radius;
    /* 0x0A */ s16 freqX;
    /* 0x0C */ s16 freqY;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 speed;
} GameGuysMagicBoxesSpot;

typedef struct GameGuysMagicBoxesSpotHistory { // 0x20 bytes
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 radius[4];
} GameGuysMagicBoxesSpotHistory;

typedef struct GameGuysMagicBoxesSpotFreq {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} GameGuysMagicBoxesSpotFreq;

s16 m268_spotIntroTimer = 0;   // intro timer
s16 m268_spotStartY = 120; // intro start y
s16 m268_spotBeamTimer = 0;   // outro timer

GameGuysMagicBoxesSpot m268_spotTbl[3] BSS;
s16 m268_spotCenterX BSS;                              // center x
s16 m268_spotCenterY BSS;                              // center y
s16 m268_spotRadius BSS;                              // radius
s16 m268_spotTargetX BSS;                              // target x
s16 m268_spotTargetY BSS;                              // target y
u8 m268_spotTargetYPad[4] BSS;                            /* Unreferenced. */
GameGuysMagicBoxesSpotHistory m268_spotHistoryTbl[3] BSS; // per-buffer ring state
u8 m268_spotHistoryTblPad[8] BSS;                            /* Unreferenced. */
GameGuysMagicBoxesSpotLayer m268_spotMaskLayer BSS;
u8 m268_spotMaskLayerPad[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesSpotLayer m268_spotColorLayer BSS;
s16 m268_spotBufNo BSS; // current buffer index

void m268_SpotLayerInit(void);
void m268_SpotLayerClear(void);
void m268_SpotErase(s16 active, s16 x, s16 y, s16 radius);
void m268_SpotDraw(s16 active, s16 x, s16 y, s16 color);
void m268_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color);
void m268_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1);

void m268_SpotIntroInit(s16 x, s16 y) {
    s16 i;
    u8 pattern;
    GameGuysMagicBoxesSpotFreq freqs[3] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };

    m268_spotCenterX = 160;
    m268_spotCenterY = 120;
    m268_spotRadius = 95;
    m268_spotTargetX = x;
    m268_spotTargetY = y;
    pattern = rand8() % 3;
    for (i = 0; i < 3; i++) {
        m268_spotTbl[i].active = 0;
        m268_spotTbl[i].freqX = freqs[pattern].x;
        m268_spotTbl[i].freqY = freqs[pattern].y;
        m268_spotTbl[i].speed = 1.5f;
        if (pattern == 0) {
            m268_spotTbl[i].speed = 1.75f;
        }
        m268_spotTbl[i].angle = i * 120;
        m268_spotTbl[i].x =
            m268_spotCenterX + cosdf(m268_spotTbl[i].freqX * m268_spotTbl[i].angle) * m268_spotRadius;
        m268_spotTbl[i].y =
            m268_spotCenterY + sindf(m268_spotTbl[i].freqY * m268_spotTbl[i].angle) * m268_spotRadius;
        m268_spotTbl[i].radius = 0;
    }
    m268_spotTbl[0].color = 1;
    m268_spotTbl[1].color = 2;
    m268_spotTbl[2].color = 4;
    m268_spotColorLayer.timer = 128;
    m268_spotMaskLayer.timer = 256;
    m268_SpotLayerInit();
    m268_SpotLayerClear();
    m268_spotBufNo = 0;
}

void m268_SpotBeamInit(void) {
    m268_SpotLayerClear();
    m268_spotBufNo = 0;
    m268_spotColorLayer.timer = 0;
    HuSprTPLvlSet(m268_spotColorLayer.group, 0, 0);
    HuSprAttrReset(m268_spotColorLayer.group, 0, 0xFFFF);
    HuSprAttrSet(m268_spotColorLayer.group, 0, HUSPR_ATTR_XLU);
    m268_spotColorLayer.sprite->data->pat->data =
        m268_spotColorLayer.unk_04[m268_spotBufNo];
}

s16 m268_SpotIntroUpdate(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (m268_spotIntroTimer >= 5) {
        if (m268_spotIntroTimer < 15) {
            for (i = 0; i < 3; i++) {
                m268_spotTbl[i].active = 1;
                m268_spotTbl[i].radius = sindf((m268_spotIntroTimer - 5) * 9.0f) * 45.0f;
            }
        } else if (m268_spotIntroTimer < 20) {
            for (i = 0; i < 3; i++) {
                m268_spotTbl[i].radius = 45;
            }
        } else if (m268_spotIntroTimer < 47) {
            for (i = 0; i < 3; i++) {
                m268_spotTbl[i].angle += m268_spotTbl[i].speed;
                if (m268_spotTbl[i].angle >= 360.0f) {
                    m268_spotTbl[i].angle -= 360.0f;
                }
                if (m268_spotTbl[i].angle < 0.0f) {
                    m268_spotTbl[i].angle += 360.0f;
                }
                m268_spotTbl[i].x = m268_spotCenterX +
                                                        cosdf(m268_spotTbl[i].freqX * m268_spotTbl[i].angle) * m268_spotRadius;
                m268_spotTbl[i].y = m268_spotCenterY +
                                                        sindf(m268_spotTbl[i].freqY * m268_spotTbl[i].angle) * m268_spotRadius;
            }
        } else if (m268_spotIntroTimer < 80) {
            if (m268_spotRadius > 0) {
                if ((m268_spotRadius -= 3) <= 0) {
                    m268_spotRadius = 0;
                }
            }
            m268_spotCenterY =
                m268_spotStartY - sindf((m268_spotIntroTimer - 47) * 2.7272727f) *
                                                       (m268_spotStartY - m268_spotTargetY);
            if (m268_spotIntroTimer == 79) {
                m268_spotCenterY = m268_spotTargetY;
            }
            for (i = 0; i < 3; i++) {
                m268_spotTbl[i].angle += m268_spotTbl[i].speed;
                if (m268_spotTbl[i].angle >= 360.0f) {
                    m268_spotTbl[i].angle -= 360.0f;
                }
                if (m268_spotTbl[i].angle < 0.0f) {
                    m268_spotTbl[i].angle += 360.0f;
                }
                m268_spotTbl[i].x = m268_spotCenterX +
                                                        cosdf(m268_spotTbl[i].freqX * m268_spotTbl[i].angle) * m268_spotRadius;
                m268_spotTbl[i].y = m268_spotCenterY +
                                                        sindf(m268_spotTbl[i].freqY * m268_spotTbl[i].angle) * m268_spotRadius;
            }
        } else if (m268_spotIntroTimer < 90) {
            for (i = 1; i < 3; i++) {
                m268_spotTbl[i].active = 0;
            }
            m268_spotTbl[0].color = 7;
        } else if (m268_spotIntroTimer >= 120) {
            m268_SpotDispOff();
            return 1;
        } else {
            m268_spotTbl[0].radius = sindf((m268_spotIntroTimer - 90) * 3.0f) * 50.0f + 45.0f;
            m268_spotColorLayer.timer = 128.0f - sindf((m268_spotIntroTimer - 90) * 3.0f) * 128.0f;
            m268_spotMaskLayer.timer = 256.0f - sindf((m268_spotIntroTimer - 90) * 3.0f) * 256.0f;
        }
    }
    if (m268_spotIntroTimer == 15) {
        HuAudFXPlay(0x52B);
    }
    if (m268_spotIntroTimer == 90) {
        HuAudFXAllFadeOut(30);
        HuAudSeqPlay(0x43);
    }
    if (m268_spotIntroTimer == 115) {
        HuAudFXPlay(0x2A1);
    }
    if (m268_spotColorLayer.timer <= 0) {
        m268_spotColorLayer.timer = 0;
    }
    HuSprTPLvlSet(m268_spotColorLayer.group, 0, m268_spotColorLayer.timer);
    if (m268_spotMaskLayer.timer <= 0) {
        m268_spotMaskLayer.timer = 0;
    }
    HuSprTPLvlSet(m268_spotMaskLayer.group, 0, m268_spotMaskLayer.timer);
    if (m268_spotIntroTimer < 90) {
        for (i = 0; i < 3; i++) {
            m268_SpotErase(m268_spotHistoryTbl[m268_spotBufNo].active[i], m268_spotHistoryTbl[m268_spotBufNo].x[i],
                                                m268_spotHistoryTbl[m268_spotBufNo].y[i], m268_spotHistoryTbl[m268_spotBufNo].radius[i]);
            m268_spotHistoryTbl[m268_spotBufNo].active[i] = m268_spotTbl[i].active;
            m268_spotHistoryTbl[m268_spotBufNo].x[i] = m268_spotTbl[i].x;
            m268_spotHistoryTbl[m268_spotBufNo].y[i] = m268_spotTbl[i].y;
            m268_spotHistoryTbl[m268_spotBufNo].radius[i] = m268_spotTbl[i].radius;
        }
    }
    if (m268_spotIntroTimer < 20) {
        for (i = 0; i < 3; i++) {
            m268_SpotDrawEx(m268_spotTbl[i].active, m268_spotTbl[i].x, m268_spotTbl[i].y, m268_spotTbl[i].radius, m268_spotTbl[i].color);
        }
    } else if (m268_spotIntroTimer < 81) {
        for (i = 0; i < 3; i++) {
            m268_SpotDraw(m268_spotTbl[i].active, m268_spotTbl[i].x, m268_spotTbl[i].y, m268_spotTbl[i].color);
        }
    } else {
        m268_SpotDrawEx(m268_spotTbl[0].active, m268_spotTbl[0].x, m268_spotTbl[0].y, m268_spotTbl[0].radius, m268_spotTbl[0].color);
    }
    m268_spotColorLayer.sprite->data->pat->data = m268_spotColorLayer.unk_04[m268_spotBufNo];
    m268_spotMaskLayer.sprite->data->pat->data = m268_spotMaskLayer.unk_04[m268_spotBufNo];
    m268_spotBufNo = (s16)(m268_spotBufNo + 1) % 3;
    m268_spotIntroTimer++;
    return 0;
}

s32 m268_SpotBeamUpdate(s32 x) {
    s16 i;

    m268_spotColorLayer.sprite->data->pat->data = m268_spotColorLayer.unk_04[0];
    if (m268_spotBeamTimer++ < 10) {
        m268_spotColorLayer.timer = 0;
    } else if (m268_spotBeamTimer < 30) {
        m268_spotColorLayer.timer = sindf((m268_spotBeamTimer - 10) * 4.5f) * 128.0f;
        HuSprTPLvlSet(m268_spotColorLayer.group, 0, m268_spotColorLayer.timer);
    } else if (m268_spotBeamTimer >= 40) {
        if (m268_spotBeamTimer < 90) {
            for (i = 0; i < 5; i++) {
                m268_SpotLineDraw(x, -100, x + (m268_spotBeamTimer - 40) + i, 240);
                m268_SpotLineDraw(x, -100, x - (m268_spotBeamTimer - 40) - i, 240);
            }
            m268_spotBeamTimer += 4;
        } else {
            return 1;
        }
    }
    return 0;
}

void m268_SpotDispOff(void) {
    HuSprDispOff(m268_spotColorLayer.group, 0);
    HuSprDispOff(m268_spotMaskLayer.group, 0);
    m268_spotColorLayer.sprite->data->pat->data =
        m268_spotColorLayer.unk_04[0];
    m268_spotMaskLayer.sprite->data->pat->data =
        m268_spotMaskLayer.unk_04[0];
}

s16 m268_SpotSprCreate(s32 dataNum, s32 attr, s32 priority, s32 tpLvl) {
    s16 sprite;
    s16 group;

    sprite = HuSprAnimDataRead(dataNum);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, attr | HUSPR_ATTR_XLU);
    HuSprPriSet(group, 0, priority);
    HuSprPosSet(group, 0, 160, 120);
    HuSprTPLvlSet(group, 0, tpLvl);
    return group;
}

void m268_SpotLayerInit(void) {
    s16 *pal;

    m268_spotColorLayer.group = m268_SpotSprCreate(0x650005, HUSPR_ATTR_NONE, 10, 128);
    m268_spotColorLayer.sprite = HuSprGet(m268_spotColorLayer.group, 0);
    m268_spotColorLayer.unk_04[0] = m268_spotColorLayer.sprite->data->pat->data;
    pal = m268_spotColorLayer.sprite->data->pal;
    m268_spotColorLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m268_spotColorLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;

    m268_spotMaskLayer.group = m268_SpotSprCreate(0x650005, HUSPR_ATTR_NONE, 10, 256);
    m268_spotMaskLayer.sprite = HuSprGet(m268_spotMaskLayer.group, 0);
    m268_spotMaskLayer.unk_04[0] = m268_spotMaskLayer.sprite->data->pat->data;
    pal = m268_spotMaskLayer.sprite->data->pal;
    m268_spotMaskLayer.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    m268_spotMaskLayer.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x0000;
}

void m268_SpotLayerClear(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = m268_spotColorLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = m268_spotMaskLayer.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

void m268_SpotErase(s16 active, s16 x, s16 y, s16 radius) {
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    if ((active == 0) | (radius < 1)) {
        return;
    }
    pixels = (u8 *)m268_spotColorLayer.unk_04[m268_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    mask = (u8 *)m268_spotMaskLayer.unk_04[m268_spotBufNo] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
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

void m268_SpotDraw(s16 active, s16 x, s16 y, s16 color) {
    m268_SpotDrawEx(active, x, y, 45, color);
}

void m268_SpotDrawEx(s16 active, s16 x, s16 y, s16 radius, s16 color) {
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
        pixels = (u8 *)m268_spotColorLayer.unk_04[m268_spotBufNo] + (x - radius) / 2 + py * 160;
        mask = (u8 *)m268_spotMaskLayer.unk_04[m268_spotBufNo] + (x - radius) / 2 + py * 160;
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

void m268_SpotLineDraw(s16 x0, s16 y0, s16 x1, s16 y1) {
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
                pixels = (u8 *)m268_spotColorLayer.unk_04[m268_spotBufNo] + x0 / 2 + y0 * 160;
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
                pixels = (u8 *)m268_spotColorLayer.unk_04[m268_spotBufNo] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    }
}
