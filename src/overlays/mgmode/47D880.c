#include "common.h"
#include "game/mallocblock.h"
#include "overlays/mgmode.h"

extern s16 D_8011B780_mgmode[];
extern s16 D_8011B8A8_mgmode[];

void func_80116610_mgmode(MgmodeModelEntry *entries, s16 index, s16 modelId) {
    MgmodeModelEntry *entry = &entries[index];

    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

void func_8011667C_mgmode(MgmodeModelEntry *entries) {
    MgmodeModelEntry *entry = entries;
    s16 i;
    s16 model;

    for (i = 0; entry->unk_00 != -1; i++, entry++) {
        D_8011B8A8_mgmode[i] = func_8000B108_main(entry->unk_00, entry->unk_04 | 0x288);
        model = D_8011B8A8_mgmode[i];
        Hu3DModelCameraSet(model, 1);
        func_80116610_mgmode(entries, i, model);
        D_8011B780_mgmode[i] = HmfModelData[model].motId;
        if (D_8011B780_mgmode[i] != -1) {
            func_8001C814_main(model, -1, entry->motAttr);
        }
    }
}

MgmodeEsprite *func_80116794_mgmode(MgmodeEspriteDef *defs) {
    MgmodeEsprite *sprites;
    s16 count;
    s16 i;
    u16 slot;

    for (count = 0; count < 0x40; count++) {
        if (defs[count].dataNum == -1) {
            break;
        }
    }
    sprites = HuMemAllocTag((count + 1) * sizeof(MgmodeEsprite), 0x7918);
    for (i = 0; i < count; i++, defs++) {
        sprites[i].spriteGroup = func_8000B838_main(defs->dataNum);
        slot = sprites[i].espriteSlot = espEntry(sprites[i].spriteGroup, 0, 1);
        espPosSet(slot, defs->x, defs->y);
        espAttrReset(slot, 0xFFFF);
        espAttrSet(slot, defs->attr);
    }
    sprites[i].spriteGroup = -1;
    return sprites;
}

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

void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y) {
    espScaleSet(arg0[index].espriteSlot, x, y);
}

void func_80116A78_mgmode(MgmodeEsprite *arg0, s16 index, s16 tpLvl) {
    espTPLvlSet(arg0[index].espriteSlot, tpLvl);
}

void func_80116AA8_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    func_8000BD50_main(arg0[index].espriteSlot, arg2);
    func_8000BDDC_main(arg0[index].espriteSlot, 0);
}

void func_80116AEC_mgmode(MgmodeEsprite *arg0, s16 index, u16 arg2) {
    espPriSet(arg0[index].espriteSlot, arg2);
}
