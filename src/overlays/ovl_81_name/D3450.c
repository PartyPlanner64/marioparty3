#include "common.h"
#include "ovl_81.h"

typedef struct UnkD3450PrcData {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkD3450PrcData; // sizeof 0x10

typedef struct UnkD3450PrcDataF {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkD3450PrcDataF; // sizeof 0x10

void func_800EB680_name_81(s16 playerIdx, s16 spaceIdx, Vec *outCoords) {
    SpaceData *space = MBDMasuGet(spaceIdx);

    outCoords->x = space->coords.x;
    outCoords->y = space->coords.y;
    outCoords->z = space->coords.z;
}

void func_800EB6C4_name_81(s16 playerIdx, s16 spaceIdx) {
    func_800EB680_name_81(playerIdx, spaceIdx, &GwPlayer[playerIdx].player_obj->coords);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB708_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB740_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB780_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB7BC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB7D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB804_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EB8B0_name_81);

s16 func_800EB984_name_81(void) {
    s32 i;
    s32 totalStars = 0;

    for (i = 0; i < 2; i++) {
        totalStars += MBDGetPlayerStruct(i)->star;
    }
    return totalStars;
}

s32 func_800EB9D4_name_81(s8 percent) {
    return percent > ((rand8() & 0xFF) * 99 >> 8);
}

s16 func_800EBA1C_name_81(void) {
    GW_SYSTEM *system = &GwSystem;

    return system->total_turns - system->current_turn + 1;
}

s32 func_800EBA50_name_81(s16 arg0, f32 arg1) {
    Vec sp10;
    s32 var_v0;

    sp10.x = D_800CBB6E_main[arg0];
    sp10.y = 0.0f;
    sp10.z = D_800D20A1_main[arg0];

    if (!(arg1 <= HuVecGetLength3F(&sp10))) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    return var_v0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBAD4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBB00_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBC60_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBD1C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBDDC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBE60_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBF2C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EBFE0_name_81);

void func_800EC114_name_81(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC11C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC1E4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC298_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC36C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC420_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC548_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC6F4_name_81);

Process *func_800EC91C_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EC6F4_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EC99C_name_81);

Process *func_800ECBB4_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EC99C_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ECC34_name_81);

void func_800ECD0C_name_81(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIdx);

    if (nlink >= 0) {
        player->clink = nlink;
        player->nlink = nlink;
        player->blink = nlink;
    }
    if (nidx >= 0) {
        player->cidx = nidx;
        player->nidx = nidx + 1;
        player->bidx = nidx - 1;
    }
}

void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIdx);

    if (nlink >= 0) {
        player->nlink = nlink;
    }
    if (nidx >= 0) {
        player->nidx = nidx;
    }
}

void func_800ECDE8_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    player->rev |= FLAG_REV;
}

void func_800ECE10_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    player->rev &= ~FLAG_REV;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ECE38_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ECF1C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED118_name_81);

void func_800ED214_name_81(s32 playerIndex) {
    Vec sp10;
    Vec sp20;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Object *partner;

    func_800ECF1C_name_81(playerIndex, &sp10, &sp20);

    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp10);
        func_800D7828_name_81(&sp10);
        HuVecCopy3F(&partner->rot, &sp10);
    }

    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        HuVecCopy3F(&partner->coords, &player->player_obj->coords);
        HuVecAdd(&partner->coords, &partner->coords, &sp20);
        func_800D7828_name_81(&sp20);
        func_800D7934_name_81(&sp20, 180.0f);
        HuVecCopy3F(&partner->rot, &sp20);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED31C_name_81);

Process *func_800ED4AC_name_81(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(func_800ED31C_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED520_name_81);

Process *func_800ED68C_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800ED520_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *func_800ED70C_name_81(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDGetPlayerStruct(playerIdx)->stats.prize.gamblePrize != -1) {
        if (arg != 0) {
            prc = func_800ED4AC_name_81(playerIdx, 0xF);
        } else {
            prc = func_800ED68C_name_81(playerIdx, 3.0f);
        }
    }
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED788_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800ED7EC_name_81);

Process *func_800ED9C4_name_81(s16 playerIdx, s32 arg) {
    Process *prc = omAddPrcObj(func_800ED7EC_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcData));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg;
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EDA38_name_81);

Process *func_800EDBEC_name_81(s16 playerIdx, f32 arg1) {
    Process *prc = omAddPrcObj(func_800EDA38_name_81, 0x4003, 0, 0x40);
    UnkD3450PrcDataF *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD3450PrcDataF));

    prc->user_data = data;
    data->unk_00 = playerIdx;
    data->unk_04 = arg1;
    return prc;
}

Process *func_800EDC6C_name_81(s32 playerIdx, s32 arg) {
    Process *prc = NULL;

    if (MBDGetPlayerStruct(playerIdx)->stats.prize.duelNo != -1) {
        if (arg != 0) {
            prc = func_800ED9C4_name_81(playerIdx, 0xF);
        } else {
            prc = func_800EDBEC_name_81(playerIdx, 3.0f);
        }
    }
    return prc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/D3450", func_800EDCE8_name_81);
