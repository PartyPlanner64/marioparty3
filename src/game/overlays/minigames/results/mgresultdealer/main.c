#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "mgresultdealer.h"

s8 mgresultdealer_mainState = 0;
u8 mgresultdealer_mainStatePad[8] = { 0 }; /* Unreferenced. */
s32 mgresultdealer_mainTimer = 0;
s8 mgresultdealer_exitWipeF = 0;

extern s16 mgresultdealer_payoutRate;
extern s16 mgresultdealer_bet;
extern s8 mgresultdealer_playerOrderTbl[4];

void mgresultdealer_MainObjMain(omObjData *);
void mgresultdealer_ExitObjMain(omObjData *);
void mgresultdealer_StageCreate(void);
void mgresultdealer_BackCreate(void);
void mgresultdealer_CameraModelSet(s16);
void mgresultdealer_PlayerProc(void);
void mgresultdealer_CoinProc(void);
void mgresultdealer_FadeProc(void);
void mgresultdealer_CalcProc(void);
void mgresultdealer_DropStart(void);
s8 mgresultdealer_DropHitCheck(void);
void mgresultdealer_ConfettiStart(void);
void mgresultdealer_PlayerWinFaceSet(void);
void mgresultdealer_PlayerLoseFaceSet(void);
void mgresultdealer_CoinRainStart(s32);
s8 mgresultdealer_CoinRainDoneCheck(void);
void mgresultdealer_FadeStart(void);
s8 mgresultdealer_FadeDoneCheck(void);
void mgresultdealer_CalcStart(void);
s32 mgresultdealer_CalcOpenCheck(void);
s32 mgresultdealer_CalcCloseCheck(void);
s8 mgresultdealer_CalcDoneCheck(void);

void mgresultdealer_ObjectSetup(void) {
    omObjData *obj;
    s16 count;
    s16 i;
    s16 j;

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            mgresultdealer_playerOrderTbl[count] = j;
            count++;
            if (count >= 4) {
                break;
            }
        }
        if (count >= 4) {
            break;
        }
    }
    Hu3DSprModelInit(100);
    omInitObjMan(0x1E, 0x28);
    CamSetupInitMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    mgresultdealer_bet = GwPlayer[mgresultdealer_playerOrderTbl[0]].gameCoin;
    mgresultdealer_payoutRate = GwPlayer[mgresultdealer_playerOrderTbl[0]].bonusCoin;
    omAddPrcObj(mgresultdealer_PlayerProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultdealer_CoinProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultdealer_FadeProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultdealer_CalcProc, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, mgresultdealer_MainObjMain);
    omAddObj(0, 0, 0, -1, mgresultdealer_ExitObjMain);
    mgresultdealer_BackCreate();
    mgresultdealer_StageCreate();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void mgresultdealer_MainObjMain(omObjData *unused) {
    omObjData *obj = mgresultdealer_playerWork.obj;
    f32 time;
    s32 state = mgresultdealer_mainState;

    switch (state) {
        case 0:
            if (mgresultdealer_bet * mgresultdealer_payoutRate > 0) {
                HuAudSeqPlay(0x46);
            } else {
                HuAudSeqPlay(0x47);
            }
            mgresultdealer_mainTimer = 0;
            state++;
            break;
        case 1:
            if (++mgresultdealer_mainTimer > 20) {
                state++;
            }
            break;
        case 2:
            mgresultdealer_CalcStart();
            state++;
            break;
        case 3:
            if (mgresultdealer_CalcOpenCheck()) {
                state++;
            }
            break;
        case 4:
            if (mgresultdealer_CalcDoneCheck() == 1) {
                mgresultdealer_mainTimer = 0;
                state++;
            }
            break;
        case 5:
            if (mgresultdealer_CalcCloseCheck()) {
                state++;
            }
            break;
        case 6:
            if (++mgresultdealer_mainTimer > 0) {
                if (mgresultdealer_bet * mgresultdealer_payoutRate > 0) {
                    state++;
                } else {
                    state = 11;
                }
            }
            break;
        case 7:
            mgresultdealer_CoinRainStart(mgresultdealer_bet * mgresultdealer_payoutRate);
            state++;
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 30, 2);
            break;
        case 8:
            if (mgresultdealer_CoinRainDoneCheck() == 1) {
                state++;
            }
            break;
        case 9:
            mgresultdealer_PlayerWinFaceSet();
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 30, 0);
            PlayerFXPlay(0x274, mgresultdealer_playerOrderTbl[0]);
            HuAudFXPlay(0x516);
            if (mgresultdealer_bet * mgresultdealer_payoutRate >= 100) {
                Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else if (mgresultdealer_bet * mgresultdealer_payoutRate >= 50) {
                Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            mgresultdealer_ConfettiStart();
            state++;
            break;
        case 10:
            time = Hu3DData[obj->model[0]].motTime;
            if (time >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                mgresultdealer_mainTimer = 0;
                state = 15;
            }
            break;
        case 11:
            mgresultdealer_FadeStart();
            state++;
            break;
        case 12:
            if (mgresultdealer_FadeDoneCheck() == 1) {
                mgresultdealer_DropStart();
                state++;
            }
            break;
        case 13:
            if (mgresultdealer_DropHitCheck() == 1) {
                if (!(GwPlayer[mgresultdealer_playerOrderTbl[0]].stat & 1)) {
                    omVibrate(mgresultdealer_playerOrderTbl[0], 20, 0, 20);
                }
                mgresultdealer_PlayerLoseFaceSet();
                state++;
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 30, 0);
                PlayerFXPlay(0x26B, mgresultdealer_playerOrderTbl[0]);
            }
            break;
        case 14:
            time = Hu3DData[obj->model[0]].motTime;
            if (time >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                mgresultdealer_mainTimer = 0;
                state++;
            }
            break;
        case 15:
            if (++mgresultdealer_mainTimer >= 15) {
                state++;
            }
            break;
        case 16:
            mgresultdealer_bet = 0;
            mgresultdealer_payoutRate = 0;
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            state++;
            break;
        case 17:
            if (WipeStatGet() == 0) {
                GameMesStub();
                omOvlReturnEx(1);
            }
            break;
    }
    mgresultdealer_mainState = state;
}

void mgresultdealer_StageCreate(void) {
    s16 model;

    model = Hu3DModelRead(0x190002, 0x2002B9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelLightInfoSet(model, 2);
    Hu3DCameraMotionSet(model, 0);
    mgresultdealer_CameraModelSet(model);
}

void mgresultdealer_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mgresultdealer_exitWipeF == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            mgresultdealer_exitWipeF = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            GameMesStub();
            omOvlReturnEx(1);
        }
    }
}

void mgresultdealer_BackCreate(void) {
    u16 espriteSlot;

    espriteSlot = espEntry(HuSprAnimDataRead(0x190000), 0, 0);
    espPosSet(espriteSlot, 0xA0, 0x78);
    espAttrSet(espriteSlot, HUSPR_ATTR_BG);
}

void mgresultdealer_CameraModelSet(s16 model) {
    HmfData_UnkBC *camera = Hu3DData[model].hmf->unkBC;
    HuMtx4F matrix;
    f32 x = camera->unk08 - camera->unk14;
    f32 y = camera->unk0C - camera->unk18;
    f32 z = camera->unk10 - camera->unk1C;
    f32 angle;
    f32 rotatedX, rotatedY;
    s8 i;

    CZoom = HuSqrtf(x * x + y * y + z * z);
    angle = atan2df(z, x);
    CRot.y = -(angle - 90.0f);
    angle = -angle;
    matrix[0][0] = matrix[2][2] = cosdf(angle);
    matrix[2][0] = -sindf(angle);
    matrix[0][2] = sindf(angle);
    matrix[1][1] = matrix[3][3] = 1.0f;
    matrix[1][0] = matrix[3][0] = matrix[0][1] = matrix[2][1] = matrix[3][1] = matrix[1][2] =
        matrix[3][2] = matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    rotatedX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0];
    rotatedY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1];
    CRot.x = -atan2df(rotatedY, rotatedX);
    CRot.z = 0.0f;
    if (CZoom > 32000.0f) {
        CZoom = 32000.0f;
    }
    Center.x = camera->unk14;
    Center.y = camera->unk18;
    Center.z = camera->unk1C;
    for (i = 0; i < 4; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCameraPerspectiveSet(i, camera->unk2C, 80.0f, 8000.0f);
    }
}
