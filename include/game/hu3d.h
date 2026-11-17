#ifndef _GAME_HU3D_H
#define _GAME_HU3D_H

#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "types.h"
#include "game/hmfvertex.h"

#define HU3D_MODEL_MAX 128

#define HU3D_ATTR_NONE 0
#define HU3D_ATTR_STATIC (1 << 0) // drawn from prebuilt static display lists
#define HU3D_ATTR_UNK2 (1 << 1)
#define HU3D_ATTR_DISPOFF (1 << 2)
#define HU3D_ATTR_FILEFREE (1 << 3)    // source file data is freed after loading
#define HU3D_ATTR_DYNAMICFREE (1 << 4) // dynamic model data has been freed

// Antialiasing mode (render mode AA_EN / IM_RD)
#define HU3D_ATTR_AA_SHIFT 5
#define HU3D_ATTR_AA_MASK (3 << HU3D_ATTR_AA_SHIFT)
#define HU3D_ATTR_AA_OFF (0 << HU3D_ATTR_AA_SHIFT)
#define HU3D_ATTR_AA (1 << HU3D_ATTR_AA_SHIFT)         // full AA (AA_EN | IM_RD)
#define HU3D_ATTR_AA_REDUCED (2 << HU3D_ATTR_AA_SHIFT) // reduced AA (AA_EN)

// Z-buffer mode (render mode Z_CMP / Z_UPD)
#define HU3D_ATTR_ZBUF_SHIFT 7
#define HU3D_ATTR_ZBUF_MASK (3 << HU3D_ATTR_ZBUF_SHIFT)
#define HU3D_ATTR_ZBUF_OFF (0 << HU3D_ATTR_ZBUF_SHIFT)
#define HU3D_ATTR_ZBUF_ON (1 << HU3D_ATTR_ZBUF_SHIFT)
#define HU3D_ATTR_ZBUF_OBJ (2 << HU3D_ATTR_ZBUF_SHIFT) // decided by each object's flags

#define HU3D_ATTR_LIGHTING (1 << 9)
#define HU3D_ATTR_LAYER_SHIFT 10
#define HU3D_ATTR_LAYER_MASK (7 << HU3D_ATTR_LAYER_SHIFT)
#define HU3D_ATTR_OBJCULL (1 << 13)    // per-object culling of static display lists
#define HU3D_ATTR_HOOK (1 << 14)       // drawn attached to another model's object (Hu3DModelHookSet)
#define HU3D_ATTR_NOPAUSE (1 << 15)
#define HU3D_ATTR_PRIMCOLOR (1 << 16)  // use the Hu3DModelPrimColorSet / Hu3DModelEnvColorSet colors
#define HU3D_ATTR_TEX_OPA (1 << 17)    // textured materials drawn without alpha coverage
#define HU3D_ATTR_NOVIEW (1 << 18)     // model matrix is not multiplied by the camera view
#define HU3D_ATTR_ZMASK (1 << 19)      // drawn with a zero color/alpha combine, depth only
#define HU3D_ATTR_MAPDATA (1 << 21)    // load map attribute and camera records
#define HU3D_ATTR_SHAPECACHE (1 << 22) // build a shape cache with the display lists
#define HU3D_ATTR_REMAKESTATIC (1 << 23) // static display lists need rebuilding
#define HU3D_ATTR_PARTICLE (1 << 24)

// Attributes that require static display lists to be rebuilt when changed
#define HU3D_ATTR_REMAKE_MASK                                                                        \
    (HU3D_ATTR_UNK2 | HU3D_ATTR_ZBUF_MASK | HU3D_ATTR_LIGHTING | HU3D_ATTR_LAYER_MASK |             \
     HU3D_ATTR_OBJCULL | HU3D_ATTR_PRIMCOLOR | HU3D_ATTR_TEX_OPA | HU3D_ATTR_ZMASK)

#define HU3D_CAM0 (1 << 0)
#define HU3D_CAM1 (1 << 1)
#define HU3D_CAM2 (1 << 2)
#define HU3D_CAM3 (1 << 3)
#define HU3D_CAM4 (1 << 4)
#define HU3D_CAM5 (1 << 5)
#define HU3D_CAM6 (1 << 6)
#define HU3D_CAM7 (1 << 7)
#define HU3D_CAM_ALL 0xFF
#define HU3D_CAM_NONE 0

#define HMF_TEXTURE_MASK(size) ((size) <= 2 ? 1 : (size) <= 4 ? 2 \
                                              : (size) <= 8   ? 3 \
                                              : (size) <= 16  ? 4 \
                                              : (size) <= 32  ? 5 \
                                              : (size) <= 64  ? 6 \
                                              : (size) <= 128 ? 7 \
                                              : (size) <= 256 ? 8 \
                                                              : 9)

typedef struct {
    Gfx *unk00[4];
    void *unk10;
    void *unk14;
} HmfModelData_Unk64_Unk3C_Struct;

typedef struct {
    u8 unk00;
    s8 unk01[3];
    s16 unk04[4];
    f32 unk0C[4];
    f32 unk1C[4];
    u8 unk2C[4];
    s16 unk30;
    s16 unk32;
} HmfModelData_Unk64_Unk60_Unk54_Struct;

struct HmfData;
struct HmfData_Unk84_Entry;

typedef struct {
    char unk00[0x1C];
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    char unk30[0x12];
    s16 boundsMin[3];
    s16 boundsMax[3];
    char unk4E[2];
    s32 unk50;
    HmfModelData_Unk64_Unk60_Unk54_Struct *unk54;
    struct HmfData *unk58;
    struct HmfData_Unk84_Entry *unk5C;
    struct HmfData_Unk84_Entry *unk60;
    Gfx *unk64;
} HmfModelData_Unk64_Unk60_Struct;

struct HmfModelEntry;

typedef struct {
    u8 target;
    u8 component;
    u8 interpolation;
    u8 flags;
    s16 objectIndex;
    s16 nodeIndex;
    s16 targetIndex;
    s16 timeIndex;
    s16 valueIndex;
    s16 keyCount;
} HmfMotionChannel;

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ HmfMotionChannel **unk08;
    /* 0x0C */ u8 *unk0C;
    /* 0x10 */ s16 *unk10;
    /* 0x14 */ f32 *unk14;
} HmfModelData_Unk64_Unk8C_Struct; // Size 0x18

typedef struct {
    u8 components[4];
} HmfAnimColor;

typedef struct {
    s16 materialIndex;
    s16 keyCount;
    s16 flags;
    s16 duration;
    u16 *times;
    HmfAnimColor *colors;
} HmfMaterialAnimTrack;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    char unk06[2];
    f32 unk08;
    HmfMaterialAnimTrack tracks[16];
} HmfModelData_Unk64_Unk98_Struct;

typedef struct {
    /* 0x00 */ char name[0x1C];
    /* 0x1C */ u8 refCount;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 colorCount;
    /* 0x20 */ s16 nameHash;
    /* 0x24 */ struct HmfData *owner;
    /* 0x28 */ u8 *data;
} HmfPaletteData; // Size 0x2C

typedef struct {
    char name[0x1C];
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u16 unk20;
    u16 nameHash;
    u16 unk24;
    u16 unk26;
    u8 *unk28;
    struct HmfData *owner;
    HmfPaletteData *unk_30;
} HmfData_Unk84_Entry2;

// New struct for the array at unk84 (0x10 bytes per entry)
typedef struct HmfData_Unk84_Entry {
    u8 unk0[3];
    s8 unk3;
    u8 unk4;
    u8 unk5[4];
    u8 unk9;
    u8 unkA[2];
    HmfData_Unk84_Entry2 *unkC; // Pointer to something with unk30 field
} HmfData_Unk84_Entry;

typedef struct {
    /* 0x00 */ s8 unk00; // UnkLightData_unk02?
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ char unk07[1];
    /* 0x08 */ Light unk08[3];
} HmfData_UnkD0; // Size 0x38

typedef struct {
    /* 0x00 */ u8 count;
    /* 0x01 */ s8 normal[3];
    /* 0x04 */ s16 indices[4];
    /* 0x0C */ Vec center;
} HmfVertexGroup; // Size 0x18

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    char unk06[2];
    Vec unk08;
    Vec unk14;
    Vec scale;
    Vec pos;
    Vec rot;
    u8 unk44;
    u8 unk45;
    char unk46[2];
    struct HmfData *unk48;
    HuMtx4F unk4C;
} HmfSkeletonNode;

typedef struct {
    s16 unk00;
    char unk02[2];
    Vec basePos;
    Vec baseRot;
    Vec baseScale;
    Vec pos;
    Vec rot;
    Vec scale;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    char unk4F[1];
    s16 *unk50;
    struct HmfData *unk54;
    HuMtx4F unk58;
} HmfMotionNode;

typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u8 unk0A;
} HmfMaterialData;

typedef struct {
    Gfx **unk00;
} HmfDisplayLists;

typedef struct {
    char unk00[0x1C];
    s16 unk1C;
    char unk1E[2];
    s32 unk20;
    s32 unk24;
    s32 unk28;
} HmfMapData;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    char unk06[2];
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} HmfData_UnkBC;

typedef struct {
    s16 vertexCount;
    s16 frames[2];
    s16 currentBuffer;
    s16 (*positions[2])[3];
    s8 (*normals[2])[3];
    u8 *visited;
} HmfVertexAnimCache;

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

typedef struct HmfData {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ char unk02[8];
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
    /* 0x0C */ s8 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12; // Changed from char[2] since it's used as s16
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22; // DISP chunk count
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26; // map count
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 *unk2C; // file start
    /* 0x30 */ u8 *unk30; // chunk data end
    /* 0x34 */ u8 *unk34; // chunk data start
    /* 0x38 */ u8 *unk38; // MAP1 chunk
    /* 0x3C */ HmfModelData_Unk64_Unk3C_Struct *unk3C;
    /* 0x40 */ Vtx *unk40;
    /* 0x44 */ Vtx *unk44[3];
    /* 0x50 */ s16 (*unk50)[3];
    /* 0x54 */ s8 (*unk54)[3];
    /* 0x58 */ HmfVertexAnimCache *unk58;
    /* 0x5C */ s16 *unk5C;
    /* 0x60 */ HmfModelData_Unk64_Unk60_Struct *unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char unk66[2];
    /* 0x68 */ HmfSkeletonNode *unk68;
    /* 0x6C */ char unk6C[0x14];
    /* 0x80 */ HmfMotionNode *unk80;
    /* 0x84 */ HmfData_Unk84_Entry *unk84; // Array of entries
    /* 0x88 */ HmfMaterialData *unk88;
    /* 0x8C */ HmfModelData_Unk64_Unk8C_Struct *unk8C;
    /* 0x90 */ HmfModelData_Unk64_Unk8C_Struct *unk90;
    /* 0x94 */ HmfModelData_Unk64_Unk8C_Struct *unk94;
    /* 0x98 */ HmfModelData_Unk64_Unk98_Struct *unk98;
    /* 0x9C */ HmfData_Unk84_Entry2 *unk9C;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ HmfVertexGroup *unkB0;
    /* 0xB4 */ HmfDispData *unkB4;
    /* 0xB8 */ HmfMtnData *unkB8;
    /* 0xBC */ HmfData_UnkBC *unkBC;
    /* 0xC0 */ void *unkC0; // light data only?
    /* 0xC4 */ HmfMapData *unkC4;
    /* 0xC8 */ u8 *unkC8; // animation slots
    /* 0xCC */ HmfDisplayLists *unkCC;
    /* 0xD0 */ HmfData_UnkD0 *unkD0;
    /* 0xD4 */ void (*unkD4)(HuMtx4F, f32, f32, f32);
    /* 0xD8 */ void (*unkD8)(HuMtx4F, f32, f32, f32);
} HmfData;

typedef struct {
    /* 0x00 */ u8 next;
    /* 0x01 */ u8 prev;
    /* 0x02 */ s16 objectIndex;
    /* 0x04 */ f32 depth;
} HmfDrawEntry; // Size 0x8

typedef struct {
    /* 0x00 */ s16 objectIndex;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ HuMtx4F mtx;
    /* 0x44 */ Mtx *fixedMtx;
    /* 0x48 */ HmfData *hmf;
    /* 0x4C */ s32 objectFlags;
    /* 0x50 */ s32 modelFlags;
    /* 0x54 */ HmfData_UnkD0 *light;
} HmfDrawObject; // Size 0x58

typedef struct {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
} HmfModelData_UnkBC_Unk58_Struct; // Size 0x30

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ union {
        f32 f;
        s32 i;
    } unk08;
    /* 0x0C */ union {
        f32 f;
        s32 i;
    } unk0C;
    /* 0x10 */ union {
        f32 f;
        s32 i;
    } unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ void (*unk18)(s16);
    /* 0x1C */ union {
        f32 f;
        s32 i;
    } unk1C;
    /* 0x20 */ union {
        f32 f;
        s32 i;
    } unk20;
    /* 0x24 */ union {
        f32 f;
        s32 i;
    } unk24;
    /* 0x28 */ Vec unk28[4];
    /* 0x58 */ HmfModelData_UnkBC_Unk58_Struct *unk58;
} HmfModelData_UnkBC_Struct; // Size 0x5C

typedef struct HmfModel {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 cameraBit;
    /* 0x02 */ u8 motId;
    /* 0x03 */ u8 motAttr;
    /* 0x04 */ u8 motIdShift;
    /* 0x05 */ u8 motShiftAttr;
    /* 0x06 */ u8 motIdShape;
    /* 0x07 */ u8 motShapeAttr;
    /* 0x08 */ u8 unk08;
    /* 0x09 */ u8 unk09;
    /* 0x0A */ u8 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ char unk12[2];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 attr;
    /* 0x1C */ Vec pos;
    /* 0x28 */ Vec rot;
    /* 0x34 */ Vec scale;
    /* 0x40 */ f32 motTime;
    /* 0x44 */ f32 motSpeed;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 motShiftTime;
    /* 0x50 */ f32 motShiftSpeed;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 motShapeTime;
    /* 0x5C */ f32 motShapeSpeed;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ HmfData *hmf;
    /* 0x68 */ HmfData *unk68;
    /* 0x6C */ HmfData *unk6C;
    /* 0x70 */ void (*hookFunc)(Gfx **, s32, s32);
    /* 0x74 */ HuMtx4F mtx;
    /* 0xB4 */ HmfData_UnkD0 *unkB4;
    /* 0xB8 */ char unkB8[4];
    /* 0xBC */ HmfModelData_UnkBC_Struct *unkBC;
} HmfModel; // Size 0xC0

typedef struct HmfAnim {
    /* 0x00 */ s16 animIdx;
    /* 0x02 */ s16 frame;
    /* 0x04 */ s16 rot;
    /* 0x06 */ s16 interp;
    /* 0x08 */ char unk_08[2];
    /* 0x0A */ u8 flags;
    /* 0x0B */ u8 speed; // 4-bit fixed point (0x10 = 1.0)
} HmfAnim;               // Size 0xC

typedef struct HmfAnimFrame {
    /* 0x00 */ s16 unk00; // image index
    /* 0x02 */ s16 time;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ char unk07[1];
} HmfAnimFrame; // Size 0x8

typedef struct HmfAnimRot {
    /* 0x00 */ s16 frameCount;
    /* 0x02 */ s16 totalFrames;
    /* 0x04 */ HmfAnimFrame *frames;
} HmfAnimRot; // Size 0x8

typedef struct HmfAnimImage {
    /* 0x00 */ s16 width;
    /* 0x02 */ s16 height;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 colorCount;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ void *palette;
    /* 0x10 */ void *data;
} HmfAnimImage; // Size 0x14

typedef struct HmfAnimSet {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 rotCount;
    /* 0x06 */ s16 interp;
    /* 0x08 */ s16 refCount;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ HmfAnimImage *unk0C;
    /* 0x10 */ HmfAnimRot *rot;
    /* 0x14 */ void *unk14;
} HmfAnimSet; // Size 0x18

typedef struct HmfModelSet {
    /* 0x00 */ s16 nodeCount;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ HuMtx4F *unk_08;
} HmfModelSet; // Size 0xC

typedef struct HmfColorKey {
    /* 0x00 */ u8 time; // 0xFF terminates the list
    /* 0x01 */ u8 color[4];
} HmfColorKey; // Size 0x5

typedef struct HmfModelEntry {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 nodeIdx;
    /* 0x06 */ s16 pointIdx;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u16 flags;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 colorR;
    /* 0x14 */ u8 colorG;
    /* 0x15 */ u8 colorB;
    /* 0x16 */ u8 colorStart[4];
    /* 0x1A */ u8 colorEnd[4];
    /* 0x1E */ char unk_1E[2];
    /* 0x20 */ HmfColorKey *unk_20;
} HmfModelEntry; // Size 0x24

#ifndef NO_EXTERN_VARIABLES
extern HmfAnim *Hu3DAnimData;
extern HmfAnimSet *Hu3DAnimSetData;
extern HmfModelEntry *Hu3DSprModelData;

extern u8 Hu3DScreenClearF;
extern HmfModelData_Unk64_Unk8C_Struct *Hu3DMotion;
#endif

void Hu3DInit(void *arg0, void *arg1, u16 arg2, u16 arg3, u16 arg4, u8 arg5);
s32 Hu3DModelCreate(u8 *, u32);
s32 Hu3DModelLink(s16 linkMdlId);
s32 Hu3DModelDLCreate(u32 flags, void *dl, s32 mode);
s32 Hu3DHookFuncCreate(s32 arg0, void (*arg1)(Gfx **, s32, s32), u8 arg2);
void Hu3DModelKill(s16);
void Hu3DExec(void *arg0, u16 arg1);
void Hu3DScreenClear(u32 arg0, u32 arg1);
void Hu3DModelPosSet(s16 arg0, f32 x, f32 y, f32 z);
void Hu3DModelRotSet(s16 arg0, f32 x, f32 y, f32 z);
void Hu3DModelScaleSet(s16 arg0, f32 x, f32 y, f32 z);
void Hu3DModelAttrSet(s16 arg0, s32 arg1, s32 arg2);
void Hu3DModelObjAttrSet(s16 arg0, s32 arg1, s32 arg2);
void Hu3DModelRemakeStatic(s16);
void Hu3DModelDynamicFree(s16);
void Hu3DMotionModelSet(s16, s16);
void Hu3DMotionShiftSet(s16, s16, s16, s16, s16);
void Hu3DMotionTimeSet(s16, f32);
f32 Hu3DMotionShapeTimeGet(s16 arg0);
f32 Hu3DMotionShapeMaxTimeGet(s16 arg0);
f32 Hu3DMotionShiftTimeGet(s16 arg0);
void Hu3DMotionAttrSet(s16, s16, s16);
void Hu3DModelCameraSet(s16, s16);
void Hu3DModelLayerSet(s16, u32);
void Hu3DMotionSpeedSet(s16, f32);
void Hu3DModelVtxBufMake(s16);
void Hu3DMotionShapeSet(s16, s16, s16);
void Hu3DFogSet(s32, s32, s32, s32, u8);
s32 Hu3DMotionCreate(void *, s32);
void Hu3DMotionSet(s16, s16);
void Hu3DBGColorSet(s32, s32, s32);
void Hu3DModelLODSet(s16, s16, f32);
void Hu3DMotionReset(s16);

#ifndef NO_EXTERN_VARIABLES
extern HmfModel *Hu3DData;
#endif

s16 Hu3DModelLinkModeSet(s16 arg0, s8 arg1);
void Hu3DModelModeSet(s16 arg0, s32 arg1);
void Hu3DAllKill(void);
Gfx *Hu3DDLModelDraw(Gfx *arg0, s16 arg1, u16 arg2);
void Hu3DModelAllReset(void);
void Hu3DModelPosGet(s16 idx, Vec *arg1);
void Hu3DModelAllAttrSet(s16 arg0, s32 arg1);
void Hu3DModelObjAttrSetByName(s16 idx, char *name, s32 arg2, s32 arg3);
void Hu3DModelVtxMorph(s16 idx1, s16 idx2, f32 t);
void Hu3DModelObjVtxMorph(s16 idx1, s16 idx2, f32 arg2, char *name, s32 arg4);
void Hu3DModelObjVtxMorph2(s16 idx1, s16 idx2, f32 arg2, char *name1, char *name2, s32 arg5);
void HmfObjVtxMorph(HmfData *hmf1, HmfData *hmf2, f32 t, s16 node1, s16 node2, s32 full);
void Hu3DShapeModeSet(s16 arg0);
void *Hu3DModelObjPtrGet(s16 idx, const char *name);
void Hu3DModelVtxWave(s16 idx, f32 arg1, f32 arg2, s32 mode);
void Hu3DModelObjVtxWave(s16 idx, f32 arg1, f32 arg2, char *name, s16 mode);
void HmfVtxWave0(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count);
void HmfVtxWave1(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count);
void HmfVtxWave2(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count);
void Hu3DModelTexAnimChange(s16 idx, char *oldName, char *newName);
void Hu3DModelTexScroll(s16 idx, f32 x, f32 y, s32 width, s32 height);
void Hu3DModelObjTexScroll(s16 idx, f32 x, f32 y, u16 width, u16 height, const char *name, u8 reset);
void Hu3DModelObjVtxColorSet(s16 idx, char *name, u8 r, u8 g, u8 b, u8 reset);
void Hu3DModelFaceFlip(s16 idx);
void Hu3DFogClear(void);
void Hu3DModelHookSet(s16 idx, s16 parentIdx, const char *name);
void Hu3DModelAnimNameSet(s16 idx, char *name);
void Hu3DMotionNext(HmfModel *model, u16 speed);
void Hu3DMotionExecAnim(HmfModel *model);
f32 Hu3DMotionMotionMaxTimeGet(s16 arg0);
void Hu3DMotionAttrSetEx(s16 idx, s16 flags, s16 clear, s16 set);
void Hu3DModelLODExec(s16 idx);
s32 Hu3DModelLODCheck(s16 arg0);
void Hu3DDrawModeSet(s8 arg0);
void Hu3DModelPrimColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void Hu3DModelEnvColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void Hu3DModelColorSet(s16 idx, u8 r, u8 g, u8 b, u8 a);
void Hu3DLayerHookSet(s16 idx, void *func);
void Hu3DMotionModelSetEx(s16 arg0, s16 arg1);
void Hu3DModelTPLvlSet(s16 arg0, u8 arg1);
void Hu3DModelTPLvlInit(s16 idx);
void Hu3DLLightCreate(s16 arg0, s8 arg1);
void Hu3DLLightColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void Hu3DLLightDirSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void Hu3DModelFaceFlagSet(s16 idx);

#endif
