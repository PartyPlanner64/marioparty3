#ifndef _MGRESULTBATTLE_H
#define _MGRESULTBATTLE_H

#include "game/object.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultBattlePlayerObj;

extern ResultBattlePlayerObj D_80108F50_mgresultbattle[4];

#endif
