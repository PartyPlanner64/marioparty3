#ifndef INST_H
#define INST_H

#include "common.h"

typedef struct {
    omObjData *object;
    void (*update)(omObjData *);
} InstObjectState;

#endif
