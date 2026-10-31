#include "common.h"
#include "game/pause.h"
#include "overlays/minigame.h"
#include "mallocblock.h"
#include "math.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} CoconutConkData; // sizeof 0x84

typedef struct {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8 unk08[0xAC];
} CoconutConkCameraWork; // sizeof 0xB4

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} CoconutConkCamera; // sizeof 0x2C

extern u16 D_8010AF68_coconut_conk[][3];
extern char *D_8010AF98_coconut_conk[];
extern D_80111B50_vine_with_me_Struct D_8010AFF0_coconut_conk;
extern CoconutConkCamera D_8010B018_coconut_conk[2];
extern const s16 D_8010B1B8_coconut_conk[];
extern f32 D_8010AFB8_coconut_conk[];
extern u8 D_800D6A90_main;
extern char D_8010B0D0_coconut_conk[];
extern char D_8010B0E4_coconut_conk[];
extern HuSprite_Unk84_Struct *D_8010B1C4_coconut_conk;
extern u8 D_8010B1C8_coconut_conk;
extern void *D_8010B1D0_coconut_conk[3];
extern s16 D_8010B1DC_coconut_conk;
extern u16 D_8010B1E2_coconut_conk[2];
extern CoconutConkData D_8010B1F0_coconut_conk[50];
extern omObjData *D_8010B274_coconut_conk;
extern s16 D_8010B2B4_coconut_conk;
extern u16 D_8010B2B6_coconut_conk;
extern f32 D_8010B2B8_coconut_conk;
extern f32 D_8010B2BC_coconut_conk;
extern omObjData *D_8010B37C_coconut_conk;
extern s16 D_8010B3BC_coconut_conk;
extern u16 D_8010B3BE_coconut_conk;
extern f32 D_8010B3C0_coconut_conk;
extern f32 D_8010B3C4_coconut_conk;
extern omObjData *D_8010B400_coconut_conk;
extern omObjData *D_8010B484_coconut_conk;
extern f32 D_8010B418_coconut_conk;
extern f32 D_8010B4A0_coconut_conk;
extern f32 D_8010B4A4_coconut_conk;
extern CoconutConkData D_8010B508_coconut_conk[6];
extern CoconutConkData D_8010B820_coconut_conk[9];
extern CoconutConkData D_8010BCC4_coconut_conk;
extern CoconutConkData D_8010BD48_coconut_conk[];
extern f32 D_800EB73C_minigame;
extern s16 D_8010B1C0_coconut_conk;
extern s16 D_8010B1C2_coconut_conk;
extern u8 D_8010B1C9_coconut_conk[3];
extern u8 D_8010B1CC_coconut_conk;
extern u8 D_8010B1DE_coconut_conk;
extern s16 D_8010AF60_coconut_conk;
extern s16 D_8010AF62_coconut_conk;
extern s16 D_8010AF64_coconut_conk;
extern s16 D_8010AF66_coconut_conk;
extern s16 D_8010B1E0_coconut_conk;
extern s16 D_8010B1E6_coconut_conk;
extern s16 D_8010CBB8_coconut_conk;
extern u8 D_8010CBBA_coconut_conk;
extern s32 D_8010AFD0_coconut_conk[];
extern u8 D_8010CBBB_coconut_conk;
extern s16 D_8010CBBC_coconut_conk;
extern u8 D_8010CBBE_coconut_conk;
extern s16 D_8010CBC0_coconut_conk;
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s32 D_800EBE24_minigame;

void func_80105C58_coconut_conk(omObjData *);
void func_80105C60_coconut_conk(omObjData *);
void func_80105D98_coconut_conk(Gfx **, s32, s32);
void func_801060C0_coconut_conk(omObjData *);
void func_801060C8_coconut_conk(omObjData *);
void func_801062D4_coconut_conk(omObjData *);
void func_801061F4_coconut_conk(omObjData *);
void func_80106394_coconut_conk(omObjData *);
void func_80106468_coconut_conk(omObjData *);
void func_8010659C_coconut_conk(omObjData *);
void func_801067E0_coconut_conk(omObjData *);
void func_801069BC_coconut_conk(omObjData *);
void func_80106D5C_coconut_conk(omObjData *);
void func_80106F18_coconut_conk(omObjData *);
void func_8010815C_coconut_conk(omObjData *);
void func_801089DC_coconut_conk(omObjData *);
void func_801090C4_coconut_conk(omObjData *);
void func_80109DEC_coconut_conk(omObjData *);
void func_8010A55C_coconut_conk(omObjData *);
void func_8010A668_coconut_conk(omObjData *);
void func_8010AE04_coconut_conk(void);
void func_8000B710_main(s32);
void func_8001EF6C_main(s16, s16, char *);
void func_800E149C_minigame(omObjData *, s32, s32);
void HuAudFXPanning(s16 arg0, s16 arg1);
void func_800E4C88_minigame(omObjData *object, u8 type, f32 x, f32 y, f32 z, f32 arg5, f32 arg6);
void func_800DDD94_minigame(omObjData *);
void func_800E6F0C_minigame(s32);
void func_800E1304_minigame(omObjData *, f32);
void func_800E1310_minigame(omObjData *, f32);
void func_800E131C_minigame(omObjData *, f32);
void func_800E139C_minigame(omObjData *, f32, f32, f32, f32, f32);
void func_800335BC_main(char *name, u16 *result);
void espAttrSet(u16, u16);
void func_8001E888_main(s16 model, f32 x, f32 y, u16 arg3, u16 arg4, char *name, s32 arg6);

void func_801059A0_coconut_conk(void) {
    func_8010AE04_coconut_conk();
}

f32 func_801059BC_coconut_conk(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_coconut_conk(void) {
    CoconutConkData *data;
    u32 i;

    for (i = 0, data = D_8010B1F0_coconut_conk; i < 50; i++, data++) {
        data->unk00 = NULL;
        data->unk04 = 0;
        data->unk06 = 0;
        data->unk08 = 0;
        data->unk0A = 0;
        data->unk0C = 0;
        data->unk0E = 0;
        data->unk10 = 0;
        data->unk12 = 0;
        data->unk14 = 0;
        data->unk16 = 0;
        data->unk18 = 0.0f;
        data->unk1C = 0.0f;
        data->unk20 = 0.0f;
        data->unk24 = 0.0f;
        data->unk28 = 0.0f;
        data->unk2C = 0.0f;
        data->unk30 = 0.0f;
        data->unk34 = 0.0f;
        data->unk38 = 0.0f;
        data->unk3C = 0.0f;
        data->unk40 = -1;
        data->unk42 = -1;
        data->unk44.x = data->unk44.y = data->unk44.z = 0.0f;
        data->unk50.x = data->unk50.y = data->unk50.z = 0.0f;
        data->unk5C.x = data->unk5C.y = data->unk5C.z = 0.0f;
        data->unk68 = 0.0f;
        data->unk6C = 0.0f;
        data->unk70 = 0.0f;
        data->unk74 = 0.0f;
        data->unk78.x = data->unk78.y = data->unk78.z = 0.0f;
    }
}

void func_80105B04_coconut_conk(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_coconut_conk(u8 arg0) {
    D_8010B1C8_coconut_conk = arg0;
}

f32 func_80105B88_coconut_conk(f32 arg0, f32 *arg1, f32 arg2) {
    f32 value = *arg1;

    *arg1 = value - arg2;
    return arg0 + value;
}

void func_80105BA4_coconut_conk(omObjData *arg0, u8 arg1) {
    s32 character = GwPlayer[arg0->work[0]].chr;

    func_80033354_main(D_8010B1DC_coconut_conk);
    D_8010B1DC_coconut_conk = HmfAnimCreate(HmfModelData[arg0->model[0]].hmf, D_8010B1D0_coconut_conk[arg1], 0,
                                            D_8010AF98_coconut_conk[character]);
}

void func_80105C58_coconut_conk(omObjData *arg0) {
}

void func_80105C60_coconut_conk(omObjData *arg0) {
    CoconutConkCameraWork *work;

    D_800EC1C0_minigame[D_800EBE28_minigame++] = arg0;
    work = HuMemAllocTag(sizeof(CoconutConkCameraWork), 0x7918);
    arg0->data = work;
    memset(work, 0, sizeof(CoconutConkCameraWork));
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk06 &= ~0x200;
    func_800E131C_minigame(arg0, 20.0f);
    func_800E1304_minigame(arg0, 0.5f);
    func_800E1310_minigame(arg0, D_800EB73C_minigame);
    func_800E139C_minigame(D_800EC1C0_minigame[0], 512.0f, -1000.0f, -285.0f, 1000.0f, -165.0f);
    arg0->func = func_80105C58_coconut_conk;
}

void func_80105D58_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3E8, 1, 0xA, -1, func_80105C60_coconut_conk);
    obj->work[0] = 0;
    D_8010B1F0_coconut_conk[0].unk00 = obj;
}

void func_80105D98_coconut_conk(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx *gfx = *arg0;
    s32 x;
    s32 top;
    s32 y;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_CULL_BOTH | G_FOG | G_LOD);
    gSPSetGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, D_8010B1C4_coconut_conk->unk0C);
    x = 0;
    for (y = 0, top = 128; y < 112; y += 4) {
        gDPLoadTextureTile(gfx++, D_8010B1C4_coconut_conk->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, y, 320, y + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (top + y) << 2, (x + 320) << 2, (top + y + 4) << 2, G_TX_RENDERTILE, 0, 0,
                            1024, 1024);
    }
    *arg0 = gfx;
}

void func_801060C0_coconut_conk(omObjData *arg0) {
}

void func_801060C8_coconut_conk(omObjData *arg0) {
    D_8010B2B4_coconut_conk = func_8000B838_main(0x23000D);
    D_8010B2B6_coconut_conk = espEntry(D_8010B2B4_coconut_conk, 0, 0);
    espAttrSet(D_8010B2B6_coconut_conk, 0x4000);
    D_8010B2B8_coconut_conk = 160.0f;
    D_8010B2BC_coconut_conk = 67.0f;
    espPosSet(D_8010B2B6_coconut_conk, 160, 67);
    D_8010B1C4_coconut_conk = func_80055194_main(func_8000B838_main(0x23000E));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80105D98_coconut_conk, 2), 1);
    arg0->func = func_801060C0_coconut_conk;
}

void func_801061AC_coconut_conk(void) {
    omObjData *obj = omAddObj(0x384, 1, 0xA, -1, func_801060C8_coconut_conk);
    obj->work[0] = 0;
    D_8010B274_coconut_conk = obj;
}

void func_801061EC_coconut_conk(omObjData *arg0) {
}

void func_801061F4_coconut_conk(omObjData *arg0) {
    D_8010B3BC_coconut_conk = func_8000B838_main(0x23000F);
    D_8010B3BE_coconut_conk = espEntry(D_8010B3BC_coconut_conk, 0, 0);
    espAttrSet(D_8010B3BE_coconut_conk, 0);
    D_8010B3C0_coconut_conk = 160.0f;
    D_8010B3C4_coconut_conk = 219.0f;
    espPosSet(D_8010B3BE_coconut_conk, 160, 219);
    arg0->func = func_801061EC_coconut_conk;
}

void func_80106294_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, func_801061F4_coconut_conk);
    obj->work[0] = 0;
    D_8010B37C_coconut_conk = obj;
}

void func_801062D4_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B1F0_coconut_conk[4];

    if (omPauseChk() + D_800D6A90_main == 0) {
        data->unk18 += 0.2f;
    }
    func_8001E888_main(arg0->model[0], 0.0f, data->unk18, D_8010B1E2_coconut_conk[0], D_8010B1E2_coconut_conk[1],
                       D_8010B0D0_coconut_conk, 0);
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

void func_80106394_coconut_conk(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x230004, 0x289);
    func_8001C954_main(arg0->model[0]);
    func_800335BC_main(D_8010B0E4_coconut_conk, D_8010B1E2_coconut_conk);
    D_8010B418_coconut_conk = 0.0f;
    arg0->trans.x = 0.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = 0.0f;
    Hu3DModelCameraSet(arg0->model[0], 1);
    arg0->func = func_801062D4_coconut_conk;
}

void func_8010641C_coconut_conk(void) {
    omObjData *obj = omAddObj(0x35C, 1, 0, -1, func_80106394_coconut_conk);
    obj->work[0] = 0;
    D_8010B400_coconut_conk = obj;
    omSetStatBit(obj, 0xA0);
}

void func_80106468_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B1F0_coconut_conk[5];

    switch (data->unk04) {
        case 0:
            data->unk1C += 0.005f;
            data->unk20 -= 0.005f;
            if (data->unk1C > 1.1f) {
                data->unk04 = 1;
            }
            break;
        case 1:
            data->unk1C -= 0.005f;
            data->unk20 += 0.005f;
            if (data->unk1C < 1.0f) {
                data->unk04 = 0;
            }
            break;
    }
    arg0->scale.x = arg0->scale.y = arg0->scale.z = data->unk1C;
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    Hu3DModelScaleSet(arg0->model[1], data->unk20, data->unk20, data->unk20);
}

void func_8010659C_coconut_conk(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x230005, 0x289);
    arg0->model[1] = func_8000B108_main(0x230005, 0x289);
    arg0->trans.x = -400.0f;
    arg0->trans.y = 700.0f;
    arg0->trans.z = -1000.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -1000.0f);
    Hu3DModelPosSet(arg0->model[1], 450.0f, 750.0f, -1000.0f);
    D_8010B4A0_coconut_conk = 1.0f;
    D_8010B4A4_coconut_conk = 1.0f;
    Hu3DModelCameraSet(arg0->model[0], 2);
    Hu3DModelCameraSet(arg0->model[1], 2);
    arg0->func = func_80106468_coconut_conk;
}

void func_801066A4_coconut_conk(void) {
    omObjData *obj = omAddObj(0x366, 5, 0xA, -1, func_8010659C_coconut_conk);
    obj->work[0] = 0;
    D_8010B484_coconut_conk = obj;
}

void func_801066E4_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B508_coconut_conk[arg0->work[0]];

    switch (data->unk04) {
        case 0:
            Hu3DMotionTimeSet(arg0->model[0], 0.0f);
            Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            break;
        case 1:
            Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
            if (D_800CCF58_main[HmfModelData[arg0->model[0]].motId].unk02 == HmfModelData[arg0->model[0]].motTime) {
                data->unk04 = 0;
            }
            break;
    }
}

void func_801067E0_coconut_conk(omObjData *arg0) {
    if (arg0->work[0] % 3 == 0) {
        arg0->model[0] = func_8000B108_main(0x230001, 0x299);
    }
    if (arg0->work[0] % 3 == 1) {
        arg0->model[0] = func_8000B108_main(0x230003, 0x299);
    }
    if (arg0->work[0] % 3 == 2) {
        arg0->model[0] = func_8000B108_main(0x23000C, 0x299);
    }
    arg0->trans.x = D_8010AFB8_coconut_conk[arg0->work[0]];
    arg0->trans.y = 0.0f;
    arg0->trans.z = -225.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -225.0f);
    Hu3DModelCameraSet(arg0->model[0], 2);
    arg0->func = func_801066E4_coconut_conk;
}

void func_80106924_coconut_conk(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        CoconutConkData *data = &D_8010B508_coconut_conk[i];
        omObjData *obj = omAddObj(0x352, 1, 0xA, -1, func_801067E0_coconut_conk);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

void func_801069BC_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B820_coconut_conk[arg0->work[0]];
    s16 sound;
    s16 pan;

    switch (data->unk04) {
        case 0:
            Hu3DMotionTimeSet(arg0->model[0], 0.0f);
            Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            func_8001C258_main(arg0->model[0], 4, 4);
            break;
        case 1:
            func_8001C258_main(arg0->model[0], 4, 0);
            arg0->trans.y = 422.0f - (++data->unk06 & 1) * 10.0f;
            if (data->unk06 > 0) {
                data->unk04 = 2;
                data->unk06 = 0;
                arg0->trans.y = 422.0f;
            }
            break;
        case 2:
            arg0->trans.y -= data->unk18;
            data->unk18 += 1.5f;
            arg0->trans.z += 4.0f;
            if (arg0->trans.y < 0.0f) {
                arg0->trans.y = 0.0f;
                data->unk04 = 3;
                data->unk18 = 0.0f;
                func_800E4C88_minigame(arg0, 1, arg0->trans.x, arg0->trans.y, arg0->trans.z, 0.0f, 0.0f);
            }
            break;
        case 3:
            if (data->unk06 == 0) {
                Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
                sound = HuAudFXPlay(D_8010AF62_coconut_conk);
                pan = (arg0->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan > 127) {
                    pan = 127;
                }
                HuAudFXPanning(sound, pan);
            }
            if ((++data->unk06 & 3) < 3) {
                func_8001C258_main(arg0->model[0], 4, 0);
            } else {
                func_8001C258_main(arg0->model[0], 4, 4);
            }
            if (data->unk06 >= 16) {
                D_8010B1DE_coconut_conk--;
                data->unk04 = 0;
                data->unk06 = 0;
                arg0->trans.z = -200.0f;
                func_8001C258_main(arg0->model[0], 4, 4);
                Hu3DMotionTimeSet(arg0->model[0], 0.0f);
                Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            }
            break;
        case 4:
            if (data->unk06 == 0) {
                Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
                sound = HuAudFXPlay(D_8010AF64_coconut_conk);
                pan = (arg0->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan > 127) {
                    pan = 127;
                }
            }
            if ((++data->unk06 & 3) < 3) {
                func_8001C258_main(arg0->model[0], 4, 0);
            } else {
                func_8001C258_main(arg0->model[0], 4, 4);
            }
            if (data->unk06 >= 16) {
                D_8010B1DE_coconut_conk--;
                data->unk04 = 0;
                data->unk06 = 0;
                arg0->trans.z = -200.0f;
                func_8001C258_main(arg0->model[0], 4, 4);
                Hu3DMotionTimeSet(arg0->model[0], 0.0f);
                Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            }
            break;
    }
}

void func_80106D40_coconut_conk(omObjData *arg0) {
    func_801069BC_coconut_conk(arg0);
}

void func_80106D5C_coconut_conk(omObjData *arg0) {
    if (arg0->work[0] < 3) {
        arg0->model[0] = func_8000B108_main(0x23000B, 0x289);
    }
    if (arg0->work[0] - 3 < 3) {
        arg0->model[0] = func_8000B108_main(0x23000A, 0x289);
    }
    if (arg0->work[0] >= 6) {
        arg0->model[0] = func_8000B108_main(0x230002, 0x289);
    }
    arg0->trans.x = arg0->trans.y = 0.0f;
    arg0->trans.z = -200.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -200.0f);
    arg0->model[1] = func_8000B108_main(7, 0x2AD);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], 2);
    Hu3DModelCameraSet(arg0->model[1], 2);
    arg0->func = func_80106D40_coconut_conk;
}

void func_80106E80_coconut_conk(void) {
    u8 i;

    for (i = 0; i < 9; i++) {
        CoconutConkData *data = &D_8010B820_coconut_conk[i];
        omObjData *obj = omAddObj(0x320, 5, 0xA, -1, func_80106D5C_coconut_conk);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

#ifdef NON_MATCHING
// Matches except for t2/t3 register allocation of mode and middle.
void func_80106F18_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;
    u16 player = arg0->work[0];
    f32 target = 0.0f;
    f32 gaps[4];
    f32 pos[3];
    u8 input;
    u8 middle;
    u8 mode;
    u8 left;
    u8 right;
    u8 widest;
    s16 i;
    s16 j;
    omObjData *obj;
    CoconutConkData *entry;

    input = rand8();
    mode = 0;
    if (((GwPlayer[player].cpu_difficulty == 0) & (input < 50)) ||
        ((GwPlayer[player].cpu_difficulty == 1) & (input < 150)) ||
        ((GwPlayer[player].cpu_difficulty == 2) & (input < 180)) ||
        ((GwPlayer[player].cpu_difficulty == 3) & (input < 255))) {
        for (i = 0; i < 3; i++) {
            CoconutConkData *e = &D_8010BD48_coconut_conk[i];
            omObjData *o = e->unk00;

            pos[i] = o->trans.x;
            if (o->trans.x + 39.0f > arg0->trans.x - 40.0f && o->trans.x - 39.0f < arg0->trans.x + 40.0f) {
                mode = 1;
            }
        }
        for (i = 0; i < 3; i++) {
            entry = &D_8010B820_coconut_conk[i];
            obj = entry->unk00;
            if (entry->unk04 == 1 || entry->unk04 == 2) {
                if (obj->trans.x + 29.0f > arg0->trans.x - 40.0f && obj->trans.x - 29.0f < arg0->trans.x + 40.0f) {
                    mode = 2;
                }
            }
        }
        if (mode == 1) {
            left = 0;
            middle = 0;
            right = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    if (pos[left] > pos[j]) {
                        left = j;
                    }
                }
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    if (pos[right] < pos[j]) {
                        right = j;
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (i != left && i != right) {
                    middle = i;
                }
            }
            gaps[0] = fabsf(-450.0f - pos[left]);
            gaps[1] = fabsf(pos[left] - pos[middle]);
            gaps[2] = fabsf(pos[middle] - pos[right]);
            gaps[3] = fabsf(pos[right] - 450.0f);
            widest = 0;
            for (i = 0; i < 3; i++) {
                if (gaps[i] < gaps[i + 1]) {
                    widest = i + 1;
                }
            }
            switch (widest) {
                case 0:
                    target = (pos[left] + -450.0f) * 0.5f;
                    break;
                case 1:
                    target = (pos[left] + pos[middle]) * 0.5f;
                    break;
                case 2:
                    target = (pos[middle] + pos[right]) * 0.5f;
                    break;
                case 3:
                    target = (pos[right] + 450.0f) * 0.5f;
                    break;
            }
            if (target + 60.0f < arg0->trans.x) {
                input = 1;
            } else if (arg0->trans.x < target - 60.0f) {
                input = 2;
            }
        }
        if (mode == 2) {
            if (data->unk18 <= 0.0f) {
                input = 1;
            } else {
                input = 2;
            }
        }
        if (mode == 0) {
            if (0.0f < data->unk18) {
                input = 1;
            } else if (data->unk18 < 0.0f) {
                input = 2;
            }
        }
    }
    data->unk06--;
    if (data->unk06 <= 0) {
        data->unk06 = 0;
    }
    if (input == 0) {
        data->unk04 = 0;
    }
    if (input % 5 == 1 && data->unk06 == 0) {
        data->unk04 = 1;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                data->unk06 = 30;
                break;
            case 1:
                data->unk06 = 10;
                break;
            case 2:
                data->unk06 = 7;
                break;
            case 3:
                data->unk06 = 1;
                break;
        }
    }
    if (input % 5 == 2 && data->unk06 == 0) {
        data->unk04 = 2;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                data->unk06 = 30;
                break;
            case 1:
                data->unk06 = 10;
                break;
            case 2:
                data->unk06 = 7;
                break;
            case 3:
                data->unk06 = 1;
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106F18_coconut_conk);
#endif

void func_80107674_coconut_conk(omObjData *arg0) {
    func_80106F18_coconut_conk(arg0);
}

void func_80107690_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;

    data->unk04 = 0;
    if (D_800CBB6E_main[arg0->work[3]] <= -30) {
        data->unk04 = 1;
    }
    if (D_800CBB6E_main[arg0->work[3]] >= 30) {
        data->unk04 = 2;
    }
}

void func_801076EC_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;

    switch (data->unk04) {
        case 0:
            if (data->unk18 < 0.0f) {
                data->unk18 += 0.05;
            }
            if (data->unk18 > 0.0f) {
                data->unk18 -= 0.05;
            }
            if ((s16)data->unk18 == 0) {
                data->unk18 = 0.0f;
                arg0->trans.x = (s16)arg0->trans.x;
            }
            break;
        case 1:
            if (data->unk18 > -10.0f) {
                data->unk18 -= 0.5f;
                if (data->unk18 < -10.0f) {
                    data->unk18 = -10.0f;
                }
            }
            break;
        case 2:
            if (data->unk18 < 10.0f) {
                data->unk18 += 0.5f;
                if (data->unk18 > 10.0f) {
                    data->unk18 = 10.0f;
                }
            }
            break;
    }
    arg0->rot.z = func_801059BC_coconut_conk(arg0->rot.z, -data->unk18);
    arg0->trans.x += data->unk18;
}

void func_801078BC_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;
    f32 nextX;

    switch (data->unk04) {
        case 0:
            if (data->unk18 < 0.0f) {
                data->unk18 += 0.05;
            }
            if (data->unk18 > 0.0f) {
                data->unk18 -= 0.05;
            }
            if ((s16)data->unk18 == 0) {
                data->unk18 = 0.0f;
                arg0->trans.x = (s16)arg0->trans.x;
            }
            break;
        case 1:
            if (data->unk18 > -7.0f) {
                data->unk18 -= 0.45f;
                if (data->unk18 < -7.0f) {
                    data->unk18 = -7.0f;
                }
            }
            break;
        case 2:
            if (data->unk18 < 7.0f) {
                data->unk18 += 0.45f;
                if (data->unk18 > 7.0f) {
                    data->unk18 = 7.0f;
                }
            }
            break;
    }
    if (data->unk18 >= -3.0f && data->unk18 <= 3.0f) {
        D_8010B1C0_coconut_conk++;
        if (D_8010B1C0_coconut_conk > 500) {
            D_8010B1C0_coconut_conk = 500;
        }
    } else {
        D_8010B1C0_coconut_conk = 0;
    }
    nextX = arg0->trans.x + data->unk18;
    if ((nextX >= 450.0f) | (nextX <= -450.0f)) {
        data->unk18 = -(data->unk18 * 0.5f);
    }
    arg0->rot.z = func_801059BC_coconut_conk(arg0->rot.z, -data->unk18);
    arg0->trans.x += data->unk18;
}

void func_80107B8C_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;
    s16 i;
    s16 sound;

    for (i = 0; i < 9; i++) {
        CoconutConkData *coconut = &D_8010B820_coconut_conk[i];
        omObjData *obj = coconut->unk00;

        if (coconut->unk04 == 2 && obj->trans.x + 29.0f >= arg0->trans.x - 40.0f &&
            obj->trans.x - 29.0f <= arg0->trans.x + 40.0f && obj->trans.y + 84.0f >= arg0->trans.y - 50.0f &&
            obj->trans.y <= arg0->trans.y + 50.0f) {
            if (D_8010B1C8_coconut_conk == 2 && D_8010B1E0_coconut_conk > 0) {
                D_8010B1CC_coconut_conk = 1;
                func_80105BA4_coconut_conk(arg0, 2);
                Hu3DMotionSpeedSet(arg0->model[6], 1.0f);
                func_8001C258_main(arg0->model[6], 4, 0);
                Hu3DModelPosSet(arg0->model[6], arg0->trans.x, arg0->trans.y + 50.0f, arg0->trans.z);
                data->unk0A = 1;
                if (!(GwPlayer[arg0->work[0]].stat & 1)) {
                    omVibrate(arg0->work[0], 20, 0, 20);
                }
            }
            coconut->unk04 = 4;
        }
    }
    if (D_800CCF58_main[HmfModelData[arg0->model[6]].motId].unk02 <= HmfModelData[arg0->model[6]].motTime) {
        func_8001C258_main(arg0->model[6], 4, 4);
        func_8001C258_main(arg0->model[7], 4, 0);
        Hu3DModelPosSet(arg0->model[7], arg0->trans.x, arg0->trans.y + 50.0f, arg0->trans.z + 40.0f);
        if (data->unk0C == 0) {
            sound = PlayerFXPlay(D_8010AF60_coconut_conk, arg0->work[0]);
            data->unk0C++;
            HuAudFXPitchSet(sound, 0);
            HuAudFXVolSet(sound, 127);
        }
    }
    switch (data->unk0A) {
        case 0:
            data->unk28 = data->unk24 = 1.0f;
            break;
        case 1:
            func_8001C258_main(arg0->model[3], 0x4000, 0);
            data->unk24 = 0.5f;
            data->unk28 = 1.3f;
            data->unk0A = 2;
            break;
        case 2:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.5f) {
                data->unk0A = 3;
            }
            break;
        case 3:
            data->unk24 -= 0.1f;
            data->unk28 += 0.06f;
            if (data->unk24 <= 0.5f) {
                data->unk0A = 4;
            }
            break;
        case 4:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.5f) {
                data->unk0A = 5;
            }
            break;
        case 5:
            data->unk24 -= 0.1f;
            data->unk28 += 0.06f;
            if (data->unk24 <= 0.5f) {
                data->unk0A = 6;
            }
            break;
        case 6:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.0f) {
                data->unk0A = 7;
            }
            break;
    }
    Hu3DModelPosSet(arg0->model[3], arg0->trans.x, 40.0f, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[3], 90.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[3], data->unk28, 1.0f, data->unk24);
}

void func_8010815C_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;
    u16 player = arg0->work[0];
    s16 pan;

    switch (D_8010B1C8_coconut_conk) {
        case 0:
            switch (data->unk08) {
                case 0:
                    data->unk04 = 1;
                    if (arg0->trans.x < 30.0f) {
                        data->unk08 = 1;
                    }
                    break;
                case 1:
                    data->unk04 = 2;
                    if (data->unk18 > 2.5f) {
                        data->unk08 = 2;
                    }
                    break;
                case 2:
                    data->unk04 = 0;
                    if ((s16)arg0->rot.z >= 350.0f || (s16)arg0->rot.z <= 5.0f) {
                        if (arg0->trans.x >= -5.0f && arg0->trans.x <= 5.0f) {
                            arg0->rot.z = 0.0f;
                            data->unk04 = 0;
                            data->unk18 = 0.0f;
                            data->unk08 = 3;
                        }
                    }
                    break;
                case 3:
                    D_8010CBBA_coconut_conk = 0;
                    data->unk08 = 0;
                    break;
            }
            func_801076EC_coconut_conk(arg0);
            break;
        case 2:
            if (D_8010B1E0_coconut_conk > 0 && D_8010B1CC_coconut_conk == 0) {
                if (GwPlayer[player].stat & 1) {
                    func_80107674_coconut_conk(arg0);
                } else {
                    func_80107690_coconut_conk(arg0);
                }
                func_801078BC_coconut_conk(arg0);
            }
            func_80107B8C_coconut_conk(arg0);
            break;
        case 3:
            func_80107B8C_coconut_conk(arg0);
            data->unk18 = 0.0f;
            break;
        case 4:
            func_80107B8C_coconut_conk(arg0);
            if (D_8010B1CC_coconut_conk != 0) {
                break;
            }
            switch (data->unk08) {
                case 0:
                    func_8001C258_main(arg0->model[3], 4, 4);
                    func_8001C258_main(arg0->model[3], 0x4000, 0);
                    Hu3DMotionSpeedSet(arg0->model[4], 1.0f);
                    func_8001C258_main(arg0->model[4], 4, 0);
                    Hu3DModelPosSet(arg0->model[4], arg0->trans.x, arg0->trans.y + 20.0f, arg0->trans.z);
                    Hu3DMotionSpeedSet(arg0->model[5], 1.0f);
                    func_8001C258_main(arg0->model[5], 4, 0);
                    Hu3DModelPosSet(arg0->model[5], arg0->trans.x, arg0->trans.y + 20.0f, arg0->trans.z);
                    func_80105BA4_coconut_conk(arg0, 1);
                    arg0->rot.z = 0.0f;
                    func_8001C5B4_main(arg0->model[0], arg0->motion[1]);
                    data->unk1C = 30.0f;
                    data->unk08 = 1;
                    break;
                case 1:
                    arg0->trans.y = func_80105B88_coconut_conk(arg0->trans.y, &data->unk1C, 3.0f);
                    if (arg0->trans.y <= 0.0f) {
                        arg0->trans.y = 0.0f;
                        data->unk08 = 2;
                        Hu3DMotionShiftSet(arg0->model[0], HmfModelData[arg0->motion[2]].motId, 0, 5, 0);
                        func_80045ED0_main((D_8010AFD0_coconut_conk[GwPlayer[arg0->work[0]].chr] << 16) | 0x2F);
                    }
                    data->unk20 -= 9.0f;
                    if (data->unk20 < 0.0f) {
                        data->unk20 = 0.0f;
                    }
                    func_8001F9E4_main(arg0->model[4], data->unk20);
                    if (D_800CCF58_main[HmfModelData[arg0->model[4]].motId].unk02 <= HmfModelData[arg0->model[4]].motTime) {
                        func_8001C258_main(arg0->model[4], 4, 4);
                    }
                    if (D_800CCF58_main[HmfModelData[arg0->model[5]].motId].unk02 <= HmfModelData[arg0->model[5]].motTime) {
                        func_8001C258_main(arg0->model[5], 4, 4);
                    }
                    break;
                case 2:
                    data->unk20 -= 9.0f;
                    if (data->unk20 < 0.0f) {
                        data->unk20 = 0.0f;
                    }
                    func_8001F9E4_main(arg0->model[4], data->unk20);
                    if (D_800CCF58_main[HmfModelData[arg0->model[4]].motId].unk02 <= HmfModelData[arg0->model[4]].motTime) {
                        func_8001C258_main(arg0->model[4], 4, 4);
                    }
                    if (D_800CCF58_main[HmfModelData[arg0->model[5]].motId].unk02 <= HmfModelData[arg0->model[5]].motTime) {
                        func_8001C258_main(arg0->model[5], 4, 4);
                    }
                    break;
            }
            break;
        case 1:
        case 5:
            break;
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    if (++D_8010CBB8_coconut_conk >= 100) {
        D_8010CBB8_coconut_conk = 0;
    }
    if (D_8010CBC0_coconut_conk == -1) {
        D_8010CBC0_coconut_conk = func_8004AC98_main(D_8010AF66_coconut_conk, arg0->work[0]);
        if (D_8010CBC0_coconut_conk == -1) {
            return;
        }
        D_8010B1E6_coconut_conk = -400;
        HuAudFXPitchSet(D_8010CBC0_coconut_conk, -400);
        D_8010B1C2_coconut_conk = 0;
        HuAudFXVolSet(D_8010CBC0_coconut_conk, D_8010B1C2_coconut_conk);
        if (D_8010CBC0_coconut_conk == -1) {
            return;
        }
    }
    if (D_8010B1C8_coconut_conk < 3) {
        if (!(D_8010CBB8_coconut_conk & 1)) {
            D_8010B1E6_coconut_conk = fabs(data->unk18 * 60.0f) + 0.0;
            if (D_8010B1E6_coconut_conk > 400) {
                D_8010B1E6_coconut_conk = 400;
            } else if (D_8010B1E6_coconut_conk < 0) {
                D_8010B1E6_coconut_conk = 0;
            }
            HuAudFXPitchSet(D_8010CBC0_coconut_conk, D_8010B1E6_coconut_conk);
        } else {
            D_8010B1C2_coconut_conk = fabs(data->unk18 * 20.0f) + 0.0;
            if (D_8010B1C2_coconut_conk > 125) {
                D_8010B1C2_coconut_conk = 125;
            } else if (D_8010B1C2_coconut_conk < 0) {
                D_8010B1C2_coconut_conk = 0;
            }
            HuAudFXVolSet(D_8010CBC0_coconut_conk, D_8010B1C2_coconut_conk);
        }
        pan = (arg0->trans.x + 450.0f) * 0.143f;
        if (pan < 0) {
            pan = 0;
        } else if (pan > 127) {
            pan = 127;
        }
        HuAudFXPanning(D_8010CBC0_coconut_conk, pan);
    }
}

void func_801089DC_coconut_conk(omObjData *obj) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;
    s8 chr = GwPlayer[obj->work[0]].chr;
    s32 model = D_800A178C_main[chr][0];
    s16 i;

    obj->model[0] = func_8000B108_main(model | D_800A178C_main[chr][2], 0x2A9);
    for (i = 0; i < 3; i++) {
        D_8010B1D0_coconut_conk[i] = DataRead(model | D_8010AF68_coconut_conk[chr][i]);
    }
    D_8010B1DC_coconut_conk = HmfAnimCreate(HmfModelData[obj->model[0]].hmf, D_8010B1D0_coconut_conk[0], 0,
                                            D_8010AF98_coconut_conk[chr]);
    func_8001C448_main(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x62));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 4));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    obj->trans.x = 400.0f;
    obj->trans.y = 40.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    data->unk18 = -10.0f;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 325.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = func_8000B0A0_main(0, 0x4A9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    func_8001C448_main(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    obj->model[2] = func_8000B108_main(8, 0x2BD);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->model[3] = func_8000B108_main(0x230000, 0x299);
    Hu3DModelPosSet(obj->model[3], 0.0f, 0.0f, 0.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    func_8001EF6C_main(obj->model[3], obj->model[0], "item_hook");
    obj->model[4] = func_8000B108_main(0x230006, 0x28D);
    Hu3DModelPosSet(obj->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[4], 0.0f);
    Hu3DMotionSpeedSet(obj->model[4], 0.0f);
    func_8001FA68_main(obj->model[4]);
    data->unk20 = 255.0f;
    func_8001F9E4_main(obj->model[4], 0xFF);
    obj->model[5] = func_8000B108_main(0x230007, 0x29D);
    Hu3DModelPosSet(obj->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[5], 0.0f);
    Hu3DMotionSpeedSet(obj->model[5], 0.0f);
    obj->model[6] = func_8000B108_main(0x230008, 0x29D);
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[6], 3.0f);
    Hu3DMotionSpeedSet(obj->model[6], 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.5f, 1.5f, 1.5f);
    obj->model[7] = func_8000B108_main(0x230009, 0x29D);
    Hu3DModelPosSet(obj->model[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[7], 1.5f, 1.5f, 1.5f);
    func_8001C814_main(obj->model[7], 2, 2);
    Hu3DModelCameraSet(obj->model[0], 2);
    Hu3DModelCameraSet(obj->model[1], 2);
    Hu3DModelCameraSet(obj->model[2], 2);
    Hu3DModelCameraSet(obj->model[3], 2);
    Hu3DModelCameraSet(obj->model[4], 2);
    Hu3DModelCameraSet(obj->model[5], 2);
    Hu3DModelCameraSet(obj->model[6], 2);
    Hu3DModelCameraSet(obj->model[7], 2);
    obj->func = func_8010815C_coconut_conk;
}

void func_80108FA0_coconut_conk(void) {
    u16 player = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            omObjData *obj;

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
            }
            obj = omAddObj(0x2BC, 9, 0x3C, -1, func_801089DC_coconut_conk);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            D_8010BCC4_coconut_conk.unk00 = obj;
        }
    }
}

void func_801090C4_coconut_conk(omObjData *arg0) {
    CoconutConkData *coconuts[3];
    omObjData *objs[3];
    CoconutConkData *data = &D_8010BD48_coconut_conk[arg0->work[1]];
    u16 player = arg0->work[0];
    u8 dir = rand8();
    omObjData *target = D_8010BD48_coconut_conk[-1].unk00;
    f32 minDist;
    s16 closest;
    s16 i;

    if (D_8010B1C8_coconut_conk == 2) {
        u8 difficulty = GwPlayer[player].cpu_difficulty;

        if ((difficulty == 0 && dir < 50) || (difficulty == 1 && dir < 80) || (difficulty == 2 && dir < 100) ||
            (difficulty == 3 && dir < 130)) {
            if (target->trans.x < arg0->trans.x) {
                dir = 1;
            } else {
                dir = 2;
            }
        }
    }
    if (D_8010CBBB_coconut_conk == 3 && D_8010B1C0_coconut_conk >= D_8010CBBC_coconut_conk) {
        closest = 0;
        minDist = 5000.0f;
        for (i = 0; i < 3; i++) {
            coconuts[i] = &D_8010BD48_coconut_conk[i];
            objs[i] = coconuts[i]->unk00;
        }
        for (i = 0; i < 3; i++) {
            if (minDist >= fabs(objs[i]->trans.x - target->trans.x)) {
                closest = i;
                minDist = fabs(objs[i]->trans.x - target->trans.x);
            }
        }
        dir = 0;
        if (arg0->work[1] == closest) {
            if (arg0->trans.x > target->trans.x) {
                dir = 1;
            } else if (arg0->trans.x < target->trans.x) {
                dir = 2;
            }
            if (arg0->trans.x + 29.0f > target->trans.x - 40.0f && arg0->trans.x - 29.0f < target->trans.x + 40.0f) {
                D_800D5558_main[arg0->work[3]] |= 0x8000;
                D_800D5558_main[arg0->work[3]] |= 0x2000;
            }
        } else {
            D_800D5558_main[arg0->work[3]] |= 0x8000;
        }
    }
    data->unk06--;
    if (data->unk06 <= 0) {
        data->unk06 = 0;
    }
    if (arg0->trans.y > 512.0f) {
        dir = 0;
    }
    if (dir == 0 && data->unk06 == 0) {
        data->unk08 = 0;
    }
    if (dir % 5 == 1 && data->unk06 == 0) {
        data->unk08 = -(rand8() & 0x1F) - 30;
        data->unk06 = 15;
    }
    if (dir % 5 == 2 && data->unk06 == 0) {
        data->unk08 = (rand8() & 0x1F) + 30;
        data->unk06 = 15;
    }
    D_800CBB6E_main[arg0->work[3]] = data->unk08;
    if (rand8() % 70 == 0) {
        D_800D5558_main[arg0->work[3]] |= 0x8000;
    }
    if (rand8() % 5 == 0) {
        D_800D5558_main[arg0->work[3]] |= 0x2000;
    }
}

void func_801095C0_coconut_conk(omObjData *);
void func_801095C8_coconut_conk(omObjData *);

void func_801095A4_coconut_conk(omObjData *arg0) {
    func_801090C4_coconut_conk(arg0);
}

void func_801095C0_coconut_conk(omObjData *arg0) {
}

#ifdef NON_MATCHING
void func_801095C8_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BD48_coconut_conk[arg0->work[1]];
    func_800E1BA8_minigame_ObjData *work = arg0->data;
    CoconutConkData *target;
    f32 minDist;
    s16 closest;
    s16 i;

    if (D_800D20A1_main[arg0->work[3]] >= 5) {
        D_800D20A1_main[arg0->work[3]] = 0;
    }
    if (D_800D20A1_main[arg0->work[3]] < -4) {
        D_800D20A1_main[arg0->work[3]] = 0;
    }
    func_800DDD94_minigame(arg0);
    if (HmfModelData[arg0->model[7]].motTime == 0.0f) {
        func_8001C258_main(arg0->model[7], 4, 4);
    }
    if (work->unk5C == 0x200 && work->unk50 == 0x80 && data->unk04 == 0) {
        data->unk04 = 1;
        if (D_8010B1DE_coconut_conk < 3) {
            D_8010B1DE_coconut_conk++;
            func_800E4C88_minigame(arg0, 7, arg0->trans.x, arg0->trans.y, arg0->trans.z, 0.0f, 0.0f);
            minDist = 3000.0f;
            closest = 0;
            for (i = 0; i < 6; i++) {
                if (fabs(arg0->trans.x - D_8010AFB8_coconut_conk[i]) < minDist) {
                    minDist = fabs(arg0->trans.x - D_8010AFB8_coconut_conk[i]);
                    closest = i;
                }
            }
            target = &D_8010B508_coconut_conk[closest];
            if (target->unk04 == 0) {
                target->unk04 = 1;
                data->unk16 = 1;
            }
            switch (closest) {
                case 0:
                case 3:
                    for (i = 0; i < 3; i++) {
                        CoconutConkData *coconut = &D_8010B820_coconut_conk[i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
                case 1:
                case 4:
                    for (i = 3; i < 6; i++) {
                        CoconutConkData *coconut = &D_8010B820_coconut_conk[i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
                case 2:
                case 5:
                    for (i = 6; i < 9; i++) {
                        CoconutConkData *coconut = &D_8010B820_coconut_conk[i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
            }
        }
    }
    if (work->unk5C != 0x200 && work->unk50 != 0x80 && arg0->trans.y <= 512.0f) {
        data->unk04 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801095C8_coconut_conk);
#endif

void func_80109940_coconut_conk(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *works[3];
    CoconutConkData *datas[3];
    omObjData *objs[3];
    CoconutConkData *data = &D_8010BD48_coconut_conk[arg0->work[1]];
    func_800E1BA8_minigame_ObjData *work = arg0->data;
    s16 i;

    if (D_8010B1C8_coconut_conk != 2) {
        func_80105B04_coconut_conk(arg0->work[0]);
    }
    data->unk18 = arg0->trans.x;
    switch (D_8010B1C8_coconut_conk) {
        case 2:
            if (D_8010B1E0_coconut_conk > 0 && D_8010B1CC_coconut_conk == 0) {
                if (!(GwPlayer[arg0->work[0]].stat & 1)) {
                    func_801095C0_coconut_conk(arg0);
                } else {
                    func_801095A4_coconut_conk(arg0);
                }
            }
            func_801095C8_coconut_conk(arg0);
            break;
        case 3:
            if (arg0->trans.y > 512.0f) {
                if (++data->unk0C > 30000) {
                    data->unk0C = 0;
                }
                if (data->unk0C < 70) {
                    D_800CBB6E_main[arg0->work[3]] = -40;
                } else if (data->unk0C < 140) {
                    D_800CBB6E_main[arg0->work[3]] = 40;
                }
                if (data->unk0C >= 140) {
                    func_801095A4_coconut_conk(arg0);
                }
                func_801095C8_coconut_conk(arg0);
                break;
            }
            if (work->unk3C != 0.0f) {
                D_800CBB6E_main[arg0->work[3]] = 0;
                D_800D20A1_main[arg0->work[3]] = -40;
            }
            for (i = 0; i < 3; i++) {
                datas[i] = &D_8010BD48_coconut_conk[i];
                objs[i] = datas[i]->unk00;
                works[i] = objs[i]->data;
            }
            if (objs[0]->trans.y <= 512.0f && works[0]->unk3C == 0.0f &&
                (works[0]->unk50 == 0 || works[0]->unk50 == 0x80) && works[0]->unk5C == 2 &&
                objs[1]->trans.y <= 512.0f && works[1]->unk3C == 0.0f &&
                (works[1]->unk50 == 0 || works[1]->unk50 == 0x80) && works[1]->unk5C == works[0]->unk5C &&
                objs[2]->trans.y <= 512.0f && works[2]->unk3C == 0.0f &&
                (works[2]->unk50 == 0 || works[2]->unk50 == 0x80) && works[2]->unk5C == works[1]->unk5C) {
                D_8010CBBA_coconut_conk = 3;
            }
            func_800DDD94_minigame(arg0);
            break;
        case 4:
            if (data->unk0E == 0) {
                if (D_8010B1CC_coconut_conk == 0) {
                    func_800E5690_minigame(arg0, 14);
                    data->unk0E = 1;
                } else {
                    func_800E5690_minigame(arg0, 13);
                    data->unk0E = 1;
                    func_80045ED0_main((D_8010AFD0_coconut_conk[GwPlayer[arg0->work[0]].chr] << 16) | 0x2F);
                }
            }
            break;
        case 0:
        case 1:
        case 5:
            break;
    }
    if (D_8010B1C8_coconut_conk != 2 && D_8010B1C8_coconut_conk != 3) {
        func_800DDD94_minigame(arg0);
    }
    if (arg0->trans.x < -450.0f) {
        arg0->trans.x = -450.0f;
    }
    if (arg0->trans.x > 450.0f) {
        arg0->trans.x = 450.0f;
    }
    if (work->unk53[1] != -1) {
        arg0->trans.x = data->unk18;
    }
    func_8001C258_main(arg0->model[1], 4, 4);
    if (data->unk16 > 0) {
        data->unk16++;
    }
    if (data->unk16 >= 4) {
        func_8004AC98_main(0x313, arg0->work[0]);
        data->unk16 = 0;
    }
}

void func_80109DEC_coconut_conk(omObjData *arg0) {
    u16 character = GwPlayer[arg0->work[0]].chr;
    s32 modelFile;
    s32 motionFile;
    func_800E1BA8_minigame_ObjData *work;
    u8 slot;

    if (GwPlayer[arg0->work[0]].stat & 1) {
        D_8010CBBB_coconut_conk++;
        switch (GwPlayer[arg0->work[0]].cpu_difficulty) {
            case 0:
                if (D_8010CBBC_coconut_conk > 60) {
                    D_8010CBBC_coconut_conk = 60;
                }
                break;
            case 1:
                if (D_8010CBBC_coconut_conk > 30) {
                    D_8010CBBC_coconut_conk = 30;
                }
                break;
            case 2:
                if (D_8010CBBC_coconut_conk > 15) {
                    D_8010CBBC_coconut_conk = 15;
                }
                break;
            case 3:
                if (D_8010CBBC_coconut_conk > 10) {
                    D_8010CBBC_coconut_conk = 10;
                }
                break;
        }
    }
    modelFile = D_800A178C_main[character][0];
    motionFile = D_800A1790_main[character][0];
    func_800E18D8_minigame();
    func_800E1BA8_minigame(arg0, modelFile, motionFile, ((u16 *)arg0->work)[1], 0x2B9, 0x2A9);
    work = arg0->data;
    work->unkEC = 0;
    func_8001C2FC_main(arg0->model[1], 0x80000000, 0);
    func_8001C258_main(arg0->model[1], 0x60, 0x20);
    func_8001C258_main(arg0->model[1], 0x180, 0x80);
    func_8001C448_main(arg0->model[1]);
    func_8001C514_main(arg0->model[1]);
    arg0->model[7] = func_8000B108_main(8, 0x2BD);
    arg0->model[6] = func_8000B108_main(5, 0x2BD);
    func_800E5A00_minigame(arg0, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(arg0, 1, func_80017BB8_main(character, 1), 1, 0);
    func_800E5A00_minigame(arg0, 2, func_80017BB8_main(character, 2), 1, 0);
    func_800E5A00_minigame(arg0, 6, func_80017BB8_main(character, 4), 1, 0x13);
    func_800E5A00_minigame(arg0, 8, func_80017BB8_main(character, 6), 1, 0x1B);
    func_800E5A00_minigame(arg0, 0x12, func_80017BB8_main(character, 0xF), 2, 0);
    func_800E5978_minigame(arg0, 0x15, func_80017BB8_main(character, 0x1F), 0, 0);
    func_800E5A00_minigame(arg0, 0xD, func_80017BB8_main(character, 0x2F), 1, 0x78);
    func_800E5A00_minigame(arg0, 0xE, func_80017BB8_main(character, 0x36), 1, 0x3E7);
    func_800E5690_minigame(arg0, 0);
    D_800EBE24_minigame = 1;
    slot = rand8() % 3;
    while (TRUE) {
        if (slot != D_8010B1C9_coconut_conk[0] && slot != D_8010B1C9_coconut_conk[1]) {
            D_8010B1C9_coconut_conk[D_8010CBBE_coconut_conk] = slot;
            D_8010CBBE_coconut_conk++;
            switch (slot) {
                case 0:
                    arg0->trans.x = -300.0f;
                    break;
                case 1:
                    arg0->trans.x = 0.0f;
                    break;
                case 2:
                    arg0->trans.x = 300.0f;
                    break;
            }
            break;
        }
        slot++;
        if (slot >= 3) {
            slot = 0;
        }
    }
    arg0->trans.y = 512.0f;
    arg0->trans.z = -225.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[7], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[6], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], 2);
    Hu3DModelCameraSet(arg0->model[1], 2);
    Hu3DModelCameraSet(arg0->model[7], 2);
    Hu3DModelCameraSet(arg0->model[6], 2);
    func_800E149C_minigame(arg0, 0, 2);
    func_80105B04_coconut_conk(arg0->work[0]);
    arg0->func = func_80109940_coconut_conk;
}

void func_8010A344_coconut_conk(void) {
    u16 player = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            CoconutConkData *data;
            omObjData *obj;

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
            }
            data = &D_8010BD48_coconut_conk[count];
            obj = omAddObj(0x28A, 9, 0x3C, -1, func_80109DEC_coconut_conk);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            data->unk00 = obj;
            obj->work[1] = count++;
            D_800EC598_minigame[D_800EC280_minigame] = obj;
            D_800EC280_minigame++;
        }
    }
}

void func_8010A4AC_coconut_conk(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1270.8f;
        CRotM[i].x = 350.94f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 415.0f;
        CenterM[i].z = -115.0f;
    }
}

void func_8010A55C_coconut_conk(omObjData *arg0) {
    u8 i;

    for (i = 0; i < 3; i++) {
        DataClose(D_8010B1D0_coconut_conk[i]);
    }
    func_80033354_main(D_8010B1DC_coconut_conk);
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010A5D8_coconut_conk(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = func_8010A55C_coconut_conk;
    }
}

void func_8010A610_coconut_conk(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        arg0->func = func_8010A5D8_coconut_conk;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010A668_coconut_conk(omObjData *arg0) {
    u8 chars[8];
    CoconutConkData *datas[3];
    omObjData *objs[3];
    omObjData *obj = D_8010BCC4_coconut_conk.unk00;
    s16 i;
    s16 j;

    for (i = 0; i < 3; i++) {
        datas[i] = &D_8010BD48_coconut_conk[i];
        objs[i] = datas[i]->unk00;
    }

    switch (D_8010B1C8_coconut_conk) {
        case 0:
            if (D_8010B1E0_coconut_conk == 13) {
                HuAudFXPlay(0x314);
                D_8010B1E0_coconut_conk = 14;
            } else if (D_8010B1E0_coconut_conk < 13) {
                D_8010B1E0_coconut_conk++;
            }
            if (D_8010CBBA_coconut_conk == 0) {
                func_80105B7C_coconut_conk(1);
                D_8010B1E0_coconut_conk = 1;
                HuAudSeqPlay(0x30);
            }
            break;
        case 1:
            if (--D_8010B1E0_coconut_conk == 0) {
                GMesCreate(4);
            }
            if (GMesStatGet() == 0) {
                func_80105B7C_coconut_conk(2);
                GMesCreate(0x1A, 30, 160, 28);
                D_8010B1E0_coconut_conk = 901;
            }
            break;
        case 2:
            if (D_8010B1E0_coconut_conk > 0) {
                D_8010B1E0_coconut_conk--;
                func_8003F578_main((D_8010B1E0_coconut_conk + 29) / 30);
            } else if (D_8010B1CC_coconut_conk == 0) {
                func_8003F5C0_main();
                func_80105B7C_coconut_conk(3);
                GMesCreate(0xF);
                D_8010B1CC_coconut_conk = 0;
                D_8010B1E0_coconut_conk = -15;
                HuAudSeqFadeOut(120);
                HuAudFXStop(D_8010CBC0_coconut_conk);
            }
            if (D_8010B1CC_coconut_conk == 1) {
                func_8003F5C0_main();
                func_80105B7C_coconut_conk(3);
                GMesCreate(0xF);
                D_8010B1CC_coconut_conk = 1;
                D_8010B1E0_coconut_conk = -15;
                HuAudSeqFadeOut(120);
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                if (D_8010B1E0_coconut_conk >= 0) {
                    if (D_8010CBBA_coconut_conk == 3) {
                        func_80105B7C_coconut_conk(4);
                        D_8010B1E0_coconut_conk = -1;
                        break;
                    }
                }
                if (D_8010B1E0_coconut_conk < 0) {
                    D_8010B1E0_coconut_conk++;
                }
            }
            break;
        case 4:
            if (D_8010B1E0_coconut_conk == -1) {
                D_8010B1E0_coconut_conk = 0;
                j = 0;
                if (D_8010B1CC_coconut_conk == 0) {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group == 0) {
                            chars[0] = GwPlayer[i].chr;
                        }
                    }
                    GMesCreate(0x16, chars[0]);
                    HuAudSeqPlay(0x65);
                    GwPlayer[obj->work[0]].bonusCoin = 10;
                } else {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group != 0) {
                            chars[j] = GwPlayer[i].chr;
                            j++;
                        }
                    }
                    GMesCreate(0x22, chars[0], chars[1], chars[2]);
                    HuAudSeqPlay(0x66);
                    for (i = 0; i < 3; i++) {
                        GwPlayer[objs[i]->work[0]].bonusCoin = 10;
                    }
                }
            }
            if (GMesStatGet() == 0) {
                if (D_8010B1E0_coconut_conk >= 15) {
                    func_80105B7C_coconut_conk(5);
                    D_8010B1E0_coconut_conk = -1;
                }
                D_8010B1E0_coconut_conk++;
            }
            break;
        case 5:
            if (D_8010B1E0_coconut_conk == 0) {
                WipeCreateOut(0, 20);
                arg0->func = func_8010A5D8_coconut_conk;
                D_8010B1E0_coconut_conk++;
            }
            break;
    }
}

void func_8010AB4C_coconut_conk(omObjData *arg0) {
    s16 i;

    func_800E6F0C_minigame(2);
    WipeCreateIn(0xFF, 16);
    D_8010B1E0_coconut_conk = 0;
    D_8010B1C8_coconut_conk = 0;
    D_8010CBBA_coconut_conk = 100;
    for (i = 0; i < 3; i++) {
        D_8010B1C9_coconut_conk[i] = 5;
    }
    D_8010CBBE_coconut_conk = 0;
    D_8010B1C0_coconut_conk = 0;
    D_8010CBBB_coconut_conk = 0;
    D_8010CBBC_coconut_conk = 500;
    D_8010B1CC_coconut_conk = 0;
    D_8010B1DE_coconut_conk = 0;
    D_8010CBC0_coconut_conk = -1;
    D_8010B1E6_coconut_conk = -400;
    D_8010B1C2_coconut_conk = 0;
    D_8010CBB8_coconut_conk = 0;
    func_80105D58_coconut_conk();
    func_801061AC_coconut_conk();
    func_80106294_coconut_conk();
    func_8010641C_coconut_conk();
    func_801066A4_coconut_conk();
    func_80108FA0_coconut_conk();
    func_8010A344_coconut_conk();
    func_80106E80_coconut_conk();
    func_80106924_coconut_conk();
    func_8010A4AC_coconut_conk();
    arg0->func = func_8010A668_coconut_conk;
}

void func_8010AC88_coconut_conk(void) {
}

void func_8010AC90_coconut_conk(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, 0xA0);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010B018_coconut_conk[i].scissorX, D_8010B018_coconut_conk[i].scissorY,
                   D_8010B018_coconut_conk[i].scissorWidth, D_8010B018_coconut_conk[i].scissorHeight);
        ViewportSet(i, D_8010B018_coconut_conk[i].viewportScale.x, D_8010B018_coconut_conk[i].viewportScale.y,
                    D_8010B018_coconut_conk[i].viewportScale.z, D_8010B018_coconut_conk[i].viewportTranslate.x,
                    D_8010B018_coconut_conk[i].viewportTranslate.y, D_8010B018_coconut_conk[i].viewportTranslate.z);
        Hu3DCamSetPerspective(i, D_8010B018_coconut_conk[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010AE04_coconut_conk(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010AC90_coconut_conk();
    HmfLightMaxSet(1);
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(0, -84.0f, 49.0f, 69.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -84.0f, 49.0f, 69.0f);
    HmfLightColorSet(2, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(2, -84.0f, 49.0f, 69.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010B1B8_coconut_conk, 0);
    func_80045010_main(D_8010B1B8_coconut_conk, 1);
    omAddObj(0x5DC, 0, 0, -1, func_8010AB4C_coconut_conk);
    omAddObj(0x5DC, 0, 0, -1, func_8010A610_coconut_conk);
    func_80105A3C_coconut_conk();
    func_800E5EA0_minigame(&D_8010AFF0_coconut_conk);
}

// Keep this table after the functions to preserve the original rodata order.
const s16 D_8010B1B8_coconut_conk[] = { 0x8260, 0x8261, 0x8262, 0 };
