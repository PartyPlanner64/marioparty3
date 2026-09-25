#include "common.h"

typedef struct Duel04CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel04CamShakeWork; // sizeof 0x10

typedef struct Duel04SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel04SpriteWork; // sizeof 0x10

void func_800FC8C4_name_81(Vec *);
void *memcpy(void *, const void *, unsigned int);
extern Vec D_80105540_name_81;
extern s16 D_8011AFC4_duel04[];
void func_8010E1C4_duel04(void);
extern void func_80105CC4_duel04(void);
extern void func_8010E7D0_duel04(void);
extern void func_8010630C_duel04(void);
extern omObjData *D_8011B4FC_duel04;
extern Object *D_8011B508_duel04;
extern Object *D_8011B510_duel04;

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801059D0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105A58_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105B10_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105B64_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105BA0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105C68_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105CC4_duel04);

Process *func_80105EB4_duel04(Object *object) {
    Process *process;
    Duel04SpriteWork *work;

    process = omAddPrcObj(func_80105CC4_duel04, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel04SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105F24_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801060D4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80106160_duel04);

void func_80106244_duel04(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80106264_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801062C4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010630C_duel04);

Process *func_80106460_duel04(s32 magnitude, s32 decay) {
    Process *process;
    Duel04CamShakeWork *work;

    process = omAddPrcObj(func_8010630C_duel04, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel04CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801064CC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80106744_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801067D8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010682C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010718C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801079BC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80107EC0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801084A8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80108554_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80109408_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010988C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010A214_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010AAB4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010AD4C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010AFB8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B134_duel04);

s32 func_8010B484_duel04(void) {
    UnkDuelObjData *data = D_8011B4FC_duel04->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B4C4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B52C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B540_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B550_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010BCD8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010CE6C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010D428_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010D960_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010D9F8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DA88_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DB10_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DB3C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DC14_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DCB8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DD4C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DDFC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DF78_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E018_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E1C4_duel04);

void func_8010E2DC_duel04(void) {
    omAddPrcObj(func_8010E1C4_duel04, 0xA, 0, 0);
}

void func_8010E308_duel04(void) {
    func_8001C814_main(D_8011B508_duel04->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_8011B508_duel04->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E358_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E408_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E584_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E624_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E7D0_duel04);

void func_8010E8E8_duel04(void) {
    omAddPrcObj(func_8010E7D0_duel04, 0xA, 0, 0);
}

void func_8010E914_duel04(void) {
    func_8001C814_main(D_8011B510_duel04->omObj1->model[0], 1, 4);
    func_8001C92C_main(D_8011B510_duel04->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E964_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EA74_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EA94_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EAF0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EC0C_duel04);

s32 func_8010ECFC_duel04(void) {
    return (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010ED34_duel04);

s16 func_8010EDDC_duel04(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_8011AFC4_duel04, sizeof(shakeAngles));
    return shakeAngles[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EE5C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010F078_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010F1E8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010FA58_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110124_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110C38_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110C94_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110CF8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80111EB8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801124B0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801125A0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801125DC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112658_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112694_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112714_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112A90_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112C7C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112E68_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801136A0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80113998_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801139D4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80113D74_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80113F04_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011407C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801141DC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114294_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801143F8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801144E0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011463C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114724_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114884_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114950_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114AE4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114C60_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114DF4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80114F70_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801150D0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115188_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801152F0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801153D8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011553C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115624_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115780_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115834_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801159C4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115B3C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80115DA8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80116168_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801163C0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011678C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801169EC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80116DA0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80117004_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801173C8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801176F0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80117A14_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80117D38_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118060_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801180B4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118108_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011815C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801181B0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118204_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118258_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801182AC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118300_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011835C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801183B4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118410_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118468_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801184C4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011851C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118578_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801185D0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8011860C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118648_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118684_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801186C0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801186FC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118738_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118774_duel04);

void func_801187B0_duel04(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801187B8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118850_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80118D14_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80119840_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801198EC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80119910_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80119A30_duel04);
