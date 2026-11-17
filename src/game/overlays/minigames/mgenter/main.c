#include "common.h"
#include "gcc/string.h"

extern s16 mgInstSlotEnd;
extern s16 GameManFirstPad;
extern s16 mgModeCoinBase;
extern u8 storySceneNo;

f32 mgenter_mgPicPosY = 115.0f;
u16 mgenter_exitF = 0;
s16 mgenter_seqKeepF = 0;

extern s16 mgenter_arrowPosF;
extern s16 mgenter_arrowDispF;
extern s16 mgenter_slideInReq;
extern s16 mgenter_mgPicState;
extern s16 mgenter_optionState;
extern s16 mgenter_mgNo;
extern s16 mgenter_stageNo;
extern s16 mgenter_stageNum;
extern s16 mgenter_stageScrollDir;
extern s16 mgenter_optionNo;
extern s16 mgenter_arrowLX;
extern s16 mgenter_arrowRX;
extern s16 mgenter_arrowLY;
extern s16 mgenter_arrowRY;
extern f32 mgenter_cameraFov;
extern f32 mgenter_cameraNear;
extern s16 mgenter_padNo;
extern f32 mgenter_cameraFar;
extern s16 mgenter_exitOvlNo;
extern s16 mgenter_exitMode;
extern s16 mgenter_exitEvtNo;

void mgenter_StageMainProc(void);
void mgenter_MainProc(void);
void mgenter_OptionProc(void);
void mgenter_TitleProc(void);
void mgenter_MesCodeStrip(u8 *str);
void mgenter_StageNameProc(void);
void mgenter_NumMainProc(void);
void mgenter_NumMesSet(s16 winId, s16 value, u8 *buf);
void mgenter_MgPicProc(void);
void mgenter_ArrowPosSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void mgenter_ArrowProc(void);
void mgenter_PlayerGroupSet(void);
void mgenter_ExitCheckObjMain(omObjData *obj);
void mgenter_CameraProc(void);
s16 mgenter_MgPicCreate(void);
void mgenter_MgPicLoad(s16 arg0);
void mgenter_ExitObjMain(omObjData *);
void mgenter_MgPicKill(void);
void mgenter_DpadStickSet(void);

void mgenter_ObjectSetup(void) {
    process_func func;
    s16 typeBits;

    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(0x19);
    omInitObjMan(0x33, 0x19);
    HuWinInit();
    omGameSysInit();
    omAddObj(0x2710, 0, 0, -1, mgenter_ExitCheckObjMain);
    Hu3DGLightMaxSet(1);
    mgenter_cameraFar = 8000.0f;
    mgenter_cameraFov = 45.0f;
    mgenter_cameraNear = 80.0f;
    CRot.x = 354.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2240.0f;
    Center.x = 0.0f;
    Center.y = 260.0f;
    Center.z = 13.0f;
    Hu3DCameraPerspectiveSet(0, mgenter_cameraFov, mgenter_cameraNear, mgenter_cameraFar);
    omPrcSetStatBit(omAddPrcObj(mgenter_CameraProc, 0x1100, 0x800, 0), 0xA0);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    Hu3DScreenClearF = 1;
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    mgenter_padNo = GameManFirstPad;
    mgenter_exitMode = 1;
    mgenter_exitOvlNo = MgDataMaxGet(GwSystem.minigame_index);
    mgenter_exitEvtNo = 0;
    mgenter_mgNo = GwSystem.minigame_index - 1;
    typeBits = (mgDataTbl[mgenter_mgNo].flags & 0x3800) >> 11;
    mgenter_stageNum = typeBits + 1;
    if (mgenter_stageNum >= 2) {
        mgenter_stageNum = typeBits;
    }
    if (mgenter_mgNo == 70) {
        func = mgenter_StageMainProc;
    } else if (mgenter_mgNo == 30) {
        func = mgenter_NumMainProc;
    } else {
        func = mgenter_MainProc;
    }
    omAddPrcObj(func, 0x3F00, 0x2000, 0);
    if (mgModeCoinBase != 0) {
        GwSystem.show_minigame_explanations = 1;
    } else {
        mgModeCoinBase++;
    }
    _SetFlag(0xD);
    HuAudSeqPlay(8);
}

void mgenter_SkipObjectSetup(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(0x19);
    omInitObjMan(0x33, 0x19);
    omOvlHisChg(0, 0x68, 0, OM_OVL_STAT_MG);
    omOvlCallEx(inst, 0, OM_OVL_STAT_BOARD);
    _SetFlag(0xD);
    mgModeCoinBase++;
}

void mgenter_StageMainProc(void) {
    s16 size[2];
    s16 winId;
    s16 confirmed;

    mgenter_stageNo = mgInstSlotEnd;
    if (mgenter_stageNo < 0) {
        mgenter_stageNo = 0;
    }
    mgenter_stageScrollDir = 0;
    mgenter_optionState = -1;
    omAddPrcObj(mgenter_ArrowProc, 0x3F00, 0x800, 0);
    omAddPrcObj(mgenter_TitleProc, 0x3F00, 0x800, 0);
    omAddPrcObj(mgenter_StageNameProc, 0x3F00, 0x800, 0);
    omAddPrcObj(mgenter_MgPicProc, 0x3F00, 0x800, 0);
    omAddPrcObj(mgenter_OptionProc, 0x3F00, 0x800, 0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgenter_slideInReq = 0;
    mgenter_mgPicState = 0;
    HuPrcSleep(10);
    HuWinMesMaxSizeGet(3, size, 0x4600, 0x4601, 0x4603);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    mgenter_optionNo = 0;
    while (TRUE) {
        HuWinMesSet(winId, 0x4600, -1, -1);
        while (HuWinStatGet(winId) != 0) {
            HuPrcVSleep();
        }
        mgenter_ArrowPosSet(60, 110, 260, 110);
        mgenter_arrowDispF = 1;
        while (TRUE) {
            mgenter_DpadStickSet();
            if (HuPadStkX[mgenter_padNo] >= 31 || (HuPadBtnDown[mgenter_padNo] & R_CBUTTONS)) {
                HuAudFXPlay(1);
                mgenter_stageScrollDir = 1;
                mgenter_arrowDispF = 0;
                HuPrcSleep(10);
                mgenter_arrowDispF = 1;
            } else if (HuPadStkX[mgenter_padNo] < -30 || (HuPadBtnDown[mgenter_padNo] & L_CBUTTONS)) {
                HuAudFXPlay(1);
                mgenter_stageScrollDir = -1;
                mgenter_arrowDispF = 0;
                HuPrcSleep(10);
                mgenter_arrowDispF = 1;
            }
            if (HuPadBtnDown[mgenter_padNo] & A_BUTTON) {
                HuAudFXPlay(2);
                mgInstSlotEnd = mgenter_stageNo;
                storySceneNo = mgenter_stageNo;
                break;
            }
            if (HuPadBtnDown[mgenter_padNo] & B_BUTTON) {
                HuAudFXPlay(4);
                mgInstSlotEnd = -1;
                mgenter_exitMode = 0;
                mgenter_exitF = 1;
                mgenter_seqKeepF = 1;
                while (TRUE) {
                    HuPrcVSleep();
                }
            }
            HuPrcVSleep();
        }
        mgenter_arrowDispF = 0;
        mgenter_mgPicState = 1;
        mgenter_optionState = 0;
        HuPrcSleep(10);
        mgenter_ArrowPosSet(80, 155, 240, 155);
        mgenter_arrowDispF = 1;
        HuWinMesSet(winId, 0x4603, -1, -1);
        while (HuWinStatGet(winId) != 0) {
            HuPrcVSleep();
        }
        while (TRUE) {
            mgenter_DpadStickSet();
            if (HuPadStkX[mgenter_padNo] >= 31 || (HuPadBtnDown[mgenter_padNo] & R_CBUTTONS)) {
                HuAudFXPlay(1);
                if (++mgenter_optionNo >= 3) {
                    mgenter_optionNo = 0;
                }
                mgenter_arrowDispF = 0;
                HuPrcSleep(10);
                mgenter_arrowDispF = 1;
            } else if (HuPadStkX[mgenter_padNo] < -30 || (HuPadBtnDown[mgenter_padNo] & L_CBUTTONS)) {
                HuAudFXPlay(1);
                if (--mgenter_optionNo < 0) {
                    mgenter_optionNo = 2;
                }
                mgenter_arrowDispF = 0;
                HuPrcSleep(10);
                mgenter_arrowDispF = 1;
            }
            if (HuPadBtnDown[mgenter_padNo] & A_BUTTON) {
                HuAudFXPlay(2);
                confirmed = TRUE;
                break;
            }
            if (HuPadBtnDown[mgenter_padNo] & B_BUTTON) {
                HuAudFXPlay(4);
                confirmed = FALSE;
                break;
            }
            HuPrcVSleep();
        }
        if (confirmed) {
            break;
        }
        mgenter_arrowDispF = 0;
        mgenter_mgPicState = 2;
        mgenter_optionState = 1;
        HuPrcSleep(10);
    }
    GwPlayer[0].group = 0;
    mgModeCoinRate = mgenter_optionNo;
    HuWinKill(winId);
    mgenter_exitMode = 2;
    mgenter_exitOvlNo = MgDataMaxGet(GwSystem.minigame_index);
    mgenter_exitEvtNo = 0;
    mgenter_exitF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void mgenter_MainProc(void) {
    s16 size[2];
    u16 sprite;
    s16 i;
    s16 winId;
    s16 btn;

    mgInstSlotEnd = -1;
    omAddPrcObj(mgenter_TitleProc, 0x3F00, 0x800, 0);
    sprite = mgenter_MgPicCreate();
    mgenter_MgPicLoad(mgDataTbl[mgenter_mgNo].flags & 0x7FF);
    espPosSet(sprite, 0, -100);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgenter_slideInReq = 0;
    for (i = 0; i < 11; i++) {
        espPosSet(sprite, sindf(i * 9.0f) * 240.0f - 80.0f, 115);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, size, 0x4607);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    HuWinMesSet(winId, 0x4607, -1, -1);
    while (HuWinStatGet(winId) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        btn = HuPadBtnDown[mgenter_padNo];
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            mgenter_exitMode = 0;
            mgenter_exitF = 1;
            mgenter_seqKeepF = 1;
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    mgenter_PlayerGroupSet();
    HuWinKill(winId);
    mgenter_exitMode = 2;
    mgenter_exitOvlNo = MgDataMaxGet(GwSystem.minigame_index);
    mgenter_exitEvtNo = 0;
    mgenter_exitF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void mgenter_TitleProc(void) {
    GAMEMES gMes;
    u8 *text;
    s16 strId;
    s16 i;
    f32 y;

    text = MessDataMesGet((void *)(mgenter_mgNo + 0x4700));
    mgenter_MesCodeStrip(text);
    strId = GameMesStrInit(&gMes, (char *)text, 0, -1, -1);
    HuSprPosSet(gMes.strGId[strId], 0, 0, -100);
    MessDataMesFree(text);
    mgenter_slideInReq = -1;
    if (mgenter_stageNum != 1) {
        y = 28.0f;
    } else {
        y = 44.0f;
    }
    while (TRUE) {
        if (mgenter_slideInReq == 0) {
            for (i = 0; i < 11; i++) {
                HuSprPosSet(gMes.strGId[strId], 0, sindf(i * 9.0f) * 160.0f, y);
                HuPrcVSleep();
            }
            mgenter_slideInReq = -1;
        }
        HuPrcVSleep();
    }
}

void mgenter_MesCodeStrip(u8 *str) {
    u8 *dst = str;
    u8 *src = str;
    u32 c;

    while (*src != '\0') {
        *dst = *src;
        c = *src;
        if (c >= 0x20 || c == 0x10) {
            dst++;
        } else if (c == 0x20 || c == 0x11) {
            dst++;
        } else {
            src++;
            continue;
        }
        src++;
    }
    *dst = '\0';
}

void mgenter_StageNameProc(void) {
    GAMEMES gMes[3];
    u8 buf[32];
    u8 *text;
    s16 len;
    s16 i;
    s16 j;
    s16 k;
    s16 strId;
    s16 cur;
    f32 x;

    cur = mgenter_stageNo;
    for (i = 0; i < 3; i++) {
        text = MessDataMesGet((void *)(i + 0x4608));
        len = strlen((char *)text);
        k = 0;
        for (j = 0; j <= len; j++) {
            if (text[j] < 0x30 && text[j] != 0x20) {
                continue;
            }
            buf[k++] = text[j];
        }
        buf[k] = '\0';
        strId = GameMesStrInit(&gMes[i], (char *)buf, 0, -1, -1);
        HuSprPosSet(gMes[i].strGId[strId], 0, -340, 52);
        gMes[i].subMode = k;
        MessDataMesFree(text);
    }
    while (TRUE) {
        if (mgenter_slideInReq == 0) {
            for (i = 0; i < 11; i++) {
                x = sindf(i * 9.0f) * 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
        }
        if (mgenter_stageScrollDir != 0) {
            for (i = 1; i < 6; i++) {
                x = (1.0f - cosdf(i * 18.0f)) * 240.0f * mgenter_stageScrollDir + 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
            cur += mgenter_stageScrollDir;
            if (cur >= 3) {
                cur = 0;
            }
            if (cur < 0) {
                cur = 2;
            }
            for (i = 1; i < 6; i++) {
                x = -(1.0f - sindf(i * 18.0f)) * 240.0f * mgenter_stageScrollDir + 160.0f;
                HuSprPosSet(gMes[cur].strGId[strId], 0, x, 52);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void mgenter_OptionProc(void) {
    s16 models[3];
    GAMEMES gMes[3];
    u8 buf[32];
    u8 mesIds[] = { 1, 0, 2 };
    u8 charIds[] = { 0, 2, 1 };
    HmfData *hmf;
    u8 *text;
    s16 model;
    s16 len;
    s16 strId;
    s16 i;
    s16 j;
    s16 k;
    s16 prevSel;
    f32 baseAngle;
    f32 rotAngle;
    f32 dir;
    f32 alpha;

    Hu3DFogSet(500, 550, 255, 255, 255);
    for (i = 0; i < 3; i++) {
        models[i] = Hu3DModelRead(charIds[i] | 0x670000, 0x2BD);
        model = models[i];
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionAttrSet(model, 1, 1);
        Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02 / 2);
        Hu3DModelPosSet(model, sindf(i * 120) * 500.0f, 0.0f, cosdf(i * 120) * 500.0f);
        hmf = Hu3DData[model].hmf;
        hmf->unk60[SearchObjectIndex(hmf, "atama_2")].unk24 = 1;
        Hu3DData[model].rot.x = 20.0f;
    }
    for (i = 0; i < 3; i++) {
        text = MessDataMesGet((void *)(mesIds[i] + 0x4604));
        len = strlen((char *)text);
        j = 0;
        for (k = 0; k <= len; k++) {
            if (text[k] >= 0x30) {
                buf[j++] = text[k];
            }
        }
        buf[j] = '\0';
        strId = GameMesStrInit(&gMes[i], (char *)buf, 0, -1, -1);
        HuSprPosSet(gMes[i].strGId[strId], 0, 160, 130);
        len = j;
        gMes[i].subMode = j;
        for (j = 0; j < len; j++) {
            HuSprTPLvlSet(gMes[i].strGId[0], j + 1, 0);
        }
        MessDataMesFree(text);
    }
    baseAngle = 0.0f;
    prevSel = mgenter_optionNo;
    rotAngle = 0.0f;
    while (TRUE) {
        switch (mgenter_optionState) {
            case 0:
                baseAngle = mgenter_optionNo * 120;
                prevSel = mgenter_optionNo;
                for (j = 0; j < 3; j++) {
                    Hu3DModelPosSet(models[j], sindf(j * 120 + baseAngle) * 500.0f, 0.0f,
                                    cosdf(j * 120 + baseAngle) * 500.0f);
                }
                for (i = 0; i < 3; i++) {
                    if (Hu3DData[models[i]].pos.z > 0.0f) {
                        Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    } else {
                        Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                }
                for (i = 0; i < 6; i++) {
                    alpha = i * 51.0f;
                    for (j = 0; j < gMes[mgenter_optionNo].subMode; j++) {
                        HuSprTPLvlSet(gMes[mgenter_optionNo].strGId[0], j + 1, alpha);
                    }
                    HuPrcVSleep();
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                Hu3DModelAttrSet(models[mgenter_optionNo], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                for (i = 0; i < 6; i++) {
                    alpha = i * 51.0f;
                    for (j = 0; j < gMes[mgenter_optionNo].subMode; j++) {
                        HuSprTPLvlSet(gMes[mgenter_optionNo].strGId[0], j + 1, 255.0f - alpha);
                    }
                    HuPrcVSleep();
                }
                HuPrcSleep(5);
                for (i = 0; i < 3; i++) {
                    Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                break;
        }
        mgenter_optionState = -1;
        if (prevSel != mgenter_optionNo) {
            dir = -HuSignF(prevSel - mgenter_optionNo);
            if ((mgenter_optionNo == 2 && prevSel == 0) || (mgenter_optionNo == 0 && prevSel == 2)) {
                dir = -dir;
            }
            for (i = 0; i < 3; i++) {
                Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            for (i = 1; i < 11; i++) {
                for (j = 0; j < 3; j++) {
                    Hu3DModelPosSet(models[j], sindf(j * 120 + baseAngle + i * 12 * dir) * 500.0f, 0.0f,
                                    cosdf(j * 120 + baseAngle + i * 12 * dir) * 500.0f);
                    HuMtxRotYF(Hu3DData[models[j]].mtx, rotAngle);
                }
                alpha = i * 25;
                for (j = 0; j < gMes[prevSel].subMode; j++) {
                    HuSprTPLvlSet(gMes[prevSel].strGId[0], j + 1, 255.0f - alpha);
                }
                for (j = 0; j < gMes[mgenter_optionNo].subMode; j++) {
                    HuSprTPLvlSet(gMes[mgenter_optionNo].strGId[0], j + 1, alpha);
                }
                rotAngle += 3.0f;
                HuPrcVSleep();
            }
            prevSel = mgenter_optionNo;
            for (i = 0; i < 3; i++) {
                if (Hu3DData[models[i]].pos.z > 0.0f) {
                    Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                } else {
                    Hu3DModelAttrSet(models[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
            }
            baseAngle = mgenter_optionNo * 120;
        }
        for (j = 0; j < 3; j++) {
            HuMtxRotYF(Hu3DData[models[j]].mtx, rotAngle);
        }
        rotAngle += 3.0f;
        HuPrcVSleep();
    }
}

void mgenter_NumMainProc(void) {
    s16 size[2];
    u8 buf[16];
    u16 sprite;
    s16 i;
    s16 winId;
    s16 valueWinId;
    s16 value;
    s16 delta;
    s16 btn;

    mgInstSlotEnd = -1;
    omAddPrcObj(mgenter_TitleProc, 0x3F00, 0x800, 0);
    sprite = mgenter_MgPicCreate();
    mgenter_MgPicLoad(mgDataTbl[mgenter_mgNo].flags & 0x7FF);
    espPosSet(sprite, 0, -100);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgenter_slideInReq = 0;
    for (i = 0; i < 11; i++) {
        espPosSet(sprite, sindf(i * 9.0f) * 240.0f - 80.0f, 100);
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, size, 0x4601);
    winId = HuWinExCreate(-1, (320 - size[0]) / 2, 180, size[0], size[1], 0);
    for (i = 0; i < 4; i++) {
        buf[i] = 0xA0;
    }
    buf[i] = '\0';
    HuWinInsertMesSizeGet((u32)buf, 0);
    HuWinMesMaxSizeGet(1, size, 0x4602);
    valueWinId = HuWinExCreate(-1, (320 - size[0]) / 2, 155, size[0], size[1], 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinExAnimIn(winId);
    HuWinMesSet(winId, 0x4601, -1, -1);
    value = 100;
    mgenter_NumMesSet(valueWinId, value, buf);
    HuWinMesSet(valueWinId, 0x4602, -1, -1);
    while (HuWinStatGet(valueWinId) != 0) {
        HuPrcVSleep();
    }
    HuWinExAnimIn(valueWinId);
    while (TRUE) {
        btn = ContBtnRep[mgenter_padNo];
        if (btn & U_JPAD) {
            delta = 100;
        } else {
            delta = (btn & D_JPAD) ? -100 : 0;
        }
        if (value == 1000 && delta > 0) {
            value = 100;
        } else if (value + delta >= 1000) {
            value = 1000;
        } else if (value + delta < 100) {
            value = 1000;
        } else {
            value += delta;
        }
        if (delta != 0) {
            mgenter_NumMesSet(valueWinId, value, buf);
            HuWinMesSet(valueWinId, 0x4602, -1, -1);
        }
        btn = HuPadBtnDown[mgenter_padNo];
        if (btn & A_BUTTON) {
            HuAudFXPlay(2);
            mgModeCoinRate = value;
            break;
        }
        if (btn & B_BUTTON) {
            HuAudFXPlay(4);
            mgenter_exitMode = 0;
            mgenter_exitF = 1;
            mgenter_seqKeepF = 1;
            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    mgenter_PlayerGroupSet();
    HuWinKill(winId);
    HuWinKill(valueWinId);
    mgenter_exitMode = 2;
    mgenter_exitOvlNo = MgDataMaxGet(GwSystem.minigame_index);
    mgenter_exitEvtNo = 0;
    mgenter_exitF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void mgenter_NumMesSet(s16 winId, s16 value, u8 *buf) {
    s16 i;

    sprintf((char *)buf, "%04d", value);
    if (buf[0] == '0') {
        buf[0] = 0x1A;
    }
    for (i = 0; i < 4; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            buf[i] += 0x70;
        }
    }
    HuWinInsertMesSet(winId, (u32)buf, 0);
}

void mgenter_MgPicProc(void) {
    u16 sprite;
    s16 i;
    f32 t;
    f32 x;

    mgenter_slideInReq = -1;
    sprite = mgenter_MgPicCreate();
    mgenter_MgPicLoad((mgDataTbl[mgenter_mgNo].flags & 0x7FF) + mgenter_stageNo * 2);
    espDispOff(sprite);
    mgenter_mgPicState = -1;
    while (TRUE) {
        switch (mgenter_mgPicState) {
            case 0:
                espDispOn(sprite);
                for (i = 0; i < 11; i++) {
                    x = sindf(i * 9.0f) * 240.0f - 80.0f;
                    espPosSet(sprite, x, mgenter_mgPicPosY);
                    HuPrcVSleep();
                }
                mgenter_mgPicState = -1;
                break;
            case 1:
                for (i = 1; i < 11; i++) {
                    t = sindf(i * 9.0f);
                    mgenter_mgPicPosY = 115.0f - t * 35.0f;
                    espPosSet(sprite, 160, mgenter_mgPicPosY);
                    espScaleSet(sprite, 1.0f - t * 0.2f, 1.0f - t * 0.2f);
                    t = 1.0f - t;
                    Hu3DFogSet((s16)(970.0f - t * 100.0f), (s16)(975.0f - t * 100.0f), 255, 255, 255);
                    HuPrcVSleep();
                }
                mgenter_mgPicState = -1;
                break;
            case 2:
                for (i = 1; i < 11; i++) {
                    t = 1.0f - sindf(i * 9.0f);
                    mgenter_mgPicPosY = 115.0f - t * 35.0f;
                    espPosSet(sprite, 160, mgenter_mgPicPosY);
                    espScaleSet(sprite, 1.0f - t * 0.2f, 1.0f - t * 0.2f);
                    t = 1.0f - t;
                    Hu3DFogSet((s16)(970.0f - t * 100.0f), (s16)(975.0f - t * 100.0f), 255, 255, 255);
                    HuPrcVSleep();
                }
                mgenter_mgPicState = -1;
                break;
        }
        if (mgenter_stageScrollDir != 0) {
            for (i = 1; i < 6; i++) {
                x = (1.0f - cosdf(i * 18.0f)) * 240.0f * mgenter_stageScrollDir + 160.0f;
                espPosSet(sprite, x, mgenter_mgPicPosY);
                HuPrcVSleep();
            }
            mgenter_stageNo += mgenter_stageScrollDir;
            if (mgenter_stageNo >= mgenter_stageNum) {
                mgenter_stageNo = 0;
            }
            if (mgenter_stageNo < 0) {
                mgenter_stageNo = mgenter_stageNum - 1;
            }
            mgenter_MgPicLoad((mgDataTbl[mgenter_mgNo].flags & 0x7FF) + mgenter_stageNo * 2);
            for (i = 1; i < 6; i++) {
                x = -(1.0f - sindf(i * 18.0f)) * 240.0f * mgenter_stageScrollDir + 160.0f;
                espPosSet(sprite, x, mgenter_mgPicPosY);
                HuPrcVSleep();
            }
            mgenter_stageScrollDir = 0;
        }
        HuPrcVSleep();
    }
}

void mgenter_ArrowPosSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    mgenter_arrowLX = arg0;
    mgenter_arrowRX = arg2;
    mgenter_arrowLY = arg1;
    mgenter_arrowRY = arg3;
    mgenter_arrowPosF = 1;
}

void mgenter_ArrowProc(void) {
    s8 prevState = 0;
    s16 fading = 0;
    s16 data1;
    s16 data2;
    s16 sprite1;
    s16 sprite2;
    s16 alpha;
    s16 prevAlpha;
    s16 step;

    mgenter_arrowDispF = 0;
    mgenter_arrowPosF = 0;
    data1 = HuSprAnimDataRead(0x140012);
    data2 = HuSprAnimDataRead(0x140013);
    sprite1 = espEntry(data1, 0, 1);
    sprite2 = espEntry(data2, 0, 1);
    espPriSet(sprite1, 0x4800);
    espPriSet(sprite2, 0x4800);
    espPosSet(sprite1, 160, 120);
    espPosSet(sprite2, 160, 120);
    espDispOff(sprite1);
    espDispOff(sprite2);
    alpha = 0;
    step = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (prevState != mgenter_arrowDispF) {
            prevState = mgenter_arrowDispF;
            fading = 1;
            if (mgenter_arrowDispF != 0) {
                step = 63;
            } else {
                step = -63;
            }
        }
        if (fading) {
            prevAlpha = alpha;
            alpha += step;
            if (alpha >= 255) {
                fading = 0;
                alpha = 255;
            } else if (alpha <= 0) {
                fading = 0;
                alpha = 0;
            }
            if (alpha != 0) {
                if (prevAlpha == 0) {
                    espDispOn(sprite1);
                    espDispOn(sprite2);
                }
                espTPLvlSet(sprite1, alpha);
                espTPLvlSet(sprite2, alpha);
            } else {
                espDispOff(sprite1);
                espDispOff(sprite2);
            }
        }
        if (mgenter_arrowPosF != 0) {
            espPosSet(sprite1, mgenter_arrowLX, mgenter_arrowLY);
            espPosSet(sprite2, mgenter_arrowRX, mgenter_arrowRY);
            mgenter_arrowPosF = 0;
        }
    }
}

void mgenter_PlayerGroupSet(void) {
    s16 minigameType = mgDataTbl[mgenter_mgNo].minigameType;
    s16 i;

    if (minigameType == 1 || minigameType == 2) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].group >= 2) {
                break;
            }
        }
        if (i == 4) {
            return;
        }
        if (minigameType == 2) {
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].group != 0) {
                    GwPlayer[i].group = 1;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].group < 2) {
                    GwPlayer[i].group = 0;
                } else {
                    GwPlayer[i].group = 1;
                }
            }
        }
    }
}

void mgenter_ExitCheckObjMain(omObjData *obj) {
    if ((mgenter_exitF != 0) || (omSysExitReq != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        if (mgenter_seqKeepF == 0) {
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = mgenter_ExitObjMain;
    }
}

void mgenter_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() != 0) {
        return;
    }
    mgenter_MgPicKill();
    HuWinAllKill();
    switch (mgenter_exitMode) {
        case 0:
            omOvlReturnEx(1);
            break;
        case 2:
            omOvlCallEx(mgenter_exitOvlNo, mgenter_exitEvtNo, OM_OVL_STAT_MGLIB | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_AUDFX1);
            break;
        case 1:
            omOvlGotoEx(mgenter_exitOvlNo, mgenter_exitEvtNo, OM_OVL_STAT_MGLIB | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_AUDFX1);
            break;
    }
}
