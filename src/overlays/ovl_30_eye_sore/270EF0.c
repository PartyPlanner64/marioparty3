#include "common.h"
#include "math.h"

// One entry of the 50 entry object table. Layout derived from the table clear
// in func_80105A74_eye_sore, which walks 50 entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04[10];
    /* 0x18 */ f32 unk_18[10];
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} EyeSoreEntry; // sizeof 0x84

typedef struct {
    /* 0x00 */ char unk_00[6];
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ char unk_07[0x11];
} EyeSoreUnkC938; // sizeof 0x18

typedef struct {
    /* 0x00 */ char unk_00[0xD];
    /* 0x0D */ s8 unk_0D;
    /* 0x0E */ s8 unk_0E;
    /* 0x0F */ char unk_0F[0x45];
} EyeSoreUnkCA60; // sizeof 0x54

extern EyeSoreEntry D_8010AF70_eye_sore[50];
extern EyeSoreUnkC938 D_8010C938_eye_sore[];
extern EyeSoreUnkCA60 D_8010CA60_eye_sore[];
// The first entry of D_8010AF70_eye_sore is accessed through these separate
// symbols.
extern s16 D_8010AFB0_eye_sore;
extern s16 D_8010AFB2_eye_sore;
extern f32 D_8010AFB4_eye_sore;
extern f32 D_8010AFB8_eye_sore;
extern s32 D_8010AC10_eye_sore[];
extern s16 D_8010AC30_eye_sore[];
extern const char *D_8010AC78_eye_sore[];
extern s16 D_8010AF22_eye_sore[];
extern void *D_8010CC18_eye_sore[][2];

f32 func_801059BC_eye_sore(f32 arg0, f32 arg1);
void func_80106054_eye_sore(omObjData *obj);
void func_8010605C_eye_sore(omObjData *obj);
void func_80105DA0_eye_sore(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_8010AAF8_eye_sore(void);

void func_801059A0_eye_sore(void) {
    func_8010AAF8_eye_sore();
}

f32 func_801059BC_eye_sore(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_eye_sore(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_eye_sore(void) {
    EyeSoreEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010AF70_eye_sore; i < 50; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04[0] = 0;
        entry->unk_04[1] = 0;
        entry->unk_04[2] = 0;
        entry->unk_04[3] = 0;
        entry->unk_04[4] = 0;
        entry->unk_04[5] = 0;
        entry->unk_04[6] = 0;
        entry->unk_04[7] = 0;
        entry->unk_04[8] = 0;
        entry->unk_04[9] = 0;
        entry->unk_18[0] = 0;
        entry->unk_18[1] = 0;
        entry->unk_18[2] = 0;
        entry->unk_18[3] = 0;
        entry->unk_18[4] = 0;
        entry->unk_18[5] = 0;
        entry->unk_18[6] = 0;
        entry->unk_18[7] = 0;
        entry->unk_18[8] = 0;
        entry->unk_18[9] = 0;
        entry->unk_40[0] = -1;
        entry->unk_40[1] = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68[0] = 0.0f;
        entry->unk_68[1] = 0.0f;
        entry->unk_68[2] = 0.0f;
        entry->unk_68[3] = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105B3C_eye_sore(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105BB4_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = (x0 - x1) * 5.0f;
    f32 dz = (z0 - z1) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = func_801059BC_eye_sore(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 func_80105CE4_eye_sore(s32 arg0) {
    return rand8() % arg0;
}

void func_80105D38_eye_sore(omObjData *obj, u16 motion, s16 shift) {
    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], shift, shift);
}

void func_80105DA0_eye_sore(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

void func_80105E0C_eye_sore(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 *angle, f32 speed) {
    f32 dx = x0 - x1;
    f32 dz = z0 - z1;
    f32 dist = sqrtf(dx * dx + dz * dz);
    f32 steps;

    if (dist == 0.0f) {
        *velX = 0.0f;
        *velZ = 0.0f;
        return;
    }
    if (dist <= speed) {
        *velX = dx;
        *velZ = dz;
    } else {
        steps = dist / speed;
        if (dx != 0.0f) {
            *velX = dx / steps;
        } else {
            *velX = 0.0f;
        }
        if (dz != 0.0f) {
            *velZ = dz / steps;
        } else {
            *velZ = 0.0f;
        }
    }
    *angle = atan2df(dx, dz);
}

s32 func_80105F40_eye_sore(omObjData *obj, f32 target) {
    f32 rotY = obj->rot.y;
    f32 diff = target - rotY;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 10.0f) {
        obj->rot.y = target;
    } else if (rotY < target) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, -10.0f);
        } else {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, 10.0f);
        }
        return 1;
    } else if (target < rotY) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, 10.0f);
        } else {
            obj->rot.y = func_801059BC_eye_sore(obj->rot.y, -10.0f);
        }
        return 1;
    }
    return 0;
}

void func_80106054_eye_sore(omObjData *obj) {
}

void func_8010605C_eye_sore(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x510000, 0x2B9);
    obj->model[1] = func_8000B108_main(0x510001, 0x2B9);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8010AFB4_eye_sore = 160.0f;
    D_8010AFB8_eye_sore = 120.0f;
    D_8010AFB0_eye_sore = func_8000B838_main(0x510004);
    D_8010AFB2_eye_sore = espEntry(D_8010AFB0_eye_sore, 0, 0);
    espAttrSet(D_8010AFB2_eye_sore, 0x1000);
    espPosSet(D_8010AFB2_eye_sore, D_8010AFB4_eye_sore, D_8010AFB8_eye_sore);
    D_8010AFB4_eye_sore = 160.0f;
    D_8010AFB8_eye_sore = 120.0f;
    D_8010AFB0_eye_sore = func_8000B838_main(0x510005);
    D_8010AFB2_eye_sore = espEntry(D_8010AFB0_eye_sore, 0, 0);
    espAttrSet(D_8010AFB2_eye_sore, 0x1000);
    espPosSet(D_8010AFB2_eye_sore, D_8010AFB4_eye_sore, D_8010AFB8_eye_sore);
    obj->func = func_80106054_eye_sore;
}

void func_80106210_eye_sore(void) {
    omObjData *obj = omAddObj(0x1F4, 3, 3, -1, func_8010605C_eye_sore);
    obj->work[0] = 0;
    D_8010AF70_eye_sore[0].obj = obj;
}

void func_80106250_eye_sore(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    Hu3DAnimKill(D_8010AF22_eye_sore[player]);
    D_8010AF22_eye_sore[player] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010CC18_eye_sore[player][anim], 0, D_8010AC78_eye_sore[chr]);
}

void func_80106328_eye_sore(omObjData *obj, s8 sound) {
    EyeSoreEntry *entry = &D_8010AF70_eye_sore[obj->work[0] + 5];

    if (obj->work[2] == 0) {
        if (entry->unk_04[8] != 0) {
            HuAudFXStop(entry->unk_04[8]);
        }
        entry->unk_04[8] = PlayerFXPlay(D_8010AC30_eye_sore[sound], obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADC8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADD4_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADE0_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADEC_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010ADF8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE04_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE10_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AE1C_eye_sore);

void func_801063E8_eye_sore(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    EyeSoreEntry *entry = &D_8010AF70_eye_sore[obj->work[0] + 5];
    s16 shift;

    if (entry->unk_04[1] != motion) {
        switch (motion) {
            case 4:
            case 7:
            case 8:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            default:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        func_80105DA0_eye_sore(obj, motion, 0, 10, shift);
        entry->unk_04[1] = motion;
        if (motion == 7) {
            func_80045ED0_main((D_8010AC10_eye_sore[chr] << 16) | 0x2F);
        }
    }
}

void func_80106510_eye_sore(omObjData *obj) {
    u8 pad = obj->work[3];
    s16 stickX = D_800CBB6E_main[pad];
    s16 stickY = -D_800D20A1_main[pad];
    f32 mag;
    f32 speed;

    if (stickX != 0 || stickY != 0) {
        mag = sqrtf(stickX * stickX + stickY * stickY);
        if (mag >= 70.0f) {
            speed = 25.0f;
        } else {
            speed = mag * 0.357;
        }
        obj->rot.y = func_801059BC_eye_sore(atan2df(stickX, stickY), 0.0f);
        obj->trans.x += sindf(obj->rot.y) * speed;
        obj->trans.z += cosdf(obj->rot.y) * speed;
        if (mag > 40.0f) {
            func_801063E8_eye_sore(obj, 2);
            func_80106328_eye_sore(obj, 2);
        } else {
            func_801063E8_eye_sore(obj, 1);
            func_80106328_eye_sore(obj, 1);
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        func_801063E8_eye_sore(obj, 0);
    }
}

void func_80106718_eye_sore(omObjData *obj) {
    s16 player = obj->work[0];
    EyeSoreUnkCA60 *state = &D_8010CA60_eye_sore[player];
    s16 i = player * 2;
    EyeSoreUnkC938 *first = &D_8010C938_eye_sore[i];
    EyeSoreUnkC938 *second = &D_8010C938_eye_sore[i + 1];

    if (state->unk_0D < 12) {
        switch (state->unk_0E) {
            case 0:
                first->unk_06 = 1;
                break;
            case 5:
                if (state->unk_0D < 7) {
                    second->unk_06 = 1;
                }
                break;
            case 60:
                first->unk_06 = 5;
                break;
            case 65:
                if (state->unk_0D < 7) {
                    second->unk_06 = 5;
                }
                break;
        }
        state->unk_0E = (state->unk_0E + 1) % 90;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010683C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801070CC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010725C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80107804_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80107CBC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108330_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108AAC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108BBC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108D3C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80108E8C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80109478_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_80109854_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_801098F8_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A0CC_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A3C0_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A464_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A528_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A54C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A62C_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A684_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A8EC_eye_sore);

void func_8010A97C_eye_sore(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010A984_eye_sore);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", func_8010AAF8_eye_sore);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_30_eye_sore/270EF0", D_8010AF0C_eye_sore);
