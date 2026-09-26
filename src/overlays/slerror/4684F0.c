#include "common.h"

extern OvlEntrypoint D_80105F20_slerror[];

void func_801059A0_slerror(void) {
    ovlEventCall(D_80105F20_slerror, omovlevtno);
}
