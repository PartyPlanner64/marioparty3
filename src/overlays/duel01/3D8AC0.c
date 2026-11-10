#include "common.h"
#include "duel01.h"

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

void *memcpy(void *, const void *, unsigned int);
extern s16 D_80118F30_duel01[];
extern s16 D_80118F48_duel01[];

void func_801059D0_duel01(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    func_80100CEC_name_81(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80105A58_duel01(void) {
    while (func_800E88FC_name_81() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_80119470_duel01 = func_800E1824_name_81(0, 0xA0, 1);
    D_80119474_duel01 = func_800E1824_name_81(0xD, 0xAE, 1);
    D_80119478_duel01 = func_800E1824_name_81(1, 0xBC, 1);
    D_8011947C_duel01 = func_800E1824_name_81(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80105B10_duel01(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    func_800E1854_name_81(D_80119470_duel01);
    func_800E1854_name_81(D_80119474_duel01);
    func_800E1854_name_81(D_80119478_duel01);
    func_800E1854_name_81(D_8011947C_duel01);
}

void func_80105B64_duel01(void) {
    GwSystem.current_board_index = 0;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void func_80105B9C_duel01(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    func_800E94D0_name_81();
    func_800E9B10_name_81(0x13, 0x241);
    func_800E9F4C_name_81(0x1C, &sp10, &sp11);
    func_800ECD0C_name_81(0, sp10, sp11);
    func_800E9F4C_name_81(0x1B, &sp10, &sp11);
    func_800ECD0C_name_81(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    func_800E9D9C_name_81();
    func_800E9564_name_81();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    func_800EA760_name_81();
    omOvlReturnEx(1);
}

void func_80105C64_duel01(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    func_800EB708_name_81(arg0, arg1, arg2);
    angle = func_800D76D0_name_81(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

void func_80105CC0_duel01(void) {
    unkStruct02 *work = HuPrcCurrentGet()->user_data;
    f32 x = work->unk_00.x;
    f32 y = work->unk_00.y;
    f32 z = work->unk_00.z;
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

Process *func_80105EB0_duel01(Object *object) {
    Process *process;
    unkStruct02 *work;

    process = omAddPrcObj(&func_80105CC0_duel01, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(unkStruct02));
    process->user_data = work;
    work->unk_00.x = object->coords.x;
    work->unk_00.y = object->coords.y;
    work->unk_00.z = object->coords.z;
    return process;
}

void func_80105F20_duel01(void) {
    Process *process = HuPrcCurrentGet();
    Duel01PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
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
    func_80105EB0_duel01(obj);
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

Process *func_801060D0_duel01(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel01PartnerAttackWork *work;

    process = omAddPrcObj(func_80105F20_duel01, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel01PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void func_8010615C_duel01(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
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

void func_80106240_duel01(void) {
    func_800FC8C4_name_81(&D_80105540_name_81);
}

void func_80106260_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81, arg3);
    } else {
        func_800EC1E4_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81, arg3);
    }
}

void func_801062C0_duel01(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    if (arg2 & 9) {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg0->coords, &D_80105540_name_81);
    } else {
        func_800EBF2C_name_81(&D_80105540_name_81, &arg1->player_obj->coords, &D_80105540_name_81);
    }
}

void func_80106308_duel01(void) {
    Duel01CamShakeWork *work = HuPrcCurrentGet()->user_data;
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

Process *func_8010645C_duel01(s32 magnitude, s32 decay) {
    Process *process;
    Duel01CamShakeWork *work;

    process = omAddPrcObj(&func_80106308_duel01, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel01CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801064C8_duel01);

Object *func_80106740_duel01(s32 arg0) {
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

void func_801067D4_duel01(Object *arg0, Vec *arg1) {
    func_800D8E88_name_81(arg0);
    func_8001C814_main(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80106828_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107188_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E60_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801079B8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80107EBC_duel01);

void func_801084A4_duel01(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80108550_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109404_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80109888_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010A210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AAB0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010AD48_duel01);

void func_8010AFB4_duel01(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    func_800142A0_main(0x1A);
    D_8011948C_duel01 = omAddObj(0x1F4, 0, 0, -1, func_8010B130_duel01);
    data = D_8011948C_duel01->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
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
    D_8011948C_duel01->work[0] = 0;
    data->unk_1E0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B130_duel01);

s32 func_8010B480_duel01(void) {
    UnkDuelObjData *data = D_8011948C_duel01->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_180); i++) {
        if (data->unk_180[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8010B4C0_duel01(void) {
    UnkDuelObjData *data = D_8011948C_duel01->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->unk_1A0); i++) {
        func_80016638_main(data->unk_1A0[i]);
    }
    omDelObj(D_8011948C_duel01);
    func_800166D0_main();
}

void func_8010B528_duel01(void) {
    D_8011948C_duel01->work[0] = 1;
}

void func_8010B53C_duel01(void) {
    D_8011948C_duel01->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010B54C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010BCD4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010CE68_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D424_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118E98_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118EA4_duel01);

void func_8010D95C_duel01(void) {
    PartnerFunc attackFuncs[12] = {
        func_80106828_duel01, func_80107188_duel01, func_801079B8_duel01, func_80107EBC_duel01,
        func_80109888_duel01, func_801084A4_duel01, func_8010CE68_duel01, func_8010D424_duel01,
        func_8010BCD4_duel01, func_80108550_duel01, func_8010A210_duel01, func_8010B54C_duel01,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        func_80109888_duel01, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    func_800FAC94_name_81(attackFuncs, otherFuncs);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010D9F4_duel01);

void func_8010DA84_duel01(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x1F);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    func_8010D9F4_duel01();
    func_800EA46C_name_81(D_80118914_duel01);
    func_800EA46C_name_81(D_80118DEC_duel01);
    func_800FC5A8_name_81(func_8011390C_duel01);
    func_800FC59C_name_81(func_80118328_duel01);
    func_800FF640_name_81(0);
}

void func_8010DB00_duel01(void) {
    Hu3DCamInit(1);
    func_8010D9F4_duel01();
    func_800FF640_name_81(1);
}

void func_8010DB2C_duel01(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], Hu3DData[D_80119490_duel01->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = func_8001D33C_main(D_80119490_duel01->omObj1->model[0], "neji");
        angle += D_8011872C_duel01;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void func_8010DC04_duel01(void) {
    HmfMotionNode *node;

    func_8002FD8C_main(D_80119490_duel01->omObj1->model[0], Hu3DData[D_80119490_duel01->omObj1->model[0]].motId, D_80118F18_duel01, 0x4C, 0x46);
    node = func_8001D33C_main(D_80119490_duel01->omObj1->model[0], D_80118F18_duel01);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010DCA8_duel01);

void func_8010DD3C_duel01(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x32, NULL);
    func_800D8944_name_81(obj);
    D_80119498_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_80118740_duel01);
    space2 = MBDMasuGet(D_80118742_duel01);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010DDEC_duel01(void) {
    Duel01SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_80119498_duel01->omObj1->model[0]].mtx, sindf(angle) * D_8011949C_duel01);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010DF68_duel01(Vec *pos) {
    Process *process;
    Duel01SwayWork *work;

    D_8011949C_duel01 = 10.0f;
    process = omAddPrcObj(func_8010DDEC_duel01, 0xA, 0, 0x40);
    D_80118744_duel01 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel01SwayWork));
    process->user_data = work;
    if (pos->x <= D_80119498_duel01->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E008_duel01(void) {
    if (D_80118744_duel01 != NULL) {
        while (D_8011949C_duel01 >= 0.0f) {
            D_8011949C_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_80118744_duel01);
        MTX_ROTZ(Hu3DData[D_80119498_duel01->omObj1->model[0]].mtx, 0.0f);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F18_duel01);

void func_8010E1B4_duel01(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_80119498_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_80119498_duel01);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_80119498_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E2CC_duel01(void) {
    omAddPrcObj(func_8010E1B4_duel01, 0xA, 0, 0);
}

void func_8010E2F8_duel01(void) {
    func_8001C814_main(D_80119498_duel01->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_80119498_duel01->omObj1->model[0], 1.0f);
}

void func_8010E348_duel01(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = func_800D8010_name_81(0x33, NULL);
    func_800D8944_name_81(obj);
    D_801194A0_duel01 = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(D_80118748_duel01);
    space2 = MBDMasuGet(D_8011874A_duel01);
    HuVecCopy3F(&obj->coords, &space1->coords);
    func_800EB708_name_81(&space1->coords, &space2->coords, &obj->rot);
}

void func_8010E3F8_duel01(void) {
    Duel01SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[D_801194A0_duel01->omObj1->model[0]].mtx, sindf(angle) * D_801194A4_duel01);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void func_8010E574_duel01(Vec *pos) {
    Process *process;
    Duel01SwayWork *work;

    D_801194A4_duel01 = 10.0f;
    process = omAddPrcObj(func_8010E3F8_duel01, 0xA, 0, 0x40);
    D_8011874C_duel01 = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel01SwayWork));
    process->user_data = work;
    if (pos->x <= D_801194A0_duel01->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void func_8010E614_duel01(void) {
    if (D_8011874C_duel01 != NULL) {
        while (D_801194A4_duel01 >= 0.0f) {
            D_801194A4_duel01 -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(D_8011874C_duel01);
        MTX_ROTZ(Hu3DData[D_801194A0_duel01->omObj1->model[0]].mtx, 0.0f);
    }
}

void func_8010E7C0_duel01(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(D_801194A0_duel01->omObj1->model[0], 1.5f);
    func_800EFABC_name_81(D_801194A0_duel01);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_801194A0_duel01->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void func_8010E8D8_duel01(void) {
    omAddPrcObj(func_8010E7C0_duel01, 0xA, 0, 0);
}

void func_8010E904_duel01(void) {
    func_8001C814_main(D_801194A0_duel01->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(D_801194A0_duel01->omObj1->model[0], 1.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010E954_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EA74_duel01);

void func_8010EAD4_duel01(s32 arg0) {
    if (D_8011875C_duel01 == 0) {
        HuAudFXPlay(0x1C4);
    }
    D_8011875C_duel01 = 1;
    func_8001C814_main(D_801194AC_duel01[arg0]->omObj1->model[0], 5, 0);
    HuPrcSleep(0xA);
}

void func_8010EB44_duel01(s32 arg0) {
    func_8001C814_main(D_801194AC_duel01[arg0]->omObj1->model[0], 1, 4);
    D_8011875C_duel01 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EB88_duel01);

s16 func_8010EC78_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    s16 partnerValues[12];

    memcpy(partnerValues, D_80118F30_duel01, sizeof(partnerValues));
    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

s16 func_8010ED20_duel01(s32 index) {
    s16 shakeAngles[12];

    memcpy(shakeAngles, D_80118F48_duel01, sizeof(shakeAngles));
    return shakeAngles[index];
}

s32 func_8010EDA0_duel01(void) {
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
                    for (i = 0; D_80118760_duel01[i * 2] != -1; i++) {
                        if (D_80118760_duel01[i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                            break;
                        }
                    }
                    partner = D_80118760_duel01[i * 2];
                    break;
                }
            }
            for (i = 0; D_8011885C_duel01[player->chr][i * 2] != -1; i++) {
                if (D_8011885C_duel01[player->chr][i * 2 + 1] > func_800EFE20_name_81(100.0f)) {
                    break;
                }
            }
            partner = D_8011885C_duel01[player->chr][i * 2];
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

#ifdef NON_MATCHING
// Frame is 8 bytes smaller than the target, and the green abs() is negated
// out of place (bgez/move/negu) instead of in place (bltzl negu) then copied.
void func_8010EFBC_duel01(void) {
    Duel01WinColorWork *work = HuPrcCurrentGet()->user_data;
    s32 window;
    s32 red = 0x43;
    u8 green;
    u8 blue;
    s16 temp;
    s32 temp2;
    f32 blueAngle = 0.0f;
    f32 greenAngle = 90.0f;

    window = work->window;
    HuWinBGColSet(work->window, 0x43, 0x80, 1);
    while (TRUE) {
        if (D_8011889C_duel01 != 0) {
            temp = sindf(greenAngle) * 128.0f;
            if (temp < 0) {
                temp = -temp;
            }
            green = temp;
            greenAngle += 6.0f;
            if (greenAngle > 360.0f) {
                greenAngle -= 360.0f;
            }
            temp2 = (s16)(sindf(blueAngle) * 64.0f);
            blue = (temp2 < 0) ? -temp2 : temp2;
            blueAngle += 3.0f;
            if (blueAngle > 360.0f) {
                blueAngle -= 360.0f;
            }
            HuWinBGColSet(window, (u8)red, green, blue);
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010EFBC_duel01);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F12C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8010F99C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110068_duel01);

void func_80110B7C_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if (MBDGetCurrentPlayerIndex() == 0 && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(0);
    }
}

void func_80110BD8_duel01(void) {
    GW_PLAYER *temp_s0;

    temp_s0 = MBDGetPlayerStruct(CUR_PLAYER);
    if ((MBDGetCurrentPlayerIndex() == 1) && !(temp_s0->rev & 4)) {
        func_800F38DC_name_81(-1, -1, 2);
        func_80110068_duel01(1);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F30_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F48_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F60_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F6C_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118F84_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FB4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FE8_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80118FF0_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119010_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119014_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801190FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801191E4_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801192CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80110C3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80111DFC_duel01);

void func_801123E8_duel01(void) {
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

void func_801124D8_duel01(void) {
    func_800E18C0_name_81();
    func_800E1960_name_81();
    func_800E1F38_name_81();
    func_800ED214_name_81(0);
    func_800ED214_name_81(1);
}

void func_80112514_duel01(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    func_800E14D8_name_81(sys->current_player_index, -coins);
    func_800F7378_name_81(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void func_80112590_duel01(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 10);
    func_800F7378_name_81(sys->current_player_index, 10);
    HuPrcSleep(30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801125CC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011264C_duel01);

void func_801129C8_duel01(void) {
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

void func_80112BB4_duel01(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80112DA0_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801135D8_duel01);

void func_801138D0_duel01(void) {
    GW_SYSTEM *sys = &GwSystem;

    func_800E14D8_name_81(sys->current_player_index, 20);
    func_800F7378_name_81(sys->current_player_index, 20);
    HuPrcSleep(30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011390C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80113CAC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801147FC_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_801193E8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80115850_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801159F8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80116484_duel01);

INCLUDE_RODATA("asm/nonmatchings/overlays/duel01/3D8AC0", D_80119410_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117480_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117624_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801179AC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117D3C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117DDC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117E7C_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117ED8_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80117FFC_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118058_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118178_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_801181C4_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118210_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_8011825C_duel01);

void func_801182A8_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (!(player->rev & 1)) {
        func_800E9F4C_name_81(0x21, &player->nnlink, &player->nnidx);
    }
}

void func_801182E4_duel01(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);

    if (player->rev & 1) {
        func_800E9F4C_name_81(0x22, &player->nnlink, &player->nnidx);
    }
}

void func_80118320_duel01(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118328_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118414_duel01);

INCLUDE_ASM("asm/nonmatchings/overlays/duel01/3D8AC0", func_80118530_duel01);
