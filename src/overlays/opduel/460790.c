#include "common.h"
#include "../ovl_81_name/ovl_81.h"

extern u32 D_8010934C_opduel[];
extern u32 *D_8010940C_opduel[];
extern u8 D_80109570_opduel;

void func_80105E20_opduel(s16 model);
void func_80108FDC_opduel(void);
void func_801090AC_opduel(omObjData *obj);
void func_801090F8_opduel(void);
void func_80109158_opduel(void);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80105CBC_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80105E20_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80105FE8_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106070_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801061C4_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106294_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106350_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801066B8_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106CB4_opduel);

INCLUDE_RODATA("asm/nonmatchings/overlays/opduel/460790", D_801094F0_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80106D18_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80108FDC_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_80109050_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801090AC_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_801090F8_opduel);

INCLUDE_ASM("asm/nonmatchings/overlays/opduel/460790", func_8010911C_opduel);

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
