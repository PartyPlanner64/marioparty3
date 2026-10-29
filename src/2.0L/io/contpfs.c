#include "common.h"
#include "controller.h"

extern s32 D_800A4200_main;       /* __osPfsInodeCacheChannel */
extern __OSInode D_800D5310_main; /* __osPfsInodeCache */

u16 __osSumcalc(u8 *ptr, s32 length) {
    s32 i;
    u32 sum = 0;
    u8 *tmp = ptr;

    for (i = 0; i < length; i++) {
        sum += *tmp++;
    }
    return sum;
}

s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum) {
    u16 data = 0;
    u32 j;

    *csum = *icsum = 0;
    for (j = 0; j < ((sizeof(__OSPackId) - sizeof(u32)) / sizeof(u8)); j += 2) {
        data = *((u16 *)((u32)ptr + j));
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid) {
    s32 ret = 0;
    u8 temp[BLOCKSIZE];
    u8 comp[BLOCKSIZE];
    u8 mask = 0;
    s32 i;
    s32 j = 0;
    u16 index[4];

    newid->repaired = -1;
    newid->random = osGetCount();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;

    SET_ACTIVEBANK_TO_ZERO;

    do {
        ret = __osPfsSelectBank(pfs, j);
        if (ret != 0) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, temp);
        if (ret != 0) {
            return ret;
        }
        temp[0] = j | 0x80;
        for (i = 1; i < BLOCKSIZE; i++) {
            temp[i] = ~temp[i];
        }
        ret = __osContRamWrite(pfs->queue, pfs->channel, 0, temp, FALSE);
        if (ret != 0) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, comp);
        if (ret != 0) {
            return ret;
        }
        for (i = 0; i < BLOCKSIZE; i++) {
            if (comp[i] != temp[i]) {
                break;
            }
        }
        if (i != BLOCKSIZE) {
            break;
        }
        if (j > 0) {
            ret = __osPfsSelectBank(pfs, 0);
            if (ret != 0) {
                return ret;
            }
            ret = __osContRamRead(pfs->queue, pfs->channel, 0, temp);
            if (ret != 0) {
                return ret;
            }
            if (temp[0] != 0x80) {
                break;
            }
        }
        j++;
    } while (j < PFS_MAX_BANKS);

    SET_ACTIVEBANK_TO_ZERO;

    mask = (j > 0) ? 1 : 0;
    newid->deviceid = (badid->deviceid & (u16)~1) | mask;
    newid->banks = j;
    newid->version = badid->version;
    __osIdCheckSum((u16 *)newid, &newid->checksum, &newid->inverted_checksum);

    index[0] = PFS_ID_0AREA;
    index[1] = PFS_ID_1AREA;
    index[2] = PFS_ID_2AREA;
    index[3] = PFS_ID_3AREA;
    for (i = 0; i < ARRLEN(index); i++) {
        ret = __osContRamWrite(pfs->queue, pfs->channel, index[i], (u8 *)newid, TRUE);
        if (ret != 0) {
            return ret;
        }
    }

    ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, temp);
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < BLOCKSIZE; i++) {
        if (temp[i] != ((u8 *)newid)[i]) {
            return PFS_ERR_DEVICE;
        }
    }
    return 0;
}

s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp) {
    u16 index[4];
    s32 ret = 0;
    u16 sum;
    u16 isum;
    s32 i;
    s32 j;

    SET_ACTIVEBANK_TO_ZERO;

    index[0] = PFS_ID_0AREA;
    index[1] = PFS_ID_1AREA;
    index[2] = PFS_ID_2AREA;
    index[3] = PFS_ID_3AREA;
    for (i = 1; i < ARRLEN(index); i++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, index[i], (u8 *)temp);
        if (ret != 0) {
            return ret;
        }
        __osIdCheckSum((u16 *)temp, &sum, &isum);
        if (temp->checksum == sum && temp->inverted_checksum == isum) {
            break;
        }
    }
    if (i == ARRLEN(index)) {
        return PFS_ERR_ID_FATAL;
    }

    for (j = 0; j < ARRLEN(index); j++) {
        if (j != i) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, index[j], (u8 *)temp, TRUE);
            if (ret != 0) {
                return ret;
            }
        }
    }
    return 0;
}

s32 __osGetId(OSPfs *pfs) {
    u16 sum;
    u16 isum;
    u8 temp[BLOCKSIZE];
    __OSPackId newid;
    s32 ret;
    __OSPackId *id;

    SET_ACTIVEBANK_TO_ZERO;

    ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, temp);
    if (ret != 0) {
        return ret;
    }
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (__OSPackId *)temp;
    if (id->checksum != sum || id->inverted_checksum != isum) {
        ret = __osCheckPackId(pfs, id);
        if (ret == PFS_ERR_ID_FATAL) {
            ret = __osRepairPackId(pfs, id, &newid);
            if (ret != 0) {
                return ret;
            }
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }

    if ((id->deviceid & 1) == 0) {
        ret = __osRepairPackId(pfs, id, &newid);
        if (ret != 0) {
            return ret;
        }
        id = &newid;
        if ((id->deviceid & 1) == 0) {
            return PFS_ERR_DEVICE;
        }
    }

    bcopy(id, pfs->id, BLOCKSIZE);
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = 1 + DEF_DIR_PAGES + (2 * pfs->banks);
    pfs->dir_size = DEF_DIR_PAGES * PFS_ONE_PAGE;
    pfs->inode_table = 1 * PFS_ONE_PAGE;
    pfs->minode_table = (1 + pfs->banks) * PFS_ONE_PAGE;
    pfs->dir_table = pfs->minode_table + (pfs->banks * PFS_ONE_PAGE);

    ret = __osContRamRead(pfs->queue, pfs->channel, PFS_LABEL_AREA, pfs->label);
    if (ret != 0) {
        return ret;
    }
    return 0;
}

s32 __osCheckId(OSPfs *pfs) {
    u8 temp[BLOCKSIZE];
    s32 ret;

    if (pfs->activebank != 0) {
        ret = __osPfsSelectBank(pfs, 0);
        if (ret == PFS_ERR_NEW_PACK) {
            ret = __osPfsSelectBank(pfs, 0);
        }
        if (ret != 0) {
            return ret;
        }
    }

    ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, temp);
    if (ret != 0) {
        if (ret != PFS_ERR_NEW_PACK) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, temp);
        if (ret != 0) {
            return ret;
        }
    }

    if (bcmp(pfs->id, temp, BLOCKSIZE) != 0) {
        return PFS_ERR_NEW_PACK;
    }
    return 0;
}

s32 __osPfsRWInode(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank) {
    u8 sum;
    s32 j;
    s32 ret;
    s32 offset;
    u8 *addr;

    if (flag == PFS_READ && bank == D_800A4204_main && pfs->channel == D_800A4200_main) {
        bcopy(&D_800D5310_main, inode, sizeof(__OSInode));
        return 0;
    }

    SET_ACTIVEBANK_TO_ZERO;

    offset = (bank > 0) ? 1 : pfs->inode_start_page;

    if (flag == PFS_WRITE) {
        inode->inode_page[0].inode_t.page = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
    }

    for (j = 0; j < PFS_ONE_PAGE; j++) {
        addr = (u8 *)inode->inode_page + j * BLOCKSIZE;
        if (flag == PFS_WRITE) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
        } else {
            ret = __osContRamRead(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr);
        }
        if (ret != 0) {
            return ret;
        }
    }

    if (flag == PFS_READ) {
        sum = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
        if (sum != inode->inode_page[0].inode_t.page) {
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = (u8 *)inode->inode_page + j * BLOCKSIZE;
                ret = __osContRamRead(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr);
            }
            sum = __osSumcalc((u8 *)&inode->inode_page[offset], (128 - offset) * 2);
            if (sum != inode->inode_page[0].inode_t.page) {
                return PFS_ERR_INCONSISTENT;
            }
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = (u8 *)inode->inode_page + j * BLOCKSIZE;
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, FALSE);
            }
        }
    }

    D_800A4204_main = bank;
    bcopy(inode, &D_800D5310_main, sizeof(__OSInode));
    D_800A4200_main = pfs->channel;
    return 0;
}
