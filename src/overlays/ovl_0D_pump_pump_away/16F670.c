#include "common.h"
#include "overlays/minigame.h"

typedef struct UnkPumpPumpAwayEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ Vec unk_78;
} UnkPumpPumpAwayEntry; // sizeof 0x84

typedef struct UnkPumpPumpAway {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C; // 0x0A is also read as an s16 elsewhere
} UnkPumpPumpAway;         // sizeof 0x10

typedef struct UnkPumpPumpAwayState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04; // 0x07 is also read as a u8 elsewhere
} UnkPumpPumpAwayState;    // sizeof 0x8

typedef struct UnkPumpPumpAwayHose {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ omObjData *unk_0C;
} UnkPumpPumpAwayHose; // sizeof 0x10

typedef struct PumpPumpAwayMovingEffect {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 hidden;
    /* 0x08 */ s32 direction;
    /* 0x0C */ f32 speed;
} PumpPumpAwayMovingEffect; // sizeof 0x10

typedef struct UnkPumpPumpAwayParticle {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ omObjData *unk_0C;
} UnkPumpPumpAwayParticle; // sizeof 0x10

typedef struct UnkPumpPumpAwayNozzle {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} UnkPumpPumpAwayNozzle; // sizeof 0x14

typedef struct UnkPumpPumpAwaySpray {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
} UnkPumpPumpAwaySpray; // sizeof 0xC

typedef struct UnkPumpPumpAwayJet {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ omObjData *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
} UnkPumpPumpAwayJet; // sizeof 0x38

typedef struct UnkPumpPumpAwayNode {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04; // 0x06 is also read as an s16 elsewhere
    /* 0x08 */ s32 unk_08; // 0x0A is also read as an s16 elsewhere
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10[8];
    /* 0x30 */ s32 unk_30;
} UnkPumpPumpAwayNode; // sizeof 0x34

typedef struct UnkPumpPumpAwayPlayer {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} UnkPumpPumpAwayPlayer; // sizeof 0x34

typedef struct PumpPumpAwayFade {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 spriteId; // 0x06 is also read as an s16
    /* 0x08 */ s32 modelId;  // 0x0A is also read as an s16
    /* 0x0C */ HuSprite_Unk84_Struct *sprite;
    /* 0x10 */ s32 alpha;
    /* 0x14 */ s32 timer;
} PumpPumpAwayFade; // sizeof 0x18

typedef struct UnkPumpPumpAwayRecord {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u16 record;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} UnkPumpPumpAwayRecord; // sizeof 0x28

typedef struct PumpPumpAwayCamera {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} PumpPumpAwayCamera; // sizeof 0x2C

typedef struct PumpPumpAwayRecordMarker {
    /* 0x00 */ s32 state;
    /* 0x04 */ u16 record;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 hidden;
} PumpPumpAwayRecordMarker; // sizeof 0xC

extern s32 D_800A178C_main[][6];
extern Vec D_80110E70_pump_pump_away[4];
extern s32 D_80111118_pump_pump_away;
extern PumpPumpAwayCamera D_8011111C_pump_pump_away[];
extern s16 D_801116EA_pump_pump_away;
extern s16 D_801116EC_pump_pump_away;
extern s16 D_801116EE_pump_pump_away;
extern s16 D_801116F0_pump_pump_away;
extern s16 D_801116F2_pump_pump_away;
extern s32 D_801116F4_pump_pump_away;
extern s32 D_801116F8_pump_pump_away;
extern s32 D_801116FC_pump_pump_away;
extern s32 D_80111700_pump_pump_away;
extern s32 D_80111704_pump_pump_away;
extern s32 D_80111708_pump_pump_away;
extern UnkPumpPumpAwaySpray D_80111710_pump_pump_away[6];
extern UnkPumpPumpAwayNode D_80111758_pump_pump_away[2];
extern s32 D_8011175C_pump_pump_away;
extern s16 D_8011175E_pump_pump_away;
extern s32 D_80111760_pump_pump_away;
extern s16 D_80111762_pump_pump_away;
extern HuSprite_Unk84_Struct *D_80111764_pump_pump_away;
extern s32 D_80111788_pump_pump_away;
extern s32 D_80111790_pump_pump_away;
extern s16 D_80111792_pump_pump_away;
extern s32 D_80111794_pump_pump_away;
extern s16 D_80111796_pump_pump_away;
extern HuSprite_Unk84_Struct *D_80111798_pump_pump_away;
extern s32 D_801117BC_pump_pump_away;
extern UnkPumpPumpAwayHose D_801117C0_pump_pump_away[2];
extern UnkPumpPumpAwayParticle D_801117E0_pump_pump_away[20];
extern UnkPumpPumpAwayNozzle D_80111920_pump_pump_away[4];
extern UnkPumpPumpAwayPlayer D_80111978_pump_pump_away[2];
extern s32 D_801119E4_pump_pump_away;
extern UnkPumpPumpAwaySpray D_801119E8_pump_pump_away[6];
extern UnkPumpPumpAwayEntry D_80111A30_pump_pump_away[50];
extern UnkPumpPumpAwayState D_80113400_pump_pump_away[3];
extern UnkPumpPumpAway D_80113418_pump_pump_away[2];
extern UnkPumpPumpAwayJet D_80113438_pump_pump_away[4];
extern s32 D_80113518_pump_pump_away;
extern s32 D_8011351C_pump_pump_away;
extern f32 D_80113520_pump_pump_away;
extern omObjData *D_80113524_pump_pump_away;
extern PumpPumpAwayFade D_80113530_pump_pump_away;
extern s32 D_80113534_pump_pump_away;
extern s16 D_80113536_pump_pump_away;
extern s32 D_80113538_pump_pump_away;
extern s16 D_8011353A_pump_pump_away;
extern HuSprite_Unk84_Struct *D_8011353C_pump_pump_away;
extern s32 D_80113540_pump_pump_away;
extern s32 D_80113544_pump_pump_away;
extern UnkPumpPumpAway D_80113570_pump_pump_away[2];
extern UnkPumpPumpAwayRecord D_801135B0_pump_pump_away;
extern u16 D_801135CC_pump_pump_away;
extern PumpPumpAwayRecordMarker D_801135D8_pump_pump_away;
extern u16 D_801135DC_pump_pump_away;
extern s32 D_801135E0_pump_pump_away;
extern PumpPumpAwayMovingEffect D_801135E8_pump_pump_away[4];
extern s32 fontcolor;
extern const s16 D_801116D8_pump_pump_away[];

void func_8000B710_main(s32 arg0);
omObjData *func_80045EF4_main(u32 arg0, s16 arg1);
u16 GWMgRecordGet(s16 arg0);
void func_8004AE00_main(s16 arg0, s16 arg1);
void func_8010654C_pump_pump_away(omObjData *obj);
void func_80106724_pump_pump_away(omObjData *obj);
void func_8010682C_pump_pump_away(omObjData *obj);
void func_801068C8_pump_pump_away(omObjData *obj);
void func_801069D0_pump_pump_away(omObjData *obj);
void func_80107338_pump_pump_away(omObjData *obj);
void func_8010749C_pump_pump_away(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_8010780C_pump_pump_away(omObjData *obj);
void func_80107B40_pump_pump_away(omObjData *obj);
void func_80108358_pump_pump_away(omObjData *obj);
void func_80108560_pump_pump_away(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_80108810_pump_pump_away(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_80108CFC_pump_pump_away(omObjData *obj);
void func_80108E74_pump_pump_away(omObjData *obj);
void func_80109280_pump_pump_away(omObjData *obj);
void func_801094CC_pump_pump_away(omObjData *obj);
void func_801099D4_pump_pump_away(omObjData *obj);
void func_80109A50_pump_pump_away(omObjData *obj);
void func_80109D74_pump_pump_away(omObjData *obj);
void func_8010B370_pump_pump_away(omObjData *obj);
void func_8010C6E4_pump_pump_away(omObjData *obj);
void func_8010D1B8_pump_pump_away(omObjData *obj);
void func_8010D48C_pump_pump_away(omObjData *obj);
void func_8010D620_pump_pump_away(omObjData *obj);
void func_8010DD24_pump_pump_away(omObjData *obj);
void func_8010E0F4_pump_pump_away(omObjData *obj);
void func_8010E45C_pump_pump_away(omObjData *obj);
void func_8010E6B8_pump_pump_away(omObjData *obj);
void func_8010E98C_pump_pump_away(omObjData *obj);
void func_8010F688_pump_pump_away(omObjData *obj);
void func_8010F900_pump_pump_away(omObjData *obj);
void func_8010FC64_pump_pump_away(omObjData *obj);
void func_8010FD94_pump_pump_away(omObjData *obj);
void func_8010FE6C_pump_pump_away(omObjData *obj);
void func_8010FEF8_pump_pump_away(omObjData *obj);
void func_8010EBC4_pump_pump_away(omObjData *obj);
void func_8010F024_pump_pump_away(omObjData *obj);
void func_80110034_pump_pump_away(omObjData *obj);
void func_801100F0_pump_pump_away(void);
void func_801102E4_pump_pump_away(omObjData *obj);
void func_801103D8_pump_pump_away(omObjData *obj);
void func_801104BC_pump_pump_away(omObjData *obj);
void func_80110D28_pump_pump_away(void);

void func_801059A0_pump_pump_away(void) {
    func_80110D28_pump_pump_away();
}

Gfx **func_801059BC_pump_pump_away(Gfx **gfxPos) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gfx = *gfxPos;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, geometryMode);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfxPos = gfx;
    return gfxPos;
}

Gfx **func_80105AA0_pump_pump_away(Gfx **gfxPos) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gfx = *gfxPos;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, geometryMode);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    *gfxPos = gfx;
    return gfxPos;
}

Gfx **func_80105B6C_pump_pump_away(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

f32 func_80105B9C_pump_pump_away(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105C1C_pump_pump_away(u32 arg0) {
    return (rand8() * arg0) >> 8;
}

void func_80105C54_pump_pump_away(void) {
    u32 i;
    UnkPumpPumpAwayEntry *entry;

    for (i = 0, entry = D_80111A30_pump_pump_away; i < 50; i++, entry++) {
        entry->unk_00 = 0;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
        entry->unk_40 = -1;
        entry->unk_42 = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68 = 0.0f;
        entry->unk_6C = 0.0f;
        entry->unk_70 = 0.0f;
        entry->unk_74 = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105D1C_pump_pump_away(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

f32 func_80105D94_pump_pump_away(f32 value) {
    s32 range;
    s32 i;
    f32 fraction;

    if (value > 1.0f) {
        range = 1;
        value = 1.0f / value;
    } else if (value < -1.0f) {
        range = -1;
        value = 1.0f / value;
    } else {
        range = 0;
    }

    fraction = 0.0f;
    for (i = 6; i > 0; i--) {
        fraction = (i * i * value * value) / (2 * i + 1 + fraction);
    }

    if (fraction != -1.0f) {
        if (range > 0) {
            return 1.5707963267948966 - value / (fraction + 1.0f);
        } else if (range < 0) {
            return -1.5707963267948966 - value / (fraction + 1.0f);
        } else {
            return value / (fraction + 1.0f);
        }
    }
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80105EE4_pump_pump_away);

void func_80106260_pump_pump_away(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010628C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010654C_pump_pump_away);

void func_801066F0_pump_pump_away(void) {
    omAddObj(0xC8, 3, 0, -1, func_8010654C_pump_pump_away);
}

void func_80106724_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *first;
    UnkPumpPumpAwayPlayer *player;
    UnkPumpPumpAwayPlayer *other;

    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            first = &D_80111978_pump_pump_away[0];
            player = D_80111978_pump_pump_away;
            other = &player[1];
            if (first->unk_18 - other->unk_18 > 0.0f) {
                obj->trans.y -= first->unk_20 * 0.9;
            } else {
                obj->trans.y -= other->unk_20 * 0.9;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 5:
            break;
        case 6:
            if (D_80113530_pump_pump_away.state < 2) {
                break;
            }
        case 7:
            obj->trans.x = obj->trans.y = 0.0f;
            obj->trans.z = -1100.0f;
            break;
    }
}

void func_8010682C_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0003, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1100.0f;
    obj->func = func_80106724_pump_pump_away;
}

void func_80106894_pump_pump_away(void) {
    omAddObj(0xFA, 1, 0, -1, func_8010682C_pump_pump_away);
}

void func_801068C8_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *first;
    UnkPumpPumpAwayPlayer *player;
    UnkPumpPumpAwayPlayer *other;

    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            first = &D_80111978_pump_pump_away[0];
            player = D_80111978_pump_pump_away;
            other = &player[1];
            if (first->unk_18 - other->unk_18 > 0.0f) {
                obj->trans.y -= first->unk_20 * 0.8;
            } else {
                obj->trans.y -= other->unk_20 * 0.8;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 5:
            break;
        case 6:
            if (D_80113530_pump_pump_away.state < 2) {
                break;
            }
        case 7:
            obj->trans.x = obj->trans.y = 0.0f;
            obj->trans.z = -1290.0f;
            break;
    }
}

void func_801069D0_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E0004, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1290.0f;
    obj->func = func_801068C8_pump_pump_away;
}

void func_80106A38_pump_pump_away(void) {
    omAddObj(0x104, 1, 0, -1, func_801069D0_pump_pump_away);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80106A6C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107338_pump_pump_away);

void func_8010745C_pump_pump_away(void) {
    omObjData *obj = omAddObj(0x64, 2, 0, -1, func_80107338_pump_pump_away);
    omSetStatBit(obj, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010749C_pump_pump_away);

void func_8010775C_pump_pump_away(omObjData *obj) {
    PumpPumpAwayFade *fade = &D_80113530_pump_pump_away;

    if (fade->state == -1) {
        return;
    }
    switch (fade->state) {
        case 0:
            fade->alpha = 0;
            break;
        case 1:
            fade->alpha += 26;
            if (fade->alpha >= 256) {
                fade->alpha = 255;
                fade->state = 2;
            }
            break;
        case 2:
            if (fade->timer != 0) {
                fade->timer--;
            } else {
                fade->state = 3;
            }
            break;
        case 3:
            fade->alpha -= 25;
            if (fade->alpha < 30) {
                fade->alpha = 0;
                fade->state = 4;
            }
            break;
        case 4:
            fade->alpha = 0;
            fade->state = -1;
            break;
    }
}

void func_8010780C_pump_pump_away(omObjData *obj) {
    D_80113534_pump_pump_away = func_8000B838_main(0x2E001E);
    D_8011353C_pump_pump_away = func_80055194_main(D_80113536_pump_pump_away);
    D_80113538_pump_pump_away = func_8001AC8C_main(0, func_8010749C_pump_pump_away, 6);
    func_8001C8A8_main(D_8011353A_pump_pump_away, 1);
    D_80113540_pump_pump_away = 0;
    D_80113530_pump_pump_away.state = -1;
    D_80113544_pump_pump_away = 30;
    obj->func = func_8010775C_pump_pump_away;
}

void func_801078B4_pump_pump_away(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0, -1, func_8010780C_pump_pump_away);
    obj->work[0] = 0;
}

void func_801078EC_pump_pump_away(omObjData *obj) {
    s32 i;
    UnkPumpPumpAwayParticle *entry;

    for (i = 0; i < 20; i++) {
        entry = &D_801117E0_pump_pump_away[i];
        if (entry->unk_00 == 0) {
            entry->unk_00 = 1;
            entry->unk_0C->trans.x = obj->trans.x;
            entry->unk_0C->trans.y = obj->trans.y + 50.0f;
            entry->unk_0C->trans.z = obj->trans.z + 50.0f;
            entry->unk_08 = 0;
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107964_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107A8C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107B40_pump_pump_away);

void func_80107E5C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1F4, 1, 1, -1, func_80107B40_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80107EB8_pump_pump_away);

void func_8010811C_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayHose *hose = &D_801117C0_pump_pump_away[obj->work[0]];
    f32 frame;

    if (hose->unk_04 == 2) {
        if (HmfModelData[obj->model[0]].unk40 >= D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2) {
            func_8001C258_main(obj->model[0], 4, 4);
            hose->unk_04 = 3;
        }
    } else if (hose->unk_04 != 3) {
        frame = HmfModelData[obj->model[0]].unk40;
        if (frame != 0.0f) {
            if (frame >= D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2) {
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
            } else {
                return;
            }
        } else {
            func_8001C5B4_main(obj->model[0], obj->motion[1]);
        }
        func_8001C814_main(obj->model[0], 2, 0);
        hose->unk_04 = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801082AC_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108358_pump_pump_away);

void func_80108504_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x258, 1, 2, -1, func_80108358_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108560_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108810_pump_pump_away);

void func_80108B0C_pump_pump_away(omObjData *obj) {
    s32 digits[4];
    s32 i = 0;
    s32 j;
    s32 distance;
    UnkPumpPumpAwayNode *node = &D_80111758_pump_pump_away[1];
    UnkPumpPumpAwayPlayer *players = D_80111978_pump_pump_away;

    for (; i < 2; i++) {
        distance = players[i].unk_18 / 10.0f;
        digits[0] = distance / 10000;
        distance -= digits[0] * 10000;
        digits[1] = distance / 1000;
        distance -= digits[1] * 1000;
        digits[2] = distance / 100;
        distance -= digits[2] * 100;
        digits[3] = distance / 10;
        distance -= digits[3] * 10;
        for (j = 0; j < 4; j++) {
            node->unk_10[i * 4 + j] = 100 - digits[j] * 10;
            if (j == 3) {
                node->unk_10[i * 4 + j] -= distance;
            }
        }
        for (j = 3; j > 0; j--) {
            if (node->unk_10[i * 4 + j] < 11) {
                node->unk_10[i * 4 + j - 1] -= 10 - node->unk_10[i * 4 + j];
            }
        }
    }
}

void func_80108CFC_pump_pump_away(omObjData *obj) {
    s32 i;
    UnkPumpPumpAwayNode *node;

    for (i = 0; i < 2; i++) {
        node = &D_80111758_pump_pump_away[i];
        if (node->unk_00 == -1) {
            return;
        }
    }
    func_80108B0C_pump_pump_away(obj);
    switch (obj->work[0]) {
        case 0:
            if (D_801116F4_pump_pump_away < 4) {
                for (i = 0; i < 2; i++) {
                    node = &D_80111758_pump_pump_away[i];
                    node->unk_30 = 0;
                }
            } else {
                obj->work[0] = 1;
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                node = &D_80111758_pump_pump_away[i];
                node->unk_30 += 25;
                if (node->unk_30 >= 255) {
                    node->unk_30 = 255;
                    obj->work[0] = 2;
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                node = &D_80111758_pump_pump_away[i];
                node->unk_30 = 255;
            }
            break;
    }
}

void func_80108E74_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayNode *entry = D_80111758_pump_pump_away;
    s32 i;

    D_8011175C_pump_pump_away = func_8000B838_main(0x2E0015);
    D_80111764_pump_pump_away = func_80055194_main(D_8011175E_pump_pump_away);
    D_80111760_pump_pump_away = func_8001AC8C_main(0, func_80108560_pump_pump_away, 2);
    func_8001C8A8_main(D_80111762_pump_pump_away, 1);
    D_80111788_pump_pump_away = 0;
    entry->unk_00 = 0;
    entry++;
    D_80111790_pump_pump_away = func_8000B838_main(0x2E0016);
    D_80111798_pump_pump_away = func_80055194_main(D_80111792_pump_pump_away);
    D_80111794_pump_pump_away = func_8001AC8C_main(0, func_80108810_pump_pump_away, 2);
    func_8001C8A8_main(D_80111796_pump_pump_away, 1);
    D_801117BC_pump_pump_away = 0;
    entry->unk_00 = 0;
    obj->func = func_80108CFC_pump_pump_away;
    for (i = 0; i < 8; i++) {
        entry->unk_10[i] = 100;
    }
}

void func_80108FA8_pump_pump_away(void) {
    omObjData *obj = omAddObj(0x384, 2, 0, -1, func_80108E74_pump_pump_away);
    obj->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80108FE0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010921C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109280_pump_pump_away);

void func_80109470_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x2EE, 1, 2, -1, func_80109280_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_801094CC_pump_pump_away);

void func_801098E0_pump_pump_away(omObjData *obj) {
    s32 *state = &D_80113518_pump_pump_away;
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[D_8011351C_pump_pump_away];

    if (*state == 4) {
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C6A8_main(obj->model[0], 0);
        func_8001C814_main(obj->model[0], 1, 0);
        func_8001C258_main(obj->model[0], 4, 0);
        obj->trans.x = player->unk_28->trans.x;
        obj->trans.y = player->unk_28->trans.y + 200.0f;
        obj->trans.z = player->unk_28->trans.z;
        *state = 5;
    }
}

void func_801099D4_pump_pump_away(omObjData *obj) {
    s32 *state = &D_80113518_pump_pump_away;

    if (*state == -1) {
        return;
    }
    switch (D_801116F4_pump_pump_away) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            if (*state < 4) {
                func_801094CC_pump_pump_away(obj);
                break;
            }
        case 8:
            func_801098E0_pump_pump_away(obj);
            break;
    }
}

void func_80109A50_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E001B, 0x1689);
    func_8000B460_main(obj, 0, 0x2E001C);
    func_8000B460_main(obj, 1, 0x2E001D);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C6A8_main(obj->model[0], 0);
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_801099D4_pump_pump_away;
    D_80113518_pump_pump_away = 0;
    D_8011351C_pump_pump_away = -1;
    D_80113520_pump_pump_away = 180.0f;
    D_80113524_pump_pump_away = obj;
}

void func_80109B48_pump_pump_away(void) {
    omObjData *obj = omAddObj(0x2E4, 1, 2, -1, func_80109A50_pump_pump_away);
    obj->work[0] = 0;
}

void func_80109B80_pump_pump_away(omObjData *obj) {
    s32 i;
    UnkPumpPumpAwayParticle *entry;
    UnkPumpPumpAwayPlayer *player;

    for (i = 0; i < 20; i++) {
        entry = &D_801117E0_pump_pump_away[i];
        if (entry->unk_00 == 0) {
            player = &D_80111978_pump_pump_away[obj->work[0]];
            entry->unk_00 = 1;
            entry->unk_0C->trans.x = obj->trans.x;
            entry->unk_0C->trans.y = obj->trans.y - 200.0f;
            entry->unk_0C->trans.z = obj->trans.z;
            entry->unk_08 = player->unk_20 * 0.6;
            break;
        }
    }
}

void func_80109C30_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayParticle *entry = &D_801117E0_pump_pump_away[obj->work[0]];

    if (entry->unk_00 == -1) {
        return;
    }
    switch (entry->unk_00) {
        case 0:
            break;
        case 1:
            func_8001C258_main(obj->model[0], 4, 0);
            entry->unk_00 = 2;
            break;
        case 2:
            entry->unk_04 -= 25;
            if (entry->unk_04 > 0) {
                func_8001F9E4_main(obj->model[0], (u8)entry->unk_04);
                obj->trans.y -= entry->unk_08 * entry->unk_08;
                obj->scale.x += 0.1;
                obj->scale.y += 0.1;
                obj->scale.z += 0.1;
            } else {
                func_8001C258_main(obj->model[0], 4, 4);
                entry->unk_04 = 255;
                entry->unk_08 = 0;
                entry->unk_00 = 0;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            }
            break;
    }
}

void func_80109D74_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayParticle *entry;

    obj->model[0] = func_8000B108_main(0x2E0013, 0x289);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 255);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->func = func_80109C30_pump_pump_away;
    entry = &D_801117E0_pump_pump_away[obj->work[0]];
    entry->unk_00 = 0;
    entry->unk_04 = 255;
    entry->unk_08 = 0;
    entry->unk_0C = obj;
}

void func_80109E3C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        omAddObj(0x2F8, 1, 0, -1, func_80109D74_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_80109E98_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A150_pump_pump_away);

void func_8010A390_pump_pump_away(omObjData *obj) {
    s32 i = obj->work[0];
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[i];
    UnkPumpPumpAwayState *state = &D_80113400_pump_pump_away[i];

    player->unk_00 = 1;
    state->unk_00 = 1;
    if (obj->work[0] == 0) {
        HuAudFXPlay(0x35F);
    }
}

void func_8010A3F0_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[obj->work[0]];

    if (player->unk_18 - player->unk_1C > 300.0f) {
        func_80109B80_pump_pump_away(obj);
        player->unk_1C = player->unk_18;
    }
}

void func_8010A468_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAway *entry;
    UnkPumpPumpAwayNozzle *nozzle;
    PumpPumpAwayMovingEffect *hose;
    UnkPumpPumpAwaySpray *spray;
    UnkPumpPumpAwaySpray *otherSpray;

    for (i = 0, entry = D_80113418_pump_pump_away; i < 2; i++) {
        entry[i].unk_0C = 1;
    }
    D_801135E0_pump_pump_away = 1;
    for (i = 0, nozzle = D_80111920_pump_pump_away; i < 4; i++) {
        nozzle[i].unk_04 = 1;
    }
    for (i = 0, hose = D_801135E8_pump_pump_away; i < 4; i++) {
        hose[i].hidden = 1;
    }
    for (i = 0, spray = D_80111710_pump_pump_away; i < 6; i++) {
        spray[i].unk_04 = 1;
    }
    for (i = 0, otherSpray = D_801119E8_pump_pump_away; i < 6; i++) {
        otherSpray[i].unk_04 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010A570_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AD24_pump_pump_away);

void func_8010ADA0_pump_pump_away(omObjData *obj) {
    u32 playerIndex = obj->work[0];
    UnkPumpPumpAwayPlayer *players = D_80111978_pump_pump_away;
    UnkPumpPumpAwayPlayer *player = &players[playerIndex ^ 1];

    if (D_801116F4_pump_pump_away < 6) {
        obj->trans.y -= player->unk_20;
        if (obj->trans.y < -2800.0f) {
            obj->trans.y = -2800.0f;
        }
    } else if (D_80113530_pump_pump_away.state >= 2) {
        obj->trans.y = 200.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AE40_pump_pump_away);

void func_8010AED4_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[obj->work[0]];

    if (player->unk_00 == 99) {
        obj->trans.y = 200.0f;
    } else if (player->unk_04 == 2) {
        obj->trans.y = 950.0f;
        player->unk_08 = 20;
    } else if (player->unk_04 == 10) {
        obj->trans.y = 1000.0f;
        obj->rot.z = 0.0f;
        player->unk_08 = 10;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010AF70_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B274_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B370_pump_pump_away);

void func_8010B5D4_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x2BC, 1, 1, -1, func_8010B370_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B630_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010B898_pump_pump_away);

void func_8010BC14_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];

    if (jet->unk_28 != 0) {
        if (jet->unk_18 != 0) {
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 4);
        } else {
            func_8001C814_main(obj->model[0], 1, 0);
            func_8001C814_main(obj->model[0], 4, 0);
        }
    } else if (jet->unk_18 != 0) {
        if (HmfModelData[obj->model[0]].unk40 <= 2.0f) {
            func_8001C814_main(obj->model[0], 1, 1);
        }
    } else if (HmfModelData[obj->model[0]].unk40 >= D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 - 2) {
        func_8001C814_main(obj->model[0], 1, 1);
    }
}

void func_8010BD80_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];

    switch (jet->unk_08) {
        case 0:
            if (obj->rot.y >= 180.0f) {
                break;
            }
            if (obj->work[0] == 0 && D_80111708_pump_pump_away != 0) {
                D_80111708_pump_pump_away--;
            }
            if (D_80111708_pump_pump_away == 0) {
                func_8001C5B4_main(obj->model[0], obj->motion[3]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 2, 2);
                jet->unk_08 = 3;
            }
            break;
        case 3:
            obj->rot.y += 10.0f;
            if (!(obj->rot.y >= 180.0f)) {
                break;
            }
            obj->rot.y = 180.0f;
        case 1:
            func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 20, 2);
            jet->unk_08 = 0;
            jet->unk_0C = 0;
            break;
    }
}

void func_8010BF14_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];
    UnkPumpPumpAwayPlayer *player;
    UnkPumpPumpAwayPlayer *other;

    if (D_80111978_pump_pump_away[obj->work[1]].unk_00 == 99 && jet->unk_0C == 0) {
        func_8001C624_main(obj->model[0], HmfModelData[obj->motion[4]].unk02, 0, 30, 2);
        jet->unk_08 = 4;
        jet->unk_0C = 1;
    }
    player = D_80111978_pump_pump_away;
    other = &player[1];
    if (player->unk_18 - other->unk_18 > 0.0f) {
        obj->trans.y -= player->unk_20;
    } else {
        obj->trans.y -= other->unk_20;
    }
    if (obj->trans.y < -3000.0f) {
        obj->trans.y = -3000.0f;
    }
}

void func_8010C060_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];
    s16 sound;

    switch (jet->unk_08) {
        case 0:
            obj->trans.y = D_80110E70_pump_pump_away[0].y;
            if (D_80111978_pump_pump_away[obj->work[1]].unk_24 == 2) {
                func_8001C5B4_main(obj->model[0], obj->motion[6]);
                func_8001C6A8_main(obj->model[0], 0.0f);
                func_8001C814_main(obj->model[0], 2, 0);
                func_8001C814_main(obj->model[0], 1, 0);
                jet->unk_08 = 6;
                sound = func_8004ACE0_main(0x286, obj->work[0]);
                if (obj->work[1] != 0) {
                    func_8004AE00_main(sound, 0x60);
                } else {
                    func_8004AE00_main(sound, 0x20);
                }
            }
            break;
        case 4:
            if (obj->work[1] == 0) {
                obj->trans.y = D_80110E70_pump_pump_away[0].y;
            } else {
                obj->trans.y = D_80110E70_pump_pump_away[obj->work[1]].y;
            }
            break;
    }
}

void func_8010C1C8_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];
    f32 angle;

    obj->trans.y = D_80110E70_pump_pump_away[0].y;
    switch (jet->unk_08) {
        case 0:
            if (jet->unk_0C == 9) {
                break;
            }
            func_8001C5B4_main(obj->model[0], obj->motion[3]);
            func_8001C6A8_main(obj->model[0], 0);
            func_8001C814_main(obj->model[0], 2, 2);
            jet->unk_08 = 3;
            break;
        case 3:
            obj->rot.y = obj->rot.y + 10.0f >= 360.0f ? obj->rot.y + 10.0f - 360.0f : obj->rot.y + 10.0f < 0.0f ? obj->rot.y + 10.0f + 360.0f
                                                                                                                : obj->rot.y + 10.0f;
            angle = obj->rot.y + 180.0f >= 360.0f ? obj->rot.y + 180.0f - 360.0f : obj->rot.y + 180.0f < 0.0f ? obj->rot.y + 180.0f + 360.0f
                                                                                                              : obj->rot.y + 180.0f;
            if (angle >= 180.0f) {
                obj->rot.y = 0;
                func_8001C624_main(obj->model[0], HmfModelData[obj->motion[0]].unk02, 0, 20, 2);
                jet->unk_08 = 0;
                jet->unk_0C = 9;
            }
            break;
    }
}

void func_8010C3E0_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayJet *jet = &D_80113438_pump_pump_away[obj->work[0]];
    s32 modelFile = D_800A178C_main[GwPlayer[obj->work[0]].chr][0];

    if (jet->unk_08 == 0) {
        func_8001C5B4_main(obj->model[0], obj->motion[5]);
        func_8001C6A8_main(obj->model[0], 0.0f);
        func_8001C814_main(obj->model[0], 1, 0);
        func_8001C814_main(obj->model[0], 2, 0);
        jet->unk_08 = 5;
        if (obj->work[0] != 0) {
            func_80045EF4_main(modelFile | 0x2F, 0x60);
        } else {
            func_80045EF4_main(modelFile | 0x2F, 0x20);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C4D0_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010C6E4_pump_pump_away);

void func_8010CBF0_pump_pump_away(void) {
    s32 i;
    s32 playerIndex;
    omObjData *obj;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(0x12C, 9, 60, -1, func_8010C6E4_pump_pump_away);
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
            default:
                playerIndex = 0;
                break;
        }
        obj->work[0] = playerIndex;
        obj->work[1] = GwPlayer[playerIndex].group;
    }
}

s32 func_8010CCBC_pump_pump_away(void) {
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;
    UnkPumpPumpAwayRecord *record = &D_801135B0_pump_pump_away;
    UnkPumpPumpAwayPlayer *other = &player[1];
    u32 distance;

    if (player->unk_18 > other->unk_18) {
        distance = (u16)(player->unk_18 * 0.01);
        if (distance > record->record) {
            GWMgRecordSet(0, distance);
        } else {
            return 0;
        }
    } else {
        distance = other->unk_18 * 0.01;
        if ((u16)distance > record->record) {
            GWMgRecordSet(0, (u16)distance);
        } else {
            return 0;
        }
    }
    return 1;
}

void func_8010CDF4_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayRecord *record = &D_801135B0_pump_pump_away;
    s32 value;

    if (D_801116F4_pump_pump_away < 9) {
        value = GWMgRecordGet(0);
        D_801135CC_pump_pump_away = value;
    } else {
        value = GWMgRecordGet(0);
    }
    record->unk_0C = value / 100;
    value %= 100;
    if (record->unk_0C == 0) {
        record->unk_0C = -1;
    }
    record->unk_10 = value / 10;
    value %= 10;
    if (record->unk_10 == 0 && record->unk_0C == -1) {
        record->unk_10 = -1;
    }
    record->unk_14 = value;
    record->unk_18 = 12;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010CEE8_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D1B8_pump_pump_away);

void func_8010D458_pump_pump_away(void) {
    omAddObj(0x2FD, 1, 0, -1, func_8010D1B8_pump_pump_away);
}

void func_8010D48C_pump_pump_away(omObjData *obj) {
    PumpPumpAwayRecordMarker *marker = &D_801135D8_pump_pump_away;
    UnkPumpPumpAwayPlayer *first = &D_80111978_pump_pump_away[0];
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;
    UnkPumpPumpAwayPlayer *other = &player[1];
    f64 height;

    if (marker->state == -1) {
        return;
    }
    if (D_801135E0_pump_pump_away == 0) {
        height = (first->unk_18 > other->unk_18) ? first->unk_18 : other->unk_18;
        if (marker->record * 10 - height * 0.1 + 400.0 < 2000.0) {
            func_8001C258_main(obj->model[0], 4, 0);
            obj->trans.y = marker->record * 10 - height * 0.1 + 350.0;
            if (obj->trans.y < -1000.0f) {
                func_8001C258_main(obj->model[0], 4, 4);
                marker->hidden = 1;
            }
        }
    }
    if (D_80113530_pump_pump_away.state >= 2 && marker->state < 10) {
        func_8001C258_main(obj->model[0], 4, 4);
        marker->state = 10;
    }
}

void func_8010D620_pump_pump_away(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2E001F, 0x1689);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 1000.0f;
    obj->trans.z = 550.0f;
    obj->func = func_8010D48C_pump_pump_away;
    D_801135D8_pump_pump_away.state = 0;
    D_801135DC_pump_pump_away = D_801135CC_pump_pump_away;
    D_801135E0_pump_pump_away = 0;
}

void func_8010D6C0_pump_pump_away(void) {
    omAddObj(0x302, 1, 0, -1, func_8010D620_pump_pump_away);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D6F4_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010D95C_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010DC68_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010DD24_pump_pump_away);

void func_8010E098_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x30C, 2, 1, -1, func_8010DD24_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E0F4_pump_pump_away);

void func_8010E45C_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayNozzle *nozzle;

    if (D_801116EC_pump_pump_away == 0) {
        D_801116EC_pump_pump_away = obj->model[0] = func_8000B108_main(0x2E0011, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116EC_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 2, 2);
    func_8001C258_main(obj->model[0], 4, 4);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = (u8)(rand8() % 10) * -50;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010E0F4_pump_pump_away;
    nozzle = &D_80111920_pump_pump_away[obj->work[0]];
    nozzle->unk_00 = 0;
    nozzle->unk_04 = 0;
    nozzle->unk_08 = rand8() & 1;
    nozzle->unk_0C = (u8)(rand8() % 6) + 4;
    nozzle->unk_10 = rand8();
}

void func_8010E65C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x2F9, 1, 1, -1, func_8010E45C_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010E6B8_pump_pump_away);

void func_8010E98C_pump_pump_away(omObjData *obj) {
    PumpPumpAwayMovingEffect *effect;

    if (D_801116EE_pump_pump_away == 0) {
        D_801116EE_pump_pump_away = obj->model[0] = func_8000B108_main(0xA0062, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116EE_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = (u8)(rand8() % 10) * -50;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010E6B8_pump_pump_away;
    effect = &D_801135E8_pump_pump_away[obj->work[0]];
    effect->state = 0;
    effect->hidden = 0;
    effect->direction = rand8() & 1;
    effect->speed = (u8)(rand8() % 5) + 10;
}

void func_8010EB68_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x2FA, 1, 0, -1, func_8010E98C_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010EBC4_pump_pump_away);

void func_8010F024_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwaySpray *spray;

    if (D_801116F0_pump_pump_away == 0) {
        D_801116F0_pump_pump_away = obj->model[0] = func_8000B108_main(0x2E0022, 0x289);
    } else {
        obj->model[0] = Hu3DModelLink(D_801116F0_pump_pump_away);
    }
    func_8001C814_main(obj->model[0], 1, 1);
    func_8001C258_main(obj->model[0], 4, 4);
    if (obj->work[0] & 1) {
        obj->trans.x = rand16() % 501 + 100;
    } else {
        obj->trans.x = -(rand16() % 501) - 100;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = func_8010EBC4_pump_pump_away;
    spray = &D_80111710_pump_pump_away[obj->work[0]];
    spray->unk_00 = 0;
    spray->unk_04 = 0;
    spray->unk_08 = rand8();
}

void func_8010F20C_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(0x2FA, 1, 0, -1, func_8010F024_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F268_pump_pump_away);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F688_pump_pump_away);

void func_8010F8A4_pump_pump_away(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(0x2FB, 1, 0, -1, func_8010F688_pump_pump_away)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", func_8010F900_pump_pump_away);

void func_8010FA20_pump_pump_away(omObjData *obj) {
}

void func_8010FA28_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
    } else {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FA20_pump_pump_away;
    }
}

void func_8010FA64_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() & 0x2) {
        D_801116FC_pump_pump_away = 0x14;
        obj->func = func_8010FA28_pump_pump_away;
    }
}

s32 func_8010FAA8_pump_pump_away(void) {
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;
    UnkPumpPumpAwayPlayer *other = &D_80111978_pump_pump_away[1];
    UnkPumpPumpAwayRecord *record = &D_801135B0_pump_pump_away;
    u32 distance;

    if (player->unk_18 > other->unk_18) {
        distance = (u16)(player->unk_18 * 0.01);
    } else {
        distance = (u16)(other->unk_18 * 0.01);
    }
    return distance > record->record;
}

void func_8010FB70_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[0];
    UnkPumpPumpAwayPlayer *other = &D_80111978_pump_pump_away[1];
    s32 winningTeam;
    s32 i;
    s32 count;
    UnkPumpPumpAwayJet *jet;
    u8 winners[2];

    if (player->unk_18 > other->unk_18) {
        winningTeam = 0;
    } else {
        winningTeam = 1;
    }
    for (i = 0, count = 0; i < 4; i++) {
        jet = &D_80113438_pump_pump_away[i];
        if (jet->unk_04->work[1] == winningTeam) {
            winners[count] = GwPlayer[jet->unk_04->work[0]].chr;
            count++;
            GwPlayer[jet->unk_04->work[0]].bonusCoin = 10;
        }
    }
    GMesCreate(GMES_MES_MG_WINNERS_2, winners[0], winners[1]);
    if (!func_8010FAA8_pump_pump_away()) {
        HuAudSeqPlay(0x66);
    } else {
        HuAudSeqPlay(0x6A);
    }
}

void func_8010FC64_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;
    UnkPumpPumpAwayPlayer *other = &player[1];

    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
    } else {
        if (player->unk_18 == other->unk_18) {
            GMesCreate(GMES_MES_MG_DRAW);
            HuAudSeqPlay(0x6C);
            D_801116FC_pump_pump_away = 144;
        } else {
            func_8010FB70_pump_pump_away(obj);
        }
        obj->func = func_8010FA64_pump_pump_away;
    }
}

void func_8010FCF8_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
    } else {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FC64_pump_pump_away;
    }
}

void func_8010FD34_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() == 0) {
        if (D_801116FC_pump_pump_away > 0) {
            D_801116FC_pump_pump_away--;
        } else {
            D_801116F8_pump_pump_away = 1;
            obj->func = func_8010FC64_pump_pump_away;
        }
    }
}

void func_8010FD94_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away > 0) {
        D_801116FC_pump_pump_away--;
    } else if (func_8010FAA8_pump_pump_away()) {
        GMesCreate(GMES_MES_MG_RECORD);
        D_801116F8_pump_pump_away = 1;
        D_801116FC_pump_pump_away = 15;
        obj->func = func_8010FD34_pump_pump_away;
    } else {
        D_801116FC_pump_pump_away = 0;
        D_801116F8_pump_pump_away = 2;
        obj->func = func_8010FC64_pump_pump_away;
    }
}

void func_8010FE2C_pump_pump_away(omObjData *obj) {
    if (GMesStatGet() == 0) {
        D_801116FC_pump_pump_away = 0xF;
        obj->func = func_8010FD94_pump_pump_away;
    }
}

void func_8010FE6C_pump_pump_away(omObjData *obj) {
    GMesCreate(GMES_MES_16);
    D_801116FC_pump_pump_away = 0x4B;
    HuAudSeqFadeOut(0x78);
    obj->func = func_8010FE2C_pump_pump_away;
}

void func_8010FEB4_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;

    if (player->unk_24 == 2 && D_80111978_pump_pump_away[1].unk_24 == 2) {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FE6C_pump_pump_away;
    }
}

void func_8010FEF8_pump_pump_away(omObjData *obj) {
    if (D_80113530_pump_pump_away.state == -1) {
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FEB4_pump_pump_away;
    }
}

void func_8010FF28_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = D_80111978_pump_pump_away;

    if (player->unk_24 != 0 && D_80111978_pump_pump_away[1].unk_24 != 0) {
        D_80113530_pump_pump_away.state = 1;
        D_801116F8_pump_pump_away = 1;
        obj->func = func_8010FEF8_pump_pump_away;
    }
}

void func_8010FF70_pump_pump_away(omObjData *obj) {
    UnkPumpPumpAwayPlayer *player = &D_80111978_pump_pump_away[0];
    UnkPumpPumpAwayPlayer *other = &D_80111978_pump_pump_away[1];

    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away--;
    } else if (player->unk_14 == 0 && other->unk_14 == 0) {
        if (player->unk_18 == 0.0f && other->unk_18 == 0.0f) {
            D_801116F8_pump_pump_away = 4;
            obj->func = func_8010FE6C_pump_pump_away;
        } else if (player->unk_04 == 10 || other->unk_04 == 10) {
            D_801116F8_pump_pump_away = 1;
            obj->func = func_8010FF28_pump_pump_away;
        }
    }
}

void func_80110034_pump_pump_away(omObjData *obj) {
    s32 i;
    UnkPumpPumpAwayJet *jet;

    D_801116FC_pump_pump_away = 45;
    D_801116F8_pump_pump_away = 1;
    obj->func = func_8010FF70_pump_pump_away;
    if (D_801119E4_pump_pump_away != 0) {
        for (i = 0; i < 4; i++) {
            jet = &D_80113438_pump_pump_away[i];
            if (jet->unk_00 != -1 && jet->unk_20 == 0) {
                omVibrate((s16)jet->unk_04->work[0], 2, 2, 20);
            }
        }
    }
}

void func_801100F0_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayJet *jet;
    UnkPumpPumpAwayPlayer *player;
    UnkPumpPumpAwayPlayer *other;
    UnkPumpPumpAwayPlayer *first;
    UnkPumpPumpAwayPlayer *team;

    for (i = 0; i < 4; i++) {
        jet = &D_80113438_pump_pump_away[i];
        team = &D_80111978_pump_pump_away[jet->unk_04->work[1]];
        team->unk_14 += jet->unk_10;
    }

    first = &D_80111978_pump_pump_away[0];
    player = D_80111978_pump_pump_away;
    other = &player[1];
    if (first->unk_14 == other->unk_14) {
        if (first->unk_14 != 0) {
            if (rand8() & 1) {
                first->unk_14 += 40;
            } else {
                other->unk_14 += 40;
            }
        } else {
            other->unk_14 = 0;
            player->unk_14 = 0;
        }
    } else {
        if (((player->unk_14 - other->unk_14 >= 0) ? player->unk_14 - other->unk_14 : other->unk_14 - player->unk_14) < 40) {
            if (player->unk_14 > other->unk_14) {
                player->unk_14 = other->unk_14 + 40;
            } else {
                other->unk_14 = player->unk_14 + 40;
            }
        }
    }
    if (player->unk_14 != 0 && other->unk_14 != 0) {
        D_801119E4_pump_pump_away = 1;
    }
}

void func_80110260_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away--;
    } else {
        obj->func = func_80110034_pump_pump_away;
    }
}

void func_80110290_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away--;
    } else {
        D_801116FC_pump_pump_away = 0;
        func_801100F0_pump_pump_away();
        obj->func = func_80110260_pump_pump_away;
    }
}

void func_801102E4_pump_pump_away(omObjData *obj) {
    if (D_801116FC_pump_pump_away != 0) {
        D_801116FC_pump_pump_away--;
        func_8003F578_main((D_801116FC_pump_pump_away + 29) / 30);
    } else {
        func_8003F5C0_main();
        D_801116FC_pump_pump_away = 90;
        obj->func = func_80110290_pump_pump_away;
        D_801116F8_pump_pump_away = 1;
        D_800D6A58_main = 1;
    }
}

void func_8011038C_pump_pump_away(omObjData *obj) {
    GMesCreate(GMES_MES_TIMER, 0xA, 0xA0, 0x1C);
    D_801116FC_pump_pump_away = 0x12D;
    obj->func = func_801102E4_pump_pump_away;
}

void func_801103D8_pump_pump_away(omObjData *obj) {
    if (++D_80111118_pump_pump_away == 0x21) {
        HuAudSeqPlay(0x2E);
    }
    if (GMesStatGet() == 0 || (GMesStatGet() & 2)) {
        obj->func = func_8011038C_pump_pump_away;
        D_801116F8_pump_pump_away = 1;
    }
}

void func_80110458_pump_pump_away(omObjData *obj) {
    GMesCreate(5);
    obj->func = func_801103D8_pump_pump_away;
    D_801116F8_pump_pump_away = 1;
}

void func_80110498_pump_pump_away(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_801104BC_pump_pump_away(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_80110498_pump_pump_away;
    }
}

void func_801104F4_pump_pump_away(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 0x14);
        obj->func = func_801104BC_pump_pump_away;
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
    }
}

void func_8011054C_pump_pump_away(void) {
    D_801116F4_pump_pump_away += D_801116F8_pump_pump_away;
    D_801116F8_pump_pump_away = 0;
}

void func_80110574_pump_pump_away(omObjData *obj) {
    func_8011054C_pump_pump_away();
    switch (D_801116F4_pump_pump_away) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            WipeCreateOut(0, 0x14);
            obj->func = func_801104BC_pump_pump_away;
            break;
    }
}

void func_801105D8_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayJet *jet;

    for (i = 0, jet = D_80113438_pump_pump_away; i < 4; i++) {
        jet[i].unk_00 = -1;
        jet[i].unk_04 = 0;
        jet[i].unk_08 = 0;
        jet[i].unk_0C = 0;
        jet[i].unk_10 = 0;
        jet[i].unk_14 = 0.0f;
        jet[i].unk_1C = 0;
        jet[i].unk_20 = 0;
        jet[i].unk_24 = 0;
        jet[i].unk_30 = 0;
    }
}

void func_80110638_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAway *entry;

    for (i = 0, entry = D_80113570_pump_pump_away; i < 2; i++) {
        entry[i].unk_00 = -1;
    }
}

void func_8011066C_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayHose *entry;

    for (i = 0, entry = D_801117C0_pump_pump_away; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
}

void func_801106AC_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayPlayer *entry;

    for (i = 0; i < 2; i++) {
        entry = &D_80111978_pump_pump_away[i];
        entry->unk_00 = -1;
        entry->unk_04 = 0;
        entry->unk_08 = 0;
        entry->unk_0C = 0;
        entry->unk_10 = 0;
        entry->unk_14 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_2C = 0;
    }
}

void func_80110718_pump_pump_away(void) {
    s32 i;
    s32 j;
    UnkPumpPumpAwayNode *entry;

    for (i = 0; i < 2; i++) {
        entry = &D_80111758_pump_pump_away[i];
        entry->unk_00 = -1;
        entry->unk_04 = 0;
        entry->unk_0C = 0;
        entry->unk_08 = 0;
        entry->unk_30 = 0;
        for (j = 0; j < 8; j++) {
            entry->unk_10[j] = 0;
        }
    }
}

void func_8011078C_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayState *entry;

    for (i = 0, entry = D_80113400_pump_pump_away; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
    }
}

void func_801107C4_pump_pump_away(void) {
    D_80113518_pump_pump_away = -1;
    D_8011351C_pump_pump_away = -1;
    D_80113520_pump_pump_away = 0.0f;
}

void func_801107E4_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayParticle *entry;

    for (i = 0, entry = D_801117E0_pump_pump_away; i < 20; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
}

void func_80110824_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAway *entry;

    for (i = 0, entry = D_80113418_pump_pump_away; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
    D_801116EA_pump_pump_away = 0;
}

void func_80110868_pump_pump_away(void) {
    D_801135D8_pump_pump_away.state = -1;
    D_801135DC_pump_pump_away = 0;
    D_801135E0_pump_pump_away = 0;
}

void func_80110888_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwayNozzle *entry;

    for (i = 0, entry = D_80111920_pump_pump_away; i < 4; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0.0f;
        entry[i].unk_10 = 0.0f;
    }
    D_801116EC_pump_pump_away = 0;
}

void func_801108D8_pump_pump_away(void) {
    s32 i;
    PumpPumpAwayMovingEffect *entry;

    for (i = 0, entry = D_801135E8_pump_pump_away; i < 4; i++) {
        entry[i].state = -1;
        entry[i].hidden = 0;
        entry[i].direction = 0;
        entry[i].speed = 0.0f;
    }
    D_801116EE_pump_pump_away = 0;
}

void func_8011091C_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwaySpray *entry;

    for (i = 0, entry = D_80111710_pump_pump_away; i < 6; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 1.0f;
    }
    D_801116F0_pump_pump_away = 0;
}

void func_8011096C_pump_pump_away(void) {
    s32 i;
    UnkPumpPumpAwaySpray *entry;

    for (i = 0, entry = D_801119E8_pump_pump_away; i < 6; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 1.0f;
    }
    D_801116F2_pump_pump_away = 0;
}

void func_801109BC_pump_pump_away(void) {
    D_801116F4_pump_pump_away = 0;
    D_801116F8_pump_pump_away = 0;
    D_801116FC_pump_pump_away = 0;
    D_80111700_pump_pump_away = 0;
    D_80111704_pump_pump_away = 0;
    D_80111708_pump_pump_away = 30;
    D_801119E4_pump_pump_away = 0;
    func_801105D8_pump_pump_away();
    func_80110638_pump_pump_away();
    func_8011066C_pump_pump_away();
    func_801106AC_pump_pump_away();
    func_80110718_pump_pump_away();
    func_8011078C_pump_pump_away();
    func_801107C4_pump_pump_away();
    func_801107E4_pump_pump_away();
    func_80110824_pump_pump_away();
    func_80110868_pump_pump_away();
    func_80110888_pump_pump_away();
    func_801108D8_pump_pump_away();
    func_8011091C_pump_pump_away();
    func_8011096C_pump_pump_away();
}

void func_80110A78_pump_pump_away(void) {
    func_801109BC_pump_pump_away();
    func_8010745C_pump_pump_away();
    func_801066F0_pump_pump_away();
    func_80106894_pump_pump_away();
    func_80106A38_pump_pump_away();
    func_8010CBF0_pump_pump_away();
    func_80107E5C_pump_pump_away();
    func_80108504_pump_pump_away();
    func_8010B5D4_pump_pump_away();
    func_80109B48_pump_pump_away();
    func_80109470_pump_pump_away();
    func_80109E3C_pump_pump_away();
    func_80108FA8_pump_pump_away();
    func_8010D458_pump_pump_away();
    func_8010D6C0_pump_pump_away();
    func_8010E098_pump_pump_away();
    func_8010E65C_pump_pump_away();
    func_8010EB68_pump_pump_away();
    func_8010F20C_pump_pump_away();
    func_8010F8A4_pump_pump_away();
    func_801078B4_pump_pump_away();
}

void func_80110B34_pump_pump_away(omObjData *obj) {
    func_80110A78_pump_pump_away();
    WipeCreateIn(0xFF, 0x10);
    obj->func = func_80110574_pump_pump_away;
    omAddObj(0x32, 0, 0, -1, func_8010F900_pump_pump_away);
    omAddObj(0x320, 0, 0, -1, func_80110458_pump_pump_away);
}

void func_80110BB0_pump_pump_away(void) {
}

void func_80110BB8_pump_pump_away(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8011111C_pump_pump_away[i].scissorX, D_8011111C_pump_pump_away[i].scissorY,
                   D_8011111C_pump_pump_away[i].scissorWidth, D_8011111C_pump_pump_away[i].scissorHeight);
        ViewportSet(i, D_8011111C_pump_pump_away[i].viewportScale.x, D_8011111C_pump_pump_away[i].viewportScale.y,
                    D_8011111C_pump_pump_away[i].viewportScale.z, D_8011111C_pump_pump_away[i].viewportTranslate.x,
                    D_8011111C_pump_pump_away[i].viewportTranslate.y, D_8011111C_pump_pump_away[i].viewportTranslate.z);
        Hu3DCamSetPerspective(i, D_8011111C_pump_pump_away[i].fov, 80.0f, 8000.0f);
    }
}

void func_80110D28_pump_pump_away(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(100);
    omInitObjMan(100, 0);
    func_8004A208_main();
    func_80110BB8_pump_pump_away();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 144, 144, 144);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 255, 255, 255);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(2, 255, 255, 255);
    HmfLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_801116D8_pump_pump_away, 0);
    func_80045010_main(D_801116D8_pump_pump_away, 1);
    omAddObj(1000, 0, 0, -1, func_80110B34_pump_pump_away);
    omAddObj(1000, 0, 0, -1, func_801104F4_pump_pump_away);
    func_80105C54_pump_pump_away();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0D_pump_pump_away/16F670", D_801116D8_pump_pump_away);
