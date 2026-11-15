#include "common.h"

void opTitleObjectSetup(void);
void func_80105C2C_opening(void);
void opDemoObjectSetup(void);

OvlEntrypoint D_80114B50_opening[] = {
    { 0, opTitleObjectSetup },
    { 1, func_80105C2C_opening },
    { 2, opDemoObjectSetup },
    { -1, NULL }
};

void func_801059A0_opening(void) {
    ovlEventCall(D_80114B50_opening, omovlevtno);
}
