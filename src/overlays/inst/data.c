#include "inst.h"

extern const char D_8010DA24_inst[];
extern const char D_8010DA34_inst[];
extern const char D_8010DA44_inst[];
extern const char D_8010DA54_inst[];
extern const char D_8010DA64_inst[];
extern const char D_8010DA74_inst[];
extern const char D_8010DA84_inst[];
extern const char D_8010DA94_inst[];
extern const char D_8010DAA4_inst[];
extern const char D_8010DAB0_inst[];
extern const char D_8010DABC_inst[];
extern const char D_8010DAC8_inst[];

s8 D_8010D400_inst[4] = {0, 1, 2, 3};
s8 D_8010D404_inst = 0;
s8 D_8010D405_inst = 0;
s8 D_8010D406_inst = 0;
s8 D_8010D407_inst = 0;
s8 D_8010D408_inst = 0;
s8 D_8010D409_inst = 0;
s8 D_8010D40A_inst = 0;
s8 D_8010D40B_inst = 0;
s8 D_8010D40C_inst[5] = {0};
s8 D_8010D411_inst = 0;
f32 D_8010D414_inst = 45.0f;
Vec D_8010D418_inst = {0.0f, 0.0f, 0.0f};
Vec D_8010D424_inst = {0.0f, 0.0f, 0.0f};
Vec D_8010D430_inst = {0.0f, 1.0f, -0.000001f};
s32 D_8010D43C_inst = 0;
s32 D_8010D440_inst = 0;
Vec D_8010D444_inst[4] = {
    {70.0f, 560.0f, 1210.0f},
    {0.0f, 560.0f, 1210.0f},
    {0.0f, 470.0f, 830.0f},
    {67.5f, 300.0f, 537.5f},
};
Vec D_8010D474_inst[4] = {
    {70.0f, 0.0f, -210.0f},
    {0.0f, 0.0f, -210.0f},
    {0.0f, 0.0f, -10.0f},
    {67.5f, 50.0f, 37.5f},
};
s32 D_8010D4A4_inst = 0;
s8 D_8010D4A8_inst = 0;
u32 D_8010D4AC_inst = 0;
u8 D_8010D4B0_inst[8] = {0, 1, 4, 5, 8, 10, 12, 14};
u8 D_8010D4B8_inst[8] = {1, 2, 3, 6, 7, 9, 13, 11};

/* The records have varying node counts and share the InstModelHooks prefix. */
InstModelHooks *D_8010D4C0_inst[][2] = {
    {(InstModelHooks *)&D_8010D770_inst, (InstModelHooks *)&D_8010D7A4_inst},
    {(InstModelHooks *)&D_8010D7B0_inst, (InstModelHooks *)&D_8010D7E4_inst},
    {(InstModelHooks *)&D_8010D7EC_inst, (InstModelHooks *)&D_8010D820_inst},
    {(InstModelHooks *)&D_8010D828_inst, (InstModelHooks *)&D_8010D85C_inst},
    {(InstModelHooks *)&D_8010D864_inst, (InstModelHooks *)&D_8010D880_inst},
    {(InstModelHooks *)&D_8010D888_inst, (InstModelHooks *)&D_8010D89C_inst},
    {(InstModelHooks *)&D_8010D888_inst, (InstModelHooks *)&D_8010D89C_inst},
    {(InstModelHooks *)&D_8010D8DC_inst, (InstModelHooks *)&D_8010D8EC_inst},
    {(InstModelHooks *)&D_8010D8F4_inst, (InstModelHooks *)&D_8010D904_inst},
};

s32 D_8010D508_inst = 0;
f32 D_8010D50C_inst = 0.0f;
s32 D_8010D510_inst = 0;
/* Unused initialized storage between the per-object state blocks. */
s32 D_8010D514_inst[3] = {0};
s32 D_8010D520_inst = 0;
s32 D_8010D524_inst = 0;
s32 D_8010D528_inst[2] = {0};
s32 D_8010D530_inst = 0;
s32 D_8010D534_inst = 0;
s32 D_8010D538_inst[2] = {0};
s32 D_8010D540_inst = 0;
s32 D_8010D544_inst = 0;
s32 D_8010D548_inst[2] = {0};
s8 D_8010D550_inst = 0;
s8 D_8010D551_inst = 0;
u8 D_8010D554_inst[4] = {0};
s32 D_8010D558_inst = 0;
const char *D_8010D55C_inst[8] = {
    D_8010DA94_inst, D_8010DA84_inst, D_8010DA74_inst, D_8010DA64_inst,
    D_8010DA54_inst, D_8010DA44_inst, D_8010DA34_inst, D_8010DA24_inst,
};
s32 D_8010D57C_inst[4] = {0x17002A, 0x17002B, 0x17002C, 0x17002D};
const char *D_8010D58C_inst[4] = {D_8010DAC8_inst, D_8010DABC_inst, D_8010DAB0_inst, D_8010DAA4_inst};
s32 D_8010D59C_inst = 0;
s32 D_8010D5A0_inst = 0;
s32 D_8010D5A4_inst[3] = {0};
s8 D_8010D5B0_inst = 0;
s8 D_8010D5B1_inst = 0;
s32 D_8010D5B4_inst = 0;
s32 D_8010D5B8_inst = -64;
s32 D_8010D5BC_inst = 0;
