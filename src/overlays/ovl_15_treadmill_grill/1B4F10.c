#include "common.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

extern s32 D_800A178C_main[][6];
extern u8 D_800D2008_main;
extern u8 D_800D6A90_main;
extern f32 D_800D51FC_main;
extern f32 D_800D5410_main;
extern omObjData *D_800EBE70_minigame[];

extern f32 D_8010AF8C_treadmill_grill[4];
extern f32 D_8010AF9C_treadmill_grill[4];
extern f32 D_8010B1B4_treadmill_grill[4];
extern f32 D_8010B1C4_treadmill_grill[4];
extern Vec D_8010AFB0_treadmill_grill[4];
extern D_80111B50_vine_with_me_Struct D_8010B03C_treadmill_grill;
extern f32 D_8010B064_treadmill_grill[];
extern s32 D_8010B098_treadmill_grill[];
extern Vec D_8010B330_treadmill_grill[6];
extern Vec D_8010B378_treadmill_grill[];
extern s32 D_8010AF80_treadmill_grill;
extern u8 D_8010AF84_treadmill_grill[4];
extern Vec D_8010B000_treadmill_grill[3];
extern u32 D_8010B0D8_treadmill_grill[4];
extern f32 D_8010AFAC_treadmill_grill;
extern s32 D_8010B128_treadmill_grill[4][4];
extern f32 D_8010B168_treadmill_grill[4];
extern s32 D_8010B178_treadmill_grill;
extern f32 D_8010B17C_treadmill_grill[4];
extern s32 D_8010B19C_treadmill_grill;
extern s32 D_8010B1D4_treadmill_grill;
extern s32 D_8010B1D8_treadmill_grill;
extern s32 D_8010B1DC_treadmill_grill;
extern s32 D_8010B224_treadmill_grill[4];
extern f32 D_8010B234_treadmill_grill[6];
extern s16 D_8010B24C_treadmill_grill[6];
extern s32 D_8010B258_treadmill_grill;
extern f32 D_8010B25C_treadmill_grill;
extern f32 D_8010B260_treadmill_grill;
extern s32 D_8010B300_treadmill_grill;
extern s32 D_8010B304_treadmill_grill;
extern s32 D_8010B308_treadmill_grill;
extern s32 D_8010B30C_treadmill_grill;
extern s16 D_8010B310_treadmill_grill[16];

void func_80106008_treadmill_grill(omObjData *object);
void func_801062DC_treadmill_grill(omObjData *object);
void func_801065DC_treadmill_grill(omObjData *object);
void func_801067A8_treadmill_grill(omObjData *object);
void func_80106DA0_treadmill_grill(omObjData *object, s32 model, s32 motion, u16 player, f32 x, f32 y, f32 z);
void func_801084B4_treadmill_grill(omObjData *object);
void func_801085D8_treadmill_grill(omObjData *object);
void func_80108730_treadmill_grill(omObjData *object);
void func_80108888_treadmill_grill(omObjData *object);
void func_801089E0_treadmill_grill(void);
void func_80108C64_treadmill_grill(omObjData *object, f32 x, f32 y, f32 z);
void func_80108DE0_treadmill_grill(omObjData *object);
void func_80108FCC_treadmill_grill(omObjData *object);
void func_80109108_treadmill_grill(omObjData *object);
void func_8010A548_treadmill_grill(void);
s32 func_8010AA2C_treadmill_grill(f32 x, f32 z);
s32 func_8010AB9C_treadmill_grill(f32 z);
void func_8010AE6C_treadmill_grill(omObjData *object);

void func_801059A0_treadmill_grill(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(30, 0);
    func_8004A208_main();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 8000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E19F0_minigame(0);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 1, 0, -1, func_801065DC_treadmill_grill);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_801067A8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801084B4_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_801085D8_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108730_treadmill_grill);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 16, 60, -1, func_80108888_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 2, 0, -1, func_80108DE0_treadmill_grill);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_8010B03C_treadmill_grill);
    D_800EB930_minigame = 53;
    D_800EB932_minigame = 20;
    Hu3DGLightDirSet(1, 86.0f, 45.0f, 74.0f);
    func_801089E0_treadmill_grill();
}

void func_80106008_treadmill_grill(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80106034_treadmill_grill(omObjData *object) {
    omObjData *other;
    f32 scale;
    s32 i;

    if (WipeStatGet() == 0) {
        func_80109108_treadmill_grill(object);
        for (i = 0; i < D_800EC1B8_minigame; i++) {
            other = D_800EBE70_minigame[i];
            other->trans.x = D_8010B378_treadmill_grill[i].x;
            other->trans.y = D_8010B378_treadmill_grill[i].y;
            other->trans.z = D_8010B378_treadmill_grill[i].z;
            other->rot.y = atan2df(-other->trans.x, -other->trans.z);
            scale = D_8010B064_treadmill_grill[i] += 0.125f;
            if (scale > 2.3f) {
                scale = 2.3f;
            }
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            other->scale.x = other->scale.y = other->scale.z = scale;
            if (scale > 1.0f && D_8010B098_treadmill_grill[i] == 0) {
                HuAudFXPlay(0x39F);
                D_8010B098_treadmill_grill[i]++;
            }
        }
    }
}

void func_801061E8_treadmill_grill(omObjData *object) {
    f32 scale;
    s32 i;

    for (i = 0; i < 3; i++) {
        scale = Hu3DData[object->model[10 + i]].scale.x;
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(object->model[10 + i], scale, scale, scale);
        Hu3DModelScaleSet(object->model[13 + i], scale, scale, scale);
    }
}

void func_801062DC_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    omObjData *player;
    s32 last;
    s32 count;
    s32 i;

    last = 0;
    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    count = 0;
    for (i = 0; i < D_800EC280_minigame; i++) {
        if (D_8010AF84_treadmill_grill[i] == 0) {
            count++;
            last = i;
        }
    }
    switch (func_800E6F40_minigame()) {
        case 0:
            if (func_800E6E9C_minigame() == 10) {
                HuAudSeqPlay(0);
            }
            break;
        case 2:
            if (count < 2) {
                func_800E6F0C_minigame(3);
            }
            break;
        case 3:
            if (count != 1) {
                D_8010B03C_treadmill_grill.unk06 = 4;
            } else {
                D_8010B03C_treadmill_grill.unk18[0] = last;
                D_8010B03C_treadmill_grill.unk06 = 0;
            }
            break;
        case 4:
            if (D_800EB934_minigame == 1) {
                if (D_8010B03C_treadmill_grill.unk06 == 4) {
                    for (i = 0; i < 4; i++) {
                        player = D_800EC598_minigame[i];
                        if (D_8010AF84_treadmill_grill[i] == 0) {
                            func_800E5798_minigame(player, 14);
                        }
                    }
                } else {
                    player = D_800EC598_minigame[last];
                    func_800E5798_minigame(player, 13);
                    data = player->data;
                    GwPlayer[data->unk59].bonusCoin += 10;
                    func_80045ED0_main(D_800A178C_main[GwPlayer[data->unk59].chr][0] | 0x2F);
                }
            }
            break;
        case 5:
            WipeCreateOut(0, 20);
            object->func = func_80106008_treadmill_grill;
            break;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        ((func_800E1BA8_minigame_ObjData *)D_800EC598_minigame[i]->data)->unk60 = CRot.y;
    }
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        object->func = func_80106008_treadmill_grill;
    }
    Center.y = 150.0f;
    Center.z = -350.0f;
}

void func_801065DC_treadmill_grill(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = func_8000B0A0_main(0x360005, 0xA9);
    object->trans.x = 100.0f;
    object->trans.y = 0.0f;
    object->trans.z = -1200.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = func_801062DC_treadmill_grill;
    work->unk03 = 1;
    CZoom = 3736.0f;
    CRot.x = 319.0f;
    CRot.y = 0.0f;
    Center.x = 0.0f;
    Center.y = 50.0f;
    Center.z = -350.0f;
    func_800E147C_minigame(object);
    func_800E139C_minigame(object, 0.0f, -1500.0f, -1500.0f, 1500.0f, 1500.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 25.0f);
    work->unk04 = 0;
    func_8001C2FC_main(object->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C954_main(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801067A8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80106DA0_treadmill_grill);

s32 func_80107230_treadmill_grill(void) {
    return 1;
}

void func_80107238_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 player;
    s32 hit;
    s32 i;

    data = object->data;
    player = data->unk59;
    hit = FALSE;
    if (D_8010AF84_treadmill_grill[player] == 0) {
        for (i = 0; i < 3; i++) {
            dx = object->trans.x - D_8010B000_treadmill_grill[i].x;
            dy = object->trans.y - D_8010B000_treadmill_grill[i].y;
            dz = object->trans.z - D_8010B000_treadmill_grill[i].z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < data->unk48 + 40.0f) {
                hit = TRUE;
                break;
            }
        }
        if (data->unk53[0] == 0 || hit == TRUE) {
            D_8010AF84_treadmill_grill[player] = 1;
            func_800E5798_minigame(object, 0x26);
            data->unk50 |= 0x400;
            data->unk38 = -D_800EB744_minigame;
            func_8001C258_main(object->model[1], 4, 4);
            func_8004AC98_main(0x39D, data->unk59);
            PlayerFXPlay(0x286, data->unk59);
            omVibrate(data->unk59, 2, 2, 20);
        }
    }
    if (GwPlayer[data->unk59].stat & 1) {
        D_800D5558_main[data->unk57] = D_8010B304_treadmill_grill;
        D_800CDA7C_main[data->unk57] = D_8010B300_treadmill_grill;
        D_800CBB6E_main[data->unk57] = D_8010B308_treadmill_grill;
        D_800D20A1_main[data->unk57] = D_8010B30C_treadmill_grill;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", D_8010B288_treadmill_grill);

void func_80107454_treadmill_grill(omObjData *object, f32 *x, f32 *y, f32 *z) {
    func_800E1BA8_minigame_ObjData *data;
    D_800EC1C0_minigame_ObjData *stageData;
    omObjData *stage;
    f32 velY;
    s16 seId;

    data = object->data;
    stage = D_800EC1C0_minigame[1];
    if (HuSqrtf(*x * *x + *z * *z) > 2000.0f) {
        func_8001C258_main(object->model[0], 4, 4);
        func_8001C258_main(object->model[10], 4, 4);
        func_8001C258_main(object->model[11], 4, 4);
        func_8001C258_main(object->model[12], 4, 4);
        func_8001C258_main(object->model[13], 4, 4);
        return;
    }
    stageData = stage->data;
    data->unk3C = atan2df(*x - stage->trans.x, *z - stage->trans.z);
    data->unk40 = 25.0f;
    velY = data->unk38;
    if (velY > D_800EB774_minigame) {
        velY = D_800EB774_minigame;
    }
    *y += velY * velY * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
    if (*x > stageData->unkA0 && *x < stageData->unkA8 && *z > stageData->unkA4 && *z < stageData->unkA8) {
        if (*y <= stageData->unk14) {
            data->unk38 = -D_800EB744_minigame;
            *y = stageData->unk14;
            switch (D_8010B0D8_treadmill_grill[data->unk59]) {
                case 0:
                    seId = 0x39E;
                    break;
                case 1:
                    seId = 0x3A0;
                    break;
                case 2:
                    seId = 0x3A1;
                    break;
                case 3:
                    seId = 0x3A2;
                    break;
                case 4:
                default:
                    seId = 0x3A3;
                    break;
            }
            func_8004AC98_main(seId, data->unk59);
            D_8010B0D8_treadmill_grill[data->unk59]++;
        }
    } else if (*y <= 0.0f) {
        data->unk38 = -D_800EB744_minigame;
        *y = 0.0f;
        switch (D_8010B0D8_treadmill_grill[data->unk59]) {
            case 0:
                seId = 0x39E;
                break;
            case 1:
                seId = 0x3A0;
                break;
            case 2:
                seId = 0x3A1;
                break;
            case 3:
                seId = 0x3A2;
                break;
            case 4:
            default:
                seId = 0x3A3;
                break;
        }
        func_8004AC98_main(seId, data->unk59);
        D_8010B0D8_treadmill_grill[data->unk59]++;
    }
    data->unk38 += D_800EB748_minigame * 0.6f;
    func_80108C64_treadmill_grill(object, *x, *y, *z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80107798_treadmill_grill);

void func_801084B4_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[0].chr][1];
    model = D_800A178C_main[GwPlayer[0].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 0, 0.0f, 250.0f, -500.0f);
    data = object->data;
    i = rand8() & 3;
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_801085D8_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[1].chr][1];
    model = D_800A178C_main[GwPlayer[1].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 1, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_80108730_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[2].chr][1];
    model = D_800A178C_main[GwPlayer[2].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 2, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

void func_80108888_treadmill_grill(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 motion;
    s32 model;
    s32 i;

    motion = D_800A178C_main[GwPlayer[3].chr][1];
    model = D_800A178C_main[GwPlayer[3].chr][0];
    func_80106DA0_treadmill_grill(object, model, motion, 3, 0.0f, 250.0f, -300.0f);
    data = object->data;
    do {
        i = rand8() & 3;
    } while (D_8010AFB0_treadmill_grill[i].x == 0.0f);
    object->trans.x = D_8010AFB0_treadmill_grill[i].x;
    object->trans.y = D_8010AFB0_treadmill_grill[i].y;
    object->trans.z = D_8010AFB0_treadmill_grill[i].z;
    D_8010AFB0_treadmill_grill[i].x = D_8010AFB0_treadmill_grill[i].y = D_8010AFB0_treadmill_grill[i].z = 0.0f;
    data->unk3C = i * 90.0f + 135.0f;
}

#ifdef NON_MATCHING
void func_801089E0_treadmill_grill(void) {
    s16 model;
    s32 i;
    void *data;
    s16 anim;

    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
    data = DataRead(0xA008A);
    D_8010B310_treadmill_grill[0] = Hu3DModelCreate(data, 0xAC1);
    anim = Hu3DAnimRead(Hu3DData[D_8010B310_treadmill_grill[0]].hmf, 0xA008C, "c201n_00_DEF");
    Hu3DModelRemakeStatic(D_8010B310_treadmill_grill[0]);
    func_8001C514_main(D_8010B310_treadmill_grill[0]);
    for (i = 1; i < 3; i++) {
        model = Hu3DModelCreate(data, 0xAC1);
        Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, "c201n_00_DEF");
        Hu3DModelRemakeStatic(model);
        func_8001C514_main(model);
        D_8010B310_treadmill_grill[i] = model;
    }
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA008A);
    D_8010B310_treadmill_grill[i] = Hu3DModelCreate(data, 0xAC1);
    anim = Hu3DAnimRead(Hu3DData[D_8010B310_treadmill_grill[i]].hmf, 0xA008D, "c201n_00_DEF");
    Hu3DModelRemakeStatic(D_8010B310_treadmill_grill[i]);
    func_8001C514_main(D_8010B310_treadmill_grill[i]);
    for (i++; i < 16; i++) {
        model = Hu3DModelCreate(data, 0xAC1);
        Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, "c201n_00_DEF");
        Hu3DModelRemakeStatic(model);
        func_8001C514_main(model);
        D_8010B310_treadmill_grill[i] = model;
    }
    HuMemMemoryFreePerm(data);
    D_800D51FC_main = 1.0f;
    D_800D5410_main = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801089E0_treadmill_grill);
#endif
void func_80108C64_treadmill_grill(omObjData *object, f32 x, f32 y, f32 z) {
    s32 player;
    f32 scale;
    s32 i;

    player = ((func_800E1BA8_minigame_ObjData *)object->data)->unk59;
    for (i = 0; i < 4; i++) {
        if (D_8010B128_treadmill_grill[player][i] >= 0) {
            if (D_8010B128_treadmill_grill[player][i] == 0) {
                Hu3DModelPosSet(object->model[10 + i], x, y + 30.0f, z);
                func_8001C258_main(object->model[10 + i], 4, 0);
            }
            if (D_8010B128_treadmill_grill[player][i] < 8) {
                scale = D_8010B168_treadmill_grill[D_8010B128_treadmill_grill[player][i] / 2];
                Hu3DModelScaleSet(object->model[10 + i], scale, scale, 1.0f);
            }
            if (D_8010B128_treadmill_grill[player][i] >= 8) {
                D_8010B128_treadmill_grill[player][i] = -1;
            }
        }
        D_8010B128_treadmill_grill[player][i]++;
    }
}

void func_80108DE0_treadmill_grill(omObjData *object) {
    A96F0_ObjData *data;
    s32 i;

    object->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(A96F0_ObjData));
    data = object->data;
    object->model[1] = 0;
    object->model[0] = D_8010B310_treadmill_grill[D_8010AF80_treadmill_grill++];
    object->func = func_80108FCC_treadmill_grill;
    data->unk44 = 0.3f;
    data->unk48 = 60.0f;
    data->unk34 = 150.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 0;
    data->unk50 = 32;
    data->unk40 = 0.0f;
    data->unk74 = 0.8f;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk56 = D_8010B178_treadmill_grill;
    func_800E149C_minigame(object, 0, 2);
    func_800E149C_minigame(object, 1, 2);
    object->trans.x = sindf(D_8010B178_treadmill_grill * 36.0f) * 450.0f;
    object->trans.y = 500.0f;
    object->trans.z = cosdf(D_8010B178_treadmill_grill * 36.0f) * 450.0f + -512.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.0f;
    D_8010B178_treadmill_grill++;
}

void func_80108FCC_treadmill_grill(omObjData *object) {
    omObjData *stage;
    A96F0_ObjData *data;

    stage = D_800EC1C0_minigame[1];
    data = object->data;
    if (func_800E6E8C_minigame() == 2) {
        object->trans.x = D_8010B378_treadmill_grill[data->unk56].x;
        object->trans.y = D_8010B378_treadmill_grill[data->unk56].y;
        object->trans.z = D_8010B378_treadmill_grill[data->unk56].z;
        object->rot.y = atan2df(stage->trans.x - object->trans.x, stage->trans.z - object->trans.z);
        object->scale.x = object->scale.y = object->scale.z =
            sindf(D_8010AFAC_treadmill_grill * 5.0f + data->unk56 * 30) * 0.3f + 2.2f;
    }
}

void func_80109108_treadmill_grill(omObjData *object) {
    Vec dir;
    f32 length;
    f32 spacing;
    f32 halfWidth;
    f32 dist;
    f32 t;
    s32 i;
    s32 n;

    n = 0;
    length = 2.0f * (D_8010AF8C_treadmill_grill[0] + 600.0f) + 2000.0f;
    spacing = length / (D_800EC1B8_minigame - 1);
    D_8010B330_treadmill_grill[0].x = sindf(D_8010AFAC_treadmill_grill) * (spacing / 2.0f) + object->trans.x + 0.0f;
    D_8010B330_treadmill_grill[0].y = 50.0f;
    D_8010B330_treadmill_grill[0].z = 350.0f;
    halfWidth = D_8010AF8C_treadmill_grill[0] / 2.0f;
    D_8010B330_treadmill_grill[1].x = halfWidth + object->trans.x + 180.0f;
    D_8010B330_treadmill_grill[1].y = 50.0f;
    D_8010B330_treadmill_grill[1].z = 350.0f;
    D_8010B330_treadmill_grill[2].x = halfWidth + object->trans.x + 180.0f;
    D_8010B330_treadmill_grill[2].y = 50.0f;
    D_8010B330_treadmill_grill[2].z = -1150.0f;
    D_8010B330_treadmill_grill[3].x = object->trans.x - halfWidth - 180.0f;
    D_8010B330_treadmill_grill[3].y = 50.0f;
    D_8010B330_treadmill_grill[3].z = -1150.0f;
    D_8010B330_treadmill_grill[4].x = object->trans.x - halfWidth - 180.0f;
    D_8010B330_treadmill_grill[4].y = 50.0f;
    D_8010B330_treadmill_grill[4].z = 350.0f;
    D_8010B330_treadmill_grill[5].x = D_8010B330_treadmill_grill[0].x;
    D_8010B330_treadmill_grill[5].y = 50.0f;
    D_8010B330_treadmill_grill[5].z = 350.0f;
    t = 0.0f;
    for (i = 0; i < 5; i++) {
        dir.x = D_8010B330_treadmill_grill[i + 1].x - D_8010B330_treadmill_grill[i].x;
        dir.y = D_8010B330_treadmill_grill[i + 1].y - D_8010B330_treadmill_grill[i].y;
        dir.z = D_8010B330_treadmill_grill[i + 1].z - D_8010B330_treadmill_grill[i].z;
        dist = HuSqrtf(dir.x * dir.x + dir.z * dir.z);
        func_800202FC_main(&dir);
        do {
            D_8010B378_treadmill_grill[n].x = t * dir.x + D_8010B330_treadmill_grill[i].x;
            D_8010B378_treadmill_grill[n].y = t * dir.y + D_8010B330_treadmill_grill[i].y;
            D_8010B378_treadmill_grill[n].z = t * dir.z + D_8010B330_treadmill_grill[i].z;
            t += spacing;
            n++;
        } while (t < dist);
        t -= dist;
    }
}

void func_801093E0_treadmill_grill(s32 arg0, s32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_801093E8_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_8010980C_treadmill_grill);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_15_treadmill_grill/1B4F10", func_80109FA8_treadmill_grill);

void func_8010A548_treadmill_grill(void) {
    f32 speed;
    s32 index;
    s32 i;

    HuAudFXPlay(0x39C);
    for (i = 0; i < 4; i++) {
        while (D_8010B1B4_treadmill_grill[i] == (speed = D_8010B234_treadmill_grill[index = (u8)(rand8() % 6)]) * 0.5f) {}
        D_8010B17C_treadmill_grill[i] = (speed - D_8010B1B4_treadmill_grill[i]) / 20.0f;
        D_8010B1C4_treadmill_grill[i] = (speed - D_8010B1B4_treadmill_grill[i]) / 20.0f;
        if (D_8010B224_treadmill_grill[i] >= 0) {
            HuAudFXPitchSet((s16)D_8010B224_treadmill_grill[i], D_8010B24C_treadmill_grill[index]);
        }
    }
    D_8010B1D8_treadmill_grill = 20;
    D_8010B1D4_treadmill_grill = 0;
}

void func_8010A6A4_treadmill_grill(void) {
    s32 i;

    if (D_8010B258_treadmill_grill++ < 2) {
        D_8010B19C_treadmill_grill = 50;
        D_8010B1DC_treadmill_grill = 0;
        for (i = 0; i < 4; i++) {
            D_8010B17C_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
            D_8010B1C4_treadmill_grill[i] = -D_8010B1B4_treadmill_grill[i] / 20.0f;
        }
        D_8010B1D8_treadmill_grill = 20;
        D_8010B1D4_treadmill_grill = 0;
    }
}

void func_8010A754_treadmill_grill(omObjData *object) {
    f32 minX;
    f32 maxX;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010AF9C_treadmill_grill[i] = D_8010AF8C_treadmill_grill[i];
        D_8010AF8C_treadmill_grill[i] -= 10.0f;
    }
    func_8010AE6C_treadmill_grill(object);
    if (D_8010B19C_treadmill_grill == 0) {
        func_8010A548_treadmill_grill();
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, -300.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, -600.0f);
    Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, -900.0f);
    D_8010B25C_treadmill_grill += 5.5f;
    D_8010B260_treadmill_grill -= 5.5f;
    Hu3DModelPosSet(object->model[4], object->trans.x, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[5], object->trans.x + D_8010B25C_treadmill_grill, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[6], object->trans.x + D_8010B260_treadmill_grill, 150.0f, 165.0f);
    Hu3DModelPosSet(object->model[7], object->trans.x + D_8010B25C_treadmill_grill + 50.0f, 220.0f, 155.0f);
    Hu3DModelPosSet(object->model[8], object->trans.x + D_8010B260_treadmill_grill - 50.0f, 220.0f, 155.0f);
    minX = -D_8010AF8C_treadmill_grill[0] / 2.0f;
    maxX = D_8010AF8C_treadmill_grill[0] / 2.0f + 50.0f;
    func_800E13CC_minigame(object, 250.0f, 250.0f, minX - 50.0f, -1050.0f, maxX, 150.0f);
}

void func_8010A9AC_treadmill_grill(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801093E0_treadmill_grill(arg0, i);
        D_8010B1B4_treadmill_grill[i] += D_8010B1C4_treadmill_grill[i];
    }
}

s32 func_8010AA2C_treadmill_grill(f32 x, f32 z) {
    s32 lane = -1;

    if (x <= 550.0f && x >= -550.0f) {
        if (z <= 150.0f && z > -150.0f) {
            lane = 0;
        } else if (z <= -150.0f && z > -450.0f) {
            lane = 1;
        } else if (z <= -450.0f && z > -750.0f) {
            lane = 2;
        } else {
            lane = 3;
        }
    }
    return lane;
}

s32 func_8010AB9C_treadmill_grill(f32 z) {
    if (z <= 150.0f && z > -150.0f) {
        return 0;
    }
    if (z <= -150.0f && z > -450.0f) {
        return 1;
    }
    if (z <= -450.0f && z > -750.0f) {
        return 2;
    }
    return 3;
}

void func_8010ACBC_treadmill_grill(omObjData *object) {
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *dst;
    Vtx *src;
    s32 i;
    s32 j;
    s32 k;
    f32 scale;

    for (i = 0; i < 4; i++) {
        hmf = Hu3DData[object->model[i]].hmf;
        scale = D_8010AF8C_treadmill_grill[i] / 1000.0f;
        for (j = 0; j < hmf->unk1A; j++) {
            group = &hmf->unkB0[j];
            if (group->normal[1] == 127) {
                for (k = 0; k < group->count; k++) {
                    dst = &hmf->unk44[D_800D2008_main][group->indices[k]];
                    src = &hmf->unk40[group->indices[k]];
                    if (src->v.ob[0] > 0) {
                        dst->v.ob[0] = D_8010AF8C_treadmill_grill[i] * 0.5f;
                    } else {
                        dst->v.ob[0] = -D_8010AF8C_treadmill_grill[i] * 0.5f;
                    }
                }
            } else {
                for (k = 0; k < group->count; k++) {
                    dst = &hmf->unk44[D_800D2008_main][group->indices[k]];
                    src = &hmf->unk40[group->indices[k]];
                    dst->v.ob[0] = src->v.ob[0] * scale;
                }
            }
        }
    }
}

void func_8010AE6C_treadmill_grill(omObjData *arg0) {
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *vtx;
    s32 i;
    s32 j;
    s32 k;
    f32 scale;

    for (i = 0; i < 4; i++) {
        hmf = Hu3DData[arg0->model[i]].hmf;
        scale = D_8010AF8C_treadmill_grill[i] / D_8010AF9C_treadmill_grill[i];
        for (j = 0; j < hmf->unk1A; j++) {
            group = &hmf->unkB0[j];
            for (k = 0; k < group->count; k++) {
                vtx = &hmf->unk40[group->indices[k]];
                vtx->v.tc[0] = (s16)(vtx->v.tc[0] * scale);
            }
        }
    }
}
