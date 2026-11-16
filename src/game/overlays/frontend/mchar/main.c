#include "common.h"
#include "game/printfunc.h"
#include "game/pause.h"

u16 mchar_exitF = 0;
u8 mchar_infoDispF = 1;
s16 mchar_voiceChrTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
char *mchar_motNameTbl[] = {
    "C000_000",
    "C000_001",
    "C000_003",
    "C000_004",
    "C000_005",
    "C000_006",
    "C000_009",
    "C000_010",
    "C000_011",
    "C000_012",
    "C000_013",
    "C000_020",
    "C000_022",
    "C000_023",
    "C000_024",
    "C000_028",
    "C000_029",
    "C000_030",
    "C000_036",
    "C000_039",
    "C000_047",
    "C000_048",
    "C000_049",
    "C000_050",
    "C000_068",
    "C000_072",
    "C000_078",
    "C000_101",
    "C000_113",
    "C000_114",
    "C000_115",
    "C000_116",
    "C000_117",
    "C000_118",
    "C000_121",
    "C000_122",
    "C000_123",
    "C000_172",
    "C000_178",
    "C000_227",
    "C000_228",
    "C000_243",
    "C000_277",
    "C000_288",
    "C000_308",
    "C000_322",
    "C000_323",
    "C000_400",
    "C000_401",
    "C000_402",
    "C000_403",
    "C000_404",
    "C000_405",
    "C000_406",
    "C000_407",
    "C000_408",
    "C000_409",
    "C000_410",
    "C000_411",
    "C000_413",
    "C000_414",
    "C000_415",
    "C000_416",
    "C000_417",
    "C000_418",
    "C000_419",
    "C000_420",
    "C000_421",
    "C000_422",
    "C000_423",
    "C000_424",
    "C000_426",
    "C000_427",
    "C000_428",
    "C000_429",
    "C000_430",
    "C000_431",
    "C000_432",
    "C000_437",
    "C000_438",
    "C000_439",
    "C000_440",
    "C000_441",
    "C000_442",
    "C000_445",
    "C000_446",
    "C000_447",
    "C000_448",
    "C000_449",
    "C000_450",
    "C000_451",
    "C000_453",
    "C000_455",
    "C000_456",
    "C000_458",
    "C000_459",
    "C000_460",
    "C000_461",
    "C000_462",
    "C000_463",
    "C000_464",
    "C000_465",
    "C000_466",
    "C000_467",
    "C000_468",
    "C000_469",
    "C000_470",
    "C000_471",
    "C000_472",
    "C000_473",
    "C000_474",
    "C000_476",
    "C000_477",
    "C000_478",
    "C000_479",
    "C000_480",
    "C000_481",
    "C000_482",
    "C000_483",
    "C000_484",
    "C000_485",
    "C000_486",
    "C000_487",
    "C000_488",
    "C000_489",
    "C000_490",
    "C000_491",
    "C000_492",
    "C000_493",
    "C000_494",
    "C000_495",
    "C000_496",
    "C000_497",
    "C000_498",
    "C000_499",
    "C000_500",
    "C000_501",
    "C000_502",
    "C000_504",
    "C000_505",
    "C000_506",
    "C000_507",
    "C000_508",
    "C000_509",
    "C000_510",
    "C000_511",
    "C000_512",
    "C000_513",
    "C000_514",
    "C000_515",
    "C000_516",
    "C000_517",
    "C000_518",
    "C000_519",
    "C000_520",
    "C000_521",
    "C000_522",
    "C000_523",
    "C000_524",
    "C000_100",
};
s16 mchar_chrNo = 0;
s16 mchar_motNo = 0;
s16 mchar_mdlNo = 0;
s16 mchar_mdlSetNo = 0;
u8 mchar_startCnt = 0;
u8 mchar_reloadCnt = 0;
s32 mchar_mdlFileTbl[] = {
    0x200A2, 0x200A1, 0x300A2, 0x300A1, 0x700A2, 0x700A1, 0x400A2, 0x400A1,
    0x500A2, 0x500A1, 0x600A2, 0x600A1, 0x800A2, 0x800A1, 0x90003, 0x90001
};

static char mchar_printStr[0x100];
static Vec mchar_cameraRot;
static s32 mchar_chrMdlTbl[8][2];
static s32 mchar_chrMotTbl[8][2];


void mchar_ExitCheckObjMain(omObjData *arg0);
void mchar_CameraReset(void);
void mchar_ViewerObjInit(omObjData *arg0);
void mchar_CameraObjMain(omObjData *arg0);
void mchar_ChrMotionChange(s16 arg0);
void mchar_ExitObjMain(omObjData *arg0);
void mchar_ChrModelRead(s16 arg0);
void mchar_ViewerObjMain(omObjData *arg0);

void mchar_ObjectSetup(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(0x19);
    omInitObjMan(0x33, 0);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        pfWinKill(omDBGInfoWin);
        omDBGInfoWin = -1;
    }
    omAddObj(0x2710, 0, 0, -1, mchar_ExitCheckObjMain);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x78, 0x78, 0x78);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, -100.0f, 100.0f, 100.0f);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    mchar_CameraReset();
    omAddObj(0x7D0, 10, 10, -1, mchar_ViewerObjInit);
    omAddObj(0x7D0, 0, 0, -1, mchar_CameraObjMain);
    WipeCreateIn(WIPE_TYPE_NORMAL, 16);
    Hu3DScreenClearF = 1;
    Hu3DBGColorSet(0xC0, 0xE0, 0xFF);
    HuAudCharVoiceInit();
}

void mchar_ViewerObjInit(omObjData *arg0) {
    s16 i;

    arg0->model[0] = -1;
    for (i = 0; i < 8; i++) {
        mchar_chrMdlTbl[i][0] = mchar_chrMdlTbl[i][1] =
            mchar_chrMotTbl[i][0] = mchar_chrMotTbl[i][1] = -1;
    }
    mchar_mdlSetNo = 0;
    mchar_ChrModelRead(0);
    Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], 2, 2);
    arg0->func = mchar_ViewerObjMain;
}

void mchar_ViewerObjMain(omObjData *arg0) {
    HmfModel *model;
    HmfModel *newModel;

    if (mchar_reloadCnt != 0) {
        mchar_reloadCnt--;
        if (mchar_reloadCnt == 0) {
            mchar_ChrModelRead(mchar_mdlSetNo);
            Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], 2, 2);
        }
    }
    if ((u16)ContBtnRep[0] & A_BUTTON) {
        mchar_motNo++;
        if (mchar_motNo >= 160) {
            mchar_motNo = 0;
        }
        mchar_ChrMotionChange(mchar_motNo);
        HuAudCharVoicePlay((mchar_voiceChrTbl[mchar_chrNo] << 16) | mchar_motNo);
    }
    if (ContBtnRep[0] & B_BUTTON) {
        mchar_motNo--;
        if (mchar_motNo < 0) {
            mchar_motNo = 159;
        }
        mchar_ChrMotionChange(mchar_motNo);
        HuAudCharVoicePlay((mchar_voiceChrTbl[mchar_chrNo] << 16) | mchar_motNo);
    }
    if (HuPadBtnDown[0] & START_BUTTON) {
        mchar_startCnt++;
    }
    if (HuPadBtnDown[0] & D_CBUTTONS) {
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        model = &Hu3DData[mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo]];
        mchar_mdlNo++;
        if (mchar_mdlNo >= 2) {
            mchar_mdlNo = 0;
        }
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        newModel = &Hu3DData[mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo]];
        newModel->motId = model->motId;
        newModel->motTime = model->motTime;
        newModel->motAttr = model->motAttr;
        newModel->motShiftTime = model->motShiftTime;
        newModel->motShiftAttr = model->motShiftAttr;
        newModel->motIdShift = model->motIdShift;
    }
    if (HuPadBtnDown[0] & L_CBUTTONS) {
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mchar_chrNo++;
        if (mchar_chrNo >= 8) {
            mchar_chrNo = 0;
        }
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], (s16)mchar_chrMotTbl[mchar_chrNo][0]);
        Hu3DMotionAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], 2, 2);
        HuAudCharVoicePlay((mchar_voiceChrTbl[mchar_chrNo] << 16) | mchar_motNo);
    }
    if (HuPadBtnDown[0] & R_CBUTTONS) {
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mchar_chrNo--;
        if (mchar_chrNo < 0) {
            mchar_chrNo = 7;
        }
        Hu3DModelAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], (s16)mchar_chrMotTbl[mchar_chrNo][0]);
        Hu3DMotionAttrSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo], 2, 2);
        HuAudCharVoicePlay((mchar_voiceChrTbl[mchar_chrNo] << 16) | mchar_motNo);
    }
    if ((u16)ContBtnRep[1] & (A_BUTTON | B_BUTTON)) {
        model = &Hu3DData[mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo]];
        if ((u16)ContBtnRep[1] & B_BUTTON) {
            model->motAttr |= 4;
        }
        model->motAttr &= 0xFE;
        model->motTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motId], model->motAttr, model->motTime, model->unk48, model->motSpeed + model->motSpeed);
        model->motShiftTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motIdShift], model->motShiftAttr, model->motShiftTime, model->unk54, model->motShiftSpeed + model->motShiftSpeed);
        model->motAttr = (model->motAttr & 0xFB) | 1;
    }
    if ((HuPadBtn[0] & (L_TRIG | R_TRIG)) == 0x30) {
        mchar_exitF = 1;
    }
    if (HuPadBtnDown[1] & START_BUTTON) {
        mchar_infoDispF = !mchar_infoDispF;
    }
    if (mchar_infoDispF != 0) {
        model = &Hu3DData[mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo]];
        fontcolor = FONT_COLOR_BLUE;
        sprintf(mchar_printStr, "MOTIONNO.%3d <%s>", mchar_motNo, mchar_motNameTbl[mchar_motNo]);
        print8(24, 182, mchar_printStr);
        sprintf(mchar_printStr, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(24, 190, mchar_printStr);
        sprintf(mchar_printStr, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(24, 198, mchar_printStr);
        sprintf(mchar_printStr, "ZOOM:  %3.3f", CZoom);
        print8(24, 206, mchar_printStr);
        sprintf(mchar_printStr, "M_TIME:%d", (u16)model->motTime);
        print8(24, 214, mchar_printStr);
    }
}

void mchar_ChrModelRead(s16 arg0) {
    s16 i;
    void *data;
    s16 flags;
    s32 *files0;
    s32 *files1;
    s32 offset;

    i = 0;
    offset = arg0;
    files0 = mchar_mdlFileTbl;
    flags = 0x2AC;
    for (; i < 8; i++) {
        mchar_chrMdlTbl[i][0] = Hu3DModelRead(files0[(i + offset) * 2], flags);
        files1 = &mchar_mdlFileTbl[1];
        CharAnimCreate((s16)mchar_chrMdlTbl[i][0], 0, i, CharMotionDataNumGet(i, 0xA3));
        Hu3DModelDynamicFree((s16)mchar_chrMdlTbl[i][0]);
        mchar_chrMdlTbl[i][1] = Hu3DModelRead(files1[(i + offset) * 2], flags);
        CharAnimCreate((s16)mchar_chrMdlTbl[i][1], 1, i, CharMotionDataNumGet(i, 0xA4));
        Hu3DModelDynamicFree((s16)mchar_chrMdlTbl[i][1]);
        if (mchar_chrMotTbl[i][0] != -1) {
            Hu3DMotionKill((s16)mchar_chrMotTbl[i][0]);
        }
        if (mchar_chrMotTbl[i][1] != -1) {
            Hu3DMotionKill((s16)mchar_chrMotTbl[i][1]);
        }
        data = DataReadTemp(CharMotionDataNumGet(i, 0));
        mchar_chrMotTbl[i][0] = Hu3DMotionCreate(data, 0);
        DataCloseTemp(data);
        mchar_chrMotTbl[i][1] = -1;
        Hu3DMotionSet((s16)mchar_chrMdlTbl[i][0], (s16)mchar_chrMotTbl[i][0]);
    }
}

void mchar_ChrMotionChange(s16 arg0) {
    s16 i;
    void *data;

    for (i = 0; i < 8; i++) {
        if (mchar_chrMotTbl[i][1] != -1) {
            Hu3DMotionKill((s16)mchar_chrMotTbl[i][1]);
        }
        mchar_chrMotTbl[i][1] = mchar_chrMotTbl[i][0];
        data = DataReadTemp(CharMotionDataNumGet(i, arg0));
        mchar_chrMotTbl[i][0] = Hu3DMotionCreate(data, 0);
        DataCloseTemp(data);
    }
    Hu3DMotionShiftSet((s16)mchar_chrMdlTbl[mchar_chrNo][mchar_mdlNo],
                       (s16)mchar_chrMotTbl[mchar_chrNo][0], 0, 10, 2);
}

void mchar_CameraObjMain(omObjData *arg0) {
    f32 dz;
    f32 zoom;
    f32 speed;

    f32 x, y;
    f32 length;
    s8 stick;

    if (HuPadBtn[0] & START_BUTTON) {
        mchar_CameraReset();
    }
    if (HuPadBtn[0] & L_TRIG) {
        if (HuPadBtn[0] & Z_TRIG) {
            zoom = CZoom;
            zoom += 30.0f;
            CZoom = zoom;
        } else {
            zoom = CZoom;
            zoom += 10.0f;
            CZoom = zoom;
        }
    }
    if ((HuPadBtn[0] & R_TRIG) && (CZoom - 10.0f != 0.0f)) {
        if (HuPadBtn[0] & Z_TRIG) {
            CZoom -= 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    x = mchar_cameraRot.x;
    y = mchar_cameraRot.y;
    if (HuPadBtn[0] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    y += (-HuPadStkX[0] / 30) * speed;
    if (y >= 360.0f) {
        y -= 360.0f;
    } else if (y < 0.0f) {
        y += 360.0f;
    }
    mchar_cameraRot.y = y;
    stick = HuPadStkY[0];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    mchar_cameraRot.x = x;
    CRot.x = (s16)x;
    CRot.y = (s16)mchar_cameraRot.y;
    if (HuPadBtn[0] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (HuPadBtn[0] & U_JPAD) {
        Center.x += sindf(y) * sindf(x) * -speed;
        Center.y += cosdf(x) * -speed;
        Center.z += cosdf(y) * sindf(x) * -speed;
    } else if (HuPadBtn[0] & D_JPAD) {
        Center.x += sindf(y) * sindf(x) * speed;
        Center.y += cosdf(x) * speed;
        Center.z += cosdf(y) * sindf(x) * speed;
    } else if (HuPadBtn[0] & L_JPAD) {
        x = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    } else if (HuPadBtn[0] & R_JPAD) {
        x = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    }
}

void mchar_CameraReset(void) {
    mchar_cameraRot.x = mchar_cameraRot.y = mchar_cameraRot.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov = 45.0f;
}

void mchar_ExitCheckObjMain(omObjData *arg0) {
    if ((mchar_exitF != 0) || (omSysExitReq != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = mchar_ExitObjMain;
        HuAudSeqFadeOut(0x3C);
    }
}

void mchar_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
