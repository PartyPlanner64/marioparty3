#include "common.h"

typedef struct Duel05CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel05CamShakeWork; // sizeof 0x10

typedef struct Duel05SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel05SpriteWork; // sizeof 0x10

void func_800FC8C4_name_81(Vec *arg0);
void *memcpy(void *, const void *, unsigned int);
extern Vec D_80105540_name_81;
extern s16 D_80115EB8_duel05[];
void func_8010E1C4_duel05(void);
extern void func_80105CD0_duel05(void);
extern void func_80106318_duel05(void);
extern void func_8010E7D0_duel05(void);
s16 MBDGetCurrentPlayerIndex(void);
void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx);
void func_800F8C68_name_81(s32 playerIndex);
extern omObjData *D_801163BC_duel05;
extern Object *D_801163C8_duel05;
extern Object *D_801163D0_duel05;

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801059D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105A58_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105B10_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105B64_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105BA0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105C74_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105CD0_duel05);

Process *func_80105EC0_duel05(Object *object) {
    Process *process;
    Duel05SpriteWork *work;

    process = omAddPrcObj(func_80105CD0_duel05, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105F30_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801060E0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010616C_duel05);

void func_80106250_duel05(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106270_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801062D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106318_duel05);

Process *func_8010646C_duel05(s32 magnitude, s32 decay) {
    Process *process;
    Duel05CamShakeWork *work;

    process = omAddPrcObj(func_80106318_duel05, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801064D8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106750_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801067E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80106838_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80107198_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801079C8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80107ECC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801084B4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80108560_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80109414_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80109898_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010A220_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AAC0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AD58_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010AFC4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B140_duel05);

s32 func_8010B490_duel05(void) {
    UnkDuelObjData *data = D_801163BC_duel05->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B4D0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B538_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B54C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010B55C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010BCE4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010CE78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010D434_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010D96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DA04_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DA94_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DB10_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DB3C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DC14_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DCB8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DD4C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DDFC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DF78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E018_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115E78_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E1C4_duel05);

void func_8010E2DC_duel05(void) {
    omAddPrcObj(func_8010E1C4_duel05, 0xA, 0, 0);
}

void func_8010E308_duel05(void) {
    func_8001C814_main(D_801163C8_duel05->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801163C8_duel05->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E358_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E408_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E584_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E624_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E7D0_duel05);

void func_8010E8E8_duel05(void) {
    omAddPrcObj(func_8010E7D0_duel05, 0xA, 0, 0);
}

void func_8010E914_duel05(void) {
    func_8001C814_main(D_801163D0_duel05->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801163D0_duel05->omObj1->model[0], 1.0f);
}

void func_8010E964_duel05(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010E96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EA00_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EAFC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EB58_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EC48_duel05);

s16 func_8010ECF0_duel05(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80115EB8_duel05, sizeof(shakeAngles));
    return shakeAngles[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010ED70_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EF8C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F0FC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010F96C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110038_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110B4C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110BA8_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EA0_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EB8_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115ED0_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EDC_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115EF4_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F24_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F54_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F58_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F60_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F80_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115F84_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011606C_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80116154_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_8011623C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80110C0C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80111DCC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801123B8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801124A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801124E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112560_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011259C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011261C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112998_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112B84_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80112D70_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801135A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801138A0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801138DC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80113C7C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114428_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114BD4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114D24_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114E74_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114E98_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114EBC_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114F10_duel05);

void func_80114F68_duel05(void) {
    if (GwSystem.current_turn & 1) {
        func_800ECD88_name_81(CUR_PLAYER, 0, 0);
    } else {
        func_800ECD88_name_81(CUR_PLAYER, 3, 0);
    }
    func_8001FDE8_main(MBDGetPlayerStruct(CUR_PLAYER)->player_obj->omObj1->model[0]);
    func_800F8C68_name_81(MBDGetCurrentPlayerIndex());
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80114FD8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011505C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115098_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801150D4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115120_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011514C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115198_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801151E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115230_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011525C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801152A8_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801152F4_duel05);

void func_80115370_duel05(void) {
}

s32 func_80115378_duel05(void) {
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

void func_801153E8_duel05(void) {
    s16 playerIndex = MBDGetCurrentPlayerIndex();
    GwSystem.boardData.halfWordBytes[playerIndex] = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011541C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011544C_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115468_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115550_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011566C_duel05);
