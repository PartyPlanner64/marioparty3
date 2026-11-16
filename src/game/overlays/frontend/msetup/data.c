#include "common.h"
#include "msetup_internal.h"

extern const char msetup_waluigiDefStr[];
extern const char msetup_dkDefStr[];
extern const char msetup_warioDefStr[];
extern const char msetup_yoshiDefStr[];
extern const char msetup_daisyDefStr[];
extern const char msetup_peachDefStr[];
extern const char msetup_luigiDefStr[];
extern const char msetup_marioDefStr[];
extern const char msetup_waluigiStr[];
extern const char msetup_dkStr[];
extern const char msetup_warioStr[];
extern const char msetup_yoshiStr[];
extern const char msetup_daisyStr[];
extern const char msetup_peachStr[];
extern const char msetup_luigiStr[];
extern const char msetup_marioStr[];
extern const char msetup_comLevelEachStr[];
extern const char msetup_comLevelAllStr[];
extern const char msetup_comLevelVeryHardStr[];
extern const char msetup_comLevelHardStr[];
extern const char msetup_comLevelNormalStr[];
extern const char msetup_comLevelEasyStr[];

u16 msetup_exitCnt = 0;

s16 msetup_exitRumbleF = 0;

f32 msetup_cameraFov = 58.0f;

s8 msetup_cameraLookF = 0;

u8 msetup_exitRumbleCnt = 10;

u32 msetup_randSeed = 0;

Process *msetup_summaryProc = NULL;

s32 msetup_stageMdlFileTbl[] = {0x140001, 0x14000C, 0x14000D};

omObjData *msetup_backObj = NULL;

s16 (*msetup_partyStepTbl[])(s16) = {
    msetup_PartyPlayerNumStep,
    msetup_PartyChrStep,
    msetup_PartyComLevelStep,
    msetup_PartyHandicapStep,
    msetup_PartyBoardStep,
    msetup_PartyTurnStep,
    msetup_PartyMgPackStep,
    msetup_PartyBonusStep,
    msetup_PartyConfirmStep,
};

s16 (*msetup_duelStepTbl[])(s16) = {msetup_DuelPlayerNumStep, msetup_DuelChrStep, msetup_DuelComLevelStep, msetup_DuelHandicapStep, msetup_DuelBoardStep, msetup_DuelTurnStep, msetup_DuelMgPackStep, msetup_DuelConfirmStep};

u8 msetup_storyBoardTbl[] = {
    0, 0, 1, 1, 2, 2, 3, 3,
    4, 4, 5, 5, 5, 5, 0, 0,
};

u8 msetup_storyStageKindTbl[] = {
    0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 0, 2, 2, 0, 0,
};

u8 msetup_storyRivalTbl[] = {
    4, 4, 3, 3, 5, 5, 2, 2,
    0, 0, 7, 6, 6, 0, 0, 0,
};

s32 msetup_storyPartyBoardMesTbl[] = {0x1A01, 0x1A02, 0x1A03, 0x1A04, 0x1A05, 0x1A06};

s32 msetup_storyDuelBoardMesTbl[] = {0x2901, 0x2902, 0x2903, 0x2904, 0x2905, 0x2906};

s32 msetup_storyDuelRivalMesTbl[] = {0x290D, 0x290F, 0x290C, 0x290A, 0x2909, 0x290B, 0x290E, 0x290E};

s32 msetup_storyDuelLuigiMesTbl[] = {0x290F, 0x2910, 0x2911, 0x2912, 0x2913, 0x2913};

s16 (*msetup_mgModeStepTbl[])(s16) = {msetup_MgModeIntroStep, msetup_PartyPlayerNumStep, msetup_PartyChrStep, msetup_PartyComLevelStep, msetup_MgModeConfirmStep};

s16 (*msetup_mgMode1PStepTbl[])(s16) = {msetup_MgMode1PIntroStep, msetup_MgMode1PChrStep, msetup_MgMode1PComLevelStep, msetup_MgMode1PConfirmStep};

s32 msetup_tutorialPartyMesTbl[] = {0x1701, 0x1702, 0x1703, 0x1704, 0x1705};

s32 msetup_tutorialDuelMesTbl[] = {0x2601, 0x2602, 0x2603, 0x2604, 0x2605};

void (*msetup_setupProcTbl[])(void) = {
    msetup_PartySetupProc,
    msetup_DuelSetupProc,
    msetup_StoryPartySetupProc,
    msetup_StoryDuelSetupProc,
    msetup_StorySetupProc,
    msetup_MgModeSetupProc,
    msetup_MgMode1PSetupProc,
    msetup_TutorialPartySetupProc,
    msetup_TutorialDuelSetupProc,
};

ModeCameraPreset msetup_cameraPreset = {{270.0f, 0.0f, 0.0f}, {0.0f, 200.0f, 0.0f}, 130.0f, 50.0f};

MsetupCameraKeyframe msetup_cameraIntroKeyTbl[] = {
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 130.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 130.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 450.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1000.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 166.5f, 70.0f}, 700.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

MsetupCameraKeyframe msetup_cameraCancelKeyTbl[] = {
    {{{{-8.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{-8.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{68.0f, 0.0f, 0.0f}, {0.0f, 166.5f, 70.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 810.0f, 50.0f}}, 0.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1960.0f, 150.0f}}, 0.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1960.0f, 150.0f}}, 0.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

MsetupCameraKeyframe msetup_cameraStartKeyTbl[] = {
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 1800.0f, 156.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 1800.0f, 156.0f}}, 1.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

/* Padding between the camera paths and the model data. */
s32 msetup_cameraKeyPad[2] = {0, 0};

s16 msetup_shadowMdl = -1;

MsetupModelEntry msetup_tumbleMdlEntryTbl[] = {
    {0xA0075, 0x2AD, 0, 2, 1, {184.0f, 0.0f, 77.0f}, {0.0f, -30.0f, 0.0f}},
    {0xA0077, 8, 0, 0, 0, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {0xA0078, 8, 0, 0, 0, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {9, 0x29D, 0, 0, 1, {184.0f, 0.0f, 77.0f}, {0.0f, 0.0f, 0.0f}},
};

s32 msetup_chrMdlFileTbl[] = {0x200A1, 0x300A2, 0x700A2, 0x400A2, 0x500A1, 0x600A1, 0x800A1, 0x90003};

u8 msetup_chrAnimAltTbl[] = {1, 0, 0, 0, 1, 1, 1, 0};

s32 msetup_chrMotEnterTbl[] = {0x20025, 0x30025, 0x70025, 0x40025, 0x50025, 0x60025, 0x80025, 0x70025};

s32 msetup_chrMotEnterAltTbl[] = {
    0x20033, 0x30033, 0x70033, 0x40033, 0x50033, 0x60033, 0x80033, 0x9000B,
    0x20072, 0x30072, 0x70072, 0x40072, 0x50072, 0x60072, 0x80072, 0x70072,
};

s32 msetup_chrMotStartTbl[] = {0x2004E, 0x3004E, 0x7004E, 0x4004E, 0x5004E, 0x6004E, 0x8004E, 0x90013};

Vec msetup_playerPosTbl[] = {
    {-272.0f, 0.0f, -16.0f},
    {-136.0f, 0.0f, -16.0f},
    {0.0f, 0.0f, -16.0f},
    {136.0f, 0.0f, -16.0f},
};

Vec msetup_duelPlayerPosTbl[] = {
    {-184.0f, 0.0f, -16.0f},
    {88.0f, 0.0f, -16.0f},
};

f32 msetup_playerRotTbl[] = {22.0f, 12.0f, 0.0f, -12.0f};

f32 msetup_duelPlayerRotTbl[] = {16.0f, -5.0f};

s16 msetup_playerAppearDelayTbl[] = {5, 5, 0, 0, 0, 5, 5, 5};

s32 msetup_comLevelIconTbl[] = {0x14001D, 0x14001E, 0x14001F, 0x140020};

s32 msetup_handicapIconTbl[] = {
    0x140025, 0x140026, 0x140027, 0x140028, 0x140029, 0x14002A, 0x14002B, 0x14002C,
    0x14002D, 0x14002E,
};

s32 msetup_duelHandicapIconTbl[] = {0x14002F, 0x140030, 0x140031, 0x140032, 0x140033};

u8 msetup_playerIconTPLvlTbl[] = {255, 255, 255, 0};

u16 msetup_chrMotEnterAltMask = 76;

s32 msetup_cursorSprTbl[] = {0x140043, 0x140044, 0x140045, 0x140046, 0x140047, 0, 0, 0};

omObjData *msetup_effObj = NULL;

f32 msetup_effParamA = 5.0f;

f32 msetup_effParamB = 20.0f;

f32 msetup_effFallSpeed = 10.0f;

f32 msetup_effParamUnusedTbl[] = {8.0f, 40.0f, 20.0f};

f32 msetup_summaryScaleTbl[] = {1.0f, 1.0f, 1.0f, 0.0f, 0.0f};

Vec msetup_panelStartPos = {0.0f, -265.0f, -467.0f};

s32 msetup_comLevelCursorSprTbl[] = {0x11000E, 0x30};

s32 msetup_playerNumMesTbl[] = {0x1504, 0x1505, 0x1506, 0x1507};

s32 msetup_chrInfoSprTbl[] = {0x140035, 0x1300D3, 0x1300D2, 0x1300D4, 0x1300CF, 0x1300CF, 0x1300CF};

s16 msetup_chrInfoPosTbl[][2] = {
    {136, 144},
    {81, 136},
    {81, 149},
    {81, 162},
    {91, 136},
    {91, 149},
    {91, 162},
    {53, 148},
    {136, 144},
    {136, 144},
    {136, 144},
    {136, 144},
};

s16 msetup_chrInfoWinTbl[][4] = {
    {94, 119, 152, 62},
    {108, 104, 120, 31},
};

s32 msetup_chrInfoPortraitTbl[] = {
    0x140036, 0x140037, 0x140038, 0x14003C, 0x14003A, 0x140039, 0x14003B, 0x14003D,
    0x14003E, 0x14003F, 0x140040, 0x140041,
};

s32 msetup_chrInfoMesTbl[] = {0x241E, 0x241F, 0x2420, 0x2424, 0x2422, 0x2421, 0x2423, 0x2425};

s32 msetup_chrInfoSubMesTbl[] = {0x2426, 0x2427, 0x2428, 0x242C, 0x242A, 0x2429, 0x242B, 0x242D};

u8 msetup_chrInfoStatTbl[][3] = {
    {1, 2, 1},
    {2, 1, 2},
    {1, 1, 1},
    {2, 2, 5},
    {2, 1, 3},
    {1, 1, 3},
    {0, 4, 3},
    {3, 1, 5},
};

MsetupModelTarget msetup_chrSelPanelOpenTbl[] = {
    {{350.0f, 300.0f, -467.0f}, 0.0f},
    {{-350.0f, 300.0f, -467.0f}, 0.0f},
};

MsetupModelTarget msetup_panelCloseTbl[] = {
    {{0.0f, 300.0f, -467.0f}, 90.0f},
    {{0.0f, 300.0f, -467.0f}, 270.0f},
};

u8 msetup_chrSlotTbl[] = {0, 1, 2, 7, 3, 4, 5, 6};

s32 msetup_chrSelOnSprTbl[] = {
    0x140014, 0x140015, 0x140016, 0x14001B, 0x140017, 0x140018, 0x140019, 0x14001A,
    -0x7FEE58C8, -0x7FEE58D4, -0x7FEE58E0, -0x7FEE58EC, -0x7FEE58F8, -0x7FEE5904, -0x7FEE5910, -0x7FEE591C,
};

s16 msetup_chrVoiceSeTbl[] = {693, 694, 695, 700, 696, 697, 698, 699};

s32 msetup_chrNameMesTbl[] = {0x150C, 0x150D, 0x150E, 0x1512, 0x150F, 0x1510, 0x1511, 0x1513};

s32 msetup_chrNameDuelMesTbl[] = {0x2407, 0x2408, 0x2409, 0x240D, 0x240A, 0x240B, 0x240C, 0x240E};

s32 msetup_chrNameMgModeMesTbl[] = {0x490C, 0x490D, 0x490E, 0x4912, 0x490F, 0x4910, 0x4911, 0x4913};

s32 msetup_chrNameMgMode1PMesTbl[] = {
    0x4A06, 0x4A07, 0x4A08, 0x4A0C, 0x4A09, 0x4A0A, 0x4A0B, 0x4A0D,
    0x700035, 0x910035, 0xB20035, 0xD30035, 0x700055, 0x910055, 0xB20055, 0xD30055,
    0x140006, 0x14000B,
};

const char *msetup_chrNodeNameTbl[] = {msetup_marioStr, msetup_luigiStr, msetup_peachStr, msetup_daisyStr, msetup_yoshiStr, msetup_warioStr, msetup_dkStr, msetup_waluigiStr};

s32 msetup_chrSelSprTbl[] = {0x130036, 0x130037, 0x130038, 0x13003D, 0x130039, 0x13003A, 0x13003B, 0x13003C};

s32 msetup_chrSelMesTbl[] = {0x1508, 0x150B, 0x150A, 0x1509};

s32 msetup_chrSelDuelMesTbl[] = {0x1508, 0x2406, 0x2406, 0x2406};

MsetupModelTarget msetup_comLevelPanelOpenTbl[] = {
    {{350.0f, 300.0f, -467.0f}, 0.0f},
    {{-350.0f, 300.0f, -467.0f}, 0.0f},
};

s16 msetup_comLevelModeCursorPosTbl[][2] = {
    {98, 50},
    {98, 84},
};

s16 msetup_comLevelCursorPosTbl[][2] = {
    {108, 64},
    {165, 64},
    {222, 64},
};

s16 msetup_comLevel4CursorPosTbl[][2] = {
    {98, 64},
    {143, 64},
    {188, 64},
    {233, 64},
};

s16 (*msetup_comLevelCursorPosTblTbl[])[2] = {msetup_comLevelModeCursorPosTbl, msetup_comLevelCursorPosTbl, msetup_comLevel4CursorPosTbl};

s32 msetup_comLevelModeMesTbl[] = {0x1515, 0x1516};

const char *msetup_comLevelNodeNameTbl[] = {msetup_comLevelEasyStr, msetup_comLevelNormalStr, msetup_comLevelHardStr, msetup_comLevelVeryHardStr, msetup_comLevelAllStr, msetup_comLevelEachStr};

s32 msetup_comLevelSprTbl[] = {0x140059, 0x14005A, 0x14005B, 0x14005C, 0x140057, 0x140058};

s16 msetup_comLevelSprFirstTbl[] = {4, 0};

s16 msetup_comLevelSprLastTbl[] = {5, 3};

s32 msetup_handicapChoiceMesTbl[] = {0x1519, 0x151A, 0x151B};

s32 msetup_bonusChoiceMesTbl[] = {0x152A, 0x152B, 0x152C};

s32 msetup_duelHandicapChoiceMesTbl[] = {0x2410, 0x2411, 0x2412};

s32 msetup_mgPackDuelMesTbl[] = {0x2431, 0x2432, 0x2433};

s32 msetup_mgPackMesTbl[] = {0x1530, 0x1531, 0x1532};

s32 msetup_boardPartySprTbl[] = {0x140048, 0x140049, 0x14004A, 0x14004B, 0x14004C, 0x14004D};

s32 msetup_boardDuelSprTbl[] = {0x140051, 0x140052, 0x140053, 0x140054, 0x140055, 0x140056};

s32 msetup_boardPartyMesTbl[] = {0x151E, 0x151F, 0x1520, 0x1521, 0x1522, 0x1523, 0x151D};

s32 msetup_boardDuelMesTbl[] = {0x2415, 0x2416, 0x2417, 0x2418, 0x2419, 0x241A, 0x2414};

s32 msetup_storyBoardPartyMesTbl[] = {0x1A11, 0x1A12, 0x1A13, 0x1A14, 0x1A15, 0x1A16};

s32 msetup_storyBoardDuelMesTbl[] = {
    0x291B, 0x291C, 0x291D, 0x291E, 0x291F, 0x2920, -0xFEFC01, 0x20102FF,
    0x3FF, -1,
};

s32 msetup_turnMesTbl[] = {0x1525, 0x1526, 0x1527, 0x1528};

f32 msetup_turnDialAngleTbl[] = {288.0f, 216.0f, 144.0f, 72.0f, 0.0f};

f32 msetup_duelTurnDialAngleTbl[] = {288.0f, 72.0f, 0.0f};

s16 msetup_turnNumTbl[] = {20, 35, 50, -1, -1, 0};

s16 msetup_turnCustomNumTbl[] = {
    10, 15, 20, 25, 30, 35, 40, 45,
    50, 0,
};

s32 msetup_duelTurnMesTbl[] = {0x242F, 0x2430};

MsetupModelTarget msetup_duelPlayerNumPanelOpenTbl[] = {
    {{-144.0f, 300.0f, -467.0f}, 180.0f},
    {{144.0f, 300.0f, -467.0f}, 180.0f},
};

MsetupModelTarget msetup_duelPlayerNumPanelCloseTbl[] = {
    {{0.0f, 300.0f, -467.0f}, 270.0f},
    {{0.0f, 300.0f, -467.0f}, 90.0f},
};

s32 msetup_duelPlayerNumMesTbl[] = {0x2404, 0x2405};

s32 msetup_duelPlayerNumAnimTbl[] = {0x14004E, 0x14004F};

s16 msetup_duelHandicapTbl[] = {1, 2, 3, 4, 5, 0};

s16 (*msetup_menuFuncTbl[])(MsetupMenuState *) = {
    msetup_MenuIdle,
    msetup_PlayerNumSelect,
    msetup_ChrSelect,
    msetup_ComLevelSelect,
    msetup_HandicapSelect,
    msetup_TurnSelect,
    msetup_HandicapChoice,
    msetup_BonusChoice,
    msetup_BoardSelect,
    msetup_DuelPlayerNumSelect,
    msetup_DuelHandicapSelect,
    msetup_DuelHandicapChoice,
    msetup_StoryBoardShow,
    msetup_MgPackChoice,
};

Vec msetup_panelPosTbl[] = {
    {0.0f, 270.0f, -377.0f},
    {190.0f, 300.0f, -467.0f},
    {0.0f, 330.0f, -557.0f},
    {-190.0f, 300.0f, -467.0f},
};

s16 msetup_panelOrderTbl[4][4] = {
    {0, 1, 2, 3},
    {3, 0, 1, 2},
    {2, 3, 0, 1},
    {1, 2, 3, 0},
};

s16 msetup_panelOrder3Tbl[4][4] = {
    {0, 1, 3, 2},
    {3, 0, 1, 2},
    {1, 3, 0, 2},
    {3, 0, 1, 2},
};

s32 msetup_playerNumAnimTbl[] = {0x14000E, 0x14000F, 0x140010, 0x140011};

f32 msetup_panelRotTbl[] = {180.0f, 0.0f, 0.0f, 0.0f};

f32 msetup_playerNumTbl[] = {1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 0.0f};

s16 msetup_storyChrVoiceSeTbl[] = {693, 694, 695, 696, 697, 698};

Vec msetup_storyChrMenuPosTbl[] = {
    {-1000.0f, 700.0f, -700.0f},
    {-85.0f, -8.0f, 2.0f},
    {-341.0f, 133.0f, -534.0f},
    {-410.0f, -50.0f, -534.0f},
};

Vec msetup_storyLevelMenuPosTbl[] = {
    {1100.0f, 510.0f, -745.0f},
    {82.0f, 13.0f, 6.0f},
    {357.0f, -31.0f, -366.0f},
    {370.0f, -65.0f, -366.0f},
};

Vec msetup_storyMgPackMenuPosTbl[] = {
    {0.0f, 700.0f, 2.0f},
    {0.0f, -8.0f, 2.0f},
    {0.0f, 700.0f, 2.0f},
    {0.0f, 205.0f, -534.0f},
};

Vec *msetup_storyMenuPosTblTbl[] = {msetup_storyChrMenuPosTbl, msetup_storyLevelMenuPosTbl, msetup_storyMgPackMenuPosTbl};

MsetupStorySprite msetup_storyChrBackTbl[] = {
    {0x140065, {129.0f, -84.0f, 0.0f}},
    {0x140065, {126.0f, 85.0f, 0.0f}},
    {0x140065, {-127.0f, 93.0f, 0.0f}},
    {0x140065, {-139.0f, -73.0f, 0.0f}},
    {0x140066, {142.0f, 0.0f, 0.0f}},
    {0x140066, {46.0f, 106.0f, 0.0f}},
    {0x140066, {-39.0f, 111.0f, 0.0f}},
    {0x140066, {-143.0f, 4.0f, 0.0f}},
    {0x140066, {-62.0f, -92.0f, 0.0f}},
    {0x140066, {27.0f, -95.0f, 0.0f}},
};

MsetupStorySprite msetup_storyLevelBackTbl[] = {
    {0x140065, {81.0f, -99.0f, 0.0f}},
    {0x140065, {79.0f, 104.0f, 0.0f}},
    {0x140065, {-88.0f, 106.0f, 0.0f}},
    {0x140065, {-84.0f, -108.0f, 0.0f}},
    {0x140066, {94.0f, -36.0f, 0.0f}},
    {0x140066, {114.0f, 41.0f, 0.0f}},
    {0x140066, {0.0f, 111.0f, 0.0f}},
    {0x140066, {-92.0f, 16.0f, 0.0f}},
    {0x140066, {-115.0f, -42.0f, 0.0f}},
    {0x140066, {6.0f, -122.0f, 0.0f}},
};

MsetupStorySprite msetup_storyMgPackBackTbl[] = {
    {0x140064, {0.0f, 0.0f, 0.0f}},
    {0x140065, {129.0f, -84.0f, 0.0f}},
    {0x140065, {126.0f, 85.0f, 0.0f}},
    {0x140065, {-127.0f, 93.0f, 0.0f}},
    {0x140065, {-139.0f, -73.0f, 0.0f}},
    {0x140066, {142.0f, 0.0f, 0.0f}},
    {0x140066, {46.0f, 106.0f, 0.0f}},
    {0x140066, {-39.0f, 111.0f, 0.0f}},
    {0x140066, {-143.0f, 4.0f, 0.0f}},
    {0x140066, {-62.0f, -92.0f, 0.0f}},
    {0x140066, {27.0f, -95.0f, 0.0f}},
};

Vec msetup_storyMenuMdlOfsTbl[] = {
    {-30.0f, 190.0f, 0.0f},
    {30.0f, 170.0f, 0.0f},
    {-30.0f, 190.0f, 0.0f},
};

Vec msetup_storyMenuMdlRotTbl[] = {
    {20.0f, 25.0f, 0.0f},
    {20.0f, 335.0f, 0.0f},
    {20.0f, 25.0f, 0.0f},
};

u8 msetup_storyChrTbl[] = {0, 1, 2, 3, 4, 5, 0, 0};

MsetupStorySprite msetup_storyChrOptTbl[] = {
    {0x14005D, {0.0f, 0.0f, 0.0f}},
    {0x140014, {-102.0f, 50.0f, 0.0f}},
    {0x140015, {0.0f, 50.0f, 0.0f}},
    {0x140016, {105.0f, 50.0f, 0.0f}},
    {0x140017, {-102.0f, -55.0f, 0.0f}},
    {0x140018, {0.0f, -55.0f, 0.0f}},
    {0x140019, {105.0f, -55.0f, 0.0f}},
};

MsetupStorySprite msetup_storyLevel4OptTbl[] = {
    {0x14005E, {0.0f, 0.0f, 0.0f}},
    {0x14005F, {0.0f, 95.0f, 0.0f}},
    {0x140060, {0.0f, 33.0f, 0.0f}},
    {0x140061, {0.0f, -30.0f, 0.0f}},
    {0x140062, {0.0f, -93.0f, 0.0f}},
};

MsetupStorySprite msetup_storyLevelOptTbl[] = {
    {0x14005E, {0.0f, 0.0f, 0.0f}},
    {0x14005F, {0.0f, 95.0f, 0.0f}},
    {0x140060, {0.0f, 33.0f, 0.0f}},
    {0x140061, {0.0f, -30.0f, 0.0f}},
    {0x140063, {0.0f, -93.0f, 0.0f}},
};

MsetupStorySprite msetup_storyMgPackOptTbl[] = {
    {0x14006A, {-90.0f, 0.0f, 0.0f}},
    {0x14006B, {90.0f, 0.0f, 0.0f}},
    {0x140069, {-90.0f, 0.0f, 0.0f}},
    {0x140069, {90.0f, 0.0f, 0.0f}},
};

s32 msetup_storyCursorSprTbl[] = {0x11000E, 0x30, 0x11000E};

s16 msetup_storyChrCursorPosTbl[][2] = {
    {90, 95},
    {130, 95},
    {170, 95},
    {90, 135},
    {130, 135},
    {170, 135},
};

s16 msetup_storyLevelCursorPosTbl[][2] = {
    {146, 77},
    {146, 102},
    {146, 127},
    {146, 152},
};

s16 msetup_storyMgPackCursorPosTbl[][2] = {
    {124, 100},
    {194, 100},
};

s16 (*msetup_storyCursorPosTblTbl[])[2] = {msetup_storyChrCursorPosTbl, msetup_storyLevelCursorPosTbl, msetup_storyMgPackCursorPosTbl};

u8 msetup_storyMenuSelInitTbl[] = {0, 1, 0, 0};

ModeCameraPreset msetup_storyCameraPreset = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 650.0f, 50.0f};

/* Align the following rodata to 16 bytes. */
s32 msetup_storyCameraPad[] = {0, 0, 0};
