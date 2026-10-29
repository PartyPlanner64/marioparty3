#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "PR/os_internal.h"
#include "PR/rcp.h"

#define ARRLEN(x) ((s32)(sizeof(x) / sizeof(x[0])))
#define CHNL_ERR(format) (((format).rxsize & CHNL_ERR_MASK) >> 4)

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u16 button;
    /* 0x6 */ s8 stick_x;
    /* 0x7 */ s8 stick_y;
} __OSContReadFormat;

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 typeh;
    /* 0x5 */ u8 typel;
    /* 0x6 */ u8 status;
    /* 0x7 */ u8 dummy1;
} __OSContRequesFormat;

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 hi;
    /* 0x05 */ u8 lo;
    /* 0x06 */ u8 data[BLOCKSIZE];
    /* 0x26 */ u8 datacrc;
} __OSContRamReadFormat;

typedef union {
    /* 0x0 */ struct {
        /* 0x0 */ u8 bank;
        /* 0x1 */ u8 page;
    } inode_t;
    /* 0x0 */ u16 ipage;
} __OSInodeUnit;

typedef struct {
    /* 0x0 */ __OSInodeUnit inode_page[128];
} __OSInode;

typedef struct {
    /* 0x00 */ u32 repaired;
    /* 0x04 */ u32 random;
    /* 0x08 */ u64 serial_mid;
    /* 0x10 */ u64 serial_low;
    /* 0x18 */ u16 deviceid;
    /* 0x1A */ u8 banks;
    /* 0x1B */ u8 version;
    /* 0x1C */ u16 checksum;
    /* 0x1E */ u16 inverted_checksum;
} __OSPackId;

typedef struct {
    /* 0x0 */ u8 txsize;
    /* 0x1 */ u8 rxsize;
    /* 0x2 */ u8 cmd;
    /* 0x3 */ u8 address;
    /* 0x4 */ u8 data[EEPROM_BLOCK_SIZE];
} __OSContEepromFormat;

#define PFS_ID_0AREA 1
#define PFS_ID_1AREA 3
#define PFS_ID_2AREA 4
#define PFS_ID_3AREA 6
#define PFS_LABEL_AREA 7

#define DEF_DIR_PAGES 2

#define SET_ACTIVEBANK_TO_ZERO           \
    if (pfs->activebank != 0) {          \
        ret = __osPfsSelectBank(pfs, 0); \
        if (ret != 0) {                  \
            return ret;                  \
        }                                \
    }

#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_READ_MEMPACK 2
#define CONT_CMD_WRITE_MEMPACK 3
#define CONT_CMD_READ_EEPROM 4
#define CONT_CMD_WRITE_EEPROM 5
#define CONT_CMD_RESET 0xFF

#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_READ_BUTTON_TX 1
#define CONT_CMD_READ_MEMPACK_TX 3
#define CONT_CMD_WRITE_MEMPACK_TX 35
#define CONT_CMD_READ_EEPROM_TX 2
#define CONT_CMD_WRITE_EEPROM_TX 10
#define CONT_CMD_RESET_TX 1

#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_READ_BUTTON_RX 4
#define CONT_CMD_READ_MEMPACK_RX 33
#define CONT_CMD_WRITE_MEMPACK_RX 1
#define CONT_CMD_READ_EEPROM_RX 8
#define CONT_CMD_WRITE_EEPROM_RX 1
#define CONT_CMD_RESET_RX 3

#define CONT_CMD_NOP 0xFF
#define CONT_CMD_END 0xFE /* indicates end of a command */
#define CONT_CMD_EXE 1    /* set pif ram status byte to this to do a command */

/* siacs.c */
void func_8007C720_main(void); /* __osSiCreateAccessQueue */
void __osSiGetAccess(void);
void __osSiRelAccess(void);

/* crc.c */
u16 __osContAddressCrc(u16 address);
u8 __osContDataCrc(u8 *data);

/* contpfs.c */
u16 __osSumcalc(u8 *data, s32 length);
s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum);
s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid);
s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp);
s32 __osGetId(OSPfs *pfs);
s32 __osCheckId(OSPfs *pfs);
s32 __osPfsRWInode(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank);

s32 __osEepStatus(OSMesgQueue *mq, OSContStatus *data);
s32 __osPfsSelectBank(OSPfs *pfs, u8 bank);
s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer);
s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force);
void __osContGetInitData(u8 *pattern, OSContStatus *data);
void __osPackRequestData(u8 cmd);
void __osPfsRequestData(u8 cmd);
void __osPfsGetInitData(u8 *pattern, OSContStatus *data);
s32 __osPfsGetStatus(OSMesgQueue *queue, int channel);
void __osPfsRequestOneChannel(s32 channel, s32 cmd);
void __osPfsGetOneChannelData(s32 channel, OSContStatus *data);

extern u8 D_800CE204;               /* __osMaxControllers */
extern u8 D_800D1F58_main;          /* __osContLastCmd */
extern OSTimer D_800D41C8_main;     /* __osEepromTimer */
extern OSMesgQueue D_800D6A28_main; /* __osEepromTimerQ */
extern OSMesg D_800D1F6C_main;      /* __osEepromTimerMsg */
extern OSPifRam D_800D0470_main;    /* __osEepPifRam */
extern OSPifRam D_800CC3F0_main;    /* __osContPifRam */
extern OSPifRam __osPfsPifRam;
extern s32 D_800A3F90_main; /* __osPfsLastChannel */
extern u8 D_800A4204_main;  /* __osPfsInodeCacheBank */
extern s32 D_800D2004_main; /* __osEepromRead16K */

#endif
