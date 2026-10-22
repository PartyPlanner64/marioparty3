#include "common.h"
#include "game/vibrator.h"
#include "mallocblock.h"

typedef struct UnkOption {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s32 unk_28;
} UnkOption;

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OptSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
} OptSprSlot; // sizeof 0x2

typedef struct {
    /* 0x00 */ s16 winID;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s32 unk_08;
} OptWinEntry; // sizeof 0xC

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
} OptCam; // sizeof 0x3C

// Object that keeps an attached 3d model sound playing for a fixed duration.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 seNo;
} OptSeObj; // sizeof 0x8

extern char D_80113A4C_option[];
extern Vec D_8011376C_option[];
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
void func_801059D0_option(void);
void func_80105FF8_option(Vec *, Vec *, Vec *);
void func_80113274_option(s32, f32 *, f32 *, f32 *);
void func_80113290_option(s32, f32, f32, f32);
omObjData *func_80106F88_option(Vec *, Vec *, s32);
void func_8010744C_option(omObjData *);
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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801059D0_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105F08_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105FF8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106508_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106998_option);

void func_80106B78_option(void) {
    if (D_801146F0_option.obj != NULL) {
        omDelObj(D_801146F0_option.obj);
    }
    D_801146F0_option.obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106BAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106C7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106F88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107058_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010737C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010744C_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801077BC_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109504_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109730_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109D04_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109EF4_option);

void func_8010A3E8_option(s32 selection) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A498_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A66C_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A940_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CB8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010AF54_option);

void func_8010B654_option(s32 selection) {
    s32 x, y;

    func_8010A8DC_option(selection, &x, &y);
    func_801096B8_option(0, x, y);
    func_801096E4_option(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010B68C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010BACC_option);

void func_8010BFA4_option(s32 selection) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C04C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C224_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110018_option);

void func_80110170_option(void) {
    func_8011019C_option();
    func_80110754_option();
    func_801119CC_option();
}

void func_8011019C_option(void) {
    s32 i;
    OptSpr *p;
    f32 zero;

    for (i = 0; i < ARRAY_COUNT(D_801147F0_option); i++) {
        D_80114EF0_option[i].espriteSlot = -1;
        D_801147F0_option[i].espriteSlot = -1;
        p = &D_801147F0_option[i];
        zero = 0.0f;
        p->unk_08 = 0;
        D_801147F0_option[i].unk_04 = 0;
        p->unk_10 = zero;
        D_801147F0_option[i].unk_0C = zero;
        D_801147F0_option[i].unk_14 = zero;
        D_801147F0_option[i].unk_18 = -1;
    }
}

s16 func_80110230_option(s32 arg0) {
    return D_80114EF0_option[arg0].espriteSlot;
}

s16 func_80110244_option(s32 arg0) {
    return D_801147F0_option[arg0].espriteSlot;
}

void func_80110260_option(s32 arg0, s32 arg1) {
    D_80114EF0_option[arg0].espriteSlot = func_8000B838_main(arg1);
}

void func_80110298_option(s32 arg0) {
    if (D_80114EF0_option[arg0].espriteSlot != -1) {
        HuSprKill(D_80114EF0_option[arg0].espriteSlot);
    }
    D_80114EF0_option[arg0].espriteSlot = -1;
}

void func_801102F0_option(s32 arg0, s16 arg1) {
    D_801147F0_option[arg0].espriteSlot = InitEspriteSlot(D_80114EF0_option[arg1].espriteSlot, 0, 0);
    func_8011053C_option(arg0, 0xA0, 0x78);
}

void func_80110358_option(s32 arg0) {
    if (D_801147F0_option[arg0].espriteSlot != -1) {
        func_8000C184_main(D_801147F0_option[arg0].espriteSlot);
    }
    D_801147F0_option[arg0].espriteSlot = -1;
}

void func_801103C8_option(s32 arg0, s32 resourceId) {
    func_80110260_option(arg0, resourceId);
    func_801102F0_option(arg0, arg0);
}

void func_801103FC_option(s32 arg0, s32 resourceId) {
    func_801103C8_option(arg0, resourceId);
    func_8000BC48_main(D_801147F0_option[arg0].espriteSlot, 0x4000);
}

void func_80110440_option(s32 arg0) {
    func_80110358_option(arg0);
    func_80110298_option(arg0);
}

void func_8011046C_option(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(D_801147F0_option); i++) {
        func_80110440_option(i);
    }
}

void func_801104A4_option(s32 arg0) {
    func_8000BB54_main(D_801147F0_option[arg0].espriteSlot);
}

void func_801104D4_option(s32 arg0) {
    func_8000BB94_main(D_801147F0_option[arg0].espriteSlot);
}

void func_80110504_option(s32 arg0) {
    func_801104A4_option(arg0);
}

void func_80110520_option(s32 arg0) {
    func_801104D4_option(arg0);
}

void func_8011053C_option(s32 arg0, s32 arg1, s32 arg2) {
    D_801147F0_option[arg0].unk_04 = arg1;
    D_801147F0_option[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

void func_80110594_option(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = D_801147F0_option[arg0].unk_04;
    *arg2 = D_801147F0_option[arg0].unk_08;
}

void func_801105C4_option(s32 arg0, f32 arg1, f32 arg2) {
    D_801147F0_option[arg0].unk_0C = arg1;
    D_801147F0_option[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

void func_80110614_option(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_8011064C_option(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_80110680_option(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_801106B4_option(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_801106E8_option(s32 arg0, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_801147F0_option[arg0].espriteSlot, 1);
    func_8000BD94_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

void func_80110754_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114F70_option); i++) {
        D_80114F70_option[i].unk_00 = -1;
        D_80114F70_option[i].unk_02 = -1;
    }
}

void func_801107A0_option(s32 arg0, s32 arg1, s32 arg2) {
    s16 model;

    model = func_8000B108_main(arg1, arg2);
    D_80114F70_option[arg0].unk_00 = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_8011083C_option(s32 arg0, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    D_80114F70_option[arg0].unk_02 = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_801108C4_option(s32 arg0) {
    if (D_80114F70_option[arg0].unk_00 != -1) {
        func_8001ACDC_main(D_80114F70_option[arg0].unk_00);
        D_80114F70_option[arg0].unk_00 = -1;
    }
    if (D_80114F70_option[arg0].unk_02 != -1) {
        func_8002D4B8_main(D_80114F70_option[arg0].unk_02);
        D_80114F70_option[arg0].unk_02 = -1;
    }
}

void func_80110974_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114F70_option); i++) {
        func_801108C4_option(i);
    }
}

s16 func_801109AC_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_00;
}

s16 func_801109D0_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_02;
}

void func_801109F4_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_1C = arg1;
    D_80114F70_option[arg0].unk_20 = arg2;
    D_80114F70_option[arg0].unk_24 = arg3;
    Hu3DModelRotSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110A5C_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_04 = arg1;
    D_80114F70_option[arg0].unk_08 = arg2;
    D_80114F70_option[arg0].unk_0C = arg3;
    Hu3DModelPosSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110AD0_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_10 = arg1;
    D_80114F70_option[arg0].unk_14 = arg2;
    D_80114F70_option[arg0].unk_18 = arg3;
    Hu3DModelScaleSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110B38_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_04;
    *arg2 = D_80114F70_option[arg0].unk_08;
    *arg3 = D_80114F70_option[arg0].unk_0C;
}

void func_80110B8C_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_1C;
    *arg2 = D_80114F70_option[arg0].unk_20;
    *arg3 = D_80114F70_option[arg0].unk_24;
}

void func_80110BD4_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_10;
    *arg2 = D_80114F70_option[arg0].unk_14;
    *arg3 = D_80114F70_option[arg0].unk_18;
}

void func_80110C1C_option(s32 arg0) {
    func_8001C258_main(D_80114F70_option[arg0].unk_00, 4, 4);
}

void func_80110C5C_option(s32 arg0) {
    func_8001C258_main(D_80114F70_option[arg0].unk_00, 4, 0);
}

void func_80110C9C_option(s32 arg0, s32 arg1) {
    func_8001C814_main(D_80114F70_option[arg0].unk_00, -1, arg1);
}

void func_80110CE0_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
    func_8001C624_main(D_80114F70_option[arg0].unk_00, D_80114F70_option[arg1].unk_02, arg2, arg3, arg4);
}

void func_80110D50_option(s32 arg0, s32 arg1) {
    func_8001C814_main(D_80114F70_option[arg0].unk_00, arg1, 0);
}

void func_80110D94_option(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_80114F70_option[arg0].unk_00);
}

void func_80110DCC_option(s32 arg0, u32 arg1) {
    func_8001C6A8_main(D_80114F70_option[arg0].unk_00, arg1);
}

void func_80110E30_option(s32 arg0) {
    while (HmfModelData[D_80114F70_option[arg0].unk_00].unk40 != D_800CCF58_main[HmfModelData[D_80114F70_option[arg0].unk_00].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80110ED0_option(s32 arg0) {
    s16 modelId = D_80114F70_option[arg0].unk_00;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void func_80110F58_option(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = func_801109AC_option(arg0);
    s16 parentModelId = func_801109D0_option(arg1);

    func_8001F304_main(modelId, parentModelId);
    func_8001C814_main(modelId, -1, arg2);
}

void func_80110FC8_option(void) {
    // The original call omits the resource id.
    D_80115A70_option = ((s16 (*)())func_8000B838_main)();
    D_80115A72_option = InitEspriteSlot(D_80115A70_option, 0, 0);
    func_8000BC48_main(D_80115A72_option, 0x4000);
    func_8000BBD4_main(D_80115A72_option, 0xA0, 0x78);
}

void func_8011102C_option(void) {
    func_8000C184_main(D_80115A72_option);
    HuSprKill(D_80115A70_option);
}

u32 func_80111058_option(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = func_800452A0_main(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801110C0_option);

s32 func_8011130C_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_8005BEE0_main(winID, 255);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C154_main(winID, 192, 192, 192);
    func_8005FBF8_main(winID, 0, 64, 64);
    func_8005C02C_main(winID, 7);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111458_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 4);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_8005BEE0_main(winID, 255);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C060_main(winID, 5, 0, 176, 192);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005C154_main(winID, 192, 192, 192);
    func_8005FBF8_main(winID, 255, 255, 255);
    func_8005C02C_main(winID, 1);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_801115C0_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C060_main(winID, 5, 0, 176, 192);
    func_8005C060_main(winID, 7, 255, 255, 255);
    func_8005C060_main(winID, 0, 0, 0, 0);
    func_8005C060_main(winID, 3, 0, 0, 0);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005C154_main(winID, 192, 192, 0);
    func_8005FBF8_main(winID, 255, 255, 255);
    func_8005C02C_main(winID, 6);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111768_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 19);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_80060C14_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111834_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 20);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_80060C14_main(winID, 0);
    func_8005FE54_main(winID, 1);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111900_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 19);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005FE54_main(winID, 1);
    func_80060C14_main(winID, 0);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

void func_801119CC_option(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80115A78_option[i].winID = -1;
        D_80115A78_option[i].unk_04 = 0;
    }
}

void func_80111A10_option(s32 arg0) {
    if (D_80115A78_option[arg0].unk_08 == 3) {
        func_80060EA8_main(D_80115A78_option[arg0].winID, 1);
        func_800610E0_main(D_80115A78_option[arg0].winID);
    } else {
        func_8005FE90_main(D_80115A78_option[arg0].winID);
        func_8005F364_main(D_80115A78_option[arg0].winID);
        D_80115A78_option[arg0].winID = -1;
    }
    if (D_80115A78_option[arg0].unk_04 != NULL) {
        func_80019C00_main(D_80115A78_option[arg0].unk_04);
        D_80115A78_option[arg0].unk_04 = NULL;
    }
}

void func_80111AF4_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115A78_option); i++) {
        if (D_80115A78_option[i].winID != -1) {
            func_80111A10_option(i);
        }
    }
}

void func_80111B58_option(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BB18_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

void func_80111B88_option(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

void func_80111BF0_option(s32 arg0) {
    func_8005FFA8_main(D_80115A78_option[arg0].winID);
}

void func_80111C20_option(s32 arg0) {
    func_8005FE90_main(D_80115A78_option[arg0].winID);
}

void func_80111C50_option(s32 arg0, u32 arg1) {
    u32 message;

    func_8005D294_main(D_80115A78_option[arg0].winID);
    if (D_80115A78_option[arg0].unk_04 != NULL) {
        func_80019C00_main(D_80115A78_option[arg0].unk_04);
        D_80115A78_option[arg0].unk_04 = NULL;
    }
    message = func_80111058_option(arg1);
    if (message > 0x80000000U) {
        D_80115A78_option[arg0].unk_04 = (void *)message;
    }
    func_8005B43C_main(D_80115A78_option[arg0].winID, message, -1, -1);
}

void func_80111D1C_option(s32 arg0, s8 arg1, u32 arg2) {
    func_800601BC_main(D_80115A78_option[arg0].winID, arg2, arg1);
}

void func_80111D58_option(s32 arg0, s16 arg1, s32 arg2) {
    func_8005E1D8_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

s16 func_80111D90_option(s32 arg0) {
    return D_80115A78_option[arg0].winID;
}

void func_80111DAC_option(s32 arg0) {
    while (func_8005E0C0_main(D_80115A78_option[arg0].winID) != 0) {
        HuPrcVSleep();
    }
}

void func_80111E00_option(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_80111E3C_option(s32 arg0, s16 arg1) {
    func_8005BE30_main(D_80115A78_option[arg0].winID, arg1);
}

u16 func_80111E74_option(s32 value) {
    static const char exitFormat[] = "\n%d\n";
    static const char posFormat[] = "POS:%4.2f,%4.2f,%4.2f";
    static const char atFormat[] = "A T:%4.2f,%4.2f,%4.2f";
    static const char upFormat[] = "U P:%4.2f,%4.2f,%4.2f";
    static const char valueFormat[] = "%d";
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, exitFormat, value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            cam = HmfModelData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, posFormat, cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, atFormat, cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, upFormat, cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, valueFormat, value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_80112028_option(s32 arg0, s32 arg1, s32 arg2) {
    func_8011053C_option(arg0, arg1, arg2);
}

void func_80112044_option(s32 arg0, u16 arg1) {
    func_80110614_option(arg0, arg1);
}

void func_80112060_option(void) {
    func_80110170_option();
    func_80105D10_option();
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112084_option);

void func_8011239C_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80114674_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80114680_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801123D8_option);

void func_80112A44_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_801108C4_option(13);
    func_801108C4_option(14);
    func_801108C4_option(15);
    func_801108C4_option(16);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112B08_option);

void func_80112E14_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_80112EB8_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x2A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80112F48_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x6A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80112FD8_option(s32 arg0, s32 resourceId, s32 arg2) {
    func_8011083C_option(arg0, resourceId, arg2);
}

void func_80112FF4_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x2002A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80113088_option(void) {
    func_801103C8_option(0, 0x88);
    func_801106B4_option(0, 5);
    func_8011053C_option(0, 0xA0, 0x71);
    func_801104D4_option(0);
}

void func_801130CC_option(void) {
    func_80110440_option(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801130E8_option);

u16 func_80113204_option(s32 arg0) {
    return (u16)D_800D0590_main[arg0];
}

s32 func_80113218_option(s32 arg0) {
    return func_801109AC_option(arg0);
}

void func_8011323C_option(s32 arg0) {
    func_80110C5C_option(arg0);
}

void func_80113258_option(s32 arg0) {
    func_80110C1C_option(arg0);
}

void func_80113274_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    func_80110B38_option(arg0, arg1, arg2, arg3);
}

void func_80113290_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_801109F4_option(arg0, arg1, arg2, arg3);
}

void func_801132AC_option(s32 arg0, s32 arg1) {
    func_80110C9C_option(arg0, arg1);
}

void func_801132C8_option(s32 arg0, s32 arg1) {
    func_80110D50_option(arg0, arg1);
}

void func_801132E4_option(s32 arg0, u32 arg1) {
    func_80110DCC_option(arg0, arg1);
}

void func_80113300_option(s32 arg0) {
    func_80110E30_option(arg0);
}

void func_8011331C_option(s32 arg0, s32 arg1, u16 arg2) {
    func_80110F58_option(arg0, arg1, arg2);
}

void func_80113338_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, u16 arg4) {
    func_80110CE0_option(arg0, arg1, arg2, arg3, arg4);
}

void func_80113368_option(s32 arg0, s32 *arg1, s32 *arg2) {
    func_80110594_option(arg0, arg1, arg2);
}

void func_80113384_option(s32 arg0) {
    func_80110504_option(arg0);
}

void func_801133A0_option(s32 arg0) {
    func_80110520_option(arg0);
}

void func_801133BC_option(s32 arg0, u32 arg1) {
    func_801110C0_option(arg0, arg1, 0xA0, 0xC2, 0, 0, 4);
}

void func_801133EC_option(s32 arg0) {
    func_80111A10_option(arg0);
}

void func_80113408_option(s32 arg0, u32 arg1) {
    func_80111C50_option(arg0, arg1);
}

void func_80113424_option(s32 arg0) {
    func_80111BF0_option(arg0);
}

void func_80113440_option(s32 arg0) {
    func_80111C20_option(arg0);
}

void func_8011345C_option(s32 arg0) {
    func_80111DAC_option(arg0);
    func_80111D58_option(arg0, 0, 0);
}

void func_80113490_option(s32 arg0) {
    func_80111DAC_option(arg0);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146BC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146C8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146D4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146E0_option);
