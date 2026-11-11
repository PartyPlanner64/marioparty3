#include "common.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/wipe.h"
#include "overlays/minigame.h"

extern u8 D_800CE20A_main;
extern u8 D_800D6A90_main;

extern s32 D_8010A010_picture_imperfect;
extern s8 D_8010A014_picture_imperfect;
extern D_80111B50_vine_with_me_Struct D_8010A128_picture_imperfect;
extern u8 D_8010A150_picture_imperfect;
extern u8 D_8010A151_picture_imperfect;
extern s16 D_8010A230_picture_imperfect;
extern s16 D_8010A232_picture_imperfect[5];
extern s16 D_8010A23C_picture_imperfect[5];
extern s16 D_8010A246_picture_imperfect[5];
extern s16 D_8010A250_picture_imperfect[5];
extern s16 D_8010A25A_picture_imperfect[5];
extern s16 D_8010A264_picture_imperfect;
extern s16 D_8010A266_picture_imperfect;
extern s16 D_8010A268_picture_imperfect;
extern s16 D_8010A26A_picture_imperfect;
extern s16 D_8010A26C_picture_imperfect;

void func_80105BA8_picture_imperfect(void);
void func_80105E68_picture_imperfect(D_80111B50_vine_with_me_Struct *arg0);
void func_80105EF4_picture_imperfect(void);
void func_80106154_picture_imperfect(omObjData *object);
void func_8010629C_picture_imperfect(omObjData *object);
void func_80109608_picture_imperfect(omObjData *object);

void func_801059A0_picture_imperfect(void) {
    omObjData *object;
    s32 i;

    func_8001FE20_main(0x20);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105EF4_picture_imperfect();
    D_8010A150_picture_imperfect = 2 - D_800CE20A_main;
    func_80105BA8_picture_imperfect();
    func_80105E68_picture_imperfect(&D_8010A128_picture_imperfect);
    func_800E5EA0_minigame(&D_8010A128_picture_imperfect);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    D_8010A151_picture_imperfect = rand8() >> 6;
    object = omAddObj(0, 0, 0, -1, func_80106154_picture_imperfect);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(0, 1, 0, -1, func_80109608_picture_imperfect);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(1, 4, 60, -1, func_8010629C_picture_imperfect);
        omSetStatBit(D_800EC598_minigame[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->work[0] = 4;
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105BA8_picture_imperfect(void) {
    s32 i;

    switch (D_8010A150_picture_imperfect) {
        case 0:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0005);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 14) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 19) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 24) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = func_8000B838_main((i + 29) | 0x3F0000);
                D_8010A25A_picture_imperfect[i] = func_8000B838_main((i + 34) | 0x3F0000);
            }
            break;
        case 1:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0006);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 39) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 44) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 49) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = func_8000B838_main((i + 54) | 0x3F0000);
            }
            break;
        case 2:
        default:
            D_8010A230_picture_imperfect = func_8000B838_main(0x3F0007);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = func_8000B838_main((i + 59) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = func_8000B838_main((i + 64) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = func_8000B838_main((i + 69) | 0x3F0000);
            }
            break;
    }
    D_8010A264_picture_imperfect = func_8000B838_main(0x40001C);
    D_8010A266_picture_imperfect = func_8000B838_main(0x40001B);
    D_8010A268_picture_imperfect = func_8000B838_main(0x40001D);
    D_8010A26A_picture_imperfect = func_8000B838_main(0x2E);
    D_8010A26C_picture_imperfect = func_8000B838_main(0x3E0019);
}

void func_80105E68_picture_imperfect(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 10;
    arg0->unk00 = 0;
    arg0->unk01 = 0;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 9;
    arg0->unk1C = -1;
    arg0->unk1E = 1800;
    arg0->unk20 = -1;
    arg0->unk22 = 360;
    arg0->unk24 = 162;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105EF4_picture_imperfect(void) {
    s32 i;

    func_8000B710_main(4);
    func_8000B5F0_main(4);
    for (i = 0; i < 4; i++) {
        CenterM[i].x = -200.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = CRotM[i].y = CRotM[i].z = 0.0f;
        CZoomM[i] = 2100.0f;
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 120.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 120.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 0.0f, 120.0f, 160.0f, 240.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 160.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
}

void func_80106154_picture_imperfect(omObjData *object) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_8010A014_picture_imperfect == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            func_800E6F0C_minigame(5);
            D_8010A014_picture_imperfect = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 49;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010A010_picture_imperfect == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    GameMesStub();
                    omOvlReturnEx(1);
                }
                D_8010A010_picture_imperfect++;
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_8010629C_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80107820_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_801081E4_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_801083C0_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108688_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108A64_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80108C20_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109284_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109608_picture_imperfect);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1E_picture_imperfect/1EF420", func_80109AC4_picture_imperfect);
