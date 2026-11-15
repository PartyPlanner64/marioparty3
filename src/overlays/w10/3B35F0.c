#include "common_board.h"

void func_801059D0_w10(void);
void func_80105A0C_w10(void);
void func_8010B5A4_w10(void);

OvlEntrypoint D_8010B7D0_w10[] = {
    { 0, func_801059D0_w10 },
    { 1, func_80105A0C_w10 },
    { 2, func_8010B5A4_w10 },
    { -1, NULL },
};

void func_801059A0_w10(void) {
    ovlEventCall(D_8010B7D0_w10, omovlevtno);
}
