#include "common.h"
#include "../ovl_81_name/ovl_81.h"

#define OBJ_HMF_MODEL(obj) (HmfModelData[(obj)->omObj1->model[0]])

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

typedef struct BoardResultWork BoardResultWork;

typedef struct BoardResultSprFiles {
    s32 files[4];
} BoardResultSprFiles;

typedef struct BoardResultSprPositions {
    f32 pos[4][2];
} BoardResultSprPositions;

typedef struct BoardResultCharHeights {
    f32 heights[8];
} BoardResultCharHeights;

void func_80105BD8_boardresult(void);
void func_80109754_boardresult(void);
void func_8010BA98_boardresult(void);
void func_8010BAD8_boardresult(omObjData *);
void func_8010BBF0_boardresult(omObjData *);
void func_8010BC3C_boardresult(void);
void func_8010BC70_boardresult(void);
void func_8010BCA4_boardresult(void);
void func_8010BD04_boardresult(void);
void func_8010BDC4_boardresult(BoardResultWork *, f32, f32, f32);
void func_8010BDD4_boardresult(BoardResultWork *, f32, f32, f32);
void func_8010BDE4_boardresult(BoardResultWork *, s16);
BoardResultWork *func_8010BD30_boardresult(s32);
void func_8010BDBC_boardresult(BoardResultWork *, s32);
void func_8010BDEC_boardresult(BoardResultWork *, s32, s32);
s16 func_8010BE04_boardresult(BoardResultWork *);
void func_8010BE0C_boardresult(BoardResultWork *, s16);
Process *func_800EBF2C_name_81(Vec *from, Vec *to, Vec *dest, s32 time);
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800F3C98_name_81(s16, s32 *, s16);
void func_800F3EC0_name_81(s16);
void func_800EB164_name_81(s32, s32);
extern s32 D_8010E3E0_boardresult;
extern s32 D_80101200_shared_board[];
extern Vec D_8010E408_boardresult;
extern Vec D_8010E414_boardresult;
extern Vec D_8010E48C_boardresult;
extern Vec D_8010E4C8_boardresult;
extern Vec D_8010E4D4_boardresult[];
extern Vec D_8010E504_boardresult[];
extern Vec D_8010E534_boardresult[];
extern s32 D_8010E72C_boardresult[];
extern u32 D_8010E738_boardresult[];
extern s32 D_8010E73C_boardresult[];
extern s32 *D_8010E88C_boardresult[];
extern s32 *D_8010E8AC_boardresult[];
extern s32 D_8010E8CC_boardresult[5];
extern omObjData *D_8010E8EC_boardresult[4];
extern Vec *D_8010E8F8_boardresult[4];
extern s32 D_8010E908_boardresult;
extern f32 D_8010E90C_boardresult;
extern s32 D_8010E910_boardresult[6];
extern s32 D_8010E928_boardresult[];
extern BoardResultSprFiles D_8010E960_boardresult;
extern BoardResultSprPositions D_8010E970_boardresult;
extern BoardResultSprPositions D_8010E990_boardresult;
extern BoardResultCharHeights D_8010E9B0_boardresult;
extern u8 D_8010EAF0_boardresult;
extern Object *D_8010EAF4_boardresult;
extern GW_PLAYER *D_8010EB38_boardresult[4];
extern Object *D_8010EB48_boardresult[6];
extern Object *D_8010EB60_boardresult[4];
extern Object *D_8010EB70_boardresult;
extern s16 D_8010EB74_boardresult;
extern s16 D_8010EB76_boardresult;
extern s16 D_8010EB78_boardresult;
extern s16 D_8010EB7C_boardresult;
extern s16 D_8010EB7E_boardresult;
extern s32 D_8010EB88_boardresult[4];
extern s32 D_8010EB98_boardresult;
extern Object *D_8010EBA0_boardresult[4];
extern s16 D_8010EBB0_boardresult[4];
extern f32 D_8010EBB8_boardresult[6];
extern s16 kakusiMasuItemHis[10];

void func_801059A0_boardresult(void) {
    s32 i;
    u32 j;

    D_8010EAF0_boardresult = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_8010BCA4_boardresult();
    func_8010BC3C_boardresult();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    HuWinInit();
    omAddPrcObj(func_8010BA98_boardresult, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_8010BBF0_boardresult);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E72C_boardresult[0]; j++) {
            D_8010E88C_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E72C_boardresult[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E738_boardresult[0]; j++) {
            D_8010E8AC_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E738_boardresult[j + 1]);
        }
    }

    func_800EF3EC_name_81(4);
}

void func_80105B68_boardresult(omObjData *obj) {
    D_8010EAF4_boardresult->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80105BD8_boardresult(void) {
    s16 models[5];
    Vec targets[4];
    UnkBoard4 *groups[2];
    BoardResultSprFiles files = D_8010E960_boardresult;
    BoardResultSprPositions leftPos = D_8010E970_boardresult;
    BoardResultSprPositions rightPos = D_8010E990_boardresult;
    BoardResultCharHeights heights = D_8010E9B0_boardresult;
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

    for (i = 0; i < 4; i++) {
        D_8010EB38_boardresult[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_8010E88C_boardresult[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_8010EB38_boardresult[i]->player_obj->coords, &D_8010E4C8_boardresult);
        func_800D8944_name_81(D_8010EB38_boardresult[i]->player_obj);
        D_8010EB38_boardresult[i]->player_obj->flags |= 1;
        D_8010EB38_boardresult[i]->stat |= 4;
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

    D_8010EAF4_boardresult = func_800D8010_name_81(0x3B, 0);
    func_800461B4_main(D_8010EAF4_boardresult->omObj1->model[0]);
    func_800D8944_name_81(D_8010EAF4_boardresult);
    HuVecCopy3F(&D_8010EAF4_boardresult->coords, &D_8010E48C_boardresult);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105B68_boardresult);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;

    model = func_8000B108_main(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = func_8000B5BC_main(D_8010E8CC_boardresult[i]);
    }
    func_8001C954_main(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    func_8001F974_main(model, models[0]);
    func_8001C814_main(model, 2, 1);
    HuPrcSleep(10);

    for (i = 0; i < 4; i++) {
        func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&targets[i], 0.0f, 0.0f, 0.0f);
        func_800EB708_name_81(&targets[i], &D_8010EB38_boardresult[i]->player_obj->coords,
                              &D_8010EB38_boardresult[i]->player_obj->rot);
        targets[i].y += heights.heights[GwPlayer[i].chr];
        D_8010EB38_boardresult[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &targets[i],
                              &D_8010EB38_boardresult[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f,
                         (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 8) {
                func_8001C814_main(model, 0, 1);
            }
            if (j == 18) {
                func_8001C814_main(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                    case 2:
                        HuAudFXPlay(0x166);
                        break;
                    case 3:
                        HuAudFXPlay(0x167);
                        break;
                }
            }
        }
        func_800D8F0C_name_81(D_8010EB38_boardresult[i]->player_obj);
    }

    HuPrcSleep(10);
    HuAudFXPlay(0x168);
    func_8001C814_main(model, 3, 0);
    HuPrcSleep(47);
    func_8001C814_main(model, 0, 1);

    func_8002FD8C_main(D_8010EAF4_boardresult->omObj1->model[0],
                       HmfModelData[D_8010EAF4_boardresult->omObj1->model[0]].motId, "l_mayu", 76, 71);
    node = func_8001D33C_main(D_8010EAF4_boardresult->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x174);
    func_8002FD8C_main(D_8010EAF4_boardresult->omObj1->model[0],
                       HmfModelData[D_8010EAF4_boardresult->omObj1->model[0]].motId, "hige", 23, 70);
    node = func_8001D33C_main(D_8010EAF4_boardresult->omObj1->model[0], "hige");
    baseY = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + baseY;
        HuPrcVSleep();
    }
    node->basePos.y = baseY;

    func_8001C814_main(model, 3, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x169);
    for (i = 0; i < 4; i++) {
        PlayerFXPlay(0x286, i);
        func_800D90D0_name_81(D_8010EB38_boardresult[i]->player_obj, 1, 2);
        func_8001C814_main(D_8010EB38_boardresult[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&targets[i], &D_8010E4C8_boardresult);
        targets[i].y += 400.0f;
        func_8008A120_main(HmfModelData[D_8010EB38_boardresult[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        func_800D8E88_name_81(D_8010EB38_boardresult[i]->player_obj);
        func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords, &targets[i],
                              &D_8010EB38_boardresult[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; j--) {
            HuVecCopyXYZ(&D_8010EB38_boardresult[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f,
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
    func_80046558_main(D_8010EAF4_boardresult->omObj1->model[0]);
    func_800D8F3C_name_81(D_8010EAF4_boardresult);
    for (i = 0; i < 4; i++) {
        func_800F3EC0_name_81(i);
    }
}

s16 func_8010685C_boardresult(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_8010EB74_boardresult = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_8010EB76_boardresult = HmfAnimLink(HmfModelData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_80106968_boardresult(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_8010EB76_boardresult != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[D_8010EB76_boardresult];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_80106A38_boardresult(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_80106A80_boardresult(omObjData *obj) {
    func_8001E888_main(D_8010EB48_boardresult[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB48_boardresult[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB48_boardresult[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

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

void func_80106CA8_boardresult(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010EB60_boardresult[i]->rot.x = sindf(obj->rot.x);
        D_8010EB60_boardresult[i]->rot.z = cosdf(obj->rot.x);
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

void func_80106DA4_boardresult(omObjData *obj) {
    Object *target = D_8010EB60_boardresult[obj->work[1]];

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_80106F54_boardresult(omObjData *obj) {
    Object *target = D_8010EB70_boardresult;

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_801070F8_boardresult(void) {
    s32 index;
    Process *process;
    f32 angle;
    s32 offset;

    index = *(s32 *)HuPrcCurrentGet()->user_data;
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, func_800EBF2C_name_81(&D_8010EB38_boardresult[index]->player_obj->coords,
                                                  &D_8010E504_boardresult[index],
                                                  &D_8010EB38_boardresult[index]->player_obj->coords, 10));
    func_800D90D0_name_81(D_8010EB38_boardresult[index]->player_obj, 0, 0);

    for (angle = 90.0f; angle > 0.0f; angle -= 9.0f) {
        OBJ_MODEL_ROT_X(D_8010EB60_boardresult[3 - index], angle);
        HuPrcVSleep();
    }
    OBJ_MODEL_ROT_X(D_8010EB60_boardresult[3 - index], 0.0f);

    HuAudFXPlay(0x175);
    for (offset = 0, angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&D_8010EB38_boardresult[index]->player_obj->coords, D_8010E4D4_boardresult[index + 4].x,
                     D_8010E4D4_boardresult[index + 4].y - sindf(angle) * 100.0f + offset,
                     D_8010E4D4_boardresult[index + 4].z);
        HuVecCopyXYZ(&D_8010EB60_boardresult[3 - index]->coords, D_8010E4D4_boardresult[index + 4].x,
                     D_8010E4D4_boardresult[index + 4].y - sindf(angle) * 100.0f + offset,
                     D_8010E4D4_boardresult[index + 4].z);
        offset -= 10;
        HuPrcVSleep();
    }
    func_800D90D0_name_81(D_8010EB38_boardresult[index]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void func_80107598_boardresult(omObjData *obj) {
    f32 scale;
    u32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(D_8010EB88_boardresult[obj->work[0]], i, scale, scale);
    }

    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_801076A0_boardresult(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 coin;
    s32 digits[3];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    D_8010EB98_boardresult = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 4; i++) {
        D_8010EB88_boardresult[i] = HuSprGrpCreate(3, 5);
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
            HuSprGrpMemberSet(D_8010EB88_boardresult[i], j, D_8010EB98_boardresult, 0);
            func_800550F4_main(D_8010EB88_boardresult[i], j, 1);
            HuSprBankSet(D_8010EB88_boardresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010EB88_boardresult[i], j, 0x4790);
            HuSprAttrSet(D_8010EB88_boardresult[i], j, 0x1000);
            HuSprColorSet(D_8010EB88_boardresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(D_8010EB88_boardresult[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(D_8010EB88_boardresult[i], j, j * 14, 0);
            }
        }

        coin = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && coin < GwPlayer[j].coin) {
                coin = GwPlayer[j].coin;
            }
        }
        if (coin == GwPlayer[i].coin) {
            D_8010E8EC_boardresult[i] = omAddObj(0x1000, 0, 0, -1, func_80107598_boardresult);
            D_8010E8EC_boardresult[i]->work[0] = i;
            D_8010E8EC_boardresult[i]->work[1] = count;
            D_8010E8EC_boardresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107AB4_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprAnimKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

void func_80107B50_boardresult(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 star;
    s32 digits[2];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    D_8010EB98_boardresult = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 4; i++) {
        D_8010EB88_boardresult[i] = HuSprGrpCreate(2, 5);
        star = GwPlayer[i].star;
        count = 1;
        if (star >= 10) {
            count = 2;
            star %= 100;
            digits[0] = star / 10;
            star %= 10;
            digits[1] = star;
        } else {
            digits[0] = star;
        }

        for (j = 0; j < count; j++) {
            HuSprGrpMemberSet(D_8010EB88_boardresult[i], j, D_8010EB98_boardresult, 0);
            func_800550F4_main(D_8010EB88_boardresult[i], j, 1);
            HuSprBankSet(D_8010EB88_boardresult[i], j, digits[j], 0);
            HuSprPriSet(D_8010EB88_boardresult[i], j, 0x4790);
            HuSprAttrSet(D_8010EB88_boardresult[i], j, 0x1000);
            HuSprColorSet(D_8010EB88_boardresult[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(D_8010EB88_boardresult[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(D_8010EB88_boardresult[i], j, j * 14, 0);
            }
        }

        star = GwPlayer[i].star;
        for (j = 0; j < 4; j++) {
            if (j != i && star < GwPlayer[j].star) {
                star = GwPlayer[j].star;
            }
        }
        if (star == GwPlayer[i].star) {
            D_8010E8EC_boardresult[i] = omAddObj(0x1000, 0, 0, -1, func_80107598_boardresult);
            D_8010E8EC_boardresult[i]->work[0] = i;
            D_8010E8EC_boardresult[i]->work[1] = count;
            D_8010E8EC_boardresult[i]->rot.x = 0.0f;
        }
    }
}

void func_80107EE8_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprAnimKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

void func_80107F84_boardresult(u8 *flags) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        if (flags[i] != 0) {
            GwPlayer[i].star++;
            if (GwPlayer[i].star >= 100) {
                GwPlayer[i].star = 99;
            }
            func_800EFA8C_name_81(GwPlayer[i].player_obj, 1, 0);
            PlayerFXPlay(0x274, i);
            func_800138EC_main(D_8010EBB0_boardresult[i], 0, 1);
            for (j = 800; j >= 250; j -= 15) {
                f32 angle;

                func_800D8E88_name_81(D_8010EBA0_boardresult[i]);
                HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->scale, 0.75f, 0.75f, 0.75f);
                HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->coords, GwPlayer[i].player_obj->coords.x,
                             j + GwPlayer[i].player_obj->coords.y, GwPlayer[i].player_obj->coords.z - 50.0f);
                angle = j * 2 - 160;
                D_8010EBA0_boardresult[i]->rot.x = sindf(angle);
                D_8010EBA0_boardresult[i]->rot.z = cosdf(angle);
                func_8000CFA4_main(D_8010EBB0_boardresult[i], D_8010EBA0_boardresult[i]->coords.x,
                                   D_8010EBA0_boardresult[i]->coords.y - 20.0f, D_8010EBA0_boardresult[i]->coords.z);
                if (j == 650) {
                    HuAudFXPlay(0x176);
                }
                HuPrcVSleep();
            }
            func_800138EC_main(D_8010EBB0_boardresult[i], 1, 0);
        }
    }
    for (j = 0; j < 4; j++) {
        if (flags[j] != 0) {
            func_800EFABC_name_81(GwPlayer[j].player_obj);
        }
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x171);
    while (1) {
        for (i = 0; i < 4; i++) {
            D_8010EBA0_boardresult[i]->scale.x -= 0.1f;
            D_8010EBA0_boardresult[i]->scale.y -= 0.1f;
            D_8010EBA0_boardresult[i]->scale.z -= 0.1f;
            D_8010EBA0_boardresult[i]->coords.y -= 20.0f;
        }
        HuPrcVSleep();
        if (D_8010EBA0_boardresult[0]->scale.x <= 0.05f) {
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        func_800D8F0C_name_81(D_8010EBA0_boardresult[i]);
        HuVecCopyXYZ(&D_8010EBA0_boardresult[i]->scale, 0.75f, 0.75f, 0.75f);
    }
    for (j = 0; j < 4; j++) {
        if (flags[j] != 0) {
            func_800EFA8C_name_81(GwPlayer[j].player_obj, -1, 2);
        }
    }
}

void func_80108378_boardresult(void) {
    u8 winners[4];
    s32 chars[4];
    s32 i;
    s32 j;
    s32 k;
    s32 max;
    s32 gameCount;
    s32 coinCount;
    s32 eventCount;
    Vec *dests;

    for (i = 0; i < 4; i++) {
        D_8010EBA0_boardresult[i] = func_800D8010_name_81(0x1D, NULL);
        func_800D8F0C_name_81(D_8010EBA0_boardresult[i]);
        HuPrcVSleep();
        D_8010EBB0_boardresult[i] = func_8000CED8_main(0xB0004, 0x6A9);
        func_8000CD00_main(D_8010EBB0_boardresult[i], 10.0f, 20.0f, 8.0f);
        func_800138EC_main(D_8010EBB0_boardresult[i], 1, 0);
        HuPrcVSleep();
    }

    func_800EB164_name_81(-1, 0x1402);
    func_800EB164_name_81(-1, 0x1403);

    // Minigame star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].gamePrize) {
            max = GwPlayer[i].gamePrize;
        }
    }
    for (i = 0, gameCount = 0; i < 4; i++) {
        if (GwPlayer[i].gamePrize == max) {
            winners[i] = 1;
            gameCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = D_80101200_shared_board[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x1404, 0x1405, 0x1406, 0x1407 };

        if (gameCount == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[gameCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (gameCount == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (gameCount != 4) {
            dests = D_8010E8F8_boardresult[gameCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[k], &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[k++],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            func_80107F84_boardresult(winners);
            dests = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[i], &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[i],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (gameCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                                    &D_8010EB70_boardresult->coords, 10));
        }
    }

    func_800EB164_name_81(-1, 0x1408);
    // Coin star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].coinPrize) {
            max = GwPlayer[i].coinPrize;
        }
    }
    for (i = 0, coinCount = 0; i < 4; i++) {
        if (GwPlayer[i].coinPrize == max) {
            winners[i] = 1;
            coinCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = D_80101200_shared_board[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x1409, 0x140A, 0x140B, 0x140C };

        if (coinCount == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[coinCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (coinCount == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (coinCount != 4) {
            dests = D_8010E8F8_boardresult[coinCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[k], &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[k++],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            func_80107F84_boardresult(winners);
            dests = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[i], &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[i],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (coinCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                                    &D_8010EB70_boardresult->coords, 10));
        }
    }

    func_800EB164_name_81(-1, 0x140D);

    // Happening star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].stats.prize.hatenaPrize) {
            max = GwPlayer[i].stats.prize.hatenaPrize;
        }
    }
    for (i = 0, eventCount = 0; i < 4; i++) {
        if (GwPlayer[i].stats.prize.hatenaPrize == max) {
            winners[i] = 1;
            eventCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = D_80101200_shared_board[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x140E, 0x140F, 0x1410, 0x1411 };

        if (eventCount == 4) {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7C_boardresult);
        } else {
            func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB7E_boardresult);
        }
        func_800EB4DC_name_81(-1, msgs[eventCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        func_80106968_boardresult(D_8010EB70_boardresult->omObj1->model[0], D_8010EB78_boardresult);
        if (eventCount == 3) {
            func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E414_boardresult,
                                  &D_8010EB70_boardresult->coords, 10);
        }
        if (eventCount != 4) {
            dests = D_8010E8F8_boardresult[eventCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[k], &D_8010EB38_boardresult[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[k++],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            func_80107F84_boardresult(winners);
            dests = D_8010E534_boardresult;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB38_boardresult[i]->player_obj->coords,
                                                                            &dests[i], &D_8010EB38_boardresult[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB60_boardresult[3 - i]->coords, &dests[i],
                                                                            &D_8010EB60_boardresult[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (eventCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_8010EB70_boardresult->coords, &D_8010E408_boardresult,
                                                                    &D_8010EB70_boardresult->coords, 10));
        }
    }
    for (i = 0; i < 4; i++) {
        func_800D8F3C_name_81(D_8010EBA0_boardresult[i]);
        func_8000D044_main(D_8010EBB0_boardresult[i]);
    }
}

void func_80109128_boardresult(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            HuVecCopyXYZ(&D_8010EB48_boardresult[i]->coords, D_8010EB48_boardresult[i]->coords.x,
                         D_8010EB48_boardresult[i]->coords.y - (D_8010E90C_boardresult + D_8010EBB8_boardresult[i]),
                         D_8010EB48_boardresult[i]->coords.z);
            if (D_8010EB48_boardresult[i]->coords.y <= -1000.0f) {
                HuVecCopyXYZ(&D_8010EB48_boardresult[i]->coords, (func_800EFE20_name_81(300.0f) - 150) * 5.0f,
                             (func_800EFE20_name_81(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                D_8010EBB8_boardresult[i] =
                    func_800EFE20_name_81(D_8010E90C_boardresult / 2.0f) - D_8010E90C_boardresult / 4.0f;
                if (D_8010E908_boardresult) {
                    func_800D8F0C_name_81(D_8010EB48_boardresult[i]);
                    D_8010E910_boardresult[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

s32 func_80109320_boardresult(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010E910_boardresult[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void func_8010935C_boardresult(BoardResultWork *work, s32 index) {
    s32 x, y, z;

    x = func_800EFE20_name_81(256.0f) - 128;
    y = -func_800EFE20_name_81(256.0f) - 500;
    func_8010BDD4_boardresult(work, x, y, 0.0f);
    x = func_800EFE20_name_81(100.0f) + index * 500 - 550;
    y = func_800EFE20_name_81(64.0f) + 218;
    z = func_800EFE20_name_81(500.0f) - 500;
    func_8010BDC4_boardresult(work, x, y, z);
    func_8010BDE4_boardresult(work, func_800EFE20_name_81(60.0f) + 30);
}

void func_801094A8_boardresult(void) {
    BoardResultWork *works[3];
    s32 i;
    s32 count;

    for (i = 0; i < 3; i++) {
        works[i] = func_8010BD30_boardresult(D_8010E928_boardresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
        func_8010935C_boardresult(works[i], i);
        func_8010BDEC_boardresult(works[i], 2, 2);
    }

    while (1) {
        for (i = 0; i < 3; i++) {
            if ((func_8010BE04_boardresult(works[i]) & 1) && rand8() < 0x20) {
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        func_8010BDEC_boardresult(works[i], 2, 0);
                        count += func_8010BE04_boardresult(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                func_8010935C_boardresult(works[0], 0);
                func_8010BDC4_boardresult(works[0], 0.0f, 250.0f, 1500.0f);
                func_8010BDEC_boardresult(works[0], 1, 0);
                func_8010BDBC_boardresult(works[0], 0xB0046);
                func_8010BE0C_boardresult(works[0], 120);
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        func_8010BDEC_boardresult(works[i], 2, 0);
                        count += func_8010BE04_boardresult(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    func_8010BDEC_boardresult(works[i], 3, 2);
                    func_8010BDBC_boardresult(works[i], D_8010E928_boardresult[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                func_8010BE0C_boardresult(works[0], 60);
                func_8010935C_boardresult(works[0], 0);
                break;
            }
            func_8010935C_boardresult(works[i], i);
        }
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA90_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EAB0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109754_boardresult);

void func_8010BA98_boardresult(void) {
    func_80105BD8_boardresult();
    func_80109754_boardresult();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010BAD8_boardresult(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010BD04_boardresult();
        func_8010BC70_boardresult();
        if (D_8010E3E0_boardresult == 0) {
            HuWinAllKill();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0)) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x16);
            SLSaveBoard(1);
        } else {
            SLCommonSet(1);
        }
        omOvlGotoEx(0x55, 0, 0x4190);
    }
}

void func_8010BBF0_boardresult(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        func_80007EC0_main(40);
        obj->func = func_8010BAD8_boardresult;
    }
}

void func_8010BC3C_boardresult(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800EF840_name_81();
    func_800F4300_name_81();
}

void func_8010BC70_boardresult(void) {
    func_800F4314_name_81();
    func_800EF880_name_81();
    func_800F4030_name_81();
    func_800D7F0C_name_81();
}

void func_8010BCA4_boardresult(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

void func_8010BD04_boardresult(void) {
    MBDBackKill();
    MBDBackClose();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EADC_boardresult);
