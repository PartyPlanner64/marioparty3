#include "common.h"
#include "mallocblock.h"

#include "overlays/baby_bowser_broadside.h"

void func_8010DE70_baby_bowser_broadside(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_80109ED0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_80109F64_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A0B4_baby_bowser_broadside);

void func_8010A158_baby_bowser_broadside(s8 arg0, BabyBowserBroadsideHandler *arg1) {
    memset(arg1, 0, sizeof(BabyBowserBroadsideHandler));
    D_80110014_baby_bowser_broadside[arg0].unk_10 = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A1B0_baby_bowser_broadside);

void func_8010A264_baby_bowser_broadside(s8 arg0) {
    BabyBowserBroadsideGroup *group = &D_80110014_baby_bowser_broadside[arg0];

    memset(group->unk_04, 0, group->unk_08 * sizeof(BabyBowserBroadsideHandler));
    group->unk_10 = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A2C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A3C8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A598_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A738_baby_bowser_broadside);

void func_8010A7CC_baby_bowser_broadside(s16 arg0) {
    BabyBowserBroadsideSprite *sprite = &D_80110018_baby_bowser_broadside[arg0];

    if (sprite->unk_00 != 0) {
        HuSprAttrSet(sprite->unk_01, 0, 0x8000);
        sprite->unk_00 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A81C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A8C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010A9D4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AADC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AB80_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010ACF8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AE60_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010AFF4_baby_bowser_broadside);

void func_8010B098_baby_bowser_broadside(s16 arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4) {
    HmfModel *model;

    if (arg0 >= 8) {
        return;
    }
    model = &HmfModelData[D_80110010_baby_bowser_broadside[arg0].unk_0C];
    model->pos.x = arg1;
    model->pos.y = arg2;
    model->pos.z = arg3;
    func_8001C258_main(D_80110010_baby_bowser_broadside[arg0].unk_0C, 4, 0);
    D_80110010_baby_bowser_broadside[arg0].unk_20[0] = arg4[0];
    D_80110010_baby_bowser_broadside[arg0].unk_20[1] = arg4[1];
    D_80110010_baby_bowser_broadside[arg0].unk_20[2] = arg4[2];
    D_80110010_baby_bowser_broadside[arg0].unk_20[3] = arg4[3];
    D_80110010_baby_bowser_broadside[arg0].unk_04 &= ~0x18;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B198_baby_bowser_broadside);

BabyBowserBroadsideWork *func_8010B328_baby_bowser_broadside(s16 arg0) {
    if (arg0 >= 8) {
        return NULL;
    }
    return &D_80110010_baby_bowser_broadside[arg0];
}

HmfModel *func_8010B360_baby_bowser_broadside(s16 arg0) {
    HmfModel *model;

    if (arg0 < 8) {
        model = &HmfModelData[D_80110010_baby_bowser_broadside[arg0].unk_0C];
    } else {
        model = NULL;
    }
    return model;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B3B4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010B54C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010BCBC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010C8D4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D4C0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D590_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010D6C4_baby_bowser_broadside);

void func_8010DAE8_baby_bowser_broadside(s32 arg0, BabyBowserBroadsideHandler *arg1) {
    D_80110020_baby_bowser_broadside = HuMemAllocTag(0xAB0, 0x7918);
    memset(D_80110020_baby_bowser_broadside, 0, 0xAB0);
    arg1->unk_40 = func_8010DE70_baby_bowser_broadside;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DB38_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DC88_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DDDC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010DE70_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E018_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E0B0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E348_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E538_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E710_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010E9FC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010ED1C_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010EDC0_baby_bowser_broadside);

f32 func_8010F004_baby_bowser_broadside(BabyBowserBroadsideShip *arg0, Vec *arg1, Vec *arg2) {
    Vec shipPos;
    Vec ma;
    Vec mb;

    shipPos.x = arg0->pos.x;
    shipPos.z = arg0->pos.z;
    ma.x = arg1->x - shipPos.x;
    ma.z = arg1->z - shipPos.z;
    mb.x = arg2->x - shipPos.x;
    mb.z = arg2->z - shipPos.z;
    return ma.z * mb.x - ma.x * mb.z;
}

s32 func_8010F060_baby_bowser_broadside(f32 *arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 t = *arg1 / arg4;
    u8 step;

    *arg0 = arg2 + (arg3 - arg2) * t;
    step = *arg1 + 1;
    *arg1 = step;
    if (arg4 < (f32)step) {
        *arg1 = 0;
        *arg0 = arg3;
        return 1;
    }
    return 0;
}

f32 func_8010F0D8_baby_bowser_broadside(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 d;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    d = 1.0f - arg0;
    return d * d * arg1 + (d + d) * arg0 * arg2 + arg0 * arg0 * arg3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F144_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F250_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F3C4_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F5C8_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F6F8_baby_bowser_broadside);

void func_8010F878_baby_bowser_broadside(f32 *arg0) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arg0[i * 4 + j] = 0.0f;
        }
        arg0[i * 4 + i] = 1.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F900_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F958_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010F9C0_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FA28_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FADC_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FB74_baby_bowser_broadside);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0C_baby_bowser_broadside/169540", func_8010FC2C_baby_bowser_broadside);
