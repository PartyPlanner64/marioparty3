#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "mallocblock.h"
#include "opening.h"

extern const Vec D_80114D84_opening;
extern const Vec D_80114D90_opening;

void func_8000BEAC_main(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_80017CD0_main(HuMtx4F, f32, f32, f32);
HmfMotionNode *func_8001D33C_main(s16 model, char *name);

void func_801061F0_opening(void) {
    func_8010621C_opening();
    func_801067D4_opening();
    func_80107A4C_opening();
}

void func_8010621C_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114EB0_opening); i++) {
        D_801155B0_opening[i].animId = -1;
        D_80114EB0_opening[i].espriteSlot = -1;
        D_80114EB0_opening[i].unk_04 = D_80114EB0_opening[i].unk_08 = 0;
        D_80114EB0_opening[i].unk_0C = D_80114EB0_opening[i].unk_10 = 0.0f;
        D_80114EB0_opening[i].unk_14 = D_80114EB0_opening[i].unk_0C;
        D_80114EB0_opening[i].unk_18 = 0xFF;
    }
}

s16 opAnimIdGet(s32 slot) {
    return D_801155B0_opening[slot].animId;
}

s16 opEspIdGet(s32 slot) {
    return D_80114EB0_opening[slot].espriteSlot;
}

void opAnimCreate(s32 arg0, s32 arg1) {
    D_801155B0_opening[arg0].animId = func_8000B838_main(arg1);
}

void opAnimKill(s32 arg0) {
    if (D_801155B0_opening[arg0].animId != -1) {
        HuSprKill(D_801155B0_opening[arg0].animId);
    }
    D_801155B0_opening[arg0].animId = -1;
}

void opEspCreate(s32 slot, s16 animId) {
    D_80114EB0_opening[slot].espriteSlot = InitEspriteSlot(D_801155B0_opening[animId].animId, 0, 0);
    opSprPosSet(slot, 0xA0, 0x78);
}

void opEspKill(s32 slot) {
    if (D_80114EB0_opening[slot].espriteSlot != -1) {
        func_8000C184_main(D_80114EB0_opening[slot].espriteSlot);
    }
    D_80114EB0_opening[slot].espriteSlot = -1;
}

void opSprCreate(s32 slot, s32 resourceId) {
    opAnimCreate(slot, resourceId);
    opEspCreate(slot, slot);
}

void opSprBGCreate(s32 slot, s32 resourceId) {
    opSprCreate(slot, resourceId);
    func_8000BC48_main(D_80114EB0_opening[slot].espriteSlot, 0x4000);
}

void opSprKill(s32 slot) {
    opEspKill(slot);
    opAnimKill(slot);
}

void opSprKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114EB0_opening); i++) {
        opSprKill(i);
    }
}

void opSprDispOn(s32 slot) {
    func_8000BB54_main(D_80114EB0_opening[slot].espriteSlot);
}

void opSprDispOff(s32 slot) {
    func_8000BB94_main(D_80114EB0_opening[slot].espriteSlot);
}

void opSprBGDispOn(s32 slot) {
    opSprDispOn(slot);
}

void opSprBGDispOff(s32 slot) {
    opSprDispOff(slot);
}

void opSprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    D_80114EB0_opening[arg0].unk_04 = arg1;
    D_80114EB0_opening[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_80114EB0_opening[arg0].espriteSlot, arg1, arg2);
}

void opSprPosGet(s32 slot, s32 *x, s32 *y) {
    *x = D_80114EB0_opening[slot].unk_04;
    *y = D_80114EB0_opening[slot].unk_08;
}

void opSprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    D_80114EB0_opening[arg0].unk_0C = arg1;
    D_80114EB0_opening[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_80114EB0_opening[arg0].espriteSlot, arg1, arg2);
}

void opSprAlphaSet(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void opSprAttrSet(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void opSprAttrReset(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void func_80106734_opening(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

void func_80106768_opening(s32 slot, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80114EB0_opening[slot].espriteSlot, 1);
    func_8000BD94_main(D_80114EB0_opening[slot].espriteSlot, arg1, arg2);
}

void func_801067D4_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115630_opening); i++) {
        D_80115630_opening[i].modelId = -1;
        D_80115630_opening[i].motionId = -1;
    }
}

void opModelCreate(s32 slot, s32 resourceId, s32 arg2) {
    s16 modelId;

    modelId = func_8000B108_main(resourceId, arg2);
    D_80115630_opening[slot].modelId = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void opMotionCreate(s32 slot, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    D_80115630_opening[slot].motionId = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void opModelKill(s32 slot) {
    if (D_80115630_opening[slot].modelId != -1) {
        func_8001ACDC_main(D_80115630_opening[slot].modelId);
        D_80115630_opening[slot].modelId = -1;
    }
    if (D_80115630_opening[slot].motionId != -1) {
        func_8002D4B8_main(D_80115630_opening[slot].motionId);
        D_80115630_opening[slot].motionId = -1;
    }
}

void opModelKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115630_opening); i++) {
        opModelKill(i);
    }
}

s16 opModelIdGet(s32 modelId) {
    return D_80115630_opening[modelId].modelId;
}

s16 opMotionIdGet(s32 motionId) {
    return D_80115630_opening[motionId].motionId;
}

void opModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].rotX = arg1;
    D_80115630_opening[arg0].rotY = arg2;
    D_80115630_opening[arg0].rotZ = arg3;
    Hu3DModelRotSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].posX = arg1;
    D_80115630_opening[arg0].posY = arg2;
    D_80115630_opening[arg0].posZ = arg3;
    Hu3DModelPosSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80115630_opening[arg0].scaleX = arg1;
    D_80115630_opening[arg0].scaleY = arg2;
    D_80115630_opening[arg0].scaleZ = arg3;
    Hu3DModelScaleSet(D_80115630_opening[arg0].modelId, arg1, arg2, arg3);
}

void opModelPosGet(s32 modelId, f32 *posX, f32 *posY, f32 *posZ) {
    *posX = D_80115630_opening[modelId].posX;
    *posY = D_80115630_opening[modelId].posY;
    *posZ = D_80115630_opening[modelId].posZ;
}

void opModelRotGet(s32 modelId, f32 *rotX, f32 *rotY, f32 *rotZ) {
    *rotX = D_80115630_opening[modelId].rotX;
    *rotY = D_80115630_opening[modelId].rotY;
    *rotZ = D_80115630_opening[modelId].rotZ;
}

void opModelScaleGet(s32 modelId, f32 *scaleX, f32 *scaleY, f32 *scaleZ) {
    *scaleX = D_80115630_opening[modelId].scaleX;
    *scaleY = D_80115630_opening[modelId].scaleY;
    *scaleZ = D_80115630_opening[modelId].scaleZ;
}

void opModelDispOff(s32 arg0) {
    func_8001C258_main(D_80115630_opening[arg0].modelId, 4, 4);
}

void opModelDispOn(s32 arg0) {
    func_8001C258_main(D_80115630_opening[arg0].modelId, 4, 0);
}

void opMotionFlagSet(s32 modelId, s16 arg1) {
    func_8001C814_main(D_80115630_opening[modelId].modelId, -1, arg1);
}

void opMotionShiftSet(s32 modelId, s32 motionId, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80115630_opening[modelId].modelId, D_80115630_opening[motionId].motionId, arg2, arg3, arg4);
}

void func_80106DD0_opening(s32 modelId, s16 arg1) {
    func_8001C814_main(D_80115630_opening[modelId].modelId, arg1, 0);
}

void opMotionSpeedSet(s32 modelId, f32 speed) {
    func_8001C92C_main(D_80115630_opening[modelId].modelId, speed);
}

void opMotionTimeSet(s32 slot, u32 time) {
    func_8001C6A8_main(D_80115630_opening[slot].modelId, time);
}

void opMotionEndWait(s32 slot) {
    while (HmfModelData[D_80115630_opening[slot].modelId].unk40 !=
           D_800CCF58_main[HmfModelData[D_80115630_opening[slot].modelId].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 opMotionEndCheck(s32 arg0) {
    s16 modelId = D_80115630_opening[arg0].modelId;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void opMotionSet(s32 modelId, s32 motionId, s16 arg2) {
    s16 model = opModelIdGet(modelId);
    s16 motion = opMotionIdGet(motionId);

    func_8001F304_main(model, motion);
    func_8001C814_main(model, -1, arg2);
}

void func_80107048_opening(void) {
    // The original call omits the resource id.
    D_801171B0_opening = ((s16 (*)())func_8000B838_main)();
    D_801171B2_opening = InitEspriteSlot(D_801171B0_opening, 0, 0);
    func_8000BC48_main(D_801171B2_opening, 0x4000);
    func_8000BBD4_main(D_801171B2_opening, 0xA0, 0x78);
}

void func_801070AC_opening(void) {
    func_8000C184_main(D_801171B2_opening);
    HuSprKill(D_801171B0_opening);
}

u32 func_801070D8_opening(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = func_800452A0_main(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", func_80107140_opening);

s16 func_8010738C_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_8005BEE0_main(slot, 255);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C154_main(slot, 192, 192, 192);
    func_8005FBF8_main(slot, 0, 64, 64);
    func_8005C02C_main(slot, 7);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801074D8_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 4);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_8005BEE0_main(slot, 255);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C060_main(slot, 5, 0, 176, 192);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005C154_main(slot, 192, 192, 192);
    func_8005FBF8_main(slot, 255, 255, 255);
    func_8005C02C_main(slot, 1);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_80107640_opening(u32 event, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 slot;

    slot = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(slot, -1, 17);
    func_8005BDFC_main(slot, 0);
    func_80060144_main(slot);
    func_8005BE30_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005C060_main(slot, 5, 0, 176, 192);
    func_8005C060_main(slot, 7, 255, 255, 255);
    func_8005C060_main(slot, 0, 0, 0, 0);
    func_8005C060_main(slot, 3, 0, 0, 0);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005C154_main(slot, 192, 192, 0);
    func_8005FBF8_main(slot, 255, 255, 255);
    func_8005C02C_main(slot, 6);
    func_8005D294_main(slot);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801077E8_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 19);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_80060C14_main(slot, 1);
    func_8005FE54_main(slot, 1);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_801078B4_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 20);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_80060C14_main(slot, 0);
    func_8005FE54_main(slot, 1);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

s16 func_80107980_opening(u32 event, s16 x, s16 y, s16 style) {
    s16 slot;

    slot = func_80060880_main(x, y, 19);
    func_8005C060_main(slot, 2, 255, 64, 64);
    func_8005C060_main(slot, 4, 96, 255, 64);
    func_8005C060_main(slot, 6, 255, 255, 64);
    func_8005FE54_main(slot, 1);
    func_80060C14_main(slot, 0);
    func_8005B43C_main(slot, event, -1, -1);
    return slot;
}

void func_80107A4C_opening(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_801171B8_opening[i].espriteSlot = -1;
        D_801171B8_opening[i].event = NULL;
    }
}

void func_80107A90_opening(s32 index) {
    if (D_801171B8_opening[index].unk_08 == 3) {
        func_80060EA8_main(D_801171B8_opening[index].espriteSlot, 1);
        func_800610E0_main(D_801171B8_opening[index].espriteSlot);
    } else {
        func_8005FE90_main(D_801171B8_opening[index].espriteSlot);
        func_8005F364_main(D_801171B8_opening[index].espriteSlot);
        D_801171B8_opening[index].espriteSlot = -1;
    }
    if (D_801171B8_opening[index].event != NULL) {
        func_80019C00_main(D_801171B8_opening[index].event);
        D_801171B8_opening[index].event = NULL;
    }
}

void func_80107B74_opening(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801171B8_opening); i++) {
        if (D_801171B8_opening[i].espriteSlot != -1) {
            func_80107A90_opening(i);
        }
    }
}

void func_80107BD8_opening(s32 slot, f32 x, f32 y) {
    func_8005BB18_main(D_801171B8_opening[slot].espriteSlot, x, y);
}

void func_80107C08_opening(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_801171B8_opening[arg0].espriteSlot, arg1, arg2);
}

void func_80107C70_opening(s32 slot) {
    func_8005FFA8_main(D_801171B8_opening[slot].espriteSlot);
}

void func_80107CA0_opening(s32 slot) {
    func_8005FE90_main(D_801171B8_opening[slot].espriteSlot);
}

void func_80107CD0_opening(s32 slot, u32 event) {
    u32 newEvent;

    func_8005D294_main(D_801171B8_opening[slot].espriteSlot);
    if (D_801171B8_opening[slot].event != NULL) {
        func_80019C00_main(D_801171B8_opening[slot].event);
        D_801171B8_opening[slot].event = NULL;
    }
    newEvent = func_801070D8_opening(event);
    if (0x80000000U < newEvent) {
        D_801171B8_opening[slot].event = (void *)newEvent;
    }
    func_8005B43C_main(D_801171B8_opening[slot].espriteSlot, newEvent, -1, -1);
}

void func_80107D9C_opening(s32 slot, s8 arg1, s32 arg2) {
    func_800601BC_main(D_801171B8_opening[slot].espriteSlot, arg2, arg1);
}

s32 func_80107DD8_opening(s32 slot, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_801171B8_opening[slot].espriteSlot, arg1, arg2);
}

s16 func_80107E10_opening(s32 slot) {
    return D_801171B8_opening[slot].espriteSlot;
}

void func_80107E2C_opening(s32 index) {
    while (func_8005E0C0_main(D_801171B8_opening[index].espriteSlot) != 0) {
        HuPrcVSleep();
    }
}

void func_80107E80_opening(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_80107EBC_opening(s32 slot, s16 arg1) {
    func_8005BE30_main(D_801171B8_opening[slot].espriteSlot, arg1);
}

u16 func_80107EF4_opening(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            camera = HmfModelData[gCameraList[0].unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", camera->unk08, camera->unk0C, camera->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", camera->unk14, camera->unk18, camera->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", camera->unk20, camera->unk24, camera->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void opDemoEventSetup(void) {
    func_801061F0_opening();
    func_80110F48_opening();
    CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
    CameraScissorSet(0, &D_80114BD0_opening);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    func_80112944_opening();
    func_80110B90_opening();
    opContErrorCreate();
}

void func_80108118_opening(s32 slot, u32 event) {
    func_80107140_opening(slot, event, 160, 194, 0, 0, 4);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524820", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524820", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524820", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524820", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524820", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", opDemoEvent);

void opDemoEventKill(void) {
    func_80107B74_opening();
    opContErrorKill();
    func_80110B9C_opening();
    opWipeKill(15);
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
    MBBackKill();
}

void func_80110B90_opening(void) {
    D_80117338_opening.obj = NULL;
}

void func_80110B9C_opening(void) {
    if (D_80117338_opening.obj != NULL) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        omDelObj(D_80117338_opening.obj);
    }
    D_80117338_opening.obj = NULL;
}

void func_80110C04_opening(omObjData *obj) {
    Vec at;
    f32 random;
    f32 offset;

    D_80117338_opening.active = ~D_80117338_opening.active;
    if (D_80117338_opening.active) {
        random = rand8();
    } else {
        random = -(f32)rand8();
    }
    random *= 1.0f / 255.0f;
    random *= (1.0f - D_80117338_opening.frame * 0.125f) * 0.8f + 0.2f;
    offset = random * D_80117338_opening.magnitude;
    HuVecCopy3F(&at, &D_80114BC4_opening);
    at.y = offset + offset + at.y;
    CameraViewportSet(0, &D_80114BB8_opening, &at);
    offset = -offset;
    MBCameraOffsetSet(0, offset);
    D_80117338_opening.frame++;
    if (D_80117338_opening.totalFrames < D_80117338_opening.frame) {
        CameraViewportSet(0, &D_80114BB8_opening, &D_80114BC4_opening);
        MBCameraOffsetSet(0, 0);
        func_80110B9C_opening();
    }
}

void func_80110D8C_opening(s32 totalFrames, f32 magnitude) {
    D_80117338_opening.frame = 0;
    D_80117338_opening.totalFrames = totalFrames;
    D_80117338_opening.magnitude = magnitude;
    D_80117338_opening.active = 1;
    D_80117338_opening.obj = omAddObj(6, 0, 0, -1, func_80110C04_opening);
}

void opDemoCharCreate(s32 slot, s32 resourceId, f32 x, f32 y, f32 z) {
    opModelCreate(slot, resourceId, 0x6A9);
    opModelPosSet(slot, x, y, z);
    opModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
    opMotionFlagSet(slot, 2);
}

void opDemoShadowCreate(s32 slot, f32 x, f32 y, f32 z) {
    opModelCreate(slot, 9, 0x229);
    opModelPosSet(slot, x, y, z);
    opModelRotSet(slot, 0.0f, 0.0f, 0.0f);
    opModelScaleSet(slot, 1.0f, 1.0f, 1.0f);
}

void opDemoModelKill(void) {
    opModelKillAll();
}

void opDemoSprKill(void) {
    opSprKillAll();
}

void func_80110F48_opening(void) {
    D_80117350_opening.obj = NULL;
    HuVecCopyXYZ(&D_80117350_opening.pos, 350.0f, 190.0f, 3770.0f);
    HuVecCopyXYZ(&D_80117350_opening.at, -1000.0f, 130.0f, 450.0f);
    HuVecCopyXYZ(&D_80117350_opening.up, 0.0f, 1.0f, 0.0f);
}

void func_80110FB0_opening(Vec *pos, Vec *at) {
    func_80111028_opening();
    HuVecCopy3F(&D_80117350_opening.pos, pos);
    HuVecCopy3F(&D_80117350_opening.at, at);
    D_80117350_opening.obj = omAddObj(6, 0, 0, -1, func_80111090_opening);
}

void func_80111028_opening(void) {
    if (D_80117350_opening.obj != NULL) {
        omDelObj(D_80117350_opening.obj);
    }
    D_80117350_opening.obj = NULL;
}

void func_8011105C_opening(void) {
    Hu3DCamSetPositionOrientation(0, &D_80117350_opening.pos, &D_80117350_opening.at, &D_80117350_opening.up);
    Hu3DCamUpdateMtx(0);
}

void func_80111090_opening(omObjData *obj) {
    func_8011105C_opening();
}

void func_801110AC_opening(f32 *posX, f32 *posY, f32 *posZ, f32 *atX, f32 *atY, f32 *atZ) {
    *posX = D_80117350_opening.pos.x;
    *posY = D_80117350_opening.pos.y;
    *posZ = D_80117350_opening.pos.z;
    *atX = D_80117350_opening.at.x;
    *atY = D_80117350_opening.at.y;
    *atZ = D_80117350_opening.at.z;
}

void func_801110F0_opening(f32 posX, f32 posY, f32 posZ, f32 atX, f32 atY, f32 atZ) {
    HuVecCopyXYZ(&D_80117350_opening.pos, posX, posY, posZ);
    HuVecCopyXYZ(&D_80117350_opening.at, atX, atY, atZ);
}

f32 func_80111164_opening(f32 x1, f32 z1, f32 x2, f32 z2) {
    return -(atan2df(z2 - z1, x2 - x1) - 90.0f);
}

f32 func_801111AC_opening(f32 current, f32 target, f32 step) {
    f32 difference = target - current;

    difference = difference < 0.0f ? difference + 360.0f : difference;
    if (difference > 180.0f) {
        if (difference > 360.0f - step) {
            return target;
        }
        return current - step;
    }
    if (difference < step) {
        return target;
    }
    return current + step;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", func_8011124C_opening);

f32 func_80111490_opening(f32 current, f32 x, f32 z, f32 weight) {
    f32 angle = func_80111164_opening(0.0f, 0.0f, x, z);
    f32 difference;

    if (angle < 0.0f) {
        angle += 360.0f;
    }
    difference = angle - current;
    difference = difference < 0.0f ? difference + 360.0f : difference;
    if (difference > 180.0f) {
        return -(360.0f - difference) * weight + current;
    }
    return difference * weight + current;
}

void func_80111580_opening(void) {
    s32 model1;
    s32 model2;
    Vec pos;
    s32 i;
    f32 t;
    f32 angle;
    f32 size;
    f32 remaining;

    model1 = func_80111984_opening(0x110012, 0x689);
    model2 = func_80111984_opening(0x110012, 0x689);
    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
    for (i = 0, remaining = 1.0f; i < 120; i++) {
        if (i == 90) {
            func_80107CA0_opening(0);
        }
        t = i * (1.0f / 120.0f);
        HuSqrtf(t);
        angle = t * 360.0f;
        t = remaining - t;
        size = t * 8.0f;
        pos.x = t * 100.0f * sindf(angle);
        pos.y = 40.0f - pos.x * 0.2f - t * 120.0f * cosdf(angle);
        pos.z = t * 800.0f * cosdf(angle) + -200.0f;
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model1, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model2, pos.x, pos.y, pos.z, size);
        func_80111DDC_opening(model2, pos.x, pos.y, pos.z, size);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_8001ACDC_main(model1);
    func_8001ACDC_main(model2);
}

s16 func_801117D4_opening(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    modelId = func_8000B108_main(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(modelId, 0x20000, 0x20000);
    func_8001C448_main(modelId);
    func_8001C954_main(modelId);
    func_8001C514_main(modelId);
    func_80013390_main(modelId, -1, 0, func_80111F58_opening);
    data = HmfModelData[modelId].hmf;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk08.f = 30.0f;
    work->unk0C.f = 720.0f;
    work->unk10.f = 80.0f;
    work->unk14 = 5.0f;
    startRadius = work->unk10.f / 10.0f;
    radiusStep = (work->unk10.f - startRadius) / work->unk08.f;
    angleStep = work->unk0C.f / work->unk08.f;
    for (i = 0; i < data->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = startRadius;
        particle->unk1C = radiusStep;
        particle->unk24 = angleStep;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return modelId;
}

s32 func_80111984_opening(s32 resourceId, s32 arg1) {
    s16 modelId;
    HmfData *data;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 startRadius;
    f32 radiusStep;
    f32 angleStep;
    s16 i;

    HuVecCopyXYZ(&D_80117378_opening, 0.0f, 0.0f, 0.0f);
    D_80117384_opening = 0;
    modelId = func_8000B108_main(resourceId, arg1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(modelId, 0x20000, 0x20000);
    func_8001C448_main(modelId);
    func_8001C954_main(modelId);
    func_8001C514_main(modelId);
    func_80013390_main(modelId, -1, 0, func_80112120_opening);
    data = HmfModelData[modelId].hmf;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk08.f = 30.0f;
    work->unk0C.f = 720.0f;
    work->unk10.f = 80.0f;
    work->unk14 = 5.0f;
    startRadius = work->unk10.f / 10.0f;
    radiusStep = (work->unk10.f - startRadius) / work->unk08.f;
    angleStep = work->unk0C.f / work->unk08.f;
    for (i = 0; i < data->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = startRadius;
        particle->unk1C = radiusStep;
        particle->unk24 = angleStep;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return modelId;
}

u32 func_80111B34_opening(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed - quotient * 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_80111C08_opening(void) {
    D_80114BE0_opening = func_80111B34_opening(D_80114BE0_opening);
    return D_80114BE0_opening;
}

u32 func_80111C30_opening(u32 max) {
    u32 value;

    value = func_80111B34_opening(D_80114BE0_opening);
    D_80114BE0_opening = value;
    return (value & 0x7FFFFFFF) % max;
}

s32 func_80111C88_opening(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    f32 angle;

    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = func_80111C30_opening(360);
            particle->unk20 = work->unk10.f / 10.0f;
            angle = (f32)func_80111C30_opening(150) - 75.0f;
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0.0f;
            particle->unk04 = 0.0f;
            return 1;
        }
    }
    return 0;
}

s32 func_80111DDC_opening(s16 modelId, f32 x, f32 y, f32 z, f32 size) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    D_80117378_opening.x = x;
    D_80117378_opening.y = x;
    D_80117378_opening.z = x;
    work = HmfModelData[modelId].unkBC;
    particle = work->unk58;
    work->unk1C.f = x;
    work->unk20.f = y;
    work->unk24.f = z;
    for (i = 0; i < data->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk04 = 0.0f;
            particle->unk24 = sindf(func_80111C30_opening(360));
            particle->unk28 = sindf(func_80111C30_opening(360));
            particle->unk2C = sindf(func_80111C30_opening(360));
            particle->unk0C = work->unk1C.f;
            particle->unk14 = work->unk24.f;
            particle->unk10 = work->unk20.f;
            particle->unk08 = size;
            return 1;
        }
    }
    return 0;
}

void func_80111F58_opening(s16 modelId) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    s16 count = data->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk18 += particle->unk24;
            if (particle->unk18 < 0.0f) {
                particle->unk18 += 360.0f;
            } else if (particle->unk18 >= 360.0f) {
                particle->unk18 -= 360.0f;
            }
            radius = particle->unk20 + particle->unk1C;
            particle->unk20 = radius;
            radius *= particle->unk2C;
            particle->unk0C = radius * sindf(particle->unk18) + work->unk1C.f;
            particle->unk14 = radius * cosdf(particle->unk18) + work->unk24.f;
            particle->unk10 = particle->unk20 * particle->unk28 + work->unk20.f;
            particle->unk04 += work->unk14;
            if (particle->unk04 > 180.0f) {
                particle->unk04 = 180.0f;
            }
            particle->unk08 = sindf(particle->unk04) * work->unk14;
        }
    }
    work->unk02++;
}

void func_80112120_opening(s16 modelId) {
    HmfData *data = HmfModelData[modelId].hmf;
    HmfModelData_UnkBC_Struct *work = HmfModelData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = work->unk58;
    s16 i;
    s16 count = data->unk1A;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk0C = particle->unk24 * 3.0f + particle->unk0C;
            particle->unk10 = particle->unk28 * 3.0f + particle->unk10 - 1.0f;
            particle->unk14 = particle->unk2C * 3.0f + particle->unk14;
            particle->unk08 = particle->unk08 - 0.2f > 0.0f ? particle->unk08 - 0.4f : 0.0f;
            if (particle->unk08 <= 0.0f) {
                particle->unk08 = 0.0f;
                particle->unk04 = 180.0f;
            }
        }
    }
    work->unk02++;
}

void opTitleSetup(void) {
    u16 sprite;

    func_801061F0_opening();
    func_80110F48_opening();
    opContErrorCreate();
    func_80112944_opening();
    {
        Vec initPos = D_80114D84_opening;
        Vec initAt = D_80114D90_opening;
        func_80110FB0_opening(&initPos, &initAt);
    }
    opSprBGCreate(0, 0x100000);
    opSprPosSet(0, 160, 120);
    func_8000BCC8_main((u16)opEspIdGet(0), 9);
    opSprBGDispOn(0);
    opSprBGCreate(1, 0x100001);
    opSprPosSet(1, 160, 120);
    func_8000BCC8_main((u16)opEspIdGet(1), 11);
    opSprBGDispOn(1);
    opSprBGCreate(2, 0x100002);
    opSprPosSet(2, 160, 71);
    opSprAttrSet(2, 8);
    opSprAlphaSet(2, 255);
    func_8000BCC8_main((u16)opEspIdGet(2), 8);
    opSprBGCreate(3, 0x100005);
    opSprPosSet(3, 160, 71);
    opSprAttrSet(3, 8);
    opSprAlphaSet(3, 255);
    sprite = opEspIdGet(3);
    func_8000BEAC_main(sprite, 255, 255, 255);
    func_8000BCC8_main(sprite, 9);
    opSprBGCreate(4, 0x100003);
    opSprPosSet(4, 158, 197);
    opSprAttrSet(4, 8);
    opSprAlphaSet(4, 255);
    func_8000BCC8_main((u16)opEspIdGet(4), 8);
    opSprBGCreate(5, 0x100004);
    opSprPosSet(5, 158, 197);
    opSprAttrSet(5, 0x1008);
    opSprAlphaSet(5, 255);
    sprite = opEspIdGet(5);
    func_8000BEAC_main(sprite, 0, 6, 115);
    func_8000BCC8_main(sprite, 9);
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524820", opTitleSprMain);

void opTitleKill(void) {
    opSprKill(5);
    opSprKill(4);
    opSprKill(3);
    opSprKill(2);
    opSprKill(1);
    opSprKill(0);
    opContErrorKill();
    opDemoObjKillAll();
    opDemoModelKill();
    opDemoSprKill();
}

void func_80112944_opening(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_80117388_opening[i].obj = NULL;
    }
}

void opDemoObjKillAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80117388_opening); i++) {
        opDemoObjKill(i);
    }
}

void opDemoObjKill(s32 index) {
    if (D_80117388_opening[index].obj != NULL) {
        omDelObj(D_80117388_opening[index].obj);
    }
    D_80117388_opening[index].obj = NULL;
}

void opDemoObjCreate(s32 index, omObjFunc func) {
    omObjData *obj;

    opDemoObjKill(index);
    obj = omAddObj(6, 0, 0, -1, func);
    D_80117388_opening[index].obj = obj;
    obj->work[0] = index;
}

void func_80112A74_opening(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;

    if (D_8011738C_opening[index][0] < 0) {
        if (opMotionEndCheck(modelId)) {
            opMotionShiftSet(modelId, D_8011739C_opening[index][0].motion[0], 4, 4, 2);
            D_8011738C_opening[index][0] = 0;
        }
    } else if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        opMotionShiftSet(modelId, D_80117398_opening[index][0].motion[0], 4, 4, 0);
        D_8011738C_opening[index][0] = -1;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_80112BA0_opening(s32 index, s32 modelId, s32 motion1, s32 motion2, s32 startTime, s32 frames) {
    opDemoObjCreate(index, func_80112A74_opening);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].motion[0] = motion1;
    D_8011739C_opening[index][0].motion[0] = motion2;
    D_80117390_opening[index][0] = frames;
    D_8011738C_opening[index][0] = startTime;
    if (startTime >= 0) {
        opMotionSet(modelId, motion1, 0);
        opMotionTimeSet(modelId, startTime);
    } else {
        opMotionSet(modelId, motion2, 2);
        opMotionTimeSet(modelId, 0);
    }
}

void func_80112C8C_opening(omObjData *obj) {
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;

    if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        opMotionTimeSet(modelId, 0);
        D_8011738C_opening[index][0] = 0;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_80112D30_opening(s32 index, s32 modelId, s32 startTime, s32 endTime) {
    opDemoObjCreate(index, func_80112C8C_opening);
    D_80117394_opening[index].modelId = modelId;
    D_8011738C_opening[index][0] = startTime;
    D_80117390_opening[index][0] = endTime;
    func_80106DD0_opening(modelId, 3);
    if (startTime > 0) {
        opMotionTimeSet(modelId, startTime);
    } else {
        opMotionTimeSet(modelId, 0);
    }
}

void opDemoOutEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 otherModelId = modelId + 32;
    s16 effectId = D_80117398_opening[index][0].effectId;
    f32 scale = D_801173A8_opening[index][0];

    HuVecCopy3F(&pos, &D_8011739C_opening[index][0].pos);
    if (D_8011738C_opening[index][0] >= 40) {
        func_8001ACDC_main(effectId);
        D_8011738C_opening[index][0] = 0;
        opDemoObjKill(index);
    } else if (D_8011738C_opening[index][0] >= 20) {
        opModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
        opModelScaleSet(otherModelId, 3.0f, 1.0f, 3.0f);
        opModelDispOff(modelId);
        opModelDispOff(otherModelId);
        D_8011738C_opening[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(effectId, pos.x, pos.y, pos.z);
        opModelScaleSet(modelId, scale, 1.0f, scale);
        opModelScaleSet(otherModelId, scale, 1.0f, scale);
        D_801173A8_opening[index][0] = scale;
        D_8011738C_opening[index][0]++;
    }
}

void opDemoOutEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    opDemoObjCreate(index, opDemoOutEffMain);
    effectId = func_801117D4_opening(0x110012, 0x689);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].effectId = effectId;
    opModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&D_8011739C_opening[index][0].pos, &pos);
    D_80117394_opening[index].unk_1C.y = 1.0f;
    D_8011738C_opening[index][0] = 0;
}

void opDemoGuideInEffMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s16 effectId = D_80117398_opening[index][0].effectId;
    f32 scale = D_801173A8_opening[index][0];

    HuVecCopy3F(&pos, &D_8011739C_opening[index][0].pos);
    if (D_8011738C_opening[index][0] >= 80) {
        func_8001ACDC_main(effectId);
        D_8011738C_opening[index][0] = 0;
        opDemoObjKill(index);
    } else if (D_8011738C_opening[index][0] >= 50) {
        D_8011738C_opening[index][0]++;
    } else {
        scale -= 1.0f / 7.0f;
        if (scale <= 0.0f) {
            scale = 0.0f;
        }
        func_80111C88_opening(effectId, pos.x, pos.y + 25.0f, pos.z);
        D_801173A8_opening[index][0] = scale;
        D_8011738C_opening[index][0]++;
    }
}

void opDemoGuideInEffCreate(s32 index, s32 modelId) {
    Vec pos;
    s16 effectId;

    opDemoObjCreate(index, opDemoGuideInEffMain);
    effectId = func_801117D4_opening(0x110012, 0x689);
    D_80117394_opening[index].modelId = modelId;
    D_80117398_opening[index][0].effectId = effectId;
    opModelPosGet(modelId, &pos.x, &pos.y, &pos.z);
    pos.y += 60.0f;
    HuVecCopy3F(&D_8011739C_opening[index][0].pos, &pos);
    D_80117394_opening[index].unk_1C.y = 1.0f;
    D_8011738C_opening[index][0] = 0;
}

void opDemoStarWaitMain(omObjData *obj) {
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    f32 step = 1.0f / D_80117390_opening[index][0];
    f32 angle = step * 360.0f + D_801173A8_opening[index][0];
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_801173A8_opening[index][0] = angle;
    height = sindf(angle) * D_801173A4_opening[index][0];
    HuVecCopy3F(&pos, &D_80117398_opening[index][0].pos);
    opModelPosSet(modelId, pos.x, height + pos.y, pos.z);
}

void opDemoStarWaitCreate(s32 index, s32 modelId, f32 x, f32 y, f32 z, f32 arg5, s32 frames) {
    opDemoObjCreate(index, opDemoStarWaitMain);
    D_80117394_opening[index].modelId = modelId;
    HuVecCopyXYZ(&D_80117398_opening[index][0].pos, x, y, z);
    D_801173A4_opening[index][0] = arg5;
    D_801173A8_opening[index][0] = 0;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = frames;
}

void func_801134FC_opening(s32 index, Vec *pos1, Vec *pos2, f32 scale, f32 angle) {
    func_80088800_main(D_801173BC_opening[index][0]->unk58, pos1->x, pos1->y, pos1->z);
    func_80017CD0_main(D_801173BC_opening[index][0]->unk58, scale, 1.0f, scale);
    func_800185A4_main(D_801173BC_opening[index][0]->unk58, angle);
    func_80088800_main(D_801173C0_opening[index][0]->unk58, pos2->x, pos2->y + 4.0f, pos2->z);
    func_80017CD0_main(D_801173C0_opening[index][0]->unk58, scale, 1.0f, scale);
    func_800185A4_main(D_801173C0_opening[index][0]->unk58, angle);
}

void func_8011361C_opening(omObjData *obj) {
    Vec pos;
    Vec shadow;
    s8 index = obj->work[0];
    f32 step = 1.0f / D_80117390_opening[index][0];
    f32 angle = step * 360.0f + D_8011739C_opening[index][0].pos.x;
    f32 height;

    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    D_8011739C_opening[index][0].pos.x = angle;
    height = sindf(angle) * D_8011739C_opening[index][0].pos.y;
    HuVecCopy3F(&pos, &D_801173B0_opening[index][0].pos);
    pos.y = height + pos.y;
    HuVecCopy3F(&shadow, &D_801173B0_opening[index][0].pos);
    shadow.y = 0;
    func_801134FC_opening(index, &pos, &shadow, 1.0f, 0);
}

void func_8011373C_opening(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    Vec modelPos;
    Vec shadow;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    OpWork *slot = &D_80117394_opening[index];
    f32 time;

    HuVecCopy3F(&start, &slot->unk_1C);
    HuVecCopy3F(&end, &slot->unk_28);
    time = 1.0f / D_80117390_opening[index][0];
    time *= D_8011738C_opening[index][0];
    HuVecCopyXYZ(&pos, time * (end.x - start.x) + start.x,
                 time * (end.y - start.y) + start.y + (0.25 - (time - 0.5f) * (time - 0.5f)) * 4.0 * 5.0 * 20.0,
                 time * (end.z - start.z) + start.z);
    HuVecCopy3F(&start, &slot->unk_1C);
    opModelPosSet(modelId, 0, 0, 0);
    HuVecCopyXYZ(&modelPos, pos.x, pos.y, pos.z);
    HuVecCopyXYZ(&shadow, pos.x, 0, pos.z);
    time = time * 0.8 + 0.2f;
    func_801134FC_opening(index, &modelPos, &shadow, time, 0);
    if (D_8011738C_opening[index][0] >= D_80117390_opening[index][0]) {
        D_8011738C_opening[index][0] = 0;
        obj->func = func_8011361C_opening;
    } else {
        D_8011738C_opening[index][0]++;
    }
}

void func_801139B0_opening(s32 index, s32 modelId, Vec *pos1, Vec *pos2, char *node1, char *node2) {
    s16 model;
    OpWork *slot;

    opDemoObjCreate(index, func_8011373C_opening);
    D_80117394_opening[index].modelId = modelId;
    slot = &D_80117394_opening[index];
    HuVecCopy3F(&slot->unk_1C, pos1);
    HuVecCopy3F(&slot->unk_28, pos2);
    D_8011739C_opening[index][0].pos.y = 12.0f;
    D_8011739C_opening[index][0].pos.x = 0;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = 20;
    model = opModelIdGet(modelId);
    D_801173BC_opening[index][0] = func_8001D33C_main(model, node1);
    D_801173C0_opening[index][0] = func_8001D33C_main(model, node2);
    func_8011373C_opening(D_80117388_opening[index].obj);
}

void func_80113AE8_opening(omObjData *obj) {
    Vec oldPos;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 frame = D_8011738C_opening[index][0];
    f32 xAngle = D_801173B0_opening[index][0].pos.x;
    f32 yAngle = D_801173B4_opening[index][0];
    f32 zAngle = D_801173B8_opening[index][0];

    oldPos.x = sindf(xAngle) * 65.0f + D_80117398_opening[index][0].pos.x;
    oldPos.y = (sindf(yAngle) + 1.0f) * 20.0f + D_8011739C_opening[index][0].pos.x;
    oldPos.z = cosdf(zAngle) * 11.0f + D_80117398_opening[index][0].pos.z;
    xAngle = xAngle + 1.45f < 360.0f ? xAngle + 1.45f : xAngle - 360.0f + 1.45f;
    yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
    zAngle = zAngle + 0.8f < 360.0f ? zAngle + 0.8f : zAngle - 360.0f + 0.8f;
    pos.x = D_80117398_opening[index][0].pos.x + sindf(xAngle) * 65.0f;
    pos.y = (sindf(yAngle) + 1.0f) * 20.0f + D_8011739C_opening[index][0].pos.x;
    pos.z = cosdf(zAngle) * 11.0f + D_80117398_opening[index][0].pos.z;
    opModelPosSet(modelId, pos.x, pos.y, pos.z);
    opModelRotSet(modelId, 0, func_80111164_opening(oldPos.x, oldPos.z, pos.x, pos.z), 0);
    frame++;
    frame = frame <= 256 ? frame : 0;
    D_8011738C_opening[index][0] = frame;
    D_801173B0_opening[index][0].pos.x = xAngle + (rand8() & 7) * 0.3f;
    D_801173B4_opening[index][0] = yAngle + (rand8() & 3) * 0.3f;
    D_801173B8_opening[index][0] = zAngle;
}

void func_80113E8C_opening(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    s8 index = obj->work[0];
    s32 modelId = D_80117394_opening[index].modelId;
    s32 frame = D_8011738C_opening[index][0];
    f32 time = 1.0f / D_80117390_opening[index][0];
    f32 xAngle;
    f32 yAngle;
    f32 zAngle;

    time *= D_8011738C_opening[index][0];
    frame++;
    if (time < 1.0f) {
        HuVecCopyXYZ(&start, D_80117398_opening[index][0].pos.x, D_8011739C_opening[index][0].pos.x,
                     D_80117398_opening[index][0].pos.z);
        HuVecCopyXYZ(&end, D_801173A4_opening[index][0], D_801173A8_opening[index][0], D_80117394_opening[index].unk_1C.z);
        xAngle = D_801173B0_opening[index][0].pos.x;
        yAngle = D_801173B4_opening[index][0];
        zAngle = D_801173B8_opening[index][0];
        pos.x = (end.x - start.x) * time + start.x;
        pos.y = (end.y - start.y) * time + start.y;
        pos.z = (end.z - start.z) * time + start.z;
        yAngle = yAngle + 13.99f < 360.0f ? yAngle + 13.99f : yAngle - 360.0f + 13.99f;
        pos.y = (sindf(yAngle) + 1.0f) * 20.0f + pos.y;
        opModelPosSet(modelId, pos.x, pos.y, pos.z);
        opModelRotSet(modelId, 0, func_80111164_opening(pos.x, pos.z, end.x, end.z), 0);
        D_8011738C_opening[index][0] = frame;
        D_801173B0_opening[index][0].pos.x = xAngle;
        D_801173B4_opening[index][0] = yAngle;
        D_801173B8_opening[index][0] = zAngle;
    } else {
        opDemoObjKill(index);
    }
    D_8011738C_opening[index][0] = frame;
}

void func_80114150_opening(s32 index, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;
    OpWork *slot;

    opModelPosGet(D_80117394_opening[index].modelId, &pos.x, &pos.y, &pos.z);
    slot = &D_80117394_opening[index];
    HuVecCopy3F(&slot->pos, &pos);
    HuVecCopyXYZ(&slot->unk_1C, x, y, z);
    D_801173B0_opening[index][0].motion[0] = 0;
    D_801173B4_opening[index][0] = 0;
    D_801173B8_opening[index][0] = 0;
    D_80117388_opening[index].obj->func = func_80113E8C_opening;
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = arg4;
}

void func_80114250_opening(s32 index, s32 modelId, f32 x, f32 y, f32 z) {
    OpObj *slot;

    opDemoObjCreate(index, func_80113AE8_opening);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = 20;
    D_80117394_opening[index].modelId = modelId;
    slot = &D_80117388_opening[index];
    slot->unk_2C.x = slot->unk_2C.y = 0;
    D_801173B0_opening[index][0].pos.x = 0;
    D_801173B0_opening[index][0].pos.x = rand8();
    D_801173B4_opening[index][0] = rand8();
    D_80117398_opening[index][0].pos.x = x;
    D_8011739C_opening[index][0].pos.x = y;
    D_80117398_opening[index][0].pos.z = z;
    func_80113AE8_opening(D_80117388_opening[index].obj);
}

void opWipeDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    if (D_80117388_opening[15].color.a != 0) {
        gSPDisplayList((*gfx)++, D_80114BE8_opening);
        gDPSetRenderMode((*gfx)++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetCombineMode((*gfx)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor((*gfx)++, 0, 0, D_80117388_opening[15].color.r, D_80117388_opening[15].color.g,
                        D_80117388_opening[15].color.b, D_80117388_opening[15].color.a);
        gDPFillRectangle((*gfx)++, 0, 0, 320, 240);
    }
}

void opWipeColorSet(s32 arg0, u8 red, u8 green, u8 blue, u8 alpha) {
    D_80117388_opening[arg0].color.r = red;
    D_80117388_opening[arg0].color.b = blue;
    D_80117388_opening[arg0].color.g = green;
    D_80117388_opening[arg0].color.a = alpha;
}

void opWipeInMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = D_8011738C_opening[index][0];
    s32 totalFrames = D_80117390_opening[index][0];
    u8 red = D_80117388_opening[index].color.r;
    u8 blue = D_80117388_opening[index].color.b;
    u8 green = D_80117388_opening[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 0.0f;
        opWipeKill(index);
    } else {
        alpha = (1.0f / totalFrames) * (totalFrames - frame);
        D_8011738C_opening[index][0]++;
    }
    opWipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void opWipeOutMain(omObjData *obj) {
    s8 index = obj->work[0];
    s32 frame = D_8011738C_opening[index][0];
    s32 totalFrames = D_80117390_opening[index][0];
    u8 red = D_80117388_opening[index].color.r;
    u8 blue = D_80117388_opening[index].color.b;
    u8 green = D_80117388_opening[index].color.g;
    f32 alpha;

    if (frame >= totalFrames) {
        alpha = 1.0f;
    } else {
        alpha = (1.0f / totalFrames) * frame;
        D_8011738C_opening[index][0]++;
    }
    opWipeColorSet(index, red, blue, green, (u8)(alpha * 255.0f));
}

void opWipeKill(s32 index) {
    if (D_80117388_opening[index].obj != NULL) {
        func_8001ACDC_main(D_80117388_opening[index].effectId);
        opDemoObjKill(index);
    }
}

void opWipeInCreate(s32 index, s32 totalFrames) {
    opWipeKill(index);
    opDemoObjCreate(index, opWipeInMain);
    D_80117388_opening[index].effectId = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(index, 0, 0, 0, 255);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = totalFrames;
}

void opWipeOutCreate(s32 index, s32 totalFrames) {
    opWipeKill(index);
    opDemoObjCreate(index, opWipeOutMain);
    D_80117388_opening[index].effectId = func_8001AC8C_main(0, opWipeDraw, 6);
    opWipeColorSet(index, 0, 0, 0, 255);
    D_8011738C_opening[index][0] = 0;
    D_80117390_opening[index][0] = totalFrames;
}

void opWipeWhiteInCreate(s32 index, s32 totalFrames) {
    opWipeInCreate(index, totalFrames);
    opWipeColorSet(index, 255, 255, 255, 255);
}

void opWipeWhiteOutCreate(s32 index, s32 totalFrames) {
    opWipeOutCreate(index, totalFrames);
    opWipeColorSet(index, 255, 255, 255, 255);
}

void func_801149A4_opening(s32 character) {
    if (D_800D20B8_main[character][2] != 0xFF) {
        func_80033354_main(D_800D20B8_main[character][2]);
        func_80033354_main(D_800D5570_main[character][2]);
        D_800D20B8_main[character][2] = 0xFF;
    }
}

void opSleep(s32 frames) {
    HuPrcSleep(frames);
}

void opContErrorCreate(void) {
    if (GWContErrorGet() == 0) {
        D_80117750_opening.animId = func_8000B838_main(0x100005);
        D_80117750_opening.espriteSlot = InitEspriteSlot(D_80117750_opening.animId, 0, 1);
        func_8000BBD4_main(D_80117750_opening.espriteSlot, 0xA0, 0xA8);
        func_8000BCC8_main(D_80117750_opening.espriteSlot, 0);
        func_8000BB94_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorDispOn(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB54_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorDispOff(void) {
    if (GWContErrorGet() == 0) {
        func_8000BB94_main(D_80117750_opening.espriteSlot);
    }
}

void opContErrorKill(void) {
    if (GWContErrorGet() == 0) {
        func_8000C184_main(D_80117750_opening.espriteSlot);
        HuSprKill(D_80117750_opening.animId);
    }
}
