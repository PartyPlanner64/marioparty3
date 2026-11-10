#include "common.h"
#include "../ovl_81_name/ovl_81.h"

// Inlined Z rotation matrix build (same as MTX_ROTZ in w02).
#define MTX_ROTZ(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[0][1], &(mtx)[0][0]);                                        \
        (mtx)[1][0] = -(mtx)[0][1];                                                         \
        (mtx)[1][1] = (mtx)[0][0];                                                          \
        (mtx)[0][2] = (mtx)[0][3] = (mtx)[1][3] = (mtx)[1][2] = (mtx)[2][0] = (mtx)[2][1] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[2][2] = (mtx)[3][3] = 1.0f;                                                   \
    }

typedef struct Duel02ModelWaitWork {
    /* 0x00 */ s32 index;
    /* 0x04 */ char unk_04[0xC];
} Duel02ModelWaitWork; // sizeof 0x10

typedef struct Duel02CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel02CamShakeWork; // sizeof 0x10

typedef struct Duel02SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel02SpriteWork; // sizeof 0x10

typedef struct Duel02PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel02PartnerAttackWork; // sizeof 0x10

typedef struct Duel02SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel02SwayWork; // sizeof 0x10


void *memcpy(void *, const void *, unsigned int);
void func_8010B134_duel02(omObjData *);
void func_800EDD50_name_81(Vec *);
void func_800EE0F4_name_81(s32);
void func_800EDF48_name_81(void);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800EE74C_name_81(s32);
void func_800FFCCC_name_81(void *);
void func_800EDF78_name_81(void);
void func_800EE468_name_81(s32);
void func_800EDDBC_name_81(void);
void func_800F3880_name_81(s32, s32, s32);
extern f32 D_801165BC_duel02;
extern s16 D_801165D2_duel02;
extern s16 D_801165D0_duel02;
extern s16 D_801165DA_duel02;
extern s16 D_801165D8_duel02;
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s32, s32);
extern s16 D_80117140_duel02[];
extern char D_80117128_duel02[];
extern Object *D_80117620_duel02;
extern s16 D_80117158_duel02[];
extern void func_8010E1B8_duel02(void);
extern void func_80105CC4_duel02(void);
extern void func_8010630C_duel02(void);
extern void func_8010E7C4_duel02(void);
extern void func_8010EA68_duel02(void);
extern omObjData *D_8011761C_duel02;
extern Object *D_80117628_duel02;
extern Object *D_80117630_duel02;
void func_8010D9F8_duel02(void);
void func_800FF640_name_81(s32);
f32 func_800D76D0_name_81(Vec *);
s32 func_800E88FC_name_81(void);
extern s32 D_80117600_duel02;
extern s32 D_80117604_duel02;
extern s32 D_80117608_duel02;
extern s32 D_8011760C_duel02;
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EBF2C_name_81(Vec *, Vec *, Vec *);
void func_800F38DC_name_81(s32, s32, s32);
void func_801100A8_duel02(s32);
void func_8011639C_duel02(s8 *, s8 *);
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_80105F24_duel02(void);
extern Process *D_801165D4_duel02;
extern f32 D_8011762C_duel02;
void func_8010DDF0_duel02(void);
extern Process *D_801165DC_duel02;
extern f32 D_80117634_duel02;
void func_8010E3FC_duel02(void);
extern event_table_entry D_801167B8_duel02[];
extern event_table_entry D_80117008_duel02[];
void func_800EA46C_name_81(event_table_entry *);
void func_800FC59C_name_81(s32 (*)(void));
void func_800FC5A8_name_81(process_func);
void func_8011394C_duel02(void);
s32 func_801163A4_duel02(void);
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_8010682C_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010718C_duel02(s32, s32, Object *, Object *, s32, s32);
void func_801079BC_duel02(s32, s32, Object *, Object *, s32, s32);
void func_80107EC0_duel02(s32, s32, Object *, Object *, s32, s32);
void func_801084A8_duel02(s32, s32, Object *, Object *, s32, s32);
void func_80108554_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010988C_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010A214_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010B550_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD8_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010CE6C_duel02(s32, s32, Object *, Object *, s32, s32);
void func_8010D428_duel02(s32, s32, Object *, Object *, s32, s32);

void func_801059D0_duel02(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel02(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80117600_duel02 = func_800E1824_name_81(0, 0xA0, 1);
    D_80117604_duel02 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80117608_duel02 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011760C_duel02 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel02(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80117600_duel02);
    func_800E1854_name_81(D_80117604_duel02);
    func_800E1854_name_81(D_80117608_duel02);
    func_800E1854_name_81(D_8011760C_duel02);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105B64_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80105BA0_duel02);

void func_80105C68_duel02(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

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

Process *func_801060D4_duel02(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel02PartnerAttackWork *work;

    process = omAddPrcObj(func_80105F24_duel02, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void func_80106160_duel02(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
    Vec offset;
    f32 angle;

    HuVecCopy3F(origPos, &obj->coords);
    if (target != NULL) {
        HuVecCopy3F(targetPos, &target->coords);
    } else {
        HuVecCopy3F(targetPos, &player->player_obj->coords);
    }
    func_800EB708_name_81(&obj->coords, targetPos, &obj->rot);
    angle = func_800D76D0_name_81(&obj->rot) + 180.0f;
    offset.x = sindf(angle) * dist;
    offset.y = 0.0f;
    offset.z = cosdf(angle) * dist;
    HuVecAdd(targetPos, targetPos, &offset);
}

void func_80106244_duel02(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

void func_80106264_duel02(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_801062C4_duel02(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
}

void func_8010630C_duel02(void) {
    Duel02CamShakeWork *work = HuPrcCurrentGet()->user_data;
    s32 magnitude = work->magnitude;
    s32 decay = work->decay;
    Vec2f base;
    Vec2f pos;

    MBDCameraPos2DGet(&base);
    func_800FC888_name_81(0);
    for (; magnitude >= 0; magnitude -= decay) {
        pos.x = func_800EFE20_name_81(magnitude) + base.x - magnitude / 2;
        pos.y = func_800EFE20_name_81(magnitude) + base.y - magnitude / 2;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
        pos.x = func_800EFE20_name_81(magnitude) + base.x - magnitude / 2;
        pos.y = func_800EFE20_name_81(magnitude) + base.y - magnitude / 2;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
    }
    func_800FC888_name_81(4);
    omDelPrcObj(NULL);
}

Process *func_80106460_duel02(s32 magnitude, s32 decay) {
    Process *process;
    Duel02CamShakeWork *work;

    process = omAddPrcObj(func_8010630C_duel02, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801064CC_duel02);

Object *func_80106744_duel02(s32 arg0) {
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

void func_801067D8_duel02(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0);
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010682C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010718C_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117070_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801079BC_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80107EC0_duel02);

void func_801084A8_duel02(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
    func_800FAD04_name_81(5);
    if (arg5 == 2) {
        HuAudFXPlay(0x25D);
        func_800FAE18_name_81(arg2, 0, 0);
        func_800EFABC_name_81(arg2);
    }
    HuAudFXPlay(0x25D);
    func_800FAE18_name_81(arg2, 0, 0);
    func_800EFABC_name_81(arg2);
    func_800D90D0_name_81(arg2, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800FADB4_name_81();
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80108554_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80109408_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010988C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010A214_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010AAB4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010AD4C_duel02);

void func_8010AFB8_duel02(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    func_800142A0_main(0x1A);
    D_8011761C_duel02 = omAddObj(0x1F4, 0, 0, -1, func_8010B134_duel02);
    data = D_8011761C_duel02->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
    sprData = DataRead(0xB0047);
    for (i = 0; i < ARRAY_COUNT(data->unk_1A0); i++) {
        if (i == 0) {
            data->unk_1A0[0] = Hu3DSprModelCreate(sprData, 0x1A0D, 8);
        } else {
            data->unk_1A0[i] = func_80014618_main(data->unk_1A0[0], 8);
        }
        func_800146DC_main(data->unk_1A0[i], 6, 0x180);
        data->unk_1C0[i] = D_800CBB60_main[data->unk_1A0[i]].modelId;
        func_800147FC_main(data->unk_1A0[i], 0xFF, 0x40, 8);
        func_80014794_main(data->unk_1A0[i], 0xC8);
        func_8001C2FC_main(data->unk_1C0[i], 0x70000000, 0x70000000);
    }
    DataClose(sprData);
    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        data->unk_180[i] = 0;
    }
    D_8011761C_duel02->work[0] = 0;
    data->unk_1E0 = 0;
}

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

void func_8010B4C4_duel02(void) {
    UnkDuelObjData *data = D_8011761C_duel02->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_1A0); i++) {
        func_80016638_main(data->unk_1A0[i]);
    }
    omDelObj(D_8011761C_duel02);
    func_800166D0_main();
}

void func_8010B52C_duel02(void) {
    D_8011761C_duel02->work[0] = 1;
}

void func_8010B540_duel02(void) {
    D_8011761C_duel02->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010B550_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010BCD8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010CE6C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D428_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170A8_duel02);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_801170B4_duel02);

void func_8010D960_duel02(void) {
    PartnerFunc attackFuncs[12] = {
        func_8010682C_duel02, func_8010718C_duel02, func_801079BC_duel02, func_80107EC0_duel02,
        func_8010988C_duel02, func_801084A8_duel02, func_8010CE6C_duel02, func_8010D428_duel02,
        func_8010BCD8_duel02, func_80108554_duel02, func_8010A214_duel02, func_8010B550_duel02,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        func_8010988C_duel02, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(attackFuncs, otherFuncs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010D9F8_duel02);

void func_8010DA88_duel02(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F8_duel02();
    func_800EA46C_name_81(D_801167B8_duel02);
    func_800EA46C_name_81(D_80117008_duel02);
    func_800FC5A8_name_81(func_8011394C_duel02);
    func_800FC59C_name_81(func_801163A4_duel02);
    func_800FF640_name_81(0);
}

void func_8010DB04_duel02(void) {
    Hu3DCamInit(1);
    func_8010D9F8_duel02();
    func_800FF640_name_81(1);
}

void func_8010DB30_duel02(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], Hu3DData[D_80117620_duel02->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = func_8001D33C_main(D_80117620_duel02->omObj1->model[0], "neji");
        angle += D_801165BC_duel02;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void func_8010DC08_duel02(void) {
    HmfMotionNode *node;

    func_8002FD8C_main(D_80117620_duel02->omObj1->model[0], Hu3DData[D_80117620_duel02->omObj1->model[0]].motId, D_80117128_duel02, 0x4C, 0x46);
    node = func_8001D33C_main(D_80117620_duel02->omObj1->model[0], D_80117128_duel02);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010DCAC_duel02);

void func_8010DD40_duel02(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x32, NULL);
    func_800D8944_name_81(obj);
    D_80117628_duel02 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_801165D0_duel02);
    space2 = MBDMasuGet(D_801165D2_duel02);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010DDF0_duel02(void) {
    Duel02SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_80117628_duel02->omObj1->model[0]].mtx, sindf(angle) * D_8011762C_duel02);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF6C_duel02(Vec *pos) {
    Process *process;
    Duel02SwayWork *work;

    D_8011762C_duel02 = 10.0f;
    process = omAddPrcObj(func_8010DDF0_duel02, 0xA, 0, 0x40);
    D_801165D4_duel02 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02SwayWork));
    process->user_data = work;
    if (pos->x <= D_80117628_duel02->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E00C_duel02(void) {
    if (D_801165D4_duel02 != NULL) {
        while (D_8011762C_duel02 >= 0.0f) {
            D_8011762C_duel02 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801165D4_duel02);
        MTX_ROTZ(Hu3DData[D_80117628_duel02->omObj1->model[0]].mtx, 0.0f);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel02/3EC590", D_80117128_duel02);

void func_8010E1B8_duel02(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_80117628_duel02->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_80117628_duel02->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80117628_duel02);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_80117628_duel02->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_80117628_duel02->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2D0_duel02(void) {
    omAddPrcObj(func_8010E1B8_duel02, 0xA, 0, 0);
}

void func_8010E2FC_duel02(void) {
    func_8001C814_main(D_80117628_duel02->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80117628_duel02->omObj1->model[0], 1.0f);
}

void func_8010E34C_duel02(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x33, NULL);
    func_800D8944_name_81(obj);
    D_80117630_duel02 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_801165D8_duel02);
    space2 = MBDMasuGet(D_801165DA_duel02);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010E3FC_duel02(void) {
    Duel02SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_80117630_duel02->omObj1->model[0]].mtx, sindf(angle) * D_80117634_duel02);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E578_duel02(Vec *pos) {
    Process *process;
    Duel02SwayWork *work;

    D_80117634_duel02 = 10.0f;
    process = omAddPrcObj(func_8010E3FC_duel02, 0xA, 0, 0x40);
    D_801165DC_duel02 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel02SwayWork));
    process->user_data = work;
    if (pos->x <= D_80117630_duel02->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E618_duel02(void) {
    if (D_801165DC_duel02 != NULL) {
        while (D_80117634_duel02 >= 0.0f) {
            D_80117634_duel02 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801165DC_duel02);
        MTX_ROTZ(Hu3DData[D_80117630_duel02->omObj1->model[0]].mtx, 0.0f);
    }
}

void func_8010E7C4_duel02(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_80117630_duel02->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_80117630_duel02->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80117630_duel02);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_80117630_duel02->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_80117630_duel02->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

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

s16 func_8010ECB8_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 partnerValues[12];

    memcpy(partnerValues, D_80117140_duel02, sizeof(partnerValues));
    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

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

void func_80110BBC_duel02(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_801100A8_duel02(0);
    }
}

void func_80110C18_duel02(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 1 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_801100A8_duel02(1);
    }
}

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

void func_80112428_duel02(void) {
    GW_PLAYER *player;
    void *handle;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FF);
    handle = func_800FFC2C_name_81(-1, 3, 5);
    func_800EE74C_name_81(3);
    func_800FFCCC_name_81(handle);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    PlayerFXPlay(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    GwPlayer[GwSystem.current_player_index].star = 5;
}

void func_80112518_duel02(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_80112554_duel02(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(sys->current_player_index, -coins);
    func_800F7378_name_81(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_801125D0_duel02(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 10);
    func_800F7378_name_81(sys->current_player_index, 10);
    HuPrcSleep(30);
}

void func_8011260C_duel02(void) {
    s8 nnlink;
    s8 nnidx;
    s8 link2 = -1;
    s8 idx2 = -1;

    if (MBDGetCurrentPlayerIndex() == 0) {
        func_800E9F4C_name_81(0x1E, &nnlink, &nnidx);
    } else {
        func_800E9F4C_name_81(0x1D, &nnlink, &nnidx);
    }
    func_8011639C_duel02(&link2, &idx2);
    func_800E24AC_name_81(nnlink, nnidx, link2, idx2);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_801100A8_duel02(MBDGetCurrentPlayerIndex());
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011268C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112A08_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112BF4_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112DE0_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80113618_duel02);

void func_80113910_duel02(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

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

void func_80116240_duel02(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x1F, &player->nnlink, &player->nnidx);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8011628C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_801162F8_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116344_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80116370_duel02);

void func_8011639C_duel02(s8 *arg0, s8 *arg1) {
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

void func_80116564_duel02(void) {
}
