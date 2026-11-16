#include "common.h"

void modesel_ObjectSetup(void);
void modesel_ReturnObjectSetup(void);
void modesel_FadeWhiteObjectSetup(void);

OvlEntrypoint modesel_ovlEntryTbl[] = {
    { 0, modesel_ObjectSetup },
    { 1, modesel_ReturnObjectSetup },
    { 2, modesel_FadeWhiteObjectSetup },
    { -1, NULL }
};

void modesel_Executor(void) {
    ovlEventCall(modesel_ovlEntryTbl, omovlevtno);
}
