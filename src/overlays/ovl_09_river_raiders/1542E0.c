#include "common.h"
#include "math.h"
#include "game/audio.h"
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
    /* 0x1C */ f32 unk_1C;
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

extern s16 D_8010D3B6_river_raiders;
extern s32 D_8010D3B8_river_raiders[];
extern f32 D_8010D3C4_river_raiders[];
extern s32 D_8010D3D0_river_raiders[];
extern f32 D_8010D570_river_raiders[4][3][16];
extern Vec2f D_8010D870_river_raiders[];
extern Vec2f D_8010D888_river_raiders[];
extern RiverRaidersEntry D_8010D9F0_river_raiders[100];
// D_8010D9F0_river_raiders[9].unk_04 and unk_06, addressed through their own symbols in some functions
// D_8010D9F0_river_raiders[6] onward, addressed through its own symbol in some functions
extern RiverRaidersEntry D_8010DD08_river_raiders[];
extern s16 D_8010DE98_river_raiders;
// D_8010D9F0_river_raiders[10] onward, addressed through its own symbol in some functions
extern RiverRaidersEntry D_8010DF18_river_raiders[];
extern s16 D_8010DE9A_river_raiders;
// D_8010D9F0_river_raiders[9].sprite and esp, addressed through their own symbols in some functions
extern s16 D_8010DED4_river_raiders;
extern s16 D_8010DED6_river_raiders;
// D_8010D9F0_river_raiders[40].unk_18, addressed through its own symbol in some functions
extern f32 D_8010EEA8_river_raiders;
extern f32 D_8010D9D0_river_raiders[3];
extern f32 D_8010D9DC_river_raiders[2];
extern s16 D_8010D9E4_river_raiders;
extern u8 D_8010D9E6_river_raiders;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern u8 D_80110D84_river_raiders;
extern u16 D_80110D88_river_raiders[2];
extern u8 D_80110D90_river_raiders;
extern u8 D_80110D91_river_raiders;
extern s16 D_80110D98_river_raiders[][5];
extern f32 D_80110DC8_river_raiders[3][2];
extern s16 D_80110DE0_river_raiders;
extern s16 D_80110DE2_river_raiders;
extern s16 D_80110DE4_river_raiders;
extern u8 D_80110DBA_river_raiders[];
extern u8 D_80110DBD_river_raiders;
extern s16 D_80110DBE_river_raiders;

void func_80105BA4_river_raiders(omObjData *obj);
void func_80105D1C_river_raiders(omObjData *obj);
void func_80105FA0_river_raiders(omObjData *obj);
void func_801060BC_river_raiders(omObjData *obj);
void func_80106244_river_raiders(omObjData *obj);
void func_80106448_river_raiders(omObjData *obj);
void func_801069A4_river_raiders(omObjData *obj);
void func_80106AF8_river_raiders(omObjData *obj);
void func_8010716C_river_raiders(omObjData *obj);
void func_80107188_river_raiders(omObjData *obj);
void func_801072FC_river_raiders(omObjData *obj);
void func_80107B14_river_raiders(omObjData *obj);
void func_80106300_river_raiders(omObjData *);
void func_80108188_river_raiders(omObjData *);
void func_8010C494_river_raiders(omObjData *obj);
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

#ifdef NON_MATCHING
// Target addresses the first unk_06 accesses through the entry pointer register instead of folding
// &D_8010D9F0_river_raiders[9] into absolute addresses.
void func_80106AF8_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[9];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *target;
    f32 dx, dz;
    f32 dist;
    f32 minDist;
    s16 best;
    s16 i;
    u8 dir;

    best = 0;
    minDist = 5000.0f;
    dir = 0;
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        func_8001C258_main(obj->model[5], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[5], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (entry->unk_06 < 31) {
        dir = rand8();
        if (((GwPlayer[player].cpu_difficulty == 0) & (dir < 30)) || ((GwPlayer[player].cpu_difficulty == 1) & (dir < 150)) ||
            ((GwPlayer[player].cpu_difficulty == 2) & (dir < 200)) || ((GwPlayer[player].cpu_difficulty == 3) & (dir < 255))) {
            // Dead stores; this switch only leaves behind the cpu_difficulty load seen in the target.
            switch (GwPlayer[player].cpu_difficulty) {
                case 0:
                    dist = 100.0f;
                    break;
                case 1:
                    dist = 150.0f;
                    break;
                case 2:
                    dist = 200.0f;
                    break;
                case 3:
                    dist = 300.0f;
                    break;
            }
            for (i = 19; i >= 0; i--) {
                cur = &D_8010DF18_river_raiders[i];
                target = cur->obj;
                dx = target->trans.x - obj->trans.x;
                dz = target->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (target->trans.z < obj->trans.z && target->trans.z > -1500.0f) {
                    if ((cur->unk_04 == 1) & (dist < minDist)) {
                        best = i;
                        minDist = dist;
                    }
                }
            }
            target = D_8010DF18_river_raiders[best].obj;
            if (target->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < target->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= target->trans.x + 50.0f + 30.0f && target->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
            minDist = 5000.0f;
            for (i = 23; i >= 20; i--) {
                cur = &D_8010DF18_river_raiders[i];
                target = cur->obj;
                dx = target->trans.x - obj->trans.x;
                dz = target->trans.z - obj->trans.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (target->trans.z < obj->trans.z && target->trans.z > -1500.0f) {
                    if ((cur->unk_04 == 1) & (dist < minDist)) {
                        best = i;
                        minDist = dist;
                    }
                }
            }
            target = D_8010DF18_river_raiders[best].obj;
            if (target->trans.x + 50.0f + 30.0f < obj->trans.x) {
                dir = 1;
            }
            if (obj->trans.x < target->trans.x - 50.0f - 30.0f) {
                dir = 2;
            }
            if (obj->trans.x <= target->trans.x + 50.0f + 30.0f && target->trans.x - 50.0f - 30.0f <= obj->trans.x) {
                dir = 0;
            }
        }
    }
    if (--entry->unk_0A <= 0) {
        entry->unk_0A = 0;
    }
    if (dir == 0) {
        entry->unk_04 = 0;
    }
    if (dir % 5 == 1 && entry->unk_0A == 0) {
        entry->unk_04 = 1;
        entry->unk_0A = 30;
    }
    if (dir % 5 == 2 && entry->unk_0A == 0) {
        entry->unk_04 = 2;
        entry->unk_0A = 30;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_80106AF8_river_raiders);
#endif

void func_8010716C_river_raiders(omObjData *obj) {
    func_80106AF8_river_raiders(obj);
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

void func_801072FC_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[9];

    switch (D_8010DE98_river_raiders) {
        case 0:
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (entry->unk_06 < 31) {
                if (entry->unk_08 == 1) {
                    Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                    entry->unk_08 = 0;
                }
            } else {
                D_80110DE4_river_raiders = -500;
                if (entry->unk_08 == 0) {
                    Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[1]].motId, 0, 1, 0);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 1, 0);
                    entry->unk_08 = 1;
                }
            }
            if (entry->unk_18 < 0.0f) {
                entry->unk_18 += 0.05;
            }
            if (entry->unk_18 > 0.0f) {
                entry->unk_18 -= 0.05;
            }
            if ((s16)entry->unk_18 == 0) {
                entry->unk_18 = 0.0f;
                obj->trans.x = (s16)obj->trans.x;
            }
            if (D_8010D9DC_river_raiders[1] < 0.0f) {
                D_8010D9DC_river_raiders[1] += 1.0f;
            }
            if (D_8010D9DC_river_raiders[1] > 0.0f) {
                D_8010D9DC_river_raiders[1] -= 1.0f;
            }
            if ((s16)D_8010D9DC_river_raiders[1] == 0) {
                D_8010D9DC_river_raiders[1] = 0.0f;
            }
            D_80110DE4_river_raiders -= 5;
            if (D_80110DE4_river_raiders < -300) {
                D_80110DE4_river_raiders = -300;
            }
            break;
        case 1:
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                entry->unk_08 = 0;
            }
            obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            if ((s16)obj->rot.z == 20.0f) {
                obj->rot.z = 19.0f;
            }
            if (entry->unk_18 > -5.0f) {
                entry->unk_18 -= 0.1f;
                if (entry->unk_18 < -5.0f) {
                    entry->unk_18 = -5.0f;
                }
            }
            D_8010D9DC_river_raiders[1] += 1.0f;
            if (D_8010D9DC_river_raiders[1] >= 10.0f) {
                D_8010D9DC_river_raiders[1] = 10.0f;
            }
            D_80110DE4_river_raiders += 5;
            if (D_80110DE4_river_raiders > 0) {
                D_80110DE4_river_raiders = 0;
            }
            break;
        case 2:
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 1, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 1, 2);
                entry->unk_08 = 0;
            }
            obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            if ((s16)obj->rot.z == 340.0f) {
                obj->rot.z = 341.0f;
            }
            if (entry->unk_18 < 5.0f) {
                entry->unk_18 += 0.1f;
                if (entry->unk_18 > 5.0f) {
                    entry->unk_18 = 5.0f;
                }
            }
            D_8010D9DC_river_raiders[1] -= 1.0f;
            if (D_8010D9DC_river_raiders[1] <= -10.0f) {
                D_8010D9DC_river_raiders[1] = -10.0f;
            }
            D_80110DE4_river_raiders += 5;
            if (D_80110DE4_river_raiders > 0) {
                D_80110DE4_river_raiders = 0;
            }
            break;
    }
    if (obj->trans.x + entry->unk_18 + 60.0f >= 580.0f || obj->trans.x + entry->unk_18 - 60.0f <= -580.0f) {
        entry->unk_18 = 0.0f;
    }
    obj->trans.x += entry->unk_18;
    if (D_80110DE0_river_raiders != -1) {
        HuAudFXPitchSet(D_80110DE0_river_raiders, D_80110DE4_river_raiders);
    }
    D_80110DC8_river_raiders[0][0] = obj->trans.x - 450.0f;
    D_80110DC8_river_raiders[0][1] = obj->trans.x + 150.0f;
    D_80110DC8_river_raiders[1][0] = obj->trans.x - 300.0f;
    D_80110DC8_river_raiders[1][1] = obj->trans.x + 300.0f;
    D_80110DC8_river_raiders[2][0] = obj->trans.x - 150.0f;
    D_80110DC8_river_raiders[2][1] = obj->trans.x + 450.0f;
}

void func_80107B14_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010D9F0_river_raiders[9];
    u16 player = obj->work[0];

    if (D_80110D90_river_raiders == 10) {
        if (D_80110DE0_river_raiders != -1) {
            func_8004AEF0_main(D_80110DE0_river_raiders, 30);
            D_80110DE0_river_raiders = -1;
        }
    } else if (D_80110DE0_river_raiders == -1) {
        D_80110DE0_river_raiders = HuAudFXPlay(D_8010D3B6_river_raiders);
    }
    switch (D_80110D90_river_raiders) {
        case 0:
        case 1:
            D_80110DE4_river_raiders = -300;
            if (D_80110DE0_river_raiders != -1) {
                HuAudFXPitchSet(D_80110DE0_river_raiders, -300);
            }
            break;
        case 2:
            if (D_80110DE2_river_raiders > 0) {
                if (GwPlayer[player].stat & 1) {
                    func_8010716C_river_raiders(obj);
                } else {
                    func_80107188_river_raiders(obj);
                }
                func_801072FC_river_raiders(obj);
            }
            break;
        case 3:
            D_80110DE4_river_raiders = -300;
            if (D_80110DE0_river_raiders != -1) {
                HuAudFXPitchSet(D_80110DE0_river_raiders, -300);
            }
            entry->unk_1C = 10.0f;
            if (++entry->unk_0C >= 20) {
                D_8010D9E6_river_raiders = 3;
            }
            if (obj->rot.z < 20.0f && obj->rot.z > 0.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, -1.0f);
            }
            if (obj->rot.z < 360.0f && obj->rot.z > 340.0f) {
                obj->rot.z = func_801059BC_river_raiders(obj->rot.z, 1.0f);
            }
            if ((s16)obj->rot.z == 0.0f) {
                obj->rot.z = 0.0f;
            }
            if (entry->unk_08 == 1) {
                Hu3DMotionShiftSet(obj->model[5], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                entry->unk_08 = 0;
            }
            if (D_8010D9DC_river_raiders[1] < 0.0f) {
                D_8010D9DC_river_raiders[1] += 1.0f;
            }
            if (D_8010D9DC_river_raiders[1] > 0.0f) {
                D_8010D9DC_river_raiders[1] -= 1.0f;
            }
            if ((s16)D_8010D9DC_river_raiders[1] == 0) {
                D_8010D9DC_river_raiders[1] = 0.0f;
            }
            break;
        case 5:
        case 10:
            if (D_80110D84_river_raiders != 0) {
                if (entry->unk_16 == 0) {
                    PlayerFXPlay(0x28F, obj->work[0]);
                    entry->unk_16 = 1;
                }
                if (entry->unk_0E <= 0) {
                    obj->trans.y = func_80105B88_river_raiders(obj->trans.y, &entry->unk_1C, 1.0f);
                    if (entry->unk_1C < -10.0f) {
                        entry->unk_1C = 10.0f;
                        entry->unk_0E = 5;
                    }
                }
                if (entry->unk_0E > 0) {
                    entry->unk_0E--;
                }
                if (obj->trans.y <= 1.0f) {
                    func_8001C258_main(obj->model[2], 4, 0);
                    func_8001C258_main(obj->model[3], 4, 0);
                } else {
                    func_8001C258_main(obj->model[2], 4, 4);
                    func_8001C258_main(obj->model[3], 4, 4);
                }
            }
            break;
    }
    switch (GwPlayer[obj->work[0]].chr) {
        case 0:
        case 1:
        case 6:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z + 40.0f);
            break;
        default:
            Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
            break;
    }
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, D_8010D9DC_river_raiders[0], obj->rot.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], obj->rot.x, D_8010D9DC_river_raiders[1], 0.0f);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[4], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_80108188_river_raiders(omObjData *obj) {
    s8 chr = GwPlayer[obj->work[0]].chr;

    obj->model[5] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x6A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x27));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x28));
    func_8001C5B4_main(obj->model[5], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[5], 0.0f);
    func_8001C814_main(obj->model[5], 2, 2);
    Hu3DModelRemakeStatic(obj->model[5]);
    func_8001C514_main(obj->model[5]);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[5], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[5], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = func_8000B108_main(0x2A0008, 0x4B9);
    func_8000B460_main(obj, 2, 0x2A0009);
    func_8000B460_main(obj, 3, 0x2A000A);
    func_8001C5B4_main(obj->model[1], obj->motion[2]);
    Hu3DMotionTimeSet(obj->model[1], 0.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 20.0f);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[2] = func_8000B108_main(0x2A0010, 0x4A9);
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y - 32.5f, obj->trans.z + 50.0f);
    obj->model[3] = func_8000B108_main(0x2A0011, 0x4A9);
    func_8001C814_main(obj->model[3], 2, 2);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->model[4] = func_8000B0A0_main(0, 0x4A9);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 0.0f, obj->trans.z + 20.0f);
    Hu3DModelScaleSet(obj->model[4], 2.0f, 2.0f, 2.0f);
    func_8001C2FC_main(obj->model[4], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[4]);
    func_8001C514_main(obj->model[4]);
    D_8010DED4_river_raiders = func_8000B838_main(D_8010D3D0_river_raiders[chr]);
    D_8010DED6_river_raiders = espEntry(D_8010DED4_river_raiders, 0, 0);
    espAttrSet(D_8010DED6_river_raiders, 0x1000);
    espPosSet(D_8010DED6_river_raiders, 30, 210);
    espScaleSet(D_8010DED6_river_raiders, 1.0f, 1.0f);
    D_80110DE4_river_raiders = -300;
    obj->func = func_80107B14_river_raiders;
}

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

void func_80108678_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    RiverRaidersEntry *cur;
    omObjData *other;
    f32 x;
    s16 hit;
    s16 i;
    s16 j;

    for (i = 0; i < 5; i++) {
        D_80110D98_river_raiders[obj->work[1]][i] = 0;
    }
    x = obj->trans.x + entry->unk_18;
    entry->unk_12 = 0;
    if (x - 65.0f < D_80110DC8_river_raiders[obj->work[2]][0]) {
        D_80110D98_river_raiders[obj->work[1]][3] = 1;
    }
    if (x + 65.0f > D_80110DC8_river_raiders[obj->work[2]][1]) {
        D_80110D98_river_raiders[obj->work[1]][3] = 2;
    }
    hit = 0;
    for (i = 0; i < 3; i++) {
        if (i != obj->work[1]) {
            cur = &D_8010DD08_river_raiders[i];
            other = cur->obj;
            switch (entry->unk_08) {
                case 1:
                    if (x + 65.0f + entry->unk_12 * 4.5f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                case 2:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f - entry->unk_12 * 4.5f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                default:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
            }
            if (hit == 1) {
                break;
            }
        }
    }
    hit = 0;
    for (j = 0; j < 3; j++) {
        if (j != obj->work[1] && j != i) {
            other = D_8010DD08_river_raiders[j].obj;
            switch (entry->unk_08) {
                case 1:
                    if (x + 65.0f + entry->unk_12 * 4.5f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                case 2:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f - entry->unk_12 * 4.5f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
                default:
                    if (x + 65.0f > other->trans.x - 65.0f && x - 65.0f < other->trans.x + 65.0f) {
                        D_80110D98_river_raiders[obj->work[1]][i] = 1;
                        hit = 1;
                    }
                    break;
            }
            if (hit == 1) {
                break;
            }
        }
    }
    if (x + 65.0f > 580.0f) {
        D_80110D98_river_raiders[obj->work[1]][4] = 1;
    }
    if (x - 65.0f < -580.0f) {
        D_80110D98_river_raiders[obj->work[1]][4] = 2;
    }
}

void func_80108ACC_river_raiders(void) {
    RiverRaidersEntry *entry;
    RiverRaidersEntry *other;
    omObjData *obj;
    omObjData *otherObj;
    s16 iter;
    s16 changed;
    s16 count;
    s16 i;
    s16 j;

    iter = 0;
    do {
        changed = 0;
        for (i = 0; i < 3; i++) {
            entry = &D_8010DD08_river_raiders[i];
            obj = entry->obj;
            for (j = 0; j < 3; j++) {
                if (j == i) {
                    continue;
                }
                if (D_80110D98_river_raiders[i][j] != 1) {
                    continue;
                }
                other = &D_8010DD08_river_raiders[j];
                otherObj = other->obj;
                if (other->unk_18 < 0.5f && other->unk_18 > -0.5f && D_80110D98_river_raiders[j][3] == 0 &&
                    D_80110D98_river_raiders[j][4] == 0) {
                    other->unk_18 = entry->unk_18;
                    changed = 1;
                }
                if (obj->trans.x > otherObj->trans.x) {
                    if (entry->unk_18 < 0.0f) {
                        entry->unk_18 = -entry->unk_18;
                        changed = 1;
                    } else if (entry->unk_18 < 0.5f && entry->unk_18 > -0.5f) {
                        entry->unk_18 = fabsf(other->unk_18);
                        changed = 1;
                    }
                } else {
                    if (entry->unk_18 > 0.0f) {
                        entry->unk_18 = -entry->unk_18;
                        changed = 1;
                    } else if (entry->unk_18 < 0.5f && entry->unk_18 > -0.5f) {
                        entry->unk_18 = -fabs(other->unk_18);
                        changed = 1;
                    }
                }
            }
            for (j = 0, count = 0; j < 3; j++) {
                if (j != i && D_80110D98_river_raiders[i][j] == 1) {
                    count++;
                }
            }
            if (count >= 2) {
                changed = 1;
            }
            if (D_80110D98_river_raiders[obj->work[1]][3] == 1) {
                obj->trans.x = D_80110DC8_river_raiders[obj->work[2]][0] + 65.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (D_80110D98_river_raiders[obj->work[1]][3] == 2) {
                obj->trans.x = D_80110DC8_river_raiders[obj->work[2]][1] - 65.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (D_80110D98_river_raiders[obj->work[1]][4] == 1) {
                obj->trans.x = 515.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            if (D_80110D98_river_raiders[obj->work[1]][4] == 2) {
                obj->trans.x = -515.0f;
                entry->unk_18 = 0.0f;
                changed = 1;
            }
            func_80108678_river_raiders(obj);
        }
    } while (++iter < 21 && changed != 0);
    for (i = 0; i < 3; i++) {
        entry = &D_8010DD08_river_raiders[i];
        obj = entry->obj;
        obj->trans.x += entry->unk_18;
    }
}

void func_80108F40_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *target;
    f32 range;
    s16 i;
    u8 dir;

    range = 0.0f;
    dir = 0;
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (entry->unk_06 == 0) {
        dir = rand8();
        if (((GwPlayer[player].cpu_difficulty == 0) & (dir < 100)) ||
            ((GwPlayer[player].cpu_difficulty == 1) & (dir < 150)) ||
            ((GwPlayer[player].cpu_difficulty == 2) & (dir < 200)) ||
            ((GwPlayer[player].cpu_difficulty == 3) & (dir < 255))) {
            switch (GwPlayer[player].cpu_difficulty) {
                case 0:
                    range = 100.0f;
                    break;
                case 1:
                    range = 150.0f;
                    break;
                case 2:
                    range = 200.0f;
                    break;
                case 3:
                    range = 300.0f;
                    break;
            }
            for (i = 19; i >= 0; i--) {
                cur = &D_8010DF18_river_raiders[i];
                target = cur->obj;
                if (target->trans.z < obj->trans.z && target->trans.x < range + obj->trans.x &&
                    obj->trans.x - range < target->trans.x && cur->unk_04 == 1) {
                    if (target->trans.x < obj->trans.x) {
                        dir = 1;
                    }
                    if (target->trans.x > obj->trans.x) {
                        dir = 2;
                    }
                }
            }
            for (i = 23; i >= 20; i--) {
                cur = &D_8010DF18_river_raiders[i];
                target = cur->obj;
                if (target->trans.z < obj->trans.z && target->trans.x < range + obj->trans.x &&
                    obj->trans.x - range < target->trans.x && cur->unk_04 == 1 && target->trans.z > -100.0f) {
                    if (target->trans.x < obj->trans.x) {
                        dir = 1;
                    }
                    if (target->trans.x > obj->trans.x) {
                        dir = 2;
                    }
                }
            }
        }
    }
    if (--entry->unk_0A <= 0) {
        entry->unk_0A = 0;
    }
    if (dir == 0) {
        entry->unk_04 = 0;
    }
    if (dir % 5 == 1 && entry->unk_0A == 0) {
        entry->unk_04 = 1;
        entry->unk_0A = 30;
    }
    if (dir % 5 == 2 && entry->unk_0A == 0) {
        entry->unk_04 = 2;
        entry->unk_0A = 30;
    }
}

void func_801093F0_river_raiders(omObjData *obj) {
    func_80108F40_river_raiders(obj);
}

void func_8010940C_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    u16 player = obj->work[0];

    entry->unk_04 = 0;
    if (--entry->unk_06 <= 0) {
        entry->unk_06 = 0;
    }
    if ((u16)(entry->unk_06 % 3) < 2) {
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[1], 4, 0);
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (entry->unk_06 == 0) {
        if (D_800CBB6E_main[GwPlayer[player].pad] < -29) {
            entry->unk_04 = 1;
        }
        if (D_800CBB6E_main[GwPlayer[player].pad] >= 30) {
            entry->unk_04 = 2;
        }
    }
}

void func_8010957C_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    omObjData *player = D_8010DD08_river_raiders[3].obj;

    switch (entry->unk_04) {
        case 0:
            if (entry->unk_06 <= 0) {
                if (entry->unk_08 != 0) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 2);
                    entry->unk_08 = 0;
                    entry->unk_12 = 0;
                }
            } else if (entry->unk_08 != 3) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 10, 1);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 1);
                entry->unk_08 = 3;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 < 0.0f) {
                entry->unk_18 += 0.05;
            }
            if (entry->unk_18 > 0.0f) {
                entry->unk_18 -= 0.05;
            }
            if ((s16)entry->unk_18 == 0 && entry->unk_18 < 0.3f && entry->unk_18 > -0.3f) {
                if (((f32)obj->work[2] - 1.0f) * 300.0f + player->trans.x < obj->trans.x) {
                    entry->unk_18 = -0.5f;
                }
                if (((f32)obj->work[2] - 1.0f) * 300.0f + player->trans.x > obj->trans.x) {
                    entry->unk_18 = 0.5f;
                }
            }
            if (D_8010D9D0_river_raiders[obj->work[1]] < 0.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] += 1.0f;
            }
            if (D_8010D9D0_river_raiders[obj->work[1]] > 0.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] -= 1.0f;
            }
            if ((s16)D_8010D9D0_river_raiders[obj->work[1]] == 0) {
                D_8010D9D0_river_raiders[obj->work[1]] = 0.0f;
            }
            break;
        case 1:
            if (entry->unk_08 != 2) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 2);
                entry->unk_08 = 2;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 > -7.0f) {
                entry->unk_18 -= 0.3f;
                if (entry->unk_18 < -7.0f) {
                    entry->unk_18 = -7.0f;
                }
            }
            D_8010D9D0_river_raiders[obj->work[1]] += 3.0f;
            if (D_8010D9D0_river_raiders[obj->work[1]] >= 20.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] = 20.0f;
            }
            break;
        case 2:
            if (entry->unk_08 != 1) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
                entry->unk_08 = 1;
                entry->unk_12 = 0;
            }
            if (entry->unk_18 < 7.0f) {
                entry->unk_18 += 0.3f;
                if (entry->unk_18 > 7.0f) {
                    entry->unk_18 = 7.0f;
                }
            }
            D_8010D9D0_river_raiders[obj->work[1]] -= 3.0f;
            if (D_8010D9D0_river_raiders[obj->work[1]] <= -20.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] = -20.0f;
            }
            break;
    }
    func_80108678_river_raiders(obj);
}

void func_80109C08_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    u16 player = obj->work[0];
    RiverRaidersEntry *cur;
    omObjData *boat;
    s16 i;

    switch (D_80110D90_river_raiders) {
        case 2:
            if (D_80110DE2_river_raiders > 0) {
                if (GwPlayer[player].stat & 1) {
                    func_801093F0_river_raiders(obj);
                } else {
                    func_8010940C_river_raiders(obj);
                }
                func_8010957C_river_raiders(obj);
            }
            break;
        case 3:
            entry->unk_1C = 10.0f;
            if (entry->unk_08 != 0) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 2);
                entry->unk_08 = 0;
            }
            if (D_8010D9D0_river_raiders[obj->work[1]] < 0.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] += 1.0f;
            }
            if (D_8010D9D0_river_raiders[obj->work[1]] > 0.0f) {
                D_8010D9D0_river_raiders[obj->work[1]] -= 1.0f;
            }
            if ((s16)D_8010D9D0_river_raiders[obj->work[1]] == 0) {
                D_8010D9D0_river_raiders[obj->work[1]] = 0.0f;
            }
            break;
        case 5:
        case 10:
            if (D_80110DBD_river_raiders != 0) {
                if (entry->unk_16 == 0) {
                    PlayerFXPlay(0x28F, obj->work[0]);
                    entry->unk_16 = 1;
                }
                switch (D_80110DBE_river_raiders) {
                    case -1:
                        if (entry->unk_08 != 2) {
                            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
                            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 2);
                            entry->unk_08 = 2;
                        }
                        if (D_8010D9E4_river_raiders > 0) {
                            obj->trans.x -= 10.0f;
                        } else {
                            obj->trans.x -= 0.0f;
                        }
                        D_8010D9D0_river_raiders[obj->work[1]] += 3.0f;
                        if (D_8010D9D0_river_raiders[obj->work[1]] >= 20.0f) {
                            D_8010D9D0_river_raiders[obj->work[1]] = 20.0f;
                        }
                        break;
                    case 1:
                        if (entry->unk_08 != 1) {
                            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
                            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
                            entry->unk_08 = 1;
                        }
                        if (D_8010D9E4_river_raiders > 0) {
                            obj->trans.x += 10.0f;
                        } else {
                            obj->trans.x += 0.0f;
                        }
                        D_8010D9D0_river_raiders[obj->work[1]] -= 3.0f;
                        if (D_8010D9D0_river_raiders[obj->work[1]] <= -20.0f) {
                            D_8010D9D0_river_raiders[obj->work[1]] = -20.0f;
                        }
                        break;
                }
                if (obj->trans.y <= 1.0f) {
                    func_8001C258_main(obj->model[2], 4, 0);
                } else {
                    func_8001C258_main(obj->model[2], 4, 4);
                }
                if (obj->work[1] == 2) {
                    if (--D_8010D9E4_river_raiders <= 0) {
                        for (i = 0; i < 3; i++) {
                            cur = &D_8010DD08_river_raiders[i];
                            boat = cur->obj;
                            boat->trans.y = func_80105B88_river_raiders(boat->trans.y, &cur->unk_1C, 1.0f);
                        }
                        D_8010D9E4_river_raiders = 0;
                        if ((s16)obj->trans.y == 0.0f) {
                            for (i = 0; i < 3; i++) {
                                cur = &D_8010DD08_river_raiders[i];
                                cur->unk_1C = 10.0f;
                            }
                            D_8010D9E4_river_raiders = 30;
                        }
                    }
                    for (i = 0; i < 3; i++) {
                        cur = &D_8010DD08_river_raiders[i];
                        boat = cur->obj;
                        if (boat->work[2] == 0 && boat->trans.x - 65.0f <= -580.0f) {
                            D_80110DBE_river_raiders = 1;
                        }
                        if (boat->work[2] == 2 && boat->trans.x + 65.0f >= 580.0f) {
                            D_80110DBE_river_raiders = -1;
                        }
                    }
                }
            }
            if (D_80110DBD_river_raiders == 0) {
                if (entry->unk_08 != 3) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 10, 1);
                    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 1);
                    entry->unk_08 = 3;
                }
                switch (D_80110DBE_river_raiders) {
                    case -1:
                        entry->unk_0C++;
                        obj->trans.x -= 3.0f;
                        D_8010D9D0_river_raiders[obj->work[1]] += 3.0f;
                        if (D_8010D9D0_river_raiders[obj->work[1]] >= 20.0f) {
                            D_8010D9D0_river_raiders[obj->work[1]] = 20.0f;
                        }
                        break;
                    case 1:
                        entry->unk_0C++;
                        obj->trans.x += 3.0f;
                        D_8010D9D0_river_raiders[obj->work[1]] -= 3.0f;
                        if (D_8010D9D0_river_raiders[obj->work[1]] <= -20.0f) {
                            D_8010D9D0_river_raiders[obj->work[1]] = -20.0f;
                        }
                        break;
                }
                if (obj->work[1] == 2) {
                    for (i = 0; i < 3; i++) {
                        cur = &D_8010DD08_river_raiders[i];
                        boat = cur->obj;
                        if (boat->work[2] == 0 && boat->trans.x - 65.0f <= -580.0f) {
                            D_80110DBE_river_raiders = 1;
                            entry->unk_0C = 0;
                        }
                        if (boat->work[2] == 2 && boat->trans.x + 65.0f >= 580.0f) {
                            D_80110DBE_river_raiders = -1;
                            entry->unk_0C = 0;
                        }
                    }
                    if (entry->unk_0C >= 30) {
                        D_80110DBE_river_raiders *= -1;
                        for (i = 0; i < 3; i++) {
                            entry->unk_0C = 0;
                        }
                    }
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], obj->rot.x, D_8010D9D0_river_raiders[obj->work[1]], obj->rot.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[3], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_8010A6A8_river_raiders(omObjData *obj) {
    RiverRaidersEntry *entry = &D_8010DD08_river_raiders[obj->work[1]];
    s8 chr = GwPlayer[obj->work[0]].chr;
    u8 lane;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x6A9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0x4F));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x50));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x51));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x52));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    func_8001C814_main(obj->model[0], 2, 2);
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    lane = rand8() % 3;
    while (TRUE) {
        if (lane != D_80110DBA_river_raiders[0] && lane != D_80110DBA_river_raiders[1]) {
            obj->work[2] = lane;
            D_80110DBA_river_raiders[D_80110D91_river_raiders] = lane;
            D_80110D91_river_raiders++;
            switch (obj->work[2]) {
                case 0:
                    obj->trans.x = -300.0f;
                    break;
                case 1:
                    obj->trans.x = 0.0f;
                    break;
                case 2:
                    obj->trans.x = 300.0f;
                    break;
            }
            break;
        }
        lane = (lane + 1) % 3;
    }
    obj->trans.y = 0.0f;
    obj->trans.z = 600.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = func_8000B108_main(0x2A000B, 0x4B9);
    func_8000B460_main(obj, 4, 0x2A000C);
    func_8000B460_main(obj, 5, 0x2A000D);
    func_8000B460_main(obj, 6, 0x2A000E);
    func_8000B460_main(obj, 7, 0x2A000F);
    func_8001C5B4_main(obj->model[1], obj->motion[4]);
    Hu3DMotionTimeSet(obj->model[1], 0.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[2] = func_8000B108_main(0x2A0011, 0x4A9);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 0.5f, 1.0f, 0.5f);
    func_8001C814_main(obj->model[2], 2, 2);
    obj->model[3] = func_8000B0A0_main(0, 0x4A9);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    func_8001C2FC_main(obj->model[3], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[3]);
    func_8001C514_main(obj->model[3]);
    entry->sprite = func_8000B838_main(D_8010D3D0_river_raiders[chr]);
    entry->esp = espEntry(entry->sprite, 0, 0);
    espAttrSet(entry->esp, 0x1000);
    espPosSet(entry->esp, D_8010D870_river_raiders[obj->work[2]].x, D_8010D870_river_raiders[obj->work[2]].y);
    espScaleSet(entry->esp, 1.0f, 1.0f);
    obj->func = func_80109C08_river_raiders;
}

#ifdef NON_MATCHING
// Target does not hoist the func_8010A6A8_river_raiders address out of the loop, which changes register allocation.
void func_8010ABA0_river_raiders(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s32 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
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
        entry = &D_8010DD08_river_raiders[count];
        obj = omAddObj(0x2EE, 9, 0x3C, -1, func_8010A6A8_river_raiders);
        obj->work[0] = playerIndex;
        obj->work[1] = count++;
        entry->obj = obj;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ABA0_river_raiders);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010ACD8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010BE88_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010C494_river_raiders);

void func_8010C890_river_raiders(void) {
    RiverRaidersEntry *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 30; i++) {
        entry = &D_8010DF18_river_raiders[i];
        obj = omAddObj(0x226, 5, 5, -1, func_8010C494_river_raiders);
        obj->work[0] = i;
        if (i < 20) {
            obj->work[1] = 0;
        }
        if (i >= 20 && i < 24) {
            obj->work[1] = 1;
        }
        if (i >= 24) {
            obj->work[1] = 2;
        }
        entry->obj = obj;
    }
}

void func_8010C980_river_raiders(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 2275.0f;
        CRotM[i].x = 319.3f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -195.0f;
        CenterM[i].z = 0.0f;
    }
}

void func_8010CA20_river_raiders(omObjData *obj) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010CA4C_river_raiders(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = func_8010CA20_river_raiders;
    }
}

void func_8010CA84_river_raiders(omObjData *obj) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
        obj->func = func_8010CA4C_river_raiders;
        HuAudSeqFadeOut(0x1E);
        func_8004AB0C_main(0x1E);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CADC_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010CF00_river_raiders);

void func_8010D0F0_river_raiders(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D0F8_river_raiders);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", func_8010D268_river_raiders);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_09_river_raiders/1542E0", D_8010D9BC_river_raiders);
