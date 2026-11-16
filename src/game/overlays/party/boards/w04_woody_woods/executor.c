#include "common_board.h"

void MB4_BoardInit(void);
void MB4_SaveInit(void);
void MB4_Create(void);
void MB4_BoardReload(void);
void MB4Ev_OpStarMapView(void);

OvlEntrypoint mb4_ovlEntryTbl[] = {
    { 0, MB4_BoardInit },
    { 1, MB4_SaveInit },
    { 2, MB4_Create },
    { 3, MB4_BoardReload },
    { 4, MB4Ev_OpStarMapView },
    { -1, NULL },
};

void MB4_Executor(void) {
    ovlEventCall(mb4_ovlEntryTbl, omovlevtno);
}
