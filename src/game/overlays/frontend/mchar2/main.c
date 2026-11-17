#include "common.h"
#include "game/printfunc.h"

u16 mchar2_exitF = 0;
u8 mchar2_infoDispF = 1;
s16 mchar2_voiceChrTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
u16 mchar2_motNoTbl[] = { 0, 1, 2, 3, 0x802F, 0x8036, 0xFFFF };
char *mchar2_motNameTbl[] = {
    "C000_000", "C000_001", "C000_003", "C000_004", "C000_400", "C000_407"
};
s16 mchar2_chrNo = 0;
s16 mchar2_motIdx = 0;
s16 mchar2_mdlNo = 1;
s16 mchar2_mdlSetNo = 0;
u8 mchar2_startCnt = 0;
u8 mchar2_reloadCnt = 0;
s32 mchar2_mdlFileTbl[] = { 0x800A2, 0x800A0, 0x90003, 0x90000 };

static u8 mchar2_motNum;
static s32 mchar2_chrMdlTbl[8][2];
static s32 mchar2_chrMotTbl[8][2];
static char mchar2_printStr[0x100];
static Vec mchar2_cameraRot;


void mchar2_ChrMotionChange(s32 arg0);
void mchar2_ViewerObjInit(omObjData *arg0);
void mchar2_ViewerObjMain(omObjData *arg0);
void mchar2_ChrModelRead(s32 arg0);
void mchar2_CameraObjMain(omObjData *arg0);
void mchar2_CameraReset(void);
void mchar2_ExitCheckObjMain(omObjData *arg0);

void mchar2_ExitObjMain(omObjData *arg0);

void mchar2_ObjectSetup(void) {
    s16 i;

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
    omAddObj(0x2710, 0, 0, -1, mchar2_ExitCheckObjMain);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x78, 0x78, 0x78);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, -100.0f, 100.0f, 100.0f);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    mchar2_CameraReset();
    omAddObj(0x7D0, 10, 10, -1, mchar2_ViewerObjInit);
    omAddObj(0x7D0, 0, 0, -1, mchar2_CameraObjMain);
    WipeCreateIn(WIPE_TYPE_NORMAL, 16);
    Hu3DScreenClearF = 1;
    Hu3DBGColorSet(0xC0, 0xE0, 0xFF);
    for (i = 0; mchar2_motNoTbl[i] != 0xFFFF; i++) {}
    mchar2_motNum = i;
    HuAudCharVoiceInit();
}

void mchar2_ViewerObjInit(omObjData *arg0) {
    s16 i;

    arg0->model[0] = -1;
    for (i = 0; i < 8; i++) {
        mchar2_chrMdlTbl[i][0] = mchar2_chrMdlTbl[i][1] =
            mchar2_chrMotTbl[i][0] = mchar2_chrMotTbl[i][1] = -1;
    }
    mchar2_mdlSetNo = 0;
    mchar2_ChrModelRead(0);
    Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], 2, 2);
    arg0->func = mchar2_ViewerObjMain;
}

void mchar2_ViewerObjMain(omObjData *arg0) {
    HmfModel *model;

    if (mchar2_reloadCnt != 0) {
        mchar2_reloadCnt--;
        if (mchar2_reloadCnt == 0) {
            mchar2_ChrModelRead(mchar2_mdlSetNo);
            Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], 2, 2);
        }
    }
    if ((u16)ContBtnRep[0] & A_BUTTON) {
        mchar2_motIdx++;
        if (mchar2_motNoTbl[mchar2_motIdx] == 0xFFFF) {
            mchar2_motIdx = 0;
        }
        mchar2_ChrMotionChange((s16)mchar2_motNoTbl[mchar2_motIdx]);
    }
    if (ContBtnRep[0] & B_BUTTON) {
        mchar2_motIdx--;
        if (mchar2_motIdx < 0) {
            mchar2_motIdx = mchar2_motNum - 1;
        }
        mchar2_ChrMotionChange((s16)mchar2_motNoTbl[mchar2_motIdx]);
    }
    if (HuPadBtnDown[0] & START_BUTTON) {
        mchar2_startCnt++;
    }
    if (HuPadBtnDown[0] & L_CBUTTONS) {
        Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mchar2_chrNo++;
        if (mchar2_chrNo >= 2) {
            mchar2_chrNo = 0;
        }
        Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], (s16)mchar2_chrMotTbl[mchar2_chrNo][0]);
        Hu3DMotionAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], 2, 2);
        HuAudCharVoicePlay((mchar2_voiceChrTbl[mchar2_chrNo] << 16) | mchar2_motIdx);
    }
    if (HuPadBtnDown[0] & R_CBUTTONS) {
        Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mchar2_chrNo--;
        if (mchar2_chrNo < 0) {
            mchar2_chrNo = 1;
        }
        Hu3DModelAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], (s16)mchar2_chrMotTbl[mchar2_chrNo][0]);
        Hu3DMotionAttrSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo], 2, 2);
        HuAudCharVoicePlay((mchar2_voiceChrTbl[mchar2_chrNo] << 16) | mchar2_motIdx);
    }
    if ((u16)ContBtnRep[1] & (A_BUTTON | B_BUTTON)) {
        model = &Hu3DData[mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo]];
        if ((u16)ContBtnRep[1] & B_BUTTON) {
            model->motAttr |= 4;
        }
        model->motAttr &= 0xFE;
        model->motTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motId], model->motAttr, model->motTime, model->unk48, model->motSpeed + model->motSpeed);
        if (model->motIdShift != 0xFF) {
            model->motShiftTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motIdShift], model->motShiftAttr, model->motShiftTime, model->unk54, model->motShiftSpeed + model->motShiftSpeed);
        }
        model->motAttr = (model->motAttr & 0xFB) | 1;
    }
    if ((HuPadBtn[0] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
        mchar2_exitF = 1;
    }
    if (HuPadBtnDown[1] & START_BUTTON) {
        mchar2_infoDispF = !mchar2_infoDispF;
    }
    if (mchar2_infoDispF != 0) {
        model = &Hu3DData[mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo]];
        fontcolor = FONT_COLOR_BLUE;
        sprintf(mchar2_printStr, "MOTIONNO.%3d <%s>", mchar2_motIdx, mchar2_motNameTbl[mchar2_motIdx]);
        print8(24, 182, mchar2_printStr);
        sprintf(mchar2_printStr, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(24, 190, mchar2_printStr);
        sprintf(mchar2_printStr, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(24, 198, mchar2_printStr);
        sprintf(mchar2_printStr, "ZOOM:  %3.3f", CZoom);
        print8(24, 206, mchar2_printStr);
        sprintf(mchar2_printStr, "M_TIME:%d", (u16)model->motTime);
        print8(24, 214, mchar2_printStr);
    }
}

void mchar2_ChrModelRead(s32 arg0) {
    s16 i;
    void *data;
    s16 flags;
    s32 *files0;
    s32 *files1;

    i = 0;
    files0 = mchar2_mdlFileTbl;
    flags = 0x2AC;
    for (; i < 2; i++) {
        mchar2_chrMdlTbl[i][0] = Hu3DModelRead(files0[i * 2], flags);
        files1 = &mchar2_mdlFileTbl[1];
        CharAnimCreate((s16)mchar2_chrMdlTbl[i][0], 0, i + 6, CharMotionDataNumGet(i + 6, 0xA3));
        Hu3DModelDynamicFree((s16)mchar2_chrMdlTbl[i][0]);
        mchar2_chrMdlTbl[i][1] = Hu3DModelRead(files1[i * 2], flags);
        CharAnimCreate((s16)mchar2_chrMdlTbl[i][1], 1, i + 6, CharMotionDataNumGet(i + 6, 0xA4));
        Hu3DModelDynamicFree((s16)mchar2_chrMdlTbl[i][1]);
        if (mchar2_chrMotTbl[i][0] != -1) {
            Hu3DMotionKill((s16)mchar2_chrMotTbl[i][0]);
        }
        if (mchar2_chrMotTbl[i][1] != -1) {
            Hu3DMotionKill((s16)mchar2_chrMotTbl[i][1]);
        }
        data = DataReadTemp(CharMotionDataNumGet(i + 6, 0));
        mchar2_chrMotTbl[i][0] = Hu3DMotionCreate(data, 0);
        DataCloseTemp(data);
        mchar2_chrMotTbl[i][1] = -1;
        Hu3DMotionSet((s16)mchar2_chrMdlTbl[i][0], (s16)mchar2_chrMotTbl[i][0]);
    }
}

void mchar2_ChrMotionChange(s32 arg0) {
    s16 i;
    void *data;

    for (i = 0; i < 2; i++) {
        if (mchar2_chrMotTbl[i][1] != -1) {
            Hu3DMotionKill((s16)mchar2_chrMotTbl[i][1]);
        }
        mchar2_chrMotTbl[i][1] = mchar2_chrMotTbl[i][0];
        data = DataReadTemp(CharMotionDataNumGet(i + 6, arg0 & 0x7FFF));
        mchar2_chrMotTbl[i][0] = Hu3DMotionCreate(data, 0);
        DataCloseTemp(data);
    }
    if (arg0 & 0x8000) {
        Hu3DMotionShiftSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo],
                           (s16)mchar2_chrMotTbl[mchar2_chrNo][0], 0, 10, 0);
    } else {
        Hu3DMotionShiftSet((s16)mchar2_chrMdlTbl[mchar2_chrNo][mchar2_mdlNo],
                           (s16)mchar2_chrMotTbl[mchar2_chrNo][0], 0, 10, 2);
    }
}

void mchar2_CameraObjMain(omObjData *arg0) {
    f32 dz;
    f32 zoom;
    f32 speed;

    f32 x, y;
    f32 length;
    s8 stick;

    if (HuPadBtn[0] & START_BUTTON) {
        mchar2_CameraReset();
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
    x = mchar2_cameraRot.x;
    y = mchar2_cameraRot.y;
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
    mchar2_cameraRot.y = y;
    stick = HuPadStkY[0];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    mchar2_cameraRot.x = x;
    CRot.x = (s16)x;
    CRot.y = (s16)mchar2_cameraRot.y;
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

void mchar2_CameraReset(void) {
    mchar2_cameraRot.x = mchar2_cameraRot.y = mchar2_cameraRot.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov = 45.0f;
}

void mchar2_ExitCheckObjMain(omObjData *arg0) {
    if ((mchar2_exitF != 0) || (omSysExitReq != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = mchar2_ExitObjMain;
        HuAudSeqFadeOut(0x3C);
    }
}

void mchar2_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
