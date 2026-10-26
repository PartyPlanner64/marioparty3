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
    s32 overlay;
    u8 minigameType;
    u8 unk05;
    u16 flags;
    s16 message;
    s16 unk_0A[4];
    s16 finalMessage;
} InstMessageInfo;

typedef struct {
    s16 unk_00;
    s16 x;
} InstSpritePos;

extern const InstModelHooks4 D_8010D770_inst;
extern const InstModelHooks D_8010D7A4_inst;
extern const InstModelHooks4 D_8010D7B0_inst;
extern const InstModelHooks D_8010D7E4_inst;
extern const InstModelHooks4 D_8010D7EC_inst;
extern const InstModelHooks D_8010D820_inst;
extern const InstModelHooks4 D_8010D828_inst;
extern const InstModelHooks D_8010D85C_inst;
extern const InstModelHooks2 D_8010D864_inst;
extern const InstModelHooks D_8010D880_inst;
extern const InstModelHooks D_8010D888_inst;
extern const InstModelHooks5 D_8010D89C_inst;
extern const InstModelHooks D_8010D8DC_inst;
extern const InstModelHooks D_8010D8EC_inst;
extern const InstModelHooks D_8010D8F4_inst;
extern const InstModelHooks D_8010D904_inst;

#endif
