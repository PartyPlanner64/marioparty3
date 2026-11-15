#include "common_duel.h"
#include "ovl_81.h"
#include "game/hmfmath.h"

// Texel data follows the palette, which is padded to a multiple of 4 colors.
#define MASU_BMP_TEXELS(bmp) (&(bmp)->data[((bmp)->palCount + 3) / 4 * 4])

extern u16 D_801050A0_name_81;
extern SpaceData *D_801050A4_name_81;
extern LinkData *D_801050A8_name_81;
extern MasuBmp *D_801050B0_name_81[19];
extern u8 D_80105100_name_81[19];
extern f32 D_80105128_name_81[8];
extern s32 D_80105148_name_81;
extern s16 D_80105150_name_81[255];
extern s16 D_8010534E_name_81;
extern s16 D_80105350_name_81[16];
extern s16 D_80105370_name_81;
extern s32 D_80105378_name_81[0x13];
extern u16 D_801050A2_name_81;
extern s16 D_801050FC_name_81;
extern u16 D_801050FE_name_81;
extern event_list_entry *D_80105114_name_81;
extern event_list_entry *D_80105118_name_81;
extern event_list_entry *D_8010511C_name_81;
extern event_list_entry *D_80105120_name_81;
extern s32 D_80105124_name_81;
extern s16 D_801053C8_name_81[];
extern Mtx *MTXBuf;
extern s16 MTXBufNum;

void *D_80101060_name_81 = NULL;
u8 *D_80101064_name_81 = NULL;
s32 D_80101068_name_81[0x13] = {
    0, 0, 0x13022E, 0x13022C, 0,
    0x13022F, 0x13022B, 0, 0x13022D, 0,
    0x130230, 0x130231, 0x130232, 0x130233, 0x130234,
    0x130235, 0x130236, 0x130237, 0x130238
};
s32 D_801010B4_name_81[0x13] = {
    0, 0, 0x13022E, 0x13022C, 0,
    0x130239, 0x13022B, 0, 0x13022D, 0,
    0x130230, 0x130231, 0x130232, 0x130233, 0x130234,
    0x130235, 0x130236, 0x130237, 0x130238
};

Vtx D_80101100_name_81[] = {
    { { { 100, 0, -100 }, 0, { 1024, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, -100 }, 0, { 0, 992 }, { 0, 0, 127, 255 } } },
    { { { -100, 0, 100 }, 0, { 0, -32 }, { 0, 0, 127, 255 } } },
    { { { 100, 0, 100 }, 0, { 1024, -32 }, { 0, 0, 127, 255 } } },
};

Gfx D_80101140_name_81[] = {
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

void func_800E93C0_name_81(s16);
void func_800E95C4_name_81(Gfx **arg0, Mtx *arg1, s32 arg2);
void func_800EA2C8_name_81(void);
void func_800EA3CC_name_81(s16 spaceIdx, event_list_entry *eventList);
void func_800EA698_name_81(s16 spaceIdx);

void func_800E93C0_name_81(s16 arg0) {
    s32 *dirs;
    s32 i;

    D_801050FC_name_81 = arg0;

    if (GwSystem.current_board_index == 5) {
        dirs = D_801010B4_name_81;
    } else {
        dirs = D_80101068_name_81;
    }

    for (i = 0; i < 0x13; i++) {
        if (dirs[i] != 0) {
            D_801050B0_name_81[i] = DataRead(dirs[i]);
        } else {
            D_801050B0_name_81[i] = NULL;
        }
    }
}

void func_800E9468_name_81(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (D_801050B0_name_81[i] != 0) {
            DataClose(D_801050B0_name_81[i]);
        }
        D_801050B0_name_81[i] = 0;
    }
}

void func_800E94D0_name_81(void) {
    s32 i;

    func_800E93C0_name_81(0);
    D_80101060_name_81 = 0;
    D_80105148_name_81 = 0;

    for (i = 0; i < 0x13; i++) {
        D_80105378_name_81[i] = 0;
    }
}

void func_800E9524_name_81(void) {
    D_80105148_name_81 = 0;
}

void func_800E9530_name_81(f32 value) {
    s32 index = D_80105148_name_81;

    if (index != 8) {
        D_80105148_name_81 = index + 1;
        D_80105128_name_81[index] = value;
    }
}

void func_800E9564_name_81(void) {
    func_800E9468_name_81();
}

void func_800E9580_name_81(s16 arg0) {
    func_800E9468_name_81();
    func_800E93C0_name_81(arg0);
}

void func_800E95B0_name_81(s32 arg0, s16 arg1) {
    D_801053C8_name_81[arg0] = arg1;
}

void func_800E95C4_name_81(Gfx **arg0, Mtx *arg1, s32 arg2) {
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
    if (!(arg2 & 0xFF) && (D_801050FE_name_81 != 0) && (D_80101064_name_81 != NULL)) {
        sp5E = HuProfCpuBegin(0xC8, 0xC8, 0xC8);
        gSPDisplayList((*gfxPos)++, D_80101140_name_81);
        Hu3DCameraSet(0, gfxPos);
        Hu3DCameraScissorDraw(0, gfxPos);
        MBDCameraPos3DGet(&sp50);
        vtx = (Vtx *)OS_K0_TO_PHYSICAL(D_80101100_name_81);

        for (i = 0; i < 0x13; i++) {
            if (D_801050B0_name_81[i] != NULL) {
                if (D_801050B0_name_81[i]->palCount <= 16) {
                    gDPLoadTLUT_pal16((*gfxPos)++, 0, D_801050B0_name_81[i]->data);
                    gDPLoadTextureBlock_4b((*gfxPos)++, MASU_BMP_TEXELS(D_801050B0_name_81[i]), G_IM_FMT_CI,
                                           32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTLUT_pal256((*gfxPos)++, D_801050B0_name_81[i]->data);
                    gDPLoadTextureBlock((*gfxPos)++, MASU_BMP_TEXELS(D_801050B0_name_81[i]), G_IM_FMT_CI,
                                        G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
                for (j = 0; j < D_801050A0_name_81; j++) {
                    s32 spaceId = *(i * 128 + D_80101064_name_81 + j);
                    if (spaceId == 0xFF) {
                        break;
                    }
                    space = MBDMasuGet(spaceId);
                    func_80089980_main(sp10, &camMtx[1]);
                    mtxTransCat(sp10, space->coords.x, space->coords.y, space->coords.z);
                    mtxScaleCat(sp10, space->rot.x * 0.8f, 1.0f, space->rot.z * 0.8f);
                    mtx = &MTXBuf[MTXBufNum++];
                    func_800898F0_main(sp10, mtx);
                    gSPMatrix((*gfxPos)++, OS_K0_TO_PHYSICAL(mtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex((*gfxPos)++, vtx, 4, 0);
                    gSP1Quadrangle((*gfxPos)++, 0, 1, 2, 3, 0);
                }
            }
        }

        HuProfCpuEnd(sp5E);
    }
}

u16 *func_800E9B00_name_81(u16 *base, s32 offset) {
    return (u16 *)((u8 *)base + *(u16 *)((u8 *)base + offset));
}

s32 func_800E9B10_name_81(s32 arg0, s16 arg1) {
    f32 sp10[3];
    LinkData *link;
    SpaceData *space;
    s16 *spaces;
    u16 *data;
    u16 *links;
    s32 i;
    s32 j;

    D_80101060_name_81 = DataRead((arg0 << 0x10) | arg1);
    if (D_80101060_name_81 != NULL) {
        D_80105114_name_81 = NULL;
        D_80105118_name_81 = NULL;
        D_8010511C_name_81 = NULL;
        D_80105120_name_81 = NULL;
        data = D_80101060_name_81;
        D_801050A0_name_81 = data[0];
        D_801050A2_name_81 = data[1];
        D_801050A4_name_81 = HuMemMemoryAllocTemp(D_801050A0_name_81 * sizeof(SpaceData));
        data = func_800E9B00_name_81(D_80101060_name_81, 4);
        space = D_801050A4_name_81;
        for (i = 0; i < D_801050A0_name_81; i++) {
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
        D_801050A8_name_81 = HuMemMemoryAllocTemp(D_801050A2_name_81 * sizeof(LinkData));
        links = func_800E9B00_name_81(D_80101060_name_81, 6);
        link = D_801050A8_name_81;
        for (i = 0; i < D_801050A2_name_81; i++) {
            data = func_800E9B00_name_81(links, i * 2);
            link->chainIndicies = *data++;
            link->spaces = HuMemMemoryAllocTemp(link->chainIndicies << 1);
            spaces = link->spaces;
            for (j = 0; j < link->chainIndicies; j++) {
                *spaces++ = *data++;
            }
            link++;
        }
        DataClose(D_80101060_name_81);
        Hu3DLayerHookSet(1, &func_800E95C4_name_81);
        D_801050FE_name_81 = 1;
    }
    D_8010534E_name_81 = 0;
    D_80105370_name_81 = 0;

    return 0;
}

void func_800E9D9C_name_81(void) {
    LinkData *link;
    s32 i;

    if (D_80101060_name_81 != NULL) {
        D_80101060_name_81 = NULL;
        D_801050FE_name_81 = 0;
        HuMemMemoryFreeTemp(D_801050A4_name_81);

        link = D_801050A8_name_81;
        for (i = 0; i < D_801050A2_name_81; i++, link++) {
            HuMemMemoryFreeTemp(link->spaces);
        }

        HuMemMemoryFreeTemp(D_801050A8_name_81);
        Hu3DLayerHookSet(1, NULL);
    }
    if (D_80101064_name_81 != NULL) {
        HuMemMemoryFreeTemp(D_80101064_name_81);
        D_80101064_name_81 = NULL;
    }
}

SpaceData *MBDMasuGet(s16 spaceIdx) {
    return &D_801050A4_name_81[spaceIdx];
}

s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx) {
    return D_801050A8_name_81[linkIdx].spaces[spaceIdx];
}

s16 MBDMasuLinkNumGet(u16 linkIdx) {
    return D_801050A8_name_81[linkIdx].chainIndicies;
}

s16 func_800E9ECC_name_81(s16 spaceIdx, s16 linkIdx) {
    s32 i;

    for (i = 0; i < MBDMasuLinkNumGet(linkIdx); i++) {
        if (MBDMasuLinkMasuIdGet(linkIdx, i) == spaceIdx) {
            return i;
        }
    }
    return -1;
}

void func_800E9F4C_name_81(s16 spaceIdx, s8 *chainOut, s8 *linkOut) {
    s32 chain;
    s32 link;

    for (chain = 0; chain < D_801050A2_name_81; chain++) {
        for (link = 0; link < MBDMasuLinkNumGet(chain); link++) {
            if (MBDMasuLinkMasuIdGet(chain, link) == spaceIdx) {
                *chainOut = chain;
                *linkOut = link;
                return;
            }
        }
    }
}

s32 func_800EA010_name_81(s16 spaceIdx, s8 *chainOut, s8 *linkOut) {
    s16 link;
    s32 i;

    for (i = 0; i < D_801050A2_name_81; i++) {
        if (*chainOut == i) {
            continue;
        }

        link = func_800E9ECC_name_81(spaceIdx, i);
        if (link != -1) {
            *chainOut = i;
            *linkOut = link;
            return 0;
        }
    }
    return -1;
}

void func_800EA0C0_name_81(void) {
    LinkData *chain;
    s16 *space;
    s16 i;
    s16 j;
    s16 k;

    chain = D_801050A8_name_81;

    for (i = 0; i < D_801050A2_name_81; i++) {
        space = chain->spaces;

        for (j = 0; j < chain->chainIndicies; j++) {
            if (MBDMasuGet(*space)->space_type == 9) {
                for (k = 0; k < MBD_MAX_PLAYERS; k++) {
                    func_800ECD0C_name_81(k, i, j);
                }
                return;
            }
            space++;
        }
        chain++;
    }

    for (k = 0; k < MBD_MAX_PLAYERS; k++) {
        func_800ECD0C_name_81(k, 0, 0);
    }
}

void func_800EA1FC_name_81(s16 spaceIdx, u16 newSpaceType) {
    MBDMasuGet(spaceIdx)->space_type = newSpaceType;
}

void func_800EA22C_name_81(u16 linkNo, u16 curSpaceType, u8 newSpaceType) {
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

void func_800EA2C8_name_81(void) {
    SpaceData *space;
    f32 baseScale;
    f32 scale;
    Process *proc = HuPrcCurrentGet();

    space = MBDMasuGet((s16)(s32)proc->user_data);
    baseScale = space->rot.x;
    scale = baseScale + 0.03f;
    if (D_80101060_name_81 != NULL) {
        while (1) {
            HuPrcVSleep();

            scale -= 0.005f;
            if (scale <= baseScale) {
                scale = baseScale;
            }

            space->rot.x = scale;
            space->rot.z = scale;
            if ((scale <= baseScale) || (D_80101060_name_81 == NULL)) {
                break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void func_800EA388_name_81(s16 spaceIdx) {
    Process *prc = omAddPrcObj(func_800EA2C8_name_81, 0xEF00, 0, 0);
    prc->user_data = (void *)(s32)spaceIdx;
}

void func_800EA3CC_name_81(s16 spaceIdx, event_list_entry *eventList) {
    switch (spaceIdx) {
        case -2:
            D_80105114_name_81 = eventList;
            break;
        case -3:
            D_80105118_name_81 = eventList;
            break;
        case -4:
            D_8010511C_name_81 = eventList;
            break;
        case -5:
            D_80105120_name_81 = eventList;
            break;
        default:
            MBDMasuGet(spaceIdx)->event_list = eventList;
            break;
    }
}

void func_800EA46C_name_81(event_table_entry *table) {
    event_table_entry *entry;

    for (entry = table; entry->space_index != -1; entry++) {
        func_800EA3CC_name_81(entry->space_index, entry->event_list);
    }
}

s32 func_800EA4D4_name_81(s16 spaceIdx, s16 activationType) {
    event_list_entry *entry;
    Process *proc;
    s16 prevSpace;
    s32 ret;

    switch (spaceIdx) {
        case -2: entry = D_80105114_name_81; break;
        case -3: entry = D_80105118_name_81; break;
        case -4: entry = D_8010511C_name_81; break;
        case -5: entry = D_80105120_name_81; break;
        default: entry = MBDMasuGet(spaceIdx)->event_list; break;
    }

    ret = 0;
    prevSpace = func_800EA6A4_name_81();
    func_800EA698_name_81(spaceIdx);

    if (entry != NULL) {
        while (entry->activation_type != 0) {
            if (entry->activation_type == activationType) {
                D_80105124_name_81 = 0;
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
                ret |= D_80105124_name_81;
            }
            entry++;
        }
    }

    func_800EA698_name_81(prevSpace);
    return ret;
}

void func_800EA68C_name_81(s32 result) {
    D_80105124_name_81 = result;
}

void func_800EA698_name_81(s16 spaceIdx) {
    GwSystem.current_space_index = spaceIdx;
}

s16 func_800EA6A4_name_81(void) {
    return GwSystem.current_space_index;
}

void func_800EA6B0_name_81(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        D_80105150_name_81[i] = *arg0++;
    }

    D_8010534E_name_81 = i;
}

void func_800EA708_name_81(s16 *arg0) {
    s32 i;

    for (i = 0; *arg0 != -1; i++) {
        D_80105350_name_81[i] = *arg0++;
    }

    D_80105370_name_81 = i;
}

void func_800EA760_name_81(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        GwSystem.unk_2A[i] = 0;
    }
}

void func_800EA788_name_81(s16 unk_17_value, s8 unk_2A_value) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] == 0) {
            GwSystem.unk_17[i] = unk_17_value;
            GwSystem.unk_2A[i] = unk_2A_value + 1;
            break;
        }
    }
}

void func_800EA7D4_name_81(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0) {
            func_800EA1FC_name_81(GwSystem.unk_17[i], GwPlayer[GwSystem.unk_2A[i] - 1].chr + 0xB);
        }
    }
}

s32 func_800EA848_name_81(s16 unk_17_value) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0 && GwSystem.unk_17[i] == unk_17_value) {
            return GwSystem.unk_2A[i] - 1;
        }
    }
    return -1;
}

void func_800EA898_name_81(s32 playerIndex, s32 newPlayerIndex) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] - 1 == playerIndex) {
            GwSystem.unk_2A[i] = newPlayerIndex + 1;
        }
    }
}

void func_800EA8DC_name_81(void) {
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] != 0) {
            func_800EA1FC_name_81(GwSystem.unk_17[i], 6);
            GwSystem.unk_2A[i] = 0;
        }
    }
}

s32 func_800EA940_name_81(s32 playerIndex) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x13; i++) {
        if (GwSystem.unk_2A[i] == playerIndex + 1) {
            count++;
        }
    }
    return count;
}

void func_800EA97C_name_81(void) {
    s32 i;
    s32 j;
    s32 n;

    if (D_80101064_name_81 != NULL) {
        HuMemMemoryFreeTemp(D_80101064_name_81);
    }
    D_80101064_name_81 = HuMemMemoryAllocTemp(0x980);

    for (i = 0; i < 0x13; i++) {
        n = 0;
        for (j = 0; j < D_801050A0_name_81; j++) {
            if (MBDMasuGet(j)->space_type == i) {
                *(i * 128 + D_80101064_name_81 + n) = j;
                n++;
            }
        }
        *(i * 128 + D_80101064_name_81 + n) = 0xFF;
        D_80105100_name_81[i] = n;
    }
}

s32 func_800EAA7C_name_81(s32 spaceType) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < D_801050A0_name_81; i++) {
        count += (MBDMasuGet(i)->space_type == spaceType);
    }
    return count;
}

u8 func_800EAAF8_name_81(s32 spaceType, s32 index) {
    return *(spaceType * 128 + D_80101064_name_81 + index);
}
