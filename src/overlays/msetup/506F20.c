#include "common.h"
#include "overlays/msetup_internal.h"
#include "mallocblock.h"

typedef struct MsetupEntryAnim {
    Vec pos;
    f32 value;
    s16 index;
    s16 state;
} MsetupEntryAnim;

extern MsetupModelEntry D_801198C4_msetup[];
extern Vec D_80119A0C_msetup[];
extern Vec D_80119A3C_msetup[];
extern f32 D_80119A54_msetup[];
extern f32 D_80119A64_msetup[];
extern s16 D_80119A6C_msetup[];
extern Process *D_8011A898_msetup[];
extern MsetupEntryAnim D_8011A9E0_msetup[];
extern omObjData *D_80119AF0_msetup;
extern s16 D_8011A938_msetup;
extern s16 D_8011A948_msetup;
extern s16 D_8011A890_msetup;
extern s16 D_8011A892_msetup[2];
extern s16 D_8011A990_msetup;
extern UnkMsetupEntry D_8011A9F2_msetup[];

void func_8006105C_main(s16, s32);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void func_8001C258_main(s16, s32, s32);
s32 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8010BEF8_msetup(void);
void func_8010ACC0_msetup(s16, s16);
void func_8010B4B8_msetup(s16, s16 *, s16);
void func_80106030_msetup(MsetupModelEntry *, MsetupModelHandle *, s32);
void func_8010B5D0_msetup(void);
s16 func_8010B388_msetup(s16, s16 *, s32, char *);

void func_8010ACC0_msetup(s16 model, s16 linkedModel) {
    f32 angle = 330.0f;
    f32 angleStep = -4.0f;
    f32 phase = 0.0f;
    f32 phaseStep = 90.0f / 16.0f;
    f32 y = 260.0f;
    f32 yStep = -260.0f / 14.0f;
    f32 x = -86.0f;
    f32 z = 617.0f;
    f32 temp;
    s32 i;

    for (i = 0; i < 15; i++) {
        Hu3DModelPosSet(model, x, y, z);
        Hu3DModelPosSet(linkedModel, x, 0.0f, z);
        temp = y + 100.0f;
        func_8010E044_msetup(D_80119AF0_msetup, 0, 100, x, temp, z);
        func_8010E044_msetup(D_80119AF0_msetup, 1, 100, x, temp, z);
        temp = (1.0 - y * 0.009) * 0.6;
        if (temp < 0.0f) {
            temp = 0.0f;
        }
        Hu3DModelScaleSet(linkedModel, temp, 1.0f, temp);
        angle += angleStep;
        y += yStep;
        phase += phaseStep;
        temp = 500.0f - sindf(phase) * 500.0f;
        x = temp * sindf(angle) + 194.0f;
        z = temp * cosdf(angle) + 197.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, 194.0f, 0.0f, 197.0f);
    Hu3DModelPosSet(linkedModel, 194.0f, 0.0f, 197.0f);
}

void func_8010AF40_msetup(MsetupModelHandle *models, s16 *animSlot, s16 *anim) {
    s16 model;
    s16 linkedModel;

    model = models[0].model;
    linkedModel = models[3].model;
    D_80119AF0_msetup->work[0] = 1;
    D_80119AF0_msetup->work[1] = 1;
    func_8010E00C_msetup(D_80119AF0_msetup, 2);
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(linkedModel, 4, 0);
    func_8010ACC0_msetup(model, linkedModel);
    D_80119AF0_msetup->work[0] = 0;
    HuAudFXPlay(0x135);
    func_8001C814_main(model, 2, 0);
    while (HmfModelData[model].unk40 < 40.0) {
        HuPrcVSleep();
    }
    func_8001C5B4_main(model, models[2].model);
    while (HmfModelData[model].unk40 < 45.0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A8);
    func_8010B4B8_msetup(model, animSlot, *anim);
    while (HmfModelData[model].unk40 < 80.0) {
        HuPrcVSleep();
    }
    func_8001F304_main(model, models[0].motion);
    func_8001C814_main(model, 2, 2);
}

void func_8010B1F4_msetup(void) {
    MsetupModelHandle models[4];
    s16 animSlot[3];
    s16 anim;
    s16 model;
    s16 linkedModel;
    s16 state;
    s16 *requestedState;

    requestedState = HuPrcCurrentGet()->user_data;
    omAddPrcObj(func_8010B5D0_msetup, 0x3F00, 0x800, 0);
    func_80106030_msetup(D_801198C4_msetup, models, 4);
    model = models[0].model;
    linkedModel = models[3].model;
    Hu3DModelScaleSet(linkedModel, 0.6f, 1.0f, 0.6f);
    func_8001F304_main(model, models[1].motion);
    func_8001C814_main(model, 2, 2);
    animSlot[0] = -1;
    anim = func_8010B388_msetup(model, animSlot, 0xA007E, "c204n_0_DEF");
    func_8010B4B8_msetup(model, animSlot, -1);
    state = 0;
    while (1) {
        if (state != *requestedState) {
            state = *requestedState;
        }
        switch (state) {
            case 0:
                break;
            case 1:
                func_8010AF40_msetup(models, animSlot, &anim);
                *requestedState = 0;
                break;
            case 2:
                func_8001C258_main(model, 4, 4);
                func_8001C258_main(linkedModel, 4, 4);
                *requestedState = 0;
                break;
        }
        HuPrcVSleep();
    }
}

s16 func_8010B388_msetup(s16 model, s16 *animSlot, s32 dataId, char *name) {
    void *data;
    s32 anim;
    s16 length;

    if (animSlot[0] >= 0) {
        func_80033354_main(animSlot[0]);
        func_80033354_main(animSlot[1]);
    }
    data = DataRead(dataId);
    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    animSlot[1] = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    length = D_800D1714_main[(s16)anim].animIdx;
    animSlot[2] = length;
    animSlot[0] = func_80032694_main(HmfModelData[model].hmf, anim, 0, name);
    func_8001C448_main(model);
    return length;
}

void func_8010B4B8_msetup(s16 model, s16 *animSlot, s16 anim) {
    HmfAnim *entry;

    if (*animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[*animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

s16 func_8010B588_msetup(s32 dataId) {
    void *data;
    s32 anim;

    data = DataRead(dataId);
    anim = func_800329B4_main(data);
    DataClose(data);
    return anim;
}

void func_8010B5D0_msetup(void) {
    s16 window;
    s16 state;

    window = func_80060880_main(250, 204, 8);
    func_8005FE54_main(window, 1 << D_8011A948_msetup);
    func_8006105C_main(window, 224);
    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    D_8011A890_msetup = D_8011A892_msetup[0] = window;
    window = func_80060880_main(250, 204, 18);
    func_8005FE54_main(window, 1 << D_8011A948_msetup);
    func_8006105C_main(window, 224);
    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    D_8011A892_msetup[1] = window;
    D_8011A990_msetup = 0;
    state = 0;
    while (1) {
        if (state != D_8011A990_msetup) {
            switch (D_8011A990_msetup) {
                case 0:
                    func_80060EA8_main(D_8011A890_msetup, 1);
                    break;
                case 1:
                    window = D_8011A890_msetup;
                    D_8011A890_msetup = D_8011A892_msetup[0];
                    if (state != 0) {
                        func_80060EA8_main(window, 1);
                    }
                    func_8005D294_main(D_8011A890_msetup);
                    func_80060C14_main(D_8011A890_msetup, 1);
                    break;
                case 2:
                    window = D_8011A890_msetup;
                    D_8011A890_msetup = D_8011A892_msetup[1];
                    if (state != 0) {
                        func_80060EA8_main(window, 1);
                    }
                    func_8005D294_main(D_8011A890_msetup);
                    func_80060C14_main(D_8011A890_msetup, 1);
                    break;
            }
            state = D_8011A990_msetup;
        }
        HuPrcVSleep();
    }
}

void func_8010B82C_msetup(s32 message) {
    func_8005B43C_main(D_8011A890_msetup, message, -1, -1);
}

s32 func_8010B858_msetup(void) {
    while (func_8005E0C0_main(D_8011A890_msetup) != 0) {
        HuPrcVSleep();
    }
    return D_800CC69C_main[D_8011A890_msetup].unk_30 == 0 ? 0 : func_8005E1D8_main(D_8011A890_msetup, 0, 0);
}

s32 func_8010B8E0_msetup(void) {
    while (func_8005E0C0_main(D_8011A890_msetup) != 0) {
        HuPrcVSleep();
    }
    return D_800CC69C_main[D_8011A890_msetup].unk_30 == 0 ? 0 : func_8005E1D8_main(D_8011A890_msetup, 1, 0);
}

void func_8010B968_msetup(u32 arg0, s8 arg1) {
    func_8005B6BC_main(D_8011A890_msetup, arg0, arg1);
}

void func_8010B998_msetup(void) {
    func_8005D294_main(D_8011A890_msetup);
}

void func_8010B9B8_msetup(s32 arg0, s32 arg1) {
    // wait for the given status bits of the menu window to be set
    while ((~func_8005B68C_main(D_8011A890_msetup) & arg0) == arg1) {
        HuPrcVSleep();
    }
}

void func_8010BA10_msetup(s32 arg0, s32 arg1) {
    func_8005B63C_main(D_8011A890_msetup, arg0, arg1);
}

s16 func_8010BA3C_msetup(void) {
    return (s16)D_800CC69C_main[D_8011A890_msetup].input;
}

void func_8010BA6C_msetup(s16 start, s16 end) {
    Vec *positions;
    f32 *values;
    s16 delay;
    s32 i;
    MsetupEntryAnim *entry;

    if (end != 2) {
        positions = D_80119A0C_msetup;
        values = D_80119A54_msetup;
    } else {
        positions = D_80119A3C_msetup;
        values = D_80119A64_msetup;
    }
    delay = D_80119A6C_msetup[D_8011A938_msetup];
    for (i = start; i < end; i++) {
        D_8011A9E0_msetup[i].state = 0;
        D_8011A9E0_msetup[i].index = i;
        D_8011A9E0_msetup[i].pos = positions[i];
        entry = &D_8011A9E0_msetup[i];
        D_8011A9E0_msetup[i].value = values[i];
        D_8011A898_msetup[i] = omAddPrcObj(func_8010BEF8_msetup, 0x4000, 0xC00, 0);
        D_8011A898_msetup[i]->user_data = entry;
        if (delay != 0) {
            HuPrcSleep(delay);
        }
    }
}

void func_8010BBF4_msetup(s16 end) {
    func_8010BA6C_msetup(0, end);
}

void func_8010BC18_msetup(s16 start, s16 end) {
    s32 i;
    s32 last = end - 1;

    for (i = start; i < end; i++) {
        D_8011A9F2_msetup[i].value = 12;
    }
    while (D_8011A9F2_msetup[last].value != 0) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        D_8011A9F2_msetup[i].value = 2;
    }
    while (D_8011A9F2_msetup[last].value != 0) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        D_8011A9F2_msetup[i].value = 18;
    }
    HuPrcVSleep();
    while (D_8011A9F2_msetup[last].value != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    for (i = start; i < end; i++) {
        omDelPrcObj(D_8011A898_msetup[i]);
        D_8011A898_msetup[i] = NULL;
    }
    HuPrcVSleep();
    HuPrcVSleep();
}

void func_8010BE8C_msetup(s16 end) {
    func_8010BC18_msetup(0, end);
}

s16 func_8010BEB0_msetup(s16 arg0, s16 arg1) {
    s16 prevValue = D_8011A9F2_msetup[arg0].value;

    if (arg1 >= 0) {
        D_8011A9F2_msetup[arg0].value = arg1;
    }
    return prevValue;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010BEF8_msetup);
