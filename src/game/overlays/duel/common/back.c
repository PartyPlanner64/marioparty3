#include "common_duel.h"
#include "game/rom.h"
#include "ovl_81.h"
#include "game/mallocblock.h"

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

extern f32 mbdBackScale;
extern f32 mbdCameraScrPos[2];
extern f32 mbdCameraSpeed; // Camera speed
extern u32 mbdBackArcAddr;
extern s32 mbdBackArcNum;
extern u32 mbdBackFileAddr;
extern u8* mbdBackHvqWork;
extern u16 mbdBackFlag;
extern s16 mbdBackOfsX;
extern s16 mbdBackOfsY;
extern s16 mbdBackHalfW;
extern s16 mbdBackHalfH;
extern HvqFileHeader* mbdBackHvqFileHdr;
extern Vec mbdBackOrigin;
extern s32 mbdPartnerUnusedWork;
extern OSMesgQueue mbdBackDmaMesgQ;
extern OSMesgQueue mbdBackDecodeMesgQ;
extern OSMesgQueue mbdBackExitMesgQ;
extern HvqHeader* mbdBackHvqCur;
extern OSMesgQueue mbdBackDoneMesgQ;
extern void* mbdBackDmaMesgBuf;
extern void* mbdBackDecodeMesgBuf;
extern void* mbdBackDoneMesgBuf;
extern void* mbdBackExitMesgBuf;
extern OSPri mbdBackThreadPri;
extern OSThread mbdBackDecodeThread;
extern OSThread mbdBackDmaThread;
extern OverlayBgEntry mbdBackTileTbl[50];
extern OverlayBgEntry *mbdBackTileMap[6][6];
extern Process* mbdCameraZoomProc;
extern Vec mbdCameraEye;
extern Vec mbdCameraAt;
extern Vec mbdCameraUp;
extern Vec mbdCameraViewportSize;
extern Vec2f mbdCameraScrTarget;
extern f32 mbdCameraSpeedDiv;
extern Process* mbdCameraUpdateProc;
extern UnkBoard7 mbdBackSprTbl[64];
extern s32 mbdBackSprNum;
extern Object* mbdBackMdlTbl[16];

s32 *mbdBackArcOfsTbl = NULL;
u32 *mbdBackFileOfsTbl = NULL;
UnkModelStruct *mbdBackHdr = NULL;
u8 mbdBackTPLvl = 0xFF;
f32 mbdBackZoom = 1.0f;
f32 mbdCameraFar = 0.0f;
f32 mbdCameraNear = 0.0f;
u32 mbdBackTexDirectF = 0;

Gfx mbdBackGfxInit[] = {
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

Process *mbdBackSprProc = NULL;
s32 mbdBackSprDispF = 1;

static s32 MBDBackFileSizeGet(u16);
void MBDBackDraw(Gfx** arg0, s32 arg1, u8 arg2);
static void MBDCameraInit(void);
static void MBDCameraClose(void);
void MBDCameraUpdateMain(void);
static void MBDBackMdlInit(void);
static void MBDBackMdlClose(void);

void MBDBackArcInit(Addr arg0) {
    HuArchive* temp_v0;
    s32* temp_v0_2;
    u32 temp_s0;

    mbdBackArcAddr = (u32)arg0;
    temp_v0 = HuMemMemoryAllocTemp(sizeof(HuArchive));
    dmaRead((u32)arg0, (u8*)temp_v0, sizeof(HuArchive));
    mbdBackArcNum = temp_v0->count;
    HuMemMemoryFreeTemp(temp_v0);
    temp_s0 = mbdBackArcNum * 4;
    temp_v0_2 = HuMemMemoryAllocTemp(temp_s0);
    mbdBackArcOfsTbl = temp_v0_2;
    dmaRead((u32)(arg0 + 4), (u8*)temp_v0_2, temp_s0);
    mbdBackHvqWork = HuMemMemoryAllocTemp(0x300);
    mbdBackHdr = NULL;
}

void MBDBackReset(void) {
    mbdBackHdr = NULL;
}

void MBDBackClose(void) {
    if (mbdBackArcOfsTbl != NULL) {
        HuMemMemoryFreeTemp(mbdBackArcOfsTbl);
        mbdBackArcOfsTbl = NULL;
        HuMemMemoryFreeTemp(mbdBackHvqWork);
    }
}

void MBDBackCreate(s32 arg0, s32 arg1) {
    UnkModelStruct* temp_v0_3;
    u32 temp_s0;
    HuArchive* temp_v0;
    u32* temp_v0_2;

    mbdPartnerUnusedWork = arg0;
    mbdBackFileAddr = mbdBackArcAddr + mbdBackArcOfsTbl[arg0];
    temp_v0 = HuMemMemoryAllocTemp(sizeof(HuArchive));
    dmaRead(mbdBackFileAddr, (u8*)temp_v0, sizeof(HuArchive));
    arg0 = temp_v0->count;
    HuMemMemoryFreeTemp(temp_v0);
    arg0++;
    temp_s0 = arg0 * 4;
    temp_v0_2 = HuMemMemoryAllocTemp(temp_s0);
    mbdBackFileOfsTbl = temp_v0_2;
    dmaRead(mbdBackFileAddr + 4, (u8*)temp_v0_2, temp_s0);
    temp_v0_3 = HuMemMemoryAllocTemp(sizeof(UnkModelStruct));
    mbdBackHdr = temp_v0_3;
    dmaRead(mbdBackFileAddr + mbdBackFileOfsTbl[0], (u8*)&temp_v0_3->unk0, sizeof(UnkModelStruct));
    mbdBackOrigin.x = mbdBackHdr->unk18;
    mbdBackOrigin.y = mbdBackHdr->unk1C;
    mbdBackOrigin.z = mbdBackHdr->unk20;
    mbdBackHdr->unk18 *= 5.0f;
    mbdBackHdr->unk1C *= 5.0f;
    mbdBackHdr->unk20 *= 5.0f;
    mbdBackHdr->unk24 *= 5.0f;
    mbdBackHdr->unk28 *= 5.0f;
    mbdBackHdr->unk2C *= 5.0f;
    mbdBackHvqFileHdr = HuMemMemoryAllocTemp(MBDBackFileSizeGet(0));
    dmaRead(mbdBackFileAddr + mbdBackFileOfsTbl[1], (u8 *)mbdBackHvqFileHdr, MBDBackFileSizeGet(0));
    mbdBackOfsY = 0;
    mbdBackOfsX = 0;
    mbdBackHalfW = mbdBackHdr->unk0 * mbdBackHdr->unk8 / 2;
    mbdBackHalfH = mbdBackHdr->unk4 * mbdBackHdr->unkC / 2;
    mbdBackFlag = 1;
    Hu3DLayerHookSet(0, MBDBackDraw);
    MBDBackStreamStart();
    MBDBackThreadPriHighSet();
    if (arg1 != 0) {
        MBDCameraInit();
    }
    MBDCameraSpeedDivSet(1.0f);
    MBDBackTPLvlSet(0xFF);
    MBDCameraSpeedSet(-1.0f);
    mbdCameraFar = 0.0f;
    mbdCameraNear = 0.0f;
    MBDCameraZoomSet(1.0f);
}

void MBDBackLoad(s32 arg0) {
    MBDBackCreate(arg0, 1);
}

void MBDBackKill(void) {
    if (mbdBackFileOfsTbl != NULL) {
        HuMemMemoryFreeTemp(mbdBackFileOfsTbl);
        mbdBackFileOfsTbl = NULL;
        HuMemMemoryFreeTemp(mbdBackHdr);
        HuMemMemoryFreeTemp(mbdBackHvqFileHdr);
        Hu3DLayerHookSet(0, 0);
        MBDBackStreamStop();
        MBDCameraClose();
    }
}

static void MBDBackOffsetSet(s16 arg0, s16 arg1) {
    mbdBackOfsX = arg0;
    mbdBackOfsY = arg1;
}

static f32 MBDBackMinXGet(void) {
    return ((-mbdBackHalfW + 160.0f) / mbdBackScale) + 160.0f;
}

static f32 MBDBackMaxXGet(void) {
    return ((mbdBackHalfW - 160.0f) / mbdBackScale) + 160.0f;
}

static f32 MBDBackMinYGet(void) {
    return ((-mbdBackHalfH + 120.0f) / mbdBackScale) + 120.0f;
}

static f32 MBDBackMaxYGet(void) {
    return ((mbdBackHalfH - 120.0f) / mbdBackScale) + 120.0f;
}

static u16 MBDBackPosClamp(Vec2f* arg0, f32 arg1) {
    u16 var_v1;

    var_v1 = 0;
    if (arg0->x <= (((-mbdBackHalfW + 160.0f) / arg1) + 160.0f)) {
        arg0->x = ((-mbdBackHalfW + 160.0f) / arg1) + 160.0f;
        var_v1 = 1;
    }
    if (((mbdBackHalfW - 160.0f) / arg1) + 160.0f + ((SCREEN_WIDTH / arg1) - (SCREEN_WIDTH / (arg1 * mbdBackZoom))) <= arg0->x) {
        arg0->x = ((mbdBackHalfW - 160.0f) / arg1) + 160.0f + ((SCREEN_WIDTH / arg1) - (SCREEN_WIDTH / (arg1 * mbdBackZoom)));
        var_v1 |= 2;
    }
    if (arg0->y <= ((-mbdBackHalfH + 120.0f) / arg1) + 120.0f) {
        arg0->y = ((-mbdBackHalfH + 120.0f) / arg1) + 120.0f;
        var_v1 |= 4;
    }
    if (((mbdBackHalfH - 120.0f) / arg1) + 120.0f + ((SCREEN_HEIGHT / arg1) - (SCREEN_HEIGHT / (arg1 * mbdBackZoom))) <= arg0->y) {
        arg0->y = ((mbdBackHalfH - 120.0f) / arg1) + 120.0f + ((SCREEN_HEIGHT / arg1) - (SCREEN_HEIGHT / (arg1 * mbdBackZoom)));
        var_v1 |= 8;
    }
    return var_v1;
}

void MBDBackDispSet(u16 arg0) {
    if (arg0) {
        mbdBackFlag = mbdBackFlag | 1;
    } else {
        mbdBackFlag = mbdBackFlag & ~1;
    }
}

static void MBDBackDmaProc(void) {
    OverlayBgEntry* sp10;

    while (1) {
        osRecvMesg(&mbdBackDmaMesgQ, (OSMesg)&sp10, OS_MESG_BLOCK);
        if (sp10 == NULL) {
            break;
        }
        dmaRead(sp10->romAddr, (u8 *)sp10->compressedData, sp10->compressedSize);
        osSendMesg(&mbdBackDecodeMesgQ, (OSMesg)sp10, OS_MESG_NOBLOCK);
    }

    osSendMesg(&mbdBackExitMesgQ, (OSMesg)1, OS_MESG_NOBLOCK);
    osDestroyThread(NULL);
}

#define SlideReadUint(buffer, src)    \
    do {                              \
        (buffer) = ((*src++) << 24);  \
        (buffer) += ((*src++) << 16); \
        (buffer) += ((*src++) << 8);  \
        (buffer) += (*src++);         \
    } while (0)

static void MBDBackSlideDecode(u8 *input, u8 *output, s32 compressedSize) {
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
static void MBDBackDecodeProc(void) {
    OverlayBgEntry *sp10;
    HvqHeader *temp_a0;

    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(mbdBackHvqFileHdr); //"HVQ-MPS 1.1"
    while (1) {
        osRecvMesg(&mbdBackDecodeMesgQ, (OSMesg)&sp10, OS_MESG_BLOCK);
        if (sp10 != NULL) {
            temp_a0 = sp10->compressedData;
            mbdBackHvqCur = sp10->compressedData;
            if (temp_a0->magic == ASCII_HVQS) {
                hvqMpsDecode1(&temp_a0->data.image, sp10->pixels, 0x40, mbdBackHvqWork);
            } else {
                // 0x1800 size for decoded tile
                MBDBackSlideDecode(mbdBackHvqCur->data.slide, (u8 *)sp10->pixels, 0x1800);
            }
            osSendMesg(&mbdBackDoneMesgQ, (OSMesg)sp10, OS_MESG_NOBLOCK);
        } else {
            break;
        }
    }

    osSendMesg(&mbdBackExitMesgQ, (OSMesg)2, OS_MESG_NOBLOCK);
    osDestroyThread(NULL);
}

static void MBDBackThreadCreate(void) {
    osCreateMesgQueue(&mbdBackDmaMesgQ, &mbdBackDmaMesgBuf, 50);
    osCreateMesgQueue(&mbdBackDecodeMesgQ, &mbdBackDecodeMesgBuf, 50);
    osCreateMesgQueue(&mbdBackDoneMesgQ, &mbdBackDoneMesgBuf, 50);
    osCreateMesgQueue(&mbdBackExitMesgQ, &mbdBackExitMesgBuf, 2);
    mbdBackThreadPri = 1;
    osCreateThread(&mbdBackDecodeThread, 0x64, (void (*)(void*))MBDBackDecodeProc, NULL, &mbdBackDecodeMesgQ, mbdBackThreadPri);
    osStartThread(&mbdBackDecodeThread);
    osCreateThread(&mbdBackDmaThread, 0x65, (void (*)(void*))MBDBackDmaProc, NULL, &mbdBackDecodeThread, 4);
    osStartThread(&mbdBackDmaThread);
}

void MBDBackThreadPriHighSet(void) {
    mbdBackThreadPri = 3;
}

void MBDBackThreadPriLowSet(void) {
    mbdBackThreadPri = 1;
}

static void MBDBackThreadPriUpdate(void) {
    if (osGetThreadPri(&mbdBackDecodeThread) != mbdBackThreadPri) {
        osSetThreadPri(&mbdBackDecodeThread, mbdBackThreadPri);
    }
}

static void MBDBackDoneFree(void) {
    OverlayBgEntry* sp10;

    while (1) {
        if (osRecvMesg(&mbdBackDoneMesgQ, (OSMesg)&sp10, 0) != OS_MESG_NOBLOCK) {
            break;
        }
        if (sp10 != NULL) {
            HuMemMemoryFreePerm(sp10->compressedData);
            sp10->compressedData = NULL;
        }
    }
}

static void MBDBackThreadKill(void) {
    s32 i;

    osJamMesg(&mbdBackDmaMesgQ, NULL, OS_MESG_NOBLOCK);
    osJamMesg(&mbdBackDecodeMesgQ, NULL, OS_MESG_NOBLOCK);

    MBDBackThreadPriHighSet();
    MBDBackThreadPriUpdate();

    osRecvMesg(&mbdBackExitMesgQ, NULL, OS_MESG_BLOCK);
    osRecvMesg(&mbdBackExitMesgQ, NULL, OS_MESG_BLOCK);

    for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++) {
        OverlayBgEntry* temp = &mbdBackTileTbl[i];
        if (temp->compressedData != NULL) {
            HuMemMemoryFreePerm(temp->compressedData);
            temp->compressedData = NULL;
        }
    }
}

static void MBDBackTileInit(void) {
    OverlayBgEntry* var_s0 = mbdBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++, var_s0++) {
        var_s0->unk0 = 0;
        var_s0->unk2 = -1;
        var_s0->pixels = HuMemAlloc(0x1800);
        var_s0->compressedData = NULL;
    }

    bzero(mbdBackTileMap, sizeof(mbdBackTileMap));
}

static void MBDBackTileUseClear(void) {
    OverlayBgEntry* var_v1 = mbdBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++, var_v1++) {
        if ((var_v1->compressedData == NULL) && (var_v1->unk0 == 0)) {
            var_v1->unk2 = -1;
        }
        var_v1->unk0 = 0;
    }
}

static void MBDBackTileClose(void) {
    OverlayBgEntry* var_s0 = mbdBackTileTbl;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++, var_s0++) {
        var_s0->unk0 = 0;
        var_s0->unk2 = -1;

        if (var_s0->pixels != NULL) {
            HuMemFree(var_s0->pixels);
            var_s0->pixels = NULL;
        }
    }
}

void MBDBackStreamStart(void) {
    MBDBackTileInit();
    MBDBackThreadCreate();
    mbdBackFlag |= 4;
}

void MBDBackStreamStop(void) {
    MBDBackThreadKill();
    MBDBackTileClose();
    mbdBackFlag &= ~4;
}

void MBDBackStreamOff(void) {
    mbdBackFlag &= ~4;
}

f32 MBDBackMdlScaleGet(void) {
    if (mbdBackHdr == NULL) {
        return 1.0f;
    } else {
        return mbdBackHdr->unk14;
    }
}

static u16 MBDBackTileNoGet(s32 arg0, s32 arg1) {
    return ((((mbdBackHdr->unkC - arg1) - 1) * mbdBackHdr->unk8) + arg0 + 1);
}

static s32 MBDBackFileSizeGet(u16 arg0) {
    arg0++;
    return mbdBackFileOfsTbl[(arg0 + 1)] - mbdBackFileOfsTbl[(arg0 + 0)];
}

static s32 MBDBackFileAddrGet(u16 arg0) {
    arg0++;
    return mbdBackFileAddr + mbdBackFileOfsTbl[(arg0)];
}

OverlayBgEntry *MBDBackTileLoad(u16 arg0) {
    OverlayBgEntry *entry;
    OverlayBgEntry *slot;
    s32 i;
    s32 size;

    slot = NULL;
    entry = mbdBackTileTbl;

    for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++, entry++) {
        if (entry->unk2 == -1) {
            slot = entry;
        } else if (entry->unk2 == arg0) {
            entry->unk0 = 1;
            return entry;
        }
    }

    if (slot != NULL) {
        slot->unk0 = 1;
        slot->unk2 = arg0;
        slot->romAddr = MBDBackFileAddrGet(arg0);
        size = MBDBackFileSizeGet(arg0);
        slot->compressedSize = size;
        slot->compressedData = HuMemMemoryAllocPerm(size);
        osSendMesg(&mbdBackDmaMesgQ, slot, OS_MESG_NOBLOCK);
    }
    return slot;
}

static void MBDBackTileMapUpdate(void) {
    s32 tileX;
    s32 tileY;
    s32 x;
    s32 y;

    tileY = (s32)(((f32)((mbdBackHalfH + mbdBackOfsY) - 0x78) -
                   ((SCREEN_HEIGHT - (SCREEN_HEIGHT / mbdBackZoom)) / 2.0f)) / 48.0f);

    for (y = 0; y < 6; y++, tileY++) {
        tileX = (s32)(((f32)((mbdBackHalfW + mbdBackOfsX) - 0xA0) -
                       ((SCREEN_WIDTH - (SCREEN_WIDTH / mbdBackZoom)) / 2.0f)) / 64.0f);

        for (x = 0; x < 6; x++, tileX++) {
            if ((tileX < 0) || (tileY < 0) ||
                (tileX >= mbdBackHdr->unk8) ||
                (tileY >= mbdBackHdr->unkC)) {
                mbdBackTileMap[x][y] = NULL;
            } else {
                mbdBackTileMap[x][y] =
                    MBDBackTileLoad(MBDBackTileNoGet(tileX, tileY));
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

void MBDBackTileDraw(Gfx** arg0, u16* arg1, s16 arg2, s16 arg3) {
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;

    temp_f20 = ((f32) arg2 + (mbdCameraScrPos[0] / 4.0f)) - (f32) (s32) (mbdCameraScrPos[0] / 4.0f);
    temp_f22 = ((f32) arg3 + (mbdCameraScrPos[1] / 4.0f)) - (f32) (s32) (mbdCameraScrPos[1] / 4.0f);

    if (mbdBackTexDirectF == 0) {
        HuLoadTextureBlock(arg0, arg1, 0, 2, 0x40, 0x20, 0, 0, 0x40, 0x20, 0, 1, 1, 6, 5, 0, 0);
    } else {
        gDPLoadTextureBlock((*arg0)++, arg1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_MIRROR,
                            G_TX_MIRROR, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    }

    if (!(mbdBackFlag & 0x10)) {
        if (mbdBackTexDirectF == 0) {
            gSPScisTextureRectangle_MP((*arg0)++,
                /*xl*/(temp_f20 * mbdBackZoom * 4.0f),
                /*yl*/((temp_f22 * mbdBackZoom * 4.0f)),
                /*xh*/(temp_f20 + 64.0f) * mbdBackZoom * 4.0f,
                /*yh*/(temp_f22 + 32.0f) * mbdBackZoom * 4.0f,
                /*tile*/0,
                /*s*/0,
                /*t*/0,
                /*dsdx*/(1024.0f / mbdBackZoom),
                /*dtdy*/(1024.0f / mbdBackZoom)
            );
        } else {
            gSPScisTextureRectangle_MP((*arg0)++,
                /*xl*/(temp_f20 * mbdBackZoom * 4.0f),
                /*yl*/((temp_f22 * mbdBackZoom * 4.0f)),
                /*xh*/(temp_f20 + 64.0f) * mbdBackZoom * 4.0f,
                /*yh*/(temp_f22 + 32.0f) * mbdBackZoom * 4.0f,
                /*tile*/0,
                /*s*/0,
                /*t*/0,
                /*dsdx*/(1024.0f / mbdBackZoom),
                /*dtdy*/(1024.0f / mbdBackZoom)
            );
        }
    } else {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/((256.0f - temp_f20) * mbdBackZoom * 4.0f),
            /*yl*/((temp_f22 * mbdBackZoom * 4.0f)),
            /*xh*/((SCREEN_WIDTH - temp_f20) * mbdBackZoom * 4.0f),
            /*yh*/((temp_f22 + 32.0f) * mbdBackZoom * 4.0f),
            /*tile*/0,
            /*s*/0x7e0,
            /*t*/0,
            /*dsdx*/-(s16)(1024.0f / mbdBackZoom),
            /*dtdy*/(1024.0f / mbdBackZoom)
        );
    }

    if (mbdBackTexDirectF == 0) {
        HuLoadTextureBlock(arg0, arg1 + (64 * 32), 0, 2, 0x40, 0x10, 0, 0, 0x40, 0x10, 0, 1, 1, 6, 4, 0, 0);
    } else {
        gDPLoadTextureBlock((*arg0)++, arg1 + (64 * 32), G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0,
                            G_TX_MIRROR, G_TX_MIRROR, 6, 4, G_TX_NOLOD, G_TX_NOLOD);
    }

    if (!(mbdBackFlag & 0x10)) {
        if (mbdBackTexDirectF == 0) {
            gSPScisTextureRectangle_MP((*arg0)++,
                /*xl*/(temp_f20 * mbdBackZoom * 4.0f),
                /*yl*/((temp_f22 + 32.0f) * mbdBackZoom * 4.0f),
                /*xh*/((temp_f20 + 64.0f) * mbdBackZoom * 4.0f),
                /*yh*/((temp_f22 + 48.0f) * mbdBackZoom * 4.0f),
                /*tile*/0,
                /*s*/0,
                /*t*/0,
                /*dsdx*/(1024.0f / mbdBackZoom),
                /*dtdy*/(1024.0f / mbdBackZoom)
            );
        } else {
            gSPScisTextureRectangle_MP((*arg0)++,
                /*xl*/(temp_f20 * mbdBackZoom * 4.0f),
                /*yl*/((temp_f22 + 32.0f) * mbdBackZoom * 4.0f),
                /*xh*/((temp_f20 + 64.0f) * mbdBackZoom * 4.0f),
                /*yh*/((temp_f22 + 48.0f) * mbdBackZoom * 4.0f),
                /*tile*/0,
                /*s*/0,
                /*t*/0,
                /*dsdx*/(1024.0f / mbdBackZoom),
                /*dtdy*/(1024.0f / mbdBackZoom)
            );
        }
    } else {
        gSPScisTextureRectangle_MP((*arg0)++,
            /*xl*/((256.0f - temp_f20) * mbdBackZoom * 4.0f),
            /*yl*/((temp_f22 + 32.0f) * mbdBackZoom * 4.0f),
            /*xh*/((SCREEN_WIDTH - temp_f20) * mbdBackZoom * 4.0f),
            /*yh*/((temp_f22 + 48.0f) * mbdBackZoom * 4.0f),
            /*tile*/0,
            /*s*/0x7e0,
            /*t*/0,
            /*dsdx*/-(s16)(1024.0f / mbdBackZoom),
            /*dtdy*/(1024.0f / mbdBackZoom)
        );
    }
}

void MBDBackDraw(Gfx** arg0, s32 arg1, u8 arg2) {
    u16 sp1E;
    u16 sp26;
    s16 spY;
    s16 spX;
    s16 row;
    s16 col;
    s16 temp_s0;
    OverlayBgEntry* bgEntry;

    if (arg2 || !(mbdBackFlag & 4)) {
        return;
    }

    MBDBackDoneFree();
    if (!(mbdBackFlag & 1)) {
        return;
    }

    MBDBackTileUseClear();
    temp_s0 = HuProfCpuBegin(0xC8, 0, 0);
    MBDBackTileMapUpdate();
    HuProfCpuEnd(temp_s0);

    sp26 = ((mbdBackHalfH + mbdBackOfsY) - 120) % 48;
    sp1E = ((mbdBackHalfW + mbdBackOfsX) - 160) % 64;

    spY = (s32)(((f32)(((mbdBackHalfH + mbdBackOfsY)) - 120) - ((SCREEN_HEIGHT - (SCREEN_HEIGHT / mbdBackZoom)) / 2.0f)) / 48.0f) - ((((mbdBackHalfH + mbdBackOfsY)) - 120) / 48);
    spX = (s32)(((f32)(((mbdBackHalfW + mbdBackOfsX)) - 160) - ((SCREEN_WIDTH - (SCREEN_WIDTH / mbdBackZoom)) / 2.0f)) / 64.0f) - ((((mbdBackHalfW + mbdBackOfsX)) - 160) / 64);

    gSPDisplayList((*arg0)++, mbdBackGfxInit);
    gDPSetEnvColor((*arg0)++, 0xFF, 0xFF, 0xFF, mbdBackTPLvl);

    if (mbdBackTPLvl < 0xFF) {
        if (mbdBackFlag & 8) {
            gDPSetCombineLERP((*arg0)++, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT);
        } else {
            gDPSetCombineLERP((*arg0)++, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT);
        }
        gDPSetRenderMode((*arg0)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    } else {
        if (mbdBackFlag & 8) {
            gDPSetCombineLERP((*arg0)++, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0);
        }

        gDPSetRenderMode((*arg0)++, G_RM_AA_SUB_SURF, G_RM_AA_SUB_SURF2);
    }

    for (row = 0; row < 6; row++) {
        for (col = 0; col < 6; col++) {
            bgEntry = mbdBackTileMap[col][row];
            if (bgEntry != NULL) {
                MBDBackTileDraw(
                    arg0,
                    bgEntry->pixels,
                    ((col + spX) * 64) - sp1E,
                    ((row + spY) * 48) - sp26
                );
            }
        }
    }

    MBDBackThreadPriUpdate();
}

f32 MBDCameraZoomGet(void) {
    return mbdBackZoom;
}

void MBDCameraZoomSet(f32 zoom) {
    mbdBackZoom = zoom;
}

static void MBDCameraZoomMotProc(void) {
    f32 target;
    f32 diff;
    f32 step;
    f32 next;
    f32 temp;

    target = *(f32 *)HuPrcCurrentGet()->user_data;

    while (1) {
        diff = mbdBackZoom - target;
        step = (0.0f < diff) ? diff : 0.0f - (mbdBackZoom - target);
        
        if (step <= 0.005f) {
            break;
        }
        
        step /= 4.0f;
        if (step < 0.005f) {
            step = 0.005f;
        }
        if (target < mbdBackZoom) {
            next = mbdBackZoom - step;
        } else {
            next = step + mbdBackZoom;
        }
        mbdBackZoom = next;
        HuPrcVSleep();
    }

    mbdBackZoom = target;
    mbdCameraZoomProc = NULL;
    omDelPrcObj(NULL);
}

Process* MBDCameraZoomMotStart(f32 arg0) {
    Process* temp_v0;
    f32* temp_v0_2;

    if (mbdCameraZoomProc != NULL) {
        omDelPrcObj(mbdCameraZoomProc);
    }
    mbdCameraZoomProc = omAddPrcObj(MBDCameraZoomMotProc, 1U, 0, 0x40);

    temp_v0_2 = HuMemMemoryAlloc(mbdCameraZoomProc->heap, 0x10);
    mbdCameraZoomProc->user_data = temp_v0_2;
    *temp_v0_2 = arg0;
    return mbdCameraZoomProc;
}

static void MBDCameraZoomMotFastProc(void) {
    f32 temp_f22;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f20;
    s32 var_s0;
    s32 i;

    temp_f22 = *(f32*)HuPrcCurrentGet()->user_data;
    temp_f2 = mbdBackZoom - temp_f22;
    if (temp_f2 > 0.0f) {
        var_f20 = temp_f2 / 5.0f;
    } else {
        var_f20 = (0.0f - (mbdBackZoom - temp_f22)) / 5.0f;
    }
    for (i = 0; i < 5; i++, HuPrcVSleep()) {
        if (temp_f22 < mbdBackZoom) {
            mbdBackZoom = mbdBackZoom - var_f20;
        } else {
            mbdBackZoom = var_f20 + mbdBackZoom;
        }
    }

    mbdBackZoom = temp_f22;
    mbdCameraZoomProc = NULL;
    omDelPrcObj(NULL);
}

Process* MBDCameraZoomMotFastStart(f32 arg0) {
    Process* proc;
    f32* temp_v0_2;

    if (mbdCameraZoomProc != NULL) {
        omDelPrcObj(mbdCameraZoomProc);
    }

    proc = omAddPrcObj(MBDCameraZoomMotFastProc, 1, 0, 0x40);
    mbdCameraZoomProc = proc;
    temp_v0_2 = HuMemMemoryAlloc(proc->heap, 0x10);
    mbdCameraZoomProc->user_data = temp_v0_2;
    *temp_v0_2 = arg0;
    return mbdCameraZoomProc;
}

static void MBDCameraInit(void) {
    Process* temp_v0;
    f32 temp_f2;
    f32 temp_f4;

    temp_f2 = (f32) (mbdBackHdr->unk4 * mbdBackHdr->unkC) / SCREEN_HEIGHT;
    mbdBackScale = temp_f2;
    temp_f4 = (f32) (mbdBackHdr->unk0 * mbdBackHdr->unk8) / SCREEN_WIDTH;
    if (temp_f2 < temp_f4) {
        mbdBackScale = temp_f4;
    }
    mbdCameraEye.x = mbdBackHdr->unk18;
    mbdCameraEye.y = mbdBackHdr->unk1C;
    mbdCameraEye.z = mbdBackHdr->unk20;
    mbdCameraAt.x = mbdBackHdr->unk24;
    mbdCameraAt.y = mbdBackHdr->unk28;
    mbdCameraAt.z = mbdBackHdr->unk2C;
    mbdCameraUp.x = mbdBackHdr->unk30;
    mbdCameraUp.y = mbdBackHdr->unk34;
    mbdCameraUp.z = mbdBackHdr->unk38;
    mbdCameraViewportSize.x = (mbdBackScale * 640.0f);
    mbdCameraViewportSize.y = (mbdBackScale * 480.0f);
    mbdCameraViewportSize.z = 511.0f;
    mbdCameraScrPos[0] = 640.0f;
    mbdCameraScrPos[1] = 480.0f;
    mbdCameraScrTarget.x = 159.5f;
    mbdCameraScrTarget.y = 119.5f;
    mbdCameraSpeedDiv = 1.0f;
    temp_v0 = omAddPrcObj(MBDCameraUpdateMain, 0x1001, 0, 0);
    mbdCameraUpdateProc = temp_v0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    mbdCameraZoomProc = 0;
    Hu3DCameraPerspectiveSet(0, mbdBackHdr->unk10, 10.0f, 200.0f);
    Hu3DCameraPosSetV(0, &mbdCameraEye, &mbdCameraAt, &mbdCameraUp);
    Hu3DCamUpdateMtx(0);
}

void MBDCameraKill(void) {
    if (mbdCameraUpdateProc != NULL) {
        omDelPrcObj(mbdCameraUpdateProc);
        mbdCameraUpdateProc = NULL;
    }
    if (mbdCameraZoomProc != NULL) {
        omDelPrcObj(mbdCameraZoomProc);
        mbdCameraZoomProc = NULL;
    }
}

static void MBDCameraClose(void) {
    MBDCameraKill();
}

void MBDCameraNearFarSet(f32 arg0, f32 arg1) {
    mbdCameraNear = arg0;
    mbdCameraFar = arg1;
}

void MBDCameraUpdateMain(void) {
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
        temp_f4 = HuVecDistance(&mbdCameraEye, &mbdCameraAt);
        var_f2 = mbdCameraFar;
        if ((var_f2 == 0.0f) || (var_f0 = mbdCameraNear, (var_f0 == 0.0f))) {
            var_f2 = temp_f4 + 1000.0f;
            var_f0 = var_f2 - 2000.0f;
        }
        if (var_f0 < 10.0f) {
            var_f0 = 10.0f;
        }
        Hu3DCameraPerspectiveSet(0, mbdBackHdr->unk10, var_f0, var_f2);
        Hu3DCameraPosSetV(0, &mbdCameraEye, &mbdCameraAt, &mbdCameraUp);
        Hu3DCamUpdateMtx(0);

        sp38.x = ((((mbdCameraScrTarget.x - 160.0f) * mbdBackScale * -4.0f) + 640.0f) - mbdCameraScrPos[0]) / mbdCameraSpeedDiv;
        sp38.y = ((((mbdCameraScrTarget.y - 120.0f) * mbdBackScale * -4.0f) + 480.0f) - mbdCameraScrPos[1]) / mbdCameraSpeedDiv;
        sp38.z = 0.0f;

        temp_f2 = HuVecGetLength3F(&sp38) / 4.0f;

        if (temp_f2 <= 1.0f) {
            mbdBackFlag &= 0xFFFD;
            mbdCameraScrPos[0] = ((mbdCameraScrTarget.x - 160.0f) * mbdBackScale * -4.0f) + 640.0f;
            mbdCameraScrPos[1] = ((mbdCameraScrTarget.y - 120.0f) * mbdBackScale * -4.0f) + 480.0f;
        } else {
            mbdBackFlag |= 2;
            if ((mbdCameraSpeed >= 0.0f) && (mbdCameraSpeed < temp_f2)) {
                MBDVecNormalize(&sp38);
                HuVecMulScalar(&sp38, mbdCameraSpeed * 4.0f, &sp38);
            }
            mbdCameraScrPos[0] += sp38.x;
            mbdCameraScrPos[1] = mbdCameraScrPos[1] + sp38.y;
        }

        sp20[0] = mbdCameraScrPos[0] / 4.0f;
        sp20[1] = mbdCameraScrPos[1] / 4.0f;

        sp10.x = mbdCameraScrPos[0] * mbdBackZoom;
        sp10.y = mbdCameraScrPos[1] * mbdBackZoom;
        sp10.z = 511.5f;

        sp28.x = mbdBackScale * 640.0f * mbdBackZoom;
        sp28.y = mbdBackScale * 480.0f * mbdBackZoom;
        sp28.z = 511.0f;

        Hu3DCameraViewportSet(0, &sp28, &sp10);
        MBDBackOffsetSet(-sp20[0] + 0xA0, -sp20[1] + 0x78);
        HuPrcVSleep();
    }
}

void MBDCameraSpeedDivSet(f32 arg0) {
    mbdCameraSpeedDiv = arg0;
}

f32 MBDCameraSpeedDivGet(void) {
    return mbdCameraSpeedDiv;
}

u16 MBDCameraPos3DSet(Vec *arg0) {
    Vec sp10;
    f32 scale;
    f32 halfW;
    f32 halfH;
    Vec2f* temp;

    HuVecCopyXYZ(&sp10, arg0->x, arg0->y + 10.0f, arg0->z);
    Hu3D3Dto2D(0, &sp10, &mbdCameraScrTarget);

    temp = &mbdCameraScrTarget;

    halfW = SCREEN_WIDTH / (2.0f * mbdBackScale);
    temp->x += halfW - (halfW / mbdBackZoom);

    halfH = SCREEN_HEIGHT / (2.0f * mbdBackScale);
    mbdCameraScrTarget.y += halfH - (halfH / mbdBackZoom);

    return MBDBackPosClamp(&mbdCameraScrTarget, mbdBackScale);
}

u16 MBDCameraPos2DSet(Vec2f *arg0) {
    mbdCameraScrTarget.x = arg0->x / mbdBackScale + 160.0f;
    mbdCameraScrTarget.y = arg0->y / mbdBackScale + 120.0f;
    return MBDBackPosClamp(&mbdCameraScrTarget, mbdBackScale);
}

void MBDCameraPos3DGet(Vec2f* arg0) {
    arg0->x = (mbdCameraScrTarget.x - 160.0f) * mbdBackScale;
    arg0->y = (mbdCameraScrTarget.y - 120.0f) * mbdBackScale;
}

void MBDCameraPos2DGet(Vec2f *arg0) {
    arg0->x = -((mbdCameraScrPos[0] / 4.0f) - 160.0f);
    arg0->y = -((mbdCameraScrPos[1] / 4.0f) - 120.0f);
}

void MBDCamera3Dto2D(Vec *arg0, Vec2f *arg1) {
    typedef struct UnkData {
        Vec2f vec;
        f32 unk_08;
        f32 unk_0C;
    } UnkData;

    UnkData sp10;
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f6;

    Hu3D3Dto2D(0, arg0, &sp10.vec);
    temp_f6 = 2.0f * mbdBackScale;
    temp_f2 = SCREEN_WIDTH / temp_f6;
    sp10.vec.x = (temp_f2 - (temp_f2 / mbdBackZoom)) + sp10.vec.x;
    temp_f0 = SCREEN_HEIGHT / temp_f6;
    sp10.vec.y = (temp_f0 - (temp_f0 / mbdBackZoom)) + sp10.vec.y;
    sp10.vec.x = ((sp10.vec.x - 160.0f) * mbdBackScale) + 160.0f;
    sp10.vec.y = ((sp10.vec.y - 120.0f) * mbdBackScale) + 120.0f;
    sp10.unk_08 = (mbdCameraScrPos[0] / 4.0f) - 160.0f;
    sp10.unk_0C = (mbdCameraScrPos[1] / 4.0f) - 120.0f;
    arg1->x = sp10.vec.x + sp10.unk_08;
    arg1->y = sp10.vec.y + sp10.unk_0C;
}

void MBDBackTPLvlSet(u8 arg0) {
    mbdBackTPLvl = arg0;
}

void MBDBackInvertSet(s16 arg0) {
    if (arg0) {
        mbdBackFlag |= 8;
    } else {
        mbdBackFlag &= ~8;
    }
}

void MBDBackFlipSet(s16 arg0) {
    if (arg0) {
        mbdBackFlag |= 0x10;
    } else {
        mbdBackFlag &= ~0x10;
    }
}

void MBDCameraSpeedSet(f32 speed) {
    mbdCameraSpeed = speed;
}

f32 MBDCameraSpeedGet(void) {
    return mbdCameraSpeed;
}

s32 MBDCameraStopCheck(void) {
    return mbdBackFlag & 2;
}

void MBDBackRefresh(Vec* arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f22;

    MBDBackStreamStop();
    MBDBackStreamStart();
    temp_f22 = MBDCameraSpeedGet();
    MBDCameraSpeedSet(-1.0f);
    temp_f20 = MBDCameraSpeedDivGet();
    MBDCameraSpeedDivSet(1.0f);
    MBDBackThreadPriHighSet();
    
    if (arg0 != NULL) {
        MBDCameraPos3DSet(arg0);
    }
    HuPrcVSleep();
    
    if (arg1 != 0) {
        MBDBackThreadPriLowSet();
    }
    
    MBDCameraSpeedDivSet(temp_f20);
    MBDCameraSpeedSet(temp_f22);
}

void MBDBackArcInitDef(void) {
    MBDBackArcInit(hvq_data_ROM_START);
}

void MBDBackCreateNoCamera(s32 arg0) {
    MBDBackCreate(arg0, 1);
    omDelPrcObj(mbdCameraUpdateProc);
    mbdCameraUpdateProc = NULL;
}

void MBDCameraBackOffsetSet(s16 arg0, s16 arg1) {
    MBDBackOffsetSet(arg0, arg1);
}

void MBDCameraScrPosSet(s16 arg0, s16 arg1) {
    mbdCameraScrTarget.x = (arg0 / mbdBackScale) + 160.0f;
    mbdCameraScrTarget.y = (arg1 / mbdBackScale) + 120.0f;
}

void MBDBackSprMain(void) {
    UnkBoard7 *obj;
    Vec2f pos;
    f32 maxX, maxY;
    f32 x, y;
    s32 i;

    while (TRUE) {
        for (i = 0; i < ARRAY_COUNT(mbdBackSprTbl); i++) {
            obj = &mbdBackSprTbl[i];

            if (!(obj->unk_00 & 1)) {
                continue;
            }

            MBDCamera3Dto2D(&obj->pos, &pos);

            if (obj->unk_01 != 0) {
                HuSprPosSet(obj->unk_02, 0, (mbdCameraScrPos[0] / (f32)obj->unk_01) + pos.x, (mbdCameraScrPos[1] / (f32)obj->unk_01) + pos.y);
            } else {
                HuSprPosSet(obj->unk_02, 0, pos.x, pos.y);
            }
            
            HuSprTPLvlSet(obj->unk_02, 0, obj->unk_06);

            if (obj->vel.x != 0.0f) {
                maxX = MBDBackMaxXGet();
                obj->pos.x += obj->vel.x;
                if (obj->pos.x >= maxX) {
                    obj->pos.x -= 2.0f * maxX;
                }
                if (obj->pos.x <= -maxX) {
                    obj->pos.x += 2.0f * maxX;
                }
            }

            if (obj->vel.z != 0.0f) {
                maxY = MBDBackMaxYGet() * 1.5f;
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

            if (mbdBackSprDispF != 0) {
                HuSprDispOn(obj->unk_02, 0);
            } else {
                HuSprDispOff(obj->unk_02, 0);
            }
        }
        HuPrcVSleep();
    }
}

void MBDBackSprInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackSprTbl); i++) {
        mbdBackSprTbl[i].unk_00 = 0;
    }

    mbdBackSprNum = 0;

    MBDBackMdlInit();
}

s32 MBDBackSprCreate(s32 arg0, Vec *arg1) {
    UnkBoard7 *obj;
    Process *proc;
    void *data;
    s32 count;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackSprTbl); i++) {
        obj = &mbdBackSprTbl[i];
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
    
        if (mbdBackSprNum == 0) {
            proc = omAddPrcObj(MBDBackSprMain, 0x1001, 0, 0);
            mbdBackSprProc = proc;
            omPrcSetStatBit(proc, OM_STAT_NOALLPAUSE);
        }
        
        mbdBackSprNum++;
        return i;
    }
    return -1;
}

s32 MBDBackSprCopyCreate(s32 arg0, Vec *arg1) {
    UnkBoard7 *unkBoard7;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackSprTbl); i++) {
        unkBoard7 = &mbdBackSprTbl[i];
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
                            mbdBackSprTbl[arg0].unk_04, 0);
        HuSprAnimModeSet(unkBoard7->unk_02, 0, HUSPR_ANIM_MODE_BANK);
        HuSprPriSet(unkBoard7->unk_02, 0, 0x8000);
        HuSprAttrSet(unkBoard7->unk_02, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
        HuSprScissorSet(unkBoard7->unk_02, 0, 0x10, 0xC, 0x130, 0xE4);

        mbdBackSprNum++;
        return i;
    }
    return -1;
}

static void MBDBackSprKill(s32 arg0) {
    UnkBoard7* temp_s0 = &mbdBackSprTbl[arg0];

    if (temp_s0->unk_00 & 1) {
        if (!(temp_s0->unk_00 & 2)) {
            HuSprAnimKill(temp_s0->unk_04);
        }
        HuSprGrpKill(temp_s0->unk_02);
        temp_s0->unk_00 = 0;
        mbdBackSprNum--;
        if (mbdBackSprNum == 0) {
            omDelPrcObj(mbdBackSprProc);
            mbdBackSprProc = NULL;
        }
    }
}

void MBDBackSprKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackSprTbl); i++) {
        MBDBackSprKill(i);
    }

    MBDBackMdlClose();
}

void MBDBackSprParallaxSet(s32 arg0, s8 arg1) {
    mbdBackSprTbl[arg0].unk_01 = arg1;
}

void MBDBackSprTPLvlSet(s32 arg0, s16 arg1) {
    mbdBackSprTbl[arg0].unk_06 = arg1;
}

void MBDBackSprColorSet(s32 arg0, RGB* arg1) {
    HuSprColorSet(mbdBackSprTbl[arg0].unk_02, 0, arg1->r, arg1->g, arg1->b);
}

void MBDBackSprVelSet(s32 arg0, Vec* arg1) {
    HuVecCopy3F(&mbdBackSprTbl[arg0].vel, arg1);
}

void MBDBackSprDispOn(void) {
    mbdBackSprDispF = 1;
}

void MBDBackSprDispOff(void) {
    mbdBackSprDispF = 0;
}

void MBDBackMdlKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackMdlTbl); i++) {
        if (mbdBackMdlTbl[i] != NULL) {
            MBDModelKill(mbdBackMdlTbl[i]);
            mbdBackMdlTbl[i] = NULL;
        }
    }
}

void MBDBackMdlInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdBackMdlTbl); i++) {
        mbdBackMdlTbl[i] = NULL;
    }
}

static void MBDBackMdlClose(void){
    MBDBackMdlKillAll();
}

#define BG_TEXEL(entry, off) (*(u16 *)((u8 *)(entry)->pixels + (off)))
#define BG_TEX_SIZE (64 * 48 * 2)

void MBDBackColorModeSet(s16 arg0) {
    OverlayBgEntry *entry;
    u16 color;
    u8 r, g, b;
    s32 lum;
    s32 gray;
    s32 i;
    u32 offset;

    switch (arg0) {
        case 0:
            MBDBackRefresh(NULL, 0);
            break;

        case 1:
            for (i = 0; i < ARRAY_COUNT(mbdBackTileTbl); i++) {
                entry = &mbdBackTileTbl[i];
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
