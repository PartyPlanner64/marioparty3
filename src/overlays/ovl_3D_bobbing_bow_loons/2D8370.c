#include "common.h"
#include "mallocblock.h"

// Per-object work block for D_80109B2C_bobbing_bow_loons, allocated in
// func_80106CC0_bobbing_bow_loons. Holds five parallel per-item arrays.
typedef struct BobbingBowLoonsWork {
    /* 0x00 */ s32 state[5];
    /* 0x14 */ f32 pos_x[5];
    /* 0x28 */ f32 pos_y[5];
    /* 0x3C */ f32 pos_z[5];
    /* 0x50 */ f32 unk_50[5];
    /* 0x64 */ f32 unk_64[5];
    /* 0x78 */ f32 rise;
} BobbingBowLoonsWork; // Size 0x7C

extern omObjData *D_80109B2C_bobbing_bow_loons;
extern omObjData *D_80109B58_bobbing_bow_loons;
extern s16 D_80109B18_bobbing_bow_loons;

s32 func_8000B638_main(void);

void func_80107C74_bobbing_bow_loons(void);
void func_80107D78_bobbing_bow_loons(void);
void func_80107E94_bobbing_bow_loons(void);
void func_80107F94_bobbing_bow_loons(void);
void func_80108354_bobbing_bow_loons(void);
void func_801088C0_bobbing_bow_loons(void);
void func_80109594_bobbing_bow_loons(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801059A0_bobbing_bow_loons);

void func_80105AE8_bobbing_bow_loons(void) {
    s16 camIndex;

    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    D_80109B18_bobbing_bow_loons = camIndex;
    Hu3DCamSetPerspective(camIndex, 30.0f, 80.0f, 8000.0f);
    CZoom = 500.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80105B64_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80105D04_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106260_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801063F8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801064C0_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801065C8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801068B0_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106A00_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097D0_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097E4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801097F8_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_8010980C_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109820_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109834_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109844_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109864_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109884_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801098E4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109904_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109924_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109944_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109964_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106A34_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106CC0_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80106F44_bobbing_bow_loons);

void func_80107130_bobbing_bow_loons(void) {
    BobbingBowLoonsWork *work = D_80109B2C_bobbing_bow_loons->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(work->state); i++) {
        work->state[i] = (work->state[i] | 2) & ~1;
    }
    work->rise = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107174_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010728C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107368_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801074CC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107830_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801079E8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107A7C_bobbing_bow_loons);

void func_80107C48_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107C74_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107C74_bobbing_bow_loons);

void func_80107D4C_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107D78_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107D78_bobbing_bow_loons);

void func_80107E68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107E94_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107E94_bobbing_bow_loons);

void func_80107F68_bobbing_bow_loons(void) {
    omAddPrcObj(func_80107F94_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80107F94_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801099A8_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010805C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010817C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010829C_bobbing_bow_loons);

void func_80108328_bobbing_bow_loons(void) {
    omAddPrcObj(func_80108354_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108354_bobbing_bow_loons);

void func_80108894_bobbing_bow_loons(void) {
    omAddPrcObj(func_801088C0_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801088C0_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_801099F4_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A14_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A34_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A54_bobbing_bow_loons);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", D_80109A68_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108C18_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108E5C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80108F2C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80109044_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801090EC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801091FC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_8010934C_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801093DC_bobbing_bow_loons);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801094B0_bobbing_bow_loons);

void func_80109568_bobbing_bow_loons(void) {
    omAddPrcObj(func_80109594_bobbing_bow_loons, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_80109594_bobbing_bow_loons);

void func_80109680_bobbing_bow_loons(void) {
    omObjData *object = omAddObj(0xFF, 1, 0, -1, NULL);

    D_80109B58_bobbing_bow_loons = object;
    object->data = HuMemAllocTag(8, 0x7918);
    object->model[0] = func_8000B108_main(0xB0003, 0x6DD);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3D_bobbing_bow_loons/2D8370", func_801096E8_bobbing_bow_loons);
