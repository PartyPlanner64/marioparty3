#include "common.h"

/*
 * The factors used by the micros conversions below. They are loaded straight
 * out of .rodata, so each one is declared here and defined after the function
 * that uses it: gcc turns a constant whose value it knows into a `li.d`
 * immediate, which would move it into a constant pool of its own.
 */
static const f64 TIME_SCALE;
static const f64 TIME_ROUNDING;

/* The micros-to-frames conversion below works on its own copies of the factors. */
static const f64 FRAMES_TIME_SCALE;
static const f64 FRAMES_TIME_ROUNDING;

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

/* Returns every voice queued up on the lame list back to the free list. The
 * next pointer is re-read from the list head after every voice, because both
 * calls below move the node to a different list. */
void func_800782A0_main(ALSynth *drvr) {
    ALLink *link;

    for (link = drvr->pLameList.next; link != NULL; link = drvr->pLameList.next) {
        alUnlink(link);
        alLink(link, &drvr->pFreeList);
    }
}

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
    f32 frames = (f32)micros * drvr->outputRate / FRAMES_TIME_SCALE + FRAMES_TIME_ROUNDING;

    return (s32)frames & ~0xF;
}

static const f64 FRAMES_TIME_SCALE = 1000000.0;
static const f64 FRAMES_TIME_ROUNDING = 0.5;

/* Finds the client whose frame is due soonest, relative to the current sample
 * position, and returns the sample count that client is now scheduled for. */
s32 func_800783C8_main(ALSynth *drvr, ALPlayer **client) {
    ALPlayer *cur;
    s32 delta = 0x7FFFFFFF;

    *client = NULL;
    for (cur = drvr->head; cur != NULL; cur = cur->next) {
        if (cur->samplesLeft - drvr->curSamples < delta) {
            *client = cur;
            delta = cur->samplesLeft - drvr->curSamples;
        }
    }

    return (*client)->samplesLeft;
}
