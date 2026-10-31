#include "common.h"

#define FLAG_IDLE 0x1
#define FLAG_SPINNING 0x2
#define FLAG_PLUMMETING 0x200

// Per-player work allocated in func_80107D30_parasol_plummet, stored at ObjData->data
typedef struct ParasolPlummetWork {
    /* 0x00 */ Vec coords;
    /* 0x0C */ f32 angle;
    /* 0x10 */ s32 moveType;
    /* 0x14 */ s32 flags;
    /* 0x18 */ char pad_18[0x2C];
    /* 0x44 */ s32 plummetTimer;
    /* 0x48 */ f32 tiltAngleLimit;
} ParasolPlummetWork; // Size 0x4C

typedef struct ParasolPlummetParasolWork {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ Vec trans;
    /* 0x14 */ char unk_14[0x14];
} ParasolPlummetParasolWork; // Size 0x28

extern omObjData *D_8010AB70_parasol_plummet[0x12];
extern u8 D_8010ABB8_parasol_plummet[0x14];

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801059A0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105B94_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105E94_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80105EC0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106418_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106788_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010687C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010693C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801069E4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106AB4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106CDC_parasol_plummet);

void func_80106DB0_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    if (work->angle > work->tiltAngleLimit) {
        work->angle -= 10.0f;
    }
    if (work->angle < work->tiltAngleLimit) {
        work->angle += 10.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80106E14_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801071B4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801074CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801076D4_parasol_plummet);

f32 func_801079D8_parasol_plummet(omObjData *arg0, s32 arg1) {
    f32 dist = -1.0f;
    ParasolPlummetWork *work = OM_GET_DATA_PTR(arg0, ParasolPlummetWork);
    f32 x = work->coords.x;
    f32 y = work->coords.y;

    if (D_8010ABB8_parasol_plummet[arg1]) {
        ParasolPlummetParasolWork *parasol = OM_GET_DATA_PTR(D_8010AB70_parasol_plummet[arg1], ParasolPlummetParasolWork);
        f32 px = parasol->trans.x;
        f32 py = parasol->trans.y;
        dist = HuSqrtf((px - x) * (px - x) + (py - y) * (py - y));
    }

    return dist;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107A44_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B5C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107B78_parasol_plummet);

void func_80107C30_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);

    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    work->flags &= ~0x100;
}

void func_80107C94_parasol_plummet(omObjData *object) {
    ParasolPlummetWork *work = OM_GET_DATA_PTR(object, ParasolPlummetWork);
    s32 flags = work->flags;

    if (flags & FLAG_SPINNING) {
        return;
    }
    if (flags & FLAG_PLUMMETING) {
        return;
    }
    if (!(flags & FLAG_IDLE)) {
        return;
    }

    work->flags = (flags | FLAG_PLUMMETING) & ~FLAG_IDLE;
    work->plummetTimer = 10;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107CD4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D14_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107D30_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80107E6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010803C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108178_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801082CC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801083F8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010856C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801086F0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108878_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801089E0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108C1C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108DD0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108F6C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80108FFC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801090A8_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801092B0_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801093D4_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109604_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_801096BC_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010995C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109B38_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109D74_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_80109F7C_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A160_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A484_parasol_plummet);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1C_parasol_plummet/1DE610", func_8010A75C_parasol_plummet);
