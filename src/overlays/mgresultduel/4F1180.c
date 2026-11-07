#include "common.h"
#include "game/object.h"
#include "game/audio.h"

extern omObjFunc D_80109330_mgresultduel;
extern omObjFunc D_80109344_mgresultduel;
extern s8 D_80109310_mgresultduel[];
extern s8 D_801092F8_mgresultduel;
extern s16 D_8010930A_mgresultduel;
extern s16 D_8010930C_mgresultduel;
extern omObjFunc D_80109320_mgresultduel;
extern omObjFunc D_80109328_mgresultduel;

void func_80106B70_mgresultduel(omObjData *);
void func_80106CA0_mgresultduel(omObjData *);
void func_80106D0C_mgresultduel(omObjData *);
void func_80107178_mgresultduel(omObjData *);
void func_80107244_mgresultduel(omObjData *);
void func_801072A8_mgresultduel(omObjData *);
void func_80107654_mgresultduel(omObjData *);
void func_80108304_mgresultduel(void);
void func_80107B04_mgresultduel(s32);
void func_80107CA4_mgresultduel(omObjData *);
void func_80108318_mgresultduel(omObjData *);
void func_80108818_mgresultduel(omObjData *);
void func_80108820_mgresultduel(omObjData *);
void func_80108D30_mgresultduel(s16, s16, s16);
void func_80108E18_mgresultduel(void);
void func_80108E2C_mgresultduel(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80106930_mgresultduel);

void func_80106B68_mgresultduel(omObjData *arg0) {
}

void func_80106B70_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[4]].motId, 0, 0x1E, 2);
    D_80109344_mgresultduel = func_80106B68_mgresultduel;
}

void func_80106BD8_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[2]].motId, 0, 0x1E, 0);
    D_80109344_mgresultduel = func_80107654_mgresultduel;
}

void func_80106C3C_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_80109344_mgresultduel = func_80106B68_mgresultduel;
}

void func_80106CA0_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_80109344_mgresultduel = func_80107654_mgresultduel;
}

void func_80106D04_mgresultduel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80106D0C_mgresultduel);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80106F38_mgresultduel);

void func_80107170_mgresultduel(omObjData *arg0) {
}

void func_80107178_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[4]].motId, 0, 0x1E, 2);
    D_80109330_mgresultduel = func_80107170_mgresultduel;
}

void func_801071E0_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[2]].motId, 0, 0x1E, 0);
    D_80109330_mgresultduel = func_80107654_mgresultduel;
}

void func_80107244_mgresultduel(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], HmfModelData[arg0->motion[3]].motId, 0, 0x1E, 0);
    D_80109330_mgresultduel = func_80107170_mgresultduel;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_801072A8_mgresultduel);

void func_801074B0_mgresultduel(void) {
}

void func_801074B8_mgresultduel(void) {
    D_80109344_mgresultduel = func_80106D0C_mgresultduel;
    D_80109330_mgresultduel = func_801072A8_mgresultduel;
}

void func_801074DC_mgresultduel(s8 arg0) {
    if (arg0 == -1) {
        D_80109344_mgresultduel = func_80106B70_mgresultduel;
    } else {
        D_80109330_mgresultduel = func_80107178_mgresultduel;
    }
}

void func_8010751C_mgresultduel(s8 arg0) {
    HuPrcSleep(2);
    if (arg0 == -1) {
        HuAudFXPanning(PlayerFXPlay(0x28F, D_80109310_mgresultduel[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x26B, D_80109310_mgresultduel[1]), 0x60);
        D_80109344_mgresultduel = func_80106BD8_mgresultduel;
        D_80109330_mgresultduel = func_80107244_mgresultduel;
    } else {
        HuAudFXPanning(PlayerFXPlay(0x26B, D_80109310_mgresultduel[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x28F, D_80109310_mgresultduel[1]), 0x60);
        D_80109344_mgresultduel = func_80106C3C_mgresultduel;
        D_80109330_mgresultduel = func_801071E0_mgresultduel;
    }
    func_80108E18_mgresultduel();
}

void func_80107618_mgresultduel(void) {
    HuPrcSleep(2);
    D_80109344_mgresultduel = func_80106CA0_mgresultduel;
    D_80109330_mgresultduel = func_80107244_mgresultduel;
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

void func_80107AF4_mgresultduel(void) {
}

void func_80107AFC_mgresultduel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80107B04_mgresultduel);

void func_80107C74_mgresultduel(s32 arg0, s32 arg1) {
    D_801092F8_mgresultduel = arg1;
    func_80107B04_mgresultduel(arg0);
    D_80109320_mgresultduel = func_80107CA4_mgresultduel;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80107CA4_mgresultduel);

void func_80108304_mgresultduel(void) {
    D_80109320_mgresultduel = func_80108318_mgresultduel;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultduel/4F1180", func_80108318_mgresultduel);

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
