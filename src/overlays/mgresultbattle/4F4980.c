#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} ResultBattleEffect; /* size = 0x20 */

void func_80106E98_mgresultbattle(void);
void func_80106ED0_mgresultbattle(omObjData *);
void func_80107610_mgresultbattle(omObjData *);
void func_801075EC_mgresultbattle(void);
void func_801075F4_mgresultbattle(omObjData *);
void func_80107B5C_mgresultbattle(f32 arg0, f32 arg1, f32 arg2);
void func_80107BDC_mgresultbattle(f32 arg0);
void func_80107C44_mgresultbattle(void);
void func_80107CA4_mgresultbattle(void);
void func_801082AC_mgresultbattle(void);

extern ResultBattlePlayerObj D_80108F90_mgresultbattle;
extern s32 D_801088E0_mgresultbattle[];
extern ResultBattleEffect D_80108A30_mgresultbattle[40];
extern omObjData *D_80108F74_mgresultbattle;
extern omObjFunc D_80108F78_mgresultbattle;
extern Vec D_801089D0_mgresultbattle[4];
extern s8 D_80108F8C_mgresultbattle[4];
extern s32 D_80108F70_mgresultbattle;
extern const s32 D_801089C0_mgresultbattle[];

void func_80106BA0_mgresultbattle(void) {
    omObjData *obj;
    void *data;
    u16 sprite1;
    u16 sprite2;
    s32 i;

    obj = omAddObj(0x14, 0x58, 8, -1, NULL);
    D_80108F74_mgresultbattle = obj;

    data = DataRead(0x210026);
    sprite1 = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprite1].modelId, 0x70000000, 0x70000000);

    data = DataRead(0xC);
    sprite2 = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprite2].modelId, 0x70000000, 0x70000000);

    for (i = 0; i < 40; i++) {
        D_80108A30_mgresultbattle[i].state = 1;
        D_80108A30_mgresultbattle[i].unk02 = func_80014618_main(sprite1, 8);
        D_80108A30_mgresultbattle[i].unk04 = func_80014618_main(sprite2, 8);
        D_80108A30_mgresultbattle[i].unk08 = 0;
        D_80108A30_mgresultbattle[i].unk18 = 0.0f;
        D_80108A30_mgresultbattle[i].unk1C = 0.0f;
        obj->model[i + 1] = D_800CBB60_main[D_80108A30_mgresultbattle[i].unk02].modelId;
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].modelId, 3.0f, 3.0f, 3.0f);
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        obj->model[i + 41] = D_800CBB60_main[D_80108A30_mgresultbattle[i].unk04].modelId;
        Hu3DModelScaleSet(D_800CBB60_main[i + 41].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(NULL, func_80106E98_mgresultbattle);
    D_80108F78_mgresultbattle = func_80106ED0_mgresultbattle;

    while (TRUE) {
        D_80108F78_mgresultbattle(obj);
        HuPrcVSleep();
    }
}

void func_80106E98_mgresultbattle(void) {
}

void func_80106EA0_mgresultbattle(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_801088E0_mgresultbattle[i] = 0;
    }
}

void func_80106ED0_mgresultbattle(omObjData *obj) {
    f32 dist;
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        switch (D_80108A30_mgresultbattle[i].state) {
            case 1:
                break;
            case 4:
                if (--D_80108A30_mgresultbattle[i].unk08 > 0) {
                    break;
                }
                D_80108A30_mgresultbattle[i].state = 2;
                /* fallthrough */
            case 2:
                Hu3DModelScaleSet(obj->model[i + 1], 1.5f, 1.5f, 1.5f);
                func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(obj->model[i + 1], D_80108A30_mgresultbattle[i].x, D_80108A30_mgresultbattle[i].y,
                                D_80108A30_mgresultbattle[i].z);
                D_80108A30_mgresultbattle[i].y -= D_80108A30_mgresultbattle[i].unk18;
                D_80108A30_mgresultbattle[i].unk18 += 4.0f;
                if (D_80108A30_mgresultbattle[i].y <= D_80108A30_mgresultbattle[i].unk1C) {
                    HuAudFXPlay(0x106);
                    for (j = 0; j < 4; j++) {
                        if (GwPlayer[D_80108F8C_mgresultbattle[j]].stat & 1) {
                            continue;
                        }
                        if (D_801088E0_mgresultbattle[j] != 0) {
                            continue;
                        }
                        dist = D_801089D0_mgresultbattle[j].x - D_80108A30_mgresultbattle[i].x;
                        if ((dist > 0.0f ? dist : -(D_801089D0_mgresultbattle[j].x - D_80108A30_mgresultbattle[i].x)) <
                            100.0f) {
                            omVibrate(D_80108F8C_mgresultbattle[j], 5, 0, 5);
                            D_801088E0_mgresultbattle[j] = 1;
                            break;
                        }
                    }
                    D_80108A30_mgresultbattle[i].state = 1;
                    func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    func_80014714_main(D_80108A30_mgresultbattle[i].unk04, 0);
                    Hu3DModelPosSet(obj->model[i + 41], D_80108A30_mgresultbattle[i].x,
                                    D_80108A30_mgresultbattle[i].unk1C, D_80108A30_mgresultbattle[i].z);
                    func_8001C258_main(obj->model[i + 41], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                break;
        }
    }
}

void func_80107260_mgresultbattle(f32 x, f32 y, f32 z, s32 count, f32 arg4) {
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 40; i++) {
        if (D_80108A30_mgresultbattle[i].state == 1) {
            D_80108A30_mgresultbattle[i].state = 4;
            D_80108A30_mgresultbattle[i].unk08 = n++;
            D_80108A30_mgresultbattle[i].x = x + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].y = y;
            D_80108A30_mgresultbattle[i].z = z + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].unk18 = 0.0f;
            D_80108A30_mgresultbattle[i].unk1C = arg4;
        }
        if (n >= count) {
            break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089A0_mgresultbattle);

void func_80107400_mgresultbattle(void) {
    omObjData *itemObj;

    itemObj = omAddObj(20, 4, 8, -1, NULL);
    D_80108F90_mgresultbattle.obj = itemObj;
    itemObj->model[1] = func_8000B108_main(0xA00A5, 0x2B9);
    func_8001C814_main(itemObj->model[1], 2, 2);
    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    itemObj->model[2] = func_8000B108_main(0x1B0000, 0x2B9);
    func_8001C258_main(itemObj->model[2], 0x4000, 0x4000);
    func_8001C814_main(itemObj->model[2], 2, 2);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelHookSet(itemObj->model[2], itemObj->model[1], "item_hook");
    itemObj->model[3] = func_8000B108_main(0x130200, 0x2B9);
    func_8001C814_main(itemObj->model[3], 2, 2);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8000B460_main(itemObj, 0, 0xA00A6);
    func_8000B460_main(itemObj, 1, 0xA00B6);
    func_8001C5B4_main(itemObj->model[1], itemObj->motion[1]);
    func_8001C814_main(itemObj->model[1], 2, 2);
    func_80107CA4_mgresultbattle();
    itemObj->trans.x = 0.0f;
    itemObj->trans.y = 0.0f;
    itemObj->trans.z = 0.0f;
    Hu3DModelPosSet(itemObj->model[0], itemObj->trans.x, itemObj->trans.y, itemObj->trans.z);
    omPrcSetDestructor(NULL, func_801075EC_mgresultbattle);
    D_80108F90_mgresultbattle.func = func_801075F4_mgresultbattle;
    while (TRUE) {
        D_80108F90_mgresultbattle.func(itemObj);
        HuPrcVSleep();
    }
}

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(omObjData *object) {
}

void func_801075FC_mgresultbattle(void) {
    D_80108F90_mgresultbattle.func = func_80107610_mgresultbattle;
}

void func_80107610_mgresultbattle(omObjData *obj) {
    s32 weights[4];
    Vec2f pos;
    f32 t;
    f32 angle;
    f32 rot;
    s32 count;
    s32 player;
    s32 total;
    s32 r;
    s32 i;

    player = 3;
    func_80107C44_mgresultbattle();
    rot = 0.0f;
    HuAudFXPlay(0x25B);
    t = rot;
    func_80106EA0_mgresultbattle();
    for (i = 0; i < 60; i++) {
        angle = t * 2.6666667f + 10.0f;
        t += 1.0f;
        pos.x = cosdf(angle) * 750.0f;
        pos.y = -sindf(angle) * 400.0f;
        func_80107B5C_mgresultbattle(pos.x + 0.0f, pos.y + 950.0f, 0.0f);
        func_80107BDC_mgresultbattle(sindf(rot) * 25.0f);
        rot += 1.5f;
        if (player >= 0 && pos.x + 0.0f <= D_801089D0_mgresultbattle[player].x) {
            count = GwPlayer[D_80108F8C_mgresultbattle[player]].gameCoin;
            if (count > 0) {
                if (count > 10) {
                    count = 10;
                }
                func_80107260_mgresultbattle(
                    D_801089D0_mgresultbattle[player].x, pos.y + 950.0f + 0.0f, 0.0f, count,
                    HmfModelData[D_80108F50_mgresultbattle[player].obj->model[1]].pos.y + 160.0f);
            }
            player--;
        }
        HuPrcVSleep();
    }

    rot = 0.0f;
    if (D_80108F70_mgresultbattle > 0) {
        HuPrcSleep(30);
        func_80106EA0_mgresultbattle();
        total = 0;
        for (i = 0; i < 4; i++) {
            weights[i] = D_801089C0_mgresultbattle[GwPlayer[i].bonusCoin];
            total += weights[i];
        }
        r = rand16() % total + 1;
        total = 0;
        player = 4;
        for (i = 0; i < 4; i++) {
            total += weights[i];
            if (total >= r) {
                player = i;
                break;
            }
        }
        GwPlayer[D_80108F8C_mgresultbattle[player]].gameCoin += D_80108F70_mgresultbattle;

        t = 0.0f;
        for (i = 0; i < 40; i++) {
            angle = t * 4.0f + 10.0f;
            t += 1.0f;
            pos.x = -cosdf(angle) * 750.0f;
            pos.y = -sindf(angle) * 400.0f;
            func_80107B5C_mgresultbattle(pos.x + 0.0f, pos.y + 950.0f, 0.0f);
            func_80107BDC_mgresultbattle(-sindf(rot) * 25.0f);
            rot += 1.5f;
            if (player >= 0 && pos.x + 0.0f >= D_801089D0_mgresultbattle[player].x) {
                count = D_80108F70_mgresultbattle;
                if (count > 0) {
                    if (count > 10) {
                        count = 10;
                    }
                    func_80107260_mgresultbattle(
                        D_801089D0_mgresultbattle[player].x, pos.y + 950.0f + 0.0f, 0.0f, count,
                        HmfModelData[D_80108F50_mgresultbattle[player].obj->model[1]].pos.y + 160.0f);
                }
                player = -1;
            }
            HuPrcVSleep();
        }
    }
    func_80107CA4_mgresultbattle();
    func_801082AC_mgresultbattle();
    D_80108F90_mgresultbattle.func = func_801075F4_mgresultbattle;
}

void func_80107B5C_mgresultbattle(f32 arg0, f32 arg1, f32 arg2) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    Hu3DModelPosSet(itemObj->model[1], arg0, arg1, arg2);
    Hu3DModelPosSet(itemObj->model[3], arg0, arg1, arg2);
}

void func_80107BDC_mgresultbattle(f32 arg0) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    Hu3DModelRotSet(itemObj->model[1], 0.0f, 0.0f, arg0);
    Hu3DModelRotSet(itemObj->model[3], 0.0f, 0.0f, arg0);
}

void func_80107C44_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_80107CA4_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089C0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D4_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D8_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_80108A00_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_80108A10_mgresultbattle);
