#include "common.h"

void boardcall_Start(void);
void boardcall_Exec(void);
void boardcall_ObjectSetup(void);

OvlEntrypoint boardcall_ovlEntryTbl[] = {
    { 0, boardcall_Start },
    { 1, boardcall_Exec },
    { 2, boardcall_ObjectSetup },
    { -1, NULL },
};

void boardcall_Executor(void) {
    ovlEventCall(boardcall_ovlEntryTbl, omovlevtno);
}
