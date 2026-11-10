#include "common.h"
#include "overlays/minigame.h"

typedef struct UnkMstory2Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory2Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011B920_mstory2;
extern Vec D_8011B92C_mstory2;
extern Vec D_8011B938_mstory2;

extern s16 D_8011B944_mstory2;
extern void (*const D_8011BDE0_mstory2[])(void);
extern const s32 D_8011BDF4_mstory2[];
extern s16 D_8011B946_mstory2;
extern s16 D_8011B948_mstory2;
extern s32 D_8011B94C_mstory2;
extern const Vec D_8011BE80_mstory2;
extern const Vec D_8011BE8C_mstory2;
extern const Vec D_8011BE98_mstory2;
extern const Vec D_8011C000_mstory2;
extern const Vec D_8011C024_mstory2;
extern const Vec D_8011C3F0_mstory2;
extern const Vec D_8011C204_mstory2;
extern const Vec D_8011C5DC_mstory2;
extern const Vec D_8011C03C_mstory2;
extern const Vec D_8011C06C_mstory2;
extern const Vec D_8011C078_mstory2;
extern const Vec D_8011C1E0_mstory2;
extern const Vec D_8011C21C_mstory2;
extern const Vec D_8011C228_mstory2;
extern const Vec D_8011C258_mstory2;
extern const Vec D_8011C264_mstory2;
extern const Vec D_8011C3CC_mstory2;
extern const Vec D_8011C408_mstory2;
extern const Vec D_8011C444_mstory2;
extern const Vec D_8011C414_mstory2;
extern const Vec D_8011C450_mstory2;
extern const Vec D_8011C5B8_mstory2;
extern const Vec D_8011C5F4_mstory2;
extern const Vec D_8011C600_mstory2;
extern s16 D_8011C640_mstory2;
extern s16 D_8011C642_mstory2;
extern s16 D_8011C644_mstory2;
extern u16 D_8011C646_mstory2;
extern s16 D_8011C648_mstory2;
extern s32 D_8011C674_mstory2;
extern UnkMstory2Obj D_8011C680_mstory2[6];
extern Vec D_8011C710_mstory2;
extern Vec D_8011C71C_mstory2;
extern Vec D_8011C728_mstory2;
extern Vec D_8011C7FC_mstory2;
extern Vec D_8011C8DC_mstory2;
extern Vec D_8011C9BC_mstory2;
extern s16 D_8011C740_mstory2[3];
extern s16 D_8011C746_mstory2;
extern const Vec D_8011C030_mstory2;
extern s16 D_8011C748_mstory2;
extern s16 D_8011C75A_mstory2;
extern s16 D_8011C75C_mstory2;
extern s16 D_8011C75E_mstory2;
extern UnkMstory2Obj D_8011C760_mstory2[6];
extern Vec D_8011C808_mstory2;
extern s16 D_8011C820_mstory2[3];
extern Vec D_8011C7F0_mstory2;
extern const Vec D_8011C060_mstory2;
extern s16 D_8011C826_mstory2;
extern const Vec D_8011C210_mstory2;
extern s16 D_8011C828_mstory2;
extern s16 D_8011C83A_mstory2;
extern s16 D_8011C83C_mstory2;
extern s16 D_8011C83E_mstory2;
extern UnkMstory2Obj D_8011C840_mstory2[6];
extern Vec D_8011C8E8_mstory2;
extern s16 D_8011C900_mstory2[3];
extern Vec D_8011C8D0_mstory2;
extern const Vec D_8011C24C_mstory2;
extern s16 D_8011C906_mstory2;
extern const Vec D_8011C3FC_mstory2;
extern s16 D_8011C908_mstory2;
extern s16 D_8011C91A_mstory2;
extern s16 D_8011C91C_mstory2;
extern s16 D_8011C91E_mstory2;
extern UnkMstory2Obj D_8011C920_mstory2[6];
extern Vec D_8011C9C8_mstory2;
extern s16 D_8011C9E0_mstory2[3];
extern Vec D_8011C9B0_mstory2;
extern const Vec D_8011C438_mstory2;
extern s16 D_8011C9E6_mstory2;
extern const Vec D_8011C5E8_mstory2;
extern s16 D_8011C9E8_mstory2;
extern s16 D_8011C9FA_mstory2;
extern s16 D_8011C9FC_mstory2;
extern s16 D_8011C9FE_mstory2;
extern UnkMstory2Obj D_8011CA10_mstory2[3];
extern s16 D_8011CA74_mstory2[3];
extern Vec D_8011CA50_mstory2;
extern const Vec D_8011C60C_mstory2;
extern s16 D_8011CA7A_mstory2;
extern s16 D_8011CA80_mstory2[4];
extern s16 D_8011CA4C_mstory2;
extern f32 D_8011BDD0_mstory2;
extern Vec D_8011CA5C_mstory2;
extern const Vec D_8011C618_mstory2;
extern f32 D_8011BDD4_mstory2;
extern f32 D_8011BDD8_mstory2;
extern s16 D_8011C74E_mstory2;
extern s16 D_8011C750_mstory2;
extern s16 D_8011C74A_mstory2[2];
extern const Vec D_8011BFF4_mstory2;
extern s16 D_8011C752_mstory2[2];
extern const Vec D_8011C00C_mstory2;
extern s16 D_8011C832_mstory2[2];
extern const Vec D_8011C1EC_mstory2;
extern s16 D_8011C912_mstory2[2];
extern const Vec D_8011C3D8_mstory2;
extern s16 D_8011C9F2_mstory2[2];
extern const Vec D_8011C5C4_mstory2;
extern s16 D_8011C82A_mstory2[2];
extern const Vec D_8011C1D4_mstory2;
extern s16 D_8011C90A_mstory2[2];
extern const Vec D_8011C3C0_mstory2;
extern s16 D_8011C9EA_mstory2[2];
extern const Vec D_8011C5AC_mstory2;
extern s16 D_8011C756_mstory2;
extern s16 D_8011C758_mstory2;
extern s16 D_8011C82E_mstory2;
extern s16 D_8011C830_mstory2;
extern s16 D_8011C836_mstory2;
extern s16 D_8011C838_mstory2;
extern s16 D_8011C90E_mstory2;
extern s16 D_8011C910_mstory2;
extern s16 D_8011C916_mstory2;
extern s16 D_8011C918_mstory2;
extern s16 D_8011C9EE_mstory2;
extern s16 D_8011C9F0_mstory2;
extern s16 D_8011C9F6_mstory2;
extern s16 D_8011C9F8_mstory2;
extern f32 D_8011CA04_mstory2;

void func_80105C1C_mstory2(void);
void func_80105DB4_mstory2(omObjData *obj);
void func_80105F94_mstory2(omObjData *obj);
void func_801063B0_mstory2(void);
void func_80105EC4_mstory2(omObjData *);
void func_80105F4C_mstory2(omObjData *);
void func_80105FBC_mstory2(void);
void func_80106D58_mstory2(s16 model, s16 arg1, s16 arg2);
void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801070D8_mstory2(omObjData *obj, Vec *pos, s32 frames);
s32 func_801072F8_mstory2(s16 model);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
void func_801076DC_mstory2(omObjData *obj, omObjData *target);
void func_8010889C_mstory2(omObjData *);
void func_8010A61C_mstory2(omObjData *);
void func_8010BCE4_mstory2(omObjData *obj);
void func_8010A5FC_mstory2(omObjData *obj);
void func_8010F2D8_mstory2(omObjData *obj);
void func_80113F68_mstory2(omObjData *obj);
void func_80118C14_mstory2(omObjData *obj);
void func_8010BF7C_mstory2(omObjData *obj);
void func_80110BA8_mstory2(omObjData *obj);
void func_80115860_mstory2(omObjData *obj);
void func_8011A4E4_mstory2(omObjData *obj);
void func_801155C8_mstory2(omObjData *obj);
void func_80110910_mstory2(omObjData *obj);
void func_8011A24C_mstory2(omObjData *obj);
void func_8010D21C_mstory2(omObjData *);
void func_8010F2F8_mstory2(omObjData *);
void func_80113F88_mstory2(omObjData *);
void func_80118C34_mstory2(omObjData *);
void func_80111EAC_mstory2(omObjData *);
void func_80116B6C_mstory2(omObjData *);
void func_801064AC_mstory2(void);
void func_8011AB84_mstory2(void);
void func_8011AC08_mstory2(void);
void func_8011AC10_mstory2(omObjData *);
void func_8011AD8C_mstory2(omObjData *);
void func_8011B080_mstory2(omObjData *);
void func_80108AB0_mstory2(omObjData *);
void func_80108C40_mstory2(omObjData *);
void func_8010D5C0_mstory2(omObjData *);
void func_80112250_mstory2(omObjData *);
void func_80116F0C_mstory2(omObjData *);
void func_801120C0_mstory2(omObjData *);
void func_80116D80_mstory2(omObjData *);
void func_8011B198_mstory2(void);
void func_8011AB7C_mstory2(omObjData *obj);
void func_8011B45C_mstory2(void);
void func_8011B64C_mstory2(void);
void func_8011B818_mstory2(void);
void func_8011B820_mstory2(omObjData *obj);
void func_80109D04_mstory2(void);
void func_8010AC1C_mstory2(void);
void func_8010B7B8_mstory2(void);
void func_8010BAC4_mstory2(void);
void func_8010C038_mstory2(void);
void func_8010C398_mstory2(void);
void func_80108A3C_mstory2(void);
void func_8010C1E4_mstory2(void);
void func_801088A4_mstory2(void);
void func_8010E9E0_mstory2(void);
void func_8010F8F8_mstory2(void);
void func_801103E4_mstory2(void);
void func_801106F0_mstory2(void);
void func_80110C64_mstory2(void);
void func_80111024_mstory2(void);
void func_8010C1DC_mstory2(void);
void func_80110E08_mstory2(void);
void func_80115AC0_mstory2(void);
void func_8011A744_mstory2(void);
void func_8010C508_mstory2(void);
void func_80111194_mstory2(void);
void func_80115E4C_mstory2(void);
void func_8011AAD0_mstory2(void);
void func_8010D3BC_mstory2(void);
void func_80110E10_mstory2(void);
void func_8010D224_mstory2(void);
void func_80113670_mstory2(void);
void func_80114588_mstory2(void);
void func_8011509C_mstory2(void);
void func_801153A8_mstory2(void);
void func_8011591C_mstory2(void);
void func_80115CDC_mstory2(void);
void func_8011204C_mstory2(void);
void func_80115AC8_mstory2(void);
void func_80111EB4_mstory2(void);
void func_8011831C_mstory2(void);
void func_80119234_mstory2(void);
void func_80119D20_mstory2(void);
void func_8011A02C_mstory2(void);
void func_8011A5A0_mstory2(void);
void func_8011A960_mstory2(void);
void func_80116D0C_mstory2(void);
void func_8011A74C_mstory2(void);
void func_80116B74_mstory2(void);

void func_801059A0_mstory2(void) {
    func_80105C1C_mstory2();
}

void func_801059BC_mstory2(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory2(omObjData *obj) {
    D_800CE17C_main[0] = D_8011B920_mstory2.x;
    D_800CE17C_main[1] = D_8011B920_mstory2.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_8011B920_mstory2, &D_8011B92C_mstory2, &D_8011B938_mstory2);
    Hu3DCamUpdateMtx(0);
}

void func_80105A64_mstory2(void) {
    omObjData *obj;

    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_801059E4_mstory2);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_801059E4_mstory2(obj);
}

void func_80105B44_mstory2(void) {
    HuWinInit();
}

void func_80105B60_mstory2(void) {
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                D_8011CA80_mstory2[count++] = i;
            }
            if (count >= 4) {
                return;
            }
        }
        if (count >= 4) {
            return;
        }
    }
}

void func_80105C1C_mstory2(void) {
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_801059BC_mstory2();
    func_80105A64_mstory2();
    func_80105B44_mstory2();
    func_80105B60_mstory2();
    D_8011C640_mstory2 = GwPlayer[0].coin;
    if (D_8011C640_mstory2 >= 5) {
        D_8011C640_mstory2 = 4;
    }
    omAddObj(0, 0, 0, -1, func_80105DB4_mstory2);
    omAddObj(0, 0, 0, -1, func_80105F94_mstory2);
    func_801063B0_mstory2();
    if (D_8011C640_mstory2 != 0) {
        if (_CheckFlag(D_8011BDF4_mstory2[D_8011C640_mstory2])) {
            D_8011B944_mstory2 = 1;
        } else {
            _SetFlag(D_8011BDF4_mstory2[D_8011C640_mstory2]);
        }
    }
    for (D_8011C642_mstory2 = 0; D_8011C642_mstory2 < 4; D_8011C642_mstory2++) {
        if (CheckControllerRead(D_8011C642_mstory2)) {
            break;
        }
    }
    if (D_8011C642_mstory2 >= 4) {
        D_8011C642_mstory2 = 0;
    }
    D_8011BDE0_mstory2[D_8011C640_mstory2]();
    WipeCreateIn(2, 16);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDF4_mstory2);

void func_80105DB4_mstory2(omObjData *obj) {
    s16 state = D_8011B946_mstory2;

    switch (state) {
        case 0:
            HuAudSeqPlay(D_8011C640_mstory2 == 0 ? 0x2C : 0x26);
            state++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                state++;
            }
            break;
        case 2:
            if (D_8011C640_mstory2 != 0 && D_8011B944_mstory2 == 1 && (D_800D5558_main[D_8011C642_mstory2] & START_BUTTON)) {
                state++;
            }
            break;
        case 4:
            D_8011B948_mstory2 = 1;
        case 3:
        default:
            obj->func = func_80105F4C_mstory2;
            break;
    }
    D_8011B946_mstory2 = state;
}

void func_80105EA4_mstory2(void) {
    D_8011B946_mstory2 = 3;
}

void func_80105EB4_mstory2(void) {
    D_8011B946_mstory2 = 4;
}

void func_80105EC4_mstory2(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        if (D_8011B948_mstory2 == 0) {
            if (D_8011C640_mstory2 != 0) {
                SLCommonSet(1);
            }
            omOvlReturnEx(1);
        } else if (D_8011B948_mstory2 == 1) {
            func_800E989C_minigame();
        }
    }
}

void func_80105F4C_mstory2(omObjData *obj) {
    WipeCreateOut(2, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80105EC4_mstory2;
}

void func_80105F94_mstory2(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105F4C_mstory2;
    }
}

void func_80105FBC_mstory2(void) {
    s16 comKeys[4] = { 0, 0, 0, 0 };
    s16 playerBits[4] = { 1, 2, 4, 8 };

    D_8011C644_mstory2 = func_80060880_main(160, 194, 20);
    comKeys[D_8011C642_mstory2] = -1;
    func_8005B63C_main(D_8011C644_mstory2, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
    HuWinActivePlayerSet(D_8011C644_mstory2, playerBits[D_8011C642_mstory2]);
    HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
}

void func_801060A4_mstory2(void) {
    HuWinHomeClear(D_8011C644_mstory2);
    func_80060C14_main(D_8011C644_mstory2, 1);
}

void func_801060D4_mstory2(void) {
    func_80060EA8_main(D_8011C644_mstory2, 1);
}

void func_801060F8_mstory2(s32 mess) {
    HuWinMesSet(D_8011C644_mstory2, mess, -1, -1);
    while (HuWinStatGet(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

void func_8010614C_mstory2(s32 mess) {
    HuWinMesSet(D_8011C644_mstory2, mess, -1, -1);
    HuWinInsertMesSet(D_8011C644_mstory2, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

s16 func_801061BC_mstory2(void) {
    return HuWinChoiceGet(D_8011C644_mstory2, 0, 1);
}

void func_801061EC_mstory2(void) {
    espDispOn(D_8011C646_mstory2);
}

void func_8010620C_mstory2(void) {
    espDispOff(D_8011C646_mstory2);
}

void func_8010622C_mstory2(void) {
    HuAudFXPlay(0x216);
    func_8001C814_main(D_8011C648_mstory2, 4, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    Hu3DMotionTimeSet(D_8011C648_mstory2, 0.0f);
    Hu3DMotionSpeedSet(D_8011C648_mstory2, 2.0f);
}

void func_80106290_mstory2(void) {
    func_8001C814_main(D_8011C648_mstory2, 4, 4);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    Hu3DMotionTimeSet(D_8011C648_mstory2, Hu3DData[D_8011C648_mstory2].motTime);
}

void func_801062F4_mstory2(void) {
    s16 i = 0;

    Hu3DData[D_8011C648_mstory2].rot.y += -10.6f;
    while (i < 5) {
        Hu3DData[D_8011C648_mstory2].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    }
}

void func_801063B0_mstory2(void) {
    D_8011C646_mstory2 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_8011C646_mstory2, 160, 120);
    espAttrSet(D_8011C646_mstory2, 0x4000);
    D_8011C648_mstory2 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_8011C648_mstory2, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_8011C648_mstory2, 2, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 1);
}

void func_80106470_mstory2(s32 arg0) {
    D_8011C674_mstory2 = arg0;
    D_8011B94C_mstory2 = 0;
    omAddPrcObj(func_801064AC_mstory2, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801064AC_mstory2);

s32 func_80106D44_mstory2(void) {
    return D_8011B94C_mstory2;
}

void func_80106D50_mstory2(void) {
}

void func_80106D58_mstory2(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            entry = &D_800D1714_main[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void func_80106E2C_mstory2(omObjData *obj, Vec *pos, s32 frames) {
    func_80106E48_mstory2(obj, pos, frames, 1);
}

void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, -5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, -5.0f, pos->z);
    }
    HuPrcVSleep();
}

void func_8010707C_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106E2C_mstory2(obj, &pos, frames);
}

void func_801070A8_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106E48_mstory2(obj, &pos, frames, arg3);
}

void func_801070D8_mstory2(omObjData *obj, Vec *target, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model = obj->model[1];
    f32 t;
    f32 angle;

    start.x = Hu3DData[model].rot.x;
    start.y = Hu3DData[model].rot.y;
    start.z = Hu3DData[model].rot.z;
    delta.x = target->x - start.x;
    delta.y = target->y - start.y;
    delta.z = target->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        angle = 90.0f / frames * t;
        rot.x = sindf(angle) * delta.x + start.x;
        rot.y = sindf(angle) * delta.y + start.y;
        rot.z = sindf(angle) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, target->x, target->y, target->z);
    HuPrcVSleep();
}

void func_80107280_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_801070D8_mstory2(obj, &pos, frames);
}

void func_801072AC_mstory2(s16 model) {
    HuPrcSleep(10);
    while (!func_801072F8_mstory2(model)) {
        HuPrcVSleep();
    }
}

s32 func_801072F8_mstory2(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x += dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}

void func_80107540_mstory2(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x -= dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z -= dz;
        HuPrcVSleep();
    }
}

void func_801076DC_mstory2(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107824_mstory2);

MstoryPath *func_80107B90_mstory2(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107E94_mstory2);

void func_8010873C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010876C_mstory2(void) {
    D_8011C75C_mstory2 = GwStory.unk1;
    if (D_8011C75C_mstory2 == 4) {
        D_8011C75E_mstory2 = 1;
    } else {
        D_8011C75E_mstory2 = 4;
    }
    func_80105FBC_mstory2();
    D_8011C75A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80109D04_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010AC1C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B7B8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C038_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C398_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108A3C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C1E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801088A4_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C75A_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010889C_mstory2(omObjData *obj) {
}

void func_801088A4_mstory2(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_0C == 1 && Hu3DData[D_8011C680_mstory2[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_8011C680_mstory2[0].unk_10, D_8011C75C_mstory2);
        }
        if (D_8011C680_mstory2[1].unk_0C == 1 && Hu3DData[D_8011C680_mstory2[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_8011C680_mstory2[1].unk_10, D_8011C75E_mstory2);
            z = Hu3DData[D_8011C680_mstory2[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void func_80108A3C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C680_mstory2[5].obj = obj;
    D_8011C680_mstory2[5].unk_08 = 0;
    D_8011C680_mstory2[5].func = func_80108AB0_mstory2;

    for (;;) {
        D_8011C680_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE2C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE48_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE74_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE80_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE8C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE98_mstory2);

void func_80108AB0_mstory2(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &pos[0], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C75C_mstory2 != 4) {
        func_8010614C_mstory2(0x5A0F);
    } else {
        func_801060F8_mstory2(0x5B00);
    }
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &pos[2], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &pos[3], 10);
    D_8011C680_mstory2[5].func = func_80108C40_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80108C40_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80109D04_mstory2);

void func_8010A290_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BEE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF28_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF88_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF94_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFAC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFB8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFC4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFD0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFDC_mstory2);

const char D_8011BFE8_mstory2[] = "item_hook";

void func_8010A298_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_8011BFE8_mstory2);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].unk_08 = 1;
}

void func_8010A3B4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C680_mstory2[0].func = func_8010A5FC_mstory2;
}

void func_8010A5FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010A61C_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_8011C680_mstory2[0].unk_0C = 1;
    D_8011C680_mstory2[0].unk_10 = 31;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74E_mstory2);
    func_80106D58_mstory2(D_8011C680_mstory2[1].obj->model[1], D_8011C758_mstory2, D_8011C756_mstory2);
    D_8011C680_mstory2[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[4]].motId, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010A784_mstory2(omObjData *obj) {
    Vec pos = D_8011BFF4_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010A9F0_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C680_mstory2[2].func = func_8010BF7C_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[0].unk_08 = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C680_mstory2[0].unk_0C = 1;
    D_8011C680_mstory2[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C680_mstory2[0].unk_0C = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010AC1C_mstory2);

void func_8010B108_mstory2(void) {
}

void func_8010B110_mstory2(omObjData *obj) {
    D_8011C680_mstory2[1].unk_0C = 1;
    D_8011C680_mstory2[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C680_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].func = func_8010A61C_mstory2;
}

void func_8010B200_mstory2(omObjData *obj) {
    Vec pos = D_8011C00C_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

void func_8010B46C_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].unk_08 = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C680_mstory2[1].unk_0C = 1;
    D_8011C680_mstory2[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C680_mstory2[1].unk_0C = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010B688_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
}

void func_8010B738_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[9]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFF4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C000_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C00C_mstory2);

const char D_8011C018_mstory2[] = "c204n_0_DEF";

void func_8010B7B8_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[2].obj = obj;
    D_8011C680_mstory2[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C710_mstory2 = D_8011BE80_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C710_mstory2.x, D_8011C710_mstory2.y, D_8011C710_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C710_mstory2.x, -5.0f, D_8011C710_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C740_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C018_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C740_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C740_mstory2[0], 0);
    D_8011C746_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, D_8011C018_mstory2);
    data = DataRead(0xA0083);
    D_8011C740_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C746_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, D_8011C018_mstory2);
    data = DataRead(0xA0080);
    D_8011C740_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    omPrcSetDestructor(0, func_8010BAC4_mstory2);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BAC4_mstory2(void) {
}

void func_8010BACC_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C024_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &target, 5);
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_8011C75C_mstory2 != 4 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_8011C75E_mstory2), 0x60);
    D_8011C680_mstory2[2].func = func_8010BCE4_mstory2;
    D_8011C680_mstory2[2].unk_08 = 5;
}

void func_8010BCE4_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010BD04_mstory2(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
}

void func_8010BDC4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C030_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[2].obj->model[1], Hu3DData[D_8011C680_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &target, 10);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].unk_08 = 1;
}

void func_8010BF7C_mstory2(omObjData *obj) {
    Vec pos = D_8011C03C_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_801070D8_mstory2(obj, &pos, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C680_mstory2[2].obj, D_8011C680_mstory2[0].obj);
        HuPrcVSleep();
    }
}

void func_8010C018_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[0].obj);
}

void func_8010C038_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[3].obj = obj;
    D_8011C680_mstory2[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C71C_mstory2 = D_8011BE8C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C71C_mstory2.x, D_8011C71C_mstory2.y, D_8011C71C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C71C_mstory2.x, -5.0f, D_8011C71C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C1DC_mstory2);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    while (1) {
        D_8011C680_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C1DC_mstory2(void) {
}

void func_8010C1E4_mstory2(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_8011C680_mstory2[3].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C748_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_8010C328_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010C348_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
}

void func_8010C398_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[4].obj = obj;
    D_8011C680_mstory2[4].unk_08 = 0;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0003, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C728_mstory2 = D_8011BE98_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C728_mstory2.x, D_8011C728_mstory2.y, D_8011C728_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C508_mstory2);
    while (1) {
        D_8011C680_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C508_mstory2(void) {
}

MstoryPath *func_8010C510_mstory2(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C814_mstory2);

void func_8010D0BC_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010D0EC_mstory2(void) {
    D_8011C83C_mstory2 = GwStory.unk1;
    if (D_8011C83C_mstory2 == 3) {
        D_8011C83E_mstory2 = 1;
    } else {
        D_8011C83E_mstory2 = 3;
    }
    func_80105FBC_mstory2();
    D_8011C83A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010E9E0_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010F8F8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801103E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80110C64_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80111024_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_8010D3BC_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80110E10_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010D224_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C83A_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010D21C_mstory2(omObjData *obj) {
}

void func_8010D224_mstory2(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_8011C760_mstory2[0].unk_0C == 1 && Hu3DData[D_8011C760_mstory2[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_8011C760_mstory2[0].unk_10, D_8011C83C_mstory2);
        }
        if (D_8011C760_mstory2[1].unk_0C == 1 && Hu3DData[D_8011C760_mstory2[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_8011C760_mstory2[1].unk_10, D_8011C83E_mstory2);
            z = Hu3DData[D_8011C760_mstory2[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void func_8010D430_mstory2(omObjData *);

void func_8010D3BC_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C760_mstory2[5].obj = obj;
    D_8011C760_mstory2[5].unk_08 = 0;
    D_8011C760_mstory2[5].func = func_8010D430_mstory2;

    for (;;) {
        D_8011C760_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

// Code matches, but the identical local initializer is merged with the one in
// func_80108AB0_mstory2, which suggests a file boundary between them.
#ifdef NON_MATCHING
void func_8010D430_mstory2(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &pos[0], 10);
    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_8011C760_mstory2[3].obj->model[1], Hu3DData[D_8011C760_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C83C_mstory2 != 3) {
        func_8010614C_mstory2(0x5A1F);
    } else {
        func_801060F8_mstory2(0x5B0F);
    }
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C760_mstory2[3].obj->model[1], Hu3DData[D_8011C760_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C760_mstory2[3].obj, &pos[2], 10);
    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &pos[3], 10);
    D_8011C760_mstory2[5].func = func_8010D5C0_mstory2;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D430_mstory2);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D5C0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010E9E0_mstory2);

void func_8010EF6C_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C024_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C030_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C03C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C054_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C060_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C06C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C078_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C090_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C0C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C108_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C168_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C174_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C180_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C18C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C198_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1A4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1B0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1BC_mstory2);

const char D_8011C1C8_mstory2[] = "item_hook";

void func_8010EF74_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_8011C1C8_mstory2);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C760_mstory2[0].func = func_8010D21C_mstory2;
    D_8011C760_mstory2[0].unk_08 = 1;
}

void func_8010F090_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C760_mstory2[0].func = func_8010F2D8_mstory2;
}

void func_8010F2D8_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

void func_8010F2F8_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_8011C760_mstory2[0].unk_0C = 1;
    D_8011C760_mstory2[0].unk_10 = 31;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C830_mstory2, D_8011C82E_mstory2);
    func_80106D58_mstory2(D_8011C760_mstory2[1].obj->model[1], D_8011C838_mstory2, D_8011C836_mstory2);
    D_8011C760_mstory2[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C760_mstory2[1].obj->model[1], Hu3DData[D_8011C760_mstory2[1].obj->motion[4]].motId, 0, 10, 2);
    D_8011C760_mstory2[0].func = func_8010D21C_mstory2;
}

void func_8010F460_mstory2(omObjData *obj) {
    Vec pos = D_8011C1D4_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C830_mstory2, D_8011C82A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C830_mstory2, D_8011C82A_mstory2[0]);
    D_8011C760_mstory2[0].func = func_8010D21C_mstory2;
}

void func_8010F6CC_mstory2(omObjData *obj) {
    Vec pos = D_8011C1E0_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C760_mstory2[2].func = func_80110BA8_mstory2;
    func_8004AC98_main(D_8011C83C_mstory2 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C760_mstory2[0].unk_08 = 10;
    while (TRUE) {
        if (D_8011C760_mstory2[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C760_mstory2[0].unk_0C = 1;
    D_8011C760_mstory2[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C760_mstory2[0].unk_0C = 0;
    D_8011C760_mstory2[0].func = func_8010D21C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F8F8_mstory2);

void func_8010FDE4_mstory2(void) {
}

void func_8010FDEC_mstory2(omObjData *obj) {
    D_8011C760_mstory2[1].unk_0C = 1;
    D_8011C760_mstory2[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C760_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_8011C760_mstory2[1].func = func_8010D21C_mstory2;
    D_8011C760_mstory2[0].func = func_8010F2F8_mstory2;
}

void func_8010FEDC_mstory2(omObjData *obj) {
    Vec pos = D_8011C1EC_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C838_mstory2, D_8011C832_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C838_mstory2, D_8011C832_mstory2[0]);
    D_8011C760_mstory2[1].func = func_8010D21C_mstory2;
}

void func_80110148_mstory2(omObjData *obj) {
    Vec pos = D_8011C1E0_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    func_8004AC98_main(D_8011C83E_mstory2 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C760_mstory2[1].unk_08 = 10;
    while (TRUE) {
        if (D_8011C760_mstory2[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C760_mstory2[1].unk_0C = 1;
    D_8011C760_mstory2[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C760_mstory2[1].unk_0C = 0;
    D_8011C760_mstory2[0].func = func_8010D21C_mstory2;
}

void func_80110364_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011C760_mstory2[1].obj->model[1], Hu3DData[D_8011C760_mstory2[1].obj->motion[9]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C760_mstory2[1].func = func_8010D21C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1D4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1EC_mstory2);

const char D_8011C1F8_mstory2[] = "c204n_0_DEF";

void func_801103E4_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_8011C760_mstory2[2].obj = obj;
    D_8011C760_mstory2[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C83A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C7F0_mstory2 = D_8011C060_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C7F0_mstory2.x, D_8011C7F0_mstory2.y, D_8011C7F0_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C7F0_mstory2.x, -5.0f, D_8011C7F0_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C820_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C1F8_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C820_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C820_mstory2[0], 0);
    D_8011C826_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C820_mstory2[0], 0, D_8011C1F8_mstory2);
    data = DataRead(0xA0083);
    D_8011C820_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C826_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C820_mstory2[0], 0, D_8011C1F8_mstory2);
    data = DataRead(0xA0080);
    D_8011C820_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C826_mstory2, D_8011C820_mstory2[0]);
    omPrcSetDestructor(0, func_801106F0_mstory2);
    D_8011C760_mstory2[2].func = func_8010D21C_mstory2;
    while (TRUE) {
        D_8011C760_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_801106F0_mstory2(void) {
}

void func_801106F8_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C204_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C826_mstory2, D_8011C820_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &target, 5);
    func_80106D58_mstory2(model, D_8011C826_mstory2, D_8011C820_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C760_mstory2[1].obj->model[1], Hu3DData[D_8011C760_mstory2[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_8011C83C_mstory2 != 3 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_8011C83E_mstory2), 0x60);
    D_8011C760_mstory2[2].func = func_80110910_mstory2;
    D_8011C760_mstory2[2].unk_08 = 5;
}

void func_80110910_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

void func_80110930_mstory2(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_8011C760_mstory2[2].func = func_8010D21C_mstory2;
}

void func_801109F0_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C210_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C826_mstory2, D_8011C820_mstory2[1]);
    Hu3DMotionShiftSet(D_8011C760_mstory2[2].obj->model[1], Hu3DData[D_8011C760_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &target, 10);
    D_8011C760_mstory2[2].func = func_8010D21C_mstory2;
    D_8011C760_mstory2[2].unk_08 = 1;
}

void func_80110BA8_mstory2(omObjData *obj) {
    Vec pos = D_8011C21C_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C826_mstory2, D_8011C820_mstory2[0]);
    func_801070D8_mstory2(obj, &pos, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C760_mstory2[2].obj, D_8011C760_mstory2[0].obj);
        HuPrcVSleep();
    }
}

void func_80110C44_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[0].obj);
}

void func_80110C64_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C760_mstory2[3].obj = obj;
    D_8011C760_mstory2[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C83A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C7FC_mstory2 = D_8011C06C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C7FC_mstory2.x, D_8011C7FC_mstory2.y, D_8011C7FC_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C7FC_mstory2.x, -5.0f, D_8011C7FC_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_80110E08_mstory2);
    D_8011C760_mstory2[3].func = func_8010D21C_mstory2;
    while (1) {
        D_8011C760_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80110E08_mstory2(void) {
}

void func_80110E10_mstory2(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_8011C760_mstory2[3].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C828_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_80110F54_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

void func_80110F74_mstory2(omObjData *obj) {
    Vec pos = D_8011C1E0_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C760_mstory2[3].func = func_8010D21C_mstory2;
}

void func_80110FC4_mstory2(void) {
    Vec pos = D_8011C228_mstory2;

    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &pos, 10);
    D_8011C760_mstory2[3].func = func_8010D21C_mstory2;
}

void func_80111024_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C760_mstory2[4].obj = obj;
    D_8011C760_mstory2[4].unk_08 = 0;
    D_8011C760_mstory2[4].func = func_8010D21C_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0004, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C808_mstory2 = D_8011C078_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C808_mstory2.x, D_8011C808_mstory2.y, D_8011C808_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_80111194_mstory2);
    while (1) {
        D_8011C760_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111194_mstory2);

MstoryPath *func_801111A0_mstory2(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801114A4_mstory2);

void func_80111D4C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_80111D7C_mstory2(void) {
    D_8011C91C_mstory2 = GwStory.unk1;
    if (D_8011C91C_mstory2 == 5) {
        D_8011C91E_mstory2 = 1;
    } else {
        D_8011C91E_mstory2 = 5;
    }
    func_80105FBC_mstory2();
    D_8011C91A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80113670_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80114588_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011509C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011591C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80115CDC_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_8011204C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80115AC8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80111EB4_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C91A_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80111EAC_mstory2(omObjData *obj) {
}

void func_80111EB4_mstory2(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_8011C840_mstory2[0].unk_0C == 1 && Hu3DData[D_8011C840_mstory2[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_8011C840_mstory2[0].unk_10, D_8011C91C_mstory2);
        }
        if (D_8011C840_mstory2[1].unk_0C == 1 && Hu3DData[D_8011C840_mstory2[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_8011C840_mstory2[1].unk_10, D_8011C91E_mstory2);
            z = Hu3DData[D_8011C840_mstory2[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void func_8011204C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C840_mstory2[5].obj = obj;
    D_8011C840_mstory2[5].unk_08 = 0;
    D_8011C840_mstory2[5].func = func_801120C0_mstory2;

    for (;;) {
        D_8011C840_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

// Code matches, but the identical local initializer is merged with the one in
// func_80108AB0_mstory2, which suggests a file boundary between them.
#ifdef NON_MATCHING
void func_801120C0_mstory2(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C840_mstory2[3].obj, &pos[0], 10);
    func_801070D8_mstory2(D_8011C840_mstory2[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_8011C840_mstory2[3].obj->model[1], Hu3DData[D_8011C840_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C91C_mstory2 != 5) {
        func_8010614C_mstory2(0x5A2D);
    } else {
        func_801060F8_mstory2(0x5B1E);
    }
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C840_mstory2[3].obj->model[1], Hu3DData[D_8011C840_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C840_mstory2[3].obj, &pos[2], 10);
    func_801070D8_mstory2(D_8011C840_mstory2[2].obj, &pos[3], 10);
    D_8011C840_mstory2[5].func = func_80112250_mstory2;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801120C0_mstory2);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80112250_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113670_mstory2);

void func_80113BFC_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C204_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C210_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C21C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C228_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C240_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C24C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C258_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C264_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C27C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C354_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C360_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C36C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C378_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C384_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C390_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C39C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3A8_mstory2);

const char D_8011C3B4_mstory2[] = "item_hook";

void func_80113C04_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_8011C3B4_mstory2);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C840_mstory2[0].func = func_80111EAC_mstory2;
    D_8011C840_mstory2[0].unk_08 = 1;
}

void func_80113D20_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C840_mstory2[0].func = func_80113F68_mstory2;
}

void func_80113F68_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

void func_80113F88_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_8011C840_mstory2[0].unk_0C = 1;
    D_8011C840_mstory2[0].unk_10 = 31;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C910_mstory2, D_8011C90E_mstory2);
    func_80106D58_mstory2(D_8011C840_mstory2[1].obj->model[1], D_8011C918_mstory2, D_8011C916_mstory2);
    D_8011C840_mstory2[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C840_mstory2[1].obj->model[1], Hu3DData[D_8011C840_mstory2[1].obj->motion[4]].motId, 0, 10, 2);
    D_8011C840_mstory2[0].func = func_80111EAC_mstory2;
}

void func_801140F0_mstory2(omObjData *obj) {
    Vec pos = D_8011C3C0_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C910_mstory2, D_8011C90A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C910_mstory2, D_8011C90A_mstory2[0]);
    D_8011C840_mstory2[0].func = func_80111EAC_mstory2;
}

void func_8011435C_mstory2(omObjData *obj) {
    Vec pos = D_8011C3CC_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C840_mstory2[2].func = func_80115860_mstory2;
    func_8004AC98_main(D_8011C91C_mstory2 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C840_mstory2[0].unk_08 = 10;
    while (TRUE) {
        if (D_8011C840_mstory2[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C840_mstory2[0].unk_0C = 1;
    D_8011C840_mstory2[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C840_mstory2[0].unk_0C = 0;
    D_8011C840_mstory2[0].func = func_80111EAC_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114588_mstory2);

void func_80114A9C_mstory2(void) {
}

void func_80114AA4_mstory2(omObjData *obj) {
    D_8011C840_mstory2[1].unk_0C = 1;
    D_8011C840_mstory2[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C840_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_8011C840_mstory2[1].func = func_80111EAC_mstory2;
    D_8011C840_mstory2[0].func = func_80113F88_mstory2;
}

void func_80114B94_mstory2(omObjData *obj) {
    Vec pos = D_8011C3D8_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C918_mstory2, D_8011C912_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C918_mstory2, D_8011C912_mstory2[0]);
    D_8011C840_mstory2[1].func = func_80111EAC_mstory2;
}

void func_80114E00_mstory2(omObjData *obj) {
    Vec pos = D_8011C3CC_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    func_8004AC98_main(D_8011C91E_mstory2 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C840_mstory2[1].unk_08 = 10;
    while (TRUE) {
        if (D_8011C840_mstory2[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C840_mstory2[1].unk_0C = 1;
    D_8011C840_mstory2[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C840_mstory2[1].unk_0C = 0;
    D_8011C840_mstory2[0].func = func_80111EAC_mstory2;
}

void func_8011501C_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011C840_mstory2[1].obj->model[1], Hu3DData[D_8011C840_mstory2[1].obj->motion[9]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C840_mstory2[1].func = func_80111EAC_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3CC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3D8_mstory2);

const char D_8011C3E4_mstory2[] = "c204n_0_DEF";

void func_8011509C_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_8011C840_mstory2[2].obj = obj;
    D_8011C840_mstory2[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C91A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C8D0_mstory2 = D_8011C24C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C8D0_mstory2.x, D_8011C8D0_mstory2.y, D_8011C8D0_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C8D0_mstory2.x, -5.0f, D_8011C8D0_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C900_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C3E4_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C900_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C900_mstory2[0], 0);
    D_8011C906_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C900_mstory2[0], 0, D_8011C3E4_mstory2);
    data = DataRead(0xA0083);
    D_8011C900_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C906_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C900_mstory2[0], 0, D_8011C3E4_mstory2);
    data = DataRead(0xA0080);
    D_8011C900_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C906_mstory2, D_8011C900_mstory2[0]);
    omPrcSetDestructor(0, func_801153A8_mstory2);
    D_8011C840_mstory2[2].func = func_80111EAC_mstory2;
    while (TRUE) {
        D_8011C840_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_801153A8_mstory2(void) {
}

void func_801153B0_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C3F0_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C906_mstory2, D_8011C900_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &target, 5);
    func_80106D58_mstory2(model, D_8011C906_mstory2, D_8011C900_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C840_mstory2[1].obj->model[1], Hu3DData[D_8011C840_mstory2[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_8011C91C_mstory2 != 5 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_8011C91E_mstory2), 0x60);
    D_8011C840_mstory2[2].func = func_801155C8_mstory2;
    D_8011C840_mstory2[2].unk_08 = 5;
}

void func_801155C8_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

void func_801155E8_mstory2(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_8011C840_mstory2[2].func = func_80111EAC_mstory2;
}

void func_801156A8_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C3FC_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C906_mstory2, D_8011C900_mstory2[1]);
    Hu3DMotionShiftSet(D_8011C840_mstory2[2].obj->model[1], Hu3DData[D_8011C840_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &target, 10);
    D_8011C840_mstory2[2].func = func_80111EAC_mstory2;
    D_8011C840_mstory2[2].unk_08 = 1;
}

void func_80115860_mstory2(omObjData *obj) {
    Vec pos = D_8011C408_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C906_mstory2, D_8011C900_mstory2[0]);
    func_801070D8_mstory2(obj, &pos, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C840_mstory2[2].obj, D_8011C840_mstory2[0].obj);
        HuPrcVSleep();
    }
}

void func_801158FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[0].obj);
}

void func_8011591C_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C840_mstory2[3].obj = obj;
    D_8011C840_mstory2[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C91A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C8DC_mstory2 = D_8011C258_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C8DC_mstory2.x, D_8011C8DC_mstory2.y, D_8011C8DC_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C8DC_mstory2.x, -5.0f, D_8011C8DC_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_80115AC0_mstory2);
    D_8011C840_mstory2[3].func = func_80111EAC_mstory2;
    while (1) {
        D_8011C840_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80115AC0_mstory2(void) {
}

void func_80115AC8_mstory2(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_8011C840_mstory2[3].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C908_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_80115C0C_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

void func_80115C2C_mstory2(omObjData *obj) {
    Vec pos = D_8011C3CC_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C840_mstory2[3].func = func_80111EAC_mstory2;
}

void func_80115C7C_mstory2(void) {
    Vec pos = D_8011C414_mstory2;

    func_801070D8_mstory2(D_8011C840_mstory2[2].obj, &pos, 10);
    D_8011C840_mstory2[3].func = func_80111EAC_mstory2;
}

void func_80115CDC_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C840_mstory2[4].obj = obj;
    D_8011C840_mstory2[4].unk_08 = 0;
    D_8011C840_mstory2[4].func = func_80111EAC_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0005, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C8E8_mstory2 = D_8011C264_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C8E8_mstory2.x, D_8011C8E8_mstory2.y, D_8011C8E8_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_80115E4C_mstory2);
    while (1) {
        D_8011C840_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115E4C_mstory2);

MstoryPath *func_80115E60_mstory2(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116164_mstory2);

void func_80116A0C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_80116A3C_mstory2(void) {
    D_8011C9FC_mstory2 = GwStory.unk1;
    if (D_8011C9FC_mstory2 == 2) {
        D_8011C9FE_mstory2 = 1;
    } else {
        D_8011C9FE_mstory2 = 2;
    }
    func_80105FBC_mstory2();
    D_8011C9FA_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8011831C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80119234_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80119D20_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011A5A0_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011A960_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80116D0C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011A74C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80116B74_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C9FA_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80116B6C_mstory2(omObjData *obj) {
}

void func_80116B74_mstory2(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_8011C920_mstory2[0].unk_0C == 1 && Hu3DData[D_8011C920_mstory2[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_8011C920_mstory2[0].unk_10, D_8011C9FC_mstory2);
        }
        if (D_8011C920_mstory2[1].unk_0C == 1 && Hu3DData[D_8011C920_mstory2[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_8011C920_mstory2[1].unk_10, D_8011C9FE_mstory2);
            z = Hu3DData[D_8011C920_mstory2[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void func_80116D0C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C920_mstory2[5].obj = obj;
    D_8011C920_mstory2[5].unk_08 = 0;
    D_8011C920_mstory2[5].func = func_80116D80_mstory2;

    for (;;) {
        D_8011C920_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

// Code matches, but the identical local initializer is merged with the one in
// func_80108AB0_mstory2, which suggests a file boundary between them.
#ifdef NON_MATCHING
void func_80116D80_mstory2(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C920_mstory2[3].obj, &pos[0], 10);
    func_801070D8_mstory2(D_8011C920_mstory2[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_8011C920_mstory2[3].obj->model[1], Hu3DData[D_8011C920_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C9FC_mstory2 != 2) {
        func_8010614C_mstory2(0x5A38);
    } else {
        func_801060F8_mstory2(0x5B2A);
    }
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C920_mstory2[3].obj->model[1], Hu3DData[D_8011C920_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C920_mstory2[3].obj, &pos[2], 10);
    func_801070D8_mstory2(D_8011C920_mstory2[2].obj, &pos[3], 10);
    D_8011C920_mstory2[5].func = func_80116F0C_mstory2;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116D80_mstory2);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116F0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011831C_mstory2);

void func_801188A8_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3F0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3FC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C408_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C414_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C42C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C438_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C444_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C450_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C468_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C498_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C4E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C540_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C54C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C558_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C564_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C570_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C57C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C588_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C594_mstory2);

const char D_8011C5A0_mstory2[] = "item_hook";

void func_801188B0_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_8011C5A0_mstory2);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C920_mstory2[0].func = func_80116B6C_mstory2;
    D_8011C920_mstory2[0].unk_08 = 1;
}

void func_801189CC_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C920_mstory2[0].func = func_80118C14_mstory2;
}

void func_80118C14_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

void func_80118C34_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_8011C920_mstory2[0].unk_0C = 1;
    D_8011C920_mstory2[0].unk_10 = 31;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C9F0_mstory2, D_8011C9EE_mstory2);
    func_80106D58_mstory2(D_8011C920_mstory2[1].obj->model[1], D_8011C9F8_mstory2, D_8011C9F6_mstory2);
    D_8011C920_mstory2[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C920_mstory2[1].obj->model[1], Hu3DData[D_8011C920_mstory2[1].obj->motion[4]].motId, 0, 10, 2);
    D_8011C920_mstory2[0].func = func_80116B6C_mstory2;
}

void func_80118D9C_mstory2(omObjData *obj) {
    Vec pos = D_8011C5AC_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C9F0_mstory2, D_8011C9EA_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C9F0_mstory2, D_8011C9EA_mstory2[0]);
    D_8011C920_mstory2[0].func = func_80116B6C_mstory2;
}

void func_80119008_mstory2(omObjData *obj) {
    Vec pos = D_8011C5B8_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C920_mstory2[2].func = func_8011A4E4_mstory2;
    func_8004AC98_main(D_8011C9FC_mstory2 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C920_mstory2[0].unk_08 = 10;
    while (TRUE) {
        if (D_8011C920_mstory2[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C920_mstory2[0].unk_0C = 1;
    D_8011C920_mstory2[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C920_mstory2[0].unk_0C = 0;
    D_8011C920_mstory2[0].func = func_80116B6C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119234_mstory2);

void func_80119720_mstory2(void) {
}

void func_80119728_mstory2(omObjData *obj) {
    D_8011C920_mstory2[1].unk_0C = 1;
    D_8011C920_mstory2[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C920_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_8011C920_mstory2[1].func = func_80116B6C_mstory2;
    D_8011C920_mstory2[0].func = func_80118C34_mstory2;
}

void func_80119818_mstory2(omObjData *obj) {
    Vec pos = D_8011C5C4_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C9F8_mstory2, D_8011C9F2_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C9F8_mstory2, D_8011C9F2_mstory2[0]);
    D_8011C920_mstory2[1].func = func_80116B6C_mstory2;
}

void func_80119A84_mstory2(omObjData *obj) {
    Vec pos = D_8011C5B8_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    func_8004AC98_main(D_8011C9FE_mstory2 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C920_mstory2[1].unk_08 = 10;
    while (TRUE) {
        if (D_8011C920_mstory2[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C920_mstory2[1].unk_0C = 1;
    D_8011C920_mstory2[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C920_mstory2[1].unk_0C = 0;
    D_8011C920_mstory2[0].func = func_80116B6C_mstory2;
}

void func_80119CA0_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011C920_mstory2[1].obj->model[1], Hu3DData[D_8011C920_mstory2[1].obj->motion[9]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C920_mstory2[1].func = func_80116B6C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5B8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5C4_mstory2);

const char D_8011C5D0_mstory2[] = "c204n_0_DEF";

void func_80119D20_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_8011C920_mstory2[2].obj = obj;
    D_8011C920_mstory2[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C9FA_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C9B0_mstory2 = D_8011C438_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C9B0_mstory2.x, D_8011C9B0_mstory2.y, D_8011C9B0_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C9B0_mstory2.x, -5.0f, D_8011C9B0_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C9E0_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C5D0_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C9E0_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C9E0_mstory2[0], 0);
    D_8011C9E6_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C9E0_mstory2[0], 0, D_8011C5D0_mstory2);
    data = DataRead(0xA0083);
    D_8011C9E0_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C9E6_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C9E0_mstory2[0], 0, D_8011C5D0_mstory2);
    data = DataRead(0xA0080);
    D_8011C9E0_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C9E6_mstory2, D_8011C9E0_mstory2[0]);
    omPrcSetDestructor(0, func_8011A02C_mstory2);
    D_8011C920_mstory2[2].func = func_80116B6C_mstory2;
    while (TRUE) {
        D_8011C920_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8011A02C_mstory2(void) {
}

void func_8011A034_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C5DC_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C9E6_mstory2, D_8011C9E0_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &target, 5);
    func_80106D58_mstory2(model, D_8011C9E6_mstory2, D_8011C9E0_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C920_mstory2[1].obj->model[1], Hu3DData[D_8011C920_mstory2[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_8011C9FC_mstory2 != 2 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_8011C9FE_mstory2), 0x60);
    D_8011C920_mstory2[2].func = func_8011A24C_mstory2;
    D_8011C920_mstory2[2].unk_08 = 5;
}

void func_8011A24C_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

void func_8011A26C_mstory2(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_8011C920_mstory2[2].func = func_80116B6C_mstory2;
}

void func_8011A32C_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C5E8_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C9E6_mstory2, D_8011C9E0_mstory2[1]);
    Hu3DMotionShiftSet(D_8011C920_mstory2[2].obj->model[1], Hu3DData[D_8011C920_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &target, 10);
    D_8011C920_mstory2[2].func = func_80116B6C_mstory2;
    D_8011C920_mstory2[2].unk_08 = 1;
}

void func_8011A4E4_mstory2(omObjData *obj) {
    Vec pos = D_8011C5F4_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C9E6_mstory2, D_8011C9E0_mstory2[0]);
    func_801070D8_mstory2(obj, &pos, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C920_mstory2[2].obj, D_8011C920_mstory2[0].obj);
        HuPrcVSleep();
    }
}

void func_8011A580_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[0].obj);
}

void func_8011A5A0_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C920_mstory2[3].obj = obj;
    D_8011C920_mstory2[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C9FA_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C9BC_mstory2 = D_8011C444_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C9BC_mstory2.x, D_8011C9BC_mstory2.y, D_8011C9BC_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C9BC_mstory2.x, -5.0f, D_8011C9BC_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8011A744_mstory2);
    D_8011C920_mstory2[3].func = func_80116B6C_mstory2;
    while (1) {
        D_8011C920_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8011A744_mstory2(void) {
}

void func_8011A74C_mstory2(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_8011C920_mstory2[3].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (D_8011C9E8_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_8011A890_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

void func_8011A8B0_mstory2(omObjData *obj) {
    Vec pos = D_8011C5B8_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C920_mstory2[3].func = func_80116B6C_mstory2;
}

void func_8011A900_mstory2(void) {
    Vec pos = D_8011C600_mstory2;

    func_801070D8_mstory2(D_8011C920_mstory2[2].obj, &pos, 10);
    D_8011C920_mstory2[3].func = func_80116B6C_mstory2;
}

void func_8011A960_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_8011C920_mstory2[4].obj = obj;
    D_8011C920_mstory2[4].unk_08 = 0;
    D_8011C920_mstory2[4].func = func_80116B6C_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0006, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C9C8_mstory2 = D_8011C450_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C9C8_mstory2.x, D_8011C9C8_mstory2.y, D_8011C9C8_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8011AAD0_mstory2);
    while (1) {
        D_8011C920_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AAD0_mstory2);

void func_8011AAE0_mstory2(void) {
    func_80105FBC_mstory2();
    D_8011CA4C_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8011B198_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8011B64C_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_8011AB84_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011CA4C_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8011AB7C_mstory2(omObjData *obj) {
}

void func_8011AB84_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_8011CA10_mstory2[2].obj = obj;
    D_8011CA10_mstory2[2].unk_08 = 0;
    D_8011CA10_mstory2[2].func = func_8011AC10_mstory2;
    omPrcSetDestructor(0, func_8011AC08_mstory2);
    while (1) {
        D_8011CA10_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8011AC08_mstory2(void) {
}

void func_8011AC10_mstory2(omObjData *obj) {
    s16 choice;

    HuPrcSleep(40);
    HuAudFXPlay(0x159);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A7F);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A80);
    choice = func_801061BC_mstory2();
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    switch (choice) {
        case 0:
            D_8011CA10_mstory2[2].func = func_8011AD8C_mstory2;
            break;
        case 1:
            D_8011CA10_mstory2[2].func = func_8011B080_mstory2;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AD8C_mstory2);

void func_8011B080_mstory2(omObjData *obj) {
    func_80106D58_mstory2(D_8011CA10_mstory2[0].obj->model[1], D_8011CA7A_mstory2, D_8011CA74_mstory2[2]);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[2]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(0x5A82);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011CA10_mstory2[1].obj->model[1], Hu3DData[D_8011CA10_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011CA10_mstory2[1].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
    D_8011CA10_mstory2[2].func = func_8011AB7C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5DC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5E8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C600_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C60C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C618_mstory2);

const char D_8011C630_mstory2[] = "c204n_0_DEF";

void func_8011B198_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011CA10_mstory2[0].obj = obj;
    D_8011CA10_mstory2[0].unk_08 = 0;
    D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011CA4C_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011CA50_mstory2 = D_8011C60C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011CA50_mstory2.x, D_8011CA50_mstory2.y, D_8011CA50_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011CA50_mstory2.x, -5.0f, D_8011CA50_mstory2.z);
    data = DataRead(0xA0082);
    D_8011CA74_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C630_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011CA74_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011CA74_mstory2[0], 0);
    D_8011CA7A_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011CA74_mstory2[0], 0, D_8011C630_mstory2);
    data = DataRead(0xA0084);
    D_8011CA74_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011CA7A_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011CA74_mstory2[0], 0, D_8011C630_mstory2);
    data = DataRead(0xA0080);
    D_8011CA74_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011CA7A_mstory2, D_8011CA74_mstory2[0]);
    omPrcSetDestructor(0, func_8011B45C_mstory2);
    while (TRUE) {
        D_8011CA10_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8011B45C_mstory2(void) {
}

void func_8011B464_mstory2(omObjData *obj) {
    if (D_8011CA10_mstory2[0].unk_08 == 1) {
        Hu3DData[obj->model[1]].pos.y += D_8011BDD0_mstory2 * D_8011BDD0_mstory2 * (D_8011BDD0_mstory2 >= 0.0f ? -8.75f : 8.75f);
        if (D_8011BDD0_mstory2 > 1.5f) {
            D_8011BDD0_mstory2 = -1.5f;
        } else {
            D_8011BDD0_mstory2 += 0.2f;
        }
    } else if (D_8011CA10_mstory2[0].unk_08 == 2) {
        Hu3DData[obj->model[1]].pos.y += D_8011BDD0_mstory2 * D_8011BDD0_mstory2 * (D_8011BDD0_mstory2 >= 0.0f ? -8.75f : 8.75f);
        if (D_8011BDD0_mstory2 > 1.5f) {
            D_8011BDD0_mstory2 = 0.0f;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
            D_8011CA10_mstory2[0].func = func_8011AB7C_mstory2;
            D_8011CA10_mstory2[0].unk_08 = 3;
        } else {
            D_8011BDD0_mstory2 += 0.2f;
        }
    }
}

void func_8011B64C_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_8011CA10_mstory2[1].obj = obj;
    D_8011CA10_mstory2[1].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011CA4C_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0129);
    func_8000B460_main(obj, 2, 0xA0125);
    func_8000B460_main(obj, 3, 0xA0128);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011CA5C_mstory2 = D_8011C618_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011CA5C_mstory2.x, D_8011CA5C_mstory2.y, D_8011CA5C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011CA5C_mstory2.x, -5.0f, D_8011CA5C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8011B818_mstory2);
    D_8011CA10_mstory2[1].func = func_8011B820_mstory2;
    while (1) {
        D_8011CA10_mstory2[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8011B818_mstory2(void) {
}

void func_8011B820_mstory2(omObjData *obj) {
    D_8011CA04_mstory2 = Hu3DData[obj->model[1]].pos.y;
    D_8011BDD8_mstory2 = sindf(D_8011BDD4_mstory2) * 15.0f + 15.0f;
    D_8011BDD4_mstory2 += 2.0f;
    if (D_8011BDD4_mstory2 >= 360.0f) {
        D_8011BDD4_mstory2 -= 360.0f;
    }
    if (D_8011CA10_mstory2[1].unk_08 != 1) {
        Hu3DModelPosSet(obj->model[1], 0.0f, D_8011BDD8_mstory2 + 225.0f, 400.0f);
    }
}
