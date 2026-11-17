#include "common.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"

// Object data for the pointer object held in m259_pointerObj,
// created in m259_PointerObjCreate. The pointer is made of 18 models.
typedef struct WinnersWheelPointer {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 rot[18];
    /* 0x4C */ f32 rawRot[18];
    /* 0x94 */ f32 speed;
    /* 0x98 */ f32 target;
    /* 0x9C */ s32 count;
    /* 0xA0 */ s32 mode;
} WinnersWheelPointer; // Size 0xA4

// Object data for the sign object held in m259_signObj,
// created in m259_SignObjCreate.
typedef struct WinnersWheelSign {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 result;
} WinnersWheelSign; // Size 0x8

// Object data for the wheel object held in m259_wheelObj,
// created in m259_WheelObjCreate.
typedef struct WinnersWheelWheel {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 rot;
    /* 0x10 */ f32 angle;
} WinnersWheelWheel; // Size 0x14

// Object data for the player object held in m259_playerObj,
// created in m259_PlayerObjCreate.
typedef struct WinnersWheelPlayer {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 result;
    /* 0x0C */ f32 scale;
    /* 0x10 */ Vec pos;
} WinnersWheelPlayer; // Size 0x1C

// Object data for the prize panel object held in m259_panelObj,
// created in m259_PanelObjCreate. Holds per-panel state for the six
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

// Object data for the panel frame object held in m259_frameObj,
// created in m259_FrameObjCreate.
typedef struct WinnersWheelPanelFrames {
    /* 0x00 */ s32 flags;
    /* 0x04 */ f32 unk_04[6];
    /* 0x1C */ f32 unk_1C[6];
    /* 0x34 */ f32 rot[6];
    /* 0x4C */ f32 angle[6];
} WinnersWheelPanelFrames; // Size 0x64

// Object data for the won prize object held in m259_prizeObj,
// created in m259_PrizeObjCreate.
typedef struct WinnersWheelPrize {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 angle;
} WinnersWheelPrize; // Size 0x18

// Object data for the two NPC objects held in m259_npcObjTbl,
// created in m259_NpcObjCreate.
typedef struct WinnersWheelNpc {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 index;
} WinnersWheelNpc; // Size 0x8

// Object data for the Bowser object held in m259_koopaObj,
// created in m259_KoopaObjCreate. Bowser appears when the pointer
// lands on the Bowser panel (panel item 17).
typedef struct WinnersWheelBowser {
    /* 0x00 */ s32 flags;
    /* 0x04 */ Vec pos;
    /* 0x10 */ f32 shadowScale;
    /* 0x14 */ f32 unk_14;
} WinnersWheelBowser; // Size 0x18

MinigameFlow m259_mgFlow = {
    MG_STATE_OPENING, MINIGAME_ITEM, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_GOT_ITEM, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    240, 300, -1, 150, 150
};
s16 m259_slowSePitch = 0;
s32 m259_chrDirTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s32 m259_chrAnimNoTbl[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s32 m259_cameraNo BSS;
u8 m259_seqNo BSS;
s16 m259_unusedNo BSS;
s32 m259_panelItemTbl[6] BSS;
s32 m259_panelNo BSS;
s32 m259_oppPanelNo BSS;
s16 m259_prizeEffNo BSS;
s16 m259_spinSeNo BSS;
s32 m259_playerNo BSS;
s32 m259_comPressTimer BSS;
s16 m259_slowSeNo BSS;
omObjData *m259_signObj BSS;
omObjData *m259_wheelObj BSS;
omObjData *m259_panelObj BSS;
omObjData *m259_frameObj BSS;
omObjData *m259_prizeObj BSS;
s16 m259_playerAnimTbl[3] BSS;
omObjData *m259_playerObj BSS;
omObjData *m259_npcObjTbl[2] BSS;
omObjData *m259_pointerObj BSS;
omObjData *m259_koopaObj BSS;

extern u16 mgInstColumnTbl[];
extern u16 mgInstSlotTbl[];

void omCameraViewSprDraw(struct CameraViewData *data);
void m259_BackCreate(void);
void m259_SignObjCreate(void);
void m259_SignObjMain(omObjData *obj);
void m259_SignRewindStart(void);
void m259_SignSinkStart(void);
void m259_ExitObjMain(omObjData *obj);
void m259_MainObjMain(omObjData *obj);
void m259_WheelObjCreate(void);
void m259_WheelObjMain(omObjData *obj);
void m259_SignRiseStart(void);
void m259_WheelSpinStart(void);
void m259_WheelStopStart(void);
void m259_WheelFlipStart(void);
void m259_WheelFlipProc(void);
void m259_PlayerObjCreate(void);
void m259_PlayerObjMain(omObjData *obj);
void m259_PlayerHitStart(s32 arg0);
void m259_PlayerWinMotSet(void);
void m259_PlayerLoseMotSet(void);
void m259_PanelObjCreate(void);
void m259_PanelObjMain(omObjData *obj);
void m259_PanelPulseStart(void);
void m259_PanelPulseProc(void);
void m259_NpcObjCreate(void);
void m259_NpcObjMain(omObjData *obj);
void m259_NpcIdleMotSet(void);
void m259_NpcWinMotSet(void);
void m259_NpcLoseMotSet(void);
void m259_PointerObjCreate(void);
void m259_PointerObjMain(omObjData *obj);
void m259_IntroStart(void);
void m259_IntroProc(void);
void m259_PointerFlashStart(void);
void m259_PointerFlashProc(void);
void m259_PointerSpinStart(void);
void m259_PointerStopStart(s32 arg0);
void m259_PointerBlinkStart(void);
void m259_PointerBlinkProc(void);
void m259_CameraZoomStart(void);
void m259_CameraZoomProc(void);
void m259_TimerProc(void);
void m259_FrameObjCreate(void);
void m259_FrameObjMain(omObjData *obj);
void m259_PrizeObjCreate(void);
void m259_PrizeObjMain(omObjData *obj);
void m259_PrizeEffStart(void);
void m259_PrizeShowStart(void);
void m259_PrizeShowProc(void);
void m259_PrizeFloatStart(void);
void m259_KoopaObjCreate(void);
void m259_KoopaObjMain(omObjData *obj);
void m259_KoopaJumpStart(void);
void m259_KoopaJumpProc(void);
void m259_CameraInit(void);

void m259_ObjectSetup(void) {
    omInitObjMan(30, 10);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    m259_CameraInit();
    omGameSysInit();
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&m259_mgFlow);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m259_BackCreate();
    m259_SignObjCreate();
    m259_WheelObjCreate();
    m259_PlayerObjCreate();
    m259_PanelObjCreate();
    m259_NpcObjCreate();
    m259_PointerObjCreate();
    m259_FrameObjCreate();
    m259_KoopaObjCreate();
    m259_unusedNo = 0;
    CZoom = 1800.0f;
    mgFieldStat = 0;
    m259_seqNo = 0;
    omAddObj(0x50, 0, 0, -1, m259_MainObjMain);
    HuAudSeqPlay(0x44);
}

void m259_BackCreate(void) {
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
    omCameraViewCreate(100, esprite[sprite].unk04, omCameraViewSprDraw, 11.1f, &pos, &target);
}

void m259_SignObjCreate(void) {
    omObjData *obj;
    WinnersWheelSign *sign;

    obj = m259_signObj = omAddObj(10, 1, 0, -1, m259_SignObjMain);
    sign = obj->data = HuMemAllocTag(sizeof(WinnersWheelSign), 0x7918);
    obj->model[0] = Hu3DModelRead(0x5C0000, 0x699);
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    omSetTra(obj, -175.0f, -400.0f, 400.0f);
    obj->func = m259_SignObjMain;
    sign->flags = 0;
    sign->result = 0;
}

void m259_SignObjMain(omObjData *obj) {
    WinnersWheelSign *sign = obj->data;

    if (sign->flags & 1) {
        if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
            sign->flags &= ~1;
            m259_SignRewindStart();
        }
    }
    if (sign->flags & 2) {
        if (Hu3DData[obj->model[0]].motTime <= 0.0f) {
            sign->flags &= ~2;
            if (sign->result != 0) {
                m259_SignSinkStart();
            }
        }
    }
    if (sign->flags & 4) {
        obj->trans.y -= 2.0f;
        if (obj->trans.y <= -400.0f) {
            sign->flags &= ~4;
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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

void m259_SignHitStart(s32 result) {
    WinnersWheelSign *sign = m259_signObj->data;

    Hu3DMotionAttrSet(m259_signObj->model[0], 4, 0);
    Hu3DMotionAttrSet(m259_signObj->model[0], 1, 0);
    sign->flags |= 1;
    sign->result = result;
    if (result == 0) {
        m259_WheelSpinStart();
        m259_PointerSpinStart();
    } else {
        m259_WheelStopStart();
        m259_PointerStopStart(result);
    }
}

void m259_SignRewindStart(void) {
    WinnersWheelSign *sign = m259_signObj->data;

    Hu3DMotionAttrSet(m259_signObj->model[0], 4, 4);
    sign->flags |= 2;
}

void m259_SignSinkStart(void) {
    WinnersWheelSign *sign = m259_signObj->data;

    sign->flags |= 4;
    HuAudFXPlay(0x4CA);
}

void m259_SignRiseStart(void) {
    WinnersWheelSign *sign = m259_signObj->data;

    sign->flags |= 8;
}

void m259_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void m259_MainObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (MgFlowMain(obj)) {
        case 0:
            if (MgFlowStatTimeGet() == 15) {
                m259_IntroStart();
            }
            break;
        case 1:
            break;
        case 2:
            if (MgFlowStatTimeGet() == 0) {
                omAddPrcObj(m259_TimerProc, 0x50, 0, 0);
                m259_seqNo = 1;
            }
            if (m259_seqNo == 1) {
                if (!(GwPlayer[m259_playerNo].stat & 1)) {
                    if (HuPadBtnDown[GwPlayer[m259_playerNo].pad] == A_BUTTON) {
                        m259_PlayerHitStart(1);
                        m259_seqNo = 3;
                    }
                } else if (--m259_comPressTimer == 0) {
                    m259_PlayerHitStart(1);
                    m259_seqNo = 3;
                }
            }
            if (m259_seqNo == 2) {
                m259_PlayerHitStart(2);
                m259_seqNo = 0;
            }
            break;
        case 3:
            if (MgFlowStatTimeGet() == 1) {
                m259_PointerBlinkStart();
                m259_PanelPulseStart();
                if (m259_panelItemTbl[m259_panelNo] != 17) {
                    m259_PrizeObjCreate();
                }
            }
            if (m259_seqNo == 4) {
                m259_WheelFlipStart();
                if (m259_panelItemTbl[m259_panelNo] == 17) {
                    m259_KoopaJumpStart();
                } else {
                    m259_PrizeShowStart();
                    m259_PrizeEffStart();
                }
                m259_seqNo = 0;
            }
            if (m259_seqNo == 5) {
                if (m259_panelItemTbl[m259_panelNo] != 17) {
                    m259_PointerFlashStart();
                }
                m259_seqNo = 0;
            }
            if (m259_panelItemTbl[m259_panelNo] != 17) {
                m259_mgFlow.resultType = MG_RESULT_GOT_ITEM;
            } else {
                m259_mgFlow.resultType = MG_RESULT_GAME_OVER;
            }
            break;
        case 4:
            if (MgFlowStatTimeGet() == 1) {
                if (m259_panelItemTbl[m259_panelNo] != 17) {
                    m259_PlayerWinMotSet();
                    m259_NpcWinMotSet();
                } else {
                    m259_PlayerLoseMotSet();
                    m259_NpcLoseMotSet();
                    HuAudFXPlay(0x4CF);
                }
            }
            break;
        case 5:
            if (m259_panelItemTbl[m259_panelNo] != 17) {
                GwPlayer[m259_playerNo].bonusCoin = m259_panelItemTbl[m259_panelNo];
            } else {
                GwPlayer[m259_playerNo].bonusCoin = -1;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            obj->func = m259_ExitObjMain;
            break;
    }
}

void m259_WheelObjCreate(void) {
    omObjData *obj;
    WinnersWheelWheel *wheel;

    obj = omAddObj(0xFF, 3, 0, -1, m259_WheelObjMain);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelWheel), 0x7918);
    m259_wheelObj = obj;
    wheel = obj->data;
    obj->model[0] = Hu3DModelRead(0x5C0001, 0x6B9);
    obj->model[1] = Hu3DModelRead(0x5C0002, 0x6B9);
    obj->model[2] = Hu3DModelRead(0x5C0004, 0xA99);
    obj->func = m259_WheelObjMain;
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

void m259_WheelObjMain(omObjData *obj) {
    WinnersWheelWheel *wheel = obj->data;

    HuRotateRPYF(Hu3DData[obj->model[0]].mtx, 0.0f, 0.0f, -wheel->angle);
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

void m259_WheelSpinStart(void) {
    WinnersWheelWheel *wheel = m259_wheelObj->data;

    wheel->flags |= 3;
}

void m259_WheelStopStart(void) {
    WinnersWheelWheel *wheel = m259_wheelObj->data;

    wheel->flags |= 5;
}

void m259_WheelFlipStart(void) {
    omAddPrcObj(m259_WheelFlipProc, 0x50, 0, 0);
}

void m259_WheelFlipProc(void) {
    WinnersWheelWheel *wheel = m259_wheelObj->data;
    WinnersWheelPanels *panels = m259_panelObj->data;
    WinnersWheelPanelFrames *frames = m259_frameObj->data;
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
        if (m259_panelItemTbl[m259_panelNo] != 17) {
            prize = m259_prizeObj->data;
            prize->angle += 6.0f;
            prize->pos.y = sindf(prize->angle - 180.0f) * 2.0f;
            prize->pos.z = cosdf(prize->angle) * 2.0f;
        }
        HuPrcVSleep();
    }
    m259_seqNo = 5;
    omDelPrcObj(NULL);
}

void m259_PlayerObjCreate(void) {
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
            m259_playerNo = i;
            break;
        }
    }
    obj = omAddObj(0x50, 5, 10, -1, m259_PlayerObjMain);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPlayer), 0x7918);
    m259_playerObj = obj;
    player = obj->data;
    player->unk_04 = 0;
    player->flags = 0;
    player->result = 0;
    player->scale = 0.93f;
    chr = GwPlayer[m259_playerNo].chr;
    dir = m259_chrDirTbl[chr] << 16;
    obj->model[0] = Hu3DModelRead(dir | modelFiles[chr], 0x6C9);
    player->pos.x = -170.0f;
    player->pos.y = -125.0f;
    player->pos.z = 230.0f;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        omObjMotionRead(obj, i, CharMotionDataNumGet(chr, motions[chr][i]));
    }
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    m259_playerAnimTbl[0] = CharAnimCreate(obj->model[0], 1, m259_chrAnimNoTbl[chr], dir | spriteFiles[chr]);
    m259_playerAnimTbl[1] = Hu3DAnimDataRead(dir | spriteFiles3[chr]);
    m259_playerAnimTbl[2] = Hu3DAnimDataRead(dir | spriteFiles2[chr]);
    Hu3DModelDynamicFree(obj->model[0]);
}

void m259_PlayerObjMain(omObjData *obj) {
    WinnersWheelPlayer *player = obj->data;

    omSetSca(obj, player->scale, player->scale, player->scale);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    if (player->flags & 1) {
        if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
            Hu3DMotionAttrSet(obj->model[0], 4, 4);
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

void m259_PlayerHitStart(s32 result) {
    WinnersWheelPlayer *player = m259_playerObj->data;

    player->flags |= 1;
    player->result = result;
    Hu3DMotionShiftSet(m259_playerObj->model[0], Hu3DData[m259_playerObj->motion[1]].motId, 0,
                       10, 0);
    Hu3DMotionAttrSet(m259_playerObj->model[0], 4, 0);
    HuAudFXPlay(0x4C9);
    m259_SignHitStart(result);
}

void m259_PlayerWinMotSet(void) {
    s32 chr = GwPlayer[m259_playerNo].chr;

    Hu3DMotionShiftSet(m259_playerObj->model[0], Hu3DData[m259_playerObj->motion[2]].motId, 0,
                       10, 0);
    CharAnimSet(m259_playerObj->model[0], 1, m259_chrAnimNoTbl[chr],
                       m259_playerAnimTbl[1]);
    HuAudCharVoicePlay((m259_chrDirTbl[chr] << 16) | 0x2F);
}

void m259_PlayerLoseMotSet(void) {
    s32 chr = GwPlayer[m259_playerNo].chr;

    Hu3DMotionShiftSet(m259_playerObj->model[0], Hu3DData[m259_playerObj->motion[3]].motId, 0,
                       10, 0);
    CharAnimSet(m259_playerObj->model[0], 1, m259_chrAnimNoTbl[chr],
                       m259_playerAnimTbl[2]);
}

void m259_PanelObjCreate(void) {
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

    obj = omAddObj(0xFF, 6, 0, -1, m259_PanelObjMain);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPanels), 0x7918);
    m259_panelObj = obj;
    panels = obj->data;
    bowserSlot = (u8)(rand8() % 6);
    m259_panelItemTbl[bowserSlot] = 17;
    data = DataRead(0x5C0007);
    sprite = Hu3DSprModelCreate(data, 0x699, 8);
    DataClose(data);
    obj->model[bowserSlot] = Hu3DSprModelData[sprite].modelId;
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
        item = mgInstColumnTbl[next++];
        counts[item]++;
        m259_panelItemTbl[i] = item;
        data = DataRead(0x21002C);
        sprite = Hu3DSprModelCreate(data, 0x699, 8);
        Hu3DSprModelPointSet(sprite, item);
        DataClose(data);
        obj->model[i] = Hu3DSprModelData[sprite].modelId;
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
    m259_panelNo = 0;
    m259_oppPanelNo = 5;
    if (GwPlayer[m259_playerNo].stat & 1) {
        item = (u8)(rand8() % 100);
        for (j = 0, total = 0; j < 5; j++) {
            if (item >= total && item < total + mgInstSlotTbl[j]) {
                break;
            }
            total += mgInstSlotTbl[j];
        }
        if (j == 5) {
            j = 4;
        }
        if (j >= bowserSlot) {
            j++;
        }
        range = 4 - GwPlayer[m259_playerNo].cpu_difficulty;
        range *= 5;
        m259_comPressTimer = cpuOffsets[j] + rand8() % (range * 2) - range;
    }
}

void m259_PanelObjMain(omObjData *obj) {
    WinnersWheelPanels *panels = obj->data;
    WinnersWheelWheel *wheel = m259_wheelObj->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        panels->x[i] = sindf(panels->angle[i] + wheel->angle) * 70.0f * wheel->scale;
        panels->y[i] = cosdf(panels->angle[i] + wheel->angle) * 70.0f * wheel->scale * panels->unk_90;
        panels->z[i] = panels->unk_94 * 5.0f;
        HuRotateRPYF(Hu3DData[obj->model[i]].mtx, 0.0f, 0.0f, -panels->angle[i] - wheel->angle);
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
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void m259_PanelPulseStart(void) {
    omAddPrcObj(m259_PanelPulseProc, 0x50, 0, 0);
}

void m259_PanelPulseProc(void) {
    WinnersWheelPanels *panels = m259_panelObj->data;
    s32 i;

    for (i = 0; i < 60; i++) {
        panels->scale[m259_panelNo] = sindf(i * 36.0f) * 0.3f + 1.395f;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m259_NpcObjCreate(void) {
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
        obj = omAddObj(0xFF, 1, 5, -1, m259_NpcObjMain);
        m259_npcObjTbl[i] = obj;
        npc = obj->data = HuMemAllocTag(sizeof(WinnersWheelNpc), 0x7918);
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0xA0147, attr);
        } else {
            obj->model[0] = Hu3DModelLink(m259_npcObjTbl[0]->model[0]);
        }
        npc->flags = 0;
        npc->index = i;
        omSetTra(obj, x[i], y[i], z[i]);
        omSetRot(obj, 0.0f, rotY[i], 0.0f);
        omSetSca(obj, 0.7f, 0.7f, 0.7f);
        omObjMotionRead(obj, 0, 0xA0148);
        omObjMotionRead(obj, 1, 0xA0149);
        omObjMotionRead(obj, 2, 0xA014A);
        omObjMotionRead(obj, 3, 0xA014B);
        omObjMotionRead(obj, 4, 0xA014C);
    }
}

void m259_NpcObjMain(omObjData *obj) {
}

void m259_NpcIdleMotSet(void) {
    Hu3DMotionShiftSet(m259_npcObjTbl[0]->model[0], Hu3DData[m259_npcObjTbl[0]->motion[0]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(m259_npcObjTbl[1]->model[0], Hu3DData[m259_npcObjTbl[1]->motion[0]].motId, 0,
                       10, 0);
    Hu3DMotionAttrSet(m259_npcObjTbl[0]->model[0], 2, 2);
    Hu3DMotionAttrSet(m259_npcObjTbl[1]->model[0], 2, 2);
}

void m259_NpcWinMotSet(void) {
    Hu3DMotionShiftSet(m259_npcObjTbl[0]->model[0], Hu3DData[m259_npcObjTbl[0]->motion[2]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(m259_npcObjTbl[1]->model[0], Hu3DData[m259_npcObjTbl[1]->motion[2]].motId, 0,
                       10, 0);
    Hu3DMotionAttrSet(m259_npcObjTbl[0]->model[0], 2, 2);
    Hu3DMotionAttrSet(m259_npcObjTbl[1]->model[0], 2, 2);
}

void m259_NpcLoseMotSet(void) {
    Hu3DMotionShiftSet(m259_npcObjTbl[0]->model[0], Hu3DData[m259_npcObjTbl[0]->motion[3]].motId, 0,
                       10, 0);
    Hu3DMotionShiftSet(m259_npcObjTbl[1]->model[0], Hu3DData[m259_npcObjTbl[1]->motion[3]].motId, 0,
                       10, 0);
}

void m259_PointerObjCreate(void) {
    s32 attr;
    WinnersWheelPointer *pointer;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 18, 0, -1, m259_PointerObjMain);
    pointer = obj->data = HuMemAllocTag(sizeof(WinnersWheelPointer), 0x7918);
    m259_pointerObj = obj;
    attr = 0x6BD;
    pointer->speed = 0.0f;
    pointer->flags = 0x20;
    pointer->count = 0;
    pointer->mode = 0;
    for (i = 0; i < 18; i++) {
        pointer->rawRot[i] = pointer->rot[i] = i * 20.0f;
        if (i == 0) {
            obj->model[i] = Hu3DModelRead(0x5C0005, attr);
            omSetTra(obj, sindf(pointer->rot[i]) * -10.5f, cosdf(pointer->rot[i]) * -10.5f, 0.0f);
            omSetRot(obj, 0.0f, 0.0f, -pointer->rot[i]);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelPosSet(obj->model[i], sindf(pointer->rot[i]) * -10.5f, cosdf(pointer->rot[i]) * -10.5f, 0.0f);
            Hu3DModelRotSet(obj->model[i], 0.0f, 0.0f, -pointer->rot[i]);
        }
    }
}

void m259_PointerObjMain(omObjData *obj) {
    WinnersWheelPointer *pointer = obj->data;
    WinnersWheelWheel *wheel = m259_wheelObj->data;
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
        m259_panelNo = (s32)((360.0f - wheel->angle + rot) / 60.0f) % 6;
    }
    if (pointer->flags & 8) {
        rot = pointer->rot[0] + 10.0f;
        m259_panelNo = (s32)((360.0f - wheel->angle + rot) / 60.0f) % 6;
        m259_oppPanelNo = 5 - m259_panelNo;
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
            m259_slowSePitch -= 9;
            if (m259_slowSePitch < -900) {
                m259_slowSePitch = -900;
            }
            HuAudFXPitchSet(m259_slowSeNo, m259_slowSePitch);
        }
        if (pointer->mode != 2) {
            if (pointer->rot[0] == pointer->target && pointer->rot[1] != pointer->rot[0]) {
                pointer->count--;
            }
            if (pointer->count == 0) {
                pointer->speed = 0.0f;
                pointer->flags &= ~4;
                pointer->flags &= ~1;
                HuAudFXStop(m259_slowSeNo);
                HuAudFXPlay(0x4CD);
                if (m259_panelItemTbl[m259_panelNo] == 17) {
                    omVibrate(m259_playerNo, 10, 0, 10);
                } else {
                    omVibrate(m259_playerNo, 2, 3, 10);
                }
                MgFlowStatSet(MG_STATE_FINISH);
            }
        } else if (pointer->speed <= minSpeed && m259_panelItemTbl[m259_panelNo] == 17) {
            pointer->speed = 0.0f;
            pointer->flags &= ~4;
            pointer->flags &= ~1;
            omVibrate(m259_playerNo, 10, 0, 10);
            MgFlowStatSet(MG_STATE_FINISH);
            HuAudFXStop(m259_slowSeNo);
            HuAudFXPlay(0x4CD);
        }
        pointer->rot[1] = pointer->rot[0];
    }
}

void m259_IntroStart(void) {
    omAddPrcObj(m259_IntroProc, 0x50, 0, 0);
}

void m259_IntroProc(void) {
    WinnersWheelPointer *pointer = m259_pointerObj->data;
    WinnersWheelSign *sign = m259_signObj->data;
    s32 i;
    s32 j;

    pointer->flags |= 8;
    pointer->flags &= ~0x20;
    Hu3DModelAttrSet(m259_pointerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(m259_pointerObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(m259_pointerObj, sindf(pointer->rot[0]) * -10.5f, cosdf(pointer->rot[0]) * -10.5f, 0.0f);
        } else {
            Hu3DModelPosSet(m259_pointerObj->model[i], sindf(pointer->rot[i]) * -10.5f,
                            cosdf(pointer->rot[i]) * -10.5f, 0.0f);
        }
    }
    for (i = 0; i < 18; i++) {
        if (i == 9) {
            continue;
        }
        pointer->rot[0] = i * 20.0f;
        pointer->rot[1] = 340.0f - pointer->rot[0];
        omSetTra(m259_pointerObj, sindf(pointer->rot[0]) * -10.5f, cosdf(pointer->rot[0]) * -10.5f, -1.0f);
        Hu3DModelPosSet(m259_pointerObj->model[1], sindf(pointer->rot[1]) * -10.5f,
                        cosdf(pointer->rot[1]) * -10.5f, -1.0f);
        HuAudFXPlay(0x4C8);
        HuPrcSleep(4);
    }
    pointer->flags &= ~8;
    m259_oppPanelNo = -1;
    Hu3DModelAttrSet(m259_pointerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m259_pointerObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    pointer->flags |= 0x20;
    m259_CameraZoomStart();
    while (CZoom < 2887.1f) {
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        Hu3DMotionShiftSet(m259_npcObjTbl[i]->model[0],
                           Hu3DData[m259_npcObjTbl[i]->motion[4]].motId, 0, 10, 0);
        Hu3DMotionAttrSet(m259_npcObjTbl[i]->model[0], 2, 2);
    }
    m259_SignRiseStart();
    for (i = 0; i < 18; i++) {
        pointer->rot[i] = i * 20.0f;
        if (i == 0) {
            omSetTra(m259_pointerObj, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
        } else {
            Hu3DModelPosSet(m259_pointerObj->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]), 0.0f);
        }
        Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 18; i++) {
            Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        pointer->flags |= 0x10;
        pointer->flags &= ~0x20;
        HuPrcSleep(10);
        for (i = 0; i < 18; i++) {
            Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        pointer->flags &= ~0x10;
        pointer->flags |= 0x20;
        HuPrcSleep(10);
    }
    while (sign->flags & 8) {
        HuPrcVSleep();
    }
    m259_PlayerHitStart(0);
    m259_NpcIdleMotSet();
    pointer->flags &= ~0x20;
    omDelPrcObj(NULL);
}

void m259_PointerFlashStart(void) {
    omAddPrcObj(m259_PointerFlashProc, 0x50, 0, 0);
}

void m259_PointerFlashProc(void) {
    WinnersWheelPointer *pointer = m259_pointerObj->data;
    s32 i;
    s32 j;

    for (i = 0; i < 18; i++) {
        if (i == 0) {
            omSetTra(m259_pointerObj, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
        } else {
            Hu3DModelPosSet(m259_pointerObj->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]), 0.0f);
        }
    }
    while (TRUE) {
        Hu3DModelAttrSet(m259_pointerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(m259_pointerObj->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        for (i = 0; i < 36; i++) {
            pointer->rot[0] = i * 20.0f;
            pointer->rot[1] = 340.0f - i * 20.0f;
            pointer->rot[2] = i * 20.0f + 180.0f;
            pointer->rot[3] = 160.0f - i * 20.0f;
            pointer->rot[4] = i * 20.0f + 100.0f;
            pointer->rot[5] = 80.0f - i * 20.0f;
            pointer->rot[6] = i * 20.0f + 280.0f;
            pointer->rot[7] = 260.0f - i * 20.0f;
            omSetTra(m259_pointerObj, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), -1.0f);
            for (j = 1; j < 8; j++) {
                Hu3DModelPosSet(m259_pointerObj->model[j], sindf(pointer->rot[j]), cosdf(pointer->rot[j]),
                                -1.0f);
            }
            HuPrcSleep(1);
        }
        for (i = 0; i < 18; i++) {
            pointer->rot[i] = i * 20.0f;
            if (i == 0) {
                omSetTra(m259_pointerObj, sindf(pointer->rot[0]), cosdf(pointer->rot[0]), 0.0f);
            } else {
                Hu3DModelPosSet(m259_pointerObj->model[i], sindf(pointer->rot[i]), cosdf(pointer->rot[i]),
                                0.0f);
            }
            Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 18; i++) {
                Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            HuPrcSleep(1);
            for (i = 0; i < 18; i++) {
                Hu3DModelAttrSet(m259_pointerObj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            HuPrcSleep(1);
        }
    }
}

void m259_PointerSpinStart(void) {
    WinnersWheelPointer *pointer = m259_pointerObj->data;

    pointer->flags |= 3;
    pointer->rot[0] = 340.0f;
    pointer->rawRot[0] = 340.0f;
    Hu3DModelAttrSet(m259_pointerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    omSetRot(m259_pointerObj, 0.0f, 0.0f, pointer->rot[0]);
    m259_spinSeNo = HuAudFXPlay(0x4C7);
}

void m259_PointerStopStart(s32 mode) {
    WinnersWheelPointer *pointer = m259_pointerObj->data;
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
    HuAudFXStop(m259_spinSeNo);
    m259_slowSeNo = HuAudFXPlay(0x4CB);
}

void m259_PointerBlinkStart(void) {
    omAddPrcObj(m259_PointerBlinkProc, 0x50, 0, 0);
}

void m259_PointerBlinkProc(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(*m259_pointerObj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuPrcSleep(10);
        Hu3DModelAttrSet(*m259_pointerObj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        HuPrcSleep(10);
    }
    m259_seqNo = 4;
    omDelPrcObj(NULL);
}

void m259_CameraZoomStart(void) {
    omAddPrcObj(m259_CameraZoomProc, 0x50, 0, 0);
}

void m259_CameraZoomProc(void) {
    WinnersWheelWheel *wheel = m259_wheelObj->data;
    WinnersWheelPanels *panels = m259_panelObj->data;
    WinnersWheelPlayer *player = m259_playerObj->data;
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

void m259_TimerProc(void) {
    s32 seconds = 10;
    s32 frames = 30;

    GMesPosSet(GMesCreate(GMES_MES_TIMER, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        GMesTimerValueSet(seconds);
        HuPrcVSleep();
        if (m259_seqNo == 3) {
            break;
        }
    } while (seconds > 0);
    GMesTimerEnd();
    if (m259_seqNo != 3) {
        m259_seqNo = 2;
    }
    omDelPrcObj(NULL);
}

void m259_FrameObjCreate(void) {
    s32 attr = 0x63D;
    WinnersWheelPanelFrames *frames;
    WinnersWheelWheel *wheel;
    omObjData *obj;
    s32 i;

    obj = omAddObj(0xFF, 6, 0, -1, m259_FrameObjMain);
    m259_frameObj = obj;
    frames = obj->data = HuMemAllocTag(sizeof(WinnersWheelPanelFrames), 0x7918);
    wheel = m259_wheelObj->data;
    frames->flags = 0;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0x5C0003, attr);
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

void m259_FrameObjMain(omObjData *obj) {
    WinnersWheelPanelFrames *frames = obj->data;
    WinnersWheelWheel *wheel = m259_wheelObj->data;
    WinnersWheelPointer *pointer = m259_pointerObj->data;
    s32 i;

    for (i = 0; i < 6; i++) {
        HuRotateRPYF(Hu3DData[obj->model[i]].mtx, 0.0f, 0.0f, -frames->angle[i]);
        if (i == 0) {
            omSetRot(obj, frames->rot[0], 0.0f, 0.0f);
            omSetSca(obj, wheel->scale, wheel->scale, 1.0f);
        } else {
            Hu3DModelRotSet(obj->model[i], frames->rot[i], 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], wheel->scale, wheel->scale, 1.0f);
        }
        if (frames->rot[i] >= 90.0f) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < 6; i++) {
        Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    if (pointer->flags & 0x20) {
        m259_panelNo = m259_oppPanelNo = -1;
    }
    for (i = 0; i < 6; i++) {
        frames->angle[i] = i * 60.0f + wheel->angle;
        if (i == m259_panelNo || i == m259_oppPanelNo || (pointer->flags & 0x10)) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void m259_PrizeObjCreate(void) {
    s32 itemFiles[16] = { 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C };
    WinnersWheelPrize *prize;
    omObjData *obj;
    void *data;
    s16 sprite;

    obj = omAddObj(0xFE, 1, 0, -1, m259_PrizeObjMain);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelPrize), 0x7918);
    m259_prizeObj = obj;
    prize = obj->data;
    if (m259_panelNo == 17) {
        data = DataRead(0x5C0007);
    } else {
        data = DataRead(itemFiles[m259_panelItemTbl[m259_panelNo]] | 0x210000);
    }
    sprite = Hu3DSprModelCreate(data, 0x69D, 8);
    DataClose(data);
    obj->model[0] = Hu3DSprModelData[sprite].modelId;
    prize->pos.x = 0.0f;
    prize->pos.y = 0.0f;
    prize->pos.z = 2.0f;
    prize->unk_10 = 0.0f;
    prize->angle = 180.0f;
    prize->flags = 0;
    omSetTra(obj, prize->pos.x, prize->pos.y, prize->pos.z);
    omSetSca(obj, 2.2f, 2.2f, 1.0f);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void m259_PrizeObjMain(omObjData *obj) {
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
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    if (prize->angle == 270.0f) {
        omVibrate(m259_playerNo, 2, 2, 20);
        HuAudFXPlay(0x10);
    }
    if (prize->flags & 2) {
        EffectPosSet(m259_prizeEffNo, prize->pos.x, prize->pos.y, prize->pos.z - 2.0f);
    }
}

void m259_PrizeFloatStart(void) {
    WinnersWheelPrize *prize = m259_prizeObj->data;

    prize->flags |= 1;
}

void m259_PrizeEffStart(void) {
    m259_prizeEffNo = EffectCreate(0xB0004, 0x6A9);
    ((WinnersWheelPrize *)m259_prizeObj->data)->flags |= 2;
}

void m259_PrizeShowStart(void) {
    omAddPrcObj(m259_PrizeShowProc, 0x50, 0, 0);
}

void m259_PrizeShowProc(void) {
    WinnersWheelPrize *prize = m259_prizeObj->data;
    s32 i;

    Hu3DModelAttrSet(m259_prizeObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    HuPrcSleep(30);
    HuAudFXPlay(0x19);
    for (i = 0; i < 31; i++) {
        prize->pos.x = m259_playerObj->trans.x * i / 30.0f;
        prize->pos.y = i * 90.0f / 30.0f + sindf(i * 6.0f) * 100.0f;
        prize->pos.z = i * m259_playerObj->trans.z / 30.0f;
        HuPrcVSleep();
    }
    m259_PrizeFloatStart();
    HuAudFXPlay(0x4CE);
    omDelPrcObj(NULL);
}

void m259_KoopaObjCreate(void) {
    WinnersWheelBowser *bowser;
    omObjData *obj;

    obj = omAddObj(0xFF, 2, 2, -1, m259_KoopaObjMain);
    obj->data = HuMemAllocTag(sizeof(WinnersWheelBowser), 0x7918);
    m259_koopaObj = obj;
    bowser = obj->data;
    obj->model[0] = Hu3DModelRead(0xA00EE, 0x69D);
    obj->model[1] = Hu3DModelRead(9, 0x4AD);
    bowser->pos.x = 0.0f;
    bowser->pos.y = -182.0f;
    bowser->pos.z = -190.0f;
    bowser->flags = 0;
    bowser->unk_14 = 0.0f;
    omSetTra(obj, bowser->pos.x, bowser->pos.y, bowser->pos.z);
    omSetSca(obj, 0.8f, 0.8f, 0.8f);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F0);
    omObjMotionRead(obj, 2, 0xA00F6);
    Hu3DMotionModelSet(obj->model[0], obj->motion[4]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
}

void m259_KoopaObjMain(omObjData *obj) {
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

void m259_KoopaJumpStart(void) {
    omAddPrcObj(m259_KoopaJumpProc, 0x50, 0, 0);
}

void m259_KoopaJumpProc(void) {
    WinnersWheelBowser *bowser = m259_koopaObj->data;
    s32 i;

    Hu3DMotionModelSet(m259_koopaObj->model[0], m259_koopaObj->motion[1]);
    bowser->unk_14 = 50.0f;
    for (i = 0; i < 31; i++) {
        if (i == 5) {
            Hu3DModelAttrSet(m259_koopaObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(m259_koopaObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            HuAudFXPlay(0x4CC);
            omVibrate(m259_playerNo, 20, 0, 20);
        }
        bowser->pos.x = 0.0f;
        bowser->pos.y = sindf(i * 6.0f) * 282.0f + -182.0f;
        bowser->pos.z = i * 380.0f / 30.0f - 190.0f;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4CF);
    MgFlowStatNext();
    Hu3DMotionShiftSet(m259_koopaObj->model[0], Hu3DData[m259_koopaObj->motion[2]].motId, 0,
                       10, 0);
    Hu3DMotionAttrSet(m259_koopaObj->model[0], 2, 2);
    omDelPrcObj(NULL);
}

void m259_CameraInit(void) {
    CamSetupInit(1);
    m259_cameraNo = CamSetupMapCullAdd();
    Hu3DCameraPerspectiveSet(m259_cameraNo, 11.1f, 80.0f, 8000.0f);
    CZoom = 2887.1f;
    CRot.x = -4.4f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = -0.9f;
    Center.y = -21.9f;
    Center.z = -253.6f;
}
