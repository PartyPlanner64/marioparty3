#include "common.h"
#include "option.h"
#include "game/mallocblock.h"

extern const Vec option_soundRoomCameraPos;
extern const Vec option_soundRoomCameraAt;
extern const Vec option_recordRoomCameraPos;
extern const Vec option_recordRoomCameraAt;
extern const Vec option_roomCameraPos;
extern const Vec option_roomCameraAt;
extern u8 saveCommonBuf;

void option_MenuWinCreate(s32, u32);
void option_MenuSprPosGet(s32, s32 *, s32 *);
void option_MenuMdlDispOn(s32);
void option_MenuMdlDispOff(s32);
void option_MenuWinMesWait(s32);
void option_MenuWinDispOn(s32);
s32 option_StickBtnGet(s32);
void option_MenuWinKill(s32);
void option_MenuMdlCreateEx(s32, s32, f32, f32, f32);
void option_MenuMotSet(s32, s32, u16);
void option_MenuMotFlagSet(s32, s32);
void option_MenuMotFlagReset(s32, s32);
void option_MenuMotTimeSet(s32, u32);
void option_MenuMdlCreate(s32, s32, f32, f32, f32);
void option_MenuCamMdlCreate(s32, s32, f32, f32, f32);
void option_MenuMotCreate(s32, s32, s32);
void option_CameraPosSet(Vec *, Vec *, Vec *);
void option_CursorSprCreate(void);
s32 option_CameraPosGet(Vec *, Vec *, Vec *);
void option_MenuMdlPosGet(s32, f32 *, f32 *, f32 *);
void option_MenuMdlRotSet(s32, f32, f32, f32);
void option_CameraProcKill(void);
void option_MenuInit(void);
void option_SprPosSet(s32, s32, s32);
void option_SprInit(void);
void option_ModelInit(void);
void option_WinInit(void);
void option_MotionCreate(s32, s32, s32);
void option_WinCreate(s32, u32, s16, s16, u16, u16, s16);
s32 option_WinType0Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type);
s32 option_WinType1Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type);
s32 option_WinType2Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type);
s32 option_WinType3Create(s32 message, s16 x, s16 y, s16 type);
s32 option_WinType4Create(s32 message, s16 x, s16 y, s16 type);
s32 option_WinType5Create(s32 message, s16 x, s16 y, s16 type);
void option_WinKill(s32);
void option_WinMesSet(s32, u32);
void option_MenuSprPosSet(s32, s32, s32);
void option_CursorSprKill(void);
s32 option_MenuMdlIdGet(s32);
void option_MenuMotShiftSet(s32, s32, s16, s16, u16);
void option_MenuSprDispOn(s32);
void option_MenuSprDispOff(s32);
void option_MenuWinMesSet(s32, u32);
void option_MenuWinDispOff(s32);
s32 option_MenuWinChoiceGet(s32);
void option_SoundRoomInit(void);
void option_MenuMotEndWait(s32);
void option_SoundRoomClose(void);
void option_CameraInit(void);
void option_CameraPerspectiveSet(f32 fov, f32 nearPlane, f32 farPlane);
void option_CameraMotionStart(s32 camId, f32 fov);
void option_CameraManualStart(f32 fov);

s32 option_stickBtn = 0;

OptSpr option_sprTbl[0x40] BSS;
OptSprSlot option_animTbl[0x40] BSS;
UnkOption option_modelTbl[0x40] BSS;
s16 option_bgAnim BSS;
u16 option_bgSpr BSS;
u8 option_bgSprPad[4] BSS; /* Unreferenced. */
OptWinEntry option_winTbl[0x20] BSS;

void option_UtilInit(void) {
    option_SprInit();
    option_ModelInit();
    option_WinInit();
}

void option_SprInit(void) {
    s32 i;
    OptSpr *p;
    f32 zero;

    for (i = 0; i < ARRAY_COUNT(option_sprTbl); i++) {
        option_animTbl[i].espriteSlot = -1;
        option_sprTbl[i].espriteSlot = -1;
        p = &option_sprTbl[i];
        zero = 0.0f;
        p->unk_08 = 0;
        option_sprTbl[i].unk_04 = 0;
        p->unk_10 = zero;
        option_sprTbl[i].unk_0C = zero;
        option_sprTbl[i].unk_14 = zero;
        option_sprTbl[i].unk_18 = -1;
    }
}

s16 option_AnimIdGet(s32 arg0) {
    return option_animTbl[arg0].espriteSlot;
}

s16 option_EspIdGet(s32 arg0) {
    return option_sprTbl[arg0].espriteSlot;
}

void option_AnimCreate(s32 arg0, s32 arg1) {
    option_animTbl[arg0].espriteSlot = HuSprAnimDataRead(arg1);
}

void option_AnimKill(s32 arg0) {
    if (option_animTbl[arg0].espriteSlot != -1) {
        HuSprAnimKill(option_animTbl[arg0].espriteSlot);
    }
    option_animTbl[arg0].espriteSlot = -1;
}

void option_EspCreate(s32 arg0, s16 arg1) {
    option_sprTbl[arg0].espriteSlot = espEntry(option_animTbl[arg1].espriteSlot, 0, 0);
    option_SprPosSet(arg0, 0xA0, 0x78);
}

void option_EspKill(s32 arg0) {
    if (option_sprTbl[arg0].espriteSlot != -1) {
        espKill(option_sprTbl[arg0].espriteSlot);
    }
    option_sprTbl[arg0].espriteSlot = -1;
}

void option_SprCreate(s32 arg0, s32 resourceId) {
    option_AnimCreate(arg0, resourceId);
    option_EspCreate(arg0, arg0);
}

void option_SprBGCreate(s32 arg0, s32 resourceId) {
    option_SprCreate(arg0, resourceId);
    espAttrSet(option_sprTbl[arg0].espriteSlot, 0x4000);
}

void option_SprKill(s32 arg0) {
    option_EspKill(arg0);
    option_AnimKill(arg0);
}

void option_SprKillAll(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(option_sprTbl); i++) {
        option_SprKill(i);
    }
}

void option_SprDispOn(s32 arg0) {
    espDispOn(option_sprTbl[arg0].espriteSlot);
}

void option_SprDispOff(s32 arg0) {
    espDispOff(option_sprTbl[arg0].espriteSlot);
}

void option_SprBGDispOn(s32 arg0) {
    option_SprDispOn(arg0);
}

void option_SprBGDispOff(s32 arg0) {
    option_SprDispOff(arg0);
}

void option_SprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    option_sprTbl[arg0].unk_04 = arg1;
    option_sprTbl[arg0].unk_08 = arg2;
    espPosSet(option_sprTbl[arg0].espriteSlot, arg1, arg2);
}

void option_SprPosGet(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = option_sprTbl[arg0].unk_04;
    *arg2 = option_sprTbl[arg0].unk_08;
}

void option_SprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    option_sprTbl[arg0].unk_0C = arg1;
    option_sprTbl[arg0].unk_10 = arg2;
    espScaleSet(option_sprTbl[arg0].espriteSlot, arg1, arg2);
}

void option_SprAlphaSet(s32 arg0, u16 arg1) {
    espTPLvlSet(option_sprTbl[arg0].espriteSlot, arg1);
}

void option_SprAttrSet(s32 arg0, u16 arg1) {
    espAttrSet(option_sprTbl[arg0].espriteSlot, arg1);
}

void option_SprAttrReset(s32 arg0, u16 arg1) {
    espAttrReset(option_sprTbl[arg0].espriteSlot, arg1);
}

void option_SprPriSet(s32 arg0, u16 arg1) {
    espPriSet(option_sprTbl[arg0].espriteSlot, arg1);
}

void option_SprBankSet(s32 arg0, u16 arg1, u16 arg2) {
    espAnimModeSet(option_sprTbl[arg0].espriteSlot, 1);
    espBankSet(option_sprTbl[arg0].espriteSlot, arg1, arg2);
}

void option_ModelInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(option_modelTbl); i++) {
        option_modelTbl[i].unk_00 = -1;
        option_modelTbl[i].unk_02 = -1;
    }
}

void option_ModelCreate(s32 arg0, s32 arg1, s32 arg2) {
    s16 model;

    model = Hu3DModelRead(arg1, arg2);
    option_modelTbl[arg0].unk_00 = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void option_MotionCreate(s32 arg0, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    option_modelTbl[arg0].unk_02 = Hu3DMotionCreate(data, (s16)arg2);
    DataClose(data);
}

void option_ModelKill(s32 arg0) {
    if (option_modelTbl[arg0].unk_00 != -1) {
        Hu3DModelKill(option_modelTbl[arg0].unk_00);
        option_modelTbl[arg0].unk_00 = -1;
    }
    if (option_modelTbl[arg0].unk_02 != -1) {
        Hu3DMotionKill(option_modelTbl[arg0].unk_02);
        option_modelTbl[arg0].unk_02 = -1;
    }
}

void option_ModelKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(option_modelTbl); i++) {
        option_ModelKill(i);
    }
}

s16 option_ModelIdGet(s32 arg0) {
    return option_modelTbl[arg0].unk_00;
}

s16 option_MotionIdGet(s32 arg0) {
    return option_modelTbl[arg0].unk_02;
}

void option_ModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    option_modelTbl[arg0].unk_1C = arg1;
    option_modelTbl[arg0].unk_20 = arg2;
    option_modelTbl[arg0].unk_24 = arg3;
    Hu3DModelRotSet(option_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void option_ModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    option_modelTbl[arg0].unk_04 = arg1;
    option_modelTbl[arg0].unk_08 = arg2;
    option_modelTbl[arg0].unk_0C = arg3;
    Hu3DModelPosSet(option_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void option_ModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    option_modelTbl[arg0].unk_10 = arg1;
    option_modelTbl[arg0].unk_14 = arg2;
    option_modelTbl[arg0].unk_18 = arg3;
    Hu3DModelScaleSet(option_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void option_ModelPosGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = option_modelTbl[arg0].unk_04;
    *arg2 = option_modelTbl[arg0].unk_08;
    *arg3 = option_modelTbl[arg0].unk_0C;
}

void option_ModelRotGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = option_modelTbl[arg0].unk_1C;
    *arg2 = option_modelTbl[arg0].unk_20;
    *arg3 = option_modelTbl[arg0].unk_24;
}

void option_ModelScaleGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = option_modelTbl[arg0].unk_10;
    *arg2 = option_modelTbl[arg0].unk_14;
    *arg3 = option_modelTbl[arg0].unk_18;
}

void option_ModelDispOff(s32 arg0) {
    Hu3DModelAttrSet(option_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void option_ModelDispOn(s32 arg0) {
    Hu3DModelAttrSet(option_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void option_MotionFlagSet(s32 arg0, s32 arg1) {
    Hu3DMotionAttrSet(option_modelTbl[arg0].unk_00, -1, arg1);
}

void option_MotionShiftSet(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
    Hu3DMotionShiftSet(option_modelTbl[arg0].unk_00, option_modelTbl[arg1].unk_02, arg2, arg3, arg4);
}

void option_MotionFlagReset(s32 arg0, s32 arg1) {
    Hu3DMotionAttrSet(option_modelTbl[arg0].unk_00, arg1, 0);
}

void option_MotionSpeedSet(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())Hu3DMotionSpeedSet;

    setModelScale(option_modelTbl[arg0].unk_00);
}

void option_MotionTimeSet(s32 arg0, u32 arg1) {
    Hu3DMotionTimeSet(option_modelTbl[arg0].unk_00, arg1);
}

void option_MotionEndWait(s32 arg0) {
    while (Hu3DData[option_modelTbl[arg0].unk_00].motTime != Hu3DMotion[Hu3DData[option_modelTbl[arg0].unk_00].motId].unk02) {
        HuPrcVSleep();
    }
}

s32 option_MotionEndCheck(s32 arg0) {
    s16 modelId = option_modelTbl[arg0].unk_00;

    return Hu3DData[modelId].motTime == Hu3DMotion[Hu3DData[modelId].motId].unk02;
}

void option_MotionSet(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = option_ModelIdGet(arg0);
    s16 parentModelId = option_MotionIdGet(arg1);

    Hu3DMotionSet(modelId, parentModelId);
    Hu3DMotionAttrSet(modelId, -1, arg2);
}

void option_BGSprCreate(void) {
    // The original call omits the resource id.
    option_bgAnim = ((s16 (*)())HuSprAnimDataRead)();
    option_bgSpr = espEntry(option_bgAnim, 0, 0);
    espAttrSet(option_bgSpr, 0x4000);
    espPosSet(option_bgSpr, 0xA0, 0x78);
}

void option_BGSprKill(void) {
    espKill(option_bgSpr);
    HuSprAnimKill(option_bgAnim);
}

u32 option_WinMesConv(u32 arg0) {
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

void option_WinCreate(s32 arg0, u32 message, s16 x, s16 y, u16 width, u16 height, s16 type) {
    s32 winID;
    u32 ptr;

    switch (type) {
        case 1:
            ptr = option_WinMesConv(message);
            winID = option_WinType1Create(ptr, x, y, width, height, type);
            break;
        case 2:
            ptr = option_WinMesConv(message);
            winID = option_WinType2Create(ptr, x, y, width, height, type);
            break;
        case 3:
            ptr = option_WinMesConv(message);
            winID = option_WinType3Create(ptr, x, y, type);
            break;
        case 4:
            ptr = option_WinMesConv(message);
            winID = option_WinType4Create(ptr, x, y, type);
            break;
        case 5:
            ptr = option_WinMesConv(message);
            winID = option_WinType5Create(ptr, x, y, type);
            break;
        case 0:
            ptr = option_WinMesConv(message);
            winID = option_WinType0Create(ptr, x, y, width, height, type);
            break;
        default:
            ptr = option_WinMesConv(message);
            winID = option_WinType0Create(ptr, x, y, width, height, type);
            break;
    }
    if (0x80000000U < ptr) {
        option_winTbl[arg0].unk_04 = (void *)ptr;
    }
    option_winTbl[arg0].winID = winID;
}

s32 option_WinType0Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type) {
    s16 winID;

    winID = HuWinCreate(x, y, width, height, 0, 8);
    HuWinAttrSet(winID, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(winID, 0);
    HuWinBGTPLvlSet(winID, 255);
    HuWinDummy(winID);
    HuWinPriSet(winID, 1);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinMesDefColSet(winID, 192, 192, 192);
    HuWinBGColSet(winID, 0, 64, 64);
    HuWinMesColSet(winID, 7);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinHomeClear(winID);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

s32 option_WinType1Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type) {
    s16 winID;

    winID = HuWinCreate(x, y, width, height, 0, 4);
    HuWinAttrSet(winID, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(winID, 0);
    HuWinBGTPLvlSet(winID, 255);
    HuWinDummy(winID);
    HuWinPriSet(winID, 1);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinMesPalSet(winID, 5, 0, 176, 192);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinMesDefColSet(winID, 192, 192, 192);
    HuWinBGColSet(winID, 255, 255, 255);
    HuWinMesColSet(winID, 1);
    HuWinHomeClear(winID);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

s32 option_WinType2Create(s32 message, s16 x, s16 y, s16 width, s16 height, s16 type) {
    s16 winID;

    winID = HuWinCreate(x, y, width, height, 0, 8);
    HuWinAttrSet(winID, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(winID, 0);
    HuWinDummy(winID);
    HuWinPriSet(winID, 1);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinMesPalSet(winID, 5, 0, 176, 192);
    HuWinMesPalSet(winID, 7, 255, 255, 255);
    HuWinMesPalSet(winID, 0, 0, 0, 0);
    HuWinMesPalSet(winID, 3, 0, 0, 0);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinMesDefColSet(winID, 192, 192, 0);
    HuWinBGColSet(winID, 255, 255, 255);
    HuWinMesColSet(winID, 6);
    HuWinHomeClear(winID);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

s32 option_WinType3Create(s32 message, s16 x, s16 y, s16 type) {
    s16 winID;

    winID = HuWinExCreateStyled(x, y, 19);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinExOpen(winID, 1);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

s32 option_WinType4Create(s32 message, s16 x, s16 y, s16 type) {
    s16 winID;

    winID = HuWinExCreateStyled(x, y, 20);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinExOpen(winID, 0);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

s32 option_WinType5Create(s32 message, s16 x, s16 y, s16 type) {
    s16 winID;

    winID = HuWinExCreateStyled(x, y, 19);
    HuWinMesPalSet(winID, 2, 255, 64, 64);
    HuWinMesPalSet(winID, 4, 96, 255, 64);
    HuWinMesPalSet(winID, 6, 255, 255, 64);
    HuWinActivePlayerSet(winID, HUWIN_PLAYER_1);
    HuWinExOpen(winID, 0);
    HuWinMesSet(winID, message, -1, -1);
    return winID;
}

void option_WinInit(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        option_winTbl[i].winID = -1;
        option_winTbl[i].unk_04 = 0;
    }
}

void option_WinKill(s32 arg0) {
    if (option_winTbl[arg0].unk_08 == 3) {
        HuWinExClose(option_winTbl[arg0].winID, 1);
        HuWinExCleanup(option_winTbl[arg0].winID);
    } else {
        HuWinDispOff(option_winTbl[arg0].winID);
        HuWinKill(option_winTbl[arg0].winID);
        option_winTbl[arg0].winID = -1;
    }
    if (option_winTbl[arg0].unk_04 != NULL) {
        HuMemDelayFree(option_winTbl[arg0].unk_04);
        option_winTbl[arg0].unk_04 = NULL;
    }
}

void option_WinKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(option_winTbl); i++) {
        if (option_winTbl[i].winID != -1) {
            option_WinKill(i);
        }
    }
}

void option_WinScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinScaleSet(option_winTbl[arg0].winID, arg1, arg2);
}

void option_WinPosSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinPosSet(option_winTbl[arg0].winID, arg1, arg2);
}

void option_WinDispOn(s32 arg0) {
    HuWinDispOn(option_winTbl[arg0].winID);
}

void option_WinDispOff(s32 arg0) {
    HuWinDispOff(option_winTbl[arg0].winID);
}

void option_WinMesSet(s32 arg0, u32 arg1) {
    u32 message;

    HuWinHomeClear(option_winTbl[arg0].winID);
    if (option_winTbl[arg0].unk_04 != NULL) {
        HuMemDelayFree(option_winTbl[arg0].unk_04);
        option_winTbl[arg0].unk_04 = NULL;
    }
    message = option_WinMesConv(arg1);
    if (message > 0x80000000U) {
        option_winTbl[arg0].unk_04 = (void *)message;
    }
    HuWinMesSet(option_winTbl[arg0].winID, message, -1, -1);
}

void option_WinInsertMesSet(s32 arg0, s8 arg1, u32 arg2) {
    HuWinInsertMesSetNoLF(option_winTbl[arg0].winID, arg2, arg1);
}

s32 option_WinChoiceGet(s32 arg0, s16 arg1, s32 arg2) {
    return HuWinChoiceGet(option_winTbl[arg0].winID, arg1, arg2);
}

s16 option_WinIdGet(s32 arg0) {
    return option_winTbl[arg0].winID;
}

void option_WinMesWait(s32 arg0) {
    while (HuWinStatGet(option_winTbl[arg0].winID) != 0) {
        HuPrcVSleep();
    }
}

void option_PadBtnWait(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & HuPadBtnDown[0]));
}

void option_WinPriSet(s32 arg0, s16 arg1) {
    HuWinPriSet(option_winTbl[arg0].winID, arg1);
}

u16 option_CameraDebugExecB(s32 value) {
    static const char exitFormat[] = "\n%d\n";
    static const char posFormat[] = "POS:%4.2f,%4.2f,%4.2f";
    static const char atFormat[] = "A T:%4.2f,%4.2f,%4.2f";
    static const char upFormat[] = "U P:%4.2f,%4.2f,%4.2f";
    static const char valueFormat[] = "%d";
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, exitFormat, value);
            break;
        }
        if (HuPadBtnDown[0] & Z_TRIG) {
            cam = Hu3DData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, posFormat, cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, atFormat, cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, upFormat, cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, valueFormat, value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return HuPadBtnDown[0];
}

void option_MenuSprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    option_SprPosSet(arg0, arg1, arg2);
}

void option_MenuSprAlphaSet(s32 arg0, u16 arg1) {
    option_SprAlphaSet(arg0, arg1);
}

void option_MenuInit(void) {
    option_UtilInit();
    option_CameraInit();
}

void option_RoomInit(void) {
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;

    option_MenuCamMdlCreate(0, 0xE0004, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(1, 0xE0007, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(3, 0xE0009, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(4, 0xE000A, 0.0f, 0.0f, 0.0f);
    option_MotionFlagSet(4, 2);
    option_MenuMotCreate(6, 0xE0005, 1);
    option_MenuMotCreate(7, 0xE0006, 1);
    option_MenuMdlCreate(9, 0xA0000, -385.0f, -6.25f, -500.0f);
    option_ModelScaleSet(9, 0.75f, 0.75f, 0.75f);
    option_MotionFlagSet(9, 2);
    option_MenuMdlCreate(10, 0xA0000, 385.0f, -6.25f, -500.0f);
    option_ModelScaleSet(10, 0.75f, 0.75f, 0.75f);
    option_MotionFlagSet(10, 2);
    CharAnimCreate(option_MenuMdlIdGet(9), 0, 10, 0xA002A);
    model = option_MenuMdlIdGet(10);
    CharAnimCreate(model, 0, 10, 0xA002A);
    CharAnimFrameSet(model, 0, 10, 1, 0);
    option_MenuMotCreate(11, 0xA001D, 1);
    option_MenuMotCreate(12, 0xA001E, 1);
    option_MenuMotCreate(13, 0xA001D, 1);
    option_MenuMotCreate(14, 0xA001E, 1);
    option_MenuMotCreate(15, 0xA0001, 1);
    option_MenuMdlCreate(20, 9, -385.0f, 0.049999997f, -500.0f);
    option_MenuMdlCreate(21, 9, 385.0f, 0.049999997f, -500.0f);
    option_CameraMotionStart((s16)option_MenuMdlIdGet(0), 68.0f);
    option_CameraPerspectiveSet(68.0f, 45.0f, 3200.0f);
    option_CameraManualStart(68.0f);
    pos = option_roomCameraPos;
    at = option_roomCameraAt;
    option_CameraPosGet(&cameraPos, &cameraAt, &up);
    option_CameraPosSet(&pos, &at, &up);
    option_CursorSprCreate();
}

void option_RoomClose(void) {
    option_CursorSprKill();
    option_CameraProcKill();
    option_ModelKillAll();
    option_SprKillAll();
    option_WinKillAll();
}

const Vec option_roomCameraPos = { 0.0f, 271.19f, 841.11f };

const Vec option_roomCameraAt = { 0.0f, 228.72f, -550.0f };

void option_SoundRoomInit(void) {
    static const char parrot[] = "oumu0_1_DEF";
    static const char trumpet[] = "tranpet_DEF";
    static const char drum[] = "doramu2_DEF";
    static const char cymbal[] = "sinbaru_DEF";
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;
    void *data;

    option_MenuCamMdlCreate(0, 0xE000D, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(1, 0xE000E, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreateEx(2, 0xE0010, -250.0f, 0.0f, -401.15002f);
    option_ModelRotSet(2, 0.0f, 10.0f, 0.0f);
    model = option_MenuMdlIdGet(2);
    data = DataRead(0xE0020);
    Hu3DAnimAttrSet(Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, (char *)parrot), 1, 0);
    DataClose(data);
    Hu3DModelRemakeStatic(model);
    Hu3DModelAnimStop(Hu3DData[model].hmf);
    option_MenuMdlCreateEx(3, 0xE0013, 250.0f, 0.0f, -401.15002f);
    option_ModelRotSet(3, 0.0f, -11.0f, 0.0f);
    model = option_MenuMdlIdGet(3);
    data = DataRead(0xE0021);
    Hu3DAnimAttrSet(Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, (char *)trumpet), 1, 0);
    DataClose(data);
    data = DataRead(0xE0022);
    Hu3DAnimAttrSet(Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, (char *)drum), 1, 0);
    DataClose(data);
    data = DataRead(0xE0023);
    Hu3DAnimAttrSet(Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, (char *)cymbal), 1, 0);
    DataClose(data);
    Hu3DModelRemakeStatic(model);
    Hu3DModelAnimStop(Hu3DData[model].hmf);
    option_MenuMdlCreateEx(4, 0xE0016, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreateEx(5, 0xE0019, 0.0f, 0.0f, 0.0f);
    option_MenuMotCreate(17, 0xE0017, 0);
    option_MenuMotCreate(18, 0xE0018, 0);
    option_MenuMotCreate(19, 0xE001A, 0);
    option_MenuMotCreate(20, 0xE001B, 0);
    if (!(saveCommonBuf & 1)) {
        option_MenuMotSet(4, 18, 0);
        option_MenuMotFlagReset(4, 7);
        option_MenuMotFlagSet(4, 2);
        option_MenuMotTimeSet(5, 1);
        option_MenuMotFlagReset(5, 7);
        option_MenuMotFlagSet(5, 4);
    } else {
        option_MenuMotSet(5, 20, 0);
        option_MenuMotFlagReset(5, 7);
        option_MenuMotFlagSet(5, 2);
        option_MenuMotTimeSet(4, 1);
        option_MenuMotFlagReset(4, 7);
        option_MenuMotFlagSet(4, 4);
    }
    option_MenuMdlCreateEx(6, 0xE001C, 90.0f, 108.2f, -300.0f);
    option_MenuMdlCreateEx(7, 0xE001C, -90.0f, 108.2f, -300.0f);
    option_MenuMdlCreate(8, 0xA00B0, 0.0f, 20.0f, -401.15002f);
    option_MotionFlagSet(8, 2);
    CharAnimCreate(option_MenuMdlIdGet(8), 0, 13, 0xA00B7);
    option_MenuMdlCreate(9, 0xE001E, 0.0f, 0.0f, 0.0f);
    option_MotionFlagSet(9, 2);
    option_MenuMdlCreate(21, 0xE001F, 0.0f, 22.25f, -310.7f);
    option_MotionFlagSet(21, 1);
    option_MenuMotCreate(10, 0xA00B1, 0);
    option_MotionSet(8, 10, 2);
    option_MenuMotCreate(11, 0xA00B2, 2);
    option_MenuMotCreate(12, 0xE000F, 0);
    option_MenuMotCreate(13, 0xE0011, 0);
    option_MenuMotCreate(14, 0xE0014, 0);
    option_MenuMotCreate(15, 0xE0012, 0);
    option_MenuMotCreate(16, 0xE0015, 0);
    option_SprCreate(1, 0x30);
    option_SprPriSet(1, 5);
    option_SprPosSet(1, 160, 113);
    option_SprDispOff(1);
    option_SprCreate(2, 0xE0024);
    option_SprPriSet(2, 10008);
    option_SprPosSet(2, 160, 113);
    option_SprDispOff(2);
    option_CameraMotionStart((s16)option_MenuMdlIdGet(0), 41.539f);
    option_CameraManualStart(41.539f);
    pos = option_soundRoomCameraPos;
    at = option_soundRoomCameraAt;
    option_CameraPosGet(&cameraPos, &cameraAt, &up);
    option_CameraPosSet(&pos, &at, &up);
    option_CursorSprCreate();
}

void option_SoundRoomClose(void) {
    option_CursorSprKill();
    option_CameraProcKill();
    option_ModelKill(0);
    option_ModelKill(1);
    option_ModelKill(2);
    option_ModelKill(3);
    option_ModelKill(4);
    option_ModelKill(5);
    option_ModelKill(6);
    option_ModelKill(7);
    option_ModelKill(8);
    option_ModelKill(9);
    option_ModelKill(10);
    option_ModelKill(11);
    option_ModelKill(12);
    option_ModelKill(13);
    option_ModelKill(14);
    option_ModelKill(15);
    option_ModelKill(16);
    option_ModelKillAll();
    option_SprKillAll();
    option_WinKillAll();
}

void option_RecordRoomInit(void) {
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;

    option_MenuMdlCreate(0, 0xE0025, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(1, 0xE0026, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(2, 0xE0027, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(3, 0xE0028, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(4, 0xE0029, 0.0f, 0.0f, 0.0f);
    option_MenuMdlCreate(5, 0xE002A, 0.0f, 0.0f, 0.0f);
    option_MenuCamMdlCreate(6, 0xE002B, 0.0f, 0.0f, 0.0f);
    option_ModelDispOff(6);
    option_MenuCamMdlCreate(7, 0xE002C, 0.0f, 0.0f, 0.0f);
    option_ModelDispOff(7);
    option_MenuMdlCreate(8, 0xA008E, -74.973503f, 56.406998f, -735.0f);
    option_MotionFlagSet(8, 2);
    CharAnimCreate(option_MenuMdlIdGet(8), 0, 9, 0xA00A3);
    option_MenuMdlCreate(9, 0xA00A2, 64.973503f, 60.8265f, -720.0f);
    option_MotionFlagSet(9, 2);
    model = option_MenuMdlIdGet(9);
    CharAnimCreate(model, 0, 8, 0xA00A3);
    CharAnimFrameSet(model, 0, 8, 1, 0);
    option_MenuMotCreate(10, 0xA009E, 1);
    option_MotionSet(8, 10, 2);
    option_MenuMotCreate(11, 0xA009F, 1);
    option_MotionSet(9, 11, 2);
    option_MenuMotCreate(12, 0xA008F, 1);
    option_CameraMotionStart((s16)option_MenuMdlIdGet(6), 55.0f);
    option_CameraPerspectiveSet(50.0f, 12.0f, 4800.0f);
    option_CameraManualStart(50.0f);
    pos = option_recordRoomCameraPos;
    at = option_recordRoomCameraAt;
    option_CameraPosGet(&cameraPos, &cameraAt, &up);
    option_CameraPosSet(&pos, &at, &up);
    option_CursorSprCreate();
}

void option_RecordRoomClose(void) {
    option_CursorSprKill();
    option_CameraProcKill();
    option_ModelKill(0);
    option_ModelKill(1);
    option_ModelKill(2);
    option_ModelKill(3);
    option_ModelKill(4);
    option_ModelKill(5);
    option_ModelKill(6);
    option_ModelKill(7);
    option_ModelKill(8);
    option_ModelKill(9);
    option_ModelKill(10);
    option_ModelKill(11);
    option_ModelKill(12);
    option_ModelKillAll();
    option_SprKillAll();
    option_WinKillAll();
}

void option_MenuMdlCreate(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    option_ModelCreate(arg0, arg1, 0x2A9);
    option_ModelPosSet(arg0, x, y, z);
    option_ModelScaleSet(arg0, 1.0f, 1.0f, 1.0f);
    option_MotionTimeSet(arg0, 0);
    option_MotionFlagSet(arg0, 1);
}

void option_MenuMdlCreateEx(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    option_ModelCreate(arg0, arg1, 0x6A9);
    option_ModelPosSet(arg0, x, y, z);
    option_ModelScaleSet(arg0, 1.0f, 1.0f, 1.0f);
    option_MotionTimeSet(arg0, 0);
    option_MotionFlagSet(arg0, 1);
}

void option_MenuMotCreate(s32 arg0, s32 resourceId, s32 arg2) {
    option_MotionCreate(arg0, resourceId, arg2);
}

void option_MenuCamMdlCreate(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    option_ModelCreate(arg0, arg1, 0x2002A9);
    option_ModelPosSet(arg0, x, y, z);
    option_ModelScaleSet(arg0, 1.0f, 1.0f, 1.0f);
    option_MotionTimeSet(arg0, 0);
    option_MotionFlagSet(arg0, 1);
}

void option_CursorSprCreate(void) {
    option_SprCreate(0, 0x88);
    option_SprPriSet(0, 5);
    option_SprPosSet(0, 0xA0, 0x71);
    option_SprDispOff(0);
}

void option_CursorSprKill(void) {
    option_SprKill(0);
}

s32 option_StickBtnGet(s32 pad) {
    s32 x, y;
    s32 absX, absY;

    x = HuPadStkX[pad];
    y = HuPadStkY[pad];

    if (option_stickBtn != 0) {
        if ((x == 0) & (y == 0)) {
            option_stickBtn = 0;
        }
        return 0;
    }
    if ((x != 0) | (y != 0)) {
        absX = __builtin_abs(x);
        absY = __builtin_abs(y);
        if (absY < absX) {
            if (absY * 2 < absX) {
                option_stickBtn = x < 0 ? L_JPAD : R_JPAD;
            } else if (y > 0) {
                option_stickBtn = x < 0 ? (U_JPAD | L_JPAD) : (U_JPAD | R_JPAD);
            } else {
                option_stickBtn = x < 0 ? (D_JPAD | L_JPAD) : (D_JPAD | R_JPAD);
            }
        } else if (absX * 2 < absY) {
            option_stickBtn = y < 0 ? D_JPAD : U_JPAD;
        } else if (y > 0) {
            option_stickBtn = x < 0 ? (U_JPAD | L_JPAD) : (U_JPAD | R_JPAD);
        } else {
            option_stickBtn = x < 0 ? (D_JPAD | L_JPAD) : (D_JPAD | R_JPAD);
        }
    }
    return option_stickBtn;
}

s32 option_PadBtnRepGet(s32 arg0) {
    return (u16)ContBtnRep[arg0];
}

s32 option_MenuMdlIdGet(s32 arg0) {
    return option_ModelIdGet(arg0);
}

void option_MenuMdlDispOn(s32 arg0) {
    option_ModelDispOn(arg0);
}

void option_MenuMdlDispOff(s32 arg0) {
    option_ModelDispOff(arg0);
}

void option_MenuMdlPosGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    option_ModelPosGet(arg0, arg1, arg2, arg3);
}

void option_MenuMdlRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    option_ModelRotSet(arg0, arg1, arg2, arg3);
}

void option_MenuMotFlagSet(s32 arg0, s32 arg1) {
    option_MotionFlagSet(arg0, arg1);
}

void option_MenuMotFlagReset(s32 arg0, s32 arg1) {
    option_MotionFlagReset(arg0, arg1);
}

void option_MenuMotTimeSet(s32 arg0, u32 arg1) {
    option_MotionTimeSet(arg0, arg1);
}

void option_MenuMotEndWait(s32 arg0) {
    option_MotionEndWait(arg0);
}

void option_MenuMotSet(s32 arg0, s32 arg1, u16 arg2) {
    option_MotionSet(arg0, arg1, arg2);
}

void option_MenuMotShiftSet(s32 arg0, s32 arg1, s16 arg2, s16 arg3, u16 arg4) {
    option_MotionShiftSet(arg0, arg1, arg2, arg3, arg4);
}

void option_MenuSprPosGet(s32 arg0, s32 *arg1, s32 *arg2) {
    option_SprPosGet(arg0, arg1, arg2);
}

void option_MenuSprDispOn(s32 arg0) {
    option_SprBGDispOn(arg0);
}

void option_MenuSprDispOff(s32 arg0) {
    option_SprBGDispOff(arg0);
}

void option_MenuWinCreate(s32 arg0, u32 arg1) {
    option_WinCreate(arg0, arg1, 0xA0, 0xC2, 0, 0, 4);
}

void option_MenuWinKill(s32 arg0) {
    option_WinKill(arg0);
}

void option_MenuWinMesSet(s32 arg0, u32 arg1) {
    option_WinMesSet(arg0, arg1);
}

void option_MenuWinDispOn(s32 arg0) {
    option_WinDispOn(arg0);
}

void option_MenuWinDispOff(s32 arg0) {
    option_WinDispOff(arg0);
}

s32 option_MenuWinChoiceGet(s32 arg0) {
    option_WinMesWait(arg0);
    return option_WinChoiceGet(arg0, 0, 0);
}

void option_MenuWinMesWait(s32 arg0) {
    option_WinMesWait(arg0);
}

const Vec option_soundRoomCameraPos = { 0.0f, 264.9f, 364.27f };

const Vec option_soundRoomCameraAt = { 0.0f, 184.59999f, 61.300003f };

const Vec option_recordRoomCameraPos = { 0.0f, 225.0f, 0.0f };

const Vec option_recordRoomCameraAt = { 0.0f, 225.0f, -220.0f };
