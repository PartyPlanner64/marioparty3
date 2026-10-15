#include "common.h"
#include "game/vibrator.h"
#include "overlays/msetup.h"

typedef s16 Array2D[2][18];

typedef struct UnkStarLift {
    char unk_00[0x04];
    s16 unk4;
} UnkStarLift;

typedef struct MsetupModelEntry {
    s32 dataId;
    s32 flags;
    s16 unk08;
    s16 motion;
    u32 positionMode;
    Vec pos;
    Vec rot;
} MsetupModelEntry;

typedef struct MsetupModelHandle {
    s16 model;
    s16 motion;
} MsetupModelHandle;

typedef struct MsetupCameraPreset {
    Vec rot;
    Vec center;
    f32 zoom;
    f32 fov;
} MsetupCameraPreset;

extern u16 D_80119410_msetup;
extern s16 D_80119412_msetup;
extern u8 D_80119419_msetup;
extern u8 D_8011AA30_msetup[];
extern u8 D_8011AA40_msetup;
extern s16 D_8011AA48_msetup;
extern s16 D_8011A93A_msetup;
extern s16 D_8011A944_msetup;
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
void func_8010B858_msetup();
void func_8010B998_msetup();
void func_8010B9B8_msetup(s32, s32);
s32 func_8010D684_msetup(s16, s16 *);
void func_8010DDD8_msetup(void *);
omObjData *func_8010DE38_msetup(s32, s32, s32);
void func_8010E4BC_msetup(Array2D *, s32, s32);
void func_8010E4D8_msetup(Array2D *, s32);
void func_8010E8C8_msetup(Array2D *, s32, s32, f32, f32, f32, f32, s32);
void func_8010F320_msetup(Process *, s16, s16, s16);
s16 func_8010F2F4_msetup(Process *, s16);
s32 _CheckFlag(s32);            /* extern */
s16 func_80055810_main(void *); /* extern */
s32 func_80113ED4_msetup(UnkStarLift *arg0);
void func_80107F88_msetup(s16, s16, s16);
void func_80105F7C_msetup(MsetupModelEntry *, s16);
void func_80105DB4_msetup(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801059A0_msetup);

void func_80105C4C_msetup(omObjData *object) {
    s32 i;

    if (D_80119412_msetup != 0) {
        D_80119419_msetup--;
        if (D_80119419_msetup == 0) {
            for (i = 0; i < D_8011AA40_msetup; i++) {
                RepeatVibrator(D_8011AA30_msetup[i], 5, 0, 5);
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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105DB4_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106DF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106FC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801070FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107428_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107840_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107964_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107ECC_msetup);

void func_80107F88_msetup(s16 countdown, s16 pointIndex, s16 frame) {
    if (frame == 0x31) {
        HuAudSeqPlay(9);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107FB4_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801084C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801085D4_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801089FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108AB8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80108F74_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109218_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109868_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109EA0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109F04_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80109F7C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A10C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A204_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A2B0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A35C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A780_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A7A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010A7EC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010AC78_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010AC94_msetup);

void func_8010ACB0_msetup(void) {
}
