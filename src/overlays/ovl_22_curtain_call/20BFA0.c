#include "common.h"
#include "overlays/minigame.h"

// One entry of the 50 entry object table at D_8010B4B0_curtain_call. Layout
// derived from the table clear in func_80105A3C_curtain_call, which walks 50
// entries of 0x84 bytes.
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
} CurtainCallEntry; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} CurtainCallCamera; // sizeof 0x2C

extern CurtainCallEntry D_8010B4B0_curtain_call[50];
// Fields of the first entry of D_8010B4B0_curtain_call are accessed through
// these separate symbols.
extern s16 D_8010B4F0_curtain_call;
extern s16 D_8010B4F2_curtain_call;
extern f32 D_8010B4F4_curtain_call;
extern f32 D_8010B4F8_curtain_call;
extern f32 D_8010B4FC_curtain_call;
extern omObjData *D_8010BA5C_curtain_call;
extern omObjData *D_8010BB64_curtain_call;
extern Process *D_8010CF34_curtain_call;
extern s8 D_8010CEC1_curtain_call;
extern s8 D_8010CE8A_curtain_call[2];
extern s32 D_8010B0C0_curtain_call[8];
extern s16 D_8010B0E0_curtain_call[2];
extern s16 D_8010B0E4_curtain_call[6];
extern u16 D_8010B0F0_curtain_call[][3];
extern char *D_8010B120_curtain_call[];
extern s8 D_8010B180_curtain_call[25];
extern f32 D_8010B19C_curtain_call[25];
extern s16 D_8010B200_curtain_call[];
extern s16 D_8010B208_curtain_call[];
extern s16 D_8010B210_curtain_call[];
extern s16 D_8010B21C_curtain_call[];
extern s8 D_8010B228_curtain_call[];
extern s8 D_8010B22C_curtain_call[];
extern s8 D_8010B234_curtain_call[];
extern u8 D_8010B25C_curtain_call[][3];
extern u8 D_8010B268_curtain_call[][4];
extern u8 D_8010B140_curtain_call[3][5];
extern u8 D_8010B150_curtain_call[3][5];
extern u8 D_8010B160_curtain_call[3][5];
extern u8 D_8010B170_curtain_call[3][5];
extern s16 D_8010CE78_curtain_call[4];
extern s16 D_8010CE88_curtain_call;
extern void *D_8010CE90_curtain_call[4][3];
extern s8 D_8010CEC0_curtain_call;
extern s8 D_8010CEC8_curtain_call[][8];
// Field at offset 1 of an 8 byte per-player table at D_8010CEC8_curtain_call,
// accessed through its own symbol.
extern s8 D_8010CEC9_curtain_call[][8];
// Field at offset 4 of the same table.
extern omObjData *D_8010CECC_curtain_call[][2];
extern s8 D_8010CEF8_curtain_call[4];
extern s8 D_8010CEFE_curtain_call;
extern s8 D_8010CEFF_curtain_call;
extern s16 D_8010CF08_curtain_call[4][2];
extern s8 D_8010CF18_curtain_call[4];
extern s8 D_8010CF20_curtain_call[2];
extern s8 D_8010CF22_curtain_call;
extern omObjData *D_8010CF24_curtain_call;
extern s16 D_8010CF2C_curtain_call[3];
extern s8 D_8010CF32_curtain_call;
extern s8 D_8010CF00_curtain_call;
extern s16 D_8010CEFC_curtain_call;
extern CurtainCallCamera D_8010B280_curtain_call[1];
extern const s16 D_8010B4A0_curtain_call[];
extern s8 D_8010CF38_curtain_call;
extern s16 D_8010CE84_curtain_call;
extern s8 D_8010CE86_curtain_call;
extern s16 D_8010CF1C_curtain_call[2];
extern s8 D_8010CE80_curtain_call[4];
extern s8 D_8010CF01_curtain_call;
extern s8 D_8010CF28_curtain_call[4];
extern s8 D_8010CF33_curtain_call;
extern s16 D_8010B23C_curtain_call[6];
// Columns of a 3 byte per-row table, each accessed through its own symbol.
extern u8 D_8010B248_curtain_call[][3];
extern u8 D_8010B249_curtain_call[][3];
extern u8 D_8010B24A_curtain_call[][3];
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;

void func_801062EC_curtain_call(void);
void func_8010AF78_curtain_call(void);
void func_80106500_curtain_call(omObjData *);
void func_80108F28_curtain_call(omObjData *);
void func_8010A948_curtain_call(omObjData *);
void func_80109AD0_curtain_call(void);
void func_8010954C_curtain_call(void);
void func_801092F0_curtain_call(omObjData *);

void func_801059A0_curtain_call(void) {
    func_8010AF78_curtain_call();
}

f32 func_801059BC_curtain_call(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_curtain_call(void) {
    CurtainCallEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010B4B0_curtain_call; i < 50; i++, entry++) {
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

void func_80105B04_curtain_call(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

s32 func_80105B7C_curtain_call(s32 arg0) {
    return rand8() % arg0;
}

void func_80105BD0_curtain_call(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_80105C3C_curtain_call(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

s8 func_80105CB8_curtain_call(omObjData *obj, f32 target) {
    if (obj->rot.y != target) {
        obj->rot.y = func_801059BC_curtain_call(obj->rot.y, 10.0f);
        return 1;
    }
    return 0;
}

void func_80105D14_curtain_call(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)D_800CDA7C_main[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_curtain_call(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[GwPlayer[0].pad] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_curtain_call(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_curtain_call(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_curtain_call(CRotM[i].y, -1.0f);
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
    if (D_800D5558_main[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

void func_801062EC_curtain_call(void) {
    s16 window = func_80060880_main(175, 92, 10);

    func_80060C14_main(window, 1);
    HuWinInsertMesSet(window, D_8010B0E4_curtain_call[D_8010CE8A_curtain_call[1]], 0);
    HuWinMesSet(window, D_8010B0E0_curtain_call[D_8010CE8A_curtain_call[0]], -1, -1);
    while (HuWinStatGet(window) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if (D_8010CEC1_curtain_call == 4) {
            break;
        }
        HuPrcVSleep();
    }
    func_80060EA8_main(window, 1);
    HuWinExCleanup(window);
    HuWinAllKill();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80106408_curtain_call(void) {
    D_800D6A58_main = 1;
    HuWinInit();
    D_8010CF34_curtain_call = omAddPrcObj(func_801062EC_curtain_call, 0x3F00, 0x800, 0);
}

void func_8010644C_curtain_call(void) {
    if (D_8010CF34_curtain_call != NULL) {
        HuWinAllKill();
        while (omDelPrcObj(D_8010CF34_curtain_call) != 0) {
        }
        D_8010CF34_curtain_call = NULL;
    }
}

void func_80106494_curtain_call(void) {
    D_800D6A58_main = 0;
}

void func_801064A0_curtain_call(omObjData *arg0) {
    switch (D_8010CEC1_curtain_call) {
        case 3:
            func_8001C258_main(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 5:
            func_8001C258_main(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
}

void func_80106500_curtain_call(omObjData *obj) {
    D_8010B4F4_curtain_call = 160.0f;
    D_8010B4F8_curtain_call = 120.0f;
    D_8010B4FC_curtain_call = 45.0f;
    D_8010B4F0_curtain_call = func_8000B838_main(0x430000);
    D_8010B4F2_curtain_call = espEntry(D_8010B4F0_curtain_call, 0, 0);
    espAttrSet(D_8010B4F2_curtain_call, 0x5000);
    espPosSet(D_8010B4F2_curtain_call, D_8010B4F4_curtain_call, D_8010B4F8_curtain_call);
    obj->model[0] = func_8000B108_main(0x430001, 0x299);
    obj->model[1] = func_8000B108_main(0x430002, 0x299);
    obj->model[2] = func_8000B108_main(0x430003, 0x299);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    Hu3DMotionTimeSet(obj->model[0], 60.0f);
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DModelCameraSet(obj->model[0], 1);
    Hu3DModelCameraSet(obj->model[1], 1);
    Hu3DModelCameraSet(obj->model[2], 1);
    obj->func = func_801064A0_curtain_call;
}

void func_80106688_curtain_call(void) {
    D_8010B4B0_curtain_call[0].obj = omAddObj(0x1F4, 4, 2, -1, func_80106500_curtain_call);
}

void func_801066C4_curtain_call(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    Hu3DAnimKill(D_8010CE78_curtain_call[player]);
    D_8010CE78_curtain_call[player] = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010CE90_curtain_call[player][anim], 0, D_8010B120_curtain_call[chr]);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B32C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B338_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B344_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B350_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B35C_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B368_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B374_curtain_call);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B380_curtain_call);

s8 func_801067A8_curtain_call(omObjData *obj, s8 mode) {
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + obj->work[0]];

    switch (mode) {
        case 0:
            if (entry->unk_5C.y == 0.05f) {
                func_8001C258_main(obj->model[2], 4, 0);
                func_8001C258_main(obj->model[3], 4, 0);
            }
            if (entry->unk_5C.y < 1.0f) {
                entry->unk_5C.y += 0.19f;
                break;
            }
            entry->unk_5C.y = 1.0f;
            Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            return 1;
        case 1:
            if (entry->unk_5C.y > 0.05f) {
                entry->unk_5C.y -= 0.19;
                break;
            }
            func_8001C258_main(obj->model[2], 4, 4);
            func_8001C258_main(obj->model[3], 4, 4);
            entry->unk_5C.y = 0.05f;
            Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            return 1;
    }
    Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    return 0;
}

void func_80106988_curtain_call(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + obj->work[0]];
    s8 shift = 0;

    if (entry->unk_06 != motion) {
        switch (motion) {
            case 4:
            case 5:
            case 6:
            case 8:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        func_80105C3C_curtain_call(obj, motion, 0, 10, shift);
        entry->unk_06 = motion;
        if (motion == 4) {
            func_80045ED0_main((D_8010B0C0_curtain_call[chr] << 16) | 0x2F);
        }
    }
}

void func_80106AB4_curtain_call(omObjData *obj) {
    CurtainCallEntry *entry;

    if (D_8010CF32_curtain_call < 5) {
        func_80106988_curtain_call(obj, 3);
        return;
    }
    entry = &D_8010B4B0_curtain_call[1 + obj->work[0]];
    if (entry->unk_04 != 0) {
        func_80106988_curtain_call(obj, 5);
        if (entry->unk_16 == 0) {
            entry->unk_16++;
            func_801066C4_curtain_call(obj, 2);
        }
    } else {
        func_80106988_curtain_call(obj, 4);
        if (entry->unk_16 == 0) {
            entry->unk_16++;
            func_801066C4_curtain_call(obj, 1);
        }
    }
}

void func_80106B78_curtain_call(omObjData *obj) {
    if ((D_8010CE88_curtain_call & 0xF) == 0) {
        switch (func_80105B7C_curtain_call(3)) {
            case 0:
                D_800CBB6E_main[obj->work[3]] = 0;
                break;
            case 1:
                D_800CBB6E_main[obj->work[3]] = 10;
                break;
            case 2:
                D_800CBB6E_main[obj->work[3]] = -10;
                break;
        }
    }
}

void func_80106C18_curtain_call(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + player];
    s8 roll;
    s8 level;

    if (obj->work[1] == 0) {
        return;
    }
    func_80105B04_curtain_call(player);
    switch (D_8010CEC1_curtain_call) {
        case 0:
            roll = func_80105B7C_curtain_call(100);
            level = D_8010CEFE_curtain_call;
            switch (D_8010CEF8_curtain_call[player]) {
                case 0:
                    if (roll < D_8010B140_curtain_call[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < D_8010B140_curtain_call[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < D_8010B140_curtain_call[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < D_8010B140_curtain_call[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < D_8010B140_curtain_call[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 1:
                    if (roll < D_8010B150_curtain_call[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < D_8010B150_curtain_call[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < D_8010B150_curtain_call[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < D_8010B150_curtain_call[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < D_8010B150_curtain_call[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 2:
                    if (roll < D_8010B160_curtain_call[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < D_8010B160_curtain_call[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < D_8010B160_curtain_call[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < D_8010B160_curtain_call[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < D_8010B160_curtain_call[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 3:
                    if (roll < D_8010B170_curtain_call[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < D_8010B170_curtain_call[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < D_8010B170_curtain_call[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < D_8010B170_curtain_call[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < D_8010B170_curtain_call[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
            }
            switch (entry->unk_0E) {
                case 1:
                case 2:
                    D_8010CF08_curtain_call[player][0] = 230 - func_80105B7C_curtain_call(70);
                    D_8010CF08_curtain_call[player][1] = func_80105B7C_curtain_call(20) + 20;
                    break;
                case 3:
                case 4:
                    D_8010CF08_curtain_call[player][0] = func_80105B7C_curtain_call(20) + 20;
                    break;
                case 5:
                case 6:
                    D_8010CF08_curtain_call[player][0] = 120 - func_80105B7C_curtain_call(60);
                    break;
            }
            entry->unk_10 = func_80105B7C_curtain_call(2);
            entry->unk_0C = func_80105B7C_curtain_call(3);
            break;
        case 3:
            switch (entry->unk_0E) {
                case 1:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player][0]) {
                        entry->unk_0A = 2;
                        func_8004AC98_main(0x417, obj->work[0]);
                    } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player][1]) {
                        if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                            entry->unk_0A = 4;
                            func_8004AC98_main(0x418, obj->work[0]);
                        }
                    } else if (D_8010CE88_curtain_call < D_8010CF08_curtain_call[player][1]) {
                        if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                            if (entry->unk_10 != 0) {
                                D_800CBB6E_main[pad] = 10;
                            } else {
                                D_800CBB6E_main[pad] = -10;
                            }
                        }
                    }
                    break;
                case 2:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player][0]) {
                        entry->unk_0A = 2;
                        func_8004AC98_main(0x417, obj->work[0]);
                    } else if (D_8010CE88_curtain_call == D_8010CF08_curtain_call[player][1]) {
                        entry->unk_0A = 4;
                        func_8004AC98_main(0x418, obj->work[0]);
                    } else if (D_8010CE88_curtain_call < D_8010CF08_curtain_call[player][1]) {
                        if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                            if (entry->unk_10 != 0) {
                                D_800CBB6E_main[pad] = 10;
                            } else {
                                D_800CBB6E_main[pad] = -10;
                            }
                        }
                    }
                    break;
                case 3:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CF18_curtain_call[player] != D_8010CEFF_curtain_call) {
                        if (entry->unk_10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    }
                    break;
                case 4:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                        if (entry->unk_10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    }
                    break;
                case 5:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                        if (entry->unk_0C == 0) {
                            entry->unk_0A = 2;
                            func_8004AC98_main(0x417, obj->work[0]);
                            entry->unk_0C = 1;
                        }
                    } else {
                        if (entry->unk_10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    }
                    break;
                case 6:
                    if (D_8010CE88_curtain_call > D_8010CF08_curtain_call[player][0]) {
                        func_80106B78_curtain_call(obj);
                    } else if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                        if (entry->unk_10 != 0) {
                            D_800CBB6E_main[pad] = 10;
                        } else {
                            D_800CBB6E_main[pad] = -10;
                        }
                    } else {
                        if (entry->unk_0C == 0) {
                            entry->unk_0A = 2;
                            func_8004AC98_main(0x417, obj->work[0]);
                            entry->unk_0C = 1;
                        }
                    }
                    break;
            }
            break;
    }
}

void func_80107560_curtain_call(omObjData *obj) {
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + obj->work[0]];
    CurtainCallEntry *other = &D_8010B4B0_curtain_call[1 + D_8010CF20_curtain_call[0]];

    if (entry->unk_14 != 1000 && D_8010CF22_curtain_call >= 2 && D_8010CEFE_curtain_call < 2) {
        if (D_8010CF20_curtain_call[0] == obj->work[0] || D_8010CF20_curtain_call[1] == D_8010CEFE_curtain_call) {
            func_80106988_curtain_call(obj, 7);
            entry->unk_14 = 1000;
        } else if (Hu3DData[other->obj->model[0]].motTime == 0.0f && entry->unk_06 != 7) {
            func_80105BD0_curtain_call(obj, 7, 2);
            entry->unk_06 = 7;
            entry->unk_14 = 1000;
        }
    }
}

void func_80107680_curtain_call(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + player];

    if (D_8010CF32_curtain_call != 2) {
        if (D_8010CF32_curtain_call > 2) {
            obj->func = func_80106AB4_curtain_call;
        }
        return;
    }
    if (entry->unk_04 != 0) {
        func_80107560_curtain_call(obj);
        return;
    }
    func_80106C18_curtain_call(obj);
    switch (D_8010CEC1_curtain_call) {
        case 0:
            func_80106988_curtain_call(obj, 0);
            break;
        case 1:
            break;
        case 3:
            if (entry->unk_0A == 1) {
                if (entry->unk_08 <= 0) {
                    if (D_800CBB6E_main[pad] < -5) {
                        if ((s32)entry->unk_44.x == -180) {
                            entry->unk_44.x = 0.0f;
                        }
                        entry->unk_08 = 1;
                        D_8010CF18_curtain_call[player] = (D_8010CF18_curtain_call[player] + 1) % 3;
                    }
                }
                if (entry->unk_08 >= 0) {
                    if (D_800CBB6E_main[pad] > 5) {
                        if ((s32)entry->unk_44.x == 0) {
                            entry->unk_44.x = -180.0f;
                        }
                        entry->unk_08 = -1;
                        D_8010CF18_curtain_call[player] = D_8010CF18_curtain_call[player] != 0 ? D_8010CF18_curtain_call[player] - 1 : 2;
                    }
                }
            }
        case 2:
            if (func_80105CB8_curtain_call(obj, 0.0f)) {
                func_80106988_curtain_call(obj, 2);
            } else if (entry->unk_06 != 3) {
                func_80106988_curtain_call(obj, 1);
            }
            break;
        case 4:
        case 5:
            if (func_80105CB8_curtain_call(obj, 180.0f)) {
                func_80106988_curtain_call(obj, 2);
            } else {
                func_80106988_curtain_call(obj, 3);
            }
            D_8010CF22_curtain_call = 0;
            entry->unk_12 = 0;
            break;
        case 6:
            if (entry->unk_12 < 30) {
                func_80105CB8_curtain_call(obj, 0.0f);
                func_80106988_curtain_call(obj, 2);
            } else if (entry->unk_12 == 30) {
                if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    func_80106988_curtain_call(obj, 6);
                    D_8010CF22_curtain_call++;
                } else {
                    func_80106988_curtain_call(obj, 8);
                    if (entry->unk_16 == 0) {
                        entry->unk_16++;
                        PlayerFXPlay(0x286, obj->work[0]);
                    }
                }
            } else if (entry->unk_12 > 70) {
                if (D_8010CF18_curtain_call[player] == D_8010CEFF_curtain_call) {
                    if (D_8010CF22_curtain_call == 1) {
                        func_80106988_curtain_call(obj, 3);
                    } else if (D_8010CEFE_curtain_call == 2) {
                        func_80106988_curtain_call(obj, 3);
                    } else if (func_80105CB8_curtain_call(obj, 180.0f)) {
                        func_80106988_curtain_call(obj, 2);
                    } else {
                        func_80106988_curtain_call(obj, 3);
                    }
                } else {
                    entry->unk_04 = 1;
                    if (D_8010CF20_curtain_call[0] < 0) {
                        D_8010CF20_curtain_call[0] = player;
                        D_8010CF20_curtain_call[1] = D_8010CEFE_curtain_call;
                    } else {
                        func_80106988_curtain_call(obj, 3);
                    }
                }
            }
            entry->unk_12++;
            break;
    }
    if (entry->unk_08 > 0) {
        entry->unk_44.x -= 4.0f;
        if ((s32)entry->unk_44.x % 60 == 0) {
            entry->unk_08 = 0;
        }
    }
    if (entry->unk_08 < 0) {
        entry->unk_44.x += 4.0f;
        if ((s32)entry->unk_44.x % 60 == 0) {
            entry->unk_08 = 0;
        }
    }
    Hu3DModelPosSet(obj->model[3], obj->trans.x + entry->unk_44.x, entry->unk_44.y, obj->trans.z);
    switch (D_8010CEC1_curtain_call) {
        case 0:
            entry->unk_44.x = 0.0f;
            D_8010CF18_curtain_call[player] = 0;
            entry->unk_0A = 0;
            entry->unk_14 = 0;
            break;
        case 3:
            switch (entry->unk_0A) {
                case 0:
                    if (func_801067A8_curtain_call(obj, 0)) {
                        entry->unk_0A = 1;
                    }
                    break;
                case 1:
                    if ((s32)entry->unk_44.x % 60 == 0 && (D_800D5558_main[pad] & 0x8000)) {
                        func_8004AC98_main(0x417, obj->work[0]);
                        entry->unk_0A = 2;
                    }
                    break;
                case 2:
                    if (func_801067A8_curtain_call(obj, 1)) {
                        entry->unk_0A = 3;
                        func_80106988_curtain_call(obj, 3);
                    }
                    break;
                case 3:
                    if (D_800D5558_main[pad] & 0x4000) {
                        func_8004AC98_main(0x418, obj->work[0]);
                        entry->unk_0A = 4;
                    }
                    break;
                case 4:
                    if (func_801067A8_curtain_call(obj, 0)) {
                        entry->unk_0A = 1;
                        func_80106988_curtain_call(obj, 1);
                    }
                    break;
            }
            break;
        case 4:
            if (func_801067A8_curtain_call(obj, 0)) {
                entry->unk_0A = 1;
            }
            break;
        case 6:
            if (func_801067A8_curtain_call(obj, 1)) {
                entry->unk_0A = 0;
            }
            break;
    }
}

void func_80107D20_curtain_call(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[1 + player];
    u16 chr = GwPlayer[player].chr;
    s32 dir = D_800A178C_main[chr][0];
    s8 i;

    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][3], 0x2A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x63));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x3A));
    for (i = 0; i < 3; i++) {
        D_8010CE90_curtain_call[player][i] = DataRead(dir | D_8010B0F0_curtain_call[chr][i]);
    }
    D_8010CE78_curtain_call[player] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010CE90_curtain_call[player][0], 0, D_8010B120_curtain_call[chr]);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    if (obj->work[0] == 0) {
        obj->model[1] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[1]);
        func_8001C514_main(obj->model[1]);
        func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        obj->model[2] = func_8000B108_main(0x430004, 0x288);
        Hu3DModelRemakeStatic(obj->model[2]);
        func_8001C514_main(obj->model[2]);
        obj->model[3] = func_8000B108_main(0x430005, 0x288);
        func_8001C2FC_main(obj->model[3], 0x80000000, 0x80000000);
        Hu3DModelRemakeStatic(obj->model[3]);
        func_8001C514_main(obj->model[3]);
        D_8010CF2C_curtain_call[0] = obj->model[1];
        D_8010CF2C_curtain_call[1] = obj->model[2];
        D_8010CF2C_curtain_call[2] = obj->model[3];
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
        obj->model[2] = Hu3DModelLink(D_8010CF2C_curtain_call[1]);
        obj->model[3] = Hu3DModelLink(D_8010CF2C_curtain_call[2]);
    }
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DMotionTimeSet(obj->model[2], func_80105B7C_curtain_call(50));
    switch (obj->work[1]) {
        case 0:
            obj->trans.x = -225.0f;
            obj->trans.z = 0.0f;
            obj->trans.y = 3.0f;
            break;
        case 1:
            obj->trans.x = -75.0f;
            obj->trans.z = 10.0f;
            obj->trans.y = 5.0f;
            break;
        case 2:
            obj->trans.x = 75.0f;
            obj->trans.z = 0.0f;
            obj->trans.y = 3.0f;
            break;
        case 3:
            obj->trans.x = 225.0f;
            obj->trans.z = 10.0f;
            obj->trans.y = 5.0f;
            break;
    }
    entry->unk_44.y = obj->trans.y + 160.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, entry->unk_44.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, entry->unk_44.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    entry->unk_5C.x = 1.0f;
    entry->unk_5C.y = 0.05f;
    entry->unk_5C.z = 1.0f;
    Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_80105BD0_curtain_call(obj, 3, 2);
    entry->unk_06 = 3;
    D_8010CF18_curtain_call[player] = 0;
    D_8010CF20_curtain_call[0] = -1;
    D_8010CF20_curtain_call[1] = -1;
    Hu3DModelCameraSet(obj->model[0], 1);
    Hu3DModelCameraSet(obj->model[1], 1);
    Hu3DModelCameraSet(obj->model[2], 1);
    Hu3DModelCameraSet(obj->model[3], 1);
    obj->work[1] = GwPlayer[player].stat & 1;
    D_8010CEF8_curtain_call[player] = GwPlayer[player].cpu_difficulty;
    obj->work[3] = GwPlayer[player].pad;
    obj->func = func_80107680_curtain_call;
}

void func_801084A0_curtain_call(void) {
    CurtainCallEntry *entry;
    omObjData *obj;
    s8 slots[4];
    s8 avail[4];
    u16 player = 0;
    s8 pick;
    s8 i;
    s8 j;
    s8 k;

    for (i = 0; i < 4; i++) {
        slots[i] = i;
        avail[i] = 1;
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
        }
        entry = &D_8010B4B0_curtain_call[1 + i];
        obj = omAddObj(0x2BC, 5, 10, -1, func_80107D20_curtain_call);
        obj->work[0] = player;
        entry->obj = obj;
        pick = func_80105B7C_curtain_call(4 - i);
        obj->work[1] = slots[pick];
        avail[slots[pick]] = 0;
        for (j = 0, k = 0; j < 4; j++) {
            if (avail[j]) {
                slots[k] = j;
                k++;
            }
        }
    }
}

void func_80108670_curtain_call(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[5 + player];

    if (D_8010CF32_curtain_call < 2) {
        return;
    }
    switch (D_8010CEC1_curtain_call) {
        case 0:
            entry->unk_04 = 0;
            entry->unk_16 = 0;
            if (player >= 4) {
                obj->trans.y = 190.0f;
            } else {
                obj->trans.y = 125.0f;
            }
            entry->unk_5C.x = entry->unk_5C.z = 1.0f;
            break;
        case 1:
            if (omPauseChk() + D_800D6A90_main != 0) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
            } else {
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
        case 2:
            func_8001C258_main(obj->model[0], 4, 4);
            func_8001C258_main(obj->model[1], 4, 4);
            break;
        case 6:
            if (D_8010CEC0_curtain_call == D_8010CEC9_curtain_call[player][0]) {
                if (D_8010CF32_curtain_call < 3 || (D_8010CF32_curtain_call == 3 && entry->unk_04 != 0)) {
                    obj->trans.y += D_8010B180_curtain_call[entry->unk_04];
                    entry->unk_5C.x = entry->unk_5C.z = D_8010B19C_curtain_call[entry->unk_04];
                    entry->unk_04 = (entry->unk_04 + 1) % 25;
                    if (entry->unk_16 == 0) {
                        entry->unk_16++;
                        HuAudFXPlay(D_8010B200_curtain_call[D_8010CEFF_curtain_call]);
                    }
                }
            }
            /* fallthrough */
        case 4:
        case 5:
            if (omPauseChk() + D_800D6A90_main != 0) {
                func_8001C258_main(obj->model[0], 4, 4);
                func_8001C258_main(obj->model[1], 4, 4);
            } else {
                func_8001C258_main(obj->model[0], 4, 0);
                func_8001C258_main(obj->model[1], 4, 0);
            }
            break;
    }
    if (D_8010CF32_curtain_call >= 4) {
        if (entry->unk_06 > 0) {
            entry->unk_06--;
        } else {
            obj->trans.y += D_8010B180_curtain_call[entry->unk_04];
            entry->unk_5C.x = entry->unk_5C.z = D_8010B19C_curtain_call[entry->unk_04];
            entry->unk_04 = (entry->unk_04 + 1) % 25;
        }
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
}

void func_801089FC_curtain_call(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[5 + player];

    switch (player) {
        case 0:
            obj->model[0] = func_8000B108_main(0xA008E, 0x2B9);
            func_8000B460_main(obj, 0, 0xA0097);
            func_8000B460_main(obj, 1, 0xA0098);
            func_8000B460_main(obj, 2, 0xA0099);
            obj->work[1] = 0;
            D_8010CF2C_curtain_call[0] = obj->model[0];
            D_8010CF24_curtain_call = obj;
            break;
        case 1:
            obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
            obj->work[1] = 0;
            obj->motion[0] = D_8010CF24_curtain_call->motion[0];
            obj->motion[1] = D_8010CF24_curtain_call->motion[1];
            obj->motion[2] = D_8010CF24_curtain_call->motion[2];
            break;
        case 2:
            obj->model[0] = func_8000B108_main(0xA00A5, 0x2B9);
            func_8000B460_main(obj, 0, 0xA00A8);
            func_8000B460_main(obj, 1, 0xA00A9);
            func_8000B460_main(obj, 2, 0xA00AA);
            obj->work[1] = 1;
            D_8010CF2C_curtain_call[0] = obj->model[0];
            D_8010CF24_curtain_call = obj;
            break;
        case 3:
            obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
            obj->work[1] = 1;
            obj->motion[0] = D_8010CF24_curtain_call->motion[0];
            obj->motion[1] = D_8010CF24_curtain_call->motion[1];
            obj->motion[2] = D_8010CF24_curtain_call->motion[2];
            break;
        case 4:
            obj->model[0] = func_8000B108_main(0xA00C5, 0x2B9);
            func_8000B460_main(obj, 0, 0xA00CB);
            func_8000B460_main(obj, 1, 0xA00CC);
            func_8000B460_main(obj, 2, 0xA00CD);
            obj->work[1] = 2;
            D_8010CF2C_curtain_call[0] = obj->model[0];
            D_8010CF24_curtain_call = obj;
            break;
        case 5:
            obj->model[0] = Hu3DModelLink(D_8010CF2C_curtain_call[0]);
            obj->work[1] = 2;
            obj->motion[0] = D_8010CF24_curtain_call->motion[0];
            obj->motion[1] = D_8010CF24_curtain_call->motion[1];
            obj->motion[2] = D_8010CF24_curtain_call->motion[2];
            break;
    }
    func_80105BD0_curtain_call(obj, 0, 2);
    if (obj->work[0] == 0) {
        obj->model[1] = func_8000B0A0_main(0, 0xC9);
        func_8001C2FC_main(obj->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[1]);
        func_8001C514_main(obj->model[1]);
        func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        D_8010CF2C_curtain_call[1] = obj->model[1];
    } else {
        obj->model[1] = Hu3DModelLink(D_8010CF2C_curtain_call[1]);
    }
    obj->trans.x = -1500.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
    if (player >= 0 && player < 2) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (player >= 2 && player < 4) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (player >= 4 && player < 6) {
        obj->scale.x = obj->scale.y = obj->scale.z = 0.52f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    entry->unk_5C.x = entry->unk_5C.z = 1.0f;
    Hu3DModelCameraSet(obj->model[0], 1);
    Hu3DModelCameraSet(obj->model[1], 1);
    obj->func = func_80108670_curtain_call;
}

void func_80108E64_curtain_call(void) {
    omObjData *obj;
    s16 i;

    for (i = 0; i < 6; i++) {
        obj = omAddObj(0x320, 3, 4, -1, func_801089FC_curtain_call);
        D_8010CECC_curtain_call[i][0] = obj;
        obj->work[0] = i;
        D_8010B4B0_curtain_call[5].obj = obj;
        omSetStatBit(obj, 0xA0);
    }
}

void func_80108EF8_curtain_call(omObjData *obj) {
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 127.0f, obj->trans.z);
}

void func_80108F28_curtain_call(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0xA0000, 0x2B9);
    func_8000B460_main(obj, 0, 0xA000C);
    func_80105BD0_curtain_call(obj, 0, 2);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    obj->trans.x = -450.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -350.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C258_main(obj->model[0], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    Hu3DModelCameraSet(obj->model[0], 1);
    Hu3DModelCameraSet(obj->model[1], 1);
    obj->func = func_80108EF8_curtain_call;
}

void func_801090FC_curtain_call(void) {
    D_8010BA5C_curtain_call = omAddObj(0x258, 3, 2, -1, func_80108F28_curtain_call);
}

void func_80109138_curtain_call(omObjData *obj) {
    CurtainCallEntry *entry = &D_8010B4B0_curtain_call[13];

    switch (D_8010CEC1_curtain_call) {
        case 0:
            func_8001C258_main(obj->model[0], 4, 4);
            break;
        case 5:
            switch (D_8010CEFE_curtain_call) {
                case 0:
                    obj->trans.x = (f32)D_8010B208_curtain_call[D_8010CEC0_curtain_call] +
                                   D_8010B228_curtain_call[D_8010CEC0_curtain_call];
                    break;
                case 1:
                    obj->trans.x = (f32)D_8010B210_curtain_call[D_8010CEC0_curtain_call] +
                                   D_8010B22C_curtain_call[D_8010CEC0_curtain_call];
                    break;
                case 2:
                    obj->trans.x = (f32)D_8010B21C_curtain_call[D_8010CEC0_curtain_call] +
                                   D_8010B234_curtain_call[D_8010CEC0_curtain_call];
                    break;
            }
            func_8001C258_main(obj->model[0], 4, 0);
            break;
    }
    if (D_8010CF32_curtain_call >= 3) {
        if (entry->unk_04 <= 0) {
            entry->unk_04 = 0;
            func_8001C258_main(obj->model[0], 4, 4);
        } else {
            entry->unk_04 -= 5;
            func_8001F9E4_main(obj->model[0], entry->unk_04);
        }
    }
}

void func_801092F0_curtain_call(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x430006, 0x2A8);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0xD2);
    obj->trans.x = 0.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010B4B0_curtain_call[13].unk_04 = 0xFF;
    func_8001C258_main(obj->model[0], 4, 4);
    Hu3DModelCameraSet(obj->model[0], 1);
    obj->func = func_80109138_curtain_call;
}

void func_801093C4_curtain_call(void) {
    D_8010BB64_curtain_call = omAddObj(0x384, 1, 1, -1, func_801092F0_curtain_call);
}

void func_80109400_curtain_call(void) {
    s8 i;
    s8 frame = D_8010CF38_curtain_call;

    for (i = 0; i < 6; i++) {
        switch (frame) {
            case 0:
                func_80105C3C_curtain_call(D_8010CECC_curtain_call[i][0], 1, 0, 5, 2);
                break;
            case 25:
                func_80105C3C_curtain_call(D_8010CECC_curtain_call[i][0], 2, 0, 5, 2);
                break;
            case 50:
                func_80105C3C_curtain_call(D_8010CECC_curtain_call[i][0], 0, 0, 5, 2);
                break;
        }
    }
    if (frame == 50) {
        D_8010CE84_curtain_call++;
        D_8010CF38_curtain_call = 0;
    } else {
        D_8010CF38_curtain_call++;
    }
}

#ifdef NON_MATCHING
// Register allocation differs: the original keeps speed in a0 and shares a1
// between the D_8010CF1C_curtain_call address, frame and i; GCC swaps them.
void func_8010954C_curtain_call(void) {
    s16 frame;
    s8 speed = 0;
    s8 i;

    if (D_8010CE84_curtain_call == D_8010CF1C_curtain_call[0] || D_8010CE84_curtain_call == D_8010CF1C_curtain_call[1]) {
        func_80109400_curtain_call();
        return;
    }
    D_8010CE84_curtain_call++;
    frame = D_8010CE84_curtain_call;
    switch (D_8010CEFE_curtain_call) {
        case 0:
            speed = 6;
            break;
        case 1:
            if (frame < 60) {
                speed = 6;
            } else if (frame < 105) {
                speed = D_8010B25C_curtain_call[D_8010CE86_curtain_call][0];
            } else if (frame < 150) {
                speed = 6;
            } else if (frame < 195) {
                speed = D_8010B25C_curtain_call[D_8010CE86_curtain_call][1];
            } else if (frame < 240) {
                speed = 6;
            } else if (frame < 285) {
                speed = D_8010B25C_curtain_call[D_8010CE86_curtain_call][2];
            }
            break;
        case 2:
            if (frame < 60) {
                speed = 6;
            } else if (frame < 105) {
                speed = D_8010B268_curtain_call[D_8010CE86_curtain_call][0];
            } else if (frame < 150) {
                speed = 6;
            } else if (frame < 195) {
                speed = D_8010B268_curtain_call[D_8010CE86_curtain_call][1];
            } else if (frame < 240) {
                speed = D_8010B268_curtain_call[D_8010CE86_curtain_call][2];
            } else if (frame < 285) {
                speed = 6;
            } else if (frame < 330) {
                speed = D_8010B268_curtain_call[D_8010CE86_curtain_call][3];
            }
            break;
    }
    for (i = 0; i < 6; i++) {
        if (D_8010CEC8_curtain_call[i][0] != 0) {
            D_8010CECC_curtain_call[i][0]->trans.x += speed;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", func_8010954C_curtain_call);
#endif

void func_8010982C_curtain_call(void) {
    CurtainCallEntry *entry;
    s8 i;
    s8 count;

    D_8010CF01_curtain_call = 0;
    for (i = 0; i < 4; i++) {
        D_8010CE80_curtain_call[i] = 0;
    }
    for (i = 0, count = 0; i < 4; i++) {
        entry = &D_8010B4B0_curtain_call[1 + i];
        if (entry->unk_04 == 0) {
            D_8010CE80_curtain_call[count] = GwPlayer[entry->obj->work[0]].chr;
            D_8010CF28_curtain_call[count] = entry->obj->work[0];
            count++;
        } else {
            D_8010CF01_curtain_call++;
        }
    }
}

void func_80109920_curtain_call(void) {
    s8 slots[6];
    s8 pick;
    s8 i;

    for (i = 0; i < 6; i++) {
        slots[D_8010CEC9_curtain_call[i][0]] = D_8010CECC_curtain_call[i][0]->work[1];
    }
    switch (D_8010CEFE_curtain_call) {
        case 0:
            pick = func_80105B7C_curtain_call(3);
            D_8010CEFF_curtain_call = slots[pick];
            D_8010CEC0_curtain_call = pick;
            D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
            if (D_8010CE8A_curtain_call[0] != 0) {
                D_8010CE8A_curtain_call[1] = pick;
            } else {
                D_8010CE8A_curtain_call[1] = 2 - pick;
            }
            break;
        case 1:
            pick = func_80105B7C_curtain_call(5);
            D_8010CEFF_curtain_call = slots[pick];
            D_8010CEC0_curtain_call = pick;
            D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
            if (D_8010CE8A_curtain_call[0] != 0) {
                D_8010CE8A_curtain_call[1] = pick;
            } else {
                D_8010CE8A_curtain_call[1] = 4 - pick;
            }
            break;
        case 2:
            pick = func_80105B7C_curtain_call(6);
            D_8010CEFF_curtain_call = slots[pick];
            D_8010CEC0_curtain_call = pick;
            D_8010CE8A_curtain_call[0] = func_80105B7C_curtain_call(2);
            if (D_8010CE8A_curtain_call[0] != 0) {
                D_8010CE8A_curtain_call[1] = pick;
            } else {
                D_8010CE8A_curtain_call[1] = 5 - pick;
            }
            break;
    }
}

void func_80109AD0_curtain_call(void) {
    CurtainCallEntry *entry = D_8010B4B0_curtain_call;
    omObjData *host = entry->obj;
    omObjData *curtain = D_8010B4B0_curtain_call[11].obj;
    s8 order[6];
    s8 avail[6];
    s8 pick;
    s8 count;
    s8 i;
    s8 j;

    switch (D_8010CEC1_curtain_call) {
        case 0:
            switch (D_8010CEFE_curtain_call) {
                case 0:
                    D_8010CEC8_curtain_call[0][0] = D_8010CEC8_curtain_call[2][0] = D_8010CEC8_curtain_call[4][0] = 1;
                    D_8010CEC8_curtain_call[1][0] = D_8010CEC8_curtain_call[3][0] = D_8010CEC8_curtain_call[5][0] = 0;
                    pick = func_80105B7C_curtain_call(6);
                    D_8010CEC8_curtain_call[0][1] = D_8010B248_curtain_call[pick][0];
                    D_8010CEC8_curtain_call[2][1] = D_8010B249_curtain_call[pick][0];
                    D_8010CEC8_curtain_call[4][1] = D_8010B24A_curtain_call[pick][0];
                    D_8010CEC8_curtain_call[1][1] = 3;
                    D_8010CEC8_curtain_call[3][1] = 4;
                    D_8010CEC8_curtain_call[5][1] = 5;
                    break;
                case 1:
                case 2:
                    for (i = 0; i < 6; i++) {
                        order[i] = i;
                        avail[i] = TRUE;
                    }
                    for (i = 0; i < 6; i++) {
                        pick = func_80105B7C_curtain_call(6 - i);
                        D_8010CEC9_curtain_call[i][0] = order[pick];
                        avail[order[pick]] = FALSE;
                        for (j = 0, count = 0; j < 6; j++) {
                            if (avail[j] != 0) {
                                order[count] = j;
                                count++;
                            }
                        }
                    }
                    for (i = 0; i < 6; i++) {
                        D_8010CEC8_curtain_call[i][0] = 1;
                        if (D_8010CEFE_curtain_call == 1 && D_8010CEC9_curtain_call[i][0] == 5) {
                            D_8010CEC8_curtain_call[i][0] = 0;
                        }
                    }
                    break;
            }
            switch (D_8010CEFE_curtain_call) {
                case 0:
                    D_8010CF1C_curtain_call[0] = 108;
                    D_8010CF1C_curtain_call[1] = 1000;
                    break;
                case 1:
                    D_8010CF1C_curtain_call[0] = func_80105B7C_curtain_call(75) + 60;
                    D_8010CF1C_curtain_call[1] = func_80105B7C_curtain_call(105) + 135;
                    D_8010CE86_curtain_call = func_80105B7C_curtain_call(3);
                    break;
                case 2:
                    D_8010CF1C_curtain_call[0] = func_80105B7C_curtain_call(105) + 60;
                    D_8010CF1C_curtain_call[1] = func_80105B7C_curtain_call(135) + 165;
                    D_8010CE86_curtain_call = func_80105B7C_curtain_call(6);
                    break;
            }
            for (i = 0; i < 6; i++) {
                if (D_8010CEC8_curtain_call[i][0] != 0) {
                    D_8010CECC_curtain_call[i][0]->trans.x = D_8010B23C_curtain_call[D_8010CEC9_curtain_call[i][0]];
                } else {
                    D_8010CECC_curtain_call[i][0]->trans.x = -1500.0f;
                }
            }
            D_8010CF38_curtain_call = 0;
            D_8010CE84_curtain_call = 0;
            Hu3DMotionSpeedSet(host->model[0], -1.0f);
            for (i = 0; i < 6; i++) {
                switch (D_8010CEFE_curtain_call) {
                    case 0:
                        if (D_8010CEC9_curtain_call[i][0] == 2) {
                            D_8010CF33_curtain_call = i;
                        }
                        break;
                    case 1:
                        if (D_8010CEC9_curtain_call[i][0] == 4) {
                            D_8010CF33_curtain_call = i;
                        }
                        break;
                    case 2:
                        if (D_8010CEC9_curtain_call[i][0] == 5) {
                            D_8010CF33_curtain_call = i;
                        }
                        break;
                }
            }
            func_80109920_curtain_call();
            D_8010CEC1_curtain_call = 1;
            break;
        case 1:
            if ((s32)Hu3DData[host->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(host->model[0], 0.0f);
                Hu3DMotionSpeedSet(host->model[0], 0.0f);
                func_8001C258_main(host->model[0], 4, 4);
            }
            func_8010954C_curtain_call();
            if (D_8010CECC_curtain_call[D_8010CF33_curtain_call][0]->trans.x >= 500.0f) {
                D_8010CEC1_curtain_call = 2;
                func_8001C258_main(host->model[0], 4, 0);
                func_8001C258_main(curtain->model[0], 4, 0);
                func_8001C258_main(curtain->model[1], 4, 0);
            }
            break;
        case 2:
            Hu3DMotionSpeedSet(host->model[0], 1.0f);
            if (curtain->trans.x < 0.0f) {
                curtain->trans.x += 7.0f;
            } else {
                curtain->trans.x = 0.0f;
                HuAudFXPlay(0x298);
                GMesCreate(0x1A, 10, 160, 28);
                D_8010CE88_curtain_call = 301;
                func_80106408_curtain_call();
                HuAudFXPlay(0x414);
                D_8010CEC1_curtain_call = 3;
            }
            break;
        case 3:
            if (D_8010CE88_curtain_call > 0) {
                D_8010CE88_curtain_call--;
                func_8003F578_main((D_8010CE88_curtain_call + 29) / 30);
            } else {
                func_8003F5C0_main();
                func_8004AD8C_main(0x414);
                D_8010CEC1_curtain_call = 4;
            }
            break;
        case 4:
            if (curtain->trans.x > -450.0f) {
                curtain->trans.x -= 7.0f;
                if (curtain->trans.x < -300.0f && D_8010CF00_curtain_call == 0) {
                    func_8004A670_main(30);
                    D_8010CF00_curtain_call = 1;
                }
            } else {
                curtain->trans.x = -450.0f;
                func_8001C258_main(curtain->model[0], 4, 4);
                func_8001C258_main(curtain->model[1], 4, 4);
                D_8010CF00_curtain_call = 0;
                for (i = 0; i < 6; i++) {
                    if (D_8010CEC8_curtain_call[i][0] != 0) {
                        switch (D_8010CEFE_curtain_call) {
                            case 0:
                                D_8010CECC_curtain_call[i][0]->trans.x =
                                    D_8010B208_curtain_call[D_8010CEC9_curtain_call[i][0]];
                                break;
                            case 1:
                                D_8010CECC_curtain_call[i][0]->trans.x =
                                    D_8010B210_curtain_call[D_8010CEC9_curtain_call[i][0]];
                                break;
                            case 2:
                                D_8010CECC_curtain_call[i][0]->trans.x =
                                    D_8010B21C_curtain_call[D_8010CEC9_curtain_call[i][0]];
                                break;
                        }
                    } else {
                        D_8010CECC_curtain_call[i][0]->trans.x = -1500.0f;
                    }
                }
                D_8010CEC1_curtain_call = 5;
                HuAudFXPlay(0x419);
                func_8010644C_curtain_call();
            }
            break;
        case 5:
            func_80106494_curtain_call();
            Hu3DMotionSpeedSet(host->model[0], -1.0f);
            if ((s32)Hu3DData[host->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(host->model[0], 0.0f);
                Hu3DMotionSpeedSet(host->model[0], 0.0f);
                func_8001C258_main(host->model[0], 4, 4);
                HuAudFXPlay(0x522);
                D_8010CE88_curtain_call = 100;
                D_8010CEC1_curtain_call = 6;
            }
            break;
        case 6:
            if (D_8010CE88_curtain_call > 0) {
                D_8010CE88_curtain_call--;
                break;
            }
            switch (D_8010CEFE_curtain_call) {
                case 0:
                case 1:
                    func_8010982C_curtain_call();
                    if (D_8010CF01_curtain_call < 3) {
                        break;
                    }
                    D_8010CEFE_curtain_call = 3;
                    pick = func_80105B7C_curtain_call(2);
                    for (i = 0; i < 6; i++) {
                        for (j = 0; j < 6; j++) {
                            if (D_8010CEC9_curtain_call[i][0] == j) {
                                entry = &D_8010B4B0_curtain_call[i + 5];
                                if (pick != 0) {
                                    entry->unk_06 = D_8010CEC9_curtain_call[i][0] * 5;
                                } else {
                                    entry->unk_06 = (5 - j) * 5;
                                }
                                break;
                            }
                        }
                    }
                    return;
                case 2:
                    func_8010982C_curtain_call();
                    D_8010CEFE_curtain_call++;
                    pick = func_80105B7C_curtain_call(2);
                    for (i = 0; i < 6; i++) {
                        for (j = 0; j < 6; j++) {
                            if (D_8010CEC9_curtain_call[i][0] == j) {
                                entry = &D_8010B4B0_curtain_call[i + 5];
                                if (pick != 0) {
                                    entry->unk_06 = D_8010CEC9_curtain_call[i][0] * 5;
                                } else {
                                    entry->unk_06 = (5 - j) * 5;
                                }
                                break;
                            }
                        }
                    }
                    return;
            }
            if (D_8010CF00_curtain_call == 0) {
                D_8010CF00_curtain_call = 1;
                func_8004AB0C_main(30);
                func_8004A72C_main(30);
            }
            Hu3DMotionSpeedSet(host->model[0], 1.0f);
            func_8001C258_main(host->model[0], 4, 0);
            if ((s32)Hu3DData[host->model[0]].motTime >= 60) {
                Hu3DMotionTimeSet(host->model[0], 60.0f);
                Hu3DMotionSpeedSet(host->model[0], 0.0f);
                D_8010CF00_curtain_call = 0;
                D_8010CEFE_curtain_call++;
                D_8010CEC1_curtain_call = 0;
            }
            break;
    }
}

void func_8010A734_curtain_call(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 1520.0f;
        CRotM[i].x = 347.14f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 225.0f;
        CenterM[i].z = -25.0f;
    }
}

void func_8010A7D8_curtain_call(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_8010A7FC_curtain_call(omObjData *obj) {
    s8 i;
    s8 j;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                DataClose(D_8010CE90_curtain_call[i][j]);
            }
            Hu3DAnimKill(D_8010CE78_curtain_call[i]);
        }
        obj->func = func_8010A7D8_curtain_call;
    }
}

void func_8010A8E8_curtain_call(omObjData *obj) {
    if (D_800D530C_main == 1) {
        func_8010644C_curtain_call();
        WipeCreateOut(0, 20);
        obj->func = func_8010A7FC_curtain_call;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010A948_curtain_call(omObjData *obj) {
    switch (D_8010CF32_curtain_call) {
        case 0:
            GMesCreate(3);
            D_8010CF32_curtain_call = 1;
            D_8010CEFC_curtain_call = 0;
            break;
        case 1:
            if (GMesStatGet() == 0) {
                D_8010CF32_curtain_call = 2;
                D_8010CEC1_curtain_call = 0;
            }
            if (++D_8010CEFC_curtain_call == 62) {
                HuAudSeqPlay(0x31);
            }
            break;
        case 2:
            func_80109AD0_curtain_call();
            if (D_8010CEFE_curtain_call == 3) {
                GMesCreate(0xE);
                HuAudSeqFadeOut(120);
                D_8010CF32_curtain_call = 3;
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                D_8010CF32_curtain_call = 4;
                D_8010CE88_curtain_call = 0;
            }
            break;
        case 4:
            if (D_8010CF01_curtain_call == 4) {
                if (++D_8010CE88_curtain_call >= 16) {
                    D_8010CF32_curtain_call = 5;
                }
            } else {
                if (++D_8010CE88_curtain_call >= 16) {
                    D_8010CF32_curtain_call = 6;
                }
            }
            break;
        case 6:
            switch (D_8010CF01_curtain_call) {
                case 0:
                    GMesCreate(0x23, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1], D_8010CE80_curtain_call[2],
                               D_8010CE80_curtain_call[3]);
                    GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[2]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[3]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 1:
                    GMesCreate(0x22, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1], D_8010CE80_curtain_call[2]);
                    GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[2]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 2:
                    GMesCreate(0x1E, D_8010CE80_curtain_call[0], D_8010CE80_curtain_call[1]);
                    GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
                    GwPlayer[D_8010CF28_curtain_call[1]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 3:
                    GMesCreate(0x16, D_8010CE80_curtain_call[0]);
                    GwPlayer[D_8010CF28_curtain_call[0]].bonusCoin = 10;
                    HuAudSeqPlay(0x65);
                    break;
            }
            D_8010CE88_curtain_call = 15;
            D_8010CF32_curtain_call = 7;
            break;
        case 5:
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            D_8010CE88_curtain_call = 15;
            D_8010CF32_curtain_call = 7;
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (--D_8010CE88_curtain_call <= 0) {
                    WipeCreateOut(0, 20);
                    obj->func = func_8010A7FC_curtain_call;
                }
            }
            break;
    }
}

void func_8010AD68_curtain_call(omObjData *obj) {
    D_8010CF32_curtain_call = 0;
    D_8010CEC1_curtain_call = 20;
    D_8010CE88_curtain_call = 0;
    D_8010CEFE_curtain_call = 0;
    D_8010CF34_curtain_call = NULL;
    D_8010CF00_curtain_call = 0;
    func_8010A734_curtain_call();
    func_80106688_curtain_call();
    func_801093C4_curtain_call();
    func_801090FC_curtain_call();
    func_801084A0_curtain_call();
    func_80108E64_curtain_call();
    WipeCreateIn(0xFF, 16);
    obj->func = func_8010A948_curtain_call;
}

void func_8010AE00_curtain_call(void) {
}

void func_8010AE08_curtain_call(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010B280_curtain_call[i].scissorX, D_8010B280_curtain_call[i].scissorY,
                   D_8010B280_curtain_call[i].scissorWidth, D_8010B280_curtain_call[i].scissorHeight);
        ViewportSet(i, D_8010B280_curtain_call[i].viewportScale.x, D_8010B280_curtain_call[i].viewportScale.y,
                    D_8010B280_curtain_call[i].viewportScale.z, D_8010B280_curtain_call[i].viewportTranslate.x,
                    D_8010B280_curtain_call[i].viewportTranslate.y, D_8010B280_curtain_call[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010B280_curtain_call[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010AF78_curtain_call(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(50, 3);
    func_8004A208_main();
    func_8010AE08_curtain_call();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010B4A0_curtain_call, 0);
    func_80045010_main(D_8010B4A0_curtain_call, 1);
    omAddObj(1500, 0, 0, -1, func_8010AD68_curtain_call);
    omAddObj(1500, 0, 0, -1, func_8010A8E8_curtain_call);
    func_80105A3C_curtain_call();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_22_curtain_call/20BFA0", D_8010B4A0_curtain_call);
