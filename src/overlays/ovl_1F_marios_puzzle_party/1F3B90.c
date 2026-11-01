#include "common.h"
#include "game/mallocblock.h"

// 0x14 byte entry for one space of a Mario's Puzzle Party board path
typedef struct MarioPuzzlePartyPathSpace {
    /* 0x00 */ s32 distance;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 ownerId;
    /* 0x10 */ s32 type;
} MarioPuzzlePartyPathSpace;

// one board path of 40 spaces
typedef struct MarioPuzzlePartyPath {
    /* 0x00 */ MarioPuzzlePartyPathSpace spaces[40];
} MarioPuzzlePartyPath;

extern MarioPuzzlePartyPath D_801102E0_marios_puzzle_party[4][6];

// per-player input state; CPU players read their input from here rather than a controller
typedef struct MarioPuzzlePartyPlayerInput {
    /* 0x00 */ s32 unk_00[16];
    /* 0x40 */ u16 direction;
    /* 0x42 */ u16 buttons;
} MarioPuzzlePartyPlayerInput; // sizeof 0x44

extern MarioPuzzlePartyPlayerInput D_80114DE0_marios_puzzle_party[4];

// number of players that took part in the game
extern s32 D_80116100_marios_puzzle_party;

// per-player "still waiting for its turn to finish" flag
extern s32 D_80116168_marios_puzzle_party[4];

// per-player process spawned by the minigame setup
extern Process *D_801163D8_marios_puzzle_party[4];

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801059A0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105C98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105D50_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80105E88_marios_puzzle_party);

u16 func_80105FCC_marios_puzzle_party(s32 playerIndex, s16 bits) {
    u16 result;

    if (!(GwPlayer[playerIndex].stat & PLAYER_IS_CPU)) {
        result = D_800D5558_main[GwPlayer[playerIndex].pad];
        result &= bits;
    } else {
        MarioPuzzlePartyPlayerInput *input = &D_80114DE0_marios_puzzle_party[playerIndex];
        result = input->buttons;
        result &= bits;
        input->buttons &= ~bits;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010604C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106A44_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106ACC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106C98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80106E40_marios_puzzle_party);

s32 func_80107000_marios_puzzle_party(s32 board, s32 pathIdx) {
    s32 i = 1;
    MarioPuzzlePartyPath *path = &D_801102E0_marios_puzzle_party[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107070_marios_puzzle_party);

s32 func_80107108_marios_puzzle_party(s32 board, s32 pathIdx) {
    s32 i = 1;
    s32 count = 0;
    MarioPuzzlePartyPath *path = &D_801102E0_marios_puzzle_party[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
        if (path->spaces[i].type == 1) {
            count++;
            i++;
        }
    }
    return count;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010718C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107224_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107400_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107880_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107CBC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108568_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801088F4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108A50_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108BB0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80108C80_marios_puzzle_party);

void func_8010913C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109160_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010961C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_801098A0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109C04_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80109D24_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A0D8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A4B4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A588_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A958_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010AD20_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010CF4C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010CFF8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D290_marios_puzzle_party);

void func_8010D46C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D490_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D8E8_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010D9AC_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010DB98_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E12C_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E868_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EAA0_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010ECD8_marios_puzzle_party);

void func_8010EEB0_marios_puzzle_party(void) {
    s32 i;

    for (i = 0; i < D_80116100_marios_puzzle_party; i++) {
        if (D_80116168_marios_puzzle_party[i] == 0) {
            omDelPrcObj(D_801163D8_marios_puzzle_party[i]);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", D_801102B4_marios_puzzle_party);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EF30_marios_puzzle_party);
