#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern u32 D_80108A64_opdueltutorial[];
extern u32 *D_80108B24_opdueltutorial[];
extern s32 D_80108930_opdueltutorial;
extern Process *D_80108934_opdueltutorial;
extern u8 D_80108C10_opdueltutorial;
extern s16 D_80108C44_opdueltutorial;
extern s16 D_80108C46_opdueltutorial;
extern GW_PLAYER *D_80108C14_opdueltutorial[2];
extern Object *D_80108C1C_opdueltutorial;
extern Vec D_80108944_opdueltutorial;
extern Vec D_80108974_opdueltutorial[];
extern Vec D_80108938_opdueltutorial;
extern Vec D_80108968_opdueltutorial;
extern Vec D_801089A4_opdueltutorial[];
extern Vec D_801089BC_opdueltutorial[];
extern Vec D_801089EC_opdueltutorial[];
extern Vec D_80108A04_opdueltutorial[];
extern Vec D_80108A1C_opdueltutorial[];
extern Vec D_80108A34_opdueltutorial[];
extern s32 *D_80108B74_opdueltutorial[];
extern s32 D_80108B94_opdueltutorial[];
extern Object *D_80108C20_opdueltutorial[2];
extern Object *D_80108C28_opdueltutorial;
extern s16 D_80108C2C_opdueltutorial;
extern s16 D_80108C30_opdueltutorial[];
extern u8 D_80101960[];

void func_800F3C98_name_81(s16, u32 *, s16);
void func_800EB7BC_name_81(Vec *);
Process *func_800EBC60_name_81(Vec *, Vec *, Vec *, s32);
Process *func_800EBF2C_name_81(Vec *, Vec *, Vec *, s32);
void func_800EF754_name_81(s16);
s32 func_800EFE8C_name_81(Object *, Vec *, f32);
void func_800F6550_name_81(s32, s16, s16);
void func_800F7228_name_81(s32, s32, s32);
void func_800F7458_name_81(s32, f32, f32);
void func_800F76F8_name_81(s32, s32, s16, s32);
void func_800F79DC_name_81(s32);
void func_800F79E8_name_81(s32);
void func_800F8418_name_81(s32, s32, s32);
s32 func_800E1854_minigame(s32);

void func_80105E38_opdueltutorial(s16 model);
void func_801062E0_opdueltutorial(void);
void func_80106BF0_opdueltutorial(void);
void func_80108774_opdueltutorial(void);
void func_801087B4_opdueltutorial(omObjData *obj);
void func_80108810_opdueltutorial(omObjData *obj);
void func_80108880_opdueltutorial(void);
void func_80108908_opdueltutorial(void);
void func_80108854_opdueltutorial(void);
void func_801088C4_opdueltutorial(void);

void func_801059A0_opdueltutorial(void) {
    GW_PLAYER *player;
    s32 i;
    s32 j;

    D_80108C10_opdueltutorial = GwSystem.current_board_index = 6;
    omInitObjMan(50, 20);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightColorSet(2, 200, 200, 200);
    func_801088C4_opdueltutorial();
    func_80108854_opdueltutorial();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    HuWinInit();
    omAddPrcObj(func_80108774_opdueltutorial, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80108810_opdueltutorial);
    for (j = 0; j < 2; j++) {
        player = MBDGetPlayerStruct(j);
        player->stats.partners.frontID = -1;
        player->stats.partners.backID = -1;
    }
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80108A64_opdueltutorial[0]; j++) {
            D_80108B24_opdueltutorial[i][j + 1] = func_80017BB8_main(i, D_80108A64_opdueltutorial[j + 1]);
        }
    }
    GwPlayer[0].stat = 1;
    GwPlayer[1].stat = 1;
    GwPlayer[0].chr = 0;
    GwPlayer[1].chr = 1;
    func_8004A208_main();
}

s16 func_80105B54_opdueltutorial(s32 file, s32 flags) {
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
    func_80013390_main(model, -1, 0, func_80105E38_opdueltutorial);
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

s32 func_80105CD4_opdueltutorial(s16 model, f32 x, f32 y, f32 z) {
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

void func_80105E38_opdueltutorial(s16 model) {
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

s16 func_80106000_opdueltutorial(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    s16 animIdx;

    data = DataRead(file);
    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    D_80108C44_opdueltutorial = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_80108C46_opdueltutorial = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_8010610C_opdueltutorial(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_80108C46_opdueltutorial != 255) {
        if (animIdx == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            anim = &D_800D1714_main[D_80108C46_opdueltutorial];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_801061DC_opdueltutorial(s32 file) {
    void *data = DataRead(file);
    s16 id = func_800329B4_main(data);

    DataClose(data);
    return id;
}

void func_80106224_opdueltutorial(omObjData *obj) {
    s32 i;

    D_80108C1C_opdueltutorial->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        D_80108C14_opdueltutorial[i]->player_obj->coords.y = D_80108C1C_opdueltutorial->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_801062E0_opdueltutorial(void) {
    Object *shadow;
    omObjData *obj;
    s16 effect;
    s32 i;
    f32 scale;

    for (i = 0; i < 2; i++) {
        D_80108C14_opdueltutorial[i] = MBDGetPlayerStruct(i);
        func_800F3C98_name_81(i, D_80108B24_opdueltutorial[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_80108974_opdueltutorial[i]);
        func_800D8944_name_81(D_80108C14_opdueltutorial[i]->player_obj);
        D_80108C14_opdueltutorial[i]->stat |= PLAYER_UNK_04;
    }
    D_80108C1C_opdueltutorial = func_800D8314_name_81(0x1301FF, -1, 1.0f, 0, 0);
    HuVecCopyXYZ(&D_80108C1C_opdueltutorial->scale, 0.625f, 0.625f, 0.625f);
    shadow = func_800D8314_name_81(0x1301FD, -1, 1.0f, 0, 0);
    HuVecCopy3F(&D_80108C1C_opdueltutorial->coords, &D_80108944_opdueltutorial);
    HuVecCopy3F(&shadow->coords, &D_80108944_opdueltutorial);
    shadow->coords.y = 0;
    HuVecCopyXYZ(&shadow->scale, shadow->coords.y, shadow->coords.y, shadow->coords.y);
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 40.0f);
    func_800138EC_main(effect, 1, 0);
    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    HuAudFXPlay(0x2ED);
    while (D_80108C1C_opdueltutorial->coords.y >= 10.0f) {
        D_80108C1C_opdueltutorial->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            D_80108C14_opdueltutorial[i]->player_obj->coords.y -= 3.0f;
        }
        HuVecCopyXYZ(&shadow->scale,
                     0.625f - D_80108C1C_opdueltutorial->coords.y * 0.625f / 250.0f,
                     0.625f - D_80108C1C_opdueltutorial->coords.y * 0.625f / 250.0f,
                     0.625f - D_80108C1C_opdueltutorial->coords.y * 0.625f / 250.0f);
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_80106224_opdueltutorial);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = D_80108C1C_opdueltutorial->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x,
                       D_80108C1C_opdueltutorial->coords.y + 40.0f, D_80108C1C_opdueltutorial->coords.z);
    func_800138EC_main(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        func_800D8F0C_name_81(D_80108C14_opdueltutorial[i]->player_obj);
    }
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&D_80108C1C_opdueltutorial->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(effect);
    func_800D8F3C_name_81(D_80108C1C_opdueltutorial);
    func_800D8F3C_name_81(shadow);
    omDelObj(obj);
}

void func_80106808_opdueltutorial(omObjData *obj) {
    D_80108C1C_opdueltutorial->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

void func_8010686C_opdueltutorial(void) {
    Object *obj;
    void *data[2];
    s32 anim;
    s32 alpha;

    obj = func_800D8314_name_81(0x14000A, -1, 1.0f, 0, 0);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001F9E4_main(obj->omObj1->model[0], 255);
    data[0] = DataRead(0x130135);
    Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    data[1] = DataRead(0x140034);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 4, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuVecCopyXYZ(&obj->coords, 0, 150.0f, 500.0f);
    HuPrcSleep(15);
    func_80033430_main(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 3, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 2, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 1, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 0, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    func_80033430_main(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(5);
    for (alpha = 255; alpha > 0; alpha -= 10) {
        func_8001F9E4_main(obj->omObj1->model[0], alpha);
        HuPrcVSleep();
    }
    func_80033430_main(anim);
    DataClose(data[0]);
    DataClose(data[1]);
    func_800D8F3C_name_81(obj);
    omDelPrcObj(NULL);
}

void func_80106BF0_opdueltutorial(void) {
    Vec directions[2];
    s16 effects[2];
    omObjData *obj;
    s32 i;
    s32 j;
    s16 effect;
    f32 scale;
    f32 angle;
    f32 radius;
    f32 speed;

    MBDBackKill();
    MBDBackLoad(23);
    func_800E8180_name_81(1000.0f, 10000.0f);
    D_80108C28_opdueltutorial = func_800D8010_name_81(62, NULL);
    HuVecCopy3F(&D_80108C28_opdueltutorial->coords, &D_80108938_opdueltutorial);
    HuVecCopyXYZ(&D_80108C28_opdueltutorial->scale, 0.6f, 0.6f, 0.6f);
    D_80108C28_opdueltutorial->rot.x = sindf(10.0f);
    D_80108C28_opdueltutorial->rot.z = cosdf(10.0f);
    D_80108C28_opdueltutorial->flags |= 1;
    D_80108C2C_opdueltutorial = func_80060880_main(75, 197, 16);
    HuWinMesPalSet(D_80108C2C_opdueltutorial, 4, 0, 224, 224);
    HuWinMesSpeedSet(D_80108C2C_opdueltutorial, 0);
    D_80108C30_opdueltutorial[0] =
        func_80106000_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80108C30_opdueltutorial[1] = func_801061DC_opdueltutorial(0xA007F);
    D_80108C30_opdueltutorial[2] = func_801061DC_opdueltutorial(0xA0080);
    D_80108C30_opdueltutorial[3] = func_801061DC_opdueltutorial(0xA0081);
    D_80108C30_opdueltutorial[4] = func_801061DC_opdueltutorial(0xA0082);
    D_80108C30_opdueltutorial[5] = func_801061DC_opdueltutorial(0xA0083);
    D_80108C30_opdueltutorial[6] = func_801061DC_opdueltutorial(0xA0084);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    D_80108C1C_opdueltutorial = func_800D8010_name_81(59, D_80108B94_opdueltutorial);
    func_800461B4_main(D_80108C1C_opdueltutorial->omObj1->model[0]);
    HuVecCopy3F(&D_80108C1C_opdueltutorial->coords, &D_80108968_opdueltutorial);
    D_80108C1C_opdueltutorial->velocity.x = 900.0f;
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 15.0f, 20.0f, 8.0f);
    func_8000D018_main(effect, 200.0f);
    func_800138EC_main(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&D_80108C14_opdueltutorial[i]->player_obj->coords, &D_801089EC_opdueltutorial[i]);
        effects[i] = func_80105B54_opdueltutorial(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            func_80105CD4_opdueltutorial(effects[i], D_80108C14_opdueltutorial[i]->player_obj->coords.x,
                                         D_80108C14_opdueltutorial[i]->player_obj->coords.y + 50.0f,
                                         D_80108C14_opdueltutorial[i]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            func_800D8E88_name_81(D_80108C14_opdueltutorial[i]->player_obj);
            HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&D_80108C14_opdueltutorial[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(11);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2500, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    j = 0;
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_8010686C_opdueltutorial, 0x300, 0, 0));
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2501, -1, -1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    HuPrcChildWatch();
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2502, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[1]);
    HuAudFXPlay(0x2DD);
    func_800138EC_main(effect, 0, 1);
    angle = 0.0f;
    radius = 500.0f;
    while (D_80108C1C_opdueltutorial->velocity.x >= 300.0f) {
        D_80108C1C_opdueltutorial->coords.x = sindf(angle) * radius;
        D_80108C1C_opdueltutorial->coords.z = cosdf(angle) * radius + D_80108968_opdueltutorial.z;
        D_80108C1C_opdueltutorial->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x, D_80108C1C_opdueltutorial->velocity.x - 50.0f,
                           D_80108C1C_opdueltutorial->coords.z);
        j++;
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords,
                                      &D_801089A4_opdueltutorial[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->rot);
                func_800EBF2C_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords,
                                      &D_801089A4_opdueltutorial[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->coords, 20);
                func_800D90D0_name_81(D_80108C14_opdueltutorial[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                func_800EB708_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords,
                                      &D_80108968_opdueltutorial, &directions[i]);
                func_800EBC60_name_81(&D_80108C14_opdueltutorial[i]->player_obj->rot, &directions[i],
                                      &D_80108C14_opdueltutorial[i]->player_obj->rot, 10);
                func_800D918C_name_81(D_80108C14_opdueltutorial[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, func_80106808_opdueltutorial);
    obj->trans.y = D_80108C1C_opdueltutorial->velocity.x;
    func_800138EC_main(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&D_80108C14_opdueltutorial[i]->player_obj->coords,
                                                                &D_801089BC_opdueltutorial[i],
                                                                &D_80108C14_opdueltutorial[i]->player_obj->coords, 20));
        func_800D90D0_name_81(D_80108C14_opdueltutorial[i]->player_obj, 2, 2);
    }
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        func_800D918C_name_81(D_80108C14_opdueltutorial[i]->player_obj, -1, 0, 5, 2);
    }
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2503, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800138EC_main(effect, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    func_800EB7BC_name_81(&directions[0]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &directions[0],
                          &D_80108C14_opdueltutorial[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2504, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[0]->player_obj->coords, &D_80108C1C_opdueltutorial->coords,
                          &directions[0]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &directions[0],
                          &D_80108C14_opdueltutorial[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(effect, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    func_800EB7BC_name_81(&directions[1]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &directions[1],
                          &D_80108C14_opdueltutorial[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2505, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[1]->player_obj->coords, &D_80108C1C_opdueltutorial->coords,
                          &directions[1]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &directions[1],
                          &D_80108C14_opdueltutorial[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    func_800138EC_main(effect, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    D_80108C1C_opdueltutorial->rot.x = sindf(0.0f);
    D_80108C1C_opdueltutorial->rot.z = cosdf(0.0f);
    func_800138EC_main(effect, 1, 0);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2506, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    j = 0;
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[5]);
    HuAudFXPlay(0x2DE);
    func_800138EC_main(effect, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    while (TRUE) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
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
        D_80108C1C_opdueltutorial->rot.x = sindf(angle);
        D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    angle = 0.0f;
    D_80108C1C_opdueltutorial->rot.x = sindf(angle);
    D_80108C1C_opdueltutorial->rot.z = cosdf(angle);
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2507, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[6]);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 0);
    func_800F6390_name_81();
    {
        s16 positions[][2] = { { 30, 40 }, { 194, 40 } };

        func_800F6550_name_81(0, positions[0][0], positions[0][1]);
        func_800F6550_name_81(1, positions[1][0], positions[1][1]);
    }
    func_800F7458_name_81(0, 0.0f, 0.0f);
    func_800F7458_name_81(1, 0.0f, 0.0f);
    D_80108930_opdueltutorial = 1;
    func_800F79E8_name_81(0);
    func_800EFABC_name_81(D_80108C14_opdueltutorial[0]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 0, 2);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2508, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[3]);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 1);
    func_800F79E8_name_81(1);
    func_800EFABC_name_81(D_80108C14_opdueltutorial[1]->player_obj);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 0, 2);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[6]);
    HuAudFXPlay(0x2E3);
    omDelObj(obj);
    func_800138EC_main(effect, 0, 1);
    while (D_80108C1C_opdueltutorial->velocity.x < 800.0f) {
        D_80108C1C_opdueltutorial->velocity.x += 10.0f;
        func_8000CFA4_main(effect, D_80108C1C_opdueltutorial->coords.x, D_80108C1C_opdueltutorial->velocity.x - 50.0f,
                           D_80108C1C_opdueltutorial->coords.z);
        HuPrcVSleep();
    }
    func_800138EC_main(effect, 1, 0);
    func_8010610C_opdueltutorial(D_80108C28_opdueltutorial->omObj1->model[0], D_80108C30_opdueltutorial[0]);
    HuPrcSleep(10);
    {
        s32 models[] = { 0x25, 0x0C, 0x09, 0x0A, 0x26, 0x0B, 0x2C, 0x24 };
        s32 sounds[] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };

        for (i = 0; i < 2; i++) {
            D_80108C20_opdueltutorial[i] =
                func_800D8010_name_81(models[GwPlayer[i].chr], D_80108B74_opdueltutorial[GwPlayer[i].chr]);
            HuVecCopy3F(&D_80108C20_opdueltutorial[i]->coords, &D_80108A04_opdueltutorial[i]);
            HuAudFXPlay(sounds[GwPlayer[i].chr]);
        }
    }
    func_800D90D0_name_81(D_80108C20_opdueltutorial[0], 0, 2);
    func_800D90D0_name_81(D_80108C20_opdueltutorial[1], 0, 2);
    while (TRUE) {
        j = func_800EFE8C_name_81(D_80108C20_opdueltutorial[0], &D_80108A1C_opdueltutorial[0], 20.0f);
        if (func_800EFE8C_name_81(D_80108C20_opdueltutorial[1], &D_80108A1C_opdueltutorial[1], 20.0f) && j) {
            break;
        }
        HuPrcVSleep();
    }
    func_800EB7BC_name_81(&directions[0]);
    func_800EB7BC_name_81(&directions[1]);
    func_800EBC60_name_81(&D_80108C20_opdueltutorial[0]->rot, &directions[0], &D_80108C20_opdueltutorial[0]->rot, 10);
    func_800EBC60_name_81(&D_80108C20_opdueltutorial[1]->rot, &directions[1], &D_80108C20_opdueltutorial[1]->rot, 10);
    HuPrcSleep(10);
    func_800D90D0_name_81(D_80108C20_opdueltutorial[0], -1, 2);
    func_800D90D0_name_81(D_80108C20_opdueltutorial[1], -1, 2);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x2509, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[0]->player_obj->coords,
                          &D_80108C14_opdueltutorial[1]->player_obj->coords, &directions[0]);
    func_800EB708_name_81(&D_80108C14_opdueltutorial[1]->player_obj->coords,
                          &D_80108C14_opdueltutorial[0]->player_obj->coords, &directions[1]);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot, &directions[0],
                          &D_80108C14_opdueltutorial[0]->player_obj->rot, 5);
    func_800EBC60_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot, &directions[1],
                          &D_80108C14_opdueltutorial[1]->player_obj->rot, 5);
    HuPrcSleep(5);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x250A, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    {
        s32 choices[2];
        s32 window1;
        s32 window2;

        choices[0] = 0;
        choices[1] = 0;
        window1 = func_800E1824_name_81(20, 174, 1);
        window2 = func_800E1824_name_81(21, 188, 1);
        HuPrcSleep(20);
        choices[0] = 1;
        choices[1] = 2;
        func_800E1854_minigame(window1);
        func_800E1854_minigame(window2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], 0, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], 0, 2);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108A34_opdueltutorial[(choices[0] - 1) * 2],
                              &D_80108C20_opdueltutorial[0]->rot);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[1]->coords,
                              &D_80108A34_opdueltutorial[(choices[1] - 1) * 2 + 1], &D_80108C20_opdueltutorial[1]->rot);
        func_800EBF2C_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108A34_opdueltutorial[(choices[0] - 1) * 2],
                              &D_80108C20_opdueltutorial[0]->coords, 20);
        func_800EBF2C_name_81(&D_80108C20_opdueltutorial[1]->coords,
                              &D_80108A34_opdueltutorial[(choices[1] - 1) * 2 + 1],
                              &D_80108C20_opdueltutorial[1]->coords, 20);
        HuPrcSleep(20);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[0]->coords, &D_80108C14_opdueltutorial[1]->player_obj->coords,
                              &directions[0]);
        func_800EB708_name_81(&D_80108C20_opdueltutorial[1]->coords, &D_80108C14_opdueltutorial[0]->player_obj->coords,
                              &directions[1]);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[0]->rot, &directions[0], &D_80108C20_opdueltutorial[0]->rot,
                              10);
        func_800EBC60_name_81(&D_80108C20_opdueltutorial[1]->rot, &directions[1], &D_80108C20_opdueltutorial[1]->rot,
                              10);
        HuPrcSleep(10);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[0], -1, 2);
        func_800D90D0_name_81(D_80108C20_opdueltutorial[1], -1, 2);
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
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x250B, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    func_800F7228_name_81(0, 10, 1);
    func_800F7228_name_81(1, 10, 0);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[0]->player_obj->rot);
    func_800EB7BC_name_81(&D_80108C14_opdueltutorial[1]->player_obj->rot);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[0]->player_obj, 4, 0);
    func_800D90D0_name_81(D_80108C14_opdueltutorial[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    func_800D918C_name_81(D_80108C14_opdueltutorial[0]->player_obj, 0, 0, 5, 2);
    func_800D918C_name_81(D_80108C14_opdueltutorial[1]->player_obj, 0, 0, 5, 2);
    HuWinMesSet(D_80108C2C_opdueltutorial, 0x250C, -1, -1);
    func_80060C14_main(D_80108C2C_opdueltutorial, 1);
    func_800EF754_name_81(D_80108C2C_opdueltutorial);
    func_80060EA8_main(D_80108C2C_opdueltutorial, 1);
    HuWinExCleanup(D_80108C2C_opdueltutorial);
}

void func_80108774_opdueltutorial(void) {
    func_801062E0_opdueltutorial();
    func_80106BF0_opdueltutorial();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_801087B4_opdueltutorial(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80108908_opdueltutorial();
        func_80108880_opdueltutorial();
        HuWinAllKill();
        if (D_80108930_opdueltutorial != 0) {
            func_800F64FC_name_81();
        }
        omOvlReturnEx(1);
    }
}

void func_80108810_opdueltutorial(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        obj->func = func_801087B4_opdueltutorial;
    }
}

void func_80108854_opdueltutorial(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80108880_opdueltutorial(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
    if (D_80108934_opdueltutorial != NULL) {
        omDelPrcObj(D_80108934_opdueltutorial);
    }
}

void func_801088C4_opdueltutorial(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(30);
}

void func_80108908_opdueltutorial() {
    MBDBackKill();
    MBDBackClose();
}
