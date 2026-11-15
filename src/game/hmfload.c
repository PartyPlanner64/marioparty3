#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/mallocblock.h"
#include "gcc/string.h"
#include "game/hmfvertex.h"
#include "game/hu3d.h"
#include "game/hmfload.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/hmfanim.h"
#include "game/hmfdraw.h"

typedef struct {
    char unk00[6];
    s16 loopIndex;
    char unk08[6];
    s16 recordCount;
    char unk10[6];
    s16 mapCount;
    char unk18[6];
    s16 recordSize;
    char unk20[6];
    s16 unk3BCount;
    char unk28[4];
    s32 flagsMask;
} HmfLoadWork;

typedef union {
    s32 word;
    f32 single;
} HmfFloatBits;

u8 D_800A0540_main = 0;
u8 D_800A0541_main = 0;
u8 D_800A0542_main = 0;
s16 sceneLoadF = 0;

static u8 *ModeTop;
static u8 *VertexTop;
static u8 *FaceTop;
static u8 *ObjectTop;
static u8 *MaterialTop;
static u8 *ColorTop;
static u8 *AttributeTop;
static u8 *MotionTop;
static u8 *StringTable;
extern u8 Hu3DObjExtF;
extern u8 Hu3DLoadFlags;
extern s16 Hu3DModelTag;
extern s16 Hu3DModelDataTag;

s16 SkeletonLoad(HmfData *, void *);
void VertexLoad(HmfData *);
s16 MaterialLoad(HmfData *);
s16 AttributeLoad(HmfData *);
s16 MotionNodeLoad(HmfData *, u16, void *);
void FaceLoad(HmfData *, s16, s16, s16);
void FaceLoadSub(HmfModelData_Unk64_Unk60_Unk54_Struct *, u8 *, HmfData *, u16 *);
s32 ObjectLoad(HmfData *);
s32 MotionNameLoad(HmfData *);
void MapAttrLoad(HmfData *, void *, s16);
s32 CameraLoad(HmfData *, void *);
void SceneLoad(HmfData *);
void LightLoad(HmfData *, u8 *, s32);

void LoadHMF(HmfData *hmf, void *fileData, s32 flags) {
    s16 i;
    s16 recordCount;
    s16 motionCount;
    s16 mapCount;
    s16 recordSize;
    s16 unk3BCount;
    s32 flagsMask;
    s16 modelCount;
    u8 *file;
    char *fileHeader;
    u8 *record;
    u8 *recordStart;
    s16 extraCount;
    s16 objectIndex;
    HmfModelData_Unk64_Unk60_Struct *data;

    file = fileData;
    fileHeader = (char *)file;
    if (fileHeader[0] != 'F' || fileHeader[1] != 'O') {
        osSyncPrintf("Unknown Hmf Format!\n");
    }
    hmf->unk2C = file;
    hmf->unk34 = file + 0xC;
    hmf->unk30 = hmf->unk2C + (hmf->unk2C[5] << 0x10) + (hmf->unk2C[6] << 8) + hmf->unk2C[7] + 8;

    VertexTop = HmfChunkSearch(0x56545831, hmf->unk34, hmf->unk30);
    FaceTop = HmfChunkSearch(0x46414331, hmf->unk34, hmf->unk30);
    ObjectTop = HmfChunkSearch(0x4F424A31, hmf->unk34, hmf->unk30);
    MaterialTop = HmfChunkSearch(0x4D415431, hmf->unk34, hmf->unk30);
    ColorTop = HmfChunkSearch(0x434F4C31, hmf->unk34, hmf->unk30);
    AttributeTop = HmfChunkSearch(0x41545231, hmf->unk34, hmf->unk30);
    MotionTop = HmfChunkSearch(0x4D544E31, hmf->unk34, hmf->unk30);
    StringTable = HmfChunkSearch(0x53545247, hmf->unk34, hmf->unk30);
    hmf->unk38 = HmfChunkSearch(0x4D415031, hmf->unk34, hmf->unk30);

    hmf->unk16 = 0;
    hmf->unk14 = 0;
    hmf->unk12 = 0;
    hmf->unk10 = 0;
    hmf->unk40 = NULL;
    hmf->unk3C = NULL;
    hmf->unkB0 = NULL;
    hmf->unk9C = NULL;
    hmf->unk0A = 0;
    hmf->unkBC = NULL;
    hmf->unk5C = NULL;
    hmf->unk58 = NULL;
    hmf->unkCC = NULL;
    hmf->unkD0 = NULL;

    ModeTop = HmfChunkSearch(0x4D4F4445, hmf->unk34, hmf->unk30);
    SceneLoad(hmf);
    if (VertexTop != NULL) {
        VertexLoad(hmf);
    }
    if (MaterialTop != NULL) {
        MaterialLoad(hmf);
    }
    Hu3DLoadFlags = flags;
    Hu3DTexLoad(hmf);
    if (AttributeTop != NULL) {
        AttributeLoad(hmf);
    }
    hmf->unk90 = NULL;
    hmf->unk8C = NULL;
    hmf->unk98 = NULL;

    record = ObjectTop + 8;
    recordCount = record[0];
    recordCount = (recordCount << 8) + record[1];
    hmf->unk64 = 0;
    hmf->unk80 = (HmfMotionNode *)-1;
    if ((recordCount << 0x10) == 0) {
        hmf->unk16 = 0;
        hmf->unk10 = 0;
        return;
    }

    record += 4;
    recordStart = record;
    i = 0;
    unk3BCount = 0;
    mapCount = 0;
    modelCount = 0;
    motionCount = 0;
    extraCount = 0;
    for (; i < recordCount; i++) {
        switch (record[2]) {
            case 0x3A:
                modelCount++;
                break;

            case 0x3D:
                motionCount++;
                break;

            case 0x61:
                mapCount++;
                break;

            case 0x5D:
                extraCount++;
                break;

            case 0x3B:
                unk3BCount++;
                break;
        }
        record += ((record[0] << 8) + record[1]) + 2;
    }

    if (motionCount != 0) {
        hmf->unk80 = HuMemAllocTag(recordCount * sizeof(HmfMotionNode), Hu3DModelTag);
    }

    if (flags & 0x200000) {
        if (mapCount != 0) {
            hmf->unkC4 = HuMemAllocTag(mapCount * sizeof(HmfMapData), Hu3DModelTag);
            hmf->unk26 = mapCount;
        }
        if (extraCount != 0) {
            hmf->unkBC = HuMemAllocTag(sizeof(HmfData_UnkBC), Hu3DModelTag);
        } else {
            hmf->unkBC = NULL;
        }
    } else {
        hmf->unkC4 = NULL;
        hmf->unkBC = NULL;
    }

    if (unk3BCount != 0) {
        hmf->unk20 = unk3BCount;
        hmf->unkC0 = HuMemAllocTag((unk3BCount * 8) - unk3BCount, Hu3DModelTag);
    } else {
        hmf->unkC0 = NULL;
        hmf->unk20 = 0;
    }

    hmf->unk60 = HuMemAllocTag(modelCount * sizeof(HmfModelData_Unk64_Unk60_Struct), Hu3DModelTag);
    record = recordStart;
    hmf->unk1C = 0;
    i = 0;
    unk3BCount = 0;
    objectIndex = 0;
    mapCount = 0;
    motionCount = 0;
    for (; i < recordCount; i++) {
        switch (record[2]) {
            case 0x3A: {
                s16 linkIndex;
                s16 vertexCount;
                s32 attrMask;

                recordStart = record + 5;
                recordSize = (record[0] << 8) + record[1];
                linkIndex = (record[6] << 8) + record[7];
                hmf->unk60[objectIndex].unk26 = GetString(hmf, &hmf->unk60[objectIndex], (record[3] << 8) + record[4]);
                data = &hmf->unk60[objectIndex];
                vertexCount = (record[8] << 8) + record[9];
                data->unk22 = vertexCount;
                hmf->unk1C += vertexCount;
                hmf->unk60[objectIndex].unk50 = 0x2B00;
                hmf->unk60[objectIndex].unk58 = NULL;
                hmf->unk60[objectIndex].unk20 = -1;
                if (hmf->unk14 != 0) {
                    FaceLoad(hmf, objectIndex, linkIndex, vertexCount);
                    if (vertexCount != 0) {
                        hmf->unk60[objectIndex].unk1C = hmf->unk60[objectIndex].unk54->unk32;
                    } else {
                        hmf->unk60[objectIndex].unk1C = 0xFF;
                    }
                }
                attrMask = hmf->unk60[objectIndex].unk50 & 0x10000;
                hmf->unk60[objectIndex].unk24 = 0;
                if (((Hu3DObjExtF != 0) & (recordSize >= 0x3A)) && recordStart[0x35] != 0 && recordStart[0x36] == 0) {
                    if (recordSize == 0x3E) {
                        hmf->unk60[objectIndex].unk50 = (recordStart[0x37] << 0x18) | (recordStart[0x39] << 8) | recordStart[0x3A] | attrMask;
                    } else {
                        hmf->unk60[objectIndex].unk50 = (recordStart[0x37] << 0x18) | attrMask;
                    }
                    hmf->unk60[objectIndex].unk24 = recordStart[0x38];
                }
                objectIndex++;
                break;
            }

            case 0x10:
                SkeletonLoad(hmf, record + 5);
                break;

            case 0x3D:
                MotionNodeLoad(hmf, motionCount, record + 5);
                motionCount++;
                break;

            case 0x61: {
                if (flags & 0x200000) {
                    hmf->unkC4[mapCount].unk1C = GetString(hmf, &hmf->unkC4[mapCount], (record[3] << 8) + record[4]);
                    MapAttrLoad(hmf, record + 5, mapCount);
                    mapCount++;
                }
                break;
            }

            case 0x5D:
                if (flags & 0x200000) {
                    CameraLoad(hmf, record + 5);
                }
                break;

            case 0x3B:
                LightLoad(hmf, record + 5, unk3BCount);
                unk3BCount++;
                break;
        }
        record += ((record[0] << 8) + record[1]) + 2;
    }

    hmf->unk10 = objectIndex;
    hmf->unk16 = motionCount;
    Hu3DMtxCalc(hmf);
    Hu3DModelAnimLoad(hmf);
    ObjectLoad(hmf);
}

void MotionNodeFree(HmfData *hmf) {
    s16 i;

    if (hmf->unk80 != (HmfMotionNode *)-1) {
        if (hmf->unk16 > 0) {
            i = 0;
            do {
                HuMemFree(hmf->unk80[i].unk50);
                i++;
            } while (i < hmf->unk16);
        }
        HuMemFree(hmf->unk80);

    } else if (hmf->unk64 != 0) {
        HuMemFree(hmf->unk68);
    }
    HuMemFree(hmf->unk60);
}

s16 SkeletonLoad(HmfData *hmf, void *arg1) {
    u8 *data;
    u8 *argData;
    HmfSkeletonNode *entry;
    s16 target;
    s16 count;
    s16 i;
    s32 value;

    argData = arg1;
    target = (argData[0] << 8) + argData[1];
    data = hmf->unk34;
    while (data < hmf->unk30) {
        data = HmfChunkSearch(0x534B4C31, data, hmf->unk30);
        if (data == NULL) {
            return 0;
        }
        if (((data[8] << 8) + data[9]) == target) {
            break;
        }
        data = HmfChunkNext(data + 4);
    }

    count = data[0xA];
    hmf->unk64 = count;
    hmf->unk68 = HuMemAllocTag(count * sizeof(HmfSkeletonNode), Hu3DModelTag);
    data += 0xB;
    for (i = 0; i < count; i++) {
        entry = &hmf->unk68[i];
        entry->unk00 = HmfRecordCount(hmf, (data[1] << 8) + data[2]);
        entry->unk48 = hmf;
        data += (data[0] << 1) + 1;
        value = data[0];
        value <<= 0x18;
        value += data[1] << 0x10;
        value += data[2] << 8;
        *(s32 *)&entry->unk08.x = value + data[3];
        value = data[4];
        value <<= 0x18;
        value += data[5] << 0x10;
        value += data[6] << 8;
        *(s32 *)&entry->unk08.y = value + data[7];
        value = data[8];
        value <<= 0x18;
        value += data[9] << 0x10;
        value += data[0xA] << 8;
        *(s32 *)&entry->unk08.z = value + data[0xB];
        data += 0xC;
        value = data[0];
        value <<= 0x18;
        value += data[1] << 0x10;
        value += data[2] << 8;
        *(s32 *)&entry->unk14.x = value + data[3];
        value = data[4];
        value <<= 0x18;
        value += data[5] << 0x10;
        value += data[6] << 8;
        *(s32 *)&entry->unk14.y = value + data[7];
        value = data[8];
        value <<= 0x18;
        value += data[9] << 0x10;
        value += data[0xA] << 8;
        *(s32 *)&entry->unk14.z = value + data[0xB];
        data += 0xC;
        value = data[0];
        value <<= 0x18;
        value += data[1] << 0x10;
        value += data[2] << 8;
        *(s32 *)&entry->scale.x = value + data[3];
        value = data[4];
        value <<= 0x18;
        value += data[5] << 0x10;
        value += data[6] << 8;
        *(s32 *)&entry->scale.y = value + data[7];
        value = data[8];
        value <<= 0x18;
        value += data[9] << 0x10;
        value += data[0xA] << 8;
        *(s32 *)&entry->scale.z = value + data[0xB];
        data += 0x18;
        entry->unk02 = (data[0] << 8) + data[1];
        entry->unk04 = (data[2] << 8) + data[3];
        entry->pos = entry->unk08;
        entry->rot = entry->unk14;
        entry->unk45 = 0;
        entry->unk44 = 0;
        data += 5;
    }
    return count;
}

s16 HmfRecordCount(void *arg0, s16 arg1) {
    u8 *base;
    u8 *data;
    s16 recordCount;
    s16 i;
    s32 modelCount;
    s32 motionCount;
    s32 mapCount;
    s32 id;

    base = ObjectTop;
    recordCount = (base[8] << 8) + base[9];
    data = base + 0xC;
    i = 0;
    modelCount = 0;
    motionCount = 0;
    mapCount = 0;
    if (recordCount > 0) {
        do {
            switch (data[2]) {
                case 0x3A:
                    id = (data[3] << 8) + data[4];
                    if (arg1 == id) {
                        return modelCount;
                    }
                    modelCount++;
                    break;

                case 0x3D:
                    id = (data[3] << 8) + data[4];
                    if (arg1 == id) {
                        return motionCount | 0x8000;
                    }
                    motionCount++;
                    break;

                case 0x61:
                    id = (data[3] << 8) + data[4];
                    if (arg1 == id) {
                        return mapCount | 0x4000;
                    }
                    mapCount++;
                    break;
            }
            data += ((data[0] << 8) + data[1]) + 2;
            i++;
        } while (i < recordCount);
    }
    return -1;
}

void VertexLoad(HmfData *hmf) {
    u8 *data;
    s16 count;
    s16 count2;
    s16 *coords;
    s8 *normals;
    s32 coordBytes;
    HmfFloatBits scale;
    s32 value;
    s16 i;

    data = VertexTop;
    count = (data[8] << 8) + data[9];
    hmf->unk14 = count;
    count2 = count;
    if (count2 != 0) {
        coordBytes = count2 << 1;
        coordBytes += count2;
        hmf->unk50 = HuMemAllocTag(coordBytes * 2, Hu3DModelDataTag);
        coords = hmf->unk50[0];
        hmf->unk54 = HuMemAllocTag(coordBytes, Hu3DModelDataTag);
        normals = hmf->unk54[0];
        value = data[0xC] << 0x18;
        value += data[0xD] << 0x10;
        value += data[0xE] << 8;
        scale.word = value + data[0xF];
        data += 0x10;
        i = 0;
        if (count2 > 0) {
            do {
                *coords++ = (s16)((f32)(s16)((data[0] << 8) + data[1]) * scale.single);
                data += 2;
                *coords++ = (s16)((f32)(s16)((data[0] << 8) + data[1]) * scale.single);
                data += 2;
                *coords++ = (s16)((f32)(s16)((data[0] << 8) + data[1]) * scale.single);
                data += 2;
                *normals++ = *data++;
                *normals++ = *data++;
                *normals++ = *data++;
                i++;
            } while (i < count);
        }
    }
}

s16 MaterialLoad(HmfData *hmf) {
    u8 *records;
    u8 *src;
    HmfMaterialData *entry;
    s16 count;
    s16 i;

    count = (MaterialTop[8] << 8) + MaterialTop[9];
    if (count == 0) {
        MaterialTop = 0;
        return 0;
    }
    hmf->unk1E = count;
    hmf->unk88 = HuMemAllocTag(count * sizeof(HmfMaterialData), Hu3DModelTag);
    records = MaterialTop + 0xA;
    for (i = 0; i < count; ++i) {
        entry = &hmf->unk88[i];
        entry->unk00 = i;
        entry->unk09 = 0;
        src = ColorTop + (((records[0] << 8) + records[1]) * 4 + 0xA);
        entry->unk01 = ((f32)src[0] > 255.0f) ? 255 : (u32)(f32)src[0];
        entry->unk02 = ((f32)src[1] > 255.0f) ? 255 : (u32)(f32)src[1];
        entry->unk03 = ((f32)src[2] > 255.0f) ? 255 : (u32)(f32)src[2];
        entry->unk04 = src[3];
        src = ColorTop + (((records[2] << 8) + records[3]) * 4 + 0xA);
        entry->unk05 = ((f32)src[0] > 255.0f) ? 255 : (u32)(f32)src[0];
        entry->unk06 = ((f32)src[1] > 255.0f) ? 255 : (u32)(f32)src[1];
        entry->unk07 = ((f32)src[2] > 255.0f) ? 255 : (u32)(f32)src[2];
        entry->unk08 = src[3];
        if (entry->unk08 != 255) {
            entry->unk09 |= 1;
            entry->unk0A = entry->unk08;
        } else {
            entry->unk0A = 255;
        }
        records += 0xC;
    }
    return count;
}

s16 AttributeLoad(HmfData *hmf) {
    u8 *data;
    u8 *colorData;
    HmfData_Unk84_Entry *entry;
    void *temp;
    s16 count;
    s16 i;
    s8 type;

    count = (AttributeTop[8] << 8) + AttributeTop[9];
    hmf->unk84 = HuMemAllocTag(count * sizeof(HmfData_Unk84_Entry), Hu3DModelTag);
    temp = HuMemAlloc(count * sizeof(s16));
    data = AttributeTop + 0xA;
    hmf->unk12 = count;
    for (i = 0; i < count; i++) {
        s8 fill;

        entry = &hmf->unk84[i];
        type = data[2];
        entry->unk0[0] = type;
        colorData = ColorTop + (((data[3] << 8) + data[4]) * 4 + 0xA);
        if (type == 0x2B) {
            entry->unk5[0] = colorData[0];
            entry->unk5[1] = colorData[1];
            entry->unk5[2] = colorData[2];
            entry->unk5[3] = colorData[3];
        } else {
            entry->unk5[3] = 0;
            entry->unk5[2] = 0;
            entry->unk5[1] = 0;
            entry->unk5[0] = 0;
        }
        switch (data[5]) {
            case 0x2D:
                entry->unk0[1] = 0;
                break;

            case 0x2E:
                entry->unk0[1] = 2;
                break;

            default:
                entry->unk0[1] = 1;
                break;
        }
        switch (data[6]) {
            case 0x2D:
                entry->unk0[2] = 0;
                break;

            case 0x2E:
                entry->unk0[2] = 2;
                break;

            default:
                entry->unk0[2] = 1;
                break;
        }
        entry->unkC = Hu3DTexSearchIdx(hmf, (data[0xA] << 8) + data[0xB]);
        fill = -1;
        entry->unk3 = fill;
        entry->unk4 = fill;
        entry->unk9 = 0xFF;
        data += ((data[0] << 8) + data[1]) + 2;
    }
    HuMemFree(temp);
    return count;
}

s16 MotionNodeLoad(HmfData *hmf, u16 motionIndex, void *arg2) {
    u8 *data;
    HmfMotionNode *entry;
    s16 count;
    s16 count2;
    s32 value;
    s16 i;

    data = arg2;
    entry = &hmf->unk80[motionIndex];
    entry->unk00 = count2 = (data[0] << 8) + data[1];
    count = count2;
    entry->unk50 = HuMemAllocTag(count2 * sizeof(s16), Hu3DModelTag);
    data += 2;
    for (i = 0; i < count; i++) {
        entry->unk50[i] = HmfRecordCount(hmf, (data[0] << 8) + data[1]);
        data += 2;
    }
    entry->unk54 = hmf;
    value = data[0];
    value <<= 0x18;
    value += data[1] << 0x10;
    value += data[2] << 8;
    *(s32 *)&entry->basePos.x = value + data[3];
    value = data[4];
    value <<= 0x18;
    value += data[5] << 0x10;
    value += data[6] << 8;
    *(s32 *)&entry->basePos.y = value + data[7];
    value = data[8];
    value <<= 0x18;
    value += data[9] << 0x10;
    value += data[0xA] << 8;
    *(s32 *)&entry->basePos.z = value + data[0xB];
    data += 0xC;
    value = data[0];
    value <<= 0x18;
    value += data[1] << 0x10;
    value += data[2] << 8;
    *(s32 *)&entry->baseRot.x = value + data[3];
    value = data[4];
    value <<= 0x18;
    value += data[5] << 0x10;
    value += data[6] << 8;
    *(s32 *)&entry->baseRot.y = value + data[7];
    value = data[8];
    value <<= 0x18;
    value += data[9] << 0x10;
    value += data[0xA] << 8;
    *(s32 *)&entry->baseRot.z = value + data[0xB];
    data += 0xC;
    value = data[0];
    value <<= 0x18;
    value += data[1] << 0x10;
    value += data[2] << 8;
    *(s32 *)&entry->baseScale.x = value + data[3];
    value = data[4];
    value <<= 0x18;
    value += data[5] << 0x10;
    value += data[6] << 8;
    *(s32 *)&entry->baseScale.y = value + data[7];
    value = data[8];
    value <<= 0x18;
    value += data[9] << 0x10;
    value += data[0xA] << 8;
    *(s32 *)&entry->baseScale.z = value + data[0xB];
    entry->pos = entry->basePos;
    entry->rot = entry->baseRot;
    entry->scale = entry->baseScale;
    entry->unk4E = 0;
    entry->unk4D = 0;
    entry->unk4C = 0;
    return count;
}

u8 *HmfChunkSearch(s32 tag, void *start, void *end) {
    u8 *cur;
    u8 *endPtr;
    s32 value;

    cur = start;
    endPtr = end;
    if (cur < endPtr) {
        do {
            value = cur[0];
            value <<= 0x18;
            value += cur[1] << 0x10;
            value += cur[2] << 8;
            value += cur[3];
            if (tag == value) {
                return cur;
            }
            cur += 4;
            value = cur[0];
            value <<= 0x18;
            value += cur[1] << 0x10;
            value += cur[2] << 8;
            value += cur[3];
            value += 4;
            cur += value;
            cur += (u32)cur & 1;
        } while (cur < endPtr);
    }
    return NULL;
}

void *HmfChunkNext(void *arg0) {
    u8 *data;
    s32 value;

    data = arg0;
    value = data[1] << 0x10;
    value += data[2] << 8;
    value += data[3];
    value += 4;
    data += value;
    return data + ((u32)data & 1);
}

void FaceLoad(HmfData *hmf, s16 objectIndex, s16 linkIndex, s16 faceCount) {
    u8 *record;
    u8 *next;
    HmfModelData_Unk64_Unk60_Unk54_Struct *faces;
    s16 *p;
    s16 *bounds;
    s16 pointCount;
    u16 flags;
    s16 v;
    s16 minX;
    s16 minY;
    s16 minZ;
    s16 maxX;
    s16 maxY;
    s16 maxZ;
    s16 i;
    s16 j;

    if (hmf->unk14 == 0) {
        return;
    }

    hmf->unk60[objectIndex].unk54 = HuMemAllocTag(faceCount * sizeof(HmfModelData_Unk64_Unk60_Unk54_Struct), Hu3DModelDataTag);
    faces = hmf->unk60[objectIndex].unk54;
    record = FaceTop + 0x10;
    for (i = 0; i < linkIndex; i++) {
        if (record[0] == 0x16) {
            next = record + 0x2A;
        } else if (record[0] != 0x35) {
            next = record + 0xC;
        } else {
            next = record + 0x36;
        }
        record = next;
    }

    minX = minY = minZ = 0x7FFF;
    maxX = maxY = maxZ = -0x8000;
    flags = 0;

    for (i = 0; i < faceCount; i++) {
        FaceLoadSub(&faces[i], record, hmf, &flags);
        if (record[0] == 0x16) {
            pointCount = 3;
        } else if (record[0] == 0x35) {
            pointCount = 4;
        } else {
            pointCount = 2;
        }

        for (j = 0; j < pointCount; j++) {
            p = hmf->unk50[faces[i].unk04[j]];
            v = p[0];
            if (minX > v) {
                minX = v;
            }
            if (maxX < v) {
                maxX = v;
            }
            v = p[1];
            if (minY > v) {
                minY = v;
            }
            if (maxY < v) {
                maxY = v;
            }
            v = p[2];
            if (minZ > v) {
                minZ = v;
            }
            if (maxZ < v) {
                maxZ = v;
            }
        }
        switch (record[0]) {
            case 0x35:
                next = record + 0x36;
                break;
            case 0x16:
                next = record + 0x2A;
                break;
            default:
                next = record + 0xC;
                break;
        }
        record = next;
    }

    hmf->unk60[objectIndex].unk50 =
        (flags & 1) ? (hmf->unk60[objectIndex].unk50 | 0x10000) : hmf->unk60[objectIndex].unk50;
    bounds = hmf->unk60[objectIndex].boundsMin;
    bounds[0] = minX;
    bounds[1] = minY;
    bounds[2] = minZ;
    bounds = hmf->unk60[objectIndex].boundsMax;
    bounds[0] = maxX;
    bounds[1] = maxY;
    bounds[2] = maxZ;
}

void FaceLoadSub(HmfModelData_Unk64_Unk60_Unk54_Struct *arg0, u8 *arg1, HmfData *arg2, u16 *arg3) {
    s32 *values1;
    s32 *values2;
    s8 *normals;
    u8 *attr;
    u16 *coords1;
    u16 *coords2;
    u16 *coords3;
    s16 count;
    s16 i;
    s16 hasColor;
    s16 step;
    s32 temp;
    s32 value;

    switch (arg1[0]) {
        case 0x35:
            count = 4;
            step = 0xC;
            break;
        case 0x16:
            count = 3;
            step = 0xC;
            break;
        default:
            count = 2;
            step = 4;
            break;
    }
    arg0->unk00 = count;
    arg1++;
    values1 = (s32 *)arg0->unk0C;
    values2 = (s32 *)arg0->unk1C;
    i = 0;
    hasColor = 0;
    while (i < count) {
        arg0->unk04[i] = (arg1[0] << 8) + arg1[1];
        arg0->unk2C[i] = arg1[3];
        value = arg1[4];
        value <<= 0x18;
        value += arg1[5] << 0x10;
        value += arg1[6] << 8;
        *values1++ = value + arg1[7];
        value = arg1[8];
        value <<= 0x18;
        value += arg1[9] << 0x10;
        value += arg1[0xA] << 8;
        *values2++ = value + arg1[0xB];
        arg0->unk04[i] = (arg1[0] << 8) + arg1[1];
        if (arg1[3] != 0xFF) {
            temp = arg0->unk04[i];
            normals = arg2->unk54[0];
            normals[temp * 3 + 0] = normals[temp * 3 + 1] = normals[temp * 3 + 2] = 0;
            hasColor = -1;
        }
        arg1 += step;
        i++;
    }
    arg0->unk30 = (arg1[0] << 8) + arg1[1];
    if (hasColor != 0) {
        arg0->unk00 |= 0x80;
    }
    coords1 = (u16 *)arg2->unk50[arg0->unk04[0]];
    coords2 = (u16 *)arg2->unk50[arg0->unk04[1]];
    coords3 = (u16 *)arg2->unk50[arg0->unk04[2]];
    FaceNormalCalc(arg0->unk01, coords1, coords2, coords3);
    if (MaterialTop != NULL) {
        *arg3 |= arg2->unk88[arg0->unk30].unk09;
        if (count == 2) {
            arg0->unk32 = -1;
        } else {
            arg0->unk32 = (arg1[2] << 8) + arg1[3];
            if (arg0->unk32 != -1) {
                attr = (u8 *)arg2->unk84[arg0->unk32].unkC;
                if (((attr[0x1C] - 3) < 2U) || attr[0x1D] == 3) {
                    *arg3 |= 1;
                }
            }
        }
    }
}

void FaceNormalCalc(s8 *arg0, u16 *arg1, u16 *arg2, u16 *arg3) {
    s32 diffX1;
    s32 diffX2;
    s32 diffY1;
    s32 diffY2;
    s32 diffZ1;
    s32 diffZ2;
    f32 crossX;
    f32 crossY;
    f32 crossZ;
    f32 scale;
    s32 a;

    a = arg1[0];
    diffX1 = a - arg2[0];
    diffX2 = arg3[0] - a;
    a = arg1[1];
    diffY1 = a - arg2[1];
    diffY2 = arg3[1] - a;
    a = arg1[2];
    diffZ1 = a - arg2[2];
    diffZ2 = arg3[2] - a;

    crossX = (s16)diffY1 * (s16)diffZ2 - (s16)diffZ1 * (s16)diffY2;
    crossY = (s16)diffZ1 * (s16)diffX2 - (s16)diffX1 * (s16)diffZ2;
    crossZ = (s16)diffX1 * (s16)diffY2 - (s16)diffY1 * (s16)diffX2;

    scale = 127.0f / HuSqrtf(crossX * crossX + crossY * crossY + crossZ * crossZ);

    arg0[0] = (crossX != 0.0f) ? (crossX * scale) : 0;
    arg0[1] = (crossY != 0.0f) ? (crossY * scale) : 0;
    arg0[2] = (crossZ != 0.0f) ? (crossZ * scale) : 0.0f;
}

s16 GetString(HmfData *hmf, void *arg1, s16 index) {
    u8 *data;
    u8 *src;
    u8 *dst;
    s16 sum;
    s16 i;
    s16 j;
    s16 len;

    data = StringTable;
    sum = data[8];
    sum = (sum << 8) + data[9];
    if (sum == 0) {
        ((u8 *)arg1)[0] = 0;
        return 0;
    }
    data += 0xA;
    src = data + sum;
    for (i = 0; i < index; i++) {
        src += data[0];
        data++;
    }
    len = data[0];
    dst = arg1;
    i = 0;
    sum = 0;
    j = 0;
    for (; i < len; i++) {
        if (j >= 0x1B) {
            *dst = 0;
            return sum;
        }
        if (src[0] == 0x2F) {
            dst = arg1;
            sum = 0;
            j = 0;
            src++;
        } else {
            *dst = src[0];
            src++;
            sum += (j + 1) * *dst;
            dst++;
            j++;
        }
    }
    *dst = 0;
    return sum;
}

s16 HmfNameHash(const u8 *arg0) {
    s32 sum = 0;
    s16 i = 1;
    u8 c = arg0[0];

    while (c != 0 && i < 28) {
        sum += i * c;
        arg0++;
        i++;
        c = arg0[0];
    }
    return sum;
}

s32 ObjectLoad(HmfData *hmf) {
    u8 *data;
    u8 *src;
    HmfDispData *entry;
    s16 *indices;
    s16 *coords;
    u8 *colors;
    HmfFloatBits scale;
    s32 size;
    s16 dispCount;
    s16 dispIndex;
    s16 vtxCount;
    s16 count;
    s16 j;

    data = hmf->unk34;
    dispCount = 0;

    while (1) {
        data = HmfChunkSearch(0x44495350, data, hmf->unk30);
        if (data == NULL) {
            break;
        }
        data = HmfChunkNext(data + 4);
        dispCount++;
    }

    if (dispCount == 0) {
        hmf->unk22 = 0;
        hmf->unkB4 = NULL;
        return 0;
    }

    hmf->unkB4 = HuMemAllocTag(dispCount * sizeof(HmfDispData), Hu3DModelTag);
    hmf->unk22 = dispCount;
    data = hmf->unk34;
    dispIndex = 0;

    while (1) {
        data = HmfChunkSearch(0x44495350, data, hmf->unk30);

        if (data == NULL) {
            break;
        }

        if (data[0xC] == 0x43) {
            entry = &hmf->unkB4[dispIndex];
            entry->unk1E = GetString(hmf, entry, (data[8] << 8) + data[9]);
            vtxCount = (data[0xA] << 8) + data[0xB];
            count = vtxCount;
            entry->unk1C = count;
            size = vtxCount * 2;
            indices = HuMemAllocTag(size, Hu3DModelTag);
            entry->unk28 = indices;
            size += vtxCount;
            coords = HuMemAllocTag(size * 2, Hu3DModelTag);
            entry->unk2C = coords;
            colors = HuMemAllocTag(size, Hu3DModelTag);
            entry->unk30 = colors;
            entry->unk20 = (data[0xD] << 8) + data[0xE];
            scale.word = (data[0xF] << 0x18) + (data[0x10] << 0x10) + (data[0x11] << 8) + data[0x12];
            scale.single *= 5.0f;
            entry->unk24 = scale.single;
            src = data + 0x13;
            for (j = 0; j < count; j++) {
                indices[0] = (src[0] << 8) + src[1];
                coords[0] = (s16)((src[2] << 8) + src[3]) * scale.single;
                coords[1] = (s16)((src[4] << 8) + src[5]) * scale.single;
                coords[2] = (s16)((src[6] << 8) + src[7]) * scale.single;
                if (hmf->unk54[indices[0]][0] == 0 && hmf->unk54[indices[0]][1] == 0 && hmf->unk54[indices[0]][2] == 0) {
                    colors[0] = colors[1] = colors[2] = 0;
                } else {
                    colors[0] = src[8];
                    colors[1] = src[9];
                    colors[2] = src[0xA];
                }
                indices++;
                coords += 3;
                colors += 3;
                src += 0xB;
            }
        }
        data = HmfChunkNext(data + 4);
        dispIndex++;
    }
    MotionNameLoad(hmf);
    return 1;
}

s32 MotionNameLoad(HmfData *hmf) {
    char buf[0x20];
    u8 *data;
    u8 *sub2;
    u8 *cur;
    HmfMtnData *entry;
    s16 id;
    s16 cnt;
    s16 count2;
    s16 mtnCount;
    s16 subCount;
    s32 subCount1;
    s16 i;
    s16 k;
    s16 m;

    data = hmf->unk34;
    mtnCount = 0;
    while (1) {
        data = HmfChunkSearch(0x4D544E31, data, hmf->unk30);
        if (data == NULL) {
            break;
        }
        cur = data + 0xD;
        subCount1 = data[0xA];
        for (i = 0; i < subCount1; i++) {
            if (cur[2] == 0xA) {
                mtnCount++;
            }
            cur += ((cur[0] << 8) + cur[1]) + 2;
        }
        data = HmfChunkNext(data + 4);
    }
    if (mtnCount == 0) {
        hmf->unkB8 = NULL;
        return 0;
    }
    hmf->unkB8 = HuMemAllocTag(mtnCount * sizeof(HmfMtnData), Hu3DModelTag);
    hmf->unk24 = mtnCount;
    data = hmf->unk34;
    mtnCount = 0;
    while (1) {
        data = HmfChunkSearch(0x4D544E31, data, hmf->unk30);
        if (data == NULL) {
            break;
        }
        subCount = data[0xA];
        sub2 = data + 0xD;
        entry = &hmf->unkB8[mtnCount];
        for (i = 0; i < subCount; i++) {
            cur = sub2;
            sub2 += ((cur[0] << 8) + cur[1]) + 2;
            if (cur[2] == 0xA) {
                cur += 3;
                entry->unk00 = (cur[0] << 8) + cur[1];
                cnt = (cur[2] << 8) + cur[3];
                count2 = cnt;
                entry->unk02 = count2;
                entry->unk04 = HuMemAllocTag(cnt * 2, Hu3DModelTag);
                cur += 4;
                for (k = 0; k < count2; k++) {
                    id = GetString(hmf, buf, (cur[0] << 8) + cur[1]);
                    for (m = 0; m < hmf->unk22; m++) {
                        if (id == hmf->unkB4[m].unk1E && strcmp(hmf->unkB4[m].unk00, buf) == 0) {
                            break;
                        }
                    }
                    if (m == hmf->unk22) {
                        entry->unk04[k] = 0;
                    } else {
                        entry->unk04[k] = m;
                    }
                    cur += 2;
                }
                mtnCount++;
            }
        }
        data = HmfChunkNext(data + 4);
    }
    return 1;
}

void MapAttrLoad(HmfData *hmf, void *arg1, s16 index) {
    u8 *data;
    HmfMapData *entry;
    s32 value;

    data = arg1;
    entry = &hmf->unkC4[index];
    value = ((data[0] << 0x18) + (data[1] << 0x10)) + (data[2] << 8);
    entry->unk20 = value + data[3];
    value = 0x10;
    value = ((data[4] << 0x18) + (data[5] << value)) + (data[6] << 8);
    entry->unk24 = value + data[7];
    value = ((data[8] << 0x18) + (data[9] << 0x10)) + (data[10] << 8);
    entry->unk28 = value + data[11];
}

s32 CameraLoad(HmfData *hmf, void *arg1) {
    char buf[0x20];
    u8 *data;
    HmfData_UnkBC *env;
    s16 id;
    s16 m;
    s32 temp1, temp2, temp3, temp4;

    data = arg1;
    env = hmf->unkBC;
    id = GetString(hmf, buf, (data[0] << 8) + data[1]);
    for (m = 0; m < hmf->unk26; m++) {
        if (id == hmf->unkC4[m].unk1C && strcmp(hmf->unkC4[m].unk00, buf) == 0) {
            break;
        }
    }
    if (m == hmf->unk26) {
        return 0;
    }
    env->unk08 = *(f32 *)&hmf->unkC4[m].unk20;
    env->unk0C = *(f32 *)&hmf->unkC4[m].unk24;
    env->unk10 = *(f32 *)&hmf->unkC4[m].unk28;
    env->unk00 = m;
    id = GetString(hmf, buf, (data[2] << 8) + data[3]);
    for (m = 0; m < hmf->unk26; m++) {
        if (id == hmf->unkC4[m].unk1C && strcmp(hmf->unkC4[m].unk00, buf) == 0) {
            break;
        }
    }
    if (m == hmf->unk26) {
        return 0;
    }
    env->unk14 = *(f32 *)&hmf->unkC4[m].unk20;
    env->unk18 = *(f32 *)&hmf->unkC4[m].unk24;
    env->unk1C = *(f32 *)&hmf->unkC4[m].unk28;
    env->unk02 = m;
    id = GetString(hmf, buf, (data[4] << 8) + data[5]);
    for (m = 0; m < hmf->unk26; m++) {
        if (id == hmf->unkC4[m].unk1C && strcmp(hmf->unkC4[m].unk00, buf) == 0) {
            break;
        }
    }
    if (m == hmf->unk26) {
        return 0;
    }
    env->unk20 = *(f32 *)&hmf->unkC4[m].unk20;
    env->unk24 = *(f32 *)&hmf->unkC4[m].unk24;
    env->unk28 = *(f32 *)&hmf->unkC4[m].unk28;
    env->unk04 = m;
    temp1 = data[6] << 0x18;
    temp1 += data[7] << 0x10;
    temp1 += data[8] << 0x8;
    temp2 = data[9];
    temp1 += temp2;
    temp2 = temp1;
    temp1 = temp2;

    *((s32 *)(&env->unk2C)) = temp1;

    return 1;
}

void SceneLoad(HmfData *hmf) {
    u8 *data;
    s32 value;

    data = ModeTop;
    value = data[0xC];
    value <<= 0x18;
    value += data[0xD] << 0x10;
    value += data[0xE] << 8;
    value += data[0xF];
    if (value & 2) {
        sceneLoadF = 1;
    } else {
        sceneLoadF = 0;
    }
    if (ModeTop[0x1C] == 0x45) {
        hmf->unkD4 = mtxRotCat;
        hmf->unkD8 = func_80088910_main;
    } else {
        hmf->unkD4 = mtxRotCatZXY;
        hmf->unkD8 = mtxRotZXY;
    }
}

void LightLoad(HmfData *hmf, u8 *data, s32 index) {
    u8 *entry;
    u8 *colors;
    HmfFloatBits x;
    HmfFloatBits y;
    HmfFloatBits z;
    f32 len;
    s32 value;

    entry = &((u8 *)hmf->unkC0)[index * 7];
    colors = &ColorTop[((data[0] << 8) + data[1]) * 4 + 0xA];
    entry[0] = colors[0];
    entry[1] = colors[1];
    entry[2] = colors[2];
    data += 3;
    value = data[0];
    value <<= 0x18;
    value += data[1] << 0x10;
    value += data[2] << 8;
    x.word = value + data[3];
    len = x.single * x.single;
    value = data[4];
    value <<= 0x18;
    value += data[5] << 0x10;
    value += data[6] << 8;
    y.word = value + data[7];
    len += y.single * y.single;
    value = data[8];
    value <<= 0x18;
    value += data[9] << 0x10;
    value += data[0xA] << 8;
    z.word = value + data[0xB];
    len += z.single * z.single;
    if (len == 0.0f) {
        entry[4] = 0;
        entry[5] = 0;
        entry[6] = 0x78;
    } else {
        len = HuSqrtf(len);
        entry[4] = (s8)(x.single / len * 120.0f);
        entry[5] = (s8)(y.single / len * 120.0f);
        entry[6] = (s8)(z.single / len * 120.0f);
    }
    entry[3] = 0;
}
