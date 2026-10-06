#include "common.h"

typedef struct UnkCrazyCogsCog { // 0x84 bytes, one entry per cog slot
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ u16 timer;
    /* 0x06 */ u8 unk_06[0x7E];
} UnkCrazyCogsCog;

extern s8 D_8010B990_crazy_cogs;
extern s16 D_8010B994_crazy_cogs;
extern s16 D_8010B99E_crazy_cogs;
extern f32 D_8010B9A8_crazy_cogs;
extern s8 D_8010B9B0_crazy_cogs[50];
extern s8 D_8010B9E2_crazy_cogs;
extern s8 D_8010B9E3_crazy_cogs[13];
extern omObjData *D_8010B9F0_crazy_cogs;
extern omObjData *D_8010BA74_crazy_cogs;
extern omObjData *D_8010BAF8_crazy_cogs;
extern omObjData *D_8010BB7C_crazy_cogs;
extern UnkCrazyCogsCog D_8010C8E4_crazy_cogs[];
extern omObjData *D_8010C5CC_crazy_cogs;
extern omObjData *D_8010C650_crazy_cogs;
extern f32 D_8010DE14_crazy_cogs;
extern s16 D_8010DE22_crazy_cogs;
extern s8 D_8010DE60_crazy_cogs;
extern s8 D_8010DE6A_crazy_cogs[4];

void func_80106270_crazy_cogs(omObjData *);
void func_80106688_crazy_cogs(omObjData *);
void func_8010683C_crazy_cogs(omObjData *);
void func_801069DC_crazy_cogs(omObjData *);
void func_8010A67C_crazy_cogs(omObjData *);
void func_8010AA10_crazy_cogs(omObjData *);
void func_8010AE08_crazy_cogs(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801059A0_crazy_cogs);

f32 func_801059BC_crazy_cogs(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80105A3C_crazy_cogs);

void func_80105B04_crazy_cogs(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

s32 func_80105B7C_crazy_cogs(s32 arg0) {
    return rand8() % arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80105BD0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80105E4C_crazy_cogs);

void func_80106034_crazy_cogs(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_801060A0_crazy_cogs(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        func_8001C624_main(arg0->model[0], HmfModelData[arg0->motion[arg1]].unk02, arg2, arg3, arg4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010611C_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B8F0_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B8F8_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B904_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B90C_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B918_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801061CC_crazy_cogs);

void func_80106268_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106270_crazy_cogs);

void func_801063DC_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs = omAddObj(0x1F4, 1, 0, -1, func_80106270_crazy_cogs);
}

void func_80106418_crazy_cogs(omObjData *arg0) {
    s8 cogIdx = ((s8 *)arg0->work)[3];
    UnkCrazyCogsCog *cog = &D_8010C8E4_crazy_cogs[cogIdx];

    if (D_8010DE6A_crazy_cogs[cogIdx] != 0) {
        if (cog->timer & 1) {
            arg0->trans.y = 10.0f;
        } else {
            arg0->trans.y = 0.0f;
        }

        cog->timer++;

        if ((s16)cog->timer >= 0x14) {
            cog->timer = 0;
            D_8010DE6A_crazy_cogs[cogIdx] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801064AC_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010654C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801065F0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106688_crazy_cogs);

void func_80106770_crazy_cogs(void) {
    D_8010BA74_crazy_cogs = omAddObj(0x3E8, 2, 0, -1, func_80106688_crazy_cogs);
}

void func_801067AC_crazy_cogs(omObjData *arg0) {
    switch (D_8010DE60_crazy_cogs) {
        case 0:
            break;
        case 1:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, D_8010B9A8_crazy_cogs);
            break;
        case 2:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, -D_8010B9A8_crazy_cogs);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010683C_crazy_cogs);

void func_80106910_crazy_cogs(void) {
    D_8010BAF8_crazy_cogs = omAddObj(0x44C, 2, 0, -1, func_8010683C_crazy_cogs);
}

void func_8010694C_crazy_cogs(omObjData *arg0) {
    switch (D_8010DE60_crazy_cogs) {
        case 0:
            break;
        case 1:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, -D_8010DE14_crazy_cogs);
            break;
        case 2:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, D_8010DE14_crazy_cogs);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801069DC_crazy_cogs);

void func_80106AB0_crazy_cogs(void) {
    D_8010BB7C_crazy_cogs = omAddObj(0x4B0, 2, 0, -1, func_801069DC_crazy_cogs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106AEC_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106B24_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106D54_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80106F54_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107078_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010728C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801074A0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107778_crazy_cogs);

void func_8010787C_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107884_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107AB8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107CA8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107D58_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80107E00_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108190_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108464_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801087B8_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108B0C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80108EE8_crazy_cogs);

void func_80109084_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010908C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801091F4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109298_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109388_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_801097EC_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109A44_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109B88_crazy_cogs);

void func_80109D24_crazy_cogs(void) {
    D_8010B9E3_crazy_cogs[0] = 1;
    D_8010B9E3_crazy_cogs[1] = 1;
    D_8010B9E3_crazy_cogs[2] = 1;
    D_8010B9E3_crazy_cogs[3] = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109D44_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_80109F64_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A4A4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A548_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010A67C_crazy_cogs);

void func_8010AA10_crazy_cogs(omObjData *arg0) {
    s16 i;

    D_8010B99E_crazy_cogs = 0;
    D_8010B994_crazy_cogs = 5;

    for (i = 0; i < 0x32; i++) {
        D_8010B9B0_crazy_cogs[i] = -1;
    }

    D_8010B9B0_crazy_cogs[i] = -1;
    D_8010B9E2_crazy_cogs = 0;
    D_8010B990_crazy_cogs = 0;
    D_8010DE22_crazy_cogs = 0;

    arg0->model[0] = -1;
    arg0->func = func_8010A67C_crazy_cogs;
}

void func_8010AAA4_crazy_cogs(void) {
    D_8010C5CC_crazy_cogs = omAddObj(0x514, 1, 1, -1, func_8010AA10_crazy_cogs);
}

void func_8010AAE0_crazy_cogs(void) {
}

void func_8010AAE8_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AAF0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010ABE0_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AE08_crazy_cogs);

void func_8010AF58_crazy_cogs(void) {
    D_8010C650_crazy_cogs = omAddObj(0x640, 1, 1, -1, func_8010AE08_crazy_cogs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010AF94_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B040_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B064_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B09C_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B0F4_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B46C_crazy_cogs);

void func_8010B568_crazy_cogs(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B570_crazy_cogs);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", func_8010B6E0_crazy_cogs);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_05_crazy_cogs/131C10", D_8010B97C_crazy_cogs);
