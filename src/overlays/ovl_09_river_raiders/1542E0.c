#include "common.h"
#include "math.h"
#include "game/esprite.h"
#include "game/hmfanim.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "overlays/minigame.h"

typedef struct RiverRaidersEntry {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 sprite;
    /* 0x42 */ s16 esp;
    /* 0x44 */ Vec pos;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ Vec unk_78;
} RiverRaidersEntry; // sizeof 0x84

extern s32 D_8010D3B8_river_raiders[];
extern f32 D_8010D3C4_river_raiders[];
extern f32 D_8010D570_river_raiders[4][3][16];
extern Vec2f D_8010D888_river_raiders[];
extern RiverRaidersEntry D_8010D9F0_river_raiders[100];
// D_8010D9F0_river_raiders[9].unk_04 and unk_06, addressed through their own symbols in some functions
extern s16 D_8010DE98_river_raiders;
extern s16 D_8010DE9A_river_raiders;
// D_8010D9F0_river_raiders[40].unk_18, addressed through its own symbol in some functions
extern f32 D_8010EEA8_river_raiders;
extern u8 D_800D6A90_main;
extern u8 D_80110D84_river_raiders;
extern u16 D_80110D88_river_raiders[2];
extern u8 D_80110D90_river_raiders;
extern u8 D_80110DBD_river_raiders;

void func_80105BA4_river_raiders(omObjData *obj);
void func_80105D1C_river_raiders(omObjData *obj);
void func_80105FA0_river_raiders(omObjData *obj);
void func_801060BC_river_raiders(omObjData *obj);
void func_80106244_river_raiders(omObjData *obj);
void func_80106448_river_raiders(omObjData *obj);
void func_801069A4_river_raiders(omObjData *obj);
void func_80106AF8_river_raiders(void);
void func_80106300_river_raiders(omObjData *);
void func_80108188_river_raiders(omObjData *);
void func_8010D268_river_raiders(void);

void func_801059A0_river_raiders(void) {
    func_8010D268_river_raiders();
}

f32 func_801059BC_river_raiders(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_river_raiders(void) {
    u32 i;
    RiverRaidersEntry *entry;

    for (i = 0, entry = D_8010D9F0_river_raiders; i < 100; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
        entry->sprite = -1;
        entry->esp = -1;
        entry->pos.x = entry->pos.y = entry->pos.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68 = 0.0f;
        entry->unk_6C = 0.0f;
        entry->unk_70 = 0.0f;
        entry->unk_74 = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105B04_river_raiders(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_river_raiders(u8 arg0) {
    D_80110D90_river_raiders = arg0;
}

f32 func_80105B88_river_raiders(f32 arg0, f32 *arg1, f32 arg2) {
    f32 prev = *arg1;

    *arg1 = prev - arg2;
    return arg0 + prev;
}

void func_80105BA4_river_raiders(omObjData *obj) {
    u32 row = obj->work[0] * 4;
    u32 col = obj->work[1] + 43;
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[row + col];

    switch (obj->work[0]) {
        case 0:
            if (obj->work[1] == 2) {
                if (D_80110D84_river_raiders / 10 != 0) {
                    espDispOn(entry->esp);
                    func_8000BD50_main(entry->esp, (u8)(D_80110D84_river_raiders / 10));
                }
            } else if (obj->work[1] == 3) {
                func_8000BD50_main(entry->esp, (u8)(D_80110D84_river_raiders % 10));
            }
            break;
        case 1:
            if (obj->work[1] == 2) {
                if (D_80110DBD_river_raiders / 10 != 0) {
                    espDispOn(entry->esp);
                    func_8000BD50_main(entry->esp, (u8)(D_80110DBD_river_raiders / 10));
                }
            } else if (obj->work[1] == 3) {
                func_8000BD50_main(entry->esp, (u8)(D_80110DBD_river_raiders % 10));
            }
            break;
    }
}

void func_80105D1C_river_raiders(omObjData *obj) {
    u32 row = obj->work[0] * 4;
    u32 col = obj->work[1] + 43;
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[row + col];

    switch (obj->work[1]) {
        case 0:
            entry->sprite = func_8000B838_main(0x2A0013);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, 0x1000);
            break;
        case 1:
            entry->sprite = func_8000B838_main(0x2A0012);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, 0x1000);
            break;
        case 2:
        case 3:
            entry->sprite = func_8000B838_main(0x31);
            entry->esp = espEntry(entry->sprite, 0, 0);
            espAttrSet(entry->esp, 0x1000);
            if (obj->work[1] == 2) {
                espDispOff(entry->esp);
            }
            break;
    }
    entry->pos.x = D_8010D888_river_raiders[obj->work[0] * 4 + obj->work[1]].x;
    entry->pos.y = D_8010D888_river_raiders[obj->work[0] * 4 + obj->work[1]].y;
    espPosSet(entry->esp, entry->pos.x, entry->pos.y);
    obj->func = func_80105BA4_river_raiders;
}

void func_80105EAC_river_raiders(void) {
    RiverRaidersEntry *entry;
    s32 row;
    s32 col;
    omObjData *obj;
    s16 i;
    s16 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            row = i * 4;
            col = j + 43;
            entry = &D_8010D9F0_river_raiders[row + col];
            obj = omAddObj(0x3DE, 1, 10, -1, func_80105D1C_river_raiders);
            obj->work[0] = i;
            obj->work[1] = j;
            entry->obj = obj;
        }
    }
}

void func_80105FA0_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[obj->work[0]];
    RiverRaidersEntry *cur;
    s16 i;

    obj->trans.z += 17.0f;
    if (obj->work[0] == 2) {
        for (i = 0; i < 3; i++) {
            cur = &D_8010D9F0_river_raiders[i];
            obj = cur->obj;
            if (obj->trans.z >= 1875.0f) {
                switch (i) {
                    case 0:
                        entry = &D_8010D9F0_river_raiders[2];
                        break;
                    case 1:
                        entry = &D_8010D9F0_river_raiders[0];
                        break;
                    case 2:
                        entry = &D_8010D9F0_river_raiders[1];
                        break;
                }
                obj->trans.z = entry->obj->trans.z - 1875.0f;
            }
        }
    }
}

void func_801060BC_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(D_8010D3B8_river_raiders[obj->work[0]], 0x288);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = D_8010D3C4_river_raiders[obj->work[0]];
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    func_8001C258_main(obj->model[0], 4, 0);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    obj->func = func_80105FA0_river_raiders;
}

void func_801061A0_river_raiders(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &D_8010D9F0_river_raiders[i];
        obj = omAddObj(0x1F4, 1, 10, -1, func_801060BC_river_raiders);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void func_80106244_river_raiders(omObjData *obj) {
    RiverRaidersEntry *water = &D_8010D9F0_river_raiders[40];

    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010EEA8_river_raiders += 1.5f;
    }
    func_8001E888_main(obj->model[0], 0.0f, water->unk_18, D_80110D88_river_raiders[0],
                       D_80110D88_river_raiders[1], "suki-m209_04_1_3", 0);
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_80106300_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2A0004, 0x2A8);
    func_8001FA68_main(obj->model[0]);
    func_8001F9E4_main(obj->model[0], 0x80);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C954_main(obj->model[0]);
    func_800335BC_main("209_water_00_DEF", D_80110D88_river_raiders);
    D_8010EEA8_river_raiders = 0.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->func = func_80106244_river_raiders;
}

void func_801063FC_river_raiders(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, func_80106300_river_raiders);
    obj->work[0] = 0;
    D_8010D9F0_river_raiders[40].obj = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_80106448_river_raiders(omObjData *obj) {
    omObjData *player = D_8010D9F0_river_raiders[9].obj;
    RiverRaidersEntry *entry;
    omObjData *boat;
    f32 x, y, z;
    f32 dx, dy, dz;
    f32 rotY, rotX;
    f32 dist;
    s16 frame;
    u8 i;

    x = y = z = 0.0f;
    for (i = 0; i < 3; i++) {
        entry = &D_8010D9F0_river_raiders[i + 6];
        boat = entry->obj;
        if (boat->work[2] != obj->work[0]) {
            continue;
        }
        switch (entry->unk_08) {
            case 0:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -D_8010D570_river_raiders[0][0][frame] * 5.0f + boat->trans.x;
                y = D_8010D570_river_raiders[0][1][frame] * 5.0f + boat->trans.y;
                z = -D_8010D570_river_raiders[0][2][frame] * 5.0f + boat->trans.z + 20.0f;
                break;
            case 1:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -D_8010D570_river_raiders[1][0][frame] * 5.0f + boat->trans.x;
                y = D_8010D570_river_raiders[1][1][frame] * 5.0f + boat->trans.y;
                z = -D_8010D570_river_raiders[1][2][frame] * 5.0f + boat->trans.z;
                break;
            case 2:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -D_8010D570_river_raiders[2][0][frame] * 5.0f + boat->trans.x;
                y = D_8010D570_river_raiders[2][1][frame] * 5.0f + boat->trans.y;
                z = -D_8010D570_river_raiders[2][2][frame] * 5.0f + boat->trans.z;
                break;
            case 3:
                frame = (s16)Hu3DData[boat->model[0]].motTime / 2;
                x = -D_8010D570_river_raiders[3][0][frame] * 5.0f + boat->trans.x;
                y = D_8010D570_river_raiders[3][1][frame] * 5.0f + boat->trans.y;
                z = -D_8010D570_river_raiders[3][2][frame] * 5.0f + boat->trans.z + 20.0f;
                break;
        }
        dx = x - player->trans.x;
        dy = y - (player->trans.y + 15.0f);
        dz = z - (player->trans.z + 60.0f);
        rotY = atan2df(dx, dz);
        rotX = atan2df(dy, sqrtf(dx * dx + dz * dz));
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        obj->rot.y = 0.0f;
        obj->scale.z = dist / 450.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
        obj->rot.y = rotY;
        obj->rot.x = -rotX;
        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->trans.x = player->trans.x;
        obj->trans.y = player->trans.y + 15.0f;
        obj->trans.z = player->trans.z + 60.0f;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
}

void func_801069A4_river_raiders(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x2A0000, 0x99);
    obj->trans.x = 0.0f;
    obj->trans.y = 15.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    func_8001C258_main(obj->model[0], 4, 0);
    obj->func = func_80106448_river_raiders;
}

void func_80106A54_river_raiders(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &D_8010D9F0_river_raiders[i + 3];
        obj = omAddObj(0x320, 1, 10, -1, func_801069A4_river_raiders);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106AF8_river_raiders);

void func_8010716C_river_raiders(void) {
    func_80106AF8_river_raiders();
}

void func_80107188_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[9];
    u16 player = obj->work[0];

    D_8010DE98_river_raiders = 0;
    if (--D_8010DE9A_river_raiders <= 0) {
        D_8010DE9A_river_raiders = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        func_8001C258_main(obj->model[5], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (entry->unk_06 < 31) {
        if (D_800CBB6E_main[GwPlayer[player].pad] < -29) {
            entry->unk_04 = 1;
        }
        if (D_800CBB6E_main[GwPlayer[player].pad] >= 30) {
            entry->unk_04 = 2;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801072FC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80107B14_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108188_river_raiders);

void func_80108574_river_raiders(void) {
    omObjData *obj;
    s16 i;
    u16 playerIndex = 0;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            continue;
        }
        switch (i) {
            case 0:
                playerIndex = 0;
                break;
            case 1:
                playerIndex = 1;
                break;
            case 2:
                playerIndex = 2;
                break;
            case 3:
                playerIndex = 3;
                break;
        }
        obj = omAddObj(0x2BC, 9, 0x3C, -1, func_80108188_river_raiders);
        obj->work[0] = playerIndex;
        D_8010D9F0_river_raiders[9].obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108678_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108ACC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80108F40_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_801093F0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010940C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010957C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80109C08_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010A6A8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ABA0_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ACD8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010BE88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C494_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C890_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C980_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA20_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA4C_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CA84_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CADC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CF00_river_raiders);

void func_8010D0F0_river_raiders(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D0F8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D268_river_raiders);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", D_8010D9BC_river_raiders);
