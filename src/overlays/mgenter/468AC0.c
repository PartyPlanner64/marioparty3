#include "common.h"

extern s16 D_800D1FE0_main;
extern u16 D_80109AA4_mgenter;
extern s16 D_80109AA6_mgenter;
extern s16 D_80109B20_mgenter;
extern s16 D_80109B34_mgenter;
extern s16 D_80109B36_mgenter;
extern s16 D_80109B38_mgenter;
extern s16 D_80109B3A_mgenter;
extern s16 D_80109B76_mgenter;
extern s16 D_80109B7C_mgenter;
extern s16 D_80109B98_mgenter;

void func_801089A0_mgenter(omObjData *);
void func_80109820_mgenter(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801059D0_mgenter);

void func_80105C60_mgenter(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0x19);
    omOvlHisChg(0, 0x68, 0, 4);
    omOvlCallEx(0x70, 0, 2);
    _SetFlag(0xD);
    D_800D1FE0_main++;
}

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

void func_80107E5C_mgenter(s16 winId, s16 value, u8 *buf) {
    s16 i;

    sprintf((char *)buf, "%04d", value);
    if (buf[0] == '0') {
        buf[0] = 0x1A;
    }
    for (i = 0; i < 4; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            buf[i] += 0x70;
        }
    }
    HuWinInsertMesSet(winId, (u32)buf, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80107F0C_mgenter);

void func_80108560_mgenter(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80109B34_mgenter = arg0;
    D_80109B36_mgenter = arg2;
    D_80109B38_mgenter = arg1;
    D_80109B3A_mgenter = arg3;
    D_80109B20_mgenter = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_80108590_mgenter);

INCLUDE_ASM("asm/nonmatchings/overlays/mgenter/468AC0", func_801087C0_mgenter);

void func_80108934_mgenter(omObjData *obj) {
    if ((D_80109AA4_mgenter != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        if (D_80109AA6_mgenter == 0) {
            HuAudSeqFadeOut(0x3C);
        }
        obj->func = func_801089A0_mgenter;
    }
}

void func_801089A0_mgenter(omObjData *obj) {
    if (WipeStatGet() != 0) {
        return;
    }
    func_80109820_mgenter();
    HuWinAllKill();
    switch (D_80109B7C_mgenter) {
        case 0:
            omOvlReturnEx(1);
            break;
        case 2:
            omOvlCallEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
            break;
        case 1:
            omOvlGotoEx(D_80109B76_mgenter, D_80109B98_mgenter, 0x111);
            break;
    }
}
