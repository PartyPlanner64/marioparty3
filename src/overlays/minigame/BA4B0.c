#include "common.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7930_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7A2C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7BCC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7E08_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E7F60_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E8EC4_minigame);

s32 func_800E8F78_minigame(Process *prc) {
    func_800E1BA8_minigame_UnkE8_ObjData *data;
    s32 result;

    if (prc == NULL) {
        return 0;
    }
    data = prc->user_data;
    data->unk04 = 0xFF;
    do {
        HuPrcVSleep();
    } while (data->unk04 != 0);
    result = omDelPrcObj(prc);
    HuMemFree(data);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E8FE4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E8FF8_minigame);

void func_800E9004_minigame(Process *prc, s16 value) {
    func_800E1BA8_minigame_UnkE8_ObjData *data = prc->user_data;

    if (data->unk04 != value) {
        do {
            HuPrcVSleep();
        } while (data->unk04 != value);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E905C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E9170_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BA4B0", func_800E989C_minigame);
