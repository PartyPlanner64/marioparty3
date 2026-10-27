#include "common.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/util.h"
#include "mallocblock.h"
#include "overlays/minigame.h"
#include "hand_line_sinker.h"

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

typedef struct HandLineSinkerPlayerWork {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ char unk1[0x28 - 0x1];
    /* 0x28 */ f32 velY;
    /* 0x2C */ u16 splashed;
    /* 0x2E */ char unk2E[0x48 - 0x2E];
} HandLineSinkerPlayerWork; // sizeof 0x48

typedef struct HandLineSinkerFollowWork {
    /* 0x00 */ omObjData *parent;
    /* 0x04 */ Vec offset;
    /* 0x10 */ Vec unk10;
} HandLineSinkerFollowWork; // sizeof 0x1C

extern s16 D_8010C0EC_hand_line_sinker;
extern s16 D_8010C0F0_hand_line_sinker;
extern omObjData *D_8010C0F4_hand_line_sinker;
extern omObjData *D_8010C0F8_hand_line_sinker;
extern s16 D_8010C10C_hand_line_sinker;
extern omObjData **D_8010C100_hand_line_sinker;
extern s32 D_8010BFA0_hand_line_sinker[];
extern s16 D_8010C148_hand_line_sinker[2][6];
extern omObjData *D_8010C160_hand_line_sinker[];
extern omObjFunc D_8010BFA8_hand_line_sinker[];
extern u16 D_8010C104_hand_line_sinker[2];
extern f32 D_8010C108_hand_line_sinker;
extern u8 D_800D6A90_main;
extern f32 D_8010C130_hand_line_sinker;
extern f32 D_8010C134_hand_line_sinker;
extern f32 D_8010C138_hand_line_sinker;
extern f32 D_8010C13C_hand_line_sinker;
extern f32 D_8010C140_hand_line_sinker;
extern omObjData *D_8010C0E0_hand_line_sinker;
extern u16 D_8010C0EE_hand_line_sinker;
extern omObjData *D_8010C0FC_hand_line_sinker;
extern CameraPreset D_8010C110_hand_line_sinker;
extern omObjData *D_8010C190_hand_line_sinker;
extern CameraPreset D_8010BF28_hand_line_sinker;

void func_80105D28_hand_line_sinker(omObjData *);
void func_80105FA4_hand_line_sinker(omObjData *obj);
void func_8001E888_main(s16 model, f32 x, f32 y, u16 arg3, u16 arg4, char *name, s32 arg6);
void func_800335BC_main(char *name, u16 *result);
void func_80106100_hand_line_sinker(omObjData *obj, u16 playerNo);
f32 func_8010ABD4_hand_line_sinker(f32 a);
void func_801081D0_hand_line_sinker(omObjData *obj);
void func_8010A6D0_hand_line_sinker(omObjData *parent, u16 type, Vec *offset, Vec *rot);
omObjData *func_8010A554_hand_line_sinker(void);
void func_800E6F0C_minigame(s32);

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

omObjData *func_801080F0_hand_line_sinker(omObjData *arg0) {
    omObjData *obj;
    s32 i;

    if (func_800E6E8C_minigame() != 2) {
        return NULL;
    }
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        if (obj->work[0] < 2) {
            if (HuSqrtf((arg0->trans.x - obj->trans.x) * (arg0->trans.x - obj->trans.x) +
                        (arg0->trans.z - obj->trans.z) * (arg0->trans.z - obj->trans.z)) < HuSqrtf(8725.0f)) {
                return obj;
            }
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_801081D0_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_80108880_hand_line_sinker);

void func_80108C5C_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work = obj->data;
    Vec pos;
    Vec rot;

    switch (obj->work[0]) {
        case 5:
            obj->rot.x -= 15.0f;
            if (obj->rot.x == -90.0f) {
                obj->work[0] = 6;
            }
            break;
        case 6:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            if (obj->trans.y >= -50.0f && work->splashed == 0) {
                pos.x = obj->trans.x;
                pos.y = -50.0f;
                pos.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &pos, &rot);
                HuAudFXPlay(0x30F);
                work->splashed = 1;
            }
            if (work->velY < 0.0f) {
                obj->work[0] = 7;
            }
            break;
        case 7:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            obj->rot.x += 30.0f;
            if (obj->rot.x > 90.0f) {
                obj->rot.x = 90.0f;
            }
            if (obj->trans.y <= -50.0f) {
                obj->work[0] = 8;
                pos.x = obj->trans.x;
                pos.y = -50.0f;
                pos.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &pos, &rot);
                HuAudFXPlay(0x30F);
            }
            break;
        case 8:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            obj->rot.x -= 20.0f;
            if (obj->rot.x < 0.0f) {
                obj->rot.x = 0.0f;
            }
            if (obj->trans.y <= -240.0f) {
                obj->trans.y = -240.0f;
                obj->work[0] = 0;
                obj->rot.x = 0.0f;
                obj->func = func_801081D0_hand_line_sinker;
            }
            break;
    }
}

void func_80108F44_hand_line_sinker(omObjData *obj) {
    omObjData *other;
    f32 angle;
    f32 diff;
    f32 x;
    f32 z;
    f32 dist;
    f32 dx;
    f32 dz;
    s32 hit;
    s32 inRange;
    s32 i;

    angle = atan2df(-obj->trans.x, -obj->trans.z);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    if (angle != obj->rot.y) {
        if (obj->rot.y != angle) {
            diff = angle - obj->rot.y;
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                if (diff > 4.0f) {
                    obj->rot.y = obj->rot.y + 4.0f;
                } else {
                    obj->rot.y = diff + obj->rot.y;
                }
            } else {
                if (360.0f - diff > 4.0f) {
                    obj->rot.y -= 4.0f;
                } else {
                    obj->rot.y -= 360.0f - diff;
                }
            }
            if (obj->rot.y < 0.0f) {
                obj->rot.y += 360.0f;
            }
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
        }
        return;
    }

    dx = sindf(angle) * 20.0f;
    dz = cosdf(angle) * 20.0f;
    x = dx + obj->trans.x;
    z = dz + obj->trans.z;
    hit = 0;
    for (i = 0; i < 3; i++) {
        other = D_8010C100_hand_line_sinker[i];
        if (obj == other || obj->work[0] == 2) {
            continue;
        }
        dist = HuSqrtf((other->trans.x - x) * (other->trans.x - x) + (other->trans.z - z) * (other->trans.z - z));
        if (dist < 270.0f) {
            x -= sindf(obj->rot.y) * (270.0f - dist);
            z -= cosdf(obj->rot.y) * (270.0f - dist);
            if (D_8010C100_hand_line_sinker[i]->work[3] == 1) {
                hit = 1;
            }
            break;
        }
    }
    omSetTra(obj, x, obj->trans.y, z);
    inRange = HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) < 300.0f;
    if (inRange | hit) {
        obj->func = NULL;
        obj->work[3] = 1;
    }
}

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

void func_801093A4_hand_line_sinker(void) {
    HandLineSinkerPlayerWork *work;

    switch (D_8010C0EE_hand_line_sinker) {
        case 0:
            WipeCreateIn(0xFF, 0x10);
            D_8010C0E0_hand_line_sinker = func_8010A554_hand_line_sinker();
            D_8010C110_hand_line_sinker.center.x = D_8010C0E0_hand_line_sinker->trans.x;
            D_8010C110_hand_line_sinker.center.y = D_8010C0E0_hand_line_sinker->trans.y;
            D_8010C110_hand_line_sinker.center.z = D_8010C0E0_hand_line_sinker->trans.z;
            D_8010C110_hand_line_sinker.rot = D_8010BF28_hand_line_sinker.rot;
            D_8010C110_hand_line_sinker.rot.x = 328.0f;
            D_8010C110_hand_line_sinker.zoom = 1250.0f;
            func_8010B5EC_hand_line_sinker(&D_8010C110_hand_line_sinker, &D_8010BF28_hand_line_sinker, 37);
            D_8010C0EE_hand_line_sinker = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                work = D_8010C0E0_hand_line_sinker->data;
                work->velY = 60.0f;
                work->splashed = 0;
                D_8010C0EE_hand_line_sinker = 3;
                HuAudFXPlay(0x305);
            }
            break;
        case 2:
            if (D_8010C0E0_hand_line_sinker->work[0] == 0) {
                D_8010C0EE_hand_line_sinker = 3;
            }
            break;
        case 3:
            D_8010C190_hand_line_sinker->work[1] = 1;
            if (D_8010C190_hand_line_sinker->work[0] == 0) {
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[8]].unk02, 0, 30, 3);
                omDelObj(D_8010C190_hand_line_sinker);
                D_8010C190_hand_line_sinker = NULL;
                omDelObj(D_8010C0F4_hand_line_sinker);
                func_800E6F0C_minigame(1);
            }
            break;
    }
}

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

void func_8010A6D0_hand_line_sinker(omObjData *parent, u16 type, Vec *offset, Vec *rot) {
    HandLineSinkerFollowWork *work;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010C160_hand_line_sinker[i] == NULL) {
            break;
        }
    }
    if (i == 6) {
        return;
    }
    D_8010C160_hand_line_sinker[i] = omAddObj(0x28, 1, 0, -1, D_8010BFA8_hand_line_sinker[type]);
    D_8010C160_hand_line_sinker[i]->data = HuMemAllocTag(sizeof(HandLineSinkerFollowWork), 0x7918);
    work = D_8010C160_hand_line_sinker[i]->data;
    D_8010C160_hand_line_sinker[i]->work[0] = i;
    func_8001C258_main(D_8010C148_hand_line_sinker[type][i], 4, 0);
    D_8010C160_hand_line_sinker[i]->model[0] = D_8010C148_hand_line_sinker[type][i];
    func_8001C6A8_main(D_8010C160_hand_line_sinker[i]->model[0], 0);
    work->parent = parent;
    work->offset = *offset;
    work->unk10 = *rot;
    if (parent == NULL) {
        omSetTra(D_8010C160_hand_line_sinker[i], offset->x, offset->y, offset->z);
    } else {
        omSetTra(D_8010C160_hand_line_sinker[i], parent->trans.x + offset->x, parent->trans.y + offset->y,
                 parent->trans.z + offset->z);
    }
    omSetRot(D_8010C160_hand_line_sinker[i], rot->x, rot->y, rot->z);
    Hu3DModelPosSet(D_8010C160_hand_line_sinker[i]->model[0], D_8010C160_hand_line_sinker[i]->trans.x,
                    D_8010C160_hand_line_sinker[i]->trans.y, D_8010C160_hand_line_sinker[i]->trans.z);
    Hu3DModelRotSet(D_8010C160_hand_line_sinker[i]->model[0], D_8010C160_hand_line_sinker[i]->rot.x,
                    D_8010C160_hand_line_sinker[i]->rot.y, D_8010C160_hand_line_sinker[i]->rot.z);
}

void func_8010A904_hand_line_sinker(omObjData *obj) {
    HandLineSinkerFollowWork *work = obj->data;

    if (work->parent != NULL) {
        omSetTra(obj, work->parent->trans.x + work->offset.x, work->parent->trans.y + work->offset.y,
                 work->parent->trans.z + work->offset.z);
    }
    if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
        func_8001C258_main(obj->model[0], 4, 4);
        D_8010C160_hand_line_sinker[obj->work[0]] = 0;
        omDelObj(obj);
    }
}

void func_8010A9F8_hand_line_sinker(omObjData *obj) {
    HandLineSinkerFollowWork *work = obj->data;

    if (work->parent != NULL) {
        omSetTra(obj, work->parent->trans.x + work->offset.x, work->parent->trans.y + work->offset.y,
                 work->parent->trans.z + work->offset.z);
    }
    if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
        func_8001C258_main(obj->model[0], 4, 4);
        D_8010C160_hand_line_sinker[obj->work[0]] = 0;
        omDelObj(obj);
    }
}

f32 func_8010AAEC_hand_line_sinker(f32 x) {
    f32 fx;
    f32 slope;
    f32 prev;
    s32 i;

    for (i = 0; i < 64; i++) {
        fx = func_8010ABD4_hand_line_sinker(x);
        if (fx == 0.0f) {
            break;
        }
        slope = (func_8010ABD4_hand_line_sinker(x + fx) - fx) / fx;
        if (slope < 1e-10f) {
            break;
        }
        prev = x;
        x -= fx / slope;
        if (fabs((x - prev) / x) < 1e-6f) {
            break;
        }
    }
    return x;
}

#ifdef NON_MATCHING
/* Only difference: the target has an extra nop between the second logf call's delay slot and the
 * following mul.s (assembler vr4300 mul fix, likely triggered by a label at that point in the original). */
f32 func_8010ABD4_hand_line_sinker(f32 a) {
    f32 b;
    f32 t;
    f32 s;
    f32 start;
    f32 end;

    b = (D_8010C140_hand_line_sinker - D_8010C138_hand_line_sinker) /
            (D_8010C13C_hand_line_sinker - D_8010C134_hand_line_sinker) -
        a * (D_8010C134_hand_line_sinker + D_8010C13C_hand_line_sinker);

    t = 2.0f * a * D_8010C134_hand_line_sinker + b;
    s = HuSqrtf(t * t + 1.0f);
    if (t + s > 0.0f) {
        start = t * s + logf(t + s);
    } else {
        start = t * s - 1.0f;
    }

    t = 2.0f * a * D_8010C13C_hand_line_sinker + b;
    s = HuSqrtf(t * t + 1.0f);
    if (t + s > 0.0f) {
        end = t * s + logf(t + s);
    } else {
        end = t * s - 1.0f;
    }

    if (a != 0.0f) {
        end = (end - start) / (a * 4.0f) - D_8010C130_hand_line_sinker;
    } else {
        end = -D_8010C130_hand_line_sinker;
    }
    return end;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010ABD4_hand_line_sinker);
#endif

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
