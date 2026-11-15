#include "common_duel.h"
#include "ovl_81.h"

typedef struct SomeStruct {
    u8 unk_00[10];
} SomeStruct;

typedef struct SomeStruct2 {
    u16 unk_00[8];
} SomeStruct2;

typedef struct SomeStruct3 {
    u8 unk_00[11];
} SomeStruct3;

typedef struct UnkOvl81_3 {
    /* 0x00 */ s32 playerIndex;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec *unk_08;
    /* 0x0C */ Vec *unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char unk_14[0xC];
} UnkOvl81_3; // sizeof 0x20

extern s16 D_80102CA4_name_81;
extern u8 D_80102CA6_name_81;
extern s16 D_80102CA8_name_81;
extern s16 D_80102CAA_name_81[];
extern GAMEMES D_80102C30_name_81;
extern omObjData *D_80102CB0_name_81;
extern omObjData *D_80102CB4_name_81;
extern u8 D_80102CB8_name_81;
extern s16 D_80102CBA_name_81[2];
extern s16 D_80102CBE_name_81[2];
extern Vec D_80102CE0_name_81;
extern Vec D_80102CEC_name_81;
extern Vec D_80102CF8_name_81;
extern Vec D_80102D04_name_81;
extern Vec D_80102D10_name_81;
extern s32 D_80102CC4_name_81;
extern s32 D_80102CC8_name_81;
extern UnkBoard4 *D_80102CCC_name_81;
extern UnkBoard4 *D_80102CD0_name_81;

char *D_80100FC0_name_81[] = { "  1 VS 1 GAME ", "  HAPPENING!  " };
s8 D_80100FC8_name_81[] = { 14, 14 };
s8 D_80100FCC_name_81[] = { -8, -8, -8, -8, -8, -8 };
s16 D_80100FD4_name_81[] = { 60, 93, 126, 159, 192, 225, 258 };

const SomeStruct D_80102478_name_81 = { { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 } };
const SomeStruct2 D_80102484_name_81 = { { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 } };
const SomeStruct3 D_80102494_name_81 = { { 0, 1, 2, 2, 3, 4, 5, 2, 1, 6, 2 } };

void func_800E31A0_name_81(void);
void func_800E02B4_name_81(s32 arg0);
void func_800E3400_name_81(s32 arg0);
void func_800E2AD0_name_81(omObjData *arg0);
void func_800E38B0_name_81(void);
void func_800E4914_name_81(void);
void func_800E4188_name_81(void);

void func_800E2870_name_81(void) {
    D_80102CA4_name_81 = -1;
    D_80102CA6_name_81 = 0;
    D_80102CA8_name_81 = -1;
    D_80102CAA_name_81[0] = D_80102CAA_name_81[1] = -1;
    D_80102CB0_name_81 = NULL;
    D_80102CB4_name_81 = NULL;
}

void func_800E28B0_name_81(void) {
    if (D_80102CA6_name_81 & 0x20) {
        GMesSprClose(&D_80102C30_name_81);
    }
    if (D_80102CA6_name_81 & 0x10) {
        HuSprGrpKill(D_80102CA8_name_81);
        HuSprAnimKill(D_80102CAA_name_81[0]);
        HuSprAnimKill(D_80102CAA_name_81[1]);
    }
    if (D_80102CB0_name_81 != NULL) {
        omDelObj(D_80102CB0_name_81);
        D_80102CB0_name_81 = NULL;
    }
    if (D_80102CB4_name_81 != NULL) {
        omDelObj(D_80102CB4_name_81);
        D_80102CB4_name_81 = NULL;
    }
    D_80102CA6_name_81 &= 0xCF;
}

void func_800E2978_name_81(omObjData *arg0) {
    s32 i;

    switch (arg0->work[0]) {
        case 0:
            arg0->rot.x += 30.0f;
            arg0->scale.x = sindf(arg0->rot.x) * 0.5f + 1.0f;
            HuSprScaleSet(D_80102CBA_name_81[0], 0, arg0->scale.x, arg0->scale.x);
            if (arg0->rot.x >= 360.0f) {
                arg0->rot.x -= 360.0f;
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                if (D_80102CBE_name_81[i] != -1) {
                    HuSprAnimKill(D_80102CBE_name_81[i]);
                }
                if (D_80102CBA_name_81[i] != -1) {
                    HuSprGrpKill(D_80102CBA_name_81[i]);
                }
            }
            D_80102CB4_name_81 = NULL;
            omDelObj(arg0);
            break;
    }
}

void func_800E2AD0_name_81(omObjData *arg0) {
    s32 i;

    if (arg0->rot.y > 0.0f) {
        arg0->rot.y = arg0->rot.y - 1.0f;
    }

    switch (arg0->work[0]) {
        case 0:
            arg0->scale.x += 0.2f;
            HuSprScaleSet(D_80102CA8_name_81, 0, arg0->scale.x, arg0->scale.x);
            if (arg0->scale.x >= 1.0f) {
                arg0->work[0] = 1;
                arg0->work[1] = 12;
            }
            break;
        case 1:
            if (arg0->work[3] == 6) {
                arg0->work[1]--;
                for (i = 0; i < 4; i++) {
                    if (!(GwPlayer[i].stat & 1)) {
                        break;
                    }
                }
                if (i != 4) {
                    for (i = 0; i < 4; i++) {
                        if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                            arg0->work[0] = 2;
                        }
                    }
                } else if (arg0->work[1] == 0) {
                    arg0->work[0] = 2;
                }
                if (arg0->work[2] == 0) {
                    HuSprPosSet(D_80102CA8_name_81, 0, 160, 120 + (s32)(sindf(arg0->rot.x) * 5.0f + 0.5f));
                    arg0->rot.x += 10.0f;
                    if (arg0->rot.x >= 360.0f) {
                        arg0->rot.x -= 360.0f;
                    }
                } else {
                    arg0->work[2]--;
                }
                break;
            }

            if (arg0->work[1] != 0) {
                arg0->work[1]--;
                break;
            }

            if (!(GwPlayer[arg0->work[3]].stat & 1)) {
                if (!(arg0->rot.y <= 0.0f)) {
                    if (!(D_800D5558_main[GwPlayer[arg0->work[3]].pad] & (A_BUTTON | B_BUTTON))) {
                        break;
                    }
                }
            }
            arg0->work[0] = 2;
            break;
        case 2:
            arg0->scale.x += 0.2f;
            HuSprScaleSet(D_80102CA8_name_81, 0, arg0->scale.x, arg0->scale.x);
            HuSprTPLvlSet(D_80102CA8_name_81, 0, (2.0f - arg0->scale.x) * 256.0f);
            if (arg0->scale.x >= 2.0f) {
                arg0->work[0] = 3;
            }
            break;
        case 3:
            HuSprGrpKill(D_80102CA8_name_81);
            HuSprAnimKill(D_80102CAA_name_81[0]);
            D_80102CA8_name_81 = -1;
            D_80102CAA_name_81[0] = -1;
            if (D_80102CB4_name_81 != NULL) {
                for (i = 0; i < 2; i++) {
                    if (D_80102CBE_name_81[i] != -1) {
                        HuSprAnimKill(D_80102CBE_name_81[i]);
                    }
                    if (D_80102CBA_name_81[i] != -1) {
                        HuSprGrpKill(D_80102CBA_name_81[i]);
                    }
                }
                omDelObj(D_80102CB4_name_81);
                D_80102CB4_name_81 = NULL;
            }
            D_80102CB0_name_81 = NULL;
            omDelObj(arg0);
            break;
    }
}

void func_800E2F84_name_81(void) {
    D_80102CB8_name_81 = 1;
}

void func_800E2F94_name_81(omObjData *obj) {
    s32 i;

    if (obj->work[2] != 0) {
        obj->work[2]--;
        return;
    }

    obj->scale.x += 0.05f;
    if (obj->scale.x >= 1.0f) {
        obj->scale.x = 1.0f;
        obj->rot.z += 20.0f;
        if (obj->rot.z >= 360.0f) {
            obj->rot.z -= 360.0f;
        }
    }

    HuSprPosSet(D_80102C30_name_81.strGId[D_80102CA4_name_81], 0, obj->rot.x + 80.0f,
                D_80102CC8_name_81 + 2.0f * sindf(obj->rot.z));

    for (i = 1; D_80100FC8_name_81[obj->work[0]] >= i; i++) {
        HuSprTPLvlSet(D_80102C30_name_81.strGId[D_80102CA4_name_81], i, obj->scale.x * 256.0f);
    }
}

void func_800E31A0_name_81(void) {
    omObjData *obj;
    void *data;
    SomeStruct sp18 = D_80102478_name_81;

    obj = omAddObj(-0x8000, 0, 0, -1, func_800E2978_name_81);
    D_80102CB4_name_81 = obj;
    obj->rot.x = 0.0f;

    if (D_80102CC4_name_81 == 0) {
        D_80102CBA_name_81[0] = HuSprGrpCreate(1, 0);
        data = DataRead(0x1301E0);
        D_80102CBE_name_81[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80102CBA_name_81[0], 0, D_80102CBE_name_81[0], 0);
        HuSprPriSet(D_80102CBA_name_81[0], 0, 0x10);
        HuSprAttrSet(D_80102CBA_name_81[0], 0, 0x1000);
        HuSprPosSet(D_80102CBA_name_81[0], 0, 0xA0, 0x32);
        D_80102CBE_name_81[1] = -1;
        D_80102CBA_name_81[1] = -1;
        obj->work[0] = 1;
        return;
    }

    D_80102CBA_name_81[0] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DF);
    D_80102CBE_name_81[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80102CBA_name_81[0], 0, D_80102CBE_name_81[0], sp18.unk_00[D_80102CC4_name_81]);
    HuSprPriSet(D_80102CBA_name_81[0], 0, 0x10);
    HuSprAttrSet(D_80102CBA_name_81[0], 0, 0x1000);
    HuSprPosSet(D_80102CBA_name_81[0], 0, 0xA0, 0x32);

    D_80102CBA_name_81[1] = HuSprGrpCreate(1, 0);
    data = DataRead(0x1301DE);
    D_80102CBE_name_81[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80102CBA_name_81[1], 0, D_80102CBE_name_81[1], 0);
    HuSprPriSet(D_80102CBA_name_81[1], 0, 0x11);
    HuSprAttrSet(D_80102CBA_name_81[1], 0, 0x1000);
    HuSprPosSet(D_80102CBA_name_81[1], 0, 0xA0, 0x32);
    obj->work[0] = 0;
}

void func_800E3400_name_81(s32 arg0) {
    omObjData *obj;
    void *data;
    SomeStruct2 sp18 = D_80102484_name_81;

    D_80102CA8_name_81 = HuSprGrpCreate(1, 0);
    data = DataRead(sp18.unk_00[GwPlayer[arg0].chr] | 0x130000);
    D_80102CAA_name_81[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80102CA8_name_81, 0, D_80102CAA_name_81[0], 0);
    HuSprPriSet(D_80102CA8_name_81, 0, 0x10);
    HuSprAttrSet(D_80102CA8_name_81, 0, 0x1000);
    HuSprPosSet(D_80102CA8_name_81, 0, 0xA0, 0x78);
    obj = omAddObj(-0x8000, 0, 0, -1, func_800E2AD0_name_81);
    D_80102CB0_name_81 = obj;

    obj->scale.x = 0;
    obj->rot.x = 180.0f;
    obj->rot.y = 150.0f;
    obj->work[2] = 30;
    obj->work[0] = 0;
    obj->work[1] = 12;

    if (D_80102CB4_name_81 != NULL) {
        obj->work[1] = 24;
    }
    obj->work[3] = arg0;
    if (arg0 >= 2) {
        obj->work[3] = 4;
    }
}

s32 func_800E35C4_name_81(void) {
    return D_80102CA6_name_81 & 4;
}

void func_800E35D4_name_81(void) {
    HuSprGrpKill(D_80102CA8_name_81);
    HuSprAnimKill(D_80102CAA_name_81[0]);
    HuSprAnimKill(D_80102CAA_name_81[1]);
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    D_80102CA6_name_81 &= 0xC3;
}

void func_800E363C_name_81(s32 arg0, Vec *pos) {
    Vec2f pos2D;
    omObjData *obj;
    s32 i;
    s32 type;

    if (!(D_80102CA6_name_81 & 4)) {
        type = arg0;
        D_80102CA4_name_81 = GameMesStrInit(&D_80102C30_name_81, D_80100FC0_name_81[type], 0, 0, 0);
        MBDCamera3Dto2D(pos, &pos2D);
        D_80102CC8_name_81 = pos2D.y - 24.0f;
        if (MBDCameraZoomGet() == 2.0f) {
            D_80102CC8_name_81 -= 10;
        }
        HuSprPosSet(D_80102C30_name_81.strGId[D_80102CA4_name_81], 0, D_80100FCC_name_81[type] + 80,
                    D_80102CC8_name_81);

        for (i = 1; D_80100FC8_name_81[type] >= i; i++) {
            HuSprTPLvlSet(D_80102C30_name_81.strGId[D_80102CA4_name_81], i, 0);
        }

        obj = omAddObj(-0x8000, 0, 0, -1, func_800E2F94_name_81);
        D_80102CB0_name_81 = obj;
        obj->scale.x = 0.0f;
        obj->trans.x = 400.0f;
        obj->trans.z = 0.0f;
        obj->rot.x = D_80100FCC_name_81[type];
        obj->rot.y = 0.0f;
        obj->rot.z = 0.0f;
        obj->work[0] = type;
        obj->work[1] = D_80102CA4_name_81;
        obj->work[2] = 30;
        obj->work[3] = 7;
        D_80102CA6_name_81 = 38;
        func_800E02B4_name_81(arg0);
    }
}

s32 func_800E3858_name_81(void) {
    return D_80102CA6_name_81 & 0xC;
}

void func_800E3868_name_81(void) {
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    GMesSprClose(&D_80102C30_name_81);
    D_80102CA6_name_81 &= 0xC3;
}

void func_800E38B0_name_81(void) {
    UnkOvl81_1 *work = HuPrcCurrentGet()->user_data;

    while (1) {
        switch (work->unk_00) {
            case 0:
                HuAudFXPlay(0x10C);
                if (work->unk_04 == 0) {
                    D_80102CC4_name_81 = GwSystem.total_turns - GwSystem.current_turn;
                    switch (D_80102CC4_name_81) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 9:
                            func_800E31A0_name_81();
                            break;
                    }
                }
                func_800E3400_name_81(work->unk_04);
                work->unk_00++;
                break;
            case 1:
                if (D_80102CA8_name_81 == -1) {
                    omDelPrcObj(NULL);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process *func_800E39AC_name_81(s32 playerIndex) {
    Process *process = omAddPrcObj(func_800E38B0_name_81, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = 0;
    work->unk_04 = playerIndex;
    return process;
}

void func_800E3A0C_name_81(void) {
    s32 idx = ((UnkOvl81_1 *)HuPrcCurrentGet()->user_data)->unk_00;
    s32 i;

    HuSprAttrReset(D_80102CCC_name_81->unk_0A, idx, 0x8000);
    HuSprAttrReset(D_80102CD0_name_81->unk_0A, idx, 0x8000);
    for (i = 0; i < 93; i += 23) {
        HuSprScaleSet(D_80102CCC_name_81->unk_0A, idx, (120 - i) / 20.0f + 1.0f, (120 - i) / 20.0f + 1.0f);
        HuSprScaleSet(D_80102CD0_name_81->unk_0A, idx, (120 - i) / 20.0f + 1.0f, (120 - i) / 20.0f + 1.0f);
        HuSprPosSet(D_80102CCC_name_81->unk_0A, idx, D_80100FD4_name_81[idx], i);
        HuSprPosSet(D_80102CD0_name_81->unk_0A, idx, D_80100FD4_name_81[idx], i);
        HuSprTPLvlSet(D_80102CCC_name_81->unk_0A, idx, i * 2);
        HuSprTPLvlSet(D_80102CD0_name_81->unk_0A, idx, i * 2);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_80102CCC_name_81->unk_0A, idx, 1.0f, 1.0f);
    HuSprScaleSet(D_80102CD0_name_81->unk_0A, idx, 1.0f, 1.0f);
    HuSprPosSet(D_80102CCC_name_81->unk_0A, idx, D_80100FD4_name_81[idx], 92);
    HuSprPosSet(D_80102CD0_name_81->unk_0A, idx, D_80100FD4_name_81[idx], 92);
    HuSprTPLvlSet(D_80102CCC_name_81->unk_0A, idx, 256);
    HuSprTPLvlSet(D_80102CD0_name_81->unk_0A, idx, 256);
    omDelPrcObj(NULL);
}

void func_800E3C6C_name_81(void) {
    SomeStruct3 members = D_80102494_name_81;
    UnkBoard4 *sprite;
    Process *process;
    UnkOvl81_1 *work;
    void *data;
    f32 scale;
    f32 rot;
    s32 i;

    data = DataRead(0x130121);
    D_80102CCC_name_81 = func_800F4528_name_81(7, 0);
    D_80102CCC_name_81->unk_0C[0] = HuSprAnimRead(data);
    for (i = 0; i < 7; i++) {
        HuSprGrpMemberSet(D_80102CCC_name_81->unk_0A, i, D_80102CCC_name_81->unk_0C[0], members.unk_00[i]);
        HuSprPriSet(D_80102CCC_name_81->unk_0A, i, 1);
        HuSprAttrSet(D_80102CCC_name_81->unk_0A, i, 0x1000);
        HuSprPosSet(D_80102CCC_name_81->unk_0A, i, D_80100FD4_name_81[i], 92);
        HuSprAttrSet(D_80102CCC_name_81->unk_0A, i, 0x8000);
    }
    DataClose(data);

    data = DataRead(0x130122);
    D_80102CD0_name_81 = func_800F4528_name_81(7, 0);
    D_80102CD0_name_81->unk_0C[0] = HuSprAnimRead(data);
    for (i = 0; i < 7; i++) {
        HuSprGrpMemberSet(D_80102CD0_name_81->unk_0A, i, D_80102CD0_name_81->unk_0C[0], members.unk_00[i]);
        HuSprPriSet(D_80102CD0_name_81->unk_0A, i, 2);
        HuSprAttrSet(D_80102CD0_name_81->unk_0A, i, 0x1000);
        HuSprPosSet(D_80102CD0_name_81->unk_0A, i, D_80100FD4_name_81[i], 92);
        HuSprColorSet(D_80102CD0_name_81->unk_0A, i, 0, 21, 233);
        HuSprAttrSet(D_80102CD0_name_81->unk_0A, i, 0x8000);
    }
    DataClose(data);

    for (i = 0; i < 7; i++) {
        HuPrcSleep(3);
        process = omAddPrcObj(func_800E3A0C_name_81, 10, 0, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
        process->user_data = work;
        work->unk_00 = i;
    }

    HuAudFXPlay(0x1CF);
    data = DataRead(0x130133);
    sprite = func_800F4528_name_81(1, 0);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 1);
    HuSprAttrSet(sprite->unk_0A, 0, 0x1000);
    HuSprPosSet(sprite->unk_0A, 0, 160, 92);
    HuSprScaleSet(sprite->unk_0A, 0, 0.0f, 0.0f);
    HuSprColorSet(sprite->unk_0A, 0, 255, 255, 0);
    HuSprTPLvlSet(sprite->unk_0A, 0, 200);
    DataClose(data);

    rot = 0.0f;
    for (scale = 1.0f; scale <= 4.0f; scale += 1.0f) {
        HuSprScaleSet(sprite->unk_0A, 0, scale, scale);
        HuSprZRotSet(sprite->unk_0A, 0, rot);
        rot += 75.0f;
        HuPrcVSleep();
    }
    for (; scale >= 0.0f; scale -= 1.0f) {
        HuSprScaleSet(sprite->unk_0A, 0, scale, scale);
        HuSprZRotSet(sprite->unk_0A, 0, rot);
        rot += 75.0f;
        HuPrcVSleep();
    }

    HuSprAttrSet(sprite->unk_0A, 0, 0x8000);
    HuPrcSleep(15);
    func_800F4584_name_81(D_80102CCC_name_81);
    func_800F4584_name_81(D_80102CD0_name_81);
    func_800F4584_name_81(sprite);
    omDelPrcObj(NULL);
}

Process *func_800E415C_name_81(void) {
    return omAddPrcObj(func_800E3C6C_name_81, 0, 0, 0);
}

void func_800E4188_name_81(void) {
    UnkOvl81_3 *work = HuPrcCurrentGet()->user_data;
    s32 playerIndex = work->playerIndex;
    s32 unk_04 = work->unk_04;
    Vec *from = work->unk_08;
    Vec *to = work->unk_0C;
    s32 mode = work->unk_10;
    Vec dir;
    s32 files[2] = { 0x130124, 0x130125 };
    s32 offsX[4][3] = { { 0, 0, -24 }, { 0, 0, 0 }, { 0, 0, 24 }, { 0, 0, 0 } };
    s32 offsY[4][3] = { { 0, 0, 45 }, { 0, 0, 37 }, { 0, 0, 45 }, { 0, 0, 37 } };
    Vec2f startPos[4] = { { 80.0f, -220.0f }, { -200.0f, 60.0f }, { 240.0f, 440.0f }, { 520.0f, 60.0f } };
    Vec2f startPos2[4] = { { 130.0f, -220.0f }, { -200.0f, 110.0f }, { 190.0f, 440.0f }, { 520.0f, 110.0f } };
    Vec2f speed[4] = { { 0.0f, 32.0f }, { 32.0f, 0.0f }, { 0.0f, -32.0f }, { -32.0f, 0.0f } };
    UnkBoard4 *sprite;
    void *data;
    f32 angle;
    s32 dirIdx;
    s32 delay;
    s32 i;

    MBDVecDirGet(from, to, &dir);
    angle = MBDVecAngleGet(&dir) + 45.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    dirIdx = angle / 90.0f;
    if (dirIdx >= 4) {
        dirIdx = 3;
    }

    sprite = func_800F4528_name_81(3, 2);
    for (i = 0; i < 3; i++) {
        if ((mode == 1 || mode == 2) && i == 2) {
            continue;
        }
        if (mode == 3 && i != 2) {
            continue;
        }
        switch (i) {
            case 0:
                data = DataRead(files[playerIndex]);
                break;
            case 1:
                data = DataRead(0x130126 + unk_04);
                break;
            default:
                data = DataRead(0x130123);
                break;
        }
        sprite->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(sprite->unk_0A, i, sprite->unk_0C[i], 0);
        HuSprPriSet(sprite->unk_0A, i, 1);
        HuSprAttrSet(sprite->unk_0A, i, 0);
        if (mode == 3) {
            HuSprPosSet(sprite->unk_0A, i, offsX[dirIdx][i], offsY[dirIdx][i]);
        } else {
            HuSprPosSet(sprite->unk_0A, i, 0, offsY[dirIdx][i]);
        }
        DataClose(data);
    }

    HuSprZRotSet(sprite->unk_0A, 0, (dirIdx - 1) * 90);
    if (dirIdx == 2 || dirIdx == 3) {
        HuSprAttrSet(sprite->unk_0A, 1, 1);
    }
    if (dirIdx == 3) {
        HuSprAttrSet(sprite->unk_0A, 0, 2);
    }

    if (!(mode & 1)) {
        HuSprPosSet(sprite->unk_0A, 0, startPos[dirIdx].x, startPos[dirIdx].y);
        for (i = 0; i < 10; i++) {
            HuSprPosSet(sprite->unk_0A, 0, startPos[dirIdx].x + i * speed[dirIdx].x,
                        startPos[dirIdx].y + i * speed[dirIdx].y);
            HuPrcVSleep();
        }
    } else {
        HuSprPosSet(sprite->unk_0A, 0, startPos2[dirIdx].x, startPos2[dirIdx].y);
        HuPrcSleep(mode + 2);
        for (i = 0; i < 10; i++) {
            HuSprPosSet(sprite->unk_0A, 0, startPos2[dirIdx].x + i * speed[dirIdx].x,
                        startPos2[dirIdx].y + i * speed[dirIdx].y);
            HuPrcVSleep();
        }
    }

    if (!(mode & 1)) {
        delay = 15;
    } else {
        delay = 12;
        delay -= mode;
    }
    HuPrcSleep(delay);
    func_800F4584_name_81(sprite);
    omDelPrcObj(NULL);
}

Process *func_800E47B8_name_81(s32 playerIndex, s32 arg1, Vec *arg2, Vec *arg3, s32 arg4) {
    Process *process;
    UnkOvl81_3 *work;
    s32 flag;

    process = omAddPrcObj(func_800E4188_name_81, 0, 0x1000, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
    process->user_data = work;
    work->playerIndex = playerIndex;
    work->unk_04 = arg1;
    work->unk_08 = arg2;
    work->unk_0C = arg3;
    work->unk_10 = 0;

    if (arg4 != 0) {
        if (playerIndex == 0) {
            flag = GWBoardFlagCheck(0x12);
        } else {
            flag = GWBoardFlagCheck(0x13);
        }
        if (flag == 0) {
            return process;
        }
        work->unk_10 = 2;

        process = omAddPrcObj(func_800E4188_name_81, 0, 0x1000, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
        process->user_data = work;
        work->playerIndex = playerIndex;
        work->unk_04 = arg1;
        work->unk_08 = arg2;
        work->unk_0C = arg3;
        work->unk_10 = 1;

        process = omAddPrcObj(func_800E4188_name_81, 0, 0x1000, 0x40);
        work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_3));
        process->user_data = work;
        work->playerIndex = playerIndex;
        work->unk_04 = arg1;
        work->unk_08 = arg2;
        work->unk_0C = arg3;
        work->unk_10 = 3;
    }
    return process;
}

void func_800E4914_name_81(void) {
    s32 idx = ((UnkOvl81_1 *)HuPrcCurrentGet()->user_data)->unk_00;
    s32 files[2] = { 0x130101, 0x130102 };
    s32 posY[2] = { 120, 90 };
    UnkBoard4 *sprite;
    void *data;
    s32 speed;
    s32 offset;
    s32 i;

    sprite = func_800F4528_name_81(1, 2);
    data = DataRead(files[idx]);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 0x2010);
    HuSprAttrSet(sprite->unk_0A, 0, 0);
    DataClose(data);

    speed = 0;
    offset = 0;
    for (i = 0; i < 7; i++) {
        HuSprPosSet(sprite->unk_0A, 0, 160, posY[idx] + offset);
        if (idx == 0) {
            offset -= speed;
        } else {
            offset += speed;
        }
        speed += 2;
        HuPrcVSleep();
    }

    HuPrcSleep(20);
    func_800F4584_name_81(sprite);
    omDelPrcObj(NULL);
}

Process *func_800E4A74_name_81(s32 arg0) {
    Process *process = omAddPrcObj(func_800E4914_name_81, 0, 0, 0x40);
    UnkOvl81_1 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkOvl81_1));
    process->user_data = work;
    work->unk_00 = arg0;
    return process;
}

void func_800E4AD0_name_81(void) {
    Hu3DCameraPerspectiveSet(1, 40.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(1, &D_80102CE0_name_81, &D_80102CEC_name_81, &D_80102CF8_name_81);
    Hu3DCamUpdateMtx(1);
    Hu3DCameraViewportSet(1, &D_80102D04_name_81, &D_80102D10_name_81);
}

void func_800E4B38_name_81(void) {
    while (1) {
        func_800E4AD0_name_81();
        HuPrcVSleep();
    }
}

UnkOvl81_2 *func_800E4B64_name_81(s32 arg0, s32 arg1) {
    HmfModel *rotHmf;
    HmfModel *hmf;
    UnkOvl81_2 *guide;
    Object *obj;
    Process *process;
    f32 zero;
    f32 one;

    guide = HuMemMemoryAllocTemp(sizeof(UnkOvl81_2));
    if (guide != NULL) {
        obj = func_800D8010_name_81(0x3E, NULL);
        guide->obj = obj;
        HuVecCopyXYZ(&obj->scale, 1.43f, 1.43f, 1.43f);
        guide->obj->flags |= 1;

        Hu3DModelCameraSet(guide->obj->omObj1->model[0], HU3D_CAM1);

        rotHmf = &Hu3DData[guide->obj->omObj1->model[0]];
        sincosdf(15.0f, &rotHmf->mtx[1][2], &rotHmf->mtx[1][1]);

        Hu3DData[guide->obj->omObj1->model[0]].mtx[2][1] = -Hu3DData[guide->obj->omObj1->model[0]].mtx[1][2];

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        hmf->mtx[2][2] = hmf->mtx[1][1];

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        zero = 0.0f;
        hmf->mtx[3][2] = zero;
        hmf->mtx[3][1] = zero;
        hmf->mtx[3][0] = zero;
        hmf->mtx[2][3] = zero;
        hmf->mtx[2][0] = zero;
        hmf->mtx[1][3] = zero;
        hmf->mtx[1][0] = zero;
        hmf->mtx[0][3] = zero;
        hmf->mtx[0][2] = zero;
        hmf->mtx[0][1] = zero;

        hmf = &Hu3DData[guide->obj->omObj1->model[0]];
        one = 1.0f;
        hmf->mtx[3][3] = one;
        hmf->mtx[0][0] = one;

        process = omAddPrcObj(func_800E4B38_name_81, 0x4000, 0, 0);
        guide->process = process;
        process->user_data = guide;

        guide->unk_0A = 0x69;

        D_80102CE0_name_81.x = zero;
        D_80102CE0_name_81.y = zero;
        D_80102CE0_name_81.z = 120.0f;

        D_80102CEC_name_81.x = zero;
        D_80102CEC_name_81.y = zero;
        D_80102CEC_name_81.z = zero;

        D_80102CF8_name_81.x = zero;
        D_80102CF8_name_81.y = one;
        D_80102CF8_name_81.z = zero;

        D_80102D04_name_81.x = 1280.0f;
        D_80102D04_name_81.y = 960.0f;
        D_80102D04_name_81.z = 511.0f;

        D_80102D10_name_81.x = 240.0f;
        D_80102D10_name_81.y = guide->unk_0A * 4.0f + 480.0f;
        D_80102D10_name_81.z = 511.5f;

        func_800E4AD0_name_81();

        if (arg1 != 0) {
            guide->win_id = HuWinExCreateStyled(0x5B, guide->unk_0A + 0x5A + arg1, 0x11);
        } else {
            guide->win_id = HuWinExCreateStyled(0x4B, guide->unk_0A + 0x5A + arg1, 0x10);
        }
    }
    return guide;
}

void func_800E4E64_name_81(UnkOvl81_2 *arg0) {
    if (arg0 != NULL) {
        MBDModelKill(arg0->obj);
        omDelPrcObj(arg0->process);
        HuWinExCleanup(arg0->win_id);
        HuMemMemoryFreeTemp(arg0);
    }
}

void func_800E4EAC_name_81(UnkOvl81_2 *arg0, s16 arg1, s16 arg2) {
    arg0->unk_0A = arg1;
    D_80102D10_name_81.y = arg1 * 4.0f + 480.0f;
    if (arg2 != 0) {
        HuWinPosSet(arg0->win_id, 91, arg0->unk_0A + 80 + arg2);
    } else {
        HuWinPosSet(arg0->win_id, 75, arg0->unk_0A + 90 + arg2);
    }
}
