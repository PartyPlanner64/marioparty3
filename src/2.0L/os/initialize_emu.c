#include "common.h"
#include "initialize.h"
#include "PR/rdb.h"

extern u32 __osRdbSend(u8 *buf, u32 size, u32 type);

char *proutSyncPrintf(char *str, const char *buf, unsigned int n);

void __osInitialize_emu(void) {
    __printfunc = proutSyncPrintf;
}

char *proutSyncPrintf(char *str, const char *buf, unsigned int n) {
    u32 sent = 0;

    while (sent < n) {
        sent += __osRdbSend((u8 *)buf + sent, n - sent, RDB_TYPE_GtoH_PRINT);
    }
    return (char *)1;
}
