#include "common.h"
#include "mgresultdealer.h"

s8 mgresultdealer_dropF = 0;
u8 mgresultdealer_dropUnusedF = 0;
s8 mgresultdealer_dropHitF = 0;
Vec mgresultdealer_dropPos = { 0.0f, 0.0f, 0.0f };
Vec mgresultdealer_dropRot = { 0.0f, 0.0f, 0.0f };
s32 mgresultdealer_confettiFileTbl[4] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E };
s16 mgresultdealer_confettiTimer = 0;

extern s16 mgresultdealer_playerFaceAnimTbl[4];
extern s8 mgresultdealer_playerOrderTbl[4];
extern f32 mgresultdealer_dropVel;
extern s16 mgresultdealer_confettiMdlTbl[4];
extern s32 omCharModelNoTbl[][6];
extern const s16 mgresultdealer_chrLoseMotTbl[][2];

void mgresultdealer_PlayerDropFall(omObjData *);
void mgresultdealer_PlayerDestroy(void);
void mgresultdealer_PlayerDropBounce(omObjData *);
void mgresultdealer_PlayerDropLand(omObjData *);
void mgresultdealer_PlayerConfetti(omObjData *);
void mgresultdealer_ConfettiCreate(void);
void mgresultdealer_ConfettiObjMain(omObjData *);
void mgresultdealer_ConfettiEmit(s16);
void mgresultdealer_ConfettiHook(s16);

void mgresultdealer_PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 8, 5, -1, NULL);
    mgresultdealer_playerWork.obj = obj;
    chr = GwPlayer[mgresultdealer_playerOrderTbl[0]].chr;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);

    obj->model[1] = Hu3DModelRead(0x83, 0x2B9);
    Hu3DMotionAttrSet(obj->model[1], 2, 0);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[1], 0.0f, 140.0f, 0.0f);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);

    obj->model[2] = Hu3DModelRead(0x190003, 0x2B9);
    Hu3DMotionAttrSet(obj->model[2], 2, 0);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[2], 0.0f, 400.0f, -35.0f);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);

    obj->model[3] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 0.0f, -5.0f, -35.0f);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM0);

    obj->model[4] = Hu3DModelRead(0x190006, 0x2B9);
    obj->model[5] = Hu3DModelRead(0x190007, 0x2B9);
    obj->model[6] = Hu3DModelRead(0x190008, 0x2B9);
    Hu3DModelCameraSet(obj->model[4], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[5], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[6], HU3D_CAM1);
    Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

    mgresultdealer_playerFaceAnimTbl[0] = CharAnimCreate(obj->model[0], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    mgresultdealer_playerFaceAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    mgresultdealer_playerFaceAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    mgresultdealer_playerFaceAnimTbl[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA6));
    Hu3DModelDynamicFree(obj->model[0]);
    CharAnimSet(obj->model[0], 2, GwPlayer[mgresultdealer_playerOrderTbl[0]].chr, mgresultdealer_playerFaceAnimTbl[0]);

    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, mgresultdealer_chrLoseMotTbl[chr][1]));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x25));
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -35.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, mgresultdealer_PlayerDestroy);
    mgresultdealer_playerWork.func = mgresultdealer_PlayerDropFall;

    while (TRUE) {
        mgresultdealer_playerWork.func(obj);
        HuPrcVSleep();
    }
}

void mgresultdealer_PlayerDropFall(omObjData *obj) {
    if (mgresultdealer_dropF) {
        mgresultdealer_dropPos.y -= mgresultdealer_dropVel;
        mgresultdealer_dropVel += 0.98f;
        mgresultdealer_dropRot.x += 30.0f;
        if (mgresultdealer_dropPos.y <= 180.0f) {
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            mgresultdealer_dropPos.y = 180.0f;
            mgresultdealer_dropVel = -10.0f;
            mgresultdealer_dropHitF = 1;
            HuAudFXPlay(0x515);
            HuAudFXPlay(0x518);
            mgresultdealer_playerWork.func = mgresultdealer_PlayerDropBounce;
        }
        Hu3DModelPosSet(obj->model[2], mgresultdealer_dropPos.x, mgresultdealer_dropPos.y,
                        mgresultdealer_dropPos.z);
        Hu3DModelRotSet(obj->model[2], mgresultdealer_dropRot.x, mgresultdealer_dropRot.y,
                        mgresultdealer_dropRot.z);
    }
}

void mgresultdealer_PlayerDropBounce(omObjData *obj) {
    mgresultdealer_dropPos.y -= mgresultdealer_dropVel;
    mgresultdealer_dropVel += 0.98f;
    mgresultdealer_dropPos.x += 5.0f;
    mgresultdealer_dropPos.z -= 5.0f;
    mgresultdealer_dropRot.x -= 5.0f;
    mgresultdealer_dropRot.y -= 5.0f;
    if (mgresultdealer_dropPos.y <= 20.0f) {
        mgresultdealer_dropPos.y = 20.0f;
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mgresultdealer_dropVel = -2.0f;
        mgresultdealer_playerWork.func = mgresultdealer_PlayerDropLand;
    }
    Hu3DModelPosSet(obj->model[2], mgresultdealer_dropPos.x, mgresultdealer_dropPos.y,
                    mgresultdealer_dropPos.z);
    Hu3DModelRotSet(obj->model[2], mgresultdealer_dropRot.x, mgresultdealer_dropRot.y,
                    mgresultdealer_dropRot.z);
}

void mgresultdealer_PlayerDropLand(omObjData *obj) {
    mgresultdealer_dropPos.y -= mgresultdealer_dropVel;
    mgresultdealer_dropVel += 0.98f;
    if (mgresultdealer_dropPos.y <= 0.0f) {
        mgresultdealer_dropPos.y = 0.0f;
        mgresultdealer_dropF = 0;
        mgresultdealer_playerWork.func = mgresultdealer_PlayerDropFall;
    }
    Hu3DModelPosSet(obj->model[2], mgresultdealer_dropPos.x, mgresultdealer_dropPos.y,
                    mgresultdealer_dropPos.z);
    Hu3DModelRotSet(obj->model[2], mgresultdealer_dropRot.x, mgresultdealer_dropRot.y,
                    mgresultdealer_dropRot.z);
}

void mgresultdealer_PlayerDestroy(void) {
}

void mgresultdealer_DropStart(void) {
    omObjData *obj = mgresultdealer_playerWork.obj;

    mgresultdealer_dropF = 1;
    mgresultdealer_dropUnusedF = 0;
    mgresultdealer_dropHitF = 0;
    mgresultdealer_dropPos.x = 0.0f;
    mgresultdealer_dropPos.y = 400.0f;
    mgresultdealer_dropPos.z = -55.0f;
    mgresultdealer_dropRot.x = 160.0f;
    mgresultdealer_dropRot.y = 20.0f;
    mgresultdealer_dropRot.z = 0.0f;
    mgresultdealer_dropVel = 0;
    Hu3DModelPosSet(obj->model[2], mgresultdealer_dropPos.x, 400.0f, -55.0f);
    Hu3DModelRotSet(obj->model[2], mgresultdealer_dropRot.x, mgresultdealer_dropRot.y, mgresultdealer_dropRot.z);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

s8 mgresultdealer_DropHitCheck(void) {
    return mgresultdealer_dropHitF;
}

void mgresultdealer_ConfettiStart(void) {
    mgresultdealer_playerWork.func = mgresultdealer_PlayerConfetti;
}

void mgresultdealer_PlayerConfetti(omObjData *obj) {
    mgresultdealer_ConfettiCreate();
    mgresultdealer_playerWork.func = mgresultdealer_PlayerDropFall;
}

const s16 mgresultdealer_chrLoseMotTbl[][2] = { { 0, 0x36 }, { 0, 0x37 }, { 0, 0x3A }, { 0, 0x37 }, { 0, 0x36 }, { 0, 0x37 }, { 0, 0x36 }, { 0, 0x37 } };

void mgresultdealer_ConfettiCreate(void) {
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(mgresultdealer_confettiFileTbl[i], 0x2A9);
        mgresultdealer_confettiMdlTbl[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, 0, mgresultdealer_ConfettiHook);
        Hu3DModelCameraSet(model, HU3D_CAM1);
    }
    omAddObj(10, 10, 10, -1, mgresultdealer_ConfettiObjMain);
}

void mgresultdealer_ConfettiObjMain(omObjData *obj) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (((mgresultdealer_confettiTimer + i) & 7) == 0) {
            mgresultdealer_ConfettiEmit(mgresultdealer_confettiMdlTbl[i]);
        }
    }
    mgresultdealer_confettiTimer++;
}

void mgresultdealer_ConfettiEmit(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (100.0f - rand8() % 200) * 2.0f;
            particle->unk10 = 500.0f;
            particle->unk14 = ((rand8() * 125) >> 5) - 500;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk08 = 3.0f;
            break;
        }
    }
}

void mgresultdealer_ConfettiHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        bc->unk02++;
    }
    particle = bc->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 8.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void mgresultdealer_PlayerWinFaceSet(void) {
    CharAnimSet(mgresultdealer_playerWork.obj->model[0], 2, GwPlayer[mgresultdealer_playerOrderTbl[0]].chr,
                       mgresultdealer_playerFaceAnimTbl[2]);
}

void mgresultdealer_PlayerLoseFaceSet(void) {
    CharAnimSet(mgresultdealer_playerWork.obj->model[0], 2, GwPlayer[mgresultdealer_playerOrderTbl[0]].chr,
                       mgresultdealer_playerFaceAnimTbl[3]);
}
