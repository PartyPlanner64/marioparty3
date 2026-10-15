#include "common.h"

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

extern Process *D_80119420_msetup;
extern s32 D_80119E94_msetup[];
extern s32 D_80119EAC_msetup[];
extern s32 D_80119EC4_msetup[];
extern s32 D_80119EE0_msetup[];
extern s16 D_8011A882_msetup;
extern s16 D_8011A886_msetup;
extern s16 D_8011A938_msetup;
extern s16 D_8011A948_msetup;
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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801059A0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105C4C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105DB4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80105E90_msetup);

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

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106030_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_8010610C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801061E0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106208_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106260_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106320_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801068F4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106DF8_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80106FC0_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801070FC_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107428_msetup);

s16 func_801077E0_msetup(s16 stateIndex) {
    D_8011A882_msetup = 1;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107840_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107964_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107A58_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_80107B8C_msetup);

s16 func_80107CF4_msetup(s16 stateIndex) {
    D_8011A882_msetup = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107D84_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }

    if (D_8011A886_msetup == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80107E48_msetup(s16 stateIndex) {
    D_8011A882_msetup = 7;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup == 0) {
        D_8011AA43_msetup = 1;
    } else {
        D_8011AA43_msetup = 0;
    }

    if (D_8011A886_msetup < 0) {
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
    D_8011A882_msetup = 9;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801084C4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801085D4_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/501C00", func_801086C8_msetup);

s16 func_801087F4_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup = 8;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup < 0) {
        func_8010F2F4_msetup(D_80119420_msetup, 0xFF);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 1);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_801088A8_msetup(s16 stateIndex) {
    D_8011A882_msetup = 5;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 3);
    } else {
        func_8010F2F4_msetup(D_80119420_msetup, 4);
    }

    if (D_8011A886_msetup < 0) {
        stateIndex--;
    } else {
        stateIndex++;
    }
    return stateIndex;
}

s16 func_80108938_msetup(s16 stateIndex) {
    s32 i;

    D_8011A882_msetup = 13;
    do {
        HuPrcVSleep();
    } while (D_8011A882_msetup != 0);

    if (D_8011A886_msetup == 0) {
        D_8011AA47_msetup = 0;
    } else {
        D_8011AA47_msetup = 1;
    }

    if (D_8011A886_msetup == -1) {
        func_8010F2F4_msetup(D_80119420_msetup, 6);
        for (i = 7; i != 0; i--) {
            HuPrcVSleep();
        }
    }

    if (D_8011A886_msetup < 0) {
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
