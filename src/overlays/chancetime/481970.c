#include "common.h"
#include "chancetime.h"
#include "game/window.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"

extern s8 D_8010FAE0_chancetime;
extern s8 D_8010FAE8_chancetime;
extern s32 D_8010FE60_chancetime;
extern s8 D_8010FE64_chancetime[3];

s32 func_8010BF3C_chancetime(void);
void func_8010DA24_chancetime(void);
s32 func_8010DAA4_chancetime(void);
s32 func_80106BB8_chancetime(void);
void func_80106BC4_chancetime(s8 arg0);
s32 func_80106BE0_chancetime(void);
void func_8010DF78_chancetime(s32 arg0);
s32 func_8010E258_chancetime(void);
void func_8010E264_chancetime(void);
s32 func_8010E4C4_chancetime(void);
void func_8010F1DC_chancetime(void);
s32 func_8010F420_chancetime(void);
void func_801062DC_chancetime(void);
void func_80105E08_chancetime(omObjData *object);
void func_80106154_chancetime(void);
void func_801061B8_chancetime(omObjData *object);
void func_80106240_chancetime(void);

void func_801059A0_chancetime(void) {
    omObjData *obj;
    s16 i;
    s16 j;
    s16 count;
    u32 roll;
    s8 temp;

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayer[j].group) {
                D_801100D0_chancetime[count] = j;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }

    D_801100DC_chancetime = BoardGetTurnTier(CUR_TURN);
    roll = (u8)(rand8() % 10) + 1;
    if (roll < 8) {
        D_8010FE64_chancetime[0] = 2;
        D_8010FE64_chancetime[1] = 0;
        D_8010FE64_chancetime[2] = 1;
    } else if (roll < 10) {
        D_8010FE64_chancetime[0] = 0;
        D_8010FE64_chancetime[1] = 1;
        D_8010FE64_chancetime[2] = 2;
    } else {
        D_8010FE64_chancetime[0] = 1;
        D_8010FE64_chancetime[1] = 0;
        D_8010FE64_chancetime[2] = 2;
    }
    for (i = 0; i < 5; i++) {
        if (rand8() & 1) {
            temp = D_8010FE64_chancetime[1];
            D_8010FE64_chancetime[1] = D_8010FE64_chancetime[2];
            D_8010FE64_chancetime[2] = temp;
        }
    }

    omInitObjMan(30, 20);
    HuWinInit();
    func_800142A0_main(80);
    func_8000B690_main(3);
    ScissorSet(0, 104.0f, 52.0f, 215.0f, 163.0f);
    ScissorSet(1, 0.0f, 0.0f, 320.0f, 240.0f);
    ScissorSet(2, 0.0f, 0.0f, 320.0f, 240.0f);
    for (i = 0; i < 3; i++) {
        ViewportSet(i, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, 0xA0);
    obj->work[0] = 3;
    omAddPrcObj(func_80106320_chancetime, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107300_chancetime, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80108CDC_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801094CC_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80109A00_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80109F34_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010A468_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010A99C_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B030_chancetime, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010BF80_chancetime, 0x1001, 0x2000, 0);
    omAddPrcObj(func_8010DBB0_chancetime, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, func_80105E08_chancetime);
    omAddObj(0, 0, 0, -1, func_801061B8_chancetime);
    func_80106154_chancetime();
    func_80106240_chancetime();
    WipeCreateIn(0xFF, 16);
}

void func_80105E08_chancetime(omObjData *object) {
    f32 fov;
    s32 state;
    s8 i;

    fov = 30.0f;
    state = D_8010FAE0_chancetime;
    switch (state) {
        case 0:
            D_8010FE60_chancetime = 0;
            state++;
            break;
        case 1:
            if (D_8010FE60_chancetime++ >= 7) {
                HuAudSeqPlay(0x42);
                HuAudFXPlay(0x4FF);
                D_8010FE60_chancetime = 0;
                state++;
            }
            break;
        case 2:
            state += func_8010BF3C_chancetime() != 0;
            break;
        case 3:
            if (++D_8010FE60_chancetime >= 0) {
                func_8010DA24_chancetime();
                state++;
                HuAudFXPlay(0x500);
            }
            break;
        case 4:
            if (func_8010DAA4_chancetime() == 1) {
                D_8010FE60_chancetime = 0;
                state++;
            }
            break;
        case 5:
            func_80106B18_chancetime();
            D_8010FE60_chancetime = 0;
            state++;
            break;
        case 6:
            if (func_80106BB8_chancetime() == 1) {
                func_8010F1DC_chancetime();
                state++;
            }
            break;
        case 7:
            state += func_8010F420_chancetime() != 0;
            break;
        case 8:
            func_8010DF78_chancetime(D_8010FE64_chancetime[0]);
            state++;
            break;
        case 9:
            if (func_8010E258_chancetime() == 1) {
                D_8010FE60_chancetime = 0;
                state++;
            }
            break;
        case 10:
            if (++D_8010FE60_chancetime > 0) {
                func_80106BC4_chancetime(D_8010FE64_chancetime[0]);
                state++;
            }
            break;
        case 11:
            state += func_80106BE0_chancetime() == 1;
            break;
        case 12:
            func_8010DF78_chancetime(D_8010FE64_chancetime[1]);
            state++;
            break;
        case 13:
            if (func_8010E258_chancetime() == 1) {
                D_8010FE60_chancetime = 0;
                state++;
            }
            break;
        case 14:
            if (++D_8010FE60_chancetime > 0) {
                func_80106BC4_chancetime(D_8010FE64_chancetime[1]);
                state++;
            }
            break;
        case 15:
            state += func_80106BE0_chancetime() == 1;
            break;
        case 16:
            func_8010DF78_chancetime(D_8010FE64_chancetime[2]);
            state++;
            break;
        case 17:
            if (func_8010E258_chancetime() == 1) {
                D_8010FE60_chancetime = 0;
                state++;
            }
            break;
        case 18:
            if (++D_8010FE60_chancetime > 0) {
                func_80106BC4_chancetime(D_8010FE64_chancetime[2]);
                state++;
            }
            break;
        case 19:
            state += func_80106BE0_chancetime() == 1;
            break;
        case 20:
            func_8010E264_chancetime();
            state++;
            break;
        case 21:
            state += func_8010E4C4_chancetime() != 0;
            break;
        case 22:
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            state++;
            break;
        case 23:
            if (WipeStatGet() == 0) {
                GMesClose();
                func_801062DC_chancetime();
                omOvlReturnEx(1);
            }
            break;
    }
    D_8010FAE0_chancetime = state;

    for (i = 0; i < 4; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCameraPerspectiveSet(i, fov, 80.0f, 8000.0f);
    }
}

void func_80106154_chancetime(void) {
    CRot.x = 0.1f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;

    Center.x = 0.0f;
    Center.y = 230.0f;
    Center.z = 920.0f;

    CZoom = 100.0f;
}

void func_801061B8_chancetime(omObjData *object) {
    if (D_800D530C_main != 1) {
        return;
    }

    if (D_8010FAE8_chancetime == 0) {
        WipeCreateOut(0, 20);
        D_8010FAE8_chancetime = 1;
    } else if (WipeStatGet() == 0) {
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        GMesClose();
        func_801062DC_chancetime();
        omOvlReturnEx(1);
    }
}

void func_80106240_chancetime(void) {
    u16 sprite;

    sprite = espEntry(func_8000B838_main(0x1C0001), 0, 0);
    espPosSet(sprite, 160, 180);
    espAttrSet(sprite, 0x4000);

    sprite = espEntry(func_8000B838_main(0x1C0005), 0, 0);
    espPosSet(sprite, 160, 60);
    espAttrSet(sprite, 0x4000);
}

void func_801062DC_chancetime(void) {
    HuWinAllKill();
    if (D_8010FAE4_chancetime == 1) {
        func_800F5EF0_shared_board();
    }
}
