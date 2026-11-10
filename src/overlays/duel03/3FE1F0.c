#include "common.h"

typedef struct Duel03CamShakeWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ s32 step;
    /* 0x08 */ char unk_08[0x8];
} Duel03CamShakeWork; // sizeof 0x10

typedef struct Duel03SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel03SpriteWork; // sizeof 0x10

void func_800FC8C4_name_81(Vec *arg0);
void *memcpy(void *, const void *, unsigned int);
extern Vec D_80105540_name_81;
extern s16 D_80117C18_duel03[];
extern void func_8010E1B8_duel03(void);
extern void func_80105CC4_duel03(void);
extern void func_8010630C_duel03(void);
extern void func_8010E7C4_duel03(void);
extern omObjData *D_801180DC_duel03;
extern Object *D_801180E8_duel03;
extern Object *D_801180F0_duel03;
void func_8010D9F8_duel03(void);
void func_800FF640_name_81(s32);
f32 func_800D76D0_name_81(Vec *);
void func_80100CEC_name_81(s32 padIdx);
s32 func_800E1824_name_81(s32, s32, s32);
s32 func_800E88FC_name_81(void);
void func_800E1854_name_81(s32);
extern s32 D_801180C0_duel03;
extern s32 D_801180C4_duel03;
extern s32 D_801180C8_duel03;
extern s32 D_801180CC_duel03;
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EC1E4_name_81(Vec *, Vec *, Vec *, f32);
void func_800EBF2C_name_81(Vec *, Vec *, Vec *);
Object *func_800D8010_name_81(s32, s32);
void func_800D8944_name_81(Object *);
void func_800D8F0C_name_81(Object *);
void func_800D8E88_name_81(void);
s16 MBDGetCurrentPlayerIndex(void);
void func_800F38DC_name_81(s32, s32, s32);
void func_8010FE9C_duel03(s32);

void func_801059D0_duel03(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel03(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_801180C0_duel03 = func_800E1824_name_81(0, 0xA0, 1);
    D_801180C4_duel03 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_801180C8_duel03 = func_800E1824_name_81(1, 0xBC, 1);
    D_801180CC_duel03 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel03(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_801180C0_duel03);
    func_800E1854_name_81(D_801180C4_duel03);
    func_800E1854_name_81(D_801180C8_duel03);
    func_800E1854_name_81(D_801180CC_duel03);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105B64_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105BA0_duel03);

void func_80105C68_duel03(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105CC4_duel03);

Process *func_80105EB4_duel03(Object *object) {
    Process *process;
    Duel03SpriteWork *work;

    process = omAddPrcObj(func_80105CC4_duel03, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel03SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80105F24_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801060D4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80106160_duel03);

void func_80106244_duel03(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

void func_80106264_duel03(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_801062C4_duel03(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010630C_duel03);

Process *func_80106460_duel03(s32 angle, s32 step) {
    Process *process;
    Duel03CamShakeWork *work;

    process = omAddPrcObj(func_8010630C_duel03, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel03CamShakeWork));
    process->user_data = work;
    work->angle = angle;
    work->step = step;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801064CC_duel03);

Object *func_80106744_duel03(s32 arg0) {
    Object *obj;

    obj = func_800D8010_name_81(arg0 & 0xFF, 0);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    func_800D8944_name_81(obj);
    func_800D8F0C_name_81(obj);
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    return obj;
}

void func_801067D8_duel03(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81();
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010682C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010718C_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117B20_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801079BC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80107EC0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801084A8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80108554_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80109408_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010988C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010A214_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AAB4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AD4C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010AFB8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B134_duel03);

s32 func_8010B484_duel03(void) {
    UnkDuelObjData *data = D_801180DC_duel03->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B4C4_duel03);

void func_8010B52C_duel03(void) {
    D_801180DC_duel03->work[0] = 1;
}

void func_8010B540_duel03(void) {
    D_801180DC_duel03->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010B550_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010BCD8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010CE6C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010D428_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010D960_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010D9F8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DA88_duel03);

void func_8010DB04_duel03(void) {
    Hu3DCamInit(1);
    func_8010D9F8_duel03();
    func_800FF640_name_81(1);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117B58_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117B64_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117B70_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117BA0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DB30_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DC08_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DCAC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DD40_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DDF0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010DF6C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E00C_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117BD8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E1B8_duel03);

void func_8010E2D0_duel03(void) {
    omAddPrcObj(func_8010E1B8_duel03, 0xA, 0, 0);
}

void func_8010E2FC_duel03(void) {
    func_8001C814_main(D_801180E8_duel03->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801180E8_duel03->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E34C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E3FC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E578_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E618_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E7C4_duel03);

void func_8010E8DC_duel03(void) {
    omAddPrcObj(func_8010E7C4_duel03, 0xA, 0, 0);
}

void func_8010E908_duel03(void) {
    func_8001C814_main(D_801180F0_duel03->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801180F0_duel03->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010E958_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EA1C_duel03);

s32 func_8010EA74_duel03(void) {
    return (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EAAC_duel03);

s16 func_8010EB54_duel03(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80117C18_duel03, sizeof(shakeAngles));
    return shakeAngles[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EBD4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EDF0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010EF60_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010F7D0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8010FE9C_duel03);

void func_801109B0_duel03(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_8010FE9C_duel03(0);
    }
}

void func_80110A0C_duel03(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 1 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_8010FE9C_duel03(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117BF0_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C00_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C18_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C30_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C3C_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C54_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117C84_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CB4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CB8_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CC0_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CE0_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117CE4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117DCC_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117EB4_duel03);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel03/3FE1F0", D_80117F9C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80110A70_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80111C30_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011221C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011230C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112348_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801123C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112400_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112480_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801127FC_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801129E8_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80112BD4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011340C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113704_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113740_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80113AE0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80114030_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011454C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011485C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80114D80_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801152E0_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_8011580C_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80115B18_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116000_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116C54_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116D84_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116EB4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80116FE4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80117124_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801171C4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_80117210_duel03);

void func_8011725C_duel03(void) {
}

s32 func_80117264_duel03(void) {
    s32 playerIndex = GwSystem.current_player_index;
    s32 otherIndex = (playerIndex + 1) & 1;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    GW_PLAYER *otherPlayer = MBDGetPlayerStruct(otherIndex);

    if (player->nlink != otherPlayer->clink) {
        return -1;
    }
    if (player->nidx != otherPlayer->cidx) {
        return -1;
    }
    return player->rev & 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801172D4_duel03);

INCLUDE_ASM("asm/nonmatchings/overlays/duel03/3FE1F0", func_801173F0_duel03);
