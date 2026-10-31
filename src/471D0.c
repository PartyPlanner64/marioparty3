#include "common.h"
#include "game/hmflight.h"
#include "game/printfunc.h"
#include "input.h"
#include "math.h"
#include "pad.h"
#include "variables.h"

typedef union LightObjWork {
    u32 words[4];
    s16 halfwords[8];
} LightObjWork;

extern omObjData *D_800A1660_main;
extern s16 D_800A1664_main;
extern s16 D_800A1666_main;
extern u8 D_800A1668_main;
extern u8 D_800A1669_main;
extern s8 D_800A166A_main;
extern char *D_800A166C_main[];
extern s16 D_800A1674_main[];
extern s16 D_800A1680_main[];
extern s16 D_800A168C_main[];
extern s16 D_800A1698_main[];
extern s8 D_800B23B0_main;
extern s8 D_800B23B1_main;
extern UnkLightData *D_800CE1D4_main;

void func_80046728_main(omObjData *);

s32 func_800465D0_main(void) {
    return D_800B23B0_main;
}

void func_800465DC_main(s8 arg0) {
    D_800B23B0_main = arg0;
}

s32 func_800465E8_main(void) {
    return D_800B23B1_main;
}

void func_800465F4_main(s8 arg0) {
    D_800B23B1_main = arg0;
}

void func_80046600_main(void) {
    LightObjWork *work;

    D_800A1660_main = omAddObj(0x7FD0, 0, 0, -1, func_80046728_main);
    omSetStatBit(D_800A1660_main, 0xA0);
    work = OM_GET_WORK_PTR(D_800A1660_main, LightObjWork);
    work->halfwords[0] = printWin(14, 14, 306, 34, 0xDF70);
    work->halfwords[4] =
        printWin(D_800A1674_main[D_800A1666_main], D_800A1680_main[D_800A1666_main],
                           D_800A168C_main[D_800A1666_main], D_800A1698_main[D_800A1666_main],
                           (D_800A1668_main << 24) | 0x80);
    D_800A1669_main = 0;
}

void func_800466D8_main(void) {
    omObjData *lightObj = D_800A1660_main;
    LightObjWork *work;

    if (lightObj != NULL) {
        work = OM_GET_WORK_PTR(lightObj, LightObjWork);
        func_8004DEC8_main(work->halfwords[0]);
        func_8004DEC8_main(work->halfwords[4]);
        omDelObj(D_800A1660_main);
        D_800A1660_main = NULL;
    }
}

void func_80046728_main(omObjData *object) {
    s16 *dirWin = &OM_GET_WORK_PTR(D_800A1660_main, LightObjWork)->halfwords[0];
    s16 *colorWin = &OM_GET_WORK_PTR(D_800A1660_main, LightObjWork)->halfwords[4];
    f32 x, y, z;
    f32 rotY, rotX;
    f32 sinX, cosX, sinY, cosY;
    s16 row, col;
    char *statStr;
    u16 button;

    statStr = D_800A166C_main[(D_800CE1D4_main->unk02[D_800A1664_main].stat ^ 1) & 1];
    fontcolor = 14;
    sprintf(D_800D5218_main, "LIGHT%1d DIR%4d,%4d,%4d  STAT %s", D_800A1664_main,
            D_800CE1D4_main->unk02[D_800A1664_main].unk04, D_800CE1D4_main->unk02[D_800A1664_main].unk05,
            D_800CE1D4_main->unk02[D_800A1664_main].unk06, statStr);
    print8(16, 16, D_800D5218_main);
    sprintf(D_800D5218_main, "COLOR    RED %3d GREEN %3d BLUE %3d", D_800CE1D4_main->unk02[D_800A1664_main].r,
            D_800CE1D4_main->unk02[D_800A1664_main].g, D_800CE1D4_main->unk02[D_800A1664_main].b);
    print8(16, 24, D_800D5218_main);

    switch (D_800A1669_main) {
        case 0:
            if ((D_800D5558_main[0] & 0x8000) && D_800A1666_main == 1) {
                D_800CC440_main[*dirWin].unk_14 = 0x7070;
                D_800A1668_main = 0xF0;
                D_800A166A_main = -4;
                D_800A1669_main = 1;
                break;
            }
            D_800A1668_main += D_800A166A_main;
            if (D_800A166A_main < 0) {
                if (D_800A1668_main <= 0x80) {
                    D_800A166A_main = 4;
                }
            } else if (D_800A1668_main >= 0xF0) {
                D_800A166A_main = -4;
            }

            button = D_800D0590_main[0];
            row = D_800A1666_main / 3;
            col = D_800A1666_main % 3;
            if (button & 0x200) {
                if (col == 0) {
                    D_800A1666_main = row * 3 + 2;
                } else {
                    D_800A1666_main--;
                }
            } else if (button & 0x100) {
                if (col == 2) {
                    D_800A1666_main = row * 3;
                } else {
                    D_800A1666_main++;
                }
            } else if (button & 0x800) {
                if (row == 0) {
                    D_800A1666_main = col + 3;
                } else {
                    D_800A1666_main -= 3;
                }
            } else if (button & 0x400) {
                if (row == 1) {
                    D_800A1666_main = col;
                } else {
                    D_800A1666_main += 3;
                }
            }

            switch (D_800A1666_main) {
                case 0:
                    if ((D_800D1244_main[0] & 4) && D_800A1664_main >= 2) {
                        D_800A1664_main--;
                    }
                    if ((D_800D1244_main[0] & 8) && D_800A1664_main < D_800CE1D4_main->unk00) {
                        D_800A1664_main++;
                    }
                    break;
                case 1:
                    break;
                case 2:
                    if (D_800D1244_main[0] & 0x800C) {
                        if (D_800CE1D4_main->unk02[D_800A1664_main].stat & 1) {
                            HmfLightStatSet(D_800A1664_main, 1, 0);
                        } else {
                            HmfLightStatSet(D_800A1664_main, 1, 1);
                        }
                    }
                    break;
                case 3:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->unk02[D_800A1664_main].r -= 1;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->unk02[D_800A1664_main].r += 1;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->unk02[D_800A1664_main].r -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->unk02[D_800A1664_main].r += 5;
                    }
                    break;
                case 4:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->unk02[D_800A1664_main].g -= 1;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->unk02[D_800A1664_main].g += 1;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->unk02[D_800A1664_main].g -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->unk02[D_800A1664_main].g += 5;
                    }
                    break;
                case 5:
                    if (D_800D1244_main[0] & 4) {
                        D_800CE1D4_main->unk02[D_800A1664_main].b -= 1;
                    }
                    if (D_800D1244_main[0] & 8) {
                        D_800CE1D4_main->unk02[D_800A1664_main].b += 1;
                    }
                    if (D_800D1244_main[0] & 2) {
                        D_800CE1D4_main->unk02[D_800A1664_main].b -= 5;
                    }
                    if (D_800D1244_main[0] & 1) {
                        D_800CE1D4_main->unk02[D_800A1664_main].b += 5;
                    }
                    break;
            }
            break;
        case 1:
            if (D_800D5558_main[0] & 0xC000) {
                D_800A1669_main = 0;
                D_800CC440_main[*dirWin].unk_14 = 0xDF70;
            }
            x = D_800CE1D4_main->unk02[D_800A1664_main].unk04;
            y = D_800CE1D4_main->unk02[D_800A1664_main].unk05;
            z = D_800CE1D4_main->unk02[D_800A1664_main].unk06;
            rotY = -D_800CBB6E_main[0] / 10;
            if (rotY >= 360.0f) {
                rotY -= 360.0f;
            } else if (rotY < 0.0f) {
                rotY += 360.0f;
            }
            rotX = -D_800D20A1_main[0] / 10;
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
            HmfLightDirSet(D_800A1664_main, x, y, z);
            break;
    }

    D_800CC440_main[*colorWin].unk_14 = (D_800A1668_main << 24) | 0x80;
    D_800CC440_main[*colorWin].unk_04 = D_800A1674_main[D_800A1666_main];
    D_800CC440_main[*colorWin].unk_08 = D_800A1680_main[D_800A1666_main];
    D_800CC440_main[*colorWin].unk_0C = D_800A168C_main[D_800A1666_main];
    D_800CC440_main[*colorWin].unk_10 = D_800A1698_main[D_800A1666_main];
}
