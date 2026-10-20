#include "common.h"
#include "game/pause.h"

extern u16 D_80106E80_mchar;
extern u8 D_80106E82_mchar;
extern s16 D_80106E84_mchar[];
extern char *D_80106E94_mchar[];
extern s16 D_80107116_mchar;
extern u8 D_8010711C_mchar;
extern u8 D_8010711D_mchar;
extern char D_80107950_mchar[];
extern s32 fontcolor;
extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern Vec D_80107A50_mchar;
extern s16 D_80107114_mchar;
extern s16 D_80107118_mchar;
extern s16 D_8010711A_mchar;
extern s32 D_80107120_mchar[];
extern s32 D_80107124_mchar[];
extern s32 D_80107A60_mchar[8][2];
extern s32 D_80107AA0_mchar[8][2];

f32 func_8002FC7C_main(D_800CCF58_main_Struct *, u16, f32, f32, f32);
void func_8004DEC8_main(s16);
void func_80045C2C_main(void);
void func_80106DF8_mchar(omObjData *arg0);
void func_80106D7C_mchar(void);
void func_80105B38_mchar(omObjData *arg0);
void func_80106898_mchar(omObjData *arg0);
void func_80106764_mchar(s16 arg0);
void func_80106E54_mchar(omObjData *arg0);
void func_8010654C_mchar(s16 arg0);
void func_80105C4C_mchar(omObjData *arg0);

void func_801059A0_mchar(void) {
    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        func_8004DEC8_main(D_800A1786_main);
        D_800A1786_main = -1;
    }
    omAddObj(0x2710, 0, 0, -1, func_80106DF8_mchar);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    func_80106D7C_mchar();
    omAddObj(0x7D0, 10, 10, -1, func_80105B38_mchar);
    omAddObj(0x7D0, 0, 0, -1, func_80106898_mchar);
    WipeCreateIn(0, 16);
    D_800CD280_main = 1;
    func_8001F38C_main(0xC0, 0xE0, 0xFF);
    func_80045C2C_main();
}

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

void func_80105C4C_mchar(omObjData *arg0) {
    HmfModel *model;
    HmfModel *newModel;

    if (D_8010711D_mchar != 0) {
        D_8010711D_mchar--;
        if (D_8010711D_mchar == 0) {
            func_8010654C_mchar(D_8010711A_mchar);
            func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
            func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        }
    }
    if ((u16)D_800D0590_main[0] & 0x8000) {
        D_80107116_mchar++;
        if (D_80107116_mchar >= 160) {
            D_80107116_mchar = 0;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D0590_main[0] & 0x4000) {
        D_80107116_mchar--;
        if (D_80107116_mchar < 0) {
            D_80107116_mchar = 159;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & 0x1000) {
        D_8010711C_mchar++;
    }
    if (D_800D5558_main[0] & 4) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        D_80107118_mchar++;
        if (D_80107118_mchar >= 2) {
            D_80107118_mchar = 0;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        newModel = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        newModel->unk02 = model->unk02;
        newModel->unk40 = model->unk40;
        newModel->unk03 = model->unk03;
        newModel->unk4C = model->unk4C;
        newModel->unk05 = model->unk05;
        newModel->unk04 = model->unk04;
    }
    if (D_800D5558_main[0] & 2) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        D_80107114_mchar++;
        if (D_80107114_mchar >= 8) {
            D_80107114_mchar = 0;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        func_8001F304_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], (s16)D_80107AA0_mchar[D_80107114_mchar][0]);
        func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & 1) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 4);
        D_80107114_mchar--;
        if (D_80107114_mchar < 0) {
            D_80107114_mchar = 7;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 4, 0);
        func_8001F304_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], (s16)D_80107AA0_mchar[D_80107114_mchar][0]);
        func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if ((u16)D_800D0590_main[1] & 0xC000) {
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        if ((u16)D_800D0590_main[1] & 0x4000) {
            model->unk03 |= 4;
        }
        model->unk03 &= 0xFE;
        model->unk40 = func_8002FC7C_main(&D_800CCF58_main[model->unk02], model->unk03, model->unk40, model->unk48, model->unk44 + model->unk44);
        model->unk4C = func_8002FC7C_main(&D_800CCF58_main[model->unk04], model->unk05, model->unk4C, model->unk54, model->unk50 + model->unk50);
        model->unk03 = (model->unk03 & 0xFB) | 1;
    }
    if ((D_800CDA7C_main[0] & 0x30) == 0x30) {
        D_80106E80_mchar = 1;
    }
    if (D_800D5558_main[1] & 0x1000) {
        D_80106E82_mchar = !D_80106E82_mchar;
    }
    if (D_80106E82_mchar != 0) {
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        fontcolor = 9;
        sprintf(D_80107950_mchar, "MOTIONNO.%3d <%s>", D_80107116_mchar, D_80106E94_mchar[D_80107116_mchar]);
        print8(24, 182, D_80107950_mchar);
        sprintf(D_80107950_mchar, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(24, 190, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(24, 198, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ZOOM:  %3.3f", CZoom);
        print8(24, 206, D_80107950_mchar);
        sprintf(D_80107950_mchar, "M_TIME:%d", (u16)model->unk40);
        print8(24, 214, D_80107950_mchar);
    }
}

void func_8010654C_mchar(s16 arg0) {
    s16 i;
    void *data;
    s16 flags;
    s32 *files0;
    s32 *files1;
    s32 offset;

    i = 0;
    offset = arg0;
    files0 = D_80107120_mchar;
    flags = 0x2AC;
    for (; i < 8; i++) {
        D_80107A60_mchar[i][0] = func_8000B108_main(files0[(i + offset) * 2], flags);
        files1 = D_80107124_mchar;
        func_80017790_main((s16)D_80107A60_mchar[i][0], 0, i, func_80017BB8_main(i, 0xA3));
        func_8001C514_main((s16)D_80107A60_mchar[i][0]);
        D_80107A60_mchar[i][1] = func_8000B108_main(files1[(i + offset) * 2], flags);
        func_80017790_main((s16)D_80107A60_mchar[i][1], 1, i, func_80017BB8_main(i, 0xA4));
        func_8001C514_main((s16)D_80107A60_mchar[i][1]);
        if (D_80107AA0_mchar[i][0] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][0]);
        }
        if (D_80107AA0_mchar[i][1] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][1]);
        }
        data = DataReadTemp(func_80017BB8_main(i, 0));
        D_80107AA0_mchar[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
        D_80107AA0_mchar[i][1] = -1;
        func_8001F304_main((s16)D_80107A60_mchar[i][0], (s16)D_80107AA0_mchar[i][0]);
    }
}

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
