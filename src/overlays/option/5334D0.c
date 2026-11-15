#include "common.h"

void func_80105C14_option(void);
void func_80105C38_option(void);
void func_80105C5C_option(void);
void func_80105C80_option(void);
void func_80105CA4_option(void);
void func_80105CC8_option(void);
void func_80105CEC_option(void);

OvlEntrypoint D_801134B0_option[] = {
    { 0, func_80105C14_option },
    { 1, func_80105C38_option },
    { 2, func_80105C5C_option },
    { 3, func_80105C80_option },
    { 4, func_80105CA4_option },
    { 5, func_80105CC8_option },
    { 6, func_80105CEC_option },
    { -1, NULL },
};

void func_801059A0_option(void) {
    ovlEventCall(D_801134B0_option, omovlevtno);
}
