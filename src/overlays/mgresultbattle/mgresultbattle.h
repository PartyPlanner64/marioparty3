#ifndef _MGRESULTBATTLE_H
#define _MGRESULTBATTLE_H

#include "game/object.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultBattlePlayerObj;

extern ResultBattlePlayerObj D_80108F50_mgresultbattle[4];
extern s32 D_80108F70_mgresultbattle;
extern s8 D_80108F8C_mgresultbattle[4];
extern Vec D_801089D0_mgresultbattle[4];

/* 4F3780 */
void func_80106918_mgresultbattle(void);

/* 4F4980 */
void func_80106BA0_mgresultbattle(void);
void func_80107400_mgresultbattle(void);
void func_801075FC_mgresultbattle(void);

/* 4F5AF0 */
void func_80107D10_mgresultbattle(void);
void func_80108130_mgresultbattle(void);
void func_801082AC_mgresultbattle(void);

#endif
