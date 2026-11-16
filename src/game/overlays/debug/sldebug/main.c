#include "common.h"
#include "macros.h"
#include "game/printfunc.h"
#include "game/overlays/opening.h"

void sldebug_MenuObjMain(omObjData *); /* extern */
void sldebug_CameraDebugObjMain(omObjData *); /* extern */
void sldebug_MenuIdleObjMain(omObjData *arg0);
s32 sldebug_MenuDecide(void);
void sldebug_CameraReset(void);        /* extern */
void sldebug_ExitCheckObjMain(omObjData *); /* extern */
void sldebug_ExitObjMain(omObjData *); /* extern */

u16 sldebug_exitF = 0;
s32 sldebug_storyEvtNo = 4;
u8 sldebug_storyTypeTbl[13] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 2 };
s32 sldebug_cursorPos = 0;
s32 sldebug_storyNo = 0;
s32 sldebug_storySaveF = 0;
s32 sldebug_storyChrNo = 0;
s32 sldebug_storyComLevel = 0;
s16 sldebug_infoDispF = 0;

Vec sldebug_cameraRotDefault BSS;
f32 sldebug_cameraZoomDefault BSS;
Vec sldebug_cameraRot BSS;
Vec sldebug_cameraCenterDefault BSS;

void sldebug_ObjectSetup(void) {
    Hu3DCamInit(1);
    MapCollInit(1);
    Hu3DSprModelInit(0x2D);
    omInitObjMan(0x33, 0xA);
    omGameSysInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(0x2710, 0, 0, -1, sldebug_ExitCheckObjMain);
    Hu3DGLightMaxSet(4);
    Hu3DGLightColorSet(0, 0x78, 0x78, 0x78);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, -100.0f, 100.0f, 100.0f);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    sldebug_cameraRotDefault.x = sldebug_cameraRotDefault.y = sldebug_cameraRotDefault.z = 0.0f;
    sldebug_cameraZoomDefault = 400.0f;
    sldebug_cameraCenterDefault.x = sldebug_cameraCenterDefault.z = 0.0f;
    sldebug_cameraCenterDefault.y = 150.0f;
    gCameraList->fov = 45.0f;
    sldebug_CameraReset();
    omAddObj(0x7D0, 0xA, 0xA, -1, sldebug_MenuObjMain);
    omAddObj(0x7D0, 0, 0, -1, sldebug_CameraDebugObjMain);
    WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
    Hu3DScreenClearF = 1;
    SLLoadStory();
    HuAudSeqPlay(8);
}

void sldebug_MenuObjMain(omObjData *arg0) {
    char *storyNames[] = {
        "STORY NO.00", "STORY NO.01", "STORY NO.02", "STORY NO.03", "STORY NO.04", "STORY NO.05",
        "STORY NO.06", "STORY NO.07", "STORY NO.08", "STORY NO.09", "STORY NO.10", "STORY NO.11", "STORY NO.12"
    };
    char *heroNames[] = { "STORY HERO  MARIO", "STORY HERO  LUIGI", "STORY HERO  PEACH", "STORY HERO  YOSHI", "STORY HERO  WARIO", "STORY HERO  DONKEY" };
    char *difficultyNames[] = { "STORY DIFF  EASY", "STORY DIFF  NORMAL", "STORY DIFF  HARD", "STORY DIFF  VERYHARD" };
    s16 i;

    fontcolor = FONT_COLOR_WHITE;
    print8(70, 80, "ALL MINIGAME ENABLE");
    print8(70, 90, "WLUIGI & DAISY ENABLE");
    print8(70, 100, storyNames[sldebug_storyNo]);
    print8(70, 110, heroNames[sldebug_storyChrNo]);
    print8(70, 120, difficultyNames[sldebug_storyComLevel]);
    print8(70, 130, "WLUIGILAND & REVKUNMAP ENABLE");
    print8(70, 140, "EXIT");
    if (ContBtnRep[0] & U_JPAD) {
        HuAudFXPlay(1);
        sldebug_cursorPos--;
        if (sldebug_cursorPos < 0) {
            sldebug_cursorPos = 6;
        }
    } else if (ContBtnRep[0] & D_JPAD) {
        HuAudFXPlay(1);
        sldebug_cursorPos++;
        if (sldebug_cursorPos >= 7) {
            sldebug_cursorPos = 0;
        }
    } else if (ContBtnRep[0] & L_JPAD) {
        switch (sldebug_cursorPos) {
            case 2:
                HuAudFXPlay(1);
                sldebug_storyNo--;
                if (sldebug_storyNo < 0) {
                    sldebug_storyNo = 12;
                }
                break;
            case 3:
                HuAudFXPlay(1);
                sldebug_storyChrNo--;
                if (sldebug_storyChrNo < 0) {
                    sldebug_storyChrNo = 5;
                }
                break;
            case 4:
                HuAudFXPlay(1);
                sldebug_storyComLevel--;
                if (sldebug_storyComLevel < 0) {
                    sldebug_storyComLevel = 3;
                }
                break;
        }
    } else if (ContBtnRep[0] & R_JPAD) {
        switch (sldebug_cursorPos) {
            case 2:
                HuAudFXPlay(1);
                sldebug_storyNo++;
                if (sldebug_storyNo >= 13) {
                    sldebug_storyNo = 0;
                }
                break;
            case 3:
                HuAudFXPlay(1);
                sldebug_storyChrNo++;
                if (sldebug_storyChrNo >= 6) {
                    sldebug_storyChrNo = 0;
                }
                break;
            case 4:
                HuAudFXPlay(1);
                sldebug_storyComLevel++;
                if (sldebug_storyComLevel >= 4) {
                    sldebug_storyComLevel = 0;
                }
                break;
        }
    } else if (HuPadBtnDown[0] & A_BUTTON) {
        if (sldebug_MenuDecide() != 0) {
            if (sldebug_storySaveF != 0) {
                GwStory.unk0 = sldebug_storyNo;
                for (i = 0; i < 13; i++) {
                    if (i < sldebug_storyNo) {
                        GwStory.progress.storyProgress[i] = 4;
                    } else {
                        GwStory.progress.storyProgress[i] = 0;
                    }
                }
                if (sldebug_storyNo == 12) {
                    GwStory.progress.fields.unkF = 4;
                }
                GwStory.unk2 = sldebug_storyComLevel;
                GwStory.unk1 = sldebug_storyChrNo;
                _ClearFlag(0x28);
                _SetFlag(0x18);
                GwSystem.playMode = 4;
                if (sldebug_storyTypeTbl[sldebug_storyNo] == 0) {
                    sldebug_storyEvtNo = 2;
                    GwSystem.playMode = 5;
                } else if (sldebug_storyTypeTbl[sldebug_storyNo] == 1) {
                    sldebug_storyEvtNo = 0x4000;
                    GwSystem.playMode |= 2;
                } else {
                    sldebug_storyEvtNo = 4;
                }
                SLSaveStory(1);
            } else {
                SLCommonSet(1);
            }
            sldebug_exitF = 1;
            arg0->func = sldebug_MenuIdleObjMain;
        }
        return;
    }
    print8(60, sldebug_cursorPos * 10 + 80, ">");
}

void sldebug_MenuIdleObjMain(omObjData *arg0) {
}

s32 sldebug_MenuDecide(void) {
    s16 i;

    HuAudFXPlay(2);
    switch (sldebug_cursorPos) {
        case 0:
            _SetFlag(0x1D);
            if ((u16)HuPadBtn[0] & A_BUTTON) {
                for (i = 0; i < 0x48; i++) {
                    GWMgUnlockSet(i);
                }
            } else {
                for (i = 0; i < 0x48; i += 3) {
                    GWMgUnlockSet(i);
                }
            }
            _SetFlag(0x1E);
            _SetFlag(0x1F);
            break;
        case 1:
            _SetFlag(0x2E);
            _SetFlag(0x2F);
            break;
        case 2:
        case 3:
        case 4:
            sldebug_storySaveF = 1;
            break;
        case 5:
            _SetFlag(0x30);
            _SetFlag(0x31);
            break;
        case 6:
            return 1;
    }
    return 0;
}

void sldebug_CameraDebugObjMain(omObjData *arg0) {
    char text[256];
    f32 speed;
    f32 zoom;
    f32 xRot;
    f32 yRot;
    f32 z;
    f32 scale;
    f32 backSpeed;
    s8 stick;

    if (HuPadBtnDown[0] & R_TRIG) {
        sldebug_infoDispF ^= 1;
    }
    if (HuPadBtn[0] & START_BUTTON) {
        sldebug_CameraReset();
    }
    if (HuPadBtn[0] & U_CBUTTONS) {
        if (HuPadBtn[0] & Z_TRIG) {
            zoom = CZoom + 30.0f;
        } else {
            zoom = CZoom + 10.0f;
        }
        CZoom = zoom;
    }
    if ((HuPadBtn[0] & D_CBUTTONS) && CZoom - 10.0f != 0.0f) {
        if (HuPadBtn[0] & Z_TRIG) {
            CZoom = CZoom - 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    xRot = sldebug_cameraRot.x;
    yRot = sldebug_cameraRot.y;
    if (HuPadBtn[0] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    yRot += (-HuPadStkX[0] / 30) * speed;
    if (yRot >= 360.0f) {
        yRot -= 360.0f;
    } else if (yRot < 0.0f) {
        yRot += 360.0f;
    }
    sldebug_cameraRot.y = yRot;
    stick = HuPadStkY[0] / 30;
    xRot += stick * speed;
    if (xRot >= 360.0f) {
        xRot -= 360.0f;
    } else if (xRot < 0.0f) {
        xRot += 360.0f;
    }
    sldebug_cameraRot.x = xRot;
    CRot.x = (s16)sldebug_cameraRot.x;
    CRot.y = (s16)sldebug_cameraRot.y;
    if (HuPadBtn[0] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (HuPadBtn[0] & U_JPAD) {
        Center.x += sindf(yRot) * sindf(xRot) * (backSpeed = -speed);
        Center.y = cosdf(xRot) * backSpeed + Center.y;
        Center.z = cosdf(yRot) * sindf(xRot) * backSpeed + Center.z;
    } else if (HuPadBtn[0] & D_JPAD) {
        Center.x += sindf(yRot) * sindf(xRot) * speed;
        Center.y = cosdf(xRot) * speed + Center.y;
        Center.z = cosdf(yRot) * sindf(xRot) * speed + Center.z;
    } else if (HuPadBtn[0] & L_JPAD) {
        xRot = gCameraList->pos.z - Center.z;
        z = -(gCameraList->pos.x - Center.x);
        scale = 1.0f / HuSqrtf(xRot * xRot + z * z);
        Center.x += xRot * scale * speed;
        Center.y += 0.0f;
        Center.z += z * scale * speed;
    } else if (HuPadBtn[0] & R_JPAD) {
        xRot = -(gCameraList->pos.z - Center.z);
        z = gCameraList->pos.x - Center.x;
        scale = 1.0f / HuSqrtf(xRot * xRot + z * z);
        Center.x += xRot * scale * speed;
        Center.y += 0.0f;
        Center.z += z * scale * speed;
    }
    if (sldebug_infoDispF != 0) {
        sprintf(text, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, text);
        sprintf(text, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, text);
        sprintf(text, "CZOOM %4.1f", CZoom);
        print8(32, 200, text);
    }
}

void sldebug_CameraReset(void) {
    CRot = sldebug_cameraRotDefault;
    sldebug_cameraRot = CRot;
    CZoom = sldebug_cameraZoomDefault;
    Center = sldebug_cameraCenterDefault;
}

void sldebug_ExitCheckObjMain(omObjData *arg0) {
    if ((sldebug_exitF != 0) || (omSysExitReq != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = sldebug_ExitObjMain;
        HuAudSeqFadeOut(0x3C);
    }
}

void sldebug_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlGotoEx(0x58, 0, 0x81);
    }
}
