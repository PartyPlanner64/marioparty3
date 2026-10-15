#include "common.h"
#include "malloc.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5B90.h"

extern s32 D_80100D90_shared_board;
extern s32 D_801075C0_opboardtutorial;
extern Vec D_801075C4_opboardtutorial;
extern Vec D_801075D0_opboardtutorial;
extern Vec D_801075F4_opboardtutorial;
extern Vec D_80107600_opboardtutorial[];
extern Vec D_80107630_opboardtutorial[];
extern u32 D_80107660_opboardtutorial[];
extern u32 *D_80107720_opboardtutorial[];
extern u8 D_80107760_opboardtutorial;
extern Object *D_80107764_opboardtutorial;
extern s16 D_80107768_opboardtutorial;
extern s16 D_80107770_opboardtutorial[];
extern s16 D_80107784_opboardtutorial;
extern s16 D_80107786_opboardtutorial;
extern GW_PLAYER *D_80107788_opboardtutorial[4];
extern Object *D_80107798_opboardtutorial;

void func_800DCCE0_shared_board(void);
void func_800DCD64_shared_board(s32 player, s32 value);
void func_800EE614_shared_board(s32 window);
void func_80013390_main(s16 model, s32 arg1, s32 arg2, void (*callback)(s16));
void func_800138EC_main(s16 model, s32 arg1, s32 arg2);
void func_80105DE0_opboardtutorial(s16 model);
s32 func_800329B4_main(void *data);
void func_80033910_main(HmfData *hmf);
void func_80033970_main(HmfData *hmf);
void func_80107408_opboardtutorial(void);
void func_801074A4_opboardtutorial(omObjData *obj);
void func_801074E8_opboardtutorial(void);
void func_80107550_opboardtutorial(void);
void func_80107448_opboardtutorial(omObjData *obj);
void func_8010751C_opboardtutorial(void);
void func_80107594_opboardtutorial(void);

void func_801059A0_opboardtutorial(void) {
    s32 i;
    u32 j;

    D_80107760_opboardtutorial = GwSystem.current_board_index;
    omInitObjMan(50, 50);
    func_80107550_opboardtutorial();
    func_801074E8_opboardtutorial();
    func_800D95C4_shared_board(1000.0f);
    func_8005A6B0_main();
    omAddPrcObj(func_80107408_opboardtutorial, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801074A4_opboardtutorial);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80107660_opboardtutorial[0]; j++) {
            D_80107720_opboardtutorial[i][j + 1] = func_80017BB8_main(i, D_80107660_opboardtutorial[j + 1]);
        }
    }
    GwPlayer[0].chr = 3;
    GwPlayer[1].chr = 2;
    GwPlayer[2].chr = 0;
    GwPlayer[3].chr = 4;
    func_8004A208_main();
}

s16 func_80105AFC_opboardtutorial(s32 file, s32 flags) {
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 initialRadius;
    f32 speed;
    f32 rotationSpeed;
    s16 i;

    model = func_8000B108_main(file, flags);
    Hu3DModelPosSet(model, 0, 0, 0);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    func_8001C448_main(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, 0, func_80105DE0_opboardtutorial);
    hmf = HmfModelData[model].hmf;
    effect = HmfModelData[model].unkBC;
    particle = effect->unk58;
    effect->unk08.f = 30.0f;
    effect->unk0C.f = 720.0f;
    effect->unk10.f = 80.0f;
    effect->unk14 = 5.0f;
    initialRadius = effect->unk10.f / 10.0f;
    speed = (effect->unk10.f - initialRadius) / effect->unk08.f;
    rotationSpeed = effect->unk0C.f / effect->unk08.f;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = initialRadius;
        particle->unk1C = speed;
        particle->unk24 = rotationSpeed;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return model;
}

s32 func_80105C7C_opboardtutorial(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    f32 angle;

    effect->unk1C.f = x;
    effect->unk20.f = y;
    effect->unk24.f = z;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = MBRand(360.0f);
            particle->unk20 = effect->unk10.f / 10.0f;
            angle = MBRand(150.0f);
            angle -= 75.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0;
            particle->unk04 = 0;
            return 1;
        }
    }
    return 0;
}

void func_80105DE0_opboardtutorial(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk18 += particle->unk24;
            if (particle->unk18 < 0.0f) {
                particle->unk18 += 360.0f;
            } else if (particle->unk18 >= 360.0f) {
                particle->unk18 -= 360.0f;
            }
            radius = particle->unk20;
            radius += particle->unk1C;
            particle->unk20 = radius;
            radius *= particle->unk2C;
            particle->unk0C = radius * sindf(particle->unk18) + effect->unk1C.f;
            radius *= cosdf(particle->unk18);
            radius += effect->unk24.f;
            particle->unk14 = radius;
            particle->unk10 = particle->unk20 * particle->unk28 + effect->unk20.f;
            particle->unk04 += effect->unk14;
            if (particle->unk04 > 180.0f) {
                particle->unk04 = 180.0f;
            }
            particle->unk08 = sindf(particle->unk04) * effect->unk14;
        }
    }
    effect->unk02++;
}

s16 func_80105FA8_opboardtutorial(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    s16 animIdx;

    data = DataRead(file);
    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80107784_opboardtutorial = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_80107786_opboardtutorial = func_80032694_main(HmfModelData[model].hmf, (u16)anim, 0, name);
    func_8001C448_main(model);
    return animIdx;
}

void func_801060B4_opboardtutorial(s16 model, s16 anim) {
    HmfAnim *entry;

    if (D_80107786_opboardtutorial != 0xFF) {
        if (anim == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[D_80107786_opboardtutorial];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

s16 func_80106184_opboardtutorial(s32 file) {
    void *data = DataRead(file);
    s32 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_801061CC_opboardtutorial(s32 player1, s32 player2) {
    GW_PLAYER *first = MBPlayerGet(player1);
    GW_PLAYER *second = MBPlayerGet(player2);
    GW_PLAYER *temp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));

    bcopy(first, temp, sizeof(GW_PLAYER));
    bcopy(second, first, sizeof(GW_PLAYER));
    bcopy(temp, second, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(temp);
}

void func_80106254_opboardtutorial(void) {
    s32 i;
    s32 j;

    for (i = 3; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (GwPlayer[j].turn > GwPlayer[j + 1].turn) {
                func_801061CC_opboardtutorial(j, j + 1);
            }
        }
    }
}

void func_801062E8_opboardtutorial(omObjData *obj) {
    s32 i;

    D_80107798_opboardtutorial->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 4; i++) {
        D_80107788_opboardtutorial[i]->player_obj->coords.y = D_80107798_opboardtutorial->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void func_801063A4_opboardtutorial(void) {
    s32 i;
    Object *shadow;
    omObjData *bob;
    s16 effect;
    f32 scale;
    f32 shadowScale;

    for (i = 0; i < 4; i++) {
        D_80107788_opboardtutorial[i] = MBPlayerGet(i);
        MBPlayerModelCreate(i, D_80107720_opboardtutorial[GwPlayer[i].chr], 2);
        HuVecCopy3F(&D_80107788_opboardtutorial[i]->player_obj->coords, &D_80107600_opboardtutorial[i]);
        MBModelTempAllocFree(D_80107788_opboardtutorial[i]->player_obj);
        D_80107788_opboardtutorial[i]->stat |= PLAYER_UNK_04;
    }
    D_80107798_opboardtutorial = MBModelFileCreate(0x1301FE, -1, 1.0f, 0, NULL);
    shadow = MBModelFileCreate(0x1301FD, -1, 1.0f, 0, NULL);
    HuVecCopy3F(&D_80107798_opboardtutorial->coords, &D_801075D0_opboardtutorial);
    HuVecCopy3F(&shadow->coords, &D_801075D0_opboardtutorial);
    shadow->coords.y = 0;
    HuVecCopyXYZ(&shadow->scale, shadow->coords.y, shadow->coords.y, shadow->coords.y);
    effect = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(effect, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 40.0f);
    func_800138EC_main(effect, 1, 0);
    MBBackTPLvlSet(128);
    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    for (i = 128; i < 256; i += 8) {
        MBBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBBackTPLvlSet(255);
    HuAudFXPlay(0x2ED);
    while (D_80107798_opboardtutorial->coords.y >= 10.0f) {
        D_80107798_opboardtutorial->coords.y -= 3.0f;
        for (i = 0; i < 4; i++) {
            D_80107788_opboardtutorial[i]->player_obj->coords.y -= 3.0f;
        }
        shadowScale = 1.0f - D_80107798_opboardtutorial->coords.y / 250.0f;
        HuVecCopyXYZ(&shadow->scale, shadowScale, shadowScale, shadowScale);
        HuPrcVSleep();
    }
    bob = omAddObj(0x1000, 0, 0, -1, func_801062E8_opboardtutorial);
    bob->rot.x = 180.0f;
    bob->rot.y = 5.0f;
    bob->rot.z = D_80107798_opboardtutorial->coords.y;
    HuPrcSleep(30);
    func_8000CFA4_main(effect, D_80107798_opboardtutorial->coords.x,
                       D_80107798_opboardtutorial->coords.y + 40.0f, D_80107798_opboardtutorial->coords.z);
    func_800138EC_main(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 4; i++) {
            HuVecCopyXYZ(&D_80107788_opboardtutorial[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(D_80107788_opboardtutorial[i]->player_obj);
    }
    func_800138EC_main(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&D_80107798_opboardtutorial->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_8000D044_main(effect);
    MBModelKill(D_80107798_opboardtutorial);
    MBModelKill(shadow);
    omDelObj(bob);
}

void func_801068E4_opboardtutorial(Object *obj) {
    HuPrcSleep(5);
    obj->velocity.y = 20.0f;
    obj->velocity.z = -2.5f;
    HuPrcSleep(10);
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    func_800610E0_main(D_80107768_opboardtutorial);
    D_80107768_opboardtutorial = func_80060880_main(75, 159, 16);
    func_8005C060_main(D_80107768_opboardtutorial, 4, 0, 224, 224);
    func_8005BDFC_main(D_80107768_opboardtutorial, 0);
}

void func_80106990_opboardtutorial(void) {
    s32 state[4];
    s32 frames[4];
    s32 order[4];
    u8 motion[4] = { 3, 6, 5, 0 };
    s32 i;
    s32 j;
    s32 temp;
    Unk3 *help;

    func_800DB5DC_shared_board();
    func_800DB56C_shared_board();
    for (i = 0; i < 4; i++) {
        if (i != 0) {
            D_80100D90_shared_board = 0;
        }
        func_800DC128_shared_board(i);
        func_800DB6A8_shared_board(i);
    }
    func_800DCCE0_shared_board();
    HuPrcSleep(20);
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1601, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    help = func_800E210C_shared_board(2, 190, 1);
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                j = (rand8() & 3) + 2;
                break;
            case 1:
                j = (rand8() & 3) + 6;
                break;
            case 2:
                j = 10;
                break;
            case 3:
                j = 1;
                break;
            default:
                j = 5;
                break;
        }
        func_800DCD64_shared_board(i, j);
    }
    for (i = 0; i < 4; i++) {
        state[i] = 1;
        frames[i] = 0;
    }
    HuPrcSleep(20);
    while (1) {
        for (i = 0; i < 4; i++) {
            if (state[i] == 1) {
                state[i] = 2;
                MBMotionSet(D_80107788_opboardtutorial[i]->player_obj, 2, 0);
                func_800EE884_shared_board(D_80107788_opboardtutorial[i]->player_obj, -1, 2);
            } else if (state[i] == 2) {
                if (++frames[i] == 5) {
                    func_800DCBCC_shared_board(i);
                    state[i] = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (state[i] != 0) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        HuPrcVSleep();
    }
    MBHelpWinKill(help);
    HuPrcSleep(20);
    for (i = 0; i < 4; i++) {
        state[i] = func_800DCD9C_shared_board(i);
        order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if (state[i] < state[j]) {
                temp = state[i];
                state[i] = state[j];
                state[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[order[i]].turn = i;
        func_800DBE6C_shared_board(i);
    }
    func_80106254_opboardtutorial();
    func_800F453C_shared_board();
    D_801075C0_opboardtutorial = 1;
    for (i = 0; i < 4; i++) {
        MBStatusDispSideSet(i, 1);
    }
    HuPrcSleep(5);
    func_8005C060_main(D_80107768_opboardtutorial, 4, 0, 255, 255);
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1602, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    for (i = 0; i < 4; i++) {
        s32 messages[4] = { 0x1603, 0x1604, 0x1605, 0x1606 };

        func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], D_80107770_opboardtutorial[motion[i]]);
        func_8005B43C_main(D_80107768_opboardtutorial, messages[i], -1, -1);
        if (i != 0) {
            func_80060C14_main(D_80107768_opboardtutorial, 1);
        }
        func_800EE614_shared_board(D_80107768_opboardtutorial);
        func_80060EA8_main(D_80107768_opboardtutorial, 1);
        func_8004ACE0_main(0x274, i);
        func_800EE94C_shared_board(D_80107788_opboardtutorial[i]->player_obj, 3, 0);
        func_800EE884_shared_board(D_80107788_opboardtutorial[i]->player_obj, -1, 2);
        func_800DBEC0_shared_board(order[i]);
        if (i == 2) {
            func_801068E4_opboardtutorial(D_80107764_opboardtutorial);
        }
        MBStatusDispMoveSet(i + 10);
        while (func_800F5278_shared_board() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(20);
    }
    func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], D_80107770_opboardtutorial[0]);
}

void func_80106F40_opboardtutorial(void) {
    s16 effects[4];
    s32 i;
    s32 j;
    f32 scale;

    MBBackKill();
    MBBackLoad(22);
    func_800E9344_shared_board(1000.0f, 10000.0f);
    D_80107764_opboardtutorial = MBModelCreate(59, NULL);
    HuVecCopy3F(&D_80107764_opboardtutorial->coords, &D_801075C4_opboardtutorial);
    HuVecCopyXYZ(&D_80107764_opboardtutorial->scale, 0.9f, 0.9f, 0.9f);
    D_80107764_opboardtutorial->rot.x = sindf(10.0f);
    D_80107764_opboardtutorial->rot.z = cosdf(10.0f);
    D_80107764_opboardtutorial->flags |= 1;
    D_80107768_opboardtutorial = func_80060880_main(75, 197, 16);
    func_8005BDFC_main(D_80107768_opboardtutorial, 0);
    D_80107770_opboardtutorial[0] = func_80105FA8_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80107770_opboardtutorial[1] = func_80106184_opboardtutorial(0xA007F);
    D_80107770_opboardtutorial[2] = func_80106184_opboardtutorial(0xA0080);
    D_80107770_opboardtutorial[3] = func_80106184_opboardtutorial(0xA0081);
    D_80107770_opboardtutorial[4] = func_80106184_opboardtutorial(0xA0082);
    D_80107770_opboardtutorial[5] = func_80106184_opboardtutorial(0xA0083);
    D_80107770_opboardtutorial[6] = func_80106184_opboardtutorial(0xA0084);
    func_801060B4_opboardtutorial(D_80107764_opboardtutorial->omObj1->model[0], D_80107770_opboardtutorial[0]);
    D_80107798_opboardtutorial = MBModelCreate(58, NULL);
    func_800461B4_main(D_80107798_opboardtutorial->omObj1->model[0]);
    HuVecCopy3F(&D_80107798_opboardtutorial->coords, &D_801075F4_opboardtutorial);
    D_80107798_opboardtutorial->velocity.x = 1000.0f;
    for (j = 0; j < 4; j++) {
        HuVecCopy3F(&D_80107788_opboardtutorial[j]->player_obj->coords, &D_80107630_opboardtutorial[j]);
        effects[j] = func_80105AFC_opboardtutorial(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 4; j++) {
            func_80105C7C_opboardtutorial(effects[j], D_80107788_opboardtutorial[j]->player_obj->coords.x,
                                          D_80107788_opboardtutorial[j]->player_obj->coords.y + 50.0f, D_80107788_opboardtutorial[j]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (j = 0; j < 4; j++) {
            MBModelDispOn(D_80107788_opboardtutorial[j]->player_obj);
            HuVecCopyXYZ(&D_80107788_opboardtutorial[j]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 4; j++) {
        HuVecCopyXYZ(&D_80107788_opboardtutorial[j]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(11);
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1600, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    func_80106990_opboardtutorial();
    func_8005B43C_main(D_80107768_opboardtutorial, 0x1607, -1, -1);
    func_80060C14_main(D_80107768_opboardtutorial, 1);
    func_800EE614_shared_board(D_80107768_opboardtutorial);
    func_80060EA8_main(D_80107768_opboardtutorial, 1);
    func_800610E0_main(D_80107768_opboardtutorial);
}

void func_80107408_opboardtutorial(void) {
    func_801063A4_opboardtutorial();
    func_80106F40_opboardtutorial();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_80107448_opboardtutorial(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80107594_opboardtutorial();
        func_8010751C_opboardtutorial();
        func_8005F524_main();
        if (D_801075C0_opboardtutorial != 0) {
            func_800F4730_shared_board();
        }
        omOvlReturnEx(1);
    }
}

void func_801074A4_opboardtutorial(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        obj->func = func_80107448_opboardtutorial;
    }
}

void func_801074E8_opboardtutorial(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
    func_800F2A20_shared_board();
}

void func_8010751C_opboardtutorial(void) {
    func_800F2A34_shared_board();
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_80107550_opboardtutorial(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(0x15);
}

void func_80107594_opboardtutorial() {
    MBBackKill();
    MBBackClose();
}
