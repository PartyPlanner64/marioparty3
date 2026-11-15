#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfspr.h"
#include "game/malloc.h"
#include "game/hmfanim.h"
#include "game/util.h"
#include "game/camera.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "overlay.h"
#include "game/rom.h"
#include "game/pad.h"
#include "game/mallocblock.h"

#define HAS_TEXT_SECTION 1
#define HAS_DATA_SECTION 2
#define HAS_BSS_SECTION 4

extern u8 padNextIdx;

Vec utilViewportScale[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 0.0f, 0.0f, 0.0f },
};
Vec utilViewportPos[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 0.0f, 0.0f, 0.0f },
};
RectF utilScissor[] = {
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
};
u32 rnd_seed = 0xD9ED;

u16 Hu3DModelRead2(s32 arg0, s32 arg1) {
    return Hu3DModelCreate(DataRead(arg0), arg1);
}

u16 Hu3DModelRead3(s32 arg0, s32 arg1) {
    return Hu3DModelCreate(DataRead(arg0), arg1);
}

u16 Hu3DModelRead(s32 arg0, s32 arg1) {
    return Hu3DModelCreate(DataRead(arg0), arg1);
}

s16 Hu3DMotionModelRead(s32 arg0) {
    return Hu3DModelCreate(DataRead(arg0), 0x1D);
}

u8 rand8(void) {
    rnd_seed = rnd_seed * 0x41C64E6D + 0x3039;
    return ((rnd_seed + 1) >> 16);
}

// checks if the overlay has a text, data, and bss section and dmas/clears the region if so
void OvlModeLoad(s32 arg0, u8 sectionFlags) {
    u8 *textVramEnd;
    u8 *textVramStart;
    u32 romStart;
    u8 *dataVramStart;
    u8 *dataVramEnd;
    u8 *bss_end;
    u8 *bss_start;
    u8 *curBssAddr;
    u8 *textStart;
    u8 *tmp;

    romStart = _modeovltbl[arg0].romStart;
    textVramStart = _modeovltbl[arg0].textVramStart;
    textVramEnd = _modeovltbl[arg0].textVramEnd;
    dataVramStart = _modeovltbl[arg0].dataVramStart;
    dataVramEnd = _modeovltbl[arg0].dataVramEnd;
    bss_start = _modeovltbl[arg0].bssVramStart;
    bss_end = _modeovltbl[arg0].bssVramEnd;
    textStart = _modeovltbl[arg0].vramStart;

    if (sectionFlags & HAS_TEXT_SECTION) {
        dmaReadOvl(romStart, textStart, textVramEnd - textVramStart);
    }
    if (sectionFlags & HAS_DATA_SECTION) {
        dmaReadOvl(romStart + (textVramEnd - textVramStart), dataVramStart, dataVramEnd - dataVramStart);
    }
    if (sectionFlags & HAS_BSS_SECTION) {
        curBssAddr = tmp = bss_start;
        while (tmp < bss_end) {
            *curBssAddr++ = 0;
            tmp++;
        }
    }
}

// copies in an overlay and clears bss region.
void OvlLoad(s32 overlayIndex) {
    u32 rom_start;
    u32 rom_end;
    u8 *bss_start;
    u8 *bss_end;
    u8 *curBssAddr;

    rom_start = _ovltbl[overlayIndex].romStart;
    rom_end = _ovltbl[overlayIndex].romEnd;
    bss_start = _ovltbl[overlayIndex].bssVramStart;
    bss_end = _ovltbl[overlayIndex].bssVramEnd;
    dmaReadOvl(rom_start, _ovltbl[overlayIndex].vramStart, rom_end - rom_start);

    curBssAddr = bss_start;
    while (bss_start < bss_end) {
        *curBssAddr++ = 0;
        bss_start++;
    }

    padNextIdx = 0;
}

void ScissorSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    utilScissor[camIndex].x1 = arg1;
    utilScissor[camIndex].y1 = arg2;
    utilScissor[camIndex].x2 = arg3;
    utilScissor[camIndex].y2 = arg4;
    Hu3DCameraScissorSet(camIndex, &utilScissor[camIndex]);
}

void ViewportSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    utilViewportScale[camIndex].x = arg1;
    utilViewportScale[camIndex].y = arg2;
    utilViewportScale[camIndex].z = arg3;

    utilViewportPos[camIndex].x = arg4;
    utilViewportPos[camIndex].y = arg5;
    utilViewportPos[camIndex].z = arg6;

    Hu3DCameraViewportSet(camIndex, &utilViewportScale[camIndex], &utilViewportPos[camIndex]);
}

void omObjMotionRead(omObjData *arg0, u16 arg1, s32 arg2) {
    s16 temp_v0;

    temp_v0 = Hu3DMotionModelRead(arg2);
    if ((temp_v0 >= 0)) {
        arg0->motion[arg1] = temp_v0;
    }
}

s8 PadNextIndexGet(void) {
    s8 temp_v1;

    if (gNumOfControllers > padNextIdx) {
        temp_v1 = padNextIdx++;
    } else {
        temp_v1 = -1;
    }
    return temp_v1;
}

u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2) {
    u16 temp_s0;
    void *temp_v0;

    temp_v0 = DataRead(arg0);
    temp_s0 = Hu3DSprModelCreate(temp_v0, arg1, (u8)arg2);
    HuMemMemoryFreePerm(temp_v0);
    return temp_s0;
}

s16 Hu3DAnimRead(HmfData* arg0, s32 arg1, char* arg2) {
    s32 temp_s0;
    void *temp_v0;

    temp_v0 = DataRead(arg1);
    temp_s0 = Hu3DAnimCreate(arg0, temp_v0, 0, arg2);
    HuMemMemoryFreePerm(temp_v0);
    return temp_s0;
}

s16 Hu3DModelReadNum(s32 arg0) {
    return Hu3DModelCreate(DataReadNum(arg0, TAG_OVERLAY), 0);
}
