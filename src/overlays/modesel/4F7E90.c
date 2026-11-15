#include "common.h"

void func_80105BD8_modesel(void);
void func_80105BFC_modesel(void);
void func_80105C20_modesel(void);

OvlEntrypoint D_8010F270_modesel[] = {
    { 0, func_80105BD8_modesel },
    { 1, func_80105BFC_modesel },
    { 2, func_80105C20_modesel },
    { -1, NULL }
};

void func_801059A0_modesel(void) {
    ovlEventCall(D_8010F270_modesel, omovlevtno);
}
