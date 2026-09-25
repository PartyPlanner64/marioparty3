#include "common.h"

extern s32 D_800A2A30_main;
extern OSMesgQueue *D_800A2A38_main;

OSMesgQueue *func_80080B30_main(void) {
    if (D_800A2A30_main == 0) {
        return 0;
    }
    return D_800A2A38_main;
}
