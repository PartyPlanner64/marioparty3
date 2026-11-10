#include "common.h"

typedef struct Duel06CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel06CamShakeWork; // sizeof 0x10

typedef struct Duel06SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel06SpriteWork; // sizeof 0x10

typedef struct Duel06PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel06PartnerAttackWork; // sizeof 0x10

typedef struct Duel06SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel06SwayWork; // sizeof 0x10

typedef void (*PartnerFunc)(s16, s32, Object *, Object *, s32, s32);

void func_800FC8C4_name_81(Vec *arg0);
void *memcpy(void *, const void *, unsigned int);
extern Vec D_80105540_name_81;
extern s16 D_80114888_duel06[];
void func_8010E1BC_duel06(void);
extern void func_80105CC8_duel06(void);
extern void func_80106310_duel06(void);
extern void func_8010E7C8_duel06(void);
extern omObjData *D_80114D4C_duel06;
extern Object *D_80114D58_duel06;
extern Object *D_80114D60_duel06;
void func_8010D9FC_duel06(void);
void func_800FF640_name_81(s32);
f32 func_800D76D0_name_81(Vec *);
void func_80100CEC_name_81(s32 padIdx);
s32 func_800E1824_name_81(s32, s32, s32);
s32 func_800E88FC_name_81(void);
void func_800E1854_name_81(s32);
extern s32 D_80114D30_duel06;
extern s32 D_80114D34_duel06;
extern s32 D_80114D38_duel06;
extern s32 D_80114D3C_duel06;
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EC1E4_name_81(Vec *, Vec *, Vec *, f32);
void func_800EBF2C_name_81(Vec *, Vec *, Vec *);
Object *func_800D8010_name_81(s32, s32);
void func_800D8944_name_81(Object *);
void func_800D8F0C_name_81(Object *);
void func_800D8E88_name_81(void);
s16 MBDGetCurrentPlayerIndex(void);
void func_800F38DC_name_81(s32, s32, s32);
void func_80110230_duel06(s32);
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800ED214_name_81(s32 playerIndex);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_80105F28_duel06(void);
extern Process *D_801144E4_duel06;
extern f32 D_80114D5C_duel06;
void func_8010DDF4_duel06(void);
extern Process *D_801144EC_duel06;
extern f32 D_80114D64_duel06;
void func_8010E400_duel06(void);
extern event_table_entry D_801146C4_duel06[];
extern event_table_entry D_80114750_duel06[];
void func_800EA46C_name_81(event_table_entry *);
void func_800FC59C_name_81(s32 (*)(void));
void func_800FC5A8_name_81(process_func);
void func_80113AD4_duel06(void);
s32 func_80114034_duel06(void);
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_80106830_duel06(s16, s32, Object *, Object *, s32, s32);
void func_80107190_duel06(s16, s32, Object *, Object *, s32, s32);
void func_801079C0_duel06(s16, s32, Object *, Object *, s32, s32);
void func_80107EC4_duel06(s16, s32, Object *, Object *, s32, s32);
void func_801084AC_duel06(s16, s32, Object *, Object *, s32, s32);
void func_80108558_duel06(s16, s32, Object *, Object *, s32, s32);
void func_80109890_duel06(s16, s32, Object *, Object *, s32, s32);
void func_8010A218_duel06(s16, s32, Object *, Object *, s32, s32);
void func_8010B554_duel06(s16, s32, Object *, Object *, s32, s32);
void func_8010BCDC_duel06(s16, s32, Object *, Object *, s32, s32);
void func_8010CE70_duel06(s16, s32, Object *, Object *, s32, s32);
void func_8010D42C_duel06(s16, s32, Object *, Object *, s32, s32);

void func_801059D0_duel06(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel06(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80114D30_duel06 = func_800E1824_name_81(0, 0xA0, 1);
    D_80114D34_duel06 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80114D38_duel06 = func_800E1824_name_81(1, 0xBC, 1);
    D_80114D3C_duel06 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel06(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80114D30_duel06);
    func_800E1854_name_81(D_80114D34_duel06);
    func_800E1854_name_81(D_80114D38_duel06);
    func_800E1854_name_81(D_80114D3C_duel06);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80105B64_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80105BA0_duel06);

void func_80105C6C_duel06(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80105CC8_duel06);

Process *func_80105EB8_duel06(Object *object) {
    Process *process;
    Duel06SpriteWork *work;

    process = omAddPrcObj(func_80105CC8_duel06, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80105F28_duel06);

Process *func_801060D8_duel06(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel06PartnerAttackWork *work;

    process = omAddPrcObj(func_80105F28_duel06, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80106164_duel06);

void func_80106248_duel06(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

void func_80106268_duel06(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_801062C8_duel06(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80106310_duel06);

Process *func_80106464_duel06(s32 magnitude, s32 decay) {
    Process *process;
    Duel06CamShakeWork *work;

    process = omAddPrcObj(func_80106310_duel06, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801064D0_duel06);

Object *func_80106748_duel06(s32 arg0) {
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

void func_801067DC_duel06(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81();
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80106830_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80107190_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801147A0_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801079C0_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80107EC4_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801084AC_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80108558_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010940C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80109890_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010A218_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010AAB8_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010AD50_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010AFBC_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010B138_duel06);

s32 func_8010B488_duel06(void) {
    UnkDuelObjData *data = D_80114D4C_duel06->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4C8_duel06(void) {
    UnkDuelObjData *data = D_80114D4C_duel06->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_1A0); i++) {
        func_80016638_main(data->unk_1A0[i]);
    }
    omDelObj(D_80114D4C_duel06);
    func_800166D0_main();
}

void func_8010B530_duel06(void) {
    D_80114D4C_duel06->work[0] = 1;
}

void func_8010B544_duel06(void) {
    D_80114D4C_duel06->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010B554_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010BCDC_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010CE70_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010D42C_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801147D8_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801147E4_duel06);

void func_8010D964_duel06(void) {
    PartnerFunc attackFuncs[12] = {
        func_80106830_duel06, func_80107190_duel06, func_801079C0_duel06, func_80107EC4_duel06,
        func_80109890_duel06, func_801084AC_duel06, func_8010CE70_duel06, func_8010D42C_duel06,
        func_8010BCDC_duel06, func_80108558_duel06, func_8010A218_duel06, func_8010B554_duel06,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        func_80109890_duel06, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(attackFuncs, otherFuncs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010D9FC_duel06);

void func_8010DA8C_duel06(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x20);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9FC_duel06();
    func_800EA46C_name_81(D_801146C4_duel06);
    func_800EA46C_name_81(D_80114750_duel06);
    func_800FC5A8_name_81(func_80113AD4_duel06);
    func_800FC59C_name_81(func_80114034_duel06);
    func_800FF640_name_81(0);
}

void func_8010DB08_duel06(void) {
    Hu3DCamInit(1);
    func_8010D9FC_duel06();
    func_800FF640_name_81(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010DB34_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010DC0C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010DCB0_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010DD44_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010DDF4_duel06);

void func_8010DF70_duel06(Vec *pos) {
    Process *process;
    Duel06SwayWork *work;

    D_80114D5C_duel06 = 10.0f;
    process = omAddPrcObj(func_8010DDF4_duel06, 0xA, 0, 0x40);
    D_801144E4_duel06 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SwayWork));
    process->user_data = work;
    if (pos->x <= D_80114D58_duel06->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E010_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114858_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E1BC_duel06);

void func_8010E2D4_duel06(void) {
    omAddPrcObj(func_8010E1BC_duel06, 0xA, 0, 0);
}

void func_8010E300_duel06(void) {
    func_8001C814_main(D_80114D58_duel06->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80114D58_duel06->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E350_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E400_duel06);

void func_8010E57C_duel06(Vec *pos) {
    Process *process;
    Duel06SwayWork *work;

    D_80114D64_duel06 = 10.0f;
    process = omAddPrcObj(func_8010E400_duel06, 0xA, 0, 0x40);
    D_801144EC_duel06 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SwayWork));
    process->user_data = work;
    if (pos->x <= D_80114D60_duel06->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E61C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E7C8_duel06);

void func_8010E8E0_duel06(void) {
    omAddPrcObj(func_8010E7C8_duel06, 0xA, 0, 0);
}

void func_8010E90C_duel06(void) {
    func_8001C814_main(D_80114D60_duel06->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80114D60_duel06->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010E95C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010EAD0_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010EBAC_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010ED04_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010EE40_duel06);

s16 func_8010EEE8_duel06(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80114888_duel06, sizeof(shakeAngles));
    return shakeAngles[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010EF68_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010F184_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010F2F4_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_8010FB64_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80110230_duel06);

void func_80110D44_duel06(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110230_duel06(0);
    }
}

void func_80110DA0_duel06(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 1 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110230_duel06(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114870_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114888_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801148A0_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801148AC_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801148C4_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_801148F4_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114924_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114928_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114930_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114950_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114954_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114A3C_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114B24_duel06);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel06/436E50", D_80114C0C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80110E04_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80111FC4_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801125B0_duel06);

void func_801126A0_duel06(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_801126DC_duel06(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(sys->current_player_index, -coins);
    func_800F7378_name_81(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_80112758_duel06(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 10);
    func_800F7378_name_81(sys->current_player_index, 10);
    HuPrcSleep(30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80112794_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80112814_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80112B90_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80112D7C_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80112F68_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801137A0_duel06);

void func_80113A98_duel06(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80113AD4_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80113E74_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80113F14_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80113FB4_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80113FF0_duel06);

void func_8011402C_duel06(void) {
}

s32 func_80114034_duel06(void) {
    s32 playerIndex = GwSystem.current_player_index;
    s32 otherIndex = (playerIndex + 1) & 1;
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    GW_PLAYER *otherPlayer = MBDGetPlayerStruct(otherIndex);

    if (player->nlink == otherPlayer->clink && player->nidx == otherPlayer->cidx) {
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_801140A0_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80114174_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80114324_duel06);

INCLUDE_ASM("asm/nonmatchings/overlays/duel06/436E50", func_80114474_duel06);
