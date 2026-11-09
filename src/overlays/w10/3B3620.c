#include "common.h"
#include "game/aura.h"
#include "game/malloc.h"
#include "game/wipe.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/1063F0.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/F5E80.h"

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} W10SprGroup; // sizeof 0x08

extern s16 D_8010B7F0_w10[4];
extern Vec D_8010B818_w10[];
extern Vec D_8010B854_w10[];
extern s16 D_8010B890_w10[];
extern s16 D_8010B898_w10[];
extern s32 D_8010B8E8_w10[];
extern s16 D_8010B8FC_w10;
extern Object *D_8010BA24_w10;
extern Process *D_8010BA28_w10;
extern Object *D_8010BA2C_w10;
extern Object *D_8010BA30_w10;
extern Object *D_8010BA38_w10[2];
extern s16 D_8010BA4C_w10;
extern s16 D_8010BA4E_w10;
extern s16 D_8010BA50_w10;
extern s16 D_8010BA52_w10;
extern s16 D_8010BA54_w10;
extern Vec D_8010BA58_w10;
extern Object *D_8010BA68_w10;
extern Object *D_8010BA6C_w10;
extern Object *D_8010BA70_w10;
extern Object *D_8010BA74_w10;

void func_801059D0_w10(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80105A0C_w10(void) {
    s32 i;

    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->chr = D_8010B7F0_w10[i];
    }
    omOvlReturnEx(1);
}

void func_80105AB8_w10(void) {
    Object *obj;

    if (D_8010BA24_w10 != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    MBModelTempAllocFree(obj);
    D_8010BA24_w10 = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8010BA28_w10 = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x25)->coords);
}

void func_80105B70_w10(void) {
    D_8010BA24_w10 = NULL;
    func_80105AB8_w10();
}

void func_80105B90_w10(void) {
    Object *obj;

    if (D_8010BA2C_w10 != NULL) {
        return;
    }
    obj = MBModelCreate(0xA, NULL);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001FA68_main(obj->omObj2->model[0]);
    D_8010BA2C_w10 = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x24)->coords);
    MBModelDispOff(obj);
}

void func_80105C28_w10(void) {
    D_8010BA2C_w10 = NULL;
    func_80105B90_w10();
}

void func_80105C48_w10(s16 arg0) {
    Object *obj;

    if (D_8010BA38_w10[arg0] != NULL) {
        return;
    }
    if (D_8010BA30_w10 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8010BA30_w10 = obj;
    } else {
        obj = MBModelLinkCreate(D_8010BA30_w10);
    }
    D_8010BA38_w10[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2F)->coords);
    HuVecAdd(&obj->coords, &D_8010B818_w10[arg0], &obj->coords);
    obj->omObj1->rot.x = D_8010B854_w10[arg0].x;
    obj->omObj1->rot.z = D_8010B854_w10[arg0].z;
}

void func_80105D6C_w10(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010BA38_w10[i] = NULL;
        func_80105C48_w10(i);
    }
}

void func_80105DC4_w10(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void func_80105E08_w10(void) {
}

void func_80105E10_w10(void) {
    UnkEA790Struct *win;
    s32 count;
    s32 sel;
    s32 i;

    MBPlayerMotionSet(-1, -1, 2);
    func_80105DC4_w10();
    win = func_800D76A0_shared_board(-1, D_8010B890_w10);
    func_800D742C_shared_board(win, -1, 0);
    if (MBPlayerComCheck(-1)) {
        count = D_8010B898_w10[GwSystem.boardData.halfWordBytes[0]++];
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }
    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80105E08_w10();
    if (sel == 0) {
        MBMoveNextMasuSet(-1, 1, 0);
    } else {
        MBMoveNextMasuSet(-1, 2, 0);
    }
    omDelPrcObj(NULL);
}

void func_80105F20_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->stat |= PLAYER_IS_CPU;
    }
}

void func_80105F64_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F292C_shared_board());
    HuPrcChildWatch();
}

void func_80105FA0_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F29EC_shared_board());
    HuPrcChildWatch();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105FDC_w10);

void func_801061E8_w10(W10SprGroup *arg0) {
    HuSprAnimKill(arg0->sprites[0]);
    HuSprAnimKill(arg0->sprites[1]);
    HuSprAnimKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreeTemp(arg0);
}

void func_80106230_w10(s16 arg0, s16 x, s16 y) {
    void *data;

    D_8010BA4C_w10 = HuSprGrpCreate(1, 0);
    data = DataRead(D_8010B8E8_w10[arg0]);
    D_8010BA4E_w10 = HuSprAnimRead(data);
    HuSprGrpMemberSet(D_8010BA4C_w10, 0, D_8010BA4E_w10, 0);
    HuSprPriSet(D_8010BA4C_w10, 0, 0xB);
    HuSprAttrSet(D_8010BA4C_w10, 0, 0x1000);
    HuSprPosSet(D_8010BA4C_w10, 0, x, y);
    DataClose(data);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106314_w10);

void func_8010649C_w10(void) {
    HuSprAnimKill(D_8010BA4E_w10);
    HuSprGrpKill(D_8010BA4C_w10);
}

void func_801064C8_w10(void) {
    f32 scale;

    for (scale = 1.0f; scale > 0.0f; scale -= 1.0f / 6.0f) {
        HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 0.0f);
    HuSprAnimKill(D_8010BA52_w10);
    HuSprGrpKill(D_8010BA50_w10);
}

// NON_MATCHING: register allocation differs for the player_obj load in the
// MBPlayerGet(-1) branch (target loads into a0, current into v0).
#ifdef NON_MATCHING
void func_80106574_w10(void) {
    Vec *pos;

    D_8010BA54_w10 = -1;
    MBPlayerPosFixSet(0, 1);
    MBPlayerPosFixSet(1, 1);
    MBPlayerPosFixSet(2, 1);
    MBPlayerPosFixSet(3, 1);
    WipeCreateIn(2, 0x10);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    while (TRUE) {
        if (D_8010BA54_w10 < 0) {
            if (D_8010BA54_w10 == -2) {
                pos = &D_8010BA58_w10;
            } else {
                pos = &MBPlayerGet(-1)->player_obj->coords;
            }
        } else {
            pos = &MBMasuGet(D_8010BA54_w10)->coords;
        }
        MBCameraPos3DSet(pos);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106574_w10);
#endif

void func_80106670_w10(s16 arg0) {
    D_8010BA54_w10 = arg0;
    MBCameraSpeedSet(4.0f);
}

void func_8010669C_w10(void) {
    HuPrcSleep(3);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    MBCameraSpeedSet(-1.0f);
}

void func_801066E8_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBPlayerGet(i);
        player->color = 0;
        player->stat &= ~2;
    }
}

void func_80106730_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBStatusColorSet(i, MBPlayerGet(i)->color);
    }
}

// NON_MATCHING: the address of GwSystem.current_player_index is CSE'd into a
// register for the increment/reset, while the target rematerializes it.
#ifdef NON_MATCHING
void func_80106774_w10(void) {
    GW_PLAYER *player;
    s32 i;

    if (++GwSystem.current_player_index >= 4) {
        GwSystem.current_player_index = 0;
    }
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        MBPlayerForwardSet(i);
        MBMotionSet(player->player_obj, -1, 2);
        MBPlayerPosFixSet(i, 1);
    }
    MBCameraZoomSet(1.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106774_w10);
#endif

void func_8010681C_w10(Vec *arg0) {
    func_800FF840_shared_board(arg0);
}

void func_80106838_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBTelopCreate(GwSystem.current_player_index));
    HuPrcChildWatch();
}

// NON_MATCHING: the address of GwSystem.current_player_index is CSE'd into s0
// across the calls, while the target reloads it directly each time.
#ifdef NON_MATCHING
void func_8010687C_w10(s16 arg0) {
    Process *process;
    Process *child;

    func_800DCD64_shared_board(GwSystem.current_player_index, arg0);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
    child = func_800DD6C4_shared_board(GwSystem.current_player_index);
    HuPrcChildWatch();
    HuPrcChildLink(process, child);
    HuPrcChildWatch();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010687C_w10);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106908_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106DEC_w10);

void func_80106ED8_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

void func_80106F40_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
}

void func_80106F7C_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    while (HuWinStatGet(guide->amount) != 0) {
        HuPrcVSleep();
    }
}

void func_80106FE0_w10(UnkMBGuideData *guide) {
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107028_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801070B8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010714C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107228_w10);

void func_80107344_w10(s16 arg0) {
    D_8010B8FC_w10 = arg0;
}

void func_80107350_w10(omObjData *obj) {
    D_8010BA68_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    D_8010BA6C_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 3.0f;
}

void func_801073C8_w10(omObjData *obj) {
    D_8010BA70_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    D_8010BA74_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 10.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107780_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107ABC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107D64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107F0C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801084CC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80108F28_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109050_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010AF68_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B12C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B434_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B5A4_w10);
