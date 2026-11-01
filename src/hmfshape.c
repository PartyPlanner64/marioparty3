#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfshape.h"
#include "game/mallocblock.h"
#include "game/hu3d.h"

#define READ_VERTEX_ANIM_NIBBLE(stream, nibble, result) \
    do {                                                \
        if (nibble == 0) {                              \
            result = *stream >> 4;                      \
        } else {                                        \
            result = (u8)(*stream & 0xF);               \
            stream++;                                   \
        }                                               \
        nibble ^= 1;                                    \
    } while (0)

#define READ_VERTEX_ANIM_BYTE(stream, nibble, result)           \
    do {                                                        \
        if (nibble == 0) {                                      \
            result = *stream;                                   \
        } else {                                                \
            result = ((*stream & 0xF) << 4) | (stream[1] >> 4); \
        }                                                       \
        stream++;                                               \
    } while (0)

typedef struct {
    HmfData *model;
    u8 *data;
    u8 *frames;
    s16 duration;
    s16 frameCount;
    s16 frameStep;
} HmfVertexAnim;

extern HmfVertexAnim *D_800D59F8_main;
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

void func_800308C0_main(HmfVertexAnim *, HmfData *, HmfVertexAnimCache *, s16);

void func_80030040_main(void) {
    s16 i;
    D_800D59F8_main = HuMemAlloc(0x140);
    for (i = 0; i < 0x10; i++) {
        D_800D59F8_main[i].frames = 0;
    }
}

s32 func_800300A4_main(HmfData *model, u8 *data) {
    s16 i;
    HmfVertexAnim *anim;

    for (i = 0; i < 16; i++) {
        if (D_800D59F8_main[i].frames == NULL) {
            break;
        }
    }
    if (i == 16) {
        return -1;
    }
    anim = &D_800D59F8_main[i];
    anim->model = model;
    anim->data = data;
    anim->duration = (data[8] << 8) + data[9];
    anim->frameCount = (data[10] << 8) + data[11];
    anim->frameStep = (data[12] << 8) + data[13];
    anim->frames = &data[14];
    return i;
}

void func_80030178_main(s32 arg0) {
    D_800D59F8_main[arg0].frames = 0;
}

void func_80030198_main(void) {
    s16 i;

    for (i = 0; i < 0x10; i++) {
        if (D_800D59F8_main[i].frames != 0) {
            func_80030178_main(i);
        }
    }
}

void func_80030208_main(HmfData *model) {
    s16 count;
    s16 i;
    HmfVertexAnimCache *cache;
    s16(*positions)[3];
    s8(*normals)[3];
    Vtx_t *vertices;

    if (model->unk58 != NULL) {
        cache = model->unk58;
        HuMemFree(cache->positions[0]);
        HuMemFree(cache->positions[1]);
        HuMemFree(cache->normals[0]);
        HuMemFree(cache->normals[1]);
        HuMemFree(cache->visited);
        HuMemFree(cache);
    }
    count = model->unk18;
    cache = HuMemAllocTag(sizeof(*cache), D_800CDD6A_main);
    model->unk58 = cache;
    cache->vertexCount = count;
    positions = HuMemAllocTag(count * 6, D_800CDD6A_main);
    cache->positions[0] = positions;
    normals = HuMemAllocTag(count * 3, D_800CDD6A_main);
    cache->normals[0] = normals;
    cache->positions[1] = HuMemAllocTag(count * 6, D_800CDD6A_main);
    cache->normals[1] = HuMemAllocTag(count * 3, D_800CDD6A_main);
    cache->visited = HuMemAllocTag((count + 7) / 8, D_800CDD6A_main);
    cache->frames[0] = cache->frames[1] = -1;
    cache->currentBuffer = 0;
    vertices = (Vtx_t *)model->unk40;
    for (i = 0; i < count; i++) {
        (*positions)[0] = vertices->ob[0];
        (*positions)[1] = vertices->ob[1];
        (*positions)[2] = vertices->ob[2];
        (*normals)[0] = vertices->cn[0];
        (*normals)[1] = vertices->cn[1];
        (*normals)[2] = vertices->cn[2];
        vertices++;
        positions++;
        normals++;
    }
}

void func_800303C8_main(HmfModel *model, f32 time) {
    if (model->hmf->unkB4 != NULL) {
        func_80031324_main(model->hmf, time);
    } else {
        func_80030414_main(model->hmf, model->unk08, time);
    }
}

void func_80030414_main(HmfData *model, s16 animIndex, f32 time) {
    HmfVertexAnim *anim;
    s16 frame;
    s16 nextFrame;
    s16 buffer;
    HmfVertexAnimCache *cache;
    s16 i;
    s16(*positions)[3];
    s8(*normals)[3];
    s16(*nextPositions)[3];
    s8(*nextNormals)[3];
    Vtx_tn *vertices;
    s16 count;
    f32 weight;

    anim = &D_800D59F8_main[animIndex];
    cache = model->unk58;
    frame = time / anim->frameStep;
    if (frame >= anim->frameCount - 1) {
        frame = anim->frameCount - 1;
    }
    weight = (time - frame * anim->frameStep) / anim->frameStep;
    nextFrame = frame + 1;
    if (nextFrame >= anim->frameCount) {
        if ((anim->duration - 1) % anim->frameStep != 0) {
            nextFrame = anim->frameCount;
            weight = 1.0f - (anim->duration - time) /
                                (anim->duration - (anim->frameCount - 1) * anim->frameStep);
        } else {
            nextFrame = anim->frameCount - 1;
        }
    }
    if (cache->frames[0] != frame && cache->frames[1] != frame) {
        i = cache->frames[cache->currentBuffer];
        if (i < 0) {
            i = 0;
        }
        if (frame < i) {
            i = 0;
        }
        for (; i <= frame; i++) {
            func_800308C0_main(anim, model, cache, i);
        }
        buffer = cache->currentBuffer;
    } else if (cache->frames[0] == frame) {
        buffer = cache->currentBuffer = 0;
    } else {
        buffer = cache->currentBuffer = 1;
    }
    if (cache->frames[0] != nextFrame && cache->frames[1] != nextFrame) {
        func_800308C0_main(anim, model, cache, nextFrame);
    }
    if (frame == nextFrame) {
        weight = 0.0f;
    }
    positions = cache->positions[buffer];
    normals = cache->normals[buffer];
    nextPositions = cache->positions[(buffer + 1) & 1];
    nextNormals = cache->normals[(buffer + 1) & 1];
    vertices = (Vtx_tn *)model->unk44[D_800D2008_main];
    count = model->unk18;
    for (i = 0; i < count; i++) {
        vertices->ob[0] = (*positions)[0] * (1.0f - weight) + (*nextPositions)[0] * weight;
        vertices->ob[1] = (*positions)[1] * (1.0f - weight) + (*nextPositions)[1] * weight;
        vertices->ob[2] = (*positions)[2] * (1.0f - weight) + (*nextPositions)[2] * weight;
        vertices->n[0] = (*normals)[0] * (1.0f - weight) + (*nextNormals)[0] * weight;
        vertices->n[1] = (*normals)[1] * (1.0f - weight) + (*nextNormals)[1] * weight;
        vertices->n[2] = (*normals)[2] * (1.0f - weight) + (*nextNormals)[2] * weight;
        vertices++;
        positions++;
        normals++;
        nextPositions++;
        nextNormals++;
    }
}

void func_800308C0_main(HmfVertexAnim *anim, HmfData *model, HmfVertexAnimCache *cache, s16 frame) {
    s32 positionOffset;
    s32 positionVertex;
    s32 positionBuffer;
    s32 normalOffset;
    s32 normalVertex;
    s32 normalBuffer;
    u8 *header;
    u8 *data;
    u8 *entries;
    s16 entryCount;
    s16 count;
    s16 i;
    s16 flags;
    s32 index;
    u16 mappedIndex;
    s16 value;
    s16 word;
    s32 highPart;
    u8 lowByte;
    u8 half;
    u8 mask;
    s16 temp;
    s16(*positions)[3];
    s16(*nextPositions)[3];
    s8(*normals)[3];
    s8(*nextNormals)[3];
    Vtx_t *vertices;

    header = &anim->frames[frame * 4];
    entryCount = (header[0] << 8) + header[1];
    data = &anim->frames[(anim->frameCount + 1) * 4];
    header = anim->frames;
    for (i = 0; i < frame; i++) {
        data += ((header[0] << 8) + header[1]) * 2 + (header[2] << 8) + header[3];
        header += 4;
    }
    entries = data;
    data = entries + entryCount * 2;
    cache->frames[(cache->currentBuffer + 1) & 1] = frame;
    count = cache->vertexCount;
    if (frame == 0) {
        positions = cache->positions[cache->currentBuffer];
        normals = cache->normals[cache->currentBuffer];
        vertices = (Vtx_t *)model->unk40;
        for (i = 0; i < count; i++) {
            (*positions)[0] = vertices->ob[0];
            (*positions)[1] = vertices->ob[1];
            (*positions)[2] = vertices->ob[2];
            (*normals)[0] = vertices->cn[0];
            (*normals)[1] = vertices->cn[1];
            (*normals)[2] = vertices->cn[2];
            vertices++;
            positions++;
            normals++;
        }
    }
    positions = cache->positions[cache->currentBuffer];
    nextPositions = cache->positions[(cache->currentBuffer + 1) & 1];
    normals = cache->normals[cache->currentBuffer];
    nextNormals = cache->normals[(cache->currentBuffer + 1) & 1];
    for (i = 0; i < count; i++) {
        (*nextPositions)[0] = (*positions)[0];
        (*nextPositions)[1] = (*positions)[1];
        (*nextPositions)[2] = (*positions)[2];
        (*nextNormals)[0] = (*normals)[0];
        (*nextNormals)[1] = (*normals)[1];
        (*nextNormals)[2] = (*normals)[2];
        positions++;
        normals++;
        nextPositions++;
        nextNormals++;
    }
    for (i = 0; i < (count + 7) / 8; i++) {
        cache->visited[i] = 0;
    }
    half = 0;
    for (i = 0; i < entryCount; i++) {
        flags = (entries[0] << 8) + entries[1];
        index = flags & 0xFFF;
        mappedIndex = model->unk5C[index];
        mask = 1 << (mappedIndex & 7);
        temp = mappedIndex >> 3;
        if (cache->visited[(u8)temp] & mask) {
            if ((flags & 0xC000) == 0xC000) {
            } else if ((flags & 0xC000) == 0x8000) {
                data++;
                data += (half != 0);
                half ^= 1;
            } else if ((flags & 0xC000) == 0x4000) {
                data += 3;
            } else {
                data += 6;
            }
            if ((flags & 0x3000) == 0x2000) {
            } else if ((flags & 0x3000) == 0x1000) {
                data++;
                data += (half != 0);
                half ^= 1;
            } else {
                data += 3;
            }
        } else {
            cache->visited[(u8)temp] |= mask;
            positionBuffer = cache->currentBuffer;
            positionVertex = model->unk5C[index];
            positionOffset = positionVertex * sizeof(*nextPositions);
            nextPositions = (s16(*)[3])(positionOffset + (u8 *)cache->positions[(positionBuffer + 1) & 1]);
            if ((flags & 0xC000) == 0xC000) {
            } else if ((flags & 0xC000) == 0x8000) {
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                temp = value;
                if (value & 8) {
                    temp = value | ~0xF;
                }
                (*nextPositions)[0] += (f32)temp;
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                temp = value;
                if (value & 8) {
                    temp = value | ~0xF;
                }
                (*nextPositions)[1] += (f32)temp;
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                temp = value;
                if (value & 8) {
                    temp = value | ~0xF;
                }
                (*nextPositions)[2] += (f32)temp;
            } else if ((flags & 0xC000) == 0x4000) {
                READ_VERTEX_ANIM_BYTE(data, half, value);
                temp = value;
                if (value & 0x80) {
                    temp = value | ~0xFF;
                }
                (*nextPositions)[0] += (f32)temp;
                READ_VERTEX_ANIM_BYTE(data, half, value);
                temp = value;
                if (value & 0x80) {
                    temp = value | ~0xFF;
                }
                (*nextPositions)[1] += (f32)temp;
                READ_VERTEX_ANIM_BYTE(data, half, value);
                temp = value;
                if (value & 0x80) {
                    temp = value | ~0xFF;
                }
                (*nextPositions)[2] += (f32)temp;
            } else {
                if (half == 0) {
                    word = *data << 8;
                } else {
                    word = (u8)(*data & 0xF);
                    word = (word << 4) | (data[1] >> 4);
                    word <<= 8;
                }
                highPart = word;
                data++;
                if (half == 0) {
                    highPart |= *data;
                    word = highPart;
                } else {
                    lowByte = *data & 0xF;
                    lowByte = (lowByte << 4) | (data[1] >> 4);
                    highPart |= lowByte;
                    word = highPart;
                }
                data++;
                temp = word;
                (*nextPositions)[0] += (f32)temp;
                if (half == 0) {
                    word = *data << 8;
                } else {
                    word = (u8)(*data & 0xF);
                    word = (word << 4) | (data[1] >> 4);
                    word <<= 8;
                }
                highPart = word;
                data++;
                if (half == 0) {
                    highPart |= *data;
                    word = highPart;
                } else {
                    lowByte = *data & 0xF;
                    lowByte = (lowByte << 4) | (data[1] >> 4);
                    highPart |= lowByte;
                    word = highPart;
                }
                data++;
                temp = word;
                (*nextPositions)[1] += (f32)temp;
                if (half == 0) {
                    word = *data << 8;
                } else {
                    word = (u8)(*data & 0xF);
                    word = (word << 4) | (data[1] >> 4);
                    word <<= 8;
                }
                highPart = word;
                data++;
                if (half == 0) {
                    highPart |= *data;
                    word = highPart;
                } else {
                    lowByte = *data & 0xF;
                    lowByte = (lowByte << 4) | (data[1] >> 4);
                    highPart |= lowByte;
                    word = highPart;
                }
                data++;
                temp = word;
                (*nextPositions)[2] += (f32)temp;
            }
            normalBuffer = cache->currentBuffer;
            normalVertex = model->unk5C[index];
            normalOffset = normalVertex * sizeof(*nextNormals);
            nextNormals = (s8(*)[3])(normalOffset + (u8 *)cache->normals[(normalBuffer + 1) & 1]);
            if ((flags & 0x3000) == 0x2000) {
            } else if ((flags & 0x3000) == 0x1000) {
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                (*nextNormals)[0] += ((value & 8) ? value | 0xFFF0 : value);
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                (*nextNormals)[1] += ((value & 8) ? value | 0xFFF0 : value);
                READ_VERTEX_ANIM_NIBBLE(data, half, value);
                (*nextNormals)[2] += ((value & 8) ? value | 0xFFF0 : value);
            } else {
                READ_VERTEX_ANIM_BYTE(data, half, value);
                (*nextNormals)[0] += value;
                READ_VERTEX_ANIM_BYTE(data, half, value);
                (*nextNormals)[1] += value;
                READ_VERTEX_ANIM_BYTE(data, half, value);
                (*nextNormals)[2] += value;
            }
        }
        entries += 2;
    }
    cache->currentBuffer = (cache->currentBuffer + 1) & 1;
}

void func_80031324_main(HmfData *model, f32 time) {
    Vtx_t *source;
    Vtx_t *dest;
    s16 count;
    s16 i;
    s16 track;
    HmfDispData *shape;
    s16 *indices;
    s16(*positions)[3];
    s8(*normals)[3];

    if (model->unkB4 == NULL || model->unkB8 == NULL) {
        return;
    }
    source = (Vtx_t *)model->unk40;
    dest = (Vtx_t *)model->unk44[D_800D2008_main];
    count = model->unk18;
    for (i = 0; i < count; i++) {
        *dest = *source;
        source++;
        dest++;
    }
    source = (Vtx_t *)model->unk44[D_800D2008_main];
    if (time >= model->unkB8->unk02 - 1) {
        time = model->unkB8->unk02 - 1;
    }
    for (track = 0; track < model->unk24; track++) {
        shape = &model->unkB4[(track + model->unkB8)->unk04[(s16)time]];
        indices = shape->unk28;
        positions = (s16(*)[3])shape->unk2C;
        normals = (s8(*)[3])shape->unk30;
        count = shape->unk1C;
        for (i = 0; i < count; i++) {
            dest = &source[model->unk5C[*indices]];
            dest->ob[0] = (*positions)[0];
            dest->ob[1] = (*positions)[1];
            dest->ob[2] = (*positions)[2];
            if ((*normals)[0] != 0 || (*normals)[1] != 0 || (*normals)[2] != 0) {
                dest->cn[0] = (*normals)[0];
                dest->cn[1] = (*normals)[1];
                dest->cn[2] = (*normals)[2];
            }
            indices++;
            positions++;
            normals++;
        }
    }
}
