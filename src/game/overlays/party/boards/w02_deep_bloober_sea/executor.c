#include "common_board.h"

void MB2_BoardInit(void);
void MB2_SaveInit(void);
void MB2_Create(void);
void MB2_BoardReload(void);
void MB2Ev_OpStarMapView(void);

OvlEntrypoint mb2_ovlEntryTbl[] = {
    { 0, MB2_BoardInit },
    { 1, MB2_SaveInit },
    { 2, MB2_Create },
    { 3, MB2_BoardReload },
    { 4, MB2Ev_OpStarMapView },
    { -1, NULL },
};

void MB2_Executor(void) {
    ovlEventCall(mb2_ovlEntryTbl, omovlevtno);
}
