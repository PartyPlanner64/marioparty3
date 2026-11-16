#include "common_duel.h"

void MBD10_BoardInit(void);
void MBD10_SaveInit(void);
void MBD10_Create(void);

OvlEntrypoint mbd10_ovlEntryTbl[] = {
    { 0, MBD10_BoardInit },
    { 1, MBD10_SaveInit },
    { 2, MBD10_Create },
    { -1, NULL }
};

void MBD10_Executor(void) {
    ovlEventCall(mbd10_ovlEntryTbl, omovlevtno);
}
