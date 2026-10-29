#include "common.h"
#include "mallocblock.h"
#include "overlays/minigame.h"

typedef struct {
    f32 posX[6];
    f32 posY[6];
    f32 posZ[6];
    s32 flags[6];
} DorrieDipEffects;

typedef struct {
    f32 posX[6];
    f32 posY[6];
    f32 posZ[6];
    f32 scaleX[6];
    s32 flags[6];
} DorrieDipWakes;

typedef struct {
    s32 grabDelay;
    s32 targetDip;
    s32 triggered;
} DorrieDipCpu;

typedef struct {
    u8 unk00[3];
    u8 unk03;
    u8 unk04;
    u8 unk05[3];
    f32 unk08;
    u8 unk0C[0xA8];
} DorrieDipBackground;

typedef struct {
    s32 flags;
    Vec hookPos;
    s32 grabTimer;
} DorrieDipDorrie;

typedef struct {
    Vec pos;
    f32 unk0C;
    f32 unk10;
    s32 unk14;
    f32 unk18;
    f32 unk1C;
} DorrieDipData;

typedef struct {
    s32 unk00[6];
    f32 unk18[6];
    f32 unk30[6];
} DorrieDipDips;

// One entry per player.
typedef struct {
    f32 posX[5];
    f32 posY[5];
    f32 posZ[5];
    f32 velY[5];
    f32 unk50[5];
    f32 unk64[5];
    f32 unk78[5];
    f32 unk8C[5];
    s32 flags[5];
    s32 playerIdx[5];
} DorrieDipSplashes; // sizeof 0xC8

extern s32 D_8010A1FC_dorrie_dip;

extern omObjData *D_8010A230_dorrie_dip;

extern omObjData *D_8010A234_dorrie_dip;

extern omObjData *D_8010A238_dorrie_dip;

extern omObjData *D_8010A23C_dorrie_dip;

extern void *D_800EBEB0_minigame;
extern f32 D_800EB774_minigame;
extern D_80111B50_vine_with_me_Struct D_8010A040_dorrie_dip;
extern s32 D_8010A1F4_dorrie_dip;
extern u8 D_8010A1F8_dorrie_dip;

extern u16 D_800A11D0_main[];
extern u16 D_800A11DC_main[];
extern s32 D_800A178C_main[][6];
extern s32 D_8010A240_dorrie_dip;
extern f32 D_8010A244_dorrie_dip;
extern omObjData *D_8010A248_dorrie_dip;
extern omObjData *D_8010A24C_dorrie_dip;
extern s32 D_8010A250_dorrie_dip;
extern f32 D_8010A1F0_dorrie_dip;
extern s16 D_8010A1FA_dorrie_dip;
extern s16 D_8010A1FE_dorrie_dip;
extern s32 D_8010A200_dorrie_dip;
extern omObjData *D_8010A224_dorrie_dip[2];
extern f32 D_8010A22C_dorrie_dip;
extern s32 D_8010A068_dorrie_dip;
extern s32 D_8010A06C_dorrie_dip;
extern s32 D_8010A208_dorrie_dip[6];
extern s32 D_8010A220_dorrie_dip;
extern u8 D_8010A046_dorrie_dip;
extern omObjData *D_8010A260_dorrie_dip;
extern DorrieDipCpu D_8010A254_dorrie_dip;

void func_8004AD70_main(void);
void func_800557A0_main(void);
s32 func_8000B638_main(void);
void func_80105FD0_dorrie_dip(omObjData *);
void func_80106210_dorrie_dip(omObjData *);
void func_80106668_dorrie_dip(omObjData *);
void func_80106E14_dorrie_dip(omObjData *, s32);
void func_80107360_dorrie_dip(omObjData *);
void func_801079D4_dorrie_dip(omObjData *);
void func_8010898C_dorrie_dip(omObjData *);
void func_80108C6C_dorrie_dip(omObjData *);
void func_801095FC_dorrie_dip(omObjData *);
void func_800E1490_minigame(u16);
void func_800E5798_minigame(omObjData *, u16);
omObjData *func_80045ED0_main(u32);
void func_800E1370_minigame(omObjData *, s32, f32);
void func_80107EE0_dorrie_dip(omObjData *);
void func_80109F00_dorrie_dip(void);
void func_80037114_main(s16, f32, f32);
void func_80106BC0_dorrie_dip(void);
void func_800DDD94_minigame(omObjData *);
void func_800E6F0C_minigame(u8);
void func_800E149C_minigame(omObjData *, s32, s32);
void func_8001EF6C_main(s16, s16, char *);
void func_8010971C_dorrie_dip(void);
void func_801064FC_dorrie_dip(void);
void func_80109E1C_dorrie_dip(s32);
void func_80108A74_dorrie_dip(s16, char *, s16, Vec *);
void func_80016B00_main(s16, s16, char *, HuMtx4F);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_80017D24_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
void func_80018044_main(HuMtx4F, HuMtx4F, HuMtx4F);
void func_801074CC_dorrie_dip(void);
void func_80108148_dorrie_dip(void);
void func_80106D50_dorrie_dip(void);
void func_80108700_dorrie_dip(void);
void func_80108678_dorrie_dip(void);
void func_80108458_dorrie_dip(void);
void func_801081A8_dorrie_dip(void);
void func_80108EA0_dorrie_dip(s32);
void func_801092E0_dorrie_dip(void);
void func_801090C4_dorrie_dip(void);
void func_80021BE0_main(void **, s32);
void func_80105B44_dorrie_dip(f32, f32, f32, f32, f32, f32, f32);
void func_80105C7C_dorrie_dip(omObjData *);
void func_8010601C_dorrie_dip(void);
void func_80106538_dorrie_dip(void);
void func_80106DB8_dorrie_dip(omObjData *);
void func_80107690_dorrie_dip(void);
void func_80107D58_dorrie_dip(void);
void func_80108800_dorrie_dip(void);
void func_80108B98_dorrie_dip(void);
void func_80109520_dorrie_dip(void);
void func_801096F0_dorrie_dip(void);
void func_80109978_dorrie_dip(void);
void func_80109B28_dorrie_dip(void);
void func_80109C14_dorrie_dip(omObjData *);

void func_80106BEC_dorrie_dip(void);

void func_801074F8_dorrie_dip(void);

void func_80108174_dorrie_dip(void);

void func_801081D4_dorrie_dip(void);

void func_80108484_dorrie_dip(void);

void func_801086A4_dorrie_dip(void);

void func_8010872C_dorrie_dip(void);

void func_801090F0_dorrie_dip(void);

void func_8010930C_dorrie_dip(void);

void func_80109738_dorrie_dip(void);

void func_801059A0_dorrie_dip(void) {
    omObjData *obj;

    omInitObjMan(30, 10);
    Hu3DAnimInit(16);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_80105B44_dorrie_dip(500.0f, 345.0f, 0.0f, 0.0f, 0.0f, 190.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    func_800E5EA0_minigame(&D_8010A040_dorrie_dip);
    D_800EBE28_minigame = 0;
    D_800EC280_minigame = 0;
    func_800E18D8_minigame();
    D_800EB774_minigame = 1.0f;
    WipeCreateIn(0xFF, 16);
    func_80108800_dorrie_dip();
    omAddObj(0x50, 0, 0, -1, func_80105C7C_dorrie_dip);
    func_8010601C_dorrie_dip();
    func_80106538_dorrie_dip();
    omAddObj(4, 10, 60, -1, func_80106DB8_dorrie_dip);
    func_80107690_dorrie_dip();
    func_80107D58_dorrie_dip();
    func_80108B98_dorrie_dip();
    func_80109520_dorrie_dip();
    func_801096F0_dorrie_dip();
    func_80109978_dorrie_dip();
    func_80109B28_dorrie_dip();
    D_8010A1F8_dorrie_dip = 0;
}

void func_80105B44_dorrie_dip(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    func_8000B5F0_main(1);
    D_8010A1F4_dorrie_dip = func_8000B638_main();
    ScissorSet(D_8010A1F4_dorrie_dip, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010A1F4_dorrie_dip, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCamSetPerspective(D_8010A1F4_dorrie_dip, 41.5f, 80.0f, 8000.0f);
}

void func_80105C7C_dorrie_dip(omObjData *obj) {
    s32 i;

    if (D_800D530C_main != 0) {
        func_8004AD70_main();
        HuAudSeqFadeOut(30);
        WipeCreateOut(0, 20);
    }
    switch (func_800E6F40_minigame(obj)) {
        case 0:
            if (func_800E6E9C_minigame() == 30) {
                func_801074CC_dorrie_dip();
            }
            if (func_800E6E9C_minigame() == 60) {
                func_80108148_dorrie_dip();
            }
            if (func_800E6E9C_minigame() == 120) {
                func_80106D50_dorrie_dip();
            }
            if (D_8010A068_dorrie_dip == func_800E6E9C_minigame()) {
                if (D_8010A068_dorrie_dip == 1) {
                    HuAudSeqPlay(0x44);
                }
                HuAudFXPlay(0x4E7);
                D_8010A068_dorrie_dip += 30 + rand8() / 8;
            }
            if (D_8010A06C_dorrie_dip == func_800E6E9C_minigame()) {
                HuAudFXPlay(0x4E8);
                D_8010A06C_dorrie_dip += 30 + rand8() / 8;
            }
            break;
        case 2:
            if (func_800E6E9C_minigame() == 0) {
                func_80108700_dorrie_dip();
                func_80108678_dorrie_dip();
            }
            break;
        case 3:
            if (func_800E6E9C_minigame() == 1) {
                if (D_8010A1F8_dorrie_dip == 2) {
                    func_80108458_dorrie_dip();
                } else {
                    func_801081A8_dorrie_dip();
                    for (i = 0; i < 6; i++) {
                        if (i != D_8010A220_dorrie_dip) {
                            func_80108EA0_dorrie_dip(i);
                        }
                    }
                }
                if (D_8010A220_dorrie_dip == -1 || D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] == 17) {
                    D_8010A046_dorrie_dip = 7;
                } else {
                    D_8010A046_dorrie_dip = 5;
                }
            }
            if (func_800E6E9C_minigame() == 15 && D_8010A220_dorrie_dip != -1 &&
                D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 17) {
                func_80108EA0_dorrie_dip(D_8010A220_dorrie_dip);
                func_801092E0_dorrie_dip();
            }
            break;
        case 4:
            if (func_800E6E9C_minigame() == 1) {
                func_801090C4_dorrie_dip();
            }
            break;
        case 5:
            if (D_8010A220_dorrie_dip != -1 && D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 17) {
                GwPlayer[D_8010A1FC_dorrie_dip].bonusCoin = D_8010A208_dorrie_dip[D_8010A220_dorrie_dip];
            } else {
                GwPlayer[D_8010A1FC_dorrie_dip].bonusCoin = -1;
            }
            WipeCreateOut(0, 20);
            obj->func = func_80105FD0_dorrie_dip;
            break;
    }
}

void func_80105FD0_dorrie_dip(omObjData *obj) {
    func_8004AB0C_main(30);
    if (WipeStatGet() == 0) {
        func_8005F524_main();
        GMesClose();
        func_800557A0_main();
        omOvlReturnEx(1);
    }
}

void func_8010601C_dorrie_dip(void) {
    s32 i;
    omObjData *obj;
    DorrieDipDips *dips;
    s32 modelFlags = 0x699;
    s32 splashFlags = 0x69D;

    obj = omAddObj(250, 12, 0, -1, func_80106210_dorrie_dip);
    D_8010A230_dorrie_dip = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipDips), 0x7918);
    dips = obj->data;
    for (i = 0; i < 6; i++) {
        dips->unk00[i] = 0;
        dips->unk18[i] = i * 60.0f;
        dips->unk30[i] = 0;
        if (i == 0) {
            obj->model[i] = func_8000B108_main(0x5F0002, modelFlags);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i + 6] = func_8000B108_main(0x5F000B, splashFlags);
            Hu3DModelRotSet(obj->model[i + 6], 0.0f, 0.0f, 0.0f);
        } else {
            obj->model[i + 6] = Hu3DModelLink(obj->model[6]);
            Hu3DModelRotSet(obj->model[i + 6], 0.0f, 0.0f, 0.0f);
        }
        func_8001C814_main(obj->model[i + 6], 2, 2);
    }
}

void func_80106210_dorrie_dip(omObjData *obj) {
    s32 i;
    DorrieDipDips *dips = obj->data;
    f32 x, y, z;

    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        y = D_8010A22C_dorrie_dip;
        z = cosdf(dips->unk18[i]) * 450.0f;
        if (i == 0) {
            omSetTra(obj, x, y, z);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], x, y, z);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
        }
    }
    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        z = cosdf(dips->unk18[i]) * 450.0f;
        Hu3DModelPosSet(obj->model[i + 6], x, 0.0f, z);
        Hu3DModelRotSet(obj->model[i + 6], 0.0f, dips->unk18[i], 0.0f);
    }
    for (i = 0; i < 6; i++) {
        if (dips->unk00[i] & 1) {
            dips->unk18[i] -= dips->unk30[i];
            if (dips->unk18[i] <= 0.0f) {
                dips->unk18[i] += 360.0f;
            }
            dips->unk30[i] += 0.2f;
            if (dips->unk30[i] > 4.8f) {
                dips->unk30[i] = 4.8f;
            }
            if (dips->unk30[i] >= 4.0f && dips->unk30[i] < 4.2f) {
                func_8001C258_main(D_8010A230_dorrie_dip->model[i + 6], 4, 0);
                func_8001C814_main(D_8010A230_dorrie_dip->model[i + 6], 2, 2);
            }
        }
    }
}

void func_801064FC_dorrie_dip(void) {
    s32 i;
    DorrieDipDips *dips = (DorrieDipDips *)D_8010A230_dorrie_dip->data;

    for (i = 0; i < 6; i++) {
        dips->unk00[i] |= 1;
    }
}

void func_80106538_dorrie_dip(void) {
    omObjData *obj;
    DorrieDipDorrie *data;

    obj = omAddObj(255, 1, 5, -1, func_80106668_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DorrieDipDorrie), 0x7918);
    D_8010A238_dorrie_dip = obj;
    data = obj->data;
    obj->model[0] = func_8000B108_main(0x5F0005, 0x699);
    func_8000B460_main(obj, 0, 0x5F0006);
    func_8000B460_main(obj, 1, 0x5F0007);
    func_8000B460_main(obj, 2, 0x5F0008);
    func_8000B460_main(obj, 3, 0x5F0009);
    func_8000B460_main(obj, 4, 0x5F000A);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    data->flags = 0;
    data->grabTimer = 0;
    D_8010A220_dorrie_dip = -1;
    omSetRot(obj, 0.0f, 270.0f, 0.0f);
}

void func_80106668_dorrie_dip(omObjData *obj) {
    Vec hookPos;
    s32 i;
    s32 splashIdx;
    f32 time;
    DorrieDipDorrie *data = obj->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    DorrieDipSplashes *splashes = D_8010A23C_dorrie_dip->data;
    DorrieDipData *item = D_8010A234_dorrie_dip->data;

    if ((data->flags & 2) && HmfModelData[obj->model[0]].unk40 == 50.0f &&
        data->hookPos.y < 20.0f && D_8010A220_dorrie_dip == -1 && data->grabTimer < 15) {
        if (data->grabTimer == 0) {
            func_8001C814_main(obj->model[0], 8, 8);
        }
        for (i = 0; i < 6; i++) {
            if (dips->unk18[i] >= 265.0f && dips->unk18[i] < 275.0f) {
                D_8010A220_dorrie_dip = i;
                omVibrate(D_8010A1FE_dorrie_dip, 10, 0, 10);
                break;
            }
        }
        if (D_8010A220_dorrie_dip != -1) {
            func_8001EF6C_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip], obj->model[0], "item_hook");
            func_8001C258_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip], 0x4000, 0x4000);
            func_8001C258_main(D_8010A230_dorrie_dip->model[D_8010A220_dorrie_dip + 6], 4, 4);
            dips->unk00[D_8010A220_dorrie_dip] &= ~1;
            func_8001C814_main(obj->model[0], 8, 0);
            if (D_8010A220_dorrie_dip == D_8010A200_dorrie_dip) {
                item->unk14 |= 4;
            } else {
                splashIdx = -1;
                for (i = 0; i < 5; i++) {
                    if (splashes->playerIdx[i] == D_8010A220_dorrie_dip) {
                        splashIdx = i;
                    }
                }
                splashes->flags[splashIdx] |= 4;
                HuAudFXPlay(0x4E6);
            }
        }
        data->grabTimer++;
        if (data->grabTimer == 15) {
            func_8001C814_main(obj->model[0], 8, 0);
        }
    }
    if (data->flags & 4) {
        time = HmfModelData[obj->model[0]].unk40;
        if ((time >= 28.0f) & (time < 30.0f)) {
            HuAudFXPlay(0x4E3);
        }
        if (time >= D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02) {
            data->flags &= ~4;
            func_8001C624_main(obj->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[0]].unk02, 0, 10, 0);
            func_8001C814_main(obj->model[0], 2, 2);
        }
        if (HmfModelData[obj->model[0]].unk40 == 50.0f) {
            func_8001C814_main(D_8010A224_dorrie_dip[0]->model[1], 8, 0);
            func_8001C814_main(D_8010A224_dorrie_dip[0]->model[1], 2, 2);
            func_8010971C_dorrie_dip();
            func_801064FC_dorrie_dip();
            for (i = 0; i < 6; i++) {
                func_80109E1C_dorrie_dip(i);
            }
        }
    }
    func_80108A74_dorrie_dip(obj->model[0], "item_hook", HmfModelData[obj->model[0]].unk40, &hookPos);
    data->hookPos.x = hookPos.x;
    data->hookPos.y = hookPos.y;
    data->hookPos.z = hookPos.z;
}

void func_80106BC0_dorrie_dip(void) {
    omAddPrcObj(func_80106BEC_dorrie_dip, 0x50, 0, 0);
}

void func_80106BEC_dorrie_dip(void) {
    DorrieDipDorrie *data = D_8010A238_dorrie_dip->data;

    func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[1]].unk02, 0, 10, 0);
    data->flags |= 2;
    while (HmfModelData[D_8010A238_dorrie_dip->model[0]].unk40 <
           D_800CCF58_main[HmfModelData[D_8010A238_dorrie_dip->model[0]].unk02].unk02) {
        HuPrcVSleep();
    }
    func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[0]].unk02, 0, 10, 0);
    func_8001C814_main(D_8010A238_dorrie_dip->model[0], 2, 2);
    data->flags &= ~2;
    func_800E6F0C_minigame(3);
    omDelPrcObj(NULL);
}

void func_80106D50_dorrie_dip(void) {
    omObjData *obj = D_8010A238_dorrie_dip;
    DorrieDipDorrie *data = obj->data;

    data->flags |= 4;
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 0xA, 0);
}

void func_80106DB8_dorrie_dip(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010A1FC_dorrie_dip = i;
            break;
        }
    }
    func_80106E14_dorrie_dip(obj, D_8010A1FC_dorrie_dip);
}

void func_80106E14_dorrie_dip(omObjData *obj, s32 playerIdx) {
    s32 motion0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    s32 motion1[8] = { 4, 4, 4, 4, 4, 4, 4, 4 };
    s32 motion2[8] = { 31, 31, 31, 31, 31, 31, 31, 31 };
    s32 motion3[8] = { 54, 54, 54, 54, 54, 54, 54, 54 };
    s32 motion4[8] = { 53, 53, 53, 53, 53, 53, 53, 53 };
    s32 motion5[8] = { 15, 15, 15, 15, 15, 15, 15, 15 };
    s32 motion6[8] = { 6, 6, 6, 6, 6, 6, 6, 6 };
    s32 motion7[8] = { 156, 156, 156, 156, 156, 156, 156, 156 };
    s32 character;
    s32 model, motion;
    func_800E1BA8_minigame_ObjData *data;

    D_800EC598_minigame[D_800EC280_minigame++] = obj;
    character = GwPlayer[playerIdx].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A178C_main[character][3];
    func_800E1BA8_minigame(obj, model, motion, playerIdx, 0x20A99, 0x20A99);
    data = obj->data;
    obj->model[3] = func_8000B108_main(3, 0x6DD);
    obj->model[4] = func_8000B108_main(4, 0x6DD);
    obj->model[6] = func_8000B108_main(5, 0x6DD);
    obj->model[5] = func_8000B108_main(6, 0x6DD);
    obj->model[7] = func_8000B108_main(8, 0x6DD);
    obj->model[8] = func_8000B108_main(7, 0x6DD);
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(character, (s16)motion0[character]), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(character, (s16)motion1[character]), 1, 19);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(character, (s16)motion2[character]), 0, 0);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(character, (s16)motion3[character]), 1, 120);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(character, (s16)motion4[character]), 1, 120);
    func_800E5A00_minigame(obj, 18, func_80017BB8_main(character, (s16)motion5[character]), 2, 0);
    func_800E5A00_minigame(obj, 8, func_80017BB8_main(character, (s16)motion6[character]), 1, 29);
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(character, (s16)motion7[character]), 0, 0);
    omSetTra(obj, 50.0f, 133.0f, 0.0f);
    data->unk3C = 270.0f;
    func_800E149C_minigame(obj, 0, 2);
    func_800E149C_minigame(obj, 1, 2);
    func_800E149C_minigame(obj, 2, 2);
    func_800E149C_minigame(obj, 3, 2);
    func_800E149C_minigame(obj, 4, 2);
    func_800E5690_minigame(obj, 0);
    D_8010A240_dorrie_dip = 0;
    obj->func = func_80107360_dorrie_dip;
}

void func_80107360_dorrie_dip(omObjData *obj) {
    func_800E1BA8_minigame_ObjData *data = obj->data;
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    D_800CBB6E_main[data->unk57] = 0;
    D_800D20A1_main[data->unk57] = 0;
    if (GwPlayer[data->unk59].stat & 1) {
        D_800CDA7C_main[data->unk57] = 0;
        D_800D5558_main[data->unk57] = 0;
    }
    if (func_800E6E8C_minigame() == 2 && (GwPlayer[data->unk59].stat & 1)) {
        func_80109F00_dorrie_dip();
    }
    func_800DDD94_minigame(obj);
    if (data->unk5C == 0x200) {
        D_8010A1F8_dorrie_dip = 3;
        if (data->unk5C == 0x200 && data->unk50 == 0x80 && !(D_8010A240_dorrie_dip & 1)) {
            D_8010A240_dorrie_dip |= 1;
            func_80106BC0_dorrie_dip();
        }
    }
    data->unk60 = 0;
    obj->trans.x = x;
    obj->trans.z = z;
}

void func_801074CC_dorrie_dip(void) {
    omAddPrcObj(func_801074F8_dorrie_dip, 0x50, 0, 0);
}

void func_801074F8_dorrie_dip(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        CZoom += (1541.0f - 500.0f) / 30.0f;
        CRot.x += (301.6f - 345.0f) / 30.0f;
        if (CRot.x < 301.6f) {
            CRot.x = 301.6f;
        }
        Center.x += -2.9f / 30.0f;
        Center.y += (98.6f - 190.0f) / 30.0f;
        Center.z += 82.6f / 30.0f;
        HuPrcVSleep();
    }
    CZoom = 1541.0f;
    CRot.x = 301.6f;
    Center.x = -2.9f;
    Center.y = 98.6f;
    Center.z = 82.6f;
    omDelPrcObj(NULL);
}

void func_80107690_dorrie_dip(void) {
    s32 used[16]; // Initialized but unused in the original function.
    s32 itemFiles[16] = { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 };
    omObjData *obj;
    DorrieDipSplashes *splashes;
    DorrieDipDips *dips;
    s32 itemIdx;
    s32 i;
    void *spriteData;
    s16 sprite;

    obj = omAddObj(254, 10, 0, -1, func_801079D4_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DorrieDipSplashes), 0x7918);
    D_8010A23C_dorrie_dip = obj;
    splashes = obj->data;
    dips = D_8010A230_dorrie_dip->data;
    for (i = 0; i < 16; i++) {
        used[i] = 0;
    }
    (void)used;
    D_8010A200_dorrie_dip = (u8)(rand8() % 6);
    D_8010A208_dorrie_dip[D_8010A200_dorrie_dip] = 17;
    itemIdx = 0;
    for (i = 0; i < 6; i++) {
        if (i == D_8010A200_dorrie_dip) {
            continue;
        }
        D_8010A208_dorrie_dip[i] = D_800A11D0_main[itemIdx];
        spriteData = DataRead(itemFiles[D_8010A208_dorrie_dip[i]] | 0x210000);
        sprite = HmfSprModelCreate(spriteData, 0xA99, 8);
        DataClose(spriteData);
        obj->model[itemIdx] = D_800CBB60_main[sprite].modelId;
        func_8001C2FC_main(obj->model[itemIdx], 0x70000000, 0x70000000);
        splashes->posX[itemIdx] = sindf(dips->unk18[i]) * 450.0f;
        splashes->posY[itemIdx] = 1500.0f;
        splashes->posZ[itemIdx] = cosdf(dips->unk18[i]) * 450.0f;
        splashes->playerIdx[itemIdx] = i;
        splashes->unk64[itemIdx] = 30.0f;
        splashes->unk8C[itemIdx] = 0;
        splashes->unk78[itemIdx] = 0;
        if (itemIdx == 0) {
            omSetTra(obj, splashes->posX[itemIdx], splashes->posY[itemIdx], splashes->posZ[itemIdx]);
            omSetSca(obj, 3.0f, 3.0f, 3.0f);
        } else {
            Hu3DModelPosSet(obj->model[itemIdx], splashes->posX[itemIdx], splashes->posY[itemIdx], splashes->posZ[itemIdx]);
            Hu3DModelScaleSet(obj->model[itemIdx], 3.0f, 3.0f, 3.0f);
        }
        splashes->flags[itemIdx] = 0;
        if (itemIdx == 0) {
            obj->model[itemIdx + 5] = func_8000B108_main(9, 0x4A9);
        } else {
            obj->model[itemIdx + 5] = Hu3DModelLink(obj->model[5]);
        }
        itemIdx++;
    }
}

void func_801079D4_dorrie_dip(omObjData *obj) {
    s32 i;
    DorrieDipSplashes *splashes = obj->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    DorrieDipDorrie *dorrie = D_8010A238_dorrie_dip->data;

    for (i = 0; i < 5; i++) {
        if (i == 0) {
            omSetTra(obj, splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        } else {
            Hu3DModelPosSet(obj->model[i], splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        }
        Hu3DModelPosSet(obj->model[i + 5], splashes->posX[i], splashes->unk64[i], splashes->posZ[i]);
        if (splashes->flags[i] & 4) {
            splashes->unk50[i] = 1.0f;
        } else {
            splashes->unk50[i] = (1440.0f - splashes->posY[i]) / 1440.0f;
        }
        Hu3DModelScaleSet(obj->model[i + 5], splashes->unk50[i], 1.0f, splashes->unk50[i]);
        if (splashes->flags[i] & 1) {
            splashes->posX[i] = sindf(dips->unk18[splashes->playerIdx[i]]) * 450.0f;
            splashes->posY[i] = D_8010A22C_dorrie_dip + 60.0f;
            splashes->posZ[i] = cosdf(dips->unk18[splashes->playerIdx[i]]) * 450.0f;
        }
        if (splashes->flags[i] & 2) {
            splashes->posY[i] += splashes->velY[i];
            splashes->velY[i] -= 3.0f;
            if (splashes->posY[i] <= 60.0f) {
                splashes->posY[i] = 60.0f;
                splashes->flags[i] &= ~2;
                splashes->flags[i] |= 1;
            }
        }
        if (splashes->flags[i] & 4) {
            splashes->posX[i] = dorrie->hookPos.x;
            splashes->posY[i] = dorrie->hookPos.y + 80.0f;
            splashes->posZ[i] = dorrie->hookPos.z;
            splashes->unk64[i] = dorrie->hookPos.y + 30.0f;
        }
        if (splashes->flags[i] & 8) {
            splashes->posY[i] = sindf(splashes->unk78[i]) * 50.0f + splashes->unk8C[i];
            splashes->unk78[i] += 5.0f;
            if (splashes->unk78[i] >= 360.0f) {
                splashes->unk78[i] -= 360.0f;
            }
            func_8000CFA4_main(D_8010A1FA_dorrie_dip, splashes->posX[i], splashes->posY[i], splashes->posZ[i]);
        }
    }
}

void func_80107D08_dorrie_dip(void) {
    s32 i;
    DorrieDipSplashes *splashes = (DorrieDipSplashes *)D_8010A23C_dorrie_dip->data;

    for (i = 0; i < 5; i++) {
        splashes->flags[i] |= 2;
        splashes->velY[i] = 0;
        splashes->posY[i] = 1500.0f;
    }
}

void func_80107D58_dorrie_dip(void) {
    omObjData *obj;
    DorrieDipData *data;
    DorrieDipDips *dips;

    obj = omAddObj(254, 2, 3, -1, func_80107EE0_dorrie_dip);
    obj->data = HuMemAllocTag(sizeof(DorrieDipData), 0x7918);
    D_8010A234_dorrie_dip = obj;
    data = obj->data;
    dips = D_8010A230_dorrie_dip->data;
    obj->model[0] = func_8000B108_main(0xA00EE, 0x4B9);
    obj->model[1] = func_8000B108_main(9, 0x4A9);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F6);
    func_8000B460_main(obj, 2, 0xA00F1);
    func_8001C814_main(obj->model[0], 2, 2);
    data->pos.x = sindf(dips->unk18[D_8010A200_dorrie_dip]) * 450.0f;
    data->pos.y = 1500.0f;
    data->pos.z = cosdf(dips->unk18[D_8010A200_dorrie_dip]) * 450.0f;
    data->unk1C = 30.0f;
    data->unk10 = 0;
    data->unk14 = 0;
    omSetTra(obj, data->pos.x, data->pos.y, data->pos.z);
}

void func_80107EE0_dorrie_dip(omObjData *obj) {
    DorrieDipData *data = obj->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    DorrieDipDorrie *dorrie = D_8010A238_dorrie_dip->data;

    omSetTra(obj, data->pos.x, data->pos.y, data->pos.z);
    omSetRot(obj, 0.0f, data->unk10, 0.0f);
    Hu3DModelPosSet(obj->model[1], data->pos.x, data->unk1C, data->pos.z);
    if (data->unk14 & 4) {
        data->unk18 = 1.0f;
    } else {
        data->unk18 = (1440.0f - data->pos.y) / 1440.0f;
    }
    Hu3DModelScaleSet(obj->model[1], data->unk18, 1.0f, data->unk18);
    if (data->unk14 & 2) {
        data->pos.x = sindf(dips->unk18[D_8010A200_dorrie_dip]) * 450.0f;
        data->pos.y = 50.0f;
        data->pos.z = cosdf(dips->unk18[D_8010A200_dorrie_dip]) * 450.0f;
        data->unk10 = dips->unk18[D_8010A200_dorrie_dip];
    }
    if (data->unk14 & 1) {
        data->pos.y += data->unk0C;
        data->unk0C -= 3.0f;
        data->unk10 = dips->unk18[D_8010A200_dorrie_dip];
        if (data->pos.y <= 60.0f) {
            data->pos.y = 60.0f;
            data->unk14 &= ~1;
            data->unk14 |= 2;
        }
    }
    if (data->unk14 & 4) {
        data->pos.x = dorrie->hookPos.x;
        data->pos.y = dorrie->hookPos.y + 60.0f;
        data->pos.z = dorrie->hookPos.z;
        data->unk1C = dorrie->hookPos.y + 30.0f;
    }
}

void func_80108128_dorrie_dip(void) {
    DorrieDipData *data = D_8010A234_dorrie_dip->data;

    data->unk14 |= 1;
    data->unk0C = 0;
}

void func_80108148_dorrie_dip(void) {
    omAddPrcObj(func_80108174_dorrie_dip, 0x50, 0, 0);
}

void func_80108174_dorrie_dip(void) {
    func_80107D08_dorrie_dip();
    HuPrcSleep(30);
    func_80108128_dorrie_dip();
    omDelPrcObj(NULL);
}

void func_801081A8_dorrie_dip(void) {
    omAddPrcObj(func_801081D4_dorrie_dip, 0x50, 0, 0);
}

void func_801081D4_dorrie_dip(void) {
    DorrieDipData *data = D_8010A234_dorrie_dip->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    f32 radius;
    f32 velY;
    s32 landed;

    data->unk14 &= ~2;
    if (D_8010A220_dorrie_dip == D_8010A200_dorrie_dip) {
        while (data->unk10 != 0.0f) {
            data->unk10 += 9.0f;
            if (data->unk10 >= 360.0f) {
                data->unk10 = 0.0f;
            }
            HuPrcVSleep();
        }
        func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
        func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
        HuAudFXPlay(0x4E2);
        omDelPrcObj(NULL);
    }
    radius = 450.0f;
    velY = 90.0f;
    data->unk10 = dips->unk18[D_8010A200_dorrie_dip];
    func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
    landed = 0;
    while (radius < 1050.0f) {
        data->pos.x = radius * sindf(dips->unk18[D_8010A200_dorrie_dip]);
        data->pos.y = velY + data->pos.y;
        velY -= 10.0f;
        radius += 30.0f;
        if (data->pos.y < 80.0f) {
            data->pos.y = 80.0f;
            if (landed == 0) {
                landed = 1;
                func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[2]);
                func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
            }
        }
        data->pos.z = radius * cosdf(dips->unk18[D_8010A200_dorrie_dip]);
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80108458_dorrie_dip(void) {
    omAddPrcObj(func_80108484_dorrie_dip, 0x50, 0, 0);
}

void func_80108484_dorrie_dip(void) {
    DorrieDipData *data = D_8010A234_dorrie_dip->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    s32 i;
    f32 rotStep;

    for (i = 0; i < 6; i++) {
        dips->unk00[i] &= ~1;
        func_8001C258_main(D_8010A230_dorrie_dip->model[i + 6], 4, 4);
        if (i != D_8010A200_dorrie_dip) {
            func_80108EA0_dorrie_dip(i);
        }
    }
    func_8001C814_main(D_8010A224_dorrie_dip[0]->model[1], 1, 1);
    func_801096F0_dorrie_dip();
    data->unk14 &= ~2;
    rotStep = (data->unk10 >= 180.0) ? 9.0f : -9.0f;
    while (data->unk10 != 0.0f) {
        data->unk10 = rotStep + data->unk10;
        if (data->unk10 >= 360.0f) {
            data->unk10 = 0.0f;
        }
        if (data->unk10 < 0.0f) {
            data->unk10 = 0.0f;
        }
        HuPrcVSleep();
    }
    func_8001C5B4_main(D_8010A234_dorrie_dip->model[0], D_8010A234_dorrie_dip->motion[1]);
    func_8001C814_main(D_8010A234_dorrie_dip->model[0], 2, 2);
    omDelPrcObj(NULL);
}

void func_80108678_dorrie_dip(void) {
    omAddPrcObj(func_801086A4_dorrie_dip, 0x50, 0, 0);
}

void func_801086A4_dorrie_dip(void) {
    while (1) {
        if (D_800D5558_main[D_8010A1FC_dorrie_dip] & A_BUTTON) {
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80108700_dorrie_dip(void) {
    omAddPrcObj(func_8010872C_dorrie_dip, 0x50, 0, 0);
}

void func_8010872C_dorrie_dip(void) {
    s32 seconds = 10;
    s32 frames = 30;

    func_80037114_main(GMesCreate(26, 10, 160, 28), 160.0f, 28.0f);
    do {
        frames--;
        if (frames == 0) {
            frames = 30;
            seconds--;
        }
        func_8003F578_main(seconds);
        HuPrcVSleep();
        if (func_800E6E8C_minigame() == 3) {
            break;
        }
    } while (seconds > 0);
    if (D_8010A1F8_dorrie_dip == 0) {
        D_8010A1F8_dorrie_dip = 2;
        func_800E6F0C_minigame(3);
    }
    func_8003F5C0_main();
    omDelPrcObj(NULL);
}

void func_80108800_dorrie_dip(void) {
    omObjData *obj;
    DorrieDipBackground *data;

    obj = omAddObj(255, 4, 0, -1, func_8010898C_dorrie_dip);
    D_8010A224_dorrie_dip[0] = obj;
    data = HuMemAllocTag(sizeof(DorrieDipBackground), 0x7918);
    obj->data = data;
    obj->model[0] = func_8000B0A0_main(0x5F0000, 0x699);
    obj->model[1] = func_8000B0A0_main(0x5F0001, 0x699);
    obj->model[2] = func_8000B0A0_main(0x5F0003, 0x699);
    obj->model[3] = func_8000B0A0_main(0x5F0004, 0x699);
    D_8010A1F0_dorrie_dip = 1.0f;
    obj->trans.x = 0;
    obj->trans.y = 0;
    obj->trans.z = 0;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = obj;
    memset(obj->data, 0, sizeof(DorrieDipBackground));
    data->unk03 = 1;
    data->unk08 = 0.5f;
    data->unk04 = 0;
    func_800E1370_minigame(obj, 2, 133.0f);
    func_8001C814_main(obj->model[1], 8, 8);
    func_8001C814_main(obj->model[1], 2, 2);
    omSetTra(obj, 0.0f, 13.0f, 0.0f);
    D_8010A244_dorrie_dip = 0;
}

void func_8010898C_dorrie_dip(omObjData *obj) {
    D_8010A22C_dorrie_dip = sindf(D_8010A244_dorrie_dip) * 10.0f - 10.0f;
    D_8010A244_dorrie_dip += 5.0f;
    if (D_8010A244_dorrie_dip >= 360.0f) {
        D_8010A244_dorrie_dip -= 360.0f;
    }
    HmfModelData[obj->model[1]].pos.y = D_8010A22C_dorrie_dip;
    HmfModelData[obj->model[3]].pos.y = D_8010A22C_dorrie_dip + 5.0f;
}

void func_80108A74_dorrie_dip(s16 model, char *hook, s16 time, Vec *pos) {
    HuMtx4F transform;
    HuMtx4F result;
    HuMtx4F hookTransform;
    HmfModel *modelData;

    func_80016B00_main(model, time, hook, hookTransform);
    modelData = &HmfModelData[model];
    func_80088800_main(transform, modelData->pos.x, modelData->pos.y, modelData->pos.z);
    func_80017D24_main(transform, modelData->rot.x, modelData->rot.y, modelData->rot.z);
    func_80017CD0_main(transform, modelData->scale.x, modelData->scale.y, modelData->scale.z);
    func_80018044_main(hookTransform, transform, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

void func_80108B98_dorrie_dip(void) {
    s32 i;
    omObjData *obj;
    DorrieDipEffects *data;
    s32 flags = 0xA3D;

    obj = omAddObj(255, 6, 0, -1, func_80108C6C_dorrie_dip);
    D_8010A248_dorrie_dip = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipEffects), 0x7918);
    data = obj->data;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i] = func_8000B108_main(0x5D0008, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data->flags[i] = 0;
    }
}

void func_80108C6C_dorrie_dip(omObjData *obj) {
    s32 i;
    f32 x, z;
    DorrieDipEffects *data = obj->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;

    for (i = 0; i < 6; i++) {
        x = sindf(dips->unk18[i]) * 450.0f;
        z = cosdf(dips->unk18[i]) * 450.0f;
        data->posX[i] = x;
        data->posY[i] = 50.0f;
        data->posZ[i] = z;
        if (i == 0) {
            omSetTra(obj, data->posX[i], data->posY[i], data->posZ[i]);
            omSetRot(obj, CRot.x, 0.0f, 0.0f);
            omSetSca(obj, 1.5f, 1.5f, 1.5f);
        } else {
            Hu3DModelPosSet(obj->model[i], data->posX[i], data->posY[i], data->posZ[i]);
            Hu3DModelRotSet(obj->model[i], CRot.x, 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->model[i], 1.5f, 1.5f, 1.5f);
        }
        if ((data->flags[i] & 1) &&
            HmfModelData[obj->model[i]].unk40 >= D_800CCF58_main[HmfModelData[obj->model[i]].unk02].unk02) {
            func_8001C258_main(obj->model[i], 4, 4);
            data->flags[i] &= ~1;
        }
    }
}

void func_80108EA0_dorrie_dip(s32 dipIdx) {
    s32 i;
    s32 splashIdx;
    f32 x, z;
    DorrieDipEffects *effects = D_8010A248_dorrie_dip->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;
    DorrieDipSplashes *splashes = D_8010A23C_dorrie_dip->data;
    DorrieDipDorrie *dorrie = D_8010A238_dorrie_dip->data;

    func_8001C258_main(D_8010A230_dorrie_dip->model[dipIdx], 4, 4);
    func_8001C258_main(D_8010A230_dorrie_dip->model[dipIdx + 6], 4, 4);
    splashIdx = -1;
    for (i = 0; i < 5; i++) {
        if (splashes->playerIdx[i] == dipIdx) {
            splashIdx = i;
        }
    }
    if (splashIdx != -1) {
        if (dipIdx != D_8010A220_dorrie_dip) {
            func_8001C258_main(D_8010A23C_dorrie_dip->model[splashIdx], 4, 4);
        }
        func_8001C258_main(D_8010A23C_dorrie_dip->model[splashIdx + 5], 4, 4);
    }
    x = sindf(dips->unk18[dipIdx]) * 450.0f;
    z = cosdf(dips->unk18[dipIdx]) * 450.0f;
    effects->posX[dipIdx] = x;
    effects->posY[dipIdx] = 50.0f;
    effects->posZ[dipIdx] = z;
    if (dipIdx == D_8010A220_dorrie_dip) {
        effects->posX[dipIdx] = dorrie->hookPos.x;
        effects->posY[dipIdx] = dorrie->hookPos.y;
        effects->posZ[dipIdx] = dorrie->hookPos.z;
    }
    dips->unk00[dipIdx] &= ~1;
    effects->flags[dipIdx] |= 1;
    func_8001C258_main(D_8010A248_dorrie_dip->model[dipIdx], 4, 0);
    func_8001C814_main(D_8010A224_dorrie_dip[0]->model[1], 1, 1);
}

void func_801090C4_dorrie_dip(void) {
    omAddPrcObj(func_801090F0_dorrie_dip, 0x50, 0, 0);
}

void func_801090F0_dorrie_dip(void) {
    func_800E1BA8_minigame_ObjData *data = D_800EC598_minigame[0]->data;
    s32 i;

    func_800E5798_minigame(D_800EC598_minigame[0], 38);
    for (i = 0; i < 10; i++) {
        data->unk3C = i * 90.0f / 10.0f + 270.0f;
        HuPrcVSleep();
    }
    if (D_8010A220_dorrie_dip != -1 && D_8010A208_dorrie_dip[D_8010A220_dorrie_dip] != 17) {
        func_800E5798_minigame(D_800EC598_minigame[0], 13);
        func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[4]].unk02, 0, 10, 0);
        func_80045ED0_main(D_800A178C_main[GwPlayer[data->unk59].chr][0] | 0x35);
        for (i = 0; i < 60; i++) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x4E4);
    } else {
        func_800E5798_minigame(D_800EC598_minigame[0], 14);
        if (D_8010A220_dorrie_dip == -1) {
            func_8001C624_main(D_8010A238_dorrie_dip->model[0], HmfModelData[D_8010A238_dorrie_dip->motion[3]].unk02, 0, 10, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801092E0_dorrie_dip(void) {
    omAddPrcObj(func_8010930C_dorrie_dip, 0x50, 0, 0);
}

void func_8010930C_dorrie_dip(void) {
    s32 i;
    s32 splashIdx;
    f32 deltaX, deltaZ, startY, angle;
    DorrieDipSplashes *splashes;
    DorrieDipDorrie *dorrie;

    HuAudFXPlay(25);
    splashes = D_8010A23C_dorrie_dip->data;
    dorrie = D_8010A238_dorrie_dip->data;
    D_8010A1FA_dorrie_dip = func_8000CED8_main(0xB0004, 0x6A9);
    splashIdx = -1;
    for (i = 0; i < 5; i++) {
        if (splashes->playerIdx[i] == D_8010A220_dorrie_dip) {
            splashIdx = i;
        }
    }
    if (splashIdx == -1) {
        osSyncPrintf("!!\n");
    }
    splashes->flags[splashIdx] &= ~4;
    splashes->flags[splashIdx] &= ~1;
    splashes->flags[splashIdx] |= 8;
    deltaX = D_800EC598_minigame[0]->trans.x - dorrie->hookPos.x;
    deltaZ = D_800EC598_minigame[0]->trans.z - dorrie->hookPos.z;
    startY = splashes->posY[splashIdx];
    for (i = 0; i < 30; i++) {
        splashes->posX[splashIdx] = deltaX / 30.0f + splashes->posX[splashIdx];
        angle = i * 180.0f / 30.0f;
        splashes->unk8C[splashIdx] = sindf(angle) * 400.0f + startY;
        if (angle > 90.0f) {
            if (splashes->unk8C[splashIdx] < D_800EC598_minigame[0]->trans.y + 300.0f) {
                splashes->unk8C[splashIdx] = D_800EC598_minigame[0]->trans.y + 300.0f;
            }
        }
        splashes->posZ[splashIdx] = deltaZ / 30.0f + splashes->posZ[splashIdx];
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80109520_dorrie_dip(void) {
    s32 i;
    omObjData *obj;
    s32 *data;
    s32 flags = 0x69D;

    obj = omAddObj(255, 9, 0, -1, func_801095FC_dorrie_dip);
    D_8010A24C_dorrie_dip = obj;
    obj->data = HuMemAllocTag(9 * sizeof(s32), 0x7918);
    data = obj->data;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            obj->model[i] = func_8000B108_main(0x5F000C, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data[i] = 0;
    }
    D_8010A250_dorrie_dip = 0;
}

void func_801095FC_dorrie_dip(omObjData *obj) {
    s32 i;
    s32 *data = obj->data;

    for (i = 0; i < 9; i++) {
        if ((data[i] & 1) && HmfModelData[obj->model[i]].unk40 >= D_800CCF58_main[HmfModelData[obj->model[i]].unk02].unk02) {
            func_8001C258_main(obj->model[i], 4, 4);
            data[i] &= ~1;
        }
    }
}

void func_801096F0_dorrie_dip(void) {
    omAddPrcObj(func_80109738_dorrie_dip, 0x50, 0, 0);
}

void func_8010971C_dorrie_dip(void) {
    D_8010A250_dorrie_dip &= ~2;
}

void func_80109738_dorrie_dip(void) {
    s32 *data = D_8010A24C_dorrie_dip->data;
    s32 i;
    s32 effectIdx;
    s32 angle;
    s32 radius;
    f32 x, z;

    D_8010A250_dorrie_dip |= 2;
    while (D_8010A250_dorrie_dip & 2) {
        if (rand8() % 16 == 0) {
            effectIdx = -1;
            for (i = 0; i < 9; i++) {
                if (!(data[i] & 1)) {
                    effectIdx = i;
                    break;
                }
            }
            if (effectIdx != -1) {
                data[effectIdx] |= 1;
                angle = (rand8() * 2) % 360;
                radius = (rand8() * 2) % 500;
                x = radius * sindf(angle);
                z = radius * cosdf(angle);
                if (effectIdx == 0) {
                    omSetTra(D_8010A24C_dorrie_dip, x, 0.0f, z);
                } else {
                    Hu3DModelPosSet(D_8010A24C_dorrie_dip->model[effectIdx], x, 0.0f, z);
                }
                func_8001C258_main(D_8010A24C_dorrie_dip->model[effectIdx], 4, 0);
                func_8001C6A8_main(D_8010A24C_dorrie_dip->model[effectIdx], 0.0f);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80109978_dorrie_dip(void) {
    s32 i;
    s32 total;
    s32 targetDip;
    s32 chance;

    chance = (u8)(rand8() % 100);
    for (i = 0, total = 0; i < 5; i++) {
        if (chance >= total && chance < total + D_800A11DC_main[i]) {
            break;
        }
        total += D_800A11DC_main[i];
    }
    if (i == 5) {
        i = 4;
    }
    targetDip = 0;
    for (total = 0; total < 6; total++) {
        if (D_8010A208_dorrie_dip[total] == i) {
            targetDip = total;
        }
    }
    chance = (u8)(rand8() % 100);
    switch (GwPlayer[D_8010A1FC_dorrie_dip].cpu_difficulty) {
        case 0:
            if (chance < 20) {
                targetDip = D_8010A200_dorrie_dip;
            }
            break;
        case 1:
            if (chance < 15) {
                targetDip = D_8010A200_dorrie_dip;
            }
            break;
        case 2:
            if (chance < 10) {
                targetDip = D_8010A200_dorrie_dip;
            }
            break;
        case 3:
            if (chance < 5) {
                targetDip = D_8010A200_dorrie_dip;
            }
            break;
    }
    D_8010A254_dorrie_dip.grabDelay = 8;
    D_8010A254_dorrie_dip.targetDip = targetDip;
    D_8010A254_dorrie_dip.triggered = 0;
}

void func_80109B28_dorrie_dip(void) {
    s32 i;
    omObjData *obj;
    DorrieDipWakes *data;
    s32 flags = 0x6BD;

    obj = omAddObj(255, 6, 0, -1, func_80109C14_dorrie_dip);
    D_8010A260_dorrie_dip = obj;
    obj->data = HuMemAllocTag(sizeof(DorrieDipWakes), 0x7918);
    data = obj->data;
    for (i = 0; i < 6; i++) {
        if (i == 0) {
            obj->model[i] = func_8000B108_main(0x5F000D, flags);
        } else {
            obj->model[i] = Hu3DModelLink(obj->model[0]);
        }
        data->flags[i] = 0;
        data->scaleX[i] = 1.0f;
    }
}

void func_80109C14_dorrie_dip(omObjData *obj) {
    s32 i;
    DorrieDipWakes *data = obj->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;

    for (i = 0; i < 6; i++) {
        if (i == 0) {
            omSetTra(obj, data->posX[i], data->posY[i], data->posZ[i]);
            omSetRot(obj, 0.0f, dips->unk18[i], 0.0f);
            omSetSca(obj, data->scaleX[i], 1.0f, 1.0f);
        } else {
            Hu3DModelPosSet(obj->model[i], data->posX[i], data->posY[i], data->posZ[i]);
            Hu3DModelRotSet(obj->model[i], 0.0f, dips->unk18[i], 0.0f);
            Hu3DModelScaleSet(obj->model[i], data->scaleX[i], 1.0f, 1.0f);
        }
        if (data->flags[i] & 1) {
            data->scaleX[i] = (4.8f - dips->unk30[i]) / 4.8f;
            if (data->scaleX[i] == 0.0f) {
                func_8001C258_main(obj->model[i], 4, 4);
                data->flags[i] &= ~1;
            }
        }
        data->posX[i] = sindf(dips->unk18[i]) * 450.0f;
        data->posY[i] = D_8010A22C_dorrie_dip;
        data->posZ[i] = cosdf(dips->unk18[i]) * 450.0f;
    }
}

void func_80109E1C_dorrie_dip(s32 dipIdx) {
    DorrieDipWakes *data = D_8010A260_dorrie_dip->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;

    data->flags[dipIdx] |= 1;
    data->posX[dipIdx] = sindf(dips->unk18[dipIdx]) * 450.0f;
    data->posY[dipIdx] = D_8010A22C_dorrie_dip;
    data->posZ[dipIdx] = cosdf(dips->unk18[dipIdx]) * 450.0f;
    func_8001C258_main(D_8010A260_dorrie_dip->model[dipIdx], 4, 0);
    func_8001C814_main(D_8010A260_dorrie_dip->model[dipIdx], 2, 2);
}

void func_80109F00_dorrie_dip(void) {
    func_800E1BA8_minigame_ObjData *data = D_800EC598_minigame[0]->data;
    DorrieDipDips *dips = D_8010A230_dorrie_dip->data;

    if (D_8010A254_dorrie_dip.triggered == 0) {
        if (dips->unk18[D_8010A254_dorrie_dip.targetDip] >= 175.0f &&
            dips->unk18[D_8010A254_dorrie_dip.targetDip] < 185.0f) {
            D_800CDA7C_main[data->unk57] |= A_BUTTON;
            D_800D5558_main[data->unk57] |= A_BUTTON;
            D_8010A254_dorrie_dip.triggered++;
        }
    }
    if (D_8010A254_dorrie_dip.triggered != 0) {
        if (--D_8010A254_dorrie_dip.grabDelay == 0) {
            D_800CDA7C_main[data->unk57] |= Z_TRIG;
            D_800D5558_main[data->unk57] |= Z_TRIG;
        }
    }
}
