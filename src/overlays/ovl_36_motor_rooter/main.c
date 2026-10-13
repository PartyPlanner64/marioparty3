#include "overlays/ovl_36.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hmfman.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "mallocblock.h"
#include "include_asm.h"
#include "input.h"
#include "variables.h"
#include "functions.us.h"

#define PLAYERS_TOTAL 2

// C1F0
void func_8000B5F0_main(u8 arg0);
s32 func_8000B710_main(s32 arg0);

// 14EA0
void func_800142A0_main(s32);

// 20A20
void Hu3DAnimInit(s32);

// unknown
extern u16 D_800D530C_main;
extern s32 D_800A178C_main[][6];

enum {
    FGRP_CAMERA
};

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 obstacleSprites[21];
    /* 0x2E */ s16 obstacleSlots[3];
    /* 0x34 */ s16 obstacleSafeDirections[3][3];
    /* 0x46 */ s16 obstacleFrames[3];
    /* 0x4C */ s16 obstaclePoints[10];
    /* 0x60 */ s16 obstacleDirections[10];
    /* 0x74 */ s16 obstacleTypes[10];
    /* 0x88 */ char unk88[2];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ omObjData *unk8C;
    /* 0x90 */ char unk90[0x64];
} PlayerView; // Size 0xF4

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 pitch;
    /* 0x10 */ f32 yaw;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 segLen;
    /* 0x1C */ f32 invSegLen;
    /* 0x20 */ f32 cumDist;
} PathPoint; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 pitch;
    /* 0x14 */ f32 yaw;
    /* 0x18 */ f32 roll;
} PathPosition; // Size 0x1C

typedef struct {
    /* 0x000 */ PlayerView *views;
    /* 0x004 */ char unk04[8];
    /* 0x00C */ s16 pathPointCount;
    /* 0x00E */ s16 unk0E;
    /* 0x010 */ char unk10[4];
    /* 0x014 */ s16 itemPoints[100];
    /* 0x0DC */ s16 itemDirections[100];
    /* 0x1A4 */ u8 unk1A4[0x30]; // mtx?
} MinigameData;                  // Size 0x1D4

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ char unk04[4];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15[7];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ char unk1E[0xA];
    /* 0x28 */ s16 unk28[5];
    /* 0x32 */ s8 animChange;
    /* 0x34 */ s16 nextAnim;
    /* 0x36 */ char unk36[0x16];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[0x3E];
} D_801137C8_motor_rooter_Struct; // Size 0x8C

void m254_InitEnvironment(void);
void m254_CreateMinigame(void);
void m254_CheckExitRequest(omObjData *object);
void m254_WaitExitWipeOut(omObjData *object);
void m254_ExitOverlay(omObjData *object);
void func_80106044_motor_rooter(omObjData *object);
void func_80106298_motor_rooter(omObjData *object);
void func_801062BC_motor_rooter(omObjData *object);
void func_80106508_motor_rooter(omObjData *object);
void func_80106998_motor_rooter(omObjData *object);
void func_80106BAC_motor_rooter(omObjData *object);
void func_80107210_motor_rooter(omObjData *object);
void func_801079E8_motor_rooter(omObjData *object);
void m254_InitCamera(FuncContext *ctx);
void func_801082E0_motor_rooter(FuncContext *ctx);
void func_80108BF0_motor_rooter(FuncContext *ctx);
void func_80109134_motor_rooter(FuncContext *ctx);
void func_801107FC_motor_rooter(u16 modelId, HuSprite_Unk84_Struct *sprite, u16 frame);
void func_8010CD84_motor_rooter(void *, s32);
s16 func_8010D03C_motor_rooter(f32);
PathPosition func_8010D0AC_motor_rooter(s16, f32);
void func_8010D2E4_motor_rooter(s32);

// BSS
extern PathPoint *D_801137C0_motor_rooter;
extern MinigameData *m254_minigame; // D_801137C4_motor_rooter
extern D_801137C8_motor_rooter_Struct *D_801137C8_motor_rooter;
extern s16 D_801137CC_motor_rooter;
extern s16 D_801137CE_motor_rooter;
extern s16 D_801137D0_motor_rooter;
extern s16 D_801137D2_motor_rooter;
extern s16 m254_playerId[]; // D_801137D4_motor_rooter
extern s16 D_801137D8_motor_rooter;
extern s16 D_8011345A_motor_rooter[];
extern s16 D_8011349E_motor_rooter[];

extern s32 D_80111550_motor_rooter;
extern s32 D_8011245C_motor_rooter;

extern s16 D_801135E0_motor_rooter[];
extern s16 D_801135EC_motor_rooter[];
extern s16 D_801135FC_motor_rooter[];
extern s16 D_80113458_motor_rooter;
extern s16 D_80113498_motor_rooter;

void m254_OverlayMain(void) {
    m254_InitEnvironment();
}

void m254_InitEnvironment(void) {
    omObjData *temp_v0;

    Hu3DAnimInit(50);
    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0->work[0] = 2;
    omSetStatBit(temp_v0, 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 152.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 60.0f, 40.0f, 4000.0f);
    ScissorSet(1, 168.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 60.0f, 40.0f, 4000.0f);
    func_8001F38C_main(0xFF, 0xFF, 0xFF);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    m254_CreateSystem();
    m254_CreateMinigame();
    omAddObj(100, 0, 0, -1, func_80106044_motor_rooter);
    omAddObj(1000, 0, 0, -1, m254_CheckExitRequest);
    func_80045010_main(D_801135E0_motor_rooter, 1);
    func_80045010_main(D_801135EC_motor_rooter, 1);
    func_80045010_main(D_801135FC_motor_rooter, 1);
}

void m254_CreateMinigame(void) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m254_playerId[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m254_playerId[1] = i;
                player2Set = TRUE;
            }
        }
    }
    m254_minigame = HuMemAllocTag(sizeof(MinigameData), 31000);
    memset(m254_minigame, 0, sizeof(MinigameData));
    m254_minigame->views = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerView), 31000);
    memset(m254_minigame->views, 0, PLAYERS_TOTAL * sizeof(PlayerView));
    D_801137CE_motor_rooter = (rand16() % 201) / 100;
    switch (D_801137CE_motor_rooter) {
        case 0:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(&D_80111550_motor_rooter, 321);
            break;
        case 1:
            D_801137CC_motor_rooter = 300;
            func_8010CD84_motor_rooter(&D_8011245C_motor_rooter, 341);
            break;
        default:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(&D_80111550_motor_rooter, 321);
            D_801137CE_motor_rooter = 0;
            break;
    }
    func_8010D2E4_motor_rooter(0);
    D_801137C8_motor_rooter = HuMemAllocTag(2 * sizeof(D_801137C8_motor_rooter_Struct), 31000); // PLAYERS_TOTAL?
    memset(D_801137C8_motor_rooter, 0, 2 * sizeof(D_801137C8_motor_rooter_Struct));
}

void m254_CheckExitRequest(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = m254_WaitExitWipeOut;
    }
}

void m254_WaitExitWipeOut(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m254_ExitOverlay;
    }
}

void m254_ExitOverlay(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105F04_motor_rooter(void) {
    s16 i;

    for (i = 0; i < 2; i++) {
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
    }
    m254_UpdateFuncGroup(FGRP_CAMERA);
}

void func_80106044_motor_rooter(omObjData *object) {
    s16 i;

    func_8001EF24_main(0x3CA, 1000, 0xFF, 0xFF, 0xFF);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 2; i++) {
        D_800EC1C0_minigame[i] = omAddObj(10, 2, 0, -1, func_801062BC_motor_rooter);
        m254_minigame->views[i].unk00 = omAddObj(100, 21, 0, -1, func_80106508_motor_rooter);
        m254_minigame->views[i].unk8C = omAddObj(200, 15, 0, -1, func_80106998_motor_rooter);
        omAddObj(500, 1, 0, -1, func_80107210_motor_rooter);
        omAddObj(800, 5, 0, -1, func_801079E8_motor_rooter);
        D_800EC598_minigame[i] = D_801137C8_motor_rooter[i].unk00 = omAddObj(300, 11, 40, -1, func_80106BAC_motor_rooter);
    }
    memset(m254_minigame->unk1A4, 0, sizeof(m254_minigame->unk1A4));
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, m254_InitCamera, 0, FALSE);
    m254_SetFunc(1, 0, -1, NULL, func_80108BF0_motor_rooter, 0, FALSE);
    WipeCreateIn(0xFF, 0x10);
    object->func = func_80106298_motor_rooter;
}

void func_80106298_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(1);
    func_80105F04_motor_rooter();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801062BC_motor_rooter);

void func_801064EC_motor_rooter(omObjData *object) {
    m254_SyncWithModel(object);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80106508_motor_rooter);

void func_80106968_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(2);
    m254_SyncWithModel(object);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80106998_motor_rooter);

void func_80106B7C_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(3);
    m254_SyncWithModel(object);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80106BAC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801070CC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80107210_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801076AC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801079E8_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80107D50_motor_rooter);

void m254_InitCamera(FuncContext *ctx) {
    s16 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 100.0f;
        CenterM[i].x = D_801137C0_motor_rooter[0].x;
        CenterM[i].y = D_801137C0_motor_rooter[0].y;
        CenterM[i].z = D_801137C0_motor_rooter[0].z;
        CRotM[i].x = D_801137C0_motor_rooter[0].pitch - 180.0f;
        CRotM[i].y = D_801137C0_motor_rooter[0].yaw;
        CRotM[i].z = D_801137C0_motor_rooter[0].unk14;
    }
    m254_ResetFunc(FGRP_CAMERA, ctx);
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, func_801082E0_motor_rooter, 0, FALSE);
}

void func_801082E0_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *var_s1;
    PathPosition position;
    s16 temp_v0;
    s16 i;

    view = m254_minigame->views;
    var_s1 = D_801137C8_motor_rooter;
    for (i = 0; i < 2; i++, var_s1++, view++) {
        if (var_s1->unk08 & 0x80) {
            continue;
        }
        temp_v0 = func_8010D03C_motor_rooter(var_s1->unk0C);
        position = func_8010D0AC_motor_rooter(temp_v0, var_s1->unk0C);
        CenterM[i].x = position.x;
        CenterM[i].y = position.y;
        CenterM[i].z = position.z;
        CRotM[i].x = position.pitch - 180.0f;
        CRotM[i].y = position.yaw;
        CRotM[i].z = position.roll;
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
        var_s1->unk1C = temp_v0 + 1;
        view->unk8A = temp_v0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108514_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801087C0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801089B8_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108BF0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80108E6C_motor_rooter);

void func_80108FDC_motor_rooter(FuncContext *ctx) {
    s16 timer;

    if (D_80113498_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113498_motor_rooter = 3;
        }
        if (D_80113498_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else if (D_80113498_motor_rooter == 1) {
        timer = ctx->work.s16[0]++;
        if (timer == 15) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 2;
        }
    } else {
        timer = ctx->work.s16[0]++;
        if (timer == 0) {
            HuAudSeqFadeOut(120);
            GMesCreate(0x11);
        } else if (GMesStatGet() == 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 1;
        }
    }
}

void func_80109134_motor_rooter(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            WipeCreateOut(0, 20);
            ctx->state = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_801091A0_motor_rooter);

void func_8010961C_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    omObjData *object;
    s16 i;
    s16 j;

    view = ctx->data;
    object = view->unk00;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            func_801107FC_motor_rooter(object->model[i * 7 + j],
                                       func_80055194_main(view->obstacleSprites[i * 7 + j]),
                                       view->obstacleFrames[i]);
        }
        view->obstacleFrames[i] = view->obstacleFrames[i] + 1 < 5 ? view->obstacleFrames[i] + 1 : 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010972C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80109C94_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_80109EFC_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A174_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010A440_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010ABC4_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010AF0C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010B394_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010B970_motor_rooter);

void func_8010BB78_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;

    if (player->unk08 & 0x11) {
        return;
    }
    if (player->unk08 & 0x100) {
        if (player->unk10 < 20.0f) {
            player->unk10 *= 2.0f;
            if (player->unk10 > 20.0f) {
                player->unk10 = 20.0f;
            }
        } else {
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
            player->unk08 &= ~0x100;
        }
    } else {
        player->unk4C++;
        if (player->unk4C > D_8011349E_motor_rooter[player->unk14]) {
            player->unk4C = 0;
            if (player->unk14 - 1 > 0) {
                player->unk14--;
                player->unk28[player->unk14] = 2;
                player->unk10 -= 4.0f;
            }
            func_8004AAD0_main(D_801137D8_motor_rooter, 64);
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345A_motor_rooter[player->unk14]);
        }
    }
}

void func_8010BCD0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    omObjData *object;
    HmfModel *model;

    player = ctx->data;
    object = player->unk00;
    model = &HmfModelData[object->model[0]];
    if (model->unk40 >= D_800CCF58_main[model->unk02].unk02 - 1) {
        player->animChange = 1;
    }
    if (player->animChange) {
        func_800E5690_minigame(object, player->nextAnim);
        player->animChange = 0;
        if (player->nextAnim == 13) {
            func_80045F1C_main(D_800A178C_main[GwPlayer[m254_playerId[object->work[0]]].chr][0] | 0x2F, -1, 0);
        }
    }
}

void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *player, s16 anim, s8 change) {
    player->animChange = change;
    player->nextAnim = anim;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010BDF0_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C084_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C44C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010C824_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010CB2C_motor_rooter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010CD84_motor_rooter);

s16 func_8010D03C_motor_rooter(f32 dist) {
    s16 i;
    PathPoint *point;

    point = &D_801137C0_motor_rooter[m254_minigame->pathPointCount - 1];
    for (i = m254_minigame->pathPointCount; i > 0; i--, point--) {
        if (point->cumDist <= dist) {
            break;
        }
    }
    return i - 1;
}

PathPosition func_8010D0AC_motor_rooter(s16 index, f32 dist) {
    PathPosition position;
    PathPoint *point;
    f32 fraction;
    f32 start;
    f32 end;

    point = &D_801137C0_motor_rooter[index];
    fraction = dist - point->cumDist;
    fraction *= point->invSegLen;
    end = point[1].x;
    start = point->x;
    position.x = (end - start) * fraction + start;
    end = point[1].y;
    start = point->y;
    position.y = (end - start) * fraction + start;
    end = point[1].z;
    start = point->z;
    position.z = (end - start) * fraction + start;
    end = point[1].pitch;
    start = point->pitch;
    position.pitch = (end - start) * fraction + start;
    end = point[1].yaw;
    start = point->yaw;
    position.yaw = (end - start) * fraction + start;
    position.roll = 0;
    return position;
}

void func_8010D1A8_motor_rooter(s16 point, s16 direction) {
    s16 index = D_801137D2_motor_rooter;

    if (point >= D_801137CC_motor_rooter) {
        return;
    }
    if (index >= 10) {
        return;
    }
    m254_minigame->views[0].obstaclePoints[index] = m254_minigame->views[1].obstaclePoints[index] = point;
    direction += 4;
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->views[0].obstacleDirections[index] = m254_minigame->views[1].obstacleDirections[index] = direction;
    m254_minigame->views[0].obstacleTypes[index] = m254_minigame->views[1].obstacleTypes[index] = (rand16() % 3) + 1;
    D_801137D2_motor_rooter++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_36_motor_rooter/main", func_8010D2E4_motor_rooter);

void func_8010DC3C_motor_rooter(s16 point, s16 direction) {
    if (point >= D_801137CC_motor_rooter || D_801137D0_motor_rooter >= 100) {
        return;
    }
    if (D_801137D0_motor_rooter >= 16 &&
        point - m254_minigame->itemPoints[D_801137D0_motor_rooter - 15] < m254_minigame->unk0E) {
        return;
    }
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->itemPoints[D_801137D0_motor_rooter] = point;
    m254_minigame->itemDirections[D_801137D0_motor_rooter++] = direction;
}

void func_8010DD10_motor_rooter(FuncContext *ctx) {
    ctx->work.s8[0]++;
    if (ctx->work.s8[0] >= 6) {
        ctx->work.s8[0] = 0;
        if (D_800CDA7C_main[0] & 0x2000) {
            D_80113458_motor_rooter = D_80113458_motor_rooter + 1 < 3 ? D_80113458_motor_rooter + 1 : 0;
        }
    }
    sprintf(D_800D5218_main, "CONT TYPE %d", D_80113458_motor_rooter);
    print8(16, 80, D_800D5218_main);
}
