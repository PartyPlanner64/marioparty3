#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

unsigned int __osRdbWriteOK = 1;

extern rdbPacket *__osRdb_IP6_Data;
extern u32 __osRdb_IP6_Size;
extern u32 __osRdb_IP6_Ct;
extern u32 __osRdb_IP6_CurWrite;

u32 __osRdbSend(u8 *buf, u32 size, u32 type) {
    rdbPacket packet;
    rdbPacket *pkt;
    u32 i;
    u32 offset = 0;
    u32 sendFirst = FALSE;
    u32 sent = 0;
    u32 count;
    u32 mask;

    mask = __osDisableInt();

    if (__osRdbWriteOK) {
        __osRdbWriteOK = 0;
        packet.type = type;
        count = (size < 4) ? size : 3;
        packet.length = count;
        for (i = 0; i < count; i++) {
            packet.buf[i] = buf[offset++];
        }
        size -= count;
        sent = count;
        sendFirst = TRUE;
    }

    while (size != 0 && __osRdb_IP6_Ct < __osRdb_IP6_Size) {
        count = (size < 4) ? size : 3;
        pkt = &__osRdb_IP6_Data[__osRdb_IP6_CurWrite];
        pkt->type = type;
        pkt->length = count;
        for (i = 0; i < count; i++) {
            pkt->buf[i] = buf[offset++];
        }
        __osRdb_IP6_CurWrite++;
        if (__osRdb_IP6_CurWrite >= __osRdb_IP6_Size) {
            __osRdb_IP6_CurWrite = 0;
        }
        __osRdb_IP6_Ct++;
        size -= count;
        sent += count;
    }

    if (sendFirst) {
        *(u32 *)RDB_BASE_REG = *(u32 *)&packet;
    }

    __osRestoreInt(mask);
    return sent;
}
