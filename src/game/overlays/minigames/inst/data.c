#include "inst.h"

extern const char inst_chrNode13Name[];
extern const char inst_chrNode12Name[];
extern const char inst_chrNode11Name[];
extern const char inst_chrNode10Name[];
extern const char inst_chrNode09Name[];
extern const char inst_chrNode08Name[];
extern const char inst_chrNode07Name[];
extern const char inst_chrNode06Name[];
extern const char inst_plateHookLastName[];
extern const char inst_plateHookMidoriName[];
extern const char inst_plateHookAkaName[];
extern const char inst_plateHookAoName[];

s8 inst_playerOrderTbl[4] = {0, 1, 2, 3};
s8 inst_mainDoneF = 0;
s8 inst_mainUnusedF = 0;
s8 inst_practiceStartF = 0;
s8 inst_practiceRetF = 0;
s8 inst_introSkipF = 0;
s8 inst_startF = 0;
s8 inst_mgType = 0;
s8 inst_mgNo = 0;
s8 inst_itemPrizeTbl[5] = {0};
s8 inst_hostNo = 0;
f32 inst_cameraTilt = 45.0f;
Vec inst_cameraPos = {0.0f, 0.0f, 0.0f};
Vec inst_cameraTarget = {0.0f, 0.0f, 0.0f};
Vec inst_cameraUp = {0.0f, 1.0f, -0.000001f};
s32 inst_mainState = 0;
s32 inst_winOpenF = 0;
Vec inst_cameraPosTbl[4] = {
    {70.0f, 560.0f, 1210.0f},
    {0.0f, 560.0f, 1210.0f},
    {0.0f, 470.0f, 830.0f},
    {67.5f, 300.0f, 537.5f},
};
Vec inst_cameraTargetTbl[4] = {
    {70.0f, 0.0f, -210.0f},
    {0.0f, 0.0f, -210.0f},
    {0.0f, 0.0f, -10.0f},
    {67.5f, 50.0f, 37.5f},
};
s32 inst_picNo = 0;
s8 inst_exitWipeF = 0;
u32 inst_cameraMoveTime = 0;
u8 inst_itemPrizeATbl[8] = {0, 1, 4, 5, 8, 10, 12, 14};
u8 inst_itemPrizeBTbl[8] = {1, 2, 3, 6, 7, 9, 13, 11};

/* The records have varying node counts and share the InstModelHooks prefix. */
InstModelHooks *inst_hookTbl[][2] = {
    {(InstModelHooks *)&inst_mg4PPlayerHooks, (InstModelHooks *)&inst_mg4PItemHooks},
    {(InstModelHooks *)&inst_mg2vs2PlayerHooks, (InstModelHooks *)&inst_mg2vs2ItemHooks},
    {(InstModelHooks *)&inst_mg3vs1PlayerHooks, (InstModelHooks *)&inst_mg3vs1ItemHooks},
    {(InstModelHooks *)&inst_battlePlayerHooks, (InstModelHooks *)&inst_battleItemHooks},
    {(InstModelHooks *)&inst_duelPlayerHooks, (InstModelHooks *)&inst_duelItemHooks},
    {(InstModelHooks *)&inst_itemPlayerHooks, (InstModelHooks *)&inst_itemItemHooks},
    {(InstModelHooks *)&inst_itemPlayerHooks, (InstModelHooks *)&inst_itemItemHooks},
    {(InstModelHooks *)&inst_omakePlayerHooks, (InstModelHooks *)&inst_omakeItemHooks},
    {(InstModelHooks *)&inst_lastPlayerHooks, (InstModelHooks *)&inst_lastItemHooks},
};

s32 inst_boxOpenCnt = 0;
f32 inst_picScaleOfs = 0.0f;
s32 inst_boxCloseCnt = 0;
/* Unused initialized storage between the per-object state blocks. */
s32 inst_boxPad[3] = {0};
s32 inst_hostWaitCnt = 0;
s32 inst_hostJumpCnt = 0;
s32 inst_hostPad[2] = {0};
s32 inst_itemHostWaitCnt = 0;
s32 inst_itemHostJumpCnt = 0;
s32 inst_itemHostPad[2] = {0};
s32 inst_battleHostWaitCnt = 0;
s32 inst_battleHostJumpCnt = 0;
s32 inst_battleHostPad[2] = {0};
s8 inst_openF = 0;
s8 inst_openDoneF = 0;
u8 inst_plateColorTbl[4] = {0};
s32 inst_playerCloseF = 0;
const char *inst_chrNodeNameTbl[8] = {
    inst_chrNode06Name, inst_chrNode07Name, inst_chrNode08Name, inst_chrNode09Name,
    inst_chrNode10Name, inst_chrNode11Name, inst_chrNode12Name, inst_chrNode13Name,
};
s32 inst_plateFileTbl[4] = {0x17002A, 0x17002B, 0x17002C, 0x17002D};
const char *inst_plateHookNameTbl[4] = {inst_plateHookAoName, inst_plateHookAkaName, inst_plateHookMidoriName, inst_plateHookLastName};
s32 inst_playerOpenCnt = 0;
s32 inst_playerCloseCnt = 0;
s32 inst_playerPad[3] = {0};
s8 inst_winStartF = 0;
s8 inst_practiceF = 0;
s32 inst_titleInCnt = 0;
s32 inst_titleY = -64;
s32 inst_titlePad = 0;
