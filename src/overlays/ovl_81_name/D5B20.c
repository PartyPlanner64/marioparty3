#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkD5B20 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Object *unk_04;
    /* 0x08 */ omObjData *unk_08;
} UnkD5B20; // sizeof 0xC

typedef struct UnkNameProcData {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkNameProcData; // sizeof 0x10

typedef struct UnkD5B20PrcData {
    /* 0x00 */ s32 *unk_00;
    /* 0x04 */ u16 unk_04;
} UnkD5B20PrcData; // sizeof 0x8

typedef struct UnkNameVecEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04; // max index
    /* 0x06 */ s16 unk_06; // current index
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec *unk_0C; // array of at least unk_04 Vecs
} UnkNameVecEntry;          // sizeof 0x10

typedef struct UnkNameWobbleData {
    /* 0x00 */ Object *obj;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} UnkNameWobbleData; // sizeof 0x10

extern UnkD5B20 D_80105560_name_81[16];
extern s32 D_8010124C_name_81;
extern Object *D_801011F0_name_81;
extern s16 D_801011F8_name_81;
extern s32 D_801011FC_name_81;
extern s32 D_80101220_name_81;
extern s32 D_800A12C0_main;
extern s32 D_800A12C4_main;

static void func_800EED5C_name_81(s32 arg0);
static void func_800EEDA0_name_81(s32 arg0, s32 arg1, s32 arg2);
static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_800EF3F8_name_81(s32 arg0, s32 arg1);
static s32 func_800EFEC8_name_81(Object *obj, Vec *target, f32 speed, Vec *dir);

Object *func_800EDD50_name_81(Vec *pos) {
    D_801011F0_name_81 = func_800D8010_name_81(0x3B, NULL);
    HuVecCopy3F(&D_801011F0_name_81->coords, pos);
    D_801011F0_name_81->flags |= 1;
    func_800461B4_main(D_801011F0_name_81->omObj1->model[0]);
    return D_801011F0_name_81;
}

void func_800EDDBC_name_81(void) {
    func_80046558_main(D_801011F0_name_81->omObj1->model[0]);
    MBDModelKill(D_801011F0_name_81);
    if (D_801011F8_name_81 != -1) {
        func_8000D044_main(D_801011F8_name_81);
        D_801011F8_name_81 = -1;
    }
}

void func_800EDE1C_name_81(void) {
    UnkNameWobbleData *data = HuPrcCurrentGet()->user_data;
    Object *obj = data->obj;
    f32 speed = data->unk_04;
    f32 amplitude = data->unk_08;
    f32 base = data->unk_0C;
    f32 angle = 0.0f;

    while (1) {
        f32 value = base - (sindf(angle) * amplitude);
        angle += speed;
        obj->velocity.x = value;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        HuPrcVSleep();
    }
}

Process *func_800EDEC4_name_81(Object *obj, f32 arg1, f32 arg2) {
    Process *prc = omAddPrcObj(func_800EDE1C_name_81, 0xA, 0, 0x40);
    UnkNameWobbleData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameWobbleData));

    prc->user_data = data;
    data->obj = obj;
    data->unk_04 = arg1;
    data->unk_08 = arg2;
    data->unk_0C = obj->velocity.x;
    return prc;
}

void func_800EDF48_name_81(void) {
    D_801011F4_name_81 = func_800EDEC4_name_81(D_801011F0_name_81, 5.0f, 2.0f);
}

void func_800EDF78_name_81(void) {
    if (D_801011F4_name_81 != NULL) {
        omDelPrcObj(D_801011F4_name_81);
        D_801011F4_name_81 = NULL;
    }
}

void func_800EDFAC_name_81(s32 arg0) {
    if (D_801011FC_name_81 != 0) {
        HuAudFXPlay(0x1EA);
    }
    switch (arg0) {
        case 0:
            D_801011F0_name_81->velocity.x = 70.0f;
            do {
                D_801011F0_name_81->velocity.x -= 2.0f;
                HuPrcVSleep();
            } while (D_801011F0_name_81->velocity.x >= 30.0f);
            break;
        case 1:
            D_801011F0_name_81->velocity.x = 120.0f;
            do {
                D_801011F0_name_81->velocity.x -= 2.5f;
                HuPrcVSleep();
            } while (D_801011F0_name_81->velocity.x >= 30.0f);
            break;
    }
}

void func_800EE0D0_name_81(s32 arg0) {
    D_801011FC_name_81 = 1;
    func_800EDFAC_name_81(arg0);
}

void func_800EE0F4_name_81(s32 arg0) {
    D_801011FC_name_81 = 0;
    func_800EDFAC_name_81(arg0);
}

void func_800EE114_name_81(void) {
    UnkNameProcData *data = HuPrcCurrentGet()->user_data;
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (data->unk_00) {
        case 0:
            while (D_801011F0_name_81->velocity.x <= 70.0f) {
                D_801011F0_name_81->velocity.x += 2.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (D_801011F0_name_81->velocity.x <= 120.0f) {
                D_801011F0_name_81->velocity.x += 2.5f;
                D_801011F0_name_81->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                D_801011F0_name_81->velocity.x += step;
                step -= 0.2f;
                D_801011F0_name_81->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    zero = 0.0f;
                    model->mtx[3][2] = zero;
                    model->mtx[3][1] = zero;
                    model->mtx[3][0] = zero;
                    model->mtx[2][3] = zero;
                    model->mtx[2][1] = zero;
                    model->mtx[2][0] = zero;
                    model->mtx[1][2] = zero;
                    model->mtx[1][3] = zero;
                    model->mtx[0][3] = zero;
                    model->mtx[0][2] = zero;
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[3][3] = 1.0f;
                    model->mtx[2][2] = 1.0f;
                    angle -= 3.0f;
                }
                HuPrcVSleep();
            }
            break;
    }
    omDelPrcObj(NULL);
}

Process *func_800EE40C_name_81(s32 arg0) {
    Process *prc = omAddPrcObj(func_800EE114_name_81, 0xA, 0, 0x40);
    UnkNameProcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameProcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    return prc;
}

void func_800EE468_name_81(s32 arg0) {
    HmfModel *model;
    f32 step;
    f32 angle;
    f32 zero;
    s32 i;

    switch (arg0) {
        case 0:
            while (D_801011F0_name_81->velocity.x <= 70.0f) {
                D_801011F0_name_81->velocity.x += 4.0f;
                HuPrcVSleep();
            }
            break;
        case 1:
            while (D_801011F0_name_81->velocity.x <= 120.0f) {
                D_801011F0_name_81->velocity.x += 2.5f;
                D_801011F0_name_81->coords.x += 2.5f;
                HuPrcVSleep();
            }
            break;
        case 2:
            step = 3.0f;
            angle = 0.0f;
            for (i = 0; i < 35; i++) {
                D_801011F0_name_81->velocity.x += step;
                step -= 0.2f;
                D_801011F0_name_81->coords.x += 2.0f;
                if (i >= 11) {
                    sincosdf(angle, &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1],
                             &Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][0]);
                    Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[1][0] =
                        -Hu3DData[D_801011F0_name_81->omObj1->model[0]].mtx[0][1];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[1][1] = model->mtx[0][0];
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    zero = 0.0f;
                    model->mtx[3][2] = zero;
                    model->mtx[3][1] = zero;
                    model->mtx[3][0] = zero;
                    model->mtx[2][3] = zero;
                    model->mtx[2][1] = zero;
                    model->mtx[2][0] = zero;
                    model->mtx[1][2] = zero;
                    model->mtx[1][3] = zero;
                    model->mtx[0][3] = zero;
                    model->mtx[0][2] = zero;
                    model = &Hu3DData[D_801011F0_name_81->omObj1->model[0]];
                    model->mtx[3][3] = 1.0f;
                    model->mtx[2][2] = 1.0f;
                    angle -= 3.0f;
                }
                HuPrcVSleep();
            }
            break;
    }
}

// Instructions match, but the rodata layout does not: the target has 12 bytes of
// zero padding after this jump table, which suggests a file boundary at
// func_800EED30_name_81 (ROM 0xD6B00) that is not yet reflected in the splat config.
#ifdef NON_MATCHING
void func_800EE74C_name_81(s32 arg0) {
    Vec pos;
    f32 angle;
    s32 i;

    switch (arg0) {
        case 0:
            D_801011F8_name_81 = func_8000CED8_main(0xB0004, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            HuVecCopy3F(&pos, &D_801011F0_name_81->coords);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                HuVecCopyXYZ(&D_801011F0_name_81->coords, sindf(i) * 12.0f + pos.x, pos.y, cosdf(i) * 2.0f + pos.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 1:
            D_801011F8_name_81 = func_8000CED8_main(0xB0004, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 2:
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 3:
            D_801011F8_name_81 = func_8000CED8_main(0xB000C, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 0.3f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
        case 4:
            D_801011F8_name_81 = func_8000CED8_main(0xB0005, 0xAA9);
            Hu3DModelCameraSet(D_801011F8_name_81, 1);
            func_8000CD00_main(D_801011F8_name_81, 1.0f, 30.0f, 1.0f);
            func_8000D018_main(D_801011F8_name_81, 10.0f);
            angle = MBDVecAngleGet(&D_801011F0_name_81->rot);
            for (i = 0; i <= 720; i += 15) {
                func_8000CFA4_main(D_801011F8_name_81, D_801011F0_name_81->coords.x, D_801011F0_name_81->velocity.x,
                                   D_801011F0_name_81->coords.z);
                D_801011F0_name_81->rot.z = cosdf(i * 3 + angle);
                D_801011F0_name_81->rot.x = sindf(i * 3 + angle);
                HuPrcVSleep();
            }
            break;
    }
    if (D_801011F8_name_81 != -1) {
        func_8000D044_main(D_801011F8_name_81);
        D_801011F8_name_81 = -1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE74C_name_81);
#endif

Object *func_800EEC40_name_81(Vec *pos) {
    D_801011F0_name_81 = func_800D8010_name_81(0x3E, NULL);
    MBDModelTempAllocFree(D_801011F0_name_81);
    HuVecCopy3F(&D_801011F0_name_81->coords, pos);
    D_801011F0_name_81->velocity.x = 120.0f;
    do {
        D_801011F0_name_81->velocity.x -= 2.5f;
        HuPrcVSleep();
    } while (D_801011F0_name_81->velocity.x >= 30.0f);
    D_801011F4_name_81 = func_800EDEC4_name_81(D_801011F0_name_81, 5.0f, 2.0f);
    return D_801011F0_name_81;
}

Object *func_800EED24_name_81(void) {
    return D_801011F0_name_81;
}

void func_800EED30_name_81(s32 arg0) {
    D_800A12C4_main = arg0;
    func_800EED5C_name_81(arg0);
}

s32 func_800EED50_name_81(void) {
    return D_800A12C4_main;
}

static void func_800EED5C_name_81(s32 arg0) {
    D_800A12C0_main = arg0;
}

void func_800EED68_name_81(s32 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 0);
}

void func_800EED84_name_81(s32 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 1);
}

static void func_800EEDA0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp18[MB_MAX_PLAYERS];
    s32 hasCom = 0;
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    s32 sp2C;
    s32 i;

    hasCom = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg1) {
            if (GwPlayer[i].stat & 1) {
                hasCom = 1;
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                HuWinActivePlayerSet(arg0, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (hasCom != 0) {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    if (arg2 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void func_800EF0A0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 0);
}

void func_800EF0BC_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 1);
}

static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i == arg1) || (i == arg2)) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (mask) {
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    } else {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    }

    if (arg3 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void func_800EF3B4_name_81(s32 arg0) {
    func_800EF3F8_name_81(arg0, 0);
}

void func_800EF3D0_name_81(s32 arg0) {
    func_800EF3F8_name_81(arg0, 1);
}

void func_800EF3EC_name_81(s32 arg0) {
    D_80101220_name_81 = arg0;
}

static void func_800EF3F8_name_81(s32 arg0, s32 arg1) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < D_80101220_name_81; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == D_80101220_name_81) {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    } else {
        for (i = 0; i < D_80101220_name_81; i++) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = 0;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        }
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    }
    HuWinComKeyReset();
}

void func_800EF754_name_81(s32 arg0) {
    HuWinActivePlayerSet(arg0, HUWIN_PLAYER_ALL);
    HuWinComKeySet(-1, -1, -1, -1);
    while (HuWinStatGet(arg0) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void func_800EF7C8_name_81(Object *arg0, f32 arg1, f32 arg2) {
    arg0->velocity.y = arg1;
    arg0->velocity.z = arg2;
}

s32 func_800EF7D4_name_81(Object *arg0) {
    s32 ret = 0;
    if (arg0->velocity.z != 0.0f) {
        ret = 1;
    }
    return ret;
}

void func_800EF800_name_81(Object *arg0) {
    while (func_800EF7D4_name_81(arg0)) {
        HuPrcVSleep();
    }
}

void func_800EF840_name_81(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80105560_name_81[i].unk_04 = NULL;
        D_80105560_name_81[i].unk_08 = NULL;
    }
}

void func_800EF880_name_81(void) {
    s32 i;
    UnkD5B20 *entry;

    for (i = 0, entry = D_80105560_name_81; i < 16; i++) {
        if (entry[i].unk_08 != NULL) {
            omDelObj(entry[i].unk_08);
            entry[i].unk_08 = NULL;
        }
    }
}

static void func_800EF8EC_name_81(omObjData *obj) {
    UnkD5B20 *entry = &D_80105560_name_81[obj->work[0]];

    if (Hu3DData[entry->unk_04->omObj1->model[0]].motTime ==
        D_800CCF58_main[Hu3DData[entry->unk_04->omObj1->model[0]].motId].unk02) {
        MBDMotionShiftSet(entry->unk_04, entry->unk_00, 0, 0xA, entry->unk_02);
        entry->unk_04 = NULL;
        entry->unk_08 = NULL;
        omDelObj(obj);
    }
}

s32 func_800EF9C4_name_81(Object *arg0, s16 arg1, s16 arg2) {
    omObjData *obj;
    UnkD5B20 *entry;
    s32 i;
    s32 ret;

    for (i = 0; i < ARRAY_COUNT(D_80105560_name_81); i++) {
        entry = &D_80105560_name_81[i];
        if (entry->unk_08 == NULL) {
            break;
        }
    }

    if (i != ARRAY_COUNT(D_80105560_name_81)) {
        obj = omAddObj(0x2000, 0, 0, -1, func_800EF8EC_name_81);
        entry->unk_08 = obj;
        obj->work[0] = i;
        entry->unk_04 = arg0;
        entry->unk_00 = arg1;
        entry->unk_02 = arg2;
        ret = i;
    } else {
        ret = -1;
    }
    return ret;
}

void func_800EFA8C_name_81(Object *arg0, s16 arg1, s32 arg2) {
    MBDMotionShiftSet(arg0, arg1, 0, 0xA, arg2);
}

void func_800EFABC_name_81(Object *arg0) {
    while (!(MBDMotionCheck(arg0) & 1)) {
        HuPrcVSleep();
    }
}

void func_800EFB00_name_81(Object *arg0) {
    do {
        HuPrcVSleep();
    } while (!(func_800D92A8_name_81(arg0) & 1));
}

s32 func_800EFB3C_name_81(s32 playerIndex) {
    s32 rank;
    s32 i;
    s32 score[MBD_MAX_PLAYERS];

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        score[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }

    for (i = 0, rank = 0; i < MBD_MAX_PLAYERS; i++) {
        if ((i != playerIndex) && (score[playerIndex] < score[i])) {
            rank++;
        }
    }
    return rank;
}

s32 func_800EFBE8_name_81(s32 playerIndex) {
    return GwPlayer[playerIndex].star * 1000 + GwPlayer[playerIndex].coin;
}

void func_800EFC28_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MBD_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MBD_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

void func_800EFD24_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MB_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MB_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

s32 func_800EFE20_name_81(f32 arg0) { // 800EEF80 in party mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

s32 func_800EFE8C_name_81(Object *obj, Vec *target, f32 speed) {
    return func_800EFEC8_name_81(obj, target, speed, &obj->rot);
}

s32 func_800EFEAC_name_81(Object *obj, Vec *target, f32 speed) {
    Vec dir;

    return func_800EFEC8_name_81(obj, target, speed, &dir);
}

static s32 func_800EFEC8_name_81(Object *obj, Vec *target, f32 speed, Vec *dir) {
    f32 dist = HuVecDistance(&obj->coords, target);

    if (dist == 0.0f) {
        return 1;
    }
    MBDVecDirGet(&obj->coords, target, dir);
    if (speed <= dist) {
        obj->coords.x += speed * dir->x;
        obj->coords.y += speed * dir->y;
        obj->coords.z += speed * dir->z;
        return 0;
    }
    HuVecCopy3F(&obj->coords, target);
    return 1;
}

UnkNameVecEntry *func_800EFFBC_name_81(s32 arg0, f32 arg1, s16 arg2, Vec *arg3) {
    UnkNameVecEntry *entry = HuMemMemoryAllocPerm(sizeof(UnkNameVecEntry));

    entry->unk_00 = arg0;
    entry->unk_04 = arg2;
    entry->unk_06 = 0;
    entry->unk_08 = arg1;
    entry->unk_0C = arg3;
    return entry;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F001C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F008C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0208_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0378_name_81);

void func_800F03C8_name_81(s16 arg0) {
    func_8001C258_main(arg0, 0x4000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F03F0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0480_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F04FC_name_81);

void func_800F05AC_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F05B4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F061C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06D4_name_81);

s32 func_800F0700_name_81(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0708_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F08BC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0C30_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0C4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0D1C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0DF8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0E4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0EA8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0FE8_name_81);

Process *func_800F1340_name_81(s32 *arg0, s32 arg1, s16 arg2) {
    Process *prc = omAddPrcObj(func_800F0FE8_name_81, 0x1005, 0, 0x40);
    UnkD5B20PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD5B20PrcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    data->unk_04 = arg2;
    D_8010124C_name_81 = arg1;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F13C0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F140C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F14A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F159C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F1784_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2090_name_81);

s32 func_800F21CC_name_81(s16 arg0) {
    s32 i;
    s16 chr = arg0;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBDGetPlayerStruct(i);
        if (player->stat & PLAYER_IS_CPU) {
            continue;
        }
        if (player->pad == chr) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2238_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F22E8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F23FC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2408_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F24DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2618_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F32CC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F336C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3500_name_81);

s16 MBDGetCurrentPlayerIndex(void) {
    return GwSystem.current_player_index;
}

GW_PLAYER *MBDGetPlayerStruct(s32 player) {
    if (player < 0) {
        player = MBDGetCurrentPlayerIndex();
    }
    return &GwPlayer[player];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F379C_name_81);

s32 func_800F37B8_name_81(s16 playerIndex) {
    return MBDGetPlayerStruct(playerIndex)->stat & PLAYER_IS_CPU;
}

void func_800F37E0_name_81(s32 playerIndex, s32 amount) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(playerIndex);
    player->coin = player->coin + amount;
    if (player->coin > 999) {
        player->coin = 999;
    }
    if (player->coin < 0) {
        player->coin = 0;
    }
    if (player->coinPrize <= player->coin) {
        player->coinPrize = player->coin;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3850_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3880_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F38DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F397C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3A04_name_81);

void func_800F3AF4_name_81(s32 playerIndex, f32 arg1) {
    Hu3DMotionSpeedSet(MBDGetPlayerStruct(playerIndex)->player_obj->omObj1->model[0], arg1);
    func_800F8CD8_name_81(playerIndex, arg1);
}

void func_800F3B54_name_81(s32 playerIndex, u8 cpuDifficulty) {
    MBDGetPlayerStruct(playerIndex)->cpu_difficulty = D_80101370_name_81[cpuDifficulty];
}

void func_800F3B8C_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3B94_name_81);

void func_800F3C28_name_81(void) {
    GW_PLAYER *player = HuPrcCurrentGet()->user_data;

    while (1) {
        HuPrcVSleep();
        if (player->stat & PLAYER_UNK_04) {
            continue;
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3C98_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3D50_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3D74_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3DC0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3DFC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3E58_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3E88_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3EC0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3F18_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3F4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F4030_name_81);
