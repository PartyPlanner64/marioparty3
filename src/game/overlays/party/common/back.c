#include "common_board.h"
#include "game/mallocblock.h"
#include "move.h"
#include "game/malloc.h"
#include "game/rom.h"
#include "back.h"
#include "vec.h"
#include "pause.h"
#include "game/hmfmath.h"

#define BG_TEXEL(entry, off) (*(u16 *)((u8 *)(entry)->pixels + (off)))
#define BG_TEX_SIZE (64 * 48 * 2)

typedef struct UnkCam3DStruct {
    Vec2f unk_00;
    f32 unk_08;
    f32 unk_0C;
} UnkCam3DStruct;

extern s32 mbBackFileAddr;

typedef struct UnkModelStruct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkModelStruct; //sizeof 0x3C

s32 *mbBackArcOfsTbl = NULL; //TODO: fix type
u32 *mbBackFileOfsTbl = NULL;
UnkModelStruct *mbBackHdr = NULL;
u8 mbBackTPLvl = 255;
f32 mbBackZoom = 1.0f;
f32 mbCameraFar = 0.0f;
f32 mbCameraNear = 0.0f;
Vec mbCameraFocusPos = { 0.0f, 0.0f, 0.0f };
s32 mbBackAltF = 0;
u8 mbBackAltTPLvl = 255;
Gfx mbBackGfxInit[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};
Process *mbBackSprProc = NULL;
s32 mbBackSprDispF = 1;
void *mbMasuData = NULL;
u8 (*mbMasuTypeListTbl)[SPACES_MAX] = NULL;
s32 mbMasuBmpTbl[] = { 0, 0x130215, 0x130216, 0, 0x130219, 0x13021F, 0x130218, 0x13021D, 0, 0x130217, 0, 0, 0x13021E, 0x130222, 0x13021B, 0x13021A };
u8 mbMasuBmpSizeTbl[] = { 0, 2, 2, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1 }; //u8 array that links space type to render type
s32 mbMasuBmpAltTbl[] = { 0, 0x130248, 0x130249, 0, 0x13024B, 0x13024C, 0x130250, 0x13024D, 0, 0x13024F, 0, 0, 0x130251, 0x13024E, 0x130252, 0x13024A };
Vtx mbMasuVtx[] = {
    { { { 100, 0, -100 }, 0, { 992, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, -100 }, 0, { 0, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, 100 }, 0, { 0, 0 }, { 0, 0, 127, 255 } } },
    { { { 100, 0, 100 }, 0, { 992, 0 }, { 0, 0, 127, 255 } } },
};
Vtx mbMasuAltVtx[] = {
    { { { 100, 0, -100 }, 0, { 224, 224 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, -100 }, 0, { 0, 224 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, 100 }, 0, { 0, 0 }, { 0, 0, 127, 255 } } },
    { { { 100, 0, 100 }, 0, { 224, 0 }, { 0, 0, 127, 255 } } },
};
Gfx mbMasuGfxInit[] = {
    gsSPSegment(0x00, 0x00000000),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};
u8 mbMasuTypeBitTbl[] = { 1, 2, 4, 1, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

extern u16 mbBackFlag;
extern OverlayBgEntry *mbBackTileMap[6][6];
extern OverlayBgEntry mbBackTileTbl[36];
extern OverlayBgEntry mbBackAltTileTbl[];
extern OSMesgQueue mbBackDmaMesgQ;
extern u16 mbMasuLinkNum;
extern u32 mbBackArcAddr;
extern s32 mbBackArcNum;
extern u16 mbBackFlag;
extern f32 mbBackScale;
extern Vec2f mbCameraScrTarget;
extern f32 mbCameraScrPos[];
extern OSMesgQueue mbBackDmaMesgQ;
extern OSMesg mbBackDmaMesgBuf[36];
extern OSThread mbBackDmaThread;
extern OSThread mbBackDecodeThread;
extern s32 mbBackThreadPri;
extern OSMesg mbBackDecodeMesgBuf[36];
extern OSMesg mbBackDoneMesgBuf[36];
extern OSMesg mbBackExitMesgBuf[2];
extern OSThread mbBackDecodeThread;
extern s32 mbBackThreadPri;
extern s16 mbBackOfsX;
extern s16 mbBackOfsY;
extern s16 mbBackHalfW;
extern s16 mbBackHalfH;
extern Process* mbCameraZoomProc;
extern Process* mbCameraUpdateProc;
extern f32 mbCameraSpeedDiv;
extern Vec mbCameraEye;
extern Vec mbCameraAt;
extern Vec mbCameraUp;
extern Vec mbCameraViewportSize;
extern f32 mbCameraSpeed;
extern s32 mbMasuFlagTbl[];
extern s16 mbMasuStarTbl[];
extern s16 mbMasuBlockNum;
extern s16 mbMasuBlockExtNum;
extern s16 mbMasuBlockTbl[];
extern s16 mbMasuBlockExtTbl[];
extern void* mbMasuEventBoardStartTbl;
extern void* mbMasuEventRoundEndTbl;
extern void* mbMasuEventTurnStartTbl;
extern void* mbMasuEventTurnTelopTbl;
extern s32 mbMasuEventResult;
extern s32 mbBackNo;
extern Vec mbBackOrigin;
extern s32 mbBackAltBank;
extern s32 mbBackAltNo;
extern UnkFAF78 *mbBackAltTbl;
extern u8* mbBackHvqWork;
extern HvqFileHeader* mbBackHvqFileHdr;
extern OSMesgQueue mbBackDecodeMesgQ;
extern OSMesgQueue mbBackDoneMesgQ;
extern OSMesgQueue mbBackExitMesgQ;
extern HvqHeader* mbBackHvqCur;
extern UnkBoard7 mbBackSprTbl[64];
extern s32 mbBackSprNum;
extern s16 mbMasuBmpMode;
extern u8* mbMasuBmpDataTbl[]; //space form images
extern s32 mbMasuArrowAngleNum;
extern f32 mbMasuArrowAngleTbl[];
extern s16 MTXBufNum;
extern Mtx* MTXBuf;
extern u16 gTotalSpaces;
extern SpaceData* mbMasuTbl;
extern LinkData* mbMasuLinkTbl;
extern u8 mbMasuTypeNumTbl[];

static void MBBackDraw(Gfx** arg0, s32 arg1, u8 arg2);
static s32 MBBackFileSizeGet(u16 arg0);
static void MBCameraInit(void);
static void MBCameraClose(void);
static void MBCameraUpdateMain(void);

void MBBackArcInit(u32 arg0) {
    HuArchive* temp_v0;
    s32* temp_v0_2;
    u32 temp_s0;

    mbBackArcAddr = arg0;
    temp_v0 = HuMemMemoryAllocTemp(sizeof(HuArchive));
    dmaRead(arg0, (u8*)temp_v0, sizeof(HuArchive));
    mbBackArcNum = temp_v0->count;
    HuMemMemoryFreeTemp(temp_v0);
    temp_s0 = mbBackArcNum * 4;
    temp_v0_2 = HuMemMemoryAllocTemp(temp_s0);
    mbBackArcOfsTbl = temp_v0_2;
    dmaRead(arg0 + 4, (u8*)temp_v0_2, temp_s0);
    mbBackHvqWork = HuMemMemoryAllocTemp(0x300); //TODO: hardcoded size
    mbBackHdr = NULL;
}

void MBBackReset(void) {
    mbBackHdr = NULL;
}

void MBBackClose(void) {
    if (mbBackArcOfsTbl != NULL) {
        HuMemMemoryFreeTemp(mbBackArcOfsTbl);
        mbBackArcOfsTbl = NULL;
        HuMemMemoryFreeTemp(mbBackHvqWork);
    }
}

void MBBackCreate(s32 arg0, s32 arg1) {
    UnkModelStruct* temp_v0_3;
    s32 temp_s2;
    u32 temp_s0;
    HuArchive* temp_v0;
    u32* temp_v0_2;

    mbBackNo = arg0;
    mbBackFileAddr = mbBackArcAddr + mbBackArcOfsTbl[arg0];
    temp_v0 = HuMemMemoryAllocTemp(sizeof(HuArchive));
    dmaRead((u32)mbBackFileAddr, (u8*)temp_v0, sizeof(HuArchive));
    arg0 = temp_v0->count;
    HuMemMemoryFreeTemp(temp_v0);
    arg0++;
    temp_s0 = arg0 * 4;
    temp_v0_2 = HuMemMemoryAllocTemp(temp_s0);
    mbBackFileOfsTbl = temp_v0_2;
    dmaRead(mbBackFileAddr + 4, (u8*)temp_v0_2, temp_s0);
    temp_v0_3 = HuMemMemoryAllocTemp(sizeof(UnkModelStruct));
    mbBackHdr = temp_v0_3;
    dmaRead(mbBackFileAddr + mbBackFileOfsTbl[0], (u8*)&temp_v0_3->unk0, sizeof(UnkModelStruct));
    mbBackOrigin.x = mbBackHdr->unk18;
    mbBackOrigin.y = mbBackHdr->unk1C;
    mbBackOrigin.z = mbBackHdr->unk20;
    mbBackHdr->unk18 *= 5.0f;
    mbBackHdr->unk1C *= 5.0f;
    mbBackHdr->unk20 *= 5.0f;
    mbBackHdr->unk24 *= 5.0f;
    mbBackHdr->unk28 *= 5.0f;
    mbBackHdr->unk2C *= 5.0f;
    mbBackHvqFileHdr = HuMemMemoryAllocTemp(MBBackFileSizeGet(0));
    dmaRead(mbBackFileAddr + mbBackFileOfsTbl[1], (u8 *)mbBackHvqFileHdr, MBBackFileSizeGet(0));
    mbBackOfsY = 0;
    mbBackOfsX = 0;
    mbBackHalfW = mbBackHdr->unk0 * mbBackHdr->unk8 / 2;
    mbBackHalfH = mbBackHdr->unk4 * mbBackHdr->unkC / 2;
    mbBackFlag = 1;
    Hu3DLayerHookSet(0, MBBackDraw);
    MBBackStreamStart();
    MBBackThreadPriHighSet();
    if (arg1 != 0) {
        MBCameraInit();
    }
    MBCameraSpeedDivSet(1.0f);
    MBBackTPLvlSet(0xFF);
    MBCameraSpeedSet(-1.0f);
    mbCameraFar = 0.0f;
    mbCameraNear = 0.0f;
    MBCameraZoomSet(1.0f);
}

void MBBackLoad(s32 arg0) {
    MBBackCreate(arg0, 1);
}

void MBBackKill(void) {
    if (mbBackFileOfsTbl != NULL) {
        HuMemMemoryFreeTemp(mbBackFileOfsTbl);
        mbBackFileOfsTbl = NULL;
        HuMemMemoryFreeTemp(mbBackHdr);
        HuMemMemoryFreeTemp(mbBackHvqFileHdr);
        Hu3DLayerHookSet(0, 0);
        MBBackStreamStop();
        MBCameraClose();
    }
}

static void MBBackOffsetSet(s16 arg0, s16 arg1) {
    mbBackOfsX = arg0;
    mbBackOfsY = arg1;
}


static f32 MBBackMaxXGet(void) {
    return ((mbBackHalfW - 160.0f) / mbBackScale) + 160.0f;
}

static f32 MBBackMaxYGet(void) {
    return ((mbBackHalfH - 120.0f) / mbBackScale) + 120.0f;
}

static u16 MBBackPosClamp(Vec2f* arg0, f32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg0->x <= (((-mbBackHalfW + 160.0f) / arg1) + 160.0f)) {
        arg0->x = ((-mbBackHalfW + 160.0f) / arg1) + 160.0f;
        var_v1 = 1;
    }
    if (((mbBackHalfW - 160.0f) / arg1) + 160.0f + ((320.0f / arg1) - (320.0f / (arg1 * mbBackZoom))) <= arg0->x) {
        arg0->x = ((mbBackHalfW - 160.0f) / arg1) + 160.0f + ((320.0f / arg1) - (320.0f / (arg1 * mbBackZoom)));
        var_v1 |= 2;
    }
    if (arg0->y <= ((-mbBackHalfH + 120.0f) / arg1) + 120.0f) {
        arg0->y = ((-mbBackHalfH + 120.0f) / arg1) + 120.0f;
        var_v1 |= 4;
    }
    if (((mbBackHalfH - 120.0f) / arg1) + 120.0f + ((240.0f / arg1) - (240.0f / (arg1 * mbBackZoom))) <= arg0->y) {
        arg0->y = ((mbBackHalfH - 120.0f) / arg1) + 120.0f + ((240.0f / arg1) - (240.0f / (arg1 * mbBackZoom)));
        var_v1 |= 8;
    }
    return var_v1;
}

void MBBackDispSet(u16 arg0) {
    if (arg0) {
        mbBackFlag = mbBackFlag | 1;
    } else {
        mbBackFlag = mbBackFlag & ~1;
    }
}

static void MBBackDmaProc(void) {
    OverlayBgEntry* sp10;

    while (1) {
        osRecvMesg(&mbBackDmaMesgQ, (OSMesg*)&sp10, 1);
        if (sp10 == NULL) {
            break;
        }
        dmaRead(sp10->romAddr, (u8 *)sp10->compressedData, sp10->compressedSize);
        osSendMesg(&mbBackDecodeMesgQ, (OSMesg*)sp10, 0);
    }

    osSendMesg(&mbBackExitMesgQ, (void* )1, 0);
    osDestroyThread(NULL);
}

#define SlideReadUint(buffer, src)    \
    do {                              \
        (buffer) = ((*src++) << 24);  \
        (buffer) += ((*src++) << 16); \
        (buffer) += ((*src++) << 8);  \
        (buffer) += (*src++);         \
    } while (0)

static void MBBackSlideDecode(u8 *input, u8 *output, s32 compressedSize) {
    u8 *src = input + 4;       // Skip metadata
    s32 flagLen = 0;           // Remaining bits in the bit buffer
    s32 flag = 0;              // Buffer holding bits for control decisions
    s32 size = compressedSize; // Bytes left to decompress
    u8 *matchPtr;              // Pointer for back-reference matches
    u32 offset, len;           // Offset and length for back-references
    u32 dist;                  // Temporary value for reading data

    while (size != 0) {
        // Refill the bit buffer if empty
        if (flagLen == 0) {
            SlideReadUint(flag, src);
            flagLen = 32;
        }

        // Determine if the next data is a literal or back-reference
        if (flag >> 31) {
            *output++ = *src++; // Write literal byte
            size--;
        } else {
            // Read the next 16 bits for the back-reference
            dist = (*src++ << 8);
            dist += (*src++);
            len = (dist >> 12) & 0xF;
            dist &= 0xFFF;
            // Calculate the pointer for the back-reference match
            matchPtr = output - dist;

            // Handle extended match lengths
            if (len == 0) {
                len = (*src++) + 0x12;
            } else {
                len += 2;
            }

            size -= len;
            if (size < 0) {
                break; // Prevent buffer overflow
            }

            // Copy the match data from the back-reference
            while (len > 0) {
                *output++ = matchPtr[-1];
                matchPtr++;
                len--;
            }
        }

        // Shift the bit buffer and decrement remaining bits
        flag <<= 1;
        flagLen--;

        // Exit if all bytes have been decompressed
        if (size == 0) {
            break;
        }
    }
}

// Decode a board image tile into RGBA5551 pixels.
static void MBBackDecodeProc(void) {
    OverlayBgEntry *sp10;
    HvqHeader *temp_a0;

    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(mbBackHvqFileHdr); //"HVQ-MPS 1.1"
    while (1) {
        osRecvMesg(&mbBackDecodeMesgQ, (void *)&sp10, 1);
        if (sp10 != NULL) {
            temp_a0 = sp10->compressedData;
            mbBackHvqCur = sp10->compressedData;
            if (temp_a0->magic == ASCII_HVQS) {
                hvqMpsDecode1(&temp_a0->data.image, sp10->pixels, 0x40, mbBackHvqWork);
            } else {
                // 0x1800 size for decoded tile
                MBBackSlideDecode(mbBackHvqCur->data.slide, (u8 *)sp10->pixels, 0x1800);
            }
            osSendMesg(&mbBackDoneMesgQ, sp10, 0);
        } else {
            break;
        }
    }

    osSendMesg(&mbBackExitMesgQ, (void *)2, 0);
    osDestroyThread(NULL);
}

static void MBBackThreadCreate(void) {
    osCreateMesgQueue(&mbBackDmaMesgQ, mbBackDmaMesgBuf, 0x24);
    osCreateMesgQueue(&mbBackDecodeMesgQ, mbBackDecodeMesgBuf, 0x24);
    osCreateMesgQueue(&mbBackDoneMesgQ, mbBackDoneMesgBuf, 0x24);
    osCreateMesgQueue(&mbBackExitMesgQ, mbBackExitMesgBuf, 2);
    mbBackThreadPri = 1;
    osCreateThread(&mbBackDecodeThread, 0x64, (void (*)(void*)) MBBackDecodeProc, NULL, &mbBackDecodeMesgQ, 1);
    osStartThread(&mbBackDecodeThread);
    osCreateThread(&mbBackDmaThread, 0x65, (void*)MBBackDmaProc, NULL, &mbBackDecodeThread, 4);
    osStartThread(&mbBackDmaThread);
}

void MBBackThreadPriHighSet(void) {
    mbBackThreadPri = 3;
}

void MBBackThreadPriLowSet(void) {
    mbBackThreadPri = 1;
}

static void MBBackThreadPriUpdate(void) {
    if (osGetThreadPri(&mbBackDecodeThread) != mbBackThreadPri) {
        osSetThreadPri(&mbBackDecodeThread, mbBackThreadPri);
    }
}

static void MBBackDoneFree(void) {
    OverlayBgEntry* sp10;

    while (1) {
        if (osRecvMesg(&mbBackDoneMesgQ, (OSMesg*)&sp10, 0) != 0) {
            break;
        }
        if (sp10 != NULL) {
            HuMemMemoryFreePerm(sp10->compressedData);
            sp10->compressedData = NULL;
        }
    }
}

static void MBBackThreadKill(void) {
    s32 i;

    osJamMesg(&mbBackDmaMesgQ, NULL, OS_MESG_NOBLOCK);
    osJamMesg(&mbBackDecodeMesgQ, NULL, OS_MESG_NOBLOCK);

    MBBackThreadPriHighSet();
    MBBackThreadPriUpdate();

    osRecvMesg(&mbBackExitMesgQ, NULL, OS_MESG_BLOCK);
    osRecvMesg(&mbBackExitMesgQ, NULL, OS_MESG_BLOCK);

    for (i = 0; i < ARRAY_COUNT(mbBackTileTbl); i++) {
        OverlayBgEntry* temp = &mbBackTileTbl[i];
        if (temp->compressedData != NULL) {
            HuMemMemoryFreePerm(temp->compressedData);
            temp->compressedData = NULL;
        }
    }
}

static void MBBackTileInit(void) {
    OverlayBgEntry* var_s0 = mbBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackTileTbl); i++, var_s0++) {
        var_s0->unk0 = 0;
        var_s0->unk1 = 0;
        var_s0->unk2 = -1;
        var_s0->pixels = HuMemAlloc(0x1800);
        var_s0->compressedData = NULL;
    }

    bzero(mbBackTileMap, sizeof(mbBackTileMap));
}

static void MBBackTileUseClear(void) {
    OverlayBgEntry* var_v1 = mbBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackTileTbl); i++, var_v1++) {
        if ((var_v1->compressedData == NULL) && (var_v1->unk0 == 0)) {
            var_v1->unk2 = -1;
        }
        var_v1->unk0 = 0;
    }
}

static void MBBackTileClose(void) {
    OverlayBgEntry* var_s0 = mbBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackTileTbl); i++, var_s0++) {
        var_s0->unk0 = 0;
        var_s0->unk2 = -1;

        if (var_s0->pixels != NULL) {
            HuMemFree(var_s0->pixels);
            var_s0->pixels = NULL;
        }
    }
}

void MBBackStreamStart(void) {
    MBBackTileInit();
    MBBackThreadCreate();
    mbBackFlag |= 4;
}

void MBBackStreamStop(void) {
    MBBackThreadKill();
    MBBackTileClose();
    mbBackFlag &= ~4;
}

void MBBackStreamOff(void) {
    mbBackFlag &= ~4;
}

f32 MBBackMdlScaleGet(void) {
    if (mbBackHdr == NULL) {
        return 1.0f;
    } else {
        return mbBackHdr->unk14;
    }
}

static u16 MBBackTileNoGet(s32 arg0, s32 arg1) {
    return ((((mbBackHdr->unkC - arg1) - 1) * mbBackHdr->unk8) + arg0 + 1);
}

static s32 MBBackFileSizeGet(u16 arg0) {
    arg0++;
    return mbBackFileOfsTbl[(arg0 + 1)] - mbBackFileOfsTbl[(arg0 + 0)];
}

static s32 MBBackFileAddrGet(u16 arg0) {
    arg0++;
    return mbBackFileAddr + mbBackFileOfsTbl[(arg0)];
}

static OverlayBgEntry *MBBackTileLoad(u16 arg0) {
    OverlayBgEntry *entry;
    OverlayBgEntry *slot;
    u16 bank;
    s32 i;
    s32 size;

    slot = NULL;
    entry = mbBackTileTbl;
    bank = 0;

    if (mbBackAltBank != 0) {
        for (i = 0; i < mbBackAltTbl[mbBackAltNo].unk_00 - 1; i++) {
            if (arg0 == mbBackAltTbl[mbBackAltNo].unk_04[i]) {
                bank = mbBackAltBank;
            }
        }
    }

    for (i = 0; i < 36; i++, entry++) {
        if (entry->unk2 == -1) {
            slot = entry;
        } else if (entry->unk2 == arg0) {
            if (entry->unk1 == bank) {
                entry->unk0 = 1;
                return entry;
            }
        }
    }

    if (slot != NULL) {
        slot->unk0 = 1;
        slot->unk2 = arg0;
        slot->unk1 = bank;
        slot->romAddr = MBBackFileAddrGet(arg0);
        size = MBBackFileSizeGet(arg0);
        slot->compressedSize = size;
        slot->compressedData = HuMemMemoryAllocPerm(size);
        osSendMesg(&mbBackDmaMesgQ, slot, OS_MESG_NOBLOCK);
    }
    return slot;
}

static void MBBackTileMapUpdate(void) {
    s32 tileX;
    s32 tileY;
    s32 x;
    s32 y;

    tileY = (s32)(((f32)((mbBackHalfH + mbBackOfsY) - 0x78) -
                   ((240.0f - (240.0f / mbBackZoom)) / 2.0f)) / 48.0f);

    for (y = 0; y < 6; y++, tileY++) {
        tileX = (s32)(((f32)((mbBackHalfW + mbBackOfsX) - 0xA0) -
                       ((320.0f - (320.0f / mbBackZoom)) / 2.0f)) / 64.0f);

        for (x = 0; x < 6; x++, tileX++) {
            if ((tileX < 0) || (tileY < 0) ||
                (tileX >= mbBackHdr->unk8) ||
                (tileY >= mbBackHdr->unkC)) {
                mbBackTileMap[x][y] = NULL;
            } else {
                mbBackTileMap[x][y] =
                    MBBackTileLoad(MBBackTileNoGet(tileX, tileY));
            }
        }
    }
}

#define gSPScisTextureRectangle_MP(pkt,xl,yl,xh,yh,tile,s,t,dsdx,dtdy) { \
    Gfx *_g = (pkt); \
    _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | \
    _SHIFTL(MAX((s16)(xh),0), 12, 12) | \
    _SHIFTL(MAX((s16)(yh),0), 0, 12)); \
    _g->words.w1 = (_SHIFTL((tile), 24, 3) | \
    _SHIFTL(MAX((s16)(xl),0), 12, 12) | \
    _SHIFTL(MAX((s16)(yl),0), 0, 12)); \
    gImmp1(pkt, G_RDPHALF_1, \
    (_SHIFTL(((s) - (((s16)(xl) < 0) ? (((s16)(dsdx) < 0) ? (MAX((((s16)(xl)*(s16)(dsdx))>>7),0)) : (MIN((((s16)(xl)*(s16)(dsdx))>>7),0))) : 0)), 16, 16) |\
    _SHIFTL(((t) - (((s32)(yl) < 0) ? (((s16)(dtdy) < 0) ? (MAX((((s16)(yl)*(s16)(dtdy))>>7),0)) : (MIN((((s16)(yl)*(s16)(dtdy))>>7),0))) : 0)), 0, 16))); \
    gImmp1(pkt, G_RDPHALF_2, (_SHIFTL((s16)(dsdx), 16, 16) | _SHIFTL((s16)(dtdy), 0, 16))); \
}

static void MBBackTileDraw(Gfx** arg0, u16* arg1, s16 arg2, s16 arg3, s16 arg4) {
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;

    temp_f20 = ((f32) arg2 + (mbCameraScrPos[0] / 4.0f)) - (f32) (s32) (mbCameraScrPos[0] / 4.0f);
    temp_f22 = ((f32) arg3 + (mbCameraScrPos[1] / 4.0f)) - (f32) (s32) (mbCameraScrPos[1] / 4.0f);
    HuLoadTextureBlock(arg0, arg1, 0, 2, 0x40, 0x20, 0, 0, 0x40, 0x20, 0, 1, 1, 6, 5, 0, 0);
    if (!(mbBackFlag & 0x10)) {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/(temp_f20 * mbBackZoom * 4.0f),
            /*yl*/((temp_f22 * mbBackZoom * 4.0f) - (f32) arg4),
            /*xh*/(temp_f20 + 64.0f) * mbBackZoom * 4.0f,
            /*yh*/(temp_f22 + 32.0f) * mbBackZoom * 4.0f,
            /*tile*/0,
            /*s*/0,
            /*t*/0,
            /*dsdx*/(1024.0f / mbBackZoom),
            /*dtdy*/(1024.0f / mbBackZoom)
        );
    } else {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/((256.0f - temp_f20) * mbBackZoom * 4.0f),
            /*yl*/((temp_f22 * mbBackZoom * 4.0f)),
            /*xh*/((320.0f - temp_f20) * mbBackZoom * 4.0f),
            /*yh*/((temp_f22 + 32.0f) * mbBackZoom * 4.0f),
            /*tile*/0,
            /*s*/0x7e0,
            /*t*/0,
            /*dsdx*/-(s16)(1024.0f / mbBackZoom),
            /*dtdy*/(1024.0f / mbBackZoom)
        );
    }
    HuLoadTextureBlock(arg0, arg1 + (64 * 32), 0, 2, 0x40, 0x10, 0, 0, 0x40, 0x10, 0, 1, 1, 6, 4, 0, 0);
    if (!(mbBackFlag & 0x10)) {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/(temp_f20 * mbBackZoom * 4.0f),
            /*yl*/((temp_f22 + 32.0f) * mbBackZoom * 4.0f),
            /*xh*/((temp_f20 + 64.0f) * mbBackZoom * 4.0f),
            /*yh*/((temp_f22 + 48.0f) * mbBackZoom * 4.0f),
            /*tile*/0,
            /*s*/0,
            /*t*/0,
            /*dsdx*/(1024.0f / mbBackZoom),
            /*dtdy*/(1024.0f / mbBackZoom)
        );
    } else {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/((256.0f - temp_f20) * mbBackZoom * 4.0f),
            /*yl*/((temp_f22 + 32.0f) * mbBackZoom * 4.0f),
            /*xh*/((320.0f - temp_f20) * mbBackZoom * 4.0f),
            /*yh*/((temp_f22 + 48.0f) * mbBackZoom * 4.0f),
            /*tile*/0,
            /*s*/0x7e0,
            /*t*/0,
            /*dsdx*/-(s16)(1024.0f / mbBackZoom),
            /*dtdy*/(1024.0f / mbBackZoom)
        );
    }
}

static void MBBackDraw(Gfx** arg0, s32 arg1, u8 arg2) {
    u16 sp1E;
    u16 sp26;
    s16 spY; // sp34
    s16 spX;
    s16 row;
    s16 col;
    s32 i;
    s16 temp_s0;
    OverlayBgEntry* bgEntry;

    if (arg2 || !(mbBackFlag & 4)) {
        return;
    }

    MBBackDoneFree();
    if (!(mbBackFlag & 1)) {
        return;
    }

    MBBackTileUseClear();
    temp_s0 = HuProfCpuBegin(0xC8, 0, 0);
    MBBackTileMapUpdate();
    HuProfCpuEnd(temp_s0);

    sp26 = ((mbBackHalfH + mbBackOfsY) - 120) % 48;
    sp1E = ((mbBackHalfW + mbBackOfsX) - 160) % 64;

    spY = (s32)(((f32)(((mbBackHalfH + mbBackOfsY)) - 120) - ((240.0f - (240.0f / mbBackZoom)) / 2.0f)) / 48.0f) - ((((mbBackHalfH + mbBackOfsY)) - 120) / 48);
    spX = (s32)(((f32)(((mbBackHalfW + mbBackOfsX)) - 160) - ((320.0f - (320.0f / mbBackZoom)) / 2.0f)) / 64.0f) - ((((mbBackHalfW + mbBackOfsX)) - 160) / 64);

    gSPDisplayList((*arg0)++, mbBackGfxInit);
    gDPSetEnvColor((*arg0)++, 0xFF, 0xFF, 0xFF, mbBackTPLvl);

    if (mbBackTPLvl < 0xFF) {
        if (mbBackFlag & 8) {
            gDPSetCombineLERP((*arg0)++, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT);
        } else {
            gDPSetCombineLERP((*arg0)++, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT);
        }
        gDPSetRenderMode((*arg0)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    } else {
        if (mbBackFlag & 8) {
            gDPSetCombineLERP((*arg0)++, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0);
        }

        gDPSetRenderMode((*arg0)++, G_RM_AA_SUB_SURF, G_RM_AA_SUB_SURF2);
    }

    for (row = 0; row < 6; row++) {
        for (col = 0; col < 6; col++) {
            bgEntry = mbBackTileMap[col][row];
            if (bgEntry == NULL) {
                continue;
            }

            if (mbBackAltF != 0 && mbBackAltTPLvl == 0xFF) {
                for (i = 0; i < (mbBackAltTbl->unk_00 - 1) && i < 0x24; i++) {
                    if (bgEntry->unk2 == mbBackAltTileTbl[i].unk2) {
                        break;
                    }
                }
                if (i != (mbBackAltTbl->unk_00 - 1) && i != 0x24) {
                    bgEntry = &mbBackAltTileTbl[i];
                }
            }

            MBBackTileDraw(
                arg0,
                bgEntry->pixels,
                ((col + spX) * 64) - sp1E,
                ((row + spY) * 48) - sp26,
                0
            );

            if (mbBackAltF != 0 && mbBackAltTPLvl > 0 && mbBackAltTPLvl < 0xFF) {
                for (i = 0; i < (mbBackAltTbl->unk_00 - 1) && i < 0x24; i++) {
                    if (bgEntry->unk2 == mbBackAltTileTbl[i].unk2) {
                        break;
                    }
                }
                if (i != (mbBackAltTbl->unk_00 - 1) && i != 0x24) {
                    bgEntry = &mbBackAltTileTbl[i];
                    gDPSetEnvColor((*arg0)++, 0xFF, 0xFF, 0xFF, mbBackAltTPLvl);
                    gDPSetCombineLERP((*arg0)++, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT);
                    gDPSetRenderMode((*arg0)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

                    MBBackTileDraw(
                        arg0,
                        bgEntry->pixels,
                        ((col + spX) * 64) - sp1E,
                        ((row + spY) * 48) - sp26,
                        -1
                    );

                    gDPSetEnvColor((*arg0)++, 0xFF, 0xFF, 0xFF, mbBackTPLvl);
                    gDPSetCombineMode((*arg0)++, G_CC_DECALRGBA, G_CC_DECALRGBA);
                    gDPSetRenderMode((*arg0)++, G_RM_AA_SUB_SURF, G_RM_AA_SUB_SURF2);
                }
            }
        }
    }

    MBBackThreadPriUpdate();
}

f32 MBCameraZoomGet(void) {
    return mbBackZoom;
}

void MBCameraZoomSet(f32 zoom) {
    mbBackZoom = zoom;
}

static void MBCameraZoomMotProc(void) {
    f32 target;
    f32 diff;
    f32 step;
    f32 next;
    f32 temp;

    target = *(f32 *)HuPrcCurrentGet()->user_data;

    while (1) {
        diff = mbBackZoom - target;
        step = (0.0f < diff) ? diff : 0.0f - (mbBackZoom - target);
        
        if (step <= 0.005f) {
            break;
        }
        
        step /= 4.0f;
        if (step < 0.005f) {
            step = 0.005f;
        }
        if (target < mbBackZoom) {
            next = mbBackZoom - step;
        } else {
            next = step + mbBackZoom;
        }
        mbBackZoom = next;
        HuPrcVSleep();
    }

    mbBackZoom = target;
    mbCameraZoomProc = NULL;
    omDelPrcObj(NULL);
}

Process* MBCameraZoomMotStart(f32 arg0) {
    Process* temp_v0;
    f32* temp_v0_2;

    if (mbCameraZoomProc != NULL) {
        omDelPrcObj(mbCameraZoomProc);
    }
    mbCameraZoomProc = omAddPrcObj(MBCameraZoomMotProc, 1U, 0, 0x40);

    temp_v0_2 = HuMemMemoryAlloc(mbCameraZoomProc->heap, 0x10);
    mbCameraZoomProc->user_data = temp_v0_2;
    *temp_v0_2 = arg0;
    return mbCameraZoomProc;
}

static void MBCameraZoomMotFastProc(void) {
    f32 temp_f22;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f20;
    s32 var_s0;
    s32 i;

    temp_f22 = *(f32*)HuPrcCurrentGet()->user_data;
    temp_f2 = mbBackZoom - temp_f22;
    if (temp_f2 > 0.0f) {
        var_f20 = temp_f2 / 5.0f;
    } else {
        var_f20 = (0.0f - (mbBackZoom - temp_f22)) / 5.0f;
    }
    for (i = 0; i < 5; i++, HuPrcVSleep()) {
        if (temp_f22 < mbBackZoom) {
            mbBackZoom = mbBackZoom - var_f20;
        } else {
            mbBackZoom = var_f20 + mbBackZoom;
        }
    }

    mbBackZoom = temp_f22;
    mbCameraZoomProc = NULL;
    omDelPrcObj(NULL);
}

Process* MBCameraZoomMotFastStart(f32 arg0) {
    Process* proc;
    f32* temp_v0_2;

    if (mbCameraZoomProc != NULL) {
        omDelPrcObj(mbCameraZoomProc);
    }

    proc = omAddPrcObj(MBCameraZoomMotFastProc, 1, 0, 0x40);
    mbCameraZoomProc = proc;
    temp_v0_2 = HuMemMemoryAlloc(proc->heap, 0x10);
    mbCameraZoomProc->user_data = temp_v0_2;
    *temp_v0_2 = arg0;
    return mbCameraZoomProc;
}

static void MBCameraInit(void) {
    Process* temp_v0;
    f32 temp_f2;
    f32 temp_f4;

    temp_f2 = (f32) (mbBackHdr->unk4 * mbBackHdr->unkC) / 240.0f;
    mbBackScale = temp_f2;
    temp_f4 = (f32) (mbBackHdr->unk0 * mbBackHdr->unk8) / 320.0f;
    if (temp_f2 < temp_f4) {
        mbBackScale = temp_f4;
    }
    mbCameraEye.x = mbBackHdr->unk18;
    mbCameraEye.y = mbBackHdr->unk1C;
    mbCameraEye.z = mbBackHdr->unk20;
    mbCameraAt.x = mbBackHdr->unk24;
    mbCameraAt.y = mbBackHdr->unk28;
    mbCameraAt.z = mbBackHdr->unk2C;
    mbCameraUp.x = mbBackHdr->unk30;
    mbCameraUp.y = mbBackHdr->unk34;
    mbCameraUp.z = mbBackHdr->unk38;
    mbCameraViewportSize.x = (mbBackScale * 640.0f);
    mbCameraViewportSize.y = (mbBackScale * 480.0f);
    mbCameraViewportSize.z = 511.0f;
    mbCameraScrPos[0] = 640.0f;
    mbCameraScrPos[1] = 480.0f;
    mbCameraScrTarget.x = 159.5f;
    mbCameraScrTarget.y = 119.5f;
    mbCameraSpeedDiv = 1.0f;
    temp_v0 = omAddPrcObj(MBCameraUpdateMain, 0x1001, 0, 0);
    mbCameraUpdateProc = temp_v0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    mbCameraZoomProc = 0;
    Hu3DCameraPerspectiveSet(0, mbBackHdr->unk10, 10.0f, 200.0f);
    Hu3DCameraPosSetV(0, &mbCameraEye, &mbCameraAt, &mbCameraUp);
    Hu3DCamUpdateMtx(0);
}

void MBCameraKill(void) {
    if (mbCameraUpdateProc != NULL) {
        omDelPrcObj(mbCameraUpdateProc);
        mbCameraUpdateProc = NULL;
    }
    if (mbCameraZoomProc != NULL) {
        omDelPrcObj(mbCameraZoomProc);
        mbCameraZoomProc = NULL;
    }
}

static void MBCameraClose(void) {
    MBCameraKill();
}

void MBCameraNearFarSet(f32 arg0, f32 arg1) {
    mbCameraNear = arg0;
    mbCameraFar = arg1;
}

static void MBCameraUpdateMain(void) {
    Vec sp10;
    s16 sp20[2];
    Vec sp28;
    Vec sp38;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f2;

    while (1) {
        temp_f4 = HuVecDistance(&mbCameraEye, &mbCameraAt);
        var_f2 = mbCameraFar;
        if ((var_f2 == 0.0f) || (var_f0 = mbCameraNear, (var_f0 == 0.0f))) {
            var_f2 = temp_f4 + 1000.0f;
            var_f0 = var_f2 - 2000.0f;
        }
        if (var_f0 < 10.0f) {
            var_f0 = 10.0f;
        }
        Hu3DCameraPerspectiveSet(0, mbBackHdr->unk10, var_f0, var_f2);
        Hu3DCameraPosSetV(0, &mbCameraEye, &mbCameraAt, &mbCameraUp);
        Hu3DCamUpdateMtx(0);

        sp38.x = ((((mbCameraScrTarget.x - 160.0f) * mbBackScale * -4.0f) + 640.0f) - mbCameraScrPos[0]) / mbCameraSpeedDiv;
        sp38.y = ((((mbCameraScrTarget.y - 120.0f) * mbBackScale * -4.0f) + 480.0f) - mbCameraScrPos[1]) / mbCameraSpeedDiv;
        sp38.z = 0.0f;

        temp_f2 = HuVecGetLength3F(&sp38) / 4.0f;

        if (temp_f2 <= 1.0f) {
            mbBackFlag &= 0xFFFD;
            mbCameraScrPos[0] = ((mbCameraScrTarget.x - 160.0f) * mbBackScale * -4.0f) + 640.0f;
            mbCameraScrPos[1] = ((mbCameraScrTarget.y - 120.0f) * mbBackScale * -4.0f) + 480.0f;
        } else {
            mbBackFlag |= 2;
            if ((mbCameraSpeed >= 0.0f) && (mbCameraSpeed < temp_f2)) {
                MBVecNormalize(&sp38);
                HuVecMulScalar(&sp38, mbCameraSpeed * 4.0f, &sp38);
            }
            mbCameraScrPos[0] += sp38.x;
            mbCameraScrPos[1] = mbCameraScrPos[1] + sp38.y;
        }

        sp20[0] = mbCameraScrPos[0] / 4.0f;
        sp20[1] = mbCameraScrPos[1] / 4.0f;

        sp10.x = mbCameraScrPos[0] * mbBackZoom;
        sp10.y = mbCameraScrPos[1] * mbBackZoom;
        sp10.z = 511.5f;

        sp28.x = mbBackScale * 640.0f * mbBackZoom;
        sp28.y = mbBackScale * 480.0f * mbBackZoom;
        sp28.z = 511.0f;

        Hu3DCameraViewportSet(0, &sp28, &sp10);
        MBBackOffsetSet(-sp20[0] + 0xA0, -sp20[1] + 0x78);
        HuPrcVSleep();
    }
}

void MBCameraSpeedDivSet(f32 arg0) {
    mbCameraSpeedDiv = arg0;
}

f32 MBCameraSpeedDivGet(void) {
    return mbCameraSpeedDiv;
}

u16 MBCameraPos3DSet(Vec *arg0) {
    Vec sp10;
    f32 scale;
    f32 halfW;
    f32 halfH;
    Vec2f* temp;
    
    mbCameraFocusPos.x = arg0->x;
    mbCameraFocusPos.y = arg0->y;
    mbCameraFocusPos.z = arg0->z;

    HuVecCopyXYZ(&sp10, arg0->x, arg0->y + 10.0f, arg0->z);
    Hu3D3Dto2D(0, &sp10, &mbCameraScrTarget);

    temp = &mbCameraScrTarget;

    halfW = 320.0f / (2.0f * mbBackScale);
    temp->x += halfW - (halfW / mbBackZoom);

    halfH = 240.0f / (2.0f * mbBackScale);
    mbCameraScrTarget.y += halfH - (halfH / mbBackZoom);

    return MBBackPosClamp(&mbCameraScrTarget, mbBackScale);
}

u16 MBCameraPos2DSet(Vec2f* arg0) {
    mbCameraScrTarget.x = arg0->x / mbBackScale + 160.0f;
    mbCameraScrTarget.y = arg0->y / mbBackScale + 120.0f;
    return MBBackPosClamp(&mbCameraScrTarget, mbBackScale);
}

void MBCameraPos3DGet(Vec2f* arg0) {
    arg0->x = (mbCameraScrTarget.x - 160.0f) * mbBackScale;
    arg0->y = (mbCameraScrTarget.y - 120.0f) * mbBackScale;
}

void MBCameraPos2DGet(Vec2f *arg0) {
    arg0->x = -((mbCameraScrPos[0] / 4.0f) - 160.0f);
    arg0->y = -((mbCameraScrPos[1] / 4.0f) - 120.0f);
}

void MBCamera3Dto2D(Vec* arg0, f32* arg1) {
    UnkCam3DStruct sp10;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f6;

    Hu3D3Dto2D(0, arg0, &sp10.unk_00);
    temp_f6 = 2.0f * mbBackScale;
    temp_f2 = 320.0f / temp_f6;
    sp10.unk_00.x = (temp_f2 - (temp_f2 / mbBackZoom)) + sp10.unk_00.x;
    temp_f0 = 240.0f / temp_f6;
    sp10.unk_00.y =  (temp_f0 - (temp_f0 / mbBackZoom)) + sp10.unk_00.y;
    sp10.unk_00.x = ((sp10.unk_00.x - 160.0f) * mbBackScale) + 160.0f;
    sp10.unk_00.y = ((sp10.unk_00.y - 120.0f) * mbBackScale) + 120.0f;
    sp10.unk_08 = (mbCameraScrPos[0] / 4.0f) - 160.0f;
    sp10.unk_0C = (mbCameraScrPos[1] / 4.0f) - 120.0f;
    arg1[0] = sp10.unk_00.x + sp10.unk_08;
    arg1[1] = sp10.unk_00.y + sp10.unk_0C;
}

void MBBackTPLvlSet(u8 arg0) {
    mbBackTPLvl = arg0;
}

void MBBackInvertSet(s16 arg0) {
    if (arg0) {
        mbBackFlag |= 8;
    } else {
        mbBackFlag &= ~8;
    }
}

void MBBackFlipSet(s16 arg0) {
    if (arg0) {
        mbBackFlag |= 0x10;
    } else {
        mbBackFlag &= ~0x10;
    }
}

void MBCameraSpeedSet(f32 arg0) {
    mbCameraSpeed = arg0;
}

f32 MBCameraSpeedGet(void) {
    return mbCameraSpeed;
}

s32 MBCameraStopCheck(void) {
    return mbBackFlag & 2;
}

void MBBackRefresh(Vec* arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f22;

    MBBackStreamStop();
    MBBackStreamStart();
    temp_f22 = MBCameraSpeedGet();
    MBCameraSpeedSet(-1.0f);
    temp_f20 = MBCameraSpeedDivGet();
    MBCameraSpeedDivSet(1.0f);
    MBBackThreadPriHighSet();
    
    if (arg0 != NULL) {
        MBCameraPos3DSet(arg0);
    }
    HuPrcVSleep();
    
    if (arg1 != 0) {
        MBBackThreadPriLowSet();
    }
    
    MBCameraSpeedDivSet(temp_f20);
    MBCameraSpeedSet(temp_f22);
}


void MBBackArcInitDef(void) {
    MBBackArcInit((u32)hvq_data_ROM_START);
}

void MBBackCreateNoCamera(s32 arg0) {
    MBBackCreate(arg0, 1);
    omDelPrcObj(mbCameraUpdateProc);
    mbCameraUpdateProc = NULL;
}

void MBCameraOffsetSet(s16 arg0, s16 arg1) {
    MBBackOffsetSet(arg0, arg1);
}

void MBCameraScrPosSet(s16 arg0, s16 arg1) {
    mbCameraScrTarget.x = (arg0 / mbBackScale) + 160.0f;
    mbCameraScrTarget.y = (arg1 / mbBackScale) + 120.0f;
}


static void MBBackSprMain(void) {
    UnkBoard7 *obj;
    f32 pos[2];
    f32 maxX, maxY;
    f32 x, y;
    s32 i;

    while (TRUE) {
        for (i = 0; i < ARRAY_COUNT(mbBackSprTbl); i++) {
            obj = &mbBackSprTbl[i];

            if (!(obj->unk_00 & 1)) {
                continue;
            }

            MBCamera3Dto2D(&obj->pos, pos);

            if (obj->unk_01 != 0) {
                HuSprPosSet(obj->unk_02, 0, (mbCameraScrPos[0] / (f32)obj->unk_01) + pos[0], (mbCameraScrPos[1] / (f32)obj->unk_01) + pos[1]);
            } else {
                HuSprPosSet(obj->unk_02, 0, pos[0], pos[1]);
            }
            
            HuSprTPLvlSet(obj->unk_02, 0, obj->unk_06);

            if (obj->vel.x != 0.0f) {
                maxX = MBBackMaxXGet();
                obj->pos.x += obj->vel.x;
                if (obj->pos.x >= maxX) {
                    obj->pos.x -= 2.0f * maxX;
                }
                if (obj->pos.x <= -maxX) {
                    obj->pos.x += 2.0f * maxX;
                }
            }

            if (obj->vel.z != 0.0f) {
                maxY = MBBackMaxYGet() * 1.5f;
                obj->pos.z += obj->vel.z;
                if (obj->pos.z >= maxY) {
                    obj->pos.z -= 2.0f * maxY;
                }
                if (obj->pos.z <= -maxY) {
                    obj->pos.z += 2.0f * maxY;
                }
            }

            if (obj->vel.y != 0.0f) {
                obj->pos.y += obj->vel.y;
            }

            if (mbBackSprDispF != 0) {
                HuSprDispOn(obj->unk_02, 0);
            } else {
                HuSprDispOff(obj->unk_02, 0);
            }
        }
        HuPrcVSleep();
    }
}

void MBBackSprInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackSprTbl); i++) {
        mbBackSprTbl[i].unk_00 = 0;
    }

    mbBackSprNum = 0;
}

s32 MBBackSprCreate(s32 arg0, Vec *arg1) {
    UnkBoard7 *obj;
    Process *proc;
    void *data;
    s32 count;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackSprTbl); i++) {
        obj = &mbBackSprTbl[i];
        if (obj->unk_00 & 1) {
            continue;
        }
    
        obj->unk_00 = 1;
        obj->unk_06 = 0x100;
        obj->unk_01 = 0;
    
        HuVecCopy3F(&obj->pos, arg1);
        HuVecCopyXYZ(&obj->vel, 0, 0, 0);
    
        obj->unk_02 = HuSprGrpCreate(1, 0);
    
        data = DataRead(arg0);
        obj->unk_04 = HuSprAnimRead(data);
        DataClose(data);
    
        HuSprGrpMemberSet(obj->unk_02, 0, obj->unk_04, 0);
        HuSprAnimModeSet(obj->unk_02, 0, HUSPR_ANIM_MODE_BANK);
        HuSprPriSet(obj->unk_02, 0, 0x8000);
        HuSprAttrSet(obj->unk_02, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
        HuSprScissorSet(obj->unk_02, 0, 0x10, 0xC, 0x130, 0xE4);
    
        if (mbBackSprNum == 0) {
            proc = omAddPrcObj(MBBackSprMain, 0x1001, 0, 0);
            mbBackSprProc = proc;
            omPrcSetStatBit(proc, OM_STAT_NOALLPAUSE);
        }
        
        mbBackSprNum++;
        return i;
    }
    return -1;
}

s32 MBBackSprCopyCreate(s32 arg0, Vec *arg1) {
    UnkBoard7 *unkBoard7;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackSprTbl); i++) {
        unkBoard7 = &mbBackSprTbl[i];
        if (unkBoard7->unk_00 & 1) {
            continue;
        }

        unkBoard7->unk_00 = 3;
        unkBoard7->unk_06 = 0x100;
        unkBoard7->unk_01 = 0;

        HuVecCopy3F(&unkBoard7->pos, arg1);
        HuVecCopyXYZ(&unkBoard7->vel, 0, 0, 0);

        unkBoard7->unk_02 = HuSprGrpCreate(1, 0);

        HuSprGrpMemberSet(unkBoard7->unk_02, 0,
                            mbBackSprTbl[arg0].unk_04, 0);
        HuSprAnimModeSet(unkBoard7->unk_02, 0, HUSPR_ANIM_MODE_BANK);
        HuSprPriSet(unkBoard7->unk_02, 0, 0x8000);
        HuSprAttrSet(unkBoard7->unk_02, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
        HuSprScissorSet(unkBoard7->unk_02, 0, 0x10, 0xC, 0x130, 0xE4);

        mbBackSprNum++;
        return i;
    }
    return -1;
}

static void MBBackSprKill(s32 arg0) {
    UnkBoard7* temp_s0 = &mbBackSprTbl[arg0];

    if (temp_s0->unk_00 & 1) {
        if (!(temp_s0->unk_00 & 2)) {
            HuSprAnimKill(temp_s0->unk_04);
        }
        HuSprGrpKill(temp_s0->unk_02);
        temp_s0->unk_00 = 0;
        mbBackSprNum--;
        if (mbBackSprNum == 0) {
            omDelPrcObj(mbBackSprProc);
            mbBackSprProc = NULL;
        }
    }
}

void MBBackSprKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbBackSprTbl); i++) {
        MBBackSprKill(i);
    }
}

void MBBackSprParallaxSet(s32 arg0, s8 arg1) {
    mbBackSprTbl[arg0].unk_01 = arg1;
}

void MBBackSprTPLvlSet(s32 arg0, s16 arg1) {
    mbBackSprTbl[arg0].unk_06 = arg1;
}

void MBBackSprColorSet(s32 arg0, RGB* arg1) {
    HuSprColorSet(mbBackSprTbl[arg0].unk_02, 0, arg1->r, arg1->g, arg1->b);
}

void MBBackSprVelSet(s32 arg0, Vec* arg1) {
    HuVecCopy3F(&mbBackSprTbl[arg0].vel, arg1);
}

void MBBackSprDispOn(void) {
    mbBackSprDispF = 1;
}

void MBBackSprDispOff(void) {
    mbBackSprDispF = 0;
}

void MBBackColorModeSet(s16 arg0) {
    OverlayBgEntry *entry;
    u16 color;
    u8 r, g, b;
    s32 lum;
    s32 gray;
    s32 i;
    u32 offset;

    switch (arg0) {
        case 0:
            MBBackRefresh(NULL, 0);
            break;

        case 1:
            for (i = 0; i < ARRAY_COUNT(mbBackTileTbl); i++) {
                entry = &mbBackTileTbl[i];
                if (entry->pixels == NULL) {
                    continue;
                }

                for (offset = 0; offset < BG_TEX_SIZE; offset += 2) {
                    color = BG_TEXEL(entry, offset);
                    r = (((color >> 11) & 0x1F) * 8) + 4;
                    g = (((color >>  6) & 0x1F) * 8) + 4;
                    b = (((color >>  1) & 0x1F) * 8) + 4;

                    lum = (r * 0.299f) + (g * 0.587f) + (b * 0.114f);
                    if (lum > 255) {
                        lum = 255;
                    }
                    lum = (lum >> 3) & 0x1F;
                    gray = (lum << 11) + (lum << 6) + (lum << 1);
                    BG_TEXEL(entry, offset) = gray;
                }
            }
            break;
    }
}

void MBBackIdleProc(void) {
    while (1) {
        HuPrcVSleep();
    }
}

static void MBMasuBmpCreate(s16 arg0) {
    s32 *var_s2;
    s32 i;

    mbMasuBmpMode = arg0;

    switch (arg0) {
        case 0:
        default:
            var_s2 = mbMasuBmpTbl;
            break;
        case 1:
            var_s2 = mbMasuBmpAltTbl;
            break;
    }

    for (i = 0; i < SPACE_TYPES_TOTAL; i++) {
        if (var_s2[i] != 0) {
            mbMasuBmpDataTbl[i] = DataRead(var_s2[i]);
        } else {
            mbMasuBmpDataTbl[i] = NULL;
        }
    }
}

static void MBMasuBmpKill(void) {
    s32 i;

    for (i = 0; i < SPACE_TYPES_TOTAL; i++) {
        if (mbMasuBmpDataTbl[i] != 0) {
            DataClose(mbMasuBmpDataTbl[i]);
        }
        mbMasuBmpDataTbl[i] = 0;
    }
}

void MBMasuInit(void) {
    s32 i;

    MBMasuBmpCreate(0);
    mbMasuData = 0;
    mbMasuArrowAngleNum = 0;

    for (i = 0; i < 16; i++) {
        mbMasuFlagTbl[i] = 0;
    }
}

void MBMasuArrowAngleAdd(f32 arg0) {
    if (mbMasuArrowAngleNum != 8) {
        mbMasuArrowAngleTbl[mbMasuArrowAngleNum++] = arg0;
    }
}

void MBMasuClose(void) {
    MBMasuBmpKill();
}

void MBMasuBmpModeSet(s16 arg0) {
    MBMasuBmpKill();
    MBMasuBmpCreate(arg0);
}

void MBMasuStarSet(s32 arg0, s16 arg1) {
    mbMasuStarTbl[arg0] = arg1;
}

extern s16 mbMasuBmpMode;
extern u16 mbMasuDispF;

static void MBMasuDraw(Gfx **arg0, Mtx *arg1, s32 arg2) {
    Gfx **gfxPos = arg0;
    HuMtx4F sp10;
    Vec2f sp50;
    Mtx *sp5C;
    Vtx *sp64;
    u8 *sp6C;
    s32 sp74;
    u16 sp7E;
    s32 sp84;
    s32 sp94;
    SpaceData *temp_s0;
    s16 var_v0;
    Mtx *temp_s0_3;
    s32 i, j;
    s32 var_s5;
    u32 temp_s4;

    sp5C = arg1;
    var_s5 = 0;
    if (!(arg2 & 0xFF) && (mbMasuDispF != 0) && (mbMasuTypeListTbl != 0)) {
        sp7E = HuProfCpuBegin(0xC8, 0xC8, 0xC8);
        gSPDisplayList((*gfxPos)++, mbMasuGfxInit);
        Hu3DCameraSet(0, gfxPos);
        Hu3DCameraScissorDraw(0, gfxPos);
        MBCameraPos3DGet(&sp50);

        if ((mbMasuBmpMode == 0) || (var_v0 = 8, (mbMasuBmpMode != 1))) {
            var_v0 = 0x10;
            sp64 = (Vtx *)OS_K0_TO_PHYSICAL(mbMasuVtx);
            sp6C = mbMasuBmpSizeTbl;
            sp74 = 0;
        } else {
            var_v0 = 8;
            sp64 = (Vtx *)OS_K0_TO_PHYSICAL(mbMasuAltVtx);
            sp6C = NULL;
            sp74 = 1;
        }
        // iterate over all space types
        for (i = 0; i < SPACE_TYPES_TOTAL; i++) {
            if (mbMasuBmpDataTbl[i] != 0) {
                if (sp74 == 0) {
                    switch (sp6C[i]) {
                        case 0:
                            gDPLoadTextureBlock((*gfxPos)++, mbMasuBmpDataTbl[i] + 0x10, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                                                32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                            break;
                        case 1:
                            // + 0x10 to skip image header data
                            gDPLoadTextureBlock((*gfxPos)++, mbMasuBmpDataTbl[i] + 0x10, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                                                16, 32, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                            break;
                        case 2:
                            gDPLoadTextureBlock((*gfxPos)++, mbMasuBmpDataTbl[i] + 0x10, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                                                16, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
                            break;
                    }
                } else {
                    gDPLoadTextureBlock((*gfxPos)++, mbMasuBmpDataTbl[i] + 0x10, G_IM_FMT_RGBA, G_IM_SIZ_32b,
                                        var_v0, var_v0, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
                }
                // read over a space types space array
                for (j = 0; j < gTotalSpaces; j++) {
                    s32 spaceId = mbMasuTypeListTbl[i][j];
                    if (spaceId == 0xff) {
                        break;
                    }
                    temp_s0 = MBMasuGet(spaceId);
                    HuMtxL2F(sp10, &sp5C[1]);
                    mtxTransCat(sp10, temp_s0->coords.x, temp_s0->coords.y, temp_s0->coords.z);
                    if ((i == 0xD) && (var_s5 < mbMasuArrowAngleNum)) {
                        mtxRotYCat(sp10, mbMasuArrowAngleTbl[var_s5++]);
                    }
                    mtxScaleCat(sp10, temp_s0->rot.x, 1.0f, temp_s0->rot.z);
                    temp_s0_3 = &MTXBuf[MTXBufNum++];
                    HuMtxF2L(sp10, temp_s0_3);
                    gSPMatrix((*gfxPos)++, OS_K0_TO_PHYSICAL(temp_s0_3), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex((*gfxPos)++, sp64, 4, 0);
                    gSP1Quadrangle((*gfxPos)++, 0, 1, 2, 3, 0);
                }
            }
        }

        HuProfCpuEnd(sp7E);
    }
}

//TODO: how is this meant to be written?
u16 *MBMasuDataOfsGet(u16 *base, s32 offset) {
    return (u16 *)((u8 *)base + *(u16 *)((u8 *)base + offset));
}

s32 MBMasuCreate(s32 arg0, s32 arg1) {
    f32 sp10[3];
    LinkData* var_s1_2;
    SpaceData* var_s1;
    s16* temp_v0_3;
    u16* var_s0_2;
    s32 var_s2;
    s32 var_v1;
    u16* temp_s3;
    u16* temp_v0_2;
    struct var_s0* var_s0;

    mbMasuData = DataRead((arg0 << 0x10) | (arg1 << 0x10 >> 0x10));
    if (mbMasuData != NULL) {
        mbMasuEventBoardStartTbl = 0;
        mbMasuEventRoundEndTbl = 0;
        mbMasuEventTurnStartTbl = 0;
        mbMasuEventTurnTelopTbl = 0;
        var_s0_2 = mbMasuData;
        gTotalSpaces = var_s0_2[0];
        mbMasuLinkNum = var_s0_2[1];
        mbMasuTbl = HuMemMemoryAllocTemp(gTotalSpaces * 0x24);
        var_s0_2 = MBMasuDataOfsGet(mbMasuData, 4);
        var_s1 = mbMasuTbl;
        for (var_s2 = 0; var_s2 < gTotalSpaces; var_s2++) {
            var_s1->unk_00 = 1;
            var_s1->unk_02 = *var_s0_2++;
            var_s1->space_type = *var_s0_2++;
            sp10[0] = var_s1->coords.x = (((f32*)var_s0_2))[0] * 5.0f * MBBackMdlScaleGet();
            sp10[1] = var_s1->coords.y = (((f32*)var_s0_2))[1] * 5.0f * MBBackMdlScaleGet();
            sp10[2] = var_s1->coords.z = (((f32*)var_s0_2))[2] * 5.0f * MBBackMdlScaleGet();
            var_s0_2 += 6;
            var_s1->rot.x = MBBackMdlScaleGet();
            var_s1->rot.y = MBBackMdlScaleGet();
            var_s1->rot.z = MBBackMdlScaleGet();
            var_s1->event_list = NULL;
            var_s1 += 1;
        }
        (void)sp10; // Suppress unused variable warning
        mbMasuLinkTbl = HuMemMemoryAllocTemp(mbMasuLinkNum * 8);
        temp_s3 = MBMasuDataOfsGet(mbMasuData, 6);
        var_s1_2 = mbMasuLinkTbl;
        for (var_s2 = 0; var_s2 < mbMasuLinkNum; var_s2++) {
            var_s0_2 = MBMasuDataOfsGet(temp_s3, var_s2 * 2);
            var_s1_2->chainIndicies = *var_s0_2++;
            var_s1_2->spaces = HuMemMemoryAllocTemp(((var_s1_2->chainIndicies << 1)));
            temp_v0_3 = var_s1_2->spaces;
            for (var_v1 = 0; var_v1 < var_s1_2->chainIndicies; var_v1++) {
                *temp_v0_3++ = *var_s0_2++;
            }
            var_s1_2 += 1;
        }
        DataClose(mbMasuData);
        Hu3DLayerHookSet(1, &MBMasuDraw);
        mbMasuDispF = 1;
    }
    mbMasuBlockExtNum = 0;
    mbMasuBlockNum = 0;

    return 0;
}

void MBMasuKill(void) {
    LinkData* var_s1;
    s32 i;

    if (mbMasuData != NULL) {
        mbMasuData = NULL;
        mbMasuDispF = 0;
        HuMemMemoryFreeTemp(mbMasuTbl);
        
        var_s1 = mbMasuLinkTbl;
        for (i = 0; i < mbMasuLinkNum; i++, var_s1++) {
            HuMemMemoryFreeTemp(var_s1->spaces);
        }
        
        HuMemMemoryFreeTemp(mbMasuLinkTbl);
        Hu3DLayerHookSet(1, NULL);
    }
    if (mbMasuTypeListTbl != NULL) {
        HuMemMemoryFreeTemp(mbMasuTypeListTbl);
        mbMasuTypeListTbl = NULL;
    }
}

//file split?

SpaceData *MBMasuGet(s16 arg0) {
    return &mbMasuTbl[arg0];
}

s16 MBMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx) {
    return mbMasuLinkTbl[linkIdx].spaces[spaceIdx];
}

s16 MBMasuLinkNumGet(u16 arg0) {
    return mbMasuLinkTbl[arg0].chainIndicies;
}

static s16 MBMasuLinkSearch(s16 arg0, s16 arg1) {
    s32 i;

    for (i = 0; i < MBMasuLinkNumGet(arg1); i++) {
        if (MBMasuLinkMasuIdGet(arg1, i) == arg0) {
            return i;
        }
    }
    return -1;
}

void MBMasuLinkIdxGet(s16 arg0, s8 *chainOut, s8 *linkOut) {
    s32 chain;
    s32 link;

    for (chain = 0; chain < mbMasuLinkNum; chain++) {
        for (link = 0; link < MBMasuLinkNumGet(chain); link++) {
            if (MBMasuLinkMasuIdGet(chain, link) == arg0) {
                *chainOut = chain;
                *linkOut = link;
                return;
            }
        }
    }
}

s32 MBMasuOtherLinkGet(s16 arg0, s8 *arg1, s8 *arg2) {
    s16 link;
    s32 i;

    for (i = 0; i < mbMasuLinkNum; i++) {
        if (*arg1 == i) {
            continue;
        }

        link = MBMasuLinkSearch(arg0, i);
        if (link != -1) {
            *arg1 = i;
            *arg2 = link;
            return 0;
        }
    }
    return -1;
}

void MBMoveStartMasuSet(void) {
    LinkData *chain;
    s16 *space;
    s16 i;
    s16 j;
    s16 k;

    chain = mbMasuLinkTbl;

    for (i = 0; i < mbMasuLinkNum; i++) {
        space = chain->spaces;

        for (j = 0; j < chain->chainIndicies; j++) {
            if (MBMasuGet(*space)->space_type == SPACE_NONE) {
                for (k = 0; k < 4; k++) {
                    MBMoveMasuSet(k, i, j);
                }
                return;
            }
            space++;
        }
        chain++;
    }

    for (k = 0; k < 4; k++) {
        MBMoveMasuSet(k, 0, 0);
    }
}

s16 MBMasuLinkRandIdxGet(u16 arg0, u16 arg1) {
    s32 linkNum;
    s32 i;
    u8 count;

    linkNum = MBMasuLinkNumGet(arg1);
    count = (rand8() % 30) + 1;
    
    for (i = 0;;) {
        if (mbMasuTypeBitTbl[MBMasuGet(MBMasuLinkMasuIdGet(arg1, i))->space_type & 0xF] & arg0) {
            if (--count == 0) {
                break;
            }
        }
        
        i++;
        if (i>= linkNum) {
            i = 0;
        }
    }
    return i;
}

static s16 MBMasuBlockGet(u16 arg0, u8 arg1) {
    u8 var_s1;
    SpaceData *space;
    s32 i, j;
    var_s1 = 0;

    for (i = 0; i < gTotalSpaces; i++) {
        space = MBMasuGet(i);
        if (mbMasuTypeBitTbl[space->space_type & 0xF] & arg0) {
            var_s1++;
        }
    }

    var_s1 -= mbMasuBlockNum;
    if (arg1 < 5) {
        var_s1 -= mbMasuBlockExtNum;
    }

    var_s1 = MBRand(var_s1);

    for (i = 0;; i = (++i < gTotalSpaces) ? i : 0) {
        space = MBMasuGet(i);
        for (j = 0; j < mbMasuBlockNum; j++) {
            if (mbMasuBlockTbl[j] == i) {
                break;
            }
        }

        if (j == mbMasuBlockNum) {
            if (arg1 < 5) {
                for (j = 0; j < mbMasuBlockExtNum; j++) {
                    if (mbMasuBlockExtTbl[j] == i) {
                        break;
                    }
                }
                if (j == mbMasuBlockExtNum) {
                    if (mbMasuTypeBitTbl[space->space_type & 0xF] & arg0) {
                        if (var_s1 == 0) {
                            break;
                        }
                        var_s1--;
                    }
                }
            } else {
                if (mbMasuTypeBitTbl[space->space_type & 0xF] & arg0) {
                    if (var_s1 == 0) {
                        break;
                    }
                    var_s1--;
                }
            }
        }
    }

    return i;
}

void MBMasuTypeSet(s16 spaceIdx, s32 newSpaceType) {
    MBMasuGet(spaceIdx)->space_type = newSpaceType;
}

// unused, sets all space types in a link to a new type
void MBMasuLinkTypeSet(u16 linkNo, u16 curSpaceType, u8 newSpaceType) {
    s32 linkSpaceCount;
    SpaceData *space;
    s32 i;

    linkSpaceCount = MBMasuLinkNumGet(linkNo);

    for (i = 0; i < linkSpaceCount; i++) {
        space = MBMasuGet(MBMasuLinkMasuIdGet(linkNo, i));
        if (space->space_type == curSpaceType) {
            space->space_type = newSpaceType;
        }
    }
}

static void MBMasuBounceProc(void) {
    SpaceData* temp_v0;
    f32 temp_f22;
    f32 var_f20;
    Process* proc =  HuPrcCurrentGet();

    temp_v0 = MBMasuGet((s16)(s32)proc->user_data);
    temp_f22 = temp_v0->rot.x;
    var_f20 = temp_f22 + 0.03f;
    if (mbMasuData != 0) {
        while (1) {
            HuPrcVSleep();
            
            var_f20 -= 0.005f;
            if (var_f20 <= temp_f22) {
                var_f20 = temp_f22;
            }
            
            temp_v0->rot.x = var_f20;
            temp_v0->rot.z = var_f20;
            if ((var_f20 <= temp_f22) || (mbMasuData == 0)) {
                break;
            }            
        }

    }
    omDelPrcObj(NULL);
}

void MBMasuBounceCreate(s16 arg0) {
    omAddPrcObj(MBMasuBounceProc, 0xEF00, 0, 0)->user_data = (void *)(s32)arg0;
}

static void MBMasuEventSet(s16 arg0, void *arg1) {
    switch (arg0) {
        case -2:
            mbMasuEventBoardStartTbl = arg1;
            break;
        case -3:
            mbMasuEventRoundEndTbl = arg1;
            break;
        case -4:
            mbMasuEventTurnStartTbl = arg1;
            break;
        case -5:
            mbMasuEventTurnTelopTbl = arg1;
            break;
        default:
            MBMasuGet(arg0)->event_list = arg1;
            break;
    }
}

void MBMasuEventTblAdd(event_table_entry *arg0) {
    event_table_entry *entry;

    for (entry = arg0; entry->space_index != -1; entry++) {
        MBMasuEventSet(entry->space_index, entry->event_list);
    }
}

s32 MBMasuEventCall(s16 arg0, s16 arg1) {
    event_list_entry *entry;
    Process *proc;
    s16 prevSpace;
    s32 ret;

    if ((GwSystem.current_player_index == 4) && (arg1 != 1)) {
        return 0;
    }

    switch (arg0) {
        case -2: entry = mbMasuEventBoardStartTbl; break;
        case -3: entry = mbMasuEventRoundEndTbl; break;
        case -4: entry = mbMasuEventTurnStartTbl; break;
        case -5: entry = mbMasuEventTurnTelopTbl; break;
        default: entry = MBMasuGet(arg0)->event_list;     break;
    }

    ret = 0;
    prevSpace = MBMasuCurGet();
    MBMasuCurSet(arg0);

    if (entry != NULL) {
        while (entry->activation_type != 0) {
            if (entry->activation_type == arg1) {
                mbMasuEventResult = 0;
                switch (entry->execution_type) {
                    case 1:
                        entry->event_fn();
                        break;
                    case 2:
                        proc = HuPrcCurrentGet();
                        HuPrcChildLink(proc, omAddPrcObj(entry->event_fn, 0x4800, 0, 0));
                        HuPrcChildWatch();
                        break;
                }
                ret |= mbMasuEventResult;
            }
            entry++;
        }
    }

    MBMasuCurSet(prevSpace);
    return ret;
}

void MBMasuEventResultSet(s32 arg0) {
    mbMasuEventResult = arg0;
}

void MBMasuCurSet(s16 arg0) {
    GwSystem.current_space_index = arg0;
}

s16 MBMasuCurGet(void) {
    return GwSystem.current_space_index;
}

s16 MBMasuKakusiBlockGet(u8 arg0) {
    return MBMasuBlockGet((1 << SPACE_BLUE), arg0);
}

void MBMasuBlockTblExtSet(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        mbMasuBlockExtTbl[i] = *arg0++;
    }
    
    mbMasuBlockExtNum = i;
}

void MBMasuBlockTblSet(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        mbMasuBlockTbl[i] = *arg0++;
    }
    
    mbMasuBlockNum = i;
}

void MBMasuTypeListCreate(void) {
    s32 var_s0;
    s32 i, j;

    if (mbMasuTypeListTbl != NULL) {
        HuMemMemoryFreeTemp(mbMasuTypeListTbl);
    }

    mbMasuTypeListTbl = HuMemMemoryAllocTemp(SPACE_TYPES_TOTAL * SPACES_MAX);

    for (i = 0; i < SPACE_TYPES_TOTAL; i++) {
        var_s0 = 0;

        for (j = 0; j < gTotalSpaces; j++) {
            if (MBMasuGet(j)->space_type == i) {
                mbMasuTypeListTbl[i][var_s0] = j;
                var_s0++;
            }
        }

        mbMasuTypeListTbl[i][var_s0] = 0xFF;
        mbMasuTypeNumTbl[i] = var_s0;
    }
}

u8 MBMasuTypeListGet(s32 arg0, s32 arg1) {
    return mbMasuTypeListTbl[arg0][arg1];
}

void MBMasuDispOn(void) {
    mbMasuDispF = 1;
}

void MBMasuDispOff(void) {
    mbMasuDispF = 0;
}
