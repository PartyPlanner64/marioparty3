#include "common.h"
#include "game/printfunc.h"
#include "overlays/opening.h"

void func_80105B64_sldebug(omObjData *); /* extern */
void func_80106254_sldebug(omObjData *); /* extern */
void func_80106124_sldebug(omObjData *arg0);
s32 func_8010612C_sldebug(void);
void func_80106850_sldebug(void);        /* extern */
void func_801068D4_sldebug(omObjData *); /* extern */
void func_80106930_sldebug(omObjData *); /* extern */
extern u16 D_80106960_sldebug;
extern s16 D_8010698C_sldebug;
extern s32 D_80106978_sldebug;
extern s32 D_80106980_sldebug;
extern s32 D_80106964_sldebug;
extern u8 D_80106968_sldebug[];
extern s32 D_8010697C_sldebug;
extern s32 D_80106984_sldebug;
extern s32 D_80106988_sldebug;
extern Vec D_80106C10_sldebug;
extern f32 D_80106C1C_sldebug;
extern Vec D_80106C20_sldebug;
extern Vec D_80106C2C_sldebug;

void func_801059A0_sldebug(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x2D);
    omInitObjMan(0x33, 0xA);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(0x2710, 0, 0, -1, func_801068D4_sldebug);
    HmfLightMaxSet(4);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    D_80106C10_sldebug.x = D_80106C10_sldebug.y = D_80106C10_sldebug.z = 0.0f;
    D_80106C1C_sldebug = 400.0f;
    D_80106C2C_sldebug.x = D_80106C2C_sldebug.z = 0.0f;
    D_80106C2C_sldebug.y = 150.0f;
    gCameraList->fov = 45.0f;
    func_80106850_sldebug();
    omAddObj(0x7D0, 0xA, 0xA, -1, func_80105B64_sldebug);
    omAddObj(0x7D0, 0, 0, -1, func_80106254_sldebug);
    WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
    D_800CD280_main = 1;
    func_80050ABC_main();
    HuAudSeqPlay(8);
}

void func_80105B64_sldebug(omObjData *arg0) {
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
    print8(70, 100, storyNames[D_8010697C_sldebug]);
    print8(70, 110, heroNames[D_80106984_sldebug]);
    print8(70, 120, difficultyNames[D_80106988_sldebug]);
    print8(70, 130, "WLUIGILAND & REVKUNMAP ENABLE");
    print8(70, 140, "EXIT");
    if (D_800D0590_main[0] & U_JPAD) {
        HuAudFXPlay(1);
        D_80106978_sldebug--;
        if (D_80106978_sldebug < 0) {
            D_80106978_sldebug = 6;
        }
    } else if (D_800D0590_main[0] & D_JPAD) {
        HuAudFXPlay(1);
        D_80106978_sldebug++;
        if (D_80106978_sldebug >= 7) {
            D_80106978_sldebug = 0;
        }
    } else if (D_800D0590_main[0] & L_JPAD) {
        switch (D_80106978_sldebug) {
            case 2:
                HuAudFXPlay(1);
                D_8010697C_sldebug--;
                if (D_8010697C_sldebug < 0) {
                    D_8010697C_sldebug = 12;
                }
                break;
            case 3:
                HuAudFXPlay(1);
                D_80106984_sldebug--;
                if (D_80106984_sldebug < 0) {
                    D_80106984_sldebug = 5;
                }
                break;
            case 4:
                HuAudFXPlay(1);
                D_80106988_sldebug--;
                if (D_80106988_sldebug < 0) {
                    D_80106988_sldebug = 3;
                }
                break;
        }
    } else if (D_800D0590_main[0] & R_JPAD) {
        switch (D_80106978_sldebug) {
            case 2:
                HuAudFXPlay(1);
                D_8010697C_sldebug++;
                if (D_8010697C_sldebug >= 13) {
                    D_8010697C_sldebug = 0;
                }
                break;
            case 3:
                HuAudFXPlay(1);
                D_80106984_sldebug++;
                if (D_80106984_sldebug >= 6) {
                    D_80106984_sldebug = 0;
                }
                break;
            case 4:
                HuAudFXPlay(1);
                D_80106988_sldebug++;
                if (D_80106988_sldebug >= 4) {
                    D_80106988_sldebug = 0;
                }
                break;
        }
    } else if (D_800D5558_main[0] & A_BUTTON) {
        if (func_8010612C_sldebug() != 0) {
            if (D_80106980_sldebug != 0) {
                GwStory.unk0 = D_8010697C_sldebug;
                for (i = 0; i < 13; i++) {
                    if (i < D_8010697C_sldebug) {
                        GwStory.progress.storyProgress[i] = 4;
                    } else {
                        GwStory.progress.storyProgress[i] = 0;
                    }
                }
                if (D_8010697C_sldebug == 12) {
                    GwStory.progress.fields.unkF = 4;
                }
                GwStory.unk2 = D_80106988_sldebug;
                GwStory.unk1 = D_80106984_sldebug;
                _ClearFlag(0x28);
                _SetFlag(0x18);
                GwSystem.playMode = 4;
                if (D_80106968_sldebug[D_8010697C_sldebug] == 0) {
                    D_80106964_sldebug = 2;
                    GwSystem.playMode = 5;
                } else if (D_80106968_sldebug[D_8010697C_sldebug] == 1) {
                    D_80106964_sldebug = 0x4000;
                    GwSystem.playMode |= 2;
                } else {
                    D_80106964_sldebug = 4;
                }
                func_8005035C_main(1);
            } else {
                SLCommonSet(1);
            }
            D_80106960_sldebug = 1;
            arg0->func = func_80106124_sldebug;
        }
        return;
    }
    print8(60, D_80106978_sldebug * 10 + 80, ">");
}

void func_80106124_sldebug(omObjData *arg0) {
}

s32 func_8010612C_sldebug(void) {
    s16 i;

    HuAudFXPlay(2);
    switch (D_80106978_sldebug) {
        case 0:
            _SetFlag(0x1D);
            if ((u16)D_800CDA7C_main[0] & A_BUTTON) {
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
            D_80106980_sldebug = 1;
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

void func_80106254_sldebug(omObjData *arg0) {
    char text[256];
    f32 speed;
    f32 zoom;
    f32 xRot;
    f32 yRot;
    f32 z;
    f32 scale;
    f32 backSpeed;
    s8 stick;

    if (D_800D5558_main[0] & R_TRIG) {
        D_8010698C_sldebug ^= 1;
    }
    if (D_800CDA7C_main[0] & START_BUTTON) {
        func_80106850_sldebug();
    }
    if (D_800CDA7C_main[0] & U_CBUTTONS) {
        if (D_800CDA7C_main[0] & Z_TRIG) {
            zoom = CZoom + 30.0f;
        } else {
            zoom = CZoom + 10.0f;
        }
        CZoom = zoom;
    }
    if ((D_800CDA7C_main[0] & D_CBUTTONS) && CZoom - 10.0f != 0.0f) {
        if (D_800CDA7C_main[0] & Z_TRIG) {
            CZoom = CZoom - 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    xRot = D_80106C20_sldebug.x;
    yRot = D_80106C20_sldebug.y;
    if (D_800CDA7C_main[0] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    yRot += (-D_800CBB6E_main[0] / 30) * speed;
    if (yRot >= 360.0f) {
        yRot -= 360.0f;
    } else if (yRot < 0.0f) {
        yRot += 360.0f;
    }
    D_80106C20_sldebug.y = yRot;
    stick = D_800D20A1_main[0] / 30;
    xRot += stick * speed;
    if (xRot >= 360.0f) {
        xRot -= 360.0f;
    } else if (xRot < 0.0f) {
        xRot += 360.0f;
    }
    D_80106C20_sldebug.x = xRot;
    CRot.x = (s16)D_80106C20_sldebug.x;
    CRot.y = (s16)D_80106C20_sldebug.y;
    if (D_800CDA7C_main[0] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (D_800CDA7C_main[0] & U_JPAD) {
        Center.x += sindf(yRot) * sindf(xRot) * (backSpeed = -speed);
        Center.y = cosdf(xRot) * backSpeed + Center.y;
        Center.z = cosdf(yRot) * sindf(xRot) * backSpeed + Center.z;
    } else if (D_800CDA7C_main[0] & D_JPAD) {
        Center.x += sindf(yRot) * sindf(xRot) * speed;
        Center.y = cosdf(xRot) * speed + Center.y;
        Center.z = cosdf(yRot) * sindf(xRot) * speed + Center.z;
    } else if (D_800CDA7C_main[0] & L_JPAD) {
        xRot = gCameraList->pos.z - Center.z;
        z = -(gCameraList->pos.x - Center.x);
        scale = 1.0f / HuSqrtf(xRot * xRot + z * z);
        Center.x += xRot * scale * speed;
        Center.y += 0.0f;
        Center.z += z * scale * speed;
    } else if (D_800CDA7C_main[0] & R_JPAD) {
        xRot = -(gCameraList->pos.z - Center.z);
        z = gCameraList->pos.x - Center.x;
        scale = 1.0f / HuSqrtf(xRot * xRot + z * z);
        Center.x += xRot * scale * speed;
        Center.y += 0.0f;
        Center.z += z * scale * speed;
    }
    if (D_8010698C_sldebug != 0) {
        sprintf(text, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, text);
        sprintf(text, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, text);
        sprintf(text, "CZOOM %4.1f", CZoom);
        print8(32, 200, text);
    }
}

void func_80106850_sldebug(void) {
    CRot = D_80106C10_sldebug;
    D_80106C20_sldebug = CRot;
    CZoom = D_80106C1C_sldebug;
    Center = D_80106C2C_sldebug;
}

void func_801068D4_sldebug(omObjData *arg0) {
    if ((D_80106960_sldebug != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = func_80106930_sldebug;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106930_sldebug(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlGotoEx(0x58, 0, 0x81);
    }
}
