#include "common.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/util.h"
#include "mallocblock.h"

typedef struct HandLineSinkerObjWork {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s32 unk8;
    /* 0x00C */ Vec pos;
    /* 0x018 */ Vec unk18;
    /* 0x024 */ char unk24[0x1CC - 0x24];
    /* 0x1CC */ s16 seNo;
    /* 0x1CE */ char unk1CE[0x1D4 - 0x1CE];
} HandLineSinkerObjWork; // sizeof 0x1D4

extern s16 D_8010C0EC_hand_line_sinker;
extern s16 D_8010C0F0_hand_line_sinker;
extern omObjData *D_8010C0F4_hand_line_sinker;
extern omObjData *D_8010C0F8_hand_line_sinker;
extern s16 D_8010C10C_hand_line_sinker;
extern omObjData **D_8010C100_hand_line_sinker;
extern s32 D_8010BFA0_hand_line_sinker[];
extern s16 D_8010C148_hand_line_sinker[2][6];
extern s32 D_8010C160_hand_line_sinker[];
extern u16 D_8010C104_hand_line_sinker[2];
extern f32 D_8010C108_hand_line_sinker;
extern u8 D_800D6A90_main;

void func_80105D28_hand_line_sinker(omObjData *);
void func_80105FA4_hand_line_sinker(omObjData *obj);
void func_8001E888_main(s16 model, f32 x, f32 y, u16 arg3, u16 arg4, char *name, s32 arg6);
void func_800335BC_main(char *name, u16 *result);
void func_80106100_hand_line_sinker(omObjData *obj, u16 playerNo);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801059A0_hand_line_sinker);

void func_80105CF0_hand_line_sinker(omObjData *arg0) {
    D_8010C0EC_hand_line_sinker = 0;
    D_8010C0F8_hand_line_sinker = 0;
    D_8010C0F4_hand_line_sinker = 0;
    D_8010C0F0_hand_line_sinker = 0;
    D_8010C10C_hand_line_sinker = 0;
    arg0->func = func_80105D28_hand_line_sinker;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010BFB0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80105D28_hand_line_sinker);

void func_80105EE8_hand_line_sinker(omObjData *obj) {
    obj->data = HuMemAllocTag(0x24, 0x7918);
    obj->model[0] = func_8000B108_main(0x220000, 0x699);
    obj->model[1] = func_8000B108_main(0x220001, 0x1A99);
    obj->model[2] = func_8000B108_main(0x220003, 0x699);
    func_8001C814_main(obj->model[2], 2, 2);
    func_800335BC_main("m201_3mizu_DEF", D_8010C104_hand_line_sinker);
    func_8001C954_main(obj->model[1]);
    D_8010C108_hand_line_sinker = 0.0f;
    obj->func = func_80105FA4_hand_line_sinker;
}

void func_80105FA4_hand_line_sinker(omObjData *obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010C108_hand_line_sinker += 0.1f;
    }
    func_8001E888_main(obj->model[1], D_8010C108_hand_line_sinker, 0.0f, D_8010C104_hand_line_sinker[0],
                       D_8010C104_hand_line_sinker[1], "m201_00-grid6", 0);
}

void func_80106040_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 0);
}

void func_80106070_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 1);
}

void func_801060A0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 2);
}

void func_801060D0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 3);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010BFF0_hand_line_sinker);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010C008_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80106100_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010689C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80107420_hand_line_sinker);

omObjData *func_80107A3C_hand_line_sinker(void) {
    omObjData *candidates[3];
    omObjData *obj;
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        if (obj->work[0] == 2 || obj->work[0] == 4) {
            continue;
        }
        if (obj->work[0] != 3) {
            candidates[count++] = obj;
        }
    }
    if (count == 0) {
        return NULL;
    }
    if (count == 1) {
        return candidates[0];
    }
    return candidates[rand8() % count];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80107B24_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801080F0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801081D0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108880_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108C5C_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108F44_hand_line_sinker);

f32 func_801092B8_hand_line_sinker(s8 stickX, s8 stickY) {
    f32 angle;
    f32 mag;

    if (stickX == 0 && stickY == 0) {
        return 0.0f;
    }
    angle = atan2df(stickY, stickX);
    mag = fabs(stickX * cosdf(angle)) + fabs(stickY * sindf(angle));
    if (mag > 70.0f) {
        mag = 70.0f;
    }
    return mag;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801093A4_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80109584_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80109B9C_hand_line_sinker);

omObjData *func_8010A554_hand_line_sinker(void) {
    omObjData *closest;
    omObjData *obj;
    f32 minDist;
    f32 dist;
    s32 i;

    minDist = 100000.0f;
    closest = NULL;
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        dist = HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
        if (dist < minDist) {
            minDist = dist;
            closest = obj;
        }
    }
    return closest;
}

void func_8010A5F0_hand_line_sinker(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            D_8010C148_hand_line_sinker[i][j] = func_8000B108_main(D_8010BFA0_hand_line_sinker[i], 0x1A9D);
            if (i == 0) {
                func_8001C2FC_main(D_8010C148_hand_line_sinker[0][j], 0x20000000, 0x20000000);
            }
            D_8010C160_hand_line_sinker[j] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A6D0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A904_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010A9F8_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010AAEC_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010ABD4_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010AD7C_hand_line_sinker);

void func_8010B0FC_hand_line_sinker(omObjData *arg0, f32 arg1) {
    HandLineSinkerObjWork *work;
    f32 ratio;
    f32 volume;

    work = arg0->data;
    ratio = 1.0f - (HuSqrtf((arg0->trans.x - work->pos.x) * (arg0->trans.x - work->pos.x) +
                            (arg0->trans.z - work->pos.z) * (arg0->trans.z - work->pos.z)) /
                    730.0f) *
                       2;
    if (ratio < 0.0f) {
        ratio = 0.0f;
    }
    volume = arg1 + (127.0f - arg1) * ratio;
    if (volume > 127.0f) {
        volume = 127.0f;
    }
    if (work->seNo >= 0) {
        func_8004AAD0_main(work->seNo, volume);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010B1E4_hand_line_sinker);
