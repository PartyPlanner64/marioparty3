#include "common.h"
#include "inst.h"

typedef struct {
    s32 overlay;
    u8 minigameType;
    u8 unk05;
    u16 flags;
    u8 unk08[12];
} InstMinigameEntry;

extern InstModelHooks *D_8010D4C0_inst[][2];
extern s32 D_8010D90C_inst[][2];
extern s32 D_8010D910_inst[][2];
extern s32 D_8010D954_inst[];

extern InstMinigameEntry D_800A6D40_main[];
extern char D_8010D978_inst[];
extern char D_8010D980_inst[];
extern s32 D_8010D43C_inst;
extern s32 D_8010D440_inst;
extern s32 D_8010DC00_inst;
extern s16 D_8010DC02_inst;
extern s8 D_8010D404_inst;
extern s8 D_8010D405_inst;
extern s8 D_8010D406_inst;
extern s8 D_8010D409_inst;
extern Vec D_8010D444_inst[4];
extern Vec D_8010D474_inst[4];
extern s8 D_8010D5B1_inst;
extern u8 D_800CE20A_main;
extern s32 D_8010D4A4_inst;
extern u32 D_8010D4AC_inst;
extern s16 D_8010DC28_inst;
extern s16 D_8010DC22_inst;
extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;

extern s8 D_8010D400_inst[4];
extern s8 D_8010D401_inst[3];
extern s8 D_8010D402_inst[2];
extern s8 D_8010D407_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D40B_inst;
extern s8 D_8010D411_inst;
extern s8 D_8010D4A8_inst;
extern f32 D_8010D414_inst;
extern Vec D_8010D418_inst;
extern Vec D_8010D424_inst;
extern Vec D_8010D430_inst;
extern void *D_8010DC10_inst;
extern void *D_8010DC14_inst;
extern void *D_8010DC18_inst;
extern InstObjectState D_8010DDD8_inst;
extern void (*D_8010DDEC_inst)(omObjData *);
extern s32 D_8010D658_inst[];
extern s32 D_8010D508_inst;
extern f32 D_8010D50C_inst;
extern s32 D_8010D510_inst;
extern s32 D_8010D520_inst;
extern s32 D_8010D524_inst;
extern s32 D_8010D530_inst;
extern s32 D_8010D534_inst;
extern s8 D_8010D40C_inst[5];
extern u8 D_8010D4B0_inst[8];
extern u8 D_8010D4B8_inst[8];
extern u8 D_8010D6B0_inst[8][5];
extern s8 D_8010D6D8_inst[4][3];
extern u8 D_8010D6E4_inst[8][5];
extern s8 D_8010D70C_inst[4][3];
extern s8 D_8010D718_inst[5];
extern s8 D_8010D71D_inst[4];
extern s8 D_8010D721_inst[1];
extern s8 D_8010D724_inst[8];
extern u16 D_800A11D0_main[5];
extern u16 D_800A11DC_main[5];

extern void (*D_8010DDE4_inst)(omObjData *);

s16 func_8000B0D4_main(s32, u16);

s32 BoardGetTurnTier(s32);
s32 BoardPlayerRankCalc(s32);

s32 func_80106418_inst(Vec *, Vec *, Vec *, Vec *, s32);
void func_80107E98_inst(void);
s32 func_80107E20_inst(void);
void func_8010B0FC_inst(void);
s32 func_8010B118_inst(void);
void func_80107BE4_inst(void);
u16 func_8010CA74_inst(u16, s16);
void func_8010CFF4_inst(void);
void func_80105D9C_inst(omObjData *); /* extern */
void func_801061EC_inst(void);        /* extern */
void func_80106310_inst(omObjData *); /* extern */
void func_801063F4_inst(void);
void func_80106388_inst(void);         /* extern */
void func_8010674C_inst(omObjData *);  /* extern */
void func_801067CC_inst(void);         /* extern */
void func_80106850_inst(Vec *, Vec *); /* extern */
void func_80106898_inst(void);         /* extern */
void func_80106EB4_inst(void);         /* extern */
void func_80107308_inst(void);         /* extern */
void func_80107938_inst(omObjData *);
void func_8010815C_inst(omObjData *);
void func_80107EE0_inst(void);
void func_80108AF0_inst(s16, void *, void *, void *);
void func_80107470_inst(void); /* extern */
void func_801079CC_inst(omObjData *);
s32 func_8010B10C_inst(void);
void func_80107E18_inst(omObjData *);
void func_80107F98_inst(omObjData *);
void func_8010B124_inst(void);
void func_80107A24_inst(omObjData *); /* extern */
void func_80107BF8_inst(omObjData *); /* extern */
void func_80108350_inst(void);        /* extern */
void func_80108808_inst(omObjData *);
void func_80108A18_inst(s16, s16, s16);
void func_80108870_inst(omObjData *);
void func_80108954_inst(omObjData *);
void func_80108A10_inst(omObjData *);
void func_8010C848_inst(void);
void func_8010C8D0_inst(void);
void func_801094B0_inst(void); /* extern */
void func_801098D8_inst(omObjData *);
void func_801099C0_inst(omObjData *);
void func_80109A84_inst(omObjData *);
void func_8010986C_inst(omObjData *); /* extern */
void func_80109A90_inst(void);        /* extern */
void func_8010A1D0_inst(void);        /* extern */
void func_8010B990_inst(void);        /* extern */
HmfSkeletonNode *func_8001D33C_main(s16, char *);
void func_80033910_main(HmfData *);
void func_80033970_main(HmfData *);
void func_8000BC48_main(u16, u16); /* extern */

void func_801059A0_inst(void) {
    void (*procFunc)(void) = NULL;
    s16 var_a1 = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_8010D400_inst[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    D_8010D40B_inst = GwSystem.minigame_index - 1;
    D_8010D40A_inst = D_800A6D44_main[D_8010D40B_inst].minigameType;

    if (_CheckFlag(0xF) != 0) {
        D_8010D407_inst = 1;
        D_8010D408_inst = 1;
    } else {
        D_8010D407_inst = 0;
        if ((GWMgUnlockCheck(D_8010D40B_inst)) != 0) {
            D_8010D408_inst = 1;
        }
    }

    GWMgUnlockSet(-1);
    _ClearFlag(0xF);
    func_80106EB4_inst();
    func_80106898_inst();
    func_80107308_inst();

    if ((GwSystem.show_minigame_explanations == 1) || (D_8010D40A_inst == 6)) {
        func_801061EC_inst();
        return;
    }

    Hu3DAnimInit(1);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 15.0f, 500.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010674C_inst), 0xA0U);
    func_800142A0_main(0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    omAddPrcObj(func_80107470_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B990_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010A1D0_inst, 0x1001, 0x1000, 0);

    switch (D_8010D40A_inst) {
        case 5:
            procFunc = func_801094B0_inst;
            D_8010D411_inst = 1;
            break;
        case 4:
            if (omovlhisidx <= 0) {
                break;
            }
            if (GwSystem.playMode & 2) {
                procFunc = func_80108350_inst;
                D_8010D411_inst = 0;
                break;
            }
        case 3:
            procFunc = func_80109A90_inst;
            D_8010D411_inst = 2;
            break;
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
        default:
            procFunc = func_80108350_inst;
            D_8010D411_inst = 0;
            break;
    }

    omAddPrcObj(procFunc, 0x1001, 0x800, 0);
    omAddObj(0, 0, 0, -1, func_80105D9C_inst);
    omAddObj(0, 0, 0, -1, func_80106310_inst);
    func_80106388_inst();
    func_80106850_inst(&D_8010D444_inst[2], &D_8010D474_inst[2]);
    func_801067CC_inst();
    WipeCreateIn(0xFF, 0x10);
}

void func_80105D9C_inst(omObjData *object) {
    s32 i;

    switch (D_8010D43C_inst) {
        case 0:
            HuAudSeqPlay(0x10);
            func_801067CC_inst();
            D_8010DC00_inst = 0;
            D_8010D405_inst = 0;
            if (D_8010D408_inst == 0) {
                D_8010D43C_inst++;
            } else {
                D_8010D418_inst.x = D_8010D444_inst[2].x;
                D_8010D418_inst.y = D_8010D444_inst[2].y;
                D_8010D418_inst.z = D_8010D444_inst[2].z;
                D_8010D424_inst.x = D_8010D474_inst[2].x;
                D_8010D424_inst.y = D_8010D474_inst[2].y;
                D_8010D424_inst.z = D_8010D474_inst[2].z;
                D_8010D430_inst.x = 0.0f;
                D_8010D430_inst.y = 1.0f;
                D_8010D430_inst.z = -0.000001f;
                D_8010D43C_inst = 6;
            }
            break;
        case 1:
            D_8010DC00_inst++;
            if (D_8010DC00_inst >= 21) {
                func_80107E98_inst();
                D_8010D43C_inst += 2;
            }
            break;
        case 2:
            if (func_80106418_inst(&D_8010D444_inst[0], &D_8010D444_inst[1], &D_8010D474_inst[0], &D_8010D474_inst[1], 5)) {
                func_80107E98_inst();
                D_8010D43C_inst++;
            }
            break;
        case 3:
            if (func_80107E20_inst()) {
                func_8010B0FC_inst();
                D_8010D43C_inst++;
            }
            break;
        case 4:
            if ((s8)func_8010B118_inst()) {
                D_8010D43C_inst++;
            }
            break;
        case 5:
            if (func_80106418_inst(&D_8010D444_inst[1], &D_8010D444_inst[2], &D_8010D474_inst[1], &D_8010D474_inst[2], 7)) {
                func_80107BE4_inst();
                D_8010D43C_inst++;
            }
            break;
        case 6:
            D_8010DC00_inst = 60;
            D_8010D43C_inst++;
            break;
        case 7:
            if (D_8010D440_inst == 1) {
                D_8010DC00_inst--;
                if (func_8010CA74_inst(0x1000, D_8010DC02_inst) || D_8010D406_inst == 1) {
                    D_8010DC00_inst = 0;
                    switch (D_8010D40A_inst) {
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            if (!(GwPlayer[D_8010D400_inst[0]].stat & 1)) {
                                omVibrate(D_8010D400_inst[0], 10, 0, 10);
                            }
                            break;
                        case 4:
                            for (i = 0; i < 2; i++) {
                                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                                    omVibrate(D_8010D400_inst[i], 10, 0, 10);
                                }
                            }
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        default:
                            for (i = 0; i < 4; i++) {
                                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                                    omVibrate(D_8010D400_inst[i], 10, 0, 10);
                                }
                            }
                            break;
                    }
                    func_8010CFF4_inst();
                    D_8010D409_inst = 1;
                    D_8010D43C_inst++;
                }
            }
            break;
        case 8:
            D_8010DC00_inst++;
            if (D_8010DC00_inst >= 15) {
                D_8010D404_inst = 1;
                D_8010D43C_inst++;
            }
            break;
        case 9:
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(30);
            HuAudFXPlay(0x154);
            D_8010D43C_inst++;
            break;
        case 10:
            if (func_80106418_inst(&D_8010D444_inst[2], &D_8010D444_inst[3], &D_8010D474_inst[2], &D_8010D474_inst[3], 25) && !WipeStatGet()) {
                func_801063F4_inst();
                func_801061EC_inst();
            }
            break;
    }
}

void func_801061EC_inst(void) {
    s32 unused[6]; // Retain the original stack frame.

    omOvlCallEx(D_800A6D40_main[D_8010D40B_inst].overlay, 0, 0x14);
    if (D_8010D5B1_inst == 1) {
        _SetFlag(0xF);
        return;
    }
    if (_CheckFlag(0xD) != 0) {
        goto pop_history;
    }
    switch (D_8010D40A_inst) {
        case 6:
            omOvlHisChg(1, 0x72, 0, 0x14);
            return;
        case 4:
            if (GwSystem.playMode & 2) {
                omOvlHisChg(1, 0x73, 0, 0x4010);
                return;
            }
            goto pop_history;
        case 3:
            omOvlHisChg(1, 0x74, 0, 0x12);
            return;
        case 5:
        case 7:
        case 8:
        pop_history:
            if (omovlhisidx > 0) {
                omovlhisidx--;
            }
            return;
        default:
            omOvlHisChg(1, 0x71, 0, 0x12);
            return;
    }
}

void func_80106310_inst(omObjData *object) {
    if (D_800D530C_main == 1) {
        if (D_8010D4A8_inst == 0) {
            WipeCreateOut(0, 20);
            D_8010D4A8_inst = 1;
        } else if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_801063F4_inst();
            omOvlReturnEx(1);
        }
    }
}

void func_80106388_inst(void) {
    u16 espriteSlot;

    espriteSlot = InitEspriteSlot(func_8000B838_main(D_8010D658_inst[D_8010D40A_inst]), 0, 0);
    func_8000BBD4_main(espriteSlot, 0xA0, 0x78);
    func_8000BC48_main(espriteSlot, 0x4000);
}

void func_801063F4_inst(void) {
    func_80037258_main();
    func_8005F524_main();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D658_inst);

s32 func_80106418_inst(Vec *startPosition, Vec *endPosition, Vec *startTarget, Vec *endTarget, s32 duration) {
    s32 done;

    D_8010D418_inst.x = (endPosition->x - startPosition->x) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startPosition->x;
    D_8010D418_inst.y = (endPosition->y - startPosition->y) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startPosition->y;
    D_8010D418_inst.z = (endPosition->z - startPosition->z) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startPosition->z;
    D_8010D424_inst.x = (endTarget->x - startTarget->x) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startTarget->x;
    D_8010D424_inst.y = (endTarget->y - startTarget->y) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startTarget->y;
    D_8010D424_inst.z = (endTarget->z - startTarget->z) * sindf(D_8010D4AC_inst * (90.0f / duration)) + startTarget->z;
    D_8010D430_inst.x = 0.0f;
    D_8010D430_inst.y = 1.0f;
    D_8010D430_inst.z = -0.000001f;
    D_8010D4AC_inst++;
    done = 0;
    if (D_8010D4AC_inst > duration) {
        D_8010D4AC_inst = 0;
        done = 1;
    }
    return done;
}

void func_8010674C_inst(omObjData *object) {
    D_800CE17C_main[0] = D_8010D418_inst.x;
    D_800CE17C_main[1] = D_8010D418_inst.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8010D418_inst, &D_8010D424_inst, &D_8010D430_inst);
    Hu3DCamUpdateMtx(0);
}

void func_801067CC_inst(void) {
    D_8010D418_inst.x = D_8010D444_inst[1].x;
    D_8010D418_inst.y = D_8010D444_inst[1].y;
    D_8010D418_inst.z = D_8010D444_inst[1].z;
    D_8010D424_inst.x = D_8010D474_inst[1].x;
    D_8010D424_inst.y = D_8010D474_inst[1].y;
    D_8010D424_inst.z = D_8010D474_inst[1].z;
    D_8010D430_inst.x = 0.0f;
    D_8010D430_inst.y = 1.0f;
    D_8010D430_inst.z = -0.000001f;
}

void func_80106850_inst(Vec *arg0, Vec *arg1) {
    D_8010D414_inst = 90.0f - atan2df(arg0->y - arg1->y, arg0->z - arg1->z);
}

void func_80106898_inst(void) {
    u8 weights[8];
    s8 selected[8];
    s8 i;
    s8 j;
    s8 tier;
    s8 rank;
    s8 total;
    s8 sum;
    s8 found;
    u8 random;
    u16 start;
    u8 *choices;
    s8 column;

    if (D_8010D40A_inst == 5) {
        if (_CheckFlag(0x1C)) {
            start = (u8)(rand8() & 3);
            if (rand8() & 1) {
                for (i = 0; i < 5; i++) {
                    D_8010D40C_inst[i] = D_8010D4B0_inst[i + start];
                }
            } else {
                for (i = 0; i < 5; i++) {
                    D_8010D40C_inst[i] = D_8010D4B8_inst[i + start];
                }
            }
            for (i = 0; i < 5; i++) {
                D_800A11D0_main[i] = D_8010D40C_inst[i];
            }
        } else if (D_8010D407_inst == 0) {
            for (i = 0; i < 8; i++) {
                selected[i] = 0;
            }
            tier = BoardGetTurnTier(-1);
            rank = BoardPlayerRankCalc(D_8010D400_inst[0]);
            if ((u8)(rand8() % 3) == 0) {
                choices = D_8010D4B0_inst;
                column = D_8010D6D8_inst[rank][tier];
                for (i = 0; i < 8; i++) {
                    weights[i] = D_8010D6B0_inst[i][column];
                }
            } else {
                choices = D_8010D4B8_inst;
                column = D_8010D70C_inst[rank][tier];
                for (i = 0; i < 8; i++) {
                    weights[i] = D_8010D6E4_inst[i][column];
                }
            }
            total = 100;
            for (j = 0; j < 5; j++) {
                random = rand8() % (total + 1);
                sum = 0;
                for (i = 0; i < 8; i++) {
                    if (selected[i] == 0) {
                        sum += weights[i];
                        if (sum >= random) {
                            selected[i] = 1;
                            total -= weights[i];
                            D_8010D40C_inst[j] = choices[i];
                            break;
                        }
                    }
                }
            }
            for (i = 0; i < 5; i++) {
                D_800A11D0_main[i] = D_8010D40C_inst[i];
            }
            column = D_8010D724_inst[GwPlayer[D_8010D400_inst[0]].chr];
            found = -1;
            for (i = 0; i < 5; i++) {
                if (column == D_800A11D0_main[i]) {
                    found = i;
                    break;
                }
            }
            if (found >= 0) {
                for (i = 0, j = 0; i < 5; i++) {
                    if (i == found) {
                        D_800A11DC_main[i] = D_8010D721_inst[0];
                    } else {
                        D_800A11DC_main[i] = D_8010D71D_inst[j];
                        j++;
                    }
                }
            } else {
                for (i = 0; i < 5; i++) {
                    D_800A11DC_main[i] = D_8010D718_inst[i];
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                D_8010D40C_inst[i] = D_800A11D0_main[i];
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6B0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6D8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D70C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D718_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D724_inst);

void func_80106EB4_inst(void) {
    s32 i;
    s32 first;
    s32 second;
    s32 humans;
    s32 temp;

    if (D_8010D407_inst == 1) {
        return;
    }
    switch ((s8)(D_8010D40B_inst - 6)) {
        case 12:
            if (rand8() & 1) {
                temp = D_8010D400_inst[0];
                D_8010D400_inst[0] = D_8010D400_inst[1];
                D_8010D400_inst[1] = temp;
            }
            if (rand8() & 1) {
                temp = D_8010D402_inst[0];
                D_8010D402_inst[0] = D_8010D402_inst[1];
                D_8010D402_inst[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[D_8010D400_inst[i]].group = i;
            }
            break;
        case 8:
            if (rand8() & 1) {
                temp = D_8010D400_inst[0];
                D_8010D400_inst[0] = D_8010D400_inst[1];
                D_8010D400_inst[1] = temp;
            }
            if (rand8() & 1) {
                temp = D_8010D402_inst[0];
                D_8010D402_inst[0] = D_8010D402_inst[1];
                D_8010D402_inst[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[D_8010D400_inst[i]].group = i;
            }
            break;
        case 7:
            for (i = 0, humans = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    humans++;
                }
            }
            if (humans == 1) {
                if (GwPlayer[D_8010D400_inst[0]].stat & 1) {
                    temp = D_8010D400_inst[0];
                    D_8010D400_inst[0] = D_8010D400_inst[1];
                    D_8010D400_inst[1] = temp;
                }
            } else if (rand8() & 1) {
                temp = D_8010D400_inst[0];
                D_8010D400_inst[0] = D_8010D400_inst[1];
                D_8010D400_inst[1] = temp;
            }
            for (i = 0, humans = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D402_inst[i]].stat & 1)) {
                    humans++;
                }
            }
            if (humans == 1) {
                if (GwPlayer[D_8010D402_inst[0]].stat & 1) {
                    temp = D_8010D402_inst[0];
                    D_8010D402_inst[0] = D_8010D402_inst[1];
                    D_8010D402_inst[1] = temp;
                }
            } else if (rand8() & 1) {
                temp = D_8010D402_inst[0];
                D_8010D402_inst[0] = D_8010D402_inst[1];
                D_8010D402_inst[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[D_8010D400_inst[i]].group = i;
            }
            break;
        case 0:
        case 1:
            for (i = 0; i < 5; i++) {
                first = (u8)(rand8() % 3);
                second = (u8)(rand8() % 3);
                if (second == first) {
                    second++;
                    second %= 3;
                }
                temp = D_8010D401_inst[first];
                D_8010D401_inst[first] = D_8010D401_inst[second];
                D_8010D401_inst[second] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[D_8010D400_inst[i]].group = i;
            }
            break;
    }
}

#ifdef NON_MATCHING
// Remaining difference: register allocation for the randomly chosen variant.
void func_80107308_inst(void) {
    u32 flags;
    s32 message = 0;
    s32 choose = 1;

    if (D_8010D407_inst == 1) {
        if ((D_8010D40B_inst == 29) | (D_8010D40B_inst == 55)) {
            message = D_800A6D40_main[D_8010D40B_inst].flags & 0x7FF;
            message += D_800CE20A_main * 2;
            choose = 0;
        }
    }
    if (choose == 1) {
        flags = D_800A6D40_main[D_8010D40B_inst].flags;
        message = flags & 0x7FF;
        if (flags & 0x4000) {
            if (D_8010D40B_inst != 70) {
                flags = (flags & 0x3800) >> 11;
                choose = rand8() % flags;
                D_800CE20A_main = choose;
            } else {
                choose = D_800CE20A_main;
            }
            message += choose * 2;
        } else if (D_8010D40B_inst == 71) {
            D_800CE20A_main = 2;
        } else if ((D_8010D40B_inst == 30) && (_CheckFlag(0x1C) != 0)) {
            D_800CE20A_main = 1;
        } else {
            D_800CE20A_main = 0;
        }
    }
    D_8010D4A4_inst = message;
}

#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107308_inst);
#endif

void func_80107470_inst(void) {
    s32 i;
    s32 j;
    omObjData *object;
    InstModelHooks *hooks;
    s32 group;
    HmfMotionNode *node;
    HmfData *data;
    HmfModelData_Unk64_Unk60_Struct *material;

    object = omAddObj(20, 10, 5, -1, NULL);
    D_8010DDD8_inst.object = object;
    object->model[0] = func_8000B0D4_main(D_8010D90C_inst[D_8010D40A_inst][0] | 0x170000, 0x16B9);
    object->model[1] = func_8000B0D4_main(0x170029, 0x1E89);
    object->model[2] = func_8000B0D4_main(D_8010D954_inst[D_8010D40A_inst], 0x1AB9);
    object->model[3] = func_8000B0D4_main(0x170028, 0x2B9);
    object->model[4] = func_8000B0D4_main(D_8010D910_inst[D_8010D40A_inst][0] | 0x170000, 0x239);
    func_8001C814_main(object->model[0], 2, 0);
    func_8001C814_main(object->model[1], 2, 0);
    func_8001C814_main(object->model[2], 2, 0);
    func_8001C814_main(object->model[3], 2, 0);
    func_8001C814_main(object->model[0], 1, 1);
    func_8001C814_main(object->model[1], 1, 1);
    func_8001C814_main(object->model[2], 1, 1);
    func_8001C814_main(object->model[3], 1, 1);
    func_8001C258_main(object->model[3], 4, 4);
    object->trans.x = 0;
    object->trans.y = 0;
    object->trans.z = 0;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[2], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[3], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    for (i = 0; i < 5; i++) {
        Hu3DModelScaleSet(object->model[i], 0.5f, 0.5f, 0.5f);
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(object->model[i + 1], 0.45f, 0.45f, 0.45f);
    }
    for (group = 0; group < 2; group++) {
        hooks = D_8010D4C0_inst[D_8010D40A_inst][group];
        for (j = 0; j < hooks->count; j++) {
            node = (HmfMotionNode *)func_8001D33C_main(object->model[0], hooks->nodes[j]);
            data = node->unk54;
            for (i = 0; i < node->unk00; i++) {
                if (node->unk50[i] >= 0) {
                    material = &data->unk60[node->unk50[i]];
                    material->unk24 = 1;
                }
            }
        }
    }
    D_8010DC10_inst = DataRead(D_8010D4A4_inst | 0x170000);
    D_8010DC18_inst = DataRead((D_8010D4A4_inst + 1) | 0x170000);
    D_8010DC14_inst = DataRead(0x170007);
    func_80108AF0_inst(object->model[1], D_8010DC18_inst, D_8010DC10_inst, D_8010DC14_inst);
    HmfModelData[object->model[1]].rot.x = -90.0f;
    omPrcSetDestructor(NULL, func_80107EE0_inst);
    if (D_8010D408_inst == 0) {
        D_8010DDD8_inst.update = func_80107938_inst;
    } else {
        D_8010DDD8_inst.update = func_8010815C_inst;
    }
    while (1) {
        D_8010DDD8_inst.update(object);
        HuPrcVSleep();
    }
}

void func_80107938_inst(omObjData *obj) {
    if ((s8)func_8010B10C_inst() == 1) {
        func_8001C814_main(obj->model[1], 1, 0);
        func_8001C814_main(obj->model[2], 1, 0);
        func_8001C258_main(obj->model[1], 4, 0);
        func_8001C258_main(obj->model[2], 4, 0);
        D_8010DDD8_inst.update = func_801079CC_inst;
    }
}

void func_801079CC_inst(omObjData *obj) {
    func_8001C814_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    D_8010DDD8_inst.update = func_80107A24_inst;
}

void func_80107A24_inst(omObjData *object) {
    f32 duration = D_800CCF58_main[HmfModelData[object->model[3]].unk02].unk02 - 25.0f;
    f32 angle = ((f32)D_8010D508_inst / duration) * D_8010D414_inst;
    s32 i;

    HmfModelData[object->model[1]].rot.x = angle - 90.0f;
    HmfModelData[object->model[2]].rot.x = angle;
    D_8010D50C_inst = (0.15f / duration) * D_8010D508_inst;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(object->model[i + 1], D_8010D50C_inst + 0.45f, D_8010D50C_inst + 0.45f,
                          D_8010D50C_inst + 0.45f);
    }
    D_8010D508_inst++;
    if ((f32)D_8010D508_inst == duration) {
        D_8010DDD8_inst.update = func_80107E18_inst;
        D_8010D50C_inst = 0;
        D_8010D508_inst = 0;
    }
}

void func_80107BE4_inst(void) {
    D_8010DDD8_inst.update = func_80107BF8_inst;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D770_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D784_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D78C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D794_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D79C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7A4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7AC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7B0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7C4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7CC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7D4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7DC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7EC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D800_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D808_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D810_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D818_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D820_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D828_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D83C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D844_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D84C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D854_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D85C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D864_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D870_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D878_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D880_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D888_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D890_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D89C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8B4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8BC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8C4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8CC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8D4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8DC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8EC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8F4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8FC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D904_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D90C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D910_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D954_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D978_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D980_inst);

void func_80107BF8_inst(omObjData *object) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    s32 j;
    f32 scale;

    nodes[0] = func_8001D33C_main(object->model[1], D_8010D978_inst);
    nodes[1] = func_8001D33C_main(object->model[2], D_8010D980_inst);
    if (nodes[0] == (HmfSkeletonNode *)-1 || nodes[1] == (HmfSkeletonNode *)-1) {
        osSyncPrintf("ERROR\n");
    }
    for (i = 0; i < 5; i++) {
        scale = sindf(i * 18.0f) * 0.5f;
        for (j = 0; j < 2; j++) {
            nodes[j]->unk4C[0][0] = scale + 1.0f;
            nodes[j]->unk4C[1][1] = scale + 1.0f;
            nodes[j]->unk4C[2][2] = scale + 1.0f;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 5; i++) {
        scale = cosdf(i * 18.0f) * 0.5f;
        if (scale < 0.3f) {
            scale = 0.3f;
        }
        for (j = 0; j < 2; j++) {
            nodes[j]->unk4C[0][0] = scale + 1.0f;
            nodes[j]->unk4C[1][1] = scale + 1.0f;
            nodes[j]->unk4C[2][2] = scale + 1.0f;
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 2; j++) {
        nodes[j]->unk4C[0][0] = 1.3f;
        nodes[j]->unk4C[1][1] = 1.3f;
        nodes[j]->unk4C[2][2] = 1.3f;
    }
    D_8010DDD8_inst.update = func_80107E18_inst;
}

void func_80107E18_inst(omObjData *object) {
}

s32 func_80107E20_inst(void) {
    s16 modelId = D_8010DDD8_inst.object->model[0];
    f32 unk40 = HmfModelData[modelId].unk40;
    return D_800CCF58_main[HmfModelData[modelId].unk02].unk02 <= unk40;
}

void func_80107E98_inst(void) {
    func_8001C6A8_main(D_8010DDD8_inst.object->model[0], 0);
    func_8001C814_main(D_8010DDD8_inst.object->model[0], 1, 0);
}

void func_80107EE0_inst(void) {
    DataClose(D_8010DC18_inst);
    DataClose(D_8010DC10_inst);
    DataClose(D_8010DC14_inst);
}

void func_80107F18_inst(void) {
    omObjData *object = D_8010DDD8_inst.object;

    func_8001C814_main(object->model[3], 1, 0);
    func_8001C814_main(object->model[3], 4, 4);
    func_8001C258_main(object->model[3], 4, 0);
    func_8010B124_inst();
    D_8010DDD8_inst.update = func_80107F98_inst;
}

void func_80107F98_inst(omObjData *obj) {
    f32 duration = D_800CCF58_main[HmfModelData[obj->model[3]].unk02].unk02 - 25.0f;
    f32 angle = D_8010D414_inst - ((f32)D_8010D510_inst / duration) * D_8010D414_inst;

    HmfModelData[obj->model[1]].rot.x = angle - 90.0f;
    HmfModelData[obj->model[2]].rot.x = angle;
    D_8010D510_inst++;
    if ((f32)D_8010D510_inst == duration) {
        D_8010DDD8_inst.update = func_80107BF8_inst;
        D_8010D510_inst = 0;
    }
}

s32 func_801080A8_inst(void) {
    f32 unk40 = HmfModelData[D_8010DDD8_inst.object->model[0]].unk40;
    return unk40 == 0.0f;
}

void func_801080FC_inst(void) {
    omObjData *obj = D_8010DDD8_inst.object;

    func_8001C814_main(obj->model[0], 1, 0);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C814_main(obj->model[0], 4, 4);
}

void func_8010815C_inst(omObjData *obj) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    f32 duration = D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02;

    func_8001C814_main(obj->model[0], 1, 0);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C6A8_main(obj->model[0], duration);
    HmfModelData[obj->model[1]].rot.x = D_8010D414_inst - 90.0f;
    HmfModelData[obj->model[2]].rot.x = D_8010D414_inst;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(obj->model[i + 1], 0.6f, 0.6f, 0.6f);
        func_8001C258_main(obj->model[i + 1], 4, 0);
    }
    nodes[0] = func_8001D33C_main(obj->model[1], D_8010D978_inst);
    nodes[1] = func_8001D33C_main(obj->model[2], D_8010D980_inst);
    for (i = 0; i < 2; i++) {
        nodes[i]->unk4C[0][0] = 1.3f;
        nodes[i]->unk4C[1][1] = 1.3f;
        nodes[i]->unk4C[2][2] = 1.3f;
    }
    D_8010DDD8_inst.update = func_80107E18_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108350_inst);

void func_8010872C_inst(omObjData *object) {
    object->trans.x = -86.0f;
    object->trans.y = -148.0f;
    object->trans.z = 253.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    func_8001C5B4_main(object->model[0], object->motion[1]);
    func_8001C814_main(object->model[0], 2, 2);
    func_80108A18_inst(object->model[0], D_8010DC28_inst, D_8010DC22_inst);
    D_8010DDE4_inst = func_80108808_inst;
}

void func_80108808_inst(omObjData *object) {
    D_8010D520_inst++;
    if (D_8010D520_inst >= 100) {
        func_8001C258_main(object->model[0], 4, 0);
        HuAudFXPlay(0x135);
        D_8010DDE4_inst = func_80108870_inst;
        D_8010D520_inst = 0;
        func_8010C8D0_inst();
    }
}

void func_80108870_inst(omObjData *object) {
    D_8010D524_inst++;
    object->trans.y = sindf(D_8010D524_inst * 5) * 200.0f + -148.0f;
    if (D_8010D524_inst >= 17) {
        object->trans.y = 52.0f;
        D_8010D524_inst = 0;
        func_8001C5B4_main(object->model[0], object->motion[2]);
        func_8001C814_main(object->model[0], 2, 0);
        HuPrcSleep(10);
        HuAudFXPlay(0x2A7);
        D_8010DDE4_inst = func_80108954_inst;
    }
}

void func_80108954_inst(omObjData *object) {
    s16 model = object->model[0];
    f32 time = HmfModelData[model].unk40;

    if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= time) {
        func_8001C5B4_main(model, object->motion[3]);
        func_8001C814_main(object->model[0], 2, 2);
        func_8010C848_inst();
        D_8010DDE4_inst = func_80108A10_inst;
    }
}

void func_80108A10_inst(omObjData *object) {
}

void func_80108A18_inst(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108AF0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_801094B0_inst);

void func_801097DC_inst(omObjData *object) {
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(*object->model, object->trans.x, object->trans.y, object->trans.z);
    D_8010DDEC_inst = func_8010986C_inst;
}

void func_8010986C_inst(omObjData *object) {
    D_8010D530_inst++;
    if (D_8010D530_inst >= 100) {
        D_8010DDEC_inst = func_801098D8_inst;
        D_8010D530_inst = 0;
        func_8001C258_main(object->model[0], 4, 0);
        HuAudFXPlay(0x298);
        func_8010C8D0_inst();
    }
}

void func_801098D8_inst(omObjData *object) {
    D_8010D534_inst++;
    object->trans.y = sindf(D_8010D534_inst * 5) * 200.0f + -171.0f;
    if (D_8010D534_inst == 13) {
        func_8001C5B4_main(object->model[0], object->motion[4]);
        func_8001C814_main(object->model[0], 2, 0);
    }
    if (D_8010D534_inst >= 17) {
        object->trans.y = 29.0f;
        D_8010D534_inst = 0;
        D_8010DDEC_inst = func_801099C0_inst;
    }
}

void func_801099C0_inst(omObjData *object) {
    s16 model = object->model[0];

    if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40) {
        func_8001C624_main(model, HmfModelData[object->motion[3]].unk02, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDEC_inst = func_80109A84_inst;
    }
}

void func_80109A84_inst(omObjData *object) {
}
