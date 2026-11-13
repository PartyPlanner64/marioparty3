#include "common.h"
#include "overlays/minigame.h"

typedef struct RidiculousRelayPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk_05[7];
} RidiculousRelayPlayer; // sizeof 0xC

extern D_80111B50_vine_with_me_Struct D_80110CB0_ridiculous_relay;
extern RidiculousRelayPlayer D_80111940_ridiculous_relay[4];
extern RidiculousRelayPlayer *D_80111970_ridiculous_relay[4]; // players indexed by group
extern f32 D_80111980_ridiculous_relay[7];
extern f32 D_8011199C_ridiculous_relay[2];
extern f32 D_801119A8_ridiculous_relay[4];
extern u8 D_801119B8_ridiculous_relay[4]; // group of each player
extern omObjData *D_801119BC_ridiculous_relay;
extern s8 D_801119C0_ridiculous_relay;
extern f32 D_801119C4_ridiculous_relay;
extern s32 D_801119C8_ridiculous_relay;
extern s16 D_801119CC_ridiculous_relay;
extern f32 D_801119D0_ridiculous_relay;
extern s32 D_801119D4_ridiculous_relay;
extern s16 D_801119D8_ridiculous_relay;
extern u8 D_801119DA_ridiculous_relay;
extern f32 D_801119DC_ridiculous_relay;
extern omObjData *D_80111A20_ridiculous_relay[4];
extern s32 D_80111A30_ridiculous_relay[3];
extern f32 D_80111A50_ridiculous_relay;

const s16 D_80110E60_ridiculous_relay[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void func_80105D40_ridiculous_relay(omObjData *object);
void func_801066A0_ridiculous_relay(omObjData *object);
void func_8010AE4C_ridiculous_relay(omObjData *object);
void func_8010AE80_ridiculous_relay(omObjData *object);
void func_8010AEAC_ridiculous_relay(omObjData *object);
void func_8010AED8_ridiculous_relay(omObjData *object);

void func_80105F48_ridiculous_relay(omObjData *object);
void func_80108DE8_ridiculous_relay(Gfx **gfxPos, s32 arg1, s32 arg2);

void func_801059A0_ridiculous_relay(void) {
    omObjData *object;

    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 22.619865f, 375.0f, 1250.0f);
    Hu3DCameraPerspectiveSet(1, 22.619865f, 375.0f, 1250.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, 0.0f, 40.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 468.75f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 468.75f;
    omAddObj(0, 0, 0, -1, func_80105D40_ridiculous_relay);
    D_801119BC_ridiculous_relay = omAddObj(8, 35, 35, -1, func_801066A0_ridiculous_relay);
    omSetStatBit(D_801119BC_ridiculous_relay, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_80111A20_ridiculous_relay[0] = omAddObj(3, 3, 12, -1, func_8010AE4C_ridiculous_relay);
    D_80111A20_ridiculous_relay[1] = omAddObj(3, 3, 12, -1, func_8010AE80_ridiculous_relay);
    D_80111A20_ridiculous_relay[2] = omAddObj(3, 3, 12, -1, func_8010AEAC_ridiculous_relay);
    D_80111A20_ridiculous_relay[3] = omAddObj(3, 3, 12, -1, func_8010AED8_ridiculous_relay);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80045010_main(D_80110E60_ridiculous_relay, 1);
    WipeCreateIn(0xFF, 16);
    D_80110CB0_ridiculous_relay.unk01 = 2;
    D_80110CB0_ridiculous_relay.unk1C = -1;
    D_80110CB0_ridiculous_relay.unk1C = 45;
    D_80110CB0_ridiculous_relay.unk1E = 9000;
    D_80110CB0_ridiculous_relay.unk03 = 0;
    D_80110CB0_ridiculous_relay.unk02 = 1;
    D_80110CB0_ridiculous_relay.unk22 = 45;
    D_80110CB0_ridiculous_relay.unk24 = 165;
    D_80110CB0_ridiculous_relay.unk04 = 0;
    D_80110CB0_ridiculous_relay.unk05 = 0;
    D_80110CB0_ridiculous_relay.unk20 = -1;
    func_800E5EA0_minigame(&D_80110CB0_ridiculous_relay);
}

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
