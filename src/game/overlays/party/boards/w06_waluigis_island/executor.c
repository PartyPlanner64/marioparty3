#include "common_board.h"

void MB6_BoardInit(void);
void MB6_SaveInit(void);
void MB6_Create(void);
void MB6_BoardReload(void);
void MB6Ev_OpStarMapView(void);

OvlEntrypoint mb6_ovlEntryTbl[] = {
    { 0, MB6_BoardInit },
    { 1, MB6_SaveInit },
    { 2, MB6_Create },
    { 3, MB6_BoardReload },
    { 4, MB6Ev_OpStarMapView },
    { -1, NULL },
};

void MB6_Executor(void) {
    ovlEventCall(mb6_ovlEntryTbl, omovlevtno);
}
