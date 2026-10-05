#include "common.h"
#include "PR/sndp.h"

/* Filter message ids used to queue a control param onto a voice. */
enum {
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_START_VOICE = 14
};

/* A sequence channel, holding the voice the synth reserved for it. */
typedef struct Unk70B20_Channel {
    char unk_00[0x08];
    PVoice *unk_08;
    char unk_0C[0x0E];
    u16 unk_1A;
} Unk70B20_Channel;

/* The control param that starts a voice playing from a wave table. */
typedef struct Unk70B20_StartParam {
    ALParam *next;
    s32 delta;
    s16 type;
    s16 unity;
    ALWaveTable *wave;
} Unk70B20_StartParam;

ALParam *func_8006BBBC_main(void);
s32 func_8006A9C8_main(ALEnvMixer *e, s32 paramID, void *param);

void func_8006FF20_main(Unk70B20_Channel *arg0, ALWaveTable *arg1) {
    if (arg0->unk_08 != NULL) {
        Unk70B20_StartParam *param = (Unk70B20_StartParam *)func_8006BBBC_main();

        if (param != NULL) {
            param->delta = D_800A2884_main->curSamples + arg0->unk_08->offset;
            param->type = AL_FILTER_START_VOICE;
            param->wave = arg1;
            param->next = NULL;
            param->unity = arg0->unk_1A;

            func_8006A9C8_main(&arg0->unk_08->p.envmixer, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
