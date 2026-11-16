#include "common.h"

void filesel_ObjectSetup(void);

OvlEntrypoint filesel_ovlEntryTbl[] = {
    { 0, filesel_ObjectSetup },
    { -1, NULL },
};

void filesel_Executor(void) {
    ovlEventCall(filesel_ovlEntryTbl, omovlevtno);
}
