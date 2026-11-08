#include "common.h"
#include "overlays/mgmode.h"
#include "gcc/memory.h"

extern s16 D_8011B818_mgmode[28];
extern s16 D_8011B830_mgmode[16];
extern s16 D_8011B850_mgmode[16];
extern u8 *D_8011B610_mgmode[3];
extern s16 D_8011B61C_mgmode;
extern s16 D_8011B61E_mgmode;
extern MgmodeEsprite *D_801194C0_mgmode;
extern s16 D_801194C4_mgmode;
extern MgmodeEsprite *D_801195D0_mgmode;
extern MgmodeEspriteDef D_8011A270_mgmode[];
extern s16 D_8011B8A8_mgmode[];

void func_80115BB8_mgmode(s16 value);
void func_80115CAC_mgmode(s16 value);
void func_80115CDC_mgmode(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits);
MgmodeEsprite *func_80116794_mgmode(MgmodeEspriteDef *defs);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void func_80116AA8_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2);
void func_80116024_mgmode(void);
void func_80116260_mgmode(void);
void func_801160A0_mgmode(s16 arg0);
void func_80116D4C_mgmode(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112200_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112CF4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80112F98_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80113204_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801134C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801136EC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114048_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801141EC_mgmode);

void func_80114344_mgmode(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_801194C0_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_801194C0_mgmode);
    D_801194C0_mgmode = (MgmodeEsprite *)-1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114404_mgmode);

void func_80114614_mgmode(s16 index) {
    while (Hu3DMotionShiftTimeGet(D_8011B8A8_mgmode[index]) != -1.0f ||
           HmfModelData[D_8011B8A8_mgmode[index]].motTime <
               D_800CCF58_main[HmfModelData[D_8011B8A8_mgmode[index]].motId].unk02) {
        HuPrcVSleep();
    }
}

void func_801146D8_mgmode(void) {
    s16 i;
    s16 j;
    f32 scale;

    for (i = 0; i < 10; i++) {
        scale = 1.0f - i / 10.0f;
        for (j = 1; j < 21; j++) {
            func_80116A48_mgmode(D_801194C0_mgmode, j, scale, scale);
        }
        HuPrcVSleep();
    }
    for (j = 1; j < 21; j++) {
        func_801169C8_mgmode(D_801194C0_mgmode, j);
        func_80116A48_mgmode(D_801194C0_mgmode, j, 1.0f, 1.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114804_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801149F4_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114C80_mgmode);

void func_80114EBC_mgmode(void) {
    s16 i;
    s16 tpLvl;

    for (i = 0; i < 10; i++) {
        tpLvl = (1.0f - i / 10.0f) * 255.0f;
        espTPLvlSet(D_801194C4_mgmode, tpLvl);
        func_801160A0_mgmode(tpLvl);
        HuPrcVSleep();
    }
    func_80116024_mgmode();
    func_80116D4C_mgmode();
    D_801194C4_mgmode = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80114FA0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801152C0_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115590_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115848_mgmode);

void func_80115A9C_mgmode(s16 x, s16 y, s16 value) {
    s16 left;
    s16 i;

    left = x - 40;
    func_80116968_mgmode(D_801194C0_mgmode, 0xF, left, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 0xF);
    func_80116968_mgmode(D_801194C0_mgmode, 0x10, x - 24, y);
    func_801169A0_mgmode(D_801194C0_mgmode, 0x10);
    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_801194C0_mgmode, i + 0x11, left + (i + 2) * 16, y);
    }
    func_80115BB8_mgmode(value);
}

void func_80115BB8_mgmode(s16 value) {
    func_80115CDC_mgmode(D_801194C0_mgmode, 0x11, value, 4);
}

void func_80115BE8_mgmode(void) {
    s16 i;

    func_801169C8_mgmode(D_801194C0_mgmode, 0xF);
    func_801169C8_mgmode(D_801194C0_mgmode, 0x10);

    for (i = 0; i < 4; i++) {
        func_801169C8_mgmode(D_801194C0_mgmode, i + 0x11);
    }
}

void func_80115C5C_mgmode(s16 value) {
    if (D_801195D0_mgmode == (MgmodeEsprite *)-1) {
        D_801195D0_mgmode = func_80116794_mgmode(D_8011A270_mgmode);
        func_80115CAC_mgmode(value);
    }
}

void func_80115CAC_mgmode(s16 value) {
    func_80115CDC_mgmode(D_801195D0_mgmode, 2, value, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/479470", D_8011A688_mgmode);

void func_80115CDC_mgmode(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits) {
    u8 buf[8];
    s16 offset;
    s16 i;

    if (value >= 10000) {
        value = 9999;
    }
    sprintf((char *)buf, "%4d", value);
    offset = 4 - digits;
    for (i = 0; i < digits; i++) {
        if (buf[offset + i] < '0') {
            func_801169C8_mgmode(sprites, base + i);
        } else {
            func_801169A0_mgmode(sprites, base + i);
            func_80116AA8_mgmode(sprites, base + i, buf[offset + i] & 0xF);
        }
    }
}

void func_80115E20_mgmode(void) {
    func_801168E0_mgmode(D_801195D0_mgmode);
    D_801195D0_mgmode = (MgmodeEsprite *)-1;
}

void func_80115E4C_mgmode(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        D_8011B850_mgmode[i] = D_8011B830_mgmode[i] = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_80115E9C_mgmode);

void func_80116024_mgmode(void) {
    s16 i;

    if (D_8011B830_mgmode[0] != GMES_ID_NONE) {
        GMesSprKill((GAMEMES *)((u8 *)D_8011B830_mgmode - offsetof(GAMEMES, strGId)));
        for (i = 0; i < 16; i++) {
            D_8011B850_mgmode[i] = D_8011B830_mgmode[i] = GMES_ID_NONE;
        }
    }
}

void func_801160A0_mgmode(s16 arg0) {
    int i;

    i = 0;
    if (D_8011B818_mgmode[0] > 0) {
        do {
            i++;
            HuSprTPLvlSet(D_8011B818_mgmode[12], (s16)i, arg0);
        } while ((s16)i < D_8011B818_mgmode[0]);
    }
}

void func_8011611C_mgmode(void) {
    HuSprite *sprite;

    D_8011B61C_mgmode = func_8000B838_main(0x12003D);
    D_8011B61E_mgmode = HuSprGrpCreate(5, 0);
    HuSprGrpMemberSet(D_8011B61E_mgmode, 0, D_8011B61C_mgmode, 0);
    HuSprAttrReset(D_8011B61E_mgmode, 0, 0xFFFF);
    HuSprAttrSet(D_8011B61E_mgmode, 0, 0x9008);
    HuSprPosSet(D_8011B61E_mgmode, 0, 160, 120);
    HuSprPriSet(D_8011B61E_mgmode, 0, 15);
    HuSprScaleSet(D_8011B61E_mgmode, 0, 1.0f, 2.0f);
    sprite = HuSprGet(D_8011B61E_mgmode, 0);
    HuMemFree(sprite->unk_84->unk00->unk00);
    D_8011B610_mgmode[0] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[1] = HuMemAllocTag(0x4B00, 0x7918);
    D_8011B610_mgmode[2] = HuMemAllocTag(0x4B00, 0x7918);
    sprite->unk_84->unk00->unk00 = D_8011B610_mgmode[0];
    func_80116260_mgmode();
}

void func_80116260_mgmode(void) {
    memset(D_8011B610_mgmode[0], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[1], 0xFF, 0x4B00);
    memset(D_8011B610_mgmode[2], 0xFF, 0x4B00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/479470", func_801162B4_mgmode);
