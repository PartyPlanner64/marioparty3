#include "common.h"

void op_TitleObjectSetup(void);
void op_DemoReturnObjectSetup(void);
void op_DemoObjectSetup(void);

OvlEntrypoint op_ovlEntryTbl[] = {
    { 0, op_TitleObjectSetup },
    { 1, op_DemoReturnObjectSetup },
    { 2, op_DemoObjectSetup },
    { -1, NULL }
};

void op_Executor(void) {
    ovlEventCall(op_ovlEntryTbl, omovlevtno);
}
