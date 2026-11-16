#include "game/overlays/minigames/11_puddle_paddle/puddle_paddle.h"
#include "gcc/memory.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/mallocblock.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"

typedef struct RGBA {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
} RGBA;

typedef struct PuddlePaddleAnimMdl { // size = 0x28, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char pad09[1];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char pad0E[2];
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ Vec unk_1C;
} PuddlePaddleAnimMdl; // size = 0x28

typedef struct PuddlePaddlePlane {
    /* 0x00 */ Vec normal;
    /* 0x0C */ f32 constant;
    /* 0x10 */ s8 axis;
    /* 0x11 */ char padding[3];
} PuddlePaddlePlane; // Size 0x14

typedef struct PuddlePaddleCollider { // 0xE4 bytes
    /* 0x00 */ s32 unk_00;        // flags
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ f32 *x;
    /* 0x0C */ f32 *y;
    /* 0x10 */ f32 *z;
    /* 0x14 */ f32 *rx;
    /* 0x18 */ f32 *ry;
    /* 0x1C */ f32 *rz;
    /* 0x20 */ HuMtx4F matrix;
    /* 0x60 */ Vec vertices[4];
    /* 0x90 */ Vec transformed[4];
    /* 0xC0 */ s16 vertexCount;
    /* 0xC2 */ char unk_C2[2];
    /* 0xC4 */ f32 unk_C4;
    /* 0xC8 */ PuddlePaddlePlane plane;
    /* 0xDC */ f32 unk_DC;
    /* 0xE0 */ s16 source;
    /* 0xE2 */ char unk_E2[2];
} PuddlePaddleCollider; // Size 0xE4

typedef struct PuddlePaddleMover { // 0x34 bytes
    /* 0x00 */ s32 unk_00;        // flags
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[2];
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec facing;
    /* 0x24 */ f32 unk_24; // radius
    /* 0x28 */ s16 unk_28; // hmf model index
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ char unk_32[2];
} PuddlePaddleMover; // Size 0x34

extern s16 Hu3DModelTag;
extern u8 Hu3DBufNo;

Gfx m217_gfxRdpInit[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx m217_gfxRspInit[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx m217_gfxInit[] = {
    gsSPDisplayList(m217_gfxRspInit),
    gsSPDisplayList(m217_gfxRdpInit),
    gsSPEndDisplayList(),
};

Gfx m217_gfxBillboardInit[] = {
    gsDPPipeSync(),
    gsSPDisplayList(m217_gfxInit),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

PuddlePaddleAnimMdl *m217_animMdlTbl BSS;
PuddlePaddleSprite *m217_sprTbl BSS;
PuddlePaddleBillboard *m217_billboardTbl BSS;
PuddlePaddleFuncGroup *m217_funcGroupTbl BSS;
PuddlePaddleCollider *m217_colliderTbl BSS;

void m217_FuncGroupSort(PuddlePaddleFuncGroup *group);
s16 m217_BillboardMdlCreate(HuSprAnimData *sprite, f32 alpha);
s16 m217_BillboardAnimMdlCreate(HuSprAnimData *sprite, f32 alpha);
s16 m217_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *hmf, f32 scale, u16 arg3, u16 arg4);
void m217_BillboardPatSet(u16 model, HuSprAnimData *sprite, u16 frame);
s32 m217_CylinderHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship);
s32 m217_SphereHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship);
s32 m217_PlaneHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship);
s16 m217_PolyInsideCheck(PuddlePaddleCollider *boat, Vec *point);
f32 m217_PlaneDistCalc(PuddlePaddleCollider *boat, Vec *point);
s32 m217_PrismHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship);
f32 m217_EdgeSideCalc(PuddlePaddleMover *arg0, Vec *arg1, Vec *arg2);
void m217_PlaneCalc(Vec *vertices, PuddlePaddlePlane *plane);
void m217_MtxIdentSet(f32 *mtx);

void m217_SystemCreate(void) {
    m217_sprTbl = HuMemAllocTag(20 * sizeof(PuddlePaddleSprite), TAG_OVERLAY);
    memset(m217_sprTbl, 0, 20 * sizeof(PuddlePaddleSprite));
    m217_animMdlTbl = HuMemAllocTag(16 * sizeof(PuddlePaddleAnimMdl), TAG_OVERLAY);
    memset(m217_animMdlTbl, 0, 16 * sizeof(PuddlePaddleAnimMdl));
    m217_billboardTbl = HuMemAllocTag(16 * sizeof(PuddlePaddleBillboard), TAG_OVERLAY);
    memset(m217_billboardTbl, 0, 16 * sizeof(PuddlePaddleBillboard));
    m217_funcGroupTbl = HuMemAllocTag(8 * sizeof(PuddlePaddleFuncGroup), TAG_OVERLAY);
}

PuddlePaddleFuncGroup *m217_FuncGroupCreate(omObjData *object, s8 index, s16 count, s16 handlers) {
    PuddlePaddleFuncGroup *group;

    if (index >= 8) {
        return NULL;
    }
    group = &m217_funcGroupTbl[index];
    if (handlers != 0) {
        group->unk_04 = HuMemAllocTag(handlers * sizeof(PuddlePaddleFunc), TAG_OVERLAY);
        memset(group->unk_04, 0, handlers * sizeof(PuddlePaddleFunc));
        group->unk_0C = HuMemAllocTag((handlers + 1) * sizeof(PuddlePaddleOrder), TAG_OVERLAY);
    }
    group->unk_08 = handlers;
    group->unk_00 = HuMemAllocTag(sizeof(PuddlePaddleSlot), TAG_OVERLAY);
    if (count != 0) {
        group->unk_00->unk_04 = HuMemAllocTag(count * sizeof(s16), TAG_OVERLAY);
        memset(group->unk_00->unk_04, 0, count * sizeof(s16));
    }
    group->unk_00->unk_08 = count;
    group->unk_10 = 1;
    group->unk_00->unk_00 = object;
    return group;
}

s16 m217_FuncSet(s8 index, s32 priority, void *data, void (*callback)(), s8 tag) {
    PuddlePaddleFuncGroup *group = &m217_funcGroupTbl[index];
    PuddlePaddleFunc *handler = group->unk_04;
    s16 i;
    s16 count = group->unk_08;

    for (i = 0; i < count; i++, handler++) {
        if (handler->unk_00 == 0) {
            handler->unk_00 = 1;
            handler->unk_08 = priority;
            handler->unk_02 = i;
            handler->unk_05 = tag;
            handler->unk_04 = 0;
            handler->unk_3C = data;
            handler->unk_40 = callback;
            break;
        }
    }
    group->unk_10 = 1;
    return i;
}

void m217_FuncReset(s8 arg0, PuddlePaddleFunc *arg1) {
    memset(arg1, 0, sizeof(PuddlePaddleFunc));
    m217_funcGroupTbl[arg0].unk_10 = 1;
}

void m217_FuncTagReset(s8 index, s8 tag) {
    PuddlePaddleFuncGroup *group = &m217_funcGroupTbl[index];
    PuddlePaddleFunc *handler = group->unk_04;
    s16 i;

    for (i = 0; i < group->unk_08; i++, handler++) {
        if (handler->unk_05 == tag) {
            m217_FuncReset(index, handler);
        }
    }
}

void m217_FuncGroupReset(s8 arg0) {
    PuddlePaddleFuncGroup *obj = &m217_funcGroupTbl[arg0];

    memset(obj->unk_04, 0, obj->unk_08 * sizeof(PuddlePaddleFunc));
    obj->unk_10 = 1;
}

void m217_FuncGroupUpdate(s8 index) {
    PuddlePaddleFuncGroup *group = &m217_funcGroupTbl[index];
    PuddlePaddleFunc *handler;
    s8 i;

    if (group->unk_10 != 0) {
        m217_FuncGroupSort(group);
    }
    i = 0;
    while (group->unk_0C[i].next != -1) {
        i = group->unk_0C[i].next;
        handler = &group->unk_04[group->unk_0C[i].handler];
        if (handler->unk_00 != 0) {
            handler->unk_40(group->unk_00, handler);
        }
    }
}

void m217_FuncGroupSort(PuddlePaddleFuncGroup *group) {
    PuddlePaddleOrder *order = group->unk_0C;
    PuddlePaddleFunc *handler = group->unk_04;
    s16 entry;
    s16 tail;
    s16 i;
    s16 insert;
    s16 current;
    s16 found;

    order[0].next = -1;
    entry = 1;
    tail = 0;
    for (i = 0; i < group->unk_08; i++, handler++) {
        if (handler->unk_00 != 0) {
            insert = tail;
            found = 0;
            current = 0;
            while (order[current].next != -1) {
                current = order[current].next;
                if ((u32)handler->unk_08 < order[current].priority) {
                    insert = current;
                    found = 1;
                    break;
                }
            }
            order[entry].handler = i;
            order[entry].priority = handler->unk_08;
            if (found != 0) {
                order[entry].next = order[order[insert].previous].next;
                order[entry].previous = order[insert].previous;
                order[order[insert].previous].next = entry;
                order[order[entry].next].previous = entry;
            } else {
                order[entry].next = order[insert].next;
                order[entry].previous = insert;
                order[insert].next = entry;
                tail = entry;
            }
            entry++;
        }
    }
    group->unk_10 = 0;
}

s16 m217_SprCreate(s16 priority, s32 directory, s32 file, u16 bank, s32 attr) {
    PuddlePaddleSprite *sprite = m217_sprTbl;
    HuSprite *data;
    s16 i;

    for (i = 0; i < 20; i++, sprite++) {
        if (sprite->unk_00 == 0) {
            sprite->unk_02 = HuSprAnimDataRead((directory << 16) | file);
            sprite->unk_01 = HuSprGrpCreate(1, 0);
            sprite->unk_06 = 255;
            HuSprAttrReset(sprite->unk_01, 0, -1);
            HuSprGrpMemberSet(sprite->unk_01, 0, sprite->unk_02, 0);
            HuSprAttrSet(sprite->unk_01, 0, attr);
            HuSprAnimModeSet(sprite->unk_01, 0, bank);
            HuSprPriSet(sprite->unk_01, 0, (u16)priority);
            HuSprPatNoSet(sprite->unk_01, 0, 0);
            HuSprSpeedSet(sprite->unk_01, 0, 1.0f);
            HuSprScaleSet(sprite->unk_01, 0, 1.0f, 1.0f);
            HuSprPosSet(sprite->unk_01, 0, 100, 100);
            data = HuSprGet(sprite->unk_01, 0);
            if (bank == 0) {
                sprite->unk_04 = 99;
            } else {
                sprite->unk_04 = data->data->patNum;
            }
            sprite->unk_00 = 2;
            m217_SprDispOff(i);
            break;
        }
    }
    return i;
}

void m217_SprDispOn(s16 index, s16 x, s16 y) {
    PuddlePaddleSprite *sprite = &m217_sprTbl[index];

    if (sprite->unk_00 != 0) {
        HuSprPatNoSet(sprite->unk_01, 0, 0);
        HuSprDispOn(sprite->unk_01, 0);
        HuSprPosSet(sprite->unk_01, 0, x, y);
        sprite->unk_00 = 2;
    }
}

void m217_SprDispOff(s16 arg0) {
    PuddlePaddleSprite *spr = &m217_sprTbl[arg0];

    if (spr->unk_00 != 0) {
        HuSprDispOff(spr->unk_01, 0);
        spr->unk_00 = 1;
    }
}

void m217_SprUpdate(void) {
    PuddlePaddleSprite *sprite = m217_sprTbl;
    s16 i;

    for (i = 0; i < 20; i++, sprite++) {
        if (sprite->unk_00 == 2) {
            if (HuSprGet(sprite->unk_01, 0)->patNo + 1 >= (u16)sprite->unk_04) {
                HuSprDispOff(sprite->unk_01, 0);
                HuSprPatNoSet(sprite->unk_01, 0, 0);
            }
        }
    }
}

s16 m217_AnimMdlCreate(s32 directory, s32 file, f32 speed, s16 type, s32 flags, s32 attr) {
    PuddlePaddleAnimMdl *work = m217_animMdlTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = Hu3DModelRead((directory << 16) | file, attr);
            Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &Hu3DData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = type;
            work->unk_04 = flags;
            work->unk_10 = speed;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 m217_AnimMdlLinkCreate(s16 arg0, f32 arg1, s16 arg2, s32 arg3) {
    PuddlePaddleAnimMdl *work = m217_animMdlTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = Hu3DModelLink(arg0);
            Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &Hu3DData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = arg2;
            work->unk_04 = arg3;
            work->unk_10 = arg1;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 m217_AnimMdlFreeGet(s16 type) {
    PuddlePaddleAnimMdl *work = m217_animMdlTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_0A == type) {
            model = &Hu3DData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
                break;
            }
        }
    }
    if (i == 16) {
        return -1;
    }
    return i;
}

s32 m217_AnimMdlDispOn(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay) {
    PuddlePaddleAnimMdl *work;
    HmfModel *model;

    if (index >= 16) {
        return 0;
    }
    if (m217_animMdlTbl[index].unk_00 == 0) {
        return 0;
    }
    work = &m217_animMdlTbl[index];
    model = &Hu3DData[work->unk_0C];
    if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
        Hu3DModelPosSet(work->unk_0C, x, y, z);
        Hu3DModelScaleSet(work->unk_0C, scale, scale, scale);
        work->unk_1C.x = rx;
        work->unk_1C.y = ry;
        work->unk_1C.z = rz;
        if (delay == 0.0f) {
            Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            work->unk_08 = 1;
            work->unk_18 = 0.0f;
            work->unk_14 = 0.0f;
            model->motSpeed = work->unk_10;
        } else {
            work->unk_08 = 0;
            work->unk_18 = delay;
            work->unk_14 = 0;
        }
        return 1;
    }
    return 0;
}

void m217_AnimMdlUpdate(void) {
    PuddlePaddleAnimMdl *work = m217_animMdlTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 != -1) {
            model = &Hu3DData[work->unk_0C];
            func_80088910_main(model->mtx, work->unk_1C.x, work->unk_1C.y, work->unk_1C.z);
            if (work->unk_08 != 0) {
                if (model->motTime >= Hu3DMotion[Hu3DData[work->unk_0C].motId].unk02) {
                    model->motTime = 0;
                    if (model->hmf->unk98 != NULL) {
                        model->hmf->unk98->unk08 = 0;
                    }
                    if (!(work->unk_04 & 1)) {
                        Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        work->unk_08 = -1;
                        model->motSpeed = 0;
                    }
                }
            } else {
                if (work->unk_14++ >= work->unk_18) {
                    Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    work->unk_08 = 1;
                    model->motSpeed = work->unk_10;
                }
            }
        }
    }
}

s16 m217_BillboardCreate(s32 directory, s32 file, s16 interval, s16 type, s32 flags) {
    PuddlePaddleBillboard *work = m217_billboardTbl;
    s16 frame;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            frame = HuSprAnimDataRead((directory << 16) | file);
            work->unk_0A = frame;
            if (flags & 1) {
                work->unk_0C = m217_BillboardAnimMdlCreate(HuSprAnimDataGet(frame), 1.0f);
            } else {
                work->unk_0C = m217_BillboardMdlCreate(HuSprAnimDataGet(frame), 1.0f);
            }
            if (flags & 8) {
                Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            work->unk_18 = &Hu3DData[work->unk_0C].pos.x;
            work->unk_1C = &Hu3DData[work->unk_0C].pos.y;
            work->unk_20 = &Hu3DData[work->unk_0C].pos.z;
            work->unk_08 = type;
            work->unk_04 = flags;
            work->unk_0E = HuSprAnimDataGet(frame)->patNum;
            work->unk_10 = 0;
            work->unk_12 = 0;
            work->unk_14 = interval;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 m217_BillboardFreeGet(s16 type) {
    PuddlePaddleBillboard *work = m217_billboardTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 == type) {
            model = &Hu3DData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && (work->unk_04 & 8) != 0) {
                break;
            }
        }
    }
    if (i == 16) {
        return -1;
    }
    return i;
}

void m217_BillboardDispOn(s16 index, f32 x, f32 y, f32 z) {
    HmfModel *model;

    if (index < 16) {
        model = &Hu3DData[m217_billboardTbl[index].unk_0C];
        model->pos.x = x;
        model->pos.y = y;
        model->pos.z = z;
        Hu3DModelAttrSet(m217_billboardTbl[index].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        m217_billboardTbl[index].unk_04 &= ~0x18;
    }
}

void m217_BillboardDispOnRef(s16 index, f32 *x, f32 *y, f32 *z) {
    HmfModel *model;

    if (index < 16) {
        model = &Hu3DData[m217_billboardTbl[index].unk_0C];
        if (x != NULL) {
            m217_billboardTbl[index].unk_18 = x;
        } else {
            m217_billboardTbl[index].unk_18 = &model->pos.x;
        }
        if (y != NULL) {
            m217_billboardTbl[index].unk_1C = y;
        } else {
            m217_billboardTbl[index].unk_1C = &model->pos.y;
        }
        if (z != NULL) {
            m217_billboardTbl[index].unk_20 = z;
        } else {
            m217_billboardTbl[index].unk_20 = &model->pos.z;
        }
        Hu3DModelAttrSet(m217_billboardTbl[index].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        m217_billboardTbl[index].unk_04 = (m217_billboardTbl[index].unk_04 & ~0x18) | 0x10;
    }
}

PuddlePaddleBillboard *m217_BillboardGet(s16 arg0) {
    PuddlePaddleBillboard *ret;

    if (arg0 < 0x10) {
        ret = &m217_billboardTbl[arg0];
    } else {
        ret = 0;
    }
    return ret;
}

HmfModel *m217_BillboardMdlGet(s16 arg0) {
    HmfModel *ret;

    if (arg0 < 0x10) {
        ret = &Hu3DData[m217_billboardTbl[arg0].unk_0C];
    } else {
        ret = 0;
    }
    return ret;
}

void m217_BillboardUpdate(void) {
    PuddlePaddleBillboard *work = m217_billboardTbl;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && !(work->unk_04 & 8)) {
            model = &Hu3DData[work->unk_0C];
            if (work->unk_04 & 0x10) {
                model->pos.x = *work->unk_18;
                model->pos.y = *work->unk_1C;
                model->pos.z = *work->unk_20;
            }
            model->rot.x = CRot.x;
            model->rot.y = CRot.y;
            if (work->unk_04 & 1) {
                if (work->unk_04 & 2) {
                    if (++work->unk_12 > work->unk_14) {
                        work->unk_12 = 0;
                        m217_BillboardPatSet(work->unk_0C, HuSprAnimDataGet(work->unk_0A), work->unk_10);
                        if (++work->unk_10 >= work->unk_0E) {
                            if (work->unk_04 & 4) {
                                work->unk_10 = 0;
                            } else {
                                work->unk_10 = 0;
                                work->unk_04 |= 8;
                                Hu3DModelAttrSet(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                }
            }
        }
    }
}

s16 m217_BillboardMdlCreate(HuSprAnimData *sprite, f32 alpha) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    u32 frameCount;
    s32 size;
    s32 frameSize;
    s16 model;
    s16 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = Hu3DModelDLCreate(0x4C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    frameCount = m217_BillboardVtxCreate(sprite, hmf, 1.0f, 0, 0x64);
    gSPDisplayList(gfx++, osVirtualToPhysical(m217_gfxBillboardInit));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        frameSize = 0x800;
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        frameSize = 0x1000;
    }
    gDPPipeSync(gfx++);
    for (i = 0; i < frameCount; i++) {
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->data + frameSize * i));
        gDPLoadTextureBlock(gfx++, 0x02000000, G_IM_FMT_CI, G_IM_SIZ_8b,
                            sprite->pat->sizeX, sprite->pat->sizeY / frameCount, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x01, osVirtualToPhysical(&hmf->unk44[0][i * 4]));
        gSPVertex(gfx++, 0x01000000, 4, 0);
        gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    }
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk00[0] = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk00[0], size);
    HuMemFree(dlBuf);
    return model;
}

s16 m217_BillboardAnimMdlCreate(HuSprAnimData *sprite, f32 alpha) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    s32 size;
    s16 model;
    s16 format;
    s16 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = Hu3DModelDLCreate(0x4C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(0x14, Hu3DModelTag);
    m217_BillboardVtxCreate(sprite, hmf, 1.0f, 0, 0x1E);
    gSPDisplayList(gfx++, osVirtualToPhysical(m217_gfxBillboardInit));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->palNum >= 2) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    } else {
        if (sprite->pixelBits & 0x8000) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        } else {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        }
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, alpha * 255.0f);
    }
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
        gDPPipeSync(gfx++);
        format = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = (sprite->pixelBits & 0x8000) ? 4 : 0;
    }
    switch (sprite->pixelBits & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format,
                                   sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b,
                                sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b,
                                sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk00[0] = hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk00[0], size);
    HuMemFree(dlBuf);
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = *(hmf->unk3C->unk00 + (i + 1)) = HuMemAllocTag(0x100, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[Hu3DBufNo + 1];
    return model;
}

s16 m217_BillboardColorMdlCreate(HuSprAnimData *sprite, RGBA *color) {
    HmfData *hmf;
    Gfx *dlBuf;
    Gfx *gfx;
    s32 size;
    s32 model;
    s32 format;
    s32 i;

    dlBuf = gfx = HuMemAlloc(0x10000);
    model = Hu3DModelDLCreate(0x8C1, dlBuf, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x01010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(0x18, Hu3DModelTag);
    m217_BillboardVtxCreate(sprite, hmf, 1.0f, 0, 0);
    gSPDisplayList(gfx++, osVirtualToPhysical(m217_gfxBillboardInit));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 0x01, 0x01, 0x01, 0x01);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->pixelBits & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk10, size);
    HuMemFree(dlBuf);
    dlBuf = gfx = HuMemAlloc(0x10000);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
        gDPPipeSync(gfx++);
        format = 2;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = (sprite->pixelBits & 0x8000) ? 4 : 0;
    }
    switch (sprite->pixelBits & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format,
                                   sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b,
                                sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b,
                                sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 0x01, osVirtualToPhysical(hmf->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u32)gfx - (u32)dlBuf;
    hmf->unk3C->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(dlBuf, hmf->unk3C->unk14, size);
    HuMemFree(dlBuf);
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = hmf->unk3C->unk00[i + 1] = HuMemAllocTag(0x100, hmf->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 0x02, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[Hu3DBufNo + 1];
    return model;
}

void m217_BillboardPatSet(u16 model, HuSprAnimData *sprite, u16 frame) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[Hu3DBufNo + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->pat[frame].data));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPPipeSync(gfx + 3);
    gSPEndDisplayList(gfx + 4);
}

void m217_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[Hu3DBufNo + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->pat[frame].data));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s16 m217_BillboardVtxCreate(HuSprAnimData *arg0, HmfData *arg1, f32 arg2, u16 arg3, u16 arg4) {
    Vtx *temp_s7;
    Vtx *var_s1;
    Vtx_t *var_t0;
    Vtx_t *var_a3;
    s32 var_a2;
    s32 temp_s4;
    s32 temp_a1;
    s32 sp24;
    s32 temp_f2;
    s32 var_s0;
    s32 var_s2;
    s32 sp2C;
    s32 temp_lo;
    s32 temp_s3;
    s32 var_s0_2;
    s32 var_a2_2;

    if (arg0->palNum >= 2) {
        var_a2 = 0x800;
    } else {
        var_a2 = 0x1000;
    }
    temp_s4 = arg0->pat->sizeX;
    temp_a1 = arg0->pat->sizeY;
    sp24 = (f64)(temp_s4 * 0x64) * arg2 / 32.0;
    temp_f2 = (f64)(temp_a1 * 0x64) * arg2 / 32.0;
    if ((arg0->pixelBits & 0xFFF) == 4) {
        var_s0 = ((temp_s4 + 1) & 0xFFFE) * temp_a1 * 4;
    } else {
        var_s0 = temp_s4 * temp_a1 * arg0->pixelBits;
    }
    var_s0 = (var_s0 < 0) ? (var_s0 + 7) : var_s0;
    var_s0 >>= 3;
    var_s2 = var_s0 / var_a2;
    if (var_s2 <= 0) {
        var_s2 = 1;
    }
    sp2C = temp_a1 / var_s2;
    temp_lo = temp_f2 / var_s2;
    temp_s3 = var_s2 * 4;
    temp_s7 = var_s1 = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
    memset(temp_s7, 0, temp_s3 * sizeof(Vtx));
    for (var_s0_2 = 0; var_s0_2 < var_s2; var_s0_2++, var_s1 += 4) {
        var_s1[0].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[0].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[0].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[0].v.tc[1] = 0;
        var_s1[1].v.ob[0] = (s32)(sp24 * 0.5);
        var_s1[1].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[1].v.tc[0] = (temp_s4 - 1) * 64;
        var_s1[1].v.tc[1] = (sp2C - 1) * 64;
        var_s1[2].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[2].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * var_s0_2);
        var_s1[2].v.tc[0] = 0;
        var_s1[2].v.tc[1] = 0;
        var_s1[3].v.ob[0] = (s32) - (sp24 * 0.5);
        var_s1[3].v.ob[1] = (s32)(temp_f2 * 0.5 - temp_lo * (var_s0_2 + 1));
        var_s1[3].v.tc[0] = 0;
        var_s1[3].v.tc[1] = (sp2C - 1) * 64;
        for (var_a2_2 = 0; var_a2_2 < 4; var_a2_2++) {
            var_s1[var_a2_2].v.ob[0] += arg3;
            var_s1[var_a2_2].v.ob[1] += arg4;
            var_s1[var_a2_2].v.ob[2] = 0;
            var_s1[var_a2_2].v.flag = 0;
            var_s1[var_a2_2].v.cn[3] = 0xFF;
            var_s1[var_a2_2].v.cn[0] = var_s1[var_a2_2].v.cn[1] = var_s1[var_a2_2].v.cn[2] = 0;
        }
    }
    var_s1 = temp_s7;
    for (var_s0_2 = 0; var_s0_2 < Hu3DBufNum; var_s0_2++) {
        arg1->unk44[var_s0_2] = HuMemAllocTag(temp_s3 * sizeof(Vtx), arg1->unk0E);
        var_t0 = &arg1->unk44[var_s0_2]->v;
        var_a3 = &var_s1->v;
        for (var_a2_2 = 0; var_a2_2 < temp_s3; var_a2_2++) {
            *(var_t0++) = *(var_a3++);
        }
    }
    HuMemFree(temp_s7);
    return var_s2;
}

void m217_ColliderInit(PuddlePaddleSlot *slot, PuddlePaddleFunc *handler) {
    m217_FuncReset(handler->unk_05, handler);
}

s32 m217_ColliderCreate(void) {
    s32 unused[6]; // Unreferenced, but present in the stack frame.

    return 0;
}

s32 m217_ColliderLinkCreate(void) {
    s32 unused[6]; // Unreferenced, but present in the stack frame.

    return 0;
}

void m217_ColliderVtxSet(s16 index, Vec *vertices, f32 arg2) {
    PuddlePaddleCollider *boat;
    Vec *destination;

    if (index >= 0) {
        return;
    }
    if (m217_colliderTbl[index].unk_04 == 0) {
        return;
    }
    boat = &m217_colliderTbl[index];
    destination = boat->vertices;
    memcpy(destination, vertices, boat->vertexCount * sizeof(Vec));
    boat->unk_C4 = arg2;
    m217_PlaneCalc(destination, &boat->plane);
}

void m217_ColliderUpdate(void) {
    s32 unused[8]; // Unreferenced, but present in the stack frame.
}

void m217_MoverInit(PuddlePaddleMover *ship, s16 count, f32 radius, s16 model) {
    if (ship != NULL) {
        ship->unk_08 = count + 1;
        ship->unk_04 = HuMemAllocTag(ship->unk_08 * sizeof(s16), TAG_OVERLAY);
        memset(ship->unk_04, -1, ship->unk_08 * sizeof(s16));
        ship->pos.x = ship->pos.y = ship->pos.z = 0.0f;
        ship->facing.x = ship->facing.y = ship->facing.z = 0.0f;
        ship->unk_24 = radius;
        ship->unk_28 = model;
    }
}

void m217_MoverUpdate(PuddlePaddleMover *ship) {
    PuddlePaddleCollider *boat;
    s16 i;

    ship->unk_30 = 0;
    ship->unk_2A = 0;
    ship->unk_2C = 0;
    ship->unk_2E = 0;
    ship->unk_00 &= ~1;
    if (ship->unk_28 != -1) {
        ship->pos.x = Hu3DData[ship->unk_28].pos.x;
        ship->pos.y = Hu3DData[ship->unk_28].pos.y;
        ship->pos.z = Hu3DData[ship->unk_28].pos.z;
    }
    for (i = 1; i < ship->unk_08; i++) {
        if (ship->unk_04[i] != -1) {
            boat = &m217_colliderTbl[ship->unk_04[i]];
            if (!(boat->unk_00 & 1)) {
                if (boat->unk_00 & 0x400) {
                    if ((s16)m217_CylinderHitCheck(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_30 = i;
                        }
                    }
                } else if (boat->unk_00 & 0x200) {
                    if ((s16)m217_SphereHitCheck(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2E = i;
                        }
                    }
                } else if (boat->unk_00 & 0x100) {
                    if ((s16)m217_PlaneHitCheck(boat, ship) != 0) {
                        ship->unk_2A = i;
                    }
                } else {
                    if ((s16)m217_PrismHitCheck(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2C = i;
                        }
                    }
                }
            }
        }
    }
    ship->pos.x += ship->facing.x;
    ship->pos.y += ship->facing.y;
    ship->pos.z += ship->facing.z;
    if (ship->unk_28 != -1) {
        Hu3DData[ship->unk_28].pos.x = ship->pos.x;
        Hu3DData[ship->unk_28].pos.y = ship->pos.y;
        Hu3DData[ship->unk_28].pos.z = ship->pos.z;
    }
}

s32 m217_CylinderHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship) {
    f32 bounds[2];
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;
    f32 radius;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    radius = ship->unk_24;
    bounds[0] = boat->transformed[0].y - radius * 0.5f;
    bounds[1] = boat->transformed[0].y + boat->unk_C4 + radius * 0.5f;
    if (next.y < bounds[0] || next.y > bounds[1]) {
        return 0;
    } else {
        difference.x = boat->transformed[0].x - next.x;
        difference.z = boat->transformed[0].z - next.z;
        distance = HuSqrtf(difference.x * difference.x + difference.z * difference.z);
        if (distance <= ship->unk_24 + boat->unk_DC) {
            if (boat->unk_00 & 0x10) {
                return 1;
            }
            if (distance != 0.0f) {
                difference.x /= distance;
                difference.x = (ship->unk_24 + boat->unk_DC) * difference.x;
                difference.z /= distance;
                difference.z = (ship->unk_24 + boat->unk_DC) * difference.z;
            }
            next.x = boat->transformed[0].x - difference.x;
            next.z = boat->transformed[0].z - difference.z;
        } else {
            return 0;
        }
    }
    movement.x = next.x - position.x;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 m217_SphereHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship) {
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    difference.x = boat->transformed[0].x - next.x;
    difference.y = boat->transformed[0].y - next.y;
    difference.z = boat->transformed[0].z - next.z;
    distance = HuSqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
    if (distance <= ship->unk_24 + boat->unk_DC) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        if (distance != 0.0f) {
            difference.x /= distance;
            difference.x *= ship->unk_24 + boat->unk_DC;
            difference.y /= distance;
            difference.y *= ship->unk_24 + boat->unk_DC;
            difference.z /= distance;
            difference.z *= ship->unk_24 + boat->unk_DC;
        }
        next.x = boat->transformed[0].x - difference.x;
        next.y = boat->transformed[0].y - difference.y;
        next.z = boat->transformed[0].z - difference.z;
    } else {
        return 0;
    }
    movement.x = next.x - position.x;
    movement.y = next.y - position.y;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 m217_PlaneHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship) {
    Vec normal;
    Vec position;
    Vec movement;
    Vec next;
    Vec contact;
    f32 constant;
    f32 side;
    f32 distance;
    f32 radius;
    s16 result;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    constant = -boat->plane.constant;
    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * position.x + normal.y * position.y + normal.z * position.z + constant;
        if (side < 0.0f) {
            return 0;
        }
    }
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * next.x + normal.y * next.y + normal.z * next.z + constant;
        distance = m217_PlaneDistCalc(boat, &next);
        if (side > 0.0f) {
            radius = ship->unk_24;
            if (distance > 0.0f ? radius <= distance : radius <= -distance) {
                return 0;
            }
        }
    } else {
        distance = m217_PlaneDistCalc(boat, &next);
        radius = ship->unk_24;
        if (distance > 0.0f ? radius <= distance : radius <= -distance) {
            return 0;
        }
    }
    contact.x = -normal.x * distance + next.x;
    contact.y = -normal.y * distance + next.y;
    contact.z = -normal.z * distance + next.z;
    result = m217_PolyInsideCheck(boat, &contact);
    if (result != 0) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        next.x = normal.x * ship->unk_24 * 1.01f + contact.x;
        next.y = normal.y * ship->unk_24 * 1.01f + contact.y;
        next.z = normal.z * ship->unk_24 * 1.01f + contact.z;
        movement.x = next.x - position.x;
        movement.y = next.y - position.y;
        movement.z = next.z - position.z;
        ship->facing.x = movement.x;
        ship->facing.y = movement.y;
        ship->facing.z = movement.z;
    }
    return result;
}

s16 m217_PolyInsideCheck(PuddlePaddleCollider *boat, Vec *point) {
    Vec edge;
    Vec offset;
    f32 cross;
    s16 i;
    s16 next;

    switch (boat->plane.axis) {
        case 0:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.y = point->y - boat->transformed[i].y;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.y * offset.z - edge.z * offset.y;
                if (cross * boat->plane.normal.x < 0.0f) {
                    return 0;
                }
            }
            break;
        case 1:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.x = point->x - boat->transformed[i].x;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.z * offset.x - edge.x * offset.z;
                if (cross * boat->plane.normal.y < 0.0f) {
                    return 0;
                }
            }
            // The Y-axis case also checks the polygon's XY projection.
            // Fall through.
        case 2:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                offset.x = point->x - boat->transformed[i].x;
                offset.y = point->y - boat->transformed[i].y;
                cross = edge.x * offset.y - edge.y * offset.x;
                if (cross * boat->plane.normal.z < 0.0f) {
                    return 0;
                }
            }
            break;
    }
    return 1;
}

f32 m217_PlaneDistCalc(PuddlePaddleCollider *boat, Vec *point) {
    f32 x = point->x;
    f32 y = point->y;
    f32 z = point->z;
    Vec normal;
    f32 length;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    length = HuSqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    return (x * normal.x + y * normal.y + z * normal.z - boat->plane.constant) / length;
}

s32 m217_PrismHitCheck(PuddlePaddleCollider *boat, PuddlePaddleMover *ship) {
    f32 side;
    f32 edge;
    s16 i;
    s16 next;

    if (!(boat->unk_00 & 2) && ship->pos.y > boat->unk_C4) {
        return 0;
    }
    side = m217_EdgeSideCalc(ship, &boat->transformed[0], &boat->transformed[1]);
    if (side == 0.0f) {
        return 0;
    }
    if (side > 0.0f) {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = m217_EdgeSideCalc(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = m217_EdgeSideCalc(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

f32 m217_EdgeSideCalc(PuddlePaddleMover *arg0, Vec *arg1, Vec *arg2) {
    Vec pos, v1, v2;

    pos.x = arg0->pos.x;
    pos.z = arg0->pos.z;
    v1.x = arg1->x - pos.x;
    v1.z = arg1->z - pos.z;
    v2.x = arg2->x - pos.x;
    v2.z = arg2->z - pos.z;
    return v1.z * v2.x - v1.x * v2.z;
}

s32 m217_LerpCalc(f32 *outPos, u8 *tickPtr, f32 posA, f32 posB, f32 numTicks) {
    f32 frac = (f32)*tickPtr / numTicks;
    u8 tick;

    *outPos = posA + ((posB - posA) * frac);
    tick = *tickPtr + 1;
    *tickPtr = tick;
    if (numTicks < tick) {
        *tickPtr = 0;
        *outPos = posB;
        return 1;
    }
    return 0;
}

f32 m217_BezierCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 t = arg0;
    f32 a;

    if (1.0f < t) {
        t = 1.0f;
    }
    a = 1.0f - t;
    return a * a * arg1 + (a + a) * t * arg2 + t * t * arg3;
}

void m217_RandPermCreate(u16 *order, s16 count) {
    s16 i;
    s16 index;
    s32 random;
    u16 temp;

    for (i = 0; i < count; i++) {
        order[i] = i;
    }
    for (i = count - 1; i >= 0; i--) {
        random = rand16();
        index = random % (i + 1);
        temp = order[i];
        order[i] = order[index];
        order[index] = temp;
    }
}

void m217_MdlSync(omObjData *object) {
    HmfModel *model = &Hu3DData[object->model[0]];

    object->scale.x = model->scale.x;
    object->scale.y = model->scale.y;
    object->scale.z = model->scale.z;
    object->trans.x = model->pos.x;
    object->trans.y = model->pos.y;
    object->trans.z = model->pos.z;
    if (model->rot.x >= 360.0f) {
        model->rot.x -= 360.0f;
    }
    if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    }
    if (model->rot.z >= 360.0f) {
        model->rot.z -= 360.0f;
    }
    if (model->rot.z < 0.0f) {
        model->rot.z += 360.0f;
    }
    object->rot.x = model->rot.x;
    object->rot.y = model->rot.y;
    object->rot.z = model->rot.z;
}

void m217_PlaneCalc(Vec *vertices, PuddlePaddlePlane *plane) {
    f32 firstX, firstY, firstZ, secondX, secondY, secondZ;
    f32 normal[3];
    f32 length;
    f32 magnitude;
    s16 axis, i;

    firstX = vertices[1].x - vertices[0].x;
    firstY = vertices[1].y - vertices[0].y;
    firstZ = vertices[1].z - vertices[0].z;
    secondX = vertices[2].x - vertices[0].x;
    secondY = vertices[2].y - vertices[0].y;
    secondZ = vertices[2].z - vertices[0].z;
    normal[0] = firstY * secondZ - firstZ * secondY;
    normal[1] = firstZ * secondX - firstX * secondZ;
    normal[2] = firstX * secondY - firstY * secondX;
    length = HuSqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length != 0.0f) {
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
    }
    plane->constant = normal[0] * vertices[0].x + normal[1] * vertices[0].y + normal[2] * vertices[0].z;
    axis = 0;
    for (i = 1; i < 3; i++) {
        magnitude = normal[axis] > 0.0f ? normal[axis] : -normal[axis];
        if (normal[i] > 0.0f ? magnitude < normal[i] : magnitude < -normal[i]) {
            axis = i;
        }
    }
    plane->normal.x = normal[0];
    plane->normal.y = normal[1];
    plane->normal.z = normal[2];
    plane->axis = axis;
}

void m217_PitchYawCalc(Vec from, Vec to, f32 *angles) {
    Vec difference;
    f32 angle;
    f32 fullRotation = 360.0f;

    difference.x = to.x - from.x;
    difference.y = to.y - from.y;
    difference.z = to.z - from.z;
    angle = atan2df(difference.y, sqrtf(difference.x * difference.x + difference.z * difference.z));
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles++ = angle;
    angle = atan2df(difference.x, difference.z);
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles = angle;
}

void m217_AngleDiffMinimize(f32 *angle, f32 *target) {
    f32 difference;

    while (*target < 0.0f) {
        *target += 360.0f;
    }
    while (*target >= 360.0f) {
        *target -= 360.0f;
    }
    while (*angle < 0.0f) {
        *angle += 360.0f;
    }
    while (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
    difference = *target - *angle;
    if (!(difference > 0.0f)) {
        difference = -difference;
    }
    if (difference > 180.0f) {
        if (*angle < *target) {
            *target -= 360.0f;
        } else {
            *angle -= 360.0f;
        }
    }
}

void m217_MtxIdentSet(f32 *mtx) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mtx[i * 4 + j] = 0.0f;
        }
        mtx[i * 4 + i] = 1.0f;
    }
}

void m217_MtxTransSet(f32 *matrix, f32 x, f32 y, f32 z) {
    m217_MtxIdentSet(matrix);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void m217_MtxRotXSet(f32 *matrix, f32 angle) {
    m217_MtxIdentSet(matrix);
    matrix[5] = cosdf(angle);
    matrix[6] = sindf(angle);
    matrix[9] = -sindf(angle);
    matrix[10] = cosdf(angle);
}

void m217_MtxRotYSet(f32 *matrix, f32 angle) {
    m217_MtxIdentSet(matrix);
    matrix[0] = cosdf(angle);
    matrix[2] = -sindf(angle);
    matrix[8] = sindf(angle);
    matrix[10] = cosdf(angle);
}

void m217_MtxMul(f32 *left, f32 *right, f32 *output) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            output[i * 4 + j] = left[i * 4] * right[j] + left[i * 4 + 1] * right[4 + j] +
                                left[i * 4 + 2] * right[8 + j] + left[i * 4 + 3] * right[12 + j];
        }
    }
}

void m217_MtxTransCalc(f32 *matrix, f32 *output) {
    *output++ = matrix[12] * matrix[0] + matrix[13] * matrix[4] + matrix[14] * matrix[8];
    *output++ = matrix[12] * matrix[1] + matrix[13] * matrix[5] + matrix[14] * matrix[9];
    *output = matrix[12] * matrix[2] + matrix[13] * matrix[6] + matrix[14] * matrix[10];
}

void m217_MtxTransformSet(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 *matrix) {
    f32 translation[16];
    f32 rotationX[16];
    f32 rotationY[16];
    f32 rotation[16];

    m217_MtxTransSet(translation, x, y, z);
    m217_MtxRotXSet(rotationX, rx);
    m217_MtxRotYSet(rotationY, ry);
    m217_MtxMul(rotationX, rotationY, rotation);
    m217_MtxMul(rotation, translation, matrix);
}

void m217_VtxTransform(Vec *vertices, s16 count, f32 *matrix, Vec *output) {
    s16 i;

    for (i = 0; i < count; i++) {
        output[i].x = (matrix[12] + vertices[i].x) * matrix[0] +
                      (matrix[13] + vertices[i].y) * matrix[4] +
                      (matrix[14] + vertices[i].z) * matrix[8];
        output[i].y = (matrix[12] + vertices[i].x) * matrix[1] +
                      (matrix[13] + vertices[i].y) * matrix[5] +
                      (matrix[14] + vertices[i].z) * matrix[9];
        output[i].z = (matrix[12] + vertices[i].x) * matrix[2] +
                      (matrix[13] + vertices[i].y) * matrix[6] +
                      (matrix[14] + vertices[i].z) * matrix[10];
    }
}
