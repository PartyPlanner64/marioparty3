#ifndef _MGRESULTDEALER_H
#define _MGRESULTDEALER_H

#include "game/object.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultDealerObj;

extern ResultDealerObj D_8010A250_mgresultdealer;

#endif
