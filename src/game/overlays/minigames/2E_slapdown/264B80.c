#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

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

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} SlapdownCamera; // sizeof 0x2C

// Sound handles; D_8010AA16_slapdown is misaligned for a standalone array.
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06[5];
} SlapdownBssAA10; // sizeof 0x10

extern s32 D_800A178C_main[][6];

s32 D_8010A6A0_slapdown[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
f32 D_8010A6C0_slapdown[4] = { -380.0f, 380.0f, 380.0f, -380.0f };
f32 D_8010A6D0_slapdown[4] = { -380.0f, -380.0f, 380.0f, 380.0f };
f32 D_8010A6E0_slapdown[4] = { -390.0f, 390.0f, 390.0f, -390.0f };
f32 D_8010A6F0_slapdown[4] = { -390.0f, -390.0f, 390.0f, 390.0f };
f32 D_8010A700_slapdown[4] = { -400.0f, 400.0f, 400.0f, -400.0f };
f32 D_8010A710_slapdown[4] = { -400.0f, -400.0f, 400.0f, 400.0f };
f32 D_8010A720_slapdown[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
f32 D_8010A730_slapdown[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
s32 D_8010A740_slapdown[4][2] = { { 0, 0x4F0007 }, { 0, 0x4F0008 }, { 0, 0x4F0009 }, { 0, 0x4F000A } };
s16 D_8010A760_slapdown[4][2] = { { 60, 450 }, { 45, 470 }, { 30, 480 }, { 25, 500 } };
Vec2f D_8010A770_slapdown[4] = { { -6.5f, -6.5f }, { 6.5f, -6.5f }, { 3.5f, 3.5f }, { -3.5f, 3.5f } }; /* Unreferenced. */
Vec2f D_8010A790_slapdown[4] = { { -4.5f, -4.5f }, { 4.5f, -4.5f }, { 1.5f, 1.5f }, { -1.5f, 1.5f } }; /* Unreferenced. */
Vec2f D_8010A7B0_slapdown[4] = { { -1.08f, -1.08f }, { 1.08f, -1.08f }, { 1.75f, 1.75f }, { -1.75f, 1.75f } };
Vec2f D_8010A7D0_slapdown[4] = { { -0.75f, -0.75f }, { 0.75f, -0.75f }, { 0.75f, 0.75f }, { -0.75f, 0.75f } };
f32 D_8010A7F0_slapdown[9] = { -65.0f, 65.0f, 190.0f, 190.0f, 130.0f, 0.0f, -130.0f, -190.0f, -190.0f };
f32 D_8010A814_slapdown[9] = { -190.0f, -190.0f, 65.0f, -65.0f, 190.0f, 190.0f, 190.0f, 65.0f, -65.0f };
Vec2f D_8010A838_slapdown[4] = { { 50.0f, 92.0f }, { 271.0f, 92.0f }, { 239.0f, 155.0f }, { 81.0f, 155.0f } };
Vec2f D_8010A858_slapdown[4] = { { 49.0f, 92.0f }, { 272.0f, 92.0f }, { 238.0f, 155.0f }, { 82.0f, 155.0f } };
s32 D_8010A878_slapdown[4] = { 0x4F000D, 0x4F000E, 0x4F000F, 0x4F0010 };
s32 D_8010A888_slapdown = 0;
SlapdownCamera D_8010A88C_slapdown[1] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 33.0f }
};

extern const s16 D_8010AA08_slapdown[];

SlapdownBssAA10 slapdownBssAA10 BSS;
extern s16 D_8010AA10_slapdown;    // slapdownBssAA10.unk_00
extern s16 D_8010AA12_slapdown;    // slapdownBssAA10.unk_02
extern s16 D_8010AA14_slapdown;    // slapdownBssAA10.unk_04
extern s16 D_8010AA16_slapdown[5]; // slapdownBssAA10.unk_06
void *D_8010AA20_slapdown[4] BSS;
s16 D_8010AA30_slapdown BSS;
s16 D_8010AA32_slapdown BSS;
u8 D_8010AA34_slapdown[4] BSS; /* Unreferenced. */
s16 D_8010AA38_slapdown[10] BSS;
f32 D_8010AA4C_slapdown BSS;
u8 D_8010AA50_slapdown BSS;
s16 D_8010AA52_slapdown BSS;
u8 D_8010AA54_slapdown[4] BSS; /* Unreferenced. */
void *D_8010AA58_slapdown[5] BSS;
s16 D_8010AA6C_slapdown BSS;
u8 D_8010AA6E_slapdown BSS;
s16 D_8010AA70_slapdown BSS;
s16 D_8010AA72_slapdown BSS;
s16 D_8010AA74_slapdown BSS;
s16 D_8010AA76_slapdown BSS;
void *D_8010AA78_slapdown[6] BSS;
s16 D_8010AA90_slapdown[4] BSS;
s16 D_8010AA98_slapdown BSS;
s16 D_8010AA9A_slapdown BSS;
void *D_8010AA9C_slapdown BSS;
s16 D_8010AAA0_slapdown BSS;
u8 D_8010AAA4_slapdown[0xC] BSS; /* Unreferenced. */
SlapdownEntry D_8010AAB0_slapdown[50] BSS;
// Fields of the first entry of D_8010AAB0_slapdown are accessed through these
// separate symbols.
extern s16 D_8010AAF0_slapdown; // [0].unk_40[0]
extern s16 D_8010AAF2_slapdown; // [0].unk_40[1]
extern f32 D_8010AAF4_slapdown; // [0].unk_44.x
extern f32 D_8010AAF8_slapdown; // [0].unk_44.y

void func_80106600_slapdown(omObjData *obj);
void func_8010924C_slapdown(omObjData *obj);
void func_80106608_slapdown(omObjData *);
void func_80106900_slapdown(omObjData *obj);
void func_8010820C_slapdown(omObjData *);
void func_80107DCC_slapdown(void);
void func_80108BAC_slapdown(omObjData *obj);
void func_80107858_slapdown(omObjData *obj);
void func_801084BC_slapdown(omObjData *obj);
void func_80108E44_slapdown(void);
void func_801096E4_slapdown(void);
void func_801099C0_slapdown(void);
void func_80109EE8_slapdown(omObjData *obj);
void func_8010A2B8_slapdown(omObjData *obj);
void func_8010A3E0_slapdown(void);
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

void func_801063D4_slapdown(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1;
    f32 dz = z1;
    f32 absDx;
    f32 absDz;
    f32 delta;
    f32 dist;
    f32 step;

    dx -= x0;
    dz -= z0;
    absDx = fabsf(dx);
    absDz = fabsf(dz);

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        dist = absDx;
        step = speed;
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
        dist = absDz;
        step = speed;
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
    D_8010AAF0_slapdown = HuSprAnimDataRead(0x4F0000);
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

void func_80106780_slapdown(omObjData *obj) {
    if (D_8010AA30_slapdown == 1 && D_8010AA74_slapdown < 50) {
        if (((rand8() & 0xFF) + (rand8() & 0xFF)) % D_8010A760_slapdown[GwPlayer[obj->work[0]].cpu_difficulty][0] == 0 || D_8010AA74_slapdown < 2) {
            D_800D5558_main[obj->work[3]] |= 0x8000;
        }
    } else {
        if (((rand8() & 0xFF) + (rand8() & 0xFF)) % D_8010A760_slapdown[GwPlayer[obj->work[0]].cpu_difficulty][1] == 0) {
            D_800D5558_main[obj->work[3]] |= 0x8000;
        }
    }
}

void func_80106900_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[11 + obj->work[0]];
    SlapdownEntry *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 found;
    s16 moving;
    s16 max;
    s16 pick;

    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010AAB0_slapdown[11 + i];
        objs[i] = entries[i]->obj;
    }
    switch (D_8010AA6E_slapdown) {
        case 3:
        case 4:
        case 5:
            if (GwPlayer[obj->work[0]].stat & 1) {
                func_80105B3C_slapdown(obj->work[0]);
                if (D_8010AA6E_slapdown == 5) {
                    func_80106780_slapdown(obj);
                }
            }
            if (obj->work[0] == 3) {
                if (D_8010AA74_slapdown > 0) {
                    for (i = 0; i < 4; i++) {
                        if (entries[i]->unk_04 == 0 && entries[i]->unk_06 == 0 && (D_800D5558_main[objs[i]->work[3]] & 0x8000)) {
                            entries[i]->unk_06 = 1;
                        }
                    }
                }
                found = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_06 != 0 && entries[i]->unk_06 < 99) {
                        found = 1;
                    }
                }
                if (found == 1) {
                    max = 1;
                    for (i = 0; i < 4; i++) {
                        if (max < entries[i]->unk_06 && entries[i]->unk_06 < 99) {
                            max = entries[i]->unk_06;
                        }
                    }
                    if (D_8010AA74_slapdown % 3 == 0) {
                        pick = (u8)(rand8() % 4);
                        while (TRUE) {
                            if (entries[pick]->unk_06 == max) {
                                func_8004AC98_main(0x47B, objs[pick]->work[0]);
                                func_80106338_slapdown(objs[pick], 2, 2, 0, &entries[pick]->unk_04);
                                Hu3DMotionSpeedSet(objs[pick]->model[4], 1.0f);
                                entries[pick]->unk_06 = 99;
                                entries[pick]->unk_08 = D_8010AA98_slapdown;
                                D_8010AA98_slapdown++;
                                if (D_8010AA30_slapdown == 1) {
                                    entries[pick]->unk_0A = D_8010AA74_slapdown;
                                } else {
                                    entries[pick]->unk_0A = -1;
                                    D_8010AAA0_slapdown++;
                                }
                                break;
                            }
                            pick++;
                            if (pick >= 4) {
                                pick = 0;
                            }
                        }
                        for (i = 0; i < 4; i++) {
                            if (pick != i && entries[i]->unk_06 != 0 && entries[i]->unk_06 < 99) {
                                entries[i]->unk_06++;
                            }
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_04 == 2 && Hu3DData[objs[i]->model[0]].motTime >= 10.0f) {
                        Hu3DMotionTimeSet(objs[i]->model[0], 9.0f);
                        Hu3DMotionSpeedSet(objs[i]->model[0], 0.0f);
                        if (entries[i]->unk_0E == 0) {
                            entries[i]->unk_0E = 1;
                        }
                    }
                }
                D_8010AA10_slapdown = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_06 != 0 && entries[i]->unk_06 != 100) {
                        D_8010AA10_slapdown = 1;
                    }
                }
            }
            switch (entry->unk_0E) {
                case 0:
                    entry->unk_18 = 0.0f;
                    break;
                case 1:
                    entry->unk_18 = func_801059BC_slapdown(entry->unk_18, 20.0f);
                    switch (entry->unk_08) {
                        case 0:
                            if (entry->unk_18 >= 93.0f) {
                                entry->unk_18 = 93.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                func_8004AC98_main(0x47C, obj->work[0]);
                            }
                            break;
                        case 1:
                            if (entry->unk_18 >= 91.0f) {
                                entry->unk_18 = 91.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                func_8004AC98_main(0x47C, obj->work[0]);
                            }
                            break;
                        case 2:
                            if (entry->unk_18 >= 89.0f) {
                                entry->unk_18 = 89.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                func_8004AC98_main(0x47C, obj->work[0]);
                            }
                            break;
                        case 3:
                            if (entry->unk_18 >= 87.0f) {
                                entry->unk_18 = 87.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                func_8004AC98_main(0x47C, obj->work[0]);
                            }
                            break;
                    }
                    break;
                case 50:
                    if (D_8010AA74_slapdown < -29) {
                        if (D_8010AA30_slapdown == 1) {
                            entry->unk_0E = 100;
                        } else {
                            entry->unk_0E = 99;
                        }
                    }
                    break;
                case 99:
                    if (entry->unk_18 <= 15.0f || entry->unk_18 >= 345.0f) {
                        entry->unk_18 = 0.0f;
                        entry->unk_0E = 100;
                    } else {
                        entry->unk_18 = func_801059BC_slapdown(entry->unk_18, -15.0f);
                    }
                    break;
                case 100:
                    entry->unk_06 = 100;
                    if (entry->unk_0A == -1) {
                        switch (entry->unk_0C) {
                            case 0:
                                if (D_8010AA16_slapdown[obj->work[0]] == -1) {
                                    D_8010AA16_slapdown[obj->work[0]] = func_8004AC98_main(0x47E, obj->work[0]);
                                    PlayerFXPlay(0x286, obj->work[0]);
                                }
                                obj->rot.y = func_801059BC_slapdown(obj->rot.y, 20.0f);
                                if (GwPlayer[obj->work[0]].chr != 5) {
                                    obj->trans.x += D_8010A7B0_slapdown[obj->work[1]].x;
                                    obj->trans.z += D_8010A7B0_slapdown[obj->work[1]].y;
                                } else {
                                    obj->trans.x += D_8010A7D0_slapdown[obj->work[1]].x;
                                    obj->trans.z += D_8010A7D0_slapdown[obj->work[1]].y;
                                }
                                func_8010629C_slapdown(obj, 3, 0, 5, 2, &entry->unk_04);
                                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                                if ((s16)obj->rot.y == D_8010A720_slapdown[obj->work[1]]) {
                                    entry->unk_0C = 1;
                                    obj->rot.y = D_8010A720_slapdown[obj->work[1]];
                                }
                                break;
                            case 1:
                                func_8010629C_slapdown(obj, 3, 0, 5, 1, &entry->unk_04);
                                break;
                        }
                    }
                    break;
            }
            break;
        case 6:
            if (entry->unk_0A == -1) {
                switch (entry->unk_0C) {
                    case 0:
                        if (D_8010AA16_slapdown[obj->work[0]] == -1) {
                            D_8010AA16_slapdown[obj->work[0]] = func_8004AC98_main(0x47E, obj->work[0]);
                            PlayerFXPlay(0x286, obj->work[0]);
                        }
                        obj->rot.y = func_801059BC_slapdown(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != 5) {
                            obj->trans.x += D_8010A7B0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7B0_slapdown[obj->work[1]].y;
                        } else {
                            obj->trans.x += D_8010A7D0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7D0_slapdown[obj->work[1]].y;
                        }
                        func_8010629C_slapdown(obj, 3, 0, 5, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == D_8010A720_slapdown[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = D_8010A720_slapdown[obj->work[1]];
                        }
                        break;
                    case 1:
                        func_8010629C_slapdown(obj, 3, 0, 5, 1, &entry->unk_04);
                        break;
                }
            }
            break;
        case 7:
        case 8:
            if (entry->unk_16 == 0) {
                switch (entry->unk_0C) {
                    case 0:
                        obj->rot.y = func_801059BC_slapdown(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != 5) {
                            obj->trans.x += D_8010A7B0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7B0_slapdown[obj->work[1]].y;
                        } else {
                            obj->trans.x += D_8010A7D0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7D0_slapdown[obj->work[1]].y;
                        }
                        func_8010629C_slapdown(obj, 1, 0, 3, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == D_8010A720_slapdown[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = D_8010A720_slapdown[obj->work[1]];
                        }
                        break;
                    case 1:
                        if (D_8010AA6E_slapdown == 8 && D_8010AA74_slapdown >= 0) {
                            func_8010629C_slapdown(obj, 4, 0, 5, 0, &entry->unk_04);
                            func_80045ED0_main((D_8010A6A0_slapdown[GwPlayer[obj->work[0]].chr] << 16) | 0x30);
                            entry->unk_0C = 2;
                        } else {
                            func_8010629C_slapdown(obj, 0, 0, 5, 1, &entry->unk_04);
                        }
                        break;
                    case 2:
                        break;
                }
            } else {
                switch (entry->unk_0C) {
                    case 0:
                        obj->rot.y = func_801059BC_slapdown(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != 5) {
                            obj->trans.x += D_8010A7B0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7B0_slapdown[obj->work[1]].y;
                        } else {
                            obj->trans.x += D_8010A7D0_slapdown[obj->work[1]].x;
                            obj->trans.z += D_8010A7D0_slapdown[obj->work[1]].y;
                        }
                        func_8010629C_slapdown(obj, 3, 0, 3, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == D_8010A720_slapdown[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = D_8010A720_slapdown[obj->work[1]];
                        }
                        break;
                    case 1:
                        if (D_8010AA6E_slapdown == 8 && D_8010AA32_slapdown != 0 && D_8010AA74_slapdown >= 0) {
                            func_8010629C_slapdown(obj, 5, 0, 5, 0, &entry->unk_04);
                            if (D_8010AA16_slapdown[obj->work[0]] != -1) {
                                HuAudFXStop(D_8010AA16_slapdown[obj->work[0]]);
                            }
                            entry->unk_0C = 2;
                        } else {
                            func_8010629C_slapdown(obj, 3, 0, 5, 1, &entry->unk_04);
                        }
                        break;
                    case 2:
                        break;
                }
            }
            if (obj->work[0] == 3 && D_8010AA32_slapdown == 0) {
                moving = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_16 != 0 &&
                        (entries[i]->unk_04 != 3 ||
                         (s16)objs[i]->rot.y != D_8010A720_slapdown[objs[i]->work[1]])) {
                        moving = 1;
                    }
                }
                if (moving == 0) {
                    D_8010AA32_slapdown = 1;
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], entry->unk_18, D_8010A730_slapdown[obj->work[1]], 0.0f);
}

void func_80107858_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[11 + obj->work[0]];
    s8 chr = GwPlayer[obj->work[0]].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2A9);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x14));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 8));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x30));
    if (chr != 3) {
        func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x38));
    } else {
        func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x3A));
    }
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    entry->unk_04 = 0;
    if (chr != 5) {
        obj->trans.x = D_8010A6C0_slapdown[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = D_8010A6D0_slapdown[obj->work[1]];
    } else {
        obj->trans.x = D_8010A6E0_slapdown[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = D_8010A6F0_slapdown[obj->work[1]];
    }
    obj->rot.x = 0.0f;
    obj->rot.y = D_8010A720_slapdown[obj->work[1]];
    obj->rot.z = 0.0f;
    obj->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[2] = func_8000B108_main(0x4F0018, 0x2A9);
    D_8010AA20_slapdown[obj->work[1]] = DataRead(D_8010A740_slapdown[obj->work[1]][1]);
    D_8010AA90_slapdown[obj->work[1]] =
        Hu3DAnimCreate(Hu3DData[obj->model[2]].hmf, D_8010AA20_slapdown[obj->work[1]], 0, "s246_07_DEF");
    Hu3DModelRemakeStatic(obj->model[2]);
    func_8001C514_main(obj->model[2]);
    Hu3DMotionTimeSet(obj->model[2], 0.0f);
    Hu3DMotionSpeedSet(obj->model[2], 0.0f);
    switch (obj->work[1]) {
        case 0:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, -285.0f);
            break;
        case 1:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, -285.0f);
            break;
        case 2:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, 285.0f);
            break;
        case 3:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, 285.0f);
            break;
    }
    Hu3DModelRotSet(obj->model[2], 0.0f, D_8010A730_slapdown[obj->work[1]], 0.0f);
    obj->model[3] = func_8000B108_main(0x4F0017, 0x2A9);
    Hu3DModelPosSet(obj->model[3], D_8010A700_slapdown[obj->work[1]], 0.0f, D_8010A710_slapdown[obj->work[1]]);
    Hu3DModelRotSet(obj->model[3], 0.0f, D_8010A720_slapdown[obj->work[1]], 0.0f);
    obj->model[4] = func_8000B108_main(0x4F001A, 0x2A9);
    Hu3DModelPosSet(obj->model[4], D_8010A700_slapdown[obj->work[1]], 0.0f, D_8010A710_slapdown[obj->work[1]]);
    Hu3DModelRotSet(obj->model[4], 0.0f, D_8010A720_slapdown[obj->work[1]], 0.0f);
    Hu3DMotionTimeSet(obj->model[4], 0.0f);
    Hu3DMotionSpeedSet(obj->model[4], 0.0f);
    entry->unk_0A = -2;
    obj->func = func_80106900_slapdown;
}

void func_80107DCC_slapdown(void) {
    s16 order[4];
    SlapdownEntry *entry;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 pick;
    u16 player;

    for (i = 0; i < 4; i++) {
        order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                player = 0;
                break;
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
            default:
                player = 0;
                break;
        }
        entry = &D_8010AAB0_slapdown[11 + i];
        obj = omAddObj(0xFA, 10, 60, -1, func_80107858_slapdown);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        entry->obj = obj;
        pick = rand8() % (4 - i);
        obj->work[1] = order[pick];
        order[pick] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void func_80107FDC_slapdown(omObjData *obj, s16 anim) {
    Hu3DAnimKill(D_8010AA12_slapdown);
    D_8010AA12_slapdown = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010AA58_slapdown[anim], 0, "s246_01_DEF");
}

void func_80108064_slapdown(void) {
    s16 i;

    for (i = 0; i < 5; i++) {
        DataClose(D_8010AA58_slapdown[i]);
    }
    Hu3DAnimKill(D_8010AA12_slapdown);
}

void func_801080D0_slapdown(void) {
    DataClose(D_8010AA9C_slapdown);
    Hu3DAnimKill(D_8010AA52_slapdown);
}

void func_801080FC_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[1];

    switch (D_8010AA6E_slapdown) {
        case 0:
            break;
        case 1:
            if (entry->unk_04 < 60) {
                if (entry->unk_06 == 0) {
                    HuAudFXPlay(0x479);
                    entry->unk_06 = 1;
                }
                entry->unk_04++;
                func_80107FDC_slapdown(obj, entry->unk_04 % 5);
            } else {
                if (entry->unk_06 == 1) {
                    HuAudFXPlay(0x47F);
                    entry->unk_06 = 2;
                }
                func_80107FDC_slapdown(obj, D_8010AA72_slapdown);
                D_8010AA50_slapdown = 1;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }
}

void func_8010820C_slapdown(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4F0019, 0x2A9);
    D_8010AA58_slapdown[0] = DataRead(0x4F0011);
    D_8010AA58_slapdown[1] = DataRead(0x4F0012);
    D_8010AA58_slapdown[2] = DataRead(0x4F0013);
    D_8010AA58_slapdown[3] = DataRead(0x4F0014);
    D_8010AA58_slapdown[4] = DataRead(0x4F0015);
    D_8010AA12_slapdown = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010AA58_slapdown[0], 0, "s246_19_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    D_8010AA72_slapdown = (u8)(rand8() % 5);
    obj->func = func_801080FC_slapdown;
}

const char D_8010A9C4_slapdown[] = "";

void func_80108340_slapdown(void) {
    omObjData *obj = omAddObj(0x96, 1, 0, -1, func_8010820C_slapdown);
    obj->work[0] = 0;
    D_8010AAB0_slapdown[1].obj = obj;
}

void func_80108380_slapdown(omObjData *obj, s16 anim) {
    Hu3DAnimKill(D_8010AA38_slapdown[obj->work[0]]);
    D_8010AA38_slapdown[obj->work[0]] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010AA78_slapdown[anim], 0, "s246_01_DEF");
}

void func_80108420_slapdown(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(D_8010AA78_slapdown[i]);
    }
    for (i = 0; i < 9; i++) {
        Hu3DAnimKill(D_8010AA38_slapdown[i]);
    }
}

void func_801084BC_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[2 + obj->work[0]];
    SlapdownEntry *entries[9];
    omObjData *objs[9];
    s16 i;
    s16 pick;

    for (i = 0; i < 9; i++) {
        entries[i] = &D_8010AAB0_slapdown[2 + i];
        objs[i] = entries[i]->obj;
    }
    (void)objs;
    if (obj->work[0] == 0) {
        D_8010AA4C_slapdown = func_801059BC_slapdown(D_8010AA4C_slapdown, 25.0f);
    }
    switch (D_8010AA6E_slapdown) {
        case 2:
            if (obj->work[0] == 8 && D_8010AA9A_slapdown == 0) {
                D_8010AA9A_slapdown = 1;
                pick = (u8)(rand8() % 9);
                if (entries[pick]->unk_06 == D_8010AA72_slapdown) {
                    pick = (u8)(rand8() % 9);
                    if (entries[pick]->unk_06 == D_8010AA72_slapdown) {
                        D_8010AA30_slapdown = 1;
                    } else {
                        D_8010AA30_slapdown = 0;
                    }
                } else {
                    D_8010AA30_slapdown = 0;
                }
                entries[pick]->unk_04 = 1;
            }
            break;
        case 3:
            obj->rot.z = D_8010AA4C_slapdown;
            D_8010AA76_slapdown = 1;
            if (D_8010AA74_slapdown <= 60 && obj->work[0] == 8) {
                for (i = 0; i < 9; i++) {
                    if (entries[i]->unk_04 == 1) {
                        D_8010AA50_slapdown = 3;
                    }
                }
            }
            break;
        case 4:
            if (entry->unk_04 == 1) {
                switch (entry->unk_08) {
                    case 0:
                        obj->rot.z = D_8010AA4C_slapdown;
                        if (D_8010AA4C_slapdown >= 150.0f && D_8010AA4C_slapdown <= 180.0f) {
                            entry->unk_08 = 1;
                        }
                        break;
                    case 1:
                        obj->rot.z = D_8010AA4C_slapdown;
                        if (D_8010AA4C_slapdown >= 0.0f && D_8010AA4C_slapdown <= 30.0f) {
                            HuAudFXPlay(0x480);
                            func_80108380_slapdown(obj, entry->unk_06);
                            obj->rot.z = 0.0f;
                            D_8010AA50_slapdown = 4;
                            entry->unk_08 = 0;
                        }
                        break;
                }
            } else {
                if (D_8010AA76_slapdown == 3) {
                    D_8010AA76_slapdown = 1;
                }
                obj->rot.z = D_8010AA4C_slapdown;
            }
            break;
        case 5:
            if (entry->unk_04 == 1) {
                if (D_8010AA74_slapdown <= 0) {
                    obj->rot.z = 0.0f;
                    if (D_8010AA10_slapdown == 0) {
                        if (D_8010AA30_slapdown != 1) {
                            entry->unk_04 = 99;
                            if (D_8010AAA0_slapdown < 3) {
                                func_80108380_slapdown(obj, 5);
                            } else {
                                entry->unk_04 = 100;
                            }
                        } else {
                            entry->unk_04 = 100;
                        }
                        D_8010AA50_slapdown = 5;
                    }
                }
            } else if (D_8010AA74_slapdown <= 0) {
                switch (entry->unk_08) {
                    case 0:
                        obj->rot.z = D_8010AA4C_slapdown;
                        if (D_8010AA4C_slapdown >= 0.0f && D_8010AA4C_slapdown <= 30.0f) {
                            entry->unk_08 = 1;
                        }
                        break;
                    case 1:
                        if (D_8010AA76_slapdown == 1) {
                            D_8010AA76_slapdown = 0;
                        }
                        obj->rot.z = 0.0f;
                        break;
                }
            } else {
                obj->rot.z = D_8010AA4C_slapdown;
            }
            if (obj->work[0] == 8 && D_8010AA50_slapdown == 5 && D_8010AA30_slapdown != 1) {
                pick = (u8)(rand8() % 9);
                while (TRUE) {
                    if (entries[pick]->unk_04 == 0) {
                        break;
                    }
                    pick++;
                    if (pick >= 9) {
                        pick = 0;
                    }
                }
                entries[pick]->unk_04 = 1;
                for (i = 0; i < 9; i++) {
                    entries[i]->unk_08 = 0;
                }
            }
            break;
        case 6:
        case 7:
            if (entry->unk_04 == 100) {
                obj->rot.z = 0.0f;
            } else {
                switch (entry->unk_08) {
                    case 0:
                        if (obj->rot.z >= 0.0f && obj->rot.z <= 30.0f) {
                            entry->unk_08 = 1;
                        } else {
                            obj->rot.z = D_8010AA4C_slapdown;
                        }
                        break;
                    case 1:
                        if (D_8010AA76_slapdown == 1) {
                            D_8010AA76_slapdown = 0;
                        }
                        obj->rot.z = 0.0f;
                        break;
                }
            }
            break;
    }
    if (obj->work[0] == 8) {
        switch (D_8010AA76_slapdown) {
            case 0:
                if (D_8010AA14_slapdown != -1) {
                    HuAudFXStop(D_8010AA14_slapdown);
                    D_8010AA14_slapdown = -1;
                    D_8010AA76_slapdown = 2;
                }
                break;
            case 1:
                if (D_8010AA14_slapdown == -1) {
                    D_8010AA14_slapdown = HuAudFXPlay(0x47A);
                }
                break;
            case 2:
                HuAudFXPlay(0x480);
                D_8010AA76_slapdown = 3;
                break;
        }
    }
}

void func_80108BAC_slapdown(omObjData *obj) {
    SlapdownEntry *entries[9];
    omObjData *objs[9];
    s16 i;
    s16 j;

    for (i = 0; i < 9; i++) {
        entries[i] = &D_8010AAB0_slapdown[2 + i];
        objs[i] = entries[i]->obj;
    }
    obj->model[0] = func_8000B108_main(0x4F0016, 0x2A9);
    obj->trans.x = D_8010A7F0_slapdown[obj->work[1]];
    obj->trans.y = 35.7455f;
    obj->trans.z = D_8010A814_slapdown[obj->work[1]];
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    if (obj->work[0] == 8) {
        D_8010AA78_slapdown[0] = DataRead(0x4F0001);
        D_8010AA78_slapdown[1] = DataRead(0x4F0002);
        D_8010AA78_slapdown[2] = DataRead(0x4F0003);
        D_8010AA78_slapdown[3] = DataRead(0x4F0004);
        D_8010AA78_slapdown[4] = DataRead(0x4F0005);
        D_8010AA78_slapdown[5] = DataRead(0x4F0006);
        entries[0]->unk_06 = D_8010AA72_slapdown;
        for (j = 1, i = 0; i < 5; i++) {
            if (i != D_8010AA72_slapdown) {
                entries[j]->unk_06 = i;
                entries[j + 1]->unk_06 = i;
                j += 2;
            }
        }
        for (i = 0; i < 9; i++) {
            D_8010AA38_slapdown[objs[i]->work[0]] =
                Hu3DAnimCreate(Hu3DData[objs[i]->model[0]].hmf, D_8010AA78_slapdown[5], 0, "s246_01_DEF");
            Hu3DModelRemakeStatic(objs[i]->model[0]);
            func_8001C514_main(objs[i]->model[0]);
        }
    }
    obj->func = func_801084BC_slapdown;
}

void func_80108E44_slapdown(void) {
    s16 order[9];
    SlapdownEntry *entry;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 pick;

    for (i = 0; i < 9; i++) {
        order[i] = i;
    }
    for (i = 0; i < 9; i++) {
        entry = &D_8010AAB0_slapdown[2 + i];
        obj = omAddObj(0xC8, 1, 0, -1, func_80108BAC_slapdown);
        obj->work[0] = i;
        entry->obj = obj;
        pick = rand8() % (9 - i);
        obj->work[1] = order[pick];
        order[pick] = -1;
        for (j = 1; j < 9 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void func_80108FE4_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[15 + obj->work[0]];
    SlapdownEntry *entries[4];
    omObjData *objs[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010AAB0_slapdown[11 + i];
        objs[i] = entries[i]->obj;
    }
    switch (D_8010AA6E_slapdown) {
        case 7:
        case 8:
        case 9:
            switch (entry->unk_04) {
                case 0:
                    for (i = 0; i < 4; i++) {
                        if (objs[i]->work[1] == obj->work[0] && entries[i]->unk_0A != -2 && entries[i]->unk_0A != -1) {
                            espDispOn(entry->unk_40[1]);
                            switch (entries[i]->unk_16) {
                                case 0:
                                    espDispOn(entry->unk_06);
                                    break;
                                case 1:
                                    espDispOn(entry->unk_08);
                                    break;
                                case 2:
                                    espDispOn(entry->unk_0A);
                                    break;
                                case 3:
                                    espDispOn(entry->unk_0C);
                                    break;
                            }
                            entry->unk_04 = 1;
                        }
                    }
                    break;
                case 1:
                    if (entry->unk_18 < 1.0f) {
                        entry->unk_18 += 0.05f;
                    } else {
                        entry->unk_04 = 2;
                    }
                    break;
                case 2:
                    break;
            }
            break;
    }
    espScaleSet(entry->unk_40[1], entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_06, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_08, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_0A, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_0C, entry->unk_18, entry->unk_18);
}

void func_8010924C_slapdown(omObjData *obj) {
    SlapdownEntry *entry = &D_8010AAB0_slapdown[15 + obj->work[0]];
    s16 i;

    if (obj->work[0] == 0 || obj->work[0] == 3) {
        entry->unk_40[0] = HuSprAnimDataRead(0x4F000C);
        entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
        if (obj->work[0] == 3) {
            espZRotSet(entry->unk_40[1], 180.0f);
        }
    } else {
        entry->unk_40[0] = HuSprAnimDataRead(0x4F000B);
        entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
        if (obj->work[0] == 2) {
            espZRotSet(entry->unk_40[1], 180.0f);
        }
    }
    espAttrSet(entry->unk_40[1], 0);
    espPosSet(entry->unk_40[1], D_8010A838_slapdown[obj->work[0]].x, D_8010A838_slapdown[obj->work[0]].y);
    espDispOff(entry->unk_40[1]);
    espPriSet(entry->unk_40[1], 0xEEEE);
    for (i = 0; i < 4; i++) {
        entry->unk_40[0] = HuSprAnimDataRead(D_8010A878_slapdown[i]);
        switch (i) {
            case 0:
                entry->unk_06 = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_06, 0);
                espPosSet(entry->unk_06, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                espDispOff(entry->unk_06);
                espPriSet(entry->unk_06, 0xAAAA);
                break;
            case 1:
                entry->unk_08 = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_08, 0);
                espPosSet(entry->unk_08, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                espDispOff(entry->unk_08);
                espPriSet(entry->unk_08, 0xAAAA);
                break;
            case 2:
                entry->unk_0A = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_0A, 0);
                espPosSet(entry->unk_0A, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                espDispOff(entry->unk_0A);
                espPriSet(entry->unk_0A, 0xAAAA);
                break;
            case 3:
                entry->unk_0C = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_0C, 0);
                espPosSet(entry->unk_0C, D_8010A858_slapdown[obj->work[0]].x, D_8010A858_slapdown[obj->work[0]].y);
                espDispOff(entry->unk_0C);
                espPriSet(entry->unk_0C, 0xAAAA);
                break;
        }
    }
    entry->unk_18 = 0.1f;
    obj->func = func_80108FE4_slapdown;
}

void func_80109640_slapdown(void) {
    SlapdownEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 4; i++) {
        entry = &D_8010AAB0_slapdown[15 + i];
        obj = omAddObj(0x12C, 1, 0, -1, func_8010924C_slapdown);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void func_801096E4_slapdown(void) {
    SlapdownEntry *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 j;
    s16 active;
    s16 out;
    s16 rank;
    s16 min;
    s16 found;

    active = 0;
    out = 0;
    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010AAB0_slapdown[11 + i];
        objs[i] = entries[i]->obj;
        // do-while(0) needed to match register allocation.
        do {
            entries[i]->unk_16 = -1;
        } while (0);
        if (entries[i]->unk_0A == -2) {
            out++;
        }
        if (entries[i]->unk_0A >= 0) {
            active++;
        }
    }
    // Copied but never read in the original.
    (void)objs;
    if (active == 0) {
        if (out == 1) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_0A == -1) {
                    entries[i]->unk_16 = 1;
                } else {
                    entries[i]->unk_16 = 0;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                entries[i]->unk_16 = 3;
            }
        }
    } else {
        rank = 3;
        found = 0;
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_0A == -1) {
                entries[i]->unk_16 = rank;
                found = 1;
            }
        }
        min = 9999;
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_0A == -2) {
                entries[i]->unk_16 = rank;
                found = 1;
            }
        }
        if (found) {
            rank--;
        }
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_16 == -1 && entries[i]->unk_0A < min) {
                    min = entries[i]->unk_0A;
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_16 == -1 && entries[i]->unk_0A == min) {
                    entries[i]->unk_16 = rank;
                    rank--;
                }
            }
            min = 9999;
        }
    }
}

void func_801099C0_slapdown(void) {
    SlapdownEntry *entries[4];
    omObjData *objs[4];
    s16 ranks[4];
    s16 places[4];
    s16 i;
    s16 found;

    for (i = 0; i < 4; i++) {
        ranks[i] = 4;
        places[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010AAB0_slapdown[11 + i];
        objs[i] = entries[i]->obj;
        if (ranks[0] > entries[i]->unk_16) {
            ranks[0] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[0] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[1]) {
            ranks[1] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[1] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[2]) {
            ranks[2] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[2] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[3]) {
            ranks[3] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[0] == entries[i]->unk_16) {
            places[i] = 0;
        }
        if (ranks[1] == entries[i]->unk_16) {
            places[i] = 1;
        }
        if (ranks[2] == entries[i]->unk_16) {
            places[i] = 2;
        }
        if (ranks[3] == entries[i]->unk_16) {
            places[i] = 3;
        }
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_16 != 3) {
            found = 1;
        }
    }
    if (found == FALSE) {
        for (i = 0; i < 4; i++) {
            places[i] = 3;
        }
        D_8010AAA0_slapdown = 4;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[objs[i]->work[0]].bonusCoin = places[i];
        entries[i]->unk_16 = places[i];
    }
}

void func_80109D54_slapdown(void) {
    u32 i;

    if (D_8010A888_slapdown == 0) {
        D_8010A888_slapdown = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2037.5552f;
            CRotM[i].x = 311.9663f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -42.5f;
            CenterM[i].z = -160.0f;
        }
    }
}

void func_80109E14_slapdown(omObjData *obj) {
    func_80108064_slapdown();
    func_80108420_slapdown();
    func_801066E4_slapdown();
    HuAudFXStop(-1);
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_80109E58_slapdown(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80109E14_slapdown;
    }
}

void func_80109E90_slapdown(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_80109E58_slapdown;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_80109EE8_slapdown(omObjData *obj) {
    SlapdownEntry *entry;
    s16 i;

    switch (D_8010AA6E_slapdown) {
        case 0:
            func_80106290_slapdown(1);
            D_8010AA74_slapdown = 0;
            HuAudFXPlay(0x47D);
            break;
        case 1:
            if (D_8010AA50_slapdown == 1) {
                func_80106290_slapdown(2);
                GMesCreate(7);
                D_8010AA74_slapdown = 0;
            }
            break;
        case 2:
            if (D_8010AA74_slapdown >= 63) {
                HuAudSeqPlay(0x38);
            } else {
                D_8010AA74_slapdown++;
            }
            if (GMesStatGet() == 0) {
                func_80106290_slapdown(3);
                D_8010AA74_slapdown = 90;
            }
            break;
        case 3:
            D_8010AA74_slapdown--;
            if (D_8010AA50_slapdown == 3) {
                func_80106290_slapdown(4);
            }
            break;
        case 4:
            if (D_8010AA74_slapdown >= -29) {
                D_8010AA74_slapdown--;
            }
            if (D_8010AA50_slapdown == 4) {
                func_80106290_slapdown(5);
            }
            break;
        case 5:
            if (D_8010AA74_slapdown >= -29) {
                D_8010AA74_slapdown--;
            }
            if (D_8010AA50_slapdown == 5) {
                if (D_8010AA30_slapdown != 1) {
                    if (D_8010AAA0_slapdown < 3) {
                        func_80106290_slapdown(4);
                        D_8010AA74_slapdown = 60;
                        for (i = 0; i < 9; i++) {
                            entry = &D_8010AAB0_slapdown[2 + i];
                            if (entry->unk_04 == 1) {
                                if (entry->unk_06 == D_8010AA72_slapdown) {
                                    D_8010AA30_slapdown = 1;
                                } else {
                                    D_8010AA30_slapdown = 0;
                                }
                                break;
                            }
                        }
                    } else {
                        func_80106290_slapdown(6);
                        D_8010AA74_slapdown = 15;
                    }
                } else {
                    func_80106290_slapdown(6);
                    D_8010AA74_slapdown = 15;
                }
            }
            break;
        case 6:
            if (D_8010AA76_slapdown == 3) {
                if (D_8010AA74_slapdown < 0) {
                    func_80106290_slapdown(7);
                    GMesCreate(0x12);
                    HuAudSeqFadeOut(120);
                    func_801096E4_slapdown();
                    func_801099C0_slapdown();
                    D_8010AA74_slapdown = -15;
                } else {
                    D_8010AA74_slapdown--;
                }
            }
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (D_8010AA74_slapdown >= 0) {
                    func_80106290_slapdown(8);
                    if (D_8010AAA0_slapdown < 4) {
                        D_8010AA74_slapdown = 98;
                    } else {
                        D_8010AA74_slapdown = 132;
                    }
                } else {
                    D_8010AA74_slapdown++;
                }
            }
            break;
        case 8:
            if (D_8010AAA0_slapdown >= 4) {
                if (D_8010AA74_slapdown == 132) {
                    HuAudSeqPlay(0x6B);
                }
            } else {
                if (D_8010AA74_slapdown == 98) {
                    HuAudSeqPlay(0x65);
                }
            }
            if (D_8010AA74_slapdown > 0) {
                D_8010AA74_slapdown--;
            } else {
                D_8010AA74_slapdown = 0;
                func_80106290_slapdown(9);
            }
            break;
        case 9:
            if (D_8010AA74_slapdown == 0) {
                WipeCreateOut(0, 20);
                obj->func = func_80109E58_slapdown;
                D_8010AA74_slapdown++;
            }
            break;
    }
}

void func_8010A2B8_slapdown(omObjData *obj) {
    s16 i;

    WipeCreateIn(0xFF, 16);
    func_80109D54_slapdown();
    func_801066A4_slapdown();
    func_80108340_slapdown();
    func_80108E44_slapdown();
    func_80107DCC_slapdown();
    func_80109640_slapdown();
    D_8010AA74_slapdown = 0;
    D_8010AA6E_slapdown = 0;
    D_8010AA50_slapdown = 0;
    D_8010AA70_slapdown = 0;
    D_8010AA10_slapdown = 0;
    D_8010AA30_slapdown = 0;
    D_8010AA72_slapdown = 0;
    D_8010AAA0_slapdown = 0;
    D_8010AA9A_slapdown = 0;
    D_8010AA32_slapdown = 0;
    D_8010AA98_slapdown = 0;
    D_8010AA4C_slapdown = 0;
    D_8010AA6C_slapdown = 0;
    D_8010AA14_slapdown = -1;
    for (i = 0; i < 4; i++) {
        D_8010AA16_slapdown[i] = -1;
    }
    D_8010AA76_slapdown = 0;
    obj->func = func_80109EE8_slapdown;
}

void func_8010A3D8_slapdown(void) {
}

void func_8010A3E0_slapdown(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010A88C_slapdown[i].scissorX, D_8010A88C_slapdown[i].scissorY,
                   D_8010A88C_slapdown[i].scissorWidth, D_8010A88C_slapdown[i].scissorHeight);
        ViewportSet(i, D_8010A88C_slapdown[i].viewportScale.x, D_8010A88C_slapdown[i].viewportScale.y,
                    D_8010A88C_slapdown[i].viewportScale.z, D_8010A88C_slapdown[i].viewportTranslate.x,
                    D_8010A88C_slapdown[i].viewportTranslate.y, D_8010A88C_slapdown[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010A88C_slapdown[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010A550_slapdown(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010A3E0_slapdown();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, -41.0f, 70.0f, 87.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -41.0f, 70.0f, 87.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -41.0f, 70.0f, 87.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010AA08_slapdown, 0);
    func_80045010_main(D_8010AA08_slapdown, 1);
    omAddObj(1000, 0, 0, -1, func_8010A2B8_slapdown);
    omAddObj(1000, 0, 0, -1, func_80109E90_slapdown);
    func_80105A74_slapdown();
}

const s16 D_8010AA08_slapdown[] = { 0x8260, 0x8261, 0x8262, 0 };
