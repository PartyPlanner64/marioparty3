#include "common.h"

void boot_ObjectSetup(void);
void boot_SkipObjectSetup(void);

/* .data */
OvlEntrypoint boot_ovlEntryTbl[] = {
    { 0, boot_ObjectSetup },
    { 1, boot_SkipObjectSetup },
    { -1, NULL },
};

void boot_Executor(void) {
    ovlEventCall(boot_ovlEntryTbl, omovlevtno);
}
