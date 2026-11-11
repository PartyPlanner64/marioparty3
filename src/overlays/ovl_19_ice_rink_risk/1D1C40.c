#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

// Per-object work block of the hockey puck objects, reached via ObjData->data
typedef struct IceRinkRiskPuckWork {
    /* 0x00 */ char pad_00[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char pad_4C[4];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ s8 unk54;
    /* 0x55 */ char pad_55[1];
    /* 0x56 */ u16 unk56; // Puck index
    /* 0x58 */ char pad_58[0x1C];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ char pad_80[4];
    /* 0x84 */ s32 unk84[9];
    /* 0xA8 */ char pad_A8[4];
} IceRinkRiskPuckWork; // Size 0xAC

// Most recent puck to puck collision, per puck
typedef struct IceRinkRiskPuckHit {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec pos;
} IceRinkRiskPuckHit; // Size 0x14

extern s32 D_800A178C_main[][6];
extern omObjData *D_800EBE70_minigame[];
extern Vec D_800EC298_minigame[];

extern Vec D_80108550_ice_rink_risk;
extern Vec D_8010855C_ice_rink_risk;
extern Vec D_80108568_ice_rink_risk;
extern Vec D_80108574_ice_rink_risk;
extern f32 D_80108584_ice_rink_risk[][3];
extern IceRinkRiskPuckHit D_801085B0_ice_rink_risk[];
extern s32 D_801085EC_ice_rink_risk[];
extern s32 D_801085F8_ice_rink_risk;
extern s32 D_80108634_ice_rink_risk;
extern s32 D_80108684_ice_rink_risk;
extern s32 D_801086E8_ice_rink_risk;
extern s32 D_801086EC_ice_rink_risk;
extern s32 D_801086F0_ice_rink_risk;
extern s32 D_801086F4_ice_rink_risk;
extern s32 D_8010864C_ice_rink_risk[4];
extern s8 D_8010865C_ice_rink_risk[4][2];
extern f32 D_80108664_ice_rink_risk[4];
extern f32 D_80108674_ice_rink_risk[4];
extern s32 D_801085FC_ice_rink_risk[4];
extern f32 D_800EB760_minigame;

void func_80106710_ice_rink_risk(omObjData *object, s32 model, s32 motion, s32 player);
s32 func_80106A60_ice_rink_risk(omObjData *object, omObjData *other);
void func_80106C54_ice_rink_risk(omObjData *object);
s32 func_80106E20_ice_rink_risk(omObjData *object);
s32 func_80106FC0_ice_rink_risk(omObjData *object);
void func_8010796C_ice_rink_risk(omObjData *object);
f32 func_80107D14_ice_rink_risk(omObjData *object, Hu3DSphere *sphere);
void func_80107DEC_ice_rink_risk(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_80107F24_ice_rink_risk(omObjData *object, Hu3DSphere *sphere, Vec *normal);
void func_80107F58_ice_rink_risk(omObjData *object, f32 x, f32 y, f32 z);
void func_80108134_ice_rink_risk(omObjData *object, Hu3DSphere *sphere);
void func_8010826C_ice_rink_risk(omObjData *object);
void func_80108384_ice_rink_risk(omObjData *object, f32 dx, f32 dz);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_801059A0_ice_rink_risk);

void func_80105E34_ice_rink_risk(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80105E60_ice_rink_risk(void) {
    D_801085EC_ice_rink_risk[D_801085F8_ice_rink_risk] = 1;
    D_801085F8_ice_rink_risk++;
    HuAudFXPlay(0x3D3);
}

void func_80105EA4_ice_rink_risk(void) {
    omObjData *puck;
    s32 i;

    for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
        puck = D_800EBE70_minigame[i];
        func_8001C258_main(puck->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(puck->model[2], 0);
        Hu3DModelPosSet(puck->model[2], puck->trans.x, puck->trans.y, puck->trans.z);
        Hu3DModelScaleSet(puck->model[2], 1.2f, 1.2f, 1.2f);
        func_8001C258_main(puck->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(puck->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        puck->func = NULL;
    }
    D_80108634_ice_rink_risk = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80105FAC_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106198_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106554_ice_rink_risk);

void func_80106710_ice_rink_risk(omObjData *object, s32 model, s32 motion, s32 player) {
    func_800E1BA8_minigame_ObjData *data;
    s32 chr;

    func_800E1BA8_minigame(object, model, motion, player, 0xA99, 0xA99);
    data = object->data;
    chr = GwPlayer[data->unk59].chr;
    object->model[3] = func_8000B108_main(3, 0x88D);
    object->model[4] = func_8000B108_main(4, 0x88D);
    object->model[5] = func_8000B108_main(6, 0x88D);
    object->model[7] = func_8000B108_main(8, 0x88D);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(object, 9, func_80017BB8_main(chr, 7), 1, 0x27);
    func_800E5A00_minigame(object, 0x11, func_80017BB8_main(chr, 0xE), 1, 0xF);
    func_800E5A00_minigame(object, 0xA, func_80017BB8_main(chr, 0x11), 1, 0x27);
    func_800E5A00_minigame(object, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(object, 0x1E, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(object, 0x1F, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5A00_minigame(object, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5A00_minigame(object, 0x26, func_80017BB8_main(chr, 0x1A), 1, 0);
    func_800E5978_minigame(object, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5978_minigame(object, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x78);
    data->unkEC = func_80106A60_ice_rink_risk;
    func_800E149C_minigame(object, 0, 2);
    func_800E3568_minigame(data, 0, func_80106FC0_ice_rink_risk);
    func_800E3568_minigame(data, 1, func_80106E20_ice_rink_risk);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106A60_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106C54_ice_rink_risk);

s32 func_80106E20_ice_rink_risk(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;

    if (GwPlayer[data->unk59].stat & 1) {
        D_800D5558_main[data->unk57] = D_801086EC_ice_rink_risk;
        D_800CDA7C_main[data->unk57] = D_801086E8_ice_rink_risk;
        D_800CBB6E_main[data->unk57] = D_801086F0_ice_rink_risk;
        D_800D20A1_main[data->unk57] = D_801086F4_ice_rink_risk;
    }
    if (object->trans.y < -2000.0f) {
        object->func = NULL;
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (D_8010864C_ice_rink_risk[data->unk59] == 1) {
        func_800E5798_minigame(object, 0x26);
        data->unk38 = -D_800EB744_minigame;
        data->unk3C = atan2df(object->trans.x, object->trans.z);
        data->unk40 = D_800EB760_minigame * 0.8f;
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_801085FC_ice_rink_risk[data->unk59] = 0;
        object->func = func_80106C54_ice_rink_risk;
        data->unk50 |= 0x400;
    }
    return 1;
}

s32 func_80106FC0_ice_rink_risk(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    omObjData *puck;
    Vec dir;
    s32 player = data->unk59;
    s32 pad = data->unk57;
    s32 difficulty;
    s32 best;
    s32 i;
    f32 bestDist;
    f32 dist;
    f32 plusDist;
    f32 angle;
    f32 dx, dy, dz;

    if (func_800E6E8C_minigame() == 2 && !(GwPlayer[player].stat & 1)) {
        return 1;
    }
    D_801086EC_ice_rink_risk = D_800D5558_main[pad];
    D_801086E8_ice_rink_risk = (u16)D_800CDA7C_main[pad];
    D_801086F0_ice_rink_risk = D_800CBB6E_main[pad];
    D_801086F4_ice_rink_risk = D_800D20A1_main[pad];
    D_800D20A1_main[pad] = 0;
    D_800CBB6E_main[pad] = 0;
    D_800D5558_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    difficulty = GwPlayer[data->unk59].cpu_difficulty;
    if (data->unk38 != 1000.0f) {
        D_800CBB6E_main[pad] = D_8010865C_ice_rink_risk[player][0];
        D_800D20A1_main[pad] = D_8010865C_ice_rink_risk[player][1];
        D_800CDA7C_main[pad] |= 0x8000;
    } else {
        bestDist = 20000.0f;
        best = -1;
        for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
            puck = D_800EBE70_minigame[i];
            dx = object->trans.x - puck->trans.x;
            dy = object->trans.y - puck->trans.y;
            dz = object->trans.z - puck->trans.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < bestDist) {
                bestDist = dist;
                best = i;
            }
        }
        if (bestDist < D_80108674_ice_rink_risk[difficulty] + 150.0f) {
            puck = D_800EBE70_minigame[best];
            dir.x = object->trans.x - puck->trans.x;
            dir.y = 0.0f;
            dir.z = object->trans.z - puck->trans.z;
            func_800202FC_main(&dir);
            D_800CBB6E_main[pad] = dir.x * 60.0f * D_80108664_ice_rink_risk[difficulty];
            D_800D20A1_main[pad] = dir.z * -60.0f * D_80108664_ice_rink_risk[difficulty];
            D_800D5558_main[pad] |= 0x8000;
        } else if (bestDist < 400.0f) {
            puck = D_800EBE70_minigame[best];
            dx = object->trans.x;
            dz = object->trans.z;
            dist = HuSqrtf(dx * dx + dz * dz);
            angle = atan2df(dx, dz);
            dx = sindf(angle + 10.0f) * dist - puck->trans.x;
            dz = cosdf(angle + 10.0f) * dist - puck->trans.z;
            plusDist = HuSqrtf(dx * dx + dz * dz);
            dx = sindf(angle - 10.0f) * dist - puck->trans.x;
            dz = cosdf(angle - 10.0f) * dist - puck->trans.z;
            if (HuSqrtf(dx * dx + dz * dz) < plusDist) {
                dx = sindf(angle + 10.0f) * dist;
                dz = cosdf(angle + 10.0f) * dist;
            } else {
                dx = sindf(angle - 10.0f) * dist;
                dz = cosdf(angle - 10.0f) * dist;
            }
            dir.x = dx - object->trans.x;
            dir.y = 0.0f;
            dir.z = dz - object->trans.z;
            func_800202FC_main(&dir);
            D_800CBB6E_main[pad] = dir.x * 60.0f * D_80108664_ice_rink_risk[difficulty];
            D_800D20A1_main[pad] = dir.z * -60.0f * D_80108664_ice_rink_risk[difficulty];
        } else {
            dx = object->trans.x;
            dz = object->trans.z;
            if (HuSqrtf(dx * dx + dz * dz) > 350.0f) {
                dir.x = -object->trans.x;
                dir.y = 0.0f;
                dir.z = -object->trans.z;
                func_800202FC_main(&dir);
                D_800CBB6E_main[pad] = dir.x * 60.0f * D_80108664_ice_rink_risk[difficulty];
                D_800D20A1_main[pad] = dir.z * -60.0f * D_80108664_ice_rink_risk[difficulty];
            }
        }
    }
    D_8010865C_ice_rink_risk[player][0] = D_800CBB6E_main[pad];
    D_8010865C_ice_rink_risk[player][1] = D_800D20A1_main[pad];
    return 1;
}

void func_80107590_ice_rink_risk(omObjData *object) {
    func_80106710_ice_rink_risk(object, D_800A178C_main[GwPlayer[0].chr][0], D_800A178C_main[GwPlayer[0].chr][2], 0);
    object->trans.x = D_80108550_ice_rink_risk.x;
    object->trans.y = D_80108550_ice_rink_risk.y;
    object->trans.z = D_80108550_ice_rink_risk.z;
}

void func_80107604_ice_rink_risk(omObjData *object) {
    func_80106710_ice_rink_risk(object, D_800A178C_main[GwPlayer[1].chr][0], D_800A178C_main[GwPlayer[1].chr][2], 1);
    object->trans.x = D_8010855C_ice_rink_risk.x;
    object->trans.y = D_8010855C_ice_rink_risk.y;
    object->trans.z = D_8010855C_ice_rink_risk.z;
}

void func_80107678_ice_rink_risk(omObjData *object) {
    func_80106710_ice_rink_risk(object, D_800A178C_main[GwPlayer[2].chr][0], D_800A178C_main[GwPlayer[2].chr][2], 2);
    object->trans.x = D_80108568_ice_rink_risk.x;
    object->trans.y = D_80108568_ice_rink_risk.y;
    object->trans.z = D_80108568_ice_rink_risk.z;
}

void func_801076EC_ice_rink_risk(omObjData *object) {
    func_80106710_ice_rink_risk(object, D_800A178C_main[GwPlayer[3].chr][0], D_800A178C_main[GwPlayer[3].chr][2], 3);
    object->trans.x = D_80108574_ice_rink_risk.x;
    object->trans.y = D_80108574_ice_rink_risk.y;
    object->trans.z = D_80108574_ice_rink_risk.z;
}

void func_80107760_ice_rink_risk(omObjData *object) {
    IceRinkRiskPuckWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(IceRinkRiskPuckWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(IceRinkRiskPuckWork));
    work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    object->model[0] = func_8000B0A0_main(0x3A0000, 0x899);
    object->model[1] = func_8000B0D4_main(9, 0xADD);
    object->model[2] = func_8000B108_main(0x3A0002, 0xADD);
    func_800E3584_minigame(object->model[1]);
    object->func = func_8010796C_ice_rink_risk;
    work->unk44 = 0.3f;
    work->unk48 = 60.0f;
    work->unk34 = 50.0f;
    work->unk3C = rand8() * (360.0f / 255.0f);
    work->unk78 = 0;
    work->unk52 = 7;
    work->unk7C = 0;
    work->unk50 = 0;
    work->unk40 = 11.0f;
    work->unk74 = 0.5f;
    work->unk56 = D_80108684_ice_rink_risk;
    work->unk54 = 1;
    for (i = 0; i < 9; i++) {
        work->unk84[i] = 0;
    }
    func_800E149C_minigame(object, 0, 2);
    object->trans.x = rand8() / 4;
    object->trans.y = D_80108584_ice_rink_risk[D_80108684_ice_rink_risk][0];
    object->trans.z = rand8() / 4;
    object->scale.x = object->scale.y = object->scale.z = 1.2f;
    D_80108684_ice_rink_risk++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_8010796C_ice_rink_risk);

f32 func_80107CB4_ice_rink_risk(omObjData *object, f32 x, f32 y, f32 z) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Hu3DSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = work->unk48;
    func_80107F58_ice_rink_risk(object, x, y, z);
    func_80108134_ice_rink_risk(object, &sphere);
    return func_80107D14_ice_rink_risk(object, &sphere);
}

f32 func_80107D14_ice_rink_risk(omObjData *object, Hu3DSphere *sphere) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Vec normal;
    f32 y = sphere->pos.y;
    f32 floorY = func_80107F24_ice_rink_risk(object, sphere, &normal);
    f32 resultY = floorY;

    if (floorY < y - work->unk34 || y + work->unk34 <= floorY) {
        if (work->unk38 == 1000.0f) {
            work->unk38 = 0.0f;
        }
        resultY = y;
    }
    func_80107DEC_ice_rink_risk(object, sphere->pos.x, resultY, sphere->pos.z, floorY, &normal);
    return resultY;
}

void func_80107DEC_ice_rink_risk(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    f32 scale = 1.0f;
    f32 height;

    if (object->model[1] != 0) {
        height = y - floorY;
        if (height != 0.0f) {
            if (height > 900.0f) {
                scale = 0.1f;
            } else {
                scale = 1.0f - fabsf(height) / 1000.0f;
            }
            work->unk53 = -1;
        }
        Hu3DModelPosSet(object->model[1], x, floorY + 5.0f, z);
        Hu3DModelScaleSet(object->model[1], scale, 1.0f, scale);
        func_800E3628_minigame(object->model[1], normal);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

f32 func_80107F24_ice_rink_risk(omObjData *object, Hu3DSphere *sphere, Vec *normal) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    f32 floorY;

    work->unk53 = 0;
    floorY = OM_GET_DATA_PTR(D_800EC1C0_minigame[0], D_800EC1C0_minigame_ObjData)->unk14;
    normal->x = 0.0f;
    normal->y = 1.0f;
    normal->z = 0.0f;
    return floorY;
}

#ifdef NON_MATCHING
void func_80107F58_ice_rink_risk(omObjData *object, f32 x, f32 y, f32 z) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    IceRinkRiskPuckWork *otherWork;
    omObjData *other;
    f32 dx, dy, dz;
    f32 dist;
    s32 i;

    for (i = 0; i < D_801085F8_ice_rink_risk; i++) {
        if (i == work->unk56) {
            continue;
        }
        other = D_800EBE70_minigame[i];
        otherWork = other->data;
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dy = other->trans.y - y;
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (work->unk48 + work->unk48);
        if (dist < 0.0f) {
            if (work->unk38 == 1000.0f) {
                func_800DFCDC_minigame(dx, dz, dist);
            }
            func_80108384_ice_rink_risk(object, dx, dz);
            if (D_801085B0_ice_rink_risk[work->unk56].unk04 >= 16) {
                D_801085B0_ice_rink_risk[work->unk56].unk00 = otherWork->unk56;
                D_801085B0_ice_rink_risk[work->unk56].unk04 = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107F58_ice_rink_risk);
#endif

void func_80108134_ice_rink_risk(omObjData *object, Hu3DSphere *arg1) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Hu3DSphere sphere;
    func_800DBCF4_minigame_Arg local;
    omObjData *obj;

    sphere.pos.x = arg1->pos.x;
    sphere.pos.y = work->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z;
    sphere.radius = arg1->radius;
    D_800EB736_minigame = 0;
    obj = D_800EC1C0_minigame[0];
    local.pos.x = local.prev.x = arg1->pos.x;
    local.pos.y = local.prev.y = work->unk34 / 2 + arg1->pos.y;
    local.pos.z = local.prev.z = arg1->pos.z;
    local.radius = sphere.radius = arg1->radius;
    func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &local.pos, obj);
    local.pos.x += D_800EBE2C_minigame;
    local.pos.y += D_800EC5D8_minigame;
    func_800DC7D8_minigame(obj, (Hu3DSphere *)&local);
    if (D_800EB736_minigame != 0) {
        func_800E2B58_minigame(D_800EC240_minigame, D_800EC298_minigame);
    }
    func_8010826C_ice_rink_risk(object);
}

void func_8010826C_ice_rink_risk(omObjData *object) {
    IceRinkRiskPuckWork *work;
    Vec normal;
    Vec dir;
    Vec reflect;
    f32 dot;

    if (D_800EB736_minigame != 0) {
        work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
        HuAudFXPlay(0x3D2);
        normal.x = D_800EC298_minigame[0].x;
        normal.y = dir.y = 0.0f;
        normal.z = D_800EC298_minigame[0].z;
        dir.x = sindf(work->unk3C + 180.0f);
        dir.z = cosdf(work->unk3C + 180.0f);
        dot = HuVecDot3F(&normal, &dir);
        normal.x = dot * normal.x;
        normal.z = dot * normal.z;
        HuVecSubtract(&reflect, &normal, &dir);
        HuVecAdd(&reflect, &normal, &reflect);
        work->unk3C = atan2df(reflect.x, reflect.z);
        work->unk40 += 1.0f;
    }
}

void func_80108384_ice_rink_risk(omObjData *object, f32 dx, f32 dz) {
    IceRinkRiskPuckWork *work = OM_GET_DATA_PTR(object, IceRinkRiskPuckWork);
    Vec normal;
    Vec dir;
    Vec reflect;
    f32 dot;
    f32 angle;

    HuAudFXPlay(0x3D2);
    normal.x = dx;
    normal.y = dir.y = 0.0f;
    normal.z = dz;
    func_800202FC_main(&normal);
    dir.x = sindf(work->unk3C + 180.0f);
    dir.z = cosdf(work->unk3C + 180.0f);
    dot = HuVecDot3F(&normal, &dir);
    normal.x = dot * normal.x;
    normal.z = dot * normal.z;
    HuVecSubtract(&reflect, &normal, &dir);
    HuVecAdd(&reflect, &normal, &reflect);
    angle = atan2df(reflect.x, reflect.z);
    work->unk3C = angle + (rand8() - 128.0f) / 64.0f;
    work->unk40 += 1.0f;
    D_801085B0_ice_rink_risk[work->unk56].pos.x = dx + object->trans.x;
    D_801085B0_ice_rink_risk[work->unk56].pos.y = object->trans.y;
    D_801085B0_ice_rink_risk[work->unk56].pos.z = dz + object->trans.z;
}
