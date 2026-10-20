#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "mallocblock.h"

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 motionId;
    /* 0x04 */ s32 posX;
    /* 0x08 */ s32 posY;
    /* 0x0C */ s32 posZ;
    /* 0x10 */ f32 scaleX;
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ f32 scaleZ;
    /* 0x1C */ f32 rotX;
    /* 0x20 */ f32 rotY;
    /* 0x24 */ f32 rotZ;
    /* 0x28 */ s32 unk_28;
} OpModel;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ RGBA color;
    /* 0x10 */ s16 effectId;
    /* 0x12 */ char unk_12[0x2A];
} OpObj; // sizeof 0x3C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OpSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec at;
    /* 0x18 */ Vec up;
    /* 0x24 */ omObjData *obj;
} OpCamVecs; // sizeof 0x28

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ f32 magnitude;
    /* 0x08 */ s32 frame;
    /* 0x0C */ s32 totalFrames;
    /* 0x10 */ s32 active;
} OpShake; // sizeof 0x14

typedef struct {
    /* 0x00 */ s16 animId;
    /* 0x02 */ u16 espriteSlot;
} OpContError; // sizeof 0x4

typedef struct {
    /* 0x00 */ s16 animId;
} OpAnimSlot; // sizeof 0x2

// View of an OpObj slot from offset 0x0C, as used by the demo model objects.
// The word at 0x0C doubles as OpObj's color for the wipe effects.
typedef struct {
    /* 0x00 */ s32 modelId;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec unk_1C;
    /* 0x1C */ char unk_38[0x20];
} OpWork; // sizeof 0x3C

typedef union {
    Vec pos;
    s32 motion[3];
} OpObjPos;

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x04 */ void *event;
    /* 0x08 */ s32 unk_08;
} OpSlot; // sizeof 0xC

void opDemoEndReset(void);
void func_80107140_opening(s32 slot, u32 event, s32 x, s32 y, s16 arg4, s16 arg5, s16 arg6);
void opObjectInit(void);
void opTitleCreate(void);
void opDemoCreate(void);
void func_80110B9C_opening(void);
void opDemoModelKill(void);
void opDemoSprKill(void);
void func_80107A90_opening(s32 index);
void func_80112A74_opening(omObjData *obj);
void opDemoStarWaitMain(omObjData *obj);
void opTitleMain(void);
void opDemoMain(void);
void opTitleSprMain(void);
void opDemoEvent(void);
void func_801061F0_opening(void);
void func_8010621C_opening(void);
void func_801067D4_opening(void);
void func_80107A4C_opening(void);
void opSprPosSet(s32 slot, s32 x, s32 y);
void opModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void opMotionSet(s32 modelId, s32 motionId, s16 arg2);
void func_80110B90_opening(void);
void func_80110C04_opening(omObjData *);
void func_80110F48_opening(void);
void func_80111028_opening(void);
void func_80111090_opening(omObjData *);
void func_80112944_opening(void);
void opContErrorCreate(void);
void MBCameraOffsetSet(s16 arg0, s16 arg1);
void func_8000BBFC_main(u16 arg0, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 arg0, f32 arg1, f32 arg2);
void func_8000BBD4_main(u16 arg0, s16 arg1, s16 arg2);
void func_8000BD94_main(u16 arg0, s32 arg1, s32 arg2);
void func_80113E8C_opening(omObjData *);
void opDemoObjKill(s32 index);
void opDemoObjKillAll(void);
void opContErrorKill(void);
void opWipeKill(s32 index);

extern u8 D_800D20B8_main[16][3];
extern u8 D_800D5570_main[16][3];
extern Gfx D_80114BE8_opening[];
extern u32 D_80114BE0_opening;
extern Vec D_80114BB8_opening;
extern Vec D_80114BC4_opening;
extern RectF D_80114BD0_opening;
extern Process *D_80114EA0_opening;
extern s32 D_80114EA4_opening;
extern OpModel D_80115630_opening[0xA0];
extern OpCamVecs D_80117350_opening;
extern OpShake D_80117338_opening;
extern OpObj D_80117388_opening[0x10];
extern s16 D_801171B0_opening;
extern u16 D_801171B2_opening;
extern OpSlot D_801171B8_opening[0x20];
extern OpSpr D_80114EB0_opening[0x40];
extern OpAnimSlot D_801155B0_opening[0x40];
extern OpContError D_80117750_opening;
extern s32 D_8011738C_opening[0x10][15];
extern s32 D_80117390_opening[0x10][15];
extern OpWork D_80117394_opening[0x10];
extern OpObjPos D_80117398_opening[0x10][5];
extern s32 D_8011739C_opening[0x10][15];
extern f32 D_801173A4_opening[0x10][15];
extern s32 D_801173A8_opening[0x10][15];
extern s32 D_801173B0_opening[0x10][15];
extern s32 D_801173B4_opening[0x10][15];
extern s32 D_801173B8_opening[0x10][15];

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opObjectInit);

void opTitleObjectSetup(void) {
    opObjectInit();
    opTitleCreate();
}

void func_80105C2C_opening(void) {
    opObjectInit();
    opDemoCreate();
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjectSetup);

void opEventInit(void) {
    opDemoEndReset();
}

void opTitleCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opTitleMain, 0x5000, 0x800, 0);
}

void opDemoCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opDemoMain, 0x5000, 0x800, 0);
}

Process *opDemoEventCreate(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *eventPrc = omAddPrcObj(opDemoEvent, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, eventPrc);
    return eventPrc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoMain);

Process *func_80105F68_opening(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *sprPrc = omAddPrcObj(opTitleSprMain, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, sprPrc);
    return sprPrc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleMain);

s32 opBtnStartCheck(void) {
    if (GWContErrorGet() == 1) {
        return (D_800D5558_main[0] & 0x1000) != 0;
    }
    return 0;
}

void opDemoEndReset(void) {
    D_80114EA4_opening = 0;
}

void opDemoEndSet(s32 value) {
    D_80114EA4_opening = value;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEndGet);

void func_801061F0_opening(void) {
    func_8010621C_opening();
    func_801067D4_opening();
    func_80107A4C_opening();
}

void func_8010621C_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114EB0_opening); i++) {
        D_801155B0_opening[i].animId = -1;
        D_80114EB0_opening[i].espriteSlot = -1;
        D_80114EB0_opening[i].unk_04 = D_80114EB0_opening[i].unk_08 = 0;
        D_80114EB0_opening[i].unk_0C = D_80114EB0_opening[i].unk_10 = 0.0f;
        D_80114EB0_opening[i].unk_14 = D_80114EB0_opening[i].unk_0C;
        D_80114EB0_opening[i].unk_18 = 0xFF;
    }
}

s16 opAnimIdGet(s32 slot) {
    return D_801155B0_opening[slot].animId;
}

s16 opEspIdGet(s32 slot) {
    return D_80114EB0_opening[slot].espriteSlot;
}

void opAnimCreate(s32 arg0, s32 arg1) {
    D_801155B0_opening[arg0].animId = func_8000B838_main(arg1);
}

void opAnimKill(s32 arg0) {
    if (D_801155B0_opening[arg0].animId != -1) {
        HuSprKill(D_801155B0_opening[arg0].animId);
    }
    D_801155B0_opening[arg0].animId = -1;
}

void opEspCreate(s32 slot, s16 animId) {
    D_80114EB0_opening[slot].espriteSlot = InitEspriteSlot(D_801155B0_opening[animId].animId, 0, 0);
    opSprPosSet(slot, 0xA0, 0x78);
}

void opEspKill(s32 slot) {
    if (D_80114EB0_opening[slot].espriteSlot != -1) {
        func_8000C184_main(D_80114EB0_opening[slot].espriteSlot);
    }
    D_80114EB0_opening[slot].espriteSlot = -1;
}

void opSprCreate(s32 slot, s32 resourceId) {
    opAnimCreate(slot, resourceId);
    opEspCreate(slot, slot);
}

void opSprBGCreate(s32 slot, s32 resourceId) {
    opSprCreate(slot, resourceId);
    func_8000BC48_main(D_80114EB0_opening[slot].espriteSlot, 0x4000);
}

void opSprKill(s32 slot) {
    opEspKill(slot);
    opAnimKill(slot);
}

void opSprKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114EB0_opening); i++) {
        opSprKill(i);
    }
}

void opSprDispOn(s32 slot) {
    func_8000BB54_main(D_80114EB0_opening[slot].espriteSlot);
}

void opSprDispOff(s32 slot) {
    func_8000BB94_main(D_80114EB0_opening[slot].espriteSlot);
}

void opSprBGDispOn(s32 slot) {
    opSprDispOn(slot);
}

void opSprBGDispOff(s32 slot) {
    opSprDispOff(slot);
}

void opSprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    D_80114EB0_opening[arg0].unk_04 = arg1;
    D_80114EB0_opening[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_80114EB0_opening[arg0].espriteSlot, arg1, arg2);
}

void opSprPosGet(s32 slot, s32 *x, s32 *y) {
    *x = D_80114EB0_opening[slot].unk_04;
    *y = D_80114EB0_opening[slot].unk_08;
}

void opSprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    D_80114EB0_opening[arg0].unk_0C = arg1;
    D_80114EB0_opening[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_80114EB0_opening[arg0].espriteSlot, arg1, arg2);
}

void opSprAlphaSet(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void opSprAttrSet(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void opSprAttrReset(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void func_80106734_opening(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void func_80106768_opening(s32 slot, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80114EB0_opening[slot].espriteSlot, 1);
    func_8000BD94_main(D_80114EB0_opening[slot].espriteSlot, arg1, arg2);
}

void func_801067D4_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115630_opening); i++) {
        D_80115630_opening[i].modelId = -1;
        D_80115630_opening[i].motionId = -1;
    }
}

void opModelCreate(s32 slot, s32 resourceId, s32 arg2) {
    s16 modelId;

    modelId = func_8000B108_main(resourceId, arg2);
    D_80115630_opening[slot].modelId = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void opMotionCreate(s32 slot, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    D_80115630_opening[slot].motionId = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void opModelKill(s32 slot) {
    if (D_80115630_opening[slot].modelId != -1) {
        func_8001ACDC_main(D_80115630_opening[slot].modelId);
        D_80115630_opening[slot].modelId = -1;
    }
    if (D_80115630_opening[slot].motionId != -1) {
        func_8002D4B8_main(D_80115630_opening[slot].motionId);
        D_80115630_opening[slot].motionId = -1;
    }
}

void opModelKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115630_opening); i++) {
        opModelKill(i);
    }
}

s16 opModelIdGet(s32 modelId) {
    return D_80115630_opening[modelId].modelId;
}

s16 opMotionIdGet(s32 motionId) {
    return D_80115630_opening[motionId].motionId;
}

void opModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].rotX = arg1;
    D_80115630_opening[arg0].rotY = arg2;
    D_80115630_opening[arg0].rotZ = arg3;
    Hu3DModelRotSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].posX = arg1;
    D_80115630_opening[arg0].posY = arg2;
    D_80115630_opening[arg0].posZ = arg3;
    Hu3DModelPosSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].scaleX = arg1;
    D_80115630_opening[arg0].scaleY = arg2;
    D_80115630_opening[arg0].scaleZ = arg3;
    Hu3DModelScaleSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelPosGet(s32 modelId, f32 *posX, f32 *posY, f32 *posZ) {
    *posX = D_80115630_opening[modelId].posX;
    *posY = D_80115630_opening[modelId].posY;
    *posZ = D_80115630_opening[modelId].posZ;
}

void opModelRotGet(s32 modelId, f32 *rotX, f32 *rotY, f32 *rotZ) {
    *rotX = D_80115630_opening[modelId].rotX;
    *rotY = D_80115630_opening[modelId].rotY;
    *rotZ = D_80115630_opening[modelId].rotZ;
}

void opModelScaleGet(s32 modelId, f32 *scaleX, f32 *scaleY, f32 *scaleZ) {
    *scaleX = D_80115630_opening[modelId].scaleX;
    *scaleY = D_80115630_opening[modelId].scaleY;
    *scaleZ = D_80115630_opening[modelId].scaleZ;
}

void opModelDispOff(s32 arg0) {
    func_8001C258_main(D_80115630_opening[arg0].modelId, 4, 4);
}

void opModelDispOn(s32 arg0) {
    func_8001C258_main(D_80115630_opening[arg0].modelId, 4, 0);
}

void opMotionFlagSet(s32 modelId, s16 arg1) {
    func_8001C814_main(D_80115630_opening[modelId].modelId, -1, arg1);
}

void opMotionShiftSet(s32 modelId, s32 motionId, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80115630_opening[modelId].modelId, D_80115630_opening[motionId].motionId, arg2, arg3, arg4);
}

void func_80106DD0_opening(s32 modelId, s16 arg1) {
    func_8001C814_main(D_80115630_opening[modelId].modelId, arg1, 0);
}

void opMotionSpeedSet(s32 modelId, f32 speed) {
    func_8001C92C_main(D_80115630_opening[modelId].modelId, speed);
}

void opMotionTimeSet(s32 slot, u32 time) {
    func_8001C6A8_main(D_80115630_opening[slot].modelId, time);
}

void opMotionEndWait(s32 slot) {
    while (HmfModelData[D_80115630_opening[slot].modelId].unk40 !=
           D_800CCF58_main[HmfModelData[D_80115630_opening[slot].modelId].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 opMotionEndCheck(s32 arg0) {
    s16 modelId = D_80115630_opening[arg0].modelId;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void opMotionSet(s32 modelId, s32 motionId, s16 arg2) {
    s16 model = opModelIdGet(modelId);
    s16 motion = opMotionIdGet(motionId);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, arg2);
}

void func_80107048_opening(void) {
    // The original call omits the resource id.
    D_801171B0_opening = ((s16 (*)())func_8000B838_main)();
    D_801171B2_opening = InitEspriteSlot(D_801171B0_opening, 0, 0);
    func_8000BC48_main(D_801171B2_opening, 0x4000);
    func_8000BBD4_main(D_801171B2_opening, 0xA0, 0x78);
}

void func_801070AC_opening(void) {
    func_8000C184_main(D_801171B2_opening);
    HuSprKill(D_801171B0_opening);
}

u32 func_801070D8_opening(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = func_800452A0_main(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107140_opening);

s16 func_8010738C_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_8005BEE0_main(slot, 255);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C154_main(slot, 192, 192, 192);
    func_8005FBF8_main(slot, 0, 64, 64);
    func_8005C02C_main(slot, 7);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801074D8_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 4);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_8005BEE0_main(slot, 255);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C060_main(slot, 5, 0, 176, 192);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005C154_main(slot, 192, 192, 192);
    func_8005FBF8_main(slot, 255, 255, 255);
    func_8005C02C_main(slot, 1);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_80107640_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C060_main(slot, 5, 0, 176, 192);
    func_8005C060_main(slot, 7, 255, 255, 255);
    func_8005C060_main(slot, 0, 0, 0, 0);
    func_8005C060_main(slot, 3, 0, 0, 0);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005C154_main(slot, 192, 192, 0);
    func_8005FBF8_main(slot, 255, 255, 255);
    func_8005C02C_main(slot, 6);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801077E8_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 19);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_80060C14_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801078B4_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 20);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_80060C14_main(slot, 0);
    func_8005FE54_main(slot, 1);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_80107980_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 19);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005FE54_main(slot, 1);
    func_80060C14_main(slot, 0);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

void func_80107A4C_opening(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_801171B8_opening[i].espriteSlot = -1;
        D_801171B8_opening[i].event = NULL;
    }
}

void func_80107A90_opening(s32 index) {
    if (D_801171B8_opening[index].unk_08 == 3) {
        func_80060EA8_main(D_801171B8_opening[index].espriteSlot, 1);
        func_800610E0_main(D_801171B8_opening[index].espriteSlot);
    } else {
        func_8005FE90_main(D_801171B8_opening[index].espriteSlot);
        func_8005F364_main(D_801171B8_opening[index].espriteSlot);
        D_801171B8_opening[index].espriteSlot = -1;
    }
    if (D_801171B8_opening[index].event != NULL) {
        func_80019C00_main(D_801171B8_opening[index].event);
        D_801171B8_opening[index].event = NULL;
    }
}

void func_80107B74_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801171B8_opening); i++) {
        if (D_801171B8_opening[i].espriteSlot != -1) {
            func_80107A90_opening(i);
        }
    }
}

void func_80107BD8_opening(s32 slot, f32 x, f32 y) {
    func_8005BB18_main(D_801171B8_opening[slot].espriteSlot, x, y);
}

void func_80107C08_opening(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_801171B8_opening[arg0].espriteSlot, arg1, arg2);
}

void func_80107C70_opening(s32 slot) {
    func_8005FFA8_main(D_801171B8_opening[slot].espriteSlot);
}

void func_80107CA0_opening(s32 slot) {
    func_8005FE90_main(D_801171B8_opening[slot].espriteSlot);
}

void func_80107CD0_opening(s32 slot, u32 event) {
    u32 newEvent;

    func_8005D294_main(D_801171B8_opening[slot].espriteSlot);
    if (D_801171B8_opening[slot].event != NULL) {
        func_80019C00_main(D_801171B8_opening[slot].event);
        D_801171B8_opening[slot].event = NULL;
    }
    newEvent = func_801070D8_opening(event);
    if (0x80000000U < newEvent) {
        D_801171B8_opening[slot].event = (void *)newEvent;
    }
    func_8005B43C_main(D_801171B8_opening[slot].espriteSlot, newEvent, -1, -1);
}

void func_80107D9C_opening(s32 slot, s8 arg1, s32 arg2) {
    func_800601BC_main(D_801171B8_opening[slot].espriteSlot, arg2, arg1);
}

s32 func_80107DD8_opening(s32 slot, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_801171B8_opening[slot].espriteSlot, arg1, arg2);
}

s16 func_80107E10_opening(s32 slot) {
    return D_801171B8_opening[slot].espriteSlot;
}

void func_80107E2C_opening(s32 index) {
    while (func_8005E0C0_main(D_801171B8_opening[index].espriteSlot) != 0) {
        HuPrcVSleep();
    }
}

void func_80107E80_opening(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_80107EBC_opening(s32 slot, s16 arg1) {
    func_8005BE30_main(D_801171B8_opening[slot].espriteSlot, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107EF4_opening);

void opDemoEventSetup(void) {
    func_801061F0_opening();
    func_80110F48_opening();
    CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
    CameraScissorSet(0, &D_80114BD0_opening);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    func_80112944_opening();
    func_80110B90_opening();
    opContErrorCreate();
}

void func_80108118_opening(s32 slot, u32 event) {
    func_80107140_opening(slot, event, 160, 194, 0, 0, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEvent);

void opDemoEventKill(void) {
    func_80107B74_opening();
    opContErrorKill();
    func_80110B9C_opening();
    opWipeKill(15);
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
    MBBackKill();
}

void func_80110B90_opening(void) {
    D_80117338_opening.obj = NULL;
}

void func_80110B9C_opening(void) {
    if (D_80117338_opening.obj != NULL) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        omDelObj(D_80117338_opening.obj);
    }
    D_80117338_opening.obj = NULL;
}

void func_80110C04_opening(omObjData *obj) {
    Vec at;
    f32 random;
    f32 offset;

    D_80117338_opening.active = ~D_80117338_opening.active;
    if (D_80117338_opening.active) {
        random = rand8();
    } else {
        random = -(f32)rand8();
    }
    random *= 1.0f / 255.0f;
    random *= (1.0f - D_80117338_opening.frame * 0.125f) * 0.8f + 0.2f;
    offset = random * D_80117338_opening.magnitude;
    HuVecCopy3F(&at, &D_80114BC4_opening);
    at.y = offset + offset + at.y;
    CameraViewportSet(0, &D_80114BB8_opening, &at);
    offset = -offset;
    MBCameraOffsetSet(0, offset);
    D_80117338_opening.frame++;
    if (D_80117338_opening.totalFrames < D_80117338_opening.frame) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        func_80110B9C_opening();
    }
}

void func_80110D8C_opening(s32 totalFrames, f32 magnitude) {
    D_80117338_opening.frame = 0;
    D_80117338_opening.totalFrames = totalFrames;
    D_80117338_opening.magnitude = magnitude;
    D_80117338_opening.active = 1;
    D_80117338_opening.obj = omAddObj(6, 0, 0, -1, func_80110C04_opening);
}

void opDemoCharCreate(s32 slot, s32 resourceId, f32 x, f32 y, f32 z) {
    opModelCreate(slot, resourceId, 0x6A9);
    opModelPosSet(slot, x, y, z);
    opModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(slot, 2);
}

void opDemoShadowCreate(s32 slot, f32 x, f32 y, f32 z) {
    opModelCreate(slot, 9, 0x229);
    opModelPosSet(slot, x, y, z);
    opModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
}

void opDemoModelKill(void) {
    opModelKillAll();
}

void opDemoSprKill(void) {
    opSprKillAll();
}

void func_80110F48_opening(void) {
    D_80117350_opening.obj = NULL;
    HuVecCopyXYZ(&D_80117350_opening.pos, 350.0f, 190.0f, 3770.0f);
    HuVecCopyXYZ(&D_80117350_opening.at, -1000.0f, 130.0f, 450.0f);
    HuVecCopyXYZ(&D_80117350_opening.up, 0.0f, 1.0f, 0.0f);
}

void func_80110FB0_opening(Vec *pos, Vec *at) {
    func_80111028_opening();
    HuVecCopy3F(&D_80117350_opening.pos, pos);
    HuVecCopy3F(&D_80117350_opening.at, at);
    D_80117350_opening.obj = omAddObj(6, 0, 0, -1, func_80111090_opening);
}

void func_80111028_opening(void) {
    if (D_80117350_opening.obj != NULL) {
        omDelObj(D_80117350_opening.obj);
    }
    D_80117350_opening.obj = NULL;
}

void func_8011105C_opening(void) {
    Hu3DCamSetPositionOrientation(0, &D_80117350_opening.pos, &D_80117350_opening.at, &D_80117350_opening.up);
    Hu3DCamUpdateMtx(0);
}

void func_80111090_opening(omObjData *obj) {
    func_8011105C_opening();
}

void func_801110AC_opening(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ) {
    *posX = D_80117350_opening.pos.x;
    *posY = D_80117350_opening.pos.y;
    *posZ = D_80117350_opening.pos.z;
    *atX = D_80117350_opening.at.x;
    *atY = D_80117350_opening.at.y;
    *atZ = D_80117350_opening.at.z;
}

void func_801110F0_opening(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ) {
    HuVecCopyXYZ(&D_80117350_opening.pos, posX, posY, posZ);
    HuVecCopyXYZ(&D_80117350_opening.at, atX, atY, atZ);
}

f32 func_80111164_opening(f32 x1, f32 z1, f32 x2, f32 z2) {
    return -(atan2df(z2 - z1, x2 - x1) - 90.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801111AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011124C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111490_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111580_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801117D4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111984_opening);

u32 func_80111B34_opening(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed - quotient * 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_80111C08_opening(void) {
    D_80114BE0_opening = func_80111B34_opening(D_80114BE0_opening);
    return D_80114BE0_opening;
}

u32 func_80111C30_opening(u32 max) {
    u32 value;

    value = func_80111B34_opening(D_80114BE0_opening);
    D_80114BE0_opening = value;
    return (value & 0x7FFFFFFF) % max;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111C88_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111DDC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111F58_opening);

void func_80112120_opening(s16 modelId) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    s16 count = data->unk1A;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk0C = particle->unk24 * 3.0f + particle->unk0C;
            particle->unk10 = particle->unk28 * 3.0f + particle->unk10 - 1.0f;
            particle->unk14 = particle->unk2C * 3.0f + particle->unk14;
            particle->unk08 = particle->unk08 - 0.2f > 0.0f ? particle->unk08 - 0.4f : 0.0f;
            if (particle->unk08 <= 0.0f) {
                particle->unk08 = 0.0f;
                particle->unk04 = 180.0f;
            }
        }
    }
    work->unk02++;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleSetup);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleSprMain);

void opTitleKill(void) {
    opSprKill(5);
    opSprKill(4);
    opSprKill(3);
    opSprKill(2);
    opSprKill(1);
    opSprKill(0);
    opContErrorKill();
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
}

void func_80112944_opening(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_80117388_opening[i].obj = NULL;
    }
}

void opDemoObjKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80117388_opening); i++) {
        opDemoObjKill(i);
    }
}

void opDemoObjKill(s32 index) {
    if (D_80117388_opening[index].obj != NULL) {
        omDelObj(D_80117388_opening[index].obj);
    }
    D_80117388_opening[index].obj = NULL;
}

void opDemoObjCreate(s32 index, omObjFunc func) {
    omObjData *obj;

    opDemoObjKill(index);
    obj = omAddObj(6, 0, 0, -1, func);
    D_80117388_opening[index].obj = obj;
    obj->work[0] = index;
}

void func_80112A74_opening(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;

    if (D_8011738C_opening[index][0] < 0) {
        if (opMotionEndCheck(modelId)) {
            opMotionShiftSet(modelId, D_8011739C_opening[index][0], 4, 4, 2);
            D_8011738C_opening[index][0] = 0;
        }
    } else if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        opMotionShiftSet(modelId, D_80117398_opening[index][0].motion[0], 4, 4, 0);
        D_8011738C_opening[index][0] = -1;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_80112BA0_opening(s32 index, s32 modelId, s32 motion1, s32 motion2, s32 startTime, s32 frames) {
    opDemoObjCreate(index, func_80112A74_opening);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].motion[0] = motion1;
    D_8011739C_opening[index][0] = motion2;
    D_80117390_opening[index][0] = frames;
    D_8011738C_opening[index][0] = startTime;
    if (startTime >= 0) {
        opMotionSet(modelId, motion1, 0);
        opMotionTimeSet(modelId, startTime);
    } else {
        opMotionSet(modelId, motion2, 2);
        opMotionTimeSet(modelId, 0);
    }
}

void func_80112C8C_opening(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;

    if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        opMotionTimeSet(modelId, 0);
        D_8011738C_opening[index][0] = 0;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_80112D30_opening(s32 index, s32 modelId, s32 startTime, s32 endTime) {
    opDemoObjCreate(index, func_80112C8C_opening);
    D_80117394_opening[index].modelId = modelId;
    D_8011738C_opening[index][0] = startTime;
    D_80117390_opening[index][0] = endTime;
    func_80106DD0_opening(modelId, 3);
    if (startTime > 0) {
        opMotionTimeSet(modelId, startTime);
    } else {
        opMotionTimeSet(modelId, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoOutEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoOutEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoGuideInEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoGuideInEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoStarWaitMain);

void opDemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames) {
    opDemoObjCreate(index, opDemoStarWaitMain);
    D_80117394_opening[index].modelId = modelId;
    HuVecCopyXYZ(&D_80117398_opening[index][0].pos, x, y, z);
    D_801173A4_opening[index][0] = arg5;
    D_801173A8_opening[index][0] = 0;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = frames;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801134FC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011361C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011373C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801139B0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80113AE8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80113E8C_opening);

void func_80114150_opening(s32 index, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;
    OpWork *slot;

    opModelPosGet(D_80117394_opening[index].modelId, &pos.x, &pos.y, &pos.z);
    slot = &D_80117394_opening[index];
    HuVecCopy3F(&slot->pos, &pos);
    HuVecCopyXYZ(&slot->unk_1C, x, y, z);
    D_801173B0_opening[index][0] = 0;
    D_801173B4_opening[index][0] = 0;
    D_801173B8_opening[index][0] = 0;
    D_80117388_opening[index].obj->func = func_80113E8C_opening;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = arg4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80114250_opening);

void opWipeDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    if (D_80117388_opening[15].color.a != 0) {
        gSPDisplayList((*gfx)++, D_80114BE8_opening);
        gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*gfx)++, 0, 0, D_80117388_opening[15].color.r, D_80117388_opening[15].color.g,
                        D_80117388_opening[15].color.b, D_80117388_opening[15].color.a);
        gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
    }
}

void opWipeColorSet(s32 arg0, u8 red, u8 green, u8 blue, u8 alpha) {
    D_80117388_opening[arg0].color.r = red;
    D_80117388_opening[arg0].color.b = blue;
    D_80117388_opening[arg0].color.g = green;
    D_80117388_opening[arg0].color.a = alpha;
}

void opWipeInMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = D_8011738C_opening[index][0];
    s32 totalFrames = D_80117390_opening[index][0];
    u8 red = D_80117388_opening[index].color.r;
    u8 blue = D_80117388_opening[index].color.b;
    u8 green = D_80117388_opening[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 0.0f;
        opWipeKill(index);
    } else {
        alpha = (1.0f / totalFrames) * (totalFrames - frame);
        D_8011738C_opening[index][0]++;
    }
    opWipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void opWipeOutMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = D_8011738C_opening[index][0];
    s32 totalFrames = D_80117390_opening[index][0];
    u8 red = D_80117388_opening[index].color.r;
    u8 blue = D_80117388_opening[index].color.b;
    u8 green = D_80117388_opening[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 1.0f;
    } else {
        alpha = (1.0f / totalFrames) * frame;
        D_8011738C_opening[index][0]++;
    }
    opWipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void opWipeKill(s32 index) {
    if (D_80117388_opening[index].obj != NULL) {
        func_8001ACDC_main(D_80117388_opening[index].effectId);
        opDemoObjKill(index);
    }
}

void opWipeInCreate(s32 index, s32 totalFrames) {
    opWipeKill(index);
    opDemoObjCreate(index, opWipeInMain);
    D_80117388_opening[index].effectId = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(index, 0, 0, 0, 255);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = totalFrames;
}

void opWipeOutCreate(s32 index, s32 totalFrames) {
    opWipeKill(index);
    opDemoObjCreate(index, opWipeOutMain);
    D_80117388_opening[index].effectId = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(index, 0, 0, 0, 255);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = totalFrames;
}

void opWipeWhiteInCreate(s32 index, s32 totalFrames) {
    opWipeInCreate(index, totalFrames);
    opWipeColorSet(index, 255, 255, 255, 255);
}

void opWipeWhiteOutCreate(s32 index, s32 totalFrames) {
    opWipeOutCreate(index, totalFrames);
    opWipeColorSet(index, 255, 255, 255, 255);
}

void func_801149A4_opening(s32 character) {
    if (D_800D20B8_main[character][2] != 0xFF) {
        func_80033354_main(D_800D20B8_main[character][2]);
        func_80033354_main(D_800D5570_main[character][2]);
        D_800D20B8_main[character][2] = 0xFF;
    }
}

void opSleep(s32 frames) {
    HuPrcSleep(frames);
}

void opContErrorCreate(void) {
    if (GWContErrorGet() == 0) {
        D_80117750_opening.animId = func_8000B838_main(0x100005);
        D_80117750_opening.espriteSlot = InitEspriteSlot(D_80117750_opening.animId, 0, 1);
        func_8000BBD4_main(D_80117750_opening.espriteSlot, 0xA0, 0xA8);
        func_8000BCC8_main(D_80117750_opening.espriteSlot, 0);
        func_8000BB94_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorDispOn(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB54_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorDispOff(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB94_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorKill(void) {
    if (GWContErrorGet() == 0) {
        func_8000C184_main(D_80117750_opening.espriteSlot);
        HuSprKill(D_80117750_opening.animId);
    }
}
