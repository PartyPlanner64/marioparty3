#include "common.h"

extern omObjData *D_8010EE90_river_raiders;
extern omObjData *D_8010DE94_river_raiders;

void func_80106300_river_raiders(omObjData *);
void func_80108188_river_raiders(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801059A0_river_raiders);

f32 func_801059BC_river_raiders(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105A3C_river_raiders);

void func_80105B04_river_raiders(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105B7C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105B88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105BA4_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105D1C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105EAC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80105FA0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801060BC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801061A0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106244_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106300_river_raiders);

void func_801063FC_river_raiders(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, func_80106300_river_raiders);
    obj->work[0] = 0;
    D_8010EE90_river_raiders = obj;
    omSetStatBit(obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106448_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801069A4_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106A54_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106AF8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010716C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80107188_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801072FC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80107B14_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108188_river_raiders);

void func_80108574_river_raiders(void) {
    omObjData *obj;
    s16 i;
    u16 playerIndex = 0;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            continue;
        }
        switch (i) {
            case 0:
                playerIndex = 0;
                break;
            case 1:
                playerIndex = 1;
                break;
            case 2:
                playerIndex = 2;
                break;
            case 3:
                playerIndex = 3;
                break;
        }
        obj = omAddObj(0x2BC, 9, 0x3C, -1, func_80108188_river_raiders);
        obj->work[0] = playerIndex;
        D_8010DE94_river_raiders = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108678_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108ACC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108F40_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801093F0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010940C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010957C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80109C08_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010A6A8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ABA0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ACD8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010BE88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C494_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C890_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C980_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA20_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA4C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA84_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CADC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CF00_river_raiders);

void func_8010D0F0_river_raiders(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D0F8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D268_river_raiders);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", D_8010D9BC_river_raiders);
