#include "common_duel.h"
#include "game/overlays/duel/common/ovl_81.h"

#define OBJ_HMF_MODEL(obj) (Hu3DData[(obj)->omObj1->model[0]])

#define OBJ_MODEL_ROT_X(obj, angle)                                                                          \
    {                                                                                                        \
        sincosdf((angle), &OBJ_HMF_MODEL(obj).mtx[1][2], &OBJ_HMF_MODEL(obj).mtx[1][1]);                     \
        OBJ_HMF_MODEL(obj).mtx[2][1] = -OBJ_HMF_MODEL(obj).mtx[1][2];                                        \
        OBJ_HMF_MODEL(obj).mtx[2][2] = OBJ_HMF_MODEL(obj).mtx[1][1];                                         \
        OBJ_HMF_MODEL(obj).mtx[0][1] = OBJ_HMF_MODEL(obj).mtx[0][2] = OBJ_HMF_MODEL(obj).mtx[0][3] =         \
            OBJ_HMF_MODEL(obj).mtx[1][0] = OBJ_HMF_MODEL(obj).mtx[1][3] = OBJ_HMF_MODEL(obj).mtx[2][0] =     \
                OBJ_HMF_MODEL(obj).mtx[2][3] = OBJ_HMF_MODEL(obj).mtx[3][0] = OBJ_HMF_MODEL(obj).mtx[3][1] = \
                    OBJ_HMF_MODEL(obj).mtx[3][2] = 0.0f;                                                     \
        OBJ_HMF_MODEL(obj).mtx[0][0] = OBJ_HMF_MODEL(obj).mtx[3][3] = 1.0f;                                  \
    }

typedef struct DuelResultWork DuelResultWork;

typedef struct DuelResultSprFiles {
    s32 files[4];
} DuelResultSprFiles;

typedef struct DuelResultSprPositions {
    f32 pos[4][2];
} DuelResultSprPositions;

typedef struct DuelResultCharMotions {
    s32 motions[8];
} DuelResultCharMotions;

typedef struct DuelResultCharActors {
    s32 ids[8];
} DuelResultCharActors;

typedef struct DuelResultCharHeights {
    f32 heights[8];
} DuelResultCharHeights;

extern const DuelResultCharMotions D_8010D7F0_duelresult;
extern const DuelResultCharMotions D_8010D810_duelresult;
extern const DuelResultCharActors D_8010D83C_duelresult;
extern s16 kakusiMasuItemHis[10];
extern s32 mbKSuitObj[];

void func_80105BD0_duelresult(void);
DuelResultWork *func_8010ABE0_duelresult(s32);
void func_8010AC6C_duelresult(DuelResultWork *, s32);
void func_8010AC9C_duelresult(DuelResultWork *, s32, s32);
s16 func_8010ACB4_duelresult(DuelResultWork *);
void func_8010ACBC_duelresult(DuelResultWork *, s16);
void func_8010AC74_duelresult(DuelResultWork *, f32, f32, f32);
void func_8010AC84_duelresult(DuelResultWork *, f32, f32, f32);
void func_8010AC94_duelresult(DuelResultWork *, s16);
void func_8010856C_duelresult(void);
void func_8010A938_duelresult(void);
void func_8010A978_duelresult(omObjData *);
void func_8010AA9C_duelresult(omObjData *);
void func_8010AAE8_duelresult(void);
void func_8010AB50_duelresult(void);
void func_8010AB1C_duelresult(void);
void func_8010ABB0_duelresult(void);
void func_800F3C98_name_81(s16, s32 *, s16);
void func_800F3EC0_name_81(s16);
void func_800EB164_name_81(s32, s32);
void func_800EF9C4_name_81(Object *, s32, s32);
void func_800EFC28_name_81(void);

s32 D_8010D290_duelresult = 0;

Vec D_8010D294_duelresult = { -750.0f, 400.0f, 2000.0f };

Vec D_8010D2A0_duelresult = { 750.0f, 400.0f, 2000.0f };

Vec D_8010D2AC_duelresult = { -750.0f, 500.0f, 4000.0f };

Vec D_8010D2B8_duelresult = { -250.0f, 0.0f, 2500.0f };

Vec D_8010D2C4_duelresult = { -250.0f, -400.0f, 2500.0f }; /* Unreferenced. */

Vec D_8010D2D0_duelresult = { -500.0f, 400.0f, 3500.0f };

Vec D_8010D2DC_duelresult[3] = {
    { 750.0f, 250.0f, 4000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f }
};

Vec D_8010D300_duelresult[3] = {
    { 0.0f, -700.0f, 1500.0f },
    { 0.0f, -500.0f, 1000.0f },
    { 0.0f, -300.0f, 500.0f }
};

Vec D_8010D324_duelresult = { -200.0f, 400.0f, -150.0f };

Vec D_8010D330_duelresult = { 0.0f, 750.0f, 2500.0f };

Vec D_8010D33C_duelresult = { 0.0f, 250.0f, 2500.0f };

Vec D_8010D348_duelresult = { 0.0f, 400.0f, 2500.0f };

Vec D_8010D354_duelresult = { 0.0f, 1000.0f, 2500.0f };

Vec D_8010D360_duelresult = { 0.0f, 100.0f, 2500.0f };

Vec D_8010D36C_duelresult = { 500.0f, 50.0f, 500.0f };

Vec D_8010D378_duelresult[16] = {
    { -150.0f, 750.0f, 2000.0f },
    { 150.0f, 750.0f, 2000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f },
    { -150.0f, 100.0f, 2000.0f },
    { 150.0f, 100.0f, 2000.0f },
    { -150.0f, 0.0f, 2000.0f },
    { 150.0f, 0.0f, 2000.0f },
    { -150.0f, -500.0f, 2000.0f },
    { 150.0f, -500.0f, 2000.0f },
    { -150.0f, 800.0f, 2000.0f },
    { 150.0f, 800.0f, 2000.0f },
    { -150.0f, 150.0f, 2000.0f },
    { 150.0f, 150.0f, 2000.0f },
    { -150.0f, 350.0f, 2000.0f },
    { 150.0f, 350.0f, 2000.0f }
};

Vec D_8010D438_duelresult[8] = {
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 240.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f }
};

Vec D_8010D498_duelresult[2] = {
    { -750.0f, 150.0f, 1500.0f },
    { 750.0f, 150.0f, 1500.0f }
};

Vec D_8010D4B0_duelresult[2] = {
    { -225.0f, 150.0f, 2500.0f },
    { 225.0f, 150.0f, 2500.0f }
};

s32 D_8010D4C8_duelresult[3] = { 2, 0x2001B, 0x20024 };

s32 D_8010D4D4_duelresult[7] = { 6, 0x2001F, 0x20030, 0x20034, 0x20039, 0x20029, 0x2008F };

s32 D_8010D4F0_duelresult[3] = { 2, 0, 0 };

s32 D_8010D4FC_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D518_duelresult[3] = { 2, 0, 0 };

s32 D_8010D524_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D540_duelresult[3] = { 2, 0, 0 };

s32 D_8010D54C_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D568_duelresult[3] = { 2, 0, 0 };

s32 D_8010D574_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D590_duelresult[3] = { 2, 0, 0 };

s32 D_8010D59C_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D5B8_duelresult[3] = { 2, 0, 0 };

s32 D_8010D5C4_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 D_8010D5E0_duelresult[3] = { 2, 0, 0 };

s32 D_8010D5EC_duelresult[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 *D_8010D608_duelresult[8] = { D_8010D4C8_duelresult, D_8010D4F0_duelresult, D_8010D518_duelresult, D_8010D540_duelresult, D_8010D568_duelresult, D_8010D590_duelresult, D_8010D5B8_duelresult, D_8010D5E0_duelresult };

s32 *D_8010D628_duelresult[8] = { D_8010D4D4_duelresult, D_8010D4FC_duelresult, D_8010D524_duelresult, D_8010D54C_duelresult, D_8010D574_duelresult, D_8010D59C_duelresult, D_8010D5C4_duelresult, D_8010D5EC_duelresult };

s32 D_8010D648_duelresult[5] = { 0x13015C, 0x13015D, 0x13015E, 0x13015F, 0x130160 };

s32 D_8010D65C_duelresult[3] = { 2, 0xA0077, 0xA0078 };

omObjData *D_8010D668_duelresult[4] = { NULL, NULL, NULL, NULL };

s32 D_8010D678_duelresult = 0;

f32 D_8010D67C_duelresult = 50.0f;

s32 D_8010D680_duelresult[6] = { 0, 0, 0, 0, 0, 0 };

s32 D_8010D698_duelresult[8] = { 0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045 };

const DuelResultSprFiles D_8010D6D0_duelresult = { { 0x1301C1, 0x1301C2, 0x1301C3, 0x1301C4 } };

const DuelResultSprPositions D_8010D6E0_duelresult = { { { 200.0f, 60.0f },
                                                         { 80.0f, 0.0f },
                                                         { 0.0f, 120.0f },
                                                         { 80.0f, 120.0f } } };

const DuelResultSprPositions D_8010D700_duelresult = { { { 120.0f, 60.0f },
                                                         { -80.0f, 0.0f },
                                                         { 0.0f, 120.0f },
                                                         { -80.0f, 120.0f } } };

const DuelResultCharHeights D_8010D720_duelresult = { { 120.0f, 120.0f, 180.0f, 160.0f, 160.0f, 190.0f, 120.0f, 180.0f } };

u8 D_8010D860_duelresult BSS;
Object *D_8010D864_duelresult BSS;
s16 D_8010D868_duelresult[4][8] BSS;
GW_PLAYER *D_8010D8A8_duelresult[2] BSS;
Object *D_8010D8B0_duelresult[6] BSS;
Object *D_8010D8C8_duelresult[2] BSS;
Object *D_8010D8D0_duelresult[2] BSS;
Object *D_8010D8D8_duelresult[2] BSS;
Object *D_8010D8E0_duelresult BSS;
s16 D_8010D8E4_duelresult BSS;
s16 D_8010D8E6_duelresult BSS;
s16 D_8010D8E8_duelresult[12] BSS;
s32 D_8010D900_duelresult[4] BSS;
s32 D_8010D910_duelresult BSS;
Object *D_8010D914_duelresult[2] BSS;
void *D_8010D91C_duelresult[2] BSS;
s32 D_8010D924_duelresult[3] BSS;
f32 D_8010D930_duelresult[8] BSS;

void func_801059A0_duelresult(void) {
    s32 i;
    u32 j;

    D_8010D860_duelresult = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_8010AB50_duelresult();
    func_8010AAE8_duelresult();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    HuWinInit();
    omAddPrcObj(func_8010A938_duelresult, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_8010AA9C_duelresult);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010D4C8_duelresult[0]; j++) {
            D_8010D608_duelresult[i][j + 1] = CharMotionDataNumGet(i, D_8010D4C8_duelresult[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010D4D4_duelresult[0]; j++) {
            D_8010D628_duelresult[i][j + 1] = CharMotionDataNumGet(i, D_8010D4D4_duelresult[j + 1]);
        }
    }
}

void func_80105B60_duelresult(omObjData *obj) {
    D_8010D864_duelresult->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80105BD0_duelresult(void) {
    s16 models[5];
    Vec targets[4];
    UnkBoard4 *groups[2];
    DuelResultSprFiles files = D_8010D6D0_duelresult;
    DuelResultSprPositions leftPos = D_8010D6E0_duelresult;
    DuelResultSprPositions rightPos = D_8010D700_duelresult;
    DuelResultCharHeights heights = D_8010D720_duelresult;
    omObjData *obj;
    HmfMotionNode *node;
    void *data;
    s16 model;
    f32 baseY;
    s32 i;
    s32 j;

    groups[0] = func_800F4528_name_81(4, 2);
    for (i = 0; i < 4; i++) {
        data = DataRead(files.files[i]);
        groups[0]->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(groups[0]->unk_0A, i, groups[0]->unk_0C[i], 0);
        HuSprPriSet(groups[0]->unk_0A, i, 1);
        HuSprAttrSet(groups[0]->unk_0A, i, 0);
        HuSprPosSet(groups[0]->unk_0A, i, leftPos.pos[i][0], leftPos.pos[i][1]);
        DataClose(data);
    }

    groups[1] = func_800F4528_name_81(4, 2);
    for (i = 0; i < 4; i++) {
        data = DataRead(files.files[i]);
        groups[1]->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(groups[1]->unk_0A, i, groups[0]->unk_0C[i], 0);
        HuSprPriSet(groups[1]->unk_0A, i, 1);
        HuSprAttrSet(groups[1]->unk_0A, i, 1);
        HuSprPosSet(groups[1]->unk_0A, i, rightPos.pos[i][0], rightPos.pos[i][1]);
        DataClose(data);
    }

    for (i = 0; i < 2; i++) {
        D_8010D8A8_duelresult[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_8010D608_duelresult[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D36C_duelresult);
        D_8010D8A8_duelresult[i]->player_obj->flags |= 1;
        D_8010D8A8_duelresult[i]->stat |= 4;
        MBDModelTempAllocFree(D_8010D8A8_duelresult[i]->player_obj);
    }

    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    MBDBackTPLvlSet(0);
    HuAudFXPlay(0x173);
    for (i = 0; i < 160; i += 3) {
        HuSprPosSet(groups[0]->unk_0A, 0, leftPos.pos[0][0] + i, leftPos.pos[0][1]);
        HuSprPosSet(groups[1]->unk_0A, 0, rightPos.pos[0][0] - i, rightPos.pos[0][1]);
        HuPrcVSleep();
    }
    func_800F4584_name_81(groups[0]);
    func_800F4584_name_81(groups[1]);
    HuPrcSleep(10);
    MBDBackTPLvlSet(255);

    D_8010D864_duelresult = func_800D8010_name_81(0x3B, 0);
    AuraCreate(D_8010D864_duelresult->omObj1->model[0]);
    MBDModelTempAllocFree(D_8010D864_duelresult);
    HuVecCopy3F(&D_8010D864_duelresult->coords, &D_8010D324_duelresult);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;

    model = Hu3DModelRead(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = Hu3DModelReadNum(D_8010D648_duelresult[i]);
    }
    Hu3DModelVtxBufMake(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    Hu3DMotionModelSetEx(model, models[1]);
    Hu3DMotionAttrSet(model, 2, 1);
    HuPrcSleep(10);

    for (i = 0; i < 2; i++) {
        MBDMotionSet(D_8010D8A8_duelresult[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&targets[i], 0.0f, 0.0f, 0.0f);
        MBDVecDirGet(&targets[i], &D_8010D8A8_duelresult[i]->player_obj->coords,
                     &D_8010D8A8_duelresult[i]->player_obj->rot);
        targets[i].y += heights.heights[GwPlayer[i].chr];
        D_8010D8A8_duelresult[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &targets[i],
                              &D_8010D8A8_duelresult[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f,
                         (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 18) {
                Hu3DMotionAttrSet(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                }
            }
        }
        MBDModelDispOff(D_8010D8A8_duelresult[i]->player_obj);
        HuPrcSleep(9);
    }

    HuAudFXPlay(0x168);
    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(52);
    Hu3DMotionAttrSet(model, 0, 1);

    Hu3DMotionNoMotSet(D_8010D864_duelresult->omObj1->model[0],
                       Hu3DData[D_8010D864_duelresult->omObj1->model[0]].motId, "l_mayu", 76, 71);
    node = Hu3DModelObjPtrGet(D_8010D864_duelresult->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x174);
    Hu3DMotionNoMotSet(D_8010D864_duelresult->omObj1->model[0],
                       Hu3DData[D_8010D864_duelresult->omObj1->model[0]].motId, "hige", 23, 70);
    node = Hu3DModelObjPtrGet(D_8010D864_duelresult->omObj1->model[0], "hige");
    baseY = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + baseY;
        HuPrcVSleep();
    }
    node->basePos.y = baseY;

    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(3);
    HuAudFXPlay(0x169);
    for (i = 0; i < 2; i++) {
        PlayerFXPlay(0x286, i);
        MBDMotionSet(D_8010D8A8_duelresult[i]->player_obj, 1, 2);
        Hu3DMotionAttrSet(D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&targets[i], &D_8010D36C_duelresult);
        targets[i].y += 400.0f;
        func_8008A120_main(Hu3DData[D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        MBDModelDispOn(D_8010D8A8_duelresult[i]->player_obj);
        func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &targets[i],
                              &D_8010D8A8_duelresult[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; j--) {
            HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f,
                         (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f);
            HuPrcVSleep();
        }
    }

    WipeCreateOut(2, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    Hu3DModelKill(model);
    for (i = 0; i < 5; i++) {
        Hu3DModelKill(models[i]);
    }
    omDelObj(obj);
    AuraKill(D_8010D864_duelresult->omObj1->model[0]);
    MBDModelKill(D_8010D864_duelresult);
    for (i = 0; i < 2; i++) {
        func_800F3EC0_name_81(i);
    }
}

s16 func_80106800_duelresult(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    D_8010D8E4_duelresult = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    D_8010D8E6_duelresult = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_8010690C_duelresult(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_8010D8E6_duelresult != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[D_8010D8E6_duelresult];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_801069DC_duelresult(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void func_80106A24_duelresult(omObjData *obj) {
    Hu3DModelObjTexScroll(D_8010D8B0_duelresult[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(D_8010D8B0_duelresult[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(D_8010D8B0_duelresult[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

    obj->trans.x -= 4.0f;
    obj->trans.y -= 2.0f;
    obj->trans.z -= 1.0f;

    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.z >= 64.0f) {
        obj->trans.z -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
    if (obj->trans.z <= -64.0f) {
        obj->trans.z += 64.0f;
    }
}

void func_80106C4C_duelresult(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010D8C8_duelresult[i]->rot.x = sindf(obj->rot.x);
        D_8010D8C8_duelresult[i]->rot.z = cosdf(obj->rot.x);
    }

    if (obj->work[0] == 0) {
        obj->rot.x += 20.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
    } else if (obj->rot.x < 360.0f) {
        obj->rot.x += 20.0f;
    } else {
        obj->rot.x = 360.0f;
    }
}

void func_80106D48_duelresult(omObjData *obj) {
    Object *target = D_8010D8C8_duelresult[obj->work[1]];

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_80106EF8_duelresult(omObjData *obj) {
    Object *target = D_8010D8E0_duelresult;

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_8010709C_duelresult(void) {
    s32 index;
    Process *process;
    f32 angle;
    s32 offset;

    index = *(s32 *)HuPrcCurrentGet()->user_data;
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, func_800EBF2C_name_81(&D_8010D8A8_duelresult[index]->player_obj->coords,
                                                  &D_8010D378_duelresult[index + 2],
                                                  &D_8010D8A8_duelresult[index]->player_obj->coords, 10));
    MBDMotionSet(D_8010D8A8_duelresult[index]->player_obj, 0, 0);

    for (angle = 90.0f; angle > 0.0f; angle -= 9.0f) {
        OBJ_MODEL_ROT_X(D_8010D8C8_duelresult[1 - index], angle);
        HuPrcVSleep();
    }
    OBJ_MODEL_ROT_X(D_8010D8C8_duelresult[1 - index], 0.0f);

    HuAudFXPlay(0x175);
    for (offset = 0, angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&D_8010D8A8_duelresult[index]->player_obj->coords, D_8010D378_duelresult[index + 2].x,
                     D_8010D378_duelresult[index + 2].y - sindf(angle) * 100.0f + offset,
                     D_8010D378_duelresult[index + 2].z);
        HuVecCopyXYZ(&D_8010D8C8_duelresult[1 - index]->coords, D_8010D378_duelresult[index + 2].x,
                     D_8010D378_duelresult[index + 2].y - sindf(angle) * 100.0f + offset,
                     D_8010D378_duelresult[index + 2].z);
        offset -= 10;
        HuPrcVSleep();
    }
    MBDMotionSet(D_8010D8A8_duelresult[index]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void func_8010753C_duelresult(omObjData *obj) {
    f32 scale;
    u32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(D_8010D900_duelresult[obj->work[0]], i, scale, scale);
    }

    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80107644_duelresult(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 coin;
    s32 digits[3];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    D_8010D910_duelresult = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 2; i++) {
        D_8010D900_duelresult[i] = HuSprGrpCreate(3, 5);
        coin = GwPlayer[i].coin;
        if (coin >= 100) {
            count = 3;
            digits[0] = coin / 100;
            coin %= 100;
            digits[1] = coin / 10;
            coin %= 10;
            digits[2] = coin;
        } else if (coin >= 10) {
            count = 2;
            coin %= 100;
            digits[0] = coin / 10;
            coin %= 10;
            digits[1] = coin;
        } else {
            count = 1;
            digits[0] = coin;
        }

        for (j = 0; j < count; j++) {
            HuSprGrpMemberSet(D_8010D900_duelresult[i], j, D_8010D910_duelresult, 0);
            HuSprAnimModeSet(D_8010D900_duelresult[i], j, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(D_8010D900_duelresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010D900_duelresult[i], j, 0x4790);
            HuSprAttrSet(D_8010D900_duelresult[i], j, 0x1000);
            HuSprColorSet(D_8010D900_duelresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(D_8010D900_duelresult[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(D_8010D900_duelresult[i], j, j * 14, 0);
            }
        }

        coin = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && coin < GwPlayer[j].coin) {
                coin = GwPlayer[j].coin;
            }
        }
        if (coin == GwPlayer[i].coin) {
            D_8010D668_duelresult[i] = omAddObj(0x1000, 0, 0, -1, func_8010753C_duelresult);
            D_8010D668_duelresult[i]->work[0] = i;
            D_8010D668_duelresult[i]->work[1] = count;
            D_8010D668_duelresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107A58_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8010D668_duelresult[i] != NULL) {
            omDelObj(D_8010D668_duelresult[i]);
            D_8010D668_duelresult[i] = NULL;
        }
        HuSprGrpKill(D_8010D900_duelresult[i]);
    }
    HuSprAnimKill(D_8010D910_duelresult);
    HuPrcVSleep();
}

void func_80107AF4_duelresult(omObjData *obj) {
    f32 scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.2f + 0.5;

    HuVecCopyXYZ(&D_8010D914_duelresult[obj->work[0]]->scale, scale, scale, scale);
    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80107BC0_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010D914_duelresult[i] = MBDModelFileCreate(0x14000A, -1, 1.0f, 0.0f, NULL);
        if (GwPlayer[i].star == 0) {
            D_8010D91C_duelresult[i] = DataRead(0x130135);
            D_8010D924_duelresult[i] = (s16)Hu3DAnimCreate(
                Hu3DData[D_8010D914_duelresult[i]->omObj1->model[0]].hmf, D_8010D91C_duelresult[i], 0, "sitagocoro_DEF");
        } else {
            D_8010D91C_duelresult[i] = DataRead(0x140034);
            D_8010D924_duelresult[i] =
                (s16)Hu3DAnimCreate(Hu3DData[D_8010D914_duelresult[i]->omObj1->model[0]].hmf,
                                    D_8010D91C_duelresult[i], GwPlayer[i].star - 1, "sitagocoro_DEF");
        }
        Hu3DModelRemakeStatic(D_8010D914_duelresult[i]->omObj1->model[0]);
        HuVecCopy3F(&D_8010D914_duelresult[i]->coords, &GwPlayer[i].player_obj->coords);
        D_8010D914_duelresult[i]->velocity.x = 280.0f;
        HuVecCopyXYZ(&D_8010D914_duelresult[i]->scale, 0.5f, 0.5f, 0.5f);
    }

    if (GwPlayer[0].star > GwPlayer[1].star) {
        D_8010D668_duelresult[0] = omAddObj(0x1000, 0, 0, -1, func_80107AF4_duelresult);
        D_8010D668_duelresult[0]->work[0] = 0;
    } else if (GwPlayer[1].star > GwPlayer[0].star) {
        D_8010D668_duelresult[0] = omAddObj(0x1000, 0, 0, -1, func_80107AF4_duelresult);
        D_8010D668_duelresult[0]->work[0] = 1;
    }
}

void func_80107E7C_duelresult(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        Hu3DAnimModelKill(D_8010D924_duelresult[i]);
        DataClose(D_8010D91C_duelresult[i]);
        MBDModelKill(D_8010D914_duelresult[i]);
        if (D_8010D668_duelresult[i] != NULL) {
            omDelObj(D_8010D668_duelresult[i]);
            D_8010D668_duelresult[i] = NULL;
        }
    }
    HuPrcVSleep();
}

void func_80107F3C_duelresult(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->coords, D_8010D8B0_duelresult[i]->coords.x,
                         D_8010D8B0_duelresult[i]->coords.y + (D_8010D67C_duelresult + D_8010D930_duelresult[i]),
                         D_8010D8B0_duelresult[i]->coords.z);
            if (D_8010D8B0_duelresult[i]->coords.y >= 1000.0f) {
                HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->coords, (func_800EFE20_name_81(300.0f) - 150) * 5.0f,
                             -(func_800EFE20_name_81(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                D_8010D930_duelresult[i] =
                    func_800EFE20_name_81(D_8010D67C_duelresult / 2.0f) - D_8010D67C_duelresult / 4.0f;
                if (D_8010D678_duelresult) {
                    MBDModelDispOff(D_8010D8B0_duelresult[i]);
                    D_8010D680_duelresult[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

s32 func_80108138_duelresult(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010D680_duelresult[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void func_80108174_duelresult(DuelResultWork *work, s32 index) {
    s32 x, y, z;

    x = func_800EFE20_name_81(256.0f) - 128;
    y = -func_800EFE20_name_81(256.0f) - 500;
    func_8010AC84_duelresult(work, x, y, 0.0f);
    x = func_800EFE20_name_81(100.0f) + index * 500 - 550;
    y = func_800EFE20_name_81(64.0f) + 218;
    z = func_800EFE20_name_81(500.0f) - 500;
    func_8010AC74_duelresult(work, x, y, z);
    func_8010AC94_duelresult(work, func_800EFE20_name_81(60.0f) + 30);
}

void func_801082C0_duelresult(void) {
    DuelResultWork *works[3];
    s32 i;
    s32 count;

    for (i = 0; i < 3; i++) {
        works[i] = func_8010ABE0_duelresult(D_8010D698_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
        func_80108174_duelresult(works[i], i);
        func_8010AC9C_duelresult(works[i], 2, 2);
    }

    while (1) {
        for (i = 0; i < 3; i++) {
            if ((func_8010ACB4_duelresult(works[i]) & 1) && rand8() < 0x20) {
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        func_8010AC9C_duelresult(works[i], 2, 0);
                        count += func_8010ACB4_duelresult(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                func_80108174_duelresult(works[0], 0);
                func_8010AC74_duelresult(works[0], 0.0f, 250.0f, 1500.0f);
                func_8010AC9C_duelresult(works[0], 1, 0);
                func_8010AC6C_duelresult(works[0], 0xB0046);
                func_8010ACBC_duelresult(works[0], 120);
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        func_8010AC9C_duelresult(works[i], 2, 0);
                        count += func_8010ACB4_duelresult(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    func_8010AC9C_duelresult(works[i], 3, 2);
                    func_8010AC6C_duelresult(works[i], D_8010D698_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                func_8010ACBC_duelresult(works[0], 60);
                func_80108174_duelresult(works[0], 0);
                break;
            }
            func_80108174_duelresult(works[i], i);
        }
        HuPrcVSleep();
    }
}

const DuelResultCharMotions D_8010D7F0_duelresult = { { 0x200A4, 0x300A4, 0x700A4, 0x400A4, 0x500A4, 0x600A4, 0x800A4, 0x9001B } };

const DuelResultCharMotions D_8010D810_duelresult = { { 0x200AB, 0x300AB, 0x700AB, 0x400AB, 0x500AB, 0x600AB, 0x800AB, 0x90027 } };

void func_8010856C_duelresult(void) {
    s32 values[4];
    s32 rank[4];
    u8 state[8];
    s32 work[4];
    DuelResultCharHeights heights = D_8010D720_duelresult;
    DuelResultCharMotions motions;
    DuelResultCharMotions winMotions;
    DuelResultCharActors actors;
    omObjData *cloudObj;
    omObjData *rotObj;
    omObjData *swayObj;
    omObjData *obj;
    Object *actor;
    Object *star;
    Process *process;
    s16 effect;
    Process *fallProc;
    UnkBoard4 *group;
    void *data;
    s32 i;
    s32 j;
    s32 n;

    MBDBackKill();
    MBDBackLoad(1);
    func_800E8180_name_81(1000.0f, 10000.0f);
    for (i = 0; i < 2; i++) {
        D_8010D8A8_duelresult[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_8010D628_duelresult[GwPlayer[i].chr], 2);
        D_8010D8A8_duelresult[i]->player_obj->flags |= 1;
        D_8010D8A8_duelresult[i]->stat |= 4;
        motions = D_8010D7F0_duelresult;
        winMotions = D_8010D810_duelresult;
        D_8010D868_duelresult[i][0] =
            CharAnimCreate(D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                               motions.motions[GwPlayer[i].chr]);
        D_8010D868_duelresult[i][1] = Hu3DAnimDataRead(winMotions.motions[GwPlayer[i].chr]);
        CharAnimSet(D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                           D_8010D868_duelresult[i][0]);
        MBDModelTempAllocFree(D_8010D8A8_duelresult[i]->player_obj);
    }

    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_8010D8A8_duelresult[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
        HuVecCopy3F(&D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D378_duelresult[i]);
        func_800EB7BC_name_81(&D_8010D8A8_duelresult[i]->player_obj->rot);
        func_8008A120_main(Hu3DData[D_8010D8A8_duelresult[i]->player_obj->omObj1->model[0]].mtx, 0.0f);
    }

    for (i = 0; i < 3; i++) {
        D_8010D8B0_duelresult[i] = MBDModelFileCreate(0x1301C7, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(D_8010D8B0_duelresult[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(D_8010D8B0_duelresult[i]->omObj1->model[0], 255 - i * 64);
        HuVecCopy3F(&D_8010D8B0_duelresult[i]->coords, &D_8010D300_duelresult[i]);
        Hu3DModelVtxBufMake(D_8010D8B0_duelresult[i]->omObj1->model[0]);
        HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->scale, 1.0f - i * 0.2f, 1.0f - i * 0.2f, 1.0f - i * 0.2f);
        MBDModelTempAllocFree(D_8010D8B0_duelresult[i]);
    }
    cloudObj = omAddObj(0x1000, 0, 0, -1, func_80106A24_duelresult);

    for (i = 0; i < 2; i++) {
        D_8010D8C8_duelresult[i] = MBDModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, 0);
        HuVecCopy3F(&D_8010D8C8_duelresult[i]->coords, &D_8010D2DC_duelresult[0]);
        HuVecCopyXYZ(&D_8010D8C8_duelresult[i]->scale, 0.625f, 0.625f, 0.625f);
        OBJ_MODEL_ROT_X(D_8010D8C8_duelresult[i], 90.0f);
        MBDModelTempAllocFree(D_8010D8C8_duelresult[i]);
    }
    rotObj = omAddObj(0x1000, 0, 0, -1, func_80106C4C_duelresult);

    D_8010D8E0_duelresult = func_800D8010_name_81(0x3E, D_8010D65C_duelresult);
    D_8010D8E0_duelresult->flags |= 1;
    HuVecCopy3F(&D_8010D8E0_duelresult->coords, &D_8010D2AC_duelresult);
    D_8010D8E0_duelresult->rot.x = sindf(10.0f);
    D_8010D8E0_duelresult->rot.z = cosdf(10.0f);
    D_8010D8E8_duelresult[0] =
        func_80106800_duelresult(D_8010D8E0_duelresult->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_8010D8E8_duelresult[1] = func_801069DC_duelresult(0xA0081);
    D_8010D8E8_duelresult[2] = func_801069DC_duelresult(0xA0080);
    D_8010D8E8_duelresult[3] = func_801069DC_duelresult(0xA0084);
    D_8010D8E8_duelresult[4] = func_801069DC_duelresult(0xA0082);
    func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0], D_8010D8E8_duelresult[0]);

    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 10.0f, 30.0f, 8.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    HuAudSeqPlay(0xF);
    WipeCreateIn(2, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800EBF2C_name_81(&D_8010D8C8_duelresult[i]->coords, &D_8010D2DC_duelresult[2 - i],
                                             &D_8010D8C8_duelresult[i]->coords, 60));
        obj = omAddObj(0x3FFF, 0, 0, -1, func_80106D48_duelresult);
        obj->work[1] = i;
        obj->work[2] = 60;
        HuPrcSleep(10);
    }
    HuPrcSleep(40);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D8E0_duelresult->coords, &D_8010D2B8_duelresult,
                                                            &D_8010D8E0_duelresult->coords, 60));
    obj = omAddObj(0x3FFF, 0, 0, -1, func_80106EF8_duelresult);
    obj->work[2] = 60;
    MBDMotionSet(D_8010D8E0_duelresult, 0, 2);
    Hu3DParticleAttrSet(effect, 0, 1);
    i = 0;
    while (1) {
        EffectPosSet(effect, D_8010D8E0_duelresult->coords.x, D_8010D8E0_duelresult->coords.y + 100.0f,
                           D_8010D8E0_duelresult->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
        if (++i == 8) {
            HuAudFXPlay(0x172);
        }
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    rotObj->work[0] = 1;
    MBDMotionSet(D_8010D8E0_duelresult, 1, 0);
    HuPrcSleep(22);
    func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0], D_8010D8E8_duelresult[0]);
    func_800EF9C4_name_81(D_8010D8E0_duelresult, -1, 2);
    HuAudFXPlay(0x2A8);
    HuPrcSleep(10);
    for (i = 0; i < 2; i++) {
        process = omAddPrcObj(func_8010709C_duelresult, 0x1000, 0, 0x40);
        process->user_data = HuMemMemoryAlloc(process->heap, 0x20);
        *(s32 *)process->user_data = i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(10);
    }
    HuPrcChildWatch();

    func_800EB164_name_81(-1, 0x2001);
    HuAudFXPlay(0x16B);
    actor = func_800D8010_name_81(0x1D, NULL);
    HuVecCopy3F(&actor->coords, &D_8010D294_duelresult);
    HuPrcChildLink(HuPrcCurrentGet(), func_800D9668_name_81(actor, 0, 20.0f, 20));
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EBF2C_name_81(&actor->coords, &D_8010D2A0_duelresult, &actor->coords, 20));
    EffectParamSet(effect, 15.0f, 30.0f, 10.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    while (1) {
        EffectPosSet(effect, actor->coords.x, actor->coords.y, actor->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    MBDModelKill(actor);
    func_80107BC0_duelresult();
    func_800EFC28_name_81();
    func_80107E7C_duelresult();

    if (GwPlayer[0].star == GwPlayer[1].star) {
        func_800EB164_name_81(-1, 0x2003);
        HuAudFXPlay(0x16C);
        actor = func_800D8010_name_81(0x1A, NULL);
        HuVecCopy3F(&actor->coords, &D_8010D294_duelresult);
        HuPrcChildLink(HuPrcCurrentGet(), func_800D9668_name_81(actor, 0, 20.0f, 20));
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800EBF2C_name_81(&actor->coords, &D_8010D2A0_duelresult, &actor->coords, 20));
        EffectParamSet(effect, 15.0f, 30.0f, 10.0f);
        Hu3DParticleAttrSet(effect, 0, 1);
        while (1) {
            EffectPosSet(effect, actor->coords.x, actor->coords.y, actor->coords.z);
            if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
                break;
            }
            HuPrcVSleep();
        }
        Hu3DParticleAttrSet(effect, 1, 0);
        MBDModelKill(actor);
        func_80107644_duelresult();
        func_800EFC28_name_81();
        func_80107A58_duelresult();

        if (GwPlayer[0].coin == GwPlayer[1].coin) {
            // The duel is a draw
            func_800EB164_name_81(-1, 0x2004);
            HuPrcVSleep();
            for (i = 0; i < 2; i++) {
                MBDMotionSet(D_8010D8A8_duelresult[i]->player_obj, 3, 0);
            }
            HuAudFXPlay(0x2A9);
            func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0], D_8010D8E8_duelresult[4]);
            group = func_800F4528_name_81(1, 0);
            data = DataRead(0x130134);
            group->unk_0C[0] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(group->unk_0A, 0, group->unk_0C[0], 0);
            HuSprPriSet(group->unk_0A, 0, 1);
            HuSprAttrSet(group->unk_0A, 0, 0);
            HuSprPosSet(group->unk_0A, 0, 160, 60);

            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                    break;
                }
            }
            if (i != 2) {
                j = 0;
                n = 0;
                while (1) {
                    for (i = 0; i < 2; i++) {
                        if (!(GwPlayer[i].stat & PLAYER_IS_CPU) &&
                            (ContBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                            break;
                        }
                    }
                    if (i != 2) {
                        break;
                    }
                    if (++j % 256 == 0) {
                        n ^= 1;
                        if (n == 0) {
                            func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0],
                                                     D_8010D8E8_duelresult[4]);
                        } else {
                            func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0],
                                                     D_8010D8E8_duelresult[2]);
                        }
                    }
                    HuPrcVSleep();
                }
            } else {
                HuPrcSleep(30);
            }
            kakusiMasuItemHis[0] = 0;
            kakusiMasuItemHis[1] = 1;
            kakusiMasuItemHis[2] = -1;
            return;
        }
    }

    func_8010690C_duelresult(D_8010D8E0_duelresult->omObj1->model[0], D_8010D8E8_duelresult[1]);
    func_800EB164_name_81(-1, 0x2002);

    // Determine rankings
    for (j = 0; j < 2; j++) {
        values[j] = GwPlayer[j].star * 1000 + GwPlayer[j].coin;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0, n = 0; j < 2; j++) {
            if (i != j) {
                n += values[i] < values[j];
            }
        }
        rank[i] = n;
    }
    for (i = 0; i < 2; i++) {
        kakusiMasuItemHis[rank[i]] = i;
    }
    kakusiMasuItemHis[2] = 0;

    D_8010D864_duelresult = func_800D8010_name_81(0x3B, NULL);
    AuraCreate(D_8010D864_duelresult->omObj1->model[0]);
    HuVecCopy3F(&D_8010D864_duelresult->coords, &D_8010D330_duelresult);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D8E0_duelresult->coords, &D_8010D2D0_duelresult,
                                                            &D_8010D8E0_duelresult->coords, 20));
    HuAudFXPlay(0x16D);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D33C_duelresult,
                                                            &D_8010D864_duelresult->coords, 40));
    EffectParamSet(effect, 15.0f, 30.0f, 20.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    EffectRangeSet(effect, 300.0f);
    while (1) {
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
    swayObj->rot.y = 30.0f;
    swayObj->rot.z = 10.0f;
    HuAudFXPlay(0x159);
    func_800EB164_name_81(-1, 0x2005);

    // Fade out the clouds
    state[0] = 0xFF;
    state[1] = 0xBF;
    state[2] = 0x7F;
    for (i = 0; i < 255; i += 10) {
        for (j = 0; j < 3; j++) {
            work[j] = state[j] - i;
            if (work[j] < 0) {
                work[j] = 0;
            }
            Hu3DModelTPLvlSet(D_8010D8B0_duelresult[j]->omObj1->model[0], work[j]);
        }
        HuPrcVSleep();
    }
    omDelObj(cloudObj);
    for (i = 0; i < 3; i++) {
        MBDModelKill(D_8010D8B0_duelresult[i]);
    }
    HuPrcVSleep();

    for (i = 0; i < 6; i++) {
        D_8010D8B0_duelresult[i] = MBDModelFileCreate(0x1301C9, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(D_8010D8B0_duelresult[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(D_8010D8B0_duelresult[i]->omObj1->model[0], 255 - i * 32);
        HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->coords, 0.0f, 5000.0f, 0.0f);
        HuVecCopyXYZ(&D_8010D8B0_duelresult[i]->scale, 1.0f - i * 0.1f, 1.0f - i * 0.1f, 1.0f - i * 0.1f);
        MBDModelTempAllocFree(D_8010D8B0_duelresult[i]);
    }
    fallProc = omAddPrcObj(func_80107F3C_duelresult, 0x1000, 0, 0);
    star = MBDModelFileCreate(0x130148, -1, 1.0f, 0.0f, 0);
    HuVecCopyXYZ(&star->scale, 0.8f, 1.0f, 0.8f);
    MBDModelDispOff(star);
    HuAudFXPlay(0x16E);
    omDelObj(swayObj);
    for (i = 0; i < 2; i++) {
        func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D378_duelresult[i + 14],
                              &D_8010D8A8_duelresult[i]->player_obj->coords, 20);
        func_800EBF2C_name_81(&D_8010D8C8_duelresult[1 - i]->coords, &D_8010D378_duelresult[i + 14],
                              &D_8010D8C8_duelresult[1 - i]->coords, 20);
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D360_duelresult,
                                                            &D_8010D864_duelresult->coords, 2));
    while (1) {
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D33C_duelresult,
                                                            &D_8010D864_duelresult->coords, 18));
    HuPrcSleep(18);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       func_800EBF2C_name_81(&D_8010D8C8_duelresult[1 - i]->coords, &D_8010D378_duelresult[i + 8],
                                             &D_8010D8C8_duelresult[1 - i]->coords, 20));
    }
    HuPrcSleep(5);
    for (i = 0; i < 2; i++) {
        D_8010D8A8_duelresult[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        MBDMotionSet(D_8010D8A8_duelresult[i]->player_obj, 4, 2);
        PlayerFXPlay(0x286, i);
    }

    for (j = 0; j < 100; j++) {
        D_8010D67C_duelresult += 1.0f;
        if (j == 20) {
            for (i = 0; i < 2; i++) {
                func_800EBF2C_name_81(&D_8010D8A8_duelresult[i]->player_obj->coords, &D_8010D378_duelresult[i + 6],
                                      &D_8010D8A8_duelresult[i]->player_obj->coords, 10);
            }
            HuPrcChildLink(HuPrcCurrentGet(),
                           func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D348_duelresult,
                                                 &D_8010D864_duelresult->coords, 15));
        }
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        if (j == 40) {
            swayObj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
            swayObj->rot.y = 30.0f;
            swayObj->rot.z = 10.0f;
        }
        if (j >= 40) {
            swayObj->rot.y += 2.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);

    // Reveal the winner's star
    HuVecCopy3F(&star->coords, &D_8010D8C8_duelresult[1 - kakusiMasuItemHis[0]]->coords);
    MBDModelDispOn(star);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&star->coords,
                                                            &D_8010D378_duelresult[kakusiMasuItemHis[0] + 10],
                                                            &star->coords, 30));
    HuPrcSleep(2);
    func_800EBF2C_name_81(&D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords,
                          &D_8010D378_duelresult[kakusiMasuItemHis[0] + 10],
                          &D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords, 28);
    omDelObj(swayObj);
    func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D360_duelresult, &D_8010D864_duelresult->coords,
                          15);
    func_800EBF2C_name_81(&D_8010D8A8_duelresult[1 - kakusiMasuItemHis[0]]->player_obj->coords,
                          &D_8010D378_duelresult[15 - kakusiMasuItemHis[0]],
                          &D_8010D8A8_duelresult[1 - kakusiMasuItemHis[0]]->player_obj->coords, 15);
    for (i = 0; i < 15; i++) {
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
    swayObj->rot.y = 80.0f;
    swayObj->rot.z = 10.0f;
    for (i = 0; i < 5; i++) {
        D_8010D67C_duelresult -= 3.0f;
        HuPrcVSleep();
    }
    MBDMotionSet(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj, 0, 0);
    func_800EF9C4_name_81(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj, -1, 2);
    for (i = 0; i < 5; i++) {
        D_8010D67C_duelresult -= 3.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EBF2C_name_81(&D_8010D8A8_duelresult[1 - kakusiMasuItemHis[0]]->player_obj->coords,
                                         &D_8010D378_duelresult[9 - kakusiMasuItemHis[0]],
                                         &D_8010D8A8_duelresult[1 - kakusiMasuItemHis[0]]->player_obj->coords, 20));
    PlayerFXPlay(0x286, 1 - kakusiMasuItemHis[0]);
    omDelObj(swayObj);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D348_duelresult,
                                                            &D_8010D864_duelresult->coords, 45));
    D_8010D678_duelresult = 1;
    while (D_8010D67C_duelresult > 60.0f) {
        D_8010D67C_duelresult -= 3.0f;
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        HuPrcVSleep();
    }
    msmSeFadeOut(60);
    while (1) {
        EffectPosSet(effect, D_8010D864_duelresult->coords.x, D_8010D864_duelresult->coords.y,
                           D_8010D864_duelresult->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, func_80105B60_duelresult);
    swayObj->rot.y = 10.0f;
    swayObj->rot.z = 10.0f;
    HuPrcSleep(20);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&star->coords,
                                                            &D_8010D378_duelresult[kakusiMasuItemHis[0] + 6],
                                                            &star->coords, 60));
    func_800EBF2C_name_81(&D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords,
                          &D_8010D378_duelresult[kakusiMasuItemHis[0] + 6],
                          &D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords, 60);
    HuPrcChildWatch();

    func_800EB4DC_name_81(-1, 0x2006, mbKSuitObj[GwPlayer[kakusiMasuItemHis[0]].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    for (i = 0; i < 2; i++) {
        actors = D_8010D83C_duelresult;
        D_8010D8D0_duelresult[i] = MBDModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, 0);
        HuVecCopy3F(&D_8010D8D0_duelresult[i]->coords, &D_8010D498_duelresult[i]);
        HuVecCopyXYZ(&D_8010D8D0_duelresult[i]->scale, 0.625f, 0.625f, 0.625f);
        MBDModelTempAllocFree(D_8010D8D0_duelresult[i]);
        HuPrcVSleep();
        D_8010D8D8_duelresult[i] = func_800D8010_name_81(actors.ids[GwPlayer[kakusiMasuItemHis[0]].chr], NULL);
        HuVecCopy3F(&D_8010D8D8_duelresult[i]->coords, &D_8010D498_duelresult[i]);
        MBDModelTempAllocFree(D_8010D8D8_duelresult[i]);
        HuPrcVSleep();
        D_8010D8D8_duelresult[i]->velocity.x = 2.0f;
    }

    D_8010D678_duelresult = 1;
    for (i = 0; !func_80108138_duelresult(); i++) {
        D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        star->coords.y += 2.0f;
        if (i == 40) {
            Hu3DParticleAttrSet(effect, 1, 0);
            func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D354_duelresult,
                                  &D_8010D864_duelresult->coords, 30);
        }
        HuPrcVSleep();
    }
    for (; i < 60; i++) {
        D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        star->coords.y += 2.0f;
        if (i == 40) {
            Hu3DParticleAttrSet(effect, 1, 0);
            func_800EBF2C_name_81(&D_8010D864_duelresult->coords, &D_8010D354_duelresult,
                                  &D_8010D864_duelresult->coords, 30);
        }
        HuPrcVSleep();
    }

    func_800E8180_name_81(100.0f, 20000.0f);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EBF2C_name_81(&D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords,
                                         &D_8010D438_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->coords, 30));
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EBF2C_name_81(&star->coords, &D_8010D438_duelresult[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &star->coords, 30));
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        func_800EBF2C_name_81(&D_8010D8D8_duelresult[i]->coords, &D_8010D4B0_duelresult[i],
                              &D_8010D8D8_duelresult[i]->coords, 60);
        func_800EBF2C_name_81(&D_8010D8D0_duelresult[i]->coords, &D_8010D4B0_duelresult[i],
                              &D_8010D8D0_duelresult[i]->coords, 60);
    }
    for (i = 0; i < 2; i++) {
        if (i != kakusiMasuItemHis[0]) {
            func_800F3EC0_name_81(i);
            MBDModelKill(D_8010D8C8_duelresult[1 - i]);
        }
    }
    AuraKill(D_8010D864_duelresult->omObj1->model[0]);
    MBDModelKill(D_8010D864_duelresult);
    MBDModelKill(D_8010D8E0_duelresult);
    HuWinAllKill();
    D_8010D290_duelresult = 1;
    EffectStop(effect);
    omDelPrcObj(fallProc);
    for (i = 0; i < 6; i++) {
        MBDModelKill(D_8010D8B0_duelresult[i]);
    }
    HuPrcSleep(5);
    omAddPrcObj(func_801082C0_duelresult, 0x1000, 0, 0);
    HuPrcSleep(1);

    PlayerFXPlay(0x27D, kakusiMasuItemHis[0]);
    CharAnimSet(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj->omObj1->model[0], 2,
                       GwPlayer[kakusiMasuItemHis[0]].chr, D_8010D868_duelresult[kakusiMasuItemHis[0]][1]);
    MBDMotionSet(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj, 2, 0);
    func_800EFABC_name_81(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj);
    HuAudFXPlay(0x177);
    MBDMotionSet(D_8010D8A8_duelresult[kakusiMasuItemHis[0]]->player_obj, 5, 2);
    group = func_800F4528_name_81(1, 0);
    data = DataRead(0x1301C6);
    group->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(group->unk_0A, 0, group->unk_0C[0], 0);
    HuSprPriSet(group->unk_0A, 0, 1);
    HuSprAttrSet(group->unk_0A, 0, 0);
    HuSprPosSet(group->unk_0A, 0, 160, 184);
    HuPrcSleep(30);

    // Wait for a human player to press a button
    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            break;
        }
    }
    if (i != 2) {
        while (1) {
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU) &&
                    (ContBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON | START_BUTTON))) {
                    break;
                }
            }
            if (i != 2) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        HuPrcSleep(30);
    }
}

void func_8010A938_duelresult(void) {
    func_80105BD0_duelresult();
    func_8010856C_duelresult();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010A978_duelresult(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010ABB0_duelresult();
        func_8010AB1C_duelresult();
        if (D_8010D290_duelresult == 0) {
            HuWinAllKill();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            if (kakusiMasuItemHis[2] == 0) {
                GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
            }
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0)) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x17);
            SLSaveBoardStory(1);
        } else {
            SLCommonSet(1);
        }
        omOvlGotoEx(0x63, 0, 0x4190);
    }
}

void func_8010AA9C_duelresult(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(2, 20);
        msmSeFadeOut(40);
        obj->func = func_8010A978_duelresult;
    }
}

void func_8010AAE8_duelresult() {
    MBDModelInit();
    func_800F3F4C_name_81();
    func_800EF840_name_81();
    func_800F4300_name_81();
}

void func_8010AB1C_duelresult() {
    func_800F4314_name_81();
    func_800EF880_name_81();
    func_800F4030_name_81();
    MBDModelClose();
}

void func_8010AB50_duelresult(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

void func_8010ABB0_duelresult() {
    MBDBackKill();
    MBDBackClose();
}

const DuelResultCharActors D_8010D83C_duelresult = { { 37, 12, 9, 10, 38, 11, 44, 36 } };
