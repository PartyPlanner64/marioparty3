#include "common.h"

void storydebug_ObjectSetup(void);

OvlEntrypoint storydebug_ovlEntryTbl[] = {
    { 0, storydebug_ObjectSetup },
    { -1, NULL }
};

void storydebug_Executor(void) {
    ovlEventCall(storydebug_ovlEntryTbl, omovlevtno);
}
