#include "common.h"
#include "overlays/minigame.h"
#include "game/sprite.h"
#include "mallocblock.h"
#include "game/pause.h"

#define PLAYER_WORK(obj) ((LockedOutPlayerWork *)((func_800E1BA8_minigame_ObjData *)(obj)->data)->unk158)

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
    Vec unk08;
    omObjData *unk14;
} LockedOutBlockWork;

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ u16 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u8 unk34[8];
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42[0xA];
} LockedOutPlayerWork; // Size 0x4C

typedef struct {
    u8 values[8];
} LockedOutCharMotions;

extern u8 D_8010A179_locked_out[][2];
extern u8 D_8010A180_locked_out;
extern Vec D_8010A184_locked_out[];
extern f32 D_8010A1B4_locked_out[];
extern Vec D_8010A1C4_locked_out[];
extern u32 D_8010A1E8_locked_out;
extern s32 D_800A178C_main[][6];
extern f32 D_8010A680_locked_out[4][4];
extern f32 D_8010A6B8_locked_out;
extern f32 D_8010A6C0_locked_out[4][4];
extern f32 D_8010A700_locked_out;
extern u8 D_8010A704_locked_out[];
extern omObjData *D_8010A610_locked_out[];
extern Vec D_8010A110_locked_out[];
extern LockedOutUnkStruct D_8010A638_locked_out[3];
extern s16 D_8010A676_locked_out;
extern s16 D_8010A678_locked_out;
extern s16 D_8010A674_locked_out;
extern s16 D_8010A67A_locked_out;
extern D_80111B50_vine_with_me_Struct D_8010A588_locked_out;
extern void *D_800EBEB0_minigame;
extern s32 D_8010A164_locked_out;
extern u16 D_8010A168_locked_out;
extern s32 D_8010A16C_locked_out;
extern s16 D_8010A170_locked_out;
extern s8 D_8010A172_locked_out;
extern s8 D_8010A173_locked_out;
extern u8 D_8010A174_locked_out;
extern s32 D_8010A580_locked_out;
extern s16 D_8010A584_locked_out;

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
void func_801064E0_locked_out(omObjData *object);
void func_80106FBC_locked_out(omObjData *object);
void func_80107ABC_locked_out(omObjData *object);
u16 func_80108A90_locked_out(omObjData *object);
u32 func_800E4A90_minigame(omObjData *);
void func_800E149C_minigame(omObjData *, s32, s32);
void func_80109858_locked_out(omObjData *object, u8 isPlayer, u8 canGrab);
void func_801090FC_locked_out(omObjData *object, func_800E1BA8_minigame_ObjData **data, LockedOutPlayerWork **arg2);
void func_80109E88_locked_out(s16 model, char *hook, s16 time, Vec *pos);
void func_8001EF6C_main(s16, s16, char *);
void func_800E6F0C_minigame(s32);
void func_80109CDC_locked_out(void);
void func_800DDD94_minigame(omObjData *);
void func_800E5138_minigame(omObjData *);
void func_80088910_main(HuMtx4F mtx, f32 r, f32 p, f32 h);

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

void func_80106134_locked_out(omObjData *object) {
    LockedOutSetupWork *work;
    s32 i;
    s32 tag;

    work = HuMemAllocTag(0xB4, 0x7918);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.5f);
    func_800E1310_minigame(object, 10.0f);
    func_800E139C_minigame(object, 0.0f, -600.0f, -615.0f, 600.0f, 615.0f);
    tag = 0x2D9;
    object->model[0] = func_8000B108_main(0x3B0000, tag);
    object->model[1] = func_8000B108_main(0x3B0003, tag);
    object->model[6] = func_8000B108_main(0x3B0010, 0x2DD);
    object->model[7] = func_8000B108_main(0x3B0011, 0x2DD);
    for (i = 0; i < 3; i++) {
        D_8010A638_locked_out[i].pos.x = D_8010A110_locked_out[i * 3].x;
        D_8010A638_locked_out[i].pos.y = D_8010A110_locked_out[i * 3].y;
        D_8010A638_locked_out[i].pos.z = D_8010A110_locked_out[i * 3].z;
        D_8010A638_locked_out[i].unk0C = 0;
        D_8010A638_locked_out[i].unk10 = 1;
        D_8010A638_locked_out[i].unk0D = object->model[2 + i] =
            func_8000B108_main((D_8010A67A_locked_out + 4) | 0x3B0000, tag);
        Hu3DModelPosSet(object->model[2 + i], D_8010A638_locked_out[i].pos.x, D_8010A638_locked_out[i].pos.y,
                        D_8010A638_locked_out[i].pos.z);
        func_8001C92C_main(object->model[2 + i], 0.0f);
        D_8010A638_locked_out[i].unk0F = func_8000B0A0_main(7, 0x2DD);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 0.0f);
        Hu3DModelRotSet(D_8010A638_locked_out[i].unk0F, 90.0f, 0.0f, 0.0f);
        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(object->model[6]);
        func_8001C258_main(D_8010A638_locked_out[i].unk0E, 4, 4);
        func_8001C92C_main(D_8010A638_locked_out[i].unk0E, 0.0f);
    }
    object->model[5] = func_8000B108_main(0x3B000A, 0x2B9);
    object->func = func_801064E0_locked_out;
}

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

void func_801064E0_locked_out(omObjData *object) {
    LockedOutPlayerWork *work;
    s32 i;
    s32 j;
    s32 count;
    s32 rank = 0;
    s32 found;
    u16 tag;
    f32 s;
    f32 c;

    switch (D_8010A674_locked_out) {
        case 0:
            GMesCreate(7);
            D_8010A168_locked_out = 300;
            D_8010A674_locked_out++;
            D_8010A584_locked_out = 20;
        case 1:
            if (--D_8010A584_locked_out == 0) {
                HuAudSeqPlay(0x35);
            }
            if (GMesStatGet() == 0) {
                func_800E6F0C_minigame(2);
                D_8010A674_locked_out++;
                GMesCreate(0x1A, (D_8010A168_locked_out + 29) / 30, 0xA0, 0x20);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x35);
            }
            break;
        case 2:
            count = 0;
            for (i = 0; i < D_8010A173_locked_out; i++) {
                count += (D_8010A638_locked_out[i].unk10 == 0);
            }
            if (count >= D_8010A172_locked_out - 1) {
                D_8010A674_locked_out = 3;
            }
            D_8010A168_locked_out--;
            func_8003F578_main((D_8010A168_locked_out + 29) / 30);
            if (D_8010A168_locked_out == 0) {
                D_8010A674_locked_out = 3;
            }
            break;
        case 3:
            D_8010A172_locked_out = 0;
            D_8010A16C_locked_out = -1;
            for (i = 0; i < 4; i++) {
                if (PLAYER_WORK(D_800EC598_minigame[i])->unk23 != 0) {
                    D_8010A172_locked_out++;
                    rank++;
                    D_8010A16C_locked_out = i;
                }
                if (PLAYER_WORK(D_800EC598_minigame[i])->unk3C != 0 && PLAYER_WORK(D_800EC598_minigame[i])->unk3C < 5) {
                    break;
                }
            }
            if (i < 4) {
                break;
            }
            for (i = 0; i < 4; i++) {
                work = PLAYER_WORK(D_800EC598_minigame[i]);
                if (work->unk23 == 0 && work->unk24 == 0) {
                    work->unk24 = rank;
                }
            }
            if (D_8010A172_locked_out >= 2) {
                WipeCreateOut(0xC, 0x1E);
                D_8010A674_locked_out = 4;
                D_8010A174_locked_out = 0;
            } else {
                func_8003F5C0_main();
                GMesCreate(0x12);
                HuAudSeqFadeOut(0x78);
                D_8010A674_locked_out = 6;
            }
            break;
        case 4:
            if (WipeStatGet() != 0) {
                break;
            }
            tag = 0x2B9;
            func_8001ACDC_main(object->model[1]);
            object->model[1] = func_8000B108_main(0x3B0002, tag);
            D_8010A67A_locked_out = (f32)func_80109D70_locked_out() * 1.52587890625e-05 * 3.0;
            D_8010A173_locked_out = 2;
            for (i = 0; i < 3; i++) {
                if (object->model[2 + i] != 0) {
                    func_8001ACDC_main(object->model[2 + i]);
                    func_8001ACDC_main(D_8010A638_locked_out[i].unk0E);
                    object->model[2 + i] = 0;
                    D_8010A638_locked_out[i].unk10 = 0;
                }
                if (i < 2) {
                    D_8010A638_locked_out[i].pos.x = D_8010A110_locked_out[i * 3 + 1].x;
                    D_8010A638_locked_out[i].pos.y = D_8010A110_locked_out[i * 3 + 1].y;
                    D_8010A638_locked_out[i].pos.z = D_8010A110_locked_out[i * 3 + 1].z;
                    D_8010A638_locked_out[i].unk0C = 0;
                    D_8010A638_locked_out[i].unk10 = 1;
                    if (D_8010A172_locked_out == 2) {
                        D_8010A638_locked_out[i].unk0D = object->model[2 + i] =
                            func_8000B108_main((D_8010A67A_locked_out + 13) | 0x3B0000, tag);
                    } else {
                        D_8010A638_locked_out[i].unk0D = object->model[2 + i] =
                            func_8000B108_main((D_8010A67A_locked_out + 4) | 0x3B0000, tag);
                    }
                    if (D_8010A172_locked_out == 2) {
                        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(object->model[7]);
                    } else {
                        D_8010A638_locked_out[i].unk0E = Hu3DModelLink(object->model[6]);
                    }
                    func_8001C92C_main(D_8010A638_locked_out[i].unk0E, 0.0f);
                    func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 0.0f);
                    func_8001C6A8_main(D_8010A638_locked_out[i].unk0F, 0.0f);
                    func_8001C258_main(D_8010A638_locked_out[i].unk0F, 4, 4);
                    Hu3DModelPosSet(object->model[2 + i], D_8010A638_locked_out[i].pos.x,
                                    D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
                    func_8001C92C_main(object->model[2 + i], 0.0f);
                }
            }
            func_8001ACDC_main(object->model[5]);
            object->model[5] = func_8000B108_main((14 - D_8010A172_locked_out) | 0x3B0000, tag);
            func_80109CDC_locked_out();
            D_8010A676_locked_out = (D_8010A172_locked_out - 1) * 3;
            D_8010A678_locked_out = 0;
            func_80109110_locked_out();
            func_8003F578_main(10);
            WipeCreateIn(0xC, 0x1E);
            D_8010A674_locked_out++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                D_8010A168_locked_out = 300;
                D_8010A674_locked_out = 2;
            }
            break;
        case 6:
            if (D_8010A16C_locked_out != -1) {
                if (D_8010A170_locked_out != 0) {
                    s = sindf(D_8010A170_locked_out * 0.5);
                    c = cosdf(D_8010A170_locked_out * 0.5);
                    CZoom = (s * 47.0 + 23.0) * 20.0;
                    CRot.x = -(s * 22.0 + 18.0);
                    Center.x = c * D_8010A638_locked_out[PLAYER_WORK(D_800EC598_minigame[D_8010A16C_locked_out])->unk3E].pos.x;
                    Center.y = (s * 1.5 + 4.0) * 20.0;
                    Center.z = c * D_8010A638_locked_out[PLAYER_WORK(D_800EC598_minigame[D_8010A16C_locked_out])->unk3E].pos.z;
                    D_8010A170_locked_out -= 6;
                }
            }
            if (D_8010A16C_locked_out == -1 && D_8010A174_locked_out != 0) {
                for (i = 0; i < 4; i++) {
                    PLAYER_WORK(D_800EC598_minigame[i])->unk24 = 3;
                }
            } else {
                rank = 0;
                for (j = 0; j < 4; j++) {
                    found = 0;
                    for (i = 0; i < 4; i++) {
                        work = PLAYER_WORK(D_800EC598_minigame[i]);
                        if (work->unk24 == j) {
                            work->unk24 = rank;
                            found = 1;
                        }
                    }
                    rank += found;
                }
            }
            if (GMesStatGet() == 0) {
                if (D_8010A16C_locked_out == -1) {
                    D_8010A164_locked_out = 0x9F;
                } else {
                    D_8010A164_locked_out = 0x71;
                }
                D_8010A580_locked_out = 15;
                D_8010A674_locked_out++;
                func_800E6F0C_minigame(4);
            }
            break;
        case 7:
            if (--D_8010A164_locked_out == 0) {
                D_8010A674_locked_out++;
            }
            if (--D_8010A580_locked_out == 0) {
                if (D_8010A16C_locked_out == -1) {
                    HuAudSeqPlay(0x6C);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 8:
            if (D_8010A164_locked_out != 0) {
                if (--D_8010A164_locked_out == 0) {
                    D_8010A674_locked_out++;
                }
            } else {
                func_800E6F0C_minigame(5);
                D_8010A164_locked_out = 16;
                WipeCreateOut(0, D_8010A164_locked_out);
                HuAudSeqFadeOut(D_8010A164_locked_out);
                func_8004AB0C_main((s16)D_8010A164_locked_out);
            }
            break;
        case 9:
            func_8004A950_main();
            omOvlReturnEx(1);
            break;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010A674_locked_out = 8;
    }
}

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

const LockedOutCharMotions D_8010A298_locked_out = { { 0, 1, 2, 3, 4, 5, 6, 7 } };

void func_801071D8_locked_out(omObjData *object) {
    LockedOutCharMotions motions = D_8010A298_locked_out;
    s32 anims[3][8] = {
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
        { 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0x1D },
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
    };
    func_800E1BA8_minigame_ObjData *data;
    LockedOutPlayerWork *work;
    u8 player;
    s8 character;
    u32 model;
    s32 motion;
    s32 linkModel;

    player = D_8010A179_locked_out[D_8010A180_locked_out][0];
    character = GwPlayer[player].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A178C_main[character][1];
    linkModel = D_800A178C_main[character][2];
    func_800E1BA8_minigame(object, model, motion, player, 0x2D9, 0x2D9);
    object->model[9] = func_8000B108_main(model | linkModel, 0x2ED);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->trans.x = D_8010A184_locked_out[D_8010A180_locked_out].x;
    object->trans.y = D_8010A184_locked_out[D_8010A180_locked_out].y;
    object->trans.z = D_8010A184_locked_out[D_8010A180_locked_out].z;
    data->unk3C = D_8010A1B4_locked_out[D_8010A180_locked_out];
    switch (model >> 16) {
        case 6:
            data->unk48 *= 1.25f;
            break;
        case 4:
            data->unk48 *= 1.1f;
            break;
        case 5:
            data->unk48 *= 1.2f;
            break;
    }
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->trans.x = D_8010A184_locked_out[D_8010A180_locked_out].x;
    object->trans.y = D_8010A184_locked_out[D_8010A180_locked_out].y;
    object->trans.z = D_8010A184_locked_out[D_8010A180_locked_out].z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    data->unk158 = HuMemAllocTag(sizeof(LockedOutPlayerWork), 0x7918);
    memset(data->unk158, 0, sizeof(LockedOutPlayerWork));
    work = data->unk158;
    work->unk20 = player;
    work->unk21 = character;
    work->unk27 = GwPlayer[player].stat & 1;
    work->unk22 = GwPlayer[player].cpu_difficulty;
    work->unk1C = model | 0x2F;
    work->unk23 = 0;
    work->unk24 = 0;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk25 = 0;
    work->unk28 = 0;
    work->unk2B = func_80017790_main(object->model[9], 2, motions.values[character], model | anims[2][character]);
    work->unk29 = func_80017AD8_main(model | anims[0][character]);
    work->unk2A = func_80017AD8_main(model | anims[1][character]);
    func_8001C514_main(object->model[9]);
    func_800E149C_minigame(object, 0, 2);
    data->unk50 |= 0x8000;
    object->func = func_80107ABC_locked_out;
    object->model[3] = func_8000B108_main(3, 0x2DD);
    object->model[6] = func_8000B108_main(5, 0x2DD);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(character, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(character, 2), 1, 0);
    func_800E5A00_minigame(object, 5, func_80017BB8_main(character, 3), 0, 0);
    func_800E5A00_minigame(object, 0x11, func_80017BB8_main(character, 0xE), 0, 0);
    func_800E5A00_minigame(object, 0x20, func_80017BB8_main(character, 0x22), 0, 0);
    func_800E5A00_minigame(object, 0x1E, func_80017BB8_main(character, 0x20), 2, 0);
    func_800E5A00_minigame(object, 0x1F, func_80017BB8_main(character, 0x21), 2, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
    func_800E5A00_minigame(object, 0xF, func_80017BB8_main(character, 0x38), 1, 0x64);
    switch (model >> 16) {
        case 2:
        case 5:
        case 7:
            func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x39), 1, 0x3C);
            break;
        case 3:
        case 4:
        case 6:
        case 8:
        case 9:
            func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x3A), 1, 0x3C);
            break;
    }
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(character, 0x8D), 1, 0);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(character, 0x8E), 0, 0);
    func_800E5690_minigame(object, 0);
    D_8010A180_locked_out++;
}

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

void func_80107ABC_locked_out(omObjData *object) {
    LockedOutCharMotions motions = D_8010A298_locked_out;
    func_800E1BA8_minigame_ObjData *data;
    LockedOutPlayerWork *work;
    LockedOutBlockWork *blockWork;
    LockedOutUnkStruct *entry;
    omObjData *block;
    Vec pos;
    u32 status;
    u16 buttons;
    u8 pad;
    s32 canGrab;
    s32 i;
    f32 angle;
    f32 radius;
    f32 time;
    s32 temp;

    data = object->data;
    work = data->unk158;
    pad = data->unk57;
    canGrab = FALSE;
    if (D_8010A674_locked_out != 2) {
        D_800D20A1_main[pad] = 0;
        D_800CBB6E_main[pad] = 0;
        D_800D5558_main[pad] = 0;
        D_800CDA7C_main[pad] = 0;
    }
    switch (D_8010A674_locked_out) {
        case 0:
            work->unk3E = 0;
            work->unk3C = 0;
            work->unk40 = 0;
            work->unk32 = 0;
            work->unk30 = 0;
            work->unk2E = 0;
            work->unk2C = 0;
            work->unk28 = 0;
            break;
        case 1:
            break;
        case 2:
            if (work->unk27 != 0 && work->unk3C == 0) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                func_80108A90_locked_out(object);
            }
            break;
        case 3:
            if (work->unk25 != 0) {
                canGrab = TRUE;
            }
            if (work->unk23 == 0) {
                func_800E5690_minigame(object, 0xF);
            }
            D_8010A180_locked_out = 0;
            break;
        case 4:
            if (work->unk23 == 0 && work->unk40 == 0) {
                func_8004AC5C_main(work->unk21 + 0x287, data->unk59);
                work->unk40 = 1;
            }
            if (WipeStatGet() != 0) {
                break;
            }
            if (work->unk23 == 0) {
                func_8001C258_main(object->model[0], 4, 4);
                func_8001C258_main(object->model[1], 4, 4);
                data->unk50 |= 0x600;
                work->unk3C = 6;
                return;
            }
            object->trans.x = D_8010A1C4_locked_out[D_8010A180_locked_out].x;
            object->trans.y = D_8010A1C4_locked_out[D_8010A180_locked_out].y;
            object->trans.z = D_8010A1C4_locked_out[D_8010A180_locked_out++].z;
            data->unk3C = 180.0f;
            data->unk40 = 0.0f;
            data->unk50 &= ~0x200;
            work->unk23 = 0;
            work->unk3E = 0;
            work->unk3C = 0;
            work->unk32 = 0;
            work->unk30 = 0;
            work->unk2E = 0;
            work->unk2C = 0;
            work->unk28 = 0;
            break;
        case 5:
            data->unk3C = 180.0f;
            break;
        case 6:
            if (work->unk23 != 0) {
                if (work->unk40 == 0) {
                    work->unk40 = 1;
                    func_8004AC5C_main(0x3D7, data->unk59);
                }
                func_8001C92C_main(D_8010A638_locked_out[work->unk3E].unk0E, 1.0f);
                D_8010A638_locked_out[work->unk3E].unk0C = 1;
                data->unk3C = 0.0f;
                func_8001C92C_main(object->model[0], 1.0f);
            }
            if (work->unk3C != 6) {
                func_8001C258_main(object->model[0], 4, 4);
                temp = object->model[0];
                object->model[0] = object->model[9];
                object->model[9] = temp;
                func_8001C258_main(object->model[0], 4, 0);
                func_800E5690_minigame(object, 0);
            }
            work->unk3C = 6;
            break;
        case 7:
            if (work->unk23 == 1) {
                func_80045ED0_main(work->unk1C);
                GwPlayer[data->unk59].bonusCoin += 10;
                GwPlayer[data->unk59].bonusCoin = work->unk24;
                func_800E5690_minigame(object, 0xD);
                func_80017954_main(object->model[0], 2, motions.values[work->unk21], work->unk29);
                work->unk23++;
            } else if (work->unk23 == 0) {
                GwPlayer[data->unk59].bonusCoin = work->unk24;
                work->unk23--;
            }
            break;
        case 8:
            if (data != NULL) {
                HuMemFree(data->unk158);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 9:
            return;
    }

    buttons = D_800D5558_main[pad];
    status = func_800E4A90_minigame(object);
    work->unk0C.x = object->trans.x;
    work->unk0C.y = object->trans.y;
    work->unk0C.z = object->trans.z;
    if (work->unk25 != 0) {
        D_800D5558_main[pad] &= ~0x4000;
    } else {
        HmfModelData[object->model[0]].unk06 = 0xFF;
    }
    entry = &D_8010A638_locked_out[work->unk3E];
    switch (work->unk3C) {
        case 0:
            if (status & 0x200000) {
                D_800D20A1_main[pad] = 0;
                D_800CBB6E_main[pad] = 0;
                D_800D5558_main[pad] = 0;
                D_800CDA7C_main[pad] = 0;
                data->unk40 = 0.0f;
                time = HmfModelData[object->model[0]].unk40;
                if (time >= D_800CCF58_main[HmfModelData[object->model[0]].unk02].unk02) {
                    work->unk26 = 0;
                    if (work->unk25 != 0) {
                        func_8001EED8_main(object->model[0], object->motion[0x26], 0);
                    }
                } else if (work->unk25 == 0) {
                    if (__builtin_fabs(time - 15.0) <= 1.0) {
                        canGrab = TRUE;
                    }
                }
            } else {
                work->unk26 = 0;
            }
            if (buttons & 0x8000) {
                if (work->unk25 == 0) {
                    if (work->unk26 == 0 && func_800E5690_minigame(object, 0x27)) {
                        func_8001C6A8_main(object->model[0], 0.0f);
                        work->unk26 = 1;
                    }
                } else {
                    canGrab = TRUE;
                }
            }
            if ((status & 0x8000) && work->unk25 != 0) {
                canGrab = TRUE;
            }
            func_800DDD94_minigame(object);
            if (work->unk25 != 0) {
                for (i = 0; i < 3; i++) {
                    if (D_8010A638_locked_out[i].unk10 == 0) {
                        continue;
                    }
                    block = D_8010A610_locked_out[work->unk25 - 1];
                    blockWork = block->data;
                    if (blockWork->unk02 != D_8010A67A_locked_out) {
                        continue;
                    }
                    if (func_80109E34_locked_out(&object->trans, &D_8010A638_locked_out[i].pos) >
                        data->unk48 + 20.0) {
                        continue;
                    }
                    func_8001C258_main(D_8010A638_locked_out[i].unk0E, 4, 0);
                    func_8001C258_main(D_8010A638_locked_out[i].unk0D, 4, 4);
                    Hu3DModelPosSet(D_8010A638_locked_out[i].unk0E, D_8010A638_locked_out[i].pos.x,
                                    D_8010A638_locked_out[i].pos.y, D_8010A638_locked_out[i].pos.z);
                    canGrab = TRUE;
                    func_8001C92C_main(D_8010A638_locked_out[i].unk0F, 1.0f);
                    func_8001C258_main(D_8010A638_locked_out[i].unk0F, 4, 0);
                    Hu3DModelPosSet(D_8010A638_locked_out[i].unk0F, D_8010A638_locked_out[i].pos.x,
                                    D_8010A638_locked_out[i].pos.y + 200.0, D_8010A638_locked_out[i].pos.z);
                    func_8004AC5C_main(0x3D9, 4);
                    D_8010A638_locked_out[i].unk10 = 0;
                    work->unk23 = 1;
                    work->unk3C = 1;
                    work->unk3E = i;
                    data->unk50 |= 0x200;
                    func_8001C258_main(block->model[0], 4, 4);
                    blockWork->unk00 = 4;
                }
            }
            func_80109858_locked_out(object, TRUE, canGrab);
            func_80106FBC_locked_out(object);

            pos.x = -610.5f;
            pos.y = 0.0f;
            pos.z = -607.0f;
            if (func_80109E34_locked_out(&pos, &object->trans) <= data->unk48 + 90.0) {
                angle = func_80109DBC_locked_out(pos.x - object->trans.x, pos.z - object->trans.z);
                object->trans.x = pos.x - (data->unk48 + 90.0) * sindf(angle);
                object->trans.z = pos.z - (data->unk48 + 90.0) * cosdf(angle);
            }

            pos.x = 610.5f;
            pos.y = 0.0f;
            pos.z = -607.0f;
            if (func_80109E34_locked_out(&pos, &object->trans) <= data->unk48 + 80.0) {
                angle = func_80109DBC_locked_out(pos.x - object->trans.x, pos.z - object->trans.z);
                object->trans.x = pos.x - (data->unk48 + 90.0) * sindf(angle);
                object->trans.z = pos.z - (data->unk48 + 90.0) * cosdf(angle);
            }
            break;
        case 1:
            func_800E5690_minigame(object, 1);
            data->unk3C = 180.0f;
            angle = func_80109DBC_locked_out(object->trans.x - (entry->pos.x + data->unk48 * 1.75),
                                             object->trans.z - (entry->pos.z + data->unk48 * 1.4));
            object->trans.x = work->unk0C.x - sindf(angle) * 4.0;
            object->trans.z = work->unk0C.z - cosdf(angle) * 4.0;
            pos.x = entry->pos.x + data->unk48 * 1.75;
            pos.y = entry->pos.y;
            pos.z = entry->pos.z + data->unk48 * 1.4;
            if (func_80109E34_locked_out(&object->trans, &pos) < 5.0) {
                func_8001C92C_main(entry->unk0E, 0.5f);
                func_8004AC5C_main(0x3D7, data->unk59);
                entry->unk0C = 1;
                data->unk3C = 180.0f;
                work->unk3C++;
            }
            break;
        case 2:
            if (data->unk3C < 250.0) {
                data->unk3C += 6.0;
            } else {
                func_800E5690_minigame(object, 0);
            }
            if (HmfModelData[entry->unk0E].unk40 >= D_800CCF58_main[HmfModelData[entry->unk0E].unk02].unk02) {
                work->unk3C++;
                work->unk40 = 30;
            }
            break;
        case 3:
            func_800E5690_minigame(object, 1);
            if (data->unk3C > 180.0) {
                data->unk3C += -3.0;
            }
            angle = data->unk3C;
            if (work->unk21 == 4 || work->unk21 == 5) {
                radius = 10.2f;
            } else {
                radius = 6.8f;
            }
            object->trans.x = radius * sindf(angle) + work->unk0C.x;
            object->trans.z = radius * cosdf(angle) + work->unk0C.z;
            if (--work->unk40 == 0) {
                func_8004AC5C_main(0x3D8, data->unk59);
                work->unk3C++;
            }
            break;
        case 4:
            func_8001C92C_main(entry->unk0E, 0.0f);
            func_8001C6A8_main(entry->unk0E, HmfModelData[entry->unk0E].unk40 - 1.5);
            if (HmfModelData[entry->unk0E].unk40 < 0.0) {
                func_8001C6A8_main(entry->unk0E, 0.0f);
                omVibrate(data->unk59, 2, 3, 10);
                entry->unk0C = 0;
                work->unk3C++;
            }
            break;
        case 5:
            return;
        case 6:
            if (work->unk23 == 0) {
                func_80109858_locked_out(object, TRUE, canGrab);
                func_80106FBC_locked_out(object);
            }
            break;
    }
    work->unk18 = status;
    if (work->unk3C != 0) {
        func_80088910_main(HmfModelData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
        func_800E4E30_minigame(object);
        func_800E5138_minigame(object);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
}

void func_801089F8_locked_out(omObjData *object, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 9; i < 12; i++) {
        if (HmfModelData[object->model[i]].unk18 & 4) {
            func_800E4C88_minigame(object, i, x, y, z, 0.0f, 0.0f);
            return;
        }
    }
}

u16 func_80108A90_locked_out(omObjData *object) {
    HuMtx4F unused; // Unused, but required for the stack layout to match.
    func_800E1BA8_minigame_ObjData *data;
    LockedOutPlayerWork *work;
    LockedOutBlockWork *blockWork;
    LockedOutUnkStruct *entry;
    omObjData *block;
    omObjData *holder;
    s16 pad;
    u8 index;
    s32 i;
    f32 angle;
    u16 buttons; // Never assigned; the original returns an uninitialized value.

    func_801090FC_locked_out(object, &data, &work);
    pad = data->unk57;
    func_800E4A90_minigame(object);
    switch (work->unk28) {
        case 0:
            if (work->unk25 != 0) {
                D_800D5558_main[pad] |= 0x8000;
            }
            work->unk2C = 0;
            work->unk2E = 0;
            index = (s32)((f32)func_80109D70_locked_out() * 1.52587890625e-05 * D_8010A676_locked_out);
            block = D_8010A610_locked_out[index];
            blockWork = block->data;
            if (blockWork->unk02 != D_8010A67A_locked_out) {
                if ((s32)((f32)func_80109D70_locked_out() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
                    break;
                }
                work->unk2E = 1;
            }
            work->unk2C = index;
            work->unk28++;
            break;
        case 1:
            block = D_8010A610_locked_out[work->unk2C];
            blockWork = block->data;
            if (work->unk25 != 0) {
                work->unk28 = 2;
                break;
            }
            if (blockWork->unk00 == 1) {
                holder = blockWork->unk14;
                angle = func_80109DBC_locked_out(holder->trans.x - object->trans.x, holder->trans.z - object->trans.z);
                if (func_80109E34_locked_out(&object->trans, &holder->trans) < data->unk48 * 2.2 + data->unk64) {
                    D_800D5558_main[pad] |= 0x4000;
                }
                for (i = 0; i < D_8010A678_locked_out; i++) {
                    blockWork = D_8010A610_locked_out[i]->data;
                    if (blockWork->unk02 == D_8010A67A_locked_out && blockWork->unk00 == 0) {
                        break;
                    }
                }
                if (i < D_8010A678_locked_out) {
                    if ((s32)((f32)func_80109D70_locked_out() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
                        work->unk28 = 0;
                    }
                }
            } else if (blockWork->unk00 == 4) {
                work->unk28 = 0;
                break;
            } else {
                angle = func_80109DBC_locked_out(block->trans.x - object->trans.x, block->trans.z - object->trans.z);
                if (func_80109E34_locked_out(&object->trans, &block->trans) <= data->unk48 + blockWork->unk04 + 2.0 &&
                    __builtin_fabs((f64)(angle - data->unk3C)) < 40.0) {
                    D_800D5558_main[pad] |= 0x8000;
                }
            }
            D_800CBB6E_main[pad] = (work->unk22 * 6.0 + 46.0) * sindf(angle);
            D_800D20A1_main[pad] = (work->unk22 * 6.0 + 46.0) * -cosdf(angle);
            break;
        case 2:
            if (work->unk25 != work->unk2C + 1) {
                D_800D5558_main[pad] |= 0x8000;
                work->unk28 = 1;
                break;
            }
            work->unk30 = (s32)((f32)func_80109D70_locked_out() * 1.52587890625e-05 * (s16)(D_8010A676_locked_out / 3));
            if (D_8010A638_locked_out[work->unk30].unk10 == 0) {
                break;
            }
            work->unk28++;
        case 3:
            if (work->unk25 == 0) {
                work->unk28 = 1;
            }
            entry = &D_8010A638_locked_out[work->unk30];
            if (entry->unk10 == 0) {
                work->unk28 = 2;
            }
            angle = func_80109DBC_locked_out(entry->pos.x - object->trans.x, entry->pos.z - object->trans.z);
            D_800CBB6E_main[pad] = (work->unk22 * 6.0 + 46.0) * sindf(angle);
            D_800D20A1_main[pad] = (work->unk22 * 6.0 + 46.0) * -cosdf(angle);
            break;
        case 4:
            break;
    }
    if (work->unk2E != 0) {
        if ((s32)((f32)func_80109D70_locked_out() * 1.52587890625e-05 * 100.0) < work->unk22 * 5 + 5) {
            work->unk28 = 0;
        }
    }
    return buttons;
}

void func_801090FC_locked_out(omObjData *object, func_800E1BA8_minigame_ObjData **data, LockedOutPlayerWork **arg2) {
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

void func_80109444_locked_out(omObjData *object) {
    LockedOutBlockWork *work;
    Vec pos;
    f32 angle;

    work = object->data;
    func_8001C258_main(object->model[1], 4, 0);
    switch (work->unk00) {
        case 0:
            work->unk01 = 1;
            break;
        case 2:
            work->unk01 = 0;
            work->unk03--;
            if (work->unk03 == 0) {
                work->unk00 = 3;
            }
        case 3:
            work->unk01 = 1;
            work->unk08.y += -2.0f;
            object->trans.x += work->unk08.x;
            object->trans.y += work->unk08.y;
            object->trans.z += work->unk08.z;
            if (object->trans.y < 50.0) {
                work->unk00 = 0;
                object->trans.y = 50.0f;
                work->unk08.y = 6.0f;
            }
            break;
        case 1:
        case 4:
            func_8001C258_main(object->model[1], 4, 4);
            work->unk01 = 0;
            break;
    }

    pos.x = -610.5f;
    pos.y = 0.0f;
    pos.z = -607.0f;
    if (func_80109E34_locked_out(&pos, &object->trans) <= work->unk04 + 90.0) {
        angle = func_80109DBC_locked_out(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - (work->unk04 + 90.0) * sindf(angle);
        object->trans.z = pos.z - (work->unk04 + 90.0) * cosdf(angle);
    }

    pos.x = 610.5f;
    pos.y = 0.0f;
    pos.z = -607.0f;
    if (func_80109E34_locked_out(&pos, &object->trans) <= work->unk04 + 80.0) {
        angle = func_80109DBC_locked_out(pos.x - object->trans.x, pos.z - object->trans.z);
        object->trans.x = pos.x - (work->unk04 + 90.0) * sindf(angle);
        object->trans.z = pos.z - (work->unk04 + 90.0) * cosdf(angle);
    }

    if (object->trans.x < -600.0) {
        object->trans.x = -600.0f;
    }
    if (object->trans.x > 600.0) {
        object->trans.x = 600.0f;
    }
    if (object->trans.z < -575.0) {
        object->trans.z = -575.0f;
    }
    if (object->trans.z > 575.0) {
        object->trans.z = 575.0f;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    func_80109858_locked_out(object, 0, 0);
    func_80106FBC_locked_out(object);
}

void func_80109858_locked_out(omObjData *object, u8 isPlayer, u8 canGrab) {
    func_800E1BA8_minigame_ObjData *data;
    LockedOutPlayerWork *playerWork;
    LockedOutBlockWork *selfWork;
    LockedOutBlockWork *work;
    omObjData *block;
    Vec hookPos;
    f32 radius;
    f32 dist;
    f32 angle;
    f32 pushAngle;
    s32 i;

    selfWork = NULL;
    if (D_8010A678_locked_out == 0) {
        return;
    }
    if (isPlayer) {
        func_801090FC_locked_out(object, &data, &playerWork);
        radius = data->unk48;
    } else {
        selfWork = object->data;
        radius = selfWork->unk04;
        canGrab = FALSE;
    }

    if (canGrab && playerWork->unk25 != 0) {
        block = D_8010A610_locked_out[playerWork->unk25 - 1];
        work = block->data;
        func_8001C258_main(block->model[0], 0x4000, 0);
        work->unk08.x = sindf(data->unk3C) * 4.0;
        work->unk08.y = 15.0f;
        work->unk08.z = cosdf(data->unk3C) * 4.0;
        func_80109E88_locked_out(object->model[0], "item_hook", HmfModelData[object->model[0]].unk40, &hookPos);
        block->trans.x = work->unk08.x * 20.0f + hookPos.x;
        block->trans.y = hookPos.y + 50.0;
        block->trans.z = work->unk08.z * 20.0f + hookPos.z;
        playerWork->unk25 = 0;
        if (work->unk00 != 4) {
            work->unk00 = 2;
        }
        work->unk01 = 0;
        work->unk03 = 5;
        canGrab = FALSE;
    }

    for (i = 0; i < D_8010A676_locked_out; i++) {
        block = D_8010A610_locked_out[i];
        work = block->data;
        if (work == selfWork) {
            continue;
        }
        dist = func_80109E34_locked_out(&object->trans, &block->trans);
        if (!(dist < radius + work->unk04 + 24.0)) {
            continue;
        }
        angle = func_80109DBC_locked_out(block->trans.x - object->trans.x, block->trans.z - object->trans.z);
        if (dist < radius + work->unk04 && (work->unk00 != 1 || work->unk00 != 4)) {
            pushAngle = func_80109DBC_locked_out(object->trans.x - block->trans.x, object->trans.z - block->trans.z);
            block->trans.x = object->trans.x - (radius + work->unk04) * sindf(pushAngle);
            block->trans.z = object->trans.z - (radius + work->unk04) * cosdf(pushAngle);
        }
        if (!canGrab || playerWork->unk25 != 0 || work->unk01 == 0) {
            continue;
        }
        angle -= data->unk3C;
        while (angle < -180.0) {
            angle += 360.0;
        }
        while (angle > 180.0) {
            angle -= 360.0;
        }
        if (__builtin_fabs((f64)angle) < 45.0) {
            func_8001EF6C_main(block->model[0], object->model[0], "item_hook");
            func_8001C258_main(block->model[0], 0x4000, 0x4000);
            func_8004AC5C_main(0x3D6, data->unk59);
            playerWork->unk25 = i + 1;
            work->unk00 = 1;
            work->unk01 = 0;
            work->unk14 = object;
        }
    }
}

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
