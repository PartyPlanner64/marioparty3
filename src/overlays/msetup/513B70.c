#include "common.h"
#include "game/vibrator.h"
#include "overlays/msetup_internal.h"

typedef struct MsetupStoryMenu {
    Vec pos;
    s16 state;
    s16 type;
    s16 result;
    s16 unk12;
} MsetupStoryMenu;

extern Vec *D_8011A16C_msetup[];
extern MsetupStorySprite D_8011A178_msetup[];
extern MsetupStorySprite D_8011A218_msetup[];
extern MsetupStorySprite D_8011A2B8_msetup[];
extern Vec D_8011A368_msetup[];
extern Vec D_8011A38C_msetup[];
extern MsetupStorySprite D_8011A3B8_msetup[];
extern MsetupStorySprite D_8011A428_msetup[];
extern MsetupStorySprite D_8011A478_msetup[];
extern MsetupStorySprite D_8011A4C8_msetup[];
extern s32 D_8011A508_msetup[];
extern s16 D_8011A514_msetup[][2];
extern s16 (*D_8011A544_msetup[])[2];
extern u8 D_8011A550_msetup[];
extern s16 D_8011A0D0_msetup[];

extern MsetupCameraPreset D_8011A554_msetup;
extern s16 D_8011A910_msetup;
extern s16 D_8011A948_msetup;
extern s16 D_8011AA48_msetup;
extern s16 D_8011A944_msetup;
extern s16 D_8011A946_msetup;
extern s16 D_8011AA4C_msetup;
extern u16 D_80119410_msetup;
extern u8 D_800CE20A_main;
extern u8 D_8011A3B0_msetup[];
extern s16 D_800D418E_main;

void func_80106260_msetup(MsetupCameraPreset *);
void func_80117A3C_msetup(void);
void espAttrSet(u16, s32);
void func_8006105C_main(s16, s32);

f32 func_80054B1C_main(s16, s16, s16, f32, f32, f32);

void func_80117910_msetup(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z, f32 scale) {
    HuSprite *sprite;
    HuCamera *cam;
    f32 depth;

    sprite = HuSprGrpData[group]->members[member];
    cam = &gCameraList[camera];
    depth = func_80054B1C_main(group, member, camera, x, y, z);
    if (depth != 0.0) {
        sprite->unk_60 = (cam->viewports[D_800D418E_main].vp.vscale[0] * scale) / 4.0 / depth / (f64)(4.0f / 3.0f);
        sprite->unk_64 = (cam->viewports[D_800D418E_main].vp.vscale[1] * scale) / 4.0 / depth;
    }
}

void func_80117A3C_msetup(void) {
    MsetupCursorState cursor;
    Vec positions[16];
    Vec position;
    Vec previousPosition;
    Vec startPosition;
    Vec delta;
    s16 sprites[16];
    s16 optionSprites[8];
    s16 angles[16];
    u8 disabled[8];
    s16 previousButtons;
    MsetupStoryMenu *menu;
    MsetupStorySprite *backgrounds;
    MsetupStorySprite *options;
    Vec *modelOffset;
    Vec *presets;
    Vec *pos;
    s16 backgroundGroup;
    s16 shadowGroup;
    s16 backgroundCount;
    s16 optionCount;
    s16 model;
    s16 decoration;
    s16 state;
    s16 difficultyCount;
    s32 i;
    Vec *target;
    s16 preset;
    s16 selection;
    u16 buttons;
    s16 group;
    s16 sprite;
    f32 frame;
    f32 duration;
    f32 x;
    f32 y;
    f32 z;
    f32 angleStep;

    menu = HuPrcCurrentGet()->user_data;
    pos = &menu->pos;
    switch (menu->type) {
        case 0:
        default:
            backgrounds = D_8011A178_msetup;
            backgroundCount = 10;
            options = D_8011A3B8_msetup;
            optionCount = 7;
            break;
        case 1:
            backgrounds = D_8011A218_msetup;
            backgroundCount = 10;
            if (_CheckFlag(0x2D)) {
                options = D_8011A428_msetup;
                optionCount = 5;
                difficultyCount = 4;
            } else {
                options = D_8011A478_msetup;
                optionCount = 5;
                difficultyCount = 3;
            }
            break;
        case 2:
            backgrounds = D_8011A2B8_msetup;
            backgroundCount = 11;
            options = D_8011A4C8_msetup;
            optionCount = 4;
            break;
    }
    presets = D_8011A16C_msetup[menu->type];
    for (i = 0; i < backgroundCount; i++) {
        sprites[i] = -1;
    }
    for (i = 0; i < optionCount; i++) {
        optionSprites[i] = -1;
    }
    shadowGroup = -1;
    *pos = presets[0];
    backgroundGroup = HuSprGrpCreate(backgroundCount, 0);
    for (i = 0; i < backgroundCount; i++) {
        sprites[i] = func_8000B838_main(backgrounds[i].dataId);
        HuSprTPLvlSet(backgroundGroup, i, 0x100);
        HuSprAttrReset(backgroundGroup, i, 0xFFFF);
        HuSprAttrSet(backgroundGroup, i, 0x1000);
        HuSprScaleSet(backgroundGroup, i, 1.0f, 1.0f);
        func_800550F4_main(backgroundGroup, i, 0);
        HuSprGrpMemberSet(backgroundGroup, i, sprites[i], 0);
        HuSprPriSet(backgroundGroup, i, 600);
        HuSprColorSet(backgroundGroup, i, 255, 255, 255);
        target = &positions[i];
        *target = backgrounds[i].pos;
        angles[i] = (i * 90 + i * 5) % 360;
    }
    if (menu->type == 2) {
        HuSprScaleSet(backgroundGroup, 0, 4.0f, 2.0f);
    }
    group = HuSprGrpCreate(optionCount, 0);
    for (i = 0; i < optionCount; i++) {
        optionSprites[i] = func_8000B838_main(options[i].dataId);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x1000);
        func_800550F4_main(group, i, 0);
        HuSprGrpMemberSet(group, i, optionSprites[i], 0);
        HuSprTPLvlSet(group, i, 0x100);
        if (i != 0) {
            HuSprPriSet(group, i, 400);
            switch (menu->type) {
                case 0:
                    HuSprAttrSet(group, i, 0x9000);
                    break;
                case 1:
                    HuSprTPLvlSet(group, i, 0x40);
                    break;
                case 2:
                    break;
            }
        } else {
            HuSprPriSet(group, i, 500);
        }
    }
    if (menu->type == 0) {
        shadowGroup = HuSprGrpCreate(optionCount, 0);
        sprite = func_8000B838_main(0x140064);
        for (i = 0; i < optionCount; i++) {
            HuSprAttrReset(shadowGroup, i, 0xFFFF);
            HuSprAttrSet(shadowGroup, i, 0x9000);
            func_800550F4_main(shadowGroup, i, 0);
            HuSprGrpMemberSet(shadowGroup, i, sprite, 0);
            HuSprTPLvlSet(shadowGroup, i, 0x80);
            HuSprPriSet(shadowGroup, i, 450);
            HuSprColorSet(shadowGroup, i, 0, 0, 0);
        }
    } else if (menu->type == 2) {
        HuSprPriSet(group, 1, 500);
        HuSprTPLvlSet(group, 0, 0x40);
        HuSprTPLvlSet(group, 1, 0x40);
    }
    model = func_8000B108_main(0xA0089, 0x29D);
    decoration = func_8000B108_main(0x140068, 0x29D);
    func_8001C814_main(model, 2, 2);
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(decoration, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelScaleSet(model, 0.8f, 0.8f, 0.8f);
    Hu3DModelScaleSet(decoration, 0.8f, 0.8f, 0.8f);
    target = &D_8011A38C_msetup[menu->type];
    Hu3DModelRotSet(model, target->x, target->y, target->z);
    Hu3DModelRotSet(decoration, target->x, target->y, target->z);
    modelOffset = &D_8011A368_msetup[menu->type];
    position.x = pos->x + modelOffset->x;
    position.y = pos->y + modelOffset->y;
    position.z = pos->z + modelOffset->z;
    Hu3DModelPosSet(model, position.x, position.y, position.z);
    Hu3DModelPosSet(decoration, position.x, position.y, position.z);
    omAddPrcObj(func_8010D6D0_msetup, 0x3F00, 0x800, 0)->user_data = &cursor;
    cursor.pos[0] = 160;
    cursor.pos[1] = 120;
    cursor.positions = D_8011A544_msetup[menu->type];
    cursor.dataId = D_8011A508_msetup[menu->type];
    cursor.selection = -1;
    cursor.state = 0;
    cursor.flags = 0;
    cursor.priority = 0;
    HuPrcVSleep();
    for (i = 0; i < 6U; i++) {
        disabled[i] = 0;
    }
    previousPosition.x = previousPosition.y = previousPosition.z = 0;
    preset = 0;
    frame = 0;
    duration = 0;
    state = 0;
    selection = D_8011A550_msetup[menu->type];
    cursor.selection = selection;
    cursor.flags = 4;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    angleStep = 90.0f / 30.0f;
    while (1) {
        if (state != menu->state) {
            switch (menu->state) {
                case 0:
                default:
                    break;
                case 6:
                    cursor.state = 2;
                    startPosition = presets[preset];
                    position = presets[preset];
                    position.y += 800.0f;
                    target = &position;
                    preset = 0;
                    goto move;
                case 4:
                    cursor.state = 2;
                    startPosition = presets[preset];
                    target = &presets[0];
                    preset = 0;
                    goto move;
                case 3:
                    cursor.state = 2;
                    startPosition = presets[preset];
                    target = &presets[2];
                    preset = 2;
                    goto move;
                case 7:
                    cursor.state = 2;
                    startPosition = presets[preset];
                    target = &presets[3];
                    preset = 3;
                    goto move;
                case 2:
                    switch (menu->type) {
                        case 0:
                            for (i = 0; i < optionCount; i++) {
                                HuSprDispOff(shadowGroup, i);
                            }
                            break;
                        case 1:
                            HuSprTPLvlSet(group, selection + 1, 0x40);
                            break;
                    }
                case 1:
                    startPosition = presets[preset];
                    target = &presets[1];
                    preset = 1;
                move:
                    delta.x = target->x - startPosition.x;
                    delta.y = target->y - startPosition.y;
                    delta.z = target->z - startPosition.z;
                    if (delta.x == 0.0f && delta.y == 0.0f && delta.z == 0.0f) {
                        frame = 0;
                        duration = frame;
                        menu->state = 0;
                    } else {
                        duration = 30;
                        frame = 0;
                    }
                    break;
                case 5:
                    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
                    cursor.state = 1;
                    switch (menu->type) {
                        case 0:
                            HuSprDispOn(group, selection + 1);
                            break;
                        case 1:
                            HuSprTPLvlSet(group, selection + 1, 0x100);
                            break;
                        case 2:
                            HuSprTPLvlSet(group, selection, 0x100);
                            break;
                    }
                    break;
            }
            state = menu->state;
        }
        if (duration != 0.0f) {
            frame += 1.0f;
            x = sindf(angleStep * frame);
            pos->x = x * delta.x + startPosition.x;
            pos->y = x * delta.y + startPosition.y;
            pos->z = x * delta.z + startPosition.z;
            if (frame >= duration) {
                frame = 0;
                duration = frame;
                menu->state = 0;
            }
        }
        for (i = 0; i < backgroundCount; i++) {
            target = &positions[i];
            x = pos->x + target->x + sindf(angles[i]);
            y = pos->y + target->y + cosdf(angles[i] * 2);
            z = pos->z + target->z;
            angles[i] += 4;
            if (angles[i] > 360) {
                angles[i] -= 360;
            }
            func_80117910_msetup(backgroundGroup, i, 0, x, y, z, 2.5f);
        }
        for (i = 0; i < optionCount; i++) {
            target = &options[i].pos;
            x = pos->x + target->x;
            y = pos->y + target->y;
            z = pos->z + target->z;
            func_80117910_msetup(group, i, 0, x, y, z, 2.5f);
            if (menu->type == 0) {
                func_80117910_msetup(shadowGroup, i, 0, x, y, z, 2.5f);
            }
        }
        position.x = pos->x + modelOffset->x;
        position.y = pos->y + modelOffset->y;
        position.z = pos->z + modelOffset->z;
        Hu3DModelPosSet(model, position.x, position.y, position.z);
        Hu3DModelPosSet(decoration, position.x, position.y, position.z);
        if (preset == 1 && previousPosition.x == pos->x && previousPosition.y == pos->y && previousPosition.z == pos->z) {
            for (i = 0; i < optionCount; i++) {
                HuSprScaleSet(group, i, 1.0f, 1.0f);
            }
        }
        previousPosition.x = pos->x;
        previousPosition.y = pos->y;
        previousPosition.z = pos->z;
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (state == 5) {
            switch (menu->type) {
                case 0:
                    if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
                        i = func_8010D4DC_msetup(D_8011A514_msetup, disabled, 6, selection, D_8011A948_msetup, buttons);
                        if ((i >= 0) & (i < 6U)) {
                            selection = i;
                        }
                        if (cursor.selection != selection) {
                            HuAudFXPlay(1);
                            HuSprDispOff(group, cursor.selection + 1);
                            HuSprDispOn(group, selection + 1);
                            cursor.selection = selection;
                        }
                    }
                    if (buttons & A_BUTTON) {
                        menu->state = 0;
                        menu->result = selection;
                        HuSprDispOn(group, selection + 1);
                        HuAudFXPlay(D_8011A0D0_msetup[selection]);
                        RepeatVibrator(D_8011A948_msetup, 5, 0, 5);
                        for (i = 1; i < optionCount; i++) {
                            if (i != selection + 1) {
                                HuSprDispOn(shadowGroup, i);
                            }
                        }
                    } else if (buttons & B_BUTTON) {
                        switch (menu->type) {
                            case 0:
                                HuAudFXPlay(5);
                                break;
                            case 1:
                                HuAudFXPlay(4);
                                menu->state = 0;
                                menu->result = -1;
                                break;
                        }
                    }
                    break;
                case 1:
                    if (buttons & (D_JPAD | L_JPAD)) {
                        selection++;
                        if (selection >= difficultyCount) {
                            selection = difficultyCount - 1;
                        }
                    } else if (buttons & (U_JPAD | R_JPAD)) {
                        selection--;
                        if (selection < 0) {
                            selection = 0;
                        }
                    }
                    if (cursor.selection != selection) {
                        HuAudFXPlay(1);
                        HuSprTPLvlSet(group, cursor.selection + 1, 0x40);
                        HuSprTPLvlSet(group, selection + 1, 0x100);
                        cursor.selection = selection;
                    }
                    if (buttons & A_BUTTON) {
                        HuAudFXPlay(2);
                        menu->state = 0;
                        menu->result = selection;
                    } else if (buttons & B_BUTTON) {
                        HuAudFXPlay(4);
                        menu->state = 0;
                        menu->result = -1;
                        HuSprTPLvlSet(group, cursor.selection + 1, 0x40);
                    }
                    break;
                case 2:
                    if (buttons & (D_JPAD | L_JPAD)) {
                        selection = 0;
                    } else if (buttons & (U_JPAD | R_JPAD)) {
                        selection = 1;
                    }
                    if (cursor.selection != selection) {
                        HuAudFXPlay(1);
                        HuSprTPLvlSet(group, cursor.selection, 0x40);
                        HuSprTPLvlSet(group, selection, 0x100);
                        cursor.selection = selection;
                        menu->result = selection;
                    }
                    if (buttons & A_BUTTON) {
                        HuAudFXPlay(2);
                        menu->state = 0;
                        menu->result = selection;
                    } else if (buttons & B_BUTTON) {
                        HuAudFXPlay(4);
                        menu->state = 0;
                        menu->result = -1;
                        HuSprTPLvlSet(group, cursor.selection, 0x40);
                    }
                    break;
            }
        }
        HuPrcVSleep();
    }
}

void func_80118D48_msetup(void) {
    MsetupStoryMenu first;
    MsetupStoryMenu second;
    MsetupStoryMenu third;
    s16 unused[8];
    s16 unused2[8];
    s32 i;
    u16 sprite;
    u16 selection;
    s16 previous;
    s32 step;

    D_800CD280_main = 1;
    func_80106260_msetup(&D_8011A554_msetup);
    for (i = 0; i < 6; i++) {
        unused2[6] = -1;
        unused[6] = -1;
    }
    // Preserve the original scratch initialization and stack layout.
    (void)unused;
    (void)unused2;
    memset(&first, 0, sizeof(first));
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &first;
    first.type = 0;
    first.pos.x = 0;
    first.pos.y = 0;
    first.pos.z = 0;
    memset(&second, 0, sizeof(second));
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &second;
    second.type = 1;
    second.pos.x = 0;
    second.pos.y = 0;
    second.pos.z = 0;
    memset(&third, 0, sizeof(third));
    omAddPrcObj(func_80117A3C_msetup, 0x3F00, 0x800, 0)->user_data = &third;
    third.type = 2;
    third.pos.x = 0;
    third.pos.y = 0;
    third.pos.z = 0;
    sprite = espEntry(func_8000B838_main(0x140067), 0, 0);
    espAttrSet(sprite, 0x4000);
    espPosSet(sprite, 160, 120);
    D_8011A910_msetup = func_80060880_main(160, 204, 19);
    HuWinActivePlayerSet(D_8011A910_msetup, 1 << D_8011A948_msetup);
    func_8006105C_main(D_8011A910_msetup, 0xE0);
    HuWinMesPalSet(D_8011A910_msetup, 2, 255, 64, 64);
    HuWinMesPalSet(D_8011A910_msetup, 4, 96, 255, 64);
    HuWinMesPalSet(D_8011A910_msetup, 6, 255, 255, 64);
    func_80060C14_main(D_8011A910_msetup, 0);
    HuAudSeqPlay(10);
    WipeColorSet(255, 255, 255);
    WipeCreateIn(D_8011AA48_msetup, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    step = 0;
    D_800CD280_main = 0;
    do {
        switch (step) {
            case 0:
                HuWinMesSet(D_8011A910_msetup, 0x6000, -1, -1);
                while (HuWinStatGet(D_8011A910_msetup)) {
                    HuPrcVSleep();
                }
                step++;
                break;
            case 1:
                HuAudFXPlay(0x213);
                first.state = 2;
                do {
                    HuPrcVSleep();
                } while (first.state);
                HuWinMesSet(D_8011A910_msetup, 0x6001, -1, -1);
                first.state = 5;
                do {
                    HuPrcVSleep();
                } while (first.state);
                HuWinHomeClear(D_8011A910_msetup);
                if (first.result >= 0) {
                    first.state = 3;
                    step++;
                }
                break;
            case 2:
                HuAudFXPlay(0x213);
                second.state = 2;
                do {
                    HuPrcVSleep();
                } while (second.state);
                HuWinMesSet(D_8011A910_msetup, 0x6002, -1, -1);
                second.state = 5;
                do {
                    HuPrcVSleep();
                } while (second.state);
                HuWinHomeClear(D_8011A910_msetup);
                if (second.result < 0) {
                    second.state = 3;
                    step--;
                } else {
                    first.state = 4;
                    second.state = 4;
                    step++;
                }
                break;
            case 3:
                HuAudFXPlay(0x213);
                third.state = 2;
                do {
                    HuPrcVSleep();
                } while (third.state);
                HuWinMesSet(D_8011A910_msetup, 0x6004, -1, -1);
                while (HuWinStatGet(D_8011A910_msetup)) {
                    HuPrcVSleep();
                }
                previous = -1;
                third.state = 5;
                do {
                    if (previous != third.result) {
                        previous = third.result;
                        if (third.result != 0) {
                            HuWinMesSet(D_8011A910_msetup, 0x6006, -1, -1);
                        } else {
                            HuWinMesSet(D_8011A910_msetup, 0x6005, -1, -1);
                        }
                    }
                    HuPrcVSleep();
                } while (third.state);
                HuWinHomeClear(D_8011A910_msetup);
                if (third.result < 0) {
                    third.state = 3;
                    first.state = 3;
                    step--;
                } else {
                    third.state = 7;
                    step++;
                }
                break;
            case 4:
                HuAudFXPlay(0x213);
                first.state = 7;
                second.state = 7;
                do {
                    HuPrcVSleep();
                } while (second.state);
                HuWinMesSet(D_8011A910_msetup, 0x6003, -1, -1);
                while (HuWinStatGet(D_8011A910_msetup)) {
                    HuPrcVSleep();
                }
                if (HuWinChoiceGet(D_8011A910_msetup, 0, 0) != 0) {
                    first.state = 4;
                    second.state = 4;
                    step--;
                } else {
                    step = -2;
                    selection = first.result;
                    if (selection < 6) {
                        GwStory.unk1 = D_8011A3B0_msetup[(s16)selection];
                        GwStory.unk2 = second.result;
                        GwStory.unk0 = 0;
                        GwStory.progress.fields.unkF = 0;
                        for (i = 0; i < 12; i++) {
                            GwStory.progress.fields.unk3[i] = 0;
                        }
                        GwSystem.playMode = 5;
                        if (third.result == 1) {
                            _SetFlag(0x29);
                        } else {
                            _ClearFlag(0x29);
                        }
                        _ClearFlag(0x18);
                        _ClearFlag(0x28);
                        _ClearFlag(0);
                        GwStory.unk65 = GwStory.unk1;
                        GwStory.unk64 = 0;
                        GwStory.unk73 = 0;
                        GwStory.unk66 = GwStory.unk2;
                        for (i = 0; i < 12; i++) {
                            GwStory.unk67[i] = 0;
                        }
                        func_8005035C_main(1);
                    }
                    HuAudFXPlay(0x214);
                    first.state = 6;
                    second.state = 6;
                    third.state = 6;
                }
                HuWinHomeClear(D_8011A910_msetup);
                break;
        }
        HuPrcVSleep();
    } while (step >= 0);
    if (step < -1) {
        D_8011A944_msetup = 1;
        D_8011AA4C_msetup = 0x75;
        D_8011A946_msetup = 0;
        D_800CE20A_main = 1;
    }
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}
