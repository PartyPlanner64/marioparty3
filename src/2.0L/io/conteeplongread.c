#include "common.h"
#include "controller.h"

s32 osEepromLongRead(OSMesgQueue *mq, u8 address, u8 *buffer, int length) {
    s32 ret = 0;

    while (length > 0) {
        ret = osEepromRead(mq, address, buffer);
        if (ret != 0) {
            return ret;
        }
        length -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
    }
    return ret;
}
