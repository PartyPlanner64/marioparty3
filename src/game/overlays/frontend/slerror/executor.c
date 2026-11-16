#include "common.h"

void slerror_ObjectSetup(void);
void slerror_ObjectSetupAlt(void);

OvlEntrypoint slerror_ovlEntryTbl[] = {
    { 0, slerror_ObjectSetup },
    { 1, slerror_ObjectSetupAlt },
    { -1, NULL }
};

void slerror_Executor(void) {
    ovlEventCall(slerror_ovlEntryTbl, omovlevtno);
}
