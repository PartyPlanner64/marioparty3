#include "common_duel.h"
#include "duel01.h"

void MBD1_BoardInit(void);
void MBD1_SaveInit(void);
void MBD1_Create(void);
void MBD1_BoardReload(void);

OvlEntrypoint mbd1_ovlEntryTbl[] = {
    { 0, MBD1_BoardInit },
    { 1, MBD1_SaveInit },
    { 2, MBD1_Create },
    { 3, MBD1_BoardReload },
    { -1, NULL }
};

void MBD1_Executor(void) {
    ovlEventCall(mbd1_ovlEntryTbl, omovlevtno);
}
