#include "common.h"
#include "game/process.h"
#include "malloc.h"

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} Duel10SprGroup; // sizeof 0x08

typedef struct Duel10CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel10CamShakeWork; // sizeof 0x10

typedef struct Duel10SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel10SpriteWork; // sizeof 0x10

extern Vec D_80105540_name_81;
extern u8 D_80100E20_name_81;

void func_800FC8C4_name_81(Vec *arg0);
extern void func_80105D2C_duel10(void);
extern void func_80106374_duel10(void);
extern void func_8010F620_duel10(void);
extern void func_8010FC2C_duel10(void);
extern omObjData *D_80114CCC_duel10;
extern Object *D_80114CDC_duel10;
extern Object *D_80114CE4_duel10;

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801059D0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105A58_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105B10_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105B64_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105BA0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105CD0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105D2C_duel10);

Process *func_80105F1C_duel10(Object *object) {
    Process *process;
    Duel10SpriteWork *work;

    process = omAddPrcObj(func_80105D2C_duel10, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80105F8C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010613C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801061C8_duel10);

void func_801062AC_duel10(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801062CC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010632C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106374_duel10);

Process *func_801064C8_duel10(s32 magnitude, s32 decay) {
    Process *process;
    Duel10CamShakeWork *work;

    process = omAddPrcObj(func_80106374_duel10, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106534_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801067AC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106840_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80106894_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801071F4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80107A24_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80107F28_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80108510_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801085BC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80109470_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801098F4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010A27C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010AB1C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ADB4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B020_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B19C_duel10);

s32 func_8010B4EC_duel10(void) {
    UnkDuelObjData *data = D_80114CCC_duel10->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B52C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B594_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B5A8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010B5B8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010BD40_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010CED4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010D490_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010D9C8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DA60_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DAE8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DB24_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DB60_duel10);

void func_8010DD5C_duel10(Duel10SprGroup *arg0) {
    HuSprAnimKill(arg0->sprites[0]);
    HuSprAnimKill(arg0->sprites[1]);
    HuSprAnimKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreePerm(arg0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010DDA4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E0EC_duel10);

void func_8010E258_duel10(void) {
}

void func_8010E260_duel10(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E268_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E31C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E338_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E37C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E408_duel10);

void func_8010E494_duel10(void) {
    D_80100E20_name_81 = 0;
    HuPrcChildWatch();
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E4B4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E8D4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010E8F4_duel10);

void func_8010EC1C_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 7;
}

void func_8010EC60_duel10(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ECA0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ED14_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ED50_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010ED98_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010EDF8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010EEE4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010EF98_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F070_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F114_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F1A8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F258_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F3D4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F474_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BBC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F620_duel10);

void func_8010F738_duel10(void) {
    omAddPrcObj(func_8010F620_duel10, 0xA, 0, 0);
}

void func_8010F764_duel10(void) {
    func_8001C814_main(D_80114CDC_duel10->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80114CDC_duel10->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F7B4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F864_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010F9E0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FA80_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FC2C_duel10);

void func_8010FD44_duel10(void) {
    omAddPrcObj(func_8010FC2C_duel10, 0xA, 0, 0);
}

void func_8010FD70_duel10(void) {
    func_8001C814_main(D_80114CE4_duel10->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80114CE4_duel10->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FDC0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8010FE0C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111D0C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111DC4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111E6C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80111FDC_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801127A8_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80112E74_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113644_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801136B4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801136F0_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113840_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113970_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80113AF4_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_80114140_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_8011450C_duel10);

INCLUDE_ASM("asm/nonmatchings/overlays/duel10/4461E0", func_801148D8_duel10);

s32 func_80114940_duel10(void) {
    s32 playerIndex = GwSystem.current_player_index;
    s32 otherIndex = (playerIndex + 1) & 1;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    GW_PLAYER *otherPlayer = MBDGetPlayerStruct(otherIndex);

    if (player->nlink == otherPlayer->clink && player->nidx == otherPlayer->cidx) {
        return 0;
    }
    return -1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BD8_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BF0_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114BFC_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C14_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C44_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C74_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C78_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114C80_duel10);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel10/4461E0", D_80114CA0_duel10);
