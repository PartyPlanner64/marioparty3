#include "ultra64.h"
#include "types.h"
#include "macros.h"
#include "humath.h"
#include "game/profiler.h"
#include "PR/os.h"

#define PROF_MAX_SAMPLES 10

typedef struct
{
    s16 unk0;
    s16 unk2;
} ProfTaskConfig;

typedef struct
{
    s32 unk0;
    s16 sampleCount;
    ProfTaskConfig config;
    s32 colors[PROF_MAX_SAMPLES];     // 000C
    u32 startTimes[PROF_MAX_SAMPLES]; // 0034
    u32 endTimes[PROF_MAX_SAMPLES];
} ProfSampleBuff;

OSTime HuProfRecordEnd(ProfSampleBuff *buffer, s16 sampleIdx);

static ProfSampleBuff HuProfCpuDispBuf;
// Global so undefined_syms.txt can alias their sampleCount fields, and aligned
// to match the placement they get as statics.
ProfSampleBuff HuProfCpuBuf BSS ALIGNED(8);
ProfSampleBuff HuProfRspBuf BSS ALIGNED(8);
// sampleCount fields of the buffers above (see undefined_syms.txt). The
// original resets them through these separate symbols.
extern s16 HuProfCpuSampleNum;
extern s16 HuProfRspSampleNum;
static u32 HuProfRspAwaitTime;
static OSMesgQueue HuProfMesgQueue;
static OSMesg HuProfMesgBuf[3];
static u32 HuProfPad; // unreferenced
// RSP task fields (an OSTask layout followed by its completion queue and message)
static u32 HuProfTaskType; // type
static u32 HuProfTaskFlags; // flags
static u64 *HuProfTaskUcodeBoot; // ucode_boot
static u32 HuProfTaskUcodeBootSize; // ucode_boot_size
static u64 *HuProfTaskUcode; // ucode
static u32 HuProfTaskUcodeSize; // ucode_size
static u64 *HuProfTaskUcodeData; // ucode_data
static u32 HuProfTaskUcodeDataSize; // ucode_data_size
static u64 *HuProfTaskDramStack; // dram_stack
static u32 HuProfTaskDramStackSize; // dram_stack_size
static u64 *HuProfTaskOutputBuff; // output_buff
static u64 *HuProfTaskOutputBuffSize; // output_buff_size
static u64 *HuProfTaskDataPtr; // data_ptr
static u32 HuProfTaskDataSize; // data_size
static u64 *HuProfTaskYieldDataPtr; // yield_data_ptr
static u32 HuProfTaskYieldDataSize; // yield_data_size
static OSMesgQueue *HuProfTaskMesgQueue;
static OSMesg HuProfTaskMesg;
static Gfx HuProfGfxBuf[0x80];

extern s32 *gUCodeAddresses;

void HuProfInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    HuProfCpuBuf.config.unk0 = arg1;
    HuProfCpuBuf.config.unk2 = arg2;
    HuProfRspBuf.config.unk0 = arg3;
    HuProfRspBuf.config.unk2 = arg4;
    HuProfTaskMesgQueue = &HuProfMesgQueue;
    HuProfTaskMesg = 0;
    HuProfTaskType = 1;
    HuProfTaskFlags = 2;
    HuProfTaskUcodeBoot = (u64 *)rspbootTextStart;
    HuProfTaskUcodeBootSize = (u32)rspbootTextEnd - (u32)rspbootTextStart;
    HuProfTaskUcodeSize = 0x1000;
    HuProfTaskUcodeDataSize = 0x800;
    HuProfTaskDramStackSize = 0x400;
    HuProfTaskDataPtr = (u64 *)HuProfGfxBuf;
    HuProfTaskDataSize = 0;
    HuProfTaskYieldDataSize = 0xC00;
    HuProfTaskUcode = (u64 *)gUCodeAddresses[arg0 * 2];
    HuProfTaskUcodeData = (u64 *)gUCodeAddresses[(arg0 * 2) | 1];
    osCreateMesgQueue(&HuProfMesgQueue, HuProfMesgBuf, ARRAY_COUNT(HuProfMesgBuf));
}

void HuProfRecordAwaitRsp(void) {
    HuProfRspAwaitTime = (u32)osGetTime();
    while (osRecvMesg(&HuProfMesgQueue, NULL, 0) == 0)
        ;
}

s16 HuProfRecordSample(ProfSampleBuff *buffer, s32 red, s32 green, u32 blue) {

    if (buffer->sampleCount >= PROF_MAX_SAMPLES) {
        return -1;
    }

    buffer->startTimes[buffer->sampleCount] = (u32)osGetTime();
    buffer->colors[buffer->sampleCount] = (((((red << 8) & 0xF800) | ((green * 8) & 0x7C0) | ((blue >> 2) & 0x3E)) | 1) << 0x10) | (((red << 8) & 0xF800) | ((green * 8) & 0x7C0) | ((blue >> 2) & 0x3E) | 1);

    return buffer->sampleCount++;
}

OSTime HuProfRecordEnd(ProfSampleBuff *buffer, s16 sampleIdx) {

    if (sampleIdx >= 0) {
        buffer->endTimes[sampleIdx] = (u32)osGetTime();
    }

    return buffer->endTimes[sampleIdx] - buffer->startTimes[sampleIdx];
}

s16 HuProfCpuBegin(u8 red, u8 green, u8 blue) {
    return HuProfRecordSample(&HuProfCpuBuf, red, green, blue);
}

void HuProfCpuEnd(s16 sampleIdx) {
    HuProfRecordEnd(&HuProfCpuBuf, sampleIdx);
}

s16 HuProfRspBegin(u8 arg0, u8 arg1, u8 arg2) {
    s16 temp_s0;
    u32 temp_s3;

    temp_s3 = osSetIntMask(1U);
    temp_s0 = HuProfRecordSample(&HuProfRspBuf, arg0, arg1, arg2);
    osSetIntMask(temp_s3);
    return temp_s0;
}

void HuProfRspEnd(s16 sampleIdx) {
    u32 temp_s1;

    temp_s1 = osSetIntMask(1U);
    HuProfRecordEnd(&HuProfRspBuf, sampleIdx);
    osSetIntMask(temp_s1);
}

void HuProfFrameBegin(void) {
    u32 temp_v0;

    HuProfCpuSampleNum = 0;
    temp_v0 = osSetIntMask(1U);
    HuProfCpuBuf.unk0 = HuProfRspAwaitTime;
    osSetIntMask(temp_v0);
}

void HuProfFrameEnd(void) {
    u32 temp_s0;

    temp_s0 = osSetIntMask(1);
    bcopy(&HuProfCpuBuf, &HuProfCpuDispBuf, sizeof(ProfSampleBuff));
    osSetIntMask(temp_s0);
}

void HuProfRspReset(void) {
    HuProfRspSampleNum = 0;
    HuProfRspBuf.unk0 = HuProfRspAwaitTime;
}

void HuProfDummy(void) {
}

// profiler rendering code was stubbed out
Gfx *HuProfDraw(ProfSampleBuff *arg1, Gfx *arg2, s32 arg3) {
    return arg2;
}

extern OSMesgQueue scGraphicsTaskQueue;
extern u64 *gThread3Stack;
extern s32 gThreadOutStack;
extern s32 gThreadOutStackSize;
extern s32 gThreadYieldStack;

void HuProfDrawTask(void) {
    Gfx *gfx = HuProfGfxBuf;

    HuProfTaskDramStack = gThread3Stack;
    HuProfTaskYieldDataPtr = (u64 *)gThreadYieldStack;
    HuProfTaskOutputBuff = (u64 *)gThreadOutStack;
    HuProfTaskOutputBuffSize = (u64 *)gThreadOutStackSize;
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_FILL);
    gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
    gfx = HuProfDraw(&HuProfCpuDispBuf, gfx, 0);
    gfx = HuProfDraw(&HuProfRspBuf, gfx, 2);
    gDPFullSync(gfx++);
    gSPEndDisplayList(gfx++);
    osJamMesg(&scGraphicsTaskQueue, &HuProfTaskType, 0);
}
