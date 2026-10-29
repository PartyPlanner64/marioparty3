#include "common.h"
#include "PR/os_internal.h"
#include "PR/rdb.h"

static int readHostInitialized = FALSE;
static OSMesgQueue readHostMesgQueue;
static OSMesg readHostMesgBuf[1];

extern void *__osRdb_Read_Data_Buf;
extern u32 __osRdb_Read_Data_Ct;

void osReadHost(void *dramAddr, u32 nbytes) {
    char tstr[4];
    u32 sent = 0;

    if (!readHostInitialized) {
        osCreateMesgQueue(&readHostMesgQueue, readHostMesgBuf, ARRAY_COUNT(readHostMesgBuf));
        osSetEventMesg(OS_EVENT_RDB_READ_DONE, &readHostMesgQueue, NULL);
        readHostInitialized = TRUE;
    }

    __osRdb_Read_Data_Buf = dramAddr;
    __osRdb_Read_Data_Ct = nbytes;

    while (sent == 0) {
        sent += __osRdbSend((u8 *)tstr, 1, RDB_TYPE_GtoH_READY_FOR_DATA);
    }

    osRecvMesg(&readHostMesgQueue, NULL, OS_MESG_BLOCK);
}
