#include "common.h"
#include "game/vibrator.h"
#include "game/gamework_data.h"
#include "game/mallocblock.h"
#include "game/saveload.h"

#define UNK_VALUE 0x91

typedef struct UnkFileSelect2 {
    s16 unk_00;
    u32 unk_04; // can be messageID or message pointer
    s32 unk_08;
} UnkFileSelect2;

typedef struct UnkFileSelect {
    s32 empty;
    u8 unk_04;
    u8 name[0x20];
    u8 unk_25[7];
    u8 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s16 unk_4C[4];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s16 unk_68[4];
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
} UnkFileSelect; // sizeof 0x84

typedef struct FileSelectData {
    UnkFileSelect files[3];
    s32 selected;
} FileSelectData;

typedef struct UnkFileName {
    u8 unk_00[0xB];
} UnkFileName; // sizeof 0xB

typedef struct UnkFileSelect3 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s32 unk_28;
} UnkFileSelect3;

typedef struct UnkFileSelect4 {
    s16 unk_00;
    u16 unk_02;
    s32 unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    u8 unk_18;
    u8 unk_19[3];
} UnkFileSelect4; // sizeof 0x1C

typedef struct UnkFileSelect5 {
    omObjData *unk_00;
    Vec unk_04;
    Vec unk_10;
    char unk_1C[0x34];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} UnkFileSelect5; // sizeof 0x5C

typedef struct UnkFileSelect6 {
    omObjData *unk_00;
    s32 unk_04;
    s32 unk_08;
    Vec unk_0C;
    Vec unk_18;
} UnkFileSelect6; // sizeof 0x24

typedef struct FileSelectInputState {
    s32 mode;
    s32 keyboard;
    s32 option;
    s32 column;
    s32 row;
    s32 frame;
    u16 name[0x10];
    u8 encodedName[0x20];
    s32 length;
} FileSelectInputState;

typedef struct FileSelectCameraTransition {
    f32 distance;
    s32 frame;
    s32 duration;
} FileSelectCameraTransition;

typedef struct FileSelectCameraState {
    Vec center;
    Vec rotation;
    FileSelectCameraTransition transition;
} FileSelectCameraState;

void filesel_WinCreate(s32, u32, s16, s16, s16, s16, s16);
void filesel_TitleCreate(s32);
void filesel_FileNameSprCreate(s32, s32);
void filesel_FileNameDispOff(s32);
s32 filesel_WinType0Create(u32, s16, s16, s16, s16, s16);
s32 filesel_WinType1Create(u32, s16, s16, s16, s16, s16);
s32 filesel_WinType2Create(u32, s16, s16, s16, s16, s16);
s32 filesel_WinType3Create(u32, s16, s16, s16);
s32 filesel_WinType4Create(u32, s16, s16, s16);
s32 filesel_WinType5Create(u32, s16, s16, s16);
void filesel_StoryStageBoardGet(s32, u8 *, u8 *);
void filesel_NameOptionBlink(s32);
void filesel_NameInputSet(u8 *);
void filesel_NameInputGet(u8 *);
s32 filesel_NameInputExec(s32);
s32 filesel_FileNameGet(s32, u8 *);
s32 filesel_AlphaInput(u32);
s32 filesel_StickRepGet(s32);
void filesel_KeyCursorDispOn(void);
void filesel_KeyCursorDispOff(void);
s32 filesel_NameLenGet(UnkFileName *);
void filesel_StoryRead(void);
void filesel_FileStatRead(s32);
void filesel_FileNameRead(s32);
void filesel_CameraEndObjMain(omObjData *);
void filesel_MainProc(void);
void filesel_StickInit(void);
void filesel_FileReadAll(void);
s32 filesel_KeyCursorPosGet(s32, s32, s32, s16 *, s16 *);
void filesel_StoryStatDispOff(void);
void filesel_BoardStatDispOff(void);
void filesel_CameraRotPosCalc(Vec *, Vec *, f32, Vec *, Vec *, Vec *);
void filesel_CameraInit(s32);
void filesel_CameraProc(void);
void filesel_TitleKill(void);
void filesel_SprInit(void);
void filesel_ModelInit(void);
void filesel_WinInit(void);
void filesel_WinKill(s32);
void filesel_SprPosSet(s32, s32, s32);
void filesel_MotionSet(s32, s32, s16);
void filesel_WinMesSet(s32, u32);
s32 filesel_FileUsedNumGet(void);
void filesel_CursorPosSet(s32, u32);
void filesel_CursorPosGet(s32, u32, s32 *, s32 *);
void filesel_CursorOfsSet(s32, u32);
void filesel_CursorMove(s32, u32);
void filesel_FileInObjMain(omObjData *object);
void filesel_FileOutObjMain(omObjData *object);
void filesel_FileRaiseObjMain(omObjData *object);
void filesel_FileLowerObjMain(omObjData *object);
void filesel_FileJumpObjMain(omObjData *object);
void filesel_FileAnimStop(u32);
void filesel_FileBreathStart(u32);
u32 filesel_FileMenuChoice(s32);
s32 filesel_RenameExec(s32);
void filesel_CopySelect(void);
void filesel_FileCopyStart(s32, s32, s32);
void filesel_EraseSelect(void);
void filesel_FileMdlWaveKill(s32);
void filesel_FileWobbleStart(s32);
void filesel_HelpWinOut(void);
void filesel_CopyEraseBtnOut(void);
void filesel_CopyEraseBtnIn(void);
void filesel_HelpWinIn(void);
omObjData *filesel_FileRaiseCreate(s32, s32);
omObjData *filesel_FileInCreate(s32, s32);
void filesel_FileOutCreate(s32, s32);
void filesel_FileLowerCreate(s32, s32);
void filesel_FileNameDispOn(s32);
void filesel_FileNameSave(s32);
void filesel_FileBreathObjMain(omObjData *);
void filesel_FileWobbleObjMain(omObjData *);
void filesel_FileAnimMoveObjMain(omObjData *);
void filesel_FileCopyKill(s32);
void filesel_FileCopyObjMain(omObjData *);
void filesel_RumbleObjMain(omObjData *object);
s32 filesel_StickBtnGet(s32);
u32 filesel_WinMesConv(u32);
s32 filesel_NameEntryExec(s32);
s32 filesel_NewNameEntryExec(s32 arg0);
s32 filesel_FileNameSet(s32, u8 *);
void filesel_CopyEraseBtnCreate(void);
void filesel_CopyEraseBtnKill(void);
s32 filesel_FileDecide(void);
s32 filesel_ModeChoice(s32 fileIndex);
void filesel_StoryStatCreate(s32 fileIndex);
void filesel_BoardStatCreate(s32 fileIndex);
void filesel_StoryStatKill(void);
void filesel_StoryStatDispOn(s32 fileIndex);
void filesel_BoardStatKill(void);
void filesel_BoardStatDispOn(s32 fileIndex);
void filesel_CameraProcKill(void);
void filesel_CameraProcCreate(void);
void filesel_MenuInit(void);
void filesel_MenuClose(void);
omObjData *filesel_FileJumpCreate(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4);
void filesel_FileAnimInit(void);
omObjData *filesel_CameraEndCreate(s32 duration);
void filesel_RumbleStart(void);

extern SaveCommonBuf saveCommonBuf;
extern f32 Hu3DVtxWaveAngle;
extern u8 storySceneNo;

extern const u8 filesel_emptyStr[];
extern const u8 filesel_storySceneTbl[];
extern char *filesel_hiraganaTbl[];
extern char *filesel_katakanaTbl[];
extern char *filesel_alphaTbl[];

s32 filesel_fileNumMdlTbl[] = { 0x001F002D, 0x001F002E, 0x001F002F };

s32 filesel_cursorPosTbl[][2] = {
    { 0x70, 0x68 },
    { 0xC0, 0x68 },
    { 0x110, 0x68 },
    { 0xD2, 0x24 },
    { 0x102, 0x24 },
    { 0x50, 0x80 },
    { 0xA0, 0x80 },
    { 0xF0, 0x80 },
};

Vec filesel_cameraPos BSS;
Vec filesel_cameraTarget BSS;
Vec filesel_cameraUp BSS;
u8 filesel_cameraPad[0xC] BSS; /* Unreferenced. */
UnkFileSelect4 filesel_sprTbl[0x40] BSS;
s16 filesel_animTbl[0x40][1] BSS;
UnkFileSelect3 filesel_modelTbl[0x40] BSS;
s16 filesel_bgAnim BSS;
u16 filesel_bgSpr BSS;
u8 filesel_bgSprPad[4] BSS; /* Unreferenced. */
UnkFileSelect2 filesel_winTbl[0x20] BSS;
FileSelectData filesel_fileWork BSS;
Process *filesel_mainProc BSS;
omObjData *filesel_debugObj BSS;
s32 filesel_nameChangeF BSS;
u8 filesel_nameChangePad[4] BSS; /* Unreferenced. */
FileSelectInputState filesel_nameInput BSS;
Vec filesel_cameraFixPos BSS;
Vec filesel_cameraFixTarget BSS;
Vec filesel_cameraFixUp BSS;
f32 filesel_cameraNear BSS;
f32 filesel_cameraFar BSS;
s32 filesel_cameraMode BSS;
Process *filesel_cameraProc BSS;
UnkFileSelect6 filesel_fileMoveTbl[4] BSS;
UnkFileSelect5 filesel_fileAnimTbl[3] BSS;
u8 filesel_fileAnimPad[4] BSS; /* Unreferenced. */
FileSelectCameraState filesel_cameraEnd BSS;
s32 filesel_stickRepCnt BSS;
s32 filesel_rumbleCnt BSS;

void filesel_UtilInit(void) {
    filesel_SprInit();
    filesel_ModelInit();
    filesel_WinInit();
}

void filesel_SprInit(void) {
    UnkFileSelect4 *p;
    f32 zero;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filesel_sprTbl); i++) {
        filesel_animTbl[i][0] = -1;
        filesel_sprTbl[i].unk_00 = -1;
        // only these two of the seven field stores go through the pointer, the rest stay symbolic
        p = &filesel_sprTbl[i];
        p->unk_08 = 0;
        filesel_sprTbl[i].unk_04 = 0;
        zero = 0.0f;
        p->unk_10 = zero;
        filesel_sprTbl[i].unk_0C = zero;
        filesel_sprTbl[i].unk_14 = zero;
        filesel_sprTbl[i].unk_18 = 0xFF;
    }
}

s16 filesel_AnimIdGet(s32 arg0) {
    return filesel_animTbl[arg0][0];
}

s16 filesel_EspIdGet(s32 arg0) {
    return filesel_sprTbl[arg0].unk_00;
}

void filesel_AnimCreate(s32 arg0, s32 arg1) {
    filesel_animTbl[arg0][0] = HuSprAnimDataRead(arg1);
}

void filesel_AnimKill(s32 arg0) {
    if (filesel_animTbl[arg0][0] != -1) {
        HuSprAnimKill(filesel_animTbl[arg0][0]);
    }
    filesel_animTbl[arg0][0] = -1;
}

void filesel_EspCreate(s32 arg0, s16 arg1) {
    filesel_sprTbl[arg0].unk_00 = espEntry(filesel_animTbl[arg1][0], 0, 0);
    filesel_SprPosSet(arg0, 0xA0, 0x78);
}

void filesel_EspKill(s32 arg0) {
    if (filesel_sprTbl[arg0].unk_00 != -1) {
        espKill(filesel_sprTbl[arg0].unk_00);
    }
    filesel_sprTbl[arg0].unk_00 = -1;
}

void filesel_SprCreate(s32 arg0, s32 arg1) {
    filesel_AnimCreate(arg0, arg1);
    filesel_EspCreate(arg0, arg0);
}

void filesel_SprBGCreate(s32 arg0, s32 arg1) {
    filesel_SprCreate(arg0, arg1);
    espAttrSet(filesel_sprTbl[arg0].unk_00, HUSPR_ATTR_BG);
}

void filesel_SprKill(s32 arg0) {
    filesel_EspKill(arg0);
    filesel_AnimKill(arg0);
}

void filesel_SprKillAll(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        filesel_SprKill(i);
    }
}

void filesel_SprDispOn(s32 arg0) {
    espDispOn(filesel_sprTbl[arg0].unk_00);
}

void filesel_SprDispOff(s32 arg0) {
    espDispOff(filesel_sprTbl[arg0].unk_00);
}

void filesel_SprBGDispOn(s32 arg0) {
    filesel_SprDispOn(arg0);
}

void filesel_SprBGDispOff(s32 arg0) {
    filesel_SprDispOff(arg0);
}

void filesel_SprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    filesel_sprTbl[arg0].unk_04 = arg1;
    filesel_sprTbl[arg0].unk_08 = arg2;
    espPosSet(filesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void filesel_SprPosGet(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = filesel_sprTbl[arg0].unk_04;
    *arg2 = filesel_sprTbl[arg0].unk_08;
}

void filesel_SprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    filesel_sprTbl[arg0].unk_0C = arg1;
    filesel_sprTbl[arg0].unk_10 = arg2;
    espScaleSet(filesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void filesel_SprAlphaSet(s32 arg0, u16 arg1) {
    espTPLvlSet(filesel_sprTbl[arg0].unk_00, arg1);
}

void filesel_SprAttrSet(s32 arg0, u16 arg1) {
    espAttrSet(filesel_sprTbl[arg0].unk_00, arg1);
}

void filesel_SprAttrReset(s32 arg0, u16 arg1) {
    espAttrReset(filesel_sprTbl[arg0].unk_00, arg1);
}

void filesel_SprPriSet(s32 arg0, u16 arg1) {
    espPriSet(filesel_sprTbl[arg0].unk_00, arg1);
}

void filesel_SprBankSet(s32 arg0, u16 arg1, u16 arg2) {
    espAnimModeSet(filesel_sprTbl[arg0].unk_00, 1);
    espBankSet(filesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void filesel_ModelInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filesel_modelTbl); i++) {
        filesel_modelTbl[i].unk_00 = -1;
        filesel_modelTbl[i].unk_02 = -1;
    }
}

void filesel_ModelCreate(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = Hu3DModelRead(arg1, arg2);

    filesel_modelTbl[arg0].unk_00 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void filesel_MotionCreate(s32 arg0, s32 arg1, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(arg1);
    filesel_modelTbl[arg0].unk_02 = Hu3DMotionCreate(data, (s16)arg2);
    DataClose(data);
}

void filesel_ModelKill(s32 arg0) {
    if (filesel_modelTbl[arg0].unk_00 != -1) {
        Hu3DModelKill(filesel_modelTbl[arg0].unk_00);
        filesel_modelTbl[arg0].unk_00 = -1;
    }
    if (filesel_modelTbl[arg0].unk_02 != -1) {
        Hu3DMotionKill(filesel_modelTbl[arg0].unk_02);
        filesel_modelTbl[arg0].unk_02 = -1;
    }
}

void filesel_ModelKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filesel_modelTbl); i++) {
        filesel_ModelKill(i);
    }
}

s32 filesel_ModelIdGet(s32 arg0) {
    return filesel_modelTbl[arg0].unk_00;
}

s16 filesel_MotionIdGet(s32 arg0) {
    return filesel_modelTbl[arg0].unk_02;
}

void filesel_ModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    filesel_modelTbl[arg0].unk_1C = arg1;
    filesel_modelTbl[arg0].unk_20 = arg2;
    filesel_modelTbl[arg0].unk_24 = arg3;
    Hu3DModelRotSet(filesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void filesel_ModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    filesel_modelTbl[arg0].unk_04 = arg1;
    filesel_modelTbl[arg0].unk_08 = arg2;
    filesel_modelTbl[arg0].unk_0C = arg3;
    Hu3DModelPosSet(filesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void filesel_ModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    filesel_modelTbl[arg0].unk_10 = arg1;
    filesel_modelTbl[arg0].unk_14 = arg2;
    filesel_modelTbl[arg0].unk_18 = arg3;
    Hu3DModelScaleSet(filesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void filesel_ModelPosGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = filesel_modelTbl[arg0].unk_04;
    *arg2 = filesel_modelTbl[arg0].unk_08;
    *arg3 = filesel_modelTbl[arg0].unk_0C;
}

void filesel_ModelRotGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = filesel_modelTbl[arg0].unk_1C;
    *arg2 = filesel_modelTbl[arg0].unk_20;
    *arg3 = filesel_modelTbl[arg0].unk_24;
}

void filesel_ModelScaleGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = filesel_modelTbl[arg0].unk_10;
    *arg2 = filesel_modelTbl[arg0].unk_14;
    *arg3 = filesel_modelTbl[arg0].unk_18;
}

void filesel_ModelDispOff(s32 arg0) {
    Hu3DModelAttrSet(filesel_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void filesel_ModelDispOn(s32 arg0) {
    Hu3DModelAttrSet(filesel_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void filesel_MotionFlagSet(s32 arg0, s32 arg1) {
    Hu3DMotionAttrSet(filesel_modelTbl[arg0].unk_00, -1, arg1);
}

void filesel_MotionShiftSet(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(filesel_modelTbl[arg0].unk_00, filesel_modelTbl[arg1].unk_02, arg2, arg3, arg4);
}

void filesel_MotionFlagReset(s32 arg0, s16 arg1) {
    Hu3DMotionAttrSet(filesel_modelTbl[arg0].unk_00, arg1, 0);
}

void filesel_MotionSpeedSet(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())Hu3DMotionSpeedSet;

    setModelScale(filesel_modelTbl[arg0].unk_00);
}

void filesel_MotionTimeSet(s32 arg0, u32 arg1) {
    Hu3DMotionTimeSet(filesel_modelTbl[arg0].unk_00, arg1);
}

void filesel_MotionEndWait(s32 arg0) {
    while (Hu3DData[filesel_modelTbl[arg0].unk_00].motTime !=
           Hu3DMotion[Hu3DData[filesel_modelTbl[arg0].unk_00].motId].unk02) {
        HuPrcVSleep();
    }
}

s32 filesel_MotionEndCheck(s32 arg0) {
    s16 modelId = filesel_modelTbl[arg0].unk_00;

    return Hu3DData[modelId].motTime == Hu3DMotion[Hu3DData[modelId].motId].unk02;
}

void filesel_MotionSet(s32 arg0, s32 arg1, s16 arg2) {
    s16 modelId = filesel_ModelIdGet(arg0);
    s16 parentModelId = filesel_MotionIdGet(arg1);

    Hu3DMotionSet(modelId, parentModelId);
    Hu3DMotionAttrSet(modelId, -1, arg2);
}

void filesel_BGSprCreate(s32 arg0) {
    filesel_bgAnim = HuSprAnimDataRead(arg0);
    filesel_bgSpr = espEntry(filesel_bgAnim, 0, 0);
    espAttrSet(filesel_bgSpr, HUSPR_ATTR_BG);
    espPosSet(filesel_bgSpr, 0xA0, 0x78);
}

void filesel_BGSprKill(void) {
    espKill(filesel_bgSpr);
    HuSprAnimKill(filesel_bgAnim);
}

u32 filesel_WinMesConv(u32 arg0) {
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

void filesel_WinCreate(s32 index, u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    u32 copiedMessage;
    s16 window;

    switch (style) {
        case 1:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType1Create(copiedMessage, x, y, width, height, style);
            break;
        case 2:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType2Create(copiedMessage, x, y, width, height, style);
            break;
        case 3:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType3Create(copiedMessage, x, y, style);
            break;
        case 4:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType4Create(copiedMessage, x, y, style);
            break;
        case 5:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType5Create(copiedMessage, x, y, style);
            break;
        case 0:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType0Create(copiedMessage, x, y, width, height, style);
            break;
        default:
            copiedMessage = filesel_WinMesConv(message);
            window = filesel_WinType0Create(copiedMessage, x, y, width, height, style);
            break;
    }
    if (copiedMessage > 0x80000000U) {
        filesel_winTbl[index].unk_04 = copiedMessage;
    }
    filesel_winTbl[index].unk_00 = window;
}

s32 filesel_WinType0Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesDefColSet(window, 192, 192, 192);
    HuWinBGColSet(window, 0, 64, 64);
    HuWinMesColSet(window, 7);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 filesel_WinType1Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 4);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinMesDefColSet(window, 192, 192, 192);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 1);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 filesel_WinType2Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 7, 255, 255, 255);
    HuWinMesPalSet(window, 0, 0, 0, 0);
    HuWinMesPalSet(window, 3, 0, 0, 0);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinMesDefColSet(window, 192, 192, 0);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 6);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 filesel_WinType3Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinExOpen(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 filesel_WinType4Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 20);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinExOpen(window, 0);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 filesel_WinType5Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinExOpen(window, 0);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

void filesel_WinInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filesel_winTbl); i++) {
        filesel_winTbl[i].unk_00 = -1;
        filesel_winTbl[i].unk_04 = 0;
    }
}

void filesel_WinKill(s32 arg0) {
    if (filesel_winTbl[arg0].unk_08 == 3) {
        HuWinExClose(filesel_winTbl[arg0].unk_00, 1);
        HuWinExCleanup(filesel_winTbl[arg0].unk_00);
    } else {
        HuWinDispOff(filesel_winTbl[arg0].unk_00);
        HuWinKill(filesel_winTbl[arg0].unk_00);
        filesel_winTbl[arg0].unk_00 = -1;
    }
    if (filesel_winTbl[arg0].unk_04 != 0) {
        HuMemDelayFree((void *)filesel_winTbl[arg0].unk_04);
        filesel_winTbl[arg0].unk_04 = 0;
    }
}

void filesel_WinKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(filesel_winTbl); i++) {
        if (filesel_winTbl[i].unk_00 != -1) {
            filesel_WinKill(i);
        }
    }
}

void filesel_WinScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    // The original call omits the position arguments.
    void (*setWindowPosition)() = (void (*)())HuWinScaleSet;

    setWindowPosition(filesel_winTbl[arg0].unk_00);
}

void filesel_WinPosSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinPosSet(filesel_winTbl[arg0].unk_00, arg1, arg2);
}

void filesel_WinDispOn(s32 arg0) {
    HuWinDispOn(filesel_winTbl[arg0].unk_00);
}

void filesel_WinDispOff(s32 arg0) {
    HuWinDispOff(filesel_winTbl[arg0].unk_00);
}

void filesel_WinMesSet(s32 arg0, u32 arg1) {
    u32 temp_v0;

    HuWinHomeClear(filesel_winTbl[arg0].unk_00);
    if (filesel_winTbl[arg0].unk_04 != 0) {
        HuMemDelayFree((void *)filesel_winTbl[arg0].unk_04);
        filesel_winTbl[arg0].unk_04 = 0;
    }

    temp_v0 = filesel_WinMesConv(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        filesel_winTbl[arg0].unk_04 = temp_v0;
    }
    HuWinMesSet(filesel_winTbl[arg0].unk_00, temp_v0, -1, -1);
}

void filesel_WinInsertMesSet(s32 arg0, s8 arg1, u32 arg2) {
    HuWinInsertMesSetNoLF(filesel_winTbl[arg0].unk_00, arg2, arg1);
}

s32 filesel_WinChoiceGet(s32 arg0, s16 arg1, s32 arg2) {
    // The original call omits the final argument.
    s32 (*setWindowStyle)() = (s32 (*)())HuWinChoiceGet;

    return setWindowStyle(filesel_winTbl[arg0].unk_00, arg1);
}

s16 filesel_WinIdGet(s32 arg0) {
    return filesel_winTbl[arg0].unk_00;
}

void filesel_WinMesWait(s32 arg0) {
    while (HuWinStatGet(filesel_winTbl[arg0].unk_00) != 0) {
        HuPrcVSleep();
    }
}

void filesel_PadBtnWait(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & HuPadBtnDown[0]));
}

void filesel_WinPriSet(s32 arg0, s16 arg1) {
    HuWinPriSet(filesel_winTbl[arg0].unk_00, arg1);
}

u16 filesel_CameraDebugExec(s32 value) {
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

void filesel_PlayerPadInit(void) {
    s16 i;
    s16 count;
    s16 pad;
    s16 player;

    for (i = 0; i < 4; i++) {
        GwPlayer[i].pad = 0xFF;
    }
    for (i = 0, count = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            GwPlayer[count].pad = i;
            count++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].pad == 0xFF) {
            for (pad = 0; pad < 4; pad++) {
                for (player = 0; player < 4; player++) {
                    if (GwPlayer[player].pad == pad) {
                        break;
                    }
                }
                if (player == 4) {
                    break;
                }
            }
            GwPlayer[i].pad = pad;
        }
    }
}

void filesel_DebugObjMain(omObjData *object) {
    if (HuPadBtnDown[0] & B_BUTTON) {
        Hu3DBGColorSet(0xFF, 0, 0);
    }
}

void filesel_MainInit(void) {
    filesel_UtilInit();
    filesel_StickInit();
    filesel_FileReadAll();
    filesel_mainProc = omAddPrcObj(filesel_MainProc, 0x5000, 0x2000, 0);
    filesel_debugObj = omAddObj(6, 0, 0, -1, filesel_DebugObjMain);
}

void filesel_MainProc(void) {
    Vec pos;
    Vec2f screenPos;
    f32 x;
    f32 y;
    f32 z;
    s32 fileIndex;
    s32 slot;
    s32 result;
    s32 story;
    f32 winOffsetX;

    Hu3DBGColorSet(0, 0x40, 0x40);
    filesel_CameraProcCreate();
    filesel_BGSprCreate(0x1F0000);
    HuPrcSleep(1);
    filesel_MenuInit();
    HuAudSeqPlay(3);
    WipeCreateIn(WIPE_FADE, 16);
    HuPrcSleep(16);
    while (1) {
        filesel_TitleKill();
        filesel_TitleCreate(0);
        filesel_CopyEraseBtnCreate();
        filesel_FileAnimInit();
        filesel_FileInCreate(0, 24);
        filesel_FileInCreate(1, 24);
        filesel_FileInCreate(2, 24);
        HuAudFXPlay(0x2F3);
        HuPrcSleep(24);
        filesel_WinMesSet(4, (u32)filesel_emptyStr);
        filesel_HelpWinIn();
        filesel_CopyEraseBtnIn();
        filesel_WinMesSet(4, 0x2A00);
        do {
            fileIndex = filesel_FileDecide();
            HuPrcVSleep();
        } while (fileIndex < 0);
        slot = fileIndex;
        filesel_CopyEraseBtnKill();
        filesel_TitleKill();
        filesel_TitleCreate(1);
        filesel_StoryStatCreate(fileIndex);
        filesel_BoardStatCreate(fileIndex);
        HuPrcSleep(3);
        filesel_ModelPosGet(fileIndex, &x, &y, &z);
        if (y < 120.0f) {
            x = z = 0.0f;
            y = 120.0f;
            filesel_FileNameDispOff(fileIndex);
            filesel_FileJumpCreate(fileIndex, x, y, z, 16);
            HuAudFXPlay(0x2F0);
            HuPrcSleep(16);
        } else {
            x = z = 0.0f;
            y = 120.0f;
            filesel_FileNameDispOff(slot);
            filesel_FileJumpCreate(slot, x, y, z, 32);
            HuAudFXPlay(0x2F0);
            HuPrcSleep(32);
        }
        filesel_ModelPosSet(slot, x, y, z);
        filesel_ModelPosSet(slot + 3, x, y, z);
        filesel_FileNameDispOn(slot);
        HuVecCopyXYZ(&pos, x, y, z);
        Hu3D3Dto2D(0, &pos, &screenPos);
        // keeping the offset in a local gives the 31.0f constant a long enough lifetime to be hoisted out of the loop
        winOffsetX = 31.0f;
        HuWinPosSet(filesel_WinIdGet(slot + 1), screenPos.x - winOffsetX, screenPos.y);
        filesel_SprPosSet(slot + 13, screenPos.x, screenPos.y + 9.0f);
        filesel_ModelDispOn(slot);
        filesel_ModelDispOn(slot + 3);
        filesel_FileNameDispOn(slot);
        filesel_WinMesSet(4, (u32)filesel_emptyStr);
        filesel_HelpWinIn();
        filesel_WinMesSet(4, 0x2A0C);
        filesel_StoryStatDispOn(slot);
        filesel_BoardStatDispOn(slot);
        while (1) {
            if (HuPadBtnDown[0] & A_BUTTON) {
                break;
            }
            if (HuPadBtnDown[0] & B_BUTTON) {
                break;
            }
            HuPrcVSleep();
        }
        HuWinHomeClear(filesel_winTbl[4].unk_00);
        HuAudFXPlay(0x138);
        result = filesel_ModeChoice(fileIndex);
        if (result != -1) {
            break;
        }
        filesel_StoryStatDispOff();
        filesel_BoardStatDispOff();
        filesel_FileNameDispOff(slot);
        filesel_FileJumpCreate(slot, -1000.0f, 1000.0f, 0.0f, 30);
        HuAudFXPlay(0x2F0);
        HuPrcSleep(30);
        filesel_ModelDispOff(0);
        filesel_ModelDispOff(3);
        filesel_ModelDispOff(1);
        filesel_ModelDispOff(4);
        filesel_ModelDispOff(2);
        filesel_ModelDispOff(5);
        filesel_FileNameDispOff(0);
        filesel_FileNameDispOff(1);
        filesel_FileNameDispOff(2);
        filesel_StoryStatKill();
        filesel_BoardStatKill();
        HuPrcVSleep();
    }
    saveCommonBuf.boxNo = fileIndex;
    ModeSelIntroShownSet(0);
    saveCommonBuf.boxNo = fileIndex;
    SLSaveCommon();
    HuAudFXPlay(0x155);
    filesel_CameraProcKill();
    filesel_FileNameDispOff(fileIndex);
    filesel_CameraEndCreate(40);
    filesel_SprDispOff(12);
    filesel_MotionTimeSet(fileIndex, 0);
    filesel_MotionFlagReset(fileIndex, 7);
    HuPrcSleep(20);
    WipeColorSet(255, 255, 255);
    filesel_RumbleStart();
    WipeCreateOut(WIPE_FADE, 20);
    HuAudSeqFadeOut(20);
    HuPrcSleep(20);
    filesel_MenuClose();
    filesel_BGSprKill();
    filesel_WinKillAll();
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 0:
            FileSelEnteredSet(1);
            omOvlCallEx(modesel, 1, OM_OVL_STAT_MGLIB | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            filesel_StoryRead();
            break;
        case 1:
            FileSelEnteredSet(0);
            filesel_StoryRead();
            if (_CheckFlag(0x28)) {
                omOvlCallEx(modesel, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
                omOvlHisChg(1, 0x7A, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
            } else {
                story = GwStory.unk0;
                if (filesel_storySceneTbl[story] != 0xFF) {
                    omOvlHisData *history = &omovlhis[++omovlhisidx];

                    history->overlayID = 0x7A;
                    history->event = 0;
                    history->stat = 0x82;
                    storySceneNo = filesel_storySceneTbl[story];
                    omOvlCallEx(storycall, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
                    omOvlHisChg(1, 0x77, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
                    break;
                }
                omOvlCallEx(modesel, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
                omOvlHisChg(1, 0x77, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
            }
            break;
        case 2: {
            omOvlHisData *history;

            filesel_StoryRead();
            FileSelEnteredSet(0);
            history = &omovlhis[++omovlhisidx];
            history->overlayID = 0x7A;
            history->event = 0;
            history->stat = 0x82;
            omOvlCallEx(msetup, 4, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
            omOvlHisChg(1, 0x77, 0, OM_OVL_STAT_MGLIB | OM_OVL_STAT_GFXBUF3);
            break;
        }
        default:
            while (1) {
                HuPrcVSleep();
            }
            break;
    }
    omDelPrcObj(filesel_mainProc);
    while (1) {
        HuPrcVSleep();
    }
}

void filesel_CopyEraseBtnCreate(void) {
    filesel_SprCreate(1, 0x1F000D);
    filesel_SprDispOff(1);
    filesel_SprCreate(2, 0x1F000E);
    filesel_SprBankSet(2, 0, 0);
    filesel_SprAttrSet(2, HUSPR_ATTR_AA);
    filesel_SprDispOff(2);
    filesel_SprCreate(3, 0x1F000F);
    filesel_SprBankSet(3, 0, 0);
    filesel_SprAttrSet(3, HUSPR_ATTR_AA);
    filesel_SprDispOff(3);
}

void filesel_CopyEraseBtnKill(void) {
    filesel_SprKill(1);
    filesel_SprKill(2);
    filesel_SprKill(3);
}

const u8 filesel_emptyStr[] = "";

const u8 filesel_storySceneTbl[] = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0xFF, 0xFF, 0xFF, 0xFF };

s32 filesel_FileMenuExec(void) {
    s32 i;
    s32 fileIndex;
    s32 selection;
    s32 noSelection;

    selection = filesel_fileWork.selected;
    if (selection >= 3) {
        selection = 2;
    }
    if (filesel_fileWork.files[filesel_fileWork.selected].unk_04 != UNK_VALUE) {
        for (i = 0; i < 3; i++) {
            if (filesel_fileWork.files[i].unk_04 == UNK_VALUE) {
                selection = i;
                break;
            }
        }
    }
    filesel_SprDispOn(18);
    filesel_CursorPosSet(18, selection);
    for (i = 0; i < 8; i++) {
        filesel_SprScaleSet(18, 1.0f, i * 0.125f);
        HuPrcVSleep();
    }
    filesel_SprScaleSet(18, 1.0f, 1.0f);
    filesel_FileBreathStart(selection);
    noSelection = -1;
    while (1) {
        selection = filesel_FileMenuChoice(selection);
        if (selection == noSelection) {
            HuPrcVSleep();
        } else {
            switch (selection) {
                case 0:
                case 1:
                case 2:
                    HuAudFXPlay(2);
                    filesel_SprDispOff(18);
                    return selection;
                case 3:
                    HuAudFXPlay(2);
                    filesel_CopySelect();
                    break;
                case 4:
                    HuAudFXPlay(2);
                    filesel_EraseSelect();
                    break;
                case 5:
                case 6:
                case 7:
                    HuAudFXPlay(2);
                    fileIndex = selection - 5;
                    filesel_SprBGDispOff(18);
                    i = 0;
                    filesel_HelpWinOut();
                    filesel_CopyEraseBtnOut();
                    filesel_SprBGDispOff(12);
                    filesel_FileNameDispOff(0);
                    filesel_FileNameDispOff(1);
                    filesel_FileNameDispOff(2);
                    for (; i < 3; i++) {
                        if (fileIndex != i) {
                            filesel_FileNameDispOff(i);
                            filesel_FileOutCreate(i, 16);
                        }
                    }
                    HuAudFXPlay(0x2F2);
                    filesel_FileRaiseCreate(fileIndex, 32);
                    HuAudFXPlay(0x2F0);
                    HuPrcSleep(16);
                    for (i = 0; i < 3; i++) {
                        if (fileIndex != i) {
                            filesel_ModelDispOff(i);
                            filesel_ModelDispOff(i + 3);
                        }
                    }
                    HuPrcSleep(16);
                    filesel_WinDispOn(0);
                    filesel_TitleKill();
                    filesel_TitleCreate(4);
                    if (filesel_RenameExec(fileIndex)) {
                        filesel_WinDispOn(4);
                        filesel_WinPosSet(4, 160.0f, 208.0f);
                        filesel_WinMesSet(4, 0x2A15);
                        HuPrcSleep(3);
                        SLCurBoxNoSet(fileIndex);
                        filesel_FileNameSave(fileIndex);
                        filesel_FileStatRead(fileIndex);
                        filesel_WinDispOff(4);
                        HuPrcSleep(3);
                    }
                    filesel_WinDispOff(0);
                    i = 0;
                    filesel_TitleKill();
                    filesel_FileLowerCreate(fileIndex, 32);
                    HuAudFXPlay(0x2F1);
                    HuPrcSleep(16);
                    for (; i < 3; i++) {
                        if (fileIndex != i) {
                            filesel_FileInCreate(i, 16);
                        }
                    }
                    for (i = 0; i < 3; i++) {
                        if (fileIndex != i) {
                            filesel_ModelDispOn(i);
                            filesel_ModelDispOn(i + 3);
                        }
                    }
                    HuPrcSleep(16);
                    for (i = 0; i < 3; i++) {
                        filesel_FileNameDispOn(i);
                    }
                    filesel_TitleCreate(0);
                    filesel_CopyEraseBtnIn();
                    filesel_HelpWinIn();
                    filesel_SprBGDispOn(18);
                    break;
            }
            filesel_CursorPosSet(18, selection);
            HuPrcVSleep();
        }
    }
}

s32 filesel_FileUsedNumGet(void) {
    s32 i;
    s32 total;

    for (i = 0, total = 0; i < ARRAY_COUNT(filesel_fileWork.files); i++) {
        if (filesel_fileWork.files[i].unk_04 == UNK_VALUE) {
            total++;
        }
    }

    return total;
}

void filesel_CopyEraseBtnUpdate(void) {
    s32 state = filesel_FileUsedNumGet();

    if (state == 1 || state == 2) {
        filesel_SprBankSet(2, 1, 0);
    } else {
        filesel_SprBankSet(2, 0, 0);
    }
    if (state != 0) {
        filesel_SprBankSet(3, 1, 0);
    } else {
        filesel_SprBankSet(3, 0, 0);
    }
}

void filesel_CopyEraseBtnIn(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i < 3; i++) {
    }
    filesel_SprDispOn(1);
    filesel_SprDispOn(2);
    filesel_SprDispOn(3);
    filesel_CopyEraseBtnUpdate();
    for (i = 0; i <= 10; i++) {
        progress = i * 0.1f;
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        HuVecCopyXYZ(&start, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&end, 224.0f, 40.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        filesel_SprPosSet(1, position.x, position.y);
        filesel_SprPosSet(2, position.x - 22.0f, position.y);
        filesel_SprPosSet(3, position.x + 26.0f, position.y);
        HuPrcVSleep();
    }
}

void filesel_CopyEraseBtnOut(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i <= 10; i++) {
        progress = 1.0f - i * 0.1f;
        if (progress < 0.0f) {
            progress = 0.0f;
        }
        HuVecCopyXYZ(&start, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&end, 224.0f, 40.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        filesel_SprPosSet(1, position.x, position.y);
        filesel_SprPosSet(2, position.x - 22.0f, position.y);
        filesel_SprPosSet(3, position.x + 26.0f, position.y);
        HuPrcVSleep();
    }
    filesel_SprDispOff(1);
    filesel_SprDispOff(2);
    filesel_SprDispOff(3);
}

void filesel_HelpWinIn(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    filesel_WinDispOn(4);
    for (i = 0; i <= 10; i++) {
        progress = i * 0.1f;
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        HuVecCopyXYZ(&start, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&end, 160.0f, 192.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        (void)position;
        filesel_WinPosSet(4, 160.0f, (96.0f - progress * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
}

void filesel_HelpWinOut(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i <= 10; i++) {
        progress = 1.0f - i * 0.1f;
        if (progress < 0.0f) {
            progress = 0.0f;
        }
        HuVecCopyXYZ(&start, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&end, 160.0f, 192.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        (void)position;
        filesel_WinPosSet(4, 160.0f, (96.0f - progress * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
    filesel_WinDispOff(4);
}

s32 filesel_FileDecide(void) {
    Vec pos;
    Vec2f screen;
    Vec position;
    s16 models[2];
    s32 selection;
    s32 fileIndex;
    s32 target;
    s32 alpha;
    s32 max;
    s32 x;
    s32 i;

    HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &pos, &screen);
    x = screen.x - 31.0f;
    HuWinPosSet(filesel_WinIdGet(1), x, 168);
    filesel_SprPosSet(13, x + 31, 177);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &pos, &screen);
    x = screen.x - 31.0f;
    HuWinPosSet(filesel_WinIdGet(2), x, 168);
    filesel_SprPosSet(14, x + 31, 177);
    HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &pos, &screen);
    x = screen.x - 31.0f;
    HuWinPosSet(filesel_WinIdGet(3), x, 168);
    filesel_SprPosSet(15, x + 31, 177);
    filesel_FileNameDispOn(0);
    filesel_FileNameDispOn(1);
    filesel_FileNameDispOn(2);
    filesel_WinScaleSet(1, 1.0f, 1.0f);
    filesel_WinScaleSet(2, 1.0f, 1.0f);
    filesel_WinScaleSet(3, 1.0f, 1.0f);
    filesel_WinDispOn(4);
    selection = filesel_FileMenuExec();
    HuPrcVSleep();
    fileIndex = selection;
    target = selection;
    if (filesel_fileWork.files[selection].unk_04 != UNK_VALUE ||
        (filesel_fileWork.files[selection].name[0] | filesel_fileWork.files[selection].name[1]) == 0) {
        i = 0;
        filesel_HelpWinOut();
        filesel_CopyEraseBtnOut();
        filesel_SprBGDispOff(12);
        filesel_FileNameDispOff(0);
        filesel_FileNameDispOff(1);
        filesel_FileNameDispOff(2);
        for (; i < 3; i++) {
            if (fileIndex != i) {
                filesel_FileNameDispOff(i);
                filesel_FileOutCreate(i, 16);
            }
        }
        HuAudFXPlay(0x2F2);
        filesel_FileRaiseCreate(fileIndex, 32);
        HuAudFXPlay(0x2F0);
        HuPrcSleep(16);
        for (i = 0; i < 3; i++) {
            if (fileIndex != i) {
                filesel_ModelDispOff(i);
                filesel_ModelDispOff(i + 3);
            }
        }
        HuPrcSleep(16);
        filesel_WinDispOn(0);
        filesel_TitleKill();
        filesel_TitleCreate(4);
        if (filesel_NewNameEntryExec(fileIndex)) {
            filesel_WinDispOff(0);
            i = 0;
            filesel_TitleKill();
            filesel_WinDispOn(4);
            filesel_WinPosSet(4, 160.0f, 208.0f);
            filesel_WinMesSet(4, 0x2A14);
            HuPrcSleep(3);
            SLCurBoxNoSet(fileIndex);
            SLSaveDataInit();
            filesel_FileNameSave(fileIndex);
            filesel_FileStatRead(fileIndex);
            filesel_WinDispOff(4);
            HuPrcSleep(3);
            filesel_ModelPosGet(fileIndex, &position.x, &position.y, &position.z);
            filesel_ModelCreate(6, 0x1F002B, 0x6A9);
            filesel_ModelCreate(7, 0x1F002C, 0x6A9);
            filesel_ModelPosSet(6, position.x, position.y, position.z);
            filesel_ModelScaleSet(6, 0.48f, 0.48f, 0.48f);
            filesel_ModelPosSet(7, position.x, position.y, position.z);
            filesel_ModelScaleSet(7, 0.48f, 0.48f, 0.48f);
            filesel_ModelDispOff(fileIndex);
            filesel_ModelDispOff(fileIndex + 3);
            filesel_ModelKill(fileIndex);
            filesel_ModelCreate(target, 0x1F002A, 0x6A9);
            filesel_ModelPosSet(fileIndex, position.x, position.y, position.z);
            filesel_ModelScaleSet(fileIndex, 0.48f, 0.48f, 0.48f);
            filesel_MotionTimeSet(fileIndex, 0);
            filesel_MotionFlagSet(fileIndex, 1);
            filesel_ModelDispOff(fileIndex);
            models[0] = filesel_ModelIdGet(6);
            models[1] = filesel_ModelIdGet(7);
            Hu3DModelTPLvlInit(models[0]);
            Hu3DModelTPLvlInit(models[1]);
            filesel_ModelDispOn(6);
            filesel_ModelDispOff(7);
            for (alpha = 255; i < 16; i++) {
                Hu3DModelTPLvlSet(models[0], alpha);
                alpha -= 16;
                HuPrcVSleep();
            }
            filesel_ModelDispOff(6);
            filesel_ModelDispOn(7);
            for (i = 0, alpha = 255, max = 255; i < 16; i++) {
                Hu3DModelTPLvlSet(models[1], max - alpha);
                alpha -= 16;
                HuPrcVSleep();
            }
            Hu3DModelTPLvlSet(models[1], 255);
            filesel_ModelDispOn(fileIndex);
            filesel_ModelDispOn(fileIndex + 3);
            filesel_ModelKill(6);
            filesel_ModelKill(7);
            filesel_SprKill(fileIndex + 13);
            filesel_FileNameSprCreate(fileIndex, 1);
            filesel_SprBGDispOff(fileIndex + 13);
            return selection;
        }
        filesel_WinDispOff(0);
        i = 0;
        filesel_TitleKill();
        filesel_FileLowerCreate(fileIndex, 32);
        HuAudFXPlay(0x2F1);
        HuPrcSleep(16);
        for (; i < 3; i++) {
            if (fileIndex != i) {
                filesel_FileInCreate(i, 16);
            }
        }
        for (i = 0; i < 3; i++) {
            if (fileIndex != i) {
                filesel_ModelDispOn(i);
                filesel_ModelDispOn(i + 3);
            }
        }
        HuPrcSleep(16);
        for (i = 0; i < 3; i++) {
            filesel_FileNameDispOn(i);
        }
        filesel_TitleCreate(0);
        filesel_WinMesSet(4, 0x2A00);
        filesel_CopyEraseBtnIn();
        filesel_HelpWinIn();
        return -1;
    }
    SLCurBoxNoSet(fileIndex);
    i = 0;
    SLLoadGameStat();
    filesel_FileStatRead(fileIndex);
    filesel_HelpWinOut();
    filesel_CopyEraseBtnOut();
    for (; i < 3; i++) {
        if (fileIndex != i) {
            filesel_FileNameDispOff(i);
            filesel_FileOutCreate(i, 16);
        }
    }
    HuAudFXPlay(0x2F2);
    HuPrcSleep(16);
    return selection;
}

#define CLAMP_BELOW(val, limit) ((val) < (limit) ? (val) : 0)

enum OptionsFileSelect {
    OPTION_FILE0 = 0,
    OPTION_FILE1 = 1,
    OPTION_FILE2 = 2,
    OPTION_FILES_END,
    OPTION_COPY = 3,
    OPTION_ERASE = 4,
    OPTION_FILES_NAME_BEGIN,
    OPTION_FILE0_NAME = 5,
    OPTION_FILE1_NAME = 6,
    OPTION_FILE2_NAME = 7,
    OPTION_MAX = 7,
};

// TODO: can the gotos be removed?
// main function for handling input when an option hasn't been select yet
u32 filesel_FileMenuChoice(s32 arg0) {
    s32 temp_v0;
    u32 temp_v1;
    s32 animTimerAdjusted;
    s32 animTimer;
    u16 pressedInput;
    s32 cursorIndex;
    u32 selectedOption;
    s32 unkValue;

    animTimer = 0;

    if (arg0 < 0) {
        arg0 = 0;
    }

    selectedOption = arg0;
    cursorIndex = selectedOption;
    unkValue = UNK_VALUE;

    while (1) {
        pressedInput = HuPadBtnRep[0];
        temp_v0 = filesel_StickBtnGet(0);
        if (temp_v0 != -1) {
            pressedInput |= temp_v0;
        }
        if (HuPadBtnDown[0] & A_BUTTON) {
            switch (selectedOption) {
                case OPTION_FILE0:
                    RepeatVibrator(0, 5, 0, 5);
                    filesel_FileAnimStop(selectedOption);
                    break;
                case OPTION_FILE1:
                    RepeatVibrator(0, 5, 0, 5);
                    filesel_FileAnimStop(selectedOption);
                    break;
                case OPTION_FILE2:
                    RepeatVibrator(0, 5, 0, 5);
                    filesel_FileAnimStop(selectedOption);
                    break;
                case OPTION_COPY:
                case OPTION_ERASE:
                case OPTION_FILE0_NAME:
                case OPTION_FILE1_NAME:
                case OPTION_FILE2_NAME:
                    break;
                default:
                    goto checkIfCursorIndexChanged;
            }
            return selectedOption;
        }
        if ((HuPadBtnDown[0] & B_BUTTON)) {
            if (selectedOption > OPTION_MAX) {
                goto checkIfCursorIndexChanged;
            }
        }
        switch (selectedOption) {
            case OPTION_FILE0:
            case OPTION_FILE1:
            case OPTION_FILE2:
                temp_v1 = filesel_FileUsedNumGet();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    filesel_WinMesSet(4, 0x2A00);
                    filesel_FileAnimStop(selectedOption);
                    cursorIndex = selectedOption + 1;
                    if (pressedInput & L_JPAD) {
                        cursorIndex = selectedOption - 1;
                        // if less than 0, wrap index back around to file index 2
                        if (cursorIndex < 0) {
                            cursorIndex = OPTION_FILE2;
                        }
                    } else {
                        cursorIndex = CLAMP_BELOW(cursorIndex, OPTION_FILES_END);
                    }
                } else if (pressedInput & (U_JPAD | D_JPAD)) {
                    if (pressedInput & U_JPAD) {
                        cursorIndex = OPTION_COPY;
                        if ((temp_v1 - 1) < (OPTION_FILES_END - 1)) {
                            filesel_WinMesSet(4, 0x2A01);
                        } else {
                            filesel_WinMesSet(4, 0x2A03);
                        }
                        filesel_FileAnimStop(selectedOption);
                    } else {
                        if (filesel_fileWork.files[cursorIndex].unk_04 == unkValue) {
                            cursorIndex = selectedOption + OPTION_FILES_NAME_BEGIN;
                            filesel_FileAnimStop(selectedOption);
                        }
                    }
                }
                break;
            case OPTION_COPY:
                temp_v1 = filesel_FileUsedNumGet();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    if (temp_v1 == 0) {
                        filesel_WinMesSet(4, 0x2A13);
                    } else {
                        filesel_WinMesSet(4, 0x2A07);
                    }
                    cursorIndex = OPTION_ERASE;
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = OPTION_FILE1;
                    filesel_WinMesSet(4, 0x2A00);
                }
                break;
            case OPTION_ERASE:
                temp_v1 = filesel_FileUsedNumGet();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    cursorIndex = OPTION_FILES_END;
                    if ((temp_v1 - 1) < 2) {
                        filesel_WinMesSet(4, 0x2A01);
                    } else {
                        filesel_WinMesSet(4, 0x2A03);
                    }
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = 2;
                    filesel_WinMesSet(4, 0x2A00);
                }
                break;
            case OPTION_FILE0_NAME:
            case OPTION_FILE1_NAME:
            case OPTION_FILE2_NAME:
                filesel_WinMesSet(4, 0x2A11);
                if (pressedInput & L_JPAD) {
                    cursorIndex = selectedOption;
                    do {
                        cursorIndex -= 1;
                        if (cursorIndex < OPTION_FILES_NAME_BEGIN) {
                            cursorIndex = 7;
                        }
                    } while (filesel_fileWork.files[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_04 != unkValue);
                } else {
                    if (pressedInput & R_JPAD) {
                        cursorIndex = selectedOption;
                        do {
                            // if cursor goes over max, wrap around back to file 0 name
                            if (++cursorIndex > OPTION_MAX) {
                                cursorIndex = OPTION_FILE0_NAME;
                            }
                        } while (filesel_fileWork.files[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_04 != unkValue);
                    }
                }
                if (pressedInput & U_JPAD) {
                    cursorIndex = selectedOption - OPTION_FILES_NAME_BEGIN;
                    filesel_WinMesSet(4, 0x2A00);
                }
                break;
        }

    checkIfCursorIndexChanged:
        if (selectedOption != cursorIndex) {
            // animate cursor to new position
            filesel_CursorMove(18, cursorIndex);
            selectedOption = cursorIndex;

            if (selectedOption < OPTION_FILES_END) {
                filesel_FileBreathStart(selectedOption);
            }
        }
        filesel_CursorPosSet(18, selectedOption);

        animTimerAdjusted = (animTimer < 0) ? animTimer + 7 : animTimer;
        animTimerAdjusted = (animTimerAdjusted >> 3);
        filesel_CursorOfsSet(18, -animTimerAdjusted);

        animTimer = (animTimer < 20) ? animTimer + 1 : 0;

        HuPrcVSleep();
    }
    return selectedOption;
}

s32 filesel_NewNameEntryExec(s32 arg0) {
    u8 buf[32]; // TODO: figure out correct type of this
    s32 temp_s0;

    bzero(&buf, sizeof(buf));
    filesel_FileNameSet(arg0, buf);
    HuPrcSleep(3);
    filesel_WinMesSet(4, 0x2A11);
    temp_s0 = filesel_NameEntryExec(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 filesel_RenameExec(s32 arg0) {
    s32 temp_s0;

    HuPrcSleep(3);
    temp_s0 = filesel_NameEntryExec(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 filesel_FileTargetChoice(s32 selection, s32 option0, s32 option1, s32 option2) {
    s32 options[3];
    s32 timer = 0;
    s32 input;
    s32 extraInput;

    options[0] = option0;
    options[1] = option1;
    options[2] = option2;
    filesel_CursorMove(18, selection);
    while (1) {
        HuPrcVSleep();
        filesel_CursorPosSet(18, selection);
        filesel_CursorOfsSet(18, -(timer / 8));
        timer = timer < 20 ? timer + 1 : 0;
        input = HuPadBtnRep[0];
        extraInput = filesel_StickBtnGet(0);
        if (extraInput != -1) {
            input |= extraInput;
        }
        if (HuPadBtnDown[0] & B_BUTTON) {
            return -1;
        }
        if (HuPadBtnDown[0] & A_BUTTON) {
            HuAudFXPlay(3);
            if (options[selection] == 1) {
                break;
            }
        } else if (input & L_JPAD) {
            do {
                selection--;
                if (selection < 0) {
                    selection = 2;
                }
            } while (options[selection] != 1);
            filesel_CursorMove(18, selection);
        } else if (input & R_JPAD) {
            do {
                selection++;
                selection = selection < 3 ? selection : 0;
            } while (options[selection] != 1);
            filesel_CursorMove(18, selection);
        }
    }
    return selection;
}

void filesel_CopySelect(void) {
    Vec sourcePosition;
    Vec destinationPosition;
    u8 name[0x20];
    s32 error = 0;
    s32 alpha;
    s32 i;
    s32 destination;
    s32 source;
    s32 model;
    s32 count;

    count = filesel_FileUsedNumGet();
    if (count <= 0) {
        filesel_WinMesSet(4, 0x2A03);
        error = 1;
    } else if (count >= 3) {
        filesel_WinMesSet(4, 0x2A04);
        error = 1;
    }
    if (error != 0) {
        filesel_CopyEraseBtnUpdate();
    } else {
        filesel_SprBankSet(2, 2, 0);
        filesel_TitleKill();
        filesel_TitleCreate(2);
        for (i = 0; i < 3; i++) {
            if (filesel_fileWork.files[i].unk_04 == UNK_VALUE) {
                break;
            }
        }
        source = i;
        filesel_WinMesSet(4, 0x2A02);
        source = filesel_FileTargetChoice(source,
                                       filesel_fileWork.files[0].unk_04 == UNK_VALUE,
                                       filesel_fileWork.files[1].unk_04 == UNK_VALUE,
                                       filesel_fileWork.files[2].unk_04 == UNK_VALUE);
        if (source < 0) {
            goto cancel;
        }
        switch (source) {
            case 0:
                filesel_WinInsertMesSet(4, 0, (u32) "1");
                break;
            case 1:
                filesel_WinInsertMesSet(4, 0, (u32) "2");
                break;
            case 2:
                filesel_WinInsertMesSet(4, 0, (u32) "3");
                break;
        }
        for (i = 0; i < 3; i++) {
            if (filesel_fileWork.files[i].unk_04 != UNK_VALUE) {
                break;
            }
        }
        filesel_WinMesSet(4, 0x2A05);
        destination = filesel_FileTargetChoice(i,
                                            source != 0 && filesel_fileWork.files[0].unk_04 != UNK_VALUE,
                                            source != 1 && filesel_fileWork.files[1].unk_04 != UNK_VALUE,
                                            source != 2 && filesel_fileWork.files[2].unk_04 != UNK_VALUE);
        if (destination < 0) {
            goto cancel;
        }
        filesel_WinDispOn(4);
        filesel_WinPosSet(4, 160.0f, 208.0f);
        filesel_WinMesSet(4, 0x2A16);
        HuPrcSleep(3);
        SLBoxCopy(source, destination);
        SLCurBoxNoSet(destination);
        SLLoadGameStat();
        filesel_FileStatRead(destination);
        HuPrcSleep(3);
        filesel_FileNameDispOff(destination);
        HuPrcSleep(3);
        filesel_MotionFlagSet(source, 0);
        filesel_MotionTimeSet(source, 0);
        HuAudFXPlay(0x2F6);
        filesel_MotionEndWait(source);
        filesel_ModelPosGet(source, &sourcePosition.x, &sourcePosition.y, &sourcePosition.z);
        filesel_ModelPosGet(destination, &destinationPosition.x, &destinationPosition.y, &destinationPosition.z);
        filesel_ModelCreate(6, 0x1F002B, 0x6A9);
        filesel_ModelPosSet(6, destinationPosition.x, destinationPosition.y, destinationPosition.z);
        filesel_ModelScaleSet(6, 0.8f, 0.8f, 0.8f);
        filesel_ModelDispOn(6);
        filesel_ModelKill(destination);
        filesel_ModelDispOff(destination + 3);
        filesel_ModelCreate(destination, 0x1F002A, 0x6A9);
        filesel_ModelPosSet(destination, sourcePosition.x, sourcePosition.y, sourcePosition.z);
        filesel_ModelScaleSet(destination, 0.8f, 0.8f, 0.8f);
        filesel_MotionTimeSet(destination, 0);
        filesel_MotionFlagSet(destination, 1);
        filesel_ModelDispOff(destination);
        model = filesel_ModelIdGet(6);
        Hu3DModelTPLvlInit(model);
        for (i = 0, alpha = 255; i < 16; i++) {
            Hu3DModelTPLvlSet(model, alpha);
            alpha -= 16;
            HuPrcVSleep();
        }
        filesel_ModelDispOff(6);
        filesel_ModelKill(6);
        filesel_ModelDispOn(destination);
        filesel_ModelDispOn(destination + 3);
        filesel_FileCopyStart(source, destination, 16);
        HuPrcSleep(16);
        filesel_MotionFlagSet(source, 4);
        HuAudFXPlay(0x2F7);
        filesel_MotionEndWait(source);
        HuPrcSleep(3);
        filesel_FileNameGet(destination, name);
        filesel_SprKill(destination + 13);
        filesel_FileNameSprCreate(destination, 1);
        filesel_WinMesSet(destination + 1, (u32)name);
        filesel_FileNameDispOn(destination);
        filesel_CopyEraseBtnUpdate();
        filesel_WinMesSet(4, 0x2A06);
    }
    filesel_TitleKill();
    filesel_TitleCreate(0);
    return;

cancel:
    filesel_CursorMove(18, 3);
    filesel_CopyEraseBtnUpdate();
    filesel_TitleKill();
    filesel_TitleCreate(0);
    if ((u32)(filesel_FileUsedNumGet() - 1) < 3) {
        filesel_WinMesSet(4, 0x2A01);
    } else {
        filesel_WinMesSet(4, 0x2A03);
    }
}

void filesel_EraseSelect(void) {
    s32 timer = 0;
    s32 i;
    s32 selection;
    s32 cursor;
    s32 input;
    s32 extraInput;

    filesel_SprBankSet(3, 2, 0);
    filesel_TitleKill();
    filesel_TitleCreate(3);
    for (i = 0; i < 3; i++) {
        selection = i;
        if (filesel_fileWork.files[selection].unk_04 == UNK_VALUE) {
            break;
        }
    }
    if (i == 3) {
        filesel_CopyEraseBtnUpdate();
        filesel_TitleKill();
        filesel_TitleCreate(0);
        filesel_WinMesSet(4, 0x2A13);
        return;
    }
    filesel_WinMesSet(4, 0x2A08);
    cursor = selection;
    filesel_CursorMove(18, selection);
    while (1) {
        HuPrcVSleep();
        filesel_CursorPosSet(18, selection);
        filesel_CursorOfsSet(18, -(timer / 8));
        timer = timer < 20 ? timer + 1 : 0;
        input = HuPadBtnRep[0];
        extraInput = filesel_StickBtnGet(0);
        if (extraInput != -1) {
            input |= extraInput;
        }
        if (HuPadBtnDown[0] & A_BUTTON) {
            if (filesel_fileWork.files[selection].unk_04 == UNK_VALUE) {
                HuAudFXPlay(3);
                filesel_SprDispOff(18);
                HuPrcSleep(3);
                if (selection == 0) {
                    filesel_WinInsertMesSet(4, 0, (u32) "1");
                } else if (selection == 1) {
                    filesel_WinInsertMesSet(4, 0, (u32) "2");
                } else if (selection == 2) {
                    filesel_WinInsertMesSet(4, 0, (u32) "3");
                }
                filesel_WinInsertMesSet(4, 1, (u32) "0");
                filesel_WinInsertMesSet(4, 2, (u32) "0");
                filesel_WinInsertMesSet(4, 3, (u32) "0");
                HuWinAttrSet(filesel_winTbl[4].unk_00, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK, HUWIN_ATTR_NONE);
                HuWinActivePlayerSet(filesel_winTbl[4].unk_00, HUWIN_PLAYER_1);
                filesel_WinMesSet(4, 0x2A09);
                while (HuWinStatGet(filesel_winTbl[4].unk_00) != 0) {
                    HuPrcVSleep();
                }
                if (filesel_WinChoiceGet(4, 1, 0) == 0) {
                    filesel_WinMesSet(4, 0x2A0A);
                    while (HuWinStatGet(filesel_winTbl[4].unk_00) != 0) {
                        HuPrcVSleep();
                    }
                    if (filesel_WinChoiceGet(4, 1, 0) == 0) {
                        filesel_WinMesSet(4, 0x2A17);
                        HuPrcSleep(3);
                        SLCurBoxNoSet(selection);
                        filesel_fileWork.files[selection].unk_04 = 0;
                        GwCommon.unk_00 = 0;
                        SLCommonSet(1);
                        filesel_SprDispOff(18);
                        input = filesel_ModelIdGet(selection);
                        filesel_WinDispOff(4);
                        filesel_FileNameDispOff(selection);
                        filesel_ModelDispOff(selection + 3);
                        filesel_ModelCreate(selection, 0x1F0029, 0x6A9);
                        switch (selection) {
                            case 0:
                                filesel_ModelPosSet(0, -400.0f, 0.0f, 0.0f);
                                break;
                            case 1:
                                filesel_ModelPosSet(1, 0.0f, 0.0f, 0.0f);
                                break;
                            case 2:
                                filesel_ModelPosSet(2, 400.0f, 0.0f, 0.0f);
                                break;
                        }
                        filesel_ModelScaleSet(selection, 0.6f, 0.6f, 0.6f);
                        cursor = selection + 3;
                        filesel_ModelScaleSet(cursor, 0.6f, 0.6f, 0.6f);
                        filesel_MotionTimeSet(selection, 0);
                        filesel_MotionFlagSet(selection, 1);
                        filesel_ModelDispOn(selection);
                        filesel_ModelDispOn(cursor);
                        RepeatVibrator(0, 30, 0, 30);
                        filesel_FileWobbleStart(selection);
                        HuAudFXPlay(0x2F8);
                        filesel_FileMdlWaveKill((s16)input);
                        filesel_SprKill(selection + 13);
                        filesel_FileNameSprCreate(selection, 0);
                        filesel_FileNameSet(selection, (u8 *)"");
                        filesel_WinMesSet(selection + 1, (u32) "");
                        HuPrcSleep(3);
                        filesel_ModelDispOn(selection);
                        filesel_ModelDispOn(cursor);
                        filesel_ModelScaleSet(selection, 0.8f, 0.8f, 0.8f);
                        filesel_ModelScaleSet(cursor, 0.8f, 0.8f, 0.8f);
                        HuPrcSleep(16);
                        filesel_FileNameDispOn(selection);
                        HuWinAttrSet(filesel_winTbl[4].unk_00, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
                        filesel_WinMesSet(4, 0x2A0B);
                        filesel_WinDispOn(4);
                        filesel_SprDispOn(18);
                        break;
                    }
                }
                HuWinAttrSet(filesel_winTbl[4].unk_00, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
                filesel_WinMesSet(4, 0x2A08);
                break;
            }
        } else if (HuPadBtnDown[0] & B_BUTTON) {
            if (filesel_FileUsedNumGet() == 0) {
                filesel_WinMesSet(4, 0x2A04);
            } else {
                filesel_WinMesSet(4, 0x2A07);
            }
            break;
        }
        if (selection < 3) {
            if (selection < 0) {
                goto cursorChanged;
            }
            if (input & L_JPAD) {
                cursor = selection;
                do {
                    cursor--;
                    if (cursor < 0) {
                        cursor = 2;
                    }
                } while (filesel_fileWork.files[cursor].unk_04 != UNK_VALUE);
            } else if (input & R_JPAD) {
                cursor = selection;
                do {
                    cursor++;
                    cursor = cursor < 3 ? cursor : 0;
                } while (filesel_fileWork.files[cursor].unk_04 != UNK_VALUE);
            }
        }
    cursorChanged:
        if (selection != cursor) {
            filesel_CursorMove(18, cursor);
            selection = cursor;
        }
    }
    filesel_SprDispOn(18);
    filesel_CursorMove(18, 4);
    filesel_CopyEraseBtnUpdate();
    filesel_TitleKill();
    filesel_TitleCreate(0);
}

void filesel_FileMdlCreate(s32 fileIndex, f32 x, f32 y, f32 z) {
    s32 modelIndex = fileIndex;
    s32 nameIndex = fileIndex + 3;

    if (filesel_fileWork.files[fileIndex].unk_04 != UNK_VALUE) {
        filesel_ModelCreate(modelIndex, 0x1F0029, 0x6A9);
    } else {
        filesel_ModelCreate(modelIndex, 0x1F002A, 0x6A9);
    }
    filesel_ModelPosSet(modelIndex, x, y, z);
    filesel_ModelScaleSet(modelIndex, 0.8f, 0.8f, 0.8f);
    filesel_MotionTimeSet(modelIndex, 0);
    filesel_MotionFlagSet(modelIndex, 1);
    filesel_ModelDispOff(modelIndex);
    filesel_ModelCreate(nameIndex, filesel_fileNumMdlTbl[fileIndex], 0x6A9);
    filesel_ModelPosSet(nameIndex, x, y, z);
    filesel_ModelScaleSet(nameIndex, 0.8f, 0.8f, 0.8f);
    filesel_MotionTimeSet(nameIndex, 0);
    filesel_MotionFlagSet(nameIndex, 1);
    filesel_ModelDispOff(nameIndex);
}

void filesel_FileMdlWaveKill(s32 arg0) {
    s16 model = arg0;
    f32 angle;
    f32 progress;
    f32 scale;

    Hu3DModelObjAttrSet(model, 0x22000, 0x20000);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    HuPrcVSleep();
    progress = 0.0f;
    angle = 0.0f;
    scale = 1.0f;
    while (1) {
        if (progress > 1.0f) {
            break;
        }
        Hu3DVtxWaveAngle = angle;
        Hu3DModelVtxWave(model, progress, scale, 2);
        angle += 46.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        progress += 0.1f;
        scale += ((10.0f - scale) / 67.0f) * 4.0f;
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelKill(model);
    HuPrcSleep(3);
}

void filesel_NameCursorSet(s32 arg0) {
    if (arg0 >= 6) {
        arg0 = 5;
    }
    filesel_SprPosSet(19, arg0 * 10 + 104, 61);
}

void filesel_CursorPosGet(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    Vec pos;
    Vec2f screen;
    s32 x;
    s32 y;

    x = filesel_cursorPosTbl[arg1][0];
    y = filesel_cursorPosTbl[arg1][1];
    switch (arg1) {
        case 0:
        case 1:
        case 2:
            filesel_ModelPosGet(arg1, &pos.x, &pos.y, &pos.z);
            pos.x += 30.0f;
            pos.y += 300.0f;
            Hu3D3Dto2D(0, &pos, &screen);
            x = screen.x;
            y = screen.y;
            break;
        case 3:
        case 4:
            x = filesel_cursorPosTbl[arg1][0];
            y = filesel_cursorPosTbl[arg1][1];
            break;
        case 5:
            HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
            goto project;
        case 6:
            HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
            goto project;
        case 7:
            HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
        project:
            Hu3D3Dto2D(0, &pos, &screen);
            x = screen.x + 31.0f;
            y = 168;
            break;
    }
    *arg2 = x;
    *arg3 = y;
}

void filesel_CursorPosSet(s32 arg0, u32 arg1) {
    s32 x;
    s32 y;

    filesel_CursorPosGet(arg0, arg1, &x, &y);
    filesel_SprPosSet(arg0, x, y);
}

void filesel_CursorOfsSet(s32 arg0, u32 arg1) {
}

void filesel_CursorMove(s32 arg0, u32 arg1) {
    s32 targetX;
    s32 targetY;
    s32 startX;
    s32 startY;
    s32 i;
    f32 progress;

    filesel_CursorPosGet(arg0, arg1, &targetX, &targetY);
    filesel_SprPosGet(arg0, &startX, &startY);
    for (i = 0; i < 5; i++) {
        progress = i * 0.25f;
        filesel_SprPosSet(arg0, startX + progress * (targetX - startX),
                              startY + progress * (targetY - startY));
        HuPrcVSleep();
    }
    filesel_SprPosSet(arg0, targetX, targetY);
}

s32 filesel_NameEntryExec(s32 fileIndex) {
    f32 origin[2];
    u8 name[0x20];
    s16 window;
    s32 result;

    origin[0] = 39.0f;
    origin[1] = 95.0f;
    filesel_SprCreate(4, 0x1F0015);
    filesel_SprPriSet(4, 5);
    filesel_SprPosSet(4, 160, 152);
    filesel_SprDispOn(4);
    filesel_SprCreate(5, 0x1F0016);
    filesel_SprPriSet(5, 5);
    filesel_SprPosSet(5, 160, 152);
    filesel_SprDispOff(5);
    filesel_SprCreate(6, 0x1F0017);
    filesel_SprPriSet(6, 5);
    filesel_SprPosSet(6, 160, 152);
    filesel_SprDispOff(6);
    filesel_SprCreate(7, 0x1F0010);
    filesel_SprPriSet(7, 4);
    filesel_SprPosSet(7, origin[0] + 14.0f + 16.0f, origin[1] + 89.0f + 7.0f);
    filesel_SprDispOff(7);
    filesel_SprCreate(8, 0x1F0011);
    filesel_SprPriSet(8, 4);
    filesel_SprPosSet(8, origin[0] + 56.0f + 16.0f, origin[1] + 89.0f + 7.0f);
    filesel_SprDispOff(8);
    filesel_SprCreate(9, 0x1F0012);
    filesel_SprPriSet(9, 4);
    filesel_SprPosSet(9, origin[0] + 98.0f + 25.0f, origin[1] + 89.0f + 7.0f);
    filesel_SprDispOff(9);
    filesel_SprCreate(10, 0x1F0013);
    filesel_SprPriSet(10, 4);
    filesel_SprPosSet(10, origin[0] + 168.0f + 7.0f, origin[1] + 89.0f + 7.0f);
    filesel_SprDispOff(10);
    filesel_SprCreate(11, 0x1F0014);
    filesel_SprPriSet(11, 4);
    filesel_SprPosSet(11, origin[0] + 202.0f + 13.0f, origin[1] + 89.0f + 7.0f);
    filesel_SprDispOff(11);
    filesel_SprCreate(17, 0x1F001A);
    filesel_SprPriSet(17, 5);
    filesel_SprPosSet(17, 160, 113);
    filesel_SprDispOff(17);
    filesel_SprCreate(19, 0x1F001B);
    filesel_SprPriSet(19, 0);
    filesel_SprScaleSet(19, 1.0f, 1.0f);
    filesel_SprPosSet(19, 160, 113);
    filesel_SprDispOff(19);
    filesel_SprCreate(48, 0x1F0023);
    filesel_SprPriSet(48, 4);
    filesel_SprPosSet(48, origin[0] + 14.0f + 20.0f - 4.0f, origin[1] + 89.0f + 10.0f - 3.0f);
    filesel_SprDispOff(48);
    filesel_SprCreate(49, 0x1F0023);
    filesel_SprPriSet(49, 4);
    filesel_SprPosSet(49, origin[0] + 56.0f + 20.0f - 4.0f, origin[1] + 89.0f + 10.0f - 3.0f);
    filesel_SprDispOff(49);
    filesel_SprCreate(50, 0x1F0024);
    filesel_SprPriSet(50, 4);
    filesel_SprPosSet(50, origin[0] + 98.0f + 28.0f - 3.0f, origin[1] + 89.0f + 10.0f - 3.0f);
    filesel_SprDispOff(50);
    filesel_SprCreate(51, 0x1F0025);
    filesel_SprPriSet(51, 4);
    filesel_SprPosSet(51, origin[0] + 168.0f + 10.0f - 3.0f, origin[1] + 89.0f + 10.0f - 3.0f);
    filesel_SprDispOff(51);
    filesel_SprCreate(52, 0x1F0026);
    filesel_SprPriSet(52, 4);
    filesel_SprPosSet(52, origin[0] + 202.0f + 16.0f - 3.0f, origin[1] + 89.0f + 10.0f - 3.0f);
    filesel_SprDispOff(52);
    filesel_nameChangeF = 0;
    bzero(name, sizeof(name));
    filesel_FileNameGet(fileIndex, name);
    filesel_WinCreate(10, (u32)name, 104, 46, 62, 20, 2);
    window = filesel_WinIdGet(10);
    HuWinAttrSet(window, HUWIN_ATTR_MONOSPACE, HUWIN_ATTR_MONOSPACE);
    HuWinBGColSet(window, 128, 128, 128);
    HuWinMesColSet(window, 7);
    filesel_SprCreate(16, 0x1F0020);
    filesel_SprScaleSet(16, 1.0f, 1.0f);
    filesel_SprAlphaSet(16, 256);
    filesel_SprPosSet(16, 135, 56);
    filesel_WinMesSet(10, (u32)name);
    filesel_WinScaleSet(10, 1.0f, 1.0f);
    filesel_NameInputSet(name);
    result = filesel_NameInputExec(fileIndex);
    if (result != 0) {
        filesel_NameInputGet(name);
        if (name[0] == 0 && name[1] == 0) {
            result = 0;
        } else {
            filesel_FileNameSet(fileIndex, name);
            filesel_WinMesSet(fileIndex + 1, (u32)name);
        }
    }
    filesel_SprBGDispOff(19);
    filesel_WinDispOff(10);
    filesel_SprBGDispOff(4);
    filesel_SprBGDispOff(5);
    filesel_SprBGDispOff(6);
    filesel_SprBGDispOff(7);
    filesel_SprBGDispOff(48);
    filesel_SprBGDispOff(8);
    filesel_SprBGDispOff(9);
    filesel_SprBGDispOff(10);
    filesel_SprBGDispOff(11);
    filesel_SprBGDispOff(17);
    filesel_SprBGDispOff(19);
    filesel_SprBGDispOff(48);
    filesel_SprBGDispOff(49);
    filesel_SprBGDispOff(50);
    filesel_SprBGDispOff(51);
    filesel_SprBGDispOff(52);
    filesel_WinKill(10);
    filesel_SprKill(16);
    HuPrcSleep(3);
    filesel_SprKill(4);
    filesel_SprKill(5);
    filesel_SprKill(6);
    filesel_SprKill(7);
    filesel_SprKill(8);
    filesel_SprKill(9);
    filesel_SprKill(10);
    filesel_SprKill(11);
    filesel_SprKill(17);
    filesel_SprKill(19);
    filesel_SprKill(48);
    filesel_SprKill(49);
    filesel_SprKill(50);
    filesel_SprKill(51);
    filesel_SprKill(52);
    return result;
}

u16 filesel_HiraganaCharGet(s32 arg0, s32 arg1) {
    u8 *str = (u8 *)filesel_hiraganaTbl[arg0];

    return (str[arg1 * 2] << 8) | str[arg1 * 2 + 1];
}

u16 filesel_KatakanaCharGet(s32 arg0, s32 arg1) {
    u8 *str = (u8 *)filesel_katakanaTbl[arg0];

    return (str[arg1 * 2] << 8) | str[arg1 * 2 + 1];
}

u16 filesel_AlphaCharGet(s32 arg0, s32 arg1) {
    u8 *str = (u8 *)filesel_alphaTbl[arg1];

    return (str[arg0 * 2] << 8) | str[arg0 * 2 + 1];
}

void filesel_NameInputSet(u8 *arg0) {
    bzero(filesel_nameInput.name, sizeof(filesel_nameInput.name));
    bcopy(arg0, filesel_nameInput.name, sizeof(filesel_nameInput.name));
}

void filesel_NameInputGet(u8 *arg0) {
    bzero(arg0, 0x20);
    bcopy(filesel_nameInput.name, arg0, 0x20);
}

s32 filesel_KeyCursorPosGet(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4) {
    s32 x = 47;
    s32 y = 103;

    switch (arg0) {
        case 4:
        case 5:
            x += 5;
            y += 12;
            if (arg1 >= 10) {
                x += 5;
            }
            if (arg1 >= 11) {
                if (arg1 < 15) {
                    x += (arg1 - 10) * 2;
                } else {
                    x += 10;
                }
            }
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        case 6:
            x += 42;
            y += 12;
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        default:
            x = 0;
            y = 0;
            break;
    }
    *arg3 = x;
    *arg4 = y;
    return 0;
}

void filesel_KeyboardDispSet(s32 arg0) {
    if (arg0 != -1) {
        filesel_SprDispOn(arg0);
    }
    if (arg0 != 4) {
        filesel_SprDispOff(4);
    }
    if (arg0 != 5) {
        filesel_SprDispOff(5);
    }
    if (arg0 != 6) {
        filesel_SprDispOff(6);
    }
}

void filesel_NameOptionDispSet(s32 arg0) {
    if (arg0 != -1) {
        filesel_SprDispOn(arg0);
    }
    if (arg0 != 7) {
        filesel_SprDispOff(7);
        filesel_SprDispOff(0x30);
    } else {
        filesel_SprDispOn(0x30);
    }
    if (arg0 != 8) {
        filesel_SprDispOff(8);
        filesel_SprDispOff(0x31);
    } else {
        filesel_SprDispOn(0x31);
    }
    if (arg0 != 9) {
        filesel_SprDispOff(9);
        filesel_SprDispOff(0x32);
    } else {
        filesel_SprDispOn(0x32);
    }
    if (arg0 != 10) {
        filesel_SprDispOff(10);
        filesel_SprDispOff(0x33);
    } else {
        filesel_SprDispOn(0x33);
    }
    if (arg0 != 11) {
        filesel_SprDispOff(11);
        filesel_SprDispOff(0x34);
    } else {
        filesel_SprDispOn(0x34);
    }
    filesel_nameInput.frame = 0;
}

void filesel_NameOptionBlink(s32 arg0) {
    s32 frame;
    s32 direction;
    f32 alpha;
    u8 opacity;
    s32 *counter;

    frame = filesel_nameInput.frame;
    if (frame < 0) {
        frame = -frame;
    }
    direction = filesel_nameInput.frame >= 0;
    // The do-while(0) ends a CSE block, keeping GCC from folding the alpha math.
    do {
        alpha = 1.0f;
    } while (0);
    frame++;
    if (direction != 0) {
        opacity = alpha * 255.0f;
    } else {
        opacity = (1.0f - alpha) * 255.0f;
    }
    counter = &filesel_nameInput.frame;
    *counter = frame;
    if (direction < 0) {
        *counter = -frame;
    }
    if (arg0 != -1) {
        filesel_SprAlphaSet(arg0, opacity);
    }
    if (arg0 != 7) {
        filesel_SprAlphaSet(7, opacity);
    }
    if (arg0 != 8) {
        filesel_SprAlphaSet(8, opacity);
    }
    if (arg0 != 9) {
        filesel_SprAlphaSet(9, opacity);
    }
    if (arg0 != 10) {
        filesel_SprAlphaSet(10, opacity);
    }
    if (arg0 != 11) {
        filesel_SprAlphaSet(11, opacity);
    }
}

char *filesel_hiraganaTbl[] = {
    "\x82\xA0\x82\xA2\x82\xA4\x82\xA6\x82\xA8", // あいうえお
    "\x82\xA9\x82\xAB\x82\xAD\x82\xAF\x82\xB1", // かきくけこ
    "\x82\xB3\x82\xB5\x82\xB7\x82\xB9\x82\xBB", // さしすせそ
    "\x82\xBD\x82\xBF\x82\xC2\x82\xC4\x82\xC6", // たちつてと
    "\x82\xC8\x82\xC9\x82\xCA\x82\xCB\x82\xCC", // なにぬねの
    "\x82\xCD\x82\xD0\x82\xD3\x82\xD6\x82\xD9", // はひふへほ
    "\x82\xDC\x82\xDD\x82\xDE\x82\xDF\x82\xE0", // まみむめも
    "\x82\xE2\x81\x40\x82\xE4\x81\x40\x82\xE6", // や　ゆ　よ
    "\x82\xE7\x82\xE8\x82\xE9\x82\xEA\x82\xEB", // らりるれろ
    "\x82\xED\x81\x40\x82\xF0\x81\x40\x82\xF1", // わ　を　ん
    "\x82\xAA\x82\xAC\x82\xAE\x82\xB0\x82\xB2", // がぎぐげご
    "\x82\xB4\x82\xB6\x82\xB8\x82\xBA\x82\xBC", // ざじずぜぞ
    "\x82\xBE\x82\xC0\x82\xC3\x82\xC5\x82\xC7", // だぢづでど
    "\x82\xCE\x82\xD1\x82\xD4\x82\xD7\x82\xDA", // ばびぶべぼ
    "\x82\xCF\x82\xD2\x82\xD5\x82\xD8\x82\xDB", // ぱぴぷぺぽ
    "\x82\x9F\x82\xA1\x82\xA3\x82\xA5\x82\xA7", // ぁぃぅぇぉ
    "\x82\xE1\x81\x40\x82\xE3\x81\x40\x82\xE5", // ゃ　ゅ　ょ
    "\x82\xC1\x81\x40\x81\x7C\x81\x40\x81\x40", // っ　−　　
};

char *filesel_katakanaTbl[] = {
    "\x83\x41\x83\x43\x83\x45\x83\x47\x83\x49", // アイウエオ
    "\x83\x4A\x83\x4C\x83\x4E\x83\x50\x83\x52", // カキクケコ
    "\x83\x54\x83\x56\x83\x58\x83\x5A\x83\x5C", // サシスセソ
    "\x83\x5E\x83\x60\x83\x63\x83\x65\x83\x67", // タチツテト
    "\x83\x69\x83\x6A\x83\x6B\x83\x6C\x83\x6D", // ナニヌネノ
    "\x83\x6E\x83\x71\x83\x74\x83\x77\x83\x7A", // ハヒフヘホ
    "\x83\x7D\x83\x7E\x83\x80\x83\x81\x83\x82", // マミムメモ
    "\x83\x84\x81\x40\x83\x86\x81\x40\x83\x88", // ヤ　ユ　ヨ
    "\x83\x89\x83\x8A\x83\x8B\x83\x8C\x83\x8D", // ラリルレロ
    "\x83\x8F\x81\x40\x83\x92\x81\x40\x83\x93", // ワ　ヲ　ン
    "\x83\x4B\x83\x4D\x83\x4F\x83\x51\x83\x53", // ガギグゲゴ
    "\x83\x55\x83\x57\x83\x59\x83\x5B\x83\x5D", // ザジズゼゾ
    "\x83\x5F\x83\x61\x83\x64\x83\x66\x83\x68", // ダヂヅデド
    "\x83\x6F\x83\x72\x83\x75\x83\x78\x83\x7B", // バビブベボ
    "\x83\x70\x83\x73\x83\x76\x83\x79\x83\x7C", // パピプペポ
    "\x83\x40\x83\x42\x83\x44\x83\x46\x83\x48", // ァィゥェォ
    "\x83\x83\x81\x40\x83\x85\x81\x40\x83\x87", // ャ　ュ　ョ
    "\x83\x62\x81\x40\x81\x7C\x81\x40\x81\x40", // ッ　−　　
};

char *filesel_alphaTbl[] = {
    "\x82\x60\x82\x61\x82\x62\x82\x63\x82\x64\x82\x65\x82\x66\x82\x67\x82\x68\x82\x69\x82\x6A\x82\x6B\x82\x6C", // ＡＢＣＤＥＦＧＨＩＪＫＬＭ
    "\x82\x6D\x82\x6E\x82\x6F\x82\x70\x82\x71\x82\x72\x82\x73\x82\x74\x82\x75\x82\x76\x82\x77\x82\x78\x82\x79", // ＮＯＰＱＲＳＴＵＶＷＸＹＺ
    "\x82\x81\x82\x82\x82\x83\x82\x84\x82\x85\x82\x86\x82\x87\x82\x88\x82\x89\x82\x8A\x82\x8B\x82\x8C\x82\x8D", // ａｂｃｄｅｆｇｈｉｊｋｌｍ
    "\x82\x8E\x82\x8F\x82\x90\x82\x91\x82\x92\x82\x93\x82\x94\x82\x95\x82\x96\x82\x97\x82\x98\x82\x99\x82\x9A", // ｎｏｐｑｒｓｔｕｖｗｘｙｚ
    "\x82\x50\x82\x51\x82\x52\x82\x53\x82\x54\x82\x55\x82\x56\x82\x57\x82\x58\x82\x4F\x81\x44\x81\x7C\x81\x40", // １２３４５６７８９０．−　
};

f32 filesel_cameraFov = 58.0f;

Vec filesel_fileNamePosTbl[] = {
    { -400.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 400.0f, 0.0f, 0.0f },
};

Vec filesel_fileInPosTbl[][2] = {
    { { -400.0f, 0.0f, -10000.0f }, { -400.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, -10000.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 400.0f, 0.0f, -10000.0f }, { 400.0f, 0.0f, 0.0f } },
};

Vec filesel_fileOutPosTbl[][2] = {
    { { -400.0f, 0.0f, -2000.0f }, { -400.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, -2000.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 400.0f, 0.0f, -2000.0f }, { 400.0f, 0.0f, 0.0f } },
};

Vec filesel_fileRaisePosTbl[] = {
    { -400.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 400.0f, 0.0f, 0.0f },
};

Vec filesel_fileLowerPosTbl[] = {
    { -400.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 400.0f, 0.0f, 0.0f },
};

s32 filesel_stickBtn = 0;

u8 filesel_storyStageBoardTbl[][2] = {
    { 0, 1 },
    { 0, 2 },
    { 1, 1 },
    { 1, 2 },
    { 2, 1 },
    { 2, 2 },
    { 3, 1 },
    { 3, 2 },
    { 4, 1 },
    { 4, 2 },
    { 5, 2 },
    { 5, 1 },
};

s32 filesel_NameOptionInput(u32 buttons) {
    s32 length;
    if (buttons & START_BUTTON) {
        filesel_nameInput.mode = 1;
        filesel_nameInput.option = 11;
        filesel_KeyCursorDispOff();
        filesel_NameOptionDispSet(filesel_nameInput.option);
        return 0;
    }
    if (HuPadBtnDown[0] & A_BUTTON) {
        switch (filesel_nameInput.option) {
            case 7:
            case 8:
                HuAudFXPlay(1);
                filesel_nameInput.keyboard = 6;
                break;
            case 9:
                HuAudFXPlay(1);
                filesel_nameInput.keyboard = 6;
                if (filesel_nameInput.column >= 13) {
                    filesel_nameInput.column = 12;
                }
                break;
            case 10:
                filesel_nameInput.name[filesel_nameInput.length] = 0;
                if (filesel_nameInput.length > 0) {
                    HuAudFXPlay(0x2EF);
                    filesel_nameInput.length--;
                } else {
                    HuAudFXPlay(5);
                }
                filesel_nameInput.name[filesel_nameInput.length] = 0;
                filesel_WinMesSet(10, (u32)filesel_nameInput.name);
                filesel_NameCursorSet(filesel_nameInput.length + 1);
                break;
            case 11:
                HuAudFXPlay(2);
                if ((u16)((filesel_nameInput.name[0] << 8) | filesel_nameInput.name[1]) != 0) {
                    return 11;
                }
                bcopy(filesel_nameInput.encodedName, filesel_nameInput.name, 0x20);
                filesel_WinMesSet(10, (u32)filesel_nameInput.name);
                length = filesel_NameLenGet((UnkFileName *)filesel_nameInput.name);
                filesel_nameInput.name[length] = 0;
                filesel_nameInput.length = length;
                filesel_NameCursorSet(filesel_nameInput.length + 1);
                break;
        }
        filesel_NameOptionDispSet(filesel_nameInput.option);
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    } else if (HuPadBtnDown[0] & B_BUTTON) {
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        if (filesel_nameInput.length > 0) {
            HuAudFXPlay(0x2EF);
            filesel_nameInput.length--;
            filesel_nameInput.name[filesel_nameInput.length] = 0;
            filesel_WinMesSet(10, (u32)filesel_nameInput.name);
            filesel_NameCursorSet(filesel_nameInput.length + 1);
        } else {
            if (filesel_nameInput.option == 11) {
                return -1;
            }
            HuAudFXPlay(1);
            filesel_nameInput.option = 11;
            filesel_KeyCursorDispOff();
            filesel_NameOptionDispSet(filesel_nameInput.option);
        }
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    } else if (buttons & U_JPAD) {
        filesel_nameInput.mode = 0;
        filesel_NameOptionDispSet(-1);
        filesel_nameInput.row = 4;
        filesel_KeyCursorDispOn();
    } else if (buttons & D_JPAD) {
        filesel_nameInput.mode = 0;
        filesel_NameOptionDispSet(-1);
        filesel_nameInput.row = 0;
        filesel_KeyCursorDispOn();
    } else if (buttons & L_JPAD) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.option) {
            case 10:
                filesel_nameInput.option = 11;
                break;
            case 11:
                filesel_nameInput.option = 10;
                break;
        }
        filesel_NameOptionDispSet(filesel_nameInput.option);
    } else if (buttons & R_JPAD) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.option) {
            case 10:
                filesel_nameInput.option = 11;
                break;
            case 11:
                filesel_nameInput.option = 10;
                break;
        }
        filesel_NameOptionDispSet(filesel_nameInput.option);
    } else if (buttons & Z_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 6;
                break;
            case 5:
                filesel_nameInput.keyboard = 6;
                break;
            case 6:
                filesel_nameInput.keyboard = 6;
                break;
        }
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    } else if (buttons & R_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 6;
                break;
            case 5:
                filesel_nameInput.keyboard = 6;
                break;
            case 6:
                filesel_nameInput.keyboard = 6;
                break;
        }
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    }
    return 0;
}

void filesel_KeyCursorDispOn(void) {
    s16 x;
    s16 y;

    filesel_KeyCursorPosGet(filesel_nameInput.keyboard, filesel_nameInput.column, filesel_nameInput.row, &x, &y);
    filesel_SprPosSet(0x11, x, y);
    filesel_SprDispOn(0x11);
}

void filesel_KeyCursorDispOff(void) {
    filesel_SprDispOff(0x11);
}

s32 filesel_HiraganaInput(u32 buttons) {
    if (buttons & START_BUTTON) {
        filesel_nameInput.mode = 1;
        filesel_nameInput.option = 11;
        filesel_KeyCursorDispOff();
        filesel_NameOptionDispSet(filesel_nameInput.option);
        return 0;
    }
    if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        filesel_KeyCursorDispOn();
        if (buttons & U_JPAD) {
            if (--filesel_nameInput.row < 0) {
                filesel_nameInput.row = 0;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 7;
                filesel_NameOptionDispSet(7);
                filesel_KeyCursorDispOff();
                return 0;
            }
        } else if (buttons & D_JPAD) {
            if (++filesel_nameInput.row >= 5) {
                filesel_nameInput.row = 4;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 7;
                filesel_NameOptionDispSet(7);
                filesel_KeyCursorDispOff();
                goto end;
            }
        } else if (buttons & L_JPAD) {
            if (--filesel_nameInput.column < 0) {
                filesel_nameInput.column = 17;
            }
        } else if (buttons & R_JPAD) {
            if (++filesel_nameInput.column >= 18) {
                filesel_nameInput.column = 0;
            }
        } else {
            return 0;
        }
        filesel_KeyCursorDispOn();
        return 0;
    }
    if (HuPadBtnDown[0] & A_BUTTON) {
        if (filesel_nameInput.length < 5) {
            HuAudFXPlay(0x2EE);
            filesel_nameInput.name[filesel_nameInput.length] = filesel_HiraganaCharGet(filesel_nameInput.column, filesel_nameInput.row);
            filesel_nameInput.length++;
            filesel_nameChangeF = 1;
        }
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        filesel_WinMesSet(10, (u32)filesel_nameInput.name);
        filesel_NameCursorSet(filesel_nameInput.length + 1);
        if (filesel_nameInput.length >= 5) {
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (HuPadBtnDown[0] & B_BUTTON) {
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        if (filesel_nameInput.length > 0) {
            HuAudFXPlay(0x2EF);
            filesel_nameInput.length--;
            filesel_nameInput.name[filesel_nameInput.length] = 0;
            filesel_WinMesSet(10, (u32)filesel_nameInput.name);
            filesel_NameCursorSet(filesel_nameInput.length + 1);
            filesel_nameChangeF = 1;
        } else {
            HuAudFXPlay(1);
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (buttons & Z_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 6;
                if (filesel_nameInput.column >= 13) {
                    filesel_nameInput.column = 12;
                }
                filesel_KeyCursorDispOn();
                break;
            case 5:
                filesel_nameInput.keyboard = 4;
                break;
            case 6:
                filesel_nameInput.keyboard = 5;
                break;
        }
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    } else if (buttons & R_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 5;
                break;
            case 5:
                filesel_nameInput.keyboard = 6;
                if (filesel_nameInput.column >= 13) {
                    filesel_nameInput.column = 12;
                }
                filesel_KeyCursorDispOn();
                break;
            case 6:
                filesel_nameInput.keyboard = 4;
                break;
        }
        filesel_KeyCursorDispOn();
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    }
end:
    return 0;
}

s32 filesel_KatakanaInput(u32 buttons) {
    if (buttons & START_BUTTON) {
        filesel_nameInput.mode = 1;
        filesel_nameInput.option = 11;
        filesel_KeyCursorDispOff();
        filesel_NameOptionDispSet(filesel_nameInput.option);
        return 0;
    }
    if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        filesel_KeyCursorDispOn();
        if (buttons & U_JPAD) {
            if (--filesel_nameInput.row < 0) {
                filesel_nameInput.row = 0;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 8;
                filesel_NameOptionDispSet(8);
                filesel_KeyCursorDispOff();
                return 0;
            }
        } else if (buttons & D_JPAD) {
            if (++filesel_nameInput.row >= 5) {
                filesel_nameInput.row = 4;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 8;
                filesel_NameOptionDispSet(8);
                filesel_KeyCursorDispOff();
                goto end;
            }
        } else if (buttons & L_JPAD) {
            if (--filesel_nameInput.column < 0) {
                filesel_nameInput.column = 17;
            }
        } else if (buttons & R_JPAD) {
            if (++filesel_nameInput.column >= 18) {
                filesel_nameInput.column = 0;
            }
        } else {
            return 0;
        }
        filesel_KeyCursorDispOn();
        return 0;
    }
    if (HuPadBtnDown[0] & A_BUTTON) {
        if (filesel_nameInput.length < 5) {
            HuAudFXPlay(0x2EE);
            filesel_nameInput.name[filesel_nameInput.length] = filesel_KatakanaCharGet(filesel_nameInput.column, filesel_nameInput.row);
            filesel_nameInput.length++;
            filesel_nameChangeF = 1;
        }
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        filesel_WinMesSet(10, (u32)filesel_nameInput.name);
        filesel_NameCursorSet(filesel_nameInput.length + 1);
        if (filesel_nameInput.length >= 5) {
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (HuPadBtnDown[0] & B_BUTTON) {
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        if (filesel_nameInput.length > 0) {
            HuAudFXPlay(0x2EF);
            filesel_nameInput.length--;
            filesel_nameInput.name[filesel_nameInput.length] = 0;
            filesel_WinMesSet(10, (u32)filesel_nameInput.name);
            filesel_NameCursorSet(filesel_nameInput.length + 1);
            filesel_nameChangeF = 1;
        } else {
            HuAudFXPlay(1);
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (buttons & Z_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 6;
                if (filesel_nameInput.column >= 13) {
                    filesel_nameInput.column = 12;
                }
                filesel_KeyCursorDispOn();
                break;
            case 5:
                filesel_nameInput.keyboard = 4;
                break;
            case 6:
                filesel_nameInput.keyboard = 5;
                break;
        }
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    } else if (buttons & R_TRIG) {
        HuAudFXPlay(1);
        switch (filesel_nameInput.keyboard) {
            case 4:
                filesel_nameInput.keyboard = 5;
                break;
            case 5:
                filesel_nameInput.keyboard = 6;
                if (filesel_nameInput.column >= 13) {
                    filesel_nameInput.column = 12;
                }
                filesel_KeyCursorDispOn();
                break;
            case 6:
                filesel_nameInput.keyboard = 4;
                break;
        }
        filesel_KeyCursorDispOn();
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    }
end:
    return 0;
}

s32 filesel_AlphaInput(u32 buttons) {
    if (buttons & START_BUTTON) {
        filesel_nameInput.mode = 1;
        filesel_nameInput.option = 11;
        filesel_KeyCursorDispOff();
        filesel_NameOptionDispSet(filesel_nameInput.option);
        return 0;
    }
    if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
        filesel_KeyCursorDispOn();
        if (buttons & U_JPAD) {
            if (--filesel_nameInput.row < 0) {
                filesel_nameInput.row = 0;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 10;
                filesel_NameOptionDispSet(10);
                filesel_KeyCursorDispOff();
                return 0;
            }
        } else if (buttons & D_JPAD) {
            if (++filesel_nameInput.row >= 5) {
                filesel_nameInput.row = 4;
                filesel_nameInput.mode = 1;
                filesel_nameInput.option = 10;
                filesel_NameOptionDispSet(10);
                filesel_KeyCursorDispOff();
                goto end;
            }
        } else if (buttons & L_JPAD) {
            if (--filesel_nameInput.column < 0) {
                filesel_nameInput.column = 12;
            }
        } else if (buttons & R_JPAD) {
            if (++filesel_nameInput.column >= 13) {
                filesel_nameInput.column = 0;
            }
        } else {
            return 0;
        }
        filesel_KeyCursorDispOn();
        return 0;
    }
    if (HuPadBtnDown[0] & A_BUTTON) {
        if (filesel_nameInput.length < 5) {
            HuAudFXPlay(0x2EE);
            filesel_nameInput.name[filesel_nameInput.length] = filesel_AlphaCharGet(filesel_nameInput.column, filesel_nameInput.row);
            filesel_nameInput.length++;
            filesel_nameChangeF = 1;
        }
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        filesel_WinMesSet(10, (u32)filesel_nameInput.name);
        filesel_NameCursorSet(filesel_nameInput.length + 1);
        if (filesel_nameInput.length >= 5) {
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (HuPadBtnDown[0] & B_BUTTON) {
        filesel_nameInput.name[filesel_nameInput.length] = 0;
        if (filesel_nameInput.length > 0) {
            HuAudFXPlay(0x2EF);
            filesel_nameInput.length--;
            filesel_nameInput.name[filesel_nameInput.length] = 0;
            filesel_WinMesSet(10, (u32)filesel_nameInput.name);
            filesel_NameCursorSet(filesel_nameInput.length + 1);
            filesel_nameChangeF = 1;
        } else {
            HuAudFXPlay(1);
            filesel_nameInput.mode = 1;
            filesel_nameInput.option = 11;
            filesel_NameOptionDispSet(11);
            filesel_KeyboardDispSet(filesel_nameInput.keyboard);
            filesel_KeyCursorDispOff();
        }
        return 0;
    }
    if (buttons & Z_TRIG) {
        goto changeKeyboard;
    }
    if (buttons & R_TRIG) {
    changeKeyboard:
        filesel_KeyCursorDispOn();
        filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    }
end:
    return 0;
}

const u8 filesel_nameMario[16] = "\x82\x6C\x82\x81\x82\x92\x82\x89\x82\x8F"; // Ｍａｒｉｏ
const u8 filesel_nameLuigi[16] = "\x82\x6B\x82\x95\x82\x89\x82\x87\x82\x89"; // Ｌｕｉｇｉ
const u8 filesel_namePeach[16] = "\x82\x6F\x82\x85\x82\x81\x82\x83\x82\x88"; // Ｐｅａｃｈ
const u8 filesel_nameYoshi[16] = "\x82\x78\x82\x8F\x82\x93\x82\x88\x82\x89"; // Ｙｏｓｈｉ
const u8 filesel_nameWario[16] = "\x82\x76\x82\x81\x82\x92\x82\x89\x82\x8F"; // Ｗａｒｉｏ
const u8 filesel_nameDk[12] = "\x82\x63\x81\x40\x82\x6A";                 // Ｄ　Ｋ

s32 filesel_NameInputExec(s32 preset) {
    s32 input;
    s32 option;
    s32 random;
    const u8 *name;
    s32 length;
    s32 firstChar;
    s32 keyboard;

    length = filesel_NameLenGet((UnkFileName *)filesel_nameInput.name);
    firstChar = filesel_nameInput.name[0];
    (void)firstChar; // Read but never used in the original.
    filesel_nameInput.keyboard = 6;
    filesel_nameInput.mode = 1;
    filesel_nameInput.option = 11;
    filesel_nameInput.column = 0;
    filesel_nameInput.row = 0;
    filesel_nameInput.frame = 0;
    filesel_nameInput.length = length;
    random = rand16() % 6;
    switch (random) {
        case 1:
            name = filesel_nameLuigi;
            break;
        case 2:
            name = filesel_namePeach;
            break;
        case 3:
            name = filesel_nameYoshi;
            break;
        case 4:
            name = filesel_nameWario;
            break;
        case 5:
            name = filesel_nameDk;
            break;
        case 0:
        default:
            name = filesel_nameMario;
            break;
    }
    bcopy(name, filesel_nameInput.encodedName, 0x12);
    filesel_KeyboardDispSet(filesel_nameInput.keyboard);
    filesel_NameOptionDispSet(filesel_nameInput.option);
    HuPrcVSleep();
    filesel_SprDispOn(19);
    filesel_SprPriSet(19, 0);
    filesel_NameCursorSet(filesel_nameInput.length + 1);
    while (1) {
        keyboard = filesel_nameInput.keyboard;
        (void)keyboard; // Read but never used in the original.
        option = filesel_nameInput.option;
        input = HuPadBtnRep[0];
        input |= filesel_StickRepGet(0);
        if (filesel_nameInput.mode) {
            input = filesel_NameOptionInput(input);
            filesel_NameOptionBlink(option);
        } else {
            input = filesel_AlphaInput(input);
        }
        if (input == 11) {
            if ((u16)((filesel_nameInput.name[0] << 8) | filesel_nameInput.name[1]) == 0) {
                switch (preset) {
                    case 0:
                        bcopy(filesel_nameMario, filesel_nameInput.name, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    case 1:
                        bcopy(filesel_nameLuigi, filesel_nameInput.name, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    case 2:
                        bcopy(filesel_namePeach, filesel_nameInput.name, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    case 3:
                        bcopy(filesel_nameYoshi, filesel_nameInput.encodedName, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    case 4:
                        bcopy(filesel_nameWario, filesel_nameInput.encodedName, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    case 5:
                        bcopy(filesel_nameDk, filesel_nameInput.encodedName, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                    default:
                        bcopy(filesel_nameMario, filesel_nameInput.encodedName, 0x12);
                        filesel_nameChangeF = 1;
                        break;
                }
            }
            filesel_WinMesSet(10, (u32)filesel_nameInput.name);
            HuPrcSleep(3);
            filesel_nameChangeF = 1;
            return 1;
        }
        if (input == -1) {
            return -1;
        }
        HuPrcVSleep();
    }
}

s32 filesel_ModeChoice(s32 fileIndex) {
    s32 frame = 0;
    f32 positions[2][2] = { { 80.0f, 48.0f }, { 240.0f, 48.0f } };
    s32 startX;
    s32 startY;
    s32 input;
    s32 targetX;
    s32 targetY;
    s32 selected = 1;
    s32 stick;
    f32 progress;

    filesel_SprPosSet(18, positions[1][0], positions[1][1]);
    filesel_SprDispOn(18);
    filesel_WinMesSet(4, 0x2A0E);
    while (1) {
        HuPrcVSleep();
        input = HuPadBtnRep[0];
        stick = filesel_StickBtnGet(0);
        if (stick != -1) {
            input |= stick;
        }
        if (HuPadBtnDown[0] & B_BUTTON) {
            input = -1;
            break;
        }
        if (HuPadBtnDown[0] & A_BUTTON) {
            filesel_SprBGDispOff(18);
            if (selected == 0) {
                HuAudFXPlay(3);
                if (_CheckFlag(0x18)) {
                    filesel_WinMesSet(4, 0x2A0F);
                    filesel_WinMesWait(4);
                    stick = filesel_WinChoiceGet(4, 0, 0);
                    if (stick == 0) {
                        input = 1;
                        break;
                    }
                    if (stick == 1) {
                        filesel_WinMesSet(4, 0x2A10);
                        filesel_WinMesWait(4);
                        if (filesel_WinChoiceGet(4, 0, 0) == 0) {
                            filesel_WinMesSet(4, (u32)filesel_emptyStr);
                            HuPrcVSleep();
                            HuWinAttrSet(filesel_winTbl[4].unk_00, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK, HUWIN_ATTR_NONE);
                            filesel_WinMesSet(4, 0x2A18);
                            filesel_WinMesWait(4);
                            filesel_WinMesSet(4, 0x2A19);
                            filesel_WinMesWait(4);
                            input = filesel_WinChoiceGet(4, 1, 0) == 0 ? 2 : -1;
                            HuWinAttrSet(filesel_winTbl[4].unk_00, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
                            break;
                        }
                    }
                } else {
                    input = 2;
                    break;
                }
                filesel_WinMesSet(4, 0x2A0D);
                filesel_SprBGDispOn(18);
            } else {
                HuAudFXPlay(3);
                input = 0;
                break;
            }
        } else if (input & (L_JPAD | R_JPAD)) {
            selected = (((u32)input >> 9) ^ 1) & 1;
            if (selected == 0) {
                filesel_SprPosGet(18, &startX, &startY);
                targetX = positions[0][0];
                targetY = positions[0][1];
                for (input = 0; input < 5; input++) {
                    progress = input * 0.25f;
                    filesel_SprPosSet(18, startX + progress * (targetX - startX),
                                          startY + progress * (targetY - startY));
                    HuPrcVSleep();
                }
                filesel_SprPosSet(18, positions[0][0], positions[0][1]);
                filesel_WinMesSet(4, 0x2A0D);
            } else {
                filesel_SprPosGet(18, &startX, &startY);
                targetX = positions[1][0];
                targetY = positions[1][1];
                for (input = 0; input < 5; input++) {
                    progress = input * 0.25f;
                    filesel_SprPosSet(18, startX + progress * (targetX - startX),
                                          startY + progress * (targetY - startY));
                    HuPrcVSleep();
                }
                filesel_SprPosSet(18, positions[1][0], positions[1][1]);
                filesel_WinMesSet(4, 0x2A0E);
            }
        }
        filesel_CursorOfsSet(18, -(frame / 8));
        frame = frame < 20 ? frame + 1 : 0;
    }
    filesel_SprDispOff(18);
    filesel_HelpWinOut();
    filesel_StoryStatDispOff();
    filesel_BoardStatDispOff();
    return input;
}

void filesel_StoryStatCreate(s32 fileIndex) {
    u8 board;
    u8 flags;
    s32 x;
    s32 y;
    s16 sprite;
    s32 number;

    filesel_StoryStageBoardGet(filesel_fileWork.files[fileIndex].unk_48, &board, &flags);
    x = 80;
    y = 104;
    filesel_SprCreate(20, 0x1F0001);
    filesel_SprPosSet(20, x, y);
    filesel_SprPriSet(20, 6);
    filesel_SprDispOff(20);
    filesel_SprCreate(21, 0x1F0004);
    filesel_SprPriSet(21, 5);
    filesel_SprPosSet(21, x, y - 16);
    filesel_SprBankSet(21, filesel_fileWork.files[fileIndex].unk_2C, 0);
    filesel_SprDispOff(21);
    {
        u8 frames[] = { 0, 1, 2, 3, 4, 5 };
        filesel_SprCreate(22, 0x1F0003);
        filesel_SprPosSet(22, x, y + 3);
        filesel_SprPriSet(22, 6);
        filesel_SprBankSet(22, frames[filesel_fileWork.files[fileIndex].unk_44], 0);
        filesel_SprDispOff(22);
    }
    filesel_SprCreate(23, 0x1F000C);
    filesel_SprPriSet(23, 5);
    filesel_SprPosSet(23, x, y + 17);
    filesel_SprBankSet(23, (flags >> 1) & 1, 0);
    filesel_SprDispOff(23);
    sprite = filesel_EspIdGet(23);
    if (flags & 2) {
        espColorSet(sprite, 255, 64, 64);
    } else {
        espColorSet(sprite, 0, 255, 255);
    }
    if (flags & 2) {
        filesel_SprCreate(24, 0x1F000A);
    } else {
        filesel_SprCreate(24, 0x1F000B);
    }
    filesel_SprPriSet(24, 5);
    filesel_SprPosSet(24, x, y + 28);
    filesel_SprBankSet(24, board, 0);
    filesel_SprDispOff(24);
    if (!_CheckFlag(0x18)) {
        filesel_SprCreate(25, 0x1F0009);
        filesel_SprPriSet(25, 5);
        filesel_SprPosSet(25, x, y - 4);
    } else if (!_CheckFlag(0x28)) {
        filesel_SprCreate(25, 0x1F0005);
        filesel_SprPriSet(25, 5);
        filesel_SprPosSet(25, x - 2, y + 28);
        filesel_SprPosSet(24, x, y + 44);
    } else {
        filesel_SprCreate(25, 0x1F0006);
        filesel_SprPriSet(25, 5);
        filesel_SprPosSet(25, x - 16, y + 44);
    }
    y += 44;
    filesel_SprDispOff(25);
    filesel_SprCreate(26, 0x1F0007);
    filesel_SprPriSet(26, 5);
    filesel_SprPosSet(26, x + 8, y);
    filesel_SprBankSet(26, 1, 0);
    number = filesel_fileWork.files[fileIndex].unk_3C % 10;
    filesel_SprBankSet(26, number, 0);
    filesel_SprDispOff(26);
    filesel_EspCreate(27, 26);
    filesel_SprPriSet(27, 5);
    filesel_SprPosSet(27, x, y);
    number = filesel_fileWork.files[fileIndex].unk_3C / 10;
    filesel_SprBankSet(27, number, 0);
    filesel_SprDispOff(27);
    filesel_EspCreate(28, 26);
    filesel_SprPriSet(28, 5);
    filesel_SprPosSet(28, x + 32, y);
    number = filesel_fileWork.files[fileIndex].unk_40 % 10;
    filesel_SprBankSet(28, number, 0);
    filesel_SprDispOff(28);
    filesel_EspCreate(29, 26);
    filesel_SprPriSet(29, 5);
    filesel_SprPosSet(29, x + 24, y);
    number = filesel_fileWork.files[fileIndex].unk_40 / 10;
    filesel_SprBankSet(29, number, 0);
    filesel_SprDispOff(29);
    filesel_SprCreate(30, 0x1F0028);
    filesel_SprPosSet(30, x + 16, y);
    espColorSet(filesel_EspIdGet(30), 0, 255, 0);
    filesel_SprPriSet(30, 5);
    filesel_SprDispOff(30);
}

void filesel_BoardStatCreate(s32 fileIndex) {
    s32 x = 240;
    s32 y = 104;
    s32 number;
    s32 row;

    filesel_SprCreate(31, 0x1F0002);
    filesel_SprPosSet(31, x, y);
    filesel_SprDispOff(31);
    filesel_SprCreate(32, 0x1F000C);
    filesel_SprPriSet(32, 5);
    filesel_SprPosSet(32, x, y - 21);
    filesel_SprBankSet(32, 0, 0);
    filesel_SprDispOff(32);
    espColorSet(filesel_EspIdGet(32), 0, 255, 255);
    filesel_EspCreate(40, 32);
    filesel_SprPriSet(40, 5);
    filesel_SprPosSet(40, x, y + 22);
    filesel_SprBankSet(40, 1, 0);
    filesel_SprDispOff(40);
    espColorSet(filesel_EspIdGet(40), 255, 64, 64);
    filesel_SprCreate(33, 0x1F000B);
    filesel_SprPriSet(33, 5);
    filesel_SprPosSet(33, x, y - 11);
    filesel_SprBankSet(33, filesel_fileWork.files[fileIndex].unk_74, 0);
    filesel_SprDispOff(33);
    filesel_SprCreate(41, 0x1F000A);
    filesel_SprPriSet(41, 5);
    filesel_SprPosSet(41, x, y + 32);
    filesel_SprBankSet(41, filesel_fileWork.files[fileIndex].unk_58, 0);
    filesel_SprDispOff(41);
    if (!_CheckFlag(0x16)) {
        filesel_SprCreate(34, 0x1F0009);
        filesel_SprPriSet(34, 5);
        filesel_SprPosSet(34, x, y - 1);
    } else {
        filesel_SprCreate(34, 0x1F0006);
        filesel_SprPriSet(34, 5);
        filesel_SprPosSet(34, x - 20, y + 5);
    }
    filesel_SprDispOff(34);
    row = y + 5;
    filesel_SprCreate(35, 0x1F0007);
    filesel_SprPriSet(35, 5);
    filesel_SprPosSet(35, x + 8, row);
    number = filesel_fileWork.files[fileIndex].unk_7C % 10;
    filesel_SprBankSet(35, number, 0);
    filesel_SprDispOff(35);
    filesel_EspCreate(36, 35);
    filesel_SprPriSet(36, 5);
    filesel_SprPosSet(36, x, row);
    number = filesel_fileWork.files[fileIndex].unk_7C / 10;
    filesel_SprBankSet(36, number, 0);
    filesel_SprDispOff(36);
    filesel_EspCreate(37, 35);
    filesel_SprPriSet(37, 5);
    filesel_SprPosSet(37, x + 32, row);
    number = filesel_fileWork.files[fileIndex].unk_80 % 10;
    filesel_SprBankSet(37, number, 0);
    filesel_SprDispOff(37);
    filesel_EspCreate(38, 35);
    filesel_SprPriSet(38, 5);
    filesel_SprPosSet(38, x + 24, row);
    number = filesel_fileWork.files[fileIndex].unk_80 / 10;
    filesel_SprBankSet(38, number, 0);
    filesel_SprDispOff(38);
    filesel_SprCreate(39, 0x1F0028);
    filesel_SprPosSet(39, x + 16, row);
    espColorSet(filesel_EspIdGet(39), 0, 255, 0);
    filesel_SprPriSet(39, 5);
    filesel_SprDispOff(39);
    if (!_CheckFlag(0x17)) {
        filesel_SprCreate(42, 0x1F0009);
        filesel_SprPriSet(42, 5);
        filesel_SprPosSet(42, x, y + 42);
    } else {
        filesel_SprCreate(42, 0x1F0006);
        filesel_SprPriSet(42, 5);
        filesel_SprPosSet(42, x - 16, y + 48);
    }
    row = y + 48;
    filesel_SprDispOff(42);
    filesel_SprCreate(43, 0x1F0007);
    filesel_SprPriSet(43, 5);
    filesel_SprPosSet(43, x + 8, row);
    number = filesel_fileWork.files[fileIndex].unk_60 % 10;
    filesel_SprBankSet(43, number, 0);
    filesel_SprDispOff(43);
    filesel_EspCreate(44, 43);
    filesel_SprPriSet(44, 5);
    filesel_SprPosSet(44, x, row);
    number = filesel_fileWork.files[fileIndex].unk_60 / 10;
    filesel_SprBankSet(44, number, 0);
    filesel_SprDispOff(44);
    filesel_EspCreate(45, 43);
    filesel_SprPriSet(45, 5);
    filesel_SprPosSet(45, x + 32, row);
    number = filesel_fileWork.files[fileIndex].unk_64 % 10;
    filesel_SprBankSet(45, number, 0);
    filesel_SprDispOff(45);
    filesel_EspCreate(46, 43);
    filesel_SprPriSet(46, 5);
    filesel_SprPosSet(46, x + 24, row);
    number = filesel_fileWork.files[fileIndex].unk_64 / 10;
    filesel_SprBankSet(46, number, 0);
    filesel_SprDispOff(46);
    if (filesel_fileWork.files[fileIndex].unk_64 != 20) {
        filesel_SprCreate(47, 0x1F0027);
        filesel_SprPosSet(47, x, y + 44);
    } else {
        filesel_SprCreate(47, 0x1F0028);
        filesel_SprPosSet(47, x + 16, y + 48);
    }
    espColorSet(filesel_EspIdGet(47), 0, 255, 0);
    filesel_SprPriSet(47, 5);
    filesel_SprDispOff(47);
}

void filesel_StoryStatKill(void) {
    filesel_SprKill(0x14);
    filesel_SprKill(0x15);
    filesel_SprKill(0x16);
    filesel_SprKill(0x17);
    filesel_SprKill(0x18);
    filesel_SprKill(0x19);
    filesel_SprKill(0x1E);
    filesel_SprKill(0x1D);
    filesel_SprKill(0x1C);
    filesel_SprKill(0x1B);
    filesel_SprKill(0x1A);
}

void filesel_StoryStatDispOn(s32 fileIndex) {
    filesel_SprBGDispOn(0x14);
    if (!_CheckFlag(0x18)) {
        filesel_SprBGDispOff(0x15);
        filesel_SprBGDispOff(0x16);
        filesel_SprBGDispOff(0x17);
        filesel_SprBGDispOff(0x18);
        filesel_SprBGDispOn(0x19);
        filesel_SprBGDispOff(0x1A);
        filesel_SprBGDispOff(0x1B);
        filesel_SprBGDispOff(0x1C);
        filesel_SprBGDispOff(0x1D);
        filesel_SprBGDispOff(0x1E);
    } else {
        filesel_SprBGDispOn(0x15);
        filesel_SprBGDispOn(0x16);
        filesel_SprBGDispOn(0x17);
        filesel_SprBGDispOn(0x18);
        filesel_SprBGDispOn(0x19);
        if (_CheckFlag(0x28)) {
            filesel_SprBGDispOn(0x1E);
            filesel_SprBGDispOn(0x1C);
            filesel_SprBGDispOn(0x1D);
            filesel_SprBGDispOn(0x1A);
            if (filesel_fileWork.files[fileIndex].unk_3C / 10) {
                filesel_SprBGDispOn(0x1B);
            }
        }
    }
}

void filesel_StoryStatDispOff(void) {
    filesel_SprBGDispOff(0x14);
    filesel_SprBGDispOff(0x15);
    filesel_SprBGDispOff(0x16);
    filesel_SprBGDispOff(0x17);
    filesel_SprBGDispOff(0x18);
    filesel_SprBGDispOff(0x19);
    filesel_SprBGDispOff(0x1A);
    filesel_SprBGDispOff(0x1B);
    filesel_SprBGDispOff(0x1C);
    filesel_SprBGDispOff(0x1D);
    filesel_SprBGDispOff(0x1E);
}

void filesel_BoardStatKill(void) {
    filesel_SprKill(0x1F);
    filesel_SprKill(0x28);
    filesel_SprKill(0x20);
    filesel_SprKill(0x21);
    filesel_SprKill(0x22);
    filesel_SprKill(0x27);
    filesel_SprKill(0x26);
    filesel_SprKill(0x25);
    filesel_SprKill(0x24);
    filesel_SprKill(0x23);
    filesel_SprKill(0x29);
    filesel_SprKill(0x2A);
    filesel_SprKill(0x2F);
    filesel_SprKill(0x2E);
    filesel_SprKill(0x2D);
    filesel_SprKill(0x2C);
    filesel_SprKill(0x2B);
}

void filesel_BoardStatDispOn(s32 fileIndex) {
    filesel_SprBGDispOn(0x1F);
    filesel_SprBGDispOn(0x28);
    filesel_SprBGDispOn(0x20);
    if (!_CheckFlag(0x16)) {
        filesel_SprBGDispOff(0x21);
        filesel_SprBGDispOn(0x22);
        filesel_SprBGDispOff(0x27);
        filesel_SprBGDispOff(0x26);
        filesel_SprBGDispOff(0x25);
        filesel_SprBGDispOff(0x24);
        filesel_SprBGDispOff(0x23);
    } else {
        filesel_SprBGDispOn(0x21);
        filesel_SprBGDispOn(0x22);
        filesel_SprBGDispOn(0x27);
        filesel_SprBGDispOn(0x25);
        filesel_SprBGDispOn(0x26);
        filesel_SprBGDispOn(0x23);
        if (filesel_fileWork.files[fileIndex].unk_7C / 10) {
            filesel_SprBGDispOn(0x24);
        }
    }
    if (!_CheckFlag(0x17)) {
        filesel_SprBGDispOff(0x29);
        filesel_SprBGDispOn(0x2A);
        filesel_SprBGDispOff(0x2C);
        filesel_SprBGDispOff(0x2B);
    } else {
        filesel_SprBGDispOn(0x29);
        filesel_SprBGDispOn(0x2F);
        if (filesel_fileWork.files[fileIndex].unk_64 == 20) {
            filesel_SprBGDispOn(0x2D);
            filesel_SprBGDispOn(0x2E);
            filesel_SprBGDispOn(0x2B);
            filesel_SprBGDispOn(0x2A);
            if (filesel_fileWork.files[fileIndex].unk_60 / 10) {
                filesel_SprBGDispOn(0x2C);
            }
        }
    }
}

void filesel_BoardStatDispOff(void) {
    filesel_SprBGDispOff(0x1F);
    filesel_SprBGDispOff(0x28);
    filesel_SprBGDispOff(0x20);
    filesel_SprBGDispOff(0x21);
    filesel_SprBGDispOff(0x22);
    filesel_SprBGDispOff(0x27);
    filesel_SprBGDispOff(0x26);
    filesel_SprBGDispOff(0x25);
    filesel_SprBGDispOff(0x24);
    filesel_SprBGDispOff(0x23);
    filesel_SprBGDispOff(0x29);
    filesel_SprBGDispOff(0x2A);
    filesel_SprBGDispOff(0x2F);
    filesel_SprBGDispOff(0x2E);
    filesel_SprBGDispOff(0x2D);
    filesel_SprBGDispOff(0x2C);
    filesel_SprBGDispOff(0x2B);
}

void filesel_CameraRotPosCalc(Vec *center, Vec *rotation, f32 distance, Vec *eye, Vec *target, Vec *up) {
    f32 pitch = rotation->x;
    f32 yaw = rotation->y;
    f32 roll = rotation->z;
    f32 upX;
    f32 upY;
    f32 upZ;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 length;

    eye->x = sindf(yaw) * cosdf(pitch) * distance + center->x;
    eye->y = -sindf(pitch) * distance + center->y;
    eye->z = cosdf(yaw) * cosdf(pitch) * distance + center->z;
    target->x = center->x;
    target->y = center->y;
    target->z = center->z;
    upX = sindf(yaw) * sindf(pitch);
    upY = cosdf(pitch);
    upZ = cosdf(yaw) * sindf(pitch);
    dx = target->x - eye->x;
    dy = target->y - eye->y;
    dz = target->z - eye->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(roll)) + upY * (dx * dy * (1.0f - cosdf(roll)) - dz * sindf(roll)) + upZ * (dx * dz * (1.0f - cosdf(roll)) + dy * sindf(roll));
    up->y = upX * (dx * dy * (1.0f - cosdf(roll)) + dz * sindf(roll)) + upY * (dy * dy + (1.0f - dy * dy) * cosdf(roll)) + upZ * (dy * dz * (1.0f - cosdf(roll)) - dx * sindf(roll));
    up->z = upX * (dx * dz * (1.0f - cosdf(roll)) - dy * sindf(roll)) + upY * (dy * dz * (1.0f - cosdf(roll)) + dx * sindf(roll)) + upZ * (dz * dz + (1.0f - dz * dz) * cosdf(roll));
}

void filesel_CameraInit(s32 arg0) {
    filesel_cameraMode = arg0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    Center.x = 0;
    Center.y = 200.0f;
    Center.z = 0;
    CZoom = 3000.0f;
    filesel_cameraNear = 80.0f;
    filesel_cameraFar = 8000.0f;
    filesel_cameraFov = 20.0f;
    HuVecCopyXYZ(&filesel_cameraFixPos, 10.0f, CRot.x, CRot.x);
    HuVecCopyXYZ(&filesel_cameraFixTarget, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&filesel_cameraFixUp, 0.0f, 1.0f, 0.0f);
    Hu3DCameraPerspectiveSet(0, filesel_cameraFov, filesel_cameraNear, filesel_cameraFar);
    Hu3DCameraPosSetV(0, &filesel_cameraFixPos, &filesel_cameraFixTarget, &filesel_cameraFixUp);
    Hu3DCamUpdateMtx(0);
}

void filesel_CameraProc(void) {
    f32 pitch;
    f32 yaw;
    f32 roll;
    f32 upX;
    f32 upY;
    f32 upZ;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 length;

    while (1) {
        if (filesel_cameraMode == -1 || filesel_cameraMode == 0) {
            if (filesel_cameraMode == 0) {
                if (HuPadBtn[0] & Z_TRIG) {
                    CZoom += HuPadStkY[0];
                    if (CZoom < 100.0f) {
                        CZoom = 100.0f;
                    } else if (CZoom > 8000.0f) {
                        CZoom = 8000.0f;
                    }
                } else {
                    CRot.x += HuPadStkY[0] * 0.1f;
                    if (CRot.x < 0.0f) {
                        CRot.x += 360.0f;
                    } else if (CRot.x >= 360.0f) {
                        CRot.x -= 360.0f;
                    }
                    CRot.y += HuPadStkX[0] * 0.1f;
                    if (CRot.y < 0.0f) {
                        CRot.y += 360.0f;
                    } else if (CRot.y >= 360.0f) {
                        CRot.y -= 360.0f;
                    }
                }
            }
            pitch = CRot.x;
            yaw = CRot.y;
            roll = CRot.z;
            filesel_cameraPos.x = sindf(yaw) * cosdf(pitch) * CZoom + Center.x;
            filesel_cameraPos.y = -sindf(pitch) * CZoom + Center.y;
            filesel_cameraPos.z = cosdf(yaw) * cosdf(pitch) * CZoom + Center.z;
            filesel_cameraTarget.x = Center.x;
            filesel_cameraTarget.y = Center.y;
            filesel_cameraTarget.z = Center.z;
            upX = sindf(yaw) * sindf(pitch);
            upY = cosdf(pitch);
            upZ = cosdf(yaw) * sindf(pitch);
            dx = filesel_cameraTarget.x - filesel_cameraPos.x;
            dy = filesel_cameraTarget.y - filesel_cameraPos.y;
            dz = filesel_cameraTarget.z - filesel_cameraPos.z;
            length = dx * dx + dy * dy + dz * dz;
            length = HuSqrtf(length);
            dx /= length;
            dy /= length;
            dz /= length;
            filesel_cameraUp.x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(roll)) + upY * (dx * dy * (1.0f - cosdf(roll)) - dz * sindf(roll)) + upZ * (dx * dz * (1.0f - cosdf(roll)) + dy * sindf(roll));
            filesel_cameraUp.y = upX * (dx * dy * (1.0f - cosdf(roll)) + dz * sindf(roll)) + upY * (dy * dy + (1.0f - dy * dy) * cosdf(roll)) + upZ * (dy * dz * (1.0f - cosdf(roll)) - dx * sindf(roll));
            filesel_cameraUp.z = upX * (dx * dz * (1.0f - cosdf(roll)) - dy * sindf(roll)) + upY * (dy * dz * (1.0f - cosdf(roll)) + dx * sindf(roll)) + upZ * (dz * dz + (1.0f - dz * dz) * cosdf(roll));
        } else {
            if (filesel_cameraMode != 1) {
                filesel_cameraFixPos.y += HuPadStkY[0];
                if (filesel_cameraFixPos.z < -2000.0f) {
                    filesel_cameraFixPos.z = -2000.0f;
                } else if (filesel_cameraFixPos.z > 2000.0f) {
                    filesel_cameraFixPos.z = 2000.0f;
                }
                filesel_cameraFixPos.x += HuPadStkX[0];
                if (filesel_cameraFixPos.x < -2000.0f) {
                    filesel_cameraFixPos.x = -2000.0f;
                } else if (filesel_cameraFixPos.x > 2000.0f) {
                    filesel_cameraFixPos.x = 2000.0f;
                }
            }
            HuVecCopy3F(&filesel_cameraPos, &filesel_cameraFixPos);
            HuVecCopy3F(&filesel_cameraTarget, &filesel_cameraFixTarget);
            HuVecCopy3F(&filesel_cameraUp, &filesel_cameraFixUp);
        }
        Hu3DCameraPosSetV(0, &filesel_cameraPos, &filesel_cameraTarget, &filesel_cameraUp);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

void filesel_CameraProcKill(void) {
    omDelPrcObj(filesel_cameraProc);
}

void filesel_CameraProcCreate(void) {
    filesel_CameraInit(-1);
    filesel_cameraProc = omAddPrcObj(filesel_CameraProc, 1, 0x2000, 0);
}

void filesel_MenuInit(void) {
    Vec position;
    Vec2f screen;
    s16 window;
    u32 width;
    f32 y;
    f32 x;

    filesel_WinCreate(0, 0x2A11, 24, 20, 200, 24, 2);
    window = filesel_WinIdGet(0);
    HuWinBGColSet(window, 128, 128, 128);
    HuWinMesColSet(window, 7);
    filesel_WinPriSet(0, 120);
    filesel_WinDispOff(0);
    filesel_TitleCreate(0);
    filesel_WinCreate(4, 0x2A00, 160, 175, 0, 0, 5);
    filesel_WinDispOff(4);
    filesel_SprCreate(18, 0x88);
    filesel_SprPriSet(18, 5);
    filesel_SprDispOff(18);
    width = 62;
    HuVecCopyXYZ(&position, -400.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &position, &screen);
    x = 31.0f;
    x = screen.x - x;
    y = 168.0f;
    filesel_WinCreate(1, (u32)filesel_fileWork.files[0].name, x, 168, width, 20, 2);
    window = filesel_WinIdGet(1);
    HuWinAttrSet(window, HUWIN_ATTR_MONOSPACE, HUWIN_ATTR_MONOSPACE);
    HuWinBGColSet(window, 192, 192, 192);
    HuWinMesColSet(window, 7);
    if (!(filesel_fileWork.files[0].name[0] | filesel_fileWork.files[0].name[1])) {
        filesel_WinMesSet(1, (u32) "");
        filesel_FileNameSprCreate(0, 0);
    } else {
        filesel_FileNameSprCreate(0, 1);
    }
    filesel_FileNameDispOff(0);
    HuVecCopyXYZ(&position, 0.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &position, &screen);
    x = screen.x - (s32)(width >> 1);
    filesel_WinCreate(2, (u32)filesel_fileWork.files[1].name, x, y, width, 20, 2);
    window = filesel_WinIdGet(2);
    HuWinAttrSet(window, HUWIN_ATTR_MONOSPACE, HUWIN_ATTR_MONOSPACE);
    HuWinBGColSet(window, 192, 192, 192);
    HuWinMesColSet(window, 7);
    if (!(filesel_fileWork.files[1].name[0] | filesel_fileWork.files[1].name[1])) {
        filesel_WinMesSet(2, (u32) "");
        filesel_FileNameSprCreate(1, 0);
    } else {
        filesel_FileNameSprCreate(1, 1);
    }
    filesel_FileNameDispOff(1);
    HuVecCopyXYZ(&position, 400.0f, 0.0f, 0.0f);
    Hu3D3Dto2D(0, &position, &screen);
    x = screen.x - (s32)(width >> 1);
    filesel_WinCreate(3, (u32)filesel_fileWork.files[2].name, x, y, width, 20, 2);
    window = filesel_WinIdGet(3);
    HuWinAttrSet(window, HUWIN_ATTR_MONOSPACE, HUWIN_ATTR_MONOSPACE);
    HuWinBGColSet(window, 128, 128, 128);
    HuWinMesColSet(window, 7);
    if (!(filesel_fileWork.files[2].name[0] | filesel_fileWork.files[2].name[1])) {
        filesel_WinMesSet(3, (u32) "");
        filesel_FileNameSprCreate(2, 0);
    } else {
        filesel_FileNameSprCreate(2, 1);
    }
    filesel_FileNameDispOff(2);
    filesel_FileMdlCreate(0, -400.0f, 0.0f, 0.0f);
    filesel_FileMdlCreate(1, -400.0f, 0.0f, 0.0f);
    filesel_FileMdlCreate(2, -400.0f, 0.0f, 0.0f);
}

void filesel_MenuClose(void) {
    filesel_ModelKill(0);
    filesel_ModelKill(1);
    filesel_ModelKill(2);
    filesel_ModelKill(3);
    filesel_ModelKill(4);
    filesel_ModelKill(5);
    filesel_WinKill(1);
    filesel_WinKill(2);
    filesel_WinKill(3);
    filesel_SprKill(13);
    filesel_SprKill(14);
    filesel_SprKill(15);
    filesel_SprKill(18);
    filesel_WinKill(0);
    filesel_TitleKill();
    filesel_WinKill(4);
}

void filesel_TitleKill(void) {
    filesel_SprKill(0xC);
}

void filesel_TitleCreate(s32 arg0) {
    s32 image;
    s32 x;
    s32 y;

    switch (arg0) {
        case 0:
            image = 0x1F001C;
            x = 0x5B;
            y = 0x21;
            break;
        case 1:
            image = 0x1F001D;
            x = 0x5E;
            y = 0x21;
            break;
        case 2:
            image = 0x1F001E;
            x = 0x36;
            y = 0x21;
            break;
        case 3:
            image = 0x1F001F;
            x = 0x3F;
            y = 0x21;
            break;
        case 4:
            image = 0x1F0022;
            x = 0x79;
            y = 0x1E;
            break;
        default:
            image = 0;
            y = 0;
            x = 0;
            break;
    }
    filesel_SprBGCreate(0xC, image);
    filesel_SprScaleSet(0xC, 1.0f, 1.0f);
    filesel_SprAlphaSet(0xC, 0x100);
    filesel_SprPosSet(0xC, x, y);
}

void filesel_FileNameSprCreate(s32 arg0, s32 arg1) {
    Vec position;
    Vec2f screen;
    s32 x;
    s32 image;

    image = arg1 ? 0x1F0020 : 0x1F0021;
    position.x = filesel_fileNamePosTbl[arg0].x;
    position.y = filesel_fileNamePosTbl[arg0].y;
    position.z = filesel_fileNamePosTbl[arg0].z;
    Hu3D3Dto2D(0, &position, &screen);
    x = screen.x;
    arg0 += 0xD;
    filesel_SprCreate(arg0, image);
    filesel_SprScaleSet(arg0, 1.0f, 1.0f);
    filesel_SprAlphaSet(arg0, 0x100);
    filesel_SprPosSet(arg0, x, 0xB1);
}

void filesel_FileNameDispOn(s32 arg0) {
    filesel_SprBGDispOn(arg0 + 0xD);
    filesel_WinDispOn(arg0 + 1);
}

void filesel_FileNameDispOff(s32 arg0) {
    filesel_SprBGDispOff(arg0 + 0xD);
    filesel_WinDispOff(arg0 + 1);
}

void filesel_FileInObjMain(omObjData *object) {
    Vec position;
    Vec rotation;
    Vec *start;
    Vec *end;
    s32 index;
    u32 slot;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 scale;
    f32 interpolation;
    f32 angle;

    slot = object->work[0];
    duration = object->work[1];
    frame = object->work[2];
    index = slot;
    start = &filesel_fileInPosTbl[index][0];
    end = &filesel_fileInPosTbl[index][1];
    progress = frame / duration;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    interpolation = progress * 0.9f;
    interpolation += 0.1f;
    scale = interpolation * 0.8f;
    filesel_ModelScaleSet(index, scale, scale, scale);
    filesel_ModelScaleSet(index + 3, scale, scale, scale);
    position.x = (end->x - start->x) * interpolation + start->x;
    position.y = (end->y - start->y) * interpolation + start->y;
    position.z = (end->z - start->z) * interpolation + start->z;
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    rotation.x = rotation.y = rotation.z = 0.0f;
    angle = progress * 3.0f;
    rotation.y = (angle - (s32)angle) * 360.0f;
    filesel_ModelRotSet(index, rotation.x, rotation.y, rotation.z);
    filesel_ModelRotSet(index + 3, rotation.x, rotation.y, rotation.z);
    if (frame >= duration) {
        filesel_ModelPosSet(index, end->x, end->y, end->z);
        filesel_ModelPosSet(index + 3, end->x, end->y, end->z);
        filesel_ModelScaleSet(index, 0.8f, 0.8f, 0.8f);
        filesel_ModelScaleSet(index + 3, 0.8f, 0.8f, 0.8f);
        omDelObj(object);
    } else {
        frame += 1.0f;
        object->work[2] = frame;
    }
}

omObjData *filesel_FileInCreate(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_FileInObjMain);

    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;

    filesel_ModelDispOn(arg0);
    filesel_ModelDispOn(arg0 + 3);
    return obj;
}

void filesel_FileOutObjMain(omObjData *object) {
    Vec position;
    Vec rotation;
    Vec *start;
    Vec *end;
    s32 index;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 scale;
    f32 interpolation;
    f32 angle;

    index = object->work[0];
    start = &filesel_fileOutPosTbl[index][0];
    end = &filesel_fileOutPosTbl[index][1];
    duration = object->work[1];
    frame = object->work[2];
    progress = frame / duration;
    progress = 1.0f - progress;
    if (progress < 0.0f) {
        progress = 0.0f;
    }
    interpolation = progress * 0.9f;
    interpolation += 0.1f;
    scale = interpolation * 0.8f;
    filesel_ModelScaleSet(index, scale, scale, scale);
    filesel_ModelScaleSet(index + 3, scale, scale, scale);
    interpolation = progress * 0.9f;
    interpolation += 0.1f;
    position.x = (end->x - start->x) * interpolation + start->x;
    position.y = (end->y - start->y) * interpolation + start->y;
    position.z = (end->z - start->z) * interpolation + start->z;
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    rotation.x = rotation.y = rotation.z = 0.0f;
    angle = progress * 3.0f;
    rotation.y = (angle - (s32)angle) * 360.0f;
    filesel_ModelRotSet(index, rotation.x, rotation.y, rotation.z);
    if (frame == duration) {
        omDelObj(object);
        filesel_ModelDispOff(index);
        filesel_ModelDispOff(index + 3);
    } else {
        frame += 1.0f;
        object->work[2] = frame;
    }
}

void filesel_FileOutCreate(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_FileOutObjMain);

    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
}

void filesel_FileRaiseObjMain(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    Vec rotation;
    s32 index;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 scale;
    f32 interpolation;
    f32 angle;
    f32 height;
    f32 finalScale = 0.48f;

    index = object->work[0];
    duration = filesel_fileMoveTbl[index].unk_08;
    frame = filesel_fileMoveTbl[index].unk_04;
    HuVecCopy3F(&start, &filesel_fileRaisePosTbl[index]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    progress = frame / duration;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    interpolation = 0.8f;
    scale = finalScale + (interpolation - finalScale) * (1.0f - progress);
    filesel_ModelScaleSet(index, scale, scale, scale);
    filesel_ModelScaleSet(index + 3, scale, scale, scale);
    interpolation = progress - interpolation;
    height = -1.6666666f * interpolation * interpolation + 1.06666662428114312;
    position.x = (end.x - start.x) * progress + start.x;
    position.y = (end.y - start.y) * height + start.y;
    position.z = (end.z - start.z) * progress + start.z;
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    rotation.x = rotation.y = rotation.z = 0.0f;
    angle = progress * 3.0f;
    rotation.y = (angle - (s32)angle) * 360.0f;
    filesel_ModelRotSet(index, rotation.x, rotation.y, rotation.z);
    filesel_ModelRotSet(index + 3, rotation.x, rotation.y, rotation.z);
    if (frame >= duration) {
        filesel_ModelPosSet(index, end.x, end.y, end.z);
        filesel_ModelPosSet(index + 3, end.x, end.y, end.z);
        filesel_ModelScaleSet(index, finalScale, finalScale, finalScale);
        filesel_ModelScaleSet(index + 3, finalScale, finalScale, finalScale);
        filesel_ModelRotSet(index, 0.0f, 0.0f, 0.0f);
        filesel_ModelRotSet(index + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(object);
    } else {
        frame += 1.0f;
        filesel_fileMoveTbl[index].unk_04 = frame;
    }
}

void filesel_FileRaiseKill(s32 arg0) {
    omDelObj(filesel_fileMoveTbl[arg0].unk_00);
}

omObjData *filesel_FileRaiseCreate(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_FileRaiseObjMain);

    obj->work[0] = arg0;
    filesel_fileMoveTbl[arg0].unk_00 = obj;
    filesel_fileMoveTbl[arg0].unk_08 = arg1;
    filesel_fileMoveTbl[arg0].unk_04 = 0;
    return obj;
}

void filesel_FileLowerObjMain(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    Vec rotation;
    s32 index;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 scale;
    f32 interpolation;
    f32 baseScale;
    f32 angle;
    f32 height;
    f32 finalScale = 0.48f;

    index = object->work[0];
    duration = filesel_fileMoveTbl[index].unk_08;
    frame = filesel_fileMoveTbl[index].unk_04;
    HuVecCopy3F(&start, &filesel_fileLowerPosTbl[index]);
    HuVecCopyXYZ(&end, -400.0f, 340.0f, 0.0f);
    interpolation = frame / duration;
    progress = 1.0f - interpolation;
    if (progress < 0.0f) {
        progress = 0.0f;
    }
    baseScale = 0.8f;
    scale = finalScale + (baseScale - finalScale) * (1.0f - progress);
    filesel_ModelScaleSet(index, scale, scale, scale);
    filesel_ModelScaleSet(index + 3, scale, scale, scale);
    interpolation = progress - baseScale;
    height = -1.6666666f * interpolation * interpolation + 1.06666662428114312;
    position.x = (end.x - start.x) * progress + start.x;
    position.y = (end.y - start.y) * height + start.y;
    position.z = (end.z - start.z) * progress + start.z;
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    rotation.x = rotation.y = rotation.z = 0.0f;
    angle = progress * 3.0f;
    rotation.y = (angle - (s32)angle) * 360.0f;
    filesel_ModelRotSet(index, rotation.x, rotation.y, rotation.z);
    filesel_ModelRotSet(index + 3, rotation.x, rotation.y, rotation.z);
    if (frame >= duration) {
        filesel_ModelPosSet(index, start.x, start.y, start.z);
        filesel_ModelPosSet(index + 3, start.x, start.y, start.z);
        filesel_ModelScaleSet(index, baseScale, baseScale, baseScale);
        filesel_ModelScaleSet(index + 3, baseScale, baseScale, baseScale);
        filesel_ModelRotSet(index, 0.0f, 0.0f, 0.0f);
        filesel_ModelRotSet(index + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(object);
    } else {
        frame += 1.0f;
        filesel_fileMoveTbl[index].unk_04 = frame;
    }
}

void filesel_FileLowerKill(s32 arg0) {
    omDelObj(filesel_fileMoveTbl[arg0].unk_00);
}

void filesel_FileLowerCreate(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_FileLowerObjMain);

    obj->work[0] = arg0;
    filesel_fileMoveTbl[arg0].unk_00 = obj;
    filesel_fileMoveTbl[arg0].unk_04 = 0;
    filesel_fileMoveTbl[arg0].unk_08 = arg1;
}

void filesel_FileJumpObjMain(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    Vec rotation;
    s32 index;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 scale;
    f32 height;
    f32 angle;

    index = object->work[0];
    duration = filesel_fileMoveTbl[index].unk_08;
    frame = filesel_fileMoveTbl[index].unk_04;
    HuVecCopy3F(&start, &filesel_fileMoveTbl[index].unk_0C);
    HuVecCopy3F(&end, &filesel_fileMoveTbl[index].unk_18);
    progress = frame / duration;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    if (end.y - start.y < 0.0f) {
        scale = progress * (0.8f - 0.48) + 0.48;
        filesel_ModelScaleSet(index, scale, scale, scale);
        filesel_ModelScaleSet(index + 3, scale, scale, scale);
    }
    if (end.y - start.y < 0.0f) {
        height = (0.2f - progress) * -1.6666666f * (0.2f - progress) + 1.0666666f;
        height = -height + 1.0f;
    } else {
        height = (progress - 0.8f) * -1.6666666f * (progress - 0.8f) + 1.0666666f;
    }
    position.x = (end.x - start.x) * progress + start.x;
    position.y = (end.y - start.y) * height + start.y;
    position.z = (end.z - start.z) * progress + start.z;
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    rotation.x = rotation.y = rotation.z = 0.0f;
    angle = progress * 3.0f;
    rotation.y = (angle - (s32)angle) * 360.0f;
    filesel_ModelRotSet(index, rotation.x, rotation.y, rotation.z);
    filesel_ModelRotSet(index + 3, rotation.x, rotation.y, rotation.z);
    if (frame >= duration) {
        filesel_ModelPosSet(index, end.x, end.y, end.z);
        filesel_ModelPosSet(index + 3, end.x, end.y, end.z);
        filesel_ModelRotSet(index, 0.0f, 0.0f, 0.0f);
        filesel_ModelRotSet(index + 3, 0.0f, 0.0f, 0.0f);
        omDelObj(object);
    } else {
        frame += 1.0f;
        filesel_fileMoveTbl[index].unk_04 = frame;
    }
}

void filesel_FileJumpKill(s32 arg0) {
    omDelObj(filesel_fileMoveTbl[arg0].unk_00);
}

omObjData *filesel_FileJumpCreate(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_FileJumpObjMain);
    f32 x;
    f32 y;
    f32 z;

    obj->work[0] = arg0;
    filesel_fileMoveTbl[arg0].unk_00 = obj;
    filesel_fileMoveTbl[arg0].unk_08 = arg4;
    filesel_fileMoveTbl[arg0].unk_04 = 0;

    filesel_ModelPosGet(arg0, &x, &y, &z);
    HuVecCopyXYZ(&filesel_fileMoveTbl[arg0].unk_0C, x, y, z);
    HuVecCopyXYZ(&filesel_fileMoveTbl[arg0].unk_18, arg1, arg2, arg3);
    return obj;
}

void filesel_FileAnimInit(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        filesel_fileAnimTbl[i].unk_00 = NULL;
    }
}

void filesel_FileAnimKill(s32 arg0) {
    omDelObj(filesel_fileAnimTbl[arg0].unk_00);
    filesel_fileAnimTbl[arg0].unk_00 = NULL;
}

void filesel_FileAnimMoveObjMain(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    s32 index;
    u32 slot;
    f32 fraction;
    f32 progress;

    index = object->work[0];
    slot = index;
    fraction = (f32)filesel_fileAnimTbl[index].unk_50 / (f32)filesel_fileAnimTbl[index].unk_58;
    progress = fraction > 1.0f ? 1.0f : fraction;
    HuVecCopy3F(&start, &filesel_fileAnimTbl[index].unk_04);
    HuVecCopy3F(&end, &filesel_fileAnimTbl[index].unk_10);
    HuVecCopyXYZ(&position, (end.x - start.x) * progress + start.x,
                 (end.y - start.y) * progress + start.y, (end.z - start.z) * progress + start.z);
    filesel_ModelPosSet(slot, position.x, position.y, position.z);
    if (progress > 1.0f) {
        filesel_FileAnimKill(index);
    }
}

void filesel_FileAnimCreate(s32 arg0, omObjFunc arg1) {
    omObjData *obj;

    if (filesel_fileAnimTbl[arg0].unk_00 != NULL) {
        omDelObj(filesel_fileAnimTbl[arg0].unk_00);
    }
    obj = omAddObj(6, 0, 0, -1, arg1);
    obj->work[0] = arg0;
    filesel_fileAnimTbl[arg0].unk_00 = obj;
}

void filesel_FileAnimMoveStart(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Vec pos;
    Vec target;

    filesel_FileAnimCreate(arg0, filesel_FileAnimMoveObjMain);
    filesel_ModelIdGet(arg0);
    filesel_ModelPosGet(arg0, &pos.x, &pos.y, &pos.z);
    HuVecCopy3F(&pos, &filesel_fileAnimTbl[arg0].unk_04);
    HuVecCopyXYZ(&target, arg1, arg2, arg3);
}

void filesel_FileAnimStop(u32 arg0) {
    filesel_FileAnimKill(arg0);
    filesel_ModelScaleSet(arg0, 0.8f, 0.8f, 0.8f);
    filesel_ModelScaleSet(arg0 + 3, 0.8f, 0.8f, 0.8f);
}

void filesel_FileBreathObjMain(omObjData *object) {
    s32 index;
    s32 angle;
    f32 wave;
    f32 x;
    f32 y;

    index = object->work[0];
    angle = filesel_fileAnimTbl[index].unk_50;
    angle += 27;
    if (angle > 360) {
        angle -= 360;
    }
    filesel_fileAnimTbl[index].unk_50 = angle;
    wave = sindf(angle) * 0.1f;
    x = wave + 0.8f;
    y = 0.8f - wave;
    filesel_ModelScaleSet(index, x, y, x);
    filesel_ModelScaleSet(index + 3, x, y, x);
}

void filesel_FileBreathStart(u32 arg0) {
    filesel_FileAnimCreate(arg0, filesel_FileBreathObjMain);
    filesel_fileAnimTbl[arg0].unk_50 = 0;
    filesel_ModelIdGet(arg0);
}

void filesel_FileWobbleObjMain(omObjData *object) {
    s32 index;
    s32 angle;
    s32 frame;
    s32 duration;
    u32 slot;
    f32 x;
    f32 y;
    f32 progress;
    f32 fraction;

    index = object->work[0];
    slot = index;
    angle = filesel_fileAnimTbl[index].unk_54;
    frame = filesel_fileAnimTbl[index].unk_50;
    duration = filesel_fileAnimTbl[index].unk_58;
    fraction = 1.0f - frame * (1.0f / 45.0f);
    progress = fraction < 0.0f ? 0.0f : fraction;
    angle += 27;
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    x = 0.0f;
    y = 0.0f;
    if (frame >= duration) {
        filesel_FileAnimStop(slot);
    } else {
        x = sindf(angle) * 0.3f * progress;
        y = 1.0f / (x + 1.0f) - 1.0f;
    }
    filesel_fileAnimTbl[index].unk_54 = angle;
    filesel_fileAnimTbl[index].unk_50 = frame + 1;
    filesel_ModelScaleSet(index, x + 0.8f, y + 0.8f, x + 0.8f);
    filesel_ModelScaleSet(index + 3, x + 0.8f, y + 0.8f, x + 0.8f);
}

void filesel_FileWobbleStart(s32 arg0) {
    filesel_FileAnimCreate(arg0, filesel_FileWobbleObjMain);
    filesel_fileAnimTbl[arg0].unk_58 = 45;
    filesel_fileAnimTbl[arg0].unk_50 = 0;
    filesel_fileAnimTbl[arg0].unk_54 = 0;
    filesel_ModelIdGet(arg0);
}

void filesel_FileCopyKill(s32 arg0) {
    omDelObj(filesel_fileAnimTbl[arg0].unk_00);
    filesel_fileAnimTbl[arg0].unk_00 = NULL;
}

void filesel_FileCopyObjMain(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    s32 index;
    s32 frame;
    f32 fraction;
    f32 progress;
    f32 height;
    f32 scale;

    index = object->work[0];
    frame = filesel_fileAnimTbl[index].unk_50;
    fraction = (f32)frame / (f32)filesel_fileAnimTbl[index].unk_58;
    progress = fraction > 1.0f ? 1.0f : fraction;
    height = (progress - 0.2f) * (-5.0f / 3.0f) * (progress - 0.2f) + 1.0666666f - (-progress + 1.0f);
    HuVecCopy3F(&start, &filesel_fileAnimTbl[index].unk_04);
    HuVecCopy3F(&end, &filesel_fileAnimTbl[index].unk_10);
    HuVecCopyXYZ(&position, (end.x - start.x) * progress + start.x,
                 (end.y - start.y) * progress + height * 400.0f + start.y,
                 (end.z - start.z) * progress + start.z);
    filesel_ModelPosSet(index, position.x, position.y, position.z);
    filesel_ModelPosSet(index + 3, position.x, position.y, position.z);
    scale = (progress * 0.7f + 0.3f) * 0.8f;
    filesel_ModelScaleSet(index, scale, scale, scale);
    filesel_ModelScaleSet(index + 3, scale, scale, scale);
    filesel_fileAnimTbl[index].unk_50 = ++frame;
    if (fraction > 1.0f) {
        filesel_FileCopyKill(index);
    }
}

void filesel_FileCopyStart(s32 arg0, s32 arg1, s32 arg2) {
    Vec positions[3] = {
        { -400.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 400.0f, 0.0f, 0.0f }
    };

    filesel_FileAnimCreate(arg1, filesel_FileCopyObjMain);
    filesel_ModelIdGet(arg1);
    HuVecCopy3F(&filesel_fileAnimTbl[arg1].unk_04, &positions[arg0]);
    filesel_fileAnimTbl[arg1].unk_04.y += 100.0f;
    HuVecCopy3F(&filesel_fileAnimTbl[arg1].unk_10, &positions[arg1]);
    filesel_fileAnimTbl[arg1].unk_50 = 0;
    filesel_fileAnimTbl[arg1].unk_58 = arg2;
}

void filesel_CameraEndObjMain(omObjData *object) {
    Vec center;
    Vec rotation;
    Vec position;
    Vec target;
    Vec up;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 distance;

    duration = filesel_cameraEnd.transition.duration;
    frame = filesel_cameraEnd.transition.frame;
    HuVecCopy3F(&center, &filesel_cameraEnd.center);
    HuVecCopy3F(&rotation, &filesel_cameraEnd.rotation);
    progress = frame / duration;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    rotation.x = progress * -88.0f;
    distance = ((1.0f - progress) * 0.75f + 0.25f) * 3000.0f;
    HuVecCopy3F(&filesel_cameraEnd.center, &center);
    HuVecCopy3F(&filesel_cameraEnd.rotation, &rotation);
    filesel_cameraEnd.transition.distance = distance;
    filesel_CameraRotPosCalc(&center, &rotation, distance, &position, &target, &up);
    Hu3DCameraPosSetV(0, &position, &target, &up);
    Hu3DCamUpdateMtx(0);
    if (frame == duration) {
        omDelObj(object);
    } else {
        frame += 1.0f;
        filesel_cameraEnd.transition.frame = frame;
    }
}

omObjData *filesel_CameraEndCreate(s32 duration) {
    omObjData *obj = omAddObj(6, 0, 0, -1, filesel_CameraEndObjMain);

    obj->work[0] = 0;
    obj->work[1] = duration;
    obj->work[2] = 0;
    HuVecCopyXYZ(&filesel_cameraEnd.center, 0.0f, 200.0f, 0.0f);
    HuVecCopyXYZ(&filesel_cameraEnd.rotation, 0.0f, 0.0f, 0.0f);
    filesel_cameraEnd.transition.distance = 3000.0f;
    filesel_cameraEnd.transition.duration = duration;
    filesel_cameraEnd.transition.frame = 0;
    return obj;
}

void filesel_StickInit(void) {
    filesel_stickBtn = 0;
    filesel_stickRepCnt = 0;
}

// converts one pad's analog stick position into a 8-way direction button mask,
// latching on the same direction repeating for a while
s32 filesel_StickRepGet(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;
    s32 direction;

    stickX = HuPadStkX[arg0];
    stickY = HuPadStkY[arg0];

    if (((stickX != 0) | (stickY != 0)) == 0) {
        return 0;
    }

    absX = __builtin_abs(stickX);
    absY = __builtin_abs(stickY);
    if (absY < absX) {
        if (absX > absY * 2) {
            direction = (stickX < 0) ? L_JPAD : R_JPAD;
        } else if (stickY > 0) {
            direction = (stickX < 0) ? (U_JPAD | L_JPAD) : (U_JPAD | R_JPAD);
        } else {
            direction = (stickX < 0) ? (D_JPAD | L_JPAD) : (D_JPAD | R_JPAD);
        }
    } else if (absY > absX * 2) {
        direction = (stickY < 0) ? D_JPAD : U_JPAD;
    } else if (stickY > 0) {
        direction = (stickX < 0) ? (U_JPAD | L_JPAD) : (U_JPAD | R_JPAD);
    } else {
        direction = (stickX < 0) ? (D_JPAD | L_JPAD) : (D_JPAD | R_JPAD);
    }

    if (filesel_stickBtn == direction && ++filesel_stickRepCnt < 9) {
        return 0;
    }
    filesel_stickBtn = direction;
    filesel_stickRepCnt = 0;
    return direction;
}

s32 filesel_StickBtnGet(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;

    stickX = HuPadStkX[arg0];
    stickY = HuPadStkY[arg0];
    if (filesel_stickBtn != 0) {
        if ((stickX == 0) & (stickY == 0)) {
            filesel_stickBtn = 0;
        }
        return 0;
    }
    if ((stickX != 0) | (stickY != 0)) {
        absX = __builtin_abs(stickX);
        absY = __builtin_abs(stickY);
        if (absY < absX) {
            if (absX > absY * 2) {
                if (stickX < 0) {
                    filesel_stickBtn = 0x200;
                } else {
                    filesel_stickBtn = 0x100;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    filesel_stickBtn = 0xA00;
                } else {
                    filesel_stickBtn = 0x900;
                }
            } else {
                if (stickX < 0) {
                    filesel_stickBtn = 0x600;
                } else {
                    filesel_stickBtn = 0x500;
                }
            }
        } else {
            if (absY > absX * 2) {
                if (stickY < 0) {
                    filesel_stickBtn = 0x400;
                } else {
                    filesel_stickBtn = 0x800;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    filesel_stickBtn = 0xA00;
                } else {
                    filesel_stickBtn = 0x900;
                }
            } else {
                if (stickX < 0) {
                    filesel_stickBtn = 0x600;
                } else {
                    filesel_stickBtn = 0x500;
                }
            }
        }
    }
    return filesel_stickBtn;
}

void filesel_FileReadAll(void) {
    s32 i;

    filesel_fileWork.selected = 0;
    for (i = 0; i < 3; i++) {
        SLCurBoxNoSet(i);
        SLLoadGameStat();
        if (GwCommon.unk_00 == UNK_VALUE && saveCommonBuf.boxNo == i) {
            filesel_fileWork.selected = i;
        }
        filesel_FileNameRead(i);
        filesel_FileStatRead(i);
    }
}

void filesel_StoryStatRead(s32 fileIndex) {
    u8 first;
    u8 second;

    filesel_fileWork.files[fileIndex].unk_2C = 0;
    filesel_fileWork.files[fileIndex].unk_30 = 0;
    filesel_fileWork.files[fileIndex].unk_34 = 0;
    filesel_fileWork.files[fileIndex].unk_38 = 0;
    filesel_fileWork.files[fileIndex].unk_3C = 99;
    filesel_fileWork.files[fileIndex].unk_40 = 99;
    filesel_fileWork.files[fileIndex].unk_44 = 0;
    filesel_fileWork.files[fileIndex].unk_48 = 0;
    if (_CheckFlag(0x18)) {
        filesel_StoryRead();
        filesel_fileWork.files[fileIndex].unk_2C = GwStory.unk1;
        filesel_fileWork.files[fileIndex].unk_48 = GwStory.unk0;
        filesel_StoryStageBoardGet(GwStory.unk0, &first, &second);
        filesel_fileWork.files[fileIndex].unk_30 = second;
        filesel_fileWork.files[fileIndex].unk_34 = first;
        filesel_fileWork.files[fileIndex].unk_38 = GwSystem.current_turn < 4 ? GwSystem.current_game_length : 3;
        filesel_fileWork.files[fileIndex].unk_3C = GwSystem.current_turn >= 100 ? 99 : (s32)GwSystem.current_turn;
        filesel_fileWork.files[fileIndex].unk_40 = GwSystem.total_turns >= 100 ? 99 : (s32)GwSystem.total_turns;
        filesel_fileWork.files[fileIndex].unk_44 = GwStory.unk2;
    }
}

void filesel_PartyBoardStatRead(s32 fileIndex) {
    filesel_fileWork.files[fileIndex].unk_70 = 0;
    filesel_fileWork.files[fileIndex].unk_74 = 0;
    filesel_fileWork.files[fileIndex].unk_78 = 0;
    filesel_fileWork.files[fileIndex].unk_7C = 0;
    filesel_fileWork.files[fileIndex].unk_80 = 99;
    if (_CheckFlag(0x16)) {
        SLLoadBoard();
        filesel_fileWork.files[fileIndex].unk_68[0] = 0;
        filesel_fileWork.files[fileIndex].unk_68[1] = 1;
        filesel_fileWork.files[fileIndex].unk_68[2] = 2;
        filesel_fileWork.files[fileIndex].unk_68[3] = 3;
        filesel_fileWork.files[fileIndex].unk_70 = (GwSystem.playMode ^ 1) & 1;
        filesel_fileWork.files[fileIndex].unk_74 = GwSystem.current_board_index;
        filesel_fileWork.files[fileIndex].unk_78 = GwSystem.current_turn < 4 ? GwSystem.current_game_length : 3;
        filesel_fileWork.files[fileIndex].unk_7C = GwSystem.current_turn >= 100 ? 99 : (s32)GwSystem.current_turn;
        filesel_fileWork.files[fileIndex].unk_80 = GwSystem.total_turns >= 100 ? 99 : (s32)GwSystem.total_turns;
    }
}

void filesel_StoryBoardStatRead(s32 fileIndex) {
    filesel_fileWork.files[fileIndex].unk_54 = 0;
    filesel_fileWork.files[fileIndex].unk_58 = 0;
    filesel_fileWork.files[fileIndex].unk_5C = 0;
    filesel_fileWork.files[fileIndex].unk_60 = 0;
    filesel_fileWork.files[fileIndex].unk_64 = 99;
    if (_CheckFlag(0x17)) {
        SLLoadBoardStory();
        filesel_fileWork.files[fileIndex].unk_4C[0] = 0;
        filesel_fileWork.files[fileIndex].unk_4C[1] = 1;
        filesel_fileWork.files[fileIndex].unk_4C[2] = 2;
        filesel_fileWork.files[fileIndex].unk_4C[3] = 3;
        filesel_fileWork.files[fileIndex].unk_54 = (((u8)GwSystem.playMode >> 1) ^ 1) & 1;
        filesel_fileWork.files[fileIndex].unk_58 = GwSystem.current_board_index;
        filesel_fileWork.files[fileIndex].unk_5C = GwSystem.current_turn < 4 ? GwSystem.current_game_length : 3;
        filesel_fileWork.files[fileIndex].unk_60 = GwSystem.current_turn >= 100 ? 99 : (s32)GwSystem.current_turn;
        filesel_fileWork.files[fileIndex].unk_64 = GwSystem.total_turns >= 100 ? 99 : (s32)GwSystem.total_turns;
    }
}

void filesel_FileStatRead(s32 fileIndex) {
    s32 i;

    filesel_fileWork.files[fileIndex].unk_04 = GwCommon.unk_00;
    if (filesel_fileWork.files[fileIndex].unk_04 == UNK_VALUE) {
        for (i = 0; i < 10; i += 2) {
            filesel_fileWork.files[fileIndex].name[i] = GwCommon.fileName[i];
            filesel_fileWork.files[fileIndex].name[i + 1] = GwCommon.fileName[i + 1];
        }
        if ((filesel_fileWork.files[fileIndex].name[0] | filesel_fileWork.files[fileIndex].name[1]) == 0) {
            filesel_fileWork.files[fileIndex].unk_04 = 0;
        }
    } else {
        filesel_fileWork.files[fileIndex].name[1] = 0;
        filesel_fileWork.files[fileIndex].name[0] = 0;
    }
    filesel_StoryStatRead(fileIndex);
    filesel_PartyBoardStatRead(fileIndex);
    filesel_StoryBoardStatRead(fileIndex);
}

void filesel_FileNameRead(s32 fileIndex) {
    s32 i;
    s32 mask;

    for (i = 0; i < 16; i++) {
        filesel_fileWork.files[fileIndex].name[i] = 0;
    }
    switch (fileIndex) {
        case 0:
            mask = 1;
            break;
        case 1:
            mask = 2;
            break;
        case 2:
            mask = 4;
            break;
        default:
            mask = 7;
            break;
    }
    filesel_fileWork.files[fileIndex].empty = (SLFormatFlags & mask) != 0;
    if (filesel_fileWork.files[fileIndex].empty != 0) {
        for (i = 0; i < 10; i++) {
            filesel_fileWork.files[fileIndex].name[i] = 0;
        }
    } else {
        for (i = 0; i < 10; i += 2) {
            if ((u16)((GwCommon.fileName[i] << 8) | GwCommon.fileName[i + 1]) == 0) {
                break;
            }
            filesel_fileWork.files[fileIndex].name[i] = GwCommon.fileName[i];
            filesel_fileWork.files[fileIndex].name[i + 1] = GwCommon.fileName[i + 1];
        }
        filesel_fileWork.files[fileIndex].name[i] = filesel_fileWork.files[fileIndex].name[i + 1] = 0;
    }
    if ((u16)((filesel_fileWork.files[fileIndex].name[0] << 8) | filesel_fileWork.files[fileIndex].name[1]) == 0) {
        bzero(filesel_fileWork.files[fileIndex].name, 32);
    }
}

s32 filesel_FileNameSet(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i++) {
        filesel_fileWork.files[arg0].name[i] = arg1[i];
    }

    // terminate string
    filesel_fileWork.files[arg0].name[i] = '\0';
    filesel_fileWork.files[arg0].name[i + 1] = '\0';
    return i;
}

s32 filesel_FileNameGet(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i += 2) {
        if ((u16)((filesel_fileWork.files[arg0].name[i] << 8) | filesel_fileWork.files[arg0].name[i + 1]) == 0) {
            break;
        }
        arg1[i] = filesel_fileWork.files[arg0].name[i];
        arg1[i + 1] = filesel_fileWork.files[arg0].name[i + 1];
    }

    arg1[i] = '\0';
    arg1[i + 1] = '\0';
    return i;
}

void filesel_FileNameSave(s32 arg0) {
    SLCurBoxNoSet(arg0);
    SLLoadGameStat();
    bcopy(filesel_fileWork.files[arg0].name, GwCommon.fileName, 10);
    saveCommonBuf.boxNo = arg0;
    SLCommonSet(1);
}

s32 filesel_NameLenGet(UnkFileName *arg0) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < 10; i += 2) {
        if ((u16)((arg0->unk_00[i] << 8) | arg0->unk_00[i + 1]) == 0) {
            break;
        }
        count++;
    }

    // terminate string
    arg0->unk_00[i + 1] = '\0';
    arg0->unk_00[i] = '\0';
    return count;
}

void filesel_RumbleObjMain(omObjData *arg0) {
    s32 *counter;
    s32 newValue;

    if (filesel_rumbleCnt == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &filesel_rumbleCnt;
    if (*counter < 0xB) {
        newValue = *counter + 1;
    } else {
        newValue = 0;
    }
    *counter = newValue;
}

void filesel_RumbleStart(void) {
    filesel_rumbleCnt = 0;
    omAddObj(6, 0, 0, -1, filesel_RumbleObjMain);
}

void filesel_StoryStageBoardGet(s32 arg0, u8 *arg1, u8 *arg2) {
    *arg1 = filesel_storyStageBoardTbl[0][0];
    *arg2 = filesel_storyStageBoardTbl[0][1];
    if (_CheckFlag(0x18)) {
        if (_CheckFlag(0x28)) {
            *arg1 = filesel_storyStageBoardTbl[arg0][0];
            *arg2 = filesel_storyStageBoardTbl[arg0][1];
        } else {
            *arg1 = filesel_storyStageBoardTbl[arg0 - 1][0];
            *arg2 = filesel_storyStageBoardTbl[arg0 - 1][1];
        }
    }
}

void filesel_StoryRead(void) {
    SLLoadStory();
    if (GwStory.unk0 == 0 && _CheckFlag(0x18)) {
        _SetFlag(0x28);
    }
}
