#include "common.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the group 0 player objects.
typedef struct EndOfTheLinePlayer {
    /* 0x00 */ u16 playerIdx;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ omObjData *obj;
} EndOfTheLinePlayer; // sizeof 0x24 (0x94 bytes are allocated for it)

// State for the whole minigame. Lives in the `data` pointer (0x5C) of the main
// object, D_8010C738_end_of_the_line. The esprite handles a player uses are the
// slots at [playerIdx], [playerIdx + 2], [playerIdx + 4], ...
typedef struct EndOfTheLineData {
    /* 0x00 */ u16 esprites[12];
    /* 0x18 */ char unk18[0x7900];
} EndOfTheLineData; // sizeof 0x7918

extern omObjData *D_8010C738_end_of_the_line;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801059A0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80105E0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80105E88_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106444_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801069D8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106CDC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107FF0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801080C8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801082D8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801088A4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80108F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010937C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80109E70_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A17C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A434_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A708_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A7D0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A8B4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A91C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AA1C_end_of_the_line);

void func_8010AA7C_end_of_the_line(EndOfTheLinePlayer *player) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    func_8000BB94_main(data->esprites[player->playerIdx + 2]);
    omDelObj(player->obj);
    player->obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AAC8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010ABD4_end_of_the_line);

void func_8010AC34_end_of_the_line(EndOfTheLinePlayer *player) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    func_8000BB94_main(data->esprites[player->playerIdx + 4]);
    omDelObj(player->obj);
    player->obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AC80_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AF28_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B064_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B190_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B234_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B300_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B420_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B4EC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B588_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B640_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BE24_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BF64_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C060_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C110_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C3F4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C47C_end_of_the_line);

void func_8010C574_end_of_the_line(void) {
}
