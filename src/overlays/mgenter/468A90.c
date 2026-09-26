#include "common.h"

extern OvlEntrypoint D_80109A80_mgenter[];

void func_801059A0_mgenter(void) {
    ovlEventCall(D_80109A80_mgenter, omovlevtno);
}
