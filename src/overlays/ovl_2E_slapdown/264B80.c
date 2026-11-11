#include "common.h"
#include "math.h"

// One entry of the 50 entry object table at D_8010AAB0_slapdown. Layout derived
// from the table clear in func_80105A74_slapdown, which walks 50 entries of 0x84
// bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} SlapdownEntry; // sizeof 0x84

extern SlapdownEntry D_8010AAB0_slapdown[50];
// Fields of the first entry of D_8010AAB0_slapdown are accessed through these
// separate symbols.
extern s16 D_8010AAF0_slapdown;
extern s16 D_8010AAF2_slapdown;
extern f32 D_8010AAF4_slapdown;
extern f32 D_8010AAF8_slapdown;
extern void *D_8010AA20_slapdown[];
extern u8 D_8010AA6E_slapdown;
extern s16 D_8010AA90_slapdown[];

void func_80106600_slapdown(omObjData *obj);
void func_80106608_slapdown(omObjData *);
void func_8010820C_slapdown(omObjData *);
void func_8010A550_slapdown(void);

void func_801059A0_slapdown(void) {
    func_8010A550_slapdown();
}

f32 func_801059BC_slapdown(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_slapdown(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_slapdown(void) {
    SlapdownEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010AAB0_slapdown; i < 50; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
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

void func_80105B3C_slapdown(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105BB4_slapdown(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_slapdown(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void func_80105CBC_slapdown(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)D_800CDA7C_main[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_slapdown(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_slapdown(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_slapdown(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_slapdown(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & A_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & B_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & D_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

const char D_8010A95C_slapdown[] = "";

void func_80106290_slapdown(u8 value) {
    D_8010AA6E_slapdown = value;
}

void func_8010629C_slapdown(omObjData *obj, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

void func_80106338_slapdown(omObjData *obj, s16 motion, s16 start, s16 end, s16 *current) {
    if (*current != motion) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], start, end);
        *current = motion;
    }
}

#ifdef NON_MATCHING
// Only differs in f8/f10 register allocation of speed and the absolute z delta,
// like func_801063F4_stacked_deck.
void func_801063D4_slapdown(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1 - x0;
    f32 dz = z1 - z0;
    f32 delta;
    f32 dist;
    f32 step;
    f32 absDx = fabsf(dx);
    f32 absDz = fabsf(dz);

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        step = speed;
        dist = absDx;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velZ = -(delta / step);
    } else {
        if (dz >= 0.0f) {
            *velZ = -speed;
        } else {
            *velZ = speed;
        }
        delta = dx;
        step = speed;
        dist = absDz;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velX = -(delta / step);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801063D4_slapdown);
#endif

f32 func_80106534_slapdown(f32 current, f32 target, f32 step) {
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (current < target) {
        if (diff > 180.0f) {
            current = func_801059BC_slapdown(current, -step);
        } else {
            current = func_801059BC_slapdown(current, step);
        }
    } else if (target < current) {
        if (diff > 180.0f) {
            current = func_801059BC_slapdown(current, step);
        } else {
            current = func_801059BC_slapdown(current, -step);
        }
    }
    return current;
}

void func_80106600_slapdown(omObjData *obj) {
}

void func_80106608_slapdown(omObjData *obj) {
    D_8010AAF0_slapdown = func_8000B838_main(0x4F0000);
    D_8010AAF2_slapdown = espEntry(D_8010AAF0_slapdown, 0, 0);
    espAttrSet(D_8010AAF2_slapdown, 0x4000);
    D_8010AAF4_slapdown = 160.0f;
    D_8010AAF8_slapdown = 120.0f;
    espPosSet(D_8010AAF2_slapdown, 160, 120);
    obj->func = func_80106600_slapdown;
}

void func_801066A4_slapdown(void) {
    omObjData *obj = omAddObj(0x32, 1, 0, -1, func_80106608_slapdown);
    obj->work[0] = 0;
    D_8010AAB0_slapdown[0].obj = obj;
}

void func_801066E4_slapdown(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        DataClose(D_8010AA20_slapdown[i]);
    }
    for (i = 0; i < 4; i++) {
        Hu3DAnimKill(D_8010AA90_slapdown[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106780_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106900_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107858_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107DCC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107FDC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108064_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801080D0_slapdown);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010A984_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801080FC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010820C_slapdown);

void func_80108340_slapdown(void) {
    omObjData *obj = omAddObj(0x96, 1, 0, -1, func_8010820C_slapdown);
    obj->work[0] = 0;
    D_8010AAB0_slapdown[1].obj = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108380_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108420_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801084BC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108BAC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108E44_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108FE4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010924C_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109640_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801096E4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801099C0_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109D54_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E14_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E58_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109E90_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109EE8_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A2B8_slapdown);

void func_8010A3D8_slapdown(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A3E0_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010A550_slapdown);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010AA08_slapdown);
