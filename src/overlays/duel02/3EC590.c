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
Process *func_800FAB68_name_81(Object *, s32, s32, s32, s32);
void func_800DCE40_name_81(s32, Vec *, s32, f32);
extern void (*D_80116788_duel02[])(void);
Process *func_800E0924_name_81(void);
extern s32 D_80101200_shared_board[];
extern Object *D_80117614_duel02;
extern Object *D_80117610_duel02;
extern s32 D_801165A8_duel02[];
extern Object *D_80117618_duel02;
extern s8 *D_80116700_duel02[];
extern s8 D_80116604_duel02[];
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

void func_80105CC4_duel02(void) {
    Duel02SpriteWork *work = HuPrcCurrentGet()->user_data;
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

void func_80105F24_duel02(void) {
    Process *process = HuPrcCurrentGet();
    Duel02PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
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
    func_80105EB4_duel02(obj);
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

void func_801064CC_duel02(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *model;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
        case 0:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                model = func_800D8010_name_81(0x28, NULL);
                D_80117610_duel02 = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                model = func_800D8010_name_81(0x28, NULL);
                D_80117614_duel02 = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        case 1:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                func_800D8F3C_name_81(D_80117610_duel02);
                func_800D8E88_name_81(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                func_800D8F3C_name_81(D_80117614_duel02);
                func_800D8E88_name_81(partner);
            }
            break;
        case 2:
            switch (D_80105620_name_81) {
                case 1:
                case 3:
                    if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                        model = func_800D8010_name_81(0x28, NULL);
                        D_80117610_duel02 = model;
                        HuVecCopy3F(&model->coords, &partner->coords);
                        HuVecCopy3F(&model->rot, &partner->rot);
                        func_800D8F0C_name_81(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                        model = func_800D8010_name_81(0x28, NULL);
                        D_80117614_duel02 = model;
                        HuVecCopy3F(&model->coords, &partner->coords);
                        HuVecCopy3F(&model->rot, &partner->rot);
                        func_800D8F0C_name_81(partner);
                    }
                    break;
            }
            break;
        case 3:
            switch (D_80105620_name_81) {
                case 1:
                case 3:
                    if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                        func_800D8F3C_name_81(D_80117610_duel02);
                        func_800D8E88_name_81(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                        func_800D8F3C_name_81(D_80117614_duel02);
                        func_800D8E88_name_81(partner);
                    }
                    break;
            }
            break;
    }
}

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

void func_80109408_duel02(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags) {
    GW_PLAYER *player;
    Process *process;
    Vec targetPos;
    Vec origPos;
    Vec dir;
    Vec effectPos;
    s32 steps;
    s32 i;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    HuAudFXPlay(0x1F4);
    func_800D90D0_name_81(obj, 0, 2);
    func_80106160_duel02(obj, target, player, &targetPos, &origPos, 0.0f);
    HuVecSubtract(&dir, &obj->coords, &targetPos);
    func_80106244_duel02();
    func_80106264_duel02(target, player, flags, 3.0f);
    targetPos.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 3.0f));
    steps = HuVecGetLength3F(&dir) / 3.0f;
    obj->flags |= 1;
    if (flags & 8) {
        func_801060D4_duel02(player, target, HuVecGetLength3F(&dir) / 3.0f, 20);
        for (i = 0; i < steps; i++) {
            func_8001F9E4_main(obj->omObj1->model[0], ~((i * 128) / steps));
            HuVecCopyXYZ(&obj->scale, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f);
            HuPrcVSleep();
        }
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(obj->omObj1->model[0], 0);
    } else {
        for (i = 0; i < steps; i++) {
            func_8001F9E4_main(obj->omObj1->model[0], ~((i * 128) / 10));
            HuVecCopyXYZ(&obj->scale, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f);
            HuPrcVSleep();
        }
        HuVecCopy3F(&effectPos, &obj->coords);
        effectPos.y += 10.0f;
        func_800DCE40_name_81(0x44, &effectPos, 0, 1.0f);
        HuPrcSleep(10);
        func_800DCE40_name_81(0x44, &effectPos, 0, 1.0f);
        HuPrcSleep(12);
        for (i = 128; i >= 0; i -= 10) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(obj->omObj1->model[0], 0);
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_8010554C_name_81 & 8, D_8010571C_name_81);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_8010554C_name_81 & 1, -1);
        }
    }
    if (!(D_80105718_name_81 & 0x10)) {
        func_800ED214_name_81(playerIndex);
        HuVecCopyXYZ(&obj->scale, 1.0f, 1.0f, 1.0f);
        for (i = 0; i < 256; i += 10) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(obj->omObj1->model[0], 255);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010988C_duel02);

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_8010A214_duel02);

void func_8010AAB4_duel02(Object *obj, s32 swap) {
    Object *model;
    f32 scale;
    f32 angle;

    if (swap) {
        D_80117618_duel02 = func_800D8010_name_81(8, D_801165A8_duel02);
        func_800D8944_name_81(D_80117618_duel02);
        func_800D8F0C_name_81(D_80117618_duel02);
    } else {
        HuPrcSleep(3);
    }
    model = func_800D8010_name_81(0x21, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &obj->coords);
    model->coords.y += 5.0f;
    HuAudFXPlay(0x1E3);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = scale + 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (swap) {
        HuVecCopy3F(&D_80117618_duel02->coords, &obj->coords);
        HuVecCopy3F(&D_80117618_duel02->rot, &obj->rot);
        func_800D8E88_name_81(D_80117618_duel02);
        func_800D8F0C_name_81(obj);
    }

    for (; scale >= 1.0f; scale = scale - 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    func_800D8F3C_name_81(model);
}

void func_8010AD4C_duel02(Object *obj) {
    Object *model;
    f32 scale;
    f32 angle;

    model = func_800D8010_name_81(0x21, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &D_80117618_duel02->coords);
    model->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = scale + 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    HuVecCopy3F(&obj->coords, &D_80117618_duel02->coords);
    HuVecCopy3F(&obj->rot, &D_80117618_duel02->rot);
    func_800D8F3C_name_81(D_80117618_duel02);
    func_800D8E88_name_81(obj);
    obj->flags &= ~1;

    for (; scale >= 1.0f; scale = scale - 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    func_800D8F3C_name_81(model);
}

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

void func_8010B134_duel02(omObjData *object) {
    UnkDuelObjData *data = object->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            data->unk_000[i].x += data->unk_0C0[i].x;
            data->unk_000[i].y += data->unk_0C0[i].y;
            data->unk_000[i].z += data->unk_0C0[i].z;
            if (data->unk_000[i].y < 0.0f) {
                data->unk_000[i].y = 0.0f;
            }
            Hu3DModelPosSet(data->unk_1C0[i], data->unk_000[i].x, data->unk_000[i].y, data->unk_000[i].z);
            data->unk_1E4[i] -= 2.0f;
            if (data->unk_1E4[i] <= 0.0f) {
                data->unk_180[i] = 0;
                func_8001C258_main(data->unk_1C0[i], 4, 4);
                func_800146DC_main(data->unk_1A0[i], 0, 0x80);
            }
            data->unk_224[i] += 0.02f;
            if (data->unk_224[i] >= 3.0f) {
                data->unk_224[i] = 3.0f;
            }
            Hu3DModelScaleSet(data->unk_1C0[i], data->unk_224[i], data->unk_224[i], data->unk_224[i]);
        }
    }
    if (object->work[0] == 1) {
        if (data->unk_1E0 == 0) {
            for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
                if (data->unk_180[i] == 0) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(data->unk_180)) {
                data->unk_180[i] = 1;
                data->unk_1E0 = 1;
                data->unk_0C0[i].x = D_80117618_duel02->rot.x;
                data->unk_0C0[i].y = -0.8f;
                data->unk_0C0[i].z = D_80117618_duel02->rot.z;
                func_800D7828_name_81(&data->unk_0C0[i]);
                data->unk_0C0[i].x *= 2.0f;
                data->unk_0C0[i].y *= 2.0f;
                data->unk_0C0[i].z *= 2.0f;
                data->unk_000[i].x = D_80117618_duel02->rot.x * 10.0f + D_80117618_duel02->coords.x;
                data->unk_000[i].z = D_80117618_duel02->rot.z * 10.0f + D_80117618_duel02->coords.z;
                data->unk_000[i].y = D_80117618_duel02->coords.y + 6.0f;
                data->unk_1E4[i] = 15.0f;
                data->unk_224[i] = 0.1f;
                func_8001C258_main(data->unk_1C0[i], 4, 0);
                func_80014850_main(data->unk_1A0[i]);
                Hu3DModelPosSet(data->unk_1C0[i], data->unk_000[i].x, data->unk_000[i].y, data->unk_000[i].z);
                Hu3DModelScaleSet(data->unk_1C0[i], data->unk_224[i], data->unk_224[i], data->unk_224[i]);
                Hu3DModelCameraSet(data->unk_1C0[i], 1);
            }
        } else {
            data->unk_1E0--;
        }
    }
}

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

s32 func_8010EDE0_duel02(void) {
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
                    for (i = 0; D_80116604_duel02[i * 2] != -1; i++) {
                        if (D_80116604_duel02[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    partner = D_80116604_duel02[i * 2];
                    break;
                }
            }
            for (i = 0; D_80116700_duel02[player->chr][i * 2] != -1; i++) {
                if (D_80116700_duel02[player->chr][i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            partner = D_80116700_duel02[player->chr][i * 2];
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

void func_8011268C_duel02(void) {
    GW_PLAYER *player;
    Object *obj;
    void *handles[2];
    f32 scale;
    f32 angle;
    s32 curPlayer;
    s32 otherPlayer;

    curPlayer = MBDGetCurrentPlayerIndex();
    otherPlayer = (curPlayer + 1) & 1;
    player = MBDGetPlayerStruct(CUR_PLAYER);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x21, NULL);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1F9);
    handles[0] = func_800FFC2C_name_81(0, 3, 5);
    handles[1] = func_800FFC2C_name_81(1, 3, 5);
    angle = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }
    func_800EA898_name_81(otherPlayer, curPlayer);
    func_800EA7D4_name_81();
    func_800EA97C_name_81();
    while (scale >= 1.0f) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
        scale -= 0.5;
    }
    func_800FFCCC_name_81(handles[0]);
    func_800FFCCC_name_81(handles[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB49C_name_81(0x16, 0x1F2B, D_80101200_shared_board[GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr], 0, 0, 0, 0);
    func_800EB278_name_81();
    func_800EB29C_name_81();
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    func_800F3880_name_81(-1, 6, 0);
    PlayerFXPlay(0x2BD, GwSystem.current_player_index);
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
}

void func_80112A08_duel02(void) {
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

void func_80112BF4_duel02(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel02/3EC590", func_80112DE0_duel02);

void func_80113618_duel02(void) {
    GW_PLAYER *player;
    Object *obj;
    void *handles[2];
    f32 scale;
    f32 angle;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuPrcSleep(10);
    HuAudFXPlay(0x1FB);
    func_800EE74C_name_81(4);
    HuPrcSleep(15);
    obj = func_800D8010_name_81(0x22, NULL);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1FE);
    handles[0] = func_800FFC2C_name_81(0, 2, 5);
    handles[1] = func_800FFC2C_name_81(1, 2, 5);
    angle = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }
    func_800EA8DC_name_81();
    func_800EA97C_name_81();
    while (scale >= 1.0f) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        func_8008A430_main(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
        scale -= 0.5;
    }
    func_800FFCCC_name_81(handles[0]);
    func_800FFCCC_name_81(handles[1]);
    func_800D8F3C_name_81(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2D);
    func_800EDF78_name_81();
    func_800EE468_name_81(2);
    func_800EDDBC_name_81();
    CharFXPlay(0x286, GwPlayer[GwSystem.current_player_index].chr);
    func_800F3880_name_81(-1, 5, 0);
    func_800EFABC_name_81(player->player_obj);
}

void func_80113910_duel02(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

void func_8011394C_duel02(void) {
    UnkBoard4 *sprite;
    void *data;
    s32 i;
    s32 offset;

    mbItemBtnF = 0;
    func_800F74E4_name_81(-1);
    HuAudFXPlay(0x204);
    sprite = func_800F4528_name_81(2, 2);
    data = DataRead(0x130103);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 1);
    HuSprAttrSet(sprite->unk_0A, 0, 0x1000);
    HuSprPosSet(sprite->unk_0A, 0, 160, -32);
    HuSprScissorSet(sprite->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    sprite->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 1, sprite->unk_0C[1], 0);
    HuSprPriSet(sprite->unk_0A, 1, 2);
    HuSprAttrSet(sprite->unk_0A, 1, 0x1000);
    HuSprPosSet(sprite->unk_0A, 1, 0, 0);
    HuSprScissorSet(sprite->unk_0A, 0, 16, 12, 304, 228);
    HuSprColorSet(sprite->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    HuSprPosSet(sprite->unk_0A, 0, 160, 120);
    offset = 0;
    for (i = 0; i < 9; i++) {
        offset += i * 2;
        HuSprPosSet(sprite->unk_0A, 0, 160, 120 - offset);
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), func_800E0924_name_81());
    HuPrcChildWatch();
    func_800F4584_name_81(sprite);
    func_800F75EC_name_81(-1);
    D_80116788_duel02[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

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
