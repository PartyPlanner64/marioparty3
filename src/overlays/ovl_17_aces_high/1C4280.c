#include "common.h"

typedef struct AceHighCamData {
    /* 0x00 */ char unk_00[2];
    /* 0x02 */ u16 camIdx;
    /* 0x04 */ char unk_04[0x88];
    /* 0x8C */ f32 unk_8C;
} AceHighCamData;

typedef struct AceHighPlayer {
    /* 0x00 */ char unk_00[0x28];
    /* 0x28 */ u16 espriteSlots[2];
} AceHighPlayer;

extern omObjData *D_8010DE5C_aces_high;
extern omObjData *D_8010DE60_aces_high;
extern omObjData **D_8010DE68_aces_high;
extern omObjData *D_8010DE80_aces_high;
extern s16 D_8010DE8C_aces_high;
extern s16 D_8010DE8E_aces_high;
extern s16 D_8010DE90_aces_high;
extern Vec D_8010DEA8_aces_high;
extern Vec D_8010DEB4_aces_high;
extern Vec D_8010DEC0_aces_high;
extern s16 D_8010DF20_aces_high;

void func_80105E84_aces_high(omObjData *object);
void func_8010CA6C_aces_high(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801059A0_aces_high);

void func_80105E44_aces_high(omObjData *object) {
    D_8010DE60_aces_high = NULL;
    D_8010DE5C_aces_high = NULL;
    D_8010DE8C_aces_high = 4;
    D_8010DE8E_aces_high = -1;
    D_8010DE90_aces_high = 0;
    object->func = func_80105E84_aces_high;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80105E84_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80105FC8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801061E0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801062DC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801068F4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80106B70_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80106D2C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80106EC0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801071D4_aces_high);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DD48_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80107654_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80107F98_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801081A8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010843C_aces_high);

void func_801085B0_aces_high(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        AceHighPlayer *player = OM_GET_DATA_PTR(D_8010DE68_aces_high[i], AceHighPlayer);

        for (j = 0; j < 2; j++) {
            func_8000BB94_main(player->espriteSlots[j]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010862C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_801088A4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010951C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80109928_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_80109EEC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A0F0_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A214_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A51C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010A884_aces_high);

void func_8010A9D4_aces_high(omObjData *object) {
    omObjData *camObj = (omObjData *)object->work[1];
    AceHighCamData *camData = (AceHighCamData *)camObj->data;
    f32 rotX = (camObj->trans.y - -250.0f) * 0.08f;

    CRotM[camData->camIdx].x = rotX;
    CRotM[camData->camIdx].z = 0.0f;
    CRotM[camData->camIdx].y = camData->unk_8C;
    CenterM[camData->camIdx].x = camObj->trans.x;
    CenterM[camData->camIdx].y = 0.0f;
    CenterM[camData->camIdx].z = camObj->trans.z;
    CZoomM[camData->camIdx] = 650.0f;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DDA8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AADC_aces_high);

void func_8010ACE0_aces_high(omObjData *object) {
    AceHighCamData *camData = (AceHighCamData *)((omObjData *)object->work[1])->data;

    CenterM[camData->camIdx].y = 0.0f;
    CZoomM[camData->camIdx] = 2700.0f;
    CRotM[camData->camIdx].x = 90.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AD4C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010AE30_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B0E8_aces_high);

void func_8010B224_aces_high(omObjData *object) {
    Hu3DCamSetPositionOrientation(OM_GET_WORK_PTR(object, s16)[1], &D_8010DEA8_aces_high, &D_8010DEB4_aces_high,
                                  &D_8010DEC0_aces_high);
    Hu3DCamUpdateMtx(OM_GET_WORK_PTR(object, s16)[1]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B26C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B4BC_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B618_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B760_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010B9F4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BCC4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BD84_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010BF3C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010C288_aces_high);

void func_8010C9DC_aces_high(void) {
    omObjData *obj = omAddObj(0x1E, 0, 0, -1, func_8010CA6C_aces_high);

    D_8010DE80_aces_high = obj;
    obj->work[0] = 1;
    D_8010DF20_aces_high = InitEspriteSlot(func_8000B838_main(0x38001C), 0, 0);
    func_8000BBD4_main(D_8010DF20_aces_high, 0xA0, 0x78);
    func_8000BCC8_main(D_8010DF20_aces_high, 0x8064);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CA6C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CD88_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CE5C_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010CFF8_aces_high);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", D_8010DE28_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D1D8_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D6D4_aces_high);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D994_aces_high);
