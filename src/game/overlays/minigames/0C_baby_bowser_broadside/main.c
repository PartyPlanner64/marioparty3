#include "common.h"
#include "game/overlays/minigame.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "baby_bowser_broadside.h"
#include "gcc/memory.h"

typedef struct BabyBowserBroadsideBall {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ Vec velocity;
    /* 0x1C */ f32 initialVelocityY;
    /* 0x20 */ f32 elapsed;
    /* 0x24 */ f32 angle;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
    /* 0x2C */ BabyBowserBroadsideMover *unk_2C;
} BabyBowserBroadsideBall; // Size 0x30

typedef struct BabyBowserBroadsidePlayer {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk_09;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char unk_11[0xF];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ char unk_24[0x24];
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ char unk_4A[2];
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ BabyBowserBroadsideBall *unk_54;
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ s16 unk_5A;
    /* 0x5C */ BabyBowserBroadsideMover *unk_5C;
} BabyBowserBroadsidePlayer;

typedef struct BabyBowserBroadsideTeam {
    /* 0x00 */ s8 count;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s16 players[2];
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ f32 angles[2];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char unk_16[2];
} BabyBowserBroadsideTeam; // Size 0x18

typedef struct BabyBowserBroadsideGame {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ char unk_08[0x10];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ char unk_1A[0xE];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ char unk_2C[0xC];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E[4];
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48[4];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s8 unk_52;
    /* 0x53 */ char unk_53[5];
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ s8 unk_60;
    /* 0x61 */ s8 unk_61;
    /* 0x62 */ char unk_62[2];
} BabyBowserBroadsideGame; // Size 0x64

extern u8 mgPlayerTeam[];

typedef struct BabyBowserBroadsidePositions {
    Vec points[4][4];
} BabyBowserBroadsidePositions;

typedef struct BabyBowserBroadsidePortraits {
    s32 files[8];
} BabyBowserBroadsidePortraits;

s16 m212_resultF = 0;
f32 m212_seaWaveRot = 0.0f;
f32 m212_seaScrollY = 0.0f;
f32 m212_seaColorRot = 180.0f;
s16 m212_startF = 0;
s16 m212_musicF = 0;
s16 m212_winStep = 0;
s16 m212_drawStep = 0;
s16 m212_koopaJrPosXTbl[6] = { 0, 0, 60, 0, -60, 0 };
s16 m212_koopaJrPosZTbl[6] = { 0, 60, 0, -60, 0, 0 };

const s16 m212_fontMesTbl[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };
const s16 m212_fontMesTbl2[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000 };
const s16 m212_fontMesTbl3[] = { 0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000 };
const Vec m212_originPos = { 0.0f, 0.0f, 0.0f };
const BabyBowserBroadsidePositions m212_centerWallVtxTbl = { {
    { { -50.0f, 100.0f, 170.0f }, { 50.0f, 100.0f, 170.0f }, { 50.0f, 200.0f, 170.0f }, { -50.0f, 200.0f, 170.0f } },
    { { 170.0f, 100.0f, 50.0f }, { 170.0f, 100.0f, -50.0f }, { 170.0f, 200.0f, -50.0f }, { 170.0f, 200.0f, 50.0f } },
    { { 50.0f, 100.0f, -170.0f }, { -50.0f, 100.0f, -170.0f }, { -50.0f, 200.0f, -170.0f }, { 50.0f, 200.0f, -170.0f } },
    { { -170.0f, 100.0f, -50.0f }, { -170.0f, 100.0f, 50.0f }, { -170.0f, 200.0f, 50.0f }, { -170.0f, 200.0f, -50.0f } },
} };
const BabyBowserBroadsidePortraits m212_chrIconTbl = { { 8, 9, 10, 11, 12, 13, 14, 15 } };
const s32 m212_chrIconTblPad[3] = { 0 }; /* Unreferenced. */

BabyBowserBroadsideTeam *m212_teamTbl BSS;
BabyBowserBroadsidePlayer *m212_playerTbl BSS;
BabyBowserBroadsideGame *m212_gameWork BSS;
s16 m212_ambientSeNo BSS;


void m212_StageObjMain(omObjData *object);
void m212_SeaObjMain(omObjData *object);
void m212_StageRotUpdate(BabyBowserBroadsideSlot *slot);
void m212_KoopaJrMove(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_KoopaJrShakeUpdate(void);
s16 m212_SprCreate(s16 priority, s32 directory, s32 file, s32 bank, s32 attr);
void m212_SprDispOn(s16 sprite, s16 x, s16 y);
s16 m212_AnimMdlCreate(s32 directory, s32 file, f32 scale, s16 type, s32 arg4, s32 flags);
s16 m212_BillboardCreate(s32 directory, s32 file, s16 type, s32 flags);
void m212_ColliderInit(s32 arg0, BabyBowserBroadsideFunc *handler);
s16 m212_ColliderCreate(s16 model, Vec *positions, s16 count, f32 arg3, f32 arg4, s32 flags);
s16 m212_ColliderLinkCreate(s16 boat, s32 flags);
void m212_MdlSync(omObjData *object);
void m212_AngleDiffMinimize(f32 *start, f32 *end);

extern u8 omAllPauseF;

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];

void m212_PlayerObjMain(omObjData *object);
void m212_PlayerInputUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_PlayerMove(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_BallUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_PlayerMotUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_PlayerStateSet(BabyBowserBroadsidePlayer *player, s16 motion, s8 arg2);
void m212_MoverUpdate(BabyBowserBroadsideMover *ship);
void m212_MoverInit(BabyBowserBroadsideMover *ship, s16 count, f32 speed, s16 model);
void m212_MainObjMain(omObjData *object);
void m212_StageObjInit(omObjData *object);
void m212_SeaObjInit(omObjData *object);
void m212_PlayerObjInit(omObjData *object);
void m212_CameraViewInit(void);
void m212_ScoreUpdate(void);
void m212_FinishSeFade(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_WinExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_PlayerWinExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_DrawExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_WipeExitExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_PlayerLoseExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
void m212_StartExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
s32 m212_ComShotHitCheck(omObjData *object, BabyBowserBroadsidePlayer *player);
void m212_PlayerComInput(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler);
BabyBowserBroadsideFuncGroup *m212_FuncGroupCreate(omObjData *object, s8 group, s16 count, s16 handlers);
s16 m212_FuncSet(s8 index, s32 flags, s32 arg2, void (*callback)(), s32 arg4); // Declared with s32 arg4: this caller does not narrow to u8.

void m212_ObjectSetup(void);
void m212_GameWorkInit(void);
void m212_ExitCheckObjMain(omObjData *object);
void m212_ExitWaitObjMain(omObjData *object);
void m212_ExitObjMain(omObjData *object);
void m212_MainObjInit(omObjData *object);
void m212_SystemCreate(void);
void m212_FuncReset(); // Unprototyped: called with one argument.
void m212_FuncGroupUpdate(s8 group);
void m212_SprUpdate(void);
void m212_AnimMdlUpdate(void);
void m212_BillboardUpdate(void);
s16 m212_AnimMdlFreeGet(s16 index);
s16 m212_BallFreeGet(BabyBowserBroadsidePlayer *player);
void m212_PlayerNextStateSet(BabyBowserBroadsidePlayer *player, s16 motion);
void m212_BallKill(BabyBowserBroadsideBall *entry);
void m212_BallFire(omObjData *object, BabyBowserBroadsideBall *entry, f32 angle, s16 team);
s16 m212_BillboardFreeGet(s16 index);
void m212_BillboardDispOn(s16 index, f32 x, f32 y, f32 z, u8 *color);
s32 m212_AnimMdlDispOn(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 arg8);

void m212_Executor(void) {
    m212_ObjectSetup();
}

void m212_ObjectSetup(void) {
    u8 camera;

    MapCollInit(0x32);
    Hu3DSprModelInit(0x30);
    omInitObjMan(0x32, 0);
    omGameSysInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(1);
    camera = CamSetupMapCullAdd();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 6000.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    m212_SystemCreate();
    m212_GameWorkInit();
    omAddObj(0x3E8, 0, 0, -1, m212_MainObjInit);
    omAddObj(0x7D0, 0, 0, -1, m212_ExitCheckObjMain);
    GMesFontMesCreate(m212_fontMesTbl, 1);
    GMesFontMesCreate(m212_fontMesTbl2, 1);
    GMesFontMesCreate(m212_fontMesTbl3, 1);
}

void m212_GameWorkInit(void) {
    s8 i, j;
    s8 angle;
    s32 random;
    f32 startAngle;

    m212_gameWork = HuMemAllocTag(0x64, TAG_OVERLAY);
    memset(m212_gameWork, 0, 0x64);
    m212_playerTbl = HuMemAllocTag(0x180, TAG_OVERLAY);
    memset(m212_playerTbl, 0, 0x180);
    for (i = 0; i < 4; i++) {
        m212_playerTbl[i].unk_54 = HuMemAllocTag(0x90, TAG_OVERLAY);
        memset(m212_playerTbl[i].unk_54, 0, 0x90);
    }
    m212_teamTbl = HuMemAllocTag(0x30, TAG_OVERLAY);
    memset(m212_teamTbl, 0, 0x30);
    random = rand16();
    angle = random % 4;
    startAngle = m212_teamTbl[0].angles[0] = angle * 90.0f;
    m212_teamTbl[0].angles[1] = startAngle + 180.0f;
    m212_teamTbl[1].angles[0] = startAngle + 90.0f;
    m212_teamTbl[1].angles[1] = startAngle + 270.0f;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            while (m212_teamTbl[i].angles[j] >= 360.0f) {
                m212_teamTbl[i].angles[j] -= 360.0f;
            }
        }
    }
}

void m212_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m212_ExitWaitObjMain;
    }
}

void m212_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m212_ExitObjMain;
    }
}

void m212_ExitObjMain(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m212_CameraUpdate(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    m212_FuncGroupUpdate(0);
}

void m212_MainObjInit(omObjData *object) {
    s16 counts[2];
    s16 i, j;
    BabyBowserBroadsideTeam *team;

    MgPlayerParamReset();
    MgShadowAltSet(1);
    m212_FuncGroupCreate(NULL, 0, 0, 4);
    m212_FuncSet(0, 0, 0, m212_CameraViewInit, 0);
    object->work[1] = 1;
    m212_FuncGroupCreate(object, (s8)object->work[1], 0, 6);
    mgMapObjTbl[0] = omAddObj(10, 1, 0, -1, m212_StageObjInit);
    mgMapObjTbl[1] = omAddObj(10, 1, 0, -1, m212_SeaObjInit);
    omSetStatBit(mgMapObjTbl[1], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    counts[1] = 0;
    counts[0] = 0;
    for (i = 0; i < 4; i++) {
        if (mgPlayerTeam[i] >= 2 || counts[0] >= 3 || counts[1] >= 3) {
            for (j = 0; j < 4; j++) {
                mgPlayerTeam[j] = GwPlayer[j].group;
            }
            break;
        }
        counts[mgPlayerTeam[i]]++;
    }
    for (i = 0; i < 4; i++) {
        team = &m212_teamTbl[m212_playerTbl[i].unk_5A = mgPlayerTeam[i]];
        m212_playerTbl[i].unk_10 = team->count;
        team->players[team->count++] = i;
    }
    for (i = 0; i < 4; i++) {
        mgPlayerObjTbl[i] = omAddObj(300, 9, 41, -1, m212_PlayerObjInit);
    }
    m212_gameWork->unk_00 = 1;
    m212_gameWork->unk_04 = 900.0f;
    m212_FuncSet((s8)object->work[1], 0xFFFF, 0, m212_ScoreUpdate, 0);
    m212_FuncSet((s8)object->work[1], 0xF, 0, m212_StartExec, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = m212_MainObjMain;
}

void m212_MainObjMain(omObjData *object) {
    m212_FuncGroupUpdate((s8)object->work[1]);
    m212_CameraUpdate();
    m212_SprUpdate();
    m212_AnimMdlUpdate();
    m212_BillboardUpdate();
}

void m212_StageObjInit(omObjData *object) {
    s16 hudY = 32;
    s32 flags = 0x99;
    s32 attr = 0x1000;
    Vec center = m212_originPos;
    Vec bowserCenter = m212_originPos;
    BabyBowserBroadsidePositions positions = m212_centerWallVtxTbl;
    BabyBowserBroadsidePortraits portraits = m212_chrIconTbl;
    BabyBowserBroadsideSlot *slot;
    BabyBowserBroadsideFunc *handler;
    BabyBowserBroadsideBall *entry;
    s16 i, j;
    s16 model;
    s16 sprite;
    s16 index;

    object->work[1] = 2;
    slot = m212_FuncGroupCreate(object, (s8)object->work[1], 6, 4)->unk_00;
    slot->unk_04[0] = Hu3DModelRead(0x2D0002, flags);
    slot->unk_04[1] = Hu3DModelRead(0x2D0000, flags);
    slot->unk_04[2] = Hu3DModelRead(0x2D0001, flags);
    slot->unk_04[3] = m212_gameWork->unk_50 = Hu3DModelRead(0x2D0008, flags);
    slot->unk_04[4] = Hu3DModelRead(0x2D0009, flags);
    slot->unk_04[5] = Hu3DModelRead(9, flags);
    m212_playerTbl[m212_teamTbl[0].players[0]].unk_48 = model = Hu3DModelRead(0x2D0004, flags);
    m212_playerTbl[m212_teamTbl[0].players[1]].unk_48 = Hu3DModelLink(model);
    m212_playerTbl[m212_teamTbl[1].players[0]].unk_48 = model = Hu3DModelRead(0x2D0005, flags);
    m212_playerTbl[m212_teamTbl[1].players[1]].unk_48 = Hu3DModelLink(model);
    entry = m212_playerTbl[m212_teamTbl[0].players[0]].unk_54;
    model = entry->unk_02 = Hu3DModelRead(0x2D0006, flags);
    for (i = 0; i < 2; i++) {
        entry = m212_playerTbl[m212_teamTbl[0].players[i]].unk_54;
        for (j = 0; j < 3; j++, entry++) {
            if ((i == 0) & (j == 0)) {
                // The first projectile already uses the original model.
            } else {
                entry->unk_02 = Hu3DModelLink(model);
            }
        }
    }
    entry = m212_playerTbl[m212_teamTbl[1].players[0]].unk_54;
    model = entry->unk_02 = Hu3DModelRead(0x2D0007, flags);
    for (i = 0; i < 2; i++) {
        entry = m212_playerTbl[m212_teamTbl[1].players[i]].unk_54;
        for (j = 0; j < 3; j++, entry++) {
            if ((i == 0) & (j == 0)) {
                // The first projectile already uses the original model.
            } else {
                entry->unk_02 = Hu3DModelLink(model);
            }
        }
    }
    Hu3DModelScaleSet((s16)slot->unk_04[5], 2.0f, 2.0f, 2.0f);
    Hu3DModelPosSet((s16)slot->unk_04[2], 0.0f, 350.0f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[3], 0.0f, 455.00003f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[4], 0.0f, 455.00003f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[5], 0.0f, 450.0f, 0.0f);
    Hu3DData[(s16)slot->unk_04[3]].motSpeed = 0.0f;
    for (i = 0; i < 4; i++) {
        Hu3DData[m212_playerTbl[i].unk_48].motSpeed = 0.0f;
    }
    flags |= 0x400;
    for (i = 0; i < 4; i++) {
        m212_AnimMdlCreate(0x2D, 12, 2.0f, 0, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        m212_AnimMdlCreate(0x2D, 13, 2.0f, 1, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        m212_AnimMdlCreate(0x2D, 10, 1.0f, 2, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        m212_AnimMdlCreate(0x2D, 11, 1.0f, 3, 0, flags);
    }
    for (i = 0; i < 8; i++) {
        index = m212_BillboardCreate(0x2D, 15, 0, 11);
        Hu3DModelScaleSet(m212_billboardTbl[index].unk_0C, 2.0f, 2.0f, 1.0f);
    }
    sprite = m212_SprCreate(255, 0x2D, 14, 0, attr);
    HuSprTPLvlSet(m212_sprTbl[sprite].unk_01, 0, 190);
    m212_SprDispOn(sprite, 70, 32);
    sprite = m212_SprCreate(255, 0x2D, 14, 0, attr);
    HuSprTPLvlSet(m212_sprTbl[sprite].unk_01, 0, 190);
    m212_SprDispOn(sprite, 250, 32);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            m212_SprDispOn(m212_SprCreate(239, 33, portraits.files[GwPlayer[m212_teamTbl[i].players[j]].chr], 0, 0), i * 180 + (s16)(j * 18 + 40), hudY);
        }
    }
    for (i = 0; i < 2; i++) {
        m212_teamTbl[i].unk_12 = model = m212_SprCreate(239, 0, 45, 0, 0);
        m212_SprDispOn(model, (s16)(i * 180 + 84), hudY);
        m212_teamTbl[i].unk_14 = model = m212_SprCreate(239, 0, 45, 0, 0);
        m212_SprDispOn(model, (s16)(i * 180 + 100), hudY);
    }
    index = m212_FuncSet((s8)object->work[1], 0xFFFF, 0, m212_ColliderInit, (s8)object->work[1]);
    handler = &m212_funcGroupTbl[object->work[1]].unk_04[index];
    handler->unk_40(0, handler);
    m212_gameWork->unk_3C = m212_ColliderCreate(-1, &center, 1, 400.0f, 1000.0f, 0x490);
    m212_gameWork->unk_46 = m212_ColliderCreate((s16)slot->unk_04[4], &bowserCenter, 1, 10.0f, 150.0f, 0x40C);
    for (i = 0; i < 4; i++) {
        m212_gameWork->unk_3E[i] = m212_ColliderCreate((s16)slot->unk_04[2], positions.points[i], 4, 0.0f, 0.0f, 0x13E);
    }
    for (i = 0; i < 4; i++) {
        m212_gameWork->unk_48[i] = m212_ColliderLinkCreate(m212_gameWork->unk_3E[i], 0x116);
    }
    m212_gameWork->unk_60 = 0;
    m212_gameWork->unk_61 = (s32)rand16() % 4 + 1;
    m212_FuncSet((s8)object->work[1], 0, 0, m212_StageRotUpdate, 0);
    m212_FuncSet((s8)object->work[1], 14, 0, m212_KoopaJrMove, 0);
    m212_FuncSet((s8)object->work[1], 15, 0, m212_KoopaJrShakeUpdate, 0);
    object->model[0] = slot->unk_04[0];
    m212_MdlSync(object);
    object->func = m212_StageObjMain;
}

void m212_StageObjMain(omObjData *object) {
    m212_FuncGroupUpdate(2);
    m212_MdlSync(object);
}

void m212_SeaObjInit(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x2D0003, 0x10099);
    Hu3DModelVtxBufMake(object->model[0]);
    object->func = m212_SeaObjMain;
}

void m212_SeaObjMain(omObjData *object) {
    Hu3DModelTexScroll(object->model[0], sindf(m212_seaWaveRot) * 15.0f, -m212_seaScrollY, 64, 64);
    Hu3DModelPrimColorSet(object->model[0], (u8)(cosdf(m212_seaColorRot) * 32.0f + 32.0f), 0, 0, (u8)(cosdf(m212_seaColorRot) * 32.0f + 32.0f));
    Hu3DModelEnvColorSet(object->model[0], 64, 32, 32, 0);
    if (omPauseChk() + omAllPauseF == 0) {
        m212_seaWaveRot += 0.5f;
        if (m212_seaWaveRot >= 360.0f) {
            m212_seaWaveRot -= 360.0f;
        }
        m212_seaScrollY += 0.2f;
        if (m212_seaScrollY >= 64.0f) {
            m212_seaScrollY -= 64.0f;
        }
        m212_seaColorRot += 2.4f;
        if (m212_seaColorRot >= 360.0f) {
            m212_seaColorRot -= 360.0f;
        }
    }
}

void m212_PlayerObjInit(omObjData *object) {
    s32 flags = 0x2B9;
    BabyBowserBroadsidePlayer *player;
    s16 i;
    s32 modelFile, motionFile;

    object->work[0] = mgPlayerObjNum;
    object->work[1] = mgPlayerObjNum + 3;
    player = &m212_playerTbl[object->work[0]];
    player->unk_02 = GwPlayer[object->work[0]].chr;
    modelFile = omCharModelNoTbl[player->unk_02][0];
    motionFile = omCharMotTbl[player->unk_02][0];
    MgPlayerCreate(object, modelFile, motionFile, (u16)object->work[0], flags, flags);
    object->trans.z = 200.0f;
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(player->unk_02, 0), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(player->unk_02, 2), 1, 0);
    MgPlayerMotLoad(object, 13, CharMotionDataNumGet(player->unk_02, 0x2F), 1, 999);
    if (player->unk_02 == 5) {
        MgPlayerMotLoad(object, 14, CharMotionDataNumGet(5, 0x38), 1, 999);
    } else {
        MgPlayerMotLoad(object, 14, CharMotionDataNumGet(player->unk_02, 0x37), 1, 999);
    }
    MgPlayerMotLoad(object, 38, CharMotionDataNumGet(player->unk_02, 0x27), 1, 0);
    MgPlayerMotLoad(object, 39, CharMotionDataNumGet(player->unk_02, 0x28), 1, 999);
    MgPlayerMotLoad(object, 40, CharMotionDataNumGet(player->unk_02, 0x28), 1, 999);
    m212_PlayerStateSet(player, 38, 1);
    player->unk_0C = -1;
    player->unk_00 = ((MgPlayerWork *)object->data)->unk57;
    player->unk_04 = 0x10000;
    player->unk_50 = m212_teamTbl[player->unk_5A].angles[player->unk_10];
    player->unk_4C = player->unk_50 + 180.0f;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    mgPlayerObjNum++;
    for (i = 0; i < 3; i++) {
        player->unk_54[i].unk_2C = HuMemAllocTag(sizeof(BabyBowserBroadsideMover), TAG_OVERLAY);
        m212_MoverInit(player->unk_54[i].unk_2C, 6, 40.0f, player->unk_54[i].unk_02);
        player->unk_54[i].unk_2C->unk_04[1] = m212_gameWork->unk_3C;
        player->unk_54[i].unk_2C->unk_04[2] = m212_gameWork->unk_46;
        player->unk_54[i].unk_2C->unk_04[3] = m212_gameWork->unk_3E[0];
        player->unk_54[i].unk_2C->unk_04[4] = m212_gameWork->unk_3E[1];
        player->unk_54[i].unk_2C->unk_04[5] = m212_gameWork->unk_3E[2];
        player->unk_54[i].unk_2C->unk_04[6] = m212_gameWork->unk_3E[3];
        Hu3DModelAttrSet(player->unk_54[i].unk_02, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    player->unk_5C = HuMemAllocTag(sizeof(BabyBowserBroadsideMover), TAG_OVERLAY);
    m212_MoverInit(player->unk_5C, 4, 50.0f, -1);
    player->unk_5C->unk_04[1] = m212_gameWork->unk_48[0];
    player->unk_5C->unk_04[2] = m212_gameWork->unk_48[1];
    player->unk_5C->unk_04[3] = m212_gameWork->unk_48[2];
    player->unk_5C->unk_04[4] = m212_gameWork->unk_48[3];
    m212_FuncGroupCreate(object, (s8)object->work[1], 0, 8);
    m212_FuncSet((s8)object->work[1], 0xF, (s32)player, m212_PlayerInputUpdate, 0);
    m212_FuncSet((s8)object->work[1], 0xCFFF, (s32)player, m212_PlayerMove, 0);
    m212_FuncSet((s8)object->work[1], 0xEFFF, (s32)player, m212_BallUpdate, 0);
    m212_FuncSet((s8)object->work[1], 0xFFFF, (s32)player, m212_PlayerMotUpdate, 0);
    object->func = m212_PlayerObjMain;
}

void m212_PlayerObjMain(omObjData *object) {
    m212_FuncGroupUpdate((s8)object->work[1]);
    MgPlayerMotUpdate(object);
}

void m212_CameraViewInit(void) {
    Center.x = 0.0f;
    Center.y = 215.0f;
    Center.z = -144.0f;
    CRot.x = 322.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2410.0f;
    m212_FuncReset(0);
}

void m212_ScoreUpdate(void) {
    s16 i;
    s16 ones, tens;

    for (i = 0; i < 2; i++) {
        if (m212_teamTbl[i].unk_10 < 100) {
            ones = m212_teamTbl[i].unk_10 % 10;
            tens = m212_teamTbl[i].unk_10 * 0.1f;
            HuSprPatNoSet(m212_sprTbl[m212_teamTbl[i].unk_12].unk_01, 0, tens);
            HuSprPatNoSet(m212_sprTbl[m212_teamTbl[i].unk_14].unk_01, 0, ones);
        } else {
            HuSprPatNoSet(m212_sprTbl[m212_teamTbl[i].unk_12].unk_01, 0, 9);
            HuSprPatNoSet(m212_sprTbl[m212_teamTbl[i].unk_14].unk_01, 0, 9);
        }
    }
}

void m212_TimerUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    if ((s8)handler->unk_04 == 0) {
        handler->unk_10 = 0;
        GMesCreate(GMES_MES_TIMER, m212_gameWork->unk_04 / 30.0f, 160, 28);
        handler->unk_04 = 1;
    }
    m212_gameWork->unk_04 -= 1.0f;
    GMesTimerValueSet((s16)((m212_gameWork->unk_04 + 29.0f) * (1.0f / 30.0f)));
    if (m212_gameWork->unk_04 < 0.0f) {
        m212_gameWork->unk_00 = 4;
        m212_gameWork->unk_38 = 0.0f;
        HuAudSeqFadeOut(120);
        GMesCreate(16);
        m212_FuncSet((s8)slot->unk_00->work[1], 0xF, 0, m212_FinishSeFade, 0);
        GMesTimerEnd();
        if (m212_teamTbl[0].unk_10 == m212_teamTbl[1].unk_10) {
            m212_FuncSet((s8)slot->unk_00->work[1], 0, 0, m212_DrawExec, 0);
        } else {
            m212_FuncSet((s8)slot->unk_00->work[1], 0, 0, m212_WinExec, 0);
        }
        m212_FuncReset((s8)slot->unk_00->work[1], handler);
    }
}

void m212_FinishSeFade(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    if ((s8)handler->unk_04 == 0) {
        handler->unk_1C = 0;
        handler->unk_1E = 0;
        handler->unk_04 = 1;
    }
    if (++handler->unk_1C >= 16) {
        handler->unk_1C = 15;
        HuAudFXAllFadeOut(15);
        m212_FuncReset((s8)slot->unk_00->work[1], handler);
    }
}

void m212_StartExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    s16 i;

    if ((s8)handler->unk_04 == 0) {
        m212_ambientSeNo = HuAudFXPlay(0x35C);
        HuAudFXVolSet(m212_ambientSeNo, 64);
        handler->unk_1C = 0;
        handler->unk_04 = 1;
    }
    switch (++handler->unk_1C) {
        case 20:
            GMesCreate(5);
            HuAudFXPlay(14);
            break;
        case 40:
            m212_startF = 1;
            break;
        default:
            if (m212_startF == 1 && GMesStatGet() == GMES_STAT_TIMEEND) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                        m212_FuncSet((s8)(i + 3), 0, (s32)&m212_playerTbl[i], m212_PlayerComInput, 0);
                    }
                }
                m212_FuncSet((s8)slot->unk_00->work[1], 0xF, 0, m212_TimerUpdate, 0);
                m212_gameWork->unk_38 = 0.5f;
                m212_gameWork->unk_00 = 2;
                m212_FuncReset((s8)slot->unk_00->work[1], handler);
            }
            break;
    }
    if (m212_musicF == 0 && GMesStatGet() != 0) {
        HuAudSeqPlay(48);
        m212_musicF = 1;
    }
}

void m212_WinExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    s16 i;
    s16 character1, character2;
    s16 player;

    if ((s8)handler->unk_04 == 0) {
        if (++handler->unk_1C > 40) {
            handler->unk_1C = 0;
            if (m212_teamTbl[0].unk_10 > m212_teamTbl[1].unk_10) {
                handler->unk_0C = 0;
            } else {
                handler->unk_0C = 1;
            }
            handler->unk_0D = !handler->unk_0C;
            for (i = 0; i < 2; i++) {
                player = m212_teamTbl[handler->unk_0C].players[i];
                m212_FuncSet((s8)(player + 3), 0xDFFF,
                                                    (s32)&m212_playerTbl[player], m212_PlayerWinExec, 0);
                player = m212_teamTbl[handler->unk_0D].players[i];
                m212_FuncSet((s8)(player + 3), 0xDFFF,
                                                    (s32)&m212_playerTbl[player], m212_PlayerLoseExec, 0);
            }
            handler->unk_04 = 1;
        }
    } else if (m212_winStep == 0) {
        if (GMesStatGet() == 0) {
            m212_winStep = 1;
        }
    } else if (m212_winStep >= 2) {
        if (GMesStatGet() == 0) {
            m212_winStep = 3;
        }
        if (m212_winStep == 3) {
            if (++handler->unk_1C >= 15) {
                m212_FuncSet((s8)slot->unk_00->work[1], 0, 0, m212_WipeExitExec, 0);
                m212_FuncReset((s8)slot->unk_00->work[1], handler);
            }
        }
    } else {
        if (++handler->unk_1C == 15) {
            character1 = m212_playerTbl[m212_teamTbl[handler->unk_0C].players[0]].unk_02;
            character2 = m212_playerTbl[m212_teamTbl[handler->unk_0C].players[1]].unk_02;
            HuAudSeqPlay(102);
            GMesCreate(GMES_MES_MG_WINNERS_2, character1, character2);
            GwPlayer[m212_teamTbl[handler->unk_0C].players[0]].bonusCoin += 10;
            GwPlayer[m212_teamTbl[handler->unk_0C].players[1]].bonusCoin += 10;
            m212_resultF = 1;
        }
        if (GMesStatGet() != 0) {
            handler->unk_1C = 0;
            m212_winStep = 2;
        }
    }
}

void m212_DrawExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    s16 i;

    if ((s8)handler->unk_04 == 0) {
        if (++handler->unk_1C > 40) {
            handler->unk_1C = 0;
            for (i = 0; i < 4; i++) {
                m212_FuncSet((s8)(i + 3), 0xDFFF, (s32)&m212_playerTbl[i], m212_PlayerLoseExec, 0);
            }
            handler->unk_04 = 1;
        }
    } else if (m212_drawStep == 0) {
        if (GMesStatGet() == 0) {
            m212_drawStep = 1;
        }
    } else if (m212_drawStep >= 2) {
        if (GMesStatGet() == 0) {
            m212_drawStep = 3;
        }
        if (m212_drawStep == 3) {
            if (++handler->unk_1C >= 15) {
                m212_FuncSet((s8)slot->unk_00->work[1], 0, 0, m212_WipeExitExec, 0);
                m212_FuncReset((s8)slot->unk_00->work[1], handler);
            }
        }
    } else {
        if (++handler->unk_1C == 15) {
            GMesCreate(GMES_MES_MG_DRAW);
            HuAudSeqPlay(108);
            m212_resultF = 1;
        }
        if (GMesStatGet() != 0) {
            handler->unk_1C = 0;
            m212_drawStep = 2;
        }
    }
}

void m212_WipeExitExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    switch ((s8)handler->unk_04) {
        case 0:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            handler->unk_04 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void m212_StageRotUpdate(BabyBowserBroadsideSlot *slot) {
    HmfModel *model = &Hu3DData[(s16)slot->unk_04[0]];

    if (m212_gameWork->unk_04 < 600.0f) {
        model->rot.y -= m212_gameWork->unk_38;
        if (model->rot.y < 0.0f) {
            model->rot.y += 360.0f;
        } else if (model->rot.y >= 360.0f) {
            model->rot.y -= 360.0f;
        }
    }
    model = &Hu3DData[(s16)slot->unk_04[2]];
    model->rot.y += m212_gameWork->unk_38;
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    } else if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
}

void m212_KoopaJrMove(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    HmfModel *model = &Hu3DData[m212_gameWork->unk_50];
    f32 startX, startZ, endX, endZ;
    f32 progress;

    if (m212_gameWork->unk_00 & 2) {
        startX = m212_koopaJrPosXTbl[m212_gameWork->unk_60];
        startZ = m212_koopaJrPosZTbl[m212_gameWork->unk_60];
        endX = m212_koopaJrPosXTbl[m212_gameWork->unk_61];
        endZ = m212_koopaJrPosZTbl[m212_gameWork->unk_61];
        progress = handler->unk_1C / 50.0f;
        progress = sindf(progress * 90.0f);
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        model->pos.x = startX + (endX - startX) * progress;
        model->pos.z = startZ + (endZ - startZ) * progress;
        if (++handler->unk_1C > 50) {
            model->pos.x = endX;
            model->pos.z = endZ;
            m212_gameWork->unk_60 = m212_gameWork->unk_61;
            handler->unk_1C = 0;
            while (1) {
                m212_gameWork->unk_61 = (s32)rand16() % 5;
                if (m212_gameWork->unk_60 == m212_gameWork->unk_61) {
                    continue;
                }
                if (m212_gameWork->unk_60 != 0) {
                    if (m212_gameWork->unk_60 - m212_gameWork->unk_61 > 0) {
                        if (m212_gameWork->unk_60 - m212_gameWork->unk_61 != 2) {
                            break;
                        }
                        continue;
                    } else if (m212_gameWork->unk_61 - m212_gameWork->unk_60 == 2) {
                        continue;
                    }
                }
                break;
            }
        }
        Hu3DData[(s16)slot->unk_04[4]].pos.x = model->pos.x;
        Hu3DData[(s16)slot->unk_04[4]].pos.z = model->pos.z;
        Hu3DModelPosSet((s16)slot->unk_04[5], model->pos.x, 450.0f, model->pos.z);
    }
}

void m212_KoopaJrShakeUpdate(void) {
    f32 tiltX, tiltZ;
    f32 angle;
    f32 progress;

    if (m212_gameWork->unk_52 != 0) {
        m212_gameWork->unk_28 += 15.0f;
        tiltX = sindf(m212_gameWork->unk_28) * 30.0f * m212_gameWork->unk_58;
        tiltZ = -(sindf(m212_gameWork->unk_28) * 30.0f * m212_gameWork->unk_5C);
        Hu3DData[m212_gameWork->unk_50].rot.x = tiltX;
        Hu3DData[m212_gameWork->unk_50].rot.z = tiltZ;
        if (m212_gameWork->unk_28 >= 360.0f) {
            m212_gameWork->unk_28 -= 360.0f;
            progress = m212_gameWork->unk_18 / 6.0f;
            progress = sindf(progress * 90.0f);
            if (progress > 1.0f) {
                progress = 1.0f;
            }
            angle = progress * 90.0f;
            m212_gameWork->unk_58 = cosdf(angle) * m212_gameWork->unk_58;
            m212_gameWork->unk_5C = cosdf(angle) * m212_gameWork->unk_5C;
            if (++m212_gameWork->unk_18 > 6) {
                m212_gameWork->unk_52 = 0;
            }
        }
    }
}

void m212_CannonMotReset(s16 arg0) {
    Hu3DData[arg0].motSpeed = 1.0f;
    Hu3DData[arg0].motTime = 0.0f;
}

void m212_KoopaJrShakeStart(f32 angle) {
    m212_gameWork->unk_58 = cosdf(angle);
    m212_gameWork->unk_5C = sindf(angle);
    m212_gameWork->unk_52 = 1;
    m212_gameWork->unk_18 = 0;
    m212_gameWork->unk_28 = 0;
}

void m212_PlayerComInput(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &Hu3DData[m212_gameWork->unk_50];
    f32 angle, currentAngle, targetAngle;
    f32 tolerance;
    f32 x, z;
    s32 random;

    if ((s8)handler->unk_04 == 0) {
        switch (GwPlayer[object->work[0]].cpu_difficulty) {
            case 0:
                handler->unk_0D = 3;
                handler->unk_0E = 10;
                handler->unk_0F = 4;
                handler->unk_10 = 15;
                handler->unk_11 = 5;
                handler->unk_12 = 3;
                handler->unk_13 = 3;
                handler->unk_14 = 5;
                break;
            case 1:
                handler->unk_0D = 5;
                handler->unk_0E = 15;
                handler->unk_0F = 6;
                handler->unk_10 = 10;
                handler->unk_11 = 3;
                handler->unk_12 = 6;
                handler->unk_13 = 6;
                handler->unk_14 = 8;
                break;
            case 2:
                handler->unk_0D = 10;
                handler->unk_0E = 20;
                handler->unk_0F = 8;
                handler->unk_10 = 5;
                handler->unk_11 = 1;
                handler->unk_12 = 9;
                handler->unk_13 = 9;
                handler->unk_14 = 13;
                break;
            case 3:
                handler->unk_0D = 15;
                handler->unk_0E = 25;
                handler->unk_0F = 10;
                handler->unk_10 = 3;
                handler->unk_11 = 0;
                handler->unk_12 = 99;
                handler->unk_13 = 99;
                handler->unk_14 = 99;
                break;
        }
        handler->unk_1C = 0;
        handler->unk_1E = 30;
        handler->unk_04 = 1;
    }
    HuPadStkX[player->unk_00] = 0;
    HuPadStkY[player->unk_00] = 0;
    HuPadBtn[player->unk_00] = 0;
    player->unk_10 = 0;
    x = model->pos.x - object->trans.x;
    z = model->pos.z - object->trans.z;
    angle = atan2df(-z, x) + 90.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    currentAngle = player->unk_4C;
    targetAngle = angle;
    m212_AngleDiffMinimize(&currentAngle, &targetAngle);
    switch (handler->unk_0C) {
        case 0:
            tolerance = (s32)rand16() % 4 + 2;
            if ((currentAngle - targetAngle > 0.0f ? currentAngle - targetAngle : -(currentAngle - targetAngle)) < tolerance) {
                if ((s16)m212_ComShotHitCheck(object, player) != 0) {
                    random = (s32)rand16() % 6;
                    handler->unk_1C = (s8)(u8)handler->unk_0F + random;
                    handler->unk_0C = 1;
                    handler->unk_2C = m212_gameWork->unk_38 > 0.0f ? 2.0f : -2.0f;
                    if ((s32)rand16() % (handler->unk_12 + 1) == 0) {
                        handler->unk_2C = -handler->unk_2C;
                    }
                } else {
                    handler->unk_1C = (s32)rand16() % (handler->unk_0E - handler->unk_0D + 1) + handler->unk_0D;
                    handler->unk_0C = 2;
                }
            } else if ((s32)rand16() % (handler->unk_13 + 1) != 0) {
                if (currentAngle - targetAngle > 0.0f) {
                    player->unk_4C -= 2.0f;
                } else if (currentAngle - targetAngle < 0.0f) {
                    player->unk_4C += 2.0f;
                }
            }
            break;
        case 1:
            if (--handler->unk_1C > 0) {
                player->unk_4C -= handler->unk_2C;
            } else {
                handler->unk_0C = 0;
            }
            if ((s32)rand16() % (handler->unk_11 + 1) == 0) {
                if ((s16)m212_ComShotHitCheck(object, player) == 0) {
                    ((u16 *)HuPadBtn)[player->unk_00] = A_BUTTON;
                }
            }
            break;
        case 2:
            if (--handler->unk_1E < 0) {
                handler->unk_1E = (s32)rand16() % (handler->unk_10 + 1);
                if (currentAngle - targetAngle > 0.0f) {
                    player->unk_4C -= 2.0f;
                } else if (currentAngle - targetAngle < 0.0f) {
                    player->unk_4C += 2.0f;
                }
            }
            if ((s16)m212_ComShotHitCheck(object, player) == 0) {
                if (--handler->unk_1C <= 0) {
                    handler->unk_0C = 0;
                } else if ((s32)rand16() % (handler->unk_11 + 1) == 0) {
                    ((u16 *)HuPadBtn)[player->unk_00] = A_BUTTON;
                }
            }
            break;
        case 3:
            if (--handler->unk_1C < 0) {
                player->unk_4C += handler->unk_2C;
            } else {
                handler->unk_0C = 0;
            }
            break;
    }
}

s32 m212_ComShotHitCheck(omObjData *object, BabyBowserBroadsidePlayer *player) {
    player->unk_5C->pos.x = object->trans.x;
    player->unk_5C->pos.y = 500.0f;
    player->unk_5C->pos.z = object->trans.z;
    player->unk_5C->facing.x = sindf(player->unk_4C) * 20.0f * 5.0f * 8.0f;
    player->unk_5C->facing.y = 0.0f;
    player->unk_5C->facing.z = cosdf(player->unk_4C) * 20.0f * 5.0f * 8.0f;
    m212_MoverUpdate(player->unk_5C);
    return player->unk_5C->unk_2A != 0;
}

void m212_PlayerInputUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    s16 index;
    f32 stickX, stickY;
    f32 angle;
    f32 currentAngle, targetAngle;

    if (m212_gameWork->unk_00 & 2) {
        if (--player->unk_58 < 0) {
            player->unk_58 = 0;
        }
        if ((u16)HuPadBtn[player->unk_00] & A_BUTTON) {
            if (player->unk_58 == 0 && player->unk_10 == 0) {
                player->unk_10 = 1;
                index = m212_BallFreeGet(player);
                if (index != -1) {
                    if (handler->unk_0C != 0) {
                        handler->unk_0C = 0;
                        m212_PlayerStateSet(player, 40, 1);
                    } else {
                        handler->unk_0C = 1;
                        m212_PlayerStateSet(player, 39, 1);
                    }
                    m212_CannonMotReset(player->unk_48);
                    m212_PlayerNextStateSet(player, 38);
                    player->unk_58 = 10;
                    player->unk_04 = (index + 1) | player->unk_04;
                }
            }
        } else {
            player->unk_10 = 0;
        }
        stickX = HuPadStkX[player->unk_00];
        stickY = HuPadStkY[player->unk_00];
        if ((stickX == 0.0f) & (stickY == 0.0f)) {
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        } else {
            angle = atan2df(stickY, stickX) + 90.0f;
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            currentAngle = player->unk_4C;
            targetAngle = angle;
            m212_AngleDiffMinimize(&currentAngle, &targetAngle);
            if ((currentAngle - targetAngle > 0.0f ? currentAngle - targetAngle : -(currentAngle - targetAngle)) < 5.0f) {
                return;
            }
            if (currentAngle - targetAngle > 0.0f) {
                player->unk_4C -= 2.0f;
            } else if (currentAngle - targetAngle < 0.0f) {
                player->unk_4C += 2.0f;
            }
        }
    }
}

void m212_PlayerMove(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    f32 sinAngle, cosAngle;
    f32 targetAngle, currentAngle;

    if (!(m212_gameWork->unk_00 & 4)) {
        if (m212_gameWork->unk_04 < 600.0f) {
            player->unk_50 -= m212_gameWork->unk_38;
        }
        if (player->unk_50 >= 360.0f) {
            player->unk_50 -= 360.0f;
        } else if (player->unk_50 < 0.0f) {
            player->unk_50 += 360.0f;
        }
        sinAngle = sindf(player->unk_50);
        cosAngle = cosdf(player->unk_50);
        sinAngle *= 550.0f;
        cosAngle *= 550.0f;
        Hu3DModelPosSet(player->unk_48, sinAngle, 400.0f, cosAngle);
        object->trans.x = sinAngle;
        object->trans.y = 455.0f;
        object->trans.z = cosAngle;
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 2.5f, cosAngle);
        targetAngle = player->unk_50 + 180.0f;
        if (targetAngle > 360.0f) {
            targetAngle -= 360.0f;
        }
        if (player->unk_4C >= 360.0f) {
            player->unk_4C -= 360.0f;
        } else if (player->unk_4C < 0.0f) {
            player->unk_4C += 360.0f;
        }
        currentAngle = player->unk_4C;
        m212_AngleDiffMinimize(&targetAngle, &currentAngle);
        if (targetAngle - currentAngle > 30.0f) {
            player->unk_4C = targetAngle - 30.0f;
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        } else if (targetAngle - currentAngle < -30.0f) {
            player->unk_4C = targetAngle + 30.0f;
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        }
        Hu3DModelRotSet(player->unk_48, 0.0f, player->unk_4C, 0.0f);
        object->rot.y = player->unk_4C;
    }
}

void m212_BallUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    BabyBowserBroadsideBall *entry = player->unk_54;
    s16 i = 0;
    s16 index;

    if ((u16)player->unk_04 != 0) {
        i = (u16)player->unk_04;
        m212_BallFire(object, &player->unk_54[(s16)(i - 1)], player->unk_4C, player->unk_5A);
        player->unk_04 &= 0xFFFF0000;
        HuAudFXPlay(0x35A);
    }
    for (i = 0; i < 3; i++, entry++) {
        if (entry->unk_00 != 0) {
            entry->unk_2C->facing.x = entry->velocity.x;
            entry->unk_2C->facing.y = entry->velocity.y;
            entry->unk_2C->facing.z = entry->velocity.z;
            m212_MoverUpdate(entry->unk_2C);
            entry->elapsed += 1.0f;
            entry->velocity.y = entry->initialVelocityY - entry->elapsed * 2.45f;
            if (entry->unk_2C->unk_2A != 0) {
                m212_BallKill(entry);
            } else if (entry->unk_2C->unk_30 != 0) {
                HuAudFXPlay(0x35B);
                m212_BallKill(entry);
                index = m212_AnimMdlFreeGet(entry->unk_28 + 2);
                if (index != -1) {
                    m212_AnimMdlDispOn(index, entry->unk_2C->pos.x, entry->unk_2C->pos.y, entry->unk_2C->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                }
                if (m212_gameWork->unk_00 & 2) {
                    m212_teamTbl[player->unk_5A].unk_10++;
                }
                m212_KoopaJrShakeStart(entry->angle);
            }
            if (!(entry->unk_2C->unk_00 & 1)) {
                m212_BallKill(entry);
            }
        }
    }
}

void m212_BallKill(BabyBowserBroadsideBall *entry) {
    s16 index = m212_AnimMdlFreeGet(entry->unk_28);

    m212_AnimMdlDispOn(index, entry->unk_2C->pos.x, entry->unk_2C->pos.y, entry->unk_2C->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    Hu3DModelAttrSet(entry->unk_02, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    entry->unk_00 = 0;
}

s16 m212_BallFreeGet(BabyBowserBroadsidePlayer *arg0) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (arg0->unk_54[i].unk_00 == 0) {
            break;
        }
    }
    if (i == 3) {
        return -1;
    }
    return i;
}

void m212_BallFire(omObjData *object, BabyBowserBroadsideBall *entry, f32 angle, s16 team) {
    f32 sinAngle, cosAngle;
    f32 x, z;
    s16 index;
    u8 color[4];

    sinAngle = sindf(angle);
    cosAngle = cosdf(angle);
    x = sinAngle * 100.0f;
    z = cosAngle * 100.0f;
    Hu3DModelPosSet(entry->unk_02, x + object->trans.x, 500.0f, z + object->trans.z);
    entry->velocity.x = entry->unk_04.x = sinAngle * 50.0f;
    entry->velocity.y = sindf(22.5f) * 30.000002f;
    entry->velocity.z = entry->unk_04.z = cosAngle * 50.0f;
    entry->initialVelocityY = entry->velocity.y;
    entry->elapsed = 0.0f;
    entry->angle = angle;
    entry->unk_00 = 1;
    Hu3DModelAttrSet(entry->unk_02, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    x = sinAngle * 180.0f;
    z = cosAngle * 180.0f;
    entry->unk_28 = team;
    index = m212_BillboardFreeGet(0);
    if (index != -1) {
        if (team == 0) {
            color[0] = 255;
            color[1] = 191;
            color[2] = 191;
            color[3] = 255;
        } else {
            color[0] = 165;
            color[1] = 204;
            color[2] = 229;
            color[3] = 255;
        }
        m212_BillboardDispOn(index, x + object->trans.x, 469.99997f, z + object->trans.z, color);
    }
    omVibrate(object->work[0], 10, 0, 10);
}

void m212_PlayerWinExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    f32 progress;

    if ((s8)handler->unk_04 == 0) {
        handler->unk_1C = 0;
        handler->unk_2C = object->rot.y;
        handler->unk_30 = 0.0f;
        m212_AngleDiffMinimize(&handler->unk_2C, &handler->unk_30);
        m212_PlayerStateSet(player, 2, 1);
        player->unk_0C = -1;
        handler->unk_04 = 1;
    }
    progress = handler->unk_1C / 20.0f;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    object->rot.y = (handler->unk_30 - handler->unk_2C) * progress + handler->unk_2C;
    if (++handler->unk_1C > 20.0f) {
        m212_PlayerStateSet(player, 0, 1);
        object->rot.y = 0.0f;
        handler->unk_1C = 20;
        if (m212_resultF != 0) {
            m212_PlayerStateSet(player, 13, 1);
            m212_FuncReset((s8)object->work[1], handler);
        }
    }
}

void m212_PlayerLoseExec(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;

    if (m212_resultF != 0) {
        m212_PlayerStateSet(player, 14, 1);
        player->unk_0C = -1;
        m212_FuncReset((s8)object->work[1], handler);
    }
}

void m212_PlayerMotUpdate(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideFunc *handler) {
    BabyBowserBroadsidePlayer *player = (BabyBowserBroadsidePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (model->motTime >= Hu3DMotion[model->motId].unk02 - 1) {
        player->unk_08 = 1;
    }
    if (player->unk_08 != 0) {
        MgPlayerMotSet(object, player->unk_0A);
        if (player->unk_0A == 13) {
            HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[object->work[0]].chr][0] | 0x2F);
        }
        player->unk_08 = 0;
        if (player->unk_0C != -1) {
            player->unk_0A = player->unk_0C;
            player->unk_0C = -1;
        }
    }
}

void m212_PlayerStateSet(BabyBowserBroadsidePlayer *player, s16 motion, s8 arg2) {
    player->unk_08 = arg2;
    player->unk_0A = motion;
}

void m212_PlayerNextStateSet(BabyBowserBroadsidePlayer *arg0, s16 arg1) {
    arg0->unk_0C = arg1;
}
