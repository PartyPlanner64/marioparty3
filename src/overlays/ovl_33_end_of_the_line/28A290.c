#include "common.h"
#include "overlays/minigame.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the group 0 player objects.
typedef struct EndOfTheLinePlayer {
    /* 0x00 */ u16 playerIdx;
    /* 0x02 */ char unk02[0x1E];
    /* 0x20 */ omObjData *obj;
} EndOfTheLinePlayer; // sizeof 0x24 (0x94 bytes are allocated for it)

// State for the whole minigame. Lives in the `data` pointer (0x5C) of the main
// object, D_8010C738_end_of_the_line. The esprite handles a player uses are the
// slots at [playerIdx], [playerIdx + 2], [playerIdx + 4], ...
typedef struct EndOfTheLineData {
    /* 0x00 */ u16 esprites[12];
    /* 0x18 */ char unk18[0x7900];
} EndOfTheLineData; // sizeof 0x7918

extern omObjData *D_8010C738_end_of_the_line;

extern s32 D_8010C730_end_of_the_line;
extern s32 D_8010C734_end_of_the_line;
extern s16 D_8010C758_end_of_the_line;
extern s16 D_8010C75A_end_of_the_line;
extern s16 D_8010C75C_end_of_the_line;
extern s16 D_8010C75E_end_of_the_line[2];
extern s16 D_8010C762_end_of_the_line;
extern s16 D_8010C764_end_of_the_line;
extern s16 D_8010C766_end_of_the_line;
extern s16 D_8010C782_end_of_the_line[3];
extern s16 D_8010C7D0_end_of_the_line;

extern f32 D_8010C5CC_end_of_the_line;
extern f32 D_8010C5D0_end_of_the_line[2];

extern D_80111B50_vine_with_me_Struct D_8010C5A0_end_of_the_line;
// Per-camera scissor (x, y, width, height) and viewport (scale x/y, translate
// x/y) settings.
extern s16 D_8010C600_end_of_the_line[2][4];
extern s16 D_8010C610_end_of_the_line[2][4];
extern omObjData *D_8010C73C_end_of_the_line[2];
extern s16 D_8010C76E_end_of_the_line;
extern s16 D_8010C770_end_of_the_line;
extern s16 D_8010C772_end_of_the_line;
extern s16 D_8010C774_end_of_the_line;
extern s16 D_8010C776_end_of_the_line;
extern s16 D_8010C778_end_of_the_line[2];
extern s16 D_8010C77C_end_of_the_line[2];
extern s16 D_8010C780_end_of_the_line;
extern Vec D_8010C788_end_of_the_line[2];
extern Vec D_8010C7A0_end_of_the_line[2];
extern Vec D_8010C7B8_end_of_the_line[2];

void func_80105E0C_end_of_the_line(omObjData *obj);
void func_80105E88_end_of_the_line(omObjData *obj);
void func_80106444_end_of_the_line(omObjData *obj);
void func_80107F0C_end_of_the_line(void);
void func_801082D8_end_of_the_line(omObjData *obj);
void func_8010AA1C_end_of_the_line(omObjData *obj);
void func_8010C060_end_of_the_line(omObjData *obj);
void func_8010C3F4_end_of_the_line(void);

#ifdef NON_MATCHING
// Matches exactly when compiled with plain -O1, but this file is built with
// -O1 -funroll-loops (needed by func_80105E0C_end_of_the_line), which strength
// reduces the camera loop and unrolls the object creation loop. This function
// likely belongs to a separate source file.
void func_801059A0_end_of_the_line(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(30, 0);
    func_8004A208_main();
    func_80045C2C_main();
    func_8000B690_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        D_8010C7A0_end_of_the_line[i].x = 0.0f;
        D_8010C7A0_end_of_the_line[i].y = 200.0f;
        D_8010C7A0_end_of_the_line[i].z = 0.0f;
        D_8010C788_end_of_the_line[i].x = 0.0f;
        D_8010C788_end_of_the_line[i].y = 300.0f;
        D_8010C788_end_of_the_line[i].z = 1000.0f;
        D_8010C7B8_end_of_the_line[i].x = 0.0f;
        D_8010C7B8_end_of_the_line[i].y = 0.1f;
        D_8010C7B8_end_of_the_line[i].z = 0.0f;
        Hu3DCameraPerspectiveSet(i, 60.0f, 80.0f, 20000.0f);
        ScissorSet(i, D_8010C600_end_of_the_line[i][0], D_8010C600_end_of_the_line[i][1],
                   D_8010C600_end_of_the_line[i][2], D_8010C600_end_of_the_line[i][3]);
        ViewportSet(i, D_8010C610_end_of_the_line[i][0], D_8010C610_end_of_the_line[i][1], 511.0f,
                    D_8010C610_end_of_the_line[i][2], D_8010C610_end_of_the_line[i][3], 511.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, func_8010C060_end_of_the_line);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105E0C_end_of_the_line);
    D_8010C738_end_of_the_line = omAddObj(10, 30, 0, -1, func_80106444_end_of_the_line);
    omSetStatBit(D_8010C738_end_of_the_line, OM_STAT_MODELPAUSE);
    for (i = 0; i < 2; i++) {
        obj = omAddObj(20, 6, 12, -1, func_801082D8_end_of_the_line);
        D_8010C73C_end_of_the_line[i] = obj;
        obj->work[0] = i;
    }
    D_8010C76E_end_of_the_line = func_8000B838_main(0x54001A);
    D_8010C770_end_of_the_line = func_8000B838_main(0x540018);
    D_8010C772_end_of_the_line = func_8000B838_main(0x540019);
    D_8010C774_end_of_the_line = func_8000B838_main(0x540013);
    D_8010C776_end_of_the_line = func_8000B838_main(0x54001B);
    D_8010C778_end_of_the_line[0] = func_8000B838_main(0x540015);
    D_8010C778_end_of_the_line[1] = func_8000B838_main(0x540014);
    D_8010C77C_end_of_the_line[0] = func_8000B838_main(0x540017);
    D_8010C77C_end_of_the_line[1] = func_8000B838_main(0x540016);
    D_8010C780_end_of_the_line = func_8000B838_main(0x38001F);
    func_80107F0C_end_of_the_line();
    func_8010C3F4_end_of_the_line();
    func_800E5EA0_minigame(&D_8010C5A0_end_of_the_line);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801059A0_end_of_the_line);
#endif

void func_80105E0C_end_of_the_line(omObjData *obj) {
    int i;

    D_8010C734_end_of_the_line = 0;
    D_8010C730_end_of_the_line = 0;
    D_8010C7D0_end_of_the_line = -1;
    D_8010C75A_end_of_the_line = 0;
    D_8010C75C_end_of_the_line = 0;
    D_8010C758_end_of_the_line = 0;
    D_8010C766_end_of_the_line = 0;
    for (i = 0; i < 2; i++) {
        D_8010C75E_end_of_the_line[i] = 0;
    }
    D_8010C762_end_of_the_line = -1;
    D_8010C764_end_of_the_line = -1;
    for (i = 0; i < 2; i++) {
        D_8010C782_end_of_the_line[i] = -1;
    }
    obj->func = func_80105E88_end_of_the_line;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80105E88_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106444_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801069D8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80106CDC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80107FF0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801080C8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801082D8_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_801088A4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80108F0C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010937C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_80109E70_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A17C_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A434_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A708_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A7D0_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010A8B4_end_of_the_line);

void func_8010A91C_end_of_the_line(omObjData *obj, s32 arg1) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLineData *data;

    if (player->obj != NULL) {
        return;
    }
    player->obj = omAddObj(0x28, 0, 0, -1, func_8010AA1C_end_of_the_line);
    player->obj->work[0] = player->playerIdx;
    player->obj->work[1] = 1;
    player->obj->work[2] = 0;
    player->obj->work[3] = arg1;
    data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    espDispOn(data->esprites[player->playerIdx + 2]);
    espTPLvlSet(data->esprites[player->playerIdx + 2], OM_GET_WORK_PTR(player->obj, s16)[5]);
    espPosSet(data->esprites[player->playerIdx + 2],
                       D_8010C5D0_end_of_the_line[player->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
}

void func_8010AA1C_end_of_the_line(omObjData *obj) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);

    obj->work[2] += obj->work[3];
    if (obj->work[2] >= 0x100) {
        obj->work[2] = 0xFF;
        obj->work[1] = 0;
    }
    espTPLvlSet(data->esprites[obj->work[0] + 2], OM_GET_WORK_PTR(obj, s16)[5]);
}

void func_8010AA7C_end_of_the_line(EndOfTheLinePlayer *player) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    espDispOff(data->esprites[player->playerIdx + 2]);
    omDelObj(player->obj);
    player->obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AAC8_end_of_the_line);

void func_8010ABD4_end_of_the_line(omObjData *obj) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);

    obj->work[2] += obj->work[3];
    if (obj->work[2] >= 0x100) {
        obj->work[2] = 0xFF;
        obj->work[1] = 0;
    }
    espTPLvlSet(data->esprites[obj->work[0] + 4], OM_GET_WORK_PTR(obj, s16)[5]);
}

void func_8010AC34_end_of_the_line(EndOfTheLinePlayer *player) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    espDispOff(data->esprites[player->playerIdx + 4]);
    omDelObj(player->obj);
    player->obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AC80_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010AF28_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B064_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B190_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B234_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B300_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B420_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B4EC_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B588_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010B640_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BE24_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010BF64_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C060_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C110_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C3F4_end_of_the_line);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_33_end_of_the_line/28A290", func_8010C47C_end_of_the_line);

void func_8010C574_end_of_the_line(void) {
}
