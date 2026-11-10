#include "common.h"
#include "game/hmfmath.h"

typedef struct UnkMstory3Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory3Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

typedef struct MstoryPlayerS16 {
    s16 v[MB_MAX_PLAYERS];
} MstoryPlayerS16; // sizeof 0x8

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern char *D_801153A0_mstory3[];

extern Vec D_80115260_mstory3;
extern Vec D_8011526C_mstory3;
extern Vec D_80115278_mstory3;
extern s16 D_80115284_mstory3;
extern s16 D_80115286_mstory3;
extern s32 D_80115288_mstory3;
extern void (*D_801154F0_mstory3[])(void);
extern s32 D_801154F8_mstory3[];
extern MstoryPlayerS16 D_80115500_mstory3;
extern MstoryPlayerS16 D_80115508_mstory3;
extern Vec D_8011556C_mstory3;
extern Vec D_80115578_mstory3;
extern char D_801156C8_mstory3[];
extern Vec D_801156E0_mstory3;
extern const Vec D_801156D4_mstory3;
extern s16 D_80115C8A_mstory3[2];
extern const Vec D_801156EC_mstory3;
extern s16 D_80115C92_mstory3[3];
extern const Vec D_8011571C_mstory3;
extern Vec D_80115728_mstory3;
extern s16 D_80115B90_mstory3;
extern s16 D_80115B92_mstory3;
extern u16 D_80115B94_mstory3;
extern s16 D_80115B96_mstory3;
extern s32 D_80115BBC_mstory3;
extern s16 D_80115B98_mstory3[8];
extern s16 D_80115BA8_mstory3[8];
extern s16 D_80115BB8_mstory3;
extern s32 D_80115510_mstory3[7];
extern s16 D_8011552C_mstory3[][2];
extern UnkMstory3Obj D_80115BC0_mstory3[6];
extern Vec D_80115C5C_mstory3;
extern Vec D_80115C68_mstory3;
extern s16 D_80115C80_mstory3[3];
extern Vec D_80115C44_mstory3;
extern Vec D_80115C50_mstory3;
extern const Vec D_80115554_mstory3;
extern const Vec D_80115560_mstory3;
extern char D_801156F8_mstory3[];
extern s16 D_80115C86_mstory3;
extern const Vec D_80115704_mstory3;
extern const Vec D_80115710_mstory3;
extern s16 D_80115C88_mstory3;
extern s16 D_80115C8E_mstory3;
extern s16 D_80115C90_mstory3;
extern s16 D_80115C96_mstory3;
extern s16 D_80115C98_mstory3;
extern s16 D_80115C9A_mstory3;
extern s16 D_80115C9C_mstory3;
extern s16 D_80115C9E_mstory3;
extern s16 D_80115DC0_mstory3[4];

void func_80105C1C_mstory3(void);
void func_80105D98_mstory3(omObjData *obj);
void func_80105F2C_mstory3(omObjData *obj);
void func_80106340_mstory3(void);
void func_80105E9C_mstory3(omObjData *);
void func_80105EE4_mstory3(omObjData *obj);
void func_80106DE0_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106CF0_mstory3(s16 model, s16 arg1, s16 arg2);
void func_80107070_mstory3(omObjData *obj, const Vec *pos, s32 frames);
void func_80107244_mstory3(s16 model);
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames);
s32 func_80107290_mstory3(s16 model);
void func_80107674_mstory3(omObjData *obj, omObjData *target);
void func_80108A94_mstory3(omObjData *);
void func_8010B634_mstory3(void);
void func_8010AB34_mstory3(omObjData *obj);
void func_8010C3F4_mstory3(omObjData *obj);
void func_8010C654_mstory3(void);
void func_8010C15C_mstory3(omObjData *obj);
void func_8010643C_mstory3(void);
void func_80106CE8_mstory3(void);
void func_80108CA8_mstory3(omObjData *);
void func_8010AB54_mstory3(omObjData *);
void func_8010A23C_mstory3(void);
void func_8010B154_mstory3(void);
void func_8010BC34_mstory3(void);
void func_8010BF40_mstory3(void);
void func_8010C4B0_mstory3(void);
void func_8010C870_mstory3(void);
void func_8010C9E0_mstory3(void);
void func_8010C65C_mstory3(void);
void func_80108A9C_mstory3(void);
void func_80108C34_mstory3(void);

void func_801059A0_mstory3(void) {
    func_80105C1C_mstory3();
}

void func_801059BC_mstory3(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory3(omObjData *obj) {
    D_800CE17C_main[0] = D_80115260_mstory3.x;
    D_800CE17C_main[1] = D_80115260_mstory3.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80115260_mstory3, &D_8011526C_mstory3, &D_80115278_mstory3);
    Hu3DCamUpdateMtx(0);
}

void func_80105A64_mstory3(void) {
    omObjData *obj;

    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_801059E4_mstory3);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_801059E4_mstory3(obj);
}

void func_80105B44_mstory3(void) {
    HuWinInit();
}

void func_80105B60_mstory3(void) {
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                D_80115DC0_mstory3[count++] = i;
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

void func_80105C1C_mstory3(void) {
    s16 chapter;

    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_801059BC_mstory3();
    func_80105A64_mstory3();
    func_80105B44_mstory3();
    func_80105B60_mstory3();
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    omAddObj(0, 0, 0, -1, func_80105D98_mstory3);
    omAddObj(0, 0, 0, -1, func_80105F2C_mstory3);
    func_80106340_mstory3();
    if (_CheckFlag(D_801154F8_mstory3[chapter])) {
        D_80115284_mstory3 = 1;
    } else {
        _SetFlag(D_801154F8_mstory3[chapter]);
    }
    for (D_80115B90_mstory3 = 0; D_80115B90_mstory3 < 4; D_80115B90_mstory3++) {
        if (CheckControllerRead(D_80115B90_mstory3)) {
            break;
        }
    }
    if (D_80115B90_mstory3 >= 4) {
        D_80115B90_mstory3 = 0;
    }
    D_801154F0_mstory3[chapter]();
    WipeCreateIn(2, 16);
}

void func_80105D98_mstory3(omObjData *obj) {
    s16 state = D_80115286_mstory3;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                state++;
            }
            break;
        case 2:
            if (D_80115284_mstory3 == 1 && (D_800D5558_main[D_80115B90_mstory3] & START_BUTTON)) {
                state++;
            }
            break;
        case 3:
            obj->func = func_80105EE4_mstory3;
            state++;
            break;
        default:
            obj->func = func_80105EE4_mstory3;
            break;
    }
    D_80115286_mstory3 = state;
}

void func_80105E8C_mstory3(void) {
    D_80115286_mstory3 = 3;
}

void func_80105E9C_mstory3(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        SLCommonSet(1);
        omOvlReturnEx(1);
    }
}

void func_80105EE4_mstory3(omObjData *obj) {
    WipeCreateOut(2, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80105E9C_mstory3;
}

void func_80105F2C_mstory3(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105EE4_mstory3;
    }
}

void func_80105F54_mstory3(void) {
    MstoryPlayerS16 comKeys = D_80115500_mstory3;
    MstoryPlayerS16 playerBits = D_80115508_mstory3;

    D_80115B92_mstory3 = func_80060880_main(160, 194, 20);
    comKeys.v[D_80115B90_mstory3] = -1;
    func_8005B63C_main(D_80115B92_mstory3, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
    HuWinActivePlayerSet(D_80115B92_mstory3, playerBits.v[D_80115B90_mstory3]);
    HuWinComKeySet(comKeys.v[0], comKeys.v[1], comKeys.v[2], comKeys.v[3]);
}

void func_8010603C_mstory3(void) {
    HuWinHomeClear(D_80115B92_mstory3);
    func_80060C14_main(D_80115B92_mstory3, 1);
}

void func_8010606C_mstory3(void) {
    func_80060EA8_main(D_80115B92_mstory3, 1);
}

void func_80106090_mstory3(s32 mess) {
    HuWinMesSet(D_80115B92_mstory3, mess, -1, -1);
    while (HuWinStatGet(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

void func_801060E4_mstory3(s32 mess) {
    HuWinMesSet(D_80115B92_mstory3, mess, -1, -1);
    HuWinInsertMesSet(D_80115B92_mstory3, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

s16 func_80106154_mstory3(void) {
    return HuWinChoiceGet(D_80115B92_mstory3, 0, 1);
}

void func_80106184_mstory3(void) {
    espDispOn(D_80115B94_mstory3);
}

void func_801061A4_mstory3(void) {
    espDispOff(D_80115B94_mstory3);
}

void func_801061C4_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    Hu3DMotionTimeSet(D_80115B96_mstory3, 0.0f);
    Hu3DMotionSpeedSet(D_80115B96_mstory3, 2.0f);
}

void func_80106220_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 4);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    Hu3DMotionTimeSet(D_80115B96_mstory3, Hu3DData[D_80115B96_mstory3].motTime);
}

void func_80106284_mstory3(void) {
    s16 i = 0;

    Hu3DData[D_80115B96_mstory3].rot.y += -10.6f;
    while (i < 5) {
        Hu3DData[D_80115B96_mstory3].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    }
}

void func_80106340_mstory3(void) {
    D_80115B94_mstory3 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_80115B94_mstory3, 160, 120);
    espAttrSet(D_80115B94_mstory3, 0x4000);
    D_80115B96_mstory3 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80115B96_mstory3, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80115B96_mstory3, 2, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 1);
}

void func_80106400_mstory3(s32 arg0) {
    D_80115BBC_mstory3 = arg0;
    D_80115288_mstory3 = 0;
    omAddPrcObj(func_8010643C_mstory3, 0x1000, 0x800, 0);
}

void func_8010643C_mstory3(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    D_80115B98_mstory3[0] = espEntry(func_8000B838_main(0x1D0001), 0, 0);
    espPosSet(D_80115B98_mstory3[0], 160, 120);
    espDispOff(D_80115B98_mstory3[0]);
    for (i = 0; i < 7; i++) {
        D_80115B98_mstory3[i + 1] = espEntry(func_8000B838_main(D_80115510_mstory3[i]), 0, 0);
        espPosSet(D_80115B98_mstory3[i + 1], D_8011552C_mstory3[i][0] + 48, D_8011552C_mstory3[i][1] + 48);
        espAttrSet(D_80115B98_mstory3[i + 1], 8);
        espDispOff(D_80115B98_mstory3[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_80115BA8_mstory3[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = D_8011552C_mstory3[D_80115BBC_mstory3][0] + 48;
        y = D_8011552C_mstory3[D_80115BBC_mstory3][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(D_80115BA8_mstory3[i], x, y);
        espAttrSet(D_80115BA8_mstory3[i], 0x1000);
        espColorSet(D_80115BA8_mstory3[i], 255, 255, 192);
        espAttrSet(D_80115BA8_mstory3[i], 8);
        espScaleSet(D_80115BA8_mstory3[i], 1.5f, 1.5f);
        espTPLvlSet(D_80115BA8_mstory3[i], 255);
        espDispOff(D_80115BA8_mstory3[i]);
    }
    HuMemMemoryFreePerm(data);
    D_80115BB8_mstory3 = espEntry(func_8000B838_main(0x1D0000), 0, 0);
    espPosSet(D_80115BB8_mstory3, 160, 120);
    espScaleSet(D_80115BB8_mstory3, 40.0f, 30.0f);
    espAttrSet(D_80115BB8_mstory3, 0);
    espDispOff(D_80115BB8_mstory3);
    omPrcSetDestructor(0, func_80106CE8_mstory3);
    espDispOn(D_80115BB8_mstory3);
    espTPLvlSet(D_80115BB8_mstory3, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_80115BB8_mstory3, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_80115BB8_mstory3, 256);
    for (i = 0; i < D_80115BBC_mstory3; i++) {
        espDispOn(D_80115B98_mstory3[i + 1]);
    }
    func_801061A4_mstory3();
    espDispOn(D_80115B98_mstory3[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_80115BB8_mstory3, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_80115BB8_mstory3);
    espTPLvlSet(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 0);
    espDispOn(D_80115B98_mstory3[D_80115BBC_mstory3 + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 255);
    espScaleSet(D_80115B98_mstory3[D_80115BBC_mstory3 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(D_80115BA8_mstory3[i], 0, 0);
        func_8000BDDC_main(D_80115BA8_mstory3[i], 1);
        espDispOn(D_80115BA8_mstory3[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(D_80115BA8_mstory3[i]);
    }
    if (D_80115BBC_mstory3 == 6) {
        HuPrcSleep(40);
        espDispOn(D_80115BB8_mstory3);
        espTPLvlSet(D_80115BB8_mstory3, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_80115BB8_mstory3, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(D_80115BB8_mstory3, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_80115BB8_mstory3, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(D_80115BB8_mstory3);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(D_80115BB8_mstory3);
    espTPLvlSet(D_80115BB8_mstory3, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_80115BB8_mstory3, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_80115BB8_mstory3, 256);
    espDispOff(D_80115B98_mstory3[D_80115BBC_mstory3 + 1]);
    espDispOff(D_80115B98_mstory3[0]);
    func_80106184_mstory3();
    HuPrcSleep(30);
    for (i = 0; i < D_80115BBC_mstory3; i++) {
        espDispOff(D_80115B98_mstory3[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_80115BB8_mstory3, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_80115BB8_mstory3);
    D_80115288_mstory3 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106CDC_mstory3(void) {
    return D_80115288_mstory3;
}

void func_80106CE8_mstory3(void) {
}

void func_80106CF0_mstory3(s16 model, s16 animSlot, s16 anim) {
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

void func_80106DC4_mstory3(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106DE0_mstory3(obj, pos, frames, 1);
}

void func_80106DE0_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void func_80107014_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DC4_mstory3(obj, &pos, frames);
}

void func_80107040_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DE0_mstory3(obj, &pos, frames, arg3);
}

void func_80107070_mstory3(omObjData *obj, const Vec *target, s32 frames) {
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

void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80107070_mstory3(obj, &pos, frames);
}

void func_80107244_mstory3(s16 model) {
    HuPrcSleep(10);
    while (!func_80107290_mstory3(model)) {
        HuPrcVSleep();
    }
}

s32 func_80107290_mstory3(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames) {
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

void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames) {
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

void func_80107674_mstory3(omObjData *obj, omObjData *target) {
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

void func_801077BC_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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
            Hu3DModelPosSet(obj->model[2], cur.x, cur.y - 5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, pos->y - 5.0f, pos->z);
    }
    HuPrcVSleep();
}

// Code matches, but the target is followed by alignment padding, which suggests
// a file boundary after this function.
#ifdef NON_MATCHING
void func_80107A18_mstory3(omObjData *obj, Vec *target, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec vel;
    Vec pos;
    Vec accel;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = target->x - start.x;
    diff.y = target->y - start.y;
    diff.z = target->z - start.z;
    if (faceDir) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    t = frames;
    accel.x = diff.x / t / 90.0f;
    accel.y = diff.y / t / 90.0f;
    accel.z = diff.z / t / 90.0f;
    vel.x = diff.x / t;
    vel.y = diff.y / t;
    vel.z = diff.z / t;
    pos.x = start.x;
    pos.y = start.y;
    pos.z = start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        if (t < 50.0f) {
            pos.x += vel.x;
            pos.y += vel.y;
            pos.z += vel.z;
        } else {
            pos.x += vel.x += accel.x;
            pos.y += vel.y += accel.y;
            pos.z += vel.z += accel.z;
        }
        if (pos.x <= target->x) {
            pos.x = target->x;
            pos.y = target->y;
            pos.z = target->z;
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            if (obj->model[2] >= 0) {
                Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
            }
            break;
        }
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, target->x, target->y, target->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], target->x, target->y - 5.0f, target->z);
    }
    HuPrcVSleep();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107A18_mstory3);
#endif

MstoryPath *func_80107D80_mstory3(Vec *points, s32 flags) {
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

void func_80108084_mstory3(MstoryPath *path, f32 time, Vec *result) {
    f32 values[4];
    f32 times[4];
    Vec *points;
    f32(*interval)[2];
    s16 i;

    if (time >= 1.0f) {
        result->x = path->points[path->count - 1].x;
        result->y = path->points[path->count - 1].y;
        result->z = path->points[path->count - 1].z;
        return;
    }
    interval = path->intervals;
    for (i = 0; i < path->count; i++, interval++) {
        if (time <= (*interval)[0]) {
            break;
        }
    }
    i--;
    if (i < 0) {
        i = 0;
    }
    if (i >= path->count - 1) {
        i--;
    }
    interval = path->intervals;
    if (path->flags & 1) {
        times[0] = i == 0 ? -(1.0f - interval[path->count - 1][0]) : interval[i - 1][0];
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[path->count - 1].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[0].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[0].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[0].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = interval[i - 1][0];
        }
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[0].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    }
}

void func_8010892C_mstory3(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010895C_mstory3(void) {
    D_80115C9C_mstory3 = GwStory.unk1;
    if (D_80115C9C_mstory3 == 0) {
        D_80115C9E_mstory3 = 1;
    } else {
        D_80115C9E_mstory3 = 0;
    }
    func_80105F54_mstory3();
    D_80115C9A_mstory3 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010A23C_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B154_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010BC34_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C4B0_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C870_mstory3, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108C34_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C65C_mstory3, 0x1001, 0x1000, 0);
    omAddPrcObj(func_80108A9C_mstory3, 0x1001, 0x1000, 0);
    func_8001C258_main(D_80115C9A_mstory3, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80108A94_mstory3(omObjData *obj) {
}

void func_80108A9C_mstory3(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_80115BC0_mstory3[0].unk_0C == 1 && Hu3DData[D_80115BC0_mstory3[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_80115BC0_mstory3[0].unk_10, D_80115C9C_mstory3);
        }
        if (D_80115BC0_mstory3[1].unk_0C == 1 && Hu3DData[D_80115BC0_mstory3[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_80115BC0_mstory3[1].unk_10, D_80115C9E_mstory3);
            z = Hu3DData[D_80115BC0_mstory3[1].obj->model[1]].pos.z;
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

void func_80108C34_mstory3(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_80115BC0_mstory3[5].obj = obj;
    D_80115BC0_mstory3[5].unk_08 = 0;
    D_80115BC0_mstory3[5].func = func_80108CA8_mstory3;

    for (;;) {
        D_80115BC0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108CA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108E28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A23C_mstory3);

void func_8010A7C8_mstory3(void) {
}

void func_8010A7D0_mstory3(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_801156C8_mstory3);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107244_mstory3(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80107244_mstory3(model);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[0].unk_08 = 1;
}

void func_8010A8EC_mstory3(omObjData *obj) {
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
    D_80115BC0_mstory3[0].func = func_8010AB34_mstory3;
}

void func_8010AB34_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

void func_8010AB54_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_80115BC0_mstory3[0].unk_0C = 1;
    D_80115BC0_mstory3[0].unk_10 = 31;
    func_8010733C_mstory3(obj, 3.5f, 15);
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8E_mstory3);
    func_80106CF0_mstory3(D_80115BC0_mstory3[1].obj->model[1], D_80115C98_mstory3, D_80115C96_mstory3);
    D_80115BC0_mstory3[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_80115BC0_mstory3[1].obj->model[1], Hu3DData[D_80115BC0_mstory3[1].obj->motion[4]].motId, 0, 10, 2);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

void func_8010ACBC_mstory3(omObjData *obj) {
    Vec pos = D_801156D4_mstory3;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106DC4_mstory3(obj, &target, 10);
    func_80107244_mstory3(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115C90_mstory3, D_80115C8A_mstory3[0]);
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

void func_8010AF28_mstory3(omObjData *obj) {
    Vec pos = D_801156E0_mstory3;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &pos, 10);
    D_80115BC0_mstory3[2].func = func_8010C3F4_mstory3;
    func_8004AC98_main(D_80115C9C_mstory3 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[0].unk_08 = 10;
    while (TRUE) {
        if (D_80115BC0_mstory3[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_80115BC0_mstory3[0].unk_0C = 1;
    D_80115BC0_mstory3[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106DC4_mstory3(obj, &target, 60);
    D_80115BC0_mstory3[0].unk_0C = 0;
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

void func_8010B154_mstory3(void) {
    s16 chrs[2] = { 0, 1 };
    s32 motIds[2] = { 0x3B, 0x44 };
    omObjData *obj;
    s16 idx;
    void *data;

    idx = D_80115C9C_mstory3 == 0;
    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[1].obj = obj;
    D_80115BC0_mstory3[1].unk_08 = 0;
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[1].unk_0C = 0;
    D_80115BC0_mstory3[1].unk_10 = 31;
    if (idx == 0) {
        obj->model[1] = func_8000B108_main(0x200A0, 0x2A9);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2A9);
    }
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chrs[idx], 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chrs[idx], 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chrs[idx], 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chrs[idx], 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chrs[idx], 0x72));
    func_8000B460_main(obj, 5, motIds[idx] | 0x1D0000);
    func_8000B460_main(obj, 6, func_80017BB8_main(chrs[idx], 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(chrs[idx], 0x33));
    func_8000B460_main(obj, 8, func_80017BB8_main(chrs[idx], 0x2F));
    if (D_80115C9C_mstory3 == 0) {
        func_8000B460_main(obj, 9, 0x1D0045);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C44_mstory3 = D_80115554_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C44_mstory3.x, D_80115C44_mstory3.y, D_80115C44_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C44_mstory3.x, D_80115C44_mstory3.y - -5.0f, D_80115C44_mstory3.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA4));
    D_80115C92_mstory3[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_801153A0_mstory3[idx]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C92_mstory3[0], 1, 0);
    Hu3DAnimBankSet(D_80115C92_mstory3[0], 0);
    D_80115C98_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115C92_mstory3[0], 0, D_801153A0_mstory3[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA9));
    D_80115C92_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115C98_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115C92_mstory3[0], 0, D_801153A0_mstory3[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xAA));
    D_80115C92_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[0]);
    omPrcSetDestructor(0, func_8010B634_mstory3);
    while (TRUE) {
        D_80115BC0_mstory3[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B634_mstory3(void) {
}

void func_8010B63C_mstory3(omObjData *obj) {
    D_80115BC0_mstory3[1].unk_0C = 1;
    D_80115BC0_mstory3[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010733C_mstory3(obj, 4.5f, 15);
    D_80115BC0_mstory3[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[0].func = func_8010AB54_mstory3;
}

void func_8010B72C_mstory3(omObjData *obj) {
    Vec pos = D_801156EC_mstory3;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106DC4_mstory3(obj, &target, 10);
    func_80107244_mstory3(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115C98_mstory3, D_80115C92_mstory3[0]);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
}

void func_8010B998_mstory3(omObjData *obj) {
    Vec pos = D_801156E0_mstory3;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &pos, 10);
    func_8004AC98_main(D_80115C9E_mstory3 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[1].unk_08 = 10;
    while (TRUE) {
        if (D_80115BC0_mstory3[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_80115BC0_mstory3[1].unk_0C = 1;
    D_80115BC0_mstory3[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106DC4_mstory3(obj, &target, 60);
    D_80115BC0_mstory3[1].unk_0C = 0;
    D_80115BC0_mstory3[0].func = func_80108A94_mstory3;
}

void func_8010BBB4_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(D_80115BC0_mstory3[1].obj->model[1], Hu3DData[D_80115BC0_mstory3[1].obj->motion[9]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    D_80115BC0_mstory3[1].func = func_80108A94_mstory3;
}

void func_8010BC34_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(10, 20, 20, -1, NULL);
    D_80115BC0_mstory3[2].obj = obj;
    D_80115BC0_mstory3[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C50_mstory3 = D_80115560_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C50_mstory3.x, D_80115C50_mstory3.y, D_80115C50_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C50_mstory3.x, -5.0f, D_80115C50_mstory3.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_80115C80_mstory3[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_801156F8_mstory3);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C80_mstory3[0], 1, 0);
    Hu3DAnimBankSet(D_80115C80_mstory3[0], 0);
    D_80115C86_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115C80_mstory3[0], 0, D_801156F8_mstory3);
    data = DataRead(0xA0083);
    D_80115C80_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115C86_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115C80_mstory3[0], 0, D_801156F8_mstory3);
    data = DataRead(0xA0080);
    D_80115C80_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    omPrcSetDestructor(0, func_8010BF40_mstory3);
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    while (TRUE) {
        D_80115BC0_mstory3[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BF40_mstory3(void) {
}

void func_8010BF48_mstory3(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_80115704_mstory3;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &target, 5);
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[0]);
    Hu3DMotionShiftSet(D_80115BC0_mstory3[1].obj->model[1], Hu3DData[D_80115BC0_mstory3[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_80115C9C_mstory3 != 0 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_80115C9E_mstory3), 0x60);
    D_80115BC0_mstory3[2].func = func_8010C15C_mstory3;
    D_80115BC0_mstory3[2].unk_08 = 5;
}

void func_8010C15C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

void func_8010C17C_mstory3(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
}

void func_8010C23C_mstory3(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_80115710_mstory3;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106CF0_mstory3(model, D_80115C86_mstory3, D_80115C80_mstory3[1]);
    Hu3DMotionShiftSet(D_80115BC0_mstory3[2].obj->model[1], Hu3DData[D_80115BC0_mstory3[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_80107070_mstory3(obj, &target, 10);
    D_80115BC0_mstory3[2].func = func_80108A94_mstory3;
    D_80115BC0_mstory3[2].unk_08 = 1;
}

void func_8010C3F4_mstory3(omObjData *obj) {
    Vec pos = D_8011571C_mstory3;

    func_80106CF0_mstory3(obj->model[1], D_80115C86_mstory3, D_80115C80_mstory3[0]);
    func_80107070_mstory3(obj, &pos, 10);
    while (TRUE) {
        func_80107674_mstory3(D_80115BC0_mstory3[2].obj, D_80115BC0_mstory3[0].obj);
        HuPrcVSleep();
    }
}

void func_8010C490_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[0].obj);
}

void func_8010C4B0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_80115BC0_mstory3[3].obj = obj;
    D_80115BC0_mstory3[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C9A_mstory3);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C5C_mstory3 = D_8011556C_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C5C_mstory3.x, D_80115C5C_mstory3.y, D_80115C5C_mstory3.z);
    Hu3DModelPosSet(obj->model[2], D_80115C5C_mstory3.x, -5.0f, D_80115C5C_mstory3.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C654_mstory3);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
    while (1) {
        D_80115BC0_mstory3[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C654_mstory3(void) {
}

void func_8010C65C_mstory3(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_80115BC0_mstory3[3].obj;
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
        if (D_80115C88_mstory3 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_8010C7A0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

void func_8010C7C0_mstory3(omObjData *obj) {
    Vec pos = D_801156E0_mstory3;

    func_80107070_mstory3(obj, &pos, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

void func_8010C810_mstory3(void) {
    Vec pos = D_80115728_mstory3;

    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &pos, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

void func_8010C870_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 20, 20, -1, NULL);
    D_80115BC0_mstory3[4].obj = obj;
    D_80115BC0_mstory3[4].unk_08 = 0;
    D_80115BC0_mstory3[4].func = func_80108A94_mstory3;
    obj->model[1] = func_8000B108_main(0x1D0007, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_80115C68_mstory3 = D_80115578_mstory3;
    Hu3DModelPosSet(obj->model[1], D_80115C68_mstory3.x, D_80115C68_mstory3.y, D_80115C68_mstory3.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C9E0_mstory3);
    while (1) {
        D_80115BC0_mstory3[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C9E0_mstory3(void) {
}
