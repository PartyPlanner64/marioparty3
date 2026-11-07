#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "mgresultbattle.h"

void func_80105E0C_mgresultbattle(void);
void func_80105EF4_mgresultbattle(void);
void func_801060A4_mgresultbattle(void);
void func_80106660_mgresultbattle(void);
void func_80106BA0_mgresultbattle(void);
void func_80107400_mgresultbattle(void);
void func_80107D10_mgresultbattle(void);
void func_80108130_mgresultbattle(void);
void func_80105CAC_mgresultbattle(omObjData *);
void func_80105E64_mgresultbattle(omObjData *);
void func_80105F50_mgresultbattle(void);
void func_80105F78_mgresultbattle(Gfx **, s32, s32);
void func_801069FC_mgresultbattle(omObjData *);
void func_801075FC_mgresultbattle(void);
void func_80106908_mgresultbattle(void);
void func_80106910_mgresultbattle(omObjData *obj);

extern s8 D_80108F8C_mgresultbattle[4];
extern s32 D_800A178C_main[][6];
extern Vec D_801089D0_mgresultbattle[4];
extern s32 D_80108908_mgresultbattle[];
extern s8 D_801088D8_mgresultbattle;
extern s8 D_801088D0_mgresultbattle;
extern s32 D_801088D4_mgresultbattle;
extern s32 D_80108F70_mgresultbattle;
extern const s8 D_801089A0_mgresultbattle[];
extern const f32 D_80108920_mgresultbattle[][4];
extern u16 D_800CC698_main;

void func_801059A0_mgresultbattle(void) {
    s16 var_a0_2;
    s16 var_a1;
    s16 i;
    s16 j;

    var_a1 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_80108F8C_mgresultbattle[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    func_800142A0_main(0x78);
    omInitObjMan(0x1E, 0x1E);
    func_8000B690_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);

    for (var_a0_2 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].bonusCoin == 3) {
            var_a0_2++;
        }
    }

    if (var_a0_2 >= 4) {
        GameMesStub();
        MBBackKill();
        MBBackClose();
        omOvlReturnEx(1);
        return;
    }
    func_801060A4_mgresultbattle();
    omAddPrcObj(func_80108130_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107400_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107D10_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106660_mgresultbattle, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106BA0_mgresultbattle, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, func_80105CAC_mgresultbattle);
    omAddObj(0, 0, 0, -1, func_80105E64_mgresultbattle);
    func_80105EF4_mgresultbattle();
    func_80105E0C_mgresultbattle();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105CAC_mgresultbattle(omObjData *obj) {
    s32 state;
    s32 i;
    s32 coins;
    s32 newCoins;

    state = D_801088D0_mgresultbattle;
    switch (state) {
        case 0:
            HuAudSeqPlay(0x15);
            D_801088D4_mgresultbattle = 0;
            state++;
            break;
        case 1:
            state++;
            break;
        case 2:
            if (D_801088D4_mgresultbattle++ >= 6) {
                func_801075FC_mgresultbattle();
                D_801088D4_mgresultbattle = 0;
                state++;
            }
            break;
        case 4:
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coins = GwPlayer[i].coin + GwPlayer[i].gameCoin;
                if (coins <= 999) {
                    newCoins = coins;
                } else {
                    newCoins = 999;
                }
                GwPlayer[i].coin = newCoins;
                MBPlayerCoinAdd(i, 0);
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            state++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                GameMesStub();
                MBBackKill();
                MBBackClose();
                omOvlReturnEx(1);
            }
            break;
    }
    D_801088D0_mgresultbattle = state;
}

void func_80105E0C_mgresultbattle(void) {
    CZoom = 2300.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 390.0f;
    Center.z = -460.0f;
}

void func_80105E64_mgresultbattle(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_801088D8_mgresultbattle == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            D_801088D8_mgresultbattle = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            GameMesStub();
            MBBackKill();
            MBBackClose();
            omOvlReturnEx(1);
        }
    }
}

void func_80105EF4_mgresultbattle(void) {
    GW_SYSTEM *system = &GwSystem;

    func_800E6630_shared_board((u32)hvq_data_ROM_START);

    if (!(system->playMode & 2)) {
        MBBackCreate(D_80108908_mgresultbattle[system->current_board_index], 0);
    } else {
        MBBackCreate(0x17, 0);
    }
    func_80105F50_mgresultbattle();
}

void func_80105F50_mgresultbattle(void) {
    Hu3DHookFuncCreate(0, func_80105F78_mgresultbattle, 0);
}

void func_80105F78_mgresultbattle(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *gdl = *gfx;

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gdl++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(gdl++, G_TP_NONE);
    gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, 127);
    gDPSetRenderMode(gdl++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode(gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetTextureLUT(gdl++, G_TT_NONE);
    gDPSetFillColor(gdl++, 0x10001);
    gDPFillRectangle(gdl++, 0, 0, 319, 239);
    *gfx = gdl;
}

void func_801060A4_mgresultbattle(void) {
    s32 order[4];
    s32 ranks[4];
    s8 rankCounts[4];
    s32 rank;
    s32 total;
    s32 type;
    s32 count;
    s32 i;
    s32 j;
    s32 player;

    for (i = 0, j = 0; i < 4; i++) {
        j += (GwPlayer[i].bonusCoin >= 3);
    }
    if (j >= 4) {
        D_80108F70_mgresultbattle = 0;
        for (i = 0; i < 4; i++) {
            GwPlayer[i].gameCoin = 0;
            GwPlayer[i].coin += GwPlayer[i].checkCoin;
        }
        return;
    }

    rank = 0;
    count = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            if (j == GwPlayer[i].bonusCoin) {
                count++;
                ranks[i] = rank;
            }
        }
        rank += count;
        count = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].bonusCoin = ranks[i];
    }
    for (i = 0; i < 4; i++) {
        rankCounts[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        rankCounts[GwPlayer[i].bonusCoin]++;
    }

    type = 0;
    if (rankCounts[0] == 1 && rankCounts[1] == 1 && rankCounts[2] == 1 && rankCounts[3] == 1) {
        type = 0;
    } else if (rankCounts[0] == 2 && rankCounts[2] == 2) {
        type = 2;
    } else if (rankCounts[0] == 2) {
        type = 1;
    } else if (rankCounts[0] == 3) {
        type = 3;
    } else if (rankCounts[1] == 2) {
        type = 4;
    } else if (rankCounts[1] == 3) {
        type = 5;
    } else if (rankCounts[2] == 2) {
        type = 6;
    } else if (rankCounts[0] == 4) {
        type = 7;
    }

    total = 0;
    for (i = 0; i < 4; i++) {
        if (D_801089A0_mgresultbattle[type] == 0) {
            GwPlayer[i].gameCoin = D_800CC698_main * D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin];
        } else if (D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin] != 0.0f) {
            GwPlayer[i].gameCoin = D_800CC698_main / D_80108920_mgresultbattle[type][GwPlayer[i].bonusCoin];
        } else {
            GwPlayer[i].gameCoin = 0;
        }
        total += GwPlayer[i].gameCoin;
    }
    D_80108F70_mgresultbattle = D_800CC698_main - total;

    switch (type) {
        case 4:
            if (D_80108F70_mgresultbattle == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 1) {
                        GwPlayer[i].gameCoin += 1;
                    }
                }
                D_80108F70_mgresultbattle = 0;
            }
            break;
        case 5:
            if (D_80108F70_mgresultbattle == 3) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 1) {
                        GwPlayer[i].gameCoin += 1;
                    }
                }
                D_80108F70_mgresultbattle = 0;
            }
            break;
        case 6:
            if (D_80108F70_mgresultbattle == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 0) {
                        GwPlayer[i].gameCoin += 2;
                        break;
                    }
                }
                D_80108F70_mgresultbattle = 0;
            }
            break;
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            player = D_80108F8C_mgresultbattle[j];
            if (i == GwPlayer[player].bonusCoin) {
                order[count++] = player;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_80108F8C_mgresultbattle[i] = order[i];
    }
}

void func_80106660_mgresultbattle(void) {
    omObjData *obj;
    s32 i;
    s32 chr;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(0x14, 4, 8, -1, NULL);
        D_80108F50_mgresultbattle[i].obj = obj;
        chr = GwPlayer[D_80108F8C_mgresultbattle[i]].chr;

        obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x2B9);
        func_8001C814_main(obj->model[1], 2, 2);
        obj->model[2] = func_8000B108_main(9, 0x2B9);
        Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 0.0f);

        func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
        func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
        func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x36));
        func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x25));
        func_8001C5B4_main(obj->model[1], obj->motion[0]);
        func_8001C814_main(obj->model[1], 2, 2);
        Hu3DModelPosSet(obj->model[1], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);
        Hu3DModelPosSet(obj->model[2], D_801089D0_mgresultbattle[i].x, D_801089D0_mgresultbattle[i].y,
                        D_801089D0_mgresultbattle[i].z);

        obj->trans.x = 0.0f;
        obj->trans.y = 0.0f;
        obj->trans.z = 0.0f;
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
        omPrcSetDestructor(NULL, func_80106908_mgresultbattle);
        D_80108F50_mgresultbattle[i].func = func_80106910_mgresultbattle;
    }

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            D_80108F50_mgresultbattle[i].func(obj);
            HuPrcVSleep();
        }
    }
}

void func_80106908_mgresultbattle(void) {
}

void func_80106910_mgresultbattle(omObjData *obj) {
}

void func_80106918_mgresultbattle(void) {
    omObjData *obj;
    s32 motion;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_80108F50_mgresultbattle[i].obj;
        if (GwPlayer[D_80108F8C_mgresultbattle[i]].gameCoin > 0) {
            motion = 1;
            PlayerFXPlay(0x274, D_80108F8C_mgresultbattle[i]);
        } else {
            motion = 2;
        }
        Hu3DMotionShiftSet(obj->model[1], HmfModelData[obj->motion[motion]].motId, 0, 0x14, 0);
    }
    D_80108F50_mgresultbattle[0].func = func_801069FC_mgresultbattle;
}

void func_801069FC_mgresultbattle(omObjData *obj) {
    s32 pressed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    while (!(Hu3DMotionShiftTimeGet(obj->model[1]) < 0.0f)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if (D_800CCF58_main[HmfModelData[obj->model[1]].motId].unk02 <= HmfModelData[obj->model[1]].motTime) {
            pressed = 0;
            for (i = 0; i < 40; i++) {
                for (j = 0; j < 4; j++) {
                    if (!(GwPlayer[j].stat & 1) && (D_800D5558_main[GwPlayer[j].pad] & A_BUTTON)) {
                        pressed = 1;
                        break;
                    }
                }
                if (pressed == 1) {
                    break;
                }
                HuPrcVSleep();
            }
            D_801088D0_mgresultbattle = 4;
            break;
        }
        HuPrcVSleep();
    }
    D_80108F50_mgresultbattle[0].func = func_80106910_mgresultbattle;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108908_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F3780", D_80108920_mgresultbattle);
