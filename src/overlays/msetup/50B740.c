#include "common.h"
#include "game/window.h"
#include "overlays/msetup_internal.h"

typedef struct UnkStarLift {
    char unk_00[0x04];
    s16 unk4;
} UnkStarLift;

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

extern s32 D_80119B44_msetup[];
extern s16 D_80119B60_msetup[][2];
extern s16 D_80119B90_msetup[][4];
extern s32 D_80119BA0_msetup[];
extern s32 D_80119BD0_msetup[];
extern s32 D_80119BF0_msetup[];
extern u8 D_80119C10_msetup[][3];

extern char *D_80119E20_msetup[];
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
extern u8 D_8011AA45_msetup; // board index chosen
extern UnkMsetupEntry D_8011A9F2_msetup[];
extern Vec D_8011A028_msetup[];
extern s16 D_8011A058_msetup[4][4];
extern s16 D_8011A078_msetup[4][4];
extern s16 D_8011A8E0_msetup[4][4];
extern s32 (*D_80119FF0_msetup[])(MsetupMenuState *);

extern char D_8011A6D8_msetup[];
extern char D_8011A7D8_msetup[];
extern char D_8011A7E0_msetup[];
extern char D_8011A7E8_msetup[];
extern char D_8011A7F0_msetup[];
extern char D_8011A7F8_msetup[];
extern f32 D_8011A908_msetup;
extern f32 D_80119F4C_msetup[];
extern s32 D_80119F3C_msetup[];

#ifdef NON_MATCHING
extern char D_8011A800_msetup[];
extern f32 D_80119F60_msetup[];
extern s32 D_80119F8C_msetup[];
extern s16 D_80119DFC_msetup[][2];
extern s16 (*D_80119E0C_msetup[])[2];
extern s32 D_80119B2C_msetup[];
extern MsetupModelTarget D_80119DC8_msetup[];
extern MsetupModelTarget D_80119C48_msetup[];
#endif

void func_8010F43C_msetup(s16 model, char *node, Vec2f *screenPos);
void func_80017D24_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, s32);
void func_8000BCC8_main(u16, s32);
void func_8000BE5C_main(u16, f32, f32);
void func_8000C184_main(u16);
void func_8001ACDC_main(s16);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void func_8001C258_main(s16, s32, s32);
void HuSprKill(s16);
s32 _CheckFlag(s32);            /* extern */
s16 func_80055810_main(void *); /* extern */
s32 func_801138F8_msetup(MsetupMenuState *, s32, s32 *, s32);
s32 func_80113ED4_msetup(UnkStarLift *arg0);

s16 HmfAnimRead(HmfData *, s32, char *);
HmfMotionNode *func_8001D33C_main(s16, char *);
void func_8002367C_main(HuMtx4F, HuMtx4F);

#ifdef NON_MATCHING
void func_80112804_msetup(void);
#endif

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_8010F87C_msetup);

void func_8011035C_msetup(void) {
    s16 previousSelection;
    MsetupPlayerSprites sprites;
    s16 group;
    s16 unusedGroup = -1;
    s16 sprite;
    MsetupMenuState *state;
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
        func_80055458_main(group, member, 256);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprAttrSet(group, member, 0x9000);
        HuSprScaleSet(group, member, 1.0f, 1.0f);
        func_800550F4_main(group, member, 1);
        func_80055024_main(group, member, sprite, 0);
        HuSprPriSet(group, member, 15000);
        func_80054904_main(group, member, D_80119B60_msetup[member][0], D_80119B60_msetup[member][1]);
        HuPrcVSleep();
    }
    i = 0;
    member = 4;
    initialSelection = state->unk02;
    for (; i < 2; i++, member++) {
        func_80054FF8_main(group, member, D_80119C10_msetup[initialSelection][i]);
    }
    for (i = 0; i < 2; i++) {
        window = func_8005A968_main(D_80119B90_msetup[i][0], D_80119B90_msetup[i][1],
                                    D_80119B90_msetup[i][2], D_80119B90_msetup[i][3], 0, 12);
        sprites.windows[i] = window;
        func_8005BDFC_main(window, 0);
        func_8005BEE0_main(window, 0);
        func_8005FBF8_main(window, 255, 255, 255);
        func_8005D294_main(window);
        func_8005FE90_main(window);
        HuPrcVSleep();
    }
    func_8005F904_main();
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
                    func_8005FFA8_main(sprites.windows[0]);
                    previousSelection = -1;
                    func_8005FFA8_main(sprites.windows[1]);
                    active = 1;
                    break;
                case 2:
                    for (i = 0; i < 8; i++) {
                        HuSprAttrSet(group, i, 0x8000);
                    }
                    active = 0;
                    func_8005FE90_main(sprites.windows[0]);
                    func_8005FE90_main(sprites.windows[1]);
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
                func_8005B43C_main(sprites.windows[0], D_80119BD0_msetup[selection], -1, -1);
                func_8005D294_main(sprites.windows[1]);
                func_8005B43C_main(sprites.windows[1], D_80119BF0_msetup[selection], -2, -1);
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
            func_8005F364_main(sprites.windows[i]);
        }
    }
    state->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80110954_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80111650_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A6D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A6E4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A6F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A6FC_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A708_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A714_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A720_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A72C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A738_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A744_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A74C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A754_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A75C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A764_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A76C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A774_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A77C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A784_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A78C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A794_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A79C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7A4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7AC_msetup);

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
        func_80055458_main(group, i, 0);
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
                        func_8010F43C_msetup(model, D_80119E20_msetup[i], &sprites.position);
                        func_80054904_main(group, i, sprites.position.x, sprites.position.y);
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
                            func_80055458_main(group, i, sprites.alpha[side]);
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
            D_8011A9F2_msetup[players[i]].value = 6;
        }
        if (buttons & A_BUTTON) {
            HuAudFXPlay(2);
            if (individual != 0) {
                currentPlayer = players[i];
                D_8011AA30_msetup.cpuDifficulty[currentPlayer] = selection;
                D_8011A9F2_msetup[currentPlayer].value = 5;
                i++;
                if (i >= cpuCount) {
                    break;
                }
            } else {
                for (j = 0; j < cpuCount; j++) {
                    currentPlayer = players[j];
                    D_8011AA30_msetup.cpuDifficulty[currentPlayer] = selection;
                    D_8011A9F2_msetup[currentPlayer].value = 5;
                }
                break;
            }
        }
        HuPrcVSleep();
    }
    cursor->state = 2;
    return selection;
}

#ifdef NON_MATCHING
// Shared cancellation block placement differs.
s32 func_801132C4_msetup(MsetupMenuState *state) {
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
        func_8001C6A8_main(model, D_800CCF58_main[HmfModelData[model].unk02].unk02);
        difficultyCount = 4;
    } else {
        func_8001C6A8_main(model, 0.0f);
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
                    if (D_8011AA30_msetup.cpuCount != 1) {
                        rotation = 180.0f;
                        spriteState.state = 5;
                        for (i = 0; i < 7; i++) {
                            rotation -= 180.0f / 7.0f;
                            Hu3DModelRotSet(model, rotation, 0.0f, 0.0f);
                            HuPrcVSleep();
                        }
                    } else {
                        state->result = -1;
                        goto finishSelection;
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
        func_8001ACDC_main(models[i].model);
    }
    func_8001ACDC_main(model);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_801132C4_msetup);
#endif

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
    anim = HmfAnimRead(HmfModelData[model].hmf, dataId, D_8011A6D8_msetup);
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
        func_8001ACDC_main(models[i].model);
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

s32 func_80113ED4_msetup(UnkStarLift *arg0) {
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
    curBoardIndex = D_8011AA45_msetup;
    arg0->unk4 = 0;
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
                    func_8000BBFC_main(backgroundEspriteSlot, i);
                    HuPrcVSleep();
                }
                func_8000C184_main(backgroundEspriteSlot);
                HuSprKill(var_s6);
            }
            temp_v0_4 = DataReadTemp(mainFSArray[curBoardIndex]);
            var_s6 = func_80055810_main(temp_v0_4);
            DataCloseTemp(temp_v0_4);
            backgroundEspriteSlot = InitEspriteSlot(var_s6, 0, 1);
            func_8000BC48_main(backgroundEspriteSlot, 0x1000);
            func_8000BCC8_main(backgroundEspriteSlot, 1);
            func_8000BBD4_main(backgroundEspriteSlot, 0xA0, var_fp);
            func_8000BE5C_main(backgroundEspriteSlot, tempFloat, tempFloat);
            for (i = 0; i < 255; i += (255 / 5)) {
                func_8000BBFC_main(backgroundEspriteSlot, i);
                HuPrcVSleep();
            }
            func_8000BBFC_main(backgroundEspriteSlot, 0xFF);
            prevBoardIndex = curBoardIndex;
            func_8010B82C_msetup(boardDescriptionId[curBoardIndex]);
        }
        HuPrcVSleep();
    }

    arg0->unk4 = curBoardIndex;
    if (curBoardIndex >= 0) {
        D_8011AA45_msetup = curBoardIndex;
    }

    temp_s5->work[0] = 2;
    temp_s5->work[1] = 17;

    for (i = 255; i > 0; i -= (255 / 5)) {
        func_8000BBFC_main(backgroundEspriteSlot, i);
        HuPrcVSleep();
    }

    func_8000BBFC_main(backgroundEspriteSlot, 0);

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
        func_8001ACDC_main(sp20[1].model);
    } else {
        for (i = 0; i < 2; i++) {
            func_8001ACDC_main(sp20[i].model);
        }
        func_8000C184_main(backgroundEspriteSlot);
        HuSprKill(var_s6);
    }
    func_8010DDD8_msetup(temp_s5);
    return 0;
}

s32 func_801145D0_msetup(UnkStarLift *state) {
    Array2D models;
    s32 *messages = NULL;
    s32 *backgrounds = NULL;
    s16 board = D_8011AA45_msetup;
    s32 y;
    f32 scale;
    s16 model;
    void *data;
    s16 sprite;
    s16 slot;
    s32 i;
    f32 value;

    state->unk4 = 0;
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
    sprite = func_80055810_main(data);
    DataCloseTemp(data);
    slot = InitEspriteSlot(sprite, 0, 1);
    func_8000BC48_main(slot, 0x1000);
    func_8000BCC8_main(slot, 1);
    func_8000BBD4_main(slot, 160, y);
    func_8000BE5C_main(slot, scale, scale);
    for (i = 0; i < 255; i += 255 / 7) {
        func_8000BBFC_main(slot, i);
        HuPrcVSleep();
    }
    func_8000BBFC_main(slot, 255);
    func_8010B82C_msetup(messages[board]);
    func_8010B858_msetup();
    for (i = 255; i > 0; i -= 255 / 7) {
        func_8000BBFC_main(slot, i);
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
        func_8001ACDC_main(models[i].model);
    }
    func_8000C184_main(slot);
    HuSprKill(sprite);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80114AA0_msetup);

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

    nodes[0] = func_8001D33C_main(model, D_8011A7D8_msetup);
    func_8002367C_main(matrices[0], nodes[0]->unk58);
    nodes[1] = func_8001D33C_main(model, D_8011A7E0_msetup);
    func_8002367C_main(matrices[1], nodes[1]->unk58);
    nodes[2] = func_8001D33C_main(model, D_8011A7E8_msetup);
    func_8002367C_main(matrices[2], nodes[2]->unk58);
    nodes[3] = func_8001D33C_main(model, D_8011A7F0_msetup);
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
            nodeMatrix = &func_8001D33C_main(model, D_8011A7F8_msetup)->unk58;
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

#ifdef NON_MATCHING
// Floating-point constant allocation changes saved registers and stack frame.
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

    nodes[0] = func_8001D33C_main(model, D_8011A7D8_msetup);
    func_8002367C_main(matrices[0], nodes[0]->unk58);
    nodes[1] = func_8001D33C_main(model, D_8011A800_msetup);
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
                angle += -24.0f;
            } else {
                angle += 24.0f;
            }
            if (360.0f < angle) {
                angle -= 360.0f;
            } else if (angle < 0.0f) {
                angle += 360.0f;
            }
            nodeMatrix = &func_8001D33C_main(model, D_8011A7F8_msetup)->unk58;
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
#else
INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80115A9C_msetup);
#endif

void func_80115E78_msetup(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].pos.x += x;
        HmfModelData[idx].pos.y += y;
        HmfModelData[idx].pos.z += z;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7E0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7E8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A7F8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/50B740", D_8011A800_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80115EE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_801167B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/50B740", func_80116FE0_msetup);

s32 func_80117818_msetup(void) {
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
