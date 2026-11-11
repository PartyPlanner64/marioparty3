#include "common.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))

// Per-object data allocated for each entry of D_80109B00_all_fired_up, stored at omObjData->data
typedef struct {
    /* 0x00 */ s8 unk00; // Index into D_80109B00_all_fired_up
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x20 */ Vec pos;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ u8 unk38;
} AllFiredUpWork; // Size 0x3C

// Per-player work allocated in func_80107DA4_all_fired_up, stored at func_800E1BA8_minigame_ObjData->unk158
typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0C */ f32 unk0C; // Stick angle
} AllFiredUpPlayerWork;   // Size 0x10

extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern f32 D_800EB76C_minigame;

extern u8 D_80109930_all_fired_up[][4];
extern Vec D_80109990_all_fired_up[];
extern u16 D_801099C0_all_fired_up[];
extern s8 D_801099C8_all_fired_up;
extern f32 D_801099CC_all_fired_up;
extern s8 D_801099D0_all_fired_up;
extern u8 D_801099D4_all_fired_up[][6];

extern s32 D_801099F8_all_fired_up;
extern s8 D_801099C9_all_fired_up;
extern s8 D_801099FC_all_fired_up;
extern f32 D_80109A00_all_fired_up;
extern s8 D_80109A04_all_fired_up;
extern s8 D_80109A05_all_fired_up;
extern s8 D_80109A06_all_fired_up;
extern s32 D_80109A08_all_fired_up[];
extern s32 D_80109A18_all_fired_up[][4];
extern f32 D_80109A58_all_fired_up[];
extern s32 D_80109AC0_all_fired_up;
extern s8 D_80109AC4_all_fired_up;
extern s8 D_80109AC5_all_fired_up;
extern D_80111B50_vine_with_me_Struct D_80109AC8_all_fired_up;
extern u8 D_80109AF0_all_fired_up;
extern s16 D_80109AF2_all_fired_up[];
extern omObjData *D_80109B00_all_fired_up[];
extern Vec D_80109B58_all_fired_up[];
extern s8 D_80109C54_all_fired_up;
extern s16 D_80109C56_all_fired_up;
extern s8 D_80109C58_all_fired_up;
extern s8 D_80109C59_all_fired_up;

void func_80105C54_all_fired_up(D_80111B50_vine_with_me_Struct *arg0);
void func_80105CE8_all_fired_up(void);
void func_80105E1C_all_fired_up(omObjData *object);
void func_80105F5C_all_fired_up(void);
void func_80106348_all_fired_up(omObjData *object);
void func_80106584_all_fired_up(omObjData *object);
void func_801067CC_all_fired_up(omObjData *object);
void func_80106B7C_all_fired_up(void);
void func_80106C68_all_fired_up(void);
void func_801068F8_all_fired_up(void);
void func_80106CDC_all_fired_up(omObjData *object);
void func_80106F04_all_fired_up(omObjData *object);
void func_80106FAC_all_fired_up(void);
void func_80107440_all_fired_up(omObjData *object);
void func_80107578_all_fired_up(omObjData *object);
void func_80107BD4_all_fired_up(omObjData *object);
void func_80107DA4_all_fired_up(omObjData *object);
void func_801080C8_all_fired_up(omObjData *object);
void func_801085A4_all_fired_up(omObjData *object);
void func_80108710_all_fired_up(omObjData *object);
void func_80108958_all_fired_up(omObjData *object);
void func_80108AA0_all_fired_up(omObjData *object);
void func_80109660_all_fired_up(omObjData *object, f32 dist, s8 arg2);
void func_801097B0_all_fired_up(omObjData *object);

void func_801059A0_all_fired_up(void) {
    omObjData *object;
    s32 i;

    func_8001FE20_main(32);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    omInitObjMan(32, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CE8_all_fired_up();
    func_80105C54_all_fired_up(&D_80109AC8_all_fired_up);
    func_800E5EA0_minigame(&D_80109AC8_all_fired_up);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105E1C_all_fired_up), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E1490_minigame(D_800EBE28_minigame);
    object = omAddObj(0, 1, 0, -1, func_801097B0_all_fired_up);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = object;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_80109AF0_all_fired_up = (rand8() * 24) >> 8;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(1, 2, 60, -1, func_80107DA4_all_fired_up);
    }
    for (i = 0; i < 4; i++) {
        D_80109AF2_all_fired_up[i] = func_8000B108_main(0x4A0003, 0x819);
        func_8001C258_main(D_80109AF2_all_fired_up[i], 4, 4);
    }
    func_80105F5C_all_fired_up();
    D_80109C58_all_fired_up = (rand8() * 6) >> 8;
    for (i = 0; i < 21; i++) {
        D_80109B00_all_fired_up[i] = omAddObj(1, 2, 0, -1, func_80106348_all_fired_up);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80105C54_all_fired_up(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 0xF;
    arg0->unk00 = 0;
    arg0->unk01 = 5;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 9;
    arg0->unk1C = 0x5A;
    arg0->unk1E = 0x708;
    arg0->unk20 = -1;
    arg0->unk22 = 0x4B;
    arg0->unk24 = 0x96;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105CE8_all_fired_up(void) {
    s32 camIndex;

    Center.x = 0.0f;
    Center.y = 820.0f;
    Center.z = 650.0f;
    CRot.x = -45.0f;
    CRot.y = CRot.z = Center.x;
    CZoom = 2100.0f;
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
}

void func_80105E1C_all_fired_up(omObjData *object) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_801099FC_all_fired_up == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            func_800E6F0C_minigame(5);
            D_801099FC_all_fired_up = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 53;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_801099F8_all_fired_up == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_801099F8_all_fired_up++;
                break;
        }
    }
}

void func_80105F5C_all_fired_up(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        D_80109B58_all_fired_up[i].y = (rand8() % 200) * 3 + 1200.0f;
    }
    D_80109B58_all_fired_up[0].x = D_80109B58_all_fired_up[0].z = 0.0f;
    D_80109B58_all_fired_up[1].x = sindf(0.0f) * 80.0f;
    D_80109B58_all_fired_up[1].z = cosdf(0.0f) * 80.0f;
    D_80109B58_all_fired_up[2].x = sindf(60.0f) * 80.0f;
    D_80109B58_all_fired_up[2].z = cosdf(60.0f) * 80.0f;
    D_80109B58_all_fired_up[3].x = sindf(120.0f) * 80.0f;
    D_80109B58_all_fired_up[3].z = cosdf(120.0f) * 80.0f;
    D_80109B58_all_fired_up[4].x = sindf(180.0f) * 80.0f;
    D_80109B58_all_fired_up[4].z = cosdf(180.0f) * 80.0f;
    D_80109B58_all_fired_up[5].x = sindf(240.0f) * 80.0f;
    D_80109B58_all_fired_up[5].z = cosdf(240.0f) * 80.0f;
    D_80109B58_all_fired_up[6].x = sindf(300.0f) * 80.0f;
    D_80109B58_all_fired_up[6].z = cosdf(300.0f) * 80.0f;
    D_80109B58_all_fired_up[7].x = sindf(0.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[7].z = cosdf(0.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[8].x = sindf(45.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[8].z = cosdf(45.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[9].x = sindf(90.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[9].z = cosdf(90.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[10].x = sindf(135.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[10].z = cosdf(135.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[11].x = sindf(180.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[11].z = cosdf(180.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[12].x = sindf(225.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[12].z = cosdf(225.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[13].x = sindf(270.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[13].z = cosdf(270.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[14].x = sindf(315.0f) * 80.0f * 2;
    D_80109B58_all_fired_up[14].z = cosdf(315.0f) * 80.0f * 2;
    for (i = 15; i < 21; i++) {
        D_80109B58_all_fired_up[i].x = D_80109B58_all_fired_up[i].y = D_80109B58_all_fired_up[i].z = 0.0f;
    }
}

void func_80106348_all_fired_up(omObjData *object) {
    AllFiredUpWork *work;
    s16 model;

    object->func = func_80106584_all_fired_up;
    work = object->data = HuMemAllocTag(sizeof(AllFiredUpWork), TAG_OVERLAY);
    memset(work, 0, sizeof(AllFiredUpWork));
    work->unk00 = D_80109AC0_all_fired_up;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk1C = 0;
    work->unk0C = 0.0f;
    work->unk14 = 0.0f;
    work->unk10 = 0.0f;
    work->unk18 = 1.0f;
    work->unk38 = 0;
    object->trans.x = D_80109B58_all_fired_up[work->unk00].x;
    object->trans.y = D_80109B58_all_fired_up[work->unk00].y;
    object->trans.z = D_80109B58_all_fired_up[work->unk00].z;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    model = object->model[0] = func_8000B108_main(0xA008A, 0xAA9);
    if (work->unk00 == 0) {
        Hu3DAnimRead(Hu3DData[model].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        Hu3DAnimLink(Hu3DData[model].hmf, 0, 0, "c201n_00_DEF");
    }
    Hu3DModelRemakeStatic(model);
    func_8001C514_main(model);
    object->model[1] = func_8000B108_main(0x4A0004, 0x2D9);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    if (work->unk00 >= 15) {
        func_8001C258_main(object->model[0], 4, 4);
        func_8001C258_main(object->model[1], 4, 4);
    }
    D_80109AC0_all_fired_up++;
}

void func_80106584_all_fired_up(omObjData *object) {
    AllFiredUpWork *work;

    if (omPauseChk() + D_800D6A90_main == 0) {
        work = object->data;
        switch (func_800E6E8C_minigame()) {
            case 0:
                func_801067CC_all_fired_up(object);
                break;
            case 2:
                if (D_801099C9_all_fired_up - 1 >= work->unk00) {
                    func_80107BD4_all_fired_up(object);
                }
                if (work->unk00 == 0) {
                    func_801068F8_all_fired_up();
                }
                switch (D_801099C8_all_fired_up) {
                    case 0:
                        func_80106CDC_all_fired_up(object);
                        break;
                    case 1:
                        func_80106F04_all_fired_up(object);
                        break;
                    case 2:
                        func_80107440_all_fired_up(object);
                        break;
                    case 3:
                        func_80107578_all_fired_up(object);
                        break;
                }
                break;
            case 3:
                object->scale.x -= 0.05f;
                if (object->scale.x < 0.0f) {
                    object->scale.x = 0.0f;
                }
                object->scale.y -= 0.05f;
                if (object->scale.y < 0.0f) {
                    object->scale.y = 0.0f;
                }
                object->scale.z -= 0.05f;
                if (object->scale.z < 0.0f) {
                    object->scale.z = 0.0f;
                }
                work->unk08 -= 0.05f;
                if (work->unk08 < 0.0f) {
                    work->unk08 = 0.0f;
                }
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
    }
}

void func_801067CC_all_fired_up(omObjData *object) {
    AllFiredUpWork *work = object->data;

    if (work->unk00 < 15) {
        if (func_800E6E9C_minigame() >= 16) {
            object->trans.y -= work->unk04 + 15.0f;
            work->unk04 += 3.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
                if (work->unk38 == 0) {
                    if (!(work->unk00 & 1)) {
                        HuAudFXPlay(0x441);
                    }
                    work->unk38 = 1;
                }
            }
            work->unk08 += 0.05f;
            if (work->unk08 > 1.0f) {
                work->unk08 = 1.0f;
            }
        }
        Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
    }
}

void func_801068F8_all_fired_up(void) {
    s32 i;

    switch (D_801099C8_all_fired_up) {
        case 0:
            if (D_80109C56_all_fired_up == 0) {
                if (D_80109AC4_all_fired_up > 0 && D_801099C9_all_fired_up < 21) {
                    func_80106B7C_all_fired_up();
                    for (i = 0; i < 21; i++) {
                        ((AllFiredUpWork *)D_80109B00_all_fired_up[i]->data)->unk18 += 0.1f;
                    }
                }
                if (D_80109C56_all_fired_up == 0) {
                    HuAudFXPlay(0x444);
                }
            }
            if (D_80109C56_all_fired_up != 90) {
                D_80109C56_all_fired_up++;
            } else {
                D_801099C8_all_fired_up = 1;
                D_80109C56_all_fired_up = 0;
                func_80106C68_all_fired_up();
            }
            break;
        case 1:
            if (D_80109C56_all_fired_up == 0) {
                HuAudFXPlay(0x443);
            }
            if (D_80109C56_all_fired_up != 30) {
                D_80109C56_all_fired_up++;
            } else {
                D_801099C8_all_fired_up = 2;
                D_80109C56_all_fired_up = 0;
                func_80106C68_all_fired_up();
            }
            break;
        case 2:
            if (D_80109C56_all_fired_up == 0) {
                D_80109C54_all_fired_up = D_801099D4_all_fired_up[D_80109C58_all_fired_up][D_80109AC4_all_fired_up++];
                if (D_80109AC4_all_fired_up >= 7) {
                    D_80109AC4_all_fired_up = 0;
                }
                func_80106FAC_all_fired_up();
                HuAudFXPlay(0x442);
            }
            if (D_80109C56_all_fired_up != 30) {
                D_80109C56_all_fired_up++;
            } else {
                D_801099C8_all_fired_up = 3;
                D_80109C56_all_fired_up = 0;
                D_801099CC_all_fired_up = 400.0f;
                D_801099D0_all_fired_up = 0;
            }
            break;
        case 3:
            if (D_80109C56_all_fired_up == 0) {
                HuAudFXPlay(0x442);
                D_80109C56_all_fired_up++;
            } else if (D_80109C56_all_fired_up != 150) {
                D_80109C56_all_fired_up++;
            } else {
                D_801099C8_all_fired_up = 0;
                D_80109C56_all_fired_up = 0;
            }
            break;
    }
}

void func_80106B7C_all_fired_up(void) {
    omObjData *first;
    omObjData *object;
    AllFiredUpWork *firstWork;
    AllFiredUpWork *work;

    D_801099C9_all_fired_up++;
    first = D_80109B00_all_fired_up[0];
    object = D_80109B00_all_fired_up[D_801099C9_all_fired_up - 1];
    firstWork = first->data;
    work = object->data;
    object->trans.x = first->trans.x;
    object->trans.y = first->trans.y;
    object->trans.z = first->trans.z;
    work->unk08 = firstWork->unk08;
    work->unk0C = firstWork->unk0C;
    work->unk14 = firstWork->unk14;
    work->unk10 = firstWork->unk10;
    func_8001C258_main(object->model[0], 4, 0);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
    func_8001C258_main(object->model[1], 4, 0);
}

void func_80106C68_all_fired_up(void) {
    AllFiredUpWork *work;
    s32 i;

    for (i = 0; i < D_801099C9_all_fired_up; i++) {
        work = D_80109B00_all_fired_up[i]->data;
        work->pos.x = D_80109B00_all_fired_up[i]->trans.x;
        work->pos.y = D_80109B00_all_fired_up[i]->trans.y;
        work->pos.z = D_80109B00_all_fired_up[i]->trans.z;
    }
}

void func_80106CDC_all_fired_up(omObjData *object) {
    AllFiredUpWork *work = object->data;

    if (D_801099C9_all_fired_up >= work->unk00) {
        if (object->trans.y > 0.0f) {
            object->trans.y -= 10.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
            }
            work->unk10 = 0.0f;
            work->unk08 += 0.1f;
            if (work->unk08 > 1.0f) {
                work->unk08 = 1.0f;
            }
            Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
        }
        if (func_800E6E9C_minigame() % 15 == 0) {
            work->unk0C = (rand8() % 180) * 2;
        }
        if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) >= 700.0f) {
            work->unk0C = atan2df(-object->trans.x, -object->trans.z);
        }
        object->trans.x += sindf(work->unk0C) * 5.0f * work->unk18;
        object->trans.z += cosdf(work->unk0C) * 5.0f * work->unk18;
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void func_80106F04_all_fired_up(omObjData *object) {
    AllFiredUpWork *work = object->data;

    if (D_801099C9_all_fired_up >= work->unk00) {
        object->trans.x += (0.0f - work->pos.x) / 30.0f;
        object->trans.y += (0.0f - work->pos.y) / 30.0f;
        object->trans.z += (0.0f - work->pos.z) / 30.0f;
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void func_80106FAC_all_fired_up(void) {
    AllFiredUpWork *work;
    f32 step;
    s32 half;
    s32 i;

    switch (D_80109C54_all_fired_up) {
        case 0:
            step = 360.0f / D_801099C9_all_fired_up;
            for (i = 0; i < D_801099C9_all_fired_up; i++) {
                work = D_80109B00_all_fired_up[i]->data;
                work->unk0C = step * work->unk00;
                work->unk2C.x = sindf(work->unk0C) * 400.0f;
                work->unk2C.y = 0.0f;
                work->unk2C.z = cosdf(work->unk0C) * 400.0f;
            }
            break;
        case 1:
            half = D_801099C9_all_fired_up / 2;
            if (D_801099C9_all_fired_up % 2 != 0) {
                step = 1400.0f / half;
            } else {
                step = 1400.0f / (half - 1);
            }
            for (i = 0; i < half; i++) {
                work = D_80109B00_all_fired_up[i]->data;
                if (D_801099C9_all_fired_up % 2 != 0) {
                    work->unk2C.x = -700.0f + step * work->unk00 + step / 2.0f;
                } else {
                    work->unk2C.x = -700.0f + step * work->unk00;
                }
                work->unk2C.y = 0.0f;
                work->unk2C.z = 0.0f;
                work->unk0C = atan2df(work->unk2C.x, work->unk2C.z);
                work->unk14 = ABS(work->unk2C.x);
            }
            for (i = half; i < D_801099C9_all_fired_up; i++) {
                work = D_80109B00_all_fired_up[i]->data;
                work->unk2C.x = 0.0f;
                work->unk2C.y = 0.0f;
                work->unk2C.z = -700.0f + step * (work->unk00 - half);
                work->unk0C = atan2df(work->unk2C.x, work->unk2C.z);
                work->unk14 = ABS(work->unk2C.z);
            }
            break;
        case 2:
            step = 1400.0f / (D_801099C9_all_fired_up - 1);
            for (i = 0; i < D_801099C9_all_fired_up; i++) {
                work = D_80109B00_all_fired_up[i]->data;
                work->unk2C.x = -700.0f + step * work->unk00;
                work->unk10 = 360.0f / (D_801099C9_all_fired_up - 1) * work->unk00;
                if (work->unk10 >= 180.0f) {
                    work->unk10 -= 180.0f;
                }
                work->unk2C.y = sindf(work->unk10) * 350.0f + 0.0f;
                work->unk2C.z = 0.0f;
                work->unk0C = atan2df(work->unk2C.x, 0.0f);
                work->unk14 = ABS(work->unk2C.x);
                work->unk08 = 1.0f - sindf(work->unk10) * 0.4f;
            }
            break;
    }
}

void func_80107440_all_fired_up(omObjData *object) {
    AllFiredUpWork *work = object->data;

    if (D_801099C9_all_fired_up >= work->unk00) {
        switch (D_80109C54_all_fired_up) {
            case 0:
            case 1:
                object->trans.x += (work->unk2C.x - 0.0f) / 30.0f;
                object->trans.z += (work->unk2C.z - 0.0f) / 30.0f;
                break;
            case 2:
                object->trans.x += (work->unk2C.x - 0.0f) / 30.0f;
                object->trans.y += (work->unk2C.y - 0.0f) / 30.0f;
                object->trans.z += (work->unk2C.z - 0.0f) / 30.0f;
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void func_80107578_all_fired_up(omObjData *object) {
    AllFiredUpWork *work = object->data;
    func_800E1BA8_minigame_ObjData *data;
    s32 i;

    if (D_801099C9_all_fired_up >= work->unk00) {
        if (work->unk00 == 0) {
            switch (D_80109C54_all_fired_up) {
                case 0:
                    for (i = 0; i < 4; i++) {
                        data = D_800EC598_minigame[i]->data;
                        if ((GwPlayer[data->unk59].stat & 1) && data->unk38 != 1000.0f) {
                            D_80109A04_all_fired_up = 1;
                            break;
                        }
                    }
                    if (D_801099CC_all_fired_up == 0.0f || D_801099CC_all_fired_up == 700.0f) {
                        D_80109C59_all_fired_up ^= 1;
                    } else if (D_80109A04_all_fired_up != 0) {
                        if (func_800E6E9C_minigame() % 15 == 0 && (rand8() >> 7)) {
                            D_80109C59_all_fired_up ^= 1;
                        }
                    }
                    break;
                case 2:
                    D_80109C59_all_fired_up = 0;
                    break;
                default:
                    if (func_800E6E9C_minigame() % 15 == 0 && (rand8() >> 7)) {
                        D_80109C59_all_fired_up ^= 1;
                    }
                    break;
            }
        }
        switch (D_80109C54_all_fired_up) {
            case 0:
                if (D_80109C59_all_fired_up == 0 && D_801099D0_all_fired_up == 0 && (rand8() & 1)) {
                    D_80109C59_all_fired_up = 1;
                }
                if (D_80109C59_all_fired_up != 0) {
                    D_801099CC_all_fired_up += 0.5f;
                    if (D_801099CC_all_fired_up > 700.0f) {
                        D_801099CC_all_fired_up = 700.0f;
                        D_801099D0_all_fired_up = 1;
                    }
                } else {
                    D_801099CC_all_fired_up -= 0.5f;
                    if (D_801099CC_all_fired_up < 0.0f) {
                        D_801099CC_all_fired_up = 0.0f;
                    }
                }
                work->unk0C += 1.5f;
                if (work->unk0C >= 360.0f) {
                    work->unk0C -= 360.0f;
                }
                object->trans.x = sindf(work->unk0C) * D_801099CC_all_fired_up;
                object->trans.z = cosdf(work->unk0C) * D_801099CC_all_fired_up;
                break;
            case 1:
                if (work->unk00 == 0 && func_800E6E9C_minigame() % 15 == 0) {
                    D_80109A00_all_fired_up = (rand8() % 15) / 10.0f + 1.0f;
                }
                if (D_80109C59_all_fired_up != 0) {
                    work->unk0C += D_80109A00_all_fired_up;
                    if (work->unk0C >= 360.0f) {
                        work->unk0C -= 360.0f;
                    }
                } else {
                    work->unk0C -= D_80109A00_all_fired_up;
                    if (work->unk0C < 0.0f) {
                        work->unk0C += 360.0f;
                    }
                }
                object->trans.x = sindf(work->unk0C) * work->unk14;
                object->trans.z = cosdf(work->unk0C) * work->unk14;
                break;
            case 2:
                if (work->unk00 == 0 && func_800E6E9C_minigame() % 5 == 0) {
                    D_80109A00_all_fired_up = (rand8() % 15) / 10.0f + 1.0f;
                }
                work->unk0C -= D_80109A00_all_fired_up;
                if (work->unk0C < 0.0f) {
                    work->unk0C += 360.0f;
                }
                object->trans.x = sindf(work->unk0C) * work->unk14;
                object->trans.z = cosdf(work->unk0C) * work->unk14;
                work->unk10 += 2.0f;
                if (work->unk10 >= 180.0f) {
                    work->unk10 -= 180.0f;
                }
                object->trans.y = sindf(work->unk10) * 350.0f;
                work->unk08 = 1.0f - sindf(work->unk10) * 0.6f;
                Hu3DModelScaleSet(object->model[1], work->unk08, work->unk08, work->unk08);
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    }
}

void func_80107BD4_all_fired_up(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    omObjData *player;
    f32 dx;
    f32 dz;
    f32 hitRange = 66.0f;
    s32 i;

    for (i = 0; i < 4; i++) {
        player = D_800EC598_minigame[i];
        data = player->data;
        if (player->work[0] != 0) {
            continue;
        }
        dx = ABS(player->trans.x - object->trans.x);
        dz = ABS(player->trans.z - object->trans.z);
        if (dx < hitRange && dz < hitRange) {
            if (player->trans.y < object->trans.y + 36.0f && player->trans.y + 150.0f > object->trans.y - 36.0f) {
                player->work[0] = 1;
                D_801099C0_all_fired_up[data->unk59] = func_800E6E9C_minigame();
                func_8004AC98_main(0x440, data->unk59);
                PlayerFXPlay(0x286, data->unk59);
                omVibrate(data->unk59, 2, 2, 20);
            }
        }
    }
}

void func_80107DA4_all_fired_up(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    AllFiredUpPlayerWork *work;
    s8 chr;
    s32 model;
    s32 motion;

    chr = GwPlayer[D_80109A05_all_fired_up].chr;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(object, model, motion, D_80109A05_all_fired_up, 0x2C9, 0x2D9);
    data = object->data;
    data->unk158 = HuMemAllocTag(sizeof(AllFiredUpPlayerWork), TAG_OVERLAY);
    memset(data->unk158, 0, sizeof(AllFiredUpPlayerWork));
    work = data->unk158;
    work->unk04 = 0.0f;
    work->unk00 = 1.0f;
    work->unk08 = 0;
    work->unk0C = 0.0f;
    object->rot.x = object->rot.y = object->rot.z = work->unk0C;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    object->work[0] = 0;
    D_80109AC5_all_fired_up = D_80109930_all_fired_up[D_80109AF0_all_fired_up][D_80109A05_all_fired_up];
    object->trans.x = D_80109990_all_fired_up[D_80109AC5_all_fired_up].x;
    object->trans.y = D_80109990_all_fired_up[D_80109AC5_all_fired_up].y;
    object->trans.z = D_80109990_all_fired_up[D_80109AC5_all_fired_up].z;
    func_800E149C_minigame(object, 0, 2);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 21, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, 0x1A), 1, 0);
    func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5690_minigame(object, 0);
    func_800E1328_minigame(object, 60.0f);
    object->func = func_801080C8_all_fired_up;
    D_80109A05_all_fired_up++;
}

void func_801080C8_all_fired_up(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    s32 character;
    s32 i;
    s32 count;
    s32 rank;

    if (omPauseChk() + D_800D6A90_main == 0) {
        switch (func_800E6E8C_minigame()) {
            case 0:
                func_801085A4_all_fired_up(object);
                break;
            case 2:
                if (GwPlayer[data->unk59].stat & 1) {
                    func_80108AA0_all_fired_up(object);
                }
                func_800DDD94_minigame(object);
                if (object->work[0] == 1) {
                    func_800E5690_minigame(object, 14);
                    func_80108710_all_fired_up(object);
                    object->work[0] = 2;
                } else if (object->work[0] == 2) {
                    func_80108710_all_fired_up(object);
                }
                if (data->unk59 == 3) {
                    count = 0;
                    for (i = 0; i < 4; i++) {
                        count += D_800EC598_minigame[i]->work[0] != 0;
                    }
                    if (count >= 3) {
                        func_800E6F0C_minigame(3);
                    }
                }
                break;
            case 3:
                if (D_80109A08_all_fired_up[data->unk59] == 0) {
                    rank = 0;
                    for (i = 0; i < 4; i++) {
                        if (i != data->unk59 && D_801099C0_all_fired_up[data->unk59] < D_801099C0_all_fired_up[i]) {
                            rank++;
                        }
                    }
                    GwPlayer[data->unk59].bonusCoin = rank;
                    D_80109A08_all_fired_up[data->unk59] = 1;
                }
                if (object->work[0] == 0) {
                    data->unk3C *= 0.9f;
                }
                func_800DDD94_minigame(object);
                if (object->work[0] == 2) {
                    func_80108710_all_fired_up(object);
                }
                break;
            case 4:
                if (func_800E6E9C_minigame() == 0) {
                    if (object->work[0] == 0) {
                        switch (GwPlayer[data->unk59].chr) {
                            case 0:
                            default:
                                character = 2;
                                break;
                            case 1:
                                character = 3;
                                break;
                            case 2:
                                character = 7;
                                break;
                            case 3:
                                character = 4;
                                break;
                            case 4:
                                character = 5;
                                break;
                            case 5:
                                character = 6;
                                break;
                            case 6:
                                character = 8;
                                break;
                            case 7:
                                character = 9;
                                break;
                        }
                        func_80045ED0_main((character << 16) | 0x2F);
                        func_800E5690_minigame(object, 13);
                        D_80109A06_all_fired_up = 0;
                    }
                    if (data->unk59 == 3 && D_80109A06_all_fired_up == -1) {
                        D_80109A06_all_fired_up = 1;
                    }
                    switch (D_80109A06_all_fired_up) {
                        case 0:
                            count = 0;
                            for (i = 0; i < 4; i++) {
                                count += GwPlayer[i].bonusCoin == 0;
                            }
                            if (count == 1) {
                                HuAudSeqPlay(0x65);
                            } else {
                                HuAudSeqPlay(0x66);
                            }
                            break;
                        case 1:
                            for (i = 0; i < 3; i++) {
                                if (D_801099C0_all_fired_up[i] != D_801099C0_all_fired_up[i + 1]) {
                                    break;
                                }
                            }
                            if (i == 3) {
                                for (i = 0; i < 4; i++) {
                                    GwPlayer[i].bonusCoin = 3;
                                }
                            }
                            HuAudSeqPlay(0x6C);
                            D_80109A06_all_fired_up = 1;
                            break;
                    }
                } else if ((D_80109A06_all_fired_up == 0 && func_800E6E9C_minigame() >= 100) ||
                           (D_80109A06_all_fired_up == 1 && func_800E6E9C_minigame() > 144)) {
                    func_800E6F0C_minigame(5);
                }
                func_800DDD94_minigame(object);
                break;
            default:
                func_800DDD94_minigame(object);
                if (object->work[0] == 2) {
                    func_80108710_all_fired_up(object);
                }
                break;
        }
        object->scale.x = object->scale.z = 1.2f;
        if (!(data->unk50 & 6)) {
            object->scale.y = 1.2f;
        }
    }
}

void func_801085A4_all_fired_up(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;

    if (func_800E6E9C_minigame() == 20) {
        data->unk3C = atan2df(object->trans.x, object->trans.z);
    } else if (func_800E6E9C_minigame() > 20) {
        if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) < 500.0f) {
            object->trans.x += sindf(data->unk3C) * 10.0f;
            object->trans.z += cosdf(data->unk3C) * 10.0f;
            func_800E5690_minigame(object, 2);
        } else {
            data->unk3C = atan2df(-object->trans.x, -object->trans.z);
            func_800E5690_minigame(object, 0);
        }
        func_800E4E30_minigame(object);
    }
    func_80088910_main(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
}

void func_80108710_all_fired_up(omObjData *object) {
    AllFiredUpPlayerWork *work;

    func_80108958_all_fired_up(object);
    if (object->trans.x > 0.0f) {
        object->trans.x += 28.0f;
    } else {
        object->trans.x -= 28.0f;
    }
    if (object->trans.z > 0.0f) {
        object->trans.z -= 28.0f;
    } else {
        object->trans.z += 28.0f;
    }
    if (ABS(object->trans.x) > 700.0f) {
        func_800E149C_minigame(object, 0, 1);
        func_8001C258_main(object->model[1], 4, 4);
        if (object->trans.y < -2000.0f) {
            object->work[0] = 3;
        }
    }
    work = ((func_800E1BA8_minigame_ObjData *)object->data)->unk158;
    if (work->unk04 < 270.0f) {
        object->trans.y = sindf(work->unk04) * 400.0f;
        work->unk04 += 6.0f;
    } else {
        object->trans.y -= 50.0f;
    }
    work->unk00 = 1.0f - sindf(work->unk04) * 0.8f;
    Hu3DModelScaleSet(object->model[1], work->unk00, work->unk00, work->unk00);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
}

void func_80108958_all_fired_up(omObjData *object) {
    s32 player = ((func_800E1BA8_minigame_ObjData *)object->data)->unk59;
    f32 scale;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_80109A18_all_fired_up[player][i] >= 0) {
            if (D_80109A18_all_fired_up[player][i] == 0) {
                Hu3DModelPosSet(D_80109AF2_all_fired_up[i], object->trans.x, object->trans.y, object->trans.z);
                func_8001C258_main(D_80109AF2_all_fired_up[i], 4, 0);
            }
            if (D_80109A18_all_fired_up[player][i] < 8) {
                scale = D_80109A58_all_fired_up[D_80109A18_all_fired_up[player][i] / 2];
                Hu3DModelScaleSet(D_80109AF2_all_fired_up[i], scale, scale, 1.0f);
            }
            if (D_80109A18_all_fired_up[player][i] >= 8) {
                D_80109A18_all_fired_up[player][i] = -1;
            }
        }
        D_80109A18_all_fired_up[player][i]++;
    }
}

#ifdef NON_MATCHING
void func_80108AA0_all_fired_up(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    AllFiredUpPlayerWork *work;
    omObjData *fire;
    f32 nearX;
    f32 nearZ;
    f32 minDist;
    f32 distSq;
    f32 radius;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 sinAngle;
    f32 cosAngle;
    f32 range;
    f32 x;
    f32 z;
    s32 tries;
    u16 stick;
    s8 blocked;
    s8 jump;
    s32 i;

    nearX = nearZ = 0.0f;
    blocked = 0;
    jump = 0;
    if (object->work[0] != 0) {
        return;
    }
    data = object->data;
    work = data->unk158;
    switch (GwPlayer[data->unk59].cpu_difficulty) {
        case 3:
            stick = 60;
            break;
        case 2:
            stick = 57;
            break;
        case 1:
        default:
            stick = 54;
            break;
        case 0:
            stick = 51;
            break;
    }
    if (work->unk08 == 0) {
        work->unk0C = (rand8() & 0xF) * 360 / 16;
        work->unk08++;
    } else {
        work->unk08++;
        if (work->unk08 >= 15) {
            work->unk08 = 0;
        }
    }
    minDist = 1400.0f * 1400.0f;
    for (i = 0; i < D_801099C9_all_fired_up; i++) {
        fire = D_80109B00_all_fired_up[i];
        dx = fire->trans.x - object->trans.x;
        dz = fire->trans.z - object->trans.z;
        distSq = dx * dx + dz * dz;
        if (distSq < minDist) {
            nearX = fire->trans.x;
            nearZ = fire->trans.z;
            minDist = distSq;
        }
    }
    dist = HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    tries = 0;
    do {
        if (work->unk0C >= 360.0f) {
            work->unk0C -= 360.0f;
        }
        sinAngle = sindf(work->unk0C);
        cosAngle = cosdf(work->unk0C);
        for (i = 0; i < D_801099C9_all_fired_up; i++) {
            fire = D_80109B00_all_fired_up[i];
            blocked = 0;
            if (D_80109C54_all_fired_up == 0 && D_801099C8_all_fired_up == 3) {
                if (D_80109C59_all_fired_up != 0) {
                    if (ABS(D_801099CC_all_fired_up - dist) < 120.0f) {
                        jump = 1;
                    }
                } else {
                    if (ABS(D_801099CC_all_fired_up - dist) < 140.0f) {
                        jump = 1;
                    }
                }
            } else {
                if (D_801099C8_all_fired_up == 2) {
                    range = 250.0f;
                } else if (D_801099C8_all_fired_up == 1) {
                    range = 200.0f;
                } else {
                    range = 100.0f;
                    if (D_801099C8_all_fired_up == 3) {
                        range = 150.0f;
                    }
                }
                dx = fire->trans.x - object->trans.x;
                dz = fire->trans.z - object->trans.z;
                if (HuSqrtf(dx * dx + dz * dz) < range) {
                    if (jump == 1) {
                        if (fire->trans.y > 0.0f) {
                            jump = 0;
                        }
                    } else if (fire->trans.y == 0.0f) {
                        jump = 1;
                    }
                }
            }
            if (D_801099C8_all_fired_up == 3) {
                range = 400.0f;
            } else {
                range = 200.0f;
                if (D_801099C8_all_fired_up == 2) {
                    range = 400.0f;
                }
            }
            x = object->trans.x + sinAngle * range;
            z = object->trans.z + cosAngle * range;
            dx = fire->trans.x - x;
            dz = fire->trans.z - z;
            if (HuSqrtf(dx * dx + dz * dz) < range) {
                blocked = 1;
                break;
            }
        }
        if (blocked == 0) {
            x = object->trans.x + sinAngle * 50.0f;
            z = object->trans.z + cosAngle * 50.0f;
            if (!(x * x + z * z > 700.0f * 700.0f)) {
                break;
            }
        }
        tries++;
        work->unk0C += 0.022222222222222223;
    } while (tries < 8);
    radius = HuSqrtf(object->trans.x * object->trans.x + object->trans.x * object->trans.x);
    if (D_801099C8_all_fired_up == 1) {
        if (D_80109C56_all_fired_up < 21) {
            work->unk0C = atan2df(object->trans.x, object->trans.z);
        } else {
            work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
        }
    } else if (D_80109C54_all_fired_up == 0 && D_801099C8_all_fired_up == 3) {
        if (D_80109C59_all_fired_up != 0) {
            if (D_801099CC_all_fired_up > 350.0f) {
                if (ABS(object->trans.x) < 150.0f && ABS(object->trans.z) < 150.0f) {
                    stick = 0;
                    data->unk3C = atan2df(object->trans.x, object->trans.z);
                } else {
                    data->unk3C = work->unk0C = atan2df(-object->trans.x, -object->trans.z);
                }
            } else {
                data->unk3C = work->unk0C = atan2df(object->trans.x, object->trans.z);
            }
        } else if (D_801099CC_all_fired_up < 350.0f) {
            data->unk3C = work->unk0C = atan2df(object->trans.x, object->trans.z);
        } else if (ABS(object->trans.x) < 150.0f && ABS(object->trans.z) < 150.0f) {
            stick = 0;
            data->unk3C = atan2df(object->trans.x, object->trans.z);
        } else {
            data->unk3C = work->unk0C = atan2df(-object->trans.x, -object->trans.z);
        }
    } else if (D_801099C8_all_fired_up == 2) {
        if (D_80109C54_all_fired_up == 1 || D_80109C54_all_fired_up == 2) {
            if (ABS(object->trans.z) < 200.0f) {
                if (object->trans.z < 0.0f) {
                    work->unk0C = 180.0f;
                } else {
                    work->unk0C = 0.0f;
                }
            } else if (ABS(object->trans.x) < 200.0f) {
                if (object->trans.x < 0.0f) {
                    work->unk0C = 270.0f;
                } else {
                    work->unk0C = 90.0f;
                }
            } else {
                work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
            }
        }
    } else if (D_801099C8_all_fired_up == 3) {
        if (D_80109C54_all_fired_up == 1 || D_80109C54_all_fired_up == 2) {
            func_80109660_all_fired_up(object, radius, jump);
            if (D_800EB76C_minigame <= data->unk40) {
                x = object->trans.x + sindf(data->unk3C) * 200.0f - nearX;
                z = object->trans.z + cosdf(data->unk3C) * 200.0f - nearZ;
                if (x * x + z * z < 200.0f * 200.0f) {
                    stick = 0;
                }
            }
        }
    } else {
        if (blocked == 1) {
            work->unk0C = atan2df(object->trans.x - nearX, object->trans.z - nearZ);
        }
        stick *= 0.8f;
    }
    D_800CBB6E_main[data->unk57] = sindf(work->unk0C) * stick;
    D_800D20A1_main[data->unk57] = -cosdf(work->unk0C) * stick;
    if (jump == 1) {
        D_800D5558_main[data->unk57] |= 0x8000;
    } else {
        D_800D5558_main[data->unk57] &= 0x7FFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108AA0_all_fired_up);
#endif

void func_80109660_all_fired_up(omObjData *object, f32 dist, s8 arg2) {
    AllFiredUpPlayerWork *work = ((func_800E1BA8_minigame_ObjData *)object->data)->unk158;

    if (D_80109C59_all_fired_up != 0) {
        if (arg2 == 0) {
            if (dist > 600.0f) {
                work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 60.0f;
            } else {
                work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 90.0f;
            }
        } else {
            work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 90.0f;
        }
    } else if (arg2 != 0) {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) - 90.0f;
    } else if (dist > 600.0f) {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 60.0f;
    } else {
        work->unk0C = atan2df(-object->trans.x, -object->trans.z) + 90.0f;
    }
}

void func_801097B0_all_fired_up(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;
    u16 sprite1;
    s16 group1;
    u16 sprite2;
    s16 group2;

    object->func = NULL;
    sprite1 = func_8000B838_main(0x4A0001);
    group1 = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group1, 0, sprite1, 0);
    HuSprAttrReset(group1, 0, 0xFFFF);
    HuSprAttrSet(group1, 0, 0x5000);
    HuSprPosSet(group1, 0, 160, 120);
    sprite2 = func_8000B838_main(0x4A0002);
    group2 = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group2, 0, sprite2, 0);
    HuSprAttrReset(group2, 0, 0xFFFF);
    HuSprAttrSet(group2, 0, 0x1000);
    HuSprPosSet(group2, 0, 160, 180);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->model[0] = func_8000B0A0_main(0x4A0000, 0x29D);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk08 = 0.5f;
}
