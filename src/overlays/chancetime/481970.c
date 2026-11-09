#include "common.h"
#include "chancetime.h"
#include "game/window.h"
#include "../ovl_80_shared_board/106A50.h"

extern s8 D_8010FAE0_chancetime;
extern s8 D_8010FAE8_chancetime;
extern s32 D_8010FE60_chancetime;
extern s8 D_8010FE64_chancetime;
extern s8 D_8010FE65_chancetime;
extern s8 D_8010FE66_chancetime;

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

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/481970", func_801059A0_chancetime);

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
            func_8010DF78_chancetime(D_8010FE64_chancetime);
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
                func_80106BC4_chancetime(D_8010FE64_chancetime);
                state++;
            }
            break;
        case 11:
            state += func_80106BE0_chancetime() == 1;
            break;
        case 12:
            func_8010DF78_chancetime(D_8010FE65_chancetime);
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
                func_80106BC4_chancetime(D_8010FE65_chancetime);
                state++;
            }
            break;
        case 15:
            state += func_80106BE0_chancetime() == 1;
            break;
        case 16:
            func_8010DF78_chancetime(D_8010FE66_chancetime);
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
                func_80106BC4_chancetime(D_8010FE66_chancetime);
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
