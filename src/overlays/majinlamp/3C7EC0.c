#include "common.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"

extern omObjData *D_80108350_majinlamp[32];
extern s16 D_80108338_majinlamp;
extern s16 D_8010833A_majinlamp;
extern s32 D_8010833C_majinlamp;
extern f32 D_801080D0_majinlamp;
extern f32 D_801080D4_majinlamp;
extern f32 D_801080D8_majinlamp;
extern f32 D_801080DC_majinlamp;
extern f32 D_801080E0_majinlamp;
extern f32 D_801080E4_majinlamp;
extern s16 D_801080E8_majinlamp;
extern s16 D_801080EA_majinlamp;
extern s16 D_801080EC_majinlamp;
extern f32 D_801080F0_majinlamp;
extern Vec D_801080F4_majinlamp[];
extern Vec D_80108118_majinlamp;
extern Object *D_8010832C_majinlamp;
extern Object *D_80108330_majinlamp;
extern GW_PLAYER *D_80108334_majinlamp;
extern Vec D_801082E4_majinlamp;
extern Vec D_801082F0_majinlamp;
extern Vec D_801082FC_majinlamp;
extern Vec D_80108308_majinlamp;
extern Vec D_80108314_majinlamp;
extern Vec D_80108320_majinlamp;
extern Process *D_801082E0_majinlamp;
extern s32 D_80108124_majinlamp;
extern s16 D_8010833E_majinlamp;
extern s16 D_80108340_majinlamp[];
extern s16 D_80108342_majinlamp;
extern s32 D_80108270_majinlamp[];
extern s32 D_80108290_majinlamp[];
extern Vec D_801082B0_majinlamp;
extern Vec D_801082BC_majinlamp;
extern Vec D_801082C8_majinlamp;
extern Vec D_801082D4_majinlamp;
extern const char D_80108260_majinlamp[];
extern const char D_80108268_majinlamp[];

void func_8001E888_main(s16 idx, f32 x, f32 y, u16 width, u16 height, char *name, u8 reset);
void msmSeStop(s32 slot);
void MBDlgResultWinExec(s32);
void MBDlgWinExecY(s16, s32, s32);
void *memcpy(void *, const void *, unsigned int);
void func_80106E74_majinlamp(void);
void func_8010771C_majinlamp(void);
void func_80107DD8_majinlamp(omObjData *arg0);
void func_80107D98_majinlamp(void);
void func_80107E1C_majinlamp(omObjData *arg0);
void func_80107E40_majinlamp(void);
void func_80107E64_majinlamp(void);
void func_80107F54_majinlamp(void);
void func_801080C4_majinlamp(void);
void func_80105B14_majinlamp(omObjData *arg0);
void func_80105E2C_majinlamp(omObjData *arg0);
void func_801067EC_majinlamp(omObjData *arg0);

void func_801059A0_majinlamp(void) {
    D_8010833C_majinlamp = GwSystem.current_player_index;
    omInitObjMan(0x50, 0x50);
    func_80107F54_majinlamp();
    func_80107E40_majinlamp();
    HuWinInit();
    omAddPrcObj(func_80107D98_majinlamp, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80107E1C_majinlamp);
}

void func_80105A20_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_80108350_majinlamp[i] = NULL;
    }
}

void func_80105A50_majinlamp(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] != NULL) {
            if (D_80108350_majinlamp[i]->func == func_80105B14_majinlamp ||
                D_80108350_majinlamp[i]->func == func_80105E2C_majinlamp ||
                D_80108350_majinlamp[i]->func == func_801067EC_majinlamp) {
                if (D_80108350_majinlamp[i]->stat & 4) {
                    D_80108350_majinlamp[i]->data = NULL;
                    omDelObj(D_80108350_majinlamp[i]);
                }
            }
        }
    }
}

void func_80105B14_majinlamp(omObjData *arg0) {
    Object *temp_v1;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->coords.x = arg0->trans.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y = arg0->trans.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z = arg0->trans.z;
            omDelObj(arg0);
        } else {
            GwPlayer[arg0->work[0]].player_obj->coords.x += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y += arg0->scale.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z += arg0->scale.z;
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->coords.x = arg0->trans.x;
        temp_v1->coords.y = arg0->trans.y;
        temp_v1->coords.z = arg0->trans.z;
        arg0->data = NULL;
        omDelObj(arg0);
    } else {
        temp_v1->coords.x += arg0->scale.x;
        temp_v1->coords.y += arg0->scale.y;
        temp_v1->coords.z += arg0->scale.z;
    }
}

omObjData *func_80105CA8_majinlamp(s32 arg0, Vec *arg1, s32 arg2, Object *arg3) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105B14_majinlamp);
    obj->work[0] = arg0;
    obj->work[1] = arg2;
    obj->trans.x = arg1->x;
    obj->trans.y = arg1->y;
    obj->trans.z = arg1->z;

    if (arg3 == NULL) {
        obj->scale.x = (arg1->x - GwPlayer[arg0].player_obj->coords.x) / arg2;
        obj->scale.y = (arg1->y - GwPlayer[arg0].player_obj->coords.y) / arg2;
        obj->scale.z = (arg1->z - GwPlayer[arg0].player_obj->coords.z) / arg2;
    } else {
        obj->scale.x = (arg1->x - arg3->coords.x) / arg2;
        obj->scale.y = (arg1->y - arg3->coords.y) / arg2;
        obj->scale.z = (arg1->z - arg3->coords.z) / arg2;
    }

    obj->data = arg3;
    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80105E2C_majinlamp(omObjData *arg0) {
    Object *temp_v1;
    Object *temp_v0;
    f32 temp_f20;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->coords.x = arg0->trans.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y = arg0->trans.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z = arg0->trans.z;
            omDelObj(arg0);
            return;
        } else {
            GwPlayer[arg0->work[0]].player_obj->coords.x += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y += arg0->scale.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z += arg0->scale.z;
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x;
            temp_v1->coords.x = temp_v0->coords.x + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x));
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y;
            temp_v1->coords.y = temp_v0->coords.y + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y));
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z;
            temp_v1->coords.z = temp_v0->coords.z + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z));
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->coords.x = arg0->trans.x;
        temp_v1->coords.y = arg0->trans.y;
        temp_v1->coords.z = arg0->trans.z;
        arg0->data = NULL;
        omDelObj(arg0);
        return;
    } else {
        temp_v1->coords.x += arg0->scale.x;
        temp_v1->coords.y += arg0->scale.y;
        temp_v1->coords.z += arg0->scale.z;
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x;
        temp_v1->coords.x = temp_v1->coords.x + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x));
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y;
        temp_v1->coords.y = temp_v1->coords.y + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y));
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z;
        temp_v1->coords.z = temp_v1->coords.z + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z));
    }
}

omObjData *func_80106634_majinlamp(s32 arg0, Vec *arg1, s32 arg2, Vec *arg3) {
    omObjData *obj;
    s32 player = -1;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, func_80105E2C_majinlamp);
    if (arg0 >= 0) {
        player = arg0;
        arg0 = 0;
        obj->work[0] = player;
    }
    obj->work[1] = arg2;
    obj->work[2] = arg2;
    obj->trans.x = arg1->x;
    obj->trans.y = arg1->y;
    obj->trans.z = arg1->z;

    if (arg0 == 0) {
        obj->scale.x = (arg1->x - GwPlayer[player].player_obj->coords.x) / arg2;
        obj->scale.y = (arg1->y - GwPlayer[player].player_obj->coords.y) / arg2;
        obj->scale.z = (arg1->z - GwPlayer[player].player_obj->coords.z) / arg2;
    } else {
        obj->scale.x = (arg1->x - ((Object *)arg0)->coords.x) / arg2;
        obj->scale.y = (arg1->y - ((Object *)arg0)->coords.y) / arg2;
        obj->scale.z = (arg1->z - ((Object *)arg0)->coords.z) / arg2;
    }

    obj->rot.x = arg3->x;
    obj->rot.y = arg3->y;
    obj->rot.z = arg3->z;
    obj->data = (void *)arg0;

    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_801067EC_majinlamp(omObjData *arg0) {
    Object *temp_v1;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->rot.x = arg0->rot.x;
            GwPlayer[arg0->work[0]].player_obj->rot.y = arg0->rot.y;
            GwPlayer[arg0->work[0]].player_obj->rot.z = arg0->rot.z;
            omDelObj(arg0);
        } else {
            arg0->scale.y += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->rot.x =
                sinf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
            GwPlayer[arg0->work[0]].player_obj->rot.y = 0;
            GwPlayer[arg0->work[0]].player_obj->rot.z =
                cosf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->rot.x = arg0->rot.x;
        temp_v1->rot.y = arg0->rot.y;
        temp_v1->rot.z = arg0->rot.z;
        arg0->data = NULL;
        omDelObj(arg0);
    } else {
        arg0->scale.y += arg0->scale.x;
        temp_v1->rot.x = sinf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
        temp_v1->rot.y = 0;
        temp_v1->rot.z = cosf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
    }
}

omObjData *func_801069B8_majinlamp(s32 arg0, Vec *arg1, s32 arg2, Object *arg3) {
    Vec sp18;
    omObjData *obj;
    f32 var_f20;
    f32 var_f4;
    s32 i;

    if (arg3 == NULL) {
        MBVecDirGet(&GwPlayer[arg0].player_obj->coords, arg1, &sp18);
    } else {
        MBVecDirGet(&arg3->coords, arg1, &sp18);
    }

    obj = omAddObj(0x1000, 0, 0, -1, func_801067EC_majinlamp);
    obj->work[0] = arg0;
    obj->work[1] = arg2;
    obj->rot.x = sp18.x;
    obj->rot.y = sp18.y;
    obj->rot.z = sp18.z;

    if (arg3 == NULL) {
        var_f20 = MBVecAngleGet(&GwPlayer[arg0].player_obj->rot);
        var_f4 = MBVecAngleGet(&sp18);
        if (var_f4 < var_f20) {
            if ((var_f20 - var_f4) >= 180.0f) {
                var_f4 += 360.0f;
            }
        } else if ((var_f4 - var_f20) >= 180.0f) {
            var_f20 += 360.0f;
        }
    } else {
        var_f20 = MBVecAngleGet(&arg3->rot);
        var_f4 = MBVecAngleGet(&sp18);
        if (var_f4 < var_f20) {
            if ((var_f20 - var_f4) >= 180.0f) {
                var_f4 += 360.0f;
            }
        } else if ((var_f4 - var_f20) >= 180.0f) {
            var_f20 += 360.0f;
        }
    }

    obj->scale.y = var_f20;
    obj->scale.x = (var_f4 - var_f20) / (f32)arg2;
    obj->data = arg3;

    for (i = 0; i < 32; i++) {
        if (D_80108350_majinlamp[i] == NULL) {
            D_80108350_majinlamp[i] = obj;
            break;
        }
    }
    return obj;
}

void func_80106BB0_majinlamp(omObjData *arg0) {
    func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, arg0->trans.x, 0x40, 0x40, D_80108260_majinlamp, 0);
    arg0->trans.x += 1.0f;

    if (D_80108124_majinlamp != 0) {
        func_8001E888_main(D_80108330_majinlamp->omObj1->model[0], 0, arg0->trans.y, 0x40, 0x40, D_80108268_majinlamp, 0);
        arg0->trans.y += 1.0f;
    }

    if (arg0->trans.x >= 64.0f) {
        arg0->trans.x -= 64.0f;
    }
    if (arg0->trans.y >= 64.0f) {
        arg0->trans.y -= 64.0f;
    }
    if (arg0->trans.x <= -64.0f) {
        arg0->trans.x += 64.0f;
    }
    if (arg0->trans.y <= -64.0f) {
        arg0->trans.y += 64.0f;
    }
}

void func_80106D3C_majinlamp(omObjData *arg0) {
    if (D_801080EC_majinlamp != 0) {
        D_8010832C_majinlamp->velocity.x = sindf(arg0->rot.y) * 30.0f;
        arg0->rot.y += 2.0f;
        if (arg0->rot.y >= 360.0f) {
            arg0->rot.y -= 360.0f;
        }
    }

    if (D_801080E8_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->velocity.x =
            D_801080F0_majinlamp * D_8010832C_majinlamp->scale.x + D_8010832C_majinlamp->velocity.x;
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_8010832C_majinlamp->coords);
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->scale, &D_8010832C_majinlamp->scale);
    }

    if (D_801080EA_majinlamp != 0) {
        D_80108334_majinlamp->player_obj->rot.x = D_8010832C_majinlamp->rot.x;
        D_80108334_majinlamp->player_obj->rot.z = D_8010832C_majinlamp->rot.z;
    }
}

void func_80106E74_majinlamp(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    f32 var_f20;
    f32 var_f22;
    f32 var_f24;
    f32 var_f26;
    f32 temp_f28;
    Object *temp_obj;
    s32 i;
    void *temp_v0;
    omObjData *temp_v1;

    D_80108338_majinlamp = HuSprGrpCreate(1, 5);
    temp_v0 = DataRead(0x1301BF);
    D_8010833A_majinlamp = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    HuSprGrpMemberSet(D_80108338_majinlamp, 0, D_8010833A_majinlamp, 0);
    HuSprPriSet(D_80108338_majinlamp, 0, 0xA);
    func_800550F4_main(D_80108338_majinlamp, 0, 1);
    HuSprAttrSet(D_80108338_majinlamp, 0, 0x5000);
    HuSprPosSet(D_80108338_majinlamp, 0, 0xA0, 0x78);
    HuSprScaleSet(D_80108338_majinlamp, 0, 50.0f, 50.0f);
    D_80108334_majinlamp = MBPlayerGet(D_8010833C_majinlamp);
    MBPlayerModelCreate(D_8010833E_majinlamp, D_80101734_shared_board[GwPlayer[D_8010833C_majinlamp].chr], 2);
    memcpy(&sp18, D_80108270_majinlamp, 0x20);
    memcpy(&sp38, D_80108290_majinlamp, 0x20);
    D_80108340_majinlamp[0] = func_80017790_main(
        D_80108334_majinlamp->player_obj->omObj1->model[0], 2,
        GwPlayer[D_8010833C_majinlamp].chr,
        ((s32 *)&sp18)[GwPlayer[D_8010833C_majinlamp].chr]);
    D_80108340_majinlamp[1] = func_80017AD8_main(
        ((s32 *)&sp38)[GwPlayer[D_8010833C_majinlamp].chr]);
    func_80017954_main(D_80108334_majinlamp->player_obj->omObj1->model[0], 2,
                       GwPlayer[D_8010833C_majinlamp].chr, D_80108340_majinlamp[0]);
    MBPlayerMotionSet(D_8010833C_majinlamp, 4, 2);
    HuVecCopyXYZ(&D_80108334_majinlamp->player_obj->coords, 150.0f, -100.0f, 3000.0f);
    temp_v1 = (omObjData *)D_80108334_majinlamp->player_obj;
    temp_v1->next_idx |= 1;
    D_8010832C_majinlamp = MBModelCreate(0x25, 0);
    HuVecCopyXYZ(&D_8010832C_majinlamp->coords, -150.0f, -50.0f, 3000.0f);
    {
        omObjData *obj = omAddObj(0x1000, 0, 0, -1, func_80106D3C_majinlamp);
        obj->rot.y = 0.0f;
        obj->scale.x = 0.0f;
    }
    D_800C9930_main = func_8004A5C4_main(0x3C);
    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    func_800F2388_shared_board(D_8010833C_majinlamp, -1, 0, 0xA, 2);
    HuPrcSleep(0xF);
    MBDlgResultWinExec(0x3A17);
    D_801080EC_majinlamp = 0;
    var_f20 = 20.0f;
    while (D_8010832C_majinlamp->velocity.x < 1000.0f) {
        D_8010832C_majinlamp->velocity.x += var_f20;
        var_f20 += 5.0f;
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8010832C_majinlamp->coords, -1600.0f, -100.0f, 1600.0f);
    D_801080EC_majinlamp = 1;
    func_8008A120_main(HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, 60.0f);
    D_8010832C_majinlamp->rot.x = sindf(45.0f);
    D_8010832C_majinlamp->rot.z = cosdf(45.0f);
    var_f20 = 50.0f;
    while (D_8010832C_majinlamp->coords.x < 0.0f) {
        D_8010832C_majinlamp->coords.x += var_f20 * 2.0f;
        D_8010832C_majinlamp->coords.z += var_f20 * 2.0f;
        var_f20 -= 1.6f;
        if (var_f20 <= 5.0f) {
            var_f20 = 5.0f;
        }
        HuPrcVSleep();
    }
    MBPlayerMotionSet(D_8010833C_majinlamp, 2, 0);
    memcpy(&sp18, &D_801082B0_majinlamp, 0xC);
    MBPlayerPosMoveCreate(&D_80108334_majinlamp->player_obj->coords, &sp18,
                          &D_80108334_majinlamp->player_obj->coords, 0x14);
    D_80108334_majinlamp->player_obj->velocity.y = 30.0f;
    D_80108334_majinlamp->player_obj->velocity.z = -2.5f;
    HuPrcSleep(0x14);
    temp_obj = D_80108334_majinlamp->player_obj;
    temp_obj->velocity.z = (temp_f28 = 0.0f);
    temp_obj->velocity.y = temp_f28;
    D_801080F0_majinlamp = D_80108334_majinlamp->player_obj->coords.y -
                           D_8010832C_majinlamp->coords.y - 15.0f;
    D_801080E8_majinlamp = 1;
    D_801080EA_majinlamp = 1;
    MBPlayerMotionSet(D_8010833C_majinlamp, -1, 2);
    memcpy(&sp28, &D_801082BC_majinlamp, 0xC);
    func_801069B8_majinlamp(D_8010833C_majinlamp, &sp28, 5, NULL);
    HuPrcSleep(5);
    MBDlgWinExecY(-1, 0x3A18, 0x28);
    HuAudFXPlay(0x12B);
    memcpy(&sp38, &D_801082C8_majinlamp, 0xC);
    memcpy(&sp48, &D_801082D4_majinlamp, 0xC);
    func_801069B8_majinlamp(0, &sp38, 0x1E, D_8010832C_majinlamp);
    func_80106634_majinlamp((s32)D_8010832C_majinlamp, &sp38, 0x1E, &sp48);
    var_f20 = 60.0f;
    for (i = 0; i < 0x1E; i++) {
        func_8008A120_main(HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, var_f20);
        func_8008A120_main(HmfModelData[D_80108334_majinlamp->player_obj->omObj1->model[0]].mtx,
                           var_f20 - 60.0f);
        var_f20 -= 2.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 2);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(D_80108334_majinlamp->player_obj);
    MBModelDispOff(D_8010832C_majinlamp);
    HuSprTPLvlSet(D_80108338_majinlamp, 0, 0);
}

void func_8010771C_majinlamp(void) {
    Vec sp[4];
    Vec *direction;
    Vec *offset;
    s16 sound;
    s32 i;

    D_80108330_majinlamp = MBModelFileCreate(0x1301F6, -1, 1.0f, 0.0f, NULL);
    HuVecCopyXYZ(&D_80108330_majinlamp->scale, 2.0f, 2.0f, 2.0f);
    func_8001C954_main(D_80108330_majinlamp->omObj1->model[0]);
    Hu3DMotionSpeedSet(D_80108330_majinlamp->omObj1->model[0], 0.25f);
    HuVecCopyXYZ(&D_80108330_majinlamp->scale, 4.0f, 4.0f, 4.0f);
    Hu3DModelCameraSet(D_80108330_majinlamp->omObj1->model[0], HU3D_CAM1);
    omAddObj(0x1000, 0, 0, -1, func_80106BB0_majinlamp);
    D_801080D0_majinlamp = 45.0f;
    D_801080DC_majinlamp = 100.0f;
    D_801080E0_majinlamp = 10.0f;
    D_801080E4_majinlamp = 20000.0f;
    func_8008A120_main(HmfModelData[D_8010832C_majinlamp->omObj1->model[0]].mtx, 60.0f);
    func_8008A120_main(HmfModelData[D_80108334_majinlamp->player_obj->omObj1->model[0]].mtx, 0.0f);
    HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_801080F4_majinlamp[0]);
    HuVecCopy3F(&D_8010832C_majinlamp->coords, &D_801080F4_majinlamp[0]);
    MBMotionSet(D_80108334_majinlamp->player_obj, -1, 2);
    MBVecForwardSet(&D_80108334_majinlamp->player_obj->rot);
    MBVecForwardSet(&D_8010832C_majinlamp->rot);
    D_801080F0_majinlamp = 0.0f;
    D_801080E8_majinlamp = 1;
    D_801080EA_majinlamp = 1;
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    sound = HuAudFXPlay(0x12A);
    MBModelDispOn(D_80108334_majinlamp->player_obj);
    MBModelDispOn(D_8010832C_majinlamp);
    for (i = 0; i < 0xB5; i += 2) {
        HuVecCopy3F(&sp[0], &D_80108334_majinlamp->player_obj->coords);
        HuVecCopy3F(&D_80108334_majinlamp->player_obj->coords, &D_801080F4_majinlamp[0]);
        HuVecSubtract(&sp[2], &D_801080F4_majinlamp[2], &D_801080F4_majinlamp[0]);
        HuVecMulScalar(&sp[2], sindf(i / 2), &sp[2]);
        HuVecAdd(&D_80108334_majinlamp->player_obj->coords, &sp[2],
                 &D_80108334_majinlamp->player_obj->coords);
        sp[3].x = -sindf(i * 2) * (0x1F4 - i);
        sp[3].y = -sindf(i * 2) * (0x12C - i);
        sp[3].z = 0.0f;
        HuVecAdd(&D_80108334_majinlamp->player_obj->coords, &sp[3],
                 &D_80108334_majinlamp->player_obj->coords);
        MBVecDirGet(&sp[0], &D_80108334_majinlamp->player_obj->coords,
                    &D_80108334_majinlamp->player_obj->rot);
        HuVecCopy3F(&D_8010832C_majinlamp->coords,
                    &D_80108334_majinlamp->player_obj->coords);
        HuVecCopy3F(&D_8010832C_majinlamp->rot, &D_80108334_majinlamp->player_obj->rot);
        HuPrcVSleep();
    }
    D_80108124_majinlamp = 1;
    D_801080EA_majinlamp = 0;
    direction = &sp[2];
    offset = &sp[3];
    MBVecForwardSet(offset);
    HuVecCopy3F(direction, &D_80108334_majinlamp->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_80108334_majinlamp->player_obj->rot, offset,
                                                                 &D_80108334_majinlamp->player_obj->rot, 0xA));
    HuPrcChildWatch();
    msmSeStop(sound);
    PlayerFXPlay(0x2BD, D_8010833E_majinlamp);
    func_80017954_main(D_80108334_majinlamp->player_obj->omObj1->model[0], 2,
                       GwPlayer[D_8010833C_majinlamp].chr, D_80108342_majinlamp);
    MBPlayerMotionSet(D_8010833C_majinlamp, 5, 2);
    HuPrcSleep(0x32);
    MBVecDirGet(&D_80108334_majinlamp->player_obj->coords, &D_80108118_majinlamp, direction);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_80108334_majinlamp->player_obj->rot, direction,
                                                                 &D_80108334_majinlamp->player_obj->rot, 0xA));
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_8010832C_majinlamp->rot, direction,
                                                                 &D_8010832C_majinlamp->rot, 0xA));
    HuPrcChildWatch();
    D_801080EA_majinlamp = 1;
    HuPrcSleep(0xA);
    HuAudFXPlay(0x12B);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_80108334_majinlamp->player_obj->coords,
                                                            &D_80108118_majinlamp,
                                                            &D_80108334_majinlamp->player_obj->coords, 0x14));
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_8010832C_majinlamp->coords, &D_80108118_majinlamp,
                                                            &D_8010832C_majinlamp->coords, 0x14));
    HuPrcSleep(0xA);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 0x14);
    HuPrcChildWatch();
}

void func_80107D98_majinlamp(void) {
    func_80106E74_majinlamp();
    func_8010771C_majinlamp();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80107DD8_majinlamp(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        func_801080C4_majinlamp();
        func_80107E64_majinlamp();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_80107E1C_majinlamp(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        arg0->func = func_80107DD8_majinlamp;
    }
}

void func_80107E40_majinlamp(void) {
    MBModelInit();
    func_800F26E8_shared_board();
}

void func_80107E64_majinlamp(void) {
    HuSprAnimKill(D_8010833A_majinlamp);
    HuSprGrpKill(D_80108338_majinlamp);
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_80107EA0_majinlamp(void) {
    for (;;) {
        Hu3DCameraPerspectiveSet(0, D_801080D0_majinlamp, D_801080D4_majinlamp, D_801080D8_majinlamp);
        Hu3DCameraPosSetV(0, &D_801082E4_majinlamp, &D_801082F0_majinlamp, &D_801082FC_majinlamp);
        Hu3DCamUpdateMtx(0);
        Hu3DCameraPerspectiveSet(1, D_801080DC_majinlamp, D_801080E0_majinlamp, D_801080E4_majinlamp);
        Hu3DCameraPosSetV(1, &D_80108308_majinlamp, &D_80108314_majinlamp, &D_80108320_majinlamp);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

void func_80107F54_majinlamp(void) {
    Hu3DCamInit(2);
    D_801082E0_majinlamp = omAddPrcObj(func_80107EA0_majinlamp, 0x1001, 0, 0);
    omPrcSetStatBit(D_801082E0_majinlamp, OM_STAT_NOALLPAUSE);

    HuVecCopyXYZ(&D_801082E4_majinlamp, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&D_801082F0_majinlamp, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_801082FC_majinlamp, 0.0f, 1.0f, 0.0f);
    Hu3DCameraPerspectiveSet(0, D_801080D0_majinlamp, D_801080D4_majinlamp, D_801080D8_majinlamp);
    Hu3DCameraPosSetV(0, &D_801082E4_majinlamp, &D_801082F0_majinlamp, &D_801082FC_majinlamp);
    Hu3DCamUpdateMtx(0);

    HuVecCopyXYZ(&D_80108308_majinlamp, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&D_80108314_majinlamp, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_80108320_majinlamp, 0.0f, 1.0f, 0.0f);
    Hu3DCameraPerspectiveSet(1, D_801080DC_majinlamp, D_801080E0_majinlamp, D_801080E4_majinlamp);
    Hu3DCameraPosSetV(1, &D_80108308_majinlamp, &D_80108314_majinlamp, &D_80108320_majinlamp);
    Hu3DCamUpdateMtx(1);
}

void func_801080C4_majinlamp(void) {
}

const char D_80108260_majinlamp[8] = "bg_in";
const char D_80108268_majinlamp[8] = "bg_out";

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108270_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_80108290_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082B0_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082BC_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082C8_majinlamp);

INCLUDE_RODATA("asm/nonmatchings/overlays/majinlamp/3C7EC0", D_801082D4_majinlamp);
