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

typedef struct SaveCommonBuf {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 boxNo;
    /* 0x02 */ u8 unk_02[0x14];
    /* 0x16 */ u16 checksum;
} SaveCommonBuf; // sizeof 0x18

extern u8 D_800A1E80_main;
extern u8 curBoxNo;
extern s16 D_800A1E82_main;
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


void func_8004FCF0_main(void) {
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

s32 func_8004FDC0_main(void) {
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

        failed = func_80050CDC_main();
        if (D_800D09A8_main.checksum != CalcChecksumEeprom(D_800D0450_main, 0, 0x16)) {
            failed = 1;
        }
        if (failed) {
            memset(&D_800D09A8_main, 0, sizeof(SaveCommonBuf));
            D_800D09A8_main.boxNo = 0xFF;
            D_800D09A8_main.flags &= ~1;
            func_80050CFC_main();
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
                func_80050CFC_main();
            }
            if (GwCommon.unk_00 != 0 && (GwCommon.unk_00 != 0x91 || failed != 0)) {
                func_8000C9C8_main(i);
                D_800D20EC_main |= 1 << i;
            }
        }

        if (D_800D09A8_main.flags & 1) {
            func_80000F30_main(1);
        } else {
            func_80000F30_main(0);
        }
    } else {
        func_8004FCF0_main();
        func_80000F30_main(0);
        D_800D20EC_main = 0xFF;
    }

    GwSystem.minigame_index = 0;
    return D_800D20EC_main;
}

void func_80050044_main(void) {
}

void func_8005004C_main(void) {
}

void func_80050054_main(void) {
}

void func_8005005C_main(void) {
}

s32 SLCommonSet(s32 writeBox) {
    if (D_800BBAB0_main) {
        func_8000C6C0_main(curBoxNo, 0, gEncodedSaveBuffer, func_8004F564_main(&GwCommon));
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
        func_8000C6C0_main(curBoxNo, SAVE_OFS_BOARD, gEncodedSaveBuffer, func_8004F504_main(&GwSystem));
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
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
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY_BOARD, gEncodedSaveBuffer, func_8004F524_main(&GwSystem));
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 2; i++) {
            func_8000C6C0_main(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
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

s32 func_8005035C_main(s32 writeBox) {
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
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, func_8004F584_main(&GwStory));
        SLCommonSet(0);
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY_SYSTEM, gEncodedSaveBuffer, func_8004F524_main(&GwSystem));
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, func_8004F584_main(&GwStory));
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
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

s32 func_80050614_main(s32 writeBox) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        SLCommonSet(0);
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY_SYSTEM, gEncodedSaveBuffer, func_8004F524_main(&GwSystem));
        func_8000C6C0_main(curBoxNo, SAVE_OFS_STORY, gEncodedSaveBuffer, func_8004F584_main(&GwStory));
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8000C6C0_main(curBoxNo, offset, gEncodedSaveBuffer, SavePlayerStruct(&GwPlayer[i]));
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
    func_8004F9AC_main(D_800D0E50_main, &GwCommon);
    return 0;
}

s32 SLLoadBoard(void) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        func_8004F8BC_main(D_800D0E50_main + SAVE_OFS_BOARD, &GwSystem);
        offset = SAVE_OFS_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(D_800D0E50_main + offset, &GwPlayer[i]);
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
        func_8004F90C_main(D_800D0E50_main + SAVE_OFS_STORY_BOARD, &GwSystem);
        offset = SAVE_OFS_STORY_BOARD_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(D_800D0E50_main + offset, &GwPlayer[i]);
            offset += D_800CCF54_main;
        }
        func_80050E84_main();
    }
    return 0;
}

s32 func_80050ABC_main(void) {
    s16 offset;
    s16 i;

    if (D_800BBAB0_main) {
        if (ReadEepromBox(curBoxNo | 0x80, 0, NULL, SAVE_BOX_SIZE) != 0) {
            return 1;
        }
        func_8004F90C_main(D_800D0E50_main + SAVE_OFS_STORY_SYSTEM, &GwSystem);
        func_8004F9FC_main(D_800D0E50_main + SAVE_OFS_STORY, &GwStory);
        GwStory.unk0 = GwStory.unk64;
        GwStory.unk1 = GwStory.unk65;
        GwStory.unk2 = GwStory.unk66;
        GwStory.progress.fields.unkF = GwStory.unk73;
        for (i = 0; i < 12; i++) {
            GwStory.progress.fields.unk3[i] = GwStory.unk67[i];
        }
        offset = SAVE_OFS_STORY_PLAYERS;
        for (i = 0; i < 4; i++) {
            func_8004F95C_main(D_800D0E50_main + offset, &GwPlayer[i]);
            offset += D_800CCF54_main;
        }
    }
    return 0;
}

s32 func_80050CDC_main(void) {
    return ReadEepromCommonBuf((u8 *)&D_800D09A8_main);
}

s32 func_80050CFC_main(void) {
    D_800D09A8_main.checksum = CalcChecksumEeprom((u8 *)&D_800D09A8_main, 0, 0x16);
    return WriteEepromCommonBuf((u8 *)&D_800D09A8_main);
}

void SLCheckSumBoxSet(void) {
    u16 checksum = CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);

    func_8000C6C0_main(curBoxNo, D_800CE2C0_main, (u8 *)&checksum, sizeof(checksum));
}

s32 SLCheckSumCheck(void) {
    u16 checksum;

    ReadEepromBox(curBoxNo, D_800CE2C0_main, (u8 *)&checksum, sizeof(checksum));
    return checksum == CalcChecksumEeprom(D_800D0E50_main, 0, D_800CE2C0_main);
}

s32 func_80050DDC_main(s16 srcBoxNo, s16 dstBoxNo) {
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

void func_80050E84_main(void) {
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
