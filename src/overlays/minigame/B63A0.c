#include "common.h"
#include "overlays/minigame.h"

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3820_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E38A4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3928_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E39CC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3AB8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3B98_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3CA0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3D3C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3E24_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3EA4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3F44_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3FD8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E4248_minigame);

s32 func_800E4510_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    if (temp_v0->unk144 != NULL) {
        if (temp_v0->unk144(arg0) == 1) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E454C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E47D8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E4890_minigame);
