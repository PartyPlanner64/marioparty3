#include "common.h"

/*
 * The two factors used by the micros-to-samples conversion below. They are
 * loaded out of .rodata, so they are declared here and defined at the bottom
 * of the file: gcc turns a constant whose value it knows into a `li.d`
 * immediate, which would move them into a 16-byte-aligned pool.
 */
static const f64 TIME_SCALE;
static const f64 TIME_ROUNDING;

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

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_8007837C_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/audio/synthesizer", func_800783C8_main);

INCLUDE_RODATA("asm/nonmatchings/2.0L/audio/synthesizer", D_800A8518_main);
