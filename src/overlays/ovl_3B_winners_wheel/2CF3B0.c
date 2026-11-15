#include "common.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"

// Object data for the pointer object held in D_8010A4C0_winners_wheel,
// created in func_80107D50_winners_wheel. The pointer is made of 18 models.
typedef struct WinnersWheelPointer {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 rot[18];
    /* 0x4C */ f32 rawRot[18];
    /* 0x94 */ f32 speed;
    /* 0x98 */ f32 target;
    /* 0x9C */ s32 count;
    /* 0xA0 */ s32 mode;
} WinnersWheelPointer; // Size 0xA4

// Object data for the sign object held in D_8010A498_winners_wheel,
// created in func_80105BA8_winners_wheel.
typedef struct WinnersWheelSign {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 result;
} WinnersWheelSign; // Size 0x8

// Object data for the wheel object held in D_8010A49C_winners_wheel,
// created in func_801063B0_winners_wheel.
typedef struct WinnersWheelWheel {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 rot;
    /* 0x10 */ f32 angle;
} WinnersWheelWheel; // Size 0x14

// Object data for the player object held in D_8010A4B4_winners_wheel,
// created in func_80106910_winners_wheel.
typedef struct WinnersWheelPlayer {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 result;
    /* 0x0C */ f32 scale;
    /* 0x10 */ Vec pos;
} WinnersWheelPlayer; // Size 0x1C

// Object data for the prize panel object held in D_8010A4A0_winners_wheel,
// created in func_801070CC_winners_wheel. Holds per-panel state for the six
// panels on the wheel.
typedef struct WinnersWheelPanels {
    /* 0x00 */ f32 x[6];
    /* 0x18 */ f32 y[6];
    /* 0x30 */ f32 z[6];
    /* 0x48 */ f32 rot[6];
    /* 0x60 */ f32 angle[6];
    /* 0x78 */ f32 scale[6];
    /* 0x90 */ f32 unk_90;
    /* 0x94 */ f32 unk_94;
} WinnersWheelPanels; // Size 0x98

// Object data for the panel frame object held in D_8010A4A4_winners_wheel,
// created in func_80109454_winners_wheel.
typedef struct WinnersWheelPanelFrames {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 unk_04[6];
    /* 0x1C */ f32 unk_1C[6];
    /* 0x34 */ f32 rot[6];
    /* 0x4C */ f32 angle[6];
} WinnersWheelPanelFrames; // Size 0x64

// Object data for the won prize object held in D_8010A4A8_winners_wheel,
// created in func_8010985C_winners_wheel.
typedef struct WinnersWheelPrize {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 angle;
} WinnersWheelPrize; // Size 0x18

// Object data for the two NPC objects held in D_8010A4B8_winners_wheel,
// created in func_801078D8_winners_wheel.
typedef struct WinnersWheelNpc {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 index;
} WinnersWheelNpc; // Size 0x8

// Object data for the Bowser object held in D_8010A4C4_winners_wheel,
// created in func_80109D44_winners_wheel. Bowser appears when the pointer
// lands on the Bowser panel (panel item 17).
typedef struct WinnersWheelBowser {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 shadowScale;
    /* 0x14 */ f32 unk_14;
} WinnersWheelBowser; // Size 0x18

MinigameFlow D_8010A260_winners_wheel = {
    MG_STATE_OPENING, MINIGAME_ITEM, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_GOT_ITEM, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    240, 300, -1, 150, 150
};
s16 D_8010A288_winners_wheel = 0;
s32 D_8010A28C_winners_wheel[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s32 D_8010A2AC_winners_wheel[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 D_8010A460_winners_wheel BSS;
u8 D_8010A464_winners_wheel BSS;
s16 D_8010A466_winners_wheel BSS;
s32 D_8010A468_winners_wheel[6] BSS;
s32 D_8010A480_winners_wheel BSS;
s32 D_8010A484_winners_wheel BSS;
s16 D_8010A488_winners_wheel BSS;
s16 D_8010A48A_winners_wheel BSS;
s32 D_8010A48C_winners_wheel BSS;
s32 D_8010A490_winners_wheel BSS;
s16 D_8010A494_winners_wheel BSS;
omObjData *D_8010A498_winners_wheel BSS;
omObjData *D_8010A49C_winners_wheel BSS;
omObjData *D_8010A4A0_winners_wheel BSS;
omObjData *D_8010A4A4_winners_wheel BSS;
omObjData *D_8010A4A8_winners_wheel BSS;
s16 D_8010A4AC_winners_wheel[3] BSS;
omObjData *D_8010A4B4_winners_wheel BSS;
omObjData *D_8010A4B8_winners_wheel[2] BSS;
omObjData *D_8010A4C0_winners_wheel BSS;
omObjData *D_8010A4C4_winners_wheel BSS;

extern u16 D_800A11D0_main[];
extern u16 D_800A11DC_main[];

void func_8004BCE4_main(struct CameraViewData *data);
void func_80105AB0_winners_wheel(void);
void func_80105BA8_winners_wheel(void);
void func_80105C5C_winners_wheel(omObjData *obj);
void func_80105F18_winners_wheel(void);
void func_80105F60_winners_wheel(void);
void func_80105FB0_winners_wheel(omObjData *obj);
void func_80105FE4_winners_wheel(omObjData *obj);
void func_801063B0_winners_wheel(void);
void func_80106514_winners_wheel(omObjData *obj);
void func_80105F94_winners_wheel(void);
void func_80106718_winners_wheel(void);
void func_80106734_winners_wheel(void);
void func_80106750_winners_wheel(void);
void func_8010677C_winners_wheel(void);
void func_80106910_winners_wheel(void);
void func_80106D2C_winners_wheel(omObjData *obj);
void func_80106EB0_winners_wheel(s32 arg0);
void func_80106F54_winners_wheel(void);
void func_8010701C_winners_wheel(void);
void func_801070CC_winners_wheel(void);
void func_801075D4_winners_wheel(omObjData *obj);
void func_801077F4_winners_wheel(void);
void func_80107820_winners_wheel(void);
void func_801078D8_winners_wheel(void);
void func_80107B04_winners_wheel(omObjData *obj);
void func_80107B0C_winners_wheel(void);
void func_80107BE0_winners_wheel(void);
void func_80107CB4_winners_wheel(void);
void func_80107D50_winners_wheel(void);
void func_80107F4C_winners_wheel(omObjData *obj);
void func_8010842C_winners_wheel(void);
void func_80108458_winners_wheel(void);
void func_801089C8_winners_wheel(void);
void func_801089F4_winners_wheel(void);
void func_80108E80_winners_wheel(void);
void func_80108F04_winners_wheel(s32 arg0);
void func_80109050_winners_wheel(void);
void func_8010907C_winners_wheel(void);
void func_80109104_winners_wheel(void);
void func_80109130_winners_wheel(void);
void func_80109388_winners_wheel(void);
void func_80109454_winners_wheel(void);
void func_801095E4_winners_wheel(omObjData *obj);
void func_8010985C_winners_wheel(void);
void func_80109A18_winners_wheel(omObjData *obj);
void func_80109BAC_winners_wheel(void);
void func_80109BF0_winners_wheel(void);
void func_80109C1C_winners_wheel(void);
void func_80109B90_winners_wheel(void);
void func_80109D44_winners_wheel(void);
void func_80109E90_winners_wheel(omObjData *obj);
void func_80109F80_winners_wheel(void);
void func_80109FAC_winners_wheel(void);
void func_8010A190_winners_wheel(void);

void func_801059A0_winners_wheel(void) {
    omInitObjMan(30, 10);
    func_8001FE20_main(16);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    func_8010A190_winners_wheel();
    func_8004A208_main();
    Hu3DBGColorSet(0, 0, 0);
    func_800E5EA0_minigame(&D_8010A260_winners_wheel);
    WipeCreateIn(0xFF, 16);
    func_80105AB0_winners_wheel();
    func_80105BA8_winners_wheel();
    func_801063B0_winners_wheel();
    func_80106910_winners_wheel();
    func_801070CC_winners_wheel();
    func_801078D8_winners_wheel();
    func_80107D50_winners_wheel();
    func_80109454_winners_wheel();
    func_80109D44_winners_wheel();
    D_8010A466_winners_wheel = 0;
    CZoom = 1800.0f;
    D_800EBE24_minigame = 0;
    D_8010A464_winners_wheel = 0;
    omAddObj(0x50, 0, 0, -1, func_80105FE4_winners_wheel);
    HuAudSeqPlay(0x44);
}

void func_80105AB0_winners_wheel(void) {
    Vec pos;
    Vec target;
    s16 sprite;

    sprite = espEntry(HuSprAnimDataRead(0x5C0006), 0, 1);
    espDispOff(sprite);
    pos.x = 0.0f;
    pos.y = 200.0f;
    pos.z = 2625.0f;
    target.x = -0.9f;
    target.y = -21.9f;
    target.z = -253.6f;
    func_8004B760_main(100, D_800CD1DC_main[sprite].unk04, func_8004BCE4_main, 11.1f, &pos, &target);
}

void func_80105BA8_winners_wheel(void) {
    omObjData *obj;
    WinnersWheelSign *sign;

    obj = D_8010A498_winners_wheel = omAddObj(10, 1, 0, -1, func_80105C5C_winners_wheel);
    sign = obj->data = HuMemAllocTag(sizeof(WinnersWheelSign), 0x7918);
    obj->model[0] = func_8000B108_main(0x5C0000, 0x699);
    func_8001C814_main(obj->model[0], 1, 1);
    omSetTra(obj, -175.0f, -400.0f, 400.0f);
    obj->func = func_80105C5C_winners_wheel;
    sign->flags = 0;
    sign->result = 0;
}

void func_80105C5C_winners_wheel(omObjData *obj) {
    WinnersWheelSign *sign = obj->data;

    if (sign->flags & 1) {
        if (Hu3DData[obj->model[0]].motTime >= D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
            sign->flags &= ~1;
            func_80105F18_winners_wheel();
        }
    }
    if (sign->flags & 2) {
        if (Hu3DData[obj->model[0]].motTime <= 0.0f) {
            sign->flags &= ~2;
            if (sign->result != 0) {
                func_80105F60_winners_wheel();
            }
        }
    }
    if (sign->flags & 4) {
        obj->trans.y -= 2.0f;
        if (obj->trans.y <= -400.0f) {
            sign->flags &= ~4;
            func_8001C258_main(obj->model[0], 4, 4);
        }
    }
    if (sign->flags & 8) {
        obj->trans.y += 4.0f;
        if (obj->trans.y >= -350.0f && obj->trans.y < -346.0f) {
            HuAudFXPlay(0x4CA);
        }
        if (obj->trans.y >= -200.0f) {
            obj->trans.y = -200.0f;
            sign->flags &= ~8;
        }
    }
}

void func_80105E78_winners_wheel(s32 result) {
    WinnersWheelSign *sign = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 0);
    func_8001C814_main(D_8010A498_winners_wheel->model[0], 1, 0);
    sign->flags |= 1;
    sign->result = result;
    if (result == 0) {
        func_80106718_winners_wheel();
        func_80108E80_winners_wheel();
    } else {
        func_80106734_winners_wheel();
        func_80108F04_winners_wheel(result);
    }
}

void func_80105F18_winners_wheel(void) {
    WinnersWheelSign *sign = D_8010A498_winners_wheel->data;

    func_8001C814_main(D_8010A498_winners_wheel->model[0], 4, 4);
    sign->flags |= 2;
}

void func_80105F60_winners_wheel(void) {
    WinnersWheelSign *sign = D_8010A498_winners_wheel->data;

    sign->flags |= 4;
    HuAudFXPlay(0x4CA);
}

void func_80105F94_winners_wheel(void) {
    WinnersWheelSign *sign = D_8010A498_winners_wheel->data;

    sign->flags |= 8;
}

void func_80105FB0_winners_wheel(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_80105FE4_winners_wheel(omObjData *obj) {
    if (D_800D530C_main != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (func_800E6F40_minigame(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 15) {
                func_8010842C_winners_wheel();
            }
            break;
        case 1:
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                omAddPrcObj(func_80109388_winners_wheel, 0x50, 0, 0);
                D_8010A464_winners_wheel = 1;
            }
            if (D_8010A464_winners_wheel == 1) {
                if (!(GwPlayer[D_8010A48C_winners_wheel].stat & 1)) {
                    if (D_800D5558_main[GwPlayer[D_8010A48C_winners_wheel].pad] == 0x8000) {
                        func_80106EB0_winners_wheel(1);
                        D_8010A464_winners_wheel = 3;
                    }
                } else if (--D_8010A490_winners_wheel == 0) {
                    func_80106EB0_winners_wheel(1);
                    D_8010A464_winners_wheel = 3;
                }
            }
            if (D_8010A464_winners_wheel == 2) {
                func_80106EB0_winners_wheel(2);
                D_8010A464_winners_wheel = 0;
            }
            break;
        case 3:
            if (func_800E6E9C_minigame() == 1) {
                func_80109050_winners_wheel();
                func_801077F4_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
                    func_8010985C_winners_wheel();
                }
            }
            if (D_8010A464_winners_wheel == 4) {
                func_80106750_winners_wheel();
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 17) {
                    func_80109F80_winners_wheel();
                } else {
                    func_80109BF0_winners_wheel();
                    func_80109BAC_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A464_winners_wheel == 5) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
                    func_801089C8_winners_wheel();
                }
                D_8010A464_winners_wheel = 0;
            }
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
                D_8010A260_winners_wheel.resultType = MG_RESULT_GOT_ITEM;
            } else {
                D_8010A260_winners_wheel.resultType = MG_RESULT_GAME_OVER;
            }
            break;
        case 4:
            if (func_800E6E9C_minigame() == 1) {
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
                    func_80106F54_winners_wheel();
                    func_80107BE0_winners_wheel();
                } else {
                    func_8010701C_winners_wheel();
                    func_80107CB4_winners_wheel();
                    HuAudFXPlay(0x4CF);
                }
            }
            break;
        case 5:
            if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = D_8010A468_winners_wheel[D_8010A480_winners_wheel];
            } else {
                GwPlayer[D_8010A48C_winners_wheel].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80105FB0_winners_wheel;
            break;
    }
}

void func_801063B0_winners_wheel(void) {
    omObjData *obj;
    WinnersWheelWheel *wheel;

    obj = omAddObj(0xFF, 3, 0, -1, func_80106514_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelWheel), 0x7918);
    D_8010A49C_winners_wheel = obj;
    wheel = obj->data;
    obj->model[0] = func_8000B108_main(0x5C0001, 0x6B9);
    obj->model[1] = func_8000B108_main(0x5C0002, 0x6B9);
    obj->model[2] = func_8000B108_main(0x5C0004, 0xA99);
    obj->func = func_80106514_winners_wheel;
    wheel->flags = 0;
    wheel->speed = 0.0f;
    wheel->rot = 0.0f;
    wheel->angle = 0.0f;
    wheel->scale = 0.93f;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, wheel->scale, wheel->scale, 1.0f);
    Hu3DModelPosSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 10.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 180.0f, 180.0f);
    Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, 0.0f);
}

void func_80106514_winners_wheel(omObjData *obj) {
    WinnersWheelWheel *wheel = obj->data;

    func_80088910_main(Hu3DData[obj->model[0]].mtx, 0.0f, 0.0f, -wheel->angle);
    omSetRot(obj, wheel->rot, 0.0f, 0.0f);
    Hu3DModelRotSet(obj->model[1], wheel->rot, 180.0f, 180.0f);
    Hu3DModelRotSet(obj->model[2], wheel->rot, 0.0f, 0.0f);
    omSetSca(obj, wheel->scale, wheel->scale, 1.0f);
    if (wheel->flags & 1) {
        wheel->angle += wheel->speed;
        if (wheel->angle >= 360.0f) {
            wheel->angle -= 360.0f;
        }
    }
    if (wheel->flags & 2) {
        wheel->speed += 0.2f;
        if (wheel->speed >= 2.4f) {
            wheel->speed = 2.4f;
            wheel->flags &= ~2;
        }
    }
    if (wheel->flags & 4) {
        wheel->speed -= 0.2f;
        if (wheel->speed <= 0.0f) {
            wheel->speed = 0.2f;
        }
        if ((s32)wheel->angle % 20 == 0) {
            wheel->speed = 0.0f;
            wheel->flags &= ~4;
            wheel->flags &= ~1;
        }
    }
}

void func_80106718_winners_wheel(void) {
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;

    wheel->flags |= 3;
}

void func_80106734_winners_wheel(void) {
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;

    wheel->flags |= 5;
}

void func_80106750_winners_wheel(void) {
    omAddPrcObj(func_8010677C_winners_wheel, 0x50, 0, 0);
}

void func_8010677C_winners_wheel(void) {
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;
    WinnersWheelPanels *panels = D_8010A4A0_winners_wheel->data;
    WinnersWheelPanelFrames *frames = D_8010A4A4_winners_wheel->data;
    WinnersWheelPrize *prize;
    s32 i;
    s32 j;

    for (i = 0; i < 30; i++) {
        wheel->rot += 6.0f;
        for (j = 0; j < 6; j++) {
            panels->rot[j] += 6.0f;
            panels->unk_90 = cosdf(i * 6.0f);
            panels->unk_94 = cosdf(i * 6.0f);
        }
        for (j = 0; j < 6; j++) {
            frames->rot[j] += 6.0f;
        }
        if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] != 17) {
            prize = D_8010A4A8_winners_wheel->data;
            prize->angle += 6.0f;
            prize->pos.y = sindf(prize->angle - 180.0f) * 2.0f;
            prize->pos.z = cosdf(prize->angle) * 2.0f;
        }
        HuPrcVSleep();
    }
    D_8010A464_winners_wheel = 5;
    omDelPrcObj(NULL);
}

void func_80106910_winners_wheel(void) {
    // Copied onto the stack but never read.
    s32 unused[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 modelFiles[8] = { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0 };
    s32 motions[8][4] = {
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
        { 0x00, 0x8C, 0x2F, 0x36 },
    };
    s32 spriteFiles[8] = { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B };
    s32 spriteFiles2[8] = { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D };
    s32 spriteFiles3[8] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C };
    WinnersWheelPlayer *player;
    omObjData *obj;
    s32 dir;
    s16 chr;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010A48C_winners_wheel = i;
            break;
        }
    }
    obj = omAddObj(0x50, 5, 10, -1, func_80106D2C_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPlayer), 0x7918);
    D_8010A4B4_winners_wheel = obj;
    player = obj->data;
    player->unk_04 = 0;
    player->flags = 0;
    player->result = 0;
    player->scale = 0.93f;
    chr = GwPlayer[D_8010A48C_winners_wheel].chr;
    dir = D_8010A28C_winners_wheel[chr] << 16;
    obj->model[0] = func_8000B108_main(dir | modelFiles[chr], 0x6C9);
    player->pos.x = -170.0f;
    player->pos.y = -125.0f;
    player->pos.z = 230.0f;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        func_8000B460_main(obj, i, func_80017BB8_main(chr, motions[chr][i]));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    D_8010A4AC_winners_wheel[0] = func_80017790_main(obj->model[0], 1, D_8010A2AC_winners_wheel[chr], dir | spriteFiles[chr]);
    D_8010A4AC_winners_wheel[1] = func_80017AD8_main(dir | spriteFiles3[chr]);
    D_8010A4AC_winners_wheel[2] = func_80017AD8_main(dir | spriteFiles2[chr]);
    func_8001C514_main(obj->model[0]);
}

void func_80106D2C_winners_wheel(omObjData *obj) {
    WinnersWheelPlayer *player = obj->data;

    omSetSca(obj, player->scale, player->scale, player->scale);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    if (player->flags & 1) {
        if (Hu3DData[obj->model[0]].motTime >= D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
            func_8001C814_main(obj->model[0], 4, 4);
            if (player->result != 0) {
                player->flags |= 2;
            }
            player->flags &= ~1;
        }
    }
    if (player->flags & 2) {
        if (Hu3DData[obj->model[0]].motTime <= 0.0f) {
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
            player->flags &= ~2;
        }
    }
}

void func_80106EB0_winners_wheel(s32 result) {
    WinnersWheelPlayer *player = D_8010A4B4_winners_wheel->data;

    player->flags |= 1;
    player->result = result;
    Hu3DMotionShiftSet(D_8010A4B4_winners_wheel->model[0], Hu3DData[D_8010A4B4_winners_wheel->motion[1]].motId, 0,
                       10, 0);
    func_8001C814_main(D_8010A4B4_winners_wheel->model[0], 4, 0);
    HuAudFXPlay(0x4C9);
    func_80105E78_winners_wheel(result);
}

void func_80106F54_winners_wheel(void) {
    s32 chr = GwPlayer[D_8010A48C_winners_wheel].chr;

    Hu3DMotionShiftSet(D_8010A4B4_winners_wheel->model[0], Hu3DData[D_8010A4B4_winners_wheel->motion[2]].motId, 0,
                       10, 0);
    func_80017954_main(D_8010A4B4_winners_wheel->model[0], 1, D_8010A2AC_winners_wheel[chr],
                       D_8010A4AC_winners_wheel[1]);
    func_80045ED0_main((D_8010A28C_winners_wheel[chr] << 16) | 0x2F);
}

void func_8010701C_winners_wheel(void) {
    s32 chr = GwPlayer[D_8010A48C_winners_wheel].chr;

    Hu3DMotionShiftSet(D_8010A4B4_winners_wheel->model[0], Hu3DData[D_8010A4B4_winners_wheel->motion[3]].motId, 0,
                       10, 0);
    func_80017954_main(D_8010A4B4_winners_wheel->model[0], 1, D_8010A2AC_winners_wheel[chr],
                       D_8010A4AC_winners_wheel[2]);
}

void func_801070CC_winners_wheel(void) {
    s32 counts[16];
    s32 cpuOffsets[6] = { 30, 45, 60, 73, 85, 98 };
    WinnersWheelPanels *panels;
    omObjData *obj;
    void *data;
    s16 sprite;
    s32 bowserSlot;
    s32 item;
    s32 total;
    s32 range;
    s32 next;
    s32 i;
    s32 j;

    obj = omAddObj(0xFF, 6, 0, -1, func_801075D4_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPanels), 0x7918);
    D_8010A4A0_winners_wheel = obj;
    panels = obj->data;
    bowserSlot = (u8)(rand8() % 6);
    D_8010A468_winners_wheel[bowserSlot] = 17;
    data = DataRead(0x5C0007);
    sprite = Hu3DSprModelCreate(data, 0x699, 8);
    DataClose(data);
    obj->model[bowserSlot] = D_800CBB60_main[sprite].modelId;
    panels->angle[bowserSlot] = bowserSlot * 60.0f + 30.0f;
    panels->rot[bowserSlot] = 0.0f;
    panels->x[bowserSlot] = sindf(panels->angle[bowserSlot]) * 70.0f;
    panels->y[bowserSlot] = cosdf(panels->angle[bowserSlot]) * 70.0f;
    panels->z[bowserSlot] = 5.0f;
    panels->scale[bowserSlot] = 1.395f;
    for (i = 0; i < 16; i++) {
        counts[i] = 0;
    }
    for (next = 0, i = 0; i < 6; i++) {
        if (i == bowserSlot) {
            continue;
        }
        item = D_800A11D0_main[next++];
        counts[item]++;
        D_8010A468_winners_wheel[i] = item;
        data = DataRead(0x21002C);
        sprite = Hu3DSprModelCreate(data, 0x699, 8);
        func_8001473C_main(sprite, item);
        DataClose(data);
        obj->model[i] = D_800CBB60_main[sprite].modelId;
        panels->angle[i] = i * 60.0f + 30.0f;
        panels->rot[i] = 0.0f;
        panels->x[i] = sindf(panels->angle[i]) * 70.0f;
        panels->y[i] = cosdf(panels->angle[i]) * 70.0f;
        panels->z[i] = 5.0f;
        panels->scale[i] = 1.395f;
    }
    panels->unk_90 = 1.0f;
    panels->unk_94 = 1.0f;
    omSetTra(obj, panels->x[0], panels->y[0], panels->z[0]);
    D_8010A480_winners_wheel = 0;
    D_8010A484_winners_wheel = 5;
    if (GwPlayer[D_8010A48C_winners_wheel].stat & 1) {
        item = (u8)(rand8() % 100);
        for (j = 0, total = 0; j < 5; j++) {
            if (item >= total && item < total + D_800A11DC_main[j]) {
                break;
            }
            total += D_800A11DC_main[j];
        }
        if (j == 5) {
            j = 4;
        }
        if (j >= bowserSlot) {
            j++;
        }
        range = 4 - GwPlayer[D_8010A48C_winners_wheel].cpu_difficulty;
        range *= 5;
        D_8010A490_winners_wheel = cpuOffsets[j] + rand8() % (range * 2) - range;
    }
}

void func_801075D4_winners_wheel(omObjData *obj) {
    WinnersWheelPanels *panels = obj->data;
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        panels->x[i] = sindf(panels->angle[i] + wheel->angle) * 70.0f * wheel->scale;
        panels->y[i] = cosdf(panels->angle[i] + wheel->angle) * 70.0f * wheel->scale * panels->unk_90;
        panels->z[i] = panels->unk_94 * 5.0f;
        func_80088910_main(Hu3DData[obj->model[i]].mtx, 0.0f, 0.0f, -panels->angle[i] - wheel->angle);
        if (i == 0) {
            omSetTra(obj, panels->x[0], panels->y[0], panels->z[0]);
            omSetRot(obj, panels->rot[0], 0.0f, 0.0f);
            omSetSca(obj, panels->scale[0], panels->scale[0], panels->scale[0]);
        } else {
            Hu3DModelPosSet(obj->model[i], panels->x[i], panels->y[i], panels->z[i]);
            Hu3DModelScaleSet(obj->model[i], panels->scale[i], panels->scale[i], panels->scale[i]);
            Hu3DModelRotSet(obj->model[i], panels->rot[i], 0.0f, 0.0f);
        }
        if (panels->z[i] <= 0.0f) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

void func_801077F4_winners_wheel(void) {
    omAddPrcObj(func_80107820_winners_wheel, 0x50, 0, 0);
}

void func_80107820_winners_wheel(void) {
    WinnersWheelPanels *panels = D_8010A4A0_winners_wheel->data;
    s32 i;

    for (i = 0; i < 60; i++) {
        panels->scale[D_8010A480_winners_wheel] = sindf(i * 36.0f) * 0.3f + 1.395f;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_801078D8_winners_wheel(void) {
    f32 x[2];
    f32 y[2];
    f32 z[2];
    f32 rotY[2];
    s32 attr;
    WinnersWheelNpc *npc;
    omObjData *obj;
    s32 i;

    x[0] = -300.0f;
    x[1] = 300.0f;
    y[0] = -62.5f;
    y[1] = -12.5f;
    z[0] = -275.0f;
    z[1] = -275.0f;
    rotY[0] = 30.0f;
    rotY[1] = -30.0f;
    attr = 0x699;
    for (i = 0; i < 2; i++) {
        obj = omAddObj(0xFF, 1, 5, -1, func_80107B04_winners_wheel);
        D_8010A4B8_winners_wheel[i] = obj;
        npc = obj->data = HuMemAllocTag(sizeof(WinnersWheelNpc), 0x7918);
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0xA0147, attr);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010A4B8_winners_wheel[0]->model[0]);
        }
        npc->flags = 0;
        npc->index = i;
        omSetTra(obj, x[i], y[i], z[i]);
        omSetRot(obj, 0.0f, rotY[i], 0.0f);
        omSetSca(obj, 0.7f, 0.7f, 0.7f);
        func_8000B460_main(obj, 0, 0xA0148);
        func_8000B460_main(obj, 1, 0xA0149);
        func_8000B460_main(obj, 2, 0xA014A);
        func_8000B460_main(obj, 3, 0xA014B);
        func_8000B460_main(obj, 4, 0xA014C);
    }
}

void func_80107B04_winners_wheel(omObjData *obj) {
}

void func_80107B0C_winners_wheel(void) {
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[0]->model[0], Hu3DData[D_8010A4B8_winners_wheel[0]->motion[0]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[1]->model[0], Hu3DData[D_8010A4B8_winners_wheel[1]->motion[0]].motId, 0,
                       10, 0);
    func_8001C814_main(D_8010A4B8_winners_wheel[0]->model[0], 2, 2);
    func_8001C814_main(D_8010A4B8_winners_wheel[1]->model[0], 2, 2);
}

void func_80107BE0_winners_wheel(void) {
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[0]->model[0], Hu3DData[D_8010A4B8_winners_wheel[0]->motion[2]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[1]->model[0], Hu3DData[D_8010A4B8_winners_wheel[1]->motion[2]].motId, 0,
                       10, 0);
    func_8001C814_main(D_8010A4B8_winners_wheel[0]->model[0], 2, 2);
    func_8001C814_main(D_8010A4B8_winners_wheel[1]->model[0], 2, 2);
}

void func_80107CB4_winners_wheel(void) {
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[0]->model[0], Hu3DData[D_8010A4B8_winners_wheel[0]->motion[3]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[1]->model[0], Hu3DData[D_8010A4B8_winners_wheel[1]->motion[3]].motId, 0,
                       10, 0);
}

void func_80107D50_winners_wheel(void) {
    s32 attr;
    WinnersWheelPointer *pointer;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 18, 0, -1, func_80107F4C_winners_wheel);
    pointer = obj->data = HuMemAllocTag(sizeof(WinnersWheelPointer), 0x7918);
    D_8010A4C0_winners_wheel = obj;
    attr = 0x6BD;
    pointer->speed = 0.0f;
    pointer->flags = 0x20;
    pointer->count = 0;
    pointer->mode = 0;
    for (i = 0; i < 18; i++) {
        pointer->rawRot[i] = pointer->rot[i] = i * 20.0f;
        if (i == 0) {
            obj->model[i] = func_8000B108_main(0x5C0005, attr);
            omSetTra(obj, sindf(pointer->rot[i]) * -10.5f, cosdf(pointer->rot[i]) * -10.5f, 0.0f);
            omSetRot(obj, 0.0f, 0.0f, -pointer->rot[i]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], sindf(pointer->rot[i]) * -10.5f, cosdf(pointer->rot[i]) * -10.5f, 0.0f);
            Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, -pointer->rot[i]);
        }
    }
}

void func_80107F4C_winners_wheel(omObjData *obj) {
    WinnersWheelPointer *pointer = obj->data;
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;
    f32 minSpeed;
    f32 rot;
    s32 i;

    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetRot(obj, 0.0f, 0.0f, -pointer->rot[0]);
        } else {
            Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, -pointer->rot[i]);
        }
    }
    if (pointer->flags & 1) {
        pointer->rawRot[0] -= pointer->speed;
        pointer->rot[0] = (s32)((pointer->rawRot[0] + 0.5f) / 20.0f) * 20.0f;
        if (pointer->rawRot[0] <= 0.0f) {
            pointer->rawRot[0] += 360.0f;
        }
        rot = pointer->rot[0] + 10.0f;
        D_8010A480_winners_wheel = (s32)((360.0f - wheel->angle + rot) / 60.0f) % 6;
    }
    if (pointer->flags & 8) {
        rot = pointer->rot[0] + 10.0f;
        D_8010A480_winners_wheel = (s32)((360.0f - wheel->angle + rot) / 60.0f) % 6;
        D_8010A484_winners_wheel = 5 - D_8010A480_winners_wheel;
    }
    if (pointer->flags & 2) {
        pointer->speed += 0.29f;
        if (pointer->speed >= 20.0f) {
            pointer->speed = 20.0f;
            pointer->flags &= ~2;
        }
    }
    if (pointer->flags & 4) {
        if (pointer->rot[1] != pointer->rot[0]) {
            HuAudFXPlay(0x4C8);
        }
        if (pointer->mode != 2) {
            minSpeed = 1.0f;
        } else {
            minSpeed = 2.0f;
        }
        if (pointer->speed >= minSpeed) {
            pointer->speed -= 0.02f;
            D_8010A288_winners_wheel -= 9;
            if (D_8010A288_winners_wheel < -900) {
                D_8010A288_winners_wheel = -900;
            }
            HuAudFXPitchSet(D_8010A494_winners_wheel, D_8010A288_winners_wheel);
        }
        if (pointer->mode != 2) {
            if (pointer->rot[0] == pointer->target && pointer->rot[1] != pointer->rot[0]) {
                pointer->count--;
            }
            if (pointer->count == 0) {
                pointer->speed = 0.0f;
                pointer->flags &= ~4;
                pointer->flags &= ~1;
                HuAudFXStop(D_8010A494_winners_wheel);
                HuAudFXPlay(0x4CD);
                if (D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 17) {
                    omVibrate(D_8010A48C_winners_wheel, 10, 0, 10);
                } else {
                    omVibrate(D_8010A48C_winners_wheel, 2, 3, 10);
                }
                func_800E6F0C_minigame(MG_STATE_FINISH);
            }
        } else if (pointer->speed <= minSpeed && D_8010A468_winners_wheel[D_8010A480_winners_wheel] == 17) {
            pointer->speed = 0.0f;
            pointer->flags &= ~4;
            pointer->flags &= ~1;
            omVibrate(D_8010A48C_winners_wheel, 10, 0, 10);
            func_800E6F0C_minigame(MG_STATE_FINISH);
            HuAudFXStop(D_8010A494_winners_wheel);
            HuAudFXPlay(0x4CD);
        }
        pointer->rot[1] = pointer->rot[0];
    }
}

void func_8010842C_winners_wheel(void) {
    omAddPrcObj(func_80108458_winners_wheel, 0x50, 0, 0);
}

void func_80108458_winners_wheel(void) {
    WinnersWheelPointer *pointer = D_8010A4C0_winners_wheel->data;
    WinnersWheelSign *sign = D_8010A498_winners_wheel->data;
    s32 i;
    s32 j;

    pointer->flags |= 8;
    pointer->flags &= ~0x20;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
    func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 0);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]) * -10.5f, cosdf(pointer->rot[0]) * -10.5f, 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(pointer->rot[i]) * -10.5f,
                            cosdf(pointer->rot[i]) * -10.5f, 0.0f);
        }
    }
    for (i = 0; i < 18; i++) {
        if (i == 9) {
            continue;
        }
        pointer->rot[0] = i * 20.0f;
        pointer->rot[1] = 340.0f - pointer->rot[0];
        omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]) * -10.5f, cosdf(pointer->rot[0]) * -10.5f, -1.0f);
        Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[1], sindf(pointer->rot[1]) * -10.5f,
                        cosdf(pointer->rot[1]) * -10.5f, -1.0f);
        HuAudFXPlay(0x4C8);
        HuPrcSleep(4);
    }
    pointer->flags &= ~8;
    D_8010A484_winners_wheel = -1;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 4);
    func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 4);
    pointer->flags |= 0x20;
    func_80109104_winners_wheel();
    while (CZoom < 2887.1f) {
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        Hu3DMotionShiftSet(D_8010A4B8_winners_wheel[i]->model[0],
                           Hu3DData[D_8010A4B8_winners_wheel[i]->motion[4]].motId, 0, 10, 0);
        func_8001C814_main(D_8010A4B8_winners_wheel[i]->model[0], 2, 2);
    }
    func_80105F94_winners_wheel();
    for (i = 0; i < 18; i++) {
        pointer->rot[i] = i * 20.0f;
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]), 0.0f);
        }
        func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 18; i++) {
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
        }
        pointer->flags |= 0x10;
        pointer->flags &= ~0x20;
        HuPrcSleep(10);
        for (i = 0; i < 18; i++) {
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 4);
        }
        pointer->flags &= ~0x10;
        pointer->flags |= 0x20;
        HuPrcSleep(10);
    }
    while (sign->flags & 8) {
        HuPrcVSleep();
    }
    func_80106EB0_winners_wheel(0);
    func_80107B0C_winners_wheel();
    pointer->flags &= ~0x20;
    omDelPrcObj(NULL);
}

void func_801089C8_winners_wheel(void) {
    omAddPrcObj(func_801089F4_winners_wheel, 0x50, 0, 0);
}

void func_801089F4_winners_wheel(void) {
    WinnersWheelPointer *pointer = D_8010A4C0_winners_wheel->data;
    s32 i;
    s32 j;

    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
        } else {
            Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]), 0.0f);
        }
    }
    while (TRUE) {
        func_8001C258_main(D_8010A4C0_winners_wheel->model[0], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[1], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[2], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[3], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[4], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[5], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[6], 4, 0);
        func_8001C258_main(D_8010A4C0_winners_wheel->model[7], 4, 0);
        for (i = 0; i < 36; i++) {
            pointer->rot[0] = i * 20.0f;
            pointer->rot[1] = 340.0f - i * 20.0f;
            pointer->rot[2] = i * 20.0f + 180.0f;
            pointer->rot[3] = 160.0f - i * 20.0f;
            pointer->rot[4] = i * 20.0f + 100.0f;
            pointer->rot[5] = 80.0f - i * 20.0f;
            pointer->rot[6] = i * 20.0f + 280.0f;
            pointer->rot[7] = 260.0f - i * 20.0f;
            omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), -1.0f);
            for (j = 1; j < 8; j++) {
                Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[j], sindf(pointer->rot[j]), cosdf(pointer->rot[j]),
                                -1.0f);
            }
            HuPrcSleep(1);
        }
        for (i = 0; i < 18; i++) {
            pointer->rot[i] = i * 20.0f;
            if (i == 0) {
                omSetTra(D_8010A4C0_winners_wheel, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
            } else {
                Hu3DModelPosSet(D_8010A4C0_winners_wheel->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]),
                                0.0f);
            }
            func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
        }
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 18; i++) {
                func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 0);
            }
            HuPrcSleep(1);
            for (i = 0; i < 18; i++) {
                func_8001C258_main(D_8010A4C0_winners_wheel->model[i], 4, 4);
            }
            HuPrcSleep(1);
        }
    }
}

void func_80108E80_winners_wheel(void) {
    WinnersWheelPointer *pointer = D_8010A4C0_winners_wheel->data;

    pointer->flags |= 3;
    pointer->rot[0] = 340.0f;
    pointer->rawRot[0] = 340.0f;
    func_8001C258_main(D_8010A4C0_winners_wheel->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    omSetRot(D_8010A4C0_winners_wheel, 0.0f, 0.0f, pointer->rot[0]);
    D_8010A48A_winners_wheel = HuAudFXPlay(0x4C7);
}

void func_80108F04_winners_wheel(s32 mode) {
    WinnersWheelPointer *pointer = D_8010A4C0_winners_wheel->data;
    f32 steps;
    s32 chance;

    pointer->flags |= 4;
    pointer->mode = mode;
    chance = (u8)(rand8() % 20);
    if (chance < 3) {
        steps = 4.0f;
    } else if (chance < 6) {
        steps = 8.0f;
    } else {
        steps = 6.0f;
    }
    steps -= 4.0f;
    pointer->target = pointer->rot[0] - steps * 20.0f;
    pointer->count = 2;
    if (steps == 0.0f) {
        pointer->count = 1;
    }
    if (pointer->target < 0.0f) {
        pointer->target += 360.0f;
    }
    pointer->speed = 4.0f;
    HuAudFXStop(D_8010A48A_winners_wheel);
    D_8010A494_winners_wheel = HuAudFXPlay(0x4CB);
}

void func_80109050_winners_wheel(void) {
    omAddPrcObj(func_8010907C_winners_wheel, 0x50, 0, 0);
}

void func_8010907C_winners_wheel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(*D_8010A4C0_winners_wheel->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuPrcSleep(10);
        func_8001C258_main(*D_8010A4C0_winners_wheel->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        HuPrcSleep(10);
    }
    D_8010A464_winners_wheel = 4;
    omDelPrcObj(NULL);
}

void func_80109104_winners_wheel(void) {
    omAddPrcObj(func_80109130_winners_wheel, 0x50, 0, 0);
}

void func_80109130_winners_wheel(void) {
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;
    WinnersWheelPanels *panels = D_8010A4A0_winners_wheel->data;
    WinnersWheelPlayer *player = D_8010A4B4_winners_wheel->data;
    f32 scaleStep = 0.002333333f;
    s32 i;
    s32 j;

    for (i = 0; i < 30; i++) {
        CZoom += 36.2f;
        for (j = 0; j < 4; j++) {
            CZoomM[j] = CZoom;
        }
        wheel->scale += scaleStep;
        player->scale += scaleStep;
        player->pos.x = (30 - i) * 5.0f / 30.0f + -175.0f;
        player->pos.y = (30 - i) * 0.0f / 30.0f + -125.0f;
        player->pos.z = (30 - i) * -95.0f / 30.0f + 325.0f;
        for (j = 0; j < 6; j++) {
            panels->scale[j] = wheel->scale * 1.5f;
        }
        HuPrcVSleep();
    }
    wheel->scale = 1.0f;
    player->scale = 1.0f;
    for (j = 0; j < 6; j++) {
        panels->scale[j] = 1.5f;
    }
    CZoom = 2887.1f;
    player->pos.x = -175.0f;
    player->pos.y = -125.0f;
    player->pos.z = 325.0f;
    omDelPrcObj(NULL);
}

void func_80109388_winners_wheel(void) {
    s32 seconds = 10;
    s32 frames = 30;

    GMesPosSet(GMesCreate(26, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        func_8003F578_main(seconds);
        HuPrcVSleep();
        if (D_8010A464_winners_wheel == 3) {
            break;
        }
    } while (seconds > 0);
    func_8003F5C0_main();
    if (D_8010A464_winners_wheel != 3) {
        D_8010A464_winners_wheel = 2;
    }
    omDelPrcObj(NULL);
}

void func_80109454_winners_wheel(void) {
    s32 attr = 0x63D;
    WinnersWheelPanelFrames *frames;
    WinnersWheelWheel *wheel;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 6, 0, -1, func_801095E4_winners_wheel);
    D_8010A4A4_winners_wheel = obj;
    frames = obj->data = HuMemAllocTag(sizeof(WinnersWheelPanelFrames), 0x7918);
    wheel = D_8010A49C_winners_wheel->data;
    frames->flags = 0;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x5C0003, attr);
            omSetTra(obj, 0.0f, 0.0f, 6.0f);
            omSetSca(obj, wheel->scale, wheel->scale, 1.0f);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], 0.0f, 0.0f, 6.0f);
            Hu3DModelScaleSet(obj->model[i], wheel->scale, wheel->scale, 1.0f);
        }
        frames->unk_04[i] = 0.0f;
        frames->unk_1C[i] = 0.0f;
        frames->rot[i] = 0.0f;
        frames->angle[i] = i * 60.0f;
    }
}

void func_801095E4_winners_wheel(omObjData *obj) {
    WinnersWheelPanelFrames *frames = obj->data;
    WinnersWheelWheel *wheel = D_8010A49C_winners_wheel->data;
    WinnersWheelPointer *pointer = D_8010A4C0_winners_wheel->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        func_80088910_main(Hu3DData[obj->model[i]].mtx, 0.0f, 0.0f, -frames->angle[i]);
        if (i == 0) {
            omSetRot(obj, frames->rot[0], 0.0f, 0.0f);
            omSetSca(obj, wheel->scale, wheel->scale, 1.0f);
        } else {
            Hu3DModelRotSet(obj->model[i], frames->rot[i], 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], wheel->scale, wheel->scale, 1.0f);
        }
        if (frames->rot[i] >= 90.0f) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
    for (i = 0; i < 6; i++) {
        func_8001C258_main(obj->model[i], 4, 0);
    }
    if (pointer->flags & 0x20) {
        D_8010A480_winners_wheel = D_8010A484_winners_wheel = -1;
    }
    for (i = 0; i < 6; i++) {
        frames->angle[i] = i * 60.0f + wheel->angle;
        if (i == D_8010A480_winners_wheel || i == D_8010A484_winners_wheel || (pointer->flags & 0x10)) {
            func_8001C258_main(obj->model[i], 4, 4);
        }
    }
}

void func_8010985C_winners_wheel(void) {
    s32 itemFiles[16] = { 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C };
    WinnersWheelPrize *prize;
    omObjData *obj;
    void *data;
    s16 sprite;

    obj = omAddObj(0xFE, 1, 0, -1, func_80109A18_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPrize), 0x7918);
    D_8010A4A8_winners_wheel = obj;
    prize = obj->data;
    if (D_8010A480_winners_wheel == 17) {
        data = DataRead(0x5C0007);
    } else {
        data = DataRead(itemFiles[D_8010A468_winners_wheel[D_8010A480_winners_wheel]] | 0x210000);
    }
    sprite = Hu3DSprModelCreate(data, 0x69D, 8);
    DataClose(data);
    obj->model[0] = D_800CBB60_main[sprite].modelId;
    prize->pos.x = 0.0f;
    prize->pos.y = 0.0f;
    prize->pos.z = 2.0f;
    prize->unk_10 = 0.0f;
    prize->angle = 180.0f;
    prize->flags = 0;
    omSetTra(obj, prize->pos.x, prize->pos.y, prize->pos.z);
    omSetSca(obj, 2.2f, 2.2f, 1.0f);
    func_8001C258_main(obj->model[0], 4, 4);
}

void func_80109A18_winners_wheel(omObjData *obj) {
    WinnersWheelPrize *prize = obj->data;

    omSetTra(obj, prize->pos.x, prize->pos.y, prize->pos.z);
    omSetRot(obj, prize->angle, 0.0f, 0.0f);
    if (prize->flags & 1) {
        prize->unk_10 += 5.0f;
        if (prize->unk_10 >= 360.0f) {
            prize->unk_10 -= 360.0f;
        }
        prize->pos.y = sindf(prize->unk_10) * 10.0f + 90.0f;
    }
    if (prize->angle >= 270.0f) {
        func_8001C258_main(obj->model[0], 4, 0);
    }
    if (prize->angle == 270.0f) {
        omVibrate(D_8010A48C_winners_wheel, 2, 2, 20);
        HuAudFXPlay(0x10);
    }
    if (prize->flags & 2) {
        func_8000CFA4_main(D_8010A488_winners_wheel, prize->pos.x, prize->pos.y, prize->pos.z - 2.0f);
    }
}

void func_80109B90_winners_wheel(void) {
    WinnersWheelPrize *prize = D_8010A4A8_winners_wheel->data;

    prize->flags |= 1;
}

void func_80109BAC_winners_wheel(void) {
    D_8010A488_winners_wheel = func_8000CED8_main(0xB0004, 0x6A9);
    ((WinnersWheelPrize *)D_8010A4A8_winners_wheel->data)->flags |= 2;
}

void func_80109BF0_winners_wheel(void) {
    omAddPrcObj(func_80109C1C_winners_wheel, 0x50, 0, 0);
}

void func_80109C1C_winners_wheel(void) {
    WinnersWheelPrize *prize = D_8010A4A8_winners_wheel->data;
    s32 i;

    func_8001C258_main(D_8010A4A8_winners_wheel->model[0], 4, 0);
    HuPrcSleep(30);
    HuAudFXPlay(0x19);
    for (i = 0; i < 31; i++) {
        prize->pos.x = D_8010A4B4_winners_wheel->trans.x * i / 30.0f;
        prize->pos.y = i * 90.0f / 30.0f + sindf(i * 6.0f) * 100.0f;
        prize->pos.z = i * D_8010A4B4_winners_wheel->trans.z / 30.0f;
        HuPrcVSleep();
    }
    func_80109B90_winners_wheel();
    HuAudFXPlay(0x4CE);
    omDelPrcObj(NULL);
}

void func_80109D44_winners_wheel(void) {
    WinnersWheelBowser *bowser;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 2, -1, func_80109E90_winners_wheel);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelBowser), 0x7918);
    D_8010A4C4_winners_wheel = obj;
    bowser = obj->data;
    obj->model[0] = func_8000B108_main(0xA00EE, 0x69D);
    obj->model[1] = func_8000B108_main(9, 0x4AD);
    bowser->pos.x = 0.0f;
    bowser->pos.y = -182.0f;
    bowser->pos.z = -190.0f;
    bowser->flags = 0;
    bowser->unk_14 = 0.0f;
    omSetTra(obj, bowser->pos.x, bowser->pos.y, bowser->pos.z);
    omSetSca(obj, 0.8f, 0.8f, 0.8f);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F0);
    func_8000B460_main(obj, 2, 0xA00F6);
    func_8001C5B4_main(obj->model[0], obj->motion[4]);
    func_8001C814_main(obj->model[0], 2, 2);
}

void func_80109E90_winners_wheel(omObjData *obj) {
    WinnersWheelBowser *bowser = obj->data;
    f32 height;

    height = bowser->pos.y - -182.0f;
    omSetTra(obj, bowser->pos.x, bowser->pos.y, bowser->pos.z);
    Hu3DModelPosSet(obj->model[1], bowser->pos.x, -182.0f, bowser->pos.z);
    if (height >= 0.0f) {
        bowser->shadowScale = (400.0f - height) / 400.0f * 0.8f;
    } else {
        bowser->shadowScale = 0.0f;
    }
    Hu3DModelScaleSet(obj->model[1], bowser->shadowScale * 1.2f, 1.0f, bowser->shadowScale * 1.2f);
}

void func_80109F80_winners_wheel(void) {
    omAddPrcObj(func_80109FAC_winners_wheel, 0x50, 0, 0);
}

void func_80109FAC_winners_wheel(void) {
    WinnersWheelBowser *bowser = D_8010A4C4_winners_wheel->data;
    s32 i;

    func_8001C5B4_main(D_8010A4C4_winners_wheel->model[0], D_8010A4C4_winners_wheel->motion[1]);
    bowser->unk_14 = 50.0f;
    for (i = 0; i < 31; i++) {
        if (i == 5) {
            func_8001C258_main(D_8010A4C4_winners_wheel->model[0], 4, 0);
            func_8001C258_main(D_8010A4C4_winners_wheel->model[1], 4, 0);
            HuAudFXPlay(0x4CC);
            omVibrate(D_8010A48C_winners_wheel, 20, 0, 20);
        }
        bowser->pos.x = 0.0f;
        bowser->pos.y = sindf(i * 6.0f) * 282.0f + -182.0f;
        bowser->pos.z = i * 380.0f / 30.0f - 190.0f;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4CF);
    func_800E6F1C_minigame();
    Hu3DMotionShiftSet(D_8010A4C4_winners_wheel->model[0], Hu3DData[D_8010A4C4_winners_wheel->motion[2]].motId, 0,
                       10, 0);
    func_8001C814_main(D_8010A4C4_winners_wheel->model[0], 2, 2);
    omDelPrcObj(NULL);
}

void func_8010A190_winners_wheel(void) {
    func_8000B5F0_main(1);
    D_8010A460_winners_wheel = func_8000B638_main();
    Hu3DCameraPerspectiveSet(D_8010A460_winners_wheel, 11.1f, 80.0f, 8000.0f);
    CZoom = 2887.1f;
    CRot.x = -4.4f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = -0.9f;
    Center.y = -21.9f;
    Center.z = -253.6f;
}
