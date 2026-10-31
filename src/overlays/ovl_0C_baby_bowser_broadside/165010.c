#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"
#include "game/pause.h"
#include "overlays/baby_bowser_broadside.h"

typedef struct BabyBowserBroadsideEntry {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec unk_04;
    /* 0x10 */ Vec velocity;
    /* 0x1C */ f32 initialVelocityY;
    /* 0x20 */ f32 elapsed;
    /* 0x24 */ f32 angle;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
    /* 0x2C */ BabyBowserBroadsideShip *unk_2C;
} BabyBowserBroadsideEntry; // Size 0x30

typedef struct unk_80109EBC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk_09;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char unk_11[0xF];
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ char unk_24[0x24];
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ char unk_4A[2];
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ BabyBowserBroadsideEntry *unk_54;
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ s16 unk_5A;
    /* 0x5C */ BabyBowserBroadsideShip *unk_5C;
} unk_80109EBC;

typedef struct BabyBowserBroadsideTeam {
    /* 0x00 */ s8 count;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s16 players[2];
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ f32 angles[2];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char unk_16[2];
} BabyBowserBroadsideTeam; // Size 0x18

typedef struct BabyBowserBroadsideGame {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ char unk_08[0x10];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ char unk_1A[0xE];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ char unk_2C[0xC];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E[4];
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48[4];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s8 unk_52;
    /* 0x53 */ char unk_53[5];
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ s8 unk_60;
    /* 0x61 */ s8 unk_61;
    /* 0x62 */ char unk_62[2];
} BabyBowserBroadsideGame; // Size 0x64

extern BabyBowserBroadsideTeam *D_80110000_baby_bowser_broadside;
extern unk_80109EBC *D_80110004_baby_bowser_broadside;
extern BabyBowserBroadsideGame *D_80110008_baby_bowser_broadside;

extern u8 D_800CB8B1_main[];

typedef struct BabyBowserBroadsidePositions {
    Vec points[4][4];
} BabyBowserBroadsidePositions;

typedef struct BabyBowserBroadsidePortraits {
    s32 files[8];
} BabyBowserBroadsidePortraits;

extern Vec D_8010FEE8_baby_bowser_broadside;
extern BabyBowserBroadsidePositions D_8010FEF4_baby_bowser_broadside;
extern BabyBowserBroadsidePortraits D_8010FFB4_baby_bowser_broadside;

void func_80106E40_baby_bowser_broadside(omObjData *object);
void func_80106EC4_baby_bowser_broadside(omObjData *object);
void func_80108210_baby_bowser_broadside(BabyBowserBroadsideSlot *slot);
void func_80108350_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80108614_baby_bowser_broadside(void);
s16 func_8010A598_baby_bowser_broadside(s32 priority, s32 directory, s32 file, s32 bank, s32 attr);
void func_8010A738_baby_bowser_broadside(s16 sprite, s16 x, s16 y);
s16 func_8010A8C4_baby_bowser_broadside(s32 directory, s32 file, f32 scale, s32 type, s32 arg4, s32 flags);
s16 func_8010AE60_baby_bowser_broadside(s32 directory, s32 file, s32 arg2, s32 arg3);
void func_8010DAE8_baby_bowser_broadside(s32 arg0, BabyBowserBroadsideHandler *handler);
s16 func_8010DB38_baby_bowser_broadside(s16 model, Vec *positions, s16 count, f32 arg3, f32 arg4, s32 flags);
s16 func_8010DC88_baby_bowser_broadside(s16 boat, s32 flags);
void func_8010F250_baby_bowser_broadside(omObjData *object);
void func_8010F6F8_baby_bowser_broadside(f32 *start, f32 *end);

extern u8 D_800D6A90_main;
extern s16 D_8010FD60_baby_bowser_broadside;
extern s16 D_8010FD76_baby_bowser_broadside;
extern s16 D_8010FD74_baby_bowser_broadside;
extern s16 D_8010FD70_baby_bowser_broadside;
extern s16 D_8010FD72_baby_bowser_broadside;
extern s16 D_8011000C_baby_bowser_broadside;
extern f32 D_8010FD64_baby_bowser_broadside;
extern f32 D_8010FD68_baby_bowser_broadside;
extern f32 D_8010FD6C_baby_bowser_broadside;

void func_8001E65C_main(s16 model, f32 x, f32 y, s32 width, s32 height);
void func_8001F6BC_main(s16 model, u8 r, u8 g, u8 b, u8 a);
void func_8001F6F8_main(s16 model, u8 r, u8 g, u8 b, u8 a);
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];

void func_80107600_baby_bowser_broadside(omObjData *object);
void func_8010913C_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80109434_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_801096E8_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80109D94_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80109EB0_baby_bowser_broadside(unk_80109EBC *player, s16 motion, s8 arg2);
void func_8010E0B0_baby_bowser_broadside(BabyBowserBroadsideShip *ship);
void func_8010E018_baby_bowser_broadside(BabyBowserBroadsideShip *ship, s16 count, f32 speed, s16 model);
s32 func_8000B638_main(void);
f32 atan2df(f32 y, f32 x);
void func_80106288_baby_bowser_broadside(omObjData *object);
void func_801062C4_baby_bowser_broadside(omObjData *object);
void func_80106E70_baby_bowser_broadside(omObjData *object);
void func_80107140_baby_bowser_broadside(omObjData *object);
void func_80107630_baby_bowser_broadside(void);
void func_801076AC_baby_bowser_broadside();
void func_80107A00_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80107C64_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80109BD8_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80107FE0_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_801081A4_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80109D2C_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
void func_80107A80_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
s32 func_80109058_baby_bowser_broadside(omObjData *object, unk_80109EBC *player);
void func_80108860_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler);
BabyBowserBroadsideGroup *func_80109F64_baby_bowser_broadside(omObjData *object, s8 group, s16 count, s16 handlers);
s16 func_8010A0B4_baby_bowser_broadside(s8 group, s32 flags, s32 arg2, void (*callback)(), s32 arg4);

extern s16 D_8010FD78_baby_bowser_broadside[];
extern s16 D_8010FD84_baby_bowser_broadside[];

extern const s16 D_8010FEC0_baby_bowser_broadside[];
extern const s16 D_8010FECC_baby_bowser_broadside[];
extern const s16 D_8010FEDC_baby_bowser_broadside[];

void func_801059BC_baby_bowser_broadside(void);
void func_80105B94_baby_bowser_broadside(void);
void func_80105DE4_baby_bowser_broadside(omObjData *object);
void func_80105E2C_baby_bowser_broadside(omObjData *object);
void func_80105E64_baby_bowser_broadside(omObjData *object);
void func_80105F64_baby_bowser_broadside(omObjData *object);
void func_80109ED0_baby_bowser_broadside(void);
void func_8010A158_baby_bowser_broadside();
void func_8010A2C4_baby_bowser_broadside(s8 group);
void func_8010A81C_baby_bowser_broadside(void);
void func_8010ACF8_baby_bowser_broadside(void);
void func_8010B3B4_baby_bowser_broadside(void);
s16 func_8010AADC_baby_bowser_broadside(s16 index);
s16 func_80109970_baby_bowser_broadside(unk_80109EBC *player);
void func_80109EBC_baby_bowser_broadside(unk_80109EBC *player, s16 motion);
void func_801098F8_baby_bowser_broadside(BabyBowserBroadsideEntry *entry);
void func_801099D4_baby_bowser_broadside(omObjData *object, BabyBowserBroadsideEntry *entry, f32 angle, s16 team);
s16 func_8010AFF4_baby_bowser_broadside(s16 index);
void func_8010B098_baby_bowser_broadside(s16 index, f32 x, f32 y, f32 z, u8 *color);
s32 func_8010AB80_baby_bowser_broadside(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 arg8);

void func_801059A0_baby_bowser_broadside(void) {
    func_801059BC_baby_bowser_broadside();
}

void func_801059BC_baby_bowser_broadside(void) {
    u8 camera;

    Hu3DAnimInit(0x32);
    func_800142A0_main(0x30);
    omInitObjMan(0x32, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    HmfLightColorSet(0, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camera = func_8000B638_main();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 30.0f, 80.0f, 6000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80109ED0_baby_bowser_broadside();
    func_80105B94_baby_bowser_broadside();
    omAddObj(0x3E8, 0, 0, -1, func_80105F64_baby_bowser_broadside);
    omAddObj(0x7D0, 0, 0, -1, func_80105DE4_baby_bowser_broadside);
    func_80045010_main(D_8010FEC0_baby_bowser_broadside, 1);
    func_80045010_main(D_8010FECC_baby_bowser_broadside, 1);
    func_80045010_main(D_8010FEDC_baby_bowser_broadside, 1);
}

void func_80105B94_baby_bowser_broadside(void) {
    s8 i, j;
    s8 angle;
    s32 random;
    f32 startAngle;

    D_80110008_baby_bowser_broadside = HuMemAllocTag(0x64, 0x7918);
    memset(D_80110008_baby_bowser_broadside, 0, 0x64);
    D_80110004_baby_bowser_broadside = HuMemAllocTag(0x180, 0x7918);
    memset(D_80110004_baby_bowser_broadside, 0, 0x180);
    for (i = 0; i < 4; i++) {
        D_80110004_baby_bowser_broadside[i].unk_54 = HuMemAllocTag(0x90, 0x7918);
        memset(D_80110004_baby_bowser_broadside[i].unk_54, 0, 0x90);
    }
    D_80110000_baby_bowser_broadside = HuMemAllocTag(0x30, 0x7918);
    memset(D_80110000_baby_bowser_broadside, 0, 0x30);
    random = rand16();
    angle = random % 4;
    startAngle = D_80110000_baby_bowser_broadside[0].angles[0] = angle * 90.0f;
    D_80110000_baby_bowser_broadside[0].angles[1] = startAngle + 180.0f;
    D_80110000_baby_bowser_broadside[1].angles[0] = startAngle + 90.0f;
    D_80110000_baby_bowser_broadside[1].angles[1] = startAngle + 270.0f;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            while (D_80110000_baby_bowser_broadside[i].angles[j] >= 360.0f) {
                D_80110000_baby_bowser_broadside[i].angles[j] -= 360.0f;
            }
        }
    }
}

void func_80105DE4_baby_bowser_broadside(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = func_80105E2C_baby_bowser_broadside;
    }
}

void func_80105E2C_baby_bowser_broadside(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80105E64_baby_bowser_broadside;
    }
}

void func_80105E64_baby_bowser_broadside(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105E88_baby_bowser_broadside(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    func_8010A2C4_baby_bowser_broadside(0);
}

void func_80105F64_baby_bowser_broadside(omObjData *object) {
    s16 counts[2];
    s16 i, j;
    BabyBowserBroadsideTeam *team;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    func_80109F64_baby_bowser_broadside(NULL, 0, 0, 4);
    func_8010A0B4_baby_bowser_broadside(0, 0, 0, func_80107630_baby_bowser_broadside, 0);
    object->work[1] = 1;
    func_80109F64_baby_bowser_broadside(object, (s8)object->work[1], 0, 6);
    D_800EC1C0_minigame[0] = omAddObj(10, 1, 0, -1, func_801062C4_baby_bowser_broadside);
    D_800EC1C0_minigame[1] = omAddObj(10, 1, 0, -1, func_80106E70_baby_bowser_broadside);
    omSetStatBit(D_800EC1C0_minigame[1], 0xA0);
    counts[1] = 0;
    counts[0] = 0;
    for (i = 0; i < 4; i++) {
        if (D_800CB8B1_main[i] >= 2 || counts[0] >= 3 || counts[1] >= 3) {
            for (j = 0; j < 4; j++) {
                D_800CB8B1_main[j] = GwPlayer[j].group;
            }
            break;
        }
        counts[D_800CB8B1_main[i]]++;
    }
    for (i = 0; i < 4; i++) {
        team = &D_80110000_baby_bowser_broadside[D_80110004_baby_bowser_broadside[i].unk_5A = D_800CB8B1_main[i]];
        D_80110004_baby_bowser_broadside[i].unk_10 = team->count;
        team->players[team->count++] = i;
    }
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(300, 9, 41, -1, func_80107140_baby_bowser_broadside);
    }
    D_80110008_baby_bowser_broadside->unk_00 = 1;
    D_80110008_baby_bowser_broadside->unk_04 = 900.0f;
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xFFFF, 0, func_801076AC_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xF, 0, func_80107A80_baby_bowser_broadside, 0);
    WipeCreateIn(0xFF, 16);
    object->func = func_80106288_baby_bowser_broadside;
}

void func_80106288_baby_bowser_broadside(omObjData *object) {
    func_8010A2C4_baby_bowser_broadside((s8)object->work[1]);
    func_80105E88_baby_bowser_broadside();
    func_8010A81C_baby_bowser_broadside();
    func_8010ACF8_baby_bowser_broadside();
    func_8010B3B4_baby_bowser_broadside();
}

void func_801062C4_baby_bowser_broadside(omObjData *object) {
    s16 hudY = 32;
    s32 flags = 0x99;
    s32 attr = 0x1000;
    Vec center = D_8010FEE8_baby_bowser_broadside;
    Vec bowserCenter = D_8010FEE8_baby_bowser_broadside;
    BabyBowserBroadsidePositions positions = D_8010FEF4_baby_bowser_broadside;
    BabyBowserBroadsidePortraits portraits = D_8010FFB4_baby_bowser_broadside;
    BabyBowserBroadsideSlot *slot;
    BabyBowserBroadsideHandler *handler;
    BabyBowserBroadsideEntry *entry;
    s16 i, j;
    s16 model;
    s16 sprite;
    s16 index;

    object->work[1] = 2;
    slot = func_80109F64_baby_bowser_broadside(object, (s8)object->work[1], 6, 4)->unk_00;
    slot->unk_04[0] = func_8000B108_main(0x2D0002, flags);
    slot->unk_04[1] = func_8000B108_main(0x2D0000, flags);
    slot->unk_04[2] = func_8000B108_main(0x2D0001, flags);
    slot->unk_04[3] = D_80110008_baby_bowser_broadside->unk_50 = func_8000B108_main(0x2D0008, flags);
    slot->unk_04[4] = func_8000B108_main(0x2D0009, flags);
    slot->unk_04[5] = func_8000B108_main(9, flags);
    D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[0].players[0]].unk_48 = model = func_8000B108_main(0x2D0004, flags);
    D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[0].players[1]].unk_48 = Hu3DModelLink(model);
    D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[1].players[0]].unk_48 = model = func_8000B108_main(0x2D0005, flags);
    D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[1].players[1]].unk_48 = Hu3DModelLink(model);
    entry = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[0].players[0]].unk_54;
    model = entry->unk_02 = func_8000B108_main(0x2D0006, flags);
    for (i = 0; i < 2; i++) {
        entry = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[0].players[i]].unk_54;
        for (j = 0; j < 3; j++, entry++) {
            if ((i == 0) & (j == 0)) {
                // The first projectile already uses the original model.
            } else {
                entry->unk_02 = Hu3DModelLink(model);
            }
        }
    }
    entry = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[1].players[0]].unk_54;
    model = entry->unk_02 = func_8000B108_main(0x2D0007, flags);
    for (i = 0; i < 2; i++) {
        entry = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[1].players[i]].unk_54;
        for (j = 0; j < 3; j++, entry++) {
            if ((i == 0) & (j == 0)) {
                // The first projectile already uses the original model.
            } else {
                entry->unk_02 = Hu3DModelLink(model);
            }
        }
    }
    Hu3DModelScaleSet((s16)slot->unk_04[5], 2.0f, 2.0f, 2.0f);
    Hu3DModelPosSet((s16)slot->unk_04[2], 0.0f, 350.0f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[3], 0.0f, 455.00003f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[4], 0.0f, 455.00003f, 0.0f);
    Hu3DModelPosSet((s16)slot->unk_04[5], 0.0f, 450.0f, 0.0f);
    HmfModelData[(s16)slot->unk_04[3]].unk44 = 0.0f;
    for (i = 0; i < 4; i++) {
        HmfModelData[D_80110004_baby_bowser_broadside[i].unk_48].unk44 = 0.0f;
    }
    flags |= 0x400;
    for (i = 0; i < 4; i++) {
        func_8010A8C4_baby_bowser_broadside(0x2D, 12, 2.0f, 0, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        func_8010A8C4_baby_bowser_broadside(0x2D, 13, 2.0f, 1, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        func_8010A8C4_baby_bowser_broadside(0x2D, 10, 1.0f, 2, 0, flags);
    }
    for (i = 0; i < 4; i++) {
        func_8010A8C4_baby_bowser_broadside(0x2D, 11, 1.0f, 3, 0, flags);
    }
    for (i = 0; i < 8; i++) {
        index = func_8010AE60_baby_bowser_broadside(0x2D, 15, 0, 11);
        Hu3DModelScaleSet(D_80110010_baby_bowser_broadside[index].unk_0C, 2.0f, 2.0f, 1.0f);
    }
    sprite = func_8010A598_baby_bowser_broadside(255, 0x2D, 14, 0, attr);
    HuSprTPLvlSet(D_80110018_baby_bowser_broadside[sprite].unk_01, 0, 190);
    func_8010A738_baby_bowser_broadside(sprite, 70, 32);
    sprite = func_8010A598_baby_bowser_broadside(255, 0x2D, 14, 0, attr);
    HuSprTPLvlSet(D_80110018_baby_bowser_broadside[sprite].unk_01, 0, 190);
    func_8010A738_baby_bowser_broadside(sprite, 250, 32);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_8010A738_baby_bowser_broadside(func_8010A598_baby_bowser_broadside(239, 33, portraits.files[GwPlayer[D_80110000_baby_bowser_broadside[i].players[j]].chr], 0, 0), i * 180 + (s16)(j * 18 + 40), hudY);
        }
    }
    for (i = 0; i < 2; i++) {
        D_80110000_baby_bowser_broadside[i].unk_12 = model = func_8010A598_baby_bowser_broadside(239, 0, 45, 0, 0);
        func_8010A738_baby_bowser_broadside(model, (s16)(i * 180 + 84), hudY);
        D_80110000_baby_bowser_broadside[i].unk_14 = model = func_8010A598_baby_bowser_broadside(239, 0, 45, 0, 0);
        func_8010A738_baby_bowser_broadside(model, (s16)(i * 180 + 100), hudY);
    }
    index = func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xFFFF, 0, func_8010DAE8_baby_bowser_broadside, (s8)object->work[1]);
    handler = &D_80110014_baby_bowser_broadside[object->work[1]].unk_04[index];
    handler->unk_40(0, handler);
    D_80110008_baby_bowser_broadside->unk_3C = func_8010DB38_baby_bowser_broadside(-1, &center, 1, 400.0f, 1000.0f, 0x490);
    D_80110008_baby_bowser_broadside->unk_46 = func_8010DB38_baby_bowser_broadside((s16)slot->unk_04[4], &bowserCenter, 1, 10.0f, 150.0f, 0x40C);
    for (i = 0; i < 4; i++) {
        D_80110008_baby_bowser_broadside->unk_3E[i] = func_8010DB38_baby_bowser_broadside((s16)slot->unk_04[2], positions.points[i], 4, 0.0f, 0.0f, 0x13E);
    }
    for (i = 0; i < 4; i++) {
        D_80110008_baby_bowser_broadside->unk_48[i] = func_8010DC88_baby_bowser_broadside(D_80110008_baby_bowser_broadside->unk_3E[i], 0x116);
    }
    D_80110008_baby_bowser_broadside->unk_60 = 0;
    D_80110008_baby_bowser_broadside->unk_61 = (s32)rand16() % 4 + 1;
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0, 0, func_80108210_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 14, 0, func_80108350_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 15, 0, func_80108614_baby_bowser_broadside, 0);
    object->model[0] = slot->unk_04[0];
    func_8010F250_baby_bowser_broadside(object);
    object->func = func_80106E40_baby_bowser_broadside;
}

void func_80106E40_baby_bowser_broadside(omObjData *object) {
    func_8010A2C4_baby_bowser_broadside(2);
    func_8010F250_baby_bowser_broadside(object);
}

void func_80106E70_baby_bowser_broadside(omObjData *object) {
    object->model[0] = func_8000B108_main(0x2D0003, 0x10099);
    func_8001C954_main(object->model[0]);
    object->func = func_80106EC4_baby_bowser_broadside;
}

void func_80106EC4_baby_bowser_broadside(omObjData *object) {
    func_8001E65C_main(object->model[0], sindf(D_8010FD64_baby_bowser_broadside) * 15.0f, -D_8010FD68_baby_bowser_broadside, 64, 64);
    func_8001F6BC_main(object->model[0], (u8)(cosdf(D_8010FD6C_baby_bowser_broadside) * 32.0f + 32.0f), 0, 0, (u8)(cosdf(D_8010FD6C_baby_bowser_broadside) * 32.0f + 32.0f));
    func_8001F6F8_main(object->model[0], 64, 32, 32, 0);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010FD64_baby_bowser_broadside += 0.5f;
        if (D_8010FD64_baby_bowser_broadside >= 360.0f) {
            D_8010FD64_baby_bowser_broadside -= 360.0f;
        }
        D_8010FD68_baby_bowser_broadside += 0.2f;
        if (D_8010FD68_baby_bowser_broadside >= 64.0f) {
            D_8010FD68_baby_bowser_broadside -= 64.0f;
        }
        D_8010FD6C_baby_bowser_broadside += 2.4f;
        if (D_8010FD6C_baby_bowser_broadside >= 360.0f) {
            D_8010FD6C_baby_bowser_broadside -= 360.0f;
        }
    }
}

void func_80107140_baby_bowser_broadside(omObjData *object) {
    s32 flags = 0x2B9;
    unk_80109EBC *player;
    s16 i;
    s32 modelFile, motionFile;

    object->work[0] = D_800EC280_minigame;
    object->work[1] = D_800EC280_minigame + 3;
    player = &D_80110004_baby_bowser_broadside[object->work[0]];
    player->unk_02 = GwPlayer[object->work[0]].chr;
    modelFile = D_800A178C_main[player->unk_02][0];
    motionFile = D_800A1790_main[player->unk_02][0];
    func_800E1BA8_minigame(object, modelFile, motionFile, (u16)object->work[0], flags, flags);
    object->trans.z = 200.0f;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(player->unk_02, 0), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(player->unk_02, 2), 1, 0);
    func_800E5A00_minigame(object, 13, func_80017BB8_main(player->unk_02, 0x2F), 1, 999);
    if (player->unk_02 == 5) {
        func_800E5A00_minigame(object, 14, func_80017BB8_main(5, 0x38), 1, 999);
    } else {
        func_800E5A00_minigame(object, 14, func_80017BB8_main(player->unk_02, 0x37), 1, 999);
    }
    func_800E5A00_minigame(object, 38, func_80017BB8_main(player->unk_02, 0x27), 1, 0);
    func_800E5A00_minigame(object, 39, func_80017BB8_main(player->unk_02, 0x28), 1, 999);
    func_800E5A00_minigame(object, 40, func_80017BB8_main(player->unk_02, 0x28), 1, 999);
    func_80109EB0_baby_bowser_broadside(player, 38, 1);
    player->unk_0C = -1;
    player->unk_00 = ((func_800E1BA8_minigame_ObjData *)object->data)->unk57;
    player->unk_04 = 0x10000;
    player->unk_50 = D_80110000_baby_bowser_broadside[player->unk_5A].angles[player->unk_10];
    player->unk_4C = player->unk_50 + 180.0f;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    D_800EC280_minigame++;
    for (i = 0; i < 3; i++) {
        player->unk_54[i].unk_2C = HuMemAllocTag(sizeof(BabyBowserBroadsideShip), 0x7918);
        func_8010E018_baby_bowser_broadside(player->unk_54[i].unk_2C, 6, 40.0f, player->unk_54[i].unk_02);
        player->unk_54[i].unk_2C->unk_04[1] = D_80110008_baby_bowser_broadside->unk_3C;
        player->unk_54[i].unk_2C->unk_04[2] = D_80110008_baby_bowser_broadside->unk_46;
        player->unk_54[i].unk_2C->unk_04[3] = D_80110008_baby_bowser_broadside->unk_3E[0];
        player->unk_54[i].unk_2C->unk_04[4] = D_80110008_baby_bowser_broadside->unk_3E[1];
        player->unk_54[i].unk_2C->unk_04[5] = D_80110008_baby_bowser_broadside->unk_3E[2];
        player->unk_54[i].unk_2C->unk_04[6] = D_80110008_baby_bowser_broadside->unk_3E[3];
        func_8001C258_main(player->unk_54[i].unk_02, 4, 4);
    }
    player->unk_5C = HuMemAllocTag(sizeof(BabyBowserBroadsideShip), 0x7918);
    func_8010E018_baby_bowser_broadside(player->unk_5C, 4, 50.0f, -1);
    player->unk_5C->unk_04[1] = D_80110008_baby_bowser_broadside->unk_48[0];
    player->unk_5C->unk_04[2] = D_80110008_baby_bowser_broadside->unk_48[1];
    player->unk_5C->unk_04[3] = D_80110008_baby_bowser_broadside->unk_48[2];
    player->unk_5C->unk_04[4] = D_80110008_baby_bowser_broadside->unk_48[3];
    func_80109F64_baby_bowser_broadside(object, (s8)object->work[1], 0, 8);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xF, (s32)player, func_8010913C_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xCFFF, (s32)player, func_80109434_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xEFFF, (s32)player, func_801096E8_baby_bowser_broadside, 0);
    func_8010A0B4_baby_bowser_broadside((s8)object->work[1], 0xFFFF, (s32)player, func_80109D94_baby_bowser_broadside, 0);
    object->func = func_80107600_baby_bowser_broadside;
}

void func_80107600_baby_bowser_broadside(omObjData *object) {
    func_8010A2C4_baby_bowser_broadside((s8)object->work[1]);
    func_800E4E30_minigame(object);
}

void func_80107630_baby_bowser_broadside(void) {
    Center.x = 0.0f;
    Center.y = 215.0f;
    Center.z = -144.0f;
    CRot.x = 322.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2410.0f;
    func_8010A158_baby_bowser_broadside(0);
}

void func_801076AC_baby_bowser_broadside(void) {
    s16 i;
    s16 ones, tens;

    for (i = 0; i < 2; i++) {
        if (D_80110000_baby_bowser_broadside[i].unk_10 < 100) {
            ones = D_80110000_baby_bowser_broadside[i].unk_10 % 10;
            tens = D_80110000_baby_bowser_broadside[i].unk_10 * 0.1f;
            func_80054FF8_main(D_80110018_baby_bowser_broadside[D_80110000_baby_bowser_broadside[i].unk_12].unk_01, 0, tens);
            func_80054FF8_main(D_80110018_baby_bowser_broadside[D_80110000_baby_bowser_broadside[i].unk_14].unk_01, 0, ones);
        } else {
            func_80054FF8_main(D_80110018_baby_bowser_broadside[D_80110000_baby_bowser_broadside[i].unk_12].unk_01, 0, 9);
            func_80054FF8_main(D_80110018_baby_bowser_broadside[D_80110000_baby_bowser_broadside[i].unk_14].unk_01, 0, 9);
        }
    }
}

void func_80107854_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    if ((s8)handler->unk_04 == 0) {
        handler->unk_10 = 0;
        GMesCreate(26, D_80110008_baby_bowser_broadside->unk_04 / 30.0f, 160, 28);
        handler->unk_04 = 1;
    }
    D_80110008_baby_bowser_broadside->unk_04 -= 1.0f;
    func_8003F578_main((s16)((D_80110008_baby_bowser_broadside->unk_04 + 29.0f) * (1.0f / 30.0f)));
    if (D_80110008_baby_bowser_broadside->unk_04 < 0.0f) {
        D_80110008_baby_bowser_broadside->unk_00 = 4;
        D_80110008_baby_bowser_broadside->unk_38 = 0.0f;
        HuAudSeqFadeOut(120);
        GMesCreate(16);
        func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0xF, 0, func_80107A00_baby_bowser_broadside, 0);
        func_8003F5C0_main();
        if (D_80110000_baby_bowser_broadside[0].unk_10 == D_80110000_baby_bowser_broadside[1].unk_10) {
            func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0, 0, func_80107FE0_baby_bowser_broadside, 0);
        } else {
            func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0, 0, func_80107C64_baby_bowser_broadside, 0);
        }
        func_8010A158_baby_bowser_broadside((s8)slot->unk_00->work[1], handler);
    }
}

void func_80107A00_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    if ((s8)handler->unk_04 == 0) {
        handler->unk_1C = 0;
        handler->unk_1E = 0;
        handler->unk_04 = 1;
    }
    if (++handler->unk_1C >= 16) {
        handler->unk_1C = 15;
        func_8004AB0C_main(15);
        func_8010A158_baby_bowser_broadside((s8)slot->unk_00->work[1], handler);
    }
}

void func_80107A80_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    s16 i;

    if ((s8)handler->unk_04 == 0) {
        D_8011000C_baby_bowser_broadside = HuAudFXPlay(0x35C);
        func_8004AAD0_main(D_8011000C_baby_bowser_broadside, 64);
        handler->unk_1C = 0;
        handler->unk_04 = 1;
    }
    switch (++handler->unk_1C) {
        case 20:
            GMesCreate(5);
            HuAudFXPlay(14);
            break;
        case 40:
            D_8010FD70_baby_bowser_broadside = 1;
            break;
        default:
            if (D_8010FD70_baby_bowser_broadside == 1 && GMesStatGet() == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                        func_8010A0B4_baby_bowser_broadside((s8)(i + 3), 0, (s32)&D_80110004_baby_bowser_broadside[i], func_80108860_baby_bowser_broadside, 0);
                    }
                }
                func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0xF, 0, func_80107854_baby_bowser_broadside, 0);
                D_80110008_baby_bowser_broadside->unk_38 = 0.5f;
                D_80110008_baby_bowser_broadside->unk_00 = 2;
                func_8010A158_baby_bowser_broadside((s8)slot->unk_00->work[1], handler);
            }
            break;
    }
    if (D_8010FD72_baby_bowser_broadside == 0 && GMesStatGet() != 0) {
        HuAudSeqPlay(48);
        D_8010FD72_baby_bowser_broadside = 1;
    }
}

void func_80107C64_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    s16 i;
    s16 character1, character2;
    s16 player;

    if ((s8)handler->unk_04 == 0) {
        if (++handler->unk_1C > 40) {
            handler->unk_1C = 0;
            if (D_80110000_baby_bowser_broadside[0].unk_10 > D_80110000_baby_bowser_broadside[1].unk_10) {
                handler->unk_0C = 0;
            } else {
                handler->unk_0C = 1;
            }
            handler->unk_0D = !handler->unk_0C;
            for (i = 0; i < 2; i++) {
                player = D_80110000_baby_bowser_broadside[handler->unk_0C].players[i];
                func_8010A0B4_baby_bowser_broadside((s8)(player + 3), 0xDFFF,
                                                    (s32)&D_80110004_baby_bowser_broadside[player], func_80109BD8_baby_bowser_broadside, 0);
                player = D_80110000_baby_bowser_broadside[handler->unk_0D].players[i];
                func_8010A0B4_baby_bowser_broadside((s8)(player + 3), 0xDFFF,
                                                    (s32)&D_80110004_baby_bowser_broadside[player], func_80109D2C_baby_bowser_broadside, 0);
            }
            handler->unk_04 = 1;
        }
    } else if (D_8010FD74_baby_bowser_broadside == 0) {
        if (GMesStatGet() == 0) {
            D_8010FD74_baby_bowser_broadside = 1;
        }
    } else if (D_8010FD74_baby_bowser_broadside >= 2) {
        if (GMesStatGet() == 0) {
            D_8010FD74_baby_bowser_broadside = 3;
        }
        if (D_8010FD74_baby_bowser_broadside == 3) {
            if (++handler->unk_1C >= 15) {
                func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0, 0, func_801081A4_baby_bowser_broadside, 0);
                func_8010A158_baby_bowser_broadside((s8)slot->unk_00->work[1], handler);
            }
        }
    } else {
        if (++handler->unk_1C == 15) {
            character1 = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[handler->unk_0C].players[0]].unk_02;
            character2 = D_80110004_baby_bowser_broadside[D_80110000_baby_bowser_broadside[handler->unk_0C].players[1]].unk_02;
            HuAudSeqPlay(102);
            GMesCreate(30, character1, character2);
            GwPlayer[D_80110000_baby_bowser_broadside[handler->unk_0C].players[0]].bonusCoin += 10;
            GwPlayer[D_80110000_baby_bowser_broadside[handler->unk_0C].players[1]].bonusCoin += 10;
            D_8010FD60_baby_bowser_broadside = 1;
        }
        if (GMesStatGet() != 0) {
            handler->unk_1C = 0;
            D_8010FD74_baby_bowser_broadside = 2;
        }
    }
}

void func_80107FE0_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    s16 i;

    if ((s8)handler->unk_04 == 0) {
        if (++handler->unk_1C > 40) {
            handler->unk_1C = 0;
            for (i = 0; i < 4; i++) {
                func_8010A0B4_baby_bowser_broadside((s8)(i + 3), 0xDFFF, (s32)&D_80110004_baby_bowser_broadside[i], func_80109D2C_baby_bowser_broadside, 0);
            }
            handler->unk_04 = 1;
        }
    } else if (D_8010FD76_baby_bowser_broadside == 0) {
        if (GMesStatGet() == 0) {
            D_8010FD76_baby_bowser_broadside = 1;
        }
    } else if (D_8010FD76_baby_bowser_broadside >= 2) {
        if (GMesStatGet() == 0) {
            D_8010FD76_baby_bowser_broadside = 3;
        }
        if (D_8010FD76_baby_bowser_broadside == 3) {
            if (++handler->unk_1C >= 15) {
                func_8010A0B4_baby_bowser_broadside((s8)slot->unk_00->work[1], 0, 0, func_801081A4_baby_bowser_broadside, 0);
                func_8010A158_baby_bowser_broadside((s8)slot->unk_00->work[1], handler);
            }
        }
    } else {
        if (++handler->unk_1C == 15) {
            GMesCreate(32);
            HuAudSeqPlay(108);
            D_8010FD60_baby_bowser_broadside = 1;
        }
        if (GMesStatGet() != 0) {
            handler->unk_1C = 0;
            D_8010FD76_baby_bowser_broadside = 2;
        }
    }
}

void func_801081A4_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    switch ((s8)handler->unk_04) {
        case 0:
            WipeCreateOut(0, 20);
            handler->unk_04 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_80108210_baby_bowser_broadside(BabyBowserBroadsideSlot *slot) {
    HmfModel *model = &HmfModelData[(s16)slot->unk_04[0]];

    if (D_80110008_baby_bowser_broadside->unk_04 < 600.0f) {
        model->rot.y -= D_80110008_baby_bowser_broadside->unk_38;
        if (model->rot.y < 0.0f) {
            model->rot.y += 360.0f;
        } else if (model->rot.y >= 360.0f) {
            model->rot.y -= 360.0f;
        }
    }
    model = &HmfModelData[(s16)slot->unk_04[2]];
    model->rot.y += D_80110008_baby_bowser_broadside->unk_38;
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    } else if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
}

void func_80108350_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    HmfModel *model = &HmfModelData[D_80110008_baby_bowser_broadside->unk_50];
    f32 startX, startZ, endX, endZ;
    f32 progress;

    if (D_80110008_baby_bowser_broadside->unk_00 & 2) {
        startX = D_8010FD78_baby_bowser_broadside[D_80110008_baby_bowser_broadside->unk_60];
        startZ = D_8010FD84_baby_bowser_broadside[D_80110008_baby_bowser_broadside->unk_60];
        endX = D_8010FD78_baby_bowser_broadside[D_80110008_baby_bowser_broadside->unk_61];
        endZ = D_8010FD84_baby_bowser_broadside[D_80110008_baby_bowser_broadside->unk_61];
        progress = handler->unk_1C / 50.0f;
        progress = sindf(progress * 90.0f);
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        model->pos.x = startX + (endX - startX) * progress;
        model->pos.z = startZ + (endZ - startZ) * progress;
        if (++handler->unk_1C > 50) {
            model->pos.x = endX;
            model->pos.z = endZ;
            D_80110008_baby_bowser_broadside->unk_60 = D_80110008_baby_bowser_broadside->unk_61;
            handler->unk_1C = 0;
            while (1) {
                D_80110008_baby_bowser_broadside->unk_61 = (s32)rand16() % 5;
                if (D_80110008_baby_bowser_broadside->unk_60 == D_80110008_baby_bowser_broadside->unk_61) {
                    continue;
                }
                if (D_80110008_baby_bowser_broadside->unk_60 != 0) {
                    if (D_80110008_baby_bowser_broadside->unk_60 - D_80110008_baby_bowser_broadside->unk_61 > 0) {
                        if (D_80110008_baby_bowser_broadside->unk_60 - D_80110008_baby_bowser_broadside->unk_61 != 2) {
                            break;
                        }
                        continue;
                    } else if (D_80110008_baby_bowser_broadside->unk_61 - D_80110008_baby_bowser_broadside->unk_60 == 2) {
                        continue;
                    }
                }
                break;
            }
        }
        HmfModelData[(s16)slot->unk_04[4]].pos.x = model->pos.x;
        HmfModelData[(s16)slot->unk_04[4]].pos.z = model->pos.z;
        Hu3DModelPosSet((s16)slot->unk_04[5], model->pos.x, 450.0f, model->pos.z);
    }
}

void func_80108614_baby_bowser_broadside(void) {
    f32 tiltX, tiltZ;
    f32 angle;
    f32 progress;

    if (D_80110008_baby_bowser_broadside->unk_52 != 0) {
        D_80110008_baby_bowser_broadside->unk_28 += 15.0f;
        tiltX = sindf(D_80110008_baby_bowser_broadside->unk_28) * 30.0f * D_80110008_baby_bowser_broadside->unk_58;
        tiltZ = -(sindf(D_80110008_baby_bowser_broadside->unk_28) * 30.0f * D_80110008_baby_bowser_broadside->unk_5C);
        HmfModelData[D_80110008_baby_bowser_broadside->unk_50].rot.x = tiltX;
        HmfModelData[D_80110008_baby_bowser_broadside->unk_50].rot.z = tiltZ;
        if (D_80110008_baby_bowser_broadside->unk_28 >= 360.0f) {
            D_80110008_baby_bowser_broadside->unk_28 -= 360.0f;
            progress = D_80110008_baby_bowser_broadside->unk_18 / 6.0f;
            progress = sindf(progress * 90.0f);
            if (progress > 1.0f) {
                progress = 1.0f;
            }
            angle = progress * 90.0f;
            D_80110008_baby_bowser_broadside->unk_58 = cosdf(angle) * D_80110008_baby_bowser_broadside->unk_58;
            D_80110008_baby_bowser_broadside->unk_5C = cosdf(angle) * D_80110008_baby_bowser_broadside->unk_5C;
            if (++D_80110008_baby_bowser_broadside->unk_18 > 6) {
                D_80110008_baby_bowser_broadside->unk_52 = 0;
            }
        }
    }
}

void func_801087CC_baby_bowser_broadside(s16 arg0) {
    HmfModelData[arg0].unk44 = 1.0f;
    HmfModelData[arg0].unk40 = 0.0f;
}

void func_80108804_baby_bowser_broadside(f32 angle) {
    D_80110008_baby_bowser_broadside->unk_58 = cosdf(angle);
    D_80110008_baby_bowser_broadside->unk_5C = sindf(angle);
    D_80110008_baby_bowser_broadside->unk_52 = 1;
    D_80110008_baby_bowser_broadside->unk_18 = 0;
    D_80110008_baby_bowser_broadside->unk_28 = 0;
}

void func_80108860_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &HmfModelData[D_80110008_baby_bowser_broadside->unk_50];
    f32 angle, currentAngle, targetAngle;
    f32 tolerance;
    f32 x, z;
    s32 random;

    if ((s8)handler->unk_04 == 0) {
        switch (GwPlayer[object->work[0]].cpu_difficulty) {
            case 0:
                handler->unk_0D = 3;
                handler->unk_0E = 10;
                handler->unk_0F = 4;
                handler->unk_10 = 15;
                handler->unk_11 = 5;
                handler->unk_12 = 3;
                handler->unk_13 = 3;
                handler->unk_14 = 5;
                break;
            case 1:
                handler->unk_0D = 5;
                handler->unk_0E = 15;
                handler->unk_0F = 6;
                handler->unk_10 = 10;
                handler->unk_11 = 3;
                handler->unk_12 = 6;
                handler->unk_13 = 6;
                handler->unk_14 = 8;
                break;
            case 2:
                handler->unk_0D = 10;
                handler->unk_0E = 20;
                handler->unk_0F = 8;
                handler->unk_10 = 5;
                handler->unk_11 = 1;
                handler->unk_12 = 9;
                handler->unk_13 = 9;
                handler->unk_14 = 13;
                break;
            case 3:
                handler->unk_0D = 15;
                handler->unk_0E = 25;
                handler->unk_0F = 10;
                handler->unk_10 = 3;
                handler->unk_11 = 0;
                handler->unk_12 = 99;
                handler->unk_13 = 99;
                handler->unk_14 = 99;
                break;
        }
        handler->unk_1C = 0;
        handler->unk_1E = 30;
        handler->unk_04 = 1;
    }
    D_800CBB6E_main[player->unk_00] = 0;
    D_800D20A1_main[player->unk_00] = 0;
    D_800CDA7C_main[player->unk_00] = 0;
    player->unk_10 = 0;
    x = model->pos.x - object->trans.x;
    z = model->pos.z - object->trans.z;
    angle = atan2df(-z, x) + 90.0f;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    currentAngle = player->unk_4C;
    targetAngle = angle;
    func_8010F6F8_baby_bowser_broadside(&currentAngle, &targetAngle);
    switch (handler->unk_0C) {
        case 0:
            tolerance = (s32)rand16() % 4 + 2;
            if ((currentAngle - targetAngle > 0.0f ? currentAngle - targetAngle : -(currentAngle - targetAngle)) < tolerance) {
                if ((s16)func_80109058_baby_bowser_broadside(object, player) != 0) {
                    random = (s32)rand16() % 6;
                    handler->unk_1C = (s8)(u8)handler->unk_0F + random;
                    handler->unk_0C = 1;
                    handler->unk_2C = D_80110008_baby_bowser_broadside->unk_38 > 0.0f ? 2.0f : -2.0f;
                    if ((s32)rand16() % (handler->unk_12 + 1) == 0) {
                        handler->unk_2C = -handler->unk_2C;
                    }
                } else {
                    handler->unk_1C = (s32)rand16() % (handler->unk_0E - handler->unk_0D + 1) + handler->unk_0D;
                    handler->unk_0C = 2;
                }
            } else if ((s32)rand16() % (handler->unk_13 + 1) != 0) {
                if (currentAngle - targetAngle > 0.0f) {
                    player->unk_4C -= 2.0f;
                } else if (currentAngle - targetAngle < 0.0f) {
                    player->unk_4C += 2.0f;
                }
            }
            break;
        case 1:
            if (--handler->unk_1C > 0) {
                player->unk_4C -= handler->unk_2C;
            } else {
                handler->unk_0C = 0;
            }
            if ((s32)rand16() % (handler->unk_11 + 1) == 0) {
                if ((s16)func_80109058_baby_bowser_broadside(object, player) == 0) {
                    ((u16 *)D_800CDA7C_main)[player->unk_00] = 0x8000;
                }
            }
            break;
        case 2:
            if (--handler->unk_1E < 0) {
                handler->unk_1E = (s32)rand16() % (handler->unk_10 + 1);
                if (currentAngle - targetAngle > 0.0f) {
                    player->unk_4C -= 2.0f;
                } else if (currentAngle - targetAngle < 0.0f) {
                    player->unk_4C += 2.0f;
                }
            }
            if ((s16)func_80109058_baby_bowser_broadside(object, player) == 0) {
                if (--handler->unk_1C <= 0) {
                    handler->unk_0C = 0;
                } else if ((s32)rand16() % (handler->unk_11 + 1) == 0) {
                    ((u16 *)D_800CDA7C_main)[player->unk_00] = 0x8000;
                }
            }
            break;
        case 3:
            if (--handler->unk_1C < 0) {
                player->unk_4C += handler->unk_2C;
            } else {
                handler->unk_0C = 0;
            }
            break;
    }
}

s32 func_80109058_baby_bowser_broadside(omObjData *object, unk_80109EBC *player) {
    player->unk_5C->pos.x = object->trans.x;
    player->unk_5C->pos.y = 500.0f;
    player->unk_5C->pos.z = object->trans.z;
    player->unk_5C->facing.x = sindf(player->unk_4C) * 20.0f * 5.0f * 8.0f;
    player->unk_5C->facing.y = 0.0f;
    player->unk_5C->facing.z = cosdf(player->unk_4C) * 20.0f * 5.0f * 8.0f;
    func_8010E0B0_baby_bowser_broadside(player->unk_5C);
    return player->unk_5C->unk_2A != 0;
}

void func_8010913C_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    s16 index;
    f32 stickX, stickY;
    f32 angle;
    f32 currentAngle, targetAngle;

    if (D_80110008_baby_bowser_broadside->unk_00 & 2) {
        if (--player->unk_58 < 0) {
            player->unk_58 = 0;
        }
        if ((u16)D_800CDA7C_main[player->unk_00] & 0x8000) {
            if (player->unk_58 == 0 && player->unk_10 == 0) {
                player->unk_10 = 1;
                index = func_80109970_baby_bowser_broadside(player);
                if (index != -1) {
                    if (handler->unk_0C != 0) {
                        handler->unk_0C = 0;
                        func_80109EB0_baby_bowser_broadside(player, 40, 1);
                    } else {
                        handler->unk_0C = 1;
                        func_80109EB0_baby_bowser_broadside(player, 39, 1);
                    }
                    func_801087CC_baby_bowser_broadside(player->unk_48);
                    func_80109EBC_baby_bowser_broadside(player, 38);
                    player->unk_58 = 10;
                    player->unk_04 = (index + 1) | player->unk_04;
                }
            }
        } else {
            player->unk_10 = 0;
        }
        stickX = D_800CBB6E_main[player->unk_00];
        stickY = D_800D20A1_main[player->unk_00];
        if ((stickX == 0.0f) & (stickY == 0.0f)) {
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        } else {
            angle = atan2df(stickY, stickX) + 90.0f;
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            currentAngle = player->unk_4C;
            targetAngle = angle;
            func_8010F6F8_baby_bowser_broadside(&currentAngle, &targetAngle);
            if ((currentAngle - targetAngle > 0.0f ? currentAngle - targetAngle : -(currentAngle - targetAngle)) < 5.0f) {
                return;
            }
            if (currentAngle - targetAngle > 0.0f) {
                player->unk_4C -= 2.0f;
            } else if (currentAngle - targetAngle < 0.0f) {
                player->unk_4C += 2.0f;
            }
        }
    }
}

void func_80109434_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    f32 sinAngle, cosAngle;
    f32 targetAngle, currentAngle;

    if (!(D_80110008_baby_bowser_broadside->unk_00 & 4)) {
        if (D_80110008_baby_bowser_broadside->unk_04 < 600.0f) {
            player->unk_50 -= D_80110008_baby_bowser_broadside->unk_38;
        }
        if (player->unk_50 >= 360.0f) {
            player->unk_50 -= 360.0f;
        } else if (player->unk_50 < 0.0f) {
            player->unk_50 += 360.0f;
        }
        sinAngle = sindf(player->unk_50);
        cosAngle = cosdf(player->unk_50);
        sinAngle *= 550.0f;
        cosAngle *= 550.0f;
        Hu3DModelPosSet(player->unk_48, sinAngle, 400.0f, cosAngle);
        object->trans.x = sinAngle;
        object->trans.y = 455.0f;
        object->trans.z = cosAngle;
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y - 2.5f, cosAngle);
        targetAngle = player->unk_50 + 180.0f;
        if (targetAngle > 360.0f) {
            targetAngle -= 360.0f;
        }
        if (player->unk_4C >= 360.0f) {
            player->unk_4C -= 360.0f;
        } else if (player->unk_4C < 0.0f) {
            player->unk_4C += 360.0f;
        }
        currentAngle = player->unk_4C;
        func_8010F6F8_baby_bowser_broadside(&targetAngle, &currentAngle);
        if (targetAngle - currentAngle > 30.0f) {
            player->unk_4C = targetAngle - 30.0f;
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        } else if (targetAngle - currentAngle < -30.0f) {
            player->unk_4C = targetAngle + 30.0f;
            if (player->unk_20 != 0) {
                player->unk_20 = 0;
                HuAudFXStop(player->unk_22);
            }
        }
        Hu3DModelRotSet(player->unk_48, 0.0f, player->unk_4C, 0.0f);
        object->rot.y = player->unk_4C;
    }
}

void func_801096E8_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    BabyBowserBroadsideEntry *entry = player->unk_54;
    s16 i = 0;
    s16 index;

    if ((u16)player->unk_04 != 0) {
        i = (u16)player->unk_04;
        func_801099D4_baby_bowser_broadside(object, &player->unk_54[(s16)(i - 1)], player->unk_4C, player->unk_5A);
        player->unk_04 &= 0xFFFF0000;
        HuAudFXPlay(0x35A);
    }
    for (i = 0; i < 3; i++, entry++) {
        if (entry->unk_00 != 0) {
            entry->unk_2C->facing.x = entry->velocity.x;
            entry->unk_2C->facing.y = entry->velocity.y;
            entry->unk_2C->facing.z = entry->velocity.z;
            func_8010E0B0_baby_bowser_broadside(entry->unk_2C);
            entry->elapsed += 1.0f;
            entry->velocity.y = entry->initialVelocityY - entry->elapsed * 2.45f;
            if (entry->unk_2C->unk_2A != 0) {
                func_801098F8_baby_bowser_broadside(entry);
            } else if (entry->unk_2C->unk_30 != 0) {
                HuAudFXPlay(0x35B);
                func_801098F8_baby_bowser_broadside(entry);
                index = func_8010AADC_baby_bowser_broadside(entry->unk_28 + 2);
                if (index != -1) {
                    func_8010AB80_baby_bowser_broadside(index, entry->unk_2C->pos.x, entry->unk_2C->pos.y, entry->unk_2C->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                }
                if (D_80110008_baby_bowser_broadside->unk_00 & 2) {
                    D_80110000_baby_bowser_broadside[player->unk_5A].unk_10++;
                }
                func_80108804_baby_bowser_broadside(entry->angle);
            }
            if (!(entry->unk_2C->unk_00 & 1)) {
                func_801098F8_baby_bowser_broadside(entry);
            }
        }
    }
}

void func_801098F8_baby_bowser_broadside(BabyBowserBroadsideEntry *entry) {
    s16 index = func_8010AADC_baby_bowser_broadside(entry->unk_28);

    func_8010AB80_baby_bowser_broadside(index, entry->unk_2C->pos.x, entry->unk_2C->pos.y, entry->unk_2C->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    func_8001C258_main(entry->unk_02, 4, 4);
    entry->unk_00 = 0;
}

s16 func_80109970_baby_bowser_broadside(unk_80109EBC *arg0) {
    s16 i;

    for (i = 0; i < 3; i++) {
        if (arg0->unk_54[i].unk_00 == 0) {
            break;
        }
    }
    if (i == 3) {
        return -1;
    }
    return i;
}

void func_801099D4_baby_bowser_broadside(omObjData *object, BabyBowserBroadsideEntry *entry, f32 angle, s16 team) {
    f32 sinAngle, cosAngle;
    f32 x, z;
    s16 index;
    u8 color[4];

    sinAngle = sindf(angle);
    cosAngle = cosdf(angle);
    x = sinAngle * 100.0f;
    z = cosAngle * 100.0f;
    Hu3DModelPosSet(entry->unk_02, x + object->trans.x, 500.0f, z + object->trans.z);
    entry->velocity.x = entry->unk_04.x = sinAngle * 50.0f;
    entry->velocity.y = sindf(22.5f) * 30.000002f;
    entry->velocity.z = entry->unk_04.z = cosAngle * 50.0f;
    entry->initialVelocityY = entry->velocity.y;
    entry->elapsed = 0.0f;
    entry->angle = angle;
    entry->unk_00 = 1;
    func_8001C258_main(entry->unk_02, 4, 0);
    x = sinAngle * 180.0f;
    z = cosAngle * 180.0f;
    entry->unk_28 = team;
    index = func_8010AFF4_baby_bowser_broadside(0);
    if (index != -1) {
        if (team == 0) {
            color[0] = 255;
            color[1] = 191;
            color[2] = 191;
            color[3] = 255;
        } else {
            color[0] = 165;
            color[1] = 204;
            color[2] = 229;
            color[3] = 255;
        }
        func_8010B098_baby_bowser_broadside(index, x + object->trans.x, 469.99997f, z + object->trans.z, color);
    }
    omVibrate(object->work[0], 10, 0, 10);
}

void func_80109BD8_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    f32 progress;

    if ((s8)handler->unk_04 == 0) {
        handler->unk_1C = 0;
        handler->unk_2C = object->rot.y;
        handler->unk_30 = 0.0f;
        func_8010F6F8_baby_bowser_broadside(&handler->unk_2C, &handler->unk_30);
        func_80109EB0_baby_bowser_broadside(player, 2, 1);
        player->unk_0C = -1;
        handler->unk_04 = 1;
    }
    progress = handler->unk_1C / 20.0f;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    object->rot.y = (handler->unk_30 - handler->unk_2C) * progress + handler->unk_2C;
    if (++handler->unk_1C > 20.0f) {
        func_80109EB0_baby_bowser_broadside(player, 0, 1);
        object->rot.y = 0.0f;
        handler->unk_1C = 20;
        if (D_8010FD60_baby_bowser_broadside != 0) {
            func_80109EB0_baby_bowser_broadside(player, 13, 1);
            func_8010A158_baby_bowser_broadside((s8)object->work[1], handler);
        }
    }
}

void func_80109D2C_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;

    if (D_8010FD60_baby_bowser_broadside != 0) {
        func_80109EB0_baby_bowser_broadside(player, 14, 1);
        player->unk_0C = -1;
        func_8010A158_baby_bowser_broadside((s8)object->work[1], handler);
    }
}

void func_80109D94_baby_bowser_broadside(BabyBowserBroadsideSlot *slot, BabyBowserBroadsideHandler *handler) {
    unk_80109EBC *player = (unk_80109EBC *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &HmfModelData[object->model[0]];

    if (model->unk40 >= D_800CCF58_main[model->unk02].unk02 - 1) {
        player->unk_08 = 1;
    }
    if (player->unk_08 != 0) {
        func_800E5690_minigame(object, player->unk_0A);
        if (player->unk_0A == 13) {
            func_80045ED0_main(D_800A178C_main[GwPlayer[object->work[0]].chr][0] | 0x2F);
        }
        player->unk_08 = 0;
        if (player->unk_0C != -1) {
            player->unk_0A = player->unk_0C;
            player->unk_0C = -1;
        }
    }
}

void func_80109EB0_baby_bowser_broadside(unk_80109EBC *player, s16 motion, s8 arg2) {
    player->unk_08 = arg2;
    player->unk_0A = motion;
}

void func_80109EBC_baby_bowser_broadside(unk_80109EBC *arg0, s16 arg1) {
    arg0->unk_0C = arg1;
}
