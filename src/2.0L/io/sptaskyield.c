#include "common.h"
#include "PR/osint.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}
