#ifndef _N_SEQP_H_
#define _N_SEQP_H_

#include "PR/n_synthInternals.h"

/*
 * Private routines shared by the n_audio sequence player (n_seqplayer.c) and
 * compact sequence player (n_csplayer.c).
 */

#define KILL_TIME 50000 /* 50 ms */

void __n_unmapVoice(N_ALSeqPlayer *seqp, N_ALVoice *voice);
void __n_seqpReleaseVoice(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime deltaTime);
char __n_voiceNeedsNoteKill(N_ALSeqPlayer *seqp, N_ALVoice *voice, ALMicroTime killTime);
N_ALVoiceState *__n_mapVoice(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 channel);
N_ALVoiceState *__n_lookupVoice(N_ALSeqPlayer *seqp, u8 key, u8 channel);
ALSound *__n_lookupSoundQuick(N_ALSeqPlayer *seqp, u8 key, u8 vel, u8 chan);
s16 __n_vsVol(N_ALVoiceState *vs, N_ALSeqPlayer *seqp);
ALMicroTime __n_vsDelta(N_ALVoiceState *vs, ALMicroTime t);
ALPan __n_vsPan(N_ALVoiceState *vs, N_ALSeqPlayer *seqp);
void __n_initFromBank(N_ALSeqPlayer *seqp, ALBank *b);
void __n_initChanState(N_ALSeqPlayer *seqp);
void __n_resetPerfChanState(N_ALSeqPlayer *seqp, s32 chan);
void __n_setInstChanState(N_ALSeqPlayer *seqp, ALInstrument *inst, s32 chan);
void __n_seqpStopOsc(N_ALSeqPlayer *seqp, N_ALVoiceState *vs);

/* Defined in the standard library (src/2.0L/audio/seq.c and cseq.c). */
char __alSeqNextDelta(ALSeq *seq, s32 *pDeltaTicks);
char __alCSeqNextDelta(ALCSeq *seq, s32 *pDeltaTicks);

#endif
