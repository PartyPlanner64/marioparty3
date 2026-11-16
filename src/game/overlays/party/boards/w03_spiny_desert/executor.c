#include "common_board.h"

void MB3_BoardInit(void);
void MB3_SaveInit(void);
void MB3_Create(void);
void MB3_BoardReload(void);
void MB3Ev_OpStarMapView(void);

OvlEntrypoint mb3_ovlEntryTbl[] = {
    { 0, MB3_BoardInit },
    { 1, MB3_SaveInit },
    { 2, MB3_Create },
    { 3, MB3_BoardReload },
    { 4, MB3Ev_OpStarMapView },
    { -1, NULL },
};

void MB3_Executor(void) {
    ovlEventCall(mb3_ovlEntryTbl, omovlevtno);
}
