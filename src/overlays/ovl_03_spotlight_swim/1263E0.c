#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"
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

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
} SpotlightSwimUnk308; // sizeof 0x8

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} SpotlightSwimCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ u32 r;
    /* 0x0C */ u32 g;
    /* 0x10 */ u32 b;
} SpotlightSwimLight; // sizeof 0x14

extern s8 D_8010CCC0_spotlight_swim[][3];
extern s16 D_8010CCF4_spotlight_swim[4];
extern u8 D_8010CDA8_spotlight_swim[];
extern u8 D_8010CDAC_spotlight_swim[4][2];
extern s8 D_8010CDB4_spotlight_swim;
extern s8 D_8010CD50_spotlight_swim[][9];
extern SpotlightSwimCamera D_8010D1D4_spotlight_swim[1];
extern const s16 D_8010D2E0_spotlight_swim[];
extern s32 D_8010D1C8_spotlight_swim[3];
extern u32 D_8010D2F0_spotlight_swim;
extern u8 D_8010CDC8_spotlight_swim[32][32];
extern s8 D_8010D2F4_spotlight_swim;
extern u32 *D_8010D2F8_spotlight_swim[3];
extern SpotlightSwimUnk308 D_8010D308_spotlight_swim[];
extern u8 D_8010D320_spotlight_swim[3];
extern u8 D_8010D329_spotlight_swim[];
extern s8 D_8010D32C_spotlight_swim;
extern u8 D_8010D340_spotlight_swim[3];
extern f32 D_8010D338_spotlight_swim[2];
extern s8 D_8010D343_spotlight_swim;
extern s16 D_8010D364_spotlight_swim;
extern s8 D_8010D366_spotlight_swim;
extern omObjData *D_8010D348_spotlight_swim;
extern s16 D_8010D368_spotlight_swim[4];
extern f32 D_8010D370_spotlight_swim[2];
extern f32 D_8010D380_spotlight_swim[3];
extern f32 D_8010D38C_spotlight_swim[3];
extern s8 D_8010D398_spotlight_swim[3];
extern s8 D_8010D39B_spotlight_swim[3];
extern u8 D_8010D3CD_spotlight_swim;
extern s8 D_8010D3AC_spotlight_swim;
extern f32 D_8010D3C0_spotlight_swim[3];
extern s16 D_8010D3B0_spotlight_swim[8];
extern SpotlightSwimLight D_8010D3D0_spotlight_swim[6];
extern u32 D_8010D448_spotlight_swim;
extern u8 D_8010D44C_spotlight_swim;
extern u32 D_8010D47C_spotlight_swim;

extern SpotlightSwimData D_8010D480_spotlight_swim[50];
extern s8 D_8010EE48_spotlight_swim;
extern SpotlightSwimUnk8 D_8010EE50_spotlight_swim[];

void func_80106150_spotlight_swim(omObjData *);
void func_801061DC_spotlight_swim(omObjData *);
void func_80106350_spotlight_swim(omObjData *);
void func_80106420_spotlight_swim(omObjData *);
void func_801065C4_spotlight_swim(omObjData *);
void func_80108AD8_spotlight_swim(omObjData *);
void func_8010AAB8_spotlight_swim(omObjData *);
void func_8010B828_spotlight_swim(omObjData *);
void func_8010A328_spotlight_swim(omObjData *);
void func_8010BA6C_spotlight_swim(Gfx **, s32, s32);
void func_8010C25C_spotlight_swim(omObjData *);
void func_80109C1C_spotlight_swim(omObjData *);
void func_80109A94_spotlight_swim(omObjData *);
void func_80109690_spotlight_swim(omObjData *);
void func_80109E08_spotlight_swim(void);
void func_8010A670_spotlight_swim(void);
void func_8010C5E0_spotlight_swim(omObjData *);
void func_8000B710_main(s32);
void func_8010CB78_spotlight_swim(void);

void func_801059A0_spotlight_swim(void) {
    func_8010CB78_spotlight_swim();
}

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

void func_801061DC_spotlight_swim(omObjData *obj) {
    SpotlightSwimData *data = &D_8010D480_spotlight_swim[1];

    if (++data->unk06 >= 30) {
        data->unk04++;
        data->unk06 = 0;
    }

    switch (data->unk04 & 1) {
        case 0:
            obj->trans.y += 0.5f;
            obj->trans.z -= 0.5f;
            if (D_8010D343_spotlight_swim != 7) {
                D_8010D338_spotlight_swim[0] += 0.5f;
                D_8010D348_spotlight_swim->trans.z -= 0.5f;
            }
            break;
        case 1:
            obj->trans.y -= 0.5f;
            obj->trans.z += 0.5f;
            if (D_8010D343_spotlight_swim != 7) {
                D_8010D338_spotlight_swim[0] -= 0.5f;
                D_8010D348_spotlight_swim->trans.z += 0.5f;
            }
            break;
    }

    obj->trans.x -= 4.0f;
    if (obj->trans.x == -254.0f) {
        obj->trans.x = 250.0f;
    }
}

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

void func_80106420_spotlight_swim(omObjData *obj) {
    s8 i;
    f32 *zs;

    for (i = 0; i < 3; i++) {
        switch (D_8010D39B_spotlight_swim[i]) {
            case 0:
                break;
            case 1:
                D_8010D398_spotlight_swim[i]++;
                if (D_8010D398_spotlight_swim[i] >= i * 7) {
                    D_8010D39B_spotlight_swim[i] = 2;
                    D_8010D398_spotlight_swim[i] = 0;
                }
                break;
            case 2:
                D_8010D398_spotlight_swim[i]++;
                if (D_8010D398_spotlight_swim[i] >= 10) {
                    D_8010D398_spotlight_swim[i] = 0;
                    D_8010D39B_spotlight_swim[i] = 0;
                    D_8010D380_spotlight_swim[i] = 1000.0f;
                }
                zs = D_8010D38C_spotlight_swim;
                Hu3DModelPosSet(obj->model[i + 1], D_8010D380_spotlight_swim[i], -200.0f, zs[i]);
                break;
        }
    }
}

void func_801065C4_spotlight_swim(omObjData *obj) {
    void *data;
    s8 i;
    f32 *xs;
    f32 *zs;

    data = DataRead(0x24000F);
    for (i = 0, xs = D_8010D380_spotlight_swim, zs = D_8010D38C_spotlight_swim; i < 3; i++) {
        obj->model[i + 1] = func_8000B108_main(0x24000E, 0x289);
        HmfAnimCreate(HmfModelData[obj->model[i + 1]].hmf, data, 0, "s203_004_DEF");
        func_8001C448_main(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_8001C8A8_main(obj->model[i + 1], 1);
        xs[i] = 1000.0f;
        zs[i] = 0.0f;
        Hu3DModelPosSet(obj->model[i + 1], xs[i], -200.0f, zs[i]);
        D_8010D398_spotlight_swim[i] = 0;
        D_8010D39B_spotlight_swim[i] = 0;
    }
    DataClose(data);
    obj->func = func_80106420_spotlight_swim;
}

void func_80106754_spotlight_swim(void) {
    D_8010D480_spotlight_swim[16].obj = omAddObj(0x4B0, 5, 3, -1, func_801065C4_spotlight_swim);
}

void func_80106790_spotlight_swim(omObjData *obj) {
    if (obj->work[2] == 0 && D_8010D343_spotlight_swim == 1) {
        func_80105C04_spotlight_swim(3, obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 10;
}

void func_80106808_spotlight_swim(omObjData *obj) {
    SpotlightSwimData *data;
    f32 angle;

    data = &D_8010D480_spotlight_swim[2];
    func_8001C6A8_main(obj->model[5], 0.0f);
    if (obj->work[1] != 5) {
        data->unk44.x = obj->trans.x;
        data->unk44.z = obj->trans.z + 35.0f;
    } else {
        angle = func_801059BC_spotlight_swim(obj->rot.y, -90.0f);
        data->unk44.x = obj->trans.x - cosdf(angle) * 50.0f;
        data->unk44.z = sindf(angle) * 50.0f + obj->trans.z + 60.0f;
    }
    data->unk44.y = obj->trans.y - D_8010CD50_spotlight_swim[obj->work[1]][D_8010D343_spotlight_swim] - 25.0f;
    if (D_8010D32C_spotlight_swim == 2 || D_8010EE48_spotlight_swim == 5) {
        Hu3DModelScaleSet(obj->model[5], 0.6f, 0.5f, 1.0f);
    } else {
        Hu3DModelScaleSet(obj->model[5], 0.8f, 0.6f, 1.0f);
    }
    Hu3DModelPosSet(obj->model[5], data->unk44.x, -200.0f, data->unk44.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801069BC_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106BC8_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80106EB0_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_801072C4_spotlight_swim);

void func_8010755C_spotlight_swim(omObjData *obj) {
    f32 x;
    f32 z;
    s8 i;

    for (i = 0; i < 3; i++) {
        x = func_80105C8C_spotlight_swim(30) + 15;
        if (func_80105C8C_spotlight_swim(2) != 0) {
            x = 0.0f - x;
        }
        z = func_80105C8C_spotlight_swim(30) + 15;
        if (func_80105C8C_spotlight_swim(2) != 0) {
            z = 0.0f - z;
        }
        D_8010D380_spotlight_swim[i] = x + obj->trans.x;
        D_8010D38C_spotlight_swim[i] = z + obj->trans.z;
        D_8010D39B_spotlight_swim[i] = 1;
    }
}

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

u8 func_80109194_spotlight_swim(omObjData *obj) {
    u8 flags = 0;

    if (D_800CBB6E_main[obj->work[3]] < -5 && obj->trans.x < 65.0f) {
        D_800CBB6E_main[obj->work[3]] = 0;
    } else if (D_800CBB6E_main[obj->work[3]] < -4) {
        flags |= 4;
    }

    if (D_800CBB6E_main[obj->work[3]] >= 6 && obj->trans.x > 255.0f) {
        D_800CBB6E_main[obj->work[3]] = 0;
    } else if (D_800CBB6E_main[obj->work[3]] >= 5) {
        flags |= 8;
    }

    if (D_800D20A1_main[obj->work[3]] >= 6 && obj->trans.y < 60.0f) {
        D_800D20A1_main[obj->work[3]] = 0;
    } else if (D_800D20A1_main[obj->work[3]] >= 5) {
        flags |= 1;
    }

    if (D_800D20A1_main[obj->work[3]] < -5 && obj->trans.y > 140.0f) {
        D_800D20A1_main[obj->work[3]] = 0;
    } else if (D_800D20A1_main[obj->work[3]] < -4) {
        flags |= 2;
    }

    return flags;
}

void func_8010932C_spotlight_swim(omObjData *obj) {
    SpotlightSwimUnk308 *data = &D_8010D308_spotlight_swim[obj->work[1]];

    if (++data->unk02 >= data->unk03) {
        data->unk02 = 0;
        data->unk03 = func_80105C8C_spotlight_swim(20) + 20;
        data->unk04 = func_80105C8C_spotlight_swim(2) == 0 ? -10 : 10;
        data->unk04 = func_80105C8C_spotlight_swim(data->unk00 + 4) != 0 ? data->unk04 : 0;
    }

    if (++data->unk05 >= data->unk06) {
        data->unk05 = 0;
        data->unk06 = func_80105C8C_spotlight_swim(20) + 20;
        data->unk07 = func_80105C8C_spotlight_swim(2) == 0 ? -10 : 10;
        data->unk07 = func_80105C8C_spotlight_swim(data->unk00 + 4) != 0 ? data->unk07 : 0;
    }

    D_800CBB6E_main[obj->work[3]] = data->unk04;
    D_800D20A1_main[obj->work[3]] = data->unk07;
}

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

void func_80109558_spotlight_swim(omObjData *obj, f32 targetX, f32 targetY) {
    if (abs(targetX - obj->trans.x) > abs(targetY - obj->trans.y)) {
        if (targetX + 3.0f < obj->trans.x) {
            D_800CBB6E_main[obj->work[3]] = -10;
        }
        if (obj->trans.x < targetX - 3.0f) {
            D_800CBB6E_main[obj->work[3]] = 10;
        }
    } else {
        if (targetY + 3.0f < obj->trans.y) {
            D_800D20A1_main[obj->work[3]] = 10;
        }
        if (obj->trans.y < targetY - 3.0f) {
            D_800D20A1_main[obj->work[3]] = -10;
        }
    }
}

// Remaining diffs: the "unk00 != 3" path is missing a `bnel` that re-sets `row`
// to 1, and the second flag bit test needs `1 << index` computed before the
// reload of D_8010D2F4_spotlight_swim (register allocation differs).
#ifdef NON_MATCHING
void func_80109690_spotlight_swim(omObjData *obj) {
    u32 index = obj->work[1];
    SpotlightSwimData *data = &D_8010D480_spotlight_swim[index + 3];
    SpotlightSwimUnk308 *unk;
    u16 row;
    s8 flags;
    s32 mask;

    if (data->unk16 == 0) {
        return;
    }

    unk = &D_8010D308_spotlight_swim[index];
    row = 1;

    if (D_8010D366_spotlight_swim != 0) {
        flags = D_8010D2F4_spotlight_swim;
        mask = flags | (1 << (D_8010D366_spotlight_swim - 1));
        if (flags == mask && D_8010D32C_spotlight_swim <= 0) {
            goto target;
        }
    } else if (D_8010D2F4_spotlight_swim != 0 && D_8010D32C_spotlight_swim <= 0 && unk->unk00 == 3) {
    target:
        if (obj->work[0] & 1) {
            goto chase;
        }
        goto wander;
    }

    if (D_8010D32C_spotlight_swim == 1) {
        row = 0;
    } else {
        flags = D_8010D2F4_spotlight_swim;
        mask = flags | (1 << index);
        if (flags == mask) {
            goto chase;
        }
    }

    if (D_8010D32C_spotlight_swim == 2) {
        goto chase;
    }

    if (++unk->unk01 >= D_8010CDAC_spotlight_swim[unk->unk00][row]) {
        if (unk->unk01 == D_8010CDAC_spotlight_swim[unk->unk00][row]) {
            data->unk06 = func_80105C8C_spotlight_swim(2);
        }

        if (unk->unk01 >= 60) {
            unk->unk01 = func_80105C8C_spotlight_swim(5);
            return;
        }

        if (data->unk06 != 0) {
            goto chase;
        }
        goto wander;
    } else {
        func_8010932C_spotlight_swim(obj);
        return;
    }

chase:
    func_80109468_spotlight_swim(obj, D_8010D370_spotlight_swim[0], D_8010D370_spotlight_swim[1]);
    return;

wander:
    func_80109558_spotlight_swim(obj, D_8010D370_spotlight_swim[0], D_8010D370_spotlight_swim[1]);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109690_spotlight_swim);
#endif

void func_801098A8_spotlight_swim(omObjData *obj) {
    s8 index = obj->work[1];
    s32 dx = obj->trans.x - D_8010D370_spotlight_swim[0];
    s32 dy = obj->trans.y - D_8010D370_spotlight_swim[1];
    s32 dist = sqrtf(dx * dx + dy * dy);

    D_8010D368_spotlight_swim[index] = dist;
    D_8010D3C0_spotlight_swim[index] = func_801059BC_spotlight_swim(
        atan2df(obj->trans.x - D_8010D370_spotlight_swim[0], obj->trans.y - D_8010D370_spotlight_swim[1]), 0.0f);

    if (D_8010D32C_spotlight_swim == 1) {
        return;
    }

    if (dist < 24) {
        D_8010D2F4_spotlight_swim |= 1 << index;
    } else {
        D_8010D2F4_spotlight_swim &= D_8010CDA8_spotlight_swim[index];
    }

    if (D_8010D2F4_spotlight_swim == 3 || D_8010D2F4_spotlight_swim == 5 || D_8010D2F4_spotlight_swim == 6) {
        if (D_8010CDB4_spotlight_swim == 0) {
            HuAudFXPlay(0x316);
            D_8010CDB4_spotlight_swim = 1;
        }
    } else {
        D_8010CDB4_spotlight_swim = 0;
    }

    if (D_8010D2F4_spotlight_swim == 7) {
        HuAudFXPlay(0x317);
    }
}

void func_80109A94_spotlight_swim(omObjData *obj) {
    SpotlightSwimData *data = &D_8010D480_spotlight_swim[obj->work[1] + 3];

    if (D_8010EE48_spotlight_swim != 2) {
        return;
    }

    func_80109690_spotlight_swim(obj);
    data->unk14 = func_80109194_spotlight_swim(obj);

    switch (data->unk14) {
        case 1:
            obj->trans.y -= 1.0f;
            break;
        case 2:
            obj->trans.y += 1.0f;
            break;
        case 4:
            obj->trans.x -= 1.5f;
            break;
        case 8:
            obj->trans.x += 1.5f;
            break;
        case 5:
            obj->trans.x -= 1.0f;
            obj->trans.y -= 1.0f;
            break;
        case 9:
            obj->trans.x += 1.0f;
            obj->trans.y -= 1.0f;
            break;
        case 6:
            obj->trans.x -= 1.0f;
            obj->trans.y += 1.0f;
            break;
        case 10:
            obj->trans.x += 1.0f;
            obj->trans.y += 1.0f;
            break;
    }

    func_801098A8_spotlight_swim(obj);
}

void func_80109C1C_spotlight_swim(omObjData *obj) {
    SpotlightSwimData *data = &D_8010D480_spotlight_swim[obj->work[1] + 3];
    s8 index = obj->work[1];

    if (GwPlayer[obj->work[0]].stat & 1) {
        data->unk16 = 1;
    } else {
        data->unk16 = 0;
        D_8010D366_spotlight_swim = index + 1;
    }

    switch (D_8010CCC0_spotlight_swim[D_8010D3AC_spotlight_swim][index]) {
        case 0:
            obj->trans.x = 70.0f;
            break;
        case 1:
            obj->trans.x = 160.0f;
            break;
        case 2:
            obj->trans.x = 250.0f;
            break;
    }

    obj->trans.y = 140.0f;
    obj->trans.z = 0.0f;
    D_8010D308_spotlight_swim[index].unk02 = 0;
    D_8010D308_spotlight_swim[index].unk03 = 0;
    D_8010D308_spotlight_swim[index].unk04 = 0;
    D_8010D308_spotlight_swim[index].unk05 = 0;
    D_8010D308_spotlight_swim[index].unk06 = 0;
    D_8010D308_spotlight_swim[index].unk07 = 0;
    D_8010D308_spotlight_swim[index].unk01 = func_80105C8C_spotlight_swim(60);
    D_8010D308_spotlight_swim[index].unk00 = GwPlayer[obj->work[0]].cpu_difficulty;
    obj->work[3] = GwPlayer[obj->work[0]].pad;
    obj->func = func_80109A94_spotlight_swim;
}

void func_80109E08_spotlight_swim(void) {
    u16 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            SpotlightSwimData *data;
            omObjData *obj;

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
            }
            data = &D_8010D480_spotlight_swim[3 + count];
            obj = omAddObj(0x320, 4, 1, -1, func_80109C1C_spotlight_swim);
            obj->work[0] = playerIndex;
            data->obj = obj;
            obj->work[1] = data->unk04 = count;
            D_8010D320_spotlight_swim[count] = obj->work[0];
            D_8010D340_spotlight_swim[count] = GwPlayer[obj->work[0]].chr;
            count++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_80109F60_spotlight_swim);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_03_spotlight_swim/1263E0", func_8010A328_spotlight_swim);

void func_8010A670_spotlight_swim(void) {
    u16 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            SpotlightSwimData *data;
            omObjData *obj;

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
            }
            data = &D_8010D480_spotlight_swim[6 + count];
            obj = omAddObj(0x384, 8, 7, -1, func_8010A328_spotlight_swim);
            obj->work[0] = playerIndex;
            data->obj = obj;
            obj->work[1] = data->unk04 = count;
            count++;
        }
    }
}

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

s8 func_8010BD5C_spotlight_swim(void) {
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

void func_8010BDE0_spotlight_swim(s32 x, s32 y, u32 r, u32 g, u32 b) {
    u32 *buf = D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim];
    s32 col;
    s32 row;
    s32 i;
    s32 j;
    s32 offset;
    u8 value;
    u32 pixel;
    u32 scale;
    u32 red;
    u32 green;
    u32 blue;
    u32 addRed;
    u32 addGreen;
    u32 addBlue;
    u32 alpha;
    s32 xEnd;
    s32 yEnd;

    x /= 2;
    y /= 2;
    xEnd = x + 32;
    yEnd = y + 32;
    for (row = y, i = 0; row < yEnd; row++, i++) {
        offset = row * 160;
        for (col = x, j = 0; col < xEnd; col++, j++) {
            value = D_8010CDC8_spotlight_swim[i][j];
            if (value == 15) {
                continue;
            }
            pixel = *(buf + col + offset);
            red = pixel >> 24;
            green = (pixel >> 16) & 0xFF;
            scale = 256 - (value << 4);
            addRed = (r * scale) >> 8;
            addGreen = (g * scale) >> 8;
            addBlue = (b * scale) >> 8;
            red = (red + addRed) & 0xFF;
            green = (green + addGreen) & 0xFF;
            blue = addBlue & 0xFF;
            if (red + green + blue == 765) {
                *(buf + col + offset) = 0;
                continue;
            }
            alpha = (765 - (red + green + blue)) * D_8010D47C_spotlight_swim / 765;
            *(buf + col + offset) = (red << 24) + (green << 16) + (blue << 8) + alpha;
        }
    }
}

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

void func_8010C094_spotlight_swim(omObjData *obj) {
    SpotlightSwimData *data;
    SpotlightSwimLight *light;
    s32 i;

    D_8010D2F0_spotlight_swim = (D_8010D2F0_spotlight_swim + 1) % 3;
    if (D_8010EE48_spotlight_swim >= 3) {
        if (func_8010BD5C_spotlight_swim() == 0) {
            for (i = 0; i < 3; i++) {
                func_8010BFD0_spotlight_swim(D_8010D2F8_spotlight_swim[D_8010D2F0_spotlight_swim],
                                             D_8010D1C8_spotlight_swim[i], 0xAA);
                light = &D_8010D3D0_spotlight_swim[i];
                func_8010BDE0_spotlight_swim(light->x, light->y, light->r, light->g, light->b);
            }
        }
    } else {
        func_8010BD10_spotlight_swim();
        for (i = 0; i < 3; i++) {
            data = &D_8010D480_spotlight_swim[3 + i];
            light = &D_8010D3D0_spotlight_swim[i];
            light->x = data->obj->trans.x - 32.0f;
            light->y = data->obj->trans.y - 32.0f;
            func_8010BDE0_spotlight_swim(light->x, light->y, light->r, light->g, light->b);
        }
    }
}

void func_8010C25C_spotlight_swim(omObjData *obj) {
    s32 i;
    s32 j;

    D_8010D2F0_spotlight_swim = 0;
    obj->model[0] = func_8001AC8C_main(0, func_8010BA6C_spotlight_swim, 2);
    func_8001C8A8_main(obj->model[0], 1);
    func_8001C258_main(obj->model[0], 4, 0);
    for (i = 0; i < 3; i++) {
        D_8010D2F8_spotlight_swim[i] = HuMemAllocTag(0x12C00, 0x7918);
        for (j = 0; j < 0x4B00; j++) {
            D_8010D2F8_spotlight_swim[i][j] = D_8010D448_spotlight_swim | 0x98;
        }
        for (j = 0; j < 3; j++) {
            func_8010BFD0_spotlight_swim(D_8010D2F8_spotlight_swim[i], D_8010D1C8_spotlight_swim[j], 0xAA);
        }
    }
    for (i = 0; i < 3; i++) {
        D_8010D3D0_spotlight_swim[i].r = 0;
        D_8010D3D0_spotlight_swim[i].g = 0;
        D_8010D3D0_spotlight_swim[i].b = 0;
    }
    for (i = 3; i < 6; i++) {
        D_8010D3D0_spotlight_swim[i].r = 0xFF;
        D_8010D3D0_spotlight_swim[i].g = 0xFF;
        D_8010D3D0_spotlight_swim[i].b = 0xFF;
    }
    D_8010D3D0_spotlight_swim[0].r = 0xFF;
    D_8010D3D0_spotlight_swim[1].g = 0xFF;
    D_8010D3D0_spotlight_swim[2].b = 0xFF;
    obj->func = func_8010C094_spotlight_swim;
}

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

void func_8010C900_spotlight_swim(omObjData *obj) {
    s8 i;

    D_8010EE48_spotlight_swim = 0;
    D_8010D364_spotlight_swim = 0;
    for (i = 0; i < 8; i++) {
        D_8010D3B0_spotlight_swim[i] = -1;
    }
    D_8010D366_spotlight_swim = 0;
    D_8010D3AC_spotlight_swim = func_80105C8C_spotlight_swim(6);
    D_8010D47C_spotlight_swim = 0x98;
    D_8010D448_spotlight_swim = 0x2000;
    func_8010C484_spotlight_swim();
    func_801061A0_spotlight_swim();
    func_801063E4_spotlight_swim();
    func_80109088_spotlight_swim();
    func_80109E08_spotlight_swim();
    func_8010A670_spotlight_swim();
    func_8010ADF8_spotlight_swim();
    func_8010C444_spotlight_swim();
    func_8010BA30_spotlight_swim();
    func_80106754_spotlight_swim();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010C5E0_spotlight_swim;
}

void func_8010CA00_spotlight_swim(void) {
}

void func_8010CA08_spotlight_swim(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010D1D4_spotlight_swim[i].scissorX, D_8010D1D4_spotlight_swim[i].scissorY,
                   D_8010D1D4_spotlight_swim[i].scissorWidth, D_8010D1D4_spotlight_swim[i].scissorHeight);
        ViewportSet(i, D_8010D1D4_spotlight_swim[i].viewportScale.x, D_8010D1D4_spotlight_swim[i].viewportScale.y,
                    D_8010D1D4_spotlight_swim[i].viewportScale.z, D_8010D1D4_spotlight_swim[i].viewportTranslate.x,
                    D_8010D1D4_spotlight_swim[i].viewportTranslate.y, D_8010D1D4_spotlight_swim[i].viewportTranslate.z);
        Hu3DCamSetPerspective(i, D_8010D1D4_spotlight_swim[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010CB78_spotlight_swim(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010CA08_spotlight_swim();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010D2E0_spotlight_swim, 0);
    func_80045010_main(D_8010D2E0_spotlight_swim, 1);
    omAddObj(0x5DC, 0, 0, -1, func_8010C900_spotlight_swim);
    omAddObj(0x5DC, 0, 0, -1, func_8010C588_spotlight_swim);
    func_80105A3C_spotlight_swim();
}

// Keep this table after the functions to preserve the original rodata order.
const s16 D_8010D2E0_spotlight_swim[] = { 0x8260, 0x8261, 0x8262, 0 };
