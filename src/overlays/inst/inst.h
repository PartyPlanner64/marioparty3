#ifndef INST_H
#define INST_H

#include "common.h"

typedef struct {
    s16 count;
    char *nodes[1];
} InstModelHooks;

typedef struct {
    omObjData *object;
    void (*update)(omObjData *);
} InstObjectState;

#endif
