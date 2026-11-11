#include "common_duel.h"
#include "ovl_81.h"

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
extern f32 D_80102D14_name_81;
extern s32 D_80102CC4_name_81;

void func_800E31A0_name_81(void);
void func_800E3400_name_81(s32 arg0);
void func_800E38B0_name_81(void);
void func_800E4914_name_81(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102458_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102468_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102478_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102484_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102494_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024A0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_801024D0_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102500_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102520_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/CA640", D_80102540_name_81);

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
        func_8003B128_main(&D_80102C30_name_81);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2AD0_name_81);

void func_800E2F84_name_81(void) {
    D_80102CB8_name_81 = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E2F94_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E31A0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3400_name_81);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E363C_name_81);

s32 func_800E3858_name_81(void) {
    return D_80102CA6_name_81 & 0xC;
}

void func_800E3868_name_81(void) {
    omDelObj(D_80102CB0_name_81);
    D_80102CB0_name_81 = NULL;
    func_8003B128_main(&D_80102C30_name_81);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3A0C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E3C6C_name_81);

Process *func_800E415C_name_81(void) {
    return omAddPrcObj(func_800E3C6C_name_81, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4188_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E47B8_name_81);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/CA640", func_800E4B64_name_81);

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
    D_80102D14_name_81 = arg1 * 4.0f + 480.0f;
    if (arg2 != 0) {
        HuWinPosSet(arg0->win_id, 91, arg0->unk_0A + 80 + arg2);
    } else {
        HuWinPosSet(arg0->win_id, 75, arg0->unk_0A + 90 + arg2);
    }
}
