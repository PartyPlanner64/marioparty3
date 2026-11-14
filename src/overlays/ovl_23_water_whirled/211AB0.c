#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "overlays/minigame.h"

extern u8 D_800D2008_main;
extern f32 D_800D5210_main;
extern u8 D_800D6A90_main;

extern Vec D_8010A160_water_whirled[];
extern f32 D_8010A190_water_whirled[4];
extern Vec D_8010A1A0_water_whirled[];
extern Vec D_8010A1D0_water_whirled[];
extern Vec D_8010A200_water_whirled[];
extern f32 D_8010A230_water_whirled[4];
extern s32 D_8010A240_water_whirled[4];
extern f32 D_8010A250_water_whirled;
extern f32 D_8010A254_water_whirled;
extern f32 D_8010A258_water_whirled;
extern f32 D_8010A25C_water_whirled;
extern f32 D_8010A260_water_whirled;
extern f32 D_8010A264_water_whirled;
extern f32 D_8010A268_water_whirled;
extern f32 D_8010A26C_water_whirled;
extern s32 D_8010A280_water_whirled;
extern s32 D_8010A284_water_whirled;
extern s32 D_8010A270_water_whirled[4];
extern s32 D_8010A288_water_whirled;
extern s32 D_8010A28C_water_whirled[4];
extern s32 D_8010A29C_water_whirled[4];
extern D_80111B50_vine_with_me_Struct D_8010A2AC_water_whirled;
extern Vec D_8010A2D4_water_whirled;
extern f32 D_8010A2E0_water_whirled[4];
extern s8 D_8010A2F0_water_whirled[4];
extern s16 D_8010A2F4_water_whirled;
extern s16 D_8010A2F6_water_whirled;
extern s16 D_8010A2F8_water_whirled;
extern s32 D_8010A2FC_water_whirled[4];
extern s16 D_8010A30C_water_whirled[][20];
extern s32 D_8010A3AC_water_whirled[];
extern s32 D_8010A3BC_water_whirled[];
extern f32 D_8010A3CC_water_whirled[4];
extern s32 D_8010A3DC_water_whirled[4];
extern s32 D_8010A3EC_water_whirled[];
extern f32 D_8010A3FC_water_whirled[4];
extern f32 D_8010A40C_water_whirled[4];
extern f32 D_8010A41C_water_whirled[];
extern s32 D_8010A42C_water_whirled[4];
extern s32 D_8010A43C_water_whirled[4];
extern Vec D_8010A44C_water_whirled[][3];
extern Vec D_8010A560_water_whirled[4][6];
extern f32 D_8010A680_water_whirled[4][6];
extern Vec D_8010A6E0_water_whirled[4][6];
extern f32 D_8010A800_water_whirled[4][6];
extern Vec2f D_8010A860_water_whirled;
extern s32 D_8010AC40_water_whirled;
extern s32 D_8010AC44_water_whirled;
extern Vec D_8010A880_water_whirled[][20];
extern s32 D_8010AC48_water_whirled[4];
extern s32 D_8010AC58_water_whirled[4];
extern s32 D_8010AC68_water_whirled[4];
extern s32 D_8010AC78_water_whirled[4];

void func_80105EA0_water_whirled(omObjData *object);
void func_8010616C_water_whirled(omObjData *object);
void func_80106308_water_whirled(omObjData *object);
void func_80106680_water_whirled(void);
void func_8010698C_water_whirled(void);
void func_80106A58_water_whirled(void);
void func_80106DB8_water_whirled(omObjData *object);
void func_80105D64_water_whirled(void);
f32 func_801061E4_water_whirled(f32 x, f32 z);
void func_801071BC_water_whirled(omObjData *object);
void func_8010750C_water_whirled(omObjData *object, u16 player);
void func_80107880_water_whirled(omObjData *object);
void func_8010789C_water_whirled(omObjData *object);
void func_801078B8_water_whirled(omObjData *object);
void func_801078D4_water_whirled(omObjData *object);
void func_80107F08_water_whirled(omObjData *object);
void func_8010860C_water_whirled(Vec *origin, Vec *p, Vec *q, Vec *out);
void func_80108898_water_whirled(omObjData *object, Vec *pos);
void func_801089C0_water_whirled(omObjData *object, f32 x, f32 z);
void func_80109340_water_whirled(s16 player, s16 bank);
void func_80109458_water_whirled(s16 player);
void func_8010956C_water_whirled(s16 player);
s32 func_8010960C_water_whirled(omObjData *object);
void func_80108DF8_water_whirled(omObjData *object);
void func_801086A0_water_whirled(omObjData *object, f32 x, f32 z);
f32 func_80108B98_water_whirled(omObjData *object, f32 x, f32 y, f32 z);
void func_801096BC_water_whirled(omObjData *object);
void func_801098AC_water_whirled(omObjData *object);
void func_80109E2C_water_whirled(omObjData *object);

void func_801059A0_water_whirled(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800D5210_main = 30000.0f;
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 16000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_801071BC_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_80107880_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_8010789C_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078B8_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078D4_water_whirled);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(4, 0, 0, -1, func_80105EA0_water_whirled), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(100, 0, 0, -1, func_80108DF8_water_whirled), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_8010A2AC_water_whirled);
    D_800EB930_minigame = 50;
    D_800EB932_minigame = 60;
    func_800EA0FC_minigame(0, 0.0f, D_8010A190_water_whirled[0]);
    func_800EA0FC_minigame(1, 0.0f, D_8010A190_water_whirled[1]);
    func_800EA0FC_minigame(2, 0.0f, D_8010A190_water_whirled[2]);
    func_800EA0FC_minigame(3, 0.0f, D_8010A190_water_whirled[3]);
    Hu3DGLightDirSet(1, D_8010A2D4_water_whirled.x, D_8010A2D4_water_whirled.y, D_8010A2D4_water_whirled.z);
}

void func_80105D64_water_whirled(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    pos.y = -sindf(rotX) * CZoom + Center.y;
    pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rotY) * sindf(rotX);
    up.y = cosdf(rotX);
    up.z = cosdf(rotY) * sindf(rotX);
    Hu3DCameraPosSetV(0, &pos, &at, &up);
}

void func_80105EA0_water_whirled(omObjData *object) {
    Vec worldPos;
    Vec2f screenPos;
    f32 min;
    f32 max;
    s32 i;

    if (func_800E6E8C_minigame() == 2) {
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].x < min) {
                min = D_8010A1D0_water_whirled[i].x;
            }
            if (max < D_8010A1D0_water_whirled[i].x) {
                max = D_8010A1D0_water_whirled[i].x;
            }
        }
        Center.x = (min + max) * 0.5f;
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].z < min) {
                min = D_8010A1D0_water_whirled[i].z;
            }
            if (max < D_8010A1D0_water_whirled[i].z) {
                max = D_8010A1D0_water_whirled[i].z;
            }
        }
        Center.z = (min + max) * 0.5f;
        CZoom = 12000.0f;
        func_80105D64_water_whirled();
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            worldPos.x = D_8010A1D0_water_whirled[i].x;
            worldPos.y = 0.0f;
            worldPos.z = D_8010A1D0_water_whirled[i].z;
            func_80012B14_main(0, &worldPos, &screenPos);
            screenPos.x = fabsf(screenPos.x - 160.0f);
            screenPos.y = fabsf(screenPos.y - 120.0f);
            screenPos.x = (screenPos.x + 40.0f) / 160.0f;
            screenPos.y = (screenPos.y + 20.0f) / 120.0f;
            if (max < screenPos.x) {
                max = screenPos.x;
            }
            if (max < screenPos.y) {
                max = screenPos.y;
            }
        }
        CZoom = max * 12000.0f;
        if (CZoom < 7000.0f) {
            CZoom = 7000.0f;
        }
    }
}

void func_8010616C_water_whirled(omObjData *object) {
    if (D_8010A288_water_whirled != 0) {
        D_8010A288_water_whirled = D_8010A288_water_whirled * 0.75f;
        HuAudFXVolSet(D_8010A284_water_whirled, D_8010A288_water_whirled);
    }
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

f32 func_801061E4_water_whirled(f32 x, f32 z) {
    f32 wave;

    wave = sindf((D_8010A250_water_whirled / D_8010A254_water_whirled -
                  HuSqrtf(x * x + z * z) / D_8010A258_water_whirled) *
                 (M_PI * 2)) *
           D_8010A25C_water_whirled;
    x += 8000.0f;
    z += 5000.0f;
    wave += sindf((D_8010A260_water_whirled / D_8010A264_water_whirled -
                   HuSqrtf(x * x + z * z) / D_8010A268_water_whirled) *
                  (M_PI * 2)) *
            D_8010A26C_water_whirled;
    return wave / 2.0f;
}

void func_80106308_water_whirled(omObjData *object) {
    HmfData *hmf;
    Vtx *vtx;
    Vtx *src;
    f32 x, z;
    f32 height;
    s32 i;

    hmf = Hu3DData[object->model[1]].hmf;
    vtx = hmf->unk44[D_800D2008_main];
    src = hmf->unk40;
    for (i = 0; i < hmf->unk18; vtx++, i++, src++) {
        x = src->v.ob[0];
        z = src->v.ob[2];
        height = sindf((D_8010A250_water_whirled / D_8010A254_water_whirled -
                        HuSqrtf(x * x + z * z) / D_8010A258_water_whirled) *
                       (2 * M_PI)) *
                 D_8010A25C_water_whirled;
        x += 8000.0f;
        z += 5000.0;
        height = (height + sindf((D_8010A260_water_whirled / D_8010A264_water_whirled -
                                  HuSqrtf(x * x + z * z) / D_8010A268_water_whirled) *
                                 (2 * M_PI)) *
                               D_8010A26C_water_whirled) /
                 2.0f;
        vtx->v.ob[1] = height;
        if (height > 0.0) {
            height = 256.0f - height;
            vtx->v.cn[1] = vtx->v.cn[0] = 170;
            vtx->v.cn[2] = height;
        } else {
            height = 175.0f - height;
            if (height > 255.0f) {
                height = 255.0f;
            }
            vtx->v.cn[0] = height;
            vtx->v.cn[1] = height;
            vtx->v.cn[2] = 255;
        }
    }
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010A250_water_whirled += 0.11f;
        D_8010A260_water_whirled += 0.09f;
    }
}

void func_80106680_water_whirled(void) {
    s32 time = func_800E6E9C_minigame();

    if (func_800E6E8C_minigame() == 0) {
        if (time < 15) {
            CRot.y = 100.0f;
            CRot.x = 350.0f;
            Center.z = 300.0f;
            Center.y = 0.0f;
            CZoom = 2500.0f;
            return;
        }
        if (time < 75.0) {
            Center.z += 10.0f;
            if (Center.z > 1000.0f) {
                Center.z = 1000.0f;
            }
            if (time == 30) {
                HuAudSeqPlay(0x6D);
            }
            return;
        }
        if (time < 90) {
            return;
        }
    }
    D_8010A2D4_water_whirled.x -= 8.0f;
    D_8010A2D4_water_whirled.z += 3.0f;
    if (D_8010A2D4_water_whirled.x < -85.0f) {
        D_8010A2D4_water_whirled.x = -85.0f;
    }
    if (D_8010A2D4_water_whirled.z > 64.0f) {
        D_8010A2D4_water_whirled.z = 64.0f;
    }
    Hu3DGLightDirSet(1, D_8010A2D4_water_whirled.x, D_8010A2D4_water_whirled.y, D_8010A2D4_water_whirled.z);
    CRot.x *= 0.995f;
    CRot.y -= 2.0f;
    CZoom *= 1.025f;
    Center.z *= 0.98f;
    Center.y += 5.0f;
    if (CRot.x < 319.0f) {
        CRot.x = 319.0f;
    }
    if (CRot.y < 1.0f) {
        CRot.y = 0.0f;
    }
    if (CZoom > 7000.0f) {
        CZoom = 7000.0f;
    }
    if (Center.z < 700.0f) {
        Center.z = 700.0f;
    }
}

void func_8010698C_water_whirled(void) {
    omObjData *target;

    if (D_8010A280_water_whirled != -1) {
        target = D_800EC598_minigame[D_8010A280_water_whirled];
        Center.x -= (Center.x - target->trans.x) * 0.25f;
        Center.z -= (Center.z - target->trans.z) * 0.25f;
        Center.y -= (Center.y - target->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

void func_80106A58_water_whirled(void) {
    s32 order[4];
    f32 progress[4];
    f32 x;
    f32 z;
    f32 angle;
    f32 tempProgress;
    s32 tempOrder;
    s32 swapped;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        progress[i] = D_8010A240_water_whirled[i] * 1500.0f;
        x = D_800EC598_minigame[i]->trans.x;
        z = D_800EC598_minigame[i]->trans.z;
        if (x > 0.0f) {
            if (z > 0.0f) {
                if (x > 1000.0f) {
                    progress[i] += atan2df(x - 1000.0f, z) / 90.0f * 500.0f + 1000.0f;
                } else {
                    progress[i] += x;
                }
            } else {
                if (x > 1000.0f) {
                    progress[i] += (atan2df(x - 1000.0f, z) - 90.0f) / 90.0f * 500.0f;
                } else {
                    progress[i] += 1000.0f - x + 500.0f;
                }
            }
        } else {
            angle = func_800202A8_main(atan2df(x + 1000.0f, z));
            if (z > 0.0f) {
                if (x < -1000.0f) {
                    progress[i] += (angle - 270.0f) / 90.0f * 500.0f;
                } else {
                    progress[i] += x + 1000.0f + 500.0f;
                }
            } else {
                if (x < -1000.0f) {
                    progress[i] += (angle - 180.0f) / 90.0f * 500.0f + 1000.0f;
                } else {
                    progress[i] -= x;
                }
            }
        }
        order[i] = i;
    }
    do {
        swapped = FALSE;
        for (i = 0; i < 3; i++) {
            for (j = i + 1; j < 4; j++) {
                // Redundant with the loop condition, but required to match.
                if (j == 4) {
                    break;
                }
                if (progress[i] > progress[j]) {
                    tempProgress = progress[j];
                    progress[j] = progress[i];
                    progress[i] = tempProgress;
                    tempOrder = order[j];
                    order[j] = order[i];
                    order[i] = tempOrder;
                    swapped = TRUE;
                }
            }
        }
    } while (swapped);
    for (i = 0; i < 4; i++) {
        D_8010A190_water_whirled[order[i]] = D_8010A2E0_water_whirled[i];
    }
}

void func_80106DB8_water_whirled(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work;
    s32 time;
    s32 i;

    func_80106308_water_whirled(object);
    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    time = func_800E6E9C_minigame();
    switch (func_800E6F40_minigame()) {
        case 0:
            if (time == 1) {
                D_8010A28C_water_whirled[0] = PlayerFXPlay(0x41A, 0);
                D_8010A28C_water_whirled[1] = PlayerFXPlay(0x41A, 1);
                D_8010A28C_water_whirled[2] = PlayerFXPlay(0x41A, 2);
                D_8010A28C_water_whirled[3] = PlayerFXPlay(0x41A, 3);
                HuAudFXPlay(0x424);
            }
        case 1:
            func_80106680_water_whirled();
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_8010A270_water_whirled[i] == 5) {
                    D_8010A280_water_whirled = i;
                    func_800E6F0C_minigame(3);
                    D_8010A2AC_water_whirled.unk18[0] = D_8010A280_water_whirled;
                    D_8010A2AC_water_whirled.unk06 = 0;
                    work = D_800EC598_minigame[D_8010A280_water_whirled]->data;
                    GwPlayer[work->unk59].bonusCoin += 10;
                    break;
                }
            }
            if (D_8010A284_water_whirled != 0) {
                D_8010A288_water_whirled += 7;
                if (D_8010A288_water_whirled > 110) {
                    D_8010A288_water_whirled = 110;
                }
            }
            func_80106A58_water_whirled();
            break;
        case 3:
            if (time == 15.0) {
                func_8004AEF0_main(D_8010A28C_water_whirled[0], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[1], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[2], 30);
                func_8004AEF0_main(D_8010A28C_water_whirled[3], 30);
                D_8010A28C_water_whirled[0] = -1;
                D_8010A28C_water_whirled[1] = -1;
                D_8010A28C_water_whirled[2] = -1;
                D_8010A28C_water_whirled[3] = -1;
            }
            if (D_8010A280_water_whirled == -1) {
                D_8010A2AC_water_whirled.unk06 = 4;
            } else {
                D_8010A288_water_whirled += 3;
                if (D_8010A288_water_whirled > 127) {
                    D_8010A288_water_whirled = 127;
                }
            }
            func_8010698C_water_whirled();
            break;
        case 4:
            if (D_8010A280_water_whirled != -1 && D_800EB934_minigame == 1) {
                func_8004AC98_main(GwPlayer[D_8010A280_water_whirled].chr + 0x290, D_8010A280_water_whirled);
            }
            if (time >= 150) {
                D_8010A288_water_whirled -= 4;
                if (D_8010A288_water_whirled < 0) {
                    D_8010A288_water_whirled = 0;
                }
            }
            func_8010698C_water_whirled();
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_8010616C_water_whirled;
            break;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        work = D_800EC598_minigame[i]->data;
        work->unk60 = CRot.y;
    }
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        object->func = func_8010616C_water_whirled;
    }
    if (D_8010A284_water_whirled != 0) {
        HuAudFXVolSet(D_8010A284_water_whirled, D_8010A288_water_whirled);
    }
}

void func_801071BC_water_whirled(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = func_8000B0A0_main(0x440000, 0x4C9);
    object->model[1] = func_8000B0A0_main(0x440001, 0x4C9);
    object->model[2] = func_8000B0A0_main(0x440003, 0x8C9);
    object->model[3] = Hu3DModelLink(object->model[2]);
    object->model[4] = func_8000B0A0_main(0x440004, 0x8C9);
    object->model[5] = Hu3DModelLink(object->model[4]);
    object->model[6] = func_8000B0A0_main(0x440005, 0x8C9);
    object->model[7] = Hu3DModelLink(object->model[6]);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    object->func = func_80106DB8_water_whirled;
    work->unk03 = 1;
    CZoom = 12000.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    func_800E147C_minigame(object);
    func_800E1370_minigame(object, 1, 0.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 25.0f);
    work->unk04 = 0;
    func_8001C2FC_main(object->model[1], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C954_main(object->model[1]);
    Hu3DModelPosSet(object->model[2], -2400.0f, 0.0f, -1400.0f);
    Hu3DModelPosSet(object->model[3], 2700.0f, 0.0f, -900.0f);
    Hu3DModelPosSet(object->model[4], 1000.0f, 300.0f, -1950.0f);
    Hu3DModelPosSet(object->model[5], -2400.0f, 500.0f, -2000.0f);
    Hu3DModelPosSet(object->model[6], -1300.0f, 500.0f, -2050.0f);
    Hu3DModelPosSet(object->model[7], 2000.0f, 100.0f, -2500.0f);
    func_8001C814_main(object->model[2], 2, 2);
    func_8001C814_main(object->model[3], 2, 2);
    func_8001C814_main(object->model[4], 2, 2);
    func_8001C814_main(object->model[5], 2, 2);
    func_8001C814_main(object->model[6], 2, 2);
    func_8001C814_main(object->model[7], 2, 2);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_8010750C_water_whirled(omObjData *object, u16 player) {
    func_800E1BA8_minigame_ObjData *work;
    s32 i;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    work = object->data;
    object->model[0] = func_8000B108_main((GwPlayer[player].chr + 9) | 0x440000, 0x6D9);
    work->unk57 = GwPlayer[player].pad;
    object->func = func_80107F08_water_whirled;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unk8C = 65536.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unk60 = 0.0f;
    func_800E1328_minigame(object, 100.0f);
    func_800E1334_minigame(object, 150.0f);
    func_800E1340_minigame(object, 20.0f);
    func_800E134C_minigame(object, 30.0f);
    func_800E12EC_minigame(object, 1000.0f);
    work->unk9C = work->unkA0 = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unkC3 = -1;
    work->unkC4 = -1;
    work->unkAC = work->unkB0 = 1.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.1f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (D_8010A2F4_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F4_water_whirled = func_8000B108_main(0x440006, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F4_water_whirled);
            }
        } else if (i == 4 || i == 1) {
            if (D_8010A2F6_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F6_water_whirled = func_8000B108_main(0x440007, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F6_water_whirled);
            }
        } else {
            if (D_8010A2F8_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F8_water_whirled = func_8000B108_main(0x440008, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F8_water_whirled);
            }
        }
        func_8001C2FC_main(object->model[i + 1], 0x70000000, 0x70000000);
    }
    work = object->data;
    work->unk3C = 90.0f;
    func_800E149C_minigame(object, 0, 2);
    do {
        i = rand8() & 3;
    } while (D_8010A2F0_water_whirled[i] != -1);
    D_8010A2F0_water_whirled[i] = player;
    object->trans.x = D_8010A160_water_whirled[i].x;
    object->trans.y = D_8010A160_water_whirled[i].y;
    object->trans.z = D_8010A160_water_whirled[i].z;
}

void func_80107880_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 0);
}

void func_8010789C_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 1);
}

void func_801078B8_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 2);
}

void func_801078D4_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 3);
}

void func_801078F0_water_whirled(omObjData *object, f32 speed) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    s32 player = work->unk59;
    f32 angle = work->unk3C;
    f32 offset;
    f32 backAngle;
    f32 scale;
    s32 idx;
    s32 i;

    idx = D_8010A2FC_water_whirled[player] + 1;
    idx = (idx != 6) ? idx : 0;
    D_8010A2FC_water_whirled[player] = idx;
    D_8010A800_water_whirled[player][idx] = 1.0f;
    D_8010A680_water_whirled[player][idx] = speed * 10.0f;
    offset = (rand8() - 128) / 4;
    D_8010A560_water_whirled[player][idx].x =
        sindf(angle + 180.0f) * 75.0f + object->trans.x + sindf(angle + 90.0f) + offset;
    D_8010A560_water_whirled[player][idx].y = object->trans.y;
    D_8010A560_water_whirled[player][idx].z =
        cosdf(angle + 180.0f) * 75.0f + object->trans.z + sindf(angle + 90.0f) + offset;
    offset = (rand8() - 128) / 4;
    backAngle = angle + 180.0f + offset;
    D_8010A6E0_water_whirled[player][idx].x = sindf(backAngle);
    D_8010A6E0_water_whirled[player][idx].z = cosdf(backAngle);
    for (i = 0; i < 6; i++) {
        if (D_8010A680_water_whirled[player][i] > 0.0f) {
            D_8010A560_water_whirled[player][i].x +=
                D_8010A6E0_water_whirled[player][i].x * D_8010A680_water_whirled[player][i] * speed;
            D_8010A560_water_whirled[player][i].y -= 20.0f;
            D_8010A560_water_whirled[player][i].z +=
                D_8010A6E0_water_whirled[player][i].z * D_8010A680_water_whirled[player][i] * speed;
            Hu3DModelPosSet(object->model[i + 1], D_8010A560_water_whirled[player][i].x,
                            D_8010A560_water_whirled[player][i].y, D_8010A560_water_whirled[player][i].z);
            D_8010A800_water_whirled[player][i] *= 1.3f;
            scale = speed * D_8010A800_water_whirled[player][i];
            Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
            func_8001C258_main(object->model[i + 1], 4, 0);
        } else {
            func_8001C258_main(object->model[i + 1], 4, 4);
        }
    }
}

s32 func_80107D18_water_whirled(s32 index, s16 value) {
    s32 sum;
    u8 i;

    D_8010A30C_water_whirled[index][D_8010A3BC_water_whirled[index]] = value;
    if (++D_8010A3BC_water_whirled[index] >= 20) {
        D_8010A3BC_water_whirled[index] = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += D_8010A30C_water_whirled[index][i];
    }
    return sum / 20;
}

void func_80107DD4_water_whirled(s32 index, f32 unused, Vec *out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    D_8010A880_water_whirled[index][D_8010A3AC_water_whirled[index]].x = D_8010A1A0_water_whirled[index].x;
    D_8010A880_water_whirled[index][D_8010A3AC_water_whirled[index]].z = D_8010A1A0_water_whirled[index].z;
    if (++D_8010A3AC_water_whirled[index] >= 20) {
        D_8010A3AC_water_whirled[index] = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += D_8010A880_water_whirled[index][i].x;
        out->z += D_8010A880_water_whirled[index][i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

void func_80107F08_water_whirled(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    s32 player;
    s32 pad;
    s32 mode;
    f32 speed;
    f32 x;
    f32 y;
    f32 z;
    f32 turn;
    f32 stickAvg;
    f32 dist;
    f32 scale;
    s16 stickX;
    s16 stickY;
    Vec vel;
    Vec drift;

    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
    player = work->unk59;
    pad = work->unk57;
    speed = work->unk40;
    D_8010A1D0_water_whirled[player].x = x = object->trans.x;
    D_8010A1D0_water_whirled[player].y = y = object->trans.y;
    D_8010A1D0_water_whirled[player].z = z = object->trans.z;
    D_8010AC40_water_whirled = (u16)D_800CDA7C_main[pad];
    D_8010AC44_water_whirled = D_800CBB6E_main[pad];
    D_800CBB6E_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    mode = func_800E6E8C_minigame();
    if (mode >= 2) {
        func_801098AC_water_whirled(object);
        stickX = D_8010AC44_water_whirled;
        stickY = 0;
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        func_800E2308_minigame(&stickX, &stickY);
    } else {
        stickY = 0;
        stickX = 0;
        D_8010AC40_water_whirled = 0;
    }
    if (D_8010AC40_water_whirled & 0x8000) {
        if (speed == 0.0f) {
            speed = 1.0f;
        }
        speed *= 1.08f;
        D_8010A3CC_water_whirled[player] *= 1.1f;
    } else {
        speed *= 0.98f;
        D_8010A3CC_water_whirled[player] *= 0.9f;
    }
    stickAvg = func_80107D18_water_whirled(player, stickX);
    turn = stickAvg / 15.0f;
    if (speed < 1.0f) {
        speed = 0.0f;
    }
    if (D_8010A190_water_whirled[player] < speed) {
        speed = D_8010A190_water_whirled[player];
    }
    if (D_8010A3CC_water_whirled[player] < 0.05f) {
        D_8010A3CC_water_whirled[player] = 0.05f;
    }
    if (1.0f < D_8010A3CC_water_whirled[player]) {
        D_8010A3CC_water_whirled[player] = 1.0f;
    }
    if (D_8010A28C_water_whirled[player] != -1 && (D_8010A3DC_water_whirled[player] & 1)) {
        HuAudFXPitchSet((s16)D_8010A28C_water_whirled[player],
                        (s16)(D_8010A3CC_water_whirled[player] * 400.0f + -400.0f));
        HuAudFXVolSet(D_8010A28C_water_whirled[player], D_8010A3CC_water_whirled[player] * 43.0f + 84.0f);
    }
    D_8010A3DC_water_whirled[player]++;
    work->unk40 = speed;
    vel.x = sindf(work->unk3C) * (speed * D_8010A3CC_water_whirled[player]);
    vel.y = 0.0f;
    vel.z = cosdf(work->unk3C) * (speed * D_8010A3CC_water_whirled[player]);
    work->unk3C = func_800202A8_main(work->unk3C - turn);
    func_80107DD4_water_whirled(player, speed, &drift);
    drift.x += vel.x;
    drift.z += vel.z;
    dist = HuSqrtf(drift.x * drift.x + drift.z * drift.z);
    if (speed < dist) {
        scale = speed / dist;
        drift.x *= scale;
        drift.z *= scale;
    }
    x += D_8010A200_water_whirled[player].x * D_8010A230_water_whirled[player] + drift.x;
    z += D_8010A200_water_whirled[player].z * D_8010A230_water_whirled[player] + drift.z;
    y = func_80108B98_water_whirled(object, x, 0.0f, z);
    D_8010A1A0_water_whirled[player].x = x - D_8010A1D0_water_whirled[player].x;
    D_8010A1A0_water_whirled[player].y = 0.0f;
    D_8010A1A0_water_whirled[player].z = z - D_8010A1D0_water_whirled[player].z;
    x += D_800EBE2C_minigame;
    z += D_800EC5D8_minigame;
    func_801086A0_water_whirled(object, x, z);
    speed = work->unk40;
    object->trans.x -= D_8010A3CC_water_whirled[player] * 50.0f;
    func_80088910_main(Hu3DData[object->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
    func_800E17D4_minigame(object, x, y - 40.0f, z);
    func_801078F0_water_whirled(object, D_8010A3CC_water_whirled[player]);
    if (D_8010A230_water_whirled[player] != 0.0f) {
        if ((D_8010A230_water_whirled[player] *= 0.9f) < 1.0f) {
            D_8010A230_water_whirled[player] = 0.0f;
        }
    }
    D_8010A2AC_water_whirled.unk08[player] = speed;
    func_801096BC_water_whirled(object);
    func_80109E2C_water_whirled(object);
    D_800CDA7C_main[pad] = D_8010AC40_water_whirled;
    D_800CBB6E_main[pad] = D_8010AC44_water_whirled;
}

void func_8010860C_water_whirled(Vec *origin, Vec *p, Vec *q, Vec *out) {
    f32 ax = p->x - origin->x;
    f32 ay = p->y - origin->y;
    f32 az = p->z - origin->z;
    f32 bx = q->x - origin->x;
    f32 by = q->y - origin->y;
    f32 bz = q->z - origin->z;

    out->x = ay * bz - az * by;
    out->y = az * bx - ax * bz;
    out->z = ax * by - ay * bx;
    func_800202FC_main(out);
}

void func_801086A0_water_whirled(omObjData *object, f32 x, f32 z) {
    func_800E1BA8_minigame_ObjData *work;
    Vec a;
    Vec b;
    Vec c;
    Vec normal;

    a.x = x;
    a.y = func_801061E4_water_whirled(x, z);
    a.z = z;
    b.x = x + sindf(0.0f) * 10.0f;
    b.z = z + cosdf(0.0f) * 10.0f;
    b.y = func_801061E4_water_whirled(b.x, b.z);
    c.x = x + sindf(90.0f) * 10.0f;
    c.z = z + cosdf(90.0f) * 10.0f;
    c.y = func_801061E4_water_whirled(c.x, c.z);
    func_8010860C_water_whirled(&a, &b, &c, &normal);
    normal.y = 0.0f;
    func_800202FC_main(&normal);
    work = object->data;
    normal.x *= 5.0f;
    normal.z *= 20.0f;
    if (work->unk90 < normal.x) {
        work->unk90 += 1.0f;
    } else if (normal.x < work->unk90) {
        work->unk90 -= 1.0f;
    }
    if (work->unk98 < normal.z) {
        work->unk98 += 1.0f;
    } else if (normal.z < work->unk98) {
        work->unk98 -= 1.0f;
    }
    object->rot.x = work->unk90;
    object->rot.z = work->unk98;
}

void func_80108898_water_whirled(omObjData *object, Vec *pos) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    func_800E1BA8_minigame_ObjData *otherWork;
    omObjData *other;
    f32 x = pos->x;
    f32 z = pos->z;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherWork = other->data;
        if (work == otherWork) {
            continue;
        }
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        dist = HuSqrtf(dx * dx + dz * dz) - (otherWork->unk48 + work->unk48);
        if (dist < 0.0f) {
            func_800DFCDC_minigame(dx, dz, dist);
            work->unk53[1] = i;
        }
    }
}

void func_801089C0_water_whirled(omObjData *object, f32 x, f32 z) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    f32 radius = work->unk48;
    f32 dist = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);

    if (dist > radius || fabs(D_800EBE2C_minigame) > radius || fabs(D_800EC5D8_minigame) > radius) {
        D_800EBE2C_minigame = D_8010A1D0_water_whirled[work->unk59].x - x;
        D_800EC5D8_minigame = D_8010A1D0_water_whirled[work->unk59].z - z;
    }
    if (func_800E6E8C_minigame() == 2) {
        if (D_8010A29C_water_whirled[work->unk59] == 0) {
            if (dist > 0.0f) {
                if (dist < radius / 3.0f) {
                    omVibrate(work->unk59, 2, 3, 10);
                } else {
                    omVibrate(work->unk59, 10, 0, 10);
                }
                D_8010A29C_water_whirled[work->unk59] = 10;
            }
        } else {
            D_8010A29C_water_whirled[work->unk59]--;
        }
    }
}

f32 func_80108B98_water_whirled(omObjData *object, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    f32 speed = work->unk40;
    s32 player = work->unk59;
    Hu3DSphere sphere;
    f32 dist;

    sphere.pos.x = x + sindf(work->unk3C) * speed + D_800EBE2C_minigame;
    sphere.pos.y = y;
    sphere.pos.z = z + cosdf(work->unk3C) * speed + D_800EC5D8_minigame;
    sphere.radius = work->unk48;
    work->unk53[0] = work->unk53[1] = -1;
    func_80108898_water_whirled(object, &sphere.pos);
    func_801089C0_water_whirled(object, x, z);
    sphere.pos.x += D_800EBE2C_minigame;
    sphere.pos.z += D_800EC5D8_minigame;
    func_800DD530_minigame(object, &sphere, 0.0f);
    dist = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
    if (dist != 0.0f) {
        if (dist > D_8010A190_water_whirled[player] * 0.5f) {
            work->unk40 *= 0.8f;
        } else {
            work->unk40 *= 0.98f;
        }
        if (dist > D_8010A230_water_whirled[player]) {
            D_8010A200_water_whirled[player].x = D_800EBE2C_minigame;
            D_8010A200_water_whirled[player].y = 0.0f;
            D_8010A200_water_whirled[player].z = D_800EC5D8_minigame;
            func_800202FC_main(&D_8010A200_water_whirled[player]);
            D_8010A230_water_whirled[player] = 16.0f;
        }
    }
    func_801089C0_water_whirled(object, x, z);
    return func_801061E4_water_whirled(sphere.pos.x, sphere.pos.z);
}

void func_80108DF8_water_whirled(omObjData *object) {
    s32 framePos[4][2] = { { 56, 31 }, { 265, 31 }, { 56, 209 }, { 265, 209 } };
    s32 iconPos[4][2] = { { 43, 32 }, { 253, 32 }, { 43, 210 }, { 253, 210 } };
    s16 frameSprite;
    s16 lapSprite;
    s16 finalLapSprite;
    s16 goalSprite;
    s16 digitAnim;
    s16 grp;
    u16 sprite;
    void *data;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

    sprite = espEntry(func_8000B838_main(0x440011), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, 0x4000);
    espScaleSet(sprite, 2.0f, 2.0f);
    // do-while(0) needed to match register allocation.
    do {
        frameSprite = func_8000B838_main(0x440012);
    } while (0);
    lapSprite = func_8000B838_main(0x440014);
    finalLapSprite = func_8000B838_main(0x440015);
    goalSprite = func_8000B838_main(0x440016);
    data = DataRead(0x440013);
    digitAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        sprite = espEntry(frameSprite, 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, framePos[i][0], framePos[i][1]);
        espPriSet(sprite, 0xFFFF);
        espTPLvlSet(sprite, 200);
        sprite = espEntry(func_8000B838_main((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, iconPos[i][0] - 10, iconPos[i][1] + 4);
        espPriSet(sprite, 100);
        D_8010AC68_water_whirled[i] = espEntry(lapSprite, 0, 1);
        espDispOn(D_8010AC68_water_whirled[i]);
        espPosSet(D_8010AC68_water_whirled[i], iconPos[i][0] + 28, iconPos[i][1] - 9);
        espPriSet(D_8010AC68_water_whirled[i], 100);
        D_8010AC58_water_whirled[i] = espEntry(finalLapSprite, 0, 1);
        espDispOff(D_8010AC58_water_whirled[i]);
        espPosSet(D_8010AC58_water_whirled[i], iconPos[i][0] + 13, iconPos[i][1] - 9);
        espPriSet(D_8010AC58_water_whirled[i], 100);
        D_8010AC78_water_whirled[i] = espEntry(goalSprite, 0, 1);
        espDispOff(D_8010AC78_water_whirled[i]);
        espPosSet(D_8010AC78_water_whirled[i], iconPos[i][0] + 13, iconPos[i][1] - 9);
        espPriSet(D_8010AC78_water_whirled[i], 100);
        x = iconPos[i][0] - 8;
        y = iconPos[i][1] - 9;
        grp = D_8010AC48_water_whirled[i] = HuSprGrpCreate(3, 5);
        HuSprGrpMemberSet(grp, 0, digitAnim, 0);
        HuSprAttrReset(grp, 0, 0xFFFF);
        HuSprAttrSet(grp, 0, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(grp, 0, x, y);
        HuSprPriSet(grp, 0, 100);
        x = 8;
        for (j = 1; j < 3; j++) {
            HuSprPriSet(grp, j, 100);
            HuSprGrpMemberSet(grp, j, digitAnim, 0);
            HuSprPosSet(grp, j, x, 0);
            HuSprAttrReset(grp, j, 0xFFFF);
            HuSprAttrSet(grp, j, HUSPR_ATTR_DISPOFF);
            x += 8;
            func_800554C4_main(grp, j, 0);
        }
        HuSprDispOn(grp, 2);
        func_800E9F40_minigame(i, iconPos[i][0], iconPos[i][1], 0);
    }
    object->func = NULL;
}

void func_80109340_water_whirled(s16 player, s16 bank) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOn(D_8010AC68_water_whirled[player]);
    HuSprDispOn(grp, 0);
    HuSprBankSet(grp, 0, bank, 0);
    func_800550F4_main(grp, 0, 1);
    HuSprDispOn(grp, 1);
    HuSprBankSet(grp, 1, 10, 0);
    func_800550F4_main(grp, 1, 1);
    HuSprDispOn(grp, 2);
    HuSprBankSet(grp, 2, 5, 0);
    func_800550F4_main(grp, 2, 1);
    espDispOff(D_8010AC58_water_whirled[player]);
    espDispOff(D_8010AC78_water_whirled[player]);
}

void func_80109458_water_whirled(s16 player) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOff(D_8010AC68_water_whirled[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    if (D_8010A3EC_water_whirled[player] >= 0) {
        espDispOn(D_8010AC58_water_whirled[player]);
        if (D_8010A3EC_water_whirled[player] >= 4) {
            D_8010A3EC_water_whirled[player] = -4;
        }
    } else {
        espDispOff(D_8010AC58_water_whirled[player]);
    }
    D_8010A3EC_water_whirled[player]++;
    espDispOff(D_8010AC78_water_whirled[player]);
}

void func_8010956C_water_whirled(s16 player) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOff(D_8010AC68_water_whirled[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    espDispOff(D_8010AC58_water_whirled[player]);
    espDispOn(D_8010AC78_water_whirled[player]);
}

s32 func_8010960C_water_whirled(omObjData *object) {
    f32 x = object->trans.x;
    f32 z = object->trans.z;

    if ((x > -550.0f) & (x < 550.0f)) {
        if (z > 0.0f) {
            return 0;
        }
        return 2;
    }
    if (x > 0.0f) {
        return 1;
    }
    return 3;
}

void func_801096BC_water_whirled(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    f32 x = object->trans.x;
    f32 z = object->trans.z;
    Vec dir;
    f32 angle;

    if ((x > -1000.0f) & (x < 1000.0f)) {
        if (z > 0.0f) {
            dir.x = 1.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
        } else {
            dir.x = -1.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
        }
    } else {
        if (x > 0.0f) {
            angle = atan2df(object->trans.x - 1000.0f, object->trans.z);
            dir.x = sindf(angle + 10.0f) - sindf(angle);
            dir.y = 0.0f;
            dir.z = cosdf(angle + 10.0f) - cosdf(angle);
        } else {
            angle = atan2df(object->trans.x + 1000.0f, object->trans.z);
            dir.x = sindf(angle + 10.0f) - sindf(angle);
            dir.y = 0.0f;
            dir.z = cosdf(angle + 10.0f) - cosdf(angle);
        }
    }
    angle = work->unk3C;
    work->unk60 = func_800E2ED4_minigame(dir.x, dir.z, sindf(angle), cosdf(angle));
}

void func_801098AC_water_whirled(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    s32 player = work->unk59;
    s32 accelerate;
    s32 section;
    f32 dx;
    f32 dz;
    f32 angle;
    f32 dir;
    f32 radius;

    if (func_800E6E8C_minigame() == 2 && !(GwPlayer[player].stat & 1)) {
        return;
    }
    D_8010AC40_water_whirled = 0;
    D_8010AC44_water_whirled = 0;
    section = func_8010960C_water_whirled(object);
    accelerate = TRUE;
    switch (section) {
        case 0:
            D_8010A860_water_whirled.x = object->trans.x + 100.0f;
            D_8010A860_water_whirled.y = object->trans.z - 50.0f;
            if (D_8010A860_water_whirled.y < D_8010A3FC_water_whirled[player] + 400.0f) {
                D_8010A860_water_whirled.y = D_8010A3FC_water_whirled[player] + 400.0f;
            }
            D_8010A40C_water_whirled[player] = rand8() * D_8010A41C_water_whirled[GwPlayer[player].cpu_difficulty];
            break;
        case 1:
            dx = object->trans.x - 700.0f;
            dz = object->trans.z;
            angle = atan2df(dx, dz);
            radius = HuSqrtf(dx * dx + dz * dz) - 150.0f + D_8010A40C_water_whirled[player];
            D_8010A860_water_whirled.x = sindf(angle + 15.0f) * radius + 700.0f;
            D_8010A860_water_whirled.y = cosdf(angle + 15.0f) * radius;
            if (object->trans.x < 800.0f && object->trans.z > 0.0f && work->unk40 > 20.0f) {
                accelerate = FALSE;
            }
            D_8010A3FC_water_whirled[player] = rand8() * D_8010A41C_water_whirled[GwPlayer[player].cpu_difficulty];
            break;
        case 2:
            D_8010A860_water_whirled.x = object->trans.x - 100.0f;
            D_8010A860_water_whirled.y = object->trans.z + 50.0f;
            if (D_8010A860_water_whirled.y > D_8010A3FC_water_whirled[player] + -400.0f) {
                D_8010A860_water_whirled.y = D_8010A3FC_water_whirled[player] + -400.0f;
            }
            D_8010A40C_water_whirled[player] = rand8() * D_8010A41C_water_whirled[GwPlayer[player].cpu_difficulty];
            break;
        case 3:
            dx = object->trans.x + 700.0f;
            dz = object->trans.z;
            angle = atan2df(dx, dz);
            radius = HuSqrtf(dx * dx + dz * dz) - 150.0f + D_8010A40C_water_whirled[player];
            D_8010A860_water_whirled.x = sindf(angle + 15.0f) * radius + -700.0f;
            D_8010A860_water_whirled.y = cosdf(angle + 15.0f) * radius;
            if (object->trans.x > -800.0f && object->trans.z < 0.0f && work->unk40 > 20.0f) {
                accelerate = FALSE;
            }
            D_8010A3FC_water_whirled[player] = rand8() * D_8010A41C_water_whirled[GwPlayer[player].cpu_difficulty];
            break;
    }
    angle = work->unk3C - 90.0f;
    dx = D_8010A860_water_whirled.x - object->trans.x;
    dz = D_8010A860_water_whirled.y - object->trans.z;
    D_8010AC44_water_whirled = (s8)(func_800E2ED4_minigame(dx, dz, sindf(angle), cosdf(angle)) * 120.0f);
    // do-while(0) needed for float register allocation of dir.
    do {
        dir = work->unk3C;
        dx = D_8010A860_water_whirled.x;
        dz = D_8010A860_water_whirled.y;
        dx -= object->trans.x;
        dz -= object->trans.z;
    } while (0);
    if (func_800E2ED4_minigame(dx, dz, sindf(dir), cosdf(dir)) < 0.0f) {
        D_8010AC44_water_whirled = 60;
    } else if (accelerate == TRUE) {
        D_8010AC40_water_whirled |= 0x8000;
    } else if (D_8010AC44_water_whirled > 0) {
        D_8010AC44_water_whirled = 60;
    } else {
        D_8010AC44_water_whirled = -60;
    }
}

void func_80109E2C_water_whirled(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    s32 player = work->unk59;
    s32 section = func_8010960C_water_whirled(object);
    Vec normal;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 side;

    func_8010860C_water_whirled(&D_8010A44C_water_whirled[section][0], &D_8010A44C_water_whirled[section][1],
                                &D_8010A44C_water_whirled[section][2], &normal);
    dx = object->trans.x - D_8010A44C_water_whirled[section][0].x;
    dy = object->trans.y - D_8010A44C_water_whirled[section][0].y;
    dz = object->trans.z - D_8010A44C_water_whirled[section][0].z;
    side = dx * normal.x + dy * normal.y + dz * normal.z >= 0.0f;
    if (section == D_8010A42C_water_whirled[player]) {
        if (D_8010A43C_water_whirled[player] == 0) {
            if (side == 1) {
                D_8010A240_water_whirled[player]++;
            }
        } else if (side == 0) {
            D_8010A240_water_whirled[player]--;
        }
        if (D_8010A240_water_whirled[player] < 0) {
            switch (section) {
                case 0:
                    D_8010A240_water_whirled[player] = -1;
                    break;
                case 1:
                    D_8010A240_water_whirled[player] = -4;
                    break;
                case 2:
                    D_8010A240_water_whirled[player] = -3;
                    break;
                case 3:
                    D_8010A240_water_whirled[player] = -2;
                    break;
            }
        }
        D_8010A43C_water_whirled[player] = side;
    } else {
        D_8010A43C_water_whirled[player] = side;
    }
    D_8010A42C_water_whirled[player] = section;
    D_8010A270_water_whirled[player] = D_8010A240_water_whirled[player] / 4;
    if (D_8010A270_water_whirled[player] < 0) {
        D_8010A270_water_whirled[player] = 0;
    }
    if (D_8010A284_water_whirled == 0 && D_8010A270_water_whirled[player] == 4) {
        D_8010A284_water_whirled = HuAudFXPlay(0x425);
    }
    if (D_8010A270_water_whirled[player] >= 5) {
        func_8010956C_water_whirled(player);
    } else if (work->unk60 >= 0.0f) {
        func_80109340_water_whirled(player, D_8010A270_water_whirled[player] < 5 ? D_8010A270_water_whirled[player] + 1 : 5);
    } else {
        func_80109458_water_whirled(player);
    }
}
