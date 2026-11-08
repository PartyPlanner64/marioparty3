#include "common.h"
#include "game/window.h"
#include "../ovl_80_shared_board/106A50.h"

extern s32 D_8010FAE4_chancetime;
extern s8 D_8010FAE8_chancetime;

void func_801062DC_chancetime(void);

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

void func_801061B8_chancetime(omObjData *object) {
    if (D_800D530C_main != 1) {
        return;
    }

    if (D_8010FAE8_chancetime == 0) {
        WipeCreateOut(0, 20);
        D_8010FAE8_chancetime = 1;
    } else if (WipeStatGet() == 0) {
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        GMesClose();
        func_801062DC_chancetime();
        omOvlReturnEx(1);
    }
}

void func_80106240_chancetime(void) {
    u16 sprite;

    sprite = espEntry(func_8000B838_main(0x1C0001), 0, 0);
    espPosSet(sprite, 160, 180);
    espAttrSet(sprite, 0x4000);

    sprite = espEntry(func_8000B838_main(0x1C0005), 0, 0);
    espPosSet(sprite, 160, 60);
    espAttrSet(sprite, 0x4000);
}

void func_801062DC_chancetime(void) {
    HuWinAllKill();
    if (D_8010FAE4_chancetime == 1) {
        func_800F5EF0_shared_board();
    }
}
