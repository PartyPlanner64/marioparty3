#include "common.h"
#include "overlays/msetup.h"
#include "game/camera.h"
#include "game/sprite.h"
#include "input.h"
#include "mallocblock.h"
#include "gcc/string.h"

typedef MsetupLinkedModel Array2D[2];

typedef struct MsetupSpriteState {
    s16 state;
    s16 unk02;
    s16 spriteSlots[8];
    s16 values[8];
} MsetupSpriteState;

typedef struct MsetupPairSpriteAnim {
    f32 angle;
    f32 speed;
    s16 pos[2][2];
} MsetupPairSpriteAnim;

typedef struct MsetupEntryAnim {
    Vec pos;
    f32 value;
    s16 index;
    s16 state;
} MsetupEntryAnim;

typedef struct UnkStarLift {
    char unk_00[0x04];
    s16 unk4;
} UnkStarLift;

typedef struct MsetupBoardAnim {
    /* 0x00 */ f32 pos[4][3];
    /* 0x30 */ s16 unk30[5];
    /* 0x3A */ s16 count;
} MsetupBoardAnim;

extern Vec D_80119B20_msetup;
extern HmfData_Unk84_Entry2 *D_800D1FCC_main;
extern s16 D_800D418E_main;
extern Process *D_80119420_msetup;
extern Vec D_80119A0C_msetup[];
extern Vec D_80119A3C_msetup[];
extern f32 D_80119A54_msetup[];
extern f32 D_80119A64_msetup[];
extern s16 D_80119A6C_msetup[];
extern Process *D_8011A898_msetup[];
extern MsetupEntryAnim D_8011A9E0_msetup[];
extern omObjData *D_80119AF0_msetup;
extern s32 D_80119E94_msetup[];
extern s32 D_80119EAC_msetup[];
extern s32 D_80119EC4_msetup[];
extern s32 D_80119EE0_msetup[];
extern s16 D_8011A938_msetup;
extern s16 D_8011A948_msetup;
extern s16 D_8011A8B0_msetup[];
extern s16 D_8011A890_msetup;
extern u8 D_8011AA45_msetup; // board index chosen
extern UnkMsetupEntry D_8011A9F2_msetup[];
extern f32 D_80119AF4_msetup;
extern f32 D_80119AF8_msetup;
extern f32 D_80119AFC_msetup;

s16 func_80011460_main(u8 *);
f32 func_80054B1C_main(s16, s16, s16, f32, f32, f32);
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
s32 func_800329B4_main(void *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8010B82C_msetup(s32);
void func_8010BEF8_msetup(void);
s32 func_8010B858_msetup(void);
void func_8010B998_msetup(void);
s32 func_8010D684_msetup(s16, s16 *);
void func_8010DAC4_msetup(omObjData *);
void func_8010DDD8_msetup(omObjData *);
omObjData *func_8010DE38_msetup(s32, s32, s32);
void func_8010E4BC_msetup(Array2D *, s32, f32);
void func_8010E4D8_msetup(MsetupLinkedModel *, s32);
void func_8010E8C8_msetup(Array2D *, s32, s32, f32, f32, f32, f32, s32);
void func_8010EB94_msetup(void);
void func_8010E09C_msetup(omObjData *);
void func_8010F320_msetup(Process *, s16, s16, s16);
s32 _CheckFlag(s32);            /* extern */
s16 func_80055810_main(void *); /* extern */
s32 func_80113ED4_msetup(UnkStarLift *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010ACC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010AF40_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B1F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B388_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010B5D0_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CAF0_msetup);

void func_8010CC70_msetup(s16 model, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *data = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = data->unk58;
    s16 i;
    f32 value1;
    f32 value2;

    data->unk08.f = arg1;
    data->unk0C.f = arg2;
    data->unk10.f = arg3;
    data->unk14 = arg4;
    value1 = (arg3 - arg3 / 10.0f) / arg1;
    value2 = arg2 / arg1;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk1C = value1;
        entry->unk24 = value2;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CD14_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010CE8C_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D234_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D4DC_msetup);

s16 func_8010D5EC_msetup(s16 controller) {
    s16 buttons = D_800CDA7C_main[controller];
    s8 stickX = D_800CBB6E_main[controller];
    s8 stickY = D_800D20A1_main[controller];

    if (stickX > 30) {
        buttons |= 0x100;
    } else if (stickX < -30) {
        buttons |= 0x200;
    }
    if (stickY > 30) {
        buttons |= 0x800;
    } else if (stickY < -30) {
        buttons |= 0x400;
    }
    return buttons;
}

s32 func_8010D684_msetup(s16 controller, s16 *previousButtons) {
    s16 oldButtons = *previousButtons;
    s16 buttons = func_8010D5EC_msetup(controller);

    oldButtons &= buttons;
    oldButtons ^= buttons;
    *previousButtons = buttons;
    return oldButtons;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010D6D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010DAC4_msetup);

void func_8010DDD8_msetup(omObjData *object) {
    func_8000C184_main(object->model[0]);
    func_8000C184_main(object->model[1]);
    HuSprKill(object->model[2]);
    HuSprKill(object->model[3]);
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
    omSetStatBit(object, 0x100);
    anim = HuMemAllocTag(sizeof(MsetupPairSpriteAnim), 0x7918);
    memset(anim, 0, sizeof(MsetupPairSpriteAnim));
    object->data = anim;

    sprite = func_8000B838_main(0x140012);
    i = InitEspriteSlot(sprite, 0, 1);
    object->model[0] = i;
    object->model[2] = sprite;
    func_8000BCC8_main(i, 0x4800);
    func_8000BBD4_main(i, leftX, y);
    func_8000BB94_main(i);
    anim->pos[0][0] = leftX;
    anim->pos[0][1] = y;

    sprite = func_8000B838_main(0x140013);
    i = InitEspriteSlot(sprite, 0, 1);
    object->model[1] = i;
    object->model[3] = sprite;
    func_8000BCC8_main(i, 0x4800);
    func_8000BBD4_main(i, rightX, y);
    func_8000BB94_main(i);
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
    omSetStatBit(object, 0x100);
    anim = HuMemAllocTag(sizeof(MsetupBoardAnim), 0x7918);
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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E52C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010E8C8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010EB94_msetup);

void func_8010F2BC_msetup(void) {
    omAddPrcObj(func_8010EB94_msetup, 0x3F00, 0x600, 0)->user_data = &D_8011A8B0_msetup;
}

s16 func_8010F2F4_msetup(Process *arg0, s16 arg1) {
    s16 *ptr = arg0->user_data;
    s32 value = arg1;

    if (value != 0) {
        *ptr = (s16)arg1;
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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F33C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F43C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F4E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8010F87C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_8011035C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80110954_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80111650_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6E4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A6FC_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A708_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A714_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A720_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A72C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A738_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A744_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A74C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A754_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A75C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A764_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A76C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A774_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A77C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A784_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A78C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A794_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A79C_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7A4_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7AC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112804_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112E08_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80112F5C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801132C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801138F8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113DEC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E20_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E54_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80113E88_msetup);

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
    s32 pad;
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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801145D0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80114AA0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801150A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801152C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801157B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115A9C_msetup);

void func_80115E78_msetup(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].pos.x += x;
        HmfModelData[idx].pos.y += y;
        HmfModelData[idx].pos.z += z;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7D8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7E8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F0_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A7F8_msetup);

INCLUDE_RODATA("asm/nonmatchings/overlays/msetup/506F20", D_8011A800_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80115EE0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_801167B8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80116FE0_msetup);

s32 func_80117818_msetup(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117820_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80117A3C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/506F20", func_80118D48_msetup);
