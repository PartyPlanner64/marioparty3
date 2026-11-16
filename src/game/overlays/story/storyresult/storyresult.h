#ifndef _STORYRESULT_H
#define _STORYRESULT_H

#include "common.h"
#include "game/overlays/msetup.h"

void storyresult_CameraPresetSet(ModeCameraPreset *preset);
s16 storyresult_StageClearCheck(void);
void storyresult_StageResultProc(void);
void storyresult_FinalResultProc(void);
void storyresult_DebugStatProc(void);

#ifndef NO_EXTERN_VARIABLES
extern u16 storyresult_exitCnt;
extern s16 storyresult_backF;
extern s16 storyresult_musFadeNo;
extern u8 storyresult_pageTbl[];
extern s16 storyresult_padNo;
extern s16 storyresult_exitMode;
extern s16 storyresult_wipeTime;
extern s16 storyresult_wipeType;
extern s16 storyresult_exitEvtNo;
extern s16 storyresult_exitOvlNo;
#endif
extern u8 storySceneNo;

#endif
