#include "common.h"
#include "mallocblock.h"
#include "overlays/ovl_24.h"

// Small object that keeps a player's camera center glued to that player's object.
typedef struct FridgedBridgesCameraTarget {
    /* 0x00 */ u16 playerId;
    /* 0x04 */ omObjData *playerObj;
} FridgedBridgesCameraTarget; // sizeof 0x8

extern s16 D_8010DA48_fridged_bridges[0xC];

void func_8010BE88_fridged_bridges(omObjData *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010BDF0_fridged_bridges);

void func_8010BE0C_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR(arg0, FridgedBridgesPlayer);
    omObjData *obj = omAddObj(0x32, 0, 0, -1, func_8010BE88_fridged_bridges);
    FridgedBridgesCameraTarget *target;

    player->unk_2C = obj;
    target = HuMemAllocTag(sizeof(FridgedBridgesCameraTarget), TAG_OVERLAY);
    obj->data = target;
    target->playerId = player->playerId;
    target->playerObj = arg0;
    obj->work[0] = 0;
}

void func_8010BE88_fridged_bridges(omObjData *arg0) {
    FridgedBridgesCameraTarget *target = arg0->data;

    if (arg0->work[0] != 0) {
        CenterM[target->playerId].x = target->playerObj->trans.x;
        CenterM[target->playerId].z = target->playerObj->trans.z;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010BEE8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010BFD0_fridged_bridges);

void func_8010C178_fridged_bridges(omObjData *arg0) {
    if (--arg0->work[0] == 0) {
        func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_8010DA48_fridged_bridges[arg0->work[1]] = 0;
        omDelObj(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C1D8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C46C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010C738_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/21CAC0", func_8010CDE4_fridged_bridges);
