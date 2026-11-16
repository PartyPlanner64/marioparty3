#include "common_board.h"

void MB10_BoardInit(void);
void MB10_SaveInit(void);
void MB10_Create(void);

OvlEntrypoint mb10_ovlEntryTbl[] = {
    { 0, MB10_BoardInit },
    { 1, MB10_SaveInit },
    { 2, MB10_Create },
    { -1, NULL },
};

void MB10_Executor(void) {
    ovlEventCall(mb10_ovlEntryTbl, omovlevtno);
}
