#include "common.h"

extern s32 mstory1_skipOnF;
extern s32 mstory1_padNo;
extern s32 mstory1_playerOrderTbl[4];
extern void (*const mstory1_sceneCreateTbl[])(void);
extern const s32 mstory1_sceneFlagTbl[];

void mstory1_SceneObjMain(omObjData *obj);
void mstory1_Scene0Create(void);
void mstory1_Scene1Create(void);
void mstory1_Scene2Create(void);
void mstory1_ExitObjMain(omObjData *obj);
void mstory1_BackCreate(void);
void mstory1_CameraObjMain(omObjData *obj);

void mstory1_ObjectSetup(void) {
    omObjData *obj;
    s16 chapter;
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                mstory1_playerOrderTbl[count] = i;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }
    Hu3DSprModelInit(60);
    omInitObjMan(30, 30);
    HuWinInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, mstory1_CameraObjMain);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mstory1_CameraObjMain(obj);
    omAddObj(0, 0, 0, -1, mstory1_SceneObjMain);
    omAddObj(0, 0, 0, -1, mstory1_ExitObjMain);
    mstory1_BackCreate();
    for (mstory1_padNo = 0; mstory1_padNo < 4; mstory1_padNo++) {
        if (CheckControllerRead(mstory1_padNo)) {
            break;
        }
    }
    if (mstory1_padNo >= 4) {
        mstory1_padNo = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 3) {
        chapter = 2;
    }
    mstory1_sceneCreateTbl[chapter]();
    if (_CheckFlag(mstory1_sceneFlagTbl[chapter])) {
        mstory1_skipOnF = 1;
    } else {
        _SetFlag(mstory1_sceneFlagTbl[chapter]);
    }
    WipeCreateIn(WIPE_STARS, 16);
}

void (*const mstory1_sceneCreateTbl[])(void) = { mstory1_Scene0Create, mstory1_Scene1Create, mstory1_Scene2Create };

const s32 mstory1_sceneFlagTbl[] = { 52, 54, 56 };
