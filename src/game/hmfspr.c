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

extern u16 Hu3DSprModelMax;
extern s16 motionBakeMtxCnt;
extern s16 *motionBakeNodeMap;
extern HuMtx4F *motionBakeMtx;
extern s16 Hu3DObjMtxStackIdx;
extern HuMtx4F Hu3DObjMtxStack[];
extern Vtx *Hu3DSprVtxBuf[8];
extern Vtx *Hu3DSprVtxPos;
extern u8 Hu3DBufNo;
extern Gfx *Hu3DSprGfxPos;
extern s16 CharAnimWork[6][3][7];
extern u8 CharAnimWorkNum[6];

u8 Hu3DSprModelInitF = 0;
s16 sprTexFilterTbl[] = { G_TF_POINT, G_TF_AVERAGE, G_TF_BILERP, G_TF_POINT };
s16 sprCharDirTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 }; // unreferenced

/* hmfanim functions. This file does not include game/hmfanim.h: it was compiled
 * against an s16 return type for Hu3DAnimDataCreate, which is declared s32 there. */
s32 Hu3DAnimCreate(HmfData *hmf, void *data, s16 bank, const char *name);
s16 Hu3DAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, const char *name);
s16 Hu3DAnimDataCreate(u8 *data);
void Hu3DAnimAttrSet(s16 animIdx, u8 bitmask, u8 flags);
void Hu3DAnimKill(s16 animIdx);
void Hu3DAnimDataKill(s16 animIdx);
void Hu3DModelAnimStop(HmfData *hmf);
void Hu3DModelAnimStart(HmfData *hmf);


void Hu3DSprModelInit(s32 count) {
    s16 i;

    Hu3DSprModelMax = count;
    for (i = 0; i < Hu3DBufNum; i++) {
        Hu3DSprVtxBuf[i] = HuMemAllocTag((s16)count * 128, TAG_MODELENTRY);
        Hu3DSprGfxBuf[i] = HuMemAllocTag((s16)count * 256, TAG_MODELENTRY);
    }
    Hu3DSprModelData = HuMemAllocTag((s16)count * sizeof(HmfModelEntry), TAG_MODELENTRY);
    for (i = 0; i < (s16)count; i++) {
        Hu3DSprModelData[i].modelId = -1;
    }
    Hu3DSprModelInitF = 1;
    Hu3DSprModelBufSwap();
}

void Hu3DSprModelBufSwap(void) {
    if (Hu3DSprModelInitF) {
        s32 playerIdx = Hu3DBufNo;

        Hu3DSprVtxPos = Hu3DSprVtxBuf[playerIdx];
        Hu3DSprGfxPos = Hu3DSprGfxBuf[playerIdx];
    }
}

u16 Hu3DSprModelCreate(void *data, u32 flags, u16 attr) {
    s16 i;
    s16 id;

    for (i = 0; i < Hu3DSprModelMax; i++) {
        if (Hu3DSprModelData[i].modelId == -1) {
            break;
        }
    }
    if (i == Hu3DSprModelMax) {
        return -1;
    }
    id = Hu3DModelDLCreate(flags, NULL, 4);
    if (id == -1) {
        return -1;
    }
    Hu3DSprModelData[i].modelId = id;
    if (data != (void *)-1) {
        id = Hu3DAnimDataCreate(data);
        Hu3DAnimSetData[id].refCount = 1;
        if (id == -1) {
            Hu3DModelKill(Hu3DSprModelData[i].modelId);
            Hu3DSprModelData[i].modelId = -1;
        }
    } else {
        id = -1;
    }
    Hu3DSprModelData[i].unk_02 = id;
    Hu3DSprModelData[i].flags = attr;
    Hu3DSprModelData[i].unk_12 = Hu3DSprModelData[i].colorR = Hu3DSprModelData[i].colorG = Hu3DSprModelData[i].colorB = 0xFF;
    Hu3DSprModelData[i].unk_0A = 0;
    Hu3DSprModelData[i].unk_08 = 0;
    Hu3DSprModelData[i].nodeIdx = 0;
    Hu3DSprModelData[i].pointIdx = 0;
    Hu3DSprModelData[i].unk_20 = NULL;
    return i;
}

u16 Hu3DSprModelLink(s16 idx, u16 attr) {
    s16 newIdx = Hu3DSprModelCreate((void *)-1, Hu3DData[Hu3DSprModelData[idx].modelId].attr, attr);

    Hu3DAnimSetData[Hu3DSprModelData[newIdx].unk_02 = Hu3DSprModelData[idx].unk_02].refCount++;
    return newIdx;
}

void Hu3DSprModelAttrSet(s16 arg0, u16 arg1, u16 arg2) {
    HmfModelEntry *entry = &Hu3DSprModelData[arg0];
    entry->flags = (entry->flags & ~arg1) | arg2;
}

void Hu3DSprModelFrameSet(s16 arg0, u16 arg1) {
    Hu3DSprModelData[arg0].nodeIdx = arg1;
}

void Hu3DSprModelPointSet(s16 arg0, u16 arg1) {
    Hu3DSprModelData[arg0].pointIdx = arg1;
    Hu3DSprModelData[arg0].nodeIdx = 0;
    Hu3DSprModelData[arg0].unk_08 = 0;
}

u16 Hu3DSprModelFrameGet(s16 arg0) {
    return Hu3DSprModelData[arg0].nodeIdx;
}

void Hu3DSprModelTPLvlSet(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        s32 visible;

        Hu3DSprModelData[arg0].unk_12 = arg1;
        visible = (u8)arg1 != 0xFF ? 0x10000 : 0;
        Hu3DModelObjAttrSet(Hu3DSprModelData[arg0].modelId, 0x10000, visible);
    }
}

void Hu3DSprModelColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    if (arg0 != -1) {
        Hu3DSprModelData[arg0].colorR = arg1;
        Hu3DSprModelData[arg0].colorG = arg2;
        Hu3DSprModelData[arg0].colorB = arg3;
    }
}

void Hu3DSprModelReset(s16 arg0) {
    HmfModelEntry *entry = &Hu3DSprModelData[arg0];

    entry->unk_0A = 0;
    entry->nodeIdx = 0;
    entry->flags &= 0xFF7F;
    Hu3DModelAttrSet(entry->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void Hu3DSprModelColorFadeSet(s16 idx, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1) {
    if (idx != -1) {
        Hu3DSprModelAttrSet(idx, 0x40, 0x40);
        Hu3DSprModelData[idx].colorStart[0] = r0;
        Hu3DSprModelData[idx].colorStart[1] = g0;
        Hu3DSprModelData[idx].colorStart[2] = b0;
        Hu3DSprModelData[idx].colorStart[3] = a0;
        Hu3DSprModelData[idx].colorEnd[0] = r1;
        Hu3DSprModelData[idx].colorEnd[1] = g1;
        Hu3DSprModelData[idx].colorEnd[2] = b1;
        Hu3DSprModelData[idx].colorEnd[3] = a1;
    }
}

void Hu3DSprModelColorKeySet(s16 arg0, HmfColorKey *arg1) {
    if (arg0 != -1) {
        Hu3DSprModelAttrSet(arg0, 0x40, 0x40);
        Hu3DSprModelData[arg0].unk_20 = arg1;
        Hu3DSprModelData[arg0].unk_0E = 0;
        Hu3DSprModelData[arg0].unk_0C = 0;
    }
}

void Hu3DSprModelExec(s32 frames) {
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

    if (!Hu3DSprModelInitF) {
        return;
    }
    for (i = 0; i < Hu3DSprModelMax; i++) {
        if (Hu3DSprModelData[i].modelId == -1) {
            continue;
        }
        entry = &Hu3DSprModelData[i];
        if ((Hu3DData[entry->modelId].attr & 4) || (u16)entry->unk_02 == 0xFFFF) {
            continue;
        }
        if (entry->flags & 0x80) {
            Hu3DModelAttrSet(entry->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            entry->flags &= 0xFF7F;
            continue;
        }
        hmf = Hu3DData[entry->modelId].hmf;
        *hmf->unk3C->unk00 = Hu3DSprGfxPos;
        animSet = &Hu3DAnimSetData[(u16)entry->unk_02];
        rot = &animSet->rot[entry->pointIdx];
        gDPSetCycleType(Hu3DSprGfxPos++, G_CYC_1CYCLE);
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
                gDPSetCombineMode(Hu3DSprGfxPos++, HMFSPR_CC_PRIM_MODULATEA, HMFSPR_CC_PRIM_MODULATEA);
            } else {
                gDPSetCombineMode(Hu3DSprGfxPos++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            }
            hmf->unk60->unk50 |= 0x10000;
            if (entry->flags & 0x100) {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            } else {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gDPSetAlphaCompare(Hu3DSprGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(Hu3DSprGfxPos++, 0, 0, 0, 1);
            gDPSetPrimColor(Hu3DSprGfxPos++, 0, 0, entry->colorR, entry->colorG, entry->colorB, entry->unk_12);
        } else if (entry->unk_12 == 0xFF) {
            if (entry->flags & 0x100) {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            } else {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
            }
            gDPSetCombineMode(Hu3DSprGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        } else {
            hmf->unk60->unk50 |= 0x10000;
            gDPSetAlphaCompare(Hu3DSprGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(Hu3DSprGfxPos++, 0, 0, 0, 1);
            gDPSetPrimColor(Hu3DSprGfxPos++, 0, 0, 0, 0, 0, entry->unk_12);
            if (entry->flags & 0x100) {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            } else {
                gDPSetRenderMode(Hu3DSprGfxPos++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            }
            gDPSetCombineMode(Hu3DSprGfxPos++, HMFSPR_CC_MODULATEA_PRIM, HMFSPR_CC_MODULATEA_PRIM);
        }
        gDPSetTextureFilter(Hu3DSprGfxPos++, sprTexFilterTbl[(entry->flags & 0x18) >> 3]);
        gSPClearGeometryMode(Hu3DSprGfxPos++, G_CULL_BACK | G_LIGHTING);
        gSPSetGeometryMode(Hu3DSprGfxPos++, G_ZBUFFER);
        image = &animSet->unk0C[rot->frames[entry->nodeIdx].unk00];
        width = image->width;
        height = image->height;
        if (animSet->rotCount == 0) {
            gDPSetTextureLUT(Hu3DSprGfxPos++, G_TT_NONE);
            if (animSet->interp & 0x8000) {
                gDPLoadTextureBlock_4b(Hu3DSprGfxPos++, image->data, G_IM_FMT_I, width, height, 0,
                                       G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                       HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureBlock(Hu3DSprGfxPos++, image->data, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                    HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            }
        } else {
            gDPSetTextureLUT(Hu3DSprGfxPos++, G_TT_RGBA16);
            if (animSet->rotCount <= 16) {
                gDPLoadTLUT_pal16(Hu3DSprGfxPos++, 0, animSet->unk14);
                gDPLoadTextureBlock_4b(Hu3DSprGfxPos++, image->data, G_IM_FMT_CI, width, height, 0,
                                       G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                       HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTLUT_pal256(Hu3DSprGfxPos++, animSet->unk14);
                gDPLoadTextureBlock(Hu3DSprGfxPos++, image->data, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, HMF_TEXTURE_MASK(image->width),
                                    HMF_TEXTURE_MASK(image->height), G_TX_NOLOD, G_TX_NOLOD);
            }
        }
        gSPVertex(Hu3DSprGfxPos++, osVirtualToPhysical(Hu3DSprVtxPos), 4, 0);
        gSP1Quadrangle(Hu3DSprGfxPos++, 0, 1, 2, 3, 0);

        negHeight = -height;
        x0 = -image->unk04;
        y0 = image->unk06;
        Hu3DSprVtxPos->n.ob[0] = x0;
        Hu3DSprVtxPos->n.ob[1] = y0;
        Hu3DSprVtxPos->n.ob[2] = 0;
        Hu3DSprVtxPos->n.n[0] = Hu3DSprVtxPos->n.n[1] = Hu3DSprVtxPos->n.n[2] = -1;
        Hu3DSprVtxPos->n.tc[0] = 0;
        Hu3DSprVtxPos->n.tc[1] = 0;
        Hu3DSprVtxPos->n.a = 0xFF;
        Hu3DSprVtxPos++;

        Hu3DSprVtxPos->n.ob[0] = x0;
        Hu3DSprVtxPos->n.ob[1] = negHeight + y0;
        Hu3DSprVtxPos->n.ob[2] = 0;
        Hu3DSprVtxPos->n.n[0] = Hu3DSprVtxPos->n.n[1] = Hu3DSprVtxPos->n.n[2] = -1;
        Hu3DSprVtxPos->n.tc[0] = 0;
        Hu3DSprVtxPos->n.tc[1] = (-negHeight - 1) << 5;
        Hu3DSprVtxPos->n.a = 0xFF;
        Hu3DSprVtxPos++;

        Hu3DSprVtxPos->n.ob[0] = width + x0;
        Hu3DSprVtxPos->n.ob[1] = negHeight + y0;
        Hu3DSprVtxPos->n.ob[2] = 0;
        Hu3DSprVtxPos->n.n[0] = Hu3DSprVtxPos->n.n[1] = Hu3DSprVtxPos->n.n[2] = -1;
        Hu3DSprVtxPos->n.tc[0] = (width - 1) << 5;
        Hu3DSprVtxPos->n.tc[1] = (-negHeight - 1) << 5;
        Hu3DSprVtxPos->n.a = 0xFF;
        Hu3DSprVtxPos++;

        Hu3DSprVtxPos->n.ob[0] = width + x0;
        Hu3DSprVtxPos->n.ob[1] = y0;
        Hu3DSprVtxPos->n.ob[2] = 0;
        Hu3DSprVtxPos->n.n[0] = Hu3DSprVtxPos->n.n[1] = Hu3DSprVtxPos->n.n[2] = -1;
        Hu3DSprVtxPos->n.tc[0] = (width - 1) << 5;
        Hu3DSprVtxPos->n.tc[1] = 0;
        Hu3DSprVtxPos->n.a = 0xFF;
        Hu3DSprVtxPos++;

        gSPEndDisplayList(Hu3DSprGfxPos++);

        if (!(entry->flags & 1) && (Hu3DPauseF == 0 || (Hu3DData[entry->modelId].attr & 0x8000))) {
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

void Hu3DSprModelKill(s32 idx) {
    if (Hu3DSprModelInitF) {
        if ((u16)Hu3DSprModelData[idx].unk_02 != 0xFFFF) {
            Hu3DAnimDataKill(Hu3DSprModelData[idx].unk_02);
        }
        Hu3DModelKill(Hu3DSprModelData[idx].modelId);
        Hu3DSprModelData[idx].modelId = -1;
    }
}

void Hu3DSprModelAllKill(void) {
    s16 i;

    if (Hu3DSprModelInitF) {
        for (i = 0; i < Hu3DSprModelMax; i++) {
            if (Hu3DSprModelData[i].modelId != -1) {
                Hu3DAnimDataKill(Hu3DSprModelData[i].unk_02);
            }
        }
        HuMemDelayFreeAllWithTag(TAG_MODELENTRY);
        Hu3DSprModelInitF = 0;
    }
}

// Seems like a good file boundary: ROM 0x17384 (model set / hierarchy helpers start here; the HmfSpr
// code above does not call into them). Not aligned by 16 though.
HmfModelSet *Hu3DMotionBake(s16 model, s16 step) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];
    HmfModelSet *set = HuMemMemoryAllocPerm(sizeof(HmfModelSet));

    set->unk_08 = HuMemMemoryAllocPerm((motion->unk02 + step) / step * (hmf->unk16 << 6));
    set->unk_04 = HuMemMemoryAllocPerm(hmf->unk16 * sizeof(s16));
    set->nodeCount = motion->unk02;
    set->unk_02 = step;
    Hu3DMotionBakeSub(model, step, set, -1);
    return set;
}

HmfModelSet *Hu3DMotionBakeObj(s16 model, s16 step, char *name) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];
    s16 node = SearchObjectIndex(hmf, name);
    HmfModelSet *set = HuMemMemoryAllocPerm(sizeof(HmfModelSet));

    set->unk_08 = HuMemMemoryAllocPerm((motion->unk02 + step) / step * sizeof(HuMtx4F));
    set->unk_04 = HuMemMemoryAllocPerm(hmf->unk16 * sizeof(s16));
    set->nodeCount = motion->unk02;
    set->unk_02 = step;
    Hu3DMotionBakeSub(model, step, set, node);
    return set;
}

void Hu3DMotionBakeSub(s16 model, s16 step, HmfModelSet *set, s16 target) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];
    s16 frame;

    motionBakeMtx = set->unk_08;
    motionBakeNodeMap = set->unk_04;
    motionBakeMtxCnt = 0;
    guMtxIdentF(Hu3DObjMtxStack[0]);
    for (frame = 0; frame < motion->unk02; frame += step) {
        Hu3DMotionExec(hmf, frame, motion, 1);
        Hu3DObjMtxStackIdx = 0;
        objMtxCalcFrame(hmf, 0, target);
    }
}

void Hu3DModelObjMtxFrameGet(s16 model, s16 frame, const char *name, HuMtx4F *out) {
    s16 nodeMap[4];
    HmfData *hmf = Hu3DData[model].hmf;
    s16 node = SearchObjectIndex(hmf, name);
    HmfModelData_Unk64_Unk8C_Struct *motion = &Hu3DMotion[Hu3DData[model].motId];

    motionBakeMtx = out;
    motionBakeNodeMap = nodeMap;
    motionBakeMtxCnt = 0;
    guMtxIdentF(Hu3DObjMtxStack[0]);
    Hu3DMotionExec(hmf, frame, motion, 1);
    Hu3DObjMtxStackIdx = 0;
    objMtxCalcFrame(hmf, 0, node);
    if (motionBakeMtxCnt >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void objMtxCalcFrame(HmfData *hmf, s16 nodeIdx, s16 target) {
    HmfMotionNode *node = &hmf->unk80[nodeIdx];
    HuMtx4F mtx;
    s16 pushed = FALSE;
    s16 i;

    HuMtxIdentF(mtx);
    if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
        mtxTransCat(mtx, node->pos.x, node->pos.y, node->pos.z);
        pushed = TRUE;
    }
    if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
        mtxRotCat(mtx, node->rot.x, node->rot.y, node->rot.z);
        pushed = TRUE;
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
        pushed = TRUE;
    }
    if (pushed) {
        Hu3DObjMtxStackIdx++;
        mtxCat(mtx, Hu3DObjMtxStack[Hu3DObjMtxStackIdx - 1], Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
    }
    for (i = 0; i < node->unk00; i++) {
        if (node->unk50[i] & 0x8000) {
            if (node->unk50[i] == -1) {
                if (motionBakeMtxCnt < hmf->unk16 && target == -1) {
                    motionBakeNodeMap[motionBakeMtxCnt] = nodeIdx;
                    mtxCopy(motionBakeMtx[motionBakeMtxCnt++], Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
                }
            } else {
                objMtxCalcFrame(hmf, node->unk50[i] & 0x7FFF, target);
            }
        } else if (target == -1 || target == (node->unk50[i] & 0x7FFF)) {
            if (motionBakeMtxCnt < hmf->unk16) {
                motionBakeNodeMap[motionBakeMtxCnt] = nodeIdx;
            }
            mtxCopy(motionBakeMtx[motionBakeMtxCnt++], Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
        }
    }
    if (pushed) {
        Hu3DObjMtxStackIdx--;
    }
}

void Hu3DMotionBakeApply(s16 model, HmfModelSet *set, s16 frame) {
    HmfData *hmf;
    s16 start;
    s16 i;

    if (frame >= set->nodeCount) {
        frame = set->nodeCount - 1;
    }
    if (frame < 0) {
        frame = 0;
    }
    hmf = Hu3DData[model].hmf;
    Hu3DData[model].motId = 0xFF;
    start = hmf->unk16 * (frame / set->unk_02);
    motionBakeMtxCnt = 0;
    motionBakeMtx = &set->unk_08[start];
    for (i = 0; i < hmf->unk16; i++) {
        mtxCopy(hmf->unk80[i].unk58, motionBakeMtx[set->unk_04[i]]);
    }
}

void Hu3DMotionBakeMtxGet(s16 model, HmfModelSet *set, HuMtx4F mtx, s16 frame) {
    HmfModel *modelP = &Hu3DData[model];

    if (frame >= set->nodeCount) {
        frame = set->nodeCount - 1;
    }
    if (frame < 0) {
        frame = 0;
    }
    HuMtxIdentF(mtx);
    if (modelP->pos.x != 0.0f || modelP->pos.y != 0.0f || modelP->pos.z != 0.0f) {
        mtxTransCat(mtx, modelP->pos.x, modelP->pos.y, modelP->pos.z);
    }
    if (modelP->rot.x != 0.0f || modelP->rot.y != 0.0f || modelP->rot.z != 0.0f) {
        mtxRotCat(mtx, modelP->rot.x, modelP->rot.y, modelP->rot.z);
    }
    if (modelP->scale.x != 1.0f || modelP->scale.y != 1.0f || modelP->scale.z != 1.0f) {
        mtxScaleCat(mtx, modelP->scale.x, modelP->scale.y, modelP->scale.z);
    }
    guMtxCatF(set->unk_08[frame / set->unk_02], mtx, mtx);
}

void Hu3DMotionBakeFree(HmfModelSet *set) {
    HuMemMemoryFreePerm(set->unk_08);
    HuMemMemoryFreePerm(set->unk_04);
    HuMemMemoryFreePerm(set);
}

void Hu3DModelObjCopy(s16 srcModel, const char *srcName, s16 dstModel, const char *dstName) {
    HmfData *src = Hu3DData[srcModel].hmf;
    HmfData *dst = Hu3DData[dstModel].hmf;
    s16 hash;
    s16 srcObj;
    s16 dstObj;
    s16 i, j;

    // Note: the strcmp calls compare against the address of the name pointer,
    // and the source object name is read from the destination model.
    hash = HmfNameHash((const u8 *)srcName);
    for (srcObj = 0; srcObj < src->unk10; srcObj++) {
        if (src->unk60[srcObj].unk26 == hash && strcmp(dst->unk60[srcObj].unk00, (char *)&srcName)) {
            break;
        }
    }
    if (srcObj == src->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", srcName);
        return;
    }
    hash = HmfNameHash((const u8 *)dstName);
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
char *CharAnimNameTbl[3 * 16] = {
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
s16 CharMotionNumTbl[] = {
    0x00A3, 0x00A4, 0x00A4,
    -1, 0x00A5, 0x00A5,
    -1, 0x00A6, 0x00A6,
    -1, 0x00A7, 0x00A7,
    -1, 0x00A8, 0x00A8,
    -1, 0x00A9, 0x00A9,
    -1, 0x00AA, 0x00AA,
};
s32 CharMotionDirTbl[8] = {
    0x00020000, 0x00030000, 0x00070000, 0x00040000,
    0x00050000, 0x00060000, 0x00080000, 0x00090000,
};
u16 CharMotionDataTbl[172] = {
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

void CharAnimInit(void) {
    s16 i, j, k;

    for (i = 0; i < 6; i++) {
        CharAnimWorkNum[i] = 0;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 7; k++) {
                CharAnimWork[i][j][k] = -1;
            }
        }
    }
    for (k = 0; k < 16; k++) {
        CharAnimId[k][0] = CharAnimId[k][1] = CharAnimId[k][2] = 0xFF;
    }
}

s16 CharAnimCreate(s16 model, s16 slot, s16 chr, s32 dataNum) {
    void *data;
    s32 anim;
    s16 animIdx;

    if (CharAnimId[chr][slot] != 0xFF) {
        Hu3DAnimKill(CharAnimId[chr][slot]);
        Hu3DAnimKill(CharAnimSrc[chr][slot]);
    }
    data = DataRead(dataNum);
    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, CharAnimNameTbl[chr + slot * 16]);
    CharAnimSrc[chr][slot] = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    CharAnimId[chr][slot] = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, CharAnimNameTbl[chr + slot * 16]);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void CharAnimSet(s16 model, s16 slot, s16 chr, s16 animIdx) {
    if (CharAnimId[chr][slot] != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            HmfAnim *anim;

            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[CharAnimId[chr][slot]];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

void CharAnimFrameSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfAnim *anim = &Hu3DAnimData[CharAnimId[arg2][arg1]];

    anim->frame = arg3;
    anim->interp = arg4;
}

s16 Hu3DAnimDataRead(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void CharAnimAttrSet(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    Hu3DAnimAttrSet(CharAnimId[arg1][arg0], arg2, arg3);
}

s32 CharMotionDataNumGetTbl(s16 chr, s16 arg1, s16 arg2) {
    return CharMotionDataNumGet(chr, CharMotionNumTbl[arg2 * 3 + arg1]);
}

s32 CharMotionDataNumGet(s16 chr, s16 animId) {
    if (chr == 7) {
        u16 packed = CharMotionDataTbl[animId];
        return ((packed & 0xFF00) << 8) | (packed & 0xFF);
    }
    return CharMotionDirTbl[chr] | animId;
}
