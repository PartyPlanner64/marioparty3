#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern u32 D_8010934C_opduel[];
extern u32 *D_8010940C_opduel[];
extern s32 D_80109200_opduel;
extern Process *D_80109204_opduel;
extern Object *D_80109208_opduel;
extern Object *D_8010920C_opduel;
extern omObjData *D_80109210_opduel;
extern s16 D_80109214_opduel;
extern Process *D_80109218_opduel;
extern UnkBoard4 *D_8010921C_opduel;
extern UnkBoard4 *D_80109220_opduel;
extern s32 D_80109228_opduel;
extern u8 D_80109570_opduel;
extern GW_PLAYER *D_80109574_opduel[2];

void func_80105E20_opduel(s16 model);
void func_80106070_opduel(omObjData *obj);
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
    HmfLightColorSet(1, 255, 255, 255);
    HmfLightColorSet(2, 200, 200, 200);
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
    hmf = HmfModelData[model].hmf;
    effect = HmfModelData[model].unkBC;
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
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
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
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
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
        func_800D8F3C_name_81(D_80109208_opduel);
        D_80109208_opduel = NULL;
    }
    if (D_8010920C_opduel != NULL) {
        func_800D8F3C_name_81(D_8010920C_opduel);
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
        func_800D8F0C_name_81(D_80109574_opduel[i]->player_obj);
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

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106350_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801066B8_opduel);

void func_80106CB4_opduel(omObjData *obj) {
    D_80109208_opduel->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_801094F0_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106D18_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80108FDC_opduel);

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
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
}

void func_8010911C_opduel(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    if (D_80109204_opduel != NULL) {
        omDelPrcObj(D_80109204_opduel);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109508_opduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109528_opduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_80109548_opduel);

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
