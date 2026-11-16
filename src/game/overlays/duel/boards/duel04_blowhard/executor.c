#include "common_duel.h"

void MBD4_BoardInit(void);
void MBD4_SaveInit(void);
void MBD4_Create(void);
void MBD4_BoardReload(void);

OvlEntrypoint mbd4_ovlEntryTbl[] = {
    { 0, MBD4_BoardInit },
    { 1, MBD4_SaveInit },
    { 2, MBD4_Create },
    { 3, MBD4_BoardReload },
    { -1, NULL }
};

void MBD4_Executor(void) {
    ovlEventCall(mbd4_ovlEntryTbl, omovlevtno);
}
