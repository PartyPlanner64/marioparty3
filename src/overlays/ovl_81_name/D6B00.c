#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkD6B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Object *unk_04;
    /* 0x08 */ omObjData *unk_08;
} UnkD6B00; // sizeof 0xC

typedef struct UnkNameVecEntry {
    /* 0x00 */ Object *obj;
    /* 0x04 */ u16 count; // number of points
    /* 0x06 */ u16 index; // current point index
    /* 0x08 */ f32 speed;
    /* 0x0C */ Vec *points; // array of count Vecs
} UnkNameVecEntry;          // sizeof 0x10

extern UnkD6B00 D_80105560_name_81[16];
extern s32 D_80101220_name_81;
extern s32 D_800A12C0_main;
extern s32 D_800A12C4_main;

static void func_800EED5C_name_81(s32 arg0);
static void func_800EEDA0_name_81(s32 arg0, s32 arg1, s32 arg2);
static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
static void func_800EF3F8_name_81(s32 arg0, s32 arg1);
static s32 func_800EFEC8_name_81(Object *obj, Vec *target, f32 speed, Vec *dir);

void func_800EED30_name_81(s32 arg0) {
    D_800A12C4_main = arg0;
    func_800EED5C_name_81(arg0);
}

s32 func_800EED50_name_81(void) {
    return D_800A12C4_main;
}

static void func_800EED5C_name_81(s32 arg0) {
    D_800A12C0_main = arg0;
}

void func_800EED68_name_81(s32 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 0);
}

void func_800EED84_name_81(s32 arg0, s32 arg1) {
    func_800EEDA0_name_81(arg0, arg1, 1);
}

static void func_800EEDA0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp18[MB_MAX_PLAYERS];
    s32 hasCom = 0;
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    s32 sp2C;
    s32 i;

    hasCom = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == arg1) {
            if (GwPlayer[i].stat & 1) {
                hasCom = 1;
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                HuWinActivePlayerSet(arg0, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (hasCom != 0) {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    if (arg2 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void func_800EF0A0_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 0);
}

void func_800EF0BC_name_81(s32 arg0, s32 arg1, s32 arg2) {
    func_800EF0D8_name_81(arg0, arg1, arg2, 1);
}

static void func_800EF0D8_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i == arg1) || (i == arg2)) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = -0x8000;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (mask) {
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    } else {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
    }

    if (arg3 == 0) {
        while (HuWinStatGet(arg0) != 0) {
            HuPrcVSleep();
        }
    } else {
        while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
            HuPrcVSleep();
        }
        winData[arg0].stat = 7;
    }
    HuWinComKeyReset();
}

void func_800EF3B4_name_81(s32 arg0) {
    func_800EF3F8_name_81(arg0, 0);
}

void func_800EF3D0_name_81(s32 arg0) {
    func_800EF3F8_name_81(arg0, 1);
}

void func_800EF3EC_name_81(s32 arg0) {
    D_80101220_name_81 = arg0;
}

static void func_800EF3F8_name_81(s32 arg0, s32 arg1) {
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = { 1, 2, 4, 8 };
    u8 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < D_80101220_name_81; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == D_80101220_name_81) {
        func_8005B63C_main(arg0, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, D_800A12C0_main);
        D_800A12C0_main = D_800A12C4_main;
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    } else {
        for (i = 0; i < D_80101220_name_81; i++) {
            if (GwPlayer[i].stat & 1) {
                sp18[GwPlayer[i].pad] = 0;
            } else {
                mask |= sp20[GwPlayer[i].pad];
                sp18[GwPlayer[i].pad] = -1;
            }
        }
        HuWinActivePlayerSet(arg0, mask);
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
        if (arg1 == 0) {
            while (HuWinStatGet(arg0) != 0) {
                HuPrcVSleep();
            }
        } else {
            while ((HuWinStatGet(arg0) != 0) && !(func_8005B68C_main(arg0) & 0x200)) {
                HuPrcVSleep();
            }
            winData[arg0].stat = 7;
        }
    }
    HuWinComKeyReset();
}

void func_800EF754_name_81(s32 arg0) {
    HuWinActivePlayerSet(arg0, HUWIN_PLAYER_ALL);
    HuWinComKeySet(-1, -1, -1, -1);
    while (HuWinStatGet(arg0) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void func_800EF7C8_name_81(Object *arg0, f32 arg1, f32 arg2) {
    arg0->velocity.y = arg1;
    arg0->velocity.z = arg2;
}

s32 func_800EF7D4_name_81(Object *arg0) {
    s32 ret = 0;
    if (arg0->velocity.z != 0.0f) {
        ret = 1;
    }
    return ret;
}

void func_800EF800_name_81(Object *arg0) {
    while (func_800EF7D4_name_81(arg0)) {
        HuPrcVSleep();
    }
}

void func_800EF840_name_81(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        D_80105560_name_81[i].unk_04 = NULL;
        D_80105560_name_81[i].unk_08 = NULL;
    }
}

void func_800EF880_name_81(void) {
    s32 i;
    UnkD6B00 *entry;

    for (i = 0, entry = D_80105560_name_81; i < 16; i++) {
        if (entry[i].unk_08 != NULL) {
            omDelObj(entry[i].unk_08);
            entry[i].unk_08 = NULL;
        }
    }
}

static void func_800EF8EC_name_81(omObjData *obj) {
    UnkD6B00 *entry = &D_80105560_name_81[obj->work[0]];

    if (Hu3DData[entry->unk_04->omObj1->model[0]].motTime ==
        D_800CCF58_main[Hu3DData[entry->unk_04->omObj1->model[0]].motId].unk02) {
        MBDMotionShiftSet(entry->unk_04, entry->unk_00, 0, 0xA, entry->unk_02);
        entry->unk_04 = NULL;
        entry->unk_08 = NULL;
        omDelObj(obj);
    }
}

s32 func_800EF9C4_name_81(Object *arg0, s16 arg1, s16 arg2) {
    omObjData *obj;
    UnkD6B00 *entry;
    s32 i;
    s32 ret;

    for (i = 0; i < ARRAY_COUNT(D_80105560_name_81); i++) {
        entry = &D_80105560_name_81[i];
        if (entry->unk_08 == NULL) {
            break;
        }
    }

    if (i != ARRAY_COUNT(D_80105560_name_81)) {
        obj = omAddObj(0x2000, 0, 0, -1, func_800EF8EC_name_81);
        entry->unk_08 = obj;
        obj->work[0] = i;
        entry->unk_04 = arg0;
        entry->unk_00 = arg1;
        entry->unk_02 = arg2;
        ret = i;
    } else {
        ret = -1;
    }
    return ret;
}

void func_800EFA8C_name_81(Object *arg0, s16 arg1, s32 arg2) {
    MBDMotionShiftSet(arg0, arg1, 0, 0xA, arg2);
}

void func_800EFABC_name_81(Object *arg0) {
    while (!(MBDMotionCheck(arg0) & 1)) {
        HuPrcVSleep();
    }
}

void func_800EFB00_name_81(Object *arg0) {
    do {
        HuPrcVSleep();
    } while (!(func_800D92A8_name_81(arg0) & 1));
}

s32 func_800EFB3C_name_81(s32 playerIndex) {
    s32 rank;
    s32 i;
    s32 score[MBD_MAX_PLAYERS];

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        score[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }

    for (i = 0, rank = 0; i < MBD_MAX_PLAYERS; i++) {
        if ((i != playerIndex) && (score[playerIndex] < score[i])) {
            rank++;
        }
    }
    return rank;
}

s32 func_800EFBE8_name_81(s32 playerIndex) {
    return GwPlayer[playerIndex].star * 1000 + GwPlayer[playerIndex].coin;
}

void func_800EFC28_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MBD_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MBD_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

void func_800EFD24_name_81(void) {
    s32 i;

    HuPrcSleep(2);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }

    if (i == MB_MAX_PLAYERS) {
        HuPrcSleep(30);
        return;
    }

    while (1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (!(GwPlayer[i].stat & 1) && (D_800D5558_main[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                break;
            }
        }

        if (i == MB_MAX_PLAYERS) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
}

s32 func_800EFE20_name_81(f32 arg0) { // 800EEF80 in party mode
    // rand8 returns an unsigned byte
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);

    // Normalize the 16-bit number to the range [0, 1), then multiply by arg0
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

s32 func_800EFE8C_name_81(Object *obj, Vec *target, f32 speed) {
    return func_800EFEC8_name_81(obj, target, speed, &obj->rot);
}

s32 func_800EFEAC_name_81(Object *obj, Vec *target, f32 speed) {
    Vec dir;

    return func_800EFEC8_name_81(obj, target, speed, &dir);
}

static s32 func_800EFEC8_name_81(Object *obj, Vec *target, f32 speed, Vec *dir) {
    f32 dist = HuVecDistance(&obj->coords, target);

    if (dist == 0.0f) {
        return 1;
    }
    MBDVecDirGet(&obj->coords, target, dir);
    if (speed <= dist) {
        obj->coords.x += speed * dir->x;
        obj->coords.y += speed * dir->y;
        obj->coords.z += speed * dir->z;
        return 0;
    }
    HuVecCopy3F(&obj->coords, target);
    return 1;
}

UnkNameVecEntry *func_800EFFBC_name_81(Object *obj, f32 speed, s16 count, Vec *points) {
    UnkNameVecEntry *entry = HuMemMemoryAllocPerm(sizeof(UnkNameVecEntry));

    entry->obj = obj;
    entry->count = count;
    entry->index = 0;
    entry->speed = speed;
    entry->points = points;
    return entry;
}

s32 func_800F001C_name_81(UnkNameVecEntry *entry) {
    if (func_800EFE8C_name_81(entry->obj, &entry->points[entry->index], entry->speed) == 0) {
        return 0;
    }
    if (++entry->index >= entry->count) {
        entry->index--;
    }
    return 1;
}

s32 func_800F008C_name_81(Object *obj, Vec *target, f32 speed) {
    Vec dir;
    f32 maxTurn = speed * 1.2f;
    f32 targetAngle;
    f32 angle;
    f32 diff;

    MBDVecDirGet(&obj->coords, target, &dir);
    targetAngle = MBDVecAngleGet(&dir);
    angle = MBDVecAngleGet(&obj->rot);
    diff = targetAngle - angle;
    if (fabs(diff) > maxTurn) {
        if (diff < 0.0f) {
            diff += 360.0f;
        }
        if (diff < 180.0f) {
            if (maxTurn < diff) {
                angle += maxTurn;
            } else {
                angle += diff;
            }
        } else if (maxTurn < 360.0f - diff) {
            angle -= maxTurn;
        } else {
            angle -= 360.0f - diff;
        }
    } else {
        angle = targetAngle;
    }
    dir.x = sindf(angle);
    dir.z = cosdf(angle);
    obj->rot = dir;
    return angle == targetAngle;
}

void func_800F0208_name_81(Vec *pos, f32 zoom, f32 targetZoom, u32 frames) {
    f32 step;

    frames = frames * 1.2f;
    step = (targetZoom - zoom) / frames;
    while (1) {
        zoom += step;
        if (step >= 0.0f) {
            if (zoom >= targetZoom) {
                zoom = targetZoom;
            }
        } else if (zoom <= targetZoom) {
            zoom = targetZoom;
        }
        MBDCameraZoomSet(zoom);
        MBDCameraPos3DSet(pos);
        if (step >= 0.0f ? zoom >= targetZoom : zoom <= targetZoom) {
            break;
        }
        HuPrcVSleep();
    }
}

void func_800F0378_name_81(Object *obj, char *hookName, s16 model) {
    Hu3DModelHookSet(model, obj->omObj1->model[0], hookName);
    func_8001C258_main(model, 0x4000, 0x4000);
}

void func_800F03C8_name_81(s16 arg0) {
    func_8001C258_main(arg0, 0x4000, 0);
}

s32 func_800F03F0_name_81(s16 x, s16 y, s16 w, s16 h) {
    s32 win = HuWinCreate(x, y, w, h, 0, 0);

    HuWinBGTPLvlSet(win, 200);
    func_80060144_main(win);
    func_8005B63C_main(win, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    HuWinMesSpeedSet(win, 0);
    return win;
}
