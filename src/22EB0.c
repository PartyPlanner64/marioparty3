#include "common.h"
#include "game/hmflight.h"
#include "game/camera.h"
#include "mallocblock.h"
#include "gcc/string.h"

#define HMF_TEXTURE_MASK(size) ((size) <= 2 ? 1 : (size) <= 4 ? 2 : \
    (size) <= 8 ? 3 : (size) <= 16 ? 4 : (size) <= 32 ? 5 : \
    (size) <= 64 ? 6 : (size) <= 128 ? 7 : (size) <= 256 ? 8 : 9)
#define HMF_TEXTURE_SIZE texture->unk1D
#define HMF_TEXTURE_SIZE_LOAD_BLOCK D_800CCF88_main
#define HMF_TEXTURE_SIZE_INCR D_800CD2FC_main
#define HMF_TEXTURE_SIZE_SHIFT D_800D1FFC_main
#define HMF_TEXTURE_SIZE_BYTES D_800D6A20_main
#define HMF_TEXTURE_SIZE_LINE_BYTES D_800C952C_main

typedef struct {
    u8 next;
    u8 prev;
    s16 objectIndex;
    f32 depth;
} HmfDrawEntry;

typedef struct {
    s16 objectIndex;
    char unk02[2];
    HuMtx4F mtx;
    Mtx *fixedMtx;
    HmfData *hmf;
    s32 objectFlags;
    s32 modelFlags;
    HmfData_UnkD0 *light;
} HmfDrawObject;

typedef struct {
    Mtx mtx;
    LookAt lookAt;
} HmfLookAtData;

typedef struct {
    s16 count;
    s16 indices[4];
    u8 flags;
    char unk0B[1];
    HmfMaterialData *material;
    HmfData_Unk84_Entry *texture;
} HmfDrawFace;

extern HmfModelData_Unk64_Unk60_Struct *D_800B19F0_main;
extern s32 D_800B19F4_main;
extern s16 D_800D0A44_main;
extern s16 D_800CDD66_main;
extern u8 D_800A0AD8_main[8];
extern HmfDrawFace D_800CD6B0_main[];

typedef struct {
    f32 value;
    f32 inTangent;
    f32 outTangent;
} HmfHermiteKey;

typedef struct {
    u32 magic;
    u32 size;
    u8 unk08;
    u8 objectCount;
    s16 duration;
    u32 channelOffset;
    u32 timeOffset;
    u32 valueOffset;
    u32 objectOffsets[1];
} HmfMotionFile;

extern u32 D_800CCF88_main;
extern u32 D_800CD2FC_main;
extern u32 D_800D6A20_main;
extern u32 D_800C952C_main;
extern u32 D_800D1FFC_main;
extern s16 D_800CE2B4_main;
extern HuCamera *D_800D10F4_main;
extern HmfLookAtData D_800D1408_main[];
extern HmfLookAtData *D_800CE20C_main;
extern Vtx *D_800D5308_main;
extern Mtx *MTXBuf;
extern s16 MTXBufNum;
extern Gfx *gMainGfxPos;
extern Gfx *D_800D1FF8_main;
extern u16 D_800D20EE_main;
extern s16 D_800CE1CE_main;
extern s16 D_800D1FD8_main;
extern s16 D_800D6A92_main;
extern u8 D_800CE19A_main;
extern HmfDrawEntry *D_800D2070_main[8];
extern s16 D_800D6AC8_main[8];
extern s16 D_800D5564_main;

extern Vtx *D_800D6A98_main[];
extern Mtx *D_800CD1B8_main[];
extern Gfx *D_800D1F38_main[];
extern u8 D_800A0AD0_main[8];
extern u8 D_800D2008_main;
extern u16 D_800D1FEE_main;
extern u16 D_800C9528_main;
extern u16 D_800D5306_main;
extern HmfDrawObject *D_800CC0BC_main;
extern UnkLightData *D_800CE1D4_main;
extern u8 D_800CB8B0_main;
extern u8 D_800D10F0_main;
extern f32 D_800D5410_main;
extern f32 D_800D51FC_main;
extern u8 D_800CE1C6_main;
extern u8 D_800CDA84_main;
extern u8 D_800D41C4_main;
extern u8 D_800D0599_main;
extern s16 D_800D6B64_main;
extern s16 D_800CC0B6_main;
extern u8 D_800CC0A8_main;
extern s32 D_800A0AE8_main[][2];

extern s32 D_800C9940_main;
extern s16 D_800D5562_main;
extern Gfx *D_800D6A88_main;
extern u8 D_800D5544_main;
extern s16 D_800CDA86_main;
extern s16 D_800CE170_main;
extern s16 D_800CDD5A_main;
extern u64 D_800CE2F0_main;
extern s32 D_800CE2F4_main;
extern u64 D_800D1FD0_main;
extern s32 D_800D1FD4_main;
extern HmfData_Unk84_Entry *D_800D0440_main;
extern HmfData_Unk84_Entry *D_800CC0AC_main;
extern Light *D_800CB8A8_main;
extern s16 D_800D1F78_main;
extern s16 D_800D1FE2_main;
extern s16 D_800CDA76_main;

extern HuMtx4F D_800D5A00_main[];
extern HuMtx4F D_800D59C0_main[];
extern HuMtx4F D_800D41B0_main[];
extern HuMtx4F D_800D5A40_main;
extern HuMtx4F D_800D41F0_main[];
extern s16 D_800D138A_main;
extern s16 D_800D5214_main;
extern u8 D_800CD6A6_main;
extern s16 D_800C9932_main;

extern u8 D_800CD2A0_main;
extern u8 D_800D1F2A_main;
extern u8 D_800D211C_main;
extern u8 D_800D20A0_main;
extern s16 D_800A0AE0_main[];
extern s32 D_800D1F74_main;

extern s16 D_800A0A78_main;
extern s16 D_800A1160_main;
extern s16 D_800CDD6A_main;
extern f32 D_800D2120_main;
extern u16 D_800D5204_main;

void func_8007AB68_main(HuMtx4F, LookAt *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_8002B2AC_main(HmfData_Unk84_Entry2 *, s16, s16);
void func_8002CB6C_main(HmfData *, s16);
void func_8002CDF4_main(HmfData *, s16);
void func_8002C960_main(HmfData *, s16, HmfData *);
s32 func_8002C5B8_main(HmfData *, s16, s16);
void func_8002C0EC_main(HmfData *, s16);
void func_8002B104_main(HmfData *, s16);
extern Gfx D_800A0A80_main[];
void func_800260F0_main(HmfData *, s32 *);
void func_8002A358_main(HmfMaterialData *, HmfData_Unk84_Entry *, u32);
void func_80029FB4_main(HmfData *, s16);
s32 func_8002DF2C_main(D_800CCF58_main_Struct *, HmfMotionFile *);
s32 func_8002D5B0_main(D_800CCF58_main_Struct *, HmfData *);
s32 func_8002D3D0_main(HmfData *, HmfMotionFile *, s32);
s32 func_8002D2D8_main(HmfMotionFile *, HmfData *);
f32 HuSqrtf(f32);
u8 func_8000EF64_main(void *, u16, s32, void *, s32);
void func_8002AC5C_main(u16);
void func_8002AF40_main(void);
void func_80089980_main(HuMtx4F, Mtx *);
void func_8002AFEC_main(HmfData *, s32, s16);
void func_80033694_main(HmfData *);
void func_80088700_main(HuMtx4F, f32, f32, f32);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_8008A070_main(f32 *);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void func_8002367C_main(HuMtx4F, HuMtx4F);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);
s32 func_8002C4C0_main(HmfData *, s16, HuMtx4F, HuMtx4F);
void func_80024DF0_main(HmfData *, s16, Mtx *, HuMtx4F);
void func_80023700_main(HmfData *, s16);
void func_8002404C_main(HmfData *, s16);
void func_80024354_main(HmfData *, s16);
void func_80023AF8_main(HmfData *, s16);
void func_8002DFF8_main(HmfData *, f32, HmfModelData_Unk64_Unk8C_Struct *, s32);
void func_8002EAC0_main(HmfData *, f32, f32);
void HmfLightReset(void);
void func_80022F08_main(HmfData *);
void func_80022FF4_main(HmfData *);
void func_800230F8_main(HmfData *);
void func_8002D094_main(Gfx **, s16, s32);
void func_800257BC_main(HmfData *, s16);
void func_80030208_main(HmfData *);
void HmfLightClose(void);
void func_800123F4_main(void);
void HmfLightInit(void);
void func_80031560_main(void);
void func_80030040_main(void);
s16 func_80011460_main(u8 *);
void func_80018544_main(HuMtx4F, HuMtx4F);
void func_80019C00_main(void *data);
void func_80022660_main(HmfData *);
void func_80030030_main(f32);
void func_8002FE08_main(s16, s16, char *, s16, s16, s16);

void func_800222B0_main(HuAllocFunc alloc, HuFreeFunc free, u16 vertexCount, u16 matrixCount, u16 gfxCount, u8 bufferCount) {
    s16 i;

    D_800D1FF0_main = bufferCount;
    D_800D2008_main = 0;
    HuMemInit(alloc, free);
    D_800D1FEE_main = vertexCount;
    D_800C9528_main = gfxCount;
    D_800D5306_main = matrixCount;
    for (i = 0; i < bufferCount; i++) {
        D_800D6A98_main[i] = HuMemAlloc(vertexCount * sizeof(Vtx));
        D_800CD1B8_main[i] = HuMemAlloc(gfxCount * sizeof(Mtx));
        D_800D1F38_main[i] = HuMemAlloc(matrixCount * sizeof(Gfx));
    }
    for (i = 0; i < ARRAY_COUNT(D_800D2070_main); i++) {
        D_800D2070_main[i] = HuMemAlloc(D_800A0AD0_main[i] * sizeof(HmfDrawEntry));
    }
    D_800CC0BC_main = HuMemAlloc(0x8400);
    D_800CE1D4_main = NULL;
    HmfLightInit();
    func_80031560_main();
    func_80030040_main();
    D_800CB8B0_main = 1;
    D_800D10F0_main = 2;
    D_800D5410_main = 1.0f;
    D_800D51FC_main = 1.0f;
    D_800CE1C6_main = 0;
    D_800CDA84_main = 0xFF;
    D_800D41C4_main = 0xFF;
    D_800D0599_main = 0xFF;
    D_800D6B64_main = 950;
    D_800CC0B6_main = 1000;
    D_800CC0A8_main = 1;
}

void func_800224BC_main(void) {
    HuMemCleanUp();
    if (D_800D20EE_main != 0) {
        D_800D5308_main = D_800D6A98_main[D_800D2008_main];
        MTXBuf = D_800CD1B8_main[D_800D2008_main];
        gMainGfxPos = D_800D1F38_main[D_800D2008_main];
        D_800D1FF8_main = gMainGfxPos;
        D_800CE20C_main = &D_800D1408_main[D_800D2008_main];
        if (++D_800D2008_main >= D_800D1FF0_main) {
            D_800D2008_main = 0;
        }
        HmfLightClose();
        D_800CE1CE_main = 0;
        MTXBufNum = 0;
        D_800D1FD8_main = 0;
        D_800D6A92_main = 0;
        D_800CE19A_main = 0;
        func_800123F4_main();
        D_800D20AC_main++;
    }
}

void func_800225D4_main(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_800D2070_main); i++) {
        D_800D6AC8_main[i] = 2;
        D_800D2070_main[i][0].next = 1;
        D_800D2070_main[i][1].prev = 0;
        D_800D2070_main[i][1].next = 0;
        D_800D2070_main[i][1].depth = 200000.0f;
    }
    D_800D5564_main = 0;
}

void func_80022660_main(HmfData *arg0) {
    Vtx *vertices;
    HmfModelData_Unk64_Unk60_Struct *object;
    s16 i, j;
    Gfx *gfx;
    Gfx *extraGfx;
    s32 flags;
    s16 savedVertexCount;
    s16 startVertex;
    s16 maxGfx;
    Gfx *savedGfx;
    Vtx *savedVertices;
    u32 vertexCapacity;
    u32 gfxCapacity;
    s16 *indices;

    maxGfx = 0;
    if (arg0->unk10 == 0 || arg0->unk14 == 0) {
        return;
    }
    savedGfx = gMainGfxPos;
    savedVertices = D_800D5308_main;
    savedVertexCount = D_800CE1CE_main;
    arg0->unk3C = HuMemAllocTag(arg0->unk10 * sizeof(Gfx *), D_800CDD6A_main);
    extraGfx = HuMemAlloc(200);
    flags = arg0->unk1C;
    flags = flags * 4 + arg0->unk10 * 8;
    D_800D5308_main = HuMemAlloc(flags * sizeof(Vtx));
    if (arg0->unkB4 != 0 || (D_800C9940_main & 0x400000)) {
        if (arg0->unk5C != NULL) {
            HuMemFree(arg0->unk5C);
        }
        arg0->unk5C = HuMemAlloc(arg0->unk14 * sizeof(s16));
        arg0->unk28 = 0;
    }
    if (D_800D5308_main == NULL) {
        arg0->unk40 = (Vtx *)(D_800CE1CE_main * sizeof(Vtx));
        D_800D5308_main = arg0->unk40;
    }
    for (i = 0, j = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unkC->unk1F & 1) {
            j++;
            break;
        }
    }
    vertexCapacity = arg0->unk1C;
    gfxCapacity = !j ? vertexCapacity * 32 : vertexCapacity * 128;
    gfx = HuMemAlloc(gfxCapacity + 4000);
    if (gfx == NULL) {
        gfx = gMainGfxPos;
    }
    if (arg0->unkCC != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unkCC->unk00[i] != NULL) {
                func_80019C00_main(arg0->unkCC->unk00[i]);
            }
        }
        HuMemFree(arg0->unkCC->unk00);
        HuMemFree(arg0->unkCC);
        arg0->unkCC = NULL;
    }
    func_80022F08_main(arg0);
    D_800CE1CE_main = 0;
    D_800D5562_main = 0;
    HmfLightReset();
    func_800230F8_main(arg0);
    object = arg0->unk60;
    for (i = 0; i < arg0->unk10; i++, object++) {
        gMainGfxPos = gfx;
        D_800D6A88_main = extraGfx;
        D_800D5544_main = 0;
        startVertex = D_800CE1CE_main;
        D_800CDA86_main = 0;
        D_800CE170_main = 0;
        D_800CDD5A_main = 0;
        D_800CE2F0_main = 0xFFFFFFFF;
        D_800D1FD0_main = 0xFFFFFFFF;
        D_800D0440_main = NULL;
        func_8002D094_main(&gMainGfxPos, 1, 0);
        if (D_800C9940_main & 0x200) {
            gSPLight(gMainGfxPos++, D_800CB8A8_main, D_800CE1D4_main->unk00 + 1);
            D_800D1F78_main = D_800CB8A8_main->l.col[0];
            D_800D1FE2_main = D_800CB8A8_main->l.col[1];
            D_800CDA76_main = D_800CB8A8_main->l.col[2];
        }
        flags = object->unk50;
        object->unk28 = D_800CE1CE_main;
        object->unk2C = D_800D5562_main;
        object->unk50 &= ~0x6000000;
        func_800257BC_main(arg0, i);
        flags &= 0x6000000;
        if (flags) {
            object->unk50 |= flags;
        }
        object->unk2A = D_800CE1CE_main - (u16)object->unk28;
        object->unk2E = D_800D5562_main - (u16)object->unk2C;
        gSPEndDisplayList(gMainGfxPos++);
        object->unk60 = D_800D0440_main;
        if (D_800D6A88_main == extraGfx) {
            flags = (gMainGfxPos - gfx) * sizeof(Gfx);
            ((Gfx **)arg0->unk3C)[i] = HuMemAllocTag(flags, D_800CDD6A_main);
            bcopy(gfx, ((Gfx **)arg0->unk3C)[i], flags);
            object->unk5C = NULL;
            object->unk64 = NULL;
        } else {
            gSPEndDisplayList(D_800D6A88_main++);
            object->unk5C = D_800CC0AC_main;
            ((Gfx **)arg0->unk3C)[i] = HuMemAllocTag((gMainGfxPos - gfx + D_800D6A88_main - extraGfx) * sizeof(Gfx), D_800CDD6A_main);
            bcopy(gfx, ((Gfx **)arg0->unk3C)[i], (gMainGfxPos - gfx) * sizeof(Gfx));
            object->unk64 = ((Gfx **)arg0->unk3C)[i] + (gMainGfxPos - gfx);
            bcopy(extraGfx, object->unk64, (D_800D6A88_main - extraGfx) * sizeof(Gfx));
        }
        if (maxGfx < gMainGfxPos - gfx) {
            maxGfx = gMainGfxPos - gfx;
        }
        if (object->unk50 & 0x6000000) {
            if (arg0->unkCC == NULL) {
                arg0->unkCC = HuMemAllocTag(sizeof(*arg0->unkCC), D_800CDD6A_main);
                arg0->unkCC->unk00 = HuMemAllocTag(arg0->unk10 * sizeof(Gfx *), D_800CDD6A_main);
                for (j = 0; j < arg0->unk10; j++) {
                    arg0->unkCC->unk00[j] = NULL;
                }
            }
            gMainGfxPos = gfx;
            D_800CE1CE_main = startVertex;
            D_800CDA86_main = 0;
            D_800CE170_main = 0;
            D_800CDD5A_main = 0;
            D_800CDA76_main = 0;
            D_800D1FE2_main = 0;
            D_800D1F78_main = 0;
            D_800CE2F0_main = 0xFFFFFFFF;
            D_800D1FD0_main = 0xFFFFFFFF;
            D_800D0440_main = NULL;
            func_800257BC_main(arg0, i);
            gSPEndDisplayList(gMainGfxPos++);
            arg0->unkCC->unk00[i] = HuMemAllocTag((gMainGfxPos - gfx) * sizeof(Gfx), D_800CDD6A_main);
            bcopy(gfx, arg0->unkCC->unk00[i], (gMainGfxPos - gfx) * sizeof(Gfx));
        }
    }
    arg0->unk18 = D_800CE1CE_main;
    arg0->unk1A = D_800D5562_main;
    vertices = HuMemAllocTag(D_800CE1CE_main * sizeof(Vtx), D_800CDD6A_main);
    bcopy(D_800D5308_main, vertices, D_800CE1CE_main * sizeof(Vtx));
    arg0->unk40 = vertices;
    func_80022FF4_main(arg0);
    for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
        arg0->unk44[i] = vertices;
    }
    if (arg0->unk5C != NULL) {
        indices = HuMemAllocTag(arg0->unk14 * sizeof(s16), D_800CDD6A_main);
        bcopy(arg0->unk5C, indices, arg0->unk14 * sizeof(s16));
        HuMemFree(arg0->unk5C);
        arg0->unk5C = indices;
    }
    if (arg0->unkB4 != 0 || (D_800C9940_main & 0x400000)) {
        func_80030208_main(arg0);
    }
    if (arg0->unk1C * 4 + arg0->unk10 * 8 < D_800CE1CE_main) {
        osSyncPrintf("Vertex Over!\n");
    }
    HuMemFree(D_800D5308_main);
    HuMemFree(gfx);
    HuMemFree(extraGfx);
    D_800CE1CE_main = savedVertexCount;
    D_800D5308_main = savedVertices;
    gMainGfxPos = savedGfx;
}

void func_80022F08_main(HmfData *arg0) {
    s16 needed;
    s16 i;
    u16 count;

    needed = 0;
    for (i = 0, count = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk50 & 0x20000) {
            needed = 1;
        }
        count += (u16)arg0->unk60[i].unk22;
    }
    if (needed && arg0->unkB0 == NULL) {
        arg0->unkB0 = HuMemAllocTag(count * sizeof(*arg0->unkB0), D_800CDD6A_main);
    }
}

void func_80022FF4_main(HmfData *arg0) {
    HmfVertexGroup *group;
    s16 *indices;
    s16 i, j;
    u16 count;
    f32 x, y, z;

    if (arg0->unkB0 == NULL) {
        return;
    }
    group = arg0->unkB0;
    for (i = 0; i < arg0->unk1A; i++, group++) {
        indices = group->indices;
        count = group->count;
        x = y = z = 0.0f;
        for (j = 0; j < count; j++, indices++) {
            x += arg0->unk40[*indices].v.ob[0];
            y += arg0->unk40[*indices].v.ob[1];
            z += arg0->unk40[*indices].v.ob[2];
        }
        group->center.x = x / count;
        group->center.y = y / count;
        group->center.z = z / count;
    }
}

void func_800230F8_main(HmfData *arg0) {
    s16 textureIndex;
    s16 i, j;

    textureIndex = 4; // TODO: why does this start at 4?

    for (i = 0; i < arg0->unk12; i++) {
        /* Skip entries marked as 0xFF */
        if (arg0->unk84[i].unk9 == 0xFF) {
            continue;
        }

        /* Find first entry with different unkC value */
        for (j = 0; j < i; j++) {
            if (arg0->unk84[i].unkC == arg0->unk84[j].unkC) {
                break;
            }
        }

        /* Copy or assign texture indices */
        if (j != i) {
            arg0->unk84[i].unk3 = arg0->unk84[j].unk3;
            arg0->unk84[i].unk4 = arg0->unk84[j].unk4;
        } else {
            arg0->unk84[i].unk3 = textureIndex++;
            if (arg0->unk84[i].unkC->unk_30 != NULL) {
                arg0->unk84[i].unk4 = textureIndex++;
            }

            if (textureIndex > 16) {
                osSyncPrintf("Texture Anime Over\n");
                return;
            }
        }
    }
}

s32 func_80023264_main(HmfData *arg0) {
    s32 var_s2;
    s16 i;

    var_s2 = 0;
    if (arg0->unk40 != NULL) {
        for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
            if (arg0->unk40 != arg0->unk44[i]) {
                if (arg0->unk0A != 0) {
                    func_80019C00_main(arg0->unk44[i]);
                } else {
                    HuMemFree(arg0->unk44[i]);
                }
                arg0->unk44[i] = arg0->unk40;
                var_s2 = 1;
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk40);
        } else {
            HuMemFree(arg0->unk40);
        }
    }
    if (arg0->unk3C != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unk0A != 0) {
                func_80019C00_main(arg0->unk3C->unk00[i]);
            } else {
                HuMemFree(arg0->unk3C->unk00[i]);
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk3C);
        } else {
            HuMemFree(arg0->unk3C);
        }
    }
    D_800D5204_main = arg0->unk0E;
    D_800CDD6A_main = arg0->unk0E + 1;
    func_80022660_main(arg0);
    return var_s2;
}

void func_80023404_main(HmfData *arg0, HuMtx4F arg1, HuMtx4F arg2) {
    HuMtx4F mtx;

    if (arg0->unk14 == 0) {
        return;
    }
    func_8002367C_main(D_800D5A00_main[0], arg1);
    D_800D138A_main = 1;
    guMtxIdentF(D_800D5A40_main);
    D_800D5214_main = 0;
    func_8002367C_main(D_800D41F0_main[0], arg2);
    if (arg0->unk01 & 4) {
        if (arg0->unk60[0].unk50 & 0x70000000) {
            func_8002C4C0_main(arg0, 0, arg1, mtx);
            func_80018044_main(arg2, mtx, arg1);
        }
        func_800898F0_main(arg1, &MTXBuf[MTXBufNum]);
        func_80024DF0_main(arg0, 0, &MTXBuf[MTXBufNum++], arg1);
        return;
    }
    if (arg0->unk80 == (HmfMotionNode *)-1) {
        if (arg0->unk8C != NULL) {
            func_8002DFF8_main(arg0, arg0->unkA0, arg0->unk8C, 1);
            if (arg0->unk90 != NULL) {
                func_8002EAC0_main(arg0, arg0->unkA4, arg0->unkA8);
            }
            if (arg0->unk94 != NULL) {
                func_8002DFF8_main(arg0, arg0->unkAC, arg0->unk94, 0);
            }
        }
        if (arg0->unk64 == 0) {
            return;
        }
        func_80023700_main(arg0, 0);
    } else {
        if (arg0->unk16 == 0) {
            return;
        }
        if (D_800CD6A6_main != 0 && (u8)arg0->unk0B == 1 && (u8)arg0->unk0C != 0) {
            func_8002404C_main(arg0, 0);
        } else {
            if (arg0->unk8C != NULL) {
                func_8002DFF8_main(arg0, arg0->unkA0, arg0->unk8C, 1);
                if (arg0->unk90 != NULL) {
                    func_8002EAC0_main(arg0, arg0->unkA4, arg0->unkA8);
                }
                if (arg0->unk94 != NULL) {
                    func_8002DFF8_main(arg0, arg0->unkAC, arg0->unk94, 0);
                }
            }
            if (arg0->unk16 == 1) {
                func_80024354_main(arg0, 0);
            } else {
                func_80023AF8_main(arg0, 0);
            }
        }
    }
    if (D_800C9528_main <= MTXBufNum) {
        osSyncPrintf("Mtx Over\n");
    }
}

void func_8002367C_main(HuMtx4F dst, HuMtx4F src) {
    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    dst[0][3] = src[0][3];
    dst[1][0] = src[1][0];
    dst[1][1] = src[1][1];
    dst[1][2] = src[1][2];
    dst[1][3] = src[1][3];
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][1];
    dst[2][2] = src[2][2];
    dst[2][3] = src[2][3];
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}

void func_80023700_main(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfSkeletonNode *node;
    s32 objectIndex;
    s32 scaled;
    s32 transformed;

    node = &arg0->unk68[arg1];
    objectIndex = node->unk00;
    scaled = 0;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        func_80018044_main(node->unk4C, D_800D5A00_main[0], mtx);
    } else {
        func_8008A070_main(mtx[0]);
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            func_80017C10_main(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            arg0->unkD4(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            func_8008A070_main(temp[0]);
            func_80017CD0_main(temp, node->scale.x, node->scale.y, node->scale.z);
            D_800D5214_main++;
            func_80018044_main(temp, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            scaled = 1;
            transformed = 1;
        }
        if (transformed) {
            D_800D138A_main++;
            func_80018044_main(mtx, D_800D59C0_main[D_800D138A_main], D_800D59C0_main[D_800D138A_main + 1]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], mtx);
    }
    if (objectIndex >= 0) {
        if (node->unk48->unk60[objectIndex].unk50 & 0x70000000) {
            func_8002C4C0_main(node->unk48, objectIndex, mtx, temp);
            func_80018044_main(D_800D41F0_main[D_800D5214_main], temp, mtx);
        }
        func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
        func_80024DF0_main(node->unk48, objectIndex, &MTXBuf[MTXBufNum], mtx);
        MTXBufNum++;
    }
    if (node->unk04 != 0) {
        func_80023700_main(arg0, arg1 + node->unk04);
    }
    if (transformed) {
        D_800D138A_main--;
    }
    if (scaled) {
        D_800D5214_main--;
    }
    if (objectIndex >= 0 && node->unk48 == arg0 && arg0->unk60[objectIndex].unk58 != NULL) {
        func_80023700_main(arg0->unk60[objectIndex].unk58, 0);
    }
    if (node->unk02 != 0) {
        func_80023700_main(arg0, arg1 + node->unk02);
    }
}

void func_80023AF8_main(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s32 objectIndex;
    s32 matrixIndex;
    s16 *indices;
    s32 count;
    s32 i;
    s32 scaled;
    s32 transformed;
    void (*rotate)(HuMtx4F, f32, f32, f32);

    node = &arg0->unk80[arg1 & 0x7FFF];
    scaled = 0;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        func_80018044_main(node->unk58, D_800D5A00_main[0], mtx);
        if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
            func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
            D_800D5214_main++;
            func_80018044_main(temp, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            scaled = 1;
        }
    } else {
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            func_80088800_main(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            if (!transformed) {
                rotate = arg0->unkD8;
            } else {
                rotate = arg0->unkD4;
            }
            rotate(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            if (transformed) {
                func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            } else {
                func_80088700_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            }
            func_80088700_main(temp, node->scale.x, node->scale.y, node->scale.z);
            matrixIndex = ++D_800D5214_main;
            func_80018044_main(temp, D_800D41B0_main[matrixIndex], D_800D41B0_main[matrixIndex + 1]);
            scaled = 1;
            transformed = 1;
        }
        if (transformed) {
            D_800D138A_main++;
            func_80018044_main(mtx, D_800D59C0_main[D_800D138A_main], D_800D59C0_main[D_800D138A_main + 1]);
        }
        if (D_800C9932_main != 1 && (u8)arg0->unk0B == 1) {
            func_8002367C_main(node->unk58, D_800D5A00_main[D_800D138A_main]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], mtx);
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    count = node->unk00;
    indices = node->unk50;
    for (i = 0; i < count; i++) {
        objectIndex = *indices;
        indices++;
        if (objectIndex & 0x8000) {
            if (objectIndex != -1) {
                func_80023AF8_main(arg0, objectIndex & 0x7FFF);
            }
        } else {
            object = &node->unk54->unk60[objectIndex];
            if (object->unk24 == 1) {
                break;
            }
            if (object->unk50 & 0x70000000) {
                func_8002C4C0_main(node->unk54, objectIndex, mtx, temp);
                func_80018044_main(D_800D41F0_main[D_800D5214_main], temp, mtx);
                func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
                matrixIndex = MTXBufNum++;
            }
            func_80024DF0_main(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
            linked = arg0->unk60[objectIndex].unk58;
            if (linked != NULL && arg0 == node->unk54) {
                func_80023AF8_main(linked, 0);
            }
        }
    }
    if (transformed) {
        D_800D138A_main--;
    }
    if (scaled) {
        D_800D5214_main--;
    }
}

void func_8002404C_main(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s16 objectIndex;
    s16 matrixIndex;
    s16 *indices;
    s16 count;
    s16 i;
    s16 scaled;

    node = &arg0->unk80[arg1 & 0x7FFF];
    scaled = 0;
    func_80018044_main(node->unk58, D_800D5A00_main[0], mtx);
    if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
        func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
        D_800D5214_main++;
        func_80018044_main(temp, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
        scaled = 1;
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    indices = node->unk50;
    i = 0;
    count = node->unk00;
    for (; i < count; i++) {
        objectIndex = *indices;
        indices++;
        if (objectIndex & 0x8000) {
            if (objectIndex != -1) {
                func_8002404C_main(arg0, objectIndex & 0x7FFF);
            }
        } else {
            object = &node->unk54->unk60[objectIndex];
            if (object->unk24 == 1) {
                break;
            }
            if (object->unk50 & 0x70000000) {
                func_8002C4C0_main(node->unk54, objectIndex, mtx, temp);
                func_80018044_main(D_800D41F0_main[D_800D5214_main], temp, mtx);
                func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
                matrixIndex = MTXBufNum++;
            }
            func_80024DF0_main(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
            linked = arg0->unk60[objectIndex].unk58;
            if (linked != NULL && arg0 == node->unk54) {
                func_8002404C_main(linked, 0);
            }
        }
    }
    if (scaled) {
        D_800D5214_main--;
    }
}

void func_80024354_main(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s32 objectIndex;
    s32 matrixIndex;
    s32 flags;
    s32 transformed;
    void (*rotate)(HuMtx4F, f32, f32, f32);

    node = &arg0->unk80[arg1 & 0x7FFF];
    objectIndex = *node->unk50;
    object = &node->unk54->unk60[objectIndex];
    if (object->unk24 == 1) {
        return;
    }
    flags = object->unk50 & 0x70000000;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        func_80018044_main(node->unk58, D_800D5A00_main[0], mtx);
        if (flags && (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f)) {
            func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
            D_800D5214_main++;
            func_80018044_main(temp, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
        }
    } else {
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            func_80088800_main(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            if (!transformed) {
                rotate = arg0->unkD8;
            } else {
                rotate = arg0->unkD4;
            }
            rotate(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            if (transformed) {
                func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            } else {
                func_80088700_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            }
            if (flags) {
                func_80088700_main(temp, node->scale.x, node->scale.y, node->scale.z);
                D_800D5214_main++;
                func_80018044_main(temp, D_800D41B0_main[D_800D5214_main], D_800D41B0_main[D_800D5214_main + 1]);
            }
            transformed = 1;
        }
        if (transformed) {
            D_800D138A_main++;
            func_80018044_main(mtx, D_800D59C0_main[D_800D138A_main], D_800D59C0_main[D_800D138A_main + 1]);
        }
        if (D_800C9932_main != 1 && (u8)arg0->unk0B == 1) {
            func_8002367C_main(node->unk58, D_800D5A00_main[D_800D138A_main]);
        }
        func_80018044_main(D_800D5A00_main[D_800D138A_main], D_800D5A00_main[0], mtx);
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    if (object->unk50 & 0x70000000) {
        func_8002C4C0_main(node->unk54, objectIndex, mtx, temp);
        func_80018044_main(D_800D41F0_main[D_800D5214_main], temp, mtx);
        func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
        matrixIndex = MTXBufNum++;
    }
    func_80024DF0_main(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
    linked = arg0->unk60[objectIndex].unk58;
    if (linked != NULL && arg0 == node->unk54) {
        func_80023AF8_main(linked, 0);
    }
}

void func_80024814_main(HmfData *arg0, s16 arg1, HmfDrawObject *arg2) {
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfMaterialData *material;
    s32 flags;

    flags = arg0->unk60[arg1].unk50;
    if (flags & 0x6000000) {
        if (D_800C9940_main == 0) {
            arg0->unk60[arg1].unk50 = flags & ~0x6000000;
            gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(D_800D5308_main));
            func_80024814_main(arg0, arg1, arg2);
            arg0->unk60[arg1].unk50 = flags;
        } else {
            object = &arg0->unk60[arg1];
            func_8002AFEC_main(arg0, object->unk50 & ~0x6000000, arg1);
            gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(arg0->unk44[D_800D2008_main]));
            if (object->unk5C != NULL) {
                if (D_800D0440_main != object->unk5C && object->unk5C != (HmfData_Unk84_Entry *)-1) {
                    gSPDisplayList(gMainGfxPos++, object->unk64);
                }
                D_800D0440_main = object->unk60;
            } else {
                D_800D0440_main = NULL;
            }
            gSPDisplayList(gMainGfxPos++, ((Gfx **)arg0->unk3C)[arg1]);
            func_8002AFEC_main(arg0, object->unk50, arg1);
            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(arg2->fixedMtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(gMainGfxPos++, arg0->unkCC->unk00[arg1]);
            return;
        }
    }
    object = &arg0->unk60[arg1];
    func_8002AFEC_main(arg0, object->unk50, arg1);
    if (object->unk50 & 0x40000) {
        func_80033694_main(arg0);
    }
    if (object->unk20 != -1 || (arg0->unk98 != NULL && (arg0->unk88[object->unk1E].unk09 & 4))) {
        material = &arg0->unk88[object->unk1E];
        gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, (u8)object->unk20);
    }
    if (D_800C9940_main & 0x10000) {
        gDPSetEnvColor(gMainGfxPos++, (u8)arg0->unk02[4], (u8)arg0->unk02[5], (u8)arg0->unk02[6], (u8)arg0->unk02[7]);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, (u8)arg0->unk02[0], (u8)arg0->unk02[1], (u8)arg0->unk02[2], (u8)arg0->unk02[3]);
    }
    if (D_800C9940_main & 1) {
        if (((Gfx **)arg0->unk3C)[arg1] == NULL) {
            return;
        }
        if (object->unk5C != NULL) {
            if (D_800D0440_main != object->unk5C && object->unk5C != (HmfData_Unk84_Entry *)-1) {
                gSPDisplayList(gMainGfxPos++, object->unk64);
            }
            D_800D0440_main = object->unk60;
        } else {
            D_800D0440_main = NULL;
        }
        gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(arg0->unk44[D_800D2008_main]));
        gSPDisplayList(gMainGfxPos++, ((Gfx **)arg0->unk3C)[arg1]);
    } else {
        gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(D_800D5308_main));
        func_800257BC_main(arg0, arg1);
    }
    if ((u32)gMainGfxPos >= (u32)D_800D1FF8_main + (D_800D5306_main << 6)) {
        osSyncPrintf("GfxMax Over\n");
    }
}

void func_80024D94_main(HmfData *arg0, s16 arg1, Mtx *arg2) {
    HuMtx4F mtx;

    func_80089980_main(mtx, arg2);
    func_80024DF0_main(arg0, arg1, arg2, mtx);
}

void func_80024DF0_main(HmfData *arg0, s16 arg1, Mtx *arg2, HuMtx4F arg3) {
    HmfDrawEntry *entries;
    HmfDrawObject *object;
    s16 entryIndex;
    s16 layer;
    s32 flags;
    f32 x, y, z;
    s16 insertion;
    HmfDrawEntry *entry;
    f32 depth;

    layer = arg0->unk00;
    entryIndex = D_800D6AC8_main[layer];
    if (entryIndex >= D_800A0AD0_main[layer]) {
        osSyncPrintf("Model Object Entry Over!! UCODE%d\n", layer);
        return;
    }
    entries = D_800D2070_main[layer];
    if (arg0->unk60[arg1].unk50 & 0x81210000) {
        x = arg3[3][0];
        y = arg3[3][1];
        z = arg3[3][2];
        depth = x * x + y * y + z * z;
        if (depth != 0.0f) {
            depth = HuSqrtf(depth);
        } else {
            depth = 0.0f;
        }
        flags = arg0->unk60[arg1].unk50;
        if (flags & 0x80210000) {
            depth = 100000.0f - depth;
        } else if (flags & 0x1000000) {
            depth = -depth;
        }
        for (insertion = entries[0].next; entries[insertion].next != 0; insertion = entries[insertion].next) {
            if (depth < entries[insertion].depth) {
                break;
            }
        }
    } else {
        insertion = entries[0].next;
        depth = 0.0f;
    }
    arg0->unk60[arg1].unk1D = entryIndex;
    insertion = entries[insertion].prev;
    entry = entries + entryIndex;
    entry->prev = insertion;
    entry->next = entries[insertion].next;
    entries[insertion].next = entryIndex;
    entries[entry->next].prev = entryIndex;
    D_800D6AC8_main[layer]++;
    entry->depth = depth;
    object = &D_800CC0BC_main[D_800D5564_main];
    entry->objectIndex = D_800D5564_main++;
    object->fixedMtx = arg2;
    object->hmf = arg0;
    object->objectIndex = arg1;
    object->modelFlags = D_800C9940_main;
    object->objectFlags = arg0->unk60[arg1].unk50;
    object->light = (HmfData_UnkD0 *)arg0->unkD0;
}

Gfx *func_800250D4_main(s16 arg0, Gfx *arg1, Gfx *arg2) {
    HmfDrawEntry *entry;
    HmfDrawObject *object;
    HmfData *hmf;
    s16 lightCount;
    s16 visited;
    s16 layer;
    s16 i, j;
    s16 count;
    s16 flags;
    u8 r, g, b;
    Gfx *start;
    s32 active;

    start = gMainGfxPos;
    if (arg2 != NULL) {
        gSPDisplayList(gMainGfxPos++, arg2);
    }
    active = D_800CE19A_main != 0;
    HmfLightExec(arg0);
    r = D_800CB8A8_main->l.col[0];
    g = D_800CB8A8_main->l.col[1];
    b = D_800CB8A8_main->l.col[2];
    lightCount = D_800CE1D4_main->unk00 + 1;
    for (layer = 0, visited = 0; layer < ARRAY_COUNT(D_800D2070_main); layer++) {
        if (D_800D6AC8_main[layer] == 2) {
            continue;
        }
        if (active) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            func_8000EF64_main(start, D_800CE19A_main, 0, NULL, 0);
            start = gMainGfxPos;
        }
        func_800127C4_main(arg0, &gMainGfxPos);
        visited++;
        active = 1;
        D_800CE19A_main = layer;
        gSPDisplayList(gMainGfxPos++, arg1);
        D_800CE2F0_main = 0xFFFFFFFF;
        D_800D1FD0_main = 0xFFFFFFFF;
        D_800D1F74_main = -1;
        D_800D0440_main = NULL;
        gSPNumLights(gMainGfxPos++, lightCount - 1);
        for (j = 1; j < lightCount; j++) {
            gSPLight(gMainGfxPos++, &D_800CB8A8_main[j], j);
        }
        gSPLight(gMainGfxPos++, D_800CB8A8_main, lightCount);
        D_800CD2A0_main = 0xFF;
        D_800D211C_main = 0xFF;
        D_800D1F2A_main = 0xFF;
        flags = -1;
        func_8002AF40_main();
        entry = &D_800D2070_main[layer][D_800D2070_main[layer][0].next];
        count = D_800D6AC8_main[layer];
        for (i = 2; i < count; i++) {
            object = &D_800CC0BC_main[entry->objectIndex];
            hmf = object->hmf;
            D_800D1F78_main = r;
            D_800D1FE2_main = g;
            D_800CDA76_main = b;
            D_800CDA86_main = 0;
            D_800CE170_main = 0;
            D_800CDD5A_main = 0;
            func_8002D094_main(&gMainGfxPos, lightCount,
                               ((u16)D_800D1F78_main << 24) + ((u16)D_800D1FE2_main << 16) + ((u16)D_800CDA76_main << 8));
            func_8002D094_main(&gMainGfxPos, 1, 0);
            if (object->light != NULL) {
                gSPLight(gMainGfxPos++, &((HmfData_UnkD0 *)hmf->unkD0)->unk08[D_800D2008_main], 2);
            }
            if (flags != object->objectFlags) {
                flags = object->objectFlags;
                func_8002AC5C_main((u16)flags);
            }
            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(object->fixedMtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            D_800C9940_main = object->modelFlags;
            func_80024814_main(hmf, object->objectIndex, object);
            if (object->light != NULL) {
                gSPLight(gMainGfxPos++, &D_800CB8A8_main[2], 2);
            }
            entry = &D_800D2070_main[layer][entry->next];
            if (entry->next == 0) {
                break;
            }
        }
    }
    if (visited == 0) {
        gSPDisplayList(gMainGfxPos++, arg1);
        gSPNumLights(gMainGfxPos++, lightCount - 1);
        for (j = 1; j < lightCount; j++) {
            gSPLight(gMainGfxPos++, &D_800CB8A8_main[j], j);
        }
        gSPLight(gMainGfxPos++, D_800CB8A8_main, lightCount);
    }
    return start;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800257BC_main);

void func_800260F0_main(HmfData *hmf, s32 *flags) {
    HmfData_Unk84_Entry2 *texture;
    HmfMaterialData *material;
    HmfData_Unk84_Entry *textureEntry;
    s16 changed;
    s16 minS, maxS, minT, maxT;
    u16 r, g, b;
    Vtx *vertex;
    s16 i;
    s16 t;
    s16 coordS;
    s8 segment;
    u8 *image;
    u8 *palette;
    Gfx **gfx;
    HmfDrawFace *face;

    if (D_800D0A44_main == 0) {
        return;
    }
    material = D_800CD6B0_main[0].material;
    textureEntry = D_800CD6B0_main[0].texture;
    if (!(*flags & 0x6000000)) {
        func_8002A358_main(material, textureEntry, *flags);
        r = g = b = 0;
        if (textureEntry == (HmfData_Unk84_Entry *)-1) {
            changed = 0;
            if (D_800C9940_main & 0x200) {
                r = material->unk01 * D_800D5410_main;
                if (r > 255)
                    r = 255;
                g = material->unk02 * D_800D5410_main;
                if (g > 255)
                    g = 255;
                b = material->unk03 * D_800D5410_main;
                if (b > 255)
                    b = 255;
                if ((u16)D_800D1F78_main != r || (u16)D_800D1FE2_main != g || (u16)D_800CDA76_main != b) {
                    D_800D1F78_main = r;
                    D_800D1FE2_main = g;
                    D_800CDA76_main = b;
                    func_8002D094_main(&gMainGfxPos, D_800CE1D4_main->unk00 + 1,
                                       ((u16)D_800D1F78_main << 24) + ((u16)D_800D1FE2_main << 16) + ((u16)D_800CDA76_main << 8));
                    changed = 1;
                }
            }
            r = material->unk05 * D_800D51FC_main;
            if (r > 255)
                r = 255;
            g = material->unk06 * D_800D51FC_main;
            if (g > 255)
                g = 255;
            b = material->unk07 * D_800D51FC_main;
            if (b > 255)
                b = 255;
            if ((u16)D_800CDD5A_main != r || (u16)D_800CE170_main != g || (u16)D_800CDA86_main != b) {
                D_800CDD5A_main = r;
                D_800CE170_main = g;
                D_800CDA86_main = b;
                func_8002D094_main(&gMainGfxPos, 1,
                                   ((u16)D_800CDD5A_main << 24) + ((u16)D_800CE170_main << 16) + ((u16)D_800CDA86_main << 8));
                changed = 1;
            }
            if (changed) {
                gDPPipeSync(gMainGfxPos++);
            }
        } else {
            texture = textureEntry->unkC;
            minT = 32000;
            if (texture->unk1F & 1) {
                minS = 32000;
                maxS = maxT = -32000;
                vertex = &D_800D5308_main[D_800CDD66_main];
                for (i = 0; i < D_800CE1CE_main - D_800CDD66_main; i++, vertex++) {
                    t = vertex->v.tc[1];
                    coordS = vertex->v.tc[0];
                    if (minS > coordS)
                        minS = coordS;
                    if (maxS < coordS)
                        maxS = coordS;
                    if (minT > t)
                        minT = t;
                    if (maxT < t)
                        maxT = t;
                }
                minS >>= 5;
                minT >>= 5;
                maxS >>= 5;
                maxT >>= 5;
                changed = 1;
            } else {
                maxS = minS = maxT = minT = 0;
                changed = 0;
            }
            switch ((s8)textureEntry->unk0[0]) {
                case 0x2A:
                case 0x2B:
                    r = material->unk01 * D_800D5410_main;
                    if (r > 255)
                        r = 255;
                    g = material->unk02 * D_800D5410_main;
                    if (g > 255)
                        g = 255;
                    b = material->unk03 * D_800D5410_main;
                    if (b > 255)
                        b = 255;
                    break;
                case 0x29:
                    r = D_800D5410_main * 255;
                    if (r > 255)
                        r = 255;
                    g = b = r;
                    break;
            }
            if ((D_800C9940_main & 0x200) && ((u16)D_800D1F78_main != r || (u16)D_800D1FE2_main != g || (u16)D_800CDA76_main != b)) {
                D_800D1F78_main = r;
                D_800D1FE2_main = g;
                D_800CDA76_main = b;
                func_8002D094_main(&gMainGfxPos, D_800CE1D4_main->unk00 + 1,
                                   ((u16)D_800D1F78_main << 24) + ((u16)D_800D1FE2_main << 16) + ((u16)D_800CDA76_main << 8));
            }
            switch ((s8)textureEntry->unk0[0]) {
                case 0x2B:
                    r = textureEntry->unk5[0] * D_800D51FC_main;
                    if (r > 255)
                        r = 255;
                    g = textureEntry->unk5[1] * D_800D51FC_main;
                    if (g > 255)
                        g = 255;
                    b = textureEntry->unk5[2] * D_800D51FC_main;
                    if (b > 255)
                        b = 255;
                    break;
                case 0x29:
                    r = D_800D51FC_main * 255;
                    if (r > 255)
                        r = 255;
                    g = b = r;
                    break;
                default:
                    r = material->unk05 * D_800D51FC_main;
                    if (r > 255)
                        r = 255;
                    g = material->unk06 * D_800D51FC_main;
                    if (g > 255)
                        g = 255;
                    b = material->unk07 * D_800D51FC_main;
                    if (b > 255)
                        b = 255;
                    break;
            }
            if ((u16)D_800CDD5A_main != r || (u16)D_800CE170_main != g || (u16)D_800CDA86_main != b) {
                D_800CDD5A_main = r;
                D_800CE170_main = g;
                D_800CDA86_main = b;
                func_8002D094_main(&gMainGfxPos, 1,
                                   ((u16)D_800CDD5A_main << 24) + ((u16)D_800CE170_main << 16) + ((u16)D_800CDA86_main << 8));
            }
            if (changed || (textureEntry != D_800D0440_main && !(*flags & 0x8000000))) {
                D_800D0440_main = textureEntry;
                segment = textureEntry->unk3;
                if (segment != -1) {
                    image = (u8 *)(segment << 24);
                    *flags |= 0x40000;
                    gfx = &gMainGfxPos;
                    D_800D5544_main = 1;
                } else {
                    image = texture->unk28;
                    if (D_800D5544_main == 0 && (((((u32)D_800C9940_main >> 13) ^ 1) & 1) && (changed ^ 1))) {
                        gfx = &D_800D6A88_main;
                        D_800CC0AC_main = D_800D0440_main;
                    } else {
                        gfx = &gMainGfxPos;
                    }
                }
                if (texture->unk1C != G_IM_FMT_CI) {
                    if (D_800B19F4_main != 0) {
                        D_800B19F4_main = 0;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
                    }
                    if (texture->unk1D != G_IM_SIZ_4b) {
                        if (texture->unk1F & 1) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, texture->unk1D, texture->unk24, image);
                            switch (texture->unk1D) {
                                case G_IM_SIZ_16b:
                                    D_800CD2FC_main = 2;
                                    D_800D6A20_main = 2;
                                    break;
                                case G_IM_SIZ_8b:
                                    D_800CD2FC_main = 1;
                                    D_800D6A20_main = 1;
                                    break;
                                case G_IM_SIZ_4b:
                                    D_800CD2FC_main = 0;
                                    D_800D6A20_main = 0;
                                    break;
                                default:
                                    D_800CD2FC_main = 2;
                                    D_800D6A20_main = 2;
                                    break;
                            }
                            gDPSetTile((*gfx)++, texture->unk1C, texture->unk1D, (((maxS - minS + 1) * D_800CD2FC_main + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, minS << 2, minT << 2, maxS << 2, maxT << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, texture->unk1D, (((maxS - minS + 1) * D_800D6A20_main + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, minS << 2, minT << 2, maxS << 2, maxT << 2);
                        } else {
                            switch (texture->unk1D) {
                                case G_IM_SIZ_16b:
                                    D_800CCF88_main = G_IM_SIZ_16b;
                                    D_800CD2FC_main = 0;
                                    D_800D6A20_main = 2;
                                    D_800C952C_main = 2;
                                    D_800D1FFC_main = 0;
                                    break;
                                case G_IM_SIZ_8b:
                                    D_800CCF88_main = G_IM_SIZ_16b;
                                    D_800CD2FC_main = 1;
                                    D_800D6A20_main = 1;
                                    D_800C952C_main = 1;
                                    D_800D1FFC_main = 1;
                                    break;
                                case G_IM_SIZ_4b:
                                    D_800CCF88_main = G_IM_SIZ_16b;
                                    D_800CD2FC_main = 3;
                                    D_800D6A20_main = 0;
                                    D_800C952C_main = 0;
                                    D_800D1FFC_main = 2;
                                    break;
                                default:
                                    D_800CCF88_main = G_IM_SIZ_32b;
                                    D_800CD2FC_main = 0;
                                    D_800D6A20_main = 4;
                                    D_800C952C_main = 2;
                                    D_800D1FFC_main = 0;
                                    break;
                            }
                            gDPLoadTextureBlock((*gfx)++, image, texture->unk1C, HMF_TEXTURE_SIZE,
                                                texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2],
                                                HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    } else {
                        if (texture->unk24 < 16) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24 >> 1, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 1, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_4b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, minS, minT, maxS + 1, maxT + 1, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    }
                } else {
                    segment = textureEntry->unk4;
                    if (segment != -1) {
                        palette = (u8 *)(segment << 24);
                        *flags |= 0x40000;
                        gfx = &gMainGfxPos;
                        D_800D5544_main = 1;
                    } else {
                        palette = texture->unk_30->data;
                        if (D_800D5544_main == 0 && (((((u32)D_800C9940_main >> 13) ^ 1) & 1) && (changed ^ 1))) {
                            gfx = &D_800D6A88_main;
                            D_800CC0AC_main = D_800D0440_main;
                        } else {
                            gfx = &gMainGfxPos;
                        }
                    }
                    if (D_800B19F4_main != G_TT_RGBA16) {
                        D_800B19F4_main = G_TT_RGBA16;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
                    }
                    if (texture->unk_30->colorCount <= 16) {
                        gDPLoadTLUT_pal16((*gfx)++, 0, palette);
                        if (texture->unk24 < 16) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24 >> 1, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 1, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_4b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, minS, minT, maxS + 1, maxT + 1, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    } else {
                        gDPLoadTLUT_pal256((*gfx)++, palette);
                        if (texture->unk24 < 8) {
                            gfx = &gMainGfxPos;
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((texture->unk24 + 8) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((texture->unk24 + 8) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile((*gfx)++, image, texture->unk1C, G_IM_SIZ_8b, texture->unk24, texture->unk26, minS, minT, maxS, maxT, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock((*gfx)++, image, texture->unk1C, G_IM_SIZ_8b, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    }
                }
                D_800D5544_main = 1;
            }
        }
    }
    if (D_800CE1CE_main - D_800CDD66_main > 32) {
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + D_800CDD66_main * sizeof(Vtx)), 32, 0);
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + (D_800CDD66_main + 32) * sizeof(Vtx)), D_800CE1CE_main - D_800CDD66_main - 32, 32);
    } else {
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + D_800CDD66_main * sizeof(Vtx)), D_800CE1CE_main - D_800CDD66_main, 0);
    }
    face = D_800CD6B0_main;
    for (i = 0; i < D_800D0A44_main; i++) {
        if (face->count == 3) {
            if (i + 1 < D_800D0A44_main && face[1].count == 3) {
                gSP2Triangles(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], 0,
                              face[1].indices[0], face[1].indices[1], face[1].indices[2], 0);
                i++;
                face += 2;
            } else {
                gSP1Triangle(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], 0);
                face++;
            }
        } else {
            gSP1Quadrangle(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], face->indices[3], 0);
            face++;
        }
    }
    D_800CDD66_main = D_800CE1CE_main;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80029FB4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002A358_main);

void func_8002AC5C_main(u16 flags) {
    u8 mode;

    mode = (flags >> 7) & 3;
    if (mode != D_800D1F2A_main) {
        D_800D1F2A_main = mode;
        gDPSetTextureFilter(gMainGfxPos++, D_800A0AE0_main[mode]);
    }
    if (D_800D20A0_main != D_800D211C_main) {
        D_800D211C_main = D_800D20A0_main;
        if (!D_800D20A0_main) {
            gSPSetGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        } else {
            gSPClearGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        }
    }
    mode = (flags >> 9) & 3;
    if (mode != D_800CD2A0_main) {
        D_800CD2A0_main = mode;
        switch (mode) {
            case 0:
                gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
                break;
            case 1:
                gDPSetColorDither(gMainGfxPos++, G_CD_NOISE);
                break;
            case 2:
                gDPSetColorDither(gMainGfxPos++, G_CD_BAYER);
                break;
            case 3:
                gDPSetColorDither(gMainGfxPos++, G_CD_MAGICSQ);
                break;
        }
    }
    if (D_800CE1C6_main) {
        gSPFogPosition(gMainGfxPos++, D_800D6B64_main, D_800CC0B6_main);
        gDPSetFogColor(gMainGfxPos++, D_800D0599_main, D_800D41C4_main, D_800CDA84_main, 255);
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AF40_main);

void func_8002AFEC_main(HmfData *hmf, s32 flags, s16 objectIndex) {
    if (D_800D1F74_main != flags || (flags & 0xE000000)) {
        D_800D1F74_main = flags;
        gSPDisplayList(gMainGfxPos++, D_800A0A80_main);
        if (flags & 0x2000) {
            gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK);
        }
        if (D_800CE1C6_main) {
            gDPSetCycleType(gMainGfxPos++, G_CYC_2CYCLE);
            gSPSetGeometryMode(gMainGfxPos++, G_FOG);
        }
        if (flags & 0x6000000) {
            func_8002C0EC_main(hmf, objectIndex);
        } else if (flags & 0x8000000) {
            func_8002B104_main(hmf, objectIndex);
        }
    }
}

void func_8002B104_main(HmfData *hmf, s16 objectIndex) {
    HuMtx4F mtx;
    HmfData_Unk84_Entry2 *texture;

    if (hmf->unk60[objectIndex].unk1C == 255) {
        return;
    }
    gDPPipeSync(gMainGfxPos++);
    func_8007AB68_main(mtx, &D_800CE20C_main->lookAt,
                       D_800D10F4_main->pos.x, D_800D10F4_main->pos.y, D_800D10F4_main->pos.z,
                       D_800D10F4_main->at.x, D_800D10F4_main->at.y, D_800D10F4_main->at.z,
                       D_800D10F4_main->up.x, D_800D10F4_main->up.y, D_800D10F4_main->up.z);
    gSPLookAt(gMainGfxPos++, &D_800CE20C_main->lookAt);
    gSPTexture(gMainGfxPos++, 1984, 1984, 0, G_TX_RENDERTILE, G_ON);
    if (hmf->unk9C == NULL) {
        texture = hmf->unk84[hmf->unk60[objectIndex].unk1C].unkC;
    } else {
        texture = hmf->unk9C;
    }
    func_8002B2AC_main(texture, 0, 0);
    gSPSetGeometryMode(gMainGfxPos++, G_TEXTURE_GEN | G_LIGHTING);
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B2AC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C0EC_main);

s32 func_8002C4C0_main(HmfData *arg0, s16 arg1, HuMtx4F arg2, HuMtx4F arg3) {
    if (!(arg0->unk60[arg1].unk50 & 0x70000000)) {
        return 0;
    }
    func_80018544_main(arg2, arg3);
    return 1;
}

void func_8002C520_main(HmfData *hmf, s16 nodeIndex, HuMtx4F mtx) {
    D_800D138A_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    if (hmf->unk80 == (HmfMotionNode *)-1 && hmf->unk64 != 0) {
        func_8002C5B8_main(hmf, 0, nodeIndex);
        func_8002367C_main(mtx, D_800D5A00_main[D_800D138A_main]);
    }
}

s32 func_8002C5B8_main(HmfData *hmf, s16 nodeIndex, s16 targetIndex) {
    HuMtx4F mtx;
    HmfSkeletonNode *node;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk68[nodeIndex];
    changed = 0;
    guMtxIdentF(mtx);
    if (node->unk08.x != 0.0f || node->unk08.y != 0.0f || node->unk08.z != 0.0f) {
        func_80017C10_main(mtx, node->unk08.x, node->unk08.y, node->unk08.z);
        changed = 1;
    }
    if (node->unk14.x != 0.0f || node->unk14.y != 0.0f || node->unk14.z != 0.0f) {
        hmf->unkD4(mtx, node->unk14.x, node->unk14.y, node->unk14.z);
        changed = 1;
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++D_800D138A_main;
        func_80018044_main(mtx, D_800D59C0_main[matrixIndex], D_800D59C0_main[matrixIndex + 1]);
    }
    if (targetIndex == nodeIndex) {
        return 0;
    }
    if (node->unk04 != 0 && func_8002C5B8_main(hmf, nodeIndex + node->unk04, targetIndex) == 0) {
        return 0;
    }
    if (changed) {
        D_800D138A_main--;
    }
    if (node->unk02 != 0) {
        if (func_8002C5B8_main(hmf, nodeIndex + node->unk02, targetIndex) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_8002C834_main(HmfData *arg0, char *name) {
    s16 hash;
    s16 i;

    hash = func_80011460_main((u8 *)name);
    for (i = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk26 == hash && strcmp(arg0->unk60[i].unk00, name) == 0) {
            break;
        }
    }
    if (i == arg0->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", name);
        return -1;
    }
    return i;
}

void func_8002C914_main(HmfData *hmf, char *name, HmfData *replacement) {
    s16 objectIndex;

    objectIndex = func_8002C834_main(hmf, name);
    if (objectIndex != -1) {
        func_8002C960_main(hmf, objectIndex, replacement);
    }
}

void func_8002C960_main(HmfData *hmf, s16 objectIndex, HmfData *replacement) {
    s16 i;
    s16 hash;
    s16 j;
    HmfSkeletonNode *node;

    hash = hmf->unk60[objectIndex].unk26;
    for (i = 0; i < replacement->unk10; i++) {
        if (replacement->unk60[i].unk26 == hash &&
            strcmp(replacement->unk60[i].unk00, hmf->unk60[objectIndex].unk00) == 0) {
            break;
        }
    }
    if (i != replacement->unk10) {
        for (j = 0; j < hmf->unk64; j++) {
            node = &hmf->unk68[j];
            if (node->unk00 == objectIndex) {
                node->unk48 = replacement;
                node->unk00 = i;
            }
        }
    }
}

void func_8002CAE4_main(HmfData *hmf) {
    if (hmf->unk14 != 0) {
        D_800D5214_main = 0;
        D_800D138A_main = 0;
        func_8008A070_main(D_800D5A00_main[0][0]);
        if (hmf->unk80 == (HmfMotionNode *)-1) {
            if (hmf->unk64 != 0) {
                func_8002CB6C_main(hmf, 0);
            }
        } else if (hmf->unk16 != 0) {
            func_8002CDF4_main(hmf, 0);
        }
    }
}

void func_8002CB6C_main(HmfData *hmf, s16 nodeIndex) {
    HuMtx4F mtx;
    HmfSkeletonNode *node;
    s8 scaled;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk68[nodeIndex];
    scaled = 0;
    changed = 0;
    func_8008A070_main(mtx[0]);
    if (hmf->unk8C == NULL) {
        if (node->unk08.x != 0.0f || node->unk08.y != 0.0f || node->unk08.z != 0.0f) {
            func_80017C10_main(mtx, node->unk08.x, node->unk08.y, node->unk08.z);
            changed = 1;
        }
        if (node->unk14.x != 0.0f || node->unk14.y != 0.0f || node->unk14.z != 0.0f) {
            hmf->unkD4(mtx, node->unk14.x, node->unk14.y, node->unk14.z);
            changed = 1;
        }
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        func_80017CD0_main(mtx, node->scale.x, node->scale.y, node->scale.z);
        scaled = 1;
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++D_800D138A_main;
        func_80018044_main(mtx, D_800D59C0_main[matrixIndex], D_800D59C0_main[matrixIndex + 1]);
    }
    func_8002367C_main(node->unk4C, D_800D5A00_main[D_800D138A_main]);
    if (node->unk04 != 0) {
        func_8002CB6C_main(hmf, nodeIndex + node->unk04);
    }
    if (changed) {
        D_800D138A_main--;
    }
    if (scaled) {
        D_800D5214_main--;
    }
    if (node->unk02 != 0) {
        func_8002CB6C_main(hmf, nodeIndex + node->unk02);
    }
}

void func_8002CDF4_main(HmfData *hmf, s16 nodeIndex) {
    HuMtx4F mtx;
    HmfMotionNode *node;
    s16 i;
    s16 child;
    s8 scaled;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk80[nodeIndex];
    scaled = 0;
    changed = 0;
    func_8008A070_main(mtx[0]);
    if (node->basePos.x != 0.0f || node->basePos.y != 0.0f || node->basePos.z != 0.0f) {
        func_80017C10_main(mtx, node->basePos.x, node->basePos.y, node->basePos.z);
        changed = 1;
    }
    if (node->baseRot.x != 0.0f || node->baseRot.y != 0.0f || node->baseRot.z != 0.0f) {
        hmf->unkD4(mtx, node->baseRot.x, node->baseRot.y, node->baseRot.z);
        changed = 1;
    }
    if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
        func_80017CD0_main(mtx, node->baseScale.x, node->baseScale.y, node->baseScale.z);
        scaled = 1;
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++D_800D138A_main;
        func_80018044_main(mtx, D_800D59C0_main[matrixIndex], D_800D59C0_main[matrixIndex + 1]);
    }
    func_8002367C_main(node->unk58, D_800D5A00_main[D_800D138A_main]);
    for (i = 0; i < node->unk00; i++) {
        child = node->unk50[i];
        if (child & 0x8000) {
            if (child != -1) {
                func_8002CDF4_main(hmf, child & 0x7FFF);
            }
        }
    }
    if (changed) {
        D_800D138A_main--;
    }
    if (scaled) {
        D_800D5214_main--;
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D094_main);

void func_8002D260_main(void) {
    s16 i;

    func_80030030_main(1.0f);
    D_800CCF58_main = HuMemAlloc(HU3D_MODEL_MAX * sizeof(*D_800CCF58_main));
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        D_800CCF58_main[i].unk02 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D2D8_main);

s32 func_8002D3AC_main(HmfMotionFile *file) {
    return (s16)func_8002D2D8_main(file, NULL);
}

s32 func_8002D3D0_main(HmfData *hmf, HmfMotionFile *file, s32 arg2) {
    s16 modelIndex = arg2;
    u32 size;
    HmfMotionFile *copy;
    s32 result;

    D_800CE2B4_main = arg2 + 0x2874;
    D_800CCF58_main[modelIndex].unk00 = 0;
    if (hmf == NULL) {
        size = file->size + 8;
        copy = HuMemAllocTag(size, D_800CE2B4_main);
        bcopy(file, copy, size);
        func_8002DF2C_main(&D_800CCF58_main[modelIndex], copy);
        result = 1;
    } else {
        result = func_8002D5B0_main(&D_800CCF58_main[modelIndex], hmf) != 0;
    }
    return result;
}

void func_8002D4B8_main(s32 arg0) {
    s16 modelIndex = arg0;

    if (modelIndex != 0xFF) {
        HuMemFreeAllWithTag(modelIndex + 0x2874);
        D_800CCF58_main[modelIndex].unk02 = -1;
    }
}

void func_8002D514_main(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (D_800CCF58_main[i].unk02 != -1) {
            HuMemFreeAllWithTag(i + 0x2874);
            D_800CCF58_main[i].unk02 = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D5B0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DA98_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DD4C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DF2C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DFF8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E78C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E8E8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002EAC0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002F60C_main);

void func_8002FB08_main(HmfData *arg0, f32 arg1) {
    if (arg0->unk98->unk02 & 1) {
        return;
    }

    arg0->unk98->unk08 = arg1 * D_800D2120_main + arg0->unk98->unk08;

    if (!(arg0->unk98->unk08 >= arg0->unk98->unk04)) {
        return;
    }

    if (arg0->unk98->unk02 & 2) {
        arg0->unk98->unk08 = 0;
    } else {
        arg0->unk98->unk08 = arg0->unk98->unk04;
    }
}

void func_8002FB98_main(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg1 * D_800D2120_main + arg0->unkA0;

    if (arg0->unkA0 >= arg0->unk8C->unk02) {
        if (D_800A1160_main != 0) {
            arg0->unkA0 = 0;
        } else {
            arg0->unkA0 = arg0->unk8C->unk02;
        }
    }
}

void func_8002FC14_main(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg0->unkA0 - arg1 * D_800D2120_main;

    if (arg0->unkA0 < 0) {
        if (D_800A1160_main != 0) {
            arg0->unkA0 = arg0->unk8C->unk02;
        } else {
            arg0->unkA0 = 0;
        }
    }
}

f32 func_8002FC7C_main(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed) {
    speed *= D_800A0A78_main * D_800D2120_main;
    if (!(flags & 9)) {
        if (!(flags & 4)) {
            frame += speed;
            if (frame >= arg0->unk02) {
                if (flags & 2) {
                    return start;
                } else {
                    return arg0->unk02;
                }
            }
        } else {
            frame -= speed;
            if (frame < start) {
                if (flags & 2) {
                    return arg0->unk02 - speed;
                } else {
                    return start;
                }
            }
        }
    }
    return frame;
}

void func_8002FD48_main(HmfData *arg0) {
    arg0->unkA0 = 0;
}

void func_8002FD50_main(HmfData *arg0) {
    arg0->unkA0 = arg0->unk8C->unk02 - 1;
}

s16 func_8002FD70_main(HmfData *arg0) {
    return arg0->unkA0;
}

void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4) {
    func_8002FE08_main(arg0, arg1, arg2, arg3, arg4, 0x8000);
}

void func_8002FDCC_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4) {
    func_8002FE08_main(arg0, arg1, arg2, arg3, arg4, 0);
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FE08_main);

void func_80030030_main(f32 arg0) {
    D_800D2120_main = arg0;
}
