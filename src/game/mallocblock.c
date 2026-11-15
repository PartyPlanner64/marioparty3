#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/mallocblock.h"

s16 gHuMemIsDirty = FALSE;
s16 HuMemDebugBlkNum = 0;

void HuMemInit(HuAllocFunc malloc, HuFreeFunc free) {
    HuMallocHeader *newBlock;

    gMallocFunc = malloc;
    gFreeFunc = free;

    if (gHuMemIsDirty) {
        HuMemFreeAll();
    }

    newBlock = gMallocFunc(sizeof(HuMallocHeader));
    gLastMallocBlock = newBlock;
    gFirstMallocBlock = newBlock;

    newBlock->data = NULL;
    newBlock->tag = TAG_DELAYED_FREE;
    newBlock->prev = newBlock;
    newBlock->next = newBlock;

    HuMemDelayFreeCnt = 0;
}

void *HuMemAlloc(s32 size) {
    return HuMemAllocTag(size, 0);
}

void *HuMemAllocTag(s32 size, s16 tag) {
    s32 alignedSize;
    void *data;
    HuMallocHeader *firstBlk;
    HuMallocHeader *newBlk;

    alignedSize = (size + 7) & ~7;
    data = gMallocFunc(alignedSize + sizeof(HuMallocHeader));
    newBlk = (HuMallocHeader *)((s32)data + alignedSize);

    firstBlk = gFirstMallocBlock;

    newBlk->prev = firstBlk;
    newBlk->next = firstBlk->next;
    firstBlk->next->prev = newBlk;
    firstBlk->next = newBlk;

    newBlk->tag = tag;
    newBlk->size = alignedSize;
    newBlk->data = data;
    newBlk->creationFrame = Hu3DFrameCnt;

    return newBlk->data;
}

void HuMemFree(void *data) {
    HuMallocHeader *block = gFirstMallocBlock->next;
    while (data != block->data) {
        block = block->next;
        if (block == gLastMallocBlock) {
            return;
        }
    }
    HuMemBlockFree(block);
}

void HuMemBlockFree(HuMallocHeader *block) {
    gLastFreedBlock = block;

    block->next->prev = block->prev;
    block->prev->next = block->next;

    gFreeFunc(block->data);
}

void HuMemFreeAllWithTag(s16 tag) {
    HuMallocHeader *prevBlk;
    HuMallocHeader *block;

    for (block = gFirstMallocBlock->next; block != gLastMallocBlock; block = block->next) {
        if (block->tag == tag) {
            if (block->tag != TAG_DELAYED_FREE) {
                prevBlk = block->prev;
                HuMemBlockFree(block);
                block = prevBlk;
            } else {
                if (--block->framesLeft == 0) {
                    prevBlk = block->prev;
                    HuMemBlockFree(block);
                    block = prevBlk;

                    if (--HuMemDelayFreeCnt <= 0) {
                        break;
                    }
                }
            }
        }
    }
}

void HuMemDelayFree(void *data) {
    HuMallocHeader *block;

    block = gFirstMallocBlock->next;
    while (data != block->data) {
        block = block->next;
        if (block == gLastMallocBlock) {
            return;
        }
    }

    block->tag = TAG_DELAYED_FREE;
    block->framesLeft = Hu3DBufNum + 1;

    ++HuMemDelayFreeCnt;
}

void HuMemDelayFreeAllWithTag(s16 arg0) {
    HuMallocHeader *block;

    block = gFirstMallocBlock->next;
    while (block != gLastMallocBlock) {
        if (block->tag == arg0) {
            block->tag = TAG_DELAYED_FREE;
            block->framesLeft = Hu3DBufNum + 1;
            ++HuMemDelayFreeCnt;
        }
        block = block->next;
    }
}

void HuMemSetDirty(void) {
    gHuMemIsDirty = TRUE;
}

void HuMemFreeAll(void) {
    HuMallocHeader *prevBlk;
    HuMallocHeader *block;

    block = gFirstMallocBlock->next;
    while (block != gLastMallocBlock) {
        prevBlk = block->prev;
        HuMemBlockFree(block);
        block = prevBlk->next;
    }

    gFreeFunc((void *)gLastMallocBlock);

    HuMemDelayFreeCnt = 0;
    gHuMemIsDirty = FALSE;
}

void HuMemCleanUp(void) {
    if (gHuMemIsDirty) {
        HuMemFreeAll();
    } else if (HuMemDelayFreeCnt != 0) {
        HuMemFreeAllWithTag(TAG_DELAYED_FREE);
    }
}

s32 HuMemGetSizeTag(s16 tag) {
    HuMallocHeader *block;
    s32 size;

    block = gFirstMallocBlock->next;
    size = 0;
    while (block != gLastMallocBlock) {
        if (block->tag == tag) {
            size += block->size;
        }
        block = block->next;
    }
    return size;
}

s32 HuMemGetSize(void) {
    HuMallocHeader *block;
    s32 size;

    block = gFirstMallocBlock->next;
    size = 0;
    while (block != gLastMallocBlock) {
        size += block->size;
        block = block->next;
    }
    return size;
}

void HuMemSetTag(void *data, s16 tag) {
    HuMallocHeader *block;

    block = gFirstMallocBlock->next;
    while (data != block->data) {
        block = block->next;
        if (block == gLastMallocBlock) {
            return;
        }
    }
    block->tag = tag;
}

// there's a messed up file split somewhere...the next string is in hmfman.c
extern const char hexFmtStr[];

s32 HuMemDebugCheck(void) {
    HuMallocHeader *block;
    s16 i;
    s16 count;
    s16 var_v1;
    s32 size;

    block = gFirstMallocBlock->next;
    size = 0;
    count = 0;
    while (block != gLastMallocBlock) {
        HuMemDebugBlk[count] = block->data;
        size += block->size;
        block = block->next;
        count++;
    }

    if ((HuMemDebugBlkNum != 0) && (HuMemDebugBlkNum != count)) {
        for (i = 0; i < count; i++) {
            for (var_v1 = 0; var_v1 < HuMemDebugBlkNum; var_v1++) {
                if (HuMemDebugBlkOld[var_v1] == HuMemDebugBlk[i])
                    break;
            }
            if (var_v1 == HuMemDebugBlkNum) {
                osSyncPrintf(hexFmtStr, HuMemDebugBlk[i]);
            }
        }
    }

    HuMemDebugBlkNum = count;
    for (i = 0; i < count; i++) {
        HuMemDebugBlkOld[i] = HuMemDebugBlk[i];
    }
    return size;
}
