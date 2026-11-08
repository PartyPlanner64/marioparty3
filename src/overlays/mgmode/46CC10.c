#include "common.h"
#include "overlays/mgmode.h"

extern u8 D_80118EB1_mgmode;
extern u8 D_80118EB2_mgmode;
extern s16 D_80118EB4_mgmode;
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;
extern s16 D_8011B884_mgmode;
extern Gfx D_80119290_mgmode[];
extern s16 D_8011B3E4_mgmode;
extern MgmodeEsprite *D_8011B3EC_mgmode;
extern s16 D_8011B8B2_mgmode;
extern u16 *D_8011B3E0_mgmode;
extern s8 D_8011B3E6_mgmode[];
extern s32 D_80119190_mgmode[];
extern s32 D_801191E4_mgmode[];
extern char D_8011A400_mgmode[];
extern char D_8011A430_mgmode[];
extern char D_8011A708_mgmode[];
extern s16 D_8011B6A0_mgmode;
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B77A_mgmode;
extern s16 D_8011B80A_mgmode;
extern u8 D_8011A8C8_mgmode[][20];
extern u8 D_8011A968_mgmode[];
extern u8 D_8011A970_mgmode[][20];
extern u8 D_8011AA10_mgmode[];
extern u8 D_8011B6B0_mgmode[][25];
extern s16 D_8011B6A8_mgmode;
extern u8 D_800D20B0_main;
extern MgmodeSpaceCoord D_80119158_mgmode[];
extern Vec D_8011AA80_mgmode[][25];
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8C4_mgmode;
extern MgmodeSpaceCoord D_80119170_mgmode[];
extern s16 D_8011B808_mgmode;
extern s16 D_8011B8B4_mgmode;
extern HuMtx4F D_8011A808_mgmode;
extern char D_8011A46C_mgmode[];
extern char D_8011A404_mgmode[];
extern char D_8011A40C_mgmode[];
extern HuMtx4F D_8011A848_mgmode;
extern HuMtx4F D_8011A888_mgmode;
extern s16 D_8011B8A8_mgmode[];
extern char *D_801192D8_mgmode[];
extern u8 D_801192F4_mgmode[];
extern u8 D_800D1FF0_main;
extern s8 D_801192FC_mgmode[];
extern s8 D_80119310_mgmode[];
extern u16 D_80119320_mgmode[];
extern u16 D_8011932C_mgmode[];
extern MgmodeEspriteDef D_8011988C_mgmode[];
extern u8 D_800CB8B1_main[];
extern f32 D_8011B6A4_mgmode;
extern f32 D_8011B804_mgmode;
extern f32 D_8011B888_mgmode;
extern Vec D_8011B898_mgmode;
extern Vec D_8011B88C_mgmode;
extern f32 D_8011B938_mgmode;
extern u8 D_8011B778_mgmode;
extern u8 D_8011B8A4_mgmode;
extern s16 D_8011B800_mgmode;
extern u8 D_800CD280_main;
extern u8 D_800D6A58_main;
extern u16 D_800CE2A0_main[];
extern u8 D_800CE20A_main;
extern s16 D_800D0468_main;
extern s16 D_800D1FE0_main;
extern s16 D_800CB894_main;
extern u16 D_800CC698_main;
extern u8 D_80118EB0_mgmode;
extern u8 D_8011B958_mgmode;
extern MgmodeSpaceCoord D_8011AA18_mgmode[];
extern u16 D_80119200_mgmode[];
extern s8 D_800D2124_main[];

void func_8010BD98_mgmode(omObjData *arg0);
void func_80108DDC_mgmode(s16 arg0);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116D4C_mgmode(void);
void func_80118CD8_mgmode(void);
void func_801090C4_mgmode(s16 arg0);
void func_80107D0C_mgmode(s32 dataNum, s16 x, s16 y);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
s16 func_801182DC_mgmode(s16 stickX, s16 stickY);
void func_80118D0C_mgmode(void);
MgmodeEsprite *func_80116794_mgmode(MgmodeEspriteDef *defs);
void func_8010A62C_mgmode(s32 arg0, s32 arg1);
void func_8010A824_mgmode(s32 arg0, s32 arg1);
void func_8010606C_mgmode(void);
void func_8010A8E4_mgmode(s32 arg0);
void func_8010AF78_mgmode(Gfx **arg0, s32 arg1, s32 arg2);
void func_8010AFEC_mgmode(void);
void func_8010BD28_mgmode(omObjData *arg0);
void func_8010BEC0_mgmode(void);
void func_80112200_mgmode(void);
s32 func_80111B08_mgmode(void);
void func_80117DD0_mgmode(void);
void func_80116E24_mgmode(s16 arg0);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_801182C0_mgmode(s16 index);
void func_80109C10_mgmode(s16 arg0, s16 arg1);
void func_80109DBC_mgmode(s16 arg0, s16 arg1);
s16 func_8010A148_mgmode(s16 arg0);
void func_8010A5F0_mgmode(void);

void func_801059A0_mgmode(void) {
    HmfModel *model;
    s16 i;

    omInitObjMan(20, 10);
    Hu3DCamInit(2);
    HuWinInit();
    func_800142A0_main(20);
    Hu3DBGColorSet(0, 0, 0);
    D_800CD280_main = 1;
    D_800D6A58_main = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    ScissorSet(1, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    D_8011B898_mgmode.z = 90.0f; // CRot.z is left as-is and copied over this below
    CZoom = 660.0f;
    Center.x = 0.0f;
    Center.y = 181.0f;
    Center.z = -395.0f;
    D_8011B6A4_mgmode = 40.0f;
    D_8011B898_mgmode = CRot;
    D_8011B938_mgmode = CZoom;
    D_8011B88C_mgmode = Center;
    D_8011B804_mgmode = 80.0f;
    D_8011B888_mgmode = 1800.0f;
    Hu3DCameraPerspectiveSet(0, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
    Hu3DCameraPerspectiveSet(1, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
    HmfLightMaxSet(4);
    HmfLightColorSet(1, 64, 64, 64);
    HmfLightDirSet(1, 0.0f, 119.0f, 0.0f);
    HmfLightStatSet(0, 1, 1);
    HmfLightColorSet(2, 150, 150, 110);
    HmfLightDirSet(2, 40.0f, 42.0f, 104.0f);
    HmfLightColorSet(3, 0, 0, 0);
    omAddObj(10000, 0, 0, -1, func_8010BD28_mgmode);
    omPrcSetStatBit(omAddPrcObj(func_8010AFEC_mgmode, 0x1100, 0x1000, 0), 0xA0);
    omAddPrcObj(func_80117DD0_mgmode, 0x3F00, 0x800, 0);
    func_8010A8E4_mgmode(0);

    if (omovlevtno == 0 || omovlevtno == 1 || omovlevtno == 6 || omovlevtno == 7) {
        omAddPrcObj(func_8010606C_mgmode, 0x3FF6, 0x2000, 0);
        HuAudSeqPlay(8);
    } else if (omovlevtno == 2 || omovlevtno == 4) {
        func_8010A8E4_mgmode(1);
        HmfLightColorSet(3, 130, 130, 50);
        HmfLightDirSet(3, -17.0f, -101.0f, -61.0f);
        omAddPrcObj(func_8010BEC0_mgmode, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 4) {
            if (func_80111B08_mgmode() == 0) {
                HuAudSeqPlay(76);
            } else {
                HuAudSeqPlay(22);
            }
        } else {
            HuAudSeqPlay(76);
        }
    } else if (omovlevtno == 3 || omovlevtno == 5) {
        omAddPrcObj(func_80112200_mgmode, 0x3FF6, 0x2000, 0);
        if (omovlevtno == 5 && D_800D1FE0_main + D_800CB894_main * GwPlayer[0].bonusCoin >= 1000) {
            HuAudSeqPlay(70);
        } else {
            HuAudSeqPlay(77);
        }
    }

    if (omovlevtno != 0) {
        for (i = 0; i < 10; i++) {
            if (D_800CE2A0_main[i] != GwCommon.mgRecord[i]) {
                break;
            }
        }
        if (i != 10) {
            func_80118CD8_mgmode();
        }
    }
    for (i = 0; i < 10; i++) {
        D_800CE2A0_main[i] = GwCommon.mgRecord[i];
    }
    D_8011B808_mgmode = 0;
    D_8011B800_mgmode = 0;
    _ClearFlag(13);
    _SetFlag(28);
    D_800CE20A_main = 0;
    model = &HmfModelData[D_800D0468_main];
    model->unk00 = (model->unk00 & 0xF9) | 3;
    Hu3DModelCameraSet(D_800D0468_main, 1);
    D_8011B8A4_mgmode = 0;
    D_8011B778_mgmode = 0;
    for (i = 0; i < 6; i++) {
        if (D_8011B928_mgmode[i] >= 3) {
            D_8011B778_mgmode = 1;
            break;
        }
    }
    if (_CheckFlag(29)) {
        D_8011B8A4_mgmode = 1;
    }
    D_8011B884_mgmode = 0;
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_8010AF78_mgmode, 0), 2);
    for (i = 0; i < 4; i++) {
        D_800CB8B1_main[i] = 0;
    }
    D_800CC698_main = 0;
    for (i = 0; i < 4; i++) {
        GwPlayer[i].star = 0;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A400_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A404_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010606C_mgmode);

s16 func_80107298_mgmode(void) {
    s16 count = 0;
    s16 win;
    s16 total;
    s16 remaining;
    s16 size[2];

    if (_CheckFlag(0x1E) && !_CheckFlag(0x2A)) {
        count = 1;
        _SetFlag(0x2A);
    }
    if (D_8011B928_mgmode[0] >= 20 && D_8011B928_mgmode[1] >= 10 && D_8011B928_mgmode[2] >= 10 &&
        D_8011B928_mgmode[3] >= 8 && D_8011B928_mgmode[4] >= 10 && D_8011B928_mgmode[5] >= 6 && !_CheckFlag(0x2B)) {
        count++;
        _SetFlag(0x2B);
    }
    if (_CheckFlag(0x1F) && !_CheckFlag(0x2C)) {
        count++;
        _SetFlag(0x2C);
    }
    if (count == 0) {
        return 0;
    }
    HuWinInsertMesSizeGet((u32)D_8011A400_mgmode, 0);
    HuWinInsertMesSizeGet((u32)D_8011A400_mgmode, 1);
    HuWinMesMaxSizeBetGet(size, 0x570D, 0x5710);
    win = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(win, 1 << D_8011B808_mgmode);
    HuWinMesSet(win, 0x570D, -1, -1);
    HuWinExAnimIn(win);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    if (count == 3) {
        HuWinMesSet(win, 0x570F, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, count);
        HuWinInsertMesSet(win, (u32)D_8011A708_mgmode, 0);
        HuWinMesSet(win, 0x570E, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    remaining = 67 - total;
    if (remaining == 0) {
        HuWinMesSet(win, 0x5711, -1, -1);
    } else {
        sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
        HuWinInsertMesSet(win, (u32)D_8011A708_mgmode, 0);
        HuWinMesSet(win, 0x5710, -1, -1);
    }
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinExAnimOut(win, 0);
    HuWinKill(win);
    func_80118CD8_mgmode();
    return count;
}

void func_80107610_mgmode(void) {
    s32 angle = 0;

    Hu3DModelScaleSet(D_8011B8B2_mgmode, 0.5f, 0.5f, 0.5f);
    while (TRUE) {
        HuPrcVSleep();
        HmfModelData[D_8011B8B2_mgmode].pos.y = sindf(angle) * 20.0f;
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A430_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A434_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A43C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A444_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A44C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A454_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A45C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A464_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A46C_mgmode);

void func_801076B0_mgmode(void) {
    s16 order[20];
    Vec tmpPos;
    HmfData *hmf;
    HmfVertexGroup *group;
    Vtx *verts;
    s16 model;
    s16 node;
    s16 count;
    s16 i;
    s16 j;
    s16 k;
    s16 b;
    s16 tmp;
    f32 x;
    f32 y;
    f32 z;
    void *data;

    func_8002367C_main(D_8011A808_mgmode,
                       ((HmfMotionNode *)func_8001D33C_main(D_8011B8A8_mgmode[6], D_8011A46C_mgmode))->unk58);
    func_8002367C_main(D_8011A848_mgmode,
                       ((HmfMotionNode *)func_8001D33C_main(D_8011B8A8_mgmode[3], D_8011A404_mgmode))->unk58);
    func_8002367C_main(D_8011A888_mgmode,
                       ((HmfMotionNode *)func_8001D33C_main(D_8011B8A8_mgmode[3], D_8011A40C_mgmode))->unk58);
    model = D_8011B8A8_mgmode[2];
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    hmf = HmfModelData[model].hmf;
    for (i = 0; i < 7; i++) {
        node = func_8002C834_main(hmf, D_801192D8_mgmode[i]);
        group = &hmf->unkB0[hmf->unk60[node].unk2C];
        verts = hmf->unk40;
        count = hmf->unk60[node].unk2E;
        for (j = 0; j < count; j++, group++) {
            x = y = z = 0.0f;
            for (k = 0; k < group->count; k++) {
                x += verts[group->indices[k]].v.ob[0];
                y += verts[group->indices[k]].v.ob[1];
                z += verts[group->indices[k]].v.ob[2];
            }
            D_8011AA80_mgmode[i][j].x = x / group->count;
            D_8011AA80_mgmode[i][j].y = y / group->count;
            D_8011AA80_mgmode[i][j].z = z / group->count;
            order[j] = j;
        }
        for (k = count - 1; k >= 0; k--) {
            for (b = 0; b < k; b++) {
                if (D_8011AA80_mgmode[i][b].x > D_8011AA80_mgmode[i][b + 1].x) {
                    tmpPos = D_8011AA80_mgmode[i][b];
                    D_8011AA80_mgmode[i][b] = D_8011AA80_mgmode[i][b + 1];
                    D_8011AA80_mgmode[i][b + 1] = tmpPos;
                    tmp = order[b];
                    order[b] = order[b + 1];
                    order[b + 1] = tmp;
                }
            }
        }
        for (j = 0; j < count; j++) {
            group = &hmf->unkB0[hmf->unk60[node].unk2C + order[j]];
            for (b = 0; b < D_800D1FF0_main; b++) {
                verts = hmf->unk44[b];
                for (k = 0; k < group->count; k++) {
                    if (D_8011B6B0_mgmode[D_801191E4_mgmode[i]][j] != 0xFF) {
                        if (i == 6 && j == 0) {
                            verts[group->indices[k]].v.tc[0] += 0x1000;
                        } else {
                            verts[group->indices[k]].v.tc[0] += D_801192F4_mgmode[i] << 9;
                        }
                    } else {
                        verts[group->indices[k]].v.tc[0] += 0xE00;
                    }
                }
            }
        }
    }
    model = D_8011B8A8_mgmode[15];
    data = DataRead(0xA002A);
    HmfAnimCreate(HmfModelData[model].hmf, data, 0, "c160n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(model);
    func_8001C514_main(model);
}

void func_80107D0C_mgmode(s32 dataNum, s16 x, s16 y) {
    s16 wins[10];
    u8 buf[32];
    u8 buf2[32];
    u8 buf3[32];
    u8 games[10] = { 0, 1, 2, 4, 3, 5, 6, 7, 9, 8 };
    s8 unlockIds[10] = { 13, 16, 35, 52, 44, 71, 71, 71, 0, -1 };
    s32 names[10] = { 0x4501, 0x4502, 0x4503, 0x4504, 0x4505, 0x4506, 0x4507, 0x4508, 0x4509, 0x450A };
    s16 anim;
    s16 sprite;
    s16 win;
    s16 i;
    s16 j;
    s16 rec;
    f32 scale;

    HuPrcSleep(3);
    anim = func_8000B838_main(dataNum);
    sprite = espEntry(anim, 0, 1);
    espPosSet(sprite, x, y);
    espPriSet(sprite, 0x8000);
    espScaleSet(sprite, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        wins[i] = HuWinExCreate(-1, x - 104, y - 71 + i * 14, 213, 20, 0);
        HuWinBGTPLvlSet(wins[i], 0);
    }
    win = HuWinExCreate(-1, 0, 0, 210, 14, 1);
    HuWinBGColSet(win, 255, 255, 255);
    HuAudFXPlay(0x2E7);
    for (i = 1; i < 11; i++) {
        scale = cosdf(i * 36.0f) * 0.5f + 0.5f;
        espScaleSet(sprite, scale, sindf(i * 9.0f));
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        rec = GWMgRecordGet(games[i]);
        if (rec < 0) {
            rec = 0;
        }
        switch (games[i]) {
            case 0:
                sprintf((char *)buf, "%3d", rec);
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
                sprintf((char *)buf, D_8011A430_mgmode, (s16)(rec / 3600));
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                rec %= 3600;
                sprintf((char *)buf2, "%2d", (s16)(rec / 60));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                sprintf((char *)buf3, "%2d", (s16)((s16)(rec % 60) / 60.0f * 100.0f));
                if (buf3[0] == ' ') {
                    buf3[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf3, 2);
                break;
            case 4:
                sprintf((char *)buf, "%3d", (s16)(rec / 100));
                rec %= 100;
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                sprintf((char *)buf2, "%2d", rec);
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                break;
            case 3:
            case 9:
                sprintf((char *)buf, D_8011A430_mgmode, (s16)(rec / 1800));
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                rec %= 1800;
                sprintf((char *)buf2, "%2d", (s16)(rec / 30));
                if (buf2[0] == ' ') {
                    buf2[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf2, 1);
                sprintf((char *)buf3, "%2d", (s16)((s16)(rec % 30) * (1.0f / 30.0f) * 99.0f));
                if (buf3[0] == ' ') {
                    buf3[0] = '0';
                }
                HuWinInsertMesSet(wins[i], (u32)buf3, 2);
                break;
            case 8:
                sprintf((char *)buf, "%4d", rec);
                HuWinInsertMesSet(wins[i], (u32)buf, 0);
                break;
        }
        HuWinDispOn(wins[i]);
        rec = unlockIds[i] - 1;
        if (rec == 70 && _CheckFlag(0x2B)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec >= 0 && GWMgUnlockCheck(rec)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec == -1 && _CheckFlag(0x1E)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else if (rec == -2 && _CheckFlag(0x1F)) {
            HuWinMesSet(wins[i], names[i], -1, -1);
        } else {
            HuWinMesSet(wins[i], 0x4500, -1, -1);
        }
        HuWinPosSet(win, x, y - 62 + i * 14);
        HuWinDispOn(win);
        HuAudFXPlay(0x2E8);
        for (j = 1; j < 4; j++) {
            HuWinBGTPLvlSet(win, (1.0f - j / 3.0f) * 256.0f);
            HuPrcVSleep();
        }
    }
    HuWinKill(win);
    do {
        HuPrcVSleep();
    } while (!(D_800D5558_main[0] & (A_BUTTON | B_BUTTON)));
    for (i = 0; i < 10; i++) {
        HuWinDispOff(wins[i]);
    }
    HuAudFXPlay(0x2E9);
    for (i = 1; i < 11; i++) {
        scale = 1.0f - sindf(i * 9.0f);
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    for (i = 0; i < 10; i++) {
        HuWinKill(wins[i]);
    }
    espKill(sprite);
    HuSprAnimKill(anim);
}

void func_80108824_mgmode(s32 arg0) {
    s16 total;
    s16 choice;
    s16 i;
    HmfMotionNode *node;

    total = D_8011B928_mgmode[0] + D_8011B928_mgmode[1] + D_8011B928_mgmode[2] + D_8011B928_mgmode[3] +
            D_8011B928_mgmode[4] + D_8011B928_mgmode[5] + D_8011B928_mgmode[7];
    if (total < 0) {
        total = 0;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, total);
    HuWinInsertMesSet(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    if (arg0 == 0) {
        HuWinMesSet(D_8011B6A0_mgmode, 0x570B, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
        HuWinMesSet(D_8011B6A0_mgmode, 0x5712, -1, -1);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
    } else {
        HuWinMesSet(D_8011B6A0_mgmode, 0x5712, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
    }
    choice = HuWinChoiceGet(D_8011B6A0_mgmode, 0, 0);
    HuWinExAnimOut(D_8011B6A0_mgmode, 0);
    if (choice == -1) {
        HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
        HuWinExAnimIn(D_8011B6A8_mgmode);
        func_801182B4_mgmode(1);
        return;
    }
    if (choice == 0) {
        func_801182B4_mgmode(0);
        func_80116ED4_mgmode(2, 10, 1, (void (*)(s16 *))-1);
        HuWinMesSet(D_8011B6A0_mgmode, 0x5713, -1, -1);
        HuWinExAnimIn(D_8011B6A0_mgmode);
        while (HuWinStatGet(D_8011B6A0_mgmode) != 0) {
            HuPrcVSleep();
        }
        func_80108DDC_mgmode(0);
    } else if (choice == 1) {
        func_801182B4_mgmode(0);
        node = func_8001D33C_main(D_8011B8B4_mgmode, D_8011A46C_mgmode);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(node->unk58, D_8011A808_mgmode);
            func_80017D24_main(node->unk58, 0.0f, sindf(i * 9) * 117.0f, 0.0f);
        }
        func_80116ED4_mgmode(6, 10, 1, (void (*)(s16 *))-1);
        func_80107D0C_mgmode(0x12000F, 160, 120);
        func_80116ED4_mgmode(1, 10, 1, (void (*)(s16 *))-1);
        HuAudFXPlay(0x245);
        for (i = 0; i < 11; i++) {
            HuPrcVSleep();
            func_8002367C_main(node->unk58, D_8011A808_mgmode);
            func_80017D24_main(node->unk58, 0.0f, (1.0f - sindf(i * 9)) * 117.0f, 0.0f);
        }
    }
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
}

void func_80108C88_mgmode(void) {
    HuWinDispOn(D_8011B6A0_mgmode);
    func_80108DDC_mgmode(D_800D20B0_main);
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
}

void func_80108CF4_mgmode(s16 arg0) {
    s32 mesOffset;

    mesOffset = (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) ? 7 : 0;
    if (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] == D_8011B940_mgmode[D_801191E4_mgmode[arg0]]) {
        mesOffset = 14;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, D_8011B928_mgmode[D_801191E4_mgmode[arg0]]);
    HuWinInsertMesSet(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    HuWinMesSet(D_8011B6A0_mgmode, D_80119190_mgmode[mesOffset + arg0], -1, -1);
}

void func_80108DDC_mgmode(s16 arg0) {
    s16 next;

    func_80108CF4_mgmode(arg0);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8011822C_mgmode(D_80119170_mgmode);
    func_801181F4_mgmode(arg0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    HuPrcSleep(5);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            HuPrcSleep(5);
            func_80108CF4_mgmode(next);
            arg0 = next;
        } else if ((D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) && D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) {
            HuAudFXPlay(2);
            func_801182B4_mgmode(0);
            HuWinExAnimOut(D_8011B6A0_mgmode, 0);
            func_80116ED4_mgmode(arg0 + 7, 15, 1, (void (*)(s16 *))-1);
            func_801090C4_mgmode(arg0);
            func_80116ED4_mgmode(2, 15, 1, (void (*)(s16 *))-1);
            func_8011822C_mgmode(D_80119170_mgmode);
            func_801181F4_mgmode(arg0);
            func_8011829C_mgmode(5);
            func_801182B4_mgmode(1);
            func_80108CF4_mgmode(arg0);
            HuWinExAnimIn(D_8011B6A0_mgmode);
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            func_801182B4_mgmode(0);
            HuWinExAnimOut(D_8011B6A0_mgmode, 0);
            func_80116ED4_mgmode(1, 10, 1, (void (*)(s16 *))-1);
            return;
        }
    }
}

void func_801090C4_mgmode(s16 arg0) {
    Vec pos;
    Vec2f screen;
    s16 category;
    s16 count;
    s16 i;
    s16 sel;
    s16 next;
    s16 ok;
    s16 win;
    s16 spriteGrp;
    s16 icon;
    s16 badge;

    category = D_801191E4_mgmode[arg0];
    count = D_8011B940_mgmode[category];
    for (i = 0; i < count; i++) {
        pos = D_8011AA80_mgmode[arg0][i];
        Hu3D3Dto2D(0, &pos, &screen);
        D_8011AA18_mgmode[i].x = screen.x;
        D_8011AA18_mgmode[i].y = screen.y;
    }
    D_8011AA18_mgmode[i].x = -1;
    D_8011AA18_mgmode[i].y = -1;
    win = HuWinExCreate(-1, 24, 16, 272, 80, 0);
    HuWinActivePlayerSet(win, 1 << D_8011B808_mgmode);
    icon = func_80116B20_mgmode();
    espAttrSet(icon, 8);
    espPosSet(icon, 76, 56);
    espScaleSet(icon, 0.75f, 0.75f);
    spriteGrp = func_8000B838_main(0x120013);
    badge = espEntry(spriteGrp, 0, 1);
    espPriSet(badge, 1);
    espDispOff(badge);
    espPosSet(badge, 76, 84);
    func_8011822C_mgmode(D_8011AA18_mgmode);
    sel = D_800D2124_main[arg0];
    for (i = 0; i < count; i++) {
        if (D_8011B6B0_mgmode[category][i] == 0xFF || D_8011B6B0_mgmode[category][i] >= 72) {
            func_801182C0_mgmode(i);
        } else if (sel == -1) {
            sel = D_800D2124_main[arg0] = i;
        }
    }
    func_801181F4_mgmode(sel);
    func_801182B4_mgmode(1);
    func_8011829C_mgmode(3);
    if (D_8011B6B0_mgmode[category][sel] != 0xFF && D_8011B6B0_mgmode[category][sel] < 72) {
        func_80109C10_mgmode(arg0, sel);
    }
    HuWinInsertMesSet(win, D_8011B6B0_mgmode[category][sel] + 0x4700, 0);
    HuWinMesSet(win, D_80119200_mgmode[D_8011B6B0_mgmode[category][sel]], -1, -1);
    HuWinExAnimIn(win);
    if (D_8011B6B0_mgmode[category][sel] != 0xFF && D_8011B6B0_mgmode[category][sel] < 72) {
        espDispOn(icon);
        if (D_800A6D40_main[D_8011B6B0_mgmode[category][sel]].flags >> 15) {
            espDispOn(badge);
        } else {
            espDispOff(badge);
        }
        func_80116C18_mgmode(D_800A6D40_main[D_8011B6B0_mgmode[category][sel]].flags & 0x7FF);
    } else {
        espDispOff(icon);
    }
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            sel = next;
            D_800D2124_main[arg0] = sel;
            for (i = 0; i < 8; i++) {
                func_8001C258_main(D_8011B8B6_mgmode[i], 4, 4);
            }
            if (D_8011B6B0_mgmode[category][sel] != 0xFF && D_8011B6B0_mgmode[category][sel] < 72) {
                func_80109C10_mgmode(arg0, sel);
                espDispOn(icon);
                if (D_800A6D40_main[D_8011B6B0_mgmode[category][sel]].flags >> 15) {
                    espDispOn(badge);
                } else {
                    espDispOff(badge);
                }
                func_80116C18_mgmode(D_800A6D40_main[D_8011B6B0_mgmode[category][sel]].flags & 0x7FF);
                HuWinInsertMesSet(win, D_8011B6B0_mgmode[category][sel] + 0x4700, 0);
                HuWinMesSet(win, D_80119200_mgmode[D_8011B6B0_mgmode[category][sel]], -1, -1);
            } else {
                espDispOff(icon);
                HuWinMesSet(win, 0x4401, -1, -1);
            }
            HuPrcSleep(3);
        } else if ((D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) && D_8011B6B0_mgmode[category][sel] != 0xFF) {
            HuAudFXPlay(2);
            for (i = 0; i < 4; i++) {
                GwPlayer[i].group = i;
            }
            ok = 1;
            if (category == 1 || category == 2) {
                func_801182B4_mgmode(0);
                ok = func_8010A148_mgmode(category);
                if (ok == 0) {
                    func_8010A5F0_mgmode();
                    func_801182B4_mgmode(1);
                    HuPrcSleep(5);
                }
            }
            if (ok == 0) {
                continue;
            }
            HuWinMesSet(win, 0x4400, -1, -1);
            while (HuWinStatGet(win) != 0) {
                HuPrcVSleep();
            }
            next = HuWinChoiceGet(win, 0, 0);
            if (category == 1 || category == 2) {
                func_8010A5F0_mgmode();
            }
            if (next == -1) {
                func_801182B4_mgmode(1);
                HuPrcSleep(2);
                HuWinMesSet(win, D_80119200_mgmode[D_8011B6B0_mgmode[category][sel]], -1, -1);
                continue;
            }
            func_801182B4_mgmode(0);
            _SetFlag(13);
            func_80109DBC_mgmode(arg0, sel);
            if (next == 1) {
                GwSystem.show_minigame_explanations = 1;
            } else {
                GwSystem.show_minigame_explanations = 0;
            }
            GwSystem.minigame_index = D_8011B6B0_mgmode[category][sel] + 1;
            D_800D20B0_main = arg0;
            omOvlHisChg(0, 0x69, 1, 0x84);
            D_80118EB1_mgmode = 1;
            D_8011B95A_mgmode = 0x68;
            if (GwSystem.minigame_index == 0x47 || GwSystem.minigame_index == 0x1F) {
                D_8011B950_mgmode = 0;
            } else {
                HuAudSeqFadeOut(60);
                D_8011B950_mgmode = 1;
            }
            D_80118EB4_mgmode = 0x82;
            D_800D1FE0_main = 0;
            while (TRUE) {
                HuPrcVSleep();
            }
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            func_801182B4_mgmode(0);
            break;
        }
    }
    func_80116D4C_mgmode();
    espKill(badge);
    HuSprAnimKill(spriteGrp);
    HuWinExAnimOut(win, 0);
    for (i = 0; i < 8; i++) {
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 4);
    }
    HuWinKill(win);
}

void func_80109C10_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    f32 x;
    f32 z;
    f32 dist;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    func_8001C258_main(model, 4, 0);
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    Hu3DModelPosSet(model, x + D_8011AA80_mgmode[arg0][arg1].x, D_8011AA80_mgmode[arg0][arg1].y - 3.0f,
                    z + D_8011AA80_mgmode[arg0][arg1].z);
}

void func_80109DBC_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    s16 i;
    f32 x;
    f32 z;
    f32 dist;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 rotX;
    f32 t;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    rotX = 15.0f;
    startX = x + D_8011AA80_mgmode[arg0][arg1].x;
    startY = D_8011AA80_mgmode[arg0][arg1].y - 3.0f;
    startZ = z + D_8011AA80_mgmode[arg0][arg1].z;
    endX = Center.x + sindf(CRot.y) * cosdf(CRot.x) * CZoom - 50.0f;
    endY = Center.y + -sindf(CRot.x) * CZoom;
    endZ = Center.z + cosdf(CRot.y) * cosdf(CRot.x) * CZoom;
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (i == 20) {
            WipeCreateOut(11, 10);
        }
        t = i / 30.0f * 0.5f;
        Hu3DModelPosSet(model, startX + (endX - startX) * t, startY + (endY - startY) * t,
                        startZ + (endZ - startZ) * t);
        Hu3DModelRotSet(model, rotX, CRot.y - i * 3, 0.0f);
        rotX -= 3.0f;
        if (rotX < 0.0f) {
            rotX = 0.0f;
        }
    }
}

s16 func_8010A148_mgmode(s16 arg0) {
    s8 *orders;
    s16 i;
    s16 timer;
    s16 sel;
    s16 ret = 1;

    if (arg0 == 2) {
        D_8011B3E0_mgmode = D_80119320_mgmode;
    } else {
        D_8011B3E0_mgmode = D_8011932C_mgmode;
    }
    if (arg0 == 2) {
        orders = D_801192FC_mgmode;
    } else {
        orders = D_80119310_mgmode;
    }
    for (i = 0; i < 4; i++) {
        D_8011B3E6_mgmode[i] = i;
    }
    D_8011B3E4_mgmode = HuWinExCreate(-1, 50, 100, 220, 80, 0);
    HuWinActivePlayerSet(D_8011B3E4_mgmode, 1 << D_8011B808_mgmode);
    HuWinMesSet(D_8011B3E4_mgmode, 0x5729, -2, -1);
    HuWinExAnimIn(D_8011B3E4_mgmode);
    for (i = 0; i < 4; i++) {
        D_8011988C_mgmode[i].dataNum = (GwPlayer[i].chr + 0x36) | 0x130000;
    }
    D_8011988C_mgmode[4].dataNum = 0x120012;
    if (arg0 == 1) {
        D_8011988C_mgmode[5].dataNum = 0x120012;
    } else {
        D_8011988C_mgmode[5].dataNum = 0x120011;
    }
    sel = 0;
    D_8011B3EC_mgmode = func_80116794_mgmode(D_8011988C_mgmode);
    func_8010A62C_mgmode(160, 134);
    func_8010A824_mgmode(160, 134);
    timer = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (timer != 0) {
            timer--;
        }
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 && timer == 0) {
            HuAudFXPlay(1);
            if (D_800CBB6E_main[D_8011B808_mgmode] >= 31) {
                sel++;
                if (orders[sel * 4] == -1) {
                    sel = 0;
                }
            } else {
                sel--;
                if (sel < 0) {
                    for (i = 0; orders[i * 4] != -1; i++) {
                    }
                    sel = i - 1;
                }
            }
            for (i = 0; i < 4; i++) {
                D_8011B3E6_mgmode[i] = orders[sel * 4 + i];
            }
            func_8010A62C_mgmode(160, 134);
            timer = 10;
        } else if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
            HuAudFXPlay(2);
            if (arg0 == 2) {
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8011B3E6_mgmode[i]].group = D_800CB8B1_main[D_8011B3E6_mgmode[i]] = (i != 0);
                }
            } else {
                for (i = 0; i < 4; i++) {
                    GwPlayer[D_8011B3E6_mgmode[i]].group = D_800CB8B1_main[D_8011B3E6_mgmode[i]] = (i >= 2);
                }
            }
            break;
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            ret = 0;
            break;
        }
    }
    return ret;
}

void func_8010A5F0_mgmode(void) {
    func_801168E0_mgmode(D_8011B3EC_mgmode);
    HuWinExAnimOut(D_8011B3E4_mgmode, 0);
    HuWinKill(D_8011B3E4_mgmode);
}

void func_8010A62C_mgmode(s32 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i], arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i] + 10, arg0 + D_8011B3E0_mgmode[i] - 0x54,
                             arg1 + 0x1E);
        func_80116968_mgmode(D_8011B3EC_mgmode, i + 4, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        if (GwPlayer[D_8011B3E6_mgmode[i]].stat & 1) {
            func_801169A0_mgmode(D_8011B3EC_mgmode, i + 14);
            func_80116968_mgmode(D_8011B3EC_mgmode, i + 14, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1 + 0xE);
        } else {
            func_801169C8_mgmode(D_8011B3EC_mgmode, i + 14);
        }
    }
}

void func_8010A824_mgmode(s32 arg0, s32 arg1) {
    s32 offset = 0x54;

    func_80116968_mgmode(D_8011B3EC_mgmode, 18, D_8011B3E0_mgmode[4] + (arg0 - offset), arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 8, D_8011B3E0_mgmode[0] + arg0 - 0x70, arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 9, D_8011B3E0_mgmode[3] + arg0 - 0x38, arg1);
}

void func_8010A8E4_mgmode(s32 arg0) {
    s16 i;
    s16 k;
    s16 category;

    D_8011B77A_mgmode = 0;
    D_8011B80A_mgmode = 0;
    for (i = 0; i < 8; i++) {
        D_8011B940_mgmode[i] = D_8011B928_mgmode[i] = D_8011A968_mgmode[i] = D_8011AA10_mgmode[i] = 0;
    }
    for (i = 0; i < 71; i++) {
        category = D_800A6D40_main[i].minigameType;
        if (D_800A6D40_main[i].overlay == 0x70 || D_800A6D40_main[i].overlay == -1) {
            continue;
        }
        if (arg0 != 0 && (i == 27 || i == 8 || i == 16)) {
            continue;
        }
        if (GWMgUnlockCheck(i)) {
            D_8011B928_mgmode[category]++;
            D_8011B80A_mgmode++;
            if (D_800A6D40_main[i].flags >> 15) {
                D_8011A8C8_mgmode[category][D_8011A968_mgmode[category]] = i;
                D_8011A968_mgmode[category]++;
            } else {
                D_8011A970_mgmode[category][D_8011AA10_mgmode[category]] = i;
                D_8011AA10_mgmode[category]++;
            }
            D_8011B6B0_mgmode[category][D_8011B940_mgmode[category]] = i;
        } else {
            if (D_800A6D40_main[i].flags >> 15) {
                D_8011A8C8_mgmode[category][D_8011A968_mgmode[category]] = 0xFF;
                D_8011A968_mgmode[category]++;
            } else {
                D_8011A970_mgmode[category][D_8011AA10_mgmode[category]] = 0xFF;
                D_8011AA10_mgmode[category]++;
            }
            D_8011B6B0_mgmode[category][D_8011B940_mgmode[category]] = 0xFF;
        }
        D_8011B940_mgmode[category]++;
        D_8011B77A_mgmode++;
    }
    for (category = 0; category < 7; category++) {
        k = 0;
        for (i = 0; i < D_8011A968_mgmode[category]; i++) {
            D_8011B6B0_mgmode[category][k++] = D_8011A8C8_mgmode[category][i];
        }
        for (i = 0; i < D_8011AA10_mgmode[category]; i++) {
            D_8011B6B0_mgmode[category][k++] = D_8011A970_mgmode[category][i];
        }
    }
    D_8011B940_mgmode[7] = 3;
    D_8011B928_mgmode[7] = 0;
    if (_CheckFlag(0x1E)) {
        D_8011B6B0_mgmode[7][0] = 65;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][0] = 0xFF;
    }
    if (D_8011B928_mgmode[0] >= 20 && D_8011B928_mgmode[1] >= 10 && D_8011B928_mgmode[2] >= 10 &&
        D_8011B928_mgmode[3] >= 8 && D_8011B928_mgmode[4] >= 10 && D_8011B928_mgmode[5] >= 6) {
        D_8011B6B0_mgmode[7][1] = 70;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][1] = 0xFF;
    }
    if (_CheckFlag(0x1F)) {
        D_8011B6B0_mgmode[7][2] = 71;
        D_8011B928_mgmode[7]++;
        D_8011B80A_mgmode++;
    } else {
        D_8011B6B0_mgmode[7][2] = 0xFF;
    }
}

void func_8010AF78_mgmode(Gfx **arg0, s32 arg1, s32 arg2) {
    if (D_8011B884_mgmode != 0) {
        gDPSetDepthImage((*arg0)++, 0x3D0800);
        gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*arg0)++, D_80119290_mgmode);
    }
}

void func_8010AFEC_mgmode(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    while (TRUE) {
        rotX = CRot.x;
        rotY = CRot.y;
        rotZ = CRot.z;
        pos.x = sindf(rotY) * cosdf(rotX) * CZoom + Center.x;
        pos.y = -sindf(rotX) * CZoom + Center.y;
        pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        upX = sindf(rotY) * sindf(rotX);
        upY = cosdf(rotX);
        upZ = cosdf(rotY) * sindf(rotX);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        length = HuSqrtf(dx * dx + dy * dy + dz * dz);
        dx /= length;
        dy /= length;
        dz /= length;
        up.x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(rotZ)) +
               upY * (dx * dy * (1.0f - cosdf(rotZ)) - dz * sindf(rotZ)) +
               upZ * (dx * dz * (1.0f - cosdf(rotZ)) + dy * sindf(rotZ));
        up.y = upX * (dx * dy * (1.0f - cosdf(rotZ)) + dz * sindf(rotZ)) +
               upY * (dy * dy + (1.0f - dy * dy) * cosdf(rotZ)) +
               upZ * (dy * dz * (1.0f - cosdf(rotZ)) - dx * sindf(rotZ));
        up.z = upX * (dx * dz * (1.0f - cosdf(rotZ)) - dy * sindf(rotZ)) +
               upY * (dy * dz * (1.0f - cosdf(rotZ)) + dx * sindf(rotZ)) +
               upZ * (dz * dz + (1.0f - dz * dz) * cosdf(rotZ));
        Hu3DCameraPerspectiveSet(0, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
        Hu3DCameraPosSetV(0, &pos, &at, &up);
        Hu3DCamUpdateMtx(0);
        Hu3DCameraPerspectiveSet(1, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
        Hu3DCameraPosSetV(1, &pos, &at, &up);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

void func_8010B574_mgmode(void) {
    char buf[256];
    HmfModel *model;
    f32 rotX;
    f32 rotY;
    f32 speed;
    f32 dirZ;
    f32 inv;

    model = &HmfModelData[D_8011B8A8_mgmode[15]];
    if (D_800D5558_main[1] & 0x10) {
        D_80118EB0_mgmode ^= 1;
        if (D_80118EB0_mgmode) {
            osSyncPrintf("\t{\n\t{%4.1f,%4.1f,%4.1f},\n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf("\t{%4.1f,%4.1f,%4.1f},\n", Center.x, Center.y, Center.z);
            osSyncPrintf("\t%4.1f,%4.1f\n\t},\n", CZoom, D_8011B6A4_mgmode);
            osSyncPrintf("HMF>%4.1f,%4.1f,%4.1f\n", model->rot.x, model->rot.y, model->rot.z);
        }
    }
    if (D_800CDA7C_main[1] & 0x1000) {
        func_80116E24_mgmode(D_8011B958_mgmode);
    }
    if (D_800CDA7C_main[1] & 8) {
        CZoom = (D_800CDA7C_main[1] & 0x2000) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((D_800CDA7C_main[1] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (D_800CDA7C_main[1] & 0x2000) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (D_800CDA7C_main[1] & 2) {
        D_8011B6A4_mgmode += 1.0f;
    }
    if (D_800CDA7C_main[1] & 1) {
        D_8011B6A4_mgmode -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, D_8011B6A4_mgmode, D_8011B804_mgmode, D_8011B888_mgmode);
    rotX = D_8011B898_mgmode.x;
    rotY = D_8011B898_mgmode.y;
    speed = (D_800CDA7C_main[1] & 0x2000) ? 5.0f : 2.0f;
    rotY += (-D_800CBB6E_main[1] / 30) * speed;
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    } else if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    D_8011B898_mgmode.y = rotY;
    rotX += (s8)(D_800D20A1_main[1] / 30) * speed;
    if (rotX >= 360.0f) {
        rotX -= 360.0f;
    } else if (rotX < 0.0f) {
        rotX += 360.0f;
    }
    D_8011B898_mgmode.x = rotX;
    CRot.x = (s16)rotX;
    CRot.y = (s16)D_8011B898_mgmode.y;
    speed = (D_800CDA7C_main[1] & 0x2000) ? 10.0f : 2.0f;
    if (D_800CDA7C_main[1] & 0x800) {
        Center.x += sindf(rotY) * sindf(rotX) * -speed;
        Center.y += cosdf(rotX) * -speed;
        Center.z += cosdf(rotY) * sindf(rotX) * -speed;
    } else if (D_800CDA7C_main[1] & 0x400) {
        Center.x += sindf(rotY) * sindf(rotX) * speed;
        Center.y += cosdf(rotX) * speed;
        Center.z += cosdf(rotY) * sindf(rotX) * speed;
    } else if (D_800CDA7C_main[1] & 0x200) {
        // rotX is reused here as the X component of the camera direction.
        rotX = gCameraList->pos.z - Center.z;
        dirZ = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    } else if (D_800CDA7C_main[1] & 0x100) {
        rotX = -(gCameraList->pos.z - Center.z);
        dirZ = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    }
    if (D_80118EB0_mgmode) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, D_8011B6A4_mgmode);
        print8(32, 200, buf);
    }
}

void func_8010BD28_mgmode(omObjData *arg0) {
    if ((D_80118EB1_mgmode != 0) || (D_800D530C_main != 0)) {
        if ((D_80118EB4_mgmode & 0x80) == 0) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        arg0->func = func_8010BD98_mgmode;
    }
}

void func_8010BD98_mgmode(omObjData *arg0) {
    if (WipeStatGet() != 0) {
        return;
    }
    HuWinAllKill();
    if (D_80118EB2_mgmode != 0) {
        func_80118CD8_mgmode();
    }
    func_80116D4C_mgmode();
    D_80118EB4_mgmode &= 0xF;
    _ClearFlag(0x1C);
    if (D_80118EB4_mgmode == 0) {
        omOvlReturnEx(1);
    } else if (D_80118EB4_mgmode == 2) {
        if (D_8011B95A_mgmode == 0x68) {
            _SetFlag(0x1C);
        }
        if (D_8011B95A_mgmode == 0x70) {
            _SetFlag(0x1C);
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
        } else {
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x84);
        }
    } else {
        omOvlGotoEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
    }
}
