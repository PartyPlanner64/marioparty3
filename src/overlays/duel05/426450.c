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

// Inlined Y rotation matrix build.
#define MTX_ROTY(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[2][0], &(mtx)[2][2]);                                        \
        (mtx)[0][2] = -(mtx)[2][0];                                                         \
        (mtx)[0][0] = (mtx)[2][2];                                                          \
        (mtx)[0][1] = (mtx)[0][3] = (mtx)[1][0] = (mtx)[1][2] = (mtx)[1][3] = (mtx)[2][1] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[1][1] = (mtx)[3][3] = 1.0f;                                                   \
    }

typedef struct Duel05CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel05CamShakeWork; // sizeof 0x10

typedef struct Duel05SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel05SpriteWork; // sizeof 0x10

typedef struct Duel05PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel05PartnerAttackWork; // sizeof 0x10

typedef struct Duel05WinColorWork {
    /* 0x00 */ s32 window;
    /* 0x04 */ char unk_04[0xC];
} Duel05WinColorWork; // sizeof 0x10

typedef struct Duel05PartnerRouletteWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ char unk_04[0xC];
} Duel05PartnerRouletteWork; // sizeof 0x10

// Board space indices used when a player picks up a partner.
typedef struct Duel05PartnerSpaces {
    /* 0x00 */ s32 returnSpace;
    /* 0x04 */ s32 startSpace;
    /* 0x08 */ s32 partnerSpace;
} Duel05PartnerSpaces; // sizeof 0xC

typedef struct Duel05SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel05SwayWork; // sizeof 0x10

void *memcpy(void *, const void *, unsigned int);
s32 func_8010EB58_duel05(void);
extern Vec D_80115F60_duel05[];
extern s16 D_80115F58_duel05[];
extern u8 D_80115F54_duel05[];
extern s16 D_80115ED0_duel05[][2];
extern s32 D_80115EDC_duel05[];
extern s32 D_80115EF4_duel05[];
extern s32 D_80115838_duel05;
void func_8010EF8C_duel05(void);
s32 func_800E1854_minigame(s32);
Process *func_800EBC60_name_81(Vec *, Vec *, Vec *, s32);
void func_800EB7BC_name_81(Vec *);
void func_800FC8DC_name_81(Object *);
void func_8010F0FC_duel05(void);
extern Vec D_80115F24_duel05[];
extern Object *D_80115834_duel05;
extern s32 D_80115830_duel05;
extern Duel05PartnerSpaces D_80115818_duel05[];
extern char D_80115DC0_duel05[];
extern s32 D_801156B0_duel05[];
Process *func_800FAB68_name_81(Object *, s32, s32, s32, s32);
Process *func_800DCE40_name_81(s32, Vec *, Vec *, f32);
extern void (*D_80115880_duel05[])(void);
Process *func_800E0924_name_81(void);
extern s32 D_80101200_shared_board[];
extern Object *D_801163B4_duel05;
extern Object *D_801163B0_duel05;
extern s32 D_801156B8_duel05[];
extern Object *D_801163B8_duel05;
extern s8 *D_801157F8_duel05[];
extern s8 D_801156FC_duel05[];
void func_8010B140_duel05(omObjData *);
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
extern f32 D_801156CC_duel05;
extern s16 D_801156E2_duel05;
extern s16 D_801156E0_duel05;
extern s16 D_801156EA_duel05;
extern s16 D_801156E8_duel05;
void func_800FADB4_name_81(void);
void func_800FAE18_name_81(Object *, s32, s32);
extern s16 D_80115EA0_duel05[];
extern char D_80115E78_duel05[];
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_80106838_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107198_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801079C8_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80107ECC_duel05(s32, s32, Object *, Object *, s32, s32);
void func_801084B4_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80108560_duel05(s32, s32, Object *, Object *, s32, s32);
void func_80109898_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010A220_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010B55C_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010BCE4_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010CE78_duel05(s32, s32, Object *, Object *, s32, s32);
void func_8010D434_duel05(s32, s32, Object *, Object *, s32, s32);
extern Object *D_801163C0_duel05;
extern s16 D_80115EB8_duel05[];
void func_8010E1C4_duel05(void);
extern void func_80105CD0_duel05(void);
extern void func_80106318_duel05(void);
extern void func_8010E7D0_duel05(void);
void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx);
extern omObjData *D_801163BC_duel05;
extern Object *D_801163C8_duel05;
extern Object *D_801163D0_duel05;
void func_8010DA04_duel05(void);
void func_800FF640_name_81(s32);
f32 func_800D76D0_name_81(Vec *);
s32 func_800E88FC_name_81(void);
extern s32 D_801163A0_duel05;
extern s32 D_801163A4_duel05;
extern s32 D_801163A8_duel05;
extern s32 D_801163AC_duel05;
void func_800EB708_name_81(Vec *, Vec *, Vec *);
Process *func_800EBF2C_name_81(Vec *, Vec *, Vec *, s32);
void func_800F38DC_name_81(s32, s32, s32);
void func_80110038_duel05(s32);
void func_80115370_duel05(s8 *, s8 *);
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_80105F30_duel05(void);
extern Process *D_801156E4_duel05;
extern f32 D_801163CC_duel05;
void func_8010DDFC_duel05(void);
extern Process *D_801156EC_duel05;
extern f32 D_801163D4_duel05;
void func_8010E408_duel05(void);
extern event_table_entry D_801158B0_duel05[];
extern event_table_entry D_80115D00_duel05[];
void func_800EA46C_name_81(event_table_entry *);
void func_800FC59C_name_81(s32 (*)(void));
void func_800FC5A8_name_81(process_func);
void func_801138DC_duel05(void);
s32 func_80115378_duel05(void);

void func_801059D0_duel05(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel05(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_801163A0_duel05 = func_800E1824_name_81(0, 0xA0, 1);
    D_801163A4_duel05 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_801163A8_duel05 = func_800E1824_name_81(1, 0xBC, 1);
    D_801163AC_duel05 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel05(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_801163A0_duel05);
    func_800E1854_name_81(D_801163A4_duel05);
    func_800E1854_name_81(D_801163A8_duel05);
    func_800E1854_name_81(D_801163AC_duel05);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105B64_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80105BA0_duel05);

void func_80105C74_duel05(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

void func_80105CD0_duel05(void) {
    Duel05SpriteWork *work = HuPrcCurrentGet()->user_data;
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

void func_80105F30_duel05(void) {
    Process *process = HuPrcCurrentGet();
    Duel05PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
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
    func_80105EC0_duel05(obj);
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

Process *func_801060E0_duel05(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel05PartnerAttackWork *work;

    process = omAddPrcObj(func_80105F30_duel05, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void func_8010616C_duel05(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
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

void func_80106250_duel05(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

Process *func_80106270_duel05(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        process = func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
    return process;
}

void func_801062D0_duel05(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_80106318_duel05(void) {
    Duel05CamShakeWork *work = HuPrcCurrentGet()->user_data;
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

void func_801064D8_duel05(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *model;

    player = MBDGetPlayerStruct(playerIndex);
    switch (mode) {
        case 0:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                model = func_800D8010_name_81(0x28, NULL);
                D_801163B0_duel05 = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                model = func_800D8010_name_81(0x28, NULL);
                D_801163B4_duel05 = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                func_800D8F0C_name_81(partner);
            }
            break;
        case 1:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
                func_800D8F3C_name_81(D_801163B0_duel05);
                func_800D8E88_name_81(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                func_800D8F3C_name_81(D_801163B4_duel05);
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
                        D_801163B0_duel05 = model;
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
                        D_801163B4_duel05 = model;
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
                        func_800D8F3C_name_81(D_801163B0_duel05);
                        func_800D8E88_name_81(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
                        func_800D8F3C_name_81(D_801163B4_duel05);
                        func_800D8E88_name_81(partner);
                    }
                    break;
            }
            break;
    }
}

Object *func_80106750_duel05(s32 arg0) {
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

void func_801067E4_duel05(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0);
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

void func_80106838_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *extra;
    s32 model;
    f32 angle;
    f32 speed;
    Vec targetPos;
    Vec origPos;
    Vec delta;
    Process *spinProcesses[2];
    Vec midPos;
    Vec *mid;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    spinProcesses[0] = NULL;
    spinProcesses[1] = NULL;
    effect = NULL;
    extra = NULL;
    model = -1;
    func_800FAD04_name_81(0);
    if (mode == 1) {
        effect = func_80106750_duel05(0x45);
    }
    partner = func_800D8010_name_81(D_801156B0_duel05[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    func_800D8944_name_81(partner);
    func_800D8F0C_name_81(partner);
    if (mode == 2) {
        extra = func_800D8010_name_81(0x56, NULL);
        func_800D8944_name_81(extra);
        func_800D8F0C_name_81(extra);
    }
    func_80106250_duel05();
    HuAudFXPlay(0x25A);
    func_800FAE18_name_81(obj, 0, 0);
    func_800EFABC_name_81(obj);
    func_800FAE18_name_81(obj, 1, 2);
    if (mode == 2) {
        HuAudFXPlay(0x1D6);
        angle = 0.0f;
        for (speed = 0.0f; speed <= 30.0f; speed += 2.0f) {
            HuPrcVSleep();
            angle += speed;
            MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        }
        spinProcesses[0] = func_800D9668_name_81(obj, angle, 30.0f, -1);
        HuVecCopy3F(&extra->coords, &obj->coords);
        func_800D8E88_name_81(extra);
        spinProcesses[1] = func_800D9668_name_81(extra, 0.0f, 30.0f, -1);
        HuPrcSleep(20);
    }
    func_8010616C_duel05(obj, target, player, &targetPos, &origPos, 6.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 3.0f));
    HuVecSubtract(&delta, &obj->coords, &targetPos);
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 3.0f));
    if (mode == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&extra->coords, &targetPos, &extra->coords, 3.0f));
    }
    func_80106270_duel05(target, player, flags, 3.0f);
    if (flags & 8) {
        func_801060E0_duel05(player, target, HuVecGetLength3F(&delta) / 3.0f, 20);
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
    } else {
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
        if (mode == 1) {
            func_801067E4_duel05(effect, &obj->coords);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            func_800DCE40_name_81(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                func_80105C74_duel05(&target->coords, &effect->coords, &effect->rot);
                func_801067E4_duel05(effect, &target->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
                func_800DD2DC_name_81(model, &midPos);
            }
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            func_800DCE40_name_81(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                func_80105C74_duel05(&player->player_obj->coords, &effect->coords, &effect->rot);
                func_801067E4_duel05(effect, &player->player_obj->coords);
            } else {
                model = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
                func_800DD2DC_name_81(model, &midPos);
            }
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &origPos, &obj->coords, 3.0f));
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &origPos, &partner->coords, 3.0f));
    if (mode == 2) {
        HuPrcChildLink(process, func_800EC1E4_name_81(&extra->coords, &origPos, &extra->coords, 3.0f));
    }
    HuPrcChildWatch();
    func_800D8F0C_name_81(partner);
    if (spinProcesses[0] != NULL) {
        omDelPrcObj(spinProcesses[0]);
    }
    if (mode == 2) {
        if (spinProcesses[1] != NULL) {
            omDelPrcObj(spinProcesses[1]);
        }
        func_800D8F0C_name_81(extra);
    }
    MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    func_800FAE18_name_81(obj, 0, 0);
    func_8001C814_main(obj->omObj1->model[0], 0, 4);
    Hu3DMotionTimeSet(obj->omObj1->model[0], 1000.0f);
    func_800EFB00_name_81(obj);
    func_800D90D0_name_81(obj, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(partner);
    if (mode == 1) {
        func_800D8F3C_name_81(effect);
    } else {
        func_800D8F3C_name_81(extra);
        if (model != -1) {
            while (!func_800DD3B4_name_81(model)) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(model);
        }
    }
    func_800FADB4_name_81();
}

void func_80107198_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *extra;
    Process *extraProcess;
    s32 i;
    f32 jumpSpeed;
    f32 jumpAccel;
    Vec targetPos;
    Vec origPos;
    s32 effectModels[2];
    Vec midPos;
    Vec *mid;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    effectModels[0] = 0x48;
    effectModels[1] = 0x49;
    extraProcess = NULL;
    effect = func_80106750_duel05(effectModels[mode - 1]);
    partner = func_800D8010_name_81(D_801156B0_duel05[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    func_800D8944_name_81(partner);
    func_800D8F0C_name_81(partner);
    if (mode == 2) {
        extra = func_800D8010_name_81(0x56, NULL);
        func_800D8944_name_81(extra);
        func_800D8F0C_name_81(extra);
    }
    func_800FAD04_name_81(1);
    func_800D90D0_name_81(obj, 0, 2);
    func_8010616C_duel05(obj, target, player, &targetPos, &origPos, 7.0f);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 3.0f));
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    func_800D8F0C_name_81(partner);
    if (mode == 2) {
        HuVecCopy3F(&extra->coords, &obj->coords);
        func_800D8E88_name_81(extra);
        extraProcess = func_800D9668_name_81(extra, 0, 30.0f, -1);
        jumpSpeed = 3.0f;
        jumpAccel = -0.375f;
        func_800EF7C8_name_81(extra, jumpSpeed, jumpAccel);
        func_800D8E88_name_81(partner);
        func_800EF7C8_name_81(partner, jumpSpeed, jumpAccel);
    }
    func_800FAE18_name_81(obj, 0, 2);
    func_800EF7C8_name_81(obj, mode + 1.0f, -(mode + 1.0f) / 8.0f);
    if (mode == 2) {
        for (i = 0; i < 8; i++) {
            MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, i * 45.0f);
            HuPrcVSleep();
        }
        MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    } else {
        HuPrcSleep(8);
    }
    obj->velocity.z = 0.0f;
    func_800FAE18_name_81(obj, 1, 0);
    if (mode == 2) {
        if (extraProcess != NULL) {
            omDelPrcObj(extraProcess);
        }
        func_800D8F0C_name_81(extra);
        func_800D8F0C_name_81(partner);
    }
    if (flags & 8) {
        func_801060E0_duel05(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        func_801067E4_duel05(effect, &obj->coords);
        HuAudFXPlay(0x25B);
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += obj->velocity.x;
        func_801067E4_duel05(effect, mid);
        if (mode == 2) {
            func_800DCE40_name_81(0x4B, &midPos, 0, 2.0f);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    func_800EFABC_name_81(obj);
    obj->velocity.z = -(mode + 1.0f) / 8.0f;
    func_800EF800_name_81(obj);
    func_800EB708_name_81(&obj->coords, &origPos, &obj->rot);
    func_800D90D0_name_81(obj, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &origPos, &obj->coords, 3.0f));
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &origPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    func_800D90D0_name_81(obj, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(effect);
    func_800D8F3C_name_81(partner);
    if (mode == 2) {
        func_800D8F3C_name_81(extra);
    }
    func_800FADB4_name_81();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115DC0_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801079C8_duel05);

void func_80107ECC_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *orig;
    Object *extra;
    f32 angle;
    Vec targetPos;
    Vec offset;
    s32 effectModels[2];
    Vec midPos;
    Vec *mid;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    effectModels[0] = 0x4F;
    effectModels[1] = 0x52;
    effect = func_80106750_duel05(effectModels[mode - 1]);
    HuVecCopyXYZ(&effect->scale, 2.0f, 2.0f, 2.0f);
    if (mode == 2) {
        HuPrcVSleep();
        extra = func_80106750_duel05(0x5B);
        HuPrcVSleep();
    }
    partner = func_800D8010_name_81(D_801156B0_duel05[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    func_800D8944_name_81(partner);
    func_800D8F0C_name_81(partner);
    func_800FAD04_name_81(3);
    if (mode == 2) {
        func_800D8F0C_name_81(obj);
        orig = obj;
        obj = func_800D8010_name_81(0x27, NULL);
        HuVecCopy3F(&obj->coords, &orig->coords);
        HuVecCopy3F(&obj->rot, &orig->rot);
    }
    func_800FAE98_name_81(obj, 0, 0, 5, 2);
    HuAudFXPlay(0x1DC);
    HuPrcSleep(20);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 2.0f);
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
        func_800EB708_name_81(&obj->coords, &targetPos, &obj->rot);
        angle = func_800D76D0_name_81(&obj->rot) + 180.0f;
        offset.x = sindf(angle) * 9.0f;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 9.0f;
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 2.0f));
        func_800D8E88_name_81(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 2.0f));
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
        HuAudFXPlay(0x256);
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
        func_800EB708_name_81(&obj->coords, &targetPos, &obj->rot);
        func_800EF7C8_name_81(obj, 7.5f, -0.825f);
        HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &targetPos, &obj->coords, 15));
        HuPrcChildWatch();
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
        func_800EB708_name_81(&obj->coords, &targetPos, &obj->rot);
        angle = func_800D76D0_name_81(&obj->rot) + 180.0f;
        offset.x = sindf(angle) * 6.0f / 2.0f;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 6.0f / 2.0f;
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 2.0f));
        func_800D8E88_name_81(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 2.0f));
        HuAudFXPlay(0x256);
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
    }
    func_800D8F0C_name_81(obj);
    obj->coords.y += obj->velocity.x;
    mid = &midPos;
    HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
    HuVecMulScalar(mid, 0.5f, mid);
    if (mode == 2) {
        func_801067E4_duel05(extra, &obj->coords);
        Hu3DMotionSpeedSet(extra->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        func_801067E4_duel05(effect, mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (mode == 1) {
        func_801067E4_duel05(effect, &midPos);
        HuAudFXPlay(0x1DD);
    } else {
        HuAudFXPlay(0x1DE);
    }
    MBDBackTPLvlSet(0xFF);
    HuPrcVSleep();
    MBDBackTPLvlSet(0x40);
    func_800FAC1C_name_81(&D_80105540_name_81);
    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
    HuPrcSleep(30);
    if (mode == 2) {
        func_800D8F3C_name_81(obj);
        func_800D8F3C_name_81(extra);
    }
    func_800D8F3C_name_81(partner);
    func_800D8F3C_name_81(effect);
    func_800FADB4_name_81();
}

void func_801084B4_duel05(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80108560_duel05);

void func_80109414_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    func_8010616C_duel05(obj, target, player, &targetPos, &origPos, 0.0f);
    HuVecSubtract(&dir, &obj->coords, &targetPos);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
    targetPos.y -= 5.0f;
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 3.0f));
    steps = HuVecGetLength3F(&dir) / 3.0f;
    obj->flags |= 1;
    if (flags & 8) {
        func_801060E0_duel05(player, target, HuVecGetLength3F(&dir) / 3.0f, 20);
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

void func_80109898_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    s32 sound;
    Vec nearPos;
    Vec origPos;
    Vec targetPos;
    Vec rot;
    Vec midPos;
    Vec *mid;
    f32 baseAngle;
    f32 angle;
    s32 i;
    s32 iAngle;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    sound = -1;
    if (mode & 0x10) {
        func_80109414_duel05(playerIndex, targetPlayer, obj, target, flags, 1);
        return;
    }
    mode &= ~0x10;
    func_800D90D0_name_81(obj, 0, 2);
    func_8010616C_duel05(obj, target, player, &targetPos, &origPos, 6.0f);
    func_8010616C_duel05(obj, target, player, &nearPos, &origPos, 8.0f);
    func_80106250_duel05();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(obj->omObj1->model[0], ~((i * 255) / 10));
        func_8001F9E4_main(obj->omObj2->model[0], ~((i * 255) / 10));
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    HuPrcChildLink(process, func_80106270_duel05(target, player, flags, 3.0f));
    HuPrcChildWatch();
    if (mode == 2) {
        sound = HuAudFXPlay(0x1DF);
        func_800EB708_name_81(&D_80105540_name_81, &obj->coords, &rot);
        baseAngle = func_800D76D0_name_81(&rot);
        iAngle = baseAngle + 90.0f;
        angle = iAngle;
        HuVecCopyXYZ(&obj->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y, D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&obj->coords, &D_80105540_name_81, &obj->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            func_8001F9E4_main(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            func_8001F9E4_main(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(obj->omObj1->model[0], 0);
        func_8001F9E4_main(obj->omObj2->model[0], 0);
        HuPrcVSleep();
        iAngle = baseAngle + -90.0f;
        angle = iAngle;
        HuVecCopyXYZ(&obj->coords, D_80105540_name_81.x + sindf(angle) * 8.0f, D_80105540_name_81.y, D_80105540_name_81.z + cosdf(angle) * 8.0f);
        func_800EB708_name_81(&obj->coords, &D_80105540_name_81, &obj->rot);
        for (i = 0; i <= 128; i += 20) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            func_8001F9E4_main(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            func_8001F9E4_main(obj->omObj1->model[0], i);
            func_8001F9E4_main(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        func_8001F9E4_main(obj->omObj1->model[0], 0);
        func_8001F9E4_main(obj->omObj2->model[0], 0);
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &nearPos);
    func_800EB708_name_81(&obj->coords, &D_80105540_name_81, &obj->rot);
    for (i = 0; i < 255; i += 10) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
        if (i == 160) {
            if (sound != -1) {
                HuAudFXStop((s16)sound);
            }
            HuAudFXPlay(0x257);
        }
    }
    func_8001F9E4_main(obj->omObj1->model[0], 255);
    func_8001F9E4_main(obj->omObj2->model[0], 255);
    HuPrcSleep(mode == 1 ? 10 : 3);
    HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &targetPos, &obj->coords, 3));
    if (flags & 8) {
        if (mode == 1) {
            func_801060E0_duel05(player, target, 0, 20);
        } else {
            func_801060E0_duel05(player, target, 0, 40);
        }
        HuPrcChildWatch();
        if (mode == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &nearPos, &obj->coords, 10));
            HuPrcChildWatch();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &targetPos, &obj->coords, 3));
            HuPrcChildWatch();
        }
    } else {
        HuPrcChildWatch();
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += 3.0f;
        func_800DCE40_name_81(0x59, &midPos, 0, 1.0f);
        HuAudFXPlay(0x1E0);
        if (mode == 2) {
            HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &nearPos, &obj->coords, 10));
            HuPrcChildWatch();
            HuPrcSleep(5);
            HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &targetPos, &obj->coords, 3));
            HuPrcChildWatch();
            func_800DCE40_name_81(0x59, &midPos, 0, 1.0f);
            HuAudFXPlay(0x1E0);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, func_800EBF2C_name_81(&obj->coords, &nearPos, &obj->coords, 10));
    HuPrcChildWatch();
    for (i = 0; i < 10; i++) {
        func_8001F9E4_main(obj->omObj1->model[0], ~((i * 255) / 10));
        func_8001F9E4_main(obj->omObj2->model[0], ~((i * 255) / 10));
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    func_800ED214_name_81(playerIndex);
    for (i = 0; i < 256; i += 10) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 255);
    func_8001F9E4_main(obj->omObj2->model[0], 255);
}

void func_8010A220_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *extra;
    Object *effect;
    Object *partner;
    Vec targetPos;
    Vec pos;
    Object *pieces[16];
    Vec effectPos;
    Vec startPos;
    Vec dir;
    Vec *vel;
    s32 i;
    s32 count;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    func_800FAD04_name_81(10);
    if (mode == 2) {
        extra = func_80106750_duel05(0x51);
        HuVecCopyXYZ(&extra->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    effect = func_80106750_duel05(0x4C);
    HuVecCopyXYZ(&effect->scale, 2.0f, 2.0f, 2.0f);
    HuPrcVSleep();
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
    }
    func_800EB708_name_81(&obj->coords, &targetPos, &obj->rot);
    partner = func_800D8010_name_81(0x57, NULL);
    func_800D8F0C_name_81(partner);
    HuVecCopy3F(&partner->coords, &obj->coords);
    partner->coords.y += 5.0f;
    targetPos.y += 5.0f;
    if (mode == 2) {
        HuVecCopyXYZ(&partner->scale, 2.0f, 2.0f, 2.0f);
        for (i = 0; i < 16; i++) {
            pieces[i] = func_800D8B18_name_81(partner);
            HuVecCopy3F(&pieces[i]->coords, &partner->coords);
            func_800D8F0C_name_81(pieces[i]);
            HuVecCopyXYZ(&pieces[i]->scale, 0.5f, 0.5f, 0.5f);
        }
    }
    func_800FAE18_name_81(obj, 0, 0);
    HuPrcSleep(20);
    func_800D8E88_name_81(partner);
    func_800EF7C8_name_81(partner, 3.0f, -0.18f);
    HuPrcChildLink(process, func_800EBF2C_name_81(&partner->coords, &targetPos, &partner->coords, 30));
    if (mode == 2) {
        for (i = 0; i < 16; i++) {
            HuVecCopy3F(&pos, &targetPos);
            pos.x += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            pos.y += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            pos.z += func_800EFE20_name_81(100.0f) / 15.0f - 3.3f;
            func_800EF7C8_name_81(pieces[i], 3.0f, -0.18f);
            HuPrcChildLink(process, func_800EBF2C_name_81(&pieces[i]->coords, &pos, &pieces[i]->coords, 30));
        }
    }
    HuAudFXPlay(0x1E1);
    func_80106250_duel05();
    func_801062D0_duel05(target, player, flags, 30);
    if (flags & 8) {
        HuVecCopy3F(&effectPos, &target->coords);
        effectPos.y += 5.0f;
        func_801060E0_duel05(player, target, 25, 40);
        if (mode == 1) {
            HuPrcSleep(32);
        } else {
            HuPrcSleep(20);
            func_800D8F0C_name_81(partner);
            HuVecCopy3F(&startPos, &partner->coords);
            startPos.y += partner->velocity.x;
            HuVecSubtract(&dir, &target->coords, &startPos);
            HuVecMulScalar(&dir, 0.05f, &dir);
            func_800DCC8C_name_81(0x4E, &startPos, &dir, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(pieces[i]);
                pieces[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                pieces[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
            HuPrcChildWatch();
        }
        func_801067E4_duel05(effect, &effectPos);
        if (mode == 2) {
            func_801067E4_duel05(extra, &effectPos);
        }
    } else {
        if (mode != 1) {
            HuPrcSleep(20);
            func_800D8F0C_name_81(partner);
            HuVecCopy3F(&effectPos, &partner->coords);
            effectPos.y += partner->velocity.x;
            if (flags & 1) {
                vel = &dir;
                HuVecSubtract(vel, &target->coords, &effectPos);
            } else {
                vel = &dir;
                HuVecSubtract(vel, &player->player_obj->coords, &effectPos);
            }
            HuVecMulScalar(vel, 0.05f, vel);
            func_800DCC8C_name_81(0x4E, &effectPos, &dir, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                func_800D8E88_name_81(pieces[i]);
                pieces[i]->velocity.z = func_800EFE20_name_81(100.0f) / 1000.0f + -0.18f - 0.05f;
                pieces[i]->velocity.y += func_800EFE20_name_81(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
        }
        HuPrcChildWatch();
        if (flags & 1) {
            HuVecCopy3F(&effectPos, &target->coords);
        } else {
            HuVecCopy3F(&effectPos, &player->player_obj->coords);
        }
        effectPos.y += 5.0f;
        func_801067E4_duel05(effect, &effectPos);
        if (mode == 2) {
            func_801067E4_duel05(extra, &effectPos);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            HuAudFXPlay((D_80105718_name_81 & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((D_80105718_name_81 & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    if (mode == 2) {
        while (TRUE) {
            count = 0;
            for (i = 0; i < 16; i++) {
                if (!func_800EF7D4_name_81(pieces[i])) {
                    func_800D8F0C_name_81(pieces[i]);
                    count++;
                }
            }
            if (i == count) {
                break;
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 16; i++) {
            func_800D8F3C_name_81(pieces[i]);
        }
    }
    func_800D8F3C_name_81(partner);
    func_800D90D0_name_81(obj, -1, 2);
    func_800ED214_name_81(playerIndex);
    HuPrcSleep(30);
    func_800D8F3C_name_81(effect);
    if (mode == 2) {
        func_800D8F3C_name_81(extra);
    }
    func_800FADB4_name_81();
}

void func_8010AAC0_duel05(Object *obj, s32 swap) {
    Object *model;
    f32 scale;
    f32 angle;

    if (swap) {
        D_801163B8_duel05 = func_800D8010_name_81(8, D_801156B8_duel05);
        func_800D8944_name_81(D_801163B8_duel05);
        func_800D8F0C_name_81(D_801163B8_duel05);
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
        HuVecCopy3F(&D_801163B8_duel05->coords, &obj->coords);
        HuVecCopy3F(&D_801163B8_duel05->rot, &obj->rot);
        func_800D8E88_name_81(D_801163B8_duel05);
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

void func_8010AD58_duel05(Object *obj) {
    Object *model;
    f32 scale;
    f32 angle;

    model = func_800D8010_name_81(0x21, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &D_801163B8_duel05->coords);
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

    HuVecCopy3F(&obj->coords, &D_801163B8_duel05->coords);
    HuVecCopy3F(&obj->rot, &D_801163B8_duel05->rot);
    func_800D8F3C_name_81(D_801163B8_duel05);
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

void func_8010AFC4_duel05(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    func_800142A0_main(0x1A);
    D_801163BC_duel05 = omAddObj(0x1F4, 0, 0, -1, func_8010B140_duel05);
    data = D_801163BC_duel05->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
    sprData = DataRead(0xB0047);
    for (i = 0; i < ARRAY_COUNT(data->sprId); i++) {
        if (i == 0) {
            data->sprId[0] = Hu3DSprModelCreate(sprData, 0x1A0D, 8);
        } else {
            data->sprId[i] = func_80014618_main(data->sprId[0], 8);
        }
        func_800146DC_main(data->sprId[i], 6, 0x180);
        data->modelId[i] = D_800CBB60_main[data->sprId[i]].modelId;
        func_800147FC_main(data->sprId[i], 0xFF, 0x40, 8);
        func_80014794_main(data->sprId[i], 0xC8);
        func_8001C2FC_main(data->modelId[i], 0x70000000, 0x70000000);
    }
    DataClose(sprData);
    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        data->active[i] = 0;
    }
    D_801163BC_duel05->work[0] = 0;
    data->spawnTimer = 0;
}

void func_8010B140_duel05(omObjData *object) {
    UnkDuelObjData *data = object->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        if (data->active[i] != 0) {
            data->pos[i].x += data->vel[i].x;
            data->pos[i].y += data->vel[i].y;
            data->pos[i].z += data->vel[i].z;
            if (data->pos[i].y < 0.0f) {
                data->pos[i].y = 0.0f;
            }
            Hu3DModelPosSet(data->modelId[i], data->pos[i].x, data->pos[i].y, data->pos[i].z);
            data->life[i] -= 2.0f;
            if (data->life[i] <= 0.0f) {
                data->active[i] = 0;
                func_8001C258_main(data->modelId[i], 4, 4);
                func_800146DC_main(data->sprId[i], 0, 0x80);
            }
            data->scale[i] += 0.02f;
            if (data->scale[i] >= 3.0f) {
                data->scale[i] = 3.0f;
            }
            Hu3DModelScaleSet(data->modelId[i], data->scale[i], data->scale[i], data->scale[i]);
        }
    }
    if (object->work[0] == 1) {
        if (data->spawnTimer == 0) {
            for (i = 0; i < ARRAY_COUNT(data->active); i++) {
                if (data->active[i] == 0) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(data->active)) {
                data->active[i] = 1;
                data->spawnTimer = 1;
                data->vel[i].x = D_801163B8_duel05->rot.x;
                data->vel[i].y = -0.8f;
                data->vel[i].z = D_801163B8_duel05->rot.z;
                func_800D7828_name_81(&data->vel[i]);
                data->vel[i].x *= 2.0f;
                data->vel[i].y *= 2.0f;
                data->vel[i].z *= 2.0f;
                data->pos[i].x = D_801163B8_duel05->rot.x * 10.0f + D_801163B8_duel05->coords.x;
                data->pos[i].z = D_801163B8_duel05->rot.z * 10.0f + D_801163B8_duel05->coords.z;
                data->pos[i].y = D_801163B8_duel05->coords.y + 6.0f;
                data->life[i] = 15.0f;
                data->scale[i] = 0.1f;
                func_8001C258_main(data->modelId[i], 4, 0);
                func_80014850_main(data->sprId[i]);
                Hu3DModelPosSet(data->modelId[i], data->pos[i].x, data->pos[i].y, data->pos[i].z);
                Hu3DModelScaleSet(data->modelId[i], data->scale[i], data->scale[i], data->scale[i]);
                Hu3DModelCameraSet(data->modelId[i], 1);
            }
        } else {
            data->spawnTimer--;
        }
    }
}

s16 func_8010B490_duel05(void) {
    UnkDuelObjData *data = D_801163BC_duel05->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        if (data->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4D0_duel05(void) {
    UnkDuelObjData *data = D_801163BC_duel05->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->sprId); i++) {
        func_80016638_main(data->sprId[i]);
    }
    omDelObj(D_801163BC_duel05);
    func_800166D0_main();
}

void func_8010B538_duel05(void) {
    D_801163BC_duel05->work[0] = 1;
}

void func_8010B54C_duel05(void) {
    D_801163BC_duel05->work[0] = 0;
}

void func_8010B55C_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *partner;
    s32 model;
    f32 angle;
    Vec targetPos;
    Vec origPos;
    Vec offset;
    Vec origRot;
    Vec midPos;
    Vec *mid;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    model = -1;
    func_800FAD04_name_81(11);
    if (flags != 0) {
        partner = func_800D8010_name_81(D_801156B0_duel05[mode - 1], NULL);
        Hu3DModelLayerSet(partner->omObj1->model[0], 0);
        Hu3DModelRemakeStatic(partner->omObj1->model[0]);
        func_800D8944_name_81(partner);
        func_800D8F0C_name_81(partner);
        func_800FAE18_name_81(obj, 0, 0);
        func_800EFABC_name_81(obj);
        func_8010AAC0_duel05(obj, 1);
        HuAudFXPlay(0x29C);
        func_800D90D0_name_81(D_801163B8_duel05, 0, 2);
        HuVecCopy3F(&origPos, &D_801163B8_duel05->coords);
        HuVecCopy3F(&origRot, &D_801163B8_duel05->rot);
        if (target != NULL) {
            HuVecCopy3F(&targetPos, &target->coords);
        } else {
            HuVecCopy3F(&targetPos, &player->player_obj->coords);
        }
        func_800EB708_name_81(&D_801163B8_duel05->coords, &targetPos, &D_801163B8_duel05->rot);
        angle = func_800D76D0_name_81(&D_801163B8_duel05->rot) + 180.0f;
        if (mode == 1) {
            offset.x = sindf(angle) * 6.0f * 2.5f;
            offset.y = 0.0f;
            offset.z = cosdf(angle) * 6.0f * 2.5f;
        } else {
            offset.x = sindf(angle) * 6.0f * 3.0f;
            offset.y = 0.0f;
            offset.z = cosdf(angle) * 6.0f * 3.0f;
        }
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, func_800EC1E4_name_81(&D_801163B8_duel05->coords, &targetPos, &D_801163B8_duel05->coords, 0.5f));
        func_80106250_duel05();
        func_80106270_duel05(target, player, flags, 0.8f);
        func_800D8E88_name_81(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &D_801163B8_duel05->coords);
        func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 0.5f));
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
        if (mode == 1) {
            func_800D90D0_name_81(D_801163B8_duel05, 3, 0);
            if (flags & 8) {
                func_801060E0_duel05(player, target, 0, 50);
            } else {
                HuPrcSleep(8);
                mid = &midPos;
                if (flags & 1) {
                    HuVecAdd(mid, &target->coords, &D_801163B8_duel05->coords);
                } else {
                    HuVecAdd(mid, &player->player_obj->coords, &D_801163B8_duel05->coords);
                }
                HuVecMulScalar(mid, 0.5f, mid);
                midPos.y += 5.0f;
                model = func_800DD1E0_name_81(0xB0025, D_80115DC0_duel05);
                func_800DD2DC_name_81(model, &midPos);
                func_800FAC1C_name_81(&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                    if (D_80105718_name_81 & 8) {
                        HuAudFXPlay(0x1CE);
                    } else {
                        HuAudFXPlay(0x1CD);
                    }
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                    if (!(flags & 1)) {
                        if (D_80105718_name_81 & 1) {
                            HuAudFXPlay(0x1CE);
                        } else {
                            HuAudFXPlay(0x1CD);
                        }
                    }
                }
            }
            func_800EFABC_name_81(D_801163B8_duel05);
            func_800D90D0_name_81(D_801163B8_duel05, -1, 2);
            HuPrcSleep(20);
        } else {
            func_800D90D0_name_81(D_801163B8_duel05, 1, 0);
            HuPrcSleep(30);
            func_8010AFC4_duel05();
            func_8010B538_duel05();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                func_801060E0_duel05(player, target, 0, 50);
            }
            func_800EFABC_name_81(D_801163B8_duel05);
            func_800D90D0_name_81(D_801163B8_duel05, 2, 2);
            if (!(flags & 8)) {
                func_800FAC1C_name_81(&D_80105540_name_81);
                if (flags & 1) {
                    func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
                }
                if (flags & 2) {
                    func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
                }
            }
            HuPrcSleep(30);
            func_8010B54C_duel05();
            while (func_8010B490_duel05()) {
                HuPrcVSleep();
            }
            func_800D918C_name_81(D_801163B8_duel05, -1, 0, 5, 2);
            HuPrcSleep(10);
            func_8010B4D0_duel05();
        }
        func_8010AD58_duel05(obj);
        func_800EB708_name_81(&obj->coords, &origPos, &obj->rot);
        func_800D90D0_name_81(obj, 0, 2);
        HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &origPos, &obj->coords, 3.0f));
        func_800D8E88_name_81(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        func_800EB708_name_81(&partner->coords, &origPos, &partner->rot);
        HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &origPos, &partner->coords, 3.0f));
        HuPrcChildWatch();
        func_800D90D0_name_81(obj, -1, 2);
        func_800ED214_name_81(playerIndex);
        func_800D8F3C_name_81(partner);
        if (mode == 1) {
            if (model != -1) {
                while (!func_800DD3B4_name_81(model)) {
                    HuPrcVSleep();
                }
                func_800DD2BC_name_81(model);
            }
        }
    } else {
        func_800FAE18_name_81(obj, 0, 0);
        func_800EFABC_name_81(obj);
        func_8010AAC0_duel05(obj, 0);
        HuAudFXPlay(0x2A0);
        func_80105EC0_duel05(obj);
        HuPrcSleep(10);
        func_800FAE18_name_81(obj, 1, 0);
        func_800EFABC_name_81(obj);
        func_800D90D0_name_81(obj, -1, 2);
    }
    func_800FADB4_name_81();
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010BCE4_duel05);

void func_8010CE78_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *partner;
    Object *partner2;
    Object *effect1;
    Object *effect2;
    Vec targetPos;
    Vec pos;
    s32 effectIds[2];
    s32 i;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    effectIds[0] = 0x4D;
    effectIds[1] = 0x53;
    partner2 = NULL;
    effect1 = NULL;
    effect2 = NULL;
    func_800FAD04_name_81(6);
    if (mode == 2) {
        effect1 = func_80106750_duel05(0x4C);
        HuPrcVSleep();
        effect2 = func_80106750_duel05(0x53);
        HuPrcVSleep();
    }
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
    }
    func_800EB708_name_81(&obj->coords, &targetPos, &obj->rot);
    partner = func_800D8010_name_81(0x58, NULL);
    func_800D8F0C_name_81(partner);
    HuPrcVSleep();
    if (mode == 2) {
        partner2 = func_800D8010_name_81(0x53, NULL);
        func_800D8F0C_name_81(partner2);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A3);
    func_800FAE98_name_81(obj, mode - 1, 0, 5, 2);
    if (mode == 1) {
        HuPrcSleep(7);
    } else {
        HuPrcSleep(15);
    }
    func_800D8E88_name_81(partner);
    HuVecCopy3F(&partner->coords, &obj->coords);
    partner->velocity.x = 5.0f;
    func_800D8F0C_name_81(partner);
    func_80106250_duel05();
    func_800D8E88_name_81(partner);
    HuPrcChildLink(process, func_800EC36C_name_81(&partner->coords, &targetPos, &partner->coords, 4.0f));
    HuPrcChildLink(process, func_80106270_duel05(target, player, flags, 4.0f));
    HuVecCopy3F(&pos, &obj->rot);
    func_800D7828_name_81(&pos);
    HuVecMulScalar(&pos, 6.0f, &pos);
    HuVecAdd(&pos, &pos, &partner->coords);
    pos.y += 5.0f;
    func_800DCE40_name_81(0x4E, &pos, 0, 0.5f);
    if (mode == 2) {
        func_800D8E88_name_81(partner2);
        func_8001C258_main(partner2->omObj1->model[0], 0x180, 0);
        Hu3DModelLayerSet(partner2->omObj1->model[0], 0x800);
        HuVecCopy3F(&partner2->coords, &partner->coords);
        partner2->velocity.x = 5.0f;
        HuPrcChildLink(process, func_800EC36C_name_81(&partner2->coords, &targetPos, &partner2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
    } else {
        HuAudFXPlay(0x1D9);
    }
    if (flags & 8) {
        func_801060E0_duel05(player, target, 0, 20);
        HuPrcChildWatch();
        func_800FC888_name_81(3);
        func_800D8F0C_name_81(partner);
        if (mode == 2) {
            func_800D8F0C_name_81(partner2);
        }
    } else {
        HuPrcChildWatch();
        func_800D8F0C_name_81(partner);
        if (mode == 2) {
            func_800D8F0C_name_81(partner2);
        }
        if (flags & 1) {
            HuVecCopy3F(&pos, &target->coords);
        } else {
            HuVecCopy3F(&pos, &player->player_obj->coords);
        }
        pos.y += partner->velocity.x;
        if (mode == 1) {
            func_800DCE40_name_81(effectIds[0], &pos, 0, 2.0f);
        } else {
            func_801067E4_duel05(effect1, &pos);
            HuVecCopyXYZ(&effect1->scale, 2.0f, 2.0f, 2.0f);
            func_801067E4_duel05(effect2, &pos);
            HuVecCopyXYZ(&effect2->scale, 2.0f, 2.0f, 2.0f);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            if (mode == 2) {
                if (D_80105718_name_81 & 8) {
                    HuAudFXPlay(0x1EF);
                } else {
                    HuAudFXPlay(0x1EE);
                }
            } else {
                if (D_80105718_name_81 & 8) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (mode == 2) {
                if (!(flags & 1)) {
                    if (D_80105718_name_81 & 1) {
                        HuAudFXPlay(0x1EF);
                    } else {
                        HuAudFXPlay(0x1EE);
                    }
                }
            } else if (!(flags & 1)) {
                if (D_80105718_name_81 & 1) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (mode == 2) {
            for (i = 0; i < 3; i++) {
                MBDBackTPLvlSet(0xFF);
                HuPrcVSleep();
                MBDBackTPLvlSet(0x40);
                HuPrcVSleep();
            }
        }
    }
    func_800D8F3C_name_81(partner);
    func_800D90D0_name_81(obj, -1, 2);
    func_800ED214_name_81(playerIndex);
    if (mode == 2) {
        HuPrcSleep(30);
        func_800D8F3C_name_81(effect1);
        func_800D8F3C_name_81(effect2);
        func_800D8F3C_name_81(partner2);
    }
    func_800FADB4_name_81();
}

void func_8010D434_duel05(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    s32 model;
    Vec targetPos;
    Vec origPos;
    Vec midPos;
    Vec *mid;

    player = MBDGetPlayerStruct(targetPlayer);
    process = HuPrcCurrentGet();
    model = -1;
    effect = NULL;
    if (mode == 1) {
        effect = func_80106750_duel05(0x45);
    }
    partner = func_800D8010_name_81(D_801156B0_duel05[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    func_800D8944_name_81(partner);
    func_800D8F0C_name_81(partner);
    func_800FAD04_name_81(7);
    func_800D90D0_name_81(obj, 0, 2);
    func_8010616C_duel05(obj, target, player, &targetPos, &origPos, 7.5f);
    func_80106250_duel05();
    func_80106270_duel05(target, player, flags, 3.0f);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &targetPos, &obj->coords, 3.0f));
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &targetPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    func_800D8F0C_name_81(partner);
    if (mode == 1) {
        func_800FAE18_name_81(obj, 0, 2);
    } else {
        func_800FAE18_name_81(obj, 1, 0);
    }
    if (flags & 8) {
        if (mode == 2) {
            HuPrcSleep(10);
        }
        func_801060E0_duel05(player, target, 0, 30);
        if (mode == 1) {
            HuPrcSleep(30);
        } else {
            func_800EFABC_name_81(obj);
        }
    } else {
        if (mode == 1) {
            HuPrcSleep(10);
        } else {
            HuPrcSleep(17);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += 5.0f;
        if (mode == 1) {
            func_800DCE40_name_81(0x4B, &midPos, 0, 2.0f);
            func_800EB804_name_81(effect);
            func_801067E4_duel05(effect, &midPos);
        } else {
            model = func_800DD1E0_name_81(0xB0024, D_80115DC0_duel05);
            func_800DD2DC_name_81(model, &midPos);
            HuAudFXPlay(0x1DB);
            HuAudFXPlay(0x1F1);
        }
        func_800FAC1C_name_81(&D_80105540_name_81);
        if (flags & 1) {
            func_800FAB68_name_81(target, D_80105550_name_81, 1, D_80105718_name_81 & 8, D_8010571C_name_81);
            if (D_80105718_name_81 & 8) {
                HuAudFXPlay(0x1CE);
            } else {
                HuAudFXPlay(0x1CD);
            }
        }
        if (flags & 2) {
            func_800FAB68_name_81(player->player_obj, D_80105558_name_81, 3, D_80105718_name_81 & 1, -1);
            if (!(flags & 1)) {
                if (D_80105718_name_81 & 1) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (mode == 2) {
            func_800EFABC_name_81(obj);
        } else {
            HuPrcSleep(10);
        }
    }
    func_800EB708_name_81(&obj->coords, &origPos, &obj->rot);
    func_800D90D0_name_81(obj, 0, 2);
    HuPrcChildLink(process, func_800EC1E4_name_81(&obj->coords, &origPos, &obj->coords, 3.0f));
    func_800D8E88_name_81(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    func_800EB708_name_81(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, func_800EC1E4_name_81(&partner->coords, &origPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    func_800D90D0_name_81(obj, -1, 2);
    func_800ED214_name_81(playerIndex);
    func_800D8F3C_name_81(partner);
    if (mode == 2) {
        if (model != -1) {
            while (!func_800DD3B4_name_81(model)) {
                HuPrcVSleep();
            }
            func_800DD2BC_name_81(model);
        }
    } else {
        func_800D8F3C_name_81(effect);
    }
    func_800FADB4_name_81();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115DF8_duel05);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115E04_duel05);

void func_8010D96C_duel05(void) {
    PartnerFunc attackFuncs[12] = {
        func_80106838_duel05, func_80107198_duel05, func_801079C8_duel05, func_80107ECC_duel05,
        func_80109898_duel05, func_801084B4_duel05, func_8010CE78_duel05, func_8010D434_duel05,
        func_8010BCE4_duel05, func_80108560_duel05, func_8010A220_duel05, func_8010B55C_duel05,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        func_80109898_duel05, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(attackFuncs, otherFuncs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DA04_duel05);

void func_8010DA94_duel05(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010DA04_duel05();
    func_800EA46C_name_81(D_801158B0_duel05);
    func_800EA46C_name_81(D_80115D00_duel05);
    func_800FC5A8_name_81(func_801138DC_duel05);
    func_800FC59C_name_81(func_80115378_duel05);
    func_800FF640_name_81(0);
}

void func_8010DB10_duel05(void) {
    Hu3DCamInit(1);
    func_8010DA04_duel05();
    func_800FF640_name_81(1);
}

void func_8010DB3C_duel05(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], Hu3DData[D_801163C0_duel05->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], "neji");
        angle += D_801156CC_duel05;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void func_8010DC14_duel05(void) {
    HmfMotionNode *node;

    func_8002FD8C_main(D_801163C0_duel05->omObj1->model[0], Hu3DData[D_801163C0_duel05->omObj1->model[0]].motId, D_80115E78_duel05, 0x4C, 0x46);
    node = func_8001D33C_main(D_801163C0_duel05->omObj1->model[0], D_80115E78_duel05);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010DCB8_duel05);

void func_8010DD4C_duel05(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x32, NULL);
    func_800D8944_name_81(obj);
    D_801163C8_duel05 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_801156E0_duel05);
    space2 = MBDMasuGet(D_801156E2_duel05);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010DDFC_duel05(void) {
    Duel05SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_801163C8_duel05->omObj1->model[0]].mtx, sindf(angle) * D_801163CC_duel05);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF78_duel05(Vec *pos) {
    Process *process;
    Duel05SwayWork *work;

    D_801163CC_duel05 = 10.0f;
    process = omAddPrcObj(func_8010DDFC_duel05, 0xA, 0, 0x40);
    D_801156E4_duel05 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05SwayWork));
    process->user_data = work;
    if (pos->x <= D_801163C8_duel05->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E018_duel05(void) {
    if (D_801156E4_duel05 != NULL) {
        while (D_801163CC_duel05 >= 0.0f) {
            D_801163CC_duel05 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801156E4_duel05);
        MTX_ROTZ(Hu3DData[D_801163C8_duel05->omObj1->model[0]].mtx, 0.0f);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel05/426450", D_80115E78_duel05);

void func_8010E1C4_duel05(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_801163C8_duel05->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_801163C8_duel05->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801163C8_duel05);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_801163C8_duel05->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_801163C8_duel05->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2DC_duel05(void) {
    omAddPrcObj(func_8010E1C4_duel05, 0xA, 0, 0);
}

void func_8010E308_duel05(void) {
    func_8001C814_main(D_801163C8_duel05->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801163C8_duel05->omObj1->model[0], 1.0f);
}

void func_8010E358_duel05(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x33, NULL);
    func_800D8944_name_81(obj);
    D_801163D0_duel05 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_801156E8_duel05);
    space2 = MBDMasuGet(D_801156EA_duel05);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010E408_duel05(void) {
    Duel05SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_801163D0_duel05->omObj1->model[0]].mtx, sindf(angle) * D_801163D4_duel05);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E584_duel05(Vec *pos) {
    Process *process;
    Duel05SwayWork *work;

    D_801163D4_duel05 = 10.0f;
    process = omAddPrcObj(func_8010E408_duel05, 0xA, 0, 0x40);
    D_801156EC_duel05 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05SwayWork));
    process->user_data = work;
    if (pos->x <= D_801163D0_duel05->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E624_duel05(void) {
    if (D_801156EC_duel05 != NULL) {
        while (D_801163D4_duel05 >= 0.0f) {
            D_801163D4_duel05 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_801156EC_duel05);
        MTX_ROTZ(Hu3DData[D_801163D0_duel05->omObj1->model[0]].mtx, 0.0f);
    }
}

void func_8010E7D0_duel05(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_801163D0_duel05->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_801163D0_duel05->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801163D0_duel05);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_801163D0_duel05->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_801163D0_duel05->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

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

s32 func_8010EC48_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 partnerValues[12];

    memcpy(partnerValues, D_80115EA0_duel05, sizeof(partnerValues));
    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

s32 func_8010ECF0_duel05(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80115EB8_duel05, sizeof(shakeAngles));
    return shakeAngles[index];
}

s32 func_8010ED70_duel05(void) {
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
                    for (i = 0; D_801156FC_duel05[i * 2] != -1; i++) {
                        if (D_801156FC_duel05[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    partner = D_801156FC_duel05[i * 2];
                    break;
                }
            }
            for (i = 0; D_801157F8_duel05[player->chr][i * 2] != -1; i++) {
                if (D_801157F8_duel05[player->chr][i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            partner = D_801157F8_duel05[player->chr][i * 2];
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8010EF8C_duel05);

void func_8010F0FC_duel05(void) {
    s16 pos[3][2];
    s32 files[6];
    u8 order[32]; // Only 12 are used; the size matches the original stack frame.
    s32 sfx[12];
    s32 player;
    s32 msgWindow;
    s16 window;
    Process *colorProcess;
    s32 state;
    s32 cpuPartner;
    Duel05WinColorWork *colorWork;
    UnkBoard4 *spr;
    void *data;
    s32 i;
    s32 angle;
    s32 count;
    u8 last;
    s32 max;
    s32 delay;

    memcpy(pos, D_80115ED0_duel05, sizeof(pos));
    memcpy(files, D_80115EDC_duel05, sizeof(files));
    player = ((Duel05PartnerRouletteWork *)HuPrcCurrentGet()->user_data)->player;
    colorProcess = NULL;
    cpuPartner = -1;
    mbItemBtnF = 0;
    if (player == 0) {
        state = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        state = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    window = HuWinCreate(60, -160, 200, 160, 0, 0);
    HuWinBGColSet(window, 0x43, 5, 1);
    HuWinBGTPLvlSet(window, 0xC0);
    if (state == 2) {
        colorProcess = omAddPrcObj(func_8010EF8C_duel05, 10, 0, 0x40);
        colorWork = HuMemMemoryAlloc(colorProcess->heap, sizeof(Duel05WinColorWork));
        colorProcess->user_data = colorWork;
        colorWork->window = window;
    }
    spr = func_800F4528_name_81(3, 0);
    for (i = 0; i < 3; i++) {
        data = DataRead(files[player * 3 + i]);
        spr->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(spr->unk_0A, i, spr->unk_0C[i], 0);
        HuSprPriSet(spr->unk_0A, i, i + 1);
        HuSprAttrSet(spr->unk_0A, i, 0);
        HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1]);
        DataClose(data);
        if (i == 2) {
            HuSprBankSet(spr->unk_0A, 2, func_800EFE20_name_81(12.0f), 0);
        }
    }
    for (angle = 90; angle < 180; angle += 15) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -200.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -200.0f + 55.0f);
        HuPrcVSleep();
    }
    for (angle = 0; angle < 180; angle += 20) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -50.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -50.0f + 55.0f);
        HuPrcVSleep();
    }
    for (angle = 0; angle < 180; angle += 20) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -30.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -30.0f + 55.0f);
        HuPrcVSleep();
    }
    max = 11;
    if (func_800F37B8_name_81(-1)) {
        count = func_800EFE20_name_81(10.0f) + 10;
        cpuPartner = func_8010ED70_duel05();
        if (state == 2 && cpuPartner != -1) {
            count = 5;
        }
    } else {
        count = -1;
    }
    msgWindow = func_800E1824_name_81(0x13, 0xB9, 0);
    D_80115838_duel05 = 1;
    last = 0xFF;
    do {
        func_800E0310_name_81(order, max);
        if (last == order[0]) {
            last = order[max];
            order[max] = order[0];
            order[0] = last;
            last = 0xFF;
        }
        for (i = 0; i <= max; i++) {
            HuAudFXPlay(0x1C8);
            last = order[i];
            HuSprBankSet(spr->unk_0A, 2, order[i], 0);
            func_800550F4_main(spr->unk_0A, 2, 1);
            for (delay = (state == 2) ? 15 : 1; delay != 0; delay--) {
                if (count > 0) {
                    if (state != 2 || cpuPartner == -1 || cpuPartner == order[i]) {
                        if (--count == 0) {
                            break;
                        }
                    }
                } else if (D_800C9520_main[GwPlayer[player].pad] & A_BUTTON) {
                    break;
                }
                HuPrcVSleep();
            }
            if (delay != 0) {
                break;
            }
        }
    } while (i == max + 1);
    memcpy(sfx, D_80115EF4_duel05, sizeof(sfx));
    HuAudFXPlay(sfx[order[i]]);
    D_80115838_duel05 = 0;
    if (player == 0) {
        if (state == 2) {
            GwSystem.playerIndexVisitingBowser &= 0xFF00;
        } else {
            GwSystem.playerIndexVisitingBowser++;
        }
    } else if (state == 2) {
        GwSystem.playerIndexVisitingBowser = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        GwSystem.playerIndexVisitingBowser += 0x100;
    }
    HuPrcSleep(30);
    D_80115830_duel05 = order[i];
    func_800E1854_minigame(msgWindow);
    if (colorProcess != NULL) {
        omDelPrcObj(colorProcess);
    }
    func_800F4584_name_81(spr);
    HuWinKill(window);
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

s32 func_8010F96C_duel05(s32 index) {
    Vec camPos;
    Vec pos;
    Vec target;
    Object *copies[10]; // Only 4 are used; the size matches the original stack frame.
    Vec offsets[4];
    s32 unused[2]; // Unused, but needed to match the stack frame.
    SpaceData *startSpace;
    SpaceData *partnerSpace;
    GW_PLAYER *player;
    Process *process;
    Duel05PartnerRouletteWork *work;
    Object *model;
    Object *partner;
    SpaceData *returnSpace;
    SpaceData *destSpace;
    s32 i;
    s32 state;

    startSpace = MBDMasuGet(D_80115818_duel05[index].startSpace);
    partnerSpace = MBDMasuGet(D_80115818_duel05[index].partnerSpace);
    player = MBDGetPlayerStruct(index);
    if (index == 0) {
        state = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        state = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    if (state == 2) {
        func_800EB140_name_81(0x16, 0x1F07);
    }
    HuVecCopy3F(&pos, &player->player_obj->coords);
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuVecCopy3F(&target, &startSpace->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &target, &pos, 3.0f));
    func_800F3880_name_81(-1, 0, 2);
    func_800EB708_name_81(&player->player_obj->coords, &startSpace->coords, &player->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EC1E4_name_81(&player->player_obj->coords, &startSpace->coords,
                                         &player->player_obj->coords, 3.0f));
    HuPrcChildWatch();
    func_800EB708_name_81(&player->player_obj->coords, &partnerSpace->coords, &player->player_obj->rot);
    func_800F3880_name_81(-1, 7, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x1C9);
    if (index == 0) {
        func_8010DF78_duel05(&player->player_obj->coords);
    } else {
        func_8010E584_duel05(&player->player_obj->coords);
    }
    func_800EFABC_name_81(player->player_obj);
    func_800F3880_name_81(-1, -1, 2);
    D_80115830_duel05 = -1;
    process = omAddPrcObj(func_8010F0FC_duel05, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel05PartnerRouletteWork));
    process->user_data = work;
    work->player = index;
    returnSpace = MBDMasuGet(D_80115818_duel05[index].returnSpace);
    func_800EB708_name_81(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->rot);
    func_800F3880_name_81(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(),
                   func_800EC1E4_name_81(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->coords, 2.0f));
    HuPrcChildWatch();
    func_800F3880_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&camPos);
    func_800EBC60_name_81(&player->player_obj->rot, &camPos, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    while (D_80115830_duel05 == -1) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&target, &partnerSpace->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &target, &pos, 2.0f));
    HuPrcChildWatch();
    if (index == 0) {
        func_8010E018_duel05();
    } else {
        func_8010E624_duel05();
    }
    model = func_800D8010_name_81(0x35, NULL);
    func_800D8F0C_name_81(model);
    partner = func_800F8050_name_81(D_80115830_duel05);
    HuVecCopy3F(&partner->coords, &partnerSpace->coords);
    partner->coords.y += 26.0f;
    func_800D8F0C_name_81(partner);
    HuAudFXPlay(0x1CA);
    if (index == 0) {
        func_8010E2DC_duel05();
    } else {
        func_8010E8E8_duel05();
    }
    HuPrcSleep(20);
    memcpy(offsets, D_80115F24_duel05, sizeof(offsets));
    for (i = 0; i < 4; i++) {
        copies[i] = func_800D8B18_name_81(model);
        Hu3DModelLayerSet(copies[i]->omObj1->model[0], 0x800);
        func_8001C258_main(copies[i]->omObj1->model[0], 0x180, 0);
        func_8001C814_main(copies[i]->omObj1->model[0], 2, 0);
        HuVecCopy3F(&copies[i]->coords, &partnerSpace->coords);
        copies[i]->velocity.x = 26.0f;
        copies[i]->coords.x += offsets[i].x;
        copies[i]->coords.y += offsets[i].y;
        copies[i]->coords.z += offsets[i].z;
        if (i == 3) {
            func_800D8E88_name_81(partner);
        }
        HuPrcSleep(4);
    }
    HuPrcSleep(25);
    for (i = 0; i < 4; i++) {
        func_800D8F3C_name_81(copies[i]);
    }
    func_800D8F3C_name_81(model);
    func_800FC888_name_81(5);
    func_800FC8DC_name_81(partner);
    destSpace = MBDMasuGet(D_80115818_duel05[index].startSpace);
    func_800EB708_name_81(&partner->coords, &destSpace->coords, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    func_800EF7C8_name_81(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EBF2C_name_81(&partner->coords, &destSpace->coords, &partner->coords, 20));
    HuPrcChildWatch();
    func_800EF800_name_81(partner);
    if (index == 0) {
        func_8010E308_duel05();
    } else {
        func_8010E914_duel05();
    }
    func_800FC888_name_81(4);
    func_800FC8C4_name_81(&pos);
    HuVecCopy3F(&pos, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&pos, &player->player_obj->coords, &pos, 2.0f));
    HuPrcChildWatch();
    func_800FC888_name_81(1);
    D_80115834_duel05 = partner;
    return D_80115830_duel05;
}

void func_80110038_duel05(s32 index) {
    Vec pos;
    u8 playerBits[4];
    s16 comKeys[4];
    Vec offsets[3];
    Vec frontPos;
    Vec backPos;
    Vec frontRot;
    Vec backRot;
    GW_PLAYER *player;
    s16 partnerId;
    s16 choice;
    Object *partner;
    s32 i;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    memcpy(playerBits, D_80115F54_duel05, sizeof(playerBits));
    memcpy(comKeys, D_80115F58_duel05, sizeof(comKeys));
    func_800DB3E0_name_81(index);
    func_800F38DC_name_81(-1, -1, 2);
    func_800EB7BC_name_81(&pos);
    func_800EBC60_name_81(&player->player_obj->rot, &pos, &player->player_obj->rot, 8);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuPrcChildWatch();
    if ((player->stats.partners.frontID != PARTNER_NONE && player->stats.partners.frontPoweredUp == POWERUP_ACTIVE) ||
        (player->stats.partners.backID != PARTNER_NONE && player->stats.partners.backPoweredUp == POWERUP_ACTIVE)) {
        func_800EAFC4_name_81(0x1F00);
        Duel_PowerDownPartners(index);
    }
    func_800EDD50_name_81(&MBDMasuGet(D_80115818_duel05[index].returnSpace)->coords);
    func_800EE0D0_name_81(0);
    func_800EDF48_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F01);
    func_800F3880_name_81(-1, 6, 0);
    func_800E14D8_name_81(index, 10);
    func_800F7378_name_81(index, 10);
    HuPrcSleep(30);
    func_800F3880_name_81(-1, -1, 2);
    if (player->stats.partners.frontID == PARTNER_NONE && player->stats.partners.backID == PARTNER_NONE) {
        func_800EB140_name_81(0x16, 0x1F04);
        partnerId = func_8010F96C_duel05(index);
    retryA:
        func_800EB1D8_name_81(0x16, 0x1F05);
        if (!func_800F37B8_name_81(index)) {
            HuWinActivePlayerSet(D_8010555C_name_81, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (func_8010EB58_duel05() >= func_800EFE20_name_81(100.0f) ||
                func_8010ECF0_duel05(partnerId) >= func_800EFE20_name_81(100.0f)) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], func_800EED50_name_81());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        choice = HuWinChoiceGet(D_8010555C_name_81, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (choice == 2) {
            func_801059D0_duel05();
            goto retryA;
        }
        if (choice == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(index);
            mbItemBtnF = 1;
            goto retryA;
        }
    } else {
        func_800EB140_name_81(0x16, 0x1F02);
    retryB:
        func_800EB1D8_name_81(0x16, 0x1F03);
        if (!func_800F37B8_name_81(index)) {
            HuWinActivePlayerSet(D_8010555C_name_81, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (player->stats.partners.backID == PARTNER_NONE ||
                func_8010EC48_duel05() >= func_800EFE20_name_81(100.0f)) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], func_800EED50_name_81());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], func_800EED50_name_81());
            func_8005B63C_main(D_8010555C_name_81, 2, 2);
        }
        choice = HuWinChoiceGet(D_8010555C_name_81, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        func_800EB278_name_81();
        func_800EB29C_name_81();
        if (choice == 2) {
            func_801059D0_duel05();
            goto retryB;
        }
        if (choice == 3) {
            mbItemBtnF = 0;
            func_800FB524_name_81(index);
            mbItemBtnF = 1;
            goto retryB;
        }
        partner = MBDGetPlayerPartnerRef(index, choice);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            memcpy(offsets, D_80115F60_duel05, sizeof(offsets));
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), func_800DCE40_name_81(0x4E, &pos, &offsets[i], 3.0f));
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            func_800D8F0C_name_81(partner);
            HuPrcChildWatch();
            func_800F85A4_name_81(index, choice);
            func_800F8358_name_81(index);
            func_800F57B0_name_81(index);
            func_800F5E2C_name_81(index);
        }
        partnerId = func_8010F96C_duel05(index);
    }
    func_800ECF1C_name_81(index, &frontPos, &backPos);
    func_800ED118_name_81(index, &frontRot, &backRot);
    func_800D918C_name_81(D_80115834_duel05, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        func_800EF7C8_name_81(D_80115834_duel05, 2.0f, -0.2f);
    }
    if (choice == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        func_800EB708_name_81(&D_80115834_duel05->coords, &frontPos, &D_80115834_duel05->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80115834_duel05->coords, &frontPos,
                                                                &D_80115834_duel05->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80115834_duel05->rot, &frontRot,
                                                                &D_80115834_duel05->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        func_800EB708_name_81(&D_80115834_duel05->coords, &backPos, &D_80115834_duel05->rot);
        HuPrcChildLink(HuPrcCurrentGet(), func_800EC1E4_name_81(&D_80115834_duel05->coords, &backPos,
                                                                &D_80115834_duel05->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), func_800EBC60_name_81(&D_80115834_duel05->rot, &backRot,
                                                                &D_80115834_duel05->rot, 7));
    }
    HuPrcChildWatch();
    func_800D8F3C_name_81(D_80115834_duel05);
    func_800F8418_name_81(index, partnerId, choice);
    func_800F821C_name_81(index, choice);
    func_800F89D0_name_81(index, PARTNER_FRONT, -1, 2);
    func_800F89D0_name_81(index, PARTNER_BACK, -1, 2);
    func_800ED214_name_81(index);
    func_800F5BB4_name_81(index);
    func_800F5EB0_name_81(index);
    if (player->stats.partners.frontID == player->stats.partners.backID) {
        switch (player->stats.partners.frontID) {
        case PARTNER_WHOMP:
        case PARTNER_THWOMP:
            func_800EB49C_name_81(0x16, 0x1F09, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontCost--;
            player->stats.partners.backCost--;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(index, 1);
            func_800F7D94_name_81(index, 1);
            break;
        default:
            func_800EB49C_name_81(0x16, 0x1F08, D_80101A1C_name_81[player->stats.partners.frontID], 0, 0, 0, 0);
            func_800EB58C_name_81();
            func_800EB278_name_81();
            func_800EB29C_name_81();
            player->stats.partners.frontPower++;
            player->stats.partners.backPower++;
            HuAudFXPlay(0x205);
            func_800F7BB4_name_81(index, 0);
            func_800F7D94_name_81(index, 0);
            break;
        }
        if (index == 0) {
            GWBoardFlagSet(0x12);
        } else {
            GWBoardFlagSet(0x13);
        }
    }
    func_800FBDD4_name_81();
    func_800EB140_name_81(0x16, 0x1F06);
    func_800EDF78_name_81();
    func_800EE468_name_81(0);
    func_800EDDBC_name_81();
    func_800DADA0_name_81(index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWatch();
}

void func_80110B4C_duel05(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110038_duel05(0);
    }
}

void func_80110BA8_duel05(void) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 1 && !(player->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110038_duel05(1);
    }
}

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

void func_801123B8_duel05(void) {
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

void func_801124A8_duel05(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_801124E4_duel05(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(sys->current_player_index, -coins);
    func_800F7378_name_81(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_80112560_duel05(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 10);
    func_800F7378_name_81(sys->current_player_index, 10);
    HuPrcSleep(30);
}

void func_8011259C_duel05(void) {
    s8 nnlink;
    s8 nnidx;
    s8 link2 = -1;
    s8 idx2 = -1;

    if (MBDGetCurrentPlayerIndex() == 0) {
        func_800E9F4C_name_81(0x1E, &nnlink, &nnidx);
    } else {
        func_800E9F4C_name_81(0x1D, &nnlink, &nnidx);
    }
    func_80115370_duel05(&link2, &idx2);
    func_800E24AC_name_81(nnlink, nnidx, link2, idx2);
    func_800ED214_name_81(GwSystem.current_player_index);
    func_80110038_duel05(MBDGetCurrentPlayerIndex());
}

void func_8011261C_duel05(void) {
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

void func_80112998_duel05(void) {
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

void func_80112B84_duel05(void) {
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

void func_80112D70_duel05(void) {
    GW_PLAYER *player;
    s32 playerIndex;
    void *handle;
    Object *partner;
    f32 angle;

    player = MBDGetPlayerStruct(CUR_PLAYER);
    playerIndex = MBDGetCurrentPlayerIndex();
    func_800DD41C_name_81(&player->player_obj->coords);
    func_800EDD50_name_81(&player->player_obj->coords);
    func_800EE0F4_name_81(1);
    func_800EDF48_name_81();
    HuAudFXPlay(0x1F6);
    func_800EE74C_name_81(1);
    HuAudFXPlay(0x1FD);
    func_800DD554_name_81();
    handle = func_800FFC2C_name_81(-1, 1, 5);
    for (angle = 0.0f; angle < 120.0f; angle += 5.0f) {
        if (player->stats.partners.frontID != PARTNER_NONE) {
            partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        if (player->stats.partners.backID != PARTNER_NONE) {
            partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        HuPrcVSleep();
    }
    Duel_SwapPartnerPositions(playerIndex);
    func_800DD564_name_81();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.partners.frontID != PARTNER_NONE) {
            partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        if (player->stats.partners.backID != PARTNER_NONE) {
            partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        HuPrcVSleep();
    }
    func_800FFCCC_name_81(handle);
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT);
        partner->velocity.x = 0.0f;
        MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK);
        partner->velocity.x = 0.0f;
        MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
    }
    func_800DD570_name_81();
    HuAudFXPlay(0x159);
    func_800EB140_name_81(0x16, 0x1F2C);
    func_800EDF78_name_81();
    func_800EE468_name_81(1);
    func_800EDDBC_name_81();
}

void func_801135A8_duel05(void) {
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

void func_801138A0_duel05(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

void func_801138DC_duel05(void) {
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
    D_80115880_duel05[GwSystem.minigame_index]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

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

void func_8011514C_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if ((player->rev & 1) && mbWalkNum != 0) {
        func_800E9F4C_name_81(0x1F, &player->nnlink, &player->nnidx);
    }
}

void func_80115198_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(4, &player->nnlink, &player->nnidx);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801151E4_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_80115230_duel05);

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_8011525C_duel05);

void func_801152A8_duel05(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1) || mbWalkNum == 0) {
        func_800E9F4C_name_81(4, &player->nnlink, &player->nnidx);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel05/426450", func_801152F4_duel05);

void func_80115370_duel05(s8 *arg0, s8 *arg1) {
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
