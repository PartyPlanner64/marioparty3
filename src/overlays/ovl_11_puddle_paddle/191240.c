#include "common.h"
#include "gcc/memory.h"

typedef struct UnkPuddlePaddle {
    /* 0x00 */ char pad00[8];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} UnkPuddlePaddle; // size >= 0x10

typedef struct UnkPuddlePaddleEntry { // size 0x24, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char pad0A[2];
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char pad0E[0xA];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} UnkPuddlePaddleEntry; // size = 0x24

typedef struct UnkPuddlePaddleObj { // size = 0x14, eight entries
    /* 0x00 */ char pad00[4];
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char pad0A[6];
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char pad11[3];
} UnkPuddlePaddleObj;

typedef struct UnkPuddlePaddleModel { // size = 0x28, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char pad0E[2];
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ char pad1C[0xC];
} UnkPuddlePaddleModel; // size = 0x28

typedef struct UnkPuddlePaddleSpr { // size = 0x8, twenty entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char pad03[1];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} UnkPuddlePaddleSpr;

extern UnkPuddlePaddleEntry *D_80111668_puddle_paddle;
extern UnkPuddlePaddleModel *D_80111660_puddle_paddle;
extern UnkPuddlePaddleSpr *D_80111664_puddle_paddle;
extern UnkPuddlePaddleObj *D_8011166C_puddle_paddle;

void func_8010BAA8_puddle_paddle(s8 arg0, void *arg1);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801059A0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801059BC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105B94_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105C3C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105C84_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105CBC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105CE0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80105DBC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106028_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106064_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106958_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106988_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801069FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106B6C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80106CE4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801073AC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801073E4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107588_puddle_paddle);

void func_801075B8_puddle_paddle(void) {
    // The original call omits the buffer argument.
    void (*initBuffer)() = (void (*)())func_8010BAA8_puddle_paddle;

    Center.x = 0.0f;
    Center.y = 280.0f;
    Center.z = 102.0f;
    CRot.x = 321.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2970.0f;
    initBuffer(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107638_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010788C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801079D4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107B2C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107DB0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80107E1C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108178_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108368_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801087DC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108D10_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80108E2C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010910C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801091F8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801094C4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109718_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109804_puddle_paddle);

void func_80109814_puddle_paddle(UnkPuddlePaddle *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010981C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80109BD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A224_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010A398_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010ABCC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B574_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B820_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010B8B4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BA04_puddle_paddle);

void func_8010BAA8_puddle_paddle(s8 arg0, void *arg1) {
    memset(arg1, 0, 0x44);
    D_8011166C_puddle_paddle[arg0].unk_10 = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BB00_puddle_paddle);

void func_8010BBB4_puddle_paddle(s8 arg0) {
    UnkPuddlePaddleObj *obj = &D_8011166C_puddle_paddle[arg0];

    memset(obj->unk_04, 0, obj->unk_08 * 0x44);
    obj->unk_10 = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BC14_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BD18_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010BEE8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C088_puddle_paddle);

void func_8010C11C_puddle_paddle(s16 arg0) {
    UnkPuddlePaddleSpr *spr = &D_80111664_puddle_paddle[arg0];

    if (spr->unk_00 != 0) {
        HuSprDispOff(spr->unk_01, 0);
        spr->unk_00 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C16C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C214_puddle_paddle);

s16 func_8010C324_puddle_paddle(s16 arg0, f32 arg1, s16 arg2, s32 arg3) {
    UnkPuddlePaddleModel *work = D_80111660_puddle_paddle;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = Hu3DModelLink(arg0);
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &HmfModelData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = arg2;
            work->unk_04 = arg3;
            work->unk_10 = arg1;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C42C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C4D0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C664_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C804_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010C98C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CA30_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CAD4_puddle_paddle);

UnkPuddlePaddleEntry *func_8010CC64_puddle_paddle(s16 arg0) {
    UnkPuddlePaddleEntry *ret;

    if (arg0 < 0x10) {
        ret = &D_80111668_puddle_paddle[arg0];
    } else {
        ret = 0;
    }
    return ret;
}

HmfModel *func_8010CC9C_puddle_paddle(s16 arg0) {
    HmfModel *ret;

    if (arg0 < 0x10) {
        ret = &HmfModelData[D_80111668_puddle_paddle[arg0].unk_0C];
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CCF0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010CE74_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010D5E4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010E1FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EDE8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EEB8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010EFEC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F410_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F42C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F43C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F44C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F4DC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F4E8_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F580_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F80C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010F9FC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010FBD4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_8010FEC0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801101E0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110284_puddle_paddle);

f32 func_801104C8_puddle_paddle(Object *arg0, Vec *arg1, Vec *arg2) {
    Vec pos, v1, v2;

    pos.x = arg0->coords.x;
    pos.z = arg0->coords.z;
    v1.x = arg1->x - pos.x;
    v1.z = arg1->z - pos.z;
    v2.x = arg2->x - pos.x;
    v2.z = arg2->z - pos.z;
    return v1.z * v2.x - v1.x * v2.z;
}

s32 func_80110524_puddle_paddle(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
    f32 frac = (f32)*tickPtr / numTicks;
    u8 tick;

    *outPos = posA + ((posB - posA) * frac);
    tick = *tickPtr + 1;
    *tickPtr = tick;
    if (numTicks < tick) {
        *tickPtr = 0;
        *outPos = posB;
        return 1;
    }
    return 0;
}

f32 func_8011059C_puddle_paddle(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 t = arg0;
    f32 a;

    if (1.0f < t) {
        t = 1.0f;
    }
    a = 1.0f - t;
    return a * a * arg1 + (a + a) * t * arg2 + t * t * arg3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110608_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110714_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110888_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110A8C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110BBC_puddle_paddle);

void func_80110D3C_puddle_paddle(f32 *mtx) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mtx[i * 4 + j] = 0.0f;
        }
        mtx[i * 4 + i] = 1.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110DC4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110E1C_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110E84_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110EEC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80110FA0_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_80111038_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/191240", func_801110F0_puddle_paddle);
