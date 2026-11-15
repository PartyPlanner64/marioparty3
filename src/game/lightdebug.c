#include "ultra64.h"
#include "types.h"
#include "game/lightdebug.h"
#include "game/hmflight.h"
#include "game/printfunc.h"
#include "game/input.h"
#include "humath.h"
#include "game/pad.h"
#include "variables.h"

typedef union LightObjWork {
    u32 words[4];
    s16 halfwords[8];
} LightObjWork;

static omObjData *lightDebugObj = NULL;
static s16 lightDebugNo = 1;
static s16 lightDebugWinPos = 0;
static u8 lightDebugWinAlpha = 0xF0;
static u8 lightDebugMode = 0;
static s8 lightDebugAlphaSpeed = -1;
static char *lightDebugStatStr[] = { "STAT", "CAME" };
static s16 lightDebugWinX0[] = { 16, 72, 224, 88, 152, 232 };
static s16 lightDebugWinY0[] = { 16, 16, 16, 24, 24, 24 };
static s16 lightDebugWinX1[] = { 56, 96, 256, 112, 192, 264 };
static s16 lightDebugWinY1[] = { 24, 24, 24, 32, 32, 32 };
extern UnkLightData *Hu3DLightData;

void LightDebugCreate(void) {
    LightObjWork *work;

    lightDebugObj = omAddObj(0x7FD0, 0, 0, -1, LightDebugExec);
    omSetStatBit(lightDebugObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    work = OM_GET_WORK_PTR(lightDebugObj, LightObjWork);
    work->halfwords[0] = printWin(14, 14, 306, 34, 0xDF70);
    work->halfwords[4] =
        printWin(lightDebugWinX0[lightDebugWinPos], lightDebugWinY0[lightDebugWinPos],
                           lightDebugWinX1[lightDebugWinPos], lightDebugWinY1[lightDebugWinPos],
                           (lightDebugWinAlpha << 24) | 0x80);
    lightDebugMode = 0;
}

void LightDebugKill(void) {
    omObjData *lightObj = lightDebugObj;
    LightObjWork *work;

    if (lightObj != NULL) {
        work = OM_GET_WORK_PTR(lightObj, LightObjWork);
        pfWinKill(work->halfwords[0]);
        pfWinKill(work->halfwords[4]);
        omDelObj(lightDebugObj);
        lightDebugObj = NULL;
    }
}

void LightDebugExec(omObjData *object) {
    s16 *dirWin = &OM_GET_WORK_PTR(lightDebugObj, LightObjWork)->halfwords[0];
    s16 *colorWin = &OM_GET_WORK_PTR(lightDebugObj, LightObjWork)->halfwords[4];
    f32 x, y, z;
    f32 rotY, rotX;
    f32 sinX, cosX, sinY, cosY;
    s16 row, col;
    char *statStr;
    u16 button;

    statStr = lightDebugStatStr[(Hu3DLightData->unk02[lightDebugNo].stat ^ 1) & 1];
    fontcolor = FONT_COLOR_YELLOW;
    sprintf(omDBGStrBuf, "LIGHT%1d DIR%4d,%4d,%4d  STAT %s", lightDebugNo,
            Hu3DLightData->unk02[lightDebugNo].unk04, Hu3DLightData->unk02[lightDebugNo].unk05,
            Hu3DLightData->unk02[lightDebugNo].unk06, statStr);
    print8(16, 16, omDBGStrBuf);
    sprintf(omDBGStrBuf, "COLOR    RED %3d GREEN %3d BLUE %3d", Hu3DLightData->unk02[lightDebugNo].r,
            Hu3DLightData->unk02[lightDebugNo].g, Hu3DLightData->unk02[lightDebugNo].b);
    print8(16, 24, omDBGStrBuf);

    switch (lightDebugMode) {
        case 0:
            if ((HuPadBtnDown[0] & A_BUTTON) && lightDebugWinPos == 1) {
                printWinData[*dirWin].unk_14 = 0x7070;
                lightDebugWinAlpha = 0xF0;
                lightDebugAlphaSpeed = -4;
                lightDebugMode = 1;
                break;
            }
            lightDebugWinAlpha += lightDebugAlphaSpeed;
            if (lightDebugAlphaSpeed < 0) {
                if (lightDebugWinAlpha <= 0x80) {
                    lightDebugAlphaSpeed = 4;
                }
            } else if (lightDebugWinAlpha >= 0xF0) {
                lightDebugAlphaSpeed = -4;
            }

            button = ContBtnRep[0];
            row = lightDebugWinPos / 3;
            col = lightDebugWinPos % 3;
            if (button & L_JPAD) {
                if (col == 0) {
                    lightDebugWinPos = row * 3 + 2;
                } else {
                    lightDebugWinPos--;
                }
            } else if (button & R_JPAD) {
                if (col == 2) {
                    lightDebugWinPos = row * 3;
                } else {
                    lightDebugWinPos++;
                }
            } else if (button & U_JPAD) {
                if (row == 0) {
                    lightDebugWinPos = col + 3;
                } else {
                    lightDebugWinPos -= 3;
                }
            } else if (button & D_JPAD) {
                if (row == 1) {
                    lightDebugWinPos = col;
                } else {
                    lightDebugWinPos += 3;
                }
            }

            switch (lightDebugWinPos) {
                case 0:
                    if ((HuPadBtnRep[0] & D_CBUTTONS) && lightDebugNo >= 2) {
                        lightDebugNo--;
                    }
                    if ((HuPadBtnRep[0] & U_CBUTTONS) && lightDebugNo < Hu3DLightData->unk00) {
                        lightDebugNo++;
                    }
                    break;
                case 1:
                    break;
                case 2:
                    if (HuPadBtnRep[0] & (A_BUTTON | U_CBUTTONS | D_CBUTTONS)) {
                        if (Hu3DLightData->unk02[lightDebugNo].stat & 1) {
                            Hu3DGLightStatSet(lightDebugNo, 1, 0);
                        } else {
                            Hu3DGLightStatSet(lightDebugNo, 1, 1);
                        }
                    }
                    break;
                case 3:
                    if (HuPadBtnRep[0] & D_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].r -= 1;
                    }
                    if (HuPadBtnRep[0] & U_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].r += 1;
                    }
                    if (HuPadBtnRep[0] & L_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].r -= 5;
                    }
                    if (HuPadBtnRep[0] & R_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].r += 5;
                    }
                    break;
                case 4:
                    if (HuPadBtnRep[0] & D_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].g -= 1;
                    }
                    if (HuPadBtnRep[0] & U_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].g += 1;
                    }
                    if (HuPadBtnRep[0] & L_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].g -= 5;
                    }
                    if (HuPadBtnRep[0] & R_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].g += 5;
                    }
                    break;
                case 5:
                    if (HuPadBtnRep[0] & D_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].b -= 1;
                    }
                    if (HuPadBtnRep[0] & U_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].b += 1;
                    }
                    if (HuPadBtnRep[0] & L_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].b -= 5;
                    }
                    if (HuPadBtnRep[0] & R_CBUTTONS) {
                        Hu3DLightData->unk02[lightDebugNo].b += 5;
                    }
                    break;
            }
            break;
        case 1:
            if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON)) {
                lightDebugMode = 0;
                printWinData[*dirWin].unk_14 = 0xDF70;
            }
            x = Hu3DLightData->unk02[lightDebugNo].unk04;
            y = Hu3DLightData->unk02[lightDebugNo].unk05;
            z = Hu3DLightData->unk02[lightDebugNo].unk06;
            rotY = -HuPadStkX[0] / 10;
            if (rotY >= 360.0f) {
                rotY -= 360.0f;
            } else if (rotY < 0.0f) {
                rotY += 360.0f;
            }
            rotX = -HuPadStkY[0] / 10;
            if (rotX >= 360.0f) {
                rotX -= 360.0f;
            } else if (rotX < 0.0f) {
                rotX += 360.0f;
            }
            sinX = sindf(rotX);
            cosX = cosdf(rotX);
            sinY = sindf(rotY);
            cosY = cosdf(rotY);
            x = x * cosY - z * sinY;
            y = x * sinX * sinY + y * cosX + z * sinX * cosY;
            z = x * cosX * sinY - y * sinX + z * cosX * cosY;
            Hu3DGLightDirSet(lightDebugNo, x, y, z);
            break;
    }

    printWinData[*colorWin].unk_14 = (lightDebugWinAlpha << 24) | 0x80;
    printWinData[*colorWin].unk_04 = lightDebugWinX0[lightDebugWinPos];
    printWinData[*colorWin].unk_08 = lightDebugWinY0[lightDebugWinPos];
    printWinData[*colorWin].unk_0C = lightDebugWinX1[lightDebugWinPos];
    printWinData[*colorWin].unk_10 = lightDebugWinY1[lightDebugWinPos];
}
