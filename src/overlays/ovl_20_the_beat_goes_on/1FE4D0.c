#include "common.h"
#include "game/camera.h"
#include "game/audio.h"
#include "game/camsetup.h"
#include "game/gamemes.h"
#include "game/hmfanim.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "math.h"
#include "overlays/minigame.h"

// Grid position of a single marker in the "Beat Goes On" note field.
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} BeatGoesOnPos; // sizeof 0x4

// Note/scoring state block hanging off omObjData::data for one "Beat Goes On" grid.
typedef struct {
    /* 0x00 */ u8 unk_00[0x16];
    /* 0x16 */ s8 unk_16;
    /* 0x17 */ s8 unk_17;
    /* 0x18 */ s8 unk_18;
    /* 0x19 */ s8 unk_19;
    /* 0x1A */ s8 noteFlags[15];
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ s8 btnA[16];
    /* 0x3A */ s8 btnB[16];
    /* 0x4A */ s8 btnZ[16];
} BeatGoesOnNotes; // sizeof 0x5A

// Work data for each player object.
typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u8 unk_0C[4];
    /* 0x10 */ s8 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ HmfModelEntry *entry;
    /* 0x1C */ s8 unk_1C;
} BeatGoesOnPlayerWork; // sizeof 0x20

// Work data for the conductor object.
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s8 unk_02;
} BeatGoesOnConductorWork; // sizeof 0x4

// One entry in the sequence of buttons the player must press.
typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s16 unk_02;
} BeatGoesOnButton; // sizeof 0x4

extern s32 D_8010C2E4_the_beat_goes_on;
extern s32 D_8010C2E8_the_beat_goes_on;
extern s8 D_8010C2EC_the_beat_goes_on;
extern BeatGoesOnPos D_8010C2F0_the_beat_goes_on[];
extern s32 D_8010C328_the_beat_goes_on[][4];
extern f32 D_8010C368_the_beat_goes_on[];
extern s8 D_8010C474_the_beat_goes_on;
extern D_80111B50_vine_with_me_Struct D_8010C478_the_beat_goes_on;
extern BeatGoesOnButton D_8010C4A0_the_beat_goes_on[16];
extern omObjData *D_8010C4E0_the_beat_goes_on;
extern omObjData *D_8010C4E4_the_beat_goes_on;
extern s8 D_8010C4E8_the_beat_goes_on;
extern s8 D_8010C4E9_the_beat_goes_on;
extern u8 D_8010C4EA_the_beat_goes_on;
extern s16 D_8010C4EC_the_beat_goes_on[4];
extern s16 D_8010C4F4_the_beat_goes_on;
extern s16 D_8010C4F6_the_beat_goes_on;
extern s16 D_8010C4F8_the_beat_goes_on;
extern s16 D_8010C4FA_the_beat_goes_on;
extern u16 D_8010C500_the_beat_goes_on[2];
extern f32 D_8010C504_the_beat_goes_on;
extern u8 D_800D6A90_main;

void func_80105C68_the_beat_goes_on(D_80111B50_vine_with_me_Struct *arg0);
void func_80105CDC_the_beat_goes_on(void);
void func_801060B0_the_beat_goes_on(f32 speed);
void func_80106358_the_beat_goes_on(omObjData *object);
void func_80106708_the_beat_goes_on(omObjData *obj);
void func_80107504_the_beat_goes_on(omObjData *obj);
void func_8010775C_the_beat_goes_on(omObjData *obj);
void func_801080DC_the_beat_goes_on(void);
u16 func_80108198_the_beat_goes_on(s8 index);
void func_80108324_the_beat_goes_on(omObjData *obj);
void func_8010B058_the_beat_goes_on(omObjData *obj);
void func_8010B0E0_the_beat_goes_on(omObjData *obj);
void func_8010B17C_the_beat_goes_on(omObjData *obj);

void func_801059A0_the_beat_goes_on(void) {
    s16 model;
    s32 i;

    func_8001FE20_main(0x20);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CDC_the_beat_goes_on();
    func_80105C68_the_beat_goes_on(&D_8010C478_the_beat_goes_on);
    func_800E5EA0_minigame(&D_8010C478_the_beat_goes_on);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80106358_the_beat_goes_on), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(0, 1, 0, -1, func_8010B058_the_beat_goes_on), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010C4E0_the_beat_goes_on = omAddObj(0, 4, 5, -1, func_80107504_the_beat_goes_on);
    model = func_8000B108_main(0x41000A, 0x819);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            D_8010C4EC_the_beat_goes_on[i] = model;
        } else {
            D_8010C4EC_the_beat_goes_on[i] = Hu3DModelLink(model);
        }
        func_8001C258_main(D_8010C4EC_the_beat_goes_on[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    D_8010C4E4_the_beat_goes_on = omAddObj(1, 0, 0, -1, func_8010B17C_the_beat_goes_on);
    omSetStatBit(D_8010C4E4_the_beat_goes_on, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010C4EA_the_beat_goes_on = rand8() * 3U / 32;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(2, 7, 10, -1, func_80108324_the_beat_goes_on);
    }
    for (i = 0; i < 5; i++) {
        omSetStatBit(omAddObj(3, 4, 2, -1, func_80106708_the_beat_goes_on), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80105C68_the_beat_goes_on(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    arg0->unk00 = 0;
    arg0->unk01 = 0;
    arg0->unk02 = 2;
    arg0->unk03 = 0;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 0;
    arg0->unk1C = 64;
    arg0->unk1E = -1;
    arg0->unk20 = 0;
    arg0->unk22 = -1;
    arg0->unk24 = 150;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105CDC_the_beat_goes_on(void) {
    s32 camIndex;

    Center.x = 0.0f;
    Center.y = 110.0f;
    Center.z = 140.0f;
    CRot.x = -40.0f;
    CRot.y = CRot.z = Center.x;
    CZoom = 1060.0f;
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 30.0f, 80.0f, 8000.0f);
}

void func_80105E0C_the_beat_goes_on(f32 speed) {
    f32 zoomStep = 1500.0f;
    f32 centerStep = -500.0f;
    f32 rotStep = -20.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z < 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x < -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &screenPos);
    HuSprPosSet(D_8010C4F4_the_beat_goes_on, 0, 160, screenPos.y + -50.0f);
}

void func_80105F60_the_beat_goes_on(f32 speed) {
    f32 zoomStep = -1500.0f;
    f32 centerStep = 500.0f;
    f32 rotStep = 20.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom < 700.0f) {
        CZoom = 700.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z > 880.0f) {
        Center.z = 880.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x > -10.0f) {
        CRot.x = -10.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &screenPos);
    HuSprPosSet(D_8010C4F4_the_beat_goes_on, 0, 160, screenPos.y + -50.0f);
}

void func_801060B0_the_beat_goes_on(f32 speed) {
    f32 zoomStep = 1140.0f;
    f32 centerStep = 240.0f;
    f32 rotStep = 10.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom > 2200.0f) {
        CZoom = 2200.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z > 380.0f) {
        Center.z = 380.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x > -30.0f) {
        CRot.x = -30.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &screenPos);
    HuSprPosSet(D_8010C4F4_the_beat_goes_on, 0, 160, screenPos.y + -50.0f);
}

void func_80106204_the_beat_goes_on(f32 speed) {
    f32 zoomStep = -1140.0f;
    f32 centerStep = -240.0f;
    f32 rotStep = -10.0f;
    Vec pos;
    Vec2f screenPos;

    CZoom += zoomStep / speed;
    if (CZoom < 1060.0f) {
        CZoom = 1060.0f;
    }
    Center.z += centerStep / speed;
    if (Center.z < 140.0f) {
        Center.z = 140.0f;
    }
    CRot.x += rotStep / speed;
    if (CRot.x < -40.0f) {
        CRot.x = -40.0f;
    }
    pos.x = 0.0f;
    pos.y = -100.0f;
    pos.z = -1794.6355f;
    func_80012B14_main(0, &pos, &screenPos);
    HuSprPosSet(D_8010C4F4_the_beat_goes_on, 0, 160, screenPos.y + -50.0f);
}

void func_80106358_the_beat_goes_on(omObjData *object) {
    omObjData *player;
    s32 i;

    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_8010C2EC_the_beat_goes_on == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            func_800E6F0C_minigame(5);
            D_8010C2EC_the_beat_goes_on = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                if (func_800E6E9C_minigame() == 16) {
                    HuAudSeqPlay(0x3F);
                    HuAudFXPlay(0x40B);
                } else if (func_800E6E9C_minigame() >= 27) {
                    func_801060B0_the_beat_goes_on(40.0f);
                }
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                if (D_8010C2E8_the_beat_goes_on == 0) {
                    func_8004AB0C_main(30);
                    if (D_8010C478_the_beat_goes_on.unk06 == 0) {
                        player = D_800EC598_minigame[D_8010C478_the_beat_goes_on.unk18[0]];
                        func_8001C258_main(player->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        func_8001C258_main(player->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        func_8001C258_main(player->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                } else if (D_8010C2E8_the_beat_goes_on == 30 && D_8010C478_the_beat_goes_on.unk06 == 4) {
                    for (i = 0; i < 4; i++) {
                        player = D_800EC598_minigame[i];
                        if (player->work[0] == 10) {
                            func_8001C258_main(player->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        } else {
                            func_800E4C88_minigame(player, 6, player->trans.x, -50.0f, player->trans.z + 50.0f, 45.0f,
                                                   0.0f);
                            func_8001C258_main(player->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            func_8001C258_main(player->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            func_8001C258_main(player->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                    }
                }
                D_8010C2E8_the_beat_goes_on++;
                break;
            case 4:
                if (func_800E6E9C_minigame() == 1) {
                    switch (D_8010C478_the_beat_goes_on.unk06) {
                        case 0:
                            GMesCreate(0x16, GwPlayer[D_8010C478_the_beat_goes_on.unk18[0]].chr);
                            HuAudSeqPlay(0x65);
                            break;
                        case 4:
                            GMesCreate(0x20);
                            HuAudSeqPlay(0x6C);
                            break;
                    }
                    D_8010C478_the_beat_goes_on.unk06 = 9;
                }
                break;
            case 5:
                if (D_8010C2E4_the_beat_goes_on == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010C2E4_the_beat_goes_on++;
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106708_the_beat_goes_on);

void func_80106BE0_the_beat_goes_on(omObjData *obj) {
    BeatGoesOnPlayerWork *work = obj->data;
    HmfModelEntry *entry = work->entry;
    u16 modelId = entry->modelId;
    HmfAnimRot *rot;
    s16 frame;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 x;
    f32 y;
    f32 z;

    obj->rot.x = CRot.x;
    obj->rot.y = CRot.y;
    obj->rot.z = CRot.z;
    Hu3DModelRotSet(modelId, obj->rot.x, obj->rot.y, obj->rot.z);
    rot = &D_800D408C_main[(u16)entry->unk_02].rot[entry->pointIdx];
    frame = rot->frames[entry->nodeIdx].unk00;
    ox = D_8010C2F0_the_beat_goes_on[frame].x - 16;
    oy = 16 - D_8010C2F0_the_beat_goes_on[frame].y;
    oz = 0.0f;
    x = ox * cosdf(CRot.y) + sindf(CRot.y) * oz;
    y = oy * cosdf(CRot.x) - sindf(CRot.x) * oz;
    z = oy * sindf(CRot.x) + sindf(CRot.x) * oz - ox * sindf(CRot.y) + cosdf(CRot.y) * oz;
    x *= obj->scale.x;
    y *= obj->scale.y;
    z *= obj->scale.z;
    x += obj->trans.x;
    y += obj->trans.y;
    z += obj->trans.z;
    Hu3DModelPosSet(obj->model[3], x, y, z);
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    Hu3DModelRotSet(obj->model[3], CRot.x, CRot.y, CRot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106E40_the_beat_goes_on);

void func_80107504_the_beat_goes_on(omObjData *obj) {
    BeatGoesOnConductorWork *work;

    obj->func = func_8010775C_the_beat_goes_on;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    obj->work[0] = 0;
    obj->data = HuMemAllocTag(sizeof(BeatGoesOnConductorWork), TAG_OVERLAY);
    memset(obj->data, 0, sizeof(BeatGoesOnConductorWork));
    work = obj->data;
    work->unk_00 = 0;
    work->unk_02 = 0;
    obj->model[0] = func_8000B108_main(0xA014D, 0x2D9);
    D_8010C4F6_the_beat_goes_on = obj->model[1] = func_8000B108_main(0x410009, 0x2D9);
    D_8010C4F8_the_beat_goes_on = obj->model[2] = func_8000B108_main(0x410008, 0x2D9);
    D_8010C4FA_the_beat_goes_on = obj->model[3] = func_8000B108_main(0x410007, 0x2D9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    func_8001C814_main(obj->model[1], 2, 1);
    func_8001C814_main(obj->model[2], 2, 1);
    func_8001C814_main(obj->model[3], 2, 1);
    func_8000B460_main(obj, 4, 0x410009);
    func_8000B460_main(obj, 0, 0xA014F);
    func_8000B460_main(obj, 1, 0xA0150);
    func_8000B460_main(obj, 2, 0xA0151);
    func_8000B460_main(obj, 3, 0xA0152);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C814_main(obj->model[3], 2, 2);
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
    func_801080DC_the_beat_goes_on();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010775C_the_beat_goes_on);

void func_801080DC_the_beat_goes_on(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010C4A0_the_beat_goes_on[i].button = func_80108198_the_beat_goes_on(i);
        if (i == 0) {
            D_8010C4A0_the_beat_goes_on[i].unk_02 = 26;
        } else {
            D_8010C4A0_the_beat_goes_on[i].unk_02 = 22;
        }
    }
    for (i = 4; i < 16; i++) {
        D_8010C4A0_the_beat_goes_on[i].button = 0;
        D_8010C4A0_the_beat_goes_on[i].unk_02 = 22;
    }
}

u16 func_80108198_the_beat_goes_on(s8 index) {
    u16 prev;
    u8 roll;

    if (index == 0) {
        prev = 0;
    } else {
        prev = D_8010C4A0_the_beat_goes_on[index - 1].button;
    }
    roll = rand8() % 30;
    if (roll < 10) {
        if (prev == A_BUTTON) {
            roll = rand8() % 20;
            if (roll < 10) {
                return B_BUTTON;
            } else {
                return Z_TRIG;
            }
        }
        return A_BUTTON;
    } else if (roll < 20) {
        if (prev == B_BUTTON) {
            roll = rand8() % 20;
            if (roll < 10) {
                return A_BUTTON;
            } else {
                return Z_TRIG;
            }
        }
        return B_BUTTON;
    } else if (prev == Z_TRIG) {
        roll = rand8() % 20;
        if (roll >= 10) {
            return B_BUTTON;
        }
        return A_BUTTON;
    }
    return Z_TRIG;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108324_the_beat_goes_on);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", D_8010C3B8_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108810_the_beat_goes_on);

#ifdef NON_MATCHING
u16 func_8010A5FC_the_beat_goes_on(func_800E1BA8_minigame_ObjData *data) {
    u16 button = 0;
    u8 roll;
    s32 chance;

    if (!(GwPlayer[data->unk59].stat & 1)) {
        return D_800D5558_main[data->unk57];
    }
    if (D_8010C4E9_the_beat_goes_on == D_8010C4E8_the_beat_goes_on &&
        D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button == 0) {
        button = func_80108198_the_beat_goes_on(D_8010C4E9_the_beat_goes_on);
    } else {
        roll = rand8() * 100 / 256;
        switch (GwPlayer[data->unk59].cpu_difficulty) {
            case 1:
                chance = 65;
                break;
            case 3:
                chance = 95;
                break;
            case 0:
                chance = 50;
                break;
            case 2:
                chance = 85;
                break;
            default:
                chance = 65;
                break;
        }
        if (D_8010C4E9_the_beat_goes_on < 5) {
            chance = 99;
        } else if (D_8010C4E9_the_beat_goes_on >= 13) {
            if (GwPlayer[data->unk59].cpu_difficulty == 0) {
                chance = 45;
            } else {
                chance = 50;
            }
        } else if (D_8010C4E9_the_beat_goes_on >= 9) {
            chance -= 5;
        }
        if (roll < chance) {
            button = D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button;
        } else if (D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button == A_BUTTON) {
            button = Z_TRIG;
            if (rand8() >> 7) {
                button = B_BUTTON;
            }
        } else if (D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button == B_BUTTON) {
            button = A_BUTTON;
            if (rand8() >> 7) {
                button = Z_TRIG;
            }
        } else if (D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button == Z_TRIG) {
            button = B_BUTTON;
            if (rand8() >> 7) {
                button = A_BUTTON;
            }
        }
    }
    return button;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A5FC_the_beat_goes_on);
#endif

void func_8010A88C_the_beat_goes_on(u16 button) {
    BeatGoesOnNotes *notes = (BeatGoesOnNotes *)D_8010C4E4_the_beat_goes_on->data;

    if (button == A_BUTTON) {
        notes->btnA[D_8010C4E9_the_beat_goes_on] = 1;
    } else if (button == B_BUTTON) {
        notes->btnB[D_8010C4E9_the_beat_goes_on] = 1;
    } else if (button == Z_TRIG) {
        notes->btnZ[D_8010C4E9_the_beat_goes_on] = 1;
    }
    if (D_8010C4E9_the_beat_goes_on == D_8010C4E8_the_beat_goes_on) {
        notes->unk_18 = 0;
        D_8010C4A0_the_beat_goes_on[D_8010C4E9_the_beat_goes_on].button = button;
    } else {
        notes->noteFlags[D_8010C4E9_the_beat_goes_on] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A94C_the_beat_goes_on);

void func_8010AD60_the_beat_goes_on(s8 *state, f32 speed) {
    switch (*state) {
        case 0:
            func_80105E0C_the_beat_goes_on(speed / 2.0f);
            if (CZoom == 2200.0f && Center.z == 380.0f && CRot.x == -30.0f) {
                *state = 1;
            }
            break;
        case 1:
            if (D_8010C474_the_beat_goes_on > 40) {
                D_8010C474_the_beat_goes_on = 0;
                *state = 2;
            } else {
                D_8010C474_the_beat_goes_on++;
            }
            break;
        case 2:
            func_80105F60_the_beat_goes_on(speed / 2.0f);
            if (CZoom == 700.0f && Center.z == 880.0f && CRot.x == -10.0f) {
                *state = 3;
            }
            break;
    }
}

#ifdef NON_MATCHING
void func_8010AF10_the_beat_goes_on(omObjData *obj) {
    func_800E1BA8_minigame_ObjData *data = obj->data;
    s32 player = data->unk59;
    s32 i = 0;
    s32 *timers = D_8010C328_the_beat_goes_on[player];
    f32 scale;

    for (; i < 4; i++) {
        if (timers[i] >= 0) {
            if (timers[i] == 0) {
                Hu3DModelPosSet(D_8010C4EC_the_beat_goes_on[i], obj->trans.x, obj->trans.y, obj->trans.z);
                func_8001C258_main(D_8010C4EC_the_beat_goes_on[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (timers[i] < 8) {
                scale = D_8010C368_the_beat_goes_on[timers[i] / 2];
                Hu3DModelScaleSet(D_8010C4EC_the_beat_goes_on[i], scale, scale, 1.0f);
            }
            if (timers[i] >= 8) {
                timers[i] = -1;
            }
        }
        timers[i]++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010AF10_the_beat_goes_on);
#endif

void func_8010B058_the_beat_goes_on(omObjData *obj) {
    obj->func = func_8010B0E0_the_beat_goes_on;
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->model[0] = func_8000B108_main(0x410005, 0x699);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main("mizu_DEF", D_8010C500_the_beat_goes_on);
    D_8010C504_the_beat_goes_on = 0.0f;
}

void func_8010B0E0_the_beat_goes_on(omObjData *obj) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010C504_the_beat_goes_on += 0.2f;
    }
    func_8001E888_main(obj->model[0], 0.0f, D_8010C504_the_beat_goes_on, D_8010C500_the_beat_goes_on[0],
                       D_8010C500_the_beat_goes_on[1], "m232_001c-cube7", 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B17C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B6DC_the_beat_goes_on);

void func_8010C0F4_the_beat_goes_on(BeatGoesOnPos *pos) {
    if (D_8010C4E9_the_beat_goes_on < 8) {
        pos->x = D_8010C4E9_the_beat_goes_on * 30 + 55;
        pos->y = 30;
    } else {
        pos->x = (D_8010C4E9_the_beat_goes_on - 8) * 30 + 55;
        pos->y = 50;
    }
}

void func_8010C14C_the_beat_goes_on(void) {
    BeatGoesOnNotes *notes = (BeatGoesOnNotes *)D_8010C4E4_the_beat_goes_on->data;
    s32 i;

    notes->unk_19 = 0;
    notes->unk_18 = 0;
    notes->unk_17 = 0;
    notes->unk_16 = 0;
    for (i = 0; i < 16; i++) {
        // The note field only has 15 slots, but the button arrays have 16.
        if (i < 15) {
            notes->noteFlags[i] = 0;
        }
        notes->btnA[i] = 0;
        notes->btnB[i] = 0;
        notes->btnZ[i] = 0;
    }
}

Vec *func_8010C1A4_the_beat_goes_on(Vec *out, Vec *from, Vec *to) {
    Vec dir;
    f32 len;

    dir.x = to->x - from->x;
    dir.y = to->y - from->y;
    dir.z = to->z - from->z;
    len = HuSqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (len == 0.0f) {
        dir.x = dir.y = dir.z = 0.0f;
    } else {
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
    }
    *out = dir;
    return out;
}
