#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "include_asm.h"
#include "variables.h"
#include "game/data.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "gcc/string.h"
#include "game/board.h"
#include "game/hmfload.h"
#include "game/hmfdraw.h"

#define HMFSPR_CC_PRIM_MODULATEA 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0
#define HMFSPR_CC_MODULATEA_PRIM TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0

extern u16 D_800CDD4E_main;
extern s16 D_800CD1B0_main;
extern s16 *D_800D04B4_main;
extern HuMtx4F *D_800D1358_main;
extern s16 D_800D138A_main;
extern HuMtx4F D_800D5A00_main[];
extern Vtx *D_800CC080_main[8];
extern Vtx *D_800CDD54_main;
extern u8 D_800D2008_main;
extern Gfx *D_800D1F30_main;
extern s16 D_800D4090_main[6][3][7];
extern u8 D_800D6A50_main[6];

u8 D_800A0620_main = 0;
s16 D_800A0624_main[] = { G_TF_POINT, G_TF_AVERAGE, G_TF_BILERP, G_TF_POINT };
s16 D_800A062C_main[] = { 2, 3, 7, 4, 5, 6, 8, 9 }; // unreferenced

/* hmfanim functions. This file does not include game/hmfanim.h: it was compiled
 * against an s16 return type for func_800329B4_main, which is declared s32 there. */
s32 HmfAnimCreate(HmfData *hmf, void *data, s16 bank, char *name);
s16 HmfAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, char *name);
s16 func_800329B4_main(u8 *data);
void func_80032FC0_main(s16 animIdx, u8 bitmask, u8 flags);
void func_80033354_main(s16 animIdx);
void func_800333B0_main(s16 animIdx);
void func_80033910_main(HmfData *hmf);
void func_80033970_main(HmfData *hmf);


void func_800142A0_main(s32 count) {
    s16 i;

    D_800CDD4E_main = count;
    for (i = 0; i < D_800D1FF0_main; i++) {
        D_800CC080_main[i] = HuMemAllocTag((s16)count * 128, TAG_MODELENTRY);
        D_800D1360[i] = HuMemAllocTag((s16)count * 256, TAG_MODELENTRY);
    }
    D_800CBB60_main = HuMemAllocTag((s16)count * sizeof(HmfModelEntry), TAG_MODELENTRY);
    for (i = 0; i < (s16)count; i++) {
        D_800CBB60_main[i].modelId = -1;
    }
    D_800A0620_main = 1;
    func_800143F0_main();
}

void func_800143F0_main(void) {
    if (D_800A0620_main) {
        s32 playerIdx = D_800D2008_main;

        D_800CDD54_main = D_800CC080_main[playerIdx];
        D_800D1F30_main = D_800D1360[playerIdx];
    }
}

u16 HmfSprModelCreate(void *data, u32 flags, u16 attr) {
    s16 i;
    s16 id;

    for (i = 0; i < D_800CDD4E_main; i++) {
        if (D_800CBB60_main[i].modelId == -1) {
            break;
        }
    }
    if (i == D_800CDD4E_main) {
        return -1;
    }
    id = func_8001A894_main(flags, NULL, 4);
    if (id == -1) {
        return -1;
    }
    D_800CBB60_main[i].modelId = id;
    if (data != (void *)-1) {
        id = func_800329B4_main(data);
        D_800D408C_main[id].refCount = 1;
        if (id == -1) {
            Hu3DModelKill(D_800CBB60_main[i].modelId);
            D_800CBB60_main[i].modelId = -1;
        }
    } else {
        id = -1;
    }
    D_800CBB60_main[i].unk_02 = id;
    D_800CBB60_main[i].flags = attr;
    D_800CBB60_main[i].unk_12 = D_800CBB60_main[i].colorR = D_800CBB60_main[i].colorG = D_800CBB60_main[i].colorB = 0xFF;
    D_800CBB60_main[i].unk_0A = 0;
    D_800CBB60_main[i].unk_08 = 0;
    D_800CBB60_main[i].nodeIdx = 0;
    D_800CBB60_main[i].pointIdx = 0;
    D_800CBB60_main[i].unk_20 = NULL;
    return i;
}

u16 func_80014618_main(s16 idx, u16 attr) {
    s16 newIdx = HmfSprModelCreate((void *)-1, HmfModelData[D_800CBB60_main[idx].modelId].attr, attr);

    D_800D408C_main[D_800CBB60_main[newIdx].unk_02 = D_800CBB60_main[idx].unk_02].refCount++;
    return newIdx;
}

void func_800146DC_main(s16 arg0, u16 arg1, u16 arg2) {
    HmfModelEntry *entry = &D_800CBB60_main[arg0];
    entry->flags = (entry->flags & ~arg1) | arg2;
}

void func_80014714_main(s16 arg0, u16 arg1) {
    D_800CBB60_main[arg0].nodeIdx = arg1;
}

void func_8001473C_main(s16 arg0, s16 arg1) {
    D_800CBB60_main[arg0].pointIdx = arg1;
    D_800CBB60_main[arg0].nodeIdx = 0;
    D_800CBB60_main[arg0].unk_08 = 0;
}

u16 func_8001476C_main(s16 arg0) {
    return D_800CBB60_main[arg0].nodeIdx;
}

void func_80014794_main(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        s32 visible;

        D_800CBB60_main[arg0].unk_12 = arg1;
        visible = (u8)arg1 != 0xFF ? 0x10000 : 0;
        func_8001C2FC_main(D_800CBB60_main[arg0].modelId, 0x10000, visible);
    }
}

void func_800147FC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    if (arg0 != -1) {
        D_800CBB60_main[arg0].colorR = arg1;
        D_800CBB60_main[arg0].colorG = arg2;
        D_800CBB60_main[arg0].colorB = arg3;
    }
}

void func_80014850_main(s16 arg0) {
    HmfModelEntry *entry = &D_800CBB60_main[arg0];

    entry->unk_0A = 0;
    entry->nodeIdx = 0;
    entry->flags &= 0xFF7F;
    func_8001C258_main(entry->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_800148A8_main(s16 idx, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1) {
    if (idx != -1) {
        func_800146DC_main(idx, 0x40, 0x40);
        D_800CBB60_main[idx].colorStart[0] = r0;
        D_800CBB60_main[idx].colorStart[1] = g0;
        D_800CBB60_main[idx].colorStart[2] = b0;
        D_800CBB60_main[idx].colorStart[3] = a0;
        D_800CBB60_main[idx].colorEnd[0] = r1;
        D_800CBB60_main[idx].colorEnd[1] = g1;
        D_800CBB60_main[idx].colorEnd[2] = b1;
        D_800CBB60_main[idx].colorEnd[3] = a1;
    }
}

void func_800149D0_main(s16 arg0, HmfColorKey *arg1) {
    if (arg0 != -1) {
        func_800146DC_main(arg0, 0x40, 0x40);
        D_800CBB60_main[arg0].unk_20 = arg1;
        D_800CBB60_main[arg0].unk_0E = 0;
        D_800CBB60_main[arg0].unk_0C = 0;
    }
}

void func_80014A3C_main(s32 frames) {
    s16 i;
    s16 j;
    HmfModelEntry *entry;
    HmfData *hmf;
    HmfAnimSet *animSet;
    HmfAnimRot *rot;
    HmfAnimImage *image;
    s16 width;
    s16 height;
    s16 x0;
    s16 y0;
    s16 negHeight;
    HmfColorKey *key;
    HmfColorKey *prev;
    s16 end;
    s16 elapsed;
    s16 span;
    f32 t;

    if (!D_800A0620_main) {
        return;
    }
    for (i = 0; i < D_800CDD4E_main; i++) {
        if (D_800CBB60_main[i].modelId == -1) {
            continue;
        }
        entry = &D_800CBB60_main[i];
        if ((HmfModelData[entry->modelId].attr & 4) || (u16)entry->unk_02 == 0xFFFF) {
            continue;
        }
        if (entry->flags & 0x80) {
            func_8001C258_main(entry->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            entry->flags &= 0xFF7F;
            continue;
        }
        hmf = HmfModelData[entry->modelId].hmf;
        *hmf->unk3C->unk00 = D_800D1F30_main;
        animSet = &D_800D408C_main[(u16)entry->unk_02];
        rot = &animSet->rot[entry->pointIdx];
        gDPSetCycleType(D_800D1F30_main++, G_CYC_1CYCLE);
        if (entry->flags & 0x40) {
            if (entry->unk_20 != NULL) {
                key = entry->unk_20;
                for (; key->time != 0xFF; key++) {
                    if (entry->unk_0A < key->time) {
                        break;
                    }
                }
                if (key->time == 0xFF) {
                    end = rot->totalFrames;
                } else {
                    end = key->time;
                }
                prev = key - 1;
                elapsed = entry->unk_0A - prev->time;
                span = end - prev->time;
                t = (f32)elapsed / (f32)span;
                entry->colorR = prev->color[0] + (key->color[0] - prev->color[0]) * t;
                entry->colorG = prev->color[1] + (key->color[1] - prev->color[1]) * t;
                entry->colorB = prev->color[2] + (key->color[2] - prev->color[2]) * t;
                entry->unk_12 = prev->color[3] + (key->color[3] - prev->color[3]) * t;
            } else {
                t = (f32)entry->unk_0A / (f32)rot->totalFrames;
                entry->colorR = entry->colorStart[0] + (entry->colorEnd[0] - entry->colorStart[0]) * t;
                entry->colorG = entry->colorStart[1] + (entry->colorEnd[1] - entry->colorStart[1]) * t;
                entry->colorB = entry->colorStart[2] + (entry->colorEnd[2] - entry->colorStart[2]) * t;
                entry->unk_12 = entry->colorStart[3] + (entry->colorEnd[3] - entry->colorStart[3]) * t;
            }
        }
        if (animSet->rotCount == 0) {
            if (animSet->interp & 0x8000) {
                gDPSetCombineMode(D_800D1F30_main++, HMFSPR_CC_PRIM_MODULATEA, HMFSPR_CC_PRIM_MODULATEA);
            } else {
                gDPSetCombineMode(D_800D1F30_main++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            }
            hmf->unk60->unk50 |= 0x10000;
            if (entry->flags & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gDPSetAlphaCompare(D_800D1F30_main++, G_AC_THRESHOLD);
            gDPSetBlendColor(D_800D1F30_main++, 0, 0, 0, 1);
            gDPSetPrimColor(D_800D1F30_main++, 0, 0, entry->colorR, entry->colorG, entry->colorB, entry->unk_12);
        } else if (entry->unk_12 == 0xFF) {
            if (entry->flags & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
            }
            gDPSetCombineMode(D_800D1F30_main++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        } else {
            hmf->unk60->unk50 |= 0x10000;
            gDPSetAlphaCompare(D_800D1F30_main++, G_AC_THRESHOLD);
            gDPSetBlendColor(D_800D1F30_main++, 0, 0, 0, 1);
            gDPSetPrimColor(D_800D1F30_main++, 0, 0, 0, 0, 0, entry->unk_12);
            if (entry->flags & 0x100) {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            } else {
                gDPSetRenderMode(D_800D1F30_main++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gDPSetCombineMode(D_800D1F30_main++, HMFSPR_CC_MODULATEA_PRIM, HMFSPR_CC_MODULATEA_PRIM);
        }
        gDPSetTextureFilter(D_800D1F30_main++, D_800A0624_main[(entry->flags & 0x18) >> 3]);
        gSPClearGeometryMode(D_800D1F30_main++, G_CULL_BACK | G_LIGHTING);
        gSPSetGeometryMode(D_800D1F30_main++, G_ZBUFFER);
        image = &animSet->unk0C[rot->frames[entry->nodeIdx].unk00];
        width = image->width;
        height = image->height;
        if (animSet->rotCount == 0) {
            gDPSetTextureLUT(D_800D1F30_main++, G_TT_NONE);
            if (animSet->interp & 0x8000) {
                gDPLoadTextureBlock_4b(D_800D1F30_main++, image->data, G_IM_FMT_I, width, height, 0,
                                       G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                       HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureBlock(D_800D1F30_main++, image->data, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                    HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            }
        } else {
            gDPSetTextureLUT(D_800D1F30_main++, G_TT_RGBA16);
            if (animSet->rotCount <= 16) {
                gDPLoadTLUT_pal16(D_800D1F30_main++, 0, animSet->unk14);
                gDPLoadTextureBlock_4b(D_800D1F30_main++, image->data, G_IM_FMT_CI, width, height, 0,
                                       G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                       HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTLUT_pal256(D_800D1F30_main++, animSet->unk14);
                gDPLoadTextureBlock(D_800D1F30_main++, image->data, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                    HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPVertex(D_800D1F30_main++, osVirtualToPhysical(D_800CDD54_main), 4, 0);
        gSP1Quadrangle(D_800D1F30_main++, 0, 1, 2, 3, 0);

        negHeight = -height;
        x0 = -image->unk04;
        y0 = image->unk06;
        D_800CDD54_main->n.ob[0] = x0;
        D_800CDD54_main->n.ob[1] = y0;
        D_800CDD54_main->n.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->n.tc[0] = 0;
        D_800CDD54_main->n.tc[1] = 0;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;

        D_800CDD54_main->n.ob[0] = x0;
        D_800CDD54_main->n.ob[1] = negHeight + y0;
        D_800CDD54_main->n.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->n.tc[0] = 0;
        D_800CDD54_main->n.tc[1] = (-negHeight - 1) << 5;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;

        D_800CDD54_main->n.ob[0] = width + x0;
        D_800CDD54_main->n.ob[1] = negHeight + y0;
        D_800CDD54_main->n.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->n.tc[0] = (width - 1) << 5;
        D_800CDD54_main->n.tc[1] = (-negHeight - 1) << 5;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;

        D_800CDD54_main->n.ob[0] = width + x0;
        D_800CDD54_main->n.ob[1] = y0;
        D_800CDD54_main->n.ob[2] = 0;
        D_800CDD54_main->n.n[0] = D_800CDD54_main->n.n[1] = D_800CDD54_main->n.n[2] = -1;
        D_800CDD54_main->n.tc[0] = (width - 1) << 5;
        D_800CDD54_main->n.tc[1] = 0;
        D_800CDD54_main->n.a = 0xFF;
        D_800CDD54_main++;

        gSPEndDisplayList(D_800D1F30_main++);

        if (!(entry->flags & 1) && (HmfPauseF == 0 || (HmfModelData[entry->modelId].attr & 0x8000))) {
            for (j = 0; j < frames; j++) {
                entry->unk_08++;
                entry->unk_0A++;
                if (entry->unk_08 >= rot->frames[entry->nodeIdx].time) {
                    entry->nodeIdx++;
                    entry->unk_08 = 0;
                    if (rot->frameCount <= entry->nodeIdx) {
                        if (entry->flags & 4) {
                            entry->flags |= 0x80;
                        }
                        if ((entry->flags & 2) || rot->frames[entry->nodeIdx - 1].time != -1) {
                            entry->nodeIdx--;
                            entry->unk_0A--;
                            break;
                        }
                        entry->nodeIdx = 0;
                        entry->unk_0A = 0;
                    }
                }
            }
        }
    }
}

void func_80016638_main(s32 idx) {
    if (D_800A0620_main) {
        if ((u16)D_800CBB60_main[idx].unk_02 != 0xFFFF) {
            func_800333B0_main(D_800CBB60_main[idx].unk_02);
        }
        Hu3DModelKill(D_800CBB60_main[idx].modelId);
        D_800CBB60_main[idx].modelId = -1;
    }
}

void func_800166D0_main(void) {
    s16 i;

    if (D_800A0620_main) {
        for (i = 0; i < D_800CDD4E_main; i++) {
            if (D_800CBB60_main[i].modelId != -1) {
                func_800333B0_main(D_800CBB60_main[i].unk_02);
            }
        }
        func_80019C68_main(TAG_MODELENTRY);
        D_800A0620_main = 0;
    }
}

// Seems like a good file boundary: ROM 0x17384 (model set / hierarchy helpers start here; the HmfSpr
// code above does not call into them). Not aligned by 16 though.
HmfModelSet *func_80016784_main(s16 model, s16 step) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[HmfModelData[model].motId];
    HmfModelSet *set = HuMemMemoryAllocPerm(sizeof(HmfModelSet));

    set->unk_08 = HuMemMemoryAllocPerm((motion->unk02 + step) / step * (hmf->unk16 << 6));
    set->unk_04 = HuMemMemoryAllocPerm(hmf->unk16 * sizeof(s16));
    set->nodeCount = motion->unk02;
    set->unk_02 = step;
    func_800169E0_main(model, step, set, -1);
    return set;
}

HmfModelSet *func_800168A8_main(s16 model, s16 step, char *name) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[HmfModelData[model].motId];
    s16 node = func_8002C834_main(hmf, name);
    HmfModelSet *set = HuMemMemoryAllocPerm(sizeof(HmfModelSet));

    set->unk_08 = HuMemMemoryAllocPerm((motion->unk02 + step) / step * sizeof(HuMtx4F));
    set->unk_04 = HuMemMemoryAllocPerm(hmf->unk16 * sizeof(s16));
    set->nodeCount = motion->unk02;
    set->unk_02 = step;
    func_800169E0_main(model, step, set, node);
    return set;
}

void func_800169E0_main(s16 model, s16 step, HmfModelSet *set, s16 target) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[HmfModelData[model].motId];
    s16 frame;

    D_800D1358_main = set->unk_08;
    D_800D04B4_main = set->unk_04;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    for (frame = 0; frame < motion->unk02; frame += step) {
        func_8002DFF8_main(hmf, frame, motion, 1);
        D_800D138A_main = 0;
        func_80016C2C_main(hmf, 0, target);
    }
}

void func_80016B00_main(s16 model, s16 frame, const char *name, HuMtx4F *out) {
    s16 nodeMap[4];
    HmfData *hmf = HmfModelData[model].hmf;
    s16 node = func_8002C834_main(hmf, name);
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[HmfModelData[model].motId];

    D_800D1358_main = out;
    D_800D04B4_main = nodeMap;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(hmf, frame, motion, 1);
    D_800D138A_main = 0;
    func_80016C2C_main(hmf, 0, node);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void func_80016C2C_main(HmfData *hmf, s16 nodeIdx, s16 target) {
    HmfMotionNode *node = &hmf->unk80[nodeIdx];
    HuMtx4F mtx;
    s16 pushed = FALSE;
    s16 i;

    func_8008A070_main(mtx);
    if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
        func_80017C10_main(mtx, node->pos.x, node->pos.y, node->pos.z);
        pushed = TRUE;
    }
    if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
        func_80017D24_main(mtx, node->rot.x, node->rot.y, node->rot.z);
        pushed = TRUE;
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
        pushed = TRUE;
    }
    if (pushed) {
        D_800D138A_main++;
        func_80018044_main(mtx, D_800D5A00_main[D_800D138A_main - 1], D_800D5A00_main[D_800D138A_main]);
    }
    for (i = 0; i < node->unk00; i++) {
        if (node->unk50[i] & 0x8000) {
            if (node->unk50[i] == -1) {
                if (D_800CD1B0_main < hmf->unk16 && target == -1) {
                    D_800D04B4_main[D_800CD1B0_main] = nodeIdx;
                    func_8002367C_main(D_800D1358_main[D_800CD1B0_main++], D_800D5A00_main[D_800D138A_main]);
                }
            } else {
                func_80016C2C_main(hmf, node->unk50[i] & 0x7FFF, target);
            }
        } else if (target == -1 || target == (node->unk50[i] & 0x7FFF)) {
            if (D_800CD1B0_main < hmf->unk16) {
                D_800D04B4_main[D_800CD1B0_main] = nodeIdx;
            }
            func_8002367C_main(D_800D1358_main[D_800CD1B0_main++], D_800D5A00_main[D_800D138A_main]);
        }
    }
    if (pushed) {
        D_800D138A_main--;
    }
}

void func_80016FB4_main(s16 model, HmfModelSet *set, s16 frame) {
    HmfData *hmf;
    s16 start;
    s16 i;

    if (frame >= set->nodeCount) {
        frame = set->nodeCount - 1;
    }
    if (frame < 0) {
        frame = 0;
    }
    hmf = HmfModelData[model].hmf;
    HmfModelData[model].motId = 0xFF;
    start = hmf->unk16 * (frame / set->unk_02);
    D_800CD1B0_main = 0;
    D_800D1358_main = &set->unk_08[start];
    for (i = 0; i < hmf->unk16; i++) {
        func_8002367C_main(hmf->unk80[i].unk58, D_800D1358_main[set->unk_04[i]]);
    }
}

void func_80017128_main(s16 model, HmfModelSet *set, HuMtx4F mtx, s16 frame) {
    HmfModel *modelP = &HmfModelData[model];

    if (frame >= set->nodeCount) {
        frame = set->nodeCount - 1;
    }
    if (frame < 0) {
        frame = 0;
    }
    func_8008A070_main(mtx);
    if (modelP->pos.x != 0.0f || modelP->pos.y != 0.0f || modelP->pos.z != 0.0f) {
        func_80017C10_main(mtx, modelP->pos.x, modelP->pos.y, modelP->pos.z);
    }
    if (modelP->rot.x != 0.0f || modelP->rot.y != 0.0f || modelP->rot.z != 0.0f) {
        func_80017D24_main(mtx, modelP->rot.x, modelP->rot.y, modelP->rot.z);
    }
    if (modelP->scale.x != 1.0f || modelP->scale.y != 1.0f || modelP->scale.z != 1.0f) {
        func_80017CD0_main(mtx, modelP->scale.x, modelP->scale.y, modelP->scale.z);
    }
    guMtxCatF(set->unk_08[frame / set->unk_02], mtx, mtx);
}

void func_80017320_main(HmfModelSet *set) {
    HuMemMemoryFreePerm(set->unk_08);
    HuMemMemoryFreePerm(set->unk_04);
    HuMemMemoryFreePerm(set);
}

void func_80017358_main(s16 srcModel, const char *srcName, s16 dstModel, const char *dstName) {
    HmfData *src = HmfModelData[srcModel].hmf;
    HmfData *dst = HmfModelData[dstModel].hmf;
    s16 hash;
    s16 srcObj;
    s16 dstObj;
    s16 i, j;

    // Note: the strcmp calls compare against the address of the name pointer,
    // and the source object name is read from the destination model.
    hash = func_80011460_main((const u8 *)srcName);
    for (srcObj = 0; srcObj < src->unk10; srcObj++) {
        if (src->unk60[srcObj].unk26 == hash && strcmp(dst->unk60[srcObj].unk00, (char *)&srcName)) {
            break;
        }
    }
    if (srcObj == src->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", srcName);
        return;
    }
    hash = func_80011460_main((const u8 *)dstName);
    for (dstObj = 0; dstObj < dst->unk10; dstObj++) {
        if (dst->unk60[dstObj].unk26 == hash && strcmp(dst->unk60[dstObj].unk00, (char *)&dstName)) {
            break;
        }
    }
    if (dstObj == dst->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", dstName);
        return;
    }
    if (dst->unk80 == (HmfMotionNode *)-1) {
        for (i = 0; i < dst->unk64; i++) {
            HmfSkeletonNode *skel = &dst->unk68[i];

            if (skel->unk00 == dstObj) {
                skel->unk48 = src;
                skel->unk00 = srcObj;
                return;
            }
        }
    } else {
        for (i = 0; i < dst->unk16; i++) {
            HmfMotionNode *node = &dst->unk80[i];

            for (j = 0; j < node->unk00; j++) {
                if (node->unk50[j] == dstObj) {
                    node->unk54 = src;
                    node->unk50[j] = srcObj;
                    break;
                }
            }
        }
    }
}

// Character texture animation slots. The data below continues the .data of the earlier
// definitions without 16-byte alignment, and its strings follow the "Can't find ObjName"
// rodata, so this is the same file and the data is defined here rather than at the top.
char *D_800A063C_main[3 * 16] = {
    "c000n_0_DEF", "c001n_0_DEF", "c002n_0_DEF", "c003n_0_DEF",
    "c004n_0_DEF", "c005n_0_DEF", "c300n_0_DEF", "c301n_0_DEF",
    "c103m_0_DEF", "c103m_0_DEF", "c160n_0_DEF", "c161s_0_DEF",
    "c162n_0_DEF", "c164m_0_DEF", "c166n_0_DEF", "c204n_0_DEF",
    "c000l_0_DEF", "c001l_0_DEF", "c002l_0_DEF", "c003l_0_DEF",
    "c004l_0_DEF", "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF",
    "c103m_0_DEF", "c103m_0_DEF", "c160n_0_DEF", "c161n_0_DEF",
    "c162n_0_DEF", "c164m_0_DEF", "c166n_0_DEF", "c204n_0_DEF",
    "c000l_0_DEF", "c001l_0_DEF", "c002l_0_DEF", "c003l_0_DEF",
    "c004l_0_DEF", "c005l_0_DEF", "c300l_0_DEF", "c301l_0_DEF",
    "c103m_0_DEF", "c103m_0_DEF", "c160n_0_DEF", "c161n_0_DEF",
    "c162n_0_DEF", "c164m_0_DEF", "c166n_0_DEF", "c204n_0_DEF",
};
s16 D_800A06FC_main[] = {
    0x00A3, 0x00A4, 0x00A4,
    -1, 0x00A5, 0x00A5,
    -1, 0x00A6, 0x00A6,
    -1, 0x00A7, 0x00A7,
    -1, 0x00A8, 0x00A8,
    -1, 0x00A9, 0x00A9,
    -1, 0x00AA, 0x00AA,
};
s32 D_800A0728_main[8] = {
    0x00020000, 0x00030000, 0x00070000, 0x00040000,
    0x00050000, 0x00060000, 0x00080000, 0x00090000,
};
u16 D_800A0748_main[172] = {
    0x0904, 0x0905, 0x0702, 0x0906, 0x0704, 0x0705, 0x0706, 0x0707,
    0x0708, 0x0709, 0x070A, 0x070B, 0x070C, 0x070D, 0x070E, 0x070F,
    0x0710, 0x0711, 0x0712, 0x0713, 0x0714, 0x0715, 0x0716, 0x0717,
    0x0718, 0x0719, 0x071A, 0x071B, 0x071C, 0x071D, 0x071E, 0x071F,
    0x0720, 0x0721, 0x0722, 0x0723, 0x0724, 0x0725, 0x0726, 0x0727,
    0x0728, 0x0729, 0x072A, 0x072B, 0x072C, 0x072D, 0x072E, 0x0907,
    0x0908, 0x0909, 0x090A, 0x090B, 0x090C, 0x090D, 0x090E, 0x090F,
    0x0910, 0x0911, 0x0912, 0x073B, 0x073C, 0x073D, 0x073E, 0x073F,
    0x0740, 0x0741, 0x0742, 0x0743, 0x0744, 0x0745, 0x0746, 0x0747,
    0x0748, 0x0749, 0x074A, 0x074B, 0x074C, 0x074D, 0x0913, 0x074F,
    0x0750, 0x0751, 0x0752, 0x0753, 0x0754, 0x0755, 0x0756, 0x0757,
    0x0758, 0x0759, 0x075A, 0x075B, 0x075C, 0x075D, 0x075E, 0x075F,
    0x0760, 0x0761, 0x0914, 0x0763, 0x0764, 0x0765, 0x0766, 0x0767,
    0x0768, 0x0769, 0x076A, 0x076B, 0x076C, 0x076D, 0x076E, 0x076F,
    0x0770, 0x0771, 0x0772, 0x0773, 0x0774, 0x0775, 0x0776, 0x0777,
    0x0778, 0x0915, 0x077A, 0x077B, 0x077C, 0x077D, 0x077E, 0x077F,
    0x0780, 0x0781, 0x0782, 0x0783, 0x0784, 0x0785, 0x0786, 0x0787,
    0x0788, 0x0789, 0x078A, 0x078B, 0x078C, 0x078D, 0x078E, 0x0916,
    0x0790, 0x0917, 0x0792, 0x0793, 0x0794, 0x0795, 0x0796, 0x0797,
    0x0798, 0x0799, 0x079A, 0x079B, 0x0918, 0x0919, 0x079E, 0x079F,
    0x0900, 0x0901, 0x0903, 0x091A, 0x091B, 0x091C, 0x091D, 0x091E,
    0x0922, 0x0925, 0x0926, 0x0927,
};

void func_8001766C_main(void) {
    s16 i, j, k;

    for (i = 0; i < 6; i++) {
        D_800D6A50_main[i] = 0;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 7; k++) {
                D_800D4090_main[i][j][k] = -1;
            }
        }
    }
    for (k = 0; k < 16; k++) {
        D_800D20B8_main[k][0] = D_800D20B8_main[k][1] = D_800D20B8_main[k][2] = 0xFF;
    }
}

s16 func_80017790_main(s16 model, s16 slot, s16 chr, s32 dataNum) {
    void *data;
    s32 anim;
    s16 animIdx;

    if (D_800D20B8_main[chr][slot] != 0xFF) {
        func_80033354_main(D_800D20B8_main[chr][slot]);
        func_80033354_main(D_800D5570_main[chr][slot]);
    }
    data = DataRead(dataNum);
    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, D_800A063C_main[chr + slot * 16]);
    D_800D5570_main[chr][slot] = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_800D20B8_main[chr][slot] = HmfAnimLink(HmfModelData[model].hmf, anim, 0, D_800A063C_main[chr + slot * 16]);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_80017954_main(s16 model, s16 slot, s16 chr, s16 animIdx) {
    if (D_800D20B8_main[chr][slot] != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            HmfAnim *anim;

            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[D_800D20B8_main[chr][slot]];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

void func_80017A84_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfAnim *anim = &D_800D1714_main[D_800D20B8_main[arg2][arg1]];

    anim->frame = arg3;
    anim->interp = arg4;
}

s16 func_80017AD8_main(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_80017B20_main(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    func_80032FC0_main(D_800D20B8_main[arg1][arg0], arg2, arg3);
}

s32 func_80017B6C_main(s16 chr, s16 arg1, s16 arg2) {
    return func_80017BB8_main(chr, D_800A06FC_main[arg2 * 3 + arg1]);
}

s32 func_80017BB8_main(s16 chr, s16 animId) {
    if (chr == 7) {
        u16 packed = D_800A0748_main[animId];
        return ((packed & 0xFF00) << 8) | (packed & 0xFF);
    }
    return D_800A0728_main[chr] | animId;
}
