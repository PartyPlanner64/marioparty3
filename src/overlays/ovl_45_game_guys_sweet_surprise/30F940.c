#include "common.h"

typedef struct GameGuysSweetSurpriseState { // 0x4 bytes
    /* 0x00 */ s16 frameCounter;
    /* 0x02 */ s16 state;
} GameGuysSweetSurpriseState;

extern GameGuysSweetSurpriseState D_8010CBA4_game_guys_sweet_surprise;
extern s16 D_8010CFE2_game_guys_sweet_surprise;
extern s16 D_8010CFE8_game_guys_sweet_surprise;
extern s16 D_8010CFEA_game_guys_sweet_surprise;
extern s16 D_8010CFF0_game_guys_sweet_surprise;
extern s16 D_8010CFFC_game_guys_sweet_surprise;

void func_801063F0_game_guys_sweet_surprise(omObjData *object);
void func_801072B4_game_guys_sweet_surprise(omObjData *object);
void func_8010AB3C_game_guys_sweet_surprise(omObjData *object);
void func_8010ABD8_game_guys_sweet_surprise(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801059A0_game_guys_sweet_surprise);

s32 func_801059BC_game_guys_sweet_surprise(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105A28_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105AB8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105C18_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105C34_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105DCC_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80105F24_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC90_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CC9C_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCAC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCB4_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCC0_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCCC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCD8_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCE4_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CCF0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010612C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801063F0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80106594_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010672C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80106918_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80106C0C_game_guys_sweet_surprise);

void func_80106CB4_game_guys_sweet_surprise(omObjData *object) {
    GameGuysSweetSurpriseState *loc;

    switch (D_8010CBA4_game_guys_sweet_surprise.state) {
        case 0:
            D_8010CFF0_game_guys_sweet_surprise = 1;
            D_8010CFFC_game_guys_sweet_surprise = 1;
            loc = &D_8010CBA4_game_guys_sweet_surprise;
            loc->state++;
            break;
        case 1:
            if (D_8010CFF0_game_guys_sweet_surprise == 0) {
                D_8010CFE2_game_guys_sweet_surprise = 1;
                loc = &D_8010CBA4_game_guys_sweet_surprise;
                loc->state++;
            }
            break;
        case 2:
            object->func = func_801063F0_game_guys_sweet_surprise;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80106D48_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80106EE4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801071F8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801072B4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107398_game_guys_sweet_surprise);

void func_801073F0_game_guys_sweet_surprise(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_801072B4_game_guys_sweet_surprise;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107418_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107478_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107514_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107550_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107750_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801077D4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107894_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107A8C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107B50_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107B8C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107CAC_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80107F74_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108218_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108538_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010878C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108878_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD50_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD70_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD90_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CD9C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108AC4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108CB8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80108FE0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_801092F0_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80109AA8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_80109DE4_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A604_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A784_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010A820_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AA94_game_guys_sweet_surprise);

void func_8010AAD8_game_guys_sweet_surprise(omObjData *object) {
    omAddObj(0xC8, 0xA, 0xA, -1, func_8010AB3C_game_guys_sweet_surprise);
    omAddObj(0x12C, 0xA, 0xA, -1, func_8010ABD8_game_guys_sweet_surprise);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AB3C_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010ABD8_game_guys_sweet_surprise);

void func_8010AC74_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFEA_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.5f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010CFEA_game_guys_sweet_surprise = 0;
    }
}

void func_8010AD04_game_guys_sweet_surprise(omObjData *object) {
    if (D_8010CFE8_game_guys_sweet_surprise == 1) {
        if (func_801059BC_game_guys_sweet_surprise(3.0f) == 0) {
            object->scale.x = object->scale.y = object->scale.z = 1.25f;
        } else {
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
        }
        func_8001C5B4_main(object->model[0], object->motion[0]);
        D_8010CFE8_game_guys_sweet_surprise = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AD94_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AE44_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010AEB8_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010B004_game_guys_sweet_surprise);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", func_8010B1B4_game_guys_sweet_surprise);

Vec2f *func_8010B1F4_game_guys_sweet_surprise(Vec2f *outPos, f32 x, f32 y, f32 z) {
    Vec pos;
    Vec2f screenPos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    *outPos = screenPos;
    return outPos;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CDEC_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CDF8_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE08_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE14_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE24_game_guys_sweet_surprise);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_45_game_guys_sweet_surprise/30F940", D_8010CE2C_game_guys_sweet_surprise);
