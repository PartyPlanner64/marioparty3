#include "common.h"
#include "game/camera.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/data.h"
#include "game/util.h"
#include "game/gamework.h"
#include "game/sprite.h"
#include "math.h"

#define CAMERA_KEEP 65535.0f

// Several distances are written as a float fraction of 200 units (e.g. 0.1f * 200.0), which folds into
// a double constant slightly off from the round value.

typedef struct RockinRacewayCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
} RockinRacewayCamera; // Size 0x24

typedef struct RockinRacewayCameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} RockinRacewayCameraPreset; // Size 0x1C

// Table of 2 rows of 4 of these allocated in func_80106B28_rockin_raceway, stored in
// D_80111B3C_rockin_raceway. func_80107E78_rockin_raceway records each racer object's transform.
typedef struct RockinRacewaySnapshot {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 active;
    /* 0x04 */ Vec trans;
    /* 0x10 */ Vec rot;
    /* 0x1C */ Vec scale;
} RockinRacewaySnapshot; // Size 0x28

// Saved model state, see func_80109044_rockin_raceway and func_80109134_rockin_raceway.
typedef struct RockinRacewayModelState {
    /* 0x00 */ s32 attr;
    /* 0x04 */ f32 motTime;
    /* 0x08 */ f32 motSpeed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
} RockinRacewayModelState; // Size 0x30

// Pool of 16 of these allocated in func_80109208_rockin_raceway, stored in D_80111B5C_rockin_raceway.
// func_801094EC_rockin_raceway claims a free entry, and func_80109384_rockin_raceway animates the
// sprite effect each frame until its animation finishes.
typedef struct RockinRacewayEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ f32 frame;
    /* 0x08 */ f32 speed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec scale;
} RockinRacewayEffect; // Size 0x30

// Per-racer state; a pointer to it is packed into the work bytes of each racer object
// (see func_8010EC0C_rockin_raceway / func_8010EC38_rockin_raceway).
typedef struct RockinRacewayRacer {
    /* 0x00 */ u8 unk00[0xA];
    /* 0x0A */ u16 unk0A; // racer slot
    /* 0x0C */ u16 unk0C; // player index
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u8 unk10[0xC];
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E; // button mask to press next
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 unk30[8];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ u16 unk4C;
    /* 0x4E */ u8 unk4E[6];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ Vec pos;
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ f32 unk68;
} RockinRacewayRacer;

// Saved sprite effect state, see func_801097A0_rockin_raceway and func_801098D8_rockin_raceway.
typedef struct RockinRacewayEffectState {
    /* 0x00 */ u16 active;
    /* 0x02 */ u16 motTime;
    /* 0x04 */ s32 attr;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
    /* 0x28 */ Vec scale;
} RockinRacewayEffectState; // Size 0x34

// Array of 4 of these allocated in func_80109DA8_rockin_raceway, stored in D_80111B40_rockin_raceway
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u16 numNodes;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ s32 *unk0C;
    /* 0x10 */ s32 *unk10;
    /* 0x14 */ f32 *unk14;
    /* 0x18 */ f32 *unk18;
    /* 0x1C */ s32 *unk1C;
    /* 0x20 */ u16 *unk20;
} Track; // Size 0x24

// Pool of 16 of these allocated in func_8010E2E4_rockin_raceway, stored in D_80111BD0_rockin_raceway.
// func_8010E344_rockin_raceway claims a free entry for a request, and func_8010E39C_rockin_raceway
// consumes requests until they expire, setting soundId back to -1 when done.
typedef struct {
    /* 0x00 */ s16 soundId; // -1 marks a free entry
    /* 0x02 */ s16 frames;  // counted down once per frame
    /* 0x04 */ s16 unk04;   // switched on as a type by func_8010E39C_rockin_raceway
    /* 0x06 */ s16 playerIndex;
} RockinRacewaySfx; // Size 0x8

// Pool of 16 of these allocated in func_8010CA1C_rockin_raceway, stored in D_80111C4C_rockin_raceway.
// func_8010CADC_rockin_raceway appends entries, and func_8010CC10_rockin_raceway folds unk0C
// into the accumulated position.
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unk0C;
} RockinRacewayVec; // Size 0x10

typedef union RockinRacewayWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} RockinRacewayWorkBytes;

// Pool of 8 of these allocated in func_80108578_rockin_raceway, stored in D_80111B48_rockin_raceway.
// func_80108760_rockin_raceway claims a free entry for a pair of blinking marker models, and
// func_80108864_rockin_raceway animates the entries each frame, alternating the visible model every
// duration frames and drifting position by the velocity vector.
typedef struct {
    /* 0x00 */ u16 active; // 0 marks a free entry
    /* 0x02 */ s16 modelA;
    /* 0x04 */ s16 modelB;
    /* 0x06 */ u16 timer;
    /* 0x08 */ u16 duration;
    /* 0x0A */ u16 flag;
    /* 0x0C */ f32 posX;
    /* 0x10 */ f32 posY;
    /* 0x14 */ f32 posZ;
    /* 0x18 */ f32 velX;
    /* 0x1C */ f32 velY;
    /* 0x20 */ f32 velZ;
} RockinRacewayFx; // Size 0x24

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern s32 D_801112C0_rockin_raceway[];
extern f32 D_801112E0_rockin_raceway[];
extern RockinRacewayCameraPreset D_80111350_rockin_raceway;
extern Vec D_80111414_rockin_raceway[4];
extern Vec D_80111444_rockin_raceway[12];
extern u8 D_801114D4_rockin_raceway[4];
extern s32 D_8011155C_rockin_raceway;
extern Gfx D_801116F0_rockin_raceway[];
extern u8 D_80111730_rockin_raceway[4];
extern u8 D_80111734_rockin_raceway[4];
extern s32 D_80111AC8_rockin_raceway;
extern s32 D_80111B00_rockin_raceway[2][6];
extern RockinRacewaySnapshot (*D_80111B3C_rockin_raceway)[4];
extern Track *D_80111B40_rockin_raceway;
extern RockinRacewayFx *D_80111B48_rockin_raceway;
extern omObjData *D_80111B4C_rockin_raceway;
extern RockinRacewayModelState *D_80111B50_rockin_raceway;
extern s16 D_80111B54_rockin_raceway;
extern omObjData *D_80111B58_rockin_raceway;
extern RockinRacewayEffect *D_80111B5C_rockin_raceway;
extern RockinRacewayEffectState *D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;
extern s16 *D_80111B68_rockin_raceway;
extern s16 D_80111B74_rockin_raceway;
extern RockinRacewaySfx *D_80111BD0_rockin_raceway;
extern s16 D_80111BD4_rockin_raceway;
extern s16 D_80111BD6_rockin_raceway;
extern omObjData *D_80111BD8_rockin_raceway;
extern RockinRacewayCamera D_80111BE0_rockin_raceway[2]; // target, origin
extern s16 D_80111C28_rockin_raceway;
extern s16 D_80111C2A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;
extern omObjData *D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway;
extern RockinRacewayVec *D_80111C4C_rockin_raceway;
// D_80111C50_rockin_raceway is a pool of 30 opaque 0x644-byte records,
// indexed by D_80111C58_rockin_raceway and filled out by D_80111C54_rockin_raceway.
extern u8 *D_80111C50_rockin_raceway;
extern s32 D_80111C54_rockin_raceway;
extern s32 D_80111C58_rockin_raceway;

void func_80105CB0_rockin_raceway(omObjData *object);
void func_80106B28_rockin_raceway(void);
void func_80108578_rockin_raceway(void);
void func_80108D84_rockin_raceway(void);
void func_80108ED4_rockin_raceway(omObjData *object);
void func_80109208_rockin_raceway(void);
void func_80109384_rockin_raceway(omObjData *object);
void func_801099AC_rockin_raceway(void);
void func_80109A04_rockin_raceway(omObjData *object);
u32 func_8010EC38_rockin_raceway(omObjData *object);
u16 func_8010A4C0_rockin_raceway(s32 dirAndFile);
s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct *sprite, u8 *color);
s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color);
void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);
void func_80109DA8_rockin_raceway(void);
void func_8010A504_rockin_raceway(void);
void func_8010B124_rockin_raceway(void);
void func_8010B774_rockin_raceway(void);
void func_8010C0D8_rockin_raceway(omObjData *object);
void func_8010C5E0_rockin_raceway(s32 arg0);
void func_8010CE90_rockin_raceway(omObjData *object);
void func_8010D5B8_rockin_raceway(void);
void func_8010E2E4_rockin_raceway(void);
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *players);
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *values);
s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801059A0_rockin_raceway);

void func_80105C24_rockin_raceway(omObjData *object) {
    object->func = func_80105CB0_rockin_raceway;
    func_80109DA8_rockin_raceway();
    func_801099AC_rockin_raceway();
    func_80108D84_rockin_raceway();
    func_80109208_rockin_raceway();
    func_8010A504_rockin_raceway();
    func_8010B124_rockin_raceway();
    func_80106B28_rockin_raceway();
    func_80108578_rockin_raceway();
    func_8010E2E4_rockin_raceway();
    func_8010B774_rockin_raceway();
    func_8010D5B8_rockin_raceway();
    if (_CheckFlag(10)) {
        D_80111AC8_rockin_raceway = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111740_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_8011174C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105CB0_rockin_raceway);

void func_80106A5C_rockin_raceway(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_80106A80_rockin_raceway(omObjData *object) {
    if (D_8011155C_rockin_raceway != 0) {
        if (D_8011155C_rockin_raceway == 1) {
            object->func = func_80106A5C_rockin_raceway;
        }
        D_8011155C_rockin_raceway--;
        return;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8011155C_rockin_raceway = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)D_8011155C_rockin_raceway);
        HuAudSeqFadeOut((s16)D_8011155C_rockin_raceway);
        func_8004AB0C_main((s16)D_8011155C_rockin_raceway);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106B28_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106DC8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801071D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010769C_rockin_raceway);

void func_80107958_rockin_raceway(RockinRacewayRacer *racer) {
    if (D_800D5558_main[racer->unk0C] & racer->unk1E) {
        racer->unk38 += D_801112E0_rockin_raceway[racer->unk1C] * 0.1f;
        if (racer->unk38 >= 1.0f) {
            racer->unk38 = 1.0f;
        }
        if (D_800D5558_main[racer->unk0C] == 0x8000) {
            racer->unk1E = 0x6000;
        } else {
            racer->unk1E = 0x8000;
        }
        racer->unk28 -= 0.05f;
        if (racer->unk28 < 0.0f) {
            racer->unk28 = 0.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107A38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107BFC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107D04_rockin_raceway);

#ifdef NON_MATCHING
// Only differs in the operand order of the snapshot address additions (base + offset in the target).
// Records the transform of each racer object into row arg0 of the snapshot table, once per racer.
void func_80107E78_rockin_raceway(s32 row, s16 arg1) {
    RockinRacewaySnapshot *snapshots;
    RockinRacewayRacer *racer;
    omObjData *object;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = D_800EC598_minigame[i];
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
        snapshots = D_80111B3C_rockin_raceway[row];
        if (snapshots[racer->unk0A].active != 0) {
            continue;
        }
        snapshots[racer->unk0A].active = 1;
        snapshots[racer->unk0A].unk00 = arg1;
        snapshots[racer->unk0A].trans.x = object->trans.x;
        snapshots[racer->unk0A].trans.y = object->trans.y;
        snapshots[racer->unk0A].trans.z = object->trans.z;
        snapshots[racer->unk0A].rot.x = object->rot.x;
        snapshots[racer->unk0A].rot.y = object->rot.y;
        snapshots[racer->unk0A].rot.z = object->rot.z;
        snapshots[racer->unk0A].scale.x = object->scale.x;
        snapshots[racer->unk0A].scale.y = object->scale.y;
        snapshots[racer->unk0A].scale.z = object->scale.z;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107E78_rockin_raceway);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010803C_rockin_raceway);

s32 func_80108464_rockin_raceway(void) {
    RockinRacewayRacer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        if (racer->unk4C >= D_801112C0_rockin_raceway[racer->unk2E] - 1 &&
            D_800EC598_minigame[i]->trans.x + racer->unk54 >= 1.7f * 200.0) {
            break;
        }
    }
    if (i < 4) {
        for (i = 0; i < 4; i++) {
            racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
            if (racer->unk1C == 0) {
                return i;
            }
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108578_rockin_raceway);

// Claims a free blink-marker entry, initializes it with the duration and base position, positions
// both models there, and returns the entry index, or -1 if the pool is full.
s32 func_80108760_rockin_raceway(Vec *arg0, s32 arg1, u16 arg2) {
    RockinRacewayFx *entry;
    s32 i;

    for (i = 0, entry = D_80111B48_rockin_raceway; i < 8 && entry->active != 0; i++, entry++) {
    }
    if (i >= 8) {
        return -1;
    }
    entry->active = 1;
    entry->duration = arg2;
    entry->flag = 0;
    if (arg0 != NULL) {
        entry->posX = arg0->x;
        entry->posY = arg0->y;
        entry->posZ = arg0->z;
    } else {
        entry->posX = entry->posY = entry->posZ = 0.0f;
    }
    if (arg1 != 0) {
        entry->velX = arg0->x;
        entry->velY = arg0->y;
        entry->velZ = arg0->z;
    } else {
        entry->velX = entry->velY = entry->velZ = 0.0f;
    }
    Hu3DModelPosSet(entry->modelA, entry->posX, entry->posY, entry->posZ);
    Hu3DModelPosSet(entry->modelB, entry->posX, entry->posY, entry->posZ);
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108864_rockin_raceway);

// Collects the first active blink marker within range of pos, returning its flag, or -1 if none.
s32 func_80108A80_rockin_raceway(Vec *pos) {
    RockinRacewayFx *entry;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    for (i = 0, entry = D_80111B48_rockin_raceway; i < 8; i++, entry++) {
        if (entry->active == 0) {
            continue;
        }
        dx = entry->posX - pos->x;
        dy = entry->posY - pos->y;
        dz = entry->posZ - pos->z;
        if (dx * dx + dy * dy + dz * dz < (0.3f * 200.0) * (0.3f * 200.0)) {
            func_8001C258_main(entry->modelA, 4, 4);
            func_8001C258_main(entry->modelB, 4, 4);
            entry->active = 0;
            if (D_80111BD4_rockin_raceway == -1 && D_80111BD6_rockin_raceway == -1 && entry->duration == 30) {
                D_80111BD6_rockin_raceway = 4;
            }
            break;
        }
    }
    if (i < 8) {
        return entry->flag;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108BAC_rockin_raceway);

void func_80108D84_rockin_raceway(void) {
    omObjData *object;
    HmfModel *model;
    s32 i;

    D_80111B4C_rockin_raceway = object = omAddObj(29, 13, 0, -1, func_80108ED4_rockin_raceway);
    object->model[0] = -1;
    for (i = 1; i < 13; i++) {
        object->model[i] = func_8000B108_main(0x1001F, 0x899);
        func_8001C2FC_main(object->model[i], 0x600, 0x400);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
        model = &Hu3DData[object->model[i]];
        model->motTime = 0.0f;
        model->motSpeed = 1.0f;
        func_8001C258_main(object->model[i], 4, 4);
    }
    D_80111B50_rockin_raceway = HuMemAllocTag(12 * sizeof(RockinRacewayModelState), TAG_OVERLAY);
    memset(D_80111B50_rockin_raceway, 0, 12 * sizeof(RockinRacewayModelState));
    D_80111B54_rockin_raceway = 0;
}

// Hides each spark model once its motion has finished playing.
void func_80108ED4_rockin_raceway(omObjData *object) {
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway != 0) {
        return;
    }
    for (i = 1; i < 13; i++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        if (model->attr & 4) {
            continue;
        }
        if (D_800CCF58_main[model->motId].unk02 <= model->motTime) {
            model->attr |= 4;
            model->motTime = 0.0f;
        }
    }
}

// Shows the first hidden spark model at the given position, facing the camera.
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z) {
    omObjData *object = D_80111B4C_rockin_raceway;
    HmfModel *model;
    s32 i;

    for (i = 1; i < 13; i++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        if (!(model->attr & 4)) {
            continue;
        }
        model->pos.x = x;
        model->pos.y = y;
        model->pos.z = z;
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        model->rot.z = CRot.z;
        model->attr &= ~4;
        model->motTime = 0.0f;
        model->motSpeed = 1.5f;
        break;
    }
}

// Saves the state of each spark model and pauses it.
void func_80109044_rockin_raceway(void) {
    omObjData *object = D_80111B4C_rockin_raceway;
    RockinRacewayModelState *state = D_80111B50_rockin_raceway;
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway != 0) {
        return;
    }
    for (i = 1; i < 13; i++, state++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        state->attr = model->attr;
        state->motTime = model->motTime;
        state->motSpeed = model->motSpeed;
        state->pos.x = model->pos.x;
        state->pos.y = model->pos.y;
        state->pos.z = model->pos.z;
        state->rot.x = model->rot.x;
        state->rot.y = model->rot.y;
        state->rot.z = model->rot.z;
        state->scale.x = model->scale.x;
        state->scale.y = model->scale.y;
        state->scale.z = model->scale.z;
        model->attr |= 4;
        model->motTime = model->motSpeed = 0.0f;
    }
    D_80111B54_rockin_raceway = 1;
}

// Restores the state of each spark model saved by func_80109044_rockin_raceway.
void func_80109134_rockin_raceway(void) {
    omObjData *object = D_80111B4C_rockin_raceway;
    RockinRacewayModelState *state = D_80111B50_rockin_raceway;
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway == 0) {
        return;
    }
    for (i = 1; i < 13; i++, state++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        model->attr = state->attr;
        model->motTime = state->motTime;
        model->motSpeed = state->motSpeed;
        model->pos.x = state->pos.x;
        model->pos.y = state->pos.y;
        model->pos.z = state->pos.z;
        model->rot.x = state->rot.x;
        model->rot.y = state->rot.y;
        model->rot.z = state->rot.z;
        model->scale.x = state->scale.x;
        model->scale.y = state->scale.y;
        model->scale.z = state->scale.z;
    }
    D_80111B54_rockin_raceway = 0;
}

void func_80109208_rockin_raceway(void) {
    HuSprite_Unk84_Struct *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    D_80111B68_rockin_raceway[2] = func_8010A4C0_rockin_raceway(11);
    sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    D_80111B58_rockin_raceway = omAddObj(28, 0, 0, -1, func_80109384_rockin_raceway);
    D_80111B5C_rockin_raceway = effect = HuMemAllocTag(sizeof(RockinRacewayEffect) * 16, TAG_OVERLAY);
    for (i = 0; i < 16; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010EC8C_rockin_raceway(sprite, D_801114D4_rockin_raceway);
        } else {
            effect->model =
                func_8010F874_rockin_raceway(sprite, D_80111B5C_rockin_raceway[0].model, D_801114D4_rockin_raceway);
        }
        effect->active = 0;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
    D_80111B60_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewayEffectState), TAG_OVERLAY);
    memset(D_80111B60_rockin_raceway, 0, 16 * sizeof(RockinRacewayEffectState));
    D_80111B64_rockin_raceway = 0;
}

void func_80109384_rockin_raceway(omObjData *object) {
    HuSprite_Unk84_Struct *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        return;
    }
    sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    for (i = 0, effect = D_80111B5C_rockin_raceway; i < 16; i++, effect++) {
        if (effect->active == 0) {
            continue;
        }
        model = &Hu3DData[effect->model];
        if (model->attr & 4) {
            continue;
        }
        effect->pos.x += effect->vel.x;
        effect->pos.y += effect->vel.y;
        effect->pos.z += effect->vel.z;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        func_8010FA78_rockin_raceway(effect->model, sprite, (s32)effect->frame, D_801114D4_rockin_raceway);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->unk10) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_801094EC_rockin_raceway(Vec *pos, Vec *vel, Vec *scale, f32 speed) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_80111B5C_rockin_raceway; i < 16; i++, effect++) {
        if (effect->active != 0) {
            continue;
        }
        effect->active = 1;
        model = &Hu3DData[effect->model];
        if (pos != NULL) {
            effect->pos.x = pos->x;
            effect->pos.y = pos->y;
            effect->pos.z = pos->z;
        } else {
            effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        }
        if (vel != NULL) {
            effect->vel.x = vel->x;
            effect->vel.y = vel->y;
            effect->vel.z = vel->z;
        } else {
            effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        }
        if (scale != NULL) {
            effect->scale.x = scale->x;
            effect->scale.y = scale->y;
            effect->scale.z = scale->z;
        } else {
            effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
        }
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8010FA78_rockin_raceway(effect->model, sprite, 0, D_801114D4_rockin_raceway);
        func_8001C258_main(effect->model, 4, 0);
        model->motTime = 0.0f;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        return i;
    }
    return -1;
}

// Spawns a small effect above the racer, drifting backward from its heading.
void func_801096A0_rockin_raceway(RockinRacewayRacer *racer) {
    Vec pos;
    Vec vel;
    Vec scale;

    pos.x = racer->pos.x;
    pos.z = racer->pos.z;
    pos.y = racer->pos.y + 0.1f * 200.0;
    vel.x = -(sindf(racer->unk68 + racer->unk40) * 100.0 * 0.1f);
    vel.z = -(cosdf(racer->unk68 + racer->unk40) * 100.0 * 0.1f);
    vel.y = 1.0f;
    scale.x = scale.y = scale.z = 0.25f;
    func_801094EC_rockin_raceway(&pos, &vel, &scale, 1.0f);
}

// Saves the state of each sprite effect and hides it.
void func_801097A0_rockin_raceway(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        return;
    }
    for (state = D_80111B60_rockin_raceway, effect = D_80111B5C_rockin_raceway, i = 0; i < 16;
         i++, effect++, state++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        state->active = effect->active;
        state->motTime = model->motTime;
        state->attr = model->attr;
        state->frame = effect->frame;
        state->speed = effect->speed;
        state->pos.x = model->pos.x;
        state->pos.y = model->pos.y;
        state->pos.z = model->pos.z;
        state->rot.x = model->rot.x;
        state->rot.y = model->rot.y;
        state->rot.z = model->rot.z;
        state->scale.x = model->scale.x;
        state->scale.y = model->scale.y;
        state->scale.z = model->scale.z;
        effect->active = 0;
        model->attr |= 4;
        model->motTime = 0.0f;
    }
    D_80111B64_rockin_raceway = 1;
}

// Restores the state of each sprite effect saved by func_801097A0_rockin_raceway.
void func_801098D8_rockin_raceway(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        return;
    }
    for (state = D_80111B60_rockin_raceway, effect = D_80111B5C_rockin_raceway, i = 0; i < 16;
         i++, effect++, state++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        effect->active = state->active;
        model->attr = state->attr;
        effect->frame = state->frame;
        effect->speed = state->speed;
        model->pos.x = state->pos.x;
        model->pos.y = state->pos.y;
        model->pos.z = state->pos.z;
        model->rot.x = state->rot.x;
        model->rot.y = state->rot.y;
        model->rot.z = state->rot.z;
        model->scale.x = state->scale.x;
        model->scale.y = state->scale.y;
        model->scale.z = state->scale.z;
    }
    D_80111B64_rockin_raceway = 0;
}

// Appends a new object to the shared minigame object list.
void func_801099AC_rockin_raceway(void) {
    omObjData *obj = omAddObj(1, 0x18, 0, -1, func_80109A04_rockin_raceway);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109A04_rockin_raceway);

void func_80109CF8_rockin_raceway(void) {
}

void func_80109D00_rockin_raceway(s32 *players) {
    omObjData *object = D_800EC1C0_minigame[0];

    func_80110C38_rockin_raceway(&object->model[3], func_80055194_main(D_80111B68_rockin_raceway[3]), players);
}

void func_80109D54_rockin_raceway(s32 *values) {
    omObjData *object = D_800EC1C0_minigame[0];

    func_80110D90_rockin_raceway(&object->model[7], func_80055194_main(D_80111B68_rockin_raceway[4]), values);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109DA8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);

u16 func_8010A48C_rockin_raceway(u16 arg0, u16 arg1) {
    Track *track = &D_80111B40_rockin_raceway[arg0];
    return track->unk20[arg1];
}

u16 func_8010A4C0_rockin_raceway(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 anim = HuSprAnimRead(data);

    DataClose(data);
    return anim;
}

void func_8010A504_rockin_raceway(void) {
    s32 group;

    D_80111B68_rockin_raceway[1] = func_8010A4C0_rockin_raceway(0x4D000F);
    D_80111B68_rockin_raceway[5] = func_8010A4C0_rockin_raceway(0x4D0012);
    D_80111B68_rockin_raceway[8] = func_8010A4C0_rockin_raceway(0x4D0013);
    group = HuSprGrpCreate(1, 0);
    D_80111B74_rockin_raceway = group;
    HuSprPosSet(group, 0, 160, 60);
    HuSprGrpMemberSet(group, 0, D_80111B68_rockin_raceway[5], 0);
    func_800550F4_main(group, 0, 0);
    func_80054FF8_main(group, 0, 0);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF | 0x1000);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A5E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A990_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010AAAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B124_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B2B8_rockin_raceway);

// Converts the two frame counts into minute, second and hundredth digits in D_80111B00_rockin_raceway.
void func_8010B5DC_rockin_raceway(s32 *frames) {
    s32 time[3];
    s32(*digits)[6] = D_80111B00_rockin_raceway;
    s32 i;

    for (i = 0; i < 2; i++) {
        time[0] = frames[i] / 1800;
        frames[i] -= time[0] * 1800;
        time[1] = frames[i] / 30;
        frames[i] -= time[1] * 30;
        time[2] = frames[i] / 30.0f * 99.0f;
        digits[i][0] = time[0] / 10;
        digits[i][1] = time[0] - digits[i][0] * 10;
        digits[i][2] = time[1] / 10;
        digits[i][3] = time[1] - digits[i][2] * 10;
        digits[i][4] = time[2] / 10;
        digits[i][5] = time[2] - digits[i][4] * 10;
    }
}

void func_8010B774_rockin_raceway(void) {
    HuCamera *camera;
    s32 i;

    Center.x = D_80111350_rockin_raceway.center.x;
    Center.y = D_80111350_rockin_raceway.center.y;
    Center.z = D_80111350_rockin_raceway.center.z;
    CRot.x = D_80111350_rockin_raceway.rot.x;
    CRot.y = D_80111350_rockin_raceway.rot.y;
    CRot.z = D_80111350_rockin_raceway.rot.z;
    CZoom = D_80111350_rockin_raceway.zoom;
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2E_rockin_raceway = 0;
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010C0D8_rockin_raceway);
    camera = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111838_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B89C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C0D8_rockin_raceway);

void func_8010C5E0_rockin_raceway(s32 arg0) {
    if (CRot.x >= 360.0) {
        CRot.x -= 360.0;
    } else if (CRot.x < 0.0) {
        CRot.x += 360.0;
    }
    if (CRot.y >= 360.0) {
        CRot.y -= 360.0;
    } else if (CRot.y < 0.0) {
        CRot.y += 360.0;
    }
    if (CRot.z >= 360.0) {
        CRot.z -= 360.0;
    } else if (CRot.z < 0.0) {
        CRot.z += 360.0;
    }
    D_80111BE0_rockin_raceway[arg0].center.x = Center.x;
    D_80111BE0_rockin_raceway[arg0].center.y = Center.y;
    D_80111BE0_rockin_raceway[arg0].center.z = Center.z;
    D_80111BE0_rockin_raceway[arg0].rot.x = CRot.x;
    D_80111BE0_rockin_raceway[arg0].rot.y = CRot.y;
    D_80111BE0_rockin_raceway[arg0].rot.z = CRot.z;
    D_80111BE0_rockin_raceway[arg0].zoom = CZoom;
    D_80111BE0_rockin_raceway[arg0].unk_1C = D_80111BE0_rockin_raceway[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010C7CC_rockin_raceway(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80111C28_rockin_raceway = frames - 1;
        D_80111C2A_rockin_raceway = frames;
        if (x != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.x = x;
        } else {
            D_80111BE0_rockin_raceway[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.y = y;
        } else {
            D_80111BE0_rockin_raceway[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.z = z;
        } else {
            D_80111BE0_rockin_raceway[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.x = rotX;
        } else {
            D_80111BE0_rockin_raceway[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.y = rotY;
        } else {
            D_80111BE0_rockin_raceway[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.z = rotZ;
        } else {
            D_80111BE0_rockin_raceway[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].zoom = zoom;
        } else {
            D_80111BE0_rockin_raceway[0].zoom = CZoom;
        }
        func_8010C5E0_rockin_raceway(1);
    }
}

void func_8010C9BC_rockin_raceway(void) {
    D_80111BD8_rockin_raceway->func = NULL;
}

void func_8010C9CC_rockin_raceway(void) {
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway->func = func_8010C0D8_rockin_raceway;
}

void func_8010CA1C_rockin_raceway(void) {
    HuCamera *camera;
    s32 i;

    D_80111C34_rockin_raceway = 0;
    D_80111C4C_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewayVec), TAG_OVERLAY);
    D_80111C30_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010CE90_rockin_raceway);
    camera = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

void func_8010CADC_rockin_raceway(Vec *arg0, f32 arg1) {
    if (D_80111C30_rockin_raceway != NULL && D_80111C34_rockin_raceway < 16) {
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].x = arg0->x;
        do {
        } while (0); // splits the basic block so the entry address is recomputed
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].y = arg0->y;
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].z = arg0->z;
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].unk0C = arg1;
        D_80111C34_rockin_raceway++;
    }
}

void func_8010CB5C_rockin_raceway(RockinRacewayRacer *racer, f32 arg1) {
    Vec pos;

    pos.x = racer->pos.x + 100.0;
    pos.y = racer->pos.y + 100.0;
    pos.z = racer->pos.z;
    func_8010CADC_rockin_raceway(&pos, arg1);
    pos.x = racer->pos.x - 100.0;
    pos.y = racer->pos.y - 100.0;
    pos.z = racer->pos.z;
    func_8010CADC_rockin_raceway(&pos, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CC10_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CE90_rockin_raceway);

void func_8010D104_rockin_raceway(void) {
    D_80111C30_rockin_raceway->func = NULL;
}

void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}

void func_8010D134_rockin_raceway(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    camera->pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    camera->pos.y = -sindf(rotX) * CZoom + Center.y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    camera->at.x = Center.x;
    camera->at.y = Center.y;
    camera->at.z = Center.z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D288_rockin_raceway);

void func_8010D5B8_rockin_raceway(void) {
    u8 *pool = HuMemAllocTag(30 * 0x644, TAG_OVERLAY);

    D_80111C50_rockin_raceway = pool;
    memset(pool, 0, 30 * 0x644);
    D_80111C54_rockin_raceway = 0;
    D_80111C58_rockin_raceway = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D600_rockin_raceway);

u8 *func_8010D944_rockin_raceway(s32 arg0) {
    s32 index = arg0;

    if (arg0 >= D_80111C54_rockin_raceway || arg0 >= 30) {
        return NULL;
    }
    if (D_80111C54_rockin_raceway >= 30) {
        index += D_80111C58_rockin_raceway;
    }
    if (index >= 30) {
        index -= 30;
    }
    return D_80111C50_rockin_raceway + index * 0x644;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D9C4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E08C_rockin_raceway);

void func_8010E2E4_rockin_raceway(void) {
    RockinRacewaySfx *sfx;
    s32 i;

    D_80111BD0_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewaySfx), TAG_OVERLAY);
    sfx = D_80111BD0_rockin_raceway;
    memset(sfx, 0, 16 * sizeof(RockinRacewaySfx));
    for (i = 0; i < 16; i++, sfx++) {
        sfx->soundId = -1;
    }
}

// Finds a free entry in the sfx pool, fills it in, and returns its index, or -1 if the pool is full.
s32 func_8010E344_rockin_raceway(s16 soundId, s16 frames, s16 unk04, s16 playerIndex) {
    RockinRacewaySfx *sfx = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16 && sfx->soundId != -1; i++, sfx++) {
    }
    if (i >= 16) {
        return -1;
    }
    sfx->soundId = soundId;
    sfx->frames = frames;
    sfx->unk04 = unk04;
    sfx->playerIndex = playerIndex;
    return i;
}

// Plays each queued sound once its delay has elapsed, then frees the entry.
void func_8010E39C_rockin_raceway(void) {
    RockinRacewaySfx *sfx = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16; i++, sfx++) {
        if (sfx->soundId == -1) {
            continue;
        }
        if (sfx->frames <= 0) {
            switch (sfx->unk04) {
                case 0:
                    HuAudFXPlay(sfx->soundId);
                    break;
                case 1:
                    func_8004AC98_main(sfx->soundId, sfx->playerIndex);
                    break;
                case 2:
                    CharFXPlay(sfx->soundId, GwPlayer[(s16)(sfx->playerIndex % 4)].chr);
                    break;
                default:
                    func_8004AC98_main(GwPlayer[(s16)(sfx->playerIndex % 4)].chr + sfx->soundId + 1, sfx->playerIndex);
                    break;
            }
            sfx->soundId = -1;
        }
        sfx->frames--;
    }
}

f32 func_8010E504_rockin_raceway(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

// Steps the angle current toward target by at most step degrees along the shorter direction.
f32 func_8010E608_rockin_raceway(f32 target, f32 current, f32 step) {
    f32 diff;
    f32 delta;

    if (target >= 360.0) {
        target -= 360.0;
    } else if (target < 0.0) {
        target += 360.0;
    }
    if (current >= 360.0) {
        current -= 360.0;
    } else if (current < 0.0) {
        current += 360.0;
    }
    diff = fmod(target - current + 360.0, 360.0);
    if (diff < 180.0) {
        if (diff <= step) {
            delta = diff;
        } else {
            delta = step;
        }
    } else if (360.0 - diff <= step) {
        delta = -(360.0 - diff);
    } else {
        delta = -step;
    }
    delta += current;
    if (delta >= 360.0) {
        delta -= 360.0;
    } else if (delta < 0.0) {
        delta += 360.0;
    }
    return delta;
}

// Linearly interpolates from arg1 to arg2 by arg0.
f32 func_8010E7C8_rockin_raceway(f32 arg0, f32 arg1, f32 arg2) {
    return arg1 + arg0 * (arg2 - arg1);
}

f32 func_8010E7E0_rockin_raceway(f32 arg0, f32 arg1, f32 arg2) {
    return func_8010E608_rockin_raceway(arg2, arg1, fabsf(func_8010E504_rockin_raceway(arg2, arg1) * arg0));
}

// Evaluates a quadratic bezier curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E840_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 inv = 1.0 - arg0;

    return inv * inv * arg1 + (inv * arg0 * arg2) * 2.0 + arg0 * arg0 * arg3;
}

// Evaluates the quadratic bezier curve per component for 3-component vectors.
void func_8010E8A0_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *out++ = func_8010E840_rockin_raceway(arg0, *arg1++, *arg2++, *arg3++);
    }
}

// Evaluates a curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E93C_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return ((arg0 - 1.0) * arg1 + (1.0 - 2.0 * arg0) * arg2 + arg0 * arg3) * 2.0;
}

// Computes the normalized tangent of the curve per component for 3-component vectors.
void func_8010E994_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    f32 tangent[3];
    f32 length;
    s32 i;

    for (i = 0; i < 3; i++) {
        tangent[i] = func_8010E93C_rockin_raceway(arg0, *arg1++, *arg2++, *arg3++);
    }
    length = sqrtf(tangent[0] * tangent[0] + tangent[1] * tangent[1] + tangent[2] * tangent[2]);
    if (length != 0.0f) {
        length = 1.0 / length;
        for (i = 0; i < 3; i++) {
            *out++ = length * tangent[i];
        }
    } else {
        *out++ = 0.0f;
        *out++ = 0.0f;
        *out = 1.0f;
    }
}

// Returns the angle of (arg0, arg1) in degrees, normalized to [0, 360).
f32 func_8010EB04_rockin_raceway(f32 arg0, f32 arg1) {
    f32 angle = atan2df(arg1, arg0);

    if (angle < 0.0) {
        angle += 360.0;
    } else if (angle >= 360.0) {
        angle -= 360.0;
    }
    return angle;
}

// Converts a direction vector into pitch and yaw angles, with zero roll.
void func_8010EB84_rockin_raceway(Vec *dir, f32 *rot) {
    *rot++ = func_8010EB04_rockin_raceway(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_8010EB04_rockin_raceway(dir->z, dir->x);
    *rot = 0.0f;
}

void func_8010EC0C_rockin_raceway(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_8010EC38_rockin_raceway(omObjData *object) {
    RockinRacewayWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct *sprite, u8 *color) {
    u8 *buffer;
    Gfx *gfx;
    Gfx *header;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    header = gfx;
    buffer = (u8 *)gfx;
    model = func_8001A894_main(0x18C1, buffer, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x71010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_8010FBAC_rockin_raceway(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_801116F0_rockin_raceway));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk10 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk10, size);
    HuMemFree(buffer);
    gfx = HuMemAlloc(0x10000);
    {
        Gfx *textureHeader = gfx;
        buffer = (u8 *)gfx;
        gfx++;
        gSPTexture(textureHeader, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->unk18;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk14 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk14, size);
    HuMemFree(buffer);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color) {
    HmfModel *srcModel = Hu3DData + model;
    HmfData *srcData = srcModel->hmf;
    HmfData *data;
    Gfx *gfx;
    s32 newModel;
    s32 i;

    newModel = func_8001A894_main(srcModel->attr, NULL, 4);
    data = Hu3DData[newModel].hmf;
    data->unk60->unk50 = srcData->unk60->unk50;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    data->unk3C->unk10 = srcData->unk3C->unk10;
    data->unk3C->unk14 = srcData->unk3C->unk14;
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return newModel;
}

void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
    s32 capacity = 0x1000;
    s32 width, height, scaledWidth, scaledHeight;
    s32 size, slices, textureHeight, sliceHeight, vertexCount;
    s32 i, j;
    Vtx_t *vertices, *start;

    if (sprite->unk1A >= 2) {
        capacity = 0x800;
    }
    width = sprite->unk00->unk04;
    height = sprite->unk00->unk06;
    scaledWidth = width * 100.0 * scale / 32.0;
    scaledHeight = height * 100.0 * scale / 32.0;
    if ((sprite->unk18 & 0xFFF) == 4) {
        size = ((width + 1) & 0xFFFE) * height * 4;
    } else {
        size = width * height * sprite->unk18;
    }
    size /= 8;
    slices = size / capacity;
    if (slices <= 0) {
        slices = 1;
    }
    textureHeight = height / slices;
    sliceHeight = scaledHeight / slices;
    vertexCount = slices * 4;
    size = slices * 4 * sizeof(Vtx_t);
    start = vertices = HuMemAllocTag(size, data->unk0E);
    memset(start, 0, size);
    for (i = 0; i < slices; i++, vertices += 4) {
        vertices[0].ob[0] = scaledWidth * 0.5;
        vertices[0].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[0].tc[0] = (width - 1) << 6;
        vertices[0].tc[1] = 0;
        vertices[1].ob[0] = scaledWidth * 0.5;
        vertices[1].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[1].tc[0] = (width - 1) << 6;
        vertices[1].tc[1] = (textureHeight - 1) << 6;
        vertices[2].ob[0] = -(scaledWidth * 0.5);
        vertices[2].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[2].tc[0] = 0;
        vertices[2].tc[1] = 0;
        vertices[3].ob[0] = -(scaledWidth * 0.5);
        vertices[3].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[3].tc[0] = 0;
        vertices[3].tc[1] = (textureHeight - 1) << 6;
        for (j = 0; j < 4; j++) {
            vertices[j].ob[0] += xOffset;
            vertices[j].ob[1] += yOffset;
            vertices[j].ob[2] = 0;
            vertices[j].flag = 0;
            vertices[j].cn[3] = 255;
            vertices[j].cn[0] = vertices[j].cn[1] = vertices[j].cn[2] = 0;
        }
    }
    vertices = start;
    for (i = 0; i < D_800D1FF0_main; i++) {
        Vtx_t *destination;
        Vtx_t *source;
        data->unk44[i] = HuMemAllocTag(vertexCount * sizeof(Vtx_t), data->unk0E);
        destination = (Vtx_t *)data->unk44[i];
        source = vertices;
        for (j = 0; j < vertexCount; j++) {
            *destination++ = *source++;
        }
    }
    HuMemFree(start);
    return slices;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FFB8_rockin_raceway);

// Shows a character face sprite above each of the 4 slots, or a blank one for a negative player.
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *players) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (players[i] < 0) {
            func_8010FA78_rockin_raceway(models[i], sprite, 8, D_80111730_rockin_raceway);
        } else {
            if (players[i] >= 4) {
                players[i] = 0;
            }
            func_8010FA78_rockin_raceway(models[i], sprite, GwPlayer[players[i]].chr, D_80111730_rockin_raceway);
        }
        Hu3DModelPosSet(models[i], D_80111414_rockin_raceway[i].x, D_80111414_rockin_raceway[i].y + 0.2f * 200.0,
                        D_80111414_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}

// Shows a digit sprite for each of the 12 digits in D_80111B00_rockin_raceway, clamped to 0-9.
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *values) {
    s32 *digits = D_80111B00_rockin_raceway[0];
    s32 i;

    for (i = 0; i < 12; i++) {
        if (digits[i] >= 9) {
            digits[i] = 9;
        } else if (digits[i] < 0) {
            digits[i] = 0;
        }
        func_8010FA78_rockin_raceway(models[i], sprite, digits[i], D_80111734_rockin_raceway);
        Hu3DModelPosSet(models[i], D_80111444_rockin_raceway[i].x, D_80111444_rockin_raceway[i].y + 0.2f * 200.0,
                        D_80111444_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}
