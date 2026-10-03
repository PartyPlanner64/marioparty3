#include "common.h"
#include "ovl_81.h"

typedef struct UnkD5B20 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Object *unk_04;
    /* 0x08 */ omObjData *unk_08;
} UnkD5B20; // sizeof 0xC

typedef struct UnkNameProcData {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkNameProcData; // sizeof 0x10

typedef struct UnkD5B20PrcData {
    /* 0x00 */ s32 *unk_00;
    /* 0x04 */ u16 unk_04;
} UnkD5B20PrcData; // sizeof 0x8

typedef struct UnkNameVecEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04; // max index
    /* 0x06 */ s16 unk_06; // current index
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec *unk_0C; // array of at least unk_04 Vecs
} UnkNameVecEntry;          // sizeof 0x10

typedef struct UnkNameWobbleData {
    /* 0x00 */ Object *obj;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} UnkNameWobbleData; // sizeof 0x10

extern UnkD5B20 D_80105560_name_81[];
extern s32 D_8010124C_name_81;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDD50_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDDBC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDE1C_name_81);

Process *func_800EDEC4_name_81(Object *obj, f32 arg1, f32 arg2) {
    Process *prc = omAddPrcObj(func_800EDE1C_name_81, 0xA, 0, 0x40);
    UnkNameWobbleData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameWobbleData));

    prc->user_data = data;
    data->obj = obj;
    data->unk_04 = arg1;
    data->unk_08 = arg2;
    data->unk_0C = obj->velocity.x;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDF48_name_81);

void func_800EDF78_name_81(void) {
    if (D_801011F4_name_81 != NULL) {
        omDelPrcObj(D_801011F4_name_81);
        D_801011F4_name_81 = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EDFAC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE0D0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE0F4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE114_name_81);

Process *func_800EE40C_name_81(s32 arg0) {
    Process *prc = omAddPrcObj(func_800EE114_name_81, 0xA, 0, 0x40);
    UnkNameProcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkNameProcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE468_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EE74C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EEC40_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED24_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED30_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED50_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED5C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED68_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EED84_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EEDA0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF0A0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF0BC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF0D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF3B4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF3D0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF3EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF3F8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF754_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF7C8_name_81);

s32 func_800EF7D4_name_81(Object *arg0) {
    s32 ret = 0;
    if (arg0->velocity.z != 0.0f) {
        ret = 1;
    }
    return ret;
}

void func_800EF800_name_81(Object *arg0) {
    while (func_800EF7D4_name_81(arg0)) {
        HuPrcVSleep();
    }
}

void func_800EF840_name_81(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80105560_name_81[i].unk_04 = NULL;
        D_80105560_name_81[i].unk_08 = NULL;
    }
}

void func_800EF880_name_81(void) {
    s32 i;
    UnkD5B20 *entry;

    for (i = 0, entry = D_80105560_name_81; i < 16; i++) {
        if (entry[i].unk_08 != NULL) {
            omDelObj(entry[i].unk_08);
            entry[i].unk_08 = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF8EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EF9C4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFA8C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFABC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFB00_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFB3C_name_81);

s32 func_800EFBE8_name_81(s32 playerIndex) {
    return GwPlayer[playerIndex].star * 1000 + GwPlayer[playerIndex].coin;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFC28_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFD24_name_81);

s32 func_800EFE20_name_81(f32 arg0) { // 800EEF80 in party mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFE8C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFEAC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800EFEC8_name_81);

UnkNameVecEntry *func_800EFFBC_name_81(s32 arg0, f32 arg1, s16 arg2, Vec *arg3) {
    UnkNameVecEntry *entry = HuMemMemoryAllocPerm(sizeof(UnkNameVecEntry));

    entry->unk_00 = arg0;
    entry->unk_04 = arg2;
    entry->unk_06 = 0;
    entry->unk_08 = arg1;
    entry->unk_0C = arg3;
    return entry;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F001C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F008C_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/D5B20", D_80102580_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0208_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0378_name_81);

void func_800F03C8_name_81(s16 arg0) {
    func_8001C258_main(arg0, 0x4000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F03F0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0480_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F04FC_name_81);

void func_800F05AC_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F05B4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F061C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F06D4_name_81);

s32 func_800F0700_name_81(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0708_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F08BC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0C30_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0C4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0D1C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0DF8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0E4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0EA8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F0FE8_name_81);

Process *func_800F1340_name_81(s32 *arg0, s32 arg1, s16 arg2) {
    Process *prc = omAddPrcObj(func_800F0FE8_name_81, 0x1005, 0, 0x40);
    UnkD5B20PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD5B20PrcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    data->unk_04 = arg2;
    D_8010124C_name_81 = arg1;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F13C0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F140C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F14A8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F159C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F1784_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2090_name_81);

s32 func_800F21CC_name_81(s16 arg0) {
    s32 i;
    s16 chr = arg0;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBDGetPlayerStruct(i);
        if (player->stat & PLAYER_IS_CPU) {
            continue;
        }
        if (player->pad == chr) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2238_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F22E8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F23FC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2408_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F24DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F2618_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F32CC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F336C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3500_name_81);

s16 MBDGetCurrentPlayerIndex(void) {
    return GwSystem.current_player_index;
}

GW_PLAYER *MBDGetPlayerStruct(s32 player) {
    if (player < 0) {
        player = MBDGetCurrentPlayerIndex();
    }
    return &GwPlayer[player];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F379C_name_81);

s32 func_800F37B8_name_81(s16 playerIndex) {
    return MBDGetPlayerStruct(playerIndex)->stat & PLAYER_IS_CPU;
}

void func_800F37E0_name_81(s32 playerIndex, s32 amount) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(playerIndex);
    player->coin = player->coin + amount;
    if (player->coin > 999) {
        player->coin = 999;
    }
    if (player->coin < 0) {
        player->coin = 0;
    }
    if (player->coinPrize <= player->coin) {
        player->coinPrize = player->coin;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3850_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3880_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F38DC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F397C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3A04_name_81);

void func_800F3AF4_name_81(s32 playerIndex, f32 arg1) {
    func_8001C92C_main(MBDGetPlayerStruct(playerIndex)->player_obj->omObj1->model[0], arg1);
    func_800F8CD8_name_81(playerIndex, arg1);
}

void func_800F3B54_name_81(s32 playerIndex, u8 cpuDifficulty) {
    MBDGetPlayerStruct(playerIndex)->cpu_difficulty = D_80101370_name_81[cpuDifficulty];
}

void func_800F3B8C_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3B94_name_81);

void func_800F3C28_name_81(void) {
    GW_PLAYER *player = HuPrcCurrentGet()->user_data;

    while (1) {
        HuPrcVSleep();
        if (player->stat & PLAYER_UNK_04) {
            continue;
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3C98_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3D50_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3D74_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3DC0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3DFC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3E58_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3E88_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3EC0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3F18_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F3F4C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D5B20", func_800F4030_name_81);
