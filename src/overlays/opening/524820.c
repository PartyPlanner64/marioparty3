#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "mallocblock.h"
#include "opening.h"

typedef struct {
    s32 x;
    s32 y;
    s32 frame;
    u32 color;
} OpDemoStar;
typedef struct {
    OpDemoStar stars[10];
} OpDemoStars;

typedef struct {
    /* 0x00 */ f32 currentYaw;
    /* 0x04 */ Vec rot;
    /* 0x10 */ f32 targetYaw;
} OpDemoRotations;

extern const Vec D_80114D84_opening;
extern const Vec D_80114D90_opening;
extern Vec D_80114B70_opening[2], D_80114B88_opening[2], D_80114BA0_opening, D_80114BAC_opening;
extern const Vec D_80114D9C_opening, D_80114DA8_opening;

void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
HmfMotionNode *func_8001D33C_main(s16 model, char *name);

void func_8001EF6C_main(s16, s16, char *);
void func_8002367C_main(HuMtx4F, HuMtx4F);
void func_80046030_main(s16, s16);
void func_80088700_main(HuMtx4F, f32, f32, f32);
void opDemoEndSet(s32);
f32 func_8011124C_opening(f32, f32, f32, f32, f32);

void func_801061F0_opening(void);
void func_8010621C_opening(void);
s16 opAnimIdGet(s32 slot);
s16 opEspIdGet(s32 slot);
void opAnimCreate(s32 arg0, s32 arg1);
void opAnimKill(s32 arg0);
void opEspCreate(s32 slot, s16 animId);
void opEspKill(s32 slot);
void opSprCreate(s32 slot, s32 resourceId);
void opSprBGCreate(s32 slot, s32 resourceId);
void opSprKill(s32 slot);
void opSprKillAll(void);
void opSprDispOn(s32 slot);
void opSprDispOff(s32 slot);
void opSprBGDispOn(s32 slot);
void opSprBGDispOff(s32 slot);
void opSprPosSet(s32 arg0, s32 arg1, s32 arg2);
void opSprPosGet(s32 slot, s32 *x, s32 *y);
void opSprScaleSet(s32 arg0, f32 arg1, f32 arg2);
void opSprAlphaSet(s32 arg0, u16 arg1);
void opSprAttrSet(s32 arg0, u16 arg1);
void opSprAttrReset(s32 arg0, u16 arg1);
void func_80106734_opening(s32 arg0, u16 arg1);
void func_80106768_opening(s32 slot, u16 arg1, u16 arg2);
void func_801067D4_opening(void);
void opModelCreate(s32 slot, s32 resourceId, s32 arg2);
void opMotionCreate(s32 slot, s32 resourceId, s32 arg2);
void opModelKill(s32 slot);
void opModelKillAll(void);
s16 opModelIdGet(s32 modelId);
s16 opMotionIdGet(s32 motionId);
void opModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void opModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void opModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void opModelPosGet(s32 modelId, f32 *posX, f32 *posY, f32 *posZ);
void opModelRotGet(s32 modelId, f32 *rotX, f32 *rotY, f32 *rotZ);
void opModelScaleGet(s32 modelId, f32 *scaleX, f32 *scaleY, f32 *scaleZ);
void opModelDispOff(s32 arg0);
void opModelDispOn(s32 arg0);
void opMotionFlagSet(s32 modelId, s16 arg1);
void opMotionShiftSet(s32 modelId, s32 motionId, s16 arg2, s16 arg3, s16 arg4);
void func_80106DD0_opening(s32 modelId, s16 arg1);
void opMotionSpeedSet(s32 modelId, f32 speed);
void opMotionTimeSet(s32 slot, u32 time);
void opMotionEndWait(s32 slot);
s32 opMotionEndCheck(s32 arg0);
void opMotionSet(s32 modelId, s32 motionId, s16 arg2);
void func_80107048_opening(void);
void func_801070AC_opening(void);
u32 func_801070D8_opening(u32 arg0);
s16 func_8010738C_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 func_801074D8_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 func_80107640_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 func_801077E8_opening(u32 event, s16 x, s16 y, s16 style);
s16 func_801078B4_opening(u32 event, s16 x, s16 y, s16 style);
s16 func_80107980_opening(u32 event, s16 x, s16 y, s16 style);
void func_80107A4C_opening(void);
void func_80107A90_opening(s32 index);
void func_80107B74_opening(void);
void func_80107BD8_opening(s32 slot, f32 x, f32 y);
void func_80107C08_opening(s32 arg0, f32 arg1, f32 arg2);
void func_80107C70_opening(s32 slot);
void func_80107CA0_opening(s32 slot);
void func_80107CD0_opening(s32 slot, u32 event);
void func_80107D9C_opening(s32 slot, s8 arg1, s32 arg2);
s32 func_80107DD8_opening(s32 slot, s16 arg1, s32 arg2);
s16 func_80107E10_opening(s32 slot);
void func_80107E2C_opening(s32 index);
void func_80107E80_opening(s32 arg0);
void func_80107EBC_opening(s32 slot, s16 arg1);
u16 func_80107EF4_opening(s32 value);
void opDemoEventSetup(void);
void func_80108118_opening(s32 slot, u32 event);
void opDemoEventKill(void);
void func_80110B90_opening(void);
void func_80110B9C_opening(void);
void func_80110C04_opening(omObjData *obj);
void func_80110D8C_opening(s32 totalFrames, f32 magnitude);
void opDemoCharCreate(s32 slot, s32 resourceId, f32 x, f32 y, f32 z);
void opDemoShadowCreate(s32 slot, f32 x, f32 y, f32 z);
void opDemoModelKill(void);
void opDemoSprKill(void);
void func_80110F48_opening(void);
void func_80110FB0_opening(Vec *pos, Vec *at);
void func_80111028_opening(void);
void func_8011105C_opening(void);
void func_80111090_opening(omObjData *obj);
void func_801110AC_opening(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ);
void func_801110F0_opening(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ);
f32 func_80111164_opening(f32 x1, f32 z1, f32 x2, f32 z2);
f32 func_801111AC_opening(f32 current, f32 target, f32 step);
f32 func_80111490_opening(f32 current, f32 x, f32 z, f32 weight);
void func_80111580_opening(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s16 func_801117D4_opening(s32 resourceId, s32 arg1);
s32 func_80111984_opening(s32 resourceId, s32 arg1);
u32 func_80111B34_opening(u32 seed);
u32 func_80111C08_opening(void);
u32 func_80111C30_opening(u32 max);
s32 func_80111C88_opening(s16 modelId, f32 x, f32 y, f32 z);
s32 func_80111DDC_opening(s16 modelId, f32 x, f32 y, f32 z, f32 size);
void func_80111F58_opening(s16 modelId);
void func_80112120_opening(s16 modelId);
void opTitleSetup(void);
void opTitleSprMain(void);
void opTitleKill(void);
void func_80112944_opening(void);
void opDemoObjKillAll(void);
void opDemoObjKill(s32 index);
void opDemoObjCreate(s32 index, omObjFunc func);
void func_80112A74_opening(omObjData *obj);
void func_80112BA0_opening(s32 index, s32 modelId, s32 motion1, s32 motion2, s32 startTime, s32 frames);
void func_80112C8C_opening(omObjData *obj);
void func_80112D30_opening(s32 index, s32 modelId, s32 startTime, s32 endTime);
void opDemoOutEffMain(omObjData *obj);
void opDemoOutEffCreate(s32 index, s32 modelId);
void opDemoGuideInEffMain(omObjData *obj);
void opDemoGuideInEffCreate(s32 index, s32 modelId);
void opDemoStarWaitMain(omObjData *obj);
void opDemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames);
void func_801134FC_opening(s32 index, Vec *pos1, Vec *pos2, f32 scale, f32 angle);
void func_8011361C_opening(omObjData *obj);
void func_8011373C_opening(omObjData *obj);
void func_801139B0_opening(s32 index, s32 modelId, Vec *pos1, Vec *pos2, char *node1, char *node2);
void func_80113AE8_opening(omObjData *obj);
void func_80113E8C_opening(omObjData *obj);
void func_80114150_opening(s32 index, f32 x, f32 y, f32 z, s32 arg4);
void func_80114250_opening(s32 index, s32 modelId, f32 x, f32 y, f32 z);
void opWipeDraw(Gfx **gfx, s32 arg1, s32 arg2);
void opWipeColorSet(s32 arg0, u8 red, u8 green, u8 blue, u8 alpha);
void opWipeInMain(omObjData *obj);
void opWipeOutMain(omObjData *obj);
void opWipeKill(s32 index);
void opWipeInCreate(s32 index, s32 totalFrames);
void opWipeOutCreate(s32 index, s32 totalFrames);
void opWipeWhiteInCreate(s32 index, s32 totalFrames);
void opWipeWhiteOutCreate(s32 index, s32 totalFrames);
void func_801149A4_opening(s32 character);
void opSleep(s32 frames);
void opContErrorCreate(void);
void opContErrorDispOn(void);
void opContErrorDispOff(void);
void opContErrorKill(void);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", func_80107140_opening);

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

u16 func_80107EF4_opening(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            camera = HmfModelData[gCameraList[0].unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", camera->unk08, camera->unk0C, camera->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", camera->unk14, camera->unk18, camera->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", camera->unk20, camera->unk24, camera->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

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

// These constants follow the window-event data in ROM.
const OpDemoStars D_80114CE4_opening = { {
    { 20, 20, 3, 0xFFFFFF00 },
    { 50, 180, 8, 0xFFFFFF00 },
    { 30, 120, 20, 0xFFFFFF00 },
    { 75, 80, 75, 0xC0F08000 },
    { 90, 200, 120, 0xFFFFFF00 },
    { 120, 45, 45, 0xC0C00000 },
    { 160, 80, 24, 0xFFFFFF00 },
    { 200, 160, 62, 0xC0C0FF00 },
    { 220, 120, 0, 0x8040FF00 },
    { 240, 50, 80, 0xFFFFFF00 },
} };

const Vec D_80114D84_opening = { 600.0f, 80.0f, 800.0f };

const Vec D_80114D90_opening = { 0.0f, 0.0f, -100.0f };

const Vec D_80114D9C_opening = { 0.0f, 0.0f, 2000.0f };

const Vec D_80114DA8_opening = { 0.0f, 0.0f, 0.0f };

void opDemoEvent(void) {
    s32 loopContinue;
    f32 runProgress;
    f32 launchProgress;
    f32 spinAngle;
    f32 temp_f20;
    f32 distance;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 cameraCosine;
    f32 approachYaw;
    s32 ascentHeight;
    s32 i;
    s32 storyMode;
    s32 frame;
    HmfModel *temp_s1;
    HmfMotionNode *temp_v0_12;
    f32 temp_f0;
    f32 turnProgress;
    f32 temp_f0_10;
    f32 temp_f0_12;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_18;
    f32 temp_f0_20;
    f32 temp_f0_22;
    f32 temp_f0_24;
    f32 temp_f0_26;
    f32 temp_f0_27;
    f32 temp_f0_30;
    f32 temp_f0_32;
    f32 temp_f0_34;
    f32 temp_f0_36;
    f32 temp_f0_38;
    f32 temp_f0_39;
    f32 temp_f0_40;
    f32 temp_f0_41;
    f32 temp_f0_42;
    f32 temp_f0_43;
    f32 temp_f0_44;
    f32 temp_f0_45;
    f32 temp_f0_46;
    f32 temp_f0_49;
    f32 temp_f0_53;
    f32 temp_f0_54;
    f32 temp_f0_56;
    f32 temp_f0_57;
    f32 temp_f0_58;
    f32 temp_f0_59;
    f32 temp_f0_5;
    f32 temp_f0_60;
    f32 temp_f0_61;
    f32 temp_f0_62;
    f32 temp_f0_63;
    f32 temp_f0_8;
    f32 temp_f12;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f2_9;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 var_f0;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    f32 var_f2_4;
    f32 var_f2_5;
    f32 var_f2_6;
    s16 temp_s1_2;
    s16 temp_s1_3;
    s16 temp_s1_4;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_13;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_9;
    s32 var_s1;
    s32 var_s3;

    D_800CD280_main = 1;
    if (omovlevtno == 0) {
        storyMode = 1;
    } else {
        storyMode = omovlevtno == 1;
    }
    opContErrorDispOn();
    if (storyMode != 0) {
        HuAudSeqPlay(0x39);
    }
    HuAudFXPlay(0x234);
    MBBackLoad(0x1F);
    func_800E9344_shared_board(10.0f, 10000.0f);
    opModelCreate(0xB, 0xF0007, 0x2A9);
    opModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
    opMotionTimeSet(0xB, 0U);
    opMotionFlagSet(0xB, 1);
    opModelDispOff(0xB);
    {
        OpDemoStars starLayout = D_80114CE4_opening;
        s32 firstSprite;
        i = 0;
        func_80111C08_opening();
        firstSprite = 1;
        // Keep the explicit back edge for the original stack-address calculation.
    star_loop:
        {
            if (i == 0) {
                opSprBGCreate(0, 0xF0009);
            } else if (i == firstSprite) {
                opSprBGCreate(1, 0xF000A);
            } else {
                if (i & 1) {
                    opEspCreate(i, 0);
                } else {
                    opEspCreate(i, 1);
                }
                opSprAttrSet(i, 0x4000U);
                func_80106768_opening(i, 0U, func_80111C30_opening(6U) & 0xFFFF);
            }
            opSprPosSet(i, starLayout.stars[i].x, starLayout.stars[i].y);
            func_8000BEAC_main(opEspIdGet(i) & 0xFFFF, 0xFF, 0xFF, 0xFF);
            i += 1;
        }
        loopContinue = i < 10;
        if (loopContinue) {
            goto star_loop;
        }
    }
    {
        Vec sp20;
        Vec sp30;
        Vec sp40;
        Vec sp50;
        Vec sp60;
        Vec sp70;
        Vec sp80;
        Vec sp90;
        Vec spA0;
        Vec spB0;
        HuMtx4F savedMatrix;
    loop_17:
        loopContinue = WipeStatGet();
        if (loopContinue != 0) {
            HuPrcVSleep();
            goto loop_17;
        }
        sp20 = D_80114D84_opening;
        sp30 = D_80114D90_opening;
        func_800E92D4_shared_board();
        func_80110FB0_opening(&sp20, &sp30);
        if (storyMode != 0) {
            func_80108118_opening(0, 0x5A00U);
            func_80107CD0_opening(0, 0x4D01U);
            func_80107E2C_opening(0);
        } else {
            func_80108118_opening(0, 0x5A00U);
            func_80107CD0_opening(0, 0x4D00U);
            opSleep(0x3C);
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x235);
        }
        func_80111580_opening(0.0f, 0.0f, 0.0f, 0.0f);
        sp40 = D_80114D9C_opening;
        sp50 = D_80114DA8_opening;
        func_80110FB0_opening(&sp40, &sp50);
        opModelDispOn(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x236);
        }
        func_80106DD0_opening(0xB, 3);
        opMotionEndWait(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x237);
        }
        opWipeWhiteOutCreate(0xF, 0x14);
        HuPrcSleep(0x32);
        opModelKill(0xB);
        opModelCreate(0xB, 0xA0122, 0x2A9);
        opModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
        opModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
        opMotionCreate(0x6C, 0xA0123, 0);
        opMotionCreate(0x6D, 0xA0124, 0);
        opMotionCreate(0x6E, 0xA012B, 0);
        opMotionSet(0xB, 0x6D, 1);
        opMotionFlagSet(0xB, 1);
        opMotionTimeSet(0xB, 1U);
        func_80046030_main(opModelIdGet(0xB), -5);
        opDemoStarWaitCreate(0, 0xB, 0.0f, 0.0f, 0.0f, 50.0f, 0x2D);
        opWipeWhiteInCreate(0xF, 0x10);
        HuPrcSleep(0x10);
        HuPrcSleep(0x14);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D03U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D02U);
            opSleep(0x78);
        }
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D05U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D04U);
            opSleep(0x78);
        }
        func_80107CD0_opening(0, 0x4D06U);
        opDemoObjKill(0);
        temp_s1 = &HmfModelData[opModelIdGet(0xB)];
        func_8002367C_main(savedMatrix, temp_s1->mtx);
        spinAngle = 0.0f;
        opMotionShiftSet(0xB, 0x6E, 4, 4, (s16)2);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D07U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D06U);
            opSleep(0x78);
        }
        func_80107CA0_opening(0);
        opMotionFlagSet(0xB, 1);
        if (storyMode != 0) {
            HuAudFXPlay(0x238);
        }
        opModelPosGet(0xB, &sp60.x, &sp60.y, &sp60.z);
        HuVecCopyXYZ(&sp70, -1000.0f, -2000.0f, 0.0f);
        for (i = 0; i < 0x1E; i++) {
            temp_f4 = (f32)i * 0.033333335f;
            HuVecCopyXYZ(&sp80, ((sp70.x - sp60.x) * temp_f4) + sp60.x, ((sp70.y - sp60.y) * temp_f4 * temp_f4) + sp60.y, ((sp70.z - sp60.z) * temp_f4) + sp60.z);
            opModelPosSet(0xB, sp80.x, sp80.y, sp80.z);
            spinAngle += 17.23f;
            if (spinAngle > 360.0f) {
                spinAngle -= 360.0f;
            }
            temp_s1->rot.z = spinAngle;
            HuPrcVSleep();
        }
        temp_s1 = &HmfModelData[opModelIdGet(0xB)];
        func_8002367C_main(temp_s1->mtx, savedMatrix);
        HuPrcSleep(0x10);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D09U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D08U);
            opSleep(0x3C);
        }
        opWipeOutCreate(0xF, 0x14);
        if (storyMode != 0) {
            HuAudSeqFadeOut(0x17);
        }
        func_8004AB0C_main(0x17);
        HuPrcSleep(0x17);
        func_80107CA0_opening(0);
        for (i = 0; i < 0xA; i++) {
            opSprKill(i);
        }
        opModelKill(0x6E);
        MBBackKill();
        MBBackLoad(0x20);
        func_800E92D4_shared_board();
        Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
        func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
        opModelDispOff(0xB);
        opDemoCharCreate(0, 0x200A0, 19.0f, 0.0f, 2700.0f);
        opModelRotSet(0, 0.0f, -30.0f, 0.0f);
        temp_v0_2 = opModelIdGet(0);
        func_80017790_main(temp_v0_2, 2, 0, 0x200A4);
        func_80017A84_main(temp_v0_2, 2, 0, 1, (s16)0);
        opDemoShadowCreate(0x20, 19.0f, 0.0f, 2700.0f);
        opDemoCharCreate(1, 0x300A0, -250.0f, 0.0f, 2920.5f);
        temp_v0_3 = opModelIdGet(1);
        func_80017790_main(temp_v0_3, 2, 1, 0x300A4);
        func_80017A84_main(temp_v0_3, 2, 1, 7, (s16)0);
        opDemoShadowCreate(0x21, -250.0f, 0.0f, 2920.5f);
        opModelDispOff(1);
        opDemoCharCreate(2, 0x700A0, 140.0f, 0.0f, 2680.0f);
        temp_v0_4 = opModelIdGet(2);
        func_80017790_main(temp_v0_4, 2, 2, 0x700A4);
        func_80017A84_main(temp_v0_4, 2, 2, 3, (s16)0);
        opDemoShadowCreate(0x22, 140.0f, 0.0f, 2680.0f);
        opModelScaleSet(0x22, 1.5f, 1.0f, 1.5f);
        opModelDispOff(2);
        opDemoCharCreate(3, 0x400A0, 240.0f, 0.0f, 2680.0f);
        temp_v0_5 = opModelIdGet(3);
        func_80017790_main(temp_v0_5, 2, 3, 0x400A4);
        func_80017A84_main(temp_v0_5, 2, 3, 6, (s16)0);
        opDemoShadowCreate(0x23, 240.0f, 0.0f, 2680.0f);
        opModelDispOff(3);
        opModelDispOff(0x23);
        opDemoCharCreate(4, 0x500A0, -240.0f, 0.0f, 2760.0f);
        temp_v0_6 = opModelIdGet(4);
        func_80017790_main(temp_v0_6, 2, 4, 0x500A4);
        func_80017A84_main(temp_v0_6, 2, 4, 9, (s16)0);
        opDemoShadowCreate(0x24, 240.0f, 0.0f, 2680.0f);
        opModelDispOff(4);
        opModelDispOff(0x24);
        opDemoCharCreate(5, 0x600A0, -140.0f, 0.0f, 2710.0f);
        temp_v0_7 = opModelIdGet(5);
        func_80017790_main(temp_v0_7, 2, 5, 0x600A4);
        func_80017A84_main(temp_v0_7, 2, 5, 7, (s16)0);
        opDemoShadowCreate(0x25, -140.0f, 0.0f, 2710.0f);
        opModelScaleSet(0x25, 1.5f, 1.0f, 1.5f);
        opModelDispOff(5);
        opModelDispOff(0x25);
        opModelCreate(6, 0xF0004, 0x6A9);
        opModelPosSet(6, -77.25f, 40.0f, 2632.5f);
        opModelScaleSet(6, 1.0f, 1.0f, 1.0f);
        opModelPosSet(0x21, -77.25f, 0.0f, 2632.5f);
        opModelCreate(7, 0xF0003, 0x6A9);
        opModelPosSet(7, 19.0f, 15.0f, 2700.0f);
        opModelRotSet(7, 0.0f, -30.0f, 0.0f);
        opModelScaleSet(7, 1.0f, 1.0f, 1.0f);
        opModelPosSet(0x22, 19.0f, 15.0f, 2700.0f);
        opModelCreate(8, 0xF0005, 0x6A9);
        opModelPosSet(8, -51.0f, 92.5f, 2651.25f);
        opModelScaleSet(8, 1.0f, 1.0f, 1.0f);
        opModelCreate(9, 0xF0002, 0x2A9);
        opModelPosSet(9, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(9, 1.0f, 1.0f, 1.0f);
        opModelCreate(0xA, 0xA015E, 0xAA9);
        opModelPosSet(0xA, -430.0f, 60.0f, 2605.0f);
        opModelScaleSet(0xA, 0.3f, 0.3f, 0.3f);
        opMotionFlagSet(0xA, 2);
        func_80114250_opening(0xC, 0xA, -340.0f, 60.0f, 2555.0f);
        opModelCreate(0x1A, 0xB0001, 0x6A9);
        opModelPosSet(0x1A, -400.0f, 25.0f, 2650.0f);
        opModelScaleSet(0x1A, 1.8f, 1.0f, 1.8f);
        opMotionTimeSet(0x1A, 0U);
        opMotionFlagSet(0x1A, 1);
        opModelDispOff(0x1A);
        opModelCreate(0x1B, 0xA015E, 0xAA9);
        opModelPosSet(0x1B, 0.0f, 100.0f, 100.0f);
        opModelScaleSet(0x1B, 0.3f, 0.3f, 0.3f);
        opMotionFlagSet(0x1B, 2);
        func_80114250_opening(0xB, 0x1B, -340.0f, 80.0f, 3100.0f);
        opMotionCreate(0x28, 0x20000, 0);
        opMotionCreate(0x29, 0x20001, 0);
        opMotionCreate(0x2A, 0xF000B, 0);
        opMotionCreate(0x2B, 0xF000C, 0);
        opMotionCreate(0x2C, 0x2001B, 0);
        opMotionCreate(0x2D, 0x1D003B, 0);
        opMotionCreate(0x2E, 0xF000D, 0);
        opMotionCreate(0x2F, 0xF000E, 0);
        opMotionCreate(0x32, 0xF0010, 0);
        opMotionCreate(0x33, 0x2009C, 0);
        opMotionCreate(0x34, 0xF0011, 0);
        opMotionCreate(0x35, 0x2009B, 0);
        opMotionCreate(0x38, 0x30000, 0);
        opMotionCreate(0x39, 0x30001, 0);
        opMotionCreate(0x3A, 0xF0012, 0);
        opMotionCreate(0x3C, 0x3007A, 0);
        opMotionCreate(0x3D, 0x3009C, 0);
        opMotionCreate(0x3E, 0x3009B, 0);
        opMotionCreate(0x40, 0x70000, 0);
        opMotionCreate(0x41, 0x70001, 0);
        opMotionCreate(0x42, 0x1D0053, 0);
        opMotionCreate(0x43, 0xF0014, 0);
        opMotionCreate(0x46, 0x7009C, 0);
        opMotionCreate(0x47, 0x7009B, 0);
        opMotionCreate(0x48, 0x40000, 0);
        opMotionCreate(0x49, 0x40001, 0);
        opMotionCreate(0x4A, 0xF0015, 0);
        opMotionCreate(0x4D, 0x4009C, 0);
        opMotionCreate(0x4E, 0x40032, 0);
        opMotionCreate(0x4F, 0x4009B, 0);
        opMotionCreate(0x50, 0x50000, 0);
        opMotionCreate(0x51, 0x50001, 0);
        opMotionCreate(0x52, 0xF0016, 0);
        opMotionCreate(0x55, 0x5009C, 0);
        opMotionCreate(0x56, 0x50033, 0);
        opMotionCreate(0x57, 0x5009B, 0);
        opMotionCreate(0x58, 0x60000, 0);
        opMotionCreate(0x59, 0x60001, 0);
        opMotionCreate(0x5A, 0xF0018, 0);
        opMotionCreate(0x5B, 0xF0019, 0);
        opMotionCreate(0x5E, 0x6009C, 0);
        opMotionCreate(0x5F, 0xF001B, 0);
        opMotionCreate(0x60, 0x6009B, 0);
        opModelDispOn(0xB);
        opModelPosSet(0xB, 920.0f, 2060.0f, 2580.0f);
        opModelRotSet(0xB, 0.0f, 45.0f, 0.0f);
        opModelScaleSet(0xB, 2.5f, 2.5f, 2.5f);
        opMotionFlagSet(0xB, 1);
        opMotionSet(0xB, 0x6D, 1);
        opMotionFlagSet(0xB, 1);
        opMotionTimeSet(0xB, 1U);
        opMotionSet(0, 0x2A, 2);
        opWipeInCreate(0xF, 0x10);
        HuPrcSleep(8);
        if (storyMode == 0) {
            HuAudSeqPlay(1);
        }
        HuPrcSleep(8);
        if (storyMode != 0) {
            HuAudSeqPlay(0x3A);
        }
        HuPrcSleep(0x1E);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D0BU);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D0AU);
            opSleep(0x3C);
        }
        opMotionShiftSet(0, 0x2B, 4, 4, 0);
        opMotionEndWait(0);
        opMotionShiftSet(0, 0x32, 4, 4, (s16)2);
        HuPrcSleep(0x14);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D0DU);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D0CU);
            opSleep(0x1C);
        }
        func_80107CA0_opening(0);
        opModelPosGet(0xB, &sp90.x, &sp90.y, &sp90.z);
        HuVecCopyXYZ(&spA0, -580.0f, 60.0f, 2580.0f);
        for (i = 0; i < 0x11; i++) {
            temp_f20 = (f32)i * 0.0625f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * temp_f20) + sp90.x, ((spA0.y - sp90.y) * temp_f20) + sp90.y, ((spA0.z - sp90.z) * temp_f20) + sp90.z);
            opModelPosSet(0xB, spB0.x, spB0.y, spB0.z);
            HuPrcVSleep();
            if (i == 0xE) {
                opModelDispOn(0x1A);
                opMotionTimeSet(0x1A, 0U);
                func_80106DD0_opening(0x1A, 1);
            }
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x239);
        }
        func_80114150_opening(0xB, -1580.0f, 600.0f, 3430.0f, 0x28);
        func_80114150_opening(0xC, -780.0f, 590.0f, 3430.0f, 0x28);
        func_80110D8C_opening(0xC, 4.0f);
        opMotionShiftSet(0, 0x2C, 4, 4, (s16)2);
        i = 0;
        if (storyMode != 0) {
            HuAudFXPlay(0x287);
            i = 0;
        }
        {
            Vec rotations[4];
            for (i = 0; i < 4; i++) {
                rotations[i].x = rotations[i].y = rotations[i].z = 0.0f;
            }
            for (i = 0; i < 0x15; i++) {
                launchProgress = (f32)i * 0.05f;
                HuVecCopyXYZ(&sp90, 19.0f, 0.0f, 2700.0f);
                HuVecCopyXYZ(&spA0, 1519.0f, 1500.0f, 2700.0f);
                HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * launchProgress) + sp90.x, ((spA0.y - sp90.y) * launchProgress) + sp90.y, ((spA0.z - sp90.z) * launchProgress) + sp90.z);
                opModelPosSet(0, spB0.x, spB0.y, spB0.z);
                opModelPosSet(0x20, spB0.x, 0.0f, spB0.z);
                opModelScaleSet(0x20, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                opModelIdGet(0);
                opModelRotSet(0, rotations[0].x, rotations[0].y, rotations[0].z);
                var_f0 = rotations[0].x + 33.0f;
                if (!(var_f0 < 360.0f)) {
                    var_f0 -= 360.0f;
                }
                rotations[0].x = var_f0;
                HuVecCopyXYZ(&sp90, -77.25f, 40.0f, 2632.5f);
                HuVecCopyXYZ(&spA0, 922.75f, 1540.0f, 2632.5f);
                HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * launchProgress) + sp90.x, ((spA0.y - sp90.y) * launchProgress) + sp90.y, ((spA0.z - sp90.z) * launchProgress) + sp90.z);
                opModelPosSet(6, spB0.x, spB0.y, spB0.z);
                opModelPosSet(0x21, spB0.x, 0.0f, spB0.z);
                opModelScaleSet(0x21, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                opModelIdGet(6);
                opModelRotSet(6, rotations[1].x, rotations[1].y, rotations[1].z);
                var_f2 = rotations[1].x + 66.0f;
                if (!(var_f2 < 360.0f)) {
                    var_f2 -= 360.0f;
                }
                rotations[1].x = var_f2;
                var_f2_2 = rotations[1].y + 12.0f;
                if (!(var_f2_2 < 360.0f)) {
                    var_f2_2 -= 360.0f;
                }
                rotations[1].y = var_f2_2;
                HuVecCopyXYZ(&sp90, 19.0f, 15.0f, 2700.0f);
                HuVecCopyXYZ(&spA0, 1419.0f, 1515.0f, 2700.0f);
                HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * launchProgress) + sp90.x, ((spA0.y - sp90.y) * launchProgress) + sp90.y, ((spA0.z - sp90.z) * launchProgress) + sp90.z);
                opModelPosSet(7, spB0.x, spB0.y, spB0.z);
                opModelPosSet(0x22, spB0.x, 0.0f, spB0.z);
                opModelScaleSet(0x22, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                opModelIdGet(7);
                opModelRotSet(7, rotations[2].x, rotations[2].y, rotations[2].z);
                var_f2_3 = rotations[2].x + 13.0f;
                if (!(var_f2_3 < 360.0f)) {
                    var_f2_3 -= 360.0f;
                }
                rotations[2].x = var_f2_3;
                var_f2_4 = rotations[2].y + 42.0f;
                if (!(var_f2_4 < 360.0f)) {
                    var_f2_4 -= 360.0f;
                }
                rotations[2].y = var_f2_4;
                HuVecCopyXYZ(&sp90, -51.0f, 92.5f, 2651.25f);
                HuVecCopyXYZ(&spA0, 1549.0f, 1592.5f, 2651.25f);
                HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * launchProgress) + sp90.x, ((spA0.y - sp90.y) * launchProgress) + sp90.y, ((spA0.z - sp90.z) * launchProgress) + sp90.z);
                opModelPosSet(8, spB0.x, spB0.y, spB0.z);
                opModelIdGet(8);
                opModelRotSet(8, rotations[3].x, rotations[3].y, rotations[3].z);
                var_f2_5 = rotations[3].x + 123.0f;
                if (!(var_f2_5 < 360.0f)) {
                    var_f2_5 -= 360.0f;
                }
                rotations[3].x = var_f2_5;
                var_f2_6 = rotations[3].y + 45.0f;
                if (!(var_f2_6 < 360.0f)) {
                    var_f2_6 -= 360.0f;
                }
                rotations[3].y = var_f2_6;
                HuPrcVSleep();
            }
            HuPrcSleep(0x14);
            opModelKill(0x1A);
            HuPrcSleep(3);
            opMotionShiftSet(0, 0x34, 4, 4, (s16)2);
            opMotionShiftSet(1, 0x39, 4, 4, (s16)2);
            opMotionShiftSet(2, 0x41, 4, 4, (s16)2);
            opMotionShiftSet(3, 0x49, 4, 4, (s16)2);
            opMotionShiftSet(4, 0x51, 4, 4, (s16)2);
            opMotionShiftSet(5, 0x59, 4, 4, (s16)2);
            opMotionSpeedSet(1, 1.6f);
            opMotionSpeedSet(2, 1.6f);
            opMotionSpeedSet(3, 1.6f);
            opMotionSpeedSet(4, 1.6f);
            opMotionSpeedSet(5, 1.6f);
            opModelDispOn(1);
            opModelDispOn(2);
            opModelDispOn(3);
            opModelDispOn(4);
            opModelDispOn(5);
            opModelDispOn(0x20);
            opModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
            opModelDispOn(0x21);
            opModelScaleSet(0x21, 1.0f, 1.0f, 1.0f);
            opModelDispOn(0x22);
            opModelScaleSet(0x22, 1.0f, 1.0f, 1.0f);
            opModelDispOn(0x23);
            opModelDispOn(0x24);
            opModelDispOn(0x25);
        }
    }
    {
        Vec sp100;
        Vec sp110;
        Vec sp120;
        Vec sp130;
        Vec sp140;
        Vec *approachTarget;
        Vec sp150;
        Vec sp160;
        Vec sp170;
        Vec sp180;
        Vec sp190;
        Vec sp1A0;
        Vec sp1B0;
        OpDemoRotations angles;
        Vec sp1D8;
        Vec sp1E8;
        Vec sp1F8;
        Vec sp208;
        Vec sp218;
        Vec sp228;
        Vec sp238;
        f32 characterAngles[8];
        Vec sp268;
        Vec sp278;
        Vec sp288;
        Vec treePos1;
        Vec sp2A8;
        Vec sp2B8;
        Vec sp2C8;
        Vec treePos2;
        Vec sp2E8;
        Vec sp2F8;
        Vec cameraPos1;
        Vec cameraAt1;
        Vec sp328;
        Vec sp338;
        Vec sp348;
        Vec sp358;
        f32 characterAngles2[8];
        Vec sp388;
        Vec sp398;
        Vec sp3A8;
        Vec sp3B8;
        Vec sp3C8;
        Vec cameraPos2;
        Vec cameraAt2;
        Vec sp3F8;
        Vec sp408;
        Vec sp418;
        Vec sp428;
        Vec sp438;
        Vec sp448;
        Vec sp458;
        Vec sp468;
        Vec2f sp478;
        Vec sp480;
        Vec sp490;
        Vec sp4A0;
        Vec sp4B0;
        Vec sp4C0;
        f32 lastAngles[2];
        frame = 0x37;
        do {
            runProgress = (f32)frame * 0.008333334f;
            if (frame == 0x64) {
                func_80107C70_opening(0);
                func_80107CD0_opening(0, 0x4D0EU);
            }
            HuVecCopyXYZ(&sp100, 1519.0f, 0.0f, 2700.0f);
            HuVecCopyXYZ(&sp110, 62.5f, 0.0f, 2775.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(0, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x20, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            opModelRotSet(0, 0.0f, func_80111164_opening(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, -850.0f, 0.0f, 3920.5f);
            HuVecCopyXYZ(&sp110, -300.0f, 0.0f, 2920.5f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(1, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x21, sp130.x, 0.0f, sp130.z);
            opModelRotSet(1, 0.0f, func_80111164_opening(sp130.x, sp130.z, (sp110.x - sp100.x) + sp130.x, (sp110.z - sp100.z) + sp130.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1640.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp110, 120.0f, 0.0f, 2505.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(2, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x22, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            opModelRotSet(2, 0.0f, func_80111164_opening(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1740.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp110, 240.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(3, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x23, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            opModelRotSet(3, 0.0f, func_80111164_opening(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 960.0f, 0.0f, 3360.0f);
            HuVecCopyXYZ(&sp110, -190.0f, 0.0f, 2775.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(4, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x24, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            opModelRotSet(4, 0.0f, func_80111164_opening(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1160.0f, 0.0f, 3310.0f);
            HuVecCopyXYZ(&sp110, -140.0f, 0.0f, 2575.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            opModelPosSet(5, sp130.x, sp130.y, sp130.z);
            opModelPosSet(0x25, sp130.x, sp130.y, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            opModelRotSet(5, 0.0f, func_80111164_opening(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuPrcVSleep();
            frame++;
        } while (frame < 0x79);
        opMotionSpeedSet(0, 1.0f);
        opMotionSpeedSet(1, 1.0f);
        opMotionSpeedSet(2, 1.0f);
        opMotionSpeedSet(3, 1.0f);
        opMotionSpeedSet(4, 1.0f);
        opMotionSpeedSet(5, 1.0f);
        opMotionShiftSet(0, 0x28, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuVecCopyXYZ(&sp100, -850.0f, 0.0f, 3920.5f);
        HuVecCopyXYZ(&sp110, -300.0f, 0.0f, 2920.5f);
        opModelPosGet(1, &sp130.x, &sp130.y, &sp130.z);
        HuVecCopyXYZ(&sp110, (sp110.x - sp100.x) + sp130.x, 0.0f, (sp110.z - sp100.z) + sp130.z);
        opModelPosGet(1, &sp100.x, &sp100.y, &sp100.z);
        opModelPosGet(0xB, &sp120.x, &sp120.y, &sp120.z);
        opMotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        for (i = 0; i < 9; i++) {
            turnProgress = (f32)i * 0.125f;
            opModelRotSet(1, 0.0f, func_8011124C_opening(sp110.x - sp100.x, sp110.z - sp100.z, sp120.x - sp100.x, sp120.z - sp100.z, turnProgress), 0.0f);
            HuPrcVSleep();
        }
        opMotionShiftSet(1, 0x3A, 4, 4, (s16)2);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D0FU);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D0EU);
            opSleep(0x5A);
        }
        func_80107CA0_opening(0);
        HuPrcSleep(0x14);
        opMotionShiftSet(0, 0x33, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x46, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x55, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        frame = 0;
        do {
            temp_f20 = (f32)frame * 0.0625f;
            opModelPosGet(4, &sp110.x, &sp110.y, &sp110.z);
            opModelPosGet(0, &sp100.x, &sp100.y, &sp100.z);
            opModelRotGet(0, &sp130.x, &sp130.y, &sp130.z);
            opModelRotSet(0, 0.0f, func_80111490_opening(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            opModelPosGet(3, &sp110.x, &sp110.y, &sp110.z);
            opModelPosGet(2, &sp100.x, &sp100.y, &sp100.z);
            opModelRotGet(2, &sp130.x, &sp130.y, &sp130.z);
            opModelRotSet(2, 0.0f, func_80111490_opening(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            opModelPosGet(2, &sp110.x, &sp110.y, &sp110.z);
            opModelPosGet(3, &sp100.x, &sp100.y, &sp100.z);
            opModelRotGet(3, &sp130.x, &sp130.y, &sp130.z);
            opModelRotSet(3, 0.0f, func_80111490_opening(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            opModelPosGet(0, &sp110.x, &sp110.y, &sp110.z);
            opModelPosGet(4, &sp100.x, &sp100.y, &sp100.z);
            opModelRotGet(4, &sp130.x, &sp130.y, &sp130.z);
            opModelRotSet(4, 0.0f, func_80111490_opening(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            HuVecCopyXYZ(&sp110, -60.0f, 0.0f, 2775.0f);
            opModelPosGet(5, &sp100.x, &sp100.y, &sp100.z);
            opModelRotGet(5, &sp130.x, &sp130.y, &sp130.z);
            opModelRotSet(5, 0.0f, func_80111490_opening(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            HuPrcVSleep();
            frame++;
        } while (frame < 0x11);
        opMotionShiftSet(0, 0x28, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(0, 0x2D, 8, 8, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(1, 0x3A, 8, 8, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(2, 0x42, 8, 8, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(3, 0x4A, 8, 8, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(4, 0x52, 8, 8, (s16)2);
        HuPrcSleep(4);
        opMotionShiftSet(5, 0x5A, 8, 8, (s16)2);
        HuPrcSleep(0x14);
        func_80107CA0_opening(0);
        HuPrcSleep(0x1E);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D11U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D10U);
            opSleep(0x64);
        }
        HuPrcSleep(0xA);
        opDemoObjKill(0xB);
        opDemoObjKill(0xC);
        opModelKill(0xA);
        opModelKill(0x1B);
        opModelKill(6);
        opModelKill(7);
        opModelKill(8);
        opModelKill(0x2A);
        opModelKill(0x2B);
        opModelKill(0x2C);
        opModelKill(0x32);
        opModelKill(0x34);
        HuPrcSleep(3);
        func_80107CA0_opening(0);
        MBBackKill();
        MBBackLoad(0x21);
        func_800E92D4_shared_board();
        Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
        func_80110FB0_opening(&D_80114B88_opening[0], &D_80114B88_opening[1]);
        opModelCreate(0xC, 0xA0089, 0x6A9);
        opModelPosSet(0xC, 4340.0f, 4720.0f, 5925.0f);
        opModelScaleSet(0xC, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0xC, 2);
        opModelCreate(0xD, 0xF0001, 0x6A9);
        opModelPosSet(0xD, 4340.0f, 4720.0f, 5925.0f);
        opModelScaleSet(0xD, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0xD, 2);
        opModelCreate(0xE, 0xF0000, 0x6A9);
        opModelPosSet(0xE, 4340.0f, 4720.0f, 5925.0f);
        opModelScaleSet(0xE, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0xE, 1);
        temp_s1_2 = opModelIdGet(0xD);
        temp_v0_9 = opModelIdGet(0xE);
        func_8001C258_main(temp_v0_9, 0x4000, 0x4000);
        func_8001EF6C_main(temp_v0_9, temp_s1_2, "hook");
        if (storyMode != 0) {
            HuAudFXPlay(0x23A);
        }
        for (i = 1; i < 0x74; i++) {
            approachTarget = D_80114B88_opening;
            temp_f20 = (f32)i * 0.008333334f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            temp_f22 = 0.5f;
            temp_f24 = 0.0f;
            if (i == 0x21) {
                func_80107C70_opening(0);
                func_80107CD0_opening(0, 0x4D12U);
            }
            HuVecCopyXYZ(&sp140, 4340.0f, 4420.0f, 5925.0f);
            HuVecCopyXYZ(&sp150, approachTarget->x - 10.0f, approachTarget->y + 40.0f, approachTarget->z - 20.0f);
            sp150.y += (temp_f20 - temp_f22) * 1600.0f * (temp_f20 - temp_f22);
            // The normalized camera yaw is unused.
            approachYaw = func_80111164_opening(approachTarget->x, approachTarget->z, approachTarget[1].x, approachTarget[1].z);
            if (approachYaw < temp_f24) {
                approachYaw += 360.0f;
            }
            HuVecCopyXYZ(&sp160, ((sp150.x - sp140.x) * temp_f20) + sp140.x, ((sp150.y - sp140.y) * temp_f20) + sp140.y, ((sp150.z - sp140.z) * temp_f20) + sp140.z);
            temp_f20 = func_80111164_opening(approachTarget->x, approachTarget->z, sp150.x, sp150.z);
            opModelRotSet(0xC, 0.0f, temp_f20, 0.0f);
            opModelRotSet(0xD, 0.0f, temp_f20, 0.0f);
            opModelPosSet(0xC, sp160.x, sp160.y, sp160.z);
            opModelPosSet(0xD, sp160.x, sp160.y, sp160.z);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D13U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D12U);
            opSleep(0x28);
        }
        func_80107CA0_opening(0);
        opModelDispOff(0xC);
        opModelDispOff(0xD);
        opModelDispOff(0xE);
        MBBackKill();
        MBBackLoad(0x20);
        func_800E92D4_shared_board();
        Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
        func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
        opModelCreate(6, 0xF0006, 0x6A9);
        opModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        opModelPosSet(6, sp170.x, sp170.y, sp170.z);
        opModelScaleSet(6, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(6, 1);
        opMotionTimeSet(6, 0U);
        opModelDispOn(6);
        opModelCreate(0x2B, 0xF0006, 0x6A9);
        opModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        opModelPosSet(6, sp170.x, 150.0f, sp170.z);
        opModelScaleSet(0x2B, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x2B, 1);
        opMotionTimeSet(0x2B, 0U);
        opModelDispOff(0x2B);
        opModelCreate(0xF, 0xA0075, 0x6A9);
        opModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        opModelPosSet(0xF, sp170.x, sp170.y, sp170.z);
        opModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0xF, 1);
        opModelDispOff(0xF);
        opMotionCreate(0x68, 0xA0076, 0);
        opMotionCreate(0x69, 0xA0077, 0);
        opMotionCreate(0x6A, 0xA0078, 0);
        opMotionSet(0xF, 0x69, 1);
        opMotionTimeSet(0xF, 0U);
        opModelPosGet(4, &sp170.x, &sp170.y, &sp170.z);
        temp_f4_2 = sp170.x - 50.0f;
        sp170.x = temp_f4_2;
        temp_f2_2 = sp170.z + 25.0f;
        sp170.z = temp_f2_2;
        opModelPosSet(4, temp_f4_2, sp170.y, temp_f2_2);
        opModelPosSet(0x24, sp170.x, sp170.y, sp170.z);
        opModelDispOn(0xC);
        opModelDispOn(0xD);
        opModelDispOn(0xE);
        opMotionTimeSet(0xD, 0U);
        opMotionSet(0, 0x33, 2);
        opMotionSet(2, 0x46, 2);
        opMotionSet(3, 0x4D, 2);
        opMotionSet(4, 0x55, 2);
        opMotionSet(5, 0x5E, 2);
        sp1A0.x = sp1A0.y = sp1A0.z = 0.0f;
        opDemoShadowCreate(0x1D, 0.0f, 0.0f, 0.0f);
        opDemoShadowCreate(0x1E, sp1A0.x, sp1A0.y, sp1A0.z);
        opModelDispOff(0x1E);
        HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
        i = 0;
        temp_f0_5 = func_80111164_opening(sp180.x, sp180.z, sp190.x, sp190.z);
        angles.targetYaw = temp_f0_5;
        opModelRotSet(0xC, 0.0f, temp_f0_5, 0.0f);
        opModelRotSet(0xD, 0.0f, angles.targetYaw, 0.0f);
        do {
            temp_f22 = (f32)i * 0.004166667f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            opModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosSet(0x1D, sp1A0.x, 0.0f, sp1A0.z);
            temp_f26 = 0.5f;
            opModelScaleSet(0x1D, temp_f26, temp_f26, temp_f26);
            opModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            opModelScaleSet(0x1E, temp_f26, temp_f26, temp_f26);
            opModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            distance = 360.0f;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            opModelRotSet(0, 0.0f, angles.targetYaw, 0.0f);
            opModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_8 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_8;
            opModelRotSet(2, 0.0f, temp_f0_8, 0.0f);
            opModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_10 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_10;
            opModelRotSet(3, 0.0f, temp_f0_10, 0.0f);
            opModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_12 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_12;
            opModelRotSet(4, 0.0f, temp_f0_12, 0.0f);
            opModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_14 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_14;
            opModelRotSet(5, 0.0f, temp_f0_14, 0.0f);
            HuPrcVSleep();
            if (i == 0x2C) {
                opMotionShiftSet(0, 0x35, 8, 0x10, (s16)2);
                opMotionShiftSet(2, 0x47, 8, 0x10, (s16)2);
                opMotionShiftSet(3, 0x4F, 8, 0x10, (s16)2);
                opMotionShiftSet(4, 0x57, 8, 0x10, (s16)2);
                opMotionShiftSet(5, 0x60, 8, 0x10, (s16)2);
            }
            i += 2;
        } while (i < 0x68);
        func_8001C258_main(opModelIdGet(0xE), 0x4000, 0);
        opModelRotGet(0xD, &sp1B0.x, &sp1B0.y, &sp1B0.z);
        opModelRotSet(0xE, sp1B0.x, sp1B0.y, sp1B0.z);
        temp_f22 = sp1B0.y;
        opModelPosGet(0xD, &sp1B0.x, &sp1B0.y, &sp1B0.z);
        sp1B0.x = (f32)((f64)sp1B0.x + ((f64)sindf(temp_f22) * 142.0));
        sp1B0.y += -108.0f;
        temp_f2_3 = (f32)((f64)sp1B0.z + ((f64)cosdf(temp_f22) * 142.0));
        sp1B0.z = temp_f2_3;
        opModelPosSet(0xE, sp1B0.x, sp1B0.y, temp_f2_3);
        opModelDispOff(0xD);
        opMotionShiftSet(0, 0x33, 8, 8, (s16)2);
        opMotionShiftSet(2, 0x46, 8, 8, (s16)2);
        opMotionShiftSet(3, 0x4D, 8, 8, (s16)2);
        opMotionShiftSet(4, 0x55, 8, 8, (s16)2);
        opMotionShiftSet(5, 0x5E, 8, 8, (s16)2);
        opMotionSpeedSet(0, 0.3f);
        opMotionSpeedSet(2, 0.3f);
        opMotionSpeedSet(3, 0.3f);
        opMotionSpeedSet(4, 0.3f);
        opMotionSpeedSet(5, 0.3f);
        opModelDispOn(0x1E);
        opModelRotGet(0xE, &angles.rot.x, &angles.rot.y, &angles.rot.z);
        i = 0x68;
        var_s1 = 0;
        do {
            if (var_s1 == 0x14) {
                func_80106DD0_opening(0xE, 1);
                if (storyMode != 0) {
                    HuAudFXPlay(0x23B);
                }
            }
            temp_f22 = (f32)var_s1 * 0.05f;
            temp_f22 = temp_f22 > 1.0f ? 1.0f : temp_f22;
            HuVecCopyXYZ(&sp1A0, sp1B0.x, (temp_f22 * temp_f22 * (97.5f - sp1B0.y)) + sp1B0.y, sp1B0.z);
            opModelPosSet(0xE, sp1A0.x, sp1A0.y, sp1A0.z);
            temp_f0_15 = func_80111490_opening(angles.rot.y, -(D_80114B70_opening[0].x - sp1A0.x), -(D_80114B70_opening[0].z - sp1A0.z), temp_f22);
            angles.rot.y = temp_f0_15;
            opModelRotSet(0xE, 0.0f, temp_f0_15, 0.0f);
            opModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            opModelScaleSet(0x1E, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f);
            temp_f22 = (f32)i * 0.004166667f;
            temp_f20 = (f32)(i - 0x68) * 0.007352941f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            sp190.y += temp_f20 * 800.0f * temp_f20;
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            opModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosSet(0x1D, sp1A0.x, 0.0f, sp1A0.z);
            opModelScaleSet(0x1D, 0.5f, 0.5f, 0.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * 0.5f) + sp180.x, ((sp190.y - sp180.y) * 0.5f) + sp180.y, ((sp190.z - sp180.z) * 0.5f) + sp180.z);
            opModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_18 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_18;
            opModelRotSet(0, 0.0f, temp_f0_18, 0.0f);
            opModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_20 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_20;
            opModelRotSet(2, 0.0f, temp_f0_20, 0.0f);
            opModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_22 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_22;
            opModelRotSet(3, 0.0f, temp_f0_22, 0.0f);
            opModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_24 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_24;
            opModelRotSet(4, 0.0f, temp_f0_24, 0.0f);
            opModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            i += 2;
            temp_f0_26 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_26;
            opModelRotSet(5, 0.0f, temp_f0_26, 0.0f);
            var_s1 += 1;
            HuPrcVSleep();
        } while (i < 0xA0);
        i = 0xA0;
        do {
            temp_f22 = (f32)var_s1 * 0.05f;
            if (var_s1 == 0x14) {
                func_80106DD0_opening(0xE, 1);
                if (storyMode != 0) {
                    HuAudFXPlay(0x23B);
                }
            }
            if (temp_f22 > 1.0f) {
                temp_f22 = 1.0f;
            }
            HuVecCopyXYZ(&sp1A0, sp1B0.x, (temp_f22 * temp_f22 * (97.5f - sp1B0.y)) + sp1B0.y, sp1B0.z);
            opModelPosSet(0xE, sp1A0.x, sp1A0.y, sp1A0.z);
            temp_f0_27 = func_80111490_opening(angles.rot.y, -(D_80114B70_opening[0].x - sp1A0.x), -(D_80114B70_opening[0].z - sp1A0.z), temp_f22);
            angles.rot.y = temp_f0_27;
            opModelRotSet(0xE, 0.0f, temp_f0_27, 0.0f);
            opModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            opModelScaleSet(0x1E, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f);
            temp_f22 = (f32)i * 0.004166667f;
            temp_f20 = (f32)(i - 0x68) * 0.007352941f;
            ascentHeight = 800;
            HuVecCopyXYZ(&sp180, ascentHeight, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            sp190.y += temp_f20 * ascentHeight * temp_f20;
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            opModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            opModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_30 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_30;
            opModelRotSet(0, 0.0f, temp_f0_30, 0.0f);
            opModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_32 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_32;
            opModelRotSet(2, 0.0f, temp_f0_32, 0.0f);
            opModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_34 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_34;
            opModelRotSet(3, 0.0f, temp_f0_34, 0.0f);
            opModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_36 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 9.0f);
            angles.targetYaw = temp_f0_36;
            opModelRotSet(4, 0.0f, temp_f0_36, 0.0f);
            opModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = func_80111164_opening(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            i += 2;
            temp_f0_38 = func_801111AC_opening(angles.currentYaw, angles.targetYaw, 9.0f);
            angles.targetYaw = temp_f0_38;
            opModelRotSet(5, 0.0f, temp_f0_38, 0.0f);
            var_s1 += 1;
            HuPrcVSleep();
        } while (i < 0xF1);
        opMotionShiftSet(0, 0x33, 4, 4, (s16)2);
        opMotionSpeedSet(0, 1.0f);
        opMotionShiftSet(2, 0x46, 4, 4, (s16)2);
        opMotionSpeedSet(2, 1.0f);
        opMotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        opMotionSpeedSet(3, 1.0f);
        opMotionShiftSet(4, 0x55, 4, 4, (s16)2);
        opMotionSpeedSet(4, 1.0f);
        opMotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        opMotionSpeedSet(5, 1.0f);
        for (i = 0; i < 0x11; i++) {
            temp_f22 = (f32)i * 0.0625f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * 0.5f) + sp180.x, ((sp190.y - sp180.y) * 0.5f) + sp180.y, ((sp190.z - sp180.z) * 0.5f) + sp180.z);
            opModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            opModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
            opModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(0, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_39 = func_80111490_opening(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_39;
            opModelRotSet(0, 0.0f, temp_f0_39, 0.0f);
            opModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(2, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_40 = func_80111490_opening(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_40;
            opModelRotSet(2, 0.0f, temp_f0_40, 0.0f);
            opModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(3, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_41 = func_80111490_opening(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_41;
            opModelRotSet(3, 0.0f, temp_f0_41, 0.0f);
            temp_f22 = 2.0f * temp_f22 > 1.0f ? 1.0f : 2.0f * temp_f22;
            opModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(4, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_42 = func_80111490_opening(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_42;
            opModelRotSet(4, 0.0f, temp_f0_42, 0.0f);
            opModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            opModelRotGet(5, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_43 = func_80111490_opening(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_43;
            opModelRotSet(5, 0.0f, temp_f0_43, 0.0f);
            HuPrcVSleep();
        }
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        opMotionShiftSet(0, 0x2E, 4, 4, (s16)0);
        HuPrcSleep(0x10);
        opModelDispOn(6);
        temp_s1_3 = opModelIdGet(0);
        temp_v0_10 = opModelIdGet(6);
        func_8001C258_main(temp_v0_10, 0x4000, 0x4000);
        func_8001EF6C_main(temp_v0_10, temp_s1_3, "item_hook");
        opModelRotGet(0, &sp208.x, &sp208.y, &sp208.z);
        opModelPosGet(0, &sp1F8.x, &sp1F8.y, &sp1F8.z);
        for (i = 1; i < 9; i++) {
            temp_f0 = (f32)i * 0.125f;
            sp208.y = func_80111490_opening(sp208.y, D_80114B70_opening[0].x - sp1F8.x, D_80114B70_opening[0].z - sp1F8.z, temp_f0);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x275);
        }
        opMotionShiftSet(2, 0x43, 8, 8, (s16)2);
        opMotionShiftSet(3, 0x4E, 8, 8, (s16)2);
        opMotionShiftSet(4, 0x56, 8, 8, (s16)0);
        opMotionEndWait(4);
        opMotionShiftSet(4, 0x50, 8, 8, (s16)2);
        func_80107C70_opening(0);
        func_80107CD0_opening(0, 0x4D14U);
        opMotionEndWait(0);
        opMotionShiftSet(0, 0x2F, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x59, 8, 8, (s16)2);
        opModelPosGet(5, &sp1D8.x, &sp1D8.y, &sp1D8.z);
        opModelPosGet(0xE, &sp1E8.x, &sp1E8.y, &sp1E8.z);
        temp_f24 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, sp1E8.x, sp1E8.z);
        i = 0;
        temp_f20 = cosdf(temp_f24);
        temp_f0_44 = sindf(temp_f24);
        temp_f22 = 60.0f;
        temp_f20 = ((temp_f20 * temp_f22) + sp1E8.x + (temp_f0_44 * temp_f22)) - 30.0f;
        sp1E8.x = temp_f20;
        temp_f20 = sindf(temp_f24);
        temp_f0_44 = cosdf(temp_f24);
        temp_f0 = temp_f22 * temp_f20;
        temp_f20 = temp_f0;
        sp1E8.z = (sp1E8.z - temp_f20) + (temp_f0_44 * temp_f22);
        sp1E8.y = sp1D8.y;
        opModelRotGet(5, &sp208.x, &sp208.y, &sp208.z);
        do {
            temp_f20 = (f32)i;
            temp_f0 = temp_f20 * 0.125f;
            HuVecCopyXYZ(&sp1F8, ((sp1E8.x - sp1D8.x) * temp_f0) + sp1D8.x, ((sp1E8.y - sp1D8.y) * temp_f0) + sp1D8.y, ((sp1E8.z - sp1D8.z) * temp_f0) + sp1D8.z);
            opModelPosSet(5, sp1F8.x, sp1F8.y, sp1F8.z);
            opModelPosSet(0x25, sp1F8.x, sp1F8.y, sp1F8.z);
            if (i < 5) {
                temp_f0 = temp_f20 * 0.25f;
                opModelRotSet(5, 0.0f, func_80111490_opening(sp208.y, sp1E8.x - sp1F8.x, (sp1E8.z + 10.0f) - sp1F8.z, temp_f0), 0.0f);
            }
            i += 1;
            HuPrcVSleep();
        } while (i < 9);
        opModelPosGet(5, &sp1D8.x, &sp1D8.y, &sp1D8.z);
        opModelPosGet(0xE, &sp1E8.x, &sp1E8.y, &sp1E8.z);
        opModelRotGet(5, &sp208.x, &sp208.y, &sp208.z);
        for (i = 0; i < 8; i++) {
            temp_f20 = (f32)i * 0.125f;
            opModelRotSet(5, 0.0f, func_80111490_opening(sp208.y, sp1E8.x - sp1F8.x, (sp1E8.z + 10.0f) - sp1F8.z, temp_f20), 0.0f);
            HuPrcVSleep();
        }
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(8);
        opMotionShiftSet(5, 0x5B, 4, 4, (s16)0);
        HuPrcSleep(8);
        opModelDispOn(0xF);
        temp_s1_4 = opModelIdGet(5);
        temp_v0_11 = opModelIdGet(0xF);
        func_8001C258_main(temp_v0_11, 0x4000, 0x4000);
        func_8001EF6C_main(temp_v0_11, temp_s1_4, "item_hook");
        for (i = 1; i < 9; i++) {
            HuPrcVSleep();
        }
        opMotionEndWait(5);
        if (storyMode != 0) {
            HuAudFXPlay(0x27A);
        }
        opMotionShiftSet(5, 0x5F, 4, 4, (s16)2);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D15U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D14U);
            opSleep(0x50);
        }
        func_80107CA0_opening(0);
        HuPrcSleep(0x32);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D17U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D16U);
            opSleep(0x3C);
        }
        func_800E9344_shared_board(10.0f, 10000.0f);
        opModelCreate(0x1C, 0xF0007, 0x2A9);
        opModelPosSet(0x1C, -580.0f, 60.0f, 2580.0f);
        opModelPosGet(0, &sp238.x, &sp238.y, &sp238.z);
        opModelRotSet(0x1C, 0.0f, func_80111164_opening(sp238.x, sp238.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
        opModelScaleSet(0x1C, 1.0f, 1.0f, 1.0f);
        opModelDispOff(0x1C);
        opMotionShiftSet(1, 0x3C, 4, 4, (s16)0);
        HuPrcSleep(4);
        opModelDispOn(0x1C);
        func_80106DD0_opening(0x1C, 1);
        opMotionTimeSet(0x1C, 0U);
        if (storyMode != 0) {
            HuAudFXPlay(0x236);
        }
        opMotionEndWait(1);
        opMotionShiftSet(1, 0x38, 4, 4, (s16)2);
        opModelRotGet(0, &sp228.x, &characterAngles[0], &sp228.z);
        opModelRotGet(1, &sp228.x, &characterAngles[1], &sp228.z);
        opModelRotGet(2, &sp228.x, &characterAngles[2], &sp228.z);
        opModelRotGet(3, &sp228.x, &characterAngles[3], &sp228.z);
        opModelRotGet(4, &sp228.x, &characterAngles[4], &sp228.z);
        opModelRotGet(5, &sp228.x, &characterAngles[5], &sp228.z);
        opModelPosGet(0xB, &sp228.x, &sp228.y, &sp228.z);
        opMotionShiftSet(2, 0x46, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x55, 4, 4, (s16)2);
        var_s3 = 0;
        do {
            temp_f20 = (f32)var_s3;
            temp_f20 *= 0.125f;
            opModelPosGet(0, &sp218.x, &sp218.y, &sp218.z);
            opModelRotSet(0, 0.0f, func_80111490_opening(characterAngles[0], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            opModelPosGet(2, &sp218.x, &sp218.y, &sp218.z);
            opModelRotSet(2, 0.0f, func_80111490_opening(characterAngles[2], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            opModelPosGet(3, &sp218.x, &sp218.y, &sp218.z);
            opModelRotSet(3, 0.0f, func_80111490_opening(characterAngles[3], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            opModelPosGet(4, &sp218.x, &sp218.y, &sp218.z);
            opModelRotSet(4, 0.0f, func_80111490_opening(characterAngles[4], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            opModelPosGet(5, &sp218.x, &sp218.y, &sp218.z);
            opModelRotSet(5, 0.0f, func_80111490_opening(characterAngles[5], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            temp_f20 *= 7.5f;
            temp_f0 = sp218.x - temp_f20;
            opModelPosSet(5, temp_f0, sp218.y, sp218.z);
            var_s3 += 1;
            HuPrcVSleep();
        } while (var_s3 < 9);
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionEndWait(0x1C);
        opModelKill(0x2D);
        opModelKill(0x39);
        opModelKill(0x41);
        opModelKill(0x42);
        opModelKill(0x43);
        opModelKill(0x49);
        opModelKill(0x4A);
        opModelKill(0x4E);
        opModelKill(0x52);
        opModelKill(0x56);
        opModelKill(0x5A);
        opModelKill(0x35);
        opModelKill(0x3D);
        opModelKill(0x46);
        opModelKill(0x4D);
        opModelKill(0x55);
        opModelKill(0x5E);
        HuPrcSleep(3);
        if (storyMode != 0) {
            HuAudFXPlay(0x23C);
        }
        opWipeWhiteOutCreate(0xF, 0x14);
        if (storyMode != 0) {
            HuAudSeqFadeOut(0x2E);
        }
        HuPrcSleep(0x14);
        HuPrcSleep(0x14);
        opModelPosGet(5, &sp268.x, &sp268.y, &sp268.z);
        opModelPosSet(5, sp268.x + 60.0f, sp268.y, sp268.z);
        opModelPosSet(0x25, sp268.x + 60.0f, sp268.y, sp268.z);
        opMotionCreate(0x30, 0xF000F, 0);
        opMotionCreate(0x44, 0x70025, 0);
        HuPrcSleep(3);
        opMotionCreate(0x53, 0xF0017, 0);
        opMotionCreate(0x5C, 0xF001A, 0);
        HuPrcSleep(3);
        opModelKill(0x1C);
        opModelKill(0x1D);
        opModelKill(0x1E);
        MBBackKill();
        MBBackLoad(0x22);
        func_800E92D4_shared_board();
        Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
        func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
        opModelKill(0xC);
        opModelKill(0xD);
        opModelKill(0xE);
        opModelKill(9);
        opModelDispOff(0xB);
        HuPrcSleep(3);
        opMotionCreate(0x31, 0x2007A, 0);
        opMotionCreate(0x3B, 0xF0013, 0);
        opMotionCreate(0x45, 0x7007A, 0);
        opMotionCreate(0x4B, 0x40003, 0);
        opMotionCreate(0x4C, 0x4007A, 0);
        opMotionCreate(0x54, 0x5007A, 0);
        opMotionCreate(0x5D, 0x6007A, 0);
        opModelCreate(0x12, 0xF0008, 0x6A9);
        opModelPosSet(0x12, -130.99998f, 0.0f, 3250.0f);
        opModelRotSet(0x12, 0.0f, 25.0f, 0.0f);
        opModelScaleSet(0x12, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x12, 1);
        temp_v0_12 = func_8001D33C_main(opModelIdGet(0x12), "tree_kage");
        func_80088700_main(temp_v0_12->unk58, 0.0f, 0.0f, 0.0f);
        temp_f24 = 0.0f;
        temp_v0_12->scale.x = temp_v0_12->scale.y = temp_v0_12->scale.z = temp_f24;
        temp_v0_12->baseScale.x = temp_v0_12->baseScale.y = temp_v0_12->baseScale.z = temp_f24;
        opModelPosGet(3, &sp278.x, &sp278.y, &sp278.z);
        opModelRotGet(3, &sp2A8.x, &sp2A8.y, &sp2A8.z);
        temp_f22 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, sp278.x, sp278.z);
        temp_f20 = sindf(temp_f22);
        temp_f0_45 = cosdf(temp_f22);
        temp_f20 *= 100.0f;
        temp_f26 = -160.0f;
        temp_f20 += temp_f0_45 * temp_f26;
        temp_f20 += sp278.x;
        treePos1.x = temp_f20;
        treePos1.y = temp_f24;
        temp_f20 = cosdf(temp_f22);
        temp_f0_45 = sindf(temp_f22);
        distance = -100.0f;
        temp_f20 = (temp_f20 * distance) + (temp_f0_45 * temp_f26) + sp278.z;
        treePos1.z = temp_f20;
        opModelPosSet(0x12, treePos1.x, treePos1.y, temp_f20);
        opModelPosGet(3, &sp278.x, &sp278.y, &sp278.z);
        opModelPosGet(0x12, &sp288.x, &sp288.y, &sp288.z);
        opModelRotSet(3, temp_f24, func_80111164_opening(sp278.x, sp278.z, sp288.x, sp288.z), temp_f24);
        func_80112BA0_opening(0, 3, 0x4B, 0x48, 0, 0x26);
        func_80112D30_opening(1, 0x12, 8, 0x33);
        opModelCreate(0x13, 0xF0008, 0x6A9);
        opModelPosSet(0x13, 344.0f, temp_f24, 2900.0f);
        opModelRotSet(0x13, temp_f24, 25.0f, temp_f24);
        opModelScaleSet(0x13, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x13, 1);
        opModelPosGet(1, &sp2B8.x, &sp2B8.y, &sp2B8.z);
        opModelRotGet(1, &sp2E8.x, &sp2E8.y, &sp2E8.z);
        temp_f22 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, sp2B8.x, sp2B8.z);
        temp_f20 = sindf(temp_f22);
        temp_f0_46 = cosdf(temp_f22);
        temp_f20 = (temp_f20 * 125.0f) + (temp_f0_46 * distance) + sp2B8.x;
        treePos2.x = temp_f20;
        treePos2.y = temp_f24;
        temp_f20 = cosdf(temp_f22);
        temp_f0_46 = sindf(temp_f22);
        temp_f20 = (temp_f20 * -125.0f) + (temp_f0_46 * distance) + sp2B8.z;
        treePos2.z = temp_f20;
        opModelPosSet(0x13, treePos2.x, treePos2.y, temp_f20);
        opModelPosGet(1, &sp2B8.x, &sp2B8.y, &sp2B8.z);
        opModelPosGet(0x13, &sp2C8.x, &sp2C8.y, &sp2C8.z);
        opModelRotSet(1, temp_f24, func_80111164_opening(sp2B8.x, sp2B8.z, sp2C8.x, sp2C8.z), temp_f24);
        func_80112BA0_opening(2, 1, 0x3B, 0x38, 0x2C, 0x28);
        func_80112D30_opening(3, 0x13, 0, 0x58);
        func_8001C258_main(opModelIdGet(0xF), 0x4000, 0);
        opModelDispOff(0xF);
        func_8001C258_main(opModelIdGet(6), 0x4000, 0);
        opModelKill(6);
        opModelPosGet(0xF, &sp2F8.x, &sp2F8.y, &sp2F8.z);
        opDemoShadowCreate(0x27, sp2F8.x, sp2F8.y, sp2F8.z);
        temp_f2_6 = (1200.0f - sp2F8.y) * 0.00083333335f;
        opModelScaleSet(0x27, temp_f2_6, 1.0f, temp_f2_6);
        opModelDispOff(0x27);
        opMotionCreate(0x6B, 0xF001C, 0);
        func_80107CA0_opening(0);
        opMotionSet(0, 0x30, 2);
        opMotionSet(2, 0x44, 2);
        opMotionSet(3, 0x48, 2);
        opMotionSet(4, 0x53, 2);
        opMotionSet(5, 0x5C, 2);
        opWipeWhiteInCreate(0xF, 0x14);
        HuPrcSleep(0x14);
        if (storyMode != 0) {
            HuAudSeqPlay(0x3B);
        }
        func_80107CD0_opening(0, 0x4D18U);
        HuPrcSleep(0x28);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D19U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D18U);
            opSleep(0x78);
        }
        func_80107CA0_opening(0);
        opModelDispOn(0xF);
        opModelDispOn(0x27);
        opMotionShiftSet(0xF, 0x69, 4, 4, (s16)2);
        func_801110AC_opening(&cameraPos1.x, &cameraPos1.y, &cameraPos1.z, &cameraAt1.x, &cameraAt1.y, &cameraAt1.z);
        temp_f26 = func_80111164_opening(cameraAt1.x, cameraAt1.z, cameraPos1.x, cameraPos1.z);
        sp328.y = 150.0f;
        sp328.x = (sindf(temp_f26) * -600.0f) + cameraPos1.x;
        sp328.z = (cosdf(temp_f26) * -600.0f) + cameraPos1.z;
        HuVecCopy3F(&sp338, &sp328);
        sp328.y += 900.0f;
        opModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
        if (storyMode != 0) {
            HuAudFXPlay(0x23D);
        }
        i = 0;
        do {
            temp_f20 = (f32)i * 0.05f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp358, (temp_f20 * (sp338.x - sp328.x)) + sp328.x, (temp_f20 * (sp338.y - sp328.y)) + sp328.y, (temp_f20 * (sp338.z - sp328.z)) + sp328.z);
            opModelPosSet(0xF, sp358.x, sp358.y, sp358.z);
            opModelPosSet(0x27, sp358.x, 0.0f, sp358.z);
            temp_f2_7 = (1200.0f - sp358.y) * 0.00083333335f;
            opModelScaleSet(0x27, temp_f2_7, 1.0f, temp_f2_7);
            opModelRotSet(0xF, 0.0f, func_80111164_opening(sp358.x, sp358.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
            HuPrcVSleep();
            i += 1;
        } while (i < 0x15);
        HuPrcSleep(8);
        opDemoGuideInEffCreate(4, 0xF);
        opDemoObjKill(0);
        opDemoObjKill(1);
        opDemoObjKill(2);
        opDemoObjKill(3);
        opModelPosGet(0xF, &sp358.x, &sp358.y, &sp358.z);
        opModelRotGet(0, &sp338.x, &characterAngles2[0], &sp338.z);
        opModelRotGet(1, &sp338.x, &characterAngles2[1], &sp338.z);
        opModelRotGet(2, &sp338.x, &characterAngles2[2], &sp338.z);
        opModelRotGet(3, &sp338.x, &characterAngles2[3], &sp338.z);
        opModelRotGet(4, &sp338.x, &characterAngles2[4], &sp338.z);
        opModelRotGet(5, &sp338.x, &characterAngles2[5], &sp338.z);
        opMotionShiftSet(0, 0x33, 4, 4, (s16)2);
        opMotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x46, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x55, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        for (i = 0; i < 9; i++) {
            temp_f20 = (f32)i * 0.125f;
            opModelPosGet(0, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(0, 0.0f, func_80111490_opening(characterAngles2[0], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            opModelPosGet(1, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(1, 0.0f, func_80111490_opening(characterAngles2[1], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            opModelPosGet(2, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(2, 0.0f, func_80111490_opening(characterAngles2[2], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            opModelPosGet(3, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(3, 0.0f, func_80111490_opening(characterAngles2[3], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            opModelPosGet(4, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(4, 0.0f, func_80111490_opening(characterAngles2[4], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            opModelPosGet(5, &sp328.x, &sp328.y, &sp328.z);
            opModelRotSet(5, 0.0f, func_80111490_opening(characterAngles2[5], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            HuPrcVSleep();
        }
        opMotionShiftSet(0, 0x28, 4, 4, (s16)2);
        opMotionShiftSet(1, 0x38, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(0x10);
        opMotionShiftSet(0xF, 0x6A, 4, 4, (s16)0);
        HuPrcSleep(0x11);
        if (storyMode != 0) {
            HuAudFXPlay(0x2A8);
        }
        HuPrcSleep(0x12);
        if (storyMode != 0) {
            func_8004AC5C_main(0x286, 0);
            func_8004AC5C_main(0x286, 1);
            func_8004AC5C_main(0x286, 2);
        }
        opMotionShiftSet(0, 0x31, 4, 4, (s16)0);
        opMotionShiftSet(1, 0x3C, 4, 4, (s16)0);
        opMotionShiftSet(2, 0x45, 4, 4, (s16)0);
        HuPrcSleep(3);
        if (storyMode != 0) {
            func_8004AC5C_main(0x286, 3);
            func_8004AC5C_main(0x286, 4);
        }
        opMotionShiftSet(3, 0x4C, 4, 4, (s16)0);
        opMotionShiftSet(4, 0x54, 4, 4, (s16)0);
        HuPrcSleep(1);
        if (storyMode != 0) {
            func_8004AC5C_main(0x286, 5);
        }
        opMotionShiftSet(5, 0x5D, 4, 4, (s16)0);
        opMotionEndWait(0xF);
        opMotionShiftSet(0xF, 0x68, 4, 4, (s16)2);
        opMotionEndWait(0);
        opMotionShiftSet(0, 0x28, 4, 4, (s16)2);
        opMotionShiftSet(1, 0x38, 4, 4, (s16)2);
        opMotionShiftSet(2, 0x40, 4, 4, (s16)2);
        opMotionEndWait(3);
        opMotionShiftSet(3, 0x48, 4, 4, (s16)2);
        opMotionShiftSet(4, 0x50, 4, 4, (s16)2);
        opMotionEndWait(5);
        opMotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(0x14);
        opDemoObjKill(4);
        opMotionShiftSet(0, 0x33, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        opMotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        opMotionShiftSet(2, 0x46, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        opMotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        opMotionShiftSet(4, 0x55, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        opMotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        opMotionSpeedSet(0, 0.6f);
        HuVecCopyXYZ(&sp338, -325.0f, 160.0f, 2600.0f);
        opModelPosGet(0xF, &sp328.x, &sp328.y, &sp328.z);
        opModelPosGet(3, &sp338.x, &sp338.y, &sp338.z);
        sp338.y = 160.0f;
        opMotionShiftSet(0xF, 0x6B, 8, 8, (s16)2);
        func_80017790_main(opModelIdGet(0xF), 2, 0xF, 0xA0081);
        i = 0;
        do {
            temp_f20 = (f32)i * 0.016666668f;
            if (i == 0x3C) {
            } else if (i == 0x36) {
                opDemoOutEffCreate(3, 3);
            } else if (i == 0x2D) {
                opDemoOutEffCreate(2, 2);
            } else if (i == 0x24) {
                opDemoOutEffCreate(0, 0);
            } else if (i == 0x1B) {
                opDemoOutEffCreate(5, 5);
            } else if (i == 0x12) {
                opDemoOutEffCreate(4, 4);
            } else if (i == 9) {
                if (storyMode != 0) {
                    HuAudFXPlay(0x23E);
                }
                opDemoOutEffCreate(1, 1);
            }
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp348, (temp_f20 * (sp338.x - sp328.x)) + sp328.x, (temp_f20 * (sp338.y - sp328.y)) + sp328.y, (temp_f20 * (sp338.z - sp328.z)) + sp328.z);
            i += 1;
            temp_f26 = func_80111164_opening(D_80114B70_opening[0].x, D_80114B70_opening[0].z, sp328.x, sp328.z);
            temp_f0_49 = sindf(temp_f20 * 90.0f) - 0.5f;
            temp_f24 = ((-temp_f0_49 * temp_f0_49) + 0.25f) * 4.0f;
            temp_f20 = sindf(temp_f26);
            temp_f0_49 = cosdf(temp_f26);
            temp_f22 = 20.0f;
            temp_f22 = temp_f24 * temp_f22;
            temp_f22 *= 5.0f;
            temp_f0 = temp_f22 * temp_f20;
            temp_f20 = temp_f0;
            temp_f20 += temp_f0_49 * 300.0f;
            temp_f0 = temp_f24 * temp_f20;
            temp_f20 = temp_f0;
            temp_f20 += sp348.x;
            sp348.x = temp_f20;
            sp348.y = 150.0f;
            temp_f20 = cosdf(temp_f26);
            temp_f22 = -temp_f22 * temp_f20 + sindf(temp_f26) * 300.0f;
            temp_f24 = temp_f24 * temp_f22 + sp348.z;
            sp348.z = temp_f24;
            opModelPosSet(0xF, sp348.x, sp348.y, temp_f24);
            opModelPosSet(0x27, sp348.x, 0.0f, sp348.z);
            temp_f2_8 = (1200.0f - sp348.y) * 0.00083333335f;
            opModelScaleSet(0x27, temp_f2_8, 1.0f, temp_f2_8);
            opModelRotSet(0xF, 0.0f, func_80111164_opening(sp348.x, sp348.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z), 0.0f);
            opModelPosGet(0, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(0, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            opModelPosGet(1, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(1, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            opModelPosGet(2, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(2, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            opModelPosGet(3, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(3, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            opModelPosGet(4, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(4, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            opModelPosGet(5, &sp358.x, &sp358.y, &sp358.z);
            opModelRotSet(5, 0.0f, func_80111164_opening(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            HuPrcVSleep();
        } while (i < 0x3D);
        opMotionShiftSet(0xF, 0x68, 8, 8, (s16)2);
        HuPrcSleep(0x28);
        opDemoObjKill(0);
        opDemoObjKill(1);
        opDemoObjKill(2);
        opDemoObjKill(3);
        opDemoObjKill(4);
        opDemoObjKill(5);
        opModelKill(0);
        opModelKill(1);
        opModelKill(2);
        opModelKill(3);
        opModelKill(4);
        opModelKill(5);
        opModelKill(0x28);
        opModelKill(0x29);
        opModelKill(0x2E);
        opModelKill(0x2F);
        opModelKill(0x30);
        opModelKill(0x31);
        opModelKill(0x33);
        opModelKill(0x38);
        opModelKill(0x3A);
        opModelKill(0x3B);
        opModelKill(0x3C);
        opModelKill(0x3D);
        opModelKill(0x40);
        opModelKill(0x44);
        opModelKill(0x46);
        opModelKill(0x48);
        opModelKill(0x4B);
        opModelKill(0x4C);
        opModelKill(0x4D);
        opModelKill(0x50);
        opModelKill(0x51);
        opModelKill(0x53);
        opModelKill(0x54);
        opModelKill(0x55);
        opModelKill(0x58);
        opModelKill(0x59);
        opModelKill(0x5B);
        opModelKill(0x5C);
        opModelKill(0x5D);
        opModelKill(0x5F);
        opModelKill(0x5E);
        opModelKill(0x69);
        opModelKill(0x6A);
        opModelKill(0xC);
        opModelKill(0xD);
        opModelKill(0x21);
        opModelKill(0x22);
        opModelKill(0x23);
        opModelKill(0x24);
        opModelKill(0x25);
        HuPrcSleep(8);
        D_800CD280_main = 1;
        opWipeWhiteOutCreate(0xF, 0x14);
        HuPrcSleep(0x14);
        MBBackKill();
        HuVecCopy3F(&sp3A8, &D_80114BA0_opening);
        HuVecCopy3F(&sp3B8, &D_80114BAC_opening);
        HuVecCopyXYZ(&sp398, sp3A8.x - sp3B8.x, sp3A8.y - sp3B8.y, sp3A8.z - sp3B8.z);
        temp_f20 = cosdf(315.0f);
        temp_f20 = (temp_f20 * sp398.x) + sp3B8.x + (sindf(315.0f) * sp398.z);
        sp388.x = temp_f20;
        sp388.y = sp3B8.y + sp398.y;
        temp_f20 = sindf(315.0f);
        cameraCosine = cosdf(315.0f);
        temp_f20 *= sp398.x;
        sp388.z = (sp3B8.z - temp_f20) + (cameraCosine * sp398.z);
        func_801110F0_opening(sp388.x, sp388.y, sp388.z, sp3B8.x, sp3B8.y, sp3B8.z);
        func_80110FB0_opening(&sp388, &D_80114BAC_opening);
        Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);
        opModelKill(0xF);
        opModelDispOff(0x27);
        opModelKill(0x68);
        HuPrcSleep(3);
        opSprCreate(0, 0xF001D);
        opSprPosSet(0, 0x78, 0x5C);
        opSprDispOff(0);
        HuPrcSleep(3);
        opModelCreate(0x10, 0x1D000A, 0x6A9);
        opModelPosSet(0x10, 0.0f, 0.0f, 0.0f);
        opModelRotSet(0x10, 270.0f, 180.0f, 0.0f);
        opModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
        opMotionTimeSet(0x10, 0U);
        opMotionFlagSet(0x10, 1);
        opModelDispOff(0x10);
        opModelCreate(0x14, 0xD000A, 0x2002A9);
        opModelPosSet(0x14, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x14, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x14, 0U);
        opMotionFlagSet(0x14, 1);
        opModelCreate(9, 0xD0000, 0x2002A9);
        opModelPosSet(9, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(9, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(9, 0U);
        opMotionFlagSet(9, 1);
        opModelDispOff(9);
        opModelCreate(0x15, 0xD0001, 0x2A9);
        opModelPosSet(0x15, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x15, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x15, 0U);
        opMotionFlagSet(0x15, 1);
        opModelCreate(0x16, 0xD0002, 0x2A9);
        opModelPosSet(0x16, 0.0f, 0.0f, -585.0f);
        opModelScaleSet(0x16, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x16, 0U);
        opMotionFlagSet(0x16, 1);
        temp_v0_13 = opModelIdGet(0x16);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "mario")->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "luigi")->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "peach")->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "yoshi")->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "wario")->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(func_8001D33C_main(temp_v0_13, "donkey")->unk58, 0.0f, -4000.0f, 0.0f);
        HuVecCopyXYZ(&sp3C8, 0.0f, 0.0f, -200.0f);
        sp3C8.z -= 8.0f;
        opModelCreate(0x17, 0xD0003, 0x2A9);
        opModelPosSet(0x17, sp3C8.x, sp3C8.y, sp3C8.z);
        opModelScaleSet(0x17, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x17, 0U);
        opMotionFlagSet(0x17, 1);
        opModelCreate(0x18, 0xD0004, 0x2A9);
        opModelPosSet(0x18, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x18, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x18, 0U);
        opMotionFlagSet(0x18, 1);
        opModelCreate(0x19, 0xD0005, 0x2A9);
        opModelPosSet(0x19, 325.0f, 9.5f, 45.0f);
        opModelScaleSet(0x19, 1.0f, 1.0f, 1.0f);
        opMotionTimeSet(0x19, 0U);
        opMotionFlagSet(0x19, 1);
        opModelCreate(0x1D, 0xD0007, 0x6A9);
        opModelPosSet(0x1D, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x1D, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x1D, 1);
        opModelIdGet(0x1D);
        opModelDispOff(0x1D);
        opModelCreate(0x1E, 0xD0008, 0x6A9);
        opModelPosSet(0x1E, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x1E, 1);
        opModelIdGet(0x1E);
        opModelDispOff(0x1E);
        opModelCreate(0x1F, 0xD0009, 0x6A9);
        opModelPosSet(0x1F, 0.0f, 0.0f, 0.0f);
        opModelScaleSet(0x1F, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x1F, 1);
        opModelIdGet(0x1F);
        opModelDispOff(0x1F);
        opModelCreate(0x1B, 0xB0001, 0x6A9);
        opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
        opModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
        opMotionTimeSet(0x1B, 0U);
        opMotionFlagSet(0x1B, 1);
        opModelDispOff(0x1B);
        opMotionCreate(0x6E, 0xA0125, 0);
        opMotionCreate(0x6F, 0xA0129, 0);
        opWipeWhiteInCreate(0xF, 0x10);
        func_801110AC_opening(&cameraPos2.x, &cameraPos2.y, &cameraPos2.z, &cameraAt2.x, &cameraAt2.y, &cameraAt2.z);
        HuVecCopyXYZ(&sp3F8, cameraPos2.x - cameraAt2.x, cameraPos2.y - cameraAt2.y, cameraPos2.z - cameraAt2.z);
        i = 0;
        do {
            temp_f26 = (f32)i * 0.016393442f;
            temp_f26 = sindf(temp_f26 * 90.0f);
            temp_f24 = 45.0f;
            temp_f24 = temp_f26 * temp_f24;
            temp_f20 = cosdf(temp_f24);
            temp_f0 = sindf(temp_f24);
            temp_f22 = 0.4f;
            temp_f22 = temp_f26 * temp_f22;
            temp_f22 += 0.6f;
            temp_f20 *= sp3F8.x;
            temp_f20 += temp_f0 * sp3F8.z;
            temp_f0 = temp_f22 * temp_f20;
            temp_f20 = temp_f0;
            temp_f20 += cameraAt2.x;
            cameraPos2.x = temp_f20;
            cameraPos2.y = (temp_f22 * -150.0f) + cameraAt2.y + sp3F8.y;
            temp_f20 = sindf(temp_f24);
            temp_f0 = cosdf(temp_f24);
            temp_f22 *= (-sp3F8.x * temp_f20) + temp_f0 * sp3F8.z;
            temp_f22 += cameraAt2.z;
            cameraPos2.z = temp_f22;
            i += 1;
            func_801110F0_opening(cameraPos2.x, cameraPos2.y, cameraPos2.z, cameraAt2.x, cameraAt2.y, cameraAt2.z);
            HuPrcVSleep();
        } while (i < 0x1F);
        opModelDispOn(0xB);
        opMotionSet(0xB, 0x6D, 2);
        opMotionFlagSet(0xB, 1);
        opMotionTimeSet(0xB, 0U);
        HuVecCopyXYZ(&sp418, 0.0f, 325.0f, 300.0f);
        HuVecCopy3F(&sp408, &sp418);
        temp_f2_9 = sp408.y + 400.0f;
        sp408.y = temp_f2_9;
        opModelPosSet(0xB, sp408.x, temp_f2_9, sp408.z);
        opModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
        for (i = 0; i < 0x33; i++) {
            temp_f26 = (f32)i * 0.02f;
            temp_f26 = sindf(temp_f26 * 90.0f);
            HuVecCopyXYZ(&sp428, (temp_f26 * (sp418.x - sp408.x)) + sp408.x, (temp_f26 * (sp418.y - sp408.y)) + sp408.y, (temp_f26 * (sp418.z - sp408.z)) + sp408.z);
            opModelPosSet(0xB, sp428.x, sp428.y, sp428.z);
            if (i < 0x1E) {
                temp_f26 = (f32)(i + 0x1F) * 0.016393442f;
                temp_f26 = sindf(temp_f26 * 90.0f);
                temp_f24 = 45.0f;
                temp_f24 = temp_f26 * temp_f24;
                temp_f20 = cosdf(temp_f24);
                temp_f0 = sindf(temp_f24);
                temp_f22 = 0.4f;
                temp_f22 = temp_f26 * temp_f22;
                temp_f22 += 0.6f;
                temp_f20 *= sp3F8.x;
                temp_f20 += temp_f0 * sp3F8.z;
                temp_f0 = temp_f22 * temp_f20;
                temp_f20 = temp_f0;
                temp_f20 += cameraAt2.x;
                cameraPos2.x = temp_f20;
                cameraPos2.y = (temp_f22 * -150.0f) + cameraAt2.y + sp3F8.y;
                temp_f20 = sindf(temp_f24);
                temp_f0 = cosdf(temp_f24);
                temp_f22 *= (-sp3F8.x * temp_f20) + temp_f0 * sp3F8.z;
                temp_f22 += cameraAt2.z;
                cameraPos2.z = temp_f22;
                func_801110F0_opening(cameraPos2.x, cameraPos2.y, cameraPos2.z, cameraAt2.x, cameraAt2.y, cameraAt2.z);
            }
            HuPrcVSleep();
        }
        HuPrcSleep(0x14);
        func_80106DD0_opening(0xB, 3);
        opMotionEndWait(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x159);
        }
        opMotionSet(0xB, 0x6E, 2);
        opDemoStarWaitCreate(0, 0xB, sp428.x, sp428.y, sp428.z, 50.0f, 0x1E);
        HuPrcSleep(0x14);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D1BU);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D1AU);
            opSleep(0x3C);
        }
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D1DU);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D1CU);
            opSleep(0x78);
        }
        func_80107CA0_opening(0);
        if (storyMode != 0) {
            opDemoObjKill(0);
            opModelPosGet(0xB, &sp458.x, &sp458.y, &sp458.z);
            HuVecCopyXYZ(&sp438, sp458.x, sp458.y, sp458.z);
            HuVecCopyXYZ(&sp448, sp438.x + 240.0f, sp438.y + 25.0f, sp438.z - 150.0f);
            for (i = 0; i < 0x1F; i++) {
                temp_f20 = (f32)i * 0.033333335f;
                HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, (temp_f20 * (sp448.z - sp438.z)) + sp438.z);
                opModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
                HuPrcVSleep();
            }
            opDemoStarWaitCreate(0, 0xB, sp458.x, sp458.y, sp458.z, 50.0f, 0x1E);
            opModelDispOn(0x1B);
            opModelPosSet(0x1B, -215.0f, 168.0f, sp458.z + 20.0f);
            opModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
            opMotionTimeSet(0x1B, 0U);
            func_80106DD0_opening(0x1B, 1);
            if (storyMode != 0) {
                HuAudFXPlay(0x241);
            }
            HuPrcSleep(8);
            opModelDispOn(0x10);
            opModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
            opModelPosSet(0x10, -190.0f, 268.0f, sp458.z);
            opDemoStarWaitCreate(6, 0x10, -190.0f, 268.0f, sp458.z, 25.0f, 0x32);
            opMotionEndWait(0x1B);
            opModelDispOff(0x1B);
            func_80107C70_opening(0);
            if (storyMode != 0) {
                func_80107CD0_opening(0, 0x4D1EU);
                func_80107E2C_opening(0);
            }
            func_80107CA0_opening(0);
            opDemoObjKill(6);
            HuPrcSleep(1);
            opModelPosGet(0x10, &sp468.x, &sp468.y, &sp468.z);
            Hu3DCam3DToScreen(0, &sp468, &sp478);
            sp478.y -= 8.0f;
            opSprDispOn(0);
            opModelDispOff(0x10);
            for (i = 0; i < 0x11; i++) {
                temp_f20 = (f32)i * 0.0625f;
                opSprPosSet(0, (s32)((temp_f20 * (160.0f - sp478.x)) + sp478.x), (s32)((temp_f20 * (120.0f - sp478.y)) + sp478.y));
                temp_f0_53 = (temp_f20 * 0.85f) + 0.15f;
                opSprScaleSet(0, temp_f0_53, temp_f0_53);
                HuPrcVSleep();
            }
            opSprScaleSet(0, 1.0f, 1.0f);
            HuPrcSleep(0x3C);
            for (i = 0; i < 0x11; i++) {
                temp_f20 = (f32)(0x10 - i) * 0.0625f;
                opSprPosSet(0, (s32)((temp_f20 * (160.0f - sp478.x)) + sp478.x), (s32)((temp_f20 * (120.0f - sp478.y)) + sp478.y));
                temp_f0_54 = (temp_f20 * 0.85f) + 0.15f;
                opSprScaleSet(0, temp_f0_54, temp_f0_54);
                HuPrcVSleep();
            }
            opSprDispOff(0);
            opModelDispOn(0x10);
            HuPrcSleep(1);
            opDemoStarWaitCreate(6, 0x10, sp468.x, sp468.y, sp468.z, 25.0f, 0x32);
            func_80107C70_opening(0);
            if (storyMode != 0) {
                func_80107CD0_opening(0, 0x4D1FU);
                func_80107E2C_opening(0);
            }
            func_80107CA0_opening(0);
            opDemoObjKill(6);
            HuPrcSleep(1);
            opModelPosGet(0x10, &sp468.x, &sp468.y, &sp468.z);
            opModelPosSet(0x1B, sp468.x, sp468.y - 100.0f, sp468.z);
            opModelDispOn(0x1B);
            opModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
            opMotionTimeSet(0x1B, 4U);
            func_80106DD0_opening(0x1B, 1);
            if (storyMode != 0) {
                HuAudFXPlay(0x242);
            }
            opModelDispOff(0x10);
            opModelKill(0x10);
            opMotionEndWait(0x1B);
            opModelDispOff(0x1B);
            opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
            opModelScaleSet(0x1B, 8.0f, 1.0f, 8.0f);
            opMotionFlagSet(0x1B, 1);
        }
        HuPrcSleep(0x24);
        func_80107C70_opening(0);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D22U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D21U);
            opSleep(0x3C);
        }
        opMotionShiftSet(0xB, 0x6F, 4, 4, (s16)2);
        func_80107CA0_opening(0);
        opDemoObjKill(0);
        HuPrcSleep(1);
        opModelPosGet(0xB, &sp438.x, &sp438.y, &sp438.z);
        HuVecCopyXYZ(&sp448, 0.0f, sp438.y - 20.0f, sp438.z - 100.0f);
        for (i = 0; i < 0x3D; i++) {
            temp_f20 = (f32)i * 0.016666668f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, (temp_f20 * (sp448.z - sp438.z)) + sp438.z);
            opModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_56 = (((1.0f - temp_f20) * 0.1f) + 0.9f) * 2.5f;
            opModelScaleSet(0xB, temp_f0_56, temp_f0_56, temp_f0_56);
            HuPrcVSleep();
        }
        HuPrcSleep(0xA);
        opModelPosGet(0xB, &sp438.x, &sp438.y, &sp438.z);
        HuVecCopyXYZ(&sp448, 0.0f, 1250.0f, sp438.z);
        for (i = 0; i < 0x1F; i++) {
            temp_f20 = (f32)i * 0.033333335f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            opModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            HuPrcVSleep();
        }
        opModelDispOn(0x27);
        opModelPosSet(0x27, 0.0f, 0.0f, 300.0f);
        opModelScaleSet(0x27, 0.01f, 1.0f, 0.01f);
        opModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
        HuVecCopyXYZ(&sp438, 0.0f, sp458.y, 300.0f);
        HuVecCopyXYZ(&sp448, 0.0f, -90.0f, 300.0f);
        HuPrcSleep(0x1E);
        for (i = 0; i < 0x21; i++) {
            temp_f20 = (f32)i * 0.028571429f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            opModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_57 = (1250.0f - sp458.y) * 0.0008f;
            opModelScaleSet(0x27, temp_f0_57, 1.0f, temp_f0_57);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x23F);
        }
        opModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
        opModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
        opModelDispOn(0x1B);
        opMotionTimeSet(0x1B, 0U);
        func_80106DD0_opening(0x1B, 1);
        opModelDispOn(0x1D);
        opModelDispOn(0x1E);
        opModelDispOn(0x1F);
        HuVecCopyXYZ(&sp480, 0.0f, 0.0f, 300.0f);
        HuVecCopyXYZ(&sp490, 250.0f, 25.0f, 355.0f);
        func_801139B0_opening(8, 0x1D, &sp480, &sp490, "star_red", "red_kage");
        HuVecCopyXYZ(&sp490, -250.0f, 25.0f, 355.0f);
        func_801139B0_opening(9, 0x1E, &sp480, &sp490, "star_blue", "blue_kage");
        HuVecCopyXYZ(&sp490, 0.0f, 25.0f, 70.0f);
        func_801139B0_opening(0xA, 0x1F, &sp480, &sp490, "star_yellow", "yellow_kage");
        opModelDispOn(9);
        opModelDispOff(0x14);
        for (i = 0x21; i < 0x24; i++) {
            temp_f20 = (f32)i * 0.028571429f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            opModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_58 = (1250.0f - sp458.y) * 0.0008f;
            opModelScaleSet(0x27, temp_f0_58, 1.0f, temp_f0_58);
            HuPrcVSleep();
        }
        opModelDispOff(0xB);
        HuPrcSleep(0x2D);
        opMotionEndWait(0x1B);
        opModelDispOff(0x1B);
        opModelKill(0x1B);
        opModelDispOff(0x27);
        opModelKill(0x27);
        HuPrcSleep(0x3C);
        if (storyMode == 0) {
            omDelPrcObj(NULL);
        loop_273:
            HuPrcVSleep();
            goto loop_273;
        }
        D_800CD280_main = 1;
        MBBackKill();
        MBBackLoad(0x22);
        func_800E92D4_shared_board();
        Hu3DCamSetPerspective(0, 40.0f, 500.0f, 8000.0f);
        func_80110FB0_opening(&D_80114B70_opening[0], &D_80114B70_opening[1]);
        func_80046558_main(opModelIdGet(0xB));
        opDemoObjKill(8);
        opDemoObjKill(9);
        opDemoObjKill(0xA);
        opModelDispOff(0xB);
        opModelKill(0xB);
        opModelKill(0x6C);
        opModelKill(0x6D);
        opModelKill(0x6E);
        opModelKill(0x6F);
        opModelKill(0x14);
        opModelKill(0x15);
        opModelKill(0x16);
        opModelKill(0x17);
        opModelKill(0x18);
        opModelKill(0x19);
        opModelKill(0x1D);
        opModelKill(0x1E);
        opModelKill(0x1F);
        opModelKill(9);
        opMotionTimeSet(0x12, 0U);
        opMotionFlagSet(0x12, 1);
        opMotionTimeSet(0x13, 0U);
        opMotionFlagSet(0x13, 1);
        opModelDispOff(0x20);
        opModelCreate(0x11, 0xA00EE, 0x6A9);
        opModelPosSet(0x11, -40.0f, 0.0f, 2775.0f);
        opModelScaleSet(0x11, 1.0f, 1.0f, 1.0f);
        opMotionFlagSet(0x11, 2);
        opModelDispOn(0x20);
        opModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
        opModelPosSet(0x20, -40.0f, 0.0f, 2775.0f);
        HuVecCopyXYZ(&sp4A0, -880.0f, 0.0f, 2820.0f);
        HuVecCopyXYZ(&sp4B0, -53.0f, 0.0f, 2807.0f);
        opMotionCreate(0x71, 0xA00F1, 0);
        temp_f20 = 37.0f / 60.0f;
        HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
        opModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
        opModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
        temp_f0_59 = func_80111164_opening(sp4C0.x, sp4C0.z, D_80114B70_opening[0].x, D_80114B70_opening[0].z);
        lastAngles[1] = temp_f0_59;
        opModelRotSet(0x11, 0.0f, temp_f0_59, 0.0f);
        opMotionShiftSet(0x11, 0x71, 8, 8, (s16)2);
        HuPrcSleep(0xA);
        if (storyMode != 0) {
            HuAudFXPlay(0x2A0);
        }
        func_80107C70_opening(0);
        func_80107CD0_opening(0, 0x4D25U);
        HuPrcSleep(0x12);
        opMotionSpeedSet(0x11, 1.4f);
        for (i = 0; i < 8; i++) {
            temp_f20 = (f32)i * 0.125f;
            opModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_60 = func_80111490_opening(lastAngles[1], sp4B0.x - sp4C0.x, sp4B0.z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_60;
            opModelRotSet(0x11, 0.0f, temp_f0_60, 0.0f);
            HuPrcVSleep();
        }
        i = 0x25;
        temp_f0_61 = func_80111164_opening(sp4A0.x, sp4A0.z, sp4B0.x, sp4B0.z);
        lastAngles[1] = temp_f0_61;
        lastAngles[0] = temp_f0_61;
        opModelRotSet(0x11, 0.0f, temp_f0_61, 0.0f);
        do {
            temp_f20 = (f32)i * 0.016666668f;
            HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
            opModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
            opModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
            i += 1;
            HuPrcVSleep();
        } while (i < 0x3D);
        opMotionSpeedSet(0x11, 1.0f);
        opModelRotGet(0x11, &lastAngles[0], &lastAngles[1], &lastAngles[0]);
        for (i = 0; i < 0x10; i++) {
            temp_f20 = (f32)i * 0.0625f;
            opModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_62 = func_80111490_opening(lastAngles[1], D_80114B70_opening[0].x - sp4C0.x, D_80114B70_opening[0].z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_62;
            opModelRotSet(0x11, 0.0f, temp_f0_62, 0.0f);
            HuPrcVSleep();
        }
        opModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
        if (storyMode != 0) {
            func_80107CD0_opening(0, 0x4D26U);
            func_80107E2C_opening(0);
        } else {
            func_80107CD0_opening(0, 0x4D25U);
            HuPrcSleep(0x46);
        }
        func_80107CA0_opening(0);
        opModelPosGet(0x11, &sp4A0.x, &sp4A0.y, &sp4A0.z);
        HuVecCopyXYZ(&sp4B0, 800.0f, 0.0f, 3030.0f);
        opModelRotGet(0x11, &lastAngles[0], &lastAngles[1], &lastAngles[0]);
        for (i = 0; i < 0x10; i++) {
            temp_f20 = (f32)i * 0.0625f;
            opModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_63 = func_80111490_opening(lastAngles[1], sp4B0.x - sp4C0.x, sp4B0.z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_63;
            opModelRotSet(0x11, 0.0f, temp_f0_63, 0.0f);
            HuPrcVSleep();
        }
        opMotionSpeedSet(0x11, 1.4f);
        for (i = 0; i < 0x3D; i++) {
            temp_f20 = (f32)i * 0.016666668f;
            HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
            opModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
            opModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
            HuPrcVSleep();
            if (i == 0xA) {
                opDemoEndSet(1);
            }
        }
        for (i = 0; i < 0x1E; i++) {
            HuPrcVSleep();
        }
        omDelPrcObj(NULL);
    loop_294:
        HuPrcVSleep();
        goto loop_294;
    }
}

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

f32 func_801111AC_opening(f32 current, f32 target, f32 step) {
    f32 difference = target - current;

    difference = difference < 0.0f ? difference + 360.0f : difference;
    if (difference > 180.0f) {
        if (difference > 360.0f - step) {
            return target;
        }
        return current - step;
    }
    if (difference < step) {
        return target;
    }
    return current + step;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", func_8011124C_opening);

f32 func_80111490_opening(f32 current, f32 x, f32 z, f32 weight) {
    f32 angle = func_80111164_opening(0.0f, 0.0f, x, z);
    f32 difference;

    if (angle < 0.0f) {
        angle += 360.0f;
    }
    difference = angle - current;
    difference = difference < 0.0f ? difference + 360.0f : difference;
    if (difference > 180.0f) {
        return -(360.0f - difference) * weight + current;
    }
    return difference * weight + current;
}

void func_80111580_opening(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 model1;
    s32 model2;
    Vec pos;
    s32 i;
    f32 t;
    f32 angle;
    f32 size;
    f32 remaining;

    model1 = func_80111984_opening(0x110012, 0x689);
    model2 = func_80111984_opening(0x110012, 0x689);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    for (i = 0, remaining = 1.0f; i < 120; i++) {
        if (i == 90) {
            func_80107CA0_opening(0);
        }
        t = i * (1.0f / 120.0f);
        HuSqrtf(t);
        angle = t * 360.0f;
        t = remaining - t;
        size = t * 8.0f;
        pos.x = t * 100.0f * sindf(angle);
        pos.y = 40.0f - pos.x * 0.2f - t * 120.0f * cosdf(angle);
        pos.z = t * 800.0f * cosdf(angle) + -200.0f;
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model2, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model2, pos.x, pos.y, pos.z, size);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_8001ACDC_main(model1);
    func_8001ACDC_main(model2);
}

s16 func_801117D4_opening(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    modelId = func_8000B108_main(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(modelId, 0x20000, 0x20000);
    func_8001C448_main(modelId);
    func_8001C954_main(modelId);
    func_8001C514_main(modelId);
    func_80013390_main(modelId, -1, 0, func_80111F58_opening);
    data = HmfModelData[modelId].hmf;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk08.f = 30.0f;
    work->unk0C.f = 720.0f;
    work->unk10.f = 80.0f;
    work->unk14 = 5.0f;
    startRadius = work->unk10.f / 10.0f;
    radiusStep = (work->unk10.f - startRadius) / work->unk08.f;
    angleStep = work->unk0C.f / work->unk08.f;
    for (i = 0; i < data->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = startRadius;
        particle->unk1C = radiusStep;
        particle->unk24 = angleStep;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return modelId;
}

s32 func_80111984_opening(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    modelId = func_8000B108_main(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(modelId, 0x20000, 0x20000);
    func_8001C448_main(modelId);
    func_8001C954_main(modelId);
    func_8001C514_main(modelId);
    func_80013390_main(modelId, -1, 0, func_80112120_opening);
    data = HmfModelData[modelId].hmf;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk08.f = 30.0f;
    work->unk0C.f = 720.0f;
    work->unk10.f = 80.0f;
    work->unk14 = 5.0f;
    startRadius = work->unk10.f / 10.0f;
    radiusStep = (work->unk10.f - startRadius) / work->unk08.f;
    angleStep = work->unk0C.f / work->unk08.f;
    for (i = 0; i < data->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = startRadius;
        particle->unk1C = radiusStep;
        particle->unk24 = angleStep;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return modelId;
}

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

s32 func_80111C88_opening(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    f32 angle;

    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = func_80111C30_opening(360);
            particle->unk20 = work->unk10.f / 10.0f;
            angle = (f32)func_80111C30_opening(150) - 75.0f;
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0.0f;
            particle->unk04 = 0.0f;
            return 1;
        }
    }
    return 0;
}

s32 func_80111DDC_opening(s16 modelId, f32 x, f32 y, f32 z, f32 size) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    D_80117378_opening.x = x;
    D_80117378_opening.y = x;
    D_80117378_opening.z = x;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk04 = 0.0f;
            particle->unk24 = sindf(func_80111C30_opening(360));
            particle->unk28 = sindf(func_80111C30_opening(360));
            particle->unk2C = sindf(func_80111C30_opening(360));
            particle->unk0C = work->unk1C.f;
            particle->unk14 = work->unk24.f;
            particle->unk10 = work->unk20.f;
            particle->unk08 = size;
            return 1;
        }
    }
    return 0;
}

void func_80111F58_opening(s16 modelId) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    s16 count = data->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk18 += particle->unk24;
            if (particle->unk18 < 0.0f) {
                particle->unk18 += 360.0f;
            } else if (particle->unk18 >= 360.0f) {
                particle->unk18 -= 360.0f;
            }
            radius = particle->unk20 + particle->unk1C;
            particle->unk20 = radius;
            radius *= particle->unk2C;
            particle->unk0C = radius * sindf(particle->unk18) + work->unk1C.f;
            particle->unk14 = radius * cosdf(particle->unk18) + work->unk24.f;
            particle->unk10 = particle->unk20 * particle->unk28 + work->unk20.f;
            particle->unk04 += work->unk14;
            if (particle->unk04 > 180.0f) {
                particle->unk04 = 180.0f;
            }
            particle->unk08 = sindf(particle->unk04) * work->unk14;
        }
    }
    work->unk02++;
}

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

void opTitleSetup(void) {
    u16 sprite;

    func_801061F0_opening();
    func_80110F48_opening();
    opContErrorCreate();
    func_80112944_opening();
    {
        Vec initPos = D_80114D84_opening;
        Vec initAt = D_80114D90_opening;
        func_80110FB0_opening(&initPos, &initAt);
    }
    opSprBGCreate(0, 0x100000);
    opSprPosSet(0, 160, 120);
    func_8000BCC8_main((u16)opEspIdGet(0), 9);
    opSprBGDispOn(0);
    opSprBGCreate(1, 0x100001);
    opSprPosSet(1, 160, 120);
    func_8000BCC8_main((u16)opEspIdGet(1), 11);
    opSprBGDispOn(1);
    opSprBGCreate(2, 0x100002);
    opSprPosSet(2, 160, 71);
    opSprAttrSet(2, 8);
    opSprAlphaSet(2, 255);
    func_8000BCC8_main((u16)opEspIdGet(2), 8);
    opSprBGCreate(3, 0x100005);
    opSprPosSet(3, 160, 71);
    opSprAttrSet(3, 8);
    opSprAlphaSet(3, 255);
    sprite = opEspIdGet(3);
    func_8000BEAC_main(sprite, 255, 255, 255);
    func_8000BCC8_main(sprite, 9);
    opSprBGCreate(4, 0x100003);
    opSprPosSet(4, 158, 197);
    opSprAttrSet(4, 8);
    opSprAlphaSet(4, 255);
    func_8000BCC8_main((u16)opEspIdGet(4), 8);
    opSprBGCreate(5, 0x100004);
    opSprPosSet(5, 158, 197);
    opSprAttrSet(5, 0x1008);
    opSprAlphaSet(5, 255);
    sprite = opEspIdGet(5);
    func_8000BEAC_main(sprite, 0, 6, 115);
    func_8000BCC8_main(sprite, 9);
}

void opTitleSprMain(void) {
    s32 frame;
    f32 alpha;
    f32 time;
    f32 speed;
    f32 velocity;
    f32 scale;

    opSprBGDispOff(2);
    opSprBGDispOff(3);
    opSprBGDispOff(4);
    opSprBGDispOff(5);
    HuAudFXPlay(0x240);
    HuPrcSleep(16);
    for (frame = 0; frame < 40; frame++) {
        HuPrcVSleep();
        alpha = 1.0f - frame * (1.0f / 60.0f);
        alpha = alpha < 0.0f ? 0.0f : alpha;
        opSprAlphaSet(0, (u8)(alpha * 255.0f));
    }
    opSprBGDispOn(2);
    opSprScaleSet(2, 0.0f, 0.0f);
    opSprScaleSet(3, 0.0f, 0.0f);
    speed = -2.0f;
    velocity = 0.0f;
    HuAudSeqPlay(2);
    for (frame = 40; frame < 61; frame++) {
        HuPrcVSleep();
        time = frame;
        alpha = 1.0f / 60.0f;
        alpha = 1.0f - alpha * time;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
        opSprAlphaSet(0, (u8)(alpha * 255.0f));
        alpha = 1.0f - (frame - 40) * 0.05f;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
        velocity += speed * -0.8f;
        speed += velocity;
        speed *= 0.7f;
        scale = speed * alpha + 1.0f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        opSprScaleSet(2, scale, scale);
        opSprScaleSet(3, scale, scale);
    }
    HuPrcVSleep();
    opSprScaleSet(2, 1.0f, 1.0f);
    opSprScaleSet(3, 1.0f, 1.0f);
    opSprAlphaSet(0, 0);
    opSprBGDispOn(4);
    opSprBGDispOn(5);
    func_80106768_opening(4, 0, 0);
    func_80106768_opening(5, 0, 0);
    opSprAlphaSet(4, 0);
    opSprAlphaSet(5, 0);
    func_8000BDDC_main(D_80114EB0_opening[4].espriteSlot, 0);
    func_8000BDDC_main(D_80114EB0_opening[5].espriteSlot, 0);
    for (frame = 0; frame < 9; frame++) {
        HuPrcVSleep();
        opSprAlphaSet(4, frame * 32);
        opSprAlphaSet(5, frame * 32);
    }
    opSprAlphaSet(4, 256);
    opSprAlphaSet(5, 256);
    func_8000BDDC_main(D_80114EB0_opening[4].espriteSlot, 1);
    func_8000BDDC_main(D_80114EB0_opening[5].espriteSlot, 1);
    opContErrorDispOn();
    HuPrcSleep(780);
    opContErrorDispOff();
    omDelPrcObj(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

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
            opMotionShiftSet(modelId, D_8011739C_opening[index][0].motion[0], 4, 4, 2);
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
    D_8011739C_opening[index][0].motion[0] = motion2;
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

void opDemoOutEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 otherModelId = modelId + 32;
    s16 effectId = D_80117398_opening[index][0].effectId;
    f32 scale = D_801173A8_opening[index][0];

    HuVecCopy3F(&pos, &D_8011739C_opening[index][0].pos);
    if (D_8011738C_opening[index][0] >= 40) {
        func_8001ACDC_main(effectId);
        D_8011738C_opening[index][0] = 0;
        opDemoObjKill(index);
    } else if (D_8011738C_opening[index][0] >= 20) {
        opModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
        opModelScaleSet(otherModelId, 3.0f, 1.0f, 3.0f);
        opModelDispOff(modelId);
        opModelDispOff(otherModelId);
        D_8011738C_opening[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(effectId, pos.x, pos.y, pos.z);
        opModelScaleSet(modelId, scale, 1.0f, scale);
        opModelScaleSet(otherModelId, scale, 1.0f, scale);
        D_801173A8_opening[index][0] = scale;
        D_8011738C_opening[index][0]++;
    }
}

void opDemoOutEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    opDemoObjCreate(index, opDemoOutEffMain);
    effectId = func_801117D4_opening(0x110012, 0x689);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].effectId = effectId;
    opModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&D_8011739C_opening[index][0].pos, &pos);
    D_80117394_opening[index].unk_1C.y = 1.0f;
    D_8011738C_opening[index][0] = 0;
}

void opDemoGuideInEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s16 effectId = D_80117398_opening[index][0].effectId;
    f32 scale = D_801173A8_opening[index][0];

    HuVecCopy3F(&pos, &D_8011739C_opening[index][0].pos);
    if (D_8011738C_opening[index][0] >= 80) {
        func_8001ACDC_main(effectId);
        D_8011738C_opening[index][0] = 0;
        opDemoObjKill(index);
    } else if (D_8011738C_opening[index][0] >= 50) {
        D_8011738C_opening[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(effectId, pos.x, pos.y + 25.0f, pos.z);
        D_801173A8_opening[index][0] = scale;
        D_8011738C_opening[index][0]++;
    }
}

void opDemoGuideInEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    opDemoObjCreate(index, opDemoGuideInEffMain);
    effectId = func_801117D4_opening(0x110012, 0x689);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].effectId = effectId;
    opModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&D_8011739C_opening[index][0].pos, &pos);
    D_80117394_opening[index].unk_1C.y = 1.0f;
    D_8011738C_opening[index][0] = 0;
}

void opDemoStarWaitMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    f32 step = 1.0f / D_80117390_opening[index][0];
    f32 angle = step * 360.0f + D_801173A8_opening[index][0];
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_801173A8_opening[index][0] = angle;
    height = sindf(angle) * D_801173A4_opening[index][0];
    HuVecCopy3F(&pos, &D_80117398_opening[index][0].pos);
    opModelPosSet(modelId, pos.x, height + pos.y, pos.z);
}

void opDemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames) {
    opDemoObjCreate(index, opDemoStarWaitMain);
    D_80117394_opening[index].modelId = modelId;
    HuVecCopyXYZ(&D_80117398_opening[index][0].pos, x, y, z);
    D_801173A4_opening[index][0] = arg5;
    D_801173A8_opening[index][0] = 0;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = frames;
}

void func_801134FC_opening(s32 index, Vec *pos1, Vec *pos2, f32 scale, f32 angle) {
    func_80088800_main(D_801173BC_opening[index][0]->unk58, pos1->x, pos1->y, pos1->z);
    func_80017CD0_main(D_801173BC_opening[index][0]->unk58, scale, 1.0f, scale);
    func_800185A4_main(D_801173BC_opening[index][0]->unk58, angle);
    func_80088800_main(D_801173C0_opening[index][0]->unk58, pos2->x, pos2->y + 4.0f, pos2->z);
    func_80017CD0_main(D_801173C0_opening[index][0]->unk58, scale, 1.0f, scale);
    func_800185A4_main(D_801173C0_opening[index][0]->unk58, angle);
}

void func_8011361C_opening(omObjData *obj) {
    Vec pos;
    Vec shadow;
    s8 index = obj->work[0];
    f32 step = 1.0f / D_80117390_opening[index][0];
    f32 angle = step * 360.0f + D_8011739C_opening[index][0].pos.x;
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_8011739C_opening[index][0].pos.x = angle;
    height = sindf(angle) * D_8011739C_opening[index][0].pos.y;
    HuVecCopy3F(&pos, &D_801173B0_opening[index][0].pos);
    pos.y = height + pos.y;
    HuVecCopy3F(&shadow, &D_801173B0_opening[index][0].pos);
    shadow.y = 0;
    func_801134FC_opening(index, &pos, &shadow, 1.0f, 0);
}

void func_8011373C_opening(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec modelPos;
    Vec shadow;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    OpWork *slot = &D_80117394_opening[index];
    f32 time;

    HuVecCopy3F(&start, &slot->unk_1C);
    HuVecCopy3F(&end, &slot->unk_28);
    time = 1.0f / D_80117390_opening[index][0];
    time *= D_8011738C_opening[index][0];
    HuVecCopyXYZ(&pos, time * (end.x - start.x) + start.x,
                 time * (end.y - start.y) + start.y + (0.25 - (time - 0.5f) * (time - 0.5f)) * 4.0 * 5.0 * 20.0,
                 time * (end.z - start.z) + start.z);
    HuVecCopy3F(&start, &slot->unk_1C);
    opModelPosSet(modelId, 0, 0, 0);
    HuVecCopyXYZ(&modelPos, pos.x, pos.y, pos.z);
    HuVecCopyXYZ(&shadow, pos.x, 0, pos.z);
    time = time * 0.8 + 0.2f;
    func_801134FC_opening(index, &modelPos, &shadow, time, 0);
    if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        D_8011738C_opening[index][0] = 0;
        obj->func = func_8011361C_opening;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_801139B0_opening(s32 index, s32 modelId, Vec *pos1, Vec *pos2, char *node1, char *node2) {
    s16 model;
    OpWork *slot;

    opDemoObjCreate(index, func_8011373C_opening);
    D_80117394_opening[index].modelId = modelId;
    slot = &D_80117394_opening[index];
    HuVecCopy3F(&slot->unk_1C, pos1);
    HuVecCopy3F(&slot->unk_28, pos2);
    D_8011739C_opening[index][0].pos.y = 12.0f;
    D_8011739C_opening[index][0].pos.x = 0;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = 20;
    model = opModelIdGet(modelId);
    D_801173BC_opening[index][0] = func_8001D33C_main(model, node1);
    D_801173C0_opening[index][0] = func_8001D33C_main(model, node2);
    func_8011373C_opening(D_80117388_opening[index].obj);
}

void func_80113AE8_opening(omObjData *obj) {
    Vec oldPos;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 frame = D_8011738C_opening[index][0];
    f32 xAngle = D_801173B0_opening[index][0].pos.x;
    f32 yAngle = D_801173B4_opening[index][0];
    f32 zAngle = D_801173B8_opening[index][0];

    oldPos.x = sindf(xAngle) * 65.0f + D_80117398_opening[index][0].pos.x;
    oldPos.y = (sindf(yAngle) + 1.0f) * 20.0f + D_8011739C_opening[index][0].pos.x;
    oldPos.z = cosdf(zAngle) * 11.0f + D_80117398_opening[index][0].pos.z;
    xAngle = xAngle + 1.45f < 360.0f ? xAngle + 1.45f : xAngle - 360.0f + 1.45f;
    yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
    zAngle = zAngle + 0.8f < 360.0f ? zAngle + 0.8f : zAngle - 360.0f + 0.8f;
    pos.x = D_80117398_opening[index][0].pos.x + sindf(xAngle) * 65.0f;
    pos.y = (sindf(yAngle) + 1.0f) * 20.0f + D_8011739C_opening[index][0].pos.x;
    pos.z = cosdf(zAngle) * 11.0f + D_80117398_opening[index][0].pos.z;
    opModelPosSet(modelId, pos.x, pos.y, pos.z);
    opModelRotSet(modelId, 0, func_80111164_opening(oldPos.x, oldPos.z, pos.x, pos.z), 0);
    frame++;
    frame = frame <= 256 ? frame : 0;
    D_8011738C_opening[index][0] = frame;
    D_801173B0_opening[index][0].pos.x = xAngle + (rand8() & 7) * 0.3f;
    D_801173B4_opening[index][0] = yAngle + (rand8() & 3) * 0.3f;
    D_801173B8_opening[index][0] = zAngle;
}

void func_80113E8C_opening(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 frame = D_8011738C_opening[index][0];
    f32 time = 1.0f / D_80117390_opening[index][0];
    f32 xAngle;
    f32 yAngle;
    f32 zAngle;

    time *= D_8011738C_opening[index][0];
    frame++;
    if (time < 1.0f) {
        HuVecCopyXYZ(&start, D_80117398_opening[index][0].pos.x, D_8011739C_opening[index][0].pos.x,
                     D_80117398_opening[index][0].pos.z);
        HuVecCopyXYZ(&end, D_801173A4_opening[index][0], D_801173A8_opening[index][0], D_80117394_opening[index].unk_1C.z);
        xAngle = D_801173B0_opening[index][0].pos.x;
        yAngle = D_801173B4_opening[index][0];
        zAngle = D_801173B8_opening[index][0];
        pos.x = (end.x - start.x) * time + start.x;
        pos.y = (end.y - start.y) * time + start.y;
        pos.z = (end.z - start.z) * time + start.z;
        yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
        pos.y = (sindf(yAngle) + 1.0f) * 20.0f + pos.y;
        opModelPosSet(modelId, pos.x, pos.y, pos.z);
        opModelRotSet(modelId, 0, func_80111164_opening(pos.x, pos.z, end.x, end.z), 0);
        D_8011738C_opening[index][0] = frame;
        D_801173B0_opening[index][0].pos.x = xAngle;
        D_801173B4_opening[index][0] = yAngle;
        D_801173B8_opening[index][0] = zAngle;
    } else {
        opDemoObjKill(index);
    }
    D_8011738C_opening[index][0] = frame;
}

void func_80114150_opening(s32 index, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;
    OpWork *slot;

    opModelPosGet(D_80117394_opening[index].modelId, &pos.x, &pos.y, &pos.z);
    slot = &D_80117394_opening[index];
    HuVecCopy3F(&slot->pos, &pos);
    HuVecCopyXYZ(&slot->unk_1C, x, y, z);
    D_801173B0_opening[index][0].motion[0] = 0;
    D_801173B4_opening[index][0] = 0;
    D_801173B8_opening[index][0] = 0;
    D_80117388_opening[index].obj->func = func_80113E8C_opening;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = arg4;
}

void func_80114250_opening(s32 index, s32 modelId, f32 x, f32 y, f32 z) {
    OpObj *slot;

    opDemoObjCreate(index, func_80113AE8_opening);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = 20;
    D_80117394_opening[index].modelId = modelId;
    slot = &D_80117388_opening[index];
    slot->unk_2C.x = slot->unk_2C.y = 0;
    D_801173B0_opening[index][0].pos.x = 0;
    D_801173B0_opening[index][0].pos.x = rand8();
    D_801173B4_opening[index][0] = rand8();
    D_80117398_opening[index][0].pos.x = x;
    D_8011739C_opening[index][0].pos.x = y;
    D_80117398_opening[index][0].pos.z = z;
    func_80113AE8_opening(D_80117388_opening[index].obj);
}

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
