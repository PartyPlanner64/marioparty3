#include "common.h"

void duelcall_Start(void);
void duelcall_Exec(void);
void duelcall_ObjectSetup(void);

OvlEntrypoint duelcall_ovlEntryTbl[] = {
    { 0, duelcall_Start },
    { 1, duelcall_Exec },
    { 2, duelcall_ObjectSetup },
    { -1, NULL }
};

void duelcall_Executor(void) {
    ovlEventCall(duelcall_ovlEntryTbl, omovlevtno);
}
