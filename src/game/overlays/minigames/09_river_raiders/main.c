#include "common.h"
#include "math.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/hmfanim.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/overlays/minigame.h"

typedef struct RiverRaidersEntry {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 sprite;
    /* 0x42 */ s16 esp;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ Vec unk_78;
} RiverRaidersEntry; // sizeof 0x84

typedef struct RiverRaidersCamera {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} RiverRaidersCamera; // sizeof 0x2C

// Group of misaligned variables (see undefined_syms.txt for aliases).
typedef struct RiverRaidersSkierState {
    /* 0x00 */ s16 unk00; // m209_skierSeNo
    /* 0x02 */ u8 unk02[3]; // m209_skierLaneTbl
    /* 0x05 */ u8 unk05; // m209_skierCoin
    /* 0x06 */ s16 unk06; // m209_skierSwayDir
} RiverRaidersSkierState; // sizeof 0x08

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern const s16 m209_fontMesTbl[];

s16 m209_coinSe = 9;
s16 m209_coinBagSe = 21;
s16 m209_logHitSe = 833;
s16 m209_engineSe = 832;
s32 m209_riverMdlTbl[3] = { 0x2A0001, 0x2A0002, 0x2A0003 };
f32 m209_riverZTbl[3] = { 0.0f, -1875.0f, -3750.0f };
s32 m209_chrIconTbl[8] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
/* Unreferenced. */
s32 m209_chrMotTbl[8][6][2] = {
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
    { { 0, 39 }, { 0, 40 }, { 0, 79 }, { 0, 80 }, { 0, 81 }, { 0, 82 } },
};
f32 m209_ropeOfsTbl[4][3][16] = {
    {
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        { 25.8971f, 25.8421f, 25.4961f, 24.9248f, 24.2387f, 23.5411f, 22.9655f, 22.6184f,
          22.6072f, 22.8636f, 23.3336f, 23.9238f, 24.5449f, 25.1392f, 25.6064f, 25.8727f },
        { 4.7879f, 4.7879f, 4.78129f, 4.7774f, 4.78282f, 4.7879f, 4.78844f, 4.78837f,
          4.7882f, 4.78802f, 4.7879f, 4.78789f, 4.78789f, 4.7879f, 4.7879f, 4.7879f },
    },
    {
        { -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f,
          -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f, -5.64f },
        { 25.276f, 25.228f, 24.884f, 24.3064f, 23.614f, 22.92f, 22.3436f, 22.0046f,
          21.9955f, 22.2599f, 22.724f, 23.3036f, 23.9172f, 24.5033f, 24.9819f, 25.24f },
        { 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f,
          4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f },
    },
    {
        { 5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f,
          5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f, 5.896f },
        { 25.212f, 25.1642f, 24.8196f, 24.2434f, 23.5528f, 22.86f, 22.2838f, 21.9449f,
          21.9278f, 22.2038f, 22.664f, 23.2423f, 23.859f, 24.4433f, 24.9074f, 25.176f },
        { 4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f,
          4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f, 4.764f },
    },
    {
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        { 25.468f, 25.4198f, 25.0776f, 24.4899f, 23.7667f, 23.044f, 22.4632f, 22.1069f,
          22.1678f, 22.5799f, 23.224f, 23.9554f, 24.683f, 25.3047f, 25.7288f, 25.895f },
        { -6.648f, -6.6128f, -6.26563f, -5.69009f, -4.95789f, -4.096f, -3.1391f, -2.26568f,
          -1.44279f, -0.398738f, 0.74f, 1.91003f, 2.99774f, 3.91425f, 4.52865f, 4.768f },
    },
};
Vec2f m209_skierIconPosTbl[3] = {
    { 200.0f, 210.0f },
    { 215.0f, 200.0f },
    { 230.0f, 210.0f },
};
Vec2f m209_scorePosTbl[8] = {
    { 50.0f, 210.0f },
    { 70.0f, 210.0f },
    { 80.0f, 210.0f },
    { 90.0f, 210.0f },
    { 250.0f, 210.0f },
    { 270.0f, 210.0f },
    { 280.0f, 210.0f },
    { 290.0f, 210.0f },
};
RiverRaidersCamera m209_cameraViewTbl[1] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 36.0f },
};

f32 m209_wakeRotTbl[5] BSS;
s16 m209_skierHopTimer BSS;
u8 m209_finishStep BSS;
u8 m209_finishStepPad[8] BSS; /* Unreferenced. */
RiverRaidersEntry m209_objWorkTbl[100] BSS;
u8 m209_logCnt BSS;
u8 m209_coinCnt BSS;
s16 m209_coinBagSide BSS;
u8 m209_boatCoin BSS;
s16 m209_starEffGrp BSS;
u16 m209_waterTexSize[2] BSS;
u8 m209_waterTexSizePad[4] BSS; /* Unreferenced. */
u8 m209_phase BSS;
u8 m209_skierLaneCnt BSS;
u8 m209_skierLaneCntPad[4] BSS; /* Unreferenced. */
s16 m209_skierHitTbl[3][5] BSS;
s16 m209_logMotLen BSS;
RiverRaidersSkierState m209_skierState BSS;
u8 m209_coinBagCnt BSS;
u8 m209_coinBagCntPad[4] BSS; /* Unreferenced. */
f32 m209_skierRangeTbl[3][2] BSS;
s16 m209_engineSeNo BSS;
s16 m209_timer BSS;
s16 m209_enginePitch BSS;

// m209_wakeRotTbl[3] onward (see undefined_syms.txt).
extern f32 m209_boatWakeRotTbl[2];
// Entries and entry fields of m209_objWorkTbl, accessed through
// separate symbols (see undefined_syms.txt).
extern RiverRaidersEntry m209_skierWorkTbl[]; // &[6]
extern s16 m209_boatSteerDir; // [9].unk_04
extern s16 m209_boatStunTimer; // [9].unk_06
extern s16 m209_boatIconSpr; // [9].sprite
extern s16 m209_boatIconEsp; // [9].esp
extern RiverRaidersEntry m209_itemWorkTbl[]; // &[10]
extern f32 m209_waterScroll; // [40].unk_18
// Aliases into m209_skierState (see undefined_syms.txt).
extern s16 m209_skierSeNo;
extern u8 m209_skierLaneTbl[];
extern u8 m209_skierCoin;
extern s16 m209_skierSwayDir;

void m209_ScoreObjMain(omObjData *obj);
void m209_ScoreObjInit(omObjData *obj);
void m209_RiverObjMain(omObjData *obj);
void m209_RiverObjInit(omObjData *obj);
void m209_WaterObjMain(omObjData *obj);
void m209_RopeObjMain(omObjData *obj);
void m209_RopeObjInit(omObjData *obj);
void m209_BoatComInputCalc(omObjData *obj);
void m209_BoatComInput(omObjData *obj);
void m209_BoatPadInput(omObjData *obj);
void m209_BoatSteer(omObjData *obj);
void m209_BoatObjMain(omObjData *obj);
void m209_WaterObjInit(omObjData *);
void m209_BoatObjInit(omObjData *);
void m209_ItemHitUpdate(omObjData *obj);
void m209_ItemObjMain(omObjData *obj);
void m209_ItemObjInit(omObjData *obj);
void m209_SkierObjCreateAll(void);
void m209_MainObjMain(omObjData *obj);
void m209_MainObjInit(omObjData *obj);
void m209_ObjectSetup(void);

void m209_Executor(void) {
    m209_ObjectSetup();
}

f32 m209_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m209_ObjWorkInit(void) {
    u32 i;
    RiverRaidersEntry *entry;

    for (i = 0, entry = m209_objWorkTbl; i < 100; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
        entry->sprite = -1;
        entry->esp = -1;
        entry->pos.x = entry->pos.y = entry->pos.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68 = 0.0f;
        entry->unk_6C = 0.0f;
        entry->unk_70 = 0.0f;
        entry->unk_74 = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void m209_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m209_PhaseSet(u8 arg0) {
    m209_phase = arg0;
}

f32 m209_GravityCalc(f32 arg0, f32 *arg1, f32 arg2) {
    f32 prev = *arg1;

    *arg1 = prev - arg2;
    return arg0 + prev;
}

void m209_ScoreObjMain(omObjData *obj) {
    u32 row = obj->work[0] * 4;
    u32 col = obj->work[1] + 43;
    RiverRaidersEntry *entry = &m209_objWorkTbl[row + col];

    switch (obj->work[0]) {
        case 0:
            if (obj->work[1] == 2) {
                if (m209_boatCoin / 10 != 0) {
                    espDispOn(entry->esp);
                    espPatNoSet(entry->esp, (u8)(m209_boatCoin / 10));
                }
            } else if (obj->work[1] == 3) {
                espPatNoSet(entry->esp, (u8)(m209_boatCoin % 10));
            }
            break;
        case 1:
            if (obj->work[1] == 2) {
                if (m209_skierCoin / 10 != 0) {
                    espDispOn(entry->esp);
                    espPatNoSet(entry->esp, (u8)(m209_skierCoin / 10));
                }
            } else if (obj->work[1] == 3) {
                espPatNoSet(entry->esp, (u8)(m209_skierCoin % 10));
            }
            break;
    }
}

void m209_ScoreObjInit(omObjData *obj) {
    u32 row = obj->work[0] * 4;
    u32 col = obj->work[1] + 43;
    RiverRaidersEntry *entry = &m209_objWorkTbl[row + col];

    switch (obj->work[1]) {
        case 0:
            entry->sprite = HuSprAnimDataRead(0x2A0013);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, HUSPR_ATTR_XLU);
            break;
        case 1:
            entry->sprite = HuSprAnimDataRead(0x2A0012);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, HUSPR_ATTR_XLU);
            break;
        case 2:
        case 3:
            entry->sprite = HuSprAnimDataRead(0x31);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, HUSPR_ATTR_XLU);
            if (obj->work[1] == 2) {
                espDispOff(entry->esp);
            }
            break;
    }
    entry->pos.x = m209_scorePosTbl[obj->work[0] * 4 + obj->work[1]].x;
    entry->pos.y = m209_scorePosTbl[obj->work[0] * 4 + obj->work[1]].y;
    espPosSet(entry->esp, entry->pos.x, entry->pos.y);
    obj->func = m209_ScoreObjMain;
}

void m209_ScoreObjCreateAll(void) {
    RiverRaidersEntry *entry;
    s32 row;
    s32 col;
    omObjData *obj;
    s16 i;
    s16 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            row = i * 4;
            col = j + 43;
            entry = &m209_objWorkTbl[row + col];
            obj = omAddObj(0x3DE, 1, 10, -1, m209_ScoreObjInit);
            obj->work[0] = i;
            obj->work[1] = j;
            entry->obj = obj;
        }
    }
}

void m209_RiverObjMain(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_objWorkTbl[obj->work[0]];
    RiverRaidersEntry *cur;
    s16 i;

    obj->trans.z += 17.0f;
    if (obj->work[0] == 2) {
        for (i = 0; i < 3; i++) {
            cur = &m209_objWorkTbl[i];
            obj = cur->obj;
            if (obj->trans.z >= 1875.0f) {
                switch (i) {
                    case 0:
                        entry = &m209_objWorkTbl[2];
                        break;
                    case 1:
                        entry = &m209_objWorkTbl[0];
                        break;
                    case 2:
                        entry = &m209_objWorkTbl[1];
                        break;
                }
                obj->trans.z = entry->obj->trans.z - 1875.0f;
            }
        }
    }
}

void m209_RiverObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(m209_riverMdlTbl[obj->work[0]], 0x288);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = m209_riverZTbl[obj->work[0]];
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    obj->func = m209_RiverObjMain;
}

void m209_RiverObjCreateAll(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &m209_objWorkTbl[i];
        obj = omAddObj(0x1F4, 1, 10, -1, m209_RiverObjInit);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m209_WaterObjMain(omObjData *obj) {
    RiverRaidersEntry *water = &m209_objWorkTbl[40];

    if (omPauseChk() + omAllPauseF == 0) {
        m209_waterScroll += 1.5f;
    }
    Hu3DModelObjTexScroll(obj->model[0], 0.0f, water->unk_18, m209_waterTexSize[0],
                       m209_waterTexSize[1], "suki-m209_04_1_3", 0);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void m209_WaterObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2A0004, 0x2A8);
    Hu3DModelTPLvlInit(obj->model[0]);
    Hu3DModelTPLvlSet(obj->model[0], 0x80);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelVtxBufMake(obj->model[0]);
    Hu3DTexSizeGet("209_water_00_DEF", m209_waterTexSize);
    m209_waterScroll = 0.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->func = m209_WaterObjMain;
}

void m209_WaterObjCreate(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, m209_WaterObjInit);
    obj->work[0] = 0;
    m209_objWorkTbl[40].obj = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m209_RopeObjMain(omObjData *obj) {
    omObjData *player = m209_objWorkTbl[9].obj;
    RiverRaidersEntry *entry;
    omObjData *boat;
    f32 x, y, z;
    f32 dx, dy, dz;
    f32 rotY, rotX;
    f32 dist;
    s16 frame;
    u8 i;

    x = y = z = 0.0f;
    for (i = 0; i < 3; i++) {
        entry = &m209_objWorkTbl[i + 6];
        boat = entry->obj;
        if (boat->work[2] != obj->work[0]) {
            continue;
        }
        switch (entry->unk_08) {
            case 0:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -m209_ropeOfsTbl[0][0][frame] * 5.0f + boat->trans.x;
                y = m209_ropeOfsTbl[0][1][frame] * 5.0f + boat->trans.y;
                z = -m209_ropeOfsTbl[0][2][frame] * 5.0f + boat->trans.z + 20.0f;
                break;
            case 1:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -m209_ropeOfsTbl[1][0][frame] * 5.0f + boat->trans.x;
                y = m209_ropeOfsTbl[1][1][frame] * 5.0f + boat->trans.y;
                z = -m209_ropeOfsTbl[1][2][frame] * 5.0f + boat->trans.z;
                break;
            case 2:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -m209_ropeOfsTbl[2][0][frame] * 5.0f + boat->trans.x;
                y = m209_ropeOfsTbl[2][1][frame] * 5.0f + boat->trans.y;
                z = -m209_ropeOfsTbl[2][2][frame] * 5.0f + boat->trans.z;
                break;
            case 3:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -m209_ropeOfsTbl[3][0][frame] * 5.0f + boat->trans.x;
                y = m209_ropeOfsTbl[3][1][frame] * 5.0f + boat->trans.y;
                z = -m209_ropeOfsTbl[3][2][frame] * 5.0f + boat->trans.z + 20.0f;
                break;
        }
        dx = x - player->trans.x;
        dy = y - (player->trans.y + 15.0f);
        dz = z - (player->trans.z + 60.0f);
        rotY = atan2df(dx, dz);
        rotX = atan2df(dy, sqrtf(dx * dx + dz * dz));
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        obj->rot.y = 0.0f;
        obj->scale.z = dist / 450.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
        obj->rot.y = rotY;
        obj->rot.x = -rotX;
        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->trans.x = player->trans.x;
        obj->trans.y = player->trans.y + 15.0f;
        obj->trans.z = player->trans.z + 60.0f;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void m209_RopeObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2A0000, 0x99);
    obj->trans.x = 0.0f;
    obj->trans.y = 15.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    obj->func = m209_RopeObjMain;
}

void m209_RopeObjCreateAll(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &m209_objWorkTbl[i + 3];
        obj = omAddObj(0x320, 1, 10, -1, m209_RopeObjInit);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m209_BoatComInputCalc(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_objWorkTbl[9];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *target;
    f32 dx, dz;
    f32 dist;
    f32 minDist;
    s16 best;
    s16 i;
    u8 dir;

    best = 0;
    minDist = 5000.0f;
    // The loop end note stops CSE from folding entry into an absolute address below.
    do {
        dir = 0;
    } while (0);
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else {
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (entry->unk_06 < 31) {
        dir = rand8();
        if (((GwPlayer[player].cpu_difficulty == 0) & (dir < 30)) || ((GwPlayer[player].cpu_difficulty == 1) & (dir < 150)) ||
            ((GwPlayer[player].cpu_difficulty == 2) & (dir < 200)) || ((GwPlayer[player].cpu_difficulty == 3) & (dir < 255))) {
            // Dead stores; this switch only leaves behind the cpu_difficulty load seen in the target.
            switch (GwPlayer[player].cpu_difficulty) {
                case 0:
                    dist = 100.0f;
                    break;
                case 1:
                    dist = 150.0f;
                    break;
                case 2:
                    dist = 200.0f;
                    break;
                case 3:
                    dist = 300.0f;
                    break;
            }
            for (i = 19; i >= 0; i--) {
                cur = &m209_itemWorkTbl[i];
                target = cur->obj;
                dx = target->trans.x - obj->trans.x;
                dz = target->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (target->trans.z < obj->trans.z && target->trans.z > -1500.0f) {
                    if ((cur->unk_04 == 1) & (dist < minDist)) {
                        best = i;
                        minDist = dist;
                    }
                }
            }
            target = m209_itemWorkTbl[best].obj;
            if (target->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < target->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= target->trans.x + 50.0f + 30.0f && target->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
            minDist = 5000.0f;
            for (i = 23; i >= 20; i--) {
                cur = &m209_itemWorkTbl[i];
                target = cur->obj;
                dx = target->trans.x - obj->trans.x;
                dz = target->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (target->trans.z < obj->trans.z && target->trans.z > -1500.0f) {
                    if ((cur->unk_04 == 1) & (dist < minDist)) {
                        best = i;
                        minDist = dist;
                    }
                }
            }
            target = m209_itemWorkTbl[best].obj;
            if (target->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < target->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= target->trans.x + 50.0f + 30.0f && target->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
        }
    }
    if (--entry->unk_0A <= 0) {
        entry->unk_0A = 0;
    }
    if (dir == 0) {
        entry->unk_04 = 0;
    }
    if (dir % 5 == 1 && entry->unk_0A == 0) {
        entry->unk_04 = 1;
        entry->unk_0A = 30;
    }
    if (dir % 5 == 2 && entry->unk_0A == 0) {
        entry->unk_04 = 2;
        entry->unk_0A = 30;
    }
}

void m209_BoatComInput(omObjData *obj) {
    m209_BoatComInputCalc(obj);
}

void m209_BoatPadInput(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_objWorkTbl[9];
    u16 player = obj->work[0];

    m209_boatSteerDir = 0;
    if (--m209_boatStunTimer <= 0) {
        m209_boatStunTimer = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else {
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (entry->unk_06 < 31) {
        if (HuPadStkX[GwPlayer[player].pad] < -29) {
            entry->unk_04 = 1;
        }
        if (HuPadStkX[GwPlayer[player].pad] >= 30) {
            entry->unk_04 = 2;
        }
    }
}

void m209_BoatSteer(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_objWorkTbl[9];

    switch (m209_boatSteerDir) {
        case 0:
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = m209_AngleAdd(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = m209_AngleAdd(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (entry->unk_06 < 31) {
                if (entry->unk_08 == 1) {
                    Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                    entry->unk_08 = 0;
                }
            } else {
                m209_enginePitch = -500;
                if (entry->unk_08 == 0) {
                    Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[1]].motId, 0, 1, 0);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 1, 0);
                    entry->unk_08 = 1;
                }
            }
            if (entry->unk_18 < 0.0f) {
                entry->unk_18 += 0.05;
            }
            if (entry->unk_18 > 0.0f) {
                entry->unk_18 -= 0.05;
            }
            if ((s16)entry->unk_18 == 0) {
                entry->unk_18 = 0.0f;
                obj->trans.x = (s16)obj->trans.x;
            }
            if (m209_boatWakeRotTbl[1] < 0.0f) {
                m209_boatWakeRotTbl[1] += 1.0f;
            }
            if (m209_boatWakeRotTbl[1] > 0.0f) {
                m209_boatWakeRotTbl[1] -= 1.0f;
            }
            if ((s16)m209_boatWakeRotTbl[1] == 0) {
                m209_boatWakeRotTbl[1] = 0.0f;
            }
            m209_enginePitch -= 5;
            if (m209_enginePitch < -300) {
                m209_enginePitch = -300;
            }
            break;
        case 1:
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                entry->unk_08 = 0;
            }
            obj->rot.z = m209_AngleAdd(obj->rot.z, 1.0f);
            if ((s16)obj->rot.z == 20.0f) {
                obj->rot.z = 19.0f;
            }
            if (entry->unk_18 > -5.0f) {
                entry->unk_18 -= 0.1f;
                if (entry->unk_18 < -5.0f) {
                    entry->unk_18 = -5.0f;
                }
            }
            m209_boatWakeRotTbl[1] += 1.0f;
            if (m209_boatWakeRotTbl[1] >= 10.0f) {
                m209_boatWakeRotTbl[1] = 10.0f;
            }
            m209_enginePitch += 5;
            if (m209_enginePitch > 0) {
                m209_enginePitch = 0;
            }
            break;
        case 2:
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                entry->unk_08 = 0;
            }
            obj->rot.z = m209_AngleAdd(obj->rot.z, -1.0f);
            if ((s16)obj->rot.z == 340.0f) {
                obj->rot.z = 341.0f;
            }
            if (entry->unk_18 < 5.0f) {
                entry->unk_18 += 0.1f;
                if (entry->unk_18 > 5.0f) {
                    entry->unk_18 = 5.0f;
                }
            }
            m209_boatWakeRotTbl[1] -= 1.0f;
            if (m209_boatWakeRotTbl[1] <= -10.0f) {
                m209_boatWakeRotTbl[1] = -10.0f;
            }
            m209_enginePitch += 5;
            if (m209_enginePitch > 0) {
                m209_enginePitch = 0;
            }
            break;
    }
    if (obj->trans.x + entry->unk_18 + 60.0f >= 580.0f || obj->trans.x + entry->unk_18 - 60.0f <= -580.0f) {
        entry->unk_18 = 0.0f;
    }
    obj->trans.x += entry->unk_18;
    if (m209_engineSeNo != -1) {
        HuAudFXPitchSet(m209_engineSeNo, m209_enginePitch);
    }
    m209_skierRangeTbl[0][0] = obj->trans.x - 450.0f;
    m209_skierRangeTbl[0][1] = obj->trans.x + 150.0f;
    m209_skierRangeTbl[1][0] = obj->trans.x - 300.0f;
    m209_skierRangeTbl[1][1] = obj->trans.x + 300.0f;
    m209_skierRangeTbl[2][0] = obj->trans.x - 150.0f;
    m209_skierRangeTbl[2][1] = obj->trans.x + 450.0f;
}

void m209_BoatObjMain(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_objWorkTbl[9];
    u16 player = obj->work[0];

    if (m209_phase == 10) {
        if (m209_engineSeNo != -1) {
            HuAudFXFadeOut(m209_engineSeNo, 30);
            m209_engineSeNo = -1;
        }
    } else if (m209_engineSeNo == -1) {
        m209_engineSeNo = HuAudFXPlay(m209_engineSe);
    }
    switch (m209_phase) {
        case 0:
        case 1:
            m209_enginePitch = -300;
            if (m209_engineSeNo != -1) {
                HuAudFXPitchSet(m209_engineSeNo, -300);
            }
            break;
        case 2:
            if (m209_timer > 0) {
                if (GwPlayer[player].stat & PLAYER_IS_CPU) {
                    m209_BoatComInput(obj);
                } else {
                    m209_BoatPadInput(obj);
                }
                m209_BoatSteer(obj);
            }
            break;
        case 3:
            m209_enginePitch = -300;
            if (m209_engineSeNo != -1) {
                HuAudFXPitchSet(m209_engineSeNo, -300);
            }
            entry->unk_1C = 10.0f;
            if (++entry->unk_0C >= 20) {
                m209_finishStep = 3;
            }
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = m209_AngleAdd(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = m209_AngleAdd(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                entry->unk_08 = 0;
            }
            if (m209_boatWakeRotTbl[1] < 0.0f) {
                m209_boatWakeRotTbl[1] += 1.0f;
            }
            if (m209_boatWakeRotTbl[1] > 0.0f) {
                m209_boatWakeRotTbl[1] -= 1.0f;
            }
            if ((s16)m209_boatWakeRotTbl[1] == 0) {
                m209_boatWakeRotTbl[1] = 0.0f;
            }
            break;
        case 5:
        case 10:
            if (m209_boatCoin != 0) {
                if (entry->unk_16 == 0) {
                    PlayerFXPlay(0x28F, obj->work[0]);
                    entry->unk_16 = 1;
                }
                if (entry->unk_0E <= 0) {
                    obj->trans.y = m209_GravityCalc(obj->trans.y, &entry->unk_1C, 1.0f);
                    if (entry->unk_1C < -10.0f) {
                        entry->unk_1C = 10.0f;
                        entry->unk_0E = 5;
                    }
                }
                if (entry->unk_0E > 0) {
                    entry->unk_0E--;
                }
                if (obj->trans.y <= 1.0f) {
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                } else {
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
            }
            break;
    }
    switch (GwPlayer[obj->work[0]].chr) {
        case 0:
        case 1:
        case 6:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z + 40.0f);
            break;
        default:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
            break;
    }
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, m209_boatWakeRotTbl[0], obj->rot.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], obj->rot.x, m209_boatWakeRotTbl[1], 0.0f);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[4], obj->rot.x, obj->rot.y, obj->rot.z);
}

void m209_BoatObjInit(omObjData *obj) {
    s8 chr = GwPlayer[obj->work[0]].chr;

    obj->model[5] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1], 0x6A9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x27));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x28));
    Hu3DMotionModelSet(obj->model[5], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[5], 0.0f);
    Hu3DMotionAttrSet(obj->model[5], 2, 2);
    Hu3DModelRemakeStatic(obj->model[5]);
    Hu3DModelDynamicFree(obj->model[5]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = Hu3DModelRead(0x2A0008, 0x4B9);
    omObjMotionRead(obj, 2, 0x2A0009);
    omObjMotionRead(obj, 3, 0x2A000A);
    Hu3DMotionModelSet(obj->model[1], obj->motion[2]);
    Hu3DMotionTimeSet(obj->model[1], 0.0f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[2] = Hu3DModelRead(0x2A0010, 0x4A9);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    obj->model[3] = Hu3DModelRead(0x2A0011, 0x4A9);
    Hu3DMotionAttrSet(obj->model[3], 2, 2);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[4] = Hu3DModelRead2(0, 0x4A9);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelScaleSet(obj->model[4], 2.0f, 2.0f, 2.0f);
    Hu3DModelObjAttrSet(obj->model[4], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[4]);
    Hu3DModelDynamicFree(obj->model[4]);
    m209_boatIconSpr = HuSprAnimDataRead(m209_chrIconTbl[chr]);
    m209_boatIconEsp = espEntry(m209_boatIconSpr, 0, 0);
    espAttrSet(m209_boatIconEsp, HUSPR_ATTR_XLU);
    espPosSet(m209_boatIconEsp, 30, 210);
    espScaleSet(m209_boatIconEsp, 1.0f, 1.0f);
    m209_enginePitch = -300;
    obj->func = m209_BoatObjMain;
}

void m209_BoatObjCreate(void) {
    omObjData *obj;
    s16 i;
    u16 playerIndex = 0;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            continue;
        }
        switch (i) {
            case 0:
                playerIndex = 0;
                break;
            case 1:
                playerIndex = 1;
                break;
            case 2:
                playerIndex = 2;
                break;
            case 3:
                playerIndex = 3;
                break;
        }
        obj = omAddObj(0x2BC, 9, 0x3C, -1, m209_BoatObjInit);
        obj->work[0] = playerIndex;
        m209_objWorkTbl[9].obj = obj;
    }
}

void m209_SkierHitCheck(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    RiverRaidersEntry *cur;
    omObjData *other;
    f32 x;
    s16 hit;
    s16 i;
    s16 j;

    for (i = 0; i < 5; i++) {
        m209_skierHitTbl[obj->work[1]][i] = 0;
    }
    x = obj->trans.x + entry->unk_18;
    entry->unk_12 = 0;
    if (x - 65.0f < m209_skierRangeTbl[obj->work[2]][0]) {
        m209_skierHitTbl[obj->work[1]][3] = 1;
    }
    if (x + 65.0f > m209_skierRangeTbl[obj->work[2]][1]) {
        m209_skierHitTbl[obj->work[1]][3] = 2;
    }
    hit = 0;
    for (i = 0; i < 3; i++) {
        if (i != obj->work[1]) {
            cur = &m209_skierWorkTbl[i];
            other = cur->obj;
            switch (entry->unk_08) {
                case 1:
                    if (x + 65.0f + entry->unk_12 * 4.5f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                case 2:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f - entry->unk_12 * 4.5f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                default:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
            }
            if (hit == 1) {
                break;
            }
        }
    }
    hit = 0;
    for (j = 0; j < 3; j++) {
        if (j != obj->work[1] && j != i) {
            other = m209_skierWorkTbl[j].obj;
            switch (entry->unk_08) {
                case 1:
                    if (x + 65.0f + entry->unk_12 * 4.5f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                case 2:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f - entry->unk_12 * 4.5f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                default:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        m209_skierHitTbl[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
            }
            if (hit == 1) {
                break;
            }
        }
    }
    if (x + 65.0f > 580.0f) {
        m209_skierHitTbl[obj->work[1]][4] = 1;
    }
    if (x - 65.0f < -580.0f) {
        m209_skierHitTbl[obj->work[1]][4] = 2;
    }
}

void m209_SkierPushCalc(void) {
    RiverRaidersEntry *entry;
    RiverRaidersEntry *other;
    omObjData *obj;
    omObjData *otherObj;
    s16 iter;
    s16 changed;
    s16 count;
    s16 i;
    s16 j;

    iter = 0;
    do {
        changed = 0;
        for (i = 0; i < 3; i++) {
            entry = &m209_skierWorkTbl[i];
            obj = entry->obj;
            for (j = 0; j < 3; j++) {
                if (j == i) {
                    continue;
                }
                if (m209_skierHitTbl[i][j] != 1) {
                    continue;
                }
                other = &m209_skierWorkTbl[j];
                otherObj = other->obj;
                if (other->unk_18 < 0.5f && other->unk_18 > -0.5f && m209_skierHitTbl[j][3] == 0 &&
                    m209_skierHitTbl[j][4] == 0) {
                    other->unk_18 = entry->unk_18;
                    changed = 1;
                }
                if (obj->trans.x > otherObj->trans.x) {
                    if (entry->unk_18 < 0.0f) {
                        entry->unk_18 = -entry->unk_18;
                        changed = 1;
                    } else if (entry->unk_18 < 0.5f && entry->unk_18 > -0.5f) {
                        entry->unk_18 = fabsf(other->unk_18);
                        changed = 1;
                    }
                } else {
                    if (entry->unk_18 > 0.0f) {
                        entry->unk_18 = -entry->unk_18;
                        changed = 1;
                    } else if (entry->unk_18 < 0.5f && entry->unk_18 > -0.5f) {
                        entry->unk_18 = -fabs(other->unk_18);
                        changed = 1;
                    }
                }
            }
            for (j = 0, count = 0; j < 3; j++) {
                if (j != i && m209_skierHitTbl[i][j] == 1) {
                    count++;
                }
            }
            if (count >= 2) {
                changed = 1;
            }
            if (m209_skierHitTbl[obj->work[1]][3] == 1) {
                obj->trans.x = m209_skierRangeTbl[obj->work[2]][0] + 65.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (m209_skierHitTbl[obj->work[1]][3] == 2) {
                obj->trans.x = m209_skierRangeTbl[obj->work[2]][1] - 65.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (m209_skierHitTbl[obj->work[1]][4] == 1) {
                obj->trans.x = 515.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (m209_skierHitTbl[obj->work[1]][4] == 2) {
                obj->trans.x = -515.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            m209_SkierHitCheck(obj);
        }
    } while (++iter < 21 && changed != 0);
    for (i = 0; i < 3; i++) {
        entry = &m209_skierWorkTbl[i];
        obj = entry->obj;
        obj->trans.x += entry->unk_18;
    }
}

void m209_SkierComInputCalc(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *target;
    f32 range;
    s16 i;
    u8 dir;

    range = 0.0f;
    dir = 0;
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (entry->unk_06 == 0) {
        dir = rand8();
        if (((GwPlayer[player].cpu_difficulty == 0) & (dir < 100)) ||
            ((GwPlayer[player].cpu_difficulty == 1) & (dir < 150)) ||
            ((GwPlayer[player].cpu_difficulty == 2) & (dir < 200)) ||
            ((GwPlayer[player].cpu_difficulty == 3) & (dir < 255))) {
            switch (GwPlayer[player].cpu_difficulty) {
                case 0:
                    range = 100.0f;
                    break;
                case 1:
                    range = 150.0f;
                    break;
                case 2:
                    range = 200.0f;
                    break;
                case 3:
                    range = 300.0f;
                    break;
            }
            for (i = 19; i >= 0; i--) {
                cur = &m209_itemWorkTbl[i];
                target = cur->obj;
                if (target->trans.z < obj->trans.z && target->trans.x < range + obj->trans.x &&
                    obj->trans.x - range < target->trans.x && cur->unk_04 == 1) {
                    if (target->trans.x < obj->trans.x) {
                        dir = 1;
                    }
                    if (target->trans.x > obj->trans.x) {
                        dir = 2;
                    }
                }
            }
            for (i = 23; i >= 20; i--) {
                cur = &m209_itemWorkTbl[i];
                target = cur->obj;
                if (target->trans.z < obj->trans.z && target->trans.x < range + obj->trans.x &&
                    obj->trans.x - range < target->trans.x && cur->unk_04 == 1 && target->trans.z > -100.0f) {
                    if (target->trans.x < obj->trans.x) {
                        dir = 1;
                    }
                    if (target->trans.x > obj->trans.x) {
                        dir = 2;
                    }
                }
            }
        }
    }
    if (--entry->unk_0A <= 0) {
        entry->unk_0A = 0;
    }
    if (dir == 0) {
        entry->unk_04 = 0;
    }
    if (dir % 5 == 1 && entry->unk_0A == 0) {
        entry->unk_04 = 1;
        entry->unk_0A = 30;
    }
    if (dir % 5 == 2 && entry->unk_0A == 0) {
        entry->unk_04 = 2;
        entry->unk_0A = 30;
    }
}

void m209_SkierComInput(omObjData *obj) {
    m209_SkierComInputCalc(obj);
}

void m209_SkierPadInput(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    u16 player = obj->work[0];

    entry->unk_04 = 0;
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (entry->unk_06 == 0) {
        if (HuPadStkX[GwPlayer[player].pad] < -29) {
            entry->unk_04 = 1;
        }
        if (HuPadStkX[GwPlayer[player].pad] >= 30) {
            entry->unk_04 = 2;
        }
    }
}

void m209_SkierSteer(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    omObjData *player = m209_skierWorkTbl[3].obj;

    switch (entry->unk_04) {
        case 0:
            if (entry->unk_06 <= 0) {
                if (entry->unk_08 != 0) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 2);
                    entry->unk_08 = 0;
                    entry->unk_12 = 0;
                }
            } else if (entry->unk_08 != 3) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 10, 1);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 1);
                entry->unk_08 = 3;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 < 0.0f) {
                entry->unk_18 += 0.05;
            }
            if (entry->unk_18 > 0.0f) {
                entry->unk_18 -= 0.05;
            }
            if ((s16)entry->unk_18 == 0 && entry->unk_18 < 0.3f && entry->unk_18 > -0.3f) {
                if (((f32)obj->work[2] - 1.0f) * 300.0f + player->trans.x < obj->trans.x) {
                    entry->unk_18 = -0.5f;
                }
                if (((f32)obj->work[2] - 1.0f) * 300.0f + player->trans.x > obj->trans.x) {
                    entry->unk_18 = 0.5f;
                }
            }
            if (m209_wakeRotTbl[obj->work[1]] < 0.0f) {
                m209_wakeRotTbl[obj->work[1]] += 1.0f;
            }
            if (m209_wakeRotTbl[obj->work[1]] > 0.0f) {
                m209_wakeRotTbl[obj->work[1]] -= 1.0f;
            }
            if ((s16)m209_wakeRotTbl[obj->work[1]] == 0) {
                m209_wakeRotTbl[obj->work[1]] = 0.0f;
            }
            break;
        case 1:
            if (entry->unk_08 != 2) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 2);
                entry->unk_08 = 2;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 > -7.0f) {
                entry->unk_18 -= 0.3f;
                if (entry->unk_18 < -7.0f) {
                    entry->unk_18 = -7.0f;
                }
            }
            m209_wakeRotTbl[obj->work[1]] += 3.0f;
            if (m209_wakeRotTbl[obj->work[1]] >= 20.0f) {
                m209_wakeRotTbl[obj->work[1]] = 20.0f;
            }
            break;
        case 2:
            if (entry->unk_08 != 1) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
                entry->unk_08 = 1;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 < 7.0f) {
                entry->unk_18 += 0.3f;
                if (entry->unk_18 > 7.0f) {
                    entry->unk_18 = 7.0f;
                }
            }
            m209_wakeRotTbl[obj->work[1]] -= 3.0f;
            if (m209_wakeRotTbl[obj->work[1]] <= -20.0f) {
                m209_wakeRotTbl[obj->work[1]] = -20.0f;
            }
            break;
    }
    m209_SkierHitCheck(obj);
}

void m209_SkierObjMain(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *boat;
    s16 i;

    switch (m209_phase) {
        case 2:
            if (m209_timer > 0) {
                if (GwPlayer[player].stat & PLAYER_IS_CPU) {
                    m209_SkierComInput(obj);
                } else {
                    m209_SkierPadInput(obj);
                }
                m209_SkierSteer(obj);
            }
            break;
        case 3:
            entry->unk_1C = 10.0f;
            if (entry->unk_08 != 0) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 2);
                entry->unk_08 = 0;
            }
            if (m209_wakeRotTbl[obj->work[1]] < 0.0f) {
                m209_wakeRotTbl[obj->work[1]] += 1.0f;
            }
            if (m209_wakeRotTbl[obj->work[1]] > 0.0f) {
                m209_wakeRotTbl[obj->work[1]] -= 1.0f;
            }
            if ((s16)m209_wakeRotTbl[obj->work[1]] == 0) {
                m209_wakeRotTbl[obj->work[1]] = 0.0f;
            }
            break;
        case 5:
        case 10:
            if (m209_skierCoin != 0) {
                if (entry->unk_16 == 0) {
                    PlayerFXPlay(0x28F, obj->work[0]);
                    entry->unk_16 = 1;
                }
                switch (m209_skierSwayDir) {
                    case -1:
                        if (entry->unk_08 != 2) {
                            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 2);
                            entry->unk_08 = 2;
                        }
                        if (m209_skierHopTimer > 0) {
                            obj->trans.x -= 10.0f;
                        } else {
                            obj->trans.x -= 0.0f;
                        }
                        m209_wakeRotTbl[obj->work[1]] += 3.0f;
                        if (m209_wakeRotTbl[obj->work[1]] >= 20.0f) {
                            m209_wakeRotTbl[obj->work[1]] = 20.0f;
                        }
                        break;
                    case 1:
                        if (entry->unk_08 != 1) {
                            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
                            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
                            entry->unk_08 = 1;
                        }
                        if (m209_skierHopTimer > 0) {
                            obj->trans.x += 10.0f;
                        } else {
                            obj->trans.x += 0.0f;
                        }
                        m209_wakeRotTbl[obj->work[1]] -= 3.0f;
                        if (m209_wakeRotTbl[obj->work[1]] <= -20.0f) {
                            m209_wakeRotTbl[obj->work[1]] = -20.0f;
                        }
                        break;
                }
                if (obj->trans.y <= 1.0f) {
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                } else {
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                if (obj->work[1] == 2) {
                    if (--m209_skierHopTimer <= 0) {
                        for (i = 0; i < 3; i++) {
                            cur = &m209_skierWorkTbl[i];
                            boat = cur->obj;
                            boat->trans.y = m209_GravityCalc(boat->trans.y, &cur->unk_1C, 1.0f);
                        }
                        m209_skierHopTimer = 0;
                        if ((s16)obj->trans.y == 0.0f) {
                            for (i = 0; i < 3; i++) {
                                cur = &m209_skierWorkTbl[i];
                                cur->unk_1C = 10.0f;
                            }
                            m209_skierHopTimer = 30;
                        }
                    }
                    for (i = 0; i < 3; i++) {
                        cur = &m209_skierWorkTbl[i];
                        boat = cur->obj;
                        if (boat->work[2] == 0 && boat->trans.x - 65.0f <= -580.0f) {
                            m209_skierSwayDir = 1;
                        }
                        if (boat->work[2] == 2 && boat->trans.x + 65.0f >= 580.0f) {
                            m209_skierSwayDir = -1;
                        }
                    }
                }
            }
            if (m209_skierCoin == 0) {
                if (entry->unk_08 != 3) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 10, 1);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 1);
                    entry->unk_08 = 3;
                }
                switch (m209_skierSwayDir) {
                    case -1:
                        entry->unk_0C++;
                        obj->trans.x -= 3.0f;
                        m209_wakeRotTbl[obj->work[1]] += 3.0f;
                        if (m209_wakeRotTbl[obj->work[1]] >= 20.0f) {
                            m209_wakeRotTbl[obj->work[1]] = 20.0f;
                        }
                        break;
                    case 1:
                        entry->unk_0C++;
                        obj->trans.x += 3.0f;
                        m209_wakeRotTbl[obj->work[1]] -= 3.0f;
                        if (m209_wakeRotTbl[obj->work[1]] <= -20.0f) {
                            m209_wakeRotTbl[obj->work[1]] = -20.0f;
                        }
                        break;
                }
                if (obj->work[1] == 2) {
                    for (i = 0; i < 3; i++) {
                        cur = &m209_skierWorkTbl[i];
                        boat = cur->obj;
                        if (boat->work[2] == 0 && boat->trans.x - 65.0f <= -580.0f) {
                            m209_skierSwayDir = 1;
                            entry->unk_0C = 0;
                        }
                        if (boat->work[2] == 2 && boat->trans.x + 65.0f >= 580.0f) {
                            m209_skierSwayDir = -1;
                            entry->unk_0C = 0;
                        }
                    }
                    if (entry->unk_0C >= 30) {
                        m209_skierSwayDir *= -1;
                        for (i = 0; i < 3; i++) {
                            entry->unk_0C = 0;
                        }
                    }
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, m209_wakeRotTbl[obj->work[1]], obj->rot.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], obj->rot.x, obj->rot.y, obj->rot.z);
}

void m209_SkierObjInit(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_skierWorkTbl[obj->work[1]];
    s8 chr = GwPlayer[obj->work[0]].chr;
    u8 lane;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1], 0x6A9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x4F));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x50));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x51));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x52));
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    lane = rand8() % 3;
    while (TRUE) {
        if (lane != m209_skierLaneTbl[0] && lane != m209_skierLaneTbl[1]) {
            obj->work[2] = lane;
            m209_skierLaneTbl[m209_skierLaneCnt] = lane;
            m209_skierLaneCnt++;
            switch (obj->work[2]) {
                case 0:
                    obj->trans.x = -300.0f;
                    break;
                case 1:
                    obj->trans.x = 0.0f;
                    break;
                case 2:
                    obj->trans.x = 300.0f;
                    break;
            }
            break;
        }
        lane = (lane + 1) % 3;
    }
    obj->trans.y = 0.0f;
    obj->trans.z = 600.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = Hu3DModelRead(0x2A000B, 0x4B9);
    omObjMotionRead(obj, 4, 0x2A000C);
    omObjMotionRead(obj, 5, 0x2A000D);
    omObjMotionRead(obj, 6, 0x2A000E);
    omObjMotionRead(obj, 7, 0x2A000F);
    Hu3DMotionModelSet(obj->model[1], obj->motion[4]);
    Hu3DMotionTimeSet(obj->model[1], 0.0f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[2] = Hu3DModelRead(0x2A0011, 0x4A9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 0.5f, 1.0f, 0.5f);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    obj->model[3] = Hu3DModelRead2(0, 0x4A9);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    Hu3DModelObjAttrSet(obj->model[3], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[3]);
    Hu3DModelDynamicFree(obj->model[3]);
    entry->sprite = HuSprAnimDataRead(m209_chrIconTbl[chr]);
    entry->esp = espEntry(entry->sprite, 0, 0);
    espAttrSet(entry->esp, HUSPR_ATTR_XLU);
    espPosSet(entry->esp, m209_skierIconPosTbl[obj->work[2]].x, m209_skierIconPosTbl[obj->work[2]].y);
    espScaleSet(entry->esp, 1.0f, 1.0f);
    obj->func = m209_SkierObjMain;
}

void m209_SkierObjCreateAll(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    u16 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            continue;
        }
        switch (i) {
            case 0:
                playerIndex = 0;
                break;
            case 1:
                playerIndex = 1;
                break;
            case 2:
                playerIndex = 2;
                break;
            case 3:
                playerIndex = 3;
                break;
        }
        entry = &m209_skierWorkTbl[count];
        obj = omAddObj(0x2EE, 9, 0x3C, -1, m209_SkierObjInit);
        obj->work[0] = playerIndex;
        obj->work[1] = count++;
        entry->obj = obj;
    }
}

// The original calls EffectGroupEmit without its float prototype, passing integer zeros. Calling
// through an unprototyped function pointer reproduces that.
void m209_ItemHitUpdate(omObjData *obj) {
    RiverRaidersEntry *entries[3];
    omObjData *boats[3];
    RiverRaidersEntry *entry = &m209_objWorkTbl[obj->work[0] + 10];
    RiverRaidersEntry *big = &m209_objWorkTbl[9];
    omObjData *bigObj = big->obj;
    RiverRaidersEntry *other;
    omObjData *otherObj;
    f32 speed;
    f32 nextZ;
    s16 model;
    s16 i;

    for (i = 0; i < 3; i++) {
        entries[i] = &m209_skierWorkTbl[i];
        boats[i] = entries[i]->obj;
    }
    switch (obj->work[1]) {
        case 0:
            nextZ = obj->trans.z + 7.0f;
            speed = 7.0f;
            for (i = 0; i < 30; i++) {
                if (obj->work[0] == i) {
                    continue;
                }
                other = &m209_itemWorkTbl[i];
                otherObj = other->obj;
                entry->unk_0A = 0;
                if (i < 20) {
                    if (other->unk_04 == 1 && otherObj->trans.x + 50.0f >= obj->trans.x - 50.0f &&
                        otherObj->trans.x - 50.0f <= obj->trans.x + 50.0f && otherObj->trans.z + 50.0f >= nextZ - 50.0f &&
                        otherObj->trans.z - 50.0f <= nextZ + 50.0f) {
                        entry->unk_0A = 1;
                        if (entry->unk_06 == 0) {
                            if (otherObj->trans.x >= obj->trans.x) {
                                entry->unk_08 = 1;
                            } else {
                                entry->unk_08 = 2;
                            }
                            entry->unk_06 = 1;
                        }
                        switch (entry->unk_08) {
                            case 1:
                                obj->trans.x -= 5.0f;
                                if (obj->trans.x - 50.0f <= -580.0f) {
                                    obj->trans.x += 5.0f;
                                    entry->unk_08 = 2;
                                }
                                break;
                            case 2:
                                obj->trans.x += 5.0f;
                                if (obj->trans.x + 50.0f >= 580.0f) {
                                    obj->trans.x -= 5.0f;
                                    entry->unk_08 = 1;
                                }
                                break;
                        }
                    }
                }
                if (i >= 20 && i < 24) {
                    if (other->unk_04 == 1 && otherObj->trans.x + 40.0f >= obj->trans.x - 50.0f &&
                        otherObj->trans.x - 40.0f <= obj->trans.x + 50.0f && otherObj->trans.z + 40.0f >= nextZ - 50.0f &&
                        otherObj->trans.z - 40.0f <= nextZ + 50.0f) {
                        entry->unk_0A = 1;
                        if (entry->unk_06 == 0) {
                            if (otherObj->trans.x >= obj->trans.x) {
                                entry->unk_08 = 1;
                            } else {
                                entry->unk_08 = 2;
                            }
                            entry->unk_06 = 1;
                        }
                        switch (entry->unk_08) {
                            case 1:
                                obj->trans.x -= 5.0f;
                                if (obj->trans.x - 50.0f <= -580.0f) {
                                    obj->trans.x += 5.0f;
                                    entry->unk_08 = 2;
                                }
                                break;
                            case 2:
                                obj->trans.x += 5.0f;
                                if (obj->trans.x + 50.0f >= 580.0f) {
                                    obj->trans.x -= 5.0f;
                                    entry->unk_08 = 1;
                                }
                                break;
                        }
                        speed = 10.0f;
                    }
                }
                if (i >= 24) {
                    if (other->unk_04 == 1 && otherObj->trans.x + 150.0f >= obj->trans.x - 50.0f &&
                        otherObj->trans.x - 150.0f <= obj->trans.x + 50.0f && otherObj->trans.z + 60.0f >= nextZ - 50.0f &&
                        otherObj->trans.z - 60.0f <= nextZ + 50.0f) {
                        entry->unk_0A = 1;
                        if (entry->unk_06 == 0) {
                            if (otherObj->trans.x >= obj->trans.x) {
                                entry->unk_08 = 1;
                            } else {
                                entry->unk_08 = 2;
                            }
                            entry->unk_06 = 1;
                        }
                        switch (entry->unk_08) {
                            case 1:
                                obj->trans.x -= 5.0f;
                                if (obj->trans.x - 50.0f <= -580.0f) {
                                    obj->trans.x += 5.0f;
                                    entry->unk_08 = 2;
                                }
                                break;
                            case 2:
                                obj->trans.x += 5.0f;
                                if (obj->trans.x + 50.0f >= 580.0f) {
                                    obj->trans.x -= 5.0f;
                                    entry->unk_08 = 1;
                                }
                                break;
                        }
                        speed = 13.0f;
                    }
                }
            }
            if (entry->unk_0A == 0) {
                entry->unk_06 = 0;
            }
            obj->trans.z = speed + obj->trans.z;
            if (m209_phase == 2) {
                if (big->unk_06 == 0 && bigObj->trans.x + 60.0f >= obj->trans.x - 50.0f &&
                    bigObj->trans.x - 60.0f <= obj->trans.x + 50.0f && bigObj->trans.z + 60.0f >= obj->trans.z - 50.0f &&
                    bigObj->trans.z - 60.0f <= obj->trans.z + 50.0f) {
                    if (entry->unk_04 == 1) {
                        s16 (*effectCreate)() = (void *)EffectGroupEmit;

                        m209_boatCoin++;
                        model = effectCreate(m209_starEffGrp, 0, 0, 0);
                        HuAudPlayerFXPlay(m209_coinSe, bigObj->work[0]);
                        Hu3DModelPosSet(model, obj->trans.x, obj->trans.y, obj->trans.z);
                        Hu3DModelScaleSet(model, 3.0f, 3.0f, 3.0f);
                    }
                    entry->unk_04 = 0;
                    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                for (i = 0; i < 3; i++) {
                    if (entries[i]->unk_06 == 0 && boats[i]->trans.x + 65.0f >= obj->trans.x - 50.0f &&
                        boats[i]->trans.x - 65.0f <= obj->trans.x + 50.0f && boats[i]->trans.z + 55.0f >= obj->trans.z - 50.0f &&
                        boats[i]->trans.z - 55.0f <= obj->trans.z + 50.0f) {
                        if (entry->unk_04 == 1) {
                            s16 (*effectCreate)() = (void *)EffectGroupEmit;

                            m209_skierCoin++;
                            model = effectCreate(m209_starEffGrp, 0, 0, 0);
                            HuAudPlayerFXPlay(m209_coinSe, boats[i]->work[0]);
                            Hu3DModelPosSet(model, obj->trans.x, obj->trans.y, obj->trans.z);
                            Hu3DModelScaleSet(model, 3.0f, 3.0f, 3.0f);
                        }
                        entry->unk_04 = 0;
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            break;
        case 1:
            nextZ = obj->trans.z + 10.0f;
            speed = 10.0f;
            for (i = 0; i < 30; i++) {
                if (obj->work[0] == i) {
                    continue;
                }
                other = &m209_itemWorkTbl[i];
                otherObj = other->obj;
                entry->unk_0A = 0;
                if (i >= 20 && i < 24) {
                    if (other->unk_04 == 1 && otherObj->trans.x + 40.0f >= obj->trans.x - 40.0f &&
                        otherObj->trans.x - 40.0f <= obj->trans.x + 40.0f && otherObj->trans.z + 40.0f >= nextZ - 40.0f &&
                        otherObj->trans.z - 40.0f <= nextZ + 40.0f) {
                        entry->unk_0A = 1;
                        if (entry->unk_06 == 0) {
                            if (otherObj->trans.x >= obj->trans.x) {
                                entry->unk_08 = 1;
                            } else {
                                entry->unk_08 = 2;
                            }
                            entry->unk_06 = 1;
                        }
                        switch (entry->unk_08) {
                            case 1:
                                obj->trans.x -= 5.0f;
                                if (obj->trans.x - 40.0f <= -580.0f) {
                                    obj->trans.x += 5.0f;
                                    entry->unk_08 = 2;
                                }
                                break;
                            case 2:
                                obj->trans.x += 5.0f;
                                if (obj->trans.x + 40.0f >= 580.0f) {
                                    obj->trans.x -= 5.0f;
                                    entry->unk_08 = 1;
                                }
                                break;
                        }
                    }
                }
                if (i >= 24) {
                    if (other->unk_04 == 1 && otherObj->trans.x + 150.0f >= obj->trans.x - 40.0f &&
                        otherObj->trans.x - 150.0f <= obj->trans.x + 40.0f && otherObj->trans.z + 60.0f >= nextZ - 40.0f &&
                        otherObj->trans.z - 60.0f <= nextZ + 40.0f) {
                        entry->unk_0A = 1;
                        if (entry->unk_06 == 0) {
                            if (otherObj->trans.x >= obj->trans.x) {
                                entry->unk_08 = 1;
                            } else {
                                entry->unk_08 = 2;
                            }
                            entry->unk_06 = 1;
                        }
                        switch (entry->unk_08) {
                            case 1:
                                obj->trans.x -= 5.0f;
                                if (obj->trans.x - 40.0f <= -580.0f) {
                                    obj->trans.x += 5.0f;
                                    entry->unk_08 = 2;
                                }
                                break;
                            case 2:
                                obj->trans.x += 5.0f;
                                if (obj->trans.x + 40.0f >= 580.0f) {
                                    obj->trans.x -= 5.0f;
                                    entry->unk_08 = 1;
                                }
                                break;
                        }
                        speed = 13.0f;
                    }
                }
            }
            if (entry->unk_0A == 0) {
                entry->unk_06 = 0;
            }
            obj->trans.z = speed + obj->trans.z;
            if (m209_phase == 2) {
                if (big->unk_06 == 0 && bigObj->trans.x + 60.0f >= obj->trans.x - 40.0f &&
                    bigObj->trans.x - 60.0f <= obj->trans.x + 40.0f && bigObj->trans.z + 60.0f >= obj->trans.z - 40.0f &&
                    bigObj->trans.z - 60.0f <= obj->trans.z + 40.0f) {
                    if (entry->unk_04 == 1) {
                        s16 (*effectCreate)() = (void *)EffectGroupEmit;

                        m209_boatCoin += 5;
                        model = effectCreate(m209_starEffGrp, 0, 0, 0);
                        HuAudPlayerFXPlay(m209_coinBagSe, bigObj->work[0]);
                        Hu3DModelPosSet(model, obj->trans.x, obj->trans.y, obj->trans.z);
                        Hu3DModelScaleSet(model, 3.0f, 3.0f, 3.0f);
                        if (!(GwPlayer[bigObj->work[0]].stat & PLAYER_IS_CPU)) {
                            omVibrate(bigObj->work[0], 2, 3, 10);
                        }
                    }
                    entry->unk_04 = 0;
                    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                for (i = 0; i < 3; i++) {
                    if (entries[i]->unk_06 == 0 && boats[i]->trans.x + 65.0f >= obj->trans.x - 40.0f &&
                        boats[i]->trans.x - 65.0f <= obj->trans.x + 40.0f && boats[i]->trans.z + 55.0f >= obj->trans.z - 40.0f &&
                        boats[i]->trans.z - 55.0f <= obj->trans.z + 40.0f) {
                        if (entry->unk_04 == 1) {
                            s16 (*effectCreate)() = (void *)EffectGroupEmit;

                            m209_skierCoin += 5;
                            model = effectCreate(m209_starEffGrp, 0, 0, 0);
                            HuAudPlayerFXPlay(m209_coinBagSe, boats[i]->work[0]);
                            Hu3DModelPosSet(model, obj->trans.x, obj->trans.y, obj->trans.z);
                            Hu3DModelScaleSet(model, 3.0f, 3.0f, 3.0f);
                            if (!(GwPlayer[boats[i]->work[0]].stat & PLAYER_IS_CPU)) {
                                omVibrate(boats[i]->work[0], 2, 3, 10);
                            }
                        }
                        entry->unk_04 = 0;
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            break;
        case 2:
            obj->trans.z += 13.0f;
            if (m209_phase == 2) {
                if (big->unk_06 == 0 && entry->unk_04 == 1 && bigObj->trans.x + 60.0f >= obj->trans.x - 150.0f &&
                    bigObj->trans.x - 60.0f <= obj->trans.x + 150.0f && bigObj->trans.z + 60.0f >= obj->trans.z - 60.0f &&
                    bigObj->trans.z - 60.0f <= obj->trans.z + 60.0f) {
                    big->unk_06 = 60;
                    HuAudPlayerFXPlay(m209_logHitSe, bigObj->work[0]);
                    PlayerFXPlay(0x286, bigObj->work[0]);
                    entry->unk_04 = 2;
                    if (!(GwPlayer[bigObj->work[0]].stat & PLAYER_IS_CPU)) {
                        omVibrate(bigObj->work[0], 20, 0, 20);
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (entries[i]->unk_06 == 0 && (entry->unk_04 == 1 || entry->unk_04 == 2) &&
                        boats[i]->trans.x + 65.0f >= obj->trans.x - 150.0f &&
                        boats[i]->trans.x - 65.0f <= obj->trans.x + 150.0f && boats[i]->trans.z + 55.0f >= obj->trans.z - 60.0f &&
                        boats[i]->trans.z - 55.0f <= obj->trans.z + 60.0f) {
                        entries[i]->unk_06 = 30;
                        HuAudPlayerFXPlay(m209_logHitSe, boats[i]->work[0]);
                        PlayerFXPlay(0x286, boats[i]->work[0]);
                        entry->unk_04 = 2;
                        if (!(GwPlayer[boats[i]->work[0]].stat & PLAYER_IS_CPU)) {
                            omVibrate(boats[i]->work[0], 20, 0, 20);
                        }
                    }
                }
                if (entry->unk_04 == 2) {
                    entry->unk_04 = 3;
                }
            }
            break;
    }
}

void m209_ItemObjMain(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_itemWorkTbl[obj->work[0]];
    RiverRaidersEntry *cur;
    u8 active;
    s16 i;

    if ((s16)m209_phase < 5) {
        if ((s16)m209_phase >= 2) {
            if (obj->work[0] == 0) {
                if (m209_timer % 29 == 0 && m209_coinCnt < 20) {
                    cur = &m209_itemWorkTbl[m209_coinCnt];
                    Hu3DModelAttrSet(cur->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m209_coinCnt++;
                    if (cur->unk_04 == 0) {
                        cur->unk_04 = 1;
                    }
                }
                if (m209_timer % 181 == 0 && m209_coinBagCnt < 3) {
                    cur = &m209_itemWorkTbl[m209_coinBagCnt + 20];
                    Hu3DModelAttrSet(cur->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m209_coinBagCnt++;
                    if (cur->unk_04 == 0) {
                        cur->unk_04 = 1;
                    }
                }
                if (m209_timer < 221 && m209_coinBagCnt == 3) {
                    cur = &m209_itemWorkTbl[m209_coinBagCnt + 20];
                    Hu3DModelAttrSet(cur->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m209_coinBagCnt++;
                    if (cur->unk_04 == 0) {
                        cur->unk_04 = 1;
                    }
                }
                if (m209_timer % 125 == 0 && m209_logCnt < 5) {
                    cur = &m209_itemWorkTbl[m209_logCnt + 24];
                    Hu3DModelAttrSet(cur->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m209_logCnt++;
                    if (cur->unk_04 == 0) {
                        cur->unk_04 = 1;
                    }
                }
                if (m209_timer < 241 && m209_logCnt == 5) {
                    cur = &m209_itemWorkTbl[m209_logCnt + 24];
                    Hu3DModelAttrSet(cur->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    m209_logCnt++;
                    if (cur->unk_04 == 0) {
                        cur->unk_04 = 1;
                    }
                }
            }
            if (entry->unk_04 == 1) {
                m209_ItemHitUpdate(obj);
                switch (entry->unk_0C) {
                    case 0:
                        obj->trans.y -= 1.0f;
                        if (++entry->unk_0E >= 30) {
                            entry->unk_0C = 1;
                            entry->unk_0E = 0;
                        }
                        break;
                    case 1:
                        obj->trans.y += 1.0f;
                        if (++entry->unk_0E >= 30) {
                            entry->unk_0C = 0;
                            entry->unk_0E = 0;
                        }
                        break;
                }
                if (obj->trans.z > 1200.0) {
                    entry->unk_04 = 0;
                    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
            }
            if (obj->work[0] >= 24) {
                switch (entry->unk_04) {
                    case 3:
                        entry->unk_04 = 4;
                        Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                        Hu3DMotionAttrSet(obj->model[0], 2, 0);
                        break;
                    case 4:
                        if (Hu3DData[obj->model[0]].motTime >= 30.0f) {
                            if (Hu3DData[obj->model[0]].motTime == 30.0f) {
                                Hu3DModelTPLvlInit(obj->model[0]);
                            }
                            entry->unk_10 -= 13;
                            if (entry->unk_10 <= 0) {
                                entry->unk_10 = 0;
                            }
                            Hu3DModelTPLvlSet(obj->model[0], entry->unk_10);
                        }
                        if (Hu3DData[obj->model[0]].motTime == m209_logMotLen) {
                            entry->unk_04 = 0;
                            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                        break;
                }
            }
            if (obj->work[0] == 0 && m209_phase == 4) {
                active = FALSE;
                for (i = 0; i < 30; i++) {
                    cur = &m209_itemWorkTbl[i];
                    if (cur->unk_04 != 0) {
                        active = TRUE;
                    }
                }
                if (!active) {
                    m209_finishStep = 4;
                }
            }
        }
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void m209_ItemObjInit(omObjData *obj) {
    RiverRaidersEntry *entry = &m209_itemWorkTbl[obj->work[0]];
    u16 offset = rand8() * 5;
    u16 sprModel;

    switch (obj->work[1]) {
        case 0:
            sprModel = SprModelRead(0x210026, 0x289, 8);
            obj->model[0] = Hu3DSprModelData[sprModel].modelId;
            Hu3DModelObjAttrSet(obj->model[0], 0x70000000, 0x70000000);
            Hu3DAnimSpeedSet(Hu3DSprModelData[sprModel].unk_02, 10.0f);
            if (!(obj->work[0] & 1)) {
                obj->trans.x = -(offset / 2) + 120.0f;
            } else {
                obj->trans.x = (offset / 2) - 120.0f;
            }
            obj->trans.y = 20.0f;
            obj->trans.z = -1200.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            obj->scale.x = obj->scale.y = obj->scale.z = 2.0f;
            Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
            break;
        case 1:
            obj->model[0] = Hu3DModelRead(0x2A0005, 0x299);
            if ((obj->work[0] & 1) == m209_coinBagSide) {
                obj->trans.x = -(offset / 2) + 120.0f;
            } else {
                obj->trans.x = (offset / 2) - 120.0f;
            }
            obj->trans.y = -30.0f;
            obj->trans.z = -1400.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
            break;
        case 2:
            obj->model[0] = Hu3DModelRead(0x2A0006, 0x2A9);
            omObjMotionRead(obj, 0, 0x2A0007);
            Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
            Hu3DMotionAttrSet(obj->model[0], 2, 1);
            entry->unk_10 = 0xFF;
            if (!(obj->work[0] & 1)) {
                obj->trans.x = -(offset / 2) + 220.0f;
            } else {
                obj->trans.x = (offset / 2) - 220.0f;
            }
            obj->trans.y = 0.0f;
            obj->trans.z = -1600.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
            m209_logMotLen = Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02;
            break;
    }
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->func = m209_ItemObjMain;
}

void m209_ItemObjCreateAll(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 30; i++) {
        entry = &m209_itemWorkTbl[i];
        obj = omAddObj(0x226, 5, 5, -1, m209_ItemObjInit);
        obj->work[0] = i;
        if (i < 20) {
            obj->work[1] = 0;
        }
        if (i >= 20 && i < 24) {
            obj->work[1] = 1;
        }
        if (i >= 24) {
            obj->work[1] = 2;
        }
        entry->obj = obj;
    }
}

void m209_CameraViewInit(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 2275.0f;
        CRotM[i].x = 319.3f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -195.0f;
        CenterM[i].z = 0.0f;
    }
}

void m209_ExitObjMain(omObjData *obj) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void m209_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m209_ExitObjMain;
    }
}

void m209_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
        obj->func = m209_ExitWaitObjMain;
        HuAudSeqFadeOut(0x1E);
        HuAudFXAllFadeOut(0x1E);
    }
}

void m209_MainObjMain(omObjData *obj) {
    RiverRaidersEntry *entries[3];
    omObjData *boats[3];
    omObjData *lastBoat = m209_skierWorkTbl[3].obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entries[i] = &m209_skierWorkTbl[i];
        boats[i] = entries[i]->obj;
    }
    if (m209_phase == 10) {
        if (m209_skierSeNo != -1) {
            HuAudFXFadeOut(m209_skierSeNo, 30);
            m209_skierSeNo = -1;
        }
    } else if (m209_skierSeNo == -1) {
        m209_skierSeNo = HuAudFXPlay(0x342);
    }
    switch (m209_phase) {
        case 0:
            m209_PhaseSet(1);
            m209_timer = 0;
            break;
        case 1:
            if (m209_timer == 0) {
                GMesCreate(GMES_MES_4);
                m209_timer++;
            } else if (m209_timer > 32) {
                HuAudSeqPlay(0x2E);
            } else {
                m209_timer++;
            }
            if (GMesStatGet() == 0) {
                m209_PhaseSet(2);
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                m209_timer = 901;
            }
            break;
        case 2:
            if (m209_timer > 0) {
                m209_timer--;
                GMesTimerValueSet((m209_timer + 29) / 30);
            } else {
                GMesTimerEnd();
                m209_PhaseSet(3);
                GMesCreate(GMES_MES_15);
                HuAudSeqFadeOut(120);
            }
            m209_SkierPushCalc();
            break;
        case 3:
            if (m209_finishStep == 3 && GMesStatGet() == 0) {
                m209_PhaseSet(4);
                m209_timer = -15;
            }
            break;
        case 4:
            if (m209_timer >= 0) {
                if (m209_finishStep == 4) {
                    m209_PhaseSet(5);
                    GwPlayer[lastBoat->work[0]].gameCoin = m209_boatCoin;
                    for (i = 0; i < 3; i++) {
                        GwPlayer[boats[i]->work[0]].gameCoin = m209_skierCoin;
                    }
                    if (m209_boatCoin + m209_skierCoin == 0) {
                        m209_timer = 0x90;
                    } else if (m209_boatCoin == 0) {
                        m209_timer = 0x62;
                    } else if (m209_skierCoin != 0) {
                        m209_timer = 0x7D;
                    } else {
                        m209_timer = 0x62;
                    }
                }
            } else {
                m209_timer++;
            }
            break;
        case 5:
            if (m209_boatCoin + m209_skierCoin == 0) {
                if (m209_timer == 0x90) {
                    HuAudSeqPlay(0x6C);
                }
            } else if (m209_boatCoin == 0 || m209_skierCoin == 0) {
                if (m209_timer == 0x62) {
                    HuAudSeqPlay(0x65);
                }
            } else if (m209_timer == 0x7D) {
                HuAudSeqPlay(0x66);
            }
            if (m209_timer > 0) {
                m209_timer--;
            } else {
                m209_PhaseSet(10);
                m209_timer = 0;
            }
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            if (m209_timer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
                obj->func = m209_ExitWaitObjMain;
                m209_timer++;
            }
            break;
    }
}

void m209_MainObjInit(omObjData *obj) {
    u8 i;
    u8 j;

    m209_timer = 0;
    m209_phase = 0;
    m209_finishStep = 50;
    m209_boatCoin = 0;
    m209_skierCoin = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            m209_skierRangeTbl[i][j] = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        m209_skierLaneTbl[i] = 5;
    }
    m209_skierLaneCnt = 0;
    m209_coinCnt = 0;
    m209_coinBagCnt = 0;
    m209_logCnt = 0;
    m209_logMotLen = 0;
    for (i = 0; i < 5; i++) {
        m209_wakeRotTbl[i] = 0;
    }
    if (!(rand8() & 1)) {
        m209_skierSwayDir = -1;
    } else {
        m209_skierSwayDir = 1;
    }
    m209_skierHopTimer = 0;
    if (!(rand8() & 1)) {
        m209_coinBagSide = 0;
    } else {
        m209_coinBagSide = 1;
    }
    m209_engineSeNo = m209_skierSeNo = -1;
    m209_CameraViewInit();
    m209_RiverObjCreateAll();
    m209_WaterObjCreate();
    m209_BoatObjCreate();
    m209_SkierObjCreateAll();
    m209_ItemObjCreateAll();
    m209_RopeObjCreateAll();
    m209_ScoreObjCreateAll();
    m209_starEffGrp = EffectGroupStarCreate(0x2A9, 10);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    obj->func = m209_MainObjMain;
}

void m209_Dummy(void) {
}

void m209_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m209_cameraViewTbl[i].scissorX, m209_cameraViewTbl[i].scissorY,
                   m209_cameraViewTbl[i].scissorWidth, m209_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m209_cameraViewTbl[i].viewportScale.x, m209_cameraViewTbl[i].viewportScale.y,
                    m209_cameraViewTbl[i].viewportScale.z, m209_cameraViewTbl[i].viewportTranslate.x,
                    m209_cameraViewTbl[i].viewportTranslate.y, m209_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m209_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m209_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(100);
    omInitObjMan(100, 0);
    omGameSysInit();
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 64, 64, 64);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(2, 64, 64, 64);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    m209_CameraInit();
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m209_fontMesTbl, 0);
    GMesFontMesCreate(m209_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m209_MainObjInit);
    omAddObj(1000, 0, 0, -1, m209_ExitCheckObjMain);
    m209_ObjWorkInit();
}

const s16 m209_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
