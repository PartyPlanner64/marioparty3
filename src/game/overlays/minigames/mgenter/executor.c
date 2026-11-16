#include "common.h"

void mgenter_ObjectSetup(void);
void mgenter_SkipObjectSetup(void);

OvlEntrypoint mgenter_ovlEntryTbl[] = {
    { 0, mgenter_ObjectSetup },
    { 1, mgenter_SkipObjectSetup },
    { -1, NULL }
};

void mgenter_Executor(void) {
    ovlEventCall(mgenter_ovlEntryTbl, omovlevtno);
}
