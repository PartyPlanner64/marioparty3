#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/ovlEvent.h"

s16 D_800A12B0_main = 0; // previous overlay index

void ovlEventCall(OvlEntrypoint *arg0, s16 arg1) {
    OvlEntrypoint *entry = arg0;

    for (; entry->index >= 0; entry++) {
        if (entry->index == arg1) {
            entry->fn();
        }
    }
}
