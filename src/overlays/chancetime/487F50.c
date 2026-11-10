#include "common.h"
#include "chancetime.h"
#include "game/window.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"

typedef struct ChanceTimeUnkFED0 {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14[3];
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ s8 unk1B[4];
    /* 0x1F */ char unk1F[9];
} ChanceTimeUnkFED0; // size = 0x28

typedef struct ChanceTimeUnkFE3C {
    /* 0x00 */ s16 coins;
    /* 0x02 */ s16 stars;
} ChanceTimeUnkFE3C; // size = 0x4

typedef struct ChanceTimeReelSpeed {
    /* 0x00 */ f32 accel;
    /* 0x04 */ f32 max;
} ChanceTimeReelSpeed; // size = 0x8

typedef struct ChanceTimeTransfer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
} ChanceTimeTransfer; // size = 0x8

extern s8 D_8010FB80_chancetime;
extern s8 D_8010FB81_chancetime;
extern s16 D_8010FB84_chancetime[2];
extern f32 D_8010FB88_chancetime;
extern f32 D_8010FB8C_chancetime;
extern Vec D_8010FB94_chancetime[];
extern s32 D_8010FC00_chancetime;
extern s32 D_8010FBF0_chancetime;
extern s32 D_8010FBF4_chancetime[3];
extern s32 D_8010FC10_chancetime;
extern s32 D_8010FC14_chancetime;
extern s32 D_8010FC18_chancetime;
extern s32 D_8010FC1C_chancetime;
extern s16 D_8010FE94_chancetime[3];
extern u16 D_8010FE9A_chancetime;
extern s32 D_8010FEC4_chancetime;
extern ChanceTimeUnkFE3C D_8010FE3C_chancetime[];
extern ChanceTimeUnkFE3C D_8010FD68_chancetime[];
extern ChanceTimeTransfer D_8010FF60_chancetime[20];
extern ChanceTimeUnkFED0 D_8010FED0_chancetime[3];
extern s16 D_8010FEB0_chancetime[3][3];
extern s8 D_8010FF3A_chancetime;
extern u8 D_8010FF3B_chancetime[];
extern u8 D_8010FC98_chancetime[][13];
extern s32 D_8010FF48_chancetime[3];
extern s8 D_8010FEC8_chancetime;
extern s8 D_8010FEC9_chancetime;
extern s8 D_80110000_chancetime;
extern s32 D_80110004_chancetime;
extern s16 D_80110010_chancetime[10];
extern s16 D_80110028_chancetime[20];
extern omObjData *D_80110080_chancetime;
extern s32 D_80110008_chancetime;
extern u32 D_8010FD5C_chancetime[];
extern u32 D_8010FD8C_chancetime[];
extern u32 D_8010FDB0_chancetime[];
extern u32 D_8010FDD4_chancetime[];
extern u32 D_8010FDF8_chancetime[];
extern u32 D_8010FE1C_chancetime[];
extern void (*D_80110084_chancetime)();
extern omObjData *D_801100C8_chancetime;
extern s8 D_801100DD_chancetime[3];
extern s8 D_801100DF_chancetime;
extern void (*D_801100CC_chancetime)(omObjData *);
extern const ChanceTimeReelSpeed D_8010FD08_chancetime[3];
extern Vec D_8010FD38_chancetime[3];
extern char *D_8010FBD8_chancetime[3];
extern s16 D_8010FE90_chancetime;
extern s16 D_8010FE92_chancetime;
extern HuSprite *D_8010FE9C_chancetime;
extern void *D_8010FEA0_chancetime;
extern void *D_8010FEA4_chancetime;
extern s16 D_8010FEA8_chancetime[2];

s32 func_8010872C_chancetime(void);
void func_8010C870_chancetime(omObjData *object);
void func_8010C5F4_chancetime(omObjData *object);
void func_8010C98C_chancetime(void);
void func_8010C994_chancetime(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_8010CF78_chancetime(s8 arg0);
void func_8010DAB0_chancetime(void);
void func_8010C610_chancetime(omObjData *object);
void func_8010F44C_chancetime(s32 arg0, s32 arg1, s32 arg2);
void func_8010D320_chancetime(omObjData *object);
void func_8010DB1C_chancetime(s8 arg0);
void func_8010DF68_chancetime(void);
void func_8010DF70_chancetime(void);
void func_8010D6A4_chancetime(s8 arg0);
void func_8010DFA4_chancetime(void);
void func_8010E1E0_chancetime(void);
void func_8010E210_chancetime(void);
void func_8010E280_chancetime(omObjData *object);
void func_8010E4D0_chancetime(omObjData *object);
void func_8010F984_chancetime(omObjData *object);
void func_8010F1F8_chancetime(void);
void func_8010F42C_chancetime(void);

// Only diff: sign-extension of the func_8000B838_main result uses s1 instead of v0 as the intermediate register.
#ifdef NON_MATCHING
void func_8010BF80_chancetime(void) {
    omObjData *obj;
    void *data;
    s8 i;
    s32 spriteId;
    s16 grp;
    HuSprite *spr;

    obj = omAddObj(20, 16, 0, -1, NULL);
    D_801100C8_chancetime = obj;

    obj->model[1] = func_8000B108_main(0x1C0009, 0x229);
    data = DataRead(0x1C0002);
    D_8010FEB0_chancetime[0][0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8010FBD8_chancetime[0]);
    func_80032FC0_main(D_8010FEB0_chancetime[0][0], 1, 1);
    Hu3DAnimBankSet(D_8010FEB0_chancetime[0][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        D_8010FEB0_chancetime[0][i] =
            Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8010FEB0_chancetime[0][0], 0, D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[0][i], 1, 1);
        Hu3DAnimBankSet(D_8010FEB0_chancetime[0][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_8001C814_main(obj->model[1], 2, 0);
    Hu3DModelCameraSet(obj->model[1], 1);

    obj->model[2] = func_8000B108_main(0x1C0009, 0x229);
    for (i = 0; i < 3; i++) {
        D_8010FEB0_chancetime[1][i] =
            Hu3DAnimLink(Hu3DData[obj->model[2]].hmf, D_8010FEB0_chancetime[0][0], 0, D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[1][i], 1, 1);
        Hu3DAnimBankSet(D_8010FEB0_chancetime[1][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[2]);
    func_8001C514_main(obj->model[2]);
    func_8001C814_main(obj->model[2], 2, 0);
    Hu3DModelCameraSet(obj->model[2], 1);

    obj->model[3] = func_8000B108_main(0x1C0009, 0x229);
    data = DataRead(0x1C0003);
    D_8010FEB0_chancetime[2][0] = Hu3DAnimCreate(Hu3DData[obj->model[3]].hmf, data, 0, D_8010FBD8_chancetime[0]);
    func_80032FC0_main(D_8010FEB0_chancetime[2][0], 1, 1);
    Hu3DAnimBankSet(D_8010FEB0_chancetime[2][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        D_8010FEB0_chancetime[2][i] =
            Hu3DAnimLink(Hu3DData[obj->model[3]].hmf, D_8010FEB0_chancetime[2][0], 0, D_8010FBD8_chancetime[i]);
        func_80032FC0_main(D_8010FEB0_chancetime[2][i], 1, 1);
        Hu3DAnimBankSet(D_8010FEB0_chancetime[2][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[3]);
    func_8001C514_main(obj->model[3]);
    func_8001C814_main(obj->model[3], 2, 0);
    Hu3DModelCameraSet(obj->model[3], 1);

    spriteId = func_8000B838_main(0x1C0000);
    D_8010FE92_chancetime = spriteId;
    grp = HuSprGrpCreate(1, 0);
    HuSprAttrSet(grp, 0, HUSPR_ATTR_DISPOFF);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    D_8010FE9C_chancetime = spr = HuSprGet(grp, 0);
    D_8010FEA0_chancetime = spr->unk_84->unk08;
    D_8010FEA4_chancetime = spr->unk_84->unk0C;
    D_8010FEA8_chancetime[0] = spr->unk_84->unk14;
    D_8010FEA8_chancetime[1] = spr->unk_84->unk16;
    D_8010FE90_chancetime = Hu3DHookFuncCreate(0, func_8010C994_chancetime, 2);
    Hu3DModelCameraSet(D_8010FE90_chancetime, 1);

    data = DataRead(0x1C0007);
    for (i = 0; i < 3; i++) {
        D_8010FE94_chancetime[i] = espEntry(HuSprAnimRead(data), 0, 0);
        espDispOff(D_8010FE94_chancetime[i]);
    }
    HuMemMemoryFreePerm(data);
    D_8010FE9A_chancetime = espEntry(func_8000B838_main(0x1C0004), 0, 0);
    espDispOff(D_8010FE9A_chancetime);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], -111.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[2], 119.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[3], 3.0f, 265.0f, -541.0f);
    func_8010CF78_chancetime(D_801100DC_chancetime);
    func_8010DAB0_chancetime();
    omPrcSetDestructor(0, func_8010C98C_chancetime);
    D_801100CC_chancetime = func_8010C5F4_chancetime;
    while (TRUE) {
        D_801100CC_chancetime(obj);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010BF80_chancetime);
#endif

void func_8010C5F4_chancetime(omObjData *object) {
    func_8010D320_chancetime(object);
}

void func_8010C610_chancetime(omObjData *object) {
    Vec pos;
    Vec2f screen;

    D_8010FB8C_chancetime += 1.2f;
    D_8010FB8C_chancetime = (D_8010FB8C_chancetime > 30.0f) ? 30.0f : D_8010FB8C_chancetime;
    D_8010FB88_chancetime -= D_8010FB8C_chancetime;
    if (D_8010FB88_chancetime < 0.0f) {
        D_8010FB8C_chancetime = D_8010FB8C_chancetime * -0.1f;
        D_8010FB88_chancetime = 0.0f;
        if (D_8010FC00_chancetime == 0) {
            func_80108704_chancetime();
            D_8010FC00_chancetime = 1;
        }
        if (D_8010FB8C_chancetime >= -0.24000001f) {
            D_8010FC00_chancetime = 0;
            D_801100CC_chancetime = func_8010C870_chancetime;
            D_8010FB88_chancetime = 0.0f;
            return;
        }
    }
    pos.x = 0.0f;
    pos.y = D_8010FB94_chancetime[0].x + D_8010FB88_chancetime - 168.0f;
    pos.z = D_8010FB94_chancetime[0].y;
    Hu3D3Dto2D(0, &pos, &screen);
    D_8010FB84_chancetime[0] = 74;
    D_8010FB84_chancetime[1] = screen.y - 120.0f + 25.0f;
    espPosSet(D_8010FE9A_chancetime, 161, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[0], D_8010FB84_chancetime[0] + 51, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[1], D_8010FB84_chancetime[0] + 124, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[2], D_8010FB84_chancetime[0] + 87, D_8010FB84_chancetime[1] + 116);
}

void func_8010C870_chancetime(omObjData *object) {
    D_8010FB84_chancetime[0] = 74;
    D_8010FB84_chancetime[1] = 25;
    espPosSet(D_8010FE9A_chancetime, 161, 71);
    espPosSet(D_8010FE94_chancetime[0], D_8010FB84_chancetime[0] + 51, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[1], D_8010FB84_chancetime[0] + 124, D_8010FB84_chancetime[1] + 46);
    espPosSet(D_8010FE94_chancetime[2], D_8010FB84_chancetime[0] + 87, D_8010FB84_chancetime[1] + 116);
    if (func_8010872C_chancetime() == 1) {
        D_8010FB88_chancetime = 600.0f;
        D_8010FB8C_chancetime = 0.0f;
        D_8010FB80_chancetime = 0;
        D_8010FB81_chancetime = 1;
        D_801100CC_chancetime = func_8010C5F4_chancetime;
    }
}

void func_8010C98C_chancetime(void) {
}

void func_8010C994_chancetime(Gfx **gfxPos, s32 arg1, s32 arg2) {
    Gfx *gfx;
    s16 texX[2];
    s16 texY[2];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 screenX;
    s16 screenY;
    s16 texWidth;
    s16 row;
    s16 rows;
    s16 offset;

    width = D_8010FEA8_chancetime[0];
    height = D_8010FEA8_chancetime[1];
    x = D_8010FB84_chancetime[0];
    y = D_8010FB84_chancetime[1];
    if ((x + width < 0) | (x >= 320)) {
        return;
    }
    if ((y + height < 0) | (y >= 240)) {
        return;
    }

    texX[0] = (x < 0) ? -x : 0;
    texX[1] = (x + width > 320) ? 320 - x : width;
    if (x < 0) {
        screenX = 0;
    } else if (x >= 319) {
        screenX = 319;
    } else {
        screenX = x;
    }
    texWidth = texX[1] - texX[0];
    texY[0] = (y < 0) ? -y : 0;
    texY[1] = (y + height > 240) ? 240 - y : height;
    if (y < 0) {
        screenY = 0;
    } else if (y >= 319) {
        screenY = 319;
    } else {
        screenY = y;
    }

    gfx = *gfxPos;
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetRenderMode(gfx++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, D_8010FEA4_chancetime);

    rows = 4;
    offset = 0;
    for (row = texY[0]; row < texY[1]; row += rows) {
        if (row + rows > texY[1]) {
            rows = texY[1] - row;
        }
        gDPLoadTextureTile(gfx++, D_8010FEA0_chancetime, G_IM_FMT_CI, G_IM_SIZ_8b, width, rows, texX[0], row, texX[1] - 1, row + rows - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, texWidth << 2, rows << 2);
        gSPTextureRectangle(gfx++, screenX << 2, (offset + screenY) << 2, (texWidth + screenX) << 2, (offset + rows + screenY) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        offset += rows;
    }
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 104, 52, 215, 163);
    *gfxPos = gfx;
}

void func_8010CF78_chancetime(s8 arg0) {
    s8 i;
    s8 j;
    s8 k;

    D_8010FBF0_chancetime = 0;
    for (i = 0; i < 3; i++) {
        D_8010FBF4_chancetime[i] = 0;
        D_801100DD_chancetime[i] = -1;
        D_8010FED0_chancetime[i].unk00 = 0;
        D_8010FED0_chancetime[i].unk10 = 2;
        D_8010FED0_chancetime[i].unk12 = 4;
        D_8010FED0_chancetime[i].unk04 = 0;
        D_8010FED0_chancetime[i].unk0C = -1.0f;
    }
    for (i = 0; i < 2; i++) {
        k = rand8() & 3;
        for (j = 0; j < 4; j++) {
            D_8010FED0_chancetime[i].unk1B[k] = GwPlayer[D_801100D0_chancetime[j]].chr;
            if (++k >= 4) {
                k = 0;
            }
        }
        D_8010FED0_chancetime[i].unk1A = 4;
    }
    k = rand8() % 13;
    for (j = 0; j < 13; j++) {
        D_8010FF3B_chancetime[k] = D_8010FC98_chancetime[arg0][j];
        if (++k >= 13) {
            k = 0;
        }
    }
    D_8010FF3A_chancetime = 13;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            D_8010FED0_chancetime[i].unk14[j] = D_8010FEB0_chancetime[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DAnmNoSet(D_8010FED0_chancetime[i].unk14[j], D_8010FED0_chancetime[i].unk1B[2 - j]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FC98_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCC8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCD8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCE8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FCF8_chancetime);

void func_8010D320_chancetime(omObjData *object) {
    ChanceTimeUnkFED0 *reel;
    s16 idx;
    s16 tmp;
    s8 i;
    s8 j;

    for (i = 0; i < 3; i++) {
        reel = &D_8010FED0_chancetime[i];
        if (reel->unk00 == 4) {
            reel->unk04 += D_8010FD08_chancetime[D_8010FBF0_chancetime - 1].accel;
            reel->unk04 = (reel->unk04 > D_8010FD08_chancetime[D_8010FBF0_chancetime - 1].max)
                              ? D_8010FD08_chancetime[D_8010FBF0_chancetime - 1].max
                              : reel->unk04;
        }
        if (reel->unk00 == 1) {
            reel->unk0C = ((s32)(reel->unk08 / 100.0f) + 1) * 100.0f;
            reel->unk00 = 2;
        }
        reel->unk08 += reel->unk04;
        reel->unk04 *= 0.98f;
        if (reel->unk00 == 2 && reel->unk08 >= reel->unk0C) {
            reel->unk08 = reel->unk0C;
            reel->unk04 = 0.0f;
            reel->unk00 = 3;
        }
        if (reel->unk08 >= 200.0f) {
            reel->unk08 -= 200.0f;
            reel->unk12 = (reel->unk12 < reel->unk1A) ? reel->unk12 : reel->unk12 - reel->unk1A;
            idx = reel->unk12;
            reel->unk10 = idx;
            for (j = 0; j < 3; j++) {
                Hu3DAnmNoSet(reel->unk14[j], reel->unk1B[idx]);
                tmp = idx - 1;
                tmp = (tmp < 0) ? reel->unk1A + tmp : tmp;
                idx = tmp;
            }
            reel->unk12 += 2;
            reel->unk12 = (reel->unk12 < reel->unk1A) ? reel->unk12 : reel->unk12 - reel->unk1A;
        }
        if (reel->unk00 == 3) {
            tmp = reel->unk10 + (s32)(reel->unk08 / 100.0f) - 2;
            tmp = (tmp < 0) ? reel->unk1A + tmp : tmp;
            tmp = (tmp < reel->unk1A) ? tmp : tmp - reel->unk1A;
            D_801100DD_chancetime[i] = reel->unk1B[tmp];
            reel->unk00 = 0;
        }
        Hu3DModelPosSet(object->model[i + 1], D_8010FD38_chancetime[i].x,
                        D_8010FD38_chancetime[i].y - reel->unk08, D_8010FD38_chancetime[i].z);
    }
}

void func_8010D6A4_chancetime(s8 arg0) {
    s8 i;
    s8 j;

    D_8010FBF0_chancetime++;
    switch (D_8010FBF0_chancetime) {
        case 1:
            D_8010FF48_chancetime[0] = HuAudFXPlay(0x4F9);
            D_8010FBF4_chancetime[0] = 1;
            break;
        case 2:
            D_8010FF48_chancetime[1] = HuAudFXPlay(0x4FA);
            D_8010FBF4_chancetime[1] = 1;
            break;
        case 3:
            D_8010FF48_chancetime[2] = HuAudFXPlay(0x4FB);
            D_8010FBF4_chancetime[2] = 1;
            break;
    }
    D_8010FED0_chancetime[arg0].unk00 = 4;
    if (arg0 < 2 && D_801100DD_chancetime[1 - arg0] != -1) {
        j = 0;
        for (i = 0; i < 4; i++) {
            if (D_801100DD_chancetime[1 - arg0] != GwPlayer[D_801100D0_chancetime[i]].chr) {
                D_8010FED0_chancetime[arg0].unk1B[j] = GwPlayer[D_801100D0_chancetime[i]].chr;
                j++;
            }
        }
        D_8010FED0_chancetime[arg0].unk1A = 3;
        for (i = 0; i < 3; i++) {
            Hu3DAnmNoSet(D_8010FED0_chancetime[arg0].unk14[i], D_8010FED0_chancetime[arg0].unk1B[2 - i]);
        }
    }
    func_8010DB1C_chancetime(arg0);
}

void func_8010D92C_chancetime(s8 arg0) {
    switch (D_8010FBF0_chancetime) {
        case 1:
            if (D_8010FBF4_chancetime[0] == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[0]);
            }
            HuAudFXPlay(0x4FC);
            break;
        case 2:
            if (D_8010FBF4_chancetime[1] == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[1]);
            }
            HuAudFXPlay(0x4FD);
            break;
        case 3:
            if (D_8010FBF4_chancetime[2] == 1) {
                HuAudFXStop((s16)D_8010FF48_chancetime[2]);
            }
            HuAudFXPlay(0x4FE);
            break;
    }
    D_8010FED0_chancetime[arg0].unk00 = 1;
}

void func_8010DA24_chancetime(void) {
    s32 i;

    D_8010FB80_chancetime = 1;
    D_8010FB81_chancetime = 0;
    for (i = 0; i < 3; i++) {
        espDispOn(D_8010FE94_chancetime[i]);
    }
    espDispOn(D_8010FE9A_chancetime);
    D_801100CC_chancetime = func_8010C610_chancetime;
}

s32 func_8010DAA4_chancetime(void) {
    return D_8010FB81_chancetime;
}

void func_8010DAB0_chancetime(void) {
    omObjData *obj = D_801100C8_chancetime;
    s8 i;

    for (i = 0; i < 3; i++) {
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void func_8010DB1C_chancetime(s8 arg0) {
    omObjData *obj = D_801100C8_chancetime;

    espDispOff(D_8010FE94_chancetime[arg0]);
    func_8001C258_main(obj->model[arg0 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010DB78_chancetime(void) {
    D_8010FEC4_chancetime = 0;
    D_8010FEC8_chancetime = 1;
    D_8010FEC9_chancetime = 0;
}

void func_8010DB98_chancetime(void) {
    D_8010FEC8_chancetime = 0;
    D_8010FEC9_chancetime = 1;
}

void func_8010DBB0_chancetime(void) {
    omObjData *obj;
    HmfModel *model;
    s16 sprId;
    s8 i;

    obj = omAddObj(0x14, 0x15, 0, -1, NULL);
    D_80110080_chancetime = obj;
    model = &Hu3DData[D_800D10F2_main];
    model->unk00 = (model->unk00 & 0xF9) | 3;
    Hu3DModelCameraSet(D_800D10F2_main, 2);
    sprId = func_8000B838_main(0x210026);
    for (i = 0; i < 20; i++) {
        D_80110028_chancetime[i] = espEntry(sprId, 0, 1);
        espPriSet(D_80110028_chancetime[i], 0);
        espDispOff(D_80110028_chancetime[i]);
        espBankSet(D_80110028_chancetime[i], 0, 0);
        func_8000BDDC_main(D_80110028_chancetime[i], 1);
        espScaleSet(D_80110028_chancetime[i], 0.5f, 0.5f);
    }
    obj->model[1] = func_8000B0D4_main(0x1301CC, 0x2B9);
    Hu3DModelScaleSet(obj->model[1], 0.5f, 0.5f, 0.5f);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelCameraSet(obj->model[1], 4);
    func_8001C258_main(obj->model[1], 4, 4);
    for (i = 1; i < 10; i++) {
        obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        Hu3DModelScaleSet(obj->model[i + 1], 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(obj->model[i + 1], 4);
        func_8001C258_main(obj->model[i + 1], 4, 4);
        func_8001C814_main(obj->model[i + 1], 2, 2);
    }
    for (i = 0; i < 10; i++) {
        D_80110010_chancetime[i] = func_8000CED8_main(0xB0004, 0x6A9);
        func_8000CD00_main(D_80110010_chancetime[i], 4.0f, 20.0f, 4.0f);
        func_8000D018_main(D_80110010_chancetime[i], 60.0f);
        Hu3DModelCameraSet(D_80110010_chancetime[i], 4);
        func_800138EC_main(D_80110010_chancetime[i], 1, 0);
        func_8001C258_main(D_80110010_chancetime[i], 4, 4);
    }
    D_80110004_chancetime = func_80060880_main(100, 160, 14);
    func_80061100_main((s16)D_80110004_chancetime, 5);
    if (!(GwPlayer[D_801100D0_chancetime[0]].stat & 1)) {
        HuWinActivePlayerSet((s16)D_80110004_chancetime, 1 << GwPlayer[D_801100D0_chancetime[0]].pad);
    }
    omPrcSetDestructor(0, func_8010DF68_chancetime);
    D_80110084_chancetime = func_8010DF70_chancetime;
    while (TRUE) {
        D_80110084_chancetime(obj);
        HuPrcVSleep();
    }
}

void func_8010DF68_chancetime(void) {
}

void func_8010DF70_chancetime(void) {
}

void func_8010DF78_chancetime(s32 arg0) {
    D_8010FC14_chancetime = 0;
    D_80110008_chancetime = (s8)arg0;
    D_80110084_chancetime = func_8010DFA4_chancetime;
}

void func_8010DFA4_chancetime(void) {
    s32 index = D_80110008_chancetime;

    HuWinHomeClear(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    HuWinMesSet(D_80110004_chancetime, D_8010FD5C_chancetime[index], -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (HuWinStatGet(D_80110004_chancetime)) {
        HuPrcVSleep();
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        HuWinComKeyReset();
    }
    D_80110000_chancetime = index;
    D_80110084_chancetime = func_8010E1E0_chancetime;
}

void func_8010E1E0_chancetime(void) {
    func_8010D6A4_chancetime(D_80110000_chancetime);
    D_80110084_chancetime = func_8010E210_chancetime;
}

void func_8010E210_chancetime(void) {
    D_8010FC1C_chancetime++;
    if (D_8010FC1C_chancetime < 10) {
        return;
    }
    D_8010FC14_chancetime = 1;
    D_8010FC1C_chancetime = 0;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

s32 func_8010E258_chancetime(void) {
    return D_8010FC14_chancetime;
}

void func_8010E264_chancetime(void) {
    D_8010FC18_chancetime = 0;
    D_80110084_chancetime = func_8010E280_chancetime;
}

void func_8010E280_chancetime(omObjData *object) {
    s32 players[2];
    s32 i;
    s32 j;
    s32 coins = GwPlayer[D_801100D0_chancetime[0]].coin;
    s32 stars = GwPlayer[D_801100D0_chancetime[0]].star;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[j].chr) {
                players[i] = j;
                break;
            }
        }
    }

    func_8010F984_chancetime(object);
    HuPrcSleep(10);
    D_8010FAE4_chancetime = 1;
    func_800F5E30_shared_board(players[0], players[1]);
    func_800F7108_shared_board();
    func_800F5F4C_shared_board(players[0], players[1]);
    func_800F5F60_shared_board();
    func_800F5F7C_shared_board();
    HuPrcSleep(40);
    func_8010E4D0_chancetime(object);
    if (coins + 1 == GwPlayer[D_801100D0_chancetime[0]].coin) {
        func_8010705C_chancetime();
    } else if (coins < GwPlayer[D_801100D0_chancetime[0]].coin) {
        func_80106F10_chancetime();
    } else if (stars < GwPlayer[D_801100D0_chancetime[0]].star) {
        func_80106F10_chancetime();
    } else if (GwPlayer[D_801100D0_chancetime[0]].coin < coins) {
        func_801071A8_chancetime();
    } else if (GwPlayer[D_801100D0_chancetime[0]].star < stars) {
        func_801071A8_chancetime();
    } else {
        func_8010705C_chancetime();
    }
    HuPrcSleep(30);
    D_8010FC18_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

s32 func_8010E4C4_chancetime(void) {
    return D_8010FC18_chancetime;
}

// Only diff: GCC combine moves the `coins` table load after the `stars` load, so the two
// stack stores are emitted in swapped order (and the blez delay slot is not filled).
#ifdef NON_MATCHING
void func_8010E4D0_chancetime(omObjData *object) {
    f32 coinsF[2];
    f32 starsF[2];
    s32 players[2];
    s32 i;
    s32 j;
    f32 offsetY;
    u16 isStars;
    s32 launched;
    s32 finished;
    s32 delay;
    s16 coins;
    s16 stars;
    s32 count;
    s32 coinAmount;
    f32 step;
    f32 lost;
    f32 gained;
    s32 frame;
    s32 timer;
    f32 value;
    f32 s;
    f32 x;
    f32 y;
    f32 t;
    f32 scale;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[D_801100D0_chancetime[j]].chr) {
                players[i] = D_801100D0_chancetime[j];
                break;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        coinsF[i] = GwPlayer[players[i]].coin;
        starsF[i] = GwPlayer[players[i]].star;
    }

    coins = D_8010FD68_chancetime[D_801100DF_chancetime].coins;
    stars = D_8010FD68_chancetime[D_801100DF_chancetime].stars;
    coinAmount = D_8010FD68_chancetime[D_801100DF_chancetime].coins;
    if (coinAmount > 0) {
        if (GwPlayer[players[0]].coin < coinAmount) {
            coins = GwPlayer[players[0]].coin;
        }
        isStars = FALSE;
    } else {
        if (stars > GwPlayer[players[0]].star) {
            stars = GwPlayer[players[0]].star;
        }
        isStars = TRUE;
    }

    if ((!isStars ? coins : stars) <= 0) {
        return;
    }

    if (!isStars) {
        offsetY = 0.0f;
        count = coins;
        if (count > 20) {
            count = 20;
        }
        step = (f32)coins / count;
    } else {
        offsetY = 16.0f;
        count = stars;
        if (count > 10) {
            count = 10;
        }
        step = (f32)stars / count;
    }
    gained = 0.0f;
    lost = 0.0f;
    delay = 20 / count;
    delay = (delay < 5) ? 5 : delay;

    for (i = 0; i < 20; i++) {
        D_8010FF60_chancetime[i].state = 0;
        D_8010FF60_chancetime[i].timer = 0;
    }

    frame = 0;
    launched = 0;
    finished = 0;
    while (finished < count) {
        for (i = 0; i < 20; i++) {
            switch (D_8010FF60_chancetime[i].state) {
                case 0:
                    if (delay < frame) {
                        if (launched < count) {
                            D_8010FF60_chancetime[i].state = 1;
                            frame = 0;
                            launched++;
                            if (!isStars) {
                                lost += step;
                                value = coinsF[0] - lost;
                                if (value >= 0.0f) {
                                    GwPlayer[players[0]].coin = (u32)value;
                                } else {
                                    GwPlayer[players[0]].coin = 0;
                                }
                                HuAudFXPlay(0x109);
                            } else {
                                lost += step;
                                value = starsF[0] - lost;
                                if (value >= 0.0f) {
                                    GwPlayer[players[0]].star = (u32)value;
                                } else {
                                    GwPlayer[players[0]].star = 0;
                                }
                            }
                        }
                    }
                    break;
                case 1:
                    if (!isStars) {
                        espDispOn(D_80110028_chancetime[i]);
                        func_8000BDDC_main(D_80110028_chancetime[i], 1);
                        espBankSet(D_80110028_chancetime[i], 0, 0);
                        espPosSet(D_80110028_chancetime[i], 80, 74.0f - offsetY);
                    } else {
                        func_8001C258_main(object->model[i + 1], 4, 0);
                        func_8001C258_main(D_80110010_chancetime[i], 4, 0);
                        func_800138EC_main(D_80110010_chancetime[i], 1, 1);
                        Hu3DModelPosSet(object->model[i + 1], -170.0f, 375.0f, 0.0f);
                        func_8000CFA4_main(D_80110010_chancetime[i], -170.0f, 375.0f, 0.0f);
                    }
                    D_8010FF60_chancetime[i].timer = 0;
                    D_8010FF60_chancetime[i].state = 3;
                    break;
                case 2:
                    D_8010FF60_chancetime[i].state = 0;
                    if (!isStars) {
                        espDispOff(D_80110028_chancetime[i]);
                        gained += step;
                        value = gained + coinsF[1];
                        if (value <= 999.0f) {
                            GwPlayer[players[1]].coin = value;
                        } else {
                            GwPlayer[players[1]].coin = 999;
                        }
                        HuAudFXPlay(0x106);
                    } else {
                        func_8001C258_main(object->model[i + 1], 4, 4);
                        func_800138EC_main(D_80110010_chancetime[i], 1, 0);
                        gained += step;
                        value = gained + starsF[1];
                        if (value <= 99.0f) {
                            GwPlayer[players[1]].star = value;
                        } else {
                            GwPlayer[players[1]].star = 99;
                        }
                        HuAudFXPlay(0x11B);
                    }
                    finished++;
                    break;
                case 3:
                    timer = D_8010FF60_chancetime[i].timer;
                    if (!isStars) {
                        x = timer * 8.5f;
                        s = sindf(timer * 9.0f);
                        y = s * 32.0f;
                        espPosSet(D_80110028_chancetime[i], x + 80.0f, 74.0f - y - offsetY);
                        espScaleSet(D_80110028_chancetime[i], s * 0.5f + 0.5f, s * 0.5f + 0.5f);
                        D_8010FF60_chancetime[i].timer++;
                        if (timer >= 20) {
                            D_8010FF60_chancetime[i].state = 2;
                        }
                    } else {
                        x = timer * 9.25f;
                        t = timer;
                        s = sindf(t * 4.5f);
                        y = s * 88.0f;
                        Hu3DModelPosSet(object->model[i + 1], x + -170.0f, y + 375.0f, 0.0f);
                        func_8000CFA4_main(D_80110010_chancetime[i], x + -170.0f, y + 375.0f, 0.0f);
                        scale = s * 0.5f + 0.5f;
                        Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                        Hu3DModelRotSet(object->model[i + 1], 0.0f, t * 15.0f, 0.0f);
                        func_8000CD00_main(D_80110010_chancetime[i], s + s + 4.0f, 20.0f, s + s + 4.0f);
                        D_8010FF60_chancetime[i].timer++;
                        if (timer >= 40) {
                            D_8010FF60_chancetime[i].state = 2;
                        }
                    }
                    break;
            }
        }
        HuPrcVSleep();
        frame++;
    }

    if (!isStars) {
        value = coinsF[0] - coins;
        if (value >= 0.0f) {
            GwPlayer[players[0]].coin = value;
        } else {
            GwPlayer[players[0]].coin = 0;
        }
        value = coins + coinsF[1];
        if (value <= 999.0f) {
            GwPlayer[players[1]].coin = value;
        } else {
            GwPlayer[players[1]].coin = 999;
        }
    } else {
        value = starsF[0] - stars;
        if (value >= 0.0f) {
            GwPlayer[players[0]].star = value;
        } else {
            GwPlayer[players[0]].star = 0;
        }
        value = stars + starsF[1];
        if (value <= 99.0f) {
            GwPlayer[players[1]].star = value;
        } else {
            GwPlayer[players[1]].star = 99;
        }
    }
    MBPlayerCoinAdd(players[1], 0);
    HuPrcSleep(30);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/487F50", func_8010E4D0_chancetime);
#endif

void func_8010F1DC_chancetime(void) {
    D_8010FC10_chancetime = 0;
    D_80110084_chancetime = func_8010F1F8_chancetime;
}

void func_8010F1F8_chancetime(void) {
    HuWinHomeClear(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    func_8010BF48_chancetime();
    HuAudFXPlay(0x298);
    HuWinMesSet(D_80110004_chancetime, 0x1B00, -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (HuWinStatGet(D_80110004_chancetime)) {
        HuPrcVSleep();
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        HuWinComKeyReset();
    }
    D_80110084_chancetime = func_8010F42C_chancetime;
}

s32 func_8010F420_chancetime(void) {
    return D_8010FC10_chancetime;
}

void func_8010F42C_chancetime(void) {
    D_8010FC10_chancetime = 1;
    D_80110084_chancetime = func_8010DF70_chancetime;
}

void func_8010F44C_chancetime(s32 arg0, s32 arg1, s32 arg2) {
    u32 mes;
    s32 i;

    for (i = 0; i < 2; i++) {
        HuWinInsertMesSet(D_80110004_chancetime, D_8010FE1C_chancetime[D_801100DD_chancetime[i]], i);
    }
    if (D_801100DF_chancetime < 5) {
        if (D_8010FDF8_chancetime[D_801100DF_chancetime] != 0) {
            HuWinInsertMesSet(D_80110004_chancetime, D_8010FDF8_chancetime[D_801100DF_chancetime], 2);
        }
    } else {
        if (D_8010FDF8_chancetime[D_801100DF_chancetime] != 0) {
            HuWinInsertMesSet(D_80110004_chancetime, D_8010FDF8_chancetime[D_801100DF_chancetime], 3);
        }
    }
    HuWinHomeClear(D_80110004_chancetime);
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    func_80108B50_chancetime();
    HuWinMesSet(D_80110004_chancetime, D_8010FD8C_chancetime[arg0], -1, -1);
    func_80060C14_main(D_80110004_chancetime, 1);
    while (HuWinStatGet(D_80110004_chancetime)) {
        HuPrcVSleep();
    }
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        func_8005B63C_main(D_80110004_chancetime, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, func_800EDC40_shared_board());
    }
    if (arg2 < arg1) {
        if (arg2 > 0) {
            mes = D_8010FDB0_chancetime[arg0];
            if (mes != 0) {
                func_80060EA8_main(D_80110004_chancetime, 1);
                HuWinMesSet(D_80110004_chancetime, mes, -1, -1);
                HuAudFXPlay(0x29A);
                func_80060C14_main(D_80110004_chancetime, 1);
                while (HuWinStatGet(D_80110004_chancetime)) {
                    HuPrcVSleep();
                }
            }
        } else {
            func_80060EA8_main(D_80110004_chancetime, 1);
            HuWinMesSet(D_80110004_chancetime, D_8010FDD4_chancetime[arg0], -1, -1);
            HuAudFXPlay(0x29A);
            func_80060C14_main(D_80110004_chancetime, 1);
            while (HuWinStatGet(D_80110004_chancetime)) {
                HuPrcVSleep();
            }
        }
    }
    func_80060EA8_main(D_80110004_chancetime, 1);
    func_80108A88_chancetime();
    if (GwPlayer[D_801100D0_chancetime[0]].stat & 1) {
        HuWinComKeyReset();
    }
    D_80110084_chancetime = func_8010E1E0_chancetime;
}

void func_8010F984_chancetime(omObjData *object) {
    s32 players[4];
    s32 i;
    s32 j;
    s32 coinAmount;
    s32 starAmount;
    s16 coins;
    s16 stars;
    u16 isStars;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (D_801100DD_chancetime[i] == GwPlayer[D_801100D0_chancetime[j]].chr) {
                players[i] = D_801100D0_chancetime[j];
                break;
            }
        }
    }

    coins = D_8010FE3C_chancetime[D_801100DF_chancetime].coins;
    coinAmount = D_8010FE3C_chancetime[D_801100DF_chancetime].coins;
    starAmount = D_8010FE3C_chancetime[D_801100DF_chancetime].stars;
    stars = starAmount;
    if (coinAmount > 0) {
        if (GwPlayer[players[0]].coin < coinAmount) {
            coins = GwPlayer[players[0]].coin;
        }
        isStars = FALSE;
    } else {
        if (stars > GwPlayer[players[0]].star) {
            stars = GwPlayer[players[0]].star;
        }
        isStars = TRUE;
    }

    if (!isStars) {
        func_8010F44C_chancetime(D_801100DF_chancetime, coinAmount, coins);
    } else {
        func_8010F44C_chancetime(D_801100DF_chancetime, starAmount, stars);
    }
}

const ChanceTimeReelSpeed D_8010FD08_chancetime[3] = { { 10.0f, 10.0f }, { 20.0f, 20.0f }, { 40.0f, 40.0f } };

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD20_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD38_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD3C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD40_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD5C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD68_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FD8C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDB0_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDD4_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FDF8_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE1C_chancetime);

INCLUDE_RODATA("asm/nonmatchings/overlays/chancetime/487F50", D_8010FE3C_chancetime);
