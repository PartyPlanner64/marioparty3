#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "ultra64.h"
#include "common_structs.h"

/* Globals whose owning module is not yet known. Most are main segment BSS
 * shared with board overlays. */
#ifndef NO_EXTERN_VARIABLES
extern s16 HuAudMusNo;
extern SaiWork mbSaiWorkTbl[5];
extern s16 mbSaiBtnF;
extern u8 mbSaiTriple7F;
extern s16 duelCancelEnableF;
extern s16 mbSubMusNo;
extern s16 mgModeCoinRate;
extern char omDBGStrBuf[];
extern u16 HuPadBtnDown[4];
extern u16 omSysExitReq;
extern u8 omSysPauseDisableF;


extern s16 mbUnkParam;
extern s16 mbEndingF;
#endif

#endif //_VARIABLES_H_
