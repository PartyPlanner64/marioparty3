#ifndef _GAME_EEPROM_H
#define _GAME_EEPROM_H

#include "ultra64.h"

s32 InitEeprom(u8 *formatted);
s32 WriteEepromBox2(s8 saveFileIndex, u16 offset, u8 *src, u16 size);
s32 WriteEepromBox(s8 saveFileIndex);
void func_8000C6C0_main(s8 saveFileIndex, u16 offset, u8 *src, u16 size);
s32 ReadEepromBox(s8 saveFileIndex, u16 offset, u8 *dst, u16 size);
s32 WriteEepromCommonBuf(u8 *src);
s32 ReadEepromCommonBuf(u8 *dst);
s32 func_8000C9C8_main(s8 saveFileIndex);
void ClearBoxBuf(s8 saveFileIndex);
void ClearCommonBuf(void);
s32 DestroyEeprom(void);
u16 CalcChecksumEeprom(u8 *data, u16 startIndex, u16 size);

s32 _InitEeprom(u8 **arg0);
s32 _DestroyEeprom(void);
s32 WriteEeprom(OSMesgQueue *arg0, u8 arg1, u8 *arg2, s32 arg3);

#endif
