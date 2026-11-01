#include "common.h"
#include "initialize.h"
#include "PR/R4300.h"

#define IS64_MAGIC 0x49533634 // 'IS64'

#define ISV_BUFFER_LEN (sizeof(((ISVDbg *)0)->data))

typedef struct {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 get;
    /* 0x08 */ u8 unk_08[0x14 - 0x08];
    /* 0x14 */ u32 put;
    /* 0x18 */ u8 unk_18[0x20 - 0x18];
    /* 0x20 */ u8 data[0x10000 - 0x20];
} ISVDbg;

extern __osExceptionVector __isExpJP;

static OSPiHandle *is_Handle;
extern u32 gISVFlag;
extern u16 gISVChk;
extern ISVDbg *gISVDbgPrnAdrs;
extern u32 leoComuBuffAdd;
extern __osExceptionVector D_800CD1A0_main; // __isExpJP save

extern void func_80081A20_main(void);

void isPrintfInit(void) {
    is_Handle = osCartRomInit();
    osEPiWriteIo(is_Handle, (u32)&gISVDbgPrnAdrs->put, 0);
    osEPiWriteIo(is_Handle, (u32)&gISVDbgPrnAdrs->get, 0);
    osEPiWriteIo(is_Handle, (u32)&gISVDbgPrnAdrs->magic, IS64_MAGIC);
}

char *is_proutSyncPrintf(char *arg, const u8 *str, u32 count) {
    u32 data;
    s32 p;
    s32 start;
    s32 end;

    if (gISVDbgPrnAdrs == NULL) {
        return NULL;
    }

    osEPiReadIo(is_Handle, (u32)&gISVDbgPrnAdrs->magic, &data);
    if (data != IS64_MAGIC) {
        return (char *)1;
    }
    osEPiReadIo(is_Handle, (u32)&gISVDbgPrnAdrs->get, &data);
    p = data;
    osEPiReadIo(is_Handle, (u32)&gISVDbgPrnAdrs->put, &data);

    start = data;
    end = start + count;

    if (end >= (s32)ISV_BUFFER_LEN) {
        end -= ISV_BUFFER_LEN;
        if (p < end || start < p) {
            return (char *)1;
        }
    } else {
        if (start < p && p < end) {
            return (char *)1;
        }
    }

    while (count) {
        if (*str != '\0') {
            s32 shift = (3 - (start & 3)) * 8;
            u32 addr = (u32)&gISVDbgPrnAdrs->data + (start & 0xFFFFFFC);

            osEPiReadIo(is_Handle, addr, &data);
            osEPiWriteIo(is_Handle, addr, (data & ~(0xFF << shift)) | (*str << shift));

            start++;
            if (start >= (s32)ISV_BUFFER_LEN) {
                start -= ISV_BUFFER_LEN;
            }
        }
        count--;
        str++;
    }

    osEPiWriteIo(is_Handle, (u32)&gISVDbgPrnAdrs->put, start);
    return (char *)1;
}

u32 __checkHardware_isv(void) {
    u32 i = 0;
    u32 save[4];
    u32 data;
    OSPiHandle *hnd = osCartRomInit();

    gISVDbgPrnAdrs = NULL;
    leoComuBuffAdd = 0;
    gISVFlag = IS64_MAGIC;
    gISVChk = 0;

    for (i = 0; i < 4; i++) {
        osEPiReadIo(hnd, 0xB0000100 + i * 4, &save[i]);
    }

    osEPiWriteIo(hnd, 0xB000010C, data);
    data = IS64_MAGIC;
    osEPiWriteIo(hnd, 0xB0000100, data);

    for (i = 0; i < 0x20000; i++) {
        osEPiReadIo(hnd, 0xB000010C, &data);
        if (data == IS64_MAGIC) {
            data = 0;
            osEPiWriteIo(hnd, 0xB0000100, data);
            gISVChk |= 1;
            osEPiReadIo(hnd, 0xB0000104, (u32 *)&gISVDbgPrnAdrs);
            osEPiReadIo(hnd, 0xB0000108, &leoComuBuffAdd);
            break;
        }
    }

    for (i = 0; i < 4; i++) {
        osEPiWriteIo(hnd, 0xB0000100 + i * 4, save[i]);
    }

    osEPiReadIo(hnd, 0xBFF00000, &data);
    gISVChk |= (data == IS64_MAGIC) ? 2 : 0;

    return gISVChk != 0;
}

void __osInitialize_isv(void) {
    void (*fn)(void);
    OSPiHandle *hnd;

    if (gISVFlag == IS64_MAGIC || __checkHardware_isv()) {
        if (gISVDbgPrnAdrs != NULL) {
            __printfunc = (void *)is_proutSyncPrintf;
            isPrintfInit();
        }
        if (gISVChk & 2) {
            hnd = osCartRomInit();
            D_800CD1A0_main = *(__osExceptionVector *)E_VEC;
            *(__osExceptionVector *)E_VEC = __isExpJP;

            osWritebackDCache(&D_800CD1A0_main, sizeof(__osExceptionVector));
            osInvalICache(&D_800CD1A0_main, sizeof(__osExceptionVector));
            osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
            osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
            osEPiReadIo(hnd, 0xBFF00010, (u32 *)&fn);
            fn();
        }
        if (gISVChk & 2) {
            func_80081A20_main();
        }
    }
}
