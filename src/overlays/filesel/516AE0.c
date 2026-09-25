#include "common.h"

extern OvlEntrypoint D_801127A0_filesel[];

void func_801059A0_filesel(void) {
    ovlEventCall(D_801127A0_filesel, omovlevtno);
}
