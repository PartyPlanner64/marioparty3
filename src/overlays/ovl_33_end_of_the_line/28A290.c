#include "common.h"
#include "math.h"
#include "overlays/minigame.h"

// Per-player state for this minigame. Lives in the `data` pointer (0x5C) of each
// of the group 0 player objects.
typedef struct EndOfTheLinePlayer {
    /* 0x00 */ u16 playerIdx;
    /* 0x02 */ u16 gwPlayerIdx;
    /* 0x04 */ omObjData *unk04;
    /* 0x08 */ omObjFunc unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ omObjData *obj;
    /* 0x24 */ Vec pos;
    /* 0x30 */ Vec rot;
    /* 0x3C */ Vec pos2;
    /* 0x48 */ Vec rot2;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ u16 unk5C;
    /* 0x5E */ u16 esprites[2];
    /* 0x62 */ u16 esprites2[2];
    /* 0x66 */ char unk66[2];
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u16 unk70;
    /* 0x72 */ char unk72[2];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A[3];
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ u16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ u16 unk8A;
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ s16 unk8E;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
} EndOfTheLinePlayer; // sizeof 0x94

// State for the whole minigame. Lives in the `data` pointer (0x5C) of the main
// object, D_8010C738_end_of_the_line. The esprite handles a player uses are the
// slots at [playerIdx], [playerIdx + 2], [playerIdx + 4], ...
typedef struct EndOfTheLineData {
    /* 0x00 */ u16 esprites[12];
    /* 0x18 */ f32 unk18[2][2];
} EndOfTheLineData; // sizeof 0x28

// Work for the objects in D_8010C744_end_of_the_line, which animate up to
// three models rising from a player.
typedef struct EndOfTheLineRiseWork {
    /* 0x00 */ Vec pos[3];
    /* 0x24 */ f32 velY[3];
    /* 0x30 */ s16 timers[3];
    /* 0x36 */ s16 cooldown;
    /* 0x38 */ omObjData *target;
} EndOfTheLineRiseWork; // sizeof 0x3C

// Data for the player's secondary object (EndOfTheLinePlayer.unk04).
typedef struct EndOfTheLinePlayerSubWork {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ u16 unk10;
} EndOfTheLinePlayerSubWork; // sizeof 0x14

extern omObjData *D_8010C738_end_of_the_line;
extern omObjData *D_8010C744_end_of_the_line[2];

extern omObjData *D_8010C730_end_of_the_line;
extern omObjData *D_8010C734_end_of_the_line;
extern u16 D_8010C650_end_of_the_line;
extern u16 D_8010C754_end_of_the_line;
extern u16 D_8010C756_end_of_the_line;
extern u16 D_8010C758_end_of_the_line;
extern u16 D_8010C75A_end_of_the_line;
extern u16 D_8010C75C_end_of_the_line;
extern u16 D_8010C75E_end_of_the_line[2];
extern s16 D_8010C762_end_of_the_line;
extern s32 D_800A178C_main[][6];
extern s16 D_8010C764_end_of_the_line;
extern u16 D_8010C766_end_of_the_line;
extern s16 D_8010C782_end_of_the_line[3];
extern s16 D_8010C7D0_end_of_the_line;

extern s16 D_8010C5C8_end_of_the_line[2];
extern f32 D_8010C5CC_end_of_the_line;
extern s32 D_8010C5D8_end_of_the_line[5];
extern s32 D_8010C5EC_end_of_the_line[5];
extern s32 D_8010C658_end_of_the_line[3];
extern u16 D_8010C768_end_of_the_line[3];
extern f32 D_8010C5D0_end_of_the_line[2];

extern D_80111B50_vine_with_me_Struct D_8010C5A0_end_of_the_line;
// Per-camera scissor (x, y, width, height) and viewport (scale x/y, translate
// x/y) settings.
extern s16 D_8010C600_end_of_the_line[2][4];
// Per-player sound effect IDs.
extern s32 D_8010C620_end_of_the_line[2][6];
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
extern u16 D_8010C664_end_of_the_line[2];
extern f32 D_8010C668_end_of_the_line;
extern f32 D_8010C66C_end_of_the_line;
extern f32 D_8010C670_end_of_the_line[2][5];
extern f32 D_8010C698_end_of_the_line[2][5];
extern Vec D_8010C6C0_end_of_the_line[2];
extern omObjData *D_8010C74C_end_of_the_line[2];

void func_80105E0C_end_of_the_line(omObjData *obj);
void func_80106CDC_end_of_the_line(omObjData *arg0, omObjData *arg1, s32 arg2);
void func_80107FF0_end_of_the_line(u16 playerIdx);
void func_801080C8_end_of_the_line(omObjData *obj);
void func_801088A4_end_of_the_line(omObjData *obj);
void func_80108F0C_end_of_the_line(omObjData *obj);
void func_8010937C_end_of_the_line(omObjData *obj);
void func_80109E70_end_of_the_line(omObjData *obj);
void func_8010A17C_end_of_the_line(omObjData *obj);
void func_8010A434_end_of_the_line(omObjData *obj);
void func_8010A708_end_of_the_line(omObjData *obj);
void func_8010A91C_end_of_the_line(omObjData *obj, s32 arg1);
void func_8010AA7C_end_of_the_line(EndOfTheLinePlayer *player);
void func_8010AAC8_end_of_the_line(omObjData *obj, s32 arg1);
void func_8010ABD4_end_of_the_line(omObjData *obj);
void func_8010AC34_end_of_the_line(EndOfTheLinePlayer *player);
s16 func_8010AC80_end_of_the_line(omObjData *obj);
void func_8010AF28_end_of_the_line(omObjData *obj);
void func_8010B064_end_of_the_line(omObjData *obj);
void func_8010B190_end_of_the_line(omObjData *obj);
void func_8010B234_end_of_the_line(omObjData *obj);
void func_8010B300_end_of_the_line(omObjData *obj);
void func_8010B420_end_of_the_line(omObjData *obj);
void func_8010B4EC_end_of_the_line(omObjData *obj);
void func_8010B588_end_of_the_line(omObjData *obj);
void func_8010B640_end_of_the_line(omObjData *obj);
void func_8010BE24_end_of_the_line(omObjData *obj);
void func_8010BF64_end_of_the_line(omObjData *obj);
void func_8010C110_end_of_the_line(u16 arg0, omObjData *obj, f32 arg2, f32 arg3, f32 arg4);
void func_8010C47C_end_of_the_line(omObjData *obj);
void func_8010C574_end_of_the_line(omObjData *obj);
void func_8010C580_end_of_the_line(void);
void func_80105E88_end_of_the_line(omObjData *obj);
void func_80106444_end_of_the_line(omObjData *obj);
void func_80107F0C_end_of_the_line(void);
void func_801082D8_end_of_the_line(omObjData *obj);
void func_8010AA1C_end_of_the_line(omObjData *obj);
void func_8010C060_end_of_the_line(omObjData *obj);
void func_8010C3F4_end_of_the_line(void);

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
        D_8010C73C_end_of_the_line[i] = obj = omAddObj(20, 6, 12, -1, func_801082D8_end_of_the_line);
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

void func_80105E0C_end_of_the_line(omObjData *obj) {
    D_8010C734_end_of_the_line = 0;
    D_8010C730_end_of_the_line = 0;
    D_8010C7D0_end_of_the_line = -1;
    D_8010C75A_end_of_the_line = 0;
    D_8010C75C_end_of_the_line = 0;
    D_8010C758_end_of_the_line = 0;
    D_8010C766_end_of_the_line = 0;
    D_8010C75E_end_of_the_line[0] = D_8010C75E_end_of_the_line[1] = 0;
    D_8010C762_end_of_the_line = -1;
    D_8010C764_end_of_the_line = -1;
    D_8010C782_end_of_the_line[0] = D_8010C782_end_of_the_line[1] = -1;
    obj->func = func_80105E88_end_of_the_line;
}

void func_80105E88_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player;
    EndOfTheLinePlayer *player2;
    s32 count;
    s32 i;

    if (D_8010C650_end_of_the_line == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010C730_end_of_the_line == NULL) {
                    D_8010C754_end_of_the_line = 0;
                    D_8010C730_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010AF28_end_of_the_line);
                    D_8010C730_end_of_the_line->work[0] = 0;
                    D_8010C730_end_of_the_line->work[1] = 0;
                }
                break;
            case 2:
                if (D_8010C758_end_of_the_line == 1) {
                    count = 0;
                    for (i = 0; i < 2; i++) {
                        if (D_8010C75E_end_of_the_line[i] == 1) {
                            D_8010C7D0_end_of_the_line = i;
                            count++;
                        }
                    }
                    if (count == 2) {
                        D_8010C5A0_end_of_the_line.unk06 = 4;
                        D_8010C75C_end_of_the_line = 1;
                    } else if (D_8010C75A_end_of_the_line == 0) {
                        player = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[D_8010C7D0_end_of_the_line ^ 1],
                                                 EndOfTheLinePlayer);
                        if (player->unk18 == 2) {
                            player->unk0C = 0;
                        }
                        if (player->unk86 != -1) {
                            HuAudFXStop(player->unk86);
                            player->unk86 = -1;
                        }
                    }
                    func_800E6F0C_minigame(3);
                } else if (func_800E6E9C_minigame() == 9000 || D_8010C75A_end_of_the_line == 1) {
                    D_8010C75A_end_of_the_line = 1;
                    D_8010C75C_end_of_the_line = 1;
                    func_8003F578_main(0);
                    player = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[0], EndOfTheLinePlayer);
                    player2 = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[1], EndOfTheLinePlayer);
                    if (player->unk18 == 1 && player2->unk18 == player->unk18) {
                        D_8010C5A0_end_of_the_line.unk06 = 4;
                        func_800E6F0C_minigame(3);
                        D_8010C5A0_end_of_the_line.unk22 = 60;
                        D_8010C734_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010B064_end_of_the_line);
                        D_8010C756_end_of_the_line = 3;
                    }
                }
                break;
            case 1:
            case 3:
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                D_8010C650_end_of_the_line = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010C580_end_of_the_line();
    }

    for (i = 0; i < 2; i++) {
        if (D_8010C782_end_of_the_line[i] < 0) {
            continue;
        }
        player = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer);
        if ((D_8010C782_end_of_the_line[i] & 0xF) == 4) {
            if (D_8010C75C_end_of_the_line == 0) {
                if (D_8010C782_end_of_the_line[i] & 0x10) {
                    func_8010AA7C_end_of_the_line(player);
                }
                if (D_8010C782_end_of_the_line[i] & 0x20) {
                    func_8010AC34_end_of_the_line(OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer));
                }
                func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i],
                                              D_8010C782_end_of_the_line[i] & 0xF);
                player->unk5C = 7;
                D_8010C73C_end_of_the_line[i]->func = func_8010A434_end_of_the_line;
                func_80107FF0_end_of_the_line(player->playerIdx);
                player->unk04->work[2] = 0;
                player->unk04->func = func_8010B640_end_of_the_line;
            } else {
                if (D_8010C782_end_of_the_line[i] & 0x10) {
                    func_8010AA7C_end_of_the_line(OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer));
                }
                if (D_8010C782_end_of_the_line[i] & 0x20) {
                    func_8010AC34_end_of_the_line(OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer));
                }
                func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i], 6);
                player->unk5C = 7;
                D_8010C73C_end_of_the_line[i]->func = func_8010A434_end_of_the_line;
                func_80107FF0_end_of_the_line(player->playerIdx);
                player->unk04->work[2] = 0;
                player->unk04->func = func_8010BF64_end_of_the_line;
            }
            if (D_8010C734_end_of_the_line == NULL) {
                if (D_8010C75C_end_of_the_line == 0) {
                    D_8010C756_end_of_the_line = 0;
                } else {
                    D_8010C756_end_of_the_line = 1;
                }
                D_8010C734_end_of_the_line = omAddObj(4, 0, 0, -1, func_8010B064_end_of_the_line);
            }
        } else {
            if (D_8010C782_end_of_the_line[i] & 0x10) {
                func_8010AA7C_end_of_the_line(OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer));
            }
            if (D_8010C782_end_of_the_line[i] & 0x20) {
                func_8010AC34_end_of_the_line(OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer));
            }
            func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, D_8010C73C_end_of_the_line[i],
                                          D_8010C782_end_of_the_line[i] & 0xF);
            if (D_8010C782_end_of_the_line[i] & 0x40) {
                player->pos2.y = 200.0f;
            }
            if (D_8010C782_end_of_the_line[i] & 0x80) {
                player->unk04->func = player->unk08;
            }
            if ((D_8010C782_end_of_the_line[i] & 0xF) == 3) {
                omVibrate(player->gwPlayerIdx, 20, 0, 20);
            }
        }
        D_8010C782_end_of_the_line[i] = -1;
    }
}

void func_80106444_end_of_the_line(omObjData *obj) {
    EndOfTheLineData *data;
    s32 i;
    s32 j;

    data = obj->data = HuMemAllocTag(sizeof(EndOfTheLineData), TAG_OVERLAY);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x540002, 0x6DD);
            obj->model[4] = func_8000B108_main(0x540003, 0x6DD);
            obj->model[12] = func_8000B108_main(0x540004, 0x6DD);
            obj->model[14] = func_8000B108_main(0x540008, 0x6DD);
            obj->model[16] = func_8000B108_main(0x540009, 0x6DD);
            obj->model[18] = func_8000B108_main(0x54000A, 0x6DD);
            for (j = 0; j < 5; j++) {
                obj->model[20 + j * 2] = func_8000B108_main(D_8010C5D8_end_of_the_line[j], D_8010C5EC_end_of_the_line[j]);
            }
        } else {
            obj->model[2] = Hu3DModelLink(obj->model[0]);
            obj->model[5] = Hu3DModelLink(obj->model[4]);
            obj->model[13] = Hu3DModelLink(obj->model[12]);
            obj->model[15] = Hu3DModelLink(obj->model[14]);
            obj->model[17] = Hu3DModelLink(obj->model[16]);
            obj->model[19] = Hu3DModelLink(obj->model[18]);
            for (j = 0; j < 5; j++) {
                obj->model[21 + j * 2] = Hu3DModelLink(obj->model[20 + j * 2]);
            }
        }
        Hu3DModelCameraSet(obj->model[i * 2], D_8010C5C8_end_of_the_line[i]);
        Hu3DModelCameraSet(obj->model[4 + i], D_8010C5C8_end_of_the_line[i]);
        Hu3DModelCameraSet(obj->model[12 + i], D_8010C5C8_end_of_the_line[i]);
        Hu3DModelCameraSet(obj->model[14 + i], D_8010C5C8_end_of_the_line[i]);
        Hu3DModelCameraSet(obj->model[16 + i], D_8010C5C8_end_of_the_line[i]);
        Hu3DModelCameraSet(obj->model[18 + i], D_8010C5C8_end_of_the_line[i]);
        func_8001C2FC_main(obj->model[18 + i], 0x70000000, 0x70000000);
        for (j = 0; j < 5; j++) {
            func_8001C2FC_main(obj->model[20 + j * 2 + i], 0x70000000, 0x70000000);
            Hu3DModelCameraSet(obj->model[20 + j * 2 + i], D_8010C5C8_end_of_the_line[i]);
        }
        for (j = 0; j < 1; j++) {
            obj->model[i * 2 + 1 + j] = Hu3DModelLink(obj->model[0]);
            Hu3DModelCameraSet(obj->model[i * 2 + 1 + j], D_8010C5C8_end_of_the_line[i]);
        }
        for (j = 0; j < 3; j++) {
            if (i == 0) {
                obj->model[6 + j] = func_8000B108_main(D_8010C658_end_of_the_line[j], 0x6DD);
            } else {
                obj->model[9 + j] = Hu3DModelLink(obj->model[6 + j]);
            }
            Hu3DModelCameraSet(obj->model[6 + i * 3 + j], D_8010C5C8_end_of_the_line[i]);
        }
        data->esprites[i] = espEntry(D_8010C76E_end_of_the_line, 0, 0);
        data->esprites[i + 2] = espEntry(D_8010C772_end_of_the_line, 0, 0);
        data->esprites[i + 4] = espEntry(D_8010C770_end_of_the_line, 0, 0);
        data->esprites[i + 6] = espEntry(D_8010C774_end_of_the_line, 0, 0);
        data->esprites[i + 8] = espEntry(D_8010C776_end_of_the_line, 0, 0);
        espPosSet(data->esprites[i], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 2], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 4], i * 160 + 80, 120);
        espPosSet(data->esprites[i + 8], i * 160 + 80, 120);
        espDispOff(data->esprites[i]);
        espDispOff(data->esprites[i + 2]);
        espDispOff(data->esprites[i + 4]);
        espDispOff(data->esprites[i + 6]);
        espDispOff(data->esprites[i + 8]);
        espAttrSet(data->esprites[i], 0x4000);
        espAttrSet(data->esprites[i + 6], 0x4008);
        espAttrSet(data->esprites[i + 8], 0x4008);
        espPriSet(data->esprites[i + 2], 0x80C8);
        espPriSet(data->esprites[i + 4], 0x8190);
    }
    data->esprites[10] = espEntry(D_8010C780_end_of_the_line, 0, 0);
    espPosSet(data->esprites[10], 160, 120);
    espPriSet(data->esprites[10], 0x8064);
    for (i = 0; i < 3; i++) {
        D_8010C768_end_of_the_line[i] = rand8() < 0x80;
    }
    obj->work[0] = 0;
    obj->func = NULL;
}

void func_801069D8_end_of_the_line(omObjData *obj) {
    EndOfTheLineData *data = OM_GET_DATA_PTR(obj, EndOfTheLineData);
    EndOfTheLinePlayer *player;
    omObjData *playerObj;
    f32 offset;
    s32 front;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            data->unk18[i][j] += 37.037037f;
            Hu3DModelPosSet(obj->model[i * 2 + j], 0.0f, 0.0f, data->unk18[i][j]);
            if (data->unk18[i][j] >= 3300.0f) {
                data->unk18[i][j] -= 6600.0f;
            }
        }
        if (obj->work[0] == 1) {
            if (data->unk18[0][0] > data->unk18[0][1]) {
                front = 1;
            } else {
                front = 0;
            }
            func_80106CDC_end_of_the_line(obj, D_8010C73C_end_of_the_line[0], 1);
            func_80106CDC_end_of_the_line(obj, D_8010C73C_end_of_the_line[1], 1);
            offset = data->unk18[0][front];
            for (j = 0; j < 2; j++) {
                playerObj = D_8010C73C_end_of_the_line[j];
                player = OM_GET_DATA_PTR(playerObj, EndOfTheLinePlayer);
                playerObj->trans.z -= offset;
                player->pos.z -= offset;
                Hu3DModelPosSet(playerObj->model[1], player->pos.x, player->pos.y, player->pos.z);
                Hu3DModelRotSet(playerObj->model[1], player->rot.x, player->rot.y, player->rot.z);
                Hu3DModelPosSet(playerObj->model[2], player->pos.x - sindf(player->rot.y) * 20.0f,
                                player->pos.y + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
                Hu3DModelRotSet(playerObj->model[2], 0.0f, player->rot.y, 0.0f);
                Hu3DModelScaleSet(playerObj->model[4], 1.0f, 1.0f, 1.0f);
                Hu3DModelPosSet(playerObj->model[4], player->pos.x - sindf(player->rot.y) * 20.0f,
                                player->pos.y + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
            }
            obj->func = NULL;
            return;
        }
    }
}

void func_80106CDC_end_of_the_line(omObjData *arg0, omObjData *arg1, s32 arg2) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(arg1, EndOfTheLinePlayer);
    u16 idx = player->playerIdx;
    EndOfTheLineData *data = OM_GET_DATA_PTR(arg0, EndOfTheLineData);
    s32 i;

    func_8001C258_main(arg0->model[idx * 2], 4, 4);
    func_8001C258_main(arg0->model[idx * 2 + 1], 4, 4);
    func_8001C258_main(arg0->model[4 + idx], 4, 4);
    func_8001C258_main(arg0->model[12 + idx], 4, 4);
    func_8001C258_main(arg0->model[14 + idx], 4, 4);
    func_8001C258_main(arg0->model[16 + idx], 4, 4);
    func_8001C258_main(arg0->model[18 + idx], 4, 4);
    for (i = 0; i < 5; i++) {
        func_8001C258_main(arg0->model[20 + i * 2 + idx], 4, 4);
    }
    func_8001C258_main(arg0->model[6 + idx * 3], 4, 4);
    func_8001C258_main(arg0->model[6 + idx * 3 + 1], 4, 4);
    func_8001C258_main(arg0->model[6 + idx * 3 + 2], 4, 4);
    func_8001C258_main(arg1->model[0], 4, 4);
    func_8001C258_main(arg1->model[1], 4, 4);
    func_8001C258_main(arg1->model[2], 4, 4);
    func_8001C258_main(arg1->model[3], 4, 4);
    func_8001C258_main(arg1->model[4], 4, 4);
    func_8001C258_main(arg1->model[5], 4, 4);
    espDispOff(data->esprites[idx]);
    espDispOff(player->esprites[0]);
    espDispOff(player->esprites[1]);
    espDispOff(player->esprites2[0]);
    espDispOff(player->esprites2[1]);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    player->unk18 = arg2;
    player->unk88 = 0x48;
    switch ((s16)arg2) {
        case 0:
            Hu3DGLightDirSet(1, 44.0f, 82.0f, -74.0f);
            func_8001C258_main(arg0->model[16 + idx], 4, 0);
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            omSetTra(arg1, 0.0f, 0.0f, 2000.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = arg1->trans.z + 237.5f + 105.0f + 50.0f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            player->pos2.x = 0.0f;
            player->pos2.y = 0.0f;
            player->pos2.z = 0.0f;
            player->rot2.x = 0.0f;
            player->rot2.y = 180.0f;
            player->rot2.z = 0.0f;
            Hu3DModelPosSet(arg1->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelRotSet(arg1->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
            espDispOn(data->esprites[idx]);
            for (i = 0; i < 5; i++) {
                func_8001C258_main(arg0->model[20 + i * 2 + idx], 4, 0);
            }
            func_8001C258_main(arg0->model[18 + idx], 4, 0);
            Hu3DModelPosSet(arg0->model[18 + idx], -1000.0f, 4000.0f, 0.0f);
            Hu3DModelScaleSet(arg0->model[18 + idx], 4.5f, 4.5f, 4.5f);
            break;
        case 1:
            func_8001C258_main(arg0->model[idx * 2], 4, 0);
            func_8001C258_main(arg0->model[4 + idx], 4, 0);
            func_8001C258_main(arg0->model[6 + idx * 3 + player->unk16], 4, 0);
            Hu3DModelPosSet(arg0->model[idx * 2], 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(arg0->model[4 + idx], 0.0f, 0.0f, -3300.0f);
            Hu3DModelPosSet(arg0->model[6 + idx * 3 + player->unk16], 0.0f, 0.0f, -3150.0f);
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 292.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            player->pos2.y = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos2.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos2.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            func_8001C258_main(arg1->model[4], 4, 0);
            espDispOn(data->esprites[idx]);
            espPosSet(data->esprites[player->playerIdx],
                      D_8010C5D0_end_of_the_line[player->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            if (D_8010C75A_end_of_the_line != 0) {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            } else if (D_8010C758_end_of_the_line == 0) {
                player->unk0C = 40.0f;
                player->unk88 = 0x48;
            } else {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            }
            player->unk68 = 0.0f;
            if (player->unk86 != -1) {
                func_80007D2C_main(player->unk86, 22);
            }
            break;
        case 2:
            func_8001C258_main(arg0->model[14 + idx], 4, 0);
            Hu3DModelPosSet(arg0->model[14 + idx], 0.0f, 0.0f, -1650.0f);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[2], arg1->trans.x, arg1->trans.y + 100.0f, arg1->trans.z + 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            if (D_8010C758_end_of_the_line == 0) {
                player->unk0C = 40.0f;
                player->unk88 = 0x48;
            } else {
                player->unk0C = 0.0f;
                player->unk88 = 0;
            }
            break;
        case 3:
            player->unk88 = 0;
            player->unk54 = 345.0f;
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            for (i = 0; i < 5; i++) {
                func_8001C258_main(arg0->model[20 + i * 2 + idx], 4, 0);
            }
            func_8001C258_main(arg0->model[12 + idx], 4, 0);
            Hu3DModelPosSet(arg0->model[12 + idx], 0.0f, 0.0f, 0.0f);
            func_8001C258_main(arg0->model[18 + idx], 4, 0);
            Hu3DModelPosSet(arg0->model[18 + idx], 1000.0f, 2500.0f, 900.0f);
            Hu3DModelScaleSet(arg0->model[18 + idx], 5.0f, 5.0f, 5.0f);
            omSetTra(arg1, -500.0f, -sindf(player->unk54) * 447.5f, -500.0f);
            omSetRot(arg1, player->unk54, 0.0f, 0.0f);
            player->pos.x = -500.0f;
            player->pos.y = -sindf(player->unk54) * 105.0f;
            player->pos.z = -792.5f;
            player->rot.x = player->unk54;
            player->rot.y = 0.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f,
                            -sindf(player->unk54) * 85.0f + 100.0f, player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            espDispOn(data->esprites[idx]);
            espPosSet(data->esprites[player->playerIdx],
                      D_8010C5D0_end_of_the_line[player->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            player->unk0C = 48.0f;
            break;
        case 4:
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            omSetTra(arg1, 0.0f, 0.0f, 950.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 1242.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            func_8001C258_main(arg1->model[4], 4, 0);
            espDispOn(data->esprites[idx + 6]);
            if (idx == 0) {
                espPosSet(data->esprites[6], 0, 0x78);
            } else {
                espPosSet(data->esprites[idx + 6], 320, 0x78);
            }
            player->unk88 = 0x48;
            if (player->unk86 != -1) {
                func_80007D2C_main(player->unk86, 22);
            }
            break;
        case 5:
            func_8001C258_main(arg0->model[idx * 2], 4, 0);
            func_8001C258_main(arg0->model[idx * 2 + 1], 4, 0);
            data->unk18[idx][0] = 1650.0f;
            data->unk18[idx][1] = -1650.0f;
            Hu3DModelPosSet(arg0->model[idx * 2], 0.0f, 0.0f, data->unk18[idx][0]);
            Hu3DModelPosSet(arg0->model[idx * 2 + 1], 0.0f, 0.0f, data->unk18[idx][1]);
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            omSetTra(arg1, 0.0f, 0.0f, 0.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 292.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            player->pos2.x = player->pos.x - sindf(player->rot.y) * 20.0f;
            player->pos2.y = player->pos.y + 700.0f + 100.0f;
            player->pos2.z = player->pos.z - cosdf(player->rot.y) * 20.0f;
            player->rot2.x = 0.0f;
            player->rot2.y = 180.0f;
            player->rot2.z = 0.0f;
            Hu3DModelPosSet(arg1->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelRotSet(arg1->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
            func_8001C258_main(arg1->model[4], 4, 0);
            Hu3DModelPosSet(arg1->model[4], player->pos2.x, 100.0f, player->pos2.z);
            player->unk6C = 0.1f;
            espDispOn(data->esprites[idx]);
            D_8010C738_end_of_the_line->func = func_801069D8_end_of_the_line;
            break;
        case 6:
            func_8001C258_main(arg1->model[0], 4, 0);
            func_8001C258_main(arg1->model[1], 4, 0);
            func_8001C258_main(arg1->model[2], 4, 0);
            omSetTra(arg1, 0.0f, 0.0f, 950.0f);
            omSetRot(arg1, 0.0f, 180.0f, 0.0f);
            player->pos.x = 0.0f;
            player->pos.y = 0.0f;
            player->pos.z = 1242.5f;
            player->rot.x = 0.0f;
            player->rot.y = 180.0f;
            player->rot.z = 0.0f;
            Hu3DModelPosSet(arg1->model[1], player->pos.x, player->pos.y, player->pos.z);
            Hu3DModelRotSet(arg1->model[1], player->rot.x, player->rot.y, player->rot.z);
            Hu3DModelPosSet(arg1->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            Hu3DModelRotSet(arg1->model[2], 0.0f, 180.0f, 0.0f);
            Hu3DModelPosSet(arg1->model[4], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                            player->pos.z - cosdf(player->rot.y) * 20.0f);
            func_8001C258_main(arg1->model[4], 4, 0);
            espDispOn(data->esprites[idx + 8]);
            if (idx == 0) {
                espPosSet(data->esprites[6], 0, 0x78);
            } else {
                espPosSet(data->esprites[idx + 6], 320, 0x78);
            }
            break;
    }
    if (player->unk86 != -1) {
        HuAudFXVolSet(player->unk86, player->unk88);
    }
}

void func_80107F0C_end_of_the_line(void) {
    omObjData *obj;
    EndOfTheLineRiseWork *work;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        D_8010C744_end_of_the_line[i] = obj = omAddObj(0x28, 3, 0, -1, NULL);
        omSetStatBit(obj, OM_STAT_MODELPAUSE);
        work = obj->data = HuMemAllocTag(sizeof(EndOfTheLineRiseWork), TAG_OVERLAY);
        for (j = 0; j < 3; j++) {
            work->timers[j] = 0;
            obj->model[j] = func_8000B108_main(0x540010, 0xA8D);
        }
        work->cooldown = 0;
    }
}

void func_80107FF0_end_of_the_line(u16 playerIdx) {
    EndOfTheLineRiseWork *work = OM_GET_DATA_PTR(D_8010C744_end_of_the_line[playerIdx], EndOfTheLineRiseWork);
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DModelCameraSet(D_8010C744_end_of_the_line[playerIdx]->model[i], D_8010C5C8_end_of_the_line[playerIdx]);
    }
    work->target = D_8010C73C_end_of_the_line[playerIdx];
    D_8010C744_end_of_the_line[playerIdx]->func = func_801080C8_end_of_the_line;
}

void func_801080C8_end_of_the_line(omObjData *obj) {
    EndOfTheLineRiseWork *work = OM_GET_DATA_PTR(obj, EndOfTheLineRiseWork);
    s32 i;

    if (work->cooldown == 0) {
        for (i = 0; i < 3; i++) {
            if (work->timers[i] == 0) {
                break;
            }
        }
        if (i != 3) {
            func_8001C258_main(obj->model[i], 4, 0);
            Hu3DMotionTimeSet(obj->model[i], 0.0f);
            Hu3DModelScaleSet(obj->model[i], 2.0f, 2.0f, 2.0f);
            work->pos[i].x = work->target->trans.x;
            work->pos[i].y = work->target->trans.y + 340.0f;
            work->pos[i].z = work->target->trans.z - 70.0f;
            work->timers[i] = 15;
            work->cooldown = 8;
            work->velY[i] = 13.0f;
        }
    } else {
        work->cooldown--;
    }
    for (i = 0; i < 3; i++) {
        if (work->timers[i] != 0) {
            Hu3DModelPosSet(obj->model[i], work->pos[i].x, work->pos[i].y, work->pos[i].z);
            work->pos[i].y += work->velY[i];
            work->velY[i] *= 0.97f;
            if (--work->timers[i] == 0) {
                func_8001C258_main(obj->model[i], 4, 4);
            }
        }
    }
}

void func_801082D8_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player;
    s32 i;
    s8 chr;

    player = obj->data = HuMemAllocTag(sizeof(EndOfTheLinePlayer), TAG_OVERLAY);
    player->playerIdx = obj->work[0];
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == player->playerIdx) {
            player->gwPlayerIdx = i;
            if (GwPlayer[i].stat & 1) {
                D_8010C762_end_of_the_line++;
            }
            break;
        }
    }
    if (D_8010C762_end_of_the_line == 1) {
        D_8010C764_end_of_the_line = rand8() & 1;
    }
    obj->model[0] = func_8000B108_main(0x540000, 0xAD9);
    obj->model[1] = func_8000B108_main(0x540001, 0xAD9);
    obj->model[5] = func_8000B108_main(0x540011, 0xADD);
    obj->model[3] = func_8000B108_main(0x82, 0xA8D);
    obj->model[4] = func_8000B0D4_main(9, 0xA8D);
    Hu3DModelCameraSet(obj->model[0], D_8010C5C8_end_of_the_line[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[1], D_8010C5C8_end_of_the_line[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[3], D_8010C5C8_end_of_the_line[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[4], D_8010C5C8_end_of_the_line[player->playerIdx]);
    Hu3DModelCameraSet(obj->model[5], D_8010C5C8_end_of_the_line[player->playerIdx]);
    Hu3DLLightCreate(obj->model[5], 1);
    Hu3DLLightColorSet(obj->model[5], 0xFF, 0xFF, 0xFF);
    Hu3DLLightDirSet(obj->model[5], 102.0f, 40.0f, 48.0f);
    chr = GwPlayer[player->gwPlayerIdx].chr;
    obj->model[2] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][1], 0x20AD9);
    Hu3DModelCameraSet(obj->model[2], D_8010C5C8_end_of_the_line[player->playerIdx]);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 0x10));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x11));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x1A));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x2E));
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x1F));
    func_8001C5B4_main(obj->model[2], obj->motion[0]);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C814_main(obj->model[0], 2, 2);
    player->unk04 = omAddObj(0x32, 0, 0, -1, func_8010B190_end_of_the_line);
    player->unk04->data = HuMemAllocTag(sizeof(EndOfTheLinePlayerSubWork), TAG_OVERLAY);
    player->unk04->work[0] = (u32)obj;
    player->unk04->work[1] = 1;
    player->unk16 = 0;
    player->unk10 = 0;
    player->unk14 = 0;
    player->obj = NULL;
    player->unk0C = 40.0f;
    player->unk1A = 4;
    player->unk1C = 0;
    player->unk78 = 15;
    player->unk8A = 20;
    player->unk8C = 0;
    player->unk86 = -1;
    player->esprites[0] = espEntry(D_8010C778_end_of_the_line[0], 0, 0);
    player->esprites[1] = espEntry(D_8010C778_end_of_the_line[1], 0, 0);
    player->esprites2[0] = espEntry(D_8010C77C_end_of_the_line[0], 0, 0);
    player->esprites2[1] = espEntry(D_8010C77C_end_of_the_line[1], 0, 0);
    espTPLvlSet(player->esprites[0], 0xDC);
    espTPLvlSet(player->esprites[1], 0xDC);
    espTPLvlSet(player->esprites2[0], 0xDC);
    espTPLvlSet(player->esprites2[1], 0xDC);
    espDispOff(player->esprites[0]);
    espDispOff(player->esprites[1]);
    espDispOff(player->esprites2[0]);
    espDispOff(player->esprites2[1]);
    for (i = 0; i < 3; i++) {
        player->unk7A[i] = -1;
    }
    player->unk80 = 0;
    player->unk82 = 0;
    func_80106CDC_end_of_the_line(D_8010C738_end_of_the_line, obj, 0);
    player->unk70 = 0;
    player->unk8C = 3;
    obj->func = func_801088A4_end_of_the_line;
}

void func_801088A4_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 dx;
    f32 dz;
    s32 i;

    if (player->pos2.y > 600.0f) {
        for (i = 0; i < 5; i++) {
            func_8001C258_main(D_8010C738_end_of_the_line->model[20 + i * 2 + player->playerIdx], 4, 0);
        }
    } else {
        for (i = 0; i < 5; i++) {
            func_8001C258_main(D_8010C738_end_of_the_line->model[20 + i * 2 + player->playerIdx], 4, 4);
        }
    }
    if (player->unk8A == 0) {
        HuAudFXPlay(D_8010C620_end_of_the_line[player->playerIdx][3]);
        player->unk8A = 30;
    } else {
        player->unk8A--;
    }
    if (player->unk78 != 0) {
        player->unk78--;
    } else if (player->rot2.y > 0.0f) {
        if (player->unk1A != 5 && player->unk70 == 0) {
            func_8001C5B4_main(obj->model[2], obj->motion[1]);
            func_8001C814_main(obj->model[2], 2, 2);
            Hu3DMotionSpeedSet(obj->model[2], 2.0f);
            player->unk1A = 5;
        }
        player->rot2.y -= 20.0f;
        if (player->rot2.y < 0.0f) {
            player->rot2.y = 0.0f;
        }
    } else if (player->rot2.y == 0.0f) {
        if (player->unk1A != 3 && player->unk70 == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[8]].motId, 0, 6, 2);
            Hu3DMotionSpeedSet(obj->model[2], 1.0f);
            player->unk1A = 3;
        }
    }
    if (obj->trans.z < 297.0f && player->unk70 == 0) {
        HuAudFXPlay(D_8010C620_end_of_the_line[player->playerIdx][4]);
        player->unk8E = PlayerFXPlay(0x286, player->gwPlayerIdx);
        player->unk70 = 1;
        player->unk74 = 80.0f;
        player->unk8A = 10000;
        Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[4]].motId, 0, 6, 2);
        func_8001C258_main(obj->model[5], 4, 0);
        Hu3DModelScaleSet(obj->model[5], 1.8f, 1.8f, 1.8f);
        player->unk1E = 7;
    }
    if (player->unk70 == 1) {
        if (player->unk8C == 0) {
            func_80007D2C_main(player->unk8E, 0x40);
        } else {
            player->unk8C--;
        }
    }
    if (obj->trans.z > -100.0f) {
        dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
        dx = sindf(obj->rot.y) * (player->unk0C / 1.08f);
        obj->trans.x += dx;
        obj->trans.z += dz;
        dz = cosdf(player->rot.y) * (player->unk0C / 1.08f);
        dx = sindf(player->rot.y) * (player->unk0C / 1.08f);
        player->pos.x += dx;
        player->pos.z += dz;
        Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    }
    if (player->unk70 == 1) {
        func_8010C110_end_of_the_line(0, obj, -1000.0f, 4000.0f, 0.0f);
        player->pos2.y += player->unk74;
        player->unk74 *= 0.98f;
        if (player->unk74 < 60.0f) {
            player->unk74 = 60.0f;
        }
        if (player->pos2.y > 4000.0f) {
            D_8010C782_end_of_the_line[player->playerIdx] = 0x85;
            player->unk74 = -6.0f;
            player->unk5C = 0;
            func_8001C5B4_main(obj->model[2], obj->motion[5]);
            obj->func = func_80108F0C_end_of_the_line;
            player->unk08 = func_8010B234_end_of_the_line;
        }
        if (player->unk1E != 0) {
            Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, (rand8() / 256.0f) * 360.0f);
            if (--player->unk1E == 0) {
                func_8001C258_main(obj->model[5], 4, 4);
            }
        }
    }
    Hu3DModelPosSet(obj->model[5], player->pos2.x, player->pos2.y + 50.0f, player->pos2.z + 100.0f);
    Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
    Hu3DModelRotSet(obj->model[2], player->rot2.x, player->rot2.y, player->rot2.z);
}

void func_80108F0C_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLinePlayerSubWork *sub;
    f32 scale;

    switch (player->unk5C) {
        case 0:
            player->pos2.y += player->unk74;
            player->unk74 *= 1.15f;
            scale = 1.0f - player->pos2.y / 1000.0f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            player->unk6C = scale;
            if (player->pos2.y < 100.0f) {
                player->pos2.y = 100.0f;
                player->unk74 = 40.0f;
                player->unk5C = 1;
                player->unk6C = 1.0f;
                func_8001C258_main(obj->model[3], 4, 0);
                Hu3DModelPosSet(obj->model[3], player->pos2.x, player->pos2.y, player->pos2.z);
                Hu3DMotionTimeSet(obj->model[3], 0.0f);
                D_8010C730_end_of_the_line->work[0] = 1;
                if (player->playerIdx == 0) {
                    HuAudSeqPlay(0x34);
                }
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            Hu3DModelScaleSet(obj->model[4], player->unk6C, player->unk6C, player->unk6C);
            Hu3DModelPosSet(obj->model[4], player->pos2.x, 100.0f, player->pos2.z);
            break;
        case 1:
            player->pos2.y += player->unk74;
            player->unk74 *= 0.5f;
            if (player->unk74 < 1.0f) {
                player->unk74 = -1.0f;
                player->unk5C = 2;
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            break;
        case 2:
            player->pos2.y += player->unk74;
            player->unk74 += player->unk74;
            if (player->pos2.y < 100.0f) {
                player->pos2.y = 100.0f;
                func_8001C5B4_main(obj->model[2], obj->motion[6]);
                player->unk5C = 3;
                player->unk78 = 22;
            }
            Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y, player->pos2.z);
            break;
        case 3:
            if (player->unk78 == 0) {
                player->unk78 = 30;
                Hu3DMotionSpeedSet(obj->model[2], 2.0f);
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[7]].motId, 0, 6, 0);
                player->unk5C = 4;
            } else {
                player->unk78--;
            }
            break;
        case 4:
            if (player->unk78 == 0) {
                player->unk78 = 20;
                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[8]].motId, 0, 6, 0);
                player->unk5C = 5;
            } else {
                player->unk78--;
            }
            break;
        case 5:
            if (player->unk78 == 0) {
                Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[9]].motId, 0, 6, 2);
                player->unk1A = 0;
                sub = OM_GET_DATA_PTR(player->unk04, EndOfTheLinePlayerSubWork);
                sub->unk10 = 20;
                sub->unk00 = 700.0f;
                sub->unk04 = 600.0f;
                sub->unk08 = -200.0f / sub->unk10;
                sub->unk0C = 400.0f / sub->unk10;
                player->unk04->func = func_8010B300_end_of_the_line;
                player->unk5C = 6;
            } else {
                player->unk78--;
            }
            break;
    }
}

void func_8010937C_end_of_the_line(omObjData *obj) {
    f32 limits[2];
    EndOfTheLinePlayer *player;
    s8 stick;
    f32 dx;
    f32 dz;
    f32 scale;
    f32 speed;
    f32 vol;
    f32 pitch;

    limits[0] = 157.0f;
    limits[1] = 203.0f;
    player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    if (D_8010C75A_end_of_the_line == 1 && player->unk1A != 2) {
        player->unk0C *= 0.7f;
        if (player->unk0C < 2.0f) {
            player->unk0C = 0.0f;
            if (player->unk86 != -1) {
                HuAudFXStop(player->unk86);
                player->unk86 = -1;
            }
            obj->func = NULL;
        }
        if (player->unk86 != -1) {
            speed = player->unk0C;
            if (speed < 8.0f) {
                vol = (speed - 1.0f) * (36.0f / 7.0f) + 36.0f;
                pitch = (speed - 1.0f) * (300.0f / 7.0f) + 300.0f;
                HuAudFXVolSet(player->unk86, vol);
                HuAudFXPitchSet(player->unk86, (s16)pitch);
            }
        }
    } else if (D_8010C758_end_of_the_line == 1) {
        player->unk0C = 0.0f;
        if (player->unk86 != -1) {
            HuAudFXStop(player->unk86);
            player->unk86 = -1;
        }
    }
    if (GwPlayer[player->gwPlayerIdx].stat & 1) {
        stick = func_8010AC80_end_of_the_line(obj);
    } else {
        stick = D_800CBB6E_main[GwPlayer[player->gwPlayerIdx].pad];
    }
    dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
    dx = sindf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.x += dx;
    obj->trans.z += dz;
    if (obj->trans.z < -3300.0f) {
        if (player->unk10 == 0) {
            if (obj->rot.y > limits[0]) {
                obj->rot.y -= 8.0f;
                if (obj->rot.y < limits[0]) {
                    obj->rot.y = limits[0];
                }
            }
        } else {
            if (obj->rot.y < limits[1]) {
                obj->rot.y += 8.0f;
                if (obj->rot.y > limits[1]) {
                    obj->rot.y = limits[1];
                }
            }
        }
        player->unk12 = player->unk10;
        espDispOff(player->esprites[0]);
        espDispOff(player->esprites[1]);
        espDispOff(player->esprites2[0]);
        espDispOff(player->esprites2[1]);
        if (player->unk1A == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[10]].motId, 0, 6, 0);
            player->unk1A = 1;
            player->unk1C = 20;
        }
    } else {
        if (stick < 0) {
            player->unk10 = 1;
        } else if (stick > 0) {
            player->unk10 = 0;
        }
        if (D_8010C75A_end_of_the_line == 0 && D_8010C758_end_of_the_line == 0 &&
            func_800E6E8C_minigame() == 2) {
            if (player->unk14 != player->unk10) {
                HuAudFXPlay(D_8010C620_end_of_the_line[player->playerIdx][0]);
            }
            espDispOn(player->esprites[player->unk10]);
            scale = sindf(player->unk68) * 0.15f + 0.85f;
            espScaleSet(player->esprites[player->unk10], scale, sindf(player->unk68) * 0.15f + 0.85f);
            espPosSet(player->esprites[player->unk10], D_8010C664_end_of_the_line[player->unk10] + player->playerIdx * 160,
                      0x50);
            espDispOff(player->esprites2[player->unk10]);
            espDispOff(player->esprites[player->unk10 ^ 1]);
            espDispOn(player->esprites2[player->unk10 ^ 1]);
            espPosSet(player->esprites2[player->unk10 ^ 1],
                      D_8010C664_end_of_the_line[player->unk10 ^ 1] + player->playerIdx * 160, 0x50);
            espScaleSet(player->esprites2[player->unk10 ^ 1], 0.7f, 0.7f);
            player->unk68 += 30.0f;
            if (player->unk68 >= 360.0f) {
                player->unk68 -= 360.0f;
            }
        } else {
            espDispOff(player->esprites[player->unk10]);
            espDispOff(player->esprites[player->unk10 ^ 1]);
            espDispOff(player->esprites2[player->unk10]);
            espDispOff(player->esprites2[player->unk10 ^ 1]);
        }
    }
    player->unk14 = player->unk10;
    if (obj->trans.z < -4100.0f && player->unk04->work[1] == 1) {
        if (D_8010C758_end_of_the_line == 0 && D_8010C75A_end_of_the_line == 0) {
            HuAudFXPlay(D_8010C620_end_of_the_line[player->playerIdx][3]);
        }
        player->unk04->work[1] = 0;
    }
    if (obj->trans.z < -4600.0f) {
        func_8010A91C_end_of_the_line(obj, 10);
        if (player->unk86 != -1) {
            func_80007D2C_main(player->unk86, 0x3C);
        }
    }
    dz = cosdf(player->rot.y) * (player->unk0C / 1.08f);
    dx = sindf(player->rot.y) * (player->unk0C / 1.08f);
    player->pos.x += dx;
    player->pos.z += dz;
    if (player->pos.z < -3300.0f) {
        if (player->unk10 == 0) {
            if (player->rot.y > limits[0]) {
                player->rot.y -= 8.0f;
                if (player->rot.y < limits[0]) {
                    player->rot.y = limits[0];
                }
            }
        } else {
            if (player->rot.y < limits[1]) {
                player->rot.y += 8.0f;
                if (player->rot.y > limits[1]) {
                    player->rot.y = limits[1];
                }
            }
        }
    }
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    player->pos2.x = player->pos.x - sindf(player->rot.y) * 20.0f;
    player->pos2.z = player->pos.z - cosdf(player->rot.y) * 20.0f;
    if (player->pos2.y > 0.0f) {
        player->pos2.y += player->unk74;
        player->unk74 *= 1.15f;
        if (player->pos2.y < 0.0f) {
            player->pos2.y = 0.0f;
            player->unk1C = 7;
            func_8001C814_main(obj->model[2], 1, 0);
            func_8001C258_main(obj->model[3], 4, 0);
            Hu3DMotionTimeSet(obj->model[3], 0.0f);
        }
    } else if (player->unk1A == 2) {
        if (player->unk1C == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[9]].motId, 0, 12, 2);
            player->unk1A = 0;
        } else {
            player->unk1C--;
        }
    }
    Hu3DModelPosSet(obj->model[3], player->pos2.x, player->pos2.y + 100.0f, player->pos2.z);
    Hu3DModelPosSet(obj->model[2], player->pos2.x, player->pos2.y + 100.0f, player->pos2.z);
    Hu3DModelRotSet(obj->model[2], 0.0f, player->rot.y, 0.0f);
    Hu3DModelPosSet(obj->model[4], player->pos2.x, player->pos.y + 100.0f + 0.0f, player->pos2.z);
    if (player->obj != NULL && player->obj->work[1] == 0 && D_8010C7D0_end_of_the_line == -1) {
        player->unk82 = 0;
        player->unk80 = 0;
        D_8010C782_end_of_the_line[player->playerIdx] = 0x12;
        player->unk04->work[1] = 1;
        obj->func = func_80109E70_end_of_the_line;
        player->unk04->func = func_8010B4EC_end_of_the_line;
    }
    if (player->unk1A == 1) {
        if (player->unk1C == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[0]].motId, 0, 15, 2);
            player->unk1A = 4;
        } else {
            player->unk1C--;
        }
    }
}

void func_80109E70_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 dz;
    s16 fx;

    dz = cosdf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.x += sindf(obj->rot.y) * (player->unk0C / 1.08f);
    obj->trans.z += dz;
    if (obj->trans.z < -650.0f) {
        func_8010AAC8_end_of_the_line(obj, 6);
        if (D_8010C766_end_of_the_line == 0 && player->unk92 == 0) {
            if (player->unk90 == 0) {
                HuAudFXPlay(D_8010C620_end_of_the_line[player->playerIdx][5]);
                player->unk92 = 1;
            } else {
                player->unk90--;
            }
        }
    }
    if (player->obj != NULL && player->obj->work[1] == 0) {
        player->unk10 = 0;
        player->unk14 = 0;
        if (player->unk12 == D_8010C768_end_of_the_line[player->unk16] || D_8010C75A_end_of_the_line == 1) {
            if (D_8010C75A_end_of_the_line == 1) {
                player->unk16 = 0;
            } else {
                player->unk16++;
            }
            if (player->unk16 < 3) {
                D_8010C782_end_of_the_line[player->playerIdx] = 0x21;
                func_8001C5B4_main(obj->model[2], obj->motion[9]);
                func_8001C814_main(obj->model[2], 2, 2);
                player->unk1A = 0;
                obj->func = func_8010937C_end_of_the_line;
                player->unk04->func = func_8010B420_end_of_the_line;
            } else {
                D_8010C758_end_of_the_line = 1;
                D_8010C75E_end_of_the_line[player->playerIdx] = 1;
                D_8010C782_end_of_the_line[player->playerIdx] = 0x24;
                func_8001C5B4_main(obj->model[2], obj->motion[0]);
                player->unk1A = 4;
                obj->func = NULL;
            }
        } else {
            D_8010C782_end_of_the_line[player->playerIdx] = 0x23;
            obj->func = func_8010A17C_end_of_the_line;
            player->unk04->func = func_8010B588_end_of_the_line;
            func_8001C5B4_main(obj->model[2], obj->motion[8]);
            player->unk1A = 3;
            if (D_8010C766_end_of_the_line == 0) {
                fx = PlayerFXPlay(0x286, player->gwPlayerIdx);
                HuAudFXVolSet(fx, 0x5C);
                if (player->playerIdx == 0) {
                    HuAudFXPanning(fx, 0x20);
                } else {
                    HuAudFXPanning(fx, 0x60);
                }
            }
        }
    }
}

void func_8010A17C_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 speed;
    f32 vy;
    f32 dx;
    f32 dz;

    func_8010C110_end_of_the_line(1, obj, 1000.0f, 2500.0f, 900.0f);
    vy = fabsf(sindf(player->unk54));
    speed = (1.0f - vy) * player->unk0C;
    vy = vy * player->unk0C;
    dz = cosdf(obj->rot.y) * (speed / 1.08f);
    dx = sindf(obj->rot.y) * (speed / 1.08f);
    obj->trans.x += dx;
    obj->trans.z += dz;
    obj->trans.y += vy;
    dz = cosdf(player->rot.y) * (speed / 1.08f);
    dx = sindf(player->rot.y) * (speed / 1.08f);
    player->pos.x += dx;
    player->pos.z += dz;
    player->pos.y += vy;
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelPosSet(obj->model[2], player->pos.x - sindf(player->rot.y) * 20.0f, player->pos.y + 100.0f,
                    player->pos.z - cosdf(player->rot.y) * 20.0f);
    Hu3DModelRotSet(obj->model[2], player->unk54, player->rot.y, 0.0f);
    player->unk0C *= 0.99f;
    if (obj->trans.z > 200.0f) {
        func_8010AAC8_end_of_the_line(obj, 8);
    }
    if (player->obj != NULL && player->obj->work[1] == 0) {
        player->unk16 = 0;
        player->unk10 = 0;
        D_8010C782_end_of_the_line[player->playerIdx] = 0x61;
        player->unk74 = -16.0f;
        player->unk04->work[1] = 1;
        func_8001C5B4_main(obj->model[2], obj->motion[11]);
        func_8001C814_main(obj->model[2], 1, 1);
        player->unk1A = 2;
        obj->func = func_8010937C_end_of_the_line;
        player->unk04->func = func_8010B420_end_of_the_line;
    }
}

void func_8010A434_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    f32 vol;
    f32 pitch;

    if (player->unk04->work[2] != 1) {
        return;
    }
    obj->trans.z -= player->unk0C;
    player->pos.z -= player->unk0C;
    Hu3DModelPosSet(obj->model[1], player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(obj->model[1], player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelPosSet(obj->model[2], player->pos.x, player->pos.y + 100.0f, player->pos.z);
    Hu3DModelRotSet(obj->model[2], 0.0f, player->rot.y, 0.0f);
    Hu3DModelPosSet(obj->model[4], player->pos.x, player->pos.y + 100.0f, player->pos.z);
    player->unk0C *= 0.968f;
    if (player->unk86 != -1 && player->unk0C < 8.0f) {
        vol = (player->unk0C - 1.0f) * (36.0f / 7.0f) + 36.0f;
        pitch = (player->unk0C - 1.0f) * (1200.0f / 7.0f) + -600.0f;
        HuAudFXVolSet(player->unk86, vol);
        HuAudFXPitchSet(player->unk86, (s16)pitch);
    }
    if (player->unk0C < 1.0f) {
        player->unk0C = 0.0f;
        player->unk58 = 180.0f;
        if (D_8010C75C_end_of_the_line == 0) {
            HuAudFXPlay(D_8010C620_end_of_the_line[0][2]);
        } else if (player->playerIdx == 0) {
            HuAudFXPlay(D_8010C620_end_of_the_line[1][2]);
        }
        if (player->unk86 != -1) {
            HuAudFXStop(player->unk86);
            player->unk86 = -1;
        }
        func_8010C47C_end_of_the_line(obj);
        if (D_8010C75C_end_of_the_line == 0) {
            Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[1]].motId, 0, 6, 2);
            player->unk5C = 8;
            obj->func = func_8010A708_end_of_the_line;
        } else {
            player->unk5C = 9;
        }
    }
}

void func_8010A708_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);

    player->unk58 -= 5.0f;
    if (player->unk58 < 65.0f) {
        player->unk58 = 65.0f;
        Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[0]].motId, 0, 6, 2);
        player->unk5C = 9;
        obj->func = NULL;
    }
    Hu3DModelRotSet(obj->model[2], 0.0f, player->unk58, 0.0f);
}

void func_8010A7D0_end_of_the_line(void) {
    omObjData *obj = D_8010C73C_end_of_the_line[D_8010C7D0_end_of_the_line];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);

    D_8010C5A0_end_of_the_line.unk18[0] = player->gwPlayerIdx;
    GwPlayer[player->gwPlayerIdx].bonusCoin = 10;
    Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[2]].motId, 0, 6, 0);
    func_80045F1C_main(D_800A178C_main[GwPlayer[player->gwPlayerIdx].chr][0] | 0x2F, -1, 0);
}

void func_8010A8B4_end_of_the_line(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[2], Hu3DData[obj->motion[3]].motId, 0, 6, 0);
    obj->func = NULL;
    func_800E6F0C_minigame(4);
}

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

void func_8010AAC8_end_of_the_line(omObjData *obj, s32 arg1) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    EndOfTheLineData *data;

    if (player->obj != NULL) {
        return;
    }
    player->obj = omAddObj(0x28, 0, 0, -1, func_8010ABD4_end_of_the_line);
    player->obj->work[0] = player->playerIdx;
    player->obj->work[1] = 1;
    player->obj->work[2] = 0;
    player->obj->work[3] = arg1;
    player->unk90 = 0xF;
    player->unk92 = 0;
    data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    espDispOn(data->esprites[player->playerIdx + 4]);
    espTPLvlSet(data->esprites[player->playerIdx + 4], OM_GET_WORK_PTR(player->obj, s16)[5]);
    espPosSet(data->esprites[player->playerIdx + 4],
              D_8010C5D0_end_of_the_line[player->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
}

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

s16 func_8010AC80_end_of_the_line(omObjData *obj) {
    s16 dirs[2];
    EndOfTheLinePlayer *player;
    s32 difficulty;
    u16 dir;

    dirs[0] = 50;
    dirs[1] = -50;
    player = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer);
    if (player->unk16 == 3) {
        return 50;
    }
    difficulty = GwPlayer[player->gwPlayerIdx].cpu_difficulty;
    if (obj->trans.z < -3200.0f) {
        if (player->unk82 != 0) {
            return dirs[player->unk84];
        }
        player->unk82 = 1;
        switch (difficulty) {
            case 0:
                if (rand8() < 190) {
                    goto wrong;
                }
                goto right;
            case 1:
                if (rand8() < 128) {
                    goto random;
                }
                goto right;
            case 2:
                if (player->unk7A[player->unk16] == -1) {
                    goto random;
                }
                if (rand8() < 220) {
                    goto right;
                }
                goto wrong;
            case 3:
                if (player->unk7A[player->unk16] == -1) {
                    goto random;
                }
                if (rand8() < 220) {
                    goto right;
                }
                goto wrong;
            right:
                dir = D_8010C768_end_of_the_line[player->unk16];
                break;
            wrong:
                dir = D_8010C768_end_of_the_line[player->unk16] ^ 1;
                break;
            random:
                dir = (rand8() & 0x80) >> 7;
                break;
        }
        if (D_8010C762_end_of_the_line != 0) {
            if (D_8010C764_end_of_the_line == player->playerIdx) {
                dir = D_8010C768_end_of_the_line[player->unk16];
            } else if (player->unk16 == 2) {
                dir = D_8010C768_end_of_the_line[2] ^ 1;
            }
        }
        player->unk84 = dir;
        player->unk7A[player->unk16] = dir;
    }
    if (player->unk82 == 0) {
        if (player->unk80 != 0) {
            player->unk80--;
        } else {
            player->unk84 = (rand8() & 0x80) >> 7;
            player->unk80 = rand8() % 30 + 10;
        }
    }
    return dirs[player->unk84];
}

void func_8010AF28_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player;
    s32 i;

    switch (D_8010C754_end_of_the_line) {
        case 0:
            WipeCreateIn(0xFF, 16);
            D_8010C754_end_of_the_line = 1;
            break;
        case 1:
            if (WipeStatGet() != 0) {
                break;
            }
            obj->work[1] = 1;
            if (obj->work[0] == 1) {
                omDelObj(obj);
                D_8010C730_end_of_the_line = NULL;
                func_800E6F0C_minigame(1);
            }
            for (i = 0; i < 2; i++) {
                player = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[i], EndOfTheLinePlayer);
                if (player->unk86 == -1) {
                    player->unk86 = HuAudFXPlay(D_8010C620_end_of_the_line[i][1]);
                    player->unk88 = 0x48;
                    HuAudFXVolSet(player->unk86, 0x48);
                    HuAudFXPitchSet(player->unk86, 600);
                    func_80007D2C_main(player->unk86, 22);
                }
            }
            break;
    }
}

void func_8010B064_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player =
        OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[D_8010C7D0_end_of_the_line], EndOfTheLinePlayer);

    switch (D_8010C756_end_of_the_line) {
        case 0:
            if (player->unk5C == 8) {
                D_8010C756_end_of_the_line = 1;
                player->unk04->func = func_8010BE24_end_of_the_line;
            }
            break;
        case 1:
            if (player->unk5C == 9) {
                if (D_8010C75C_end_of_the_line == 0) {
                    func_8010A7D0_end_of_the_line();
                } else {
                    func_8010A8B4_end_of_the_line(D_8010C73C_end_of_the_line[0]);
                    func_8010A8B4_end_of_the_line(D_8010C73C_end_of_the_line[1]);
                }
                func_800E6F0C_minigame(4);
                D_8010C756_end_of_the_line = 2;
            }
            break;
        case 2:
            break;
        case 3:
            if (D_800EB934_minigame == 1) {
                func_8010A8B4_end_of_the_line(D_8010C73C_end_of_the_line[0]);
                func_8010A8B4_end_of_the_line(D_8010C73C_end_of_the_line[1]);
            }
            break;
    }
}

void func_8010B190_end_of_the_line(omObjData *obj) {
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    D_8010C7A0_end_of_the_line[idx].x = player->pos2.x;
    D_8010C7A0_end_of_the_line[idx].y = player->pos2.y + 0.0f;
    D_8010C7A0_end_of_the_line[idx].z = player->pos2.z;
    D_8010C788_end_of_the_line[idx].x = player->pos2.x;
    D_8010C788_end_of_the_line[idx].y = 200.0f;
    D_8010C788_end_of_the_line[idx].z = D_8010C7A0_end_of_the_line[idx].z - 1000.0f;
}

void func_8010B234_end_of_the_line(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        D_8010C7A0_end_of_the_line[idx].x = target->trans.x;
        D_8010C7A0_end_of_the_line[idx].y = target->trans.y + 200.0f;
        D_8010C7A0_end_of_the_line[idx].z = target->trans.z;
        D_8010C788_end_of_the_line[idx].x = target->trans.x;
        D_8010C788_end_of_the_line[idx].y = D_8010C7A0_end_of_the_line[idx].y + 700.0f;
        D_8010C788_end_of_the_line[idx].z = D_8010C7A0_end_of_the_line[idx].z + 600.0f;
    }
}

void func_8010B300_end_of_the_line(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    EndOfTheLinePlayerSubWork *sub = OM_GET_DATA_PTR(player->unk04, EndOfTheLinePlayerSubWork);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        if (sub->unk10 != 0) {
            D_8010C738_end_of_the_line->work[0] = obj->work[1];
            target->func = func_8010937C_end_of_the_line;
            D_8010C7A0_end_of_the_line[idx].x = target->trans.x;
            D_8010C7A0_end_of_the_line[idx].y = target->trans.y + 200.0f;
            D_8010C7A0_end_of_the_line[idx].z = target->trans.z;
            sub->unk00 += sub->unk08;
            sub->unk04 += sub->unk0C;
            D_8010C788_end_of_the_line[idx].y = target->trans.y + 200.0f + sub->unk00;
            D_8010C788_end_of_the_line[idx].z = target->trans.z + sub->unk04;
            sub->unk10--;
        } else {
            player->unk04->func = func_8010B420_end_of_the_line;
            func_8010B420_end_of_the_line(obj);
        }
    }
}

void func_8010B420_end_of_the_line(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        D_8010C7A0_end_of_the_line[idx].x = target->trans.x;
        D_8010C7A0_end_of_the_line[idx].y = target->trans.y + 200.0f;
        D_8010C7A0_end_of_the_line[idx].z = target->trans.z;
        D_8010C788_end_of_the_line[idx].x = target->trans.x;
        D_8010C788_end_of_the_line[idx].y = D_8010C7A0_end_of_the_line[idx].y + 500.0f;
        D_8010C788_end_of_the_line[idx].z = D_8010C7A0_end_of_the_line[idx].z + 1000.0f;
    }
}

void func_8010B4EC_end_of_the_line(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        D_8010C7A0_end_of_the_line[idx].x = target->trans.x;
        D_8010C7A0_end_of_the_line[idx].y = 0.0f;
        D_8010C7A0_end_of_the_line[idx].z = target->trans.z;
        D_8010C788_end_of_the_line[idx].x = target->trans.x;
        D_8010C788_end_of_the_line[idx].y = 0.0f;
        D_8010C788_end_of_the_line[idx].z = D_8010C7A0_end_of_the_line[idx].z + 10.0f;
    }
}

void func_8010B588_end_of_the_line(omObjData *obj) {
    omObjData *target = (omObjData *)obj->work[0];
    EndOfTheLinePlayer *player = OM_GET_DATA_PTR(target, EndOfTheLinePlayer);
    s32 idx = player->playerIdx;

    if (obj->work[1] == 1) {
        D_8010C7A0_end_of_the_line[idx].x = target->trans.x;
        D_8010C7A0_end_of_the_line[idx].y = target->trans.y + 100.0f;
        D_8010C7A0_end_of_the_line[idx].z = target->trans.z;
    }
    D_8010C788_end_of_the_line[idx].x = -2200.0f;
    D_8010C788_end_of_the_line[idx].y = -1100.0f;
    D_8010C788_end_of_the_line[idx].z = 700.0f;
}

void func_8010B640_end_of_the_line(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);
    EndOfTheLinePlayer *other = OM_GET_DATA_PTR(D_8010C73C_end_of_the_line[idx ^ 1], EndOfTheLinePlayer);
    s16 *viewport;
    s16 *scissor;
    s16 viewX;

    if (obj->work[2] == 0) {
        D_8010C766_end_of_the_line = 1;
        viewport = D_8010C610_end_of_the_line[idx];
        scissor = D_8010C600_end_of_the_line[idx];
        if (idx == 0) {
            D_8010C5CC_end_of_the_line += 4.0f;
            if (D_8010C5CC_end_of_the_line >= 320.0f) {
                D_8010C5CC_end_of_the_line = 320.0f;
                obj->work[2] = 1;
            }
            espPosSet(data->esprites[idx + 6], D_8010C5CC_end_of_the_line - 160.0f, 0x78);
            espPosSet(data->esprites[7], D_8010C5CC_end_of_the_line + 160.0f, 0x78);
            espPosSet(data->esprites[10], D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx + 4],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx + 2],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            scissor[2] += 4.0f;
            ScissorSet(idx, scissor[0], scissor[1], scissor[2], scissor[3]);
            ScissorSet(1, scissor[2] + 1, D_8010C600_end_of_the_line[1][1], D_8010C600_end_of_the_line[1][2],
                       D_8010C600_end_of_the_line[1][3]);
            viewX = viewport[2] + (D_8010C5CC_end_of_the_line - 160.0f) * 320.0f / 159.0f;
            ViewportSet(idx, viewport[0], viewport[1], 511.0f, viewX, viewport[3], 511.0f);
        } else {
            D_8010C5CC_end_of_the_line -= 4.0f;
            if (D_8010C5CC_end_of_the_line <= 0.0f) {
                D_8010C5CC_end_of_the_line = 0.0f;
                obj->work[2] = 1;
            }
            espPosSet(data->esprites[idx + 6], D_8010C5CC_end_of_the_line + 160.0f, 0x78);
            espPosSet(data->esprites[6], D_8010C5CC_end_of_the_line - 160.0f, 0x78);
            espPosSet(data->esprites[10], D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx + 4],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx + 2],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            espPosSet(data->esprites[other->playerIdx],
                      D_8010C5D0_end_of_the_line[other->playerIdx] + D_8010C5CC_end_of_the_line, 0x78);
            scissor[0] -= 4.0f;
            ScissorSet(idx, scissor[0], scissor[1], scissor[2], scissor[3]);
            ScissorSet(0, D_8010C600_end_of_the_line[0][0], D_8010C600_end_of_the_line[0][1],
                       D_8010C600_end_of_the_line[1][0] - 1, D_8010C600_end_of_the_line[0][3]);
            viewX = viewport[2] - (160.0f - D_8010C5CC_end_of_the_line) * 320.0f / 159.0f;
            ViewportSet(idx, viewport[0], viewport[1], 511.0f, viewX, viewport[3], 511.0f);
        }
    }
    D_8010C668_end_of_the_line = 1.0f;
    D_8010C7A0_end_of_the_line[idx].x = 400.0f;
    D_8010C7A0_end_of_the_line[idx].y = 400.0f;
    D_8010C7A0_end_of_the_line[idx].z = 0.0f;
    D_8010C788_end_of_the_line[idx].x = 1660.0f;
    D_8010C788_end_of_the_line[idx].y = 1030.0f;
    D_8010C788_end_of_the_line[idx].z = 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f, 1.0f);
    Hu3DCameraPerspectiveSet(idx, 33.0f, 80.0f, 20000.0f);
}

void func_8010BE24_end_of_the_line(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);

    if (D_8010C66C_end_of_the_line > 0.9f) {
        D_8010C66C_end_of_the_line -= 0.01f;
    }
    D_8010C7A0_end_of_the_line[idx].x = 400.0f;
    D_8010C7A0_end_of_the_line[idx].y = 400.0f;
    D_8010C7A0_end_of_the_line[idx].z = 0.0f;
    D_8010C788_end_of_the_line[idx].x = D_8010C66C_end_of_the_line * 1660.0f;
    D_8010C788_end_of_the_line[idx].y = D_8010C66C_end_of_the_line * 1030.0f;
    D_8010C788_end_of_the_line[idx].z = D_8010C66C_end_of_the_line * 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f - D_8010C66C_end_of_the_line + 1.0f,
                1.0f - D_8010C66C_end_of_the_line + 1.0f);
}

void func_8010BF64_end_of_the_line(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR((omObjData *)obj->work[0], EndOfTheLinePlayer)->playerIdx;
    EndOfTheLineData *data = OM_GET_DATA_PTR(D_8010C738_end_of_the_line, EndOfTheLineData);

    D_8010C7A0_end_of_the_line[idx].x = 400.0f;
    D_8010C7A0_end_of_the_line[idx].y = 400.0f;
    D_8010C7A0_end_of_the_line[idx].z = 0.0f;
    D_8010C788_end_of_the_line[idx].x = 1660.0f;
    D_8010C788_end_of_the_line[idx].y = 1030.0f;
    D_8010C788_end_of_the_line[idx].z = 810.0f;
    espScaleSet(data->esprites[idx + 6], 1.0f, 1.0f);
    Hu3DCameraPerspectiveSet(idx, 33.0f, 80.0f, 20000.0f);
    obj->work[2] = 1;
}

void func_8010C060_end_of_the_line(omObjData *obj) {
    u32 i;

    for (i = 0; i < obj->work[0]; i++) {
        Hu3DCameraPosSetV(i, &D_8010C788_end_of_the_line[i], &D_8010C7A0_end_of_the_line[i],
                          &D_8010C7B8_end_of_the_line[i]);
        Hu3DCamUpdateMtx(i);
    }
}

void func_8010C110_end_of_the_line(u16 arg0, omObjData *obj, f32 x, f32 y, f32 z) {
    Vec at;
    Vec eye;
    Vec pos;
    f32 len;
    s32 idx;
    s32 i;

    idx = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer)->playerIdx;

    eye.x = D_8010C788_end_of_the_line[idx].x - x;
    eye.y = D_8010C788_end_of_the_line[idx].y - y;
    eye.z = D_8010C788_end_of_the_line[idx].z - z;
    len = HuSqrtf(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z);
    eye.x /= len;
    eye.y /= len;
    eye.z /= len;

    at.x = D_8010C7A0_end_of_the_line[idx].x - x;
    at.y = D_8010C7A0_end_of_the_line[idx].y - y;
    at.z = D_8010C7A0_end_of_the_line[idx].z - z;
    len = HuSqrtf(at.x * at.x + at.y * at.y + at.z * at.z);
    at.x /= len;
    at.y /= len;
    at.z /= len;

    at.x = eye.x * D_8010C6C0_end_of_the_line[arg0].x + (1.0f - D_8010C6C0_end_of_the_line[arg0].x) * at.x;
    at.y = eye.y * D_8010C6C0_end_of_the_line[arg0].y + (1.0f - D_8010C6C0_end_of_the_line[arg0].y) * at.y;
    at.z = eye.z * D_8010C6C0_end_of_the_line[arg0].z + (1.0f - D_8010C6C0_end_of_the_line[arg0].z) * at.z;

    for (i = 0; i < 5; i++) {
        pos.x = x + at.x * D_8010C670_end_of_the_line[arg0][i];
        pos.y = y + at.y * D_8010C670_end_of_the_line[arg0][i];
        pos.z = z + at.z * D_8010C670_end_of_the_line[arg0][i];
        Hu3DModelPosSet(D_8010C738_end_of_the_line->model[20 + i * 2 + idx], pos.x, pos.y, pos.z);
        Hu3DModelScaleSet(D_8010C738_end_of_the_line->model[20 + i * 2 + idx], D_8010C698_end_of_the_line[arg0][i],
                          D_8010C698_end_of_the_line[arg0][i], D_8010C698_end_of_the_line[arg0][i]);
    }
}

void func_8010C3F4_end_of_the_line(void) {
    omObjData *obj;
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010C74C_end_of_the_line[i] = obj = omAddObj(0x28, 1, 0, -1, NULL);
        obj->model[0] = func_8000B108_main(0x540012, 0xA8D);
    }
}

void func_8010C47C_end_of_the_line(omObjData *obj) {
    s32 idx = OM_GET_DATA_PTR(obj, EndOfTheLinePlayer)->playerIdx;

    omSetTra(D_8010C74C_end_of_the_line[idx], obj->trans.x + 150.0f, obj->trans.y + 50.0f, obj->trans.z + 100.0f);
    omSetSca(D_8010C74C_end_of_the_line[idx], 3.0f, 3.0f, 3.0f);
    func_8001C258_main(D_8010C74C_end_of_the_line[idx]->model[0], 4, 0);
    Hu3DModelCameraSet(D_8010C74C_end_of_the_line[idx]->model[0], D_8010C5C8_end_of_the_line[idx]);
    func_8001C814_main(D_8010C74C_end_of_the_line[idx]->model[0], 2, 2);
    D_8010C74C_end_of_the_line[idx]->func = func_8010C574_end_of_the_line;
}

void func_8010C574_end_of_the_line(omObjData *obj) {
}
