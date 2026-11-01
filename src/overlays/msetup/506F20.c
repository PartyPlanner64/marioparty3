#include "common.h"
#include "overlays/msetup_internal.h"
#include "game/mallocblock.h"

extern MsetupPlayerConfig D_8011AA30_msetup;
extern s16 D_801198C0_msetup;
extern s32 D_80119964_msetup[];
extern u8 D_80119984_msetup[];
extern s32 D_8011998C_msetup[];
extern s32 D_801199AC_msetup[];
extern s32 D_801199EC_msetup[];
extern s32 D_80119A7C_msetup[];
extern s32 D_80119A8C_msetup[];
extern s32 D_80119AB4_msetup[];
extern u8 D_80119AC8_msetup[];
extern u16 D_80119ACC_msetup;
extern u8 D_800D20B8_main[16][3];
extern u8 D_800D5570_main[16][3];
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

void espTPLvlSet(u16 spriteId, s16 arg1);
void func_80012B14_main(s16, Vec *, Vec2f *);
s16 func_8010CAF0_msetup(s32, s32);
s32 func_8010CD14_msetup(s16, f32, f32, f32);
void func_8006105C_main(s32 winId, s32 alpha);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void func_8001C258_main(s16, s32, s32);
s32 func_800329B4_main(u8 *data); // Declared locally: this caller was compiled against an int return type.
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
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(linkedModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8010ACC0_msetup(model, linkedModel);
    D_80119AF0_msetup->work[0] = 0;
    HuAudFXPlay(0x135);
    func_8001C814_main(model, 2, 0);
    while (HmfModelData[model].motTime < 40.0) {
        HuPrcVSleep();
    }
    func_8001C5B4_main(model, models[2].model);
    while (HmfModelData[model].motTime < 45.0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A8);
    func_8010B4B8_msetup(model, animSlot, *anim);
    while (HmfModelData[model].motTime < 80.0) {
        HuPrcVSleep();
    }
    Hu3DMotionSet(model, models[0].motion);
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
    Hu3DMotionSet(model, models[1].motion);
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
                func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(linkedModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
    animSlot[0] = HmfAnimLink(HmfModelData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
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
    HuWinActivePlayerSet(window, 1 << D_8011A948_msetup);
    func_8006105C_main(window, 224);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    D_8011A890_msetup = D_8011A892_msetup[0] = window;
    window = func_80060880_main(250, 204, 18);
    HuWinActivePlayerSet(window, 1 << D_8011A948_msetup);
    func_8006105C_main(window, 224);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
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
                    HuWinHomeClear(D_8011A890_msetup);
                    func_80060C14_main(D_8011A890_msetup, 1);
                    break;
                case 2:
                    window = D_8011A890_msetup;
                    D_8011A890_msetup = D_8011A892_msetup[1];
                    if (state != 0) {
                        func_80060EA8_main(window, 1);
                    }
                    HuWinHomeClear(D_8011A890_msetup);
                    func_80060C14_main(D_8011A890_msetup, 1);
                    break;
            }
            state = D_8011A990_msetup;
        }
        HuPrcVSleep();
    }
}

void func_8010B82C_msetup(s32 message) {
    HuWinMesSet(D_8011A890_msetup, message, -1, -1);
}

s32 func_8010B858_msetup(void) {
    while (HuWinStatGet(D_8011A890_msetup) != 0) {
        HuPrcVSleep();
    }
    return winData[D_8011A890_msetup].num_choices == 0 ? 0 : HuWinChoiceGet(D_8011A890_msetup, 0, 0);
}

s32 func_8010B8E0_msetup(void) {
    while (HuWinStatGet(D_8011A890_msetup) != 0) {
        HuPrcVSleep();
    }
    return winData[D_8011A890_msetup].num_choices == 0 ? 0 : HuWinChoiceGet(D_8011A890_msetup, 1, 0);
}

void func_8010B968_msetup(u32 arg0, s8 arg1) {
    HuWinInsertMesSet(D_8011A890_msetup, arg0, arg1);
}

void func_8010B998_msetup(void) {
    HuWinHomeClear(D_8011A890_msetup);
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
    return (s16)winData[D_8011A890_msetup].input;
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
        D_8011A9E0_msetup[i].state = 12;
    }
    while (D_8011A9E0_msetup[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        D_8011A9E0_msetup[i].state = 2;
    }
    while (D_8011A9E0_msetup[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        D_8011A9E0_msetup[i].state = 18;
    }
    HuPrcVSleep();
    while (D_8011A9E0_msetup[last].state != 0) {
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
    s16 prevValue = D_8011A9E0_msetup[arg0].state;

    if (arg1 >= 0) {
        D_8011A9E0_msetup[arg0].state = arg1;
    }
    return prevValue;
}

void func_8010BEF8_msetup(void) {
    s16 offset[2];
    Vec2f projected;
    s16 sprites[4];
    s16 slots[4];
    s16 alpha[4];
    s16 alphaStep[4];
    s16 alphaTarget[4];
    s16 kill[4];
    s16 motions[4];
    s16 model;
    s16 shadow;
    s16 effect;
    s16 character;
    s16 specialMotion;
    s16 playing;
    s32 i;
    s32 dataId;
    MsetupEntryAnim *entry;
    Vec *pos;
    s16 state;
    s16 setupCharacter;
    s16 index;
    f32 scale;
    f32 scaleStep;

    i = 0;
    entry = HuPrcCurrentGet()->user_data;
    for (; i < 4; i++) {
        slots[i] = -1;
        sprites[i] = -1;
        alphaStep[i] = 0;
        alphaTarget[i] = 0;
        alpha[i] = 0;
        kill[i] = 0;
    }
    motions[0] = -1;
    motions[1] = -1;
    character = D_8011AA30_msetup.characters[entry->index];
    setupCharacter = character;
    model = func_8000B108_main(D_80119964_msetup[setupCharacter], 0x2A9);
    index = model;
    func_8001C814_main(index, 2, 2);
    func_8001C258_main(index, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    pos = &entry->pos;
    Hu3DModelPosSet(index, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(index, 0.0f, entry->value, 0.0f);
    motions[3] = HmfModelData[index].motId;
    HuPrcVSleep();
    if (D_80119984_msetup[setupCharacter] != 0) {
        func_80017790_main(index, 1, setupCharacter, func_80017BB8_main(setupCharacter, 0xA4));
    } else {
        func_80017790_main(index, 0, character, func_80017BB8_main(character, 0xA3));
    }
    func_8001C514_main(index);
    HuPrcVSleep();
    if (D_801198C0_msetup < 0) {
        index = D_801198C0_msetup = func_8000B108_main(9, 0x299);
    } else {
        index = Hu3DModelLink(D_801198C0_msetup);
    }
    shadow = index;
    func_8001C258_main(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(shadow, pos->x, 0.0f, pos->z);
    HuPrcVSleep();
    specialMotion = 0;
    if ((D_80119ACC_msetup >> D_8011A938_msetup) & 1) {
        specialMotion = 1;
        motions[0] = func_8000B13C_main(D_801199AC_msetup[character]);
    } else {
        motions[0] = func_8000B13C_main(D_8011998C_msetup[character]);
    }
    state = 0;
    HuPrcVSleep();
    motions[1] = func_8000B13C_main(D_801199EC_msetup[character]);
    HuPrcVSleep();
    effect = func_8010CAF0_msetup(0x110012, 0x289);
    scale = 0.0f;
    scaleStep = 0.0f;
    playing = 0;
    do {
        HuPrcVSleep();
        if (state != entry->state) {
            state = entry->state;
        }
        switch (state) {
            case 0:
                break;
            case 1:
                for (i = 15; i != 0; i--) {
                    func_8010CD14_msetup(effect, pos->x, pos->y + 50.0f, pos->z);
                    HuPrcVSleep();
                }
                entry->state = 3;
                break;
            case 3:
                func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                func_8001C258_main(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (motions[0] >= 0 && (!specialMotion || entry->index != 0)) {
                    func_8001C5B4_main(model, motions[0]);
                    playing = 1;
                }
                scale = 0.0f;
                scaleStep = 1.0f / 15.0f;
                for (i = 15; i != 0; i--) {
                    scale += scaleStep;
                    Hu3DModelScaleSet(model, scale, 1.0f, scale);
                    Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
                    HuPrcVSleep();
                }
                entry->state = 0;
                break;
            case 2:
                scale = 1.0f;
                scaleStep = 1.0f / 7.0f;
                entry->state = 4;
                break;
            case 4:
                scale -= scaleStep;
                if (scale <= 0.0f) {
                    scale = 0.0f;
                    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    func_8001C258_main(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    entry->state = 0;
                }
                Hu3DModelScaleSet(model, scale, 1.0f, scale);
                Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
                func_8010CD14_msetup(effect, pos->x, pos->y + 50.0f, pos->z);
                break;
            case 11:
                for (i = 0; i < 4; i++) {
                    if (slots[i] >= 0) {
                        espDispOn(slots[i]);
                        alphaTarget[i] = D_80119AC8_msetup[i];
                        alphaStep[i] = (u8)(D_80119AC8_msetup[i] / 5U);
                    }
                }
                entry->state = 0;
                break;
            case 12:
                for (i = 0; i < 4; i++) {
                    alphaTarget[i] = 0;
                    alphaStep[i] = -alpha[i] / 5;
                }
                entry->state = 0;
                break;
            case 13:
                index = D_8011AA30_msetup.stars[entry->index];
                index--;
                if (index < 0) {
                    break;
                }
                dataId = D_80119AB4_msetup[index];
                i = 2;
                offset[0] = 28;
                offset[1] = -48;
                goto createSprite;
            case 15:
                kill[2] = 1;
            case 14:
                i = 2;
                goto hideSprite;
            case 5:
                dataId = D_80119A7C_msetup[D_8011AA30_msetup.cpuDifficulty[entry->index]];
                i = 0;
                offset[0] = 8;
                offset[1] = -6;
                goto createSprite;
            case 7:
                kill[0] = 1;
            case 6:
                i = 0;
                goto hideSprite;
            case 8:
                dataId = D_80119A8C_msetup[D_8011AA30_msetup.stars[entry->index]];
                i = 1;
                offset[0] = 16;
                offset[1] = -30;
            createSprite:
                if (slots[(s16)i] >= 0) {
                    espKill(slots[(s16)i]);
                }
                if (sprites[(s16)i] >= 0) {
                    HuSprAnimKill(sprites[(s16)i]);
                }
                index = i;
                kill[index] = 0;
                sprites[index] = func_8000B838_main(dataId);
                slots[index] = espEntry(sprites[index], 0, 1);
                espPriSet(slots[index], 1);
                func_80012B14_main(0, pos, &projected);
                espPosSet(slots[index], (s16)(offset[0] + projected.x), (s16)(offset[1] + projected.y));
                espTPLvlSet(slots[index], 0);
                espDispOn(slots[index]);
                alphaTarget[index] = D_80119AC8_msetup[index];
                alphaStep[index] = (u8)(D_80119AC8_msetup[index] / 7U);
                entry->state = 0;
                break;
            case 10:
                kill[1] = 1;
            case 9:
                i = 1;
            hideSprite:
                alphaTarget[(s16)i] = 0;
                alphaStep[(s16)i] = -alpha[(s16)i] / 7;
                entry->state = 0;
                if (alpha[(s16)i] == 0 && kill[(s16)i] != 0) {
                    kill[(s16)i] = 0;
                    if (slots[(s16)i] >= 0) {
                        espKill(slots[(s16)i]);
                        slots[(s16)i] = -1;
                    }
                    if (sprites[(s16)i] >= 0) {
                        HuSprAnimKill(sprites[(s16)i]);
                        sprites[(s16)i] = -1;
                    }
                }
                break;
            case 16:
                if (motions[1] >= 0) {
                    func_8001C5B4_main(model, motions[1]);
                }
                entry->state = 0;
                break;
            case 17:
                if (motions[0] >= 0) {
                    Hu3DMotionShiftSet(model, HmfModelData[motions[0]].motId, 0, 6, 0);
                }
                entry->state = 0;
                playing = 1;
                break;
            case 18:
                state = -1;
                break;
        }
        if (playing && D_800CCF58_main[HmfModelData[model].motId].unk02 <= HmfModelData[model].motTime) {
            Hu3DMotionShiftSet(model, motions[3], 0, 30, 2);
            playing = 0;
        }
        for (i = 0; i < 4; i++) {
            if (slots[i] >= 0) {
                if (alphaStep[i] != 0) {
                    alpha[i] += alphaStep[i];
                    if (alphaStep[i] < 0) {
                        if (alpha[i] <= alphaTarget[i]) {
                            alpha[i] = alphaTarget[i];
                            alphaStep[i] = 0;
                        }
                    } else {
                        if (alpha[i] >= alphaTarget[i]) {
                            alpha[i] = alphaTarget[i];
                            alphaStep[i] = 0;
                        }
                    }
                    espTPLvlSet(slots[i], alpha[i]);
                    if (alpha[i] == 0) {
                        espDispOff(slots[i]);
                        if (kill[i] != 0) {
                            kill[i] = 0;
                            if (slots[i] >= 0) {
                                espKill(slots[i]);
                                slots[i] = -1;
                            }
                            if (sprites[i] >= 0) {
                                HuSprAnimKill(sprites[i]);
                                sprites[i] = -1;
                            }
                        }
                    }
                }
            }
        }
    } while (state >= 0);
    for (i = 0; i < 4; i++) {
        if (slots[i] >= 0) {
            espKill(slots[i]);
        }
        if (sprites[i] >= 0) {
            HuSprAnimKill(sprites[i]);
        }
    }
    if (D_800D20B8_main[character][1] != 0xFF) {
        func_80033354_main(D_800D20B8_main[character][1]);
        func_80033354_main(D_800D5570_main[character][1]);
        D_800D20B8_main[character][1] = 0xFF;
    }
    Hu3DModelKill(model);
    Hu3DModelKill(shadow);
    if (D_801198C0_msetup == shadow) {
        D_801198C0_msetup = -1;
    }
    for (i = 0; i < 2; i++) {
        if (motions[i] >= 0) {
            Hu3DModelKill(motions[i]);
        }
    }
    Hu3DModelKill(effect);
    entry->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}
