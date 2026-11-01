#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfspr.h"
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

extern u8 D_800A0620_main;
extern s16 D_800A0624_main[];
extern u16 D_800CDD4E_main;
extern s16 D_800CD1B0_main;
extern s16 *D_800D04B4_main;
extern HuMtx4F *D_800D1358_main;
extern s16 D_800D138A_main;
extern HuMtx4F D_800D5A00_main[];
extern s16 D_800A06FC_main[];
extern s32 D_800A0728_main[8];
extern u16 D_800A0748_main[172];
extern Vtx *D_800CC080_main[8];
extern Vtx *D_800CDD54_main;
extern u8 D_800D2008_main;
extern Gfx *D_800D1F30_main;
extern s16 D_800D4090_main[6][3][7];
extern u8 D_800D6A50_main[6];
extern char *D_800A063C_main[3 * 16];

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
        ((s32 **)&D_800D1360)[i] = HuMemAllocTag((s16)count * 256, TAG_MODELENTRY);
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
        D_800D1F30_main = ((Gfx *const *)&D_800D1360)[playerIdx];
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

void func_80014714_main(s16 arg0, s16 arg1) {
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

void func_80016B00_main(s16 model, s16 frame, char *name, HuMtx4F *out) {
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

void func_80017358_main(s16 srcModel, char *srcName, s16 dstModel, char *dstName) {
    HmfData *src = HmfModelData[srcModel].hmf;
    HmfData *dst = HmfModelData[dstModel].hmf;
    s16 hash;
    s16 srcObj;
    s16 dstObj;
    s16 i, j;

    // Note: the strcmp calls compare against the address of the name pointer,
    // and the source object name is read from the destination model.
    hash = func_80011460_main((u8 *)srcName);
    for (srcObj = 0; srcObj < src->unk10; srcObj++) {
        if (src->unk60[srcObj].unk26 == hash && strcmp(dst->unk60[srcObj].unk00, (char *)&srcName)) {
            break;
        }
    }
    if (srcObj == src->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", srcName);
        return;
    }
    hash = func_80011460_main((u8 *)dstName);
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

// Reasonable file boundary: ROM 0x1826C (character texture animation slots start here; only the
// code below uses D_800D20B8_main, D_800D4090_main, D_800D6A50_main and D_800A063C_main).
// Not aligned by 16 though.
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

// Possible file boundary: ROM 0x18810 (generic matrix math helpers start here; weak evidence,
// no padding and no rodata/data used by the functions below)
void func_80017C10_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    mtx[3][0] += x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0];
    mtx[3][1] += x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1];
    mtx[3][2] += x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2];
    mtx[3][3] += x * mtx[0][3] + y * mtx[1][3] + z * mtx[2][3];
}

void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 0; i < 3; i++) {
        mtx[0][i] *= x;
        mtx[1][i] *= y;
        mtx[2][i] *= z;
    }
}

void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    f32 rot[3][3];
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;
    f32 m00, m01, m02;
    f32 m10, m11, m12;

    sincosdf(x, &sx, &cx);
    if (x == y) {
        sy = sx;
        cy = cx;
    } else {
        sincosdf(y, &sy, &cy);
    }
    if (x == z) {
        sz = sx;
        cz = cx;
    } else if (y == z) {
        sz = sy;
        cz = cy;
    } else {
        sincosdf(z, &sz, &cz);
    }
    rot[0][0] = cy * cz;
    rot[0][1] = cy * sz;
    rot[0][2] = -sy;
    rot[1][0] = sx * sy * cz - cx * sz;
    rot[1][1] = sx * sy * sz + cx * cz;
    rot[1][2] = sx * cy;
    rot[2][0] = cx * sy * cz + sx * sz;
    rot[2][1] = cx * sy * sz - sx * cz;
    rot[2][2] = cx * cy;
    m00 = rot[0][0] * mtx[0][0] + rot[0][1] * mtx[1][0] + rot[0][2] * mtx[2][0];
    m01 = rot[0][0] * mtx[0][1] + rot[0][1] * mtx[1][1] + rot[0][2] * mtx[2][1];
    m02 = rot[0][0] * mtx[0][2] + rot[0][1] * mtx[1][2] + rot[0][2] * mtx[2][2];
    m10 = rot[1][0] * mtx[0][0] + rot[1][1] * mtx[1][0] + rot[1][2] * mtx[2][0];
    m11 = rot[1][0] * mtx[0][1] + rot[1][1] * mtx[1][1] + rot[1][2] * mtx[2][1];
    m12 = rot[1][0] * mtx[0][2] + rot[1][1] * mtx[1][2] + rot[1][2] * mtx[2][2];
    mtx[2][0] = rot[2][0] * mtx[0][0] + rot[2][1] * mtx[1][0] + rot[2][2] * mtx[2][0];
    mtx[2][1] = rot[2][0] * mtx[0][1] + rot[2][1] * mtx[1][1] + rot[2][2] * mtx[2][1];
    mtx[2][2] = rot[2][0] * mtx[0][2] + rot[2][1] * mtx[1][2] + rot[2][2] * mtx[2][2];
    mtx[0][0] = m00;
    mtx[0][1] = m01;
    mtx[0][2] = m02;
    mtx[1][0] = m10;
    mtx[1][1] = m11;
    mtx[1][2] = m12;
}

void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out) {
    s32 i;

    if (a[0][3] != 0.0f || a[1][3] != 0.0f || a[2][3] != 0.0f || a[3][3] != 1.0f) {
        f32 b00, b01, b02, b03;
        f32 b10, b11, b12, b13;
        f32 b20, b21, b22, b23;
        f32 b30, b31, b32, b33;
        f32 r0, r1, r2, r3;

        i = 0;
        b00 = b[0][0];
        b10 = b[1][0];
        b20 = b[2][0];
        b30 = b[3][0];
        b01 = b[0][1];
        b11 = b[1][1];
        b21 = b[2][1];
        b31 = b[3][1];
        b02 = b[0][2];
        b12 = b[1][2];
        b22 = b[2][2];
        b32 = b[3][2];
        b03 = b[0][3];
        b13 = b[1][3];
        b23 = b[2][3];
        b33 = b[3][3];
        for (; i < 4; i++) {
            out[i][0] = (r0 = a[i][0]) * b00 + (r1 = a[i][1]) * b10 + (r2 = a[i][2]) * b20 + (r3 = a[i][3]) * b30;
            out[i][1] = r0 * b01 + r1 * b11 + r2 * b21 + r3 * b31;
            out[i][2] = r0 * b02 + r1 * b12 + r2 * b22 + r3 * b32;
            out[i][3] = r0 * b03 + r1 * b13 + r2 * b23 + r3 * b33;
        }
    } else {
        f32 b00, b01, b02, b03;
        f32 b10, b11, b12, b13;
        f32 b20, b21, b22, b23;
        f32 r0, r1, r2;
        f32 c0, c1, c2;

        i = 0;
        b00 = b[0][0];
        b10 = b[1][0];
        b20 = b[2][0];
        b01 = b[0][1];
        b11 = b[1][1];
        b21 = b[2][1];
        b02 = b[0][2];
        b12 = b[1][2];
        b22 = b[2][2];
        b03 = b[0][3];
        b13 = b[1][3];
        b23 = b[2][3];
        for (; i < 3; i++) {
            out[i][0] = (r0 = a[i][0]) * b00 + (r1 = a[i][1]) * b10 + (r2 = a[i][2]) * b20;
            out[i][1] = r0 * b01 + r1 * b11 + r2 * b21;
            out[i][2] = r0 * b02 + r1 * b12 + r2 * b22;
            out[i][3] = r0 * b03 + r1 * b13 + r2 * b23;
        }
        out[3][0] = (c0 = a[3][0]) * b[0][0] + (c1 = a[3][1]) * b[1][0] + (c2 = a[3][2]) * b[2][0] + b[3][0];
        out[3][1] = c0 * b[0][1] + c1 * b[1][1] + c2 * b[2][1] + b[3][1];
        out[3][2] = c0 * b[0][2] + c1 * b[1][2] + c2 * b[2][2] + b[3][2];
        out[3][3] = c0 * b[0][3] + c1 * b[1][3] + c2 * b[2][3] + b[3][3];
    }
}

s16 func_800183A0_main(HuMtx4F src, HuMtx4F dst) {
    f32 c00 = src[1][1] * src[2][2] - src[1][2] * src[2][1];
    f32 c10 = src[1][2] * src[2][0] - src[1][0] * src[2][2];
    f32 c20 = src[1][0] * src[2][1] - src[1][1] * src[2][0];
    f32 det = c00 * src[0][0] + c10 * src[0][1] + c20 * src[0][2];

    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    dst[0][0] = c00 * det;
    dst[1][0] = c10 * det;
    dst[2][0] = c20 * det;
    dst[0][1] = (src[0][2] * src[2][1] - src[0][1] * src[2][2]) * det;
    dst[0][2] = (src[0][1] * src[1][2] - src[0][2] * src[1][1]) * det;
    dst[1][1] = (src[0][0] * src[2][2] - src[0][2] * src[2][0]) * det;
    dst[1][2] = (src[0][2] * src[1][0] - src[0][0] * src[1][2]) * det;
    dst[2][1] = (src[0][1] * src[2][0] - src[0][0] * src[2][1]) * det;
    dst[2][2] = (src[0][0] * src[1][1] - src[0][1] * src[1][0]) * det;
    dst[0][3] = dst[1][3] = dst[2][3] = dst[3][0] = dst[3][1] = dst[3][2] = 0.0f;
    dst[3][3] = 1.0f;
    return 1;
}

s32 func_80018544_main(HuMtx4F src, HuMtx4F dst) {
    HuMtx4F inv;

    if (!func_800183A0_main(src, inv)) {
        guMtxIdentF(dst);
        return 0;
    }
    guMtxCatF(inv, src, dst);
    return 1;
}

void func_800185A4_main(HuMtx4F mtx, f32 angle) {
    f32 s = sindf(angle);
    f32 c = cosdf(angle);
    f32 row0[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        row0[i] = mtx[0][i];
    }
    for (i = 0; i < 3; i++) {
        mtx[0][i] = c * row0[i] - s * mtx[2][i];
        mtx[2][i] = s * row0[i] + c * mtx[2][i];
    }
}

void func_8001866C_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    HuMtx4F tmp;
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;
    f32 a, b, c;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    tmp[0][0] = mtx[0][0];
    tmp[0][1] = mtx[0][1];
    tmp[0][2] = mtx[0][2];
    tmp[0][3] = mtx[0][3];
    tmp[1][0] = mtx[1][0];
    tmp[1][1] = mtx[1][1];
    tmp[1][2] = mtx[1][2];
    tmp[1][3] = mtx[1][3];
    tmp[2][0] = mtx[2][0];
    tmp[2][1] = mtx[2][1];
    tmp[2][2] = mtx[2][2];
    tmp[2][3] = mtx[2][3];
    a = cx * sz;
    b = -cz * sy + cy * sx * sz;
    c = cy * cz + sx * sy * sz;
    mtx[0][0] = a * tmp[1][0] + b * tmp[2][0] + c * tmp[0][0];
    mtx[0][1] = a * tmp[1][1] + b * tmp[2][1] + c * tmp[0][1];
    mtx[0][2] = a * tmp[1][2] + b * tmp[2][2] + c * tmp[0][2];
    mtx[0][3] = a * tmp[1][3] + b * tmp[2][3] + c * tmp[0][3];
    a = cx * cz;
    b = cz * sx * sy - cy * sz;
    c = cy * cz * sx + sy * sz;
    mtx[1][0] = a * tmp[1][0] + b * tmp[0][0] + c * tmp[2][0];
    mtx[1][1] = a * tmp[1][1] + b * tmp[0][1] + c * tmp[2][1];
    mtx[1][2] = a * tmp[1][2] + b * tmp[0][2] + c * tmp[2][2];
    mtx[1][3] = a * tmp[1][3] + b * tmp[0][3] + c * tmp[2][3];
    a = cx * cy;
    b = cx * sy;
    mtx[2][0] = a * tmp[2][0] - tmp[1][0] * sx + b * tmp[0][0];
    mtx[2][1] = a * tmp[2][1] - tmp[1][1] * sx + b * tmp[0][1];
    mtx[2][2] = a * tmp[2][2] - tmp[1][2] * sx + b * tmp[0][2];
    mtx[2][3] = a * tmp[2][3] - tmp[1][3] * sx + b * tmp[0][3];
}

void func_80018978_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    mtx[0][0] = cy * cz + sx * sy * sz;
    mtx[1][0] = -cx * sz;
    mtx[2][0] = cz * sy + cy * sx * sz;
    mtx[0][1] = cz * sx * sy + cy * sz;
    mtx[1][1] = cx * cz;
    mtx[2][1] = -cy * cz * sx + sy * sz;
    mtx[0][2] = -cx * sy;
    mtx[1][2] = sx;
    mtx[2][2] = cx * cy;
    mtx[3][0] = mtx[3][1] = mtx[3][2] = mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
    mtx[3][3] = 1.0f;
}

f32 InterpolateBMLine(f32 *value, f32 *time, f32 x) {
    f32 slope[2];
    f32 midTime, midValue, midSlope;
    f32 crossTime;
    f32 dx, b;
    f32 t0, t1, v0, v1, s0, s1;
    s32 crosses;
    s32 i;

    if (value[0] == value[1] && value[0] == value[2] && value[0] == value[3]) {
        return value[0];
    }
    for (i = 1; i < 3; i++) {
        slope[i - 1] = ((value[i] - value[i - 1]) / (time[i] - time[i - 1]) +
                        (value[i + 1] - value[i]) / (time[i + 1] - time[i])) *
                       0.5f;
    }
    midTime = (time[2] + time[1]) * 0.5f;
    crosses = FALSE;
    if (slope[1] - slope[0] != 0.0f) {
        crossTime = (slope[1] * time[2] - slope[0] * time[1] - (value[2] - value[1])) / (slope[1] - slope[0]);
        if (time[1] <= crossTime && crossTime <= time[2]) {
            crosses = TRUE;
        }
    }
    if (crosses == TRUE) {
        dx = midTime - time[1];
        b = (value[2] - value[1]) / (time[2] - time[1]) - (slope[1] - slope[0]) / 2.0f;
        midValue = (slope[1] - slope[0]) / ((time[2] - time[1]) * 2) * dx * dx + b * dx + value[1];
        midSlope = (slope[1] - slope[0]) / (time[2] - time[1]) * dx + b;
    } else {
        dx = midTime - time[1];
        midValue = (value[2] + value[1]) * (dx / (time[2] - time[1]));
        midSlope = (value[2] - value[1]) * 2 / (time[2] - time[1]) - (slope[1] + slope[0]) * (dx / (time[2] - time[1]));
    }
    if (x < midTime) {
        t0 = time[1];
        v0 = value[1];
        s0 = slope[0];
        t1 = midTime;
        v1 = midValue;
        s1 = midSlope;
    } else {
        t0 = midTime;
        v0 = midValue;
        s0 = midSlope;
        t1 = time[2];
        v1 = value[2];
        s1 = slope[1];
    }
    return (s1 - s0) / ((t1 - t0) * 2) * (x - t0) * (x - t0) + ((v1 - v0) / (t1 - t0) - (s1 - s0) / 2.0f) * (x - t0) + v0;
}

f32 func_80018D68_main(f32 mtx[3][3]) {
    f32 m10 = mtx[1][0], m11 = mtx[1][1], m12 = mtx[1][2];
    f32 m20 = mtx[2][0], m21 = mtx[2][1], m22 = mtx[2][2];

    return mtx[0][0] * (m11 * m22 - m12 * m21) +
           mtx[0][1] * (m12 * m20 - m10 * m22) +
           mtx[0][2] * (m10 * m21 - m11 * m20);
}

void func_80018DD8_main(f32 arg0[4][4], s32 arg1, s32 arg2, f32 arg3[3][3]) {
    s32 i, j, k, l;

    k = 0;
    for (i = 0; i < 4; i++) {
        if (i != arg1) {
            l = 0;
            for (j = 0; j < 4; j++) {
                if (j != arg2) {
                    arg3[k][l] = arg0[i][j];
                    l++;
                }
            }
            k++;
        }
    }
}

f32 func_80018E50_main(HuMtx4F mtx, s32 row, s32 col) {
    f32 minor[3][3];

    func_80018DD8_main(mtx, row, col, minor);
    return func_80018D68_main(minor);
}

f32 func_80018E74_main(HuMtx4F mtx) {
    f32 det = 0.0f;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 sign = (i != i / 2 * 2) ? -1 : 1;

        det += func_80018E50_main(mtx, 0, i) * mtx[0][i] * sign;
    }
    return det;
}

s32 func_80018F18_main(HuMtx4F src, HuMtx4F dst) {
    f32 det = func_80018E74_main(src);
    s32 i, j;

    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s32 sign = i + j;

            sign = (sign != sign / 2 * 2) ? -1 : 1;

            dst[j][i] = func_80018E50_main(src, i, j) * det * sign;
        }
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6A98_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AA4_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AB0_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6ABC_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AC8_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AD4_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AE0_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AEC_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6AF8_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B04_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B10_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B1C_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B28_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B34_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B40_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B4C_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B58_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B64_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B70_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B7C_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B88_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6B94_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6BA0_main);

INCLUDE_RODATA("asm/nonmatchings/hmfspr", D_800A6BAC_main);
