#include "common.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"

typedef struct {
    f32 posX[6];
    f32 posY[6];
    f32 posZ[6];
    s32 flags[6];
} DorrieDipEffects;

typedef struct {
    f32 posX[6];
    f32 posY[6];
    f32 posZ[6];
    f32 scaleX[6];
    s32 flags[6];
} DorrieDipWakes;

typedef struct {
    s32 grabDelay;
    s32 targetDip;
    s32 triggered;
} DorrieDipCpu;

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[3];
    f32 unk08;
    u8 unk0C[0xA8];
} DorrieDipBackground;

typedef struct {
    s32 flags;
    Vec hookPos;
    s32 grabTimer;
} DorrieDipDorrie;

typedef struct {
    Vec pos;
    f32 unk0C;
    f32 unk10;
    s32 unk14;
    f32 unk18;
    f32 unk1C;
} DorrieDipData;

typedef struct {
    s32 unk00[6];
    f32 unk18[6];
    f32 unk30[6];
} DorrieDipDips;

// One entry per player.
typedef struct {
    f32 posX[5];
    f32 posY[5];
    f32 posZ[5];
    f32 velY[5];
    f32 unk50[5];
    f32 unk64[5];
    f32 unk78[5];
    f32 unk8C[5];
    s32 flags[5];
    s32 playerIdx[5];
} DorrieDipSplashes; // sizeof 0xC8

extern u16 mgInstColumnTbl[];
extern u16 mgInstSlotTbl[];
extern s32 omCharModelNoTbl[][6];

MinigameFlow m262_mgFlow = {
    MG_STATE_OPENING, MINIGAME_ITEM, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_GOT_ITEM, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    210, 300, -1, 90, 135
};
s32 m262_ambSeTime = 1;
s32 m262_ambSe2Time = 30;

f32 m262_unusedScale BSS;
s32 m262_cameraNo BSS;
u8 m262_seqNo BSS;
s16 m262_itemEffNo BSS;
s32 m262_playerNo BSS;
s32 m262_koopaRaftNo BSS;
u8 m262_koopaRaftNoPad[4] BSS; /* Unreferenced. */
s32 m262_raftItemTbl[6] BSS;
s32 m262_grabRaftNo BSS;
omObjData *m262_stageObjTbl[2] BSS;
f32 m262_waterY BSS;
omObjData *m262_raftObj BSS;
omObjData *m262_koopaObj BSS;
omObjData *m262_dorrieObj BSS;
omObjData *m262_itemObj BSS;
s32 m262_playerFlag BSS;
f32 m262_waterAngle BSS;
omObjData *m262_burstObj BSS;
omObjData *m262_rippleObj BSS;
s32 m262_rippleFlag BSS;
DorrieDipCpu m262_comWork BSS;
omObjData *m262_wakeObj BSS;

/* Low halfword of m262_playerNo. */
extern s16 m262_playerNoS16;

void m262_ExitObjMain(omObjData *);
void m262_RaftObjMain(omObjData *);
void m262_DorrieObjMain(omObjData *);
void m262_PlayerInit(omObjData *, s32);
void m262_PlayerObjMain(omObjData *);
void m262_ItemObjMain(omObjData *);
void m262_StageObjMain(omObjData *);
void m262_BurstObjMain(omObjData *);
void m262_RippleObjMain(omObjData *);
void m262_KoopaObjMain(omObjData *);
void m262_ComInput(void);
void m262_DorrieDipStart(void);
void m262_RippleStop(void);
void m262_RaftSpinStart(void);
void m262_WakeStart(s32);
void m262_HookPosGet(s16, char *, s16, Vec *);
void m262_CameraZoomOutStart(void);
void m262_DropStart(void);
void m262_DorrieRoarStart(void);
void m262_TimerStart(void);
void m262_PadWaitStart(void);
void m262_TimeUpStart(void);
void m262_KoopaLeaveStart(void);
void m262_RaftBurst(s32);
void m262_ItemGetStart(void);
void m262_ResultStart(void);
void m262_CameraInit(f32, f32, f32, f32, f32, f32, f32);
void m262_MainObjMain(omObjData *);
void m262_RaftObjCreate(void);
void m262_DorrieObjCreate(void);
void m262_PlayerObjInit(omObjData *);
void m262_ItemObjCreate(void);
void m262_KoopaObjCreate(void);
void m262_StageObjCreate(void);
void m262_BurstObjCreate(void);
void m262_RippleObjCreate(void);
void m262_RippleStart(void);
void m262_ComInit(void);
void m262_WakeObjCreate(void);
void m262_WakeObjMain(omObjData *);

void m262_DorrieDipProc(void);

void m262_CameraZoomOutProc(void);

void m262_DropProc(void);

void m262_KoopaLeaveProc(void);

void m262_TimeUpProc(void);

void m262_PadWaitProc(void);

void m262_TimerProc(void);

void m262_ResultProc(void);

void m262_ItemGetProc(void);

void m262_RippleProc(void);

void m262_ObjectSetup(void) {
    omObjData *obj;

    omInitObjMan(30, 10);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(0x40);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m262_CameraInit(500.0f, 345.0f, 0.0f, 0.0f, 0.0f, 190.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&m262_mgFlow);
    mgMapObjNum = 0;
    mgPlayerObjNum = 0;
    MgPlayerParamReset();
    mgPlayerFallMax = 1.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m262_StageObjCreate();
    omAddObj(0x50, 0, 0, -1, m262_MainObjMain);
    m262_RaftObjCreate();
    m262_DorrieObjCreate();
    omAddObj(4, 10, 60, -1, m262_PlayerObjInit);
    m262_ItemObjCreate();
    m262_KoopaObjCreate();
    m262_BurstObjCreate();
    m262_RippleObjCreate();
    m262_RippleStart();
    m262_ComInit();
    m262_WakeObjCreate();
    m262_seqNo = 0;
}

void m262_CameraInit(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    m262_cameraNo = CamSetupMapCullAdd();
    ScissorSet(m262_cameraNo, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(m262_cameraNo, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCameraPerspectiveSet(m262_cameraNo, 41.5f, 80.0f, 8000.0f);
}

void m262_MainObjMain(omObjData *obj) {
    s32 i;

    if (omSysExitReq != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (MgFlowMain(obj)) {
        case 0:
            if (MgFlowStatTimeGet() == 30) {
                m262_CameraZoomOutStart();
            }
            if (MgFlowStatTimeGet() == 60) {
                m262_DropStart();
            }
            if (MgFlowStatTimeGet() == 120) {
                m262_DorrieRoarStart();
            }
            if (m262_ambSeTime == MgFlowStatTimeGet()) {
                if (m262_ambSeTime == 1) {
                    HuAudSeqPlay(0x44);
                }
                HuAudFXPlay(0x4E7);
                m262_ambSeTime += 30 + rand8() / 8;
            }
            if (m262_ambSe2Time == MgFlowStatTimeGet()) {
                HuAudFXPlay(0x4E8);
                m262_ambSe2Time += 30 + rand8() / 8;
            }
            break;
        case 2:
            if (MgFlowStatTimeGet() == 0) {
                m262_TimerStart();
                m262_PadWaitStart();
            }
            break;
        case 3:
            if (MgFlowStatTimeGet() == 1) {
                if (m262_seqNo == 2) {
                    m262_TimeUpStart();
                } else {
                    m262_KoopaLeaveStart();
                    for (i = 0; i < 6; i++) {
                        if (i != m262_grabRaftNo) {
                            m262_RaftBurst(i);
                        }
                    }
                }
                if (m262_grabRaftNo == -1 || m262_raftItemTbl[m262_grabRaftNo] == 17) {
                    m262_mgFlow.resultType = MG_RESULT_GAME_OVER;
                } else {
                    m262_mgFlow.resultType = MG_RESULT_GOT_ITEM;
                }
            }
            if (MgFlowStatTimeGet() == 15 && m262_grabRaftNo != -1 &&
                m262_raftItemTbl[m262_grabRaftNo] != 17) {
                m262_RaftBurst(m262_grabRaftNo);
                m262_ItemGetStart();
            }
            break;
        case 4:
            if (MgFlowStatTimeGet() == 1) {
                m262_ResultStart();
            }
            break;
        case 5:
            if (m262_grabRaftNo != -1 && m262_raftItemTbl[m262_grabRaftNo] != 17) {
                GwPlayer[m262_playerNo].bonusCoin = m262_raftItemTbl[m262_grabRaftNo];
            } else {
                GwPlayer[m262_playerNo].bonusCoin = -1;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            obj->func = m262_ExitObjMain;
            break;
    }
}

void m262_ExitObjMain(omObjData *obj) {
    HuAudFXAllFadeOut(30);
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        GMesClose();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m262_RaftObjCreate(void) {
    s32 i;
    omObjData *obj;
    DorrieDipDips *dips;
    s32 modelFlags = 0x699;
    s32 splashFlags = 0x69D;

    obj = omAddObj(250, 12, 0, -1, m262_RaftObjMain);
    m262_raftObj = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipDips), TAG_OVERLAY);
    dips = obj->data;
    for (i = 0; i < 6; i++) {
        dips->unk00[i] = 0;
        dips->unk18[i] = i * 60.0f;
        dips->unk30[i] = 0;
        if (i == 0) {
            obj->model[i] = Hu3DModelRead(0x5F0002, modelFlags);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i + 6] = Hu3DModelRead(0x5F000B, splashFlags);
            Hu3DModelRotSet(obj->model[i + 6], 0.0f, 0.0f, 0.0f);
        } else {
            obj->model[i + 6] = Hu3DModelLink(obj->model[6]);
            Hu3DModelRotSet(obj->model[i + 6], 0.0f, 0.0f, 0.0f);
        }
        Hu3DMotionAttrSet(obj->model[i + 6], 2, 2);
    }
}

void m262_RaftObjMain(omObjData *obj) {
    s32 i;
    DorrieDipDips *dips = obj->data;
    f32 x, y, z;

    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        y = m262_waterY;
        z = cosdf(dips->unk18[i]) * 450.0f;
        if (i == 0) {
            omSetTra(obj, x, y, z);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], x, y, z);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        z = cosdf(dips->unk18[i]) * 450.0f;
        Hu3DModelPosSet(obj->model[i + 6], x, 0.0f, z);
        Hu3DModelRotSet(obj->model[i + 6], 0.0f, dips->unk18[i], 0.0f);
    }
    for (i = 0; i < 6; i++) {
        if (dips->unk00[i] & 1) {
            dips->unk18[i] -= dips->unk30[i];
            if (dips->unk18[i] <= 0.0f) {
                dips->unk18[i] += 360.0f;
            }
            dips->unk30[i] += 0.2f;
            if (dips->unk30[i] > 4.8f) {
                dips->unk30[i] = 4.8f;
            }
            if (dips->unk30[i] >= 4.0f && dips->unk30[i] < 4.2f) {
                Hu3DModelAttrSet(m262_raftObj->model[i + 6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DMotionAttrSet(m262_raftObj->model[i + 6], 2, 2);
            }
        }
    }
}

void m262_RaftSpinStart(void) {
    s32 i;
    DorrieDipDips *dips = (DorrieDipDips *)m262_raftObj->data;

    for (i = 0; i < 6; i++) {
        dips->unk00[i] |= 1;
    }
}

void m262_DorrieObjCreate(void) {
    omObjData *obj;
    DorrieDipDorrie *data;

    obj = omAddObj(255, 1, 5, -1, m262_DorrieObjMain);
    obj->data = HuMemAllocTag(sizeof(DorrieDipDorrie), TAG_OVERLAY);
    m262_dorrieObj = obj;
    data = obj->data;
    obj->model[0] = Hu3DModelRead(0x5F0005, 0x699);
    omObjMotionRead(obj, 0, 0x5F0006);
    omObjMotionRead(obj, 1, 0x5F0007);
    omObjMotionRead(obj, 2, 0x5F0008);
    omObjMotionRead(obj, 3, 0x5F0009);
    omObjMotionRead(obj, 4, 0x5F000A);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    data->flags = 0;
    data->grabTimer = 0;
    m262_grabRaftNo = -1;
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
}

void m262_DorrieObjMain(omObjData *obj) {
    Vec hookPos;
    s32 i;
    s32 splashIdx;
    f32 time;
    DorrieDipDorrie *data = obj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    DorrieDipSplashes *splashes = m262_itemObj->data;
    DorrieDipData *item = m262_koopaObj->data;

    if ((data->flags & 2) && Hu3DData[obj->model[0]].motTime == 50.0f &&
        data->hookPos.y < 20.0f && m262_grabRaftNo == -1 && data->grabTimer < 15) {
        if (data->grabTimer == 0) {
            Hu3DMotionAttrSet(obj->model[0], 8, 8);
        }
        for (i = 0; i < 6; i++) {
            if (dips->unk18[i] >= 265.0f && dips->unk18[i] < 275.0f) {
                m262_grabRaftNo = i;
                omVibrate(m262_playerNoS16, 10, 0, 10);
                break;
            }
        }
        if (m262_grabRaftNo != -1) {
            Hu3DModelHookSet(m262_raftObj->model[m262_grabRaftNo], obj->model[0], "item_hook");
            Hu3DModelAttrSet(m262_raftObj->model[m262_grabRaftNo], 0x4000, 0x4000);
            Hu3DModelAttrSet(m262_raftObj->model[m262_grabRaftNo + 6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            dips->unk00[m262_grabRaftNo] &= ~1;
            Hu3DMotionAttrSet(obj->model[0], 8, 0);
            if (m262_grabRaftNo == m262_koopaRaftNo) {
                item->unk14 |= 4;
            } else {
                splashIdx = -1;
                for (i = 0; i < 5; i++) {
                    if (splashes->playerIdx[i] == m262_grabRaftNo) {
                        splashIdx = i;
                    }
                }
                splashes->flags[splashIdx] |= 4;
                HuAudFXPlay(0x4E6);
            }
        }
        data->grabTimer++;
        if (data->grabTimer == 15) {
            Hu3DMotionAttrSet(obj->model[0], 8, 0);
        }
    }
    if (data->flags & 4) {
        time = Hu3DData[obj->model[0]].motTime;
        if ((time >= 28.0f) & (time < 30.0f)) {
            HuAudFXPlay(0x4E3);
        }
        if (time >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
            data->flags &= ~4;
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[m262_dorrieObj->motion[0]].motId, 0, 10, 0);
            Hu3DMotionAttrSet(obj->model[0], 2, 2);
        }
        if (Hu3DData[obj->model[0]].motTime == 50.0f) {
            Hu3DMotionAttrSet(m262_stageObjTbl[0]->model[1], 8, 0);
            Hu3DMotionAttrSet(m262_stageObjTbl[0]->model[1], 2, 2);
            m262_RippleStop();
            m262_RaftSpinStart();
            for (i = 0; i < 6; i++) {
                m262_WakeStart(i);
            }
        }
    }
    m262_HookPosGet(obj->model[0], "item_hook", Hu3DData[obj->model[0]].motTime, &hookPos);
    data->hookPos.x = hookPos.x;
    data->hookPos.y = hookPos.y;
    data->hookPos.z = hookPos.z;
}

void m262_DorrieDipStart(void) {
    omAddPrcObj(m262_DorrieDipProc, 0x50, 0, 0);
}

void m262_DorrieDipProc(void) {
    DorrieDipDorrie *data = m262_dorrieObj->data;

    Hu3DMotionShiftSet(m262_dorrieObj->model[0], Hu3DData[m262_dorrieObj->motion[1]].motId, 0, 10, 0);
    data->flags |= 2;
    while (Hu3DData[m262_dorrieObj->model[0]].motTime <
           Hu3DMotion[Hu3DData[m262_dorrieObj->model[0]].motId].unk02) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(m262_dorrieObj->model[0], Hu3DData[m262_dorrieObj->motion[0]].motId, 0, 10, 0);
    Hu3DMotionAttrSet(m262_dorrieObj->model[0], 2, 2);
    data->flags &= ~2;
    MgFlowStatSet(MG_STATE_FINISH);
    omDelPrcObj(NULL);
}

void m262_DorrieRoarStart(void) {
    omObjData *obj = m262_dorrieObj;
    DorrieDipDorrie *data = obj->data;

    data->flags |= 4;
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 0xA, 0);
}

void m262_PlayerObjInit(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            m262_playerNo = i;
            break;
        }
    }
    m262_PlayerInit(obj, m262_playerNo);
}

void m262_PlayerInit(omObjData *obj, s32 playerIdx) {
    s32 motion0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    s32 motion1[8] = { 4, 4, 4, 4, 4, 4, 4, 4 };
    s32 motion2[8] = { 31, 31, 31, 31, 31, 31, 31, 31 };
    s32 motion3[8] = { 54, 54, 54, 54, 54, 54, 54, 54 };
    s32 motion4[8] = { 53, 53, 53, 53, 53, 53, 53, 53 };
    s32 motion5[8] = { 15, 15, 15, 15, 15, 15, 15, 15 };
    s32 motion6[8] = { 6, 6, 6, 6, 6, 6, 6, 6 };
    s32 motion7[8] = { 156, 156, 156, 156, 156, 156, 156, 156 };
    s32 character;
    s32 model, motion;
    MgPlayerWork *data;

    mgPlayerObjTbl[mgPlayerObjNum++] = obj;
    character = GwPlayer[playerIdx].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharModelNoTbl[character][3];
    MgPlayerCreate(obj, model, motion, playerIdx, 0x20A99, 0x20A99);
    data = obj->data;
    obj->model[3] = Hu3DModelRead(3, 0x6DD);
    obj->model[4] = Hu3DModelRead(4, 0x6DD);
    obj->model[6] = Hu3DModelRead(5, 0x6DD);
    obj->model[5] = Hu3DModelRead(6, 0x6DD);
    obj->model[7] = Hu3DModelRead(8, 0x6DD);
    obj->model[8] = Hu3DModelRead(7, 0x6DD);
    MgPlayerMotLoad(obj, 0, CharMotionDataNumGet(character, (s16)motion0[character]), 1, 0);
    MgPlayerMotLoad(obj, 6, CharMotionDataNumGet(character, (s16)motion1[character]), 1, 19);
    MgPlayerMotLoad(obj, 21, CharMotionDataNumGet(character, (s16)motion2[character]), 0, 0);
    MgPlayerMotLoad(obj, 14, CharMotionDataNumGet(character, (s16)motion3[character]), 1, 120);
    MgPlayerMotLoad(obj, 13, CharMotionDataNumGet(character, (s16)motion4[character]), 1, 120);
    MgPlayerMotLoad(obj, 18, CharMotionDataNumGet(character, (s16)motion5[character]), 2, 0);
    MgPlayerMotLoad(obj, 8, CharMotionDataNumGet(character, (s16)motion6[character]), 1, 29);
    MgPlayerMotLoad(obj, 38, CharMotionDataNumGet(character, (s16)motion7[character]), 0, 0);
    omSetTra(obj, 50.0f, 133.0f, 0.0f);
    data->unk3C = 270.0f;
    MgPlayerMapAttrSet(obj, 0, 2);
    MgPlayerMapAttrSet(obj, 1, 2);
    MgPlayerMapAttrSet(obj, 2, 2);
    MgPlayerMapAttrSet(obj, 3, 2);
    MgPlayerMapAttrSet(obj, 4, 2);
    MgPlayerMotSet(obj, 0);
    m262_playerFlag = 0;
    obj->func = m262_PlayerObjMain;
}

void m262_PlayerObjMain(omObjData *obj) {
    MgPlayerWork *data = obj->data;
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    HuPadStkX[data->unk57] = 0;
    HuPadStkY[data->unk57] = 0;
    if (GwPlayer[data->unk59].stat & 1) {
        HuPadBtn[data->unk57] = 0;
        HuPadBtnDown[data->unk57] = 0;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY && (GwPlayer[data->unk59].stat & 1)) {
        m262_ComInput();
    }
    MgPlayerObjMain(obj);
    if (data->unk5C == 0x200) {
        m262_seqNo = 3;
        if (data->unk5C == 0x200 && data->unk50 == 0x80 && !(m262_playerFlag & 1)) {
            m262_playerFlag |= 1;
            m262_DorrieDipStart();
        }
    }
    data->unk60 = 0;
    obj->trans.x = x;
    obj->trans.z = z;
}

void m262_CameraZoomOutStart(void) {
    omAddPrcObj(m262_CameraZoomOutProc, 0x50, 0, 0);
}

void m262_CameraZoomOutProc(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += (1541.0f - 500.0f) / 30.0f;
        CRot.x += (301.6f - 345.0f) / 30.0f;
        if (CRot.x < 301.6f) {
            CRot.x = 301.6f;
        }
        Center.x += -2.9f / 30.0f;
        Center.y += (98.6f - 190.0f) / 30.0f;
        Center.z += 82.6f / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1541.0f;
    CRot.x = 301.6f;
    Center.x = -2.9f;
    Center.y = 98.6f;
    Center.z = 82.6f;
    omDelPrcObj(NULL);
}

void m262_ItemObjCreate(void) {
    s32 used[16]; // Initialized but unused in the original function.
    s32 itemFiles[16] = { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 };
    omObjData *obj;
    DorrieDipSplashes *splashes;
    DorrieDipDips *dips;
    s32 itemIdx;
    s32 i;
    void *spriteData;
    s16 sprite;

    obj = omAddObj(254, 10, 0, -1, m262_ItemObjMain);
    obj->data = HuMemAllocTag(sizeof(DorrieDipSplashes), TAG_OVERLAY);
    m262_itemObj = obj;
    splashes = obj->data;
    dips = m262_raftObj->data;
    for (i = 0; i < 16; i++) {
        used[i] = 0;
    }
    (void)used;
    m262_koopaRaftNo = (u8)(rand8() % 6);
    m262_raftItemTbl[m262_koopaRaftNo] = 17;
    itemIdx = 0;
    for (i = 0; i < 6; i++) {
        if (i == m262_koopaRaftNo) {
            continue;
        }
        m262_raftItemTbl[i] = mgInstColumnTbl[itemIdx];
        spriteData = DataRead(itemFiles[m262_raftItemTbl[i]] | 0x210000);
        sprite = Hu3DSprModelCreate(spriteData, 0xA99, 8);
        DataClose(spriteData);
        obj->model[itemIdx] = Hu3DSprModelData[sprite].modelId;
        Hu3DModelObjAttrSet(obj->model[itemIdx], 0x70000000, 0x70000000);
        splashes->posX[itemIdx] = sindf(dips->unk18[i]) * 450.0f;
        splashes->posY[itemIdx] = 1500.0f;
        splashes->posZ[itemIdx] = cosdf(dips->unk18[i]) * 450.0f;
        splashes->playerIdx[itemIdx] = i;
        splashes->unk64[itemIdx] = 30.0f;
        splashes->unk8C[itemIdx] = 0;
        splashes->unk78[itemIdx] = 0;
        if (itemIdx == 0) {
            omSetTra(obj, splashes->posX[itemIdx], splashes->posY[itemIdx], splashes->posZ[itemIdx]);
            omSetSca(obj, 3.0f, 3.0f, 3.0f);
        } else {
            Hu3DModelPosSet(obj->model[itemIdx], splashes->posX[itemIdx], splashes->posY[itemIdx], splashes->posZ[itemIdx]);
            Hu3DModelScaleSet(obj->model[itemIdx], 3.0f, 3.0f, 3.0f);
        }
        splashes->flags[itemIdx] = 0;
        if (itemIdx == 0) {
            obj->model[itemIdx + 5] = Hu3DModelRead(9, 0x4A9);
        } else {
            obj->model[itemIdx + 5] = Hu3DModelLink(obj->model[5]);
        }
        itemIdx++;
    }
}

void m262_ItemObjMain(omObjData *obj) {
    s32 i;
    DorrieDipSplashes *splashes = obj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    DorrieDipDorrie *dorrie = m262_dorrieObj->data;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        } else {
            Hu3DModelPosSet(obj->model[i], splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], splashes->posX[i], splashes->unk64[i], splashes->posZ[i]);
        if (splashes->flags[i] & 4) {
            splashes->unk50[i] = 1.0f;
        } else {
            splashes->unk50[i] = (1440.0f - splashes->posY[i]) / 1440.0f;
        }
        Hu3DModelScaleSet(obj->model[i + 5], splashes->unk50[i], 1.0f, splashes->unk50[i]);
        if (splashes->flags[i] & 1) {
            splashes->posX[i] = sindf(dips->unk18[splashes->playerIdx[i]]) * 450.0f;
            splashes->posY[i] = m262_waterY + 60.0f;
            splashes->posZ[i] = cosdf(dips->unk18[splashes->playerIdx[i]]) * 450.0f;
        }
        if (splashes->flags[i] & 2) {
            splashes->posY[i] += splashes->velY[i];
            splashes->velY[i] -= 3.0f;
            if (splashes->posY[i] <= 60.0f) {
                splashes->posY[i] = 60.0f;
                splashes->flags[i] &= ~2;
                splashes->flags[i] |= 1;
            }
        }
        if (splashes->flags[i] & 4) {
            splashes->posX[i] = dorrie->hookPos.x;
            splashes->posY[i] = dorrie->hookPos.y + 80.0f;
            splashes->posZ[i] = dorrie->hookPos.z;
            splashes->unk64[i] = dorrie->hookPos.y + 30.0f;
        }
        if (splashes->flags[i] & 8) {
            splashes->posY[i] = sindf(splashes->unk78[i]) * 50.0f + splashes->unk8C[i];
            splashes->unk78[i] += 5.0f;
            if (splashes->unk78[i] >= 360.0f) {
                splashes->unk78[i] -= 360.0f;
            }
            EffectPosSet(m262_itemEffNo, splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        }
    }
}

void m262_ItemDropStart(void) {
    s32 i;
    DorrieDipSplashes *splashes = (DorrieDipSplashes *)m262_itemObj->data;

    for (i = 0; i < 5; i++) {
        splashes->flags[i] |= 2;
        splashes->velY[i] = 0;
        splashes->posY[i] = 1500.0f;
    }
}

void m262_KoopaObjCreate(void) {
    omObjData *obj;
    DorrieDipData *data;
    DorrieDipDips *dips;

    obj = omAddObj(254, 2, 3, -1, m262_KoopaObjMain);
    obj->data = HuMemAllocTag(sizeof(DorrieDipData), TAG_OVERLAY);
    m262_koopaObj = obj;
    data = obj->data;
    dips = m262_raftObj->data;
    obj->model[0] = Hu3DModelRead(0xA00EE, 0x4B9);
    obj->model[1] = Hu3DModelRead(9, 0x4A9);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F6);
    omObjMotionRead(obj, 2, 0xA00F1);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    data->pos.x = sindf(dips->unk18[m262_koopaRaftNo]) * 450.0f;
    data->pos.y = 1500.0f;
    data->pos.z = cosdf(dips->unk18[m262_koopaRaftNo]) * 450.0f;
    data->unk1C = 30.0f;
    data->unk10 = 0;
    data->unk14 = 0;
    omSetTra(obj, data->pos.x, data->pos.y, data->pos.z);
}

void m262_KoopaObjMain(omObjData *obj) {
    DorrieDipData *data = obj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    DorrieDipDorrie *dorrie = m262_dorrieObj->data;

    omSetTra(obj, data->pos.x, data->pos.y, data->pos.z);
    omSetRot(obj, 0.0f, data->unk10, 0.0f);
    Hu3DModelPosSet(obj->model[1], data->pos.x, data->unk1C, data->pos.z);
    if (data->unk14 & 4) {
        data->unk18 = 1.0f;
    } else {
        data->unk18 = (1440.0f - data->pos.y) / 1440.0f;
    }
    Hu3DModelScaleSet(obj->model[1], data->unk18, 1.0f, data->unk18);
    if (data->unk14 & 2) {
        data->pos.x = sindf(dips->unk18[m262_koopaRaftNo]) * 450.0f;
        data->pos.y = 50.0f;
        data->pos.z = cosdf(dips->unk18[m262_koopaRaftNo]) * 450.0f;
        data->unk10 = dips->unk18[m262_koopaRaftNo];
    }
    if (data->unk14 & 1) {
        data->pos.y += data->unk0C;
        data->unk0C -= 3.0f;
        data->unk10 = dips->unk18[m262_koopaRaftNo];
        if (data->pos.y <= 60.0f) {
            data->pos.y = 60.0f;
            data->unk14 &= ~1;
            data->unk14 |= 2;
        }
    }
    if (data->unk14 & 4) {
        data->pos.x = dorrie->hookPos.x;
        data->pos.y = dorrie->hookPos.y + 60.0f;
        data->pos.z = dorrie->hookPos.z;
        data->unk1C = dorrie->hookPos.y + 30.0f;
    }
}

void m262_KoopaDropStart(void) {
    DorrieDipData *data = m262_koopaObj->data;

    data->unk14 |= 1;
    data->unk0C = 0;
}

void m262_DropStart(void) {
    omAddPrcObj(m262_DropProc, 0x50, 0, 0);
}

void m262_DropProc(void) {
    m262_ItemDropStart();
    HuPrcSleep(30);
    m262_KoopaDropStart();
    omDelPrcObj(NULL);
}

void m262_KoopaLeaveStart(void) {
    omAddPrcObj(m262_KoopaLeaveProc, 0x50, 0, 0);
}

void m262_KoopaLeaveProc(void) {
    DorrieDipData *data = m262_koopaObj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    f32 radius;
    f32 velY;
    s32 landed;

    data->unk14 &= ~2;
    if (m262_grabRaftNo == m262_koopaRaftNo) {
        while (data->unk10 != 0.0f) {
            data->unk10 += 9.0f;
            if (data->unk10 >= 360.0f) {
                data->unk10 = 0.0f;
            }
            HuPrcVSleep();
        }
        Hu3DMotionModelSet(m262_koopaObj->model[0], m262_koopaObj->motion[1]);
        Hu3DMotionAttrSet(m262_koopaObj->model[0], 2, 2);
        HuAudFXPlay(0x4E2);
        omDelPrcObj(NULL);
    }
    radius = 450.0f;
    velY = 90.0f;
    data->unk10 = dips->unk18[m262_koopaRaftNo];
    Hu3DMotionModelSet(m262_koopaObj->model[0], m262_koopaObj->motion[1]);
    landed = 0;
    while (radius < 1050.0f) {
        data->pos.x = radius * sindf(dips->unk18[m262_koopaRaftNo]);
        data->pos.y = velY + data->pos.y;
        velY -= 10.0f;
        radius += 30.0f;
        if (data->pos.y < 80.0f) {
            data->pos.y = 80.0f;
            if (landed == 0) {
                landed = 1;
                Hu3DMotionModelSet(m262_koopaObj->model[0], m262_koopaObj->motion[2]);
                Hu3DMotionAttrSet(m262_koopaObj->model[0], 2, 2);
            }
        }
        data->pos.z = radius * cosdf(dips->unk18[m262_koopaRaftNo]);
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m262_TimeUpStart(void) {
    omAddPrcObj(m262_TimeUpProc, 0x50, 0, 0);
}

void m262_TimeUpProc(void) {
    DorrieDipData *data = m262_koopaObj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    s32 i;
    f32 rotStep;

    for (i = 0; i < 6; i++) {
        dips->unk00[i] &= ~1;
        Hu3DModelAttrSet(m262_raftObj->model[i + 6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        if (i != m262_koopaRaftNo) {
            m262_RaftBurst(i);
        }
    }
    Hu3DMotionAttrSet(m262_stageObjTbl[0]->model[1], 1, 1);
    m262_RippleStart();
    data->unk14 &= ~2;
    rotStep = (data->unk10 >= 180.0) ? 9.0f : -9.0f;
    while (data->unk10 != 0.0f) {
        data->unk10 = rotStep + data->unk10;
        if (data->unk10 >= 360.0f) {
            data->unk10 = 0.0f;
        }
        if (data->unk10 < 0.0f) {
            data->unk10 = 0.0f;
        }
        HuPrcVSleep();
    }
    Hu3DMotionModelSet(m262_koopaObj->model[0], m262_koopaObj->motion[1]);
    Hu3DMotionAttrSet(m262_koopaObj->model[0], 2, 2);
    omDelPrcObj(NULL);
}

void m262_PadWaitStart(void) {
    omAddPrcObj(m262_PadWaitProc, 0x50, 0, 0);
}

void m262_PadWaitProc(void) {
    while (1) {
        if (HuPadBtnDown[m262_playerNo] & A_BUTTON) {
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m262_TimerStart(void) {
    omAddPrcObj(m262_TimerProc, 0x50, 0, 0);
}

void m262_TimerProc(void) {
    s32 seconds = 10;
    s32 frames = 30;

    GMesPosSet(GMesCreate(26, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        GMesTimerValueSet(seconds);
        HuPrcVSleep();
        if (MgFlowStatGet() == MG_STATE_FINISH) {
            break;
        }
    } while (seconds > 0);
    if (m262_seqNo == 0) {
        m262_seqNo = 2;
        MgFlowStatSet(MG_STATE_FINISH);
    }
    GMesTimerEnd();
    omDelPrcObj(NULL);
}

void m262_StageObjCreate(void) {
    omObjData *obj;
    DorrieDipBackground *data;

    obj = omAddObj(255, 4, 0, -1, m262_StageObjMain);
    m262_stageObjTbl[0] = obj;
    data = HuMemAllocTag(sizeof(DorrieDipBackground), TAG_OVERLAY);
    obj->data = data;
    obj->model[0] = Hu3DModelRead2(0x5F0000, 0x699);
    obj->model[1] = Hu3DModelRead2(0x5F0001, 0x699);
    obj->model[2] = Hu3DModelRead2(0x5F0003, 0x699);
    obj->model[3] = Hu3DModelRead2(0x5F0004, 0x699);
    m262_unusedScale = 1.0f;
    obj->trans.x = 0;
    obj->trans.y = 0;
    obj->trans.z = 0;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = obj;
    memset(obj->data, 0, sizeof(DorrieDipBackground));
    data->unk03 = 1;
    data->unk08 = 0.5f;
    data->unk04 = 0;
    MgMapAttrSet(obj, 2, 133.0f);
    Hu3DMotionAttrSet(obj->model[1], 8, 8);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    omSetTra(obj, 0.0f, 13.0f, 0.0f);
    m262_waterAngle = 0;
}

void m262_StageObjMain(omObjData *obj) {
    m262_waterY = sindf(m262_waterAngle) * 10.0f - 10.0f;
    m262_waterAngle += 5.0f;
    if (m262_waterAngle >= 360.0f) {
        m262_waterAngle -= 360.0f;
    }
    Hu3DData[obj->model[1]].pos.y = m262_waterY;
    Hu3DData[obj->model[3]].pos.y = m262_waterY + 5.0f;
}

void m262_HookPosGet(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    Hu3DModelObjMtxFrameGet(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    func_80088800_main(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    mtxCat(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

void m262_BurstObjCreate(void) {
    s32 i;
    omObjData *obj;
    DorrieDipEffects *data;
    s32 flags = 0xA3D;

    obj = omAddObj(255, 6, 0, -1, m262_BurstObjMain);
    m262_burstObj = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipEffects), TAG_OVERLAY);
    data = obj->data;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i] = Hu3DModelRead(0x5D0008, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data->flags[i] = 0;
    }
}

void m262_BurstObjMain(omObjData *obj) {
    s32 i;
    f32 x, z;
    DorrieDipEffects *data = obj->data;
    DorrieDipDips *dips = m262_raftObj->data;

    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        z = cosdf(dips->unk18[i]) * 450.0f;
        data->posX[i] = x;
        data->posY[i] = 50.0f;
        data->posZ[i] = z;
        if (i == 0) {
            omSetTra(obj, data->posX[i], data->posY[i], data->posZ[i]);
            omSetRot(obj, CRot.x, 0.0f, 0.0f);
            omSetSca(obj, 1.5f, 1.5f, 1.5f);
        } else {
            Hu3DModelPosSet(obj->model[i], data->posX[i], data->posY[i], data->posZ[i]);
            Hu3DModelRotSet(obj->model[i], CRot.x, 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], 1.5f, 1.5f, 1.5f);
        }
        if ((data->flags[i] & 1) &&
            Hu3DData[obj->model[i]].motTime >= Hu3DMotion[Hu3DData[obj->model[i]].motId].unk02) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            data->flags[i] &= ~1;
        }
    }
}

void m262_RaftBurst(s32 dipIdx) {
    s32 i;
    s32 splashIdx;
    f32 x, z;
    DorrieDipEffects *effects = m262_burstObj->data;
    DorrieDipDips *dips = m262_raftObj->data;
    DorrieDipSplashes *splashes = m262_itemObj->data;
    DorrieDipDorrie *dorrie = m262_dorrieObj->data;

    Hu3DModelAttrSet(m262_raftObj->model[dipIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m262_raftObj->model[dipIdx + 6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    splashIdx = -1;
    for (i = 0; i < 5; i++) {
        if (splashes->playerIdx[i] == dipIdx) {
            splashIdx = i;
        }
    }
    if (splashIdx != -1) {
        if (dipIdx != m262_grabRaftNo) {
            Hu3DModelAttrSet(m262_itemObj->model[splashIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrSet(m262_itemObj->model[splashIdx + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    x = sindf(dips->unk18[dipIdx]) * 450.0f;
    z = cosdf(dips->unk18[dipIdx]) * 450.0f;
    effects->posX[dipIdx] = x;
    effects->posY[dipIdx] = 50.0f;
    effects->posZ[dipIdx] = z;
    if (dipIdx == m262_grabRaftNo) {
        effects->posX[dipIdx] = dorrie->hookPos.x;
        effects->posY[dipIdx] = dorrie->hookPos.y;
        effects->posZ[dipIdx] = dorrie->hookPos.z;
    }
    dips->unk00[dipIdx] &= ~1;
    effects->flags[dipIdx] |= 1;
    Hu3DModelAttrSet(m262_burstObj->model[dipIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet(m262_stageObjTbl[0]->model[1], 1, 1);
}

void m262_ResultStart(void) {
    omAddPrcObj(m262_ResultProc, 0x50, 0, 0);
}

void m262_ResultProc(void) {
    MgPlayerWork *data = mgPlayerObjTbl[0]->data;
    s32 i;

    MgPlayerMotForceSet(mgPlayerObjTbl[0], 38);
    for (i = 0; i < 10; i++) {
        data->unk3C = i * 90.0f / 10.0f + 270.0f;
        HuPrcVSleep();
    }
    if (m262_grabRaftNo != -1 && m262_raftItemTbl[m262_grabRaftNo] != 17) {
        MgPlayerMotForceSet(mgPlayerObjTbl[0], 13);
        Hu3DMotionShiftSet(m262_dorrieObj->model[0], Hu3DData[m262_dorrieObj->motion[4]].motId, 0, 10, 0);
        HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[data->unk59].chr][0] | 0x35);
        for (i = 0; i < 60; i++) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x4E4);
    } else {
        MgPlayerMotForceSet(mgPlayerObjTbl[0], 14);
        if (m262_grabRaftNo == -1) {
            Hu3DMotionShiftSet(m262_dorrieObj->model[0], Hu3DData[m262_dorrieObj->motion[3]].motId, 0, 10, 0);
        }
    }
    omDelPrcObj(NULL);
}

void m262_ItemGetStart(void) {
    omAddPrcObj(m262_ItemGetProc, 0x50, 0, 0);
}

void m262_ItemGetProc(void) {
    s32 i;
    s32 splashIdx;
    f32 deltaX, deltaZ, startY, angle;
    DorrieDipSplashes *splashes;
    DorrieDipDorrie *dorrie;

    HuAudFXPlay(25);
    splashes = m262_itemObj->data;
    dorrie = m262_dorrieObj->data;
    m262_itemEffNo = EffectCreate(0xB0004, 0x6A9);
    splashIdx = -1;
    for (i = 0; i < 5; i++) {
        if (splashes->playerIdx[i] == m262_grabRaftNo) {
            splashIdx = i;
        }
    }
    if (splashIdx == -1) {
        osSyncPrintf("!!\n");
    }
    splashes->flags[splashIdx] &= ~4;
    splashes->flags[splashIdx] &= ~1;
    splashes->flags[splashIdx] |= 8;
    deltaX = mgPlayerObjTbl[0]->trans.x - dorrie->hookPos.x;
    deltaZ = mgPlayerObjTbl[0]->trans.z - dorrie->hookPos.z;
    startY = splashes->posY[splashIdx];
    for (i = 0; i < 30; i++) {
        splashes->posX[splashIdx] = deltaX / 30.0f + splashes->posX[splashIdx];
        angle = i * 180.0f / 30.0f;
        splashes->unk8C[splashIdx] = sindf(angle) * 400.0f + startY;
        if (angle > 90.0f) {
            if (splashes->unk8C[splashIdx] < mgPlayerObjTbl[0]->trans.y + 300.0f) {
                splashes->unk8C[splashIdx] = mgPlayerObjTbl[0]->trans.y + 300.0f;
            }
        }
        splashes->posZ[splashIdx] = deltaZ / 30.0f + splashes->posZ[splashIdx];
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m262_RippleObjCreate(void) {
    s32 i;
    omObjData *obj;
    s32 *data;
    s32 flags = 0x69D;

    obj = omAddObj(255, 9, 0, -1, m262_RippleObjMain);
    m262_rippleObj = obj;
    obj->data = HuMemAllocTag(9 * sizeof(s32), TAG_OVERLAY);
    data = obj->data;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            obj->model[i] = Hu3DModelRead(0x5F000C, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data[i] = 0;
    }
    m262_rippleFlag = 0;
}

void m262_RippleObjMain(omObjData *obj) {
    s32 i;
    s32 *data = obj->data;

    for (i = 0; i < 9; i++) {
        if ((data[i] & 1) && Hu3DData[obj->model[i]].motTime >= Hu3DMotion[Hu3DData[obj->model[i]].motId].unk02) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            data[i] &= ~1;
        }
    }
}

void m262_RippleStart(void) {
    omAddPrcObj(m262_RippleProc, 0x50, 0, 0);
}

void m262_RippleStop(void) {
    m262_rippleFlag &= ~2;
}

void m262_RippleProc(void) {
    s32 *data = m262_rippleObj->data;
    s32 i;
    s32 effectIdx;
    s32 angle;
    s32 radius;
    f32 x, z;

    m262_rippleFlag |= 2;
    while (m262_rippleFlag & 2) {
        if (rand8() % 16 == 0) {
            effectIdx = -1;
            for (i = 0; i < 9; i++) {
                if (!(data[i] & 1)) {
                    effectIdx = i;
                    break;
                }
            }
            if (effectIdx != -1) {
                data[effectIdx] |= 1;
                angle = (rand8() * 2) % 360;
                radius = (rand8() * 2) % 500;
                x = radius * sindf(angle);
                z = radius * cosdf(angle);
                if (effectIdx == 0) {
                    omSetTra(m262_rippleObj, x, 0.0f, z);
                } else {
                    Hu3DModelPosSet(m262_rippleObj->model[effectIdx], x, 0.0f, z);
                }
                Hu3DModelAttrSet(m262_rippleObj->model[effectIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DMotionTimeSet(m262_rippleObj->model[effectIdx], 0.0f);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m262_ComInit(void) {
    s32 i;
    s32 total;
    s32 targetDip;
    s32 chance;

    chance = (u8)(rand8() % 100);
    for (i = 0, total = 0; i < 5; i++) {
        if (chance >= total && chance < total + mgInstSlotTbl[i]) {
            break;
        }
        total += mgInstSlotTbl[i];
    }
    if (i == 5) {
        i = 4;
    }
    targetDip = 0;
    for (total = 0; total < 6; total++) {
        if (m262_raftItemTbl[total] == i) {
            targetDip = total;
        }
    }
    chance = (u8)(rand8() % 100);
    switch (GwPlayer[m262_playerNo].cpu_difficulty) {
        case 0:
            if (chance < 20) {
                targetDip = m262_koopaRaftNo;
            }
            break;
        case 1:
            if (chance < 15) {
                targetDip = m262_koopaRaftNo;
            }
            break;
        case 2:
            if (chance < 10) {
                targetDip = m262_koopaRaftNo;
            }
            break;
        case 3:
            if (chance < 5) {
                targetDip = m262_koopaRaftNo;
            }
            break;
    }
    m262_comWork.grabDelay = 8;
    m262_comWork.targetDip = targetDip;
    m262_comWork.triggered = 0;
}

void m262_WakeObjCreate(void) {
    s32 i;
    omObjData *obj;
    DorrieDipWakes *data;
    s32 flags = 0x6BD;

    obj = omAddObj(255, 6, 0, -1, m262_WakeObjMain);
    m262_wakeObj = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipWakes), TAG_OVERLAY);
    data = obj->data;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i] = Hu3DModelRead(0x5F000D, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data->flags[i] = 0;
        data->scaleX[i] = 1.0f;
    }
}

void m262_WakeObjMain(omObjData *obj) {
    s32 i;
    DorrieDipWakes *data = obj->data;
    DorrieDipDips *dips = m262_raftObj->data;

    for (i = 0; i < 6; i++) {
        if (i == 0) {
            omSetTra(obj, data->posX[i], data->posY[i], data->posZ[i]);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
            omSetSca(obj, data->scaleX[i], 1.0f, 1.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], data->posX[i], data->posY[i], data->posZ[i]);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
            Hu3DModelScaleSet(obj->model[i], data->scaleX[i], 1.0f, 1.0f);
        }
        if (data->flags[i] & 1) {
            data->scaleX[i] = (4.8f - dips->unk30[i]) / 4.8f;
            if (data->scaleX[i] == 0.0f) {
                Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                data->flags[i] &= ~1;
            }
        }
        data->posX[i] = sindf(dips->unk18[i]) * 450.0f;
        data->posY[i] = m262_waterY;
        data->posZ[i] = cosdf(dips->unk18[i]) * 450.0f;
    }
}

void m262_WakeStart(s32 dipIdx) {
    DorrieDipWakes *data = m262_wakeObj->data;
    DorrieDipDips *dips = m262_raftObj->data;

    data->flags[dipIdx] |= 1;
    data->posX[dipIdx] = sindf(dips->unk18[dipIdx]) * 450.0f;
    data->posY[dipIdx] = m262_waterY;
    data->posZ[dipIdx] = cosdf(dips->unk18[dipIdx]) * 450.0f;
    Hu3DModelAttrSet(m262_wakeObj->model[dipIdx], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet(m262_wakeObj->model[dipIdx], 2, 2);
}

void m262_ComInput(void) {
    MgPlayerWork *data = mgPlayerObjTbl[0]->data;
    DorrieDipDips *dips = m262_raftObj->data;

    if (m262_comWork.triggered == 0) {
        if (dips->unk18[m262_comWork.targetDip] >= 175.0f &&
            dips->unk18[m262_comWork.targetDip] < 185.0f) {
            HuPadBtn[data->unk57] |= A_BUTTON;
            HuPadBtnDown[data->unk57] |= A_BUTTON;
            m262_comWork.triggered++;
        }
    }
    if (m262_comWork.triggered != 0) {
        if (--m262_comWork.grabDelay == 0) {
            HuPadBtn[data->unk57] |= Z_TRIG;
            HuPadBtnDown[data->unk57] |= Z_TRIG;
        }
    }
}
