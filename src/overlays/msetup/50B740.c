#include "common.h"
#include "game/window.h"
#include "game/vibrator.h"
#include "overlays/msetup_internal.h"

typedef struct MsetupDifficultySprites {
    s16 sprites[8];
    Vec2f position;
    s16 alpha[4];
    s16 alphaStep[4];
    s16 active[4];
    s16 delay[4];
} MsetupDifficultySprites;

typedef struct MsetupPlayerSprites {
    s16 sprites[8];
    s16 unused[8];
    s16 portraits[8];
    s16 windows[2];
} MsetupPlayerSprites;

typedef struct MsetupSelectionEntry {
    s16 group;
    s16 normal;
    s16 selected;
    s16 flags;
} MsetupSelectionEntry;

typedef struct MsetupSelectionCursor {
    MsetupSelectionEntry *entries;
    s16 pos[2];
    s16 (*positions)[2];
    s16 selection;
    s16 state;
    s16 frames;
    s16 controller;
    s16 priority;
    s16 count;
    s16 result;
} MsetupSelectionCursor;

typedef struct MsetupSelectionData {
    s16 selectionIds[4];
    s16 selections[4];
    s16 sprites[4];
    s16 slots[4];
    u8 disabled[8];
    s16 previousButtons;
} MsetupSelectionData;

extern MsetupEntryAnim D_8011A9E0_msetup[];
extern s16 D_80119FE4_msetup[];
extern Vec D_80119B20_msetup;
extern s32 D_80119B44_msetup[];
extern s16 D_80119B60_msetup[][2];
extern s16 D_80119B90_msetup[][4];
extern s32 D_80119BA0_msetup[];
extern s32 D_80119BD0_msetup[];
extern s32 D_80119BF0_msetup[];
extern u8 D_80119C10_msetup[][3];

extern const char *D_80119E20_msetup[];
extern s32 D_80119E38_msetup[];
extern s16 D_80119E50_msetup[];
extern s16 D_80119E54_msetup[];

extern s32 D_80119E58_msetup[];
extern s32 D_80119E64_msetup[];
extern s32 D_80119E70_msetup[];
extern s32 D_80119E7C_msetup[];
extern s32 D_80119E88_msetup[];
extern Process *D_80119420_msetup;
extern s32 D_80119E18_msetup[];
extern s32 D_80119E94_msetup[];
extern s32 D_80119EAC_msetup[];
extern s32 D_80119EC4_msetup[];
extern s32 D_80119EE0_msetup[];
extern s32 D_80119EFC_msetup[];
extern s32 D_80119F14_msetup[];
extern s16 D_8011A938_msetup;
extern s16 D_8011A948_msetup;
extern s16 D_8011A990_msetup;
extern MsetupPlayerConfig D_8011AA30_msetup;
extern Vec D_8011A028_msetup[];
extern s16 D_8011A058_msetup[4][4];
extern s16 D_8011A078_msetup[4][4];
extern s16 D_8011A8E0_msetup[4][4];
extern s16 (*D_80119FF0_msetup[])(MsetupMenuState *);
extern s32 D_8011A098_msetup[];
extern f32 D_8011A0A8_msetup[];
extern f32 D_8011A0B8_msetup[];
extern s32 D_80119B34_msetup[];
extern s32 D_80119FDC_msetup[];
extern s32 D_80119FD4_msetup[];
extern MsetupModelTarget D_80119F94_msetup[];
extern MsetupModelTarget D_80119FB4_msetup[];

extern const char D_8011A6D8_msetup[];
extern const char D_8011A7D8_msetup[];
extern const char D_8011A7E0_msetup[];
extern const char D_8011A7E8_msetup[];
extern const char D_8011A7F0_msetup[];
extern const char D_8011A7F8_msetup[];
extern f32 D_8011A908_msetup;
extern u8 D_8011AA42_msetup; // Alias of D_8011AA30_msetup.totalTurns.
extern f32 D_80119F4C_msetup[];
extern s16 D_80119F6C_msetup[];
extern s16 D_80119F78_msetup[];
extern const char D_8011A800_msetup[];
extern s32 D_80119F3C_msetup[];
extern f32 D_80119F60_msetup[];
extern s32 D_80119F8C_msetup[];

extern s16 D_80119DFC_msetup[][2];
extern s16 (*D_80119E0C_msetup[])[2];
extern s32 D_80119B2C_msetup[];
extern MsetupModelTarget D_80119DC8_msetup[];

extern s32 D_80119CC0_msetup[];
extern s32 D_80119CE0_msetup[];
extern s32 D_80119D00_msetup[];
extern s32 D_80119D20_msetup[];
extern s32 D_80119AD0_msetup[];
extern s16 D_80119CB0_msetup[];

extern MsetupModelTarget D_80119C48_msetup[];
extern MsetupModelTarget D_80119C28_msetup[];
extern u8 D_80119C68_msetup[];
extern s32 D_80119C70_msetup[];
extern const char *D_80119D68_msetup[];
extern s32 D_80119D88_msetup[];
extern s32 D_80119DA8_msetup[];
extern s32 D_80119DB8_msetup[];
extern Process *D_8011A900_msetup;
extern MsetupPortraitState D_8011A904_msetup;

s16 func_80115A9C_msetup(s16, s16, HuMtx4F, s16 *, s16);
void func_8010E32C_msetup(Array2D *, s32, f32, s32);
void func_800332D4_main(s16, f32);

void func_8010F43C_msetup(s16 model, char *node, Vec2f *screenPos);
void func_80017D24_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void espTPLvlSet(u16, s16);
void espAttrSet(u16, s32);
void espPriSet(u16, s32);
void espScaleSet(u16, f32, f32);
void espKill(u16);
void Hu3DModelKill(s16);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void func_8001C258_main(s16, s32, s32);
void HuSprKill(s16);
s32 _CheckFlag(s32);            /* extern */
s16 HuSprAnimRead(void *); /* extern */
s32 func_801138F8_msetup(MsetupMenuState *, s32, s32 *, s32);
s16 func_80113ED4_msetup(MsetupMenuState *arg0);

s16 HmfAnimRead(HmfData *, s32, char *);
HmfMotionNode *func_8001D33C_main(s16, char *);
void func_8002367C_main(HuMtx4F, HuMtx4F);

void func_80112804_msetup(void);

void func_8010F4E0_msetup(MsetupLinkedModel *models, s16 count, s16 layout) {
    Vec pos;
    s16 *positions[4];
    s32 i;
    s32 frame;
    f32 progress;
    Vec *start;

    if (count == 3) {
        for (i = 0; i < 4; i++) {
            positions[i] = D_8011A078_msetup[i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            positions[i] = D_8011A058_msetup[i];
        }
    }
    for (i = 0; i < count; i++) {
        models[i].targetPosition = positions[layout][i];
    }
    for (frame = 0; frame < 15; frame++) {
        progress = sindf(frame * (90.0f / 14.0f));
        for (i = 0; i < count; i++) {
            start = &D_8011A028_msetup[models[i].currentPosition];
            pos = D_8011A028_msetup[models[i].targetPosition];
            pos.x -= start->x;
            pos.y -= start->y;
            pos.z -= start->z;
            pos.x *= progress;
            pos.y *= progress;
            pos.z *= progress;
            pos.x += start->x;
            pos.y += start->y;
            pos.z += start->z;
            Hu3DModelPosSet(models[i].model, pos.x, pos.y, pos.z);
            if (models[i].targetPosition == 0) {
                Hu3DModelRotSet(models[i].model, 0, sindf(frame * (90.0f / 14.0f)) * 180.0f, 0);
            } else if (models[i].currentPosition == 0) {
                Hu3DModelRotSet(models[i].model, 0, 180.0f - sindf(frame * (90.0f / 14.0f)) * 180.0f, 0);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        start = &D_8011A028_msetup[models[i].targetPosition];
        Hu3DModelPosSet(models[i].model, start->x, start->y, start->z);
        models[i].pos = *start;
        models[i].currentPosition = models[i].targetPosition;
    }
}

s16 func_8010F87C_msetup(MsetupMenuState *state) {
    MsetupLinkedModel models[4];
    Vec pos;
    s16 *positions[4];
    s16 previousButtons;
    s16 model;
    s16 selection;
    s16 modelCount;
    s16 frame;
    s32 i;
    omObjData *cursor = NULL;
    s16 refresh;
    u16 buttons;
    s16 connected;
    s32 count;
    Vec *rot;
    MsetupLinkedModel *entry;
    s16 position;
    f32 angle;
    f32 progress;
    Vec *target;

    connected = D_8011AA30_msetup.connectedCount;
    if (state->result < 0) {
        i = D_8011AA30_msetup.humanCount;
        for (selection = 0; selection < 4; selection++) {
            if (i == D_8011A0B8_msetup[selection]) {
                break;
            }
        }
        selection = selection < 4 ? selection : 0;
        state->result = selection;
    } else {
        if (state->result >= 4) {
            state->result = 0;
        }
        selection = state->result;
    }
    count = connected;
    if (count < D_8011A0B8_msetup[selection]) {
        for (selection = 0; selection < 4; selection++) {
            if (count == D_8011A0B8_msetup[selection]) {
                break;
            }
        }
        selection = selection < 4 ? selection : 0;
        state->result = selection;
    }
    func_8010B998_msetup();
    modelCount = connected;
    if (modelCount < 2) {
        modelCount = 2;
    }
    for (i = 0; i < modelCount; i++) {
        model = func_8000B108_main(0x140003, 0x2A9);
        models[i].model = model;
        models[i].unk1A = HmfAnimRead(HmfModelData[model].hmf, D_8011A098_msetup[i], (char *)D_8011A6D8_msetup);
        func_800332D4_main(models[i].unk1A, 0.75f);
        func_8001C448_main(model);
        func_8001C514_main(model);
        entry = &models[i];
        entry->flags = 0;
        rot = &entry->rot;
        rot->x = rot->y = rot->z = 0;
        if (i & 1) {
            entry->rot.y = 180.0f;
        }
        Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
        target = &entry->pos;
        *target = D_80119B20_msetup;
        Hu3DModelPosSet(model, target->x, target->y, target->z);
        Hu3DModelScaleSet(model, 0.1, 0.1, 0.1);
        HuPrcVSleep();
    }
    if (modelCount == 3) {
        for (i = 0; i < 4; i++) {
            positions[i] = D_8011A078_msetup[i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            positions[i] = D_8011A058_msetup[i];
        }
    }
    if (connected >= 2) {
        cursor = func_8010DE38_msetup(64, 256, 64);
    }
    func_8010B82C_msetup(0x1503);
    refresh = 1;
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup((Array2D *)models, modelCount, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    if (connected >= 2) {
        cursor->work[0] = 1;
        cursor->work[1] = 36;
        for (frame = 0; frame < 7; frame++) {
            progress = frame / 7.0f;
            for (i = 0; i < modelCount; i++) {
                position = positions[selection][i];
                entry = &models[i];
                target = &D_8011A028_msetup[position];
                pos.x = (target->x - entry->pos.x) * progress;
                pos.y = (target->y - entry->pos.y) * progress;
                pos.z = (target->z - entry->pos.z) * progress;
                pos.x += entry->pos.x;
                pos.y += entry->pos.y;
                pos.z += entry->pos.z;
                angle = (D_8011A0A8_msetup[position] - entry->rot.y) * progress;
                model = entry->model;
                Hu3DModelRotSet(model, entry->rot.x, angle + entry->rot.y, entry->rot.z);
                Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            }
            HuPrcVSleep();
        }
        for (i = 0; i < modelCount; i++) {
            position = positions[selection][i];
            entry = &models[i];
            entry->pos = D_8011A028_msetup[position];
            entry->rot.y = D_8011A0A8_msetup[position];
            model = entry->model;
            Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
        }
    } else {
        func_8001C258_main(models[1].model, 4, 4);
        angle = models[0].rot.y;
        progress = 180.0f / 7.0f;
        model = models[0].model;
        for (frame = 0; frame < 7; frame++) {
            angle += progress;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            Hu3DModelRotSet(model, 0, angle, 0);
            HuPrcVSleep();
        }
        models[0].rot.y = angle;
    }
    for (i = 0; i < modelCount; i++) {
        models[i].targetPosition = models[i].currentPosition = positions[selection][i];
    }
    refresh = 1;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    while (1) {
        if (refresh) {
            func_8010B82C_msetup(D_80119B34_msetup[state->result]);
            refresh = 0;
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                state->result = -1;
                break;
            }
            func_8010B82C_msetup(0x1503);
            refresh = 1;
            func_8010B858_msetup();
            buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        } else if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            i = D_8011A0B8_msetup[state->result];
            D_8011AA30_msetup.humanCount = i;
            D_8011AA30_msetup.cpuCount = 4 - i;
            for (i = 0; i < D_8011AA30_msetup.humanCount; i++) {
                RepeatVibrator(D_8011AA30_msetup.controllerPorts[i], 10, 0, 10);
            }
            break;
        }
        if (connected >= 2) {
            if (buttons & 0x900) {
                state->result++;
                if (state->result >= connected) {
                    state->result = 0;
                }
                cursor->work[0] = 4;
            } else if (buttons & 0x600) {
                state->result--;
                if (state->result < 0) {
                    state->result = connected - 1;
                }
                cursor->work[0] = 3;
            }
        }
        if (selection != state->result) {
            HuAudFXPlay(1);
            func_8010F4E0_msetup(models, modelCount, state->result);
            refresh = 1;
            selection = state->result;
        }
        HuPrcVSleep();
    }
    if (connected >= 2) {
        cursor->work[0] = 2;
        cursor->work[1] = 17;
    } else {
        angle = models[0].rot.y;
        progress = 180.0f / 7.0f;
        model = models[0].model;
        for (frame = 0; frame < 7; frame++) {
            angle += progress;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            Hu3DModelRotSet(model, 0, angle, 0);
            HuPrcVSleep();
        }
        models[0].rot.y = angle;
        func_8001C258_main(models[1].model, 4, 0);
    }
    func_8010B998_msetup();
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup((Array2D *)models, modelCount, 7, 360.0f, 400.0f, 1.0f, 0.1f, 4);
    if (connected >= 2) {
        func_8010DDD8_msetup(cursor);
    }
    for (i = 0; i < modelCount; i++) {
        func_80033430_main(models[i].unk1A);
        Hu3DModelKill(models[i].model);
    }
    return 0;
}

void func_8011035C_msetup(void) {
    s16 previousSelection;
    MsetupPlayerSprites sprites;
    s16 group;
    s16 unusedGroup = -1;
    s16 sprite;
    MsetupPortraitState *state;
    s32 i;
    s16 member;
    s16 currentState;
    s16 active;
    s16 window;
    s16 initialSelection;
    s16 selection;

    i = 0;
    state = HuPrcCurrentGet()->user_data;
    for (; i < 8; i++) {
        sprites.unused[i] = -1;
        sprites.sprites[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        sprites.windows[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        sprites.portraits[i] = func_8000B838_main(D_80119BA0_msetup[i]);
        if (i & 1) {
            HuPrcVSleep();
        }
    }
    group = HuSprGrpCreate(8, 0);
    for (member = 0; member < 8; member++) {
        if (member == 7) {
            sprite = sprites.portraits[state->unk02];
        } else {
            sprite = func_8000B838_main(D_80119B44_msetup[member]);
            sprites.sprites[member] = sprite;
        }
        HuSprTPLvlSet(group, member, 256);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprAttrSet(group, member, 0x9000);
        HuSprScaleSet(group, member, 1.0f, 1.0f);
        func_800550F4_main(group, member, 1);
        func_80055024_main(group, member, sprite, 0);
        HuSprPriSet(group, member, 15000);
        HuSprPosSet(group, member, D_80119B60_msetup[member][0], D_80119B60_msetup[member][1]);
        HuPrcVSleep();
    }
    i = 0;
    member = 4;
    initialSelection = state->unk02;
    for (; i < 2; i++, member++) {
        func_80054FF8_main(group, member, D_80119C10_msetup[initialSelection][i]);
    }
    for (i = 0; i < 2; i++) {
        window = HuWinCreate(D_80119B90_msetup[i][0], D_80119B90_msetup[i][1],
                                    D_80119B90_msetup[i][2], D_80119B90_msetup[i][3], 0, 12);
        sprites.windows[i] = window;
        HuWinMesSpeedSet(window, 0);
        HuWinBGTPLvlSet(window, 0);
        HuWinBGColSet(window, 255, 255, 255);
        HuWinHomeClear(window);
        HuWinDispOff(window);
        HuPrcVSleep();
    }
    HuWinComKeyReset();
    active = 0;
    previousSelection = state->unk02;
    currentState = 0;
    do {
        if (currentState != state->state) {
            switch (state->state) {
                case 0:
                    break;
                case 1:
                    for (i = 0; i < 8; i++) {
                        HuSprAttrReset(group, i, 0x8000);
                    }
                    HuWinDispOn(sprites.windows[0]);
                    previousSelection = -1;
                    HuWinDispOn(sprites.windows[1]);
                    active = 1;
                    break;
                case 2:
                    for (i = 0; i < 8; i++) {
                        HuSprAttrSet(group, i, 0x8000);
                    }
                    active = 0;
                    HuWinDispOff(sprites.windows[0]);
                    HuWinDispOff(sprites.windows[1]);
                    break;
            }
            currentState = state->state;
        }
        if (active != 0) {
            if (previousSelection != state->unk02) {
                selection = state->unk02;
                func_80055024_main(group, 7, sprites.portraits[state->unk02], 0);
                i = 0;
                member = 4;
                for (; i < 3; i++, member++) {
                    func_80054FF8_main(group, member, D_80119C10_msetup[selection][i]);
                }
                HuWinMesSet(sprites.windows[0], D_80119BD0_msetup[selection], -1, -1);
                HuWinHomeClear(sprites.windows[1]);
                HuWinMesSet(sprites.windows[1], D_80119BF0_msetup[selection], -2, -1);
                previousSelection = state->unk02;
            }
        }
        HuPrcVSleep();
    } while (currentState != 3);
    for (i = 0; i < 8; i++) {
        if (sprites.portraits[i] >= 0) {
            HuSprKill(sprites.portraits[i]);
        }
    }
    for (i = 0; i < 8; i++) {
        if (sprites.sprites[i] >= 0) {
            HuSprKill(sprites.sprites[i]);
        }
    }
    if (group >= 0) {
        HuSprGrpKill(group);
    }
    if (unusedGroup >= 0) {
        HuSprGrpKill(unusedGroup);
    }
    for (i = 0; i < 2; i++) {
        if (sprites.windows[i] >= 0) {
            HuWinKill(sprites.windows[i]);
        }
    }
    state->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80110954_msetup(void) {
    MsetupSelectionData data;
    MsetupSelectionCursor *cursor;
    s16 *position;
    s32 *messages;
    s16 sprite;
    s16 slot;
    s16 previousState;
    s16 visible;
    s16 alpha;
    s16 alphaDelta;
    s16 x;
    s16 y;
    s16 startX;
    s16 startY;
    s16 targetX;
    s16 targetY;
    s16 deltaX;
    s16 deltaY;
    s16 offsetX;
    s16 offsetY;
    s16 previousSelection;
    s16 frames;
    s16 updateGlobal;
    s16 selection;
    s16 selectedCount;
    s16 refresh;
    s16 enabled;
    s32 i;
    s16 nextSelection;
    s16 buttons;
    f32 weight;

    cursor = HuPrcCurrentGet()->user_data;
    updateGlobal = 0;
    switch (D_8011A938_msetup) {
        case 0:
        default:
            messages = D_80119CC0_msetup;
            break;
        case 1:
            messages = D_80119CE0_msetup;
            updateGlobal = 1;
            break;
        case 5:
            messages = D_80119D00_msetup;
            break;
        case 6:
            messages = D_80119D20_msetup;
            break;
    }
    if (cursor->priority < 0) {
        sprite = func_8000B838_main(0x11000E);
        slot = espEntry(sprite, 0, 1);
    } else {
        sprite = func_8000B838_main(0x140042);
        slot = espEntry(sprite, cursor->priority, 1);
    }
    espPriSet(slot, 1);
    position = cursor->pos;
    offsetX = (cursor->priority & 1) ? 1 : -1;
    offsetY = (cursor->priority & 2) ? 1 : -1;
    if (cursor->positions != NULL && cursor->selection >= 0) {
        cursor->pos[0] = offsetX + cursor->positions[cursor->selection][0];
        cursor->pos[1] = offsetY + cursor->positions[cursor->selection][1];
    }
    x = targetX = position[0];
    y = targetY = position[1];
    espPosSet(slot, x, y);
    espDispOff(slot);
    visible = 0;
    alpha = 0;
    alphaDelta = 0;
    previousSelection = cursor->selection;
    frames = 0;
    previousState = cursor->state;
    startX = x;
    startY = y;
    deltaX = deltaY = 0;
    selection = previousSelection;
    cursor->result = 0;
    selectedCount = 0;
    enabled = 0;
    for (i = 0; i < cursor->count; i++) {
        data.selectionIds[i] = cursor->priority + (s16)(i + 1);
    }
    i = 0;
    HuPrcVSleep();
    for (; i < 4; i++) {
        data.sprites[i] = data.slots[i] = -1;
    }
    for (i = 0; i < cursor->count; i++) {
        data.sprites[i] = func_8000B838_main(D_80119AD0_msetup[cursor->priority]);
        data.slots[i] = espEntry(data.sprites[i], 0, 1);
        espPriSet(data.slots[i], 2);
        espScaleSet(data.slots[i], 0.75f, 0.75f);
        espTPLvlSet(data.slots[i], 256);
        espDispOff(data.slots[i]);
    }
    refresh = 0;
    HuPrcVSleep();
    if (updateGlobal) {
        D_8011A904_msetup.unk02 = selection;
    }
    while (1) {
        if (previousState != cursor->state) {
            switch (cursor->state) {
                case 0:
                    break;
                case 1:
                    alphaDelta = 64;
                    if (!visible) {
                        if (cursor->result == 1) {
                            selectedCount--;
                            i = data.selections[selectedCount];
                            if (data.selectionIds[selectedCount] == cursor->entries[i].flags) {
                                cursor->entries[i].flags = 0;
                                HuSprAttrSet(cursor->entries[i].group, cursor->entries[i].selected, 0x8000);
                                HuSprAttrReset(cursor->entries[i].group, cursor->entries[i].normal, 0x8000);
                                espDispOff(data.slots[selectedCount]);
                            }
                        }
                        cursor->result = 0;
                        alpha = 0;
                        espTPLvlSet(slot, 0);
                        espDispOn(slot);
                        func_8010D684_msetup(cursor->controller, &data.previousButtons);
                        func_8010D684_msetup(cursor->controller, &data.previousButtons);
                        visible = 1;
                        refresh = 1;
                        selection = previousSelection;
                        enabled = 1;
                        if (!(cursor->entries[selection].flags & 0xFFEF)) {
                            cursor->entries[selection].flags = 0x10;
                        }
                    }
                    break;
                case 2:
                    if (visible) {
                        alphaDelta = -64;
                        visible = 0;
                        enabled = 0;
                        if (!(cursor->entries[selection].flags & 0xFFEF)) {
                            cursor->entries[selection].flags = 0;
                        }
                        HuSprAttrSet(cursor->entries[selection].group, cursor->entries[selection].selected, 0x8000);
                        HuSprAttrReset(cursor->entries[selection].group, cursor->entries[selection].normal, 0x8000);
                    }
                    break;
                case -1:
                    espKill(slot);
                    HuSprKill(sprite);
                    for (i = 0; i < 4; i++) {
                        if (data.slots[i] >= 0) {
                            espKill(data.slots[i]);
                        }
                        if (data.sprites[i] >= 0) {
                            HuSprKill(data.sprites[i]);
                        }
                    }
                    cursor->state = 100;
                    while (1) {
                        HuPrcVSleep();
                    }
                    break;
            }
            previousState = cursor->state;
        }
        if (visible) {
            if (refresh) {
                if (cursor->priority == 4) {
                    func_8010B82C_msetup(messages[selection]);
                }
                if (updateGlobal) {
                    D_8011A904_msetup.unk02 = selection;
                }
                HuSprAttrSet(cursor->entries[selection].group, cursor->entries[selection].normal, 0x8000);
                HuSprAttrReset(cursor->entries[selection].group, cursor->entries[selection].selected, 0x8000);
                refresh = 0;
            }
            buttons = func_8010D684_msetup(cursor->controller, &data.previousButtons);
            if (buttons & B_BUTTON) {
                HuAudFXPlay(4);
                if (selectedCount) {
                    selectedCount--;
                    i = data.selections[selectedCount];
                    if (data.selectionIds[selectedCount] == cursor->entries[i].flags) {
                        cursor->entries[i].flags = 0;
                        if (i == selection) {
                            cursor->entries[i].flags = 0x10;
                        } else {
                            HuSprAttrSet(cursor->entries[i].group, cursor->entries[i].selected, 0x8000);
                            HuSprAttrReset(cursor->entries[i].group, cursor->entries[i].normal, 0x8000);
                        }
                        espDispOff(data.slots[selectedCount]);
                    }
                    cursor->result = 0;
                    enabled = 1;
                } else {
                    cursor->result = -1;
                }
            } else if (enabled) {
                if ((buttons & A_BUTTON) && !(cursor->entries[selection].flags & 0xFFEF)) {
                    if (cursor->priority != 4) {
                        func_8004AC5C_main(D_80119CB0_msetup[selection], cursor->controller);
                        RepeatVibrator(cursor->controller, 5, 0, 5);
                    } else {
                        HuAudFXPlay(D_80119CB0_msetup[selection]);
                    }
                    cursor->entries[selection].flags = data.selectionIds[selectedCount];
                    HuSprAttrSet(cursor->entries[selection].group, cursor->entries[selection].normal, 0x8000);
                    HuSprAttrReset(cursor->entries[selection].group, cursor->entries[selection].selected, 0x8000);
                    data.selections[selectedCount] = selection;
                    espPosSet(data.slots[selectedCount], targetX, targetY + 13);
                    espDispOn(data.slots[selectedCount]);
                    selectedCount++;
                    if (selectedCount >= cursor->count) {
                        cursor->result = 1;
                        enabled = 0;
                    } else {
                        for (i = selection + 1; i < 8; i++) {
                            if (cursor->entries[i].flags == 0) {
                                break;
                            }
                        }
                        if (i < 8) {
                            selection = i;
                        } else {
                            for (i = 0; i < selection; i++) {
                                if (cursor->entries[i].flags == 0) {
                                    break;
                                }
                            }
                            if (i >= 8) {
                                i = 0;
                            }
                            selection = i;
                        }
                        cursor->selection = selection;
                        cursor->entries[(s16)i].flags = 0x10;
                        refresh = 1;
                    }
                }
            }
            if (enabled && (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD))) {
                for (i = 0; i < 8; i++) {
                    data.disabled[i] = cursor->entries[i].flags;
                }
                nextSelection = func_8010D4DC_msetup(cursor->positions, data.disabled, 8, selection, cursor->controller, buttons);
                if (nextSelection >= 0) {
                    HuAudFXPlay(1);
                    if (!(cursor->entries[selection].flags & 0xFFEF)) {
                        cursor->entries[selection].flags = 0;
                    }
                    HuSprAttrSet(cursor->entries[selection].group, cursor->entries[selection].selected, 0x8000);
                    HuSprAttrReset(cursor->entries[selection].group, cursor->entries[selection].normal, 0x8000);
                    selection = nextSelection;
                    cursor->selection = selection;
                    cursor->entries[selection].flags = 0x10;
                    refresh = 1;
                }
            }
        }
        if (previousSelection != cursor->selection) {
            s16 current = cursor->selection;
            previousSelection = current;
            if (cursor->positions != NULL) {
                position[0] = offsetX + cursor->positions[current][0];
                position[1] = offsetY + cursor->positions[current][1];
            }
            selection = previousSelection;
        }
        if (targetX != position[0] || targetY != position[1]) {
            targetX = position[0];
            targetY = position[1];
            frames = cursor->frames;
            if (frames) {
                startX = x;
                startY = y;
                deltaX = targetX - x;
                deltaY = targetY - y;
            }
        }
        if (alphaDelta) {
            alpha += alphaDelta;
            if (alpha >= 256) {
                alpha = 255;
                alphaDelta = 0;
                cursor->state = 0;
            } else if (alpha < 0) {
                alpha = 0;
                alphaDelta = 0;
                espDispOff(slot);
                visible = 0;
                cursor->state = 0;
            }
            espTPLvlSet(slot, alpha);
        }
        if ((x != targetX) | (y != targetY)) {
            if (!frames) {
                x = targetX;
                y = targetY;
            } else {
                frames--;
                weight = sindf((90.0f / cursor->frames) * (cursor->frames - frames));
                x = startX + deltaX * weight;
                y = startY + deltaY * weight;
            }
            espPosSet(slot, x, y);
        }
        HuPrcVSleep();
    }
}

s16 func_80111650_msetup(MsetupMenuState *state) {
    MsetupLinkedModel models[2];
    MsetupSelectionEntry entries[8];
    MsetupSelectionCursor cursors[4];
    Process *processes[4];
    s16 sprites[16];
    Vec2f position;
    s16 positions[8][2];
    s32 spriteIds[2];
    s8 selections[4];
    s16 model;
    s32 *messages;
    s16 group;
    s16 cpuCount;
    s16 humanCount;
    s16 initialState;
    s16 slot;
    s16 sprite;
    s32 j;
    s16 index;
    s16 menuState;
    s32 member;
    s16 spriteIndex;
    s32 i;
    s16 flags;
    s16 alpha;
    s16 count;
    s16 firstCpuIndex;
    s16 characterSprite;
    MsetupSelectionCursor *cursor;

    func_8010B998_msetup();
    state->result = 0;
    D_8011A900_msetup = NULL;
    slot = sprite = -1;
    switch (D_8011A938_msetup) {
        default:
        case 0:
            messages = D_80119DA8_msetup;
            break;
        case 1:
            messages = D_80119DB8_msetup;
            D_8011A904_msetup.state = 0;
            D_8011A904_msetup.unk02 = 0;
            D_8011A900_msetup = omAddPrcObj(func_8011035C_msetup, 0x3F00, 0x600, 0);
            D_8011A900_msetup->user_data = &D_8011A904_msetup;
            break;
    }
    func_8010E4BC_msetup(&models, 2, 90.0f);
    func_8010E4D8_msetup(models, 2);
    model = func_8000B108_main(0x140007, 0x289);
    func_8001C448_main(model);
    func_8001C258_main(model, 4, 4);
    Hu3DModelScaleSet(model, 1.2f, 1.2f, 1.2f);
    Hu3DModelPosSet(model, 0, 300, -280);
    func_8001C814_main(model, 1, 1);
    group = HuSprGrpCreate(16, 0);
    for (i = 0; i < 8; i++) {
        func_8010F43C_msetup(model, (char *)D_80119D68_msetup[i], &position);
        spriteIds[0] = D_80119D88_msetup[i];
        spriteIds[1] = D_80119C70_msetup[i];
        spriteIndex = 0;
        if (i == 3) {
            spriteIndex = -(_CheckFlag(0x2E) == 0);
        } else if (i == 7) {
            if (!_CheckFlag(0x2F)) {
                spriteIndex = -1;
            }
        }
        if (spriteIndex == -1) {
            spriteIds[0] = 0x14001C;
            spriteIds[1] = 0x14001C;
        }
        entries[i].group = group;
        entries[i].normal = i;
        entries[i].selected = i + 8;
        entries[i].flags = spriteIndex;
        positions[i][0] = position.x + 6;
        positions[i][1] = position.y - 2;
        for (j = 0, member = i; j < 2; j++, member += 8) {
            characterSprite = func_8000B838_main(spriteIds[j]);
            sprites[member] = characterSprite;
            HuSprTPLvlSet(group, member, 0x100);
            HuSprAttrReset(group, member, 0xFFFF);
            HuSprAttrSet(group, member, 0x9000);
            HuSprScaleSet(group, member, 1.0f, 1.0f);
            func_800550F4_main(group, member, 0);
            func_80055024_main(group, member, characterSprite, 0);
            HuSprPriSet(group, member, 600);
            HuSprPosSet(group, member, position.x, position.y);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        processes[i] = NULL;
        selections[i] = -1;
    }
    humanCount = D_8011AA30_msetup.humanCount;
    cpuCount = D_8011AA30_msetup.cpuCount;
    count = humanCount;
    firstCpuIndex = humanCount;
    if (cpuCount) {
        count = firstCpuIndex + 1;
    }
    for (i = 0; i < humanCount; i++) {
        if (entries[i].flags == 0) {
            selections[i] = i;
        } else {
            for (index = i + 1; index < 8; index++) {
                if (entries[index].flags == 0) {
                    break;
                }
            }
            if (index >= 8) {
                index = i;
            }
            selections[i] = index;
        }
    }
    for (i = 0; i < count; i++) {
        processes[i] = omAddPrcObj(func_80110954_msetup, 0x3F00, 0x800, 0);
        cursor = &cursors[i];
        processes[i]->user_data = cursor;
        cursor->entries = entries;
        cursor->positions = positions;
        cursor->state = 0;
        if (i < humanCount) {
            cursor->priority = i;
            cursor->controller = D_8011AA30_msetup.controllerPorts[i];
            cursor->selection = selections[i];
            cursor->frames = 4;
            cursor->count = 1;
        } else {
            cursor->priority = 4;
            cursor->controller = D_8011A948_msetup;
            cursor->selection = 0;
            cursor->frames = 0;
            cursor->count = cpuCount;
        }
        cursor->result = 0;
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720, 565, 0.1f, 1.0f, 1);
    Hu3DModelPosSet(model, 0, 300, -280);
    func_8001C258_main(model, 4, 0);
    func_8010E52C_msetup(models, D_80119C28_msetup, 2, 7, &model, 1, 0.1f, 1.2f);
    for (i = 0; i < 8; i++) {
        HuSprAttrReset(group, i, 0x8000);
    }
    for (alpha = 0; alpha < 256; alpha += 36) {
        for (i = 0; i < 8; i++) {
            HuSprTPLvlSet(group, i, alpha);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        HuSprTPLvlSet(group, i, 256);
    }
    switch (D_8011A938_msetup) {
        default:
        case 0:
            initialState = 0;
            menuState = 0;
            break;
        case 1:
            initialState = 2;
            menuState = 2;
            D_8011A904_msetup.unk02 = 0;
            D_8011A904_msetup.state = 1;
            break;
        case 6:
            initialState = 3;
            menuState = 3;
            i = D_8011AA30_msetup.characters[0];
            for (index = 0; index < 8; index++) {
                if (D_80119C68_msetup[index] == i) {
                    break;
                }
            }
            index = index < 8 ? index : 0;
            entries[index].flags = 1;
            sprite = func_8000B838_main(D_80119AD0_msetup[0]);
            slot = espEntry(sprite, 0, 1);
            espPriSet(slot, 2);
            espScaleSet(slot, 0.75f, 0.75f);
            espTPLvlSet(slot, 256);
            espPosSet(slot, positions[index][0], positions[index][1] + 12);
            HuSprAttrSet(group, entries[index].normal, 0x8000);
            HuSprAttrReset(group, entries[index].selected, 0x8000);
            break;
    }
    do {
        switch (menuState) {
            case 0:
                func_8010B82C_msetup(messages[0]);
                func_8010B858_msetup();
                for (i = 0; i < humanCount; i++) {
                    cursors[i].state = 1;
                }
                do {
                    HuPrcVSleep();
                    index = 0;
                    flags = 1;
                    for (i = 0; i < humanCount; i++) {
                        if (cursors[i].result > 0) {
                            index++;
                        }
                    }
                    flags = cursors[0].result < 0 ? 0 : flags;
                } while ((flags != 0) & (index < humanCount));
                for (i = 0; i < humanCount; i++) {
                    cursors[i].state = 2;
                    spriteIndex = cursors[i].priority + 1;
                    for (index = 0; index < 8; index++) {
                        if (spriteIndex == entries[index].flags) {
                            break;
                        }
                    }
                    D_8011AA30_msetup.characters[i] = D_80119C68_msetup[index];
                    D_8011AA30_msetup.cpuDifficulty[i] = 0xFF;
                }
                menuState = cpuCount ? 1 : -1;
                if (!flags) {
                    menuState = -1;
                    state->result = menuState;
                }
                break;
            case 1:
                func_8010B82C_msetup(messages[cpuCount]);
                func_8010B858_msetup();
                cursor = &cursors[firstCpuIndex];
                for (i = 0; i < 8; i++) {
                    if (entries[i].flags == 0) {
                        break;
                    }
                }
                i = i < 8 ? i : 0;
                cursor->frames = 0;
                cursor->selection = i;
                HuPrcVSleep();
                cursor->frames = 4;
                cursor->state = 1;
                do {
                    HuPrcVSleep();
                } while (cursor->result == 0);
                cursor->state = 2;
                if (cursor->result < 0) {
                    menuState = initialState;
                } else {
                    for (index = 0; index < 8; index++) {
                        if (cursor->priority < entries[index].flags) {
                            i = firstCpuIndex + (s16)(entries[index].flags - cursor->priority - 1);
                            if (i < 4) {
                                D_8011AA30_msetup.characters[i] = D_80119C68_msetup[index];
                                D_8011AA30_msetup.cpuDifficulty[i] = 1;
                            }
                        }
                    }
                    menuState = -1;
                }
                break;
            case 2:
                func_8010B82C_msetup(messages[0]);
                func_8010B858_msetup();
                menuState = cpuCount ? 1 : -1;
                for (index = 0; index < humanCount; index++) {
                    cursor = &cursors[index];
                    spriteIndex = cursor->priority + 1;
                    for (i = 0; i < 8; i++) {
                        if (spriteIndex == entries[i].flags) {
                            break;
                        }
                    }
                    if (i >= 8) {
                        for (i = 0; i < 8; i++) {
                            if (entries[i].flags == 0) {
                                break;
                            }
                        }
                        i = i < 8 ? i : 0;
                    }
                    cursor->frames = 0;
                    cursor->selection = i;
                    HuPrcVSleep();
                    cursor->frames = 4;
                    cursor->state = 1;
                    do {
                        HuPrcVSleep();
                    } while (cursor->result == 0);
                    cursor->state = 2;
                    if (cursor->result < 0) {
                        index--;
                        if (index < 0) {
                            menuState = -1;
                            state->result = menuState;
                            break;
                        }
                        index--;
                    } else {
                        spriteIndex = cursors[index].priority + 1;
                        for (i = 0; i < 8; i++) {
                            if (spriteIndex == entries[i].flags) {
                                break;
                            }
                        }
                        D_8011AA30_msetup.characters[index] = D_80119C68_msetup[i];
                        D_8011AA30_msetup.cpuDifficulty[index] = 0xFF;
                    }
                }
                break;
            case 3:
                func_8010B82C_msetup(messages[cpuCount]);
                func_8010B858_msetup();
                cursor = &cursors[firstCpuIndex];
                for (i = 0; i < 8; i++) {
                    if (entries[i].flags == 0) {
                        break;
                    }
                }
                i = i < 8 ? i : 0;
                cursor->frames = 0;
                cursor->selection = i;
                HuPrcVSleep();
                cursor->frames = 4;
                cursor->state = 1;
                do {
                    HuPrcVSleep();
                } while (cursor->result == 0);
                cursor->state = 2;
                if (cursor->result < 0) {
                    func_8010B82C_msetup(0x1501);
                    if (func_8010B858_msetup() != 0) {
                        menuState = 3;
                        break;
                    }
                    state->result = -1;
                    goto finish_cpu;
                } else {
                    for (index = 0; index < 8; index++) {
                        if (cursor->priority < entries[index].flags) {
                            i = firstCpuIndex + (s16)(entries[index].flags - cursor->priority - 1);
                            if (i < 4) {
                                D_8011AA30_msetup.characters[i] = D_80119C68_msetup[index];
                                D_8011AA30_msetup.cpuDifficulty[i] = 1;
                            }
                        }
                    }
                }
            finish_cpu:
                menuState = -1;
                espDispOff(slot);
                break;
        }
        HuPrcVSleep();
    } while (menuState >= 0);
    func_8010B998_msetup();
    if (D_8011A900_msetup != NULL) {
        D_8011A904_msetup.state = 2;
    }
    for (i = 0; i < 4; i++) {
        if (processes[i] != NULL) {
            cursors[i].state = -1;
        }
    }
    for (alpha = 256; alpha > 0; alpha -= 36) {
        for (i = 0; i < 16; i++) {
            HuSprTPLvlSet(group, i, alpha);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        HuSprAttrSet(group, i, 0x8000);
    }
    func_8010E52C_msetup(models, D_80119C48_msetup, 2, 7, &model, 1, 1.2f, 0.0f);
    if (D_8011A900_msetup != NULL) {
        D_8011A904_msetup.state = 3;
    }
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360, 400, 1.0f, 0.1f, 1);
    if (D_8011A900_msetup != NULL) {
        omDelPrcObj(D_8011A900_msetup);
    }
    for (i = 0; i < 4; i++) {
        if (processes[i] != NULL) {
            omDelPrcObj(processes[i]);
        }
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    HuSprGrpKill(group);
    for (i = 0; i < 16; i++) {
        HuSprKill(sprites[i]);
    }
    Hu3DModelKill(model);
    if (slot >= 0) {
        espKill(slot);
    }
    if (sprite >= 0) {
        HuSprKill(sprite);
    }
    return 0;
}

/* Keep these strings before the menu process jump table in rodata. */
const char D_8011A6D8_msetup[] = "03tex_DEF";

const char D_8011A6E4_msetup[] = "waruigi_DEF";

const char D_8011A6F0_msetup[] = "donkey_DEF";

const char D_8011A6FC_msetup[] = "wario_DEF";

const char D_8011A708_msetup[] = "yoshi_DEF";

const char D_8011A714_msetup[] = "daisy_DEF";

const char D_8011A720_msetup[] = "peach_DEF";

const char D_8011A72C_msetup[] = "ruigi_DEF";

const char D_8011A738_msetup[] = "mario_DEF";

const char D_8011A744_msetup[] = "waluigi";

const char D_8011A74C_msetup[] = "donkey";

const char D_8011A754_msetup[] = "wario";

const char D_8011A75C_msetup[] = "yoshi";

const char D_8011A764_msetup[] = "daisy";

const char D_8011A76C_msetup[] = "peach";

const char D_8011A774_msetup[] = "luigi";

const char D_8011A77C_msetup[] = "mario";

const char D_8011A784_msetup[] = "kobetu";

const char D_8011A78C_msetup[] = "zenin";

const char D_8011A794_msetup[] = "s_tuyoi";

const char D_8011A79C_msetup[] = "tuyoi";

const char D_8011A7A4_msetup[] = "futuu";

const char D_8011A7AC_msetup[] = "yowai";
const char D_8011A7B4_msetup[4] = "";

void func_80112804_msetup(void) {
    MsetupDifficultySprites sprites;
    s16 group;
    s16 model;
    MsetupMenuState *state;
    s32 i;
    s16 currentState;
    s16 index;
    s32 side;
    s16 first;
    s16 last;

    i = 0;
    state = HuPrcCurrentGet()->user_data;
    model = state->unk02;
    group = HuSprGrpCreate(6, 0);
    for (; i < 6; i++) {
        index = func_8000B838_main(D_80119E38_msetup[i]);
        sprites.sprites[i] = index;
        HuSprTPLvlSet(group, i, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x9000);
        HuSprScaleSet(group, i, 1.0f, 1.0f);
        func_800550F4_main(group, i, 0);
        func_80055024_main(group, i, index, 0);
        HuSprPriSet(group, i, 600);
    }
    for (i = 0; i < 2; i++) {
        sprites.alpha[i] = 0;
        sprites.alphaStep[i] = 0;
        sprites.active[i] = 0;
        sprites.delay[i] = 0;
    }
    currentState = 0;
    do {
        if (currentState != state->state) {
            switch (state->state) {
                case 0:
                    break;
                case 1:
                    index = 0;
                    goto show;
                case 3:
                    index = 1;
                show:
                    if (sprites.active[index] == 0) {
                        sprites.alpha[index] = 0;
                        sprites.alphaStep[index] = 36;
                        sprites.active[index] = 1;
                        sprites.delay[index] = 3;
                    }
                    state->state = 0;
                    break;
                case 2:
                    index = 0;
                    goto hide;
                case 4:
                    index = 1;
                hide:
                    if (sprites.active[index] != 0) {
                        sprites.alpha[index] = 256;
                        sprites.alphaStep[index] = -36;
                        sprites.delay[index] = 0;
                    }
                    state->state = 0;
                    break;
                case 5:
                    index = 0;
                    side = 0;
                    if (sprites.active[0] != 0 && sprites.active[1] == 0) {
                        index = 0;
                        side = 1;
                    } else if (sprites.active[1] != 0 && sprites.active[0] == 0) {
                        index = 1;
                        side = 0;
                    }
                    if ((index != 0) | (side != 0)) {
                        sprites.alpha[index] = 256;
                        sprites.alphaStep[index] = -85;
                        sprites.delay[index] = 0;
                        sprites.alpha[side] = 0;
                        sprites.alphaStep[side] = 85;
                        sprites.active[side] = 1;
                        sprites.delay[side] = 4;
                    }
                    state->state = 0;
                    break;
                case 6:
                    for (index = 0; index < 2; index++) {
                        if (sprites.active[index] != 0) {
                            sprites.alpha[index] = 256;
                            sprites.alphaStep[index] = -36;
                            sprites.delay[index] = 0;
                        }
                    }
                    state->state = 0;
                    break;
                case 7:
                    state->state = -1;
                    break;
            }
            currentState = state->state;
        }
        for (side = 0; side < 2; side++) {
            if (sprites.active[side] != 0) {
                if (sprites.delay[side] != 0) {
                    sprites.delay[side]--;
                } else {
                    first = D_80119E50_msetup[side];
                    last = D_80119E54_msetup[side];
                    if (side == 1 && state->result == 3) {
                        last--;
                    }
                    for (i = first; i <= last; i++) {
                        func_8010F43C_msetup(model, (char *)D_80119E20_msetup[i], &sprites.position);
                        HuSprPosSet(group, i, sprites.position.x, sprites.position.y);
                    }
                    if (sprites.alphaStep[side] != 0) {
                        index = sprites.alpha[side];
                        sprites.alpha[side] += sprites.alphaStep[side];
                        if (sprites.alpha[side] <= 0) {
                            sprites.alpha[side] = 0;
                            sprites.alphaStep[side] = 0;
                            sprites.active[side] = 0;
                            for (i = first; i <= last; i++) {
                                HuSprAttrSet(group, i, 0x8000);
                            }
                        } else if (sprites.alpha[side] >= 256) {
                            sprites.alpha[side] = 256;
                            sprites.alphaStep[side] = 0;
                        } else if (index == 0) {
                            for (i = first; i <= last; i++) {
                                HuSprAttrReset(group, i, 0x8000);
                            }
                        }
                        for (i = first; i <= last; i++) {
                            HuSprTPLvlSet(group, i, sprites.alpha[side]);
                        }
                    }
                }
            }
        }
        HuPrcVSleep();
    } while (currentState >= 0);
    HuSprGrpKill(group);
    for (i = 0; i < 6; i++) {
        if (sprites.sprites[i] >= 0) {
            HuSprKill(sprites.sprites[i]);
        }
    }
    state->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}

s16 func_80112E08_msetup(s16 selection, s16 *previousButtons, MsetupCursorState *cursor) {
    s16 buttons;
    s16 previousSelection;

    func_8010B82C_msetup(0x1514);
    previousSelection = -1;
    func_8010B858_msetup();
    cursor->selection = selection;
    HuPrcVSleep();
    cursor->flags = 4;
    cursor->state = 1;
    func_8010D684_msetup(D_8011A948_msetup, previousButtons);
    while (1) {
        if (previousSelection != selection) {
            previousSelection = selection;
            func_8010B82C_msetup(D_80119E18_msetup[selection]);
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, previousButtons);
        if (buttons & (U_JPAD | R_JPAD)) {
            selection = 0;
        } else if (buttons & (D_JPAD | L_JPAD)) {
            selection = 1;
        }
        if (selection != cursor->selection) {
            HuAudFXPlay(1);
            cursor->selection = selection;
        }
        if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            selection = -1;
            break;
        }
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        HuPrcVSleep();
    }
    cursor->state = 2;
    return selection;
}

s16 func_80112F5C_msetup(s16 individual, s16 count, s16 *previousButtons, MsetupCursorState *cursor) {
    s16 players[4];
    s16 player;
    s16 cpuCount;
    s16 selection;
    s16 previousPlayer;
    s16 i;
    s16 buttons;
    s32 j;
    s32 currentPlayer;

    player = D_8011AA30_msetup.humanCount;
    cpuCount = D_8011AA30_msetup.cpuCount;
    for (i = 0; player < 4; i++, player++) {
        players[i] = player;
    }
    i = 0;
    previousPlayer = -1;
    cursor->flags = 0;
    selection = D_8011AA30_msetup.cpuDifficulty[players[0]];
    cursor->selection = selection;
    HuPrcVSleep();
    HuPrcVSleep();
    cursor->flags = 4;
    cursor->state = 1;
    func_8010D684_msetup(D_8011A948_msetup, previousButtons);
    while (1) {
        if (previousPlayer != i) {
            if (individual != 0) {
                func_8010B968_msetup(D_8011AA30_msetup.characters[players[i]] + 0x1C00, 0);
                func_8010B82C_msetup(0x1518);
            } else {
                func_8010B82C_msetup(0x1517);
            }
            previousPlayer = i;
            selection = D_8011AA30_msetup.cpuDifficulty[players[i]];
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, previousButtons);
        if (buttons & (U_JPAD | R_JPAD)) {
            selection++;
            if (selection >= count) {
                selection = count - 1;
            }
        } else if (buttons & (D_JPAD | L_JPAD)) {
            selection--;
            if (selection < 0) {
                selection = 0;
            }
        }
        if (selection != cursor->selection) {
            HuAudFXPlay(1);
            cursor->selection = selection;
        }
        if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            if (individual != 0) {
                i--;
                if (i < 0) {
                    selection = -1;
                    break;
                }
            } else {
                selection = -1;
                break;
            }
            D_8011A9E0_msetup[players[i]].state = 6;
        }
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            if (individual != 0) {
                currentPlayer = players[i];
                D_8011AA30_msetup.cpuDifficulty[currentPlayer] = selection;
                D_8011A9E0_msetup[currentPlayer].state = 5;
                i++;
                if (i >= cpuCount) {
                    break;
                }
            } else {
                for (j = 0; j < cpuCount; j++) {
                    currentPlayer = players[j];
                    D_8011AA30_msetup.cpuDifficulty[currentPlayer] = selection;
                    D_8011A9E0_msetup[currentPlayer].state = 5;
                }
                break;
            }
        }
        HuPrcVSleep();
    }
    cursor->state = 2;
    return selection;
}

s16 func_801132C4_msetup(MsetupMenuState *state) {
    Process *cursorProcesses[2];
    MsetupCursorState cursors[2];
    MsetupMenuState spriteState;
    Array2D models;
    s16 model;
    s16 previousButtons;
    Process *spriteProcess;
    MsetupCursorState *cursor;
    s32 i;
    s16 step;
    s16 individual;
    s32 difficultyCount;
    s16 result;
    f32 rotation;

    state->result = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 90.0f);
    func_8010E4D8_msetup(models, 2);
    model = func_8000B108_main(0x140007, 0x289);
    func_8001C448_main(model);
    func_8001C258_main(model, 4, 4);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(model, 0.0f, -300.0f, -280.0f);
    func_8001C814_main(model, 1, 1);
    if (_CheckFlag(0x2D)) {
        Hu3DMotionTimeSet(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
        difficultyCount = 4;
    } else {
        Hu3DMotionTimeSet(model, 0.0f);
        difficultyCount = 3;
    }
    if (D_8011AA30_msetup.cpuCount == 1) {
        Hu3DModelRotSet(model, 180.0f, 0.0f, 0.0f);
    }
    spriteState.state = 0;
    spriteState.unk02 = model;
    spriteState.result = difficultyCount;
    spriteProcess = omAddPrcObj(func_80112804_msetup, 0x3F00, 0x800, 0);
    spriteProcess->user_data = &spriteState;
    for (i = 0; i < 2; i++) {
        cursorProcesses[i] = omAddPrcObj(func_8010D6D0_msetup, 0x3F00, 0x800, 0);
        cursor = &cursors[i];
        cursorProcesses[i]->user_data = cursor;
        cursor->pos[0] = 160;
        cursor->pos[1] = 120;
        if ((i == 1) & (difficultyCount == 4)) {
            cursor->positions = D_80119DFC_msetup;
        } else {
            cursor->positions = D_80119E0C_msetup[i];
        }
        cursor->dataId = D_80119B2C_msetup[1 - i];
        cursor->selection = -1;
        cursor->state = 0;
        cursor->flags = 0;
        cursor->priority = 0;
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    Hu3DModelPosSet(model, 0.0f, 300.0f, -280.0f);
    D_8011A990_msetup = 1;
    Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
    func_8001C258_main(model, 4, 0);
    if (D_8011AA30_msetup.cpuCount == 1) {
        spriteState.state = 3;
    } else {
        spriteState.state = 1;
    }
    func_8010E52C_msetup(models, D_80119DC8_msetup, 2, 7, &model, 1, 0.1f, 1.2f);
    step = D_8011AA30_msetup.cpuCount == 1 ? 2 : 1;
    individual = 0;
    do {
        switch (step) {
            case 1:
                result = func_80112E08_msetup(individual, &previousButtons, &cursors[0]);
                if (result < 0) {
                    state->result = -1;
                    goto finishSelection;
                }
                individual = result;
                step++;
                rotation = 0.0f;
                spriteState.state = 5;
                for (i = 0; i < 7; i++) {
                    rotation += 180.0f / 7.0f;
                    Hu3DModelRotSet(model, rotation, 0.0f, 0.0f);
                    HuPrcVSleep();
                }
                break;
            case 2:
                result = func_80112F5C_msetup(individual, difficultyCount, &previousButtons, &cursors[1]);
                step = -1;
                if (result < 0) {
                    step = 1;
                    if (D_8011AA30_msetup.cpuCount == 1) {
                        state->result = -1;
                        step = -1;
                        break;
                    } else {
                        rotation = 180.0f;
                        spriteState.state = 5;
                        for (i = 0; i < 7; i++) {
                            rotation -= 180.0f / 7.0f;
                            Hu3DModelRotSet(model, rotation, 0.0f, 0.0f);
                            HuPrcVSleep();
                        }
                    }
                }
                break;
        }
        goto waitForSelection;
    finishSelection:
        step = -1;
    waitForSelection:
        HuPrcVSleep();
    } while (step > 0);
    spriteState.state = 6;
    func_8010E52C_msetup(models, D_80119C48_msetup, 2, 7, &model, 1, 1.1f, 0.0f);
    cursors[0].state = -1;
    cursors[1].state = -1;
    spriteState.state = 7;
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);
    omDelPrcObj(spriteProcess);
    omDelPrcObj(cursorProcesses[0]);
    omDelPrcObj(cursorProcesses[1]);
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    Hu3DModelKill(model);
    return 0;
}

s32 func_801138F8_msetup(MsetupMenuState *state, s32 dataId, s32 *messages, s32 selectionArg) {
    Array2D models;
    s16 previousButtons;
    s16 anim;
    s16 model;
    s16 selection;
    s16 previousSelection;
    s16 buttons;
    s16 direction;
    omObjData *arrows;
    s32 i;
    f32 rotation;
    f32 rotationStep;

    selection = selectionArg;
    state->result = selection;
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 0.0f);
    model = models[0].model;
    anim = HmfAnimRead(HmfModelData[model].hmf, dataId, (char *)D_8011A6D8_msetup);
    func_8001C448_main(model);
    func_80032FC0_main(anim, 1, 1);
    func_8010E4D8_msetup(models, 2);
    func_80032FF8_main(anim, selection);
    arrows = func_8010DE38_msetup(96, 224, 72);
    if (messages != NULL) {
        func_8010B82C_msetup(messages[0]);
        func_8010B858_msetup();
    }
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.52f, 1);
    arrows->work[0] = 1;
    arrows->work[1] = 36;
    func_8001C258_main(models[1].model, 4, 4);
    for (rotation = 0.0f; rotation < 180.0f; rotation += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0.0f, rotation, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 180.0f, 0.0f);
    previousSelection = -1;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    while (1) {
        if (messages != NULL) {
            if (previousSelection != selection) {
                previousSelection = selection;
                func_8010B82C_msetup(messages[selection + 1]);
            }
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            selection = -1;
            break;
        }
        direction = 0;
        if (buttons & (U_JPAD | R_JPAD)) {
            direction = 1;
        } else if (buttons & (D_JPAD | L_JPAD)) {
            direction = -1;
        }
        if (direction != 0) {
            HuAudFXPlay(1);
            selection ^= 1;
            if (direction > 0) {
                arrows->work[0] = 4;
                rotationStep = 45.0f;
            } else {
                arrows->work[0] = 3;
                rotationStep = -45.0f;
            }
            for (i = 4, rotation = 180.0f; i != 0; i--) {
                rotation += rotationStep;
                Hu3DModelRotSet(model, 0.0f, rotation, 0.0f);
                HuPrcVSleep();
            }
            func_80032FF8_main(anim, selection);
            for (i = 4, rotation = 0.0f; i != 0; i--) {
                rotation += rotationStep;
                Hu3DModelRotSet(model, 0.0f, rotation, 0.0f);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
    state->result = selection;
    arrows->work[0] = 2;
    arrows->work[1] = 17;
    for (rotation = 180.0f; rotation < 360.0f; rotation += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0.0f, rotation, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C258_main(models[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.52f, 0.1f, 1);
    func_8010DDD8_msetup(arrows);
    if (anim >= 0) {
        func_80033430_main(anim);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    return 0;
}

s16 func_80113DEC_msetup(MsetupMenuState *state) {
    return func_801138F8_msetup(state, 0x140021, D_80119E58_msetup, 1);
}

s16 func_80113E20_msetup(MsetupMenuState *state) {
    return func_801138F8_msetup(state, 0x140022, D_80119E64_msetup, 0);
}

s16 func_80113E54_msetup(MsetupMenuState *state) {
    return func_801138F8_msetup(state, 0x140021, D_80119E70_msetup, 1);
}

s16 func_80113E88_msetup(MsetupMenuState *state) {
    s32 *messages = D_80119E88_msetup;

    if (D_8011A938_msetup == 1) {
        messages = D_80119E7C_msetup;
    }
    return func_801138F8_msetup(state, 0x140050, messages, 0);
}

s16 func_80113ED4_msetup(MsetupMenuState *arg0) {
#define MODE_PARTY 0
#define MODE_DUEL 1
#define FLAG_WALUIGIS_ISLAND 0x31
#define FLAG_BACKTRACK 0x30
    Array2D sp20;
    s16 unk_68;
    s32 *mainFSArray;
    s32 boardCountMaxCopy;
    f32 var_f20;
    void *temp_v0_4;
    omObjData *temp_s5;
    s16 prevBoardIndex;
    s16 backgroundEspriteSlot;
    s16 var_s6;
    s16 pad;
    s32 var_fp;
    s32 boardCountMax;
    s32 *boardDescriptionId;
    s16 curBoardIndex;
    s16 temp;
    s32 i;
    f32 tempFloat;

    boardDescriptionId = NULL;
    mainFSArray = NULL;
    curBoardIndex = D_8011AA30_msetup.boardIndex;
    arg0->result = 0;
    backgroundEspriteSlot = -1;
    var_s6 = -1;
    boardCountMax = 6;
    var_fp = 70;
    tempFloat = 1.0f;

    switch (D_8011A938_msetup) { // current mode
        case MODE_PARTY:
            boardDescriptionId = D_80119EC4_msetup;
            mainFSArray = D_80119E94_msetup; // party mode board backgrounds
            tempFloat = 1.0f;
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_WALUIGIS_ISLAND) != 0) {
                boardCountMax = 6;
            }
            break;
        case MODE_DUEL:
            boardDescriptionId = D_80119EE0_msetup;
            mainFSArray = D_80119EAC_msetup; // duel mode board backgrounds
            var_fp = 74;
            boardCountMax = 5;
            if (_CheckFlag(FLAG_BACKTRACK) != 0) {
                boardCountMax = 6;
            }
            break;
    }

    func_8010B998_msetup();
    func_8010E4BC_msetup(&sp20, 2, 0);
    func_8010E4D8_msetup(sp20, 2);
    temp = sp20[0].model;
    temp_s5 = func_8010DE38_msetup(0x40, 0x100, 0x48);
    func_8010B82C_msetup(boardDescriptionId[6]);
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&sp20, 2, 0xF, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(sp20[1].model, 4, 4);

    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 180.0f, 0);
    temp_s5->work[0] = 1;
    temp_s5->work[1] = 36;

    for (var_f20 = 1.0f; var_f20 < 2.5f; var_f20 += (3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 2.5f, 2.5f, 2.5f);
    prevBoardIndex = -1;
    pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
    boardCountMaxCopy = boardCountMax;
    while (1) {
        pad = func_8010D684_msetup(D_8011A948_msetup, &unk_68);
        if (pad & A_BUTTON) {
            HuAudFXPlay(2);
            break;
        }
        if (pad & B_BUTTON) {
            HuAudFXPlay(4);
            curBoardIndex = -1;
            break;
        }
        if (pad & (U_JPAD | R_JPAD)) {
            curBoardIndex++;
            curBoardIndex = (boardCountMaxCopy <= curBoardIndex) ? 0 : curBoardIndex;
            HuAudFXPlay(1);
            temp_s5->work[0] = 4;
        } else {
            if (pad & (D_JPAD | L_JPAD)) {
                if (--curBoardIndex < 0) {
                    curBoardIndex = boardCountMax - 1;
                }
                HuAudFXPlay(1);
                temp_s5->work[0] = 3;
            }
        }
        // check if background image should update
        if (prevBoardIndex != curBoardIndex) {
            if (backgroundEspriteSlot >= 0) {
                for (i = 255; i > 0; i -= (255 / 5)) {
                    espTPLvlSet(backgroundEspriteSlot, i);
                    HuPrcVSleep();
                }
                espKill(backgroundEspriteSlot);
                HuSprKill(var_s6);
            }
            temp_v0_4 = DataReadTemp(mainFSArray[curBoardIndex]);
            var_s6 = HuSprAnimRead(temp_v0_4);
            DataCloseTemp(temp_v0_4);
            backgroundEspriteSlot = espEntry(var_s6, 0, 1);
            espAttrSet(backgroundEspriteSlot, 0x1000);
            espPriSet(backgroundEspriteSlot, 1);
            espPosSet(backgroundEspriteSlot, 0xA0, var_fp);
            espScaleSet(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                espTPLvlSet(backgroundEspriteSlot, i);
                HuPrcVSleep();
            }
            espTPLvlSet(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_msetup(boardDescriptionId[curBoardIndex]);
        }
        HuPrcVSleep();
    }

    arg0->result = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA30_msetup.boardIndex = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;

    for (i = 255; i > 0; i -= (255 / 5)) {
        espTPLvlSet(backgroundEspriteSlot, i);
        HuPrcVSleep();
    }

    espTPLvlSet(backgroundEspriteSlot, 0);

    for (var_f20 = 2.5f; var_f20 > 1.0f; var_f20 += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(temp, var_f20, var_f20, var_f20);
        HuPrcVSleep();
    }

    Hu3DModelScaleSet(temp, 1.0f, 1.0f, 1.0f);

    for (var_f20 = 180.0f; var_f20 < 360.0f; var_f20 += (180.0f / 7.0f)) {
        Hu3DModelRotSet(temp, 0, var_f20, 0);
        HuPrcVSleep();
    }

    Hu3DModelRotSet(temp, 0, 0.0f, 0);
    func_8001C258_main(sp20[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&sp20, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);

    if (curBoardIndex >= 0) {
        func_8010F320_msetup(D_80119420_msetup, 0, sp20[0].model, -1);
        func_8010F320_msetup(D_80119420_msetup, 2, backgroundEspriteSlot, var_s6);
        Hu3DModelKill(sp20[1].model);
    } else {
        for (i = 0; i < 2; i++) {
            Hu3DModelKill(sp20[i].model);
        }
        espKill(backgroundEspriteSlot);
        HuSprKill(var_s6);
    }
    func_8010DDD8_msetup(temp_s5);
    return 0;
}

s16 func_801145D0_msetup(MsetupMenuState *state) {
    Array2D models;
    s32 *messages = NULL;
    s32 *backgrounds = NULL;
    s16 board = D_8011AA30_msetup.boardIndex;
    s32 y;
    f32 scale;
    s16 model;
    void *data;
    s16 sprite;
    s16 slot;
    s32 i;
    f32 value;

    state->result = 0;
    scale = 1.0f;
    y = 70;
    switch (D_8011A938_msetup) {
        case 2:
            messages = D_80119EFC_msetup;
            backgrounds = D_80119E94_msetup;
            scale = 1.0f;
            y = 74;
            break;
        case 3:
            messages = D_80119F14_msetup;
            backgrounds = D_80119EAC_msetup;
            scale = 1.0f;
            y = 74;
            break;
    }
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 0);
    func_8010E4D8_msetup(models, 2);
    model = models[0].model;
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    func_8001C258_main(models[1].model, 4, 4);
    for (value = 0.0f; value < 180.0f; value += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, value, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 180.0f, 0);
    for (value = 1.0f; value < 2.5f; value += 3.0f / 14.0f) {
        Hu3DModelScaleSet(model, value, value, value);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(model, 2.5f, 2.5f, 2.5f);
    data = DataReadTemp(backgrounds[board]);
    sprite = HuSprAnimRead(data);
    DataCloseTemp(data);
    slot = espEntry(sprite, 0, 1);
    espAttrSet(slot, 0x1000);
    espPriSet(slot, 1);
    espPosSet(slot, 160, y);
    espScaleSet(slot, scale, scale);
    for (i = 0; i < 255; i += 255 / 7) {
        espTPLvlSet(slot, i);
        HuPrcVSleep();
    }
    espTPLvlSet(slot, 255);
    func_8010B82C_msetup(messages[board]);
    func_8010B858_msetup();
    for (i = 255; i > 0; i -= 255 / 7) {
        espTPLvlSet(slot, i);
        HuPrcVSleep();
    }
    for (value = 2.5f; value > 1.0f; value += -(3.0f / 14.0f)) {
        Hu3DModelScaleSet(model, value, value, value);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
    for (value = 180.0f; value < 360.0f; value += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, value, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 0, 0);
    func_8001C258_main(models[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 1);
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    espKill(slot);
    HuSprKill(sprite);
    return 0;
}

s16 func_80114AA0_msetup(MsetupMenuState *state) {
    Array2D models;
    s16 previousButtons;
    s16 selection;
    s16 player;
    s16 oldSelection;
    s16 oldPlayer;
    s16 model;
    s16 anim;
    omObjData *cursor;
    u16 buttons;
    s16 reverse;
    s32 i;
    s32 direction;
    f32 angle;
    f32 step;

    state->result = 0;
    selection = D_8011AA30_msetup.stars[0];
    player = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 0);
    model = models[0].model;
    anim = HmfAnimRead(HmfModelData[model].hmf, 0x140023, (char *)D_8011A6D8_msetup);
    func_8001C448_main(model);
    func_80032FC0_main(anim, 1, 1);
    func_8010E4D8_msetup(models, 2);
    func_80032FF8_main(anim, selection);
    cursor = func_8010DE38_msetup(96, 224, 72);
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.4f, 1);
    cursor->work[0] = 1;
    cursor->work[1] = 36;
    func_8001C258_main(models[1].model, 4, 4);
    for (angle = 0.0f; angle < 180.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, angle, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 180.0f, 0);
    oldSelection = selection;
    oldPlayer = -1;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    while (1) {
        if (oldPlayer != player) {
            func_8010B968_msetup(D_8011AA30_msetup.characters[player] + 0x1C00, 0);
            func_8010B82C_msetup(0x151C);
            oldPlayer = player;
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            D_8011AA30_msetup.stars[player] = selection;
            if (selection != 0) {
                D_8011A9E0_msetup[player].state = 8;
            } else {
                D_8011A9E0_msetup[player].state = 10;
            }
            player++;
            if (player >= 4) {
                state->result = 0;
                break;
            }
            selection = D_8011AA30_msetup.stars[player];
        } else if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            player--;
            if (player < 0) {
                state->result = -1;
                break;
            }
            D_8011A9E0_msetup[player].state = 9;
            selection = D_8011AA30_msetup.stars[player];
        }
        reverse = 0;
        if (buttons & (U_JPAD | R_JPAD)) {
            selection++;
            selection = selection >= 10 ? 0 : selection;
            cursor->work[0] = 4;
        } else if (buttons & (D_JPAD | L_JPAD)) {
            selection--;
            if (selection < 0) {
                selection = 9;
            }
            cursor->work[0] = 3;
            reverse = 1;
        }
        if (oldSelection != selection) {
            HuAudFXPlay(1);
            direction = reverse;
            step = 45.0f;
            if (direction) {
                step = -45.0f;
            }
            i = 4;
            for (angle = 180.0f; i != 0; i--) {
                angle += step;
                Hu3DModelRotSet(model, 0, angle, 0);
                HuPrcVSleep();
            }
            func_80032FF8_main(anim, selection);
            i = 4;
            for (angle = 0.0f; i != 0; i--) {
                angle += step;
                Hu3DModelRotSet(model, 0, angle, 0);
                HuPrcVSleep();
            }
            oldSelection = selection;
        }
        HuPrcVSleep();
    }
    cursor->work[0] = 2;
    cursor->work[1] = 17;
    for (angle = 180.0f; angle < 360.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, angle, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 0, 0);
    func_8001C258_main(models[1].model, 4, 0);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.4f, 0.1f, 1);
    func_8010DDD8_msetup(cursor);
    if (anim >= 0) {
        func_80033430_main(anim);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    return 0;
}

s32 func_801150A0_msetup(s16 controller) {
    u8 stickX = D_800CBB6E_main[controller];
    u8 stickY = D_800D20A1_main[controller];
    s32 quadrant = 0;
    f32 angle;

    if ((u8)(stickX + 30) <= 60 && (u8)(stickY + 30) <= 60) {
        return -1;
    }
    angle = atan2df((s8)stickX, (s8)stickY);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if ((angle >= 0.0f) & (angle < 90.0f)) {
        quadrant = 0;
    } else if ((angle >= 90.0f) & (angle < 180.0f)) {
        quadrant = 1;
    } else if ((angle >= 180.0f) & (angle < 270.0f)) {
        quadrant = 2;
    } else if ((angle >= 270.0f) & (angle < 360.0f)) {
        quadrant = 3;
    }
    return quadrant;
}

s16 func_801152C4_msetup(s16 model, s16 anim, HuMtx4F matrix, s16 *previousButtons, s16 selection) {
    HmfMotionNode *nodes[4];
    s8 unused[4];
    HuMtx4F matrices[4];
    HuMtx4F *nodeMatrix;
    f32 phase;
    f32 angle;
    f32 targetAngle;
    f32 delta;
    f32 scale;
    s16 oldSelection;
    u16 buttons;
    s32 direction;
    s16 i;

    nodes[0] = func_8001D33C_main(model, (char *)D_8011A7D8_msetup);
    func_8002367C_main(matrices[0], nodes[0]->unk58);
    nodes[1] = func_8001D33C_main(model, (char *)D_8011A7E0_msetup);
    func_8002367C_main(matrices[1], nodes[1]->unk58);
    nodes[2] = func_8001D33C_main(model, (char *)D_8011A7E8_msetup);
    func_8002367C_main(matrices[2], nodes[2]->unk58);
    nodes[3] = func_8001D33C_main(model, (char *)D_8011A7F0_msetup);
    func_8002367C_main(matrices[3], nodes[3]->unk58);
    phase = 0.0f;
    for (i = 0; i < 4; i++) {
        unused[i] = 0;
    }
    // Preserve the original scratch initialization and stack layout.
    (void)unused;
    angle = D_8011A908_msetup;
    targetAngle = D_80119F4C_msetup[selection];
    oldSelection = -1;
    while (1) {
        buttons = func_8010D684_msetup(D_8011A948_msetup, previousButtons);
        if (buttons & 0x4000) {
            HuAudFXPlay(4);
            selection = -1;
            break;
        }
        if (buttons & 0x8000) {
            if (selection < 3) {
                HuAudFXPlay(0x139);
            } else {
                HuAudFXPlay(2);
            }
            break;
        }
        direction = buttons >> 8;
        direction &= 0xF;
        if (direction) {
            if (D_800CDA7C_main[D_8011A948_msetup] & 0x300) {
                if (D_800CDA7C_main[D_8011A948_msetup] & 0x100) {
                    selection++;
                    if (selection >= 4) {
                        selection = 0;
                    }
                    HuAudFXPlay(1);
                } else if (D_800CDA7C_main[D_8011A948_msetup] & 0x200) {
                    selection--;
                    if (selection < 0) {
                        selection = 3;
                    }
                    HuAudFXPlay(1);
                }
            } else {
                direction = (s16)func_801150A0_msetup(D_8011A948_msetup);
                if (direction >= 0 && selection != direction) {
                    HuAudFXPlay(1);
                    selection = direction;
                }
            }
        }
        if (oldSelection != selection) {
            func_8010B82C_msetup(D_80119F3C_msetup[selection]);
            targetAngle = D_80119F4C_msetup[selection];
            D_8011A908_msetup = targetAngle;
            if (oldSelection >= 0) {
                nodeMatrix = &nodes[oldSelection]->unk58;
                func_8002367C_main(*nodeMatrix, matrices[oldSelection]);
                func_80017CD0_main(*nodeMatrix, 1, 1, 1);
            }
            oldSelection = selection;
        }
        if (targetAngle != angle) {
            delta = targetAngle - angle;
            scale = __builtin_fabsf(delta);
            if (180.0f < scale) {
                delta = -delta;
            }
            if (delta < 0.0f) {
                delta = -24.0f;
            } else {
                delta = 24.0f;
            }
            angle += delta;
            if (360.0f < angle) {
                angle -= 360.0f;
            } else if (angle < 0.0f) {
                angle += 360.0f;
            }
            nodeMatrix = &func_8001D33C_main(model, (char *)D_8011A7F8_msetup)->unk58;
            func_8002367C_main(*nodeMatrix, matrix);
            func_80017D24_main(*nodeMatrix, 0.0f, 0.0f, angle);
        }
        phase += 12.0f;
        if (180.0f <= phase) {
            phase -= 180.0f;
        }
        scale = sindf(phase) * 0.5f + 1.0f;
        nodeMatrix = &nodes[selection]->unk58;
        func_8002367C_main(*nodeMatrix, matrices[selection]);
        func_80017CD0_main(*nodeMatrix, scale, scale, scale);
        HuPrcVSleep();
    }
    nodeMatrix = &nodes[oldSelection]->unk58;
    func_8002367C_main(*nodeMatrix, matrices[oldSelection]);
    func_80017CD0_main(*nodeMatrix, 1, 1, 1);
    return selection;
}

s16 func_801157B8_msetup(s16 model, s16 anim, s16 *controller, s16 selection, MsetupLinkedModel *linked, omObjData *obj) {
    f32 angle;
    s16 oldSelection;
    s16 linkedModel;
    s16 buttons;

    func_80032FF8_main(anim, selection);
    for (angle = 0.0f; angle <= 180.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0.0f, angle, 0.0f);
        HuPrcVSleep();
    }
    func_8010B82C_msetup(0x1529);
    oldSelection = -1;
    while (1) {
        buttons = func_8010D684_msetup(D_8011A948_msetup, controller);
        if (buttons & 0x4000) {
            HuAudFXPlay(4);
            selection = -1;
            break;
        }
        if (buttons & 0x8000) {
            HuAudFXPlay(0x139);
            break;
        }
        if (buttons & 0x900) {
            selection++;
            if (selection >= 9) {
                selection = 0;
            }
            HuAudFXPlay(1);
            obj->work[0] = 4;
        } else if (buttons & 0x600) {
            selection--;
            if (selection < 0) {
                selection = 8;
            }
            HuAudFXPlay(1);
            obj->work[0] = 3;
        }
        if (oldSelection != selection) {
            func_80032FF8_main(anim, selection);
            oldSelection = selection;
        }
        HuPrcVSleep();
    }
    if (selection >= 0) {
        linkedModel = linked->model;
        func_8001C258_main(linkedModel, 4, 0);
        Hu3DModelRotSet(linkedModel, 0.0f, 180.0f, 0.0f);
        for (angle = 180.0f; angle < 360.0f; angle += 180.0f / 7.0f) {
            Hu3DModelRotSet(model, 0.0f, angle, 0.0f);
            Hu3DModelRotSet(linkedModel, 0.0f, angle, 0.0f);
            HuPrcVSleep();
        }
    } else {
        for (angle = 180.0f; angle >= 0.0f; angle -= 180.0f / 7.0f) {
            Hu3DModelRotSet(model, 0.0f, angle, 0.0f);
            HuPrcVSleep();
        }
    }
    return selection;
}

s16 func_80115A9C_msetup(s16 model, s16 anim, HuMtx4F matrix, s16 *previousButtons, s16 selection) {
    HmfMotionNode *nodes[2];
    HuMtx4F matrices[2];
    HuMtx4F *nodeMatrix;
    f32 phase;
    f32 angle;
    f32 targetAngle;
    f32 delta;
    f32 scale;
    s16 oldSelection;
    s16 buttons;

    nodes[0] = func_8001D33C_main(model, (char *)D_8011A7D8_msetup);
    func_8002367C_main(matrices[0], nodes[0]->unk58);
    nodes[1] = func_8001D33C_main(model, (char *)D_8011A800_msetup);
    func_8002367C_main(matrices[1], nodes[1]->unk58);
    phase = 0.0f;
    angle = D_8011A908_msetup;
    targetAngle = D_80119F60_msetup[selection];
    oldSelection = -1;
    while (1) {
        buttons = func_8010D684_msetup(D_8011A948_msetup, previousButtons);
        if (buttons & 0x4000) {
            HuAudFXPlay(4);
            selection = -1;
            break;
        }
        if (buttons & 0x8000) {
            HuAudFXPlay(0x139);
            break;
        }
        if (buttons & 0x900) {
            if (selection != 0) {
                HuAudFXPlay(1);
            }
            selection = 0;
        } else if (buttons & 0x600) {
            if (selection == 0) {
                HuAudFXPlay(1);
            }
            selection = 1;
        }
        if (oldSelection != selection) {
            func_8010B82C_msetup(D_80119F8C_msetup[selection]);
            targetAngle = D_80119F60_msetup[selection];
            D_8011A908_msetup = targetAngle;
            if (oldSelection >= 0) {
                HmfMotionNode *node = nodes[oldSelection];
                nodeMatrix = &node->unk58;
                func_8002367C_main(*nodeMatrix, matrices[oldSelection]);
                func_80017CD0_main(*nodeMatrix, 1, 1, 1);
            }
            oldSelection = selection;
        }
        if (targetAngle != angle) {
            delta = targetAngle - angle;
            scale = __builtin_fabsf(delta);
            if (180.0f < scale) {
                delta = -delta;
            }
            if (delta < 0.0f) {
                angle += -24.0f;
            } else {
                angle += 24.0f;
            }
            if (360.0f < angle) {
                angle -= 360.0f;
            } else if (angle < 0.0f) {
                angle += 360.0f;
            }
            nodeMatrix = &func_8001D33C_main(model, (char *)D_8011A7F8_msetup)->unk58;
            func_8002367C_main(*nodeMatrix, matrix);
            func_80017D24_main(*nodeMatrix, 0.0f, 0.0f, angle);
        }
        phase += 12.0f;
        if (180.0f <= phase) {
            phase -= 180.0f;
        }
        scale = sindf(phase) * 0.5f + 1.0f;
        nodeMatrix = &nodes[selection]->unk58;
        func_8002367C_main(*nodeMatrix, matrices[selection]);
        func_80017CD0_main(*nodeMatrix, scale, scale, scale);
        HuPrcVSleep();
    }
    nodeMatrix = &nodes[oldSelection]->unk58;
    func_8002367C_main(*nodeMatrix, matrices[oldSelection]);
    func_80017CD0_main(*nodeMatrix, 1, 1, 1);
    return selection;
}

void func_80115E78_msetup(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].pos.x += x;
        HmfModelData[idx].pos.y += y;
        HmfModelData[idx].pos.z += z;
    }
}

/* These strings follow the menu process jump table in rodata. */
const char D_8011A7D8_msetup[] = "20turn";

const char D_8011A7E0_msetup[] = "35turn";

const char D_8011A7E8_msetup[] = "50turn";

const char D_8011A7F0_msetup[] = "q_turn";

const char D_8011A7F8_msetup[] = "hari";

const char D_8011A800_msetup[] = "mugen";

s16 func_80115EE0_msetup(MsetupMenuState *state) {
    Array2D models;
    Vec pos;
    Vec rot;
    HuMtx4F matrix;
    s16 previousButtons;
    s16 anim;
    s16 selection;
    s16 phase;
    s16 model;
    s16 linkedModel;
    s16 backModel;
    Vec *linkedRot;
    omObjData *cursor;
    s32 message;
    s32 i;
    f32 angle;
    f32 step;

    state->result = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 0);
    func_8010E4D8_msetup(models, 2);
    model = func_8000B108_main(0x140008, 0x2A9);
    linkedModel = model;
    anim = HmfAnimRead(HmfModelData[linkedModel].hmf, 0x140024, "uramen_CIDX");
    func_8001C448_main(linkedModel);
    rot.x = rot.y = rot.z = 0;
    Hu3DModelRotSet(linkedModel, 0, 0, 0);
    pos = D_80119B20_msetup;
    Hu3DModelPosSet(linkedModel, pos.x, pos.y, pos.z);
    Hu3DModelScaleSet(linkedModel, 0.1f, 0.1f, 0.1f);
    func_8002367C_main(matrix, func_8001D33C_main(linkedModel, (char *)D_8011A7F8_msetup)->unk58);
    message = 0;
    switch (D_8011A938_msetup) {
        case 0:
            func_80017CD0_main(func_8001D33C_main(linkedModel, (char *)D_8011A800_msetup)->unk58, 0, 0, 0);
            message = 0x1524;
            break;
        case 1:
            func_80017CD0_main(func_8001D33C_main(linkedModel, (char *)D_8011A7E0_msetup)->unk58, 0, 0, 0);
            func_80017CD0_main(func_8001D33C_main(linkedModel, (char *)D_8011A7E8_msetup)->unk58, 0, 0, 0);
            func_80017CD0_main(func_8001D33C_main(linkedModel, (char *)D_8011A7F0_msetup)->unk58, 0, 0, 0);
            message = 0x242E;
            break;
    }
    cursor = func_8010DE38_msetup(96, 224, 72);
    func_8010B82C_msetup(message);
    i = 0;
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.5f, 1);
    models[0].pos.z -= 1.5f;
    models[1].pos.z -= 1.5f;
    backModel = models[1].model;
    Hu3DModelPosSet(backModel, models[1].pos.x, models[1].pos.y, models[1].pos.z);
    func_8001C258_main(backModel, 4, 4);
    linkedModel = models[0].model;
    Hu3DModelPosSet(linkedModel, models[0].pos.x, models[0].pos.y, models[0].pos.z);
    pos.y += 565.0f;
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    rot.y = 180.0f;
    Hu3DModelScaleSet(model, 1.5f, 1.5f, 1.5f);
    linkedRot = &models[0].rot;
    step = 180.0f / 7.0f;
    for (; i < 7; i++) {
        rot.y = step + rot.y;
        if (360.0f < rot.y) {
            rot.y -= 360.0f;
        }
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        linkedRot->y = step + linkedRot->y;
        if (360.0f < linkedRot->y) {
            linkedRot->y -= 360.0f;
        }
        Hu3DModelRotSet(linkedModel, linkedRot->x, linkedRot->y, linkedRot->z);
        HuPrcVSleep();
    }
    rot.y = 0;
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
    func_8001C258_main(linkedModel, 4, 4);
    phase = 0;
    switch (D_8011A938_msetup) {
        case 0:
            phase = 0;
            break;
        case 1:
            phase = 2;
            break;
    }
    selection = 0;
    D_8011A908_msetup = 0;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    do {
        func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        switch (phase) {
            case 0:
                selection = func_801152C4_msetup(model, anim, matrix, &previousButtons, selection);
                if (selection < 0) {
                    state->result = -1;
                } else if (selection < 3) {
                    D_8011AA30_msetup.totalTurns = D_80119F6C_msetup[selection];
                    D_8011AA30_msetup.unk16 = selection;
                    selection = -1;
                } else {
                    selection = 0;
                    phase++;
                }
                break;
            case 1:
                cursor->work[0] = 1;
                cursor->work[1] = 36;
                selection = func_801157B8_msetup(model, anim, &previousButtons, selection, models, cursor);
                if (selection < 0) {
                    selection = 3;
                    phase--;
                } else {
                    D_8011AA30_msetup.totalTurns = D_80119F78_msetup[selection];
                    D_8011AA30_msetup.unk16 = 3;
                    selection = -1;
                }
                cursor->work[0] = 2;
                cursor->work[1] = 36;
                break;
            case 2:
                selection = func_80115A9C_msetup(model, anim, matrix, &previousButtons, selection);
                if (selection < 0) {
                    state->result = -1;
                } else if (selection < 2) {
                    D_8011AA42_msetup = selection == 0 ? 20 : 255;
                    selection = -1;
                } else {
                    state->result = -1;
                    selection = -1;
                }
                break;
        }
        HuPrcVSleep();
    } while (selection >= 0);
    func_8010B998_msetup();
    linkedModel = models[1].model;
    func_8001C258_main(linkedModel, 4, 0);
    Hu3DModelRotSet(linkedModel, 0, 180.0f, 0);
    for (angle = 0; angle < 180.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, angle, 0);
        Hu3DModelRotSet(models[0].model, 0, angle, 0);
        Hu3DModelRotSet(linkedModel, 0, angle + 180.0f, 0);
        HuPrcVSleep();
    }
    func_8001C258_main(models[0].model, 4, 0);
    func_8001C258_main(model, 4, 4);
    models[0].rot.y = 0;
    models[1].rot.y = 180.0f;
    models[0].pos.z += 1.5f;
    models[1].pos.z += 1.5f;
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.5f, 0.1f, 2);
    func_8010DDD8_msetup(cursor);
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    if (state->result >= 0) {
        switch (D_8011A938_msetup) {
            case 0:
                for (i = 0; i < 9; i++) {
                    if (D_8011AA30_msetup.totalTurns == D_80119F78_msetup[i]) {
                        break;
                    }
                }
                i = i < 9 ? i : 0;
                break;
            case 1:
                i = D_8011AA30_msetup.totalTurns == 255 ? 9 : 2;
                break;
        }
        func_80032FF8_main(anim, i);
        func_8010F320_msetup(D_80119420_msetup, 1, model, anim);
    } else {
        if (anim >= 0) {
            func_80033430_main(anim);
        }
        Hu3DModelKill(model);
    }
    return 0;
}

s16 func_801167B8_msetup(MsetupMenuState *state) {
    Array2D models;
    s16 previousButtons;
    s32 i;
    s16 selection;
    s16 oldSelection;
    s16 model;
    s16 connected;
    omObjData *cursor;
    s16 refresh;
    u16 buttons;
    f32 angle;
    f32 scale;
    f32 oldScale;
    s32 count;

    connected = D_8011AA30_msetup.connectedCount;
    cursor = NULL;
    if (state->result < 0) {
        i = D_8011AA30_msetup.humanCount;
        for (selection = 0; selection < 2; selection++) {
            if (i == D_8011A0B8_msetup[selection]) {
                break;
            }
        }
        selection = selection >= 2 ? 0 : selection;
        state->result = selection;
    } else {
        if (state->result >= 2) {
            state->result = 0;
        }
        selection = state->result;
    }
    count = connected;
    if (count < D_8011A0B8_msetup[selection]) {
        for (selection = 0; selection < 2; selection++) {
            if (count == D_8011A0B8_msetup[selection]) {
                break;
            }
        }
        selection = selection >= 2 ? 0 : selection;
        state->result = selection;
    }
    func_8010B998_msetup();
    angle = connected >= 2 ? 90.0f : 0.0f;
    func_8010E32C_msetup(&models, 2, angle, 0);
    for (i = 0; i < 2; i++) {
        model = models[i].model;
        models[i].unk1A = HmfAnimRead(HmfModelData[model].hmf, D_80119FDC_msetup[i], (char *)D_8011A6D8_msetup);
        func_8001C448_main(model);
        func_800332D4_main(models[i].unk1A, 0.75f);
    }
    func_8010E4D8_msetup(models, 2);
    if (connected >= 2) {
        cursor = func_8010DE38_msetup(64, 256, 72);
    }
    func_8010B82C_msetup(0x2403);
    func_8010B858_msetup();
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    if (connected >= 2) {
        cursor->work[0] = 1;
        cursor->work[1] = 36;
        func_8010E52C_msetup(models, D_80119F94_msetup, 2, 7, NULL, 0, 0.0f, 1.0f);
        i = 4;
        for (scale = 1.0f; i != 0; i--) {
            scale += 0.1f;
            Hu3DModelScaleSet(models[selection].model, scale, scale, scale);
            HuPrcVSleep();
        }
    } else {
        func_8001C258_main(models[1].model, 4, 4);
        angle = models[0].rot.y;
        oldScale = 180.0f / 7.0f;
        model = models[0].model;
        for (i = 0; i < 7; i++) {
            angle += oldScale;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            Hu3DModelRotSet(model, 0, angle, 0);
            HuPrcVSleep();
        }
        models[0].rot.y = angle;
    }
    oldSelection = selection;
    refresh = 1;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    while (1) {
        if (refresh) {
            func_8010B82C_msetup(D_80119FD4_msetup[selection]);
            refresh = 0;
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            state->result = selection;
            break;
        }
        if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            func_8010B82C_msetup(0x2401);
            if (func_8010B858_msetup() == 0) {
                state->result = -1;
                break;
            }
            refresh = 1;
            func_8010B82C_msetup(0x2403);
            func_8010B858_msetup();
            buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        }
        if (connected >= 2) {
            if (buttons & 0x900) {
                selection++;
                selection = selection >= 2 ? 0 : selection;
                cursor->work[0] = 4;
            } else if (buttons & 0x600) {
                selection--;
                if (selection < 0) {
                    selection = 1;
                }
                cursor->work[0] = 3;
            }
        }
        if (oldSelection != selection) {
            HuAudFXPlay(1);
            scale = 1.0f;
            oldScale = 1.4f;
            for (i = 4; i != 0; i--) {
                scale += 0.1f;
                oldScale += -0.1f;
                Hu3DModelScaleSet(models[selection].model, scale, scale, scale);
                Hu3DModelScaleSet(models[oldSelection].model, oldScale, oldScale, oldScale);
                HuPrcVSleep();
            }
            oldSelection = selection;
            refresh = 1;
        }
        HuPrcVSleep();
    }
    if (state->result >= 0) {
        i = D_8011A0B8_msetup[state->result];
        D_8011AA30_msetup.humanCount = i;
        D_8011AA30_msetup.cpuCount = 2 - i;
        for (i = 0; i < D_8011AA30_msetup.humanCount; i++) {
            RepeatVibrator(D_8011AA30_msetup.controllerPorts[i], 10, 0, 10);
        }
    }
    if (connected >= 2) {
        cursor->work[0] = 2;
        cursor->work[1] = 17;
        func_8010E52C_msetup(models, D_80119FB4_msetup, 2, 7, NULL, 0, 0.0f, 1.0f);
    } else {
        angle = models[0].rot.y;
        oldScale = 180.0f / 7.0f;
        model = models[0].model;
        for (i = 0; i < 7; i++) {
            angle += oldScale;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            Hu3DModelRotSet(model, 0, angle, 0);
            HuPrcVSleep();
        }
        models[0].rot.y = angle;
        func_8001C258_main(models[1].model, 4, 0);
    }
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 2);
    if (connected >= 2) {
        func_8010DDD8_msetup(cursor);
    }
    for (i = 0; i < 2; i++) {
        func_80033430_main(models[i].unk1A);
        Hu3DModelKill(models[i].model);
    }
    return 0;
}

s16 func_80116FE0_msetup(MsetupMenuState *state) {
    static const char nodeName[0x1C] = "sitagocoro_DEF";
    Array2D models;
    s16 previousButtons;
    s32 i;
    s16 selection;
    s16 player;
    omObjData *cursor;
    s16 oldSelection;
    s16 model;
    s16 motion;
    s16 oldPlayer;
    u16 buttons;
    f32 angle;
    f32 step;
    s16 reverse;
    s16 *starCounts;

    state->result = 0;
    selection = 0;
    starCounts = D_80119FE4_msetup;
    for (; selection < 5; selection++) {
        if (D_8011AA30_msetup.stars[0] == starCounts[selection]) {
            break;
        }
    }
    selection = selection >= 5 ? 0 : selection;
    player = 0;
    func_8010B998_msetup();
    func_8010E4BC_msetup(&models, 2, 0);
    func_8010E4D8_msetup(models, 2);
    model = func_8000B108_main(0x14000A, 0x2A9);
    motion = HmfAnimRead(HmfModelData[model].hmf, 0x140034, (char *)nodeName);
    func_8001C448_main(model);
    func_8001C514_main(model);
    func_80032FC0_main(motion, 1, 1);
    func_80032FF8_main(motion, selection);
    func_8001C258_main(model, 4, 4);
    cursor = func_8010DE38_msetup(96, 224, 72);
    HuAudFXPlay(0x2D9);
    func_8010E8C8_msetup(&models, 2, 15, 720.0f, 565.0f, 0.1f, 1.0f, 1);
    cursor->work[0] = 1;
    cursor->work[1] = 36;
    func_8001C258_main(models[1].model, 4, 4);
    Hu3DModelPosSet(model, D_80119B20_msetup.x, D_80119B20_msetup.y + 565.0f, D_80119B20_msetup.z + 0.5f);
    Hu3DModelRotSet(model, 0, 180.0f, 0);
    func_8001C258_main(model, 4, 0);
    for (angle = 0; angle < 180.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(models[0].model, 0, angle, 0);
        Hu3DModelRotSet(model, 0, angle + 180.0f, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, 0, 0, 0);
    Hu3DModelRotSet(models[0].model, 0, 180.0f, 0);
    oldSelection = selection;
    oldPlayer = -1;
    func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
    while (1) {
        if (oldPlayer != player) {
            func_8010B968_msetup(D_8011AA30_msetup.characters[player] + 0x1C00, 0);
            func_8010B82C_msetup(0x2413);
            oldPlayer = player;
        }
        buttons = func_8010D684_msetup(D_8011A948_msetup, &previousButtons);
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            D_8011AA30_msetup.stars[player] = D_80119FE4_msetup[selection];
            D_8011A9E0_msetup[player].state = 13;
            player++;
            if (player >= 2) {
                state->result = 0;
                break;
            }
            i = D_8011AA30_msetup.stars[player];
            for (selection = 0; selection < 5; selection++) {
                if (i == D_80119FE4_msetup[selection]) {
                    break;
                }
            }
            selection = selection >= 5 ? 0 : selection;
        } else if (buttons & B_BUTTON) {
            HuAudFXPlay(4);
            player--;
            if (player < 0) {
                state->result = -1;
                break;
            }
            D_8011A9E0_msetup[player].state = 14;
            i = D_8011AA30_msetup.stars[player];
            for (selection = 0; selection < 5; selection++) {
                if (i == D_80119FE4_msetup[selection]) {
                    break;
                }
            }
            selection = selection >= 5 ? 0 : selection;
        }
        reverse = 0;
        if (buttons & 0x900) {
            selection++;
            selection = selection >= 5 ? 0 : selection;
            cursor->work[0] = 4;
        } else if (buttons & 0x600) {
            selection--;
            if (selection < 0) {
                selection = 4;
            }
            cursor->work[0] = 3;
            reverse = 1;
        }
        if (oldSelection != selection) {
            HuAudFXPlay(1);
            step = reverse ? -45.0f : 45.0f;
            for (i = 4, angle = 0; i != 0; i--) {
                angle += step;
                if (angle < 0) {
                    angle += 360.0f;
                }
                Hu3DModelRotSet(model, 0, angle, 0);
                Hu3DModelRotSet(models[0].model, 0, angle + 180.0f, 0);
                HuPrcVSleep();
            }
            func_80032FF8_main(motion, selection);
            for (i = 4, angle = 180.0f; i != 0; i--) {
                angle += step;
                if (angle >= 360.0f) {
                    angle -= 360.0f;
                }
                Hu3DModelRotSet(model, 0, angle, 0);
                Hu3DModelRotSet(models[0].model, 0, angle + 180.0f, 0);
                HuPrcVSleep();
            }
            oldSelection = selection;
        }
        HuPrcVSleep();
    }
    cursor->work[0] = 2;
    cursor->work[1] = 17;
    for (angle = 0; angle < 180.0f; angle += 180.0f / 7.0f) {
        Hu3DModelRotSet(model, 0, angle, 0);
        Hu3DModelRotSet(models[0].model, 0, angle + 180.0f, 0);
        HuPrcVSleep();
    }
    func_8001C258_main(models[1].model, 4, 0);
    Hu3DModelRotSet(models[1].model, 0, 0, 0);
    func_8001C258_main(model, 4, 4);
    HuAudFXPlay(0x2DA);
    func_8010E8C8_msetup(&models, 2, 7, 360.0f, 400.0f, 1.0f, 0.1f, 2);
    func_8010DDD8_msetup(cursor);
    if (motion >= 0) {
        func_80033430_main(motion);
    }
    if (model >= 0) {
        Hu3DModelKill(model);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelKill(models[i].model);
    }
    return 0;
}

s16 func_80117818_msetup(MsetupMenuState *state) {
    return 0;
}

void func_80117820_msetup(void) {
    MsetupMenuState *state;
    s16 currentState;

    state = HuPrcCurrentGet()->user_data;
    for (currentState = 0; currentState < 4; currentState++) {
        D_8011A8E0_msetup[currentState][0] = -1;
        D_8011A8E0_msetup[currentState][1] = -1;
        D_8011A8E0_msetup[currentState][2] = -1;
        D_8011A8E0_msetup[currentState][3] = -1;
    }
    func_8010E21C_msetup();
    currentState = 0;
    while (1) {
        if (currentState != state->state) {
            currentState = (u16)state->state < 14 ? state->state : 0;
        }
        state->state = D_80119FF0_msetup[currentState](state);
        HuPrcVSleep();
    }
}
