#include "common.h"
#include "PR/synthInternals.h"

/* alFilterNew */
void func_80075B00_main(ALFilter *f, ALCmdHandler h, ALSetParam s, s32 type) {
    f->source = 0;
    f->handler = h;
    f->setParam = s;
    f->inp = 0;
    f->outp = 0;
    f->type = type;
}
