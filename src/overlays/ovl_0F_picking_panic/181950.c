#include "common.h"

typedef struct PickingPanicPlayer {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ char unk5[0xB];
} PickingPanicPlayer; // sizeof 0x10

extern PickingPanicPlayer D_8010EEA0_picking_panic[4];
extern PickingPanicPlayer *D_8010EEE0_picking_panic[4];
extern s8 D_8010EEF0_picking_panic[2];
extern s16 D_8010EF10_picking_panic[2];
extern u8 D_8010EF14_picking_panic;
extern s8 D_8010EF15_picking_panic[2];
extern s32 D_8010EF7C_picking_panic;
extern s16 D_8010EF80_picking_panic;
extern f32 D_8010EF84_picking_panic[2];
extern f32 D_8010EF94_picking_panic;
extern s8 D_8010EF98_picking_panic[2];
extern u8 D_8010EFA4_picking_panic;
extern s32 D_8010EFA8_picking_panic;
extern s8 D_8010EFBC_picking_panic[2];
extern s16 D_8010EFBE_picking_panic;
extern u8 D_8010EFC0_picking_panic[4];

void func_80106020_picking_panic(omObjData *object);
void func_80109C00_picking_panic(Gfx **, s32, s32);
void func_8010B220_picking_panic(omObjData *object, u8 arg1);
void func_8010B8D0_picking_panic(omObjData *object);
void func_8010B8EC_picking_panic(omObjData *object);
void func_8010B908_picking_panic(omObjData *object, s32 arg1);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_801059A0_picking_panic);

void func_80105D3C_picking_panic(omObjData *object) {
    u8 groups[4];
    u8 group;
    s32 i;

    D_8010EFBE_picking_panic = 0;
    D_8010EF80_picking_panic = 0;
    D_8010EFA8_picking_panic = 0;
    D_8010EF7C_picking_panic = 0;
    D_8010EF14_picking_panic = 5;
    D_8010EF10_picking_panic[0] = D_8010EF10_picking_panic[1] = 1;
    D_8010EF98_picking_panic[0] = D_8010EF98_picking_panic[1] = -1;
    D_8010EFBC_picking_panic[0] = D_8010EFBC_picking_panic[1] = 0;
    D_8010EEF0_picking_panic[0] = D_8010EEF0_picking_panic[1] = 0;
    D_8010EF15_picking_panic[0] = D_8010EF15_picking_panic[1] = 0;
    D_8010EFA4_picking_panic = 0xFF;
    D_8010EF94_picking_panic = D_8010EF84_picking_panic[0] = D_8010EF84_picking_panic[1] = 0.0f;

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[i] = &D_8010EEA0_picking_panic[i];
        bzero(&D_8010EEA0_picking_panic[i], sizeof(PickingPanicPlayer));
    }

    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        groups[i] = group;
        D_8010EFC0_picking_panic[groups[i]] = i;
    }

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[groups[i]]->unk0 = i;
        D_8010EEE0_picking_panic[i]->unk2 = GwPlayer[D_8010EFC0_picking_panic[i]].pad;
        D_8010EEE0_picking_panic[i]->unk3 = GwPlayer[D_8010EFC0_picking_panic[i]].chr;
        D_8010EEE0_picking_panic[i]->unk1 = i;
        D_8010EEE0_picking_panic[i]->unk4 = (GwPlayer[D_8010EFC0_picking_panic[i]].stat & 1)
                                                ? GwPlayer[D_8010EFC0_picking_panic[i]].cpu_difficulty
                                                : -1;
    }

    for (i = 0; i < 4; i++) {
        if (D_8010EEE0_picking_panic[i]->unk4 != -1) {
            if (D_8010EEE0_picking_panic[(i & 1) ? i - 1 : i + 1]->unk4 == -1) {
                D_8010EEE0_picking_panic[i]->unk4 += 4;
            }
        }
    }

    func_8001AC8C_main(0, func_80109C00_picking_panic, 2);
    object->func = func_80106020_picking_panic;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E720_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E758_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106020_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E798_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7C0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7E8_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010664C_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106E84_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80107A48_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E990_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80109C00_picking_panic);

void func_8010B11C_picking_panic(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &HmfModelData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}

void func_8010B160_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 0);
    object->func = func_8010B8D0_picking_panic;
}

void func_8010B194_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 1);
    object->func = NULL;
}

void func_8010B1C0_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 2);
    object->func = func_8010B8EC_picking_panic;
}

void func_8010B1F4_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 3);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B220_picking_panic);

void func_8010B8D0_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 0);
}

void func_8010B8EC_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 1);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E9E0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA20_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA40_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA80_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA8C_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B908_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAB8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAE8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAFC_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB04_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB08_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB10_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB18_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB20_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB28_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB30_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB38_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB40_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB48_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB50_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB58_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB60_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB68_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB70_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB78_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB80_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB88_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB90_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB98_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC08_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC10_picking_panic);
