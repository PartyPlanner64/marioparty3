#include "common.h"
#include "overlays/minigame.h"
#include "game/sprite.h"
#include "mallocblock.h"

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[0xAF];
} LockedOutSetupWork;

typedef struct {
    Vec pos;
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 unk10;
    u8 unk11[3];
} LockedOutUnkStruct;

typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    f32 unk04;
    u8 unk08[0xC];
    s32 unk14;
} LockedOutBlockWork;

extern u32 D_8010A1E8_locked_out;
extern f32 D_8010A680_locked_out[4][4];
extern f32 D_8010A6B8_locked_out;
extern f32 D_8010A6C0_locked_out[4][4];
extern f32 D_8010A700_locked_out;
extern u8 D_8010A704_locked_out[];
extern omObjData *D_8010A610_locked_out[];
extern LockedOutUnkStruct D_8010A638_locked_out[3];
extern s16 D_8010A676_locked_out;
extern s16 D_8010A678_locked_out;
extern s16 D_8010A674_locked_out;
extern s16 D_8010A67A_locked_out;
extern D_80111B50_vine_with_me_Struct D_8010A588_locked_out;
extern void *D_800EBEB0_minigame;

void func_800E12EC_minigame(omObjData *, f32);
void func_800E1304_minigame(omObjData *, f32);
void func_800E1310_minigame(omObjData *, f32);
void func_800E131C_minigame(omObjData *, f32);
void func_800E1328_minigame(omObjData *, f32);
void func_800E1334_minigame(omObjData *, f32);
void func_800E1340_minigame(omObjData *, f32);
void func_800E139C_minigame(omObjData *, f32, f32, f32, f32, f32);
void func_800E4C88_minigame(omObjData *, u8, f32, f32, f32, f32, f32);
void func_80021BE0_main(void *arg0, u16 arg1);
s32 func_8000B638_main(void);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
void func_80016B00_main(s16, s16, char *, HuMtx4F);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_80017D24_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);

void func_80105B38_locked_out(omObjData *object);
void func_80105CB4_locked_out(HuMtx4F, HuMtx4F);
void func_80106040_locked_out(void);
void func_80106134_locked_out(omObjData *object);
void func_80106424_locked_out(omObjData *object);
void func_8010713C_locked_out(void);
s32 func_80109D70_locked_out(void);
f32 func_80109DBC_locked_out(f32 y, f32 x);
f32 func_80109E34_locked_out(Vec *arg0, Vec *arg1);
void func_800E1490_minigame(s32 arg0);
void func_80109110_locked_out(void);
void func_80109264_locked_out(omObjData *object);
void func_80109444_locked_out(omObjData *object);
void func_801071D8_locked_out(omObjData *object);

void func_801059A0_locked_out(void) {
    omObjData *obj;
    u8 camIndex;

    Hu3DAnimInit(2);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 45.0f, 80.0f, 8000.0f);
    func_800E1804_minigame();
    func_80105B38_locked_out(obj);
    func_80106040_locked_out();
    memset(&D_8010A588_locked_out, 0, 0x28);
    D_8010A588_locked_out.unk01 = 4;
    func_800E5EA0_minigame(&D_8010A588_locked_out);
    func_8010713C_locked_out();
    D_8010A676_locked_out = 9;
    D_8010A678_locked_out = 0;
    func_80109110_locked_out();
    func_8001F38C_main(0, 0, 0);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105B38_locked_out(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 1400.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 0.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov[0] / 2.0);
    cosFov = cosdf(camera->fov[0] / 2.0);
    D_8010A700_locked_out = sinFov / cosFov;
    guMtxL2F(D_8010A680_locked_out, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_8010A6C0_locked_out, &camera->mtxs[0].lookAtMtx);
    func_80105CB4_locked_out(D_8010A6C0_locked_out, D_8010A6C0_locked_out);
}

void func_80105C34_locked_out(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80105CB4_locked_out(HuMtx4F src, HuMtx4F dst) {
    f32 mtx[4][4];
    f32 t0;
    f32 t1;
    f32 t2;
    f32 det;
    f32 *dstRow3;

    func_8002367C_main(mtx, src);

    t0 = mtx[1][1] * mtx[2][2] - mtx[1][2] * mtx[2][1];
    t1 = mtx[1][2] * mtx[2][0] - mtx[1][0] * mtx[2][2];

    t2 = mtx[1][0] * mtx[2][1] - mtx[1][1] * mtx[2][0];

    det = t0 * mtx[0][0] + t1 * mtx[0][1] + t2 * mtx[0][2];

    dstRow3 = &dst[3][0];
    if (det != 0.0f) {
        det = 1.0f / det;

        dst[0][0] = t0 * det;
        dst[1][0] = t1 * det;
        dst[2][0] = t2 * det;

        dst[0][1] = (mtx[0][2] * mtx[2][1] - mtx[0][1] * mtx[2][2]) * det;
        dst[0][2] = (mtx[0][1] * mtx[1][2] - mtx[0][2] * mtx[1][1]) * det;
        dst[1][1] = (mtx[0][0] * mtx[2][2] - mtx[0][2] * mtx[2][0]) * det;

        dst[1][2] = (mtx[0][2] * mtx[1][0] - mtx[0][0] * mtx[1][2]) * det;
        dst[2][1] = (mtx[0][1] * mtx[2][0] - mtx[0][0] * mtx[2][1]) * det;
        dst[2][2] = (mtx[0][0] * mtx[1][1] - mtx[0][1] * mtx[1][0]) * det;

        dst[2][3] = 0.0f;
        dst[1][3] = 0.0f;
        dst[0][3] = 0.0f;
        dst[3][3] = 1.0f;

        func_80105C34_locked_out(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80105EA4_locked_out(f32 *pos, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, pos[0], pos[1], pos[2]);
    guMtxCatF(mtx, D_8010A680_locked_out, mtx);
    depth = mtx[3][2] * D_8010A700_locked_out;
    scale = __builtin_fabsf(depth);
    if (scale == 0.0) {
        return;
    }
    dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
    dst[1] = -mtx[3][1] * 120.0f / scale;
}

void func_80105F74_locked_out(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_8010A6B8_locked_out;
    f32 scale = __builtin_fabsf(depth * D_8010A700_locked_out);
    f32 mtx[4][4];

    guTranslateF(mtx, ((x + x) * scale * 1.3333334f) / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_8010A6C0_locked_out, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_80106040_locked_out(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_8010A67A_locked_out = (f32)func_80109D70_locked_out() * 1.52587890625e-05 * 3.0;
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 8, 0, -1, func_80106134_locked_out);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80106424_locked_out);
    D_8010A674_locked_out = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106134_locked_out);

void func_80106424_locked_out(omObjData *object) {
    LockedOutSetupWork *work;

    work = HuMemAllocTag(0xB4, 0x7918);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.5f);
    func_800E1310_minigame(object, 10.0f);
    func_800E139C_minigame(object, 0.0f, -600.0f, -615.0f, 600.0f, 665.0f);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801064E0_locked_out);

void func_80106FBC_locked_out(omObjData *object) {
    LockedOutUnkStruct *entry;
    Vec pos;
    f32 frames;
    f32 radius;
    f32 angle;
    s32 i;

    for (i = 0; i < 3; i++) {
        entry = &D_8010A638_locked_out[i];
        if (entry->unk0C == 0) {
            continue;
        }
        frames = D_800CCF58_main[HmfModelData[entry->unk0E].unk02].unk02;
        radius = HmfModelData[entry->unk0E].unk40 * 175.0 / frames + 50.0;
        pos.x = entry->pos.x - 86.5;
        pos.y = entry->pos.y;
        pos.z = entry->pos.z;
        if (func_80109E34_locked_out(&pos, &object->trans) > radius) {
            continue;
        }
        angle = func_80109DBC_locked_out(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - radius * sindf(angle);
        object->trans.z = pos.z - radius * cosdf(angle);
    }
}

void func_8010713C_locked_out(void) {
    s32 i;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 15, 50, -1, func_801071D8_locked_out);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A298_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A2A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801071D8_locked_out);

void func_80107844_locked_out(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;
    u32 character;
    f32 zero;
    func_800E1BA8_minigame_UnkE8_ObjData *entry;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), 0x7918);
    memset(object->data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), 0x7918);
    memset(data->unkE8, 0, object->mtncnt * 3 * sizeof(s32));

    object->model[0] = func_8000B108_main(arg1 | arg2, tag);
    for (i = 0; i < object->mtncnt; i++) {
        object->motion[i] = -1;
    }
    for (i = 0; i < object->mtncnt; i++) {
        entry = data->unkE8;
        entry[i].unk02 = 0;
        entry[i].unk00 = 0;
    }

    data->unk57 = GwPlayer[player].pad;
    data->unk52 = 0;
    data->unkB4 = 1.0f;
    data->unkD0 = -1;
    data->unk4C = 0.5f;
    data->unkCC = 1.0f;
    zero = 0.0f;
    data->unkA4 = zero;
    data->unk9C = zero;
    data->unkA0 = zero;
    data->unk59 = player;

    data->unk3C = atan2df(-object->trans.x, -object->trans.z);
    func_800E1328_minigame(object, 60.0f);
    func_800E1334_minigame(object, 150.0f);
    func_800E1340_minigame(object, 20.0f);
    func_800E12EC_minigame(object, 1000.0f);

    character = (u32)arg1 >> 16;
    switch (character) {
        case 6:
            data->unkAC = 0.8f;
            break;
        case 5:
            data->unkAC = 0.9f;
            break;
        case 0:
        default:
            data->unkAC = 1.0f;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107ABC_locked_out);

void func_801089F8_locked_out(omObjData *object, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[object->model[i]].unk18 & 4) {
            func_800E4C88_minigame(object, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80108A90_locked_out);

void func_801090FC_locked_out(omObjData *object, func_800E1BA8_minigame_ObjData **data, void **arg2) {
    *data = object->data;
    *arg2 = (*data)->unk158;
}

void func_80109110_locked_out(void) {
    s32 i;
    s16 j;
    u8 temp;

    for (i = 0; i < D_8010A676_locked_out; i++) {
        D_8010A610_locked_out[i] = omAddObj(3, 5, 5, -1, func_80109264_locked_out);
    }
    for (i = 0; i < D_8010A676_locked_out; i++) {
        D_8010A704_locked_out[i] = i;
    }
    for (i = D_8010A676_locked_out; i > 0; i--) {
        j = (f32)func_80109D70_locked_out() * 1.52587890625e-05 * i;
        temp = D_8010A704_locked_out[i - 1];
        D_8010A704_locked_out[i - 1] = D_8010A704_locked_out[j];
        D_8010A704_locked_out[j] = temp;
    }
}

void func_80109264_locked_out(omObjData *object) {
    Vec positions[9] = {
        { 50.0f, 50.0f, 60.0f },
        { -50.0f, 50.0f, -60.0f },
        { 150.0f, 50.0f, -60.0f },
        { -150.0f, 50.0f, 60.0f },
        { 250.0f, 50.0f, 60.0f },
        { -250.0f, 50.0f, -60.0f },
        { 350.0f, 50.0f, -60.0f },
        { -350.0f, 50.0f, 60.0f },
        { 450.0f, 50.0f, 60.0f },
    };
    LockedOutBlockWork *work;

    work = HuMemAllocTag(sizeof(LockedOutBlockWork), 0x7918);
    object->data = work;
    memset(work, 0, sizeof(LockedOutBlockWork));
    work->unk00 = 0;
    work->unk02 = D_8010A678_locked_out % 3;
    work->unk04 = 20.0f;
    work->unk14 = 0;
    work->unk01 = 0;
    object->model[0] = func_8000B108_main((work->unk02 + 7) | 0x3B0000, 0x2D9);
    object->model[1] = func_8000B0D4_main(9, 0x2D9);
    Hu3DModelScaleSet(object->model[1], 0.75f, 0.75f, 0.75f);
    object->trans.x = positions[D_8010A704_locked_out[D_8010A678_locked_out]].x;
    object->trans.y = positions[D_8010A704_locked_out[D_8010A678_locked_out]].y;
    object->trans.z = positions[D_8010A704_locked_out[D_8010A678_locked_out]].z;
    object->rot.x = -90.0f;
    object->func = func_80109444_locked_out;
    D_8010A678_locked_out++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109444_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109858_locked_out);

void func_80109CDC_locked_out(void) {
    omObjData *object;
    s32 i;

    for (i = 0; i < D_8010A676_locked_out; i++) {
        object = D_8010A610_locked_out[i];
        func_8001ACDC_main(object->model[0]);
        func_8001ACDC_main(object->model[1]);
        HuMemFree(object->data);
        object->data = NULL;
        omDelObj(object);
    }
}

s32 func_80109D70_locked_out(void) {
    D_8010A1E8_locked_out = (D_8010A1E8_locked_out + (rand8() & 0xFF)) * 0x41C64E6D + 0x3039;
    return D_8010A1E8_locked_out >> 16;
}

f32 func_80109DBC_locked_out(f32 y, f32 x) {
    f32 fullCircle = 360.0f;
    f32 angle = atan2df(y, x);

    if (angle < -180.0f) {
        angle += fullCircle;
    } else if (angle >= 180.0) {
        angle -= fullCircle;
    }
    return angle;
}

f32 func_80109E34_locked_out(Vec *arg0, Vec *arg1) {
    return sqrtf(((arg0->x - arg1->x) * (arg0->x - arg1->x)) +
                 ((arg0->z - arg1->z) * (arg0->z - arg1->z)));
}

void func_80109E88_locked_out(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    func_80016B00_main(model, time, hook, hookTransform);
    modelData = &HmfModelData[model];
    func_80088800_main(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    func_80017D24_main(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    func_80017CD0_main(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    func_80018044_main(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

s16 func_80109FAC_locked_out(s32 dataNum) {
    void *data;
    s16 spriteId;

    data = DataRead(dataNum);
    spriteId = func_80055810_main(data);
    DataClose(data);
    return spriteId;
}

s16 func_80109FF4_locked_out(s16 spriteId, s16 count) {
    s16 groupId;
    s32 i;

    if (spriteId == -1) {
        return -1;
    }
    groupId = HuSprGrpCreate(count, 0);
    if (groupId == -1) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        func_80055024_main(groupId, i, spriteId, 0);
    }
    return groupId;
}

HuSprite_Unk84_Unk00_Struct *func_8010A0BC_locked_out(s16 groupId, s16 member) {
    return &func_80055194_main(groupId)->unk00[member];
}
