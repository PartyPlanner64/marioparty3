#include "common.h"
#include "option.h"
#include "game/overlays/minigame.h"
#include "game/vibrator.h"
#include "game/mallocblock.h"
#include "game/pad.h"
#include "game/saveload.h"

// One entry per on-screen cursor; the object is the 3D cursor for that slot.
typedef struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *obj;
} OptCursor; // sizeof 0x2C

// Object that keeps an attached 3d model sound playing for a fixed duration.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 seNo;
} OptSeObj; // sizeof 0x8

typedef struct {
    s32 message;
    s16 sound;
} OptSoundEntry;

typedef struct {
    s32 title;
    OptSoundEntry entries[9];
} OptSoundPage;

typedef struct {
    OptSoundPage pages[15];
} OptSoundMenu;

typedef struct {
    OptSoundPage pages[12];
} OptMusicMenu;

// Window rectangle for a line of the board record pages, relative to the top left of the page.
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 w;
    /* 0x0C */ f32 h;
} OptRecordWinRect; // sizeof 0x10

extern const OptSoundMenu option_soundTestTbl;
extern const OptMusicMenu option_musicTestTbl;
extern OptSprSlot option_animTbl[0x40];
extern OptSpr option_sprTbl[0x40];
extern UnkOption option_modelTbl[0x40];
extern s16 option_bgAnim;
extern u16 option_bgSpr;
extern OptWinEntry option_winTbl[0x20];
extern SaveCommonBuf saveCommonBuf;
extern s32 option_stickBtn;

s32 option_PadBtnRepGet(s32 arg0);
s32 option_SeObjCheck(void);
s32 option_MgTypeUnlockCheck(void);
void option_SeObjKill(void);
omObjData *option_SeObjCreate(s32);

void option_PartyRecordExec(s32 animFile, s16 x, s16 y);
void option_DuelRecordExec(s32 animFile, s16 x, s16 y);
void option_MgRecordExec(s32 animFile, s16 x, s16 y);
s32 option_RecordRoomDecide(s32, s32);
void option_MenuWinCreate(s32, u32);
void option_MenuSprPosGet(s32, s32 *, s32 *);
void option_MenuMdlDispOn(s32);
void option_MenuMdlDispOff(s32);
void option_MenuWinMesWait(s32);
void option_MenuWinDispOn(s32);
s32 option_StickBtnGet(s32);
s32 option_RoomDecide(s32, s32);
s32 option_RoomMove(s32, s32);
void option_RoomCursorSet(s32, s32);
void option_ScreenPosGet(f32, f32, f32, s32 *, s32 *);
omObjData *option_CameraTurnMove(Vec *, Vec *, s32);
void option_MenuWinKill(s32);
void option_ScreenPosCalc(Vec *, Vec *, Vec *, f32, Vec *, f32 *, f32 *);
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
void option_CameraManualStart(f32 fov);
void option_CameraMoveKill(void);
omObjData *option_CameraTurnEaseMove(Vec *pos, Vec *at, s32 duration);
void option_MenuMdlPosGet(s32, f32 *, f32 *, f32 *);
void option_MenuMdlRotSet(s32, f32, f32, f32);
omObjData *option_CameraMove(Vec *, Vec *, s32);
void option_WorkInit(void);
void option_RoomProc(void);
s32 option_RoomChoice(void);
void option_RoomInit(void);
void option_LookAtCreate(s32, s32);
void option_LookAtKillAll(void);
void option_RoomClose(void);
void option_SoundRoomProc(void);
void option_RecordRoomProc(void);
void option_LookAtInit(void);
void option_SeObjInit(void);
void option_MenuInit(void);
void option_RoomCreate(void);
void option_SoundRoomCreate(void);
void option_RecordRoomCreate(void);
void option_SprPosSet(s32, s32, s32);
void option_SprInit(void);
void option_ModelInit(void);
void option_WinInit(void);
void option_MotionCreate(s32, s32, s32);
void option_WinCreate(s32, u32, s16, s16, u16, u16, s16);
void option_WinKill(s32);
void option_WinMesSet(s32, u32);
void option_MenuSprPosSet(s32, s32, s32);
void option_CursorSprKill(void);
s32 option_MenuMdlIdGet(s32);
omObjData *option_CameraEaseMove(Vec *, Vec *, s32);
void option_MenuMotShiftSet(s32, s32, s16, s16, u16);
void option_MenuSprDispOn(s32);
void option_MenuSprDispOff(s32);
void option_MenuWinMesSet(s32, u32);
void option_MenuWinDispOff(s32);
s32 option_SoundRoomDecide(s32, s32);
s32 option_SoundRoomMove(s32, s32);
void option_SoundRoomCursorUpdate(s32, s32);
s32 option_MenuWinChoiceGet(s32);
void option_SoundRoomInit(void);
void option_MenuMotEndWait(s32);
void option_SoundRoomClose(void);
void option_RecordRoomInit(void);
void option_RecordRoomClose(void);
void option_RumbleStart(void);
void option_SoundTestExec(void);
void option_MusicTestExec(void);

Vec option_unusedCameraTbl0[2] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
}; /* Unreferenced. */
Vec option_roomCameraBackTbl[2] = {
    { 0.0f, 250.0f, 350.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec option_unusedCameraTbl1[4][2] = {
    { { 0.0f, 271.19f, 350.0f }, { 0.0f, 228.72f, -550.0f } },
    { { 0.0f, 271.19f, 350.0f }, { -535.0f, 228.72f, -550.0f } },
    { { 0.0f, 271.19f, 350.0f }, { 535.0f, 228.72f, -550.0f } },
    { { 0.0f, 250.0f, -400.0f }, { 0.0f, 228.72f, 1275.0f } },
}; /* Unreferenced. */
Vec option_soundRoomCameraTbl[6][2] = {
    { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.59999f, 61.300003f } },
    { { 0.0f, 224.46501f, -293.5f }, { 0.0f, 123.75f, -61.300003f } },
    { { 0.0f, 224.46501f, 364.27f }, { -242.5f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, 364.27f }, { 240.0f, 123.75f, -358.5f } },
    { { 0.0f, 224.46501f, -293.5f }, { -265.7f, 105.85f, 725.0f } },
    { { 0.0f, 224.46501f, -293.5f }, { 265.7f, 105.85f, 725.0f } },
};
Vec option_unusedCameraPosTbl[9] = {
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 184.59999f, -61.300003f },
    { 0.0f, 123.75f, -640.0f },
    { -242.5f, 201.0f, -358.5f },
    { 535.0f, 228.72f, -550.0f },
    { -265.7f, 105.85f, 725.0f },
    { 265.7f, 105.85f, 725.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 200.0f, -220.0f },
}; /* Unreferenced. */
Vec option_recordRoomCameraLTbl[2] = {
    { 0.0f, 225.0f, 0.0f },
    { -75.0f, 200.0f, -680.0f },
};
Vec option_recordRoomCameraRTbl[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 75.0f, 200.0f, -680.0f },
};
Vec option_recordRoomCameraExitTbl[2] = {
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 225.0f, 475.0f },
};
Vec option_unusedCursorPosTbl[4] = {
    { 0.0f, 170.0f, -7.64f },
    { -195.0f, -165.0f, -220.0f },
    { 195.0f, 165.0f, -220.0f },
    { -50.0f, 0.0f, 475.0f },
}; /* Unreferenced. */
Vec option_roomRecordDoorPos = { 0.0f, 410.0f, -450.0f };
Vec option_roomRecordDoorAt = { 0.0f, 410.0f, -550.0f };
Vec option_roomDoorLPos = { -535.0f, 88.70001f, -450.0f };
Vec option_roomDoorLAt = { -535.0f, 88.70001f, -550.0f };
Vec option_roomDoorRPos = { 535.0f, 88.70001f, -450.0f };
Vec option_roomDoorRAt = { 535.0f, 88.70001f, -550.0f };
Vec option_roomExitPos = { 0.0f, 128.70001f, 1175.0f };
Vec option_roomExitAt = { 0.0f, 128.70001f, 1275.0f };
Vec option_unusedCameraTbl2[2] = {
    { 0.0f, 93.70001f, -450.0f },
    { 0.0f, 93.70001f, -525.0f },
}; /* Unreferenced. */
Vec option_roomCursorPosTbl[4] = {
    { 0.0f, 430.0f, -550.0f },
    { -535.0f, 100.0f, -550.0f },
    { 535.0f, 100.0f, -550.0f },
    { 0.0f, 100.0f, 1275.0f },
};
Vec option_roomCameraCTbl[2] = {
    { 0.0f, 271.19f, 350.0f },
    { 0.0f, 228.72f, -550.0f },
};
Vec option_roomCameraExitTbl[2] = {
    { 0.0f, 250.0f, 350.0f },
    { 0.0f, 228.72f, 1275.0f },
};
Vec option_roomCameraLTbl[2] = {
    { 0.0f, 228.72f, 350.0f },
    { -535.0f, 228.72f, -550.0f },
};
Vec option_roomCameraRTbl[2] = {
    { 0.0f, 228.72f, 350.0f },
    { 535.0f, 228.72f, -550.0f },
};
Vec option_soundRoomExitLPos = { -265.7f, 105.85f, 625.0f };
Vec option_soundRoomExitLAt = { -265.7f, 105.85f, 725.0f };
Vec option_soundRoomExitRPos = { 265.7f, 105.85f, 625.0f };
Vec option_soundRoomExitRAt = { 265.7f, 105.85f, 725.0f };
Vec option_soundTestCameraTbl[2] = {
    { -228.75f, 123.75f, 41.500015f },
    { -323.75f, 98.75f, -358.5f },
};
Vec option_soundTestBackCameraTbl[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { -242.5f, 123.75f, -358.5f },
};
Vec option_musicTestCameraTbl[2] = {
    { 228.75f, 123.75f, 41.500015f },
    { 323.75f, 98.75f, -358.5f },
};
Vec option_musicTestBackCameraTbl[2] = {
    { 0.0f, 224.46501f, 364.27f },
    { 242.5f, 123.75f, -358.5f },
};
Vec option_recordRoomCursorLPos = { -195.0f, 165.0f, -695.0f };
Vec option_recordRoomCursorRPos = { 195.0f, 165.0f, -695.0f };
Vec option_recordRoomCursorExitPos = { -50.0f, 225.0f, 475.0f };
Vec option_recordRoomExitPos = { 0.0f, 225.0f, 275.0f };
Vec option_recordRoomExitAt = { 0.0f, 225.0f, 575.0f };
s32 option_partyRecordChrTbl[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OptRecordWinRect option_partyRecordWinTbl[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};
s32 option_duelRecordChrTbl[9] = { 0, 1, 2, 3, 4, 5, 7, 6, 8 };
OptRecordWinRect option_duelRecordWinTbl[6] = {
    { 0.0f, 0.0f, 213.0f, 20.0f },
    { 0.0f, 19.0f, 213.0f, 20.0f },
    { 0.0f, 34.0f, 213.0f, 20.0f },
    { 0.0f, 53.0f, 213.0f, 20.0f },
    { 0.0f, 105.0f, 213.0f, 20.0f },
    { 0.0f, 120.0f, 213.0f, 20.0f },
};

Process *option_roomProc BSS;
u8 option_roomProcPad[4] BSS; /* Unreferenced. */
s32 option_cursorWork[4] BSS;
OptCursor option_lookAtTbl[2] BSS;
OptSeObj option_seWork BSS;
s32 option_rumbleCnt BSS;

void option_MgRecordExec(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    u8 text0[32];
    u8 text1[32];
    u8 text2[32];
    u8 records[10] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 };
    s8 minigames[10] = { 13, 16, 35, 52, 44, 71, 71, 71, 0, -1 };
    s32 messages[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 anim;
    u16 sprite;
    s16 win;
    s16 i;
    s16 j;
    s16 record;
    s32 offsetY;
    f32 scale;

    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        offsetY = i * 14 - 71;
        wins[i] = HuWinExCreate(-1, x - 104, y + offsetY, 213, 20, 0);
        HuWinBGTPLvlSet(wins[i], 0);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        record = GWMgRecordGet(records[i]);
        if (record < 0) {
            record = 0;
        }
        switch (records[i]) {
            case 0:
                sprintf((char *)text0, "%3d", record);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
                sprintf((char *)text0, "%d", record / 3600);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                record %= 3600;
                sprintf((char *)text1, "%2d", record / 60);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                sprintf((char *)text2, "%2d", (s16)((record % 60) / 60.0f * 100.0f));
                if (text2[0] == ' ') {
                    text2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text2, 2);
                break;
            case 4:
                sprintf((char *)text0, "%3d", record / 100);
                record %= 100;
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                sprintf((char *)text1, "%2d", record);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                break;
            case 3:
            case 9:
                sprintf((char *)text0, "%d", record / 1800);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                record %= 1800;
                sprintf((char *)text1, "%2d", record / 30);
                if (text1[0] == ' ') {
                    text1[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text1, 1);
                sprintf((char *)text2, "%2d", (s16)((record % 30) * (1.0f / 30.0f) * 99.0f));
                if (text2[0] == ' ') {
                    text2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)text2, 2);
                break;
            case 8:
                sprintf((char *)text0, "%4d", record);
                HuWinInsertMesSet(wins[i], (u32)text0, 0);
                break;
        }
        HuWinDispOn(wins[i]);
        record = minigames[i];
        record--;
        if (record == 70 && _CheckFlag(0x2B)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record >= 0 && GWMgUnlockCheck(record)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record == -1 && _CheckFlag(0x1E)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else if (record == -2 && _CheckFlag(0x1F)) {
            HuWinMesSet(wins[i], messages[i], -1, -1);
        } else {
            HuWinMesSet(wins[i], 0x4500, -1, -1);
        }
        HuWinPosSet(win, x, y + (s16)(i * 14 - 62));
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    HuWinKill(win);
    do {
        HuPrcVSleep();
    } while (!(HuPadBtnDown[0] & (A_BUTTON | B_BUTTON)));
    for (i = 0; i < 10; i++) {
        HuWinDispOff(wins[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        HuWinKill(wins[i]);
    }
    espKill(sprite);
    HuSprAnimKill(anim);
}

void option_RoomCreate(void) {
    option_WorkInit();
    option_MenuInit();
    option_roomProc = omAddPrcObj(option_RoomProc, 0x5000, 0x2000, 0);
}

void option_SoundRoomCreate(void) {
    option_WorkInit();
    option_MenuInit();
    option_roomProc = omAddPrcObj(option_SoundRoomProc, 0x5000, 0x2000, 0);
}

void option_RecordRoomCreate(void) {
    option_WorkInit();
    option_MenuInit();
    option_roomProc = omAddPrcObj(option_RecordRoomProc, 0x5000, 0x2000, 0);
}

void option_WorkInit(void) {
    option_LookAtInit();
    option_SeObjInit();
}

const Vec option_roomStartPos = { 0.0f, 271.19f, 1191.11f };

const Vec option_roomCenterAt = { 0.0f, 228.72f, -550.0f };

const Vec option_cameraUp = { 0.0f, 1.0f, 0.0f };

const Vec option_roomCenterPos = { 0.0f, 271.19f, 350.0f };

const Vec option_roomFromLPos = { -535.0f, 228.72f, -550.0f };

const Vec option_roomFromAt = { 0.0f, 228.72f, 350.0f };

const Vec option_roomFromLTurnPos = { -160.0f, 228.72f, 50.0f };

const Vec option_roomFromLTurnAt = { 450.0f, 228.72f, 1191.11f };

const Vec option_roomFromRPos = { 535.0f, 228.72f, -550.0f };

const Vec option_roomFromRTurnPos = { 160.0f, 228.72f, 50.0f };

const Vec option_roomFromRTurnAt = { -450.0f, 228.72f, 1191.11f };

const Vec option_roomFromRecordPos = { 0.0f, 410.0f, -550.0f };

const Vec option_roomFromRecordMovePos = { 0.0f, 228.72f, 50.0f };

const Vec option_roomFromRecordTurnAt = { 0.0f, 228.72f, 1191.11f };

void option_RoomProc(void) {
    s32 selection;
    s32 active = 1;
    Vec pos, at;

    Hu3DBGColorSet(0, 0x40, 0x40);
    option_RoomInit();
    option_LookAtCreate(0, 9);
    option_LookAtCreate(1, 10);
    switch (omovlevtno) {
        case 0:
            HuAudSubSeqPlay(7);
            WipeCreateIn(11, 16);
            pos = option_roomStartPos;
            at = option_roomCenterAt;
            {
                Vec up = option_cameraUp;
                option_CameraPosSet(&pos, &at, &up);
            }
            {
                Vec pos = option_roomCenterPos;
                Vec at = option_roomCenterAt;
                option_CameraEaseMove(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 1:
            HuAudSubSeqPlay(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = option_roomFromLPos;
                Vec at = option_roomFromAt;
                Vec up = option_cameraUp;
                option_CameraPosSet(&pos, &at, &up);
            }
            {
                Vec pos = option_roomFromLTurnPos;
                Vec at = option_roomFromLTurnAt;
                option_CameraTurnEaseMove(&pos, &at, 46);
            }
            HuPrcSleep(46);
            {
                Vec pos = option_roomCenterPos;
                Vec at = option_roomCenterAt;
                option_CameraTurnMove(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 2:
            HuAudSubSeqPlay(7);
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = option_roomFromRPos;
                Vec at = option_roomFromAt;
                Vec up = option_cameraUp;
                option_CameraPosSet(&pos, &at, &up);
            }
            {
                Vec pos = option_roomFromRTurnPos;
                Vec at = option_roomFromRTurnAt;
                option_CameraTurnEaseMove(&pos, &at, 46);
            }
            HuPrcSleep(46);
            {
                Vec pos = option_roomCenterPos;
                Vec at = option_roomCenterAt;
                option_CameraTurnMove(&pos, &at, 45);
            }
            HuPrcSleep(45);
            break;
        case 3:
            WipeColorSet(255, 255, 255);
            WipeCreateIn(11, 16);
            {
                Vec pos = option_roomFromRecordPos;
                Vec at = option_roomFromAt;
                Vec up = option_cameraUp;
                option_CameraPosSet(&pos, &at, &up);
            }
            {
                Vec pos = option_roomFromRecordMovePos;
                Vec at = option_roomFromAt;
                option_CameraMove(&pos, &at, 50);
            }
            HuPrcSleep(50);
            {
                Vec pos = option_roomFromAt;
                Vec at = option_roomFromRecordTurnAt;
                option_CameraEaseMove(&pos, &at, 25);
            }
            HuPrcSleep(25);
            {
                Vec pos = option_roomFromAt;
                Vec at = option_roomCenterAt;
                option_CameraTurnMove(&pos, &at, 35);
            }
            HuPrcSleep(35);
            break;
        default:
            HuAudSubSeqPlay(7);
            WipeCreateIn(11, 16);
            {
                Vec pos = option_roomStartPos;
                Vec at = option_roomCenterAt;
                option_CameraTurnMove(&pos, &at, 45);
            }
            HuPrcSleep(16);
            break;
    }
    selection = option_RoomChoice();
    option_MenuSprDispOff(0);
    switch (selection) {
        case 0:
            HuVecCopy3F(&pos, &option_roomRecordDoorPos);
            pos.y += 20.0f;
            HuVecCopy3F(&at, &option_roomRecordDoorAt);
            at.y += 20.0f;
            HuAudFXPlay(0x2EB);
            option_MenuMotFlagSet(0, 0);
            option_MenuMotTimeSet(0, 0);
            option_MenuMotEndWait(0);
            option_CameraMove(&pos, &at, 20);
            option_RumbleStart();
            WipeCreateOut(11, 20);
            HuPrcSleep(20);
            break;
        case 1:
            HuVecCopy3F(&pos, &option_roomDoorLPos);
            pos.z += 200.0f;
            HuVecCopy3F(&at, &option_roomDoorLAt);
            option_MenuMotShiftSet(9, 12, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            option_MenuMotSet(0, 6, 0);
            option_MenuMotEndWait(0);
            pos.z -= 200.0f;
            at.z -= 200.0f;
            option_CameraMove(&pos, &at, 20);
            option_RumbleStart();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 2:
            HuVecCopy3F(&pos, &option_roomDoorRPos);
            pos.z += 200.0f;
            HuVecCopy3F(&at, &option_roomDoorRAt);
            option_MenuMotShiftSet(10, 11, 0, 8, 0);
            HuAudFXPlay(0x2EB);
            option_MenuMotSet(0, 7, 0);
            option_MenuMotTimeSet(0, 0);
            option_MenuMotEndWait(0);
            pos.z -= 200.0f;
            at.z -= 200.0f;
            option_CameraMove(&pos, &at, 20);
            option_RumbleStart();
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 3:
        case 4:
            HuVecCopy3F(&pos, &option_roomExitPos);
            HuVecCopy3F(&at, &option_roomExitAt);
            option_CameraMove(&pos, &at, 30);
            HuPrcSleep(20);
            option_CameraMoveKill();
            HuAudFXPlay(0x2E1);
            option_MenuMotFlagSet(1, 0);
            option_MenuMotTimeSet(1, 0);
            option_MenuMotEndWait(1);
            option_CameraMove(&pos, &at, 20);
            option_RumbleStart();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    active = selection;
    option_LookAtKillAll();
    option_RoomClose();
    HuWinAllKill();
    omOvlKill();
    switch (active) {
        case 0:
            omOvlHisChg(0, 0x7B, 3, 0x91);
            omOvlCallEx(0x7B, 6, 0x91);
            break;
        case 1:
            omOvlGotoEx(0x7B, 4, 0x91);
            break;
        case 2:
            omOvlGotoEx(0x7B, 5, 0x91);
            break;
        case 3:
            omOvlReturnEx(1);
            omOvlHisChg(0, 0x77, 3, 0x91);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(option_roomProc);
    while (1) {
        HuPrcVSleep();
    }
}

s32 option_RoomChoice(void) {
    s32 selection = 0;
    s32 buttons;
    s32 result;
    Vec at;
    s32 x, y;

    if (ModeSelIntroShownGet()) {
        ModeSelIntroShownSet(1);
        option_MenuWinCreate(0, 0x4E00);
        option_MenuWinMesWait(0);
        option_MenuWinMesSet(0, 0x4E02);
    } else {
        option_MenuWinCreate(0, 0x4E02);
    }
    option_MenuSprDispOn(0);
    option_RoomCursorSet(selection, 0);
    while (1) {
        buttons = HuPadBtnDown[0];
        buttons |= option_StickBtnGet(0);
        if (buttons & 0x8000) {
            result = option_RoomDecide(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = option_RoomMove(selection, buttons);
        } else if (buttons & 0x4000) {
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            switch (selection) {
                case 0:
                case 1:
                    HuVecCopy3F(&at, &option_roomCameraBackTbl[1]);
                    option_CameraTurnMove(&option_roomCameraBackTbl[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 2:
                    HuVecCopy3F(&at, &option_roomCameraBackTbl[1]);
                    option_CameraTurnMove(&option_roomCameraBackTbl[0], &at, 30);
                    HuPrcSleep(30);
                    break;
                case 9:
                default:
                    break;
            }
            selection = 3;
            option_ScreenPosGet(0.0f, 100.0f, 1275.0f, &x, &y);
            option_MenuSprPosSet(0, x, y);
            option_MenuWinDispOn(0);
            option_MenuWinMesSet(0, 0x4E03);
            option_MenuSprDispOn(0);
        }
        HuPrcVSleep();
    }
    option_MenuWinKill(0);
    return selection;
}

void option_CursorPosSet(s32 arg0, s32 arg1, s32 arg2) {
    option_cursorWork[0] = arg1;
    option_cursorWork[1] = arg2;
    option_MenuSprPosSet(arg0, 160, arg2);
}

void option_CursorUpdate(s32 arg0) {
    if (++option_cursorWork[3] >= 21) {
        option_cursorWork[3] = 0;
    }
    option_cursorWork[2] = 0;
    option_MenuSprPosSet(arg0, option_cursorWork[0], option_cursorWork[1]);
}

void option_ScreenPosCalc(Vec *pos, Vec *at, Vec *up, f32 fov, Vec *point, f32 *screenX, f32 *screenY) {
    f32 mtx[4][4];
    f32 dx, dy, dz;
    f32 x, y, z;

    HuLookAtF(mtx, pos->x, pos->y, pos->z, at->x, at->y, at->z, up->x, up->y, up->z);
    dx = point->x;
    dy = point->y;
    dz = point->z;
    dx -= pos->x;
    dy -= pos->y;
    dz -= pos->z;
    x = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    y = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    z = dx * mtx[0][2] + dy * mtx[1][2] + dz * mtx[2][2];
    fov /= 2.0f;
    dx = sindf(fov) / cosdf(fov) * z * (4.0f / 3.0f);
    dy = sindf(fov) / cosdf(fov) * z;
    x = x * (160.0f / -dx) + 160.0f;
    *screenX = x;
    y = y * (120.0f / dy) + 120.0f;
    *screenY = y;
}

void option_ScreenPosGet(f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;
    HuCamera *camera;

    camera = gCameraList;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    option_ScreenPosCalc(&camera->pos, &camera->at, &camera->up, camera->fov, &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void option_ScreenPosGetEx(Vec *camPos, Vec *camAt, Vec *camUp, f32 x, f32 y, f32 z, s32 *screenX, s32 *screenY) {
    Vec pos;
    f32 px, py;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    option_ScreenPosCalc(camPos, camAt, camUp, gCameraList->fov, &pos, &px, &py);
    *screenX = px;
    *screenY = py;
}

void option_SprPosMoveV(s32 slot, Vec *start, Vec *end, s32 duration) {
    f32 startPos[2], endPos[2];
    s32 x, y;
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        option_ScreenPosGet(start->x, start->y, start->z, &x, &y);
        startPos[0] = x;
        startPos[1] = y;
        option_ScreenPosGet(end->x, end->y, end->z, &x, &y);
        endPos[0] = x;
        endPos[1] = y;
        t = (1.0f / duration) * i;
        option_MenuSprPosSet(slot, t * (endPos[0] - startPos[0]) + startPos[0], t * (endPos[1] - startPos[1]) + startPos[1]);
        HuPrcVSleep();
    }
    option_MenuSprPosSet(slot, endPos[0], endPos[1]);
}

void option_SprPosMove(s32 index, s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    f32 t;

    for (i = 0; i <= duration; i++) {
        t = (1.0f / duration) * i;
        option_MenuSprPosSet(index, startX + t * (endX - startX), startY + t * (endY - startY));
        HuPrcVSleep();
    }
    option_MenuSprPosSet(index, endX, endY);
}

void option_RoomCursorPosGet(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            val1 = 0xA0;
            val2 = 0x50;
            break;
        case 1:
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
        case 4:
            val1 = 0xA0;
            val2 = 0x6E;
            break;
        case 5:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

const Vec option_roomRecordDoorMovePos = { 0.0f, 430.0f, -150.0f };

const Vec option_roomRecordDoorMoveAt = { 0.0f, 430.0f, -550.0f };

const Vec option_roomDoorLMovePos = { -535.0f, 128.72f, -150.0f };

const Vec option_roomDoorLMoveAt = { -535.0f, 78.72f, -550.0f };

const Vec option_roomDoorRMovePos = { 535.0f, 128.72f, -150.0f };

const Vec option_roomDoorRMoveAt = { 535.0f, 78.72f, -550.0f };

s32 option_RoomDecide(s32 selection, s32 buttons) {
    switch (selection) {
        case 0: {
            Vec pos;
            Vec at;
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            pos = option_roomRecordDoorMovePos;
            at = option_roomRecordDoorMoveAt;
            option_CameraEaseMove(&pos, &at, 30);
            option_MenuMotShiftSet(9, 11, 0, 8, 0);
            option_MenuMotShiftSet(10, 12, 0, 8, 0);
            HuPrcSleep(30);
            break;
        }
        case 1: {
            Vec pos;
            Vec at;
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            pos = option_roomDoorLMovePos;
            at = option_roomDoorLMoveAt;
            option_CameraEaseMove(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 2: {
            Vec pos;
            Vec at;
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            pos = option_roomDoorRMovePos;
            at = option_roomDoorRMoveAt;
            option_CameraEaseMove(&pos, &at, 20);
            HuPrcSleep(20);
            break;
        }
        case 3:
            option_MenuSprDispOff(0);
            option_MenuWinMesSet(0, 0x4E04);
            if (option_MenuWinChoiceGet(0)) {
                option_MenuWinMesSet(0, 0x4E03);
                option_MenuSprDispOn(0);
                return -1;
            }
            selection = 3;
            break;
        case 9:
        default:
            break;
    }
    return selection;
}

s32 option_RoomMove(s32 selection, s32 buttons) {
    Vec up;
    s32 x, y, endX, endY;

    up = option_cameraUp;

    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
                option_CameraTurnMove(&option_roomCameraLTbl[0], &option_roomCameraLTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_roomCameraLTbl[0], &option_roomCameraLTbl[1], &up, option_roomCursorPosTbl[1].x, option_roomCursorPosTbl[1].y, option_roomCursorPosTbl[1].z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 2;
                option_CameraTurnMove(&option_roomCameraRTbl[0], &option_roomCameraRTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_roomCameraRTbl[0], &option_roomCameraRTbl[1], &up, option_roomCursorPosTbl[2].x, option_roomCursorPosTbl[2].y, option_roomCursorPosTbl[2].z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e01);
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                option_CameraTurnMove(&option_roomCameraExitTbl[0], &option_roomCameraExitTbl[1], 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(20);
                option_ScreenPosGet(option_roomCursorPosTbl[3].x, option_roomCursorPosTbl[3].y, option_roomCursorPosTbl[3].z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuMdlDispOff(0);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e03);
            } else if (buttons & 0x100) {
                selection = 0;
                option_CameraTurnMove(&option_roomCameraCTbl[0], &option_roomCameraCTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_roomCameraCTbl[0], &option_roomCameraCTbl[1], &up, option_roomCursorPosTbl[0].x, option_roomCursorPosTbl[0].y, option_roomCursorPosTbl[0].z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e02);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 0;
                option_CameraTurnMove(&option_roomCameraCTbl[0], &option_roomCameraCTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_roomCameraCTbl[0], &option_roomCameraCTbl[1], &up, option_roomCursorPosTbl[0].x, option_roomCursorPosTbl[0].y, option_roomCursorPosTbl[0].z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e02);
            } else if (buttons & 0x100) {
                selection = 3;
                option_CameraTurnMove(&option_roomCameraExitTbl[0], &option_roomCameraExitTbl[1], 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(20);
                option_ScreenPosGet(option_roomCursorPosTbl[3].x, option_roomCursorPosTbl[3].y, option_roomCursorPosTbl[3].z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuMdlDispOff(0);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e03);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                option_CameraTurnMove(&option_roomCameraRTbl[0], &option_roomCameraRTbl[1], 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuMdlDispOn(0);
                HuPrcSleep(20);
                option_ScreenPosGet(option_roomCursorPosTbl[2].x, option_roomCursorPosTbl[2].y, option_roomCursorPosTbl[2].z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e01);
            } else if (buttons & 0x100) {
                selection = 1;
                option_CameraTurnMove(&option_roomCameraLTbl[0], &option_roomCameraLTbl[1], 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuMdlDispOn(0);
                HuPrcSleep(20);
                option_ScreenPosGet(option_roomCursorPosTbl[1].x, option_roomCursorPosTbl[1].y, option_roomCursorPosTbl[1].z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e01);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

void option_RoomCursorSet(s32 selection, s32 arg1) {
    s32 index = 0;
    s32 x, y;

    switch (selection) {
        case 0:
            index = 0;
            break;
        case 1:
            index = 1;
            break;
        case 2:
            index = 2;
            break;
        case 3:
            index = 3;
            break;
    }
    option_ScreenPosGet(option_roomCursorPosTbl[index].x, option_roomCursorPosTbl[index].y, option_roomCursorPosTbl[index].z, &x, &y);
    option_MenuSprPosSet(0, x, y);
}

s32 option_SoundRoomChoice(void) {
    Vec pos, at;
    s32 selection = 0;
    s32 buttons;
    s32 result;

    option_CameraManualStart(41.539f);
    option_MenuWinCreate(0, 0x4E05);
    option_MenuWinMesWait(0);
    option_MenuWinMesSet(0, 0x4E06);
    option_MenuSprDispOn(0);
    option_SoundRoomCursorUpdate(0, 0);
    while (1) {
        buttons = HuPadBtnDown[0];
        buttons |= option_StickBtnGet(0);
        if (buttons & 0x8000) {
            result = option_SoundRoomDecide(selection, buttons);
            if (result != -1) {
                selection = result;
                break;
            }
        } else if (buttons & 0xF00) {
            selection = option_SoundRoomMove(selection, buttons);
        } else if (buttons & 0x4000) {
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            switch (selection) {
                case 0:
                case 1:
                case 2:
                    selection = 4;
                    HuVecCopy3F(&pos, &option_soundRoomCameraTbl[4][0]);
                    HuVecCopy3F(&at, &option_soundRoomCameraTbl[4][1]);
                    option_CameraTurnMove(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 3:
                    selection = 5;
                    HuVecCopy3F(&pos, &option_soundRoomCameraTbl[5][0]);
                    HuVecCopy3F(&at, &option_soundRoomCameraTbl[5][1]);
                    option_CameraTurnMove(&pos, &at, 20);
                    HuPrcSleep(20);
                    break;
                case 4:
                case 5:
                default:
                    break;
            }
            option_MenuWinDispOn(0);
            option_MenuWinMesSet(0, 0x4E0B);
            option_MenuSprDispOn(0);
        }
        option_SoundRoomCursorUpdate(selection, buttons);
        HuPrcVSleep();
    }
    option_MenuWinKill(0);
    return selection;
}

void option_SoundRoomProc(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    Hu3DBGColorSet(0, 64, 64);
    option_SoundRoomInit();
    HuAudSeqPlay(0x4A);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = option_SoundRoomChoice();
    option_MenuSprDispOff(0);
    switch (selection) {
        case 4:
            HuVecCopy3F(&pos, &option_soundRoomExitLPos);
            HuVecCopy3F(&at, &option_soundRoomExitLAt);
            pos.z -= 200.0f;
            option_CameraMove(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            option_MenuMotFlagSet(1, 0);
            option_MenuMotTimeSet(1, 0);
            option_MenuMotEndWait(1);
            pos.z += 200.0f;
            option_CameraMove(&pos, &at, 20);
            goto fadeOut;
        case 5:
            HuVecCopy3F(&pos, &option_soundRoomExitRPos);
            HuVecCopy3F(&at, &option_soundRoomExitRAt);
            pos.z -= 200.0f;
            option_CameraMove(&pos, &at, 20);
            HuPrcSleep(20);
            HuAudFXPlay(0x2EB);
            option_MenuMotFlagSet(1, 0);
            option_MenuMotSet(1, 12, 0);
            option_MenuMotTimeSet(1, 0);
            option_MenuMotEndWait(1);
            pos.z += 200.0f;
            option_CameraMove(&pos, &at, 20);
        case 0:
        case 1:
        case 2:
        case 3:
        fadeOut:
            result = selection;
            option_RumbleStart();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            HuAudSeqFadeOut(20);
            HuPrcSleep(20);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    option_SoundRoomClose();
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 4:
            omOvlGotoEx(0x7B, 1, 0x91);
            break;
        case 5:
            omOvlGotoEx(0x7B, 2, 0x91);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(option_roomProc);
    while (1) {
        HuPrcVSleep();
    }
}

void option_SoundRoomCursorPosGet(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            if (!(saveCommonBuf.flags & 1)) {
                val1 = 0xE0;
                val2 = 0x38;
            } else {
                val1 = 0xB8;
                val2 = 0x38;
            }
            break;
        case 1:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 4:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 5:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 6:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

s32 option_SoundRoomMove(s32 selection, s32 buttons) {
    Vec pos, at;
    Vec(*camera)[2];
    s32 x, y, endX, endY;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 2;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuMdlDispOff(6);
                option_MenuMdlDispOff(7);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(2, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E0A);
            } else if (buttons & 0x100) {
                selection = 3;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuMdlDispOff(6);
                option_MenuMdlDispOff(7);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(3, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E09);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 4;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                option_CameraTurnMove(&pos, &at, 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(4, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 0;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(0, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E06);
                option_MenuMdlDispOn(6);
                option_MenuMdlDispOn(7);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 0;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[0][0]);
                HuVecCopy3F(&at, &camera[0][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(0, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E06);
                option_MenuMdlDispOn(6);
                option_MenuMdlDispOn(7);
            } else if (buttons & 0x100) {
                selection = 5;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                option_CameraTurnMove(&pos, &at, 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(5, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4E0B);
            }
            break;
        case 4:
            if (buttons & 0x200) {
                selection = 5;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[5][0]);
                HuVecCopy3F(&at, &camera[5][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(5, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E0B);
            } else if (buttons & 0x100) {
                selection = 2;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[2][0]);
                HuVecCopy3F(&at, &camera[2][1]);
                option_CameraTurnMove(&pos, &at, 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(2, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4E0A);
            }
            break;
        case 5:
            if (buttons & 0x200) {
                selection = 3;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[3][0]);
                HuVecCopy3F(&at, &camera[3][1]);
                option_CameraTurnMove(&pos, &at, 20);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(3, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 20);
                HuPrcSleep(12);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4E09);
            } else if (buttons & 0x100) {
                selection = 4;
                camera = option_soundRoomCameraTbl;
                HuVecCopy3F(&pos, &camera[4][0]);
                HuVecCopy3F(&at, &camera[4][1]);
                option_CameraTurnMove(&pos, &at, 8);
                option_MenuSprPosGet(0, &x, &y);
                option_SoundRoomCursorPosGet(4, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 8);
                option_MenuWinMesSet(0, 0x4E0B);
            }
            break;
        case 1:
        default:
            break;
    }
    return selection;
}

s32 option_SoundRoomDecide(s32 selection, s32 buttons) {
    s32 result = -1;
    s32 choice;
    s32 model;

    switch (selection) {
        case 0: {
            Vec camera[2] = { { 0.0f, 264.9f, 164.26999f }, { 0.0f, 184.59999f, -138.7f } };

            option_MenuMdlDispOff(6);
            option_MenuMdlDispOff(7);
            option_MenuSprDispOff(0);
            option_MenuWinDispOff(0);
            option_CameraMove(&camera[0], &camera[1], 8);
            HuPrcSleep(8);
            option_MenuWinKill(0);
            do {
                if (!(saveCommonBuf.flags & 1)) {
                    option_MenuWinCreate(0, 0x4E07);
                    option_MenuWinMesSet(0, 0x4E07);
                    choice = option_MenuWinChoiceGet(0);
                    if (choice == 0) {
                        option_MenuSprDispOff(0);
                        HuPrcVSleep();
                        saveCommonBuf.flags |= 1;
                        msmSysSetOutputMode(1);
                        RepeatVibrator(0, 5, 0, 5);
                        SLSaveCommon();
                        option_MenuWinDispOff(0);
                        option_MenuWinKill(0);
                        option_MenuMotShiftSet(8, 11, 0, 8, 0);
                        option_MenuMotFlagReset(21, 1);
                        option_MenuMotTimeSet(21, 0);
                        option_MenuMotEndWait(8);
                        option_MenuMotShiftSet(8, 10, 0, 8, 2);
                        option_MenuMotFlagReset(4, 7);
                        option_MenuMotEndWait(4);
                        option_MenuMotSet(4, 17, 0);
                        option_MenuMotTimeSet(4, 40);
                        option_MenuMotFlagSet(4, 4);
                        HuAudFXPlay(0x2F5);
                        option_MenuMotSet(5, 19, 0);
                        option_MenuMotFlagReset(5, 7);
                        option_MenuMotTimeSet(5, 0);
                        option_MenuMotEndWait(5);
                        option_MenuMotSet(5, 20, 2);
                        option_MenuMotFlagSet(5, 2);
                    }
                } else {
                    option_MenuWinCreate(0, 0x4E08);
                    option_MenuWinMesSet(0, 0x4E08);
                    choice = option_MenuWinChoiceGet(0);
                    if (choice == 0) {
                        option_MenuSprDispOff(0);
                        HuPrcVSleep();
                        saveCommonBuf.flags &= ~1;
                        msmSysSetOutputMode(0);
                        RepeatVibrator(0, 5, 0, 5);
                        SLSaveCommon();
                        option_MenuWinKill(0);
                        option_MenuMotShiftSet(8, 11, 0, 2, 0);
                        option_MenuMotFlagReset(21, 1);
                        option_MenuMotTimeSet(21, 0);
                        option_MenuMotEndWait(8);
                        option_MenuMotShiftSet(8, 10, 0, 8, 2);
                        option_MenuMotFlagReset(5, 7);
                        option_MenuMotEndWait(5);
                        option_MenuMotSet(5, 19, 0);
                        option_MenuMotTimeSet(5, 40);
                        option_MenuMotFlagSet(5, 4);
                        HuAudFXPlay(0x2F5);
                        option_MenuMotSet(4, 17, 0);
                        option_MenuMotFlagReset(4, 7);
                        option_MenuMotTimeSet(4, 0);
                        option_MenuMotEndWait(4);
                        option_MenuMotSet(4, 18, 2);
                        option_MenuMotFlagSet(4, 2);
                    }
                }
                option_SoundRoomCursorUpdate(selection, 0);
            } while (choice == 0);
            option_MenuWinMesSet(0, 0x4E06);
            {
                Vec camera[2] = { { 0.0f, 264.9f, 364.27f }, { 0.0f, 184.59999f, 61.300003f } };

                option_MenuWinDispOff(0);
                option_CameraMove(&camera[0], &camera[1], 8);
            }
            HuPrcSleep(8);
            option_MenuSprDispOn(0);
            option_MenuWinDispOn(0);
            option_MenuMdlDispOn(6);
            option_MenuMdlDispOn(7);
            return result;
        }
        case 1:
            return result;
        case 2:
            option_MenuSprDispOff(0);
            option_CameraMove(&option_soundTestCameraTbl[0], &option_soundTestCameraTbl[1], 8);
            HuAudFXPlay(0x2EA);
            option_MenuMotTimeSet(2, 0);
            option_MenuMotFlagReset(2, 7);
            option_MenuMotFlagSet(2, 0);
            option_MenuMotEndWait(2);
            option_MenuWinDispOff(0);
            HuAudSeqVolSet(0x60);
            option_SoundTestExec();
            HuAudSeqVolSet(0x7F);
            option_CameraMove(&option_soundTestBackCameraTbl[0], &option_soundTestBackCameraTbl[1], 8);
            option_MenuMotTimeSet(2, 40);
            option_MenuMotFlagReset(2, 7);
            option_MenuMotFlagSet(2, 4);
            model = option_MenuMdlIdGet(2);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            option_MenuWinDispOn(0);
            option_MenuSprDispOn(0);
            break;
        case 3:
            option_MenuWinDispOff(0);
            option_MenuSprDispOff(0);
            option_CameraMove(&option_musicTestCameraTbl[0], &option_musicTestCameraTbl[1], 8);
            HuAudFXPlay(0x2EA);
            option_MenuMotTimeSet(3, 0);
            option_MenuMotFlagReset(3, 7);
            option_MenuMotFlagSet(3, 0);
            option_MenuMotEndWait(3);
            option_MusicTestExec();
            HuAudSeqPlay(0x4A);
            option_CameraMove(&option_musicTestBackCameraTbl[0], &option_musicTestBackCameraTbl[1], 8);
            option_MenuMotTimeSet(3, 40);
            option_MenuMotFlagReset(3, 7);
            option_MenuMotFlagSet(3, 4);
            model = option_MenuMdlIdGet(3);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            option_MenuWinDispOn(0);
            option_MenuSprDispOn(0);
            break;
        case 4:
        case 5:
            option_MenuSprDispOff(0);
            option_MenuWinMesSet(0, 0x4E0C);
            if (option_MenuWinChoiceGet(0) != 0) {
                option_MenuWinMesSet(0, 0x4E0B);
                option_MenuSprDispOn(0);
                return -1;
            }
            result = selection;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = selection;
            break;
    }
    return result;
}

void option_SoundRoomCursorUpdate(s32 selection, s32 buttons) {
    s32 x, y;

    option_SoundRoomCursorPosGet(selection, &x, &y);
    option_CursorPosSet(0, x, y);
    option_CursorUpdate(0);
}

s32 option_RecordRoomMove(s32 selection, s32 buttons) {
    Vec pos, at, up;
    s32 x, y, endX, endY;

    up = option_cameraUp;
    switch (selection) {
        case 0:
            if (buttons & 0x200) {
                selection = 1;
            } else if (buttons & 0x100) {
                selection = 2;
            }
            break;
        case 1:
            if (buttons & 0x200) {
                selection = 3;
                HuVecCopy3F(&pos, &option_recordRoomCameraRTbl[0]);
                HuVecCopy3F(&at, &option_recordRoomCameraExitTbl[1]);
                option_CameraTurnMove(&pos, &at, 30);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(30);
                option_ScreenPosGet(option_recordRoomCursorExitPos.x, option_recordRoomCursorExitPos.y, option_recordRoomCursorExitPos.z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e12);
            } else if (buttons & 0x100) {
                selection = 2;
                option_CameraTurnMove(&option_recordRoomCameraRTbl[0], &option_recordRoomCameraRTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_recordRoomCameraRTbl[0], &option_recordRoomCameraRTbl[1], &up, option_recordRoomCursorRPos.x, option_recordRoomCursorRPos.y, option_recordRoomCursorRPos.z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e0e);
            }
            break;
        case 2:
            if (buttons & 0x200) {
                selection = 1;
                option_CameraTurnMove(&option_recordRoomCameraLTbl[0], &option_recordRoomCameraLTbl[1], 7);
                option_MenuSprPosGet(0, &x, &y);
                option_ScreenPosGetEx(&option_recordRoomCameraLTbl[0], &option_recordRoomCameraLTbl[1], &up, option_recordRoomCursorLPos.x, option_recordRoomCursorLPos.y, option_recordRoomCursorLPos.z, &endX, &endY);
                option_SprPosMove(0, x, y, endX, endY, 7);
                option_MenuWinMesSet(0, 0x4e10);
            } else if (buttons & 0x100) {
                selection = 3;
                HuVecCopy3F(&pos, &option_recordRoomCameraRTbl[0]);
                HuVecCopy3F(&at, &option_recordRoomCameraExitTbl[1]);
                option_CameraTurnMove(&pos, &at, 30);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(30);
                option_ScreenPosGet(option_recordRoomCursorExitPos.x, option_recordRoomCursorExitPos.y, option_recordRoomCursorExitPos.z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e12);
            }
            break;
        case 3:
            if (buttons & 0x200) {
                selection = 2;
                option_CameraTurnMove(&option_recordRoomCameraRTbl[0], &option_recordRoomCameraRTbl[1], 30);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(30);
                option_ScreenPosGet(option_recordRoomCursorRPos.x, option_recordRoomCursorRPos.y, option_recordRoomCursorRPos.z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e0e);
            } else if (buttons & 0x100) {
                selection = 1;
                option_CameraTurnMove(&option_recordRoomCameraLTbl[0], &option_recordRoomCameraLTbl[1], 30);
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                HuPrcSleep(30);
                option_ScreenPosGet(option_recordRoomCursorLPos.x, option_recordRoomCursorLPos.y, option_recordRoomCursorLPos.z, &x, &y);
                option_MenuSprPosSet(0, x, y);
                option_MenuSprDispOn(0);
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4e10);
            }
            break;
        case 4:
        default:
            break;
    }
    return selection;
}

s32 option_RecordRoomDecide(s32 selection, s32 arg1) {
    Vec pos, at;
    s32 result = -1;
    s32 choice;
    s32 model;

    switch (selection) {
        case 0:
            break;
        case 1:
            option_MenuSprDispOff(0);
            HuAudFXPlay(0x2E6);
            option_MenuMotShiftSet(8, 12, 0, 8, 2);
            option_MenuMotTimeSet(4, 0);
            option_MenuMotFlagReset(4, 7);
            option_MenuMotEndWait(4);
            option_MenuWinMesSet(0, 0x4E11);
            choice = option_MenuWinChoiceGet(0);
            if (choice == 0) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                option_CameraMove(&pos, &at, 20);
                option_MenuWinDispOff(0);
                HuPrcSleep(20);
                option_PartyRecordExec(0xE002E, 160, 120);
            } else if (choice == 1) {
                HuVecCopyXYZ(&pos, -195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, -195.0f, 160.0f, -680.0f);
                option_CameraMove(&pos, &at, 20);
                option_MenuWinDispOff(0);
                HuPrcSleep(20);
                option_DuelRecordExec(0xE002E, 160, 120);
            }
            option_MenuWinMesSet(0, 0x4E10);
            option_CameraMove(&option_recordRoomCameraLTbl[0], &option_recordRoomCameraLTbl[1], 30);
            option_MenuMotShiftSet(8, 10, 0, 8, 2);
            option_MenuMotFlagReset(4, 7);
            option_MenuMotFlagSet(4, 4);
            HuPrcSleep(30);
            model = option_MenuMdlIdGet(4);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            option_MenuWinDispOn(0);
            option_MenuSprDispOn(0);
            break;
        case 2:
            option_MenuSprDispOff(0);
            HuAudFXPlay(0x2E6);
            option_MenuMotShiftSet(9, 12, 0, 8, 2);
            option_MenuMotTimeSet(5, 0);
            option_MenuMotFlagReset(5, 7);
            option_MenuMotEndWait(5);
            option_MenuWinMesSet(0, 0x4E0F);
            if (option_MenuWinChoiceGet(0) == 0) {
                HuVecCopyXYZ(&pos, 195.0f, 160.0f, -595.0f);
                HuVecCopyXYZ(&at, 195.0f, 160.0f, -665.0f);
                option_CameraMove(&pos, &at, 20);
                option_MenuWinDispOff(0);
                HuPrcSleep(20);
                option_MgRecordExec(0xE002D, 160, 120);
            }
            option_MenuWinMesSet(0, 0x4E0E);
            option_CameraMove(&option_recordRoomCameraRTbl[0], &option_recordRoomCameraRTbl[1], 30);
            option_MenuMotShiftSet(9, 11, 0, 8, 2);
            option_MenuMotFlagReset(5, 7);
            option_MenuMotFlagSet(5, 4);
            HuPrcSleep(30);
            model = option_MenuMdlIdGet(5);
            while (Hu3DData[(s16)model].motTime != 0.0f) {
                HuPrcVSleep();
            }
            option_MenuWinDispOn(0);
            option_MenuSprDispOn(0);
            break;
        case 3:
            option_MenuSprDispOff(0);
            option_MenuWinMesSet(0, 0x4E13);
            if (option_MenuWinChoiceGet(0) == 0) {
                result = 3;
            } else {
                switch (selection) {
                    case 0:
                    default:
                        break;
                    case 1:
                        option_MenuWinMesSet(0, 0x4E10);
                        break;
                    case 2:
                        option_MenuWinMesSet(0, 0x4E0E);
                        break;
                    case 3:
                        option_MenuWinMesSet(0, 0x4E12);
                        break;
                }
                option_MenuSprDispOn(0);
                result = -1;
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            result = 4;
            break;
    }
    return result;
}

void option_RecordRoomCursorUpdate(s32 selection, s32 buttons) {
    s32 x = 160;
    s32 y = 120;

    switch (selection) {
        case 0:
            break;
        case 1:
            option_ScreenPosGet(option_recordRoomCursorLPos.x, option_recordRoomCursorLPos.y, option_recordRoomCursorLPos.z, &x, &y);
            break;
        case 2:
            option_ScreenPosGet(option_recordRoomCursorRPos.x, option_recordRoomCursorRPos.y, option_recordRoomCursorRPos.z, &x, &y);
            break;
        case 3:
            option_ScreenPosGet(option_recordRoomCursorExitPos.x, option_recordRoomCursorExitPos.y, option_recordRoomCursorExitPos.z, &x, &y);
            break;
    }
    option_CursorPosSet(0, x, y);
    option_CursorUpdate(0);
}

s32 option_RecordRoomChoice(void) {
    s32 x, y;
    s32 buttons;
    s32 selection;
    s32 next;

    option_MenuWinCreate(0, 0x4E0D);
    option_MenuWinMesWait(0);
    option_MenuWinMesSet(0, 0x4E10);
    selection = 1;
    option_CameraTurnMove(&option_recordRoomCameraLTbl[0], &option_recordRoomCameraLTbl[1], 20);
    HuPrcSleep(20);
    option_ScreenPosGet(option_recordRoomCursorLPos.x, option_recordRoomCursorLPos.y, option_recordRoomCursorLPos.z, &x, &y);
    option_MenuSprPosSet(0, x, y);
    option_MenuSprDispOn(0);
    option_RecordRoomCursorUpdate(1, 0);
    {
        Vec pos, at;
        while (1) {
            buttons = HuPadBtnDown[0];
            buttons |= option_StickBtnGet(0);
            if (buttons & 0x8000) {
                next = option_RecordRoomDecide(selection, buttons);
                if (next != -1) {
                    selection = next;
                    break;
                }
            } else if (buttons & 0xF00) {
                selection = option_RecordRoomMove(selection, buttons);
            } else if (buttons & 0x4000) {
                option_MenuSprDispOff(0);
                option_MenuWinDispOff(0);
                switch (selection) {
                    case 0:
                    case 1:
                    case 2:
                        selection = 3;
                        HuVecCopy3F(&pos, &option_recordRoomCameraExitTbl[0]);
                        HuVecCopy3F(&at, &option_recordRoomCameraExitTbl[1]);
                        option_CameraTurnMove(&pos, &at, 20);
                        HuPrcSleep(20);
                        break;
                    case 3:
                    default:
                        selection = 3;
                        break;
                }
                option_MenuWinDispOn(0);
                option_MenuWinMesSet(0, 0x4E12);
                option_MenuSprDispOn(0);
            }
            option_RecordRoomCursorUpdate(selection, buttons);
            HuPrcVSleep();
        }
    }
    option_MenuWinKill(0);
    return selection;
}

void option_RecordRoomProc(void) {
    Vec pos, at;
    s32 selection;
    s32 result;

    Hu3DBGColorSet(0, 64, 64);
    option_RecordRoomInit();
    HuAudSeqVolSet(0x60);
    WipeCreateIn(0xB, 16);
    HuPrcSleep(16);
    selection = option_RecordRoomChoice();
    option_MenuSprDispOff(0);
    switch (selection) {
        case 3:
            HuVecCopy3F(&pos, &option_recordRoomExitPos);
            pos.z -= 200.0f;
            pos.y -= 40.0f;
            HuVecCopy3F(&at, &option_recordRoomExitAt);
            at.y -= 40.0f;
            HuAudFXPlay(0x2EB);
            option_MenuMotTimeSet(1, 0);
            option_MenuMotFlagReset(1, 7);
            option_MenuMotEndWait(1);
            pos.z += 200.0f;
            option_CameraMove(&pos, &at, 20);
            result = selection;
            option_RumbleStart();
            WipeColorSet(255, 255, 255);
            WipeCreateOut(0xB, 20);
            HuAudSeqVolSet(0x7F);
            HuPrcSleep(20);
            break;
        case 0:
        case 1:
        case 2:
        case 4:
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            selection = 9;
            break;
    }
    result = selection;
    option_RecordRoomClose();
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 3:
            omOvlReturnEx(1);
            break;
        default:
            omOvlReturnEx(1);
            break;
    }
    omDelPrcObj(option_roomProc);
    while (1) {
        HuPrcVSleep();
    }
}

void option_PartyRecordExec(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    s16 icons[8];
    s16 digits[16];
    s16 anim;
    u16 sprite;
    s16 win;
    s16 iconAnim;
    s16 digitAnim;
    s32 nextPage = 0;
    s32 messages[6] = { 0x5002, 0x5003, 0x5004, 0x5005, 0x5006, 0x5007 };
    char text[8];
    s16 i;
    s16 j;
    s32 page;
    s32 count;
    s32 buttons;
    s32 value;
    s32 ones;
    f32 scale;
    f32 baseX;
    f32 baseY;

    page = 0;
    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    iconAnim = HuSprAnimDataRead(0x1F0004);
    for (i = 0; i < 8; i++) {
        icons[i] = espEntry(iconAnim, 0, 1);
        espPosSet(icons[i], x + i * 24 - 84, y + 12);
        espPriSet(icons[i], 0x8000);
        espScaleSet(icons[i], 1.0f, 1.0f);
        espAnimModeSet(icons[i], 1);
        espBankSet(icons[i], (u16)option_partyRecordChrTbl[i], 0);
        espDispOff(icons[i]);
    }
    digitAnim = HuSprAnimDataRead(0x1F0007);
    for (i = 0; i < 8; i++) {
        s32 offsetX;

        digits[i * 2] = espEntry(digitAnim, 0, 1);
        digits[i * 2 + 1] = espEntry(digitAnim, 0, 1);
        offsetX = i * 24 - 96;
        espPosSet(digits[i * 2], x + offsetX + 8, y + 26);
        espPosSet(digits[i * 2 + 1], x + offsetX + 16, y + 26);
        espPriSet(digits[i * 2], 0x8000);
        espPriSet(digits[i * 2 + 1], 0x8000);
        espScaleSet(digits[i * 2], 1.0f, 1.0f);
        espScaleSet(digits[i * 2 + 1], 1.0f, 1.0f);
        espAnimModeSet(digits[i * 2], 1);
        espAnimModeSet(digits[i * 2 + 1], 1);
        value = (u8)(GwCommon.boardRecord[0][page].chr[option_partyRecordChrTbl[i]] / 10);
        if (value >= 10) {
            value = 9;
        }
        ones = (u8)(GwCommon.boardRecord[0][page].chr[option_partyRecordChrTbl[i]] % 10);
        espBankSet(digits[i * 2], (u16)value, 0);
        espBankSet(digits[i * 2 + 1], (u16)ones, 0);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    baseX = x - 104;
    baseY = y - 71;
    while (1) {
        wins[0] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[0].x, baseY + option_partyRecordWinTbl[0].y,
                                option_partyRecordWinTbl[0].w, option_partyRecordWinTbl[0].h, 0);
        HuWinBGTPLvlSet(wins[0], 0);
        HuWinMesSet(wins[0], 0x5000, -1, -1);
        wins[1] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[1].x, baseY + option_partyRecordWinTbl[1].y,
                                option_partyRecordWinTbl[1].w, option_partyRecordWinTbl[1].h, 0);
        HuWinBGTPLvlSet(wins[1], 0);
        HuWinMesSet(wins[1], messages[page], -1, -1);
        count = 2;
        wins[count] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[count].x, baseY + option_partyRecordWinTbl[count].y,
                                    option_partyRecordWinTbl[count].w, option_partyRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        value = GwCommon.boardRecord[0][page].playCount;
        if (value >= 100) {
            value = 99;
        }
        sprintf(text, "%2d", value);
        HuWinInsertMesSet(wins[count], (u32)text, 0);
        HuWinMesSet(wins[count], 0x500E, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[count].x, baseY + option_partyRecordWinTbl[count].y,
                                    option_partyRecordWinTbl[count].w, option_partyRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x500F, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[count].x, baseY + option_partyRecordWinTbl[count].y,
                                    option_partyRecordWinTbl[count].w, option_partyRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5010, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_partyRecordWinTbl[count].x, baseY + option_partyRecordWinTbl[count].y,
                                    option_partyRecordWinTbl[count].w, option_partyRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5011, -1, -1);
        count++;
        for (i = 0; i < 4; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + option_partyRecordWinTbl[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            espDispOn(icons[i]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 10);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            value = (u8)(GwCommon.boardRecord[0][page].chr[option_partyRecordChrTbl[i]] / 10);
            if (value >= 10) {
                value = 9;
            }
            ones = (u8)(GwCommon.boardRecord[0][page].chr[option_partyRecordChrTbl[i]] % 10);
            espBankSet(digits[i * 2], (u16)value, 0);
            espBankSet(digits[i * 2 + 1], (u16)ones, 0);
            espAnimModeSet(digits[i * 2], 1);
            espAnimModeSet(digits[i * 2 + 1], 1);
            if (value != 0) {
                espDispOn(digits[i * 2]);
            } else {
                espDispOff(digits[i * 2]);
            }
            espDispOn(digits[i * 2 + 1]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 25);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        HuWinDispOff(win);
        for (i = 4; i < count; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + option_partyRecordWinTbl[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            buttons = HuPadBtnDown[0];
            buttons |= option_StickBtnGet(0);
        } while (!(buttons & (B_BUTTON | L_JPAD | R_JPAD)));
        if (buttons & B_BUTTON) {
            break;
        }
        if (buttons & L_JPAD) {
            nextPage = nextPage - 1 < 0 ? 5 : nextPage - 1;
            if (!_CheckFlag(0x31) && nextPage == 5) {
                nextPage = 4;
            }
        }
        if (buttons & R_JPAD) {
            nextPage = nextPage + 1 < 6 ? nextPage + 1 : 0;
            if (!_CheckFlag(0x31) && nextPage == 5) {
                nextPage = 0;
            }
        }
        page = nextPage;
        for (i = 0; i < 8; i++) {
            espDispOff(icons[i]);
            espDispOff(digits[i * 2]);
            espDispOff(digits[i * 2 + 1]);
        }
        for (i = 0; i < count; i++) {
            HuWinDispOff(wins[i]);
        }
        for (i = 0; i < count; i++) {
            HuWinKill(wins[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    HuWinKill(win);
    for (i = 0; i < 8; i++) {
        espDispOff(icons[i]);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    for (i = 0; i < count; i++) {
        HuWinDispOff(wins[i]);
    }
    for (i = 0; i < count; i++) {
        HuWinKill(wins[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        espKill(icons[i]);
        espKill(digits[i * 2]);
        espKill(digits[i * 2 + 1]);
    }
    HuSprAnimKill(iconAnim);
    HuSprAnimKill(digitAnim);
    espKill(sprite);
    HuSprAnimKill(anim);
}

void option_DuelRecordExec(s32 animFile, s16 x, s16 y) {
    s16 wins[10];
    s16 icons[8];
    s16 digits[16];
    s16 anim;
    u16 sprite;
    s16 win;
    s16 iconAnim;
    s16 digitAnim;
    s32 nextPage = 0;
    s32 messages[6] = { 0x5008, 0x5009, 0x500A, 0x500B, 0x500C, 0x500D };
    char text[8];
    s16 i;
    s16 j;
    s32 page;
    s32 count;
    s32 buttons;
    s32 value;
    s32 ones;
    f32 scale;
    f32 baseX;
    f32 baseY;

    page = 0;
    HuPrcSleep(3);
    anim = HuSprAnimDataRead(animFile);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    iconAnim = HuSprAnimDataRead(0x1F0004);
    for (i = 0; i < 8; i++) {
        icons[i] = espEntry(iconAnim, 0, 1);
        espPosSet(icons[i], x + i * 24 - 84, y + 12);
        espPriSet(icons[i], 0x8000);
        espScaleSet(icons[i], 1.0f, 1.0f);
        espAnimModeSet(icons[i], 1);
        espBankSet(icons[i], (u16)option_duelRecordChrTbl[i], 0);
        espDispOff(icons[i]);
    }
    digitAnim = HuSprAnimDataRead(0x1F0007);
    for (i = 0; i < 8; i++) {
        s32 offsetX;

        digits[i * 2] = espEntry(digitAnim, 0, 1);
        digits[i * 2 + 1] = espEntry(digitAnim, 0, 1);
        offsetX = i * 24 - 96;
        espPosSet(digits[i * 2], x + offsetX + 8, y + 26);
        espPosSet(digits[i * 2 + 1], x + offsetX + 16, y + 26);
        espPriSet(digits[i * 2], 0x8000);
        espPriSet(digits[i * 2 + 1], 0x8000);
        espScaleSet(digits[i * 2], 1.0f, 1.0f);
        espScaleSet(digits[i * 2 + 1], 1.0f, 1.0f);
        espAnimModeSet(digits[i * 2], 1);
        espAnimModeSet(digits[i * 2 + 1], 1);
        value = (u8)(GwCommon.boardRecord[1][page].chr[option_duelRecordChrTbl[i]] / 10);
        if (value >= 10) {
            value = 9;
        }
        ones = (u8)(GwCommon.boardRecord[1][page].chr[option_duelRecordChrTbl[i]] % 10);
        espBankSet(digits[i * 2], (u16)value, 0);
        espBankSet(digits[i * 2 + 1], (u16)ones, 0);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i <= 10; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    baseX = x - 104;
    baseY = y - 71;
    while (1) {
        wins[0] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[0].x, baseY + option_duelRecordWinTbl[0].y,
                                option_duelRecordWinTbl[0].w, option_duelRecordWinTbl[0].h, 0);
        HuWinBGTPLvlSet(wins[0], 0);
        HuWinMesSet(wins[0], 0x5001, -1, -1);
        wins[1] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[1].x, baseY + option_duelRecordWinTbl[1].y,
                                option_duelRecordWinTbl[1].w, option_duelRecordWinTbl[1].h, 0);
        HuWinBGTPLvlSet(wins[1], 0);
        HuWinMesSet(wins[1], messages[page], -1, -1);
        count = 2;
        wins[count] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[count].x, baseY + option_duelRecordWinTbl[count].y,
                                    option_duelRecordWinTbl[count].w, option_duelRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        value = GwCommon.boardRecord[1][page].playCount;
        if (value >= 100) {
            value = 99;
        }
        sprintf(text, "%2d", value);
        HuWinInsertMesSet(wins[count], (u32)text, 0);
        HuWinMesSet(wins[count], 0x500E, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[count].x, baseY + option_duelRecordWinTbl[count].y,
                                    option_duelRecordWinTbl[count].w, option_duelRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x500F, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[count].x, baseY + option_duelRecordWinTbl[count].y,
                                    option_duelRecordWinTbl[count].w, option_duelRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5010, -1, -1);
        count++;
        wins[count] = HuWinExCreate(-1, baseX + option_duelRecordWinTbl[count].x, baseY + option_duelRecordWinTbl[count].y,
                                    option_duelRecordWinTbl[count].w, option_duelRecordWinTbl[count].h, 0);
        HuWinBGTPLvlSet(wins[count], 0);
        HuWinMesSet(wins[count], 0x5011, -1, -1);
        count++;
        for (i = 0; i < 4; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + option_duelRecordWinTbl[i].y + 9.0f);
            HuAudFXPlay(0x2E8);
            HuWinDispOn(win);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 8; i++) {
            espDispOn(icons[i]);
        }
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 10);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        for (i = 0; i < 8; i++) {
            value = (u8)(GwCommon.boardRecord[1][page].chr[option_duelRecordChrTbl[i]] / 10);
            if (value >= 10) {
                value = 9;
            }
            ones = (u8)(GwCommon.boardRecord[1][page].chr[option_duelRecordChrTbl[i]] % 10);
            espBankSet(digits[i * 2], (u16)value, 0);
            espBankSet(digits[i * 2 + 1], (u16)ones, 0);
            espAnimModeSet(digits[i * 2], 1);
            espAnimModeSet(digits[i * 2 + 1], 1);
            if (value != 0) {
                espDispOn(digits[i * 2]);
            } else {
                espDispOff(digits[i * 2]);
            }
            espDispOn(digits[i * 2 + 1]);
        }
        HuAudFXPlay(0x2E8);
        HuWinDispOn(win);
        for (j = 1; j < 4; j++) {
            HuWinPosSet(win, x, y + 25);
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
        HuWinDispOff(win);
        for (i = 4; i < count; i++) {
            HuWinDispOn(wins[i]);
            HuWinPosSet(win, baseX + 104.0f, baseY + option_duelRecordWinTbl[i].y + 9.0f);
            HuWinDispOn(win);
            HuAudFXPlay(0x2E8);
            for (j = 1; j < 4; j++) {
                HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
                HuPrcVSleep();
            }
        }
        do {
            HuPrcVSleep();
            buttons = HuPadBtnDown[0];
            buttons |= option_StickBtnGet(0);
        } while (!(buttons & (B_BUTTON | L_JPAD | R_JPAD)));
        if (buttons & B_BUTTON) {
            break;
        }
        if (buttons & L_JPAD) {
            nextPage = nextPage - 1 < 0 ? 5 : nextPage - 1;
            if (!_CheckFlag(0x30) && nextPage == 5) {
                nextPage = 4;
            }
        }
        if (buttons & R_JPAD) {
            nextPage = nextPage + 1 < 6 ? nextPage + 1 : 0;
            if (!_CheckFlag(0x30) && nextPage == 5) {
                nextPage = 0;
            }
        }
        page = nextPage;
        for (i = 0; i < 8; i++) {
            espDispOff(icons[i]);
            espDispOff(digits[i * 2]);
            espDispOff(digits[i * 2 + 1]);
        }
        for (i = 0; i < count; i++) {
            HuWinDispOff(wins[i]);
        }
        for (i = 0; i < count; i++) {
            HuWinKill(wins[i]);
        }
        HuPrcSleep(3);
    }
    HuAudFXPlay(0x2E9);
    HuWinKill(win);
    for (i = 0; i < 8; i++) {
        espDispOff(icons[i]);
        espDispOff(digits[i * 2]);
        espDispOff(digits[i * 2 + 1]);
    }
    for (i = 0; i < count; i++) {
        HuWinDispOff(wins[i]);
    }
    for (i = 0; i < count; i++) {
        HuWinKill(wins[i]);
    }
    HuPrcSleep(3);
    for (i = 1; i <= 10; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 8; i++) {
        espKill(icons[i]);
        espKill(digits[i * 2]);
        espKill(digits[i * 2 + 1]);
    }
    HuSprAnimKill(iconAnim);
    HuSprAnimKill(digitAnim);
    espKill(sprite);
    HuSprAnimKill(anim);
}

void option_ListCursorUpdate(s32 x, s32 y, s32 frame) {
    option_MenuSprPosSet(1, (s32)(x + sindf(frame * 18) * 4.0f) - 2, y);
}

void option_ListCursorMove(s32 startX, s32 startY, s32 endX, s32 endY, s32 duration) {
    s32 i;
    s32 dx;
    s32 dy;
    f32 t;

    i = 0;
    dx = endX - startX;
    dy = endY - startY;
    for (;; i++) {
        HuPrcVSleep();
        t = (f32)i / duration;
        option_MenuSprPosSet(1, dx * t + startX, dy * t + startY);
        if (i == duration) {
            break;
        }
    }
}

void option_SoundTestExec(void) {
    s16 windows[16];
    OptSoundMenu menu = option_soundTestTbl;
    s16 titleWindow;
    s32 i;
    s32 page;
    s32 selected;
    s32 frame;
    s32 buttons;
    s32 customSounds;
    s32 previous;
    s32 sound;
    s16 model;

    option_MenuMotTimeSet(2, 0);
    option_MenuMotSet(2, 13, 0);
    option_MenuMotFlagReset(2, 7);
    selected = 0;
    page = 0;
    option_MenuSprPosSet(2, 90, 116);
    option_MenuSprDispOn(2);
    option_MenuSprPosSet(1, 30, 40);
    option_MenuSprDispOn(1);
    titleWindow = HuWinExCreate(-1, 24, 28, 120, 20, 0);
    HuWinBGTPLvlSet(titleWindow, 0);
    HuWinMesDefColSet(titleWindow, 192, 192, 192);
    HuWinBGColSet(titleWindow, 255, 255, 255);
    HuWinMesPalSet(titleWindow, 0, 0, 0, 0);
    HuWinMesColSet(titleWindow, 0);
    HuWinMesSet(titleWindow, menu.pages[0].title, -1, -1);
    HuWinDispOn(titleWindow);
    customSounds = 0;
    if (MgStoryRankGet(0) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[1].message = 0x4C37;
        menu.pages[14].entries[1].sound = 0x2C7;
    }
    if (MgStoryRankGet(1) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[2].message = 0x4C38;
        menu.pages[14].entries[2].sound = 0x2C8;
    }
    if (MgStoryRankGet(2) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[3].message = 0x4C39;
        menu.pages[14].entries[3].sound = 0x2C9;
    }
    if (MgStoryRankGet(3) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[4].message = 0x4C3A;
        menu.pages[14].entries[4].sound = 0x2CA;
    }
    if (MgStoryRankGet(4) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[5].message = 0x4C3B;
        menu.pages[14].entries[5].sound = 0x2CB;
    }
    if (MgStoryRankGet(5) >= 0) {
        customSounds = 1;
        menu.pages[14].entries[6].message = 0x4C3C;
        menu.pages[14].entries[6].sound = 0x2CC;
    }
    if (customSounds) {
        menu.pages[14].entries[0].message = 0x4C36;
        menu.pages[14].entries[0].sound = 0x240;
    }
    for (i = 0; i < 9; i++) {
        windows[i] = HuWinExCreate(-1, 36, (i + 1) * 14 + 28, 120, 20, 0);
        HuWinBGTPLvlSet(windows[i], 0);
        HuWinMesDefColSet(windows[i], 192, 192, 192);
        HuWinBGColSet(windows[i], 255, 255, 255);
        HuWinMesPalSet(windows[i], 0, 0, 0, 0);
        HuWinMesColSet(windows[i], 0);
        if (menu.pages[page].entries[i].message != -1) {
            HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
        } else {
            HuWinHomeClear(windows[i]);
        }
        HuWinDispOn(windows[i]);
    }
    windows[10] = HuWinExCreate(-1, 36, 176, 120, 44, 0);
    HuWinBGTPLvlSet(windows[10], 0);
    HuWinMesDefColSet(windows[10], 192, 192, 192);
    HuWinBGColSet(windows[10], 255, 255, 255);
    HuWinMesPalSet(windows[10], 0, 0, 0, 0);
    HuWinMesColSet(windows[10], 0);
    HuWinMesSet(windows[10], 0x5D00, -1, -1);
    HuWinDispOn(windows[10]);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        buttons = HuPadBtnRep[0];
        buttons |= option_PadBtnRepGet(0);
        buttons = (buttons & ~(A_BUTTON | B_BUTTON)) | (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON));
        if (buttons & 0x4000) {
            model = option_MenuMdlIdGet(2);
            Hu3DModelAnimStop(Hu3DData[model].hmf);
            break;
        } else if (buttons & 0x8000) {
            if (menu.pages[page].entries[selected].sound != -1) {
                if (option_SeObjCheck()) {
                    option_SeObjKill();
                }
                sound = HuAudFXPlay(menu.pages[page].entries[selected].sound);
                model = option_MenuMdlIdGet(2);
                Hu3DModelAnimStart(Hu3DData[model].hmf);
                option_SeObjCreate(sound);
            } else {
                option_MenuMdlIdGet(2);
            }
        } else if (buttons & 0x300) {
            if (buttons & 0x200) {
                page--;
            } else {
                page++;
            }
            page = page < 15 ? page : 0;
            if (page < 0) {
                page = 14;
            }
            if (page == 14) {
                if (!customSounds) {
                    page = buttons & 0x200 ? 13 : 0;
                }
            }
            HuWinMesSet(titleWindow, menu.pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (menu.pages[page].entries[i].message != -1) {
                    HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
                } else {
                    HuWinHomeClear(windows[i]);
                }
            }
            for (;;) {
                if (menu.pages[page].entries[selected].sound != -1) {
                    goto update_cursor;
                }
                selected--;
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            }
        } else if (buttons & 0xC00) {
            previous = selected;
            do {
                if (buttons & 0x800) {
                    selected--;
                } else {
                    selected++;
                }
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            } while (menu.pages[page].entries[selected].sound == -1);
            option_ListCursorMove(30, (previous + 1) * 14 + 40, 30, (selected + 1) * 14 + 40, 4);
        }
    update_cursor:
        frame = frame < 11 ? frame + 1 : 0;
        option_ListCursorUpdate(30, (selected + 1) * 14 + 40, frame);
    }
    HuWinDispOff(titleWindow);
    HuWinKill(titleWindow);
    for (i = 0; i < 9; i++) {
        HuWinDispOff(windows[i]);
    }
    for (i = 0; i < 9; i++) {
        HuWinKill(windows[i]);
    }
    HuWinDispOff(windows[10]);
    HuWinKill(windows[10]);
    HuAudFXPlay(0x2F9);
    option_MenuMotSet(2, 15, 1);
    option_MenuMotTimeSet(2, 40);
    HuPrcSleep(3);
    option_MenuSprDispOff(1);
    option_MenuSprDispOff(2);
}

void option_MusicTestExec(void) {
    s16 windows[16];
    OptMusicMenu menu = option_musicTestTbl;
    s16 titleWindow;
    s32 i;
    s32 page;
    s32 selected;
    s32 frame;
    s32 buttons;
    s32 previous;
    s16 model;

    option_MenuMotTimeSet(3, 0);
    option_MenuMotSet(3, 14, 0);
    option_MenuMotFlagReset(3, 7);
    selected = 0;
    page = 0;
    option_MenuSprPosSet(2, 230, 116);
    option_MenuSprDispOn(2);
    option_MenuSprPosSet(1, 170, 40);
    option_MenuSprDispOn(1);
    titleWindow = HuWinExCreate(-1, 164, 28, 120, 20, 0);
    HuWinBGTPLvlSet(titleWindow, 0);
    HuWinMesDefColSet(titleWindow, 192, 192, 192);
    HuWinBGColSet(titleWindow, 255, 255, 255);
    HuWinMesPalSet(titleWindow, 0, 0, 0, 0);
    HuWinMesColSet(titleWindow, 0);
    HuWinMesSet(titleWindow, 0x5D01, -1, -1);
    HuWinDispOn(titleWindow);
    if (option_MgTypeUnlockCheck()) {
        menu.pages[2].entries[1].message = 0x5D15;
        menu.pages[2].entries[1].sound = 0x4C;
    }
    if (_CheckFlag(0x1D)) {
        menu.pages[2].entries[2].message = 0x5D16;
        menu.pages[2].entries[2].sound = 0x4D;
    }
    if (_CheckFlag(0x31)) {
        menu.pages[3].entries[5].message = 0x5D1C;
        menu.pages[3].entries[5].sound = 0x1D;
    }
    if (_CheckFlag(0x30)) {
        menu.pages[4].entries[2].message = 0x5D1F;
        menu.pages[4].entries[2].sound = 0x20;
    }
    if (_CheckFlag(0x1E)) {
        menu.pages[8].entries[7].message = 0x5D3C;
        menu.pages[8].entries[7].sound = 0x41;
        menu.pages[10].entries[0].message = 0x5D44;
        menu.pages[10].entries[0].sound = 0x28;
        menu.pages[10].entries[1].message = 0x5D45;
        menu.pages[10].entries[1].sound = 0x29;
        menu.pages[10].entries[2].message = 0x5D46;
        menu.pages[10].entries[2].sound = 0x2A;
        menu.pages[10].entries[3].message = 0x5D47;
        menu.pages[10].entries[3].sound = 0x6;
    }
    for (i = 0; i < 9; i++) {
        windows[i] = HuWinExCreate(-1, 180, (i + 1) * 14 + 28, 118, 20, 0);
        HuWinBGTPLvlSet(windows[i], 0);
        HuWinMesDefColSet(windows[i], 192, 192, 192);
        HuWinBGColSet(windows[i], 255, 255, 255);
        HuWinMesPalSet(windows[i], 0, 0, 0, 0);
        HuWinMesColSet(windows[i], 0);
        if (menu.pages[page].entries[i].message != -1) {
            HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
        } else {
            HuWinHomeClear(windows[i]);
        }
        HuWinDispOn(windows[i]);
    }
    windows[10] = HuWinExCreate(-1, 176, 190, 120, 44, 0);
    HuWinBGTPLvlSet(windows[10], 0);
    HuWinMesDefColSet(windows[10], 192, 192, 192);
    HuWinBGColSet(windows[10], 255, 255, 255);
    HuWinMesPalSet(windows[10], 0, 0, 0, 0);
    HuWinMesColSet(windows[10], 0);
    HuWinMesSet(windows[10], 0x5D00, -1, -1);
    HuWinDispOn(windows[10]);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        buttons = HuPadBtnRep[0];
        buttons |= option_PadBtnRepGet(0);
        buttons = (buttons & ~(A_BUTTON | B_BUTTON)) | (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON));
        if (buttons & 0x4000) {
            model = option_MenuMdlIdGet(3);
            Hu3DModelAnimStop(Hu3DData[model].hmf);
            break;
        } else if (buttons & 0x8000) {
            HuAudSeqStop();
            if (menu.pages[page].entries[selected].sound != -1) {
                HuAudSeqPlay(menu.pages[page].entries[selected].sound);
            }
            model = option_MenuMdlIdGet(3);
            Hu3DModelAnimStart(Hu3DData[model].hmf);
        } else if (buttons & 0x300) {
            if (buttons & 0x200) {
                page--;
            } else {
                page++;
            }
            page = page < 12 ? page : 0;
            if (page < 0) {
                page = 11;
            }
            if (page == 10) {
                if (!_CheckFlag(0x1E)) {
                    page = buttons & 0x200 ? 9 : 11;
                }
            }
            HuWinMesSet(titleWindow, menu.pages[page].title, -1, -1);
            for (i = 0; i < 9; i++) {
                if (menu.pages[page].entries[i].message != -1) {
                    HuWinMesSet(windows[i], menu.pages[page].entries[i].message, -1, -1);
                } else {
                    HuWinHomeClear(windows[i]);
                }
            }
            for (;;) {
                if (menu.pages[page].entries[selected].sound != -1) {
                    goto update_cursor;
                }
                selected--;
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            }
        } else if (buttons & 0xC00) {
            previous = selected;
            do {
                if (buttons & 0x800) {
                    selected--;
                } else {
                    selected++;
                }
                selected = selected < 9 ? selected : 0;
                if (selected < 0) {
                    selected = 8;
                }
            } while (menu.pages[page].entries[selected].sound == -1);
            option_ListCursorMove(170, (previous + 1) * 14 + 40, 170, (selected + 1) * 14 + 40, 4);
        }
    update_cursor:
        frame = frame < 11 ? frame + 1 : 0;
        option_ListCursorUpdate(170, (selected + 1) * 14 + 40, frame);
    }
    HuWinDispOff(titleWindow);
    HuWinKill(titleWindow);
    for (i = 0; i < 9; i++) {
        HuWinDispOff(windows[i]);
    }
    for (i = 0; i < 9; i++) {
        HuWinKill(windows[i]);
    }
    HuWinDispOff(windows[10]);
    HuWinKill(windows[10]);
    HuAudFXPlay(0x2F9);
    option_MenuMotSet(3, 16, 1);
    option_MenuMotTimeSet(3, 40);
    HuPrcSleep(3);
    option_MenuSprDispOff(1);
    option_MenuSprDispOff(2);
}

f32 option_LookAtAngleCalc(f32 x, f32 y) {
    return -(atan2df(y, x) - 90.0f);
}

void option_LookAtInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(option_lookAtTbl); i++) {
        HuVecCopyXYZ(&option_lookAtTbl[i].unk_00, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&option_lookAtTbl[i].unk_0C, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&option_lookAtTbl[i].unk_18, 0.0f, 0.0f, 0.0f);
        option_lookAtTbl[i].obj = NULL;
    }
}

void option_LookAtKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(option_lookAtTbl); i++) {
        omDelObj(option_lookAtTbl[i].obj);
    }
}

void option_LookAtObjMain(omObjData *obj) {
    Vec pos;
    Vec at;
    Vec up;
    Vec modelPos;
    Vec direction;
    s32 model;

    model = option_lookAtTbl[obj->work[0]].unk_24;
    option_CameraPosGet(&pos, &at, &up);
    option_MenuMdlPosGet(model, &modelPos.x, &modelPos.y, &modelPos.z);
    HuVecCopyXYZ(&direction, pos.x - modelPos.x, pos.y - modelPos.y, pos.z - modelPos.z);
    option_MenuMdlRotSet(model, 0.0f, option_LookAtAngleCalc(direction.x, direction.z), 0.0f);
}

void option_LookAtCreate(s32 index, s32 model) {
    f32 x, y, z;

    if (option_lookAtTbl[index].obj != NULL) {
        omDelObj(option_lookAtTbl[index].obj);
    }
    option_MenuMdlPosGet(model, &x, &y, &z);
    HuVecCopyXYZ(&option_lookAtTbl[index].unk_0C, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&option_lookAtTbl[index].unk_18, x, y, z);
    option_lookAtTbl[index].unk_24 = model;
    option_lookAtTbl[index].obj = omAddObj(6, 0, 0, -1, option_LookAtObjMain);
    option_lookAtTbl[index].obj->work[0] = index;
}

const OptSoundMenu option_soundTestTbl = {
    {
        {
            0x4C01,
            {
                { 0x4C10, 0x2B5 },
                { 0x4C11, 0x263 },
                { 0x4C14, 0x275 },
                { 0x4C12, 0x290 },
                { 0x4C13, 0x27E },
                { 0x4C15, 0x26C },
                { 0x4C16, 0x287 },
                { 0x4C17, 0x2AC },
                { -1, -1 },
            },
        },
        {
            0x4C02,
            {
                { 0x4C10, 0x2B6 },
                { 0x4C11, 0x264 },
                { 0x4C14, 0x276 },
                { 0x4C12, 0x291 },
                { 0x4C13, 0x27F },
                { 0x4C15, 0x26D },
                { 0x4C16, 0x288 },
                { 0x4C17, 0x2AD },
                { -1, -1 },
            },
        },
        {
            0x4C03,
            {
                { 0x4C10, 0x2B7 },
                { 0x4C11, 0x265 },
                { 0x4C14, 0x277 },
                { 0x4C12, 0x292 },
                { 0x4C13, 0x280 },
                { 0x4C15, 0x26E },
                { 0x4C16, 0x289 },
                { 0x4C17, 0x2AE },
                { -1, -1 },
            },
        },
        {
            0x4C04,
            {
                { 0x4C10, 0x2B8 },
                { 0x4C11, 0x266 },
                { 0x4C14, 0x278 },
                { 0x4C12, 0x293 },
                { 0x4C13, 0x281 },
                { 0x4C15, 0x26F },
                { 0x4C16, 0x28A },
                { 0x4C17, 0x2AF },
                { -1, -1 },
            },
        },
        {
            0x4C05,
            {
                { 0x4C10, 0x2B9 },
                { 0x4C11, 0x267 },
                { 0x4C14, 0x279 },
                { 0x4C12, 0x294 },
                { 0x4C13, 0x282 },
                { 0x4C15, 0x270 },
                { 0x4C16, 0x28B },
                { 0x4C17, 0x2B0 },
                { -1, -1 },
            },
        },
        {
            0x4C06,
            {
                { 0x4C10, 0x2BA },
                { 0x4C11, 0x268 },
                { 0x4C14, 0x27A },
                { 0x4C12, 0x295 },
                { 0x4C13, 0x283 },
                { 0x4C15, 0x271 },
                { 0x4C16, 0x28C },
                { 0x4C17, 0x2B1 },
                { -1, -1 },
            },
        },
        {
            0x4C07,
            {
                { 0x4C10, 0x2BC },
                { 0x4C11, 0x26A },
                { 0x4C14, 0x27C },
                { 0x4C12, 0x297 },
                { 0x4C13, 0x285 },
                { 0x4C15, 0x273 },
                { 0x4C16, 0x28E },
                { 0x4C17, 0x2B3 },
                { -1, -1 },
            },
        },
        {
            0x4C08,
            {
                { 0x4C10, 0x2BB },
                { 0x4C11, 0x269 },
                { 0x4C14, 0x27B },
                { 0x4C12, 0x296 },
                { 0x4C13, 0x284 },
                { 0x4C15, 0x272 },
                { 0x4C16, 0x28D },
                { 0x4C17, 0x2B2 },
                { -1, -1 },
            },
        },
        {
            0x4C09,
            {
                { 0x4C18, 0x2A6 },
                { 0x4C19, 0x2A7 },
                { 0x4C1A, 0x2A8 },
                { 0x4C1B, 0x2A9 },
                { 0x4C1C, 0x2AA },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0A,
            {
                { 0x4C1D, 0x29B },
                { 0x4C1E, 0x298 },
                { 0x4C1F, 0x299 },
                { 0x4C20, 0x29A },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0B,
            {
                { 0x4C21, 0x29C },
                { 0x4C22, 0x29D },
                { 0x4C23, 0x29E },
                { 0x4C24, 0x29F },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0C,
            {
                { 0x4C25, 0x259 },
                { 0x4C26, 0x25B },
                { 0x4C27, 0x256 },
                { 0x4C28, 0x257 },
                { 0x4C29, 0x25D },
                { 0x4C2A, 0x2A3 },
                { 0x4C2B, 0x2A4 },
                { 0x4C2C, 0x2A2 },
                { -1, -1 },
            },
        },
        {
            0x4C0D,
            {
                { 0x4C2D, 0x258 },
                { 0x4C2E, 0x2A5 },
                { 0x4C2F, 0x2A0 },
                { 0x4C30, 0x2A1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0E,
            {
                { 0x4C31, 0x251 },
                { 0x4C32, 0x253 },
                { 0x4C33, 0x252 },
                { 0x4C34, 0x254 },
                { 0x4C35, 0x255 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x4C0F,
            {
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
    },
};

const OptMusicMenu option_musicTestTbl = {
    {
        {
            0x5D01,
            {
                { 0x5D0F, 0x3 },
                { 0x5D10, 0x9 },
                { 0x5D11, 0xB },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D02,
            {
                { 0x5D12, 0x4 },
                { 0x5D13, 0x7 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D03,
            {
                { 0x5D14, 0x8 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D04,
            {
                { 0x5D17, 0x18 },
                { 0x5D18, 0x19 },
                { 0x5D19, 0x1A },
                { 0x5D1A, 0x1B },
                { 0x5D1B, 0x1C },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D05,
            {
                { 0x5D1D, 0x1E },
                { 0x5D1E, 0x1F },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D06,
            {
                { 0x5D20, 0xD },
                { 0x5D21, 0x12 },
                { 0x5D22, 0x17 },
                { 0x5D23, 0x24 },
                { 0x5D24, 0x13 },
                { 0x5D25, 0xF },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D07,
            {
                { 0x5D26, 0x10 },
                { 0x5D27, 0x3E },
                { 0x5D28, 0x14 },
                { 0x5D29, 0x15 },
                { 0x5D2A, 0x16 },
                { 0x5D2B, 0x46 },
                { 0x5D2C, 0x47 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D08,
            {
                { 0x5D2D, 0x2D },
                { 0x5D2E, 0x2E },
                { 0x5D2F, 0x2F },
                { 0x5D30, 0x30 },
                { 0x5D31, 0x31 },
                { 0x5D32, 0x32 },
                { 0x5D33, 0x33 },
                { 0x5D34, 0x34 },
                { -1, -1 },
            },
        },
        {
            0x5D09,
            {
                { 0x5D35, 0x35 },
                { 0x5D36, 0x36 },
                { 0x5D37, 0x37 },
                { 0x5D38, 0x38 },
                { 0x5D39, 0x44 },
                { 0x5D3A, 0x43 },
                { 0x5D3B, 0x42 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0A,
            {
                { 0x5D3D, 0xA },
                { 0x5D3E, 0x39 },
                { 0x5D3F, 0x3A },
                { 0x5D40, 0x3B },
                { 0x5D41, 0x26 },
                { 0x5D42, 0x21 },
                { 0x5D43, 0x2C },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0B,
            {
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
        {
            0x5D0C,
            {
                { 0x5D48, 0x3C },
                { 0x5D49, 0x3D },
                { 0x5D4A, 0x48 },
                { 0x5D4B, 0x45 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
                { -1, -1 },
            },
        },
    },
};

u16 option_CameraDebugExec(s32 value) {
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (HuPadBtnDown[0] & Z_TRIG) {
            cam = Hu3DData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return HuPadBtnDown[0];
}

void option_SeObjInit(void) {
    option_seWork.obj = NULL;
}

s32 option_SeObjCheck(void) {
    return option_seWork.obj != NULL;
}

void option_SeObjKill(void) {
    s16 modelId;

    if (option_seWork.obj != NULL) {
        modelId = option_MenuMdlIdGet(2);
        Hu3DModelAnimStop(Hu3DData[modelId].hmf);
        HuAudFXStop((s16)option_seWork.seNo);
        omDelObj(option_seWork.obj);
        option_seWork.obj = NULL;
    }
}

void option_SeObjMain(omObjData *obj) {
    s16 modelId;

    if (msmSeGetStatus(option_seWork.seNo) == 0) {
        modelId = option_MenuMdlIdGet(2);
        Hu3DModelAnimStop(Hu3DData[modelId].hmf);
        HuAudFXStop((s16)option_seWork.seNo);
        omDelObj(obj);
        option_seWork.obj = NULL;
    }
}

omObjData *option_SeObjCreate(s32 seNo) {
    if (option_seWork.obj != NULL) {
        omDelObj(option_seWork.obj);
    }
    option_seWork.obj = omAddObj(6, 0, 0, -1, option_SeObjMain);
    option_seWork.seNo = seNo;
    msmSeGetStatus(seNo);
    return option_seWork.obj;
}

void option_RumbleObjMain(omObjData *obj) {
    s32 *counter;

    if (option_rumbleCnt == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &option_rumbleCnt;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

void option_RumbleStart(void) {
    option_rumbleCnt = 0;
    omAddObj(6, 0, 0, -1, option_RumbleObjMain);
}

s32 option_MgTypeUnlockCheck(void) {
    s32 type;
    s16 counts[9];
    s16 i;
    s16 minigameType;

    for (i = 0; i < 9; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        minigameType = mgDataTbl[i].minigameType;
        if ((mgDataTbl[i].overlay == 0x70) | (mgDataTbl[i].overlay == -1)) {
            continue;
        }
        if ((i == 27) | (i == 8)) {
            continue;
        }
        if (i == 16) {
            continue;
        }
        type = minigameType;
        if (type < 5 && GWMgUnlockCheck(i) != 0) {
            if (++counts[type] >= 3) {
                return 1;
            }
        }
    }
    return 0;
}
