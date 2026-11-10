#include "common.h"

extern s32 D_80114A84_mstory1;
extern s32 D_801158B4_mstory1;
extern s32 D_80115CB0_mstory1[4];
extern void (*const D_80114C40_mstory1[])(void);
extern const s32 D_80114C4C_mstory1[];

void func_80105C90_mstory1(omObjData *obj);
void func_80105D80_mstory1(omObjData *obj);
void func_80105E00_mstory1(void);
void func_80105F28_mstory1(omObjData *obj);

void func_801059A0_mstory1(void) {
    omObjData *obj;
    s16 chapter;
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                D_80115CB0_mstory1[count] = i;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }
    func_800142A0_main(60);
    omInitObjMan(30, 30);
    HuWinInit();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_80105F28_mstory1);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80105F28_mstory1(obj);
    omAddObj(0, 0, 0, -1, func_80105C90_mstory1);
    omAddObj(0, 0, 0, -1, func_80105D80_mstory1);
    func_80105E00_mstory1();
    for (D_801158B4_mstory1 = 0; D_801158B4_mstory1 < 4; D_801158B4_mstory1++) {
        if (CheckControllerRead(D_801158B4_mstory1)) {
            break;
        }
    }
    if (D_801158B4_mstory1 >= 4) {
        D_801158B4_mstory1 = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 3) {
        chapter = 2;
    }
    D_80114C40_mstory1[chapter]();
    if (_CheckFlag(D_80114C4C_mstory1[chapter])) {
        D_80114A84_mstory1 = 1;
    } else {
        _SetFlag(D_80114C4C_mstory1[chapter]);
    }
    WipeCreateIn(2, 16);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48BE30", D_80114C40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48BE30", D_80114C4C_mstory1);
