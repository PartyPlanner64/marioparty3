#include "common_duel.h"
#include "ovl_81.h"

typedef struct SomeStruct {
    u8 unk_00[10];
} SomeStruct;

typedef struct SomeStruct2 {
    u16 unk_00[8];
} SomeStruct2;

typedef struct SomeStruct3 {
    u8 unk_00[11];
} SomeStruct3;

typedef struct UnkOvl81_3 {
    /* 0x00 */ s32 playerIndex;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec *unk_08;
    /* 0x0C */ Vec *unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char unk_14[0xC];
} UnkOvl81_3; // sizeof 0x20

extern s16 mbdTelopMgTypeStrNo;
extern u8 mbdTelopFlag;
extern s16 mbdTelopPlayerGrp;
extern s16 mbdTelopPlayerAnim[];
extern GAMEMES mbdTelopMes;
extern omObjData *mbdTelopPlayerObj;
extern omObjData *mbdTelopLast5Obj;
extern u8 mbdTelopLast5StopF;
extern s16 mbdTelopLast5Grp[2];
extern s16 mbdTelopLast5Anim[2];
extern Vec mbdGuideCameraEye;
extern Vec mbdGuideCameraAt;
extern Vec mbdGuideCameraUp;
extern Vec mbdGuideCameraViewSize;
extern Vec mbdGuideCameraViewPos;
extern s32 mbdTelopLast5Turn;
extern s32 mbdTelopMgTypeY;
extern UnkBoard4 *mbdTelopTitleSpr;
extern UnkBoard4 *mbdTelopTitleShadowSpr;

char *mbdTelopTitleStrTbl[] = { "  1 VS 1 GAME ", "  HAPPENING!  " };
s8 mbdTelopTitleLenTbl[] = { 14, 14 };
s8 mbdTelopTitleOfsTbl[] = { -8, -8, -8, -8, -8, -8 };
s16 mbdTelopTitleXTbl[] = { 60, 93, 126, 159, 192, 225, 258 };

const SomeStruct mbdTelopLast5FrameTbl = { { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 } };
const SomeStruct2 mbdTelopPlayerSprTbl = { { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 } };
const SomeStruct3 mbdTelopTitleMemberTbl = { { 0, 1, 2, 2, 3, 4, 5, 2, 1, 6, 2 } };

void MBDTelopLast5Create(void);
void MBDMgCallListStart(s32 arg0);
void MBDTelopPlayerCreate(s32 arg0);
void MBDTelopPlayerMain(omObjData *arg0);
void MBDTelopMain(void);
void MBDTelopBannerProc(void);
void MBDTelopAttackProc(void);

void MBDTelopInit(void) {
    mbdTelopMgTypeStrNo = -1;
    mbdTelopFlag = 0;
    mbdTelopPlayerGrp = -1;
    mbdTelopPlayerAnim[0] = mbdTelopPlayerAnim[1] = -1;
    mbdTelopPlayerObj = NULL;
    mbdTelopLast5Obj = NULL;
}

void MBDTelopClose(void) {
    if (mbdTelopFlag & 0x20) {
        GMesSprClose(&mbdTelopMes);
    }
    if (mbdTelopFlag & 0x10) {
        HuSprGrpKill(mbdTelopPlayerGrp);
        HuSprAnimKill(mbdTelopPlayerAnim[0]);
        HuSprAnimKill(mbdTelopPlayerAnim[1]);
    }
    if (mbdTelopPlayerObj != NULL) {
        omDelObj(mbdTelopPlayerObj);
        mbdTelopPlayerObj = NULL;
    }
    if (mbdTelopLast5Obj != NULL) {
        omDelObj(mbdTelopLast5Obj);
        mbdTelopLast5Obj = NULL;
    }
    mbdTelopFlag &= 0xCF;
}

void MBDTelopLast5Main(omObjData *arg0) {
    s32 i;

    switch (arg0->work[0]) {
        case 0:
            arg0->rot.x += 30.0f;
            arg0->scale.x = sindf(arg0->rot.x) * 0.5f + 1.0f;
            HuSprScaleSet(mbdTelopLast5Grp[0], 0, arg0->scale.x, arg0->scale.x);
            if (arg0->rot.x >= 360.0f) {
                arg0->rot.x -= 360.0f;
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (mbdTelopLast5Anim[i] != -1) {
                    HuSprAnimKill(mbdTelopLast5Anim[i]);
                }
                if (mbdTelopLast5Grp[i] != -1) {
                    HuSprGrpKill(mbdTelopLast5Grp[i]);
                }
            }
            mbdTelopLast5Obj = NULL;
            omDelObj(arg0);
            break;
    }
}

void MBDTelopPlayerMain(omObjData *arg0) {
    s32 i;

    if (arg0->rot.y > 0.0f) {
        arg0->rot.y = arg0->rot.y - 1.0f;
    }

    switch (arg0->work[0]) {
        case 0:
            arg0->scale.x += 0.2f;
            HuSprScaleSet(mbdTelopPlayerGrp, 0, arg0->scale.x, arg0->scale.x);
            if (arg0->scale.x >= 1.0f) {
                arg0->work[0] = 1;
                arg0->work[1] = 12;
            }
            break;
        case 1:
            if (arg0->work[3] == 6) {
                arg0->work[1]--;
                for (i = 0; i < 4; i++) {
                    if (!(GwPlayer[i].stat & 1)) {
                        break;
                    }
                }
                if (i != 4) {
                    for (i = 0; i < 4; i++) {
                        if (!(GwPlayer[i].stat & 1) && (HuPadBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                            arg0->work[0] = 2;
                        }
                    }
                } else if (arg0->work[1] == 0) {
                    arg0->work[0] = 2;
                }
                if (arg0->work[2] == 0) {
                    HuSprPosSet(mbdTelopPlayerGrp, 0, 160, 120 + (s32)(sindf(arg0->rot.x) * 5.0f + 0.5f));
                    arg0->rot.x += 10.0f;
                    if (arg0->rot.x >= 360.0f) {
                        arg0->rot.x -= 360.0f;
                    }
                } else {
                    arg0->work[2]--;
                }
                break;
            }

            if (arg0->work[1] != 0) {
                arg0->work[1]--;
                break;
            }

            if (!(GwPlayer[arg0->work[3]].stat & 1)) {
                if (!(arg0->rot.y <= 0.0f)) {
                    if (!(HuPadBtnDown[GwPlayer[arg0->work[3]].pad] & (A_BUTTON | B_BUTTON))) {
                        break;
                    }
                }
            }
            arg0->work[0] = 2;
            break;
        case 2:
            arg0->scale.x += 0.2f;
            HuSprScaleSet(mbdTelopPlayerGrp, 0, arg0->scale.x, arg0->scale.x);
            HuSprTPLvlSet(mbdTelopPlayerGrp, 0, (2.0f - arg0->scale.x) * 256.0f);
            if (arg0->scale.x >= 2.0f) {
                arg0->work[0] = 3;
            }
            break;
        case 3:
            HuSprGrpKill(mbdTelopPlayerGrp);
            HuSprAnimKill(mbdTelopPlayerAnim[0]);
            mbdTelopPlayerGrp = -1;
            mbdTelopPlayerAnim[0] = -1;
            if (mbdTelopLast5Obj != NULL) {
                for (i = 0; i < 2; i++) {
                    if (mbdTelopLast5Anim[i] != -1) {
                        HuSprAnimKill(mbdTelopLast5Anim[i]);
                    }
                    if (mbdTelopLast5Grp[i] != -1) {
                        HuSprGrpKill(mbdTelopLast5Grp[i]);
                    }
                }
                omDelObj(mbdTelopLast5Obj);
                mbdTelopLast5Obj = NULL;
            }
            mbdTelopPlayerObj = NULL;
            omDelObj(arg0);
            break;
    }
}

void MBDTelopLast5Stop(void) {
    mbdTelopLast5StopF = 1;
}

void MBDTelopMgTypeMain(omObjData *obj) {
    s32 i;

    if (obj->work[2] != 0) {
        obj->work[2]--;
        return;
    }

    obj->scale.x += 0.05f;
    if (obj->scale.x >= 1.0f) {
        obj->scale.x = 1.0f;
        obj->rot.z += 20.0f;
        if (obj->rot.z >= 360.0f) {
            obj->rot.z -= 360.0f;
        }
    }

    HuSprPosSet(mbdTelopMes.strGId[mbdTelopMgTypeStrNo], 0, obj->rot.x + 80.0f,
                mbdTelopMgTypeY + 2.0f * sindf(obj->rot.z));

    for (i = 1; mbdTelopTitleLenTbl[obj->work[0]] >= i; i++) {
        HuSprTPLvlSet(mbdTelopMes.strGId[mbdTelopMgTypeStrNo], i, obj->scale.x * 256.0f);
    }
}

void MBDTelopLast5Create(void) {
    omObjData *obj;
    void *data;
    SomeStruct sp18 = mbdTelopLast5FrameTbl;

    obj = omAddObj(-0x8000, 0, 0, -1, MBDTelopLast5Main);
    mbdTelopLast5Obj = obj;
    obj->rot.x = 0.0f;

    if (mbdTelopLast5Turn == 0) {
        mbdTelopLast5Grp[0] = HuSprGrpCreate(1, 0);
        data = DataRead(0x1301E0);
        mbdTelopLast5Anim[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbdTelopLast5Grp[0], 0, mbdTelopLast5Anim[0], 0);
        HuSprPriSet(mbdTelopLast5Grp[0], 0, 0x10);
        HuSprAttrSet(mbdTelopLast5Grp[0], 0, HUSPR_ATTR_XLU);
        HuSprPosSet(mbdTelopLast5Grp[0], 0, 0xA0, 0x32);
        mbdTelopLast5Anim[1] = -1;
        mbdTelopLast5Grp[1] = -1;
        obj->work[0] = 1;
        return;
    }

    mbdTelopLast5Grp[0] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DF);
    mbdTelopLast5Anim[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbdTelopLast5Grp[0], 0, mbdTelopLast5Anim[0], sp18.unk_00[mbdTelopLast5Turn]);
    HuSprPriSet(mbdTelopLast5Grp[0], 0, 0x10);
    HuSprAttrSet(mbdTelopLast5Grp[0], 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbdTelopLast5Grp[0], 0, 0xA0, 0x32);

    mbdTelopLast5Grp[1] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DE);
    mbdTelopLast5Anim[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbdTelopLast5Grp[1], 0, mbdTelopLast5Anim[1], 0);
    HuSprPriSet(mbdTelopLast5Grp[1], 0, 0x11);
    HuSprAttrSet(mbdTelopLast5Grp[1], 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbdTelopLast5Grp[1], 0, 0xA0, 0x32);
    obj->work[0] = 0;
}

void MBDTelopPlayerCreate(s32 arg0) {
    omObjData *obj;
    void *data;
    SomeStruct2 sp18 = mbdTelopPlayerSprTbl;

    mbdTelopPlayerGrp = HuSprGrpCreate(1, 0);
    data = DataRead(sp18.unk_00[GwPlayer[arg0].chr] | 0x130000);
    mbdTelopPlayerAnim[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbdTelopPlayerGrp, 0, mbdTelopPlayerAnim[0], 0);
    HuSprPriSet(mbdTelopPlayerGrp, 0, 0x10);
    HuSprAttrSet(mbdTelopPlayerGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbdTelopPlayerGrp, 0, 0xA0, 0x78);
    obj = omAddObj(-0x8000, 0, 0, -1, MBDTelopPlayerMain);
    mbdTelopPlayerObj = obj;

    obj->scale.x = 0;
    obj->rot.x = 180.0f;
    obj->rot.y = 150.0f;
    obj->work[2] = 30;
    obj->work[0] = 0;
    obj->work[1] = 12;

    if (mbdTelopLast5Obj != NULL) {
        obj->work[1] = 24;
    }
    obj->work[3] = arg0;
    if (arg0 >= 2) {
        obj->work[3] = 4;
    }
}

s32 MBDTelopPlayerCheck(void) {
    return mbdTelopFlag & 4;
}

void MBDTelopPlayerKill(void) {
    HuSprGrpKill(mbdTelopPlayerGrp);
    HuSprAnimKill(mbdTelopPlayerAnim[0]);
    HuSprAnimKill(mbdTelopPlayerAnim[1]);
    omDelObj(mbdTelopPlayerObj);
    mbdTelopPlayerObj = NULL;
    mbdTelopFlag &= 0xC3;
}

void MBDTelopMgTypeCreate(s32 arg0, Vec *pos) {
    Vec2f pos2D;
    omObjData *obj;
    s32 i;
    s32 type;

    if (!(mbdTelopFlag & 4)) {
        type = arg0;
        mbdTelopMgTypeStrNo = GameMesStrInit(&mbdTelopMes, mbdTelopTitleStrTbl[type], 0, 0, 0);
        MBDCamera3Dto2D(pos, &pos2D);
        mbdTelopMgTypeY = pos2D.y - 24.0f;
        if (MBDCameraZoomGet() == 2.0f) {
            mbdTelopMgTypeY -= 10;
        }
        HuSprPosSet(mbdTelopMes.strGId[mbdTelopMgTypeStrNo], 0, mbdTelopTitleOfsTbl[type] + 80,
                    mbdTelopMgTypeY);

        for (i = 1; mbdTelopTitleLenTbl[type] >= i; i++) {
            HuSprTPLvlSet(mbdTelopMes.strGId[mbdTelopMgTypeStrNo], i, 0);
        }

        obj = omAddObj(-0x8000, 0, 0, -1, MBDTelopMgTypeMain);
        mbdTelopPlayerObj = obj;
        obj->scale.x = 0.0f;
        obj->trans.x = 400.0f;
        obj->trans.z = 0.0f;
        obj->rot.x = mbdTelopTitleOfsTbl[type];
        obj->rot.y = 0.0f;
        obj->rot.z = 0.0f;
        obj->work[0] = type;
        obj->work[1] = mbdTelopMgTypeStrNo;
        obj->work[2] = 30;
        obj->work[3] = 7;
        mbdTelopFlag = 38;
        MBDMgCallListStart(arg0);
    }
}

s32 MBDTelopMgTypeStatGet(void) {
    return mbdTelopFlag & 0xC;
}

void MBDTelopMgTypeKill(void) {
    omDelObj(mbdTelopPlayerObj);
    mbdTelopPlayerObj = NULL;
    GMesSprClose(&mbdTelopMes);
    mbdTelopFlag &= 0xC3;
}

void MBDTelopMain(void) {
    UnkOvl81_1 *work = HuPrcCurrentGet()->user_data;

    while (1) {
        switch (work->unk_00) {
            case 0:
                HuAudFXPlay(0x10C);
                if (work->unk_04 == 0) {
                    mbdTelopLast5Turn = GwSystem.total_turns - GwSystem.current_turn;
                    switch (mbdTelopLast5Turn) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 9:
                            MBDTelopLast5Create();
                            break;
                    }
                }
                MBDTelopPlayerCreate(work->unk_04);
                work->unk_00++;
                break;
            case 1:
                if (mbdTelopPlayerGrp == -1) {
                    omDelPrcObj(NULL);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBDTelopCreate(s32 playerIndex) {
    Process *process = omAddPrcObj(MBDTelopMain, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = 0;
    work->unk_04 = playerIndex;
    return process;
}

void MBDTelopTitleCharProc(void) {
    s32 idx = ((UnkOvl81_1 *)HuPrcCurrentGet()->user_data)->unk_00;
    s32 i;

    HuSprDispOn(mbdTelopTitleSpr->unk_0A, idx);
    HuSprDispOn(mbdTelopTitleShadowSpr->unk_0A, idx);
    for (i = 0; i < 93; i += 23) {
        HuSprScaleSet(mbdTelopTitleSpr->unk_0A, idx, (120 - i) / 20.0f + 1.0f, (120 - i) / 20.0f + 1.0f);
        HuSprScaleSet(mbdTelopTitleShadowSpr->unk_0A, idx, (120 - i) / 20.0f + 1.0f, (120 - i) / 20.0f + 1.0f);
        HuSprPosSet(mbdTelopTitleSpr->unk_0A, idx, mbdTelopTitleXTbl[idx], i);
        HuSprPosSet(mbdTelopTitleShadowSpr->unk_0A, idx, mbdTelopTitleXTbl[idx], i);
        HuSprTPLvlSet(mbdTelopTitleSpr->unk_0A, idx, i * 2);
        HuSprTPLvlSet(mbdTelopTitleShadowSpr->unk_0A, idx, i * 2);
        HuPrcVSleep();
    }
    HuSprScaleSet(mbdTelopTitleSpr->unk_0A, idx, 1.0f, 1.0f);
    HuSprScaleSet(mbdTelopTitleShadowSpr->unk_0A, idx, 1.0f, 1.0f);
    HuSprPosSet(mbdTelopTitleSpr->unk_0A, idx, mbdTelopTitleXTbl[idx], 92);
    HuSprPosSet(mbdTelopTitleShadowSpr->unk_0A, idx, mbdTelopTitleXTbl[idx], 92);
    HuSprTPLvlSet(mbdTelopTitleSpr->unk_0A, idx, 256);
    HuSprTPLvlSet(mbdTelopTitleShadowSpr->unk_0A, idx, 256);
    omDelPrcObj(NULL);
}

void MBDTelopTitleProc(void) {
    SomeStruct3 members = mbdTelopTitleMemberTbl;
    UnkBoard4 *sprite;
    Process *process;
    UnkOvl81_1 *work;
    void *data;
    f32 scale;
    f32 rot;
    s32 i;

    data = DataRead(0x130121);
    mbdTelopTitleSpr = MBDSprGrpCreate(7, 0);
    mbdTelopTitleSpr->unk_0C[0] = HuSprAnimRead(data);
    for (i = 0; i < 7; i++) {
        HuSprGrpMemberSet(mbdTelopTitleSpr->unk_0A, i, mbdTelopTitleSpr->unk_0C[0], members.unk_00[i]);
        HuSprPriSet(mbdTelopTitleSpr->unk_0A, i, 1);
        HuSprAttrSet(mbdTelopTitleSpr->unk_0A, i, HUSPR_ATTR_XLU);
        HuSprPosSet(mbdTelopTitleSpr->unk_0A, i, mbdTelopTitleXTbl[i], 92);
        HuSprDispOff(mbdTelopTitleSpr->unk_0A, i);
    }
    DataClose(data);

    data = DataRead(0x130122);
    mbdTelopTitleShadowSpr = MBDSprGrpCreate(7, 0);
    mbdTelopTitleShadowSpr->unk_0C[0] = HuSprAnimRead(data);
    for (i = 0; i < 7; i++) {
        HuSprGrpMemberSet(mbdTelopTitleShadowSpr->unk_0A, i, mbdTelopTitleShadowSpr->unk_0C[0], members.unk_00[i]);
        HuSprPriSet(mbdTelopTitleShadowSpr->unk_0A, i, 2);
        HuSprAttrSet(mbdTelopTitleShadowSpr->unk_0A, i, HUSPR_ATTR_XLU);
        HuSprPosSet(mbdTelopTitleShadowSpr->unk_0A, i, mbdTelopTitleXTbl[i], 92);
        HuSprColorSet(mbdTelopTitleShadowSpr->unk_0A, i, 0, 21, 233);
        HuSprDispOff(mbdTelopTitleShadowSpr->unk_0A, i);
    }
    DataClose(data);

    for (i = 0; i < 7; i++) {
        HuPrcSleep(3);
        process = omAddPrcObj(MBDTelopTitleCharProc, 10, 0, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
        process->user_data = work;
        work->unk_00 = i;
    }

    HuAudFXPlay(0x1CF);
    data = DataRead(0x130133);
    sprite = MBDSprGrpCreate(1, 0);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 1);
    HuSprAttrSet(sprite->unk_0A, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(sprite->unk_0A, 0, 160, 92);
    HuSprScaleSet(sprite->unk_0A, 0, 0.0f, 0.0f);
    HuSprColorSet(sprite->unk_0A, 0, 255, 255, 0);
    HuSprTPLvlSet(sprite->unk_0A, 0, 200);
    DataClose(data);

    rot = 0.0f;
    for (scale = 1.0f; scale <= 4.0f; scale += 1.0f) {
        HuSprScaleSet(sprite->unk_0A, 0, scale, scale);
        HuSprZRotSet(sprite->unk_0A, 0, rot);
        rot += 75.0f;
        HuPrcVSleep();
    }
    for (; scale >= 0.0f; scale -= 1.0f) {
        HuSprScaleSet(sprite->unk_0A, 0, scale, scale);
        HuSprZRotSet(sprite->unk_0A, 0, rot);
        rot += 75.0f;
        HuPrcVSleep();
    }

    HuSprDispOff(sprite->unk_0A, 0);
    HuPrcSleep(15);
    MBDSprGrpKill(mbdTelopTitleSpr);
    MBDSprGrpKill(mbdTelopTitleShadowSpr);
    MBDSprGrpKill(sprite);
    omDelPrcObj(NULL);
}

Process *MBDTelopTitleCreate(void) {
    return omAddPrcObj(MBDTelopTitleProc, 0, 0, 0);
}

void MBDTelopAttackProc(void) {
    UnkOvl81_3 *work = HuPrcCurrentGet()->user_data;
    s32 playerIndex = work->playerIndex;
    s32 unk_04 = work->unk_04;
    Vec *from = work->unk_08;
    Vec *to = work->unk_0C;
    s32 mode = work->unk_10;
    Vec dir;
    s32 files[2] = { 0x130124, 0x130125 };
    s32 offsX[4][3] = { { 0, 0, -24 }, { 0, 0, 0 }, { 0, 0, 24 }, { 0, 0, 0 } };
    s32 offsY[4][3] = { { 0, 0, 45 }, { 0, 0, 37 }, { 0, 0, 45 }, { 0, 0, 37 } };
    Vec2f startPos[4] = { { 80.0f, -220.0f }, { -200.0f, 60.0f }, { 240.0f, 440.0f }, { 520.0f, 60.0f } };
    Vec2f startPos2[4] = { { 130.0f, -220.0f }, { -200.0f, 110.0f }, { 190.0f, 440.0f }, { 520.0f, 110.0f } };
    Vec2f speed[4] = { { 0.0f, 32.0f }, { 32.0f, 0.0f }, { 0.0f, -32.0f }, { -32.0f, 0.0f } };
    UnkBoard4 *sprite;
    void *data;
    f32 angle;
    s32 dirIdx;
    s32 delay;
    s32 i;

    MBDVecDirGet(from, to, &dir);
    angle = MBDVecAngleGet(&dir) + 45.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    dirIdx = angle / 90.0f;
    if (dirIdx >= 4) {
        dirIdx = 3;
    }

    sprite = MBDSprGrpCreate(3, 2);
    for (i = 0; i < 3; i++) {
        if ((mode == 1 || mode == 2) && i == 2) {
            continue;
        }
        if (mode == 3 && i != 2) {
            continue;
        }
        switch (i) {
            case 0:
                data = DataRead(files[playerIndex]);
                break;
            case 1:
                data = DataRead(0x130126 + unk_04);
                break;
            default:
                data = DataRead(0x130123);
                break;
        }
        sprite->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], 0);
        HuSprPriSet(sprite->unk_0A, i, 1);
        HuSprAttrSet(sprite->unk_0A, i, HUSPR_ATTR_NONE);
        if (mode == 3) {
            HuSprPosSet(sprite->unk_0A, i, offsX[dirIdx][i], offsY[dirIdx][i]);
        } else {
            HuSprPosSet(sprite->unk_0A, i, 0, offsY[dirIdx][i]);
        }
        DataClose(data);
    }

    HuSprZRotSet(sprite->unk_0A, 0, (dirIdx - 1) * 90);
    if (dirIdx == 2 || dirIdx == 3) {
        HuSprAttrSet(sprite->unk_0A, 1, HUSPR_ATTR_FLIPX);
    }
    if (dirIdx == 3) {
        HuSprAttrSet(sprite->unk_0A, 0, HUSPR_ATTR_FLIPY);
    }

    if (!(mode & 1)) {
        HuSprPosSet(sprite->unk_0A, 0, startPos[dirIdx].x, startPos[dirIdx].y);
        for (i = 0; i < 10; i++) {
            HuSprPosSet(sprite->unk_0A, 0, startPos[dirIdx].x + i * speed[dirIdx].x,
                        startPos[dirIdx].y + i * speed[dirIdx].y);
            HuPrcVSleep();
        }
    } else {
        HuSprPosSet(sprite->unk_0A, 0, startPos2[dirIdx].x, startPos2[dirIdx].y);
        HuPrcSleep(mode + 2);
        for (i = 0; i < 10; i++) {
            HuSprPosSet(sprite->unk_0A, 0, startPos2[dirIdx].x + i * speed[dirIdx].x,
                        startPos2[dirIdx].y + i * speed[dirIdx].y);
            HuPrcVSleep();
        }
    }

    if (!(mode & 1)) {
        delay = 15;
    } else {
        delay = 12;
        delay -= mode;
    }
    HuPrcSleep(delay);
    MBDSprGrpKill(sprite);
    omDelPrcObj(NULL);
}

Process *MBDTelopAttackCreate(s32 playerIndex, s32 arg1, Vec *arg2, Vec *arg3, s32 arg4) {
    Process *process;
    UnkOvl81_3 *work;
    s32 flag;

    process = omAddPrcObj(MBDTelopAttackProc, 0, 0x1000, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
    process->user_data = work;
    work->playerIndex = playerIndex;
    work->unk_04 = arg1;
    work->unk_08 = arg2;
    work->unk_0C = arg3;
    work->unk_10 = 0;

    if (arg4 != 0) {
        if (playerIndex == 0) {
            flag = GWBoardFlagCheck(0x12);
        } else {
            flag = GWBoardFlagCheck(0x13);
        }
        if (flag == 0) {
            return process;
        }
        work->unk_10 = 2;

        process = omAddPrcObj(MBDTelopAttackProc, 0, 0x1000, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
        process->user_data = work;
        work->playerIndex = playerIndex;
        work->unk_04 = arg1;
        work->unk_08 = arg2;
        work->unk_0C = arg3;
        work->unk_10 = 1;

        process = omAddPrcObj(MBDTelopAttackProc, 0, 0x1000, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
        process->user_data = work;
        work->playerIndex = playerIndex;
        work->unk_04 = arg1;
        work->unk_08 = arg2;
        work->unk_0C = arg3;
        work->unk_10 = 3;
    }
    return process;
}

void MBDTelopBannerProc(void) {
    s32 idx = ((UnkOvl81_1 *)HuPrcCurrentGet()->user_data)->unk_00;
    s32 files[2] = { 0x130101, 0x130102 };
    s32 posY[2] = { 120, 90 };
    UnkBoard4 *sprite;
    void *data;
    s32 speed;
    s32 offset;
    s32 i;

    sprite = MBDSprGrpCreate(1, 2);
    data = DataRead(files[idx]);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 0x2010);
    HuSprAttrSet(sprite->unk_0A, 0, HUSPR_ATTR_NONE);
    DataClose(data);

    speed = 0;
    offset = 0;
    for (i = 0; i < 7; i++) {
        HuSprPosSet(sprite->unk_0A, 0, 160, posY[idx] + offset);
        if (idx == 0) {
            offset -= speed;
        } else {
            offset += speed;
        }
        speed += 2;
        HuPrcVSleep();
    }

    HuPrcSleep(20);
    MBDSprGrpKill(sprite);
    omDelPrcObj(NULL);
}

Process *MBDTelopBannerCreate(s32 arg0) {
    Process *process = omAddPrcObj(MBDTelopBannerProc, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = arg0;
    return process;
}

void MBDGuideCameraCreate(void) {
    Hu3DCameraPerspectiveSet(1, 40.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(1, &mbdGuideCameraEye, &mbdGuideCameraAt, &mbdGuideCameraUp);
    Hu3DCamUpdateMtx(1);
    Hu3DCameraViewportSet(1, &mbdGuideCameraViewSize, &mbdGuideCameraViewPos);
}

void MBDGuideMain(void) {
    while (1) {
        MBDGuideCameraCreate();
        HuPrcVSleep();
    }
}

UnkOvl81_2 *MBDGuideCreate(s32 arg0, s32 arg1) {
    HmfModel *rotHmf;
    HmfModel *hmf;
    UnkOvl81_2 *guide;
    Object *obj;
    Process *process;
    f32 zero;
    f32 one;

    guide = HuMemMemoryAllocTemp(sizeof(UnkOvl81_2));
    if (guide != NULL) {
        obj = MBDModelCreate(0x3E, NULL);
        guide->obj = obj;
        HuVecCopyXYZ(&obj->scale, 1.43f, 1.43f, 1.43f);
        guide->obj->flags |= 1;

        Hu3DModelCameraSet(guide->obj->omObj1->model[0], HU3D_CAM1);

        rotHmf = &Hu3DData[guide->obj->omObj1->model[0]];
        sincosdf(15.0f, &rotHmf->mtx[1][2], &rotHmf->mtx[1][1]);

        Hu3DData[guide->obj->omObj1->model[0]].mtx[2][1] = -Hu3DData[guide->obj->omObj1->model[0]].mtx[1][2];

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        hmf->mtx[2][2] = hmf->mtx[1][1];

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        zero = 0.0f;
        hmf->mtx[3][2] = zero;
        hmf->mtx[3][1] = zero;
        hmf->mtx[3][0] = zero;
        hmf->mtx[2][3] = zero;
        hmf->mtx[2][0] = zero;
        hmf->mtx[1][3] = zero;
        hmf->mtx[1][0] = zero;
        hmf->mtx[0][3] = zero;
        hmf->mtx[0][2] = zero;
        hmf->mtx[0][1] = zero;

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        one = 1.0f;
        hmf->mtx[3][3] = one;
        hmf->mtx[0][0] = one;

        process = omAddPrcObj(MBDGuideMain, 0x4000, 0, 0);
        guide->process = process;
        process->user_data = guide;

        guide->unk_0A = 0x69;

        mbdGuideCameraEye.x = zero;
        mbdGuideCameraEye.y = zero;
        mbdGuideCameraEye.z = 120.0f;

        mbdGuideCameraAt.x = zero;
        mbdGuideCameraAt.y = zero;
        mbdGuideCameraAt.z = zero;

        mbdGuideCameraUp.x = zero;
        mbdGuideCameraUp.y = one;
        mbdGuideCameraUp.z = zero;

        mbdGuideCameraViewSize.x = 1280.0f;
        mbdGuideCameraViewSize.y = 960.0f;
        mbdGuideCameraViewSize.z = 511.0f;

        mbdGuideCameraViewPos.x = 240.0f;
        mbdGuideCameraViewPos.y = guide->unk_0A * 4.0f + 480.0f;
        mbdGuideCameraViewPos.z = 511.5f;

        MBDGuideCameraCreate();

        if (arg1 != 0) {
            guide->win_id = HuWinExCreateStyled(0x5B, guide->unk_0A + 0x5A + arg1, 0x11);
        } else {
            guide->win_id = HuWinExCreateStyled(0x4B, guide->unk_0A + 0x5A + arg1, 0x10);
        }
    }
    return guide;
}

void MBDGuideKill(UnkOvl81_2 *arg0) {
    if (arg0 != NULL) {
        MBDModelKill(arg0->obj);
        omDelPrcObj(arg0->process);
        HuWinExCleanup(arg0->win_id);
        HuMemMemoryFreeTemp(arg0);
    }
}

void MBDGuidePosSet(UnkOvl81_2 *arg0, s16 arg1, s16 arg2) {
    arg0->unk_0A = arg1;
    mbdGuideCameraViewPos.y = arg1 * 4.0f + 480.0f;
    if (arg2 != 0) {
        HuWinPosSet(arg0->win_id, 91, arg0->unk_0A + 80 + arg2);
    } else {
        HuWinPosSet(arg0->win_id, 75, arg0->unk_0A + 90 + arg2);
    }
}
