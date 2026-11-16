#include "common_duel.h"

void MBD3_BoardInit(void);
void MBD3_SaveInit(void);
void MBD3_Create(void);
void MBD3_BoardReload(void);

OvlEntrypoint mbd3_ovlEntryTbl[] = {
    { 0, MBD3_BoardInit },
    { 1, MBD3_SaveInit },
    { 2, MBD3_Create },
    { 3, MBD3_BoardReload },
    { -1, NULL }
};

void MBD3_Executor(void) {
    ovlEventCall(mbd3_ovlEntryTbl, omovlevtno);
}
