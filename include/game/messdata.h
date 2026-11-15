#ifndef _GAME_MESSDATA_H
#define _GAME_MESSDATA_H

#include "ultra64.h"

void MessDataInit(u32 stringsRomPtr);
void MessDataSet(u32 ptr);
void *MessDataMesGet(void *arg0);
void MessDataMesFree(void *ptr);

#endif
