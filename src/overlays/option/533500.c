#include "common.h"
#include "overlays/option.h"
#include "game/vibrator.h"
#include "mallocblock.h"

typedef struct {
    /* 0x00 */ s32 overlay;
    /* 0x04 */ u8 minigameType;
    /* 0x05 */ u8 unk_05[15];
} OptMinigameEntry; // sizeof 0x14

// One entry per on-screen cursor; the object is the 3D cursor for that slot.
typedef struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *obj;
} OptCursor; // sizeof 0x2C

typedef struct {
    /* 0x00 */ Process *prcObj;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec at;
    /* 0x1C */ Vec up;
    /* 0x28 */ f32 fov;
    /* 0x2C */ f32 nearPlane;
    /* 0x30 */ f32 farPlane;
    /* 0x34 */ s16 camId;
    /* 0x38 */ omObjData *obj;
    /* 0x3C */ Vec startPos;
    /* 0x48 */ Vec startAt;
    /* 0x54 */ Vec endPos;
    /* 0x60 */ Vec endAt;
    /* 0x6C */ s32 frame;
    /* 0x70 */ s32 duration;
} OptCam; // sizeof 0x74

// Object that keeps an attached 3d model sound playing for a fixed duration.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 seNo;
} OptSeObj; // sizeof 0x8

extern OptMinigameEntry D_800A6D40_main[];
extern Vec D_80113A98_option;
extern Vec D_80113580_option[6][2];
extern Vec D_801135E0_option[2];
extern Vec D_801135F8_option[2];
extern Vec D_801137FC_option;
extern Vec D_80113808_option;
extern Vec D_80113814_option;
extern Vec D_80113820_option;
extern Vec D_801138B0_option;
extern Vec D_801138BC_option;
extern Vec D_801139E0_option;
extern Vec D_801139EC_option;
extern Vec D_801139F8_option;
extern s8 D_800D2132_main;
extern Vec D_80113508_option[2];
extern Vec D_801146BC_option;
extern Vec D_801146C8_option;
extern Vec D_801146D4_option;
extern Vec D_801146E0_option;
extern Vec D_80114674_option;
extern Vec D_80114680_option;
extern Vec D_80113B90_option;
extern Vec D_80113B9C_option;
extern Vec D_80113BA8_option;
extern Vec D_80113BB4_option;
extern Vec D_80113BC0_option;
extern Vec D_80113BCC_option;
extern char D_80113A4C_option[];
extern Vec D_8011376C_option[];
extern Vec D_8011367C_option[2];
extern Vec D_80113694_option[2];
extern Vec D_801136B8_option;
extern Vec D_801136AC_option[2];
extern Vec D_8011379C_option[2];
extern Vec D_801137B4_option[2];
extern Vec D_801137CC_option[2];
extern Vec D_801137E4_option[2];
extern Vec D_8011388C_option;
extern Vec D_80113898_option;
extern Vec D_801138A4_option;
extern s32 D_80114778_option[4];
extern OptCam D_801146F0_option;
extern s32 D_80114764_option;
extern Process *D_80114770_option;
extern OptCursor D_80114788_option[2];
extern OptSeObj D_801147E0_option;
extern s32 D_801147E8_option;
extern OptSprSlot D_80114EF0_option[0x40];
extern OptSpr D_801147F0_option[0x40];
extern UnkOption D_80114F70_option[0x40];
extern s16 D_80115A70_option;
extern u16 D_80115A72_option;
extern OptWinEntry D_80115A78_option[0x20];
extern u8 D_800D09A8_main;
extern s32 D_801139D0_option;

void func_8010C3E4_option(s32, s32, s32);
void func_8010D5B0_option(s32, s32, s32);
void func_80107F50_option(s32, s32, s32);
void func_80030030_main(f32);
s32 func_8010BACC_option(s32, s32);
s32 func_800465E8_main(void);
void func_800465F4_main(s32);
void func_801133BC_option(s32, u32);
void func_80113368_option(s32, s32 *, s32 *);
void func_8011323C_option(s32);
void func_80113258_option(s32);
void func_80113490_option(s32);
void func_80113424_option(s32);
s32 func_801130E8_option(s32);
s32 func_80109D04_option(s32, s32);
s32 func_80109EF4_option(s32, s32);
void func_8010A3E8_option(s32, s32);
void func_80109908_option(f32, f32, f32, s32 *, s32 *);
omObjData *func_80107758_option(Vec *, Vec *, s32);
void func_801133EC_option(s32);
s32 func_800078F8_main(s32);
void func_8000BBFC_main(u16, s16);
void func_8000BD94_main(u16, s32, s32);
void func_8000BDDC_main(u16, s32);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BE5C_main(u16, f32, f32);
void func_80013350_main(s16);
void func_80012E54_main(s16);
void func_80033910_main(HmfData *);
void func_80109730_option(Vec *, Vec *, Vec *, f32, Vec *, f32 *, f32 *);
void func_80112F48_option(s32, s32, f32, f32, f32);
void func_8011331C_option(s32, s32, u16);
void func_801132AC_option(s32, s32);
void func_801132C8_option(s32, s32);
void func_801132E4_option(s32, u32);
void func_80112EB8_option(s32, s32, f32, f32, f32);
void func_80112FF4_option(s32, s32, f32, f32, f32);
void func_80112FD8_option(s32, s32, s32);
void func_80106508_option(Vec *, Vec *, Vec *);
void func_80113088_option(void);
void func_801059D0_option(void);
void func_80105FF8_option(Vec *, Vec *, Vec *);
void func_80113274_option(s32, f32 *, f32 *, f32 *);
void func_80113290_option(s32, f32, f32, f32);
omObjData *func_80106F88_option(Vec *, Vec *, s32);
void func_8010744C_option(omObjData *);
void func_80107B80_option(Vec *, Vec *, f32, Vec *);
void func_80107D64_option(Vec *, Vec *, f32, Vec *);
void func_80106C7C_option(omObjData *);
void func_80107058_option(omObjData *);
void func_801077BC_option(omObjData *);
void func_80105E40_option(void);
void func_80108B34_option(void);
void func_80108B58_option(void);
void func_8010A66C_option(void);
void func_8010C224_option(void);
void func_8010F94C_option(void);
void func_8010FDF4_option(void);
void func_80112060_option(void);
void func_80108A68_option(void);
void func_80108AAC_option(void);
void func_80108AF0_option(void);
void func_8011053C_option(s32, s32, s32);
void func_8011019C_option(void);
void func_80110754_option(void);
void func_801119CC_option(void);
void func_8011083C_option(s32, s32, s32);
void func_801110C0_option(s32, u32, s32, s32, u16, u16, s16);
void func_80111A10_option(s32);
void func_80111C50_option(s32, u32);
void func_80112028_option(s32, s32, s32);
void func_801130CC_option(void);
s32 func_80113218_option(s32);
omObjData *func_8010737C_option(Vec *, Vec *, s32);
void func_80113338_option(s32, s32, s16, s16, u16);
void func_80113384_option(s32);
void func_801133A0_option(s32);
void func_80113408_option(s32, u32);
void func_80113440_option(s32);
s32 func_8010AF54_option(s32, s32);
s32 func_8010A940_option(s32, s32);
void func_8010B654_option(s32, s32);
s32 func_8011345C_option(s32);
void func_801123D8_option(void);
void func_80113300_option(s32);
void func_80112A44_option(void);
void func_80112B08_option(void);
void func_80112E14_option(void);
void func_8010FFDC_option(void);

void func_801059D0_option(void) {
    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    {
        Vec pos = D_801139E0_option;
        Vec at = D_801139EC_option;
        Vec up = D_801139F8_option;

        ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCamSetPerspective(0, 41.0f, 80.0f, 8000.0f);
        Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    }
    func_80030030_main(1.0f);
    pfInit();
    func_8005A6B0_main();
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 128, 128, 128);
    HmfLightColorSet(1, 64, 64, 96);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

void func_80105C14_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C38_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C5C_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C80_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105CA4_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CC8_option(void) {
    func_801059D0_option();
    func_80108AAC_option();
}

void func_80105CEC_option(void) {
    func_801059D0_option();
    func_80108AF0_option();
}

void func_80105D10_option(void) {
    D_801146F0_option.prcObj = NULL;
    D_801146F0_option.obj = NULL;
    D_801146F0_option.camId = -1;
    D_801146F0_option.fov = 50.0f;
    D_801146F0_option.nearPlane = 80.0f;
    D_801146F0_option.farPlane = 4000.0f;
}

void func_80105D5C_option(f32 fov, f32 nearPlane, f32 farPlane) {
    D_801146F0_option.fov = fov;
    D_801146F0_option.nearPlane = nearPlane;
    D_801146F0_option.farPlane = farPlane;
}

void func_80105D74_option(void) {
    while (1) {
        func_80012E54_main(0);
        HuPrcVSleep();
    }
}

void func_80105DA0_option(s32 camId, f32 fov) {
    if (D_801146F0_option.prcObj != NULL) {
        func_80105E40_option();
    }
    func_80013320_main(camId, 0);
    D_801146F0_option.camId = camId;
    D_801146F0_option.fov = fov;
    Hu3DCamSetPerspective(0, fov, D_801146F0_option.nearPlane, D_801146F0_option.farPlane);
    func_80012E54_main(0);
    D_801146F0_option.prcObj = omAddPrcObj(func_80105D74_option, 0x5000, 0x2000, 0);
}

void func_80105E40_option(void) {
    if (D_801146F0_option.prcObj != NULL) {
        omDelPrcObj(D_801146F0_option.prcObj);
    } else {
        while (1) {
            HuPrcVSleep();
        }
    }

    if (D_801146F0_option.camId != -1) {
        func_80013350_main(0);
        D_801146F0_option.camId = -1;
    }

    D_801146F0_option.prcObj = NULL;
}

void func_80105EB8_option(void) {
    while (1) {
        Hu3DCamSetPositionOrientation(0, &D_801146F0_option.pos, &D_801146F0_option.at, &D_801146F0_option.up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void func_80105F08_option(f32 fov) {
    Vec pos, at, up;

    D_801146F0_option.fov = fov;
    if (D_801146F0_option.camId != -1) {
        func_80105FF8_option(&pos, &at, &up);
        HuVecCopy3F(&D_801146F0_option.pos, &pos);
        HuVecCopy3F(&D_801146F0_option.at, &at);
        HuVecCopy3F(&D_801146F0_option.up, &up);
    }
    if (D_801146F0_option.prcObj != NULL) {
        func_80105E40_option();
    }
    Hu3DCamSetPositionOrientation(0, &D_801146F0_option.pos, &D_801146F0_option.at, &D_801146F0_option.up);
    Hu3DCamUpdateMtx(0);
    Hu3DCamSetPerspective(0, D_801146F0_option.fov, D_801146F0_option.nearPlane, D_801146F0_option.farPlane);
    D_801146F0_option.prcObj = omAddPrcObj(func_80105EB8_option, 0x5000, 0x2000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105FF8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106508_option);

void func_80106998_option(omObjData *obj) {
    Vec pos, at, up, start, end;
    f32 t, clamped;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&start, &D_801146F0_option.startPos);
    HuVecCopy3F(&end, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    HuVecCopy3F(&start, &D_801146F0_option.startAt);
    HuVecCopy3F(&end, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (end.x - start.x) * clamped + start.x, (end.y - start.y) * clamped + start.y,
                 (end.z - start.z) * clamped + start.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

void func_80106B78_option(void) {
    if (D_801146F0_option.obj != NULL) {
        omDelObj(D_801146F0_option.obj);
    }
    D_801146F0_option.obj = NULL;
}

omObjData *func_80106BAC_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106998_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_80106C7C_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    startLength = HuVecGetLength3F(&startDir);
    t = HuVecGetLength3F(&endDir);
    HuVecCopyXYZ(&direction, at.x - pos.x, 0.0f, at.z - pos.z);
    length = HuVecGetLength3F(&direction);
    t = ((t - startLength) * clamped + startLength) / length;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80106F88_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80106C7C_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_80107058_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, length;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    clamped = sindf(clamped * 90.0f);
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    startLength = HuVecGetLength3F(&startDir);
    t = HuVecGetLength3F(&endDir);
    HuVecCopyXYZ(&direction, at.x - pos.x, 0.0f, at.z - pos.z);
    length = HuVecGetLength3F(&direction);
    t = ((t - startLength) * clamped + startLength) / length;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_8010737C_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    func_80106B78_option();
    obj = omAddObj(6, 0, 0, -1, func_80107058_option);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_801146F0_option.obj = obj;
    D_801146F0_option.frame = 0;
    D_801146F0_option.duration = duration;
    HuVecCopy3F(&D_801146F0_option.startAt, &D_801146F0_option.at);
    HuVecCopy3F(&D_801146F0_option.startPos, &D_801146F0_option.pos);
    HuVecCopyXYZ(&D_801146F0_option.endAt, at->x, at->y, at->z);
    HuVecCopyXYZ(&D_801146F0_option.endPos, pos->x, pos->y, pos->z);
    return obj;
}

void func_8010744C_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&startDir, &endDir, angleT, &direction);
    } else {
        func_80107D64_option(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * clamped + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80107758_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_8010744C_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_8010778C_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_8010744C_option;
    D_80114764_option = 0;
    return obj;
}

void func_801077BC_option(omObjData *obj) {
    Vec pos, at, up, startPos, endPos, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)D_801146F0_option.frame / D_801146F0_option.duration;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    HuVecCopy3F(&startPos, &D_801146F0_option.startPos);
    HuVecCopy3F(&endPos, &D_801146F0_option.endPos);
    HuVecCopyXYZ(&pos, (endPos.x - startPos.x) * clamped + startPos.x,
                 (endPos.y - startPos.y) * clamped + startPos.y,
                 (endPos.z - startPos.z) * clamped + startPos.z);
    HuVecCopy3F(&startAt, &D_801146F0_option.startAt);
    HuVecCopy3F(&endAt, &D_801146F0_option.endAt);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - startPos.x, 0.0f, startAt.z - startPos.z);
    HuVecCopyXYZ(&endDir, endAt.x - endPos.x, 0.0f, endAt.z - endPos.z);
    angleT = sindf(clamped * 90.0f);
    if (D_80114764_option != 0) {
        func_80107B80_option(&startDir, &endDir, angleT, &direction);
    } else {
        func_80107D64_option(&startDir, &endDir, angleT, &direction);
    }
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * angleT + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 t * direction.z + pos.z);
    if (D_801146F0_option.frame > D_801146F0_option.duration) {
        omDelObj(obj);
        func_80106508_option(&D_801146F0_option.endPos, &D_801146F0_option.endAt, &up);
        D_801146F0_option.obj = NULL;
    } else {
        D_801146F0_option.frame++;
        func_80106508_option(&pos, &at, &up);
    }
}

omObjData *func_80107AD4_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_801077BC_option;
    D_80114764_option = 1;
    return obj;
}

omObjData *func_80107B08_option(Vec *pos, Vec *at, s32 duration) {
    omObjData *obj;

    obj = func_80106F88_option(pos, at, duration);
    obj->func = func_801077BC_option;
    D_80114764_option = 0;
    return obj;
}

f32 func_80107B38_option(f32 x1, f32 y1, f32 x2, f32 y2) {
    return -(atan2df(y2 - y1, x2 - x1) - 90.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107B80_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107D64_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A20_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107F50_option);

void func_80108A68_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_80108B58_option, 0x5000, 0x2000, 0);
}

void func_80108AAC_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010A66C_option, 0x5000, 0x2000, 0);
}

void func_80108AF0_option(void) {
    func_80108B34_option();
    func_80112060_option();
    D_80114770_option = omAddPrcObj(func_8010C224_option, 0x5000, 0x2000, 0);
}

void func_80108B34_option(void) {
    func_8010F94C_option();
    func_8010FDF4_option();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A4C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A50_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A54_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", jtbl_80113A58_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A80_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A8C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A98_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AA4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AB0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113ABC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AC8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AD4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AE0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AEC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AF8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B04_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B10_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108B58_option);

s32 func_80109504_option(void) {
    s32 selection = 0;
    s32 buttons;
    s32 result;
    Vec at;
    s32 x, y;

    if (func_800465E8_main()) {
        func_800465F4_main(1);
        func_801133BC_option(0, 0x4E00);
        func_80113490_option(0);
        func_80113408_option(0, 0x4E02);
    } else {
        func_801133BC_option(0, 0x4E02);
    }
    func_80113384_option(0);
    func_8010A3E8_option(selection, 0);
    while (1) {
        buttons = D_800D5558_main[0];
        buttons |= func_801130E8_option(0);
        if (buttons & 0x8000) {
            result = func_80109D04_option(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = func_80109EF4_option(selection, buttons);
        } else if (buttons & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (selection) {
                case 0:
                case 1:
                    HuVecCopy3F(&at, &D_80113508_option[1]);
                    func_80107758_option(&D_80113508_option[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 2:
                    HuVecCopy3F(&at, &D_80113508_option[1]);
                    func_80107758_option(&D_80113508_option[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 9:
                default:
                    break;
            }
            selection = 3;
            func_80109908_option(0.0f, 100.0f, 1275.0f, &x, &y);
            func_80112028_option(0, x, y);
            func_80113424_option(0);
            func_80113408_option(0, 0x4E03);
            func_80113384_option(0);
        }
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return selection;
}

void func_801096B8_option(s32 arg0, s32 arg1, s32 arg2) {
    D_80114778_option[0] = arg1;
    D_80114778_option[1] = arg2;
    func_80112028_option(arg0, 160, arg2);
}

void func_801096E4_option(s32 arg0) {
    if (++D_80114778_option[3] >= 21) {
        D_80114778_option[3] = 0;
    }
    D_80114778_option[2] = 0;
    func_80112028_option(arg0, D_80114778_option[0], D_80114778_option[1]);
}

void func_80109730_option(Vec *pos, Vec *at, Vec *up, f32 fov, Vec *point, f32 *screenX, f32 *screenY) {
    f32 mtx[4][4];
    f32 dx, dy, dz;
    f32 x, y, z;

    guLookAtF(mtx, pos->x, pos->y, pos->z, at->x, at->y, at->z, up->x, up->y, up->z);
    dx = point->x;
    dy = point->y;
    dz = point->z;
    dx -= pos->x;
    dy -= pos->y;
    dz -= pos->z;
    x = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    y = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    z = dx * mtx[0][2] + dy * mtx[1][2] + dz * mtx[2][2];
    fov /= 2.0f;
    dx = sindf(fov) / cosdf(fov) * z * (4.0f / 3.0f);
    dy = sindf(fov) / cosdf(fov) * z;
    x = x * (160.0f / -dx) + 160.0f;
    *screenX = x;
    y = y * (120.0f / dy) + 120.0f;
    *screenY = y;
}

void func_80109908_option(f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;
    HuCamera *camera;

    camera = gCameraList;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(&camera->pos, &camera->at, &camera->up, camera->fov[0], &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void func_8010998C_option(Vec *camPos, Vec *camAt, Vec *camUp, f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80109730_option(camPos, camAt, camUp, gCameraList->fov[0], &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void func_80109A0C_option(s32 slot, Vec *start, Vec *end, s32 duration) {
    f32 startPos[2], endPos[2];
    s32 x, y;
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        func_80109908_option(start->x, start->y, start->z, &x, &y);
        startPos[0] = x;
        startPos[1] = y;
        func_80109908_option(end->x, end->y, end->z, &x, &y);
        endPos[0] = x;
        endPos[1] = y;
        t = (1.0f / duration) * i;
        func_80112028_option(slot, t * (endPos[0] - startPos[0]) + startPos[0], t * (endPos[1] - startPos[1]) + startPos[1]);
        HuPrcVSleep();
    }
    func_80112028_option(slot, endPos[0], endPos[1]);
}

void func_80109B7C_option(s32 index, s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        t = (1.0f / duration) * i;
        func_80112028_option(index, startX + t * (endX - startX), startY + t * (endY - startY));
        HuPrcVSleep();
    }
    func_80112028_option(index, endX, endY);
}

void func_80109CB0_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            val1 = 0xA0;
            val2 = 0x50;
            break;
        case 1:
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
        case 4:
            val1 = 0xA0;
            val2 = 0x6E;
            break;
        case 5:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B9C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BB4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BC0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BCC_option);

s32 func_80109D04_option(s32 selection, s32 buttons) {
    switch (selection) {
        case 0: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113B90_option;
            at = D_80113B9C_option;
            func_8010737C_option(&pos, &at, 30);
            func_80113338_option(9, 11, 0, 8, 0);
            func_80113338_option(10, 12, 0, 8, 0);
            HuPrcSleep(30);
            break;
        }
        case 1: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113BA8_option;
            at = D_80113BB4_option;
            func_8010737C_option(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 2: {
            Vec pos;
            Vec at;
            func_801133A0_option(0);
            func_80113440_option(0);
            pos = D_80113BC0_option;
            at = D_80113BCC_option;
            func_8010737C_option(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 3:
            func_801133A0_option(0);
            func_80113408_option(0, 0x4E04);
            if (func_8011345C_option(0)) {
                func_80113408_option(0, 0x4E03);
                func_80113384_option(0);
                return -1;
            }
            selection = 3;
            break;
        case 9:
        default:
            break;
    }
    return selection;
}

s32 func_80109EF4_option(s32 selection, s32 buttons) {
    Vec up;
    s32 x, y, endX, endY;

    up = D_80113A98_option;

    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
                func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_801137CC_option[0], &D_801137CC_option[1], &up, D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 2;
                func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_801137E4_option[0], &D_801137E4_option[1], &up, D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e01);
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113258_option(0);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e03);
            } else if (buttons & 0x100) {
                selection = 0;
                func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e02);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 0;
                func_80107758_option(&D_8011379C_option[0], &D_8011379C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011379C_option[0], &D_8011379C_option[1], &up, D_8011376C_option[0].x, D_8011376C_option[0].y, D_8011376C_option[0].z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e02);
            } else if (buttons & 0x100) {
                selection = 3;
                func_80107758_option(&D_801137B4_option[0], &D_801137B4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[3].x, D_8011376C_option[3].y, D_8011376C_option[3].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113258_option(0);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e03);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                func_80107758_option(&D_801137E4_option[0], &D_801137E4_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_8011323C_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[2].x, D_8011376C_option[2].y, D_8011376C_option[2].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 1;
                func_80107758_option(&D_801137CC_option[0], &D_801137CC_option[1], 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_8011323C_option(0);
                HuPrcSleep(20);
                func_80109908_option(D_8011376C_option[1].x, D_8011376C_option[1].y, D_8011376C_option[1].z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e01);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

void func_8010A3E8_option(s32 selection, s32 arg1) {
    s32 index = 0;
    s32 x, y;

    switch (selection) {
        case 0:
            index = 0;
            break;
        case 1:
            index = 1;
            break;
        case 2:
            index = 2;
            break;
        case 3:
            index = 3;
            break;
    }
    func_80109908_option(D_8011376C_option[index].x, D_8011376C_option[index].y, D_8011376C_option[index].z, &x, &y);
    func_80112028_option(0, x, y);
}

s32 func_8010A498_option(void) {
    Vec pos, at;
    s32 selection = 0;
    s32 buttons;
    s32 result;

    func_80105F08_option(41.539f);
    func_801133BC_option(0, 0x4E05);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E06);
    func_80113384_option(0);
    func_8010B654_option(0, 0);
    while (1) {
        buttons = D_800D5558_main[0];
        buttons |= func_801130E8_option(0);
        if (buttons & 0x8000) {
            result = func_8010AF54_option(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = func_8010A940_option(selection, buttons);
        } else if (buttons & 0x4000) {
            func_801133A0_option(0);
            func_80113440_option(0);
            switch (selection) {
                case 0:
                case 1:
                case 2:
                    selection = 4;
                    HuVecCopy3F(&pos, &D_801135E0_option[0]);
                    HuVecCopy3F(&at, &D_801135E0_option[1]);
                    func_80107758_option(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 3:
                    selection = 5;
                    HuVecCopy3F(&pos, &D_801135F8_option[0]);
                    HuVecCopy3F(&at, &D_801135F8_option[1]);
                    func_80107758_option(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 4:
                case 5:
                default:
                    break;
            }
            func_80113424_option(0);
            func_80113408_option(0, 0x4E0B);
            func_80113384_option(0);
        }
        func_8010B654_option(selection, buttons);
        HuPrcVSleep();
    }
    func_801133EC_option(0);
    return selection;
}

void func_8010A66C_option(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    func_8001F38C_main(0, 64, 64);
    func_801123D8_option();
    HuAudSeqPlay(0x4A);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = func_8010A498_option();
    func_801133A0_option(0);
    switch (selection) {
        case 4:
            HuVecCopy3F(&pos, &D_801137FC_option);
            HuVecCopy3F(&at, &D_80113808_option);
            pos.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            func_801132AC_option(1, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
            goto fadeOut;
        case 5:
            HuVecCopy3F(&pos, &D_80113814_option);
            HuVecCopy3F(&at, &D_80113820_option);
            pos.z -= 200.0f;
            func_80106F88_option(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            func_801132AC_option(1, 0);
            func_8011331C_option(1, 12, 0);
            func_801132E4_option(1, 0);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
        case 0:
        case 1:
        case 2:
        case 3:
        fadeOut:
            result = selection;
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    func_80112A44_option();
    func_8005F524_main();
    omOvlKill();
    switch (result) {
        case 4:
            omOvlGotoEx(0x7B, 1, 0x91);
            break;
        case 5:
            omOvlGotoEx(0x7B, 2, 0x91);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010A8DC_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            if (!(D_800D09A8_main & 1)) {
                val1 = 0xE0;
                val2 = 0x38;
            } else {
                val1 = 0xB8;
                val2 = 0x38;
            }
            break;
        case 1:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 4:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 5:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 6:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

s32 func_8010A940_option(s32 selection, s32 buttons) {
    Vec pos, at;
    Vec(*camera)[2];
    s32 x, y, endX, endY;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 2;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113258_option(6);
                func_80113258_option(7);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(2, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0A);
            } else if (buttons & 0x100) {
                selection = 3;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113258_option(6);
                func_80113258_option(7);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(3, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E09);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 4;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(4, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 0;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(0, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E06);
                func_8011323C_option(6);
                func_8011323C_option(7);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 0;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(0, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E06);
                func_8011323C_option(6);
                func_8011323C_option(7);
            } else if (buttons & 0x100) {
                selection = 5;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(5, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0B);
            }
            break;
        case 4:
            if (buttons & 0x200) {
                selection = 5;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(5, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 2;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(2, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E0A);
            }
            break;
        case 5:
            if (buttons & 0x200) {
                selection = 3;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                func_80107758_option(&pos, &at, 20);
                func_801133A0_option(0);
                func_80113440_option(0);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(3, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4E09);
            } else if (buttons & 0x100) {
                selection = 4;
                camera = D_80113580_option;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                func_80107758_option(&pos, &at, 8);
                func_80113368_option(0, &x, &y);
                func_8010A8DC_option(4, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 8);
                func_80113408_option(0, 0x4E0B);
            }
            break;
        case 1:
        default:
            break;
    }
    return selection;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CB8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010AF54_option);

void func_8010B654_option(s32 selection, s32 buttons) {
    s32 x, y;

    func_8010A8DC_option(selection, &x, &y);
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

s32 func_8010B68C_option(s32 selection, s32 buttons) {
    Vec pos, at, up;
    s32 x, y, endX, endY;

    up = D_80113A98_option;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
            } else if (buttons & 0x100) {
                selection = 2;
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                HuVecCopy3F(&pos, &D_80113694_option[0]);
                HuVecCopy3F(&at, &D_801136B8_option);
                func_80107758_option(&pos, &at, 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e12);
            } else if (buttons & 0x100) {
                selection = 2;
                func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_80113694_option[0], &D_80113694_option[1], &up, D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e0e);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 1;
                func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 7);
                func_80113368_option(0, &x, &y);
                func_8010998C_option(&D_8011367C_option[0], &D_8011367C_option[1], &up, D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &endX, &endY);
                func_80109B7C_option(0, x, y, endX, endY, 7);
                func_80113408_option(0, 0x4e10);
            } else if (buttons & 0x100) {
                selection = 3;
                HuVecCopy3F(&pos, &D_80113694_option[0]);
                HuVecCopy3F(&at, &D_801136B8_option);
                func_80107758_option(&pos, &at, 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e12);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                func_80107758_option(&D_80113694_option[0], &D_80113694_option[1], 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e0e);
            } else if (buttons & 0x100) {
                selection = 1;
                func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
                func_801133A0_option(0);
                func_80113440_option(0);
                HuPrcSleep(30);
                func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
                func_80112028_option(0, x, y);
                func_80113384_option(0);
                func_80113424_option(0);
                func_80113408_option(0, 0x4e10);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

s32 func_8010BACC_option(s32 selection, s32 arg1) {
    Vec pos, at;
    s32 result = -1;
    s32 choice;
    s32 model;

    switch (selection) {
        case 0:
            break;
        case 1:
            func_801133A0_option(0);
            HuAudFXPlay(0x2E6);
            func_80113338_option(8, 12, 0, 8, 2);
            func_801132E4_option(4, 0);
            func_801132C8_option(4, 7);
            func_80113300_option(4);
            func_80113408_option(0, 0x4E11);
            choice = func_8011345C_option(0);
            if (choice == 0) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_8010C3E4_option(0xE002E, 160, 120);
            } else if (choice == 1) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_8010D5B0_option(0xE002E, 160, 120);
            }
            func_80113408_option(0, 0x4E10);
            func_80106F88_option(&D_8011367C_option[0], &D_8011367C_option[1], 30);
            func_80113338_option(8, 10, 0, 8, 2);
            func_801132C8_option(4, 7);
            func_801132AC_option(4, 4);
            HuPrcSleep(30);
            model = func_80113218_option(4);
            while (HmfModelData[(s16)model].unk40 != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 2:
            func_801133A0_option(0);
            HuAudFXPlay(0x2E6);
            func_80113338_option(9, 12, 0, 8, 2);
            func_801132E4_option(5, 0);
            func_801132C8_option(5, 7);
            func_80113300_option(5);
            func_80113408_option(0, 0x4E0F);
            if (func_8011345C_option(0) == 0) {
                HuVecCopyXYZ(&pos, 195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, 195.0f, 160.0f, -665.0f);
                func_80106F88_option(&pos, &at, 20);
                func_80113440_option(0);
                HuPrcSleep(20);
                func_80107F50_option(0xE002D, 160, 120);
            }
            func_80113408_option(0, 0x4E0E);
            func_80106F88_option(&D_80113694_option[0], &D_80113694_option[1], 30);
            func_80113338_option(9, 11, 0, 8, 2);
            func_801132C8_option(5, 7);
            func_801132AC_option(5, 4);
            HuPrcSleep(30);
            model = func_80113218_option(5);
            while (HmfModelData[(s16)model].unk40 != 0.0f) {
                HuPrcVSleep();
            }
            func_80113424_option(0);
            func_80113384_option(0);
            break;
        case 3:
            func_801133A0_option(0);
            func_80113408_option(0, 0x4E13);
            if (func_8011345C_option(0) == 0) {
                result = 3;
            } else {
                switch (selection) {
                    case 0:
                    default:
                        break;
                    case 1:
                        func_80113408_option(0, 0x4E10);
                        break;
                    case 2:
                        func_80113408_option(0, 0x4E0E);
                        break;
                    case 3:
                        func_80113408_option(0, 0x4E12);
                        break;
                }
                func_80113384_option(0);
                result = -1;
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = 4;
            break;
    }
    return result;
}

void func_8010BFA4_option(s32 selection, s32 buttons) {
    s32 x = 160;
    s32 y = 120;

    switch (selection) {
        case 0:
            break;
        case 1:
            func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
            break;
        case 2:
            func_80109908_option(D_80113898_option.x, D_80113898_option.y, D_80113898_option.z, &x, &y);
            break;
        case 3:
            func_80109908_option(D_801138A4_option.x, D_801138A4_option.y, D_801138A4_option.z, &x, &y);
            break;
    }
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

s32 func_8010C04C_option(void) {
    s32 x, y;
    s32 buttons;
    s32 selection;
    s32 next;

    func_801133BC_option(0, 0x4E0D);
    func_80113490_option(0);
    func_80113408_option(0, 0x4E10);
    selection = 1;
    func_80107758_option(&D_8011367C_option[0], &D_8011367C_option[1], 20);
    HuPrcSleep(20);
    func_80109908_option(D_8011388C_option.x, D_8011388C_option.y, D_8011388C_option.z, &x, &y);
    func_80112028_option(0, x, y);
    func_80113384_option(0);
    func_8010BFA4_option(1, 0);
    {
        Vec pos, at;
        while (1) {
            buttons = D_800D5558_main[0];
            buttons |= func_801130E8_option(0);
            if (buttons & 0x8000) {
                next = func_8010BACC_option(selection, buttons);
                if (next != -1) {
                    selection = next;
                    break;
                }
            } else if (buttons & 0xF00) {
                selection = func_8010B68C_option(selection, buttons);
            } else if (buttons & 0x4000) {
                func_801133A0_option(0);
                func_80113440_option(0);
                switch (selection) {
                    case 0:
                    case 1:
                    case 2:
                        selection = 3;
                        HuVecCopy3F(&pos, &D_801136AC_option[0]);
                        HuVecCopy3F(&at, &D_801136AC_option[1]);
                        func_80107758_option(&pos, &at, 20);
                        HuPrcSleep(20);
                        break;
                    case 3:
                    default:
                        selection = 3;
                        break;
                }
                func_80113424_option(0);
                func_80113408_option(0, 0x4E12);
                func_80113384_option(0);
            }
            func_8010BFA4_option(selection, buttons);
            HuPrcVSleep();
        }
    }
    func_801133EC_option(0);
    return selection;
}

void func_8010C224_option(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    func_8001F38C_main(0, 64, 64);
    func_80112B08_option();
    func_8004A9DC_main(0x60);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = func_8010C04C_option();
    func_801133A0_option(0);
    switch (selection) {
        case 3:
            HuVecCopy3F(&pos, &D_801138B0_option);
            pos.z -= 200.0f;
            pos.y -= 40.0f;
            HuVecCopy3F(&at, &D_801138BC_option);
            at.y -= 40.0f;
            HuAudFXPlay(0x2EB);
            func_801132E4_option(1, 0);
            func_801132C8_option(1, 7);
            func_80113300_option(1);
            pos.z += 200.0f;
            func_80106F88_option(&pos, &at, 20);
            result = selection;
            func_8010FFDC_option();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            func_8004A9DC_main(0x7F);
            HuPrcSleep(20);
            break;
        case 0:
        case 1:
        case 2:
        case 4:
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    func_80112E14_option();
    func_8005F524_main();
    omOvlKill();
    switch (result) {
        case 3:
            omOvlReturnEx(1);
            break;
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(D_80114770_option);
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C3E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010D5B0_option);

void func_8010E77C_option(s32 x, s32 y, s32 frame) {
    func_80112028_option(1, (s32)(x + sindf(frame * 18) * 4.0f) - 2, y);
}

void func_8010E7FC_option(s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    s32 dx;
    s32 dy;
    f32 t;

    i = 0;
    dx = endX - startX;
    dy = endY - startY;
    for (;; i++) {
        HuPrcVSleep();
        t = (f32)i / duration;
        func_80112028_option(1, dx * t + startX, dy * t + startY);
        if (i == duration) {
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010E8E0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010F138_option);

f32 func_8010F914_option(f32 x, f32 y) {
    return -(atan2df(y, x) - 90.0f);
}

void func_8010F94C_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114788_option); i++) {
        HuVecCopyXYZ(&D_80114788_option[i].unk_00, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].unk_0C, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&D_80114788_option[i].unk_18, 0.0f, 0.0f, 0.0f);
        D_80114788_option[i].obj = NULL;
    }
}

void func_8010FA28_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114788_option); i++) {
        omDelObj(D_80114788_option[i].obj);
    }
}

void func_8010FA7C_option(omObjData *obj) {
    Vec pos;
    Vec at;
    Vec up;
    Vec modelPos;
    Vec direction;
    s32 model;

    model = D_80114788_option[obj->work[0]].unk_24;
    func_80105FF8_option(&pos, &at, &up);
    func_80113274_option(model, &modelPos.x, &modelPos.y, &modelPos.z);
    HuVecCopyXYZ(&direction, pos.x - modelPos.x, pos.y - modelPos.y, pos.z - modelPos.z);
    func_80113290_option(model, 0.0f, func_8010F914_option(direction.x, direction.z), 0.0f);
}

void func_8010FB40_option(s32 index, s32 model) {
    f32 x, y, z;

    if (D_80114788_option[index].obj != NULL) {
        omDelObj(D_80114788_option[index].obj);
    }
    func_80113274_option(model, &x, &y, &z);
    HuVecCopyXYZ(&D_80114788_option[index].unk_0C, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_80114788_option[index].unk_18, x, y, z);
    D_80114788_option[index].unk_24 = model;
    D_80114788_option[index].obj = omAddObj(6, 0, 0, -1, func_8010FA7C_option);
    D_80114788_option[index].obj->work[0] = index;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D78_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113DA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_8011421C_option);

u16 func_8010FC40_option(s32 value) {
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            cam = HmfModelData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, D_80113A4C_option, value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_8010FDF4_option(void) {
    D_801147E0_option.obj = NULL;
}

s32 func_8010FE00_option(void) {
    return D_801147E0_option.obj != NULL;
}

void func_8010FE10_option(void) {
    s16 modelId;

    if (D_801147E0_option.obj != NULL) {
        modelId = func_80113218_option(2);
        func_80033910_main(HmfModelData[modelId].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(D_801147E0_option.obj);
        D_801147E0_option.obj = NULL;
    }
}

void func_8010FE84_option(omObjData *obj) {
    s16 modelId;

    if (func_800078F8_main(D_801147E0_option.seNo) == 0) {
        modelId = func_80113218_option(2);
        func_80033910_main(HmfModelData[modelId].hmf);
        HuAudFXStop((s16)D_801147E0_option.seNo);
        omDelObj(obj);
        D_801147E0_option.obj = NULL;
    }
}

omObjData *func_8010FF0C_option(s32 seNo) {
    if (D_801147E0_option.obj != NULL) {
        omDelObj(D_801147E0_option.obj);
    }
    D_801147E0_option.obj = omAddObj(6, 0, 0, -1, func_8010FE84_option);
    D_801147E0_option.seNo = seNo;
    func_800078F8_main(seNo);
    return D_801147E0_option.obj;
}

void func_8010FF88_option(omObjData *obj) {
    s32 *counter;

    if (D_801147E8_option == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_801147E8_option;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

void func_8010FFDC_option(void) {
    D_801147E8_option = 0;
    omAddObj(6, 0, 0, -1, func_8010FF88_option);
}

s32 func_80110018_option(void) {
    s32 type;
    s16 counts[9];
    s16 i;
    s16 minigameType;

    for (i = 0; i < 9; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        minigameType = D_800A6D40_main[i].minigameType;
        if ((D_800A6D40_main[i].overlay == 0x70) | (D_800A6D40_main[i].overlay == -1)) {
            continue;
        }
        if ((i == 27) | (i == 8)) {
            continue;
        }
        if (i == 16) {
            continue;
        }
        type = minigameType;
        if (type < 5 && GWMgUnlockCheck(i) != 0) {
            if (++counts[type] >= 3) {
                return 1;
            }
        }
    }
    return 0;
}
