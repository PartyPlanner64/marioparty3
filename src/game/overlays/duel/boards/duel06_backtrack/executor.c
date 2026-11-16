#include "common_duel.h"

void MBD6_BoardInit(void);
void MBD6_SaveInit(void);
void MBD6_Create(void);
void MBD6_BoardReload(void);

OvlEntrypoint mbd6_ovlEntryTbl[] = {
    { 0, MBD6_BoardInit },
    { 1, MBD6_SaveInit },
    { 2, MBD6_Create },
    { 3, MBD6_BoardReload },
    { -1, NULL }
};

void MBD6_Executor(void) {
    ovlEventCall(mbd6_ovlEntryTbl, omovlevtno);
}
