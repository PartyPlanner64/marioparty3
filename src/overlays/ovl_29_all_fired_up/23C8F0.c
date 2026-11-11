#include "common.h"
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
    /* 0x08 */ s16 unk08;
    /* 0x0C */ f32 unk0C;
} AllFiredUpPlayerWork; // Size 0x10

extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;

extern u8 D_80109930_all_fired_up[][4];
extern Vec D_80109990_all_fired_up[];
extern s16 D_801099C0_all_fired_up[];
extern s8 D_801099C8_all_fired_up;

extern s32 D_801099F8_all_fired_up;
extern s8 D_801099C9_all_fired_up;
extern s8 D_801099FC_all_fired_up;
extern s8 D_80109A05_all_fired_up;
extern s32 D_80109A18_all_fired_up[][4];
extern f32 D_80109A58_all_fired_up[];
extern s32 D_80109AC0_all_fired_up;
extern s8 D_80109AC5_all_fired_up;
extern D_80111B50_vine_with_me_Struct D_80109AC8_all_fired_up;
extern u8 D_80109AF0_all_fired_up;
extern s16 D_80109AF2_all_fired_up[];
extern omObjData *D_80109B00_all_fired_up[];
extern Vec D_80109B58_all_fired_up[];
extern s8 D_80109C54_all_fired_up;
extern u8 D_80109C58_all_fired_up;
extern s8 D_80109C59_all_fired_up;

void func_80105C54_all_fired_up(D_80111B50_vine_with_me_Struct *arg0);
void func_80105CE8_all_fired_up(void);
void func_80105E1C_all_fired_up(omObjData *object);
void func_80105F5C_all_fired_up(void);
void func_80106348_all_fired_up(omObjData *object);
void func_80106584_all_fired_up(omObjData *object);
void func_801067CC_all_fired_up(omObjData *object);
void func_801068F8_all_fired_up(void);
void func_80106CDC_all_fired_up(omObjData *object);
void func_80106F04_all_fired_up(omObjData *object);
void func_80107440_all_fired_up(omObjData *object);
void func_80107578_all_fired_up(omObjData *object);
void func_80107BD4_all_fired_up(omObjData *object);
void func_80107DA4_all_fired_up(omObjData *object);
void func_801080C8_all_fired_up(omObjData *object);
void func_80108958_all_fired_up(omObjData *object);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80105F5C_all_fired_up);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801068F8_all_fired_up);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106FAC_all_fired_up);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80107578_all_fired_up);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801080C8_all_fired_up);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108AA0_all_fired_up);

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
