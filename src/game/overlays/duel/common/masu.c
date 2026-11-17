#include "common_duel.h"
#include "ovl_81.h"
#include "game/hmfmath.h"

// Texel data follows the palette, which is padded to a multiple of 4 colors.
#define MASU_BMP_TEXELS(bmp) (&(bmp)->data[((bmp)->palCount + 3) / 4 * 4])

extern u16 mbdMasuNum;
extern SpaceData *mbdMasuTbl;
extern LinkData *mbdMasuLinkTbl;
extern MasuBmp *mbdMasuBmpDataTbl[MBD_MASU_TYPE_MAX];
extern u8 mbdMasuTypeNumTbl[MBD_MASU_TYPE_MAX];
extern f32 mbdMasuArrowAngleTbl[8];
extern s32 mbdMasuArrowAngleNum;
extern s16 mbdMasuBlockExtTbl[255];
extern s16 mbdMasuBlockExtNum;
extern s16 mbdMasuBlockTbl[16];
extern s16 mbdMasuBlockNum;
extern s32 mbdMasuFlagTbl[0x13];
extern u16 mbdMasuLinkNum;
extern s16 mbdMasuBmpMode;
extern u16 mbdMasuDispF;
extern event_list_entry *mbdMasuEventBoardStartTbl;
extern event_list_entry *mbdMasuEventRoundEndTbl;
extern event_list_entry *mbdMasuEventTurnStartTbl;
extern event_list_entry *mbdMasuEventTurnTelopTbl;
extern s32 mbdMasuEventResult;
extern s16 mbdMasuStarTbl[];
extern Mtx *MTXBuf;
extern s16 MTXBufNum;

void *mbdMasuData = NULL;
u8 *mbdMasuTypeListTbl = NULL;
s32 mbdMasuBmpTbl[MBD_MASU_TYPE_MAX] = {
    0, 0, 0x13022E, 0x13022C, 0,
    0x13022F, 0x13022B, 0, 0x13022D, 0,
    0x130230, 0x130231, 0x130232, 0x130233, 0x130234,
    0x130235, 0x130236, 0x130237, 0x130238
};
s32 mbdMasuBmpAltTbl[MBD_MASU_TYPE_MAX] = {
    0, 0, 0x13022E, 0x13022C, 0,
    0x130239, 0x13022B, 0, 0x13022D, 0,
    0x130230, 0x130231, 0x130232, 0x130233, 0x130234,
    0x130235, 0x130236, 0x130237, 0x130238
};

Vtx mbdMasuVtx[] = {
    { { { 100, 0, -100 }, 0, { 1024, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, -100 }, 0, { 0, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, 100 }, 0, { 0, -32 }, { 0, 0, 127, 255 } } },
    { { { 100, 0, 100 }, 0, { 1024, -32 }, { 0, 0, 127, 255 } } },
};

Gfx mbdMasuGfxInit[] = {
    gsSPSegment(0, 0),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};

void MBDMasuBmpCreate(s16);
void MBDMasuDraw(Gfx **arg0, Mtx *arg1, s32 arg2);
void MBDMasuBounceProc(void);
void MBDMasuEventSet(s16 spaceIdx, event_list_entry *eventList);
void MBDMasuCurSet(s16 spaceIdx);

void MBDMasuBmpCreate(s16 arg0) {
    s32 *dirs;
    s32 i;

    mbdMasuBmpMode = arg0;

    if (GwSystem.current_board_index == 5) {
        dirs = mbdMasuBmpAltTbl;
    } else {
        dirs = mbdMasuBmpTbl;
    }

    for (i = 0; i < MBD_MASU_TYPE_MAX; i++) {
        if (dirs[i] != 0) {
            mbdMasuBmpDataTbl[i] = DataRead(dirs[i]);
        } else {
            mbdMasuBmpDataTbl[i] = NULL;
        }
    }
}

void MBDMasuBmpKill(void) {
    s32 i;

    for (i = 0; i < MBD_MASU_TYPE_MAX; i++) {
        if (mbdMasuBmpDataTbl[i] != 0) {
            DataClose(mbdMasuBmpDataTbl[i]);
        }
        mbdMasuBmpDataTbl[i] = 0;
    }
}

void MBDMasuInit(void) {
    s32 i;

    MBDMasuBmpCreate(0);
    mbdMasuData = 0;
    mbdMasuArrowAngleNum = 0;

    for (i = 0; i < 0x13; i++) {
        mbdMasuFlagTbl[i] = 0;
    }
}

void MBDMasuArrowAngleReset(void) {
    mbdMasuArrowAngleNum = 0;
}

void MBDMasuArrowAngleAdd(f32 value) {
    s32 index = mbdMasuArrowAngleNum;

    if (index != 8) {
        mbdMasuArrowAngleNum = index + 1;
        mbdMasuArrowAngleTbl[index] = value;
    }
}

void MBDMasuClose(void) {
    MBDMasuBmpKill();
}

void MBDMasuBmpModeSet(s16 arg0) {
    MBDMasuBmpKill();
    MBDMasuBmpCreate(arg0);
}

void MBDMasuStarSet(s32 arg0, s16 arg1) {
    mbdMasuStarTbl[arg0] = arg1;
}

void MBDMasuDraw(Gfx **arg0, Mtx *arg1, s32 arg2) {
    Gfx **gfxPos = arg0;
    HuMtx4F sp10;
    Mtx *camMtx;
    Vtx *vtx;
    Vec2f sp50;
    s16 sp5E;
    SpaceData *space;
    Mtx *mtx;
    MasuBmp *bmp;
    s32 i;
    s32 j;

    camMtx = arg1;
    if (!(arg2 & 0xFF) && (mbdMasuDispF != 0) && (mbdMasuTypeListTbl != NULL)) {
        sp5E = HuProfCpuBegin(0xC8, 0xC8, 0xC8);
        gSPDisplayList((*gfxPos)++, mbdMasuGfxInit);
        Hu3DCameraSet(0, gfxPos);
        Hu3DCameraScissorDraw(0, gfxPos);
        MBDCameraPos3DGet(&sp50);
        vtx = (Vtx *)OS_K0_TO_PHYSICAL(mbdMasuVtx);

        for (i = 0; i < MBD_MASU_TYPE_MAX; i++) {
            if (mbdMasuBmpDataTbl[i] != NULL) {
                if (mbdMasuBmpDataTbl[i]->palCount <= 16) {
                    gDPLoadTLUT_pal16((*gfxPos)++, 0, mbdMasuBmpDataTbl[i]->data);
                    gDPLoadTextureBlock_4b((*gfxPos)++, MASU_BMP_TEXELS(mbdMasuBmpDataTbl[i]), G_IM_FMT_CI,
                                           32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTLUT_pal256((*gfxPos)++, mbdMasuBmpDataTbl[i]->data);
                    gDPLoadTextureBlock((*gfxPos)++, MASU_BMP_TEXELS(mbdMasuBmpDataTbl[i]), G_IM_FMT_CI,
                                        G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
                for (j = 0; j < mbdMasuNum; j++) {
                    s32 spaceId = *(i * SPACES_MAX + mbdMasuTypeListTbl + j);
                    if (spaceId == 0xFF) {
                        break;
                    }
                    space = MBDMasuGet(spaceId);
                    HuMtxL2F(sp10, &camMtx[1]);
                    mtxTransCat(sp10, space->coords.x, space->coords.y, space->coords.z);
                    mtxScaleCat(sp10, space->rot.x * 0.8f, 1.0f, space->rot.z * 0.8f);
                    mtx = &MTXBuf[MTXBufNum++];
                    HuMtxF2L(sp10, mtx);
                    gSPMatrix((*gfxPos)++, OS_K0_TO_PHYSICAL(mtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex((*gfxPos)++, vtx, 4, 0);
                    gSP1Quadrangle((*gfxPos)++, 0, 1, 2, 3, 0);
                }
            }
        }

        HuProfCpuEnd(sp5E);
    }
}

u16 *MBDMasuDataOfsGet(u16 *base, s32 offset) {
    return (u16 *)((u8 *)base + *(u16 *)((u8 *)base + offset));
}

s32 MBDMasuCreate(s32 arg0, s16 arg1) {
    f32 sp10[3];
    LinkData *link;
    SpaceData *space;
    s16 *spaces;
    u16 *data;
    u16 *links;
    s32 i;
    s32 j;

    mbdMasuData = DataRead((arg0 << 0x10) | arg1);
    if (mbdMasuData != NULL) {
        mbdMasuEventBoardStartTbl = NULL;
        mbdMasuEventRoundEndTbl = NULL;
        mbdMasuEventTurnStartTbl = NULL;
        mbdMasuEventTurnTelopTbl = NULL;
        data = mbdMasuData;
        mbdMasuNum = data[0];
        mbdMasuLinkNum = data[1];
        mbdMasuTbl = HuMemMemoryAllocTemp(mbdMasuNum * sizeof(SpaceData));
        data = MBDMasuDataOfsGet(mbdMasuData, 4);
        space = mbdMasuTbl;
        for (i = 0; i < mbdMasuNum; i++) {
            space->unk_00 = 1;
            space->unk_02 = *data++;
            space->space_type = *data++;
            sp10[0] = space->coords.x = ((f32 *)data)[0] * 5.0f * MBDBackMdlScaleGet();
            sp10[1] = space->coords.y = ((f32 *)data)[1] * 5.0f * MBDBackMdlScaleGet();
            sp10[2] = space->coords.z = ((f32 *)data)[2] * 5.0f * MBDBackMdlScaleGet();
            data += 6;
            space->rot.x = MBDBackMdlScaleGet();
            space->rot.y = MBDBackMdlScaleGet();
            space->rot.z = MBDBackMdlScaleGet();
            space->event_list = NULL;
            space++;
        }
        (void)sp10;
        mbdMasuLinkTbl = HuMemMemoryAllocTemp(mbdMasuLinkNum * sizeof(LinkData));
        links = MBDMasuDataOfsGet(mbdMasuData, 6);
        link = mbdMasuLinkTbl;
        for (i = 0; i < mbdMasuLinkNum; i++) {
            data = MBDMasuDataOfsGet(links, i * 2);
            link->chainIndicies = *data++;
            link->spaces = HuMemMemoryAllocTemp(link->chainIndicies << 1);
            spaces = link->spaces;
            for (j = 0; j < link->chainIndicies; j++) {
                *spaces++ = *data++;
            }
            link++;
        }
        DataClose(mbdMasuData);
        Hu3DLayerHookSet(1, &MBDMasuDraw);
        mbdMasuDispF = 1;
    }
    mbdMasuBlockExtNum = 0;
    mbdMasuBlockNum = 0;

    return 0;
}

void MBDMasuKill(void) {
    LinkData *link;
    s32 i;

    if (mbdMasuData != NULL) {
        mbdMasuData = NULL;
        mbdMasuDispF = 0;
        HuMemMemoryFreeTemp(mbdMasuTbl);

        link = mbdMasuLinkTbl;
        for (i = 0; i < mbdMasuLinkNum; i++, link++) {
            HuMemMemoryFreeTemp(link->spaces);
        }

        HuMemMemoryFreeTemp(mbdMasuLinkTbl);
        Hu3DLayerHookSet(1, NULL);
    }
    if (mbdMasuTypeListTbl != NULL) {
        HuMemMemoryFreeTemp(mbdMasuTypeListTbl);
        mbdMasuTypeListTbl = NULL;
    }
}

SpaceData *MBDMasuGet(s16 spaceIdx) {
    return &mbdMasuTbl[spaceIdx];
}

s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx) {
    return mbdMasuLinkTbl[linkIdx].spaces[spaceIdx];
}

s16 MBDMasuLinkNumGet(u16 linkIdx) {
    return mbdMasuLinkTbl[linkIdx].chainIndicies;
}

s16 MBDMasuLinkSearch(s16 spaceIdx, s16 linkIdx) {
    s32 i;

    for (i = 0; i < MBDMasuLinkNumGet(linkIdx); i++) {
        if (MBDMasuLinkMasuIdGet(linkIdx, i) == spaceIdx) {
            return i;
        }
    }
    return -1;
}

void MBDMasuLinkIdxGet(s16 spaceIdx, s8 *chainOut, s8 *linkOut) {
    s32 chain;
    s32 link;

    for (chain = 0; chain < mbdMasuLinkNum; chain++) {
        for (link = 0; link < MBDMasuLinkNumGet(chain); link++) {
            if (MBDMasuLinkMasuIdGet(chain, link) == spaceIdx) {
                *chainOut = chain;
                *linkOut = link;
                return;
            }
        }
    }
}

s32 MBDMasuOtherLinkGet(s16 spaceIdx, s8 *chainOut, s8 *linkOut) {
    s16 link;
    s32 i;

    for (i = 0; i < mbdMasuLinkNum; i++) {
        if (*chainOut == i) {
            continue;
        }

        link = MBDMasuLinkSearch(spaceIdx, i);
        if (link != -1) {
            *chainOut = i;
            *linkOut = link;
            return 0;
        }
    }
    return -1;
}

void MBDPlayerStartMasuSet(void) {
    LinkData *chain;
    s16 *space;
    s16 i;
    s16 j;
    s16 k;

    chain = mbdMasuLinkTbl;

    for (i = 0; i < mbdMasuLinkNum; i++) {
        space = chain->spaces;

        for (j = 0; j < chain->chainIndicies; j++) {
            if (MBDMasuGet(*space)->space_type == MBD_MASU_TYPE_START_BLUE) {
                for (k = 0; k < MBD_MAX_PLAYERS; k++) {
                    MBDMoveMasuSet(k, i, j);
                }
                return;
            }
            space++;
        }
        chain++;
    }

    for (k = 0; k < MBD_MAX_PLAYERS; k++) {
        MBDMoveMasuSet(k, 0, 0);
    }
}

void MBDMasuTypeSet(s16 spaceIdx, u16 newSpaceType) {
    MBDMasuGet(spaceIdx)->space_type = newSpaceType;
}

void MBDMasuLinkTypeSet(u16 linkNo, u16 curSpaceType, u8 newSpaceType) {
    s32 linkSpaceCount;
    SpaceData *space;
    s32 i;

    linkSpaceCount = MBDMasuLinkNumGet(linkNo);

    for (i = 0; i < linkSpaceCount; i++) {
        space = MBDMasuGet(MBDMasuLinkMasuIdGet(linkNo, i));
        if (space->space_type == curSpaceType) {
            space->space_type = newSpaceType;
        }
    }
}

void MBDMasuBounceProc(void) {
    SpaceData *space;
    f32 baseScale;
    f32 scale;
    Process *proc = HuPrcCurrentGet();

    space = MBDMasuGet((s16)(s32)proc->user_data);
    baseScale = space->rot.x;
    scale = baseScale + 0.03f;
    if (mbdMasuData != NULL) {
        while (1) {
            HuPrcVSleep();

            scale -= 0.005f;
            if (scale <= baseScale) {
                scale = baseScale;
            }

            space->rot.x = scale;
            space->rot.z = scale;
            if ((scale <= baseScale) || (mbdMasuData == NULL)) {
                break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void MBDMasuBounceCreate(s16 spaceIdx) {
    Process *prc = omAddPrcObj(MBDMasuBounceProc, 0xEF00, 0, 0);
    prc->user_data = (void *)(s32)spaceIdx;
}

void MBDMasuEventSet(s16 spaceIdx, event_list_entry *eventList) {
    switch (spaceIdx) {
        case -2:
            mbdMasuEventBoardStartTbl = eventList;
            break;
        case -3:
            mbdMasuEventRoundEndTbl = eventList;
            break;
        case -4:
            mbdMasuEventTurnStartTbl = eventList;
            break;
        case -5:
            mbdMasuEventTurnTelopTbl = eventList;
            break;
        default:
            MBDMasuGet(spaceIdx)->event_list = eventList;
            break;
    }
}

void MBDMasuEventTblAdd(event_table_entry *table) {
    event_table_entry *entry;

    for (entry = table; entry->space_index != -1; entry++) {
        MBDMasuEventSet(entry->space_index, entry->event_list);
    }
}

s32 MBDMasuEventCall(s16 spaceIdx, s16 activationType) {
    event_list_entry *entry;
    Process *proc;
    s16 prevSpace;
    s32 ret;

    switch (spaceIdx) {
        case -2: entry = mbdMasuEventBoardStartTbl; break;
        case -3: entry = mbdMasuEventRoundEndTbl; break;
        case -4: entry = mbdMasuEventTurnStartTbl; break;
        case -5: entry = mbdMasuEventTurnTelopTbl; break;
        default: entry = MBDMasuGet(spaceIdx)->event_list; break;
    }

    ret = 0;
    prevSpace = MBDMasuCurGet();
    MBDMasuCurSet(spaceIdx);

    if (entry != NULL) {
        while (entry->activation_type != 0) {
            if (entry->activation_type == activationType) {
                mbdMasuEventResult = 0;
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
                ret |= mbdMasuEventResult;
            }
            entry++;
        }
    }

    MBDMasuCurSet(prevSpace);
    return ret;
}

void MBDMasuEventResultSet(s32 result) {
    mbdMasuEventResult = result;
}

void MBDMasuCurSet(s16 spaceIdx) {
    GwSystem.current_space_index = spaceIdx;
}

s16 MBDMasuCurGet(void) {
    return GwSystem.current_space_index;
}

void MBDMasuBlockTblExtSet(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        mbdMasuBlockExtTbl[i] = *arg0++;
    }

    mbdMasuBlockExtNum = i;
}

void MBDMasuBlockTblSet(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        mbdMasuBlockTbl[i] = *arg0++;
    }

    mbdMasuBlockNum = i;
}

void MBDMasuOwnerInit(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        GwSystem.unk_2A[i] = 0;
    }
}

void MBDMasuOwnerAdd(s16 unk_17_value, s8 unk_2A_value) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] == 0) {
            GwSystem.unk_17[i] = unk_17_value;
            GwSystem.unk_2A[i] = unk_2A_value + 1;
            break;
        }
    }
}

void MBDMasuOwnerTypeUpdate(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0) {
            MBDMasuTypeSet(GwSystem.unk_17[i], MBD_MASU_TYPE_CHR(GwPlayer[GwSystem.unk_2A[i] - 1].chr));
        }
    }
}

s32 MBDMasuOwnerGet(s16 unk_17_value) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0 && GwSystem.unk_17[i] == unk_17_value) {
            return GwSystem.unk_2A[i] - 1;
        }
    }
    return -1;
}

void MBDMasuOwnerSwap(s32 playerIndex, s32 newPlayerIndex) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] - 1 == playerIndex) {
            GwSystem.unk_2A[i] = newPlayerIndex + 1;
        }
    }
}

void MBDMasuOwnerClear(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0) {
            MBDMasuTypeSet(GwSystem.unk_17[i], MBD_MASU_TYPE_BASIC);
            GwSystem.unk_2A[i] = 0;
        }
    }
}

s32 MBDMasuOwnerNumGet(s32 playerIndex) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] == playerIndex + 1) {
            count++;
        }
    }
    return count;
}

void MBDMasuTypeListCreate(void) {
    s32 i;
    s32 j;
    s32 n;

    if (mbdMasuTypeListTbl != NULL) {
        HuMemMemoryFreeTemp(mbdMasuTypeListTbl);
    }
    mbdMasuTypeListTbl = HuMemMemoryAllocTemp(MBD_MASU_TYPE_MAX * SPACES_MAX);

    for (i = 0; i < MBD_MASU_TYPE_MAX; i++) {
        n = 0;
        for (j = 0; j < mbdMasuNum; j++) {
            if (MBDMasuGet(j)->space_type == i) {
                *(i * SPACES_MAX + mbdMasuTypeListTbl + n) = j;
                n++;
            }
        }
        *(i * SPACES_MAX + mbdMasuTypeListTbl + n) = 0xFF;
        mbdMasuTypeNumTbl[i] = n;
    }
}

s32 MBDMasuTypeNumGet(s32 spaceType) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < mbdMasuNum; i++) {
        count += (MBDMasuGet(i)->space_type == spaceType);
    }
    return count;
}

u8 MBDMasuTypeListGet(s32 spaceType, s32 index) {
    return *(spaceType * SPACES_MAX + mbdMasuTypeListTbl + index);
}
