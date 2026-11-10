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

typedef struct Duel04CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel04CamShakeWork; // sizeof 0x10

typedef struct Duel04SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel04SpriteWork; // sizeof 0x10

typedef struct Duel04PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel04PartnerAttackWork; // sizeof 0x10

typedef struct Duel04SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel04SwayWork; // sizeof 0x10

void *memcpy(void *, const void *, unsigned int);
extern s8 *D_80119DE4_duel04[];
extern s8 D_80119CE8_duel04[];
void func_8010B134_duel04(omObjData *);
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
extern f32 D_80119CBC_duel04;
extern s16 D_80119CD2_duel04;
extern s16 D_80119CD0_duel04;
extern s16 D_80119CDA_duel04;
extern s16 D_80119CD8_duel04;
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s32, s32);
extern s16 D_8011AFAC_duel04[];
extern char D_8011AF88_duel04[];
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_8010682C_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010718C_duel04(s32, s32, Object *, Object *, s32, s32);
void func_801079BC_duel04(s32, s32, Object *, Object *, s32, s32);
void func_80107EC0_duel04(s32, s32, Object *, Object *, s32, s32);
void func_801084A8_duel04(s32, s32, Object *, Object *, s32, s32);
void func_80108554_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010988C_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010A214_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010B550_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD8_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010CE6C_duel04(s32, s32, Object *, Object *, s32, s32);
void func_8010D428_duel04(s32, s32, Object *, Object *, s32, s32);
extern Object *D_8011B500_duel04;
extern s16 D_8011AFC4_duel04[];
void func_8010E1C4_duel04(void);
extern void func_80105CC4_duel04(void);
extern void func_8010E7D0_duel04(void);
extern void func_8010630C_duel04(void);
extern omObjData *D_8011B4FC_duel04;
extern Object *D_8011B508_duel04;
extern Object *D_8011B510_duel04;
void func_8010D9F8_duel04(void);
extern event_table_entry D_80119E9C_duel04[];
extern event_table_entry D_8011ADE8_duel04[];
void func_800EA46C_name_81(event_table_entry *);
void func_800FC590_name_81(void (*)(void));
void func_800FC59C_name_81(s32 (*)(void));
void func_800FC5A8_name_81(process_func);
void func_801139D4_duel04(void);
s32 func_801187B8_duel04(void);
void func_801198EC_duel04(void);
void func_800FF640_name_81(s32);
f32 func_800D76D0_name_81(Vec *);
s32 func_800E88FC_name_81(void);
extern s32 D_8011B4E0_duel04;
extern s32 D_8011B4E4_duel04;
extern s32 D_8011B4E8_duel04;
extern s32 D_8011B4EC_duel04;
void func_800EB708_name_81(Vec *, Vec *, Vec *);
void func_800EBF2C_name_81(Vec *, Vec *, Vec *);
void func_800F38DC_name_81(s32, s32, s32);
void func_80110124_duel04(s32);
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_80105F24_duel04(void);
extern Process *D_80119CD4_duel04;
extern f32 D_8011B50C_duel04;
void func_8010DDFC_duel04(void);
extern Process *D_80119CDC_duel04;
extern f32 D_8011B514_duel04;
void func_8010E408_duel04(void);

void func_801059D0_duel04(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel04(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011B4E0_duel04 = func_800E1824_name_81(0, 0xA0, 1);
    D_8011B4E4_duel04 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_8011B4E8_duel04 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011B4EC_duel04 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel04(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_8011B4E0_duel04);
    func_800E1854_name_81(D_8011B4E4_duel04);
    func_800E1854_name_81(D_8011B4E8_duel04);
    func_800E1854_name_81(D_8011B4EC_duel04);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105B64_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80105BA0_duel04);

void func_80105C68_duel04(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

void func_80105CC4_duel04(void) {
    Duel04SpriteWork *work = HuPrcCurrentGet()->user_data;
    f32 x = work->pos.x;
    f32 y = work->pos.y;
    f32 z = work->pos.z;
    Vec pos;
    Vec2f screenPos;
    UnkBoard4 *sprite;
    void *data;
    f32 amplitude;
    s32 i;

    HuPrcSleep(5);
    HuVecCopyXYZ(&pos, x, y, z);
    MBDCamera3Dto2D(&pos, &screenPos);
    sprite = func_800F4528_name_81(1, 0);
    data = DataRead(0x1301EC);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 0x2010);
    HuSprAttrSet(sprite->unk_0A, 0, 0);
    HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y);
    HuAudFXPlay(0x202);
    amplitude = 20.0f;
    for (i = 0; i < 20; i++) {
        HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y - fabs(sindf(i * 20) * amplitude));
        amplitude -= 1.0f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }
    func_800F4584_name_81(sprite);
    omDelPrcObj(NULL);
}

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

void func_80105F24_duel04(void) {
    Process *process = HuPrcCurrentGet();
    Duel04PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = work->player;
    Object *obj = work->obj;
    s32 delay = work->delay;
    s32 waitTime = work->waitTime;
    Vec offset;
    Vec origPos;

    delay -= 5;
    if (delay > 0) {
        HuPrcSleep(delay);
    }
    func_80105EB4_duel04(obj);
    HuVecSubtract(&offset, &obj->coords, &player->player_obj->coords);
    if (D_80105620_name_81 == 3 || D_80105620_name_81 == 1) {
        func_800D7934_name_81(&offset, -90.0f);
    } else {
        func_800D7934_name_81(&offset, 90.0f);
    }
    HuVecAdd(&offset, &offset, &obj->coords);
    HuVecCopy3F(&origPos, &obj->coords);
    func_800FB0B8_name_81(obj, 3, 0);
    D_80101994_name_81++;
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &offset, &obj->coords, 2.0f));
    HuPrcChildWatch();
    HuPrcSleep(waitTime);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &origPos, &obj->coords, 2.0f));
    func_8001C814_main(obj->omObj1->model[0], 0, 4);
    HuPrcChildWatch();
    func_800EFB00_name_81(obj);
    func_800D90D0_name_81(obj, -1, 2);
    D_80101994_name_81--;
    omDelPrcObj(NULL);
}

Process *func_801060D4_duel04(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel04PartnerAttackWork *work;

    process = omAddPrcObj(func_80105F24_duel04, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel04PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void func_80106160_duel04(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
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

void func_80106244_duel04(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

void func_80106264_duel04(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_801062C4_duel04(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
}

void func_8010630C_duel04(void) {
    Duel04CamShakeWork *work = HuPrcCurrentGet()->user_data;
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

Object *func_80106744_duel04(s32 arg0) {
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

void func_801067D8_duel04(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0);
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010682C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010718C_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AED0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801079BC_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80107EC0_duel04);

void func_801084A8_duel04(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80108554_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80109408_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010988C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010A214_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010AAB4_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010AD4C_duel04);

void func_8010AFB8_duel04(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    func_800142A0_main(0x1A);
    D_8011B4FC_duel04 = omAddObj(0x1F4, 0, 0, -1, func_8010B134_duel04);
    data = D_8011B4FC_duel04->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
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
    D_8011B4FC_duel04->work[0] = 0;
    data->unk_1E0 = 0;
}

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

void func_8010B4C4_duel04(void) {
    UnkDuelObjData *data = D_8011B4FC_duel04->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_1A0); i++) {
        func_80016638_main(data->unk_1A0[i]);
    }
    omDelObj(D_8011B4FC_duel04);
    func_800166D0_main();
}

void func_8010B52C_duel04(void) {
    D_8011B4FC_duel04->work[0] = 1;
}

void func_8010B540_duel04(void) {
    D_8011B4FC_duel04->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010B550_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010BCD8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010CE6C_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010D428_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AF08_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AF14_duel04);

void func_8010D960_duel04(void) {
    PartnerFunc attackFuncs[12] = {
        func_8010682C_duel04, func_8010718C_duel04, func_801079BC_duel04, func_80107EC0_duel04,
        func_8010988C_duel04, func_801084A8_duel04, func_8010CE6C_duel04, func_8010D428_duel04,
        func_8010BCD8_duel04, func_80108554_duel04, func_8010A214_duel04, func_8010B550_duel04,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        func_8010988C_duel04, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(attackFuncs, otherFuncs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010D9F8_duel04);

void func_8010DA88_duel04(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F8_duel04();
    func_800EA46C_name_81(D_80119E9C_duel04);
    func_800EA46C_name_81(D_8011ADE8_duel04);
    func_800FC5A8_name_81(func_801139D4_duel04);
    func_800FC59C_name_81(func_801187B8_duel04);
    func_800FC590_name_81(func_801198EC_duel04);
    func_800FF640_name_81(0);
}

void func_8010DB10_duel04(void) {
    Hu3DCamInit(1);
    func_8010D9F8_duel04();
    func_800FF640_name_81(1);
}

void func_8010DB3C_duel04(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_8011B500_duel04->omObj1->model[0], Hu3DData[D_8011B500_duel04->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = func_8001D33C_main(D_8011B500_duel04->omObj1->model[0], "neji");
        angle += D_80119CBC_duel04;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void func_8010DC14_duel04(void) {
    HmfMotionNode *node;

    func_8002FD8C_main(D_8011B500_duel04->omObj1->model[0], Hu3DData[D_8011B500_duel04->omObj1->model[0]].motId, D_8011AF88_duel04, 0x4C, 0x46);
    node = func_8001D33C_main(D_8011B500_duel04->omObj1->model[0], D_8011AF88_duel04);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010DCB8_duel04);

void func_8010DD4C_duel04(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x32, NULL);
    func_800D8944_name_81(obj);
    D_8011B508_duel04 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_80119CD0_duel04);
    space2 = MBDMasuGet(D_80119CD2_duel04);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010DDFC_duel04(void) {
    Duel04SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_8011B508_duel04->omObj1->model[0]].mtx, sindf(angle) * D_8011B50C_duel04);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF78_duel04(Vec *pos) {
    Process *process;
    Duel04SwayWork *work;

    D_8011B50C_duel04 = 10.0f;
    process = omAddPrcObj(func_8010DDFC_duel04, 0xA, 0, 0x40);
    D_80119CD4_duel04 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel04SwayWork));
    process->user_data = work;
    if (pos->x <= D_8011B508_duel04->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E018_duel04(void) {
    if (D_80119CD4_duel04 != NULL) {
        while (D_8011B50C_duel04 >= 0.0f) {
            D_8011B50C_duel04 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80119CD4_duel04);
        MTX_ROTZ(Hu3DData[D_8011B508_duel04->omObj1->model[0]].mtx, 0.0f);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AF88_duel04);

void func_8010E1C4_duel04(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_8011B508_duel04->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_8011B508_duel04->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_8011B508_duel04);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_8011B508_duel04->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011B508_duel04->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2DC_duel04(void) {
    omAddPrcObj(func_8010E1C4_duel04, 0xA, 0, 0);
}

void func_8010E308_duel04(void) {
    func_8001C814_main(D_8011B508_duel04->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_8011B508_duel04->omObj1->model[0], 1.0f);
}

void func_8010E358_duel04(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x33, NULL);
    func_800D8944_name_81(obj);
    D_8011B510_duel04 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_80119CD8_duel04);
    space2 = MBDMasuGet(D_80119CDA_duel04);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010E408_duel04(void) {
    Duel04SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_8011B510_duel04->omObj1->model[0]].mtx, sindf(angle) * D_8011B514_duel04);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E584_duel04(Vec *pos) {
    Process *process;
    Duel04SwayWork *work;

    D_8011B514_duel04 = 10.0f;
    process = omAddPrcObj(func_8010E408_duel04, 0xA, 0, 0x40);
    D_80119CDC_duel04 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel04SwayWork));
    process->user_data = work;
    if (pos->x <= D_8011B510_duel04->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E624_duel04(void) {
    if (D_80119CDC_duel04 != NULL) {
        while (D_8011B514_duel04 >= 0.0f) {
            D_8011B514_duel04 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80119CDC_duel04);
        MTX_ROTZ(Hu3DData[D_8011B510_duel04->omObj1->model[0]].mtx, 0.0f);
    }
}

void func_8010E7D0_duel04(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_8011B510_duel04->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_8011B510_duel04->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_8011B510_duel04);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_8011B510_duel04->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011B510_duel04->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8E8_duel04(void) {
    omAddPrcObj(func_8010E7D0_duel04, 0xA, 0, 0);
}

void func_8010E914_duel04(void) {
    func_8001C814_main(D_8011B510_duel04->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_8011B510_duel04->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010E964_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EA74_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EA94_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EAF0_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010EC0C_duel04);

s32 func_8010ECFC_duel04(void) {
    return (5 - GwPlayer[GwSystem.current_player_index].star) * 10;
}

s16 func_8010ED34_duel04(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 partnerValues[12];

    memcpy(partnerValues, D_8011AFAC_duel04, sizeof(partnerValues));
    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

s16 func_8010EDDC_duel04(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_8011AFC4_duel04, sizeof(shakeAngles));
    return shakeAngles[index];
}

s32 func_8010EE5C_duel04(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s32 partner = -1;
    s32 roll = func_800EFE20_name_81(10.0f);
    s32 i;

    switch (player->cpu_difficulty) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            if (player->stats.partners.frontID != PARTNER_NONE || player->stats.partners.backID != PARTNER_NONE) {
                if (roll < 6) {
                    if (player->stats.partners.frontID != PARTNER_NONE) {
                        partner = player->stats.partners.frontID;
                    }
                    if (player->stats.partners.backID != PARTNER_NONE) {
                        partner = player->stats.partners.backID;
                    }
                    break;
                }
                if (roll < 8) {
                    for (i = 0; D_80119CE8_duel04[i * 2] != -1; i++) {
                        if (D_80119CE8_duel04[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    partner = D_80119CE8_duel04[i * 2];
                    break;
                }
            }
            for (i = 0; D_80119DE4_duel04[player->chr][i * 2] != -1; i++) {
                if (D_80119DE4_duel04[player->chr][i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            partner = D_80119DE4_duel04[player->chr][i * 2];
            break;
    }
    if (partner == -1) {
        partner = func_800EFE20_name_81(12.0f);
    }
    if ((u32)partner >= 12) {
        partner = 0;
    }
    return partner;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010F078_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010F1E8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_8010FA58_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110124_duel04);

void func_80110C38_duel04(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110124_duel04(0);
    }
}

void func_80110C94_duel04(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 1 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110124_duel04(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AFAC_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AFC4_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AFDC_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011AFE8_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B000_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B030_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B060_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B064_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B06C_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B08C_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B090_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B178_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B260_duel04);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel04/410910", D_8011B348_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80110CF8_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80111EB8_duel04);

void func_801124B0_duel04(void) {
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

void func_801125A0_duel04(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_801125DC_duel04(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(sys->current_player_index, -coins);
    func_800F7378_name_81(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_80112658_duel04(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 10);
    func_800F7378_name_81(sys->current_player_index, 10);
    HuPrcSleep(30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112694_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112714_duel04);

void func_80112A90_duel04(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    void *handle;
    Object *partners[2];

    player = MBDGetPlayerStruct(CUR_PLAYER);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    handle = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(0);
    func_800FFCCC_name_81(handle);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partners[PARTNER_FRONT] = NULL;
    partners[PARTNER_BACK] = NULL;
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partners[PARTNER_FRONT] = func_800D8010_name_81(0x38, NULL);
        func_800D8944_name_81(partners[PARTNER_FRONT]);
        HuVecCopy3F(&partners[PARTNER_FRONT]->coords, &MBDGetPlayerPartnerRef(sys->current_player_index, PARTNER_FRONT)->coords);
        func_8001C814_main(partners[PARTNER_FRONT]->omObj1->model[0], 2, 0);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partners[PARTNER_BACK] = func_800D8010_name_81(0x38, NULL);
        func_800D8944_name_81(partners[PARTNER_BACK]);
        HuVecCopy3F(&partners[PARTNER_BACK]->coords, &MBDGetPlayerPartnerRef(sys->current_player_index, PARTNER_BACK)->coords);
        func_8001C814_main(partners[PARTNER_BACK]->omObj1->model[0], 2, 0);
    }
    HuAudFXPlay(0x1FA);
    if (partners[PARTNER_FRONT] != NULL) {
        func_800EFABC_name_81(partners[PARTNER_FRONT]);
        func_800D8F3C_name_81(partners[PARTNER_FRONT]);
    }
    if (partners[PARTNER_BACK] != NULL) {
        func_800EFABC_name_81(partners[PARTNER_BACK]);
        func_800D8F3C_name_81(partners[PARTNER_BACK]);
    }
    Duel_PowerUpPartners(sys->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(0));
    HuPrcChildWatch();
    func_800EDDBC_name_81();
}

void func_80112C7C_duel04(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    void *handle;
    Object *partners[2];

    player = MBDGetPlayerStruct(CUR_PLAYER);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1FB);
    handle = func_800FFC2C_name_81(-1, 0, 5);
    func_800EE74C_name_81(4);
    func_800FFCCC_name_81(handle);
    func_800EDF78_name_81();
    HuPrcChildLink(HuPrcCurrentGet(), func_800EE40C_name_81(2));
    partners[PARTNER_FRONT] = NULL;
    partners[PARTNER_BACK] = NULL;
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partners[PARTNER_FRONT] = func_800D8010_name_81(0x3A, NULL);
        func_800D8944_name_81(partners[PARTNER_FRONT]);
        HuVecCopy3F(&partners[PARTNER_FRONT]->coords, &MBDGetPlayerPartnerRef(sys->current_player_index, PARTNER_FRONT)->coords);
        func_8001C814_main(partners[PARTNER_FRONT]->omObj1->model[0], 2, 0);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partners[PARTNER_BACK] = func_800D8010_name_81(0x3A, NULL);
        func_800D8944_name_81(partners[PARTNER_BACK]);
        HuVecCopy3F(&partners[PARTNER_BACK]->coords, &MBDGetPlayerPartnerRef(sys->current_player_index, PARTNER_BACK)->coords);
        func_8001C814_main(partners[PARTNER_BACK]->omObj1->model[0], 2, 0);
    }
    if (partners[PARTNER_FRONT] != NULL) {
        func_800EFABC_name_81(partners[PARTNER_FRONT]);
        func_800D8F3C_name_81(partners[PARTNER_FRONT]);
    }
    if (partners[PARTNER_BACK] != NULL) {
        func_800EFABC_name_81(partners[PARTNER_BACK]);
        func_800D8F3C_name_81(partners[PARTNER_BACK]);
    }
    Duel_PowerDownPartners(sys->current_player_index);
    HuAudFXPlay(0x1FC);
    HuPrcChildLink(HuPrcCurrentGet(), func_800E4A74_name_81(1));
    HuPrcChildWatch();
    func_800EDDBC_name_81();
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_80112E68_duel04);

INCLUDE_ASM("asm/nonmatchings/overlays/duel04/410910", func_801136A0_duel04);

void func_80113998_duel04(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

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

void func_80118648_duel04(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1)) {
        func_800E9F4C_name_81(0x21, &player->nnlink, &player->nnidx);
    }
}

void func_80118684_duel04(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (player->rev & 1) {
        func_800E9F4C_name_81(0x22, &player->nnlink, &player->nnidx);
    }
}

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
