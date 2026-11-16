#ifndef INST_H
#define INST_H

#include "common.h"
#include "game/gamemes.h"

typedef struct {
    s16 count;
    const char *nodes[1];
} InstModelHooks;

typedef struct {
    s16 count;
    const char *nodes[2];
} InstModelHooks2;

typedef struct {
    s16 count;
    const char *nodes[4];
} InstModelHooks4;

typedef struct {
    s16 count;
    const char *nodes[5];
} InstModelHooks5;

typedef struct {
    omObjData *object;
    void (*update)(omObjData *);
} InstObjectState;

typedef struct {
    s16 curGroup;       /* 0x00 */
    s16 mainMembers[3]; /* 0x02 */
    s16 helpMembers[2]; /* 0x08 */
    s16 member;         /* 0x0C */
} UnkInstWin;           /* sizeof 0x0E */

typedef struct {
    s16 unk_00;
    s16 x;
} InstSpritePos;

extern const InstModelHooks4 inst_mg4PPlayerHooks;
extern const InstModelHooks inst_mg4PItemHooks;
extern const InstModelHooks4 inst_mg2vs2PlayerHooks;
extern const InstModelHooks inst_mg2vs2ItemHooks;
extern const InstModelHooks4 inst_mg3vs1PlayerHooks;
extern const InstModelHooks inst_mg3vs1ItemHooks;
extern const InstModelHooks4 inst_battlePlayerHooks;
extern const InstModelHooks inst_battleItemHooks;
extern const InstModelHooks2 inst_duelPlayerHooks;
extern const InstModelHooks inst_duelItemHooks;
extern const InstModelHooks inst_itemPlayerHooks;
extern const InstModelHooks5 inst_itemItemHooks;
extern const InstModelHooks inst_omakePlayerHooks;
extern const InstModelHooks inst_omakeItemHooks;
extern const InstModelHooks inst_lastPlayerHooks;
extern const InstModelHooks inst_lastItemHooks;

#endif
