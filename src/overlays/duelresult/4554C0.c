#include "common_duel.h"
#include "../ovl_81_name/ovl_81.h"

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

extern s32 D_8010D290_duelresult;
extern Vec D_8010D378_duelresult[];
extern Vec D_8010D390_duelresult[];
extern s32 D_8010D4C8_duelresult[];
extern u32 D_8010D4D4_duelresult[];
extern s32 *D_8010D608_duelresult[];
extern s32 *D_8010D628_duelresult[];
extern omObjData *D_8010D668_duelresult[2];
extern s32 D_8010D678_duelresult;
extern f32 D_8010D67C_duelresult;
extern s32 D_8010D680_duelresult[6];
extern s32 D_8010D698_duelresult[];
extern u8 D_8010D860_duelresult;
extern Object *D_8010D864_duelresult;
extern GW_PLAYER *D_8010D8A8_duelresult[2];
extern Object *D_8010D8B0_duelresult[];
extern Object *D_8010D8C8_duelresult[2];
extern Object *D_8010D8E0_duelresult;
extern s16 D_8010D8E4_duelresult;
extern s16 D_8010D8E6_duelresult;
extern s32 D_8010D900_duelresult[2];
extern s32 D_8010D910_duelresult;
extern f32 D_8010D930_duelresult[6];
extern Object *D_8010D914_duelresult[2];
extern void *D_8010D91C_duelresult[2];
extern s32 D_8010D924_duelresult[2];
extern s16 kakusiMasuItemHis[10];

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
            D_8010D608_duelresult[i][j + 1] = func_80017BB8_main(i, D_8010D4C8_duelresult[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010D4D4_duelresult[0]; j++) {
            D_8010D628_duelresult[i][j + 1] = func_80017BB8_main(i, D_8010D4D4_duelresult[j + 1]);
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

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/4554C0", func_80105BD0_duelresult);

s16 func_80106800_duelresult(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    D_8010D8E4_duelresult = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_8010D8E6_duelresult = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_8010690C_duelresult(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_8010D8E6_duelresult != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            anim = &D_800D1714_main[D_8010D8E6_duelresult];
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
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_80106A24_duelresult(omObjData *obj) {
    func_8001E888_main(D_8010D8B0_duelresult[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010D8B0_duelresult[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010D8B0_duelresult[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

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
                                                  &D_8010D390_duelresult[index],
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
            func_800550F4_main(D_8010D900_duelresult[i], j, 1);
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
        func_80033430_main(D_8010D924_duelresult[i]);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D7F0_duelresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D810_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/4554C0", func_8010856C_duelresult);

void func_8010A938_duelresult(void) {
    func_80105BD0_duelresult();
    func_8010856C_duelresult();
    D_800D530C_main = 1;
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
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        func_80007EC0_main(40);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult/4554C0", D_8010D83C_duelresult);
