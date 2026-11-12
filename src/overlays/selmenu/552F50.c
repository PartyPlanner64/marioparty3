#include "common.h"
#include "gcc/string.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct SelMenuConfig {
    u8 available;
    u8 player_groups;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    char *name;
} SelMenuConfig; // sizeof 0x10

typedef struct SelMenuPlayerGroups {
    u8 group[4];
    u8 unk_04[0xC];
} SelMenuPlayerGroups; // sizeof 0x10

typedef struct SelMenuSound {
    s16 fx;
    u8 unk_02;
    s8 vol;
} SelMenuSound; // sizeof 0x4

extern s16 D_8010A070_selmenu;
extern s16 D_8010A072_selmenu;
extern SelMenuConfig D_80108C90_selmenu[];
extern SelMenuPlayerGroups D_801092C0_selmenu[];
extern s16 D_8010A078_selmenu[];
extern GW_PLAYER D_8010A098_selmenu[];
extern SelMenuSound D_80109740_selmenu[];
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s16 D_8010A08C_selmenu;
extern s16 D_8010A08E_selmenu;
extern s16 D_8010A090_selmenu;
extern s16 D_8010A1C0_selmenu[];
extern s16 D_8010A1D0_selmenu[];
extern s16 D_8010A1E0_selmenu[];
extern s8 D_8010A1F8_selmenu[];
extern s8 D_8010A1FC_selmenu[];
extern u8 D_8010A200_selmenu;
extern s16 D_8010A202_selmenu;
extern s16 D_8010A204_selmenu;
extern u16 D_8010A206_selmenu;
extern u8 D_8010A270_selmenu[];
extern u16 D_80109754_selmenu[2][2];
extern char *D_801097F4_selmenu[];
extern u8 D_80109800_selmenu;
extern s32 D_80109810_selmenu;
extern s32 D_80109814_selmenu;
extern s32 D_80109818_selmenu;
extern s16 D_8010A208_selmenu;
extern s16 D_8010A210_selmenu[];
extern u16 D_8010A274_selmenu[];
extern u16 D_8010A27C_selmenu[];
extern u16 D_8010A284_selmenu[];
extern char D_80109FEC_selmenu[];
extern char D_80109FF8_selmenu[];
extern u8 D_8010A1B0_selmenu[];
extern u8 D_8010A1B4_selmenu[];
extern s16 D_8010A1F0_selmenu[];
extern s32 D_8010A260_selmenu[];

void func_80105F30_selmenu(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void func_80105FC8_selmenu(omObjData *obj);
void func_80106770_selmenu(omObjData *obj);
void func_80106A10_selmenu(omObjData *obj);
void func_80106DEC_selmenu(omObjData *obj);
void func_80107924_selmenu(omObjData *obj);
void func_80107DEC_selmenu(omObjData *obj);
void func_80107DFC_selmenu(omObjData *obj);
void func_801087C8_selmenu(u16 index);
void func_80108814_selmenu(s16 dir);
void func_801089C0_selmenu(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void func_80108890_selmenu(s16 dir);
void func_80108A40_selmenu(void);

void func_801059A0_selmenu(void) {
    omObjData *obj;
    u16 sprite;
    s32 i;

    D_8010A200_selmenu = 0;
    _SetFlag(0x12);
    GwSystem.show_minigame_explanations = 0;
    if (omprevovl >= 0 && omprevovl < 71) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].coin += GwPlayer[i].gameCoin;
            GwPlayer[i].coin += GwPlayer[i].bonusCoin;
            if (GwPlayer[i].coin >= 1000) {
                GwPlayer[i].coin = 999;
            }
            if (GwPlayer[i].coin < 0) {
                GwPlayer[i].coin = 0;
            }
            GwPlayer[i].gameCoin = 0;
            GwPlayer[i].bonusCoin = 0;
        }
    }
    omInitObjMan(50, 0);
    func_80105F30_selmenu(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x60, 0x60, 0x10);
    Hu3DGLightDirSet(1, 100.0f, -100.0f, 100.0f);
    omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omAddObj(0, 0, 0, -1, func_80105FC8_selmenu);
    omAddObj(1, 0, 0, -1, func_80106770_selmenu);
    omMakeGroup(0, 32);
    obj = omAddObj(10, 1, 80, -1, NULL);
    for (i = 0; i < 8; i++) {
        D_8010A1C0_selmenu[i] = func_8000B108_main(D_800A178C_main[i][0] | D_800A1790_main[i][0], 0x69D);
        Hu3DData[D_8010A1C0_selmenu[i]].motAttr |= 2;
        func_8000B460_main(obj, 0, func_80017BB8_main(i, 0));
        D_8010A1D0_selmenu[i] = obj->motion[0];
        func_8000B460_main(obj, 1, func_80017BB8_main(i, 0x2F));
        D_8010A1E0_selmenu[i] = obj->motion[1];
    }
    omDelObj(obj);
    for (i = 0; i < 4; i++) {
        D_8010A1FC_selmenu[i] = 0;
        D_8010A1F8_selmenu[i] = 0;
    }
    D_8010A202_selmenu = func_8000B838_main(0x10020);
    func_8000B880_main(D_8010A202_selmenu, 0.3f, 0.3f, 0.3f);
    for (i = 0; i < 35; i++) {
        sprite = espEntry(D_8010A202_selmenu, i % 6, 1);
        espDispOn(sprite);
        espPriSet(sprite, 0xFFFF);
        espAttrSet(sprite, 0x4000);
        espTPLvlSet(sprite, 0xFF);
        espPosSet(sprite, (i % 7) * 48, (i / 7) * 48);
    }
    D_8010A204_selmenu = func_8000B838_main(10);
    D_8010A206_selmenu = espEntry(D_8010A204_selmenu, 0, 1);
    espDispOn(D_8010A206_selmenu);
    espPosSet(D_8010A206_selmenu, 0x80, 0x80);
    espScaleSet(D_8010A206_selmenu, 0.25f, 0.25f);
    for (i = 0; i < 40; i++) {
        D_8010A210_selmenu[i] = -1;
    }
    D_8010A208_selmenu = func_8000B838_main(12);
    for (i = 0; i < 4; i++) {
        D_8010A27C_selmenu[i] = 0;
        D_8010A284_selmenu[i] = 0;
        D_8010A274_selmenu[i] = 0;
    }
    WipeCreateIn(0xFF, 16);
    HuAudSeqPlay(rand8() % 9);
}

void func_80105F30_selmenu(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    func_8000B5F0_main(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
}

void func_80105FC8_selmenu(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010A270_selmenu[i] = 0;
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        stickX = D_800CBB6E_main[i];
        stickY = D_800D20A1_main[i];
        if (D_800D5558_main[i] & (U_JPAD | U_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 1;
        }
        if (D_800D5558_main[i] & (D_JPAD | D_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 2;
        }
        if (D_800D5558_main[i] & (L_JPAD | L_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 4;
        }
        if (D_800D5558_main[i] & (R_JPAD | R_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 8;
        }
        if (stickY < -10 && ABS(D_8010A1FC_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 2;
        }
        if (stickY > 10 && ABS(D_8010A1FC_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 1;
        }
        if (stickX < -10 && ABS(D_8010A1F8_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 4;
        }
        if (stickX > 10 && ABS(D_8010A1F8_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 8;
        }
        D_8010A1F8_selmenu[i] = stickX;
        D_8010A1FC_selmenu[i] = stickY;
        if (D_800D5558_main[i] & Z_TRIG) {
            D_8010A270_selmenu[i] |= 0x40;
        }
        if ((D_800CDA7C_main[i] & (U_JPAD | U_CBUTTONS)) || stickY > 10) {
            if (D_8010A274_selmenu[i] & 1) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 1) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 1;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 1;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (D_JPAD | D_CBUTTONS)) || stickY < -10) {
            if (D_8010A274_selmenu[i] & 2) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 2) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 2;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 2;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (L_JPAD | L_CBUTTONS)) || stickX < -10) {
            if (D_8010A274_selmenu[i] & 4) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 4) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 4;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 4;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (R_JPAD | R_CBUTTONS)) || stickX > 10) {
            if (D_8010A274_selmenu[i] & 8) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 8) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 8;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 8;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else {
            D_8010A27C_selmenu[i] = 0;
        }
        if (D_800D5558_main[i] & A_BUTTON) {
            D_8010A270_selmenu[i] |= 0x10;
        }
        if (D_800D5558_main[i] & B_BUTTON) {
            D_8010A270_selmenu[i] |= 0x20;
        }
        if (D_800D5558_main[i] & START_BUTTON) {
            D_8010A270_selmenu[i] |= 0x80;
        }
        if ((D_800CDA7C_main[i] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
            omOvlReturnEx(0);
            return;
        }
    }
}

void func_80106770_selmenu(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        D_8010A1B4_selmenu[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].chr = i;
        D_8010A1F0_selmenu[i] = i;
        D_8010A1B0_selmenu[i] = 0;
        D_8010A260_selmenu[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_8010A1B4_selmenu[i] = 1;
        }
    }
    D_8010A070_selmenu = -1;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (D_80108C90_selmenu[i * 10 + j].available != 1) {
                break;
            }
        }
        if (j == 10) {
            D_8010A078_selmenu[i] = -1;
        } else {
            D_8010A078_selmenu[i] = j;
        }
    }
    func_80108890_selmenu(1);
    if (omprevovl != 999) {
        for (i = 0; i < 100; i++) {
            if (D_80108C90_selmenu[i].unk_04 == omprevovl) {
                D_8010A070_selmenu = i / 10;
                D_8010A072_selmenu = i % 10;
                D_8010A078_selmenu[D_8010A070_selmenu] = D_8010A072_selmenu;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_8010A098_selmenu[i] = GwPlayer[i];
    }
    func_80108A40_selmenu();
    obj->func = func_80106A10_selmenu;
}

#ifdef NON_MATCHING
// The x coordinate 0x40 is loaded before the availability branch and zero-extended at the shared call.
void func_80106A10_selmenu(omObjData *obj) {
    SelMenuConfig *config;
    u16 *color;
    s32 i;

    rand8();
    config = &D_80108C90_selmenu[D_8010A070_selmenu * 10];
    for (i = 0; i < 10; i++, config++) {
        sprintf(D_800D5218_main, config->name);
        strlen(D_800D5218_main);
        if (D_80108C90_selmenu[D_8010A070_selmenu * 10 + i].available == 0) {
            color = D_80109754_selmenu[0];
        } else {
            color = D_80109754_selmenu[1];
        }
        if (D_8010A072_selmenu == i) {
            func_801089C0_selmenu(0x40, (i + 10) * 9, D_800D5218_main, color[1], color[0]);
        } else {
            func_801089C0_selmenu(0x40, (i + 10) * 9, D_800D5218_main, color[0], 0);
        }
    }
    sprintf(D_800D5218_main, D_80109FEC_selmenu, D_8010A070_selmenu + 1, 10);
    func_801089C0_selmenu(0x80, 0x40, D_800D5218_main, 15, 7);
    sprintf(D_800D5218_main, D_80109FF8_selmenu, D_801097F4_selmenu[D_800A175E_main]);
    func_801089C0_selmenu(0x80, 0x48, D_800D5218_main, 14, 6);
    espPosSet(D_8010A206_selmenu, 0x3C, (D_8010A072_selmenu + 11) * 9 - 1);
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if ((D_8010A270_selmenu[i] & 0x90) && D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].available == 0) {
            if (D_80109800_selmenu == 0) {
                omAddObj(2, 0, 0, -1, func_80107DEC_selmenu);
                D_80109800_selmenu = 1;
                espDispOff(D_8010A206_selmenu);
                obj->func = func_80107924_selmenu;
                func_801087C8_selmenu(1);
            }
        } else if (D_8010A270_selmenu[i] & 1) {
            func_80108814_selmenu(-1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(0);
        } else if (D_8010A270_selmenu[i] & 2) {
            func_80108814_selmenu(1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(0);
        } else if (D_8010A270_selmenu[i] & 4) {
            func_80108890_selmenu(-1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(4);
        } else if (D_8010A270_selmenu[i] & 8) {
            func_80108890_selmenu(1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(4);
        } else if (D_8010A270_selmenu[i] & 0x40) {
            D_8010A08C_selmenu = 0;
            D_8010A08E_selmenu = 0;
            D_8010A090_selmenu = 0;
            obj->func = func_80106DEC_selmenu;
        } else if (D_800D5558_main[i] & 0x10) {
            if (++D_800A175E_main >= 3) {
                D_800A175E_main = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106A10_selmenu);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80106DEC_selmenu);

#ifdef NON_MATCHING
// The initial textOfs value is constant-folded into the sprite y positions, and shadowOfs/textOfs registers swap.
void func_80107924_selmenu(omObjData *obj) {
    u32 x;
    s32 y;
    s32 shadowOfs = 12;
    s32 textOfs = 6;
    s32 i;

    rand8();
    sprintf(D_800D5218_main, D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].name);
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    y = (D_8010A072_selmenu + 10) * 9;
    if (y - D_80109810_selmenu > 48) {
        if (--D_80109818_selmenu == 0) {
            D_8010A210_selmenu[D_80109814_selmenu] = espEntry(D_8010A208_selmenu, 0, 1);
            espAttrSet(D_8010A210_selmenu[D_80109814_selmenu], 0x4000);
            espPriSet(D_8010A210_selmenu[D_80109814_selmenu], 0x8000);
            espScaleSet(D_8010A210_selmenu[D_80109814_selmenu], 0.75f, 0.75f);
            espSpeedSet(D_8010A210_selmenu[D_80109814_selmenu], 8.0f);
            espPosSet(D_8010A210_selmenu[D_80109814_selmenu], x, y - (u16)D_80109810_selmenu + textOfs + 8);
            espColorSet(D_8010A210_selmenu[D_80109814_selmenu], 0xFF, 0xFF, 0xBE);
            D_80109814_selmenu++;
            D_8010A210_selmenu[D_80109814_selmenu] = espEntry(D_8010A208_selmenu, 0, 1);
            espAttrSet(D_8010A210_selmenu[D_80109814_selmenu], 0x4000);
            espPriSet(D_8010A210_selmenu[D_80109814_selmenu], 0x8000);
            espScaleSet(D_8010A210_selmenu[D_80109814_selmenu], 0.75f, 0.75f);
            espSpeedSet(D_8010A210_selmenu[D_80109814_selmenu], 8.0f);
            espPosSet(D_8010A210_selmenu[D_80109814_selmenu],
                      x + strlen(D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].name) * 8,
                      y - (u16)D_80109810_selmenu + textOfs + 8);
            espColorSet(D_8010A210_selmenu[D_80109814_selmenu], 0xFF, 0xFF, 0xBE);
            D_80109814_selmenu++;
            D_80109818_selmenu = 4;
        }
        D_80109810_selmenu += 4;
        if (y < y - D_80109810_selmenu + shadowOfs) {
            shadowOfs = (y - D_80109810_selmenu + shadowOfs) - y;
        }
        if (y < y - D_80109810_selmenu + textOfs) {
            textOfs = (y - D_80109810_selmenu + textOfs) - y;
        }
        fontcolor = 9;
        print8(x, y - (u16)D_80109810_selmenu + shadowOfs, D_800D5218_main);
        fontcolor = 13;
        print8(x, y - (u16)D_80109810_selmenu + textOfs, D_800D5218_main);
    }
    for (i = 0; i < D_80109814_selmenu; i++) {
        if (D_8010A210_selmenu[i] != -1 && (func_8000BE1C_main(D_8010A210_selmenu[i]) & 6)) {
            espKill(D_8010A210_selmenu[i]);
            D_8010A210_selmenu[i] = -1;
        }
    }
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    fontcolor = 7;
    print8(x + 1, y + 1 - (u16)D_80109810_selmenu, D_800D5218_main);
    fontcolor = 15;
    print8(x, y - (u16)D_80109810_selmenu, D_800D5218_main);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107924_selmenu);
#endif

void func_80107DEC_selmenu(omObjData *obj) {
    obj->func = func_80107DFC_selmenu;
}

INCLUDE_ASM("asm/nonmatchings/overlays/selmenu/552F50", func_80107DFC_selmenu);

void func_801087C8_selmenu(u16 index) {
    HuAudFXVolSet(HuAudFXPlay(D_80109740_selmenu[index].fx), D_80109740_selmenu[index].vol);
}

void func_80108814_selmenu(s16 dir) {
    s16 index = D_8010A072_selmenu;

    do {
        index += dir;
        if (index >= 10) {
            index = 0;
        } else if (index < 0) {
            index = 9;
        }
    } while (D_80108C90_selmenu[D_8010A070_selmenu * 10 + index].available == 1);
    D_8010A072_selmenu = index;
}

void func_80108890_selmenu(s16 dir) {
    u16 found = FALSE;
    s16 prevPage;
    s16 page;
    s32 i;

    prevPage = page = D_8010A070_selmenu;
    do {
        page += dir;
        if (page >= 10) {
            page = 0;
        } else if (page < 0) {
            page = 9;
        }
        for (i = 0; i < 10; i++) {
            if (D_80108C90_selmenu[page * 10 + i].available == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    D_8010A070_selmenu = page;
    if (prevPage == -1) {
        D_8010A072_selmenu = -1;
        func_80108814_selmenu(1);
        D_8010A078_selmenu[D_8010A070_selmenu] = D_8010A072_selmenu;
    } else {
        D_8010A078_selmenu[prevPage] = D_8010A072_selmenu;
        D_8010A072_selmenu = D_8010A078_selmenu[D_8010A070_selmenu];
    }
}

void func_801089C0_selmenu(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_80108A40_selmenu(void) {
    SelMenuPlayerGroups *groups = &D_801092C0_selmenu[D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].player_groups];
    GW_PLAYER *player = D_8010A098_selmenu;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void func_80108AB4_selmenu(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &D_8010A098_selmenu[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void func_80108B1C_selmenu(void) {
    u8 groups[4];
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        groups[i] = D_8010A098_selmenu[i].group;
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_8010A098_selmenu[i].group = groups[r];
    }
}

void func_80108BE8_selmenu(void) {
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_8010A098_selmenu[i].pad = r;
    }
}
