#ifndef _N_SEQP_H_
#define _N_SEQP_H_

#include "PR/n_synthInternals.h"

/*
 * Private routines shared by the n_audio sequence player (n_seqplayer.c) and
 * compact sequence player (n_csplayer.c). The libultra name of each routine is
 * noted alongside the placeholder name it currently has in this project.
 */

#define KILL_TIME 50000 /* 50 ms */

/* __n_unmapVoice */
void func_80070F8C_main(N_ALSeqPlayer *seqp, N_ALVoice *voice);
/* __n_seqpReleaseVoice */
void func_80070FF0_main(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime deltaTime);
/* __n_voiceNeedsNoteKill */
char func_8007110C_main(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime killTime);
/* __n_mapVoice */
N_ALVoiceState *func_800711F0_main(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 channel);
/* __n_lookupVoice */
N_ALVoiceState *func_80071240_main(N_ALSeqPlayer *seqp, u8 key, u8 channel);
/* __n_lookupSoundQuick */
ALSound *func_80071294_main(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan);
/* __n_vsVol */
s16 func_80071368_main(N_ALVoiceState *vs, N_ALSeqPlayer *seqp);
/* __n_vsDelta */
ALMicroTime func_800713D8_main(N_ALVoiceState *vs, ALMicroTime t);
/* __n_vsPan */
ALPan func_800713F4_main(N_ALVoiceState *vs, N_ALSeqPlayer *seqp);
/* __n_initFromBank */
void func_80071438_main(N_ALSeqPlayer *seqp, ALBank *b);
/* __n_initChanState */
void func_800714E4_main(N_ALSeqPlayer *seqp);
/* __n_resetPerfChanState */
void func_80071548_main(N_ALSeqPlayer *seqp, s32 chan);
/* __n_setInstChanState */
void func_800715C8_main(N_ALSeqPlayer *seqp, ALInstrument *inst, s32 chan);
/* __n_seqpStopOsc */
void func_8007161C_main(N_ALSeqPlayer *seqp, N_ALVoiceState *vs);

/* Defined in the standard library (src/2.0L/audio/seq.c and cseq.c). */
char __alSeqNextDelta(ALSeq *seq, s32 *pDeltaTicks);
char __alCSeqNextDelta(ALCSeq *seq, s32 *pDeltaTicks);

#endif
