#include "staff.h"

// Rodrigues rotation matrix elements for a rotation of angle degrees about the unit axis (x, y, z).
#define ROT_XX(x, y, z, angle) ((x) * (x) + (1.0f - (x) * (x)) * cosdf(angle))
#define ROT_XY(x, y, z, angle) ((x) * (y) * (1.0f - cosdf(angle)) - (z) * sindf(angle))
#define ROT_XZ(x, y, z, angle) ((x) * (z) * (1.0f - cosdf(angle)) + (y) * sindf(angle))
#define ROT_YX(x, y, z, angle) ((x) * (y) * (1.0f - cosdf(angle)) + (z) * sindf(angle))
#define ROT_YY(x, y, z, angle) ((y) * (y) + (1.0f - (y) * (y)) * cosdf(angle))
#define ROT_YZ(x, y, z, angle) ((y) * (z) * (1.0f - cosdf(angle)) - (x) * sindf(angle))
#define ROT_ZX(x, y, z, angle) ((x) * (z) * (1.0f - cosdf(angle)) - (y) * sindf(angle))
#define ROT_ZY(x, y, z, angle) ((y) * (z) * (1.0f - cosdf(angle)) + (x) * sindf(angle))
#define ROT_ZZ(x, y, z, angle) ((z) * (z) + (1.0f - (z) * (z)) * cosdf(angle))

typedef struct StaffCreditEntry { // sizeof 0x4
    /* 0x00 */ s8 type;
    /* 0x01 */ s8 wait;
    /* 0x02 */ u16 arg;
} StaffCreditEntry;

typedef struct StaffCreditSlot { // sizeof 0x20
    /* 0x00 */ Vec pos;
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y;
    /* 0x10 */ s16 win0;
    /* 0x12 */ s16 win1;
    /* 0x14 */ s16 sprite;
    /* 0x16 */ s16 model;
    /* 0x18 */ s16 motion;
    /* 0x1A */ s16 linkModel;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 type;
} StaffCreditSlot;

s32 staff_creditSprTbl[1] = { 0x160042 };
StaffCreditEntry staff_creditSec0Tbl[] = {
    { 4, 0, 0x6400 },
    { 1, 0, 0x4B00 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec1Tbl[] = {
    { 4, 0, 0x6401 },
    { 1, 0, 0x4B01 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec2Tbl[] = {
    { 4, 0, 0x6402 },
    { 1, 0, 0x4B02 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec3Tbl[] = {
    { 4, 0, 0x6403 },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B02 },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B03 },
    { 1, 15, 0x4B04 },
    { 1, 0, 0x4B05 },
    { 1, 15, 0x4B06 },
    { 1, 0, 0x4B07 },
    { 1, 0, 0x4B08 },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B01 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec4Tbl[] = {
    { 4, 0, 0x6404 },
    { 1, 0, 0x4B09 },
    { 1, 0, 0x4B0A },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec5Tbl[] = {
    { 4, 0, 0x6405 },
    { 1, 0, 0x4B0B },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec6Tbl[] = {
    { 4, 0, 0x6406 },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B0C },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B0D },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B0E },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec7Tbl[] = {
    { 4, 0, 0x6407 },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B0F },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B10 },
    { 1, 0, 0x4B11 },
    { 1, 0, 0x4B12 },
    { 1, 0, 0x4B13 },
    { 1, 15, 0x4B14 },
    { 1, 0, 0x4B15 },
    { 1, 0, 0x4B16 },
    { 1, 0, 0x4B17 },
    { 1, 0, 0x4B18 },
    { 1, 15, 0x4B19 },
    { 1, 0, 0x4B1A },
    { 1, 0, 0x4B1B },
    { 1, 0, 0x4B1C },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B1D },
    { 1, 0, 0x4B1E },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec8Tbl[] = {
    { 4, 0, 0x6408 },
    { 1, 0, 0x4B1F },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec9Tbl[] = {
    { 4, 0, 0x6409 },
    { 1, 0, 0x4B20 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec10Tbl[] = {
    { 4, 0, 0x640A },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B21 },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B22 },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B23 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec11Tbl[] = {
    { 4, 0, 0x640B },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B24 },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B25 },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B26 },
    { 1, 0, 0x4B27 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec12Tbl[] = {
    { 4, 0, 0x640C },
    { 1, 0, 0x4B28 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec13Tbl[] = {
    { 4, 0, 0x640D },
    { 3, 0, 0x6428 },
    { 1, 0, 0x4B29 },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B2A },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B2B },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B2C },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec14Tbl[] = {
    { 4, 0, 0x640E },
    { 3, 0, 0x6428 },
    { 1, 0, 0x4B2D },
    { 1, 0, 0x4B2E },
    { 3, 0, 0x6425 },
    { 1, 0, 0x4B2F },
    { 3, 0, 0x6426 },
    { 1, 0, 0x4B30 },
    { 1, 0, 0x4B31 },
    { 1, 15, 0x4B32 },
    { 1, 0, 0x4B33 },
    { 1, 0, 0x4B34 },
    { 1, 0, 0x4B35 },
    { 1, 0, 0x4B36 },
    { 1, 15, 0x4B37 },
    { 1, 0, 0x4B38 },
    { 1, 0, 0x4B39 },
    { 1, 0, 0x4B3A },
    { 3, 0, 0x6427 },
    { 1, 0, 0x4B3B },
    { 1, 0, 0x4B3C },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec15Tbl[] = {
    { 4, 0, 0x640F },
    { 1, 0, 0x4B3D },
    { 1, 0, 0x4B3E },
    { 1, 0, 0x4B3F },
    { 1, 0, 0x4B40 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec16Tbl[] = {
    { 4, 0, 0x6410 },
    { 1, 0, 0x4B41 },
    { 1, 0, 0x4B42 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec17Tbl[] = {
    { 4, 0, 0x6411 },
    { 1, 0, 0x4B43 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec18Tbl[] = {
    { 4, 0, 0x6412 },
    { 1, 0, 0x4B44 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec19Tbl[] = {
    { 4, 0, 0x6413 },
    { 1, 0, 0x4B45 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec20Tbl[] = {
    { 4, 0, 0x6414 },
    { 1, 0, 0x4B46 },
    { 1, 0, 0x4B4A },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec21Tbl[] = {
    { 4, 0, 0x6415 },
    { 1, 0, 0x4B47 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec22Tbl[] = {
    { 4, 0, 0x6416 },
    { 1, 0, 0x4B48 },
    { 1, 0, 0x4B4B },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec23Tbl[] = {
    { 4, 0, 0x6417 },
    { 1, 0, 0x4B49 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec24Tbl[] = {
    { 4, 0, 0x6418 },
    { 1, 0, 0x4B4C },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec25Tbl[] = {
    { 4, 0, 0x6419 },
    { 1, 22, 0x4B4D },
    { 2, 15, 0x0 },
    { 1, 0, 0x4B4E },
    { 1, 0, 0x4B4F },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec26Tbl[] = {
    { 4, 0, 0x641A },
    { 1, 0, 0x4B50 },
    { 1, 0, 0x4B51 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec27Tbl[] = {
    { 4, 0, 0x641B },
    { 1, 0, 0x4B52 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec28Tbl[] = {
    { 4, 0, 0x641C },
    { 1, 0, 0x4B53 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec29Tbl[] = {
    { 4, 0, 0x641D },
    { 1, 0, 0x4B54 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec30Tbl[] = {
    { 4, 0, 0x641E },
    { 3, 0, 0x642B },
    { 1, 0, 0x4B6C },
    { 1, 0, 0x4B6D },
    { 3, 0, 0x642C },
    { 1, 0, 0x4B6E },
    { 1, 0, 0x4B6F },
    { 3, 0, 0x642D },
    { 1, 0, 0x4B70 },
    { 1, 0, 0x4B71 },
    { 3, 0, 0x642E },
    { 1, 0, 0x4B72 },
    { 1, 0, 0x4B73 },
    { 1, 0, 0x4B74 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec31Tbl[] = {
    { 4, 0, 0x641F },
    { 1, 0, 0x4B56 },
    { 1, 0, 0x4B57 },
    { 1, 15, 0x4B58 },
    { 1, 15, 0x4B59 },
    { 1, 15, 0x4B5A },
    { 1, 0, 0x4B6A },
    { 1, 15, 0x4B6B },
    { 1, 0, 0x4B5B },
    { 1, 15, 0x4B5C },
    { 1, 15, 0x4B5D },
    { 1, 15, 0x4B5E },
    { 1, 15, 0x4B75 },
    { 1, 0, 0x4B76 },
    { 1, 15, 0x4B5F },
    { 1, 15, 0x4B60 },
    { 1, 0, 0x4B61 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec32Tbl[] = {
    { 4, 0, 0x6420 },
    { 1, 0, 0x4B62 },
    { 1, 0, 0x4B0A },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec33Tbl[] = {
    { 4, 0, 0x6421 },
    { 1, 0, 0x4B63 },
    { 1, 0, 0x4B64 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec34Tbl[] = {
    { 4, 0, 0x6422 },
    { 1, 0, 0x4B41 },
    { 1, 0, 0x4B65 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec35Tbl[] = {
    { 4, 0, 0x6423 },
    { 1, 0, 0x4B66 },
    { 1, 0, 0x4B67 },
    { -1, 0, 0 },
};
StaffCreditEntry staff_creditSec36Tbl[] = {
    { 4, 0, 0x6424 },
    { 1, 0, 0x4B68 },
    { 1, 30, 0x4B69 },
    { -1, 0, 0 },
};
StaffCreditEntry *staff_creditTbl[] = {
    staff_creditSec0Tbl,
    staff_creditSec1Tbl,
    staff_creditSec2Tbl,
    staff_creditSec3Tbl,
    staff_creditSec4Tbl,
    staff_creditSec5Tbl,
    staff_creditSec6Tbl,
    staff_creditSec7Tbl,
    staff_creditSec8Tbl,
    staff_creditSec9Tbl,
    staff_creditSec10Tbl,
    staff_creditSec11Tbl,
    staff_creditSec12Tbl,
    staff_creditSec13Tbl,
    staff_creditSec14Tbl,
    staff_creditSec15Tbl,
    staff_creditSec16Tbl,
    staff_creditSec17Tbl,
    staff_creditSec18Tbl,
    staff_creditSec19Tbl,
    staff_creditSec20Tbl,
    staff_creditSec21Tbl,
    staff_creditSec22Tbl,
    staff_creditSec23Tbl,
    staff_creditSec24Tbl,
    staff_creditSec25Tbl,
    staff_creditSec26Tbl,
    staff_creditSec27Tbl,
    staff_creditSec28Tbl,
    staff_creditSec29Tbl,
    staff_creditSec30Tbl,
    staff_creditSec31Tbl,
    staff_creditSec32Tbl,
    staff_creditSec33Tbl,
    staff_creditSec34Tbl,
    staff_creditSec35Tbl,
    staff_creditSec36Tbl,
    NULL,
    NULL,
};
Vec staff_finaleStarPosTbl[5] = {
    { -77.0f, 202.0f, 1762.0f },
    { -135.0f, 170.0f, 2500.0f },
    { -135.0f, 140.0f, 2500.0f },
    { 115.0f, 400.0f, -115.0f },
    { 52.0f, 0.0f, 135.0f },
};
Vec staff_endTumblePos = { 52.0f, 340.0f, 400.0f };
s32 staff_endSprTbl[3] = { 0x160004, 0x16000D, 0x160003 };
MsetupModelEntry staff_finaleMdlEntryTbl[4] = {
    { 0xF0004, 0x2B9, 0, 0, 1, { -41.0f, 0.0f, 2893.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xF0003, 0x2B9, 0, 0, 1, { 96.0f, 0.0f, 3072.0f }, { 0.0f, -30.0f, 0.0f } },
    { 0xF0005, 0x2B9, 0, 0, 1, { -59.0f, 45.0f, 2907.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xA015E, 0x2B9, 0, 2, 1, { -77.0f, 202.0f, 1216.0f }, { 0.0f, 0.0f, 0.0f } },
};

extern StaffDecoEntry staff_finaleChrTbl[8];
extern u8 staff_spiralColorTbl[4][4];

void staff_WinCreateAll(s16 *windows, s16 count) {
    s32 i;
    s16 window;

    for (i = 0; i < count; i++, windows++) {
        window = *windows = HuWinCreate(-120, -50, 240, 20, 0, 12);
        HuWinCenterPosSet(window, 120, 10);
        HuWinMesSpeedSet(window, 0);
        HuWinBGTPLvlSet(window, 0);
        HuWinMesPalSet(window, 2, 255, 0, 0);
        HuWinMesPalSet(window, 4, 0, 144, 0);
        HuWinMesPalSet(window, 5, 0, 176, 192);
        HuWinMesPalSet(window, 6, 255, 173, 0);
        HuWinMesDefColSet(window, 64, 64, 64);
        HuWinBGColSet(window, 0, 0, 0);
        HuWinMesColSet(window, 7);
        HuWinTPLvlSet(window, 0x100);
        HuWinDispOff(window);
    }
}

void staff_CreditRollProc(void) {
    StaffCreditSlot slots[12];
    s16 models[16];
    s16 anims[1];
    s16 sprites[1];
    Process *prc;
    UnkStaff_4 *prcWork;
    s16 *state;
    StaffCreditSlot *slot;
    StaffCreditEntry *entry;
    s32 i;
    s16 model;
    s16 link;
    s16 curState;
    s16 wait;
    s16 entryIdx;
    s16 modelIdx;
    s16 win0Idx;
    s16 win1Idx;
    s16 active;
    s16 done;

    state = HuPrcCurrentGet()->user_data;
    prc = omAddPrcObj(staff_CastProc, 0x4000, 0x1000, 0);
    HuPrcVSleep();
    prcWork = prc->user_data;
    for (slot = slots, i = 0; i < 12; i++, slot++) {
        slot->type = 0;
        slot->model = -1;
        slot->motion = -1;
        slot->win0 = -1;
        slot->win1 = -1;
        slot->sprite = -1;
        slot->linkModel = -1;
        slot->unk_1C = -1;
    }
    model = -1;
    for (i = 0; i < 3; i++) {
        if (model < 0) {
            model = link = Hu3DModelRead(0x160025, 0x2B9);
        } else {
            link = Hu3DModelLink(model);
        }
        models[i] = link;
        Hu3DModelAttrSet(link, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 1; i++) {
        anims[i] = HuSprAnimDataRead(staff_creditSprTbl[i]);
        sprites[i] = espEntry(anims[i], 0, 0);
        espDispOff(sprites[i]);
    }
    modelIdx = 0;
    win0Idx = 0;
    win1Idx = 0;
    curState = 0;
    while (curState >= 0) {
        if (curState != *state) {
            switch (*state) {
                case 0:
                    break;
                case 1:
                    wait = 1;
                    entry = staff_creditTbl[0];
                    entryIdx = 1;
                    break;
            }
            curState = *state;
        }
        if (curState == 1) {
            if (entryIdx >= 0 && --wait == 0) {
                if (entry->type == -1) {
                    entry = staff_creditTbl[entryIdx];
                    entryIdx++;
                    if (entry == NULL) {
                        entryIdx = -1;
                    }
                    wait += 127;
                } else {
                    for (slot = slots, i = 0; i < 12; i++, slot++) {
                        if (slot->type == 0) {
                            break;
                        }
                    }
                    if (i < 12) {
                        slot->x = 160;
                        slot->y = 320;
                        slot->pos.x = 0.0f;
                        slot->pos.y = -480.0f;
                        slot->pos.z = 380.0f;
                        slot->type = entry->type;
                        switch (slot->type) {
                            case 1:
                                staff_TextLineStrSet(1, win1Idx, entry->arg, slot->x, slot->y);
                                slot->win1 = win1Idx;
                                if (++win1Idx >= 12) {
                                    win1Idx = 0;
                                }
                                break;
                            case 4:
                                slot->linkModel = models[modelIdx];
                                Hu3DModelAttrSet(slot->linkModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                                Hu3DModelPosSet(slot->linkModel, slot->pos.x, slot->pos.y, slot->pos.z);
                                staff_CastShow(prc, &slot->model, &slot->motion, &slot->pos);
                                if (++modelIdx >= 3) {
                                    modelIdx = 0;
                                }
                                /* fallthrough */
                            case 3:
                                staff_TextLineStrSet(0, win0Idx, entry->arg, slot->x, slot->y);
                                slot->win0 = win0Idx;
                                if (++win0Idx >= 6) {
                                    win0Idx = 0;
                                }
                                wait += 22;
                                break;
                            case 2:
                                slot->sprite = sprites[entry->arg];
                                espDispOn(slot->sprite);
                                break;
                        }
                        wait += entry->wait;
                        entry++;
                        if (slot->type == 1 && entry->type >= 3) {
                            wait += 22;
                        }
                        wait += 30;
                    } else {
                        wait = 1;
                    }
                }
            }
            for (slot = slots, i = 0, active = 0; i < 12; i++, slot++) {
                if (slot->type == 0) {
                    continue;
                }
                active++;
                done = 0;
                slot->y--;
                if (slot->type == 4) {
                    done = slot->y < -63;
                } else if (slot->y < -15) {
                    done++;
                }
                if (done) {
                    slot->type = 0;
                    if (slot->model >= 0) {
                        Hu3DModelAttrSet(slot->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        staff_CastKillReq(prc, slot->model);
                    }
                    slot->model = -1;
                    slot->motion = -1;
                    if (slot->win1 >= 0) {
                        staff_TextLineDispSet(1, slot->win1, 0);
                        slot->win1 = -1;
                    }
                    if (slot->sprite >= 0) {
                        espDispOff(slot->sprite);
                        slot->sprite = -1;
                    }
                    if (slot->win0 >= 0) {
                        staff_TextLineDispSet(0, slot->win0, 0);
                        slot->win0 = -1;
                    }
                    if (slot->linkModel >= 0) {
                        Hu3DModelAttrSet(slot->linkModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        slot->linkModel = -1;
                    }
                } else {
                    switch (slot->type) {
                        case 1:
                            if (slot->win1 >= 0) {
                                staff_TextLinePosSet(1, slot->win1, slot->x, slot->y);
                            }
                            break;
                        case 4:
                            slot->pos.y = 288.0 - slot->y * 2.4;
                            Hu3DModelPosSet(slot->linkModel, slot->pos.x, slot->pos.y, slot->pos.z);
                            if (slot->model >= 0) {
                                staff_CastPosSet(prc, slot->model, &slot->pos);
                            }
                            /* fallthrough */
                        case 3:
                            staff_TextLinePosSet(0, slot->win0, slot->x, slot->y);
                            break;
                        case 2:
                            espPosSet(slot->sprite, slot->x, slot->y);
                            break;
                    }
                }
            }
            if (active == 0 && entryIdx < 0) {
                *state = -1;
            }
        }
        HuPrcVSleep();
    }
    prcWork->unk_04 = 1;
    for (i = 0; i < 3; i++) {
        Hu3DModelKill(models[i]);
    }
    for (i = 0; i < 1; i++) {
        espKill(sprites[i]);
        HuSprAnimKill(anims[i]);
    }
    HuPrcVSleep();
    *state = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void staff_FinaleWalkUpdate(s16 *state, f32 *angle, f32 *rotY, UnkStaff *work) {
    Vec pos = work->pos;
    Vec *p = &pos;
    f32 dx;
    f32 rot;

    switch (*state) {
        case 0:
            p->x += 6.266667f;
            if (p->x >= 260.0f) {
                (*state)++;
                *angle = 0.0f;
            }
            break;
        case 1:
            *angle += 12.0f;
            if (*angle >= 180.0f) {
                *angle = 180.0f;
                (*state)++;
            }
            dx = cosdf(*angle) * 6.266667f;
            p->x += dx;
            rot = 90.0f - *angle;
            *rotY = rot;
            break;
        case 2:
            p->x -= 6.266667f;
            if (p->x <= -680.0f) {
                (*state)++;
                *angle = 0.0f;
            }
            break;
        case 3:
            *angle += 12.0f;
            if (*angle >= 180.0f) {
                *angle = 180.0f;
                *state = 0;
            }
            dx = cosdf(*angle) * -6.266667f;
            p->x += dx;
            rot = *angle + -90.0f;
            *rotY = rot;
            break;
    }
    work->pos.x = p->x;
    Hu3DModelPosSet(work->unk_18, p->x, p->y, p->z);
    Hu3DModelPosSet(work->unk_1E, p->x, 0.0f, p->z);
    Hu3DModelRotSet(work->unk_18, work->rot.x, *rotY - 8.0f, work->rot.z);
}

void staff_FinaleStarUpdate(UnkStaff_1 *works) {
    Vec pos[3];
    UnkStaff_1 *work;
    Vec *p;
    s32 i;
    f32 temp;
    f32 dx;
    f32 dz;
    f32 rot;

    for (work = works, p = pos, i = 0; i < 3; i++, work++, p++) {
        *p = work->pos;
        work->unk_18.z += 180.0f / 7.0f;
        if (work->unk_18.z >= 180.0f) {
            work->unk_18.z -= 180.0f;
            temp = (f32)(staff_Rand() & 0x1F) - 15.0f;
            temp += 20.0f;
            work->unk_24 = temp;
        }
        temp = sindf(work->unk_18.z) * work->unk_24;
        p->y += temp;
    }

    work = works;
    p = pos;
    switch (work->unk_2A) {
        case 0:
            p->x += 6.266667f;
            if (p->x >= 260.0f) {
                work->unk_2A++;
                work->unk_18.x = 0.0f;
            }
            break;
        case 1:
            work->unk_18.x += 12.0f;
            if (work->unk_18.x >= 180.0f) {
                work->unk_18.x = 180.0f;
                work->unk_2A++;
            }
            dx = cosdf(work->unk_18.x) * 6.266667f;
            p->x += dx;
            rot = work->unk_18.x + -90.0f;
            work->rot.y = rot;
            break;
        case 2:
            p->x -= 6.266667f;
            if (p->x <= -680.0f) {
                work->unk_2A++;
                work->unk_18.x = 0.0f;
            }
            break;
        case 3:
            work->unk_18.x += 12.0f;
            if (work->unk_18.x >= 180.0f) {
                work->unk_18.x = 180.0f;
                work->unk_2A = 0;
            }
            dx = cosdf(work->unk_18.x) * -6.266667f;
            p->x += dx;
            rot = 90.0f - work->unk_18.x;
            work->rot.y = rot;
            break;
    }
    work->pos.x = p->x;

    for (work = works + 1, p = pos + 1, i = 1; i < 3; i++, work++, p++) {
        temp = work->unk_18.x;
        switch (i) {
            case 1:
                temp += 6.0f;
                rot = -90.0f;
                break;
            case 2:
                temp -= 5.0f;
                rot = 90.0f;
                break;
        }
        if (temp < 0.0f) {
            temp += 360.0f;
        } else if (temp >= 360.0f) {
            temp -= 360.0f;
        }
        work->unk_18.x = temp;
        dx = sindf(temp) * work->unk_18.y;
        dz = cosdf(temp) * work->unk_18.y;
        p->x += dx;
        p->z += dz;
        rot += temp;
        if (rot < 0.0f) {
            rot += 360.0f;
        } else if (rot >= 360.0f) {
            rot -= 360.0f;
        }
        work->rot.y = rot;
    }

    for (work = works, p = pos, i = 0; i < 3; i++, work++, p++) {
        Hu3DModelPosSet(work->unk_28, p->x, p->y, p->z);
        Hu3DModelRotSet(work->unk_28, work->rot.x, work->rot.y, work->rot.z);
    }
}

void staff_FinaleStarCreate(UnkStaff_1 *works) {
    s16 base = -1;
    UnkStaff_1 *work;
    s32 i;
    s16 model;

    for (work = works, i = 0; i < 3; i++, work++) {
        if (base < 0) {
            base = model = Hu3DModelCreate(DataReadTemp(0xA015E), 0x2B9);
        } else {
            model = Hu3DModelLink(base);
        }
        work->unk_28 = model;
        Hu3DMotionAttrSet(model, -1, 2);
        work->pos = staff_finaleStarPosTbl[i];
        Hu3DModelPosSet(model, work->pos.x, work->pos.y, work->pos.z);
        work->rot.x = work->rot.y = work->rot.z = 0.0f;
        work->unk_24 = 30.0f;
        switch (i) {
            case 0:
                Hu3DModelScaleSet(model, 0.8f, 0.8f, 0.8f);
                work->rot.y = -90.0f;
                Hu3DModelRotSet(model, 0.0f, -90.0f, 0.0f);
                work->unk_18.y = work->unk_18.x = work->unk_18.z = 0.0f;
                break;
            case 1:
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                work->unk_18.z = 60.0f;
                work->unk_18.x = 0.0f;
                work->unk_18.y = 50.0f;
                break;
            case 2:
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                work->unk_18.z = 120.0f;
                work->unk_18.x = 180.0f;
                work->unk_18.y = 80.0f;
                break;
        }
        work->unk_2A = 0;
    }
}

void staff_FinaleChrCreate(UnkStaff *works) {
    StaffDecoEntry *entry = staff_finaleChrTbl;
    UnkStaff *work = works;
    s16 shadowBase = -1;
    s32 i;
    s16 model;
    s16 shadow;
    void *data;

    for (i = 0; i < 8; i++, work++, entry++) {
        model = work->unk_18 = Hu3DModelCreate(DataReadTemp(entry->dataId), 0x2A9);
        data = DataReadTemp(entry->animDataId);
        work->unk_1C = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, entry->animName);
        HuMemMemoryFreePerm(data);
        Hu3DModelRemakeStatic(model);
        Hu3DModelDynamicFree(model);
        work->unk_1A = Hu3DModelCreate(DataReadTemp(entry->subDataId), 0x1D);
        Hu3DMotionModelSet(model, work->unk_1A);
        Hu3DMotionAttrSet(model, -1, 2);
        Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
        work->pos = entry->pos;
        Hu3DModelPosSet(model, work->pos.x, work->pos.y, work->pos.z);
        work->rot = entry->rot;
        Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
        work->unk_1E = -1;
        if (i != 0) {
            if (shadowBase < 0) {
                shadowBase = shadow = Hu3DModelCreate(DataReadTemp(9), 0x299);
            } else {
                shadow = Hu3DModelLink(shadowBase);
            }
            work->unk_1E = shadow;
            Hu3DModelPosSet(shadow, work->pos.x, 0.0f, work->pos.z);
            Hu3DModelScaleSet(shadow, 1.2f, 1.2f, 1.2f);
        }
    }
}

void staff_FinaleProc(void) {
    MsetupModelHandle sp10[3];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    f32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    MsetupModelHandle *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
    MBDCameraKill();
    staff_cameraLookF = 1;
    staff_cameraPos.x = 350.0f;
    staff_cameraPos.y = 190.0f;
    staff_cameraPos.z = 3770.0f;
    staff_cameraTarget.x = -1000.0f;
    staff_cameraTarget.y = 130.0f;
    staff_cameraTarget.z = 450.0f;
    staff_cameraFov = 40.0f;
    Hu3DCameraPerspectiveSet(0, 40.0f, staff_cameraNear, staff_cameraFar);
    staff_ModelEntryReadAll(staff_finaleMdlEntryTbl, sp10, 3);
    staff_FinaleChrCreate(sp20);
    staff_FinaleStarCreate(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0.0f;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                staff_FinaleStarUpdate(sp120);
                staff_FinaleWalkUpdate(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            staff_FinaleStarUpdate(sp120);
            staff_FinaleWalkUpdate(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    for (temp3 = sp10, i = 0; i < 3; i++, temp3++) {
        Hu3DModelKill(temp3->model);
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        Hu3DModelKill(temp2->unk_18);
        Hu3DModelKill(temp2->unk_1A);
        Hu3DAnimKill(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            Hu3DModelKill(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        Hu3DModelKill(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

void staff_EndShadowUpdate(s16 model, Vec *pos) {
    f32 height = pos->y;
    f32 scale = 400.0f - height;
    f32 offsetX;
    f32 offsetZ;

    if (scale < 0.0f) {
        scale = 0.0f;
    }
    scale *= 0.0015f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    offsetX = height * (f64)0.2f;
    offsetZ = height * (0.2f * 1.732);
    offsetX += pos->x;
    offsetZ += pos->z;
    Hu3DModelPosSet(model, offsetX, 0.0f, offsetZ);
    if (height >= 80.0f) {
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void staff_EndTumbleDropExec(s16 model, s16 shadow, Vec *start) {
    Vec pos;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 *spinAxis;
    s32 count;
    f32 angle;
    f32 speed;
    f32 remain;
    s32 i;

    rotZ = 0.0f;
    rotY = rotZ;
    rotX = rotZ;
    count = staff_Rand();
    i = count & 0xF;
    if (i >= 10) {
        rotZ = -90.0f;
        spinAxis = &rotY;
    } else {
        spinAxis = &rotX;
    }
    count >>= 4;
    i = (count & 3) * 90;
    angle = i;
    speed = 0.0f;
    i = 0;
    pos = *start;
    do {
        angle -= 10.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        speed += 2.0f;
        pos.y -= speed;
        if (pos.y <= 0.0f) {
            pos.y = 0.0f;
            speed *= -0.5;
            RepeatVibrator(staff_padNo, 5, 0, 5);
            i++;
        }
        pos.z -= 8.0f;
        Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
        *spinAxis = angle;
        Hu3DModelRotSet(model, rotX, rotY, rotZ);
        staff_EndShadowUpdate(shadow, &pos);
        HuPrcVSleep();
    } while (i < 2);

    i = angle;
    remain = i % 90;
    if (remain >= 10.0f) {
        i = remain;
        count = i / 10;
        speed = pos.y / count;
        for (; count != 0; count--) {
            angle -= 10.0f;
            pos.y -= speed;
            pos.z -= 8.0f;
            Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
            *spinAxis = angle;
            Hu3DModelRotSet(model, rotX, rotY, rotZ);
            staff_EndShadowUpdate(shadow, &pos);
            HuPrcVSleep();
        }
    }
    pos.y = 0.0f;
    Hu3DModelPosSet(model, pos.x, 22.0f, pos.z);
    *spinAxis -= 8.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
    *spinAxis += 12.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
    *spinAxis -= 4.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
}

void staff_EndProc(void) {
    UnkStaff_9 work;
    s16 *stat;
    s16 model;
    s16 shadow;
    s16 motion;
    s16 grp;
    s16 state;
    s16 x;
    s16 tpLvl;
    s16 step;
    u16 esp;
    s32 i;

    stat = HuPrcCurrentGet()->user_data;
    Hu3DGLightDirSet(1, -21.0f, 235.0f, 181.0f);
    esp = espEntry(HuSprAnimDataRead(0x160024), 0, 0);
    espAttrSet(esp, HUSPR_ATTR_BG);
    espPosSet(esp, 160, 120);
    espPriSet(esp, 0xFFF0);
    staff_cameraLookF = 1;
    staff_cameraPos.x = -300.578f;
    staff_cameraPos.y = 542.5f;
    staff_cameraPos.z = 595.0f;
    staff_cameraTarget.x = 10.3905f;
    staff_cameraTarget.y = 0.0f;
    staff_cameraTarget.z = 48.0235f;
    staff_cameraFov = 32.0f;
    Hu3DCameraPerspectiveSet(0, 32.0f, staff_cameraNear, staff_cameraFar);
    motion = Hu3DMotionModelRead(0xA007D);
    model = Hu3DModelRead(0xA0075, 0x2A9);
    Hu3DModelDynamicFree(model);
    Hu3DModelScaleSet(model, 0.6f, 0.6f, 0.6f);
    HuPrcVSleep();
    Hu3DMotionModelSet(model, motion);
    Hu3DMotionAttrSet(model, 2, 2);
    shadow = Hu3DModelRead(9, 0x299);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    work.pos = staff_endTumblePos;
    Hu3DModelPosSet(model, work.pos.x, work.pos.y + 22.0f, work.pos.z);
    staff_EndShadowUpdate(shadow, &work.pos);
    for (i = 0; i < 3; i++) {
        work.anims[i] = HuSprAnimDataRead(staff_endSprTbl[i]);
    }
    grp = HuSprGrpCreate(3, 0);
    for (x = 268, i = 0; i < 3; i++, x += 12) {
        HuSprTPLvlSet(grp, i, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
        HuSprScaleSet(grp, i, 1.0f, 1.0f);
        {
            // A local pointer to work is needed for the address to be hoisted out of the loop.
            UnkStaff_9 *w = &work;

            HuSprGrpMemberSet(grp, i, w->anims[i], 0);
        }
        HuSprAnimModeSet(grp, i, HUSPR_ANIM_MODE_STOP);
        HuSprPriSet(grp, i, 400);
        HuSprPosSet(grp, i, x, 214);
    }
    *stat = 0;
    state = 0;
    while (TRUE) {
        if (state != *stat) {
            if (*stat == 1) {
                Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            state = *stat;
        }
        if (state == 1) {
            staff_EndTumbleDropExec(model, shadow, &work.pos);
            for (i = 0; i < 3; i++) {
                HuSprDispOn(grp, i);
                HuSprTPLvlSet(grp, i, 0);
            }
            tpLvl = 0;
            step = 2;
            do {
                tpLvl += step;
                if (tpLvl >= 256) {
                    tpLvl = 256;
                    step = 0;
                }
                for (i = 0; i < 3; i++) {
                    HuSprTPLvlSet(grp, i, tpLvl);
                }
                HuPrcVSleep();
            } while (step != 0);
            *stat = 0;
        }
        HuPrcVSleep();
    }
}

UnkStaff_2 *staff_FireworkCreate(s32 arg0) {
    Process *prc = omAddPrcObj(staff_FireworkProc, 0x3F00, 0x2000, 0);
    UnkStaff_2 *data = HuMemAllocTag(sizeof(UnkStaff_2), TAG_OVERLAY);

    prc->user_data = data;
    data->unk_0A = data->unk_06 = 60;
    data->unk_0C.x = 0.0f;
    data->unk_0C.y = 500.0f;
    data->unk_0C.z = 0.0f;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 0.0f;
    data->unk_18.z = 0.0f;
    data->unk_00 = arg0;
    data->unk_04 = 0;
    return data;
}

void staff_FireworkSprSet(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

void staff_FireworkEndPosSet(UnkStaff_2 *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void staff_FireworkStartPosSet(UnkStaff_2 *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_18.x = x;
    arg0->unk_18.y = y;
    arg0->unk_18.z = z;
}

void staff_FireworkTimeSet(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void staff_FireworkFlagSet(UnkStaff_2 *arg0, s32 mask, s32 value) {
    arg0->unk_04 = value | (arg0->unk_04 & ~mask);
}

s16 staff_FireworkFlagGet(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void staff_FireworkBurstTimeSet(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

void staff_FireworkProc(void) {
    s16 model;
    s16 model2;
    s16 i;
    s16 angle;
    HmfModelData_UnkBC_Struct *effect;
    UnkStaff_2 *work;
    f32 rot;
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    Vec cur;
    Vec prev;
    s16 count;
    s16 j;
    s16 k;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 s;
    f32 s2;
    f32 scale;
    f32 vx;
    f32 vy;
    f32 vz;
    s32 range;

    rot = 0.0f;
    work = HuPrcCurrentGet()->user_data;
    angle = 0;
    model = Hu3DModelRead(0xB0034, 0x2A8);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (k = 0; k < hmf->unk10; k++) {
        count = hmf->unk60[k].unk22;
        face = hmf->unk60[k].unk54;
        for (j = 0; j < count; j++, face++) {
            face->unk00 |= 0x80;
        }
    }
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, staff_FireworkBurstHook);
    Hu3DParticleAttrSet(model, 8, 8);
    effect = Hu3DData[model].unkBC;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    model2 = Hu3DModelRead(0xB0035, 0x2B9);
    Hu3DModelAttrSet(model2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(model2, 2.0f, 2.0f, 2.0f);
    Hu3DMotionSpeedSet(model2, 2.0f);

    while (TRUE) {
        if (work->unk_04 & 4) {
            break;
        }
        if (work->unk_04 & 1) {
            HuPrcVSleep();
            continue;
        }
        work->unk_04 &= ~1;
        work->center = work->unk_18;
        work->unk_24 = work->unk_0C;
        work->unk_08 = work->unk_0A;
        range = rand8() * 2 + 400;
        work->unk_3C.x = range - range / 2.0f;
        range = rand8() * 2 + 200;
        work->unk_3C.y = range - range / 2.0f;
        range = rand8() * 2 + 200;
        work->unk_3C.z = range - range / 2.0f;
        work->unk_48 = (rand8() & 1) ? 180.0f : 0.0f;
        effect->unk08.f = work->unk_06;
        cur = work->center;
        prev = cur;
        HuAudFXPlay(0x16F);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DParticleCntSet(model, 0);
        effect->unk18 = staff_FireworkTrailHook;
        Hu3DParticleAttrSet(model, 2, 0);

        for (i = 0; i <= work->unk_08; i++) {
            HuPrcVSleep();
            prev = cur;
            dx = work->unk_24.x - work->center.x;
            dy = work->unk_24.y - work->center.y;
            dz = work->unk_24.z - work->center.z;
            s = sindf(90.0f / work->unk_08 * i);
            s2 = sindf(180.0f / work->unk_08 * i + work->unk_48);
            cur.x = s * dx + work->center.x + s2 * work->unk_3C.x;
            cur.y = s * dy + work->center.y + s2 * work->unk_3C.y;
            cur.z = s * dz + work->center.z + s2 * work->unk_3C.z;
            angle += 5;
            if (angle > 360) {
                angle -= 360;
            }
            rot += 20.0f;
            if (rot > 360.0f) {
                rot -= 360.0f;
            }

            dx = prev.x - cur.x;
            dy = prev.y - cur.y;
            dz = prev.z - cur.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                continue;
            }
            dx /= dist;
            dy /= dist;
            dz /= dist;

            for (j = 0; j < 2; j++) {
                vx = dx * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                vy = dy * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                vz = dz * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                scale = dist * ((s32)(rand8() * 25U >> 7) * 0.01f);
                vx *= scale;
                vy *= scale;
                vz *= scale;
                staff_ParticleAdd(model, vx + cur.x, vy + cur.y, vz + cur.z, vx, vy, vz, 0xFF, 0xFF, 0xC0);
            }

            vx = ROT_XX(dx, dy, dz, rot) * 0.0f + ROT_XY(dx, dy, dz, rot) + ROT_XZ(dx, dy, dz, rot) * 0.0f;
            vy = ROT_YX(dx, dy, dz, rot) * 0.0f + ROT_YY(dx, dy, dz, rot) + ROT_YZ(dx, dy, dz, rot) * 0.0f;
            vz = ROT_ZX(dx, dy, dz, rot) * 0.0f + ROT_ZY(dx, dy, dz, rot) + ROT_ZZ(dx, dy, dz, rot) * 0.0f;
            vx = (dx * 0.5f + vx * 0.5f) * dist / 2.0f;
            vy = (dy * 0.5f + vy * 0.5f) * dist / 2.0f;
            vz = (dz * 0.5f + vz * 0.5f) * dist / 2.0f;
            staff_ParticleAdd(model, cur.x, cur.y, cur.z, vx, vy, vz, 0xFF, 0x20, 0x20);

            vx = ROT_XX(dx, dy, dz, rot) * 0.0f + ROT_XY(dx, dy, dz, rot) * -1.0f + ROT_XZ(dx, dy, dz, rot) * 0.0f;
            vy = ROT_YX(dx, dy, dz, rot) * 0.0f + ROT_YY(dx, dy, dz, rot) * -1.0f + ROT_YZ(dx, dy, dz, rot) * 0.0f;
            vz = ROT_ZX(dx, dy, dz, rot) * 0.0f + ROT_ZY(dx, dy, dz, rot) * -1.0f + ROT_ZZ(dx, dy, dz, rot) * 0.0f;
            vx = (dx * 0.5f + vx * 0.5f) * dist / 2.0f;
            vy = (dy * 0.5f + vy * 0.5f) * dist / 2.0f;
            vz = (dz * 0.5f + vz * 0.5f) * dist / 2.0f;
            staff_ParticleAdd(model, cur.x, cur.y, cur.z, vx, vy, vz, 0xFF, 0x40, 0x00);
        }

        HuPrcSleep(15);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(model2, 0.0f);
        Hu3DModelAttrSet(model2, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(model2, cur.x, cur.y, cur.z);
        HuPrcVSleep();
        HuAudFXPlay(0x170);
        staff_FireworkShapeSet(model, work->unk_00);
        effect->unk18 = staff_FireworkBurstHook;
        Hu3DParticleCntSet(model, 0);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        Hu3DParticleAttrSet(model, 2, 0);
        while (!(Hu3DParticleAttrGet(model) & 2)) {
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(model2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        if (!(work->unk_04 & 2)) {
            work->unk_04 |= 1;
        }
        HuPrcVSleep();
    }
    Hu3DModelKill(model);
    Hu3DModelKill(model2);
    HuMemFree(work);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void staff_FireworkShapeSet(s16 model, s32 dataNum) {
    s16 anim;
    s16 grp;
    HuSprite *sprite;
    HuSprAnimPat *img;
    u16 *pixels;
    s16 count;
    HmfModelData_UnkBC_Struct *bc;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 width;
    s16 height;
    s16 used;
    s16 i;
    s16 x;
    s16 y;

    anim = HuSprAnimDataRead(dataNum);
    grp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(grp, 0, anim, 0);
    sprite = HuSprGet(grp, 0);
    img = sprite->data->pat;
    pixels = img->data;
    used = 0;
    width = img->sizeX;
    height = img->sizeY;
    for (i = 0; i < width * height; i++) {
        if (*pixels++ == 0xFFFF) {
            used++;
        }
    }
    pixels = sprite->data->pat->data;
    bc = Hu3DData[model].unkBC;
    count = Hu3DData[model].hmf->unk1A;
    particle = bc->unk58;
    for (y = 0, used = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (*pixels++ == 0xFFFF && used < count) {
                particle = &bc->unk58[used];
                particle->unk18 = rand8() & 0xF;
                particle->unk24 = (x - width / 2) * 12;
                particle->unk28 = (height / 2 - y) * 12;
                particle->unk2C = 1.0f;
                particle->unk08 = 3.0f;
                particle->unk04 = ((u16)(rand8() * 5) >> 7) * 0.1f + 3.0f;
                used++;
                particle++;
            }
        }
    }
    for (i = 0; i < count - used; i++, particle++) {
        particle->unk08 = particle->unk2C = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(anim);
}

HmfModelData_UnkBC_Unk58_Struct *staff_ParticleAdd(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r,
                                                     u8 g, u8 b) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk24 = vx;
            particle->unk28 = vy;
            particle->unk2C = vz;
            particle->unk00[0] = r;
            particle->unk00[1] = g;
            particle->unk00[2] = b;
            particle->unk08 = 2.0f;
            break;
        }
    }
    return particle;
}

void staff_FireworkBurstHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    s16 count = hmf->unk1A;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfModelData_UnkBC_Unk58_Struct *src;
    HmfModelData_UnkBC_Unk58_Struct *dst;
    s16 i;
    s16 j;
    s16 dead;
    u8 r;
    u8 g;
    u8 b;
    f32 angle;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk2C > 0.0f) {
                particle->unk08 = 1.0f;
            }
        }
    }
    particle = bc->unk58;
    r = rand8() | 0x80;
    g = rand8() | 0x80;
    b = rand8() | 0x80;
    if (bc->unk02 <= bc->unk08.f) {
        if (bc->unk02 > 20) {
            for (j = 0; j < 2; j++) {
                src = &bc->unk58[(rand8() * count) >> 8];
                if (src->unk2C > 0.0f) {
                    dst = &bc->unk58[(rand8() * count) >> 8];
                    if (dst->unk2C <= 0.0f) {
                        dst->unk0C = src->unk0C;
                        dst->unk10 = src->unk10;
                        dst->unk14 = src->unk14;
                        dst->unk08 = 1.0f;
                    }
                }
            }
        }
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    angle = bc->unk02 * particle->unk04;
                    if (angle > 90.0f) {
                        angle = 90.0f;
                    }
                    particle->unk0C = sindf(angle) * particle->unk24;
                    particle->unk10 = sindf(angle) * particle->unk28;
                    particle->unk14 = 0.0f;
                    particle->unk08 = ((bc->unk02 + i) & 1) * 0.5f + 1.0f;
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
            }
        }
    } else {
        for (i = 0, dead = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    if (particle->unk18 <= 0.0f) {
                        particle->unk10 -= particle->unk04 * 5.0f;
                        particle->unk08 -= 0.02f;
                        if (particle->unk08 < 0.0f) {
                            particle->unk08 = 0.0f;
                        }
                    } else {
                        particle->unk18 -= 1.0f;
                        particle->unk08 = ((bc->unk02 + i) & 1) * 0.5f + 1.0f;
                    }
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
                dead++;
            }
        }
        if (dead >= i) {
            bc->unk04 |= 2;
            return;
        }
    }
    bc->unk02++;
}

void staff_FireworkTrailHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    s16 count = hmf->unk1A;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        }
        bc->unk02++;
    }
    particle = bc->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28;
            particle->unk14 += particle->unk2C;
            particle->unk10 -= 5.0f;
            particle->unk08 -= 0.05f;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void staff_SpiralCreate(void) {
    Process *prc = omAddPrcObj(staff_SpiralProc, 0x3F00, 0x2000, 0);
    UnkStaff_5 *data = HuMemAllocTag(sizeof(UnkStaff_5), TAG_OVERLAY);

    prc->user_data = data;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 100.0f;
    data->unk_18.z = 0.0f;
}

void staff_SpiralProc(void) {
    s16 angle[2];
    Vec cur[2];
    Vec prev[2];
    f32 rot[2];
    f32 tilt[2];
    UnkStaff_5 *work;
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    s16 count;
    s16 i;
    s16 j;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 vx;
    f32 vy;
    f32 vz;
    s16 color;

    work = HuPrcCurrentGet()->user_data;
    model = Hu3DModelRead(0xB0034, 0x6A8);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        count = hmf->unk60[j].unk22;
        face = hmf->unk60[j].unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, staff_FireworkBurstHook);
    Hu3DParticleAttrSet(model, 8, 8);
    effect = Hu3DData[model].unkBC;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DParticleCntSet(model, 0);
    effect->unk18 = staff_FireworkTrailHook;
    Hu3DParticleAttrSet(model, 2, 0);
    work->unk_30 = work->unk_18;
    cur[0].x = sindf(0.0f) * 150.0f + work->unk_30.x;
    cur[0].y = work->unk_30.y;
    cur[0].z = cosdf(0.0f) * 150.0f + work->unk_30.z;
    prev[0] = cur[0];
    tilt[0] = rot[0] = 0.0f;
    angle[0] = 0;
    cur[1].x = sindf(180.0f) * 150.0f + work->unk_30.x;
    cur[1].y = work->unk_30.y;
    cur[1].z = cosdf(180.0f) * 150.0f + work->unk_30.z;
    prev[1] = cur[1];
    tilt[1] = rot[1] = 180.0f;
    angle[1] = 180;
    while (TRUE) {
        HuPrcVSleep();
        for (i = 0; i < 2; i++) {
            prev[i] = cur[i];
            dx = sindf(angle[i]) * 150.0f;
            dz = cosdf(angle[i]) * 150.0f;
            t = sindf(tilt[i]) * 10.0f;
            cur[i].x = dx * cosdf(t) + work->unk_30.x;
            cur[i].y = dx * -sindf(t) + work->unk_30.y;
            cur[i].z = dz + work->unk_30.z;
            angle[i] += 5;
            if (angle[i] > 360) {
                angle[i] -= 360;
            }
            rot[i] += 20.0f;
            if (rot[i] > 360.0f) {
                rot[i] -= 360.0f;
            }
            tilt[i] += 1.0f;
            if (tilt[i] > 360.0f) {
                tilt[i] -= 360.0f;
            }
            dx = prev[i].x - cur[i].x;
            dy = prev[i].y - cur[i].y;
            dz = prev[i].z - cur[i].z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                continue;
            }
            dx /= dist;
            dy /= dist;
            dz /= dist;
            t = rot[i];
            vx = ROT_XY(dx, dy, dz, t);
            vy = ROT_YY(dx, dy, dz, t);
            vz = ROT_ZY(dx, dy, dz, t);
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            staff_ParticleAdd(model, cur[i].x, cur[i].y, cur[i].z, vx, vy, vz, staff_spiralColorTbl[color][0],
                                staff_spiralColorTbl[color][1], staff_spiralColorTbl[color][2])
                ->unk08 = 1.0f;
            vx = -ROT_XY(dx, dy, dz, t);
            vy = -ROT_YY(dx, dy, dz, t);
            vz = -ROT_ZY(dx, dy, dz, t);
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            staff_ParticleAdd(model, cur[i].x, cur[i].y, cur[i].z, vx, vy, vz, staff_spiralColorTbl[color][0],
                                staff_spiralColorTbl[color][1], staff_spiralColorTbl[color][2])
                ->unk08 = 1.0f;
        }
    }
}

StaffDecoEntry staff_finaleChrTbl[8] = {
    { 0x200A1, 0xF000B, 0x200A4, "c000l_0_DEF", { 100.0f, -14.0f, 3072.0f }, { 0.0f, -30.0f, 0.0f } },
    { 0x300A1, 0x160043, 0x300AB, "c001l_0_DEF", { 205.0f, 0.0f, 2869.0f }, { 0.0f, 46.0f, 0.0f } },
    { 0x700A1, 0x160044, 0x700AB, "c002l_0_DEF", { 299.0f, 0.0f, 2950.0f }, { 0.0f, -122.0f, 0.0f } },
    { 0x400A1, 0x160045, 0x400A3, "c003l_0_DEF", { -150.0f, 0.0f, 1762.0f }, { 0.0f, 83.0f, 0.0f } },
    { 0x500A1, 0x160046, 0x500AA, "c004l_0_DEF", { -626.0f, 0.0f, 2245.0f }, { 0.0f, 79.0f, 0.0f } },
    { 0x600A1, 0x160047, 0x600A4, "c005l_0_DEF", { -203.0f, 0.0f, 3066.0f }, { 0.0f, 39.0f, 0.0f } },
    { 0x800A1, 0x160048, 0x800AA, "c300l_0_DEF", { -346.0f, 0.0f, 2356.0f }, { 0.0f, -103.0f, -8.0f } },
    { 0x90001, 0x160049, 0x9001A, "c301l_0_DEF", { -133.0f, 0.0f, 2460.0f }, { 0.0f, 0.0f, 0.0f } },
};
s32 staff_finaleChrPad[3] = { 0 }; /* Unreferenced. */
u8 staff_spiralColorTbl[4][4] = { { 0, 255, 255, 0 }, { 255, 160, 40, 0 }, { 255, 255, 0, 0 }, { 0, 255, 0, 0 } };
