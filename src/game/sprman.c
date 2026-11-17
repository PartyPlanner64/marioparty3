#include "game/sprite.h"
#include "game/hu3d.h"
#include "game/camera.h"
#include "game/mallocblock.h"
#include "include_asm.h"
#include "macros.h"
#include "game/profiler.h"
#include "game/malloc.h"

#define HUSPR_READ16(p) (((p)[0] << 8) + (p)[1])
#define HUSPR_READ32(p) (((p)[0] << 24) + ((p)[1] << 16) + ((p)[2] << 8) + (p)[3])

typedef struct {
    u8 images[4];
    u8 animations[4];
    u8 pixels[4];
    u8 palette[4];
    u8 imageCount[2];
    u8 animationCount[2];
    u8 width[2];
    u8 height[2];
    u8 pixelBits[2];
    u8 paletteCount;
} HuSprFileHeader;

typedef struct {
    u8 pixels[4];
    u8 width[2];
    u8 height[2];
    u8 centerX[2];
    u8 centerY[2];
} HuSprFileImage;

typedef struct {
    u8 image[2];
    u8 duration[2];
    u8 shiftX;
    u8 shiftY;
    u8 flip;
} HuSprFileFrame;

typedef struct {
    HuSprite *last;
    HuSprite *first;
} HuSprPrioBucket;


f64 fmod(f64 x, f64 y);

static Vp HuSprViewport = {
    { { 640, 480, 511, 0 }, { 640, 480, 511, 0 } },
};
static s32 HuSprOrderDirtyF = 0; // redraw?
static Mtx HuSprOrthoMtx;
static Gfx *HuSprFGList;
static HuSprite *HuSprOrderTop; // head of sorted draw list
static f32 HuSpr3DScale;
extern Gfx *HuSprTileBuf;
extern s16 HuSprLayerHookMdl;
extern s16 Hu3DCamMtxNo;
extern HuSprAnmDesc *HuSprPalAnimData[0x100];
extern u16 HuSprPalAnimNum;
extern u16 HuSprAnimNum;
extern u16 HuSprOrderNum;
extern HuSprAnimData *HuSprAnimTbl[];
extern void *HuSprGfxBuf[3];
extern u8 Hu3DBufNo;
extern s32 HuSprGfxBufSize;
extern void *HuSprVtxPos;
extern s8 Hu3DPauseF;
extern HuSprGrp *HuSprGrpLast;
extern HuSprGrp *HuSprGrpFirst;
extern HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX];
extern u16 HuSprGrpNum;

void HuSprInit(void) {
    s16 i;
    void **p;

    HuSprGrpNum = 0;
    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        HuSprGrpData[i] = NULL;
    }
    HuSprGrpFirst = NULL;
    HuSprGrpLast = NULL;
    HuSprOrderNum = 0;
    HuSprGfxBuf[0] =
        HuSprGfxBuf[1] =
            HuSprGfxBuf[2] =
                HuSprVtxPos = NULL;
    HuSprGfxBufSize = NULL;
    guOrtho(&HuSprOrthoMtx, -160.0f, 160.0f, -120.0f, 120.0f, 0.0f, 8000.0f, 2.0f);
    HuSprLayerHookMdl = Hu3DHookFuncCreate(0, HuSprLayerHook, 0);
    Hu3DModelCameraSet(HuSprLayerHookMdl, HU3D_CAM0);
    HuSprFGHookMdl = Hu3DHookFuncCreate(0, HuSprFGHook, 6);
    HuSprAnimInit();
    HuSprPalAnimInit();
    HuSprOrderDirtyF = 1;
}

HuSprGrp *HuSprGrpAlloc(s16 arg0, u16 arg1) {
    HuSprGrp *temp_v0;

    // Allocation assumes 'members' is the last member of HuSprGrp.
    temp_v0 = HuMemAlloc(offsetof(HuSprGrp, members) + arg0 * sizeof(*temp_v0->members));
    if (temp_v0 == NULL) {
        return NULL;
    }
    temp_v0->unk_08 = arg1;
    temp_v0->unk_0A = arg0;
    if (HuSprGrpLast == NULL) {
        HuSprGrpLast = temp_v0;
    }
    temp_v0->next = HuSprGrpFirst;
    if (temp_v0->next != NULL) {
        temp_v0->next->prev = temp_v0;
    }
    temp_v0->prev = NULL;
    HuSprGrpFirst = temp_v0;
    HuSprGrpNum++;
    HuSprOrderDirtyF = 1;
    return temp_v0;
}

void HuSprMemberDataFree(HuSprite *arg0) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (arg0->unk_128[i] != NULL) {
            HuMemDelayFree(arg0->unk_128[i]);
        }
        if (arg0->unk_134[i] != NULL) {
            HuMemDelayFree(arg0->unk_134[i]);
        }
        if (arg0->unk_98.unk70[i] != NULL) {
            HuMemDelayFree(arg0->unk_98.unk70[i]);
        }
    }
    HuMemDelayFree(arg0);
}

void HuSprGrpKill(s16 arg0) {
    HuSprGrp *group = HuSprGrpData[arg0];
    HuSprGrp *next = group->next;
    HuSprGrp *prev = group->prev;

    if (group->members[0] != NULL) {
        s16 i;
        HuSprite **mp = group->members;

        for (i = 0; i < group->unk_0A; i++) {
            HuSprMemberDataFree(*mp++);
        }
    }
    if (next != NULL) {
        next->prev = prev;
    }
    if (prev != NULL) {
        prev->next = next;
    }
    if (HuSprGrpLast == group) {
        HuSprGrpLast = prev;
        if (prev != NULL) {
            prev->next = NULL;
        }
    }
    if (HuSprGrpFirst == group) {
        HuSprGrpFirst = next;
        if (next != NULL) {
            next->prev = NULL;
        }
    }
    HuMemFree(group);
    HuSprGrpData[arg0] = NULL;
    HuSprGrpNum--;
    HuSprOrderDirtyF = 1;
}

void HuSprGrpAllKill(void) {
    s16 i;

    HuSprGrpNum = 0;
    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] != NULL) {
            HuSprGrpKill(i);
        }
    }
    HuSprGrpFirst = NULL;
    HuSprGrpLast = NULL;
    HuSprOrderNum = 0;
    HuSprOrderDirtyF = 1;
}

s16 HuSprGrpCreate(u16 arg0, u16 arg1) {
    HuSprGrp *temp_v0_2;
    HuSprite **var_s2;
    HuSprite *temp_v0_3;
    s16 var_s4;
    s16 i;

    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] == NULL) {
            break;
        }
    }
    if (i == HUSPR_GRP_MAX) {
        return -1;
    }
    var_s4 = i;
    temp_v0_2 = HuSprGrpAlloc(arg0, arg1);
    if (temp_v0_2 == NULL) {
        return -1;
    }
    HuSprGrpData[var_s4] = temp_v0_2;
    temp_v0_2->unk_0A = 0;
    temp_v0_2->dirty = 1;
    var_s2 = temp_v0_2->members;
    for (i = 0; i < arg0; i++) {
        *(var_s2++) = temp_v0_3 = HuMemAlloc(0x210);
        if (temp_v0_3 == NULL) {
            HuSprGrpKill(var_s4);
            return -1;
        }
        temp_v0_2->unk_0A++;
    }
    HuSprGrpMemberInit(temp_v0_2, arg0);
    return var_s4;
}

s32 HuSprGrpMemberKill(s16 group, s16 member, u16 count) {
    HuSprGrp *groupPtr = HuSprGrpData[group];
    HuSprite **mp = &groupPtr->members[member];
    HuSprite *sprite;
    s16 i;

    for (i = 0; i < count; i++) {
        HuSprMemberDataFree(*mp++);
    }
    groupPtr->unk_0A -= count;
    if (groupPtr->unk_0A == 0) {
        groupPtr->members[0] = NULL;
        HuSprGrpKill(group);
        return 0;
    }
    HuMemMemoryReallocPerm(groupPtr, offsetof(HuSprGrp, members) + groupPtr->unk_0A * sizeof(*groupPtr->members));
    mp = &groupPtr->members[member];
    for (i = 0; i < groupPtr->unk_0A - member; i++) {
        *mp = mp[count];
        mp++;
    }
    for (i = 0; i < groupPtr->unk_0A; i++) {
        sprite = groupPtr->members[i];
        sprite->unk_00 = i;
        sprite->unk_02 = groupPtr->unk_0A;
    }
    return 0;
}

s32 HuSprGrpMemberInsert(s16 group, s16 member, u16 count) {
    HuSprGrp *oldGroup = HuSprGrpData[group];
    HuSprGrp *newGroup;
    HuSprite **mp;
    HuSprite *sprite;
    s16 newSlot;
    s16 i;

    for (i = 0; i < HUSPR_GRP_MAX; i++) {
        if (HuSprGrpData[i] == NULL) {
            break;
        }
    }
    if (i == HUSPR_GRP_MAX) {
        return -1;
    }
    newSlot = i;
    newGroup = HuSprGrpAlloc(count + oldGroup->unk_0A, oldGroup->unk_08);
    if (newGroup == NULL) {
        return -1;
    }
    HuSprGrpData[newSlot] = newGroup;
    newGroup->unk_0A = 0;
    newGroup->dirty = 1;
    mp = newGroup->members;
    for (i = 0; i < count; i++) {
        *(mp++) = sprite = HuMemAlloc(0x210);
        if (sprite == NULL) {
            HuSprGrpKill(newSlot);
            return -1;
        }
        newGroup->unk_0A++;
    }
    HuSprGrpMemberInit(newGroup, count);
    newGroup->members[0]->unk_2E = 0;
    if (member >= 0) {
        mp = newGroup->members + count - 1;
        for (i = 0; i < count; i++) {
            mp[member + 1] = *mp;
            mp--;
        }
        mp = newGroup->members;
        for (i = 0; i < member + 1; i++) {
            *(mp++) = oldGroup->members[i];
        }
    }
    mp = &newGroup->members[member] + count + 1;
    for (i = 0; i < oldGroup->unk_0A - (member + 1); i++) {
        *(mp++) = (oldGroup->members + member)[i + 1];
    }
    newGroup->unk_0A = count + oldGroup->unk_0A;
    for (i = 0; i < newGroup->unk_0A; i++) {
        HuSprite *member_sprite = newGroup->members[i];

        member_sprite->unk_00 = i;
        member_sprite->unk_02 = newGroup->unk_0A;
    }
    oldGroup->members[0] = NULL;
    HuSprGrpKill(group);
    HuSprGrpData[group] = newGroup;
    HuSprGrpData[newSlot] = NULL;
    return 0;
}

void HuSprAnmInit(HuSprAnm *arg0) {
    arg0->data = NULL;
    arg0->animStat = 0;
    arg0->animMode = 0;
    arg0->bank = 0;
    arg0->animNo = 0;
    arg0->time = 0.0f;
    arg0->speed = 1.0f;
    arg0->patNo = 0;
    arg0->flip = 0;
    arg0->shiftY = 0;
    arg0->shiftX = 0;
}

void HuSprAnmSync(HuSprite *arg0) {
    arg0->anim.data = arg0->data;
    arg0->anim.animStat = arg0->animStat;
    arg0->anim.animMode = arg0->animMode;
    arg0->anim.animNo = arg0->animNo;
    arg0->anim.bank = arg0->bank;
    arg0->anim.time = arg0->time;
    arg0->anim.speed = arg0->speed;
    arg0->anim.flip = arg0->flip;
    arg0->anim.patNo = arg0->patNo;
    arg0->anim.shiftY = 0;
    arg0->anim.shiftX = 0;
}

void HuSprGrpMemberInit(HuSprGrp *group, u16 count) {
    HuSprite *sprite;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++) {
        sprite = group->members[i];
        sprite->unk_04 = 0;
        sprite->unk_08 = 0;
        sprite->unk_18 = sprite->unk_1C = 1.0f;
        sprite->prio = 0x8000;
        sprite->unk_20 = 0;
        sprite->dispAttr = 0;
        sprite->color[0] = sprite->color[1] = sprite->color[2] = 0;
        sprite->tpLvl = 0x100;
        if (i != 0) {
            sprite->unk_2E = 0;
        } else {
            sprite->unk_2E = -1;
        }
        sprite->unk_30.f = sprite->unk_34.f = 1.0f;
        sprite->unk_38 = sprite->unk_3A = 0;
        sprite->unk_3C = sprite->unk_3E = sprite->unk_40 = sprite->unk_42 = 0;
        sprite->unk_44 = 0;
        sprite->unk_116 = sprite->unk_114 = -1;
        sprite->pos.x = 0.0f;
        sprite->pos.y = 0.0f;
        sprite->scale.x = sprite->scale.y = 1.0f;
        sprite->zRot = 0.0f;
        sprite->attr = 0;
        sprite->unk_60 = sprite->unk_64 = 1.0f;
        HuSprAnmInit(&sprite->anim);
        sprite->data = sprite->anim.data;
        sprite->animStat = sprite->anim.animStat;
        sprite->animMode = (u16)sprite->anim.animMode;
        sprite->bank = (u16)sprite->anim.bank;
        sprite->time = sprite->anim.time;
        sprite->speed = sprite->anim.speed;
        sprite->patNo = (u16)sprite->anim.patNo;
        sprite->flip = sprite->anim.flip;
        sprite->shiftX = sprite->anim.shiftX;
        sprite->shiftY = sprite->anim.shiftY;
        sprite->unk_98.unk00 = NULL;
        sprite->unk_98.unk64.f = 1.0f;
        for (j = 0; j < 0x10; j++) {
            sprite->unk_98.unk04[j] = 0xFFFF;
            sprite->unk_98.unk24[j] = 0.0f;
        }
        sprite->unk_98.unk68 = 0;
        sprite->unk_98.unk6C = NULL;
        sprite->unk_98.unk70[0] = sprite->unk_98.unk70[1] = sprite->unk_98.unk70[2] = NULL;
        sprite->unk_00 = i;
        sprite->unk_02 = count;
        sprite->unk_118 = sprite->unk_11C = NULL;
        sprite->unk_128[0] = sprite->unk_128[1] = sprite->unk_128[2] = NULL;
        sprite->unk_134[0] = sprite->unk_134[1] = sprite->unk_134[2] = NULL;
        HuMtxIdent(&sprite->unk_140[0]);
        HuMtxIdent(&sprite->unk_140[1]);
        HuMtxIdent(&sprite->unk_140[2]);
        sprite->unk_120 = 0;
        sprite->unk_124 = NULL;
        sprite->scissorX = sprite->scissorY = 0;
        sprite->scissorX2 = 0x140;
        sprite->scissorY2 = 0xF0;
    }
}

// rebuild sprite draw list (highest priority first)
HuSprite *HuSprPrioSort(void) {
    HuSprPrioBucket buckets[0x100];
    HuSprGrp *group;
    HuSprite *sprite;
    HuSprite *last;
    s32 i;
    s32 j;
    s32 bucket;
    s32 minBucket = -1;
    s32 maxBucket = 0;
    HuSprite *node = NULL;

    if (HuSprOrderDirtyF == 0) {
        return HuSprOrderTop;
    }
    HuSprOrderDirtyF = 0;
    HuSprOrderNum = 0;
    group = HuSprGrpLast;
    bzero(buckets, sizeof(buckets));
    while (group != NULL) {
        for (i = 0; i < group->unk_0A; i++) {
            sprite = group->members[i];
            sprite->unk_11C = NULL;
            sprite->unk_118 = NULL;
        }
        group = group->prev;
    }
    for (group = HuSprGrpLast; group != NULL; group = group->prev) {
        for (i = 0; i < group->unk_0A; i++) {
            sprite = group->members[i];
            if (sprite->dispAttr & HUSPR_ATTR_DISPOFF) {
                continue;
            }
            bucket = sprite->prio >> 8;
            if (minBucket < 0) {
                maxBucket = bucket;
                minBucket = maxBucket;
                buckets[maxBucket].first = sprite;
                buckets[maxBucket].last = sprite;
            } else {
                if (maxBucket < bucket) {
                    node = buckets[maxBucket].first;
                } else {
                    for (j = bucket; j < maxBucket + 1; j++) {
                        node = buckets[j].first;
                        if (node != NULL && sprite->prio <= node->prio) {
                            last = buckets[j].last;
                            if (last != NULL && sprite->prio <= last->prio) {
                                node = last;
                            }
                            break;
                        }
                    }
                    if (j == maxBucket + 1) {
                        node = buckets[maxBucket].first;
                    }
                }
                while (node != NULL) {
                    if (sprite->prio > node->prio) {
                        break;
                    }
                    node = node->unk_118;
                }
                if (node != NULL) {
                    sprite->unk_118 = node;
                    sprite->unk_11C = node->unk_11C;
                    if (node->unk_11C != NULL) {
                        node->unk_11C->unk_118 = sprite;
                    }
                    node->unk_11C = sprite;
                } else {
                    sprite->unk_118 = NULL;
                    sprite->unk_11C = buckets[minBucket].last;
                    buckets[minBucket].last->unk_118 = sprite;
                }
                if (buckets[bucket].last == NULL || sprite->prio <= buckets[bucket].last->prio) {
                    buckets[bucket].last = sprite;
                }
                if (buckets[bucket].first == NULL || sprite->prio > buckets[bucket].first->prio) {
                    buckets[bucket].first = sprite;
                }
                if (bucket < minBucket) {
                    minBucket = bucket;
                }
                if (maxBucket < bucket) {
                    maxBucket = bucket;
                }
            }
            HuSprOrderNum++;
        }
    }
    HuSprOrderTop = buckets[maxBucket].first;
    return buckets[maxBucket].first;
}

s16 HuSprGrpRootCount(HuSprGrp *arg0) {
    HuSprite *sprite;
    s16 result = 0;
    s16 i;
    s16 j;

    for (j = 0; j < arg0->unk_0A; j++) {
        sprite = arg0->members[j];
        sprite->unk_116 = -1;
        sprite->unk_114 = -1;
    }
    for (i = 0; i < arg0->unk_0A; i++) {
        sprite = arg0->members[i];

        if (sprite->unk_2E >= 0) {
            HuSprite *parent = arg0->members[sprite->unk_2E];

            if (parent->unk_116 < 0) {
                parent->unk_116 = i;
            } else {
                for (j = 0; j < i; j++) {
                    HuSprite *other = arg0->members[j];

                    if (j != i && sprite->unk_2E == other->unk_2E && other->unk_114 < 0) {
                        other->unk_114 = i;
                        break;
                    }
                }
            }
        } else {
            result = i;
        }
    }
    return result;
}

void HuSprMtxCat(f32 a0[][2], f32 a1[][2], f32 a2[][2]) {
    s16 i;

    for (i = 0; i < 3; i++) {
        a2[i][0] = a0[i][0] * a1[0][0] + a0[i][1] * a1[1][0];
        a2[i][1] = a0[i][0] * a1[0][1] + a0[i][1] * a1[1][1];
    }
    a2[2][0] += a1[2][0];
    a2[2][1] += a1[2][1];
}

// Updates all sprite groups, resolving parent-relative positions and
// rotations by walking each group's sprite hierarchy.
// The traversal stack depth wraps at 8 bits.
void HuSprExec(void) {
    f32 mtx[0x100][3][2];
    f32 parentMtx[3][2];
    f32 localMtx[3][2];
    u16 stack[0x100];
    HuSprGrp *group;
    HuSprite *sprite;
    HuSprite *parent;
    s32 cur;
    s32 n;
    u16 depth = 0;
    f32 angle;

    for (group = HuSprGrpLast; group != NULL; group = group->prev) {
        if (group->dirty) {
            group->dirty = 0;
            switch (group->unk_08) {
                case 0:
                    for (cur = 0; cur < group->unk_0A; cur++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        sprite->unk_04 = sprite->shiftX + sprite->pos.x;
                        sprite->unk_08 = sprite->shiftY + sprite->pos.y;
                        sprite->unk_20 = sprite->zRot;
                        HuSprTexLoad(sprite);
                    }
                    break;
                case 1:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        if (sprite->unk_2E < 0) {
                            sprite->unk_04 = sprite->shiftX + sprite->pos.x;
                            sprite->unk_08 = sprite->shiftY + sprite->pos.y;
                            sprite->unk_20 = sprite->zRot;
                        } else {
                            parent = group->members[sprite->unk_2E];
                            sprite->unk_04 = sprite->shiftX + sprite->pos.x;
                            sprite->unk_08 = sprite->shiftY + sprite->pos.y;
                            sprite->unk_20 = parent->unk_20 + sprite->zRot;
                        }
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
                case 2:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        if (sprite->unk_2E < 0) {
                            sprite->unk_04 = sprite->shiftX + sprite->pos.x;
                            sprite->unk_08 = sprite->shiftY + sprite->pos.y;
                        } else {
                            parent = group->members[sprite->unk_2E];
                            sprite->unk_04 = (sprite->shiftX + sprite->pos.x) * sprite->unk_18 + parent->unk_04;
                            sprite->unk_08 = (sprite->shiftY + sprite->pos.y) * sprite->unk_1C + parent->unk_08;
                        }
                        sprite->unk_20 = sprite->zRot;
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
                case 3:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        if (sprite->unk_2E < 0) {
                            sprite->unk_04 = sprite->shiftX + sprite->pos.x;
                            sprite->unk_08 = sprite->shiftY + sprite->pos.y;
                            sprite->unk_20 = sprite->zRot;
                        } else {
                            parent = group->members[sprite->unk_2E];
                            sprite->unk_04 = (sprite->shiftX + sprite->pos.x) * sprite->unk_18 + parent->unk_04;
                            sprite->unk_08 = (sprite->shiftY + sprite->pos.y) * sprite->unk_1C + parent->unk_08;
                            sprite->unk_20 = parent->unk_20 + sprite->zRot;
                        }
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
                case 4:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        if (sprite->unk_2E < 0) {
                            parentMtx[0][0] = parentMtx[1][1] = 1.0f;
                            parentMtx[0][1] = parentMtx[1][0] = 0.0f;
                            parentMtx[2][0] = sprite->shiftX + sprite->pos.x;
                            parentMtx[2][1] = sprite->shiftY + sprite->pos.y;
                            sprite->unk_04 = sprite->pos.x;
                            sprite->unk_08 = sprite->pos.y;
                        } else {
                            localMtx[0][0] = localMtx[1][1] = 1.0f;
                            localMtx[0][1] = localMtx[1][0] = 0.0f;
                            localMtx[2][0] = (sprite->shiftX + sprite->pos.x) * sprite->unk_18;
                            localMtx[2][1] = (sprite->shiftY + sprite->pos.y) * sprite->unk_1C;
                            HuSprMtxCat(localMtx, mtx[sprite->unk_2E], parentMtx);
                            sprite->unk_04 = (s16)parentMtx[2][0];
                            sprite->unk_08 = (s16)parentMtx[2][1];
                        }
                        sprite->unk_20 = sprite->zRot;
                        angle = -sprite->zRot * (3.141592654 / 180.0);
                        localMtx[0][0] = localMtx[1][1] = cosf(angle);
                        localMtx[0][1] = sinf(angle);
                        localMtx[1][0] = -localMtx[0][1];
                        localMtx[2][0] = localMtx[2][1] = 0.0f;
                        HuSprMtxCat(localMtx, parentMtx, mtx[sprite->unk_00]);
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
                case 5:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        if (sprite->unk_2E < 0) {
                            parentMtx[0][0] = parentMtx[1][1] = 1.0f;
                            parentMtx[0][1] = parentMtx[1][0] = 0.0f;
                            parentMtx[2][0] = sprite->shiftX + sprite->pos.x;
                            parentMtx[2][1] = sprite->shiftY + sprite->pos.y;
                            sprite->unk_04 = sprite->pos.x;
                            sprite->unk_08 = sprite->pos.y;
                            sprite->unk_20 = sprite->zRot;
                        } else {
                            parent = group->members[sprite->unk_2E];
                            localMtx[0][0] = localMtx[1][1] = 1.0f;
                            localMtx[0][1] = localMtx[1][0] = 0.0f;
                            localMtx[2][0] = (sprite->shiftX + sprite->pos.x) * sprite->unk_18;
                            localMtx[2][1] = (sprite->shiftY + sprite->pos.y) * sprite->unk_1C;
                            HuSprMtxCat(localMtx, mtx[sprite->unk_2E], parentMtx);
                            sprite->unk_04 = (s16)parentMtx[2][0];
                            sprite->unk_08 = (s16)parentMtx[2][1];
                            sprite->unk_20 = parent->unk_20 + sprite->zRot;
                        }
                        angle = -sprite->zRot * (3.141592654 / 180.0);
                        localMtx[0][0] = localMtx[1][1] = cosf(angle);
                        localMtx[0][1] = sinf(angle);
                        localMtx[1][0] = -localMtx[0][1];
                        localMtx[2][0] = localMtx[2][1] = 0.0f;
                        HuSprMtxCat(localMtx, parentMtx, mtx[sprite->unk_00]);
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
            }
        } else {
            switch (group->unk_08) {
                case 0:
                    for (cur = 0; cur < group->unk_0A; cur++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        HuSprTexLoad(sprite);
                    }
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    cur = HuSprGrpRootCount(group);
                    for (n = 0; n < group->unk_0A; n++) {
                        sprite = group->members[cur];
                        HuSprAnimExec(sprite);
                        HuSprTexLoad(sprite);
                        if (sprite->unk_116 >= 0) {
                            stack[depth++] = cur;
                            depth = (u8)depth;
                            cur = sprite->unk_116;
                        } else {
                            while (sprite->unk_114 < 0 && depth != 0) {
                                depth--;
                                cur = stack[depth];
                                depth &= 0xFF;
                                sprite = group->members[cur];
                            }
                            cur = sprite->unk_114;
                        }
                    }
                    break;
            }
        }
    }
}

void HuSprGfxBufAlloc(void) {
    if (HuSprGfxBuf[Hu3DBufNo] != NULL) {
        HuMemFree(HuSprGfxBuf[Hu3DBufNo]);
    }
    if (HuSprGfxBufSize != NULL) {
        HuSprGfxBuf[Hu3DBufNo] = HuMemAlloc(HuSprGfxBufSize);
    } else {
        HuSprGfxBuf[Hu3DBufNo] = NULL;
    }
    HuSprVtxPos = HuSprGfxBuf[Hu3DBufNo];
}

// Model draw callback that builds the display list for all sprites. It is
// drawn before 3D models, so HUSPR_ATTR_BG sprites are drawn here. Sprites
// without HUSPR_ATTR_BG are linked into a separate list (HuSprFGList) and
// branched over here, so that HuSprFGHook can draw them over everything later.
void HuSprLayerHook(Gfx **gdl, s32 arg1, s32 arg2) {
    HuCamMtxs *mtxs;
    HuCamera *cam;
    HuSprite *sprite;
    s16 inSeparate = FALSE;
    Gfx *separateBranch = NULL;
    Gfx *mainBranch = NULL;
    s16 sample;

    HuSprGfxBufSize = 0;
    sample = HuProfCpuBegin(0, 200, 0);
    HuSprExec();
    HuProfCpuEnd(sample);
    sprite = HuSprPrioSort();
    HuSprGfxBufAlloc();
    HuSprTileBuf = HuMemAlloc(0x4000);
    sample = HuProfCpuBegin(0, 0, 200);
    gSPViewport((*gdl)++, &HuSprViewport);
    gSPPerspNormalize((*gdl)++, 0x8000);
    gSPMatrix((*gdl)++, osVirtualToPhysical(&HuSprOrthoMtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetScissor((*gdl)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync((*gdl)++);
    gDPSetTexturePersp((*gdl)++, G_TP_NONE);
    gSPTexture((*gdl)++, 0xFFFF, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode((*gdl)++, G_CULL_BOTH);
    gSPSetGeometryMode((*gdl)++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetBlendColor((*gdl)++, 0, 0, 0, 1);
    gDPSetAlphaCompare((*gdl)++, G_AC_THRESHOLD);
    HuSprFGList = NULL;
    for (; sprite != NULL; sprite = sprite->unk_118) {
        if (sprite->dispAttr & HUSPR_ATTR_BG) {
            if (inSeparate) {
                if (separateBranch != NULL) {
                    gSPBranchList(separateBranch, *gdl + 1);
                }
                mainBranch = (*gdl)++;
            }
            inSeparate = FALSE;
        } else {
            if (!inSeparate) {
                if (mainBranch != NULL) {
                    gSPBranchList(mainBranch, *gdl + 1);
                }
                separateBranch = (*gdl)++;
                if (HuSprFGList == NULL) {
                    HuSprFGList = *gdl;
                }
            }
            inSeparate = TRUE;
        }
        HuSprDisp(gdl, sprite, arg2);
    }
    if (inSeparate) {
        gSPEndDisplayList((*gdl)++);
        if (separateBranch != NULL) {
            gSPBranchList(separateBranch, *gdl);
        }
    } else if (HuSprFGList != NULL) {
        gSPEndDisplayList(mainBranch);
    }
    gDPSetTextureLUT((*gdl)++, G_TT_NONE);
    HuMemFree(HuSprTileBuf);
    mtxs = (HuCamMtxs *)arg1;
    cam = (HuCamera *)arg2;
    gSPMatrix((*gdl)++, &mtxs->perspMtx, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix((*gdl)++, &mtxs->lookAtMtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetScissor((*gdl)++, G_SC_NON_INTERLACE, cam->screenLeft, cam->screenTop, cam->screenRight, cam->screenBottom);
    HuProfCpuEnd(sample);
}

// Model draw callback that renders the sprite display list for a camera.
void HuSprFGHook(Gfx **gdl, s32 arg1, s32 arg2) {
    HuCamMtxs *mtxs = (HuCamMtxs *)arg1;
    HuCamera *cam = (HuCamera *)arg2;

    if (HuSprFGList == NULL) {
        return;
    }
    gSPViewport((*gdl)++, &HuSprViewport);
    gSPPerspNormalize((*gdl)++, 0x8000);
    gSPMatrix((*gdl)++, osVirtualToPhysical(&HuSprOrthoMtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetScissor((*gdl)++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync((*gdl)++);
    gDPSetTexturePersp((*gdl)++, G_TP_NONE);
    gSPTexture((*gdl)++, 0xFFFF, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode((*gdl)++, G_CULL_BOTH);
    gSPSetGeometryMode((*gdl)++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetBlendColor((*gdl)++, 0, 0, 0, 1);
    gDPSetAlphaCompare((*gdl)++, G_AC_THRESHOLD);
    gSPDisplayList((*gdl)++, HuSprFGList);
    gDPSetTextureLUT((*gdl)++, G_TT_NONE);
    gSPMatrix((*gdl)++, &mtxs->perspMtx, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix((*gdl)++, &mtxs->lookAtMtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetScissor((*gdl)++, G_SC_NON_INTERLACE, cam->screenLeft, cam->screenTop, cam->screenRight, cam->screenBottom);
}

void HuSprPosSet(s16 group, s16 member, s16 arg2, s16 arg3) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if ((sprite_ptr->pos.x != arg2) || (sprite_ptr->pos.y != arg3)) {
        group_ptr->dirty = 1;
        sprite_ptr->pos.x = arg2;
        sprite_ptr->pos.y = arg3;
    }
}

void HuSprPrimDepthSet(s16 group, s16 member, s16 arg2) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_44 = arg2;
}

// Transforms a point by a fixed-point matrix.
void HuSprMtxXformVec4(Mtx *m, f32 x, f32 y, f32 z, f32 w, f32 *ox, f32 *oy, f32 *oz, f32 *ow) {
    HuMtx4F mf;

    HuMtxL2F(mf, m);
    *ox = x * mf[0][0] + y * mf[1][0] + z * mf[2][0] + mf[3][0];
    *oy = x * mf[0][1] + y * mf[1][1] + z * mf[2][1] + mf[3][1];
    *oz = x * mf[0][2] + y * mf[1][2] + z * mf[2][2] + mf[3][2];
    *ow = x * mf[0][3] + y * mf[1][3] + z * mf[2][3] + mf[3][3];
}

// Projects a 3D point through a camera and positions the sprite at the
// resulting screen coordinate. Returns the projected depth scale.
f32 HuSpr3Dto2D(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z) {
    Mtx perspMtx;
    Mtx lookAtMtx;
    u16 perspNorm;
    f32 x1, y1, z1, w1;
    f32 x2, y2, z2, w2;
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite = group_ptr->members[member];
    HuCamera *cam = &gCameraList[camera];
    s32 depth;
    f32 scale;

    guPerspective(&perspMtx, &perspNorm, cam->fov, 4.0f / 3.0f, cam->near, cam->far, 1.0f);
    guLookAt(&lookAtMtx, cam->pos.x, cam->pos.y, cam->pos.z, cam->at.x, cam->at.y, cam->at.z, cam->up.x, cam->up.y,
             cam->up.z);
    HuSprMtxXformVec4(&lookAtMtx, x, y, z, 1.0f, &x1, &y1, &z1, &w1);
    HuSprMtxXformVec4(&perspMtx, x1, y1, z1, w1, &x2, &y2, &z2, &w2);
    if (w2 != 0.0f) {
        depth = (cam->viewports[Hu3DCamMtxNo].vp.vscale[2] << 5) * z2 / w2 +
                (cam->viewports[Hu3DCamMtxNo].vp.vtrans[2] << 5);
    } else {
        depth = cam->viewports[Hu3DCamMtxNo].vp.vtrans[2] << 5;
    }
    if (depth < 0) {
        depth = 0;
    } else if (depth > 0x7FC0) {
        depth = 0x7FC0;
    }
    scale = sindf(gCameraList[camera].fov * 0.5) * z1 / cosdf(gCameraList[camera].fov * 0.5);
    HuSpr3DScale = scale = fabsf(scale);
    if (scale != 0.0) {
        sprite->pos.x = cam->viewports[Hu3DCamMtxNo].vp.vscale[0] / 4.0 * x1 / scale / (f64)(4.0f / 3.0f) +
                         cam->viewports[Hu3DCamMtxNo].vp.vtrans[0] / 4.0;
        sprite->pos.y = cam->viewports[Hu3DCamMtxNo].vp.vscale[1] / 4.0 * -y1 / scale +
                         cam->viewports[Hu3DCamMtxNo].vp.vtrans[1] / 4.0;
    }
    sprite->unk_44 = depth;
    group_ptr->dirty = 1;
    return HuSpr3DScale;
}

// Positions the sprite at a projected 3D point and scales it by depth.
void HuSpr3DPosSet(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];
    HuCamera *cam = &gCameraList[camera];

    HuSpr3Dto2D(group, member, camera, x, y, z);
    if (HuSpr3DScale != 0.0) {
        sprite->unk_60 = cam->viewports[Hu3DCamMtxNo].vp.vscale[0] / 4.0 / HuSpr3DScale / (f64)(4.0f / 3.0f);
        sprite->unk_64 = cam->viewports[Hu3DCamMtxNo].vp.vscale[1] / 4.0 / HuSpr3DScale;
    }
}

void HuSprPatNoSet(s16 group, s16 member, s32 arg2) {
    HuSprGrpData[group]->members[member]->patNo = arg2;
}

void HuSprGrpMemberSet(s16 group, s16 member, s16 arg2, u16 arg3) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->data = HuSprAnimTbl[arg2];
    if (HuSprAnimTbl[arg2]->bank != 0) {
        sprite_ptr->animMode = HUSPR_ANIM_MODE_BANK;
    }
    sprite_ptr->bank = arg3;
    sprite_ptr->time = 0.0f;
    sprite_ptr->speed = 1.0f;
    sprite_ptr->animNo = 0;
    sprite_ptr->animStat = 0;
    sprite_ptr->patNo = 0;
    HuSprAnmSync(sprite_ptr);
}

void HuSprSpeedSet(s16 group, s16 member, f32 arg2) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->speed = arg2;
    HuSprAnmSync(sprite_ptr);
}

void HuSprAnimModeSet(s16 group, s16 member, s32 mode) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->animStat &= ~HUSPR_ANIM_STAT_INIT;
    sprite_ptr->animMode = mode;
    HuSprAnmSync(sprite_ptr);
}

void HuSprBankSet(s16 group, s16 member, u16 arg2, s32 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->animStat &= ~HUSPR_ANIM_STAT_INIT;
    sprite->bank = arg2;
    sprite->animNo = arg3;
    sprite->time = 0;
    HuSprAnmSync(sprite);
}

HuSprAnimData *HuSprAnimDataGet(s16 arg0) {
    return HuSprAnimTbl[arg0];
}

u8 HuSprAnimStatGet(s16 group, s16 member) {
    return HuSprGrpData[group]->members[member]->animStat;
}

void HuSprScaleSet(s16 group, s16 member, f32 x, f32 y) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if (sprite_ptr->scale.x != x || sprite_ptr->scale.y != y || sprite_ptr->unk_60 != 1.0f || sprite_ptr->unk_64 != 1.0f) {
        group_ptr->dirty = 1;
        sprite_ptr->scale.x = x;
        sprite_ptr->scale.y = y;
        sprite_ptr->unk_64 = 1.0f;
        sprite_ptr->unk_60 = 1.0f;
    }
}

void HuSprPriSet(s16 group, s16 member, u16 prio) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if (sprite_ptr->prio != prio) {
        sprite_ptr->prio = prio;
        HuSprOrderDirtyF = 1;
    }
}

void HuSprZRotSet(s16 group, s16 member, f32 arg2) {
    HuSprGrp *group_ptr = HuSprGrpData[group];
    HuSprite *sprite_ptr = group_ptr->members[member];

    if (sprite_ptr->zRot != arg2) {
        group_ptr->dirty = 1;
        sprite_ptr->zRot = arg2;
    }
}

void HuSprAttrReset(s16 group, s16 member, s32 attr) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if ((sprite_ptr->attr & HUSPR_ATTR_DISPOFF) && (attr & HUSPR_ATTR_DISPOFF)) {
        HuSprOrderDirtyF = 1;
    }
    if ((sprite_ptr->attr & HUSPR_ATTR_BG) && (attr & HUSPR_ATTR_BG)) {
        HuSprOrderDirtyF = 1;
    }
    sprite_ptr->attr &= ~attr;
    sprite_ptr->dispAttr = sprite_ptr->attr;
}

void HuSprAttrSet(s16 group, s16 member, s32 attr) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    if (!(sprite_ptr->attr & HUSPR_ATTR_DISPOFF) && (attr & HUSPR_ATTR_DISPOFF)) {
        HuSprOrderDirtyF = 1;
    }
    if (!(sprite_ptr->attr & HUSPR_ATTR_BG) && (attr & HUSPR_ATTR_BG)) {
        HuSprOrderDirtyF = 1;
    }
    sprite_ptr->attr |= attr;
    sprite_ptr->dispAttr = sprite_ptr->attr;
}

void HuSprColorSet(s16 group, s16 member, u8 r, u8 g, u8 b) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->color[0] = r;
    sprite_ptr->color[1] = g;
    sprite_ptr->color[2] = b;
}

void HuSprTPLvlSet(s16 group, s16 member, u16 arg2) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->tpLvl = arg2;
}

void HuSprColorTPLvlSet(s16 group, s16 member, u8 arg2, u8 arg3, u8 arg4, u16 arg5) {
    HuSprite *sprite_ptr = HuSprGrpData[group]->members[member];

    sprite_ptr->color[0] = arg2;
    sprite_ptr->color[1] = arg3;
    sprite_ptr->color[2] = arg4;
    sprite_ptr->tpLvl = arg5;
}

void HuSprParentSet(s16 group, s16 member, s16 arg2) {
    HuSprGrpData[group]->members[member]->unk_2E = arg2;
}

void HuSprShiftSet(s16 group, s16 member, u8 shiftX, u8 shiftY) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->shiftX = shiftX;
    sprite->shiftY = shiftY;
}

HuSprite *HuSprGet(s16 group, s16 member) {
    return HuSprGrpData[group]->members[member];
}

void HuSprRectSet(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_3C = arg2;
    sprite->unk_3E = arg3;
    sprite->unk_40 = arg4;
    sprite->unk_42 = arg5;
}

void HuSprTexScaleSet(s16 group, s16 member, f32 arg2, f32 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_30.f = arg2;
    sprite->unk_34.f = arg3;
}

void HuSprTexMaskSet(s16 group, s16 member, u16 arg2, u16 arg3) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->unk_38 = arg2;
    sprite->unk_3A = arg3;
}

void HuSprScissorSet(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];

    sprite->scissorX = arg2;
    sprite->scissorY = arg3;
    sprite->scissorX2 = arg4;
    sprite->scissorY2 = arg5;
}

void HuSprAnimInit(void) {
    s16 i;

    HuSprAnimNum = 0;
    for (i = 0; i < 0x100; i++) {
        HuSprAnimTbl[i] = NULL;
    }
}

void HuSprAnimKill(s16 arg0) {
    HuSprAnimData *desc = HuSprAnimTbl[arg0];
    s16 i;

    if (desc->bank != NULL) {
        HuSprAnimBank *cel = *desc->bank;
        if (cel != NULL) {
            for (i = 0; i < desc->bankNum; i++) {
                HuMemFree(cel->frame);
                cel++;
            }
        }
        HuMemFree(*desc->bank);
        HuMemFree(desc->bank);
    }
    HuMemDelayFree(desc->pal);
    {
        HuSprAnimPat *cel = desc->pat;
        for (i = 0; i < desc->patNum; i++) {
            HuMemDelayFree(cel->data);
            cel++;
        }
    }
    HuMemFree(desc->pat);
    HuMemFree(desc);
    HuSprAnimTbl[arg0] = NULL;
    HuSprAnimNum--;
}

void HuSprAnimAllKill(void) {
    s16 i;

    for (i = 0; i < 0x100; i++) {
        if (HuSprAnimTbl[i] != NULL) {
            HuSprAnimKill(i);
        }
    }
}

s16 HuSprAnimRead(void *arg0) {
    HuSprAnimFrame *frames[0x100];
    HuSprAnimData *desc;
    HuSprAnimPat *image;
    HuSprAnimBank **animations;
    HuSprAnimBank *animation;
    HuSprAnimFrame *frame;
    HuSprFileHeader *header = arg0;
    HuSprFileImage *fileImage;
    u8(*animationOffsets)[4];
    u8 *pixels;
    u8 *palette;
    u8 *dest;
    u8 *src;
    s32 size;
    u32 j;
    s16 i;
    s16 slot;
    s16 k;

    for (i = 0; i < 0x100 && HuSprAnimTbl[i] != NULL; i++) {
    }
    if (i == 0x100) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(sizeof(*desc));
    if (desc == NULL) {
        return -1;
    }
    fileImage = (HuSprFileImage *)((u8 *)header + HUSPR_READ32(header->images));
    animationOffsets = (u8(*)[4])((u8 *)header + HUSPR_READ32(header->animations));
    pixels = (u8 *)header + HUSPR_READ32(header->pixels);
    palette = (u8 *)header + HUSPR_READ32(header->palette);
    desc->patNum = HUSPR_READ16(header->imageCount);
    desc->bankNum = HUSPR_READ16(header->animationCount);
    desc->sizeX = HUSPR_READ16(header->width);
    desc->sizeY = HUSPR_READ16(header->height);
    desc->pixelBits = HUSPR_READ16(header->pixelBits);
    desc->palNum = header->paletteCount;
    // A zero palette count represents 256 colors for 8-bit images.
    if (desc->pixelBits == 8 && desc->palNum == 0) {
        desc->palNum = 0x100;
    }
    desc->pat = NULL;
    desc->bank = NULL;
    desc->data = NULL;
    desc->pal = NULL;
    HuSprAnimTbl[slot] = desc;
    HuSprAnimNum++;
    image = HuMemAlloc(desc->patNum * sizeof(*image));
    if (image != NULL) {
        desc->pat = image;
    } else {
        HuSprAnimKill(slot);
        return -1;
    }
    for (i = 0; i < desc->patNum; i++) {
        image->sizeX = HUSPR_READ16(fileImage->width);
        image->sizeY = HUSPR_READ16(fileImage->height);
        image->centerX = HUSPR_READ16(fileImage->centerX);
        image->centerY = HUSPR_READ16(fileImage->centerY);
        size = image->sizeX * image->sizeY * (desc->pixelBits & 0x7FFF) / 8;
        image->data = HuMemAlloc(size);
        if (image->data == NULL) {
            desc->patNum = i;
            HuSprAnimKill(slot);
            return -1;
        }
        for (j = 0; j < size; j++) {
            ((u8 *)image->data)[j] = *pixels++;
        }
        fileImage++;
        if (i == 0) {
            desc->data = image->data;
        }
        image++;
    }
    if (desc->palNum != 0) {
        dest = HuMemAlloc(desc->palNum * 2);
        if (dest != NULL) {
            desc->pal = dest;
        } else {
            HuSprAnimKill(slot);
            return -1;
        }
        for (i = 0; i < desc->palNum; i++) {
            *dest++ = palette[i * 2];
            *dest++ = palette[i * 2 + 1];
        }
    }
    if (desc->bankNum == 0) {
        return slot;
    }
    animations = HuMemAlloc(desc->bankNum * (s32)sizeof(*animations));
    if (animations != NULL) {
        desc->bank = animations;
    } else {
        HuSprAnimKill(slot);
        return -1;
    }
    animation = HuMemAlloc(desc->bankNum * (s32)sizeof(*animation));
    if (animation == NULL) {
        HuSprAnimKill(slot);
        return -1;
    }
    for (i = 0; i < desc->bankNum; i++) {
        // The original loader scales this index by the record size twice.
        animations[i] = &animation[i * sizeof(*animation)];
    }
    for (k = 0; k < desc->bankNum; k++) {
        src = (u8 *)header + HUSPR_READ32(animationOffsets[k]);
        animation->timeNum = HUSPR_READ16(src);
        src += 2;
        frames[k] = HuMemAlloc(animation->timeNum * sizeof(*frame));
        if (frames[k] == NULL) {
            desc->bankNum = k;
            HuSprAnimKill(slot);
            return -1;
        }
        animation->frame = frames[k];
        frame = frames[k];
        for (i = 0; i < animation->timeNum; i++) {
            frame->pat = HUSPR_READ16(((HuSprFileFrame *)src)->image);
            frame->time = HUSPR_READ16(((HuSprFileFrame *)src)->duration);
            frame->shiftX = ((HuSprFileFrame *)src)->shiftX;
            frame->shiftY = ((HuSprFileFrame *)src)->shiftY;
            frame->flip = ((HuSprFileFrame *)src)->flip;
            src += sizeof(HuSprFileFrame);
            frame++;
        }
        animation++;
    }
    return slot;
}

s32 HuSprAnimMake(u16 sizeX, u16 sizeY, u16 pixelBits, u16 palNum, u16 patNum) {
    HuSprAnimData *desc;
    HuSprAnimPat *cel;
    s16 i;
    s16 slot;

    for (i = 0; i < 0x100 && HuSprAnimTbl[i] != NULL; i++) {
    }
    if (i == 0x100) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(0x1C);
    if (desc == NULL) {
        return -1;
    }
    desc->patNum = patNum;
    desc->bankNum = 0;
    desc->sizeX = sizeX;
    desc->sizeY = sizeY * patNum;
    desc->pixelBits = pixelBits;
    desc->palNum = palNum;
    desc->pat = NULL;
    desc->bank = 0;
    desc->data = NULL;
    desc->pal = NULL;
    HuSprAnimTbl[slot] = desc;
    HuSprAnimNum++;
    cel = HuMemAlloc(desc->patNum * 0xC);
    if (cel != NULL) {
        desc->pat = cel;
    } else {
        HuSprAnimKill(slot);
        return -1;
    }
    for (i = 0; i < desc->patNum; i++) {
        s32 size;

        cel->sizeX = sizeX;
        cel->sizeY = sizeY;
        cel->centerX = sizeX >> 1;
        cel->centerY = sizeY >> 1;
        size = cel->sizeX * cel->sizeY * (desc->pixelBits & 0x7FFF);
        cel->data = HuMemAlloc(size / 8);
        if (cel->data == NULL) {
            desc->patNum = i;
            HuSprAnimKill(slot);
            return -1;
        }
        if (i == 0) {
            desc->data = cel->data;
        }
        cel++;
    }
    if (desc->palNum != 0) {
        void *pal = HuMemAlloc(desc->palNum * 2);

        if (pal != NULL) {
            desc->pal = pal;
        } else {
            HuSprAnimKill(slot);
            return -1;
        }
    }
    return slot;
}

void HuSprAnmSet(HuSprAnm *arg0, s16 arg1, u16 arg2, u16 arg3) {
    HuSprAnmInit(arg0);
    arg0->animMode = arg3;
    arg0->bank = arg2;
    arg0->data = HuSprAnimDataGet(arg1);
}

s16 HuSprAnmRead(void *arg0, HuSprAnm *arg1, u16 arg2, u16 arg3) {
    s16 temp = HuSprAnimRead(arg0);

    HuSprAnmSet(arg1, temp, arg2, arg3);
    return temp;
}

HuSprAnimPat *HuSprAnimPatGet(HuSprAnimData **arg0, u16 arg1) {
    return &(*arg0)->pat[arg1];
}

HuSprAnimPat *HuSprAnimPatGetNum(s16 arg0, u16 arg1) {
    return &HuSprAnimTbl[arg0]->pat[arg1];
}

HuSprAnimPat *HuSprAnmPatGet(HuSprAnm *arg0) {
    return &arg0->data->pat[arg0->patNo];
}

void *HuSprAnimPatDataGet(HuSprAnimData **arg0, u16 arg1) {
    HuSprAnimPat *entry = &(*arg0)->pat[arg1];

    return entry->data;
}

void *HuSprAnimPatDataGetNum(s16 arg0, u16 arg1) {
    HuSprAnimPat *entry = &HuSprAnimTbl[arg0]->pat[arg1];

    return entry->data;
}

void HuSprAnimPatDataSet(HuSprAnimData **arg0, u16 arg1, void *arg2) {
    HuSprAnimPat *entry = &(*arg0)->pat[arg1];

    HuMemDelayFree(entry->data);
    entry->data = arg2;
}

void HuSprAnimPatDataSetNum(s16 arg0, u16 arg1, void *arg2) {
    HuSprAnimPat *entry = &HuSprAnimTbl[arg0]->pat[arg1];

    HuMemDelayFree(entry->data);
    entry->data = arg2;
}

void *HuSprAnmPatDataGet(HuSprAnm *arg0) {
    HuSprAnimPat *entry = &arg0->data->pat[arg0->patNo];

    return entry->data;
}

void *HuSprAnimPalGet(HuSprAnimData **arg0) {
    return (*arg0)->pal;
}

void *HuSprAnimPalGetNum(s16 arg0) {
    return HuSprAnimTbl[arg0]->pal;
}

void HuSprAnimPalSet(HuSprAnimData **arg0, void *arg1) {
    HuMemDelayFree((*arg0)->pal);
    (*arg0)->pal = arg1;
}

void HuSprAnimPalSetNum(s16 arg0, void *arg1) {
    HuMemDelayFree(HuSprAnimTbl[arg0]->pal);
    HuSprAnimTbl[arg0]->pal = arg1;
}

s16 HuSprAnmFrameGet(HuSprAnm *arg0) {
    HuSprAnimData *desc = arg0->data;

    if (desc == NULL) {
        return -1;
    }
    if (arg0->animMode == HUSPR_ANIM_MODE_BANK) {
        HuSprAnimBank *cel;
        HuSprAnimFrame *frame;

        if (desc->bank == NULL) {
            return 0;
        }
        cel = &(*desc->bank)[arg0->bank];
        frame = &cel->frame[arg0->animNo];
        arg0->patNo = frame->pat;
        arg0->shiftX = frame->shiftX;
        arg0->shiftY = frame->shiftY;
        arg0->flip = frame->flip;
    } else if (arg0->animMode >= HUSPR_ANIM_MODE_PAT_LOOP) {
        if (arg0->animMode <= HUSPR_ANIM_MODE_PAT_PINGPONG) {
            arg0->patNo = arg0->animNo;
        }
    }
    return 0;
}

void SpriteCalcFrame(HuSprAnm *arg0) {
    HuSprAnimData *desc = arg0->data;
    HuSprAnimBank *cel;
    HuSprAnimFrame *frame;
    s16 prev;

    if (desc == NULL) {
        return;
    }
    arg0->animStat &= HUSPR_ANIM_STAT_INIT;
    switch (arg0->animMode) {
        case HUSPR_ANIM_MODE_STOP:
            return;
        case HUSPR_ANIM_MODE_BANK:
            if (desc->bank == NULL) {
                return;
            }
            cel = &(*desc->bank)[arg0->bank];
            frame = &cel->frame[arg0->animNo];
            arg0->time += arg0->speed;
            if ((s16)arg0->time > frame->time) {
                arg0->time = 0.0f;
                arg0->animNo++;
                arg0->animStat |= HUSPR_ANIM_STAT_FRAME;
                if (arg0->animNo >= cel->timeNum) {
                    arg0->animMode = HUSPR_ANIM_MODE_STOP;
                    arg0->animStat |= HUSPR_ANIM_STAT_END;
                } else if (cel->frame[arg0->animNo].time < 0) {
                    arg0->animNo = 0;
                    arg0->animStat |= HUSPR_ANIM_STAT_LOOP;
                }
            }
            arg0->patNo = frame->pat;
            arg0->shiftX = frame->shiftX;
            arg0->shiftY = frame->shiftY;
            arg0->flip = frame->flip;
            break;
        case HUSPR_ANIM_MODE_PAT_LOOP:
            prev = arg0->animNo;
            arg0->time += arg0->speed;
            arg0->animNo = (s32)arg0->time + arg0->animNo;
            if (arg0->animNo != prev) {
                arg0->time -= arg0->animNo - prev;
                arg0->animStat |= HUSPR_ANIM_STAT_FRAME;
            }
            if (arg0->animNo >= arg0->data->patNum) {
                arg0->animNo = 0;
                arg0->time = 0.0f;
                arg0->animStat |= HUSPR_ANIM_STAT_LOOP;
            }
            arg0->patNo = arg0->animNo;
            break;
        case HUSPR_ANIM_MODE_PAT_PINGPONG:
            prev = arg0->animNo;
            arg0->time += arg0->speed;
            arg0->animNo = (s32)arg0->time + arg0->animNo;
            if (arg0->animNo != prev) {
                arg0->time -= arg0->animNo - prev;
                arg0->animStat |= HUSPR_ANIM_STAT_LOOP;
            }
            if (arg0->animNo < 0 || arg0->animNo >= arg0->data->patNum) {
                arg0->animNo = (arg0->speed < 0.0f) ? 1 : arg0->data->patNum - 2;
                arg0->time = 0.0f;
                arg0->speed = -arg0->speed;
                arg0->animStat |= HUSPR_ANIM_STAT_LOOP;
            }
            arg0->patNo = arg0->animNo;
            break;
        default:
            return;
    }
    arg0->animStat |= HUSPR_ANIM_STAT_UPDATE;
}

void HuSprAnimExec(HuSprite *sprite) {
    HuSprAnm *anm = &sprite->anim;

    HuSprAnmSync(sprite);
    if (!(sprite->anim.animStat & HUSPR_ANIM_STAT_INIT)) {
        if (HuSprAnmFrameGet(anm) == 0) {
            sprite->anim.animStat |= HUSPR_ANIM_STAT_INIT;
        }
    } else {
        if (Hu3DPauseF == 0 || (sprite->dispAttr & HUSPR_ATTR_NOPAUSE)) {
            SpriteCalcFrame(anm);
        }
    }
    sprite->animStat = anm->animStat;
    sprite->animMode = (u16)anm->animMode;
    sprite->patNo = (u16)anm->patNo;
    sprite->shiftX = anm->shiftX;
    sprite->shiftY = anm->shiftY;
    sprite->flip = anm->flip;
    sprite->animNo = (u16)anm->animNo;
    sprite->time = anm->time;
    sprite->speed = anm->speed;
    sprite->unk_18 = sprite->scale.x * sprite->unk_60;
    sprite->unk_1C = sprite->scale.y * sprite->unk_64;
    if (sprite->unk_98.unk00 != NULL) {
        HuSprPalAnimExec(&sprite->unk_98);
    }
}

// Computes the texture tiling of a sprite and reserves display list space.
void HuSprTexLoad(HuSprite *sprite) {
    HuSprAnimPat *image;
    s32 fmt = G_IM_FMT_RGBA;
    s32 siz = G_IM_SIZ_4b;
    s32 width;
    u32 lines;
    u32 tiles;
    s32 changed;

    sprite->dispAttr = sprite->flip ^ sprite->attr;
    if (sprite->data == NULL || (sprite->dispAttr & HUSPR_ATTR_DISPOFF)) {
        return;
    }
    if (fabs(fmod(sprite->unk_20, 360.0)) > 0.1f || (sprite->dispAttr & (HUSPR_ATTR_WRAPS_MASK | HUSPR_ATTR_WRAPT_MASK | HUSPR_ATTR_AA_MASK)) ||
        (sprite->dispAttr & (HUSPR_ATTR_RECT | HUSPR_ATTR_RECT_TILE)) == (HUSPR_ATTR_RECT | HUSPR_ATTR_RECT_TILE) || (sprite->dispAttr & HUSPR_ATTR_VTX)) {
        image = &sprite->data->pat[sprite->patNo];
        switch (sprite->data->pixelBits & 0x7FFF) {
            case 4:
                fmt = G_IM_FMT_CI;
                siz = G_IM_SIZ_4b;
                break;
            case 8:
                fmt = G_IM_FMT_CI;
                siz = G_IM_SIZ_8b;
                break;
            case 16:
                fmt = G_IM_FMT_RGBA;
                siz = G_IM_SIZ_16b;
                break;
            case 24:
                fmt = G_IM_FMT_RGBA;
                siz = G_IM_SIZ_32b;
                break;
        }
        width = ((image->sizeX << siz) >> 4 << 4) >> siz;
        if (width < image->sizeX) {
            width += 16 >> siz;
        }
        switch (fmt) {
            case G_IM_FMT_CI:
                if ((0x1000 >> siz) >= image->sizeY * width) {
                    lines = image->sizeY;
                } else {
                    lines = (0x1000 >> siz) / width;
                }
                break;
            case G_IM_FMT_I:
                if (image->sizeY * width <= 0x1000) {
                    lines = image->sizeY;
                } else {
                    lines = 0x1000 / width;
                }
                break;
            default:
                if ((0x2000 >> siz) >= image->sizeY * width) {
                    lines = image->sizeY;
                } else {
                    lines = (0x2000 >> siz) / width;
                }
                break;
        }
        tiles = image->sizeY / lines;
        sprite->dispAttr |= HUSPR_ATTR_VTXDRAW;
        if (!(sprite->dispAttr & HUSPR_ATTR_DLCACHE)) {
            HuSprGfxBufSize += !(sprite->dispAttr & HUSPR_ATTR_MULTITEX) ? (tiles + 2) << 5 : (tiles + 2) << 6;
        } else {
            changed = sprite->dispAttr ^ sprite->prevAttr;
            if (sprite->unk_124 == NULL || (changed & HUSPR_ATTR_VTXDRAW)) {
                sprite->dispAttr |= HUSPR_ATTR_DLDIRTY;
            }
            if (sprite->dispAttr & HUSPR_ATTR_DLDIRTY) {
                if (sprite->unk_128[sprite->unk_120] != NULL) {
                    HuMemFree(sprite->unk_128[sprite->unk_120]);
                    HuMemFree(sprite->unk_134[sprite->unk_120]);
                    sprite->unk_128[sprite->unk_120] = NULL;
                    sprite->unk_134[sprite->unk_120] = NULL;
                }
                sprite->unk_134[sprite->unk_120] =
                    HuMemAlloc(!(sprite->dispAttr & HUSPR_ATTR_MULTITEX) ? (tiles + 2) << 5 : (tiles + 2) << 6);
            }
        }
    } else {
        sprite->dispAttr &= ~HUSPR_ATTR_VTXDRAW;
        if (sprite->dispAttr & HUSPR_ATTR_DLCACHE) {
            changed = sprite->dispAttr ^ sprite->prevAttr;
            if (sprite->unk_124 == NULL || (changed & HUSPR_ATTR_VTXDRAW)) {
                sprite->dispAttr |= HUSPR_ATTR_DLDIRTY;
            }
            if (sprite->dispAttr & HUSPR_ATTR_DLDIRTY) {
                if (sprite->unk_128[sprite->unk_120] != NULL) {
                    HuMemFree(sprite->unk_128[sprite->unk_120]);
                    HuMemFree(sprite->unk_134[sprite->unk_120]);
                    sprite->unk_128[sprite->unk_120] = NULL;
                    sprite->unk_134[sprite->unk_120] = NULL;
                }
            }
        }
    }
    sprite->prevAttr = sprite->dispAttr;
}

void HuSprClose(void) {
    s16 i;

    HuSprGrpAllKill();
    HuSprAnimAllKill();
    HuSprPalAnimAllKill();
    for (i = 0; i < 3; i++) {
        if (HuSprGfxBuf[i] != NULL) {
            HuMemFree(HuSprGfxBuf[i]);
        }
    }
}

// Unused; references math routines so they are linked.
void HuSprDummy(void) {
    HuMtx4F mf;
    Mtx a;
    Mtx b;

    fmod(0.0, 0.0);
    guTranslateF(mf, 0.0f, 0.0f, 0.0f);
    guMtxCatL(&a, &b, &a);
}

u16 HuSprRead16(u8 **arg0) {
    u8 *p = *arg0;
    u16 val = (p[0] << 8) + p[1];

    *arg0 = p + 2;
    return val;
}

u32 HuSprRead32(u8 **arg0) {
    u8 *p = *arg0;
    u32 val = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];

    *arg0 = p + 4;
    return val;
}

void HuSprPalAnimInit(void) {
    s16 i;

    HuSprPalAnimNum = 0;
    for (i = 0; i < 0x100; i++) {
        HuSprPalAnimData[i] = NULL;
    }
}

s16 HuSprPalAnimRead(u8 *data) {
    u8 *base = data;
    HuSprAnmDesc *desc;
    HuSprAnmEntry *group;
    HuSprPalFrame *frame;
    HuSprPalEntry *entry;
    u8 *groupData;
    s32 i;
    s32 j;
    s32 k;
    s32 slot;

    for (i = 0; i < 0x100; i++) {
        if (HuSprPalAnimData[i] == NULL) {
            break;
        }
    }
    if (i == 0x100) {
        return -1;
    }
    slot = i;
    desc = HuMemAlloc(sizeof(*desc));
    desc->unk00 = HuSprRead16(&data);
    desc->unk02 = HuSprRead16(&data);
    desc->unk04 = HuMemAlloc(desc->unk02 * sizeof(*desc->unk04));
    for (j = 0; j < desc->unk02; j++) {
        desc->unk04[j] = group = HuMemAlloc(sizeof(*group));
        groupData = base + HuSprRead32(&data);
        group->unk00 = HuSprRead16(&groupData);
        if (group->unk00 == 0) {
            continue;
        }
        group->unk02 = HuSprRead16(&groupData);
        group->unk04 = HuMemAlloc(group->unk02 * sizeof(*group->unk04));
        for (k = 0; k < group->unk02; k++) {
            frame = HuMemAlloc(sizeof(*frame));
            group->unk04[k] = frame;
            frame->duration = HuSprRead16(&groupData);
            entry = HuMemAlloc(group->unk00 * sizeof(*entry));
            frame->entries = entry;
            for (i = 0; i < group->unk00; i++) {
                entry->index = HuSprRead16(&groupData);
                entry->color = HuSprRead16(&groupData);
                entry++;
            }
        }
    }
    desc->unk08 = HuSprRead16(&data);
    desc->unk0C = HuMemAlloc(desc->unk08 * sizeof(*desc->unk0C));
    for (i = 0; i < desc->unk08; i++) {
        desc->unk0C[i] = HuSprRead16(&data);
    }
    HuSprPalAnimData[slot] = desc;
    HuSprPalAnimNum++;
    return slot;
}

void HuSprPalAnimKill(s16 arg0) {
    HuSprAnmDesc *desc = HuSprPalAnimData[arg0];
    s32 i;

    for (i = 0; i < desc->unk02; i++) {
        HuSprAnmEntry *group = desc->unk04[i];

        if (group->unk00 != 0) {
            s32 j;

            for (j = 0; j < group->unk02; j++) {
                HuSprPalFrame *frame = group->unk04[j];

                HuMemFree(frame->entries);
                HuMemFree(frame);
            }
            HuMemFree(group->unk04);
        }
        HuMemFree(group);
    }
    HuMemFree(desc->unk04);
    HuMemFree(desc->unk0C);
    HuMemFree(desc);
    HuSprPalAnimData[arg0] = NULL;
    HuSprPalAnimNum--;
}

void HuSprPalAnimSet(s16 group, s16 member, s16 arg2) {
    HuSprite *sprite = HuSprGrpData[group]->members[member];
    s32 i;

    sprite->unk_98.unk00 = HuSprPalAnimData[arg2];
    sprite->unk_98.unk64.f = 1.0f;
    for (i = 0; i < 0x10; i++) {
        sprite->unk_98.unk04[i] = 0xFFFF;
        sprite->unk_98.unk24[i] = 0.0f;
    }
    sprite->unk_98.unk6C = NULL;
}

void HuSprPalAnimParamSet(s16 group, s16 member, s32 arg2) {
    HuSprGrpData[group]->members[member]->unk_98.unk64.i = arg2;
}

void HuSprPalAnimAllKill(void) {
    s16 i;

    for (i = 0; i < 0x100; i++) {
        if (HuSprPalAnimData[i] != NULL) {
            HuSprPalAnimKill(i);
        }
    }
}

void HuSprPalAnimExec(HuSprPalAnm *arg0) {
    HuSprAnmDesc *desc;
    HuSprAnmEntry *group;
    HuSprPalFrame *frame;
    HuSprPalEntry *entry;
    s32 changed;
    s32 i;
    s32 j;

    changed = FALSE;
    desc = arg0->unk00;
    for (i = 0; i < desc->unk02; i++) {
        group = desc->unk04[i];
        if (group->unk00 == 0) {
            continue;
        }
        arg0->unk24[i] -= arg0->unk64.f;
        do {
            if (arg0->unk24[i] <= 0.0f) {
                arg0->unk04[i]++;
                if (arg0->unk04[i] >= group->unk02) {
                    arg0->unk04[i] = 0;
                    frame = group->unk04[0];
                } else {
                    frame = group->unk04[arg0->unk04[i]];
                    if (frame->duration <= 0) {
                        arg0->unk04[i] = 0;
                        frame = group->unk04[0];
                    }
                }
                arg0->unk24[i] += frame->duration;
                changed = TRUE;
            }
        } while (arg0->unk24[i] < 0.0f);
    }
    if (!changed) {
        return;
    }
    if (arg0->unk70[arg0->unk68] == NULL) {
        arg0->unk70[arg0->unk68] = HuMemAlloc(desc->unk08 * sizeof(u16));
    }
    arg0->unk6C = arg0->unk70[arg0->unk68];
    bcopy(desc->unk0C, arg0->unk6C, desc->unk08 * sizeof(u16));
    arg0->unk68++;
    if (arg0->unk68 >= 3) {
        arg0->unk68 = 0;
    }
    for (j = 0; j < desc->unk02; j++) {
        group = desc->unk04[j];
        if (group->unk00 == 0) {
            continue;
        }
        frame = group->unk04[arg0->unk04[j]];
        entry = frame->entries;
        for (i = 0; i < group->unk00; i++) {
            arg0->unk6C[entry->index] = entry->color;
            entry++;
        }
    }
}
