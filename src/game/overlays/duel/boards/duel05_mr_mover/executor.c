#include "common_duel.h"

void MBD5_BoardInit(void);
void MBD5_SaveInit(void);
void MBD5_Create(void);
void MBD5_BoardReload(void);

OvlEntrypoint mbd5_ovlEntryTbl[] = {
    { 0, MBD5_BoardInit },
    { 1, MBD5_SaveInit },
    { 2, MBD5_Create },
    { 3, MBD5_BoardReload },
    { -1, NULL }
};

void MBD5_Executor(void) {
    ovlEventCall(mbd5_ovlEntryTbl, omovlevtno);
}
