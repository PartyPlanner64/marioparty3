#include "common.h"
#include "game/overlays/minigame.h"
#include "game/sprite.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"

#define PLAYER_WORK(obj) ((LockedOutPlayerWork *)((MgPlayerWork *)(obj)->data)->unk158)

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[0xAF];
} LockedOutMapWork;

typedef struct {
    Vec pos;
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 unk10;
    u8 unk11[3];
} LockedOutDoor;

typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    f32 unk04;
    Vec unk08;
    omObjData *unk14;
} LockedOutKeyWork;

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ u16 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u8 unk34[8];
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42[0xA];
} LockedOutPlayerWork; // Size 0x4C

typedef struct {
    u8 values[8];
} LockedOutCharMotions;

extern s32 omCharModelNoTbl[][6];

Vec m226_doorPosTbl[7] = {
    { 0.0f, 0.0f, -615.0f },
    { 227.5f, 0.0f, -615.0f },
    { 0.0f, 0.0f, -615.0f },
    { 345.0f, 0.0f, -615.0f },
    { -227.5f, 0.0f, -615.0f },
    { 0.0f, 0.0f, -615.0f },
    { -345.0f, 0.0f, -615.0f }
};
s32 m226_phaseTimer = 0;
u16 m226_timer = 0;
s32 m226_winner = -1;
s16 m226_winCameraAngle = 180;
s8 m226_survivorNum = 4;
s8 m226_doorNum = 3;
u8 m226_firstRoundF = 1;
u8 m226_playerSlotTbl[4][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } };
u8 m226_playerSlotNo = 0;
Vec m226_playerStartPosTbl[4] = {
    { -300.0f, 0.0f, 400.0f },
    { -100.0f, 0.0f, 400.0f },
    { 100.0f, 0.0f, 400.0f },
    { 300.0f, 0.0f, 400.0f }
};
f32 m226_playerStartRotTbl[4] = { 180.0f, 180.0f, 180.0f, 180.0f };
Vec m226_finalPosTbl[3] = {
    { -200.0f, 0.0f, 400.0f },
    { 200.0f, 0.0f, 400.0f },
    { 0.0f, 0.0f, 400.0f }
};
u32 m226_randSeed = 0x41C64E6D;

s32 m226_resultMusicDelay BSS;
s16 m226_musicDelay BSS;
MinigameFlow m226_mgFlow BSS;
u8 m226_mgFlowPad[0x60] BSS; /* Unreferenced. */
omObjData *m226_keyObjTbl[10] BSS;
LockedOutDoor m226_doorTbl[3] BSS;
s16 m226_phase BSS;
s16 m226_keyNum BSS;
s16 m226_keyCreateCnt BSS;
s16 m226_keyType BSS;
u8 m226_keyTypePad[4] BSS; /* Unreferenced. */
f32 m226_cameraMtx[4][4] BSS;
f32 m226_cameraInvMtx[4][4] BSS;
f32 m226_cameraFovTan BSS;
u8 m226_keyOrderTbl[12] BSS;

void m226_CameraViewInit(omObjData *object);
void m226_MtxInvert(HuMtx4F, HuMtx4F);
void m226_MapObjCreateAll(void);
void m226_MapObjInit(omObjData *object);
void m226_MapBoundObjInit(omObjData *object);
void m226_PlayerObjCreateAll(void);
s32 m226_Rand16Get(void);
f32 m226_AngleCalc(f32 y, f32 x);
f32 m226_DistXZCalc(Vec *arg0, Vec *arg1);
void m226_KeyObjCreateAll(void);
void m226_KeyObjInit(omObjData *object);
void m226_KeyObjMain(omObjData *object);
void m226_PlayerObjInit(omObjData *object);
void m226_MainObjMain(omObjData *object);
void m226_DoorPush(omObjData *object);
void m226_PlayerObjMain(omObjData *object);
u16 m226_PlayerComInput(omObjData *object);
void m226_KeyGrabUpdate(omObjData *object, u8 isPlayer, u8 canGrab);
void m226_PlayerWorkGet(omObjData *object, MgPlayerWork **data, LockedOutPlayerWork **arg2);
void m226_HookPosGet(s16 model, char *hook, s16 time, Vec *pos);
void m226_KeyKillAll(void);

void m226_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;

    MapCollInit(2);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    omInitObjMan(0x20, 0);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    MgFieldStatClear();
    m226_CameraViewInit(obj);
    m226_MapObjCreateAll();
    memset(&m226_mgFlow, 0, 0x28);
    m226_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m226_mgFlow);
    m226_PlayerObjCreateAll();
    m226_keyNum = 9;
    m226_keyCreateCnt = 0;
    m226_KeyObjCreateAll();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void m226_CameraViewInit(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 1400.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    m226_cameraFovTan = sinFov / cosFov;
    guMtxL2F(m226_cameraMtx, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(m226_cameraInvMtx, &camera->mtxs[0].lookAtMtx);
    m226_MtxInvert(m226_cameraInvMtx, m226_cameraInvMtx);
}

void m226_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void m226_MtxInvert(HuMtx4F src, HuMtx4F dst) {
    f32 mtx[4][4];
    f32 t0;
    f32 t1;
    f32 t2;
    f32 det;
    f32 *dstRow3;

    mtxCopy(mtx, src);

    t0 = mtx[1][1] * mtx[2][2] - mtx[1][2] * mtx[2][1];
    t1 = mtx[1][2] * mtx[2][0] - mtx[1][0] * mtx[2][2];

    t2 = mtx[1][0] * mtx[2][1] - mtx[1][1] * mtx[2][0];

    det = t0 * mtx[0][0] + t1 * mtx[0][1] + t2 * mtx[0][2];

    dstRow3 = &dst[3][0];
    if (det != 0.0f) {
        det = 1.0f / det;

        dst[0][0] = t0 * det;
        dst[1][0] = t1 * det;
        dst[2][0] = t2 * det;

        dst[0][1] = (mtx[0][2] * mtx[2][1] - mtx[0][1] * mtx[2][2]) * det;
        dst[0][2] = (mtx[0][1] * mtx[1][2] - mtx[0][2] * mtx[1][1]) * det;
        dst[1][1] = (mtx[0][0] * mtx[2][2] - mtx[0][2] * mtx[2][0]) * det;

        dst[1][2] = (mtx[0][2] * mtx[1][0] - mtx[0][0] * mtx[1][2]) * det;
        dst[2][1] = (mtx[0][1] * mtx[2][0] - mtx[0][0] * mtx[2][1]) * det;
        dst[2][2] = (mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0]) * det;

        dst[2][3] = 0.0f;
        dst[1][3] = 0.0f;
        dst[0][3] = 0.0f;
        dst[3][3] = 1.0f;

        m226_MtxVecMul(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void m226_ScreenPosCalc(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, m226_cameraMtx, mtx);
    depth = mtx[3][2] * m226_cameraFovTan;
    scale = __builtin_fabsf(depth);
    if (scale == 0.0) {
        return;
    }
    dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
    dst[1] = -mtx[3][1] * 120.0f / scale;
}

void m226_WorldPosCalc(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + m226_cameraMtx[3][2];
    f32 scale = __builtin_fabsf(depth * m226_cameraFovTan);
    f32 mtx[4][4];

    guTranslateF(mtx, ((x + x) * scale * 1.3333334f) / SCREEN_WIDTH, -((y + y) * scale / SCREEN_HEIGHT), depth);
    guMtxCatF(mtx, m226_cameraInvMtx, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void m226_MapObjCreateAll(void) {
    mgMapObjNum = 0;
    MgMapBaseSet(0);
    m226_keyType = (f32)m226_Rand16Get() * 1.52587890625e-05 * 3.0;
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 8, 0, -1, m226_MapObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m226_MapBoundObjInit);
    m226_phase = 0;
}

void m226_MapObjInit(omObjData *object) {
    LockedOutMapWork *work;
    s32 i;
    s32 tag;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, 10.0f);
    MgMapBoxSet(object, 0.0f, -600.0f, -615.0f, 600.0f, 615.0f);
    tag = 0x2D9;
    object->model[0] = Hu3DModelRead(0x3B0000, tag);
    object->model[1] = Hu3DModelRead(0x3B0003, tag);
    object->model[6] = Hu3DModelRead(0x3B0010, 0x2DD);
    object->model[7] = Hu3DModelRead(0x3B0011, 0x2DD);
    for (i = 0; i < 3; i++) {
        m226_doorTbl[i].pos.x = m226_doorPosTbl[i * 3].x;
        m226_doorTbl[i].pos.y = m226_doorPosTbl[i * 3].y;
        m226_doorTbl[i].pos.z = m226_doorPosTbl[i * 3].z;
        m226_doorTbl[i].unk0C = 0;
        m226_doorTbl[i].unk10 = 1;
        m226_doorTbl[i].unk0D = object->model[2 + i] =
            Hu3DModelRead((m226_keyType + 4) | 0x3B0000, tag);
        Hu3DModelPosSet(object->model[2 + i], m226_doorTbl[i].pos.x, m226_doorTbl[i].pos.y,
                        m226_doorTbl[i].pos.z);
        Hu3DMotionSpeedSet(object->model[2 + i], 0.0f);
        m226_doorTbl[i].unk0F = Hu3DModelRead2(7, 0x2DD);
        Hu3DMotionSpeedSet(m226_doorTbl[i].unk0F, 0.0f);
        Hu3DModelRotSet(m226_doorTbl[i].unk0F, 90.0f, 0.0f, 0.0f);
        m226_doorTbl[i].unk0E = Hu3DModelLink(object->model[6]);
        Hu3DModelAttrSet(m226_doorTbl[i].unk0E, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(m226_doorTbl[i].unk0E, 0.0f);
    }
    object->model[5] = Hu3DModelRead(0x3B000A, 0x2B9);
    object->func = m226_MainObjMain;
}

void m226_MapBoundObjInit(omObjData *object) {
    LockedOutMapWork *work;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, 10.0f);
    MgMapBoxSet(object, 0.0f, -600.0f, -615.0f, 600.0f, 665.0f);
    object->func = NULL;
}

void m226_MainObjMain(omObjData *object) {
    LockedOutPlayerWork *work;
    s32 i;
    s32 j;
    s32 count;
    s32 rank = 0;
    s32 found;
    u16 tag;
    f32 s;
    f32 c;

    switch (m226_phase) {
        case 0:
            GMesCreate(GMES_MES_7);
            m226_timer = 300;
            m226_phase++;
            m226_musicDelay = 20;
        case 1:
            if (--m226_musicDelay == 0) {
                HuAudSeqPlay(0x35);
            }
            if (GMesStatGet() == 0) {
                MgFlowStatSet(MG_STATE_PLAY);
                m226_phase++;
                GMesCreate(GMES_MES_TIMER, (m226_timer + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x35);
            }
            break;
        case 2:
            count = 0;
            for (i = 0; i < m226_doorNum; i++) {
                count += (m226_doorTbl[i].unk10 == 0);
            }
            if (count >= m226_survivorNum - 1) {
                m226_phase = 3;
            }
            m226_timer--;
            GMesTimerValueSet((m226_timer + 29) / 30);
            if (m226_timer == 0) {
                m226_phase = 3;
            }
            break;
        case 3:
            m226_survivorNum = 0;
            m226_winner = -1;
            for (i = 0; i < 4; i++) {
                if (PLAYER_WORK(mgPlayerObjTbl[i])->unk23 != 0) {
                    m226_survivorNum++;
                    rank++;
                    m226_winner = i;
                }
                if (PLAYER_WORK(mgPlayerObjTbl[i])->unk3C != 0 && PLAYER_WORK(mgPlayerObjTbl[i])->unk3C < 5) {
                    break;
                }
            }
            if (i < 4) {
                break;
            }
            for (i = 0; i < 4; i++) {
                work = PLAYER_WORK(mgPlayerObjTbl[i]);
                if (work->unk23 == 0 && work->unk24 == 0) {
                    work->unk24 = rank;
                }
            }
            if (m226_survivorNum >= 2) {
                WipeCreateOut(WIPE_BOO, 0x1E);
                m226_phase = 4;
                m226_firstRoundF = 0;
            } else {
                GMesTimerEnd();
                GMesCreate(GMES_MES_18);
                HuAudSeqFadeOut(0x78);
                m226_phase = 6;
            }
            break;
        case 4:
            if (WipeStatGet() != 0) {
                break;
            }
            tag = 0x2B9;
            Hu3DModelKill(object->model[1]);
            object->model[1] = Hu3DModelRead(0x3B0002, tag);
            m226_keyType = (f32)m226_Rand16Get() * 1.52587890625e-05 * 3.0;
            m226_doorNum = 2;
            for (i = 0; i < 3; i++) {
                if (object->model[2 + i] != 0) {
                    Hu3DModelKill(object->model[2 + i]);
                    Hu3DModelKill(m226_doorTbl[i].unk0E);
                    object->model[2 + i] = 0;
                    m226_doorTbl[i].unk10 = 0;
                }
                if (i < 2) {
                    m226_doorTbl[i].pos.x = m226_doorPosTbl[i * 3 + 1].x;
                    m226_doorTbl[i].pos.y = m226_doorPosTbl[i * 3 + 1].y;
                    m226_doorTbl[i].pos.z = m226_doorPosTbl[i * 3 + 1].z;
                    m226_doorTbl[i].unk0C = 0;
                    m226_doorTbl[i].unk10 = 1;
                    if (m226_survivorNum == 2) {
                        m226_doorTbl[i].unk0D = object->model[2 + i] =
                            Hu3DModelRead((m226_keyType + 13) | 0x3B0000, tag);
                    } else {
                        m226_doorTbl[i].unk0D = object->model[2 + i] =
                            Hu3DModelRead((m226_keyType + 4) | 0x3B0000, tag);
                    }
                    if (m226_survivorNum == 2) {
                        m226_doorTbl[i].unk0E = Hu3DModelLink(object->model[7]);
                    } else {
                        m226_doorTbl[i].unk0E = Hu3DModelLink(object->model[6]);
                    }
                    Hu3DMotionSpeedSet(m226_doorTbl[i].unk0E, 0.0f);
                    Hu3DMotionSpeedSet(m226_doorTbl[i].unk0F, 0.0f);
                    Hu3DMotionTimeSet(m226_doorTbl[i].unk0F, 0.0f);
                    Hu3DModelAttrSet(m226_doorTbl[i].unk0F, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(object->model[2 + i], m226_doorTbl[i].pos.x,
                                    m226_doorTbl[i].pos.y, m226_doorTbl[i].pos.z);
                    Hu3DMotionSpeedSet(object->model[2 + i], 0.0f);
                }
            }
            Hu3DModelKill(object->model[5]);
            object->model[5] = Hu3DModelRead((14 - m226_survivorNum) | 0x3B0000, tag);
            m226_KeyKillAll();
            m226_keyNum = (m226_survivorNum - 1) * 3;
            m226_keyCreateCnt = 0;
            m226_KeyObjCreateAll();
            GMesTimerValueSet(10);
            WipeCreateIn(WIPE_BOO, 0x1E);
            m226_phase++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                m226_timer = 300;
                m226_phase = 2;
            }
            break;
        case 6:
            if (m226_winner != -1) {
                if (m226_winCameraAngle != 0) {
                    s = sindf(m226_winCameraAngle * 0.5);
                    c = cosdf(m226_winCameraAngle * 0.5);
                    CZoom = (s * 47.0 + 23.0) * 20.0;
                    CRot.x = -(s * 22.0 + 18.0);
                    Center.x = c * m226_doorTbl[PLAYER_WORK(mgPlayerObjTbl[m226_winner])->unk3E].pos.x;
                    Center.y = (s * 1.5 + 4.0) * 20.0;
                    Center.z = c * m226_doorTbl[PLAYER_WORK(mgPlayerObjTbl[m226_winner])->unk3E].pos.z;
                    m226_winCameraAngle -= 6;
                }
            }
            if (m226_winner == -1 && m226_firstRoundF != 0) {
                for (i = 0; i < 4; i++) {
                    PLAYER_WORK(mgPlayerObjTbl[i])->unk24 = 3;
                }
            } else {
                rank = 0;
                for (j = 0; j < 4; j++) {
                    found = 0;
                    for (i = 0; i < 4; i++) {
                        work = PLAYER_WORK(mgPlayerObjTbl[i]);
                        if (work->unk24 == j) {
                            work->unk24 = rank;
                            found = 1;
                        }
                    }
                    rank += found;
                }
            }
            if (GMesStatGet() == 0) {
                if (m226_winner == -1) {
                    m226_phaseTimer = 0x9F;
                } else {
                    m226_phaseTimer = 0x71;
                }
                m226_resultMusicDelay = 15;
                m226_phase++;
                MgFlowStatSet(MG_STATE_RESULT);
            }
            break;
        case 7:
            if (--m226_phaseTimer == 0) {
                m226_phase++;
            }
            if (--m226_resultMusicDelay == 0) {
                if (m226_winner == -1) {
                    HuAudSeqPlay(0x6C);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 8:
            if (m226_phaseTimer != 0) {
                if (--m226_phaseTimer == 0) {
                    m226_phase++;
                }
            } else {
                MgFlowStatSet(MG_STATE_EXIT);
                m226_phaseTimer = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, m226_phaseTimer);
                HuAudSeqFadeOut(m226_phaseTimer);
                HuAudFXAllFadeOut((s16)m226_phaseTimer);
            }
            break;
        case 9:
            HuAudSeqStop();
            omOvlReturnEx(1);
            break;
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m226_phase = 8;
    }
}

void m226_DoorPush(omObjData *object) {
    LockedOutDoor *entry;
    Vec pos;
    f32 frames;
    f32 radius;
    f32 angle;
    s32 i;

    for (i = 0; i < 3; i++) {
        entry = &m226_doorTbl[i];
        if (entry->unk0C == 0) {
            continue;
        }
        frames = Hu3DMotion[Hu3DData[entry->unk0E].motId].unk02;
        radius = Hu3DData[entry->unk0E].motTime * 175.0 / frames + 50.0;
        pos.x = entry->pos.x - 86.5;
        pos.y = entry->pos.y;
        pos.z = entry->pos.z;
        if (m226_DistXZCalc(&pos, &object->trans) > radius) {
            continue;
        }
        angle = m226_AngleCalc(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - radius * sindf(angle);
        object->trans.z = pos.z - radius * cosdf(angle);
    }
}

void m226_PlayerObjCreateAll(void) {
    s32 i;

    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerObjNum = 0;
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 15, 50, -1, m226_PlayerObjInit);
    }
}

const LockedOutCharMotions m226_chrAnimTbl = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void m226_PlayerObjInit(omObjData *object) {
    LockedOutCharMotions motions = m226_chrAnimTbl;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    MgPlayerWork *data;
    LockedOutPlayerWork *work;
    u8 player;
    s8 character;
    u32 model;
    s32 motion;
    s32 linkModel;

    player = m226_playerSlotTbl[m226_playerSlotNo][1];
    character = GwPlayer[player].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharModelNoTbl[character][1];
    linkModel = omCharModelNoTbl[character][2];
    MgPlayerCreate(object, model, motion, player, 0x2D9, 0x2D9);
    object->model[9] = Hu3DModelRead(model | linkModel, 0x2ED);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->trans.x = m226_playerStartPosTbl[m226_playerSlotNo].x;
    object->trans.y = m226_playerStartPosTbl[m226_playerSlotNo].y;
    object->trans.z = m226_playerStartPosTbl[m226_playerSlotNo].z;
    data->unk3C = m226_playerStartRotTbl[m226_playerSlotNo];
    switch (model >> 16) {
        case 6:
            data->unk48 *= 1.25f;
            break;
        case 4:
            data->unk48 *= 1.1f;
            break;
        case 5:
            data->unk48 *= 1.2f;
            break;
    }
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->trans.x = m226_playerStartPosTbl[m226_playerSlotNo].x;
    object->trans.y = m226_playerStartPosTbl[m226_playerSlotNo].y;
    object->trans.z = m226_playerStartPosTbl[m226_playerSlotNo].z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(sizeof(LockedOutPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(LockedOutPlayerWork));
    work = data->unk158;
    work->unk20 = player;
    work->unk21 = character;
    work->unk27 = GwPlayer[player].stat & PLAYER_IS_CPU;
    work->unk22 = GwPlayer[player].cpu_difficulty;
    work->unk1C = model | 0x2F;
    work->unk23 = 0;
    work->unk24 = 0;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk25 = 0;
    work->unk28 = 0;
    work->unk2B = CharAnimCreate(object->model[9], 2, motions.values[character], model | anims[2][character]);
    work->unk29 = Hu3DAnimDataRead(model | anims[0][character]);
    work->unk2A = Hu3DAnimDataRead(model | anims[1][character]);
    Hu3DModelDynamicFree(object->model[9]);
    MgPlayerMapAttrSet(object, 0, 2);
    data->unk50 |= 0x8000;
    object->func = m226_PlayerObjMain;
    object->model[3] = Hu3DModelRead(3, 0x2DD);
    object->model[6] = Hu3DModelRead(5, 0x2DD);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(object, 5, CharMotionDataNumGet(character, 3), 0, 0);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(character, 0xE), 0, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(character, 0x22), 0, 0);
    MgPlayerMotLoad(object, 0x1E, CharMotionDataNumGet(character, 0x20), 2, 0);
    MgPlayerMotLoad(object, 0x1F, CharMotionDataNumGet(character, 0x21), 2, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
    MgPlayerMotLoad(object, 0xF, CharMotionDataNumGet(character, 0x38), 1, 0x64);
    switch (model >> 16) {
        case 2:
        case 5:
        case 7:
            MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x39), 1, 0x3C);
            break;
        case 3:
        case 4:
        case 6:
        case 8:
        case 9:
            MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x3A), 1, 0x3C);
            break;
    }
    MgPlayerMotLoad(object, 0x26, CharMotionDataNumGet(character, 0x8D), 1, 0);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(character, 0x8E), 0, 0);
    MgPlayerMotSet(object, 0);
    m226_playerSlotNo++;
}

void m226_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
    MgPlayerWork *data;
    s32 i;
    u32 character;
    f32 zero;
    MgMotAttr *entry;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(MgPlayerWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(MgPlayerWork));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * 3 * sizeof(s32));

    object->model[0] = Hu3DModelRead(arg1 | arg2, tag);
    for (i = 0; i < object->mtncnt; i++) {
        object->motion[i] = -1;
    }
    for (i = 0; i < object->mtncnt; i++) {
        entry = data->unkE8;
        entry[i].unk02 = 0;
        entry[i].unk00 = 0;
    }

    data->unk57 = GwPlayer[player].pad;
    data->unk52 = 0;
    data->unkB4 = 1.0f;
    data->unkD0 = -1;
    data->unk4C = 0.5f;
    data->unkCC = 1.0f;
    zero = 0.0f;
    data->unkA4 = zero;
    data->unk9C = zero;
    data->unkA0 = zero;
    data->unk59 = player;

    data->unk3C = atan2df(-object->trans.x, -object->trans.z);
    MgPlayerRadiusSet(object, 60.0f);
    MgPlayerHeightSet(object, 150.0f);
    MgPlayerPunchRadiusSet(object, 20.0f);
    MgPlayerVelYSet(object, 1000.0f);

    character = (u32)arg1 >> 16;
    switch (character) {
        case 6:
            data->unkAC = 0.8f;
            break;
        case 5:
            data->unkAC = 0.9f;
            break;
        case 0:
        default:
            data->unkAC = 1.0f;
            break;
    }
}

void m226_PlayerObjMain(omObjData *object) {
    LockedOutCharMotions motions = m226_chrAnimTbl;
    MgPlayerWork *data;
    LockedOutPlayerWork *work;
    LockedOutKeyWork *blockWork;
    LockedOutDoor *entry;
    omObjData *block;
    Vec pos;
    u32 status;
    u16 buttons;
    u8 pad;
    s32 canGrab;
    s32 i;
    f32 angle;
    f32 radius;
    f32 time;
    s32 temp;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    canGrab = FALSE;
    if (m226_phase != 2) {
        HuPadStkY[pad] = 0;
        HuPadStkX[pad] = 0;
        HuPadBtnDown[pad] = 0;
        HuPadBtn[pad] = 0;
    }
    switch (m226_phase) {
        case 0:
            work->unk3E = 0;
            work->unk3C = 0;
            work->unk40 = 0;
            work->unk32 = 0;
            work->unk30 = 0;
            work->unk2E = 0;
            work->unk2C = 0;
            work->unk28 = 0;
            break;
        case 1:
            break;
        case 2:
            if (work->unk27 != 0 && work->unk3C == 0) {
                HuPadStkY[pad] = 0;
                HuPadStkX[pad] = 0;
                HuPadBtnDown[pad] = 0;
                HuPadBtn[pad] = 0;
                m226_PlayerComInput(object);
            }
            break;
        case 3:
            if (work->unk25 != 0) {
                canGrab = TRUE;
            }
            if (work->unk23 == 0) {
                MgPlayerMotSet(object, 0xF);
            }
            m226_playerSlotNo = 0;
            break;
        case 4:
            if (work->unk23 == 0 && work->unk40 == 0) {
                _HuAudPlayerFXPlay(work->unk21 + 0x287, data->unk59);
                work->unk40 = 1;
            }
            if (WipeStatGet() != 0) {
                break;
            }
            if (work->unk23 == 0) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                data->unk50 |= 0x600;
                work->unk3C = 6;
                return;
            }
            object->trans.x = m226_finalPosTbl[m226_playerSlotNo].x;
            object->trans.y = m226_finalPosTbl[m226_playerSlotNo].y;
            object->trans.z = m226_finalPosTbl[m226_playerSlotNo++].z;
            data->unk3C = 180.0f;
            data->unk40 = 0.0f;
            data->unk50 &= ~0x200;
            work->unk23 = 0;
            work->unk3E = 0;
            work->unk3C = 0;
            work->unk32 = 0;
            work->unk30 = 0;
            work->unk2E = 0;
            work->unk2C = 0;
            work->unk28 = 0;
            break;
        case 5:
            data->unk3C = 180.0f;
            break;
        case 6:
            if (work->unk23 != 0) {
                if (work->unk40 == 0) {
                    work->unk40 = 1;
                    _HuAudPlayerFXPlay(0x3D7, data->unk59);
                }
                Hu3DMotionSpeedSet(m226_doorTbl[work->unk3E].unk0E, 1.0f);
                m226_doorTbl[work->unk3E].unk0C = 1;
                data->unk3C = 0.0f;
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
            }
            if (work->unk3C != 6) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                temp = object->model[0];
                object->model[0] = object->model[9];
                object->model[9] = temp;
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                MgPlayerMotSet(object, 0);
            }
            work->unk3C = 6;
            break;
        case 7:
            if (work->unk23 == 1) {
                HuAudCharVoicePlay(work->unk1C);
                GwPlayer[data->unk59].bonusCoin += 10;
                GwPlayer[data->unk59].bonusCoin = work->unk24;
                MgPlayerMotSet(object, 0xD);
                CharAnimSet(object->model[0], 2, motions.values[work->unk21], work->unk29);
                work->unk23++;
            } else if (work->unk23 == 0) {
                GwPlayer[data->unk59].bonusCoin = work->unk24;
                work->unk23--;
            }
            break;
        case 8:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 9:
            return;
    }

    buttons = HuPadBtnDown[pad];
    status = MgPlayerMotStatGet(object);
    work->unk0C.x = object->trans.x;
    work->unk0C.y = object->trans.y;
    work->unk0C.z = object->trans.z;
    if (work->unk25 != 0) {
        HuPadBtnDown[pad] &= ~B_BUTTON;
    } else {
        Hu3DData[object->model[0]].motIdShape = 0xFF;
    }
    entry = &m226_doorTbl[work->unk3E];
    switch (work->unk3C) {
        case 0:
            if (status & 0x200000) {
                HuPadStkY[pad] = 0;
                HuPadStkX[pad] = 0;
                HuPadBtnDown[pad] = 0;
                HuPadBtn[pad] = 0;
                data->unk40 = 0.0f;
                time = Hu3DData[object->model[0]].motTime;
                if (time >= Hu3DMotion[Hu3DData[object->model[0]].motId].unk02) {
                    work->unk26 = 0;
                    if (work->unk25 != 0) {
                        Hu3DMotionShapeSet(object->model[0], object->motion[0x26], 0);
                    }
                } else if (work->unk25 == 0) {
                    if (__builtin_fabs(time - 15.0) <= 1.0) {
                        canGrab = TRUE;
                    }
                }
            } else {
                work->unk26 = 0;
            }
            if (buttons & A_BUTTON) {
                if (work->unk25 == 0) {
                    if (work->unk26 == 0 && MgPlayerMotSet(object, 0x27)) {
                        Hu3DMotionTimeSet(object->model[0], 0.0f);
                        work->unk26 = 1;
                    }
                } else {
                    canGrab = TRUE;
                }
            }
            if ((status & 0x8000) && work->unk25 != 0) {
                canGrab = TRUE;
            }
            MgPlayerObjMain(object);
            if (work->unk25 != 0) {
                for (i = 0; i < 3; i++) {
                    if (m226_doorTbl[i].unk10 == 0) {
                        continue;
                    }
                    block = m226_keyObjTbl[work->unk25 - 1];
                    blockWork = block->data;
                    if (blockWork->unk02 != m226_keyType) {
                        continue;
                    }
                    if (m226_DistXZCalc(&object->trans, &m226_doorTbl[i].pos) >
                        data->unk48 + 20.0) {
                        continue;
                    }
                    Hu3DModelAttrSet(m226_doorTbl[i].unk0E, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(m226_doorTbl[i].unk0D, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(m226_doorTbl[i].unk0E, m226_doorTbl[i].pos.x,
                                    m226_doorTbl[i].pos.y, m226_doorTbl[i].pos.z);
                    canGrab = TRUE;
                    Hu3DMotionSpeedSet(m226_doorTbl[i].unk0F, 1.0f);
                    Hu3DModelAttrSet(m226_doorTbl[i].unk0F, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(m226_doorTbl[i].unk0F, m226_doorTbl[i].pos.x,
                                    m226_doorTbl[i].pos.y + 200.0, m226_doorTbl[i].pos.z);
                    _HuAudPlayerFXPlay(0x3D9, 4);
                    m226_doorTbl[i].unk10 = 0;
                    work->unk23 = 1;
                    work->unk3C = 1;
                    work->unk3E = i;
                    data->unk50 |= 0x200;
                    Hu3DModelAttrSet(block->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    blockWork->unk00 = 4;
                }
            }
            m226_KeyGrabUpdate(object, TRUE, canGrab);
            m226_DoorPush(object);

            pos.x = -610.5f;
            pos.y = 0.0f;
            pos.z = -607.0f;
            if (m226_DistXZCalc(&pos, &object->trans) <= data->unk48 + 90.0) {
                angle = m226_AngleCalc(pos.x - object->trans.x, pos.z - object->trans.z);
                object->trans.x = pos.x - (data->unk48 + 90.0) * sindf(angle);
                object->trans.z = pos.z - (data->unk48 + 90.0) * cosdf(angle);
            }

            pos.x = 610.5f;
            pos.y = 0.0f;
            pos.z = -607.0f;
            if (m226_DistXZCalc(&pos, &object->trans) <= data->unk48 + 80.0) {
                angle = m226_AngleCalc(pos.x - object->trans.x, pos.z - object->trans.z);
                object->trans.x = pos.x - (data->unk48 + 90.0) * sindf(angle);
                object->trans.z = pos.z - (data->unk48 + 90.0) * cosdf(angle);
            }
            break;
        case 1:
            MgPlayerMotSet(object, 1);
            data->unk3C = 180.0f;
            angle = m226_AngleCalc(object->trans.x - (entry->pos.x + data->unk48 * 1.75),
                                             object->trans.z - (entry->pos.z + data->unk48 * 1.4));
            object->trans.x = work->unk0C.x - sindf(angle) * 4.0;
            object->trans.z = work->unk0C.z - cosdf(angle) * 4.0;
            pos.x = entry->pos.x + data->unk48 * 1.75;
            pos.y = entry->pos.y;
            pos.z = entry->pos.z + data->unk48 * 1.4;
            if (m226_DistXZCalc(&object->trans, &pos) < 5.0) {
                Hu3DMotionSpeedSet(entry->unk0E, 0.5f);
                _HuAudPlayerFXPlay(0x3D7, data->unk59);
                entry->unk0C = 1;
                data->unk3C = 180.0f;
                work->unk3C++;
            }
            break;
        case 2:
            if (data->unk3C < 250.0) {
                data->unk3C += 6.0;
            } else {
                MgPlayerMotSet(object, 0);
            }
            if (Hu3DData[entry->unk0E].motTime >= Hu3DMotion[Hu3DData[entry->unk0E].motId].unk02) {
                work->unk3C++;
                work->unk40 = 30;
            }
            break;
        case 3:
            MgPlayerMotSet(object, 1);
            if (data->unk3C > 180.0) {
                data->unk3C += -3.0;
            }
            angle = data->unk3C;
            if (work->unk21 == 4 || work->unk21 == 5) {
                radius = 10.2f;
            } else {
                radius = 6.8f;
            }
            object->trans.x = radius * sindf(angle) + work->unk0C.x;
            object->trans.z = radius * cosdf(angle) + work->unk0C.z;
            if (--work->unk40 == 0) {
                _HuAudPlayerFXPlay(0x3D8, data->unk59);
                work->unk3C++;
            }
            break;
        case 4:
            Hu3DMotionSpeedSet(entry->unk0E, 0.0f);
            Hu3DMotionTimeSet(entry->unk0E, Hu3DData[entry->unk0E].motTime - 1.5);
            if (Hu3DData[entry->unk0E].motTime < 0.0) {
                Hu3DMotionTimeSet(entry->unk0E, 0.0f);
                omVibrate(data->unk59, 2, 3, 10);
                entry->unk0C = 0;
                work->unk3C++;
            }
            break;
        case 5:
            return;
        case 6:
            if (work->unk23 == 0) {
                m226_KeyGrabUpdate(object, TRUE, canGrab);
                m226_DoorPush(object);
            }
            break;
    }
    work->unk18 = status;
    if (work->unk3C != 0) {
        HuRotateRPYF(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
        MgPlayerMotUpdate(object);
        MgPlayerScaleUpdate(object);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
}

void m226_SplashEffSet(omObjData *object, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (Hu3DData[object->model[i]].attr & 4) {
            MgPlayerEffSet(object, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

u16 m226_PlayerComInput(omObjData *object) {
    HuMtx4F unused; // Unused, but required for the stack layout to match.
    MgPlayerWork *data;
    LockedOutPlayerWork *work;
    LockedOutKeyWork *blockWork;
    LockedOutDoor *entry;
    omObjData *block;
    omObjData *holder;
    s16 pad;
    u8 index;
    s32 i;
    f32 angle;
    u16 buttons; // Never assigned; the original returns an uninitialized value.

    m226_PlayerWorkGet(object, &data, &work);
    pad = data->unk57;
    MgPlayerMotStatGet(object);
    switch (work->unk28) {
        case 0:
            if (work->unk25 != 0) {
                HuPadBtnDown[pad] |= A_BUTTON;
            }
            work->unk2C = 0;
            work->unk2E = 0;
            index = (s32)((f32)m226_Rand16Get() * 1.52587890625e-05 * m226_keyNum);
            block = m226_keyObjTbl[index];
            blockWork = block->data;
            if (blockWork->unk02 != m226_keyType) {
                if ((s32)((f32)m226_Rand16Get() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
                    break;
                }
                work->unk2E = 1;
            }
            work->unk2C = index;
            work->unk28++;
            break;
        case 1:
            block = m226_keyObjTbl[work->unk2C];
            blockWork = block->data;
            if (work->unk25 != 0) {
                work->unk28 = 2;
                break;
            }
            if (blockWork->unk00 == 1) {
                holder = blockWork->unk14;
                angle = m226_AngleCalc(holder->trans.x - object->trans.x, holder->trans.z - object->trans.z);
                if (m226_DistXZCalc(&object->trans, &holder->trans) < data->unk48 * 2.2 + data->unk64) {
                    HuPadBtnDown[pad] |= B_BUTTON;
                }
                for (i = 0; i < m226_keyCreateCnt; i++) {
                    blockWork = m226_keyObjTbl[i]->data;
                    if (blockWork->unk02 == m226_keyType && blockWork->unk00 == 0) {
                        break;
                    }
                }
                if (i < m226_keyCreateCnt) {
                    if ((s32)((f32)m226_Rand16Get() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
                        work->unk28 = 0;
                    }
                }
            } else if (blockWork->unk00 == 4) {
                work->unk28 = 0;
                break;
            } else {
                angle = m226_AngleCalc(block->trans.x - object->trans.x, block->trans.z - object->trans.z);
                if (m226_DistXZCalc(&object->trans, &block->trans) <= data->unk48 + blockWork->unk04 + 2.0 &&
                    __builtin_fabs((f64)(angle - data->unk3C)) < 40.0) {
                    HuPadBtnDown[pad] |= A_BUTTON;
                }
            }
            HuPadStkX[pad] = (work->unk22 * 6.0 + 46.0) * sindf(angle);
            HuPadStkY[pad] = (work->unk22 * 6.0 + 46.0) * -cosdf(angle);
            break;
        case 2:
            if (work->unk25 != work->unk2C + 1) {
                HuPadBtnDown[pad] |= A_BUTTON;
                work->unk28 = 1;
                break;
            }
            work->unk30 = (s32)((f32)m226_Rand16Get() * 1.52587890625e-05 * (s16)(m226_keyNum / 3));
            if (m226_doorTbl[work->unk30].unk10 == 0) {
                break;
            }
            work->unk28++;
        case 3:
            if (work->unk25 == 0) {
                work->unk28 = 1;
            }
            entry = &m226_doorTbl[work->unk30];
            if (entry->unk10 == 0) {
                work->unk28 = 2;
            }
            angle = m226_AngleCalc(entry->pos.x - object->trans.x, entry->pos.z - object->trans.z);
            HuPadStkX[pad] = (work->unk22 * 6.0 + 46.0) * sindf(angle);
            HuPadStkY[pad] = (work->unk22 * 6.0 + 46.0) * -cosdf(angle);
            break;
        case 4:
            break;
    }
    if (work->unk2E != 0) {
        if ((s32)((f32)m226_Rand16Get() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
            work->unk28 = 0;
        }
    }
    return buttons;
}

void m226_PlayerWorkGet(omObjData *object, MgPlayerWork **data, LockedOutPlayerWork **arg2) {
    *data = object->data;
    *arg2 = (*data)->unk158;
}

void m226_KeyObjCreateAll(void) {
    s32 i;
    s16 j;
    u8 temp;

    for (i = 0; i < m226_keyNum; i++) {
        m226_keyObjTbl[i] = omAddObj(3, 5, 5, -1, m226_KeyObjInit);
    }
    for (i = 0; i < m226_keyNum; i++) {
        m226_keyOrderTbl[i] = i;
    }
    for (i = m226_keyNum; i > 0; i--) {
        j = (f32)m226_Rand16Get() * 1.52587890625e-05 * i;
        temp = m226_keyOrderTbl[i - 1];
        m226_keyOrderTbl[i - 1] = m226_keyOrderTbl[j];
        m226_keyOrderTbl[j] = temp;
    }
}

void m226_KeyObjInit(omObjData *object) {
    Vec positions[9] = {
        { 50.0f, 50.0f, 60.0f },
        { -50.0f, 50.0f, -60.0f },
        { 150.0f, 50.0f, -60.0f },
        { -150.0f, 50.0f, 60.0f },
        { 250.0f, 50.0f, 60.0f },
        { -250.0f, 50.0f, -60.0f },
        { 350.0f, 50.0f, -60.0f },
        { -350.0f, 50.0f, 60.0f },
        { 450.0f, 50.0f, 60.0f },
    };
    LockedOutKeyWork *work;

    work = HuMemAllocTag(sizeof(LockedOutKeyWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(LockedOutKeyWork));
    work->unk00 = 0;
    work->unk02 = m226_keyCreateCnt % 3;
    work->unk04 = 20.0f;
    work->unk14 = 0;
    work->unk01 = 0;
    object->model[0] = Hu3DModelRead((work->unk02 + 7) | 0x3B0000, 0x2D9);
    object->model[1] = Hu3DModelRead3(9, 0x2D9);
    Hu3DModelScaleSet(object->model[1], 0.75f, 0.75f, 0.75f);
    object->trans.x = positions[m226_keyOrderTbl[m226_keyCreateCnt]].x;
    object->trans.y = positions[m226_keyOrderTbl[m226_keyCreateCnt]].y;
    object->trans.z = positions[m226_keyOrderTbl[m226_keyCreateCnt]].z;
    object->rot.x = -90.0f;
    object->func = m226_KeyObjMain;
    m226_keyCreateCnt++;
}

void m226_KeyObjMain(omObjData *object) {
    LockedOutKeyWork *work;
    Vec pos;
    f32 angle;

    work = object->data;
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    switch (work->unk00) {
        case 0:
            work->unk01 = 1;
            break;
        case 2:
            work->unk01 = 0;
            work->unk03--;
            if (work->unk03 == 0) {
                work->unk00 = 3;
            }
        case 3:
            work->unk01 = 1;
            work->unk08.y += -2.0f;
            object->trans.x += work->unk08.x;
            object->trans.y += work->unk08.y;
            object->trans.z += work->unk08.z;
            if (object->trans.y < 50.0) {
                work->unk00 = 0;
                object->trans.y = 50.0f;
                work->unk08.y = 6.0f;
            }
            break;
        case 1:
        case 4:
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            work->unk01 = 0;
            break;
    }

    pos.x = -610.5f;
    pos.y = 0.0f;
    pos.z = -607.0f;
    if (m226_DistXZCalc(&pos, &object->trans) <= work->unk04 + 90.0) {
        angle = m226_AngleCalc(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - (work->unk04 + 90.0) * sindf(angle);
        object->trans.z = pos.z - (work->unk04 + 90.0) * cosdf(angle);
    }

    pos.x = 610.5f;
    pos.y = 0.0f;
    pos.z = -607.0f;
    if (m226_DistXZCalc(&pos, &object->trans) <= work->unk04 + 80.0) {
        angle = m226_AngleCalc(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - (work->unk04 + 90.0) * sindf(angle);
        object->trans.z = pos.z - (work->unk04 + 90.0) * cosdf(angle);
    }

    if (object->trans.x < -600.0) {
        object->trans.x = -600.0f;
    }
    if (object->trans.x > 600.0) {
        object->trans.x = 600.0f;
    }
    if (object->trans.z < -575.0) {
        object->trans.z = -575.0f;
    }
    if (object->trans.z > 575.0) {
        object->trans.z = 575.0f;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    m226_KeyGrabUpdate(object, 0, 0);
    m226_DoorPush(object);
}

void m226_KeyGrabUpdate(omObjData *object, u8 isPlayer, u8 canGrab) {
    MgPlayerWork *data;
    LockedOutPlayerWork *playerWork;
    LockedOutKeyWork *selfWork;
    LockedOutKeyWork *work;
    omObjData *block;
    Vec hookPos;
    f32 radius;
    f32 dist;
    f32 angle;
    f32 pushAngle;
    s32 i;

    selfWork = NULL;
    if (m226_keyCreateCnt == 0) {
        return;
    }
    if (isPlayer) {
        m226_PlayerWorkGet(object, &data, &playerWork);
        radius = data->unk48;
    } else {
        selfWork = object->data;
        radius = selfWork->unk04;
        canGrab = FALSE;
    }

    if (canGrab && playerWork->unk25 != 0) {
        block = m226_keyObjTbl[playerWork->unk25 - 1];
        work = block->data;
        Hu3DModelAttrSet(block->model[0], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
        work->unk08.x = sindf(data->unk3C) * 4.0;
        work->unk08.y = 15.0f;
        work->unk08.z = cosdf(data->unk3C) * 4.0;
        m226_HookPosGet(object->model[0], "item_hook", Hu3DData[object->model[0]].motTime, &hookPos);
        block->trans.x = work->unk08.x * 20.0f + hookPos.x;
        block->trans.y = hookPos.y + 50.0;
        block->trans.z = work->unk08.z * 20.0f + hookPos.z;
        playerWork->unk25 = 0;
        if (work->unk00 != 4) {
            work->unk00 = 2;
        }
        work->unk01 = 0;
        work->unk03 = 5;
        canGrab = FALSE;
    }

    for (i = 0; i < m226_keyNum; i++) {
        block = m226_keyObjTbl[i];
        work = block->data;
        if (work == selfWork) {
            continue;
        }
        dist = m226_DistXZCalc(&object->trans, &block->trans);
        if (!(dist < radius + work->unk04 + 24.0)) {
            continue;
        }
        angle = m226_AngleCalc(block->trans.x - object->trans.x, block->trans.z - object->trans.z);
        if (dist < radius + work->unk04 && (work->unk00 != 1 || work->unk00 != 4)) {
            pushAngle = m226_AngleCalc(object->trans.x - block->trans.x, object->trans.z - block->trans.z);
            block->trans.x = object->trans.x - (radius + work->unk04) * sindf(pushAngle);
            block->trans.z = object->trans.z - (radius + work->unk04) * cosdf(pushAngle);
        }
        if (!canGrab || playerWork->unk25 != 0 || work->unk01 == 0) {
            continue;
        }
        angle -= data->unk3C;
        while (angle < -180.0) {
            angle += 360.0;
        }
        while (angle > 180.0) {
            angle -= 360.0;
        }
        if (__builtin_fabs((f64)angle) < 45.0) {
            Hu3DModelHookSet(block->model[0], object->model[0], "item_hook");
            Hu3DModelAttrSet(block->model[0], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
            _HuAudPlayerFXPlay(0x3D6, data->unk59);
            playerWork->unk25 = i + 1;
            work->unk00 = 1;
            work->unk01 = 0;
            work->unk14 = object;
        }
    }
}

void m226_KeyKillAll(void) {
    omObjData *object;
    s32 i;

    for (i = 0; i < m226_keyNum; i++) {
        object = m226_keyObjTbl[i];
        Hu3DModelKill(object->model[0]);
        Hu3DModelKill(object->model[1]);
        HuMemFree(object->data);
        object->data = NULL;
        omDelObj(object);
    }
}

s32 m226_Rand16Get(void) {
    m226_randSeed = (m226_randSeed + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return m226_randSeed >> 16;
}

f32 m226_AngleCalc(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < -180.0f) {
        angle += fullCircle;
    } else if (angle >= 180.0) {
        angle -= fullCircle;
    }
    return angle;
}

f32 m226_DistXZCalc(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void m226_HookPosGet(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    Hu3DModelObjMtxFrameGet(model, time, hook, &hookTransform);
    modelData = &Hu3DData[model];
    HuTranslateF(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    mtxRotCat(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    mtxScaleCat(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    mtxCat(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 m226_AnimDataRead(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    return spriteId;
}

s16 m226_SprGrpCreate(s16 spriteId, s16 count) {
    s16 groupId;
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    groupId = HuSprGrpCreate(count, 0);
    if (groupId == -1) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        HuSprGrpMemberSet(groupId, i, spriteId, 0);
    }
    return groupId;
}

HuSprAnimPat *m226_SprAnimPatGet(s16 groupId, s16 member) {
    return &HuSprAnimDataGet(groupId)->pat[member];
}
