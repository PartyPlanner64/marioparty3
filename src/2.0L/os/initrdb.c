#include "common.h"
#include "PR/os_internal.h"

extern u8 *__osRdb_IP6_Data;
extern s32 __osRdb_IP6_Size;
extern s32 __osRdb_IP6_Ct;
extern s32 __osRdb_IP6_CurWrite;
extern s32 __osRdb_IP6_CurSend;

void osInitRdb(u8 *sendBuf, u32 sendSize) {
    register u32 int_disabled;

    sendSize >>= 2;

    if (((u32)sendBuf & 3) != 0) {
        sendBuf = (u8 *)(((u32)sendBuf & 3) + 4);
        sendSize--;
    }

    int_disabled = __osDisableInt();

    __osRdb_IP6_Data = sendBuf;
    __osRdb_IP6_Size = sendSize;
    __osRdb_IP6_Ct = 0;
    __osRdb_IP6_CurWrite = 0;
    __osRdb_IP6_CurSend = 0;

    __osRestoreInt(int_disabled);
}
