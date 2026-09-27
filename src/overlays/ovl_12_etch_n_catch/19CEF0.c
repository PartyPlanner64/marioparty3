#include "common.h"

// Grid cell value marking a cell that was just filled.
#define ETCH_N_CATCH_CELL_FILLED 0x21

// Per-player record. D_801113D8_etch_n_catch points at one 0x100-entry array of
// these per player, and a record is free for reuse while unk_00 is zero.
// Records are chained through unk_04/unk_08/unk_0C.
typedef struct EtchNCatchNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ struct EtchNCatchNode *unk_04;
    /* 0x08 */ struct EtchNCatchNode *unk_08;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ char unk_10[0x28];
} EtchNCatchNode; // sizeof 0x38

// Heap-allocated (0x20 bytes) work block; unk_0C is the head of a linked list
// of nodes (func_80108B64 inserts, func_80108BCC removes, func_80108C08 walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ char unk_00[0xC];
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ char unk_10[0x10];
} EtchNCatchWork; // sizeof 0x20

// Byte grid of player slots: D_8010C84C_etch_n_catch is the base address and
// D_8010C846_etch_n_catch the row stride in bytes.
extern u8 *D_8010C84C_etch_n_catch;
extern s16 D_8010C846_etch_n_catch;
extern EtchNCatchNode *D_801113D8_etch_n_catch[4];

// Heap-allocated list of grid cells touched this frame, one pointer per entry.
extern u8 **D_8010C878_etch_n_catch;

// Minigame object owning the etch/catch models. unk_40 points at the three model
// handles, unk_18/unk_30 are the position and scale triples written to them.
typedef struct EtchNCatchObj {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk_24[0xC];
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ char unk_3C[4];
    /* 0x40 */ s16 *unk_40;
} EtchNCatchObj; // sizeof 0x44

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_801059A0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105CD0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105D5C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80105ED4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106334_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106A64_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107D38_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80107EA4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010880C_etch_n_catch);

void func_80108B20_etch_n_catch(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

EtchNCatchNode *func_80108B28_etch_n_catch(s8 playerId) {
    EtchNCatchNode *node = D_801113D8_etch_n_catch[playerId];
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (node->unk_00 == 0) {
            break;
        }
        node++;
    }
    return node;
}

void func_80108B64_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    EtchNCatchNode *prev = *head;

    if (prev != NULL) {
        while (prev->unk_08 != NULL) {
            prev = prev->unk_08;
        }
        node->unk_08 = prev->unk_08;
        node->unk_04 = prev;
        prev->unk_08 = node;
        if (node->unk_08 != NULL) {
            node->unk_08->unk_04 = node;
        }
        return;
    }

    node->unk_08 = *head;
    node->unk_04 = NULL;
    *head = node;
    if (prev != NULL) {
        prev->unk_04 = node;
    }
}

void func_80108BCC_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    if (node->unk_08 != NULL) {
        node->unk_08->unk_04 = node->unk_04;
    }
    if (node->unk_04 != NULL) {
        node->unk_04->unk_08 = node->unk_08;
    } else {
        *head = node->unk_08;
    }
    node->unk_00 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108C08_etch_n_catch);

// Undoes the "filled" mark on every grid cell appended to the touched-cell list
// up to (but not including) arg0.
void func_80108D84_etch_n_catch(u8 **arg0) {
    u8 **cellPtr = D_8010C878_etch_n_catch;
    // arg0 points one past the last appended cell, so the difference is a byte offset.
    s32 count = ((s32)arg0 - (s32)cellPtr) >> 2;
    s32 i;

    for (i = 0; i < count; i++) {
        u8 *cell = *cellPtr++;
        if (cell[0] == ETCH_N_CATCH_CELL_FILLED) {
            cell[0] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108DD0_etch_n_catch);

u8 *func_801090E0_etch_n_catch(s16 x, s16 y) {
    return D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
}

u8 func_80109114_etch_n_catch(s16 x, s16 y) {
    u8 *p = D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
    return *p;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010914C_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C740_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C758_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C770_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C788_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109370_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_801097B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109A54_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7BC_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80109EB8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AB7C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AD6C_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C7F0_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AEE4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010AFB8_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B154_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B24C_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010B3B4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BBE4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BD98_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BE84_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C2F4_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C390_etch_n_catch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C444_etch_n_catch);

f32 func_8010C4F8_etch_n_catch(f32 arg0) {
    while (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    }
    while (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010C574_etch_n_catch);

void func_8010C628_etch_n_catch(EtchNCatchObj *obj, f32 scale) {
    obj->unk_38 = scale;
    obj->unk_34 = scale;
    obj->unk_30 = scale;
    Hu3DModelScaleSet(obj->unk_40[0], scale, obj->unk_34, obj->unk_38);
    Hu3DModelScaleSet(obj->unk_40[1], obj->unk_30, obj->unk_34, obj->unk_38);
    Hu3DModelScaleSet(obj->unk_40[2], obj->unk_30, obj->unk_34, obj->unk_38);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C820_etch_n_catch);
