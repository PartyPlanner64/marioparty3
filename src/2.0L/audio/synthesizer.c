#include "common.h"

/*
 * The factors used by the micros conversions below. They are loaded straight
 * out of .rodata, so each one is declared here and defined after the function
 * that uses it: gcc turns a constant whose value it knows into a `li.d`
 * immediate, which would move it into a constant pool of its own.
 */
static const f64 TIME_SCALE;
static const f64 TIME_ROUNDING;

/*
 * The micros-to-frames conversion below works on its own copy of the scale
 * factor, and adds the 0.5 rounding constant that is still assembled in from
 * the original rodata at the bottom of this file.
 */
static const f64 FRAMES_TIME_SCALE;
extern f64 D_800A8518_main;

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", alSynNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_800780AC_main);

ALParam *func_8007825C_main(void) {
    ALParam *param = NULL;

    if (alGlobals->drvr.paramList != NULL) {
        param = alGlobals->drvr.paramList;
        alGlobals->drvr.paramList = param->next;
        param->next = NULL;
    }

    return param;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_80078288_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_800782A0_main);

void func_800782F4_main(ALSynth *drvr, ALLink *link) {
    alUnlink(link);
    alLink(link, &drvr->pLameList);
}

s32 func_80078334_main(ALSynth *drvr, s32 micros) {
    /* The 0.5 compensates for the average effect of the truncation error made
     * when the float result is cast to an int. */
    f32 samples = (f32)micros * drvr->outputRate / TIME_SCALE + TIME_ROUNDING;

    return samples;
}

static const f64 TIME_SCALE = 1000000.0;
static const f64 TIME_ROUNDING = 0.5;

/* Like the conversion above, but the frames are always played back in groups of
 * 16, so the frame count is rounded down to a multiple of 16. */
s32 func_8007837C_main(ALSynth *drvr, s32 micros) {
    f32 frames = (f32)micros * drvr->outputRate / FRAMES_TIME_SCALE + D_800A8518_main;

    return (s32)frames & ~0xF;
}

static const f64 FRAMES_TIME_SCALE = 1000000.0;

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_800783C8_main);

INCLUDE_RODATA("asm/nonmatchings/2.0L/audio/synthesizer", D_800A8518_main);
