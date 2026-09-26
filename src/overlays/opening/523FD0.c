#include "common.h"

extern OvlEntrypoint D_80114B50_opening[];

void func_801059A0_opening(void) {
    ovlEventCall(D_80114B50_opening, omovlevtno);
}
