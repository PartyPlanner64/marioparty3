#include "common.h"
#include "math.h"
#include "overlays/minigame.h"

// One entry of the 50 entry object table at D_8010D260_three_door_monty.
// Layout derived from the table clear in func_80105A74_three_door_monty.
typedef struct {
    /* 0x00 */ omObjData *obj;
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
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} ThreeDoorMontyEntry; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} ThreeDoorMontyCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[3];
} ThreeDoorMontyBssEC48; // sizeof 0x8

extern u8 D_800D6A90_main;
extern s32 D_800A178C_main[][6];
extern const s16 D_8010D228_three_door_monty[];
// obj of D_8010D260_three_door_monty[8], accessed through a separate symbol.
extern omObjData *D_8010D680_three_door_monty;
// unk_18 of D_8010D260_three_door_monty[8], accessed through a separate symbol.
extern f32 D_8010D698_three_door_monty;
// obj of D_8010D260_three_door_monty[12], accessed through a separate symbol.
extern omObjData *D_8010D890_three_door_monty;
// unk_18 of D_8010D260_three_door_monty[12], accessed through a separate symbol.
extern f32 D_8010D8A8_three_door_monty;
extern u8 D_8010EC47_three_door_monty; // low byte of D_8010EC46_three_door_monty
extern s16 D_8010EC48_three_door_monty;    // threeDoorMontyBssEC48.unk_00
extern s16 D_8010EC4A_three_door_monty[3]; // threeDoorMontyBssEC48.unk_02

// walking speeds, indexed by obj->work[0]
f32 D_8010CD10_three_door_monty[3] = { 13.0f, 14.0f, 15.0f };
f32 D_8010CD1C_three_door_monty[3] = { 20.0f, 21.0f, 22.0f };
s32 D_8010CD28_three_door_monty[3][2] = {
    { 1, 6 },
    { 143, 145 },
    { 199, 199 },
};
Vec2f D_8010CD40_three_door_monty[3] = {
    { -345.0f, -775.0f },
    { 0.0f, -775.0f },
    { 345.0f, -775.0f },
};
s32 D_8010CD58_three_door_monty[3] = { 7, 8, 9 };
s32 D_8010CD64_three_door_monty[4][4] = {
    { 44, 54, 64, 74 },
    { 108, 118, 128, 138 },
    { 172, 182, 192, 202 },
    { 236, 246, 256, 266 },
};
// per-character voice bank
s32 D_8010CDA4_three_door_monty[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 D_8010CDC4_three_door_monty[2][2] = { { 99, 51 }, { 212, 51 } };
s32 D_8010CDCC_three_door_monty = 0;
ThreeDoorMontyCamera D_8010CDD0_three_door_monty[3] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
};

s16 D_8010D230_three_door_monty BSS;
s16 D_8010D232_three_door_monty BSS;
u16 D_8010D234_three_door_monty[2] BSS;
void *D_8010D238_three_door_monty[3] BSS;
s16 D_8010D244_three_door_monty[4] BSS;
HuSprAnimData *D_8010D24C_three_door_monty BSS;
s16 D_8010D250_three_door_monty BSS;
s16 D_8010D252_three_door_monty BSS;
s16 D_8010D254_three_door_monty BSS;
s16 D_8010D256_three_door_monty BSS;
s16 D_8010D258_three_door_monty BSS;
u8 D_8010D25C_three_door_monty[4] BSS; /* Unreferenced. */
ThreeDoorMontyEntry D_8010D260_three_door_monty[50] BSS;
HuSprAnimData *D_8010EC28_three_door_monty[2] BSS;
u8 D_8010EC30_three_door_monty BSS;
s16 D_8010EC32_three_door_monty BSS;
HuSprAnimData *D_8010EC34_three_door_monty BSS;
u16 D_8010EC38_three_door_monty BSS;
s16 D_8010EC3A_three_door_monty BSS;
s16 D_8010EC3C_three_door_monty BSS;
s16 D_8010EC3E_three_door_monty BSS;
s16 D_8010EC40_three_door_monty BSS;
u8 D_8010EC42_three_door_monty BSS;
s16 D_8010EC44_three_door_monty BSS;
s16 D_8010EC46_three_door_monty BSS;
ThreeDoorMontyBssEC48 threeDoorMontyBssEC48 BSS;
s16 D_8010EC50_three_door_monty BSS;

void func_8010642C_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed);
void func_801071F4_three_door_monty(omObjData *obj);
void func_801071FC_three_door_monty(omObjData *);
void func_8010CBBC_three_door_monty(void);
void func_80106868_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2);
void func_80106B98_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2);
void func_80106EDC_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2);
void func_80107384_three_door_monty(omObjData *obj);
void func_8010742C_three_door_monty(omObjData *);
void func_80109594_three_door_monty(omObjData *);
void func_80108034_three_door_monty(omObjData *obj);
void func_80108C28_three_door_monty(omObjData *obj);
void func_8010916C_three_door_monty(omObjData *obj);
void func_8010973C_three_door_monty(omObjData *obj);
void func_8010A678_three_door_monty(omObjData *obj);
void func_8010B138_three_door_monty(omObjData *obj);
void func_8010B7B8_three_door_monty(omObjData *obj);
void func_8010BC08_three_door_monty(omObjData *obj);
void func_8010C390_three_door_monty(omObjData *obj);
void func_8010C8C0_three_door_monty(omObjData *obj);
void func_8010C3E8_three_door_monty(omObjData *obj);
void func_8010B5A8_three_door_monty(void);
void func_8010BD88_three_door_monty(void);
void func_8010C1B4_three_door_monty(void);
void func_80109890_three_door_monty(omObjData *obj);

void func_801059A0_three_door_monty(void) {
    func_8010CBBC_three_door_monty();
}

f32 func_801059BC_three_door_monty(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_three_door_monty(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_three_door_monty(void) {
    ThreeDoorMontyEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010D260_three_door_monty; i < 50; i++, entry++) {
        entry->obj = NULL;
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
        entry->unk_40[0] = -1;
        entry->unk_40[1] = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68[0] = 0.0f;
        entry->unk_68[1] = 0.0f;
        entry->unk_68[2] = 0.0f;
        entry->unk_68[3] = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105B3C_three_door_monty(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105BB4_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_three_door_monty(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void func_80105CBC_three_door_monty(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)D_800CDA7C_main[conNo] & D_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = func_801059BC_three_door_monty(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = func_801059BC_three_door_monty(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = func_801059BC_three_door_monty(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = func_801059BC_three_door_monty(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & A_BUTTON) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & B_BUTTON) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & D_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 3; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

void func_801062E8_three_door_monty(u8 value) {
    D_8010EC30_three_door_monty = value;
}

void func_801062F4_three_door_monty(omObjData *obj, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

void func_80106390_three_door_monty(omObjData *obj, s16 motion, s16 start, s16 end, s16 *current) {
    if (*current != motion) {
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        func_8001C814_main(obj->model[0], start, end);
        *current = motion;
    }
}

void func_8010642C_three_door_monty(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1;
    f32 dz = z1;
    f32 absDx;
    f32 absDz;
    f32 delta;
    f32 dist;
    f32 step;

    dx -= x0;
    dz -= z0;
    absDx = fabsf(dx);
    absDz = fabsf(dz);

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        dist = absDx;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velZ = -(delta / step);
    } else {
        if (dz >= 0.0f) {
            *velZ = -speed;
        } else {
            *velZ = speed;
        }
        delta = dx;
        dist = absDz;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velX = -(delta / step);
    }
}

void func_8010658C_three_door_monty(omObjData *obj, f32 *outX, f32 *outZ, f32 scale) {
    f32 angle = obj->rot.y;
    s16 quadrant = 0;

    if (angle >= 90.0f) {
        quadrant++;
    }
    if (angle >= 180.0f) {
        quadrant++;
    }
    if (angle >= 270.0f) {
        quadrant++;
    }
    switch (quadrant) {
        case 0:
            *outX = angle * scale;
            *outZ = (90.0f - angle) * scale;
            break;
        case 1:
            angle -= 90.0f;
            *outX = (90.0f - angle) * scale;
            *outZ = -(angle * scale);
            break;
        case 2:
            angle -= 180.0f;
            *outX = -(angle * scale);
            *outZ = -(90.0f - angle) * scale;
            break;
        case 3:
            angle -= 270.0f;
            *outX = -(90.0f - angle) * scale;
            *outZ = angle * scale;
            break;
    }
}

f32 func_801066F4_three_door_monty(f32 current, f32 target, f32 step) {
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (current < target) {
        if (diff > 180.0f) {
            current = func_801059BC_three_door_monty(current, -step);
        } else {
            current = func_801059BC_three_door_monty(current, step);
        }
        return current;
    } else if (target < current) {
        if (diff > 180.0f) {
            current = func_801059BC_three_door_monty(current, step);
        } else {
            current = func_801059BC_three_door_monty(current, -step);
        }
        return current;
    }
    return 0.0f;
}

f32 func_801067C4_three_door_monty(f32 base, f32 *value, f32 step) {
    f32 prev = *value;

    *value = prev - step;
    return base + prev;
}

const char D_8010CEFC_three_door_monty[] = "243_kino_DEF";

void func_801067E0_three_door_monty(omObjData *obj, u8 index) {
    Hu3DAnimKill(D_8010EC3E_three_door_monty);
    D_8010EC3E_three_door_monty = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010D238_three_door_monty[index], 0, D_8010CEFC_three_door_monty);
}

void func_80106868_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, D_8010D24C_three_door_monty->pal);
    x = 0;
    // j is never incremented here, unlike in func_80106B98_three_door_monty.
    for (i = 0, y = 49, j = 0; i < 191; i += 4) {
        i -= (j >= 12);
        gDPLoadTextureTile(gfx++, D_8010D24C_three_door_monty->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void func_80106B98_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, D_8010EC34_three_door_monty->pal);
    x = 0;
    for (i = 0, y = 0, j = 0; i < 51; i += 4, j++) {
        i -= (j >= 12);
        gDPLoadTextureTile(gfx++, D_8010EC34_three_door_monty->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void func_80106EDC_three_door_monty(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 i;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    for (i = 0; i < 2; i++) {
        gDPLoadTLUT_pal16(gfx++, 0, D_8010EC28_three_door_monty[i]->pal);
        gDPLoadTextureTile_4b(gfx++, D_8010EC28_three_door_monty[i]->data, G_IM_FMT_CI, 8, 32, 0, 0, 8, 32, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                              G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 8 << 2, 32 << 2);
        gSPTextureRectangle(gfx++, D_8010CDC4_three_door_monty[i][0] << 2, D_8010CDC4_three_door_monty[i][1] << 2,
                            (D_8010CDC4_three_door_monty[i][0] + 8) << 2, (D_8010CDC4_three_door_monty[i][1] + 32) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfxP = gfx;
}

void func_801071F4_three_door_monty(omObjData *obj) {
}

void func_801071FC_three_door_monty(omObjData *obj) {
    D_8010EC34_three_door_monty = func_80055194_main(func_8000B838_main(0x4C0004));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80106B98_three_door_monty, 2), 2);
    D_8010D24C_three_door_monty = func_80055194_main(func_8000B838_main(0x4C0003));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80106868_three_door_monty, 2), 1);
    D_8010EC28_three_door_monty[0] = func_80055194_main(func_8000B838_main(0x4C0005));
    D_8010EC28_three_door_monty[1] = func_80055194_main(func_8000B838_main(0x4C0006));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80106EDC_three_door_monty, 2), 2);
    obj->model[0] = func_8000B108_main(0x4C000F, 0x289);
    Hu3DModelCameraSet(obj->model[0], 2);
    obj->func = func_801071F4_three_door_monty;
}

void func_80107344_three_door_monty(void) {
    omObjData *obj = omAddObj(0x32, 5, 0xA, -1, func_801071FC_three_door_monty);
    obj->work[0] = 0;
    D_8010D260_three_door_monty[0].obj = obj;
}

void func_80107384_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[12];

    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010D8A8_three_door_monty += 0.05f;
    }
    func_8001E888_main(obj->model[0], entry->unk_18, 0.0f, D_8010D234_three_door_monty[0], D_8010D234_three_door_monty[1],
                       "dammy-castle_ground1_2", 0);
}

void func_8010742C_three_door_monty(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4C000D, 0x2A9);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main("243_water_DEF", D_8010D234_three_door_monty);
    D_8010D260_three_door_monty[12].unk_18 = 0.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelCameraSet(obj->model[0], 1);
    obj->func = func_80107384_three_door_monty;
}

void func_801074B4_three_door_monty(void) {
    omObjData *obj = omAddObj(0x10E, 1, 0, -1, func_8010742C_three_door_monty);
    obj->work[0] = 0;
    D_8010D890_three_door_monty = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_80107500_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[5 + obj->work[0]];
    ThreeDoorMontyEntry *entryA;
    ThreeDoorMontyEntry *entryB;
    omObjData *objA;
    omObjData *objB;
    f32 velX;
    f32 velZ;
    f32 temp;
    s16 door;
    s16 i;
    s16 j;

    velX = velZ = 0.0f;
    switch (entry->unk_06) {
        case 0:
            if (entry->unk_08 == -1) {
                door = (u8)(rand8() % 3);
                while (TRUE) {
                    if (D_8010EC32_three_door_monty < 60) {
                        if (door != entry->unk_0A) {
                            entry->unk_08 = door;
                            break;
                        }
                    } else if (D_8010EC4A_three_door_monty[door] == -1) {
                        entry->unk_08 = door;
                        break;
                    }
                    door++;
                    if (door >= 3) {
                        door = 0;
                    }
                }
            } else {
                entry->unk_0A = entry->unk_08;
                if (D_8010CD40_three_door_monty[entry->unk_08].y + 300.0f < obj->trans.z) {
                    if (D_8010EC32_three_door_monty < 60) {
                        func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                       D_8010CD40_three_door_monty[entry->unk_08].y + 300.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, D_8010CD10_three_door_monty[obj->work[0]]);
                    } else {
                        func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                       D_8010CD40_three_door_monty[entry->unk_08].y + 300.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, D_8010CD1C_three_door_monty[obj->work[0]]);
                    }
                    entry->unk_1C = atan2df(D_8010CD40_three_door_monty[entry->unk_08].x - obj->trans.x,
                                            D_8010CD40_three_door_monty[entry->unk_08].y + 300.0f - obj->trans.z);
                    entry->unk_1C = func_801059BC_three_door_monty(entry->unk_1C, 0.0f);
                    obj->rot.y = func_801066F4_three_door_monty(obj->rot.y, entry->unk_1C, 15.0f);
                    obj->trans.x += velX;
                    obj->trans.z += velZ;
                } else if (D_8010CD40_three_door_monty[entry->unk_08].y - 500.0f < obj->trans.z) {
                    if (D_8010EC32_three_door_monty < 60) {
                        func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                       D_8010CD40_three_door_monty[entry->unk_08].y - 500.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, D_8010CD10_three_door_monty[obj->work[0]]);
                    } else {
                        func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                       D_8010CD40_three_door_monty[entry->unk_08].y - 500.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, D_8010CD1C_three_door_monty[obj->work[0]]);
                    }
                    entry->unk_1C = atan2df(D_8010CD40_three_door_monty[entry->unk_08].x - obj->trans.x,
                                            D_8010CD40_three_door_monty[entry->unk_08].y - 500.0f - obj->trans.z);
                    entry->unk_1C = func_801059BC_three_door_monty(entry->unk_1C, 0.0f);
                    obj->rot.y = func_801066F4_three_door_monty(obj->rot.y, entry->unk_1C, 15.0f);
                    obj->trans.x += velX;
                    obj->trans.z += velZ;
                } else if (D_8010EC32_three_door_monty < 60) {
                    if ((u8)(rand8() % 30) == 0) {
                        entry->unk_06 = 2;
                    }
                } else {
                    D_8010EC4A_three_door_monty[entry->unk_08] = obj->work[0];
                    entry->unk_06 = 5;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (obj->trans.z < D_8010CD40_three_door_monty[entry->unk_08].y + 260.0f) {
                if (D_8010EC32_three_door_monty < 60) {
                    func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                   D_8010CD40_three_door_monty[entry->unk_08].y + 280.0f, obj->trans.x,
                                                   obj->trans.z, &velX, &velZ, D_8010CD10_three_door_monty[obj->work[0]]);
                } else {
                    func_8010642C_three_door_monty(D_8010CD40_three_door_monty[entry->unk_08].x,
                                                   D_8010CD40_three_door_monty[entry->unk_08].y + 280.0f, obj->trans.x,
                                                   obj->trans.z, &velX, &velZ, D_8010CD1C_three_door_monty[obj->work[0]]);
                }
                entry->unk_1C = atan2df(D_8010CD40_three_door_monty[entry->unk_08].x - obj->trans.x,
                                        D_8010CD40_three_door_monty[entry->unk_08].y + 280.0f - obj->trans.z);
                entry->unk_1C = func_801059BC_three_door_monty(entry->unk_1C, 0.0f);
                obj->rot.y = func_801066F4_three_door_monty(obj->rot.y, entry->unk_1C, 15.0f);
                obj->trans.x += velX;
                obj->trans.z += velZ;
            } else {
                door = (u8)(rand8() % 3);
                while (TRUE) {
                    if (D_8010EC32_three_door_monty < 60) {
                        if (door != entry->unk_0A) {
                            entry->unk_08 = door;
                            break;
                        }
                    } else if (D_8010EC4A_three_door_monty[door] == -1) {
                        entry->unk_08 = door;
                        break;
                    }
                    door++;
                    if (door >= 3) {
                        door = 0;
                    }
                }
                switch (entry->unk_0A) {
                    case 0:
                        if (entry->unk_08 == 1) {
                            entry->unk_06 = 3;
                            entry->unk_3C = 4.0f;
                        }
                        if (entry->unk_08 == 2) {
                            entry->unk_06 = 6;
                            entry->unk_3C = 4.0f;
                        }
                        break;
                    case 1:
                        if (entry->unk_08 == 0) {
                            entry->unk_06 = 3;
                            entry->unk_3C = -4.0f;
                        }
                        if (entry->unk_08 == 2) {
                            entry->unk_06 = 3;
                            entry->unk_3C = 4.0f;
                        }
                        break;
                    case 2:
                        if (entry->unk_08 == 0) {
                            entry->unk_06 = 6;
                            entry->unk_3C = -4.0f;
                        }
                        if (entry->unk_08 == 1) {
                            entry->unk_06 = 3;
                            entry->unk_3C = -4.0f;
                        }
                        break;
                }
                entry->unk_16 = 0;
            }
            break;
        case 3:
            entry->unk_0A = entry->unk_08;
            func_8010658C_three_door_monty(obj, &velX, &velZ, 0.17f);
            obj->trans.x += velX;
            obj->trans.z += velZ;
            obj->rot.y = func_801059BC_three_door_monty(obj->rot.y, entry->unk_3C);
            if (++entry->unk_16 >= 46) {
                entry->unk_06 = 0;
            }
            break;
        case 4:
            if (entry->unk_04 != 0) {
                obj->rot.y = func_801066F4_three_door_monty(obj->rot.y, 0.0f, 15.0f);
            }
            if (obj->trans.z < -225.0f) {
                if (D_8010EC32_three_door_monty < 60) {
                    velZ = D_8010CD10_three_door_monty[obj->work[0]];
                } else {
                    velZ = D_8010CD1C_three_door_monty[obj->work[0]];
                }
                obj->trans.z += velZ;
            } else {
                func_801062F4_three_door_monty(obj, 0, 0, 3, 2, &entry->unk_04);
                if (entry->unk_0E >= 5) {
                    entry->unk_06 = 0;
                    entry->unk_0E = 0;
                    func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                } else {
                    entry->unk_0E++;
                }
            }
            break;
        case 5:
            break;
        case 6:
            func_8010658C_three_door_monty(obj, &velX, &velZ, 0.25f);
            obj->trans.x += velX;
            obj->trans.z += velZ;
            obj->rot.y = func_801059BC_three_door_monty(obj->rot.y, entry->unk_3C);
            if (++entry->unk_16 >= 23) {
                entry->unk_06 = 0;
            }
            break;
    }
    if (obj->work[0] == 2) {
        for (i = 0; i < 3; i++) {
            entryA = &D_8010D260_three_door_monty[5 + i];
            objA = entryA->obj;
            for (j = 0; j < 3; j++) {
                entryB = &D_8010D260_three_door_monty[5 + j];
                objB = entryB->obj;
                if (objB->work[0] == objA->work[0]) {
                    continue;
                }
                if (objB->trans.x + 50.0f > objA->trans.x - 50.0f && objB->trans.x - 50.0f < objA->trans.x + 50.0f &&
                    objB->trans.z + 50.0f > objA->trans.z - 50.0f && objB->trans.z - 50.0f < objA->trans.z + 50.0f) {
                    if (objA->trans.z < D_8010CD40_three_door_monty[0].y - 350.0f &&
                        objB->trans.z < D_8010CD40_three_door_monty[0].y - 350.0f) {
                        if (rand8() & 1) {
                            temp = objB->trans.z;
                            objB->trans.z = objA->trans.z;
                            objA->trans.z = temp;
                        }
                        if (objA->trans.z < objB->trans.z) {
                            entryA->unk_06 = 0;
                            entryB->unk_06 = 2;
                        } else {
                            entryA->unk_06 = 2;
                            entryB->unk_06 = 0;
                        }
                    } else if (objB->trans.z < objA->trans.z) {
                        entryA->unk_06 = 4;
                        entryA->unk_08 = -1;
                    } else if (objB->trans.z == objA->trans.z) {
                        if (objB->work[0] > objA->work[0]) {
                            entryA->unk_06 = 4;
                            entryA->unk_08 = -1;
                        } else if (entryA->unk_06 != 3) {
                            entryA->unk_06 = 0;
                            entryA->unk_08 = entryA->unk_0A;
                        }
                    } else if (objB->trans.z > objA->trans.z) {
                        if (entryA->unk_06 != 3) {
                            entryA->unk_06 = 0;
                            entryA->unk_08 = entryA->unk_0A;
                        }
                    }
                }
            }
        }
    }
}

void func_80108034_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[5 + obj->work[0]];
    ThreeDoorMontyEntry *doors[3];
    ThreeDoorMontyEntry *other;
    omObjData *otherObj;
    s16 i;
    s16 busy;

    for (i = 0; i < 3; i++) {
        doors[i] = &D_8010D260_three_door_monty[9 + i];
    }
    switch (D_8010EC30_three_door_monty) {
        case 1:
            busy = 0;
            if (D_8010EC32_three_door_monty >= 15) {
                for (i = 0; i < 3; i++) {
                    if (doors[i]->unk_04 != 5 && doors[i]->unk_04 != 6) {
                        doors[i]->unk_04 = 5;
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_06 != 1) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                if (obj->trans.z < -450.0f) {
                    func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                    obj->trans.z += D_8010CD10_three_door_monty[obj->work[0]];
                }
                for (i = 0; i < 3; i++) {
                    other = &D_8010D260_three_door_monty[5 + i];
                    otherObj = other->obj;
                    if (otherObj->trans.z < -450.0f) {
                        busy = 1;
                    } else {
                        func_801062F4_three_door_monty(otherObj, 0, 0, 3, 2, &other->unk_04);
                    }
                }
                if (busy == 0) {
                    D_8010EC42_three_door_monty = 1;
                }
            }
            break;
        case 3:
            func_80107500_three_door_monty(obj);
            func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
            if (obj->work[0] == 2) {
                if (obj->trans.z < -350.0f) {
                    D_8010D252_three_door_monty = 2;
                }
                switch (D_8010D252_three_door_monty) {
                    case 0:
                        if ((u8)(rand8() % 10) == 0) {
                            D_8010D252_three_door_monty = 1;
                        }
                        break;
                    case 1:
                        D_8010EC46_three_door_monty -= 10;
                        if (D_8010EC46_three_door_monty <= 0) {
                            D_8010EC46_three_door_monty = 0;
                            if ((u8)(rand8() % 50) == 0) {
                                D_8010D252_three_door_monty = 2;
                            }
                        }
                        break;
                    case 2:
                        D_8010EC46_three_door_monty += 10;
                        if (D_8010EC46_three_door_monty >= 255) {
                            D_8010D252_three_door_monty = 0;
                            D_8010EC46_three_door_monty = 255;
                        }
                        break;
                }
                func_8001F9E4_main(obj->model[0], D_8010EC46_three_door_monty);
                func_8001F9E4_main(obj->model[1], D_8010EC46_three_door_monty);
            }
            busy = 0;
            for (i = 0; i < 3; i++) {
                other = &D_8010D260_three_door_monty[5 + i];
                if (other->unk_06 != 5) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                D_8010EC46_three_door_monty = 255;
                func_8001F9E4_main(obj->model[0], D_8010EC46_three_door_monty);
                func_8001F9E4_main(obj->model[1], D_8010EC46_three_door_monty);
                for (i = 0; i < 3; i++) {
                    if (doors[i]->unk_04 != 0 && doors[i]->unk_04 != 1) {
                        doors[i]->unk_04 = 0;
                    }
                    D_8010EC42_three_door_monty = 3;
                }
            }
            break;
        case 4:
            entry->unk_06 = 0;
            break;
        case 7:
            D_8010EC3A_three_door_monty = 0;
            break;
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
            for (i = 0; i < 3; i++) {
                D_8010EC4A_three_door_monty[i] = -1;
            }
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_04 != 5 && doors[i]->unk_04 != 6) {
                    doors[i]->unk_04 = 5;
                }
            }
            obj->rot.y = 0.0f;
            if (obj->work[0] == D_8010D250_three_door_monty) {
                switch (entry->unk_06) {
                    case 0:
                        if (doors[entry->unk_08]->unk_06 == 1) {
                            if (obj->trans.z > -600.0f && D_8010EC3C_three_door_monty == 0) {
                                D_8010EC3C_three_door_monty = 1;
                            }
                            if (obj->trans.z < -450.0f) {
                                func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                                obj->trans.z += D_8010CD10_three_door_monty[obj->work[0]];
                            } else {
                                Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                entry->unk_18 = 20.0f;
                                entry->unk_06 = 1;
                            }
                        }
                        break;
                    case 1:
                        obj->trans.y = func_801067C4_three_door_monty(obj->trans.y, &entry->unk_18, 2.0f);
                        if (obj->trans.y < entry->unk_24) {
                            obj->trans.y = entry->unk_24;
                        }
                        if (obj->trans.y <= entry->unk_24) {
                            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                            func_801062F4_three_door_monty(obj, 0, 0, 3, 2, &entry->unk_04);
                            entry->unk_06 = 2;
                        }
                        break;
                    case 2:
                        D_8010EC3A_three_door_monty = 1;
                        if ((D_8010EC30_three_door_monty == 10 || D_8010EC30_three_door_monty == 11 ||
                             D_8010EC30_three_door_monty == 12 || D_8010EC30_three_door_monty == 13) &&
                            D_8010EC48_three_door_monty == 1) {
                            if (obj->trans.y <= entry->unk_24) {
                                func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                                Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                entry->unk_18 = 20.0f;
                            }
                            obj->trans.y = func_801067C4_three_door_monty(obj->trans.y, &entry->unk_18, 2.0f);
                            if (obj->trans.y < entry->unk_24) {
                                obj->trans.y = entry->unk_24;
                            }
                        }
                        break;
                }
            } else {
                other = &D_8010D260_three_door_monty[5 + D_8010D250_three_door_monty];
                if (other->unk_06 == 2) {
                    switch (entry->unk_06) {
                        case 0:
                            if (doors[entry->unk_08]->unk_06 == 1) {
                                if (obj->trans.z < -450.0f) {
                                    func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                                    obj->trans.z += D_8010CD10_three_door_monty[obj->work[0]];
                                } else {
                                    func_801062F4_three_door_monty(obj, 0, 0, 3, 2, &entry->unk_04);
                                    entry->unk_06 = 1;
                                }
                            }
                            break;
                        case 1:
                            entry->unk_06 = 2;
                            break;
                        case 2:
                            if (D_8010EC30_three_door_monty == 10 || D_8010EC30_three_door_monty == 11 ||
                                D_8010EC30_three_door_monty == 12 || D_8010EC30_three_door_monty == 13) {
                                if (obj->trans.y <= entry->unk_24) {
                                    func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
                                    Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                    entry->unk_18 = 20.0f;
                                }
                                obj->trans.y = func_801067C4_three_door_monty(obj->trans.y, &entry->unk_18, 2.0f);
                                if (obj->trans.y < entry->unk_24) {
                                    obj->trans.y = entry->unk_24;
                                }
                                D_8010EC48_three_door_monty = 1;
                            }
                            break;
                    }
                }
            }
            if (D_8010EC30_three_door_monty == 8 && obj->work[0] == 2) {
                busy = 0;
                for (i = 0; i < 3; i++) {
                    other = &D_8010D260_three_door_monty[5 + i];
                    if (other->unk_06 != 2) {
                        busy = 1;
                    }
                }
                if (busy == 0) {
                    for (i = 0; i < 3; i++) {
                        other = &D_8010D260_three_door_monty[5 + i];
                        other->unk_06 = 0;
                        other->unk_08 = -1;
                    }
                    D_8010EC42_three_door_monty = 8;
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    if (entry->unk_18 > 0.0f) {
        entry->unk_20 -= 0.02f;
    } else if (entry->unk_18 < 0.0f) {
        entry->unk_20 += 0.02f;
    }
    if (entry->unk_20 < 0.1f) {
        entry->unk_20 = 0.1f;
    } else if (entry->unk_20 > 1.0f) {
        entry->unk_20 = 1.0f;
    }
    Hu3DModelScaleSet(obj->model[1], entry->unk_20, obj->scale.y, entry->unk_20);
}

void func_80108C28_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[5 + obj->work[0]];

    switch (obj->work[0]) {
        case 0:
            obj->model[0] = func_8000B108_main(0xA0000, 0x2A9);
            func_8000B460_main(obj, 0, D_8010CD28_three_door_monty[obj->work[0]][0] | 0xA0000);
            func_8000B460_main(obj, 1, D_8010CD28_three_door_monty[obj->work[0]][1] | 0xA0000);
            obj->trans.x = D_8010CD40_three_door_monty[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 10.0f;
            obj->trans.z = D_8010CD40_three_door_monty[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 1.0f;
            obj->scale.y = 1.0f;
            obj->scale.z = 1.0f;
            break;
        case 1:
            obj->model[0] = func_8000B108_main(0xA008E, 0x2A9);
            func_8000B460_main(obj, 0, D_8010CD28_three_door_monty[obj->work[0]][0] | 0xA0000);
            func_8000B460_main(obj, 1, D_8010CD28_three_door_monty[obj->work[0]][1] | 0xA0000);
            obj->trans.x = D_8010CD40_three_door_monty[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 30.0f;
            obj->trans.z = D_8010CD40_three_door_monty[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 1.0f;
            obj->scale.y = 1.0f;
            obj->scale.z = 1.0f;
            break;
        case 2:
            obj->model[0] = func_8000B108_main(0xA00C4, 0x2A9);
            func_8000B460_main(obj, 0, D_8010CD28_three_door_monty[obj->work[0]][0] | 0xA0000);
            func_8000B460_main(obj, 1, D_8010CD28_three_door_monty[obj->work[0]][1] | 0xA0000);
            obj->trans.x = D_8010CD40_three_door_monty[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 0.0f;
            obj->trans.z = D_8010CD40_three_door_monty[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 0.52f;
            obj->scale.y = 0.52f;
            obj->scale.z = 0.52f;
            D_8010EC46_three_door_monty = 0xFF;
            func_8001FA68_main(obj->model[0]);
            func_8001F9E4_main(obj->model[0], D_8010EC47_three_door_monty);
            break;
    }
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    if (obj->work[0] == 2) {
        func_8001FA68_main(obj->model[1]);
        func_8001F9E4_main(obj->model[1], D_8010EC47_three_door_monty);
    } else {
        Hu3DModelRemakeStatic(obj->model[1]);
        func_8001C514_main(obj->model[1]);
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    entry->unk_20 = 1.0f;
    Hu3DModelScaleSet(obj->model[1], entry->unk_20, obj->scale.y, entry->unk_20);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    entry->unk_08 = -1;
    Hu3DModelCameraSet(obj->model[0], 2);
    Hu3DModelCameraSet(obj->model[1], 2);
    obj->func = func_80108034_three_door_monty;
}

void func_801090C8_three_door_monty(void) {
    ThreeDoorMontyEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &D_8010D260_three_door_monty[5 + i];
        obj = omAddObj(0x96, 5, 0xA, -1, func_80108C28_three_door_monty);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void func_8010916C_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[8];
    ThreeDoorMontyEntry *doors[3];
    s16 i;
    s16 busy;

    for (i = 0; i < 3; i++) {
        doors[i] = &D_8010D260_three_door_monty[9 + i];
    }
    switch (D_8010EC30_three_door_monty) {
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            busy = 0;
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_06 != 1) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                func_8001C258_main(obj->model[0], 4, 0);
                entry->unk_18 += 0.1f;
                if (entry->unk_18 > 1.0f) {
                    entry->unk_18 = 1.0f;
                    D_8010D250_three_door_monty = (u8)(rand8() % 3);
                    func_801067E0_three_door_monty(obj, D_8010D250_three_door_monty);
                    D_8010EC42_three_door_monty = 4;
                    HuAudFXPlay(0x453);
                    D_8010EC50_three_door_monty = 0;
                }
            }
            break;
        case 5:
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            if (Hu3DData[obj->model[0]].motTime >= 60.0f && D_8010EC50_three_door_monty == 0) {
                HuAudFXPlay(0x453);
                D_8010EC50_three_door_monty = 1;
            }
            if (Hu3DData[obj->model[0]].motTime >= 120.0f && D_8010EC50_three_door_monty == 1) {
                HuAudFXPlay(0x453);
                D_8010EC50_three_door_monty = 2;
            }
            if (Hu3DData[obj->model[0]].motTime >= 180.0f && D_8010EC50_three_door_monty == 2) {
                switch (D_8010D250_three_door_monty) {
                    case 0:
                        HuAudFXPlay(0x455);
                        break;
                    case 1:
                        HuAudFXPlay(0x457);
                        break;
                    case 2:
                        HuAudFXPlay(0x456);
                        break;
                }
                D_8010EC50_three_door_monty = 3;
            }
            if (Hu3DData[obj->model[0]].motTime >= D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
                D_8010EC42_three_door_monty = 5;
            }
            break;
        case 6:
        case 7:
        case 9:
        case 12:
            break;
        case 8:
        case 10:
        case 11:
        case 13:
            if (entry->unk_18 > 0.1f) {
                entry->unk_18 -= 0.1f;
            } else {
                entry->unk_18 = 0.1f;
                func_8001C258_main(obj->model[0], 4, 4);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionSpeedSet(obj->model[0], 0.0f);
            }
            break;
    }
    obj->scale.x = obj->scale.y = entry->unk_18;
}

void func_80109594_three_door_monty(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4C000E, 0x2A9);
    D_8010D238_three_door_monty[0] = DataRead(0x4C0000);
    D_8010D238_three_door_monty[1] = DataRead(0x4C0001);
    D_8010D238_three_door_monty[2] = DataRead(0x4C0002);
    D_8010EC3E_three_door_monty =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, D_8010D238_three_door_monty[0], 0, D_8010CEFC_three_door_monty);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    func_8001C258_main(obj->model[0], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 450.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = D_8010D698_three_door_monty = 0.1f;
    obj->scale.y = D_8010D260_three_door_monty[8].unk_18;
    obj->scale.z = 1.0f;
    Hu3DModelCameraSet(obj->model[0], 2);
    obj->func = func_8010916C_three_door_monty;
}

void func_801096FC_three_door_monty(void) {
    omObjData *obj = omAddObj(0xC8, 5, 0xA, -1, func_80109594_three_door_monty);
    obj->work[0] = 0;
    D_8010D680_three_door_monty = obj;
}

void func_8010973C_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[9 + obj->work[0]];

    switch (entry->unk_04) {
        case 0:
            entry->unk_04 = 1;
            HuAudFXPlay(0x452);
            break;
        case 1:
            if (obj->trans.y > 0.0f) {
                obj->trans.y -= 15.0f;
            }
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
                entry->unk_06 = 0;
            }
            break;
        case 5:
            entry->unk_04 = 6;
            HuAudFXPlay(0x451);
            break;
        case 6:
            if (obj->trans.y < 185.0f) {
                obj->trans.y += 10.0f;
            }
            if (obj->trans.y > 185.0f) {
                obj->trans.y = 185.0f;
                entry->unk_06 = 1;
            }
            break;
    }
}

void func_80109890_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[9 + obj->work[0]];

    switch (obj->work[0]) {
        case 0:
            obj->model[0] = func_8000B108_main(0x4C000C, 0x2B9);
            break;
        case 1:
            obj->model[0] = func_8000B108_main(0x4C000B, 0x2B9);
            break;
        case 2:
            obj->model[0] = func_8000B108_main(0x4C000A, 0x2B9);
            break;
    }
    obj->trans.x = D_8010CD40_three_door_monty[obj->work[0]].x;
    obj->trans.y = 0.0f;
    obj->trans.z = D_8010CD40_three_door_monty[obj->work[0]].y;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.z = 1.0f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelCameraSet(obj->model[0], 2);
    entry->unk_04 = 1;
    obj->func = func_8010973C_three_door_monty;
}

void func_801099EC_three_door_monty(void) {
    ThreeDoorMontyEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &D_8010D260_three_door_monty[9 + i];
        obj = omAddObj(0xFA, 5, 0xA, -1, func_80109890_three_door_monty);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

f32 func_80109A90_three_door_monty(s16 mode, f32 value) {
    f32 result = 0.0f;

    switch (mode) {
        case 1:
            result = rand8() + value;
            break;
        case 2:
            result = rand8() - value;
            break;
        case 3:
            result = rand8() * value;
            break;
        case 4:
            result = rand8() / (s16)value;
            break;
        case 5:
            result = rand8() % (s16)value;
            break;
        case 6:
            if (rand8() % (s16)value == 0) {
                result = 1.0f;
            }
            break;
        case 0:
        default:
            result = rand8();
            break;
    }
    return result;
}

void func_80109C84_three_door_monty(omObjData *obj) {
    s16 choice = 0;
    s16 act = 0;
    s16 door = 0;
    s16 i;

    for (i = 0; i < 3; i++) {
        if (D_8010EC4A_three_door_monty[i] == D_8010D250_three_door_monty) {
            door = i;
        }
    }
    switch (GwPlayer[obj->work[0]].cpu_difficulty) {
        case 0:
            act = func_80109A90_three_door_monty(6, 50.0f);
            choice = func_80109A90_three_door_monty(5, 10.0f);
            break;
        case 1:
            act = func_80109A90_three_door_monty(6, 30.0f);
            choice = func_80109A90_three_door_monty(5, 15.0f);
            break;
        case 2:
            act = func_80109A90_three_door_monty(6, 15.0f);
            choice = func_80109A90_three_door_monty(5, 20.0f);
            break;
        case 3:
            act = func_80109A90_three_door_monty(6, 10.0f);
            choice = func_80109A90_three_door_monty(5, 25.0f);
            break;
    }
    if (D_8010D254_three_door_monty >= 4957) {
        act = 1;
    }
    if (act != 0) {
        switch (choice) {
            case 0:
                D_800D5558_main[obj->work[3]] |= 0x2000;
                break;
            case 1:
                D_800D5558_main[obj->work[3]] |= 0x4000;
                break;
            case 2:
                D_800D5558_main[obj->work[3]] |= 0x8000;
                break;
            default:
                if (door == 0) {
                    D_800D5558_main[obj->work[3]] |= 0x2000;
                } else if (door == 1) {
                    D_800D5558_main[obj->work[3]] |= 0x4000;
                } else if (door == 2) {
                    D_800D5558_main[obj->work[3]] |= 0x8000;
                }
                break;
        }
    }
}

void func_80109F0C_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[1 + obj->work[0]];

    if (entry->unk_14 == 0) {
        return;
    }
    if (GwPlayer[obj->work[0]].stat & 1) {
        func_80105B3C_three_door_monty(obj->work[0]);
        if (D_8010D254_three_door_monty >= 165) {
            func_80109C84_three_door_monty(obj);
        }
    }
    if (entry->unk_06 != -1) {
        return;
    }
    if (D_800D5558_main[obj->work[3]] & 0x8000) {
        if (D_8010D254_three_door_monty >= 34) {
            entry->unk_12 = D_8010D254_three_door_monty - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = D_8010D254_three_door_monty;
        }
        func_801062F4_three_door_monty(obj, 4, 0, 3, 0, &entry->unk_04);
        func_8001C258_main(obj->model[2], 4, 0);
        func_8001C258_main(obj->model[3], 4, 4);
        func_8001C258_main(obj->model[4], 4, 4);
        entry->unk_06 = 2;
    }
    if (D_800D5558_main[obj->work[3]] & 0x4000) {
        if (D_8010D254_three_door_monty >= 34) {
            entry->unk_12 = D_8010D254_three_door_monty - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = D_8010D254_three_door_monty;
        }
        func_801062F4_three_door_monty(obj, 4, 0, 3, 0, &entry->unk_04);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[3], 4, 0);
        func_8001C258_main(obj->model[4], 4, 4);
        entry->unk_06 = 1;
    }
    if (D_800D5558_main[obj->work[3]] & 0x2000) {
        if (D_8010D254_three_door_monty >= 34) {
            entry->unk_12 = D_8010D254_three_door_monty - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = D_8010D254_three_door_monty;
        }
        func_801062F4_three_door_monty(obj, 4, 0, 3, 0, &entry->unk_04);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001C258_main(obj->model[3], 4, 4);
        func_8001C258_main(obj->model[4], 4, 0);
        entry->unk_06 = 0;
    }
}

void func_8010A27C_three_door_monty(void) {
    ThreeDoorMontyEntry *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 j;
    s16 found;
    f32 best;

    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010D260_three_door_monty[1 + i];
        // objs is never read in this function; pointer form avoids a
        // set-but-unused warning without changing codegen.
        *(objs + i) = entries[i]->obj;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_14 == 1 && entries[i]->unk_06 == -1) {
            entries[i]->unk_16 = D_8010EC38_three_door_monty;
            entries[i]->unk_14 = 0;
            entries[i]->unk_08 = 1;
            D_8010D230_three_door_monty++;
            found = 1;
        }
        if (entries[i]->unk_14 == 1 &&
            D_8010EC4A_three_door_monty[entries[i]->unk_06] != D_8010D250_three_door_monty) {
            entries[i]->unk_16 = D_8010EC38_three_door_monty;
            entries[i]->unk_14 = 0;
            entries[i]->unk_08 = 2;
            D_8010D230_three_door_monty++;
            found = 1;
        }
    }
    if (found == 1) {
        D_8010EC38_three_door_monty--;
    }
    if (D_8010D230_three_door_monty < 3) {
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1) {
                    best = -100.0f;
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1 && best <= (s16)(entries[i]->unk_12 / 10)) {
                    best = (s16)(entries[i]->unk_12 / 10);
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1 && (s16)(entries[i]->unk_12 / 10) == best) {
                    entries[i]->unk_16 = D_8010EC38_three_door_monty;
                    entries[i]->unk_14 = 0;
                    entries[i]->unk_08 = 3;
                    D_8010D230_three_door_monty++;
                }
            }
            D_8010EC38_three_door_monty--;
        }
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_08 == 3 && (s16)(entries[i]->unk_12 / 10) == best) {
                entries[i]->unk_14 = 1;
                entries[i]->unk_08 = 0;
                D_8010D230_three_door_monty--;
            }
        }
    }
}

void func_8010A678_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[1 + obj->work[0]];
    ThreeDoorMontyEntry *other;
    s16 i;
    s16 found;

    switch (D_8010EC30_three_door_monty) {
        case 1:
        case 2:
            break;
        case 3:
            if (obj->rot.y >= 0.0f && obj->rot.y < 180.0f) {
                obj->rot.y = func_801059BC_three_door_monty(obj->rot.y, 9.0f);
                func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
            } else {
                obj->rot.y = 180.0f;
                func_801062F4_three_door_monty(obj, 2, 0, 3, 2, &entry->unk_04);
            }
            break;
        case 4:
        case 5:
            if (obj->rot.y > 0.0f && obj->rot.y < 270.0f) {
                obj->rot.y = func_801059BC_three_door_monty(obj->rot.y, -9.0f);
                func_801062F4_three_door_monty(obj, 1, 0, 3, 2, &entry->unk_04);
            } else {
                obj->rot.y = 0.0f;
                func_801062F4_three_door_monty(obj, 3, 0, 20, 2, &entry->unk_04);
            }
            entry->unk_06 = -1;
            break;
        case 6:
            if (D_8010D254_three_door_monty >= 33 && D_8010D254_three_door_monty <= 4957) {
                func_80109F0C_three_door_monty(obj);
            }
            if (obj->work[0] == 3) {
                found = FALSE;
                for (i = 0; i < 4; i++) {
                    other = &D_8010D260_three_door_monty[1 + i];
                    if (other->unk_14 == 1 && other->unk_06 == -1) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    D_8010EC44_three_door_monty = 1;
                }
            }
            break;
        case 7:
            if (obj->work[0] == 3) {
                func_8010A27C_three_door_monty();
                D_8010EC42_three_door_monty = 7;
                D_8010D258_three_door_monty = 0;
                for (i = 0; i < 4; i++) {
                    other = &D_8010D260_three_door_monty[1 + i];
                    if (other->unk_08 == 1 || other->unk_08 == 2 || other->unk_08 == 3) {
                        D_8010D258_three_door_monty++;
                    }
                }
                if (D_8010D258_three_door_monty >= 4) {
                    for (i = 0; i < 4; i++) {
                        other = &D_8010D260_three_door_monty[1 + i];
                        other->unk_16 = 99;
                    }
                }
            }
            break;
        case 8:
        case 9:
            if (D_8010D230_three_door_monty < 3) {
                if (entry->unk_14 == 0) {
                    switch (entry->unk_08) {
                        case 1:
                        case 2:
                            if (D_8010EC3C_three_door_monty >= 2) {
                                for (i = 0; i < 3; i++) {
                                    func_8001C258_main(obj->model[2 + i], 4, 4);
                                }
                                func_80106390_three_door_monty(obj, 6, 2, 0, &entry->unk_04);
                                if (D_8010D244_three_door_monty[obj->work[0]] == 0) {
                                    PlayerFXPlay(0x286, obj->work[0]);
                                    D_8010D244_three_door_monty[obj->work[0]] = 1;
                                }
                                if (entry->unk_04 == 6) {
                                    if (Hu3DData[obj->model[0]].motTime >=
                                        D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
                                        entry->unk_08 = 10;
                                    }
                                }
                            }
                            break;
                        case 3:
                            if (D_8010EC3C_three_door_monty >= 2) {
                                for (i = 0; i < 3; i++) {
                                    func_8001C258_main(obj->model[2 + i], 4, 4);
                                }
                                func_80106390_three_door_monty(obj, 6, 2, 0, &entry->unk_04);
                                if (D_8010D244_three_door_monty[obj->work[0]] == 0) {
                                    PlayerFXPlay(0x286, obj->work[0]);
                                    D_8010D244_three_door_monty[obj->work[0]] = 1;
                                }
                                if (entry->unk_04 == 6) {
                                    if (Hu3DData[obj->model[0]].motTime >=
                                        D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
                                        entry->unk_08 = 10;
                                    }
                                }
                            }
                            break;
                        case 10:
                            func_801062F4_three_door_monty(obj, 1, 0, 30, 2, &entry->unk_04);
                            if (obj->trans.z < 500.0f) {
                                obj->trans.z += 10.0f;
                                obj->trans.y -= 3.0f;
                            } else {
                                obj->trans.z = 500.0f;
                                entry->unk_08 = 50;
                            }
                            break;
                        case 50:
                            break;
                    }
                }
                if (D_8010EC30_three_door_monty == 9) {
                    if (obj->work[0] == 3) {
                        found = FALSE;
                        for (i = 0; i < 4; i++) {
                            other = &D_8010D260_three_door_monty[1 + i];
                            if (other->unk_14 == 0 && other->unk_08 != 50) {
                                found = TRUE;
                            }
                        }
                        if (!found) {
                            D_8010EC42_three_door_monty = 9;
                        }
                    }
                }
            }
            break;
        case 10:
        case 11:
            break;
        case 12:
            if (entry->unk_14 != 0) {
                if (D_8010EC3C_three_door_monty >= 2) {
                    for (i = 0; i < 3; i++) {
                        func_8001C258_main(obj->model[2 + i], 4, 4);
                    }
                    func_801062F4_three_door_monty(obj, 5, 0, 30, 0, &entry->unk_04);
                    if (D_8010D244_three_door_monty[obj->work[0]] == 0) {
                        func_80045ED0_main((D_8010CDA4_three_door_monty[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                        D_8010D244_three_door_monty[obj->work[0]] = 1;
                    }
                }
            }
            if (entry->unk_14 == 0) {
                switch (entry->unk_08) {
                    case 1:
                    case 2:
                        if (D_8010EC3C_three_door_monty >= 2) {
                            for (i = 0; i < 3; i++) {
                                func_8001C258_main(obj->model[2 + i], 4, 4);
                            }
                            func_80106390_three_door_monty(obj, 6, 2, 0, &entry->unk_04);
                            if (D_8010D230_three_door_monty >= 4) {
                                if (D_8010D244_three_door_monty[obj->work[0]] == 0) {
                                    D_8010D244_three_door_monty[obj->work[0]] = 1;
                                }
                            }
                            if (entry->unk_04 == 6) {
                                if (Hu3DData[obj->model[0]].motTime >=
                                    D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
                                    entry->unk_08 = 10;
                                }
                            }
                        }
                        break;
                    case 3:
                        if (D_8010EC3C_three_door_monty >= 2) {
                            for (i = 0; i < 3; i++) {
                                func_8001C258_main(obj->model[2 + i], 4, 4);
                            }
                            func_80106390_three_door_monty(obj, 6, 2, 0, &entry->unk_04);
                            if (D_8010D230_three_door_monty >= 4) {
                                if (D_8010D244_three_door_monty[obj->work[0]] == 0) {
                                    func_80045ED0_main(
                                        (D_8010CDA4_three_door_monty[GwPlayer[obj->work[0]].chr] << 16) | 0x36);
                                    D_8010D244_three_door_monty[obj->work[0]] = 1;
                                }
                            }
                            if (entry->unk_04 == 6) {
                                if (Hu3DData[obj->model[0]].motTime >=
                                    D_800CCF58_main[Hu3DData[obj->model[0]].motId].unk02) {
                                    entry->unk_08 = 10;
                                }
                            }
                        }
                        break;
                    case 10:
                        break;
                    case 50:
                        break;
                }
            }
            break;
    }
    if (GwPlayer[obj->work[0]].chr != 5) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z - 20.0f);
    }
}

void func_8010B138_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[1 + obj->work[0]];
    s8 chr = GwPlayer[obj->work[0]].chr;
    s16 i;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2A9);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x66));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x8A));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x36));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    entry->unk_04 = 0;
    obj->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    switch (obj->work[1]) {
        case 0:
            obj->trans.x = -325.0f;
            break;
        case 1:
            obj->trans.x = -110.0f;
            break;
        case 2:
            obj->trans.x = 110.0f;
            break;
        case 3:
            obj->trans.x = 325.0f;
            break;
    }
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    if (chr != 5) {
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z + 30.0f);
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    for (i = 0; i < 3; i++) {
        obj->model[2 + i] = func_8000B108_main(D_8010CD58_three_door_monty[i] | 0x4C0000, 0xA9);
        Hu3DModelHookSet(obj->model[2 + i], obj->model[0], "item_hook");
        func_8001C258_main(obj->model[2 + i], 0x4000, 0x4000);
        if (i == 0) {
            func_8001C258_main(obj->model[2], 4, 0);
        } else {
            func_8001C258_main(obj->model[2 + i], 4, 4);
        }
    }
    Hu3DModelCameraSet(obj->model[0], 4);
    Hu3DModelCameraSet(obj->model[1], 4);
    Hu3DModelCameraSet(obj->model[2], 4);
    Hu3DModelCameraSet(obj->model[3], 4);
    Hu3DModelCameraSet(obj->model[4], 4);
    entry->unk_14 = 1;
    obj->func = func_8010A678_three_door_monty;
}

void func_8010B5A8_three_door_monty(void) {
    ThreeDoorMontyEntry *entry;
    omObjData *obj;
    s16 order[4];
    s16 i;
    s16 j;
    s16 idx;
    u16 player;

    for (i = 0; i < 4; i++) {
        order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                player = 0;
                break;
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
            default:
                player = 0;
                break;
        }
        entry = &D_8010D260_three_door_monty[1 + i];
        obj = omAddObj(100, 10, 60, -1, func_8010B138_three_door_monty);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        entry->obj = obj;
        idx = rand8() % (4 - i);
        obj->work[1] = order[idx];
        order[idx] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void func_8010B7B8_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[obj->work[0] * 4 + 13 + obj->work[1]];
    ThreeDoorMontyEntry *entries[4];
    omObjData *objs[4];
    s16 count;
    u8 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010D260_three_door_monty[1 + i];
        // objs is never read in this function; pointer form avoids a
        // set-but-unused warning without changing codegen.
        *(objs + i) = entries[i]->obj;
    }
    switch (D_8010EC30_three_door_monty) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            espDispOff(entry->unk_40[1]);
            break;
        case 7:
            espDispOff(entry->unk_40[1]);
            if (obj->work[1] != 1) {
                entry->unk_04 = (u8)(rand8() % 10);
            }
            D_8010EC40_three_door_monty = 0;
            break;
        case 8:
        case 10:
        case 11:
        case 13:
            count = 0;
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_08 == 0 || entries[i]->unk_08 == 3) {
                    count++;
                }
            }
            if (count >= 2) {
                if ((entries[obj->work[0]]->unk_08 == 0 || entries[obj->work[0]]->unk_08 == 3) &&
                    D_8010EC3C_three_door_monty > 0) {
                    espDispOn(entry->unk_40[1]);
                    if (D_8010EC40_three_door_monty == 0) {
                        D_8010D256_three_door_monty = HuAudFXPlay(0x454);
                        D_8010EC40_three_door_monty = 1;
                    }
                    if (obj->work[1] == 1) {
                        // The do-while(0) raises entry's loop-weighted ref count so it
                        // outranks obj in register allocation (entry in s0, obj in s1).
                        do {
                            entry->unk_04 = 11;
                        } while (0);
                        func_8000BD50_main(entry->unk_40[1], 11);
                    } else {
                        entry->unk_04++;
                        if (entry->unk_04 >= 10) {
                            entry->unk_04 = 0;
                        }
                        switch (obj->work[1]) {
                            case 0:
                                if (D_8010EC32_three_door_monty < 50) {
                                    entry->unk_04 = entries[obj->work[0]]->unk_12 / 1000;
                                }
                                break;
                            case 2:
                                if (D_8010EC32_three_door_monty < 40) {
                                    entry->unk_04 = (s16)(entries[obj->work[0]]->unk_12 / 100) % 10;
                                }
                                break;
                            case 3:
                                if (D_8010EC32_three_door_monty < 30) {
                                    entry->unk_04 = (s16)(entries[obj->work[0]]->unk_12 / 10) % 10;
                                    if (D_8010EC40_three_door_monty == 1) {
                                        HuAudFXStop(D_8010D256_three_door_monty);
                                        D_8010EC40_three_door_monty = 2;
                                    }
                                    if (D_8010EC3C_three_door_monty == 1) {
                                        D_8010EC3C_three_door_monty = 2;
                                    }
                                }
                                break;
                        }
                        func_8000BD50_main(entry->unk_40[1], entry->unk_04);
                    }
                }
            } else if (D_8010EC3C_three_door_monty == 1) {
                D_8010EC3C_three_door_monty = 2;
            }
            break;
    }
}

void func_8010BC08_three_door_monty(omObjData *obj) {
    ThreeDoorMontyEntry *entry = &D_8010D260_three_door_monty[obj->work[0] * 4 + 13 + obj->work[1]];
    ThreeDoorMontyEntry *entries[4];
    omObjData *objs[4];
    u8 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010D260_three_door_monty[1 + i];
        objs[i] = entries[i]->obj;
    }
    entry->unk_40[0] = func_8000B838_main(0x31);
    entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
    if (obj->work[1] == 1) {
        entry->unk_04 = 11;
        func_8000BD50_main(entry->unk_40[1], 11);
    } else {
        entry->unk_04 = (u8)(rand8() % 10);
        func_8000BD50_main(entry->unk_40[1], entry->unk_04);
    }
    espPosSet(entry->unk_40[1], D_8010CD64_three_door_monty[(s16)objs[obj->work[0]]->work[1]][obj->work[1]], 140);
    espDispOff(entry->unk_40[1]);
    obj->func = func_8010B7B8_three_door_monty;
}

void func_8010BD88_three_door_monty(void) {
    ThreeDoorMontyEntry *entry;
    omObjData *obj;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            entry = &D_8010D260_three_door_monty[i * 4 + 13 + j];
            obj = omAddObj(0x12C, 1, 0xA, -1, func_8010BC08_three_door_monty);
            obj->work[0] = i;
            obj->work[1] = j;
            entry->obj = obj;
        }
    }
}

void func_8010BE64_three_door_monty(void) {
    ThreeDoorMontyEntry *entries[4];
    omObjData *objs[4];
    s16 best[4];
    s16 rank[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        best[i] = 4;
        rank[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        entries[i] = &D_8010D260_three_door_monty[1 + i];
        objs[i] = entries[i]->obj;
        if (best[0] > entries[i]->unk_16) {
            best[0] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[0] < entries[i]->unk_16 && entries[i]->unk_16 < best[1]) {
            best[1] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[1] < entries[i]->unk_16 && entries[i]->unk_16 < best[2]) {
            best[2] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[2] < entries[i]->unk_16 && entries[i]->unk_16 < best[3]) {
            best[3] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[0] == entries[i]->unk_16) {
            rank[i] = 0;
        }
        if (best[1] == entries[i]->unk_16) {
            rank[i] = 1;
        }
        if (best[2] == entries[i]->unk_16) {
            rank[i] = 2;
        }
        if (best[3] == entries[i]->unk_16) {
            rank[i] = 3;
        }
    }
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_16 == 99) {
            rank[i] = 3;
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[objs[i]->work[0]].bonusCoin = rank[i];
    }
}

void func_8010C1B4_three_door_monty(void) {
    u32 i;

    if (D_8010CDCC_three_door_monty == 0) {
        D_8010CDCC_three_door_monty = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 1641.4171f;
            CRotM[i].x = 322.53763f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 150.0f;
            CenterM[i].z = -290.0f;
        }
        CZoomM[2] = 1641.4171f;
        CRotM[2].x = 342.44815f;
        CRotM[2].y = 0.0f;
        CRotM[2].z = 0.0f;
        CenterM[2].x = 0.0f;
        CenterM[2].y = 240.0f;
        CenterM[2].z = -220.0f;
    }
}

void func_8010C2DC_three_door_monty(omObjData *obj) {
    s16 i;

    for (i = 0; i < 3; i++) {
        DataClose(D_8010D238_three_door_monty[i]);
    }
    Hu3DAnimKill(D_8010EC3E_three_door_monty);
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_8010C358_three_door_monty(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010C2DC_three_door_monty;
    }
}

void func_8010C390_three_door_monty(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        obj->func = func_8010C358_three_door_monty;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010C3E8_three_door_monty(omObjData *obj) {
    switch (D_8010EC30_three_door_monty) {
        case 0:
            func_801062E8_three_door_monty(1);
            break;
        case 1:
            if (D_8010EC42_three_door_monty == 1) {
                func_801062E8_three_door_monty(2);
                D_8010EC32_three_door_monty = 0;
            } else if (++D_8010EC32_three_door_monty > 50) {
                D_8010EC32_three_door_monty = 50;
            }
            break;
        case 2:
            if (D_8010EC32_three_door_monty == 0) {
                GMesCreate(7);
                D_8010EC32_three_door_monty++;
            } else if (D_8010EC32_three_door_monty >= 63) {
                HuAudSeqPlay(0x31);
            } else {
                D_8010EC32_three_door_monty++;
            }
            if (GMesStatGet() == 0) {
                func_801062E8_three_door_monty(3);
                D_8010EC32_three_door_monty = 0;
            }
            break;
        case 3:
            if (D_8010EC42_three_door_monty == 3) {
                func_801062E8_three_door_monty(4);
                D_8010EC3C_three_door_monty = 0;
                D_800D6A58_main = 1;
            } else {
                D_8010EC32_three_door_monty++;
            }
            break;
        case 4:
            if (D_8010EC42_three_door_monty == 4) {
                func_801062E8_three_door_monty(5);
                D_8010EC32_three_door_monty = 0;
            }
            break;
        case 5:
            if (D_8010EC42_three_door_monty == 5) {
                func_801062E8_three_door_monty(6);
                D_8010EC32_three_door_monty = 151;
                GMesCreate(0x1A, 5, 160, 28);
            }
            break;
        case 6:
            if (D_8010EC32_three_door_monty <= 0 || D_8010EC44_three_door_monty == 1) {
                D_8010D254_three_door_monty = 0;
                D_8010EC44_three_door_monty = 0;
                func_8003F5C0_main();
                func_801062E8_three_door_monty(7);
                D_800D6A58_main = 0;
            } else {
                D_8010EC32_three_door_monty--;
                D_8010D254_three_door_monty += 33;
                if (D_8010D254_three_door_monty % 1000 == 990) {
                    D_8010D254_three_door_monty += 10;
                }
            }
            func_8003F578_main((D_8010EC32_three_door_monty + 29) / 30);
            break;
        case 7:
            if (D_8010EC42_three_door_monty == 7) {
                func_801062E8_three_door_monty(10);
                D_8010EC32_three_door_monty = 150;
                if (D_8010D230_three_door_monty == 4) {
                    func_801062E8_three_door_monty(11);
                }
            }
            break;
        case 8:
        case 9:
            break;
        case 10:
            if (D_8010EC3C_three_door_monty == 2) {
                GMesCreate(0x12);
                HuAudSeqFadeOut(120);
                D_8010EC3C_three_door_monty = 3;
            }
            if (D_8010EC3C_three_door_monty == 3 && GMesStatGet() == 0) {
                if (D_8010D232_three_door_monty >= 0) {
                    D_8010EC32_three_door_monty = 99;
                    func_801062E8_three_door_monty(12);
                }
                D_8010D232_three_door_monty++;
            }
            if (D_8010EC32_three_door_monty > 0) {
                D_8010EC32_three_door_monty--;
            } else {
                D_8010EC32_three_door_monty = 0;
            }
            break;
        case 11:
            if (D_8010EC3C_three_door_monty == 2) {
                GMesCreate(0x12);
                HuAudSeqFadeOut(120);
                D_8010EC3C_three_door_monty = 3;
            }
            if (D_8010EC3C_three_door_monty == 3 && GMesStatGet() == 0) {
                if (D_8010D232_three_door_monty >= 0) {
                    D_8010EC32_three_door_monty = 144;
                    func_801062E8_three_door_monty(12);
                }
                D_8010D232_three_door_monty++;
            }
            break;
        case 12:
            if (D_8010D230_three_door_monty == 4) {
                if (D_8010EC32_three_door_monty == 144) {
                    HuAudSeqPlay(0x6C);
                }
            } else {
                if (D_8010EC32_three_door_monty == 98) {
                    HuAudSeqPlay(0x65);
                }
            }
            if (D_8010EC32_three_door_monty > 0) {
                D_8010EC32_three_door_monty--;
            } else {
                D_8010EC32_three_door_monty = 0;
                func_801062E8_three_door_monty(13);
            }
            break;
        case 13:
            if (D_8010EC32_three_door_monty == 0) {
                func_8010BE64_three_door_monty();
                WipeCreateOut(0, 20);
                obj->func = func_8010C358_three_door_monty;
                D_8010EC32_three_door_monty++;
            }
            break;
    }
}

void func_8010C8C0_three_door_monty(omObjData *obj) {
    s16 i;

    WipeCreateIn(0xFF, 16);
    func_80107344_three_door_monty();
    func_801090C8_three_door_monty();
    func_801096FC_three_door_monty();
    func_801099EC_three_door_monty();
    func_8010B5A8_three_door_monty();
    func_801074B4_three_door_monty();
    func_8010BD88_three_door_monty();
    func_8010C1B4_three_door_monty();
    D_8010EC32_three_door_monty = 0;
    D_8010EC30_three_door_monty = 0;
    D_8010EC42_three_door_monty = 0;
    D_8010D254_three_door_monty = 0;
    D_8010EC3A_three_door_monty = 0;
    D_8010D250_three_door_monty = -1;
    D_8010EC38_three_door_monty = 3;
    D_8010EC3C_three_door_monty = 0;
    D_8010D230_three_door_monty = 0;
    D_8010D252_three_door_monty = 0;
    D_8010EC46_three_door_monty = 0;
    for (i = 0; i < 3; i++) {
        D_8010EC4A_three_door_monty[i] = -1;
    }
    D_8010EC48_three_door_monty = 0;
    D_8010EC44_three_door_monty = 0;
    for (i = 0; i < 4; i++) {
        D_8010D244_three_door_monty[i] = 0;
    }
    D_8010D258_three_door_monty = 0;
    D_8010EC40_three_door_monty = 0;
    D_8010EC50_three_door_monty = 0;
    D_8010D232_three_door_monty = -15;
    obj->func = func_8010C3E8_three_door_monty;
}

void func_8010CA40_three_door_monty(void) {
}

void func_8010CA48_three_door_monty(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 3;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(3);
    func_8000B710_main(3);
    for (i = 0; i < 3; i++) {
        ScissorSet(i, D_8010CDD0_three_door_monty[i].scissorX, D_8010CDD0_three_door_monty[i].scissorY,
                   D_8010CDD0_three_door_monty[i].scissorWidth, D_8010CDD0_three_door_monty[i].scissorHeight);
        ViewportSet(i, D_8010CDD0_three_door_monty[i].viewportScale.x, D_8010CDD0_three_door_monty[i].viewportScale.y,
                    D_8010CDD0_three_door_monty[i].viewportScale.z, D_8010CDD0_three_door_monty[i].viewportTranslate.x,
                    D_8010CDD0_three_door_monty[i].viewportTranslate.y,
                    D_8010CDD0_three_door_monty[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010CDD0_three_door_monty[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010CBBC_three_door_monty(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8010CA48_three_door_monty();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010D228_three_door_monty, 0);
    func_80045010_main(D_8010D228_three_door_monty, 1);
    omAddObj(1000, 0, 0, -1, func_8010C8C0_three_door_monty);
    omAddObj(1000, 0, 0, -1, func_8010C390_three_door_monty);
    func_80105A74_three_door_monty();
}

const s16 D_8010D228_three_door_monty[] = { 0x8260, 0x8261, 0x8262, 0 };
