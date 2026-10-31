#include "common.h"
#include "gcc/string.h"
#include "game/hmfman.h"
#include "game/camera.h"
#include "game/hmflight.h"
#include "macros.h"
#include "mallocblock.h"
#include "include_asm.h"

s32 func_80023264_main(HmfData *);
extern s32 D_800A0530_main;
extern s32 D_800C9940_main;

// graphics.c
u8 func_8000EF64_main(void *arg0, u16 arg1, s32 arg2, void *arg3, s32 arg4);

// hmfload.c
void func_8000F978_main(HmfData *);
s16 func_80011460_main(u8 *);

// hmfparticle.c
void func_800139AC_main(s16 model, s16 group);

// hmfspr.c
void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out);

// hmflight.c
void func_80019668_main(HmfData_UnkD0 *light);

// hmfcoll.c
void func_80021AF4_main(void);
void func_80021B20_main(s16 index);

// hmfdraw.c
void func_800222B0_main(void *arg0, void *arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5);
void func_800224BC_main(void);
void func_80022660_main(HmfData *);
void func_800225D4_main(void);
void func_80023404_main(HmfData *arg0, HuMtx4F arg1, HuMtx4F arg2);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
Gfx *func_800250D4_main(s16 arg0, Gfx *arg1, Gfx *arg2);
s32 func_8002F60C_main(HmfData *hmf);
s16 func_8002C834_main(HmfData *, char *);
void func_8002D260_main(void);
s32 func_8002D3AC_main(void *);
void func_8002D514_main(void);
void func_80030030_main(f32);
f32 func_8002FC7C_main(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed);

// hmfshape.c
void func_80030178_main(s32 arg0);
void func_800303C8_main(HmfModel *model, f32 time);
void func_80030198_main(void);
s32 func_800300A4_main(void *, void *);

// hmfanim.c
extern HmfData_Unk84_Entry2 *D_800D1FCC_main;
void func_8003186C_main(HmfData *hmf);
HmfData_Unk84_Entry2 *func_80031A44_main(HmfData *hmf, char *name);
void func_80033450_main(void);
void func_80033510_main(void);
void func_80034048_main(s16 animIdx, s16 count);
void HmfAnimExec(u16 vcount);

// 8AC70.c
void func_8008A070_main(void *);

// hmfspr.c
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);

// libhmath/gurotaterpy.c
void func_80088910_main(HuMtx4F mtx, f32 r, f32 p, f32 h);

// camera.c
void func_80012E54_main(s16 camIndex);

// wipe.c
void WipeExecAlways(Gfx **gfx);

// printfunc.c
Gfx *pfDrawFonts(Gfx *gfx);

// unknown
void func_8000D3AC_main(void);

Gfx *func_8001BD24_main(Gfx *arg0, s16 arg1, u16 arg2);
void func_8001F038_main(HmfModel *model, u16 speed);
void func_8001F154_main(HmfModel *model);
void func_8001F4BC_main(s16 idx);

void func_8001D874_main(HmfData *hmf, f32 arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8001DACC_main(HmfData *hmf, f32 arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8001DDB8_main(HmfData *hmf, f32 arg1, f32 arg2, u16 arg3, u16 arg4);
void func_8001CF1C_main(HmfData *hmf1, HmfData *hmf2, f32 arg2, s16 node1, s16 node2, s32 arg5);

extern Gfx *gMainGfxPos;

void Hmfload(HmfData *, void *, s32);
void *func_80010AC8_main(void *);
void Hu3DFogClear(void);
s32 func_8001FF04_main(s32);
s32 func_8002D2D8_main(void *, HmfData *);

extern u8 D_800A0540_main;
extern u8 D_800A0541_main;
extern u8 D_800A0542_main;
extern Gfx D_800A09B0_main[];
extern Gfx D_800A0A08_main[];
extern Gfx D_800A0A38_main[];
extern f32 D_800A0A7C_main;
extern s16 D_800A0A78_main;
extern s16 D_800C9932_main;
extern s32 D_800C9940_main;
extern u16 D_800CBB72_main[];
extern s8 D_800CC0A8_main;
extern s16 D_800CC0B6_main;
extern void (*D_800CC3D8_main[])(Gfx **, HuCamMtxs *, s16);
extern u16 D_800CD2F6_main;
extern s8 D_800CDA84_main;
extern s16 D_800CDD6A_main;
extern HmfData D_800CB8C0_main;
extern u8 D_800CE19A_main;
extern s8 D_800CE1C6_main;
extern u8 D_800CD280_main;
extern HuCamMtxs *D_800D0444_main;
extern s8 D_800D0599_main;
extern u16 D_800D05A0_main[][128];
extern Gfx *D_800D1FF8_main;
extern u8 D_800CD6A6_main;
extern s16 D_800D418E_main;
extern Gfx D_800A09C8_main[];
extern HmfDrawEntry *D_800D2070_main[8];
extern HmfDrawObject *D_800CC0BC_main;
extern s32 D_800A08B0_main;
extern HuCamera *D_800D10F4_main;
extern s32 D_800D1F70_main;
extern s32 D_800D1FE8_main;
extern u8 D_800D2008_main;
extern s8 HmfPauseF;
extern u16 D_800D20EE_main;
extern s8 D_800D41C4_main;
extern u16 D_800D5204_main;
extern s16 D_800D6B64_main;

const char D_800A6BB8_main[] = "%x\n";
const char D_800A6BBC_main[] = "Model Entry Over!\n";

void func_8001A070_main(void *arg0, void *arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5) {
    s16 modelId;

    func_800222B0_main(arg0, arg1, arg2, arg3, arg4, arg5);
    func_8002D260_main();
    HmfModelData = HuMemAlloc(HU3D_MODEL_MAX * sizeof(HmfModel));
    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        HmfModelData[modelId].hmf = NULL;
    }
    func_800224BC_main();
    D_800D20AC_main = 0;
    D_800D1F70_main = 0;
    D_800D20EE_main = 1;
    HmfPauseF = 0;
    D_800CD280_main = 1;
    D_800CC3D8_main[0] = D_800CC3D8_main[1] = 0;
    func_8000D3AC_main();
    D_800D1FE8_main = 0;
}

s16 Hu3DModelCreate(u8 *data, u32 arg1) {
    HmfModel *modelP;
    HmfData *hmf;
    void *var_a1;
    s16 modelId;
    s16 var_a0;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (HmfModelData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    D_800D5204_main = TAG_MODEL + modelId * 2;
    D_800CDD6A_main = TAG_MODEL + 1 + modelId * 2;
    modelP = &HmfModelData[modelId];
    modelP->unk08 = 0xFF;
    hmf = modelP->hmf = HuMemAlloc(sizeof(HmfData));
    hmf->unk0E = D_800D5204_main;
    if (data[0] == 'M' && data[1] == 'T') {
        hmf->unk14 = 0;
        hmf->unk84 = 0;
        hmf->unk38 = 0;
        hmf->unkC8 = 0;
        hmf->unk98 = NULL;
        if (data[2] == 'N' && data[3] == 'X') {
            modelP->motId = func_8002D3AC_main(data);
            arg1 &= ~(0x10 | 0x1);
        } else {
            var_a1 = data + 8;
            if (data[8] == 'M') {
                if (data[9] == 'T' && data[10] == 'N' && data[11] == 'X') {
                    modelP->motId = func_8002D3AC_main(var_a1);
                    arg1 &= ~0x11;
                    var_a1 = func_80010AC8_main(data + 12);
                } else {
                    modelP->motId = 0xFF;
                }
            } else {
                modelP->motId = 0xFF;
            }
            modelP->unk08 = func_800300A4_main(data, var_a1);
        }
    } else {
        Hmfload(hmf, data, arg1);
        if (hmf->unk38 != 0) {
            HuMemSetTag(hmf->unk50, D_800CDD6A_main);
            modelP->unk10 = func_8001FF04_main(modelId);
        } else {
            modelP->unk10 = -1;
        }
        hmf->unk00 = (arg1 >> HU3D_ATTR_LAYER_SHIFT) & 7;
        modelP->attr = arg1;
        modelP->motId = func_8002D2D8_main(data, hmf);
        if (modelP->motId != 0xFF) {
            if (hmf->unk14 == 0) {
                func_8000F978_main(hmf);
            } else {
                goto skip;
            }
        }
    }
    if (hmf->unk14 == 0) {
        arg1 |= HU3D_ATTR_DISPOFF;
    }
skip:
    modelP->attr = arg1;
    if (arg1 & 8) {
        gFreeFunc(data);
    }
    if (arg1 & HU3D_ATTR_STATIC) {
        D_800C9940_main = modelP->attr;
        func_80022660_main(hmf);
    }
    hmf->unk0B = 1;
    if (arg1 & HU3D_ATTR_DYNAMICFREE) {
        for (var_a0 = 0; var_a0 < hmf->unk10; var_a0++) {
            if (hmf->unk60[var_a0].unk50 & 0x06000000) {
                break;
            }
        }
        if (var_a0 == hmf->unk10) {
            HuMemFreeAllWithTag(D_800D5204_main);
        }
    }
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 =
                            modelP->motShapeTime =
                                modelP->motShapeAttr =
                                    modelP->unk60 = 0;
    modelP->motShapeSpeed = 1.0f;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShape = -1;
    modelP->motIdShift = -1;
    modelP->unk09 = -1;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->cameraBit = HU3D_CAM_ALL;
    modelP->unk00 = 0;
    modelP->unkB4 = 0;
    func_8008A070_main(modelP->mtx);
    D_800D1FE8_main++;
    return modelId;
}

s32 Hu3DModelLink(s16 linkMdlId) {
    HmfModel *modelP;
    s16 modelId;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (HmfModelData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    modelP = &HmfModelData[modelId];
    modelP->hmf = HmfModelData[linkMdlId].hmf;
    modelP->attr = HmfModelData[linkMdlId].attr;
    modelP->unk00 = HmfModelData[linkMdlId].unk00;
    modelP->unk10 = HmfModelData[linkMdlId].unk10;
    modelP->motId = HmfModelData[linkMdlId].motId;
    modelP->hmf->unk0B++;
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 =
                            modelP->motShapeTime =
                                modelP->motShapeAttr =
                                    modelP->unk60 = 0;
    modelP->motShapeSpeed = 1.0f;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShape = -1;
    modelP->motIdShift = -1;
    modelP->unk09 = -1;
    modelP->unk08 = -1;
    modelP->unkB4 = 0;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->cameraBit = HU3D_CAM_ALL;
    func_8008A070_main(modelP->mtx);
    D_800D1FE8_main++;
    return modelId;
}

s32 func_8001A894_main(u32 flags, void *dl, s32 mode) {
    HmfModel *modelP;
    HmfData *hmf;
    s16 modelId;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (HmfModelData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(D_800A6BBC_main);
        return -1;
    }
    D_800D5204_main = TAG_MODEL + modelId * 2;
    D_800CDD6A_main = TAG_MODEL + 1 + modelId * 2;
    modelP = &HmfModelData[modelId];
    hmf = modelP->hmf = HuMemAllocTag(sizeof(HmfData), D_800CDD6A_main);
    hmf->unk0E = D_800D5204_main;
    hmf->unk3C = dl;
    hmf->unk0B = 1;
    hmf->unk00 = (flags >> HU3D_ATTR_LAYER_SHIFT) & 7;
    modelP->hookFunc = NULL;
    modelP->hmf->unk98 = NULL;
    modelP->unk08 = 0xFF;
    modelP->attr = flags | HU3D_ATTR_STATIC;
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 = 0;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShift = 0xFF;
    modelP->motId = 0xFF;
    modelP->unk09 = 0xFF;
    modelP->unkB4 = NULL;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    switch (mode & 6) {
        case 4:
            func_8008A070_main(modelP->mtx);
            hmf->unk3C = HuMemAllocTag(4, D_800CDD6A_main);
            hmf->unk3C->unk00[0] = dl;
            hmf->unk60 = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk60_Struct), D_800CDD6A_main);
            hmf->unk10 = 1;
            hmf->unk14 = 1;
            hmf->unk38 = NULL;
            hmf->unkC8 = NULL;
            hmf->unk60->unk50 = 0;
            hmf->unk60->unk20 = -1;
            hmf->unk60->unk5C = (HmfData_Unk84_Entry *)-1;
            hmf->unk60->unk60 = NULL;
            hmf->unkB4 = NULL;
            hmf->unk0A = 0;
            hmf->unkD4 = func_80017D24_main;
            hmf->unkD8 = func_80088910_main;
            hmf->unk60->boundsMin[0] = hmf->unk60->boundsMin[1] = hmf->unk60->boundsMin[2] = -0x8000;
            hmf->unk60->boundsMax[0] = hmf->unk60->boundsMax[1] = hmf->unk60->boundsMax[2] = -0x8000;
        case 0:
        case 2:
            modelP->cameraBit = HU3D_CAM_ALL;
            break;
        case 6:
            modelP->cameraBit = HU3D_CAM_NONE;
            break;
    }
    modelP->unk00 = mode | 1;
    D_800D1FE8_main++;
    return modelId;
}
s16 func_8001ABD4_main(s16 arg0, s8 arg1) {
    s16 idx = Hu3DModelLink(arg0);

    if (idx < 0) {
        return -1;
    }
    HmfModelData[idx].unk00 = arg1;
    return idx;
}

void func_8001AC34_main(s16 arg0, s32 arg1) {
    HmfModel *model = &HmfModelData[arg0];
    u8 flags = (model->unk00 & 0xF9) | 1;
    u8 newFlags = arg1 | flags;

    model->unk00 = newFlags;
    if ((arg1 & 0xFF) == 6) {
        model->cameraBit = HU3D_CAM_NONE;
    } else {
        model->cameraBit = HU3D_CAM_ALL;
    }
}

s32 Hu3DHookFuncCreate(s32 arg0, void (*arg1)(Gfx **, s32, s32), u8 arg2) {
    s16 idx = func_8001A894_main(arg0, NULL, arg2);
    HmfModel *var_v1 = &HmfModelData[idx];

    var_v1->hookFunc = arg1;
    return idx;
}

void Hu3DModelKill(s16 idx) {
    HmfData *hmf;
    s16 i;

    if (HmfModelData[idx].hmf == NULL) {
        return;
    }
    D_800D1FE8_main--;
    if (HmfModelData[idx].unk09 != 0xFF && HmfModelData[idx].unk14 != 0.0f) {
        hmf = HmfModelData[idx].unk6C;
    } else {
        hmf = HmfModelData[idx].hmf;
    }
    HmfModelData[idx].hmf = NULL;
    if (HmfModelData[idx].unk00 & 1) {
        if (--hmf->unk0B == 0) {
            func_80019C68_main(hmf->unk0E);
            func_80019C68_main(hmf->unk0E + 1);
        }
        return;
    }
    if (HmfModelData[idx].unk00 != 0) {
        return;
    }
    if (--hmf->unk0B != 0) {
        return;
    }
    if (hmf->unkBC != NULL) {
        for (i = 0; i < 6; i++) {
            if (gCameraList[i].unk4 == idx) {
                gCameraList[i].unk4 = -1;
                break;
            }
        }
    }
    func_80019C68_main(hmf->unk0E);
    func_80019C68_main(hmf->unk0E + 1);
    func_8003186C_main(hmf);
    if (hmf->unk38 != NULL) {
        func_80021B20_main(HmfModelData[idx].unk10);
    }
    if (HmfModelData[idx].unk08 != 0xFF) {
        func_80030178_main(HmfModelData[idx].unk08);
    }
    if (hmf->unkC8 != NULL) {
        for (i = 0; i < hmf->unk2A; i++) {
            func_80033354_main(hmf->unkC8[i]);
        }
    }
    func_80019C00_main(hmf);
    if (HmfModelData[idx].motId != 0xFF) {
        func_8002D4B8_main((s16)HmfModelData[idx].motId);
    }
}
void Hu3DModelAllKill(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (HmfModelData[i].hmf != NULL) {
            Hu3DModelKill(i);
        }
    }
    func_80033510_main();
    func_80033450_main();
    func_80030198_main();
    func_80021AF4_main();
    func_8002D514_main();
    Hu3DFogClear();
    D_800CC3D8_main[0] = D_800CC3D8_main[1] = 0;
    func_80030030_main(1.0f);
    func_80019968_main(1);
    func_8000D3AC_main();
}

void Hu3DExec(void *arg0, u16 arg1) {
    HuMtx4F mtx;
    HuMtx4F scaleMtx;
    HuMtx4F camMtx;
    HmfModel *model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *bc;
    Gfx *bgDl;
    Gfx *gfxStart;
    Gfx *gfx;
    s32 mask;
    s32 sample;
    s32 count;
    s32 i;
    s32 group;

    mask = 1;
    gfxStart = NULL;
    if (D_800D20EE_main == 0) {
        return;
    }
    gSPEndDisplayList(gMainGfxPos++);
    D_800CBB72_main[0] = D_800CBB72_main[1] = D_800CBB72_main[2] = D_800CBB72_main[3] = 0;
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        model = &HmfModelData[i];
        if (model->hmf != NULL && !(model->attr & HU3D_ATTR_DISPOFF) && model->unk00 != 0) {
            group = (model->unk00 & 6) >> 1;
            D_800D05A0_main[group][D_800CBB72_main[group]] = i;
            D_800CBB72_main[group]++;
        }
    }
    bgDl = D_800D1FF8_main;
    D_800CE19A_main = 0;
    for (D_800CD6A6_main = 0; D_800CD6A6_main < D_800C9932_main; D_800CD6A6_main++) {
        if (bgDl == NULL) {
            gfxStart = func_8001BD24_main(gfxStart, 1, mask);
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            func_8000EF64_main(gfxStart, D_800CE19A_main, 0, NULL, 0);
        }
        func_800225D4_main();
        D_800D10F4_main = &gCameraList[D_800CD6A6_main];
        D_800D0444_main = &D_800D10F4_main->mtxs[D_800D418E_main];
        gfxStart = gMainGfxPos;
        if (D_800D10F4_main->unk4 != -1) {
            func_80012E54_main(D_800CD6A6_main);
        }
        Hu3DCameraSet(D_800CD6A6_main, &gMainGfxPos);
        func_800127C4_main(D_800CD6A6_main, &gMainGfxPos);
        mask = 1 << (s16)D_800CD6A6_main;
        gSPDisplayList(gMainGfxPos++, D_800A09C8_main);
        gSPEndDisplayList(gMainGfxPos++);
        gfx = gMainGfxPos;
        if (bgDl != NULL) {
            gSPDisplayList(gMainGfxPos++, bgDl);
        }
        func_800127C4_main(D_800CD6A6_main, &gMainGfxPos);
        if (D_800D10F4_main->unkA8 != NULL) {
            D_800D10F4_main->unkA8(D_800CD6A6_main);
        }
        if (D_800CC3D8_main[0] != NULL) {
            D_800CC3D8_main[0](&gMainGfxPos, D_800D0444_main, D_800CD6A6_main);
        }
        if (D_800CC3D8_main[1] != NULL) {
            D_800CC3D8_main[1](&gMainGfxPos, D_800D0444_main, D_800CD6A6_main);
        }
        gfx = func_8001BD24_main(gfx, 0, mask);
        gSPEndDisplayList(gMainGfxPos++);
        sample = func_8004D6AC_main(200, 255, 0);
        count = D_800D1FE8_main;
        for (i = 0; count != 0; i++) {
            model = &HmfModelData[i];
            if (model->hmf == NULL) {
                continue;
            }
            count--;
            if (model->attr & HU3D_ATTR_REMAKESTATIC) {
                Hu3DModelRemakeStatic(i);
            }
            hmf = model->hmf;
            if (D_800CD6A6_main == 0) {
                hmf->unk0C = 0;
            }
            if (model->attr & HU3D_ATTR_DISPOFF) {
                continue;
            }
            if (!(model->cameraBit & mask)) {
                continue;
            }
            if (model->unk00 != 0 && (model->unk00 & 6) != 4) {
                continue;
            }
            if (hmf->unk38 != NULL && D_800D10F4_main->unkA0 != NULL) {
                D_800D10F4_main->unkA0(D_800D10F4_main->unkA4, model);
                continue;
            }
            if (model->unk09 != 0xFF) {
                func_8001F4BC_main(i);
            }
            if (model->attr & 0x1000000) {
                bc = model->unkBC;
                if ((!HmfPauseF || (model->attr & HU3D_ATTR_NOPAUSE)) && !(bc->unk04 & 2)) {
                    bc->unk18(i);
                }
                func_800139AC_main(i, bc->unk00);
            }
            hmf->unk0A = 1;
            hmf->unk01 = model->unk00;
            D_800C9940_main = model->attr;
            if (!(model->attr & 0x40000)) {
                guMtxL2F(camMtx, &D_800D0444_main->lookAtMtx);
                if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
                    func_80017C10_main(camMtx, model->pos.x, model->pos.y, model->pos.z);
                }
                if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
                    func_80017D24_main(camMtx, model->rot.x, model->rot.y, model->rot.z);
                }
                if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
                    func_80017CD0_main(camMtx, model->scale.x, model->scale.y, model->scale.z);
                    scaleMtx[0][0] = model->scale.x;
                    scaleMtx[1][1] = model->scale.y;
                    scaleMtx[2][2] = model->scale.z;
                    scaleMtx[3][3] = 1.0f;
                    scaleMtx[0][1] = scaleMtx[0][2] = scaleMtx[0][3] = scaleMtx[1][0] = scaleMtx[1][2] =
                        scaleMtx[1][3] = scaleMtx[2][0] = scaleMtx[2][1] = scaleMtx[2][3] = scaleMtx[3][0] =
                            scaleMtx[3][1] = scaleMtx[3][2] = 0.0f;
                } else {
                    func_8008A070_main(scaleMtx);
                }
                func_80018044_main(model->mtx, camMtx, mtx);
            } else {
                func_8002367C_main(mtx, model->mtx);
                if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
                    func_80017C10_main(mtx, model->pos.x, model->pos.y, model->pos.z);
                }
                if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
                    func_80017D24_main(mtx, model->rot.x, model->rot.y, model->rot.z);
                }
                if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
                    func_80017CD0_main(mtx, model->scale.x, model->scale.y, model->scale.z);
                    scaleMtx[0][0] = model->scale.x;
                    scaleMtx[1][1] = model->scale.y;
                    scaleMtx[2][2] = model->scale.z;
                    scaleMtx[3][3] = 1.0f;
                    scaleMtx[0][1] = scaleMtx[0][2] = scaleMtx[0][3] = scaleMtx[1][0] = scaleMtx[1][2] =
                        scaleMtx[1][3] = scaleMtx[2][0] = scaleMtx[2][1] = scaleMtx[2][3] = scaleMtx[3][0] =
                            scaleMtx[3][1] = scaleMtx[3][2] = 0.0f;
                } else {
                    func_8008A070_main(scaleMtx);
                }
            }
            hmf->unkD0 = model->unkB4;
            if (model->unkB4 != NULL) {
                func_80019668_main(model->unkB4);
            }
            if (model->motId != 0xFF) {
                hmf->unk8C = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motId];
                hmf->unkA0 = model->motTime;
                if (model->motIdShape != 0xFF) {
                    hmf->unk94 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motIdShape];
                    hmf->unkAC = model->motShapeTime;
                } else {
                    hmf->unk94 = NULL;
                }
                if (model->motIdShift != 0xFF) {
                    if (model->unk0C != 0) {
                        hmf->unk90 = (HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motIdShift];
                        hmf->unkA4 = model->motShiftTime;
                        hmf->unkA8 = (f32)model->unk0E / model->unk0C;
                        if (!HmfPauseF) {
                            model->unk0E += arg1;
                        }
                        if (model->unk0E >= model->unk0C) {
                            model->motId = model->motIdShift;
                            model->motTime = model->motShiftTime;
                            model->motAttr = model->motShiftAttr;
                            model->unk48 = model->unk54;
                            model->motIdShift = 0xFF;
                        }
                    } else {
                        hmf->unk90 = NULL;
                    }
                } else {
                    hmf->unk90 = NULL;
                }
            } else {
                hmf->unk8C = hmf->unk90 = hmf->unk94 = NULL;
            }
            if (D_800C9940_main & 0x4000) {
                func_80089980_main(mtx, D_800CC0BC_main[D_800D2070_main[model->unk68->unk00][model->unk68->unk60[model->unk0A].unk1D].objectIndex].fixedMtx);
            }
            func_80023404_main(hmf, mtx, scaleMtx);
            hmf->unk0C++;
            if (model->unk08 != 0xFF || hmf->unkB4 != NULL) {
                func_800303C8_main(model, model->motTime);
            }
            if (hmf->unk98 != NULL) {
                func_8002F60C_main(hmf);
            }
            if (hmf->unkC8 != NULL) {
                func_8001F154_main(model);
            }
        }
        func_8004D6E8_main(sample);
        bgDl = NULL;
        gfxStart = func_800250D4_main(D_800CD6A6_main, gfxStart, gfx);
        if (D_800D10F4_main->unkAC != NULL) {
            D_800D10F4_main->unkAC(D_800CD6A6_main);
        }
    }
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        model = &HmfModelData[i];
        if (model->hmf == NULL || (model->attr & HU3D_ATTR_DISPOFF)) {
            continue;
        }
        if (HmfPauseF && !(model->attr & HU3D_ATTR_NOPAUSE)) {
            continue;
        }
        if (model->motId == 0xFF) {
            continue;
        }
        func_8001F038_main(model, arg1);
        if (model->hmf->unk98 != NULL && model->unk00 == 0) {
            model->hmf->unk98->unk08 = model->motTime;
        }
    }
    if (!HmfPauseF) {
        HmfAnimExec(arg1);
    }
    gfxStart = func_8001BD24_main(gfxStart, 1, mask);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gfxStart = func_8001BD24_main(gfxStart, 3, 0);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    WipeExecAlways(&gMainGfxPos);
    gMainGfxPos = pfDrawFonts(gMainGfxPos);
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);
    func_8000EF64_main(gfxStart, D_800CE19A_main, 1, arg0, 0x309);
    D_800A08B0_main++;
}

Gfx *func_8001BD24_main(Gfx *arg0, s16 arg1, u16 arg2) {
    s16 i;

    for (i = 0; i < D_800CBB72_main[arg1]; i++) {
        HmfModel *temp_s0 = &HmfModelData[D_800D05A0_main[arg1][i]];

        if (!(temp_s0->cameraBit & arg2) && arg2 != 0) {
            continue;
        }
        D_800CD2F6_main = D_800D05A0_main[arg1][i];
        if (temp_s0->hmf->unk00 != D_800CE19A_main) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            func_8000EF64_main(arg0, D_800CE19A_main, 0, NULL, 0);
            D_800CE19A_main = temp_s0->hmf->unk00;
            arg0 = gMainGfxPos;
        }
        if (temp_s0->hookFunc != NULL) {
            temp_s0->hookFunc(&gMainGfxPos, (s32)D_800D0444_main, (s32)D_800D10F4_main);
        } else if (temp_s0->hmf->unk3C != NULL) {
            gSPDisplayList(gMainGfxPos++, temp_s0->hmf->unk3C);
        }
    }
    return arg0;
}

void Hu3DInit(void) {
    s16 i;

    HuMemSetDirty();
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        HmfModelData[i].hmf = NULL;
    }
    gCameraList = NULL;
    D_800C9932_main = 0;
    D_800D2008_main = 0;
    D_800D20EE_main = 0;
}

void func_8001BF90_main(u32 arg0, u32 arg1) {
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);
    gSPDisplayList(gMainGfxPos++, D_800A09B0_main);
    gDPSetDepthImage(gMainGfxPos++, arg1);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg1);
    gSPDisplayList(gMainGfxPos++, D_800A0A08_main);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg0);
    if (D_800CD280_main != 0) {
        gDPSetFillColor(gMainGfxPos++, PACK_FILL_COLOR(D_800A0540_main, D_800A0541_main, D_800A0542_main, 1));
        gSPDisplayList(gMainGfxPos++, D_800A0A38_main);
    }
}

void Hu3DModelPosSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].pos.x = x;
        HmfModelData[idx].pos.y = y;
        HmfModelData[idx].pos.z = z;
    }
}

void Hu3DModelPosGet(s16 idx, Vec *arg1) {
    arg1->x = HmfModelData[idx].pos.x;
    arg1->y = HmfModelData[idx].pos.y;
    arg1->z = HmfModelData[idx].pos.z;
}

void Hu3DModelRotSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].rot.x = x;
        HmfModelData[idx].rot.y = y;
        HmfModelData[idx].rot.z = z;
    }
}

void Hu3DModelScaleSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].scale.x = x;
        HmfModelData[idx].scale.y = y;
        HmfModelData[idx].scale.z = z;
    }
}

void func_8001C1F0_main(s16 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        func_8001C258_main(i, arg0, arg1);
    }
}

void func_8001C258_main(s16 idx, s32 arg1, s32 arg2) {
    HmfModel *model = &HmfModelData[idx];

    if (model->hmf != NULL) {
        if (arg1 & 0xB3F82) {
            arg2 |= HU3D_ATTR_REMAKESTATIC;
        }
        if (arg1 & HU3D_ATTR_LAYER_MASK) {
            Hu3DModelLayerSet(idx, arg2 & HU3D_ATTR_LAYER_MASK);
        }
        model->attr &= ~arg1;
        model->attr |= arg2;
    }
}

void func_8001C2FC_main(s16 idx, s32 arg1, s32 arg2) {
    HmfData *temp_a3 = HmfModelData[idx].hmf;
    s16 var_t0;

    for (var_t0 = 0; var_t0 < temp_a3->unk10; var_t0++) {
        temp_a3->unk60[var_t0].unk50 &= ~arg1;
        temp_a3->unk60[var_t0].unk50 |= arg2;
    }
}

void func_8001C39C_main(s16 idx, char *name, s32 arg2, s32 arg3) {
    HmfData *temp_s0 = HmfModelData[idx].hmf;
    s16 temp_v0 = func_8002C834_main(temp_s0, name);

    if (temp_v0 >= 0) {
        temp_s0->unk60[temp_v0].unk50 &= ~arg2;
        temp_s0->unk60[temp_v0].unk50 |= arg3;
    }
}

void Hu3DModelRemakeStatic(s16 arg0) {
    func_8001C258_main(arg0, HU3D_ATTR_REMAKESTATIC | HU3D_ATTR_STATIC, HU3D_ATTR_STATIC);
    D_800C9940_main = HmfModelData[arg0].attr;

    if (D_800C9940_main & HU3D_ATTR_DYNAMICFREE) {
        osSyncPrintf("RemakeStatic Error! Executed DynamicFree already!\n");
        D_800A0530_main = 0x10002;
        return;
    }

    if (func_80023264_main(HmfModelData[arg0].hmf) != NULL) {
        func_8001C954_main(arg0);
    }
}

void func_8001C514_main(s16 idx) {
    if (HmfModelData[idx].hmf->unk0A != 0) {
        func_80019C68_main(HmfModelData[idx].hmf->unk0E);
    } else {
        HuMemFreeAllWithTag(HmfModelData[idx].hmf->unk0E);
    }
    func_8001C258_main(idx, HU3D_ATTR_DYNAMICFREE, HU3D_ATTR_DYNAMICFREE);
}

void func_8001C5B4_main(s16 idx, s16 arg1) {
    HmfModel *model = &HmfModelData[idx];

    model->motId = HmfModelData[arg1].motId;
    model->motAttr = 0;
    model->unk48 = model->motTime = 0.0f;
    model->motSpeed = 1.0f;
    model->motIdShift = 0xFF;
}

void Hu3DMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfModel *temp_a0;

    temp_a0 = &HmfModelData[arg0];
    if (temp_a0->motIdShift != 0xFF) {
        temp_a0->motId = temp_a0->motIdShift;
        temp_a0->motTime = temp_a0->motShiftTime;
        temp_a0->motAttr = temp_a0->motShiftAttr;
        temp_a0->unk48 = temp_a0->unk54;
    }
    temp_a0->motIdShift = (u8)arg1;
    temp_a0->motShiftTime = arg2;
    temp_a0->unk0E = (u16)0;
    temp_a0->unk0C = arg3;
    temp_a0->motShiftAttr = (u8)arg4;
    temp_a0->unk54 = 0.0f;
}

void Hu3DMotionTimeSet(s16 arg0, f32 arg1) {
    HmfModel *model = &HmfModelData[arg0];

    if (D_800CCF58_main[model->motId].unk02 < arg1) {
        model->motTime = D_800CCF58_main[model->motId].unk02;
    } else {
        model->motTime = arg1;
    }
}

f32 Hu3DMotionShapeTimeGet(s16 arg0) {
    if (HmfModelData[arg0].motShapeTime < 0.0f) {
        return 0.0f;
    }
    return HmfModelData[arg0].motShapeTime;
}

f32 Hu3DMotionShapeMaxTimeGet(s16 arg0) {
    if (HmfModelData[arg0].motShapeTime < 0.0f) {
        return 0.0f;
    }
    return D_800CCF58_main[HmfModelData[arg0].motIdShape].unk02;
}

f32 Hu3DMotionShiftTimeGet(s16 idx) {
    if (HmfModelData[idx].motIdShift == 0xFF) {
        return -1.0f;
    }
    return HmfModelData[idx].motShiftTime;
}

void func_8001C814_main(s16 idx, s16 arg1, s16 arg2) {
    HmfModel *temp_a3 = &HmfModelData[idx];

    temp_a3->motAttr &= ~arg1;
    temp_a3->motAttr |= arg2;
    if (temp_a3->hmf->unk98 != NULL) {
        temp_a3->hmf->unk98->unk02 &= ~arg1;
        temp_a3->hmf->unk98->unk02 |= arg2;
    }
    if (temp_a3->motIdShift != 0xFF) {
        temp_a3->motShiftAttr &= ~arg1;
        temp_a3->motShiftAttr |= arg2;
    }
}

void Hu3DModelCameraSet(s16 idx, s16 arg1) {
    if (idx >= 0 && HmfModelData[idx].hmf != NULL) {
        HmfModelData[idx].cameraBit = arg1;
    }
}

void Hu3DModelLayerSet(s16 idx, u32 arg1) {
    HmfModelData[idx].attr &= ~HU3D_ATTR_LAYER_MASK;
    HmfModelData[idx].attr |= arg1;
    HmfModelData[idx].hmf->unk00 = (arg1 >> HU3D_ATTR_LAYER_SHIFT) & 7;
}

void Hu3DMotionSpeedSet(s16 idx, f32 arg1) {
    HmfModel *model = &HmfModelData[idx];
    model->motSpeed = arg1;
}

// officially named "DynamicFree"
void func_8001C954_main(s16 idx) {
    HmfData *hmf = HmfModelData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    s16 count;
    s16 i;
    s16 j;

    for (i = 0; i < D_800D1FF0_main; i++) {
        src = hmf->unk40;
        if (hmf->unk44[i] == src) {
            count = hmf->unk18;
            dst = hmf->unk44[i] = HuMemAllocTag(count * sizeof(Vtx), hmf->unk0E + 1);
            for (j = 0; j < count; j++) {
                dst->v = src->v;
                src++;
                dst++;
            }
        }
    }
}
void func_8001CAA4_main(s16 idx1, s16 idx2, f32 t) {
    HmfData *hmf = HmfModelData[idx1].hmf;
    Vtx_tn *src1 = (Vtx_tn *)hmf->unk40;
    Vtx_tn *src2 = (Vtx_tn *)HmfModelData[idx2].hmf->unk40;
    Vtx_tn *dst = (Vtx_tn *)hmf->unk44[D_800D2008_main];
    s16 count;
    s16 i;

    count = hmf->unk18;
    for (i = 0; i < count; i++) {
        *dst = *src1;
        if (src1->ob[0] != src2->ob[0] || src1->ob[1] != src2->ob[1] || src1->ob[2] != src2->ob[2]) {
            dst->ob[0] = src1->ob[0] * t + src2->ob[0] * (1.0f - t);
            dst->ob[1] = src1->ob[1] * t + src2->ob[1] * (1.0f - t);
            dst->ob[2] = src1->ob[2] * t + src2->ob[2] * (1.0f - t);
            dst->n[0] = src1->n[0] * t + src2->n[0] * (1.0f - t);
            dst->n[1] = src1->n[1] * t + src2->n[1] * (1.0f - t);
            dst->n[2] = src1->n[2] * t + src2->n[2] * (1.0f - t);
        }
        src1++;
        src2++;
        dst++;
    }
}
void func_8001CD34_main(s16 idx1, s16 idx2, f32 arg2, char *name, s32 arg4) {
    HmfData *hmf1 = HmfModelData[idx1].hmf;
    HmfData *hmf2 = HmfModelData[idx2].hmf;
    s16 node1 = func_8002C834_main(hmf1, name);
    s16 node2 = func_8002C834_main(hmf2, name);

    if (node1 == -1 || node2 == -1) {
        return;
    }
    func_8001CF1C_main(hmf1, hmf2, arg2, node1, node2, arg4);
}
void func_8001CE28_main(s16 idx1, s16 idx2, f32 arg2, char *name1, char *name2, s32 arg5) {
    HmfData *hmf1 = HmfModelData[idx1].hmf;
    HmfData *hmf2 = HmfModelData[idx2].hmf;
    s16 node1 = func_8002C834_main(hmf1, name1);
    s16 node2 = func_8002C834_main(hmf2, name2);

    if (node1 == -1 || node2 == -1) {
        return;
    }
    func_8001CF1C_main(hmf1, hmf2, arg2, node1, node2, arg5);
}
void func_8001CF1C_main(HmfData *hmf1, HmfData *hmf2, f32 t, s16 node1, s16 node2, s32 full) {
    Vtx_tn *src1;
    Vtx_tn *src2;
    Vtx_tn *dst;
    s16 start = 0;
    s16 count;
    s16 i;

    if (full) {
        src1 = (Vtx_tn *)hmf1->unk40;
        dst = (Vtx_tn *)hmf1->unk44[D_800D2008_main];
        start = hmf1->unk60[node1].unk28;
        for (i = 0; i < start; i++) {
            *dst = *src1;
            src1++;
            dst++;
        }
    }
    src1 = (Vtx_tn *)&hmf1->unk40[hmf1->unk60[node1].unk28];
    src2 = (Vtx_tn *)&hmf2->unk40[hmf2->unk60[node2].unk28];
    dst = (Vtx_tn *)&hmf1->unk44[D_800D2008_main][hmf1->unk60[node1].unk28];
    count = hmf1->unk60[node1].unk2A;
    for (i = 0; i < count; i++) {
        *dst = *src1;
        if (src1->ob[0] != src2->ob[0] || src1->ob[1] != src2->ob[1] || src1->ob[2] != src2->ob[2]) {
            dst->ob[0] = src1->ob[0] * t + src2->ob[0] * (1.0f - t);
            dst->ob[1] = src1->ob[1] * t + src2->ob[1] * (1.0f - t);
            dst->ob[2] = src1->ob[2] * t + src2->ob[2] * (1.0f - t);
            dst->n[0] = src1->n[0] * t + src2->n[0] * (1.0f - t);
            dst->n[1] = src1->n[1] * t + src2->n[1] * (1.0f - t);
            dst->n[2] = src1->n[2] * t + src2->n[2] * (1.0f - t);
        }
        src1++;
        src2++;
        dst++;
    }
    if (full) {
        start += count;
        count = hmf1->unk18;
        for (i = start; i < count; i++) {
            *dst = *src1;
            src1++;
            dst++;
        }
    }
}
void func_8001D330_main(s16 arg0) {
    D_800A0A78_main = arg0;
}

void *func_8001D33C_main(s16 idx, char *name) {
    HmfData *hmf = HmfModelData[idx].hmf;
    s16 node = func_8002C834_main(hmf, name);
    s16 count;
    s16 i;
    s16 j;

    if (hmf->unk80 != (HmfMotionNode *)-1) {
        for (i = 0; i < hmf->unk16; i++) {
            count = hmf->unk80[i].unk00;
            for (j = 0; j < count; j++) {
                if (hmf->unk80[i].unk50[j] == node) {
                    break;
                }
            }
            if (j != count) {
                break;
            }
        }
        if (i == hmf->unk16) {
            return (void *)-1;
        }
        return &hmf->unk80[i];
    } else {
        for (i = 0; i < hmf->unk64; i++) {
            if (hmf->unk68[i].unk00 == node) {
                break;
            }
        }
        if (i == hmf->unk64) {
            return (void *)-1;
        }
        return &hmf->unk68[i];
    }
}
void func_8001D558_main(s16 idx, f32 arg1, f32 arg2, s32 mode) {
    HmfData *hmf = HmfModelData[idx].hmf;

    if (hmf != NULL) {
        switch (mode & 0xF) {
            case 0:
                func_8001D874_main(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
            case 1:
                func_8001DACC_main(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
            case 2:
                func_8001DDB8_main(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
        }
    }
}
void func_8001D638_main(s16 idx, f32 arg1, f32 arg2, char *name, s16 mode) {
    HmfData *hmf = HmfModelData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    node = func_8002C834_main(hmf, name);
    if (node == -1) {
        return;
    }
    if (mode & 0x80) {
        src = hmf->unk40;
        dst = hmf->unk44[D_800D2008_main];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = src->v;
            src++;
            dst++;
        }
    }
    switch (mode & 0xF) {
        case 0:
            func_8001D874_main(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
        case 1:
            func_8001DACC_main(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
        case 2:
            func_8001DDB8_main(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
    }
}
void func_8001D874_main(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 n;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++, group++) {
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale;
        sy = cy * scale;
        sz = cz * scale;
        n = group->count & 0x7F;
        indices = group->indices;
        for (j = 0; j < n; j++, indices++) {
            src = &hmf->unk40[*indices];
            dst = &hmf->unk44[D_800D2008_main][*indices];
            dst->v.ob[0] = (src->v.ob[0] - cx) * inv + sx;
            dst->v.ob[1] = (src->v.ob[1] - cy) * inv + sy;
            dst->v.ob[2] = (src->v.ob[2] - cz) * inv + sz;
        }
    }
}
void func_8001DACC_main(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    f32 jitter[8] = { 0.0f, -0.1f, 0.5f, 0.8f, -0.2f, 0.1f, 0.3f, -0.3f };
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 n;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++, group++) {
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale + cx * (1.0f - scale) * jitter[i & 7];
        sy = cy * scale + cy * (1.0f - scale) * jitter[i & 7];
        sz = cz * scale + cz * (1.0f - scale) * jitter[i & 7];
        n = group->count & 0x7F;
        indices = group->indices;
        for (j = 0; j < n; j++, indices++) {
            src = &hmf->unk40[*indices];
            dst = &hmf->unk44[D_800D2008_main][*indices];
            dst->v.ob[0] = (src->v.ob[0] - cx) * inv + sx;
            dst->v.ob[1] = (src->v.ob[1] - cy) * inv + sy;
            dst->v.ob[2] = (src->v.ob[2] - cz) * inv + sz;
        }
    }
}

void func_8001DDB8_main(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    f32 sinTbl[4];
    f32 cosTbl[4];
    f32 jitter[8] = { 0.0f, -0.1f, 0.5f, 0.8f, -0.2f, 0.1f, 0.3f, -0.3f };
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    f32 s;
    f32 c;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 nx;
    s16 ny;
    s16 nz;
    s16 n;
    s16 i;
    s16 j;

    sinTbl[0] = sindf(D_800A0A7C_main);
    cosTbl[0] = cosdf(D_800A0A7C_main);
    sinTbl[1] = sindf(-D_800A0A7C_main / 2.0f);
    cosTbl[1] = cosdf(-D_800A0A7C_main / 2.0f);
    sinTbl[2] = sindf(D_800A0A7C_main / 2.0f);
    cosTbl[2] = cosdf(D_800A0A7C_main / 2.0f);
    sinTbl[3] = sindf(-D_800A0A7C_main);
    cosTbl[3] = cosdf(-D_800A0A7C_main);
    for (i = 0; i < count; i++, group++) {
        s = sinTbl[i & 3];
        c = cosTbl[i & 3];
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale + cx * (1.0f - scale) * jitter[i & 7];
        sy = cy * scale + cy * (1.0f - scale) * jitter[i & 7];
        sz = cz * scale + cz * (1.0f - scale) * jitter[i & 7];
        n = group->count & 0x7F;
        indices = group->indices;
        nx = group->normal[0];
        if (nx < 0) {
            nx = -nx;
        }
        ny = group->normal[1];
        if (ny < 0) {
            ny = -ny;
        }
        nz = group->normal[2];
        if (nz < 0) {
            nz = -nz;
        }
        if (nx > ny && nx > nz) {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[D_800D2008_main][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = (dx * c + dy * s) * inv + sx;
                dst->v.ob[1] = (-dx * s + dy * c) * inv + sy;
                dst->v.ob[2] = dz * inv + sz;
            }
        } else if (ny > nz) {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[D_800D2008_main][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = dx * inv + sx;
                dst->v.ob[1] = (dy * c + dz * s) * inv + sy;
                dst->v.ob[2] = (-dy * s + dz * c) * inv + sz;
            }
        } else {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[D_800D2008_main][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = (dx * c - dz * s) * inv + sx;
                dst->v.ob[1] = dy * inv + sy;
                dst->v.ob[2] = (dx * s + dz * c) * inv + sz;
            }
        }
    }
}
void func_8001E500_main(s16 idx, char *oldName, char *newName) {
    HmfData_Unk84_Entry2 *found = NULL;
    HmfData *hmf = HmfModelData[idx].hmf;
    u16 hash;
    s16 i;

    hash = func_80011460_main((u8 *)newName);
    for (i = 0; i < 128; i++) {
        if (D_800D1FCC_main[i].nameHash != 0 && D_800D1FCC_main[i].nameHash == hash &&
            strcmp(D_800D1FCC_main[i].name, newName) == 0) {
            found = &D_800D1FCC_main[i];
            break;
        }
    }
    hash = func_80011460_main((u8 *)oldName);
    for (i = 0; i < hmf->unk12; i++) {
        if (hmf->unk84[i].unkC->nameHash == hash) {
            hmf->unk84[i].unkC = found;
        }
    }
}
void func_8001E65C_main(s16 idx, f32 x, f32 y, s32 width, s32 height) {
    HmfData *hmf = HmfModelData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    u16 w;
    u16 h;
    u16 s;
    u16 t;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    src = hmf->unk40;
    dst = hmf->unk44[D_800D2008_main];
    count = hmf->unk18;
    w = width * 32;
    h = height * 32;
    s = x * 32.0f;
    t = y * 32.0f;
    if (x < 0.0f) {
        x = -x;
    }
    if (y < 0.0f) {
        y = -y;
    }
    if (x * 32.0f > w) {
        s %= w;
    }
    if (y * 32.0f > h) {
        t %= h;
    }
    for (i = 0; i < count; i++) {
        dst->v.tc[0] = src->v.tc[0] + s;
        dst->v.tc[1] = src->v.tc[1] + t;
        src++;
        dst++;
    }
}
void func_8001E888_main(s16 idx, f32 x, f32 y, u16 width, u16 height, char *name, u8 reset) {
    HmfData *hmf = HmfModelData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    u16 s;
    u16 t;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    if (reset) {
        src = hmf->unk40;
        dst = hmf->unk44[D_800D2008_main];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = src->v;
            src++;
            dst++;
        }
    }
    node = func_8002C834_main(hmf, name);
    count = hmf->unk60[node].unk2A;
    src = &hmf->unk40[hmf->unk60[node].unk28];
    dst = &hmf->unk44[D_800D2008_main][hmf->unk60[node].unk28];
    width <<= 5;
    height <<= 5;
    s = x * 32.0f;
    t = y * 32.0f;
    if (x < 0.0f) {
        x = -x;
    }
    if (y < 0.0f) {
        y = -y;
    }
    if (x * 32.0f > width) {
        s %= width;
    }
    if (y * 32.0f > height) {
        t %= height;
    }
    for (i = 0; i < count; i++) {
        dst->v.tc[0] = src->v.tc[0] + s;
        dst->v.tc[1] = src->v.tc[1] + t;
        src++;
        dst++;
    }
}
void func_8001EBC0_main(s16 idx, char *name, u8 r, u8 g, u8 b, u8 reset) {
    HmfData *hmf = HmfModelData[idx].hmf;
    Vtx *vtx;
    Vtx *dst;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    if (reset) {
        vtx = hmf->unk40;
        dst = hmf->unk44[D_800D2008_main];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = vtx->v;
            vtx++;
            dst++;
        }
    }
    node = func_8002C834_main(hmf, name);
    count = hmf->unk60[node].unk2A;
    vtx = &hmf->unk44[D_800D2008_main][hmf->unk60[node].unk28];
    for (i = 0; i < count; i++) {
        vtx->v.cn[0] = r;
        vtx->v.cn[1] = g;
        vtx->v.cn[2] = b;
        vtx++;
    }
}
void func_8001ED54_main(s16 idx) {
    HmfData *hmf = HmfModelData[idx].hmf;
    HmfModelData_Unk64_Unk60_Struct *obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    s16 i;
    s16 j;
    s16 k;
    s16 n;
    s16 tmp;
    f32 ftmp;

    for (i = 0; i < hmf->unk10; i++) {
        obj = &hmf->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            face = &obj->unk54[j];
            n = face->unk00 & 0x7F;
            for (k = 0; k < n / 2; k++) {
                tmp = face->unk04[k];
                face->unk04[k] = face->unk04[n - k - 1];
                face->unk04[n - k - 1] = tmp;
                ftmp = face->unk0C[k];
                face->unk0C[k] = face->unk0C[n - k - 1];
                face->unk0C[n - k - 1] = ftmp;
                ftmp = face->unk1C[k];
                face->unk1C[k] = face->unk1C[n - k - 1];
                face->unk1C[n - k - 1] = ftmp;
            }
        }
    }
}
void Hu3DMotionShapeSet(s16 idx, s16 arg1, s16 arg2) {
    HmfModel *model = &HmfModelData[idx];
    f32 zero;

    model->motIdShape = arg1;
    zero = 0.0f;
    model->motShapeTime = zero;
    model->unk60 = zero;
    model->motShapeAttr = arg2;
    model->motShapeSpeed = 1.0f;
}

void Hu3DFogSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    D_800CE1C6_main = 1;
    D_800D6B64_main = arg0;
    D_800CC0B6_main = arg1;
    D_800D0599_main = arg2;
    D_800D41C4_main = arg3;
    D_800CDA84_main = arg4;
}

void Hu3DFogClear(void) {
    D_800CE1C6_main = 0;
}

void Hu3DModelHookSet(s16 idx, s16 parentIdx, char *name) {
    HmfData *hmf = HmfModelData[parentIdx].hmf;
    s16 node = func_8002C834_main(hmf, name);

    HmfModelData[idx].unk68 = hmf;
    HmfModelData[idx].unk0A = node;
}

void func_8001EFEC_main(s16 idx, char *name) {
    HmfData *hmf = HmfModelData[idx].hmf;

    hmf->unk9C = func_80031A44_main(hmf, name);
}

void func_8001F038_main(HmfModel *model, u16 speed) {
    model->motTime = func_8002FC7C_main((HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motId], model->motAttr,
                                      model->motTime, model->unk48, speed * model->motSpeed);
    if (model->motIdShift != 0xFF) {
        model->motShiftTime = func_8002FC7C_main((HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motIdShift],
                                          model->motShiftAttr, model->motShiftTime, model->unk54, speed * model->motShiftSpeed);
    }
    if (model->motIdShape != 0xFF) {
        model->motShapeTime = func_8002FC7C_main((HmfModelData_Unk64_Unk8C_Struct *)&D_800CCF58_main[model->motIdShape],
                                          model->motShapeAttr, model->motShapeTime, model->unk60, speed * model->motShapeSpeed);
    }
}
void func_8001F154_main(HmfModel *model) {
    HmfData *hmf = model->hmf;
    s16 frame = model->motTime;
    s16 i;

    for (i = 0; i < hmf->unk2A; i++) {
        func_80032FC0_main(hmf->unkC8[i], 1, 1);
        func_80034048_main(hmf->unkC8[i], frame);
    }
}

s32 func_8001F1FC_main(void *arg0, s32 arg1) {
    u8 *data = arg0;
    s16 ret;

    if (data[0] != 'M' || data[1] != 'T' || data[2] != 'N' || data[3] != 'X') {
        D_800D5204_main = 0x2810;
        D_800CDD6A_main = 0x2811;
        D_800CB8C0_main.unk0E = 0x2810;
        Hmfload(&D_800CB8C0_main, data, (s16)arg1);
        ret = func_8002D2D8_main(data, &D_800CB8C0_main);
        HuMemFreeAllWithTag(D_800D5204_main);
        HuMemFreeAllWithTag(D_800CDD6A_main);
    } else {
        ret = func_8002D3AC_main(data);
    }
    if (arg1 & 8) {
        gFreeFunc(data);
    }
    return ret;
}

void Hu3DMotionSet(s16 arg0, s16 arg1) {
    HmfModel *temp_v0;

    temp_v0 = &HmfModelData[arg0];
    temp_v0->motId = arg1;
    temp_v0->motAttr = 0;
    temp_v0->unk48 =
        temp_v0->motTime = 0.0f;
    temp_v0->motSpeed = 1.0f;
    temp_v0->motIdShift = 0xFF;
}

f32 Hu3DMotionMotionMaxTimeGet(s16 arg0) {
    return D_800CCF58_main[arg0].unk02;
}

void Hu3DBGColorSet(s32 r, s32 g, s32 b) {
    D_800A0540_main = r;
    D_800A0541_main = g;
    D_800A0542_main = b;
}

void func_8001F3A8_main(s16 idx, s16 flags, s16 clear, s16 set) {
    HmfModel *model = &HmfModelData[idx];

    if (flags & 1) {
        if (model->motId != 0xFF) {
            model->motAttr &= ~clear;
            model->motAttr |= set;
            if (flags & 2) {
                if (model->motIdShift != 0xFF) {
                    model->motShiftAttr &= ~clear;
                    model->motShiftAttr |= set;
                }
            }
            if (flags & 4) {
                if (model->motIdShape != 0xFF) {
                    model->motShapeAttr &= ~clear;
                    model->motShapeAttr |= set;
                }
            }
        }
    }
}

void func_8001F450_main(s16 arg0, s16 arg1, f32 arg2) {
    HmfModel *model;

    model = &HmfModelData[arg0];
    model->unk09 = arg1;
    model->unk6C = model->hmf;
    model->unk14 = arg2;
    model = &HmfModelData[arg1];
    model->unk09 = arg0;
    model->unk6C = NULL;
    model->unk14 = 0.0f;
    model->attr |= HU3D_ATTR_DISPOFF;
}

void func_8001F4BC_main(s16 idx) {
    HmfModel *model = &HmfModelData[idx];
    HmfData *hmf;
    f32 dx = D_800D10F4_main->pos.x - model->pos.x;
    f32 dy = D_800D10F4_main->pos.y - model->pos.y;
    f32 dz = D_800D10F4_main->pos.z - model->pos.z;
    s16 i;

    if (model->unk14 < HuSqrtf(dx * dx + dy * dy + dz * dz)) {
        hmf = model->unk6C;
    } else {
        hmf = HmfModelData[model->unk09].hmf;
    }
    if (hmf != model->hmf) {
        model->hmf = hmf;
        for (i = 0; i < HU3D_MODEL_MAX; i++) {
            if (HmfModelData[i].hmf != NULL || (HmfModelData[i].attr & HU3D_ATTR_DISPOFF)) {
                continue;
            }
            if ((HmfModelData[i].attr & 0x4000) &&
                (model->hmf == HmfModelData[i].unk68 || HmfModelData[model->unk09].hmf == HmfModelData[i].unk68)) {
                HmfModelData[i].unk68 = hmf;
            }
        }
    }
    HmfModelData[model->unk09].attr |= HU3D_ATTR_DISPOFF;
}
s32 func_8001F668_main(s16 arg0) {
    HmfModel *model = &HmfModelData[arg0];

    return model->hmf == HmfModelData[model->unk09].hmf;
}

void func_8001F6B0_main(s8 arg0) {
    D_800CC0A8_main = arg0;
}

void func_8001F6BC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfData *hmf;

    hmf = HmfModelData[arg0].hmf;
    hmf->unk02[0] = arg1;
    hmf->unk02[1] = arg2;
    hmf->unk02[2] = arg3;
    hmf->unk02[3] = arg4;
}

void func_8001F6F8_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfData *hmf;

    hmf = HmfModelData[arg0].hmf;
    hmf->unk02[4] = arg1;
    hmf->unk02[5] = arg2;
    hmf->unk02[6] = arg3;
    hmf->unk02[7] = arg4;
}

void func_8001F734_main(s16 idx, u8 r, u8 g, u8 b, u8 a) {
    func_8001F6BC_main(idx, r, g, b, a);
    func_8001F6F8_main(idx, r * 0.5f, g * 0.5f, b * 0.5f, a * 0.5f);
}
void Hu3DLayerHookSet(s16 idx, void *func) {
    D_800CC3D8_main[idx] = func;
}

void func_8001F974_main(s16 arg0, s16 arg1) {
    func_8001C5B4_main(arg0, arg1);
    HmfModelData[arg0].unk08 = HmfModelData[arg1].unk08;
}

void func_8001F9E4_main(s16 arg0, u8 arg1) {
    HmfData *hmf = HmfModelData[arg0].hmf;
    s16 i;

    for (i = 0; i < hmf->unk10; i++) {
        hmf->unk60[i].unk20 = arg1;
    }
}

void func_8001FA68_main(s16 idx) {
    HmfData *hmf = HmfModelData[idx].hmf;
    s16 i;

    func_8001C2FC_main(idx, 0x110000, 0x110000);
    for (i = 0; i < hmf->unk1E; i++) {
        hmf->unk88[i].unk0A = 0xFF;
        hmf->unk88[i].unk09 |= 5;
    }
    Hu3DModelRemakeStatic(idx);
}

void Hu3DLLightCreate(s16 arg0, s8 arg1) {
    HmfModel *model = &HmfModelData[arg0];
    HmfData_UnkD0 *light;

    if (model->unkB4 == NULL) {
        light = HuMemAllocTag(sizeof(HmfData_UnkD0), D_800CDD6A_main);
        model->unkB4 = light;
        light->unk03 = arg1;
        light->unk02 = 0x40;
        light->unk01 = 0x40;
        light->unk00 = 0x40;
        light->unk06 = 0x64;
        light->unk05 = 0x64;
        light->unk04 = 0x64;
    }
}

void Hu3DLLightColorSet(s16 arg0, s8 arg1, s8 arg2, s8 arg3) {
    HmfData_UnkD0 *light;

    light = HmfModelData[arg0].unkB4;
    if (light != NULL) {
        light->unk00 = arg1;
        light->unk01 = arg2;
        light->unk02 = arg3;
    }
}

void Hu3DLLightInfinitytSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    HmfData_UnkD0 *light;
    f32 len;

    if (HmfModelData[arg0].unkB4 != NULL) {
        light = HmfModelData[arg0].unkB4;
        len = HuSqrtf(arg1 * arg1 + arg2 * arg2 + arg3 * arg3);
        if (len != 0.0f) {
            light->unk04 = (s8)((arg1 / len) * 120.0f);
            light->unk05 = (s8)((arg2 / len) * 120.0f);
            light->unk06 = (s8)((arg3 / len) * 120.0f);
        } else {
            light->unk04 = 0;
            light->unk05 = 120;
            light->unk06 = 0;
        }
    }
}

void func_8001FD08_main(s16 idx) {
    HmfData *hmf = HmfModelData[idx].hmf;
    HmfModelData_Unk64_Unk60_Struct *obj;
    s16 i;
    s16 j;

    for (i = 0; i < hmf->unk10; i++) {
        obj = &hmf->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            obj->unk54[j].unk00 |= 0x80;
        }
    }
}

void func_8001FDE8_main(s16 arg0) {
    HmfModelData[arg0].motId = 0xFF;
}
