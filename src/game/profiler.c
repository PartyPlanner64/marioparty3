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

OSTime func_8004D638_main(ProfSampleBuff *buffer, s16 sampleIdx);

extern u8 D_8008F1C0_main;
static ProfSampleBuff D_800B23E0_main;
// Global so undefined_syms.txt can alias their sampleCount fields, and aligned
// to match the placement they get as statics.
ProfSampleBuff D_800B2468_main BSS ALIGNED(8);
ProfSampleBuff D_800B24F0_main BSS ALIGNED(8);
// sampleCount fields of the buffers above (see undefined_syms.txt). The
// original resets them through these separate symbols.
extern s16 D_800B246C_main;
extern s16 D_800B24F4_main;
static u32 D_800B2574_main;
static OSMesgQueue D_800B2578_main;
static OSMesg D_800B2590_main[3];
static u32 D_800B259C_main; // unreferenced
// RSP task fields (an OSTask layout followed by its completion queue and message)
static u32 D_800B25A0_main; // type
static u32 D_800B25A4_main; // flags
static u64 *D_800B25A8_main; // ucode_boot
static u32 D_800B25AC_main; // ucode_boot_size
static u64 *D_800B25B0_main; // ucode
static u32 D_800B25B4_main; // ucode_size
static u64 *D_800B25B8_main; // ucode_data
static u32 D_800B25BC_main; // ucode_data_size
static u64 *D_800B25C0_main; // dram_stack
static u32 D_800B25C4_main; // dram_stack_size
static u64 *D_800B25C8_main; // output_buff
static u64 *D_800B25CC_main; // output_buff_size
static u64 *D_800B25D0_main; // data_ptr
static u32 D_800B25D4_main; // data_size
static u64 *D_800B25D8_main; // yield_data_ptr
static u32 D_800B25DC_main; // yield_data_size
static OSMesgQueue *D_800B25E0_main;
static OSMesg D_800B25E4_main;
static Gfx D_800B25F0_main[0x80];

extern s32 *gUCodeAddresses;

void HuProfInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    D_800B2468_main.config.unk0 = arg1;
    D_800B2468_main.config.unk2 = arg2;
    D_800B24F0_main.config.unk0 = arg3;
    D_800B24F0_main.config.unk2 = arg4;
    D_800B25E0_main = &D_800B2578_main;
    D_800B25E4_main = 0;
    D_800B25A0_main = 1;
    D_800B25A4_main = 2;
    D_800B25A8_main = (u64 *)rspbootTextStart;
    D_800B25AC_main = (u32)rspbootTextEnd - (u32)rspbootTextStart;
    D_800B25B4_main = 0x1000;
    D_800B25BC_main = 0x800;
    D_800B25C4_main = 0x400;
    D_800B25D0_main = (u64 *)D_800B25F0_main;
    D_800B25D4_main = 0;
    D_800B25DC_main = 0xC00;
    D_800B25B0_main = (u64 *)gUCodeAddresses[arg0 * 2];
    D_800B25B8_main = (u64 *)gUCodeAddresses[(arg0 * 2) | 1];
    osCreateMesgQueue(&D_800B2578_main, D_800B2590_main, ARRAY_COUNT(D_800B2590_main));
}

void HuProfRecordAwaitRsp(void) {
    D_800B2574_main = (u32)osGetTime();
    while (osRecvMesg(&D_800B2578_main, NULL, 0) == 0)
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

OSTime func_8004D638_main(ProfSampleBuff *buffer, s16 sampleIdx) {

    if (sampleIdx >= 0) {
        buffer->endTimes[sampleIdx] = (u32)osGetTime();
    }

    return buffer->endTimes[sampleIdx] - buffer->startTimes[sampleIdx];
}

s16 func_8004D6AC_main(u8 red, u8 green, u8 blue) {
    return HuProfRecordSample(&D_800B2468_main, red, green, blue);
}

void func_8004D6E8_main(s16 sampleIdx) {
    func_8004D638_main(&D_800B2468_main, sampleIdx);
}

s16 func_8004D710_main(u8 arg0, u8 arg1, u8 arg2) {
    s16 temp_s0;
    u32 temp_s3;

    temp_s3 = osSetIntMask(1U);
    temp_s0 = HuProfRecordSample(&D_800B24F0_main, arg0, arg1, arg2);
    osSetIntMask(temp_s3);
    return temp_s0;
}

void func_8004D788_main(s16 sampleIdx) {
    u32 temp_s1;

    temp_s1 = osSetIntMask(1U);
    func_8004D638_main(&D_800B24F0_main, sampleIdx);
    osSetIntMask(temp_s1);
}

void func_8004D7D8_main(void) {
    u32 temp_v0;

    D_800B246C_main = 0;
    temp_v0 = osSetIntMask(1U);
    D_800B2468_main.unk0 = D_800B2574_main;
    osSetIntMask(temp_v0);
}

void func_8004D814_main(void) {
    u32 temp_s0;

    temp_s0 = osSetIntMask(1);
    bcopy(&D_800B2468_main, &D_800B23E0_main, sizeof(ProfSampleBuff));
    osSetIntMask(temp_s0);
}

void func_8004D85C_main(void) {
    D_800B24F4_main = 0;
    D_800B24F0_main.unk0 = D_800B2574_main;
}

void func_8004D878_main(void) {
}

// profiler rendering code was stubbed out
Gfx *func_8004D880_main(ProfSampleBuff *arg1, Gfx *arg2, s32 arg3) {
    return arg2;
}

extern OSMesgQueue D_800CC3C0_main;
extern u64 *gThread3Stack;
extern s32 gThreadOutStack;
extern s32 gThreadOutStackSize;
extern s32 gThreadYieldStack;

void func_8004D888_main(void) {
    Gfx *gfx = D_800B25F0_main;

    D_800B25C0_main = gThread3Stack;
    D_800B25D8_main = (u64 *)gThreadYieldStack;
    D_800B25C8_main = (u64 *)gThreadOutStack;
    D_800B25CC_main = (u64 *)gThreadOutStackSize;
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_FILL);
    gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
    gfx = func_8004D880_main(&D_800B23E0_main, gfx, 0);
    gfx = func_8004D880_main(&D_800B24F0_main, gfx, 2);
    gDPFullSync(gfx++);
    gSPEndDisplayList(gfx++);
    osJamMesg(&D_800CC3C0_main, &D_800B25A0_main, 0);
}
