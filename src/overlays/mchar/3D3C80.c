#include "common.h"

extern u16 D_80106E80_mchar;
extern Vec D_80107A50_mchar;
extern s16 D_80107114_mchar;
extern s16 D_80107118_mchar;
extern s16 D_8010711A_mchar;
extern s32 D_80107A60_mchar[8][2];
extern s32 D_80107AA0_mchar[8][2];

void func_80106E54_mchar(omObjData *arg0);
void func_8010654C_mchar(s16 arg0);
void func_80105C4C_mchar(omObjData *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_801059A0_mchar);

void func_80105B38_mchar(omObjData *arg0) {
    s16 i;

    arg0->model[0] = -1;
    for (i = 0; i < 8; i++) {
        D_80107A60_mchar[i][0] = D_80107A60_mchar[i][1] =
            D_80107AA0_mchar[i][0] = D_80107AA0_mchar[i][1] = -1;
    }
    D_8010711A_mchar = 0;
    func_8010654C_mchar(0);
    func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
    func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
    arg0->func = func_80105C4C_mchar;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107160_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010716C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107178_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107184_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107190_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010719C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071A8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071B4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071C0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071CC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071D8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071E4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071F0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801071FC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107208_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107214_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107220_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010722C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107238_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107244_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107250_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010725C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107268_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107274_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107280_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010728C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107298_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072A4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072B0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072BC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072C8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072D4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072E0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072EC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801072F8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107304_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107310_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010731C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107328_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107334_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107340_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010734C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107358_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107364_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107370_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010737C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107388_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107394_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073A0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073AC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073B8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073C4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073D0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073DC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073E8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801073F4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107400_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010740C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107418_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107424_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107430_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010743C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107448_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107454_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107460_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010746C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107478_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107484_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107490_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010749C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074A8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074B4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074C0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074CC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074D8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074E4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074F0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801074FC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107508_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107514_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107520_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010752C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107538_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107544_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107550_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010755C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107568_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107574_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107580_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010758C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107598_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075A4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075B0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075BC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075C8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075D4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075E0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075EC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801075F8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107604_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107610_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010761C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107628_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107634_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107640_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010764C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107658_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107664_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107670_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010767C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107688_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107694_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076A0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076AC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076B8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076C4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076D0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076DC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076E8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801076F4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107700_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010770C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107718_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107724_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107730_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010773C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107748_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107754_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107760_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010776C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107778_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107784_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107790_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010779C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077A8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077B4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077C0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077CC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077D8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077E4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077F0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801077FC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107808_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107814_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107820_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010782C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107838_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107844_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107850_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010785C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107868_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107874_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107880_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_8010788C_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_80107898_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801078A4_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801078B0_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801078BC_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801078C8_mchar);

INCLUDE_RODATA("asm/nonmatchings/overlays/mchar/3D3C80", D_801078D4_mchar);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_80105C4C_mchar);

INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_8010654C_mchar);

void func_80106764_mchar(s16 arg0) {
    s16 i;
    void *data;

    for (i = 0; i < 8; i++) {
        if (D_80107AA0_mchar[i][1] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][1]);
        }
        D_80107AA0_mchar[i][1] = D_80107AA0_mchar[i][0];
        data = DataReadTemp(func_80017BB8_main(i, arg0));
        D_80107AA0_mchar[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
    }
    func_8001C624_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar],
                       (s16)D_80107AA0_mchar[D_80107114_mchar][0], 0, 10, 2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mchar/3D3C80", func_80106898_mchar);

void func_80106D7C_mchar(void) {
    D_80107A50_mchar.x = D_80107A50_mchar.y = D_80107A50_mchar.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov[0] = 45.0f;
}

void func_80106DF8_mchar(omObjData *arg0) {
    if ((D_80106E80_mchar != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(0, 8);
        arg0->func = func_80106E54_mchar;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106E54_mchar(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
