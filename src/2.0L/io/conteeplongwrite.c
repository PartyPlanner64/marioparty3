#include "common.h"
#include "controller.h"

s32 osEepromLongWrite(OSMesgQueue *mq, u8 address, u8 *buffer, int length) {
    s32 ret = 0;

    while (length > 0) {
        ret = osEepromWrite(mq, address, buffer);
        if (ret != 0) {
            return ret;
        }
        length -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
        osSetTimer(&__osEepromTimer, 562500, 0, &__osEepromTimerQ, &__osEepromTimerMsg);
        osRecvMesg(&__osEepromTimerQ, NULL, OS_MESG_BLOCK);
    }
    return ret;
}
