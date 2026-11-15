#ifndef _GAME_CAMSETUP_H
#define _GAME_CAMSETUP_H

#include "ultra64.h"

void CamSetupInit(u8 arg0);
// Unprototyped: some callers (e.g. bounce_n_trounce) pass an unused argument.
s32 CamSetupMapCullAdd();
void CamSetupInitMulti(s32 arg0);
s32 CamSetupMapCullAddMulti(s32 arg0);

#endif
