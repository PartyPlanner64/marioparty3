#include "common_duel.h"

void func_80105B64_duel06(void);
void func_80105BA0_duel06(void);
void func_8010DA8C_duel06(void);
void func_8010DB08_duel06(void);

OvlEntrypoint D_80114480_duel06[] = {
    { 0, func_80105B64_duel06 },
    { 1, func_80105BA0_duel06 },
    { 2, func_8010DA8C_duel06 },
    { 3, func_8010DB08_duel06 },
    { -1, NULL }
};

void func_801059A0_duel06(void) {
    ovlEventCall(D_80114480_duel06, omovlevtno);
}
