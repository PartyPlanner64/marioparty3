#include "common.h"
#include "PR/n_libaudio.h"

void n_alSynRemovePlayer(ALPlayer *client) {
    ALPlayer *thing;
    ALPlayer *prev = NULL;
    OSIntMask mask;

    if (n_syn->head != NULL) {
        mask = osSetIntMask(OS_IM_NONE);

        for (thing = n_syn->head; thing != NULL; thing = thing->next) {
            if (thing == client) {
                if (prev != NULL) {
                    prev->next = thing->next;
                } else {
                    n_syn->head = thing->next;
                }
                client->next = NULL;
                break;
            }
            prev = thing;
        }

        osSetIntMask(mask);
    }

    mask = osSetIntMask(OS_IM_NONE);

    if (n_syn->n_sndp == client) {
        n_syn->n_sndp = NULL;
    } else if (n_syn->n_seqp1 == client) {
        n_syn->n_seqp1 = NULL;
    } else if (n_syn->n_seqp2 == client) {
        n_syn->n_seqp2 = NULL;
    }

    osSetIntMask(mask);
}
