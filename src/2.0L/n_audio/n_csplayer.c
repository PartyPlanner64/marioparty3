#include "common.h"
#include "PR/n_libaudio.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", n_alCSPNew);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", __n_CSPVoiceHandler);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", __n_CSPHandleNextSeqEvent);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", __n_CSPHandleMIDIMsg);

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", __n_CSPHandleMetaMsg);

void __n_CSPRepostEvent(ALEventQueue *evtq, N_ALEventListItem *item) {
    ALLink *cur;
    ALLink *next;
    OSIntMask mask;

    mask = osSetIntMask(1);

    for (cur = &evtq->allocList; cur != NULL; cur = cur->next) {
        next = cur->next;

        if (next == NULL) {
            alLink(&item->node, cur);
            break;
        }
        if (item->delta < ((N_ALEventListItem *)next)->delta) {
            ((N_ALEventListItem *)next)->delta -= item->delta;
            alLink(&item->node, cur);
            break;
        }
        item->delta -= ((N_ALEventListItem *)next)->delta;
    }

    osSetIntMask(mask);
}

void __n_setUsptFromTempo(N_ALCSPlayer *seqp, f32 scale) {
    if (seqp->target != NULL) {
        seqp->uspt = (s32)(scale * seqp->target->qnpt);
    } else {
        seqp->uspt = 0x1E8;
    }
}

INCLUDE_ASM("asm/nonmatchings/2.0L/n_audio/n_csplayer", __n_CSPPostNextSeqEvent);
