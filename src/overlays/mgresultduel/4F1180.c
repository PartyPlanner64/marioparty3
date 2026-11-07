#include "common.h"
#include "game/object.h"
#include "game/audio.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkResultDuelStruct {
    /* 0x00 */ u8 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ Vec pos;
    /* 0x14 */ f32 unk14;
} UnkResultDuelStruct; // size = 0x18

typedef struct ResultDuelObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultDuelObj;

extern s8 D_80109310_mgresultduel[];
extern s8 D_801092F8_mgresultduel;
extern s16 D_8010930A_mgresultduel;
extern s16 D_8010930C_mgresultduel;
extern omObjFunc D_80109320_mgresultduel;
extern omObjFunc D_80109328_mgresultduel;
extern omObjData *D_8010931C_mgresultduel;
extern ResultDuelObj D_8010932C_mgresultduel;
extern ResultDuelObj D_80109340_mgresultduel;
extern s32 D_80109314_mgresultduel;
extern s32 D_800A178C_main[][6];
extern s8 D_80109318_mgresultduel;
extern s32 D_80108E80_mgresultduel;
extern s32 D_80108E84_mgresultduel;
extern s32 D_80108E88_mgresultduel;
extern s32 D_80108E8C_mgresultduel;
extern s32 D_80108E90_mgresultduel;
extern s32 D_80108E94_mgresultduel;
extern UnkResultDuelStruct D_80108F38_mgresultduel[20];

void func_80106B68_mgresultduel(omObjData *);
void func_80106B70_mgresultduel(omObjData *);
void func_80106D04_mgresultduel(void);
void func_80107170_mgresultduel(omObjData *);
void func_801074B0_mgresultduel(void);
void func_80106CA0_mgresultduel(omObjData *);
void func_80106D0C_mgresultduel(omObjData *);
void func_80107178_mgresultduel(omObjData *);
void func_80107244_mgresultduel(omObjData *);
void func_801072A8_mgresultduel(omObjData *);
void func_80107618_mgresultduel(void);
void func_80107654_mgresultduel(omObjData *);
void func_80108304_mgresultduel(void);
void func_80107B04_mgresultduel(s32);
void func_80107CA4_mgresultduel(omObjData *);
void func_80108318_mgresultduel(omObjData *);
void func_80106730_mgresultduel(void);
void func_800F79E8_name_81(s32);
void func_800E1504_name_81(s8, s32, s32, s32);
void func_800F37E0_name_81(s16, s32);
void func_80108818_mgresultduel(omObjData *);
void func_80108820_mgresultduel(omObjData *);
void func_80108D30_mgresultduel(s16, s16, s16);
void func_80108E04_mgresultduel(void);
void func_80108E18_mgresultduel(void);
void func_80108E2C_mgresultduel(omObjData *);

void func_80106930_mgresultduel(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 5, 8, -1, NULL);
    D_80109340_mgresultduel.obj = obj;
    chr = GwPlayer[D_80109310_mgresultduel[0]].chr;

    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], -460.0f, 0.0f, 2300.0f);

    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], -460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);

    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106D04_mgresultduel);
    D_80109340_mgresultduel.func = func_80106B68_mgresultduel;

    while (TRUE) {
        D_80109340_mgresultduel.func(obj);
        HuPrcVSleep();
    }
}

void func_80106B68_mgresultduel(omObjData *arg0) {
}

void func_80106B70_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[4]].motId, 0, 0x1E, 2);
    D_80109340_mgresultduel.func = func_80106B68_mgresultduel;
}

void func_80106BD8_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[2]].motId, 0, 0x1E, 0);
    D_80109340_mgresultduel.func = func_80107654_mgresultduel;
}

void func_80106C3C_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_80109340_mgresultduel.func = func_80106B68_mgresultduel;
}

void func_80106CA0_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_80109340_mgresultduel.func = func_80107654_mgresultduel;
}

void func_80106D04_mgresultduel(void) {
}

void func_80106D0C_mgresultduel(omObjData *arg0) {
    f32 i;
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, 90.0f, 0.0f);
    func_8001C5B4_main(arg0->model[1], arg0->motion[1]);
    func_8001C814_main(arg0->model[1], 2, 2);
    for (i = 0.0f; i < 240.0f; i += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], -460.0f + i, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], -460.0f + i, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], x = -220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], x, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[0]].motId, 0, 0x1E, 2);
    D_80109340_mgresultduel.func = func_80106B68_mgresultduel;
    if (D_80109318_mgresultduel != 2) {
        func_80108E04_mgresultduel();
    } else {
        func_80107618_mgresultduel();
    }
}

void func_80106F38_mgresultduel(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 5, 8, -1, NULL);
    D_8010932C_mgresultduel.obj = obj;
    chr = GwPlayer[D_80109310_mgresultduel[1]].chr;

    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 460.0f, 0.0f, 2300.0f);

    obj->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);

    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_801074B0_mgresultduel);
    D_8010932C_mgresultduel.func = func_80107170_mgresultduel;

    while (TRUE) {
        D_8010932C_mgresultduel.func(obj);
        HuPrcVSleep();
    }
}

void func_80107170_mgresultduel(omObjData *arg0) {
}

void func_80107178_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[4]].motId, 0, 0x1E, 2);
    D_8010932C_mgresultduel.func = func_80107170_mgresultduel;
}

void func_801071E0_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[2]].motId, 0, 0x1E, 0);
    D_8010932C_mgresultduel.func = func_80107654_mgresultduel;
}

void func_80107244_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_8010932C_mgresultduel.func = func_80107170_mgresultduel;
}

void func_801072A8_mgresultduel(omObjData *arg0) {
    f32 i;
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, -90.0f, 0.0f);
    func_8001C5B4_main(arg0->model[1], arg0->motion[1]);
    func_8001C814_main(arg0->model[1], 2, 2);
    for (i = 0.0f; i < 240.0f; i += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], 460.0f - i, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], 460.0f - i, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], x = 220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], x, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, -rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[0]].motId, 0, 0x1E, 2);
    D_8010932C_mgresultduel.func = func_80107170_mgresultduel;
}

void func_801074B0_mgresultduel(void) {
}

void func_801074B8_mgresultduel(void) {
    D_80109340_mgresultduel.func = func_80106D0C_mgresultduel;
    D_8010932C_mgresultduel.func = func_801072A8_mgresultduel;
}

void func_801074DC_mgresultduel(s8 arg0) {
    if (arg0 == -1) {
        D_80109340_mgresultduel.func = func_80106B70_mgresultduel;
    } else {
        D_8010932C_mgresultduel.func = func_80107178_mgresultduel;
    }
}

void func_8010751C_mgresultduel(s8 arg0) {
    HuPrcSleep(2);
    if (arg0 == -1) {
        HuAudFXPanning(PlayerFXPlay(0x28F, D_80109310_mgresultduel[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x26B, D_80109310_mgresultduel[1]), 0x60);
        D_80109340_mgresultduel.func = func_80106BD8_mgresultduel;
        D_8010932C_mgresultduel.func = func_80107244_mgresultduel;
    } else {
        HuAudFXPanning(PlayerFXPlay(0x26B, D_80109310_mgresultduel[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x28F, D_80109310_mgresultduel[1]), 0x60);
        D_80109340_mgresultduel.func = func_80106C3C_mgresultduel;
        D_8010932C_mgresultduel.func = func_801071E0_mgresultduel;
    }
    func_80108E18_mgresultduel();
}

void func_80107618_mgresultduel(void) {
    HuPrcSleep(2);
    D_80109340_mgresultduel.func = func_80106CA0_mgresultduel;
    D_8010932C_mgresultduel.func = func_80107244_mgresultduel;
}

void func_80107654_mgresultduel(omObjData *obj) {
    f32 time;
    f32 endTime;
    s16 model;

    model = obj->model[1];
    time = HmfModelData[model].motTime;
    endTime = D_800CCF58_main[HmfModelData[model].motId].unk02;
    while (endTime <= time) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80108304_mgresultduel();
    while (TRUE) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80107710_mgresultduel);

void func_80107AF4_mgresultduel(omObjData *arg0) {
}

void func_80107AFC_mgresultduel(void) {
}

void func_80107B04_mgresultduel(s32 arg0) {
    omObjData *obj;
    s8 i;

    obj = D_8010931C_mgresultduel;
    if (arg0 > 0) {
        arg0 = (arg0 > 50) ? 50 : arg0;
        D_80108E84_mgresultduel = arg0;
        D_80108E88_mgresultduel = 0;
        D_80108E80_mgresultduel = 0;
        D_80108E8C_mgresultduel = 0;
        if (arg0 <= 100) {
            D_80108E90_mgresultduel = arg0;
        } else {
            D_80108E90_mgresultduel = 100;
        }
        D_80108E94_mgresultduel = 4;
        for (i = 0; i < 20; i++) {
            D_80108F38_mgresultduel[i].unk00 = 0;
            D_80108F38_mgresultduel[i].unk04 = 0;
            D_80108F38_mgresultduel[i].pos.x = D_80108F38_mgresultduel[i].pos.y =
                D_80108F38_mgresultduel[i].pos.z = 0.0f;
            D_80108F38_mgresultduel[i].unk14 = -10.0f;
            func_8001C258_main(obj->model[i + 1], 4, 4);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
    }
}

void func_80107C74_mgresultduel(s32 arg0, s32 arg1) {
    D_801092F8_mgresultduel = arg1;
    func_80107B04_mgresultduel(arg0);
    D_80109320_mgresultduel = func_80107CA4_mgresultduel;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80107CA4_mgresultduel);

void func_80108304_mgresultduel(void) {
    D_80109320_mgresultduel = func_80108318_mgresultduel;
}

#ifdef NON_MATCHING
/*
 * Only diff: when promoting `player` for func_800F37E0_name_81, the target
 * shifts into a0 (sll a0,s0,16) while this compiles to sll s0,s0,16.
 * `player` is local to one basic block here, so local-alloc ties the shift
 * temp to it. The target behaves as if `player` were not block-local
 * (assigning it in both arms of the if/else fixes this part, via
 * cross-jumping, but then the s8 extension for func_800E1504_name_81 no
 * longer reuses the shifted temp).
 */
void func_80108318_mgresultduel(omObjData *arg0) {
    omObjData *obj;
    Vec pos;
    Vec2f screenPos;
    s8 temp;
    s16 player;

    func_800F79E8_name_81(-1);
    if (D_80109318_mgresultduel != 2) {
        if (D_80109318_mgresultduel == -1) {
            obj = D_80109340_mgresultduel.obj;
        } else {
            obj = D_8010932C_mgresultduel.obj;
        }
        pos.x = HmfModelData[obj->model[1]].pos.x;
        pos.y = HmfModelData[obj->model[1]].pos.y + 120.0f;
        pos.z = HmfModelData[obj->model[1]].pos.z;
        Hu3D3Dto2D(0, &pos, &screenPos);
        func_800E0CEC_name_81();
        temp = (D_80109318_mgresultduel == -1) ? D_80109310_mgresultduel[0] : D_80109310_mgresultduel[1];
        player = temp;
        func_800E1504_name_81(temp, D_80109314_mgresultduel, screenPos.x, screenPos.y);
        HuPrcSleep(20);
        func_800F37E0_name_81(player, D_80109314_mgresultduel);
        HuPrcSleep(20);
        func_800E0E38_name_81();
    } else {
        HuPrcSleep(40);
    }
    func_80106730_mgresultduel();
    D_80109320_mgresultduel = func_80107AF4_mgresultduel;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80108318_mgresultduel);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_801084B0_mgresultduel);

void func_80108818_mgresultduel(omObjData *arg0) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80108820_mgresultduel);

void func_80108D28_mgresultduel(void) {
}

void func_80108D30_mgresultduel(s16 model, s16 anim, s16 animIdx) {
    HmfAnim *entry;

    if (anim >= 0) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[anim];
            entry->animIdx = animIdx;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void func_80108E04_mgresultduel(void) {
    D_80109328_mgresultduel = func_80108820_mgresultduel;
}

void func_80108E18_mgresultduel(void) {
    D_80109328_mgresultduel = func_80108E2C_mgresultduel;
}

void func_80108E2C_mgresultduel(omObjData *arg0) {
    func_80108D30_mgresultduel(arg0->model[1], D_8010930C_mgresultduel, D_8010930A_mgresultduel);
    D_80109328_mgresultduel = func_80108818_mgresultduel;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultduel/4F1180", D_80108ED4_mgresultduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultduel/4F1180", D_80108F10_mgresultduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultduel/4F1180", D_80108F18_mgresultduel);
