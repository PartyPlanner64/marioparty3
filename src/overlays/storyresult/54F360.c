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

typedef struct StoryResultSprDef {
    /* 0x00 */ s32 file;
    /* 0x04 */ StoryResultPos pos;
} StoryResultSprDef; // sizeof 0x8

typedef struct StoryResultWinDef {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} StoryResultWinDef; // sizeof 0x8

void func_80107920_storyresult(void);
Process *func_8010832C_storyresult(s16 *arg0, s16 arg1);
void func_80108F0C_storyresult(void);
s16 func_8010A370_storyresult(s16 arg0);
Process *func_8010A4A4_storyresult(u16 arg0, s16 arg1);
s32 func_8010A558_storyresult(Process *prc);
s16 func_8010A5C4_storyresult(s16 playerIdx);
s16 func_8010A738_storyresult(s16 playerIdx);
s16 func_8010A7B0_storyresult(s16 playerIdx);
s16 func_8010A7EC_storyresult(void);
extern StoryResultSprDef D_8010A9E4_storyresult[15];
extern s32 D_8010AA5C_storyresult[];
extern s32 D_8010AA78_storyresult[];
extern u32 D_8010AA90_storyresult[];
extern u32 D_8010AAA8_storyresult[];
extern u32 D_8010AAB8_storyresult[];
extern u8 D_8010AAD4_storyresult[];
extern u8 D_8010AAE0_storyresult[];
extern u8 D_8010AAEC_storyresult[][3];
extern StoryResultWinDef D_8010AB04_storyresult[6];
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
extern s16 winPrio;
extern s32 D_8010A940_storyresult[];
extern u32 D_8010A974_storyresult[];
extern u32 D_8010A9A8_storyresult[];
extern u8 D_8010A9C8_storyresult[];
extern u16 D_8010A9D8_storyresult[];

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

void func_80107204_storyresult(void) {
    StoryResultWork *data;
    s16 rank;
    s16 x;
    s16 y;
    s16 sprite;
    s16 cursor;
    s16 window;
    s16 i;
    s32 confirmed;

    rank = func_8010A7EC_storyresult();
    if (GwStory.unk0 < 12) {
        GwStory.progress.fields.unk3[GwStory.unk0] = rank;
    } else {
        GwStory.progress.fields.unkF = rank;
    }
    x = 160;
    y = 120;
    data = func_8010A4A4_storyresult(2, GwStory.unk1)->user_data;
    HuPrcVSleep();
    D_8010A912_storyresult = 1;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(D_8010A940_storyresult[GwStory.unk0]);
    func_800E8180_name_81(1000.0f, 10000.0f);
    if (GwStory.unk0 == 12) {
        sprite = espEntry(func_8000B838_main(0x1D0012), 0, 0);
        espAttrSet(sprite, 0x4000);
        espPriSet(sprite, 0xF001);
        espPosSet(sprite, 160, 120);
    }
    sprite = espEntry(func_8000B838_main(0x140064), 0, 1);
    espAttrSet(sprite, 0x4000);
    espPriSet(sprite, 0xF000);
    espScaleSet(sprite, 10.0f, 8.0f);
    espPosSet(sprite, x, y);
    espColorSet(sprite, 0, 0, 0);
    espTPLvlSet(sprite, 64);
    D_800CD280_main = 1;

    cursor = espEntry(func_8000B838_main(0x150001), 0, 1);
    espPriSet(cursor, 600);
    espPosSet(cursor, x, y + 84);
    espTPLvlSet(cursor, 0);
    espDispOff(cursor);

    window = HuWinCreate(x - 112, y + 67, 224, 42, 0, 12);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 0);
    HuWinPriSet(window, 1);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_8005C154_main(window, 64, 64, 64);
    HuWinBGColSet(window, 0, 0, 0);
    HuWinMesColSet(window, 7);
    func_8005BF70_main(window, 255);

    if (GwStory.unk0 >= 12) {
        HuAudSeqPlay(0x26);
        D_8010A914_storyresult = 0;
    }
    WipeCreateIn(D_8010AC2A_storyresult, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    data->state = 1;
    espDispOn(cursor);
    for (i = 0; i <= 256; i += 36) {
        espTPLvlSet(cursor, i);
        HuPrcVSleep();
    }
    while (data->state != 0) {
        HuPrcVSleep();
    }
    HuWinInsertMesSet(window, D_8010A974_storyresult[GwStory.unk0], 0);
    HuWinInsertMesSet(window, D_8010A9A8_storyresult[rank], 1);
    HuWinMesSet(window, 0x6126, -1, -1);
    while (HuWinStatGet(window)) {
        HuPrcVSleep();
    }

    if (GwStory.unk0 >= 12) {
        omOvlHisChg(0, 0x7D, 1, 0x4090);
        omovlhisidx++;
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = 14;
    } else {
        if (GwStory.unk0 == 11) {
            _SetFlag(0x2F);
            _SetFlag(0x31);
        } else if (GwStory.unk0 == 10) {
            _SetFlag(0x2E);
            _SetFlag(0x30);
        }
        GwStory.unk0++;
        if (GwStory.unk0 >= 13) {
            GwStory.unk0 = 12;
        }
        if (D_8010A924_storyresult[GwStory.unk0] == 1) {
            GwSystem.playMode = 6;
        } else {
            GwSystem.playMode = 5;
        }
        D_8010ABE2_storyresult = 1;
        D_8010AC32_storyresult = 0x75;
        D_8010AC30_storyresult = 0;
        D_800CE20A_main = D_8010A9C8_storyresult[GwStory.unk0];
        while (TRUE) {
            data->state = 10;
            do {
                HuPrcVSleep();
            } while (data->state != 0);
            HuWinMesSet(window, 0x6127, -1, -1);
            while (HuWinStatGet(window)) {
                HuPrcVSleep();
            }
            if (HuWinChoiceGet(window, 0, 0) == 0) {
                confirmed = TRUE;
                if (func_80106FF0_storyresult() != 0) {
                    data->state = 11;
                    do {
                        HuPrcVSleep();
                    } while (data->state != 0);
                    HuWinMesSet(window, 0x6129, -1, -1);
                    while (HuWinStatGet(window)) {
                        HuPrcVSleep();
                    }
                    if (HuWinChoiceGet(window, 0, 0) != 0) {
                        confirmed = FALSE;
                    }
                }
                HuWinHomeClear(window);
                if (!confirmed) {
                    continue;
                }
                HuWinMesSet(window, 0x612C, -1, -1);
                HuPrcVSleep();
                func_80107030_storyresult();
                data->state = 10;
                HuWinMesSet(window, 0x612A, -1, -1);
                while (HuWinStatGet(window)) {
                    HuPrcVSleep();
                }
                break;
            }
            HuWinHomeClear(window);
            break;
        }
    }
    D_8010A910_storyresult = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80107920_storyresult(void) {
    s16 sprites[2];
    StoryResultPos pos[2];
    s16 *result;
    StoryResultWork *data;
    s16 cursorAnim;
    s16 arrowAnim;
    s16 window;
    s16 cursor;
    Process *prc;
    s16 i;
    s16 selection;
    s16 speed;
    s16 angle;
    s16 count;
    f32 offset;
    s32 confirmed;

    result = HuPrcCurrentGet()->user_data;

    cursorAnim = func_8000B838_main(0x150001);
    cursor = espEntry(cursorAnim, 0, 1);
    espPriSet(cursor, 600);
    espPosSet(cursor, 160, 204);
    espTPLvlSet(cursor, 0);
    espDispOff(cursor);

    window = HuWinCreate(48, 187, 224, 42, 0, 12);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 0);
    HuWinPriSet(window, 1);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_8005C154_main(window, 64, 64, 64);
    HuWinBGColSet(window, 0, 0, 0);
    HuWinMesColSet(window, 7);
    func_8005BF70_main(window, 255);

    pos[0].x = 25;
    pos[1].x = 295;
    pos[0].y = pos[1].y = 130;
    arrowAnim = func_8000B838_main(0x150003);
    for (i = 0; i < 2; i++) {
        sprites[i] = espEntry(arrowAnim, 0, 1);
        espPriSet(sprites[i], 100);
        espPosSet(sprites[i], pos[i].x, pos[i].y);
        espTPLvlSet(sprites[i], 0);
        espDispOff(sprites[i]);
    }
    espAttrSet(sprites[1], 1);

    prc = func_8010A4A4_storyresult(1, -1);
    if (prc == NULL) {
        *result = -3;
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    data = prc->user_data;
    HuPrcVSleep();
    data->state = 1;
    espDispOn(cursor);
    espDispOn(sprites[0]);
    espDispOn(sprites[1]);
    for (i = 0; i <= 256; i += 36) {
        espTPLvlSet(cursor, i);
        espTPLvlSet(sprites[0], i);
        espTPLvlSet(sprites[1], i);
        HuPrcVSleep();
    }

    HuWinMesSet(window, 0x6128, -1, -1);
    HuPrcVSleep();
    selection = 0;
    angle = 0;
    speed = 0;
    while (TRUE) {
        if (D_800D5558_main[D_8010ABE0_storyresult] & 0x8000) {
            HuAudFXPlay(2);
            break;
        }
        if (data->state == 0) {
            if ((D_800D5558_main[D_8010ABE0_storyresult] & 0x100) || D_800CBB6E_main[D_8010ABE0_storyresult] >= 31) {
                HuAudFXPlay(1);
                data->state = 3;
                angle = 180;
                speed = -22;
                selection = 1;
            } else if ((D_800D5558_main[D_8010ABE0_storyresult] & 0x200) ||
                       D_800CBB6E_main[D_8010ABE0_storyresult] < -30) {
                HuAudFXPlay(1);
                data->state = 4;
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

    HuWinHomeClear(window);
    for (i = 256; i >= 0; i -= 36) {
        espTPLvlSet(sprites[0], i);
        espTPLvlSet(sprites[1], i);
        HuPrcVSleep();
    }
    espDispOff(sprites[0]);
    espDispOff(sprites[1]);
    if (GwStory.unk2 >= 2) {
        _SetFlag(0x2D);
    }
    _ClearFlag(0x28);
    _ClearFlag(0x18);

    while (TRUE) {
        data->state = 10;
        do {
            HuPrcVSleep();
        } while (data->state != 0);
        HuWinMesSet(window, 0x6127, -1, -1);
        while (HuWinStatGet(window)) {
            HuPrcVSleep();
        }
        if (HuWinChoiceGet(window, 0, 0) == 0) {
            confirmed = TRUE;
            count = func_801070D8_storyresult();
            if (count != 0) {
                if (count >= 13) {
                    HuWinMesSet(window, 0x612D, -1, -1);
                    while (HuWinStatGet(window)) {
                        HuPrcVSleep();
                    }
                    data->state = 9;
                    do {
                        HuPrcVSleep();
                    } while (data->state != 0);
                    HuWinMesSet(window, 0x612E, -1, -1);
                } else {
                    data->state = 9;
                    do {
                        HuPrcVSleep();
                    } while (data->state != 0);
                    HuWinMesSet(window, 0x6129, -1, -1);
                }
                while (HuWinStatGet(window)) {
                    HuPrcVSleep();
                }
                if (HuWinChoiceGet(window, 0, 0) != 0) {
                    confirmed = FALSE;
                }
            }
            HuWinHomeClear(window);
            if (!confirmed) {
                continue;
            }
            HuWinMesSet(window, 0x612C, -1, -1);
            HuPrcVSleep();
            if (GwStory.unk1 < 6) {
                _SetFlag(D_8010A9D8_storyresult[GwStory.unk1]);
            }
            func_80107140_storyresult();
            data->state = 10;
            HuWinMesSet(window, 0x612A, -1, -1);
            while (HuWinStatGet(window)) {
                HuPrcVSleep();
            }
        }
        HuWinHomeClear(window);
        break;
    }
    D_8010ABE2_storyresult = 3;
    D_8010AC32_storyresult = 0x7C;
    D_8010AC30_storyresult = 6;
    *result = -1;
    data->state = 2;
    for (i = 256; i >= 0; i -= 36) {
        espTPLvlSet(cursor, i);
        HuPrcVSleep();
    }
    espDispOff(cursor);
    while (data->state != 0) {
        HuPrcVSleep();
    }
    func_8010A558_storyresult(prc);
    espKill(cursor);
    espKill(sprites[0]);
    espKill(sprites[1]);
    HuSprAnimKill(cursorAnim);
    HuSprAnimKill(arrowAnim);
    HuWinKill(window);
    *result = -3;
    while (TRUE) {
        HuPrcVSleep();
    }
}

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

void func_801083A4_storyresult(void) {
    s16 status;
    u16 sprite;
    s16 value;
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
    for (j = 0; j < ARRAY_COUNT(GwStory.unk58); j++) {
        GwStory.unk5E[j] = j & 3;
        GwStory.unk58[j] = 4;
        for (i = 0; i < ARRAY_COUNT(GwStory.unk10[j]); i++) {
            GwStory.unk10[j][i] = 4;
        }
    }
    // i is reused to hold the button flags.
    i = 0;
    if (D_800CDA7C_main[0] & 4) {
        i |= 1;
    }
    if (D_800CDA7C_main[0] & 1) {
        i |= 2;
    }
    if (D_800CDA7C_main[0] & 8) {
        i |= 4;
    }
    func_8010832C_storyresult(&status, i);
    while (status >= 0) {
        HuPrcVSleep();
    }
    D_8010A910_storyresult = 1;
    while (1) {
        HuPrcVSleep();
    }
}

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

void func_80108F0C_storyresult(void) {
    s16 color[3];
    s16 step[3];
    u32 msgs[4];
    StoryResultWork *data;
    s16 *rankWin;
    StoryResultPanel *work;
    StoryResultElem *elem;
    StoryResultSprDef *def;
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
    s16 winAlpha;
    s16 winFadeSpeed;
    s16 hasRank;
    s16 colorFrames;
    s16 colorTimer;
    s16 colorCycle;
    s16 page;
    s16 prevPage;
    s16 pageChanging;
    s16 rank;
    s16 curRank;
    s16 hasPartner;
    s16 partnerFading;
    s16 graphic;
    s16 x;
    s16 y;
    s16 member;
    s16 markX;
    u32 msg;
    s32 temp; // sprite priority during setup, fade-finished flag in the main loop
    s32 i;

    data = HuPrcCurrentGet()->user_data;
    work = HuMemAllocTag(sizeof(StoryResultPanel), 0x7918);
    memset(work, 0, sizeof(StoryResultPanel));
    work->data = data;
    page = 0;
    prevPage = 0;
    elem = work->elems;
    hasPartner = 0;
    for (i = 0; i < 24; i++, elem++) {
        elem->unk04 = -1;
        elem->unk06 = 256;
        elem->unk08 = 0;
        elem->unk0A = 0;
    }
    work->unk14A = -1;
    work->unk148 = -1;
    rank = -1;
    msgs[3] = 0;
    switch (data->unk_00) {
        case 0:
        default:
            hasRank = 1;
            rank = func_8010A370_storyresult(data->unk_02);
            msgs[0] = 0x6101;
            msgs[2] = D_8010AAA8_storyresult[GwStory.unk5E[data->unk_02]];
            msgs[3] = D_8010AAB8_storyresult[rank];
            work->unk124 = data->unk_02;
            break;
        case 1:
            data->unk_02 = GwStory.unk1;
            hasRank = 1;
            rank = func_8010A370_storyresult(-1);
            msgs[0] = 0x6101;
            msgs[2] = D_8010AAA8_storyresult[GwStory.unk2];
            msgs[3] = D_8010AAB8_storyresult[rank];
            work->unk124 = -1;
            break;
        case 2:
            if (func_80106FF0_storyresult() != 0) {
                hasPartner = 1;
            }
            data->unk_02 = GwStory.unk1;
            msgs[0] = 0x6100;
            msgs[2] = D_8010AAA8_storyresult[GwStory.unk2];
            work->unk124 = -1;
            hasRank = 1;
            if (GwStory.unk0 == 12) {
                rank = func_8010A370_storyresult(-1);
                page = 2;
                prevPage = 2;
            } else {
                prevPage = page = D_8010A924_storyresult[GwStory.unk0];
            }
            break;
    }
    msgs[1] = D_8010AA90_storyresult[data->unk_02];

    group = HuSprGrpCreate(24, 0);
    member = 0;
    def = D_8010A9E4_storyresult;
    for (elem = work->elems, i = 0; i < ARRAY_COUNTU(D_8010A9E4_storyresult); i++, member++, def++, elem++) {
        temp = 1200;
        graphic = func_8000B838_main(def->file);
        elem->unk04 = graphic;
        elem->pos = def->pos;
        x = elem->pos.x + data->x;
        y = elem->pos.y + data->y;
        if (i >= 2) {
            temp = 1199;
        }
        func_801085E8_storyresult(group, member, graphic, temp, x, y);
    }
    HuSprScaleSet(group, 1, 1.0f, 1.02f);
    // Both branches are identical, but the branch is needed to match.
    if (data->unk_00 == 2) {
        HuSprColorSet(group, 1, 0, 0, 0);
        HuSprTPLvlSet(group, 1, 255);
    } else {
        HuSprColorSet(group, 1, 0, 0, 0);
        HuSprTPLvlSet(group, 1, 255);
    }
    work->elems[1].unk06 = 255;
    work->group = group;

    graphic = func_8000B838_main(D_8010AA78_storyresult[data->unk_02]);
    work->elems[15].unk04 = graphic;
    work->elems[15].pos.x = -96;
    work->elems[15].pos.y = -74;
    x = work->elems[15].pos.x + data->x;
    y = work->elems[15].pos.y + data->y;
    func_801085E8_storyresult(group, 15, graphic, 1200, x, y);
    if (hasPartner) {
        graphic = func_8000B838_main(D_8010AA78_storyresult[GwStory.unk65]);
        work->elems[23].unk04 = graphic;
        work->elems[23].pos.x = -96;
        work->elems[23].pos.y = -74;
        x = work->elems[23].pos.x + data->x;
        y = work->elems[23].pos.y + data->y;
        func_801085E8_storyresult(group, 23, graphic, 1200, x, y);
    }
    for (gfx = work->graphics, i = 0; i < 4; i++, gfx++) {
        *gfx = func_8000B838_main(D_8010AA5C_storyresult[i]);
    }
    work->unk148 = HuSprGrpCreate(13, 0);
    work->unk14A = func_8000B838_main(0x15001D);
    y = data->y - 28;
    for (i = 0; i < 13; i++) {
        markX = data->x + (s16)(i * 12 - 24);
        func_801085E8_storyresult(work->unk148, i, work->unk14A, 1200, markX, y);
    }

    winPrio = 400;
    win = work->windows;
    flag = work->winFlags;
    x = data->x;
    y = data->y;
    for (i = 0; i < ARRAY_COUNTU(work->windows); i++, win++, flag++) {
        *win = HuWinCreate(x + D_8010AB04_storyresult[i].x, y + D_8010AB04_storyresult[i].y,
                           D_8010AB04_storyresult[i].w, D_8010AB04_storyresult[i].h, 0, 12);
        HuWinMesSpeedSet(*win, 0);
        HuWinBGTPLvlSet(*win, 0);
        HuWinMesPalSet(*win, 2, 255, 64, 64);
        HuWinMesPalSet(*win, 5, 0, 176, 192);
        HuWinMesPalSet(*win, 4, 96, 255, 64);
        HuWinMesPalSet(*win, 6, 255, 255, 64);
        func_8005C154_main(*win, 64, 64, 64);
        HuWinBGColSet(*win, 0, 0, 0);
        HuWinMesColSet(*win, 7);
        func_8005BF70_main(*win, 0);
        *flag = 0;
    }
    win = work->windows;
    flag = work->winFlags;
    HuWinMesSet(work->windows[0], msgs[0], -1, -1);
    HuWinMesSet(work->windows[1], msgs[1], -1, -1);
    HuWinMesSet(work->windows[2], msgs[2], -1, -1);
    work->winFlags[0] = work->winFlags[1] = work->winFlags[2] = 1;
    if (hasRank) {
        if (msgs[3] != 0) {
            HuWinMesSet(work->windows[3], msgs[3], -1, -1);
        }
        flag[3] = 1;
        HuWinMesPalSet(win[3], 7, D_8010AAEC_storyresult[rank][0], D_8010AAEC_storyresult[rank][1],
                       D_8010AAEC_storyresult[rank][2]);
    }
    HuWinMesSet(win[5], 0x6111, -1, -1);
    func_80108D34_storyresult(page, work);

    state = 0;
    work->unk14C = 0;
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
    partnerFading = 0;
    do {
        if ((state == 1 || state == 2) && work->winFlags[0] == 0) {
            data->state = 0;
        }
        if (fadeInWait) {
            if (sprFadeSpeed == 0 && winFadeSpeed == 0) {
                fadeInWait = 0;
                data->state = 0;
            }
        }
        if (pageChanging) {
            if (sprFadeSpeed == 0 && winFadeSpeed == 0) {
                pageChanging = 0;
                func_80108D34_storyresult(page, work);
                sprAlpha = 0;
                sprFadeSpeed = 51;
                winAlpha = 0;
                winFadeSpeed = 51;
                fadeInWait = 1;
                if (page >= 4) {
                    if (partnerFading) {
                        partnerFading = 0;
                        if (page == 6) {
                            elem = &work->elems[23];
                        } else {
                            elem = &work->elems[15];
                        }
                        elem->unk08 = 1;
                    }
                    msg = 0;
                    if (page == 5) {
                        HuWinMesSet(work->windows[0], msgs[0], -1, -1);
                        HuWinMesSet(work->windows[1], msgs[1], -1, -1);
                        HuWinMesSet(work->windows[2], msgs[2], -1, -1);
                        msg = msgs[3];
                        curRank = rank;
                    } else if (page == 4) {
                        curRank = func_8010A370_storyresult(GwStory.unk1);
                        HuWinMesSet(work->windows[2], D_8010AAA8_storyresult[GwStory.unk5E[GwStory.unk1]], -1, -1);
                        msg = 0;
                        if (curRank < 0) {
                            HuWinMesSet(work->windows[0], 0x6100, -1, -1);
                        } else {
                            HuWinMesSet(work->windows[0], 0x6101, -1, -1);
                            msg = D_8010AAB8_storyresult[curRank];
                        }
                    } else if (page == 6) {
                        curRank = func_8010A370_storyresult(-2);
                        HuWinMesSet(work->windows[1], D_8010AA90_storyresult[GwStory.unk65], -1, -1);
                        HuWinMesSet(work->windows[2], D_8010AAA8_storyresult[GwStory.unk66], -1, -1);
                        msg = 0;
                        if (curRank < 0) {
                            HuWinMesSet(work->windows[0], 0x6100, -1, -1);
                        } else {
                            HuWinMesSet(work->windows[0], 0x6101, -1, -1);
                            msg = D_8010AAB8_storyresult[curRank];
                        }
                    }
                    if (msg != 0) {
                        HuWinMesSet(work->windows[3], msg, -1, -1);
                        HuWinMesPalSet(work->windows[3], 7, D_8010AAEC_storyresult[curRank][0],
                                       D_8010AAEC_storyresult[curRank][1], D_8010AAEC_storyresult[curRank][2]);
                        if (curRank == 4) {
                            colorCycle = 1;
                            colorPtr = colorStart = D_8010AAD4_storyresult;
                            colorFrames = 6;
                        } else if (curRank == 3) {
                            colorCycle = 1;
                            colorPtr = colorStart = D_8010AAE0_storyresult;
                            colorFrames = 8;
                        }
                    } else {
                        HuWinHomeClear(work->windows[3]);
                    }
                    for (i = 0; i < 4; i++) {
                        work->winFlags[i] = 1;
                    }
                }
            }
        } else if (prevPage != page) {
            sprAlpha = 255;
            sprFadeSpeed = -51;
            winAlpha = 255;
            winFadeSpeed = -51;
            work->winFlags[4] = 1;
            if (prevPage >= 3) {
                work->winFlags[5] = 1;
                work->unk14C = 1;
            }
            for (elem = work->elems, i = 0; i < 24; i++, elem++) {
                if (elem->unk0A > 0) {
                    elem->unk0A = 0;
                    elem->unk08 = 1;
                }
            }
            if (page >= 4) {
                colorCycle = 0;
                for (i = 0; i < 4; i++) {
                    work->winFlags[i] = 1;
                }
            }
            if (page == 6 || prevPage == 6) {
                partnerFading = 1;
                if (page == 6) {
                    elem = &work->elems[15];
                } else {
                    elem = &work->elems[23];
                }
                elem->unk08 = 2;
            }
            prevPage = page;
            pageChanging = 1;
        }
        if (state != data->state) {
            elem = work->elems;
            switch (data->state) {
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
                            colorPtr = colorStart = D_8010AAD4_storyresult;
                            colorFrames = 6;
                        } else if (rank == 3) {
                            colorCycle = 1;
                            colorPtr = colorStart = D_8010AAE0_storyresult;
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
                        if (prevPage >= 3) {
                            work->winFlags[5] = 1;
                            work->unk14C = 1;
                        }
                        for (elem = work->elems, i = 0; i < 24; i++, elem++) {
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
                case 5:
                    i = 0;
                    goto setPage;
                case 6:
                    i = 1;
                    goto setPage;
                case 7:
                    i = 2;
                    goto setPage;
                case 8:
                    i = 3;
                    goto setPage;
                case 9:
                    i = 4;
                    goto setPage;
                case 10:
                    i = 5;
                    if (page != 4 && page != 6) {
                        data->state = 8;
                        i = 3;
                    }
                    goto setPage;
                case 11:
                    i = 6;
                setPage:
                    if (page == i) {
                        data->state = 0;
                    }
                    page = i;
                    break;
                case 255:
                    break;
            }
            state = data->state;
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
            sprAlpha += sprFadeSpeed;
            temp = 0;
            if (sprAlpha >= 255) {
                sprFadeSpeed = 0;
                sprAlpha = 255;
                temp = 1;
            } else if (sprAlpha <= 0) {
                sprFadeSpeed = 0;
                sprAlpha = 0;
                temp = 1;
            }
            for (elem = work->elems, i = 0; i < 24; i++, elem++) {
                if (elem->unk08 > 0) {
                    if (elem->unk08 == 1) {
                        elem->unk08 = 2;
                        HuSprDispOn(group, i);
                    }
                    if ((s16)temp) {
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
            if (work->unk14C) {
                if (temp) {
                    work->unk14C = 0;
                }
                x = work->unk148;
                for (i = 0; i < 13; i++) {
                    if (sprAlpha == 0) {
                        HuSprDispOff(x, i);
                    }
                    HuSprTPLvlSet(x, i, sprAlpha);
                }
            }
        }
        if (winFadeSpeed != 0) {
            winAlpha += winFadeSpeed;
            temp = 0;
            if (winAlpha >= 255) {
                winFadeSpeed = 0;
                winAlpha = 255;
                temp = 1;
            } else if (winAlpha <= 0) {
                winFadeSpeed = 0;
                winAlpha = 0;
                temp = 1;
            }
            for (win = work->windows, flag = work->winFlags, i = 0; i < 6; i++, win++, flag++) {
                if (*flag > 0) {
                    if ((s16)temp) {
                        *flag = 0;
                    }
                    func_8005BF70_main(*win, winAlpha);
                }
            }
        }
        HuPrcVSleep();
    } while (state != 255);

    HuSprGrpKill(group);
    for (elem = work->elems, i = 0; i < ARRAY_COUNTU(work->elems) - 1; i++, elem++) {
        if (elem->unk04 >= 0) {
            HuSprAnimKill(elem->unk04);
        }
    }
    HuSprGrpKill(work->unk148);
    HuSprAnimKill(work->unk14A);
    for (gfx = work->graphics, i = 0; i < 4; i++, gfx++) {
        if (*gfx >= 0) {
            HuSprAnimKill(*gfx);
        }
    }
    for (win = work->windows, i = 0; i < ARRAY_COUNTU(work->windows); i++, win++) {
        HuWinKill(*win);
    }
    HuMemFree(work);
    data->state = 0;
    while (TRUE) {
        HuPrcVSleep();
    }
}

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

s16 func_8010A5C4_storyresult(s16 playerIdx) {
    s16 stars = GwPlayer[playerIdx].star;
    s16 maxStars = 0;
    s16 coins;
    s16 maxCoins;
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
    // The star lead reuses the loop counter.
    i = stars - maxStars;
    if (i >= 2) {
        result = 4;
    } else if (i == 1) {
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
