#include "ChillyWaters.h"

void MB1_BoardInit(void);
void MB1_SaveInit(void);
void MB1_Create(void);
void MB1_BoardReload(void);
void MB1Ev_OpStarMapView(void);

OvlEntrypoint mb1_ovlEntryTbl[] = {
    { 0, MB1_BoardInit },
    { 1, MB1_SaveInit },
    { 2, MB1_Create },
    { 3, MB1_BoardReload },
    { 4, MB1Ev_OpStarMapView },
    { -1, NULL },
};

void MB1_Executor(void) {
    ovlEventCall(mb1_ovlEntryTbl, omovlevtno);
}
