#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/input.h"

void ContDataInit(void) {
    s16 i;
    for (i = 0; i < MAXCONTROLLERS; ++i) {
        ContBtn[i] =
            ContBtnOld[i] =
                ContBtnDown[i] =
                    ContBtnRep[i] =
                        ContRepCnt[i] = 0;
    }
}

void ContDataUpdate(void) {
    s16 i;
    s32 temp_v0_3;
    s32 temp_v0_5;
    u16 var_a2;
    s8 temp_v0_2;
    s8 temp_v0_4;

    for (i = 0; i < MAXCONTROLLERS; ++i) {
        ContBtnOld[i] = ContBtn[i];
        var_a2 = HuPadBtn[i];
        temp_v0_2 = HuPadStkX[i];
        temp_v0_3 = ((temp_v0_2 >> 7) | 1);

        if (((temp_v0_2 * temp_v0_3) - 0x1E) > 0) {
            if (temp_v0_3 > 0) {
                var_a2 = (var_a2 & 0xFDFF) | 0x100;
            } else {
                var_a2 = (var_a2 & 0xFEFF) | 0x200;
            }
        }

        temp_v0_4 = HuPadStkY[i];
        temp_v0_5 = ((temp_v0_4 >> 7) | 1);

        if (((temp_v0_4 * temp_v0_5) - 0x1E) > 0) {
            if (temp_v0_5 > 0) {
                var_a2 = (var_a2 & 0xFBFF) | 0x800;
            } else {
                var_a2 = (var_a2 & 0xF7FF) | 0x400;
            }
        }

        ContBtn[i] = var_a2;
        ContBtnDown[i] = var_a2 & (var_a2 ^ ContBtnOld[i]);

        if ((var_a2 & 0xFFFF) != ContBtnOld[i]) {
            ContRepCnt[i] = 0xA;
            ContBtnRep[i] = ContBtnDown[i];
        } else {
            if (ContRepCnt[i] > 0) {
                ContRepCnt[i] = ContRepCnt[i] - 1;
                ContBtnRep[i] = ContBtnDown[i];
            } else {
                ContRepCnt[i] = 1;
                ContBtnRep[i] = var_a2;
            }
        }
    }
}
