#include "common.h"
#include "overlays/mgmode.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern u8 D_80118EB1_mgmode;
extern u8 D_80118EB2_mgmode;
extern s16 D_80118EB4_mgmode;
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;
extern s16 D_8011B884_mgmode;
extern Gfx D_80119290_mgmode[];
extern s16 D_8011B3E4_mgmode;
extern MgmodeEsprite *D_8011B3EC_mgmode;
extern s16 D_8011B8B2_mgmode;
extern u16 *D_8011B3E0_mgmode;
extern s8 D_8011B3E6_mgmode[];
extern s32 D_80119190_mgmode[];
extern s32 D_801191E4_mgmode[];
extern char D_8011A400_mgmode[];
extern char D_8011A430_mgmode[];
extern char D_8011A708_mgmode[];
extern s16 D_8011B6A0_mgmode;
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B6A8_mgmode;
extern u8 D_800D20B0_main;
extern MgmodeSpaceCoord D_80119158_mgmode[];
extern Vec D_8011AA80_mgmode[][25];
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8C4_mgmode;
extern MgmodeSpaceCoord D_80119170_mgmode[];
extern s16 D_8011B808_mgmode;
extern s16 D_8011B8B4_mgmode;
extern HuMtx4F D_8011A808_mgmode;
extern char D_8011A46C_mgmode[];

void func_8010BD98_mgmode(omObjData *arg0);
void func_80108DDC_mgmode(s16 arg0);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116D4C_mgmode(void);
void func_80118CD8_mgmode(void);
void func_801090C4_mgmode(s16 arg0);
void func_80107D0C_mgmode(s32 mes, s16 x, s16 y);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
s16 func_801182DC_mgmode(s16 stickX, s16 stickY);
void func_80118D0C_mgmode(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801059A0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A400_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A404_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010606C_mgmode);

s16 func_80107298_mgmode(void) {
    s16 count = 0;
    s16 win;
    s16 total;
    s16 remaining;
    s16 size[2];

    if (_CheckFlag(0x1E) && !_CheckFlag(0x2A)) {
        count = 1;
        _SetFlag(0x2A);
    }
    if (D_8011B928_mgmode[0] >= 20 && D_8011B928_mgmode[1] >= 10 && D_8011B928_mgmode[2] >= 10 &&
        D_8011B928_mgmode[3] >= 8 && D_8011B928_mgmode[4] >= 10 && D_8011B928_mgmode[5] >= 6 && !_CheckFlag(0x2B)) {
        count++;
        _SetFlag(0x2B);
    }
    if (_CheckFlag(0x1F) && !_CheckFlag(0x2C)) {
        count++;
        _SetFlag(0x2C);
    }
    if (count == 0) {
        return 0;
    }
    HuWinInsertMesSizeGet((u32)D_8011A400_mgmode, 0);
    HuWinInsertMesSizeGet((u32)D_8011A400_mgmode, 1);
    HuWinMesMaxSizeBetGet(size, 0x570D, 0x5710);
    win = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(win, 1 << D_8011B808_mgmode);
    HuWinMesSet(win, 0x570D, -1, -1);
    HuWinExAnimIn(win);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    if (count == 3) {
        HuWinMesSet(win, 0x570F, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, count);
        HuWinInsertMesSet(win, (u32)D_8011A708_mgmode, 0);
        HuWinMesSet(win, 0x570E, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    remaining = 67 - total;
    if (remaining == 0) {
        HuWinMesSet(win, 0x5711, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
        HuWinInsertMesSet(win, (u32)D_8011A708_mgmode, 0);
        HuWinMesSet(win, 0x5710, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinExAnimOut(win, 0);
    HuWinKill(win);
    func_80118CD8_mgmode();
    return count;
}

void func_80107610_mgmode(void) {
    s32 angle = 0;

    Hu3DModelScaleSet(D_8011B8B2_mgmode, 0.5f, 0.5f, 0.5f);
    while (TRUE) {
        HuPrcVSleep();
        HmfModelData[D_8011B8B2_mgmode].pos.y = sindf(angle) * 20.0f;
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A430_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A434_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A43C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A444_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A44C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A454_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A45C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A464_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A46C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801076B0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A484_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A490_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A49C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107D0C_mgmode);

void func_80108824_mgmode(s32 arg0) {
    s16 total;
    s16 choice;
    s16 i;
    HmfMotionNode *node;

    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    if (total < 0) {
        total = 0;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
    HuWinInsertMesSet(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    if (arg0 == 0) {
        HuWinMesSet(D_8011B6A0_mgmode, 0x570B, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
        HuWinMesSet(D_8011B6A0_mgmode, 0x5712, -1, -1);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
    } else {
        HuWinMesSet(D_8011B6A0_mgmode, 0x5712, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
    }
    choice = HuWinChoiceGet(D_8011B6A0_mgmode, 0, 0);
    HuWinExAnimOut(D_8011B6A0_mgmode, 0);
    if (choice == -1) {
        HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
        HuWinExAnimIn(D_8011B6A8_mgmode);
        func_801182B4_mgmode(1);
        return;
    }
    if (choice == 0) {
        func_801182B4_mgmode(0);
        func_80116ED4_mgmode(2, 10, 1, (void (*)(s16 *))-1);
        HuWinMesSet(D_8011B6A0_mgmode, 0x5713, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
        func_80108DDC_mgmode(0);
    } else if (choice == 1) {
        func_801182B4_mgmode(0);
        node = func_8001D33C_main(D_8011B8B4_mgmode, D_8011A46C_mgmode);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(node->unk58, D_8011A808_mgmode);
            func_80017D24_main(node->unk58, 0.0f, sindf(i * 9) * 117.0f, 0.0f);
        }
        func_80116ED4_mgmode(6, 10, 1, (void (*)(s16 *))-1);
        func_80107D0C_mgmode(0x12000F, 160, 120);
        func_80116ED4_mgmode(1, 10, 1, (void (*)(s16 *))-1);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(node->unk58, D_8011A808_mgmode);
            func_80017D24_main(node->unk58, 0.0f, (1.0f - sindf(i * 9)) * 117.0f, 0.0f);
        }
    }
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
}

void func_80108C88_mgmode(void) {
    HuWinDispOn(D_8011B6A0_mgmode);
    func_80108DDC_mgmode(D_800D20B0_main);
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
}

void func_80108CF4_mgmode(s16 arg0) {
    s32 mesOffset;

    mesOffset = (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) ? 7 : 0;
    if (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] == D_8011B940_mgmode[D_801191E4_mgmode[arg0]]) {
        mesOffset = 14;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, D_8011B928_mgmode[D_801191E4_mgmode[arg0]]);
    HuWinInsertMesSet(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    HuWinMesSet(D_8011B6A0_mgmode, D_80119190_mgmode[mesOffset + arg0], -1, -1);
}

void func_80108DDC_mgmode(s16 arg0) {
    s16 next;

    func_80108CF4_mgmode(arg0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8011822C_mgmode(D_80119170_mgmode);
    func_801181F4_mgmode(arg0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    HuPrcSleep(5);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            HuPrcSleep(5);
            func_80108CF4_mgmode(next);
            arg0 = next;
        } else if ((D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) && D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) {
            HuAudFXPlay(2);
            func_801182B4_mgmode(0);
            HuWinExAnimOut(D_8011B6A0_mgmode, 0);
            func_80116ED4_mgmode(arg0 + 7, 15, 1, (void (*)(s16 *))-1);
            func_801090C4_mgmode(arg0);
            func_80116ED4_mgmode(2, 15, 1, (void (*)(s16 *))-1);
            func_8011822C_mgmode(D_80119170_mgmode);
            func_801181F4_mgmode(arg0);
            func_8011829C_mgmode(5);
            func_801182B4_mgmode(1);
            func_80108CF4_mgmode(arg0);
            HuWinExAnimIn(D_8011B6A0_mgmode);
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            func_801182B4_mgmode(0);
            HuWinExAnimOut(D_8011B6A0_mgmode, 0);
            func_80116ED4_mgmode(1, 10, 1, (void (*)(s16 *))-1);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801090C4_mgmode);

void func_80109C10_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    f32 x;
    f32 z;
    f32 dist;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    func_8001C258_main(model, 4, 0);
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    Hu3DModelPosSet(model, x + D_8011AA80_mgmode[arg0][arg1].x, D_8011AA80_mgmode[arg0][arg1].y - 3.0f,
                    z + D_8011AA80_mgmode[arg0][arg1].z);
}

void func_80109DBC_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    s16 i;
    f32 x;
    f32 z;
    f32 dist;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 rotX;
    f32 t;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    rotX = 15.0f;
    startX = x + D_8011AA80_mgmode[arg0][arg1].x;
    startY = D_8011AA80_mgmode[arg0][arg1].y - 3.0f;
    startZ = z + D_8011AA80_mgmode[arg0][arg1].z;
    endX = Center.x + sindf(CRot.y) * cosdf(CRot.x) * CZoom - 50.0f;
    endY = Center.y + -sindf(CRot.x) * CZoom;
    endZ = Center.z + cosdf(CRot.y) * cosdf(CRot.x) * CZoom;
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (i == 20) {
            WipeCreateOut(11, 10);
        }
        t = i / 30.0f * 0.5f;
        Hu3DModelPosSet(model, startX + (endX - startX) * t, startY + (endY - startY) * t,
                        startZ + (endZ - startZ) * t);
        Hu3DModelRotSet(model, rotX, CRot.y - i * 3, 0.0f);
        rotX -= 3.0f;
        if (rotX < 0.0f) {
            rotX = 0.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A148_mgmode);

void func_8010A5F0_mgmode(void) {
    func_801168E0_mgmode(D_8011B3EC_mgmode);
    HuWinExAnimOut(D_8011B3E4_mgmode, 0);
    HuWinKill(D_8011B3E4_mgmode);
}

void func_8010A62C_mgmode(s32 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i], arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i] + 10, arg0 + D_8011B3E0_mgmode[i] - 0x54,
                             arg1 + 0x1E);
        func_80116968_mgmode(D_8011B3EC_mgmode, i + 4, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        if (GwPlayer[D_8011B3E6_mgmode[i]].stat & 1) {
            func_801169A0_mgmode(D_8011B3EC_mgmode, i + 14);
            func_80116968_mgmode(D_8011B3EC_mgmode, i + 14, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1 + 0xE);
        } else {
            func_801169C8_mgmode(D_8011B3EC_mgmode, i + 14);
        }
    }
}

void func_8010A824_mgmode(s32 arg0, s32 arg1) {
    s32 offset = 0x54;

    func_80116968_mgmode(D_8011B3EC_mgmode, 18, D_8011B3E0_mgmode[4] + (arg0 - offset), arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 8, D_8011B3E0_mgmode[0] + arg0 - 0x70, arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 9, D_8011B3E0_mgmode[3] + arg0 - 0x38, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A8E4_mgmode);

void func_8010AF78_mgmode(Gfx **arg0, s32 arg1, s32 arg2) {
    if (D_8011B884_mgmode != 0) {
        gDPSetDepthImage((*arg0)++, 0x3D0800);
        gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*arg0)++, D_80119290_mgmode);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010AFEC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010B574_mgmode);

void func_8010BD28_mgmode(omObjData *arg0) {
    if ((D_80118EB1_mgmode != 0) || (D_800D530C_main != 0)) {
        if ((D_80118EB4_mgmode & 0x80) == 0) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        arg0->func = func_8010BD98_mgmode;
    }
}

void func_8010BD98_mgmode(omObjData *arg0) {
    if (WipeStatGet() != 0) {
        return;
    }
    HuWinAllKill();
    if (D_80118EB2_mgmode != 0) {
        func_80118CD8_mgmode();
    }
    func_80116D4C_mgmode();
    D_80118EB4_mgmode &= 0xF;
    _ClearFlag(0x1C);
    if (D_80118EB4_mgmode == 0) {
        omOvlReturnEx(1);
    } else if (D_80118EB4_mgmode == 2) {
        if (D_8011B95A_mgmode == 0x68) {
            _SetFlag(0x1C);
        }
        if (D_8011B95A_mgmode == 0x70) {
            _SetFlag(0x1C);
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
        } else {
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x84);
        }
    } else {
        omOvlGotoEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
    }
}
