#ifndef _GAME_PRINTFUNC_H
#define _GAME_PRINTFUNC_H

#include "ultra64.h"

#define FONT_COLOR_BLACK 0
#define FONT_COLOR_DARK_BLUE 1
#define FONT_COLOR_DARK_RED 2
#define FONT_COLOR_DARK_MAGENTA 3
#define FONT_COLOR_DARK_GREEN 4
#define FONT_COLOR_DARK_CYAN 5
#define FONT_COLOR_DARK_YELLOW 6
#define FONT_COLOR_GRAY 7
#define FONT_COLOR_TRANSLUCENT_GRAY 8
#define FONT_COLOR_BLUE 9
#define FONT_COLOR_RED 10
#define FONT_COLOR_MAGENTA 11
#define FONT_COLOR_GREEN 12
#define FONT_COLOR_CYAN 13
#define FONT_COLOR_YELLOW 14
#define FONT_COLOR_WHITE 15

// filled rect behind debug text
typedef struct Unk_D_800CC440 {
    u16 unk_00; // active
    s32 unk_04; // left
    s32 unk_08; // top
    s32 unk_0C; // right
    s32 unk_10; // bottom
    u32 unk_14; // color
} Unk_D_800CC440;

typedef struct Unk_D_800CE1DC {
    u8 unk_00; // red
    u8 unk_01; // green
    u8 unk_02; // blue
    s8 unk_03; // red speed
    s8 unk_04; // green speed
    s8 unk_05; // blue speed
    u8 unk_06; // red max
    u8 unk_07; // green max
    u8 unk_08; // blue max
    u8 unk_09; // red min
    u8 unk_0A; // green min
    u8 unk_0B; // blue min
} Unk_D_800CE1DC;

extern s32 fontcolor;
extern Unk_D_800CC440 D_800CC440_main[4];
extern Unk_D_800CE1DC D_800CE1DC_main;

s16 printWin(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8004DEC8_main(s16 arg0);
void func_8004DF10_main(void);
void func_8004DF4C_main(u8 arg0, u8 arg1, u8 arg2);
void func_8004DF7C_main(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
void func_8004DFC0_main(void);
void func_8004DFD8_main(void);

#endif
