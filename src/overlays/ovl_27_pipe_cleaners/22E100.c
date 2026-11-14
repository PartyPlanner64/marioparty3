#include "common.h"
#include "overlays/minigame.h"
#include "overlays/ovl_27.h"

// Per-pipe state used by the pipe cleaners (D_8010AB30_pipe_cleaners, one entry per pipe).
typedef struct PipeCleanerWork {
    /* 0x00 */ s32 motionId;
    /* 0x04 */ omObjData *object;
    /* 0x08 */ s32 counter;
    /* 0x0C */ s32 rank;
    /* 0x10 */ s32 state;
    /* 0x14 */ f32 rotX;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ Vec pos;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
} PipeCleanerWork; // Size 0x38

// Sprite/HUD work entries (D_8010A300_pipe_cleaners); same layout as other minigames' 0x84 work pools.
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
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s16 spriteFileId;
    /* 0x42 */ s16 espId;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} PipeCleanerSpriteWork; // Size 0x84

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rotZ;
} PipeCleanerPipePlacement; // Size 0x10

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ omObjData *obj;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} PipeCleanerSlot; // Size 0x1C

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 rotZ;
    /* 0x10 */ s32 dir;
} PipeCleanerSpawnPos; // Size 0x14

typedef struct {
    /* 0x00 */ s32 espId;
    /* 0x04 */ s32 state;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 alpha;
    /* 0x10 */ s32 unk10;
} PipeCleanerSign; // Size 0x14

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} PipeCleanerCamera; // Size 0x2C

extern s32 D_800A178C_main[][6];

extern s32 D_80109EC0_pipe_cleaners[4][3];
extern PipeCleanerPipePlacement D_80109EF0_pipe_cleaners[4];
extern u16 D_80109F30_pipe_cleaners[8][3];
extern char *D_80109F60_pipe_cleaners[];
extern PipeCleanerSpawnPos D_80109F80_pipe_cleaners[4];
extern f32 D_80109FD0_pipe_cleaners[16];
extern s32 D_8010A010_pipe_cleaners[4][2];
extern s16 D_8010A030_pipe_cleaners;
extern s32 D_8010A034_pipe_cleaners;
extern s32 D_8010A038_pipe_cleaners;
extern s32 D_8010A03C_pipe_cleaners;
extern PipeCleanerCamera D_8010A040_pipe_cleaners[4];
extern const s16 D_8010A2A8_pipe_cleaners[];
extern void *D_8010A2B0_pipe_cleaners[4][3];
extern s16 D_8010A2E0_pipe_cleaners[4];
extern s32 D_8010A2F0_pipe_cleaners;
extern PipeCleanerSpriteWork D_8010A300_pipe_cleaners[10];
extern s32 D_8010A828_pipe_cleaners;
extern s32 D_8010A82C_pipe_cleaners;
extern s16 D_8010A830_pipe_cleaners[4];
extern s8 D_8010A838_pipe_cleaners[4][60];
extern PipeCleanerSlot D_8010A968_pipe_cleaners[16];
extern omObjData *D_8010AB28_pipe_cleaners;
extern PipeCleanerWork D_8010AB30_pipe_cleaners[4];
extern s32 D_8010AC10_pipe_cleaners;
extern s32 D_8010AC14_pipe_cleaners;
extern PipeCleanerSign D_8010AC18_pipe_cleaners[16];
extern s32 D_8010AD58_pipe_cleaners;

void func_80105C50_pipe_cleaners(omObjData *obj);
void func_801066E4_pipe_cleaners(omObjData *obj);
void func_80106FD8_pipe_cleaners(omObjData *obj, u16 chr, f32 time, s32 motion);
void func_80107598_pipe_cleaners(omObjData *obj);
void func_80108708_pipe_cleaners(void);
void func_80108964_pipe_cleaners(PipeCleanerSign *sign, s32 arg1);
void func_80109D70_pipe_cleaners(void);

void func_801059A0_pipe_cleaners(void) {
    func_80109D70_pipe_cleaners();
}

f32 func_801059BC_pipe_cleaners(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_pipe_cleaners(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_pipe_cleaners(void) {
    PipeCleanerSpriteWork *work;
    u32 i;

    for (i = 0, work = D_8010A300_pipe_cleaners; i < 10; i++, work++) {
        work->obj = NULL;
        work->unk04 = 0;
        work->unk06 = 0;
        work->unk08 = 0;
        work->unk0A = 0;
        work->unk0C = 0;
        work->unk0E = 0;
        work->unk10 = 0;
        work->unk12 = 0;
        work->unk14 = 0;
        work->unk16 = 0;
        work->unk18 = 0;
        work->unk1C = 0;
        work->unk20 = 0;
        work->unk24 = 0;
        work->unk28 = 0;
        work->unk2C = 0;
        work->unk30 = 0;
        work->unk34 = 0;
        work->unk38 = 0;
        work->unk3C = 0;
        work->spriteFileId = -1;
        work->espId = -1;
        work->pos.x = work->pos.y = work->pos.z = 0.0f;
        work->unk50.x = work->unk50.y = work->unk50.z = 0.0f;
        work->unk5C.x = work->unk5C.y = work->unk5C.z = 0.0f;
        work->unk68 = 0.0f;
        work->unk6C = 0.0f;
        work->unk70 = 0.0f;
        work->unk74 = 0.0f;
        work->unk78.x = work->unk78.y = work->unk78.z = 0.0f;
    }
}

void func_80105B3C_pipe_cleaners(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105BB4_pipe_cleaners(omObjData *obj) {
    PipeCleanerSpriteWork *work = D_8010A300_pipe_cleaners;

    espPosSet(work[0].espId, work[0].pos.x, work[0].pos.y);
    espPosSet(work[1].espId, work[1].pos.x, work[1].pos.y);
}

void func_80105C50_pipe_cleaners(omObjData *obj) {
    PipeCleanerSpriteWork *work;

    work = &D_8010A300_pipe_cleaners[1];
    work->pos.x = 160.0f;
    work->pos.y = 120.0f;
    work->spriteFileId = func_8000B838_main(0x48000C);
    work->espId = espEntry(work->spriteFileId, 0, 0);
    espAttrSet(work->espId, 0x5000);
    espPosSet(work->espId, work->pos.x, work->pos.y);

    work = &D_8010A300_pipe_cleaners[0];
    work->pos.x = 160.0f;
    work->pos.y = 120.0f;
    work->spriteFileId = func_8000B838_main(0x48000A);
    work->espId = espEntry(work->spriteFileId, 0, 0);
    espAttrSet(work->espId, 0x1000);
    espPosSet(work->espId, work->pos.x, work->pos.y);
    obj->func = func_80105BB4_pipe_cleaners;
}

void func_80105DB4_pipe_cleaners(void) {
    omAddObj(0x64, 1, 0, -1, func_80105C50_pipe_cleaners);
}

void func_80105DE8_pipe_cleaners(omObjData *object) {
}

void func_80105DF0_pipe_cleaners(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x480001, 0x299);
    obj->model[1] = func_8000B108_main(0x480002, 0x299);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_80105DE8_pipe_cleaners;
}

void func_80105E60_pipe_cleaners(void) {
    omAddObj(0x6E, 2, 0, -1, func_80105DF0_pipe_cleaners);
}

void func_80105E94_pipe_cleaners(s32 arg0) {
    s16 modelId = D_8010A830_pipe_cleaners[arg0];

    func_8001C258_main(D_800CBB60_main[modelId].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_800146DC_main(modelId, 1, 0);
}

void func_80105EF8_pipe_cleaners(omObjData *obj) {
}

void func_80105F00_pipe_cleaners(omObjData *obj) {
    s16 *spritePtr = &D_8010A830_pipe_cleaners[obj->work[0]];
    void *data;
    s32 animId;
    s16 sprite;

    data = DataRead(0xB);
    animId = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    sprite = Hu3DSprModelCreate((void *)-1, 0x2A4, 0x10);
    func_800147FC_main(sprite, 0xFF, 0xFF, 0xFF);
    func_800146DC_main(sprite, 1, 1);
    D_800CBB60_main[sprite].unk_02 = animId;
    func_8001C258_main(D_800CBB60_main[sprite].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(D_800CBB60_main[sprite].modelId, -60.0f, 180.0f, 0.0f);
    Hu3DModelScaleSet(D_800CBB60_main[sprite].modelId, 3.0f, 3.0f, 3.0f);
    func_8001C814_main(D_800CBB60_main[sprite].modelId, 2, 2);
    Hu3DModelCameraSet(D_800CBB60_main[sprite].modelId, 1 << obj->work[0]);
    *spritePtr = sprite;
    obj->func = func_80105EF8_pipe_cleaners;
}

void func_80106078_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1F4, 1, 0, -1, func_80105F00_pipe_cleaners)->work[0] = i;
    }
}

void func_801060D4_pipe_cleaners(s32 arg0) {
    s32 *state = &D_8010A928_pipe_cleaners[arg0];

    if (*state == 0) {
        *state = 1;
    }
}

void func_801060FC_pipe_cleaners(omObjData *obj) {
    s32 *state = &D_8010A928_pipe_cleaners[obj->work[0]];

    if (*state == 0) {
        return;
    }
    if (*state == 1) {
        func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C5B4_main(obj->model[0], D_8010AB28_pipe_cleaners->motion[0]);
        func_8001C814_main(obj->model[0], 2, 2);
        Hu3DMotionTimeSet(obj->model[0], 0.0f);
        *state = 2;
    } else if (Hu3DData[obj->model[0]].motTime == 0.0f) {
        func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C814_main(obj->model[0], 1, 1);
        *state = 0;
    }
}

void func_80106204_pipe_cleaners(omObjData *obj) {
    D_8010A928_pipe_cleaners[obj->work[0]] = 0;
    if (obj->work[0] == 0) {
        obj->model[0] = func_8000B108_main(0x480004, 0x299);
        D_8010AC14_pipe_cleaners = obj->model[0];
        func_8000B460_main(obj, 0, 0x480005);
        D_8010AB28_pipe_cleaners = obj;
    } else {
        obj->model[0] = Hu3DModelLink(D_8010AC14_pipe_cleaners);
    }
    obj->trans.x = D_80109EF0_pipe_cleaners[obj->work[0] & 3].x;
    obj->trans.y = D_80109EF0_pipe_cleaners[obj->work[0] & 3].y;
    obj->trans.z = D_80109EF0_pipe_cleaners[obj->work[0] & 3].z;
    obj->rot.z = D_80109EF0_pipe_cleaners[obj->work[0] & 3].rotZ;
    func_8001C5B4_main(obj->model[0], D_8010AB28_pipe_cleaners->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], 1 << (obj->work[0] >> 2));
    obj->func = func_801060FC_pipe_cleaners;
}

void func_8010638C_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        omAddObj(0x190, 1, 1, -1, func_80106204_pipe_cleaners)->work[0] = i;
    }
}

void func_801063E8_pipe_cleaners(omObjData *obj, s32 slot) {
    slot &= 3;
    if (slot == 0) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x4000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 60;
    } else if (slot == 1) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x8000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = 60;
    } else if (slot == 2) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x4000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -60;
    } else if (slot == 3) {
        D_800D5558_main[GwPlayer[obj->work[0]].pad] = 0x8000;
        D_800D20A1_main[GwPlayer[obj->work[0]].pad] = -60;
    }
}

// NON_MATCHING: t1/t2 register swap for the hoisted -1 constant and the (mode == 0) test.
#ifdef NON_MATCHING
s32 func_80106540_pipe_cleaners(omObjData *obj, u32 mode) {
    PipeCleanerSlot *slot;
    s32 idx;
    u32 i;
    s32 found[4];

    for (i = 0; i < 4; i++) {
        found[i] = -2;
    }
    for (i = 0; i < 4; i++) {
        idx = obj->work[0] * 4 + i;
        slot = &D_8010A968_pipe_cleaners[idx];
        switch (mode) {
            case 0:
                switch (slot->state) {
                    case 0:
                    case 1:
                    case 3:
                    case 4:
                        break;
                    case 2:
                        return idx;
                }
                break;
            case 1:
                switch (slot->state) {
                    case 0:
                    case 3:
                    case 4:
                        break;
                    case 1:
                    case 2:
                        return idx;
                }
                break;
            case 2:
                switch (slot->state) {
                    case 0:
                    case 4:
                        break;
                    case 1:
                    case 2:
                        found[i] = -1;
                        break;
                    case 3:
                        found[i] = slot->unk14;
                        break;
                }
                break;
        }
    }
    if (mode == 2) {
        for (i = 0; i < 4; i++) {
            if (found[i] >= 0 && found[i] < 4) {
                return obj->work[0] * 4 + i;
            }
        }
        for (i = 0; i < 4; i++) {
            if (found[i] == -1) {
                return obj->work[0] * 4 + i;
            }
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106540_pipe_cleaners);
#endif

// NON_MATCHING: the else branch is tail-merged into the identical code in the first branch; the target keeps
// two copies.
#ifdef NON_MATCHING
void func_801066E4_pipe_cleaners(omObjData *obj) {
    PipeCleanerWork *work;
    s32 slot;

    func_80105B3C_pipe_cleaners(obj->work[0]);
    work = &D_8010AB30_pipe_cleaners[obj->work[0]];
    if (work->motionId != 0) {
        return;
    }
    if (work->unk34 != 0) {
        work->unk34--;
        return;
    }
    if (rand8() % work->unk28 == 0) {
        slot = func_80106540_pipe_cleaners(obj, rand8() % 3);
        if (slot == -1) {
            return;
        }
        if (rand8() % work->unk2C == 0) {
            func_801063E8_pipe_cleaners(obj, slot);
        } else {
            slot = (rand8() & 3) + obj->work[0] * 4;
            if (rand8() % work->unk2C != 0) {
                func_801063E8_pipe_cleaners(obj, slot);
            }
        }
        work->unk34 = (rand8() % work->unk30) * 5;
    } else {
        slot = (rand8() & 3) + obj->work[0] * 4;
        if (rand8() % work->unk2C != 0) {
            func_801063E8_pipe_cleaners(obj, slot);
        }
        work->unk34 = (rand8() % work->unk30) * 5;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801066E4_pipe_cleaners);
#endif

void func_8010698C_pipe_cleaners(omObjData *obj, u8 anim) {
    s8 chr = GwPlayer[obj->work[0]].chr;

    Hu3DAnimKill(D_8010A2E0_pipe_cleaners[obj->work[0]]);
    D_8010A2E0_pipe_cleaners[obj->work[0]] = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010A2B0_pipe_cleaners[obj->work[0]][anim], 0, D_80109F60_pipe_cleaners[chr]);
}

void func_80106A70_pipe_cleaners(omObjData *obj, s32 motion) {
    if (motion == 0) {
        s16 motId = Hu3DData[obj->motion[0] & 0x3FFF].motId;

        Hu3DMotionShapeSet(obj->model[0], motId, 2);
    } else {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        Hu3DData[obj->model[0]].motIdShape = 0xFF;
    }
}

void func_80106B18_pipe_cleaners(omObjData *obj, PipeCleanerWork *work) {
    work->pos.x = -60.0f;
    work->pos.y = 150.0f;
    work->pos.z = 0.0f;
    work->rotX = 0.0f;
    func_8001C258_main(work->object->model[2], 0x4000, HU3D_ATTR_NONE);
    Hu3DModelPosSet(obj->model[2], work->pos.x, work->pos.y, work->pos.z);
    Hu3DModelRotSet(obj->model[2], work->rotX, 0.0f, 0.0f);
    func_80106A70_pipe_cleaners(work->object, 7);
    func_8001C814_main(work->object->model[0], 2, 2);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    work->motionId = 7;
    work->state = 1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A134_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A140_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A14C_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A158_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A164_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A170_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A17C_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A188_pipe_cleaners);

void func_80106BF8_pipe_cleaners(omObjData *obj, PipeCleanerWork *work) {
    work->pos.y += 10.0;
    work->rotX += 46.0;
    Hu3DModelPosSet(obj->model[2], work->pos.x, work->pos.y, work->pos.z);
    Hu3DModelRotSet(obj->model[2], work->rotX, 0.0f, 0.0f);
    if (work->pos.y >= 240.0) {
        work->state = 2;
    }
}

void func_80106CB4_pipe_cleaners(omObjData *obj, PipeCleanerWork *work) {
    func_8001C258_main(work->object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    work->state = 3;
}

void func_80106CF4_pipe_cleaners(PipeCleanerWork *work) {
    s32 dir = D_800A178C_main[GwPlayer[work->object->work[0]].chr][0];

    func_80106A70_pipe_cleaners(work->object, 5);
    func_8001C814_main(work->object->model[0], 2, 2);
    Hu3DMotionTimeSet(work->object->model[0], 0.0f);
    work->motionId = 5;
    func_80045ED0_main(dir | 0x2F);
    func_8010698C_pipe_cleaners(work->object, 1);
}

void func_80106DA4_pipe_cleaners(PipeCleanerWork *work) {
    func_80106A70_pipe_cleaners(work->object, 6);
    func_8001C814_main(work->object->model[0], 2, 2);
    Hu3DMotionTimeSet(work->object->model[0], 0.0f);
    work->motionId = 6;
    func_8010698C_pipe_cleaners(work->object, 2);
}

void func_80106E10_pipe_cleaners(omObjData *obj) {
    PipeCleanerWork *work = &D_8010AB30_pipe_cleaners[obj->work[0]];

    if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] > 50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000)) {
        func_80106A70_pipe_cleaners(obj, 1);
        work->motionId = 2;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] < -50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x8000)) {
        func_80106A70_pipe_cleaners(obj, 3);
        work->motionId = 4;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] > 50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x4000)) {
        func_80106A70_pipe_cleaners(obj, 2);
        work->motionId = 1;
    } else if (D_800D20A1_main[GwPlayer[obj->work[0]].pad] < -50 && (D_800D5558_main[GwPlayer[obj->work[0]].pad] & 0x4000)) {
        func_80106A70_pipe_cleaners(obj, 4);
        work->motionId = 3;
    }
    func_8001C814_main(obj->model[0], 2, 2);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
}

// NON_MATCHING: the |time - 20| branches are laid out differently (target keeps an explicit jump over the
// else block).
#ifdef NON_MATCHING
void func_80106FD8_pipe_cleaners(omObjData *obj, u16 chr, f32 time, s32 motion) {
    f32 base;
    f32 range;
    f32 scale;

    range = base = 1.0f;
    if (motion < 3) {
        range = 40.0f;
        base = 0.5f;
    } else {
        switch (chr) {
            case 0:
            case 2:
            case 7:
                range = 50.0f;
                base = 0.6f;
                break;
            case 5:
                if (motion != 3) {
                    range = 100.0f;
                    base = 0.8f;
                    break;
                }
            case 1:
            case 4:
            case 6:
                range = 0.0f;
                base = 1.0f;
                break;
            case 3:
                range = 100.0f;
                base = 0.8f;
                break;
        }
    }
    if (range == 0.0f) {
        Hu3DModelScaleSet(obj->model[1], base, 1.0f, base);
    } else {
        scale = (time < 20.0f) ? 20.0f - time : time - 20.0f;
        Hu3DModelScaleSet(obj->model[1], base + scale / range, 1.0f, base + scale / range);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106FD8_pipe_cleaners);
#endif

void func_80107114_pipe_cleaners(omObjData *obj) {
    PipeCleanerWork *work = &D_8010AB30_pipe_cleaners[obj->work[0]];
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0] * 4 + (work->motionId - 1)];
    f32 time = Hu3DData[obj->model[0]].motTime;

    if (time == 16.0f) {
        if (slot->state != 0 && slot->state != 4) {
            slot->unk04 = 4;
            slot->unk10 = 0;
            func_801060D4_pipe_cleaners(obj->work[0] * 4 + (work->motionId - 1));
            HuAudFXPlay(0x436);
            func_8004AC98_main(0x437, obj->work[0]);
            func_8001C814_main(obj->model[0], 4, 4);
            work->counter++;
            if (!(GwPlayer[obj->work[0]].stat & 1)) {
                omVibrate(obj->work[0], 10, 0, 10);
            }
        }
    } else if (Hu3DData[obj->model[0]].motTime == 0.0f) {
        func_80106A70_pipe_cleaners(obj, 0);
        func_8001C814_main(obj->model[0], 2, 2);
        Hu3DMotionTimeSet(obj->model[0], 0.0f);
        work->motionId = 0;
    }
    func_80106FD8_pipe_cleaners(obj, GwPlayer[obj->work[0]].chr, time, work->motionId);
}

void func_8010731C_pipe_cleaners(omObjData *obj) {
    s16 modelId = obj->model[0];

    if (Hu3DData[modelId].motTime == D_800CCF58_main[Hu3DData[modelId].motId].unk02 - 2) {
        func_8001C814_main(modelId, 1, 1);
    }
}

void func_801073A4_pipe_cleaners(omObjData *obj) {
    s16 modelId = obj->model[0];

    if (Hu3DData[modelId].motTime == D_800CCF58_main[Hu3DData[modelId].motId].unk02 - 2) {
        func_8001C814_main(modelId, 1, 1);
    }
}

void func_8010742C_pipe_cleaners(omObjData *obj) {
    PipeCleanerWork *work;

    if (GwPlayer[obj->work[0]].stat & 1) {
        func_801066E4_pipe_cleaners(obj);
    }
    if (D_8010A2F0_pipe_cleaners != 2) {
        func_80105B3C_pipe_cleaners(obj->work[0]);
    }
    work = &D_8010AB30_pipe_cleaners[obj->work[0]];
    switch (work->motionId) {
        case 0:
            func_80106E10_pipe_cleaners(obj);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            func_80107114_pipe_cleaners(obj);
            break;
        case 5:
            func_8010731C_pipe_cleaners(obj);
            break;
        case 6:
            func_801073A4_pipe_cleaners(obj);
            break;
    }
    if (D_8010A2F0_pipe_cleaners == 4) {
        switch (work->state) {
            case 0:
                func_80106B18_pipe_cleaners(obj, work);
                break;
            case 1:
                func_80106BF8_pipe_cleaners(obj, work);
                break;
            case 2:
                func_80106CB4_pipe_cleaners(obj, work);
                func_80105E94_pipe_cleaners(obj->work[0]);
                break;
        }
    }
}

void func_80107598_pipe_cleaners(omObjData *obj) {
    PipeCleanerWork *work = &D_8010AB30_pipe_cleaners[obj->work[0]];
    u16 chr;
    u8 difficulty;
    s32 dir;
    s32 i;

    work->motionId = 0;
    work->object = obj;
    work->counter = 0;
    work->rank = 0;
    work->state = 0;
    work->rotX = 0;
    work->unk18 = 0;
    work->pos.x = work->pos.y = work->pos.z = 0.0f;
    chr = GwPlayer[obj->work[0]].chr;
    dir = D_800A178C_main[chr][0];
    obj->model[0] = func_8000B108_main(dir | D_800A178C_main[chr][2], 0x2A9);
    for (i = 0; i < 3; i++) {
        D_8010A2B0_pipe_cleaners[obj->work[0]][i] = DataRead(dir | D_80109F30_pipe_cleaners[chr][i]);
    }
    D_8010A2E0_pipe_cleaners[obj->work[0]] = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010A2B0_pipe_cleaners[obj->work[0]][0], 0, D_80109F60_pipe_cleaners[chr]);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x18));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x68));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x69));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x6A));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x6B));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0));
    func_80106A70_pipe_cleaners(obj, 0);
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 10.0f, 50.0f);
    obj->trans.x = 0;
    obj->trans.y = 0;
    obj->trans.z = 0;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[2] = func_8000B108_main(0x480003, 0x299);
    func_8001C258_main(obj->model[2], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[2], obj->model[0], "item_hook");
    Hu3DModelCameraSet(obj->model[0], 1 << obj->work[0]);
    Hu3DModelCameraSet(obj->model[1], 1 << obj->work[0]);
    Hu3DModelCameraSet(obj->model[2], 1 << obj->work[0]);
    difficulty = GwPlayer[obj->work[0]].cpu_difficulty;
    work->unk28 = D_80109EC0_pipe_cleaners[difficulty][0];
    work->unk2C = D_80109EC0_pipe_cleaners[difficulty][1];
    work->unk30 = D_80109EC0_pipe_cleaners[difficulty][2];
    work->unk34 = (rand8() % work->unk30) * 5;
    obj->func = func_8010742C_pipe_cleaners;
}

void func_80107A48_pipe_cleaners(void) {
    u16 player = 0;
    s16 i;

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
        omAddObj(0x12C, 9, 0x3C, -1, func_80107598_pipe_cleaners)->work[0] = player;
    }
}

void func_80107B28_pipe_cleaners(omObjData *obj) {
    PipeCleanerSpawnPos *spawn = &D_80109F80_pipe_cleaners[obj->work[0] & 3];
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (slot->unk10 != 0) {
        return;
    }
    slot->unk10 = 1;
    obj->trans.x = spawn->pos.x;
    obj->trans.y = spawn->pos.y;
    obj->trans.z = spawn->pos.z;
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 1, 1);
    Hu3DModelScaleSet(obj->model[0], 0.1f, 0.1f, 0.1f);
    Hu3DAnimBankSet(obj->work[1], 0);
}

void func_80107C08_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (slot->unk10 == 0) {
        slot->unk10 = 1;
        slot->unk14 = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        func_8001C814_main(obj->model[0], 2, 2);
        Hu3DMotionTimeSet(obj->model[0], 0.0f);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
        func_80034048_main(obj->work[1], 0);
        func_80032FC0_main(obj->work[1], 1, 0);
    }
    obj->trans.y += D_80109FD0_pipe_cleaners[slot->unk14] * D_80109F80_pipe_cleaners[obj->work[0] & 3].dir;
    if (slot->unk14 == 14) {
        func_8001C814_main(obj->model[0], 1, 1);
        switch (slot->unk0C) {
            case 0:
            case 2:
                slot->unk04 = 2;
                break;
            case 1:
                slot->unk04 = 3;
                break;
        }
        slot->unk10 = 0;
    }
    slot->unk14++;
}

void func_80107D84_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];
    s32 duration;

    if (slot->unk10 == 0) {
        slot->unk10 = 1;
        slot->unk14 = 0;
        func_8001C814_main(obj->model[0], 1, 1);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
    }
    duration = 119;
    if (slot->unk0C == 0) {
        duration = 29;
    }
    if (slot->unk14 == duration) {
        slot->unk04 = 3;
        slot->unk10 = 0;
    }
    slot->unk14++;
}

void func_80107E3C_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];
    s32 done;

    if (slot->unk10 == 0) {
        slot->unk10 = 1;
        slot->unk14 = 0;
        if (slot->unk18 == 0) {
            func_8001C5B4_main(obj->model[0], obj->motion[0]);
            func_8001C814_main(obj->model[0], 4, 4);
            Hu3DMotionTimeSet(obj->model[0], 30.0f);
            Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
            Hu3DAnimBankSet(obj->work[1], 1);
        }
    }
    obj->trans.y -= D_80109FD0_pipe_cleaners[slot->unk14] * D_80109F80_pipe_cleaners[obj->work[0] & 3].dir;
    done = FALSE;
    if (D_80109F80_pipe_cleaners[obj->work[0] & 3].dir == -1) {
        if (D_80109F80_pipe_cleaners[obj->work[0] & 3].pos.y <= obj->trans.y) {
            done = TRUE;
        }
    } else if (obj->trans.y <= D_80109F80_pipe_cleaners[obj->work[0] & 3].pos.y) {
        done = TRUE;
    }
    if (slot->unk14 >= 14 || done) {
        func_8001C814_main(obj->model[0], 1, 1);
        Hu3DModelScaleSet(obj->model[0], 0.1f, 0.1f, 0.1f);
        slot->unk04 = 0;
        slot->unk10 = 0;
        slot->unk18 = 0;
    }
    slot->unk14++;
}

void func_8010801C_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];

    if (slot->unk10 == 0) {
        slot->unk10 = 1;
        slot->unk14 = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 2);
        Hu3DMotionTimeSet(obj->model[0], 0.0f);
        Hu3DModelScaleSet(obj->model[0], 1.0f, 1.0f, 1.0f);
        Hu3DAnimBankSet(obj->work[1], 2);
        slot->unk04 = 3;
        slot->unk10 = 0;
        slot->unk18 = 1;
    }
    slot->unk14++;
}

void func_801080F4_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];

    slot->state = slot->unk04;
    switch (slot->state) {
        case 0:
            func_80107B28_pipe_cleaners(obj);
            break;
        case 1:
            func_80107C08_pipe_cleaners(obj);
            break;
        case 2:
            func_80107D84_pipe_cleaners(obj);
            break;
        case 3:
            func_80107E3C_pipe_cleaners(obj);
            break;
        case 4:
            func_8010801C_pipe_cleaners(obj);
            break;
    }
}

void func_80108194_pipe_cleaners(omObjData *obj) {
    PipeCleanerSlot *slot = &D_8010A968_pipe_cleaners[obj->work[0]];
    void *data;

    obj->model[0] = func_8000B108_main(0x480006, 0x289);
    func_8000B460_main(obj, 0, 0x480007);
    func_8000B460_main(obj, 1, 0x480008);
    if (obj->work[0] == 0) {
        data = DataRead(0x480009);
        obj->work[1] = D_8010A828_pipe_cleaners = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "s239_001_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->work[1] = Hu3DAnimLink(Hu3DData[obj->model[0]].hmf, D_8010A828_pipe_cleaners, 0, "s239_001_DEF");
    }
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_80034048_main(obj->work[1], 0);
    func_80032FC0_main(obj->work[1], 1, 1);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 1, 1);
    slot->obj = obj;
    slot->state = 0;
    slot->unk04 = 0;
    slot->unk14 = 0;
    slot->unk10 = 0;
    slot->unk0C = 0;
    slot->unk18 = 0;
    obj->trans.x = D_80109F80_pipe_cleaners[obj->work[0] & 3].pos.x;
    obj->trans.y = D_80109F80_pipe_cleaners[obj->work[0] & 3].pos.y;
    obj->trans.z = D_80109F80_pipe_cleaners[obj->work[0] & 3].pos.z;
    obj->rot.z = D_80109F80_pipe_cleaners[obj->work[0] & 3].rotZ;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelCameraSet(obj->model[0], 1 << (obj->work[0] >> 2));
    obj->func = func_801080F4_pipe_cleaners;
}

void func_80108428_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        omAddObj(0xC8, 1, 2, -1, func_80108194_pipe_cleaners)->work[0] = i;
    }
}

void func_80108484_pipe_cleaners(void) {
    s32 pattern[26];
    u32 last;
    u32 next;
    u32 i;
    u32 j;
    s32 k;
    s32 dir;
    s32 step;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 60; j++) {
            D_8010A838_pipe_cleaners[i][j] = -1;
        }
    }
    next = 0;
    for (j = 0; j < 26; j++) {
        pattern[j] = -1;
    }
    for (i = 0; i < 4; i++) {
        last = (u8)(rand8() % 22) + 3;
        for (j = 0; j < 25; j++) {
            pattern[j] = rand8() & 3;
            if ((j & 1) && pattern[j] == pattern[j - 1]) {
                j--;
                continue;
            }
            if ((j & 3) == 0) {
                step = (u8)(rand8() % 3) + 1;
                next = j + step;
            }
            if (j == next) {
                pattern[j] += 4;
            }
            k = j * 2 + (rand8() & 1);
            D_8010A838_pipe_cleaners[i][k] = pattern[j];
            if (j == last) {
                do {
                    dir = rand8() & 3;
                } while (dir == D_8010A838_pipe_cleaners[i][k - 1] || dir == D_8010A838_pipe_cleaners[i][k - 2] ||
                         dir == D_8010A838_pipe_cleaners[i][k - 3]);
                if (k & 1) {
                    D_8010A838_pipe_cleaners[i][k - 1] = dir;
                } else {
                    D_8010A838_pipe_cleaners[i][k + 1] = dir;
                }
            }
        }
    }
}

// NON_MATCHING: register allocation differs around the D_8010AC10_pipe_cleaners / 15 quotient.
#ifdef NON_MATCHING
void func_80108708_pipe_cleaners(void) {
    PipeCleanerSlot *slot;
    s32 col;
    s32 type;
    s32 dir;
    s32 i;
    s32 j;

    if (D_8010AC10_pipe_cleaners >= 900) {
        return;
    }
    if (D_8010AC10_pipe_cleaners < 89) {
        return;
    }
    if (D_8010AC10_pipe_cleaners == 89) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                slot = &D_8010A968_pipe_cleaners[i * 4 + j];
                slot->unk0C = 2;
                slot->unk04 = 1;
                slot->unk10 = 0;
            }
        }
        return;
    }
    if (D_8010AC10_pipe_cleaners % 15 == 14) {
        col = 59 - D_8010AC10_pipe_cleaners / 15;
        for (i = 0; i < 4; i++) {
            type = D_8010A838_pipe_cleaners[i][col];
            if (type == -1) {
                continue;
            }
            dir = type & 3;
            type /= 4;
            slot = &D_8010A968_pipe_cleaners[i * 4 + dir];
            if (slot->state != 0) {
                for (j = 0; j < 4; j++) {
                    slot = &D_8010A968_pipe_cleaners[i * 4 + j];
                    if (slot->state == 0) {
                        break;
                    }
                }
                if (slot->state != 0) {
                    continue;
                }
            }
            if (type == 0) {
                slot->unk0C = 0;
            } else {
                slot->unk0C = 1;
            }
            slot->unk04 = 1;
            slot->unk10 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108708_pipe_cleaners);
#endif

void func_801088AC_pipe_cleaners(PipeCleanerSign *sign, s32 arg1) {
    if (arg1 != 0) {
        if (sign->scale < 1.0f) {
            sign->scale += 0.1;
            if (sign->scale >= 1.0f) {
                sign->scale = 1.0f;
            }
        } else {
            sign->scale = 1.0f;
        }
    } else {
        if (sign->scale < 1.0f) {
            sign->scale += 0.1;
            if (sign->scale >= 1.0f) {
                sign->scale = 1.0f;
            }
        } else {
            sign->scale = 1.0f;
        }
    }
    espScaleSet(sign->espId, sign->scale, sign->scale);
}

// NON_MATCHING: the target reloads scale and uses a second 0.1 rodata constant for the comparison.
#ifdef NON_MATCHING
void func_80108964_pipe_cleaners(PipeCleanerSign *sign, s32 arg1) {
    sign->scale -= 0.1;
    if (sign->scale <= 0.1) {
        sign->scale = 0.1f;
    }
    espScaleSet(sign->espId, sign->scale, sign->scale);
    if (sign->alpha > 20.0f) {
        sign->alpha -= 25.5;
    } else {
        sign->alpha = 1.0f;
    }
    espTPLvlSet(sign->espId, sign->alpha);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108964_pipe_cleaners);
#endif

void func_80108A4C_pipe_cleaners(omObjData *obj) {
    PipeCleanerSign *sign;
    PipeCleanerWork *work;
    s32 i;

    if (D_8010A2F0_pipe_cleaners != 5) {
        for (i = 0; i < 16; i++) {
            sign = &D_8010AC18_pipe_cleaners[i];
            espDispOff(sign->espId);
            sign->state = 0;
        }
        D_8010AD58_pipe_cleaners = 16;
        D_8010A82C_pipe_cleaners = 0;
        return;
    }
    for (i = 0; i < 16; i++) {
        sign = &D_8010AC18_pipe_cleaners[i];
        if (sign->state == 0) {
            sign->state = 1;
            sign->scale = 0.0f;
            sign->alpha = 255.0f;
            sign->unk10 = 0;
        }
    }
    if (D_8010AD58_pipe_cleaners > 0) {
        D_8010AD58_pipe_cleaners--;
        if (D_8010A82C_pipe_cleaners == 2 && D_8010A030_pipe_cleaners == -1) {
            D_8010A030_pipe_cleaners = HuAudFXPlay(0x3EC);
        }
    } else {
        D_8010A82C_pipe_cleaners++;
        switch (D_8010A82C_pipe_cleaners) {
            case 1:
                D_8010AD58_pipe_cleaners = 15;
                break;
            case 2:
                if (D_8010A030_pipe_cleaners == -1) {
                    D_8010A030_pipe_cleaners = HuAudFXPlay(0x3EC);
                }
                D_8010AD58_pipe_cleaners = 60;
                break;
            case 3:
                HuAudFXPlay(0x3ED);
                D_8010AD58_pipe_cleaners = 30;
                break;
            case 4:
                D_8010AD58_pipe_cleaners = 16;
                break;
        }
    }
    for (i = 0; i < 4; i++) {
        work = &D_8010AB30_pipe_cleaners[i];

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 0];
        espDispOn(sign->espId);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(sign, 1);
                break;
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                func_80108964_pipe_cleaners(sign, 1);
                break;
        }

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 1];
        espDispOn(sign->espId);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(sign, 0);
                break;
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                func_80108964_pipe_cleaners(sign, 0);
                break;
        }

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 2];
        func_8000BD50_main(sign->espId, sign->unk10 / 10);
        espDispOn(sign->espId);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(sign, 0);
                break;
            case 1:
                break;
            case 2:
                sign->unk10 = (u8)(rand8() % 100);
                break;
            case 3:
                sign->unk10 = work->counter;
                break;
            case 4:
                func_80108964_pipe_cleaners(sign, 0);
                break;
        }

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 3];
        func_8000BD50_main(sign->espId, sign->unk10 % 10);
        espDispOn(sign->espId);
        switch (D_8010A82C_pipe_cleaners) {
            case 0:
                func_801088AC_pipe_cleaners(sign, 0);
                break;
            case 1:
                break;
            case 2:
                sign->unk10 = (u8)(rand8() % 100);
                break;
            case 3:
                sign->unk10 = work->counter;
                break;
            case 4:
                func_80108964_pipe_cleaners(sign, 0);
                break;
        }
    }
}

void func_80108F18_pipe_cleaners(omObjData *obj) {
    PipeCleanerSign *sign;
    s32 frameFile;
    s32 crossFile;
    s32 digitFile;
    s32 i;

    frameFile = func_8000B838_main(0x48000B);
    crossFile = func_8000B838_main(0x21001B);
    digitFile = func_8000B838_main(0x2E);
    for (i = 0; i < 4; i++) {
        sign = &D_8010AC18_pipe_cleaners[i * 4 + 0];
        sign->espId = espEntry(frameFile, 0, 0);
        espAttrSet(sign->espId, 0x1000);
        espScaleSet(sign->espId, 1.0f, 1.0f);
        espPosSet(sign->espId, D_8010A010_pipe_cleaners[i][0] - 30, D_8010A010_pipe_cleaners[i][1]);
        espDispOff(sign->espId);

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 1];
        sign->espId = espEntry(crossFile, 0, 0);
        espAttrSet(sign->espId, 0x1000);
        espScaleSet(sign->espId, 2.0f, 2.0f);
        espPosSet(sign->espId, D_8010A010_pipe_cleaners[i][0], D_8010A010_pipe_cleaners[i][1]);
        espDispOff(sign->espId);

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 2];
        sign->espId = espEntry(digitFile, 0, 0);
        espAttrSet(sign->espId, 0x1000);
        espScaleSet(sign->espId, 1.0f, 1.0f);
        espPosSet(sign->espId, D_8010A010_pipe_cleaners[i][0] + 20, D_8010A010_pipe_cleaners[i][1]);
        espDispOff(sign->espId);

        sign = &D_8010AC18_pipe_cleaners[i * 4 + 3];
        sign->espId = espEntry(digitFile, 0, 0);
        espAttrSet(sign->espId, 0x1000);
        espScaleSet(sign->espId, 1.0f, 1.0f);
        espPosSet(sign->espId, D_8010A010_pipe_cleaners[i][0] + 40, D_8010A010_pipe_cleaners[i][1]);
        espDispOff(sign->espId);
    }
    obj->func = func_80108A4C_pipe_cleaners;
}

void func_801091E4_pipe_cleaners(void) {
    omAddObj(0x258, 1, 0, -1, func_80108F18_pipe_cleaners);
}

void func_80109218_pipe_cleaners(void) {
    PipeCleanerWork *work;
    u16 counts[4];
    u16 used;
    u16 temp;
    s16 i;
    s16 j;

    for (j = 0; j < 4; j++) {
        counts[j] = D_8010AB30_pipe_cleaners[j].counter;
    }
    for (i = 0; i < 3; i++) {
        for (j = 3; j > i; j--) {
            if (counts[j] > counts[j - 1]) {
                temp = counts[j];
                counts[j] = counts[j - 1];
                counts[j - 1] = temp;
            }
        }
    }
    used = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            work = &D_8010AB30_pipe_cleaners[j];
            if (!((used >> j) & 1) && work->counter == counts[i]) {
                work->rank = i;
                used |= 1 << j;
            }
        }
    }
}

void func_801093A4_pipe_cleaners(void) {
    s32 winners[4];
    PipeCleanerWork *work;
    s32 count;
    s32 i;

    for (i = 0; i < 4; i++) {
        winners[i] = 0;
    }
    for (i = 1; i < 4; i++) {
        if (D_8010AB30_pipe_cleaners[i].counter != D_8010AB30_pipe_cleaners[0].counter) {
            break;
        }
    }
    if (i == 4) {
        if (D_8010AB30_pipe_cleaners[0].counter == 0) {
            count = 0;
            for (i = 0; i < 4; i++) {
                work = &D_8010AB30_pipe_cleaners[i];
                func_80106DA4_pipe_cleaners(work);
                GwPlayer[work->object->work[0]].bonusCoin = 0;
            }
        } else {
            count = 4;
            for (i = 0; i < 4; i++) {
                work = &D_8010AB30_pipe_cleaners[i];
                winners[i] = GwPlayer[work->object->work[0]].chr;
                func_80106CF4_pipe_cleaners(work);
                GwPlayer[work->object->work[0]].bonusCoin = 10;
            }
        }
    } else {
        count = 0;
        for (i = 0; i < 4; i++) {
            work = &D_8010AB30_pipe_cleaners[i];
            if (D_8010AB30_pipe_cleaners[i].rank == 0) {
                winners[count++] = GwPlayer[work->object->work[0]].chr;
                func_80106CF4_pipe_cleaners(work);
                GwPlayer[work->object->work[0]].bonusCoin = 10;
            } else {
                func_80106DA4_pipe_cleaners(work);
                GwPlayer[work->object->work[0]].bonusCoin = 0;
            }
        }
    }
    switch (count) {
        case 0:
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            break;
        case 1:
            GMesCreate(0x16, winners[0]);
            HuAudSeqPlay(0x65);
            break;
        case 2:
            GMesCreate(0x1E, winners[0], winners[1]);
            HuAudSeqPlay(0x66);
            break;
        case 3:
            GMesCreate(0x22, winners[0], winners[1], winners[2]);
            HuAudSeqPlay(0x66);
            break;
        case 4:
            GMesCreate(0x23, winners[0], winners[1], winners[2], winners[3]);
            HuAudSeqPlay(0x66);
            break;
    }
}

void func_801096C0_pipe_cleaners(void) {
    u32 i;

    if (D_8010A034_pipe_cleaners != 0) {
        return;
    }
    D_8010A034_pipe_cleaners = 1;
    for (i = 0; i < 4; i++) {
        CZoomM[i] = 1500.0f;
        CRotM[i].x = 357.631f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 160.0f;
        CenterM[i].z = -30.0f;
    }
}

void func_80109784_pipe_cleaners(omObjData *obj) {
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            DataClose(D_8010A2B0_pipe_cleaners[i][j]);
        }
        Hu3DAnimKill(D_8010A2E0_pipe_cleaners[i]);
    }
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_8010984C_pipe_cleaners(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80109784_pipe_cleaners;
    }
}

void func_80109884_pipe_cleaners(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010984C_pipe_cleaners;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_801098DC_pipe_cleaners(omObjData *obj) {
    switch (D_8010A2F0_pipe_cleaners) {
        case 0:
            GMesCreate(3);
            D_8010A2F0_pipe_cleaners = 1;
            break;
        case 1:
            if (++D_8010A038_pipe_cleaners == 13) {
                HuAudSeqPlay(0x36);
            }
            if (GMesStatGet() == 0 || (GMesStatGet() & 2)) {
                D_8010A2F0_pipe_cleaners = 2;
                GMesCreate(0x1A, 30, 160, 28);
                D_8010AC10_pipe_cleaners = 901;
            }
            break;
        case 2:
            func_80108708_pipe_cleaners();
            if (D_8010AC10_pipe_cleaners > 0) {
                D_8010AC10_pipe_cleaners--;
                func_8003F578_main((D_8010AC10_pipe_cleaners + 29) / 30);
            } else {
                func_8003F5C0_main();
                D_8010AC10_pipe_cleaners = 15;
                D_8010A2F0_pipe_cleaners = 3;
            }
            break;
        case 3:
            if (--D_8010AC10_pipe_cleaners == 0) {
                GMesCreate(0xE);
                HuAudSeqFadeOut(120);
                D_8010A2F0_pipe_cleaners = 4;
            }
            break;
        case 4:
            if (GMesStatGet() == 0) {
                func_80109218_pipe_cleaners();
                D_8010AC10_pipe_cleaners = 135;
                D_8010A2F0_pipe_cleaners = 5;
            }
            break;
        case 5:
            if (--D_8010AC10_pipe_cleaners == 0) {
                D_8010AC10_pipe_cleaners = 1;
                D_8010A2F0_pipe_cleaners = 6;
            }
            break;
        case 6:
            if (--D_8010AC10_pipe_cleaners == 0) {
                func_801093A4_pipe_cleaners();
                D_8010A2F0_pipe_cleaners = 7;
            }
            break;
        case 7:
            if (D_8010A03C_pipe_cleaners == 0) {
                if (GMesStatGet() & 2) {
                    D_8010A03C_pipe_cleaners = 1;
                    D_8010AC10_pipe_cleaners = 20;
                }
            } else if (--D_8010AC10_pipe_cleaners <= 0) {
                WipeCreateOut(0, 20);
                obj->func = func_8010984C_pipe_cleaners;
            }
            break;
    }
    func_801096C0_pipe_cleaners();
}

void func_80109B74_pipe_cleaners(omObjData *obj) {
    WipeCreateIn(0xFF, 16);
    func_80105DB4_pipe_cleaners();
    func_80105E60_pipe_cleaners();
    func_80108428_pipe_cleaners();
    func_8010638C_pipe_cleaners();
    func_80107A48_pipe_cleaners();
    func_80108484_pipe_cleaners();
    func_801091E4_pipe_cleaners();
    func_80106078_pipe_cleaners();
    D_8010A2F0_pipe_cleaners = 0;
    obj->func = func_801098DC_pipe_cleaners;
}

void func_80109BF4_pipe_cleaners(void) {
}

void func_80109BFC_pipe_cleaners(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        ScissorSet(i, D_8010A040_pipe_cleaners[i].scissorX, D_8010A040_pipe_cleaners[i].scissorY,
                   D_8010A040_pipe_cleaners[i].scissorWidth, D_8010A040_pipe_cleaners[i].scissorHeight);
        ViewportSet(i, D_8010A040_pipe_cleaners[i].viewportScale.x, D_8010A040_pipe_cleaners[i].viewportScale.y,
                    D_8010A040_pipe_cleaners[i].viewportScale.z, D_8010A040_pipe_cleaners[i].viewportTranslate.x,
                    D_8010A040_pipe_cleaners[i].viewportTranslate.y, D_8010A040_pipe_cleaners[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010A040_pipe_cleaners[i].fov, 80.0f, 8000.0f);
    }
}

void func_80109D70_pipe_cleaners(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_80109BFC_pipe_cleaners();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 255, 255, 255);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010A2A8_pipe_cleaners, 0);
    func_80045010_main(D_8010A2A8_pipe_cleaners, 1);
    omAddObj(1000, 0, 0, -1, func_80109B74_pipe_cleaners);
    omAddObj(1000, 0, 0, -1, func_80109884_pipe_cleaners);
    func_80105A74_pipe_cleaners();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A2A8_pipe_cleaners);
