#include "common.h"
#include "math.h"
#include "overlays/minigame.h"

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
extern s16 D_8010A760_slapdown[][2];
extern s16 D_8010AA30_slapdown;
extern s16 D_8010AA12_slapdown;
extern s16 D_8010AA52_slapdown;
extern void *D_8010AA58_slapdown[5];
extern void *D_8010AA9C_slapdown;
extern const char D_8010A984_slapdown[];
extern s16 D_8010AA72_slapdown;
extern u8 D_8010AA50_slapdown;
extern s16 D_8010AA38_slapdown[10];
extern void *D_8010AA78_slapdown[6];
extern s32 D_8010A888_slapdown;
extern s16 D_8010AA74_slapdown;
extern SlapdownCamera D_8010A88C_slapdown[1];
extern const s16 D_8010AA08_slapdown[];
extern s16 D_8010AA10_slapdown;
extern s16 D_8010AA14_slapdown;
extern s16 D_8010AA16_slapdown[5];
extern s16 D_8010AA32_slapdown;
extern s32 D_8010AA4C_slapdown;
extern s16 D_8010AA6C_slapdown;
extern s16 D_8010AA70_slapdown;
extern s16 D_8010AA76_slapdown;
extern s16 D_8010AA98_slapdown;
extern s16 D_8010AA9A_slapdown;
extern s16 D_8010AAA0_slapdown;

void func_80106600_slapdown(omObjData *obj);
void func_8010924C_slapdown(omObjData *obj);
void func_80106608_slapdown(omObjData *);
void func_8010820C_slapdown(omObjData *);
void func_80107DCC_slapdown(void);
void func_80108BAC_slapdown(omObjData *obj);
void func_80107858_slapdown(omObjData *obj);
void func_80108E44_slapdown(void);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80106900_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80107858_slapdown);

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
    D_8010AA12_slapdown = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010AA58_slapdown[anim], 0, D_8010A984_slapdown);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010A984_slapdown);

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
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010AA78_slapdown[anim], 0, D_8010A984_slapdown);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801084BC_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108BAC_slapdown);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80108FE4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_8010924C_slapdown);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801096E4_slapdown);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_801099C0_slapdown);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", func_80109EE8_slapdown);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2E_slapdown/264B80", D_8010AA08_slapdown);
