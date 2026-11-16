#include "common.h"
#include "game/mallocblock.h"
#include "mgmode.h"

extern s16 mgmode_motTbl[];
extern s16 mgmode_mdlTbl[];

MgmodeModelEntry mgmode_roomMdlDefTbl[19] = {
    { 0x00120000, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120001, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120002, 0x220, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120003, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120004, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00140001, 0x231, 0, 0, { 0.0f, 0.0f, 1125.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120005, 0x231, 0, 0, { 90.0f, 65.0f, -440.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012000A, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120007, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120008, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120006, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120009, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012000B, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012000C, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012000D, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0000, 0x220, 0, 2, { 0.0f, 33.5f, -540.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A001A, 0x231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0021, 0x231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};
MgmodeEspriteDef mgmode_teamSprDefTbl[20] = {
    { 0x00130036, 0x1000, 0, 0 },
    { 0x00130036, 0x1000, 0, 0 },
    { 0x00130036, 0x1000, 0, 0 },
    { 0x00130036, 0x1000, 0, 0 },
    { 0x00120011, 0x1000, 0, 0 },
    { 0x00120011, 0x1000, 0, 0 },
    { 0x00120011, 0x1000, 0, 0 },
    { 0x00120011, 0x1000, 0, 0 },
    { 0x00140012, 0x1000, 0, 0 },
    { 0x00140013, 0x1000, 0, 0 },
    { 0x00140043, 0x1000, 0, 0 },
    { 0x00140044, 0x1000, 0, 0 },
    { 0x00140045, 0x1000, 0, 0 },
    { 0x00140046, 0x1000, 0, 0 },
    { 0x001300D1, 0x1000, 0, 0 },
    { 0x001300D1, 0x1000, 0, 0 },
    { 0x001300D1, 0x1000, 0, 0 },
    { 0x001300D1, 0x1000, 0, 0 },
    { 0x00120010, 0x1000, 0, 0 },
    { -1, 0x0, 0, 0 }
};
MgmodeModelEntry mgmode_battleMdlDefTbl[37] = {
    { 0x00120015, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120017, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120018, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120019, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0028, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0x000A0029, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0x000A0019, 0x220, 0, 2, { -222.0f, 26.0f, -312.0f }, { 0.0f, 15.0f, 0.0f } },
    { 0x000800A1, 0x220, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000800A1, 0x220, 0, 2, { -42.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000800A1, 0x220, 0, 2, { 38.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000800A1, 0x220, 0, 2, { 118.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -22.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 78.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x231, 0, 0, { -222.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};
MgmodeEspriteDef mgmode_battleMenuSprDefTbl[10] = {
    { 0x0012001A, 0x1000, 160, 120 },
    { 0x0012001B, 0x9000, 0, 0 },
    { 0x0012001C, 0x9000, 0, 0 },
    { 0x0012001D, 0x9000, 0, 0 },
    { 0x0012001E, 0x9000, 0, 0 },
    { 0x00120020, 0x9000, 0, 0 },
    { 0x0012001F, 0x9000, 0, 0 },
    { 0x00120021, 0x9000, 0, 0 },
    { 0x00120022, 0x9000, 0, 0 },
    { -1, 0x0, 0, 0 }
};
MgmodeEspriteDef mgmode_battleBoardSprDefTbl[10] = {
    { 0x00120014, 0x5000, 160, 120 },
    { 0x00120023, 0xD000, 160, 120 },
    { 0x00120023, 0xD000, 160, 120 },
    { 0x00120023, 0xD000, 160, 120 },
    { 0x00120023, 0xD000, 160, 120 },
    { 0x0012002D, 0x5000, 160, 120 },
    { 0x0012002D, 0x5000, 160, 120 },
    { 0x0012002D, 0x5000, 160, 120 },
    { 0x0012002D, 0x5000, 160, 120 },
    { -1, 0x0, 0, 0 }
};
MgmodeModelEntry mgmode_gambleMdlDefTbl[20] = {
    { 0x00120035, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120036, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120038, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00120039, 0x231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0063, 0xA31, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0x000A0072, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0x000A0070, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0x000A006A, 0x231, 0, 2, { -436.0f, 0.0f, 92.0f }, { 0.0f, 100.0f, 0.0f } },
    { 0x000800A1, 0x224, 0, 2, { 178.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00080000, 0x231, 0, 2, { -122.0f, 26.0f, -312.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012000C, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0, 0x235, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0012003A, 0x624, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0x0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};
MgmodeEspriteDef mgmode_gambleCoinSprDefTbl[7] = {
    { 0x0021001A, 0x1000, 29, 22 },
    { 0x0021001B, 0x1000, 39, 21 },
    { 49, 0x1000, 49, 21 },
    { 49, 0x1000, 59, 21 },
    { 49, 0x1000, 69, 21 },
    { 49, 0x1000, 79, 21 },
    { -1, 0x0, 0, 0 }
};
MgmodeEspriteDef mgmode_gambleBoardSprDefTbl[22] = {
    { 0x0012001A, 0x5000, 184, 108 },
    { 0x0012003B, 0xD000, 160, 120 },
    { 0x0012003C, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C008C, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C008C, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x00190009, 0xD000, 160, 120 },
    { 0x000C008C, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { 0x000C0086, 0xD000, 160, 120 },
    { -1, 0x0, 0, 0 }
};
u8 mgmode_chrVoiceTbl[8] = {
    2, 3, 7, 4, 5, 6, 8, 9
};

void mgmode_MdlListPosSet(MgmodeModelEntry *entries, s16 index, s16 modelId) {
    MgmodeModelEntry *entry = &entries[index];

    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

void mgmode_MdlListCreate(MgmodeModelEntry *entries) {
    MgmodeModelEntry *entry = entries;
    s16 i;
    s16 model;

    for (i = 0; entry->unk_00 != -1; i++, entry++) {
        mgmode_mdlTbl[i] = Hu3DModelRead(entry->unk_00, entry->unk_04 | 0x288);
        model = mgmode_mdlTbl[i];
        Hu3DModelCameraSet(model, 1);
        mgmode_MdlListPosSet(entries, i, model);
        mgmode_motTbl[i] = Hu3DData[model].motId;
        if (mgmode_motTbl[i] != -1) {
            Hu3DMotionAttrSet(model, -1, entry->motAttr);
        }
    }
}

MgmodeEsprite *mgmode_SprListCreate(MgmodeEspriteDef *defs) {
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
        sprites[i].spriteGroup = HuSprAnimDataRead(defs->dataNum);
        slot = sprites[i].espriteSlot = espEntry(sprites[i].spriteGroup, 0, 1);
        espPosSet(slot, defs->x, defs->y);
        espAttrReset(slot, 0xFFFF);
        espAttrSet(slot, defs->attr);
    }
    sprites[i].spriteGroup = -1;
    return sprites;
}

void mgmode_SprListKill(MgmodeEsprite *arg0) {
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

void mgmode_SprListPosSet(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3) {
    espPosSet(arg0[index].espriteSlot, arg2, arg3);
}

void mgmode_SprListDispOn(MgmodeEsprite *arg0, s16 index) {
    espDispOn(arg0[index].espriteSlot);
}

void mgmode_SprListDispOff(MgmodeEsprite *arg0, s16 index) {
    espDispOff(arg0[index].espriteSlot);
}

void mgmode_SprListAttrSet(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    espAttrSet(arg0[index].espriteSlot, arg2);
}

void mgmode_SprListAttrReset(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    espAttrReset(arg0[index].espriteSlot, arg2);
}

void mgmode_SprListScaleSet(MgmodeEsprite *arg0, s16 index, f32 x, f32 y) {
    espScaleSet(arg0[index].espriteSlot, x, y);
}

void mgmode_SprListTPLvlSet(MgmodeEsprite *arg0, s16 index, s16 tpLvl) {
    espTPLvlSet(arg0[index].espriteSlot, tpLvl);
}

void mgmode_SprListPatNoSet(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    espPatNoSet(arg0[index].espriteSlot, arg2);
    espAnimModeSet(arg0[index].espriteSlot, 0);
}

void mgmode_SprListPriSet(MgmodeEsprite *arg0, s16 index, u16 arg2) {
    espPriSet(arg0[index].espriteSlot, arg2);
}
