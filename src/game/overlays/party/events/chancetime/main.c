#include "common.h"
#include "chancetime.h"
#include "game/window.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/main.h"

extern s32 chancetime_flowTimer;
extern s8 chancetime_blockOrderTbl[3];

s32 chancetime_IntroEndCheck(void);
void chancetime_PanelDropStart(void);
s32 chancetime_PanelLandCheck(void);
s32 chancetime_PlayerEnterCheck(void);
void chancetime_PlayerHitStart(s8 arg0);
s32 chancetime_PlayerHitCheck(void);
void chancetime_BlockSpinStart(s32 arg0);
s32 chancetime_BlockSpinCheck(void);
void chancetime_TransferStart(void);
s32 chancetime_TransferCheck(void);
void chancetime_IntroMesStart(void);
s32 chancetime_IntroMesCheck(void);
void chancetime_Close(void);
void chancetime_FlowObjMain(omObjData *object);
void chancetime_CameraInit(void);
void chancetime_ExitCheckObjMain(omObjData *object);
void chancetime_BgSprCreate(void);

s8 chancetime_flowState = 0;
s32 chancetime_statusVsF = 0;
s8 chancetime_exitF = 0;

void chancetime_ObjectSetup(void) {
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
                chancetime_playerOrderTbl[count] = j;
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

    chancetime_turnTier = MBTurnTierGet(CUR_TURN);
    roll = (u8)(rand8() % 10) + 1;
    if (roll < 8) {
        chancetime_blockOrderTbl[0] = 2;
        chancetime_blockOrderTbl[1] = 0;
        chancetime_blockOrderTbl[2] = 1;
    } else if (roll < 10) {
        chancetime_blockOrderTbl[0] = 0;
        chancetime_blockOrderTbl[1] = 1;
        chancetime_blockOrderTbl[2] = 2;
    } else {
        chancetime_blockOrderTbl[0] = 1;
        chancetime_blockOrderTbl[1] = 0;
        chancetime_blockOrderTbl[2] = 2;
    }
    for (i = 0; i < 5; i++) {
        if (rand8() & 1) {
            temp = chancetime_blockOrderTbl[1];
            chancetime_blockOrderTbl[1] = chancetime_blockOrderTbl[2];
            chancetime_blockOrderTbl[2] = temp;
        }
    }

    omInitObjMan(30, 20);
    HuWinInit();
    Hu3DSprModelInit(80);
    CamSetupInitMulti(3);
    ScissorSet(0, 104.0f, 52.0f, 215.0f, 163.0f);
    ScissorSet(1, 0.0f, 0.0f, 320.0f, 240.0f);
    ScissorSet(2, 0.0f, 0.0f, 320.0f, 240.0f);
    for (i = 0; i < 3; i++) {
        ViewportSet(i, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 3;
    omAddPrcObj(chancetime_PlayerProc, 0x1001, 0x2000, 0);
    omAddPrcObj(chancetime_HostProc, 0x1001, 0x2000, 0);
    omAddPrcObj(chancetime_DancerProc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_Dancer1Proc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_Dancer2Proc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_Dancer3Proc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_Dancer4Proc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_HostLJumpProc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_HostRJumpProc, 0x1001, 0x1000, 0);
    omAddPrcObj(chancetime_BlockProc, 0x1001, 0x2000, 0);
    omAddPrcObj(chancetime_EventProc, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, chancetime_FlowObjMain);
    omAddObj(0, 0, 0, -1, chancetime_ExitCheckObjMain);
    chancetime_CameraInit();
    chancetime_BgSprCreate();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void chancetime_FlowObjMain(omObjData *object) {
    f32 fov;
    s32 state;
    s8 i;

    fov = 30.0f;
    state = chancetime_flowState;
    switch (state) {
        case 0:
            chancetime_flowTimer = 0;
            state++;
            break;
        case 1:
            if (chancetime_flowTimer++ >= 7) {
                HuAudSeqPlay(0x42);
                HuAudFXPlay(0x4FF);
                chancetime_flowTimer = 0;
                state++;
            }
            break;
        case 2:
            state += chancetime_IntroEndCheck() != 0;
            break;
        case 3:
            if (++chancetime_flowTimer >= 0) {
                chancetime_PanelDropStart();
                state++;
                HuAudFXPlay(0x500);
            }
            break;
        case 4:
            if (chancetime_PanelLandCheck() == 1) {
                chancetime_flowTimer = 0;
                state++;
            }
            break;
        case 5:
            chancetime_PlayerEnterStart();
            chancetime_flowTimer = 0;
            state++;
            break;
        case 6:
            if (chancetime_PlayerEnterCheck() == 1) {
                chancetime_IntroMesStart();
                state++;
            }
            break;
        case 7:
            state += chancetime_IntroMesCheck() != 0;
            break;
        case 8:
            chancetime_BlockSpinStart(chancetime_blockOrderTbl[0]);
            state++;
            break;
        case 9:
            if (chancetime_BlockSpinCheck() == 1) {
                chancetime_flowTimer = 0;
                state++;
            }
            break;
        case 10:
            if (++chancetime_flowTimer > 0) {
                chancetime_PlayerHitStart(chancetime_blockOrderTbl[0]);
                state++;
            }
            break;
        case 11:
            state += chancetime_PlayerHitCheck() == 1;
            break;
        case 12:
            chancetime_BlockSpinStart(chancetime_blockOrderTbl[1]);
            state++;
            break;
        case 13:
            if (chancetime_BlockSpinCheck() == 1) {
                chancetime_flowTimer = 0;
                state++;
            }
            break;
        case 14:
            if (++chancetime_flowTimer > 0) {
                chancetime_PlayerHitStart(chancetime_blockOrderTbl[1]);
                state++;
            }
            break;
        case 15:
            state += chancetime_PlayerHitCheck() == 1;
            break;
        case 16:
            chancetime_BlockSpinStart(chancetime_blockOrderTbl[2]);
            state++;
            break;
        case 17:
            if (chancetime_BlockSpinCheck() == 1) {
                chancetime_flowTimer = 0;
                state++;
            }
            break;
        case 18:
            if (++chancetime_flowTimer > 0) {
                chancetime_PlayerHitStart(chancetime_blockOrderTbl[2]);
                state++;
            }
            break;
        case 19:
            state += chancetime_PlayerHitCheck() == 1;
            break;
        case 20:
            chancetime_TransferStart();
            state++;
            break;
        case 21:
            state += chancetime_TransferCheck() != 0;
            break;
        case 22:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            state++;
            break;
        case 23:
            if (WipeStatGet() == 0) {
                GMesClose();
                chancetime_Close();
                omOvlReturnEx(1);
            }
            break;
    }
    chancetime_flowState = state;

    for (i = 0; i < 4; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCameraPerspectiveSet(i, fov, 80.0f, 8000.0f);
    }
}

void chancetime_CameraInit(void) {
    CRot.x = 0.1f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;

    Center.x = 0.0f;
    Center.y = 230.0f;
    Center.z = 920.0f;

    CZoom = 100.0f;
}

void chancetime_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq != 1) {
        return;
    }

    if (chancetime_exitF == 0) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        chancetime_exitF = 1;
    } else if (WipeStatGet() == 0) {
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        GMesClose();
        chancetime_Close();
        omOvlReturnEx(1);
    }
}

void chancetime_BgSprCreate(void) {
    u16 sprite;

    sprite = espEntry(HuSprAnimDataRead(0x1C0001), 0, 0);
    espPosSet(sprite, 160, 180);
    espAttrSet(sprite, HUSPR_ATTR_BG);

    sprite = espEntry(HuSprAnimDataRead(0x1C0005), 0, 0);
    espPosSet(sprite, 160, 60);
    espAttrSet(sprite, HUSPR_ATTR_BG);
}

void chancetime_Close(void) {
    HuWinAllKill();
    if (chancetime_statusVsF == 1) {
        MBStatusVsKill();
    }
}
