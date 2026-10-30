#include "common.h"
#include "PR/synthInternals.h"

/*
 * Standard (non-n_audio) libultra sound player, from the libultra sndplayer.c
 * source. It is compiled with the game's default -O1 flags and linked among
 * the game objects rather than from the libultra archive. It appears unused,
 * since the game uses the n_audio sound player (n_sndplayer.c) instead.
 */

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define MIN_RATIO 0.0001

typedef enum {
    AL_SNDP_PLAY_EVT,
    AL_SNDP_STOP_EVT,
    AL_SNDP_PAN_EVT,
    AL_SNDP_VOL_EVT,
    AL_SNDP_PITCH_EVT,
    AL_SNDP_API_EVT,
    AL_SNDP_DECAY_EVT,
    AL_SNDP_END_EVT,
    AL_SNDP_FX_EVT
} ALSndpMsgType;

typedef struct {
    ALVoice voice;
    ALSound *sound; /* sound referenced here */
    s16 priority;
    f32 pitch; /* current playback pitch */
    s32 state; /* play state for this sound */
    s16 vol;   /* volume - combined with volume from bank */
    ALPan pan; /* pan - 0 = left, 127 = right */
    u8 fxMix;  /* wet/dry mix - 0 = dry, 127 = wet */
} ALSoundState;

typedef union {
    ALEvent msg;

    struct {
        s16 type;
        ALSoundState *state;
    } common;

    struct {
        s16 type;
        ALSoundState *state;
        s16 vol;
    } vol;

    struct {
        s16 type;
        ALSoundState *state;
        f32 pitch;
    } pitch;

    struct {
        s16 type;
        ALSoundState *state;
        ALPan pan;
    } pan;

    struct {
        s16 type;
        ALSoundState *state;
        u8 mix;
    } fx;
} ALSndpEvent;

ALMicroTime _sndpVoiceHandler(void *node);
void _handleEvent(ALSndPlayer *sndp, ALSndpEvent *event);
void _removeEvents(ALEventQueue *evtq, ALSoundState *state);
s32 _DivS32ByF32(s32 value, f32 divisor);

void alSndpNew(ALSndPlayer *sndp, ALSndpConfig *c) {
    u8 *ptr;
    ALEvent evt;
    ALSoundState *sState;
    u32 i;

    /*
     * Init member variables
     */
    sndp->maxSounds = c->maxSounds;
    sndp->target = -1;
    sndp->frameTime = AL_USEC_PER_FRAME; /* time between API events */
    sState = alHeapAlloc(c->heap, 1, c->maxSounds * sizeof(ALSoundState));
    sndp->sndState = sState;

    for (i = 0; i < c->maxSounds; i++) {
        sState[i].sound = NULL;
    }

    /*
     * init the event queue
     */
    ptr = alHeapAlloc(c->heap, 1, c->maxEvents * sizeof(ALEventListItem));
    alEvtqNew(&sndp->evtq, (ALEventListItem *)ptr, c->maxEvents);

    /*
     * add ourselves to the driver
     */
    sndp->drvr = &alGlobals->drvr;
    sndp->node.next = NULL;
    sndp->node.handler = _sndpVoiceHandler;
    sndp->node.clientData = sndp;
    alSynAddPlayer(sndp->drvr, &sndp->node);

    /*
     * Start responding to API events
     */
    evt.type = AL_SNDP_API_EVT;
    alEvtqPostEvent(&sndp->evtq, &evt, sndp->frameTime);
    sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
}

/*************************************************************
 * Sound Player private routines
 *************************************************************/
ALMicroTime _sndpVoiceHandler(void *node) {
    ALSndPlayer *sndp = (ALSndPlayer *)node;
    ALSndpEvent evt;

    do {
        switch (sndp->nextEvent.type) {
            case AL_SNDP_API_EVT:
                evt.common.type = AL_SNDP_API_EVT;
                evt.common.state = (ALSoundState *)-1;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
                break;

            default:
                _handleEvent(sndp, (ALSndpEvent *)&sndp->nextEvent);
                break;
        }
        sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);
    } while (sndp->nextDelta == 0);

    sndp->curTime += sndp->nextDelta;
    return sndp->nextDelta;
}

void _handleEvent(ALSndPlayer *sndp, ALSndpEvent *event) {
    ALVoiceConfig vc;
    ALSound *snd;
    ALVoice *voice;
    ALPan pan;
    f32 pitch;
    ALSndpEvent evt;
    ALMicroTime delta;
    s16 vol;
    s16 tmp;
    s32 vtmp;
    ALSoundState *state;

    state = event->common.state;
    snd = state->sound;

    switch (event->msg.type) {
        case AL_SNDP_PLAY_EVT:
            if (state->state != AL_STOPPED || snd == NULL) {
                return;
            }

            vc.fxBus = 0; /* effect buss 0 */
            vc.priority = state->priority;
            vc.unityPitch = 0;

            voice = &state->voice;
            alSynAllocVoice(sndp->drvr, voice, &vc);

            vol = (s16)((s32)snd->envelope->attackVolume * state->vol / AL_VOL_FULL);
            tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
            tmp = MAX(tmp, AL_PAN_LEFT);
            pan = (ALPan)MIN(tmp, AL_PAN_RIGHT);
            pitch = state->pitch;
            delta = snd->envelope->attackTime;

            alSynStartVoice(sndp->drvr, voice, snd->wavetable);
            state->state = AL_PLAYING;

            alSynSetPan(sndp->drvr, voice, pan);
            alSynSetVol(sndp->drvr, voice, vol, delta);
            alSynSetPitch(sndp->drvr, voice, pitch);
            alSynSetFXMix(sndp->drvr, voice, state->fxMix);

            evt.common.type = AL_SNDP_DECAY_EVT;
            evt.common.state = state;
            delta = _DivS32ByF32(snd->envelope->attackTime, state->pitch);
            alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            break;

        case AL_SNDP_STOP_EVT:
            if (state->state != AL_PLAYING || snd == NULL) {
                return;
            }

            delta = _DivS32ByF32(snd->envelope->releaseTime, state->pitch);
            alSynSetVol(sndp->drvr, &state->voice, 0, delta);

            if (delta) {
                evt.common.type = AL_SNDP_END_EVT;
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
                state->state = AL_STOPPING;
            } else {
                /* note: this code is repeated in AL_SNDP_END_EVT */
                alSynStopVoice(sndp->drvr, &state->voice);
                alSynFreeVoice(sndp->drvr, &state->voice);
                _removeEvents(&sndp->evtq, state);
                state->state = AL_STOPPED;
            }
            break;

        case AL_SNDP_PAN_EVT:
            state->pan = event->pan.pan;
            if (state->state == AL_PLAYING && snd != NULL) {
                tmp = state->pan - AL_PAN_CENTER + snd->samplePan;
                tmp = MAX(tmp, AL_PAN_LEFT);
                pan = (ALPan)MIN(tmp, AL_PAN_RIGHT);
                alSynSetPan(sndp->drvr, &state->voice, pan);
            }
            break;

        case AL_SNDP_PITCH_EVT:
            /* Limit the pitch to a practical value even though we only need */
            /* to limit it to a non-zero number to avoid divide by zero. */
            if ((state->pitch = event->pitch.pitch) < MIN_RATIO) {
                state->pitch = MIN_RATIO;
            }

            if (state->state == AL_PLAYING) {
                alSynSetPitch(sndp->drvr, &state->voice, state->pitch);
            }
            break;

        case AL_SNDP_FX_EVT:
            state->fxMix = event->fx.mix;
            if (state->state == AL_PLAYING) {
                alSynSetFXMix(sndp->drvr, &state->voice, state->fxMix);
            }
            break;

        case AL_SNDP_VOL_EVT:
            state->vol = event->vol.vol;
            if (state->state == AL_PLAYING && snd != NULL) {
                vtmp = snd->envelope->decayVolume * state->vol / AL_VOL_FULL;
                alSynSetVol(sndp->drvr, &state->voice, (s16)vtmp, 1000);
            }
            break;

        case AL_SNDP_DECAY_EVT:
            /*
             * The voice has theoretically reached its attack velocity,
             * set up callback for release envelope - except for a looped sound
             */
            if (snd->envelope->decayTime != -1) {
                vtmp = snd->envelope->decayVolume * state->vol / AL_VOL_FULL;
                delta = _DivS32ByF32(snd->envelope->decayTime, state->pitch);
                alSynSetVol(sndp->drvr, &state->voice, (s16)vtmp, delta);
                evt.common.type = AL_SNDP_STOP_EVT;
                evt.common.state = state;
                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, delta);
            }
            break;

        case AL_SNDP_END_EVT:
            /* note: this code is repeated in AL_SNDP_STOP_EVT */
            alSynStopVoice(sndp->drvr, &state->voice);
            alSynFreeVoice(sndp->drvr, &state->voice);
            _removeEvents(&sndp->evtq, state);
            state->state = AL_STOPPED;
            break;

        default:
            break;
    }
}

void _removeEvents(ALEventQueue *evtq, ALSoundState *state) {
    ALLink *thisNode;
    ALLink *nextNode;
    ALEventListItem *thisItem;
    ALEventListItem *nextItem;
    ALSndpEvent *thisEvent;
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    thisNode = evtq->allocList.next;
    while (thisNode != NULL) {
        nextNode = thisNode->next;
        thisItem = (ALEventListItem *)thisNode;
        nextItem = (ALEventListItem *)nextNode;
        thisEvent = (ALSndpEvent *)&thisItem->evt;
        if (thisEvent->common.state == state) {
            if (nextItem != NULL) {
                nextItem->delta += thisItem->delta;
            }
            alUnlink(thisNode);
            alLink(thisNode, &evtq->freeList);
        }
        thisNode = nextNode;
    }

    osSetIntMask(mask);
}

s32 _DivS32ByF32(s32 value, f32 divisor) {
    f64 ratio = value / divisor;
    return ratio > 2147483647.0 ? 0x7FFFFFFF : (s32)ratio;
}
