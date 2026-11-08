#include "common.h"
#include "game/window.h"
#include "../ovl_80_shared_board/106A50.h"

extern s32 D_8010FAE4_chancetime;

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/481970", func_801059A0_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/481970", func_80105E08_chancetime);

void func_80106154_chancetime(void) {
    CRot.x = 0.1f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;

    Center.x = 0.0f;
    Center.y = 230.0f;
    Center.z = 920.0f;

    CZoom = 100.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/481970", func_801061B8_chancetime);

INCLUDE_ASM("asm/nonmatchings/overlays/chancetime/481970", func_80106240_chancetime);

void func_801062DC_chancetime(void) {
    HuWinAllKill();
    if (D_8010FAE4_chancetime == 1) {
        func_800F5EF0_shared_board();
    }
}
