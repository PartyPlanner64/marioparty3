#include "common.h"

extern OvlEntrypoint D_8010F270_modesel[];

void func_801059A0_modesel(void) {
    ovlEventCall(D_8010F270_modesel, omovlevtno);
}
