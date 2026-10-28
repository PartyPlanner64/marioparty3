#include "common.h"
#include "math.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} SpotlightSwimData; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s8 unk04;
} SpotlightSwimUnk8; // sizeof 0x8

extern s16 D_8010CCF4_spotlight_swim[4];
extern s32 D_8010D2F0_spotlight_swim;
extern u8 D_8010CDC8_spotlight_swim[32][32];
extern u32 *D_8010D2F8_spotlight_swim[3];
extern u8 D_8010D329_spotlight_swim[];
extern s8 D_8010D343_spotlight_swim;
extern omObjData *D_8010D348_spotlight_swim;
extern u8 D_8010D3CD_spotlight_swim;
extern s16 D_8010D3B0_spotlight_swim[8];
extern u32 D_8010D448_spotlight_swim;
extern u8 D_8010D44C_spotlight_swim;
extern u32 D_8010D47C_spotlight_swim;

extern SpotlightSwimData D_8010D480_spotlight_swim[50];
extern s8 D_8010EE48_spotlight_swim;
extern SpotlightSwimUnk8 D_8010EE50_spotlight_swim[];

void func_80106150_spotlight_swim(omObjData *);
void func_801061DC_spotlight_swim(omObjData *);
void func_80106350_spotlight_swim(omObjData *);
void func_801065C4_spotlight_swim(omObjData *);
void func_80108AD8_spotlight_swim(omObjData *);
void func_8010AAB8_spotlight_swim(omObjData *);
void func_8010B828_spotlight_swim(omObjData *);
void func_8010C25C_spotlight_swim(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801059A0_spotlight_swim);

f32 func_801059BC_spotlight_swim(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_spotlight_swim(void) {
    SpotlightSwimData *data;
    u32 i;

    for (i = 0, data = D_8010D480_spotlight_swim; i < 50; i++, data++) {
        data->obj = NULL;
        data->unk04 = 0;
        data->unk06 = 0;
        data->unk08 = 0;
        data->unk0A = 0;
        data->unk0C = 0;
        data->unk0E = 0;
        data->unk10 = 0;
        data->unk12 = 0;
        data->unk14 = 0;
        data->unk16 = 0;
        data->unk18 = 0.0f;
        data->unk1C = 0.0f;
        data->unk20 = 0.0f;
        data->unk24 = 0.0f;
        data->unk28 = 0.0f;
        data->unk2C = 0.0f;
        data->unk30 = 0.0f;
        data->unk34 = 0.0f;
        data->unk38 = 0.0f;
        data->unk3C = 0.0f;
        data->unk40 = -1;
        data->unk42 = -1;
        data->unk44.x = data->unk44.y = data->unk44.z = 0.0f;
        data->unk50.x = data->unk50.y = data->unk50.z = 0.0f;
        data->unk5C.x = data->unk5C.y = data->unk5C.z = 0.0f;
        data->unk68 = 0.0f;
        data->unk6C = 0.0f;
        data->unk70 = 0.0f;
        data->unk74 = 0.0f;
        data->unk78.x = data->unk78.y = data->unk78.z = 0.0f;
    }
}

void func_80105B04_spotlight_swim(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_spotlight_swim(s16 arg0, s16 arg1) {
    s16 stopSeNo = D_8010D3B0_spotlight_swim[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    D_8010D3B0_spotlight_swim[arg1] = func_8004AC98_main(D_8010CCF4_spotlight_swim[arg0], arg1);
}

void func_80105C04_spotlight_swim(s16 arg0, s16 arg1) {
    s16 stopSeNo = D_8010D3B0_spotlight_swim[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    D_8010D3B0_spotlight_swim[arg1] = func_8004ACE0_main(D_8010CCF4_spotlight_swim[arg0], arg1);
}

s32 func_80105C8C_spotlight_swim(s32 arg0) {
    return rand8() % arg0;
}

void func_80105CE0_spotlight_swim(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_80105D4C_spotlight_swim(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
    }
}

s8 func_80105DC8_spotlight_swim(omObjData *obj) {
    if (obj->rot.y != 0.0f) {
        if (obj->rot.y < 180.0f) {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, -7.0f);
            if (obj->rot.y > 350.0f) {
                obj->rot.y = 0.0f;
            }
        } else {
            obj->rot.y = func_801059BC_spotlight_swim(obj->rot.y, 7.0f);
            if (obj->rot.y < 10.0f) {
                obj->rot.y = 0.0f;
            }
        }
        return 1;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80105E9C_spotlight_swim);

void func_80106148_spotlight_swim(omObjData *object) {
}

void func_80106150_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240000, 0x299);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_80106148_spotlight_swim;
}

void func_801061A0_spotlight_swim(void) {
    D_8010D480_spotlight_swim[0].obj = omAddObj(0x1F4, 1, 0, -1, func_80106150_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801061DC_spotlight_swim);

void func_80106350_spotlight_swim(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x240001, 0xA9);
    obj->trans.x = 250.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -50.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C8A8_main(obj->model[0], 1);
    obj->func = func_801061DC_spotlight_swim;
}

void func_801063E4_spotlight_swim(void) {
    D_8010D480_spotlight_swim[1].obj = omAddObj(0x258, 1, 0, -1, func_80106350_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106420_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801065C4_spotlight_swim);

void func_80106754_spotlight_swim(void) {
    D_8010D480_spotlight_swim[16].obj = omAddObj(0x4B0, 5, 3, -1, func_801065C4_spotlight_swim);
}

void func_80106790_spotlight_swim(omObjData *obj) {
    if (obj->work[2] == 0 && D_8010D343_spotlight_swim == 1) {
        func_80105C04_spotlight_swim(3, obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 10;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106808_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801069BC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106BC8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106EB0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801072C4_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010755C_spotlight_swim);

s32 func_80107674_spotlight_swim(omObjData *obj) {
    if ((D_800CBB6E_main[obj->work[3]] < 3 && obj->trans.x <= -450.0f) ||
        (D_800CBB6E_main[obj->work[3]] >= 4 && obj->trans.x >= 450.0f)) {
        D_8010D329_spotlight_swim[0] |= 1;
        return 0;
    }
    return 1;
}

s32 func_80107710_spotlight_swim(omObjData *obj) {
    if ((D_800D20A1_main[obj->work[3]] >= 4 && obj->trans.z <= -450.0f) ||
        (D_800D20A1_main[obj->work[3]] < 3 && obj->trans.z >= 260.0f)) {
        D_8010D329_spotlight_swim[0] |= 2;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801077AC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801079FC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80107C10_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010846C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010881C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80108AD8_spotlight_swim);

void func_80109088_spotlight_swim(void) {
    u16 playerIndex;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }

    switch (i) {
        case 0:
            playerIndex = 0;
            break;
        case 1:
            playerIndex = 1;
            break;
        case 2:
            playerIndex = 2;
            break;
        case 3:
            playerIndex = 3;
            break;
        default:
            playerIndex = 0;
            break;
    }

    D_8010D348_spotlight_swim = omAddObj(0x2BC, 9, 10, -1, func_80108AD8_spotlight_swim);
    D_8010D348_spotlight_swim->work[0] = playerIndex;
    D_8010D480_spotlight_swim[2].obj = D_8010D348_spotlight_swim;
    D_8010D3CD_spotlight_swim = D_8010D348_spotlight_swim->work[0];
    D_8010D44C_spotlight_swim = GwPlayer[D_8010D348_spotlight_swim->work[0]].chr;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109194_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010932C_spotlight_swim);

void func_80109468_spotlight_swim(omObjData *obj, f32 targetX, f32 targetY) {
    if (targetX + 3.0f < obj->trans.x) {
        D_800CBB6E_main[obj->work[3]] = -10;
    }
    if (obj->trans.x < targetX - 3.0f) {
        D_800CBB6E_main[obj->work[3]] = 10;
    }
    if (targetY + 3.0f < obj->trans.y) {
        D_800D20A1_main[obj->work[3]] = 10;
    }
    if (obj->trans.y < targetY - 3.0f) {
        D_800D20A1_main[obj->work[3]] = -10;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109558_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109690_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801098A8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109A94_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109C1C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109E08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109F60_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A328_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A670_spotlight_swim);

void func_8010A7AC_spotlight_swim(omObjData *obj) {
    s8 idx = obj->work[0];
    SpotlightSwimData *data = &D_8010D480_spotlight_swim[obj->work[0] + 9];
    SpotlightSwimData *data3 = &D_8010D480_spotlight_swim[obj->work[0] + 3];
    omObjData *obj3 = data3->obj;
    SpotlightSwimData *data6 = &D_8010D480_spotlight_swim[obj->work[0] + 6];
    omObjData *obj6 = data6->obj;
    s16 dx, dz, dist;
    s8 motion;

    if (D_8010EE48_spotlight_swim < 3) {
        dx = data->unk44.x - obj3->trans.x;
        dz = 200.0f - obj3->trans.y;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 100) {
            motion = 0;
        } else if (dist < 150) {
            motion = 1;
        } else {
            motion = 2;
        }

        obj->rot.y = func_801059BC_spotlight_swim(
            atan2df(data3->obj->trans.x - data->unk44.x, data3->obj->trans.y - 200.0f), 0.0f);
        obj6->rot.y = obj->rot.y;
        data->unk50.x = func_801059BC_spotlight_swim(atan2df(dist, 60.0f), 0.0f);
        data->unk50.x = func_801059BC_spotlight_swim(80.0f, -data->unk50.x);

        if (D_8010EE50_spotlight_swim[idx].unk04 != motion) {
            D_8010EE50_spotlight_swim[idx].unk04 = motion;
            func_80105D4C_spotlight_swim(obj6, motion, 0, 5, 2);
            func_8001C92C_main(obj6->model[0], 0.5f);
        }

        if (D_8010EE50_spotlight_swim[idx].unk00 != obj->rot.y) {
            D_8010EE50_spotlight_swim[idx].unk00 = obj->rot.y;
            func_8001C92C_main(obj6->model[0], 0.5f);
        } else {
            func_8001C92C_main(obj6->model[0], 0.0f);
            func_80105D4C_spotlight_swim(obj6, D_8010EE50_spotlight_swim[idx].unk04, 0, 10, 2);
        }

        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        Hu3DModelRotSet(obj->model[1], data->unk50.x, obj->rot.y, obj->rot.z);
        Hu3DModelRotSet(obj6->model[0], obj6->rot.x, obj6->rot.y, obj6->rot.z);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AAB8_spotlight_swim);

void func_8010ADF8_spotlight_swim(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        SpotlightSwimData *data = &D_8010D480_spotlight_swim[9 + i];

        data->obj = omAddObj(0x3E8, 5, 5, -1, func_8010AAB8_spotlight_swim);
        data->obj->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010AE9C_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010B828_spotlight_swim);

void func_8010BA30_spotlight_swim(void) {
    D_8010D480_spotlight_swim[13].obj = omAddObj(0x514, 5, 5, -1, func_8010B828_spotlight_swim);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BA6C_spotlight_swim);

void func_8010BD10_spotlight_swim(void) {
    u32 i;
    u32 *ptr = D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim];

    for (i = 0; i < 0x35C0; i++) {
        *ptr = D_8010D47C_spotlight_swim | D_8010D448_spotlight_swim;
        ptr++;
    }
}

s32 func_8010BD5C_spotlight_swim(void) {
    u32 i;
    u32 *ptr = D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim];

    for (i = 0; i < 0x4B00; i++) {
        *ptr = D_8010D47C_spotlight_swim | D_8010D448_spotlight_swim;
        ptr++;
    }

    if (D_8010D47C_spotlight_swim >= 8) {
        D_8010D47C_spotlight_swim -= 8;
        return 0;
    }

    D_8010D47C_spotlight_swim = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010BDE0_spotlight_swim);

void func_8010BFD0_spotlight_swim(u32 *buf, s32 x, s32 y) {
    s32 col;
    s32 row;
    s32 i;
    s32 j;
    s32 offset;
    u32 value;

    x /= 2;
    y /= 2;
    for (row = y, i = 0; row < y + 32; row++, i++) {
        offset = row * 160;
        for (col = x, j = 0; col < x + 32; col++, j++) {
            value = D_8010CDC8_spotlight_swim[i][j] << 4;
            if (value > D_8010D47C_spotlight_swim) {
                value = D_8010D47C_spotlight_swim;
            }
            *(buf + col + offset) = value + D_8010D448_spotlight_swim;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C094_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C25C_spotlight_swim);

void func_8010C444_spotlight_swim(void) {
    omObjData *obj = omAddObj(0x44C, 1, 0, -1, func_8010C25C_spotlight_swim);
    obj->work[0] = 0;
    D_8010D480_spotlight_swim[12].obj = obj;
}

void func_8010C484_spotlight_swim(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 2241.8f;
        CRotM[i].x = 314.3f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -195.0f;
        CenterM[i].z = 40.0f;
    }
}

void func_8010C52C_spotlight_swim(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C550_spotlight_swim(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C52C_spotlight_swim;
    }
}

void func_8010C588_spotlight_swim(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C550_spotlight_swim;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C5E0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010C900_spotlight_swim);

void func_8010CA00_spotlight_swim(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010CA08_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010CB78_spotlight_swim);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", D_8010D2E0_spotlight_swim);
