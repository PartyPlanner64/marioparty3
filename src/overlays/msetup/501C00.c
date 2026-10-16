#include "common.h"
#include "game/vibrator.h"
#include "overlays/msetup.h"
#include "mallocblock.h"
#include "gcc/string.h"

typedef MsetupLinkedModel Array2D[2];

typedef struct UnkStarLift {
    char unk_00[0x04];
    s16 unk4;
} UnkStarLift;

typedef struct MsetupSceneryState {
    f32 upperHeights[3];
    f32 lowerHeights[3];
    f32 rotation;
    Vec innerPositions[3];
    Vec outerPositions[6];
} MsetupSceneryState;

typedef struct MsetupCameraPreset {
    Vec rot;
    Vec center;
    f32 zoom;
    f32 fov;
} MsetupCameraPreset;

extern s16 D_801198C0_msetup;
extern void (*D_8011955C_msetup[])(void);
extern omObjData *D_80119430_msetup;
extern s16 (*D_80119434_msetup[])(s16);
extern s16 (*D_80119458_msetup[])(s16);
extern u8 D_80119478_msetup[];
extern s16 (*D_80119510_msetup[])(s16);
extern s16 (*D_80119524_msetup[])(s16);
extern u8 D_80119488_msetup[];
extern u8 D_80119498_msetup[];
extern s32 D_801194A8_msetup[];
extern u8 D_8011A949_msetup;
extern u16 D_80119410_msetup;
extern s16 D_80119412_msetup;
extern u8 D_80119419_msetup;
extern MsetupPlayerConfig D_8011AA30_msetup;
extern u8 D_8011AA40_msetup;
extern u8 D_8011AA41_msetup;
extern s16 D_8011AA48_msetup;
extern s16 D_8011A93A_msetup;
extern s16 D_8011A944_msetup;
extern s16 D_8011A946_msetup;
extern s16 D_8011AA4C_msetup;
extern s16 D_8011AA4A_msetup;
extern f32 D_80119414_msetup;
extern u32 D_8011941C_msetup;
extern f32 D_8011A93C_msetup;
extern f32 D_8011A940_msetup;
extern Vec D_8011A994_msetup;
extern Process *D_80119420_msetup;
extern s32 D_80119E94_msetup[];
extern s32 D_80119EAC_msetup[];
extern s32 D_80119EC4_msetup[];
extern s32 D_80119EE0_msetup[];
extern s16 D_8011A880_msetup;
extern UnkMsetupEntry D_8011A9F2_msetup[];
extern u8 D_8011AA3C_msetup[];
extern MsetupMenuState D_8011A882_msetup;
extern s16 D_8011A990_msetup;
extern s16 D_8011A938_msetup;
extern s16 D_8011A948_msetup;
extern s16 D_8011A950_msetup[];
extern s16 D_8011A9A0_msetup[];
extern u8 D_8011AA43_msetup;
extern u8 D_8011AA45_msetup; // board index chosen
extern u8 D_8011AA47_msetup;
extern s32 D_80119424_msetup[];
extern s32 D_80119534_msetup[];
extern s32 D_80119548_msetup[];
extern MsetupCameraPreset D_80119580_msetup;
extern MsetupCameraPreset D_801195A0_msetup;
extern MsetupCameraPreset D_801197BC_msetup;
extern MsetupCameraPreset D_801196C0_msetup;

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
void func_8010B82C_msetup(s32);
s32 func_8010B858_msetup(void);
void func_8010B968_msetup(u32, s8);
void func_8010B998_msetup(void);
s16 func_8010BA3C_msetup(void);
omObjData *func_8010E21C_msetup(void);
void func_8010BBF4_msetup(s16);
void func_8010BE8C_msetup(s16);
void func_8010BA6C_msetup(s16, s16);
void func_8010BC18_msetup(s16, s16);
void func_8010B9B8_msetup(s32, s32);
s32 func_8010D684_msetup(s16, s16 *);
void func_8010DDD8_msetup(void *);
omObjData *func_8010DE38_msetup(s32, s32, s32);
void func_8010E4BC_msetup(Array2D *, s32, f32);
void func_8010E4D8_msetup(MsetupLinkedModel *, s32);
void func_8010E8C8_msetup(Array2D *, s32, s32, f32, f32, f32, f32, s32);
void func_8010F320_msetup(Process *, s16, s16, s16);
s16 func_8010F2F4_msetup(Process *, s16);
s32 _CheckFlag(s32);            /* extern */
s16 func_80055810_main(void *); /* extern */
s32 func_80113ED4_msetup(UnkStarLift *arg0);
void func_80107F88_msetup(s16, s16, s16);
void func_80105F7C_msetup(MsetupModelEntry *, s16);
void func_80105DB4_msetup(omObjData *);
void func_8010A7EC_msetup(s16);
void func_8010ACB0_msetup(void);
void func_8010A35C_msetup(s16 (**)(s16));
void func_801059A0_msetup(void);
void func_80105C4C_msetup(omObjData *);
void func_80106320_msetup(void);
void func_80106DF8_msetup(void);
void func_80117820_msetup(void);
void func_8010B1F4_msetup(void);
Process *func_8010F2BC_msetup(void);
void func_801068F4_msetup(MsetupCameraPreset *, f32, void (*)(s16, s16, s16));

void func_801059A0_msetup(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(25);
    omInitObjMan(51, 25);
    func_8005A6B0_main();
    func_8004A208_main();
    D_800CD280_main = 1;
    D_8011A940_msetup = 80.0f;
    D_8011A93C_msetup = 6000.0f;
    D_80119414_msetup = 58.0f;
    Hu3DCamSetPerspective(0, D_80119414_msetup, D_8011A940_msetup, D_8011A93C_msetup);
    D_8011A994_msetup.x = 0;
    D_8011A994_msetup.y = 0;
    D_8011A994_msetup.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    D_801198C0_msetup = -1;
    omAddObj(10000, 0, 0, -1, func_80105C4C_msetup);
    HmfLightMaxSet(3);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(2, 0.0f, 0.0f, 100.0f);
    HmfLightColorSet(3, 240, 240, 240);
    HmfLightDirSet(3, 0.0f, 100.0f, 0.0f);
    HmfLightColorSet(1, 255, 255, 255);
    func_8001F38C_main(16, 16, 240);
    omPrcSetStatBit(omAddPrcObj(func_80106320_msetup, 0x1100, 0x400, 0), 0xA0);
    D_8011A944_msetup = 0;
    func_80106DF8_msetup();
    D_8011A938_msetup = -1;
    switch (omovlevtno) {
        case 0:
            D_8011A938_msetup = 0;
            break;
        case 1:
            D_8011A938_msetup = 1;
            break;
        case 2:
            D_8011A938_msetup = 2;
            break;
        case 3:
            D_8011A938_msetup = 3;
            break;
        case 4:
            D_8011A938_msetup = 4;
            break;
        case 5:
            D_8011A938_msetup = 5;
            break;
        case 6:
            D_8011A938_msetup = 6;
            break;
        case 7:
            D_8011A938_msetup = 7;
            break;
        case 8:
            D_8011A938_msetup = 8;
            break;
    }
    if (D_8011A938_msetup < 0) {
        D_80119410_msetup = 1;
    } else {
        omAddPrcObj(D_8011955C_msetup[D_8011A938_msetup], 0x3F00, 0x1000, 0);
    }
    if (D_8011A938_msetup == 4) {
        WipeColorSet(255, 255, 255);
    } else {
        WipeColorSet(0, 0, 0);
    }
    D_8011AA48_msetup = 11;
    D_8011A93A_msetup = 20;
}

void func_80105C4C_msetup(omObjData *object) {
    s32 i;

    if (D_80119412_msetup != 0) {
        D_80119419_msetup--;
        if (D_80119419_msetup == 0) {
            for (i = 0; i < D_8011AA40_msetup; i++) {
                RepeatVibrator(D_8011AA30_msetup.controllerPorts[i], 5, 0, 5);
            }
            D_80119419_msetup = 10;
        }
    }
    if (D_80119410_msetup == 0) {
        if (D_800D530C_main != 0) {
            goto createWipe;
        }
    } else if (D_80119410_msetup == 1) {
        goto createWipe;
    } else {
        D_80119410_msetup--;
    }
    return;

createWipe:
    if (D_8011A938_msetup == 4) {
        WipeColorSet(255, 255, 255);
        D_8011AA48_msetup = 11;
    } else {
        D_8011AA48_msetup = 2;
    }
    if (D_8011AA48_msetup >= 0) {
        WipeCreateOut(D_8011AA48_msetup, D_8011A93A_msetup);
    }
    if (D_8011A944_msetup == 0) {
        HuAudSeqFadeOut(15);
    }
    object->func = func_80105DB4_msetup;
}

void func_80105DB4_msetup(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        func_8005F524_main();
        func_8010ACB0_msetup();
        flags = 0x14;
        switch (D_8011A944_msetup) {
            case 0:
            default:
                omOvlReturnEx(1);
                break;
            case 2:
                omOvlCallEx(D_8011AA4C_msetup, D_8011A946_msetup, flags);
                break;
            case 1:
                omOvlGotoEx(D_8011AA4C_msetup, D_8011A946_msetup, flags);
                break;
            case 3:
                omOvlGotoEx(D_8011AA4C_msetup, D_8011A946_msetup, 0x4090);
                break;
            case 4:
                omOvlGotoEx(D_8011AA4C_msetup, D_8011A946_msetup, 0x92);
                break;
        }
    }
}

void func_80105E90_msetup(MsetupModelEntry *entry) {
    s32 i;
    s16 model;
    s32 motion;

    for (i = 0; entry->dataId != -1; entry++, i++) {
        model = D_8011A950_msetup[(s16)i] = func_8000B108_main(entry->dataId, entry->flags);
        func_80105F7C_msetup(entry, model);
        motion = D_8011A9A0_msetup[(s16)i] = HmfModelData[model].unk02;
        if (motion != -1) {
            func_8001C814_main(model, -1, entry->motion);
        }
    }
}

void func_80105F7C_msetup(MsetupModelEntry *entry, s16 model) {
    switch (entry->positionMode) {
        case 0:
            break;
        case 1:
            Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
        case 2:
            Hu3DModelPosSet(model, entry->pos.x * 5.0f, entry->pos.y * 5.0f, entry->pos.z * 5.0f);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
    }
}

void func_80106030_msetup(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = func_8000B108_main(entry->dataId, entry->flags);
        func_80105F7C_msetup(entry, model);
        motion = handle->motion = HmfModelData[model].unk02;
        if (motion >= 0) {
            func_8001C814_main(model, -1, entry->motion);
        }
    }
}

u32 func_8010610C_msetup(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed % 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_801061E0_msetup(void) {
    return D_8011941C_msetup = func_8010610C_msetup(D_8011941C_msetup);
}

u32 func_80106208_msetup(u32 limit) {
    u32 random;

    random = D_8011941C_msetup = func_8010610C_msetup(D_8011941C_msetup);
    return (random & 0x7FFFFFFF) % limit;
}

void func_80106260_msetup(MsetupCameraPreset *preset) {
    CRot = preset->rot;
    D_8011A994_msetup = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != D_80119414_msetup) {
        D_80119414_msetup = preset->fov;
        Hu3DCamSetPerspective(0, D_80119414_msetup, D_8011A940_msetup, D_8011A93C_msetup);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106320_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801068F4_msetup);

void func_80106DF8_msetup(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        D_8011AA30_msetup.controllerPorts[i] = 0xFF;
        D_8011AA30_msetup.characters[i] = i;
        D_8011AA30_msetup.cpuDifficulty[i] = 0xFF;
        D_8011AA30_msetup.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_8011AA30_msetup.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_8011AA30_msetup.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (D_8011AA30_msetup.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            D_8011AA30_msetup.controllerPorts[i] = port;
        }
    }
    D_8011AA30_msetup.totalTurns = 0;
    D_8011AA30_msetup.unk16 = 0;
    D_8011AA30_msetup.unk13 = 0;
    D_8011AA30_msetup.connectedCount = connectedCount;
    D_8011AA30_msetup.humanCount = 0;
    D_8011AA30_msetup.cpuCount = 4;
    D_8011AA30_msetup.boardIndex = 0;
    D_8011AA30_msetup.unk17 = 0;
    D_8011A948_msetup = D_8011AA30_msetup.controllerPorts[0];
}

f32 func_80106FC0_msetup(Vec *pos, u32 mask, f32 radius) {
    u32 random;
    f32 angle;

    random = func_801061E0_msetup() & mask;
    pos->y -= (f32)random;
    random = func_801061E0_msetup() & 0x7FFFFFFF;
    if (D_8011AA4A_msetup != 0) {
        random %= 120;
        random += 120;
    } else {
        random %= 360;
    }
    angle = random;
    pos->x = radius * sindf(angle);
    pos->z = radius * cosdf(angle);
    return angle;
}

void func_801070FC_msetup(omObjData *object) {
    MsetupSceneryState *state;
    Vec *pos;
    s32 i;
    u16 model;
    f32 height;

    state = object->data;
    for (i = 0; i < 3; i++) {
        model = object->model[i + 4];
        height = state->upperHeights[i];
        height += 100.0f;
        if (height >= 4000.0f) {
            height -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelRotSet(model, 0.0f, state->rotation, 0.0f);
        state->upperHeights[i] = height;
    }
    state->rotation += 2.0f;
    for (i = 0; i < 3; i++) {
        model = object->model[i + 1];
        height = state->lowerHeights[i];
        height += 60.0f;
        if (height >= 4000.0f) {
            height -= 12000.0f;
        }
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        state->lowerHeights[i] = height;
    }
    for (i = 0; i < 3; i++) {
        model = object->model[i + 7];
        pos = &state->innerPositions[i];
        pos->y += 40.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            func_80106FC0_msetup(pos, 0xFFF, 900.00006103515625f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    for (i = 0; i < 6; i++) {
        model = object->model[i + 10];
        pos = &state->outerPositions[i];
        pos->y += 75.0f;
        if (pos->y > 1000.0f) {
            pos->y -= 12000.0f;
            height = func_80106FC0_msetup(pos, 0xFFF, 906.00006103515625f);
            Hu3DModelRotSet(model, 0.0f, height - 180.0f, 0.0f);
        }
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
}

omObjData *func_80107428_msetup(void) {
    MsetupSceneryState *state;
    omObjData *object;
    Vec *pos;
    s32 i;
    s16 model;
    s16 source;
    f32 height;

    D_8011AA4A_msetup = 0;
    object = omAddObj(0x17D0, 16, 0, -1, func_801070FC_msetup);
    D_80119430_msetup = object;
    if (object == NULL) {
        return NULL;
    }
    object->model[0] = -1;
    state = HuMemAllocTag(sizeof(MsetupSceneryState), 0x7918);
    memset(state, 0, sizeof(MsetupSceneryState));
    object->data = state;
    height = 0.0f;
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = func_8000B108_main(0x140000, 0x2B9);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 4] = model;
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        state->upperHeights[i] = height;
        height -= 4000.0f;
    }
    state->rotation = 0.0f;
    height = state->rotation;
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = func_8000B108_main(0x140004, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 1] = model;
        Hu3DModelPosSet(model, 0.0f, height, 0.0f);
        Hu3DModelScaleSet(model, 1.2f, 2.0f, 1.2f);
        state->lowerHeights[i] = height;
        height -= 4000.0f;
    }
    source = -1;
    for (i = 0; i < 3; i++) {
        if (source < 0) {
            model = func_8000B108_main(0x140002, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 7] = model;
        pos = &state->innerPositions[i];
        pos->y = 0.0f;
        func_80106FC0_msetup(pos, 0x1FFF, 900.00006103515625f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    }
    source = -1;
    for (i = 0; i < 6; i++) {
        if (source < 0) {
            model = func_8000B108_main(0x140005, 0x299);
            source = model;
        } else {
            model = Hu3DModelLink(source);
        }
        object->model[i + 10] = model;
        pos = &state->outerPositions[i];
        pos->y = 0.0f;
        height = func_80106FC0_msetup(pos, 0x1FFF, 906.00006103515625f);
        Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
        Hu3DModelRotSet(model, 0.0f, height - 180.0f, 0.0f);
    }
    return object;
}

s16 func_801077E0_msetup(s16 stateIndex) {
    D_8011A882_msetup.state = 1;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107840_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result != -1) {
        D_8011A990_msetup = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BBF4_msetup(D_8011A880_msetup);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 1;
        }
        while (D_8011A9F2_msetup[3].value != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107964_msetup(s16 stateIndex) {
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 7;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup = 1;
    }
    if (D_8011A882_msetup.result == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BE8C_msetup(D_8011A880_msetup);
    }
    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107A58_msetup(s16 stateIndex) {
    s32 i;

    if (D_8011A882_msetup.result < 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 10;
        }
    }
    D_8011A882_msetup.state = 6;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == 0) {
        D_8011A882_msetup.state = 4;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
        if (D_8011A882_msetup.result >= 0) {
            stateIndex++;
        }
    } else {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011AA3C_msetup[i] = 0;
        }
        if (D_8011A882_msetup.result < 0) {
            stateIndex--;
        } else {
            stateIndex++;
        }
    }
    return stateIndex;
}

s16 func_80107B8C_msetup(s16 stateIndex) {
    s32 i;

    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i].value = 12;
    }
    D_8011A990_msetup = 2;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    D_8011A882_msetup.state = 8;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result < 0) {
        func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 1);
    }
    D_8011A990_msetup = 1;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i].value = 11;
    }
    HuPrcVSleep();
    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107CF4_msetup(s16 stateIndex) {
    D_8011A882_msetup.state = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107D84_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup.state = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }

    if (D_8011A882_msetup.result == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107E48_msetup(s16 stateIndex) {
    D_8011A882_msetup.state = 7;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == 0) {
        D_8011AA43_msetup = 1;
    } else {
        D_8011AA43_msetup = 0;
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107ECC_msetup(s16 stateIndex) {
    D_8011A882_msetup.result = 0;
    func_8010B82C_msetup(0x152D);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x152F);
        stateIndex = -2;
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
    } else {
        func_8010B82C_msetup(0x152E);
        if (func_8010B858_msetup() == 0) {
            func_8010F2F4_msetup(D_80119420_msetup, 9);
            HuAudFXPlay(0x2E4);
            stateIndex = 0;
            func_8010BE8C_msetup(D_8011A880_msetup);
        } else {
            D_8011A882_msetup.result = -1;
            stateIndex--;
        }
    }
    return stateIndex;
}

void func_80107F88_msetup(s16 countdown, s16 pointIndex, s16 frame) {
    if (frame == 0x31) {
        HuAudSeqPlay(9);
    }
}

void func_80107FB4_msetup(void) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    D_8011A880_msetup = 4;
    _ClearFlag(0);
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    process = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(D_8011A882_msetup));
    D_8011A882_msetup.result = -1;
    process->user_data = &D_8011A882_msetup;
    D_80119420_msetup = func_8010F2BC_msetup();
    process = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 16);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(&D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    if (!_CheckFlag(0x1A)) {
        _SetFlag(0x1A);
        func_8010B82C_msetup(0x1500);
        func_8010B858_msetup();
    }
    func_8010B82C_msetup(0x1502);
    func_8010B858_msetup();
    step = 0;
    do {
        step = D_80119434_msetup[step](step);
    } while (step >= 0);
    func_8010F2F4_msetup(D_80119420_msetup, 8);
    D_8011A990_msetup = 0;
    if (step < -1) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 16;
        }
        HuAudSeqFadeOut(390);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(&D_801197BC_msetup, 22.0f, NULL);
        GwSystem.current_board_index = D_8011AA30_msetup.boardIndex;
        GwSystem.total_turns = D_8011AA30_msetup.totalTurns;
        GwSystem.current_game_length = D_8011AA30_msetup.unk16;
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA30_msetup.characters[i];
            GwPlayer[i].star = D_8011AA30_msetup.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.controllerPorts[i];
            if (D_8011AA30_msetup.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA30_msetup.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (D_8011AA30_msetup.unk13 != 0) {
            _SetFlag(0x1B);
        } else {
            _ClearFlag(0x1B);
        }
        if (D_8011AA30_msetup.unk17 != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        D_8011A944_msetup = 4;
        D_8011AA4C_msetup = 71;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 75;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(&D_801196C0_msetup, 25.0f, NULL);
    }
    func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

s16 func_80108464_msetup(s16 stateIndex) {
    D_8011A882_msetup.state = 9;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801084C4_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result != -1) {
        D_8011A990_msetup = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BBF4_msetup(D_8011A880_msetup);
        HuAudFXPlay(0x2DB);
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 1;
        }
        while (D_8011A9F2_msetup[1].value != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801085D4_msetup(s16 stateIndex) {
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 6;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup = 1;
    }
    if (D_8011A882_msetup.result == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BE8C_msetup(D_8011A880_msetup);
    }
    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801086C8_msetup(s16 stateIndex) {
    s32 i;

    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i].value = 14;
    }
    D_8011A882_msetup.state = 11;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == 0) {
        D_8011A882_msetup.state = 10;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
        if (D_8011A882_msetup.result >= 0) {
            stateIndex++;
        }
    } else {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011AA3C_msetup[i] = 5;
        }
        if (D_8011A882_msetup.result < 0) {
            stateIndex--;
        } else {
            stateIndex++;
        }
    }
    return stateIndex;
}

s16 func_801087F4_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup.state = 8;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result < 0) {
        func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 1);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801088A8_msetup(s16 stateIndex) {
    D_8011A882_msetup.state = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80108938_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup.state = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }

    if (D_8011A882_msetup.result == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A882_msetup.result < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801089FC_msetup(s16 stateIndex) {
    D_8011A882_msetup.result = 0;
    func_8010B82C_msetup(0x241B);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x241D);
        stateIndex = -2;
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
    } else {
        func_8010B82C_msetup(0x241C);
        if (func_8010B858_msetup() == 0) {
            func_8010F2F4_msetup(D_80119420_msetup, 9);
            HuAudFXPlay(0x2E4);
            stateIndex = 0;
            func_8010BE8C_msetup(D_8011A880_msetup);
        } else {
            D_8011A882_msetup.result = -1;
            stateIndex--;
        }
    }
    return stateIndex;
}

void func_80108AB8_msetup(void) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    D_8011A880_msetup = 2;
    _ClearFlag(0);
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[1], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    process = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(D_8011A882_msetup));
    D_8011A882_msetup.result = -1;
    process->user_data = &D_8011A882_msetup;
    D_80119420_msetup = func_8010F2BC_msetup();
    process = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA3C_msetup[i] = 5;
    }
    WipeCreateIn(D_8011AA48_msetup, 16);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(&D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    if (!_CheckFlag(0x19)) {
        _SetFlag(0x19);
        func_8010B82C_msetup(0x2400);
        func_8010B858_msetup();
    }
    func_8010B82C_msetup(0x2402);
    func_8010B858_msetup();
    step = 0;
    do {
        step = D_80119458_msetup[step](step);
    } while (step >= 0);
    func_8010F2F4_msetup(D_80119420_msetup, 8);
    D_8011A990_msetup = 0;
    if (step < -1) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 16;
        }
        HuAudSeqFadeOut(390);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(&D_801197BC_msetup, 22.0f, NULL);
        GwSystem.current_board_index = D_8011AA30_msetup.boardIndex;
        GwSystem.total_turns = D_8011AA30_msetup.totalTurns;
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA30_msetup.characters[i];
            GwPlayer[i].star = D_8011AA30_msetup.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.controllerPorts[i];
            if (D_8011AA30_msetup.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA30_msetup.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        if (D_8011AA30_msetup.unk17 != 0) {
            _SetFlag(0x20);
        } else {
            _ClearFlag(0x20);
        }
        D_8011A944_msetup = 3;
        D_8011AA4C_msetup = 90;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 75;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(&D_801196C0_msetup, 25.0f, NULL);
    }
    func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80108F74_msetup(void) {
    u8 characters[4];
    s32 i;
    s32 player;
    s16 mode;
    u8 opponent;
    u8 character;
    u8 stars;
    u32 random;
    u32 first;
    u32 second;

    GwSystem.current_board_index = D_80119478_msetup[GwStory.unk0];
    GwSystem.current_game_length = 0;
    mode = D_80119488_msetup[GwStory.unk0];
    stars = 0;
    if (mode == 1) {
        GwSystem.total_turns = 20;
        stars = 5;
    } else {
        GwSystem.total_turns = 15;
    }
    GwPlayer[0].chr = GwStory.unk1;
    GwPlayer[0].star = stars;
    GwPlayer[0].pad = D_8011A949_msetup;
    GwPlayer[0].cpu_difficulty = 1;
    GwPlayer[0].stat = 0;
    GwPlayer[0].coin = 0;
    opponent = D_80119498_msetup[GwStory.unk0];
    if (opponent == GwStory.unk1) {
        opponent = 1;
    }
    i = 0;
    if (mode == 1) {
        GwPlayer[1].chr = opponent;
        GwPlayer[1].star = stars;
        GwPlayer[1].pad = D_8011AA30_msetup.controllerPorts[1];
        GwPlayer[1].cpu_difficulty = GwStory.unk2;
        GwPlayer[1].stat = 1;
        GwPlayer[1].coin = 0;
    } else {
        character = 0;
        do {
            if (character != GwStory.unk1) {
                if (character != opponent) {
                    characters[i++] = character;
                }
            }
            character++;
        } while (i < 4);
        for (i = 96; i != 0; i--) {
            random = func_801061E0_msetup();
            first = random & 3;
            second = (random >> 2) & 3;
            character = characters[first];
            characters[first] = characters[second];
            characters[second] = character;
        }
        player = 1;
        if (GwStory.unk0 >= 11) {
            GwPlayer[player].chr = opponent;
            GwPlayer[player].star = stars;
            GwPlayer[player].pad = D_8011AA30_msetup.controllerPorts[1];
            GwPlayer[player].cpu_difficulty = GwStory.unk2;
            GwPlayer[player].stat = 1;
            GwPlayer[player].coin = 0;
            player = 2;
        }
        for (i = 0; player < 4; player++, i++) {
            GwPlayer[player].chr = characters[i];
            GwPlayer[player].star = stars;
            GwPlayer[player].pad = D_8011AA30_msetup.controllerPorts[player];
            GwPlayer[player].cpu_difficulty = GwStory.unk2;
            GwPlayer[player].stat = 1;
            GwPlayer[player].coin = 0;
        }
    }
}

void func_80109218_msetup(void) {
    s16 state[2];
    Process *process;
    s32 i;

    D_8011A880_msetup = 4;
    func_80108F74_msetup();
    D_8011AA30_msetup.boardIndex = GwSystem.current_board_index;
    D_8011AA30_msetup.totalTurns = GwSystem.total_turns;
    D_8011AA30_msetup.unk17 = _CheckFlag(0x29);
    for (i = 0; i < D_8011A880_msetup; i++) {
        D_8011AA30_msetup.characters[i] = GwPlayer[i].chr;
        D_8011AA30_msetup.stars[i] = GwPlayer[i].star;
        D_8011AA30_msetup.controllerPorts[i] = GwPlayer[i].pad;
        if (GwPlayer[i].stat & 1) {
            D_8011AA30_msetup.cpuDifficulty[i] = GwPlayer[i].cpu_difficulty;
        } else {
            D_8011AA30_msetup.cpuDifficulty[i] = 0xFF;
        }
    }
    D_8011AA30_msetup.humanCount = 1;
    D_8011AA30_msetup.cpuCount = 3;
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[2], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    process = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(D_8011A882_msetup));
    D_8011A882_msetup.result = -1;
    process->user_data = &D_8011A882_msetup;
    process = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    func_80106260_msetup(&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 16);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(&D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    state[0] = 1;
    HuAudFXPlay(0x2DB);
    D_8011A9F2_msetup[0].value = 1;
    while (state[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B998_msetup();
    func_8010B968_msetup(D_8011AA30_msetup.characters[0] + 0x1C00, 0);
    func_8010B82C_msetup(0x1A00);
    func_8010B858_msetup();
    func_8010B82C_msetup(D_801194A8_msetup[D_8011AA30_msetup.boardIndex]);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A07);
    func_8010B858_msetup();
    func_8010B998_msetup();
    D_8011A990_msetup = 2;
    D_8011A882_msetup.state = 12;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);
    D_8011A990_msetup = 1;
    HuPrcVSleep();
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B82C_msetup(0x1A08);
    func_8010B858_msetup();
    D_8011A990_msetup = 0;
    HuAudFXPlay(0x2DB);
    for (i = 1; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i].value = 1;
    }
    for (i = 7; i != 0; i--) {
        HuPrcVSleep();
    }
    D_8011A9F2_msetup[0].value = 17;
    while (D_8011A9F2_msetup[D_8011A880_msetup - 1].value != 0) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B82C_msetup(0x1A09);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0A);
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0B);
    func_8010B858_msetup();
    if (D_8011AA47_msetup != 0) {
        func_8010B82C_msetup(0x1A10);
    } else {
        func_8010B82C_msetup(0x1A0F);
    }
    func_8010B858_msetup();
    func_8010B82C_msetup(0x1A0C);
    func_8010B858_msetup();
    i = 1;
    do {
        func_8010B82C_msetup(0x1A0D);
        if (func_8010B858_msetup() == 0) {
            func_8010B82C_msetup(0x1A0E);
            func_8010B858_msetup();
            HuAudFXPlay(0x2A6);
            D_8011A990_msetup = 0;
            for (i = 0; i < D_8011A880_msetup; i++) {
                D_8011A9F2_msetup[i].value = 16;
            }
            HuAudSeqFadeOut(390);
            D_80119412_msetup = 1;
            HuAudFXPlay(0x2DF);
            func_801068F4_msetup(&D_801197BC_msetup, 22.0f, NULL);
            _ClearFlag(0);
            _ClearFlag(0x28);
            _SetFlag(0x1B);
            if (D_8011AA47_msetup != 0) {
                _SetFlag(0x20);
            } else {
                _ClearFlag(0x20);
            }
            GwSystem.playMode = 5;
            D_8011A944_msetup = 4;
            D_8011AA4C_msetup = 71;
            D_8011A946_msetup = 0;
            omOvlHisChg(0, 0x7D, 0, 0x4090);
            omovlhisidx++;
            i = 0;
        } else {
            func_8010B82C_msetup(0x1501);
            if (func_8010B858_msetup() == 0) {
                i = 0;
                D_8011A990_msetup = 0;
                D_80119410_msetup = 75;
                HuAudFXPlay(0x2EC);
                func_801068F4_msetup(&D_801196C0_msetup, 25.0f, NULL);
            }
        }
    } while (i != 0);
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109868_msetup);

s16 func_80109EA0_msetup(s16 stateIndex) {
    s16 nextState;

    if (D_8011A882_msetup.result >= 0) {
        func_8010B82C_msetup(0x4900);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4902);
        func_8010B858_msetup();
        nextState = stateIndex + 1;
    } else {
        nextState = stateIndex - 1;
    }
    return nextState;
}

s16 func_80109F04_msetup(s16 stateIndex) {
    s16 nextState;

    if (D_8011A882_msetup.result >= 0) {
        func_8010B968_msetup(D_8011AA30_msetup.characters[0] + 0x1C00, 0);
        func_8010B82C_msetup(0x4A00);
        func_8010B858_msetup();
        func_8010B82C_msetup(0x4A02);
        func_8010B858_msetup();
        nextState = stateIndex + 1;
    } else {
        nextState = stateIndex - 1;
    }
    return nextState;
}

s16 func_80109F7C_msetup(s16 step) {
    s32 i;

    D_8011A882_msetup.state = 2;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup.state != 0);

    if (D_8011A882_msetup.result != -1) {
        D_8011A990_msetup = 0;
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        func_8010BA6C_msetup(1, D_8011A880_msetup);
        for (i = 4; i != 0; i--) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x2DB);
        for (i = 1; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 1;
        }
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
        D_8011A9F2_msetup[0].value = 17;
        while (D_8011A9F2_msetup[D_8011A880_msetup - 1].value != 0) {
            HuPrcVSleep();
        }
    }
    if (D_8011A882_msetup.result < 0) {
        step--;
    } else {
        step++;
    }
    return step;
}

s16 func_8010A10C_msetup(s16 step) {
    s32 i;

    if (D_8011AA41_msetup != 0) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 7;
        }
        D_8011A882_msetup.state = 3;
        do {
            HuPrcVSleep();
        } while (D_8011A882_msetup.state != 0);
    } else {
        D_8011A990_msetup = 1;
    }
    if (D_8011A882_msetup.result == -1) {
        HuAudFXPlay(0x2E4);
        func_8010BC18_msetup(1, D_8011A880_msetup);
    }
    if (D_8011A882_msetup.result < 0) {
        step--;
    } else {
        step++;
    }
    return step;
}

s16 func_8010A204_msetup(s16 step) {
    D_8011A882_msetup.result = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        step = -2;
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            step = 1;
            func_8010BE8C_msetup(D_8011A880_msetup);
        } else {
            D_8011A882_msetup.result = -1;
            step--;
        }
    }
    return step;
}

s16 func_8010A2B0_msetup(s16 step) {
    D_8011A882_msetup.result = 0;
    func_8010B82C_msetup(0x4919);
    if (func_8010B858_msetup() == 0) {
        func_8010B82C_msetup(0x491B);
        step = -2;
        func_8010B858_msetup();
        HuAudFXPlay(0x2A6);
    } else {
        func_8010B82C_msetup(0x491A);
        if (func_8010B858_msetup() == 0) {
            HuAudFXPlay(0x2E4);
            func_8010BC18_msetup(1, D_8011A880_msetup);
            step = 1;
        } else {
            D_8011A882_msetup.result = -1;
            step--;
        }
    }
    return step;
}

void func_8010A35C_msetup(s16 (**steps)(s16)) {
    s16 state[2];
    Process *process;
    s16 step;
    s32 i;

    D_8011A880_msetup = 4;
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[0], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    process = omAddPrcObj(func_80117820_msetup, 0xBB8, 0x1000, 0);
    memset(&D_8011A882_msetup, 0, sizeof(D_8011A882_msetup));
    D_8011A882_msetup.result = -1;
    process->user_data = &D_8011A882_msetup;
    process = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    if (D_8011A938_msetup == 6) {
        func_8010BA6C_msetup(0, 1);
    }
    func_80106260_msetup(&D_80119580_msetup);
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 16);
    D_8011A882_msetup.result = 0;
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(&D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    if (D_8011A938_msetup == 6) {
        HuAudFXPlay(0x2DB);
        D_8011A9F2_msetup[0].value = 1;
    }
    state[0] = 1;
    do {
        HuPrcVSleep();
    } while (state[0] == 1);
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    step = 0;
    do {
        step = steps[step](step);
    } while (step >= 0);
    D_8011A990_msetup = 0;
    if (step < -1) {
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 12;
        }
        HuPrcVSleep();
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 16;
        }
        HuAudSeqFadeOut(390);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(&D_801197BC_msetup, 22.0f, NULL);
        for (i = 0; i < D_8011A880_msetup; i++) {
            GwPlayer[i].chr = D_8011AA30_msetup.characters[i];
            GwPlayer[i].star = D_8011AA30_msetup.stars[i];
            GwPlayer[i].coin = 0;
            GwPlayer[i].pad = D_8011AA30_msetup.controllerPorts[i];
            if (D_8011AA30_msetup.cpuDifficulty[i] < 4) {
                GwPlayer[i].cpu_difficulty = D_8011AA30_msetup.cpuDifficulty[i];
                GwPlayer[i].stat = 1;
            } else {
                GwPlayer[i].cpu_difficulty = 1;
                GwPlayer[i].stat = 0;
            }
        }
        D_8011A944_msetup = 1;
        D_8011AA4C_msetup = 105;
        D_8011A946_msetup = 0;
    } else {
        D_80119410_msetup = 75;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(&D_801196C0_msetup, 25.0f, NULL);
    }
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010A780_msetup(void) {
    func_8010A35C_msetup(D_80119510_msetup);
}

void func_8010A7A0_msetup(void) {
    D_8011AA30_msetup.humanCount = 1;
    D_8011AA30_msetup.cpuCount = 3;
    D_8011AA30_msetup.characters[0] = GwStory.unk1;
    D_8011AA30_msetup.cpuDifficulty[0] = 0xFF;
    func_8010A35C_msetup(D_80119524_msetup);
}

void func_8010A7EC_msetup(s16 mode) {
    s16 state[2];
    Process *process;
    s32 *messages;
    s32 i;
    u8 *controllerPort;
    s32 stars;

    switch (mode) {
        default:
        case 0:
            D_8011A880_msetup = 4;
            D_8011AA30_msetup.humanCount = 1;
            D_8011AA30_msetup.cpuCount = 3;
            D_8011AA30_msetup.characters[0] = 3;
            D_8011AA30_msetup.characters[1] = 2;
            D_8011AA30_msetup.characters[2] = 0;
            D_8011AA30_msetup.characters[3] = 4;
            messages = D_80119534_msetup;
            i = 2;
            break;
        case 1:
            D_8011A880_msetup = 2;
            D_8011AA30_msetup.humanCount = 1;
            D_8011AA30_msetup.cpuCount = 1;
            D_8011AA30_msetup.characters[0] = 0;
            D_8011AA30_msetup.characters[1] = 1;
            messages = D_80119548_msetup;
            i = 1;
            break;
    }
    Hu3DModelPosSet(func_8000B108_main(D_80119424_msetup[i], 0x2B9), 0.0f, -37.5f, 100.0f);
    func_80107428_msetup();
    func_8010E21C_msetup();
    process = omAddPrcObj(func_8010B1F4_msetup, 0x3E8, 0x600, 0);
    memset(state, 0, sizeof(state));
    process->user_data = state;
    func_80106260_msetup(&D_80119580_msetup);
    func_8010BBF4_msetup(D_8011A880_msetup);
    i = 0;
    HuPrcVSleep();
    WipeCreateIn(D_8011AA48_msetup, 16);
    HuAudFXPlay(0x2D8);
    func_801068F4_msetup(&D_801195A0_msetup, 22.0f, func_80107F88_msetup);
    D_8011AA4A_msetup = 1;
    state[0] = 1;
    HuAudFXPlay(0x2DB);
    for (; i < D_8011A880_msetup; i++) {
        D_8011A9F2_msetup[i].value = 1;
    }
    while (state[0] == 1) {
        HuPrcVSleep();
    }
    D_8011A990_msetup = 1;
    func_8010B9B8_msetup(0x4000, 0x4000);
    func_8010B998_msetup();
    for (i = 0; i < 4; i++) {
        func_8010B82C_msetup(messages[i]);
        func_8010B858_msetup();
        if (func_8010BA3C_msetup() & 0x4000) {
            func_8010B82C_msetup(messages[4]);
            if (func_8010B858_msetup() == 0) {
                break;
            }
        }
    }
    if (i < 4) {
        D_8011A990_msetup = 0;
        D_80119410_msetup = 75;
        HuAudFXPlay(0x2EC);
        func_801068F4_msetup(&D_801196C0_msetup, 25.0f, NULL);
    } else {
        HuAudFXPlay(0x2A6);
        D_8011A990_msetup = 0;
        for (i = 0; i < D_8011A880_msetup; i++) {
            D_8011A9F2_msetup[i].value = 16;
        }
        HuAudSeqFadeOut(390);
        D_80119412_msetup = 1;
        HuAudFXPlay(0x2DF);
        func_801068F4_msetup(&D_801197BC_msetup, 22.0f, NULL);
        _ClearFlag(0);
        GwSystem.current_board_index = 6;
        GwSystem.total_turns = 20;
        GwSystem.current_game_length = 0;
        switch (mode) {
            default:
            case 0:
                D_8011A944_msetup = 4;
                D_8011AA4C_msetup = 71;
                D_8011A946_msetup = 0;
                stars = 0;
                break;
            case 1:
                D_8011A944_msetup = 3;
                D_8011AA4C_msetup = 90;
                D_8011A946_msetup = 0;
                stars = 5;
                break;
        }
        for (i = 0; i < D_8011A880_msetup; i++) {
            controllerPort = &D_8011A949_msetup;
            GwPlayer[i].chr = D_8011AA30_msetup.characters[i];
            GwPlayer[i].star = stars;
            GwPlayer[i].pad = *controllerPort;
            GwPlayer[i].cpu_difficulty = 1;
            GwPlayer[i].stat = 1;
            GwPlayer[i].coin = 0;
        }
    }
    D_80119410_msetup = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010AC78_msetup(void) {
    func_8010A7EC_msetup(0);
}

void func_8010AC94_msetup(void) {
    func_8010A7EC_msetup(1);
}

void func_8010ACB0_msetup(void) {
}
