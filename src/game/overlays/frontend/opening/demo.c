#include "common.h"
#include "game/overlays/party/common/back.h"
#include "game/mallocblock.h"
#include "game/overlays/opening.h"
#include "game/hmfmath.h"

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

extern const Vec op_mesCameraPos;
extern const Vec op_mesCameraAt;
extern const Vec op_sparkCameraPos, op_sparkCameraAt;

Vec op_cameraMainTbl[2] = { { 350.0f, 190.0f, 3770.0f }, { -1000.0f, 130.0f, 450.0f } };
Vec op_cameraFarTbl[2] = { { 220.0f, 963.0f, 1900.0f }, { 4340.0f, 4720.0f, 5925.0f } };
Vec op_cameraOrbitPos = { 0.0f, 700.0f, 1500.0f };
Vec op_cameraOrbitAt = { 0.0f, 0.0f, -500.0f };
Vec op_viewportScale = { 640.0f, 480.0f, 511.0f };
Vec op_viewportTrans = { 640.0f, 480.0f, 511.0f };
RectF op_scissorRect = { 8.0f, 8.0f, 312.0f, 232.0f };
u32 op_randSeed = 0;

Gfx op_wipeDl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 192),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};

void op_DemoEndSet(s32);
f32 op_DirLerp(f32 x1, f32 z1, f32 x2, f32 z2, f32 weight);

s16 op_AnimIdGet(s32 slot);
s16 op_EspIdGet(s32 slot);
void op_AnimCreate(s32 arg0, s32 arg1);
void op_AnimKill(s32 arg0);
void op_EspCreate(s32 slot, s16 animId);
void op_EspKill(s32 slot);
void op_SprCreate(s32 slot, s32 resourceId);
void op_SprBGCreate(s32 slot, s32 resourceId);
void op_SprKill(s32 slot);
void op_SprKillAll(void);
void op_SprDispOn(s32 slot);
void op_SprDispOff(s32 slot);
void op_SprBGDispOn(s32 slot);
void op_SprBGDispOff(s32 slot);
void op_SprPosGet(s32 slot, s32 *x, s32 *y);
void op_SprScaleSet(s32 arg0, f32 arg1, f32 arg2);
void op_SprAlphaSet(s32 arg0, u16 arg1);
void op_SprAttrSet(s32 arg0, u16 arg1);
void op_SprAttrReset(s32 arg0, u16 arg1);
void op_SprPriSet(s32 arg0, u16 arg1);
void op_SprBankSet(s32 slot, u16 arg1, u16 arg2);
void op_ModelCreate(s32 slot, s32 resourceId, s32 arg2);
void op_MotionCreate(s32 slot, s32 resourceId, s32 arg2);
void op_ModelKill(s32 slot);
void op_ModelKillAll(void);
s16 op_ModelIdGet(s32 modelId);
s16 op_MotionIdGet(s32 motionId);
void op_ModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void op_ModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void op_ModelPosGet(s32 modelId, f32 *posX, f32 *posY, f32 *posZ);
void op_ModelRotGet(s32 modelId, f32 *rotX, f32 *rotY, f32 *rotZ);
void op_ModelScaleGet(s32 modelId, f32 *scaleX, f32 *scaleY, f32 *scaleZ);
void op_ModelDispOff(s32 arg0);
void op_ModelDispOn(s32 arg0);
void op_MotionFlagSet(s32 modelId, s16 arg1);
void op_MotionShiftSet(s32 modelId, s32 motionId, s16 arg2, s16 arg3, s16 arg4);
void op_MotionFlagReset(s32 modelId, s16 arg1);
void op_MotionSpeedSet(s32 modelId, f32 speed);
void op_MotionTimeSet(s32 slot, u32 time);
void op_MotionEndWait(s32 slot);
s32 op_MotionEndCheck(s32 arg0);
void op_BGSprCreate(void);
void op_BGSprKill(void);
u32 op_WinMesConv(u32 arg0);
s16 op_WinType0Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 op_WinType1Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 op_WinType2Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
s16 op_WinType3Create(u32 event, s16 x, s16 y, s16 style);
s16 op_WinType4Create(u32 event, s16 x, s16 y, s16 style);
s16 op_WinType5Create(u32 event, s16 x, s16 y, s16 style);
void op_WinKillAll(void);
void op_WinScaleSet(s32 slot, f32 x, f32 y);
void op_WinPosSet(s32 arg0, f32 arg1, f32 arg2);
void op_WinDispOn(s32 slot);
void op_WinDispOff(s32 slot);
void op_WinMesSet(s32 slot, u32 event);
void op_WinInsertMesSet(s32 slot, s8 arg1, s32 arg2);
s32 op_WinChoiceGet(s32 slot, s16 arg1, s32 arg2);
s16 op_WinIdGet(s32 slot);
void op_WinMesWait(s32 index);
void op_PadBtnWait(s32 arg0);
void op_WinPriSet(s32 slot, s16 arg1);
u16 op_CameraDebugExec(s32 value);
void op_MenuWinCreate(s32 slot, u32 event);
void op_CameraShakeCreate(s32 totalFrames, f32 magnitude);
void op_DemoCharCreate(s32 slot, s32 resourceId, f32 x, f32 y, f32 z);
void op_DemoShadowCreate(s32 slot, f32 x, f32 y, f32 z);
void op_CameraObjCreate(Vec *pos, Vec *at);
void op_CameraUpdate(void);
void op_CameraPosGet(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ);
void op_CameraPosSet(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ);
f32 op_CameraAngleCalc(f32 x1, f32 z1, f32 x2, f32 z2);
f32 op_AngleStep(f32 current, f32 target, f32 step);
f32 op_AngleLerp(f32 current, f32 x, f32 z, f32 weight);
void op_SparkTrailExec(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
u32 op_RandSeedCalc(u32 seed);
u32 op_Rand(void);
u32 op_RandMod(u32 max);
s32 op_SpiralEffAdd(s16 modelId, f32 x, f32 y, f32 z);
void op_DemoObjCreate(s32 index, omObjFunc func);
void op_DemoMotIntervalCreate(s32 index, s32 modelId, s32 motion1, s32 motion2, s32 startTime, s32 frames);
void op_DemoMotRestartMain(omObjData *obj);
void op_DemoMotRestartCreate(s32 index, s32 modelId, s32 startTime, s32 endTime);
void op_DemoOutEffCreate(s32 index, s32 modelId);
void op_DemoGuideInEffCreate(s32 index, s32 modelId);
void op_DemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames);
void op_DemoJumpNodeSet(s32 index, Vec *pos1, Vec *pos2, f32 scale, f32 angle);
void op_DemoFloatMain(omObjData *obj);
void op_DemoJumpCreate(s32 index, s32 modelId, Vec *pos1, Vec *pos2, char *node1, char *node2);
void op_DemoFlyAwaySet(s32 index, f32 x, f32 y, f32 z, s32 arg4);
void op_DemoFlyCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z);
void op_WipeDraw(Gfx **gfx, s32 arg1, s32 arg2);
void op_WipeColorSet(s32 arg0, u8 red, u8 green, u8 blue, u8 alpha);
void op_WipeInMain(omObjData *obj);
void op_WipeOutMain(omObjData *obj);
void op_WipeInCreate(s32 index, s32 totalFrames);
void op_WipeOutCreate(s32 index, s32 totalFrames);
void op_WipeWhiteInCreate(s32 index, s32 totalFrames);
void op_WipeWhiteOutCreate(s32 index, s32 totalFrames);
void op_CharAnimKill(s32 character);
void op_Sleep(s32 frames);

void op_UtilInit(void) {
    op_SprInit();
    op_ModelInit();
    op_WinInit();
}

void op_SprInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_sprTbl); i++) {
        op_animTbl[i].animId = -1;
        op_sprTbl[i].espriteSlot = -1;
        op_sprTbl[i].unk_04 = op_sprTbl[i].unk_08 = 0;
        op_sprTbl[i].unk_0C = op_sprTbl[i].unk_10 = 0.0f;
        op_sprTbl[i].unk_14 = op_sprTbl[i].unk_0C;
        op_sprTbl[i].unk_18 = 0xFF;
    }
}

s16 op_AnimIdGet(s32 slot) {
    return op_animTbl[slot].animId;
}

s16 op_EspIdGet(s32 slot) {
    return op_sprTbl[slot].espriteSlot;
}

void op_AnimCreate(s32 arg0, s32 arg1) {
    op_animTbl[arg0].animId = HuSprAnimDataRead(arg1);
}

void op_AnimKill(s32 arg0) {
    if (op_animTbl[arg0].animId != -1) {
        HuSprAnimKill(op_animTbl[arg0].animId);
    }
    op_animTbl[arg0].animId = -1;
}

void op_EspCreate(s32 slot, s16 animId) {
    op_sprTbl[slot].espriteSlot = espEntry(op_animTbl[animId].animId, 0, 0);
    op_SprPosSet(slot, 0xA0, 0x78);
}

void op_EspKill(s32 slot) {
    if (op_sprTbl[slot].espriteSlot != -1) {
        espKill(op_sprTbl[slot].espriteSlot);
    }
    op_sprTbl[slot].espriteSlot = -1;
}

void op_SprCreate(s32 slot, s32 resourceId) {
    op_AnimCreate(slot, resourceId);
    op_EspCreate(slot, slot);
}

void op_SprBGCreate(s32 slot, s32 resourceId) {
    op_SprCreate(slot, resourceId);
    espAttrSet(op_sprTbl[slot].espriteSlot, 0x4000);
}

void op_SprKill(s32 slot) {
    op_EspKill(slot);
    op_AnimKill(slot);
}

void op_SprKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_sprTbl); i++) {
        op_SprKill(i);
    }
}

void op_SprDispOn(s32 slot) {
    espDispOn(op_sprTbl[slot].espriteSlot);
}

void op_SprDispOff(s32 slot) {
    espDispOff(op_sprTbl[slot].espriteSlot);
}

void op_SprBGDispOn(s32 slot) {
    op_SprDispOn(slot);
}

void op_SprBGDispOff(s32 slot) {
    op_SprDispOff(slot);
}

void op_SprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    op_sprTbl[arg0].unk_04 = arg1;
    op_sprTbl[arg0].unk_08 = arg2;
    espPosSet(op_sprTbl[arg0].espriteSlot, arg1, arg2);
}

void op_SprPosGet(s32 slot, s32 *x, s32 *y) {
    *x = op_sprTbl[slot].unk_04;
    *y = op_sprTbl[slot].unk_08;
}

void op_SprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    op_sprTbl[arg0].unk_0C = arg1;
    op_sprTbl[arg0].unk_10 = arg2;
    espScaleSet(op_sprTbl[arg0].espriteSlot, arg1, arg2);
}

void op_SprAlphaSet(s32 arg0, u16 arg1) {
    espTPLvlSet(op_sprTbl[arg0].espriteSlot, arg1);
}

void op_SprAttrSet(s32 arg0, u16 arg1) {
    espAttrSet(op_sprTbl[arg0].espriteSlot, arg1);
}

void op_SprAttrReset(s32 arg0, u16 arg1) {
    espAttrReset(op_sprTbl[arg0].espriteSlot, arg1);
}

void op_SprPriSet(s32 arg0, u16 arg1) {
    espPriSet(op_sprTbl[arg0].espriteSlot, arg1);
}

void op_SprBankSet(s32 slot, u16 arg1, u16 arg2) {
    espAnimModeSet(op_sprTbl[slot].espriteSlot, 1);
    espBankSet(op_sprTbl[slot].espriteSlot, arg1, arg2);
}

void op_ModelInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_modelTbl); i++) {
        op_modelTbl[i].modelId = -1;
        op_modelTbl[i].motionId = -1;
    }
}

void op_ModelCreate(s32 slot, s32 resourceId, s32 arg2) {
    s16 modelId;

    modelId = Hu3DModelRead(resourceId, arg2);
    op_modelTbl[slot].modelId = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void op_MotionCreate(s32 slot, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    op_modelTbl[slot].motionId = Hu3DMotionCreate(data, (s16)arg2);
    DataClose(data);
}

void op_ModelKill(s32 slot) {
    if (op_modelTbl[slot].modelId != -1) {
        Hu3DModelKill(op_modelTbl[slot].modelId);
        op_modelTbl[slot].modelId = -1;
    }
    if (op_modelTbl[slot].motionId != -1) {
        Hu3DMotionKill(op_modelTbl[slot].motionId);
        op_modelTbl[slot].motionId = -1;
    }
}

void op_ModelKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_modelTbl); i++) {
        op_ModelKill(i);
    }
}

s16 op_ModelIdGet(s32 modelId) {
    return op_modelTbl[modelId].modelId;
}

s16 op_MotionIdGet(s32 motionId) {
    return op_modelTbl[motionId].motionId;
}

void op_ModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    op_modelTbl[arg0].rotX = arg1;
    op_modelTbl[arg0].rotY = arg2;
    op_modelTbl[arg0].rotZ = arg3;
    Hu3DModelRotSet(op_modelTbl[arg0].modelId, arg1, arg2, arg3);
}

void op_ModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    op_modelTbl[arg0].posX = arg1;
    op_modelTbl[arg0].posY = arg2;
    op_modelTbl[arg0].posZ = arg3;
    Hu3DModelPosSet(op_modelTbl[arg0].modelId, arg1, arg2, arg3);
}

void op_ModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    op_modelTbl[arg0].scaleX = arg1;
    op_modelTbl[arg0].scaleY = arg2;
    op_modelTbl[arg0].scaleZ = arg3;
    Hu3DModelScaleSet(op_modelTbl[arg0].modelId, arg1, arg2, arg3);
}

void op_ModelPosGet(s32 modelId, f32 *posX, f32 *posY, f32 *posZ) {
    *posX = op_modelTbl[modelId].posX;
    *posY = op_modelTbl[modelId].posY;
    *posZ = op_modelTbl[modelId].posZ;
}

void op_ModelRotGet(s32 modelId, f32 *rotX, f32 *rotY, f32 *rotZ) {
    *rotX = op_modelTbl[modelId].rotX;
    *rotY = op_modelTbl[modelId].rotY;
    *rotZ = op_modelTbl[modelId].rotZ;
}

void op_ModelScaleGet(s32 modelId, f32 *scaleX, f32 *scaleY, f32 *scaleZ) {
    *scaleX = op_modelTbl[modelId].scaleX;
    *scaleY = op_modelTbl[modelId].scaleY;
    *scaleZ = op_modelTbl[modelId].scaleZ;
}

void op_ModelDispOff(s32 arg0) {
    Hu3DModelAttrSet(op_modelTbl[arg0].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void op_ModelDispOn(s32 arg0) {
    Hu3DModelAttrSet(op_modelTbl[arg0].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void op_MotionFlagSet(s32 modelId, s16 arg1) {
    Hu3DMotionAttrSet(op_modelTbl[modelId].modelId, -1, arg1);
}

void op_MotionShiftSet(s32 modelId, s32 motionId, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(op_modelTbl[modelId].modelId, op_modelTbl[motionId].motionId, arg2, arg3, arg4);
}

void op_MotionFlagReset(s32 modelId, s16 arg1) {
    Hu3DMotionAttrSet(op_modelTbl[modelId].modelId, arg1, 0);
}

void op_MotionSpeedSet(s32 modelId, f32 speed) {
    Hu3DMotionSpeedSet(op_modelTbl[modelId].modelId, speed);
}

void op_MotionTimeSet(s32 slot, u32 time) {
    Hu3DMotionTimeSet(op_modelTbl[slot].modelId, time);
}

void op_MotionEndWait(s32 slot) {
    while (Hu3DData[op_modelTbl[slot].modelId].motTime !=
           Hu3DMotion[Hu3DData[op_modelTbl[slot].modelId].motId].unk02) {
        HuPrcVSleep();
    }
}

s32 op_MotionEndCheck(s32 arg0) {
    s16 modelId = op_modelTbl[arg0].modelId;

    return Hu3DData[modelId].motTime == Hu3DMotion[Hu3DData[modelId].motId].unk02;
}

void op_MotionSet(s32 modelId, s32 motionId, s16 arg2) {
    s16 model = op_ModelIdGet(modelId);
    s16 motion = op_MotionIdGet(motionId);

    Hu3DMotionSet(model, motion);
    Hu3DMotionAttrSet(model, -1, arg2);
}

void op_BGSprCreate(void) {
    // The original call omits the resource id.
    op_bgAnim = ((s16 (*)())HuSprAnimDataRead)();
    op_bgSpr = espEntry(op_bgAnim, 0, 0);
    espAttrSet(op_bgSpr, 0x4000);
    espPosSet(op_bgSpr, 0xA0, 0x78);
}

void op_BGSprKill(void) {
    espKill(op_bgSpr);
    HuSprAnimKill(op_bgAnim);
}

u32 op_WinMesConv(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = GameMesStrConv2(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

void op_WinCreate(s32 slot, u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window;
    u32 newEvent;

    switch (style) {
        case 1:
            newEvent = op_WinMesConv(event);
            window = op_WinType1Create(newEvent, x, y, width, height, style);
            break;
        case 2:
            newEvent = op_WinMesConv(event);
            window = op_WinType2Create(newEvent, x, y, width, height, style);
            break;
        case 3:
            newEvent = op_WinMesConv(event);
            window = op_WinType3Create(newEvent, x, y, style);
            break;
        case 4:
            newEvent = op_WinMesConv(event);
            window = op_WinType4Create(newEvent, x, y, style);
            break;
        case 5:
            newEvent = op_WinMesConv(event);
            window = op_WinType5Create(newEvent, x, y, style);
            break;
        case 0:
            newEvent = op_WinMesConv(event);
            window = op_WinType0Create(newEvent, x, y, width, height, style);
            break;
        default:
            newEvent = op_WinMesConv(event);
            window = op_WinType0Create(newEvent, x, y, width, height, style);
            break;
    }
    if (0x80000000U < newEvent) {
        op_winTbl[slot].event = (void *)newEvent;
    }
    op_winTbl[slot].espriteSlot = window;
}

s16 op_WinType0Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = HuWinCreate(x, y, width, height, 0, 8);
    HuWinAttrSet(slot, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(slot, 0);
    HuWinBGTPLvlSet(slot, 255);
    HuWinDummy(slot);
    HuWinPriSet(slot, 1);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinMesDefColSet(slot, 192, 192, 192);
    HuWinBGColSet(slot, 0, 64, 64);
    HuWinMesColSet(slot, 7);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinHomeClear(slot);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

s16 op_WinType1Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = HuWinCreate(x, y, width, height, 0, 4);
    HuWinAttrSet(slot, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(slot, 0);
    HuWinBGTPLvlSet(slot, 255);
    HuWinDummy(slot);
    HuWinPriSet(slot, 1);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinMesPalSet(slot, 5, 0, 176, 192);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinMesDefColSet(slot, 192, 192, 192);
    HuWinBGColSet(slot, 255, 255, 255);
    HuWinMesColSet(slot, 1);
    HuWinHomeClear(slot);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

s16 op_WinType2Create(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = HuWinCreate(x, y, width, height, 0, 8);
    HuWinAttrSet(slot, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(slot, 0);
    HuWinDummy(slot);
    HuWinPriSet(slot, 1);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinMesPalSet(slot, 5, 0, 176, 192);
    HuWinMesPalSet(slot, 7, 255, 255, 255);
    HuWinMesPalSet(slot, 0, 0, 0, 0);
    HuWinMesPalSet(slot, 3, 0, 0, 0);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinMesDefColSet(slot, 192, 192, 0);
    HuWinBGColSet(slot, 255, 255, 255);
    HuWinMesColSet(slot, 6);
    HuWinHomeClear(slot);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

s16 op_WinType3Create(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = HuWinExCreateStyled(x, y, 19);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinExOpen(slot, 1);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

s16 op_WinType4Create(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = HuWinExCreateStyled(x, y, 20);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinExOpen(slot, 0);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

s16 op_WinType5Create(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = HuWinExCreateStyled(x, y, 19);
    HuWinMesPalSet(slot, 2, 255, 64, 64);
    HuWinMesPalSet(slot, 4, 96, 255, 64);
    HuWinMesPalSet(slot, 6, 255, 255, 64);
    HuWinActivePlayerSet(slot, HUWIN_PLAYER_1);
    HuWinExOpen(slot, 0);
    HuWinMesSet(slot, event, -1, -1);
    return slot;
}

void op_WinInit(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        op_winTbl[i].espriteSlot = -1;
        op_winTbl[i].event = NULL;
    }
}

void op_WinKill(s32 index) {
    if (op_winTbl[index].unk_08 == 3) {
        HuWinExClose(op_winTbl[index].espriteSlot, 1);
        HuWinExCleanup(op_winTbl[index].espriteSlot);
    } else {
        HuWinDispOff(op_winTbl[index].espriteSlot);
        HuWinKill(op_winTbl[index].espriteSlot);
        op_winTbl[index].espriteSlot = -1;
    }
    if (op_winTbl[index].event != NULL) {
        HuMemDelayFree(op_winTbl[index].event);
        op_winTbl[index].event = NULL;
    }
}

void op_WinKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_winTbl); i++) {
        if (op_winTbl[i].espriteSlot != -1) {
            op_WinKill(i);
        }
    }
}

void op_WinScaleSet(s32 slot, f32 x, f32 y) {
    HuWinScaleSet(op_winTbl[slot].espriteSlot, x, y);
}

void op_WinPosSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinPosSet(op_winTbl[arg0].espriteSlot, arg1, arg2);
}

void op_WinDispOn(s32 slot) {
    HuWinDispOn(op_winTbl[slot].espriteSlot);
}

void op_WinDispOff(s32 slot) {
    HuWinDispOff(op_winTbl[slot].espriteSlot);
}

void op_WinMesSet(s32 slot, u32 event) {
    u32 newEvent;

    HuWinHomeClear(op_winTbl[slot].espriteSlot);
    if (op_winTbl[slot].event != NULL) {
        HuMemDelayFree(op_winTbl[slot].event);
        op_winTbl[slot].event = NULL;
    }
    newEvent = op_WinMesConv(event);
    if (0x80000000U < newEvent) {
        op_winTbl[slot].event = (void *)newEvent;
    }
    HuWinMesSet(op_winTbl[slot].espriteSlot, newEvent, -1, -1);
}

void op_WinInsertMesSet(s32 slot, s8 arg1, s32 arg2) {
    HuWinInsertMesSetNoLF(op_winTbl[slot].espriteSlot, arg2, arg1);
}

s32 op_WinChoiceGet(s32 slot, s16 arg1, s32 arg2) {
    return HuWinChoiceGet(op_winTbl[slot].espriteSlot, arg1, arg2);
}

s16 op_WinIdGet(s32 slot) {
    return op_winTbl[slot].espriteSlot;
}

void op_WinMesWait(s32 index) {
    while (HuWinStatGet(op_winTbl[index].espriteSlot) != 0) {
        HuPrcVSleep();
    }
}

void op_PadBtnWait(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & HuPadBtnDown[0]));
}

void op_WinPriSet(s32 slot, s16 arg1) {
    HuWinPriSet(op_winTbl[slot].espriteSlot, arg1);
}

u16 op_CameraDebugExec(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (HuPadBtnDown[0] & Z_TRIG) {
            camera = Hu3DData[gCameraList[0].unk4].hmf->unkBC;
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
    return HuPadBtnDown[0];
}

void op_DemoEventSetup(void) {
    op_UtilInit();
    op_CameraInit();
    Hu3DCameraViewportSet(0, &op_viewportScale, &op_viewportTrans);
    Hu3DCameraScissorSet(0, &op_scissorRect);
    MBBackArcInit((u32)hvq_data_ROM_START);
    op_DemoObjInit();
    op_CameraShakeInit();
    op_ContErrorCreate();
}

void op_MenuWinCreate(s32 slot, u32 event) {
    op_WinCreate(slot, event, 160, 194, 0, 0, 4);
}

// These constants follow the window-event data in ROM.
const OpDemoStars op_demoStarTbl = { {
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

const Vec op_mesCameraPos = { 600.0f, 80.0f, 800.0f };

const Vec op_mesCameraAt = { 0.0f, 0.0f, -100.0f };

const Vec op_sparkCameraPos = { 0.0f, 0.0f, 2000.0f };

const Vec op_sparkCameraAt = { 0.0f, 0.0f, 0.0f };

void op_DemoEvent(void) {
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

    Hu3DScreenClearF = 1;
    if (omovlevtno == 0) {
        storyMode = 1;
    } else {
        storyMode = omovlevtno == 1;
    }
    op_ContErrorDispOn();
    if (storyMode != 0) {
        HuAudSeqPlay(0x39);
    }
    HuAudFXPlay(0x234);
    MBBackLoad(0x1F);
    MBCameraNearFarSet(10.0f, 10000.0f);
    op_ModelCreate(0xB, 0xF0007, 0x2A9);
    op_ModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
    op_ModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
    op_MotionTimeSet(0xB, 0U);
    op_MotionFlagSet(0xB, 1);
    op_ModelDispOff(0xB);
    {
        OpDemoStars starLayout = op_demoStarTbl;
        s32 firstSprite;
        i = 0;
        op_Rand();
        firstSprite = 1;
        // Keep the explicit back edge for the original stack-address calculation.
    star_loop:
        {
            if (i == 0) {
                op_SprBGCreate(0, 0xF0009);
            } else if (i == firstSprite) {
                op_SprBGCreate(1, 0xF000A);
            } else {
                if (i & 1) {
                    op_EspCreate(i, 0);
                } else {
                    op_EspCreate(i, 1);
                }
                op_SprAttrSet(i, 0x4000U);
                op_SprBankSet(i, 0U, op_RandMod(6U) & 0xFFFF);
            }
            op_SprPosSet(i, starLayout.stars[i].x, starLayout.stars[i].y);
            espColorSet(op_EspIdGet(i) & 0xFFFF, 0xFF, 0xFF, 0xFF);
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
        sp20 = op_mesCameraPos;
        sp30 = op_mesCameraAt;
        MBCameraKill();
        op_CameraObjCreate(&sp20, &sp30);
        if (storyMode != 0) {
            op_MenuWinCreate(0, 0x5A00U);
            op_WinMesSet(0, 0x4D01U);
            op_WinMesWait(0);
        } else {
            op_MenuWinCreate(0, 0x5A00U);
            op_WinMesSet(0, 0x4D00U);
            op_Sleep(0x3C);
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x235);
        }
        op_SparkTrailExec(0.0f, 0.0f, 0.0f, 0.0f);
        sp40 = op_sparkCameraPos;
        sp50 = op_sparkCameraAt;
        op_CameraObjCreate(&sp40, &sp50);
        op_ModelDispOn(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x236);
        }
        op_MotionFlagReset(0xB, 3);
        op_MotionEndWait(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x237);
        }
        op_WipeWhiteOutCreate(0xF, 0x14);
        HuPrcSleep(0x32);
        op_ModelKill(0xB);
        op_ModelCreate(0xB, 0xA0122, 0x2A9);
        op_ModelPosSet(0xB, 0.0f, 0.0f, 0.0f);
        op_ModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
        op_MotionCreate(0x6C, 0xA0123, 0);
        op_MotionCreate(0x6D, 0xA0124, 0);
        op_MotionCreate(0x6E, 0xA012B, 0);
        op_MotionSet(0xB, 0x6D, 1);
        op_MotionFlagSet(0xB, 1);
        op_MotionTimeSet(0xB, 1U);
        AuraCreateEx(op_ModelIdGet(0xB), -5);
        op_DemoStarWaitCreate(0, 0xB, 0.0f, 0.0f, 0.0f, 50.0f, 0x2D);
        op_WipeWhiteInCreate(0xF, 0x10);
        HuPrcSleep(0x10);
        HuPrcSleep(0x14);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D03U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D02U);
            op_Sleep(0x78);
        }
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D05U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D04U);
            op_Sleep(0x78);
        }
        op_WinMesSet(0, 0x4D06U);
        op_DemoObjKill(0);
        temp_s1 = &Hu3DData[op_ModelIdGet(0xB)];
        mtxCopy(savedMatrix, temp_s1->mtx);
        spinAngle = 0.0f;
        op_MotionShiftSet(0xB, 0x6E, 4, 4, (s16)2);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D07U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D06U);
            op_Sleep(0x78);
        }
        op_WinDispOff(0);
        op_MotionFlagSet(0xB, 1);
        if (storyMode != 0) {
            HuAudFXPlay(0x238);
        }
        op_ModelPosGet(0xB, &sp60.x, &sp60.y, &sp60.z);
        HuVecCopyXYZ(&sp70, -1000.0f, -2000.0f, 0.0f);
        for (i = 0; i < 0x1E; i++) {
            temp_f4 = (f32)i * 0.033333335f;
            HuVecCopyXYZ(&sp80, ((sp70.x - sp60.x) * temp_f4) + sp60.x, ((sp70.y - sp60.y) * temp_f4 * temp_f4) + sp60.y, ((sp70.z - sp60.z) * temp_f4) + sp60.z);
            op_ModelPosSet(0xB, sp80.x, sp80.y, sp80.z);
            spinAngle += 17.23f;
            if (spinAngle > 360.0f) {
                spinAngle -= 360.0f;
            }
            temp_s1->rot.z = spinAngle;
            HuPrcVSleep();
        }
        temp_s1 = &Hu3DData[op_ModelIdGet(0xB)];
        mtxCopy(temp_s1->mtx, savedMatrix);
        HuPrcSleep(0x10);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D09U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D08U);
            op_Sleep(0x3C);
        }
        op_WipeOutCreate(0xF, 0x14);
        if (storyMode != 0) {
            HuAudSeqFadeOut(0x17);
        }
        HuAudFXAllFadeOut(0x17);
        HuPrcSleep(0x17);
        op_WinDispOff(0);
        for (i = 0; i < 0xA; i++) {
            op_SprKill(i);
        }
        op_ModelKill(0x6E);
        MBBackKill();
        MBBackLoad(0x20);
        MBCameraKill();
        Hu3DCameraPerspectiveSet(0, 40.0f, 500.0f, 8000.0f);
        op_CameraObjCreate(&op_cameraMainTbl[0], &op_cameraMainTbl[1]);
        op_ModelDispOff(0xB);
        op_DemoCharCreate(0, 0x200A0, 19.0f, 0.0f, 2700.0f);
        op_ModelRotSet(0, 0.0f, -30.0f, 0.0f);
        temp_v0_2 = op_ModelIdGet(0);
        CharAnimCreate(temp_v0_2, 2, 0, 0x200A4);
        CharAnimFrameSet(temp_v0_2, 2, 0, 1, (s16)0);
        op_DemoShadowCreate(0x20, 19.0f, 0.0f, 2700.0f);
        op_DemoCharCreate(1, 0x300A0, -250.0f, 0.0f, 2920.5f);
        temp_v0_3 = op_ModelIdGet(1);
        CharAnimCreate(temp_v0_3, 2, 1, 0x300A4);
        CharAnimFrameSet(temp_v0_3, 2, 1, 7, (s16)0);
        op_DemoShadowCreate(0x21, -250.0f, 0.0f, 2920.5f);
        op_ModelDispOff(1);
        op_DemoCharCreate(2, 0x700A0, 140.0f, 0.0f, 2680.0f);
        temp_v0_4 = op_ModelIdGet(2);
        CharAnimCreate(temp_v0_4, 2, 2, 0x700A4);
        CharAnimFrameSet(temp_v0_4, 2, 2, 3, (s16)0);
        op_DemoShadowCreate(0x22, 140.0f, 0.0f, 2680.0f);
        op_ModelScaleSet(0x22, 1.5f, 1.0f, 1.5f);
        op_ModelDispOff(2);
        op_DemoCharCreate(3, 0x400A0, 240.0f, 0.0f, 2680.0f);
        temp_v0_5 = op_ModelIdGet(3);
        CharAnimCreate(temp_v0_5, 2, 3, 0x400A4);
        CharAnimFrameSet(temp_v0_5, 2, 3, 6, (s16)0);
        op_DemoShadowCreate(0x23, 240.0f, 0.0f, 2680.0f);
        op_ModelDispOff(3);
        op_ModelDispOff(0x23);
        op_DemoCharCreate(4, 0x500A0, -240.0f, 0.0f, 2760.0f);
        temp_v0_6 = op_ModelIdGet(4);
        CharAnimCreate(temp_v0_6, 2, 4, 0x500A4);
        CharAnimFrameSet(temp_v0_6, 2, 4, 9, (s16)0);
        op_DemoShadowCreate(0x24, 240.0f, 0.0f, 2680.0f);
        op_ModelDispOff(4);
        op_ModelDispOff(0x24);
        op_DemoCharCreate(5, 0x600A0, -140.0f, 0.0f, 2710.0f);
        temp_v0_7 = op_ModelIdGet(5);
        CharAnimCreate(temp_v0_7, 2, 5, 0x600A4);
        CharAnimFrameSet(temp_v0_7, 2, 5, 7, (s16)0);
        op_DemoShadowCreate(0x25, -140.0f, 0.0f, 2710.0f);
        op_ModelScaleSet(0x25, 1.5f, 1.0f, 1.5f);
        op_ModelDispOff(5);
        op_ModelDispOff(0x25);
        op_ModelCreate(6, 0xF0004, 0x6A9);
        op_ModelPosSet(6, -77.25f, 40.0f, 2632.5f);
        op_ModelScaleSet(6, 1.0f, 1.0f, 1.0f);
        op_ModelPosSet(0x21, -77.25f, 0.0f, 2632.5f);
        op_ModelCreate(7, 0xF0003, 0x6A9);
        op_ModelPosSet(7, 19.0f, 15.0f, 2700.0f);
        op_ModelRotSet(7, 0.0f, -30.0f, 0.0f);
        op_ModelScaleSet(7, 1.0f, 1.0f, 1.0f);
        op_ModelPosSet(0x22, 19.0f, 15.0f, 2700.0f);
        op_ModelCreate(8, 0xF0005, 0x6A9);
        op_ModelPosSet(8, -51.0f, 92.5f, 2651.25f);
        op_ModelScaleSet(8, 1.0f, 1.0f, 1.0f);
        op_ModelCreate(9, 0xF0002, 0x2A9);
        op_ModelPosSet(9, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(9, 1.0f, 1.0f, 1.0f);
        op_ModelCreate(0xA, 0xA015E, 0xAA9);
        op_ModelPosSet(0xA, -430.0f, 60.0f, 2605.0f);
        op_ModelScaleSet(0xA, 0.3f, 0.3f, 0.3f);
        op_MotionFlagSet(0xA, 2);
        op_DemoFlyCreate(0xC, 0xA, -340.0f, 60.0f, 2555.0f);
        op_ModelCreate(0x1A, 0xB0001, 0x6A9);
        op_ModelPosSet(0x1A, -400.0f, 25.0f, 2650.0f);
        op_ModelScaleSet(0x1A, 1.8f, 1.0f, 1.8f);
        op_MotionTimeSet(0x1A, 0U);
        op_MotionFlagSet(0x1A, 1);
        op_ModelDispOff(0x1A);
        op_ModelCreate(0x1B, 0xA015E, 0xAA9);
        op_ModelPosSet(0x1B, 0.0f, 100.0f, 100.0f);
        op_ModelScaleSet(0x1B, 0.3f, 0.3f, 0.3f);
        op_MotionFlagSet(0x1B, 2);
        op_DemoFlyCreate(0xB, 0x1B, -340.0f, 80.0f, 3100.0f);
        op_MotionCreate(0x28, 0x20000, 0);
        op_MotionCreate(0x29, 0x20001, 0);
        op_MotionCreate(0x2A, 0xF000B, 0);
        op_MotionCreate(0x2B, 0xF000C, 0);
        op_MotionCreate(0x2C, 0x2001B, 0);
        op_MotionCreate(0x2D, 0x1D003B, 0);
        op_MotionCreate(0x2E, 0xF000D, 0);
        op_MotionCreate(0x2F, 0xF000E, 0);
        op_MotionCreate(0x32, 0xF0010, 0);
        op_MotionCreate(0x33, 0x2009C, 0);
        op_MotionCreate(0x34, 0xF0011, 0);
        op_MotionCreate(0x35, 0x2009B, 0);
        op_MotionCreate(0x38, 0x30000, 0);
        op_MotionCreate(0x39, 0x30001, 0);
        op_MotionCreate(0x3A, 0xF0012, 0);
        op_MotionCreate(0x3C, 0x3007A, 0);
        op_MotionCreate(0x3D, 0x3009C, 0);
        op_MotionCreate(0x3E, 0x3009B, 0);
        op_MotionCreate(0x40, 0x70000, 0);
        op_MotionCreate(0x41, 0x70001, 0);
        op_MotionCreate(0x42, 0x1D0053, 0);
        op_MotionCreate(0x43, 0xF0014, 0);
        op_MotionCreate(0x46, 0x7009C, 0);
        op_MotionCreate(0x47, 0x7009B, 0);
        op_MotionCreate(0x48, 0x40000, 0);
        op_MotionCreate(0x49, 0x40001, 0);
        op_MotionCreate(0x4A, 0xF0015, 0);
        op_MotionCreate(0x4D, 0x4009C, 0);
        op_MotionCreate(0x4E, 0x40032, 0);
        op_MotionCreate(0x4F, 0x4009B, 0);
        op_MotionCreate(0x50, 0x50000, 0);
        op_MotionCreate(0x51, 0x50001, 0);
        op_MotionCreate(0x52, 0xF0016, 0);
        op_MotionCreate(0x55, 0x5009C, 0);
        op_MotionCreate(0x56, 0x50033, 0);
        op_MotionCreate(0x57, 0x5009B, 0);
        op_MotionCreate(0x58, 0x60000, 0);
        op_MotionCreate(0x59, 0x60001, 0);
        op_MotionCreate(0x5A, 0xF0018, 0);
        op_MotionCreate(0x5B, 0xF0019, 0);
        op_MotionCreate(0x5E, 0x6009C, 0);
        op_MotionCreate(0x5F, 0xF001B, 0);
        op_MotionCreate(0x60, 0x6009B, 0);
        op_ModelDispOn(0xB);
        op_ModelPosSet(0xB, 920.0f, 2060.0f, 2580.0f);
        op_ModelRotSet(0xB, 0.0f, 45.0f, 0.0f);
        op_ModelScaleSet(0xB, 2.5f, 2.5f, 2.5f);
        op_MotionFlagSet(0xB, 1);
        op_MotionSet(0xB, 0x6D, 1);
        op_MotionFlagSet(0xB, 1);
        op_MotionTimeSet(0xB, 1U);
        op_MotionSet(0, 0x2A, 2);
        op_WipeInCreate(0xF, 0x10);
        HuPrcSleep(8);
        if (storyMode == 0) {
            HuAudSeqPlay(1);
        }
        HuPrcSleep(8);
        if (storyMode != 0) {
            HuAudSeqPlay(0x3A);
        }
        HuPrcSleep(0x1E);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D0BU);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D0AU);
            op_Sleep(0x3C);
        }
        op_MotionShiftSet(0, 0x2B, 4, 4, 0);
        op_MotionEndWait(0);
        op_MotionShiftSet(0, 0x32, 4, 4, (s16)2);
        HuPrcSleep(0x14);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D0DU);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D0CU);
            op_Sleep(0x1C);
        }
        op_WinDispOff(0);
        op_ModelPosGet(0xB, &sp90.x, &sp90.y, &sp90.z);
        HuVecCopyXYZ(&spA0, -580.0f, 60.0f, 2580.0f);
        for (i = 0; i < 0x11; i++) {
            temp_f20 = (f32)i * 0.0625f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * temp_f20) + sp90.x, ((spA0.y - sp90.y) * temp_f20) + sp90.y, ((spA0.z - sp90.z) * temp_f20) + sp90.z);
            op_ModelPosSet(0xB, spB0.x, spB0.y, spB0.z);
            HuPrcVSleep();
            if (i == 0xE) {
                op_ModelDispOn(0x1A);
                op_MotionTimeSet(0x1A, 0U);
                op_MotionFlagReset(0x1A, 1);
            }
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x239);
        }
        op_DemoFlyAwaySet(0xB, -1580.0f, 600.0f, 3430.0f, 0x28);
        op_DemoFlyAwaySet(0xC, -780.0f, 590.0f, 3430.0f, 0x28);
        op_CameraShakeCreate(0xC, 4.0f);
        op_MotionShiftSet(0, 0x2C, 4, 4, (s16)2);
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
                op_ModelPosSet(0, spB0.x, spB0.y, spB0.z);
                op_ModelPosSet(0x20, spB0.x, 0.0f, spB0.z);
                op_ModelScaleSet(0x20, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                op_ModelIdGet(0);
                op_ModelRotSet(0, rotations[0].x, rotations[0].y, rotations[0].z);
                var_f0 = rotations[0].x + 33.0f;
                if (!(var_f0 < 360.0f)) {
                    var_f0 -= 360.0f;
                }
                rotations[0].x = var_f0;
                HuVecCopyXYZ(&sp90, -77.25f, 40.0f, 2632.5f);
                HuVecCopyXYZ(&spA0, 922.75f, 1540.0f, 2632.5f);
                HuVecCopyXYZ(&spB0, ((spA0.x - sp90.x) * launchProgress) + sp90.x, ((spA0.y - sp90.y) * launchProgress) + sp90.y, ((spA0.z - sp90.z) * launchProgress) + sp90.z);
                op_ModelPosSet(6, spB0.x, spB0.y, spB0.z);
                op_ModelPosSet(0x21, spB0.x, 0.0f, spB0.z);
                op_ModelScaleSet(0x21, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                op_ModelIdGet(6);
                op_ModelRotSet(6, rotations[1].x, rotations[1].y, rotations[1].z);
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
                op_ModelPosSet(7, spB0.x, spB0.y, spB0.z);
                op_ModelPosSet(0x22, spB0.x, 0.0f, spB0.z);
                op_ModelScaleSet(0x22, 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f), 1.0f - (launchProgress * 0.9f));
                op_ModelIdGet(7);
                op_ModelRotSet(7, rotations[2].x, rotations[2].y, rotations[2].z);
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
                op_ModelPosSet(8, spB0.x, spB0.y, spB0.z);
                op_ModelIdGet(8);
                op_ModelRotSet(8, rotations[3].x, rotations[3].y, rotations[3].z);
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
            op_ModelKill(0x1A);
            HuPrcSleep(3);
            op_MotionShiftSet(0, 0x34, 4, 4, (s16)2);
            op_MotionShiftSet(1, 0x39, 4, 4, (s16)2);
            op_MotionShiftSet(2, 0x41, 4, 4, (s16)2);
            op_MotionShiftSet(3, 0x49, 4, 4, (s16)2);
            op_MotionShiftSet(4, 0x51, 4, 4, (s16)2);
            op_MotionShiftSet(5, 0x59, 4, 4, (s16)2);
            op_MotionSpeedSet(1, 1.6f);
            op_MotionSpeedSet(2, 1.6f);
            op_MotionSpeedSet(3, 1.6f);
            op_MotionSpeedSet(4, 1.6f);
            op_MotionSpeedSet(5, 1.6f);
            op_ModelDispOn(1);
            op_ModelDispOn(2);
            op_ModelDispOn(3);
            op_ModelDispOn(4);
            op_ModelDispOn(5);
            op_ModelDispOn(0x20);
            op_ModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
            op_ModelDispOn(0x21);
            op_ModelScaleSet(0x21, 1.0f, 1.0f, 1.0f);
            op_ModelDispOn(0x22);
            op_ModelScaleSet(0x22, 1.0f, 1.0f, 1.0f);
            op_ModelDispOn(0x23);
            op_ModelDispOn(0x24);
            op_ModelDispOn(0x25);
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
                op_WinDispOn(0);
                op_WinMesSet(0, 0x4D0EU);
            }
            HuVecCopyXYZ(&sp100, 1519.0f, 0.0f, 2700.0f);
            HuVecCopyXYZ(&sp110, 62.5f, 0.0f, 2775.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(0, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x20, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            op_ModelRotSet(0, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, -850.0f, 0.0f, 3920.5f);
            HuVecCopyXYZ(&sp110, -300.0f, 0.0f, 2920.5f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(1, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x21, sp130.x, 0.0f, sp130.z);
            op_ModelRotSet(1, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, (sp110.x - sp100.x) + sp130.x, (sp110.z - sp100.z) + sp130.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1640.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp110, 120.0f, 0.0f, 2505.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(2, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x22, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            op_ModelRotSet(2, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1740.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp110, 240.0f, 0.0f, 2680.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(3, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x23, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            op_ModelRotSet(3, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 960.0f, 0.0f, 3360.0f);
            HuVecCopyXYZ(&sp110, -190.0f, 0.0f, 2775.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(4, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x24, sp130.x, 0.0f, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            op_ModelRotSet(4, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuVecCopyXYZ(&sp100, 1160.0f, 0.0f, 3310.0f);
            HuVecCopyXYZ(&sp110, -140.0f, 0.0f, 2575.0f);
            HuVecCopyXYZ(&sp130, ((sp110.x - sp100.x) * runProgress) + sp100.x, ((sp110.y - sp100.y) * runProgress) + sp100.y, ((sp110.z - sp100.z) * runProgress) + sp100.z);
            op_ModelPosSet(5, sp130.x, sp130.y, sp130.z);
            op_ModelPosSet(0x25, sp130.x, sp130.y, sp130.z);
            HuVecCopyXYZ(&sp110, -580.0f, 60.0f, 2580.0f);
            op_ModelRotSet(5, 0.0f, op_CameraAngleCalc(sp130.x, sp130.z, sp110.x, sp110.z), 0.0f);
            HuPrcVSleep();
            frame++;
        } while (frame < 0x79);
        op_MotionSpeedSet(0, 1.0f);
        op_MotionSpeedSet(1, 1.0f);
        op_MotionSpeedSet(2, 1.0f);
        op_MotionSpeedSet(3, 1.0f);
        op_MotionSpeedSet(4, 1.0f);
        op_MotionSpeedSet(5, 1.0f);
        op_MotionShiftSet(0, 0x28, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuVecCopyXYZ(&sp100, -850.0f, 0.0f, 3920.5f);
        HuVecCopyXYZ(&sp110, -300.0f, 0.0f, 2920.5f);
        op_ModelPosGet(1, &sp130.x, &sp130.y, &sp130.z);
        HuVecCopyXYZ(&sp110, (sp110.x - sp100.x) + sp130.x, 0.0f, (sp110.z - sp100.z) + sp130.z);
        op_ModelPosGet(1, &sp100.x, &sp100.y, &sp100.z);
        op_ModelPosGet(0xB, &sp120.x, &sp120.y, &sp120.z);
        op_MotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        for (i = 0; i < 9; i++) {
            turnProgress = (f32)i * 0.125f;
            op_ModelRotSet(1, 0.0f, op_DirLerp(sp110.x - sp100.x, sp110.z - sp100.z, sp120.x - sp100.x, sp120.z - sp100.z, turnProgress), 0.0f);
            HuPrcVSleep();
        }
        op_MotionShiftSet(1, 0x3A, 4, 4, (s16)2);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D0FU);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D0EU);
            op_Sleep(0x5A);
        }
        op_WinDispOff(0);
        HuPrcSleep(0x14);
        op_MotionShiftSet(0, 0x33, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x46, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x55, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        frame = 0;
        do {
            temp_f20 = (f32)frame * 0.0625f;
            op_ModelPosGet(4, &sp110.x, &sp110.y, &sp110.z);
            op_ModelPosGet(0, &sp100.x, &sp100.y, &sp100.z);
            op_ModelRotGet(0, &sp130.x, &sp130.y, &sp130.z);
            op_ModelRotSet(0, 0.0f, op_AngleLerp(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            op_ModelPosGet(3, &sp110.x, &sp110.y, &sp110.z);
            op_ModelPosGet(2, &sp100.x, &sp100.y, &sp100.z);
            op_ModelRotGet(2, &sp130.x, &sp130.y, &sp130.z);
            op_ModelRotSet(2, 0.0f, op_AngleLerp(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            op_ModelPosGet(2, &sp110.x, &sp110.y, &sp110.z);
            op_ModelPosGet(3, &sp100.x, &sp100.y, &sp100.z);
            op_ModelRotGet(3, &sp130.x, &sp130.y, &sp130.z);
            op_ModelRotSet(3, 0.0f, op_AngleLerp(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            op_ModelPosGet(0, &sp110.x, &sp110.y, &sp110.z);
            op_ModelPosGet(4, &sp100.x, &sp100.y, &sp100.z);
            op_ModelRotGet(4, &sp130.x, &sp130.y, &sp130.z);
            op_ModelRotSet(4, 0.0f, op_AngleLerp(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            HuVecCopyXYZ(&sp110, -60.0f, 0.0f, 2775.0f);
            op_ModelPosGet(5, &sp100.x, &sp100.y, &sp100.z);
            op_ModelRotGet(5, &sp130.x, &sp130.y, &sp130.z);
            op_ModelRotSet(5, 0.0f, op_AngleLerp(sp130.y, sp110.x - sp100.x, sp110.z - sp100.z, temp_f20), 0.0f);
            HuPrcVSleep();
            frame++;
        } while (frame < 0x11);
        op_MotionShiftSet(0, 0x28, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(0, 0x2D, 8, 8, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(1, 0x3A, 8, 8, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(2, 0x42, 8, 8, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(3, 0x4A, 8, 8, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(4, 0x52, 8, 8, (s16)2);
        HuPrcSleep(4);
        op_MotionShiftSet(5, 0x5A, 8, 8, (s16)2);
        HuPrcSleep(0x14);
        op_WinDispOff(0);
        HuPrcSleep(0x1E);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D11U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D10U);
            op_Sleep(0x64);
        }
        HuPrcSleep(0xA);
        op_DemoObjKill(0xB);
        op_DemoObjKill(0xC);
        op_ModelKill(0xA);
        op_ModelKill(0x1B);
        op_ModelKill(6);
        op_ModelKill(7);
        op_ModelKill(8);
        op_ModelKill(0x2A);
        op_ModelKill(0x2B);
        op_ModelKill(0x2C);
        op_ModelKill(0x32);
        op_ModelKill(0x34);
        HuPrcSleep(3);
        op_WinDispOff(0);
        MBBackKill();
        MBBackLoad(0x21);
        MBCameraKill();
        Hu3DCameraPerspectiveSet(0, 40.0f, 500.0f, 8000.0f);
        op_CameraObjCreate(&op_cameraFarTbl[0], &op_cameraFarTbl[1]);
        op_ModelCreate(0xC, 0xA0089, 0x6A9);
        op_ModelPosSet(0xC, 4340.0f, 4720.0f, 5925.0f);
        op_ModelScaleSet(0xC, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0xC, 2);
        op_ModelCreate(0xD, 0xF0001, 0x6A9);
        op_ModelPosSet(0xD, 4340.0f, 4720.0f, 5925.0f);
        op_ModelScaleSet(0xD, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0xD, 2);
        op_ModelCreate(0xE, 0xF0000, 0x6A9);
        op_ModelPosSet(0xE, 4340.0f, 4720.0f, 5925.0f);
        op_ModelScaleSet(0xE, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0xE, 1);
        temp_s1_2 = op_ModelIdGet(0xD);
        temp_v0_9 = op_ModelIdGet(0xE);
        Hu3DModelAttrSet(temp_v0_9, 0x4000, 0x4000);
        Hu3DModelHookSet(temp_v0_9, temp_s1_2, "hook");
        if (storyMode != 0) {
            HuAudFXPlay(0x23A);
        }
        for (i = 1; i < 0x74; i++) {
            approachTarget = op_cameraFarTbl;
            temp_f20 = (f32)i * 0.008333334f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            temp_f22 = 0.5f;
            temp_f24 = 0.0f;
            if (i == 0x21) {
                op_WinDispOn(0);
                op_WinMesSet(0, 0x4D12U);
            }
            HuVecCopyXYZ(&sp140, 4340.0f, 4420.0f, 5925.0f);
            HuVecCopyXYZ(&sp150, approachTarget->x - 10.0f, approachTarget->y + 40.0f, approachTarget->z - 20.0f);
            sp150.y += (temp_f20 - temp_f22) * 1600.0f * (temp_f20 - temp_f22);
            // The normalized camera yaw is unused.
            approachYaw = op_CameraAngleCalc(approachTarget->x, approachTarget->z, approachTarget[1].x, approachTarget[1].z);
            if (approachYaw < temp_f24) {
                approachYaw += 360.0f;
            }
            HuVecCopyXYZ(&sp160, ((sp150.x - sp140.x) * temp_f20) + sp140.x, ((sp150.y - sp140.y) * temp_f20) + sp140.y, ((sp150.z - sp140.z) * temp_f20) + sp140.z);
            temp_f20 = op_CameraAngleCalc(approachTarget->x, approachTarget->z, sp150.x, sp150.z);
            op_ModelRotSet(0xC, 0.0f, temp_f20, 0.0f);
            op_ModelRotSet(0xD, 0.0f, temp_f20, 0.0f);
            op_ModelPosSet(0xC, sp160.x, sp160.y, sp160.z);
            op_ModelPosSet(0xD, sp160.x, sp160.y, sp160.z);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D13U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D12U);
            op_Sleep(0x28);
        }
        op_WinDispOff(0);
        op_ModelDispOff(0xC);
        op_ModelDispOff(0xD);
        op_ModelDispOff(0xE);
        MBBackKill();
        MBBackLoad(0x20);
        MBCameraKill();
        Hu3DCameraPerspectiveSet(0, 40.0f, 500.0f, 8000.0f);
        op_CameraObjCreate(&op_cameraMainTbl[0], &op_cameraMainTbl[1]);
        op_ModelCreate(6, 0xF0006, 0x6A9);
        op_ModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        op_ModelPosSet(6, sp170.x, sp170.y, sp170.z);
        op_ModelScaleSet(6, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(6, 1);
        op_MotionTimeSet(6, 0U);
        op_ModelDispOn(6);
        op_ModelCreate(0x2B, 0xF0006, 0x6A9);
        op_ModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        op_ModelPosSet(6, sp170.x, 150.0f, sp170.z);
        op_ModelScaleSet(0x2B, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x2B, 1);
        op_MotionTimeSet(0x2B, 0U);
        op_ModelDispOff(0x2B);
        op_ModelCreate(0xF, 0xA0075, 0x6A9);
        op_ModelPosGet(0xE, &sp170.x, &sp170.y, &sp170.z);
        op_ModelPosSet(0xF, sp170.x, sp170.y, sp170.z);
        op_ModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0xF, 1);
        op_ModelDispOff(0xF);
        op_MotionCreate(0x68, 0xA0076, 0);
        op_MotionCreate(0x69, 0xA0077, 0);
        op_MotionCreate(0x6A, 0xA0078, 0);
        op_MotionSet(0xF, 0x69, 1);
        op_MotionTimeSet(0xF, 0U);
        op_ModelPosGet(4, &sp170.x, &sp170.y, &sp170.z);
        temp_f4_2 = sp170.x - 50.0f;
        sp170.x = temp_f4_2;
        temp_f2_2 = sp170.z + 25.0f;
        sp170.z = temp_f2_2;
        op_ModelPosSet(4, temp_f4_2, sp170.y, temp_f2_2);
        op_ModelPosSet(0x24, sp170.x, sp170.y, sp170.z);
        op_ModelDispOn(0xC);
        op_ModelDispOn(0xD);
        op_ModelDispOn(0xE);
        op_MotionTimeSet(0xD, 0U);
        op_MotionSet(0, 0x33, 2);
        op_MotionSet(2, 0x46, 2);
        op_MotionSet(3, 0x4D, 2);
        op_MotionSet(4, 0x55, 2);
        op_MotionSet(5, 0x5E, 2);
        sp1A0.x = sp1A0.y = sp1A0.z = 0.0f;
        op_DemoShadowCreate(0x1D, 0.0f, 0.0f, 0.0f);
        op_DemoShadowCreate(0x1E, sp1A0.x, sp1A0.y, sp1A0.z);
        op_ModelDispOff(0x1E);
        HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
        HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
        i = 0;
        temp_f0_5 = op_CameraAngleCalc(sp180.x, sp180.z, sp190.x, sp190.z);
        angles.targetYaw = temp_f0_5;
        op_ModelRotSet(0xC, 0.0f, temp_f0_5, 0.0f);
        op_ModelRotSet(0xD, 0.0f, angles.targetYaw, 0.0f);
        do {
            temp_f22 = (f32)i * 0.004166667f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            op_ModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosSet(0x1D, sp1A0.x, 0.0f, sp1A0.z);
            temp_f26 = 0.5f;
            op_ModelScaleSet(0x1D, temp_f26, temp_f26, temp_f26);
            op_ModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            op_ModelScaleSet(0x1E, temp_f26, temp_f26, temp_f26);
            op_ModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            distance = 360.0f;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            op_ModelRotSet(0, 0.0f, angles.targetYaw, 0.0f);
            op_ModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_8 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_8;
            op_ModelRotSet(2, 0.0f, temp_f0_8, 0.0f);
            op_ModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_10 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_10;
            op_ModelRotSet(3, 0.0f, temp_f0_10, 0.0f);
            op_ModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_12 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_12;
            op_ModelRotSet(4, 0.0f, temp_f0_12, 0.0f);
            op_ModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + distance;
            }
            temp_f0_14 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_14;
            op_ModelRotSet(5, 0.0f, temp_f0_14, 0.0f);
            HuPrcVSleep();
            if (i == 0x2C) {
                op_MotionShiftSet(0, 0x35, 8, 0x10, (s16)2);
                op_MotionShiftSet(2, 0x47, 8, 0x10, (s16)2);
                op_MotionShiftSet(3, 0x4F, 8, 0x10, (s16)2);
                op_MotionShiftSet(4, 0x57, 8, 0x10, (s16)2);
                op_MotionShiftSet(5, 0x60, 8, 0x10, (s16)2);
            }
            i += 2;
        } while (i < 0x68);
        Hu3DModelAttrSet(op_ModelIdGet(0xE), 0x4000, 0);
        op_ModelRotGet(0xD, &sp1B0.x, &sp1B0.y, &sp1B0.z);
        op_ModelRotSet(0xE, sp1B0.x, sp1B0.y, sp1B0.z);
        temp_f22 = sp1B0.y;
        op_ModelPosGet(0xD, &sp1B0.x, &sp1B0.y, &sp1B0.z);
        sp1B0.x = (f32)((f64)sp1B0.x + ((f64)sindf(temp_f22) * 142.0));
        sp1B0.y += -108.0f;
        temp_f2_3 = (f32)((f64)sp1B0.z + ((f64)cosdf(temp_f22) * 142.0));
        sp1B0.z = temp_f2_3;
        op_ModelPosSet(0xE, sp1B0.x, sp1B0.y, temp_f2_3);
        op_ModelDispOff(0xD);
        op_MotionShiftSet(0, 0x33, 8, 8, (s16)2);
        op_MotionShiftSet(2, 0x46, 8, 8, (s16)2);
        op_MotionShiftSet(3, 0x4D, 8, 8, (s16)2);
        op_MotionShiftSet(4, 0x55, 8, 8, (s16)2);
        op_MotionShiftSet(5, 0x5E, 8, 8, (s16)2);
        op_MotionSpeedSet(0, 0.3f);
        op_MotionSpeedSet(2, 0.3f);
        op_MotionSpeedSet(3, 0.3f);
        op_MotionSpeedSet(4, 0.3f);
        op_MotionSpeedSet(5, 0.3f);
        op_ModelDispOn(0x1E);
        op_ModelRotGet(0xE, &angles.rot.x, &angles.rot.y, &angles.rot.z);
        i = 0x68;
        var_s1 = 0;
        do {
            if (var_s1 == 0x14) {
                op_MotionFlagReset(0xE, 1);
                if (storyMode != 0) {
                    HuAudFXPlay(0x23B);
                }
            }
            temp_f22 = (f32)var_s1 * 0.05f;
            temp_f22 = temp_f22 > 1.0f ? 1.0f : temp_f22;
            HuVecCopyXYZ(&sp1A0, sp1B0.x, (temp_f22 * temp_f22 * (97.5f - sp1B0.y)) + sp1B0.y, sp1B0.z);
            op_ModelPosSet(0xE, sp1A0.x, sp1A0.y, sp1A0.z);
            temp_f0_15 = op_AngleLerp(angles.rot.y, -(op_cameraMainTbl[0].x - sp1A0.x), -(op_cameraMainTbl[0].z - sp1A0.z), temp_f22);
            angles.rot.y = temp_f0_15;
            op_ModelRotSet(0xE, 0.0f, temp_f0_15, 0.0f);
            op_ModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            op_ModelScaleSet(0x1E, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f);
            temp_f22 = (f32)i * 0.004166667f;
            temp_f20 = (f32)(i - 0x68) * 0.007352941f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            sp190.y += temp_f20 * 800.0f * temp_f20;
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            op_ModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosSet(0x1D, sp1A0.x, 0.0f, sp1A0.z);
            op_ModelScaleSet(0x1D, 0.5f, 0.5f, 0.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * 0.5f) + sp180.x, ((sp190.y - sp180.y) * 0.5f) + sp180.y, ((sp190.z - sp180.z) * 0.5f) + sp180.z);
            op_ModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_18 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_18;
            op_ModelRotSet(0, 0.0f, temp_f0_18, 0.0f);
            op_ModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_20 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_20;
            op_ModelRotSet(2, 0.0f, temp_f0_20, 0.0f);
            op_ModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_22 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_22;
            op_ModelRotSet(3, 0.0f, temp_f0_22, 0.0f);
            op_ModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_24 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_24;
            op_ModelRotSet(4, 0.0f, temp_f0_24, 0.0f);
            op_ModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            i += 2;
            temp_f0_26 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_26;
            op_ModelRotSet(5, 0.0f, temp_f0_26, 0.0f);
            var_s1 += 1;
            HuPrcVSleep();
        } while (i < 0xA0);
        i = 0xA0;
        do {
            temp_f22 = (f32)var_s1 * 0.05f;
            if (var_s1 == 0x14) {
                op_MotionFlagReset(0xE, 1);
                if (storyMode != 0) {
                    HuAudFXPlay(0x23B);
                }
            }
            if (temp_f22 > 1.0f) {
                temp_f22 = 1.0f;
            }
            HuVecCopyXYZ(&sp1A0, sp1B0.x, (temp_f22 * temp_f22 * (97.5f - sp1B0.y)) + sp1B0.y, sp1B0.z);
            op_ModelPosSet(0xE, sp1A0.x, sp1A0.y, sp1A0.z);
            temp_f0_27 = op_AngleLerp(angles.rot.y, -(op_cameraMainTbl[0].x - sp1A0.x), -(op_cameraMainTbl[0].z - sp1A0.z), temp_f22);
            angles.rot.y = temp_f0_27;
            op_ModelRotSet(0xE, 0.0f, temp_f0_27, 0.0f);
            op_ModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            op_ModelScaleSet(0x1E, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f, (temp_f22 * 0.5f) + 0.5f);
            temp_f22 = (f32)i * 0.004166667f;
            temp_f20 = (f32)(i - 0x68) * 0.007352941f;
            ascentHeight = 800;
            HuVecCopyXYZ(&sp180, ascentHeight, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            sp190.y += temp_f20 * ascentHeight * temp_f20;
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * temp_f22) + sp180.x, ((sp190.y - sp180.y) * temp_f22) + sp180.y, ((sp190.z - sp180.z) * temp_f22) + sp180.z);
            op_ModelPosSet(0xC, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosSet(0xD, sp1A0.x, sp1A0.y, sp1A0.z);
            op_ModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(0, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_30 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_30;
            op_ModelRotSet(0, 0.0f, temp_f0_30, 0.0f);
            op_ModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(2, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_32 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_32;
            op_ModelRotSet(2, 0.0f, temp_f0_32, 0.0f);
            op_ModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(3, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_34 = op_AngleStep(angles.currentYaw, angles.targetYaw, 5.0f);
            angles.targetYaw = temp_f0_34;
            op_ModelRotSet(3, 0.0f, temp_f0_34, 0.0f);
            op_ModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(4, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            temp_f0_36 = op_AngleStep(angles.currentYaw, angles.targetYaw, 9.0f);
            angles.targetYaw = temp_f0_36;
            op_ModelRotSet(4, 0.0f, temp_f0_36, 0.0f);
            op_ModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(5, &sp190.x, &angles.currentYaw, &sp190.z);
            temp_f20 = op_CameraAngleCalc(sp180.x, sp180.z, sp1A0.x, sp1A0.z);
            angles.targetYaw = temp_f20;
            if (temp_f20 < 0.0f) {
                angles.targetYaw = temp_f20 + 360.0f;
            }
            i += 2;
            temp_f0_38 = op_AngleStep(angles.currentYaw, angles.targetYaw, 9.0f);
            angles.targetYaw = temp_f0_38;
            op_ModelRotSet(5, 0.0f, temp_f0_38, 0.0f);
            var_s1 += 1;
            HuPrcVSleep();
        } while (i < 0xF1);
        op_MotionShiftSet(0, 0x33, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 1.0f);
        op_MotionShiftSet(2, 0x46, 4, 4, (s16)2);
        op_MotionSpeedSet(2, 1.0f);
        op_MotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        op_MotionSpeedSet(3, 1.0f);
        op_MotionShiftSet(4, 0x55, 4, 4, (s16)2);
        op_MotionSpeedSet(4, 1.0f);
        op_MotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        op_MotionSpeedSet(5, 1.0f);
        for (i = 0; i < 0x11; i++) {
            temp_f22 = (f32)i * 0.0625f;
            HuVecCopyXYZ(&sp180, 800.0f, 400.0f, 2320.0f);
            HuVecCopyXYZ(&sp190, -880.0f, 400.0f, 3231.5f);
            HuVecCopyXYZ(&sp1A0, ((sp190.x - sp180.x) * 0.5f) + sp180.x, ((sp190.y - sp180.y) * 0.5f) + sp180.y, ((sp190.z - sp180.z) * 0.5f) + sp180.z);
            op_ModelPosSet(0x1E, sp1A0.x, 0.0f, sp1A0.z);
            op_ModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
            op_ModelPosGet(0, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(0, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_39 = op_AngleLerp(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_39;
            op_ModelRotSet(0, 0.0f, temp_f0_39, 0.0f);
            op_ModelPosGet(2, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(2, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_40 = op_AngleLerp(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_40;
            op_ModelRotSet(2, 0.0f, temp_f0_40, 0.0f);
            op_ModelPosGet(3, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(3, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_41 = op_AngleLerp(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_41;
            op_ModelRotSet(3, 0.0f, temp_f0_41, 0.0f);
            temp_f22 = 2.0f * temp_f22 > 1.0f ? 1.0f : 2.0f * temp_f22;
            op_ModelPosGet(4, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(4, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_42 = op_AngleLerp(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_42;
            op_ModelRotSet(4, 0.0f, temp_f0_42, 0.0f);
            op_ModelPosGet(5, &sp180.x, &sp180.y, &sp180.z);
            op_ModelRotGet(5, &sp190.x, &angles.targetYaw, &sp190.z);
            temp_f0_43 = op_AngleLerp(angles.targetYaw, sp1A0.x - sp180.x, sp1A0.z - sp180.z, temp_f22);
            angles.targetYaw = temp_f0_43;
            op_ModelRotSet(5, 0.0f, temp_f0_43, 0.0f);
            HuPrcVSleep();
        }
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        op_MotionShiftSet(0, 0x2E, 4, 4, (s16)0);
        HuPrcSleep(0x10);
        op_ModelDispOn(6);
        temp_s1_3 = op_ModelIdGet(0);
        temp_v0_10 = op_ModelIdGet(6);
        Hu3DModelAttrSet(temp_v0_10, 0x4000, 0x4000);
        Hu3DModelHookSet(temp_v0_10, temp_s1_3, "item_hook");
        op_ModelRotGet(0, &sp208.x, &sp208.y, &sp208.z);
        op_ModelPosGet(0, &sp1F8.x, &sp1F8.y, &sp1F8.z);
        for (i = 1; i < 9; i++) {
            temp_f0 = (f32)i * 0.125f;
            sp208.y = op_AngleLerp(sp208.y, op_cameraMainTbl[0].x - sp1F8.x, op_cameraMainTbl[0].z - sp1F8.z, temp_f0);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x275);
        }
        op_MotionShiftSet(2, 0x43, 8, 8, (s16)2);
        op_MotionShiftSet(3, 0x4E, 8, 8, (s16)2);
        op_MotionShiftSet(4, 0x56, 8, 8, (s16)0);
        op_MotionEndWait(4);
        op_MotionShiftSet(4, 0x50, 8, 8, (s16)2);
        op_WinDispOn(0);
        op_WinMesSet(0, 0x4D14U);
        op_MotionEndWait(0);
        op_MotionShiftSet(0, 0x2F, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x59, 8, 8, (s16)2);
        op_ModelPosGet(5, &sp1D8.x, &sp1D8.y, &sp1D8.z);
        op_ModelPosGet(0xE, &sp1E8.x, &sp1E8.y, &sp1E8.z);
        temp_f24 = op_CameraAngleCalc(op_cameraMainTbl[0].x, op_cameraMainTbl[0].z, sp1E8.x, sp1E8.z);
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
        op_ModelRotGet(5, &sp208.x, &sp208.y, &sp208.z);
        do {
            temp_f20 = (f32)i;
            temp_f0 = temp_f20 * 0.125f;
            HuVecCopyXYZ(&sp1F8, ((sp1E8.x - sp1D8.x) * temp_f0) + sp1D8.x, ((sp1E8.y - sp1D8.y) * temp_f0) + sp1D8.y, ((sp1E8.z - sp1D8.z) * temp_f0) + sp1D8.z);
            op_ModelPosSet(5, sp1F8.x, sp1F8.y, sp1F8.z);
            op_ModelPosSet(0x25, sp1F8.x, sp1F8.y, sp1F8.z);
            if (i < 5) {
                temp_f0 = temp_f20 * 0.25f;
                op_ModelRotSet(5, 0.0f, op_AngleLerp(sp208.y, sp1E8.x - sp1F8.x, (sp1E8.z + 10.0f) - sp1F8.z, temp_f0), 0.0f);
            }
            i += 1;
            HuPrcVSleep();
        } while (i < 9);
        op_ModelPosGet(5, &sp1D8.x, &sp1D8.y, &sp1D8.z);
        op_ModelPosGet(0xE, &sp1E8.x, &sp1E8.y, &sp1E8.z);
        op_ModelRotGet(5, &sp208.x, &sp208.y, &sp208.z);
        for (i = 0; i < 8; i++) {
            temp_f20 = (f32)i * 0.125f;
            op_ModelRotSet(5, 0.0f, op_AngleLerp(sp208.y, sp1E8.x - sp1F8.x, (sp1E8.z + 10.0f) - sp1F8.z, temp_f20), 0.0f);
            HuPrcVSleep();
        }
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(8);
        op_MotionShiftSet(5, 0x5B, 4, 4, (s16)0);
        HuPrcSleep(8);
        op_ModelDispOn(0xF);
        temp_s1_4 = op_ModelIdGet(5);
        temp_v0_11 = op_ModelIdGet(0xF);
        Hu3DModelAttrSet(temp_v0_11, 0x4000, 0x4000);
        Hu3DModelHookSet(temp_v0_11, temp_s1_4, "item_hook");
        for (i = 1; i < 9; i++) {
            HuPrcVSleep();
        }
        op_MotionEndWait(5);
        if (storyMode != 0) {
            HuAudFXPlay(0x27A);
        }
        op_MotionShiftSet(5, 0x5F, 4, 4, (s16)2);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D15U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D14U);
            op_Sleep(0x50);
        }
        op_WinDispOff(0);
        HuPrcSleep(0x32);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D17U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D16U);
            op_Sleep(0x3C);
        }
        MBCameraNearFarSet(10.0f, 10000.0f);
        op_ModelCreate(0x1C, 0xF0007, 0x2A9);
        op_ModelPosSet(0x1C, -580.0f, 60.0f, 2580.0f);
        op_ModelPosGet(0, &sp238.x, &sp238.y, &sp238.z);
        op_ModelRotSet(0x1C, 0.0f, op_CameraAngleCalc(sp238.x, sp238.z, op_cameraMainTbl[0].x, op_cameraMainTbl[0].z), 0.0f);
        op_ModelScaleSet(0x1C, 1.0f, 1.0f, 1.0f);
        op_ModelDispOff(0x1C);
        op_MotionShiftSet(1, 0x3C, 4, 4, (s16)0);
        HuPrcSleep(4);
        op_ModelDispOn(0x1C);
        op_MotionFlagReset(0x1C, 1);
        op_MotionTimeSet(0x1C, 0U);
        if (storyMode != 0) {
            HuAudFXPlay(0x236);
        }
        op_MotionEndWait(1);
        op_MotionShiftSet(1, 0x38, 4, 4, (s16)2);
        op_ModelRotGet(0, &sp228.x, &characterAngles[0], &sp228.z);
        op_ModelRotGet(1, &sp228.x, &characterAngles[1], &sp228.z);
        op_ModelRotGet(2, &sp228.x, &characterAngles[2], &sp228.z);
        op_ModelRotGet(3, &sp228.x, &characterAngles[3], &sp228.z);
        op_ModelRotGet(4, &sp228.x, &characterAngles[4], &sp228.z);
        op_ModelRotGet(5, &sp228.x, &characterAngles[5], &sp228.z);
        op_ModelPosGet(0xB, &sp228.x, &sp228.y, &sp228.z);
        op_MotionShiftSet(2, 0x46, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x55, 4, 4, (s16)2);
        var_s3 = 0;
        do {
            temp_f20 = (f32)var_s3;
            temp_f20 *= 0.125f;
            op_ModelPosGet(0, &sp218.x, &sp218.y, &sp218.z);
            op_ModelRotSet(0, 0.0f, op_AngleLerp(characterAngles[0], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            op_ModelPosGet(2, &sp218.x, &sp218.y, &sp218.z);
            op_ModelRotSet(2, 0.0f, op_AngleLerp(characterAngles[2], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            op_ModelPosGet(3, &sp218.x, &sp218.y, &sp218.z);
            op_ModelRotSet(3, 0.0f, op_AngleLerp(characterAngles[3], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            op_ModelPosGet(4, &sp218.x, &sp218.y, &sp218.z);
            op_ModelRotSet(4, 0.0f, op_AngleLerp(characterAngles[4], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            op_ModelPosGet(5, &sp218.x, &sp218.y, &sp218.z);
            op_ModelRotSet(5, 0.0f, op_AngleLerp(characterAngles[5], sp228.x - sp218.x, sp228.z - sp218.z, temp_f20), 0.0f);
            temp_f20 *= 7.5f;
            temp_f0 = sp218.x - temp_f20;
            op_ModelPosSet(5, temp_f0, sp218.y, sp218.z);
            var_s3 += 1;
            HuPrcVSleep();
        } while (var_s3 < 9);
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionEndWait(0x1C);
        op_ModelKill(0x2D);
        op_ModelKill(0x39);
        op_ModelKill(0x41);
        op_ModelKill(0x42);
        op_ModelKill(0x43);
        op_ModelKill(0x49);
        op_ModelKill(0x4A);
        op_ModelKill(0x4E);
        op_ModelKill(0x52);
        op_ModelKill(0x56);
        op_ModelKill(0x5A);
        op_ModelKill(0x35);
        op_ModelKill(0x3D);
        op_ModelKill(0x46);
        op_ModelKill(0x4D);
        op_ModelKill(0x55);
        op_ModelKill(0x5E);
        HuPrcSleep(3);
        if (storyMode != 0) {
            HuAudFXPlay(0x23C);
        }
        op_WipeWhiteOutCreate(0xF, 0x14);
        if (storyMode != 0) {
            HuAudSeqFadeOut(0x2E);
        }
        HuPrcSleep(0x14);
        HuPrcSleep(0x14);
        op_ModelPosGet(5, &sp268.x, &sp268.y, &sp268.z);
        op_ModelPosSet(5, sp268.x + 60.0f, sp268.y, sp268.z);
        op_ModelPosSet(0x25, sp268.x + 60.0f, sp268.y, sp268.z);
        op_MotionCreate(0x30, 0xF000F, 0);
        op_MotionCreate(0x44, 0x70025, 0);
        HuPrcSleep(3);
        op_MotionCreate(0x53, 0xF0017, 0);
        op_MotionCreate(0x5C, 0xF001A, 0);
        HuPrcSleep(3);
        op_ModelKill(0x1C);
        op_ModelKill(0x1D);
        op_ModelKill(0x1E);
        MBBackKill();
        MBBackLoad(0x22);
        MBCameraKill();
        Hu3DCameraPerspectiveSet(0, 40.0f, 500.0f, 8000.0f);
        op_CameraObjCreate(&op_cameraMainTbl[0], &op_cameraMainTbl[1]);
        op_ModelKill(0xC);
        op_ModelKill(0xD);
        op_ModelKill(0xE);
        op_ModelKill(9);
        op_ModelDispOff(0xB);
        HuPrcSleep(3);
        op_MotionCreate(0x31, 0x2007A, 0);
        op_MotionCreate(0x3B, 0xF0013, 0);
        op_MotionCreate(0x45, 0x7007A, 0);
        op_MotionCreate(0x4B, 0x40003, 0);
        op_MotionCreate(0x4C, 0x4007A, 0);
        op_MotionCreate(0x54, 0x5007A, 0);
        op_MotionCreate(0x5D, 0x6007A, 0);
        op_ModelCreate(0x12, 0xF0008, 0x6A9);
        op_ModelPosSet(0x12, -130.99998f, 0.0f, 3250.0f);
        op_ModelRotSet(0x12, 0.0f, 25.0f, 0.0f);
        op_ModelScaleSet(0x12, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x12, 1);
        temp_v0_12 = Hu3DModelObjPtrGet(op_ModelIdGet(0x12), "tree_kage");
        func_80088700_main(temp_v0_12->unk58, 0.0f, 0.0f, 0.0f);
        temp_f24 = 0.0f;
        temp_v0_12->scale.x = temp_v0_12->scale.y = temp_v0_12->scale.z = temp_f24;
        temp_v0_12->baseScale.x = temp_v0_12->baseScale.y = temp_v0_12->baseScale.z = temp_f24;
        op_ModelPosGet(3, &sp278.x, &sp278.y, &sp278.z);
        op_ModelRotGet(3, &sp2A8.x, &sp2A8.y, &sp2A8.z);
        temp_f22 = op_CameraAngleCalc(op_cameraMainTbl[0].x, op_cameraMainTbl[0].z, sp278.x, sp278.z);
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
        op_ModelPosSet(0x12, treePos1.x, treePos1.y, temp_f20);
        op_ModelPosGet(3, &sp278.x, &sp278.y, &sp278.z);
        op_ModelPosGet(0x12, &sp288.x, &sp288.y, &sp288.z);
        op_ModelRotSet(3, temp_f24, op_CameraAngleCalc(sp278.x, sp278.z, sp288.x, sp288.z), temp_f24);
        op_DemoMotIntervalCreate(0, 3, 0x4B, 0x48, 0, 0x26);
        op_DemoMotRestartCreate(1, 0x12, 8, 0x33);
        op_ModelCreate(0x13, 0xF0008, 0x6A9);
        op_ModelPosSet(0x13, 344.0f, temp_f24, 2900.0f);
        op_ModelRotSet(0x13, temp_f24, 25.0f, temp_f24);
        op_ModelScaleSet(0x13, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x13, 1);
        op_ModelPosGet(1, &sp2B8.x, &sp2B8.y, &sp2B8.z);
        op_ModelRotGet(1, &sp2E8.x, &sp2E8.y, &sp2E8.z);
        temp_f22 = op_CameraAngleCalc(op_cameraMainTbl[0].x, op_cameraMainTbl[0].z, sp2B8.x, sp2B8.z);
        temp_f20 = sindf(temp_f22);
        temp_f0_46 = cosdf(temp_f22);
        temp_f20 = (temp_f20 * 125.0f) + (temp_f0_46 * distance) + sp2B8.x;
        treePos2.x = temp_f20;
        treePos2.y = temp_f24;
        temp_f20 = cosdf(temp_f22);
        temp_f0_46 = sindf(temp_f22);
        temp_f20 = (temp_f20 * -125.0f) + (temp_f0_46 * distance) + sp2B8.z;
        treePos2.z = temp_f20;
        op_ModelPosSet(0x13, treePos2.x, treePos2.y, temp_f20);
        op_ModelPosGet(1, &sp2B8.x, &sp2B8.y, &sp2B8.z);
        op_ModelPosGet(0x13, &sp2C8.x, &sp2C8.y, &sp2C8.z);
        op_ModelRotSet(1, temp_f24, op_CameraAngleCalc(sp2B8.x, sp2B8.z, sp2C8.x, sp2C8.z), temp_f24);
        op_DemoMotIntervalCreate(2, 1, 0x3B, 0x38, 0x2C, 0x28);
        op_DemoMotRestartCreate(3, 0x13, 0, 0x58);
        Hu3DModelAttrSet(op_ModelIdGet(0xF), 0x4000, 0);
        op_ModelDispOff(0xF);
        Hu3DModelAttrSet(op_ModelIdGet(6), 0x4000, 0);
        op_ModelKill(6);
        op_ModelPosGet(0xF, &sp2F8.x, &sp2F8.y, &sp2F8.z);
        op_DemoShadowCreate(0x27, sp2F8.x, sp2F8.y, sp2F8.z);
        temp_f2_6 = (1200.0f - sp2F8.y) * 0.00083333335f;
        op_ModelScaleSet(0x27, temp_f2_6, 1.0f, temp_f2_6);
        op_ModelDispOff(0x27);
        op_MotionCreate(0x6B, 0xF001C, 0);
        op_WinDispOff(0);
        op_MotionSet(0, 0x30, 2);
        op_MotionSet(2, 0x44, 2);
        op_MotionSet(3, 0x48, 2);
        op_MotionSet(4, 0x53, 2);
        op_MotionSet(5, 0x5C, 2);
        op_WipeWhiteInCreate(0xF, 0x14);
        HuPrcSleep(0x14);
        if (storyMode != 0) {
            HuAudSeqPlay(0x3B);
        }
        op_WinMesSet(0, 0x4D18U);
        HuPrcSleep(0x28);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D19U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D18U);
            op_Sleep(0x78);
        }
        op_WinDispOff(0);
        op_ModelDispOn(0xF);
        op_ModelDispOn(0x27);
        op_MotionShiftSet(0xF, 0x69, 4, 4, (s16)2);
        op_CameraPosGet(&cameraPos1.x, &cameraPos1.y, &cameraPos1.z, &cameraAt1.x, &cameraAt1.y, &cameraAt1.z);
        temp_f26 = op_CameraAngleCalc(cameraAt1.x, cameraAt1.z, cameraPos1.x, cameraPos1.z);
        sp328.y = 150.0f;
        sp328.x = (sindf(temp_f26) * -600.0f) + cameraPos1.x;
        sp328.z = (cosdf(temp_f26) * -600.0f) + cameraPos1.z;
        HuVecCopy3F(&sp338, &sp328);
        sp328.y += 900.0f;
        op_ModelScaleSet(0xF, 1.0f, 1.0f, 1.0f);
        if (storyMode != 0) {
            HuAudFXPlay(0x23D);
        }
        i = 0;
        do {
            temp_f20 = (f32)i * 0.05f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp358, (temp_f20 * (sp338.x - sp328.x)) + sp328.x, (temp_f20 * (sp338.y - sp328.y)) + sp328.y, (temp_f20 * (sp338.z - sp328.z)) + sp328.z);
            op_ModelPosSet(0xF, sp358.x, sp358.y, sp358.z);
            op_ModelPosSet(0x27, sp358.x, 0.0f, sp358.z);
            temp_f2_7 = (1200.0f - sp358.y) * 0.00083333335f;
            op_ModelScaleSet(0x27, temp_f2_7, 1.0f, temp_f2_7);
            op_ModelRotSet(0xF, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, op_cameraMainTbl[0].x, op_cameraMainTbl[0].z), 0.0f);
            HuPrcVSleep();
            i += 1;
        } while (i < 0x15);
        HuPrcSleep(8);
        op_DemoGuideInEffCreate(4, 0xF);
        op_DemoObjKill(0);
        op_DemoObjKill(1);
        op_DemoObjKill(2);
        op_DemoObjKill(3);
        op_ModelPosGet(0xF, &sp358.x, &sp358.y, &sp358.z);
        op_ModelRotGet(0, &sp338.x, &characterAngles2[0], &sp338.z);
        op_ModelRotGet(1, &sp338.x, &characterAngles2[1], &sp338.z);
        op_ModelRotGet(2, &sp338.x, &characterAngles2[2], &sp338.z);
        op_ModelRotGet(3, &sp338.x, &characterAngles2[3], &sp338.z);
        op_ModelRotGet(4, &sp338.x, &characterAngles2[4], &sp338.z);
        op_ModelRotGet(5, &sp338.x, &characterAngles2[5], &sp338.z);
        op_MotionShiftSet(0, 0x33, 4, 4, (s16)2);
        op_MotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x46, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x55, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        for (i = 0; i < 9; i++) {
            temp_f20 = (f32)i * 0.125f;
            op_ModelPosGet(0, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(0, 0.0f, op_AngleLerp(characterAngles2[0], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            op_ModelPosGet(1, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(1, 0.0f, op_AngleLerp(characterAngles2[1], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            op_ModelPosGet(2, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(2, 0.0f, op_AngleLerp(characterAngles2[2], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            op_ModelPosGet(3, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(3, 0.0f, op_AngleLerp(characterAngles2[3], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            op_ModelPosGet(4, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(4, 0.0f, op_AngleLerp(characterAngles2[4], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            op_ModelPosGet(5, &sp328.x, &sp328.y, &sp328.z);
            op_ModelRotSet(5, 0.0f, op_AngleLerp(characterAngles2[5], sp358.x - sp328.x, sp358.z - sp328.z, temp_f20), 0.0f);
            HuPrcVSleep();
        }
        op_MotionShiftSet(0, 0x28, 4, 4, (s16)2);
        op_MotionShiftSet(1, 0x38, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(0x10);
        op_MotionShiftSet(0xF, 0x6A, 4, 4, (s16)0);
        HuPrcSleep(0x11);
        if (storyMode != 0) {
            HuAudFXPlay(0x2A8);
        }
        HuPrcSleep(0x12);
        if (storyMode != 0) {
            _HuAudPlayerFXPlay(0x286, 0);
            _HuAudPlayerFXPlay(0x286, 1);
            _HuAudPlayerFXPlay(0x286, 2);
        }
        op_MotionShiftSet(0, 0x31, 4, 4, (s16)0);
        op_MotionShiftSet(1, 0x3C, 4, 4, (s16)0);
        op_MotionShiftSet(2, 0x45, 4, 4, (s16)0);
        HuPrcSleep(3);
        if (storyMode != 0) {
            _HuAudPlayerFXPlay(0x286, 3);
            _HuAudPlayerFXPlay(0x286, 4);
        }
        op_MotionShiftSet(3, 0x4C, 4, 4, (s16)0);
        op_MotionShiftSet(4, 0x54, 4, 4, (s16)0);
        HuPrcSleep(1);
        if (storyMode != 0) {
            _HuAudPlayerFXPlay(0x286, 5);
        }
        op_MotionShiftSet(5, 0x5D, 4, 4, (s16)0);
        op_MotionEndWait(0xF);
        op_MotionShiftSet(0xF, 0x68, 4, 4, (s16)2);
        op_MotionEndWait(0);
        op_MotionShiftSet(0, 0x28, 4, 4, (s16)2);
        op_MotionShiftSet(1, 0x38, 4, 4, (s16)2);
        op_MotionShiftSet(2, 0x40, 4, 4, (s16)2);
        op_MotionEndWait(3);
        op_MotionShiftSet(3, 0x48, 4, 4, (s16)2);
        op_MotionShiftSet(4, 0x50, 4, 4, (s16)2);
        op_MotionEndWait(5);
        op_MotionShiftSet(5, 0x58, 4, 4, (s16)2);
        HuPrcSleep(0x14);
        op_DemoObjKill(4);
        op_MotionShiftSet(0, 0x33, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        op_MotionShiftSet(1, 0x3D, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        op_MotionShiftSet(2, 0x46, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        op_MotionShiftSet(3, 0x4D, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        op_MotionShiftSet(4, 0x55, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        op_MotionShiftSet(5, 0x5E, 4, 4, (s16)2);
        op_MotionSpeedSet(0, 0.6f);
        HuVecCopyXYZ(&sp338, -325.0f, 160.0f, 2600.0f);
        op_ModelPosGet(0xF, &sp328.x, &sp328.y, &sp328.z);
        op_ModelPosGet(3, &sp338.x, &sp338.y, &sp338.z);
        sp338.y = 160.0f;
        op_MotionShiftSet(0xF, 0x6B, 8, 8, (s16)2);
        CharAnimCreate(op_ModelIdGet(0xF), 2, 0xF, 0xA0081);
        i = 0;
        do {
            temp_f20 = (f32)i * 0.016666668f;
            if (i == 0x3C) {
            } else if (i == 0x36) {
                op_DemoOutEffCreate(3, 3);
            } else if (i == 0x2D) {
                op_DemoOutEffCreate(2, 2);
            } else if (i == 0x24) {
                op_DemoOutEffCreate(0, 0);
            } else if (i == 0x1B) {
                op_DemoOutEffCreate(5, 5);
            } else if (i == 0x12) {
                op_DemoOutEffCreate(4, 4);
            } else if (i == 9) {
                if (storyMode != 0) {
                    HuAudFXPlay(0x23E);
                }
                op_DemoOutEffCreate(1, 1);
            }
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp348, (temp_f20 * (sp338.x - sp328.x)) + sp328.x, (temp_f20 * (sp338.y - sp328.y)) + sp328.y, (temp_f20 * (sp338.z - sp328.z)) + sp328.z);
            i += 1;
            temp_f26 = op_CameraAngleCalc(op_cameraMainTbl[0].x, op_cameraMainTbl[0].z, sp328.x, sp328.z);
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
            op_ModelPosSet(0xF, sp348.x, sp348.y, temp_f24);
            op_ModelPosSet(0x27, sp348.x, 0.0f, sp348.z);
            temp_f2_8 = (1200.0f - sp348.y) * 0.00083333335f;
            op_ModelScaleSet(0x27, temp_f2_8, 1.0f, temp_f2_8);
            op_ModelRotSet(0xF, 0.0f, op_CameraAngleCalc(sp348.x, sp348.z, op_cameraMainTbl[0].x, op_cameraMainTbl[0].z), 0.0f);
            op_ModelPosGet(0, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(0, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            op_ModelPosGet(1, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(1, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            op_ModelPosGet(2, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(2, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            op_ModelPosGet(3, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(3, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            op_ModelPosGet(4, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(4, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            op_ModelPosGet(5, &sp358.x, &sp358.y, &sp358.z);
            op_ModelRotSet(5, 0.0f, op_CameraAngleCalc(sp358.x, sp358.z, sp348.x, sp348.z), 0.0f);
            HuPrcVSleep();
        } while (i < 0x3D);
        op_MotionShiftSet(0xF, 0x68, 8, 8, (s16)2);
        HuPrcSleep(0x28);
        op_DemoObjKill(0);
        op_DemoObjKill(1);
        op_DemoObjKill(2);
        op_DemoObjKill(3);
        op_DemoObjKill(4);
        op_DemoObjKill(5);
        op_ModelKill(0);
        op_ModelKill(1);
        op_ModelKill(2);
        op_ModelKill(3);
        op_ModelKill(4);
        op_ModelKill(5);
        op_ModelKill(0x28);
        op_ModelKill(0x29);
        op_ModelKill(0x2E);
        op_ModelKill(0x2F);
        op_ModelKill(0x30);
        op_ModelKill(0x31);
        op_ModelKill(0x33);
        op_ModelKill(0x38);
        op_ModelKill(0x3A);
        op_ModelKill(0x3B);
        op_ModelKill(0x3C);
        op_ModelKill(0x3D);
        op_ModelKill(0x40);
        op_ModelKill(0x44);
        op_ModelKill(0x46);
        op_ModelKill(0x48);
        op_ModelKill(0x4B);
        op_ModelKill(0x4C);
        op_ModelKill(0x4D);
        op_ModelKill(0x50);
        op_ModelKill(0x51);
        op_ModelKill(0x53);
        op_ModelKill(0x54);
        op_ModelKill(0x55);
        op_ModelKill(0x58);
        op_ModelKill(0x59);
        op_ModelKill(0x5B);
        op_ModelKill(0x5C);
        op_ModelKill(0x5D);
        op_ModelKill(0x5F);
        op_ModelKill(0x5E);
        op_ModelKill(0x69);
        op_ModelKill(0x6A);
        op_ModelKill(0xC);
        op_ModelKill(0xD);
        op_ModelKill(0x21);
        op_ModelKill(0x22);
        op_ModelKill(0x23);
        op_ModelKill(0x24);
        op_ModelKill(0x25);
        HuPrcSleep(8);
        Hu3DScreenClearF = 1;
        op_WipeWhiteOutCreate(0xF, 0x14);
        HuPrcSleep(0x14);
        MBBackKill();
        HuVecCopy3F(&sp3A8, &op_cameraOrbitPos);
        HuVecCopy3F(&sp3B8, &op_cameraOrbitAt);
        HuVecCopyXYZ(&sp398, sp3A8.x - sp3B8.x, sp3A8.y - sp3B8.y, sp3A8.z - sp3B8.z);
        temp_f20 = cosdf(315.0f);
        temp_f20 = (temp_f20 * sp398.x) + sp3B8.x + (sindf(315.0f) * sp398.z);
        sp388.x = temp_f20;
        sp388.y = sp3B8.y + sp398.y;
        temp_f20 = sindf(315.0f);
        cameraCosine = cosdf(315.0f);
        temp_f20 *= sp398.x;
        sp388.z = (sp3B8.z - temp_f20) + (cameraCosine * sp398.z);
        op_CameraPosSet(sp388.x, sp388.y, sp388.z, sp3B8.x, sp3B8.y, sp3B8.z);
        op_CameraObjCreate(&sp388, &op_cameraOrbitAt);
        Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);
        op_ModelKill(0xF);
        op_ModelDispOff(0x27);
        op_ModelKill(0x68);
        HuPrcSleep(3);
        op_SprCreate(0, 0xF001D);
        op_SprPosSet(0, 0x78, 0x5C);
        op_SprDispOff(0);
        HuPrcSleep(3);
        op_ModelCreate(0x10, 0x1D000A, 0x6A9);
        op_ModelPosSet(0x10, 0.0f, 0.0f, 0.0f);
        op_ModelRotSet(0x10, 270.0f, 180.0f, 0.0f);
        op_ModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
        op_MotionTimeSet(0x10, 0U);
        op_MotionFlagSet(0x10, 1);
        op_ModelDispOff(0x10);
        op_ModelCreate(0x14, 0xD000A, 0x2002A9);
        op_ModelPosSet(0x14, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x14, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x14, 0U);
        op_MotionFlagSet(0x14, 1);
        op_ModelCreate(9, 0xD0000, 0x2002A9);
        op_ModelPosSet(9, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(9, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(9, 0U);
        op_MotionFlagSet(9, 1);
        op_ModelDispOff(9);
        op_ModelCreate(0x15, 0xD0001, 0x2A9);
        op_ModelPosSet(0x15, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x15, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x15, 0U);
        op_MotionFlagSet(0x15, 1);
        op_ModelCreate(0x16, 0xD0002, 0x2A9);
        op_ModelPosSet(0x16, 0.0f, 0.0f, -585.0f);
        op_ModelScaleSet(0x16, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x16, 0U);
        op_MotionFlagSet(0x16, 1);
        temp_v0_13 = op_ModelIdGet(0x16);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "mario"))->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "luigi"))->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "peach"))->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "yoshi"))->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "wario"))->unk58, 0.0f, -4000.0f, 0.0f);
        func_80088800_main(((HmfMotionNode *)Hu3DModelObjPtrGet(temp_v0_13, "donkey"))->unk58, 0.0f, -4000.0f, 0.0f);
        HuVecCopyXYZ(&sp3C8, 0.0f, 0.0f, -200.0f);
        sp3C8.z -= 8.0f;
        op_ModelCreate(0x17, 0xD0003, 0x2A9);
        op_ModelPosSet(0x17, sp3C8.x, sp3C8.y, sp3C8.z);
        op_ModelScaleSet(0x17, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x17, 0U);
        op_MotionFlagSet(0x17, 1);
        op_ModelCreate(0x18, 0xD0004, 0x2A9);
        op_ModelPosSet(0x18, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x18, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x18, 0U);
        op_MotionFlagSet(0x18, 1);
        op_ModelCreate(0x19, 0xD0005, 0x2A9);
        op_ModelPosSet(0x19, 325.0f, 9.5f, 45.0f);
        op_ModelScaleSet(0x19, 1.0f, 1.0f, 1.0f);
        op_MotionTimeSet(0x19, 0U);
        op_MotionFlagSet(0x19, 1);
        op_ModelCreate(0x1D, 0xD0007, 0x6A9);
        op_ModelPosSet(0x1D, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x1D, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x1D, 1);
        op_ModelIdGet(0x1D);
        op_ModelDispOff(0x1D);
        op_ModelCreate(0x1E, 0xD0008, 0x6A9);
        op_ModelPosSet(0x1E, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x1E, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x1E, 1);
        op_ModelIdGet(0x1E);
        op_ModelDispOff(0x1E);
        op_ModelCreate(0x1F, 0xD0009, 0x6A9);
        op_ModelPosSet(0x1F, 0.0f, 0.0f, 0.0f);
        op_ModelScaleSet(0x1F, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x1F, 1);
        op_ModelIdGet(0x1F);
        op_ModelDispOff(0x1F);
        op_ModelCreate(0x1B, 0xB0001, 0x6A9);
        op_ModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
        op_ModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
        op_MotionTimeSet(0x1B, 0U);
        op_MotionFlagSet(0x1B, 1);
        op_ModelDispOff(0x1B);
        op_MotionCreate(0x6E, 0xA0125, 0);
        op_MotionCreate(0x6F, 0xA0129, 0);
        op_WipeWhiteInCreate(0xF, 0x10);
        op_CameraPosGet(&cameraPos2.x, &cameraPos2.y, &cameraPos2.z, &cameraAt2.x, &cameraAt2.y, &cameraAt2.z);
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
            op_CameraPosSet(cameraPos2.x, cameraPos2.y, cameraPos2.z, cameraAt2.x, cameraAt2.y, cameraAt2.z);
            HuPrcVSleep();
        } while (i < 0x1F);
        op_ModelDispOn(0xB);
        op_MotionSet(0xB, 0x6D, 2);
        op_MotionFlagSet(0xB, 1);
        op_MotionTimeSet(0xB, 0U);
        HuVecCopyXYZ(&sp418, 0.0f, 325.0f, 300.0f);
        HuVecCopy3F(&sp408, &sp418);
        temp_f2_9 = sp408.y + 400.0f;
        sp408.y = temp_f2_9;
        op_ModelPosSet(0xB, sp408.x, temp_f2_9, sp408.z);
        op_ModelRotSet(0xB, 0.0f, 0.0f, 0.0f);
        for (i = 0; i < 0x33; i++) {
            temp_f26 = (f32)i * 0.02f;
            temp_f26 = sindf(temp_f26 * 90.0f);
            HuVecCopyXYZ(&sp428, (temp_f26 * (sp418.x - sp408.x)) + sp408.x, (temp_f26 * (sp418.y - sp408.y)) + sp408.y, (temp_f26 * (sp418.z - sp408.z)) + sp408.z);
            op_ModelPosSet(0xB, sp428.x, sp428.y, sp428.z);
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
                op_CameraPosSet(cameraPos2.x, cameraPos2.y, cameraPos2.z, cameraAt2.x, cameraAt2.y, cameraAt2.z);
            }
            HuPrcVSleep();
        }
        HuPrcSleep(0x14);
        op_MotionFlagReset(0xB, 3);
        op_MotionEndWait(0xB);
        if (storyMode != 0) {
            HuAudFXPlay(0x159);
        }
        op_MotionSet(0xB, 0x6E, 2);
        op_DemoStarWaitCreate(0, 0xB, sp428.x, sp428.y, sp428.z, 50.0f, 0x1E);
        HuPrcSleep(0x14);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D1BU);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D1AU);
            op_Sleep(0x3C);
        }
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D1DU);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D1CU);
            op_Sleep(0x78);
        }
        op_WinDispOff(0);
        if (storyMode != 0) {
            op_DemoObjKill(0);
            op_ModelPosGet(0xB, &sp458.x, &sp458.y, &sp458.z);
            HuVecCopyXYZ(&sp438, sp458.x, sp458.y, sp458.z);
            HuVecCopyXYZ(&sp448, sp438.x + 240.0f, sp438.y + 25.0f, sp438.z - 150.0f);
            for (i = 0; i < 0x1F; i++) {
                temp_f20 = (f32)i * 0.033333335f;
                HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, (temp_f20 * (sp448.z - sp438.z)) + sp438.z);
                op_ModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
                HuPrcVSleep();
            }
            op_DemoStarWaitCreate(0, 0xB, sp458.x, sp458.y, sp458.z, 50.0f, 0x1E);
            op_ModelDispOn(0x1B);
            op_ModelPosSet(0x1B, -215.0f, 168.0f, sp458.z + 20.0f);
            op_ModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
            op_MotionTimeSet(0x1B, 0U);
            op_MotionFlagReset(0x1B, 1);
            if (storyMode != 0) {
                HuAudFXPlay(0x241);
            }
            HuPrcSleep(8);
            op_ModelDispOn(0x10);
            op_ModelScaleSet(0x10, 3.0f, 3.0f, 3.0f);
            op_ModelPosSet(0x10, -190.0f, 268.0f, sp458.z);
            op_DemoStarWaitCreate(6, 0x10, -190.0f, 268.0f, sp458.z, 25.0f, 0x32);
            op_MotionEndWait(0x1B);
            op_ModelDispOff(0x1B);
            op_WinDispOn(0);
            if (storyMode != 0) {
                op_WinMesSet(0, 0x4D1EU);
                op_WinMesWait(0);
            }
            op_WinDispOff(0);
            op_DemoObjKill(6);
            HuPrcSleep(1);
            op_ModelPosGet(0x10, &sp468.x, &sp468.y, &sp468.z);
            Hu3D3Dto2D(0, &sp468, &sp478);
            sp478.y -= 8.0f;
            op_SprDispOn(0);
            op_ModelDispOff(0x10);
            for (i = 0; i < 0x11; i++) {
                temp_f20 = (f32)i * 0.0625f;
                op_SprPosSet(0, (s32)((temp_f20 * (160.0f - sp478.x)) + sp478.x), (s32)((temp_f20 * (120.0f - sp478.y)) + sp478.y));
                temp_f0_53 = (temp_f20 * 0.85f) + 0.15f;
                op_SprScaleSet(0, temp_f0_53, temp_f0_53);
                HuPrcVSleep();
            }
            op_SprScaleSet(0, 1.0f, 1.0f);
            HuPrcSleep(0x3C);
            for (i = 0; i < 0x11; i++) {
                temp_f20 = (f32)(0x10 - i) * 0.0625f;
                op_SprPosSet(0, (s32)((temp_f20 * (160.0f - sp478.x)) + sp478.x), (s32)((temp_f20 * (120.0f - sp478.y)) + sp478.y));
                temp_f0_54 = (temp_f20 * 0.85f) + 0.15f;
                op_SprScaleSet(0, temp_f0_54, temp_f0_54);
                HuPrcVSleep();
            }
            op_SprDispOff(0);
            op_ModelDispOn(0x10);
            HuPrcSleep(1);
            op_DemoStarWaitCreate(6, 0x10, sp468.x, sp468.y, sp468.z, 25.0f, 0x32);
            op_WinDispOn(0);
            if (storyMode != 0) {
                op_WinMesSet(0, 0x4D1FU);
                op_WinMesWait(0);
            }
            op_WinDispOff(0);
            op_DemoObjKill(6);
            HuPrcSleep(1);
            op_ModelPosGet(0x10, &sp468.x, &sp468.y, &sp468.z);
            op_ModelPosSet(0x1B, sp468.x, sp468.y - 100.0f, sp468.z);
            op_ModelDispOn(0x1B);
            op_ModelScaleSet(0x1B, 1.0f, 1.0f, 1.0f);
            op_MotionTimeSet(0x1B, 4U);
            op_MotionFlagReset(0x1B, 1);
            if (storyMode != 0) {
                HuAudFXPlay(0x242);
            }
            op_ModelDispOff(0x10);
            op_ModelKill(0x10);
            op_MotionEndWait(0x1B);
            op_ModelDispOff(0x1B);
            op_ModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
            op_ModelScaleSet(0x1B, 8.0f, 1.0f, 8.0f);
            op_MotionFlagSet(0x1B, 1);
        }
        HuPrcSleep(0x24);
        op_WinDispOn(0);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D22U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D21U);
            op_Sleep(0x3C);
        }
        op_MotionShiftSet(0xB, 0x6F, 4, 4, (s16)2);
        op_WinDispOff(0);
        op_DemoObjKill(0);
        HuPrcSleep(1);
        op_ModelPosGet(0xB, &sp438.x, &sp438.y, &sp438.z);
        HuVecCopyXYZ(&sp448, 0.0f, sp438.y - 20.0f, sp438.z - 100.0f);
        for (i = 0; i < 0x3D; i++) {
            temp_f20 = (f32)i * 0.016666668f;
            temp_f20 = sindf(temp_f20 * 90.0f);
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, (temp_f20 * (sp448.z - sp438.z)) + sp438.z);
            op_ModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_56 = (((1.0f - temp_f20) * 0.1f) + 0.9f) * 2.5f;
            op_ModelScaleSet(0xB, temp_f0_56, temp_f0_56, temp_f0_56);
            HuPrcVSleep();
        }
        HuPrcSleep(0xA);
        op_ModelPosGet(0xB, &sp438.x, &sp438.y, &sp438.z);
        HuVecCopyXYZ(&sp448, 0.0f, 1250.0f, sp438.z);
        for (i = 0; i < 0x1F; i++) {
            temp_f20 = (f32)i * 0.033333335f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            op_ModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            HuPrcVSleep();
        }
        op_ModelDispOn(0x27);
        op_ModelPosSet(0x27, 0.0f, 0.0f, 300.0f);
        op_ModelScaleSet(0x27, 0.01f, 1.0f, 0.01f);
        op_ModelScaleSet(0xB, 1.0f, 1.0f, 1.0f);
        HuVecCopyXYZ(&sp438, 0.0f, sp458.y, 300.0f);
        HuVecCopyXYZ(&sp448, 0.0f, -90.0f, 300.0f);
        HuPrcSleep(0x1E);
        for (i = 0; i < 0x21; i++) {
            temp_f20 = (f32)i * 0.028571429f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            op_ModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_57 = (1250.0f - sp458.y) * 0.0008f;
            op_ModelScaleSet(0x27, temp_f0_57, 1.0f, temp_f0_57);
            HuPrcVSleep();
        }
        if (storyMode != 0) {
            HuAudFXPlay(0x23F);
        }
        op_ModelPosSet(0x1B, 0.0f, -120.0f, 300.0f);
        op_ModelScaleSet(0x1B, 1.8f, 1.0f, 1.8f);
        op_ModelDispOn(0x1B);
        op_MotionTimeSet(0x1B, 0U);
        op_MotionFlagReset(0x1B, 1);
        op_ModelDispOn(0x1D);
        op_ModelDispOn(0x1E);
        op_ModelDispOn(0x1F);
        HuVecCopyXYZ(&sp480, 0.0f, 0.0f, 300.0f);
        HuVecCopyXYZ(&sp490, 250.0f, 25.0f, 355.0f);
        op_DemoJumpCreate(8, 0x1D, &sp480, &sp490, "star_red", "red_kage");
        HuVecCopyXYZ(&sp490, -250.0f, 25.0f, 355.0f);
        op_DemoJumpCreate(9, 0x1E, &sp480, &sp490, "star_blue", "blue_kage");
        HuVecCopyXYZ(&sp490, 0.0f, 25.0f, 70.0f);
        op_DemoJumpCreate(0xA, 0x1F, &sp480, &sp490, "star_yellow", "yellow_kage");
        op_ModelDispOn(9);
        op_ModelDispOff(0x14);
        for (i = 0x21; i < 0x24; i++) {
            temp_f20 = (f32)i * 0.028571429f;
            temp_f20 = temp_f20 * temp_f20;
            HuVecCopyXYZ(&sp458, (temp_f20 * (sp448.x - sp438.x)) + sp438.x, (temp_f20 * (sp448.y - sp438.y)) + sp438.y, temp_f20 + (sp448.z - sp438.z) + sp438.z);
            op_ModelPosSet(0xB, sp458.x, sp458.y, sp458.z);
            temp_f0_58 = (1250.0f - sp458.y) * 0.0008f;
            op_ModelScaleSet(0x27, temp_f0_58, 1.0f, temp_f0_58);
            HuPrcVSleep();
        }
        op_ModelDispOff(0xB);
        HuPrcSleep(0x2D);
        op_MotionEndWait(0x1B);
        op_ModelDispOff(0x1B);
        op_ModelKill(0x1B);
        op_ModelDispOff(0x27);
        op_ModelKill(0x27);
        HuPrcSleep(0x3C);
        if (storyMode == 0) {
            omDelPrcObj(NULL);
        loop_273:
            HuPrcVSleep();
            goto loop_273;
        }
        Hu3DScreenClearF = 1;
        MBBackKill();
        MBBackLoad(0x22);
        MBCameraKill();
        Hu3DCameraPerspectiveSet(0, 40.0f, 500.0f, 8000.0f);
        op_CameraObjCreate(&op_cameraMainTbl[0], &op_cameraMainTbl[1]);
        AuraKill(op_ModelIdGet(0xB));
        op_DemoObjKill(8);
        op_DemoObjKill(9);
        op_DemoObjKill(0xA);
        op_ModelDispOff(0xB);
        op_ModelKill(0xB);
        op_ModelKill(0x6C);
        op_ModelKill(0x6D);
        op_ModelKill(0x6E);
        op_ModelKill(0x6F);
        op_ModelKill(0x14);
        op_ModelKill(0x15);
        op_ModelKill(0x16);
        op_ModelKill(0x17);
        op_ModelKill(0x18);
        op_ModelKill(0x19);
        op_ModelKill(0x1D);
        op_ModelKill(0x1E);
        op_ModelKill(0x1F);
        op_ModelKill(9);
        op_MotionTimeSet(0x12, 0U);
        op_MotionFlagSet(0x12, 1);
        op_MotionTimeSet(0x13, 0U);
        op_MotionFlagSet(0x13, 1);
        op_ModelDispOff(0x20);
        op_ModelCreate(0x11, 0xA00EE, 0x6A9);
        op_ModelPosSet(0x11, -40.0f, 0.0f, 2775.0f);
        op_ModelScaleSet(0x11, 1.0f, 1.0f, 1.0f);
        op_MotionFlagSet(0x11, 2);
        op_ModelDispOn(0x20);
        op_ModelScaleSet(0x20, 1.0f, 1.0f, 1.0f);
        op_ModelPosSet(0x20, -40.0f, 0.0f, 2775.0f);
        HuVecCopyXYZ(&sp4A0, -880.0f, 0.0f, 2820.0f);
        HuVecCopyXYZ(&sp4B0, -53.0f, 0.0f, 2807.0f);
        op_MotionCreate(0x71, 0xA00F1, 0);
        temp_f20 = 37.0f / 60.0f;
        HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
        op_ModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
        op_ModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
        temp_f0_59 = op_CameraAngleCalc(sp4C0.x, sp4C0.z, op_cameraMainTbl[0].x, op_cameraMainTbl[0].z);
        lastAngles[1] = temp_f0_59;
        op_ModelRotSet(0x11, 0.0f, temp_f0_59, 0.0f);
        op_MotionShiftSet(0x11, 0x71, 8, 8, (s16)2);
        HuPrcSleep(0xA);
        if (storyMode != 0) {
            HuAudFXPlay(0x2A0);
        }
        op_WinDispOn(0);
        op_WinMesSet(0, 0x4D25U);
        HuPrcSleep(0x12);
        op_MotionSpeedSet(0x11, 1.4f);
        for (i = 0; i < 8; i++) {
            temp_f20 = (f32)i * 0.125f;
            op_ModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_60 = op_AngleLerp(lastAngles[1], sp4B0.x - sp4C0.x, sp4B0.z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_60;
            op_ModelRotSet(0x11, 0.0f, temp_f0_60, 0.0f);
            HuPrcVSleep();
        }
        i = 0x25;
        temp_f0_61 = op_CameraAngleCalc(sp4A0.x, sp4A0.z, sp4B0.x, sp4B0.z);
        lastAngles[1] = temp_f0_61;
        lastAngles[0] = temp_f0_61;
        op_ModelRotSet(0x11, 0.0f, temp_f0_61, 0.0f);
        do {
            temp_f20 = (f32)i * 0.016666668f;
            HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
            op_ModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
            op_ModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
            i += 1;
            HuPrcVSleep();
        } while (i < 0x3D);
        op_MotionSpeedSet(0x11, 1.0f);
        op_ModelRotGet(0x11, &lastAngles[0], &lastAngles[1], &lastAngles[0]);
        for (i = 0; i < 0x10; i++) {
            temp_f20 = (f32)i * 0.0625f;
            op_ModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_62 = op_AngleLerp(lastAngles[1], op_cameraMainTbl[0].x - sp4C0.x, op_cameraMainTbl[0].z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_62;
            op_ModelRotSet(0x11, 0.0f, temp_f0_62, 0.0f);
            HuPrcVSleep();
        }
        op_ModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
        if (storyMode != 0) {
            op_WinMesSet(0, 0x4D26U);
            op_WinMesWait(0);
        } else {
            op_WinMesSet(0, 0x4D25U);
            HuPrcSleep(0x46);
        }
        op_WinDispOff(0);
        op_ModelPosGet(0x11, &sp4A0.x, &sp4A0.y, &sp4A0.z);
        HuVecCopyXYZ(&sp4B0, 800.0f, 0.0f, 3030.0f);
        op_ModelRotGet(0x11, &lastAngles[0], &lastAngles[1], &lastAngles[0]);
        for (i = 0; i < 0x10; i++) {
            temp_f20 = (f32)i * 0.0625f;
            op_ModelPosGet(0x11, &sp4C0.x, &sp4C0.y, &sp4C0.z);
            temp_f0_63 = op_AngleLerp(lastAngles[1], sp4B0.x - sp4C0.x, sp4B0.z - sp4C0.z, temp_f20);
            lastAngles[0] = temp_f0_63;
            op_ModelRotSet(0x11, 0.0f, temp_f0_63, 0.0f);
            HuPrcVSleep();
        }
        op_MotionSpeedSet(0x11, 1.4f);
        for (i = 0; i < 0x3D; i++) {
            temp_f20 = (f32)i * 0.016666668f;
            HuVecCopyXYZ(&sp4C0, ((sp4B0.x - sp4A0.x) * temp_f20) + sp4A0.x, ((sp4B0.y - sp4A0.y) * temp_f20) + sp4A0.y, ((sp4B0.z - sp4A0.z) * temp_f20) + sp4A0.z);
            op_ModelPosSet(0x11, sp4C0.x, sp4C0.y, sp4C0.z);
            op_ModelPosSet(0x20, sp4C0.x, sp4C0.y, sp4C0.z);
            HuPrcVSleep();
            if (i == 0xA) {
                op_DemoEndSet(1);
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

void op_DemoEventKill(void) {
    op_WinKillAll();
    op_ContErrorKill();
    op_CameraShakeKill();
    op_WipeKill(15);
    op_DemoObjKillAll();
    op_DemoModelKill();
    op_DemoSprKill();
    MBBackKill();
}

void op_CameraShakeInit(void) {
    op_cameraShake.obj = NULL;
}

void op_CameraShakeKill(void) {
    if (op_cameraShake.obj != NULL) {
        Hu3DCameraViewportSet(0, &op_viewportScale, &op_viewportTrans);
        MBCameraOffsetSet(0, 0);
        omDelObj(op_cameraShake.obj);
    }
    op_cameraShake.obj = NULL;
}

void op_CameraShakeObjMain(omObjData *obj) {
    Vec at;
    f32 random;
    f32 offset;

    op_cameraShake.active = ~op_cameraShake.active;
    if (op_cameraShake.active) {
        random = rand8();
    } else {
        random = -(f32)rand8();
    }
    random *= 1.0f / 255.0f;
    random *= (1.0f - op_cameraShake.frame * 0.125f) * 0.8f + 0.2f;
    offset = random * op_cameraShake.magnitude;
    HuVecCopy3F(&at, &op_viewportTrans);
    at.y = offset + offset + at.y;
    Hu3DCameraViewportSet(0, &op_viewportScale, &at);
    offset = -offset;
    MBCameraOffsetSet(0, offset);
    op_cameraShake.frame++;
    if (op_cameraShake.totalFrames < op_cameraShake.frame) {
        Hu3DCameraViewportSet(0, &op_viewportScale, &op_viewportTrans);
        MBCameraOffsetSet(0, 0);
        op_CameraShakeKill();
    }
}

void op_CameraShakeCreate(s32 totalFrames, f32 magnitude) {
    op_cameraShake.frame = 0;
    op_cameraShake.totalFrames = totalFrames;
    op_cameraShake.magnitude = magnitude;
    op_cameraShake.active = 1;
    op_cameraShake.obj = omAddObj(6, 0, 0, -1, op_CameraShakeObjMain);
}

void op_DemoCharCreate(s32 slot, s32 resourceId, f32 x, f32 y, f32 z) {
    op_ModelCreate(slot, resourceId, 0x6A9);
    op_ModelPosSet(slot, x, y, z);
    op_ModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    op_ModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
    op_MotionFlagSet(slot, 2);
}

void op_DemoShadowCreate(s32 slot, f32 x, f32 y, f32 z) {
    op_ModelCreate(slot, 9, 0x229);
    op_ModelPosSet(slot, x, y, z);
    op_ModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    op_ModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
}

void op_DemoModelKill(void) {
    op_ModelKillAll();
}

void op_DemoSprKill(void) {
    op_SprKillAll();
}

void op_CameraInit(void) {
    op_cameraWork.obj = NULL;
    HuVecCopyXYZ(&op_cameraWork.pos, 350.0f, 190.0f, 3770.0f);
    HuVecCopyXYZ(&op_cameraWork.at, -1000.0f, 130.0f, 450.0f);
    HuVecCopyXYZ(&op_cameraWork.up, 0.0f, 1.0f, 0.0f);
}

void op_CameraObjCreate(Vec *pos, Vec *at) {
    op_CameraObjKill();
    HuVecCopy3F(&op_cameraWork.pos, pos);
    HuVecCopy3F(&op_cameraWork.at, at);
    op_cameraWork.obj = omAddObj(6, 0, 0, -1, op_CameraObjMain);
}

void op_CameraObjKill(void) {
    if (op_cameraWork.obj != NULL) {
        omDelObj(op_cameraWork.obj);
    }
    op_cameraWork.obj = NULL;
}

void op_CameraUpdate(void) {
    Hu3DCameraPosSetV(0, &op_cameraWork.pos, &op_cameraWork.at, &op_cameraWork.up);
    Hu3DCamUpdateMtx(0);
}

void op_CameraObjMain(omObjData *obj) {
    op_CameraUpdate();
}

void op_CameraPosGet(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ) {
    *posX = op_cameraWork.pos.x;
    *posY = op_cameraWork.pos.y;
    *posZ = op_cameraWork.pos.z;
    *atX = op_cameraWork.at.x;
    *atY = op_cameraWork.at.y;
    *atZ = op_cameraWork.at.z;
}

void op_CameraPosSet(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ) {
    HuVecCopyXYZ(&op_cameraWork.pos, posX, posY, posZ);
    HuVecCopyXYZ(&op_cameraWork.at, atX, atY, atZ);
}

f32 op_CameraAngleCalc(f32 x1, f32 z1, f32 x2, f32 z2) {
    return -(atan2df(z2 - z1, x2 - x1) - 90.0f);
}

f32 op_AngleStep(f32 current, f32 target, f32 step) {
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

f32 op_DirLerp(f32 x1, f32 z1, f32 x2, f32 z2, f32 weight) {
    f32 current;
    f32 target;
    f32 forwardTarget;
    f32 backwardTarget;
    f32 angle;
    f32 cross;

    current = op_CameraAngleCalc(0.0f, 0.0f, x1, z1);
    if (current < 0.0f) {
        current += 360.0f;
    }
    target = op_CameraAngleCalc(0.0f, 0.0f, x2, z2);
    if (target < 0.0f) {
        target += 360.0f;
    }
    if ((target - current < 0.0f ? -(target - current) : target - current) < 5.0f) {
        return target;
    }
    cross = -z1 * x2 + x1 * z2;
    if (cross > 0.0f) {
        backwardTarget = target - current < 0.0f ? target : target - 360.0f;
        angle = (backwardTarget - current) * weight + current;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        forwardTarget = target;
        forwardTarget = forwardTarget - current > 0.0f ? forwardTarget : forwardTarget + 360.0f;
        angle = (forwardTarget - current) * weight + current;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
    }
    return angle;
}

f32 op_AngleLerp(f32 current, f32 x, f32 z, f32 weight) {
    f32 angle = op_CameraAngleCalc(0.0f, 0.0f, x, z);
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

void op_SparkTrailExec(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 model1;
    s32 model2;
    Vec pos;
    s32 i;
    f32 t;
    f32 angle;
    f32 size;
    f32 remaining;

    model1 = op_SparkEffCreate(0x110012, 0x689);
    model2 = op_SparkEffCreate(0x110012, 0x689);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    for (i = 0, remaining = 1.0f; i < 120; i++) {
        if (i == 90) {
            op_WinDispOff(0);
        }
        t = i * (1.0f / 120.0f);
        HuSqrtf(t);
        angle = t * 360.0f;
        t = remaining - t;
        size = t * 8.0f;
        pos.x = t * 100.0f * sindf(angle);
        pos.y = 40.0f - pos.x * 0.2f - t * 120.0f * cosdf(angle);
        pos.z = t * 800.0f * cosdf(angle) + -200.0f;
        op_SparkEffAdd(model1, pos.x, pos.y, pos.z, size);
        op_SparkEffAdd(model1, pos.x, pos.y, pos.z, size);
        op_SparkEffAdd(model2, pos.x, pos.y, pos.z, size);
        op_SparkEffAdd(model2, pos.x, pos.y, pos.z, size);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DModelKill(model1);
    Hu3DModelKill(model2);
}

s16 op_SpiralEffCreate(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&op_effPos, 0.0f, 0.0f, 0.0f);
    op_effNum = 0;
    modelId = Hu3DModelRead(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(modelId, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(modelId);
    Hu3DModelVtxBufMake(modelId);
    Hu3DModelDynamicFree(modelId);
    Hu3DParticleCreate(modelId, -1, 0, op_SpiralEffHook);
    data = Hu3DData[modelId].hmf;
    work = Hu3DData[modelId].unkBC;
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

s32 op_SparkEffCreate(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&op_effPos, 0.0f, 0.0f, 0.0f);
    op_effNum = 0;
    modelId = Hu3DModelRead(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(modelId, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(modelId);
    Hu3DModelVtxBufMake(modelId);
    Hu3DModelDynamicFree(modelId);
    Hu3DParticleCreate(modelId, -1, 0, op_SparkEffHook);
    data = Hu3DData[modelId].hmf;
    work = Hu3DData[modelId].unkBC;
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

u32 op_RandSeedCalc(u32 seed) {
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

u32 op_Rand(void) {
    op_randSeed = op_RandSeedCalc(op_randSeed);
    return op_randSeed;
}

u32 op_RandMod(u32 max) {
    u32 value;

    value = op_RandSeedCalc(op_randSeed);
    op_randSeed = value;
    return (value & 0x7FFFFFFF) % max;
}

s32 op_SpiralEffAdd(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *data = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = Hu3DData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    f32 angle;

    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = op_RandMod(360);
            particle->unk20 = work->unk10.f / 10.0f;
            angle = (f32)op_RandMod(150) - 75.0f;
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0.0f;
            particle->unk04 = 0.0f;
            return 1;
        }
    }
    return 0;
}

s32 op_SparkEffAdd(s16 modelId, f32 x, f32 y, f32 z, f32 size) {
    HmfData *data = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    op_effPos.x = x;
    op_effPos.y = x;
    op_effPos.z = x;
    work = Hu3DData[modelId].unkBC;
    particle = work->unk58;
    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk04 = 0.0f;
            particle->unk24 = sindf(op_RandMod(360));
            particle->unk28 = sindf(op_RandMod(360));
            particle->unk2C = sindf(op_RandMod(360));
            particle->unk0C = work->unk1C.f;
            particle->unk14 = work->unk24.f;
            particle->unk10 = work->unk20.f;
            particle->unk08 = size;
            return 1;
        }
    }
    return 0;
}

void op_SpiralEffHook(s16 modelId) {
    HmfData *data = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = Hu3DData[modelId].unkBC;
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

void op_SparkEffHook(s16 modelId) {
    HmfData *data = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = Hu3DData[modelId].unkBC;
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

void op_TitleSetup(void) {
    u16 sprite;

    op_UtilInit();
    op_CameraInit();
    op_ContErrorCreate();
    op_DemoObjInit();
    {
        Vec initPos = op_mesCameraPos;
        Vec initAt = op_mesCameraAt;
        op_CameraObjCreate(&initPos, &initAt);
    }
    op_SprBGCreate(0, 0x100000);
    op_SprPosSet(0, 160, 120);
    espPriSet((u16)op_EspIdGet(0), 9);
    op_SprBGDispOn(0);
    op_SprBGCreate(1, 0x100001);
    op_SprPosSet(1, 160, 120);
    espPriSet((u16)op_EspIdGet(1), 11);
    op_SprBGDispOn(1);
    op_SprBGCreate(2, 0x100002);
    op_SprPosSet(2, 160, 71);
    op_SprAttrSet(2, 8);
    op_SprAlphaSet(2, 255);
    espPriSet((u16)op_EspIdGet(2), 8);
    op_SprBGCreate(3, 0x100005);
    op_SprPosSet(3, 160, 71);
    op_SprAttrSet(3, 8);
    op_SprAlphaSet(3, 255);
    sprite = op_EspIdGet(3);
    espColorSet(sprite, 255, 255, 255);
    espPriSet(sprite, 9);
    op_SprBGCreate(4, 0x100003);
    op_SprPosSet(4, 158, 197);
    op_SprAttrSet(4, 8);
    op_SprAlphaSet(4, 255);
    espPriSet((u16)op_EspIdGet(4), 8);
    op_SprBGCreate(5, 0x100004);
    op_SprPosSet(5, 158, 197);
    op_SprAttrSet(5, 0x1008);
    op_SprAlphaSet(5, 255);
    sprite = op_EspIdGet(5);
    espColorSet(sprite, 0, 6, 115);
    espPriSet(sprite, 9);
}

void op_TitleSprMain(void) {
    s32 frame;
    f32 alpha;
    f32 time;
    f32 speed;
    f32 velocity;
    f32 scale;

    op_SprBGDispOff(2);
    op_SprBGDispOff(3);
    op_SprBGDispOff(4);
    op_SprBGDispOff(5);
    HuAudFXPlay(0x240);
    HuPrcSleep(16);
    for (frame = 0; frame < 40; frame++) {
        HuPrcVSleep();
        alpha = 1.0f - frame * (1.0f / 60.0f);
        alpha = alpha < 0.0f ? 0.0f : alpha;
        op_SprAlphaSet(0, (u8)(alpha * 255.0f));
    }
    op_SprBGDispOn(2);
    op_SprScaleSet(2, 0.0f, 0.0f);
    op_SprScaleSet(3, 0.0f, 0.0f);
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
        op_SprAlphaSet(0, (u8)(alpha * 255.0f));
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
        op_SprScaleSet(2, scale, scale);
        op_SprScaleSet(3, scale, scale);
    }
    HuPrcVSleep();
    op_SprScaleSet(2, 1.0f, 1.0f);
    op_SprScaleSet(3, 1.0f, 1.0f);
    op_SprAlphaSet(0, 0);
    op_SprBGDispOn(4);
    op_SprBGDispOn(5);
    op_SprBankSet(4, 0, 0);
    op_SprBankSet(5, 0, 0);
    op_SprAlphaSet(4, 0);
    op_SprAlphaSet(5, 0);
    espAnimModeSet(op_sprTbl[4].espriteSlot, 0);
    espAnimModeSet(op_sprTbl[5].espriteSlot, 0);
    for (frame = 0; frame < 9; frame++) {
        HuPrcVSleep();
        op_SprAlphaSet(4, frame * 32);
        op_SprAlphaSet(5, frame * 32);
    }
    op_SprAlphaSet(4, 256);
    op_SprAlphaSet(5, 256);
    espAnimModeSet(op_sprTbl[4].espriteSlot, 1);
    espAnimModeSet(op_sprTbl[5].espriteSlot, 1);
    op_ContErrorDispOn();
    HuPrcSleep(780);
    op_ContErrorDispOff();
    omDelPrcObj(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

void op_TitleKill(void) {
    op_SprKill(5);
    op_SprKill(4);
    op_SprKill(3);
    op_SprKill(2);
    op_SprKill(1);
    op_SprKill(0);
    op_ContErrorKill();
    op_DemoObjKillAll();
    op_DemoModelKill();
    op_DemoSprKill();
}

void op_DemoObjInit(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        op_demoObjTbl[i].obj = NULL;
    }
}

void op_DemoObjKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(op_demoObjTbl); i++) {
        op_DemoObjKill(i);
    }
}

void op_DemoObjKill(s32 index) {
    if (op_demoObjTbl[index].obj != NULL) {
        omDelObj(op_demoObjTbl[index].obj);
    }
    op_demoObjTbl[index].obj = NULL;
}

void op_DemoObjCreate(s32 index, omObjFunc func) {
    omObjData *obj;

    op_DemoObjKill(index);
    obj = omAddObj(6, 0, 0, -1, func);
    op_demoObjTbl[index].obj = obj;
    obj->work[0] = index;
}

void op_DemoMotIntervalMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;

    if (op_demoObjTime[index][0] < 0) {
        if (op_MotionEndCheck(modelId)) {
            op_MotionShiftSet(modelId, op_demoObjParamB[index][0].motion[0], 4, 4, 2);
            op_demoObjTime[index][0] = 0;
        }
    } else if (op_demoObjTime[index][0] >= op_demoObjMaxTime[index][0]) {
        op_MotionShiftSet(modelId, op_demoObjParamA[index][0].motion[0], 4, 4, 0);
        op_demoObjTime[index][0] = -1;
    } else {
        op_demoObjTime[index][0]++;
    }
}

void op_DemoMotIntervalCreate(s32 index, s32 modelId, s32 motion1, s32 motion2, s32 startTime, s32 frames) {
    op_DemoObjCreate(index, op_DemoMotIntervalMain);
    op_demoObjWork[index].modelId = modelId;
    op_demoObjParamA[index][0].motion[0] = motion1;
    op_demoObjParamB[index][0].motion[0] = motion2;
    op_demoObjMaxTime[index][0] = frames;
    op_demoObjTime[index][0] = startTime;
    if (startTime >= 0) {
        op_MotionSet(modelId, motion1, 0);
        op_MotionTimeSet(modelId, startTime);
    } else {
        op_MotionSet(modelId, motion2, 2);
        op_MotionTimeSet(modelId, 0);
    }
}

void op_DemoMotRestartMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;

    if (op_demoObjTime[index][0] >= op_demoObjMaxTime[index][0]) {
        op_MotionTimeSet(modelId, 0);
        op_demoObjTime[index][0] = 0;
    } else {
        op_demoObjTime[index][0]++;
    }
}

void op_DemoMotRestartCreate(s32 index, s32 modelId, s32 startTime, s32 endTime) {
    op_DemoObjCreate(index, op_DemoMotRestartMain);
    op_demoObjWork[index].modelId = modelId;
    op_demoObjTime[index][0] = startTime;
    op_demoObjMaxTime[index][0] = endTime;
    op_MotionFlagReset(modelId, 3);
    if (startTime > 0) {
        op_MotionTimeSet(modelId, startTime);
    } else {
        op_MotionTimeSet(modelId, 0);
    }
}

void op_DemoOutEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;
    s32 otherModelId = modelId + 32;
    s16 effectId = op_demoObjParamA[index][0].effectId;
    f32 scale = op_demoObjEndY[index][0];

    HuVecCopy3F(&pos, &op_demoObjParamB[index][0].pos);
    if (op_demoObjTime[index][0] >= 40) {
        Hu3DModelKill(effectId);
        op_demoObjTime[index][0] = 0;
        op_DemoObjKill(index);
    } else if (op_demoObjTime[index][0] >= 20) {
        op_ModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
        op_ModelScaleSet(otherModelId, 3.0f, 1.0f, 3.0f);
        op_ModelDispOff(modelId);
        op_ModelDispOff(otherModelId);
        op_demoObjTime[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        op_SpiralEffAdd(effectId, pos.x, pos.y, pos.z);
        op_ModelScaleSet(modelId, scale, 1.0f, scale);
        op_ModelScaleSet(otherModelId, scale, 1.0f, scale);
        op_demoObjEndY[index][0] = scale;
        op_demoObjTime[index][0]++;
    }
}

void op_DemoOutEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    op_DemoObjCreate(index, op_DemoOutEffMain);
    effectId = op_SpiralEffCreate(0x110012, 0x689);
    op_demoObjWork[index].modelId = modelId;
    op_demoObjParamA[index][0].effectId = effectId;
    op_ModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&op_demoObjParamB[index][0].pos, &pos);
    op_demoObjWork[index].unk_1C.y = 1.0f;
    op_demoObjTime[index][0] = 0;
}

void op_DemoGuideInEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s16 effectId = op_demoObjParamA[index][0].effectId;
    f32 scale = op_demoObjEndY[index][0];

    HuVecCopy3F(&pos, &op_demoObjParamB[index][0].pos);
    if (op_demoObjTime[index][0] >= 80) {
        Hu3DModelKill(effectId);
        op_demoObjTime[index][0] = 0;
        op_DemoObjKill(index);
    } else if (op_demoObjTime[index][0] >= 50) {
        op_demoObjTime[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        op_SpiralEffAdd(effectId, pos.x, pos.y + 25.0f, pos.z);
        op_demoObjEndY[index][0] = scale;
        op_demoObjTime[index][0]++;
    }
}

void op_DemoGuideInEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    op_DemoObjCreate(index, op_DemoGuideInEffMain);
    effectId = op_SpiralEffCreate(0x110012, 0x689);
    op_demoObjWork[index].modelId = modelId;
    op_demoObjParamA[index][0].effectId = effectId;
    op_ModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&op_demoObjParamB[index][0].pos, &pos);
    op_demoObjWork[index].unk_1C.y = 1.0f;
    op_demoObjTime[index][0] = 0;
}

void op_DemoStarWaitMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;
    f32 step = 1.0f / op_demoObjMaxTime[index][0];
    f32 angle = step * 360.0f + op_demoObjEndY[index][0];
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    op_demoObjEndY[index][0] = angle;
    height = sindf(angle) * op_demoObjEndX[index][0];
    HuVecCopy3F(&pos, &op_demoObjParamA[index][0].pos);
    op_ModelPosSet(modelId, pos.x, height + pos.y, pos.z);
}

void op_DemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames) {
    op_DemoObjCreate(index, op_DemoStarWaitMain);
    op_demoObjWork[index].modelId = modelId;
    HuVecCopyXYZ(&op_demoObjParamA[index][0].pos, x, y, z);
    op_demoObjEndX[index][0] = arg5;
    op_demoObjEndY[index][0] = 0;
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = frames;
}

void op_DemoJumpNodeSet(s32 index, Vec *pos1, Vec *pos2, f32 scale, f32 angle) {
    func_80088800_main(op_demoObjBodyNode[index][0]->unk58, pos1->x, pos1->y, pos1->z);
    mtxScaleCat(op_demoObjBodyNode[index][0]->unk58, scale, 1.0f, scale);
    mtxRotYCat(op_demoObjBodyNode[index][0]->unk58, angle);
    func_80088800_main(op_demoObjShadowNode[index][0]->unk58, pos2->x, pos2->y + 4.0f, pos2->z);
    mtxScaleCat(op_demoObjShadowNode[index][0]->unk58, scale, 1.0f, scale);
    mtxRotYCat(op_demoObjShadowNode[index][0]->unk58, angle);
}

void op_DemoFloatMain(omObjData *obj) {
    Vec pos;
    Vec shadow;
    s8 index = obj->work[0];
    f32 step = 1.0f / op_demoObjMaxTime[index][0];
    f32 angle = step * 360.0f + op_demoObjParamB[index][0].pos.x;
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    op_demoObjParamB[index][0].pos.x = angle;
    height = sindf(angle) * op_demoObjParamB[index][0].pos.y;
    HuVecCopy3F(&pos, &op_demoObjAngleX[index][0].pos);
    pos.y = height + pos.y;
    HuVecCopy3F(&shadow, &op_demoObjAngleX[index][0].pos);
    shadow.y = 0;
    op_DemoJumpNodeSet(index, &pos, &shadow, 1.0f, 0);
}

void op_DemoJumpMain(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec modelPos;
    Vec shadow;
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;
    OpWork *slot = &op_demoObjWork[index];
    f32 time;

    HuVecCopy3F(&start, &slot->unk_1C);
    HuVecCopy3F(&end, &slot->unk_28);
    time = 1.0f / op_demoObjMaxTime[index][0];
    time *= op_demoObjTime[index][0];
    HuVecCopyXYZ(&pos, time * (end.x - start.x) + start.x,
                 time * (end.y - start.y) + start.y + (0.25 - (time - 0.5f) * (time - 0.5f)) * 4.0 * 5.0 * 20.0,
                 time * (end.z - start.z) + start.z);
    HuVecCopy3F(&start, &slot->unk_1C);
    op_ModelPosSet(modelId, 0, 0, 0);
    HuVecCopyXYZ(&modelPos, pos.x, pos.y, pos.z);
    HuVecCopyXYZ(&shadow, pos.x, 0, pos.z);
    time = time * 0.8 + 0.2f;
    op_DemoJumpNodeSet(index, &modelPos, &shadow, time, 0);
    if (op_demoObjTime[index][0] >= op_demoObjMaxTime[index][0]) {
        op_demoObjTime[index][0] = 0;
        obj->func = op_DemoFloatMain;
    } else {
        op_demoObjTime[index][0]++;
    }
}

void op_DemoJumpCreate(s32 index, s32 modelId, Vec *pos1, Vec *pos2, char *node1, char *node2) {
    s16 model;
    OpWork *slot;

    op_DemoObjCreate(index, op_DemoJumpMain);
    op_demoObjWork[index].modelId = modelId;
    slot = &op_demoObjWork[index];
    HuVecCopy3F(&slot->unk_1C, pos1);
    HuVecCopy3F(&slot->unk_28, pos2);
    op_demoObjParamB[index][0].pos.y = 12.0f;
    op_demoObjParamB[index][0].pos.x = 0;
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = 20;
    model = op_ModelIdGet(modelId);
    op_demoObjBodyNode[index][0] = Hu3DModelObjPtrGet(model, node1);
    op_demoObjShadowNode[index][0] = Hu3DModelObjPtrGet(model, node2);
    op_DemoJumpMain(op_demoObjTbl[index].obj);
}

void op_DemoFlyMain(omObjData *obj) {
    Vec oldPos;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;
    s32 frame = op_demoObjTime[index][0];
    f32 xAngle = op_demoObjAngleX[index][0].pos.x;
    f32 yAngle = op_demoObjAngleY[index][0];
    f32 zAngle = op_demoObjAngleZ[index][0];

    oldPos.x = sindf(xAngle) * 65.0f + op_demoObjParamA[index][0].pos.x;
    oldPos.y = (sindf(yAngle) + 1.0f) * 20.0f + op_demoObjParamB[index][0].pos.x;
    oldPos.z = cosdf(zAngle) * 11.0f + op_demoObjParamA[index][0].pos.z;
    xAngle = xAngle + 1.45f < 360.0f ? xAngle + 1.45f : xAngle - 360.0f + 1.45f;
    yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
    zAngle = zAngle + 0.8f < 360.0f ? zAngle + 0.8f : zAngle - 360.0f + 0.8f;
    pos.x = op_demoObjParamA[index][0].pos.x + sindf(xAngle) * 65.0f;
    pos.y = (sindf(yAngle) + 1.0f) * 20.0f + op_demoObjParamB[index][0].pos.x;
    pos.z = cosdf(zAngle) * 11.0f + op_demoObjParamA[index][0].pos.z;
    op_ModelPosSet(modelId, pos.x, pos.y, pos.z);
    op_ModelRotSet(modelId, 0, op_CameraAngleCalc(oldPos.x, oldPos.z, pos.x, pos.z), 0);
    frame++;
    frame = frame <= 256 ? frame : 0;
    op_demoObjTime[index][0] = frame;
    op_demoObjAngleX[index][0].pos.x = xAngle + (rand8() & 7) * 0.3f;
    op_demoObjAngleY[index][0] = yAngle + (rand8() & 3) * 0.3f;
    op_demoObjAngleZ[index][0] = zAngle;
}

void op_DemoFlyAwayMain(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = op_demoObjWork[index].modelId;
    s32 frame = op_demoObjTime[index][0];
    f32 time = 1.0f / op_demoObjMaxTime[index][0];
    f32 xAngle;
    f32 yAngle;
    f32 zAngle;

    time *= op_demoObjTime[index][0];
    frame++;
    if (time < 1.0f) {
        HuVecCopyXYZ(&start, op_demoObjParamA[index][0].pos.x, op_demoObjParamB[index][0].pos.x,
                     op_demoObjParamA[index][0].pos.z);
        HuVecCopyXYZ(&end, op_demoObjEndX[index][0], op_demoObjEndY[index][0], op_demoObjWork[index].unk_1C.z);
        xAngle = op_demoObjAngleX[index][0].pos.x;
        yAngle = op_demoObjAngleY[index][0];
        zAngle = op_demoObjAngleZ[index][0];
        pos.x = (end.x - start.x) * time + start.x;
        pos.y = (end.y - start.y) * time + start.y;
        pos.z = (end.z - start.z) * time + start.z;
        yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
        pos.y = (sindf(yAngle) + 1.0f) * 20.0f + pos.y;
        op_ModelPosSet(modelId, pos.x, pos.y, pos.z);
        op_ModelRotSet(modelId, 0, op_CameraAngleCalc(pos.x, pos.z, end.x, end.z), 0);
        op_demoObjTime[index][0] = frame;
        op_demoObjAngleX[index][0].pos.x = xAngle;
        op_demoObjAngleY[index][0] = yAngle;
        op_demoObjAngleZ[index][0] = zAngle;
    } else {
        op_DemoObjKill(index);
    }
    op_demoObjTime[index][0] = frame;
}

void op_DemoFlyAwaySet(s32 index, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;
    OpWork *slot;

    op_ModelPosGet(op_demoObjWork[index].modelId, &pos.x, &pos.y, &pos.z);
    slot = &op_demoObjWork[index];
    HuVecCopy3F(&slot->pos, &pos);
    HuVecCopyXYZ(&slot->unk_1C, x, y, z);
    op_demoObjAngleX[index][0].motion[0] = 0;
    op_demoObjAngleY[index][0] = 0;
    op_demoObjAngleZ[index][0] = 0;
    op_demoObjTbl[index].obj->func = op_DemoFlyAwayMain;
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = arg4;
}

void op_DemoFlyCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z) {
    OpObj *slot;

    op_DemoObjCreate(index, op_DemoFlyMain);
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = 20;
    op_demoObjWork[index].modelId = modelId;
    slot = &op_demoObjTbl[index];
    slot->unk_2C.x = slot->unk_2C.y = 0;
    op_demoObjAngleX[index][0].pos.x = 0;
    op_demoObjAngleX[index][0].pos.x = rand8();
    op_demoObjAngleY[index][0] = rand8();
    op_demoObjParamA[index][0].pos.x = x;
    op_demoObjParamB[index][0].pos.x = y;
    op_demoObjParamA[index][0].pos.z = z;
    op_DemoFlyMain(op_demoObjTbl[index].obj);
}

void op_WipeDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    if (op_demoObjTbl[15].color.a != 0) {
        gSPDisplayList((*gfx)++, op_wipeDl);
        gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*gfx)++, 0, 0, op_demoObjTbl[15].color.r, op_demoObjTbl[15].color.g,
                        op_demoObjTbl[15].color.b, op_demoObjTbl[15].color.a);
        gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
    }
}

void op_WipeColorSet(s32 arg0, u8 red, u8 green, u8 blue, u8 alpha) {
    op_demoObjTbl[arg0].color.r = red;
    op_demoObjTbl[arg0].color.b = blue;
    op_demoObjTbl[arg0].color.g = green;
    op_demoObjTbl[arg0].color.a = alpha;
}

void op_WipeInMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = op_demoObjTime[index][0];
    s32 totalFrames = op_demoObjMaxTime[index][0];
    u8 red = op_demoObjTbl[index].color.r;
    u8 blue = op_demoObjTbl[index].color.b;
    u8 green = op_demoObjTbl[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 0.0f;
        op_WipeKill(index);
    } else {
        alpha = (1.0f / totalFrames) * (totalFrames - frame);
        op_demoObjTime[index][0]++;
    }
    op_WipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void op_WipeOutMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = op_demoObjTime[index][0];
    s32 totalFrames = op_demoObjMaxTime[index][0];
    u8 red = op_demoObjTbl[index].color.r;
    u8 blue = op_demoObjTbl[index].color.b;
    u8 green = op_demoObjTbl[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 1.0f;
    } else {
        alpha = (1.0f / totalFrames) * frame;
        op_demoObjTime[index][0]++;
    }
    op_WipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void op_WipeKill(s32 index) {
    if (op_demoObjTbl[index].obj != NULL) {
        Hu3DModelKill(op_demoObjTbl[index].effectId);
        op_DemoObjKill(index);
    }
}

void op_WipeInCreate(s32 index, s32 totalFrames) {
    op_WipeKill(index);
    op_DemoObjCreate(index, op_WipeInMain);
    op_demoObjTbl[index].effectId = Hu3DHookFuncCreate(0, op_WipeDraw, 6);
    op_WipeColorSet(index, 0, 0, 0, 255);
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = totalFrames;
}

void op_WipeOutCreate(s32 index, s32 totalFrames) {
    op_WipeKill(index);
    op_DemoObjCreate(index, op_WipeOutMain);
    op_demoObjTbl[index].effectId = Hu3DHookFuncCreate(0, op_WipeDraw, 6);
    op_WipeColorSet(index, 0, 0, 0, 255);
    op_demoObjTime[index][0] = 0;
    op_demoObjMaxTime[index][0] = totalFrames;
}

void op_WipeWhiteInCreate(s32 index, s32 totalFrames) {
    op_WipeInCreate(index, totalFrames);
    op_WipeColorSet(index, 255, 255, 255, 255);
}

void op_WipeWhiteOutCreate(s32 index, s32 totalFrames) {
    op_WipeOutCreate(index, totalFrames);
    op_WipeColorSet(index, 255, 255, 255, 255);
}

void op_CharAnimKill(s32 character) {
    if (CharAnimId[character][2] != 0xFF) {
        Hu3DAnimKill(CharAnimId[character][2]);
        Hu3DAnimKill(CharAnimSrc[character][2]);
        CharAnimId[character][2] = 0xFF;
    }
}

void op_Sleep(s32 frames) {
    HuPrcSleep(frames);
}

void op_ContErrorCreate(void) {
    if (GWContErrorGet() == 0) {
        op_contError.animId = HuSprAnimDataRead(0x100005);
        op_contError.espriteSlot = espEntry(op_contError.animId, 0, 1);
        espPosSet(op_contError.espriteSlot, 0xA0, 0xA8);
        espPriSet(op_contError.espriteSlot, 0);
        espDispOff(op_contError.espriteSlot);
    }
}

void op_ContErrorDispOn(void) {
    if (GWContErrorGet() == 0) {
        espDispOn(op_contError.espriteSlot);
    }
}

void op_ContErrorDispOff(void) {
    if (GWContErrorGet() == 0) {
        espDispOff(op_contError.espriteSlot);
    }
}

void op_ContErrorKill(void) {
    if (GWContErrorGet() == 0) {
        espKill(op_contError.espriteSlot);
        HuSprAnimKill(op_contError.animId);
    }
}
