#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern u32 D_8010934C_opduel[];
extern u32 *D_8010940C_opduel[];
extern s32 D_80109200_opduel;
extern Process *D_80109204_opduel;
extern ObjectDuel *D_80109208_opduel;
extern ObjectDuel *D_8010920C_opduel;
extern omObjData *D_80109210_opduel;
extern s16 D_80109214_opduel;
extern Process *D_80109218_opduel;
extern UnkBoard4 *D_8010921C_opduel;
extern UnkBoard4 *D_80109220_opduel;
extern omObjData *D_80109224_opduel;
extern s32 D_80109228_opduel;
extern Vec D_8010922C_opduel;
extern Vec D_80109250_opduel;
extern Vec D_8010925C_opduel[];
extern Vec D_8010928C_opduel[];
extern Vec D_801092A4_opduel[];
extern Vec D_801092BC_opduel[];
extern Vec D_801092D4_opduel[];
extern Vec D_801092EC_opduel[];
extern Vec D_80109304_opduel[];
extern Vec D_8010931C_opduel[];
extern u8 D_80109570_opduel;
extern s32 *D_80109464_opduel[];
extern s32 D_80109484_opduel[];
extern GW_PLAYER *D_80109574_opduel[2];
extern ObjectDuel *D_8010957C_opduel[2];
extern s32 D_80101200_shared_board[];
extern u8 D_80101960[];

void func_800F3C98_name_81(s16, u32 *, s16);
void func_800EB164_name_81(s32, s32);
void func_800EB5E8_name_81(void);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void func_800EB7BC_name_81(Vec *);
Process *func_800EBC60_name_81(Vec *, Vec *, Vec *, s32);
Process *func_800EBF2C_name_81(Vec *, Vec *, Vec *, s32);
s32 func_800EFE8C_name_81(ObjectDuel *, Vec *, f32);
void func_800F6550_name_81(s32, s16, s16);
void func_800F7228_name_81(s32, s32, s32);
void func_800F7458_name_81(s32, f32, f32);
void func_800F76F8_name_81(s32, s32, s16, s32);
void func_800F79DC_name_81(s32);
void func_800F79E8_name_81(s32);
void func_800F8418_name_81(s32, s32, s32);
s32 func_800E1854_minigame(s32);
void func_80105E20_opduel(s16 model);
void func_80106070_opduel(omObjData *obj);
void func_801066B8_opduel(void);
void func_80106D18_opduel(void);
void func_80108FDC_opduel(void);
void func_80109050_opduel(omObjData *obj);
void func_801090AC_opduel(omObjData *obj);
void func_801090F8_opduel(void);
void func_8010911C_opduel(void);
void func_80109158_opduel(void);
void func_801091DC_opduel(void);

void func_801059A0_opduel(void) {
    GW_PLAYER *player;
    s32 i;
    s32 j;

    D_80109570_opduel = GwSystem.current_board_index;
    omInitObjMan(50, 20);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightColorSet(2, 200, 200, 200);
    func_80109158_opduel();
    func_801090F8_opduel();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    HuWinInit();
    omAddPrcObj(func_80108FDC_opduel, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801090AC_opduel);
    for (j = 0; j < 2; j++) {
        player = MBDGetPlayerStruct(j);
        player->stats.partners.frontID = -1;
        player->stats.partners.backID = -1;
    }
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010934C_opduel[0]; j++) {
            D_8010940C_opduel[i][j + 1] = func_80017BB8_main(i, D_8010934C_opduel[j + 1]);
        }
    }
    func_8004A208_main();
}

s16 func_80105B3C_opduel(s32 file, s32 flags) {
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 initialRadius;
    f32 speed;
    f32 rotationSpeed;
    s16 i;

    model = func_8000B108_main(file, flags);
    Hu3DModelPosSet(model, 0, 0, 0);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, 0, func_80105E20_opduel);
    hmf = Hu3DData[model].hmf;
    effect = Hu3DData[model].unkBC;
    particle = effect->unk58;
    effect->unk08.f = 30.0f;
    effect->unk0C.f = 720.0f;
    effect->unk10.f = 80.0f;
    effect->unk14 = 5.0f;
    initialRadius = effect->unk10.f / 10.0f;
    speed = (effect->unk10.f - initialRadius) / effect->unk08.f;
    rotationSpeed = effect->unk0C.f / effect->unk08.f;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = initialRadius;
        particle->unk1C = speed;
        particle->unk24 = rotationSpeed;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return model;
}

s32 func_80105CBC_opduel(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    f32 angle;

    effect->unk1C.f = x;
    effect->unk20.f = y;
    effect->unk24.f = z;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = func_800EFE20_name_81(360.0f);
            particle->unk20 = effect->unk10.f / 10.0f;
            angle = func_800EFE20_name_81(150.0f);
            angle -= 75.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0;
            particle->unk04 = 0;
            return 1;
        }
    }
    return 0;
}

void func_80105E20_opduel(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk18 += particle->unk24;
            if (particle->unk18 < 0.0f) {
                particle->unk18 += 360.0f;
            } else if (particle->unk18 >= 360.0f) {
                particle->unk18 -= 360.0f;
            }
            radius = particle->unk20;
            radius += particle->unk1C;
            particle->unk20 = radius;
            radius *= particle->unk2C;
            particle->unk0C = radius * sindf(particle->unk18) + effect->unk1C.f;
            radius *= cosdf(particle->unk18);
            radius += effect->unk24.f;
            particle->unk14 = radius;
            particle->unk10 = particle->unk20 * particle->unk28 + effect->unk20.f;
            particle->unk04 += effect->unk14;
            if (particle->unk04 > 180.0f) {
                particle->unk04 = 180.0f;
            }
            particle->unk08 = sindf(particle->unk04) * effect->unk14;
        }
    }
    effect->unk02++;
}

void func_80105FE8_opduel(s32 player1, s32 player2) {
    GW_PLAYER *first = MBDGetPlayerStruct(player1);
    GW_PLAYER *second = MBDGetPlayerStruct(player2);
    GW_PLAYER *temp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));

    bcopy(first, temp, sizeof(GW_PLAYER));
    bcopy(second, first, sizeof(GW_PLAYER));
    bcopy(temp, second, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(temp);
}

void func_80106070_opduel(omObjData *obj) {
    s32 i;

    if (WipeStatGet() != 0) {
        return;
    }
    if (D_80109214_opduel != -1) {
        func_8000D044_main(D_80109214_opduel);
        D_80109214_opduel = -1;
    }
    if (D_80109208_opduel != NULL) {
        MBDModelKill(D_80109208_opduel);
        D_80109208_opduel = NULL;
    }
    if (D_8010920C_opduel != NULL) {
        MBDModelKill(D_8010920C_opduel);
        D_8010920C_opduel = NULL;
    }
    if (D_80109210_opduel != NULL) {
        omDelObj(D_80109210_opduel);
        D_80109210_opduel = NULL;
    }
    if (D_80109218_opduel != NULL) {
        omDelPrcObj(D_80109218_opduel);
        D_80109218_opduel = NULL;
    }
    if (D_8010921C_opduel != NULL) {
        func_800F4584_name_81(D_8010921C_opduel);
        D_8010921C_opduel = NULL;
    }
    if (D_80109220_opduel != NULL) {
        func_800F4584_name_81(D_80109220_opduel);
        D_80109220_opduel = NULL;
    }
    for (i = 0; i < 2; i++) {
        MBDModelDispOff((ObjectDuel *)D_80109574_opduel[i]->player_obj);
    }
    omDelObj(obj);
}

void func_801061C4_opduel(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            if (D_800C9520_main[GwPlayer[i].pad] & START_BUTTON) {
                break;
            }
        }
    }
    if (i != 2) {
        D_80109228_opduel = 1;
        WipeColorSet(255, 255, 255);
        WipeCreateOut(11, 16);
        HuAudSeqFadeOut(32);
        func_80007EC0_main(32);
        obj->func = func_80106070_opduel;
    }
}

void func_80106294_opduel(omObjData *obj) {
    s32 i;

    D_80109208_opduel->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        D_80109574_opduel[i]->player_obj->coords.y = D_80109208_opduel->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_80106350_opduel(void) {
    s32 titleFiles[] = { 0x130022, 0x130023, 0x130024, 0x130025, 0x130026, 0x130027 };
    s32 subtitleFiles[] = { 0x130028, 0x130029, 0x13002A, 0x13002B, 0x13002C, 0x13002D };
    void *data;
    f32 amplitude;
    f32 angle;

    HuPrcSleep(10);
    D_8010921C_opduel = func_800F4528_name_81(1, 0);
    data = DataRead(titleFiles[D_80109570_opduel]);
    D_8010921C_opduel->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_8010921C_opduel->unk_0A, 0, D_8010921C_opduel->unk_0C[0], 0);
    HuSprPriSet(D_8010921C_opduel->unk_0A, 0, 10);
    HuSprAttrSet(D_8010921C_opduel->unk_0A, 0, 0);
    HuSprPosSet(D_8010921C_opduel->unk_0A, 0, 160, 100);
    HuSprScaleSet(D_8010921C_opduel->unk_0A, 0, 0.0f, 0.0f);
    for (amplitude = 0.5f, angle = 0.0f; angle <= 720.0f; angle += 45.0f) {
        HuSprScaleSet(D_8010921C_opduel->unk_0A, 0,
                      sindf(angle) * amplitude + 1.0f, sindf(angle) * amplitude + 1.0f);
        amplitude -= 0.03125f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuSprScaleSet(D_8010921C_opduel->unk_0A, 0, 1.0f, 1.0f);
    D_80109220_opduel = func_800F4528_name_81(1, 0);
    data = DataRead(subtitleFiles[D_80109570_opduel]);
    D_80109220_opduel->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80109220_opduel->unk_0A, 0, D_80109220_opduel->unk_0C[0], 0);
    HuSprPriSet(D_80109220_opduel->unk_0A, 0, 9);
    HuSprAttrSet(D_80109220_opduel->unk_0A, 0, 0);
    HuSprPosSet(D_80109220_opduel->unk_0A, 0, 160, 130);
    HuPrcSleep(75);
    func_800F4584_name_81(D_80109220_opduel);
    func_800F4584_name_81(D_8010921C_opduel);
    D_80109220_opduel = NULL;
    D_8010921C_opduel = NULL;
}

void func_801066B8_opduel(void) {
    s32 i;
    f32 scale;

    for (i = 0; i < 2; i++) {
        D_80109574_opduel[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_8010940C_opduel[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80109574_opduel[i]->player_obj->coords, &D_8010925C_opduel[i]);
        MBDModelTempAllocFree((ObjectDuel *)D_80109574_opduel[i]->player_obj);
        D_80109574_opduel[i]->stat |= PLAYER_UNK_04;
    }
    D_80109208_opduel = MBDModelFileCreate(0x1301FF, -1, 1.0f, 0, 0);
    HuVecCopyXYZ(&D_80109208_opduel->scale, 0.625f, 0.625f, 0.625f);
    D_8010920C_opduel = MBDModelFileCreate(0x1301FD, -1, 1.0f, 0, 0);
    HuVecCopy3F(&D_80109208_opduel->coords, &D_8010922C_opduel);
    HuVecCopy3F(&D_8010920C_opduel->coords, &D_8010922C_opduel);
    D_8010920C_opduel->coords.y = 0;
    HuVecCopyXYZ(&D_8010920C_opduel->scale, D_8010920C_opduel->coords.y, D_8010920C_opduel->coords.y, D_8010920C_opduel->coords.y);
    D_80109214_opduel = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80109214_opduel, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(D_80109214_opduel, 40.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    D_80109224_opduel = omAddObj(0x1000, 0, 0, -1, func_801061C4_opduel);
    HuAudSeqPlay(110);
    func_80106350_opduel();
    HuPrcSleep(15);
    HuAudFXPlay(0x2ED);
    while (D_80109208_opduel->coords.y >= 10.0f) {
        D_80109208_opduel->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            D_80109574_opduel[i]->player_obj->coords.y -= 3.0f;
        }
        HuVecCopyXYZ(&D_8010920C_opduel->scale,
                     0.625f - D_80109208_opduel->coords.y * 0.625f / 250.0f,
                     0.625f - D_80109208_opduel->coords.y * 0.625f / 250.0f,
                     0.625f - D_80109208_opduel->coords.y * 0.625f / 250.0f);
        HuPrcVSleep();
    }
    D_80109210_opduel = omAddObj(0x1000, 0, 0, -1, func_80106294_opduel);
    D_80109210_opduel->rot.x = 180.0f;
    D_80109210_opduel->rot.y = 5.0f;
    D_80109210_opduel->rot.z = D_80109208_opduel->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(D_80109214_opduel, D_80109208_opduel->coords.x,
                       D_80109208_opduel->coords.y + 40.0f, D_80109208_opduel->coords.z);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        MBDModelDispOff((ObjectDuel *)D_80109574_opduel[i]->player_obj);
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    HuPrcSleep(20);
    if (D_80109228_opduel != 0) {
        HuPrcSleep(-1);
    } else {
        omDelObj(D_80109224_opduel);
        D_80109224_opduel = NULL;
    }
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&D_80109208_opduel->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(D_80109214_opduel);
    D_80109214_opduel = -1;
    MBDModelKill(D_80109208_opduel);
    D_80109208_opduel = NULL;
    MBDModelKill(D_8010920C_opduel);
    D_8010920C_opduel = NULL;
    omDelObj(D_80109210_opduel);
    D_80109210_opduel = NULL;
    omDelPrcObj(NULL);
}

void func_80106CB4_opduel(omObjData *obj) {
    D_80109208_opduel->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

void func_80106D18_opduel(void) {
    Vec directions[2];
    s32 backgrounds[] = { 0x17, 0x17, 0x17, 0x17, 0x17, 0x17 };
    s16 effects[2];
    HmfMotionNode *node;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 retried;
    f32 scale;
    f32 angle;
    f32 radius;
    f32 speed;
    f32 base;

    MBDBackKill();
    MBDBackLoad(backgrounds[GwSystem.current_board_index]);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_80109208_opduel = func_800D8010_name_81(59, D_80109484_opduel);
    func_800461B4_main(D_80109208_opduel->omObj1->model[0]);
    HuVecCopy3F(&D_80109208_opduel->coords, &D_80109250_opduel);
    D_80109208_opduel->velocity.x = 900.0f;
    D_80109214_opduel = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80109214_opduel, 15.0f, 20.0f, 8.0f);
    func_8000D018_main(D_80109214_opduel, 200.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&D_80109574_opduel[i]->player_obj->coords, &D_801092D4_opduel[i]);
        effects[i] = func_80105B3C_opduel(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            func_80105CBC_opduel(effects[i], D_80109574_opduel[i]->player_obj->coords.x,
                                 D_80109574_opduel[i]->player_obj->coords.y + 50.0f,
                                 D_80109574_opduel[i]->player_obj->coords.z);
            if (j == 0) {
                func_800FFAE0_name_81(i, 1);
            }
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            MBDModelDispOn((ObjectDuel *)D_80109574_opduel[i]->player_obj);
            HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_80109574_opduel[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuAudFXPlay(0x2DD);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    angle = 0.0f;
    radius = 500.0f;
    j = 0;
    while (D_80109208_opduel->velocity.x >= 300.0f) {
        D_80109208_opduel->coords.x = sindf(angle) * radius;
        D_80109208_opduel->coords.z = cosdf(angle) * radius + D_80109250_opduel.z;
        D_80109208_opduel->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        func_8000CFA4_main(D_80109214_opduel, D_80109208_opduel->coords.x,
                           D_80109208_opduel->velocity.x - 50.0f, D_80109208_opduel->coords.z);
        j++;
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&D_80109574_opduel[i]->player_obj->coords, &D_8010928C_opduel[i],
                                      &D_80109574_opduel[i]->player_obj->rot);
                func_800EBF2C_name_81(&D_80109574_opduel[i]->player_obj->coords, &D_8010928C_opduel[i],
                                      &D_80109574_opduel[i]->player_obj->coords, 20);
                MBDMotionSet((ObjectDuel *)D_80109574_opduel[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&D_80109574_opduel[i]->player_obj->coords, &D_80109250_opduel,
                                      &directions[i]);
                func_800EBC60_name_81(&D_80109574_opduel[i]->player_obj->rot, &directions[i],
                                      &D_80109574_opduel[i]->player_obj->rot, 10);
                MBDMotionShiftSet((ObjectDuel *)D_80109574_opduel[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_80106CB4_opduel);
    obj->trans.y = D_80109208_opduel->velocity.x;
    func_800138EC_main(D_80109214_opduel, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_80109574_opduel[i]->player_obj->coords,
                                                                &D_801092A4_opduel[i],
                                                                &D_80109574_opduel[i]->player_obj->coords, 20));
        MBDMotionSet((ObjectDuel *)D_80109574_opduel[i]->player_obj, 2, 2);
    }
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        MBDMotionShiftSet((ObjectDuel *)D_80109574_opduel[i]->player_obj, -1, 0, 5, 2);
    }
    HuAudSeqPlay(13);
    HuAudFXPlay(0x159);
    {
        s32 messages[] = { 0x2701, 0x2702, 0x2703, 0x2704, 0x2705, 0x2706 };

        MBDMotionSet(D_80109208_opduel, 0, 2);
        func_800EB4DC_name_81(-1, 0x2700, messages[D_80109570_opduel], 0, 0, 0, 0);
        func_800EB5E8_name_81();
        func_800EB5E8_name_81();
        func_800EB278_name_81();
        func_800EB29C_name_81();
        MBDMotionSet(D_80109208_opduel, -1, 2);
    }
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    func_800EB7BC_name_81(&directions[0]);
    func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &directions[0],
                          &D_80109574_opduel[0]->player_obj->rot, 10);
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x2707, D_80101200_shared_board[GwPlayer[0].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    MBDMotionSet(D_80109208_opduel, -1, 2);
    MBDVecDirGet(&D_80109574_opduel[0]->player_obj->coords, &D_80109208_opduel->coords, &directions[0]);
    func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &directions[0],
                          &D_80109574_opduel[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    func_800EB7BC_name_81(&directions[1]);
    func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &directions[1],
                          &D_80109574_opduel[1]->player_obj->rot, 10);
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x2708, D_80101200_shared_board[GwPlayer[1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    MBDMotionSet(D_80109208_opduel, -1, 2);
    MBDVecDirGet(&D_80109574_opduel[1]->player_obj->coords, &D_80109208_opduel->coords, &directions[1]);
    func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &directions[1],
                          &D_80109574_opduel[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    retried = 0;
    D_80109208_opduel->rot.x = sindf(0.0f);
    D_80109208_opduel->rot.z = cosdf(0.0f);
    func_800138EC_main(D_80109214_opduel, 1, 0);
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x2709);
    MBDMotionSet(D_80109208_opduel, -1, 2);
    j = func_800EFE20_name_81(2.0f);
spin:
    HuAudFXPlay(0x2DE);
    func_800138EC_main(D_80109214_opduel, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80109208_opduel->rot.x = sindf(angle);
        D_80109208_opduel->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    switch (func_800EFE20_name_81(20.0f)) {
        case 0:
            if (retried == 0) {
                retried = 1;
                while (!(angle >= 160.0f && angle <= 200.0f)) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    D_80109208_opduel->rot.x = sindf(angle);
                    D_80109208_opduel->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                for (speed = 30.0f; speed >= 0.0f; speed -= 1.0f) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    D_80109208_opduel->rot.x = sindf(angle);
                    D_80109208_opduel->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                func_800138EC_main(D_80109214_opduel, 1, 0);
                HuPrcSleep(30);
                MBDMotionSet(D_80109208_opduel, 0, 2);
                func_800EB164_name_81(-1, 0x270A);
                MBDMotionSet(D_80109208_opduel, -1, 2);
                goto spin;
            }
            // fallthrough
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (j != 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else {
                    if (angle >= 70.0f && angle <= 110.0f) {
                        break;
                    }
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.0f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            func_800138EC_main(D_80109214_opduel, 1, 0);
            HuPrcSleep(20);
            func_800138EC_main(D_80109214_opduel, 0, 1);
            speed = -25.0f;
            for (i = 0; i < 6; i++) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = 180.0f;
            if (j == 0) {
                angle = 0.0f;
            }
            D_80109208_opduel->rot.x = sindf(angle);
            D_80109208_opduel->rot.z = cosdf(angle);
            for (i = 0; i < 30; i++) {
                angle += 90.0f;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle) / (i + 10.0f);
                HuPrcVSleep();
            }
            break;
        default:
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (j == 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else {
                    if (angle >= 70.0f && angle <= 110.0f) {
                        break;
                    }
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.04f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                D_80109208_opduel->rot.x = sindf(angle);
                D_80109208_opduel->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = 180.0f;
            if (j == 0) {
                angle = 0.0f;
            }
            D_80109208_opduel->rot.x = sindf(angle);
            D_80109208_opduel->rot.z = cosdf(angle);
            break;
    }
    func_800138EC_main(D_80109214_opduel, 1, 0);
    func_800FFAE0_name_81(j, 2);
    HuPrcSleep(20);
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x270B);
    MBDMotionSet(D_80109208_opduel, -1, 2);
    if (j == 0) {
        MBDMotionSet(D_80109208_opduel, 0, 2);
        func_800EB4DC_name_81(-1, 0x270C, D_80101200_shared_board[GwPlayer[0].chr], 0, 0, 0, 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        MBDMotionSet(D_80109208_opduel, -1, 2);
    } else {
        MBDMotionSet(D_80109208_opduel, 0, 2);
        func_800EB4DC_name_81(-1, 0x270C, D_80101200_shared_board[GwPlayer[1].chr], 0, 0, 0, 0);
        func_800EB278_name_81();
        func_800EB29C_name_81();
        MBDMotionSet(D_80109208_opduel, -1, 2);
        MBDVecDirGet(&D_80109574_opduel[0]->player_obj->coords, &D_80109574_opduel[1]->player_obj->coords,
                              &D_80109574_opduel[0]->player_obj->rot);
        MBDVecDirGet(&D_80109574_opduel[1]->player_obj->coords, &D_80109574_opduel[0]->player_obj->coords,
                              &D_80109574_opduel[1]->player_obj->rot);
        MBDMotionSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 2, 2);
        MBDMotionSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 2, 2);
        while (TRUE) {
            j = func_800EFE8C_name_81((ObjectDuel *)D_80109574_opduel[0]->player_obj, &D_801092BC_opduel[0], 10.0f);
            if (func_800EFE8C_name_81((ObjectDuel *)D_80109574_opduel[1]->player_obj, &D_801092BC_opduel[1], 10.0f) && j) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            j = func_800EFE8C_name_81((ObjectDuel *)D_80109574_opduel[0]->player_obj, &D_801092A4_opduel[1], 10.0f);
            if (func_800EFE8C_name_81((ObjectDuel *)D_80109574_opduel[1]->player_obj, &D_801092A4_opduel[0], 10.0f) && j) {
                break;
            }
            HuPrcVSleep();
        }
        func_80105FE8_opduel(0, 1);
        MBDVecDirGet(&D_80109574_opduel[1]->player_obj->coords, &D_80109208_opduel->coords, &directions[1]);
        func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &directions[1],
                              &D_80109574_opduel[1]->player_obj->rot, 5);
        MBDMotionSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 0, 2);
        MBDMotionSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 0, 2);
    }
    func_800EB7BC_name_81(&D_80109574_opduel[0]->player_obj->rot);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 0);
    func_800F6390_name_81();
    {
        s16 positions[][2] = { { 30, 40 }, { 194, 40 } };

        func_800F6550_name_81(0, positions[0][0], positions[0][1]);
        func_800F6550_name_81(1, positions[1][0], positions[1][1]);
    }
    func_800F7458_name_81(0, 0.0f, 0.0f);
    func_800F7458_name_81(1, 0.0f, 0.0f);
    D_80109200_opduel = 1;
    func_800F79E8_name_81(0);
    func_800FFAE0_name_81(0, 3);
    func_800EFABC_name_81(D_80109574_opduel[0]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 0, 2);
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB4DC_name_81(-1, 0x270D, D_80101200_shared_board[GwPlayer[1].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    MBDMotionSet(D_80109208_opduel, -1, 2);
    func_800EB7BC_name_81(&D_80109574_opduel[1]->player_obj->rot);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 1);
    func_800F79E8_name_81(1);
    func_800FFAE0_name_81(1, 3);
    func_800EFABC_name_81(D_80109574_opduel[1]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 0, 2);
    if (j != 0) {
        func_800138EC_main(D_80109214_opduel, 0, 1);
        func_800EB7BC_name_81(&directions[0]);
        func_800EBC60_name_81(&D_80109208_opduel->rot, &directions[0], &D_80109208_opduel->rot, 5);
        HuPrcSleep(6);
        func_800138EC_main(D_80109214_opduel, 1, 0);
    }
    MBDMotionSet(D_80109208_opduel, 0, 2);
    func_800EB164_name_81(-1, 0x270E);
    MBDMotionSet(D_80109208_opduel, -1, 2);
    func_8002FD8C_main(D_80109208_opduel->omObj1->model[0], Hu3DData[D_80109208_opduel->omObj1->model[0]].motId,
                       "l_mayu", 0x4C, 0x47);
    node = func_8001D33C_main(D_80109208_opduel->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }
    func_800138EC_main(D_80109214_opduel, 0, 1);
    HuAudFXPlay(0x174);
    func_8002FD8C_main(D_80109208_opduel->omObj1->model[0], Hu3DData[D_80109208_opduel->omObj1->model[0]].motId,
                       "hige", 0x17, 0x46);
    node = func_8001D33C_main(D_80109208_opduel->omObj1->model[0], "hige");
    base = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + base;
        HuPrcVSleep();
    }
    node->basePos.y = base;
    func_800138EC_main(D_80109214_opduel, 1, 0);
    {
        s32 models[] = { 0x25, 0x0C, 0x09, 0x0A, 0x26, 0x0B, 0x2C, 0x24 };
        s32 sounds[] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };

        for (i = 0; i < 2; i++) {
            D_8010957C_opduel[i] = func_800D8010_name_81(models[GwPlayer[i].chr], D_80109464_opduel[GwPlayer[i].chr]);
            HuVecCopy3F(&D_8010957C_opduel[i]->coords, &D_801092EC_opduel[i]);
            HuAudFXPlay(sounds[GwPlayer[i].chr]);
        }
    }
    MBDMotionSet(D_8010957C_opduel[0], 0, 2);
    MBDMotionSet(D_8010957C_opduel[1], 0, 2);
    while (TRUE) {
        j = func_800EFE8C_name_81(D_8010957C_opduel[0], &D_80109304_opduel[0], 20.0f);
        if (func_800EFE8C_name_81(D_8010957C_opduel[1], &D_80109304_opduel[1], 20.0f) && j) {
            break;
        }
        HuPrcVSleep();
    }
    func_800EB7BC_name_81(&directions[0]);
    func_800EB7BC_name_81(&directions[1]);
    func_800EBC60_name_81(&D_8010957C_opduel[0]->rot, &directions[0], &D_8010957C_opduel[0]->rot, 10);
    func_800EBC60_name_81(&D_8010957C_opduel[1]->rot, &directions[1], &D_8010957C_opduel[1]->rot, 10);
    HuPrcSleep(10);
    MBDMotionSet(D_8010957C_opduel[0], -1, 2);
    MBDMotionSet(D_8010957C_opduel[1], -1, 2);
    MBDVecDirGet(&D_80109574_opduel[0]->player_obj->coords, &D_80109574_opduel[1]->player_obj->coords,
                          &directions[0]);
    MBDVecDirGet(&D_80109574_opduel[1]->player_obj->coords, &D_80109574_opduel[0]->player_obj->coords,
                          &directions[1]);
    func_800EBC60_name_81(&D_80109574_opduel[0]->player_obj->rot, &directions[0],
                          &D_80109574_opduel[0]->player_obj->rot, 5);
    func_800EBC60_name_81(&D_80109574_opduel[1]->player_obj->rot, &directions[1],
                          &D_80109574_opduel[1]->player_obj->rot, 5);
    MBDMotionShiftSet(D_80109208_opduel, 0, 0, 5, 2);
    func_800EB164_name_81(-1, 0x270F);
    MBDMotionShiftSet(D_80109208_opduel, -1, 0, 5, 2);
    {
        s32 choices[2];
        s32 window1;
        s32 window2;

        choices[0] = 0;
        choices[1] = 0;
        window1 = func_800E1824_name_81(20, 174, 1);
        window2 = func_800E1824_name_81(21, 188, 1);
        while (choices[0] == 0 || choices[1] == 0) {
            for (i = 0; i < 2; i++) {
                if (choices[i] != 0) {
                    continue;
                }
                if (func_800F37B8_name_81(i) == 0) {
                    if (D_800C9520_main[GwPlayer[i].pad] & A_BUTTON) {
                        choices[i] = 1;
                    } else if (D_800C9520_main[GwPlayer[i].pad] & B_BUTTON) {
                        choices[i] = 2;
                    }
                } else {
                    choices[i] = 1;
                    switch (GwPlayer[i].chr) {
                        case 5:
                            choices[i] = 2;
                            break;
                        case 2:
                            if (func_800EFE20_name_81(100.0f) < 50) {
                                choices[i] = 2;
                            }
                            break;
                        case 0:
                            if (func_800EFE20_name_81(100.0f) < 20) {
                                choices[i] = 2;
                            }
                            break;
                    }
                }
            }
            HuPrcVSleep();
        }
        func_800E1854_minigame(window1);
        func_800E1854_minigame(window2);
        MBDMotionSet(D_8010957C_opduel[0], 0, 2);
        MBDMotionSet(D_8010957C_opduel[1], 0, 2);
        MBDVecDirGet(&D_8010957C_opduel[0]->coords, &D_8010931C_opduel[(choices[0] - 1) * 2],
                              &D_8010957C_opduel[0]->rot);
        MBDVecDirGet(&D_8010957C_opduel[1]->coords, &D_8010931C_opduel[(choices[1] - 1) * 2 + 1],
                              &D_8010957C_opduel[1]->rot);
        func_800EBF2C_name_81(&D_8010957C_opduel[0]->coords, &D_8010931C_opduel[(choices[0] - 1) * 2],
                              &D_8010957C_opduel[0]->coords, 20);
        func_800EBF2C_name_81(&D_8010957C_opduel[1]->coords, &D_8010931C_opduel[(choices[1] - 1) * 2 + 1],
                              &D_8010957C_opduel[1]->coords, 20);
        HuPrcSleep(20);
        MBDVecDirGet(&D_8010957C_opduel[0]->coords, &D_80109574_opduel[1]->player_obj->coords,
                              &directions[0]);
        MBDVecDirGet(&D_8010957C_opduel[1]->coords, &D_80109574_opduel[0]->player_obj->coords,
                              &directions[1]);
        func_800EBC60_name_81(&D_8010957C_opduel[0]->rot, &directions[0], &D_8010957C_opduel[0]->rot, 10);
        func_800EBC60_name_81(&D_8010957C_opduel[1]->rot, &directions[1], &D_8010957C_opduel[1]->rot, 10);
        HuPrcSleep(10);
        MBDMotionSet(D_8010957C_opduel[0], -1, 2);
        MBDMotionSet(D_8010957C_opduel[1], -1, 2);
        func_800F8418_name_81(0, D_80101960[GwPlayer[0].chr], choices[0] - 1);
        func_800F79DC_name_81(0);
        if (choices[0] == 1) {
            func_800F5BB4_name_81(0);
            func_800F76F8_name_81(0, 0, 28, 0);
        } else {
            func_800F5EB0_name_81(0);
            func_800F76F8_name_81(0, 0, -28, 1);
        }
        func_800F8418_name_81(1, D_80101960[GwPlayer[1].chr], choices[1] - 1);
        if (choices[1] == 1) {
            func_800F5BB4_name_81(1);
            func_800F76F8_name_81(1, 0, 28, 0);
        } else {
            func_800F5EB0_name_81(1);
            func_800F76F8_name_81(1, 0, -28, 1);
        }
        for (i = 28; i >= 0; i--) {
            if (choices[0] == 1) {
                func_800F76F8_name_81(0, 0, i, 0);
            } else {
                func_800F76F8_name_81(0, 0, -i, 1);
            }
            if (choices[1] == 1) {
                func_800F76F8_name_81(1, 0, i, 0);
            } else {
                func_800F76F8_name_81(1, 0, -i, 1);
            }
            HuPrcVSleep();
        }
    }
    func_800F79DC_name_81(1);
    MBDMotionShiftSet(D_80109208_opduel, 0, 0, 5, 2);
    func_800EB164_name_81(-1, 0x2710);
    MBDMotionShiftSet(D_80109208_opduel, -1, 0, 5, 2);
    func_800F7228_name_81(0, 10, 1);
    func_800F7228_name_81(1, 10, 0);
    func_800EB7BC_name_81(&D_80109574_opduel[0]->player_obj->rot);
    func_800EB7BC_name_81(&D_80109574_opduel[1]->player_obj->rot);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 4, 0);
    MBDMotionSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    MBDMotionShiftSet((ObjectDuel *)D_80109574_opduel[0]->player_obj, 0, 0, 5, 2);
    MBDMotionShiftSet((ObjectDuel *)D_80109574_opduel[1]->player_obj, 0, 0, 5, 2);
    MBDMotionShiftSet(D_80109208_opduel, 0, 0, 5, 2);
    func_800EB164_name_81(-1, 0x2711);
    MBDMotionShiftSet(D_80109208_opduel, -1, 0, 5, 2);
}

void func_80108FDC_opduel(void) {
    D_80109218_opduel = omAddPrcObj(func_801066B8_opduel, 0x300, 0x2000, 0);
    HuPrcChildLink(HuPrcCurrentGet(), D_80109218_opduel);
    HuPrcChildWatch();
    func_80106D18_opduel();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80109050_opduel(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_801091DC_opduel();
        func_8010911C_opduel();
        HuWinAllKill();
        if (D_80109200_opduel != 0) {
            func_800F64FC_name_81();
        }
        omOvlReturnEx(1);
    }
}

void func_801090AC_opduel(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        HuAudSeqFadeOut(60);
        obj->func = func_80109050_opduel;
    }
}

void func_801090F8_opduel(void) {
    MBDModelInit();
    func_800F3F4C_name_81();
}

void func_8010911C_opduel(void) {
    func_800F4030_name_81();
    MBDModelClose();
    if (D_80109204_opduel != NULL) {
        omDelPrcObj(D_80109204_opduel);
    }
}

void func_80109158_opduel(void) {
    s32 sp10[] = { 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };

    Hu3DCamInit(1);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(sp10[GwSystem.current_board_index]);
}

void func_801091DC_opduel(void) {
    MBDBackKill();
    MBDBackClose();
}
