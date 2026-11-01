#include "common.h"
#include "mallocblock.h"
#include "overlays/mgmode.h"

void espAttrSet(u16 arg0, u16 arg1);
void espAttrReset(u16, u16);

void func_80116610_mgmode(MgmodeModelEntry *entries, s16 index, s16 modelId) {
    MgmodeModelEntry *entry = &entries[index];

    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_8011667C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116794_mgmode);

void func_801168E0_mgmode(MgmodeEsprite *arg0) {
    MgmodeEsprite *sprite = arg0;
    s16 i;

    for (i = 0; i < 0x40; i++) {
        if (sprite->spriteGroup == -1) {
            break;
        }
        espKill(sprite->espriteSlot);
        HuSprAnimKill(sprite->spriteGroup);
        sprite++;
    }
    HuMemFree(arg0);
}

void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3) {
    espPosSet(arg0[index].espriteSlot, arg2, arg3);
}

void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index) {
    espDispOn(arg0[index].espriteSlot);
}

void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index) {
    espDispOff(arg0[index].espriteSlot);
}

void func_801169F0_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    espAttrSet(arg0[index].espriteSlot, arg2);
}

void func_80116A1C_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    espAttrReset(arg0[index].espriteSlot, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116A48_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116A78_mgmode);

void func_80116AA8_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    func_8000BD50_main(arg0[index].espriteSlot, arg2);
    func_8000BDDC_main(arg0[index].espriteSlot, 0);
}

void func_80116AEC_mgmode(MgmodeEsprite *arg0, s16 index, u16 arg2) {
    espPriSet(arg0[index].espriteSlot, arg2);
}
