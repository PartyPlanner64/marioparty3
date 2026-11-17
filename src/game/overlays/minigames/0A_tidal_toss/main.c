// The original source called fmod without a prototype in scope, so its result is read as an int.
// Hide the math.h prototype so that fmod can be declared here the way the compiler saw it.
#define fmod fmod_math_h
#include "common.h"
#undef fmod
#include "game/overlays/minigame.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"

#define TIDAL_TOSS_WORK(obj) ((TidalTossWork *)((MgPlayerWork *)(obj)->data)->unk158)

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    u8 unk10;
} TidalTossWave;

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[0xAF];
} TidalTossSetupWork;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    u16 unk28;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u16 unk32;
    u16 unk34;
    u16 unk36;
    u16 unk38;
    u8 unk3A[0xA];
    f32 unk44;
    f32 unk48;
    f32 unk4C;
} TidalTossWork;

typedef struct TidalTossSortEntry {
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    f32 depth;
    struct TidalTossSortEntry *prev;
    struct TidalTossSortEntry *next;
} TidalTossSortEntry;

typedef struct {
    s16 count;
    s16 indices[4];
    char unk0A[0xA];
} TidalTossFace;

typedef struct {
    s16 unk00;
    s16 unk02;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} TidalTossCloudWork;

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];
extern u8 Hu3DBufNo;

u8 m210_soloNo = 0;
s16 m210_cloudPosTbl[3][2] = { { 55, 30 }, { 198, 38 }, { 294, 24 } };
f32 m210_cloudScaleTbl[3] = { 1.0f, 0.8f, 1.2f };
s32 m210_phaseTimer = 0;
u16 m210_timer = 0;
s32 m210_winner = -1;
s16 m210_winnerPad[2] = { 180, 0 }; /* Unreferenced. */
u8 m210_seaVtxLimitTbl[8] = { 0x1C, 0x1C, 0x3C, 0x3C, 0x1C, 0x1C, 0x1C, 0x3C };
s32 m210_seaGfxReadyF = 0;
s32 m210_seaGfxBuildStep = 0;
f32 m210_seaTexScroll = 0.0f;
u8 m210_playerSlotTbl[4][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } };
u8 m210_playerSlotNo = 0;
u8 m210_teamSlotNo = 0;
f32 m210_playerPosTbl[4][3] = {
    { 0.0f, 20.0f, -20.0f },
    { -240.0f, 0.0f, 0.0f },
    { 240.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 240.0f },
};
f32 m210_playerRotTbl[4] = { 0.0f, 90.0f, -90.0f, 180.0f };
u32 m210_randSeed = 0x41C64E6D;

s16 m210_musicDelay BSS;
Mtx m210_seaMtx[3] BSS;
TidalTossSortEntry *m210_seaSortTbl BSS;
Vtx *m210_seaVtxBuf BSS;
MinigameFlow m210_mgFlow BSS;
s16 m210_backAnim BSS;
s16 m210_cloudAnim BSS;
u8 m210_cloudAnimPad[12] BSS; /* Unreferenced. */
s16 m210_backSpr BSS;
s16 m210_backSprPad BSS; /* Unreferenced. */
s16 m210_cloudSpr BSS;
s16 m210_cloudSprPad BSS;      /* Unreferenced. */
u8 m210_cloudSprPadB[0x48] BSS; /* Unreferenced. */
s16 m210_seaMdl BSS;
s16 m210_seaTexAnim BSS;
Gfx *m210_seaGfx BSS;
s16 m210_phase BSS;
s16 m210_phasePad BSS; /* Unreferenced. */
s32 m210_phasePadB BSS; /* Unreferenced. */
TidalTossWave m210_waveTbl[8] BSS;
TidalTossCloudWork m210_cloudWorkTbl[3] BSS;
s32 m210_cloudWorkTblPad BSS; /* Unreferenced. */
f32 m210_cameraMtx[4][4] BSS;
f32 m210_cameraInvMtx[4][4] BSS;
f32 m210_cameraFovTan BSS;

s32 fmod(f64 x, f64 y);
void m210_PlayerObjInit(omObjData *);
void m210_CameraViewInit(omObjData *object);
void m210_MapObjCreateAll(void);
void m210_PlayerObjCreateAll(void);
void m210_MainObjInit(omObjData *);
void m210_IslandMapObjInit(omObjData *);
void m210_DeepMapObjInit(omObjData *);
void m210_MainObjMain(omObjData *);
void m210_SeaDraw(Gfx **, s32, s32);
s32 m210_Rand16Get(void);
u16 m210_SoloComInput(omObjData *);
void m210_PlayerWorkGet(omObjData *, MgPlayerWork **, TidalTossWork **);
void m210_MtxInvert(HuMtx4F, HuMtx4F);
s16 m210_AnimDataRead(s32);
s16 m210_SprGrpCreate(s16, s16);
HuSprAnimPat *m210_SprAnimPatGet(s16 arg0, s16 arg1);
void m210_TeamObjMain(omObjData *);
u16 m210_TeamComInput(omObjData *arg0, f32 arg1);
f32 m210_DistXZCalc(Vec *arg0, Vec *arg1);
f32 m210_AngleCalc(f32 arg0, f32 arg1);
void m210_SoloObjMain(omObjData *);

void m210_ObjectSetup(void) {
    omObjData *obj;
    u8 camIndex;

    MapCollInit(3);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    omInitObjMan(0x10, 0);
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 8000.0f);
    MgFieldStatClear();
    m210_CameraViewInit(obj);
    m210_MapObjCreateAll();
    memset(&m210_mgFlow, 0, 0x28);
    m210_mgFlow.type = MINIGAME_BATTLE;
    MgFlowInit(&m210_mgFlow);
    m210_PlayerObjCreateAll();
}

void m210_CameraViewInit(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 1600.0f;
    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    m210_cameraFovTan = sinFov / cosFov;
    guMtxL2F(m210_cameraMtx, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(m210_cameraInvMtx, &camera->mtxs[0].lookAtMtx);
    m210_MtxInvert(m210_cameraInvMtx, m210_cameraInvMtx);
}

void m210_MtxVecMul(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void m210_MtxInvert(HuMtx4F src, HuMtx4F dst) {
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

        m210_MtxVecMul(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void m210_ScreenPosCalc(f32 *arg0, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, arg0[0], arg0[1], arg0[2]);
    guMtxCatF(mtx, m210_cameraMtx, mtx);
    depth = mtx[3][2] * m210_cameraFovTan;
    scale = __builtin_fabsf(depth);
    if (scale == 0.0) {
        return;
    }
    dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
    dst[1] = -mtx[3][1] * 120.0f / scale;
}

void m210_WorldPosCalc(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + m210_cameraMtx[3][2];
    f32 scale = __builtin_fabsf(depth * m210_cameraFovTan);
    f32 mtx[4][4];

    guTranslateF(mtx, ((x + x) * scale * 1.3333334f) / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, m210_cameraInvMtx, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void m210_MapObjCreateAll(void) {
    mgMapObjNum = 0;
    MgMapBaseSet(0);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m210_MainObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m210_IslandMapObjInit);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(5, 1, 0, -1, m210_DeepMapObjInit);
    m210_phase = 0;
}

void m210_MainObjInit(omObjData *object) {
    TidalTossSetupWork *work;
    TidalTossWave *entry;
    TidalTossCloudWork *spriteWork;
    s16 *spriteGroup;
    s16 *setupSpriteGroup;
    s16 setupSpriteId;
    s16 model;
    f32 zero;
    f32 scale;
    s32 i;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, 10.0f);
    MgMapCircleSet(object, 0.0f, 730.0f);

    m210_backAnim = m210_AnimDataRead(0x2B0000);
    setupSpriteId = m210_SprGrpCreate(m210_backAnim, 1);
    setupSpriteGroup = &m210_backSpr;
    *setupSpriteGroup = setupSpriteId;
    HuSprPosSet(*setupSpriteGroup, 0, 160, 120);
    HuSprAttrSet(*setupSpriteGroup, 0, HUSPR_ATTR_BG);

    model = Hu3DModelRead(0x2B0003, 0x4002CD);
    object->model[0] = model;
    m210_seaMdl = model;
    Hu3DModelVtxBufMake(object->model[0]);
    object->model[1] = Hu3DModelRead(0x2B0004, 0x2D9);
    object->model[2] = Hu3DHookFuncCreate(0x80, m210_SeaDraw, 2);
    m210_seaTexAnim = m210_AnimDataRead(0x2B0001);

    entry = m210_waveTbl;
    zero = 0.0f;
    for (i = 0; i < 8; i++) {
        entry->unk10 = 0;
        entry->unk0C = zero;
        entry->unk08 = zero;
        entry->unk04 = zero;
        entry->unk00 = zero;
        entry++;
    }

    m210_cloudAnim = m210_AnimDataRead(0x2B0002);
    m210_cloudSpr = m210_SprGrpCreate(m210_cloudAnim, 3);
    spriteWork = m210_cloudWorkTbl;
    for (i = 0; i < 3; i++) {
        spriteWork->unk04 = (f32)m210_cloudPosTbl[i][0];
        spriteWork->unk00 = spriteWork->unk04;
        spriteWork->unk08 = (f32)m210_cloudPosTbl[i][1];
        spriteWork->unk02 = spriteWork->unk08;
        scale = m210_cloudScaleTbl[i];
        spriteWork->unk10 = scale;
        spriteWork->unk0C = scale;
        spriteWork->unk14 = (f32)((f64)(f32)m210_Rand16Get() * 1.52587890625e-05 * 360.0);
        spriteWork->unk18 = (f32)((f64)(f32)m210_Rand16Get() * 1.52587890625e-05 * 360.0);
        spriteWork->unk1C = (f32)((f64)(f32)m210_Rand16Get() * 1.52587890625e-05 * 2.0 + 2.0);
        spriteWork->unk20 = (f32)((f64)(f32)m210_Rand16Get() * 1.52587890625e-05 * 1.5 + 1.0);
        spriteGroup = &m210_cloudSpr;
        HuSprAttrSet(*spriteGroup, (s16)i, HUSPR_ATTR_VTX | HUSPR_ATTR_BG | HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_BILERP);
        HuSprPosSet(*spriteGroup, (s16)i, spriteWork->unk00, spriteWork->unk02);
        spriteWork++;
    }

    object->func = m210_MainObjMain;
}

void m210_IslandMapObjInit(omObjData *object) {
    TidalTossSetupWork *work;

    work = HuMemAllocTag(sizeof(TidalTossSetupWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(TidalTossSetupWork));
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 5.0f);
    MgMapAccelSet(object, 10.0f);
    MgMapCircleSet(object, 20.0f, 345.0f);
    object->func = NULL;
}

void m210_DeepMapObjInit(omObjData *object) {
    TidalTossSetupWork *work;

    work = HuMemAllocTag(sizeof(TidalTossSetupWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(TidalTossSetupWork));
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.05f);
    MgMapAccelSet(object, 20.0f);
    MgMapCircleSet(object, -800.0f, 1380.0f);
    object->func = NULL;
}

void m210_MainObjMain(omObjData *object) {
    s8 chars[4];
    TidalTossWave *entry;
    TidalTossCloudWork *spriteWork;
    HuSprite *sprite;
    s16 *spriteGroup;
    s32 i;
    s32 active;
    s32 count;

    switch (m210_phase) {
        case 0:
            Hu3DBGColorSet(0, 0, 0);
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            GMesCreate(GMES_MES_4);
            HuAudFXPlay(0x42E);
            m210_phaseTimer = 45;
            m210_timer = 900;
            m210_phase++;
            m210_musicDelay = 60;
            // fallthrough
        case 1:
            if (--m210_musicDelay == -1) {
                HuAudSeqPlay(0x2F);
            }
            if (--m210_phaseTimer == -1) {
                HuAudFXAllFadeOut(45);
            }
            if (GMesStatGet() == 0) {
                MgFlowStatSet(MG_STATE_PLAY);
                m210_phase++;
                GMesCreate(GMES_MES_TIMER, (m210_timer + 29) / 30, 160, 32);
                HuAudFXPlay(0xE);
            }
            break;
        case 2:
            active = 0;
            for (i = 0; i < 4; i++) {
                if (i != m210_soloNo) {
                    active += TIDAL_TOSS_WORK(mgPlayerObjTbl[i])->unk2F;
                }
            }
            if (active == 0) {
                m210_winner = m210_soloNo;
                m210_phase = 3;
            }
            m210_timer--;
            GMesTimerValueSet((m210_timer + 29) / 30);
            if (m210_timer == 0) {
                m210_phase = 3;
            }
            break;
        case 3:
            if (m210_winner == m210_soloNo) {
                TIDAL_TOSS_WORK(mgPlayerObjTbl[m210_winner])->unk2F = 1;
            } else {
                for (i = 0; i < 4; i++) {
                    if (i != m210_soloNo) {
                        TIDAL_TOSS_WORK(mgPlayerObjTbl[i])->unk2F = 1;
                    }
                }
            }
            GMesTimerEnd();
            GMesCreate(GMES_MES_15);
            HuAudSeqFadeOut(120);
            m210_phase++;
            m210_phaseTimer = 15;
            break;
        case 4:
            if (GMesStatGet() == 0) {
                if (--m210_phaseTimer == 0) {
                    if (m210_winner == m210_soloNo) {
                        GMesCreate(GMES_MES_MG_WINNER, TIDAL_TOSS_WORK(mgPlayerObjTbl[m210_winner])->unk2C);
                        HuAudSeqPlay(0x65);
                    } else {
                        for (i = 0, count = 0; i < 4; i++) {
                            if (i != m210_soloNo) {
                                chars[count] = TIDAL_TOSS_WORK(mgPlayerObjTbl[i])->unk2C;
                                count++;
                            }
                        }
                        GMesCreate(GMES_MES_MG_WINNERS_3, chars[0], chars[1], chars[2]);
                        HuAudSeqPlay(0x66);
                    }
                    m210_phaseTimer = 15;
                    m210_phase++;
                    MgFlowStatSet(MG_STATE_RESULT);
                }
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                if (--m210_phaseTimer == 0) {
                    m210_phase++;
                }
            }
            break;
        case 6:
            if (m210_phaseTimer != 0) {
                if (--m210_phaseTimer == 0) {
                    m210_phase++;
                }
            } else {
                MgFlowStatSet(MG_STATE_EXIT);
                m210_phaseTimer = 16;
                WipeCreateOut(WIPE_TYPE_NORMAL, m210_phaseTimer);
                HuAudSeqFadeOut(m210_phaseTimer);
                HuAudFXAllFadeOut((s16)m210_phaseTimer);
            }
            break;
        case 7:
            HuMemFree(m210_seaGfx);
            HuAudSeqStop();
            omOvlReturnEx(1);
            break;
    }

    entry = m210_waveTbl;
    for (i = 0; i < 8; i++) {
        if (entry->unk10 != 0) {
            entry->unk00 += entry->unk08;
            if (entry->unk00 >= 900.0) {
                entry->unk10 = 0;
                entry->unk00 = 0.0f;
            }
            if (entry->unk00 >= 160.0) {
                entry->unk08 = (1.15 - entry->unk10 * 0.15) * 20.0;
            }
        }
        entry++;
    }

    spriteWork = m210_cloudWorkTbl;
    for (i = 0; i < 3; i++) {
        spriteWork->unk04 = spriteWork->unk00 + sindf(spriteWork->unk14) * 8.0;
        spriteWork->unk08 = spriteWork->unk02 + sindf(spriteWork->unk18) * 6.0;
        spriteWork->unk14 += spriteWork->unk0C;
        if (spriteWork->unk14 >= 360.0) {
            spriteWork->unk14 -= 360.0;
        }
        spriteWork->unk18 += spriteWork->unk10;
        if (spriteWork->unk18 >= 360.0) {
            spriteWork->unk18 -= 360.0;
        }
        spriteGroup = &m210_cloudSpr;
        sprite = HuSprGet(*spriteGroup, i);
        sprite->pos.x = spriteWork->unk04;
        sprite->pos.y = spriteWork->unk08;
        HuSprScaleSet(*spriteGroup, i, spriteWork->unk0C + sindf(spriteWork->unk14 * 6.0) * 0.1,
                      spriteWork->unk10 - sindf(spriteWork->unk14 * 6.0) * 0.1);
        spriteWork++;
    }

    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m210_phase = 6;
        m210_phaseTimer = 0;
    }
}

void m210_SeaDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HuMtx4F modelMtx;
    HuMtx4F mtx;
    Vtx_t saved;
    TidalTossFace faces[64];
    HmfModel *model = &Hu3DData[m210_seaMdl];
    HmfData *hmf = model->hmf;
    HmfModelData_Unk64_Unk60_Struct *object = hmf->unk60;
    HmfModelData_Unk64_Unk60_Unk54_Struct *source;
    HmfData_Unk84_Entry *texture;
    TidalTossSortEntry *entry;
    TidalTossSortEntry *other;
    TidalTossFace *face;
    TidalTossWave *wave;
    HuSprAnimPat *frame;
    HuSprAnimData *anim;
    Gfx *gfx;
    Gfx *gfxStart;
    Vtx *vertex;
    Vtx *src;
    Vtx *dst;
    s16 *position;
    s8 *color;
    s32 i;
    s32 j;
    s16 vertexLimit;
    s16 count;
    s16 vertexCount;
    s16 vertexIndex;
    s16 sourceIndex;
    s16 textureWidth;
    s16 textureHeight;
    s16 unlit;
    s16 s;
    s16 t;
    s16 groupStart;
    s16 faceCount;
    s16 flush;
    s16 maxVertex;
    s16 groupSize;
    s16 gfxCount;
    f32 minDepth;
    f32 radius;
    f32 dirX;
    f32 dirZ;
    f64 dist;
    f64 diff;
    f64 absDiff;
    f64 strength;

    if (m210_seaGfxReadyF == 0) {
        switch (m210_seaGfxBuildStep) {
            case 0:
                entry = HuMemAlloc((object->unk22 + 2) * sizeof(TidalTossSortEntry));
                m210_seaSortTbl = entry;
                m210_seaVtxBuf = HuMemAlloc(hmf->unk18 * 2 * sizeof(Vtx));
                memset(m210_seaVtxBuf, 0, hmf->unk18 * 2 * sizeof(Vtx));
                m210_seaSortTbl->depth = -19980.0f;
                m210_seaSortTbl->prev = NULL;
                m210_seaSortTbl->next = &m210_seaSortTbl[object->unk22 + 1];
                m210_seaSortTbl[object->unk22 + 1].depth = 19980.0f;
                m210_seaSortTbl[object->unk22 + 1].prev = m210_seaSortTbl;
                m210_seaSortTbl[object->unk22 + 1].next = NULL;
                entry++;
                for (i = 0; i < object->unk22; i++, entry++) {
                    source = &object->unk54[i];
                    entry->face = source;
                    count = source->unk00 & 0x7F;
                    minDepth = 19980.0f;
                    for (j = 0; j < count; j++) {
                        sourceIndex = source->unk04[j];
                        position = hmf->unk50[sourceIndex];
                        if (position[2] < minDepth) {
                            minDepth = position[2];
                        }
                    }
                    entry->depth = minDepth;
                    other = m210_seaSortTbl;
                    other = other->next;
                    while (other->depth < entry->depth) {
                        other = other->next;
                    }
                    other->prev->next = entry;
                    entry->prev = other->prev;
                    entry->next = other;
                    other->prev = entry;
                }
                groupStart = 0;
                vertexCount = 0;
                vertexLimit = m210_seaVtxLimitTbl[(u32)(model->attr & HU3D_ATTR_LAYER_MASK) >> HU3D_ATTR_LAYER_SHIFT];
                entry = m210_seaSortTbl;
                for (i = 0; i < object->unk22; i++) {
                    entry = entry->next;
                    if (entry->face == NULL) {
                        continue;
                    }
                    source = entry->face;
                    count = source->unk00 & 0x7F;
                    if (source->unk00 < 3) {
                        continue;
                    }
                    if (source->unk32 >= 0) {
                        texture = &hmf->unk84[source->unk32];
                    } else {
                        texture = (HmfData_Unk84_Entry *)-1;
                    }
                    if (vertexLimit < vertexCount - groupStart) {
                        groupStart = vertexCount;
                    }
                    if (texture != (HmfData_Unk84_Entry *)-1) {
                        textureWidth = texture->unkC->unk24 << 5;
                        textureHeight = texture->unkC->unk26 << 5;
                    } else {
                        textureWidth = textureHeight = 0;
                    }
                    unlit = source->unk00 & 0x80;
                    for (j = 0; j < count; j++) {
                        sourceIndex = source->unk04[j];
                        position = hmf->unk50[sourceIndex];
                        if (unlit) {
                            color = (s8 *)&hmf->unk88[source->unk2C[j]].unk05;
                        } else {
                            color = hmf->unk54[sourceIndex];
                        }
                        s = source->unk0C[j] * textureWidth;
                        t = source->unk1C[j] * textureHeight;
                        vertex = &m210_seaVtxBuf[vertexCount - 1];
                        for (vertexIndex = vertexCount - 1; vertexIndex >= groupStart; vertexIndex--, vertex--) {
                            if (vertex->v.ob[0] == position[0] && vertex->v.ob[1] == position[1] &&
                                vertex->v.ob[2] == position[2] && (s8)vertex->v.cn[0] == color[0] &&
                                (s8)vertex->v.cn[1] == color[1] && (s8)vertex->v.cn[2] == color[2] &&
                                vertex->v.tc[0] == s && vertex->v.tc[1] == t) {
                                break;
                            }
                        }
                        if (vertexIndex <= groupStart) {
                            vertex = &m210_seaVtxBuf[vertexCount];
                            vertex->v.ob[0] = position[0];
                            vertex->v.ob[1] = position[1];
                            vertex->v.ob[2] = position[2];
                            vertex->v.cn[0] = color[0];
                            vertex->v.cn[1] = color[1];
                            vertex->v.cn[2] = color[2];
                            vertex->v.tc[0] = s;
                            vertex->v.tc[1] = t;
                            vertex->v.cn[3] = 0xFF;
                            hmf->unk5C[sourceIndex] = vertexCount;
                            vertexCount++;
                        } else {
                            hmf->unk5C[sourceIndex] = vertexIndex;
                        }
                    }
                }
                hmf->unk18 = vertexCount;
                break;
            case 1:
                HuMemFree(hmf->unk40);
                for (i = 0; i < 3; i++) {
                    HuMemFree(hmf->unk44[i]);
                }
                hmf->unk40 = HuMemAllocTag(hmf->unk18 * sizeof(Vtx), hmf->unk0E);
                bcopy(m210_seaVtxBuf, hmf->unk40, hmf->unk18 * sizeof(Vtx));
                for (i = 0; i < 3; i++) {
                    hmf->unk44[i] = HuMemAllocTag(hmf->unk18 * sizeof(Vtx), hmf->unk0E);
                    bcopy(m210_seaVtxBuf, hmf->unk44[i], hmf->unk18 * sizeof(Vtx));
                }
                HuMemFree(m210_seaVtxBuf);
                break;
            case 2:
                gfx = HuMemAlloc(0x280 * sizeof(Gfx));
                gfxStart = gfx;
                groupStart = 0;
                faceCount = 0;
                vertexLimit = m210_seaVtxLimitTbl[(u32)(model->attr & HU3D_ATTR_LAYER_MASK) >> HU3D_ATTR_LAYER_SHIFT];
                maxVertex = 0;
                flush = 0;
                entry = m210_seaSortTbl;
                for (i = 0; i < object->unk22; i++) {
                    entry = entry->next;
                    if (entry->face == NULL) {
                        continue;
                    }
                    source = entry->face;
                    count = source->unk00 & 0x7F;
                    face = &faces[faceCount];
                    face->count = count;
                    for (j = 0; j < count; j++) {
                        vertexCount = hmf->unk5C[source->unk04[j]];
                        if (vertexCount + 1 > maxVertex) {
                            maxVertex = vertexCount + 1;
                        }
                        if (vertexLimit < maxVertex - groupStart) {
                            flush = 1;
                        }
                        face->indices[j] = vertexCount - groupStart;
                    }
                    faceCount++;
                    if (flush || i == object->unk22 - 1) {
                        groupSize = maxVertex - groupStart;
                        if (groupSize > 32) {
                            gSPVertex(gfx++, 0x01000000 + groupStart * sizeof(Vtx), 32, 0);
                            gSPVertex(gfx++, 0x01000000 + (groupStart + 32) * sizeof(Vtx), groupSize - 32, 32);
                        } else {
                            gSPVertex(gfx++, 0x01000000 + groupStart * sizeof(Vtx), groupSize, 0);
                        }
                        for (j = 0; j < faceCount; j++) {
                            face = &faces[j];
                            if (face->count == 3) {
                                if (j + 1 < faceCount && face[1].count == 3) {
                                    gSP2Triangles(gfx++, face->indices[0], face->indices[1], face->indices[2], 0,
                                                  face[1].indices[0], face[1].indices[1], face[1].indices[2], 0);
                                    j++;
                                } else {
                                    gSP1Triangle(gfx++, face->indices[0], face->indices[1], face->indices[2], 0);
                                }
                            } else {
                                gSP2Triangles(gfx++, face->indices[0], face->indices[1], face->indices[3], 0,
                                              face->indices[3], face->indices[1], face->indices[2], 0);
                            }
                        }
                        flush = 0;
                        groupStart = maxVertex;
                        faceCount = 0;
                    }
                }
                gSPEndDisplayList(gfx++);
                gfxCount = gfx - gfxStart;
                m210_seaGfx = HuMemAlloc(gfxCount * sizeof(Gfx));
                bcopy(gfxStart, m210_seaGfx, gfxCount * sizeof(Gfx));
                HuMemFree(gfxStart);
                HuMemFree(m210_seaSortTbl);
                m210_seaGfxReadyF++;
                break;
        }
        m210_seaGfxBuildStep++;
        return;
    }

    gfx = *gfxPos;
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPPipeSync(gfx++);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetBlendColor(gfx++, 0, 0, 0, 0);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);

    guMtxL2F(mtx, &((HuCamMtxs *)arg1)->lookAtMtx);
    mtxTransCat(mtx, model->pos.x, model->pos.y, model->pos.z);
    mtxRotCat(mtx, model->rot.x, model->rot.y, model->rot.z);
    mtxScaleCat(mtx, model->scale.x, model->scale.y, model->scale.z);
    mtxCat(model->mtx, mtx, modelMtx);
    guMtxF2L(modelMtx, &m210_seaMtx[Hu3DBufNo]);
    gSPMatrix(gfx++, osVirtualToPhysical(&m210_seaMtx[Hu3DBufNo]),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    frame = m210_SprAnimPatGet(m210_seaTexAnim, 0);
    anim = HuSprAnimDataGet(m210_seaTexAnim);
    gDPLoadTLUT_pal16(gfx++, 0, anim->pal);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTextureBlock_4b(gfx++, frame->data, G_IM_FMT_CI, frame->sizeX, frame->sizeY, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiBlock_4b(gfx++, frame->data, 0, 1, G_IM_FMT_CI, frame->sizeX, frame->sizeY, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    if (Hu3DPauseF == 0) {
        m210_seaTexScroll += 1.0;
    }
    gDPSetTileSize(gfx++, 0, 0, (s32)(m210_seaTexScroll * 1.5 + 7.25) & 0x1FF, (frame->sizeX - 1) << 2,
                   (frame->sizeY - 1) << 2);
    gDPSetTileSize(gfx++, 1, 16, (s32)m210_seaTexScroll & 0x1FF, (frame->sizeX - 1) << 2, (frame->sizeY - 1) << 2);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0, SHADE, COMBINED, 0, SHADE, 0, 0, 0, 0,
                      COMBINED);
    gDPSetPrimColor(gfx++, 0, 0, 128, 128, 128, 176);

    src = hmf->unk40;
    dst = hmf->unk44[Hu3DBufNo];
    for (i = 0; i < hmf->unk18; i++, src++, dst++) {
        dist = src->v.ob[0] * src->v.ob[0] + src->v.ob[2] * src->v.ob[2];
        dist = sqrtf(dist);
        dst->v = src->v;
        dst->v.cn[0] = (s32)((f32)src->v.cn[0] * 0.5);
        dst->v.cn[1] = (s32)((f32)src->v.cn[1] * 0.5);
        dst->v.cn[2] = (s32)((f32)src->v.cn[2] * 0.5);
        dst->v.cn[3] = 144;
        if (dist < 140.0) {
            continue;
        }
        if (710.0 < dist) {
            continue;
        }
        wave = m210_waveTbl;
        for (j = 0; j < 8; j++, wave++) {
            if (wave->unk10 == 0) {
                continue;
            }
            saved = dst->v;
            diff = wave->unk00 - dist;
            absDiff = fabs(diff);
            radius = dist;
            if (100.0 <= absDiff) {
                dst->v.ob[1] = src->v.ob[1];
            } else if (((diff < 34.0) & (0.0 <= diff) && 0.0 < dst->v.ob[2]) ||
                       ((-34.0 < diff) & (diff <= 0.0) && dst->v.ob[2] <= 0.0)) {
                dirX = src->v.ob[0] / radius;
                dirZ = src->v.ob[2] / radius;
                dst->v.ob[0] = dirX * wave->unk00;
                dst->v.ob[1] = src->v.ob[1] + wave->unk04;
                dst->v.ob[2] = dirZ * wave->unk00;
                dst->v.cn[0] = src->v.cn[0];
                dst->v.cn[1] = src->v.cn[1];
                dst->v.cn[2] = src->v.cn[2];
                dst->v.cn[3] = 255;
            } else {
                strength = 1.0 - absDiff / 100.0;
                strength *= strength;
                dst->v.ob[1] = src->v.ob[1] + wave->unk04 * strength;
                dst->v.cn[0] = (s32)((f32)src->v.cn[0] * (strength * 0.5 + 0.5));
                dst->v.cn[1] = (s32)((f32)src->v.cn[1] * (strength * 0.5 + 0.5));
                dst->v.cn[2] = (s32)((f32)src->v.cn[2] * (strength * 0.5 + 0.5));
                dst->v.cn[3] = strength * 112.0 + 144.0;
            }
            if (saved.ob[1] > dst->v.ob[1]) {
                dst->v = saved;
            }
        }
    }

    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(hmf->unk44[Hu3DBufNo]));
    gSPDisplayList(gfx++, m210_seaGfx);
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    *gfxPos = gfx;
}

void m210_WaveCreate(f32 arg0) {
    TidalTossWave *entry;
    s32 i;

    entry = m210_waveTbl;
    for (i = 0; i < 8; i++) {
        if (entry->unk10 == 0) {
            entry->unk00 = 0.0f;
            if (arg0 <= 150.0) {
                HuAudFXPlay(0x343);
                entry->unk10 = 1;
                entry->unk08 = 20.0f;
                entry->unk04 = 60.0f;
                entry->unk0C = 16.0f;
            } else if (arg0 <= 250.0) {
                HuAudFXPlay(0x346);
                entry->unk10 = 2;
                entry->unk08 = 20.0f;
                entry->unk04 = 120.0f;
                entry->unk0C = 20.0f;
            } else {
                HuAudFXPlay(0x345);
                entry->unk10 = 3;
                entry->unk08 = 26.0f;
                entry->unk04 = 240.0f;
                entry->unk0C = 30.0f;
            }
            return;
        }
        entry++;
    }
}

void m210_PlayerObjCreateAll(void) {
    s32 i;

    MgPlayerParamReset();
    mgPlayerObjNum = 0;
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 0xF, 0x32, -1, m210_PlayerObjInit);
    }
}

void m210_PlayerObjInit(omObjData *object) {
    MgPlayerWork *data;
    TidalTossWork *work;
    u8 playerIndex;
    u8 playerSlot;
    s8 character;
    u32 model;
    u16 modelTag;
    s32 motion;
    s32 i;
    f32 scale;

    playerSlot = m210_playerSlotNo;
    playerIndex = m210_playerSlotTbl[playerSlot][1];
    character = (s8)GwPlayer[playerIndex].chr;
    model = omCharModelNoTbl[character][0];
    motion = omCharMotTbl[character][0];
    modelTag = 0x2D9;
    MgPlayerCreate(object, model, motion, playerIndex, modelTag, modelTag);

    data = object->data;
    data->unk50 &= 0xFFFE;
    data->unkEC = 0;
    playerSlot = m210_playerSlotNo;
    object->trans.x = m210_playerPosTbl[playerSlot][0];
    object->trans.y = m210_playerPosTbl[playerSlot][1];
    object->trans.z = m210_playerPosTbl[playerSlot][2];
    data->unk3C = m210_playerRotTbl[playerSlot];
    scale = data->unkAC;
    object->scale.z = scale;
    object->scale.y = scale;
    object->scale.x = scale;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(0x64, TAG_OVERLAY);
    memset(data->unk158, 0, 0x64);
    work = data->unk158;
    work->unk2B = playerIndex;
    playerSlot = m210_playerSlotNo;
    work->unk2D = GwPlayer[playerSlot].group;
    work->unk2C = character;
    work->unk30 = GwPlayer[playerIndex].stat & PLAYER_IS_CPU;
    work->unk2E = GwPlayer[playerIndex].cpu_difficulty;
    work->unk2F = 0;
    work->unk1C = 11.0f;
    work->unk00 = object->trans.x;
    work->unk04 = object->trans.y;
    work->unk08 = object->trans.z;

    if (work->unk2D != 0) {
        playerSlot = m210_teamSlotNo;
        object->trans.x = m210_playerPosTbl[playerSlot + 1][0];
        object->trans.y = m210_playerPosTbl[playerSlot + 1][1];
        object->trans.z = m210_playerPosTbl[playerSlot + 1][2];
        data->unk3C = m210_playerRotTbl[playerSlot + 1];
        MgPlayerMapAttrSet(object, 0, 2);
        MgPlayerMapAttrSet(object, 1, 1);
        MgPlayerMapAttrSet(object, 2, 1);
        data->unk50 |= 0x8000;
        object->func = m210_TeamObjMain;
        m210_teamSlotNo++;
    } else {
        object->trans.x = m210_playerPosTbl[0][0];
        object->trans.y = m210_playerPosTbl[0][1];
        object->trans.z = m210_playerPosTbl[0][2];
        data->unk3C = m210_playerRotTbl[0];
        MgPlayerMapAttrSet(object, 0, 1);
        MgPlayerMapAttrSet(object, 1, 2);
        MgPlayerMapAttrSet(object, 2, 1);
        object->model[9] = Hu3DModelRead(0x2B0005, modelTag);
        Hu3DModelPosSet(object->model[9], object->trans.x, object->trans.y,
                        object->trans.z + 20.0);
        m210_soloNo = data->unk59;
        object->func = m210_SoloObjMain;
    }

    modelTag = 0x2DD;
    if (work->unk2D != 0) {
        for (i = 9; i < 12; i++) {
            object->model[i] = Hu3DModelRead(0x320003, modelTag);
            Hu3DMotionSpeedSet(object->model[i], 0.5f);
            Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
        }
    }

    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(character, 4), 1, 0x13);
    MgPlayerMotLoad(object, 0x15, CharMotionDataNumGet(character, 0x1F), 0, 0x13);

    if (work->unk2D != 0) {
        MgPlayerMotLoad(object, 1, CharMotionDataNumGet(character, 1), 1, 0);
        MgPlayerMotLoad(object, 2, CharMotionDataNumGet(character, 1), 1, 0);
        MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(character, 0xE), 0, 0);
        MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(character, 0x22), 0, 0);
        MgPlayerMotLoad(object, 9, CharMotionDataNumGet(character, 7), 1, 0x27);
        MgPlayerMotLoad(object, 0xA, CharMotionDataNumGet(character, 0x11), 1, 0x27);
        MgPlayerMotRead(object, 0x21, CharMotionDataNumGet(character, 0x23), 2, 0);
        MgPlayerMotLoad(object, 0x22, CharMotionDataNumGet(character, 0x24), 2, 0);
        work->unk24 = model | 0x2F;
        MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
        MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x36), 1, 0x78);
    } else {
        MgPlayerMotLoad(object, 8, CharMotionDataNumGet(character, 6), 1, 0x1D);
        MgPlayerMotLoad(object, 0x12, CharMotionDataNumGet(character, 0xF), 2, 0);
        switch (model >> 16) {
            case 2:
                work->unk24 = model | 0x30;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x30), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x38), 1, 0x64);
                break;
            case 3:
                work->unk24 = model | 0x30;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x30), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x38), 1, 0x64);
                break;
            case 7:
                work->unk24 = model | 0x30;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x30), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x36), 1, 0x78);
                break;
            case 5:
                work->unk24 = model | 0x2F;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x38), 1, 0x64);
                break;
            case 6:
                work->unk24 = model | 0x2F;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x38), 1, 0x64);
                break;
            case 9:
                work->unk24 = model | 0x2F;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x38), 1, 0x64);
                break;
            case 4:
            case 8:
            default:
                work->unk24 = model | 0x2F;
                MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
                MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x36), 1, 0x78);
                break;
        }
    }

    MgPlayerMotSet(object, 0);

    m210_playerSlotNo++;
}

void m210_PlayerCreate(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
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

void m210_SoloObjMain(omObjData *object) {
    MgPlayerWork *data;
    TidalTossWork *work;
    u8 player;
    u16 status;
    s32 random;
    f32 y;
    f32 zero;

    data = object->data;
    work = data->unk158;
    player = data->unk57;

    switch (m210_phase) {
        case 0:
            work->unk44 = 0.0f;
            random = m210_Rand16Get();
            work->unk36 = (s32)((f64)(f32)random * 1.52587890625e-05 * 12.0);
            work->unk38 = 0;
            break;
        case 1:
            break;
        case 2:
            if (work->unk30 != 0) {
                HuPadStkY[player] = 0;
                HuPadStkX[player] = 0;
                HuPadBtnDown[player] = 0;
                HuPadBtn[player] = 0;
                m210_SoloComInput(object);
            }
            break;
        case 3:
        case 4:
            HuPadStkX[player] = 0;
            HuPadStkY[player] = -64;
            HuPadBtnDown[player] = 0;
            HuPadBtn[player] = 0;
            break;
        case 5:
            if (work->unk2F == 1) {
                MgPlayerMotSet(object, 0xD);
                HuAudCharVoicePlay(work->unk24);
                GwPlayer[data->unk59].bonusCoin += 10;
                work->unk2F++;
            } else if (work->unk2F == 0) {
                MgPlayerMotSet(object, 0xE);
                work->unk2F--;
            }
            break;
        case 6:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 7:
            return;
    }

    status = MgPlayerMotStatGet(object);
    work->unk0C = object->trans.x;
    work->unk10 = object->trans.y;
    work->unk14 = object->trans.z;
    if (status & MGPLAYER_MOTSTAT_JUMP) {
        HuPadStkY[player] = 0;
        HuPadStkX[player] = 0;
    }

    MgPlayerObjMain(object);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

    if (status & MGPLAYER_MOTSTAT_HIPDROP) {
        if ((data->unk50 & 0x80) && (work->unk2A == 0)) {
            m210_WaveCreate(work->unk20);
            work->unk2A++;
        }
        if (!(work->unk28 & MGPLAYER_MOTSTAT_HIPDROP)) {
            work->unk20 = object->trans.y - 20.0;
            work->unk2A = 0;
        }
    } else if ((work->unk28 & MGPLAYER_MOTSTAT_JUMP) && !(status & MGPLAYER_MOTSTAT_JUMP)) {
        m210_WaveCreate(100.0f);
        work->unk20 = 100.0f;
    }

    work->unk44 += 4.0;
    if (work->unk44 >= 360.0) {
        work->unk44 -= 360.0;
    }

    if ((work->unk20 > 20.0) && (work->unk2A != 0)) {
        y = 20.0 - work->unk20 * 0.075;
        work->unk20 *= 0.8;
    } else {
        y = 20.0 - sindf(work->unk44) * 5.0;
    }

    Hu3DModelPosSet(object->model[9], 0.0f, y, 0.0f);
    if (!(status & (MGPLAYER_MOTSTAT_JUMP | MGPLAYER_MOTSTAT_HIPDROP))) {
        object->trans.y = y;
    }
    zero = 0.0f;
    object->trans.z = zero;
    object->trans.x = zero;
    work->unk28 = status;
}

void m210_SplashEffSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (Hu3DData[arg0->model[i]].attr & 4) {
            MgPlayerEffSet(arg0, i, arg1, arg2, arg3, 0.0f, 0.0f);
            return;
        }
    }
}

void m210_TeamObjMain(omObjData *object) {
    MgPlayerWork *data;
    TidalTossWork *work;
    u8 player;
    u32 status;
    f64 dist;
    TidalTossWave *entry;
    s32 i;
    f32 angle;
    f32 rot;
    f32 diff;
    f64 radius;
    omObjData *other;
    MgPlayerWork *otherData;

    data = object->data;
    work = data->unk158;
    player = data->unk57;
    status = MgPlayerMotStatGet(object);
    work->unk0C = object->trans.x;
    work->unk10 = object->trans.y;
    work->unk14 = object->trans.z;
    dist = sqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);

    switch (m210_phase) {
        case 0:
            work->unk2F = 1;
            work->unk2A = 0;
            work->unk44 = 0.0f;
            work->unk4C = (s32)((f64)(f32)m210_Rand16Get() * 1.52587890625e-05 * 10.0);
            break;
        case 1:
            break;
        case 2:
            if (work->unk30 != 0) {
                HuPadStkY[player] = 0;
                HuPadStkX[player] = 0;
                HuPadBtnDown[player] = 0;
                HuPadBtn[player] = 0;
                m210_TeamComInput(object, dist);
            }
            if (data->unkBE == 0) {
                entry = m210_waveTbl;
                for (i = 0; i < 8; i++, entry++) {
                    if (entry->unk10 == 0) {
                        continue;
                    }
                    diff = entry->unk00 - dist;
                    if (!(__builtin_fabsf(diff) <= entry->unk08 * 0.75)) {
                        continue;
                    }
                    if (!(object->trans.y < entry->unk04)) {
                        continue;
                    }
                    angle = m210_AngleCalc(object->trans.x, object->trans.z);
                    if (angle > 180.0) {
                        angle -= 360.0f;
                    }
                    rot = data->unk3C;
                    if (rot > 180.0) {
                        rot -= 360.0f;
                    }
                    if (fabs(rot - angle) < 90.0) {
                        MgPlayerMotSet(object, 10);
                        data->unk3C = angle;
                        data->unk40 = entry->unk0C;
                        status |= MGPLAYER_MOTSTAT_KNOCKBACK_FRONT;
                    } else {
                        MgPlayerMotSet(object, 9);
                        data->unk3C = angle + 180.0;
                        data->unk40 = -entry->unk0C;
                        status |= MGPLAYER_MOTSTAT_KNOCKBACK_BACK;
                    }
                    data->unk38 = -0.735f;
                    data->unkBE = 94;
                    MgPlayerSePlay(data, 8);
                    switch (entry->unk10) {
                        case 1:
                            omVibrate(data->unk59, 2, 3, 10);
                            break;
                        case 2:
                            omVibrate(data->unk59, 10, 0, 10);
                            break;
                        case 3:
                            omVibrate(data->unk59, 2, 2, 20);
                            break;
                    }
                }
            }
            if (object->trans.y <= 0.0) {
                object->trans.x += object->trans.x * 0.5 / dist;
                object->trans.z += object->trans.z * 0.5 / dist;
            }
            break;
        case 3:
            if (data->unkBE != 0) {
                data->unkBE = 1;
            }
            // fallthrough
        case 4:
            HuPadStkX[player] = 0;
            HuPadStkY[player] = -48;
            HuPadBtnDown[player] = 0;
            HuPadBtn[player] = 0;
            break;
        case 5:
            HuPadStkX[player] = 0;
            HuPadStkY[player] = -48;
            HuPadBtnDown[player] = 0;
            HuPadBtn[player] = 0;
            angle = fmod(data->unk3C, 360.0);
            if ((8.0 < angle && angle < 352.0) || (angle < -8.0 && -352.0 < angle)) {
                break;
            }
            if (work->unk2F == 1) {
                if (work->unk2A == 0) {
                    MgPlayerMotForceSet(object, 13);
                    HuAudCharVoicePlay(work->unk24);
                }
                GwPlayer[data->unk59].bonusCoin += 10;
                work->unk2F++;
            } else if (work->unk2F == 0) {
                work->unk2F--;
            }
            break;
        case 6:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 7:
            return;
    }

    HuPadStkX[player] = (f32)HuPadStkX[player] * 0.325;
    HuPadStkY[player] = (f32)HuPadStkY[player] * 0.325;
    MgPlayerObjMain(object);
    if (dist <= 190.0) {
        object->trans.x = object->trans.x / dist * 190.0;
        object->trans.z = object->trans.z / dist * 190.0;
    }
    if ((status & (MGPLAYER_MOTSTAT_KNOCKBACK_BACK | MGPLAYER_MOTSTAT_KNOCKBACK_FRONT)) && work->unk2A == 0) {
        if (690.0 - data->unk48 <= dist && m210_phase == 2) {
            if (status & MGPLAYER_MOTSTAT_KNOCKBACK_BACK) {
                data->unk40 = -24.0f;
            } else {
                data->unk40 = 24.0f;
            }
            MgPlayerMapAttrSet(object, 0, 1);
            MgPlayerMapAttrSet(object, 2, 2);
            data->unk38 = -1.0289999f;
            work->unk2A = 1;
            work->unk2F = 0;
            _HuAudPlayerFXPlay(0x344, data->unk59);
            _HuAudPlayerFXPlay(work->unk2C + 0x287, data->unk59);
        }
    } else {
        if (data->unk40 > 4.0) {
            data->unk40 = 4.0f;
        }
        if (status & MGPLAYER_MOTSTAT_JUMP) {
            if (!(work->unk28 & MGPLAYER_MOTSTAT_JUMP)) {
                work->unk18 = data->unk40;
            }
            data->unk40 = work->unk18;
        } else if (work->unk28 & MGPLAYER_MOTSTAT_JUMP) {
            if (dist <= 590.0) {
                m210_SplashEffSet(object, object->trans.x, 60.0f, object->trans.z + 50.0);
            }
        }
    }
    if (work->unk2A != 0) {
        if (data->unk40 > 0.0f) {
            data->unk40 = 20.0f;
        } else {
            data->unk40 = -20.0f;
        }
    } else if (690.0 - data->unk48 <= dist) {
        object->trans.x = (690.0 - data->unk48) * (object->trans.x / dist);
        object->trans.z = (690.0 - data->unk48) * (object->trans.z / dist);
    }

    for (i = 0; i < 4; i++) {
        other = mgPlayerObjTbl[i];
        if (object == other) {
            continue;
        }
        otherData = other->data;
        if (((TidalTossWork *)otherData->unk158)->unk2D == 0) {
            continue;
        }
        if (fabs(object->trans.y - other->trans.y) > 30.0) {
            continue;
        }
        dist = m210_DistXZCalc(&object->trans, &other->trans);
        radius = data->unk48 + otherData->unk48;
        if (radius < dist) {
            continue;
        }
        if (data->unk40 <= otherData->unk40) {
            angle = m210_AngleCalc(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
            other->trans.x = object->trans.x + radius * sindf(angle);
            other->trans.z = object->trans.z + radius * cosdf(angle);
        } else {
            angle = m210_AngleCalc(object->trans.x - other->trans.x, object->trans.z - other->trans.z);
            object->trans.x = other->trans.x + radius * sindf(angle);
            object->trans.z = other->trans.z + radius * cosdf(angle);
        }
    }
    work->unk28 = status;
    for (i = 9; i < 12; i++) {
        if (Hu3DData[object->model[i]].motTime >= Hu3DMotion[Hu3DData[object->model[i]].motId].unk02) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

u16 m210_SoloComInput(omObjData *object) {
    TidalTossWork *work;
    MgPlayerWork *data;
    s16 player;
    s32 status;
    s32 random;
    u16 result;

    m210_PlayerWorkGet(object, &data, &work);
    player = data->unk57;
    status = MgPlayerMotStatGet(object);

    switch (work->unk32) {
        case 1:
            if (work->unk2E == 0) {
                HuPadBtn[player] |= A_BUTTON;
            }
            if (status & MGPLAYER_MOTSTAT_JUMP) {
                work->unk32++;
            } else {
                HuPadBtnDown[player] |= A_BUTTON;
            }
            break;
        case 2:
            if (work->unk2E == 0) {
                HuPadBtn[player] |= A_BUTTON;
            }
            if (!(status & MGPLAYER_MOTSTAT_JUMP)) {
                work->unk32 = 0;
            }
            break;
        case 3:
            if (status & MGPLAYER_MOTSTAT_IDLE) {
                HuPadBtnDown[player] |= A_BUTTON;
                work->unk32++;
            }
            break;
        case 4:
            HuPadBtn[player] |= A_BUTTON;
            if ((f64)(f32)work->unk34 <= object->trans.y - 20.0) {
                HuPadBtnDown[player] |= Z_TRIG;
                work->unk32++;
            }
            break;
        case 5:
            if (status & MGPLAYER_MOTSTAT_IDLE) {
                work->unk32 = 0;
            }
            break;
    }

    if (work->unk32 == 0) {
        random = m210_Rand16Get();
        if (random % (6 - work->unk2E) == 0) {
            work->unk38 = 5;
            random = m210_Rand16Get();
            if (random % (work->unk2E + 3) == 0 || work->unk36 == 0) {
                work->unk32 = 3;
                random = m210_Rand16Get();
                work->unk34 = (s32)((f64)(f32)random * 1.52587890625e-05 * 10.0) * 10 + 170;
                random = m210_Rand16Get();
                work->unk36 = (s32)((f64)(f32)random * 1.52587890625e-05 * 8.0) + 8;
            } else {
                work->unk32 = 1;
                work->unk34 = 400;
                work->unk36--;
            }
        }
    }

    return result;
}

u16 m210_TeamComInput(omObjData *arg0, f32 arg1) {
    TidalTossWork *work;
    MgPlayerWork *data;
    TidalTossWave *entry;
    f32 distance;
    f64 distanceD;
    f32 absDistance;
    f32 radius;
    u32 status;
    s16 player;
    s32 i;
    s32 random;
    u16 result; // The original function returns this uninitialized value; its caller ignores it.

    m210_PlayerWorkGet(arg0, &data, &work);
    {
        f32 unused[2]; // Unused stack space retained from the original function.
    }
    player = data->unk57;
    status = MgPlayerMotStatGet(arg0);
    entry = m210_waveTbl;

    for (i = 0; i < 8; i++) {
        if (entry->unk10 != 0) {
            distance = entry->unk00 - arg1;
            distanceD = distance;
            absDistance = __builtin_fabsf(distance);
            radius = entry->unk08 + (7.25 - (f32)entry->unk10 + (f32)work->unk2E * 0.25) * 20.0;
            if (absDistance <= radius) {
                if (distanceD <= 0.0) {
                    random = (s32)((f32)m210_Rand16Get() * 1.52587890625e-05 * 100.0);
                    if (random < work->unk2E * 10 + 45) {
                        HuPadBtnDown[player] |= A_BUTTON;
                        switch (work->unk2E) {
                            case 0:
                            case 1:
                                work->unk32 = 10;
                                break;
                            case 2:
                                if (entry->unk10 != 1) {
                                    work->unk32 = 10;
                                } else {
                                    work->unk32 = 0;
                                }
                                break;
                            case 3:
                                if (entry->unk10 == 3) {
                                    work->unk32 = 10;
                                } else {
                                    work->unk32 = 0;
                                }
                                break;
                        }
                        break;
                    }
                }
            }
        }
        entry++;
    }

    if (work->unk32 != 0) {
        work->unk32--;
        HuPadBtn[player] |= A_BUTTON;
    }

    if (240.0 < arg1 && !(status & MGPLAYER_MOTSTAT_JUMP)) {
        HuPadStkX[player] = (work->unk2E * 4.0 + 53.0) * -arg0->trans.x / arg1;
        HuPadStkY[player] = (work->unk2E * 4.0 + 53.0) * arg0->trans.z / arg1;
    }

    return result;
}

void m210_PlayerWorkGet(omObjData *arg0, MgPlayerWork **arg1, TidalTossWork **arg2) {
    *arg1 = arg0->data;
    *arg2 = (*arg1)->unk158;
}

s32 m210_Rand16Get(void) {
    m210_randSeed = m210_randSeed * 0x41C64E6D + 0x3039;
    m210_randSeed += rand8();
    return m210_randSeed >> 16;
}

f32 m210_DistXZCalc(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

f32 m210_AngleCalc(f32 arg0, f32 arg1) {
    f32 angle;
    f32 fullRot = 360.0f;

    angle = atan2df(arg0, arg1);
    if (angle < 0.0f) {
        angle += fullRot;
    } else if (fullRot <= angle) {
        angle -= fullRot;
    }
    return angle;
}

s16 m210_AnimDataRead(s32 arg0) {
    void *temp_v0;
    s16 temp_s0;

    temp_v0 = DataRead(arg0);
    temp_s0 = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    return temp_s0;
}

s16 m210_SprGrpCreate(s16 arg0, s16 arg1) {
    s16 spriteId;
    s32 i;

    if (arg0 == -1) {
        return -1;
    }
    spriteId = HuSprGrpCreate(arg1, 0);
    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < arg1; i++) {
        HuSprGrpMemberSet(spriteId, i, arg0, 0);
    }
    return spriteId;
}

HuSprAnimPat *m210_SprAnimPatGet(s16 arg0, s16 arg1) {
    return &HuSprAnimDataGet(arg0)->pat[arg1];
}
