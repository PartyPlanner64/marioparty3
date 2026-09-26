#include "common.h"
#include "../ovl_80_shared_board/FA250.h"

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 motionId;
    /* 0x04 */ s32 posX;
    /* 0x08 */ s32 posY;
    /* 0x0C */ s32 posZ;
    /* 0x10 */ f32 scaleX;
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ f32 scaleZ;
    /* 0x1C */ f32 rotX;
    /* 0x20 */ f32 rotY;
    /* 0x24 */ f32 rotZ;
    /* 0x28 */ s32 unk_28;
} OpModel;

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ char unk_04[0x38];
} OpObj; // sizeof 0x3C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OpSpr; // sizeof 0x1C

void func_801061F0_opening(void);
void func_80110B90_opening(void);
void func_80110F48_opening(void);
void func_80112944_opening(void);
void opContErrorCreate(void);

extern Vec D_80114BB8_opening;
extern Vec D_80114BC4_opening;
extern RectF D_80114BD0_opening;
extern OpModel D_80115630_opening[0xA0];
extern omObjData *D_80117374_opening;
extern OpObj D_80117388_opening[0x10];
extern s16 D_801171B0_opening;
extern u16 D_801171B2_opening;
extern OpSpr D_80114EB0_opening[0x40];
INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opObjectInit);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleObjectSetup);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80105C2C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjectSetup);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opEventInit);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEventCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80105F68_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opBtnStartCheck);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEndReset);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEndSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEndGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801061F0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8010621C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opAnimIdGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opEspIdGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opAnimCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opAnimKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opEspCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opEspKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprBGCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprKillAll);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprBGDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprBGDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprPosSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprPosGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprScaleSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprAlphaSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprAttrSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSprAttrReset);

void func_80106734_opening(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_80114EB0_opening[arg0].espriteSlot, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80106768_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801067D4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelKillAll);

s16 opModelIdGet(s32 modelId) {
    return D_80115630_opening[modelId].modelId;
}

s16 opMotionIdGet(s32 motionId) {
    return D_80115630_opening[motionId].motionId;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelRotSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelPosSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelScaleSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelPosGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelRotGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelScaleGet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opModelDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionFlagSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionShiftSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80106DD0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionSpeedSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionTimeSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionEndWait);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionEndCheck);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opMotionSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107048_opening);

void func_801070AC_opening(void) {
    func_8000C184_main(D_801171B2_opening);
    HuSprKill(D_801171B0_opening);
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801070D8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107140_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8010738C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801074D8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107640_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801077E8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801078B4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107980_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107A4C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107A90_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107B74_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107BD8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107C08_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107C70_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107CA0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107CD0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107D9C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107DD8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107E10_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107E2C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107E80_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107EBC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80107EF4_opening);

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

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80108118_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114CE4_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D84_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D90_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114D9C_opening);

INCLUDE_RODATA("asm/nonmatchings/overlays/opening/524000", D_80114DA8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEvent);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoEventKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110B90_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110B9C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110C04_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110D8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoCharCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoShadowCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoModelKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoSprKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110F48_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80110FB0_opening);

void func_80111028_opening(void) {
    if (D_80117374_opening != NULL) {
        omDelObj(D_80117374_opening);
    }
    D_80117374_opening = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011105C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111090_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801110AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801110F0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111164_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801111AC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011124C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111490_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111580_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801117D4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111984_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111B34_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111C08_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111C30_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111C88_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111DDC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80111F58_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80112120_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleSetup);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleSprMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleKill);

void func_80112944_opening(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_80117388_opening[i].obj = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjKillAll);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80112A74_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80112BA0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80112C8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80112D30_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoOutEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoOutEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoGuideInEffMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoGuideInEffCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoStarWaitMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoStarWaitCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801134FC_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011361C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_8011373C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801139B0_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80113AE8_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80113E8C_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80114150_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_80114250_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeDraw);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeColorSet);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeInMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeOutMain);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeKill);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeInCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeOutCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeWhiteInCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opWipeWhiteOutCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", func_801149A4_opening);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opSleep);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opContErrorCreate);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opContErrorDispOn);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opContErrorDispOff);

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opContErrorKill);
