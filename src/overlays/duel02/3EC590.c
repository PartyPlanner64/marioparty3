#include "common.h"

typedef struct Duel02ModelWaitWork {
    /* 0x00 */ s32 index;
    /* 0x04 */ char unk_04[0xC];
} Duel02ModelWaitWork; // sizeof 0x10

typedef struct Duel02CamWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel02CamWork; // sizeof 0x10

typedef struct Duel02SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel02SpriteWork; // sizeof 0x10

void func_800FC8C4_name_81(Vec *);
void *memcpy(void *, const void *, unsigned int);
extern Vec D_80105540_name_81;
extern s16 D_80117158_duel02[];
extern void func_8010E1B8_duel02(void);
extern void func_80105CC4_duel02(void);
extern void func_8010630C_duel02(void);
extern void func_8010E7C4_duel02(void);
extern void func_8010EA68_duel02(void);
extern omObjData *D_8011761C_duel02;
extern Object *D_80117628_duel02;
extern Object *D_80117630_duel02;

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801059D0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105A58_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105B10_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105B64_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105BA0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105C68_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105CC4_duel02);

Process *func_80105EB4_duel02(Object *object) {
    Process *process;
    Duel02SpriteWork *work;

    process = omAddPrcObj(func_80105CC4_duel02, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105F24_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801060D4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80106160_duel02);

void func_80106244_duel02(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80106264_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801062C4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010630C_duel02);

Process *func_80106460_duel02(s32 magnitude, s32 decay) {
    Process *process;
    Duel02CamWork *work;

    process = omAddPrcObj(func_8010630C_duel02, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02CamWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801064CC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80106744_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801067D8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010682C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010718C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117070_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801079BC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80107EC0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801084A8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80108554_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80109408_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010988C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010A214_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010AAB4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010AD4C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010AFB8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B134_duel02);

s32 func_8010B484_duel02(void) {
    UnkDuelObjData *data = D_8011761C_duel02->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B4C4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B52C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B540_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B550_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010BCD8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010CE6C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D428_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D960_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D9F8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DA88_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DB04_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170A8_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170B4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170C0_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170F0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DB30_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DC08_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DCAC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DD40_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DDF0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DF6C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E00C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117128_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E1B8_duel02);

void func_8010E2D0_duel02(void) {
    omAddPrcObj(func_8010E1B8_duel02, 0xA, 0, 0);
}

void func_8010E2FC_duel02(void) {
    func_8001C814_main(D_80117628_duel02->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80117628_duel02->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E34C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E3FC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E578_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E618_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E7C4_duel02);

void func_8010E8DC_duel02(void) {
    omAddPrcObj(func_8010E7C4_duel02, 0xA, 0, 0);
}

void func_8010E908_duel02(void) {
    func_8001C814_main(D_80117630_duel02->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80117630_duel02->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010E958_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EA10_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EA68_duel02);

void func_8010EB40_duel02(s32 arg0) {
    Process *process;
    Duel02ModelWaitWork *work;

    process = omAddPrcObj(func_8010EA68_duel02, 0x1000, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02ModelWaitWork));
    process->user_data = work;
    work->index = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EB98_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EBC8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010ECB8_duel02);

s16 func_8010ED60_duel02(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80117158_duel02, sizeof(shakeAngles));
    return shakeAngles[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EDE0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010EFFC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010F16C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010F9DC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801100A8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80110BBC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80110C18_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117140_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117158_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117170_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_8011717C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117194_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171C4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171F4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801171F8_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117200_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117220_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117224_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_8011730C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801173F4_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801174DC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80110C7C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80111E3C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112428_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112518_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112554_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801125D0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011260C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011268C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112A08_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112BF4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112DE0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80113618_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80113910_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011394C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80113CEC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80114630_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80114B94_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801154DC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80115A54_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80115BDC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80115D64_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80115EE4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116064_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011611C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801161D4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116240_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011628C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801162F8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116344_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116370_duel02);

void func_8011639C_duel02(void) {
}

s32 func_801163A4_duel02(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116414_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116564_duel02);
