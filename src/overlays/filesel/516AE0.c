#include "common.h"

void func_80105BC0_filesel(void);

OvlEntrypoint D_801127A0_filesel[] = {
    { 0, func_80105BC0_filesel },
    { -1, NULL },
};

void func_801059A0_filesel(void) {
    ovlEventCall(D_801127A0_filesel, omovlevtno);
}
