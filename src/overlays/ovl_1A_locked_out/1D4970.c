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

extern u32 D_8010A1E8_locked_out;
extern f32 D_8010A680_locked_out[4][4];
extern f32 D_8010A6B8_locked_out;
extern f32 D_8010A6C0_locked_out[4][4];
extern f32 D_8010A700_locked_out;
extern omObjData *D_8010A610_locked_out[];
extern s16 D_8010A676_locked_out;

void func_800E1304_minigame(omObjData *, f32);
void func_800E1310_minigame(omObjData *, f32);
void func_800E131C_minigame(omObjData *, f32);
void func_800E139C_minigame(omObjData *, f32, f32, f32, f32, f32);
void func_800E4C88_minigame(omObjData *, u8, f32, f32, f32, f32, f32);

void func_801071D8_locked_out(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_801059A0_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105B38_locked_out);

void func_80105C34_locked_out(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80105CB4_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106040_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80106FBC_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80107844_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109110_locked_out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109264_locked_out);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", D_8010A468_locked_out);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1A_locked_out/1D4970", func_80109E88_locked_out);

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
