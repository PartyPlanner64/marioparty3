#include "common_duel.h"

void MBD2_BoardInit(void);
void MBD2_SaveInit(void);
void MBD2_Create(void);
void MBD2_BoardReload(void);

OvlEntrypoint mbd2_ovlEntryTbl[] = {
    { 0, MBD2_BoardInit },
    { 1, MBD2_SaveInit },
    { 2, MBD2_Create },
    { 3, MBD2_BoardReload },
    { -1, NULL }
};

void MBD2_Executor(void) {
    ovlEventCall(mbd2_ovlEntryTbl, omovlevtno);
}
