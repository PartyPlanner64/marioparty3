#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

extern u32 D_800A2D80_main;
extern rdbPacket *D_800D5554_main;
extern u32 D_800CE174_main;
extern u32 D_800D6A8C_main;
extern u32 D_800CC43C_main;

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

    if (D_800A2D80_main) {
        D_800A2D80_main = 0;
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

    while (size != 0 && D_800D6A8C_main < D_800CE174_main) {
        count = (size < 4) ? size : 3;
        pkt = &D_800D5554_main[D_800CC43C_main];
        pkt->type = type;
        pkt->length = count;
        for (i = 0; i < count; i++) {
            pkt->buf[i] = buf[offset++];
        }
        D_800CC43C_main++;
        if (D_800CC43C_main >= D_800CE174_main) {
            D_800CC43C_main = 0;
        }
        D_800D6A8C_main++;
        size -= count;
        sent += count;
    }

    if (sendFirst) {
        *(u32 *)RDB_BASE_REG = *(u32 *)&packet;
    }

    __osRestoreInt(mask);
    return sent;
}
