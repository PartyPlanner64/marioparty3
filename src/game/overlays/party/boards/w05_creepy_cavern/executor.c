#include "common_board.h"

void MB5_BoardInit(void);
void MB5_SaveInit(void);
void MB5_Create(void);
void MB5_BoardReload(void);
void MB5Ev_OpStarMapView(void);

OvlEntrypoint mb5_ovlEntryTbl[] = {
    { 0, MB5_BoardInit },
    { 1, MB5_SaveInit },
    { 2, MB5_Create },
    { 3, MB5_BoardReload },
    { 4, MB5Ev_OpStarMapView },
    { -1, NULL },
};

void MB5_Executor(void) {
    ovlEventCall(mb5_ovlEntryTbl, omovlevtno);
}
