#include "common.h"
#include "gcc/memory.h"
#include "math.h"
#include "game/overlays/minigame.h"

// The 4 player entries start at entry 2 of m242_objWorkTbl, and the 12
// cards laid out on the table start at entry 6.
#define STACKED_DECK_PLAYERS (&m242_objWorkTbl[2])
#define STACKED_DECK_CARDS (&m242_objWorkTbl[6])
// Entries 23-25 are the three spinning objects created by m242_DecoObjCreateAll.
#define STACKED_DECK_SPINNERS (&m242_objWorkTbl[23])

typedef struct {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} StackedDeckCamera;

// One entry of the 50 card stack. Layout derived from the table clear in
// m242_ObjWorkInit, which walks 50 entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04[10];
    /* 0x18 */ f32 unk_18[10];
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} StackedDeckObjWork; // sizeof 0x84
// Groups of BSS variables that are not 4-aligned as standalone arrays. The
// original names are aliased to the fields (see undefined_syms.txt).
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01[5];
    /* 0x06 */ s16 unk_06[7];
} StackedDeckPhaseWork; // sizeof 0x14

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[4];
} StackedDeckS16Group; // sizeof 0xA

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];

s32 m242_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
Vec2f m242_cardPosTbl[12] = {
    { -525.0f, -350.0f },
    { -175.0f, -350.0f },
    { 175.0f, -350.0f },
    { 525.0f, -350.0f },
    { -525.0f, 150.0f },
    { -175.0f, 150.0f },
    { 175.0f, 150.0f },
    { 525.0f, 150.0f },
    { -525.0f, 650.0f },
    { -175.0f, 650.0f },
    { 175.0f, 650.0f },
    { 525.0f, 650.0f },
};
Vec2f m242_decoPosTbl[3] = { { 70.0f, 20.0f }, { -10.0f, 10.0f }, { -70.0f, 20.0f } };
f32 m242_decoSpeedTbl[3] = { 2.0f, 2.0f, 2.0f };
// The intended delays (90, 900, 0, 30, 150) landed in gaugeValue/winners, likely
// from an initializer written without the inner braces. It doesn't matter in
// practice: this overlay never runs MgFlowMain, so only the
// setup in MgFlowInit reads this struct.
MinigameFlow m242_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 90.0f, 900.0f, 0.0f, 30.0f },
    { 150, 0, 0, 0 },
    0, 0, 0, 0, 0
};
s32 m242_cameraSetF = 0;
StackedDeckCamera m242_cameraViewTbl[1] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 33.0f }
};

extern const s16 m242_fontMesTbl[];

s16 m242_pickCardType BSS;
s16 m242_flySeF BSS;
StackedDeckPhaseWork m242_phaseWork BSS;
extern u8 m242_phase;     // m242_phaseWork.unk_00
extern s8 m242_rankCntTbl[5];  // m242_phaseWork.unk_01
extern s16 m242_coinRankTbl[7]; // m242_phaseWork.unk_06
void *m242_cardAnimDataTbl[6] BSS;
s16 m242_timer BSS;
u8 m242_timerPad[0xC] BSS; /* Unreferenced. */
StackedDeckObjWork m242_objWorkTbl[50] BSS;
// Alias of the player entries (STACKED_DECK_PLAYERS), used where the target
// indexes the player table directly.
extern StackedDeckObjWork m242_playerWorkTbl[4];
s16 m242_shuffleCnt BSS;
s16 m242_koopaCardNum BSS;
s32 m242_decoMdl BSS;
StackedDeckS16Group m242_teresaCardGrp BSS;
extern s16 m242_teresaCardNum;    // m242_teresaCardGrp.unk_00
extern s16 m242_starRankTbl[4]; // m242_teresaCardGrp.unk_02
s16 m242_finalHitF BSS;
s16 m242_cardSeStep BSS;
s8 m242_rankPlayerTbl[4][4] BSS;
s16 m242_hitEffState BSS;
u8 m242_hitEffStatePad[4] BSS; /* Unreferenced. */
s16 m242_slotUsedTbl[12] BSS;
StackedDeckS16Group m242_flipSeGrp BSS;
extern s16 m242_flipSeCnt;    // m242_flipSeGrp.unk_00
extern s16 m242_queueSlotFTbl[4]; // m242_flipSeGrp.unk_02
s16 m242_comFlipF BSS;
s16 m242_shuffleCardNo BSS;
s16 m242_dealCnt BSS;
s16 m242_cardAnimTbl[12] BSS;
u8 m242_jumpF BSS;
u8 m242_phaseDoneNo BSS;
s16 m242_kinokoCardNum BSS;
s16 m242_roundNo BSS;
s16 m242_queueLast BSS;
s16 m242_smokeState BSS;

void m242_VelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed);
void m242_MapObjMain(omObjData *object);
void m242_MapObjInit(omObjData *object);
void m242_BackObjMain(omObjData *object);
void m242_BackObjInit(omObjData *object);
void m242_PlayerComInput(omObjData *object);
void m242_PlayerCardFlipCheck(omObjData *object);
void m242_PlayerObjMain(omObjData *object);
void m242_PlayerObjInit(omObjData *object);
void m242_CardObjMain(omObjData *object);
void m242_CardObjInit(omObjData *object);
void m242_CardChrObjMain(omObjData *object);
void m242_SmokeObjMain(omObjData *object);
void m242_SmokeObjInit(omObjData *object);
void m242_HitEffObjMain(omObjData *object);
void m242_HitEffObjInit(omObjData *object);
void m242_DecoObjMain(omObjData *object);
void m242_DecoObjInit(omObjData *object);
void m242_ExitObjMain(omObjData *object);
void m242_ExitWaitObjMain(omObjData *object);
void m242_ExitCheckObjMain(omObjData *object);
void m242_MainObjMain(omObjData *object);
void m242_MainObjInit(omObjData *object);
void m242_ObjectSetup(void);

void m242_Executor(void) {
    m242_ObjectSetup();
}

f32 m242_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m242_RandMulGet(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void m242_ObjWorkInit(void) {
    StackedDeckObjWork *card;
    u32 i;

    for (i = 0, card = m242_objWorkTbl; i < 50; i++, card++) {
        card->obj = NULL;
        card->unk_04[0] = 0;
        card->unk_04[1] = 0;
        card->unk_04[2] = 0;
        card->unk_04[3] = 0;
        card->unk_04[4] = 0;
        card->unk_04[5] = 0;
        card->unk_04[6] = 0;
        card->unk_04[7] = 0;
        card->unk_04[8] = 0;
        card->unk_04[9] = 0;
        card->unk_18[0] = 0;
        card->unk_18[1] = 0;
        card->unk_18[2] = 0;
        card->unk_18[3] = 0;
        card->unk_18[4] = 0;
        card->unk_18[5] = 0;
        card->unk_18[6] = 0;
        card->unk_18[7] = 0;
        card->unk_18[8] = 0;
        card->unk_18[9] = 0;
        card->unk_40[0] = -1;
        card->unk_40[1] = -1;
        card->unk_44.x = card->unk_44.y = card->unk_44.z = 0.0f;
        card->unk_50.x = card->unk_50.y = card->unk_50.z = 0.0f;
        card->unk_5C.x = card->unk_5C.y = card->unk_5C.z = 0.0f;
        card->unk_68[0] = 0.0f;
        card->unk_68[1] = 0.0f;
        card->unk_68[2] = 0.0f;
        card->unk_68[3] = 0.0f;
        card->unk_78.x = card->unk_78.y = card->unk_78.z = 0.0f;
    }
}

void m242_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m242_CameraDebugPrint(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = m242_AngleAdd(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void m242_CameraDebugPad(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)HuPadBtn[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m242_AngleAdd(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m242_AngleAdd(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m242_AngleAdd(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m242_AngleAdd(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & A_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & B_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & L_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & R_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & U_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & D_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

void m242_PhaseSet(u8 value) {
    m242_phase = value;
}

void m242_MotShiftSet(omObjData *object, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

f32 m242_GravityCalc(f32 base, f32 *value, f32 step) {
    f32 prev = *value;

    *value = prev - step;
    return base + prev;
}

void m242_CardAnimSet(omObjData *object, u8 anim) {
    Hu3DAnimKill(m242_cardAnimTbl[object->work[0]]);
    m242_cardAnimTbl[object->work[0]] =
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, m242_cardAnimDataTbl[anim], 0, "card_k_DEF");
}

void m242_VelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1;
    f32 dz = z1;
    f32 absDx;
    f32 absDz;
    f32 delta;
    f32 dist;
    f32 step;

    dx -= x0;
    dz -= z0;
    absDx = fabsf(dx);
    absDz = fabsf(dz);

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        dist = absDx;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velZ = -(delta / step);
    } else {
        if (dz >= 0.0f) {
            *velZ = -speed;
        } else {
            *velZ = speed;
        }
        delta = dx;
        dist = absDz;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velX = -(delta / step);
    }
}

void m242_MapObjMain(omObjData *object) {
}

void m242_MapObjInit(omObjData *object) {
    MgMapWork *work;

    mgMapObjTbl[mgMapObjNum++] = object;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapBoxSet(mgMapObjTbl[0], 1.0f, -5060.0f, -5000.0f, 5060.0f, 5000.0f);
    object->func = m242_MapObjMain;
}

void m242_MapObjCreate(void) {
    omObjData *obj = omAddObj(0x3E6, 1, 1, -1, m242_MapObjInit);
    obj->work[0] = 0;
    m242_objWorkTbl[0].obj = obj;
}

void m242_BackObjMain(omObjData *object) {
}

void m242_BackObjInit(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[1];

    card->unk_40[0] = HuSprAnimDataRead(0x4B0000);
    card->unk_40[1] = espEntry(card->unk_40[0], 0, 0);
    espAttrSet(card->unk_40[1], HUSPR_ATTR_BG);
    card->unk_44.x = 160.0f;
    card->unk_44.y = 120.0f;
    espPosSet(card->unk_40[1], 160, 120);
    object->func = m242_BackObjMain;
}

void m242_BackObjCreate(void) {
    omObjData *obj = omAddObj(0x3E7, 1, 1, -1, m242_BackObjInit);
    obj->work[0] = 0;
    m242_objWorkTbl[1].obj = obj;
}

void m242_PlayerDummy(void) {
}

void m242_PlayerComInput(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 2];
    omObjData *target;
    f32 velX;
    f32 velZ;

    if (card->unk_04[9] == 0) {
        card->unk_04[8] = (u8)(rand8() % 12);
        while (TRUE) {
            if (STACKED_DECK_CARDS[card->unk_04[8]].unk_04[1] == 1) {
                card->unk_04[9] = 1;
                return;
            }
            if (++card->unk_04[8] >= 12) {
                card->unk_04[8] = 0;
            }
        }
    }

    target = STACKED_DECK_CARDS[card->unk_04[8]].obj;
    m242_VelCalc(target->trans.x, target->trans.z, object->trans.x, object->trans.z, &velX, &velZ, 60.0f);
    HuPadStkX[object->work[3]] = velX;
    HuPadStkY[object->work[3]] = -velZ;
    if (target->trans.x - 45.0f <= object->trans.x && object->trans.x <= target->trans.x + 45.0f &&
        target->trans.z - 67.5f <= object->trans.z && object->trans.z <= target->trans.z + 67.5f) {
        HuPadBtnDown[object->work[3]] |= A_BUTTON;
        HuPadBtnDown[object->work[3]] |= Z_TRIG;
    }
}

void m242_PlayerCardFlipCheck(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 2];
    MgPlayerWork *data = object->data;
    StackedDeckObjWork *other;
    omObjData *cardObj;
    s16 i;

    if (card->unk_04[0] == 0 && data->unk5C == 0x200 && data->unk50 == 0x80) {
        card->unk_04[0] = 1;
        for (i = 0; i < 12; i++) {
            other = &STACKED_DECK_CARDS[i];
            cardObj = other->obj;
            if (cardObj->trans.x - 90.0f < object->trans.x && object->trans.x < cardObj->trans.x + 90.0f &&
                cardObj->trans.z - 135.0f < object->trans.z && object->trans.z < cardObj->trans.z + 135.0f &&
                // The original reads this halfword field as a word.
                *(s32 *)other->unk_04 == 1) {
                card->unk_04[8] = 0;
                card->unk_04[9] = 0;
                other->unk_04[0] = 1;
                m242_pickCardType = cardObj->work[1];
                m242_phaseDoneNo = 6;
            }
        }
    }
    if (data->unk5C != 0x200 && data->unk50 != 0x80 && object->trans.y <= 1.0f) {
        card->unk_04[0] = 0;
        m242_jumpF = 0;
    }
    if (object->trans.y > 1.0f) {
        m242_jumpF = 1;
    }
    if (object->trans.z > 800.0f) {
        object->trans.z = 800.0f;
    }
    if (object->trans.x < -500.0f) {
        object->trans.x = -500.0f;
    }
    if (object->trans.x > 500.0f) {
        object->trans.x = 500.0f;
    }
}

void m242_PlayerObjMain(omObjData *object) {
    StackedDeckObjWork *card = &STACKED_DECK_PLAYERS[object->work[0]];
    MgPlayerWork *data = object->data;
    omObjData *player;
    StackedDeckObjWork *other;
    StackedDeckObjWork *effect;
    omObjData *obj;
    omObjData *cardObj;
    f32 velX;
    f32 velZ;
    s16 slot;
    s16 found;
    s16 i;

    if (m242_phase != 6) {
        m242_PadClear(object->work[0]);
    }

    switch (m242_phase) {
        case 1:
        case 2:
        case 3:
            object->rot.y = 0.0f;
            data->unk3C = 180.0f;
            break;
        case 4:
            if (object->work[1] == 0) {
                if (object->trans.x > 0.0f) {
                    HuPadStkX[object->work[3]] = -60;
                } else if (object->trans.z > 800.0f) {
                    HuPadStkY[object->work[3]] = 60;
                }
                if (object->trans.z <= 800.0f) {
                    m242_phaseDoneNo = 4;
                }
            } else if (object->work[1] <= m242_queueLast) {
                if ((object->work[1] - 1) * 140.0f < object->trans.x) {
                    HuPadStkX[object->work[3]] = -60;
                } else {
                    object->trans.x = (object->work[1] - 1) * 140.0f;
                    data->unk3C = 180.0f;
                }
            }
            break;
        case 5:
            if (object->work[1] != 0 && object->work[1] <= m242_queueLast) {
                if ((object->work[1] - 1) * 140.0f < object->trans.x) {
                    HuPadStkX[object->work[3]] = -60;
                } else {
                    object->trans.x = (object->work[1] - 1) * 140.0f;
                    data->unk3C = 180.0f;
                }
            }
            break;
        case 13:
            if (object->work[1] == 0) {
                if (object->trans.x > 0.0f) {
                    HuPadStkX[object->work[3]] = -60;
                } else if (object->trans.z > 800.0f) {
                    HuPadStkY[object->work[3]] = 60;
                }
                if (object->trans.z <= 800.0f) {
                    m242_phaseDoneNo = 13;
                }
            } else if (object->work[1] <= m242_queueLast) {
                if ((object->work[1] - 1) * 140.0f < object->trans.x) {
                    HuPadStkX[object->work[3]] = -60;
                } else {
                    object->trans.x = (object->work[1] - 1) * 140.0f;
                    data->unk3C = 180.0f;
                }
            }
            break;
        case 6:
            if (m242_timer >= 286) {
                m242_PadClear(object->work[0]);
                break;
            }
            if (object->work[1] == 0) {
                if (GwPlayer[object->work[0]].stat & 1) {
                    m242_PadClear(object->work[0]);
                    m242_PlayerComInput(object);
                }
                m242_PlayerCardFlipCheck(object);
                m242_comFlipF = 0;
            } else if (object->work[1] <= m242_queueLast) {
                m242_PadClear(object->work[0]);
                if ((object->work[1] - 1) * 140.0f < object->trans.x) {
                    HuPadStkX[object->work[3]] = -60;
                } else {
                    object->trans.x = (object->work[1] - 1) * 140.0f;
                    data->unk3C = 180.0f;
                }
            }
            m242_flipSeCnt = 0;
            break;
        case 7:
            if (object->work[1] == 0) {
                for (i = 0; i < 12; i++) {
                    other = &STACKED_DECK_CARDS[i];
                    cardObj = other->obj;
                    if (other->unk_04[0] == 1) {
                        break;
                    }
                }
                if (data->unk50 == 0x80 ||
                    (cardObj->trans.x - 90.0f < object->trans.x && object->trans.x < cardObj->trans.x + 90.0f &&
                     cardObj->trans.z - 135.0f < object->trans.z && object->trans.z < cardObj->trans.z + 135.0f &&
                     other->unk_04[0] == 1 && m242_comFlipF == 0)) {
                    MgPlayerMotSet(object, 0);
                    HuPadBtnDown[object->work[3]] |= A_BUTTON;
                    m242_comFlipF = 1;
                }
            }
            if (object->work[1] == 0) {
                if (m242_flipSeCnt == 3) {
                    m242_flipSeCnt = 4;
                    HuAudPlayerFXPlay(0x445, object->work[0]);
                } else if (m242_flipSeCnt < 3) {
                    m242_flipSeCnt++;
                }
                data->unk3C = 0.0f;
                if (object->trans.x >= -175.0f && object->trans.x <= 175.0f) {
                    if (object->trans.x < -20.0f) {
                        HuPadStkX[object->work[3]] = 60;
                    } else if (object->trans.x > 20.0f) {
                        HuPadStkX[object->work[3]] = -60;
                    }
                }
                if (object->trans.x < -175.0f) {
                    if (object->trans.x < -370.0f) {
                        HuPadStkX[object->work[3]] = 60;
                    } else if (object->trans.x > -330.0f) {
                        HuPadStkX[object->work[3]] = -60;
                    }
                }
                if (object->trans.x > 175.0f) {
                    if (object->trans.x < 330.0f) {
                        HuPadStkX[object->work[3]] = 60;
                    } else if (object->trans.x > 370.0f) {
                        HuPadStkX[object->work[3]] = -60;
                    }
                }
            } else if (object->work[1] <= m242_queueLast) {
                if ((object->work[1] - 1) * 140.0f < object->trans.x) {
                    HuPadStkX[object->work[3]] = -60;
                } else {
                    object->trans.x = (object->work[1] - 1) * 140.0f;
                    data->unk3C = 180.0f;
                }
            }
            m242_flySeF = 0;
            break;
        case 8:
            if (object->work[1] == 0) {
                effect = &m242_objWorkTbl[18];
                switch (card->unk_04[2]) {
                    case 0:
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x27) {
                            MgPlayerMotSet(object, 0x27);
                            card->unk_04[1] = 0x27;
                        }
                        if (card->unk_04[1] == 0x27 && Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 <=
                                                           Hu3DData[object->model[0]].motTime) {
                            card->unk_04[2] = 1;
                            card->unk_04[1] = 0;
                        }
                        break;
                    case 1:
                        if (m242_queueLast >= 2) {
                            m242_VelCalc((m242_queueLast - 1) * 140.0f, 800.0f, object->trans.x,
                                                       object->trans.z, &velX, &velZ, 60.0f);
                            HuPadStkX[object->work[3]] = velX;
                            HuPadStkY[object->work[3]] = -velZ;
                            if ((m242_queueLast - 1) * 140.0f - 10.0f < object->trans.x &&
                                object->trans.x < (m242_queueLast - 1) * 140.0f + 10.0f) {
                                card->unk_04[2] = 2;
                                data->unk40 = 0.0f;
                                object->trans.x = (m242_queueLast - 1) * 140.0f;
                            }
                        } else {
                            m242_VelCalc(m242_queueLast * 140.0f, 800.0f, object->trans.x,
                                                       object->trans.z, &velX, &velZ, 60.0f);
                            HuPadStkX[object->work[3]] = velX;
                            HuPadStkY[object->work[3]] = -velZ;
                            if (m242_queueLast * 140.0f - 10.0f < object->trans.x &&
                                object->trans.x < m242_queueLast * 140.0f + 10.0f) {
                                card->unk_04[2] = 2;
                                data->unk40 = 0.0f;
                                object->trans.x = m242_queueLast * 140.0f;
                            }
                        }
                        break;
                    case 2:
                        if (object->trans.z < 1100.0f) {
                            HuPadStkY[object->work[3]] = -60;
                        } else {
                            object->trans.z = 1100.0f;
                            if ((m242_queueLast - 1) * 140.0f < object->trans.x) {
                                HuPadStkX[object->work[3]] = -60;
                            } else {
                                data->unk40 = 0.0f;
                                object->trans.x = (m242_queueLast - 1) * 140.0f;
                                if (data->unk3C <= 200.0f && data->unk3C >= 160.0f) {
                                    if (card->unk_04[1] != 0) {
                                        MgPlayerMotSet(object, 2);
                                        object->motion[0] = object->motion[43];
                                        MgPlayerMotSet(object, 0);
                                        card->unk_04[1] = 0;
                                    }
                                    data->unk3C = 180.0f;
                                    if (effect->unk_04[0] == 5) {
                                        card->unk_04[2] = 0;
                                        m242_phaseDoneNo = 8;
                                        effect->unk_04[0] = 0;
                                    }
                                } else {
                                    data->unk3C = m242_AngleAdd(data->unk3C, -15.0f);
                                    if (card->unk_04[1] != 2) {
                                        MgPlayerMotSet(object, 2);
                                        object->motion[43] = object->motion[0];
                                        object->motion[0] = object->motion[2];
                                        card->unk_04[1] = 2;
                                    }
                                }
                            }
                        }
                        break;
                }
            } else if (object->work[1] <= m242_queueLast) {
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (player->work[1] == 0) {
                        break;
                    }
                }
                if (player->trans.x > 60.0f) {
                    if (object->work[1] == 1) {
                        if (object->trans.z > 800.0f) {
                            HuPadStkY[object->work[3]] = 60;
                        }
                    } else if ((object->work[1] - 2) * 140.0f < object->trans.x) {
                        HuPadStkX[object->work[3]] = -60;
                    } else {
                        object->trans.x = (object->work[1] - 2) * 140.0f;
                        data->unk3C = 180.0f;
                    }
                }
            }
            if (object->work[0] == 3 && m242_phaseDoneNo == 8) {
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (player->work[1] == 0) {
                        player->work[1] = m242_queueLast;
                    } else if (player->work[1] <= m242_queueLast) {
                        player->work[1]--;
                    }
                }
            }
            break;
        case 9:
            effect = &m242_objWorkTbl[19];
            if (object->work[1] == 0) {
                switch (card->unk_04[2]) {
                    case 0:
                        data->unk3C = 0.0f;
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x28) {
                            MgPlayerMotSet(object, 0x28);
                            card->unk_04[1] = 0x28;
                        }
                        if (card->unk_04[1] == 0x28 && Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 <=
                                                           Hu3DData[object->model[0]].motTime) {
                            card->unk_04[2] = 1;
                            card->unk_04[1] = 0;
                            object->motion[43] = object->motion[2];
                            object->motion[2] = object->motion[42];
                            PlayerFXPlay(0x286, object->work[0]);
                        }
                        break;
                    case 1:
                        if (object->trans.z < 800.0f) {
                            m242_VelCalc(150.0f, 800.0f, object->trans.x, object->trans.z, &velX,
                                                       &velZ, 60.0f);
                        } else {
                            m242_VelCalc(150.0f, 1600.0f, object->trans.x, object->trans.z, &velX,
                                                       &velZ, 60.0f);
                        }
                        HuPadStkX[object->work[3]] = velX;
                        HuPadStkY[object->work[3]] = -velZ;
                        if (object->trans.z > 1500.0f) {
                            object->trans.z = 3000.0f;
                            object->motion[2] = object->motion[43];
                            card->unk_04[2] = 2;
                        }
                        break;
                    case 2:
                        card->unk_04[2] = 3;
                        break;
                }
            } else if (object->work[1] <= m242_queueLast) {
                switch (card->unk_04[2]) {
                    case 0:
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x28) {
                            data->unk3C = 180.0f;
                            MgPlayerMotSet(object, 0x28);
                            card->unk_04[1] = 0x28;
                        }
                        if (card->unk_04[1] == 0x28 && Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 <=
                                                           Hu3DData[object->model[0]].motTime) {
                            card->unk_04[2] = 1;
                            card->unk_04[1] = 0;
                            object->motion[43] = object->motion[2];
                            object->motion[2] = object->motion[42];
                        }
                        break;
                    case 1:
                        for (i = 0; i < 4; i++) {
                            other = &STACKED_DECK_PLAYERS[i];
                            player = other->obj;
                            if (player->work[1] == 0) {
                                break;
                            }
                        }
                        if (other->unk_04[2] == 1 && player->trans.z > 800.0f && player->trans.x > -150.0f &&
                            player->trans.x < 450.0f) {
                            slot = rand8() % 100;
                            switch (object->work[1]) {
                                case 1:
                                    card->unk_18[0] = -60.0f;
                                    card->unk_18[1] = -slot;
                                    break;
                                case 2:
                                    if (!(rand8() & 1)) {
                                        card->unk_18[0] = slot;
                                    } else {
                                        card->unk_18[0] = -slot;
                                    }
                                    card->unk_18[1] = -60.0f;
                                    break;
                                case 3:
                                    card->unk_18[0] = 60.0f;
                                    card->unk_18[1] = -slot;
                                    break;
                            }
                            card->unk_04[2] = 2;
                            PlayerFXPlay(0x286, object->work[0]);
                        }
                        break;
                    case 2:
                        HuPadStkX[object->work[3]] = card->unk_18[0];
                        HuPadStkY[object->work[3]] = card->unk_18[1];
                        if (object->trans.z > 1500.0f || object->trans.x < -1000.0f || object->trans.x > 1000.0f) {
                            object->trans.z = 3000.0f;
                            object->motion[2] = object->motion[43];
                            card->unk_04[2] = 3;
                        }
                        break;
                }
            }
            if (object->work[0] == 3) {
                found = FALSE;
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (other->unk_04[2] != 3 && player->work[1] <= m242_queueLast) {
                        found = TRUE;
                    }
                }
                if (!found && effect->unk_04[0] == 5) {
                    for (i = 0; i < 4; i++) {
                        other = &STACKED_DECK_PLAYERS[i];
                        other->unk_04[2] = 0;
                    }
                    m242_phaseDoneNo = 9;
                    effect->unk_04[0] = 0;
                }
            }
            break;
        case 10:
            if (object->work[1] <= m242_queueLast) {
                switch (card->unk_04[2]) {
                    case 0:
                        slot = (rand8() & 0xFF) % (m242_queueLast + 1);
                        while (TRUE) {
                            if (m242_queueSlotFTbl[slot] == 0) {
                                object->work[1] = slot;
                                object->trans.x = slot * 140.0f;
                                object->trans.z = 1500.0f;
                                card->unk_04[2] = 1;
                                data->unk40 = 0.0f;
                                m242_queueSlotFTbl[slot] = 1;
                                break;
                            }
                            if (++slot > m242_queueLast) {
                                slot = 0;
                            }
                        }
                        break;
                    case 1:
                        if (object->trans.z > 1100.0f) {
                            HuPadStkY[object->work[3]] = 60;
                        } else {
                            data->unk40 = 0.0f;
                            object->trans.z = 1100.0f;
                            card->unk_04[2] = 2;
                        }
                        break;
                    case 2:
                        break;
                }
            }
            if (object->work[0] == 3) {
                found = FALSE;
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (other->unk_04[2] != 2 && player->work[1] <= m242_queueLast) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    for (i = 0; i < 4; i++) {
                        other = &STACKED_DECK_PLAYERS[i];
                        other->unk_04[2] = 0;
                        m242_queueSlotFTbl[i] = 0;
                    }
                    m242_phaseDoneNo = 10;
                }
            }
            break;
        case 11:
            if (object->work[1] == 0) {
                effect = &m242_objWorkTbl[20];
                obj = effect->obj;
                switch (card->unk_04[2]) {
                    case 0:
                        data->unk40 = 0.0f;
                        data->unk3C = 0.0f;
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x29) {
                            MgPlayerMotSet(object, 0x29);
                            card->unk_04[1] = 0x29;
                            card->unk_04[7] = m242_queueLast;
                        }
                        if (obj->trans.x > object->trans.x) {
                            card->unk_04[6] = 1;
                        } else {
                            card->unk_04[6] = 2;
                        }
                        if (effect->unk_04[0] >= 5) {
                            card->unk_04[2] = 1;
                            MgPlayerMotSet(object, 0x12);
                            card->unk_04[1] = 0x12;
                            Hu3DMotionTimeSet(object->model[0], 0.0f);
                            Hu3DMotionSpeedSet(object->model[0], 0.0f);
                            card->unk_18[2] = 50.0f;
                            m242_hitEffState = 1;
                        }
                        break;
                    case 1:
                        if (m242_flySeF == 0) {
                            m242_flySeF = 1;
                            PlayerFXPlay(0x286, object->work[0]);
                            HuAudFXPlay(0x44A);
                        }
                        object->trans.y = card->unk_18[3] =
                            m242_GravityCalc(card->unk_18[3], &card->unk_18[2], 0.05f);
                        if (card->unk_04[6] == 1) {
                            object->trans.x -= 20.0f;
                        } else {
                            object->trans.x += 20.0f;
                        }
                        object->trans.z += 20.0f;
                        object->rot.y = m242_AngleAdd(object->rot.y, 66.0f);
                        object->rot.x = m242_AngleAdd(object->rot.x, 66.0f);
                        if (object->trans.y > 3000.0f) {
                            object->trans.x = 3000.0f;
                            card->unk_04[2] = 2;
                            object->trans.y = 0.0f;
                        }
                        break;
                    case 2:
                        if (effect->unk_04[0] == 7) {
                            card->unk_04[2] = 0;
                            m242_phaseDoneNo = 11;
                            effect->unk_04[0] = 0;
                            card->unk_04[1] = 0;
                        }
                        break;
                }
            } else if (object->work[1] <= m242_queueLast) {
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (player->work[1] == 0) {
                        break;
                    }
                }
                if (other->unk_04[2] > 0) {
                    if (object->work[1] == 1) {
                        if (object->trans.z > 800.0f) {
                            HuPadStkY[object->work[3]] = 60;
                        }
                    } else if ((object->work[1] - 2) * 140.0f < object->trans.x) {
                        HuPadStkX[object->work[3]] = -60;
                    } else {
                        object->trans.x = (object->work[1] - 2) * 140.0f;
                        data->unk3C = 180.0f;
                    }
                }
            }
            if (object->work[0] == 3 && m242_phaseDoneNo == 11) {
                for (i = 0; i < 4; i++) {
                    other = &STACKED_DECK_PLAYERS[i];
                    player = other->obj;
                    if (player->work[1] == 0) {
                        player->work[1] = 99;
                    } else if (player->work[1] <= m242_queueLast) {
                        player->work[1]--;
                    }
                }
                m242_queueLast--;
            }
            break;
        case 14:
        case 15:
            if (object->work[1] == 0) {
                effect = &m242_objWorkTbl[20];
                obj = effect->obj;
                switch (card->unk_04[2]) {
                    case 0:
                        data->unk40 = 0.0f;
                        data->unk3C = 0.0f;
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x29) {
                            MgPlayerMotSet(object, 0x29);
                            card->unk_04[1] = 0x29;
                            card->unk_04[7] = m242_queueLast;
                        }
                        if (obj->trans.x > object->trans.x) {
                            card->unk_04[6] = 1;
                        } else {
                            card->unk_04[6] = 2;
                        }
                        if (effect->unk_04[0] >= 5) {
                            card->unk_04[2] = 1;
                            MgPlayerMotSet(object, 0x12);
                            card->unk_04[1] = 0x12;
                            Hu3DMotionTimeSet(object->model[0], 0.0f);
                            Hu3DMotionSpeedSet(object->model[0], 0.0f);
                            card->unk_18[2] = 50.0f;
                            m242_hitEffState = 1;
                            m242_finalHitF = 1;
                        }
                        break;
                    case 1:
                        if (m242_flySeF == 0) {
                            m242_flySeF = 1;
                            PlayerFXPlay(0x286, object->work[0]);
                            HuAudFXPlay(0x44A);
                        }
                        object->trans.y = card->unk_18[3] =
                            m242_GravityCalc(card->unk_18[3], &card->unk_18[2], 0.05f);
                        if (card->unk_04[6] == 1) {
                            object->trans.x -= 20.0f;
                        } else {
                            object->trans.x += 20.0f;
                        }
                        object->trans.z += 20.0f;
                        object->rot.y = m242_AngleAdd(object->rot.y, 66.0f);
                        object->rot.x = m242_AngleAdd(object->rot.x, 66.0f);
                        if (object->trans.y > 3000.0f) {
                            object->trans.x = 3000.0f;
                            card->unk_04[2] = 2;
                        }
                        break;
                    case 2:
                        break;
                }
            } else if (object->work[1] <= m242_queueLast && m242_phase == 15) {
                if (data->unk3C <= 20.0f || data->unk3C >= 340.0f) {
                    data->unk3C = 0.0f;
                    MgPlayerMotSet(object, 2);
                    object->motion[0] = object->motion[43];
                    MgPlayerMotSet(object, 0);
                    card->unk_04[1] = 0;
                } else {
                    data->unk3C = m242_AngleAdd(data->unk3C, 15.0f);
                    if (card->unk_04[1] != 2) {
                        MgPlayerMotSet(object, 2);
                        object->motion[43] = object->motion[0];
                        object->motion[0] = object->motion[2];
                        card->unk_04[1] = 2;
                    }
                }
            }
            break;
        case 16:
        case 17:
            if (object->work[1] == 0) {
                effect = &m242_objWorkTbl[20];
                obj = effect->obj;
                switch (card->unk_04[2]) {
                    case 0:
                        data->unk40 = 0.0f;
                        data->unk3C = 0.0f;
                        if (effect->unk_04[0] == 2 && card->unk_04[1] != 0x29) {
                            MgPlayerMotSet(object, 0x29);
                            card->unk_04[1] = 0x29;
                            card->unk_04[7] = m242_queueLast;
                        }
                        if (obj->trans.x > object->trans.x) {
                            card->unk_04[6] = 1;
                        } else {
                            card->unk_04[6] = 2;
                        }
                        if (effect->unk_04[0] >= 5) {
                            card->unk_04[2] = 1;
                            MgPlayerMotSet(object, 0x12);
                            card->unk_04[1] = 0x12;
                            Hu3DMotionTimeSet(object->model[0], 0.0f);
                            Hu3DMotionSpeedSet(object->model[0], 0.0f);
                            card->unk_18[2] = 50.0f;
                            m242_hitEffState = 1;
                            m242_finalHitF = 1;
                        }
                        break;
                    case 1:
                        if (m242_flySeF == 0) {
                            m242_flySeF = 1;
                            PlayerFXPlay(0x286, object->work[0]);
                            HuAudFXPlay(0x44A);
                        }
                        object->trans.y = card->unk_18[3] =
                            m242_GravityCalc(card->unk_18[3], &card->unk_18[2], 0.05f);
                        if (card->unk_04[6] == 1) {
                            object->trans.x -= 20.0f;
                        } else {
                            object->trans.x += 20.0f;
                        }
                        object->trans.z += 20.0f;
                        object->rot.y = m242_AngleAdd(object->rot.y, 66.0f);
                        object->rot.x = m242_AngleAdd(object->rot.x, 66.0f);
                        if (object->trans.y > 3000.0f) {
                            object->trans.x = 3000.0f;
                            card->unk_04[2] = 2;
                        }
                        break;
                    case 2:
                        if (effect->unk_04[0] == 7) {
                            card->unk_04[2] = 0;
                            m242_phaseDoneNo = 11;
                            effect->unk_04[0] = 0;
                            card->unk_04[1] = 0;
                        }
                        break;
                }
            } else if (object->work[1] <= m242_queueLast) {
                if (data->unk3C <= 20.0f || data->unk3C >= 340.0f) {
                    data->unk3C = 0.0f;
                    if (card->unk_04[1] != 13 && m242_timer >= 0) {
                        object->motion[0] = object->motion[43];
                        MgPlayerMotSet(object, 13);
                        card->unk_04[1] = 13;
                        card->unk_04[7] = 0;
                        HuAudCharVoicePlay((m242_voiceChrTbl[GwPlayer[object->work[0]].chr] << 16) | 0x30);
                    }
                } else {
                    data->unk3C = m242_AngleAdd(data->unk3C, 15.0f);
                    if (card->unk_04[1] != 2) {
                        MgPlayerMotSet(object, 2);
                        object->motion[43] = object->motion[0];
                        object->motion[0] = object->motion[2];
                        card->unk_04[1] = 2;
                    }
                }
            }
            break;
    }

    if (m242_phase == 7) {
        mgPlayerJumpPower = 1.7f;
    } else {
        mgPlayerJumpPower = 1.3f;
    }
    if (object->work[1] > m242_queueLast) {
        m242_PadClear(object->work[0]);
        data->unk40 = 0.0f;
    }
    MgPlayerObjMain(object);
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    if (object->trans.x >= 3000.0f) {
        object->trans.y = object->work[0] * 500.0f + 100.0f;
    }
    if (object->trans.z < -500.0f) {
        object->trans.z = -499.0f;
    }
}

void m242_PlayerObjInit(omObjData *object) {
    StackedDeckObjWork *card = &STACKED_DECK_PLAYERS[object->work[0]];
    u16 character = GwPlayer[object->work[0]].chr;
    s32 modelFile = omCharModelNoTbl[character][0];
    s32 motionFile = omCharMotTbl[character][0];
    MgPlayerWork *work;
    omObjData *obj;
    StackedDeckObjWork *player;
    s32 values[4];
    s16 i;
    s16 j;
    s16 rank;
    s16 slot;

    MgPlayerParamReset();
    MgPlayerCreate(object, modelFile, motionFile, ((u16 *)object->work)[1], 0x2B9, 0x2A9);
    work = object->data;
    work->unkEC = NULL;
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_AA_MASK, HU3D_ATTR_AA);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_ON);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    object->model[7] = Hu3DModelRead(8, 0x2BD);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(object, 6, CharMotionDataNumGet(character, 4), 1, 0x13);
    MgPlayerMotLoad(object, 8, CharMotionDataNumGet(character, 6), 1, 0x1B);
    MgPlayerMotLoad(object, 0x12, CharMotionDataNumGet(character, 0xF), 2, 0);
    MgPlayerMotRead(object, 0x15, CharMotionDataNumGet(character, 0x1F), 0, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x30), 1, 0x78);
    MgPlayerMotLoad(object, 0x27, CharMotionDataNumGet(character, 0x33), 2, 0);
    MgPlayerMotLoad(object, 0x28, CharMotionDataNumGet(character, 0x7A), 2, 0);
    MgPlayerMotLoad(object, 0x29, CharMotionDataNumGet(character, 0x37), 1, 0x78);
    MgPlayerMotLoad(object, 0x2A, CharMotionDataNumGet(character, 0x70), 1, 0);
    card->unk_04[1] = 0;
    MgPlayerMotSet(object, 0);
    mgFieldStat = 1;

    // The last player sets up the turn order for everyone, ranked by coins and
    // then by stars.
    if (object->work[0] == 3) {
        for (i = 0; i < 4; i++) {
            player = &STACKED_DECK_PLAYERS[i];
            obj = player->obj;
            for (j = 0; j < 4; j++) {
                values[j] = GwPlayer[j].coin;
            }
            for (j = 0, rank = 0; j < 4; j++) {
                if (j != obj->work[0] && values[obj->work[0]] < values[j]) {
                    rank++;
                }
            }
            m242_coinRankTbl[i] = rank;
        }
        for (i = 0; i < 4; i++) {
            player = &STACKED_DECK_PLAYERS[i];
            obj = player->obj;
            for (j = 0; j < 4; j++) {
                values[j] = GwPlayer[j].star;
            }
            for (j = 0, rank = 0; j < 4; j++) {
                if (j != obj->work[0]) {
                    if (values[obj->work[0]] < values[j]) {
                        rank++;
                    } else if (values[obj->work[0]] == values[j] &&
                               m242_coinRankTbl[i] > m242_coinRankTbl[j]) {
                        rank++;
                    }
                }
            }
            m242_starRankTbl[i] = rank;
        }
        for (i = 0; i < 4; i++) {
            player = &STACKED_DECK_PLAYERS[i];
            obj = player->obj;
            rank = m242_starRankTbl[i];
            obj->work[1] = rank;
            m242_rankPlayerTbl[rank][m242_rankCntTbl[rank]] = obj->work[0];
            m242_rankCntTbl[rank]++;
        }
        for (i = 0; i < 4;) {
            if (m242_rankCntTbl[i] >= 2) {
                slot = m242_RandMulGet(m242_rankCntTbl[i]);
                obj = m242_playerWorkTbl[m242_rankPlayerTbl[i][slot]].obj;
                obj->work[1] += m242_rankCntTbl[i] - 1;
                m242_rankCntTbl[i]--;
                for (j = slot; j < 3; j++) {
                    m242_rankPlayerTbl[i][j] = m242_rankPlayerTbl[i][j + 1];
                }
                if (m242_rankCntTbl[i] == 1) {
                    i++;
                }
            } else {
                i++;
            }
        }
        for (i = 0; i < 4; i++) {
            player = &STACKED_DECK_PLAYERS[i];
            obj = player->obj;
            obj->trans.x = obj->work[1] * 140.0f;
            obj->trans.y = 0.0f;
            obj->trans.z = 1100.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        }
    }
    MgPlayerMapAttrSet(object, 0, 2);
    m242_PadClear(object->work[0]);
    object->rot.y = 180.0f;
    work->unk3C = 180.0f;
    object->func = m242_PlayerObjMain;
}

void m242_PlayerObjCreateAll(void) {
    StackedDeckObjWork *card;
    omObjData *obj;
    u16 player;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                player = 0;
                break;
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
            default:
                player = 0;
                break;
        }
        card = &m242_objWorkTbl[i + 2];
        obj = omAddObj(0x1F4, 9, 0x3C, -1, m242_PlayerObjInit);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        card->obj = obj;
        mgPlayerObjTbl[mgPlayerObjNum] = obj;
        mgPlayerObjNum++;
    }
}

void m242_CardObjMain(omObjData *object) {
    StackedDeckObjWork *card = &STACKED_DECK_CARDS[object->work[0]];
    s16 i;
    s16 slot;
    u8 busy;
    f32 targetZ;
    omObjData *cardObj;
    StackedDeckObjWork *other;

    switch (m242_phase) {
        case 1:
            switch (card->unk_04[1]) {
                case 0:
                    for (i = 0; i < 12; i++) {
                        if (m242_slotUsedTbl[i] == 0) {
                            if (i == 0 || i == 1 || i == 4 || i == 5 || i == 8 || i == 9) {
                                object->trans.x = -1200.0f;
                            } else {
                                object->trans.x = 1200.0f;
                            }
                            object->trans.y = (object->work[0] + 1) * 2;
                            object->trans.z = m242_cardPosTbl[i].y;
                            card->unk_04[3] = i;
                            m242_slotUsedTbl[i] = 1;
                            break;
                        }
                    }
                    switch (m242_roundNo) {
                        case 0:
                            if (m242_dealCnt < 6) {
                                m242_CardAnimSet(object, 0);
                                object->work[1] = 1;
                                m242_kinokoCardNum++;
                            }
                            if (m242_dealCnt >= 6 && m242_dealCnt < 8) {
                                m242_CardAnimSet(object, 1);
                                object->work[1] = 2;
                                m242_teresaCardNum++;
                            }
                            if (m242_dealCnt >= 8) {
                                m242_CardAnimSet(object, 2);
                                object->work[1] = 3;
                                m242_koopaCardNum++;
                            }
                            break;
                        case 1:
                            if (m242_dealCnt < 4) {
                                m242_CardAnimSet(object, 0);
                                object->work[1] = 1;
                                m242_kinokoCardNum++;
                            }
                            if (m242_dealCnt >= 4 && m242_dealCnt < 7) {
                                m242_CardAnimSet(object, 2);
                                object->work[1] = 3;
                                m242_koopaCardNum++;
                            }
                            if (m242_dealCnt >= 7) {
                                m242_CardAnimSet(object, 1);
                                object->work[1] = 2;
                                m242_teresaCardNum++;
                            }
                            break;
                        case 2:
                            if (m242_dealCnt < 3) {
                                m242_CardAnimSet(object, 0);
                                object->work[1] = 1;
                                m242_kinokoCardNum++;
                            }
                            if (m242_dealCnt >= 3) {
                                m242_CardAnimSet(object, 2);
                                object->work[1] = 3;
                                m242_koopaCardNum++;
                            }
                            break;
                        case 3:
                            if (m242_dealCnt < 2) {
                                m242_CardAnimSet(object, 0);
                                object->work[1] = 1;
                                m242_kinokoCardNum++;
                            }
                            if (m242_dealCnt >= 2) {
                                m242_CardAnimSet(object, 2);
                                object->work[1] = 3;
                                m242_koopaCardNum++;
                            }
                            break;
                        case 4:
                            if (m242_dealCnt < 1) {
                                m242_CardAnimSet(object, 0);
                                object->work[1] = 1;
                                m242_kinokoCardNum++;
                            }
                            if (m242_dealCnt >= 1) {
                                m242_CardAnimSet(object, 2);
                                object->work[1] = 3;
                                m242_koopaCardNum++;
                            }
                            break;
                    }
                    m242_dealCnt++;
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    card->unk_04[1] = 1;
                    card->unk_04[2] = 1;
                    break;
                case 1:
                    if (card->unk_04[3] == 0 || card->unk_04[3] == 1 || card->unk_04[3] == 4 ||
                        card->unk_04[3] == 5 || card->unk_04[3] == 8 || card->unk_04[3] == 9) {
                        if (object->trans.x < m242_cardPosTbl[card->unk_04[3]].x) {
                            object->trans.x += 50.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[card->unk_04[3]].x;
                            if (object->trans.y > 0.0f) {
                                object->trans.y -= 5.0f;
                            }
                            if (object->trans.y < 0.0f) {
                                object->trans.y = 0.0f;
                            }
                        }
                    } else if (object->trans.x > m242_cardPosTbl[card->unk_04[3]].x) {
                        object->trans.x -= 50.0f;
                    } else {
                        object->trans.x = m242_cardPosTbl[card->unk_04[3]].x;
                        if (object->trans.y > 0.0f) {
                            object->trans.y -= 5.0f;
                        }
                        if (object->trans.y < 0.0f) {
                            object->trans.y = 0.0f;
                        }
                    }
                    if (object->work[0] == 11) {
                        if (m242_cardSeStep == 0) {
                            HuAudFXPlay(0x447);
                            m242_cardSeStep = 1;
                        }
                        busy = FALSE;
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (cardObj->trans.x != m242_cardPosTbl[other->unk_04[3]].x ||
                                cardObj->trans.y != 0.0f) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            m242_phaseDoneNo = 1;
                            m242_dealCnt = 0;
                            m242_cardSeStep = 0;
                        }
                    }
                    break;
            }
            break;
        case 2:
            switch (card->unk_04[4]) {
                case 0:
                    if (card->unk_04[2] == 1) {
                        if (m242_cardSeStep == 0) {
                            HuAudFXPlay(0x44F);
                            m242_cardSeStep = 1;
                        }
                        if (card->unk_18[0] > 0.0f) {
                            card->unk_18[4] -= 0.02;
                        } else if (card->unk_18[0] < 0.0f) {
                            card->unk_18[4] += 0.02;
                        }
                        card->unk_18[1] += 8.0f;
                        object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                        if (card->unk_18[1] > 180.0f) {
                            card->unk_18[1] = 180.0f;
                        }
                        if (object->trans.y <= 0.0f) {
                            object->trans.y = 0.0f;
                            card->unk_18[4] = 1.0f;
                            if (card->unk_04[6] < 255) {
                                if (m242_cardSeStep == 1) {
                                    HuAudFXPlay(0x450);
                                    m242_cardSeStep = 2;
                                }
                                card->unk_04[6] += 7;
                            } else {
                                card->unk_18[0] = 15.0f;
                                card->unk_04[4] = 1;
                            }
                        }
                        if (card->unk_18[1] < 90.0f) {
                            card->unk_18[3] -= 0.05f;
                            card->unk_04[5] -= 3;
                        } else if (card->unk_18[1] > 90.0f) {
                            card->unk_18[3] += 0.05f;
                            card->unk_04[5] += 3;
                        }
                    } else {
                        card->unk_04[4] = 1;
                    }
                    break;
                case 1:
                    if (card->unk_04[2] == 1) {
                        if (m242_cardSeStep == 2) {
                            HuAudFXPlay(0x44F);
                            m242_cardSeStep = 0;
                        }
                        if (card->unk_18[0] > 0.0f) {
                            card->unk_18[4] -= 0.02;
                        } else if (card->unk_18[0] < 0.0f) {
                            card->unk_18[4] += 0.02;
                        }
                        card->unk_18[1] -= 8.0f;
                        object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                        if (card->unk_18[1] < 0.0f) {
                            card->unk_18[1] = 0.0f;
                        }
                        if (object->trans.y <= 0.0f) {
                            object->trans.y = 0.0f;
                            card->unk_18[4] = 1.0f;
                            card->unk_18[0] = 15.0f;
                        }
                        if (card->unk_18[1] > 90.0f) {
                            card->unk_18[3] -= 0.05f;
                            card->unk_04[5] -= 3;
                        } else if (card->unk_18[1] < 90.0f) {
                            card->unk_18[3] += 0.05f;
                            card->unk_04[5] += 3;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 1 || cardObj->trans.y != 0.0f || other->unk_18[1] != 0.0f) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 2;
                                other->unk_04[2] = 0;
                                other->unk_04[3] = 0;
                                m242_slotUsedTbl[i] = 0;
                            }
                        }
                    }
                    break;
                case 2:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x447);
                    }
                    if (object->trans.y < (object->work[0] + 1) * 2) {
                        object->trans.y += 1.0f;
                    } else {
                        object->trans.y = (object->work[0] + 1) * 2;
                        if (m242_cardPosTbl[0].x < object->trans.x) {
                            object->trans.x -= 50.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[0].x;
                        }
                        if (m242_cardPosTbl[0].y < object->trans.z) {
                            object->trans.z -= 50.0f;
                        } else {
                            object->trans.z = m242_cardPosTbl[0].y;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 2 || cardObj->trans.x != m242_cardPosTbl[0].x ||
                                cardObj->trans.z != m242_cardPosTbl[0].y) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 3;
                                m242_cardSeStep = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x448);
                    }
                    if (object->trans.y == 2.0f) {
                        m242_shuffleCardNo = object->work[0];
                        if (m242_cardPosTbl[1].x > object->trans.x) {
                            object->trans.x += 50.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[1].x;
                        }
                        if (m242_cardPosTbl[1].y > object->trans.z) {
                            object->trans.z += 50.0f;
                        } else {
                            object->trans.z = m242_cardPosTbl[1].y;
                        }
                        if (object->trans.x == m242_cardPosTbl[1].x &&
                            object->trans.z == m242_cardPosTbl[1].y) {
                            m242_shuffleCnt++;
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 4;
                            }
                        }
                    }
                    break;
                case 4:
                    if (object->work[0] != m242_shuffleCardNo) {
                        object->trans.y -= 2.0f;
                        card->unk_04[4] = 5;
                    } else if (object->trans.y < 26.0f) {
                        object->trans.y += 5.0f;
                    } else {
                        object->trans.y = 26.0f;
                        if (m242_cardPosTbl[0].x < object->trans.x) {
                            object->trans.x -= 50.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[0].x;
                        }
                        if (m242_cardPosTbl[0].y < object->trans.z) {
                            object->trans.z -= 50.0f;
                        } else {
                            object->trans.z = m242_cardPosTbl[0].y;
                        }
                        if (object->trans.x == m242_cardPosTbl[0].x &&
                            object->trans.z == m242_cardPosTbl[0].y) {
                            card->unk_04[4] = 5;
                        }
                    }
                    break;
                case 5:
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 5 || cardObj->trans.x != m242_cardPosTbl[0].x ||
                                cardObj->trans.z != m242_cardPosTbl[0].y) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                if (m242_shuffleCnt > 0) {
                                    other->unk_04[4] = 6;
                                    if (i == 11) {
                                        m242_shuffleCnt = 0;
                                    }
                                    m242_cardSeStep = 0;
                                } else {
                                    other->unk_04[4] = 3;
                                }
                            }
                        }
                    }
                    break;
                case 6:
                    slot = (u8)(rand8() % 12);
                    while (TRUE) {
                        if (m242_slotUsedTbl[slot] == 0) {
                            card->unk_04[3] = slot;
                            m242_slotUsedTbl[slot] = 1;
                            card->unk_04[4] = 7;
                            break;
                        }
                        if (++slot >= 12) {
                            slot = 0;
                        }
                    }
                    break;
                case 7:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x449);
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].x > object->trans.x) {
                        object->trans.x += 50.0f;
                    } else {
                        object->trans.x = m242_cardPosTbl[card->unk_04[3]].x;
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].y > object->trans.z) {
                        object->trans.z += 50.0f;
                    } else {
                        object->trans.z = m242_cardPosTbl[card->unk_04[3]].y;
                    }
                    if (object->trans.x == m242_cardPosTbl[card->unk_04[3]].x &&
                        object->trans.z == m242_cardPosTbl[card->unk_04[3]].y) {
                        if (object->trans.y > 0.0f) {
                            object->trans.y -= 5.0f;
                        }
                        if (object->trans.y < 0.0f) {
                            object->trans.y = 0.0f;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 7 ||
                                cardObj->trans.x != m242_cardPosTbl[other->unk_04[3]].x ||
                                cardObj->trans.z != m242_cardPosTbl[other->unk_04[3]].y ||
                                cardObj->trans.y != 0.0f) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 0;
                            }
                            m242_phaseDoneNo = 2;
                        }
                    }
                    break;
            }
            break;
        case 3:
            switch (card->unk_04[4]) {
                case 0:
                    if (card->unk_04[2] == 1) {
                        if (m242_cardSeStep == 0) {
                            HuAudFXPlay(0x44F);
                            m242_cardSeStep = 1;
                        }
                        if (card->unk_18[0] > 0.0f) {
                            card->unk_18[4] -= 0.02;
                        } else if (card->unk_18[0] < 0.0f) {
                            card->unk_18[4] += 0.02;
                        }
                        card->unk_18[1] += 8.0f;
                        object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                        if (card->unk_18[1] > 180.0f) {
                            card->unk_18[1] = 180.0f;
                        }
                        if (object->trans.y <= 0.0f) {
                            object->trans.y = 0.0f;
                            card->unk_18[4] = 1.0f;
                            if (card->unk_04[6] < 255) {
                                if (m242_cardSeStep == 1) {
                                    HuAudFXPlay(0x450);
                                    m242_cardSeStep = 2;
                                }
                                card->unk_04[6] += 7;
                            } else {
                                card->unk_18[0] = 15.0f;
                                card->unk_04[4] = 1;
                            }
                        }
                        if (card->unk_18[1] < 90.0f) {
                            card->unk_18[3] -= 0.05f;
                            card->unk_04[5] -= 3;
                        } else if (card->unk_18[1] > 90.0f) {
                            card->unk_18[3] += 0.05f;
                            card->unk_04[5] += 3;
                        }
                    } else {
                        card->unk_04[4] = 1;
                    }
                    break;
                case 1:
                    if (card->unk_04[2] == 1) {
                        if (m242_cardSeStep == 2) {
                            HuAudFXPlay(0x44F);
                            m242_cardSeStep = 0;
                        }
                        if (card->unk_18[0] > 0.0f) {
                            card->unk_18[4] -= 0.02;
                        } else if (card->unk_18[0] < 0.0f) {
                            card->unk_18[4] += 0.02;
                        }
                        card->unk_18[1] -= 8.0f;
                        object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                        if (card->unk_18[1] < 0.0f) {
                            card->unk_18[1] = 0.0f;
                        }
                        if (object->trans.y <= 0.0f) {
                            object->trans.y = 0.0f;
                            card->unk_18[4] = 1.0f;
                            card->unk_18[0] = 15.0f;
                        }
                        if (card->unk_18[1] > 90.0f) {
                            card->unk_18[3] -= 0.05f;
                            card->unk_04[5] -= 3;
                        } else if (card->unk_18[1] < 90.0f) {
                            card->unk_18[3] += 0.05f;
                            card->unk_04[5] += 3;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 1 || cardObj->trans.y != 0.0f || other->unk_18[1] != 0.0f) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 2;
                                other->unk_04[2] = 0;
                                m242_slotUsedTbl[i] = 0;
                            }
                        }
                    }
                    break;
                case 2:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x447);
                    }
                    if (object->trans.y < (object->work[0] + 1) * 2) {
                        object->trans.y += 1.0f;
                    } else {
                        object->trans.y = (object->work[0] + 1) * 2;
                        if (card->unk_04[3] == 0 || card->unk_04[3] == 1 || card->unk_04[3] == 4 ||
                            card->unk_04[3] == 5 || card->unk_04[3] == 8 || card->unk_04[3] == 9) {
                            if (m242_cardPosTbl[5].x > object->trans.x) {
                                object->trans.x += 40.0f;
                            } else {
                                object->trans.x = m242_cardPosTbl[5].x;
                            }
                            if (m242_cardPosTbl[5].y < object->trans.z) {
                                object->trans.z -= 40.0f;
                            } else if (object->trans.z < m242_cardPosTbl[5].y) {
                                object->trans.z += 40.0f;
                            }
                            targetZ = m242_cardPosTbl[5].y;
                        } else {
                            if (m242_cardPosTbl[6].x < object->trans.x) {
                                object->trans.x -= 40.0f;
                            } else {
                                object->trans.x = m242_cardPosTbl[6].x;
                            }
                            if (m242_cardPosTbl[6].y < object->trans.z) {
                                object->trans.z -= 40.0f;
                            } else if (object->trans.z < m242_cardPosTbl[6].y) {
                                object->trans.z += 40.0f;
                            }
                            targetZ = m242_cardPosTbl[6].y;
                        }
                        if (targetZ - 30.0f < object->trans.z && object->trans.z < targetZ + 30.0f) {
                            object->trans.z = targetZ;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[3] == 0 || other->unk_04[3] == 1 || other->unk_04[3] == 4 ||
                                other->unk_04[3] == 5 || other->unk_04[3] == 8 || other->unk_04[3] == 9) {
                                if (other->unk_04[4] != 2 || cardObj->trans.x != m242_cardPosTbl[5].x ||
                                    cardObj->trans.z != m242_cardPosTbl[5].y) {
                                    busy = TRUE;
                                }
                            } else if (other->unk_04[4] != 2 ||
                                       cardObj->trans.x != m242_cardPosTbl[6].x ||
                                       cardObj->trans.z != m242_cardPosTbl[6].y) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 3;
                                m242_cardSeStep = 0;
                                if (other->unk_04[3] == 0 || other->unk_04[3] == 1 || other->unk_04[3] == 4 ||
                                    other->unk_04[3] == 5 || other->unk_04[3] == 8 || other->unk_04[3] == 9) {
                                    other->unk_04[3] = 5;
                                } else {
                                    other->unk_04[3] = 6;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x448);
                    }
                    if (card->unk_04[3] == 5) {
                        if (m242_cardPosTbl[6].x > object->trans.x) {
                            object->trans.x += 40.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[6].x;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 3 || cardObj->trans.x != m242_cardPosTbl[6].x) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 4;
                            }
                        }
                    }
                    break;
                case 4:
                    if (card->unk_04[3] == 6) {
                        if (m242_cardPosTbl[5].x < object->trans.x) {
                            object->trans.x -= 40.0f;
                        } else {
                            object->trans.x = m242_cardPosTbl[5].x;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[3] == 6 &&
                                (other->unk_04[4] != 4 || cardObj->trans.x != m242_cardPosTbl[5].x)) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 7;
                                m242_cardSeStep = 0;
                            }
                        }
                    }
                    break;
                case 7:
                    slot = (u8)(rand8() % 12);
                    if (card->unk_04[3] == 5) {
                        while (TRUE) {
                            if ((slot == 0 || slot == 1 || slot == 4 || slot == 5 || slot == 8 || slot == 9) &&
                                m242_slotUsedTbl[slot] == 0) {
                                card->unk_04[3] = slot;
                                m242_slotUsedTbl[slot] = 1;
                                card->unk_04[4] = 8;
                                break;
                            }
                            if (++slot >= 12) {
                                slot = 0;
                            }
                        }
                    } else {
                        while (TRUE) {
                            if ((slot == 2 || slot == 3 || slot == 6 || slot == 7 || slot == 10 || slot == 11) &&
                                m242_slotUsedTbl[slot] == 0) {
                                card->unk_04[3] = slot;
                                m242_slotUsedTbl[slot] = 1;
                                card->unk_04[4] = 8;
                                break;
                            }
                            if (++slot >= 12) {
                                slot = 0;
                            }
                        }
                    }
                    break;
                case 8:
                    if (object->work[0] == 11 && m242_cardSeStep == 0) {
                        m242_cardSeStep = 1;
                        HuAudFXPlay(0x449);
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].x < object->trans.x) {
                        object->trans.x -= 40.0f;
                    } else if (object->trans.x < m242_cardPosTbl[card->unk_04[3]].x) {
                        object->trans.x += 40.0f;
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].x - 30.0f < object->trans.x &&
                        object->trans.x < m242_cardPosTbl[card->unk_04[3]].x + 30.0f) {
                        object->trans.x = m242_cardPosTbl[card->unk_04[3]].x;
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].y < object->trans.z) {
                        object->trans.z -= 40.0f;
                    } else if (object->trans.z < m242_cardPosTbl[card->unk_04[3]].y) {
                        object->trans.z += 40.0f;
                    }
                    if (m242_cardPosTbl[card->unk_04[3]].y - 30.0f < object->trans.z &&
                        object->trans.z < m242_cardPosTbl[card->unk_04[3]].y + 30.0f) {
                        object->trans.z = m242_cardPosTbl[card->unk_04[3]].y;
                    }
                    if (object->trans.x == m242_cardPosTbl[card->unk_04[3]].x &&
                        object->trans.z == m242_cardPosTbl[card->unk_04[3]].y) {
                        if (object->trans.y > 0.0f) {
                            object->trans.y -= 5.0f;
                        }
                        if (object->trans.y < 0.0f) {
                            object->trans.y = 0.0f;
                        }
                    }
                    busy = FALSE;
                    if (object->work[0] == 11) {
                        for (i = 0; i < 12; i++) {
                            other = &STACKED_DECK_CARDS[i];
                            cardObj = other->obj;
                            if (other->unk_04[4] != 8 ||
                                cardObj->trans.x != m242_cardPosTbl[other->unk_04[3]].x ||
                                cardObj->trans.z != m242_cardPosTbl[other->unk_04[3]].y ||
                                cardObj->trans.y != 0.0f) {
                                busy = TRUE;
                            }
                        }
                        if (!busy) {
                            for (i = 0; i < 12; i++) {
                                other = &STACKED_DECK_CARDS[i];
                                other->unk_04[4] = 0;
                            }
                            m242_phaseDoneNo = 3;
                        }
                    }
                    break;
            }
            break;
        case 7:
            if (m242_pickCardType == 4 && card->unk_04[1] == 1) {
                if (card->unk_04[0] == 0 && object->work[1] == 3) {
                    card->unk_04[0] = 1;
                    m242_pickCardType = 3;
                }
            } else if (card->unk_04[0] == 1 && card->unk_04[1] == 1) {
                if (card->unk_18[0] > 0.0f) {
                    card->unk_18[4] -= 0.02;
                } else if (card->unk_18[0] < 0.0f) {
                    card->unk_18[4] += 0.02;
                }
                object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                card->unk_18[1] += 45.0f;
                if (card->unk_18[1] > 900.0f) {
                    card->unk_18[1] = 900.0f;
                }
                if (card->unk_18[0] > 0.0f) {
                    card->unk_18[3] -= 0.05f;
                    card->unk_04[5] -= 3;
                } else if (card->unk_18[0] < 0.0f) {
                    card->unk_18[3] += 0.05f;
                    card->unk_04[5] += 3;
                }
                if (object->trans.y <= 0.0f) {
                    object->trans.y = 0.0f;
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    card->unk_18[4] = 1.0f;
                    switch (object->work[1]) {
                        case 1:
                            m242_CardAnimSet(object, 3);
                            break;
                        case 2:
                            m242_CardAnimSet(object, 4);
                            break;
                        case 3:
                            m242_CardAnimSet(object, 5);
                            break;
                    }
                    if (++card->unk_04[7] >= 7) {
                        card->unk_04[7] = 0;
                        m242_phaseDoneNo = 7;
                    }
                }
            }
            break;
        case 8:
        case 9:
        case 11:
        case 12:
        case 14:
        case 15:
        case 16:
        case 17:
            if (card->unk_04[0] == 1) {
                card->unk_18[2] -= 0.02f;
                card->unk_18[3] -= 0.02f;
                card->unk_18[4] -= 0.02f;
                card->unk_04[6] -= 15;
                if (card->unk_18[2] < 0.1f) {
                    card->unk_18[2] = 0.1f;
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    card->unk_04[0] = 0;
                    card->unk_04[1] = 0;
                    m242_slotUsedTbl[card->unk_04[3]] = 0;
                    card->unk_04[3] = 0;
                    card->unk_18[0] = 15.0f;
                    card->unk_18[1] = 0.0f;
                    card->unk_04[5] = 150;
                    card->unk_04[6] = 0;
                    card->unk_18[2] = 1.0f;
                    card->unk_18[3] = 1.0f;
                    card->unk_18[4] = 1.0f;
                }
            }
            break;
    }

    if (card->unk_04[5] < 0) {
        card->unk_04[5] = 0;
    }
    if (card->unk_04[5] >= 151) {
        card->unk_04[5] = 150;
    }
    Hu3DModelTPLvlSet(object->model[1], card->unk_04[5]);
    if (card->unk_04[6] < 0) {
        card->unk_04[6] = 0;
    }
    if (card->unk_04[6] >= 256) {
        card->unk_04[6] = 255;
    }
    Hu3DModelTPLvlSet(object->model[2], card->unk_04[6]);
    object->rot.x = 0.0f;
    object->rot.y = 180.0f;
    object->rot.z = m242_AngleAdd(card->unk_18[1], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
    object->scale.x = card->unk_18[2];
    object->scale.y = card->unk_18[2];
    object->scale.z = card->unk_18[2];
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    if (card->unk_18[3] < 0.1f) {
        card->unk_18[3] = 0.1f;
    }
    if (card->unk_18[3] > 1.0f) {
        card->unk_18[3] = 1.0f;
    }
    Hu3DModelScaleSet(object->model[1], card->unk_18[3], object->scale.y, card->unk_18[4]);
    Hu3DModelScaleSet(object->model[2], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    card->unk_18[5] = 10.0f;
    if (object->trans.z < -100.0f) {
        card->unk_18[6] = 40.0f;
    } else if (object->trans.z < 400.0f) {
        card->unk_18[6] = 35.0f;
    } else {
        card->unk_18[6] = 30.0f;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x + card->unk_18[5], -4.0f,
                    object->trans.z + card->unk_18[6]);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
}

void m242_CardObjInit(omObjData *object) {
    StackedDeckObjWork *card = &STACKED_DECK_CARDS[object->work[0]];

    object->model[0] = Hu3DModelRead(0x4B0008, 0x2A9);
    object->model[1] = Hu3DModelRead(0x4B0009, 0x2A9);
    object->model[2] = Hu3DModelRead(0x4B000B, 0x2A9);
    if (object->work[0] == 0) {
        m242_cardAnimDataTbl[0] = DataRead(0x4B0002);
        m242_cardAnimDataTbl[1] = DataRead(0x4B0003);
        m242_cardAnimDataTbl[2] = DataRead(0x4B0004);
        m242_cardAnimDataTbl[3] = DataRead(0x4B0005);
        m242_cardAnimDataTbl[4] = DataRead(0x4B0006);
        m242_cardAnimDataTbl[5] = DataRead(0x4B0007);
    }
    m242_cardAnimTbl[object->work[0]] =
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, m242_cardAnimDataTbl[0], 0, "card_k_DEF");
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    card->unk_04[5] = 150;
    Hu3DModelTPLvlInit(object->model[1]);
    Hu3DModelTPLvlSet(object->model[1], card->unk_04[5]);
    card->unk_04[6] = 0;
    Hu3DModelTPLvlInit(object->model[2]);
    Hu3DModelTPLvlSet(object->model[2], card->unk_04[6]);
    card->unk_18[0] = 15.0f;
    card->unk_18[1] = 0.0f;
    object->rot.x = 0.0f;
    object->rot.y = 180.0f;
    object->rot.z = m242_AngleAdd(card->unk_18[1], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
    card->unk_18[2] = 1.0f;
    card->unk_18[3] = 1.0f;
    card->unk_18[4] = 1.0f;
    object->scale.x = card->unk_18[2];
    object->scale.y = card->unk_18[2];
    object->scale.z = card->unk_18[2];
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], card->unk_18[3], object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[2], object->scale.x, object->scale.y, object->scale.z);
    object->trans.x = m242_cardPosTbl[object->work[0]].x;
    object->trans.y = 0.0f;
    object->trans.z = m242_cardPosTbl[object->work[0]].y;
    card->unk_18[5] = 0.0f;
    card->unk_18[6] = 0.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x + card->unk_18[5], -4.0f, object->trans.z + card->unk_18[6]);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->func = m242_CardObjMain;
}

void m242_CardObjCreateAll(void) {
    s16 i;

    for (i = 0; i < 12; i++) {
        StackedDeckObjWork *card = &STACKED_DECK_CARDS[i];
        omObjData *obj = omAddObj(0x226, 3, 3, -1, m242_CardObjInit);

        obj->work[0] = i;
        card->obj = obj;
    }
}

void m242_CardChrObjMain(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 18];
    omObjData *player;
    omObjData *cardObj;
    s16 i;

    for (i = 0; i < 4; i++) {
        player = STACKED_DECK_PLAYERS[i].obj;
        if (player->work[1] == 0) {
            break;
        }
    }

    switch (m242_phase) {
        case 8:
            if (object->work[0] != 0) {
                break;
            }
            switch (card->unk_04[0]) {
                case 0:
                    for (i = 0; i < 12; i++) {
                        cardObj = STACKED_DECK_CARDS[i].obj;
                        if (STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                            card->unk_04[0] = 1;
                            object->trans.x = cardObj->trans.x;
                            object->trans.y = 0.0f;
                            object->trans.z = cardObj->trans.z;
                            card->unk_18[1] = 0.0f;
                            break;
                        }
                    }
                    break;
                case 1:
                    card->unk_18[1] += 30.0f;
                    m242_MotShiftSet(object, 0, 0, 5, 2, &card->unk_04[1]);
                    if (m242_smokeState == 0) {
                        m242_smokeState = 1;
                        HuAudFXPlay(0x446);
                    }
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    card->unk_18[0] = 20.0f;
                    card->unk_18[4] = 1.0f;
                    card->unk_04[0] = 2;
                    HuAudFXPlay(0x44C);
                    if (!(GwPlayer[player->work[0]].stat & 1)) {
                        omVibrate(player->work[0], 2, 3, 10);
                    }
                    break;
                case 2:
                    if (card->unk_18[0] > 0.0f) {
                        card->unk_18[4] -= 0.03;
                    } else if (card->unk_18[0] < 0.0f) {
                        card->unk_18[4] += 0.03;
                    }
                    card->unk_18[1] += 30.0f;
                    object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                    if (object->trans.y < 0.0f) {
                        object->trans.y = 0.0f;
                        card->unk_18[4] = 1.0f;
                        card->unk_04[0] = 3;
                    }
                    break;
                case 3:
                    card->unk_04[0] = 4;
                    break;
                case 4:
                    m242_MotShiftSet(object, 1, 0, 5, 2, &card->unk_04[1]);
                    if (object->trans.z < 150.0f) {
                        object->trans.z += 25.0f;
                        card->unk_18[1] = 0.0f;
                    } else {
                        if (card->unk_04[3] == 0) {
                            if (object->trans.x <= player->trans.x) {
                                card->unk_04[3] = 1;
                            } else {
                                card->unk_04[3] = 2;
                            }
                        }
                        if (card->unk_04[3] == 1) {
                            object->trans.x -= 25.0f;
                            card->unk_18[1] = 270.0f;
                        } else if (card->unk_04[3] == 2) {
                            object->trans.x += 25.0f;
                            card->unk_18[1] = 90.0f;
                        }
                    }
                    if (object->trans.x < -1000.0f || object->trans.x > 1000.0f) {
                        card->unk_04[3] = 0;
                        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        card->unk_04[0] = 5;
                    }
                    break;
                case 5:
                    break;
            }
            break;
        case 9:
            if (object->work[0] != 1) {
                break;
            }
            switch (card->unk_04[0]) {
                case 0:
                    for (i = 0; i < 12; i++) {
                        cardObj = STACKED_DECK_CARDS[i].obj;
                        if (STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                            card->unk_04[0] = 1;
                            object->trans.x = cardObj->trans.x;
                            object->trans.y = 0.0f;
                            object->trans.z = cardObj->trans.z;
                            card->unk_18[1] = 0.0f;
                            card->unk_18[5] = 0.1f;
                            card->unk_04[4] = 0;
                            break;
                        }
                    }
                    break;
                case 1:
                    card->unk_18[1] += 30.0f;
                    card->unk_18[5] += 0.05f;
                    if (card->unk_18[5] >= 1.7f) {
                        card->unk_18[5] = 1.7f;
                    }
                    card->unk_04[4] += 10;
                    if (card->unk_04[4] >= 256) {
                        card->unk_04[4] = 255;
                    }
                    m242_MotShiftSet(object, 0, 0, 5, 2, &card->unk_04[1]);
                    if (m242_smokeState == 0) {
                        m242_smokeState = 1;
                        HuAudFXPlay(0x446);
                    }
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    card->unk_18[0] = 20.0f;
                    card->unk_18[4] = card->unk_18[5];
                    card->unk_04[0] = 2;
                    HuAudFXPlay(0x44D);
                    card->unk_04[5] = 0;
                    if (!(GwPlayer[player->work[0]].stat & 1)) {
                        omVibrate(player->work[0], 10, 0, 10);
                    }
                    break;
                case 2:
                    card->unk_18[4] = card->unk_18[5];
                    card->unk_18[1] += 30.0f;
                    card->unk_18[5] += 0.05f;
                    if (card->unk_18[5] >= 1.7f) {
                        card->unk_18[5] = 1.7f;
                    }
                    card->unk_04[4] += 10;
                    if (card->unk_04[4] >= 256) {
                        card->unk_04[4] = 255;
                    }
                    object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                    if (object->trans.y < 0.0f) {
                        object->trans.y = 0.0f;
                        card->unk_18[4] = card->unk_18[5];
                        card->unk_04[0] = 3;
                    }
                    if (++card->unk_04[5] >= 45) {
                        card->unk_04[5] = 0;
                        HuAudFXPlay(0x44D);
                    }
                    break;
                case 3:
                    if (card->unk_04[2] < 15) {
                        card->unk_04[4] -= 15;
                    } else {
                        card->unk_04[4] += 15;
                    }
                    if (card->unk_04[4] >= 256) {
                        card->unk_04[4] = 255;
                    } else if (card->unk_04[4] < 0) {
                        card->unk_04[4] = 0;
                    }
                    if (++card->unk_04[2] >= 31) {
                        card->unk_04[0] = 4;
                        card->unk_04[2] = 0;
                        card->unk_04[4] = 255;
                    }
                    if (++card->unk_04[5] >= 45) {
                        card->unk_04[5] = 0;
                        HuAudFXPlay(0x44D);
                    }
                    break;
                case 4:
                    if (player->trans.z < 1500.0f) {
                        card->unk_18[1] =
                            atan2df(player->trans.x - object->trans.x, player->trans.z - object->trans.z);
                        m242_VelCalc(player->trans.x, player->trans.z, object->trans.x,
                                                   object->trans.z, &card->unk_18[2], &card->unk_18[3], 15.0f);
                    } else {
                        card->unk_18[1] = atan2df(player->trans.x - object->trans.x, 2500.0f - object->trans.z);
                        m242_VelCalc(player->trans.x, 2500.0f, object->trans.x, object->trans.z,
                                                   &card->unk_18[2], &card->unk_18[3], 17.0f);
                    }
                    object->trans.x += card->unk_18[2];
                    object->trans.z += card->unk_18[3];
                    if (object->trans.x < -2000.0f || object->trans.x > 2000.0f || object->trans.z > 2000.0f) {
                        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        card->unk_04[0] = 5;
                        card->unk_18[2] = 0.0f;
                        card->unk_18[3] = 0.0f;
                        card->unk_18[5] = 1.7f;
                        card->unk_04[4] = 0;
                    }
                    if (++card->unk_04[5] >= 45) {
                        card->unk_04[5] = 0;
                        HuAudFXPlay(0x44D);
                    }
                    break;
                case 5:
                    break;
            }
            object->scale.x = object->scale.y = object->scale.z = card->unk_18[5];
            Hu3DModelTPLvlSet(object->model[0], card->unk_04[4]);
            Hu3DModelTPLvlSet(object->model[1], card->unk_04[4]);
            break;
        case 11:
        case 14:
        case 15:
        case 16:
        case 17:
            if (object->work[0] != 2) {
                break;
            }
            switch (card->unk_04[0]) {
                case 0:
                    for (i = 0; i < 12; i++) {
                        cardObj = STACKED_DECK_CARDS[i].obj;
                        if (STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                            card->unk_04[0] = 1;
                            object->trans.x = cardObj->trans.x;
                            object->trans.y = 0.0f;
                            object->trans.z = cardObj->trans.z;
                            card->unk_18[1] = 0.0f;
                            break;
                        }
                    }
                    break;
                case 1:
                    card->unk_18[1] += 30.0f;
                    m242_MotShiftSet(object, 0, 0, 5, 2, &card->unk_04[1]);
                    if (m242_smokeState == 0) {
                        m242_smokeState = 1;
                        HuAudFXPlay(0x446);
                    }
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    card->unk_18[0] = 20.0f;
                    card->unk_18[4] = 1.0f;
                    card->unk_04[0] = 2;
                    HuAudFXPlay(0x44B);
                    break;
                case 2:
                    if (card->unk_18[0] > 0.0f) {
                        card->unk_18[4] -= 0.03;
                    } else if (card->unk_18[0] < 0.0f) {
                        card->unk_18[4] += 0.03;
                    }
                    card->unk_18[1] += 30.0f;
                    object->trans.y = m242_GravityCalc(object->trans.y, &card->unk_18[0], 1.0f);
                    if (object->trans.y < 0.0f) {
                        object->trans.y = 0.0f;
                        card->unk_18[4] = 1.0f;
                        card->unk_04[0] = 3;
                    }
                    break;
                case 3:
                    Hu3DMotionSpeedSet(object->model[0], 2.0f);
                    card->unk_04[0] = 4;
                    break;
                case 4:
                    m242_MotShiftSet(object, 1, 0, 5, 2, &card->unk_04[1]);
                    card->unk_18[1] = atan2df(player->trans.x - object->trans.x, player->trans.z - object->trans.z);
                    m242_VelCalc(player->trans.x, player->trans.z, object->trans.x, object->trans.z,
                                               &card->unk_18[2], &card->unk_18[3], 30.0f);
                    object->trans.x += card->unk_18[2];
                    object->trans.z += card->unk_18[3];
                    if (object->trans.x < player->trans.x + 120.0f && player->trans.x - 120.0f < object->trans.x &&
                        object->trans.z < player->trans.z + 120.0f && player->trans.z - 120.0f < object->trans.z) {
                        card->unk_04[0] = 5;
                    }
                    break;
                case 5:
                    if (card->unk_04[3] == 0) {
                        if (object->trans.x <= 0.0f) {
                            card->unk_04[3] = 1;
                        } else {
                            card->unk_04[3] = 2;
                        }
                    }
                    m242_MotShiftSet(object, 0, 0, 5, 2, &card->unk_04[1]);
                    if (++card->unk_04[2] >= 16) {
                        card->unk_04[0] = 6;
                        card->unk_04[2] = 0;
                    }
                    break;
                case 6:
                    m242_MotShiftSet(object, 1, 0, 5, 2, &card->unk_04[1]);
                    if (object->trans.z < 150.0f) {
                        object->trans.z += 30.0f;
                        card->unk_18[1] = 0.0f;
                    } else if (card->unk_04[3] == 1) {
                        object->trans.x -= 25.0f;
                        card->unk_18[1] = 270.0f;
                    } else if (card->unk_04[3] == 2) {
                        object->trans.x += 25.0f;
                        card->unk_18[1] = 90.0f;
                    }
                    if (object->trans.x < -1000.0f || object->trans.x > 1000.0f) {
                        card->unk_04[3] = 0;
                        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DMotionSpeedSet(object->model[0], 1.0f);
                        card->unk_18[2] = 0.0f;
                        card->unk_18[3] = 0.0f;
                        card->unk_04[0] = 7;
                    }
                    break;
                case 7:
                    break;
            }
            break;
    }

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.5f, object->trans.z);
    if (card->unk_18[1] > 720.0f) {
        card->unk_18[1] = 720.0f;
    }
    object->rot.y = m242_AngleAdd(card->unk_18[1], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], card->unk_18[4], object->scale.y, card->unk_18[4]);
}

void m242_CardChrObjInit(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 18];

    switch (object->work[0]) {
        case 0:
            object->model[0] = Hu3DModelRead(0xA0000, 0x2B9);
            omObjMotionRead(object, 0, 0xA0001);
            omObjMotionRead(object, 1, 0xA0006);
            Hu3DMotionModelSet(object->model[0], object->motion[0]);
            Hu3DMotionAttrSet(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 0.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.0f;
            object->scale.y = 1.0f;
            object->scale.z = 1.0f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            break;
        case 1:
            object->model[0] = Hu3DModelRead(0xA00C4, 0x2A9);
            omObjMotionRead(object, 0, 0xA00C7);
            Hu3DMotionModelSet(object->model[0], object->motion[0]);
            Hu3DMotionAttrSet(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 50.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.7f;
            object->scale.y = 1.7f;
            object->scale.z = 1.7f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            card->unk_04[4] = 0;
            Hu3DModelTPLvlInit(object->model[0]);
            Hu3DModelTPLvlSet(object->model[0], card->unk_04[4]);
            break;
        case 2:
            object->model[0] = Hu3DModelRead(0xA00EE, 0x2B9);
            omObjMotionRead(object, 0, 0xA00EF);
            omObjMotionRead(object, 1, 0xA0103);
            Hu3DMotionModelSet(object->model[0], object->motion[0]);
            Hu3DMotionAttrSet(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 0.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.0f;
            object->scale.y = 1.0f;
            object->scale.z = 1.0f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            break;
    }
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    if (object->work[0] == 1) {
        Hu3DModelTPLvlInit(object->model[1]);
        Hu3DModelTPLvlSet(object->model[1], card->unk_04[4]);
    } else {
        Hu3DModelRemakeStatic(object->model[1]);
        Hu3DModelDynamicFree(object->model[1]);
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.5f, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    card->unk_18[4] = 1.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], card->unk_18[4], object->scale.y, card->unk_18[4]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->func = m242_CardChrObjMain;
}

void m242_CardChrObjCreateAll(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        StackedDeckObjWork *card = &m242_objWorkTbl[i + 18];
        omObjData *obj = omAddObj(0x23A, 5, 5, -1, m242_CardChrObjInit);

        obj->work[0] = i;
        card->obj = obj;
    }
}

void m242_SmokeObjMain(omObjData *object) {
    StackedDeckObjWork *effect = &m242_objWorkTbl[21];
    omObjData *cardObj;
    s16 i;

    switch (m242_smokeState) {
        case 0:
            break;
        case 1:
            for (i = 0; i < 12; i++) {
                cardObj = STACKED_DECK_CARDS[i].obj;
                if (STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                    break;
                }
            }
            object->trans.x = cardObj->trans.x;
            object->trans.y = -50.0f;
            object->trans.z = cardObj->trans.z + 150.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            m242_smokeState = 2;
            break;
        case 2:
            effect->unk_18[0] += 0.7f;
            Hu3DSprModelFrameSet(effect->unk_04[0], (s32)effect->unk_18[0]);
            if (Hu3DSprModelFrameGet(effect->unk_04[0]) >= 14) {
                m242_smokeState = 0;
                effect->unk_18[0] = 0.0f;
            }
            break;
    }
}

void m242_SmokeObjInit(omObjData *object) {
    StackedDeckObjWork *effect = &m242_objWorkTbl[21];
    void *data;
    u16 sprite;

    data = DataRead(0xB);
    sprite = Hu3DSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    object->model[0] = Hu3DSprModelData[sprite].modelId;
    effect->unk_04[0] = sprite;
    Hu3DSprModelAttrSet(sprite, 1, 1);
    Hu3DSprModelColorSet(effect->unk_04[0], 200, 200, 200);
    Hu3DSprModelTPLvlSet(effect->unk_04[0], 255);
    Hu3DSprModelFrameSet(effect->unk_04[0], 14);
    object->scale.x = object->scale.y = object->scale.z = 10.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    object->func = m242_SmokeObjMain;
}

void m242_SmokeObjCreate(void) {
    omObjData *obj = omAddObj(0x244, 1, 0, -1, m242_SmokeObjInit);
    obj->work[0] = 0;
}

void m242_HitEffObjMain(omObjData *object) {
    StackedDeckObjWork *effect = &m242_objWorkTbl[22];
    omObjData *player;
    s16 i;

    for (i = 0; i < 4; i++) {
        player = STACKED_DECK_PLAYERS[i].obj;
        if (player->work[1] == 0) {
            break;
        }
    }

    switch (m242_hitEffState) {
        case 0:
            break;
        case 1:
            object->trans.x = player->trans.x;
            object->trans.y = 60.0f;
            object->trans.z = player->trans.z + 60.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            m242_hitEffState = 2;
            if (!(GwPlayer[player->work[0]].stat & 1)) {
                omVibrate(player->work[0], 20, 0, 20);
            }
            break;
        case 2:
            if (effect->unk_04[1] < 5) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                effect->unk_04[1]++;
            } else {
                m242_hitEffState = 0;
                effect->unk_04[1] = 0;
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

void m242_HitEffObjInit(omObjData *object) {
    StackedDeckObjWork *effect = &m242_objWorkTbl[22];
    void *data;
    u16 sprite;

    data = DataRead(0x4B0001);
    sprite = Hu3DSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    object->model[0] = Hu3DSprModelData[sprite].modelId;
    effect->unk_04[0] = sprite;
    Hu3DSprModelAttrSet(sprite, 2, 0);
    Hu3DSprModelFrameSet(effect->unk_04[0], 0);
    Hu3DMotionSpeedSet(object->model[0], 3.0f);
    object->scale.x = object->scale.y = object->scale.z = 5.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->func = m242_HitEffObjMain;
}

void m242_HitEffObjCreate(void) {
    omObjData *obj = omAddObj(0x24E, 1, 0, -1, m242_HitEffObjInit);
    obj->work[0] = 0;
}

void m242_DecoObjMain(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 23];
    StackedDeckObjWork *spinner;
    f32 speed;
    s16 i;
    s16 moving;

    switch (m242_phase) {
        case 8:
            speed = 2.0f;
            break;
        case 9:
            speed = 4.0f;
            break;
        default:
            speed = 1.0f;
            break;
    }

    switch (m242_phase) {
        case 2:
            card->unk_18[0] -= m242_decoSpeedTbl[object->work[0]] * 5.0f;
            if (card->unk_18[0] < 0.0f) {
                card->unk_18[0] = m242_AngleAdd(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        case 3:
            card->unk_18[0] += m242_decoSpeedTbl[object->work[0]] * 5.0f;
            if (card->unk_18[0] > 360.0f) {
                card->unk_18[0] = m242_AngleAdd(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        case 11:
            if (object->work[0] == 0 || object->work[0] == 2) {
                card->unk_18[0] += m242_decoSpeedTbl[object->work[0]] * 5.0f;
            } else {
                card->unk_18[0] -= m242_decoSpeedTbl[object->work[0]] * 5.0f;
            }
            if (card->unk_18[0] > 360.0f) {
                card->unk_18[0] = m242_AngleAdd(card->unk_18[0], 0.0f);
            }
            if (card->unk_18[0] < 0.0f) {
                card->unk_18[0] = m242_AngleAdd(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        default:
            switch (card->unk_04[0]) {
                case 0:
                    if (card->unk_18[0] > -40.0f) {
                        card->unk_18[0] -= speed * m242_decoSpeedTbl[object->work[0]];
                    } else {
                        card->unk_18[0] = -40.0f;
                    }
                    moving = FALSE;
                    for (i = 0; i < 3; i++) {
                        spinner = &STACKED_DECK_SPINNERS[i];
                        if (spinner->unk_18[0] != -40.0f) {
                            moving = TRUE;
                        }
                    }
                    if (!moving) {
                        for (i = 0; i < 3; i++) {
                            spinner = &STACKED_DECK_SPINNERS[i];
                            spinner->unk_04[0] = 1;
                        }
                    }
                    break;
                case 1:
                    if (card->unk_18[0] < 40.0f) {
                        card->unk_18[0] += speed * m242_decoSpeedTbl[object->work[0]];
                    } else {
                        card->unk_18[0] = 40.0f;
                    }
                    moving = FALSE;
                    for (i = 0; i < 3; i++) {
                        spinner = &STACKED_DECK_SPINNERS[i];
                        if (spinner->unk_18[0] != 40.0f) {
                            moving = TRUE;
                        }
                    }
                    if (!moving) {
                        for (i = 0; i < 3; i++) {
                            spinner = &STACKED_DECK_SPINNERS[i];
                            spinner->unk_04[0] = 0;
                        }
                    }
                    break;
            }
            break;
    }

    object->rot.z = m242_AngleAdd(card->unk_18[0], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
}

void m242_DecoObjInit(omObjData *object) {
    StackedDeckObjWork *card = &m242_objWorkTbl[object->work[0] + 23];

    if (object->work[0] == 0) {
        object->model[0] = Hu3DModelRead(0x4B000A, 0x2B9);
        m242_decoMdl = object->model[0];
    } else {
        object->model[0] = Hu3DModelLink((s16)m242_decoMdl);
    }
    object->trans.x = m242_decoPosTbl[object->work[0]].x * 5.0f;
    object->trans.y = m242_decoPosTbl[object->work[0]].y * 5.0f;
    object->trans.z = -875.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->rot.x = 0.0f;
    object->rot.y = 180.0f;
    object->rot.z = 0.0f;
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    object->scale.x = 1.0f;
    object->scale.y = 1.0f;
    object->scale.z = 1.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    card->unk_18[0] = 0.0f;
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    object->func = m242_DecoObjMain;
}

void m242_DecoObjCreateAll(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        StackedDeckObjWork *card = &m242_objWorkTbl[i + 23];
        omObjData *obj = omAddObj(0x258, 1, 1, -1, m242_DecoObjInit);

        obj->work[0] = i;
        card->obj = obj;
    }
}

void m242_CameraViewInit(void) {
    u32 i;

    if (m242_cameraSetF == 0) {
        m242_cameraSetF = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2522.7217f;
            CRotM[i].x = 332.3684f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -200.0f;
            CenterM[i].z = 75.0f;
        }
    }
}

void m242_ExitObjMain(omObjData *object) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(m242_cardAnimDataTbl[i]);
    }
    for (i = 0; i < 12; i++) {
        Hu3DAnimKill(m242_cardAnimTbl[i]);
    }
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m242_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m242_ExitObjMain;
    }
}

void m242_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m242_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m242_MainObjMain(omObjData *object) {
    StackedDeckObjWork *players[4];
    omObjData *playerObjs[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        players[i] = &STACKED_DECK_PLAYERS[i];
        playerObjs[i] = players[i]->obj;
    }

    switch (m242_phase) {
        case 0:
            m242_PhaseSet(1);
            m242_timer = 0;
            break;
        case 1:
            if (m242_phaseDoneNo == 1) {
                if (!(rand8() & 1)) {
                    m242_PhaseSet(2);
                } else {
                    m242_PhaseSet(3);
                }
            }
            break;
        case 2:
            if (m242_phaseDoneNo == 2) {
                if (m242_roundNo == 0) {
                    m242_PhaseSet(4);
                } else {
                    m242_PhaseSet(13);
                }
                if (++m242_roundNo >= 5) {
                    m242_roundNo = 4;
                }
            }
            break;
        case 3:
            if (m242_phaseDoneNo == 3) {
                if (m242_roundNo == 0) {
                    m242_PhaseSet(4);
                } else {
                    m242_PhaseSet(13);
                }
                if (++m242_roundNo >= 5) {
                    m242_roundNo = 4;
                }
            }
            break;
        case 4:
            if (m242_phaseDoneNo == 4) {
                m242_PhaseSet(5);
                m242_timer = 0;
            }
            break;
        case 5:
            if (m242_timer == 0) {
                GMesCreate(GMES_MES_7);
                m242_timer++;
            } else if (m242_timer >= 43) {
                HuAudSeqPlay(0x35);
            } else {
                m242_timer++;
            }
            if (GMesStatGet() == 0) {
                m242_PhaseSet(6);
                GMesCreate(GMES_MES_TIMER, 10, 0xA0, 0x1C);
                m242_timer = 301;
            }
            break;
        case 13:
            if (m242_phaseDoneNo == 13) {
                m242_PhaseSet(6);
                GMesCreate(GMES_MES_TIMER, 10, 0xA0, 0x1C);
                m242_timer = 301;
            }
            break;
        case 6:
            if (m242_timer > 0) {
                m242_timer--;
                GMesTimerValueSet((m242_timer + 29) / 30);
            } else if (m242_phaseDoneNo != 6 && m242_jumpF == 0) {
                m242_pickCardType = 4;
                GMesTimerEnd();
                m242_timer = 0;
                m242_PhaseSet(7);
            }
            if (m242_phaseDoneNo == 6) {
                GMesTimerEnd();
                m242_timer = 0;
                m242_PhaseSet(7);
            }
            break;
        case 7:
            if (m242_phaseDoneNo == 7) {
                m242_timer = 0;
                switch (m242_pickCardType) {
                    case 1:
                        m242_PhaseSet(8);
                        break;
                    case 2:
                        m242_PhaseSet(9);
                        break;
                    case 3:
                        if (m242_queueLast == 1) {
                            m242_PhaseSet(14);
                        } else {
                            m242_PhaseSet(11);
                        }
                        break;
                }
            }
            break;
        case 8:
            if (m242_phaseDoneNo == 8) {
                m242_kinokoCardNum--;
                m242_PhaseSet(13);
            }
            break;
        case 9:
            if (m242_phaseDoneNo == 9) {
                m242_teresaCardNum--;
                m242_PhaseSet(10);
            }
            break;
        case 10:
            if (m242_phaseDoneNo == 10) {
                m242_PhaseSet(13);
            }
            break;
        case 11:
            if (m242_phaseDoneNo == 11) {
                m242_koopaCardNum--;
                m242_PhaseSet(13);
            }
            break;
        case 12:
            break;
        case 14:
            if (m242_finalHitF == 1) {
                GMesCreate(GMES_MES_18);
                HuAudSeqFadeOut(120);
                m242_PhaseSet(15);
                m242_timer = -15;
            }
            break;
        case 15:
            if (GMesStatGet() == 0) {
                if (m242_timer >= 0) {
                    m242_PhaseSet(16);
                    m242_timer = 98;
                } else {
                    m242_timer++;
                }
            }
            break;
        case 16:
            if (m242_timer == 98) {
                HuAudSeqPlay(0x65);
            }
            if (m242_timer > 0) {
                m242_timer--;
            } else {
                m242_PhaseSet(17);
                m242_timer = 0;
                for (i = 0; i < 4; i++) {
                    GwPlayer[playerObjs[i]->work[0]].bonusCoin = players[i]->unk_04[7];
                }
            }
            break;
        case 17:
            if (m242_timer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                object->func = m242_ExitWaitObjMain;
                m242_timer++;
            }
            break;
    }
}

void m242_MainObjInit(omObjData *object) {
    s16 i;
    s16 j;

    MgFlowStatSet(MG_STATE_PLAY);
    m242_timer = 0;
    m242_phase = 0;
    m242_phaseDoneNo = 0;
    m242_roundNo = 0;
    m242_kinokoCardNum = 0;
    m242_teresaCardNum = 0;
    m242_koopaCardNum = 0;
    m242_smokeState = 0;
    m242_hitEffState = 0;
    m242_pickCardType = 0;
    m242_queueLast = 3;
    for (i = 0; i < 4; i++) {
        m242_queueSlotFTbl[i] = 0;
    }
    m242_jumpF = 0;
    for (i = 0; i < 12; i++) {
        m242_slotUsedTbl[i] = 0;
    }
    m242_dealCnt = 0;
    m242_shuffleCnt = 0;
    m242_shuffleCardNo = 0;
    for (i = 0; i < 4; i++) {
        m242_rankCntTbl[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m242_rankPlayerTbl[i][j] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        m242_coinRankTbl[i] = 0;
        m242_starRankTbl[i] = 0;
    }
    m242_comFlipF = 0;
    m242_cardSeStep = 0;
    m242_flySeF = 0;
    m242_flipSeCnt = 0;
    m242_finalHitF = 0;
    m242_MapObjCreate();
    m242_BackObjCreate();
    m242_PlayerObjCreateAll();
    m242_CardObjCreateAll();
    m242_CardChrObjCreateAll();
    m242_SmokeObjCreate();
    m242_HitEffObjCreate();
    m242_DecoObjCreateAll();
    m242_CameraViewInit();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = m242_MainObjMain;
}

void m242_Dummy(void) {
}

void m242_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m242_cameraViewTbl[i].scissorX, m242_cameraViewTbl[i].scissorY,
                   m242_cameraViewTbl[i].scissorWidth, m242_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m242_cameraViewTbl[i].viewportScale.x, m242_cameraViewTbl[i].viewportScale.y,
                    m242_cameraViewTbl[i].viewportScale.z, m242_cameraViewTbl[i].viewportTranslate.x,
                    m242_cameraViewTbl[i].viewportTranslate.y, m242_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m242_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m242_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    m242_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m242_fontMesTbl, 0);
    GMesFontMesCreate(m242_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m242_MainObjInit);
    omAddObj(1000, 0, 0, -1, m242_ExitCheckObjMain);
    m242_ObjWorkInit();
    MgFlowInit(&m242_mgFlow);
}

const s16 m242_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
