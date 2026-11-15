#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/saveload.h"
#include "game/gamework.h"
#include "game/gameman.h"
#include "game/gamework_data.h"
#include "game/msm.h"
#include "game/saveEncode.h"
#include "game/eeprom.h"
#include "game/pad.h"
#include "gcc/memory.h"

#define SAVE_BOX_SIZE 0x2A0
#define SAVE_BOX_COUNT 3

// Offsets of each encoded region within a save box.
#define SAVE_OFS_BOARD (D_800D04B0_main)
#define SAVE_OFS_BOARD_PLAYERS (D_800D04B0_main + D_800CBB64_main)
#define SAVE_OFS_STORY_BOARD (D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4))
#define SAVE_OFS_STORY_BOARD_PLAYERS (SAVE_OFS_STORY_BOARD + D_800C9944_main)
#define SAVE_OFS_STORY_SYSTEM (SAVE_OFS_STORY_BOARD + (D_800C9944_main + D_800CCF54_main * 2))
#define SAVE_OFS_STORY (SAVE_OFS_STORY_SYSTEM + D_800C9944_main)
#define SAVE_OFS_STORY_PLAYERS (D_800CD6A4_main + SAVE_OFS_STORY)

static u8 D_800A1E80_main = 0;
u8 curBoxNo = 0;
static s16 D_800A1E82_main = 0;
static u8 D_800BBAB0_main;
extern SaveCommonBuf D_800D09A8_main;
extern u8 D_800D0450_main[];
extern u8 D_800D0E50_main[];
extern u8 gEncodedSaveBuffer[];
extern u16 D_800D04B0_main;
extern u16 D_800CBB64_main;
extern u16 D_800C9944_main;
extern u16 D_800CCF54_main;
extern u16 D_800CD6A4_main;
extern u16 D_800CE2C0_main;

void SLSaveDataInit(void) {
    GWInit();
    GWGameStatReset();
    GwCommon.languageIndex = 2;
    GwCommon.unk9F = 3;
    GwCommon.unkA2 = 3;
    GwCommon.unk9E = 3;
    GwCommon.unkA0 = 3;
    GwCommon.unkA1 = 3;
    D_800D09A8_main.flags &= ~1;
    D_800D09A8_main.boxNo = 0;
    if (D_800BBAB0_main) {
        ClearBoxBuf(curBoxNo);
        _SetFlag(0x2E);
        _SetFlag(0x2F);
        SLCommonSet(0);
        memset(D_800D0E50_main + D_800D04B0_main, 0, SAVE_BOX_SIZE - D_800D04B0_main);
        SLCheckSumBoxSet();
        WriteEepromBox(curBoxNo);
    }
}

s32 SLInit(void) {
    u8 formatted;
    s32 i;
    s32 failed;

    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) == 1) {
            break;
        }
    }
    if (i == 4) {
        D_800A1E80_main = 1;
    }

    if (D_800A1E82_main == 0) {
        D_800A1E82_main = 1;
        if (InitEeprom(&formatted) != 0) {
            D_800BBAB0_main = 0;
        } else {
            D_800BBAB0_main = 1;
        }
    }

    if (D_800BBAB0_main) {
        if (formatted == 1) {
            D_800D20EC_main = 0x1F;
        } else {
            D_800D20EC_main = 0;
        }

        failed = SLLoadCommon();
        if (D_800D09A8_main.checksum != CalcChecksumEeprom(D_800D0450_main, 0, 0x16)) {
            failed = 1;
        }
        if (failed) {
            memset(&D_800D09A8_main, 0, sizeof(SaveCommonBuf));
            D_800D09A8_main.boxNo = 0xFF;
            D_800D09A8_main.flags &= ~1;
            SLSaveCommon();
            D_800D20EC_main |= 8;
        }

        for (i = 0; i < SAVE_BOX_COUNT; i++) {
            SLCurBoxNoSet(i);
            failed = SLLoadGameStat();
            if (failed == 0 && SLCheckSumCheck() == 0) {
                failed = 1;
            }
            if (GwCommon.unk_00 == 0 && D_800D09A8_main.boxNo == i) {
                D_800D09A8_main.boxNo = 0xFF;
                SLSaveCommon();
            }
            if (GwCommon.unk_00 != 0 && (GwCommon.unk_00 != 0x91 || failed != 0)) {
                ClearEepromBoxHeader(i);
                D_800D20EC_main |= 1 << i;
            }
        }

        if (D_800D09A8_main.flags & 1) {
            msmSysSetOutputMode(1);
        } else {
            msmSysSetOutputMode(0);
        }
    } else {
        SLSaveDataInit();
        msmSysSetOutputMode(0);
        D_800D20EC_main = 0xFF;
    }

    GwSystem.minigame_index = 0;
    return D_800D20EC_main;
}

void SLStub0(void) {
}

void SLStub1(void) {
}

void SLStub2(void) {
}

void SLStub3(void) {
}

s32 SLCommonSet(s32 writeBox) {
    if (D_800BBAB0_main) {
        SetEepromBoxBuf(curBoxNo, 0, gEncodedSaveBuffer, SaveCommonEncode(&GwCommon));
        if (writeBox) {
            SLCheckSumBoxSet();
            return WriteEepromBox(curBoxNo);
        }
        return 0;
    }
    return 0;
}

s32 SLSaveBoard(s32 writeBox) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_BOARD, gEncodedSaveBuffer, SaveBoardSystemEncode(&GwSystem));
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += D_800CCF54_main;
        }
        if (writeBox) {
            SLCheckSumBoxSet();
            return WriteEepromBox(curBoxNo);
        }
        return 0;
    }
    return 0;
}

s32 SLSaveBoardStory(s32 writeBox) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY_BOARD, gEncodedSaveBuffer, SaveStorySystemEncode(&GwSystem));
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 2; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += D_800CCF54_main;
        }
        if (writeBox) {
            SLCheckSumBoxSet();
            return WriteEepromBox(curBoxNo);
        }
        return 0;
    }
    return 0;
}

s32 SLSaveStory(s32 writeBox) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        GwStory.unk64 = GwStory.unk0;
        GwStory.unk65 = GwStory.unk1;
        GwStory.unk66 = GwStory.unk2;
        GwStory.unk73 = GwStory.progress.fields.unkF;
        for (i = 0; i < 12; i++) {
            GwStory.unk67[i] = GwStory.progress.fields.unk3[i];
        }
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, SaveStoryEncode(&GwStory));
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY_SYSTEM, gEncodedSaveBuffer, SaveStorySystemEncode(&GwSystem));
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, SaveStoryEncode(&GwStory));
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += D_800CCF54_main;
        }
        if (writeBox) {
            SLCheckSumBoxSet();
            return WriteEepromBox(curBoxNo);
        }
        return 0;
    }
    return 0;
}

s32 SLSaveStorySystem(s32 writeBox) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY_SYSTEM, gEncodedSaveBuffer, SaveStorySystemEncode(&GwSystem));
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, SaveStoryEncode(&GwStory));
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += D_800CCF54_main;
        }
        if (writeBox) {
            SLCheckSumBoxSet();
            return WriteEepromBox(curBoxNo);
        }
        return 0;
    }
    return 0;
}

s32 SLLoadGameStat(void) {
    if (D_800BBAB0_main == 0) {
        return 0;
    }
    if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
        return 1;
    }
    SaveCommonDecode(D_800D0E50_main, &GwCommon);
    return 0;
}

s32 SLLoadBoard(void) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveBoardSystemDecode(D_800D0E50_main + SAVE_OFS_BOARD, &GwSystem);
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(D_800D0E50_main + offset, &GwPlayer[i]);
            offset += D_800CCF54_main;
        }
    }
    return 0;
}

s32 SLLoadBoardStory(void) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveStorySystemDecode(D_800D0E50_main + SAVE_OFS_STORY_BOARD, &GwSystem);
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(D_800D0E50_main + offset, &GwPlayer[i]);
            offset += D_800CCF54_main;
        }
        SLPadAssign();
    }
    return 0;
}

s32 SLLoadStory(void) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveStorySystemDecode(D_800D0E50_main + SAVE_OFS_STORY_SYSTEM, &GwSystem);
        SaveStoryDecode(D_800D0E50_main + SAVE_OFS_STORY, &GwStory);
        GwStory.unk0 = GwStory.unk64;
        GwStory.unk1 = GwStory.unk65;
        GwStory.unk2 = GwStory.unk66;
        GwStory.progress.fields.unkF = GwStory.unk73;
        for (i = 0; i < 12; i++) {
            GwStory.progress.fields.unk3[i] = GwStory.unk67[i];
        }
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(D_800D0E50_main + offset, &GwPlayer[i]);
            offset += D_800CCF54_main;
        }
    }
    return 0;
}

s32 SLLoadCommon(void) {
    return ReadEepromCommonBuf((u8 *)&D_800D09A8_main);
}

s32 SLSaveCommon(void) {
    D_800D09A8_main.checksum = CalcChecksumEeprom((u8 *)&D_800D09A8_main, 0, 0x16);
    return WriteEepromCommonBuf((u8 *)&D_800D09A8_main);
}

void SLCheckSumBoxSet(void) {
    u16 checksum = CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);

    SetEepromBoxBuf(curBoxNo, D_800CE2C0_main, (u8 *)&checksum, sizeof(checksum));
}

s32 SLCheckSumCheck(void) {
    u16 checksum;

    ReadEepromBox(curBoxNo, D_800CE2C0_main, (u8 *)&checksum, sizeof(checksum));
    return checksum == CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);
}

s32 SLBoxCopy(s16 srcBoxNo, s16 dstBoxNo) {
    s32 prevBoxNo = curBoxNo;

    SLCurBoxNoSet(srcBoxNo);
    if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
        SLCurBoxNoSet(prevBoxNo);
        return 1;
    }
    SLCurBoxNoSet(dstBoxNo);
    if (WriteEepromBox(curBoxNo) != 0) {
        SLCurBoxNoSet(prevBoxNo);
        return 1;
    }
    SLCurBoxNoSet(prevBoxNo);
    // The original has no return value on success.
}

void SLCurBoxNoSet(s32 boxNo) {
    curBoxNo = boxNo;
}

void SLPadAssign(void) {
    s8 used[4];
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        used[i] = 0;
    }
    used[GwPlayer[0].pad] = -1;
    used[GwPlayer[1].pad] = -1;
    for (i = 0, j = 2; i < 4; i++) {
        if (used[i] == 0) {
            GwPlayer[j].pad = i;
            j++;
        }
    }
}
