#include "common.h"

typedef struct RidiculousRelayPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk_05[7];
} RidiculousRelayPlayer; // sizeof 0xC

extern RidiculousRelayPlayer D_80111940_ridiculous_relay[4];
extern RidiculousRelayPlayer *D_80111970_ridiculous_relay[4]; // players indexed by group
extern f32 D_80111980_ridiculous_relay[7];
extern f32 D_8011199C_ridiculous_relay[2];
extern f32 D_801119A8_ridiculous_relay[4];
extern u8 D_801119B8_ridiculous_relay[4]; // group of each player
extern s8 D_801119C0_ridiculous_relay;
extern f32 D_801119C4_ridiculous_relay;
extern s32 D_801119C8_ridiculous_relay;
extern s16 D_801119CC_ridiculous_relay;
extern f32 D_801119D0_ridiculous_relay;
extern s32 D_801119D4_ridiculous_relay;
extern s16 D_801119D8_ridiculous_relay;
extern u8 D_801119DA_ridiculous_relay;
extern f32 D_801119DC_ridiculous_relay;
extern s32 D_80111A30_ridiculous_relay[3];
extern f32 D_80111A50_ridiculous_relay;

void func_80105F48_ridiculous_relay(omObjData *object);
void func_80108DE8_ridiculous_relay(Gfx **gfxPos, s32 arg1, s32 arg2);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_801059A0_ridiculous_relay);

void func_80105D40_ridiculous_relay(omObjData *object) {
    s32 group;
    s32 i;

    D_801119CC_ridiculous_relay = 0;
    D_801119D8_ridiculous_relay = 0;
    D_801119D4_ridiculous_relay = 0;
    D_801119C8_ridiculous_relay = 0;
    D_801119C0_ridiculous_relay = 5;
    D_801119DA_ridiculous_relay = 0;
    D_8011199C_ridiculous_relay[0] = D_8011199C_ridiculous_relay[1] = 0.0f;
    D_801119C4_ridiculous_relay = 0.0f;
    D_80111A50_ridiculous_relay = 0.0f;
    D_801119DC_ridiculous_relay = 0.0f;
    D_801119D0_ridiculous_relay = 0.0f;
    D_801119A8_ridiculous_relay[0] = D_801119A8_ridiculous_relay[1] = D_801119A8_ridiculous_relay[2] = D_801119A8_ridiculous_relay[3] = 0.0f;
    D_80111980_ridiculous_relay[0] = D_80111980_ridiculous_relay[1] = D_80111980_ridiculous_relay[2] = D_80111980_ridiculous_relay[3] =
        D_80111980_ridiculous_relay[4] = D_80111980_ridiculous_relay[5] = D_80111980_ridiculous_relay[6] = 0.0f;
    D_80111A30_ridiculous_relay[0] = D_80111A30_ridiculous_relay[1] = D_80111A30_ridiculous_relay[2] = -1;
    for (i = 0; i < 4; i++) {
        D_80111970_ridiculous_relay[i] = &D_80111940_ridiculous_relay[i];
        bzero(D_80111970_ridiculous_relay[i], sizeof(RidiculousRelayPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        D_801119B8_ridiculous_relay[i] = group;
        D_80111970_ridiculous_relay[group]->playerNo = i;
        D_80111970_ridiculous_relay[group]->pad = GwPlayer[i].pad;
        D_80111970_ridiculous_relay[group]->chr = GwPlayer[i].chr;
        D_80111970_ridiculous_relay[group]->group = group;
        D_80111970_ridiculous_relay[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, func_80108DE8_ridiculous_relay, 2);
    object->func = func_80105F48_ridiculous_relay;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110E60_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80105F48_ridiculous_relay);

s16 func_80106610_ridiculous_relay(s32 file, u16 *sprite, u16 flags) {
    void *data = DataRead(file);
    s16 anim = func_800329B4_main(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, flags, 0);
    D_800CBB60_main[idx].unk_02 = anim;
    return D_800CBB60_main[idx].modelId;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_801066A0_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106D28_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110EB8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F34_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F40_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F7C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F84_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110F8C_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80106D4C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FA8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80110FC8_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_80108DE8_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AE4C_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AE80_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AEAC_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AED8_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111030_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111050_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111070_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010AF04_ridiculous_relay);

f32 func_8010B474_ridiculous_relay(f32 x) {
    Vec pos;
    Vec2f out;

    pos.x = x;
    pos.y = 0.0f;
    pos.z = 0.0f;
    func_80012B14_main(1, &pos, &out);
    return out.x;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011108C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801110D4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011111C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111164_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111178_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111184_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111194_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111A4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111B4_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010B4A8_ridiculous_relay);

s16 func_80110BF4_ridiculous_relay(s16 arg0, s16 arg1) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return func_8004AC5C_main(arg0, 0);
}

s16 func_80110C3C_ridiculous_relay(s16 seId, s16 playerIdx) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_8004AC5C_main(seId + GwPlayer[playerIdx].chr + 1, 0);
}
