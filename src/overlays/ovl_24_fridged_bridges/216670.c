#include "common.h"
#include "overlays/ovl_24.h"

extern s32 D_8010D35C_fridged_bridges;
extern s32 D_8010D360_fridged_bridges;
extern s16 D_8010DA60_fridged_bridges;
extern s16 D_8010DA68_fridged_bridges;
extern omObjData **D_8010DA64_fridged_bridges;
extern omObjData *D_8010DA70_fridged_bridges;

void func_80105F34_fridged_bridges(omObjData *arg0);
void func_80108FBC_fridged_bridges(omObjData *arg0);
omObjData **omGetGroupMemberList(s16 arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801059A0_fridged_bridges);

void func_80105F00_fridged_bridges(omObjData *arg0) {
    D_8010D360_fridged_bridges = 0;
    D_8010D35C_fridged_bridges = 0;
    D_8010DA68_fridged_bridges = 0;
    D_8010DA60_fridged_bridges = -1;
    arg0->func = func_80105F34_fridged_bridges;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80105F34_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D268_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D27C_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D290_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D2A4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801061C4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801062F8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010641C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80106438_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80106454_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80106470_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010648C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801068F4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107164_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010733C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107510_fridged_bridges);

void func_801075A4_fridged_bridges(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801075AC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010775C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80107870_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D2D8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801079CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108050_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801082D0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801084E0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108648_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108720_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108B08_fridged_bridges);

void func_80108BEC_fridged_bridges(omObjData *arg0) {
    omObjData **bridgeObjs = omGetGroupMemberList(1);
    s32 deletedCount = 0;
    s32 i;

    for (i = 0; i < 12; i++) {
        deletedCount += bridgeObjs[i] == NULL;
    }

    if (deletedCount == 12) {
        arg0->work[0] = 1;
        arg0->func = func_80108FBC_fridged_bridges;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108C60_fridged_bridges);

// Shrinking phase of a player's bridge-sink object (created with func_80108C60).
// Sinks the player model 10 units per frame while scaling it away; when the
// scale runs out, stops the animation and deletes the object.
void func_80108EBC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR((omObjData *)arg0->work[0], FridgedBridgesPlayer);
    s16 playerId = player->playerId;
    u16 modelId = D_8010DA70_fridged_bridges->model[playerId * 5];
    f32 *scale;

    arg0->trans.y -= 10.0f;
    Hu3DModelPosSet(modelId, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    scale = (f32 *)&arg0->work[2];
    *scale -= 0.04f;
    if (*scale <= 0.0f) {
        func_8001C258_main(modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        omDelObj(arg0);
    } else {
        Hu3DModelScaleSet(modelId, *scale, *scale, *scale);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108FBC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109154_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801091F8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109390_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109988_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D4C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D6C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109F84_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A0F4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A1A4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A360_fridged_bridges);

// True once every player has left the frozen (state 2) pose.
s32 func_8010ADC0_fridged_bridges(void) {
    s32 notFrozenCount = 0;
    s32 i = 0;
    omObjData **playerObjs = D_8010DA64_fridged_bridges;

    for (; i < 4; i++) {
        notFrozenCount += OM_GET_DATA_PTR(playerObjs[i], FridgedBridgesPlayer)->state != 2;
    }
    return notFrozenCount == 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE0C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE98_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B164_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B3EC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B7CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B8CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010BB18_fridged_bridges);
