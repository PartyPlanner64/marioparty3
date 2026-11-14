#include "common.h"
#include "game/pad.h"
#include "math.h"
#include "overlays/minigame.h"

typedef struct AceHighPlayer {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 camIdx;
    /* 0x04 */ omObjData *camObj;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ Vec dir;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ char unk_22[2];
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ u16 espriteSlots[2];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ u16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u16 unk_50;
    /* 0x52 */ u16 unk_52;
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ char unk_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ omObjData *unk_6C;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ char unk_72[2];
    /* 0x74 */ omObjData *unk_74;
    /* 0x78 */ omObjData *unk_78;
    /* 0x7C */ f32 unk_7C;
    /* 0x80 */ f32 unk_80;
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ u16 unk_88;
    /* 0x8A */ char unk_8A[2];
    /* 0x8C */ f32 unk_8C;
    /* 0x90 */ u16 unk_90;
    /* 0x92 */ u16 unk_92;
    /* 0x94 */ s16 unk_94;
    /* 0x96 */ char unk_96[2];
    /* 0x98 */ omObjData *unk_98;
    /* 0x9C */ Vec unk_9C;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ u16 unk_AC;
    /* 0xAE */ u16 unk_AE;
    /* 0xB0 */ u16 unk_B0;
    /* 0xB2 */ char unk_B2[0xE];
} AceHighPlayer; // sizeof 0xC0

typedef struct AceHighShot {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 radius;
    /* 0x10 */ Vec dir;
    /* 0x1C */ omObjData *owner;
    /* 0x20 */ s16 effectIdx;
    /* 0x22 */ s16 effectModel;
    /* 0x24 */ u16 timer;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ omObjData *target;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
} AceHighShot; // sizeof 0x38

extern u8 D_800D6A90_main;
extern D_80111B50_vine_with_me_Struct D_8010DB40_aces_high;
extern u16 D_8010DB68_aces_high[4];
extern f32 D_8010DB70_aces_high[4][4];
extern f32 D_8010DBB0_aces_high[4][4];
extern Vec D_8010DBF0_aces_high[2];
extern u16 D_8010DC08_aces_high;
extern f32 D_8010DC0C_aces_high;
extern s32 D_8010DC10_aces_high[];
extern s32 D_8010DC30_aces_high[];
extern s16 D_8010DC50_aces_high[4][2][2];
extern s16 D_8010DC70_aces_high[4][2];
extern f32 D_8010DC80_aces_high[];
extern s32 D_8010DC90_aces_high[];
extern u16 D_8010DCB0_aces_high;
extern u16 D_8010DCB2_aces_high;
extern Vec2f D_8010DCB4_aces_high;
extern Vec2f D_8010DCBC_aces_high[4];
extern u16 D_8010DE50_aces_high[2];
extern f32 D_8010DE54_aces_high[2];
extern omObjData *D_8010DE5C_aces_high;
extern omObjData *D_8010DE60_aces_high;
extern omObjData *D_8010DE64_aces_high;
extern omObjData **D_8010DE68_aces_high;
extern omObjData *D_8010DE6C_aces_high;
extern omObjData **D_8010DE70_aces_high[4];
extern omObjData *D_8010DE80_aces_high;
extern omObjData *D_8010DE84_aces_high;
extern u16 D_8010DE88_aces_high;
extern u16 D_8010DE8A_aces_high;
extern s16 D_8010DE8C_aces_high;
extern s16 D_8010DE8E_aces_high;
extern s16 D_8010DE90_aces_high;
extern s16 D_8010DE92_aces_high;
extern s16 D_8010DE94_aces_high;
extern s16 D_8010DE96_aces_high;
extern Vec D_8010DE98_aces_high;
extern s16 D_8010DEA4_aces_high;
extern s16 D_8010DEA6_aces_high;
extern Vec D_8010DEA8_aces_high;
extern Vec D_8010DEB4_aces_high;
extern Vec D_8010DEC0_aces_high;
extern u16 D_8010DED0_aces_high[20];
extern u16 D_8010DEF8_aces_high[20];
extern s16 D_8010DF20_aces_high;

void func_80105E44_aces_high(omObjData *object);
void func_80105E84_aces_high(omObjData *object);
void func_80105FC8_aces_high(omObjData *object);
void func_801061E0_aces_high(omObjData *object);
void func_801062DC_aces_high(omObjData *object);
void func_80106EC0_aces_high(omObjData *object);
void func_801071D4_aces_high(omObjData *object);
void func_80107654_aces_high(omObjData *object);
void func_80107F98_aces_high(omObjData *object);
void func_801081A8_aces_high(omObjData *object);
void func_8010843C_aces_high(omObjData *object);
void func_801085B0_aces_high(void);
void func_8010862C_aces_high(omObjData *object);
void func_801088A4_aces_high(omObjData *object, s8 *stickX, s8 *stickY, u16 *btnDown, u16 *btn);
u16 func_8010951C_aces_high(omObjData *object, Vec *target, f32 angleTol, f32 heightTol, s8 *stickX, s8 *stickY);
void func_80109928_aces_high(omObjData *object);
s16 func_80109EEC_aces_high(omObjData *object, f32 fov, omObjData **list, omObjData **nearest, f32 *minDist);
f32 func_8010A0F0_aces_high(omObjData *object);
void func_8010A214_aces_high(omObjData *object);
void func_8010A51C_aces_high(omObjData *object);
void func_8010A884_aces_high(omObjData *object);
void func_8010A9D4_aces_high(omObjData *object);
void func_8010AADC_aces_high(omObjData *object);
void func_8010ACE0_aces_high(omObjData *object);
void func_8010AD4C_aces_high(omObjData *object);
void func_8010AE30_aces_high(omObjData *object);
void func_8010B0E8_aces_high(omObjData *object);
void func_8010B224_aces_high(omObjData *object);
void func_8010B26C_aces_high(omObjData *object);
void func_8010B4BC_aces_high(omObjData *object);
void func_8010B618_aces_high(void);
void func_8010B760_aces_high(omObjData *object);
void func_8010B9F4_aces_high(omObjData *object);
void func_8010BCC4_aces_high(void);
void func_8010BD84_aces_high(omObjData *object);
void func_8010BF3C_aces_high(omObjData *object);
void func_8010C288_aces_high(omObjData *object);
void func_8010C9DC_aces_high(void);
void func_8010CA6C_aces_high(omObjData *object);
void func_8010CD88_aces_high(omObjData *object);
void func_8010CE5C_aces_high(omObjData *object);
void func_8010CFF8_aces_high(void);
u16 func_8010D1D8_aces_high(u16 winner);
void func_8010D6D4_aces_high(omObjData *object);
void func_8010D994_aces_high(omObjData *object);
void func_8010DB20_aces_high(void);

void func_801059A0_aces_high(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(80, 0);
    func_8004A208_main();
    func_8000B690_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        CZoomM[i] = 1500.0f;
        CRotM[i].x = -5.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 0.0f;
        CenterM[i].z = 0.0f;
        Hu3DCameraPerspectiveSet(i, 90.0f, 80.0f, 14000.0f);
        ScissorSet(i, D_8010DB70_aces_high[i][0], D_8010DB70_aces_high[i][1], D_8010DB70_aces_high[i][2],
                   D_8010DB70_aces_high[i][3]);
        ViewportSet(i, D_8010DBB0_aces_high[i][0], D_8010DBB0_aces_high[i][1], 511.0f, D_8010DBB0_aces_high[i][2],
                    D_8010DBB0_aces_high[i][3], 511.0f);
    }
    D_8010DE84_aces_high = obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010DE98_aces_high.x = D_8010DBF0_aces_high[0].x;
    D_8010DE98_aces_high.y = D_8010DBF0_aces_high[0].y;
    D_8010DE98_aces_high.z = D_8010DBF0_aces_high[0].z;
    Hu3DBGColorSet((u8)D_8010DE98_aces_high.x, (u8)D_8010DE98_aces_high.y, (u8)D_8010DE98_aces_high.z);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105E44_aces_high);
    D_8010DE64_aces_high = omAddObj(10, 4, 0, -1, func_80105FC8_aces_high);
    omSetStatBit(D_8010DE64_aces_high, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(D_8010DE64_aces_high, OM_STAT_MODELPAUSE);
    func_800E5EA0_minigame(&D_8010DB40_aces_high);
    D_800EB930_minigame = 50;
    D_800EB932_minigame = 10;
    omMakeGroup(0, 4);
    D_8010DE68_aces_high = omGetGroupMemberList(0);
    for (i = 0; i < 4; i++) {
        omAddObj(20, 7, 0, 0, func_801062DC_aces_high)->work[0] = i;
    }
    func_8010C9DC_aces_high();
    func_8010B618_aces_high();
    D_8010DEA4_aces_high = func_8000B838_main(0x380027);
    D_8010DEA6_aces_high = func_8000B838_main(0x380028);
}

void func_80105E44_aces_high(omObjData *object) {
    D_8010DE60_aces_high = NULL;
    D_8010DE5C_aces_high = NULL;
    D_8010DE8C_aces_high = 4;
    D_8010DE8E_aces_high = -1;
    D_8010DE90_aces_high = 0;
    object->func = func_80105E84_aces_high;
}

void func_80105E84_aces_high(omObjData *object) {
    if (D_8010DC08_aces_high == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010DE5C_aces_high == NULL) {
                    D_8010DE88_aces_high = 0;
                    D_8010DE5C_aces_high = omAddObj(4, 0, 0, -1, func_8010CD88_aces_high);
                }
                break;
            case 1:
                break;
            case 2:
                if (D_8010DE8C_aces_high < 2) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (D_8010DE60_aces_high == NULL) {
                    D_8010DE8A_aces_high = 0;
                    D_8010DE60_aces_high = omAddObj(4, 0, 0, -1, func_8010CE5C_aces_high);
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudFXStop(D_8010DE96_aces_high);
                HuAudSeqFadeOut(30);
                func_8004AB0C_main(30);
                D_8010DC08_aces_high = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010DB20_aces_high();
    }
}

void func_80105FC8_aces_high(omObjData *object) {
    u16 sprite;

    object->model[0] = func_8000B108_main(0x38000A, 0x6D9);
    Hu3DModelPosSet(object->model[0], 0.0f, -1000.0f, 0.0f);
    object->model[1] = func_8000B108_main(0x380025, 0x699);
    Hu3DModelPosSet(object->model[1], 0.0f, 900.0f, -8000.0f);
    object->model[2] = func_8000B108_main(0x380026, 0x699);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 8000.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 180.0f, 0.0f);
    object->model[3] = func_8000B108_main(0x38000B, 0x6C9);
    Hu3DModelPosSet(object->model[3], 0.0f, -1000.0f, 0.0f);
    Hu3DData[object->model[3]].hmf->unk84->unk0[2] = 0;
    Hu3DModelRemakeStatic(object->model[3]);
    func_8001C514_main(object->model[3]);
    D_8010DE92_aces_high = sprite = espEntry(func_8000B838_main(0x38001E), 0, 0);
    espPosSet(sprite, 160, 120);
    espPriSet(sprite, 0x8096);
    D_8010DE94_aces_high = sprite = espEntry(func_8000B838_main(0x38001F), 0, 0);
    espPosSet(sprite, 160, 120);
    espPriSet(sprite, 0x8096);
    D_8010DE54_aces_high[0] = D_8010DE54_aces_high[1] = 0.0f;
    func_800335BC_main("m223_03kaze_IA88", D_8010DE50_aces_high);
    func_8001C954_main(object->model[3]);
    object->func = func_801061E0_aces_high;
}

void func_801061E0_aces_high(omObjData *object) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010DE54_aces_high[1] += 2.0f;
        D_8010DC0C_aces_high -= 0.0f;
        if (D_8010DC0C_aces_high < 0.0f) {
            D_8010DC0C_aces_high += 360.0f;
        }
    }
    func_8001E888_main(object->model[3], D_8010DE54_aces_high[0], D_8010DE54_aces_high[1], D_8010DE50_aces_high[0],
                       D_8010DE50_aces_high[1], "m223_4-cyl11", 0);
    Hu3DModelRotSet(object->model[3], 0.0f, D_8010DC0C_aces_high, 0.0f);
}

const char D_8010DD1C_aces_high[] = "";

void func_801062DC_aces_high(omObjData *object) {
    AceHighPlayer *player;
    u16 idx;
    s8 chr;
    s16 spr;
    s16 i;
    u16 sprite;

    idx = object->work[0];
    player = object->data = HuMemAllocTag(sizeof(AceHighPlayer), 0x7918);
    player->camIdx = idx;
    chr = GwPlayer[idx].chr;
    object->model[0] = func_8000B108_main(D_8010DC10_aces_high[chr], 0x6B9);
    if (idx == 0) {
        object->model[1] = func_8000B108_main(0x380008, 0x6D9);
        object->model[2] = func_8000B108_main(0x380009, 0x6D9);
        object->model[3] = func_8000B108_main(0x380021, 0x6D9);
        object->model[4] = func_8000B108_main(0x380022, 0x6D9);
        object->model[5] = func_8000B108_main(0x380023, 0x6D9);
        object->model[6] = func_8000B108_main(0x380024, 0x6D9);
    } else {
        object->model[1] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[1]);
        object->model[2] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[2]);
        object->model[3] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[3]);
        object->model[4] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[4]);
        object->model[5] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[5]);
        object->model[6] = Hu3DModelLink(D_8010DE68_aces_high[0]->model[6]);
    }
    func_8001C258_main(object->model[3], 4, 4);
    func_8001C2FC_main(object->model[3], 0x70000000, 0x70000000);
    func_8001C258_main(object->model[2], 4, 4);
    func_8001C814_main(object->model[4], 3, 2);
    func_8001C814_main(object->model[5], 3, 2);
    func_8001C814_main(object->model[6], 3, 2);
    func_8001C258_main(object->model[4], 4, 4);
    func_8001C258_main(object->model[6], 4, 4);
    omSetTra(object, sindf(D_8010DC80_aces_high[idx]) * 1150.0f, -250.0f, cosdf(D_8010DC80_aces_high[idx]) * 1150.0f);
    omSetRot(object, 0.0f, atan2df(-object->trans.x, -object->trans.z), 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    spr = func_8000B838_main(D_8010DC30_aces_high[chr]);
    player->unk_1C = espEntry(spr, 0, 0);
    player->unk_1E = espEntry(spr, 0, 0);
    espDispOff(player->unk_1E);
    spr = func_8000B838_main(0x38001D);
    for (i = 0; i < 2; i++) {
        player->espriteSlots[i] = espEntry(spr, 0, 0);
        espPosSet(player->espriteSlots[i], D_8010DC50_aces_high[idx][i][0], D_8010DC50_aces_high[idx][i][1]);
    }
    player->unk_2E = sprite = espEntry(D_8010DEA4_aces_high, 0, 0);
    espPriSet(sprite, 0x80C8);
    espDispOff(sprite);
    player->unk_30 = sprite = espEntry(D_8010DEA6_aces_high, 0, 0);
    espPriSet(sprite, 0x80C8);
    espPosSet(sprite, D_8010DC70_aces_high[idx][0], D_8010DC70_aces_high[idx][1]);
    espDispOff(sprite);
    player->unk_0C = 0;
    player->unk_3C = 0.0f;
    player->unk_38 = 0.0f;
    player->unk_40 = 0.0f;
    player->unk_32 = 0;
    player->unk_34 = 0;
    player->unk_20 = 0;
    player->unk_24 = 4;
    player->unk_00 = 0;
    player->unk_26 = 2;
    player->unk_2C = -1;
    player->unk_36 = 0;
    player->unk_52 = 0;
    player->unk_54 = 1;
    player->unk_56 = 1;
    player->unk_58 = 0;
    player->unk_4C = 1;
    player->unk_6C = NULL;
    player->unk_5C = 0.0f;
    player->unk_60 = 0.0f;
    player->unk_68 = 0.0f;
    player->unk_64 = 0.0f;
    player->unk_08 = 27.777777f;
    player->dir.x = sindf(object->rot.y);
    player->dir.y = 0.0f;
    player->dir.z = cosdf(object->rot.y);
    player->unk_88 = 0;
    player->unk_44 = 0.0f;
    player->unk_90 = 1;
    player->unk_8C = object->rot.y;
    player->unk_94 = 0;
    player->unk_92 = 0;
    player->unk_AE = 0;
    player->unk_70 = 0;
    player->unk_74 = omAddObj(60, 0, 0, -1, func_8010D6D4_aces_high);
    player->unk_74->work[2] = 0;
    player->unk_74->work[3] = (u32)object;
    player->unk_78 = omAddObj(60, 0, 0, -1, func_8010D994_aces_high);
    player->unk_78->work[0] = (u32)object;
    player->unk_78->work[1] = 0;
    player->unk_78->scale.x = 0.0f;
    object->work[0] = 30;
    player->camObj = omAddObj(50, 0, 0, -1, func_8010A9D4_aces_high);
    player->camObj->work[0] = 1;
    player->camObj->work[1] = (u32)object;
    object->func = func_80106EC0_aces_high;
}

void func_801068F4_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;

    func_80088910_main(Hu3DData[object->model[0]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
    omSetRot(object, 0.0f, object->rot.y, 0.0f);
    if (player->unk_90 == 0) {
        func_8001C258_main(object->model[0], 4, 4);
    } else {
        func_8001C258_main(object->model[0], 4, 0);
    }
    if (player->unk_56 == 1) {
        Hu3DModelPosSet(object->model[1], object->trans.x + player->unk_60, object->trans.y + player->unk_68,
                        object->trans.z + player->unk_64);
        func_80088910_main(Hu3DData[object->model[1]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(object->model[1], 0.0f, object->rot.y, 0.0f);
        Hu3DModelPosSet(object->model[2], object->trans.x + player->unk_60, object->trans.y + player->unk_68,
                        object->trans.z + player->unk_64);
        func_80088910_main(Hu3DData[object->model[2]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(object->model[2], 0.0f, object->rot.y, 0.0f);
        if (player->unk_58 == 0) {
            func_8001C258_main(object->model[2], 4, 4);
            func_8001C258_main(object->model[1], 4, 0);
        } else {
            func_8001C258_main(object->model[1], 4, 4);
            func_8001C258_main(object->model[2], 4, 0);
        }
        if (player->unk_90 == 0) {
            func_8001C258_main(object->model[1], 4, 4);
            func_8001C258_main(object->model[2], 4, 4);
        }
    }
}

void func_80106B70_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    s16 model;

    switch (player->unk_4C) {
        case 0:
            model = object->model[4];
            func_8001C258_main(object->model[5], 4, 4);
            func_8001C258_main(object->model[6], 4, 4);
            break;
        case 1:
            model = object->model[5];
            func_8001C258_main(object->model[4], 4, 4);
            func_8001C258_main(object->model[6], 4, 4);
            break;
        case 2:
            model = object->model[6];
            func_8001C258_main(object->model[4], 4, 4);
            func_8001C258_main(object->model[5], 4, 4);
            break;
        case 3:
            model = -1;
            func_8001C258_main(object->model[4], 4, 4);
            func_8001C258_main(object->model[5], 4, 4);
            func_8001C258_main(object->model[6], 4, 4);
            break;
    }
    if (model >= 0) {
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, object->trans.x, object->trans.y, object->trans.z);
        func_80088910_main(Hu3DData[model].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(model, 0.0f, object->rot.y, 0.0f);
    }
    if (player->unk_90 == 0) {
        func_8001C258_main(object->model[4], 4, 4);
        func_8001C258_main(object->model[5], 4, 4);
        func_8001C258_main(object->model[6], 4, 4);
    }
}

void func_80106D2C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;

    if (D_800CDA7C_main[0] & L_JPAD) {
        object->rot.y -= 2.0f;
    }
    if (D_800CDA7C_main[0] & R_JPAD) {
        object->rot.y += 2.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (D_800CDA7C_main[0] & U_JPAD) {
        player->unk_38 += 2.0f;
    }
    if (D_800CDA7C_main[0] & D_JPAD) {
        player->unk_38 -= 2.0f;
    }
    if (D_800CDA7C_main[0] & L_CBUTTONS) {
        player->unk_3C -= 2.0f;
    }
    if (D_800CDA7C_main[0] & R_CBUTTONS) {
        player->unk_3C += 2.0f;
    }
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
}

void func_80106EC0_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;

    if (object->work[0] != 0) {
        object->work[0]--;
    } else {
        switch (player->unk_88) {
            case 0:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= -90.0f) {
                    player->unk_38 += 180.0f;
                    player->unk_3C += 180.0f;
                    object->rot.y += 180.0f;
                    player->unk_88 = 1;
                }
                break;
            case 1:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= 0.0f) {
                    player->unk_88 = 2;
                }
                break;
            case 2:
                player->unk_38 += 4.0f;
                player->unk_3C -= 8.0f;
                if (player->unk_38 >= 90.0f) {
                    player->unk_38 = 90.0f;
                    player->unk_3C = 0.0f;
                    player->unk_88 = 3;
                }
                break;
            case 3:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= 0.0f) {
                    player->unk_38 = 0.0f;
                    object->work[1] = 30;
                    player->camObj->func = func_8010AADC_aces_high;
                    player->camObj->work[2] = 0;
                    player->camObj->scale.x = CRotM[player->camIdx].x;
                    player->unk_88 = 4;
                    if (player->camIdx == 3) {
                        func_800E6F0C_minigame(1);
                    }
                }
                break;
            case 4:
                if (--object->work[1] == 0) {
                    player->camObj->func = func_8010A51C_aces_high;
                    object->func = func_80107654_aces_high;
                }
                break;
        }
    }
    player->dir.y = -sindf(player->unk_38) * cosdf(player->unk_3C);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
}

void func_801071D4_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    s8 stickX;
    s8 stickY;
    u16 btnDown;
    u16 btn;
    f32 target;
    f32 speed;

    func_801088A4_aces_high(object, &stickX, &stickY, &btnDown, &btn);
    btn = 0;
    btnDown = 0;
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = stickY / 70.0f * 30.0f;
    if (target < player->unk_38) {
        if (target - player->unk_38 < -10.0f) {
            player->unk_38 -= 10.0f;
            player->unk_7C = -10.0f;
        } else {
            player->unk_38 = target;
            player->unk_7C = target;
        }
    } else if (target - player->unk_38 > 10.0f) {
        player->unk_38 += 10.0f;
        player->unk_7C = 10.0f;
    } else {
        player->unk_38 = target;
        player->unk_7C = target;
    }
    target = stickX / 70.0f * 60.0f;
    if (target < player->unk_3C) {
        if (target - player->unk_3C < -10.0f) {
            player->unk_3C -= 10.0f;
            player->unk_80 = -10.0f;
        } else {
            player->unk_3C = target;
            player->unk_80 = target;
        }
    } else if (target - player->unk_3C > 10.0f) {
        player->unk_3C += 10.0f;
        player->unk_80 = 10.0f;
    } else {
        player->unk_3C = target;
        player->unk_80 = target;
    }
    player->unk_84 = player->unk_80 / 30.0f;
    if (btn & 0x4000) {
        speed = 16.666666f;
        player->unk_4C = 0;
    } else if (btn & 0x8000) {
        speed = 41.666664f;
        player->unk_4C = 2;
    } else {
        speed = 27.777777f;
        player->unk_4C = 1;
    }
    if (player->unk_0C == 1) {
        speed *= 2.0f;
    }
    if (speed < player->unk_08) {
        player->unk_08 -= 2.0f;
        if (player->unk_08 < speed) {
            player->unk_08 = speed;
        }
    } else if (player->unk_08 < speed) {
        player->unk_08 += 2.0f;
        if (speed < player->unk_08) {
            player->unk_08 = speed;
        }
    }
    if (stickX == 0) {
        player->unk_32 = 0;
    } else if (stickX < 0) {
        player->unk_32 = 1;
    } else {
        player->unk_32 = 2;
    }
    object->rot.y -= player->unk_3C / 30.0f;
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    func_8010862C_aces_high(object);
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
}

void func_80107654_aces_high(omObjData *object) {
    f32 shake[4] = { 10.0f, 0.0f, -10.0f, 0.0f };
    AceHighPlayer *player = object->data;
    u32 hit;
    s16 mode;
    s8 stickX;
    s8 stickY;
    u16 btnDown;
    u16 btn;
    f32 target;
    f32 speed;
    s8 pad;
    s32 com;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        func_8004AC5C_main(0x3AF, player->camIdx);
        espDispOff(player->espriteSlots[--player->unk_26]);
        if (player->unk_26 == 0) {
            player->unk_00 = 4;
            player->unk_4E = 45;
            player->unk_4C = 3;
            player->unk_58 = 0;
            func_8010A884_aces_high(object);
            func_8001C258_main(object->model[3], 4, 0);
            func_8001C814_main(object->model[3], 3, 2);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, object->trans.z);
            D_8010DE8C_aces_high--;
            player->unk_98 = NULL;
            HuAudFXPlay(0x3B0);
            object->func = func_801081A8_aces_high;
            omVibrate(player->camIdx, 30, 0, 30);
            PlayerFXPlay(0x286, player->camIdx);
            return;
        }
        player->unk_00 = 3;
        player->unk_50 = 30;
        omVibrate(player->camIdx, 20, 0, 20);
        PlayerFXPlay(0x2AB, player->camIdx);
    }
    if (hit & 2) {
        player->unk_56 = 1;
        player->unk_5C = 50.0f;
        func_8001C258_main(object->model[1], 4, 0);
    }
    if (hit & 4) {
        player->unk_74->work[0] = 45;
        player->unk_74->work[1] = 6;
        player->unk_74->work[2] = 1;
    }
    func_8010843C_aces_high(object);
    mode = func_800E6E8C_minigame();
    if (mode == 2 || mode == 3 || func_800E6E8C_minigame() == 4) {
        com = GwPlayer[player->camIdx].stat & 1;
        if (com || mode == 3 || mode == 4) {
            func_801088A4_aces_high(object, &stickX, &stickY, &btnDown, &btn);
            if (mode == 3 || mode == 4) {
                btn = 0;
                btnDown = 0;
            }
        } else {
            pad = GwPlayer[player->camIdx].pad;
            stickX = D_800CBB6E_main[pad];
            stickY = D_800D20A1_main[pad];
            btnDown = D_800D5558_main[pad];
            btn = D_800CDA7C_main[pad];
        }
    } else {
        btn = 0;
        btnDown = 0;
        stickY = 0;
        stickX = 0;
    }
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = stickY / 70.0f * 30.0f;
    if (target < player->unk_38) {
        if (target - player->unk_38 < -10.0f) {
            player->unk_38 -= 10.0f;
            player->unk_7C = -10.0f;
        } else {
            player->unk_38 = target;
            player->unk_7C = target;
        }
    } else if (target - player->unk_38 > 10.0f) {
        player->unk_38 += 10.0f;
        player->unk_7C = 10.0f;
    } else {
        player->unk_38 = target;
        player->unk_7C = target;
    }
    target = stickX / 70.0f * 60.0f;
    if (target < player->unk_3C) {
        if (target - player->unk_3C < -10.0f) {
            player->unk_3C -= 10.0f;
            player->unk_80 = -10.0f;
        } else {
            player->unk_3C = target;
            player->unk_80 = target;
        }
    } else if (target - player->unk_3C > 10.0f) {
        player->unk_3C += 10.0f;
        player->unk_80 = 10.0f;
    } else {
        player->unk_3C = target;
        player->unk_80 = target;
    }
    player->unk_84 = player->unk_80 / 30.0f;
    if (btn & 0x4000) {
        speed = 16.666666f;
        player->unk_4C = 0;
    } else if (btn & 0x8000) {
        speed = 41.666664f;
        player->unk_4C = 2;
    } else {
        speed = 27.777777f;
        player->unk_4C = 1;
    }
    if (speed < player->unk_08) {
        player->unk_08 -= 2.0f;
        if (player->unk_08 < speed) {
            player->unk_08 = speed;
        }
    } else if (player->unk_08 < speed) {
        player->unk_08 += 2.0f;
        if (speed < player->unk_08) {
            player->unk_08 = speed;
        }
    }
    if (stickX == 0) {
        player->unk_32 = 0;
    } else if (stickX < 0) {
        player->unk_32 = 1;
    } else {
        player->unk_32 = 2;
    }
    object->rot.y -= player->unk_3C / 30.0f;
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    if (object->trans.y < -500.0f) {
        object->trans.y = -500.0f;
    }
    if (object->trans.y > 500.0f) {
        object->trans.y = 500.0f;
    }
    player->unk_44 = 0.0f;
    if (player->unk_00 == 3) {
        if (player->unk_50 == 0) {
            player->unk_90 = 1;
            player->unk_00 = 0;
        } else {
            if (--player->unk_50 & 1) {
                player->unk_90 = 0;
            } else {
                player->unk_90 = 1;
            }
            player->unk_44 = shake[player->unk_50 & 3];
        }
    }
    func_8010862C_aces_high(object);
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
    if (btn & Z_TRIG) {
        if (player->unk_54 == 1) {
            player->unk_52++;
            if (player->unk_52 >= 30) {
                player->unk_58 ^= 1;
            }
        }
    } else {
        if (player->unk_52 >= 30 && player->unk_54 == 1) {
            func_8010BF3C_aces_high(object);
            func_8004AC5C_main(0x3B2, player->camIdx);
        }
        player->unk_52 = 0;
        player->unk_58 = 0;
    }
    if (player->unk_20 == 0) {
        if ((btnDown & Z_TRIG) && player->unk_24 != 0) {
            func_8010B9F4_aces_high(object);
            func_8004AC5C_main(0x3AD, player->camIdx);
        }
    } else {
        player->unk_20--;
    }
    if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) >= 3950.0f) {
        player->unk_00 = 1;
        player->unk_48 = (500.0f - object->trans.y) / 45.0f;
        player->unk_4E = 45;
        player->unk_52 = 0;
        player->unk_92 = 0;
        object->func = func_80107F98_aces_high;
    }
}

void func_80107F98_aces_high(omObjData *object) {
    AceHighPlayer *player;
    u32 hit;
    f32 angle;

    hit = object->mode;
    object->mode = 0;
    player = object->data;
    if (hit & 2) {
        player->unk_56 = 1;
        player->unk_5C = 50.0f;
        func_8001C258_main(object->model[1], 4, 0);
    }
    if (hit & 4) {
        player->unk_74->work[0] = 45;
        player->unk_74->work[1] = 6;
        player->unk_74->work[2] = 1;
    }
    angle = atan2df(-object->trans.x, -object->trans.z);
    player->unk_58 = 0;
    switch (player->unk_00) {
        case 1:
            player->unk_38 -= 15.0f;
            if (player->unk_38 < -90.0f) {
                player->unk_38 = -90.0f;
            }
            object->rot.y += 20.0f;
            if (object->rot.y >= 360.0f) {
                object->rot.y -= 360.0f;
            }
            object->trans.y += player->unk_48;
            if (--player->unk_4E == 0) {
                object->trans.y = 500.0f;
                object->rot.y = angle;
                player->unk_3C = 0.0f;
                player->unk_00 = 2;
                player->unk_90 = 1;
            } else if (player->unk_4E & 1) {
                player->unk_90 = 0;
            } else {
                player->unk_90 = 1;
            }
            break;
        case 2:
            player->unk_38 += 15.0f;
            if (player->unk_38 >= 0.0f) {
                player->unk_38 = 0.0f;
                player->unk_00 = 0;
                object->func = func_80107654_aces_high;
            }
            player->unk_90 = 1;
            break;
    }
    func_8010843C_aces_high(object);
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
}

void func_801081A8_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;

    switch (player->unk_00) {
        case 4:
            player->unk_38 += 10.0f;
            if (player->unk_38 >= 90.0f) {
                player->unk_38 = 90.0f;
                player->unk_00 = 5;
            }
            break;
        case 5:
            if (player->unk_36 == 0 && object->trans.y < -1000.0f) {
                player->unk_36 = 1;
            }
            if (object->trans.y < -3000.0f) {
                player->unk_00 = 6;
                object->func = NULL;
                player->unk_90 = 0;
                func_8001C258_main(object->model[3], 4, 4);
                player->camObj->func = func_8010ACE0_aces_high;
                Hu3DModelCameraSet(D_8010DE64_aces_high->model[3],
                                   Hu3DData[D_8010DE64_aces_high->model[3]].cameraBit &
                                       ~D_8010DB68_aces_high[player->camIdx]);
            }
            break;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    func_8010843C_aces_high(object);
    func_801068F4_aces_high(object);
    func_80106B70_aces_high(object);
    Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, object->trans.z);
    player->unk_74->work[2] = 0;
    player->unk_78->work[1] = 0;
    espDispOff(player->unk_2E);
    espDispOff(player->unk_30);
    if (player->unk_2C != -1) {
        HuAudFXStop(player->unk_2C);
        player->unk_2C = -1;
    }
}

void func_8010843C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 x;
    f32 y;

    if (player->unk_5C > 0.0f) {
        player->unk_5C -= 10.0f;
        x = -sindf(player->unk_3C);
        y = sindf(player->unk_38);
        player->unk_60 = x * cosdf(-object->rot.y) - y * sindf(-object->rot.y);
        player->unk_64 = x * sindf(-object->rot.y) + y * cosdf(-object->rot.y);
        player->unk_68 = 1.0f - HuSqrtf(player->unk_60 * player->unk_60 + player->unk_64 * player->unk_64);
        player->unk_60 *= player->unk_5C;
        player->unk_68 *= player->unk_5C;
        player->unk_64 *= player->unk_5C;
        if (player->unk_5C <= 0.0f) {
            player->unk_5C = 0.0f;
            player->unk_54 = 1;
            player->unk_52 = 0;
        }
    }
}

void func_801085B0_aces_high(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        AceHighPlayer *player = OM_GET_DATA_PTR(D_8010DE68_aces_high[i], AceHighPlayer);

        for (j = 0; j < 2; j++) {
            espDispOff(player->espriteSlots[j]);
        }
    }
}

void func_8010862C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *other;
    omObjData *otherObj;
    u16 tries;
    s32 i;
    f32 dist;
    f32 ofs;

    for (tries = 0; tries < 4; tries++) {
        for (i = 0; i < 4; i++) {
            if (i == player->camIdx) {
                continue;
            }
            otherObj = D_8010DE68_aces_high[i];
            other = otherObj->data;
            if (other->unk_00 == 6 || other->unk_00 == 1 || other->unk_00 == 3) {
                continue;
            }
            dist = HuSqrtf((object->trans.x - otherObj->trans.x) * (object->trans.x - otherObj->trans.x) +
                           (object->trans.y - otherObj->trans.y) * (object->trans.y - otherObj->trans.y) +
                           (object->trans.z - otherObj->trans.z) * (object->trans.z - otherObj->trans.z));
            if (dist <= HuSqrtf(32400.0f)) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        omVibrate(player->camIdx, 2, 3, 10);
        omVibrate(other->camIdx, 2, 3, 10);
        switch (tries) {
            case 0:
                ofs = -90.0f;
                if (object->trans.y + ofs >= -500.0f) {
                    object->trans.y += ofs;
                }
                break;
            case 1:
                ofs = 90.0f;
                if (object->trans.y + ofs <= 500.0f) {
                    object->trans.y += ofs;
                }
                break;
            case 2:
                ofs = 90.0f;
                object->trans.x += sindf(object->rot.y + ofs) * ofs;
                object->trans.z += cosdf(object->rot.y + ofs) * ofs;
                break;
            case 3:
                ofs = 90.0f;
                object->trans.x += sindf(object->rot.y - ofs) * ofs;
                object->trans.z += cosdf(object->rot.y - ofs) * ofs;
                break;
        }
    }
}

void func_801088A4_aces_high(omObjData *object, s8 *stickX, s8 *stickY, u16 *btnDown, u16 *btn) {
    omObjData *list[4];
    Vec target;
    omObjData *nearest;
    f32 minDist;
    AceHighPlayer *player;
    AceHighPlayer *otherData;
    omObjData *other;
    f32 farDist;
    f32 nearDist;
    f32 fov;
    f32 angleTol;
    f32 missileDist;
    f32 dist;
    f32 angle;
    f32 rotY;
    f32 diff;
    f32 stick;
    u16 state;
    u16 result;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    *btnDown = 0;
    player = object->data;
    switch (GwPlayer[player->camIdx].cpu_difficulty) {
        case 0:
            farDist = 1000.0f;
            nearDist = 500.0f;
            fov = 30.0f;
            angleTol = 5.0f;
            missileDist = 500.0f;
            break;
        case 1:
            farDist = 900.0f;
            nearDist = 500.0f;
            fov = 30.0f;
            angleTol = 4.0f;
            missileDist = 700.0f;
            break;
        case 2:
            farDist = 800.0f;
            nearDist = 400.0f;
            fov = 40.0f;
            angleTol = 3.0f;
            missileDist = 900.0f;
            break;
        case 3:
            farDist = 700.0f;
            nearDist = 400.0f;
            fov = 40.0f;
            angleTol = 3.0f;
            missileDist = 1200.0f;
            break;
    }
    state = player->unk_92;
    dist = HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    if (dist > 3150.0f && state != 2 && !(state == 5 || state == 6)) {
        angle = atan2df(object->trans.x, object->trans.z);
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        rotY = object->rot.y;
        if (rotY < 0.0f) {
            rotY += 360.0f;
        }
        diff = rotY - angle;
        if (fabs(diff) < 75.0) {
            player->unk_94 = player->unk_92;
            player->unk_92 = 2;
            player->unk_A8 = angle - 180.0f;
            if (player->unk_A8 < 0.0f) {
                player->unk_A8 += 360.0f;
            }
        }
    }
    if (state == 0) {
        func_80109928_aces_high(object);
    }
    switch (state) {
        case 1:
            other = player->unk_98;
            otherData = other->data;
            if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (otherData->unk_00 == 6) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            dist = HuSqrtf((other->trans.x - object->trans.x) * (other->trans.x - object->trans.x) +
                           (other->trans.z - object->trans.z) * (other->trans.z - object->trans.z)) *
                   0.8f;
            if (dist > 1500.0f) {
                dist = 1500.0f;
            }
            if (dist < 100.0f) {
                dist = 100.0f;
            }
            target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
            target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
            target.y = other->trans.y;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            result = func_8010951C_aces_high(object, &target, angleTol, 60.0f, stickX, stickY);
            if (dist < 2400.0f) {
                *btnDown |= 0x2000;
            }
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (--player->unk_B0 == 0) {
                player->unk_92 = 0;
                player->unk_34 = 0;
            }
            break;
        case 3:
            other = player->unk_98;
            otherData = other->data;
            if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (otherData->unk_00 == 6) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (player->unk_AE == 0) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            dist = HuSqrtf((other->trans.x - object->trans.x) * (other->trans.x - object->trans.x) +
                           (other->trans.z - object->trans.z) * (other->trans.z - object->trans.z)) *
                   0.8f;
            if (dist > 1500.0f) {
                dist = 1500.0f;
            }
            if (dist < 100.0f) {
                dist = 100.0f;
            }
            target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
            target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
            target.y = other->trans.y;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            result = func_8010951C_aces_high(object, &target, angleTol, 60.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            break;
        case 4:
            target = player->unk_9C;
            dist = HuSqrtf((object->trans.x - player->unk_9C.x) * (object->trans.x - player->unk_9C.x) +
                           (object->trans.y - player->unk_9C.y) * (object->trans.y - player->unk_9C.y) +
                           (object->trans.z - player->unk_9C.z) * (object->trans.z - player->unk_9C.z));
            result = func_8010951C_aces_high(object, &target, angleTol, 20.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (dist < 100.0f) {
                player->unk_92 = 0;
            }
            if (--player->unk_B0 == 0) {
                player->unk_92 = 0;
            }
            break;
        case 2:
            angle = player->unk_A8;
            rotY = object->rot.y;
            if (rotY < 0.0f) {
                rotY += 360.0f;
            }
            diff = rotY - angle;
            if (fabs(diff) < 5.0) {
                player->unk_92 = player->unk_94;
                break;
            }
            if (fabs(diff) > 35.0) {
                stick = 70.0f;
            } else {
                stick = fabs(diff / 2.0f);
            }
            if (stick < 10.0f) {
                stick = 10.0f;
            }
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                *stickX = stick;
            } else {
                *stickX = -stick;
            }
            if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) > 3600.0f) {
                *btn |= 0x4000;
            }
            break;
        case 5:
            target = player->unk_9C;
            dist = HuSqrtf((object->trans.x - player->unk_9C.x) * (object->trans.x - player->unk_9C.x) +
                           (object->trans.y - player->unk_9C.y) * (object->trans.y - player->unk_9C.y) +
                           (object->trans.z - player->unk_9C.z) * (object->trans.z - player->unk_9C.z));
            result = func_8010951C_aces_high(object, &target, 3.0f, 20.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (func_800E6E8C_minigame() == 4) {
                player->unk_92 = 6;
                func_8010B26C_aces_high(object);
                player->camObj->func = func_8010B4BC_aces_high;
                object->func = func_801071D4_aces_high;
                player->unk_4E = 25;
            }
            break;
        case 6:
            if (player->unk_4E != 0) {
                *stickY = -45;
                *stickX = -65;
                player->unk_4E--;
            } else {
                *stickY = -70;
                player->unk_0C = 1;
            }
            *btn |= 0x8000;
            break;
    }
    if (state == 5 || state == 6) {
        return;
    }
    if (func_80109EEC_aces_high(object, fov, list, &nearest, &minDist) != 0) {
        if (minDist <= 2750.0f) {
            *btnDown |= 0x2000;
        }
        if (player->unk_92 == 1 && minDist < 1000.0f) {
            player->unk_B0 = rand8() % 181 + 60;
            player->unk_92 = 1;
            player->unk_98 = nearest;
        }
    }
    if (player->unk_70 != 0 && func_8010A0F0_aces_high(object) < missileDist) {
        *btn = (*btn & ~0x4000) | 0x8000;
    }
    if (player->unk_AE != 0) {
        if (player->unk_52 < player->unk_AC) {
            *btn |= 0x2000;
        } else {
            player->unk_AE = 0;
        }
    }
    func_8010A214_aces_high(object);
}

u16 func_8010951C_aces_high(omObjData *object, Vec *target, f32 angleTol, f32 heightTol, s8 *stickX, s8 *stickY) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *other;
    f32 scale;
    f32 angle;
    f32 rotY;
    f32 diff;
    f32 stick;
    f32 dy;
    u16 btn;

    scale = HuSqrtf((target->x - object->trans.x) * (target->x - object->trans.x) +
                    (target->z - object->trans.z) * (target->z - object->trans.z)) /
            600.0f;
    if (scale > 2.0f) {
        scale = 2.0f;
    }
    if (scale < 0.3f) {
        scale = 0.3f;
    }
    btn = 0;
    angle = atan2df(target->x - object->trans.x, target->z - object->trans.z);
    rotY = object->rot.y;
    if (rotY > 180.0f) {
        rotY -= 360.0f;
    }
    diff = rotY - angle;
    if (fabs(diff) < angleTol) {
        *stickX = 0;
    } else {
        if (fabs(diff * scale) > 70.0) {
            stick = 70.0f;
            btn = 0x4000;
        } else {
            stick = fabs(diff * scale);
        }
        if (stick < 10.0f) {
            stick = 0.0f;
        }
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        if (rotY < 0.0f) {
            rotY += 360.0f;
        }
        diff = angle - rotY;
        if (diff < 0.0f) {
            diff += 360.0f;
        }
        if (diff > 180.0f) {
            *stickX = stick;
        } else {
            *stickX = -stick;
        }
        if (player->unk_92 == 1 || player->unk_92 == 3) {
            other = player->unk_98->data;
            if (other->unk_32 == player->unk_32 && other->unk_34 == 0) {
                if (rand8() % 10 < 5) {
                    player->unk_34 ^= 1;
                }
            }
            if (player->unk_34 != 0) {
                *stickX = -*stickX;
            }
        }
    }
    dy = target->y - object->trans.y;
    if (fabs(dy) > heightTol) {
        if (fabs(dy * scale) > 70.0) {
            stick = 70.0f;
        } else {
            stick = fabs(dy * scale);
        }
        if (stick < 10.0f) {
            stick = 0.0f;
        }
        if (target->y > object->trans.y) {
            *stickY = -stick;
        } else {
            *stickY = stick;
        }
    }
    return btn;
}

void func_80109928_aces_high(omObjData *object) {
    u16 actions[4][8] = {
        { 4, 1, 4, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
    };
    AceHighPlayer *player = object->data;
    omObjData *otherObj;
    s16 chance;
    u16 action;
    u16 done;
    s32 i;
    u16 state;
    f32 angle;
    f32 dist;

    switch (GwPlayer[player->camIdx].cpu_difficulty) {
        case 0:
            chance = 2;
            break;
        case 1:
            chance = 3;
            break;
        case 2:
            chance = 4;
            break;
        case 3:
            chance = 4;
            break;
    }
    if (D_8010DE8C_aces_high == 2) {
        chance *= 2;
    }
    done = 0;
    action = actions[GwPlayer[player->camIdx].cpu_difficulty][rand8() & 7];
    while (done == 0) {
        switch (action) {
            case 1:
                for (i = 0; i < 4; i++) {
                    if (i == player->camIdx) {
                        continue;
                    }
                    otherObj = D_8010DE68_aces_high[i];
                    state = ((AceHighPlayer *)otherObj->data)->unk_00;
                    if (state == 6 || state == 4) {
                        continue;
                    }
                    if (state == 5 || state == 1) {
                        continue;
                    }
                    break;
                }
                if (i == 4) {
                    action = 4;
                    break;
                }
                player->unk_98 = otherObj;
                if (player->unk_54 == 1 && rand8() % 10 < chance) {
                    player->unk_AC = (rand8() & 0xF) + 30;
                    player->unk_AE = 1;
                    player->unk_92 = 3;
                    done = 1;
                } else {
                    player->unk_B0 = rand8() % 181 + 60;
                    player->unk_92 = 1;
                    done = 1;
                }
                break;
            case 4:
                if (D_8010DE8C_aces_high == 2 && rand8() % 10 < 2) {
                    action = 1;
                    break;
                }
                angle = atan2df(object->trans.x, object->trans.z) - 180.0f;
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                angle *= 10.0f;
                angle += (rand8() * rand8()) % 900 - 450.0f;
                angle /= 10.0f;
                dist = (rand8() * rand8()) % 2750 + 200.0f;
                player->unk_9C.x = sindf(angle) * dist;
                player->unk_9C.z = cosdf(angle) * dist;
                player->unk_9C.y = (rand8() * rand8()) % 1000 + -500.0f;
                player->unk_92 = 4;
                player->unk_B0 = rand8() % 121 + 60;
                done = 1;
                break;
        }
    }
}

s16 func_80109EEC_aces_high(omObjData *object, f32 fov, omObjData **list, omObjData **nearest, f32 *minDist) {
    s16 count = 0;
    AceHighPlayer *player = object->data;
    omObjData *other;
    u16 state;
    s32 i;
    f32 angle;
    f32 rotY;
    f32 dist;

    *list = NULL;
    *minDist = 1000000.0f;
    *nearest = NULL;
    for (i = 0; i < 4; i++) {
        if (player->camIdx == i) {
            continue;
        }
        other = D_8010DE68_aces_high[i];
        state = ((AceHighPlayer *)other->data)->unk_00;
        if (state == 6 || state == 4) {
            continue;
        }
        if (state == 5 || state == 1) {
            continue;
        }
        angle = atan2df(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
        rotY = object->rot.y;
        if (rotY > 180.0f) {
            rotY -= 360.0f;
        }
        if (fabs(rotY - angle) <= fov / 2.0f) {
            list[count++] = other;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            if (dist < *minDist) {
                *minDist = dist;
                *nearest = other;
            }
        }
    }
    return count;
}

f32 func_8010A0F0_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    omObjData **shots;
    omObjData *shot;
    f32 minDist;
    f32 dist;
    s32 i;
    s32 j;

    minDist = 10000000.0f;
    for (i = 0; i < 4; i++) {
        if (i == player->camIdx) {
            continue;
        }
        shots = D_8010DE70_aces_high[i];
        for (j = 0; j < 5; j++) {
            shot = shots[j];
            if (shot == NULL || ((AceHighShot *)shot->data)->unk_00 != 1) {
                continue;
            }
            dist = HuSqrtf((shot->trans.x - object->trans.x) * (shot->trans.x - object->trans.x) +
                           (shot->trans.y - object->trans.y) * (shot->trans.y - object->trans.y) +
                           (shot->trans.z - object->trans.z) * (shot->trans.z - object->trans.z));
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

void func_8010A214_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    s32 i;
    f32 angle;
    f32 dist;

    for (i = 0; i < 4; i++) {
        if (((AceHighPlayer *)D_8010DE68_aces_high[i]->data)->unk_98 != object) {
            continue;
        }
        if (player->unk_92 == 4) {
            continue;
        }
        if (rand8() % 10 >= 5) {
            continue;
        }
        player->unk_98 = NULL;
        angle = atan2df(object->trans.x, object->trans.z) - 180.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle *= 10.0f;
        angle += (rand8() * rand8()) % 900 - 450.0f;
        angle /= 10.0f;
        dist = (rand8() * rand8()) % 2750 + 200.0f;
        player->unk_9C.x = sindf(angle) * dist;
        player->unk_9C.z = cosdf(angle) * dist;
        player->unk_9C.y = (rand8() * rand8()) % 1000 + -500.0f;
        player->unk_92 = 4;
        player->unk_B0 = rand8() % 121 + 60;
    }
}

void func_8010A51C_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotX;
    f32 rotY;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    if (player->unk_00 != 4 && player->unk_00 != 5) {
        rotY = playerObj->rot.y - 180.0f;
        CRotM[player->camIdx].y = rotY;
        rotX = playerObj->trans.y * 0.06f;
        CRotM[player->camIdx].x = rotX;
        x = playerObj->trans.x + sindf(playerObj->rot.y) * 300.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 300.0f;
        y = playerObj->trans.y + 100.0f;
        CenterM[player->camIdx].x = x;
        CenterM[player->camIdx].y = y;
        CenterM[player->camIdx].z = z;
        if (player->unk_08 > 27.777777f) {
            zoom = (player->unk_08 - 27.777777f) / 13.888887f * 150.0f + 1000.0f;
        } else if (player->unk_08 < 27.777777f) {
            zoom = 1000.0f - (27.777777f - player->unk_08) / 11.111111f * 150.0f;
        } else {
            zoom = 1000.0f;
        }
        CZoomM[player->camIdx] = zoom;
    } else {
        rotX = playerObj->trans.y * 0.06f;
        if (rotX < -90.0f) {
            rotX = -90.0f;
        }
        CRotM[player->camIdx].x = rotX;
        x = playerObj->trans.x + sindf(playerObj->rot.y) * 300.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 300.0f;
        y = playerObj->trans.y + 100.0f;
        CenterM[player->camIdx].x = x;
        CenterM[player->camIdx].y = y;
        CenterM[player->camIdx].z = z;
        CZoomM[player->camIdx] =
            HuSqrtf((object->trans.x - playerObj->trans.x) * (object->trans.x - playerObj->trans.x) +
                    (object->trans.y - playerObj->trans.y) * (object->trans.y - playerObj->trans.y) +
                    (object->trans.z - playerObj->trans.z) * (object->trans.z - playerObj->trans.z));
    }
}

void func_8010A884_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 rotX = CRotM[player->camIdx].x;
    f32 rotY = CRotM[player->camIdx].y;

    player->camObj->trans.x = CenterM[player->camIdx].x + sindf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    player->camObj->trans.y = CenterM[player->camIdx].y + -sindf(rotX) * CZoomM[player->camIdx];
    player->camObj->trans.z = CenterM[player->camIdx].z + cosdf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
}

void func_8010A9D4_aces_high(omObjData *object) {
    omObjData *camObj = (omObjData *)object->work[1];
    AceHighPlayer *camData = (AceHighPlayer *)camObj->data;
    f32 rotX = (camObj->trans.y - -250.0f) * 0.08f;

    CRotM[camData->camIdx].x = rotX;
    CRotM[camData->camIdx].z = 0.0f;
    CRotM[camData->camIdx].y = camData->unk_8C;
    CenterM[camData->camIdx].x = camObj->trans.x;
    CenterM[camData->camIdx].y = 0.0f;
    CenterM[camData->camIdx].z = camObj->trans.z;
    CZoomM[camData->camIdx] = 650.0f;
}

void func_8010AADC_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;

    object->work[2]++;
    CRotM[player->camIdx].x += (playerObj->trans.y * 0.06f - object->scale.x) / 30.0f;
    CenterM[player->camIdx].x = sindf(playerObj->rot.y) * 300.0f / 30.0f * object->work[2] + playerObj->trans.x;
    CenterM[player->camIdx].z = cosdf(playerObj->rot.y) * 300.0f / 30.0f * object->work[2] + playerObj->trans.z;
    CenterM[player->camIdx].y += (playerObj->trans.y + 100.0f) / 30.0f;
    CZoomM[player->camIdx] += 11.666667f;
}

void func_8010ACE0_aces_high(omObjData *object) {
    AceHighPlayer *camData = (AceHighPlayer *)((omObjData *)object->work[1])->data;

    CenterM[camData->camIdx].y = 0.0f;
    CZoomM[camData->camIdx] = 2700.0f;
    CRotM[camData->camIdx].x = 90.0f;
}

void func_8010AD4C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    omObjData *camObj = player->camObj;

    camObj->scale.x = -180.0f;
    camObj->trans.x = (-10.0f - CRotM[player->camIdx].x) / 60.0f;
    camObj->trans.y = CRotM[player->camIdx].x;
    camObj->scale.y = -4.5f;
    camObj->scale.z = (750.0f - CZoomM[player->camIdx]) / 60.0f;
    camObj->trans.z = CZoomM[player->camIdx];
    camObj->work[2] = 0;
    camObj->func = func_8010AE30_aces_high;
}

void func_8010AE30_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotY;
    f32 rotX;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    rotY = playerObj->rot.y + object->scale.x;
    object->scale.x += 3.0f;
    rotX = object->trans.y + object->work[2] * object->trans.x;
    x = playerObj->trans.x + sindf(playerObj->rot.y) * (object->work[2] * object->scale.y + 300.0f);
    z = playerObj->trans.z + cosdf(playerObj->rot.y) * (object->work[2] * object->scale.y + 300.0f);
    y = playerObj->trans.y + 100.0f;
    zoom = object->trans.z + object->work[2] * object->scale.z;
    if (object->work[2]++ >= 60) {
        rotY = playerObj->rot.y;
        rotX = -10.0f;
        x = playerObj->trans.x + sindf(rotY) * 30.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 30.0f;
        y = playerObj->trans.y + 100.0f;
        zoom = 750.0f;
        object->func = func_8010B0E8_aces_high;
    }
    CRotM[player->camIdx].y = rotY;
    CRotM[player->camIdx].x = rotX;
    CenterM[player->camIdx].x = x;
    CenterM[player->camIdx].y = y;
    CenterM[player->camIdx].z = z;
    CZoomM[player->camIdx] = zoom;
}

void func_8010B0E8_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotY;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    rotY = playerObj->rot.y;
    CRotM[player->camIdx].y = rotY;
    CRotM[player->camIdx].x = -10.0f;
    x = sindf(playerObj->rot.y) * 30.0f + playerObj->trans.x;
    z = cosdf(playerObj->rot.y) * 30.0f + playerObj->trans.z;
    y = playerObj->trans.y + 100.0f;
    CenterM[player->camIdx].x = x;
    CenterM[player->camIdx].y = y;
    CenterM[player->camIdx].z = z;
    zoom = 750.0f;
    CZoomM[player->camIdx] = zoom;
}

void func_8010B224_aces_high(omObjData *object) {
    Hu3DCameraPosSetV(OM_GET_WORK_PTR(object, s16)[1], &D_8010DEA8_aces_high, &D_8010DEB4_aces_high,
                      &D_8010DEC0_aces_high);
    Hu3DCamUpdateMtx(OM_GET_WORK_PTR(object, s16)[1]);
}

void func_8010B26C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 rotX = CRotM[player->camIdx].x;
    f32 rotY = CRotM[player->camIdx].y;

    D_8010DEA8_aces_high.x = CenterM[player->camIdx].x + sindf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    D_8010DEA8_aces_high.y = CenterM[player->camIdx].y + -sindf(rotX) * CZoomM[player->camIdx];
    D_8010DEA8_aces_high.z = CenterM[player->camIdx].z + cosdf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    D_8010DEB4_aces_high.x = CenterM[player->camIdx].x;
    D_8010DEB4_aces_high.y = CenterM[player->camIdx].y;
    D_8010DEB4_aces_high.z = CenterM[player->camIdx].z;
    D_8010DEC0_aces_high.x = sindf(rotY) * sindf(rotX);
    D_8010DEC0_aces_high.y = cosdf(rotX);
    D_8010DEC0_aces_high.z = cosdf(rotY) * sindf(rotX);
    omDelObj(D_8010DE84_aces_high);
    D_8010DE84_aces_high = omAddObj(0x7FDA, 0, 0, -1, func_8010B224_aces_high);
    D_8010DE84_aces_high->work[0] = player->camIdx;
    omSetStatBit(D_8010DE84_aces_high, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_8010B4BC_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotX;
    f32 rotY;

    D_8010DEB4_aces_high.x = sindf(playerObj->rot.y) * 30.0f + playerObj->trans.x;
    D_8010DEB4_aces_high.z = cosdf(playerObj->rot.y) * 30.0f + playerObj->trans.z;
    D_8010DEB4_aces_high.y = playerObj->trans.y + 100.0f;
    CRotM[player->camIdx].y =
        atan2df(playerObj->trans.x - D_8010DEA8_aces_high.x, playerObj->trans.z - D_8010DEA8_aces_high.z);
    rotX = CRotM[player->camIdx].x;
    rotY = CRotM[player->camIdx].y;
    D_8010DEC0_aces_high.x = sindf(rotY) * sindf(rotX);
    D_8010DEC0_aces_high.y = cosdf(rotX);
    D_8010DEC0_aces_high.z = cosdf(rotY) * sindf(rotX);
}

void func_8010B618_aces_high(void) {
    s32 i;

    D_8010DE6C_aces_high = omAddObj(28, 4, 0, -1, func_8010B760_aces_high);
    for (i = 0; i < 4; i++) {
        D_8010DE6C_aces_high->model[i] = func_8000B108_main(D_8010DC90_aces_high[GwPlayer[i].chr], 0xADD);
    }
    for (i = 0; i < 20; i++) {
        D_8010DED0_aces_high[i] = 0;
        D_8010DEF8_aces_high[i] = func_8000B108_main(0x380020, 0xADD);
    }
    for (i = 0; i < 4; i++) {
        omMakeGroup(i + 1, 5);
        D_8010DE70_aces_high[i] = omGetGroupMemberList(i + 1);
    }
}

void func_8010B760_aces_high(omObjData *object) {
    omObjData **shots;
    omObjData **otherShots;
    omObjData *shot;
    omObjData *other;
    AceHighShot *shotData;
    AceHighShot *otherData;
    f32 dist;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    for (i = 0; i < 4; i++) {
        shots = D_8010DE70_aces_high[i];
        for (j = 0; j < 5; j++) {
            if (shots[j] == NULL) {
                continue;
            }
            shot = shots[j];
            shotData = shot->data;
            if (shotData->unk_02 == 1) {
                continue;
            }
            for (k = 0; k < 4; k++) {
                if (k == i) {
                    continue;
                }
                other = D_8010DE68_aces_high[k];
                if (((AceHighPlayer *)other->data)->unk_00 != 0) {
                    continue;
                }
                dist = HuSqrtf((other->trans.x - shot->trans.x) * (other->trans.x - shot->trans.x) +
                               (other->trans.y - shot->trans.y) * (other->trans.y - shot->trans.y) +
                               (other->trans.z - shot->trans.z) * (other->trans.z - shot->trans.z));
                if (HuSqrtf((shotData->radius + 90.0f) * (shotData->radius + 90.0f)) < dist) {
                    continue;
                }
                func_80047E90_main(other, 1);
                func_80047E90_main(shot, 1);
            }
            for (k = 0; k < 4; k++) {
                if (k == i) {
                    continue;
                }
                otherShots = D_8010DE70_aces_high[k];
                for (m = 0; m < 5; m++) {
                    other = otherShots[m];
                    if (other == NULL) {
                        continue;
                    }
                    if (other == shot) {
                        continue;
                    }
                    otherData = other->data;
                    if (otherData->unk_02 == 1) {
                        continue;
                    }
                    dist = HuSqrtf((shot->trans.x - other->trans.x) * (shot->trans.x - other->trans.x) +
                                   (shot->trans.y - other->trans.y) * (shot->trans.y - other->trans.y) +
                                   (shot->trans.z - other->trans.z) * (shot->trans.z - other->trans.z));
                    if (HuSqrtf((shotData->radius + otherData->radius) * (shotData->radius + otherData->radius)) <
                        dist) {
                        continue;
                    }
                    func_80047E90_main(shot, 1);
                    func_80047E90_main(other, 1);
                }
            }
        }
    }
}

void func_8010B9F4_aces_high(omObjData *object) {
    AceHighPlayer *player;
    omObjData *shotObj;
    AceHighShot *shot;
    Vec dir;
    f32 rotY;
    f32 len;
    u16 idx;
    s32 i;

    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    player = object->data;
    player->unk_20 = 10;
    player->unk_24--;
    idx = player->camIdx;
    shotObj = omAddObj(28, 1, 0, idx + 1, func_8010BD84_aces_high);
    shot = shotObj->data = HuMemAllocTag(sizeof(AceHighShot), 0x7918);
    shotObj->model[0] = Hu3DModelLink(D_8010DE6C_aces_high->model[idx]);
    func_8001C258_main(shotObj->model[0], 4, 0);
    shot->unk_00 = 0;
    shot->speed = player->unk_08 + 27.777777f;
    dir = player->dir;
    rotY = object->rot.y - player->unk_80;
    shot->dir.y = -sindf(player->unk_38) * 0.5f;
    shot->dir.x = sindf(rotY) * (1.0 - fabs(shot->dir.y));
    shot->dir.z = cosdf(rotY) * (1.0 - fabs(shot->dir.y));
    shot->dir.x += dir.x;
    shot->dir.y += dir.y;
    shot->dir.z += dir.z;
    len = HuSqrtf(shot->dir.x * shot->dir.x + shot->dir.y * shot->dir.y + shot->dir.z * shot->dir.z);
    shot->dir.x /= len;
    shot->dir.y /= len;
    shot->dir.z /= len;
    shot->owner = object;
    shot->unk_02 = 0;
    shot->unk_08 = 2400.0f;
    shot->radius = 30.0f;
    shot->unk_26 = 0;
    for (i = 0; i < 20; i++) {
        if (D_8010DED0_aces_high[i] == 0) {
            break;
        }
    }
    if (i == 20) {
        shot->effectIdx = -1;
    } else {
        shot->effectIdx = i;
        shot->effectModel = D_8010DEF8_aces_high[i];
        D_8010DED0_aces_high[i] = 1;
    }
    omSetTra(shotObj, object->trans.x, object->trans.y, object->trans.z);
}

void func_8010BCC4_aces_high(void) {
    omObjData **shots;
    AceHighPlayer *player;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        shots = D_8010DE70_aces_high[i];
        for (j = 0; j < 5; j++) {
            if (shots[j] != NULL) {
                func_80047E90_main(shots[j], 1);
            }
        }
        player = D_8010DE68_aces_high[i]->data;
        for (j = 0; j < 4; j++) {
            player->unk_74->work[2] = 0;
        }
    }
}

void func_8010BD84_aces_high(omObjData *object) {
    AceHighShot *shot = object->data;
    AceHighPlayer *owner;
    u32 hit;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        shot->unk_02 = 1;
        func_8001C258_main(shot->effectModel, 4, 0);
        func_8001C814_main(shot->effectModel, 3, 0);
        Hu3DMotionTimeSet(shot->effectModel, 0.0f);
        Hu3DModelPosSet(shot->effectModel, object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelKill(object->model[0]);
        shot->timer = 30;
        shot->radius = 50.0f;
    }
    switch (shot->unk_02) {
        case 0:
            object->trans.x += shot->dir.x * shot->speed;
            object->trans.y += shot->dir.y * shot->speed;
            object->trans.z += shot->dir.z * shot->speed;
            shot->unk_08 -= shot->speed;
            if (shot->unk_08 < 0.0f) {
                owner = shot->owner->data;
                func_8004AC5C_main(0x3AE, owner->camIdx);
                func_80047E90_main(object, 1);
            }
            break;
        case 1:
            if (shot->timer == 0) {
                func_8001C258_main(shot->effectModel, 4, 4);
                D_8010DED0_aces_high[shot->effectIdx] = 0;
                owner = shot->owner->data;
                owner->unk_24++;
                omDelObj(object);
            } else {
                shot->timer--;
            }
            break;
    }
}

void func_8010BF3C_aces_high(omObjData *object) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *otherData;
    omObjData *shotObj;
    omObjData *other;
    AceHighShot *shot;
    f32 minDist;
    f32 dist;
    s32 i;

    func_8001C258_main(object->model[1], 4, 0);
    func_8001C258_main(object->model[2], 4, 4);
    player->unk_58 = 0;
    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    player->unk_56 = 0;
    player->unk_54 = 0;
    shotObj = player->unk_6C = omAddObj(28, 1, 0, player->camIdx + 1, func_8010C288_aces_high);
    shotObj->data = HuMemAllocTag(sizeof(AceHighShot), 0x7918);
    shotObj->model[0] = object->model[1];
    shotObj->trans.x = object->trans.x;
    shotObj->trans.y = object->trans.y;
    shotObj->trans.z = object->trans.z;
    shotObj->rot.x = object->rot.x;
    shotObj->rot.y = object->rot.y;
    shotObj->rot.z = object->rot.z;
    shot = shotObj->data;
    shot->unk_00 = 1;
    shot->speed = 52.777775f;
    shot->dir = player->dir;
    shot->owner = object;
    shot->unk_02 = 0;
    shot->unk_08 = 7900.0f;
    shot->radius = 35.0f;
    shot->unk_26 = 0;
    shot->unk_2C = player->unk_38;
    shot->unk_30 = object->rot.y;
    if (shot->unk_2C < 0.0f) {
        shot->unk_2C += 360.0f;
    }
    shot->unk_34 = 20;
    shot->unk_36 = 0;
    for (i = 0; i < 20; i++) {
        if (D_8010DED0_aces_high[i] == 0) {
            break;
        }
    }
    if (i == 20) {
        shot->effectIdx = -1;
    } else {
        shot->effectIdx = i;
        shot->effectModel = D_8010DEF8_aces_high[i];
        D_8010DED0_aces_high[i] = 1;
    }
    minDist = 1000000.0f;
    shot->target = NULL;
    for (i = 0; i < 4; i++) {
        if (i == player->camIdx) {
            continue;
        }
        other = D_8010DE68_aces_high[i];
        otherData = other->data;
        if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
            continue;
        }
        if (otherData->unk_00 == 6) {
            continue;
        }
        dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                       (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                       (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
        if (dist < minDist) {
            minDist = dist;
            shot->target = other;
        }
    }
    if (shot->target != NULL) {
        otherData = shot->target->data;
        otherData->unk_70++;
        func_80047E90_main(shot->target, 4);
        otherData->unk_78->work[1] = 1;
    }
    omVibrate(player->camIdx, 10, 0, 10);
}

void func_8010C288_aces_high(omObjData *object) {
    AceHighShot *shot = object->data;
    AceHighPlayer *playerData;
    u32 hit;
    f32 yaw;
    f32 pitch;
    f32 yawDelta;
    f32 len;
    f32 diff;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        shot->unk_02 = 1;
        func_8001C258_main(shot->effectModel, 4, 0);
        func_8001C814_main(shot->effectModel, 3, 0);
        Hu3DMotionTimeSet(shot->effectModel, 0.0f);
        Hu3DModelPosSet(shot->effectModel, object->trans.x, object->trans.y, object->trans.z);
        func_8001C258_main(object->model[0], 4, 4);
        shot->timer = 30;
        shot->radius = 50.0f;
        playerData = shot->owner->data;
        playerData->unk_6C = NULL;
        if (shot->target != NULL) {
            playerData = shot->target->data;
            if (--playerData->unk_70 < 0) {
                playerData->unk_70 = 0;
            }
        }
    }
    switch (shot->unk_02) {
        case 0:
            if (shot->target != NULL) {
                playerData = shot->target->data;
                if (playerData->unk_00 == 4 || playerData->unk_00 == 5) {
                    shot->target = NULL;
                } else if (playerData->unk_00 == 6) {
                    shot->target = NULL;
                } else {
                    yaw = atan2df(shot->target->trans.x - object->trans.x, shot->target->trans.z - object->trans.z);
                    if (yaw < 0.0f) {
                        yaw += 360.0f;
                    }
                    if (shot->target->trans.y == object->trans.y) {
                        pitch = 0.0f;
                    } else {
                        pitch = atan2df(shot->target->trans.y - object->trans.y,
                                        shot->target->trans.z - object->trans.z);
                    }
                    if (pitch > 90.0f) {
                        pitch = 180.0f - pitch;
                    }
                    if (pitch < -90.0f) {
                        pitch = -180.0f - pitch;
                    }
                    yawDelta = yaw - shot->unk_30;
                    len = HuSqrtf(pitch * pitch + yawDelta * yawDelta);
                    if (len != 0.0f) {
                        len = 1.0f / len;
                        pitch = fabs(pitch * len * 3.5f);
                        yawDelta = fabs(yawDelta * len * 3.5f);
                    } else {
                        pitch = 3.5f;
                        yawDelta = pitch;
                    }
                    diff = yaw - shot->unk_30;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (yawDelta < diff) {
                            shot->unk_30 += yawDelta;
                        } else {
                            shot->unk_30 = yaw;
                        }
                    } else if (yawDelta < 360.0f - diff) {
                        shot->unk_30 -= yawDelta;
                    } else {
                        shot->unk_30 = yaw;
                    }
                    if (shot->unk_30 < 0.0f) {
                        shot->unk_30 += 360.0f;
                    }
                    if (shot->unk_30 >= 360.0f) {
                        shot->unk_30 -= 360.0f;
                    }
                    if (shot->target->trans.y == object->trans.y) {
                        yaw = 0.0f;
                    } else {
                        yaw = atan2df(shot->target->trans.y - object->trans.y,
                                      shot->target->trans.z - object->trans.z);
                    }
                    if (yaw > 90.0f) {
                        yaw = 180.0f - yaw;
                    }
                    if (yaw < -90.0f) {
                        yaw = -180.0f - yaw;
                    }
                    if (yaw < 0.0f) {
                        yaw += 360.0f;
                    }
                    if (yaw >= 360.0f) {
                        yaw -= 360.0f;
                    }
                    diff = yaw - shot->unk_2C;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (pitch < diff) {
                            shot->unk_2C += pitch;
                        } else {
                            shot->unk_2C = yaw;
                        }
                    } else if (pitch < 360.0f - diff) {
                        shot->unk_2C -= pitch;
                    } else {
                        shot->unk_2C = yaw;
                    }
                    if (shot->unk_2C < 0.0f) {
                        shot->unk_2C += 360.0f;
                    }
                    if (shot->unk_2C >= 360.0f) {
                        shot->unk_2C -= 360.0f;
                    }
                    if (shot->unk_34 == 0) {
                        if (shot->unk_36 == 0) {
                            shot->dir.y = sindf(shot->unk_2C);
                            shot->dir.x = sindf(shot->unk_30) * (1.0 - fabs(shot->dir.y));
                            shot->dir.z = cosdf(shot->unk_30) * (1.0 - fabs(shot->dir.y));
                            shot->unk_36 = 2;
                        } else {
                            shot->unk_36--;
                        }
                    } else {
                        shot->unk_34--;
                    }
                }
            }
            object->trans.x += shot->dir.x * shot->speed;
            object->trans.y += shot->dir.y * shot->speed;
            object->trans.z += shot->dir.z * shot->speed;
            func_80088910_main(Hu3DData[object->model[0]].mtx, -shot->unk_2C, 0.0f, 0.0f);
            object->rot.y = shot->unk_30;
            shot->unk_08 -= shot->speed;
            if (shot->unk_08 < 0.0f) {
                func_80047E90_main(object, 1);
            }
            break;
        case 1:
            if (shot->timer == 0) {
                func_8001C258_main(shot->effectModel, 4, 4);
                D_8010DED0_aces_high[shot->effectIdx] = 0;
                func_80047E90_main(shot->owner, 2);
                omDelObj(object);
            } else {
                shot->timer--;
            }
            break;
    }
}

void func_8010C9DC_aces_high(void) {
    omObjData *obj = omAddObj(0x1E, 0, 0, -1, func_8010CA6C_aces_high);

    D_8010DE80_aces_high = obj;
    obj->work[0] = 1;
    D_8010DF20_aces_high = espEntry(func_8000B838_main(0x38001C), 0, 0);
    espPosSet(D_8010DF20_aces_high, 0xA0, 0x78);
    espPriSet(D_8010DF20_aces_high, 0x8064);
}

void func_8010CA6C_aces_high(omObjData *object) {
    u16 order[4] = { 0, 1, 2, 3 };
    AceHighPlayer *player;
    f32 scale;
    s16 x;
    s16 y;
    omObjData *obj;
    u16 temp;
    s32 i;
    s32 j;

    if (object->work[0] == 0) {
        for (i = 0; i < 4; i++) {
            player = D_8010DE68_aces_high[i]->data;
            espDispOff(player->unk_1C);
            espDispOff(player->unk_1E);
        }
        espDispOff(D_8010DF20_aces_high);
        object->func = NULL;
        return;
    }
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (D_8010DE68_aces_high[order[i]]->trans.y < D_8010DE68_aces_high[order[j]]->trans.y) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        obj = D_8010DE68_aces_high[order[i]];
        player = obj->data;
        x = obj->trans.x * 0.005063291f + 160.0f;
        y = obj->trans.z * 0.005063291f + 120.0f;
        espPosSet(player->unk_1C, x, y);
        scale = 1.0f + obj->trans.y / 500.0f * 0.25f;
        espScaleSet(player->unk_1C, scale, scale);
        espPriSet(player->unk_1C, (u16)(i + 0x8005));
        espZRotSet(player->unk_1C, obj->rot.y);
        espTPLvlSet(player->unk_1C, 0xC0);
        if (player->unk_6C != NULL) {
            x = player->unk_6C->trans.x * 0.005063291f + 160.0f;
            y = player->unk_6C->trans.z * 0.005063291f + 120.0f;
            espPosSet(player->unk_1E, x, y);
            scale = 1.0f + player->unk_6C->trans.y / 500.0f * 0.25f;
            scale *= 0.5f;
            espScaleSet(player->unk_1E, scale, scale);
            espZRotSet(player->unk_1E, player->unk_6C->rot.y);
            espDispOn(player->unk_1E);
        } else {
            espDispOff(player->unk_1E);
        }
    }
}

void func_8010CD88_aces_high(omObjData *object) {
    switch (D_8010DE88_aces_high) {
        case 0:
            WipeCreateIn(0xFF, 16);
            D_8010DE88_aces_high = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                D_8010DE88_aces_high = 2;
                D_8010DE96_aces_high = HuAudFXPlay(0x3AC);
                HuAudFXPlay(0x3B3);
            }
            break;
        case 2:
            if (func_800E6E8C_minigame() == 1) {
                omDelObj(object);
                D_8010DE5C_aces_high = NULL;
            }
            break;
    }
}

void func_8010CE5C_aces_high(omObjData *object) {
    switch (D_8010DE8A_aces_high) {
        case 0:
            if (D_8010DCB0_aces_high == 0) {
                D_8010DCB0_aces_high = 1;
                D_8010DE80_aces_high->work[0] = 0;
                func_8010BCC4_aces_high();
                func_801085B0_aces_high();
                HuAudFXStop(D_8010DE96_aces_high);
            }
            func_8010CFF8_aces_high();
            if (D_8010DE90_aces_high != 0) {
                if (D_8010DCB2_aces_high != 0) {
                    D_8010DCB2_aces_high--;
                } else if (D_8010DE8E_aces_high != -1) {
                    D_8010DE8A_aces_high = 2;
                    func_8010AD4C_aces_high(D_8010DE68_aces_high[D_8010DE8E_aces_high]);
                    HuAudFXPlay(0x3B4);
                } else {
                    func_800E6F0C_minigame(4);
                    D_8010DB40_aces_high.unk06 = 4;
                    D_8010DE8A_aces_high = 1;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (func_8010D1D8_aces_high(D_8010DE8E_aces_high) == 1) {
                func_800E6F0C_minigame(4);
                D_8010DE8A_aces_high = 3;
                D_8010DB40_aces_high.unk18[0] = D_8010DE8E_aces_high;
                GwPlayer[D_8010DE8E_aces_high].bonusCoin = 10;
                PlayerFXPlay(0x28F, D_8010DE8E_aces_high);
            }
            break;
    }
}

void func_8010CFF8_aces_high(void) {
    s32 count = 0;
    u16 numAlive = 0;
    s16 maxLives = 0;
    u16 alive[4];
    AceHighPlayer *player;
    s32 i;
    omObjData *obj;

    if (D_8010DE90_aces_high == 1) {
        return;
    }
    D_8010DE90_aces_high = 0;
    for (i = 0; i < 4; i++) {
        obj = D_8010DE68_aces_high[i];
        player = obj->data;
        count++;
        if (player->unk_00 == 4 || player->unk_00 == 5) {
            continue;
        }
        if (player->unk_00 == 6) {
            continue;
        }
        alive[numAlive++] = i;
    }
    if (count != 4) {
        return;
    }
    D_8010DE90_aces_high = 1;
    D_8010DE8E_aces_high = -1;
    for (i = 0; i < numAlive; i++) {
        player = D_8010DE68_aces_high[alive[i]]->data;
        if (player->unk_26 > maxLives) {
            maxLives = player->unk_26;
        }
    }
    for (i = 0; i < numAlive; i++) {
        player = D_8010DE68_aces_high[alive[i]]->data;
        if (player->unk_26 != maxLives) {
            continue;
        }
        if (D_8010DE8E_aces_high != -1) {
            D_8010DE8E_aces_high = -1;
            return;
        }
        D_8010DE8E_aces_high = alive[i];
    }
    if (numAlive != 0 && D_8010DE8E_aces_high != -1) {
        obj = D_8010DE68_aces_high[D_8010DE8E_aces_high];
        player = obj->data;
        player->unk_92 = 5;
        player->unk_9C.x = 0.0f;
        player->unk_9C.y = 0.0f;
        player->unk_9C.z = 0.0f;
    }
}

// NON_MATCHING: only register allocation differs. Target keeps the scissor
// walking pointer in s0 and the viewport pointer in s1 (4 saved regs, 0x50
// frame); here one `rect` variable gets s1 for both (s0 is taken by the local
// `winner` zero-extension pseudo that overlaps the viewport part). Using separate
// scissor and viewport variables gets the scissor part in s0, but the viewport
// pointer is then a block-local, non-call-crossing pseudo that local-alloc ties
// to the shift temp (a0, 3 saved regs). To land in s1 it must be a global
// pseudo that crosses a call, yet the target shows no other use of s1 there.
// Writing [1][0]/[3][0] through the global array (instead of rect[0]) is needed
// so the reads after the stores reload from memory. Also tried: per-section
// `rect = D_8010DB70_aces_high[i]`, all-global indexing, a Vec2f pointer for the
// target position, deriving the viewport pointer from rect, do-while(0) around
// the scissor or viewport part, s32 x/y/w/h, declaration order.
#ifdef NON_MATCHING
u16 func_8010D1D8_aces_high(u16 winner) {
    f32 angle;
    f32 moveX;
    f32 moveY;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    f32 *rect;

    angle = atan2df(D_8010DCBC_aces_high[winner].x - D_8010DCB4_aces_high.x,
                    D_8010DCBC_aces_high[winner].y - D_8010DCB4_aces_high.y);
    moveX = sindf(angle) * 2.5f;
    moveY = cosdf(angle) * 2.5f;
    D_8010DCB4_aces_high.x += moveX;
    D_8010DCB4_aces_high.y += moveY;
    if (moveX < 0.0f) {
        if (D_8010DCB4_aces_high.x < D_8010DCBC_aces_high[winner].x) {
            D_8010DCB4_aces_high.x = D_8010DCBC_aces_high[winner].x;
        }
    } else if (D_8010DCB4_aces_high.x > D_8010DCBC_aces_high[winner].x) {
        D_8010DCB4_aces_high.x = D_8010DCBC_aces_high[winner].x;
    }
    if (moveY < 0.0f) {
        if (D_8010DCB4_aces_high.y < D_8010DCBC_aces_high[winner].y) {
            D_8010DCB4_aces_high.y = D_8010DCBC_aces_high[winner].y;
        }
    } else if (D_8010DCB4_aces_high.y > D_8010DCBC_aces_high[winner].y) {
        D_8010DCB4_aces_high.y = D_8010DCBC_aces_high[winner].y;
    }
    rect = D_8010DB70_aces_high[0];
    rect[2] = D_8010DCB4_aces_high.x - 1.0f;
    rect[3] = D_8010DCB4_aces_high.y - 1.0f;
    ScissorSet(0, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    D_8010DB70_aces_high[1][0] = D_8010DCB4_aces_high.x + 1.0f;
    rect[3] = D_8010DCB4_aces_high.y - 1.0f;
    ScissorSet(1, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    rect[2] = D_8010DCB4_aces_high.x - 1.0f;
    rect[1] = D_8010DCB4_aces_high.y + 1.0f;
    ScissorSet(2, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    D_8010DB70_aces_high[3][0] = D_8010DCB4_aces_high.x + 1.0f;
    rect[1] = D_8010DCB4_aces_high.y + 1.0f;
    ScissorSet(3, rect[0], rect[1], rect[2], rect[3]);
    rect = D_8010DBB0_aces_high[winner];
    x = rect[0] + fabs(D_8010DCB4_aces_high.x - 160.0f) * 320.0 / 158.0;
    y = rect[1] + fabs(D_8010DCB4_aces_high.y - 120.0f) * 240.0 / 118.0;
    w = (D_8010DCB4_aces_high.x - 160.0f) * 320.0f / 158.0f + rect[2];
    h = (D_8010DCB4_aces_high.y - 120.0f) * 240.0f / 158.0f + rect[3];
    ViewportSet(winner, x, y, 511.0f, w, h, 511.0f);
    espPosSet(D_8010DE92_aces_high, 160, D_8010DCB4_aces_high.y);
    espPosSet(D_8010DE94_aces_high, D_8010DCB4_aces_high.x, 120);
    return D_8010DCB4_aces_high.x == D_8010DCBC_aces_high[winner].x &&
           D_8010DCB4_aces_high.y == D_8010DCBC_aces_high[winner].y;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_17_aces_high/1C4280", func_8010D1D8_aces_high);
#endif

void func_8010D6D4_aces_high(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[3];
    AceHighPlayer *player = playerObj->data;
    Vec pos;
    Vec2f screen;
    f32 scale;
    f32 minX;
    f32 maxX;
    f32 minY;
    f32 maxY;

    if (object->work[2] == 0) {
        espDispOff(player->unk_2E);
        if (player->unk_2C != -1) {
            HuAudFXStop(player->unk_2C);
            player->unk_2C = -1;
        }
    } else if (object->work[0] != 0 && player->unk_70 != 0) {
        object->work[0]--;
        if (object->work[1] != 0) {
            scale = 1.2f;
            object->scale.y = 0.0f;
            object->work[1]--;
        } else {
            scale = 1.0f - sindf(object->scale.y) * 0.25f;
            object->scale.y += 30.0f;
            if (object->scale.y >= 360.0f) {
                object->scale.y -= 360.0f;
            }
        }
        pos.x = playerObj->trans.x;
        pos.y = playerObj->trans.y + 160.0f + playerObj->trans.y / 25.0f;
        pos.z = playerObj->trans.z;
        func_80012B14_main(player->camIdx, &pos, &screen);
        minX = minY = 15.400001f;
        maxX = 144.6f;
        maxY = 104.6f;
        if (player->camIdx & 1) {
            minX = 175.4f;
            maxX = 304.6f;
        }
        if (player->camIdx >= 2) {
            minY += 120.0f;
            maxY += 120.0f;
        }
        if (screen.x < minX) {
            screen.x = minX;
        }
        if (screen.x > maxX) {
            screen.x = maxX;
        }
        if (screen.y < minY) {
            screen.y = minY;
        }
        if (screen.y > maxY) {
            screen.y = maxY;
        }
        espPosSet(player->unk_2E, screen.x, screen.y);
        espScaleSet(player->unk_2E, scale, scale);
        espDispOn(player->unk_2E);
        if (player->unk_2C == -1) {
            player->unk_2C = func_8004AC98_main(0x3B1, player->camIdx);
        }
    } else {
        object->work[2] = 0;
    }
}

void func_8010D994_aces_high(omObjData *object) {
    AceHighPlayer *player = ((omObjData *)object->work[0])->data;

    if (object->work[1] == 0) {
        espDispOff(player->unk_30);
        return;
    }
    switch (object->work[1]) {
        case 1:
            if (object->scale.x < 1.0f) {
                object->scale.x += 0.2f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
            } else {
                object->scale.x = 1.0f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
                object->work[1] = 2;
            }
        case 2:
            if (player->unk_70 == 0) {
                object->work[1] = 3;
            }
            break;
        case 3:
            if (object->scale.x > 0.0f) {
                object->scale.x -= 0.200001f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
            } else {
                object->scale.x = 0.0f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
                object->work[1] = 0;
            }
            break;
    }
    espDispOn(player->unk_30);
}
