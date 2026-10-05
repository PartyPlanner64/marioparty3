#include "common.h"
#include "PR/sndp.h"

/* Filter message ids used to queue a control param onto a voice. */
enum {
    AL_FILTER_ADD_UPDATE = 3,
    AL_FILTER_SET_PITCH = 7
};

/* A sequence channel, holding the voice the synth reserved for it. */
typedef struct Unk709E0_Channel {
    char unk_00[0x08];
    PVoice *unk_08;
} Unk709E0_Channel;

ALParam *func_8006BBBC_main(void);
s32 func_8006A9C8_main(ALEnvMixer *e, s32 paramID, void *param);

void func_8006FDE0_main(Unk709E0_Channel *arg0, f32 arg1) {
    if (arg0->unk_08 != NULL) {
        ALParam *param = func_8006BBBC_main();

        if (param != NULL) {
            param->delta = D_800A2884_main->curSamples + arg0->unk_08->offset;
            param->type = AL_FILTER_SET_PITCH;
            param->data.f = arg1;
            param->next = NULL;

            func_8006A9C8_main(&arg0->unk_08->p.envmixer, AL_FILTER_ADD_UPDATE, param);
        }
    }
}
