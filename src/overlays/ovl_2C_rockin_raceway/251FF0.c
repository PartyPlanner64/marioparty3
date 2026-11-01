#include "common.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"

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

extern Track *D_80111B40_rockin_raceway;
extern RockinRacewayFx *D_80111B48_rockin_raceway;
extern RockinRacewaySfx *D_80111BD0_rockin_raceway;
extern omObjData *D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway;
extern RockinRacewayVec *D_80111C4C_rockin_raceway;
// D_80111C50_rockin_raceway is a pool of 30 opaque 0x644-byte records,
// indexed by D_80111C58_rockin_raceway and filled out by D_80111C54_rockin_raceway.
extern u8 *D_80111C50_rockin_raceway;
extern s32 D_80111C54_rockin_raceway;
extern s32 D_80111C58_rockin_raceway;

void func_80109A04_rockin_raceway(omObjData *object);
void func_8010CE90_rockin_raceway(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801059A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105C24_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111740_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_8011174C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105CB0_rockin_raceway);

void func_80106A5C_rockin_raceway(void) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106A80_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106B28_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80106DC8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801071D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010769C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107958_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107A38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107BFC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107D04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80107E78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010803C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108464_rockin_raceway);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108A80_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108BAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108D84_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108ED4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80108F8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109044_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109134_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109208_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109384_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801094EC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801096A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801097A0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_801098D8_rockin_raceway);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109D00_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109D54_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80109DA8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);

u16 func_8010A48C_rockin_raceway(u16 arg0, u16 arg1) {
    Track *track = &D_80111B40_rockin_raceway[arg0];
    return track->unk20[arg1];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A4C0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A504_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A5E4_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A990_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010AAAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B124_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B2B8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B5DC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B774_rockin_raceway);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", D_80111838_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B89C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C0D8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C5E0_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C7CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9BC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010C9CC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CA1C_rockin_raceway);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CB5C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CC10_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010CE90_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D104_rockin_raceway);

void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D134_rockin_raceway);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E39C_rockin_raceway);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E608_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7C8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E7E0_rockin_raceway);

// Evaluates a quadratic bezier curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E840_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 inv = 1.0 - arg0;

    return inv * inv * arg1 + (inv * arg0 * arg2) * 2.0 + arg0 * arg0 * arg3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E8A0_rockin_raceway);

// Evaluates a curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E93C_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return ((arg0 - 1.0) * arg1 + (1.0 - 2.0 * arg0) * arg2 + arg0 * arg3) * 2.0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010E994_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB04_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EB84_rockin_raceway);

void func_8010EC0C_rockin_raceway(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_8010EC38_rockin_raceway(omObjData *object, s32 arg1, u32 arg2) {
    RockinRacewayWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010EC8C_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010F874_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FA78_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FBAC_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010FFB8_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110C38_rockin_raceway);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80110D90_rockin_raceway);
