#include "common.h"
#include "overlays/msetup_internal.h"
#include "mallocblock.h"
#include "gcc/string.h"

typedef struct MsetupModelSpriteAnim {
    f32 scale[2];
    f32 speed[2];
    /* The eight cleanup flags share storage with the sprite fade parameters. */
    union {
        s16 destroy[8];
        struct {
            s16 reserved[4];
            s16 delta[1];
            s16 alpha[1];
        } sprite;
    } fade;
} MsetupModelSpriteAnim;

typedef struct MsetupPairSpriteAnim {
    f32 angle;
    f32 speed;
    s16 pos[2][2];
} MsetupPairSpriteAnim;

typedef struct MsetupBoardAnim {
    /* 0x00 */ f32 pos[4][3];
    /* 0x30 */ s16 unk30[5];
    /* 0x3A */ s16 count;
} MsetupBoardAnim;

extern Vec D_80119B20_msetup;
extern f32 D_80119B0C_msetup[];
extern s16 D_8011A938_msetup;
extern HmfData_Unk84_Entry2 *D_800D1FCC_main;
extern omObjData *D_80119AF0_msetup;
extern MsetupSpriteState D_8011A8B0_msetup;
extern f32 D_80119AF4_msetup;
extern f32 D_80119AF8_msetup;
extern f32 D_80119AFC_msetup;

void espScaleSet(u16, f32, f32);
s16 func_80011460_main(u8 *);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);
void espTPLvlSet(u16 spriteId, s16 arg1);
void espPriSet(u16, s32);
void espKill(u16);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void HuSprAnimKill(s16);
void func_8010DAC4_msetup(omObjData *);
void func_8010EB94_msetup(void);
void func_8010E09C_msetup(omObjData *);

void func_80016B00_main(s16 model, s16 frame, char *name, HuMtx4F *out);

void func_8010D060_msetup(HmfData *arg0, s16 arg1) {
    // 0x80 in unk9 marks the entry's texture as used, but only if a texture is assigned
    if (arg0->unk84[arg1].unk3 != -1) {
        arg0->unk84[arg1].unk9 |= 0x80;
    }
}

void func_8010D094_msetup(HmfData *arg0, s16 arg1) {
    // 0x80 in unk9 marks the entry's texture as used, but only if a texture is assigned
    if (arg0->unk84[arg1].unk3 != -1) {
        arg0->unk84[arg1].unk9 &= 0x7F;
    }
}

s16 func_8010D0C8_msetup(s16 model, char *name) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfData_Unk84_Entry2 *texture;
    s16 hash = func_80011460_main((u8 *)name);
    s32 i;

    texture = NULL;
    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
            texture = &D_800D1FCC_main[i];
            break;
        }
    }
    if (i == 128 || texture == NULL) {
        osSyncPrintf("Can't Find TextureName! mSetupGetMpAttrIdx\n");
        return -1;
    }
    for (i = 0; i < hmf->unk12; i++) {
        if (hmf->unk84[i].unkC == texture) {
            break;
        }
    }
    if (i >= hmf->unk12) {
        i = -1;
    }
    return i;
}

s16 func_8010D234_msetup(s16 positions[][2], u8 *disabled, s16 count, s16 selection, s16 directionX, s16 directionY) {
    s16 i;
    s16 closest;
    f32 x;
    f32 y;
    f32 length;
    f32 normX;
    f32 normY;
    f32 distance;
    f32 closestDistance;
    f32 deltaX;
    f32 deltaY;
    f32 candidateX;
    f32 candidateY;

    x = positions[selection][0];
    y = positions[selection][1];
    length = HuSqrtf(directionX * directionX + directionY * directionY);
    if (length == 0.0f) {
        return selection;
    }
    normX = directionX / length;
    normY = directionY / length;
    closestDistance = 100000.0f;
    closest = -1;
    for (i = 0; i < count; i++) {
        if (i == selection || disabled[i]) {
            continue;
        }
        deltaX = x - positions[i][0];
        deltaY = y - positions[i][1];
        distance = HuSqrtf(deltaX * deltaX + deltaY * deltaY);
        if (distance != 0.0f) {
            candidateX = deltaX / distance;
            candidateY = deltaY / distance;
        } else {
            candidateY = 0.0f;
            candidateX = 0.0f;
        }
        deltaX = normX - candidateX;
        deltaY = normY - candidateY;
        length = deltaX * deltaX + deltaY * deltaY;
        if (length > 0.25f) {
            continue;
        }
        if (distance < closestDistance) {
            closestDistance = distance;
            closest = i;
        }
    }
    return closest;
}

s16 func_8010D4DC_msetup(s16 positions[][2], u8 *disabled, s16 count, s16 selection, s16 controller, s16 buttons) {
    s16 directionX;
    s16 directionY;

    directionX = D_800CBB6E_main[controller];
    directionX = -directionX;
    directionY = D_800D20A1_main[controller];
    if (buttons & L_JPAD) {
        if (directionX < 30) {
            directionX = 100;
        }
    } else if (buttons & R_JPAD) {
        if (directionX > -30) {
            directionX = -100;
        }
    }
    if (buttons & U_JPAD) {
        if (directionY < 30) {
            directionY = 100;
        }
    } else if (buttons & D_JPAD) {
        if (directionY > -30) {
            directionY = -100;
        }
    }
    return func_8010D234_msetup(positions, disabled, count, selection, directionX, directionY);
}

s16 func_8010D5EC_msetup(s16 controller) {
    s16 buttons = D_800CDA7C_main[controller];
    s8 stickX = D_800CBB6E_main[controller];
    s8 stickY = D_800D20A1_main[controller];

    if (stickX > 30) {
        buttons |= R_JPAD;
    } else if (stickX < -30) {
        buttons |= L_JPAD;
    }
    if (stickY > 30) {
        buttons |= U_JPAD;
    } else if (stickY < -30) {
        buttons |= D_JPAD;
    }
    return buttons;
}

s16 func_8010D684_msetup(s16 controller, s16 *previousButtons) {
    s16 oldButtons = *previousButtons;
    s16 buttons = func_8010D5EC_msetup(controller);

    oldButtons &= buttons;
    oldButtons ^= buttons;
    *previousButtons = buttons;
    return oldButtons;
}

void func_8010D6D0_msetup(void) {
    s16 sprite;
    s16 slot;
    s16 previousState;
    s16 visible;
    s16 startX;
    s16 startY;
    s16 deltaX;
    s16 deltaY;
    s16 previousSelection;
    s16 targetX;
    s16 targetY;
    s16 x;
    s16 y;
    s16 alpha;
    s16 alphaDelta;
    s16 frames;
    f32 weight;
    MsetupCursorState *cursor;
    s16 *position;

    cursor = HuPrcCurrentGet()->user_data;
    position = cursor->pos;
    sprite = func_8000B838_main(cursor->dataId);
    slot = espEntry(sprite, cursor->priority, 1);
    espPriSet(slot, 1);
    x = targetX = cursor->pos[0];
    y = targetY = cursor->pos[1];
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
    while (1) {
        if (previousState != cursor->state) {
            switch (cursor->state) {
                case 0:
                    break;
                case 1:
                    alphaDelta = 64;
                    if (visible == 0) {
                        alpha = 0;
                        espTPLvlSet(slot, 0);
                        espDispOn(slot);
                        visible = 1;
                    }
                    break;
                case 2:
                    if (visible != 0) {
                        alphaDelta = -64;
                    }
                    break;
                case -1:
                    espKill(slot);
                    HuSprAnimKill(sprite);
                    cursor->state = 100;
                    while (1) {
                        HuPrcVSleep();
                    }
                    break;
            }
            previousState = cursor->state;
        }
        if (previousSelection != cursor->selection) {
            s16 selection = cursor->selection;

            previousSelection = selection;
            if (cursor->positions != NULL) {
                position[0] = cursor->positions[selection][0];
                position[1] = cursor->positions[selection][1];
            }
        }
        if (targetX != position[0] || targetY != position[1]) {
            targetX = position[0];
            targetY = position[1];
            frames = cursor->flags;
            if (frames != 0) {
                startX = x;
                startY = y;
                deltaX = targetX - x;
                deltaY = targetY - y;
            }
        }
        if (alphaDelta != 0) {
            alpha += alphaDelta;
            if (alpha >= 256) {
                alpha = 255;
                alphaDelta = 0;
            } else if (alpha < 0) {
                alpha = 0;
                alphaDelta = 0;
                espDispOff(slot);
                visible = 0;
            }
            espTPLvlSet(slot, alpha);
        }
        if ((x != targetX) | (y != targetY)) {
            if (frames == 0) {
                x = targetX;
                y = targetY;
            } else {
                frames--;
                weight = sindf((90.0f / cursor->flags) * (cursor->flags - frames));
                x = startX + deltaX * weight;
                y = startY + deltaY * weight;
            }
            espPosSet(slot, x, y);
        }
        HuPrcVSleep();
    }
}

void func_8010DAC4_msetup(omObjData *object) {
    MsetupPairSpriteAnim *anim;
    s16 slot;
    s16 y;
    s16 x;
    s32 value;
    f32 offset;

    anim = object->data;
    if (object->work[0] != object->work[3]) {
        switch (object->work[0]) {
            case 0:
                break;
            case 1:
                object->work[2] = 0;
                espDispOn(object->model[0]);
                espDispOn(object->model[1]);
                break;
            case 2:
                object->work[2] = 255;
                break;
            case 3:
                if (object->work[3] == 4) {
                    value = object->work[2];
                    slot = object->model[value];
                    x = anim->pos[value][0];
                    y = anim->pos[value][1];
                    espPosSet(slot, x, y);
                }
                object->work[2] = 0;
                object->work[1] = 5;
                anim->angle = 360.0f;
                anim->speed = -36.0f;
                break;
            case 4:
                if (object->work[3] == 3) {
                    value = object->work[2];
                    slot = object->model[value];
                    x = anim->pos[value][0];
                    y = anim->pos[value][1];
                    espPosSet(slot, x, y);
                }
                object->work[2] = 1;
                object->work[1] = 5;
                anim->angle = 0;
                anim->speed = 36.0f;
                break;
            case 255:
                espKill(object->model[0]);
                espKill(object->model[1]);
                HuSprAnimKill(object->model[2]);
                HuSprAnimKill(object->model[3]);
                object->work[0] = 0;
                break;
        }
        object->work[3] = object->work[0];
    }
    switch (object->work[3]) {
        case 0:
            break;
        case 1:
            value = object->work[2] + object->work[1];
            if (value >= 256) {
                value = 255;
                object->work[0] = 0;
            }
            object->work[2] = value;
            espTPLvlSet(object->model[0], value);
            espTPLvlSet(object->model[1], value);
            break;
        case 2:
            value = object->work[2] - object->work[1];
            if (value < 0) {
                value = 0;
                espDispOff(object->model[0]);
                espDispOff(object->model[1]);
                object->work[0] = 0;
            }
            object->work[2] = value;
            espTPLvlSet(object->model[0], value);
            espTPLvlSet(object->model[1], value);
            break;
        case 3:
        case 4:
            value = object->work[2];
            slot = object->model[value];
            x = anim->pos[value][0];
            y = anim->pos[value][1];
            if (object->work[1] == 0) {
                object->work[0] = 0;
            } else {
                object->work[1]--;
                anim->angle += anim->speed;
                offset = sindf(anim->angle);
                offset *= 12.0f;
                x += offset;
            }
            espPosSet(slot, x, y);
            break;
    }
}

void func_8010DDD8_msetup(omObjData *object) {
    espKill(object->model[0]);
    espKill(object->model[1]);
    HuSprAnimKill(object->model[2]);
    HuSprAnimKill(object->model[3]);
    HuMemFree(object->data);
    omDelObj(object);
}

omObjData *func_8010DE38_msetup(s32 leftX, s32 rightX, s32 y) {
    s16 i;
    MsetupPairSpriteAnim *anim;
    omObjData *object;
    s16 sprite;

    object = omAddObj(0x17D0, 4, 0, -1, func_8010DAC4_msetup);
    if (object == NULL) {
        return NULL;
    }
    omSetStatBit(object, OM_STAT_MODELPAUSE);
    anim = HuMemAllocTag(sizeof(MsetupPairSpriteAnim), TAG_OVERLAY);
    memset(anim, 0, sizeof(MsetupPairSpriteAnim));
    object->data = anim;

    sprite = func_8000B838_main(0x140012);
    i = espEntry(sprite, 0, 1);
    object->model[0] = i;
    object->model[2] = sprite;
    espPriSet(i, 0x4800);
    espPosSet(i, leftX, y);
    espDispOff(i);
    anim->pos[0][0] = leftX;
    anim->pos[0][1] = y;

    sprite = func_8000B838_main(0x140013);
    i = espEntry(sprite, 0, 1);
    object->model[1] = i;
    object->model[3] = sprite;
    espPriSet(i, 0x4800);
    espPosSet(i, rightX, y);
    espDispOff(i);
    anim->pos[1][0] = rightX;
    anim->pos[1][1] = y;

    for (i = 0; i < 4; i++) {
        object->work[i] = 0;
    }
    return object;
}

s16 func_8010E00C_msetup(omObjData *arg0, s16 arg1) {
    MsetupBoardAnim *anim;

    if (arg0 == NULL) {
        return 0;
    }
    anim = arg0->data;
    if (arg1 > 4) {
        arg1 = 4;
    }
    anim->count = arg1;
    return arg1;
}

void func_8010E044_msetup(omObjData *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5) {
    MsetupBoardAnim *anim;

    if (arg0 == NULL) {
        return;
    }
    anim = arg0->data;
    if (arg1 < anim->count) {
        anim->pos[arg1][0] = arg3;
        anim->pos[arg1][1] = arg4;
        anim->pos[arg1][2] = arg5;
        anim->unk30[arg1] = arg2;
    }
}

void func_8010E09C_msetup(omObjData *object) {
    s16 model = object->model[0];
    s32 modelIndex = model;
    MsetupBoardAnim *anim;
    s32 i;
    s32 range;
    f32 x;
    f32 z;
    f32 *pos;

    if (object->work[1] != object->work[2]) {
        func_8000CD00_main(modelIndex, D_80119AF4_msetup, D_80119AF8_msetup, D_80119AFC_msetup);
        object->work[2] = object->work[1];
    }
    anim = object->data;
    switch (object->work[0]) {
        case 0:
            break;
        case 1:
            for (i = 0; i < anim->count; i++) {
                range = anim->unk30[i];
                pos = anim->pos[i];
                x = (rand8() * range) / 256 - range / 2;
                z = (rand8() * range) / 256 - range / 2;
                func_8000CD74_main(model, x + pos[0], pos[1], z + pos[2]);
            }
            break;
    }
}

omObjData *func_8010E21C_msetup(void) {
    MsetupBoardAnim *anim;
    omObjData *object;
    HmfModelData_UnkBC_Struct *data;
    s16 model;

    object = omAddObj(0x17D0, 1, 0, -1, func_8010E09C_msetup);
    D_80119AF0_msetup = object;
    if (object == NULL) {
        return NULL;
    }
    omSetStatBit(object, OM_STAT_MODELPAUSE);
    anim = HuMemAllocTag(sizeof(MsetupBoardAnim), TAG_OVERLAY);
    memset(anim, 0, sizeof(MsetupBoardAnim));
    object->data = anim;
    model = object->model[0] = func_8000CBA0_main(0x110012, 0x289);
    data = HmfModelData[model].unkBC;
    data->unk1C.f = data->unk20.f = data->unk24.f = 0.0f;
    data->unk10.f = 100.0f;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->work[0] = 0;
    object->work[1] = 0;
    object->work[2] = 0xFF;
    object->work[3] = 0;
    return object;
}

void func_8010E32C_msetup(Array2D *arg0, s32 count, f32 rotation, s32 link) {
    s32 i;
    s16 sourceModel = -1;
    s16 model;
    MsetupLinkedModel *entry;
    Vec *rot;

    for (i = 0; i < count; i++) {
        if (sourceModel < 0 || !link) {
            model = sourceModel = func_8000B108_main(0x140003, 0x2A9);
        } else {
            model = Hu3DModelLink(sourceModel);
        }
        (*arg0)[i].model = model;
        (*arg0)[i].flags = 0;
        entry = &(*arg0)[i];
        rot = &entry->rot;
        entry->rot.x = entry->rot.z = 0.0f;
        if (i != 0) {
            entry->rot.y = rotation + 180.0f;
        } else {
            rot->y = rotation;
        }
        Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
        entry->pos = D_80119B20_msetup;
        Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
        Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
        HuPrcVSleep();
    }
}

void func_8010E4BC_msetup(Array2D *arg0, s32 arg1, f32 arg2) {
    func_8010E32C_msetup(arg0, arg1, arg2, 1);
}

void func_8010E4D8_msetup(MsetupLinkedModel *entry, s32 count) {
    s32 i;

    for (i = 0; i < count; i++, entry++) {
        func_8001C514_main(entry->model);
    }
}

void func_8010E52C_msetup(MsetupLinkedModel *models, MsetupModelTarget *targets, s16 count, s16 frames,
                          s16 *scaleModels, s16 scaleCount, f32 startScale, f32 endScale) {
    Vec pos;
    MsetupLinkedModel *entry;
    Vec *rot;
    MsetupModelTarget *target;
    s16 model;
    s32 i;
    s32 frame;
    s32 j;
    f32 progress;
    f32 rotation;
    f32 yRot;
    f32 scaleRange;

    scaleRange = endScale - startScale;
    for (frame = 0; frame < frames; frame++) {
        progress = (f32)frame / frames;
        for (i = 0; i < count; i++) {
            if (models[i].flags & 1) {
                continue;
            }
            model = models[i].model;
            entry = &models[i];
            target = &targets[i];
            pos.x = (target->pos.x - entry->pos.x) * progress;
            pos.y = (target->pos.y - entry->pos.y) * progress;
            pos.z = (target->pos.z - entry->pos.z) * progress;
            pos.x += entry->pos.x;
            pos.y += entry->pos.y;
            pos.z += entry->pos.z;
            rot = &entry->rot;
            if (entry->rot.y > 180.0f) {
                rotation = entry->rot.y - 360.0f;
                yRot = (targets[i].rotation - rotation) * progress + rotation;
            } else {
                yRot = (targets[i].rotation - rot->y) * progress + rot->y;
            }
            Hu3DModelRotSet(model, rot->x, yRot, rot->z);
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        }
        rotation = startScale + progress * scaleRange;
        if (scaleModels != NULL) {
            for (j = 0; j < scaleCount; j++) {
                if (scaleModels[j] >= 0) {
                    Hu3DModelScaleSet(scaleModels[j], rotation, rotation, rotation);
                }
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        if (models[i].flags & 1) {
            continue;
        }
        model = models[i].model;
        entry = &models[i];
        entry->pos = targets[i].pos;
        entry->rot.y = targets[i].rotation;
        Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
        Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
    }
    if (scaleModels != NULL) {
        for (j = 0; j < scaleCount; j++) {
            if (scaleModels[j] >= 0) {
                Hu3DModelScaleSet(scaleModels[j], endScale, endScale, endScale);
            }
        }
    }
}

void func_8010E8C8_msetup(Array2D *models, s16 count, s16 frames, f32 rotation, f32 height, f32 scale, f32 endScale,
                          s16 animateBoard) {
    s16 boardCount;
    s32 i;
    s16 model;
    MsetupLinkedModel *entry;
    MsetupLinkedModel *current;
    Vec *rot;
    f32 rotationStep;
    f32 heightStep;
    f32 scaleStep;

    if ((D_80119AF0_msetup != NULL) & (animateBoard != 0)) {
        D_80119AF0_msetup->work[0] = 1;
        D_80119AF0_msetup->work[1] = 1;
        boardCount = func_8010E00C_msetup(D_80119AF0_msetup, animateBoard);
    } else {
        boardCount = 0;
    }
    rotationStep = rotation / frames;
    heightStep = height / frames;
    scaleStep = (endScale - scale) / frames;
    while (frames != 0) {
        entry = *models;
        for (i = 0; i < count; i++) {
            if (entry->flags & 1) {
                continue;
            }
            model = entry->model;
            current = entry;
            rot = &entry->rot;
            entry->rot.y = rotationStep + entry->rot.y;
            if (entry->rot.y >= 360.0f) {
                entry->rot.y -= 360.0f;
            }
            if (rot->y < 0.0f) {
                rot->y += 360.0f;
            }
            current->pos.y = heightStep + current->pos.y;
            Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
            Hu3DModelPosSet(model, current->pos.x, current->pos.y, current->pos.z);
            Hu3DModelScaleSet(model, scale, scale, scale);
            if (i < boardCount) {
                func_8010E044_msetup(D_80119AF0_msetup, i, 120, current->pos.x, current->pos.y, current->pos.z);
            }
            entry++;
        }
        scale += scaleStep;
        HuPrcVSleep();
        frames--;
    }
    entry = *models;
    for (i = 0; i < count; i++) {
        if (entry->flags & 1) {
            continue;
        }
        Hu3DModelScaleSet(entry->model, endScale, endScale, endScale);
        entry++;
    }
    if (boardCount != 0) {
        D_80119AF0_msetup->work[0] = 0;
    }
}

void func_8010EB94_msetup(void) {
    MsetupModelSpriteAnim anim;
    s16 previousState;
    s16 index;
    s16 handle;
    s32 i;
    MsetupSpriteState *data;
    s16 *slots;
    s16 *values;

    data = HuPrcCurrentGet()->user_data;
    slots = data->spriteSlots;
    values = data->values;
    for (i = 0; i < 8; i++) {
        slots[i] = -1;
        values[i] = -1;
        anim.fade.destroy[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        anim.speed[i] = 0;
    }
    for (i = 0; i < 1; i++) {
        anim.fade.sprite.delta[i] = 0;
    }
    data->state = 0;
    previousState = 0;
    while (1) {
        if (previousState != data->state) {
            switch (data->state) {
                case 0:
                    break;
                case 1:
                    if (slots[0] < 0 || slots[2] < 0) {
                        data->state = 0;
                        break;
                    }
                    anim.scale[0] = 0;
                    anim.speed[0] = 1.0f / 7.0f;
                    handle = slots[0];
                    func_8001C258_main(handle, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(handle, 260.0f, 345.0f, -40.0f);
                    Hu3DModelRotSet(handle, 0, 180.0f, 0);
                    anim.fade.sprite.alpha[0] = 0;
                    anim.fade.sprite.delta[0] = 25;
                    handle = slots[2];
                    switch (D_8011A938_msetup) {
                        case 0:
                            espScaleSet((u16)handle, 0.8f, 0.8f);
                            break;
                        case 1:
                            espScaleSet((u16)handle, 0.8f, 0.8f);
                            break;
                    }
                    espPosSet((u16)handle, 263, 48);
                    espDispOn((u16)handle);
                    anim.fade.destroy[0] = 0;
                    anim.fade.destroy[2] = 0;
                    data->state = 0;
                    break;
                case 3:
                    anim.fade.destroy[0] = 1;
                    anim.fade.destroy[2] = 1;
                case 2:
                    if (slots[0] < 0 || slots[2] < 0) {
                        data->state = 0;
                        break;
                    }
                    anim.speed[0] = -1.0f / 7.0f;
                    anim.fade.sprite.alpha[0] = 255;
                    anim.fade.sprite.delta[0] = -36;
                    data->state = 0;
                    break;
                case 4:
                    if (slots[1] < 0) {
                        data->state = 0;
                        break;
                    }
                    anim.scale[1] = 0;
                    anim.speed[1] = 1.0f / 7.0f;
                    handle = slots[1];
                    func_8001C258_main(handle, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(handle, 260.0f, 175.0f, -80.0f);
                    Hu3DModelRotSet(handle, 0, 180.0f, 0);
                    anim.fade.destroy[1] = 0;
                    data->state = 0;
                    break;
                case 6:
                    anim.fade.destroy[1] = 1;
                case 5:
                    if (slots[1] < 0) {
                        data->state = 0;
                        break;
                    }
                    anim.speed[1] = -1.0f / 7.0f;
                    data->state = 0;
                    break;
                case 9:
                    for (i = 0; i < 8; i++) {
                        if (slots[i] >= 0) {
                            anim.fade.destroy[i] = 1;
                        }
                    }
                case 8:
                    handle = 0;
                    for (i = 0; i < 2; i++, handle++) {
                        if (slots[handle] >= 0) {
                            anim.speed[i] = -1.0f / 7.0f;
                        }
                    }
                    handle = 2;
                    for (i = 0; i < 1; i++, handle++) {
                        if (slots[handle] >= 0) {
                            anim.fade.sprite.delta[i] = -36;
                        }
                    }
                    break;
                case 255:
                    handle = 0;
                    for (i = 0; i < 2; i++, handle++) {
                        if (values[handle] >= 0) {
                            func_80033430_main(values[handle]);
                        }
                        if (slots[handle] >= 0) {
                            Hu3DModelKill(slots[handle]);
                        }
                    }
                    handle = 2;
                    for (i = 0; i < 1; i++) {
                        if (slots[handle] >= 0) {
                            espKill((u16)slots[handle]);
                        }
                        if (values[handle] >= 0) {
                            HuSprAnimKill(values[handle]);
                        }
                    }
                    for (i = 0; i < 2; i++) {
                        anim.speed[i] = 0;
                    }
                    for (i = 0; i < 1; i++) {
                        anim.fade.sprite.delta[i] = 0;
                    }
                    data->state = 0;
                    break;
            }
            previousState = data->state;
        }
        for (i = 0; i < 2; i++) {
            if (anim.speed[i] == 0) {
                continue;
            }
            index = i;
            handle = slots[index];
            if (handle >= 0) {
                anim.scale[i] += anim.speed[i];
                if (anim.scale[i] >= D_80119B0C_msetup[index]) {
                    anim.scale[i] = D_80119B0C_msetup[index];
                    anim.speed[i] = 0;
                } else if (anim.scale[i] <= 0) {
                    anim.scale[i] = 0;
                    anim.speed[i] = 0;
                    func_8001C258_main(handle, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (anim.fade.destroy[index] != 0) {
                        if (values[index] >= 0) {
                            func_80033430_main(values[index]);
                            values[index] = -1;
                        }
                        Hu3DModelKill(handle);
                        anim.fade.destroy[index] = 0;
                        slots[index] = -1;
                        handle = -1;
                    }
                }
                if (handle >= 0) {
                    Hu3DModelScaleSet(handle, anim.scale[i], anim.scale[i], anim.scale[i]);
                }
            }
        }
        for (i = 0; i < 1; i++) {
            if (anim.fade.sprite.delta[i] != 0) {
                index = i + 2;
                handle = slots[index];
                if (handle >= 0) {
                    anim.fade.sprite.alpha[i] += anim.fade.sprite.delta[i];
                    if (anim.fade.sprite.alpha[i] >= 256) {
                        anim.fade.sprite.alpha[i] = 255;
                        anim.fade.sprite.delta[i] = 0;
                    } else if (anim.fade.sprite.alpha[i] < 0) {
                        anim.fade.sprite.alpha[i] = 0;
                        anim.fade.sprite.delta[i] = 0;
                        espDispOff((u16)handle);
                        if (anim.fade.destroy[index] != 0) {
                            espKill((u16)handle);
                            if (values[index] >= 0) {
                                HuSprAnimKill(values[index]);
                                values[index] = -1;
                            }
                            anim.fade.destroy[index] = 0;
                            slots[index] = -1;
                            handle = -1;
                        }
                    }
                    if (handle >= 0) {
                        espTPLvlSet((u16)handle, anim.fade.sprite.alpha[i]);
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

Process *func_8010F2BC_msetup(void) {
    Process *process = omAddPrcObj(func_8010EB94_msetup, 0x3F00, 0x600, 0);

    process->user_data = &D_8011A8B0_msetup;
    return process;
}

s16 func_8010F2F4_msetup(Process *arg0, s16 arg1) {
    s16 *ptr = arg0->user_data;
    s32 value = arg1;

    if (value != 0) {
        *ptr = arg1;
    } else {
        value = *ptr;
    }
    return value;
}

void func_8010F320_msetup(Process *process, s16 index, s16 spriteSlot, s16 value) {
    MsetupSpriteState *data = process->user_data;

    data->spriteSlots[index] = spriteSlot;
    data->values[index] = value;
}

void func_8010F33C_msetup(s16 model, Vec *worldPos, HuMtx4F nodeTransform) {
    HuMtx4F transform;
    HuMtx4F combined;
    HmfModel *entry = &HmfModelData[model];

    func_80088800_main(transform, entry->pos.x, entry->pos.y, entry->pos.z);
    func_80017D24_main(transform, entry->rot.x, entry->rot.y, entry->rot.z);
    func_80017CD0_main(transform, entry->scale.x, entry->scale.y, entry->scale.z);
    func_80018044_main(nodeTransform, transform, combined);
    worldPos->x = combined[0][0] + combined[1][0] + combined[2][0] + combined[3][0];
    worldPos->y = combined[0][1] + combined[1][1] + combined[2][1] + combined[3][1];
    worldPos->z = combined[0][2] + combined[1][2] + combined[2][2] + combined[3][2];
}

void func_8010F43C_msetup(s16 model, char *node, Vec2f *screenPos) {
    HuMtx4F transform;
    Vec worldPos;

    func_80016B00_main(model, HmfModelData[model].motTime, node, &transform);
    func_8010F33C_msetup(model, &worldPos, transform);
    Hu3D3Dto2D(0, &worldPos, screenPos);
}
