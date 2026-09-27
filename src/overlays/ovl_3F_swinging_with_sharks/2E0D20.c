#include "common.h"

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 animId;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} SharkEntry; // Size 0x24

extern s16 D_8010B938_swinging_with_sharks;
extern s16 D_8010BB48_swinging_with_sharks;
extern Vec D_8010BB78_swinging_with_sharks;
extern Vec D_8010BB90_swinging_with_sharks;
extern f32 D_8010BB9C_swinging_with_sharks;
extern Vec D_8010BBA8_swinging_with_sharks;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801059A0_swinging_with_sharks);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", D_8010B770_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80105FE4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80106334_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80106398_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80106870_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80106D44_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107044_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801071A8_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107384_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801073F0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107628_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801076DC_swinging_with_sharks);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", D_8010B7C0_swinging_with_sharks);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", D_8010B7C8_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801077C4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107954_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108474_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801085F4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801088F0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801089A4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108B24_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108B4C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108C08_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108DB0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108E00_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108E50_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108F20_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109020_swinging_with_sharks);

void func_801096AC_swinging_with_sharks(void) {
    CRot = D_8010BBA8_swinging_with_sharks;
    D_8010BB90_swinging_with_sharks = CRot;
    CZoom = D_8010BB9C_swinging_with_sharks;
    Center = D_8010BB78_swinging_with_sharks;
}

void func_80109730_swinging_with_sharks(SharkEntry *arg0, s16 arg1, s16 modelId) {
    SharkEntry *entry = &arg0[arg1];
    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010979C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801098C0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109924_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109950_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109B04_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109C90_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A0C0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A260_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A41C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A4DC_swinging_with_sharks);

void func_8010AA68_swinging_with_sharks(void) {
    D_8010BB48_swinging_with_sharks = HmfModelData[D_8010B938_swinging_with_sharks].rot.y;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010AAA0_swinging_with_sharks);
