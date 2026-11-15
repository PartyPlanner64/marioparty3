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
#define SAVE_OFS_BOARD (saveCommonSize)
#define SAVE_OFS_BOARD_PLAYERS (saveCommonSize + saveBoardSystemSize)
#define SAVE_OFS_STORY_BOARD (saveCommonSize + (saveBoardSystemSize + savePlayerSize * 4))
#define SAVE_OFS_STORY_BOARD_PLAYERS (SAVE_OFS_STORY_BOARD + saveStorySystemSize)
#define SAVE_OFS_STORY_SYSTEM (SAVE_OFS_STORY_BOARD + (saveStorySystemSize + savePlayerSize * 2))
#define SAVE_OFS_STORY (SAVE_OFS_STORY_SYSTEM + saveStorySystemSize)
#define SAVE_OFS_STORY_PLAYERS (saveStorySize + SAVE_OFS_STORY)

static u8 SLNoPadF = 0;
u8 curBoxNo = 0;
static s16 SLInitF = 0;
static u8 SaveEnableF;
extern SaveCommonBuf saveCommonBuf;
extern u8 eepCommonBuf[];
extern u8 eepBoxBuf[];
extern u8 gEncodedSaveBuffer[];
extern u16 saveCommonSize;
extern u16 saveBoardSystemSize;
extern u16 saveStorySystemSize;
extern u16 savePlayerSize;
extern u16 saveStorySize;
extern u16 saveChecksumOfs;

void SLSaveDataInit(void) {
    GWInit();
    GWGameStatReset();
    GwCommon.languageIndex = 2;
    GwCommon.unk9F = 3;
    GwCommon.unkA2 = 3;
    GwCommon.unk9E = 3;
    GwCommon.unkA0 = 3;
    GwCommon.unkA1 = 3;
    saveCommonBuf.flags &= ~1;
    saveCommonBuf.boxNo = 0;
    if (SaveEnableF) {
        ClearBoxBuf(curBoxNo);
        _SetFlag(0x2E);
        _SetFlag(0x2F);
        SLCommonSet(0);
        memset(eepBoxBuf + saveCommonSize, 0, SAVE_BOX_SIZE - saveCommonSize);
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
        SLNoPadF = 1;
    }

    if (SLInitF == 0) {
        SLInitF = 1;
        if (InitEeprom(&formatted) != 0) {
            SaveEnableF = 0;
        } else {
            SaveEnableF = 1;
        }
    }

    if (SaveEnableF) {
        if (formatted == 1) {
            SLFormatFlags = 0x1F;
        } else {
            SLFormatFlags = 0;
        }

        failed = SLLoadCommon();
        if (saveCommonBuf.checksum != CalcChecksumEeprom(eepCommonBuf, 0, 0x16)) {
            failed = 1;
        }
        if (failed) {
            memset(&saveCommonBuf, 0, sizeof(SaveCommonBuf));
            saveCommonBuf.boxNo = 0xFF;
            saveCommonBuf.flags &= ~1;
            SLSaveCommon();
            SLFormatFlags |= 8;
        }

        for (i = 0; i < SAVE_BOX_COUNT; i++) {
            SLCurBoxNoSet(i);
            failed = SLLoadGameStat();
            if (failed == 0 && SLCheckSumCheck() == 0) {
                failed = 1;
            }
            if (GwCommon.unk_00 == 0 && saveCommonBuf.boxNo == i) {
                saveCommonBuf.boxNo = 0xFF;
                SLSaveCommon();
            }
            if (GwCommon.unk_00 != 0 && (GwCommon.unk_00 != 0x91 || failed != 0)) {
                ClearEepromBoxHeader(i);
                SLFormatFlags |= 1 << i;
            }
        }

        if (saveCommonBuf.flags & 1) {
            msmSysSetOutputMode(1);
        } else {
            msmSysSetOutputMode(0);
        }
    } else {
        SLSaveDataInit();
        msmSysSetOutputMode(0);
        SLFormatFlags = 0xFF;
    }

    GwSystem.minigame_index = 0;
    return SLFormatFlags;
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
    if (SaveEnableF) {
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

    if (SaveEnableF) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_BOARD, gEncodedSaveBuffer, SaveBoardSystemEncode(&GwSystem));
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += savePlayerSize;
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

    if (SaveEnableF) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY_BOARD, gEncodedSaveBuffer, SaveStorySystemEncode(&GwSystem));
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 2; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += savePlayerSize;
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

    if (SaveEnableF) {
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
            offset += savePlayerSize;
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

    if (SaveEnableF) {
        SLCommonSet(0);
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY_SYSTEM, gEncodedSaveBuffer, SaveStorySystemEncode(&GwSystem));
        SetEepromBoxBuf(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, SaveStoryEncode(&GwStory));
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            SetEepromBoxBuf(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
            offset += savePlayerSize;
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
    if (SaveEnableF == 0) {
        return 0;
    }
    if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
        return 1;
    }
    SaveCommonDecode(eepBoxBuf, &GwCommon);
    return 0;
}

s32 SLLoadBoard(void) {
    s16 offset;
    s16 i;

    if (SaveEnableF) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveBoardSystemDecode(eepBoxBuf + SAVE_OFS_BOARD, &GwSystem);
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(eepBoxBuf + offset, &GwPlayer[i]);
            offset += savePlayerSize;
        }
    }
    return 0;
}

s32 SLLoadBoardStory(void) {
    s16 offset;
    s16 i;

    if (SaveEnableF) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveStorySystemDecode(eepBoxBuf + SAVE_OFS_STORY_BOARD, &GwSystem);
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(eepBoxBuf + offset, &GwPlayer[i]);
            offset += savePlayerSize;
        }
        SLPadAssign();
    }
    return 0;
}

s32 SLLoadStory(void) {
    s16 offset;
    s16 i;

    if (SaveEnableF) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        SaveStorySystemDecode(eepBoxBuf + SAVE_OFS_STORY_SYSTEM, &GwSystem);
        SaveStoryDecode(eepBoxBuf + SAVE_OFS_STORY, &GwStory);
        GwStory.unk0 = GwStory.unk64;
        GwStory.unk1 = GwStory.unk65;
        GwStory.unk2 = GwStory.unk66;
        GwStory.progress.fields.unkF = GwStory.unk73;
        for (i = 0; i < 12; i++) {
            GwStory.progress.fields.unk3[i] = GwStory.unk67[i];
        }
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            SavePlayerDecode(eepBoxBuf + offset, &GwPlayer[i]);
            offset += savePlayerSize;
        }
    }
    return 0;
}

s32 SLLoadCommon(void) {
    return ReadEepromCommonBuf((u8 *)&saveCommonBuf);
}

s32 SLSaveCommon(void) {
    saveCommonBuf.checksum = CalcChecksumEeprom((u8 *)&saveCommonBuf, 0, 0x16);
    return WriteEepromCommonBuf((u8 *)&saveCommonBuf);
}

void SLCheckSumBoxSet(void) {
    u16 checksum = CalcChecksumEeprom(eepBoxBuf, 0, saveChecksumOfs);

    SetEepromBoxBuf(curBoxNo, saveChecksumOfs, (u8 *)&checksum, sizeof(checksum));
}

s32 SLCheckSumCheck(void) {
    u16 checksum;

    ReadEepromBox(curBoxNo, saveChecksumOfs, (u8 *)&checksum, sizeof(checksum));
    return checksum == CalcChecksumEeprom(eepBoxBuf, 0, saveChecksumOfs);
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
