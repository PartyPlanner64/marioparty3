#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"

extern u32 D_80109148_eatsa_pizza;
extern u8 D_80109101_eatsa_pizza[4][2];
extern u8 D_80109108_eatsa_pizza;
extern u8 D_8010910C_eatsa_pizza[4];
extern s16 D_80109110_eatsa_pizza[4][3];
extern f32 D_80109128_eatsa_pizza[8];
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern f32 D_80109358_eatsa_pizza[4][4];
extern f32 D_80109390_eatsa_pizza;
extern f32 D_80109398_eatsa_pizza[4][4];
extern f32 D_801093D8_eatsa_pizza;
extern s16 D_80109278_eatsa_pizza;
extern s16 D_8010927A_eatsa_pizza[2];
extern s16 D_8010927E_eatsa_pizza[2];
extern s16 D_80109282_eatsa_pizza[1];
extern s16 D_80109284_eatsa_pizza;
extern s16 D_80109288_eatsa_pizza;
extern s16 D_8010928A_eatsa_pizza[3];
extern s16 D_8010928E_eatsa_pizza;
extern s16 D_80109298_eatsa_pizza[0x10];
extern u16 D_801092B8_eatsa_pizza[4];
extern s16 D_801092C0_eatsa_pizza[2][5][7];
extern u16 D_8010934C_eatsa_pizza[2];
extern s16 D_80109350_eatsa_pizza;
extern s32 D_80109138_eatsa_pizza;
extern s16 D_8010913A_eatsa_pizza;
extern u16 D_8010913C_eatsa_pizza;
extern s32 D_80109140_eatsa_pizza;
extern s16 D_80109144_eatsa_pizza;
extern s32 D_80109260_eatsa_pizza[2];

// Per-player work allocated in func_80106504_eatsa_pizza, stored at ObjData->unk158
typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 radius;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
} Work; // Size 0x38

extern Work *D_80109268_eatsa_pizza[4][2];

void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
f32 atan2df(f32, f32);
void func_800E12EC_minigame(omObjData *arg0, f32 arg1);
void func_800E1328_minigame(omObjData *arg0, f32 arg1);
void func_800E1334_minigame(omObjData *arg0, f32 arg1);
void func_800E1340_minigame(omObjData *arg0, f32 arg1);
u32 func_800E4A90_minigame(void);
s32 func_800E2250_minigame(omObjData *arg0, s32 arg1, s32 arg2);
s32 func_80107E6C_eatsa_pizza(omObjData *object);
void func_801078C4_eatsa_pizza(omObjData *object);
void func_80107A64_eatsa_pizza(omObjData *object);
void func_80106084_eatsa_pizza(omObjData *object);
void func_8010679C_eatsa_pizza(omObjData *object);
void func_801083A8_eatsa_pizza(omObjData *arg0, func_800E1BA8_minigame_ObjData **arg1, void **arg2);
s16 HuSprAnimRead(void *data);
void *func_801090B4_eatsa_pizza(s16 arg0, s16 arg1);
void func_801087DC_eatsa_pizza(omObjData *object);
void func_80108C50_eatsa_pizza(omObjData *);
s16 func_80108FA4_eatsa_pizza(s32 arg0);
s16 func_80108FEC_eatsa_pizza(s16 arg0, s16 arg1);
s16 func_80108E48_eatsa_pizza(u16 arg0, f32 *arg1);
s32 func_80108F4C_eatsa_pizza(void);
s32 func_801070E8_eatsa_pizza(omObjData *object);
omObjData *func_80045F1C_main(u32 arg0, s16 arg1, s16 arg2);

void func_80105AF4_eatsa_pizza(omObjData *object);
void func_801083BC_eatsa_pizza(void);
void func_80108470_eatsa_pizza(omObjData *object);
void func_801084F8_eatsa_pizza(omObjData *object);
void func_80105C64_eatsa_pizza(HuMtx4F src, HuMtx4F dst);
void func_80105FF0_eatsa_pizza(void);
void func_80106504_eatsa_pizza(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag);
void func_800E1490_minigame(s32 arg0);
void func_800E1804_minigame(void);
void func_80021BE0_main(void *arg0, u16 arg1);
s32 func_8000B638_main(void);

extern void *D_800EBEB0_minigame;

void func_801059A0_eatsa_pizza(void) {
    omObjData *obj;
    u8 camIndex;

    Hu3DAnimInit(1);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    omInitObjMan(0x10, 0);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 5.0f, 80.0f, 4000.0f);
    func_800E1804_minigame();
    func_80105AF4_eatsa_pizza(obj);
    func_801083BC_eatsa_pizza();
    func_80105FF0_eatsa_pizza();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105AF4_eatsa_pizza(omObjData *object) {
    HuCamera *camera;
    f32 sinFov;
    f32 cosFov;

    CZoom = 2000.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    omOutView(object);

    camera = gCameraList;
    sinFov = sindf(camera->fov / 2.0);
    cosFov = cosdf(camera->fov / 2.0);
    D_801093D8_eatsa_pizza = sinFov / cosFov;
    guMtxL2F(D_80109358_eatsa_pizza, &camera->mtxs[0].lookAtMtx);
    guMtxL2F(D_80109398_eatsa_pizza, &camera->mtxs[0].lookAtMtx);
    func_80105C64_eatsa_pizza(D_80109398_eatsa_pizza, D_80109398_eatsa_pizza);
}

void func_80105BE4_eatsa_pizza(HuMtx4F mtx, f32 x, f32 y, f32 z, f32 *dst) {
    dst[0] = ((x * mtx[0][0]) + (y * mtx[1][0])) + (z * mtx[2][0]);
    dst[1] = ((x * mtx[0][1]) + (y * mtx[1][1])) + (z * mtx[2][1]);
    dst[2] = ((x * mtx[0][2]) + (y * mtx[1][2])) + (z * mtx[2][2]);
}

void func_80105C64_eatsa_pizza(HuMtx4F src, HuMtx4F dst) {
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

        func_80105BE4_eatsa_pizza(dst, -mtx[3][0], -mtx[3][1], -mtx[3][2], dstRow3);
    }
}

void func_80105E54_eatsa_pizza(f32 *arg0, f32 *dst) {
    f32 mtx[4][4];
    f32 depth;
    f32 scale;

    guTranslateF(mtx, arg0[0], arg0[1], arg0[2]);
    guMtxCatF(mtx, D_80109358_eatsa_pizza, mtx);
    depth = mtx[3][2] * D_801093D8_eatsa_pizza;
    scale = __builtin_fabsf(depth);
    if (scale == 0.0) {
        return;
    }
    dst[0] = mtx[3][0] * 160.0f / scale / 1.3333334f;
    dst[1] = -mtx[3][1] * 120.0f / scale;
}

void func_80105F24_eatsa_pizza(f32 x, f32 y, f32 z, f32 *dst) {
    f32 depth = z + D_80109390_eatsa_pizza;
    f32 scale = __builtin_fabsf(depth * D_801093D8_eatsa_pizza);
    f32 mtx[4][4];

    guTranslateF(mtx, ((x + x) * scale * 1.3333334f) / 320.0f, -((y + y) * scale / 240.0f), depth);
    guMtxCatF(mtx, D_80109398_eatsa_pizza, mtx);
    dst[0] = mtx[3][0];
    dst[1] = mtx[3][1];
    dst[2] = mtx[3][2];
}

void func_80105FF0_eatsa_pizza(void) {
    s32 i;

    func_800E18D8_minigame();
    D_800EC280_minigame = 0;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 0xB, 0x32, -1, func_80106084_eatsa_pizza);
    }
}

void func_80106084_eatsa_pizza(omObjData *object) {
    u8 player;
    u8 group;
    s8 character;
    s32 model;
    s32 motion;
    func_800E1BA8_minigame_ObjData *data;
    Work *work;

    player = D_80109101_eatsa_pizza[D_80109108_eatsa_pizza][0];
    group = GwPlayer[player].group;
    character = (s8)GwPlayer[player].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A1790_main[character][0];
    func_800E19F0_minigame(1);
    func_80106504_eatsa_pizza(object, model, motion, player, 0x2D9);

    data = object->data;
    object->trans.x = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][0];
    object->trans.y = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][1];
    object->trans.z = D_80109110_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]][2];
    object->rot.x = 90.0f;
    object->rot.z = D_80109128_eatsa_pizza[group * 2 + D_8010910C_eatsa_pizza[group]];
    data->unk3C = object->rot.z + 180.0;
    object->scale.x = object->scale.y = object->scale.z = data->unkAC * 0.15;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);

    work = data->unk158;
    work->unk30 = player;
    work->unk32 = group;
    work->unk33 = D_8010910C_eatsa_pizza[group];
    work->unk18 = work->unk14 = data->unk3C;
    work->unk35 = GwPlayer[player].stat & 1;
    work->unk31 = GwPlayer[player].cpu_difficulty;
    work->unk2C = model | 0x4E;
    work->unk34 = 0;
    work->unk36 = 0;
    work->radius = 11.0f;
    work->pos.x = object->trans.x;
    work->pos.y = object->trans.y;
    work->pos.z = object->trans.z;
    work->unk26 = -1;
    work->unk24 = -1;
    work->unk28 = 8;
    work->unk2A = 0;
    D_80109268_eatsa_pizza[group][D_8010910C_eatsa_pizza[group]] = work;
    object->model[3] = func_8000B108_main(3, 0x2DD);
    object->model[4] = func_8000B108_main(4, 0x2DD);
    object->model[6] = func_8000B108_main(5, 0x2DD);
    object->model[5] = func_8000B108_main(6, 0x2DD);
    object->model[7] = func_8000B108_main(8, 0x2DD);
    object->model[8] = func_8000B108_main(7, 0x2DD);
    object->func = func_8010679C_eatsa_pizza;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 0x10, func_80017BB8_main(character, 0x3E), 1, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x4E), 2, 0x78);
    func_800E5A00_minigame(object, 0xE, func_80017BB8_main(character, 0x3A), 2, 0x3C);
    func_800E5690_minigame(object, 0);
    D_80109108_eatsa_pizza++;
    D_8010910C_eatsa_pizza[group]++;
}

void func_80106504_eatsa_pizza(omObjData *object, s32 arg1, s32 arg2, u16 player, u16 tag) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;
    u32 character;
    f32 zero;
    func_800E1BA8_minigame_UnkE8_ObjData *entry;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    memset(data->unkE8, 0, object->mtncnt * 3 * sizeof(s32));
    data->unk158 = HuMemAllocTag(0x38, TAG_OVERLAY);
    memset(data->unk158, 0, 0x38);

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

void func_8010679C_eatsa_pizza(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    Work *work;
    s32 mode;
    s32 input = 0;
    s32 frameStatus;
    s32 cutResult = 0;
    s16 dx;
    s16 dy;
    u8 player;
    f32 distance;
    f32 angle;
    f32 delta;
    f32 currentAngle;
    f32 screenPos[11];
    s32 i;

    data = object->data;
    work = data->unk158;
    currentAngle = data->unk3C;
    frameStatus = func_800E4A90_minigame();
    work->unk20 = (s16)(s32)(work->pos.x + 160.0f);
    work->unk20 >>= 5;
    work->unk22 = (s16)(s32)(work->pos.y + 120.0f);
    work->unk22 = (work->unk22 - 8) >> 5;
    if (work->unk20 >= 5) {
        work->unk20 -= 5;
    }

    mode = D_80109350_eatsa_pizza;
    switch (mode) {
        case 0:
        case 1:
            break;
        case 2:
            work = data->unk158;
            player = data->unk57;
            if ((frameStatus & 0xFFFF) == 2) {
                func_800E5690_minigame(object, 0x10);
            }
            if (work->unk35 == 0) {
                s32 pad = (s8)player;
                u32 packedInput = func_800E2250_minigame(object, D_800CBB6E_main[pad], D_800D20A1_main[pad]);
                dx = packedInput >> 16;
                dy = packedInput;
                input = D_800D5558_main[pad];
                work->unk24 = work->unk20;
                work->unk26 = work->unk22;
            } else {
                input = func_801070E8_eatsa_pizza(object);
                dy = 0x30;
                dx = 0x30;
            }

            work->unk0C = work->pos.x;
            work->unk10 = work->pos.y;
            if (__builtin_fabs((f64)dx) < 16.0) {
                dx = 0;
            }
            if (__builtin_fabs((f64)dy) < 16.0) {
                dy = 0;
            }
            distance = sqrtf((f32)(dx * dx + dy * dy)) / 6.0;
            data->unk40 = distance;
            if (distance > 16.0) {
                data->unk40 = 16.0f;
            }
            if (data->unk40 != 0.0) {
                if ((frameStatus & 0xFFFF) == 2) {
                    func_800E5690_minigame(object, 0x10);
                }
                if (work->unk35 == 0) {
                    angle = atan2df((f32)dx, (f32) - dy) + 180.0;
                } else {
                    angle = work->unk18;
                }
                if (angle >= 360.0) {
                    angle -= 360.0;
                }
                if (angle == currentAngle) {
                    data->unk3C = currentAngle;
                } else {
                    delta = angle - currentAngle;
                    if (delta < -180) {
                        if (delta < 0) {
                            goto rotatePositive;
                        }
                    }
                    if (delta < 180) {
                        if (delta > 0) {
                            goto rotatePositive;
                        }
                    }
                    goto rotateNegative;

                rotatePositive:
                    currentAngle += 20.0f;
                    delta = angle - currentAngle;
                    if (delta > -180) {
                        if (delta < 0) {
                            currentAngle = angle;
                            goto positiveClampDone;
                        }
                    }
                    if (((angle - currentAngle) > 180) && ((angle - currentAngle) > 0)) {
                        currentAngle = angle;
                    }
                positiveClampDone:
                    if (currentAngle > 360.0) {
                        currentAngle -= 360.0;
                    }
                    data->unk3C = currentAngle;
                    goto rotateDone;

                rotateNegative:
                    currentAngle -= 20.0f;
                    delta = angle - currentAngle;
                    if (delta < -180) {
                        if (delta < 0) {
                            currentAngle = angle;
                            goto negativeClampDone;
                        }
                    }
                    if (((angle - currentAngle) < 180) && ((angle - currentAngle) > 0)) {
                        currentAngle = angle;
                    }
                negativeClampDone:
                    if (currentAngle < 0.0) {
                        currentAngle += 360.0;
                    }
                    data->unk3C = currentAngle;
                rotateDone:;
                }
                work->unk14 = currentAngle;
                object->rot.z = currentAngle - 180.0;
                if (HmfModelData[object->model[0]].motTime == 0.0) {
                    cutResult = 1;
                }
                work->unk36 = 4;
                work->pos.x -= sindf(angle) * data->unk40 * 0.1;
                work->pos.y -= cosdf(angle) * data->unk40 * 0.1;
            }
            if (work->unk37 != 0) {
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
                work->unk37--;
            } else {
                Hu3DMotionSpeedSet(object->model[0], data->unk40 * 0.075);
            }
            break;
        case 3:
        case 4:
            func_800E5690_minigame(object, 0);
            Hu3DMotionSpeedSet(object->model[0], 1.0f);
            work->unk36 = 2;
            break;
        case 5:
            if (work->unk36 != 0) {
                if (work->unk34 != 0) {
                    func_800E5690_minigame(object, 0xD);
                    func_80045F1C_main(work->unk2C, (work->unk32 * 5 << 3) + 0x2C, work->unk30);
                    GwPlayer[data->unk59].bonusCoin += 10;
                } else {
                    func_800E5690_minigame(object, 0xE);
                }
            }
            break;
        case 6:
            if (data != NULL) {
                HuMemFree(data->unkE8);
                HuMemFree(data->unk158);
                HuMemFree(data);
                object->data = NULL;
                object->func = NULL;
            }
            return;
        case 7:
            return;
    }

    if (input & A_BUTTON) {
        i = func_80107E6C_eatsa_pizza(object);
        if ((i & 0xFFFF) != 0) {
            cutResult = i;
        }
        if (work->unk37 == 0) {
            work->unk37 = 0x10;
        }
    }
    if ((cutResult & 0xFFFF) == 1) {
        CharFXPlay(0x1F, GwPlayer[data->unk59].chr);
    } else if ((cutResult & 0xFFFF) == 3) {
        CharFXPlay(0x350, GwPlayer[data->unk59].chr);
    } else if ((cutResult & 0xFFFF) == 2) {
        CharFXPlay(0x347, GwPlayer[data->unk59].chr);
    }
    if (work->unk36 != 0) {
        work->unk36--;
        func_801078C4_eatsa_pizza(object);
        func_80107A64_eatsa_pizza(object);
    }
    if (work->unk32 == 0) {
        if (work->pos.x < -144.0f)
            work->pos.x = -144.0f;
        if (work->pos.x > -16.0f)
            work->pos.x = -16.0f;
    } else {
        if (work->pos.x < 16.0f)
            work->pos.x = 16.0f;
        if (work->pos.x > 144.0f)
            work->pos.x = 144.0f;
    }
    if (work->pos.y < -104.0f)
        work->pos.y = -104.0f;
    if (work->pos.y > 104.0f)
        work->pos.y = 104.0f;
    func_80105F24_eatsa_pizza(work->pos.x, work->pos.y, work->pos.z, screenPos);
    object->trans.x = screenPos[0];
    object->trans.y = screenPos[1];
    func_800E4E30_minigame(object);
}

s32 func_801070E8_eatsa_pizza(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    Work *work;
    u16 *mask;
    s32 random;
    s16 x;
    s16 y;
    u16 selfX;
    u16 selfY;
    s16 targetX;
    s16 targetY;
    s16 otherX;
    s16 otherY;
    s32 offsetX;
    s32 offsetY;
    s32 scanIndex;
    s32 sign;
    u16 input;
    f32 angle;
    f32 bestDistance;
    f32 xPos;
    f32 targetPixelX;
    f32 targetPixelY;
    f32 dx;
    f32 dy;
    f32 distance;
    s16 found = 0;

    bestDistance = 65536.0f;
    input = 0;
    func_801083A8_eatsa_pizza(object, &data, (void **)&work);
    random = func_80108F4C_eatsa_pizza();
    if (random % (9 - (work->unk31 * 2)) == 0) {
        input = A_BUTTON;
    }

    if (work->unk2A >= 4) {
        random = func_80108F4C_eatsa_pizza();
        angle = work->unk18 + 60.0 - (((random & 1) * 15) << 3);
        if (angle > 360.0) {
            angle -= 360.0;
        }
        if (angle < 0.0) {
            angle += 360.0;
        }
        work->unk18 = angle;
        random = func_80108F4C_eatsa_pizza();
        work->unk28 = (random & 7) + 5;
    }

    if (data->unk3C == work->unk18) {
        work->unk28--;
        if (work->unk28 != 0) {
            return input;
        }
    } else {
        return input;
    }
    if (work->unk32 != 0) {
        xPos = work->pos.x;
    } else {
        xPos = work->pos.x + 160.0f;
    }
    random = func_80108F4C_eatsa_pizza();
    angle = data->unk3C + ((f32)(random - 0x8000) * 3.0517578125e-05) * 20.0;
    xPos -= sindf(angle) * 4.0;
    angle = work->pos.y + 120.0f - (cosdf(angle) * 4.0);

    if (work->unk24 == -1 || work->unk26 == -1) {
        work->unk24 = work->unk20;
        work->unk26 = work->unk22;
    }
    selfX = work->unk24;
    selfY = work->unk26;

    if (D_801092C0_eatsa_pizza[work->unk32][(s16)selfX][(s16)selfY] != 0) {
        mask = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[work->unk32], 0);
        for (offsetY = 0; offsetY < 32; offsetY++) {
            y = (selfY << 5) + (s16)(offsetY + 8);
            for (offsetX = 0; offsetX < 32; offsetX++) {
                x = (selfX << 5) + offsetX;
                scanIndex = y * 160;
                if (mask[(u16)(scanIndex + x)] & 1) {
                    dx = xPos - x;
                    dy = angle - y;
                    distance = sqrtf((dx * dx) + (dy * dy));
                    if (bestDistance < distance) {
                        continue;
                    }
                    random = func_80108F4C_eatsa_pizza();
                    bestDistance = distance;
                    work->unk28 = (random & 3) + 3;
                    targetPixelX = x;
                    targetPixelY = y;
                }
            }
        }
    } else {
        random = func_80108F4C_eatsa_pizza();
        scanIndex = random & 1;
        while (++scanIndex < 7) {
            otherX = D_80109268_eatsa_pizza[work->unk32][work->unk33 ^ 1]->unk24;
            otherY = D_80109268_eatsa_pizza[work->unk32][work->unk33 ^ 1]->unk26;
            for (offsetX = scanIndex; offsetX >= -scanIndex; offsetX--) {
                offsetY = scanIndex - __builtin_abs(offsetX);
                for (sign = 0; sign < 2; sign++, offsetY = -offsetY) {
                    x = selfX - offsetX;
                    y = selfY - offsetY;
                    if ((x < 0) | (y < 0) || (x >= 5) | (y >= 7) ||
                        ((x == otherX) & (y == otherY))) {
                        continue;
                    }

                    dx = xPos - (x * 32) + 16.0f;
                    dy = angle - (y * 32) + 24.0f;
                    distance = sqrtf((dx * dx) + (dy * dy));
                    if (bestDistance < distance) {
                        continue;
                    }
                    {
                        s16 tileCount = D_801092C0_eatsa_pizza[work->unk32][x][y];

                        if (tileCount != 0) {
                            bestDistance = distance;
                            found = tileCount;
                            targetX = x;
                            targetY = y;
                        }
                    }
                }
            }
            if (found != 0) {
                break;
            }
        }

        if (found != 0) {
            work->unk24 = targetX;
            work->unk26 = targetY;
        } else {
            work->unk24 = otherX;
            work->unk26 = otherY;
        }
        targetPixelX = (targetX * 32) + 16;
        targetPixelY = (targetY * 32) + 24;
        random = func_80108F4C_eatsa_pizza();
        work->unk28 = (random & 7) + 5;
    }

    angle = atan2df(xPos - targetPixelX, angle - targetPixelY);
    if (angle > 360.0) {
        angle -= 360.0;
    }
    if (angle < 0.0) {
        angle += 360.0;
    }
    work->unk18 = angle;
    return input;
}

void func_801078C4_eatsa_pizza(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data;
    Work *self;
    func_800E1BA8_minigame_ObjData *otherData;
    Work *other;
    f32 selfRadius;
    f32 dx;
    f32 dy;
    f32 otherRadius;
    f32 dist;
    s32 i;
    s32 j;
    s32 count = 0;

    func_801083A8_eatsa_pizza(arg0, &data, (void **)&self);
    selfRadius = self->radius;
    for (i = 0, j = 0; i < 4; i++, j++) {
        if (data->unk59 == j) {
            continue;
        }
        func_801083A8_eatsa_pizza(D_800EC598_minigame[i], &otherData, (void **)&other);
        dx = other->pos.x - self->pos.x;
        dy = other->pos.y - self->pos.y;
        otherRadius = other->radius;
        dist = sqrtf((dx * dx) + (dy * dy));
        if (dist < selfRadius + otherRadius) {
            if (dist != 0.0) {
                dx /= dist;
                dy /= dist;
            }
            dist = selfRadius + otherRadius - dist;
            self->pos.x -= dx * dist;
            self->pos.y -= dy * dist;
            count++;
        }
    }
    if (count != 0) {
        self->unk2A += 1;
    } else {
        self->unk2A = 0;
    }
}

void func_80107A64_eatsa_pizza(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    Work *work;
    u8 *map;
    f32 x;
    f32 y;
    s16 yMin;
    s16 yMax;
    s16 xMin;
    s16 xMax;
    f32 bestX = 65535.0f;
    f32 bestY = 65535.0f;
    f32 best = 65535.0f;
    s32 count = 0;
    s32 row;
    s32 col;
    f32 dx;
    f32 dy;
    f32 dist;

    func_801083A8_eatsa_pizza(object, &data, (void **)&work);
    map = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[work->unk32], 0);
    x = work->pos.x + 160.0f;
    y = work->pos.y + 120.0f;
    yMin = y - 16.0f;
    if (yMin < 0) {
        yMin = 0;
    }
    yMax = y + 16.0f;
    if (yMax > 240) {
        yMax = 240;
    }
    xMin = x - 16.0f;
    if (xMin < 0) {
        xMin = 0;
    }
    xMax = x + 16.0f;
    if (xMax > 320) {
        xMax = 320;
    }
    if (work->unk32 == 1) {
        x -= 160.0f;
        xMin -= 160;
        xMax -= 160;
    }
    for (row = yMin; row <= yMax; row++) {
        for (col = xMin; col <= xMax; col++) {
            u8 pixel = map[(row * 160 + col) >> 1];
            if ((col & 1 ? pixel & 0xF0 : pixel & 0xF) == 0) {
                continue;
            }
            dx = col - x;
            dy = row - y;
            dist = sqrtf((dx * dx) + (dy * dy));
            if (best < dist) {
                continue;
            }
            best = dist;
            bestX = col - 160 + work->unk32 * 160;
            bestY = row - 120;
            count++;
        }
    }
    if (count != 0 && best < work->radius) {
        dx = bestX - work->unk0C;
        dy = bestY - work->unk10;
        dist = sqrtf((dx * dx) + (dy * dy));
        if (dist != 0.0) {
            dx /= dist;
            dy /= dist;
            work->pos.x = bestX - dx * work->radius;
            work->pos.y = bestY - dy * work->radius;
        }
    }
}

#if NONMATCHING
s16 func_80107E6C_eatsa_pizza(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    Work *work;
    u16 *mask;
    u16 color;
    u8 *image;
    u8 nibble;
    u8 *pattern;
    u8 patternNibble;
    s32 x;
    s32 y;
    s32 centerX;
    s32 centerY;
    s32 maskIndex;
    s32 otherIndex;
    s32 column;
    s16 removed;
    s16 yMin;
    s16 yMax;
    s16 xMin;
    s16 xMax;
    s32 count;
    u8 patternPixel;
    s16 result;

    result = 0;
    func_801083A8_eatsa_pizza(object, &data, (void **)&work);
    mask = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[work->unk32], 0);
    image = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[work->unk32], 0);
    pattern = func_801090B4_eatsa_pizza(D_80109282_eatsa_pizza[0], 0);

    if (work->unk32 != 0) {
        centerX = work->pos.x - sindf(data->unk3C) * 2.0;
    } else {
        centerX = work->pos.x + 160.0 - sindf(data->unk3C) * 2.0;
    }
    centerY = work->pos.y + 120.0 - cosdf(data->unk3C) * 2.0;

    yMin = centerY - 16;
    if (yMin < 0) {
        yMin = 0;
    }
    yMax = centerY + 16;
    if (yMax >= 241) {
        yMax = 240;
    }
    xMin = centerX - 16;
    if (xMin < 0) {
        xMin = 0;
    }
    xMax = centerX + 16;
    if (xMax >= 321) {
        xMax = 320;
    }
    if (xMin & 1) {
        xMin++;
    }

    for (y = yMin, count = 0; y < yMax; y++, count++) {
        for (x = xMin, column = 0; x < xMax; x++, column++) {
            maskIndex = ((y * 160) + x) >> 1;
            if (y & 1) {
                otherIndex = ((y - 1) * 160 + x) >> 1;
            } else {
                otherIndex = ((y + 1) * 160 + x) >> 1;
            }
            if (mask[(maskIndex << 1) + (x & 1)] & 1) {
                nibble = image[maskIndex];
                if (column & 1) {
                    patternPixel = pattern[((count * 32) + column) >> 1];
                    patternNibble = patternPixel & 0xF;
                    if ((nibble & 0xF) != 0 && (patternPixel & 0xF) != 0 && !(patternPixel & 8)) {
                        if ((nibble & 0xF) >= 4) {
                            omVibrate(data->unk59, 5, 0, 5);
                            result |= 0x8000;
                        }
                        nibble -= patternNibble;
                    }
                } else {
                    patternPixel = pattern[((count * 32) + column) >> 1];
                    patternNibble = patternPixel & 0xF0;
                    if ((nibble & 0xF0) != 0 && (patternPixel & 0xF0) != 0 && !(patternPixel & 0x80)) {
                        if ((nibble & 0xF0) >= 0x40) {
                            omVibrate(data->unk59, 5, 0, 5);
                            result |= 0x8000;
                        }
                        nibble -= patternNibble;
                    }
                }
                image[maskIndex] = nibble;
                if (image[maskIndex] == 0 && image[otherIndex] == 0) {
                    result++;
                    removed = 0;
                    if (mask[maskIndex * 2] & 1) {
                        removed++;
                    }
                    if (mask[maskIndex * 2 + 1] & 1) {
                        removed++;
                    }
                    if (mask[otherIndex * 2] & 1) {
                        removed++;
                    }
                    if (mask[otherIndex * 2 + 1] & 1) {
                        removed++;
                    }
                    color = mask[maskIndex * 2] &= ~1;
                    mask[maskIndex * 2 + 1] &= ~1;
                    mask[otherIndex * 2] &= ~1;
                    mask[otherIndex * 2 + 1] &= ~1;
                    D_801092B8_eatsa_pizza[work->unk32] -= removed;
                    D_801092C0_eatsa_pizza[work->unk32][x >> 5][(y - 8) >> 5] -= removed;
                }
            }
        }
    }
    if (result != 0) {
        func_80108E48_eatsa_pizza(color, (f32 *)work);
        result = (result & 0x8000) ? 3 : 2;
    }
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0B_eatsa_pizza/161750", func_80107E6C_eatsa_pizza);
#endif

void func_801083A8_eatsa_pizza(omObjData *arg0, func_800E1BA8_minigame_ObjData **arg1, void **arg2) {
    *arg1 = arg0->data;
    *arg2 = (*arg1)->unk158;
}

void func_801083BC_eatsa_pizza(void) {
    D_800EBE28_minigame = 0;
    func_800E1490_minigame(0);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_80108470_eatsa_pizza);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(5, 1, 0, -1, func_801084F8_eatsa_pizza);
    D_80109350_eatsa_pizza = 0;
}

void func_80108470_eatsa_pizza(omObjData *object) {
    s16 *groupP;
    s16 data = func_80108FA4_eatsa_pizza(0x2C0000);

    D_80109278_eatsa_pizza = data;
    // Group pointer must be captured as part of the store so the address is
    // computed after the call, matching the original.
    *(groupP = &D_80109288_eatsa_pizza) = func_80108FEC_eatsa_pizza(data, 1);
    HuSprPosSet(*groupP, 0, 160, 120);
    HuSprAttrSet(*groupP, 0, 0x4000);
    object->func = func_801087DC_eatsa_pizza;
}

void func_801084F8_eatsa_pizza(omObjData *object) {
    u16 *image16;
    u8 *image8;
    s16 group;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        D_8010927A_eatsa_pizza[i] = func_80108FA4_eatsa_pizza((i + 1) | 0x2C0000);
        D_8010928A_eatsa_pizza[i] = func_80108FEC_eatsa_pizza(D_8010927A_eatsa_pizza[i], 1);
        HuSprAttrSet(D_8010928A_eatsa_pizza[i], 0, 0x1008);
        image16 = func_801090B4_eatsa_pizza(D_8010927A_eatsa_pizza[i], 0);
        for (j = 0; j < 240; j++) {
            for (k = 0; k < 160; k++) {
                if (image16[j * 160 + k] & 1) {
                    D_801092B8_eatsa_pizza[i]++;
                    D_801092C0_eatsa_pizza[i][k >> 5][(j - 8) >> 5]++;
                }
            }
        }

        D_8010927E_eatsa_pizza[i] = func_80108FA4_eatsa_pizza((i + 3) | 0x2C0000);
        image8 = func_801090B4_eatsa_pizza(D_8010927E_eatsa_pizza[i], 0);
        for (k = 0; k < 0x4B00; k++) {
            if ((image8[k] & 0x0F) != 0 && (image8[k] & 8) == 0) {
                D_8010934C_eatsa_pizza[i]++;
            }
            if ((image8[k] & 0xF0) != 0 && (image8[k] & 0x80) == 0) {
                D_8010934C_eatsa_pizza[i]++;
            }
        }
    }

    HuSprPosSet(D_8010928A_eatsa_pizza[0], 0, 0x50, 0x78);
    HuSprPosSet(D_8010928A_eatsa_pizza[1], 0, 0xF0, 0x78);
    D_80109282_eatsa_pizza[0] = func_80108FA4_eatsa_pizza(0x2C0005);
    D_80109282_eatsa_pizza[1] = func_80108FA4_eatsa_pizza(0x2C0006);
    D_8010928A_eatsa_pizza[2] = HuSprGrpCreate(0x10, 0);
    group = D_8010928A_eatsa_pizza[2];
    for (i = 0; i < 0x10; i++) {
        HuSprAttrSet(group, i, 0x9000);
        D_80109298_eatsa_pizza[i] = 0;
    }
    object->func = func_80108C50_eatsa_pizza;
}

void func_801087DC_eatsa_pizza(omObjData *object) {
    s32 i;
    s16 seq;
    s16 *wipeDuration;

    switch (D_80109350_eatsa_pizza) {
        case 0:
            GMesCreate(5);
            D_8010913C_eatsa_pizza = 900;
            D_80109350_eatsa_pizza++;
            /* fallthrough */
        case 1:
            if (WipeStatGet() == 0) {
                D_80109144_eatsa_pizza++;
                if (D_80109144_eatsa_pizza == 1) {
                    HuAudSeqPlay(0x36);
                }
            }
            if (GMesStatGet() != 0) {
                break;
            }
            D_80109350_eatsa_pizza++;
            GMesCreate(0x1A, (D_8010913C_eatsa_pizza + 0x1D) / 30, 0xA0, 0x20);
            HuAudFXPlay(0xE);
            for (i = 0; i < 2; i++) {
                D_80109260_eatsa_pizza[i] = (s16)D_801092B8_eatsa_pizza[i];
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if ((s16)D_801092B8_eatsa_pizza[i] == 0) {
                    D_80109350_eatsa_pizza = 3;
                }
            }
            D_8010913C_eatsa_pizza--;
            func_8003F578_main((D_8010913C_eatsa_pizza + 0x1D) / 30);
            if (D_8010913C_eatsa_pizza == 0) {
                D_80109350_eatsa_pizza = 3;
            }
            break;
        case 3:
            for (i = 0; i < 2; i++) {
                HuSprAttrSet(D_8010928A_eatsa_pizza[i], 0, 0x4000);
            }
            if (D_80109260_eatsa_pizza[0] == (s16)D_801092B8_eatsa_pizza[0] &&
                D_80109260_eatsa_pizza[1] == (s16)D_801092B8_eatsa_pizza[1]) {
                D_80109140_eatsa_pizza = -1;
            } else {
                if ((s16)D_801092B8_eatsa_pizza[0] < (s16)D_801092B8_eatsa_pizza[1]) {
                    D_80109268_eatsa_pizza[0][0]->unk34 = 1;
                    D_80109268_eatsa_pizza[0][1]->unk34 = 1;
                    D_80109140_eatsa_pizza = 0;
                } else {
                    D_80109268_eatsa_pizza[1][0]->unk34 = 1;
                    D_80109268_eatsa_pizza[1][1]->unk34 = 1;
                    D_80109140_eatsa_pizza = 1;
                }
            }
            func_8003F5C0_main();
            GMesCreate(0x10);
            HuAudSeqFadeOut(0x78);
            D_80109138_eatsa_pizza = 0xF;
            D_80109350_eatsa_pizza++;
            break;
        case 4:
            if (GMesStatGet() != 0) {
                break;
            }
            D_80109138_eatsa_pizza--;
            if (D_80109138_eatsa_pizza != 0) {
                break;
            }
            if (D_80109140_eatsa_pizza == -1) {
                GMesCreate(0x20);
                seq = 0x6C;
            } else {
                GMesCreate(
                    0x1E,
                    GwPlayer[D_80109268_eatsa_pizza[D_80109140_eatsa_pizza][0]->unk30].chr,
                    GwPlayer[D_80109268_eatsa_pizza[D_80109140_eatsa_pizza][1]->unk30].chr);
                seq = 0x66;
            }
            HuAudSeqPlay(seq);
            D_80109138_eatsa_pizza = 0xF;
            D_80109350_eatsa_pizza++;
            break;
        case 5:
            if (GMesStatGet() != 0) {
                break;
            }
            D_80109138_eatsa_pizza--;
            if (D_80109138_eatsa_pizza != 0) {
                break;
            }
            D_80109350_eatsa_pizza++;
            break;
        case 6:
            if (D_80109138_eatsa_pizza == 0) {
                goto wipe_timer;
            }
            D_80109138_eatsa_pizza--;
            if (D_80109138_eatsa_pizza != 0) {
                break;
            }
            D_80109350_eatsa_pizza++;
            break;
        wipe_timer:
            D_80109138_eatsa_pizza = 0x10;
            wipeDuration = &D_8010913A_eatsa_pizza;
            WipeCreateOut(WIPE_TYPE_NORMAL, *wipeDuration);
            HuAudSeqFadeOut(*wipeDuration);
            func_8004AB0C_main(*wipeDuration);
            break;
        case 7:
            HuAudSeqStop();
            omOvlReturnEx(1);
            break;
    }

    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_80109350_eatsa_pizza = 6;
    }
}

void func_80108C50_eatsa_pizza(omObjData *object) {
    s16 group = D_8010928E_eatsa_pizza;
    HuSprite *sprite;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (D_80109298_eatsa_pizza[i] == 0) {
            continue;
        }
        sprite = HuSprGet(group, i);
        func_800551AC_main(group, i);
        if (sprite->unk_8A < sprite->unk_84->unk10 - 1) {
            continue;
        }
        HuSprDispOff(group, i);
        D_80109298_eatsa_pizza[i] = 0;
    }
}

s16 func_80108D1C_eatsa_pizza(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    s32 i;
    s16 group;

    if (arg0 == -1) {
        return -1;
    }
    for (i = 0; i < 0x10; i++) {
        if (D_80109298_eatsa_pizza[i] == 0) {
            break;
        }
    }
    if (i >= 0x10) {
        return -1;
    }
    D_80109298_eatsa_pizza[i] = 1;
    group = D_8010928E_eatsa_pizza;
    HuSprGrpMemberSet(group, i, arg0, 0);
    func_800550F4_main(group, i, 2);
    HuSprPosSet(group, i, arg1, arg2);
    HuSprZRotSet(group, i, arg3);
    HuSprDispOn(group, i);
    return i;
}

s16 func_80108E48_eatsa_pizza(u16 arg0, f32 *arg1) {
    s32 group;
    s32 spriteId;
    u32 color;
    u32 red;
    u32 green;
    u32 blue;

    group = D_8010928E_eatsa_pizza;
    spriteId = func_80108D1C_eatsa_pizza(D_80109284_eatsa_pizza, (s16)(arg1[0] + 160.0), (s16)(arg1[1] + 120.0), arg1[5]);
    if (spriteId == -1) {
        return -1;
    }
    color = arg0;
    red = (color >> 11) << 3;
    green = (color >> 3) & 0xF8;
    blue = (color << 2) & 0xF8;
    func_80055484_main(group, spriteId, red, green, blue, 0x100);
    HuSprScaleSet(group, spriteId, 0.75f, 0.75f);
    return spriteId;
}

s32 func_80108F4C_eatsa_pizza(void) {
    D_80109148_eatsa_pizza = D_80109148_eatsa_pizza * 0x41C64E6D + 0x3039;
    D_80109148_eatsa_pizza += rand8();
    return D_80109148_eatsa_pizza >> 16;
}

s16 func_80108FA4_eatsa_pizza(s32 arg0) {
    void *temp_v0;
    s16 temp_s0;

    temp_v0 = DataRead(arg0);
    temp_s0 = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    return temp_s0;
}

s16 func_80108FEC_eatsa_pizza(s16 arg0, s16 arg1) {
    s16 spriteId;
    s32 i;

    if (arg0 == -1) {
        return -1;
    }
    spriteId = HuSprGrpCreate(arg1, 0);
    if (spriteId == -1) {
        return -1;
    }
    for (i = 0; i < arg1; i++) {
        HuSprGrpMemberSet(spriteId, i, arg0, 0);
    }
    return spriteId;
}

void *func_801090B4_eatsa_pizza(s16 arg0, s16 arg1) {
    HuSprite_Unk84_Unk00_Struct *entry = &func_80055194_main(arg0)->unk00[arg1];

    return entry->unk00;
}
