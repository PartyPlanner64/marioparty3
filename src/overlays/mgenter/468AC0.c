#include "common.h"

extern u16 D_80109AA4_mgenter;
extern s16 D_80109AA6_mgenter;

void func_801089A0_mgenter(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801059D0_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80105C60_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80105CD8_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106294_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106568_mgenter);

void func_80106710_mgenter(u8 *str) {
    u8 *dst = str;
    u8 *src = str;
    u32 c;

    while (*src != '\0') {
        *dst = *src;
        c = *src;
        if (c >= 0x20 || c == 0x10) {
            dst++;
        } else if (c == 0x20 || c == 0x11) {
            dst++;
        } else {
            src++;
            continue;
        }
        src++;
    }
    *dst = '\0';
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_8010677C_mgenter);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC0_mgenter);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgenter/468AC0", D_80109AC4_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80106BD0_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801079B4_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80107E5C_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80107F0C_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80108560_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80108590_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801087C0_mgenter);

void func_80108934_mgenter(omObjData *obj) {
    if ((D_80109AA4_mgenter != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(0, 8);
        if (D_80109AA6_mgenter == 0) {
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = func_801089A0_mgenter;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801089A0_mgenter);
