#include "common.h"

void func_801059D0_mgenter(void);
void func_80105C60_mgenter(void);

OvlEntrypoint D_80109A80_mgenter[] = {
    { 0, func_801059D0_mgenter },
    { 1, func_80105C60_mgenter },
    { -1, NULL }
};

void func_801059A0_mgenter(void) {
    ovlEventCall(D_80109A80_mgenter, omovlevtno);
}
