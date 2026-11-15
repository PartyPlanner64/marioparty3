#include "common.h"
#include "game_guys_lucky_7.h"

typedef struct GameGuysLucky7Banner { // 0x14 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
} GameGuysLucky7Banner;

typedef struct GameGuysLucky7Ring { // 0x18 bytes
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 radius;
    /* 0x0A */ s16 freqX;
    /* 0x0C */ s16 freqY;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 speed;
} GameGuysLucky7Ring;

typedef struct GameGuysLucky7RingHistory { // 0x20 bytes
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 radius[4];
} GameGuysLucky7RingHistory;

typedef struct GameGuysLucky7RingFreq {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} GameGuysLucky7RingFreq;

s16 D_8010D300_game_guys_lucky_7 = 0;   // intro timer
s16 D_8010D302_game_guys_lucky_7 = 120; // intro start y
s16 D_8010D304_game_guys_lucky_7 = 0;   // outro timer

GameGuysLucky7Ring D_8010D810_game_guys_lucky_7[3] BSS;
s16 D_8010D858_game_guys_lucky_7 BSS;                          // center x
s16 D_8010D85A_game_guys_lucky_7 BSS;                          // center y
s16 D_8010D85C_game_guys_lucky_7 BSS;                          // radius
s16 D_8010D85E_game_guys_lucky_7 BSS;                          // target x
s16 D_8010D860_game_guys_lucky_7 BSS;                          // target y
u8 D_8010D864_game_guys_lucky_7[4] BSS;                        /* Unreferenced. */
GameGuysLucky7RingHistory D_8010D868_game_guys_lucky_7[3] BSS; // per-buffer ring state
u8 D_8010D8C8_game_guys_lucky_7[8] BSS;                        /* Unreferenced. */
GameGuysLucky7Banner D_8010D8D0_game_guys_lucky_7 BSS;
s16 D_8010D8E4_game_guys_lucky_7 BSS; // current buffer index
GameGuysLucky7Banner D_8010D8E8_game_guys_lucky_7 BSS;

void func_8010C97C_game_guys_lucky_7(void);
void func_8010CAE0_game_guys_lucky_7(void);
void func_8010CB70_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 radius);
void func_8010CCCC_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 color);
void func_8010CD0C_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 radius, s16 color);
void func_8010CF04_game_guys_lucky_7(s16 x0, s16 y0, s16 x1, s16 y1);

void func_8010B830_game_guys_lucky_7(s16 x, s16 y) {
    s16 i;
    u8 pattern;
    GameGuysLucky7RingFreq freqs[3] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };

    D_8010D858_game_guys_lucky_7 = 160;
    D_8010D85A_game_guys_lucky_7 = 120;
    D_8010D85C_game_guys_lucky_7 = 95;
    D_8010D85E_game_guys_lucky_7 = x;
    D_8010D860_game_guys_lucky_7 = y;
    pattern = rand8() % 3;
    for (i = 0; i < 3; i++) {
        D_8010D810_game_guys_lucky_7[i].active = 0;
        D_8010D810_game_guys_lucky_7[i].freqX = freqs[pattern].x;
        D_8010D810_game_guys_lucky_7[i].freqY = freqs[pattern].y;
        D_8010D810_game_guys_lucky_7[i].speed = 1.5f;
        if (pattern == 0) {
            D_8010D810_game_guys_lucky_7[i].speed = 1.75f;
        }
        D_8010D810_game_guys_lucky_7[i].angle = i * 120;
        D_8010D810_game_guys_lucky_7[i].x =
            D_8010D858_game_guys_lucky_7 + cosdf(D_8010D810_game_guys_lucky_7[i].freqX * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
        D_8010D810_game_guys_lucky_7[i].y =
            D_8010D85A_game_guys_lucky_7 + sindf(D_8010D810_game_guys_lucky_7[i].freqY * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
        D_8010D810_game_guys_lucky_7[i].radius = 0;
    }
    D_8010D810_game_guys_lucky_7[0].color = 1;
    D_8010D810_game_guys_lucky_7[1].color = 2;
    D_8010D810_game_guys_lucky_7[2].color = 4;
    D_8010D8E8_game_guys_lucky_7.timer = 128;
    D_8010D8D0_game_guys_lucky_7.timer = 256;
    func_8010C97C_game_guys_lucky_7();
    func_8010CAE0_game_guys_lucky_7();
    D_8010D8E4_game_guys_lucky_7 = 0;
}

void func_8010BAFC_game_guys_lucky_7(void) {
    func_8010CAE0_game_guys_lucky_7();
    D_8010D8E4_game_guys_lucky_7 = 0;
    D_8010D8E8_game_guys_lucky_7.timer = 0;
    HuSprTPLvlSet(D_8010D8E8_game_guys_lucky_7.group, 0, 0);
    HuSprAttrReset(D_8010D8E8_game_guys_lucky_7.group, 0, 0xFFFF);
    HuSprAttrSet(D_8010D8E8_game_guys_lucky_7.group, 0, 0x1000);
    D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00 =
        D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7];
}

s16 func_8010BB88_game_guys_lucky_7(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (D_8010D300_game_guys_lucky_7 >= 5) {
        if (D_8010D300_game_guys_lucky_7 < 15) {
            for (i = 0; i < 3; i++) {
                D_8010D810_game_guys_lucky_7[i].active = 1;
                D_8010D810_game_guys_lucky_7[i].radius = sindf((D_8010D300_game_guys_lucky_7 - 5) * 9.0f) * 45.0f;
            }
        } else if (D_8010D300_game_guys_lucky_7 < 20) {
            for (i = 0; i < 3; i++) {
                D_8010D810_game_guys_lucky_7[i].radius = 45;
            }
        } else if (D_8010D300_game_guys_lucky_7 < 47) {
            for (i = 0; i < 3; i++) {
                D_8010D810_game_guys_lucky_7[i].angle += D_8010D810_game_guys_lucky_7[i].speed;
                if (D_8010D810_game_guys_lucky_7[i].angle >= 360.0f) {
                    D_8010D810_game_guys_lucky_7[i].angle -= 360.0f;
                }
                if (D_8010D810_game_guys_lucky_7[i].angle < 0.0f) {
                    D_8010D810_game_guys_lucky_7[i].angle += 360.0f;
                }
                D_8010D810_game_guys_lucky_7[i].x = D_8010D858_game_guys_lucky_7 +
                                                    cosdf(D_8010D810_game_guys_lucky_7[i].freqX * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
                D_8010D810_game_guys_lucky_7[i].y = D_8010D85A_game_guys_lucky_7 +
                                                    sindf(D_8010D810_game_guys_lucky_7[i].freqY * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
            }
        } else if (D_8010D300_game_guys_lucky_7 < 80) {
            if (D_8010D85C_game_guys_lucky_7 > 0) {
                if ((D_8010D85C_game_guys_lucky_7 -= 3) <= 0) {
                    D_8010D85C_game_guys_lucky_7 = 0;
                }
            }
            D_8010D85A_game_guys_lucky_7 =
                D_8010D302_game_guys_lucky_7 - sindf((D_8010D300_game_guys_lucky_7 - 47) * 2.7272727f) *
                                                   (D_8010D302_game_guys_lucky_7 - D_8010D860_game_guys_lucky_7);
            if (D_8010D300_game_guys_lucky_7 == 79) {
                D_8010D85A_game_guys_lucky_7 = D_8010D860_game_guys_lucky_7;
            }
            for (i = 0; i < 3; i++) {
                D_8010D810_game_guys_lucky_7[i].angle += D_8010D810_game_guys_lucky_7[i].speed;
                if (D_8010D810_game_guys_lucky_7[i].angle >= 360.0f) {
                    D_8010D810_game_guys_lucky_7[i].angle -= 360.0f;
                }
                if (D_8010D810_game_guys_lucky_7[i].angle < 0.0f) {
                    D_8010D810_game_guys_lucky_7[i].angle += 360.0f;
                }
                D_8010D810_game_guys_lucky_7[i].x = D_8010D858_game_guys_lucky_7 +
                                                    cosdf(D_8010D810_game_guys_lucky_7[i].freqX * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
                D_8010D810_game_guys_lucky_7[i].y = D_8010D85A_game_guys_lucky_7 +
                                                    sindf(D_8010D810_game_guys_lucky_7[i].freqY * D_8010D810_game_guys_lucky_7[i].angle) * D_8010D85C_game_guys_lucky_7;
            }
        } else if (D_8010D300_game_guys_lucky_7 < 90) {
            for (i = 1; i < 3; i++) {
                D_8010D810_game_guys_lucky_7[i].active = 0;
            }
            D_8010D810_game_guys_lucky_7[0].color = 7;
        } else if (D_8010D300_game_guys_lucky_7 >= 120) {
            func_8010C824_game_guys_lucky_7();
            return 1;
        } else {
            D_8010D810_game_guys_lucky_7[0].radius = sindf((D_8010D300_game_guys_lucky_7 - 90) * 3.0f) * 50.0f + 45.0f;
            D_8010D8E8_game_guys_lucky_7.timer = 128.0f - sindf((D_8010D300_game_guys_lucky_7 - 90) * 3.0f) * 128.0f;
            D_8010D8D0_game_guys_lucky_7.timer = 256.0f - sindf((D_8010D300_game_guys_lucky_7 - 90) * 3.0f) * 256.0f;
        }
    }
    if (D_8010D300_game_guys_lucky_7 == 15) {
        HuAudFXPlay(0x51F);
    }
    if (D_8010D300_game_guys_lucky_7 == 90) {
        func_8004AB0C_main(30);
        HuAudSeqPlay(0x43);
    }
    if (D_8010D300_game_guys_lucky_7 == 100) {
        HuAudFXPlay(0x2A1);
    }
    if (D_8010D8E8_game_guys_lucky_7.timer <= 0) {
        D_8010D8E8_game_guys_lucky_7.timer = 0;
    }
    HuSprTPLvlSet(D_8010D8E8_game_guys_lucky_7.group, 0, D_8010D8E8_game_guys_lucky_7.timer);
    if (D_8010D8D0_game_guys_lucky_7.timer <= 0) {
        D_8010D8D0_game_guys_lucky_7.timer = 0;
    }
    HuSprTPLvlSet(D_8010D8D0_game_guys_lucky_7.group, 0, D_8010D8D0_game_guys_lucky_7.timer);
    if (D_8010D300_game_guys_lucky_7 < 90) {
        for (i = 0; i < 3; i++) {
            func_8010CB70_game_guys_lucky_7(D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].active[i], D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].x[i],
                                            D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].y[i], D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].radius[i]);
            D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].active[i] = D_8010D810_game_guys_lucky_7[i].active;
            D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].x[i] = D_8010D810_game_guys_lucky_7[i].x;
            D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].y[i] = D_8010D810_game_guys_lucky_7[i].y;
            D_8010D868_game_guys_lucky_7[D_8010D8E4_game_guys_lucky_7].radius[i] = D_8010D810_game_guys_lucky_7[i].radius;
        }
    }
    if (D_8010D300_game_guys_lucky_7 < 20) {
        for (i = 0; i < 3; i++) {
            func_8010CD0C_game_guys_lucky_7(D_8010D810_game_guys_lucky_7[i].active, D_8010D810_game_guys_lucky_7[i].x, D_8010D810_game_guys_lucky_7[i].y, D_8010D810_game_guys_lucky_7[i].radius, D_8010D810_game_guys_lucky_7[i].color);
        }
    } else if (D_8010D300_game_guys_lucky_7 < 81) {
        for (i = 0; i < 3; i++) {
            func_8010CCCC_game_guys_lucky_7(D_8010D810_game_guys_lucky_7[i].active, D_8010D810_game_guys_lucky_7[i].x, D_8010D810_game_guys_lucky_7[i].y, D_8010D810_game_guys_lucky_7[i].color);
        }
    } else {
        func_8010CD0C_game_guys_lucky_7(D_8010D810_game_guys_lucky_7[0].active, D_8010D810_game_guys_lucky_7[0].x, D_8010D810_game_guys_lucky_7[0].y, D_8010D810_game_guys_lucky_7[0].radius, D_8010D810_game_guys_lucky_7[0].color);
    }
    D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00 = D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7];
    D_8010D8D0_game_guys_lucky_7.sprite->unk_84->unk00->unk00 = D_8010D8D0_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7];
    D_8010D8E4_game_guys_lucky_7 = (s16)(D_8010D8E4_game_guys_lucky_7 + 1) % 3;
    D_8010D300_game_guys_lucky_7++;
    return 0;
}

s32 func_8010C670_game_guys_lucky_7(s32 x) {
    s16 i;

    D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00 = D_8010D8E8_game_guys_lucky_7.unk_04[0];
    if (D_8010D304_game_guys_lucky_7++ < 10) {
        D_8010D8E8_game_guys_lucky_7.timer = 0;
    } else if (D_8010D304_game_guys_lucky_7 < 30) {
        D_8010D8E8_game_guys_lucky_7.timer = sindf((D_8010D304_game_guys_lucky_7 - 10) * 4.5f) * 128.0f;
        HuSprTPLvlSet(D_8010D8E8_game_guys_lucky_7.group, 0, D_8010D8E8_game_guys_lucky_7.timer);
    } else if (D_8010D304_game_guys_lucky_7 >= 40) {
        if (D_8010D304_game_guys_lucky_7 < 90) {
            for (i = 0; i < 5; i++) {
                func_8010CF04_game_guys_lucky_7(x, -100, x + (D_8010D304_game_guys_lucky_7 - 40) + i, 240);
                func_8010CF04_game_guys_lucky_7(x, -100, x - (D_8010D304_game_guys_lucky_7 - 40) - i, 240);
            }
            D_8010D304_game_guys_lucky_7 += 4;
        } else {
            return 1;
        }
    }
    return 0;
}

void func_8010C824_game_guys_lucky_7(void) {
    HuSprDispOff(D_8010D8E8_game_guys_lucky_7.group, 0);
    HuSprDispOff(D_8010D8D0_game_guys_lucky_7.group, 0);
    D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00 =
        D_8010D8E8_game_guys_lucky_7.unk_04[0];
    D_8010D8D0_game_guys_lucky_7.sprite->unk_84->unk00->unk00 =
        D_8010D8D0_game_guys_lucky_7.unk_04[0];
}

s16 func_8010C8A8_game_guys_lucky_7(s32 dataNum, s32 attr, s32 priority, s32 tpLvl) {
    s16 sprite;
    s16 group;

    sprite = func_8000B838_main(dataNum);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, attr | 0x1000);
    HuSprPriSet(group, 0, priority);
    HuSprPosSet(group, 0, 160, 120);
    HuSprTPLvlSet(group, 0, tpLvl);
    return group;
}

void func_8010C97C_game_guys_lucky_7(void) {
    s16 *pal;

    D_8010D8E8_game_guys_lucky_7.group = func_8010C8A8_game_guys_lucky_7(0x64000A, 0, 10, 128);
    D_8010D8E8_game_guys_lucky_7.sprite = HuSprGet(D_8010D8E8_game_guys_lucky_7.group, 0);
    D_8010D8E8_game_guys_lucky_7.unk_04[0] = D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk00->unk00;
    pal = D_8010D8E8_game_guys_lucky_7.sprite->unk_84->unk0C;
    D_8010D8E8_game_guys_lucky_7.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010D8E8_game_guys_lucky_7.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;

    D_8010D8D0_game_guys_lucky_7.group = func_8010C8A8_game_guys_lucky_7(0x64000A, 0, 10, 256);
    D_8010D8D0_game_guys_lucky_7.sprite = HuSprGet(D_8010D8D0_game_guys_lucky_7.group, 0);
    D_8010D8D0_game_guys_lucky_7.unk_04[0] = D_8010D8D0_game_guys_lucky_7.sprite->unk_84->unk00->unk00;
    pal = D_8010D8D0_game_guys_lucky_7.sprite->unk_84->unk0C;
    D_8010D8D0_game_guys_lucky_7.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010D8D0_game_guys_lucky_7.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x0000;
}

void func_8010CAE0_game_guys_lucky_7(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = D_8010D8E8_game_guys_lucky_7.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = D_8010D8D0_game_guys_lucky_7.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

void func_8010CB70_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 radius) {
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    if ((active == 0) | (radius < 1)) {
        return;
    }
    pixels = (u8 *)D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    mask = (u8 *)D_8010D8D0_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
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

void func_8010CCCC_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 color) {
    func_8010CD0C_game_guys_lucky_7(active, x, y, 45, color);
}

void func_8010CD0C_game_guys_lucky_7(s16 active, s16 x, s16 y, s16 radius, s16 color) {
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
        pixels = (u8 *)D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + (x - radius) / 2 + py * 160;
        mask = (u8 *)D_8010D8D0_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + (x - radius) / 2 + py * 160;
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

void func_8010CF04_game_guys_lucky_7(s16 x0, s16 y0, s16 x1, s16 y1) {
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
                pixels = (u8 *)D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + x0 / 2 + y0 * 160;
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
                pixels = (u8 *)D_8010D8E8_game_guys_lucky_7.unk_04[D_8010D8E4_game_guys_lucky_7] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    }
}
